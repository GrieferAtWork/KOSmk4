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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_RT_EXCEPT_SYSCALL_H
#define GUARD_KERNEL_INCLUDE_KERNEL_RT_EXCEPT_SYSCALL_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/pertask.h>

#include <kos/except-handler.h>

/*[[[config CONFIG_HAVE_KERNEL_USERPROCMASK = true
 * Do we want to support `sys_set_userprocmask_address(2)'?
 * ]]]*/
#ifdef CONFIG_NO_KERNEL_USERPROCMASK
#undef CONFIG_HAVE_KERNEL_USERPROCMASK
#elif !defined(CONFIG_HAVE_KERNEL_USERPROCMASK)
#define CONFIG_HAVE_KERNEL_USERPROCMASK
#elif (-CONFIG_HAVE_KERNEL_USERPROCMASK - 1) == -1
#undef CONFIG_HAVE_KERNEL_USERPROCMASK
#define CONFIG_NO_KERNEL_USERPROCMASK
#endif /* ... */
/*[[[end]]]*/

#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
#include <kos/bits/userprocmask.h>

#if __OFFSET_USERPROCMASK_MYTID != 0
#error "Kernel code assumes that the TID address of a userprocmask is at offset=0"
#endif /* __OFFSET_USERPROCMASK_MYTID != 0 */
#endif /* CONFIG_HAVE_KERNEL_USERPROCMASK */

DECL_BEGIN


/* User-space exception handler descriptor. */
#ifdef __CC__
struct user_except_handler {
	uintptr_t                     ueh_mode;    /* Handler mode (One of `EXCEPT_HANDLER_MODE_*' + set of `EXCEPT_HANDLER_FLAG_*') */
	USER CHECKED except_handler_t ueh_handler; /* [valid_if(EXCEPT_HANDLER_FLAG_SETHANDLER)] Handler entry point */
	USER CHECKED void            *ueh_stack;   /* Handler stack  (or `EXCEPT_HANDLER_SP_CURRENT'  when not  set)
	                                            * NOTE: This pointer also doubles as the user-space sigaltstack! */
};

/* User-space exception handler mode for the current thread. */
DATDEF ATTR_PERTASK struct user_except_handler this_user_except_handler;

/* [0..1][lock(PRIVATE(THIS_TASK))]
 * User-space TID address used to implement functionality such as `pthread_join()'
 * When the associated thread exits, it will:
 *     >> pid_t *addr = PERTASK_GET(this_tid_address);
 *     >> if (addr) {
 *     >>     TRY {
 *     >>         *addr = 0;
 *     >>         mman_broadcastfutex(addr);
 *     >>     } EXCEPT {
 *     >>         if (!was_thrown(E_SEGFAULT) ||
 *     >>             (PERTASK_GET(this_exception_args.e_segfault.s_addr) != (uintptr_t)addr))
 *     >>             except_printf("...");
 *     >>     }
 *     >> }
 * When a new thread is created by clone(), the `CLONE_CHILD_CLEARTID' flag will  cause
 * the given `ctid' to be used as  the initial value for `this_tid_address', while  the
 * `CLONE_CHILD_SETTID' flag will cause the same address to be filled with the thread's
 * TID. */
DATDEF ATTR_PERTASK USER CHECKED pid_t *this_tid_address;




/* A system call and ABI for a user-space-controlled sigprocmask(). Using
 * this, user-space can  block/unblock signals without  having to do  any
 * system calls in the case where no signal arrived in the mean time, and
 * in  the case where a signal did arrive in the mean time, only 1 system
 * call (`sys_rpc_serve_sysret(2)') is required.
 *
 * Purpose:
 *    - A lot of kernel-space code makes use of `preemption_pushoff()' / `preemption_pop()'
 *      in order to ensure reentrancy for small sections of code. The equivalent user-space
 *      API for this is `sigprocmask()', however that function is anything but efficient in
 *      what  it  does, having  to  unconditionally employ  a  system call  when  used, and
 *      furthermore, that system call isn't the fastest one out there, either.
 *    - Solve this problem by designing a sigprocmask() function that can be  implemented
 *      entirely within the confines of user-space (only needing to perform a system call
 *      in the scenario where a (potentially) pending signal has become unmask)
 *
 * Notes:
 *    - The race condition caused  by the thread exiting,  and its reaper destroying  the
 *      backing memory of the userprocmask structure is solved by merging this new system
 *      call with the exiting `set_tid_address(2)' API, which already solves this problem
 *      by  requiring that the backing storage of the  TID address may only be freed once
 *      the kernel has written `0' to the TID address.
 *    - The `pm_sigsize' field must not be changed  by user-space. The kernel only guaranties  that
 *      it will check that field once (during the initial call to `sys_set_userprocmask_address()')
 *      If the field is altered at  any point after that, the  kernel will most likely just  ignore
 *      that change, continuing to work under the assumption of the original value.
 *    - When the kernel needs to modify a thread's signal mask, this is handled by:
 *       - In the case of calling a signal handler with a non-empty `sigaction::sa_mask',
 *         the kernel will load the `pm_sigmask'  pointer, and or' the pointed-to  signal
 *         set  with `sigaction::sa_mask'. Note  though that this  could only happen when
 *         `*pm_sigmask'  contained any 0-bits before, meaning that an all-1s signal mask
 *         will never be modified in this case.
 *       - A call to the actual `sys_sigprocmask(2)' system call (_NOT_ the libc variant
 *         described further below).
 *         In this case, rather than modifying its own, original signal mask, the kernel
 *         will  instead load the `pm_sigmask' pointer, and apply the same modifications
 *         it would have applied to the thread's internal (kernel-space) signal mask the
 *         signal set pointed-to by user-space. In this case, the system call doesn't do
 *         anything  that couldn't already be implemented in user-space, but still works
 *         as expected for the sake of compatibility.
 *
 * Semantics:
 *
 *    - When  using  `sys_set_userprocmask_address(2)', the  pointed-to `struct userprocmask'
 *      structure must have  thread-local storage  duration (that  is: may  not be  destroyed
 *      until _after_  the thread  that called  `sys_set_userprocmask_address()' has  exited,
 *      or until another call to `sys_set_userprocmask_address(2)' that assigned a  different
 *      address, or disabled USERPROCMASK by passing NULL, or a call to `set_tid_address(2)',
 *      which also disables USERPROCMASK)
 *
 *    - Kernel-space  checks for is-signal-masked are only ever  performed in the context of the
 *      thread in question itself.  When some other  thread wishes to  know if a  userprocmask'd
 *      thread  is masking some signal, they must simply  assume that the thread isn't, and send
 *      an RPC that should confirm  this for them. This is  required, due to the indirection  of
 *      the `pm_sigmask' field, which allows user-space to switch between signal mask  pointers,
 *      rather than having  to copy around  signal sets as  a whole. Also,  this is required  to
 *      ensure  that modifications made  by libc's sigprocmask() are  applied atomically for all
 *      signals, rather than individually for each signal (which would result in race conditions
 *      when  unmasking  one signal  triggers a  signal handler  that would  get executed  in an
 *      inconsistent context)
 *      As such, user-space making use of userprocmask somewhat increases the overhead needed
 *      for raising signals, however given that  raising signals in general aren't  something
 *      done  by programs  with the intend  of using them  for performance-critical purposes,
 *      this is completely acceptable.
 *
 *    - During a (successful) call to exec(), userprocmask-mode is disabled, the same way it
 *      would  also be disabled from user-space calling `sys_set_userprocmask_address(NULL)'
 *      As such, the final contents of `pm_sigmask'  from the thread calling exec() will  be
 *      loaded into the kernel's internal (legacy) sigprocmask buffer, such that the  signal
 *      mask  itself is inherited by a new process  the same way it would be if userprocmask
 *      hadn't been using by the original process.
 *
 *    - During a call to fork() or clone() (w/o CLONE_VM), the parent thread's
 *      TASK_FUSERPROCMASK    attribute    is    inherited    unconditionally.
 *
 *    - During a call to clone(CLONE_VM), where the parent is a userprocmask  thread,
 *      prior to clone() returning in either the parent or child, the parent thread's
 *      user-space `pm_sigmask' is copied into  the kernel-space buffer of the  child
 *      thread, before the child thread will start with TASK_FUSERPROCMASK=0.
 *
 *    - During a vfork(2),  where the parent  thread has the  TASK_FUSERPROCMASK
 *      attribute set, the parent's process's `pm_sigmask' will be copied into a
 *      temporary kernel-space buffer prior to starting the child thread.  Then,
 *      until the child thread indicates that it has successfully called exec(2)
 *      or   _Exit(2),  the  parent  thread's  TASK_FUSERPROCMASK  attribute  is
 *      cleared, and the internal kernel-space signal  mask is set to block  all
 *      signals (except `SIGKILL' and `SIGSTOP'), thus mirroring the behavior of
 *      vfork() without userprocmask.
 *      The child thread is started with the `TASK_FUSERPROCMASK' attribute  set,
 *      which will be cleared the normal way once the child performs a successful
 *      call  to either  exec(2) or _Exit(2),  at which pointer  the process will
 *      once again wake up.
 *      Back in the parent process, the kernel will now perform 2 copy operations:
 *       - memcpy(orig_pm_sigmask, &saved_sigmask, sizeof(sigset_t));
 *       - THIS_USERPROCMASK_POINTER->pm_sigmask = orig_pm_sigmask;
 *      Where `THIS_USERPROCMASK_POINTER' is the pointer that the parent thread originally
 *      passed  to  `sys_set_userprocmask_address()', `orig_pm_sigmask'  was the  value of
 *      `THIS_USERPROCMASK_POINTER->pm_sigmask'  prior to the child process being started,
 *      and `saved_sigmask' were  the contents  of `*orig_pm_sigmask' prior  to the  child
 *      process being started.
 *
 *    - During  a  vfork(2),  where  the  parent  thread  didn't  have  then `TASK_FUSERPROCMASK'
 *      attribute  set, but the child process performs a call to `sys_set_userprocmask_address()'
 *      before eventually performing a successful call to exec(2) or exit(2), the parent thread's
 *      TLS state (which at this point is assumed  to be shared with the child process) is  fixed
 *      up to indicate that `sys_set_userprocmask_address()' had yet to be called in its context.
 *      This is done by having the vfork child do `THIS_USERPROCMASK_POINTER->pm_sigmask = NULL',
 *      thus indicating to the parent thread that `sys_set_userprocmask_address(2)' wasn't called
 *      yet.
 *      For this purpose, the kernel  sets a thread flag `TASK_FUSERPROCMASK_AFTER_VFORK'  when
 *      a call `sys_set_userprocmask_address(<not-NULL>)' is performed by a thread that doesn't
 *      already  have the `TASK_FUSERPROCMASK'  attribute set, but  does have the `TASK_FVFORK'
 *      attribute set.
 *
 *
 * Example code:
 * >> sigset_t os, ns;
 * >> sigfillset(&ns);
 * >> sigprocmask(SIG_SETMASK, &ns, &os);   // preemption_pushoff()
 * >> ...
 * >> sigprocmask(SIG_SETMASK, &os, NULL);  // preemption_pop()
 *
 *
 * Implementation of libc's `sigprocmask()':
 * >> struct userprocmask {
 * >>     pid_t     pm_mytid;    // [const] TID of the thread (same as `set_tid_address(2)')
 * >>     size_t    pm_sigsize;  // [const] == sizeof(sigset_t)
 * >>     sigset_t *pm_sigmask;  // [KERNEL:READ|WRITE(1), USER:WRITE][0..1] Pointer to the current signal mask
 * >>                            // The kernel may or' this with another mask when a signal handler is invoked
 * >>                            // that contains a non-empty `sa_mask'.
 * >>                            // Set to `NULL' to indicate that `sys_set_userprocmask_address()' wasn't called, yet.
 * >>     uintptr_t pm_flags;    // [KERNEL:WRITE, USER:READWRITE] Set of `USERPROCMASK_FLAG_*'
 * >>     sigset_t  pm_pending;  // [KERNEL:WRITE, USER:READWRITE] Set of pending signals
 * >>                            // When a currently masked signal arrives, the kernel
 * >>                            // will set its associated bit to 1 within this set
 * >>     // === End of user-kernel-ABI (below is only used by libc!)
 * >>     sigset_t  pm_masks[2]; // Buffer for user-space signal masks
 * >> };
 * >>
 * >>
 * >> // New system calls
 * >>
 * >> // Register the address of the calling thread's userprocmask controller.
 * >> // This also initializes `*pm_sigmask' and `pm_pending', such that
 * >> // `*pm_sigmask' is filled with the current kernel-level signal mask,
 * >> // as would be returned by `sigprocmask(2)', while `pm_pending' is
 * >> // filled in with the equivalent of `sigpending(2)'
 * >> // Additionally, the address of `&mymask' is stored alongside other
 * >> // user-space TLS state pointers such as `set_tid_address(2)', and
 * >> // the kernel may read from `*(&mymask)->pm_sigmask', and write to
 * >> // `(&mymask)->pm_pending' (using atomic-or for the later) from this
 * >> // point forth.
 * >> // NOTE: Passing `NULL' for `ctl' disables userprocmask-mode, though
 * >> //       before this is done, the kernel will copy the `pm_sigmask'
 * >> //       of the previously set controller into its internal signal
 * >> //       mask. (i.e. the one used outside of userprocmask-mode)
 * >> // Note though that `pm_sigmask' is ignored for `SIGKILL' and `SIGSTOP'
 * >> // Note also that this function replaces `set_tid_address(2)', such that
 * >> // it negates a prior call to said function, while a future call to said
 * >> // function will disable userprocmask, similar to passing `NULL'
 * >> errno_t sys_set_userprocmask_address(struct userprocmask *ctl);
 * >>
 * >> // >> rpc_serve_sysret(2)
 * >> // Service asynchronous (posix-signal-style) RPCs before returning to user-space
 * >> // NOTE: Not a cancellation point, and only serves async RPCs!
 * >> // @return: 0 : Always, unconditionally returned.
 * >> [restart(dont)] sys_rpc_serve_sysret:() -> errno_t;
 * >>
 * >>
 * >> // Per-thread user-space signal mask controller
 * >> __thread struct userprocmask mymask;
 * >>
 * >> // Run during startup, or lazily on first call to `libc:sigprocmask()'
 * >> mymask.pm_sigsize = sizeof(sigset_t);
 * >> mymask.pm_sigmask = &mymask.pm_masks[0];
 * >> sys_set_userprocmask_address(&mymask);
 * >>
 * >> int sigprocmask(int how, sigset_t *ns, sigset_t *os) {
 * >>     sigset_t *oldset, *newset;
 * >>     oldset = mymask.pm_sigmask;
 * >>
 * >>     if (os)
 * >>         memcpy(os, oldset, sizeof(sigset_t));
 * >>     if (!ns)
 * >>         return 0;
 * >>
 * >>     // Select a storage location for the new mask
 * >>     newset = oldset + 1;
 * >>     if (newset != &mymask.pm_masks[0] &&
 * >>         newset != &mymask.pm_masks[1])
 * >>         newset = &mymask.pm_masks[0];
 * >>
 * >>     // Initialize a new signal mask from the old one, `how', and the new one
 * >>     init_sigset_for_sigprocmask(newset, how, oldset, ns);
 * >>
 * >>     // Atomically enable use of the new, updated mask
 * >>     // From this point forth, signals sent to our thread will be masked by `newset'
 * >>     ATOMIC_WRITE(mymask.pm_sigmask, newset);
 * >>     COMPILER_BARRIER();
 * >>
 * >>     // Optimization: If we know that no signal became unmasked, we don't
 * >>     //               have to search for any pending, unmasked signals!
 * >>     if (how == SIG_BLOCK)
 * >>         return 0;
 * >>
 * >>     // Optimization: If there are _any_ pending signals, the kernel sets this flag
 * >>     if (!(mymask.pm_flags & USERPROCMASK_FLAG_HASPENDING))
 * >>         return 0;
 * >>
 * >>     // Check if previously pending signals became available
 * >>     for (signo_t i = 1; i < NSIG; ++i) {
 * >>
 * >>         // HINT: Instead of testing each signal individually, this can be made
 * >>         //       faster by first checking for non-zero words in `pm_pending',
 * >>         //       which would test 32/64 signals at once, before checking if
 * >>         //       any of them are unmasked!
 * >>         if (sigismember(&mymask.pm_pending, i) && !sigismember(newset, i)) {
 * >>
 * >>             // Clear the set of pending signals (because the kernel won't do this)
 * >>             // Also note that there is no guaranty that the signal that became
 * >>             // avilable in the mean time is still available now. - The signal may
 * >>             // have been directed at our process as a whole, and another thread
 * >>             // may have already handled it.
 * >>             sigemptyset(&mymask.pm_pending);
 * >>             ATOMIC_AND(mymask.pm_flags, ~USERPROCMASK_FLAG_HASPENDING);
 * >>
 * >>             // Handle all async (== sysret) RPCs (and thus posix signals)
 * >>             sys_rpc_serve_sysret();
 * >>             break;
 * >>         }
 * >>     }
 * >>     return 0;
 * >> }
 *
 * Additionally, this allows libc to expose a pair of new, better-optimized  signal
 * mask  functions that can be used to directly  set the address of the used signal
 * mask, allowing a  program to pre-define/initialize  a number of  special-purpose
 * signal masks, which it can then switch to/from, with the only remaining overhead
 * being the checking for pending signals
 *
 * >> // New user-space function:
 * >> sigset_t *getsigmaskptr(void) {
 * >>     return mymask.pm_sigmask;
 * >> }
 * >>
 * >> // New user-space function:
 * >> sigset_t *setsigmaskptr(sigset_t *sigmaskptr) {
 * >>     sigset_t *result = mymask.pm_sigmask;
 * >>     mymask.pm_sigmask = sigmaskptr;
 * >>     if (mymask.pm_flags & USERPROCMASK_FLAG_HASPENDING) {
 * >>         for (signo_t i = 1; i < NSIG; ++i) {
 * >>             if (sigismember(&mymask.pm_pending, i) && !sigismember(sigmaskptr, i)) {
 * >>                 sigemptyset(&mymask.pm_pending);
 * >>                 sys_rpc_serve_sysret();
 * >>                 break;
 * >>             }
 * >>         }
 * >>     }
 * >>     return result;
 * >> }
 *
 * Example usage:
 * >> static sigset_t const fullmask = SIGSET_INIT_FULL;
 * >> void my_function_that_mustnt_get_interrupted(void);
 * >> void my_function(void) {
 * >>     sigset_t *oldset;
 * >>
 * >>     // Mask all signals
 * >>     // NOTE: `fullmask' can be const, since all of its bits are already 1,
 * >>     //       and the kernel will only ever write to the current mask in
 * >>     //       order to turn 0-bits into 1s (so no write would ever be done)
 * >>     // However, this also assumes that `my_function_that_mustnt_get_interrupted()'
 * >>     // doesn't include a call to `sys_sigprocmask(2)' (i.e. _NOT_ the library
 * >>     // variant), since such a call would also try to write to `fullmask'
 * >>     oldset = setsigmaskptr((sigset_t *)&fullmask); // preemption_pushoff()
 * >>
 * >>     my_function_that_mustnt_get_interrupted();
 * >>
 * >>     // Restore the old signal mask
 * >>     setsigmaskptr(oldset);                         // preemption_pop()
 * >> }
 */
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
/* [valid_if(THIS_TASK->t_flags & TASK_FUSERPROCMASK)][lock(PRIVATE(THIS_TASK))] */
DATDEF ATTR_PERTASK USER CHECKED struct userprocmask *
this_userprocmask_address ASMNAME("this_tid_address");
#endif /* CONFIG_HAVE_KERNEL_USERPROCMASK */



#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_RT_EXCEPT_SYSCALL_H */
