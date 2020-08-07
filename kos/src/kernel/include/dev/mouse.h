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
#ifndef GUARD_KERNEL_INCLUDE_DEV_MOUSE_H
#define GUARD_KERNEL_INCLUDE_DEV_MOUSE_H 1

#include <kernel/compiler.h>

#include <dev/char.h>
#include <kernel/types.h>
#include <sched/signal.h>

#include <hybrid/sync/atomic-rwlock.h>

#include <kos/ioctl/mouse.h>

#include <stdbool.h>

DECL_BEGIN

#ifndef CONFIG_MOUSE_BUFFER_SIZE
#define CONFIG_MOUSE_BUFFER_SIZE 256
#endif /* !CONFIG_MOUSE_BUFFER_SIZE */


#ifdef __CC__

struct mouse_device;

union mouse_buffer_state {
	WEAK uintptr_t bs_word; /* Atomic control word. */
	struct {
		uintptr_half_t s_start; /* Offset to the first used packet */
		uintptr_half_t s_used;  /* Number of used packets. */
	} bs_state;
};

struct mouse_buffer {
	union mouse_buffer_state mb_bufstate; /* Buffer state */
	WEAK mouse_packet_t      mb_buffer[CONFIG_MOUSE_BUFFER_SIZE]; /* Buffer of unread mouse inputs. */
	struct sig               mb_avail;    /* Signal broadcast when the buffer becomes non-empty. */
};

struct mouse_state {
	s32 ms_abs_x;   /* Absolute position in X. */
	s32 ms_abs_y;   /* Absolute position in Y. */
	u32 ms_buttons; /* Currently held buttons. */
};

#define MOUSE_DEVICE_FLAG_NORMAL 0x0000 /* Normal mouse device flags. */
#define MOUSE_DEVICE_FLAG_GENABS 0x0001 /* Generate absolute mouse packets. */

struct mouse_device
#ifdef __cplusplus
	: character_device
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct character_device md_dev;   /* The underlying character device. */
#endif /* !__cplusplus */
	struct mouse_buffer     md_buf;   /* [lock(md_lock)] Mouse input buffer. */
	struct mouse_state      md_state; /* [lock(md_lock)] Current mouse state at the head of the buffer of pending inputs. */
	struct mouse_rect       md_rect;  /* [lock(md_lock)] Clip rectangle for absolute mouse positions. */
#ifndef CONFIG_NO_SMP
	struct atomic_rwlock    md_lock;  /* Preemption-lock for writing to `md_buf', `md_state' and `md_rect' */
#endif /* !CONFIG_NO_SMP */
	WEAK uintptr_t          md_flags; /* Mouse device flags (Set of `MOUSE_DEVICE_FLAG_*') */
};


#define character_device_isamouse(self)                    \
	((self)->cd_heapsize >= sizeof(struct mouse_device) && \
	 (self)->cd_type.ct_read == &mouse_device_read)

/* Initialize/finalize the given mouse device.
 * NOTE: Drivers that override the `ct_fini' operator of a given mouse
 *       must ensure that `mouse_device_fini()' is still invoked by their
 *       override.
 * NOTE: The following operators are intrinsically provided by mouse,
 *       get initialized by `mouse_device_init()', and should not be
 *       overwritten:
 *         - ct_read
 *         - ct_ioctl
 *         - ct_stat
 *         - ct_poll */
FUNDEF NOBLOCK void NOTHROW(KCALL mouse_device_init)(struct mouse_device *__restrict self);
#define mouse_device_fini(self) (void)0 /* No-op (for now) */


/* Mouse character device operators */
FUNDEF NONNULL((1)) size_t KCALL mouse_device_read(struct character_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF NONNULL((1)) syscall_slong_t KCALL mouse_device_ioctl(struct character_device *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
FUNDEF NONNULL((1)) void KCALL mouse_device_stat(struct character_device *__restrict self, USER CHECKED struct stat *result) THROWS(...);
FUNDEF NONNULL((1)) poll_mode_t KCALL mouse_device_poll(struct character_device *__restrict self, poll_mode_t what) THROWS(...);

/* Read packets from a given mouse device buffer. */
FUNDEF NOBLOCK mouse_packet_t NOTHROW(KCALL mouse_buffer_trygetpacket)(struct mouse_buffer *__restrict self);
FUNDEF mouse_packet_t KCALL mouse_buffer_getpacket(struct mouse_buffer *__restrict self) THROWS(E_WOULDBLOCK);

/* Generate mouse input packets
 * Note that when generating event packets, the motion
 * packets should always be created before other events */
FUNDEF bool KCALL mouse_device_motion(struct mouse_device *__restrict self, s32 relx, s32 rely);
FUNDEF bool KCALL mouse_device_moveto(struct mouse_device *__restrict self, s32 absx, s32 absy);
FUNDEF bool KCALL mouse_device_button(struct mouse_device *__restrict self, u32 mask, u32 flag);
FUNDEF bool KCALL mouse_device_vwheel(struct mouse_device *__restrict self, s32 lines);
FUNDEF bool KCALL mouse_device_hwheel(struct mouse_device *__restrict self, s32 rows);
FUNDEF bool KCALL mouse_device_button_ex(struct mouse_device *__restrict self, u32 mask, u32 flag, u32 xflg, u32 *__restrict pold_buttons, u32 *__restrict pnew_buttons);
FUNDEF NOBLOCK bool NOTHROW(KCALL mouse_device_motion_nopr)(struct mouse_device *__restrict self, s32 relx, s32 rely);
FUNDEF NOBLOCK bool NOTHROW(KCALL mouse_device_moveto_nopr)(struct mouse_device *__restrict self, s32 absx, s32 absy);
FUNDEF NOBLOCK bool NOTHROW(KCALL mouse_device_button_nopr)(struct mouse_device *__restrict self, u32 mask, u32 flag);
FUNDEF NOBLOCK bool NOTHROW(KCALL mouse_device_vwheel_nopr)(struct mouse_device *__restrict self, s32 lines);
FUNDEF NOBLOCK bool NOTHROW(KCALL mouse_device_hwheel_nopr)(struct mouse_device *__restrict self, s32 rows);
FUNDEF NOBLOCK bool NOTHROW(KCALL mouse_device_button_ex_nopr)(struct mouse_device *__restrict self, u32 mask, u32 flag, u32 xflg, u32 *__restrict pold_buttons, u32 *__restrict pnew_buttons);

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_DEV_MOUSE_H */
