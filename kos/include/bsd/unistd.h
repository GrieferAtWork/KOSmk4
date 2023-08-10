/* HASH CRC-32:0x2c41a242 */
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
/* (#) Portability: libbsd  (/include/bsd/unistd.h) */
/* (#) Portability: libc4/5 (/include/bsd/unistd.h) */
#ifndef _BSD_UNISTD_H
#define _BSD_UNISTD_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <unistd.h>
#include <fcntl.h> /* As seen in `libc4/5' */
#include <sys/stat.h> /* As seen in `libc4/5' */
#include <sys/time.h> /* As seen in `libc4/5' */

#ifdef __CC__
__SYSDECL_BEGIN

#if !defined(__getmode_defined) && defined(__CRT_HAVE_getmode)
#define __getmode_defined
/* >> setmode(3), getmode(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),__mode_t,__NOTHROW_NCX,getmode,(void const *__bbox, __mode_t __mode),(__bbox,__mode))
#endif /* !__getmode_defined && __CRT_HAVE_getmode */
#if !defined(__setmode_defined) && defined(__CRT_HAVE_setmode)
#define __setmode_defined
/* >> setmode(3), getmode(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),void *,__NOTHROW_NCX,setmode,(char const *__mode_str),(__mode_str))
#endif /* !__setmode_defined && __CRT_HAVE_setmode */
#ifndef __closefrom_defined
#define __closefrom_defined
#ifdef __CRT_HAVE_closefrom
/* >> closefrom(2)
 * Close all file descriptors with indices `>= lowfd' (s.a. `fcntl(F_CLOSEM)') */
__CDECLARE_VOID(,__NOTHROW_NCX,closefrom,(__fd_t __lowfd),(__lowfd))
#else /* __CRT_HAVE_closefrom */
#include <asm/os/fcntl.h>
#if ((defined(__CRT_HAVE_fcntl) || defined(__CRT_HAVE___fcntl) || defined(__CRT_HAVE___libc_fcntl)) && defined(__F_CLOSEM)) || defined(__CRT_HAVE_close_range)
#include <libc/local/unistd/closefrom.h>
/* >> closefrom(2)
 * Close all file descriptors with indices `>= lowfd' (s.a. `fcntl(F_CLOSEM)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(closefrom, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL closefrom)(__fd_t __lowfd) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(closefrom))(__lowfd); })
#else /* ((__CRT_HAVE_fcntl || __CRT_HAVE___fcntl || __CRT_HAVE___libc_fcntl) && __F_CLOSEM) || __CRT_HAVE_close_range */
#undef __closefrom_defined
#endif /* ((!__CRT_HAVE_fcntl && !__CRT_HAVE___fcntl && !__CRT_HAVE___libc_fcntl) || !__F_CLOSEM) && !__CRT_HAVE_close_range */
#endif /* !__CRT_HAVE_closefrom */
#endif /* !__closefrom_defined */
#ifndef __setproctitle_defined
#define __setproctitle_defined
#ifdef __CRT_HAVE_setproctitle
/* >> setproctitle(3)
 * Set the program comm name. S.a.:
 *  - pthread_setname_np(3)
 *  - prctl(PR_SET_NAME)
 *  - "/proc/self/comm" */
__LIBC __ATTR_IN(1) __ATTR_LIBC_PRINTF(1, 2) void __NOTHROW_NCX(__VLIBCCALL setproctitle)(char const *__format, ...) __CASMNAME_SAME("setproctitle");
#else /* __CRT_HAVE_setproctitle */
#include <linux/prctl.h>
#if ((defined(__CRT_HAVE_prctl) && defined(PR_SET_NAME)) || ((defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self) || defined(__CRT_HAVE_cthread_self)) && (defined(__CRT_HAVE_pthread_setname_np) || defined(__CRT_HAVE_pthread_set_name_np) || defined(__CRT_HAVE_cthread_set_name)))) && (defined(__TASK_COMM_LEN) || defined(__CRT_HAVE_vstrdupf) || defined(__CRT_HAVE_vasprintf) || ((defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free))))
#include <libc/local/stdlib/setproctitle.h>
/* >> setproctitle(3)
 * Set the program comm name. S.a.:
 *  - pthread_setname_np(3)
 *  - prctl(PR_SET_NAME)
 *  - "/proc/self/comm" */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(setproctitle, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_LIBC_PRINTF(1, 2) void __NOTHROW_NCX(__VLIBCCALL setproctitle)(char const *__format, ...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setproctitle))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define setproctitle(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setproctitle))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#else /* ((__CRT_HAVE_prctl && PR_SET_NAME) || ((__CRT_HAVE_pthread_self || __CRT_HAVE_thrd_current || __CRT_HAVE_thr_self || __CRT_HAVE_cthread_self) && (__CRT_HAVE_pthread_setname_np || __CRT_HAVE_pthread_set_name_np || __CRT_HAVE_cthread_set_name))) && (__TASK_COMM_LEN || __CRT_HAVE_vstrdupf || __CRT_HAVE_vasprintf || ((__CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free))) */
#undef __setproctitle_defined
#endif /* ((!__CRT_HAVE_prctl || !PR_SET_NAME) && ((!__CRT_HAVE_pthread_self && !__CRT_HAVE_thrd_current && !__CRT_HAVE_thr_self && !__CRT_HAVE_cthread_self) || (!__CRT_HAVE_pthread_setname_np && !__CRT_HAVE_pthread_set_name_np && !__CRT_HAVE_cthread_set_name))) || (!__TASK_COMM_LEN && !__CRT_HAVE_vstrdupf && !__CRT_HAVE_vasprintf && ((!__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_free && !__CRT_HAVE_cfree && !__CRT_HAVE___libc_free))) */
#endif /* !__CRT_HAVE_setproctitle */
#endif /* !__setproctitle_defined */
#ifndef __getpeereid_defined
#define __getpeereid_defined
#ifdef __CRT_HAVE_getpeereid
/* >> getpeereid(3)
 * Convenience wrapper for `getsockopt(sockfd, SOL_SOCKET, SO_PEERCRED)' */
__CDECLARE(__ATTR_FDARG(1) __ATTR_OUT(2) __ATTR_OUT(3),int,__NOTHROW_NCX,getpeereid,(__fd_t __sockfd, uid_t *__euid, gid_t *__egid),(__sockfd,__euid,__egid))
#else /* __CRT_HAVE_getpeereid */
#include <asm/os/socket.h>
#if defined(__CRT_HAVE_getsockopt) && defined(__SOL_SOCKET) && defined(__SO_PEERCRED)
#include <libc/local/unistd/getpeereid.h>
/* >> getpeereid(3)
 * Convenience wrapper for `getsockopt(sockfd, SOL_SOCKET, SO_PEERCRED)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(getpeereid, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) __ATTR_OUT(2) __ATTR_OUT(3) int __NOTHROW_NCX(__LIBCCALL getpeereid)(__fd_t __sockfd, uid_t *__euid, gid_t *__egid) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getpeereid))(__sockfd, __euid, __egid); })
#else /* __CRT_HAVE_getsockopt && __SOL_SOCKET && __SO_PEERCRED */
#undef __getpeereid_defined
#endif /* !__CRT_HAVE_getsockopt || !__SOL_SOCKET || !__SO_PEERCRED */
#endif /* !__CRT_HAVE_getpeereid */
#endif /* !__getpeereid_defined */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BSD_UNISTD_H */
