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
#ifndef GUARD_MODEXT2_EXT2_H
#define GUARD_MODEXT2_EXT2_H 1

#include <kernel/compiler.h>

DECL_BEGIN
struct ext2idat;
DECL_END
#define FNODE_FSDATA_T struct ext2idat

#include <kernel/fs/flat.h>
#include <kernel/fs/lnknode.h>
#include <kernel/fs/regnode.h>
#include <kernel/types.h>
#include <sched/atomic64.h>

#include <kos/sched/shared-rwlock.h>

DECL_BEGIN


/* Documentation and comments are taken from here:
 * >> https://wiki.osdev.org/Ext2
 * >> https://en.wikipedia.org/wiki/Ext2
 * >> http://www.nongnu.org/ext2-doc/ext2.html
 */

#define EXT2_FT_UNKNOWN  0 /* Unknown File Type */
#define EXT2_FT_REG_FILE 1 /* Regular File */
#define EXT2_FT_DIR      2 /* Directory File */
#define EXT2_FT_CHRDEV   3 /* Character Device */
#define EXT2_FT_BLKDEV   4 /* Block Device */
#define EXT2_FT_FIFO     5 /* Buffer File */
#define EXT2_FT_SOCK     6 /* Socket File */
#define EXT2_FT_SYMLINK  7 /* Symbolic Link */


typedef struct ATTR_PACKED {
	le32    e_total_inodes;      /* Total number of inodes in file system */
	le32    e_total_blocks;      /* Total number of blocks in file system */
	le32    e_reserved_blocks;   /* Number of blocks reserved for superuser (see `e_reserved_(u|g)id') */
	le32    e_free_blocks;       /* Total number of unallocated blocks */
	le32    e_free_inodes;       /* Total number of unallocated inodes */
	le32    e_first_blockno;     /* First block which is available for general-purpose allocation */
	le32    e_log2_blocksz;      /* log2(block_size) - 10.    (block_size == 1024 << e_log2_blocksz) */
	le32    e_log2_fragsz;       /* log2(fragment_size) - 10. (fragment_size == 1024 << e_log2_fragsz) */
	le32    e_blocks_per_group;  /* Number of blocks in each block group */
	le32    e_frags_per_group;   /* Number of fragments in each block group */
	le32    e_inodes_per_group;  /* Number of inodes in each block group */
	le32    e_last_mount;        /* Last mount time (in POSIX time; time32_t) */
	le32    e_last_write;        /* Last written time (in POSIX time; time32_t) */
	le16    e_mounts_fsck;       /* Number of times the volume has been mounted since its last consistency check (fsck) */
	le16    e_mounts_fsck_limit; /* Number of mounts allowed before a consistency check (fsck) must be done */
#define EXT2_SIGNATURE    0xef53 /* Expected signature. */
	le16    e_signature;         /* Ext2 signature (EXT2_SIGNATURE), used to help confirm the presence of Ext2 on a volume */
#define EXT2_FS_STATE_FCLEAN 0x0001 /* The filesystem is clean. */
#define EXT2_FS_STATE_FERROR 0x0002 /* The filesystem is riddled with errors. */
	le16    e_fs_state;          /* File system state (One of `EXT2_FS_STATE_F*') */
#define EXT2_ERROR_ACTION_FIGNORE     0x0001 /* Ignore errors. */
#define EXT2_ERROR_ACTION_FREMOUNT_RO 0x0002 /* Remount as read-only. */
#define EXT2_ERROR_ACTION_FPANIC      0x0003 /* Kernel panic (KOS doesn't comply with this one's demands...) */
	le16    e_error_action;      /* What to do when an error is detected (One of `EXT2_ERROR_ACTION_F*') */
	le16    e_version_minor;     /* Minor portion of version */
	le32    e_last_fsck;         /* POSIX time of last consistency check (fsck; time32_t) */
	le32    e_fsck_interval;     /* Interval (in POSIX time) between forced consistency checks (fsck; time32_t) */
#define EXT2_OS_FLINUX         0 /* Linux */
#define EXT2_OS_FGNU_HURD      1 /* GNU HURD */
#define EXT2_OS_FMASIX         2 /* Masix */
#define EXT2_OS_FFREEBSD       3 /* Free BSD */
#define EXT2_OS_FOTHER         4 /* Other */
	le32    e_os_id;             /* Operating system ID from which the filesystem on this volume was created (One of `EXT2_OS_F*') */
	le32    e_version_major;     /* Major portion of version */
	le16    e_reserved_uid;      /* User ID that can use reserved blocks */
	le16    e_reserved_gid;      /* Group ID that can use reserved blocks */
	/* Everything below only exists when `e_version_major >= 1' */
	le32    e_nonreserved_inode; /* First non-reserved inode in file system.
	                              * e_version_major < 1 --> == 11 */
	le16    e_inode_size;        /* Size of each inode structure in bytes.
	                              * e_version_major   <   1  -->   ==  128 */
	le16    e_super_blockgrp;    /* Block group that this superblock is part of (if backup copy) */
#define EXT2_FEAT_OPT_FPREALLOC_DIR 0x0001 /* Preallocate a number of blocks for newly created directories. (s.a. `e_prealloc_dir') */
#define EXT2_FEAT_OPT_FASF          0x0002 /* AFS server inodes exist. */
#define EXT2_FEAT_OPT_FJOURNAL      0x0004 /* File system has a journal. */
#define EXT2_FEAT_OPT_FEXTINODE     0x0008 /* Inodes have extended attributes. */
#define EXT2_FEAT_OPT_FRESIZABLE    0x0010 /* File system can resize itself for larger partitions. */
#define EXT2_FEAT_OPT_FHASHDIR      0x0020 /* Directories use hash index. */
	le32    e_feat_optional;     /* Optional features present (Set of `EXT2_FEAT_OPT_F*') */
#define EXT2_FEAT_REQ_FCOMPRESSION  0x0001 /* Compression is used. */
#define EXT2_FEAT_REQ_FDIRENT_TYPE  0x0002 /* Directory entries contain a type field. */
#define EXT2_FEAT_REQ_FREPLAY_JOURNAL 0x0004 /* File system needs to replay its journal. */
#define EXT2_FEAT_REQ_FJOURNAL      0x0008 /* File system uses a journal device. */
	le32    e_feat_required;     /* Required features present (Set of `EXT2_FEAT_REQ_F*') */
#define EXT2_FEAT_MRO_FSPARSE       0x0001 /* Sparse superblocks and group descriptor tables. */
#define EXT2_FEAT_MRO_FSIZE64       0x0002 /* File system uses a 64-bit file size. */
#define EXT2_FEAT_MRO_FDIRTREE      0x0004 /* Directory contents are stored in the form of a Binary Tree. */
	le32    e_feat_mountro;      /* Features that if not supported, the volume must be mounted read-only. (Set of `EXT2_FEAT_MRO_F*') */
	u8      e_fs_id[16];         /* File system ID (what is output by blkid) */
	char    e_fs_name[16];       /* Volume name (C-style string: characters terminated by a 0 byte) */
	char    e_last_mount_path[16]; /* Path volume was last mounted to (C-style string: characters terminated by a 0 byte) */
	le32    e_compression;       /* Compression algorithms used (s.a. `EXT2_FEAT_REQ_FCOMPRESSION') */
	u8      e_prealloc_files;    /* Number of blocks to preallocate for files */
	u8      e_prealloc_dir;      /* Number of blocks to preallocate for directories */
	u16   __e_pad;               /* ... */
	u8      e_journal_id[16];    /* Journal ID */
	le32    e_journal_inode;     /* Journal inode */
	le32    e_journal_device;    /* Journal device */
	le32    e_orphan;            /* Head of orphan inode list */
} Ext2DiskSuperblock;

#define EXT2_SUPERBLOCK_OFFSET  1024 /* From the start of the partition. */
#define EXT2_ROOT_DIRECTORY_INO 2    /* Root directory INode number. */


typedef u32 ext2_block_t;          /* Index of disk block (get addr via `EXT2_BLOCK2ADDR()') */
typedef u32 ext2_blocki_t;         /* Index of disk block containing an array `ext2_block_t[es_ind_blocksize]' */
typedef u32 ext2_blockii_t;        /* Index of disk block containing an array `ext2_blocki_t[es_ind_blocksize]' */
typedef u32 ext2_blockiii_t;       /* Index of disk block containing an array `ext2_blockii_t[es_ind_blocksize]' */
typedef le32 ext2_disk_block_t;    /* Same as `ext2_block_t', but uses on-disk endian encoding. */
typedef le32 ext2_disk_blocki_t;   /* Same as `ext2_blocki_t', but uses on-disk endian encoding. */
typedef le32 ext2_disk_blockii_t;  /* Same as `ext2_blockii_t', but uses on-disk endian encoding. */
typedef le32 ext2_disk_blockiii_t; /* Same as `ext2_blockiii_t', but uses on-disk endian encoding. */

typedef u32 ext2_blockid_t; /* Index of a block within a file. */
typedef u32 ext2_bgroup_t;
typedef u32 ext2_ino_t;


typedef struct ATTR_PACKED {
	/* Block group descriptor. */
	ext2_disk_block_t bg_busage;      /* Block address of a block-usage bitset. */
	ext2_disk_block_t bg_iusage;      /* Block address of an inode-usage bitset. */
	ext2_disk_block_t bg_inodes;      /* Starting block address of inode table (points to `Ext2INode') */
	le16              bg_free_blocks; /* Number of unallocated blocks in group */
	le16              bg_free_inodes; /* Number of unallocated inodes in group */
	le16              bg_num_dirs;    /* Number of directories in group */
/*	u8              __bg_unused[14];   * ... */
} Ext2DiskBlockGroup;
#define EXT2_BLOCKGROUP_SIZE 32


typedef struct ATTR_PACKED {
	/* INode data structure. */
	le16                 i_mode;       /* INode type and permissions (Identical to our `mode_t') */
	le16                 i_uid;        /* INode UID (Identical to our `uid_t') */
	le32                 i_size_low;   /* Lower 32 bits of INode size in bytes. */
	le32                 i_atime;      /* Last accessed time (`time32_t' format) */
	le32                 i_btime;      /* File birth time (`time32_t' format) */
	le32                 i_mtime;      /* File modification time (`time32_t' format) */
	le32                 i_dtime;      /* File deletion time (`time32_t' format) */
	le16                 i_gid;        /* INode GID (Identical to our gid_t') */
	le16                 i_nlink;      /* Number of hard links (Identical to our `nlink_t') */
	le32                 i_nsectors;   /* Count of disk sectors (not Ext2 blocks) in use by this inode, not
	                                    * counting the actual inode structure nor directory entries linking
	                                    * to the inode. */
#define EXT2_INODE_FSECURE_DELETE 0x00000001 /* Rewrite data and INode headers of the file a couple
                                              * of times to  prevent file  recovery upon  deletion. */
#define EXT2_INODE_FKEEP_DATA     0x00000002 /* (IGNORED) Try to preserve file data for as long as
                                              * possible  after  deletion to  allow  for undelete. */
#define EXT2_INODE_FSYNC          0x00000008 /* Changes are written to disk immediately. (same as `IO_DSYNC') */
#define EXT2_INODE_FIMMUTABLE     0x00000010 /* File contents cannot be modified. */
#define EXT2_INODE_FAPPEND        0x00000020 /* Opening  the file forces  `O_APPEND' to be used.
                                              * However, mapping the file to memory still allows
                                              * non-trailing data to be overwritten. */
#define EXT2_INODE_FDONT_DUMP     0x00000040 /* Don't include the file in filesystem dumps. */
#define EXT2_INODE_FNOATIME       0x00000080 /* The file's last-accessed time should not be updated. */
#define EXT2_INODE_FHASHDIR       0x00010000 /* Hash-indexed directory. */
#define EXT2_INODE_FAFSDIR        0x00020000 /* AFS directory. */
#define EXT2_INODE_FJOURNAL       0x00040000 /* Journal file data. */
	le32                 i_flags;      /* File flags (Set of `EXT2_INODE_F*') */
	le32                 i_os1;        /* OS-specific field #1 (RESERVED) */
#define EXT2_DIRECT_BLOCK_COUNT  12    /* Number of direct block pointers. */
	ext2_disk_block_t    i_dblock[EXT2_DIRECT_BLOCK_COUNT];
	                                   /* Direct block pointers for file data. */
	ext2_disk_blocki_t   i_siblock;    /* Single-Indirect block table. */
	ext2_disk_blockii_t  i_diblock;    /* Double-indirect block table. */
	ext2_disk_blockiii_t i_tiblock;    /* Triple-indirect block table. */
	le32                 i_generation; /* Generation number? */
	le32                 i_acl;        /* [valid_if(:->es_version >= EXT2_VERSION_1)] File ACL. */
	le32                 i_size_high;  /* [valid_if(EXT2_FEAT_MRO_FSIZE64)] High 32 bits of file size. */
	le32                 i_fragment;   /* Block address of fragment??? */
#ifdef __INTELLISENSE__
	struct ATTR_PACKED
#else /* __INTELLISENSE__ */
	union ATTR_PACKED
#endif /* !__INTELLISENSE__ */
	{
		struct ATTR_PACKED {
			u8     l_fragno;        /* Fragment number??? */
			u8     l_fragsz;        /* Fragment size??? */
			le16 __l_pad;           /* ... */
			le16   l_uid_high;      /* High 16 bits of `i_uid' */
			le16   l_gid_high;      /* High 16 bits of `i_gid' */
			le32 __l_pad2;          /* ... */
		}          i_os_linux;      /* [valid_if(:es_os == EXT2_OS_FLINUX)] */

		struct ATTR_PACKED {
			u8     h_fragno;        /* Fragment number??? */
			u8     h_fragsz;        /* Fragment size??? */
			le16   h_mode_high;     /* High 16 bits of `i_mode' */
			le16   h_uid_high;      /* High 16 bits of `i_uid' */
			le16   h_gid_high;      /* High 16 bits of `i_gid' */
			le32   h_uid_author;    /* User ID of author (if == 0xFFFFFFFF, the normal User ID will be used) */
		}          i_os_hurd;       /* [valid_if(:es_os == EXT2_OS_FGNU_HURD)] */

		struct ATTR_PACKED {
			u8     m_fragno;        /* Fragment number??? */
			u8     m_fragsz;        /* Fragment size??? */
			u8   __m_pad[10];       /* ... */
		}          i_masix;         /* [valid_if(:es_os == EXT2_OS_FMASIX)] */
		le32       i_os2[3];        /* Operating System Specific Value #2 */
	};
} Ext2DiskINode;


typedef struct ATTR_PACKED {
	/* Directory entry. */
	le32        d_ino;           /* Directory entry INO number. (Or ZERO(0) if unused/deleted) */
	le16        d_entsize;       /* Total size of the directory entry (including _all_ fields). */
#ifdef __INTELLISENSE__
	struct ATTR_PACKED
#else /* __INTELLISENSE__ */
	union ATTR_PACKED
#endif /* !__INTELLISENSE__ */
	{
		le16    d_namlen;        /* [valid_if(!(:->es_feat_required & EXT2_FEAT_REQ_FDIRENT_TYPE))]
		                          * length of the name (in characters; excluding \0) */
		struct ATTR_PACKED {
			u8  d_namlen_low;    /* Low 8 bits of the name length. */
			u8  d_type;          /* Entry type (One of `EXT2_FT_*'). */
		};
	};
//	char        d_name[1];       /* The directory entry name. */
} Ext2DiskDirent;



struct ext2iblock {
	ext2_disk_block_t eib_blocks[0]; /* [es_ind_blocksize] Direct block pointers (Or `0' if not allocated) */
};
#define ext2iblock_sizeof(es_ind_blocksize) (sizeof(ext2_disk_block_t) * (es_ind_blocksize))
#define ext2iblock_blocks(self)             ((self)->eib_blocks)

struct ext2iiblock {
	struct ext2iblock *eiib_blocks_c[0]; /* [0..1][owned][NULL_if(eiib_blocks[i] != 0)][es_ind_blocksize]
	                                      * [lock(ei_lock)] Lazily allocated, in-sync mirrors of `eiib_blocks[i]' */
/*	ext2_disk_blocki_t eiib_blocks[0];    * [es_ind_blocksize] Single-Indirect block table. (Or `0' if not allocated) */
};
#define ext2iiblock_sizeof(es_ind_blocksize)       ((sizeof(struct ext2iblock *) + sizeof(ext2_disk_blocki_t)) * (es_ind_blocksize))
#define ext2iiblock_blocks(self, es_ind_blocksize) ((ext2_disk_blocki_t *)&(self)->eiib_blocks_c[es_ind_blocksize])

struct ext2iiiblock {
	struct ext2iiblock *eiiib_blocks_c[0]; /* [0..1][owned][NULL_if(eiiib_blocks[i] != 0)][es_ind_blocksize]
	                                        * [lock(ei_lock)] Lazily allocated, in-sync mirrors of `eiiib_blocks[i]' */
/*	ext2_disk_blockii_t eiiib_blocks[0];    * [es_ind_blocksize] Double-indirect block table. (Or `0' if not allocated) */
};
#define ext2iiiblock_sizeof(es_ind_blocksize)       ((sizeof(struct ext2iiblock *) + sizeof(ext2_disk_blockii_t)) * (es_ind_blocksize))
#define ext2iiiblock_blocks(self, es_ind_blocksize) ((ext2_disk_blockii_t *)&(self)->eiiib_blocks_c[es_ind_blocksize])



struct ext2idat {
	pos_t                ei_inoaddr;   /* [const] On-disk address of associated `Ext2DiskINode' */
	struct shared_rwlock ei_lock;      /* Lock for fields below */
	ext2_blockid_t       ei_blocks;    /* [lock(ei_lock)] # of allocated EXT2 blocks in use. (NOT THE SAME AS `i_nsectors'!) */
	ext2_block_t         ei_dblock[EXT2_DIRECT_BLOCK_COUNT];
	                                   /* [lock(ei_lock)] Direct block pointers for file data. (Or `0' if not allocated) */
	ext2_blocki_t        ei_siblock;   /* [lock(ei_lock)] Single-Indirect block table. (Or `0' if not allocated) */
	ext2_blockii_t       ei_diblock;   /* [lock(ei_lock)] Double-indirect block table. (Or `0' if not allocated) */
	ext2_blockiii_t      ei_tiblock;   /* [lock(ei_lock)] Triple-indirect block table. (Or `0' if not allocated) */
	struct ext2iblock   *ei_siblock_c; /* [0..1][NULL_if(ei_siblock != 0)][lock(ei_lock)] Lazily allocated, in-sync mirror of `ei_siblock' */
	struct ext2iiblock  *ei_diblock_c; /* [0..1][NULL_if(ei_diblock != 0)][lock(ei_lock)] Lazily allocated, in-sync mirror of `ei_diblock' */
	struct ext2iiiblock *ei_tiblock_c; /* [0..1][NULL_if(ei_tiblock != 0)][lock(ei_lock)] Lazily allocated, in-sync mirror of `ei_tiblock' */
};

/* Helpers for accessing `struct ext2idat::ei_lock' */
#define /*        */ _ext2idat_reap(self)        (void)0
#define /*        */ ext2idat_reap(self)         (void)0
#define /*        */ ext2idat_mustreap(self)     0
#define /*BLOCKING*/ ext2idat_write(self)        shared_rwlock_write(&(self)->ei_lock)
#define /*BLOCKING*/ ext2idat_write_nx(self)     shared_rwlock_write_nx(&(self)->ei_lock)
#define /*        */ ext2idat_trywrite(self)     shared_rwlock_trywrite(&(self)->ei_lock)
#define /*        */ ext2idat_endwrite(self)     (shared_rwlock_endwrite(&(self)->ei_lock), ext2idat_reap(self))
#define /*        */ _ext2idat_endwrite(self)    shared_rwlock_endwrite(&(self)->ei_lock)
#define /*BLOCKING*/ ext2idat_read(self)         shared_rwlock_read(&(self)->ei_lock)
#define /*BLOCKING*/ ext2idat_read_nx(self)      shared_rwlock_read_nx(&(self)->ei_lock)
#define /*        */ ext2idat_tryread(self)      shared_rwlock_tryread(&(self)->ei_lock)
#define /*        */ _ext2idat_endread(self)     shared_rwlock_endread(&(self)->ei_lock)
#define /*        */ ext2idat_endread(self)      (void)(shared_rwlock_endread(&(self)->ei_lock) && (ext2idat_reap(self), 0))
#define /*        */ _ext2idat_end(self)         shared_rwlock_end(&(self)->ei_lock)
#define /*        */ ext2idat_end(self)          (void)(shared_rwlock_end(&(self)->ei_lock) && (ext2idat_reap(self), 0))
#define /*BLOCKING*/ ext2idat_upgrade(self)      shared_rwlock_upgrade(&(self)->ei_lock)
#define /*        */ ext2idat_tryupgrade(self)   shared_rwlock_tryupgrade(&(self)->ei_lock)
#define /*        */ ext2idat_downgrade(self)    shared_rwlock_downgrade(&(self)->ei_lock)
#define /*        */ ext2idat_reading(self)      shared_rwlock_reading(&(self)->ei_lock)
#define /*        */ ext2idat_writing(self)      shared_rwlock_writing(&(self)->ei_lock)
#define /*        */ ext2idat_canread(self)      shared_rwlock_canread(&(self)->ei_lock)
#define /*        */ ext2idat_canwrite(self)     shared_rwlock_canwrite(&(self)->ei_lock)
#define /*BLOCKING*/ ext2idat_waitread(self)     shared_rwlock_waitread(&(self)->ei_lock)
#define /*BLOCKING*/ ext2idat_waitwrite(self)    shared_rwlock_waitwrite(&(self)->ei_lock)
#define /*BLOCKING*/ ext2idat_waitread_nx(self)  shared_rwlock_waitread_nx(&(self)->ei_lock)
#define /*BLOCKING*/ ext2idat_waitwrite_nx(self) shared_rwlock_waitwrite_nx(&(self)->ei_lock)


struct ext2regnode: fregnode {
	struct ext2idat ern_fdat; /* Fat node data. */
};

struct ext2lnknode: flnknode {
	struct ext2idat eln_fdat; /* Fat node data. */
};

struct ext2dirnode: flatdirnode {
	struct ext2idat edn_fdat; /* Fat node data. */
	atomic64_t      edn_1dot; /* [lock(ATOMIC && WRITE_ONCE)] Position of "." entry in directory stream (or `(uint64_t)-1' if unknown). */
	atomic64_t      edn_2dot; /* [lock(ATOMIC && WRITE_ONCE)] Position of ".." entry in directory stream (or `(uint64_t)-1' if unknown). */
};
#define ext2dirnode_assuper(self) \
	flatsuper_asext2(flatdirnode_assuper((struct flatdirnode *)(self)))


#define ext2super_blocks2sectors(self, num_blocks) \
	((uint32_t)((((uint64_t)(num_blocks) << (self)->es_blockshift) + (self)->es_blockmask) >> (self)->es_super.ffs_super.fs_dev->mf_blockshift))
#define ext2super_sectors2blocks(self, num_sectors) \
	((uint32_t)(((uint64_t)(num_sectors) << (self)->es_super.ffs_super.fs_dev->mf_blockshift)) >> (self)->es_blockshift)

struct ext2super {
	ext2_block_t        es_blk_per_bgrp;  /* [!0][const] Blocks per block group. */
	ext2_ino_t          es_ino_per_bgrp;  /* [!0][const] Inodes per block group. */
	ext2_block_t        es_total_blocks;  /* [!0][const] Total number of blocks. */
	size_t              es_inode_size;    /* [>= 128][const] Size of a single INode (in bytes). */
	size_t              es_inode_io_size; /* [>= 128 && <= sizeof(Ext2DiskINode)][const] INode I/O size. */
	ext2_ino_t          es_total_inodes;  /* [!0][const] Total number of INodes.
	                                       * NOTE: Since the first valid INode number is ONE(1), this
	                                       *       field  doubles as the greatest valid INode number. */
	u32                 es_version_maj;   /* [const] EXT2 version number */
	u16                 es_version_min;   /* [const] EXT2 version number */
	u32                 es_feat_optional; /* [const] Optional features in use (Set of `EXT2_FEAT_OPT_F*') */
	u32                 es_feat_required; /* [const] Required features in use (Set of `EXT2_FEAT_REQ_F*') */
	u32                 es_feat_mountro;  /* [const] Mount-ro features in use (Set of `EXT2_FEAT_MRO_F*') */
	u32                 es_os;            /* [const] Operating system that was used to create the superblock (One of `EXT2_OS_F*'). */
#ifdef __INTELLISENSE__
	shift_t             es_blockshift;    /* [const] Shift to convert block numbers into absolute on-disk locations. */
#else /* __INTELLISENSE__ */
#define es_blockshift   es_super.ffs_super.fs_root.mf_blockshift
#endif /* !__INTELLISENSE__ */
	size_t              es_iobalign;      /* [const][== 1 << es_super.ffs_super.fs_dev->mf_iobashift] */
	size_t              es_blockmask;     /* [const][== (1 << es_blockshift) - 1] Size of a block (in bytes) minus 1. */
	size_t              es_blocksize;     /* [const][== (1 << es_blockshift)] Size of a block (in bytes). */
	size_t              es_ind_blocksize; /* [const][== (1 << es_blockshift) / 4] Number of entries in an indirect block pointer block. */
	size_t              es_ind_blocksize_p2; /* [const][== es_ind_blocksize * es_ind_blocksize] */
	size_t              es_ind_blocksize_p3; /* [const][== es_ind_blocksize * es_ind_blocksize * es_ind_blocksize] */
	ext2_bgroup_t       es_bgroupc;       /* [!0][const] The total number of block groups. */
	Ext2DiskBlockGroup *es_bgroupv;       /* [0..es_bgroupc][const][owned] Read/Write memory mapping of the superblock's block-group table. */
	void               *es_freebgroupv;   /* [1..1][const][owned] Token used to munmap() `es_bgroupv' during destruction (only used during destruction) */
	struct flatsuper    es_super;         /* Underlying superblock */
	struct ext2idat     es_fdat;          /* Superblock fs-specific file data. */
	atomic64_t         _es_1dot;          /* s.a. `struct ext2dirnode::edn_1dot' */
	atomic64_t         _es_2dot;          /* s.a. `struct ext2dirnode::edn_2dot' */
};
#define flatsuper_asext2(self)     COMPILER_CONTAINER_OF(self, struct ext2super, es_super)
#define fsuper_asext2(self)        COMPILER_CONTAINER_OF(self, struct ext2super, es_super.ffs_super)
#define fdirnode_asext2super(self) COMPILER_CONTAINER_OF(self, struct ext2super, es_super.ffs_super.fs_root)
#define fnode_asext2super(self)    fdirnode_asext2super(fnode_asdir(self))
#define mfile_asext2super(self)    fdirnode_asext2super(mfile_asdir(self))

/* Convert block addresses to on-disk locations, as well as the opposite.
 * Also  used  to  convert  in-file  addresses  to  their  block indices. */
#define EXT2_BLOCK2ADDR(self, block) ((pos_t)(block) << (self)->es_blockshift)
#define EXT2_ADDR2BLOCK(self, addr)  ((ext2_block_t)((addr) >> (self)->es_blockshift))

/* Return the block group index associated with a given INode. */
#define EXT2_INO_BGRP_INDEX(self, ino) ((ext2_bgroup_t)((ext2_ino_t)((ino)-1) / (self)->es_ino_per_bgrp))

/* Return the offset into a block group of a given INode. */
#define EXT2_INO_BGRP_OFFSET(self, ino) ((ext2_ino_t)((ext2_ino_t)((ino)-1) % (self)->es_ino_per_bgrp))

DECL_END

#endif /* !GUARD_MODEXT2_EXT2_H */
