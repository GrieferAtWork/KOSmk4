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
%(c_prefix){
/* (#) Portability: FreeBSD       (/sys/sys/eventfd.h) */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/eventfd.h) */
/* (#) Portability: diet libc     (/include/sys/eventfd.h) */
/* (#) Portability: musl libc     (/include/sys/eventfd.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(eventfd_t = __UINT64_TYPE__)]
%[default:section(".text.crt{|.dos}.sched.eventfd")]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <asm/os/eventfd.h> /* __EFD_* */
)]%[insert:prefix(
#include <bits/types.h>
)]%{

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

}

@@>> eventfd(2)
@@Construct a new kernel event object, and return a handle for it.
@@@param: count: The initial # of available events.
@@@param: flags: Set of `EFD_*'
@@@return: * : The newly constructed file handle.
[[wunused, decl_include("<features.h>", "<bits/types.h>")]]
$fd_t eventfd(__STDC_UINT_AS_SIZE_T count,
              __STDC_INT_AS_UINT_T flags);

@@>> eventfd_read(3)
@@Read the event counter, and (if not `O_NONBLOCK'), wait for an event to happen
[[cp, requires_function(read)]]
[[decl_include("<bits/types.h>"), impl_include("<libc/errno.h>")]]
int eventfd_read([[fdread]] $fd_t fd, eventfd_t *value) {
	ssize_t error;
	error = read(fd, value, sizeof(eventfd_t));
	if (error == sizeof(eventfd_t))
		return 0;
@@pp_ifdef EINVAL@@
	if (error >= 0)
		(void)libc_seterrno(EINVAL);
@@pp_endif@@
	return -1;
}

@@>> eventfd_write(3)
@@Increment the event counter
[[cp, requires_function(write)]]
[[decl_include("<bits/types.h>"), impl_include("<libc/errno.h>")]]
int eventfd_write([[fdwrite]] $fd_t fd, eventfd_t value) {
	ssize_t error;
	error = write(fd, &value, sizeof(eventfd_t));
	if (error == sizeof(eventfd_t))
		return 0;
@@pp_ifdef EINVAL@@
	if (error >= 0)
		(void)libc_seterrno(EINVAL);
@@pp_endif@@
	return -1;
}

%{
#endif /* __CC__ */

__SYSDECL_END

}
