/* HASH CRC-32:0x98d53eff */
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_EXCEPT_HANDLER_H
#define _KOS_EXCEPT_HANDLER_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <kos/anno.h>
#include <kos/except.h>
#include <kos/bits/except-handler.h>

#ifndef __EXCEPT_HANDLER_CC
#define __EXCEPT_HANDLER_CC  /* nothing */
#endif /* !__EXCEPT_HANDLER_CC */

/* >> set_exception_handler(2)
 * Interface for defining how the kernel propagates exceptions to user-space.
 * By default, kernel exceptions aren't propagated and are instead handled as
 * the process simply being terminated when the kernel tries to propagate an
 * exception (meaning that sys_X* system calls either terminate the process on
 * error, or propagate an exception by sending a POSIX signal, when such a signal
 * exists (s.a. `error_as_signal(3)'))
 * Using this interface, user-space can define a per-thread exception handler.
 *   - This handler is inherited by child processes/threads during `clone(2)' / `fork(2)'
 *   - When exec() is called, the handler is reset, meaning that applications
 *     always start with kernel exception handling disabled. (s.a. mode #1)
 * Note that some situations exist where the kernel may try to propagate an
 * exception into user-space, even when user-space didn't actually perform
 * a system call (though such exceptions are arch-specific):
 *   - Division by Zero                        (E_DIVIDE_BY_ZERO)
 *   - FPU Access failed to allocate registers (E_BADALLOC)
 *   - Integer overflow with check             (E_OVERFLOW)
 *   - Illegal/Privileged instruction executed (E_ILLEGAL_INSTRUCTION)
 *   - etc.
 * For compatibility with POSIX, (most of) these types of exceptions can be
 * handled in 1 of 2 ways:
 *   - By raising a POSIX signal in the affected thread.
 *     This is the default behavior, both before (mode #1) and after (mode #4)
 *     the exception handler initialization that is performed by `libc.so'
 *     (which simply defines its handler to be used for system call exceptions)
 *     In this mode, so-long as no sys_X* system calls are used, KOS behaves
 *     identically to POSIX guidelines, and no exceptions will ever be thrown
 *     without the user explicitly making use of exception-enabled functions,
 *     or marking their binary as `dlexceptaware(3)'
 *     -> This is the default when a standard-linked application's main()
 *        function is reached, and is further described by mode #4
 *   - By propagating the underlying kernel exception into user-space.
 *     In this mode, user-space gains the greatest amount of knowledge
 *     about the exception in question, but will be required to implement
 *     handling for exceptions, as well as include .eh_frame unwind information
 *     within their application, and be using C++ if the intend is to actually
 *     catch such an exception (KOS kernel exceptions use the same mechanism
 *     as C++, meaning that RAII and the like get handled correctly, though to
 *     make the intend of handling KOS exceptions more clear, as well as allow
 *     for possible compiler-specific extensions in the future, it is still
 *     recommended to use the `TRY' and `EXCEPT' macros from `<kos/except.h>'
 *     instead of using `try' and `catch (...)')
 *
 * In practice, you will usually encounter 1 of 4 modes, though KOS system
 * libraries often assume that either mode #3 or #4 is enabled, and in practice
 * there is little to no reason to ever concern yourself with any of this, as
 * libc will by default allow for the use of exceptions:
 *
 *  #1 KOS exceptions are fully disabled
 *     Behavior:
 *      - The kernel will send POSIX signals to the user application,
 *        and KOS operates in compliance with POSIX.
 *     Environment:
 *      - This mode is encountered just after the initial jump to
 *        user-space, after exec() was called.
 *      - As such, this environment is present for most of libdl.so,
 *        as well as within any __attribute__((constructor)) called
 *        before the one within libc.so that sets up mode #4
 *
 *  #2 KOS exceptions are enabled only for sys_X* system call invocations
 *     Behavior:
 *      - Same as mode #1, in that POSIX signals are send for all
 *        exceptions that are unrelated to sys_X* system calls
 *      - When a system call is invoked by sys_X*, any exception it
 *        may throw is propagated to user-space and re-thrown as a
 *        KOS exception (s.a. <kos/except.h>)
 *     Environment:
 *      - Something behaving like this mode is what you will encounter
 *        for most of your travels.
 *        That is, it is the mode that is emulated by libc with #4.
 *
 *  #3 Only use KOS exceptions
 *     Behavior:
 *      - Any exception raised by a sys_X* system call, or caused by
 *        other means that would normally provoke a signal to be raised
 *        will instead be handled via the user-space exception handler.
 *      - Note however that even in this mode, POSIX signals are _NOT_
 *        disabled in any sense of the word: things like SIGINT or other
 *        signals raised by kill(2) still behave as one would expect and
 *        are not affected by KOS exceptions
 *        Only signals that would normally be triggered directly by a
 *        program doing something questionable (e.g. SIGILL) are affected,
 *        and even then: are only propagated as KOS exceptions when thrown
 *        by the kernel itself.
 *     Environment:
 *      - This mode is enabled by default if an .exe file (rather than
 *        an ELF) is executed, so-as to allow for simpler integration
 *        with SEH
 *      - Additionally, this mode is often set at the start of main()
 *        in applications that were specifically written to run on KOS
 *        and take full advantage of its feature set, but don't wish to
 *        make use of #4 to prevent any possibility of ambiguity caused
 *        by posix signals not being too specific when it comes to signal
 *        causes.
 *
 *  #4 Use KOS exceptions only in modules that are `dlexceptaware(3)'
 *     Behavior:
 *      - The mode actually implemented as a sub-set of mode #3, with libc
 *        performing special analysis to determine how an exception should
 *        actually be handled based on the program state when it occurred:
 *         #1:    Check if the `EXCEPT_FINEXCEPT' flag is set
 *                If it is, move on to step #CORE
 *         #2:    Check if the base application is exception aware (see below)
 *                If it is, raise the exception like it would be in mode #3
 *         #3:    Check if the exception is E_EXIT_THREAD or E_EXIT_PROCESS.
 *                If it is, raise the exception like it would be in mode #3
 *         #4:    Save the currently active thread-local KOS exception, and
 *                set the `EXCEPT_FINEXCEPT' flag. (may be restored later)
 *                Then set the currently active thread-local KOS exception to
 *                the new one provided by the kernel.
 *         #5:    Unwind the stack using `error_unwind(3)' until an exception
 *                handler is found. - If no handler can be found before the stack
 *                is fully unwound, or if an error occurs during unwind (s.a.
 *                `UNWIND_*' from <libunwind/api.h>), move on to step #SIG
 *                Note that for this purpose, only catch-all handlers (i.e. `catch (...)')
 *                are considered viable handlers.
 *         #6:    If at least one handler was found, check if the associated module
 *                is exception aware (s.a. `dlexceptaware(3)')
 *                If the handler isn't apart of such a module, continue unwinding in
 *                search of a handler that is apart of a module matching this criteria
 *                  - To determine if such a handler exists, personality functions are invoked
 *                    like `fun(1, _UA_SEARCH_PHASE, _UEC_KERNKOS, <internal>, <context>)'
 *                    When `_URC_HANDLER_FOUND' is returned:
 *                        Check the module that contains the associated FDE
 *                    When `_URC_CONTINUE_UNWIND' or `_URC_NO_REASON' is returned:
 *                        Continue unwinding in search for a viable handler
 *                    When `_URC_FATAL_PHASE1_ERROR' or `_URC_FATAL_PHASE2_ERROR' is returned:
 *                        Move on to step #CORE (using `UNWIND_NO_FRAME')
 *                    When anything else is returned:
 *                        Move on to step #SIG
 *         #7:    If no handler apart of a dlexceptaware-module was found in step #6, move on to step #SIG
 *         #8:    Make sure that both `EXCEPT_FINEXCEPT' and `EXCEPT_FMAYSIGNAL' are set.
 *         #9:    Unwind to the closest found exception handler and resume execution there.
 *                Note that this unwinding will invoke personality functions a second time,
 *                which differs from the usual single-pass unwinding used for handling all
 *                other types of KOS exceptions.
 *         #SIG:  Restore the KOS exception saved in step #1.
 *                Translate the exception into a signal which is then raised
 *                within the calling thread (s.a. `error_as_signal(3)')
 *                If the exception cannot be translated into a signal,
 *                move on to step #CORE.
 *                NOTE: For this purpose, the `sys_raiseat()' system call exists.
 *         #CORE: Trigger a coredump to terminate the current application.
 *                NOTE: For this purpose, the `sys_coredump()' system call exists.
 *     Environment:
 *      - This is the actual mode that you will encounter for most of your travels.
 *      - It is set up during libc initialization and usually remains active
 *        for the entirety of the lifetime of any given application.
 *
 * Interaction with fork(2) / exec(2):
 *   - After a call to fork(2) or clone(2), the newly created thread/process
 *     will always inherit the exception handler of the calling thread (note
 *     that I said _thread_ right there, not process)
 *     Unlike other components inherited by clone(2), this component does
 *     not feature a specific CLONE_* flag, meaning that this step is always
 *     performed
 *   - After a call to exec(2), the calling process is reset to mode #1 (i.e.
 *     exclusively make use of posix signals), since a new memory image probably
 *     implies that user-space exception handlers are no longer present where
 *     they once where.
 */

__SYSDECL_BEGIN

#define EXCEPT_HANDLER_MODE_UNCHANGED   0x0000 /* Don't change the current mode */
#define EXCEPT_HANDLER_MODE_DISABLED    0x0001 /* MODE: Disable exception handlers (s.a. mode #1) */
#define EXCEPT_HANDLER_MODE_ENABLED     0x0002 /* MODE: Enable exception handlers for sys_X* system calls (s.a. mode #2)
                                                * When this flag is set, `set_exception_handler()' will set `HANDLER'
                                                * as the new exception handler called by the kernel. */
#define EXCEPT_HANDLER_MODE_SIGHAND     0x0003 /* MODE: Enable exceptions for non-syscall exceptions (s.a. mode #3) */
#define EXCEPT_HANDLER_MODE_MASK        0x000f /* Mask for the mode */
#define EXCEPT_HANDLER_FLAG_ONESHOT     0x2000 /* FLAG: Before execution of the handler is started, set the mode to `EXCEPT_HANDLER_MODE_DISABLED' */
#define EXCEPT_HANDLER_FLAG_SETHANDLER  0x4000 /* FLAG: Set the given `HANDLER' as the new exception handler called by the kernel. */
#define EXCEPT_HANDLER_FLAG_SETSTACK    0x8000 /* FLAG: Set the given `HANDLER_SP' as the stack used for handling exceptions. */


/* Special value for `__handler_sp': Re-use the previous user-space stack for storing exceptions */
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
#define EXCEPT_HANDLER_SP_CURRENT (__CCAST(void *)0)
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
#define EXCEPT_HANDLER_SP_CURRENT (__CCAST(void *)-1)
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */

#ifdef __CC__

#ifndef __except_handler_t_defined
#define __except_handler_t_defined 1
/* Prototype for a low-level user-space exception handler.
 * Note that the exact prototype may differ between architectures, as
 * well as the calling convention not always being the same, either.
 * The passed pointers will point to structures stored on a dedicated
 * exception handler stack, or (by default) on the stack of the thread
 * that caused the exception.
 * In either case, it will be that same stack that is set as active when
 * the exception handler itself gets invoked.
 * Other caveats include the fact that the expected behavior of the
 * function by differ based on other flags passed to `set_exception_handler()' */
typedef __except_handler_t except_handler_t;
#endif /* !__except_handler_t_defined */

/* Set the exception handler mode for the calling thread.
 * Examples:
 *     Set mode #1: set_exception_handler(EXCEPT_HANDLER_MODE_DISABLED, NULL, NULL)
 *     Set mode #2: set_exception_handler(EXCEPT_HANDLER_MODE_ENABLED | EXCEPT_HANDLER_FLAG_SETHANDLER, &except_handler3, NULL)
 *     Set mode #3: set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND | EXCEPT_HANDLER_FLAG_SETHANDLER, &except_handler3, NULL)
 *     Set mode #4: set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND | EXCEPT_HANDLER_FLAG_SETHANDLER, &except_handler4, NULL)
 * WARNING: Many system libraries assume that either mode #3 or #4 is enabled,
 *          as other modes may not allow for exceptions such as E_SEGFAULT to
 *          be handled using the TRY-EXCEPT model.
 *          Examples for these include: `libinstrlen:instruction_trysucc()'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
__CDECLARE_OPT(,int,__NOTHROW,set_exception_handler,(unsigned int __mode, except_handler_t __handler, void *__handler_sp),(__mode,__handler,__handler_sp))
/* Get the current exception handler mode for the calling thread.
 * @param: PMODE:       When non-NULL, store the current mode, which is encoded as:
 *                       - One of `EXCEPT_HANDLER_MODE_(DISABLED|ENABLED|SIGHAND)'
 *                       - Or'd with a set of `EXCEPT_HANDLER_FLAG_(ONESHOT|SETHANDLER|SETSTACK)'
 * @param: PHANDLER:    The address of the user-space exception handler.
 *                      Note that when no handler has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETHANDLER)'),
 *                      then this pointer is set to `NULL'.
 * @param: PHANDLER_SP: The starting address of the user-space exception handler stack.
 *                      Note that when no stack has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETSTACK)'),
 *                      or when the stack was defined to re-use the previous stack,
 *                      then this pointer is set to `EXCEPT_HANDLER_SP_CURRENT'.
 * @return: 0 :         Success.
 * @return: -1:EFAULT:  One of the given pointers is non-NULL and faulty */
__CDECLARE_OPT(,int,__NOTHROW_NCX,get_exception_handler,(unsigned int *__pmode, except_handler_t *__phandler, void **__phandler_sp),(__pmode,__phandler,__phandler_sp))
#ifdef __CRT_HAVE_except_handler3
/* Mode #2 / #3 exception handler (see description above) */
__LIBC __ATTR_NORETURN void (__EXCEPT_HANDLER_CC except_handler3)(error_register_state_t *__restrict __state, struct exception_data *__restrict __error) __THROWS(...) __CASMNAME_SAME("except_handler3");
#endif /* __CRT_HAVE_except_handler3 */
#ifdef __CRT_HAVE_except_handler4
/* Mode #4 exception handler (see description above) */
__LIBC __ATTR_NORETURN void (__EXCEPT_HANDLER_CC except_handler4)(error_register_state_t *__restrict __state, struct exception_data *__restrict __error) __THROWS(...) __CASMNAME_SAME("except_handler4");
#endif /* __CRT_HAVE_except_handler4 */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_KOS_EXCEPT_HANDLER_H */
