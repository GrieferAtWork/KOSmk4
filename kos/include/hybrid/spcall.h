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
 * Use the functions:
 * >> ATTR_NORETURN void SPCALL_NORETURN_SP(void (SPCALL_CC &fun)(void *), void *arg, void *sp);
 * >> ATTR_NORETURN void SPCALL_NORETURN(void (SPCALL_CC &fun)(void *), void *arg,
 * >>                                    void *stackaddr, size_t stacksize);
 *
 * When not supported, `!defined(SPCALL_NORETURN)'
 */

#ifndef __USER_LABEL_PREFIX_STR__
#ifdef __USER_LABEL_PREFIX__
#define __USER_LABEL_PREFIX_STR__ __PP_STR(__USER_LABEL_PREFIX__)
#else /* __USER_LABEL_PREFIX__ */
#define __USER_LABEL_PREFIX_STR__ /* nothing */
#endif /* !__USER_LABEL_PREFIX__ */
#endif /* !__USER_LABEL_PREFIX_STR__ */


#ifdef __ARCH_STACK_ALIGNMENT
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
#define __PRIVATE_SPALIGN(sp) \
	(void *)((__UINTPTR_TYPE__)(sp) & ~(__ARCH_STACK_ALIGNMENT - 1))
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
#define __PRIVATE_SPALIGN(sp) \
	(void *)(((__UINTPTR_TYPE__)(sp) + __ARCH_STACK_ALIGNMENT - 1) & ~(__ARCH_STACK_ALIGNMENT - 1))
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
#else /* __ARCH_STACK_ALIGNMENT */
#define __PRIVATE_SPALIGN(sp) sp
#endif /* !__ARCH_STACK_ALIGNMENT */

#ifdef __x86_64__
/************************************************************************/
/* X86_64                                                               */
/************************************************************************/

#if defined(_MSC_VER) && 0 /* inline asm isn't supported by 64-bit vc */
#define SPCALL_CC __ATTR_MSABI
#define SPCALL_NORETURN_SP(fun, arg, sp)                    \
	do {                                                    \
		void *__spc_arg      = (arg);                       \
		void *__spc_stackend = (__BYTE_TYPE__ *)(sp) - 32;  \
		__spc_stackend = __PRIVATE_SPALIGN(__spc_stackend); \
		__asm {                                             \
			__asm MOV RCX, __spc_arg                        \
			__asm MOV RSP, __spc_stackend                   \
			__asm CALL fun                                  \
		}                                                   \
		__builtin_unreachable();                            \
	}	__WHILE0
#elif defined(__COMPILER_HAVE_GCC_ASM)
#if !defined(__NO_ATTR_MSABI) && (defined(__NO_ATTR_SYSVABI) || defined(__WINNT__))
#define SPCALL_CC __ATTR_MSABI
#define SPCALL_NORETURN_SP(fun, arg, sp)                    \
	do {                                                    \
		void *__spc_stackend = (__BYTE_TYPE__ *)(sp) - 32;  \
		__spc_stackend = __PRIVATE_SPALIGN(__spc_stackend); \
		__asm__ __volatile__("movq %0, %%rsp\n\t"           \
		                     "call "                        \
		                     __USER_LABEL_PREFIX_STR__      \
		                     __PP_STR(fun)                  \
		                     :                              \
		                     : "g" (__spc_stackend)         \
		                     , "c" (arg)                    \
		                     : "memory", "cc");             \
		__builtin_unreachable();                            \
	}	__WHILE0
#else /* ...  */
#define SPCALL_CC __ATTR_SYSVABI
#define SPCALL_NORETURN_SP(fun, arg, sp)               \
	do {                                               \
		void *__spc_stackend = __PRIVATE_SPALIGN(sp);  \
		__asm__ __volatile__("movq %0, %%rsp\n\t"      \
		                     "call "                   \
		                     __USER_LABEL_PREFIX_STR__ \
		                     __PP_STR(fun)             \
		                     :                         \
		                     : "g" (__spc_stackend)    \
		                     , "D" (arg)               \
		                     : "memory", "cc");        \
		__builtin_unreachable();                       \
	}	__WHILE0
#endif /* !... */
#endif /* ... */

#elif defined(__i386__)
/************************************************************************/
/* I386                                                                 */
/************************************************************************/

#ifdef _MSC_VER
#define SPCALL_CC __ATTR_FASTCALL
#define SPCALL_NORETURN_SP(fun, arg, sp)              \
	do {                                              \
		void *__spc_arg      = (arg);                 \
		void *__spc_stackend = __PRIVATE_SPALIGN(sp); \
		__asm {                                       \
			__asm MOV ECX, __spc_arg                  \
			__asm MOV ESP, __spc_stackend             \
			__asm CALL fun                            \
		}                                             \
		__builtin_unreachable();                      \
	}	__WHILE0
#elif defined(__COMPILER_HAVE_GCC_ASM)
#ifndef __NO_ATTR_FASTCALL
#define SPCALL_CC __ATTR_FASTCALL
#define SPCALL_NORETURN_SP(fun, arg, sp)               \
	do {                                               \
		void *__spc_stackend = __PRIVATE_SPALIGN(sp);  \
		__asm__ __volatile__("movl %0, %%esp\n\t"      \
		                     "call "                   \
		                     __USER_LABEL_PREFIX_STR__ \
		                     __PP_STR(fun)             \
		                     :                         \
		                     : "g" (__spc_stackend)    \
		                     , "c" (arg)               \
		                     : "memory", "cc");        \
		__builtin_unreachable();                       \
	}	__WHILE0
#else /* !__NO_ATTR_FASTCALL */
#define SPCALL_CC __ATTR_CDECL
#define SPCALL_NORETURN_SP(fun, arg, sp)                    \
	do {                                                    \
		void *__spc_stackend = (__BYTE_TYPE__ *)(sp) - 4;   \
		__spc_stackend = __PRIVATE_SPALIGN(__spc_stackend); \
		*(void **)__spc_stackend = (arg);                   \
		__asm__ __volatile__("movl %0, %%esp\n\t"           \
		                     "call "                        \
		                     __USER_LABEL_PREFIX_STR__      \
		                     __PP_STR(fun)                  \
		                     :                              \
		                     : "g" (__spc_stackend)         \
		                     : "memory", "cc");             \
		__builtin_unreachable();                            \
	}	__WHILE0
#endif /* __NO_ATTR_FASTCALL */
#endif /* ... */

#elif defined(__aarch64__)
/************************************************************************/
/* AARCH64                                                              */
/************************************************************************/

#if defined(__COMPILER_HAVE_GCC_ASM) && defined(__COMPILER_HAVE_REGISTER_VARS)
#define SPCALL_CC /* nothing */
#define SPCALL_NORETURN_SP(fun, arg, sp)               \
	do {                                               \
		void *__spc_stackend = __PRIVATE_SPALIGN(sp);  \
		__register_var(void *, __x0, "x0") = (arg);    \
		__asm__ __volatile__("mov sp, %0\n\t"          \
		                     "bl "                     \
		                     __USER_LABEL_PREFIX_STR__ \
		                     __PP_STR(fun)             \
		                     :                         \
		                     : "r" (__spc_stackend)    \
		                     , "r" (__x0)              \
		                     : "memory", "cc");        \
		__builtin_unreachable();                       \
	}	__WHILE0
#endif /* __COMPILER_HAVE_GCC_ASM && __COMPILER_HAVE_REGISTER_VARS */

#elif defined(__arm__)
/************************************************************************/
/* ARM                                                                  */
/************************************************************************/

#if defined(__COMPILER_HAVE_GCC_ASM) && defined(__COMPILER_HAVE_REGISTER_VARS)
#define SPCALL_CC /* nothing */
#define SPCALL_NORETURN_SP(fun, arg, sp)               \
	do {                                               \
		void *__spc_stackend = __PRIVATE_SPALIGN(sp);  \
		__register_var(void *, __r0, "r0") = (arg);    \
		__asm__ __volatile__("mov sp, %0\n\t"          \
		                     "bl "                     \
		                     __USER_LABEL_PREFIX_STR__ \
		                     __PP_STR(fun)             \
		                     :                         \
		                     : "r" (__spc_stackend)    \
		                     , "r" (__r0)              \
		                     : "memory", "cc");        \
		__builtin_unreachable();                       \
	}	__WHILE0
#endif /* __COMPILER_HAVE_GCC_ASM && __COMPILER_HAVE_REGISTER_VARS */

#else /* ARCH... */
/* ... Unsupported architecture */
#endif /* !ARCH... */


#ifdef SPCALL_NORETURN_SP
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
#define SPCALL_NORETURN(fun, arg, stackbase, stacksize) \
	SPCALL_NORETURN_SP(fun, arg, (__BYTE_TYPE__ *)(stackbase) + (stacksize))
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
#define SPCALL_NORETURN(fun, arg, stackbase, stacksize) \
	SPCALL_NORETURN_SP(fun, arg, stackbase)
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
#endif /* SPCALL_NORETURN_SP */



#endif /* !__GUARD_HYBRID_SPCALL_H */
