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
#ifndef GUARD_KERNEL_INCLUDE_DEV_VIDEO_H
#define GUARD_KERNEL_INCLUDE_DEV_VIDEO_H 1

#include <kernel/compiler.h>

#include <dev/char.h>
#include <dev/ansitty.h>
#include <kos/ioctl/video.h>
#include <kernel/types.h>

#include <libvideo/codec/codecs.h>

/* Video adapter interface */

DECL_BEGIN

#ifdef __CC__

struct video_device;

struct video_device_ops {
	/* [1..1] Enumerate available display formats for the given video device.
	 * @param: offset: The number of leading formats to skip (for consecutive
	 *                 calls to query supported formats in chunks)
	 * @return: * : The number of returned video format descriptors.
	 *              This is always `<= limit' and always `== limit'
	 *              if there may be more formats. */
	size_t (KCALL *vdf_listfmt)(struct video_device *__restrict self,
	                            USER CHECKED struct vd_format *fmt,
	                            size_t offset, size_t limit)
			THROWS(E_SEGFAULT, E_IOERROR, ...);

	/* [1..1] Get/Set the current video format.
	 * NOTE: When `VIDEO_CODEC_NONE' is used/returned as codec, the video device
	 *       is set to terminal mode, an optional mode allowing the display to be
	 *       used as an ansi tty mode.
	 * @throws: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_VIDEO_CODEC: [vdf_setfmt] ... */
	void (KCALL *vdf_getfmt)(struct video_device *__restrict self, USER CHECKED struct vd_format *fmt)
			THROWS(E_SEGFAULT, E_IOERROR, ...);
	void (KCALL *vdf_setfmt)(struct video_device *__restrict self, USER CHECKED struct vd_format const *fmt)
			THROWS(E_SEGFAULT, E_IOERROR, E_INVALID_ARGUMENT_BAD_VALUE, ...);

	/* [0..1] Get/Set the current video palette (used for VIDEO_CODEC_HASPAL())
	 * NOTE: These ops are mandatory if the device supports any palette-driven video formats.
	 * NOTE: When called while a non-palette-based video mode is used, or when `codec' doesn't
	 *       match the actual current video format, the behavior is weakly undefined, in that
	 *       something may still happen, nothing may happen, but whatever happens, these
	 *       functions will still return normally with everything left in a consistent state.
	 * @param: pal: [vdf_setpal] When NULL, set the default palette for the current video mode. */
	void (KCALL *vdf_getpal)(struct video_device *__restrict self, vd_codec_t codec,
	                         USER CHECKED struct vd_palette *pal)
			THROWS(E_SEGFAULT, E_IOERROR, ...);
	void (KCALL *vdf_setpal)(struct video_device *__restrict self, vd_codec_t codec,
	                         USER CHECKED struct vd_palette const *pal)
			THROWS(E_SEGFAULT, E_IOERROR, ...);
	/* TODO: Operators to get/set the TTY-mode font. */
};

struct video_device
#ifdef __cplusplus
	: ansitty_device
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct ansitty_device   vd_ansi;  /* The underling ansitty device */
#endif /* !__cplusplus */
	struct video_device_ops vd_ops;   /* Video device operations. */
};

#define video_device_fini(self) \
	(ansitty_device_fini(self))

/* Generic video device ioctl() handler. */
FUNDEF NONNULL((1)) syscall_slong_t KCALL
video_device_ioctl(struct character_device *__restrict self, syscall_ulong_t cmd,
                   USER UNCHECKED void *arg, iomode_t mode) THROWS(...);


/* Initialize a given video device.
 * NOTE: `ops->ato_output' must be set to NULL when calling this function.
 *       The internal routing of this callback to injecting keyboard output
 *       is done dynamically when the ANSI TTY is connected to the output
 *       channel of a `struct tty'
 * This function initializes the following operators:
 *   - cd_type.ct_write = &ansitty_device_write;  // Mustn't be re-assigned!
 *   - cd_type.ct_fini  = &video_device_fini;     // Must be called by an override
 *   - cd_type.ct_ioctl = &video_device_ioctl;    // Must be called by an override
 * The following operators must still be defined by the caller:
 *   - cd_type.ct_mmap  = &...;  // mmap() the linear frame buffer for the current video format
 *                               //  - The behavior of mmap() in terminal mode is weakly undefined
 *                               //  - The contents/behavior of old mappings after a mode change
 *                               //    are weakly undefined
 */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL video_device_cinit)(struct video_device *__restrict self,
                                  struct video_device_ops const *__restrict ops,
                                  struct ansitty_operators const *tty_ops);



#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_DEV_VIDEO_H */
