/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Linux     (/usr/include/linux/vt.h) */
/* (#) Portability: diet libc (/include/linux/vt.h) */
#ifndef _LINUX_VT_H
#define _LINUX_VT_H 1

/* TODO: Support this stuff within the kernel */
/* DISCLAIMER: _STRONGLY_ Based on '/usr/include/linux/vt.h' */

#include <__stdinc.h>

#include <asm/ioctl.h>
#include <bits/types.h>

/*
 * These constants are also useful for user-level apps (e.g., VC resizing).
 */
#define MIN_NR_CONSOLES      1  /* must be at least 1 */
#define MAX_NR_CONSOLES      63 /* serial lines start at 64 */
#define MAX_NR_USER_CONSOLES 63 /* must be root to allocate above this */

/* 0x56 is 'V', to avoid collision with termios and kd */

#define VT_OPENQRY _IO('V', 0x00) /* [int *pvtno] find available vt */

#ifdef __CC__
struct vt_mode {
	__int8_t  mode;   /* vt mode (one of `VT_AUTO', `VT_PROCESS' or `VT_ACKACQ') */
	__int8_t  waitv;  /* if set, hang on writes if not active */
	__int16_t relsig; /* signal to raise on release req */
	__int16_t acqsig; /* signal to raise on acquisition */
	__int16_t frsig;  /* unused (set to 0) */
};
#endif /* __CC__ */
#define VT_GETMODE _IO('V', 0x01) /* [struct vt_mode *mode] get mode of active vt */
#define VT_SETMODE _IO('V', 0x02) /* [struct vt_mode const *mode] set mode of active vt */
#define    VT_AUTO    0x00 /* auto vt switching */
#define    VT_PROCESS 0x01 /* process controls switching */
#define    VT_ACKACQ  0x02 /* acknowledge switch */

#ifdef __CC__
struct vt_stat {
	__uint16_t v_active; /* active vt */
	__uint16_t v_signal; /* signal to send */
	__uint16_t v_state;  /* vt bitmask */
};
#endif /* __CC__ */

/* Note: the  ioctl  VT_GETSTATE does  not  work for
 * consoles 16 and higher (since it returns a short) */
#define VT_GETSTATE    _IO('V', 0x03) /* [struct vt_stat *st] get global vt state info */
#define VT_SENDSIG     _IO('V', 0x04) /* signal to send to bitmask of vts */

#define VT_RELDISP     _IO('V', 0x05) /* release display */

#define VT_ACTIVATE    _IO('V', 0x06) /* make vt active */
#define VT_WAITACTIVE  _IO('V', 0x07) /* wait for vt active */
#define VT_DISALLOCATE _IO('V', 0x08) /* free memory associated to vt */

#ifdef __CC__
struct vt_sizes {
	__int16_t v_rows;       /* number of rows */
	__int16_t v_cols;       /* number of columns */
	__int16_t v_scrollsize; /* number of lines of scrollback */
};
#endif /* __CC__ */
#define VT_RESIZE _IO('V', 0x09) /* set kernel's idea of screensize */

#ifdef __CC__
struct vt_consize {
	__uint16_t v_rows; /* number of rows */
	__uint16_t v_cols; /* number of columns */
	__uint16_t v_vlin; /* number of pixel rows on screen */
	__uint16_t v_clin; /* number of pixel rows per character */
	__uint16_t v_vcol; /* number of pixel columns on screen */
	__uint16_t v_ccol; /* number of pixel columns per character */
};
#endif /* __CC__ */
#define VT_RESIZEX       _IO('V', 0x0a) /* set kernel's idea of screensize + more */
#define VT_LOCKSWITCH    _IO('V', 0x0b) /* disallow vt switching */
#define VT_UNLOCKSWITCH  _IO('V', 0x0c) /* allow vt switching */
#define VT_GETHIFONTMASK _IO('V', 0x0d) /* return hi font mask */

#ifdef __CC__
struct vt_event {
	__UINT32_TYPE__ event;
#define VT_EVENT_SWITCH  0x0001 /* Console switch */
#define VT_EVENT_BLANK   0x0002 /* Screen blank */
#define VT_EVENT_UNBLANK 0x0004 /* Screen unblank */
#define VT_EVENT_RESIZE  0x0008 /* Resize display */
#define VT_MAX_EVENT     0x000f
	__UINT32_TYPE__ oldev;  /* Old console */
	__UINT32_TYPE__ newev;  /* New console (if changing) */
	__UINT32_TYPE__ pad[4]; /* Padding for expansion */
};
#endif /* __CC__ */

#define VT_WAITEVENT _IO('V', 0x0e) /* Wait for an event */

#ifdef __CC__
struct vt_setactivate {
	__UINT32_TYPE__ console;
	struct vt_mode  mode;
};
#endif /* __CC__ */

#define VT_SETACTIVATE _IO('V', 0x0f) /* Activate and set the mode of a console */


#endif /* !_LINUX_VT_H */
