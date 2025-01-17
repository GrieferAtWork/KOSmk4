/* HASH CRC-32:0x52ed8797 */
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
/* (#) Portability: FreeBSD       (/sys/sys/eventfd.h) */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/eventfd.h) */
/* (#) Portability: diet libc     (/include/sys/eventfd.h) */
/* (#) Portability: musl libc     (/include/sys/eventfd.h) */
#ifndef _SYS_EVENTFD_H
#define _SYS_EVENTFD_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/os/eventfd.h> /* __EFD_* */
#include <bits/types.h>

#ifdef __USE_GLIBC_BLOAT
#include <stdint.h>
#endif /* __USE_GLIBC_BLOAT */

__SYSDECL_BEGIN

/* Flags for `eventfd()'. */
#if ((!defined(EFD_SEMAPHORE) && defined(__EFD_SEMAPHORE)) || \
     (!defined(EFD_NONBLOCK) && defined(__EFD_NONBLOCK)) ||   \
     (!defined(EFD_CLOEXEC) && defined(__EFD_CLOEXEC)) ||     \
     (!defined(EFD_CLOFORK) && defined(__EFD_CLOFORK)))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#if !defined(EFD_SEMAPHORE) && defined(__EFD_SEMAPHORE)
	EFD_SEMAPHORE = __EFD_SEMAPHORE, /* Create a semaphore */
#endif /* !EFD_SEMAPHORE && __EFD_SEMAPHORE */
#if !defined(EFD_NONBLOCK) && defined(__EFD_NONBLOCK)
	EFD_NONBLOCK  = __EFD_NONBLOCK,  /* Set the IO_NONBLOCK flag */
#endif /* !EFD_NONBLOCK && __EFD_NONBLOCK */
#if !defined(EFD_CLOEXEC) && defined(__EFD_CLOEXEC)
	EFD_CLOEXEC   = __EFD_CLOEXEC,   /* Set the IO_CLOEXEC flag */
#endif /* !EFD_CLOEXEC && __EFD_CLOEXEC */
#if !defined(EFD_CLOFORK) && defined(__EFD_CLOFORK)
	EFD_CLOFORK   = __EFD_CLOFORK,   /* Set the IO_CLOFORK flag */
#endif /* !EFD_CLOFORK && __EFD_CLOFORK */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#if !defined(EFD_SEMAPHORE) && defined(__EFD_SEMAPHORE)
#define EFD_SEMAPHORE EFD_SEMAPHORE /* Create a semaphore */
#endif /* !EFD_SEMAPHORE && __EFD_SEMAPHORE */
#if !defined(EFD_NONBLOCK) && defined(__EFD_NONBLOCK)
#define EFD_NONBLOCK  EFD_NONBLOCK  /* Set the IO_NONBLOCK flag */
#endif /* !EFD_NONBLOCK && __EFD_NONBLOCK */
#if !defined(EFD_CLOEXEC) && defined(__EFD_CLOEXEC)
#define EFD_CLOEXEC   EFD_CLOEXEC   /* Set the IO_CLOEXEC flag */
#endif /* !EFD_CLOEXEC && __EFD_CLOEXEC */
#if !defined(EFD_CLOFORK) && defined(__EFD_CLOFORK)
#define EFD_CLOFORK   EFD_CLOFORK   /* Set the IO_CLOFORK flag */
#endif /* !EFD_CLOFORK && __EFD_CLOFORK */
#else /* __COMPILER_PREFERR_ENUMS */
#if !defined(EFD_SEMAPHORE) && defined(__EFD_SEMAPHORE)
#define EFD_SEMAPHORE __EFD_SEMAPHORE /* Create a semaphore */
#endif /* !EFD_SEMAPHORE && __EFD_SEMAPHORE */
#if !defined(EFD_NONBLOCK) && defined(__EFD_NONBLOCK)
#define EFD_NONBLOCK  __EFD_NONBLOCK  /* Set the IO_NONBLOCK flag */
#endif /* !EFD_NONBLOCK && __EFD_NONBLOCK */
#if !defined(EFD_CLOEXEC) && defined(__EFD_CLOEXEC)
#define EFD_CLOEXEC   __EFD_CLOEXEC   /* Set the IO_CLOEXEC flag */
#endif /* !EFD_CLOEXEC && __EFD_CLOEXEC */
#if !defined(EFD_CLOFORK) && defined(__EFD_CLOFORK)
#define EFD_CLOFORK   __EFD_CLOFORK   /* Set the IO_CLOFORK flag */
#endif /* !EFD_CLOFORK && __EFD_CLOFORK */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __EFD_SEMAPHORE || __EFD_NONBLOCK || __EFD_CLOEXEC || __EFD_CLOFORK */


#ifdef __CC__

/* Type for event counter. */
#ifndef __eventfd_t_defined
#define __eventfd_t_defined
typedef __uint64_t eventfd_t;
#endif /* !__eventfd_t_defined */

/* >> eventfd(2)
 * Construct a new kernel event object, and return a handle for it.
 * @param: count: The initial # of available events.
 * @param: flags: Set of `EFD_*'
 * @return: * : The newly constructed file handle. */
__CDECLARE_OPT(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,eventfd,(__STDC_UINT_AS_SIZE_T __count, __STDC_INT_AS_UINT_T __flags),(__count,__flags))
#ifdef __CRT_HAVE_eventfd_read
/* >> eventfd_read(3)
 * Read the event counter, and (if not `O_NONBLOCK'), wait for an event to happen */
__CDECLARE(__ATTR_FDREAD(1),int,__NOTHROW_RPC,eventfd_read,(__fd_t __fd, eventfd_t *___value),(__fd,___value))
#elif defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)
#include <libc/local/sys.eventfd/eventfd_read.h>
/* >> eventfd_read(3)
 * Read the event counter, and (if not `O_NONBLOCK'), wait for an event to happen */
__NAMESPACE_LOCAL_USING_OR_IMPL(eventfd_read, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDREAD(1) int __NOTHROW_RPC(__LIBCCALL eventfd_read)(__fd_t __fd, eventfd_t *___value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(eventfd_read))(__fd, ___value); })
#endif /* ... */
#ifdef __CRT_HAVE_eventfd_write
/* >> eventfd_write(3)
 * Increment the event counter */
__CDECLARE(__ATTR_FDWRITE(1),int,__NOTHROW_RPC,eventfd_write,(__fd_t __fd, eventfd_t ___value),(__fd,___value))
#elif defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
#include <libc/local/sys.eventfd/eventfd_write.h>
/* >> eventfd_write(3)
 * Increment the event counter */
__NAMESPACE_LOCAL_USING_OR_IMPL(eventfd_write, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDWRITE(1) int __NOTHROW_RPC(__LIBCCALL eventfd_write)(__fd_t __fd, eventfd_t ___value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(eventfd_write))(__fd, ___value); })
#endif /* ... */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_EVENTFD_H */
