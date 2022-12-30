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
/* (#) Portability: Linux (/usr/include/linux/unistd.h) */
#ifndef _LINUX_UNISTD_H
#define _LINUX_UNISTD_H 1

#include <__stdinc.h>

#include <asm/unistd.h> /* __NR_* */

#include <libc/unistd.h> /* __libc_syscall() */

__DECL_BEGIN

#ifdef __CC__

#if defined(____libc_syscall_defined) && defined(____libc_syscall64_defined)
#define __LINUX_PRIVATE_SYSCALLX(returnType, name, params, args) \
	returnType(name) params {                                    \
		__STATIC_IF(sizeof(returnType) >= 8) {                   \
			return (returnType)__libc_syscall64 args;            \
		}                                                        \
		__STATIC_ELSE(sizeof(returnType) >= 8) {                 \
			return (returnType)__libc_syscall args;              \
		}                                                        \
	}
#elif defined(____libc_syscall_defined)
#define __LINUX_PRIVATE_SYSCALLX(returnType, name, params, args) \
	returnType(name) params {                                    \
		return (returnType)__libc_syscall args;                  \
	}
#else /* ... */
#define __LINUX_PRIVATE_SYSCALLX(returnType, name, params, args) \
	returnType(name) params; /* Cause a linker error if not defined elsewhere... */
#endif /* !... */

#define _syscall0(type, name)            \
	__LINUX_PRIVATE_SYSCALLX(type, name, \
	                         (void),     \
	                         (__NR_##name))
#define _syscall1(type, name, type1, arg1) \
	__LINUX_PRIVATE_SYSCALLX(type, name,   \
	                         (type1 arg1), \
	                         (__NR_##name, arg1))
#define _syscall2(type, name, type1, arg1, type2, arg2) \
	__LINUX_PRIVATE_SYSCALLX(type, name,                \
	                         (type1 arg1, type2 arg2),  \
	                         (__NR_##name, arg1, arg2))
#define _syscall3(type, name, type1, arg1, type2, arg2, type3, arg3) \
	__LINUX_PRIVATE_SYSCALLX(type, name,                             \
	                         (type1 arg1, type2 arg2, type3 arg3),   \
	                         (__NR_##name, arg1, arg2, arg3))
#define _syscall4(type, name, type1, arg1, type2, arg2, type3, arg3, type4, arg4) \
	__LINUX_PRIVATE_SYSCALLX(type, name,                                          \
	                         (type1 arg1, type2 arg2, type3 arg3, type4 arg4),    \
	                         (__NR_##name, arg1, arg2, arg3, arg4))
#define _syscall5(type, name, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5) \
	__LINUX_PRIVATE_SYSCALLX(type, name,                                                       \
	                         (type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5),     \
	                         (__NR_##name, arg1, arg2, arg3, arg4, arg5))
#define _syscall6(type, name, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6) \
	__LINUX_PRIVATE_SYSCALLX(type, name,                                                                    \
	                         (type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, type6 arg6),      \
	                         (__NR_##name, arg1, arg2, arg3, arg4, arg5, arg6))
#else /* __CC__ */

#define _syscall0(type, name)                                                                               /* nothing */
#define _syscall1(type, name, type1, arg1)                                                                  /* nothing */
#define _syscall2(type, name, type1, arg1, type2, arg2)                                                     /* nothing */
#define _syscall3(type, name, type1, arg1, type2, arg2, type3, arg3)                                        /* nothing */
#define _syscall4(type, name, type1, arg1, type2, arg2, type3, arg3, type4, arg4)                           /* nothing */
#define _syscall5(type, name, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5)              /* nothing */
#define _syscall6(type, name, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5, type6, arg6) /* nothing */

#endif /* !__CC__ */

__DECL_END

#endif /* !_LINUX_UNISTD_H */
