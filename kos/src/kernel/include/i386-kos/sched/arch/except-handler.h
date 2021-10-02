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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_EXCEPT_HANDLER_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_EXCEPT_HANDLER_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_RPC
#include <kernel/types.h>
#include <hybrid/host.h>

#ifdef __CC__
DECL_BEGIN

/* Arch-specific function:
 * Try to invoke the user-space exception handler for `except_data'
 * WARNING: Because this function writes to the user-space stack,
 *          it  is  capable of  throwing an  `E_SEGFAULT' itself.
 * @param: state:   The user-space CPU state (note that `icpustate_isuser(state)' is assumed!)
 * @param: sc_info: When  non-NULL, information about  the system call  that caused the exception.
 *                  Otherwise, if this argument is `NULL', the exception was caused by user-space,
 *                  such as a user-space program causing an `E_SEGFAULT', as opposed to the kernel
 *                  throwing an `E_FSERROR_FILE_NOT_FOUND'
 *            HINT: Additional information about how the system call was invoked can be
 *                  extracted from `sc_info->rsi_flags' (s.a. `<kos/asm/rpc-method.h>')
 * @return: NULL:   User-space does not define an exception handler.
 * @return: * :     The updated interrupt CPU state, modified to invoke the
 *                  user-space exception handler once user-space  execution
 *                  resumes. */
FUNDEF WUNUSED NONNULL((1, 3)) struct icpustate *FCALL
userexcept_callhandler(struct icpustate *__restrict state,
                       struct rpc_syscall_info const *sc_info,
                       struct exception_data const *__restrict except_data)
		THROWS(E_SEGFAULT);


/* Raise a posix signal in user-space for `siginfo'
 * @param: state:   The user-space CPU state (note that `icpustate_isuser(state)' is assumed!)
 * @param: sc_info: When  non-NULL,  information about  the system  call  that caused  the signal.
 *                  Otherwise,  if this argument  is `NULL', the signal  was caused by user-space,
 *                  such as a user-space program causing an `E_SEGFAULT', as opposed to the kernel
 *                  throwing an `E_FSERROR_FILE_NOT_FOUND'
 *            HINT: Additional information about how the system call was invoked can be extracted
 *                  from      `sc_info->rsi_flags'!      (s.a.      `<kos/asm/rpc-method.h>')
 * @param: siginfo: The signal that is being raised
 * @param: except_info: When non-NULL, `siginfo' was generated through `error_as_signal(&except_info->ei_data)',
 *                  and  if a coredump ends up being generated  as a result of the signal being
 *                  raised, that coredump will include information about `error_info()', rather
 *                  than the given `siginfo'
 * @return: * :     The updated interrupt CPU state, modified to invoke the
 *                  user-space signal  handler  once  user-space  execution
 *                  resumes. */
struct __siginfo_struct;
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 3)) struct icpustate *FCALL
x86_userexcept_raisesignal(struct icpustate *__restrict state,
                           struct rpc_syscall_info const *sc_info,
                           struct __siginfo_struct const *__restrict siginfo,
                           struct exception_info const *except_info DFL(__NULLPTR));

/* Helper function for  `x86_userexcept_raisesignal()' that  may be  used
 * to raise the appropriate POSIX signal for the currently set exception.
 * @return: NULL: The current exception cannot be translated into a posix signal.
 * @return: * :     The updated interrupt CPU state, modified to invoke the
 *                  user-space signal  handler  once  user-space  execution
 *                  resumes. */
FUNDEF WUNUSED NONNULL((1, 3)) struct icpustate *FCALL
x86_userexcept_raisesignal_from_exception(struct icpustate *__restrict state,
                                          struct rpc_syscall_info const *sc_info,
                                          struct exception_info const *__restrict except_info);

/* Arch-specific function:
 * Translate the current exception into an errno and set that errno
 * as the return value of  the system call described by  `sc_info'. */
FUNDEF NOBLOCK WUNUSED NONNULL((1, 2, 3)) struct icpustate *
NOTHROW(FCALL userexcept_seterrno)(struct icpustate *__restrict state,
                                   struct rpc_syscall_info const *__restrict sc_info,
                                   struct exception_data const *__restrict except_data);


/* Propagate the currently  thrown exception  into user-space, using  either the  user-space
 * exception handler, by raising  a POSIX signal,  or by translating  the exception into  an
 * E* error code in  the event of a  system call with exceptions  disabled (on x86,  except-
 * enabled is usually controlled by the CF bit, however this function takes that information
 * from the `RPC_SYSCALL_INFO_FEXCEPT' bit in `sc_info->rsi_flags'). */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(FCALL x86_userexcept_propagate)(struct icpustate *__restrict state,
                                        struct rpc_syscall_info const *sc_info);


/* Given a user-space UCPUSTATE, load that state into the active IRET tail, whilst
 * accounting for additional user-space RPC redirection, before serving user-level
 * RPC functions, and finally propagating the then set exception (if one still is)
 * into user-space with the help of `x86_userexcept_propagate()'.
 * Afterwards, load  the updated  icpustate at  the base  of the  calling thread's  stack,
 * and finally fully unwind into user-space by use of `x86_userexcept_unwind_interrupt()'.
 * NOTE: This is the function that should be called by the personality functions of
 *       custom system  call  handlers  that also  reset  the  kernel-space  stack. */
FUNDEF ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL x86_userexcept_unwind)(struct ucpustate *__restrict state,
                                     struct rpc_syscall_info const *sc_info);

/* Same  as  `x86_userexcept_unwind()',  however  the  caller  has  already  done  the work
 * of constructing a `struct icpustate *' at the base of the current thread's kernel stack. */
FUNDEF ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL x86_userexcept_unwind_i)(struct icpustate *__restrict state,
                                       struct rpc_syscall_info const *sc_info);

/* Unwind the currently set exception through an interrupt.
 * If   the  interrupt  leads   into  user-space,  service   user-space  RPC  functions  before
 * checking  if  the   exception  is   (still)  set  by   looking  at   `error_code() != E_OK'.
 * If the exception is still set at that point, propagate it using `x86_userexcept_propagate()'
 * If  the  exception  was  cleared,  continue  unwinding  into  user-space  the  normal   way.
 * If  the interrupt leads  into kernel-space, invoke  the unwinding machinery unconditionally,
 * even when `error_code() == E_OK' (this is required to correctly handle the case of unwinding
 * an interrupt after an  exception was propagated  into user-space, before  an RPC caused  the
 * kernel's IRET tail to be re-directed once again) */
FUNDEF ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL x86_userexcept_unwind_interrupt)(struct icpustate *__restrict state);

/* Same as `x86_userexcept_unwind_interrupt()', but `struct icpustate *state'
 * was already loaded into the `%esp' / `%rsp' register. */
#ifdef __x86_64__
FUNDEF ATTR_NORETURN void NOTHROW(ASMCALL x86_userexcept_unwind_interrupt_rsp)(void);
#else /* __x86_64__ */
FUNDEF ATTR_NORETURN void NOTHROW(ASMCALL x86_userexcept_unwind_interrupt_esp)(void);
#endif /* !__x86_64__ */

/* Function for the sub-branch of `x86_userexcept_unwind_interrupt_esp()'
 * that  assumes   that   the   target  is   located   in   kernel-space. */
#ifdef __x86_64__
FUNDEF ATTR_NORETURN void NOTHROW(ASMCALL x86_userexcept_unwind_interrupt_kernel_rsp)(void);
#else /* __x86_64__ */
FUNDEF ATTR_NORETURN void NOTHROW(ASMCALL x86_userexcept_unwind_interrupt_kernel_esp)(void);
#endif /* !__x86_64__ */



DECL_END
#endif /* __CC__ */
#endif /* !CONFIG_USE_NEW_RPC */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_EXCEPT_HANDLER_H */
