/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef GUARD_LIBC_USER_SYS_WAIT_C
#define GUARD_LIBC_USER_SYS_WAIT_C 1

#include "../api.h"
#include "sys.wait.h"

#include <kos/syscalls.h>
#include <syscall.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:wait,hash:CRC-32=0x51c2a33d]]]*/
/* Wait for any child process (same as `waitpid(-1, STAT_LOC, 0);') */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wait") pid_t
NOTHROW_RPC(LIBCCALL libc_wait)(__WAIT_STATUS stat_loc)
/*[[[body:wait]]]*/
{
	pid_t result;
#ifdef SYS_waitpid
	result = sys_waitpid(-1, (int32_t *)stat_loc, 0);
#elif defined(SYS_wait4_64)
	result = sys_wait4_64(-1, (int32_t *)stat_loc, 0, NULL);
#else /* ... */
	result = sys_wait4(-1, (int32_t *)stat_loc, 0, NULL);
#endif /* !... */
	return libc_seterrno_syserr(result);
}
/*[[[end:wait]]]*/

/*[[[head:waitpid,hash:CRC-32=0xb94e8d5d]]]*/
/* Wait for a child process:
 *  - `pid < -1':  Wait for any child process whose process group ID is `-PID'
 *  - `pid == -1': Wait for any child process
 *  - `pid == 0':  Wait for any child process whose process group ID is that of the caller
 *  - `pid > 0':   Wait for the child whose process ID is equal to `PID'
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.waitpid") pid_t
NOTHROW_RPC(LIBCCALL libc_waitpid)(pid_t pid,
                                   __WAIT_STATUS stat_loc,
                                   int options)
/*[[[body:waitpid]]]*/
{
	pid_t result;
#ifdef SYS_waitpid
	result = sys_waitpid(pid,
	                     (int32_t *)stat_loc,
	                     (syscall_ulong_t)(unsigned int)options);
#elif defined(SYS_wait4_64)
	result = sys_wait4_64(pid,
	                      (int32_t *)stat_loc,
	                      (syscall_ulong_t)(unsigned int)options,
	                      NULL);
#else /* ... */
	result = sys_wait4(pid,
	                   (int32_t *)stat_loc,
	                   (syscall_ulong_t)(unsigned int)options,
	                   NULL);
#endif /* !... */
	return libc_seterrno_syserr(result);
}
/*[[[end:waitpid]]]*/

/*[[[head:waitid,hash:CRC-32=0x98f3d30f]]]*/
/* @param options: At least one of `WEXITED|WSTOPPED|WCONTINUED', optionally or'd with `WNOHANG|WNOWAIT' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.waitid") int
NOTHROW_RPC(LIBCCALL libc_waitid)(idtype_t idtype,
                                  id_t id,
                                  siginfo_t *infop,
                                  int options)
/*[[[body:waitid]]]*/
{
	pid_t result;
#ifdef SYS_waitid64
	result = sys_waitid64(idtype, id, infop,
	                      (syscall_ulong_t)(unsigned int)options,
	                      NULL);
#else /* SYS_waitid64 */
	result = sys_waitid(idtype, id, infop,
	                    (syscall_ulong_t)(unsigned int)options,
	                    NULL);
#endif /* !SYS_waitid64 */
	return libc_seterrno_syserr(result);
}
/*[[[end:waitid]]]*/

/*[[[head:wait3,hash:CRC-32=0x9c75742b]]]*/
/* Same as `waitpid(-1,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wait3") pid_t
NOTHROW_RPC(LIBCCALL libc_wait3)(__WAIT_STATUS stat_loc,
                                 int options,
                                 struct rusage *usage)
/*[[[body:wait3]]]*/
{
	pid_t result;
	result = sys_wait4(-1,
	                   (int32_t *)stat_loc,
	                   (syscall_ulong_t)(unsigned int)options,
	                   usage);
	return libc_seterrno_syserr(result);
}
/*[[[end:wait3]]]*/

/*[[[head:wait4,hash:CRC-32=0x3269b18]]]*/
/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.wait4") pid_t
NOTHROW_RPC(LIBCCALL libc_wait4)(pid_t pid,
                                 __WAIT_STATUS stat_loc,
                                 int options,
                                 struct rusage *usage)
/*[[[body:wait4]]]*/
{
	pid_t result;
	result = sys_wait4(pid,
	                   (int32_t *)stat_loc,
	                   (syscall_ulong_t)(unsigned int)options,
	                   usage);
	return libc_seterrno_syserr(result);
}
/*[[[end:wait4]]]*/

/*[[[head:detach,hash:CRC-32=0x9da0d053]]]*/
/* >> detach(2)
 * Detach the descriptor of `PID' from the thread that
 * would have received a signal when it changes state,
 * as well as prevent the thread from turning into a
 * zombie once it dies.
 * For simplicity, think of it like this:
 *   - pthread_create()  -->  clone()
 *   - pthread_join()    -->  wait()
 *   - pthread_detach()  -->  detach()  // Linux's missing link, now implemented
 * A total of 4 special cases exists to alter the behavior of this function:
 *   - PID == 0 || PID == gettid():
 *     Detach the calling thread from the set of running children within
 *     its own process. Note however that when this is done by the main
 *     thread of the process, gettid() will equal getpid(), and the behavior
 *     will be different.
 *   - PID == getpid():
 *     Detach the calling process from its parent, essentially daemonizing
 *     the calling process the same way a double-fork would:
 *     >> if (fork() == 0) {
 *     >> 	if (fork() == 0) {
 *     >> 		// This is a daemonized process
 *     >> 		// aka. the parent process no longer knows
 *     >> 		// about us, and also can't wait(2) on us.
 *     >> 		...
 *     >> 	}
 *     >> 	exit(0);
 *     >> }
 *     Same as:
 *     >> if (fork() == 0) {
 *     >> 	detach(0); // or `detach(getpid())', since 0 --> gettid() and gettid() == getpid()
 *     >> 	// This is a daemonized process
 *     >> 	// aka. the parent process no longer knows
 *     >> 	// about us, and also can't wait(2) on us.
 *     >> 	...
 *     >> }
 *   - PID == -1:
 *     Detach all child processes/threads of the calling process, essentially
 *     turning its chain of children into a clean slate that no longer contains
 *     any wait(2)able child threads or processes.
 *     If no waitable children existed, `ECHILD' is set; else `0' is returned.
 * Before any of this is done, the thread referred to by `PID' is one of the following:
 *   - The leader of the process that called `fork()' or `clone()' without
 *    `CLONE_PARENT' to create the thread referred to by `PID'
 *   - The creator of the process containing a thread that called
 *    `clone()' with `CLONE_PARENT', which then created the thread
 *     referred to by `PID'.
 *   - Even if the thread doesn't deliver a signal upon it terminating,
 *     the process that would have received such a signal is still relevant.
 *   -> In other words: The thread `PID' must be one of your children,
 *                      or you had to have been assigned as its child.
 * If the calling thread isn't part of that process that will receive
 * the signal if the thread dies without being detached first, then
 * the call fails by throwing an `E_ILLEGAL_OPERATION'.
 * If the thread had already been detached, then the call fails by
 * throwing an `E_ILLEGAL_OPERATION' as well.
 * Upon success, the thread referred to by `PID' will clean up its own
 * PID descriptor without the need of anyone to wait() for it, a behavior
 * that linux implements using `CLONE_THREAD' (which you shouldn't use,
 * because it's flawed by design)
 * Once detached, any further use of PID results in a race condition
 * (which linux neglects to mention for `CLONE_THREAD'), because there
 * is no way of ensuring that PID still refers to the original thread,
 * as another thread may have been created using the same PID, after
 * the detached thread exited.
 * NOTE: If a thread is crated using clone() with `CLONE_DETACHED' set,
 *       it will behave effectively as though this function had already
 *       be called.
 * NOTE: If the thread already has terminated, detaching it will kill
 *       its zombie the same way wait() would.
 * NOTE: Passing ZERO(0) for `PID' will detach the calling thread.
 *       However, this operation fails if the calling thread isn't
 *       part of the same process as the parent process of the thread.
 *       In other words, the child of a fork() can't do this, and
 *       neither can the spawnee of clone(CLONE_THREAD|CLONE_PARENT),
 *       clone(0) or clone(CLONE_PARENT).
 * @errno: EPERM:               The calling process isn't the recipient of signals
 *                              delivered when `PID' changes state. This can either
 *                              be because `PID' has already been detached, or because
 *                              YOU CAN'T DETACH SOMEONE ELSE'S THREAD!
 *                              Another possibility is that the thread was already
 *                              detached, then exited, following which a new thread
 *                              got created and had been assigned the PID of your
 *                              ancient, no longer existent thread.
 * @errno: ECHILD:             `PID' was equal to `-1', but no waitable children existed
 * @throw: E_PROCESS_EXITED:    The process referred to by `PID' doesn't exist.
 *                              This could mean that it had already been detached
 *                              and exited, or that the `PID' is just invalid (which
 *                              would also be the case if it was valid at some point) */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.detach") int
NOTHROW_NCX(LIBCCALL libc_detach)(pid_t pid)
/*[[[body:detach]]]*/
{
	errno_t result;
	result = sys_detach(pid);
	return libc_seterrno_syserr(result);
}
/*[[[end:detach]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xcd64ad8f]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(wait, libc_wait);
DEFINE_PUBLIC_WEAK_ALIAS(__wait, libc_wait);
DEFINE_PUBLIC_WEAK_ALIAS(waitpid, libc_waitpid);
DEFINE_PUBLIC_WEAK_ALIAS(__waitpid, libc_waitpid);
DEFINE_PUBLIC_WEAK_ALIAS(waitid, libc_waitid);
DEFINE_PUBLIC_WEAK_ALIAS(wait3, libc_wait3);
DEFINE_PUBLIC_WEAK_ALIAS(wait4, libc_wait4);
DEFINE_PUBLIC_WEAK_ALIAS(detach, libc_detach);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_WAIT_C */
