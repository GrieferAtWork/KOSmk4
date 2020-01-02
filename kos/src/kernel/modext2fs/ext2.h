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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODEXT2FS_EXT2_H
#define GUARD_MODEXT2FS_EXT2_H 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <kernel/types.h>
#include <sched/rwlock.h>

DECL_BEGIN


/* Documentation and comments are taken from here:
 * >> https://wiki.osdev.org/Ext2
 */

typedef struct ATTR_PACKED {
	le32    e_total_inodes;      /* Total number of inodes in file system */
	le32    e_total_blocks;      /* Total number of blocks in file system */
	le32    e_reserved_blocks;   /* Number of blocks reserved for superuser (see `e_reserved_(u|g)id') */
	le32    e_free_blocks;       /* Total number of unallocated blocks */
	le32    e_free_inodes;       /* Total number of unallocated inodes */
	le32    e_super_blockno;     /* Block number of the block containing the superblock */
	le32    e_log2_blocksz;      /* log2 (block_size) - 10.    (block_size == 1024 << e_log2_blocksz) */
	le32    e_log2_fragsz;       /* log2 (fragment_size) - 10. (fragment_size == 1024 << e_log2_fragsz) */
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
	le16    e_version_major;     /* Major portion of version */
	le16    e_reserved_uid;      /* User ID that can use reserved blocks */
	le16    e_reserved_gid;      /* Group ID that can use reserved blocks */
	/* Everything below only exists when `e_version_major >= 1' */
	le32    e_nonreserved_inode; /* First non-reserved inode in file system.
	                              * e_version_major < 1 --> == 11 */
	le16    e_inode_size;        /* Size of each inode structure in bytes.
	                              * e_version_major < 1 --> == 128 */
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


typedef u32 ext2_block_t;
typedef u32 ext2_blockid_t; /* Index of a block within a file. */
typedef u32 ext2_bgroup_t;
typedef u32 ext2_ino_t;


typedef struct ATTR_PACKED {
	/* Block group descriptor. */
	le32    bg_busage;           /* [TYPE(ext2_block_t)] Block address of a block-usage bitset. */
	le32    bg_iusage;           /* [TYPE(ext2_block_t)] Block address of an inode-usage bitset. */
	le32    bg_inodes;           /* [TYPE(ext2_block_t -> Ext2INode)] Starting block address of inode table */
	le16    bg_free_blocks;      /* Number of unallocated blocks in group */
	le16    bg_free_inodes;      /* Number of unallocated inodes in group */
	le16    bg_num_dirs;         /* Number of directories in group */
/*	u8    __bg_unused[14];        * ... */
} Ext2DiskBlockGroup;
#define EXT2_BLOCKGROUP_SIZE   32


typedef struct ATTR_PACKED {
	/* INode data structure. */
	le16    i_mode;              /* INode type and permissions (Identical to our `mode_t i_attr.a_mode' field) */
	le16    i_uid;               /* INode UID (Identical to our `mode_t i_attr.a_uid' field) */
	le32    i_size_low;          /* Lower 32 bits of INode size in bytes. */
	le32    i_atime;             /* Last accessed time (`time32_t' format) */
	le32    i_ctime;             /* File creation time (`time32_t' format) */
	le32    i_mtime;             /* File modification time (`time32_t' format) */
	le32    i_dtime;             /* File deletion time (`time32_t' format) */
	le16    i_gid;               /* INode GID (Identical to our `mode_t i_attr.a_gid' field) */
	le16    i_nlink;             /* Number of hard links (Identical to our `mode_t i_nlink' field) */
	le32    i_blocks;            /* Count of disk sectors (not Ext2 blocks) in use by this inode, not
	                              * counting the actual inode structure nor directory entries linking
	                              * to the inode. */
#define EXT2_INODE_FSECURE_DELETE 0x00000001 /* Rewrite data and INode headers of the file a couple
	                                          * of times to prevent file recovery upon deletion. */
#define EXT2_INODE_FKEEP_DATA     0x00000002 /* (IGNORED) Try to preserve file data for as long as
	                                          * possible after deletion to allow for undelete. */
#define EXT2_INODE_FSYNC          0x00000008 /* Changes are written to disk immediately. (same as `IO_SYNC') */
#define EXT2_INODE_FIMMUTABLE     0x00000010 /* File contents cannot be modified. */
#define EXT2_INODE_FAPPEND        0x00000020 /* Opening the file forces `O_APPEND' to be used.
	                                          * However, mapping the file to memory still allows
	                                          * non-trailing data to be overwritten. */
#define EXT2_INODE_FDONT_DUMP     0x00000040 /* Don't include the file in filesystem dumps. */
#define EXT2_INODE_FNOATIME       0x00000080 /* The file's last-accessed time should not be updated. */
#define EXT2_INODE_FHASHDIR       0x00010000 /* Hash-indexed directory. */
#define EXT2_INODE_FAFSDIR        0x00020000 /* AFS directory. */
#define EXT2_INODE_FJOURNAL       0x00040000 /* Journal file data. */
	le32    i_flags;             /* File flags (Set of `EXT2_INODE_F*') */
	le32    i_os1;               /* OS-specific field #1 (RESERVED) */
#define EXT2_DIRECT_BLOCK_COUNT  12 /* Number of direct block pointers. */
	le32    i_dblock[EXT2_DIRECT_BLOCK_COUNT];
	                             /* [TYPE(ext2_block_t)] Direct block pointers for file data. */
	le32    i_siblock;           /* [TYPE(ext2_block_t)] Pointer to a block filled with `ext2_block_t[:sd_ind_blocksize]'. */
	le32    i_diblock;           /* [TYPE(ext2_block_t)] Pointer to a block filled with `i_siblock[:sd_ind_blocksize]'. */
	le32    i_tiblock;           /* [TYPE(ext2_block_t)] Pointer to a block filled with `i_diblock[:sd_ind_blocksize]'. */
	le32    i_generation;        /* Generation number? */
	le32    i_acl;               /* [valid_if(:->sd_version >= EXT2_VERSION_1)] File ACL. */
	le32    i_size_high;         /* [valid_if(EXT2_FEAT_MRO_FSIZE64)] High 32 bits of file size. */
	le32    i_fragment;          /* Block address of fragment??? */
#ifdef __INTELLISENSE__
	struct ATTR_PACKED
#else
	union ATTR_PACKED
#endif
	{
		struct ATTR_PACKED {
			u8     l_fragno;        /* Fragment number??? */
			u8     l_fragsz;        /* Fragment size??? */
			le16 __l_pad;           /* ... */
			le16   l_uid_high;      /* High 16 bits of `i_uid' */
			le16   l_gid_high;      /* High 16 bits of `i_gid' */
			le32 __l_pad2;          /* ... */
		}          i_os_linux;      /* [valid_if(:sd_os == EXT2_OS_FLINUX)] */
		struct ATTR_PACKED {
			u8     h_fragno;        /* Fragment number??? */
			u8     h_fragsz;        /* Fragment size??? */
			le16   h_mode_high;     /* High 16 bits of `i_mode' */
			le16   h_uid_high;      /* High 16 bits of `i_uid' */
			le16   h_gid_high;      /* High 16 bits of `i_gid' */
			le32   h_uid_author;    /* User ID of author (if == 0xFFFFFFFF, the normal User ID will be used) */
		}          i_os_hurd;       /* [valid_if(:sd_os == EXT2_OS_FGNU_HURD)] */
		struct ATTR_PACKED {
			u8     m_fragno;        /* Fragment number??? */
			u8     m_fragsz;        /* Fragment size??? */
			u8   __m_pad[10];       /* ... */
		}          i_masix;         /* [valid_if(:sd_os == EXT2_OS_FMASIX)] */
		le32       i_os2[3];        /* Operating System Specific Value #2 */
	};
} Ext2DiskINode;


typedef struct ATTR_PACKED {
	/* Directory entry. */
	le32        d_ino;           /* Directory entry INO number. (Or ZERO(0) if unused/deleted) */
	le16        d_entsize;       /* Total size of the directory entry (including _all_ fields). */
#ifdef __INTELLISENSE__
	struct ATTR_PACKED
#else
	union ATTR_PACKED
#endif
	{
		le16    d_namlen;        /* [valid_if(!(:->sd_feat_required & EXT2_FEAT_REQ_FDIRENT_TYPE))]
									* length of the name (in characters; excluding \0) */
		struct ATTR_PACKED {
			u8  d_namlen_low;    /* Low 8 bits of the name length. */
			u8  d_type;          /* Entry type (One of `DT_*'). */
		};
	};
//  char        d_name[1];       /* The directory entry name. */
} Ext2DiskDirent;







typedef struct block_group Ext2BlockGroup;
struct block_group {
	/* Block group descriptor. */
	struct rwlock bg_lock;
	ext2_block_t  bg_busage_addr;  /* [valid_if(BLOCK_GROUP_FLOADED)][const]
	                                * Block address of a block-usage bitset with `:sd_blk_per_bgrp' elements.
	                                * 1-bits are currently in use (allocated), and ZERO-bits are free.
	                                * The blocks referred to are calculated as `INDEX_OF(:sd_groups,self) * sd_blk_per_bgrp' */
	ext2_block_t  bg_iusage_addr;  /* [valid_if(BLOCK_GROUP_FLOADED)][const]
	                                * Block address of an inode-usage bitset with `:sd_ino_per_bgrp' elements.
	                                * 1-bits are currently in use (allocated), and ZERO-bits are free. * */
	ext2_block_t  bg_inodes;       /* [valid_if(BLOCK_GROUP_FLOADED)][const]
	                                * Block address of an `Ext2INode[:sd_ino_per_bgrp]' array. */
	u16           bg_free_blocks;  /* [valid_if(BLOCK_GROUP_FLOADED)] Number of unallocated blocks in group */
	u16           bg_free_inodes;  /* [valid_if(BLOCK_GROUP_FLOADED)] Number of unallocated inodes in group */
	u16           bg_num_dirs;     /* [valid_if(BLOCK_GROUP_FLOADED)] Number of allocated directory INodes in group. */
#define BLOCK_GROUP_FNORMAL 0x0000 /* Normal block group flags. */
#define BLOCK_GROUP_FLOADED 0x0001 /* [WRITE_ONCE] Data on the block group has been read from disk. */
#define BLOCK_GROUP_FCHANGE 0x0002 /* One of the non-constant fields loaded by `BLOCK_GROUP_FLOADED' has been changed. */
#define BLOCK_GROUP_FBCHANG 0x0004 /* The block-usage bitset has been changed. */
#define BLOCK_GROUP_FICHANG 0x0008 /* The INode-usage bitset has been changed. */
	u16           bg_flags;        /* Block group flags (Set of `BLOCK_GROUP_F*') */
#if __SIZEOF_POINTER__ > 4
	u32         __bg_pad2;         /* ... */
#endif
	byte_t       *bg_busage;       /* [0..:sd_blk_per_bgrp/8][owned] Bitset of allocated blocks in this group.
	                                * This vector is lazily allocated and read from disk upon first access.
	                                * Note however that it does not follow WRITE_ONCE rules, so you need to
	                                * be holding a read-lock on `bg_lock' if you wish to dereference this vector.
	                                * (Anything else would make sense either, considering that the bitset
	                                * contained could change at any time if you aren't holding that lock)
	                                * When `BLOCK_GROUP_FBCHANG' flag has been set, this vector differs from its on-disk shadow. */
	byte_t       *bg_iusage;       /* [0..:sd_ino_per_bgrp/8][owned] Bitset of allocated Inodes in this group.
	                                * Lazily allocated the same way `bg_busage' is.
	                                * When `BLOCK_GROUP_FICHANG' flag has been set, this vector differs from its on-disk shadow. */
};

typedef struct ext2_superblock Ext2Superblock;
struct ext2_superblock: public superblock {
	pos_t               sd_bgroups_pos;   /* [const] The absolute on-disk position of the block group table. */
	ext2_bgroup_t       sd_bgroups_cnt;   /* [!0][const] The total number of block groups. */
	ext2_block_t        sd_blk_per_bgrp;  /* [!0][const] Blocks per block group. */
	ext2_ino_t          sd_ino_per_bgrp;  /* [!0][const] Inodes per block group. */
	ext2_block_t        sd_total_blocks;  /* [!0][const] Total number of blocks. */
	size_t              sd_inode_size;    /* [>= 128][const] Size of a single INode (in bytes). */
	ext2_ino_t          sd_total_inodes;  /* [!0][const] Total number of INodes.
	                                       * NOTE: Since the first valid INode number is ONE(1), this
	                                       *       field doubles as the greatest valid INode number. */
#define EXT2_VERSION_0  0x00000000        /* Ext2 version 0 */
#define EXT2_VERSION_1  0x00010000        /* Ext2 version 1.0 */
	u32                 sd_version;       /* [const] EXT2 version number (major << 16 | minor) */
	u32                 sd_feat_optional; /* [const] Optional features in use (Set of `EXT2_FEAT_OPT_F*') */
	u32                 sd_feat_required; /* [const] Required features in use (Set of `EXT2_FEAT_REQ_F*') */
	u32                 sd_feat_mountro;  /* [const] Mount-ro features in use (Set of `EXT2_FEAT_MRO_F*') */
	unsigned int        sd_os;            /* [const] Operating system that was used to create the superblock (One of `EXT2_OS_F*'). */
#ifndef CONFIG_VM_DATABLOCK_MIN_PAGEINFO
#define sd_block_shift  db_addrshift      /* [const] Shift applied to block numbers to convert
	                                       *         them into absolute on-disk locations. */
#define sd_blocksize    db_pagesize       /* [const][== 1 << sd_block_shift] Size of a single block (in bytes) */
#else /* !CONFIG_VM_DATABLOCK_MIN_PAGEINFO */
	unsigned int        sd_block_shift;   /* [const] Shift applied to block numbers to convert
	                                       *         them into absolute on-disk locations. */
	size_t              sd_blocksize;     /* [const][== 1 << sd_block_shift] Size of a single block (in bytes) */
#endif /* CONFIG_VM_DATABLOCK_MIN_PAGEINFO */
	size_t              sd_blockmask;     /* [const][== sd_blocksize-1] Block mask for extracting the offset within a block. */
	size_t              sd_ind_blocksize; /* [const][== sd_blocksize / 4] Number of entries in an indirect block pointer block. */
	struct block_group *sd_groups;        /* [1..sd_bgroups_cnt][const][owned]
	                                       * Vector of block group descriptors that have been loaded into memory. */
};

#define EXT2_BLOCKSIZE(super) (1 << (super)->sd_block_shift)


/* Convert block addresses to on-disk locations, as well as the opposite.
 * Also used to convert in-file addresses to their block indices. */
#define EXT2_BLOCK2ADDR(super,block)     ((pos_t)(block) << (super)->sd_block_shift)
#define EXT2_ADDR2BLOCK(super,block)     ((ext2_block_t)(block) >> (super)->sd_block_shift)

/* Return the block group index associated with a given INode. */
#define EXT2_INO_BGRP_INDEX(super,ino)   ((ext2_bgroup_t)((ext2_ino_t)((ino)-1) / (super)->sd_ino_per_bgrp))

/* Return the offset into a block group of a given INode. */
#define EXT2_INO_BGRP_OFFSET(super,ino)  ((ext2_ino_t)((ext2_ino_t)((ino)-1) % (super)->sd_ino_per_bgrp))



#define BLOCK_TABLE_FNORMAL   0x0000
#define BLOCK_TABLE_FCHANGE   0x0001 /* The block table has been changed. */
#define BLOCK_TABLE_FCHANGE_P 0x0002 /* (Only used by `struct block_table_x2' and `struct block_table_x3') -- A child table has been changed. */
struct block_table {
	u16          bt_flags;     /* Set of `BLOCK_TABLE_F*' */
	u16        __bt_pad;       /* ... */
	ext2_block_t bt_blocks[1]; /* [:sd_ind_blocksize] Vector of indicate blocks.
	                            * This vector is initially read from disk when the table is allocated.
	                            * Making modifications to this vector requires a write-lock on the
	                            * associated INode. */
};

struct block_table_x2 {
	u16                     b2_flags;     /* Set of `BLOCK_TABLE_F*' */
	u16                   __b2_pad[(sizeof(void *)-2)/2]; /* ... */
	struct block_table    **b2_tables;    /* [0..1][owned][1..:sd_ind_blocksize][owned] Vector of indirection blocks.
	                                       * NOTE: Both this vector, as well as its contents are lazily allocated:
	                                       *  - LAZLY_ALLOC(WRITE_ONCE,lock(READ(::i_lock)))
	                                       *    - Meaning you can use WRITE_ONCE semantics while
	                                       *      holding a read-lock in the associated INode.
	                                       *  - DELETE(lock(WRITE(::i_lock)))
	                                       *    - Meaning you have full access (including deletion)
	                                       *      while holding a write-lock in the associated INode. */
	ext2_block_t            b2_blocks[1]; /* [:sd_ind_blocksize] Vector of indirection blocks. */
};

struct block_table_x3 {
	u16                     b3_flags;     /* Set of `BLOCK_TABLE_F*' */
	u16                   __b3_pad[(sizeof(void *)-2)/2]; /* ... */
	struct block_table_x2 **b3_tables;    /* [0..1][owned][1..:sd_ind_blocksize][owned] Vector of indirection blocks.
	                                       * Same as `struct block_table_x2::b2_tables' (including the same locking semantics),
	                                       * but used for triple indirection, rather than single indirection. */
	ext2_block_t            b3_blocks[1]; /* [:sd_ind_blocksize] Vector of indirection blocks. */
};

struct inode_data {
	/* INode data blocks are enumerated in the following order:
	 *    #1: i_dblock                 (0 ... 11)
	 *    #2: i_siblock->*data         (12 ... 12 + sd_ind_blocksize - 1)
	 *    #3: i_diblock->*->*data      (12 + sd_ind_blocksize ... 12 + sd_ind_blocksize + sd_ind_blocksize^2 - 1)
	 *    #4: i_tiblock->*->*->*data   (12 + sd_ind_blocksize + sd_ind_blocksize^2 ... 12 + sd_ind_blocksize + sd_ind_blocksize^3 - 1)
	 */
	struct block_table    *i_siblock; /* [0..1][MIRROR(lock,struct block_table_x2::b2_tables)]
	                                   * Lazily allocated pointer to the single indirection block table.
	                                   * Synchronization required to access this field is the same as
	                                   * is required to access tables apart of the double-indirection table. */
	struct block_table_x2 *i_diblock; /* [0..1][MIRROR(lock,struct block_table_x2::b2_tables)]
	                                   * Same as `i_siblock', but for doubly indirect blocks. */
	struct block_table_x3 *i_tiblock; /* [0..1][MIRROR(lock,struct block_table_x2::b2_tables)]
	                                   * Same as `i_siblock', but for triply indirect blocks. */
	/* Caches values of all the fields found in `Ext2INode', but not in `struct inode' */
	ext2_block_t i_dblock[EXT2_DIRECT_BLOCK_COUNT]; /* Direct block pointers for file data. */
	ext2_block_t i_siblock_addr; /* Pointer to a block filled with `ext2_block_t[EXT2_BLOCKSIZE(:)]'. */
	ext2_block_t i_diblock_addr; /* Pointer to a block filled with `i_siblock[EXT2_BLOCKSIZE(:)]'. */
	ext2_block_t i_tiblock_addr; /* Pointer to a block filled with `i_diblock[EXT2_BLOCKSIZE(:)]'. */
	ext2_block_t i_block_count;  /* Number of allocated blocks (Ext2DiskINode::i_blocks) */
	/* With the exception of `i_flags', the following fields aren't actually being used. */
	le32         i_dtime;        /* File deletion time (`time32_t' format) */
	le32         i_flags;        /* File flags (Set of `EXT2_INODE_F*') */
	le32         i_os1;          /* OS-specific field #1 (RESERVED) */
	le32         i_generation;   /* Generation number? */
	le32         i_acl;          /* [valid_if(:->sd_version >= EXT2_VERSION_1)] File ACL. */
	le32         i_fragment;     /* Block address of fragment??? */
	le32         i_os2[3];       /* Operating System Specific Value #2
	                              * NOTE: depending on the OS, KOS makes use of
	                              *       the high-16-bit UID and GID fields,
	                              *       however since not everything uses those,
	                              *       this field caches all OS-specific values. */
};



/* Inode types for different ext2 filesystem components. */
INTDEF struct inode_type Ext2_DirOps; /* S_ISDIR */
INTDEF struct inode_type Ext2_RegOps; /* S_ISREG */
INTDEF struct inode_type Ext2_DevOps; /* S_ISBLK, S_ISCHR */
INTDEF struct inode_type Ext2_LnkOps; /* S_ISLNK */



/* Return a pointer to (and lazily initialize) the block group
 * associated with the given `index'.
 * @assume(index < self->sd_bgroups_cnt); */
INTDEF ATTR_RETNONNULL WUNUSED Ext2BlockGroup *KCALL
Ext2_Group(Ext2Superblock *__restrict self, ext2_bgroup_t index)
		THROWS(E_IOERROR, E_BADALLOC, E_WOULDBLOCK, E_INTERRUPT);

/* Return the absolute on-disk position of the `Ext2DiskINode'
 * structure used to store descriptor data for the given `ino'. */
INTDEF WUNUSED pos_t KCALL
Ext2_InoAddr(Ext2Superblock *__restrict self, ext2_ino_t ino)
		THROWS(E_IOERROR_BADBOUNDS, E_IOERROR, E_BADALLOC, E_WOULDBLOCK, E_INTERRUPT);


/* Read the descriptor for the given `ino' from disk */
INTDEF void KCALL
Ext2_ReadINodeDiskDescriptor(Ext2Superblock *__restrict self, ext2_ino_t ino,
                             Ext2DiskINode *__restrict buf)
		THROWS(E_IOERROR, E_BADALLOC, ...);
/* Write the descriptor for the given `ino' to disk */
INTDEF void KCALL
Ext2_WriteINodeDiskDescriptor(Ext2Superblock *__restrict self, ext2_ino_t ino,
                              Ext2DiskINode const *__restrict buf)
		THROWS(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC, ...);


/* Read/Write data to/from an ext2 INode. */
INTDEF void KCALL Ext2_VReadFromINode(struct inode *__restrict self, CHECKED USER void *buf, size_t bufsize, pos_t pos);
INTDEF void KCALL Ext2_VWriteToINode(struct inode *__restrict self, CHECKED USER void const *buf, size_t bufsize, pos_t pos);
INTDEF void KCALL Ext2_ReadFromINode(struct inode *__restrict self, CHECKED USER void *buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio);
INTDEF void KCALL Ext2_WriteToINode(struct inode *__restrict self, CHECKED USER void const *buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio);
INTDEF void KCALL Ext2_ReadFromINodePhys(struct inode *__restrict self, vm_phys_t dst, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio);
INTDEF void KCALL Ext2_WriteToINodePhys(struct inode *__restrict self, vm_phys_t src, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio);
INTDEF void KCALL Ext2_ReadFromINodeVector(struct inode *__restrict self, struct aio_buffer *__restrict buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio);
INTDEF void KCALL Ext2_WriteToINodeVector(struct inode *__restrict self, struct aio_buffer *__restrict buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio);
INTDEF void KCALL Ext2_ReadFromINodeVectorPhys(struct inode *__restrict self, struct aio_pbuffer *__restrict buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio);
INTDEF void KCALL Ext2_WriteToINodeVectorPhys(struct inode *__restrict self, struct aio_pbuffer *__restrict buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio);
INTDEF void KCALL Ext2_ReadSymLink(struct symlink_node *__restrict self);



INTDEF void KCALL
Ext2_OpenSuperblock(Ext2Superblock *__restrict self, UNCHECKED USER char *args)
		THROWS(E_FSERROR_WRONG_FILE_SYSTEM, E_FSERROR_CORRUPTED_FILE_SYSTEM,
		       E_IOERROR_BADBOUNDS, E_DIVIDE_BY_ZERO, E_OVERFLOW, E_INDEX_ERROR,
		       E_IOERROR, E_SEGFAULT, ...);

INTDEF NOBLOCK void
NOTHROW(KCALL Ext2_FinalizeSuperblock)(Ext2Superblock *__restrict self);

INTDEF void KCALL
Ext2_OpenINode(Ext2Superblock *__restrict self,
               struct inode *__restrict node,
               struct directory_node *__restrict parent_directory,
               struct directory_entry *__restrict parent_directory_entry)
		THROWS(E_IOERROR, E_BADALLOC, ...);

INTDEF void KCALL
Ext2_SynchronizeSuperblock(Ext2Superblock *__restrict self)
		THROWS(E_IOERROR, ...);

INTDEF struct superblock_type Ext2_SuperblockType;


DECL_END

#endif /* !GUARD_MODEXT2FS_EXT2_H */
