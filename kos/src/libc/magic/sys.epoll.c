/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/epoll.h) */
/* (#) Portability: diet libc     (/include/sys/epoll.h) */
/* (#) Portability: musl libc     (/include/sys/epoll.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.io.poll")]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <asm/os/epoll.h>
)]%[insert:prefix(
#include <bits/os/epoll.h>
)]%[insert:prefix(
#include <bits/os/sigset.h> /* struct __sigset_struct */
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#ifdef __USE_GLIBC
#include <sys/types.h>
#include <stdint.h>
#endif /* __USE_GLIBC */

__SYSDECL_BEGIN

/* Flags accepted by `epoll_create1(2)'. */
#if defined(__EPOLL_CLOEXEC) || defined(__EPOLL_CLOFORK)
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __EPOLL_CLOEXEC
	EPOLL_CLOEXEC = __EPOLL_CLOEXEC, /* Set the IO_CLOEXEC flag */
#endif /* __EPOLL_CLOEXEC */
#ifdef __EPOLL_CLOFORK
	EPOLL_CLOFORK = __EPOLL_CLOFORK, /* Set the IO_CLOFORK flag */
#endif /* __EPOLL_CLOFORK */

};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __EPOLL_CLOEXEC
#define EPOLL_CLOEXEC EPOLL_CLOEXEC /* Set the IO_CLOEXEC flag */
#endif /* __EPOLL_CLOEXEC */
#ifdef __EPOLL_CLOFORK
#define EPOLL_CLOFORK EPOLL_CLOFORK /* Set the IO_CLOFORK flag */
#endif /* __EPOLL_CLOFORK */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __EPOLL_CLOEXEC
#define EPOLL_CLOEXEC __EPOLL_CLOEXEC /* Set the IO_CLOEXEC flag */
#endif /* __EPOLL_CLOEXEC */
#ifdef __EPOLL_CLOFORK
#define EPOLL_CLOFORK __EPOLL_CLOFORK /* Set the IO_CLOFORK flag */
#endif /* __EPOLL_CLOFORK */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __EPOLL_CLOEXEC || __EPOLL_CLOFORK */

/* EPOLL_EVENTS */
#if (defined(__EPOLLIN) || defined(__EPOLLPRI) ||        \
     defined(__EPOLLOUT) || defined(__EPOLLERR) ||       \
     defined(__EPOLLHUP) || defined(__EPOLLRDNORM) ||    \
     defined(__EPOLLRDBAND) || defined(__EPOLLWRNORM) || \
     defined(__EPOLLWRBAND) || defined(__EPOLLMSG) ||    \
     defined(__EPOLLRDHUP) || defined(__EPOLLWAKEUP) ||  \
     defined(__EPOLLONESHOT) || defined(__EPOLLET))
/*[[[enum]]]*/
#ifdef __CC__
enum EPOLL_EVENTS {
#ifdef __EPOLLIN
	EPOLLIN      = __EPOLLIN,      /* There is data to read. (`read' & friends won't block when invoked) */
#endif /* __EPOLLIN */
#ifdef __EPOLLPRI
	EPOLLPRI     = __EPOLLPRI,     /* There is urgent data to read. */
#endif /* __EPOLLPRI */
#ifdef __EPOLLOUT
	EPOLLOUT     = __EPOLLOUT,     /* Writing now will not block. (`write' & friends won't block when invoked) */
#endif /* __EPOLLOUT */
#ifdef __EPOLLRDNORM
	EPOLLRDNORM  = __EPOLLRDNORM,  /* 100% identical to `POLLIN' (Normal data may be read). */
#endif /* __EPOLLRDNORM */
#ifdef __EPOLLRDBAND
	EPOLLRDBAND  = __EPOLLRDBAND,  /* Priority data may be read. */
#endif /* __EPOLLRDBAND */
#ifdef __EPOLLWRNORM
	EPOLLWRNORM  = __EPOLLWRNORM,  /* 100% identical to `POLLOUT' (Writing now will not block). */
#endif /* __EPOLLWRNORM */
#ifdef __EPOLLWRBAND
	EPOLLWRBAND  = __EPOLLWRBAND,  /* Priority data may be written. */
#endif /* __EPOLLWRBAND */
#ifdef __EPOLLMSG
	EPOLLMSG     = __EPOLLMSG,     /* Documented as unused */
#endif /* __EPOLLMSG */
#ifdef __EPOLLRDHUP
	EPOLLRDHUP   = __EPOLLRDHUP,   /* Socket peer closed connection, or shut down writing half of its connection */
#endif /* __EPOLLRDHUP */
#ifdef __EPOLLWAKEUP
	EPOLLWAKEUP  = __EPOLLWAKEUP,  /* Currently ignored */
#endif /* __EPOLLWAKEUP */
#ifdef __EPOLLONESHOT
	EPOLLONESHOT = __EPOLLONESHOT, /* Automatically stop monitoring the file descriptor once it's condition is met. */
#endif /* __EPOLLONESHOT */
#ifdef __EPOLLET
	EPOLLET      = __EPOLLET,      /* Enable edge-triggered monitoring */
#endif /* __EPOLLET */
/* Event types always implicitly polled for. */
#ifdef __EPOLLERR
	EPOLLERR     = __EPOLLERR,     /* Error condition. */
#endif /* __EPOLLERR */
#ifdef __EPOLLHUP
	EPOLLHUP     = __EPOLLHUP,     /* Hung up. (writes are no longer possible) */
#endif /* __EPOLLHUP */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __EPOLLIN
#define EPOLLIN      EPOLLIN      /* There is data to read. (`read' & friends won't block when invoked) */
#endif /* __EPOLLIN */
#ifdef __EPOLLPRI
#define EPOLLPRI     EPOLLPRI     /* There is urgent data to read. */
#endif /* __EPOLLPRI */
#ifdef __EPOLLOUT
#define EPOLLOUT     EPOLLOUT     /* Writing now will not block. (`write' & friends won't block when invoked) */
#endif /* __EPOLLOUT */
#ifdef __EPOLLRDNORM
#define EPOLLRDNORM  EPOLLRDNORM  /* 100% identical to `POLLIN' (Normal data may be read). */
#endif /* __EPOLLRDNORM */
#ifdef __EPOLLRDBAND
#define EPOLLRDBAND  EPOLLRDBAND  /* Priority data may be read. */
#endif /* __EPOLLRDBAND */
#ifdef __EPOLLWRNORM
#define EPOLLWRNORM  EPOLLWRNORM  /* 100% identical to `POLLOUT' (Writing now will not block). */
#endif /* __EPOLLWRNORM */
#ifdef __EPOLLWRBAND
#define EPOLLWRBAND  EPOLLWRBAND  /* Priority data may be written. */
#endif /* __EPOLLWRBAND */
#ifdef __EPOLLMSG
#define EPOLLMSG     EPOLLMSG     /* Documented as unused */
#endif /* __EPOLLMSG */
#ifdef __EPOLLRDHUP
#define EPOLLRDHUP   EPOLLRDHUP   /* Socket peer closed connection, or shut down writing half of its connection */
#endif /* __EPOLLRDHUP */
#ifdef __EPOLLWAKEUP
#define EPOLLWAKEUP  EPOLLWAKEUP  /* Currently ignored */
#endif /* __EPOLLWAKEUP */
#ifdef __EPOLLONESHOT
#define EPOLLONESHOT EPOLLONESHOT /* Automatically stop monitoring the file descriptor once it's condition is met. */
#endif /* __EPOLLONESHOT */
#ifdef __EPOLLET
#define EPOLLET      EPOLLET      /* Enable edge-triggered monitoring */
#endif /* __EPOLLET */
/* Event types always implicitly polled for. */
#ifdef __EPOLLERR
#define EPOLLERR     EPOLLERR     /* Error condition. */
#endif /* __EPOLLERR */
#ifdef __EPOLLHUP
#define EPOLLHUP     EPOLLHUP     /* Hung up. (writes are no longer possible) */
#endif /* __EPOLLHUP */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __EPOLLIN
#define EPOLLIN      __EPOLLIN      /* There is data to read. (`read' & friends won't block when invoked) */
#endif /* __EPOLLIN */
#ifdef __EPOLLPRI
#define EPOLLPRI     __EPOLLPRI     /* There is urgent data to read. */
#endif /* __EPOLLPRI */
#ifdef __EPOLLOUT
#define EPOLLOUT     __EPOLLOUT     /* Writing now will not block. (`write' & friends won't block when invoked) */
#endif /* __EPOLLOUT */
#ifdef __EPOLLRDNORM
#define EPOLLRDNORM  __EPOLLRDNORM  /* 100% identical to `POLLIN' (Normal data may be read). */
#endif /* __EPOLLRDNORM */
#ifdef __EPOLLRDBAND
#define EPOLLRDBAND  __EPOLLRDBAND  /* Priority data may be read. */
#endif /* __EPOLLRDBAND */
#ifdef __EPOLLWRNORM
#define EPOLLWRNORM  __EPOLLWRNORM  /* 100% identical to `POLLOUT' (Writing now will not block). */
#endif /* __EPOLLWRNORM */
#ifdef __EPOLLWRBAND
#define EPOLLWRBAND  __EPOLLWRBAND  /* Priority data may be written. */
#endif /* __EPOLLWRBAND */
#ifdef __EPOLLMSG
#define EPOLLMSG     __EPOLLMSG     /* Documented as unused */
#endif /* __EPOLLMSG */
#ifdef __EPOLLRDHUP
#define EPOLLRDHUP   __EPOLLRDHUP   /* Socket peer closed connection, or shut down writing half of its connection */
#endif /* __EPOLLRDHUP */
#ifdef __EPOLLWAKEUP
#define EPOLLWAKEUP  __EPOLLWAKEUP  /* Currently ignored */
#endif /* __EPOLLWAKEUP */
#ifdef __EPOLLONESHOT
#define EPOLLONESHOT __EPOLLONESHOT /* Automatically stop monitoring the file descriptor once it's condition is met. */
#endif /* __EPOLLONESHOT */
#ifdef __EPOLLET
#define EPOLLET      __EPOLLET      /* Enable edge-triggered monitoring */
#endif /* __EPOLLET */
/* Event types always implicitly polled for. */
#ifdef __EPOLLERR
#define EPOLLERR     __EPOLLERR     /* Error condition. */
#endif /* __EPOLLERR */
#ifdef __EPOLLHUP
#define EPOLLHUP     __EPOLLHUP     /* Hung up. (writes are no longer possible) */
#endif /* __EPOLLHUP */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */

/* Command codes for the `op' argument of `epoll_ctl(2)'. */
#if (defined(__EPOLL_CTL_ADD) || defined(__EPOLL_CTL_DEL) || \
     defined(__EPOLL_CTL_MOD))
/*[[[enum]]]*/
#ifdef __CC__
typedef enum __epoll_ctl {
#ifdef __EPOLL_CTL_ADD
	EPOLL_CTL_ADD = __EPOLL_CTL_ADD, /* Add a new file to-be monitored. */
#endif /* __EPOLL_CTL_ADD */
#ifdef __EPOLL_CTL_DEL
	EPOLL_CTL_DEL = __EPOLL_CTL_DEL, /* Stop monitoring a given file. */
#endif /* __EPOLL_CTL_DEL */
#ifdef __EPOLL_CTL_MOD
	EPOLL_CTL_MOD = __EPOLL_CTL_MOD  /* Change the `struct epoll_event' associated with a given file descriptor. */
#endif /* __EPOLL_CTL_MOD */
} __epoll_ctl_t;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __EPOLL_CTL_ADD
#define EPOLL_CTL_ADD EPOLL_CTL_ADD /* Add a new file to-be monitored. */
#endif /* __EPOLL_CTL_ADD */
#ifdef __EPOLL_CTL_DEL
#define EPOLL_CTL_DEL EPOLL_CTL_DEL /* Stop monitoring a given file. */
#endif /* __EPOLL_CTL_DEL */
#ifdef __EPOLL_CTL_MOD
#define EPOLL_CTL_MOD EPOLL_CTL_MOD /* Change the `struct epoll_event' associated with a given file descriptor. */
#endif /* __EPOLL_CTL_MOD */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __EPOLL_CTL_ADD
#define EPOLL_CTL_ADD __EPOLL_CTL_ADD /* Add a new file to-be monitored. */
#endif /* __EPOLL_CTL_ADD */
#ifdef __EPOLL_CTL_DEL
#define EPOLL_CTL_DEL __EPOLL_CTL_DEL /* Stop monitoring a given file. */
#endif /* __EPOLL_CTL_DEL */
#ifdef __EPOLL_CTL_MOD
#define EPOLL_CTL_MOD __EPOLL_CTL_MOD /* Change the `struct epoll_event' associated with a given file descriptor. */
#endif /* __EPOLL_CTL_MOD */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#elif defined(__CC__)
typedef int __epoll_ctl_t;
#endif /* ... */

#ifdef __CC__

typedef union epoll_data epoll_data_t;

#ifndef __sigset_t_defined
#define __sigset_t_defined 1
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

/*
 * PORTABILITY NOTES:
 *
 * The KOS implementation of epoll somewhat differs from the one provided by linux:
 *   >> epfd   = epoll_create();
 *   >> somefd = get_some_fd();
 *   >> epoll_ctl(epfd, EPOLL_CTL_MOD, somefd, { ... });
 *   >> close(somefd);
 *   Linux behavior:
 *    - `somefd' is automatically removed from `epfd'
 *   KOS behavior:
 *    - `somefd'  may  or  may  not   be  automatically  removed  from   `epfd'.
 *      The  actual internal behavior  depends on how  epfd stores its reference
 *      to `somefd'. For this, the KOS kernel has 2 cases: 1 where `epfd' stores
 *      a normal, full  reference to `somefd',  and one where  it stores a  weak
 *      reference (such that  closing and destroying  `somefd' is not  prevented
 *      from doing so by being apart of an epoll fd-set)
 *    - Which of  these 2  behaviors is  used  depends on  the internal  handle  type
 *      associated with `somefd' (one of `HANDLE_TYPE_*' from <kos/kernel/handle.h>),
 *      though  when  which behavior  is  used is  an  implementation detail  that is
 *      subject to change over time.
 *   Recommended behavior for maximum portability:
 *    - As linux documentation  already suggests, relying  on the  auto-removal
 *      behavior  of closing monitored  files isn't something  that ever has to
 *      be used and more often than not only introduces unnecessary complexity.
 *      Furthermore,  often this behavior  can't even be  done reliably since a
 *      monitored handled may get duplicated by any number of events (including
 *      fork(2) calls  made by  other threads).  As such,  explicitly  removing
 *      handles from the  associated epoll  descriptor is always  a good  idea.
 *
 */


}
%[define_replacement(__epoll_ctl_t = int)]


@@>> epoll_create(2)
@@Deprecated alias for `epoll_create1(0)' (the `size' argument is ignored)
@@@return: * : The newly created epoll control descriptor.
@@@return: -1: Error (s.a. `errno')
[[wunused, decl_include("<features.h>")]]
$fd_t epoll_create(__STDC_INT_AS_SIZE_T size);

@@>> epoll_create1(2)
@@Create a new epoll control descriptor which can be used for
@@monitoring of pollable events happening in registered files.
@@@param: flags: Set of `EPOLL_CLOEXEC | EPOLL_CLOFORK'
@@@return: * :   The newly created epoll control descriptor.
@@@return: -1:   Error (s.a. `errno')
@@@throw: E_INVALID_ARGUMENT_UNKNOWN_FLAG:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CREATE1_FLAGS: [...]
[[wunused, decl_include("<features.h>")]]
$fd_t epoll_create1(__STDC_INT_AS_UINT_T flags);


@@>> epoll_ctl(2)
@@Manipulate a given epoll controller `epfd', as previously returned by `epoll_create1(2)'
@@in order to register (`EPOLL_CTL_ADD'), remove (`EPOLL_CTL_DEL') or modify (`EPOLL_CTL_MOD')
@@the file descriptors being monitored
@@@param: op:    One of `EPOLL_CTL_ADD', `EPOLL_CTL_DEL' or `EPOLL_CTL_MOD'
@@@param: fd:    The file descriptor to add/remove/modify
@@@param: event: The new configuration for `fd' (ignored when `op' is `EPOLL_CTL_DEL')
@@@return: 0 :   Success
@@@return: -1:   [errno=EEXIST][op=EPOLL_CTL_ADD] The given `fd' (and its kernel object) has already been registered
@@@return: -1:   [errno=ENOENT][op=EPOLL_CTL_MOD|EPOLL_CTL_DEL] The given `fd' (and its kernel object) aren't registered
@@@return: -1:   Error (s.a. `errno')
@@@throw: E_ILLEGAL_REFERENCE_LOOP: The given `fd' is another epoll that either
@@                                  forms a loop with `epfd', or has too many nested.
@@@throw: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_EPOLL_CTL_OP: [...]
[[decl_include("<bits/epoll.h>")]]
int epoll_ctl($fd_t epfd, __epoll_ctl_t op,
              $fd_t fd, struct epoll_event *event);


@@>> epoll_wait(2)
@@Wait until at least one of the conditions monitored by `epfd' to be met.
@@@param: epfd:      The epoll controller on which to wait.
@@@param: events:    A buffer where the kernel can store information on the
@@                   events that actually took place.
@@@param: maxevents: The # of events that can be stored in `events' (must be >= 1)
@@@param: timeout:   The max amount of time (in milliseconds) before returning
@@                   in the case where no event occurred in the mean time. When
@@                   set to `-1', wait indefinitely
@@@return: >= 1:     The # of events that happened (written to the first `return'
@@                   items of `events')
@@@return: 0:        No events happened before `timeout' expired.
@@@return: -1:       Error (s.a. `errno')
[[cp, decl_include("<features.h>", "<bits/epoll.h>")]]
__STDC_INT_AS_SSIZE_T epoll_wait($fd_t epfd, [[nonnull]] struct epoll_event *events,
                                 __STDC_INT_AS_SIZE_T maxevents, int timeout);

@@>> epoll_pwait(2)
@@Same as `epoll_wait(2)', but change the calling thread's signal mask to `ss' while
@@waiting. Wait until at least one of the conditions monitored by `epfd' to be met.
@@@param: epfd:      The epoll controller on which to wait.
@@@param: events:    A buffer where the kernel can store information on the
@@                   events that actually took place.
@@@param: maxevents: The # of events that can be stored in `events' (must be >= 1)
@@@param: timeout:   The max amount of time (in milliseconds) before returning
@@                   in the case where no event occurred in the mean time. When
@@                   set to `-1', wait indefinitely
@@@param: ss:        The signal mask to apply while waiting for an event to happen.
@@@return: >= 1:     The # of events that happened (written to the first `return'
@@                   items of `events')
@@@return: 0:        No events happened before `timeout' expired.
@@@return: -1:       Error (s.a. `errno')
[[cp, decl_include("<features.h>", "<bits/epoll.h>")]]
__STDC_INT_AS_SSIZE_T epoll_pwait($fd_t epfd, [[nonnull]] struct epoll_event *events,
                                  __STDC_INT_AS_SIZE_T maxevents, int timeout,
                                  sigset_t const *ss);



%{
#endif /* __CC__ */

__SYSDECL_END

}
