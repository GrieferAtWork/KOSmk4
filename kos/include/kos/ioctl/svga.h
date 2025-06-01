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
/*!always_includes <kos/ioctl/_openfd.h>*/
#ifndef _KOS_IOCTL_SVGA_H
#define _KOS_IOCTL_SVGA_H 1

/* KOS-specific /dev/svga system interface. */

#include <__stdinc.h>

#include <asm/ioctl.h>
#include <bits/types.h>
#include <kos/ioctl/video.h>

#include <libsvgadrv/chipset.h>

#include "_openfd.h"

__DECL_BEGIN

/* IO control codes for `/dev/svga' and ttys/locks created with it.
 *
 * NOTES:
 *  - SVGA_IOC_GETMODE: [svga] Throws `E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND' if no tty/lck is active
 *  - SVGA_IOC_GETMODE: [lck]  Throws `E_ILLEGAL_OPERATION_CONTEXT_SVGA_NO_MODE_SET' if no video mode
 *                             was set. This only happens if a video lock is set when no tty had been
 *                             active. When a tty was active before, its video mode will be inherited
 *                             during `SVGA_IOC_MAKELCK'.
 *  - SVGA_IOC_SETMODE: [svga] Throws `E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND' if no tty/lck is active
 *  - Commands marked with [io] require the caller to have `CAP_SYS_RAWIO'
 *  - SVGA_IOC_GETDEFMODE/SVGA_IOC_SETDEFMODE is the same for svga and all derived objects
 *  - `lck' can be  mmap'd after  `SVGA_IOC_SETMODE' was  used to  set a  mode.
 *    The mmap(2) operation once again asserts that you've got `CAP_SYS_RAWIO',
 *    but once that check passes, it will map the mode's `smi_lfb' (if present)
 *    or the region `A0000-BFFFF'
 *  - SVGA_IOC_SETMODE: [svga] Sets the video mode  of the currently active  tty.
 *                             When a video lock is active, change the video mode
 *                             of the tty that will be loaded once the video lock
 *                             is released.
 *  - SVGA_IOC_SETMODE: [tty]  Sets the video mode of this tty. If the tty is
 *                             not currently active, changes will only become
 *                             visible once it gets activated.
 *  - SVGA_IOC_SETMODE: [lck]  Sets the reference video mode of this lock.  Note
 *                             that this  is not  really necessary,  as a  video
 *                             lock allows you to directly talk to the hardware,
 *                             which can be done with `libsvgadrv'.
 *
 * The video lock object:
 *  - This object should  be created  before you make  any direct  access to  video
 *    registers. Once created, this object's continued existence (iow: don't  close
 *    it until you're done) will prevent  system TTYs from really being  activated,
 *    in that `SVGA_IOC_ACTIVATE' will not truly activate the tty, but will instead
 *    mark the tty to be loaded once the video lock is close(2)'d.
 *  - Additionally, video lock objects contain  an internal copy of all  VGA
 *    registers, including any chipset-specific  ones. Once the lock  object
 *    gets destroyed (by its last reference being `close(2)'d, including the
 *    case where the owning process unexpectedly terminates), it will  start
 *    an async operation  to restore  chipset registers and  its stored  VGA
 *    mode, before handing off control to the TTY last `SVGA_IOC_ACTIVATE'ed
 *  - Calling `SVGA_IOC_MAKELCK' when there already exists another lock will
 *    block until said other lock  is released. As such,  `SVGA_IOC_MAKELCK'
 *    can  (and _should_) be  used by user-space  programs to gain exclusive
 *    access to the video chipset.
 */
#define SVGA_IOC_MAKELCK     VID_IOC_MAKELCK                           /* [io:svga        ] Create a new video lock */
#define SVGA_IOC_ACTIVATE    VID_IOC_ACTIVATE                          /* [io:     tty    ] Activate TTY */
#define SVGA_IOC_MAKETTY     _IOR_KOS('S', 0x00, struct svga_maketty)  /* [io:svga        ] Create a new TTY */
#define SVGA_IOC_GETMODE     _IOR_KOS('S', 0x01, struct svga_modeinfo) /* [   svga|tty|lck] Get current video mode */
#define SVGA_IOC_SETMODE     _IOW_KOS('S', 0x01, struct svga_modeinfo) /* [io:svga|tty|lck] Set current video mode (@throw: E_INVALID_ARGUMENT_CONTEXT_SVGA_INVALID_MODE: Not a supported mode) */
#define SVGA_IOC_GETDEFMODE  _IOR_KOS('S', 0x02, struct svga_modeinfo) /* [   svga|tty|lck] Get default video mode */
#define SVGA_IOC_SETDEFMODE  _IOW_KOS('S', 0x02, struct svga_modeinfo) /* [io:svga|tty|lck] Set default video mode (@throw: E_INVALID_ARGUMENT_CONTEXT_SVGA_INVALID_MODE: Not a supported mode) */
#define SVGA_IOC_LSMODES     _IOR_KOS('S', 0x03, struct svga_lsmodes)  /* [   svga|tty|lck] List available modes */
#define SVGA_IOC_GETCSNAME   _IOR_KOS('S', 0x04, char[SVGA_CSNAMELEN]) /* [   svga|tty|lck] Get chipset name */
#define SVGA_IOC_CSSTRINGS   _IOR_KOS('S', 0x05, struct svga_strings)  /* [   svga|tty|lck] Get chipset strings */
#define SVGA_IOC_GETPAL_RGBX _IOR_KOS('S', 0x06, struct svga_palette)  /* [   svga|tty|lck] Get video palette (using `video_color_t' format) */
#define SVGA_IOC_SETPAL_RGBX _IOW_KOS('S', 0x06, struct svga_palette)  /* [io:svga|tty|lck] Set video palette (using `video_color_t' format) */
#define SVGA_IOC_GETCSMODE   _IOR_KOS('S', 0x07, struct svga_csmode)   /* [   svga|tty|lck] Get current video mode (including extra chipset fields) */
#define SVGA_IOC_SETCSMODE   _IOW_KOS('S', 0x07, struct svga_csmode)   /* [io:         lck] Set current video mode (including extra chipset fields) (only allowed on video locks, since this allows setting invalid modes) */
/*      SVGA_IOC_            _IO*_KOS('S', 0x08, ...)                   * ... */
/*      SVGA_IOC_            _IO*_KOS('S', 0x09, ...)                   * ... */

/* Misc tty functions. */
#define SVGA_IOC_GETTTYINFO  VID_IOC_GETTTYINFO                        /* [   svga|tty    ] Get TTY information */
#define SVGA_IOC_GETCELLDATA VID_IOC_GETCELLDATA                       /* [   svga|tty    ] Get TTY cell data; @throw: E_INDEX_ERROR_OUT_OF_BOUNDS: ... */
#define SVGA_IOC_SETCELLDATA VID_IOC_SETCELLDATA                       /* [   svga|tty    ] Set TTY cell data; @throw: E_INDEX_ERROR_OUT_OF_BOUNDS: ... */
#define SVGA_IOC_GETCURSOR   VID_IOC_GETCURSOR                         /* [   svga|tty    ] Get 0-based cursor x,y position (same data-source as "\e[6n") */
#define SVGA_IOC_SETCURSOR   VID_IOC_SETCURSOR                         /* [   svga|tty    ] Set 0-based cursor x,y position; @throw: E_INDEX_ERROR_OUT_OF_BOUNDS: ... */


#ifdef __CC__
struct svga_csmode {
	__uint64_t                svcm_bufsz; /* [in]  Available buffer size
	                                       * [out] Required buffer size */
	union {
		struct svga_modeinfo *svcm_buf;   /* [svcm_bufsz] Buffer for CS-specific mode info */
		__uint64_t           _svcm_albuf; /* Align... */
	};
};

struct svga_lsmodes {
	__uint32_t                svl_offset; /* Start enumeration with the `svl_offset'th mode */
	__uint32_t                svl_count;  /* [in]  max # of modes to enumerate.
	                                       * [out] Total number of modes minus `svl_offset' */
	union {
		struct svga_modeinfo *svl_buf;    /* [0..svl_count] Mode list buffer. */
		__uint64_t           _svl_albuf;  /* Align... */
	};
};

struct svga_maketty {
	struct openfd        smt_res;    /* [out] Handle for the newly created ansitty. */
	union {
		char const      *smt_name;   /* [1..1] TTY Device name. (Filename for /dev) */
		__uint64_t      _smt_alname; /* Align... */
	};
	struct svga_modeinfo smt_mode;   /* Video mode to set for this tty. */
};

struct svga_strings {
	__uint64_t      svs_start; /* Start enumeration with the `svs_start'th name/value pair. */
	__uint64_t      svs_count; /* [in]  Max # of name/value pairs to write.
	                            * [out] # of written name/value pairs. */
	__uint64_t      svs_bufsz; /* [in]  Input buffer size (in bytes)
	                            * [out] Required buffer size (in bytes) to write up to
	                            *       in:svs_count name/value pairs >= `svs_start'. */
	union {
		char       *svs_buf;   /* [0..svs_bufsz] String buffer. Strings are written as:
		                        * "name1\0value1\0name2\0value2\0lastname\0lastvalue\0"
		                        * The  last string must be detected by out:`svs_bufsz',
		                        * which points after the  "\0" of `"lastvalue"', or  by
		                        * counting the # of `\0', which equals `svs_count * 2'. */
		__uint64_t _svs_albuf; /* Align... */
	};
};

struct svga_palette_color;
struct svga_palette {
	__uint16_t                     svp_base;  /* [in] Color base index */
	__uint16_t                     svp_size;  /* [in] # of colors to read/write
	                                           * [out] # of actually read colors (clamped
	                                           * when trying to read past end of palette) */
	__uint32_t                    _svp_pad;   /* ... */
	union {
		struct svga_palette_color *svp_pal;   /* [0..svp_size] Palette color I/O data */
		__uint64_t                _svp_alpal; /* Align... */
	};
};

#endif /* __CC__ */

__DECL_END

#endif /* !_KOS_IOCTL_SVGA_H */
