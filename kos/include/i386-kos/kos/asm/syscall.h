/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_KOS_ASM_SYSCALL_H
#define _I386_KOS_KOS_ASM_SYSCALL_H 1

#include <__stdinc.h>
#include <__crt.h>

#define __X86_SYSCALL_EXISTS_PLACEHOLDER_0    ,
#define __X86_SYSCALL_EXISTS_PLACEHOLDER_1    ,
#define __X86_SYSCALL_EXISTS_PLACEHOLDER_2    ,
#define __X86_SYSCALL_EXISTS_PLACEHOLDER_3    ,
#define __X86_SYSCALL_EXISTS_PLACEHOLDER_4    ,
#define __X86_SYSCALL_EXISTS_PLACEHOLDER_5    ,
#define __X86_SYSCALL_EXISTS_PLACEHOLDER_6    ,
#define __X86_SYSCALL_EXISTS_ARG_IMPL(x, val, ...) val
#define __X86_SYSCALL_EXISTS_ARG(x) __X86_SYSCALL_EXISTS_ARG_IMPL x
#define __X86_SYSCALL_EXISTS3(...)  __X86_SYSCALL_EXISTS_ARG((__VA_ARGS__ 1, 0))
#define __X86_SYSCALL_EXISTS2(x)    __X86_SYSCALL_EXISTS3(__X86_SYSCALL_EXISTS_PLACEHOLDER_##x)
#define __X86_SYSCALL_EXISTS(x)     __X86_SYSCALL_EXISTS2(x)

#ifndef __NRFEAT_DEFINED_SYSCALL_REGISTER_COUNT
#undef __WANT_SYSCALL_REGISTER_COUNT
#define __WANT_SYSCALL_REGISTER_COUNT 1
#include <asm/syscalls.h>
#endif /* !__NRFEAT_DEFINED_SYSCALL_REGISTER_COUNT */
#define __CRT_HAVE_SC(name) __X86_SYSCALL_EXISTS(__NRRC_##name)


#ifdef __KERNEL__
#include <hybrid/host.h>

#ifdef __x86_64__
#define __ARCH_SYSCALLCC __ATTR_SYSVABI
#else /* __x86_64__ */
#define __ARCH_SYSCALLCC __ATTR_CDECL
#endif /* !__x86_64__ */

#define __CDECLARE_SC(attr, Treturn, name, param, args) __PUBDEF attr Treturn (__ARCH_SYSCALLCC sys_##name) param;
#define __CDECLARE_VOID_SC(attr, name, param, args)     __PUBDEF attr void (__ARCH_SYSCALLCC sys_##name) param;

/* Within the kernel, syscall functions _all_ can throw errors! */
#define __CDECLARE_XSC(attr, Treturn, name, param, args) /* nothing */
#define __CDECLARE_VOID_XSC(attr, name, param, args)     /* nothing */
#define __CRT_HAVE_XSC(name) 0

#else /* __KERNEL__ */
#undef __HAVE_INLINE_SYSCALLS
#ifdef __WANT_INLINE_SYSCALLS
#define __HAVE_INLINE_SYSCALLS 1

#ifdef __CC__
#include <hybrid/host.h>
#include <bits/types.h>
#include <__crt.h>


#if !defined(__NRFEAT_DEFINED_SYSCALL_ARGUMENT_LIST_PACKER) || \
    !defined(__NRFEAT_DEFINED_SYSCALL_ATTR_NORETURN)
#undef __WANT_SYSCALL_ARGUMENT_LIST_PACKER
#undef __WANT_SYSCALL_ATTR_NORETURN
#define __WANT_SYSCALL_ARGUMENT_LIST_PACKER 1
#define __WANT_SYSCALL_ATTR_NORETURN 1
#include <asm/syscalls-proto.h>
#endif /* !... */


#define __CRT_HAVE_XSC __CRT_HAVE_SC

#define __X86_SYSCALL_NORETURN_UNREACHABLE2_0   /* nothing */
#define __X86_SYSCALL_NORETURN_UNREACHABLE2_1   __builtin_unreachable();
#define __X86_SYSCALL_NORETURN_UNREACHABLE2(is) __X86_SYSCALL_NORETURN_UNREACHABLE2_##is
#define __X86_SYSCALL_NORETURN_UNREACHABLE(is)  __X86_SYSCALL_NORETURN_UNREACHABLE2(is)
#define __X86_SYSCALL_COMMA_IF_ARGC_0   /* nothing */
#define __X86_SYSCALL_COMMA_IF_ARGC_1   ,
#define __X86_SYSCALL_COMMA_IF_ARGC_2   ,
#define __X86_SYSCALL_COMMA_IF_ARGC_3   ,
#define __X86_SYSCALL_COMMA_IF_ARGC_4   ,
#define __X86_SYSCALL_COMMA_IF_ARGC_5   ,
#define __X86_SYSCALL_COMMA_IF_ARGC_6   ,
#define __X86_SYSCALL_COMMA_IF_ARGC2(n) __X86_SYSCALL_COMMA_IF_ARGC_##n
#define __X86_SYSCALL_COMMA_IF_ARGC(n) __X86_SYSCALL_COMMA_IF_ARGC2(n)


__SYSDECL_BEGIN
#ifdef __x86_64__

__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_syscall0)(__syscall_ulong_t __sysno) { __register __syscall_ulong_t __res; __asm__ __volatile__("clc\n\tsyscall" : "=a" (__res) : "0" (__sysno) : "memory", "cc", "rcx", "r11"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_Xsyscall0)(__syscall_ulong_t __sysno) { __register __syscall_ulong_t __res; __asm__ __volatile__("stc\n\tsyscall" : "=a" (__res) : "0" (__sysno) : "memory", "cc", "rcx", "r11"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_syscall1)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0) { __register __syscall_ulong_t __res; __asm__ __volatile__("clc\n\tsyscall" : "=a" (__res) : "0" (__sysno), "D" (__arg0) : "memory", "cc", "rcx", "r11"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_Xsyscall1)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0) { __register __syscall_ulong_t __res; __asm__ __volatile__("stc\n\tsyscall" : "=a" (__res) : "0" (__sysno), "D" (__arg0) : "memory", "cc", "rcx", "r11"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_syscall2)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1) { __register __syscall_ulong_t __res; __asm__ __volatile__("clc\n\tsyscall" : "=a" (__res) : "0" (__sysno), "D" (__arg0), "S" (__arg1) : "memory", "cc", "rcx", "r11"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_Xsyscall2)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1) { __register __syscall_ulong_t __res; __asm__ __volatile__("stc\n\tsyscall" : "=a" (__res) : "0" (__sysno), "D" (__arg0), "S" (__arg1) : "memory", "cc", "rcx", "r11"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_syscall3)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2) { __register __syscall_ulong_t __res; __asm__ __volatile__("clc\n\tsyscall" : "=a" (__res) : "0" (__sysno), "D" (__arg0), "S" (__arg1), "d" (__arg2) : "memory", "cc", "rcx", "r11"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_Xsyscall3)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2) { __register __syscall_ulong_t __res; __asm__ __volatile__("stc\n\tsyscall" : "=a" (__res) : "0" (__sysno), "D" (__arg0), "S" (__arg1), "d" (__arg2) : "memory", "cc", "rcx", "r11"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_syscall4)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3) { __register __syscall_ulong_t __res; __register __syscall_ulong_t __r10 __asm__("%r10") = __arg3; __asm__ __volatile__("clc\n\tsyscall" : "=a" (__res) : "0" (__sysno), "D" (__arg0), "S" (__arg1), "d" (__arg2), "r" (__r10) : "memory", "cc", "rcx", "r11"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_Xsyscall4)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3) { __register __syscall_ulong_t __res; __register __syscall_ulong_t __r10 __asm__("%r10") = __arg3; __asm__ __volatile__("stc\n\tsyscall" : "=a" (__res) : "0" (__sysno), "D" (__arg0), "S" (__arg1), "d" (__arg2), "r" (__r10) : "memory", "cc", "rcx", "r11"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_syscall5)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3, __syscall_ulong_t __arg4) { __register __syscall_ulong_t __res; __register __syscall_ulong_t __r10 __asm__("%r10") = __arg3; __register __syscall_ulong_t __r8 __asm__("%r8") = __arg4; __asm__ __volatile__("clc\n\tsyscall" : "=a" (__res) : "0" (__sysno), "D" (__arg0), "S" (__arg1), "d" (__arg2), "r" (__r10), "r" (__r8) : "memory", "cc", "rcx", "r11"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_Xsyscall5)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3, __syscall_ulong_t __arg4) { __register __syscall_ulong_t __res; __register __syscall_ulong_t __r10 __asm__("%r10") = __arg3; __register __syscall_ulong_t __r8 __asm__("%r8") = __arg4; __asm__ __volatile__("stc\n\tsyscall" : "=a" (__res) : "0" (__sysno), "D" (__arg0), "S" (__arg1), "d" (__arg2), "r" (__r10), "r" (__r8) : "memory", "cc", "rcx", "r11"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_syscall6)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3, __syscall_ulong_t __arg4, __syscall_ulong_t __arg5) { __register __syscall_ulong_t __res; __register __syscall_ulong_t __r10 __asm__("%r10") = __arg3; __register __syscall_ulong_t __r8 __asm__("%r8") = __arg4; __register __syscall_ulong_t __r9 __asm__("%r9") = __arg5; __asm__ __volatile__("clc\n\tsyscall" : "=a" (__res) : "0" (__sysno), "D" (__arg0), "S" (__arg1), "d" (__arg2), "r" (__r10), "r" (__r8), "r" (__r9) : "memory", "cc", "rcx", "r11"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_Xsyscall6)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3, __syscall_ulong_t __arg4, __syscall_ulong_t __arg5) { __register __syscall_ulong_t __res; __register __syscall_ulong_t __r10 __asm__("%r10") = __arg3; __register __syscall_ulong_t __r8 __asm__("%r8") = __arg4; __register __syscall_ulong_t __r9 __asm__("%r9") = __arg5; __asm__ __volatile__("stc\n\tsyscall" : "=a" (__res) : "0" (__sysno), "D" (__arg0), "S" (__arg1), "d" (__arg2), "r" (__r10), "r" (__r8), "r" (__r9) : "memory", "cc", "rcx", "r11"); return __res; }

#define __X86_64_SYSCALL_SELECT2(argc)  __x86_syscall##argc
#define __X86_64_SYSCALL_SELECT(argc)   __X86_64_SYSCALL_SELECT2(argc)
#define __X86_64_XSYSCALL_SELECT2(argc) __x86_Xsyscall##argc
#define __X86_64_XSYSCALL_SELECT(argc)  __X86_64_XSYSCALL_SELECT2(argc)

#define __X86_64_SYSCALL_ARG_PLACEHOLDER_1  ,
#define __X86_64_SYSCALL_TAKE_SECOND_ARG_IMPL(x,val,...) val
#define __X86_64_SYSCALL_TAKE_SECOND_ARG(x) __X86_64_SYSCALL_TAKE_SECOND_ARG_IMPL x
#define __X86_64_SYSCALL_IS_DEFINED3(...) __X86_64_SYSCALL_TAKE_SECOND_ARG((__VA_ARGS__ 1, 0))
#define __X86_64_SYSCALL_IS_DEFINED2(x) __X86_64_SYSCALL_IS_DEFINED3(__X86_64_SYSCALL_ARG_PLACEHOLDER_##x)
#define __X86_64_SYSCALL_IS_DEFINED(x)  __X86_64_SYSCALL_IS_DEFINED2(x)

#define __CDECLARE_SC(attr, Treturn, name, param, args)                                                                                    \
	__FORCELOCAL attr Treturn (__LIBCCALL sys_##name) param {                                                                              \
		return (Treturn)__X86_64_SYSCALL_SELECT(__NRRC_##name)(__NR_##name __X86_SYSCALL_COMMA_IF_ARGC(__NRRC_##name) __NRAP_##name args); \
	}
#define __CDECLARE_VOID_SC(attr, name, param, args)                                                                        \
	__FORCELOCAL attr void (__LIBCCALL sys_##name) param {                                                                 \
		__X86_64_SYSCALL_SELECT(__NRRC_##name)(__NR_##name __X86_SYSCALL_COMMA_IF_ARGC(__NRRC_##name) __NRAP_##name args); \
		__X86_SYSCALL_NORETURN_UNREACHABLE(__X86_64_SYSCALL_IS_DEFINED(__NRNT_##name));                                    \
	}
#define __CDECLARE_XSC(attr, Treturn, name, param, args)                                                                                   \
	__FORCELOCAL attr Treturn (__LIBCCALL sys_X##name) param {                                                                             \
		return (Treturn)__X86_64_SYSCALL_SELECT(__NRRC_##name)(__NR_##name __X86_SYSCALL_COMMA_IF_ARGC(__NRRC_##name) __NRAP_##name args); \
	}
#define __CDECLARE_VOID_XSC(attr, name, param, args)                                                                       \
	__FORCELOCAL attr void (__LIBCCALL sys_X##name) param {                                                                \
		__X86_64_SYSCALL_SELECT(__NRRC_##name)(__NR_##name __X86_SYSCALL_COMMA_IF_ARGC(__NRRC_##name) __NRAP_##name args); \
		__X86_SYSCALL_NORETURN_UNREACHABLE(__X86_64_SYSCALL_IS_DEFINED(__NRNT_##name));                                    \
	}

#else /* __x86_64__ */

#if defined(__X86_SYSCALL_METHOD_INT80)
#define __X86_SYSCALL_ASSEMBLY   "clc\n\tint {$0x80|80h}"
#define __X86_XSYSCALL_ASSEMBLY  "stc\n\tint {$0x80|80h}"
#elif defined(__X86_SYSCALL_METHOD_SYSENTER) && 0 /* TODO */
#define __X86_SYSCALL_ASSEMBLY   "clc\n\tsysenter" /* TODO */
#define __X86_XSYSCALL_ASSEMBLY  "stc\n\tsysenter" /* TODO */
#elif defined(__BUILDING_LIBC)
__asm__(".hidden libc___i386_syscall\n\t.global libc___i386_syscall\n\t"
        ".hidden libc___i386_Xsyscall\n\t.global libc___i386_Xsyscall\n\t");
#define __X86_SYSCALL_ASSEMBLY   "call libc___i386_syscall"
#define __X86_XSYSCALL_ASSEMBLY  "call libc___i386_Xsyscall"
#elif defined(__CRT_HAVE___i386_syscall0) && defined(__CRT_HAVE___i386_Xsyscall0) && \
      defined(__CRT_HAVE___i386_syscall5) && defined(__CRT_HAVE___i386_Xsyscall5) && \
      0 /* This method doesn't work since PLT requires %ebx to point to the GOT, \
         * however the system call itself also needs %ebx as an argument register, \
         * so we have no way of actually invoking any kind of system call (especially \
         * since it is %ebx that is used to pass the very first argument) */
#define __X86_SYSCALL_ASSEMBLY   "call __i386_syscall@PLT"
#define __X86_XSYSCALL_ASSEMBLY  "call __i386_Xsyscall@PLT"
#else
#define __X86_SYSCALL_ASSEMBLY   "clc\n\tint {$0x80|80h}"
#define __X86_XSYSCALL_ASSEMBLY  "stc\n\tint {$0x80|80h}"
#endif

__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_syscall0)(__syscall_ulong_t __sysno) { __register __syscall_ulong_t __res; __asm__ __volatile__(__X86_SYSCALL_ASSEMBLY : "=a" (__res) : "0" (__sysno) : "memory", "cc"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_Xsyscall0)(__syscall_ulong_t __sysno) { __register __syscall_ulong_t __res; __asm__ __volatile__(__X86_XSYSCALL_ASSEMBLY : "=a" (__res) : "0" (__sysno) : "memory", "cc"); return __res; }
__FORCELOCAL __uint64_t (__LIBCCALL __x86_syscall0_dw)(__syscall_ulong_t __sysno) { __register __uint64_t __res; __asm__ __volatile__(__X86_SYSCALL_ASSEMBLY : "=A" (__res) : "a" (__sysno) : "memory", "cc"); return __res; }
__FORCELOCAL __uint64_t (__LIBCCALL __x86_Xsyscall0_dw)(__syscall_ulong_t __sysno) { __register __uint64_t __res; __asm__ __volatile__(__X86_XSYSCALL_ASSEMBLY : "=A" (__res) : "a" (__sysno) : "memory", "cc"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_syscall1)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0) { __register __syscall_ulong_t __res; __asm__ __volatile__(__X86_SYSCALL_ASSEMBLY : "=a" (__res) : "0" (__sysno), "b" (__arg0) : "memory", "cc"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_Xsyscall1)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0) { __register __syscall_ulong_t __res; __asm__ __volatile__(__X86_XSYSCALL_ASSEMBLY : "=a" (__res) : "0" (__sysno), "b" (__arg0) : "memory", "cc"); return __res; }
__FORCELOCAL __uint64_t (__LIBCCALL __x86_syscall1_dw)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0) { __register __uint64_t __res; __asm__ __volatile__(__X86_SYSCALL_ASSEMBLY : "=A" (__res) : "a" (__sysno), "b" (__arg0) : "memory", "cc"); return __res; }
__FORCELOCAL __uint64_t (__LIBCCALL __x86_Xsyscall1_dw)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0) { __register __uint64_t __res; __asm__ __volatile__(__X86_XSYSCALL_ASSEMBLY : "=A" (__res) : "a" (__sysno), "b" (__arg0) : "memory", "cc"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_syscall2)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1) { __register __syscall_ulong_t __res; __asm__ __volatile__(__X86_SYSCALL_ASSEMBLY : "=a" (__res) : "0" (__sysno), "b" (__arg0), "c" (__arg1) : "memory", "cc"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_Xsyscall2)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1) { __register __syscall_ulong_t __res; __asm__ __volatile__(__X86_XSYSCALL_ASSEMBLY : "=a" (__res) : "0" (__sysno), "b" (__arg0), "c" (__arg1) : "memory", "cc"); return __res; }
__FORCELOCAL __uint64_t (__LIBCCALL __x86_syscall2_dw)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1) { __register __uint64_t __res; __asm__ __volatile__(__X86_SYSCALL_ASSEMBLY : "=A" (__res) : "a" (__sysno), "b" (__arg0), "c" (__arg1) : "memory", "cc"); return __res; }
__FORCELOCAL __uint64_t (__LIBCCALL __x86_Xsyscall2_dw)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1) { __register __uint64_t __res; __asm__ __volatile__(__X86_XSYSCALL_ASSEMBLY : "=A" (__res) : "a" (__sysno), "b" (__arg0), "c" (__arg1) : "memory", "cc"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_syscall3)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2) { __register __syscall_ulong_t __res; __asm__ __volatile__(__X86_SYSCALL_ASSEMBLY : "=a" (__res) : "0" (__sysno), "b" (__arg0), "c" (__arg1), "d" (__arg2) : "memory", "cc"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_Xsyscall3)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2) { __register __syscall_ulong_t __res; __asm__ __volatile__(__X86_XSYSCALL_ASSEMBLY : "=a" (__res) : "0" (__sysno), "b" (__arg0), "c" (__arg1), "d" (__arg2) : "memory", "cc"); return __res; }
__FORCELOCAL __uint64_t (__LIBCCALL __x86_syscall3_dw)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2) { __register __uint64_t __res; __asm__ __volatile__(__X86_SYSCALL_ASSEMBLY : "=A" (__res) : "a" (__sysno), "b" (__arg0), "c" (__arg1), "d" (__arg2) : "memory", "cc"); return __res; }
__FORCELOCAL __uint64_t (__LIBCCALL __x86_Xsyscall3_dw)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2) { __register __uint64_t __res; __asm__ __volatile__(__X86_XSYSCALL_ASSEMBLY : "=A" (__res) : "a" (__sysno), "b" (__arg0), "c" (__arg1), "d" (__arg2) : "memory", "cc"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_syscall4)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3) { __register __syscall_ulong_t __res; __asm__ __volatile__(__X86_SYSCALL_ASSEMBLY : "=a" (__res) : "0" (__sysno), "b" (__arg0), "c" (__arg1), "d" (__arg2), "S" (__arg3) : "memory", "cc"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_Xsyscall4)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3) { __register __syscall_ulong_t __res; __asm__ __volatile__(__X86_XSYSCALL_ASSEMBLY : "=a" (__res) : "0" (__sysno), "b" (__arg0), "c" (__arg1), "d" (__arg2), "S" (__arg3) : "memory", "cc"); return __res; }
__FORCELOCAL __uint64_t (__LIBCCALL __x86_syscall4_dw)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3) { __register __uint64_t __res; __asm__ __volatile__(__X86_SYSCALL_ASSEMBLY : "=A" (__res) : "a" (__sysno), "b" (__arg0), "c" (__arg1), "d" (__arg2), "S" (__arg3) : "memory", "cc"); return __res; }
__FORCELOCAL __uint64_t (__LIBCCALL __x86_Xsyscall4_dw)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3) { __register __uint64_t __res; __asm__ __volatile__(__X86_XSYSCALL_ASSEMBLY : "=A" (__res) : "a" (__sysno), "b" (__arg0), "c" (__arg1), "d" (__arg2), "S" (__arg3) : "memory", "cc"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_syscall5)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3, __syscall_ulong_t __arg4) { __register __syscall_ulong_t __res; __asm__ __volatile__(__X86_SYSCALL_ASSEMBLY : "=a" (__res) : "0" (__sysno), "b" (__arg0), "c" (__arg1), "d" (__arg2), "S" (__arg3), "D" (__arg4) : "memory", "cc"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_Xsyscall5)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3, __syscall_ulong_t __arg4) { __register __syscall_ulong_t __res; __asm__ __volatile__(__X86_XSYSCALL_ASSEMBLY : "=a" (__res) : "0" (__sysno), "b" (__arg0), "c" (__arg1), "d" (__arg2), "S" (__arg3), "D" (__arg4) : "memory", "cc"); return __res; }
__FORCELOCAL __uint64_t (__LIBCCALL __x86_syscall5_dw)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3, __syscall_ulong_t __arg4) { __register __uint64_t __res; __asm__ __volatile__(__X86_SYSCALL_ASSEMBLY : "=A" (__res) : "a" (__sysno), "b" (__arg0), "c" (__arg1), "d" (__arg2), "S" (__arg3), "D" (__arg4) : "memory", "cc"); return __res; }
__FORCELOCAL __uint64_t (__LIBCCALL __x86_Xsyscall5_dw)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3, __syscall_ulong_t __arg4) { __register __uint64_t __res; __asm__ __volatile__(__X86_XSYSCALL_ASSEMBLY : "=A" (__res) : "a" (__sysno), "b" (__arg0), "c" (__arg1), "d" (__arg2), "S" (__arg3), "D" (__arg4) : "memory", "cc"); return __res; }

#if 0 /* F$CK! YOU GCC! Why isn't there any f-ing way to pass values through EBP? */
register __ULONGPTR_TYPE__ __kos_syscall6_ebp __asm__("%ebp");
#define __X86_SYSCALL_WITH_EBP(c) c 
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_syscall6)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3, __syscall_ulong_t __arg4, __syscall_ulong_t __arg5) { __register __syscall_ulong_t __res; __kos_syscall6_ebp = __arg5; __asm__ __volatile__(__X86_SYSCALL_WITH_EBP(__X86_SYSCALL_ASSEMBLY) : "=a" (__res) : "0" (__sysno), "b" (__arg0), "c" (__arg1), "d" (__arg2), "S" (__arg3), "D" (__arg4) : "memory", "cc"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_Xsyscall6)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3, __syscall_ulong_t __arg4, __syscall_ulong_t __arg5) { __register __syscall_ulong_t __res; __kos_syscall6_ebp = __arg5; __asm__ __volatile__(__X86_SYSCALL_WITH_EBP(__X86_XSYSCALL_ASSEMBLY) : "=a" (__res) : "0" (__sysno), "b" (__arg0), "c" (__arg1), "d" (__arg2), "S" (__arg3), "D" (__arg4) : "memory", "cc"); return __res; }
__FORCELOCAL __uint64_t (__LIBCCALL __x86_syscall6_dw)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3, __syscall_ulong_t __arg4, __syscall_ulong_t __arg5) { __register __uint64_t __res; __kos_syscall6_ebp = __arg5; __asm__ __volatile__(__X86_SYSCALL_WITH_EBP(__X86_SYSCALL_ASSEMBLY) : "=A" (__res) : "a" (__sysno), "b" (__arg0), "c" (__arg1), "d" (__arg2), "S" (__arg3), "D" (__arg4) : "memory", "cc"); return __res; }
__FORCELOCAL __uint64_t (__LIBCCALL __x86_Xsyscall6_dw)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3, __syscall_ulong_t __arg4, __syscall_ulong_t __arg5) { __register __uint64_t __res; __kos_syscall6_ebp = __arg5; __asm__ __volatile__(__X86_SYSCALL_WITH_EBP(__X86_XSYSCALL_ASSEMBLY) : "=A" (__res) : "a" (__sysno), "b" (__arg0), "c" (__arg1), "d" (__arg2), "S" (__arg3), "D" (__arg4) : "memory", "cc"); return __res; }
#undef __X86_SYSCALL_WITH_EBP
#else
/* FIXME: `__X86_SYSCALL_TEST_EBP' is incomplete, and could never be complete.
 *        Add an extension to binutils `.ifccont' that behaves similar to `.ifc',
 *        but checks for contains, rather than equals */
#include "syscall-test-ebp.h"

#define __X86_DEFINE_SYSCALL6_WRAPPER                                             \
	".ifndef __x86.syscall6\n"                                                    \
	".pushsection .text.__x86.syscall6,\"axG\",@progbits,__x86.syscall6,comdat\n" \
	".globl   __x86.syscall6\n"                                                   \
	".hidden  __x86.syscall6\n"                                                   \
	".type    __x86.syscall6, @function\n"                                        \
	"__x86.syscall6:\n"                                                           \
	"\t.cfi_startproc simple\n"                                                   \
	"\t.cfi_def_cfa %%esp, 8\n"                                                   \
	"\t.cfi_rel_offset %%eip, 0\n"                                                \
	"\txchgl %%ebp, 4(%%esp)\n"                                                   \
	"\t" __X86_SYSCALL_ASSEMBLY "\n"                                              \
	"\tmovl  4(%%esp), %%ebp\n"                                                   \
	"\tret   $4\n"                                                                \
	"\t.cfi_endproc\n"                                                            \
	".popsection\n"                                                               \
	".endif\n"
	
#define __X86_DEFINE_XSYSCALL6_WRAPPER                                              \
	".ifndef __x86.Xsyscall6\n"                                                     \
	".pushsection .text.__x86.Xsyscall6,\"axG\",@progbits,__x86.Xsyscall6,comdat\n" \
	".globl   __x86.Xsyscall6\n"                                                    \
	".hidden  __x86.Xsyscall6\n"                                                    \
	".type    __x86.Xsyscall6, @function\n"                                         \
	"__x86.Xsyscall6:\n"                                                            \
	"\t.cfi_startproc simple\n"                                                     \
	"\t.cfi_def_cfa %%esp, 8\n"                                                     \
	"\t.cfi_rel_offset %%eip, 0\n"                                                  \
	"\txchgl %%ebp, 4(%%esp)\n"                                                     \
	"\t" __X86_XSYSCALL_ASSEMBLY "\n"                                               \
	"\tmovl  4(%%esp), %%ebp\n"                                                     \
	"\tret   $4\n"                                                                  \
	"\t.cfi_endproc\n"                                                              \
	".size __x86.Xsyscall6, . - __x86.Xsyscall6\n"                                  \
	".popsection\n"                                                                 \
	".endif\n"
	
#define __X86_SYSCALL_WITH_EBP(c, w, cw) \
	".ifc %8,%%ebp\n\t" c "\n\t"         \
	".else\n\t"                          \
	__X86_SYSCALL_TEST_EBP               \
	".ifdef .Lbp%=\n\t" w                \
	"pushl %8\n\t" cw "\n\t"             \
	".else\n\t"                          \
	"movl %%ebp, %1\n\t"                 \
	"movl %8, %%ebp\n\t" c "\n\t"        \
	"movl %1, %%ebp\n\t"                 \
	".endif\n\t"                         \
	".endif\n\t"
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_syscall6)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3, __syscall_ulong_t __arg4, __syscall_ulong_t __arg5) { __register __syscall_ulong_t __res; __register __syscall_ulong_t __temp; __asm__ __volatile__(__X86_SYSCALL_WITH_EBP(__X86_SYSCALL_ASSEMBLY, __X86_DEFINE_SYSCALL6_WRAPPER, "call __x86.syscall6") : "=a" (__res), "=&m" (__temp) : "0" (__sysno), "b" (__arg0), "c" (__arg1), "d" (__arg2), "S" (__arg3), "D" (__arg4), "g" (__arg5) : "memory", "cc"); return __res; }
__FORCELOCAL __syscall_ulong_t (__LIBCCALL __x86_Xsyscall6)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3, __syscall_ulong_t __arg4, __syscall_ulong_t __arg5) { __register __syscall_ulong_t __res; __register __syscall_ulong_t __temp; __asm__ __volatile__(__X86_SYSCALL_WITH_EBP(__X86_XSYSCALL_ASSEMBLY, __X86_DEFINE_XSYSCALL6_WRAPPER, "call __x86.Xsyscall6") : "=a" (__res), "=&m" (__temp) : "0" (__sysno), "b" (__arg0), "c" (__arg1), "d" (__arg2), "S" (__arg3), "D" (__arg4), "g" (__arg5) : "memory", "cc"); return __res; }
__FORCELOCAL __uint64_t (__LIBCCALL __x86_syscall6_dw)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3, __syscall_ulong_t __arg4, __syscall_ulong_t __arg5) { __register __uint64_t __res; __register __syscall_ulong_t __temp; __asm__ __volatile__(__X86_SYSCALL_WITH_EBP(__X86_SYSCALL_ASSEMBLY, __X86_DEFINE_SYSCALL6_WRAPPER, "call __x86.syscall6") : "=A" (__res), "=&m" (__temp) : "a" (__sysno), "b" (__arg0), "c" (__arg1), "d" (__arg2), "S" (__arg3), "D" (__arg4), "g" (__arg5) : "memory", "cc"); return __res; }
__FORCELOCAL __uint64_t (__LIBCCALL __x86_Xsyscall6_dw)(__syscall_ulong_t __sysno, __syscall_ulong_t __arg0, __syscall_ulong_t __arg1, __syscall_ulong_t __arg2, __syscall_ulong_t __arg3, __syscall_ulong_t __arg4, __syscall_ulong_t __arg5) { __register __uint64_t __res; __register __syscall_ulong_t __temp; __asm__ __volatile__(__X86_SYSCALL_WITH_EBP(__X86_XSYSCALL_ASSEMBLY, __X86_DEFINE_XSYSCALL6_WRAPPER, "call __x86.Xsyscall6") : "=A" (__res), "=&m" (__temp) : "a" (__sysno), "b" (__arg0), "c" (__arg1), "d" (__arg2), "S" (__arg3), "D" (__arg4), "g" (__arg5) : "memory", "cc"); return __res; }
#undef __X86_SYSCALL_WITH_EBP
#endif

#undef __X86_XSYSCALL_ASSEMBLY
#undef __X86_SYSCALL_ASSEMBLY
#undef __X86_XSYSCALL0_ASSEMBLY
#undef __X86_SYSCALL0_ASSEMBLY

#define __I386_SYSCALL_ARG_PLACEHOLDER_1  ,
#define __I386_SYSCALL_TAKE_SECOND_ARG_IMPL(x, val, ...) val
#define __I386_SYSCALL_TAKE_SECOND_ARG(x) __I386_SYSCALL_TAKE_SECOND_ARG_IMPL x
#define __I386_SYSCALL_IS_DEFINED3(...) __I386_SYSCALL_TAKE_SECOND_ARG((__VA_ARGS__ 1, 0))
#define __I386_SYSCALL_IS_DEFINED2(x) __I386_SYSCALL_IS_DEFINED3(__I386_SYSCALL_ARG_PLACEHOLDER_##x)
#define __I386_SYSCALL_IS_DEFINED(x)  __I386_SYSCALL_IS_DEFINED2(x)
#define __I386_SYSCALL_SELECT2_0(n)   __x86_syscall##n
#define __I386_SYSCALL_SELECT2_1(n)   __x86_syscall##n##_dw
#define __I386_SYSCALL_SELECT2(n, dw) __I386_SYSCALL_SELECT2_##dw(n)
#define __I386_SYSCALL_SELECT(n, dw)  __I386_SYSCALL_SELECT2(n, dw)
#define __I386_SYSCALL_SELECT0(n)     __I386_SYSCALL_SELECT2_0(n)
#define __I386_XSYSCALL_SELECT2_0(n)  __x86_Xsyscall##n
#define __I386_XSYSCALL_SELECT2_1(n)  __x86_Xsyscall##n##_dw
#define __I386_XSYSCALL_SELECT2(n,dw) __I386_XSYSCALL_SELECT2_##dw(n)
#define __I386_XSYSCALL_SELECT(n, dw) __I386_XSYSCALL_SELECT2(n, dw)
#define __I386_XSYSCALL_SELECT0(n)    __I386_XSYSCALL_SELECT2_0(n)

#define __CDECLARE_SC(attr, Treturn, name, param, args)                                                                   \
	__FORCELOCAL attr Treturn (__LIBCCALL sys_##name) param {                                                             \
		return (Treturn)__I386_SYSCALL_SELECT(__NRRC_##name,__I386_SYSCALL_IS_DEFINED(__NRDW_##name))                     \
		                                     (__NR_##name __X86_SYSCALL_COMMA_IF_ARGC(__NRRC_##name) __NRAP_##name args); \
	}
#define __CDECLARE_VOID_SC(attr, name, param, args)                                                        \
	__FORCELOCAL attr void (__LIBCCALL sys_##name) param {                                                 \
		__I386_SYSCALL_SELECT0(__NRRC_##name)                                                              \
		                      (__NR_##name __X86_SYSCALL_COMMA_IF_ARGC(__NRRC_##name) __NRAP_##name args); \
		__X86_SYSCALL_NORETURN_UNREACHABLE(__I386_SYSCALL_IS_DEFINED(__NRNT_##name));                      \
	}
#define __CDECLARE_XSC(attr, Treturn, name, param, args)                                                                  \
	__FORCELOCAL attr Treturn (__LIBCCALL sys_X##name) param {                                                            \
		return (Treturn)__I386_XSYSCALL_SELECT(__NRRC_##name,__I386_SYSCALL_IS_DEFINED(__NRDW_##name))                    \
		                                     (__NR_##name __X86_SYSCALL_COMMA_IF_ARGC(__NRRC_##name) __NRAP_##name args); \
	}
#define __CDECLARE_VOID_XSC(attr, name, param, args)                                                        \
	__FORCELOCAL attr void (__LIBCCALL sys_X##name) param {                                                 \
		__I386_XSYSCALL_SELECT0(__NRRC_##name)                                                              \
		                       (__NR_##name __X86_SYSCALL_COMMA_IF_ARGC(__NRRC_##name) __NRAP_##name args); \
		__X86_SYSCALL_NORETURN_UNREACHABLE(__I386_SYSCALL_IS_DEFINED(__NRNT_##name));                       \
	}
#endif /* !__x86_64__ */

__SYSDECL_END

#endif /* __CC__ */
#endif /* __WANT_INLINE_SYSCALLS */
#endif /* !__KERNEL__ */

#endif /* !_I386_KOS_KOS_ASM_SYSCALL_H */
