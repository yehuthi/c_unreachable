#ifndef __C_UNREACHABLE_H
#define __C_UNREACHABLE_H

// C23 setup
#if __STDC_VERSION__ >= 202311L
#include <stddef.h>
#endif

// C23: check if actually implemented, as C23 is still pretty new
#if __STDC_VERSION__ >= 202311L && defined(unreachable)
// then unreachable is provided, do nothing.

// Compiler extensions
#elif defined(__GNUC__)
#define unreachable() (__builtin_unreachable())
#elif defined(_MSC_VER)
#define unreachable() (__assume(0))

// C11 noreturn
#elif __STDC_VERSION__ >= 201112L
_Noreturn inline void __c_unreachable_impl() {}
#define unreachable() (__c_unreachable_impl())

// give up
#else
#define unreachable
#endif

#endif // include guard
