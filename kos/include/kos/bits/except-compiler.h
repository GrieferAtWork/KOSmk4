/* Copyright (c) 2019-2023 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_BITS_EXCEPT_COMPILER_H
#define _KOS_BITS_EXCEPT_COMPILER_H 1

#include <__stdinc.h>

 /* TODO: In user-space, using TRY and EXCEPT should  leave some sort of marker in  the
 *       binary  that allows for libc to consider these handlers as `dlexceptaware(3)'
 *       when operating in except-mode #4. However, I  am unsure as to how this  could
 *       be implemented without making some additional tweaks to gcc under KOS, though
 *       that wouldn't even be  the first time  I had to  tweak binutils/gcc for  this
 *       project... */
#ifdef __cplusplus
#ifdef __CHECKER__
#define __RAII_FINALLY   __IF1
#define __NOEXCEPT_START do noexcept
#define __NOEXCEPT_END   __WHILE0
#else /* __CHECKER__ */
extern "C++" {
__NAMESPACE_INT_BEGIN
template<class __F> struct __FinallyAction {
	__F __c;
	__CXX_CLASSMEMBER __FinallyAction(__F __f) __CXX_NOEXCEPT: __c(__f) {}
	__CXX_CLASSMEMBER ~__FinallyAction() __CXX_NOEXCEPT { __c(); }
};
struct __FinallyBase {
	template<class __F> __CXX_CLASSMEMBER __FinallyAction<__F>
	operator ->* (__F __f) __CXX_NOEXCEPT { return __FinallyAction<__F>(__f); }
};
__NAMESPACE_INT_END
} /* extern "C++" */
#ifndef __COMPILER_UNIQUE
#define __COMPILER_UNIQUE_IMPL2(x, y) x##y
#define __COMPILER_UNIQUE_IMPL(x, y) __COMPILER_UNIQUE_IMPL2(x, y)
#ifdef __COUNTER__
#define __COMPILER_UNIQUE(x) __COMPILER_UNIQUE_IMPL(x, __COUNTER__)
#else /* __COUNTER__ */
#define __COMPILER_UNIQUE(x) __COMPILER_UNIQUE_IMPL(x, __LINE__)
#endif /* !__COUNTER__ */
#endif /* !__COMPILER_UNIQUE */
#define __RAII_FINALLY       auto __COMPILER_UNIQUE(__raii_finally) = __NAMESPACE_INT_SYM __FinallyBase()->*[&]

/* Using NOEXCEPT_START ... NOEXCEPT_END, you can construct blocks of code
 * that will trigger  undefined behavior  if they cause  an exception.  In
 * debug-mode, this  undefined behavior  includes panic/coredump,  similar
 * to when an exception is propagated through a NOTHROW function. */
#ifndef __NOEXCEPT_START
#ifdef __GNUC__
/* Sadly, GCC doesn't see the optimization potential when  encountering
 * a catch-block that consists of nothing but `__builtin_unreachable()'
 *
 * It should be obvious that such a construct could be optimized into
 * a section of code that can be considered as NOTHROW, similar to an
 * inline function declared as NOTHROW. */
#elif !defined(NDEBUG) && !defined(NDEBUG_EXCEPT) && !defined(NDEBUG_NOTHROW)
#define __NOEXCEPT_START do try
#define __NOEXCEPT_END   catch(...) { __builtin_unreachable(); } __WHILE0
#endif /* ... */
#endif /* !__NOEXCEPT_START */
#endif /* !__CHECKER__ */

#ifndef __TRY
#define __TRY    try
#define __EXCEPT catch(...)
#endif /* !__TRY */
#endif /* __cplusplus */

#ifndef __NOEXCEPT_START
#define __NOEXCEPT_START_IS_NOOP
#define __NOEXCEPT_START do
#define __NOEXCEPT_END   __WHILE0
#endif /* !__NOEXCEPT_START */

#endif /* !_KOS_BITS_EXCEPT_COMPILER_H */
