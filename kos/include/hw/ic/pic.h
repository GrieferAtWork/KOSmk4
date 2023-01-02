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
#ifndef _HW_IC_PIC_H
#define _HW_IC_PIC_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>
#include <sys/io.h>

/* PIC (Programmable Interrupt Controller) API. */
#define X86_PIC1       __IOPORT(0x20) /* IO base address for master PIC */
#define X86_PIC2       __IOPORT(0xa0) /* IO base address for slave PIC */
#define X86_PIC1_CMD   X86_PIC1
#define X86_PIC1_DATA (X86_PIC1 + 1)
#define X86_PIC2_CMD   X86_PIC2
#define X86_PIC2_DATA (X86_PIC2 + 1)

#define X86_PIC_CMD_EOI     0x20 /* End-of-interrupt command code */
#define X86_ICW1_ICW4       0x01 /* ICW4 (not) needed */
#define X86_ICW1_SINGLE     0x02 /* Single (cascade) mode */
#define X86_ICW1_INTERVAL4  0x04 /* Call address interval 4 (8) */
#define X86_ICW1_LEVEL      0x08 /* Level triggered (edge) mode */
#define X86_ICW1_INIT       0x10 /* Initialization - required! */
#define X86_ICW4_8086       0x01 /* 8086/88 (MCS-80/85) mode */
#define X86_ICW4_AUTO       0x02 /* Auto (normal) EOI */
#define X86_ICW4_BUF_SLAVE  0x08 /* Buffered mode/slave */
#define X86_ICW4_BUF_MASTER 0x0c /* Buffered mode/master */
#define X86_ICW4_SFNM       0x10 /* Special fully nested (not) */
#define X86_PIC_READ_IRR    0x0a /* OCW3 irq ready next CMD read */
#define X86_PIC_READ_ISR    0x0b /* OCW3 irq service next CMD read */

#endif /* !_HW_IC_PIC_H */
