# c_unreachable

Cross-compiler `unreachable` hint for C, in a header-only library.

## Usage

The library defines a function-like macro `unreachable`.

> [!WARNING]
> As `unreachable()` is only a hint to the optimizer, actually reaching it will not abort
> the program, but instead, is undefined-behavior.
>
> If you want a safer version, you can use the standard library's [`assert(0 && "unreachable")`](https://en.cppreference.com/w/cpp/error/assert) (only check in debug build) or [`abort()`](https://en.cppreference.com/w/c/program/abort).

## Example

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

## Implementation Priority

1. [C23](https://en.cppreference.com/w/c/program/unreachable)
2. Compiler extension
    - GCC-like (GCC, Clang): [`__builtin_unreachable`](https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#index-_005f_005fbuiltin_005funreachable)
    - MSVC-like (MSVC, Intel): [`__assume(0)`](https://learn.microsoft.com/en-us/cpp/intrinsics/assume)
3. C11 [`_Noreturn`](https://en.cppreference.com/w/c/language/_Noreturn)

If none of the conditions apply, the call to unreachable expands to nothing; no warning or error is emitted.
