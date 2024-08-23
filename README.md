# c_unreachable

Cross-compiler `unreachable` hint for C, in a header-only library.

## Usage

The library defines a function-like macro `unreachable`.

> [!WARNING]
> As `unreachable()` is only a hint to the optimizer, actually reaching it will not abort
> the program, but instead, is undefined-behavior.
>
> If you want a safer version, you can use the standard library's [`assert(0 && "unreachable")`](https://en.cppreference.com/w/cpp/error/assert) (only check in debug build) or [`abort()`](https://en.cppreference.com/w/c/program/abort).

## Examples

Branching:
```c
#include <stdint.h>
#include "c_unreachable.h"

typedef enum {
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
} color;

uint32_t color_value(color c) {
    switch (c) {
        case COLOR_RED:   return 0xff0000;
        case COLOR_GREEN: return 0x00ff00;
        case COLOR_BLUE:  return 0x0000ff;
        default: unreachable();
    }
}
```

Infinite loops:
```c
#include "c_unreachable.h"
#include <stdio.h>
#include <unistd.h>

int main() {
    for(size_t i = 0; ; i++) {
        printf("%d seconds since launch\n", i);
        sleep(1);
    }
    unreachable();
}
```

## CMake Snippet

```cmake
include(FetchContent)
FetchContent_Declare(
    c_unreachable
    GIT_REPOSITORY https://github.com/yehuthi/c_unreachable.git
    GIT_TAG 6cc3b0c52ad0f61823e1ba2a7a7f7f6d448d9293
)
FetchContent_MakeAvailable(c_unreachable)

add_executable(my_project src/main.c)
target_link_libraries(my_project c_unreachable)
```

## Implementation Priority

1. [C23 `unreachable`](https://en.cppreference.com/w/c/program/unreachable) if implemented
2. Compiler extension
    - GCC-like (GCC, Clang): [`__builtin_unreachable`](https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#index-_005f_005fbuiltin_005funreachable)
    - MSVC-like (MSVC, Intel): [`__assume(0)`](https://learn.microsoft.com/en-us/cpp/intrinsics/assume)
3. C11 [`_Noreturn`](https://en.cppreference.com/w/c/language/_Noreturn)
4. None: The call to unreachable expands to nothing; the compiler is not hinted.

### Diagnostics

You can set the `C_UNREACHABLE_DIAG` diagnostics macro to observe the implementation actually used.

When set, a message with the method will show in the compiler's output.
If set to `1` via an error message, `2` for warning, and `3` for message.

Negate the value to only trigger it when no method is used and the compiler cannot be hinted.
E.g. set to `-1` to trigger a compilation error only when hinting was not possible (very discouraged outside
of diagnostics).
