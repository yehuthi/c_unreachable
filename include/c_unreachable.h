#ifndef __C_UNREACHABLE_H
#define __C_UNREACHABLE_H

// C23 setup
#if __STDC_VERSION__ > 201710L
#include <stddef.h>
#endif

// C23: check if actually implemented, as C23 is still pretty new
#if __STDC_VERSION__ > 201710L && defined(unreachable)
// then unreachable is provided, do nothing.
// Diagnostics {{{
#ifdef C_UNREACHABLE_DIAG
#if C_UNREACHABLE_DIAG == 1
#error c_unreachable method: C23
#elif C_UNREACHABLE_DIAG == 2
#warning c_unreachable method: C23
#elif C_UNREACHABLE_DIAG == 3
#pragma message("c_unreachable method: C23")
#endif
#endif
// }}}

// Compiler extensions
#elif defined(__GNUC__)
#define unreachable() (__builtin_unreachable())
// Diagnostics {{{
#ifdef C_UNREACHABLE_DIAG
#if C_UNREACHABLE_DIAG == 1
#error c_unreachable method: extension GNU
#elif C_UNREACHABLE_DIAG == 2
#warning c_unreachable method: extension GNU
#elif C_UNREACHABLE_DIAG == 3
#pragma message("c_unreachable method: extension GNU")
#endif
#endif
// }}}
#elif defined(_MSC_VER)
#define unreachable() (__assume(0))
// Diagnostics {{{
#ifdef C_UNREACHABLE_DIAG
#if C_UNREACHABLE_DIAG == 1
#error c_unreachable method: extension MSVC
#elif C_UNREACHABLE_DIAG == 2
#warning c_unreachable method: extension MSVC
#elif C_UNREACHABLE_DIAG == 3
#pragma message("c_unreachable method: extension MSVC")
#endif
#endif
// }}}

// C11 noreturn
#elif __STDC_VERSION__ >= 201112L
_Noreturn inline void __c_unreachable_impl() {}
#define unreachable() (__c_unreachable_impl())
// Diagnostics {{{
#ifdef C_UNREACHABLE_DIAG
#if C_UNREACHABLE_DIAG == 1
#error c_unreachable method: noreturn
#elif C_UNREACHABLE_DIAG == 2
#warning c_unreachable method: noreturn
#elif C_UNREACHABLE_DIAG == 3
#pragma message("c_unreachable method: noreturn")
#endif
#endif
// }}}

// give up
#else
// Diagnostics {{{
#ifdef C_UNREACHABLE_DIAG
#if C_UNREACHABLE_DIAG == 1
#error c_unreachable method: none
#elif C_UNREACHABLE_DIAG == 2
#warning c_unreachable method: none
#elif C_UNREACHABLE_DIAG == 3
#pragma message("c_unreachable method: none")
#endif
#endif
// }}}
#define unreachable()
#endif

#endif // include guard
