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
#ifndef _KOS_IOCTL_VIDEO_H
#define _KOS_IOCTL_VIDEO_H 1

/* KOS-specific video-device system interface. */

#include <__stdinc.h>

#include <asm/ioctl.h>
#include <bits/types.h>
#include <kos/hop/openfd.h>

#include <libsvga/chipset.h>

__DECL_BEGIN

/* IO control codes for /dev/svga and ttys/locks created with it.
 * NOTES:
 *  - SVGA_IOC_GETMODE: [svga] Throws `E_NO_SUCH_OBJECT' if no tty/lck is active
 *  - SVGA_IOC_GETMODE: [lck]  Throws `E_NO_SUCH_OBJECT' if no video mode has been set, yet
 *  - SVGA_IOC_SETMODE: [svga] Throws `E_NO_SUCH_OBJECT' if no tty/lck is active
 *  - Commands marked with [io] require the caller to have `CAP_SYS_RAWIO'
 *  - SVGA_IOC_GETDEFMODE/SVGA_IOC_SETDEFMODE is the same for svga and all derived objects
 *  - `lck' can be  mmap'd after  `SVGA_IOC_SETMODE' was  used to  set a  mode.
 *    The mmap(2) operation once again asserts that you've got `CAP_SYS_RAWIO',
 *    but once that check passes, it will map the mode's `smi_lfb' (if present)
 *    or the region `A0000-BFFFF'
 *  - SVGA_IOC_SETMODE: [svga] Sets the video mode of the currently active tty.
 *                             When a video lock is  active, the video mode  of
 *                             the tty that will be loaded once the video  lock
 *                             is released is set.
 *  - SVGA_IOC_SETMODE: [tty]  Sets the video mode of this tty. If the tty is
 *                             not currently active, changes will only become
 *                             visible once it gets activated.
 *  - SVGA_IOC_SETMODE: [lck]  Sets the reference video mode of this lock.  Note
 *                             that this  is not  really necessary,  as a  video
 *                             lock allows you to directly talk to the hardware,
 *                             which can be done with `libsvga'.
 *
 * The video lock object:
 *  - This object must be created before you should perform direct access to  video
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
#define SVGA_IOC_GETMODE    _IOR_KOS('S', 0x01, struct svga_modeinfo) /* [   svga|tty|lck] Get current video mode */
#define SVGA_IOC_SETMODE    _IOW_KOS('S', 0x01, struct svga_modeinfo) /* [io:svga|tty|lck] Set current video mode (@throw: E_NO_SUCH_OBJECT: Not a supported mode) */
#define SVGA_IOC_GETDEFMODE _IOR_KOS('S', 0x02, struct svga_modeinfo) /* [   svga|tty|lck] Get default video mode */
#define SVGA_IOC_SETDEFMODE _IOW_KOS('S', 0x02, struct svga_modeinfo) /* [io:svga|tty|lck] Set default video mode (@throw: E_NO_SUCH_OBJECT: Not a supported mode) */
#define SVGA_IOC_LSMODES    _IOR_KOS('S', 0x03, struct svga_lsmodes)  /* [   svga|tty|lck] List available modes */
#define SVGA_IOC_MAKETTY    _IOR_KOS('S', 0x04, struct svga_maketty)  /* [io:svga        ] Create a new TTY */
#define SVGA_IOC_MAKELCK    _IOR_KOS('S', 0x05, struct hop_openfd)    /* [io:svga        ] Create a new video lock */
#define SVGA_IOC_ACTIVATE   _IO_KOS('S', 0x05)                        /* [io:     tty    ] Activate TTY */
/* TODO: ioctls to query chipset name & strings */

#ifdef __CC__
struct svga_lsmodes {
	__uint32_t                svl_offset; /* Start enumeration with the `svl_offset'th mode */
	__uint32_t                svl_count;  /* [in]  max # of modes to enumerate
	                                       * [out] #  of   modes  actually   enumerated.
	                                       * When `svl_offset >= MODE_COUNT', set to `0' */
	union {
		struct svga_modeinfo *svl_buf;    /* [0..svl_count] Mode list buffer. */
		__uint64_t           _svl_albuf;  /* Align... */
	};
};

struct svga_maketty {
	struct hop_openfd    smt_res;    /* [out] Handle for the newly created ansitty. */
	union {
		char const      *smt_name;   /* [1..1] TTY Device name. (Filename for /dev) */
		__uint64_t      _smt_alname; /* Align... */
	};
	struct svga_modeinfo smt_mode;   /* Video mode to set for this tty. */
};

#endif /* __CC__ */

__DECL_END

#endif /* !_KOS_IOCTL_VIDEO_H */
