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
#ifndef GUARD_KERNEL_INCLUDE_DEV_TTY_H
#define GUARD_KERNEL_INCLUDE_DEV_TTY_H 1

#include <kernel/compiler.h>

#include <dev/ttybase.h>
#include <misc/atomic-ref.h>
#include <sched/mutex.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

DECL_BEGIN

/* Terminal display drivers such as VGA should not implement the
 * tty interface. Instead, they should only need to implement
 * the normal character_device interface and provide a write-operator
 * that implements an ansi-compliant display port (using libansitty)
 *
 * An actual `struct tty' shouldn't actually be something that gets created
 * implicitly, but should be created explicitly (using the mktty() syscall) by
 * combining 2 arbitrary file descriptors, one providing a read-operator and
 * presumably being implemented by something like the ps2 driver, and the
 * other providing a write-operator and presumably being implemented by
 * something like the VGA driver.
 *
 * The actual `struct tty' then uses `struct terminal' to implement the TERMIOS
 * interface, forwarding/pulling data from its connected read/write object handles
 * as needed, while also encapsulating all of the required POSIX job control
 *
 * On-top of this, it would then also be possible to allow the tty objects to
 * react to the CTRL+ALT+F{1-NN} key combinations to switch between each other.
 *
 * The common base-class of this and PTY objects is `struct ttybase_device'
 */

#ifdef __CC__
struct tty_device_forward;
struct tty_device
#ifdef __cplusplus
    : ttybase_device
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct ttybase_device t_base;        /* The underlying base-tty */
#endif /* !__cplusplus */
	uintptr_half_t        t_ihandle_typ; /* [const] Input (keyboard) handle type (One of `HANDLE_TYPE_*') */
	uintptr_half_t        t_ohandle_typ; /* [const] Output (display) handle type (One of `HANDLE_TYPE_*') */
	REF void             *t_ihandle_ptr; /* [1..1][const] Input handle pointer. */
	REF void             *t_ohandle_ptr; /* [1..1][const] Output handle pointer. */
	/* [1..1][const] Input handle read operator callback. */
	size_t (KCALL *t_ihandle_read)(void *__restrict ptr, USER CHECKED void *dst,
	                               size_t num_bytes, iomode_t mode) THROWS(...);
	/* [1..1][const] Output handle write operator callback. */
	size_t (KCALL *t_ohandle_write)(void *__restrict ptr, USER CHECKED void const *src,
	                                size_t num_bytes, iomode_t mode) THROWS(...);
	XATOMIC_REF_STRUCT(struct tty_device_forward) t_forward; /* [0..1] TTY data forwarding thread. */
};

DEFINE_REFCOUNT_TYPE_SUBCLASS(tty_device, ttybase_device);

#define TTY_DEVICE_FORWARD(self) \
	((XATOMIC_REF(struct tty_device_forward) &)(self)->t_forward)

struct task;
struct rpc_entry;
struct tty_device_forward {
	/* Reading keyboard input only when read() is called doesn't work:
	 * With that design, things like CRTL+C wouldn't get recognized until
	 * the application which a user is trying to terminate actually
	 * reads from its TTY (which really defeats the point in the most
	 * common use of CTRL+C being to halt a program that has hung itself)
	 * The solution here is to designate a thread to continuously read from
	 * the TTY input handle (keyboard) and pass anything that it gets to
	 * `terminal_iwrite()' (with IO_NONBLOCK set, so that something like
	 * a filled up input buffer won't hinder processing of control combinations, either)
	 *
	 * Note however that there _has_ to be a way to terminate/restart this thread
	 * using some ioctl(), because after all: Any given keyboard input can only
	 * ever be read once before it disappears into the aether
	 * Also note that control over this thread also has to be made available to
	 * the VT (VirtualTerminal) controller to only have the active terminal read
	 * input data from the keyboard.
	 *
	 * Also note that we can't just have the keyboard driver directly forward its
	 * output data to the tty driver, since this would mean that `terminal_iwrite()'
	 * would have to be called in the context of an interrupt, meaning that a
	 * call to `t_ohandle_write()' would have to allow for asynchronous and re-entrant
	 * calls into itself (and even more general be able to work as NOEXCEPT, since any
	 * exception it could throw would have to be something that the keyboard interrupt
	 * handler could reasonably handle by itself, which doesn't work for things like
	 * E_INTERRUPT or E_WOULDBLOCK in case somwhere along the line `task_serve()' gets
	 * called) */
	WEAK refcnt_t                        tf_refcnt; /* Reference counter for this structure. */
	struct rpc_entry                    *tf_cancel; /* [0..1][lock(CLEAR_ONCE)] The RPC which can be used to terminate the thread. */
	REF struct task                     *tf_thread; /* [1..1][const] The thread used for forwarding input data. */
	XATOMIC_WEAKLYREF(struct tty_device) tf_device; /* [0..1][lock(CLEAR_ONCE)] The associated device. (set to NULL to terminate the forwarding thread) */
};
FUNDEF NOBLOCK void NOTHROW(KCALL tty_device_forward_destroy)(struct tty_device_forward *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct tty_device_forward, tf_refcnt, tty_device_forward_destroy)



#define ttybase_isatty(self) \
	((self)->cd_type.ct_poll == &tty_device_poll)
#define character_device_isatty(self) \
	((self)->cd_type.ct_poll == &tty_device_poll)
FUNDEF NONNULL((1)) poll_mode_t KCALL
tty_device_poll(struct character_device *__restrict self, poll_mode_t what) THROWS(...);

/* Create (but don't register) a new TTY device that connects the two given
 * handles, such that character-based keyboard input is taken from `ihandle_ptr',
 * and ansi-compliant display output is written to `ohandle_ptr'
 * For this purpose, special handling is done for certain handles:
 *   - ihandle_typ == HANDLE_TYPE_CHARACTERDEVICE && character_device_isakeyboard(ihandle_ptr):
 *     Input is read using `keyboard_device_getchar()', rather than `handle_read()'
 *   - ohandle_typ == HANDLE_TYPE_CHARACTERDEVICE && character_device_isanansitty(ohandle_ptr):
 *     `((struct ansitty_device *)ohandle_ptr)->at_tty' will be bound to the newly created tty device
 *     (s.a.. `return'), such that its output gets injected as `terminal_iwrite(&return->t_term, ...)'
 *     When the returned tty device is destroyed, this link gets severed automatically.
 * Upon success, the caller should:
 *   - Initialize `return->cd_name'
 *   - Register the device using one of:
 *      - `character_device_register(return, ...)'
 *      - `character_device_register_auto(return)'
 * NOTE: The TTY is created with data forwarding disabled. */
FUNDEF ATTR_RETNONNULL REF struct tty_device *KCALL
tty_device_alloc(uintptr_half_t ihandle_typ, void *ihandle_ptr,
                 uintptr_half_t ohandle_typ, void *ohandle_ptr)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

/* Start/Stop forwarding input handle data on the given TTY
 * Note that for any given input handle, only a single TTY should
 * ever be allowed to process data. - Allowing multiple TTYs to do
 * so could result in weakly undefined behavior as it would no
 * longer be clear who should actually receive data, causing a
 * soft race condition with the potential of data being scattered
 * between readers, or some random reader getting all of the data.
 * @return: true:  The FWD thread was started/stopped
 * @return: false: The FWD thread was already running/halted */
FUNDEF bool KCALL
tty_device_startfwd(struct tty_device *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC);
FUNDEF NOBLOCK bool
NOTHROW(KCALL tty_device_stopfwd)(struct tty_device *__restrict self);


#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_DEV_TTY_H */
