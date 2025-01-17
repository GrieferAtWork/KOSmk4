/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_ASM_RTM_H
#define _I386_KOS_ASM_RTM_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

/* Hardware defined RTM transaction status codes.
 * NOTE: A  value of `0' is possible, and indicates that the transaction
 *       cannot be performed atomically (but that the fallback-path must
 *       be executed instead) */
#define _XABORT_FAILED   __UINT32_C(0x00000000) /* Transaction cannot be performed atomically */
#define _XABORT_EXPLICIT __UINT32_C(0x00000001) /* Abort was caused by `xabort' */
#define _XABORT_RETRY    __UINT32_C(0x00000002) /* The transaction may succeed if re-attempted */
#define _XABORT_CONFLICT __UINT32_C(0x00000004) /* Transaction failed due to an address-conflict with another processor */
#define _XABORT_CAPACITY __UINT32_C(0x00000008) /* The internal buffer to track transactions overflowed */
#define _XABORT_DEBUG    __UINT32_C(0x00000010) /* A #DB (%drN) or #BP (int3) was triggered */
#define _XABORT_NESTED   __UINT32_C(0x00000020) /* A nested transaction failed */
#define _XABORT_NOSYS    __UINT32_C(0x00ffffff) /* RTM isn't supposed */
#define _XABORT_CODE_M   __UINT32_C(0xff000000) /* [valid_if(_XABORT_EXPLICIT)] XABORT argument */
#define _XABORT_CODE_S   24                     /* Shift for `_XABORT_CODE_M' */
#define _XABORT_CODE(x)  (((x) & _XABORT_CODE_M) >> _XABORT_CODE_S)

/* Returned by `__xbegin()' when RTM was entered successfully. */
#define _XBEGIN_STARTED __UINT32_C(0xffffffff) /* RTM was entered */

#ifdef __CC__
__DECL_BEGIN

#if ((__has_builtin(__builtin_ia32_xbegin) || __has_builtin(__builtin_ia32_xend) ||   \
      __has_builtin(__builtin_ia32_xabort) || __has_builtin(__builtin_ia32_xtest)) && \
     (defined(__GNUC__) || defined(__COMPILER_HAVE_PRAGMA_GCC_TARGET)))
#pragma GCC push_options
#pragma GCC target("rtm")
#endif /* ... */

#if __has_builtin(__builtin_ia32_xbegin) || defined(__COMPILER_HAVE_GCC_ASM)
/* Start a transaction (s.a. `rtm_begin()')
 * @return: _XBEGIN_STARTED: Transaction started.
 * @return: _XABORT_* :      Transaction failed. */
__FORCELOCAL __ATTR_ARTIFICIAL __UINT32_TYPE__(__xbegin)(void) {
#if __has_builtin(__builtin_ia32_xbegin)
	return (__UINT32_TYPE__)__builtin_ia32_xbegin();
#else /* __has_builtin(__builtin_ia32_xbegin) */
	__register __UINT32_TYPE__ __result;
	__asm__ __volatile__("xbegin 991f\n\t"
	                     "movl $-1, %%eax\n\t" /* -1 == _XBEGIN_STARTED */
	                     "991:"
	                     : "=a" (__result));
	return __result;
#endif /* !__has_builtin(__builtin_ia32_xbegin) */
}
#endif /* __has_builtin(__builtin_ia32_xbegin) || __COMPILER_HAVE_GCC_ASM */


#if __has_builtin(__builtin_ia32_xend) || defined(__COMPILER_HAVE_GCC_ASM)
/* End a transaction (s.a. `rtm_end()')
 * If  the  transaction   was  successful,  return   normally.
 * If the transaction failed, `__xbegin()' returns `_XABORT_*'
 * If no transaction was in progress, trigger #GP(0) that is propagated to user-space as
 * `E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE:E_ILLEGAL_INSTRUCTION_X86_OPCODE(0x0f01, 2)' */
__FORCELOCAL __ATTR_ARTIFICIAL void(__xend)(void) {
#if __has_builtin(__builtin_ia32_xend)
	__builtin_ia32_xend();
#else /* __has_builtin(__builtin_ia32_xend) */
	__asm__ __volatile__("xend" : : : "memory");
#endif /* !__has_builtin(__builtin_ia32_xend) */
}
#endif /* __has_builtin(__builtin_ia32_xend) || __COMPILER_HAVE_GCC_ASM */


/* Abort the current transaction by having `__xbegin()'
 * return    with     `_XABORT_EXPLICIT | ((code & 0xff) << _XABORT_CODE_S)'
 * If no transaction was in progress, behave as a no-op (s.a. `rtm_abort()') */
#if __has_builtin(__builtin_ia32_xabort)
#define __xabort(code) __builtin_ia32_xabort(code)
#elif !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_GCC_ASM)
#define __xabort(code) __XBLOCK({ __asm__ __volatile__("xabort %0" : : "N" (code)); (void)0; })
#elif defined(__COMPILER_HAVE_GCC_ASM)
#define __xabort(code) __asm__ __volatile__("xabort %0" : : "N" (code))
#endif /* ... */


/* Check if a transaction is currently in progress (s.a. `rtm_test()')
 * @return: true:  Inside of RTM mode
 * @return: false: Outside of RTM mode */
#if __has_builtin(__builtin_ia32_xtest) || defined(__COMPILER_HAVE_GCC_ASM)
#ifdef __KOS__ /* Always available under KOS */
__FORCELOCAL __ATTR_ARTIFICIAL __BOOL __NOTHROW(__xtest)(void)
#else /* __KOS__ */
__FORCELOCAL __ATTR_ARTIFICIAL __BOOL(__xtest)(void)
#endif /* !__KOS__ */
{
#if __has_builtin(__builtin_ia32_xtest)
	return __builtin_ia32_xtest();
#else /* __has_builtin(__builtin_ia32_xtest) */
	__BOOL __result;
	/* TODO: Check for `__GCC_ASM_FLAG_OUTPUTS__' */
	__asm__ __volatile__("xtest" : "=@ccz" (__result) : : "cc");
	return __result;
#endif /* !__has_builtin(__builtin_ia32_xtest) */
}
#endif /* __has_builtin(__builtin_ia32_xtest) || __COMPILER_HAVE_GCC_ASM */

#if ((__has_builtin(__builtin_ia32_xbegin) || __has_builtin(__builtin_ia32_xend) ||   \
      __has_builtin(__builtin_ia32_xabort) || __has_builtin(__builtin_ia32_xtest)) && \
     (defined(__GNUC__) || defined(__COMPILER_HAVE_PRAGMA_GCC_TARGET)))
#pragma GCC pop_options
#endif /* ... */

__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_ASM_RTM_H */
