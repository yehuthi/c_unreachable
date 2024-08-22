#pragma once

// C23
#if __STDC_VERSION__ >= 202311L
#include <stddef.h>
#else

// Compiler extensions
#ifdef __GNUC__
#define unreachable() (__builtin_unreachable())
#elifdef _MSC_VER
#define unreachable() (__assume(0))

// C11 noreturn
#elseif __STDC_VERSION__ >= 201112L
_Noreturn inline void __c_unreachable_impl() {}
#define unreachable() (__c_unreachable_impl())

// give up
#else
#define unreachable
#endif

#endif // C23 branch
