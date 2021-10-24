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

struct videodev;

struct videodev_ops {
#ifdef CONFIG_USE_NEW_FS
	struct ansittydev_ops vdf_tty; /* Ansi tty operators. */
#endif /* CONFIG_USE_NEW_FS */

	/* [1..1] Enumerate available display formats for the given video device.
	 * @param: offset: The number of leading formats to skip (for consecutive
	 *                 calls  to   query   supported   formats   in   chunks)
	 * @return: * : The number of returned video format descriptors.
	 *              This  is always `<= limit' and always `== limit'
	 *              if there may be more formats. */
	size_t (KCALL *vdf_listfmt)(struct videodev *__restrict self,
	                            USER CHECKED struct vd_format *fmt,
	                            size_t offset, size_t limit)
			THROWS(E_SEGFAULT, E_IOERROR, ...);

	/* [1..1] Get/Set the current video format.
	 * NOTE: When `VIDEO_CODEC_NONE' is used/returned as codec, the video  device
	 *       is set to terminal mode, an optional mode allowing the display to be
	 *       used as an ansi tty mode.
	 * @throws: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_VIDEO_CODEC: [vdf_setfmt] ... */
	void (KCALL *vdf_getfmt)(struct videodev *__restrict self, USER CHECKED struct vd_format *fmt)
			THROWS(E_SEGFAULT, E_IOERROR, ...);
	void (KCALL *vdf_setfmt)(struct videodev *__restrict self, USER CHECKED struct vd_format const *fmt)
			THROWS(E_SEGFAULT, E_IOERROR, E_INVALID_ARGUMENT_BAD_VALUE, ...);

	/* [0..1] Get/Set   the   current   video   palette   (used   for   VIDEO_CODEC_HASPAL())
	 * NOTE: These ops are mandatory if the device supports any palette-driven video formats.
	 * NOTE: When called while a non-palette-based video mode is used, or when `codec' doesn't
	 *       match the actual current video format, the behavior is weakly undefined, in  that
	 *       something  may  still happen,  nothing may  happen,  but whatever  happens, these
	 *       functions will still return normally with everything left in a consistent  state.
	 * @param: pal: [vdf_setpal] When NULL, set the default palette for the current video mode. */
	void (KCALL *vdf_getpal)(struct videodev *__restrict self, vd_codec_t codec,
	                         USER CHECKED struct vd_palette *pal)
			THROWS(E_SEGFAULT, E_IOERROR, ...);
	void (KCALL *vdf_setpal)(struct videodev *__restrict self, vd_codec_t codec,
	                         USER CHECKED struct vd_palette const *pal)
			THROWS(E_SEGFAULT, E_IOERROR, ...);
	/* TODO: Operators to get/set the TTY-mode font. */
};


struct videodev
#ifndef __WANT_FS_INLINE_STRUCTURES
    : ansittydev                     /* The underling ansitty device */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct ansittydev       vd_atty; /* The underling ansitty device */
#define _videodev_asatty(x) &(x)->vd_atty
#define _videodev_atty_     vd_atty.
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _videodev_asatty(x) x
#define _videodev_atty_     /* nothing */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
#ifndef CONFIG_USE_NEW_FS
	struct videodev_ops vd_ops;  /* Video device operations. */
#endif /* !CONFIG_USE_NEW_FS */
};


#ifdef CONFIG_USE_NEW_FS
#define videodev_getops(self) \
	((struct videodev_ops const *)__COMPILER_REQTYPE(struct videodev const *, self)->_videodev_atty_ _ansittydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_ops)
#define _videodev_assert_ops_(ops) _ansittydev_assert_ops_(&(ops)->vdf_tty)

/* Helper macros */
#define mfile_asvideo(self)      ((struct videodev *)(self))
#define fnode_asvideo(self)      mfile_asvideo(_fnode_asfile(self))
#define devnode_asvideo(self)    fnode_asvideo(_fdevnode_asnode(self))
#define device_asvideo(self)     devnode_asvideo(_device_asdevnode(self))
#define chrdev_asvideo(self)     device_asvideo(_chrdev_asdev(self))
#define ansittydev_asvideo(self) chrdev_asvideo(_ansittydev_aschr(self))

/* Default video device operators. */
#define videodev_v_destroy ansittydev_v_destroy
#define videodev_v_changed ansittydev_v_changed
#define videodev_v_wrattr  ansittydev_v_wrattr
#define videodev_v_write   ansittydev_v_write
FUNDEF NONNULL((1)) syscall_slong_t KCALL
videodev_v_ioctl(struct mfile *__restrict self, syscall_ulong_t cmd,
                 USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Initialize common+basic fields. The caller must still initialize:
 *  - self->_videodev_atty_ _ansittydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_flags |= MFILE_FN_GLOBAL_REF;  # s.a. `device_registerf()'
 *  - self->_videodev_atty_ _ansittydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_allnodes;  # s.a. `device_registerf()'
 *  - self->_videodev_atty_ _ansittydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_supent;    # s.a. `device_registerf()'
 *  - self->_videodev_atty_ _ansittydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_ino;       # s.a. `device_registerf()'
 *  - self->_videodev_atty_ _ansittydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_mode;      # Something or'd with S_IFCHR
 *  - self->_videodev_atty_ _ansittydev_chr_ _chrdev_dev_ _device_devnode_ dn_devno;                     # s.a. `device_registerf()'
 *  - self->_videodev_atty_ _ansittydev_chr_ _chrdev_dev_ dv_driver;                                     # As `incref(drv_self)'
 *  - self->_videodev_atty_ _ansittydev_chr_ _chrdev_dev_ dv_dirent;                                     # s.a. `device_registerf()'
 *  - self->_videodev_atty_ _ansittydev_chr_ _chrdev_dev_ dv_byname_node;                                # s.a. `device_registerf()'
 * @param: struct videodev          *self:    Ansitty to initialize.
 * @param: struct videodev_ops      *ops:     Ansitty operators.
 * @param: struct ansitty_operators *tty_ops: TTY operators. NOTE: `ato_output', `ato_setled' and `ato_termios' must _NOT_
 *                                            be implemented; these operators are provided by the internal implementation! */
#define _videodev_init(self, ops, tty_ops) \
	_ansittydev_init(_videodev_asatty(self), &(ops)->vdf_tty, tty_ops)
#define _videodev_cinit(self, ops, tty_ops) \
	_ansittydev_cinit(_videodev_asatty(self), &(ops)->vdf_tty, tty_ops)
	
/* Finalize a partially initialized `struct videodev' (as initialized by `_videodev_init()') */
#define _videodev_fini(self) _ansittydev_fini(_videodev_asatty(self))

#else /* CONFIG_USE_NEW_FS */

#define videodev_getops(self) (&(self)->vd_ops)

/* Generic video device ioctl() handler. */
FUNDEF NONNULL((1)) syscall_slong_t KCALL
videodev_v_ioctl(struct chrdev *__restrict self, syscall_ulong_t cmd,
                 USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
#define video_device_v_fini(self) ansittydev_v_fini(self)

/* Initialize a given video device.
 * NOTE: `ops->ato_output' must be set to NULL when calling this  function.
 *       The internal routing of this callback to injecting keyboard output
 *       is done dynamically when the ANSI  TTY is connected to the  output
 *       channel of a `struct mkttydev'
 * This function initializes the following operators:
 *   - cd_type.ct_write = &ansittydev_v_write;  // Mustn't be re-assigned!
 *   - cd_type.ct_fini  = &video_device_v_fini;     // Must be called by an override
 *   - cd_type.ct_ioctl = &videodev_v_ioctl;    // Must be called by an override
 * The following operators must still be defined by the caller:
 *   - cd_type.ct_mmap  = &...;  // mmap() the linear frame buffer for the current video format
 *                               //  - The behavior of mmap() in terminal mode is weakly undefined
 *                               //  - The contents/behavior of old mappings after a mode change
 *                               //    are weakly undefined
 */
FUNDEF NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(KCALL videodev_cinit)(struct videodev *__restrict self,
                              struct videodev_ops const *__restrict ops,
                              struct ansitty_operators const *__restrict tty_ops);
#endif /* !CONFIG_USE_NEW_FS */


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_DEV_VIDEO_H */
