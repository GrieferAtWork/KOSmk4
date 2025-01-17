/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _HW_HID_PS2_H
#define _HW_HID_PS2_H 1

#include <__stdinc.h>

#include <sys/io.h>

/* TODO: Split this header into:
 *       <hw/bus/ps2.h>
 *       <hw/hid/ps2kbd.h>
 *       <hw/hid/ps2mouse.h>
 */

__DECL_BEGIN

#define PS2_DATA   __IOPORT(0x60)
#define PS2_STATUS __IOPORT(0x64)
#define PS2_CMD    __IOPORT(0x64)

/* PS/2 status port flags. */
#define PS2_STATUS_OUTFULL              0x01
#define PS2_STATUS_INFULL               0x02
#define PS2_STATUS_SYSTEM               0x04
#define PS2_STATUS_IN_IS_CONTROLLER_CMD 0x08
#define PS2_STATUS_KB_ENABLED           0x10
#define PS2_STATUS_OUTFULL2             0x20
#define PS2_STATUS_TIMEOUT_ERROR        0x40
#define PS2_STATUS_PARITY_ERROR         0x80

#define PS2_RSP_ACK    0xfa  /* Command acknowledged */
#define PS2_RPS_RESEND 0xfe  /* Please resend last command */


/* PS/2 controller command codes. */
#define PS2_CONTROLLER_RRAM(n)            (0x20 + (n))
#define PS2_CONTROLLER_WRAM(n)            (0x60 + (n))
#define PS2_CONTROLLER_TEST_PORT1         0xaa
#define PS2_CONTROLLER_ENABLE_PORT1       0xae
#define PS2_CONTROLLER_DISABLE_PORT1      0xad
#define PS2_CONTROLLER_TEST_PORT2         0xa9
#define PS2_CONTROLLER_ENABLE_PORT2       0xa8
#define PS2_CONTROLLER_DISABLE_PORT2      0xa7
#define PS2_CONTROLLER_READ_OUTPUT        0xd0
#define PS2_CONTROLLER_WRITE_OUTPUT       0xd1
#define PS2_CONTROLLER_WRITE_PORT1_OUTPUT 0xd2
#define PS2_CONTROLLER_WRITE_PORT2_OUTPUT 0xd3
#define PS2_CONTROLLER_WRITE_PORT2_INPUT  0xd4

/* Layout of the `PS2_CONTROLLER_RRAM(0)' (Controller configuration) byte. */
#define PS2_CONTROLLER_CFG_PORT1_IRQ       0x01
#define PS2_CONTROLLER_CFG_PORT2_IRQ       0x02
#define PS2_CONTROLLER_CFG_SYSTEMFLAG      0x04
#define PS2_CONTROLLER_CFG_PORT1_CLOCK     0x10
#define PS2_CONTROLLER_CFG_PORT2_CLOCK     0x20
#define PS2_CONTROLLER_CFG_PORT1_TRANSLATE 0x40

/* PS/2 keyboard command codes. */
#define PS2_KEYBOARD_CMD_SETLED           0xed /* RECV(PS2_RSP_ACK), SEND(PS2_KEYBOARD_CMD_SETLED_*), RECV(PS2_RSP_ACK) */
#   define PS2_KEYBOARD_CMD_SETLED_SCROLLLOCK 0x01
#   define PS2_KEYBOARD_CMD_SETLED_NUMLOCK    0x02
#   define PS2_KEYBOARD_CMD_SETLED_CAPSLOCK   0x04
#define PS2_KEYBOARD_CMD_ECHO             0xee /* RECV(0xee) */
#define PS2_KEYBOARD_CMD_SCANSET          0xf0 /* RECV(PS2_RSP_ACK), SEND(PS2_KEYBOARD_CMD_SCANSET_*), RECV(PS2_RSP_ACK), ... */
#   define PS2_KEYBOARD_CMD_SCANSET_GET   0x00 /* Get current scanset -- RECV(PS2_RSP_ACK), SEND(PS2_KEYBOARD_CMD_SCANSET_GET), RECV(PS2_RSP_ACK), RECV(<result>) */
#   define PS2_KEYBOARD_CMD_SCANSET_SET1  0x01 /* Use scanset #1 -- RECV(PS2_RSP_ACK), SEND(PS2_KEYBOARD_CMD_SCANSET_SET1), RECV(PS2_RSP_ACK) */
#   define PS2_KEYBOARD_CMD_SCANSET_SET2  0x02 /* Use scanset #2 -- RECV(PS2_RSP_ACK), SEND(PS2_KEYBOARD_CMD_SCANSET_SET2), RECV(PS2_RSP_ACK) */
#   define PS2_KEYBOARD_CMD_SCANSET_SET3  0x03 /* Use scanset #3 -- RECV(PS2_RSP_ACK), SEND(PS2_KEYBOARD_CMD_SCANSET_SET3), RECV(PS2_RSP_ACK) */
#define PS2_KEYBOARD_CMD_IDENTIFY         0xf2 /* RECV(PS2_RSP_ACK), RECV(ID0), [RECV(ID1), [RECV(ID2), [...]]] */
#define PS2_KEYBOARD_CMD_ENABLE_SCANNING  0xf4 /* RECV(PS2_RSP_ACK) */
#define PS2_KEYBOARD_CMD_DISABLE_SCANNING 0xf5 /* RECV(PS2_RSP_ACK) */
#define PS2_KEYBOARD_CMD_SETDEFAULT       0xf6 /* RECV(PS2_RSP_ACK) */
#define PS2_KEYBOARD_CMD_RESET            0xff /* RECV(PS2_RSP_ACK), RECV(0xaa) */

__DECL_END

#endif /* !_HW_HID_PS2_H */
