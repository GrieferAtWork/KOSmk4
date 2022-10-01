/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID_SPCALL_H
#define __GUARD_HYBRID_SPCALL_H 1

#include "../__stdinc.h"
/**/

#include "host.h"
#include "typecore.h"

/*
 * Portable helpers for calling a function with a different stack
 *
 * >> PRIVATE ATTR_NOINLINE ATTR_NORETURN ATTR_USED
 * >> void SPCALL_CC callee(void *arg) {
 * >>     ...
 * >>     __builtin_unreachable();
 * >> }
 * >>
 * >> PRIVATE void *stack[1024];
 * >>
 * >> PRIVATE void do_call(void *arg) {
 * >>     SPCALL_NORETURN(callee, arg, stack, sizeof(stack));
 * >> }
 *
 * Use the function:
 * >> ATTR_NORETURN void SPCALL_NORETURN(void (SPCALL_CC &fun)(void *), void *arg,
 * >>                                    void *stackaddr, size_t stacksize);
 *
 * When not supported, `!defined(SPCALL)'
 */


#ifdef __x86_64__
/************************************************************************/
/* X86_64                                                               */
/************************************************************************/

#if defined(_MSC_VER) && 0 /* inline asm isn't supported by 64-bit vc */
#define SPCALL_CC __ATTR_MSABI
#define SPCALL_NORETURN(fun, arg, stackaddr, stacksize)       \
	do {                                                      \
		void *__spc_arg      = (arg);                         \
		void *__spc_stackend = (__BYTE_TYPE__ *)(stackaddr) + \
		                                        (stacksize) - \
		                                        32;           \
		__asm {                                               \
			__asm MOV RCX, __spc_arg                          \
			__asm MOV RSP, __spc_stackend                     \
			__asm CALL fun                                    \
		}                                                     \
		__builtin_unreachable();                              \
	}	__WHILE0
#elif defined(__COMPILER_HAVE_GCC_ASM)
#ifdef __USER_LABEL_PREFIX__
#define __USER_LABEL_PREFIX_STR__ PP_STR(__USER_LABEL_PREFIX__)
#else /* __USER_LABEL_PREFIX__ */
#define __USER_LABEL_PREFIX_STR__ /* nothing */
#endif /* !__USER_LABEL_PREFIX__ */
#if !defined(__NO_ATTR_MSABI) && (defined(__NO_ATTR_SYSVABI) || defined(__WINNT__))
#define SPCALL_CC __ATTR_MSABI
#define SPCALL_NORETURN(fun, arg, stackaddr, stacksize)       \
	do {                                                      \
		void *__spc_stackend = (__BYTE_TYPE__ *)(stackaddr) + \
		                                        (stacksize) - \
		                                        32;           \
		__asm__ __volatile__("movq %0, %%rsp\n\t"             \
		                     "call "                          \
		                     __USER_LABEL_PREFIX_STR__        \
		                     PP_STR(fun)                      \
		                     :                                \
		                     : "g" (__spc_stackend)           \
		                     , "c" (arg)                      \
		                     : "memory", "cc");               \
		__builtin_unreachable();                              \
	}	__WHILE0
#else /* ...  */
#define SPCALL_CC __ATTR_SYSVABI
#define SPCALL_NORETURN(fun, arg, stackaddr, stacksize)       \
	do {                                                      \
		void *__spc_stackend = (__BYTE_TYPE__ *)(stackaddr) + \
		                                        (stacksize);  \
		__asm__ __volatile__("movq %0, %%rsp\n\t"             \
		                     "call "                          \
		                     __USER_LABEL_PREFIX_STR__        \
		                     PP_STR(fun)                      \
		                     :                                \
		                     : "g" (__spc_stackend)           \
		                     , "D" (arg)                      \
		                     : "memory", "cc");               \
		__builtin_unreachable();                              \
	}	__WHILE0
#endif /* !... */
#endif /* ... */

#elif defined(__i386__)
/************************************************************************/
/* I386                                                                 */
/************************************************************************/

#ifdef _MSC_VER
#define SPCALL_CC __ATTR_FASTCALL
#define SPCALL_NORETURN(fun, arg, stackaddr, stacksize)       \
	do {                                                      \
		void *__spc_arg      = (arg);                         \
		void *__spc_stackend = (__BYTE_TYPE__ *)(stackaddr) + \
		                                        (stacksize);  \
		__asm {                                               \
			__asm MOV ECX, __spc_arg                          \
			__asm MOV ESP, __spc_stackend                     \
			__asm CALL fun                                    \
		}                                                     \
		__builtin_unreachable();                              \
	}	__WHILE0
#else /* _MSC_VER */
#ifndef __NO_ATTR_FASTCALL
#define SPCALL_CC __ATTR_FASTCALL
#define SPCALL_NORETURN(fun, arg, stackaddr, stacksize)       \
	do {                                                      \
		void *__spc_stackend = (__BYTE_TYPE__ *)(stackaddr) + \
		                                        (stacksize);  \
		__asm__ __volatile__("movl %0, %%esp\n\t"             \
		                     "call "                          \
		                     __USER_LABEL_PREFIX_STR__        \
		                     PP_STR(fun)                      \
		                     :                                \
		                     : "g" (__spc_stackend)           \
		                     , "c" (arg)                      \
		                     : "memory", "cc");               \
		__builtin_unreachable();                              \
	}	__WHILE0
#else /* !__NO_ATTR_FASTCALL */
#define SPCALL_CC __ATTR_CDECL
#define SPCALL_NORETURN(fun, arg, stackaddr, stacksize)       \
	do {                                                      \
		void *__spc_stackend = (__BYTE_TYPE__ *)(stackaddr) + \
		                                        (stacksize) - \
		                                        4;            \
		*(void **)__spc_stackend = (arg);                     \
		__asm__ __volatile__("movl %0, %%esp\n\t"             \
		                     "call "                          \
		                     __USER_LABEL_PREFIX_STR__        \
		                     PP_STR(fun)                      \
		                     :                                \
		                     : "g" (__spc_stackend)           \
		                     : "memory", "cc");               \
		__builtin_unreachable();                              \
	}	__WHILE0
#endif /* __NO_ATTR_FASTCALL */
#endif /* !_MSC_VER */

#else /* ARCH... */
/* ... Unsupported architecture */
#endif /* !ARCH... */



#endif /* !__GUARD_HYBRID_SPCALL_H */
