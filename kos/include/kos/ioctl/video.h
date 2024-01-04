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
#ifndef _KOS_IOCTL_VIDEO_H
#define _KOS_IOCTL_VIDEO_H 1

/* KOS-specific video-device system interface. */

#include <__stdinc.h>

#include <asm/ioctl.h>
#include <bits/types.h>

#include "_openfd.h"


/* Activate a video TTY (only  applicable to video TTY  objects)
 * The creation of video tty objects is done via device-specific
 * ioctls. E.g. for svga, you'd use `SVGA_IOC_MAKETTY'.
 * @throw: E_INSUFFICIENT_RIGHTS: Caller doesn't have `CAP_SYS_RAWIO' */
#define VID_IOC_ACTIVATE _IO_KOS('V', 0x00)

/* Create a new video lock object for a given video device.
 * @throw: E_INSUFFICIENT_RIGHTS: Caller doesn't have `CAP_SYS_RAWIO' */
#define VID_IOC_MAKELCK _IOR_KOS('V', 0x01, struct openfd)

/* Video TTY ioctl codes.
 * When used on a video controller device, these commands are forwarded to the currently active tty. */
#define VID_IOC_GETTTYINFO  _IOR_KOS('V', 0x10, struct vidttyinfo)     /* Get TTY information */
#define VID_IOC_GETCELLDATA _IOR_KOS('V', 0x11, struct vidttycelldata) /* Get TTY cell data; @throw: E_INDEX_ERROR_OUT_OF_BOUNDS: ... */
#define VID_IOC_SETCELLDATA _IOW_KOS('V', 0x11, struct vidttycelldata) /* Set TTY cell data; @throw: E_INDEX_ERROR_OUT_OF_BOUNDS: ... */
#define VID_IOC_GETCURSOR   _IOR_KOS('V', 0x12, __uint16_t[2])         /* Get 0-based cursor x,y position (same data-source as "\e[6n") */
#define VID_IOC_SETCURSOR   _IOW_KOS('V', 0x12, __uint16_t[2])         /* Set 0-based cursor x,y position; @throw: E_INDEX_ERROR_OUT_OF_BOUNDS: ... */


#ifdef __CC__
__DECL_BEGIN

struct vidttyinfo {
	__uint16_t vti_cellw;    /* [const] Character cell width in pixels (usually `9') */
	__uint16_t vti_cellh;    /* [const] Character cell height in pixels (usually `16') */
	__uint16_t vti_resx;     /* [const] # of character cells in X */
	__uint16_t vti_resy;     /* [const] # of character cells in Y */
	__uint16_t vti_cellsize; /* [const] Cell buffer size (in bytes) */
};

struct vidttycelldata {
	__uint16_t      vcd_x;     /* First cell X position (0-based) */
	__uint16_t      vcd_y;     /* First cell Y position (0-based) */
	__uint16_t      vcd_w;     /* # of cells to read/write in X */
	__uint16_t      vcd_h;     /* # of cells to read/write in Y */
	union {
		__byte_t   *vcd_dat;   /* [vcd_w * vcd_h * vti_cellsize] Cell data  buffer.
		                        * Format is device-specific, but using this you can
		                        * easily preserve+restore specific areas of display
		                        * memory. */
		__uint64_t _vcd_aldat; /* ... */
	};
};

__DECL_END
#endif /* __CC__ */


#endif /* !_KOS_IOCTL_VIDEO_H */
