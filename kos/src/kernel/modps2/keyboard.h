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
#ifndef GUARD_MODPS2_KEYBOARD_H
#define GUARD_MODPS2_KEYBOARD_H 1

#include <kernel/compiler.h>

#include <dev/keyboard.h>
#include <kernel/types.h>

#include <hybrid/sched/atomic-rwlock.h>

#include <kos/sched/shared-lock.h>

#include "ps2.h"

DECL_BEGIN


enum {
	PS2_KEYBOARD_STATE_SS1,
	PS2_KEYBOARD_STATE_SS1_E0,
	PS2_KEYBOARD_STATE_SS1_E0_2A,
	PS2_KEYBOARD_STATE_SS1_E0_2A_E0,
	PS2_KEYBOARD_STATE_SS1_E0_B7,
	PS2_KEYBOARD_STATE_SS1_E0_B7_E0,
	PS2_KEYBOARD_STATE_SS1_E1,
	PS2_KEYBOARD_STATE_SS1_E1_1D,
	PS2_KEYBOARD_STATE_SS1_E1_1D_45,
	PS2_KEYBOARD_STATE_SS1_E1_1D_45_91,
	PS2_KEYBOARD_STATE_SS1_E1_1D_45_91_9D,

	PS2_KEYBOARD_STATE_SS2,
	PS2_KEYBOARD_STATE_SS2_E0,
	PS2_KEYBOARD_STATE_SS2_E0_12,
	PS2_KEYBOARD_STATE_SS2_E0_12_E0,
	PS2_KEYBOARD_STATE_SS2_E0_F0,
	PS2_KEYBOARD_STATE_SS2_E0_F0_7C,
	PS2_KEYBOARD_STATE_SS2_E0_F0_7C_E0,
	PS2_KEYBOARD_STATE_SS2_E0_F0_7C_E0_F0,
	PS2_KEYBOARD_STATE_SS2_E1,
	PS2_KEYBOARD_STATE_SS2_E1_14,
	PS2_KEYBOARD_STATE_SS2_E1_14_77,
	PS2_KEYBOARD_STATE_SS2_E1_14_77_E1,
	PS2_KEYBOARD_STATE_SS2_E1_14_77_E1_F0,
	PS2_KEYBOARD_STATE_SS2_E1_14_77_E1_F0_14,
	PS2_KEYBOARD_STATE_SS2_E1_14_77_E1_F0_14_F0,
	PS2_KEYBOARD_STATE_SS2_F0,

	PS2_KEYBOARD_STATE_SS3,
	PS2_KEYBOARD_STATE_SS3_F0,
};


#define PS2_KEYBOARD_ERROR_ACK    0x01 /* Received `0xfa' */
#define PS2_KEYBOARD_ERROR_RESEND 0x02 /* Received `0xfe' */

struct ps2_keyboard
#ifdef __cplusplus
    : kbddev
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct kbddev pk_keyboard; /* The underlying keyboard. */
#endif /* !__cplusplus */
	ps2_portid_t           pk_portno;     /* [const] PS/2 port number. */
	u8                     pk_state;      /* ISR-only: PS/2 keyboard state (one of `PS2_KEYBOARD_STATE_*'). */
	struct shared_lock     pk_cmdlock;    /* Lock held when issuing commands to the keyboard. */
	u8                     pk_errors;     /* ISR-only: PS/2 error state (set of `PS2_KEYBOARD_ERROR_*'). */
	struct sig             pk_errors_sig; /* Signal broadcast when `pk_errors' changes. */
};


INTDEF FREE void KCALL
ps2_keyboard_create(struct ps2_probe_data *__restrict probe_data,
                    ps2_portid_t portno);

DECL_END

#endif /* !GUARD_MODPS2_KEYBOARD_H */
