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
#ifndef _ASM_OS_VFORK_H
#define _ASM_OS_VFORK_H 1

#include <__stdinc.h>

/*
 * #define __ARCH_HAVE_VFORK_SHARED_VM
 * >> Defined when the system implements the vfork(2) system call  such
 *    that  it isn't a  shallow alias for  fork(2), but rather executes
 *    the child process within the same VM as the parent process,  only
 *    that the parent will not resume execution before the child exits,
 *    or invokes one the exec(2) system calls.
 *
 * >> Knowing  this at  compile-time allows  for some  trickery where the
 *    child  process  will be  able to  write  back extended  exec status
 *    information (such  as the  exec-errno upon  failure) back  to  main
 *    memory, such that  once `vfork(2)' returns  to the parent  process,
 *    that parent can assume that (among everything else that is memory),
 *    its  `errno' was shared with the child process, such that (assuming
 *    that the error was  caused by exec(2)->errno=ENOENT), the  vfork(2)
 *    system call will return the child pid as usual, but errno was  left
 *    set to the same `ENOENT'.
 *
 * -> Knowing this, it becomes  significantly easier to implement  error
 *    propagation as the result of a failed exec() in situations such as
 *    system(3) or the spawn(3) family of functions (both POSIX and DOS)
 *
 *
 *
 * #define __ARCH_HAVE_SIGBLOCK_VFORK
 * >> POSIX signals send to a vfork'd child (except for  SIGSTOP/SIGKILL)
 *    are always masked, no matter what the vfork-process's actual signal
 *    mask says about the signal!
 * >> Linux  doesn't  do this,  but  handles the  problem  in user-space  in a
 *    way  that essentially  requires one  to _always_  _unconditionally_ do a
 *    `sigprocmask()' to  mask _all_  signals before  the vfork(),  such  that
 *    the  child process doesn't  accidentally run any  signal handlers in the
 *    context of the parent VM (which could result in an inconsistency between
 *    process  contexts such as  memory and open  file descriptors (where only
 *    the former is shared,  but a signal handler  of the vfork()'d child  may
 *    still run  the  handler,  thinking it's  the  parent)  and  consequently
 *    close a file handle that remains open for the parent).
 * >> On KOS this problem is handled  differently, such that a thread  with
 *    the `TASK_FVFORK' flag set is handled as though `this_kernel_sigmask'
 *    always were a signal mask identical to `sigmask_full'
 * >> As far as semantics go, you can think of `__ARCH_HAVE_SIGBLOCK_VFORK'
 *    like this:
 *    >> #ifdef __ARCH_HAVE_SIGBLOCK_VFORK
 *    >> #define vfork_with_sigmask() vfork()
 *    >> #else // __ARCH_HAVE_SIGBLOCK_VFORK
 *    >> // NOTES:
 *    >> //   - `RUN_AFTER_EXEC()' can't be implemented in user-space,
 *    >> //     but like the name would suggest, this is a piece of code
 *    >> //     that is run by the kernel after a successful exec(), but
 *    >> //     before the newly exec'd program first gains control.
 *    >> //   - Further calls to `sigprocmask()' won't actually be able
 *    >> //     to alter the effective mask set (which remains equal to
 *    >> //     `_nmask') until `RUN_AFTER_EXEC()' loads `_omask'.
 *    >> //     Instead, further call to `sigprocmask()' alter `_omask2',
 *    >> //     meaning further changes only become effective in case of
 *    >> //     a successful exec.
 *    >> //     Also note that this mechanism has been designed in such
 *    >> //     a manner that it correctly works with threads that make
 *    >> //     use of the userprocmask mechanism. (in this case, exec
 *    >> //     loads the vfork'd thread's userprocmask into the kernel
 *    >> //     sigmask, launching the new executable with the contents
 *    >> //     of the userprocmask at the time of the exec(). Then, when
 *    >> //     the parent awakes from waiting for the child in clone,
 *    >> //     it will write the copy it took of the userprocmask prior
 *    >> //     to staring the child, such that changes made to it before
 *    >> //     doing exec() or exit() don't remain visible in the parent)
 *    >> #define vfork_with_sigmask()                             \
 *    >>    ({                                                    \
 *    >>        sigset_t _nmask, _omask;                          \
 *    >>        pid_t _pid;                                       \
 *    >>        sigfillset(&_nmask);                              \
 *    >>        sigdelset(SIGKILL, &_nmask);                      \
 *    >>        sigdelset(SIGSTOP, &_nmask);                      \
 *    >>        sigprocmask(SIG_SETMASK, &_nmask, &_omask);       \
 *    >>        _pid = vfork();                                   \
 *    >>        if (_pid == 0) {                                  \
 *    >>            sigset_t _omask2 = _omask;                    \
 *    >>            RUN_AFTER_EXEC({                              \
 *    >>                sigprocmask(SIG_SETMASK, &_omask2, NULL); \
 *    >>            });                                           \
 *    >>        } else {                                          \
 *    >>            sigprocmask(SIG_SETMASK, &_omask, NULL);      \
 *    >>        }                                                 \
 *    >>        _pid;                                             \
 *    >>    })
 *    >> #endif // !__ARCH_HAVE_SIGBLOCK_VFORK
 *
 */

#if defined(__linux__)
#define __ARCH_HAVE_SHARED_VM_VFORK 1
#elif defined(__KOS__)
#define __ARCH_HAVE_SHARED_VM_VFORK 1 /* Implemented as of 2020-09-08T14:05 */
#define __ARCH_HAVE_SIGBLOCK_VFORK  1 /* Implemented as of 2020-09-11T17:58 */
#endif /* ... */

#endif /* !_ASM_OS_VFORK_H */
