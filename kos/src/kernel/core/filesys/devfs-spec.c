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
#include <kernel/malloc.h>
#include <kernel/mman/mfile.h>
#include <sched/atomic64.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/overflow.h>

#include <kos/dev.h>
#include <sys/stat.h>

#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

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
	result->st_atim.tv_sec  = (typeof(result->st_atim.tv_sec))boottime.tv_sec;
	result->st_atim.tv_nsec = (typeof(result->st_atim.tv_nsec))boottime.tv_nsec;
	result->st_mtim.tv_sec  = (typeof(result->st_mtim.tv_sec))boottime.tv_sec;
	result->st_mtim.tv_nsec = (typeof(result->st_mtim.tv_nsec))boottime.tv_nsec;
	result->st_ctim.tv_sec  = (typeof(result->st_ctim.tv_sec))boottime.tv_sec;
	result->st_ctim.tv_nsec = (typeof(result->st_ctim.tv_nsec))boottime.tv_nsec;
	fdirnode_v_stat(self, result);
}

PRIVATE struct mfile_stream_ops const devfs_spec_v_stream_ops_with_boottime = {
	.mso_open  = &fdirnode_v_open,
	.mso_stat  = &devfs_spec_v_stat_with_boottime,
	.mso_ioctl = &fdirnode_v_ioctl,
	.mso_hop   = &fdirnode_v_hop,
};


/* Decode a string such as "4:5" into a devno.
 * When the given `name' can't be decoded as such, return `DEV_UNSET' */
PRIVATE WUNUSED NONNULL((1)) dev_t KCALL
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
	do {
		ch = *name++;
		if ((ch >= '1' && ch <= '9') ||
		    (ch == '0' && minor != 0)) {
			if (OVERFLOW_UMUL(minor, 10, &minor) ||
			    OVERFLOW_UADD(minor, ch - '0', &minor))
				goto err;
		} else {
			goto err;
		}
	} while (name < end);
	if (major > MAJORMASK)
		goto err;
	if (minor > MINORMASK)
		goto err;
	return MKDEV(major, minor);
err:
	return DEV_UNSET;
}


/* Symlink file node that expands to the name of a device
 * `dl_devname', prefixed by `(char const *)fn_fsdata' */
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
		.no_free   = (void(KCALL *)(struct fnode *__restrict))(void *)-1,
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
	}
	result->dl_devname = incref(dev->dv_dirent);
	mfile_tslock_release(dev);
	result->fn_fsdata = (void *)prefix;
	result->fn_ino    = DEVFS_INO_DYN((uintptr_t)dev ^ (uintptr_t)prefix);
	return result;
}

struct devicelink_dirent {
	char const        *dld_pfx; /* [1..1][const] Prefix for link strings. */
	REF struct device *dld_dev; /* [1..1][const] Pointed-to device. */
	struct fdirent     dld_ent; /* Underlying directory entry */
};

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

PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) ino_t FCALL
devicelink_dirent_v_getino(struct fdirent *__restrict self,
                           struct fdirnode *__restrict UNUSED(dir))
		THROWS(E_IOERROR, ...) {
	struct devicelink_dirent *me;
	me = container_of(self, struct devicelink_dirent, dld_ent);
	return DEVFS_INO_DYN((uintptr_t)me->dld_dev ^ (uintptr_t)me->dld_pfx);
}

PRIVATE struct fdirent_ops const devicelink_dirent_ops = {
	.fdo_destroy  = &devicelink_dirent_v_destroy,
	.fdo_opennode = &devicelink_dirent_v_opennode,
	.fdo_getino   = &devicelink_dirent_v_getino,
};

/* Construct a new directory entry for a device symlink.
 * The caller must still initialize `return->dld_ent.fd_name' and `fd_hash' */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((2, 3)) REF struct devicelink_dirent *KCALL
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











/************************************************************************/
/* /dev/block                                                           */
/************************************************************************/
PRIVATE char const devfs_block_lnkpfx[] = "../";
PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
devfs_block_lookup(struct fdirnode *__restrict UNUSED(self),
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
			        "%" PRIuN(__SIZEOF_MAJOR_T__) ":%" PRIuN(__SIZEOF_MINOR_T__),
			        MAJOR(devno), MINOR(devno));
			result->dld_ent.fd_hash = fdirent_hash(result->dld_ent.fd_name,
			                                       result->dld_ent.fd_namelen);
			return &result->dld_ent;
		}
	}
	return NULL;
}

struct block_enum: fdirenum {
	/* TODO */
};

PRIVATE BLOCKING NONNULL((1)) void KCALL
devfs_block_dno_enum(struct fdirenum *__restrict result)
		THROWS(E_IOERROR, ...) {
	/* TODO */
	result->de_ops = &fdirenum_empty_ops;
}




/************************************************************************/
/* /dev/char                                                            */
/************************************************************************/
PRIVATE char const devfs_char_lnkpfx[] = "../"; /* Must be distinct from `devfs_block_lnkpfx'! */
PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
devfs_char_lookup(struct fdirnode *__restrict UNUSED(self),
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
			        "%" PRIuN(__SIZEOF_MAJOR_T__) ":%" PRIuN(__SIZEOF_MINOR_T__),
			        MAJOR(devno), MINOR(devno));
			result->dld_ent.fd_hash = fdirent_hash(result->dld_ent.fd_name,
			                                       result->dld_ent.fd_namelen);
			return &result->dld_ent;
		}
	}
	return NULL;
}

struct char_enum: fdirenum {
	/* TODO */
};

PRIVATE BLOCKING NONNULL((1)) void KCALL
devfs_char_dno_enum(struct fdirenum *__restrict result)
		THROWS(E_IOERROR, ...) {
	/* TODO */
	result->de_ops = &fdirenum_empty_ops;
}




/************************************************************************/
/* /dev/cpu                                                             */
/************************************************************************/
PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
devfs_cpu_lookup(struct fdirnode *__restrict UNUSED(self),
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
devfs_cpu_dno_enum(struct fdirenum *__restrict result)
		THROWS(E_IOERROR, ...) {
	/* TODO */
	result->de_ops = &fdirenum_empty_ops;
}




/************************************************************************/
/* /dev/disk                                                             */
/************************************************************************/
PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
devfs_disk_lookup(struct fdirnode *__restrict UNUSED(self),
                  struct flookup_info *__restrict info)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	/* TODO */
	(void)info;
	COMPILER_IMPURE();
	return NULL;
}

struct disk_enum: fdirenum {
	/* TODO */
};

PRIVATE BLOCKING NONNULL((1)) void KCALL
devfs_disk_dno_enum(struct fdirenum *__restrict result)
		THROWS(E_IOERROR, ...) {
	/* TODO */
	result->de_ops = &fdirenum_empty_ops;
}







/* Operator tables for special /dev directories. */
#define INIT_SPEC_FNODE_OPS                                                     \
	{                                                                           \
		.no_file = {                                                            \
			.mo_destroy = (void(KCALL *)(struct mfile *__restrict))(void *)-1,  \
			.mo_changed = &fdirnode_v_changed,                                  \
			.mo_stream  = &devfs_spec_v_stream_ops_with_boottime,               \
		},                                                                      \
		.no_free   = (void(KCALL *)(struct fnode *__restrict))(void *)-1,       \
		.no_wrattr = &fnode_v_wrattr_noop,                                      \
	}

INTERN_CONST struct fdirnode_ops const devfs_block_ops = {
	.dno_node   = INIT_SPEC_FNODE_OPS,
	.dno_lookup = &devfs_block_lookup,
	.dno_enumsz = sizeof(struct block_enum),
	.dno_enum   = &devfs_block_dno_enum,
};

INTERN_CONST struct fdirnode_ops const devfs_char_ops  = {
	.dno_node   = INIT_SPEC_FNODE_OPS,
	.dno_lookup = &devfs_char_lookup,
	.dno_enumsz = sizeof(struct char_enum),
	.dno_enum   = &devfs_char_dno_enum,
};

INTERN_CONST struct fdirnode_ops const devfs_cpu_ops   = {
	.dno_node   = INIT_SPEC_FNODE_OPS,
	.dno_lookup = &devfs_cpu_lookup,
	.dno_enumsz = sizeof(struct cpu_enum),
	.dno_enum   = &devfs_cpu_dno_enum,
};

INTERN_CONST struct fdirnode_ops const devfs_disk_ops  = {
	.dno_node   = INIT_SPEC_FNODE_OPS,
	.dno_lookup = &devfs_disk_lookup,
	.dno_enumsz = sizeof(struct disk_enum),
	.dno_enum   = &devfs_disk_dno_enum,
};

#undef INIT_SPEC_FNODE_OPS

DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_DEVFS_SPEC_C */
