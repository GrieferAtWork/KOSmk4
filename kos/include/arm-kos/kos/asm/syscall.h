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
#ifndef _ARM_KOS_KOS_ASM_SYSCALL_H
#define _ARM_KOS_KOS_ASM_SYSCALL_H 1

#include <__stdinc.h>
#ifndef __LCLINT__
#include <__crt.h>

#define __ARM_SYSCALL_EXISTS_PLACEHOLDER_0    ,
#define __ARM_SYSCALL_EXISTS_PLACEHOLDER_1    ,
#define __ARM_SYSCALL_EXISTS_PLACEHOLDER_2    ,
#define __ARM_SYSCALL_EXISTS_PLACEHOLDER_3    ,
#define __ARM_SYSCALL_EXISTS_PLACEHOLDER_4    ,
#define __ARM_SYSCALL_EXISTS_PLACEHOLDER_5    ,
#define __ARM_SYSCALL_EXISTS_PLACEHOLDER_6    ,
#define __ARM_SYSCALL_EXISTS_ARG_IMPL(x, val, ...) val
#define __ARM_SYSCALL_EXISTS_ARG(x) __ARM_SYSCALL_EXISTS_ARG_IMPL x
#define __ARM_SYSCALL_EXISTS3(...)  __ARM_SYSCALL_EXISTS_ARG((__VA_ARGS__ 1, 0))
#define __ARM_SYSCALL_EXISTS2(x)    __ARM_SYSCALL_EXISTS3(__ARM_SYSCALL_EXISTS_PLACEHOLDER_##x)
#define __ARM_SYSCALL_EXISTS(x)     __ARM_SYSCALL_EXISTS2(x)

#ifndef __NRFEAT_DEFINED_SYSCALL_REGISTER_COUNT
#undef __WANT_SYSCALL_REGISTER_COUNT
#define __WANT_SYSCALL_REGISTER_COUNT 1
#include <asm/syscalls.h>
#endif /* !__NRFEAT_DEFINED_SYSCALL_REGISTER_COUNT */

#ifdef __KERNEL__
#include <hybrid/host.h>

#define __ARCH_SYSCALLCC /* nothing */

#define __CDECLARE_SC(attr, Treturn, name, param, args) __PUBDEF attr Treturn (sys_##name) param;
#define __CDECLARE_VOID_SC(attr, name, param, args)     __PUBDEF attr void (sys_##name) param;

/* Within the kernel, syscall functions _all_ can throw errors! */
#define __CDECLARE_XSC(attr, Treturn, name, param, args) /* nothing */
#define __CDECLARE_VOID_XSC(attr, name, param, args)     /* nothing */
#define __CRT_HAVE_SC(name) __ARM_SYSCALL_EXISTS(__NRRC_##name)
#define __CRT_HAVE_XSC(name) 0

#else /* __KERNEL__ */

#undef __HAVE_INLINE_SYSCALLS
/* Enable inline system calls if explicitly requested, or under freestanding configurations */
#if defined(__WANT_INLINE_SYSCALLS) || defined(__CRT_FREESTANDING) || 1
#define __HAVE_INLINE_SYSCALLS 1
#ifdef __CC__
#include <hybrid/host.h>
#include <bits/types.h>

#if (!defined(__NRFEAT_DEFINED_SYSCALL_ARGUMENT_LIST_PACKER) || \
     !defined(__NRFEAT_DEFINED_SYSCALL_ATTR_NORETURN))
#undef __WANT_SYSCALL_ARGUMENT_LIST_PACKER
#undef __WANT_SYSCALL_ATTR_NORETURN
#define __WANT_SYSCALL_ARGUMENT_LIST_PACKER 1
#define __WANT_SYSCALL_ATTR_NORETURN 1
#include <asm/syscalls-proto.h>
#endif /* !... */

#define __CRT_HAVE_SC(name) __ARM_SYSCALL_EXISTS(__NRRC_##name)
#define __CRT_HAVE_XSC      __CRT_HAVE_SC

#define __ARM_SYSCALL_NORETURN_UNREACHABLE2_0   /* nothing */
#define __ARM_SYSCALL_NORETURN_UNREACHABLE2_1   __builtin_unreachable();
#define __ARM_SYSCALL_NORETURN_UNREACHABLE2(is) __ARM_SYSCALL_NORETURN_UNREACHABLE2_##is
#define __ARM_SYSCALL_NORETURN_UNREACHABLE(is)  __ARM_SYSCALL_NORETURN_UNREACHABLE2(is)
#define __ARM_SYSCALL_COMMA_IF_ARGC_0           /* nothing */
#define __ARM_SYSCALL_COMMA_IF_ARGC_1           ,
#define __ARM_SYSCALL_COMMA_IF_ARGC_2           ,
#define __ARM_SYSCALL_COMMA_IF_ARGC_3           ,
#define __ARM_SYSCALL_COMMA_IF_ARGC_4           ,
#define __ARM_SYSCALL_COMMA_IF_ARGC_5           ,
#define __ARM_SYSCALL_COMMA_IF_ARGC_6           ,
#define __ARM_SYSCALL_COMMA_IF_ARGC2(n)         __ARM_SYSCALL_COMMA_IF_ARGC_##n
#define __ARM_SYSCALL_COMMA_IF_ARGC(n)          __ARM_SYSCALL_COMMA_IF_ARGC2(n)


__SYSDECL_BEGIN

#define __ARM_DO_SYSCALL(sysno, ...)                       \
	__register_var(__syscall_ulong_t, __r7, "r7") = sysno; \
	__asm__ __volatile__("swi 0x0"                         \
	                     : "=r" (__r0)                     \
	                     : "r" (__r7) __VA_ARGS__          \
	                     : "memory")

#define __ARM_DO_SYSCALL_DW(sysno, ...)                    \
	__register_var(__syscall_ulong_t, __r7, "r7") = sysno; \
	__asm__ __volatile__("swi 0x0"                         \
	                     : "=r" (__r0), "=r" (__r1)        \
	                     : "r" (__r7) __VA_ARGS__          \
	                     : "memory")
#define __ARM_PACK_SYSRET_DW() ((__uint64_t)__r0 | ((__uint64_t)__r1 << 32))



__FORCELOCAL __ATTR_ARTIFICIAL __syscall_ulong_t (__LIBKCALL __arm_syscall0)(__syscall_ulong_t __sysno) {
	__register_var(__syscall_ulong_t, __r0, "r0");
	__ARM_DO_SYSCALL(__sysno);
	return __r0;
}

__FORCELOCAL __ATTR_ARTIFICIAL __syscall_ulong_t (__LIBKCALL __arm_syscall1)(__syscall_ulong_t __sysno,
                                                                             __syscall_ulong_t __arg0) {
	__register_var(__syscall_ulong_t, __r0, "r0") = __arg0;
	__ARM_DO_SYSCALL(__sysno,, "r" (__r0));
	return __r0;
}

__FORCELOCAL __ATTR_ARTIFICIAL __syscall_ulong_t (__LIBKCALL __arm_syscall2)(__syscall_ulong_t __sysno,
                                                                             __syscall_ulong_t __arg0,
                                                                             __syscall_ulong_t __arg1) {
	__register_var(__syscall_ulong_t, __r0, "r0") = __arg0;
	__register_var(__syscall_ulong_t, __r1, "r1") = __arg1;
	__ARM_DO_SYSCALL(__sysno,, "r" (__r0), "r" (__r1));
	return __r0;
}

__FORCELOCAL __ATTR_ARTIFICIAL __syscall_ulong_t (__LIBKCALL __arm_syscall3)(__syscall_ulong_t __sysno,
                                                                             __syscall_ulong_t __arg0,
                                                                             __syscall_ulong_t __arg1,
                                                                             __syscall_ulong_t __arg2) {
	__register_var(__syscall_ulong_t, __r0, "r0") = __arg0;
	__register_var(__syscall_ulong_t, __r1, "r1") = __arg1;
	__register_var(__syscall_ulong_t, __r2, "r2") = __arg2;
	__ARM_DO_SYSCALL(__sysno,, "r" (__r0), "r" (__r1), "r" (__r2));
	return __r0;
}

__FORCELOCAL __ATTR_ARTIFICIAL __syscall_ulong_t (__LIBKCALL __arm_syscall4)(__syscall_ulong_t __sysno,
                                                                             __syscall_ulong_t __arg0,
                                                                             __syscall_ulong_t __arg1,
                                                                             __syscall_ulong_t __arg2,
                                                                             __syscall_ulong_t __arg3) {
	__register_var(__syscall_ulong_t, __r0, "r0") = __arg0;
	__register_var(__syscall_ulong_t, __r1, "r1") = __arg1;
	__register_var(__syscall_ulong_t, __r2, "r2") = __arg2;
	__register_var(__syscall_ulong_t, __r3, "r3") = __arg3;
	__ARM_DO_SYSCALL(__sysno,, "r" (__r0), "r" (__r1), "r" (__r2), "r" (__r3));
	return __r0;
}

__FORCELOCAL __ATTR_ARTIFICIAL __syscall_ulong_t (__LIBKCALL __arm_syscall5)(__syscall_ulong_t __sysno,
                                                                             __syscall_ulong_t __arg0,
                                                                             __syscall_ulong_t __arg1,
                                                                             __syscall_ulong_t __arg2,
                                                                             __syscall_ulong_t __arg3,
                                                                             __syscall_ulong_t __arg4) {
	__register_var(__syscall_ulong_t, __r0, "r0") = __arg0;
	__register_var(__syscall_ulong_t, __r1, "r1") = __arg1;
	__register_var(__syscall_ulong_t, __r2, "r2") = __arg2;
	__register_var(__syscall_ulong_t, __r3, "r3") = __arg3;
	__register_var(__syscall_ulong_t, __r4, "r4") = __arg4;
	__ARM_DO_SYSCALL(__sysno,, "r" (__r0), "r" (__r1), "r" (__r2), "r" (__r3), "r" (__r4));
	return __r0;
}

__FORCELOCAL __ATTR_ARTIFICIAL __syscall_ulong_t (__LIBKCALL __arm_syscall6)(__syscall_ulong_t __sysno,
                                                                             __syscall_ulong_t __arg0,
                                                                             __syscall_ulong_t __arg1,
                                                                             __syscall_ulong_t __arg2,
                                                                             __syscall_ulong_t __arg3,
                                                                             __syscall_ulong_t __arg4,
                                                                             __syscall_ulong_t __arg5) {
	__register_var(__syscall_ulong_t, __r0, "r0") = __arg0;
	__register_var(__syscall_ulong_t, __r1, "r1") = __arg1;
	__register_var(__syscall_ulong_t, __r2, "r2") = __arg2;
	__register_var(__syscall_ulong_t, __r3, "r3") = __arg3;
	__register_var(__syscall_ulong_t, __r4, "r4") = __arg4;
	__register_var(__syscall_ulong_t, __r5, "r5") = __arg5;
	__ARM_DO_SYSCALL(__sysno,, "r" (__r0), "r" (__r1), "r" (__r2), "r" (__r3), "r" (__r4), "r" (__r5));
	return __r0;
}

__FORCELOCAL __ATTR_ARTIFICIAL __syscall_ulong_t (__LIBKCALL __arm_syscall7)(__syscall_ulong_t __sysno,
                                                                             __syscall_ulong_t __arg0,
                                                                             __syscall_ulong_t __arg1,
                                                                             __syscall_ulong_t __arg2,
                                                                             __syscall_ulong_t __arg3,
                                                                             __syscall_ulong_t __arg4,
                                                                             __syscall_ulong_t __arg5,
                                                                             __syscall_ulong_t __arg6) {
	__register_var(__syscall_ulong_t, __r0, "r0") = __arg0;
	__register_var(__syscall_ulong_t, __r1, "r1") = __arg1;
	__register_var(__syscall_ulong_t, __r2, "r2") = __arg2;
	__register_var(__syscall_ulong_t, __r3, "r3") = __arg3;
	__register_var(__syscall_ulong_t, __r4, "r4") = __arg4;
	__register_var(__syscall_ulong_t, __r5, "r5") = __arg5;
	__register_var(__syscall_ulong_t, __r6, "r6") = __arg6;
	__ARM_DO_SYSCALL(__sysno,, "r" (__r0), "r" (__r1), "r" (__r2), "r" (__r3), "r" (__r4), "r" (__r5), "r" (__r6));
	return __r0;
}


__FORCELOCAL __ATTR_ARTIFICIAL __uint64_t (__LIBKCALL __arm_syscall0_dw)(__syscall_ulong_t __sysno) {
	__register_var(__syscall_ulong_t, __r0, "r0");
	__register_var(__syscall_ulong_t, __r1, "r1");
	__ARM_DO_SYSCALL_DW(__sysno);
	return __ARM_PACK_SYSRET_DW();
}

__FORCELOCAL __ATTR_ARTIFICIAL __uint64_t (__LIBKCALL __arm_syscall1_dw)(__syscall_ulong_t __sysno,
                                                                         __syscall_ulong_t __arg0) {
	__register_var(__syscall_ulong_t, __r0, "r0") = __arg0;
	__register_var(__syscall_ulong_t, __r1, "r1");
	__ARM_DO_SYSCALL_DW(__sysno,, "r" (__r0));
	return __ARM_PACK_SYSRET_DW();
}

__FORCELOCAL __ATTR_ARTIFICIAL __uint64_t (__LIBKCALL __arm_syscall2_dw)(__syscall_ulong_t __sysno,
                                                                         __syscall_ulong_t __arg0,
                                                                         __syscall_ulong_t __arg1) {
	__register_var(__syscall_ulong_t, __r0, "r0") = __arg0;
	__register_var(__syscall_ulong_t, __r1, "r1") = __arg1;
	__ARM_DO_SYSCALL_DW(__sysno,, "r" (__r0), "r" (__r1));
	return __ARM_PACK_SYSRET_DW();
}

__FORCELOCAL __ATTR_ARTIFICIAL __uint64_t (__LIBKCALL __arm_syscall3_dw)(__syscall_ulong_t __sysno,
                                                                         __syscall_ulong_t __arg0,
                                                                         __syscall_ulong_t __arg1,
                                                                         __syscall_ulong_t __arg2) {
	__register_var(__syscall_ulong_t, __r0, "r0") = __arg0;
	__register_var(__syscall_ulong_t, __r1, "r1") = __arg1;
	__register_var(__syscall_ulong_t, __r2, "r2") = __arg2;
	__ARM_DO_SYSCALL_DW(__sysno,, "r" (__r0), "r" (__r1), "r" (__r2));
	return __ARM_PACK_SYSRET_DW();
}

__FORCELOCAL __ATTR_ARTIFICIAL __uint64_t (__LIBKCALL __arm_syscall4_dw)(__syscall_ulong_t __sysno,
                                                                         __syscall_ulong_t __arg0,
                                                                         __syscall_ulong_t __arg1,
                                                                         __syscall_ulong_t __arg2,
                                                                         __syscall_ulong_t __arg3) {
	__register_var(__syscall_ulong_t, __r0, "r0") = __arg0;
	__register_var(__syscall_ulong_t, __r1, "r1") = __arg1;
	__register_var(__syscall_ulong_t, __r2, "r2") = __arg2;
	__register_var(__syscall_ulong_t, __r3, "r3") = __arg3;
	__ARM_DO_SYSCALL_DW(__sysno,, "r" (__r0), "r" (__r1), "r" (__r2), "r" (__r3));
	return __ARM_PACK_SYSRET_DW();
}

__FORCELOCAL __ATTR_ARTIFICIAL __uint64_t (__LIBKCALL __arm_syscall5_dw)(__syscall_ulong_t __sysno,
                                                                         __syscall_ulong_t __arg0,
                                                                         __syscall_ulong_t __arg1,
                                                                         __syscall_ulong_t __arg2,
                                                                         __syscall_ulong_t __arg3,
                                                                         __syscall_ulong_t __arg4) {
	__register_var(__syscall_ulong_t, __r0, "r0") = __arg0;
	__register_var(__syscall_ulong_t, __r1, "r1") = __arg1;
	__register_var(__syscall_ulong_t, __r2, "r2") = __arg2;
	__register_var(__syscall_ulong_t, __r3, "r3") = __arg3;
	__register_var(__syscall_ulong_t, __r4, "r4") = __arg4;
	__ARM_DO_SYSCALL_DW(__sysno,, "r" (__r0), "r" (__r1), "r" (__r2), "r" (__r3), "r" (__r4));
	return __ARM_PACK_SYSRET_DW();
}

__FORCELOCAL __ATTR_ARTIFICIAL __uint64_t (__LIBKCALL __arm_syscall6_dw)(__syscall_ulong_t __sysno,
                                                                         __syscall_ulong_t __arg0,
                                                                         __syscall_ulong_t __arg1,
                                                                         __syscall_ulong_t __arg2,
                                                                         __syscall_ulong_t __arg3,
                                                                         __syscall_ulong_t __arg4,
                                                                         __syscall_ulong_t __arg5) {
	__register_var(__syscall_ulong_t, __r0, "r0") = __arg0;
	__register_var(__syscall_ulong_t, __r1, "r1") = __arg1;
	__register_var(__syscall_ulong_t, __r2, "r2") = __arg2;
	__register_var(__syscall_ulong_t, __r3, "r3") = __arg3;
	__register_var(__syscall_ulong_t, __r4, "r4") = __arg4;
	__register_var(__syscall_ulong_t, __r5, "r5") = __arg5;
	__ARM_DO_SYSCALL_DW(__sysno,, "r" (__r0), "r" (__r1), "r" (__r2), "r" (__r3), "r" (__r4), "r" (__r5));
	return __ARM_PACK_SYSRET_DW();
}

__FORCELOCAL __ATTR_ARTIFICIAL __uint64_t (__LIBKCALL __arm_syscall7_dw)(__syscall_ulong_t __sysno,
                                                                         __syscall_ulong_t __arg0,
                                                                         __syscall_ulong_t __arg1,
                                                                         __syscall_ulong_t __arg2,
                                                                         __syscall_ulong_t __arg3,
                                                                         __syscall_ulong_t __arg4,
                                                                         __syscall_ulong_t __arg5,
                                                                         __syscall_ulong_t __arg6) {
	__register_var(__syscall_ulong_t, __r0, "r0") = __arg0;
	__register_var(__syscall_ulong_t, __r1, "r1") = __arg1;
	__register_var(__syscall_ulong_t, __r2, "r2") = __arg2;
	__register_var(__syscall_ulong_t, __r3, "r3") = __arg3;
	__register_var(__syscall_ulong_t, __r4, "r4") = __arg4;
	__register_var(__syscall_ulong_t, __r5, "r5") = __arg5;
	__register_var(__syscall_ulong_t, __r6, "r6") = __arg6;
	__ARM_DO_SYSCALL_DW(__sysno,, "r" (__r0), "r" (__r1), "r" (__r2), "r" (__r3), "r" (__r4), "r" (__r5), "r" (__r6));
	return __ARM_PACK_SYSRET_DW();
}


/* Flag for system call numbers to indicate execution in an exception-enabled context */
#define __ARM_XSYSCALL_FLAG 0x800000 /* Or'd with `sysno' */


#define __ARM_SYSCALL_ARG_PLACEHOLDER_1  ,
#define __ARM_SYSCALL_TAKE_SECOND_ARG_IMPL(x, val, ...) val
#define __ARM_SYSCALL_TAKE_SECOND_ARG(x) __ARM_SYSCALL_TAKE_SECOND_ARG_IMPL x
#define __ARM_SYSCALL_IS_DEFINED3(...) __ARM_SYSCALL_TAKE_SECOND_ARG((__VA_ARGS__ 1, 0))
#define __ARM_SYSCALL_IS_DEFINED2(x) __ARM_SYSCALL_IS_DEFINED3(__ARM_SYSCALL_ARG_PLACEHOLDER_##x)
#define __ARM_SYSCALL_IS_DEFINED(x)  __ARM_SYSCALL_IS_DEFINED2(x)
#define __ARM_SYSCALL_SELECT2_0(n)   __arm_syscall##n
#define __ARM_SYSCALL_SELECT2_1(n)   __arm_syscall##n##_dw
#define __ARM_SYSCALL_SELECT2(n, dw) __ARM_SYSCALL_SELECT2_##dw(n)
#define __ARM_SYSCALL_SELECT(n, dw)  __ARM_SYSCALL_SELECT2(n, dw)
#define __ARM_SYSCALL_SELECT0(n)     __ARM_SYSCALL_SELECT2_0(n)

#define __CDECLARE_SC(attr, Treturn, name, param, args)                                                                   \
	__FORCELOCAL __ATTR_ARTIFICIAL attr Treturn (__LIBKCALL sys_##name) param {                                           \
		return (Treturn)__ARM_SYSCALL_SELECT(__NRRC_##name,__ARM_SYSCALL_IS_DEFINED(__NRDW_##name))                       \
		                                     (__NR_##name __ARM_SYSCALL_COMMA_IF_ARGC(__NRRC_##name) __NRAP_##name args); \
	}
#define __CDECLARE_VOID_SC(attr, name, param, args)                                                        \
	__FORCELOCAL __ATTR_ARTIFICIAL attr void (__LIBKCALL sys_##name) param {                               \
		__ARM_SYSCALL_SELECT0(__NRRC_##name)                                                               \
		                      (__NR_##name __ARM_SYSCALL_COMMA_IF_ARGC(__NRRC_##name) __NRAP_##name args); \
		__ARM_SYSCALL_NORETURN_UNREACHABLE(__ARM_SYSCALL_IS_DEFINED(__NRNT_##name));                       \
	}
#define __CDECLARE_XSC(attr, Treturn, name, param, args)                                                     \
	__FORCELOCAL __ATTR_ARTIFICIAL attr Treturn (__LIBKCALL sys_X##name) param {                             \
		return (Treturn)__ARM_SYSCALL_SELECT(__NRRC_##name,__ARM_SYSCALL_IS_DEFINED(__NRDW_##name))          \
		                                    (__NR_##name | __ARM_XSYSCALL_FLAG                               \
		                                     __ARM_SYSCALL_COMMA_IF_ARGC(__NRRC_##name) __NRAP_##name args); \
	}
#define __CDECLARE_VOID_XSC(attr, name, param, args)                                           \
	__FORCELOCAL __ATTR_ARTIFICIAL attr void (__LIBKCALL sys_X##name) param {                  \
		__ARM_SYSCALL_SELECT0(__NRRC_##name)                                                   \
		                      (__NR_##name | __ARM_XSYSCALL_FLAG                               \
		                       __ARM_SYSCALL_COMMA_IF_ARGC(__NRRC_##name) __NRAP_##name args); \
		__ARM_SYSCALL_NORETURN_UNREACHABLE(__ARM_SYSCALL_IS_DEFINED(__NRNT_##name));           \
	}

__SYSDECL_END

#endif /* __CC__ */
#endif /* __WANT_INLINE_SYSCALLS */
#endif /* !__KERNEL__ */
#endif /* !__LCLINT__ */

#endif /* !_ARM_KOS_KOS_ASM_SYSCALL_H */
