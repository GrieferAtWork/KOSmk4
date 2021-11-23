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

#include <kernel/compiler.h>

#include <kernel/fs/constdir.h>
#include <kernel/fs/devfs-spec.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/node.h>
#include <kernel/mman/mfile.h>
#include <sched/tsc.h>

#include <sys/stat.h>

#include <stddef.h>

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





/************************************************************************/
/* /dev/block                                                           */
/************************************************************************/
PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
devfs_block_lookup(struct fdirnode *__restrict UNUSED(self),
                   struct flookup_info *__restrict info)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	/* TODO */
	(void)info;
	COMPILER_IMPURE();
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
PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
devfs_char_lookup(struct fdirnode *__restrict UNUSED(self),
                  struct flookup_info *__restrict info)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	/* TODO */
	(void)info;
	COMPILER_IMPURE();
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
