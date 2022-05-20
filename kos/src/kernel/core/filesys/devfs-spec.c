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
#ifndef GUARD_KERNEL_CORE_FILESYS_DEVFS_SPEC_C
#define GUARD_KERNEL_CORE_FILESYS_DEVFS_SPEC_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/blkdev.h>
#include <kernel/fs/chrdev.h>
#include <kernel/fs/constdir.h>
#include <kernel/fs/devfs-spec.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/lnknode.h>
#include <kernel/fs/node.h>
#include <kernel/fs/ramfs.h>
#include <kernel/malloc.h>
#include <kernel/mman/mfile.h>
#include <sched/atomic64.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/overflow.h>

#include <kos/dev.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <sys/stat.h>

#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/**/
#include "devfs-spec.h"

DECL_BEGIN

/*
 * Special /dev-fs folders:
 *
 * /dev/block/             -- Contains symlinks for the /dev device, such as 8:0 -> ../sda
 * /dev/char/              -- Contains symlinks for the /dev device, such as 1:1 -> ../mem
 * /dev/cpu/[id]/cpuid     -- A readable file to access `cpuid' data for a given CPU.
 * /dev/disk/by-id/        -- Symlinks for block-devices
 * /dev/disk/by-label/     -- Symlinks for block-devices
 * /dev/disk/by-partlabel/ -- Symlinks for block-devices
 * /dev/disk/by-partuuid/  -- Symlinks for block-devices
 * /dev/disk/by-path/      -- Symlinks for block-devices
 * /dev/disk/by-uuid/      -- Symlinks for block-devices
 */



/************************************************************************/
/* Common operators                                                     */
/************************************************************************/
PRIVATE BLOCKING NONNULL((1)) void KCALL
devfs_spec_v_stat_with_boottime(struct mfile *__restrict self,
                                USER CHECKED struct stat *result)
		THROWS(...) {
	result->st_atime     = boottime.tv_sec;
	result->st_atimensec = boottime.tv_nsec;
	result->st_mtime     = boottime.tv_sec;
	result->st_mtimensec = boottime.tv_nsec;
	result->st_ctime     = boottime.tv_sec;
	result->st_ctimensec = boottime.tv_nsec;
	result->st_btime     = boottime.tv_sec;
	result->st_btimensec = boottime.tv_nsec;
	fdirnode_v_stat(self, result);
}

INTERN_CONST struct mfile_stream_ops const devfs_spec_v_stream_ops_with_boottime = {
	.mso_open  = &fdirnode_v_open,
	.mso_stat  = &devfs_spec_v_stat_with_boottime,
	.mso_ioctl = &fdirnode_v_ioctl,
};


/* Decode a string such as "4:5" into a devno.
 * When the given `name' can't be decoded as such, return `DEV_UNSET' */
PRIVATE ATTR_PURE WUNUSED dev_t KCALL
decode_devno(USER CHECKED char const *name, u16 namelen)
		THROWS(E_SEGFAULT) {
	char const *end = name + namelen;
	char ch;
	major_t major = 0;
	minor_t minor = 0;
	if (namelen < 3)
		goto err;
	for (;;) {
		if unlikely(name >= end)
			goto err;
		ch = *name++;
		if ((ch >= '1' && ch <= '9') ||
		    (ch == '0' && major != 0)) {
			if (OVERFLOW_UMUL(major, 10, &major) ||
			    OVERFLOW_UADD(major, ch - '0', &major))
				goto err;
		} else if (ch == ':' && major != 0) {
			break;
		} else {
			goto err;
		}
	}
	if unlikely(name >= end)
		goto err;
	ch = *name++;
	if (ch == '0') {
		/* minor number is supposed to be `0' */
		if (name != end)
			goto err;
	} else {
		for (;;) {
			if (ch >= '0' && ch <= '9') {
				if (OVERFLOW_UMUL(minor, 10, &minor) ||
				    OVERFLOW_UADD(minor, ch - '0', &minor))
					goto err;
			} else {
				goto err;
			}
			if (name >= end)
				break;
			ch = *name++;
		}
	}
	if (major > MAJORMASK)
		goto err;
	if (minor > MINORMASK)
		goto err;
	return MKDEV(major, minor);
err:
	return DEV_UNSET;
}


/* Symlink file node that expands to the name of a device
 * `dl_devname',  prefixed  by  `(char const *)fn_fsdata' */
struct devicelink: flnknode {
	REF struct devdirent *dl_devname; /* [1..1][const] Device name. */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL devicelink_v_destroy)(struct mfile *__restrict self) {
	struct devicelink *me;
	me = (struct devicelink *)mfile_aslnk(self);
	decref_unlikely(me->dl_devname);
	kfree(me);
}

PRIVATE BLOCKING WUNUSED NONNULL((1)) size_t KCALL
devicelink_v_readlink(struct flnknode *__restrict self,
                      USER CHECKED /*utf-8*/ char *buf,
                      size_t bufsize) {
	struct devicelink *me = (struct devicelink *)self;
	return snprintf(buf, bufsize, "%s%$s",
	                (char const *)me->fn_fsdata,
	                (size_t)me->dl_devname->dd_dirent.fd_namelen,
	                me->dl_devname->dd_dirent.fd_name);
}

INTERN_CONST struct flnknode_ops const devicelink_ops = {
	.lno_node = {
		.no_file = {
			.mo_destroy = &devicelink_v_destroy,
			.mo_changed = &flnknode_v_changed,
			.mo_stream  = &flnknode_v_stream_ops_readlink_size,
		},
		.no_free   = (typeoffield(struct fnode_ops, no_free))(void *)-1,
		.no_wrattr = &fnode_v_wrattr_noop,
	},
	.lno_readlink = &devicelink_v_readlink,
};

INTDEF struct flnknode const devicelink_template;

/* Construct a new devicelink object. */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct devicelink *KCALL
devicelink_new(char const *__restrict prefix, struct device *__restrict dev) {
	REF struct devicelink *result;
	result = (REF struct devicelink *)kmalloc(sizeof(struct devicelink), GFP_NORMAL);
	result = (REF struct devicelink *)memcpy(result, &devicelink_template, sizeof(devicelink_template));
	/* Fill in dynamic fields */
	mfile_tslock_acquire(dev);
	if likely(!(dev->mf_flags & MFILE_F_DELETED)) {
		result->mf_atime = dev->mf_atime;
		result->mf_mtime = dev->mf_mtime;
		result->mf_ctime = dev->mf_ctime;
		result->mf_btime = dev->mf_btime;
	}
	result->dl_devname = incref(dev->dv_dirent);
	mfile_tslock_release(dev);
	result->fn_fsdata = (void *)prefix;
	result->fn_ino    = DEVFS_INO_DYN((uintptr_t)dev ^ (uintptr_t)prefix);
	return result;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL devicelink_dirent_v_destroy)(struct fdirent *__restrict self) {
	struct devicelink_dirent *me;
	me = container_of(self, struct devicelink_dirent, dld_ent);
	decref_unlikely(me->dld_dev);
	kfree(me);
}

PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
devicelink_dirent_v_opennode(struct fdirent *__restrict self,
                             struct fdirnode *__restrict UNUSED(dir))
		THROWS(E_BADALLOC, E_IOERROR, ...) {
	struct devicelink_dirent *me;
	me = container_of(self, struct devicelink_dirent, dld_ent);
	return devicelink_new(me->dld_pfx, me->dld_dev);
}

PRIVATE BLOCKING ATTR_PURE WUNUSED NONNULL((1, 2)) ino_t FCALL
devicelink_dirent_v_getino(struct fdirent *__restrict self,
                           struct fdirnode *__restrict UNUSED(dir))
		THROWS(E_IOERROR, ...) {
	struct devicelink_dirent *me;
	me = container_of(self, struct devicelink_dirent, dld_ent);
	return DEVFS_INO_DYN((uintptr_t)me->dld_dev ^ (uintptr_t)me->dld_pfx);
}

INTERN_CONST struct fdirent_ops const devicelink_dirent_ops = {
	.fdo_destroy  = &devicelink_dirent_v_destroy,
	.fdo_opennode = &devicelink_dirent_v_opennode,
	.fdo_getino   = &devicelink_dirent_v_getino,
};

/* Construct a new directory entry for a device symlink.
 * The caller must still initialize `return->dld_ent.fd_name' and `fd_hash' */
INTERN ATTR_RETNONNULL WUNUSED NONNULL((2, 3)) REF struct devicelink_dirent *KCALL
devicelink_dirent_new(u16 namelen, char const *pfx, struct device *__restrict dev) {
	REF struct devicelink_dirent *result;
	result = (REF struct devicelink_dirent *)kmalloc(offsetof(struct devicelink_dirent, dld_ent.fd_name) +
	                                                 (namelen + 1) * sizeof(char),
	                                                 GFP_NORMAL);

	/* Fill in fields. */
	result->dld_dev            = mfile_asdevice(incref(dev));
	result->dld_pfx            = pfx;
	result->dld_ent.fd_refcnt  = 1;
	result->dld_ent.fd_ops     = &devicelink_dirent_ops;
	result->dld_ent.fd_namelen = namelen;
	result->dld_ent.fd_type    = DT_LNK;
	return result;
}

INTERN NOBLOCK NONNULL((1)) void
NOTHROW(KCALL devenum_v_fini)(struct fdirenum *__restrict self) {
	struct devenum *me = (struct devenum *)self;
	axref_fini(&me->de_nextfil);
}

INTERN BLOCKING NONNULL((1)) pos_t KCALL
devenum_v_seekdir(struct fdirenum *__restrict self, off_t offset, unsigned int whence)
		THROWS(E_OVERFLOW, E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_IOERROR, ...) {
	pos_t result;
	struct devenum *me = (struct devenum *)self;
	switch (whence) {

		/* TODO: Full seek support by using the inode number of devices as offset.
		 *       Because we're  using an  LLRB-tree, we  can find  the first  file
		 *       with an `INO >= offset' in O(log2(N)) time. */

	case SEEK_SET: {
		REF struct fnode *dev;
		if (offset != 0)
			goto invarg;
		dev = devenum_after(NULL);
		axref_set_inherit(&me->de_nextfil, dev);
		result = 0;
	}	break;

	default:
invarg:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE,
		      whence);
		break;
	}
	return result;
}















/************************************************************************/
/* /dev/block                                                           */
/************************************************************************/
PRIVATE char const devfs_block_lnkpfx[] = "../";
PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
devfs_block_v_lookup(struct fdirnode *__restrict UNUSED(self),
                     struct flookup_info *__restrict info)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	dev_t devno = decode_devno(info->flu_name, info->flu_namelen);
	if (devno != DEV_UNSET) {
		REF struct blkdev *dev;
		dev = blkdev_lookup_bydev(devno);
		if (dev != NULL) {
			REF struct devicelink_dirent *result;
			FINALLY_DECREF_UNLIKELY(dev);
			/* Allocate a new directory entry. */
			result = devicelink_dirent_new(info->flu_namelen, devfs_block_lnkpfx, dev);
			sprintf(result->dld_ent.fd_name,
			        "%" PRIuN(__SIZEOF_MAJOR_T__) ":"
			        "%" PRIuN(__SIZEOF_MINOR_T__),
			        MAJOR(devno), MINOR(devno));
			result->dld_ent.fd_hash = fdirent_hash(result->dld_ent.fd_name,
			                                       result->dld_ent.fd_namelen);
			return &result->dld_ent;
		}
	}
	return NULL;
}

PRIVATE BLOCKING NONNULL((1)) size_t KCALL
devfs_block_enum_v_readdir(struct fdirenum *__restrict self, USER CHECKED struct dirent *buf,
                           size_t bufsize, readdir_mode_t readdir_mode, iomode_t UNUSED(mode))
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	char namebuf[COMPILER_LENOF("" PRIMAXuN(__SIZEOF_MAJOR_T__) ":"
	                            "" PRIMAXuN(__SIZEOF_MINOR_T__))];
	ssize_t result;
	u16 namelen;
	struct devenum *me = (struct devenum *)self;
	REF struct fnode *olddev, *mydev, *newdev;
again:
	olddev = axref_get(&me->de_nextfil);
	mydev  = olddev; /* Inherit reference */

	/* Find the next block device. */
	for (;;) {
		if (!mydev)
			return 0; /* EOF */
		if (fnode_isblkdev(mydev))
			break; /* Found a block device! */
		FINALLY_DECREF_UNLIKELY(mydev);
		mydev = devenum_after(mydev);
	}
	FINALLY_DECREF_UNLIKELY(mydev);

	/* Generate directory entry name. */
	namelen = (u16)sprintf(namebuf,
	                       "%" PRIuN(__SIZEOF_MAJOR_T__) ":"
	                       "%" PRIuN(__SIZEOF_MINOR_T__),
	                       MAJOR(fnode_asblkdev(mydev)->dn_devno),
	                       MINOR(fnode_asblkdev(mydev)->dn_devno));

	/* Yield directory entry. */
	result = fdirenum_feedent_ex(buf, bufsize, readdir_mode,
	                             DEVFS_INO_DYN((uintptr_t)mydev ^ (uintptr_t)devfs_block_lnkpfx),
	                             DT_LNK, namelen, namebuf);
	if (result < 0)
		return (size_t)~result; /* Don't advance directory position. */

	/* Update the nextdev field of the enumerator. */
	newdev = devenum_after(mydev);
	if (!axref_cmpxch_inherit_new(&me->de_nextfil, olddev, newdev)) {
		decref_unlikely(newdev);
		goto again;
	}
	return (size_t)result;
}


PRIVATE struct fdirenum_ops const devfs_block_enum_ops = {
	.deo_fini    = &devenum_v_fini,
	.deo_readdir = &devfs_block_enum_v_readdir,
	.deo_seekdir = &devenum_v_seekdir,
};


PRIVATE BLOCKING NONNULL((1)) void KCALL
devfs_block_v_enum(struct fdirenum *__restrict result)
		THROWS(E_IOERROR, ...) {
	struct devenum *me;
	me         = (struct devenum *)result;
	me->de_ops = &devfs_block_enum_ops;
	devenum_init(me);
}




/************************************************************************/
/* /dev/char                                                            */
/************************************************************************/
PRIVATE char const devfs_char_lnkpfx[] = "../"; /* Must be distinct from `devfs_block_lnkpfx'! */
PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
devfs_char_v_lookup(struct fdirnode *__restrict UNUSED(self),
                    struct flookup_info *__restrict info)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	dev_t devno = decode_devno(info->flu_name, info->flu_namelen);
	if (devno != DEV_UNSET) {
		REF struct chrdev *dev;
		dev = chrdev_lookup_bydev(devno);
		if (dev != NULL) {
			REF struct devicelink_dirent *result;
			FINALLY_DECREF_UNLIKELY(dev);
			/* Allocate a new directory entry. */
			result = devicelink_dirent_new(info->flu_namelen, devfs_char_lnkpfx, dev);
			sprintf(result->dld_ent.fd_name,
			        "%" PRIuN(__SIZEOF_MAJOR_T__) ":"
			        "%" PRIuN(__SIZEOF_MINOR_T__),
			        MAJOR(devno), MINOR(devno));
			result->dld_ent.fd_hash = fdirent_hash(result->dld_ent.fd_name,
			                                       result->dld_ent.fd_namelen);
			return &result->dld_ent;
		}
	}
	return NULL;
}

PRIVATE BLOCKING NONNULL((1)) size_t KCALL
devfs_char_enum_v_readdir(struct fdirenum *__restrict self, USER CHECKED struct dirent *buf,
                          size_t bufsize, readdir_mode_t readdir_mode, iomode_t UNUSED(mode))
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	char namebuf[COMPILER_LENOF("" PRIMAXuN(__SIZEOF_MAJOR_T__) ":"
	                            "" PRIMAXuN(__SIZEOF_MINOR_T__))];
	ssize_t result;
	u16 namelen;
	struct devenum *me = (struct devenum *)self;
	REF struct fnode *olddev, *mydev, *newdev;
again:
	olddev = axref_get(&me->de_nextfil);
	mydev  = olddev; /* Inherit reference */

	/* Find the next character device. */
	for (;;) {
		if (!mydev)
			return 0; /* EOF */
		if (fnode_ischrdev(mydev))
			break; /* Found a character device! */
		FINALLY_DECREF_UNLIKELY(mydev);
		mydev = devenum_after(mydev);
	}
	FINALLY_DECREF_UNLIKELY(mydev);

	/* Generate directory entry name. */
	namelen = (u16)sprintf(namebuf,
	                       "%" PRIuN(__SIZEOF_MAJOR_T__) ":"
	                       "%" PRIuN(__SIZEOF_MINOR_T__),
	                       MAJOR(fnode_aschrdev(mydev)->dn_devno),
	                       MINOR(fnode_aschrdev(mydev)->dn_devno));

	/* Yield directory entry. */
	result = fdirenum_feedent_ex(buf, bufsize, readdir_mode,
	                             DEVFS_INO_DYN((uintptr_t)mydev ^ (uintptr_t)devfs_char_lnkpfx),
	                             DT_LNK, namelen, namebuf);
	if (result < 0)
		return (size_t)~result; /* Don't advance directory position. */

	/* Update the nextdev field of the enumerator. */
	newdev = devenum_after(mydev);
	if (!axref_cmpxch_inherit_new(&me->de_nextfil, olddev, newdev)) {
		decref_unlikely(newdev);
		goto again;
	}
	return (size_t)result;
}


PRIVATE struct fdirenum_ops const devfs_char_enum_ops = {
	.deo_fini    = &devenum_v_fini,
	.deo_readdir = &devfs_char_enum_v_readdir,
	.deo_seekdir = &devenum_v_seekdir,
};


PRIVATE BLOCKING NONNULL((1)) void KCALL
devfs_char_v_enum(struct fdirenum *__restrict result)
		THROWS(E_IOERROR, ...) {
	struct devenum *me;
	me         = (struct devenum *)result;
	me->de_ops = &devfs_char_enum_ops;
	devenum_init(me);
}




/************************************************************************/
/* /dev/cpu                                                             */
/************************************************************************/
PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
devfs_cpu_v_lookup(struct fdirnode *__restrict UNUSED(self),
                   struct flookup_info *__restrict info)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	/* TODO */
	(void)info;
	COMPILER_IMPURE();
	return NULL;
}

struct cpu_enum: fdirenum {
	/* TODO */
};

PRIVATE BLOCKING NONNULL((1)) void KCALL
devfs_cpu_v_enum(struct fdirenum *__restrict result)
		THROWS(E_IOERROR, ...) {
	/* TODO */
	result->de_ops = &fdirenum_empty_ops;
}







/* Operator tables for special /dev directories. */
#define INIT_SPEC_FNODE_OPS                                                              \
	{                                                                                    \
		.no_file = {                                                                     \
			.mo_destroy = (typeoffield(struct mfile_ops, mo_destroy))(void *)-1, \
			.mo_changed = &fdirnode_v_changed,                                           \
			.mo_stream  = &devfs_spec_v_stream_ops_with_boottime,                        \
		},                                                                               \
		.no_free   = (typeoffield(struct fnode_ops, no_free))(void *)-1,      \
		.no_wrattr = &fnode_v_wrattr_noop,                                               \
	}

INTERN_CONST struct fdirnode_ops const devfs_block_ops = {
	.dno_node   = INIT_SPEC_FNODE_OPS,
	.dno_lookup = &devfs_block_v_lookup,
	.dno_enumsz = sizeof(struct devenum),
	.dno_enum   = &devfs_block_v_enum,
};

INTERN_CONST struct fdirnode_ops const devfs_char_ops  = {
	.dno_node   = INIT_SPEC_FNODE_OPS,
	.dno_lookup = &devfs_char_v_lookup,
	.dno_enumsz = sizeof(struct devenum),
	.dno_enum   = &devfs_char_v_enum,
};

INTERN_CONST struct fdirnode_ops const devfs_cpu_ops   = {
	.dno_node   = INIT_SPEC_FNODE_OPS,
	.dno_lookup = &devfs_cpu_v_lookup,
	.dno_enumsz = sizeof(struct cpu_enum),
	.dno_enum   = &devfs_cpu_v_enum,
};

#undef INIT_SPEC_FNODE_OPS

DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_DEVFS_SPEC_C */
