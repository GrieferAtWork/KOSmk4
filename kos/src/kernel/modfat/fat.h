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
#ifndef GUARD_MODFAT_FAT_H
#define GUARD_MODFAT_FAT_H 1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_FS
DECL_BEGIN
struct inode_data;
DECL_END
#define FNODE_FSDATA_T struct inode_data

#include <kernel/types.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/flat.h>
#include <kernel/fs/lnknode.h>
#include <kernel/fs/node.h>
#include <kernel/fs/regnode.h>
#include <kernel/fs/super.h>
#include <sched/shared_rwlock.h>

#include <hybrid/minmax.h>
#else /* CONFIG_USE_NEW_FS */
#include <kernel/types.h>
#include <sched/rwlock.h>
#include <fs/node.h>
#endif /* !CONFIG_USE_NEW_FS */

/* Configuration option: Support cygwin-style symbolic links.
 * NOTE: Those weird  wide-character  symlinks  referenced  by  the
 *       cygwin source code aren't supported. Only regular symlinks
 *       are, and those are always assumed to represent UTF-8 text.
 *       But also note that I've never seen cygwin actually  create
 *       one of those wide-character symlinks... */
#ifdef CONFIG_NO_FAT_CYGWIN_SYMLINKS
#undef CONFIG_FAT_CYGWIN_SYMLINKS
#elif !defined(CONFIG_FAT_CYGWIN_SYMLINKS)
#define CONFIG_FAT_CYGWIN_SYMLINKS 1
#elif (CONFIG_FAT_CYGWIN_SYMLINKS + 0) == 0
#undef CONFIG_FAT_CYGWIN_SYMLINKS
#define CONFIG_NO_FAT_CYGWIN_SYMLINKS 1
#endif /* ... */


DECL_BEGIN

/* NOTE: This implementation uses the absolute on-disk location of a  FAT
 *       directory entry (The  `struct fat_dirent' structure) as  `ino_t'
 *       Here, the `struct fat_dirent'  that is  actually describing  the
 *       file is meant, meaning that LFN-entries are _NOT_ used as index,
 *       but the actual file entry following thereafter! */

#ifdef __CC__

struct fatsuper;
typedef struct fatsuper FatSuperblock;

/* FAT filesystem type (One of `FAT12', `FAT16' or `FAT32'). */
#define FAT12 0
#define FAT16 1
#define FAT32 2

#define FAT12_MAXCLUSTERS 0xff4      /* 4084 */
#define FAT16_MAXCLUSTERS 0xfff4     /* 65524 */
#define FAT32_MAXCLUSTERS 0xfffffff4 /* 4294967284 */


/* File attribute flags for `struct fat_dirent::f_attr' */
#define FAT_ATTR_READONLY      0x01
#define FAT_ATTR_HIDDEN        0x02
#define FAT_ATTR_SYSTEM        0x04
#define FAT_ATTR_VOLUMEID      0x08
#define FAT_ATTR_DIRECTORY     0x10
#define FAT_ATTR_ARCHIVE       0x20
#define FAT_ATTR_DEVICE        0x40
/*                             0x80 */
#define FAT_ATTR_LONGFILENAME (FAT_ATTR_READONLY | FAT_ATTR_HIDDEN | FAT_ATTR_SYSTEM | FAT_ATTR_VOLUMEID)

struct ATTR_PACKED fat_filetime {
	union ATTR_PACKED {
		struct ATTR_PACKED {
			unsigned int ft_sec : 5;
			unsigned int ft_min : 6;
			unsigned int ft_hour : 5;
		};
		u16 ft_sum;
	};
};

struct ATTR_PACKED fat_filedate {
	union ATTR_PACKED {
		u16 fd_sum;
		struct ATTR_PACKED {
			unsigned int fd_day : 5;
			unsigned int fd_month : 4;
			unsigned int fd_year : 7;
		};
	};
};

struct ATTR_PACKED fat_filectime {
	u8 fc_sectenth;      /* Creation time in 10ms resolution (0-199). */
	struct fat_filetime fc_time; /* Creation time. */
	struct fat_filedate fc_date; /* Creation date. */
};

struct ATTR_PACKED fat_filemtime {
	struct fat_filetime fc_time; /* Modification time. */
	struct fat_filedate fc_date; /* Modification date. */
};
#define fat_fileatime fat_filedate


struct ATTR_PACKED fat_dirent {
	/* FAT directory file entry */
	union ATTR_PACKED {
		struct ATTR_PACKED {
			union ATTR_PACKED {
				struct ATTR_PACKED {
					union ATTR_PACKED {
#define MARKER_DIREND        0x00       /* End of directory. */
#define MARKER_IS0XE5        0x05       /* Character: First character is actually 0xe5. */
#define MARKER_UNUSED        0xe5       /* Unused entry (ignore). */
						u8   f_marker;  /* Special directory entry marker (One of `MARKER_*'). */
						char f_name[8]; /* Short (8-character) filename. */
					};
					char f_ext[3]; /* File extension. */
				};
				char f_nameext[11]; /* Name+extension. */
			};
			u8 f_attr; /* File attr. */
			/* https://en.wikipedia.org/wiki/8.3_filename
			 * NOTE: After testing, the flags specified by that link are wrong.
			 *       >> The following lowercase flags are correct though! */
#define NTFLAG_NONE               0x00           /* Normal flags. */
#define NTFLAG_LOWBASE            0x08           /* Lowercase basename. */
#define NTFLAG_LOWEXT             0x10           /* Lowercase extension. */
			u8                    f_ntflags;     /* NT Flags (Set of `NTFLAG_*'). */
			struct fat_filectime  f_ctime;       /* Creation time. */
			union ATTR_PACKED {
				struct ATTR_PACKED {
					u8              f_uid;   /* User ID */
					u8              f_gid;   /* Group ID */
				};
				struct fat_fileatime f_atime; /* Last access time (or rather date...). */
			};
			union ATTR_PACKED {
#define FAT_ARB_NO_OD  0x0001 /* Owner delete/rename/attribute change requires permission */
#define FAT_ARB_NO_OX  0x0002 /* Owner execute requires permission (FlexOS, 4680 OS, 4690 OS only) */
#define FAT_ARB_NO_OW  0x0004 /* Owner write/modify requires permission */
#define FAT_ARB_NO_OR  0x0008 /* Owner read/copy requires permission */
#define FAT_ARB_NO_GD  0x0010 /* Group delete/rename/attribute change requires permission */
#define FAT_ARB_NO_GX  0x0020 /* Group execute requires permission (FlexOS, 4680 OS, 4690 OS only) */
#define FAT_ARB_NO_GW  0x0040 /* Group write/modify requires permission */
#define FAT_ARB_NO_GR  0x0080 /* Group read/copy requires permission */
#define FAT_ARB_NO_WD  0x0100 /* World delete/rename/attribute change requires permission */
#define FAT_ARB_NO_WX  0x0200 /* World execute requires permission (FlexOS, 4680 OS, 4690 OS only) */
#define FAT_ARB_NO_WW  0x0400 /* World write/modify requires permission */
#define FAT_ARB_NO_WR  0x0800 /* World read/copy requires permission */
				le16 f_arb;       /* Access rights bitmap (set of `FAT_ARB_NO_*') */
				le16 f_clusterhi; /* High 2 bytes of the file's cluster. */
			};
			struct fat_filemtime f_mtime;     /* Last modification time. */
			le16                 f_clusterlo;   /* Lower 2 bytes of the file's cluster. */
			le32                 f_size;        /* File size. */
		};
/* Sizes of the three name portions. */
#define LFN_NAME1 5
#define LFN_NAME2 6
#define LFN_NAME3 2
#define LFN_NAME  (LFN_NAME1 + LFN_NAME2 + LFN_NAME3)
		struct ATTR_PACKED {
			/* Long filename entry. */
#define LFN_SEQNUM_MIN        0x01
#define LFN_SEQNUM_MAX        0x14
#define LFN_SEQNUM_MAXCOUNT ((LFN_SEQNUM_MAX-LFN_SEQNUM_MIN)+1)
			u8   lfn_seqnum;            /* Sequence number (One of `LFN_SEQNUM_*'). */
			le16 lfn_name_1[LFN_NAME1]; /* First LFN part */
			u8   lfn_attr;              /* Attributes (always `FAT_ATTR_LONGFILENAME') */
			u8   lfn_type;              /* Long directory entry type (set to ZERO(0)) */
			u8   lfn_csum;              /* Checksum of DOS filename (s.a.: `fat_LFNchksum'). */
			le16 lfn_name_2[LFN_NAME2]; /* Second LFN part */
			le16 lfn_clus;              /* First cluster (Always 0x0000). */
			le16 lfn_name_3[LFN_NAME3]; /* Third LFN part */
		};
	};
};

typedef struct ATTR_PACKED {
	/* FAT BIOS Parameter Block (common header) */
	u8             bpb_jmp[3];              /* Jump instructions (executable). */
	char           bpb_oem[8];              /* OEM identifier */
	le16           bpb_bytes_per_sector;    /* The number of Bytes per sector. */
	u8             bpb_sectors_per_cluster; /* Number of sectors per cluster. */
	le16           bpb_reserved_sectors;    /* Number of reserved sectors. */
	u8             bpb_fatc;                /* Number of File Allocation Tables (FAT's) on the storage media (1..4). */
	le16           bpb_maxrootsize;         /* [!FAT32] Max number of entries in the root directory. */
	le16           bpb_shortsectorc;        /* The total sectors in the logical volume (If 0, use `bpb_numheads' instead). */
	u8             bpb_mediatype;           /* Indicates the media descriptor type. */
	le16           bpb_sectors_per_fat;     /* [!FAT32] Number of sectors per FAT. */
	le16           bpb_sectors_per_track;   /* Number of sectors per track. */
	le16           bpb_numheads;            /* Number of heads or sides on the storage media. */
	le32           bpb_hiddensectors;       /* Absolute sector address of the fat header (lba of the fat partition). */
	le32           bpb_longsectorc;         /* Large amount of sector on media (Used for more than `65535' sectors) */
} FatBiosParameterBlock;

typedef struct ATTR_PACKED {
	FatBiosParameterBlock f16_bpb;           /* BIOS Parameter Block. */
	u8                    f16_driveno;       /* Drive number. The value here should be identical to the value returned by BIOS interrupt 0x13,
	                                          * or passed  in  the  DL register;  i.e.  0x00  for a  floppy  disk  and 0x80  for  hard  disks.
	                                          * This  number   is  useless   because   the  media   is  likely   to   be  moved   to   another
	                                          * machine and inserted in a drive with a different drive number. */
	u8                    f16_ntflags;       /* Windows NT Flags. (Set to 0) */
	u8                    f16_signature;     /* Signature (Must be 0x28 or 0x29). */
	le32                  f16_volid;         /* VolumeID ~Serial~ number. Used for tracking volumes between computers. */
	char                  f16_label[11];     /* Volume label string. This field is padded with spaces. */
	char                  f16_sysname[8];    /* System identifier string. This field  is a string representation of  the FAT file system  type.
	                                          * It is padded with spaces. The spec says never to trust the contents of this string for any use. */
	u8                    f16_bootcode[448]; /* Boot code. */
	u8                    f16_bootsig[2];    /* Bootable partition signature (0x55, 0xAA). */
} Fat16DiskHeader;

typedef struct ATTR_PACKED {
	/* FAT32 Extended boot record. */
	FatBiosParameterBlock f32_bpb;             /* BIOS Parameter Block. */
	le32                  f32_sectors_per_fat; /* Number of sectors per FAT. */
	le16                  f32_flags;           /* Flags. */
	le16                  f32_version;         /* FAT version number. The high byte is the major version and the low byte is the minor version. FAT drivers should respect this field. */
	le32                  f32_root_cluster;    /* The cluster number of the root directory. Often this field is set to 2. */
	le16                  f32_fsinfo_cluster;  /* The sector number of the FSInfo structure. */
	le16                  f32_backup_cluster;  /* The sector number of the backup boot sector. */
	u8                    f32_set2zero[12];    /* Reserved. When the volume is formated these bytes should be zero. */
	u8                    f32_driveno;         /* Drive number. The value here should be identical to the value returned by BIOS interrupt 0x13,
	                                            * or passed  in  the  DL register;  i.e.  0x00  for a  floppy  disk  and 0x80  for  hard  disks.
	                                            * This  number   is  useless   because   the  media   is  likely   to   be  moved   to   another
	                                            * machine and inserted in a drive with a different drive number. */
	u8                    f32_ntflags;         /* Windows NT Flags. (Set to 0) */
	u8                    f32_signature;       /* Signature (Must be 0x28 or 0x29). */
	le32                  f32_volid;           /* VolumeID ~Serial~ number. Used for tracking volumes between computers. */
	char                  f32_label[11];       /* Volume label string. This field is padded with spaces. */
	char                  f32_sysname[8];      /* System identifier string. This field  is a string representation of  the FAT file system  type.
	                                            * It is padded with spaces. The spec says never to trust the contents of this string for any use. */
	u8                    f32_bootcode[420];   /* Boot code. */
	u8                    f32_bootsig[2];      /* Bootable partition signature (0x55, 0xAA). */
} Fat32DiskHeader;

typedef union ATTR_PACKED {
	FatBiosParameterBlock bpb;
	Fat16DiskHeader       fat16;
	Fat32DiskHeader       fat32;
} FatDiskHeader;

typedef u32 FatSectorIndex;  /* Sector number (sector_t). */
typedef u32 FatClusterIndex; /* Cluster/Fat index number. */
#define FAT_CLUSTER_UNUSED     0 /* Cluster number found in the FileAllocationTable, marking an unused cluster. */
#define FAT_CLUSTER_FAT16_ROOT 0 /* Cluster ID found in parent-directory entries referring to the ROOT directory. */


/* NOTE: On FAT, Inode numbers are the on-disk address of `struct fat_dirent' */

#ifdef CONFIG_USE_NEW_FS
typedef struct fatregnode FatRegNode;
typedef struct fatdirnode FatDirNode;

struct fatdirent {
	char               fad_83[8 + 3]; /* [const] 8.3 filename */
	struct fflatdirent fad_ent;       /* Underlying directory entry. */
};
#define fdirent_asfat(self)     COMPILER_CONTAINER_OF(self, struct fatdirent, fad_ent.fde_ent)
#define fflatdirent_asfat(self) COMPILER_CONTAINER_OF(self, struct fatdirent, fad_ent)

#define _fatdirent_alloc(namelen)                                                                \
	((struct fatdirent *)kmalloc(__builtin_offsetof(struct fatdirent, fad_ent.fde_ent.fd_name) + \
	                             ((namelen) + 1) * sizeof(char),                                 \
	                             GFP_NORMAL))
#define _fatdirent_free(self) kfree(__COMPILER_REQTYPE(struct fatdirent *, self))



typedef struct inode_data {
	REF struct fflatdirent *fn_ent; /* [0..1][lock(fn_dir + _MFILE_F_SMP_TSLOCK)] Directory entry of this INode (or `NULL' for root directory) */
	REF FatDirNode         *fn_dir; /* [0..1][lock(fn_dir + _MFILE_F_SMP_TSLOCK)] Directory containing this INode (or `NULL' for root directory) */
	union ATTR_PACKED {
		struct ATTR_PACKED {
			pos_t              r16_rootpos;   /* [const] On-disk starting address of the root directory segment. (Aligned by `result->ft_sectorsize') */
			u32                r16_rootsiz;   /* [const] Max size of the root-directory segment (in bytes) */
		}                      fn16_root;     /* [valid_if(:ft_type != FAT32 && :self == :s_root)] */
		struct ATTR_PACKED {
			struct shared_rwlock fn_lock;     /* Lock for the vector of clusters. */
			size_t               fn_clusterc; /* [lock(fn_lock)] Amount of loaded cluster indices. */
			FatClusterIndex     *fn_clusterv; /* [0..fn_clusterc][lock(fn_lock)]
			                                   * - Vector of file cluster starting indices. Indices are  passed
			                                   *   to `FAT_CLUSTERADDR()' to convert them into absolute on-disk
			                                   *   locations.
			                                   * - Each cluster has a length of `:ft_clustersize' bytes.  If
			                                   *   `fn_clusterv[fn_clusterc-1] >= :ft_cluster_eof', then all
			                                   *   clusters have been loaded. */
		};
	};
	struct ATTR_PACKED { /* File header data. */
		u8                     ff_attr;       /* File attr. */
		u8                     ff_ntflags;    /* NT Flags (Set of `NTFLAG_*'). */
		u16                    ff_arb;        /* [valid_if(SUPERBLOCK->ft_features & FAT_FEATURE_ARB)] ARB. */
	}                          fn_file;
} FatNodeData;


struct fatregnode: fregnode {
	FatNodeData frn_fdat; /* Fat node data. */
};

struct fatdirnode: fflatdirnode {
	FatNodeData fdn_fdat; /* Fat node data. */
};
#define FatDirNode_AsSuper(self) ((FatSuperblock *)fflatdirnode_assuper((struct fflatdirnode *)(self)))

#ifdef CONFIG_FAT_CYGWIN_SYMLINKS
typedef struct fatlnknode FatLnkNode;
struct fatlnknode: flnknode {
	FatNodeData fln_fdat; /* Fat node data. */
};
#endif /* CONFIG_FAT_CYGWIN_SYMLINKS */

#define fregnode_asfat(self)     ((FatRegNode *)(self))
#define fflatdirnode_asfat(self) ((FatDirNode *)(self))
#define fdirnode_asfat(self)     fflatdirnode_asfat(fdirnode_asflat(self))
#define fdirnode_asfatsup(self)  FatDirNode_AsSuper(fdirnode_asfat(self))
#ifdef CONFIG_FAT_CYGWIN_SYMLINKS
#define flnknode_asfat(self)     ((FatLnkNode *)(self))
#endif /* CONFIG_FAT_CYGWIN_SYMLINKS */
#define fnode_asfatreg(self)   fregnode_asfat(fnode_asreg(self))
#define fnode_asfatdir(self)   fflatdirnode_asfat(fnode_asflatdir(self))
#define fnode_asfatlnk(self)   flnknode_asfat(fnode_aslnk(self))
#define fnode_asfatsup(self)   FatDirNode_AsSuper(fnode_asfatdir(self))
#define mfile_asfatreg(self)   fregnode_asfat(mfile_asreg(self))
#define mfile_asfatdir(self)   fflatdirnode_asfat(mfile_asflatdir(self))
#define mfile_asfatlnk(self)   flnknode_asfat(mfile_aslnk(self))
#define mfile_asfatsup(self)   FatDirNode_AsSuper(mfile_asfatdir(self))


typedef NOBLOCK NONNULL((1)) FatClusterIndex (FCALL *PFatGetFatIndirection)(FatSuperblock const *__restrict self, FatClusterIndex index);
typedef NOBLOCK NONNULL((1)) void (FCALL *PFatSetFatIndirection)(FatSuperblock *__restrict self, FatClusterIndex index, FatClusterIndex indirection_target);

struct fatsuper {
	mode_t                  ft_mode;        /* [valid_if(!(ft_features & FAT_FEATURE_ARB))] Default permissions for every file on this filesystem (Defaults to 0777). */
	uid_t                   ft_uid;         /* [valid_if(!(ft_features & FAT_FEATURE_UGID))] Owner UID for every file on this filesystem (Defaults to 0). */
	gid_t                   ft_gid;         /* [valid_if(!(ft_features & FAT_FEATURE_UGID))] Owner GID for every file on this filesystem (Defaults to 0). */
	u16                     ft_type;        /* [const] FAT filesystem type (One of `FAT12', `FAT16' or `FAT32'). */
#define FAT_FEATURE_SEC32             0x0000 /* struct fat_dirent+0x14: High 16 bits of the 32-bit starting sector number */
#define FAT_FEATURE_ARB               0x0001 /* struct fat_dirent+0x14: 16-bit access rights bitmap (set of `FAT_ARB_NO_*') */
#define FAT_FEATURE_ATIME             0x0000 /* struct fat_dirent+0x12: 16-bit last-access timestamp */
#define FAT_FEATURE_UGID              0x0002 /* struct fat_dirent+0x12: 8-bit user/group IDs */
#ifdef CONFIG_FAT_CYGWIN_SYMLINKS
#define FAT_FEATURE_NO_CYGWIN_SYMLINK 0x8000 /* Disable cygwin symlink support */
#endif /* CONFIG_FAT_CYGWIN_SYMLINKS */
	u16                     ft_features;    /* [const] Fat features (Set of `FAT_FEATURE_*'). */
	char                    ft_oem[9];      /* [const] OEM identifier. */
	char                    ft_label[12];   /* [const] Volume label string (zero-terminated). */
	char                    ft_sysname[9];  /* [const] System identifier string (zero-terminated). */
	u32                     ft_volid;       /* [const] FAT Volume ID. */
	u8                     _ft_pad;         /* ... */
	u8                      ft_fat_count;   /* [const] Amount of redundant FAT copies. */
#ifdef __INTELLISENSE__
	size_t                  ft_sectorshift; /* [const] ilog2(ft_sectorsize) (in bytes). */
#else /* __INTELLISENSE__ */
#define ft_sectorshift      ft_super.ffs_super.fs_root.mf_blockshift  /* [const] ilog2(ft_sectorsize) (in bytes). */
#endif /* !__INTELLISENSE__ */
	size_t                  ft_sectorsize;  /* [const][== 1 << ft_sectorshift] Size of a sector (in bytes). */
	size_t                  ft_clustersize; /* [const][== ft_sec4clus << ft_sectorshift] Size of a cluster (in bytes). */
	size_t                  ft_fat_size;    /* [const][== ft_sec4fat << ft_sectorshift] Size of a single FileAllocationTable (in bytes). */
	FatSectorIndex          ft_sec4clus;    /* [const] Amount of sectors per cluster. */
	FatSectorIndex          ft_sec4fat;     /* [const] Amount of sectors per FileAllocationTable. */
	FatSectorIndex          ft_dat_start;   /* [const] First data sector. */
	FatSectorIndex          ft_fat_start;   /* [const] Sector number of the first FileAllocationTable. */
	union ATTR_PACKED {
		FatClusterIndex     ft_fat_length;  /* [const] The max number of the FAT indirection entries. */
		FatClusterIndex     ft_cluster_eof; /* [const] Cluster indices greater than or equal to this are considered EOF. */
	};
	FatClusterIndex         ft_cluster_eof_marker; /* [const] Marker used to indicate EOF entries in the FAT. */
	PFatGetFatIndirection   ft_fat_get;     /* [const][1..1] Read an entry from the FileAllocationTable. */
	PFatSetFatIndirection   ft_fat_set;     /* [const][1..1] Write an entry to the FileAllocationTable. */
	struct shared_rwlock    ft_fat_lock;    /* Lock for accessing the FileAllocationTable cache. */
	void                   *ft_fat_table;   /* [lock(ft_fat_lock)][1..ft_fat_size][owned][const] Memory-mapping of the FAT table. */
	struct mman_unmap_kram_job *ft_freefat; /* [1..1][owned][const] Used for unmapping `ft_fat_table' */
	FatClusterIndex         ft_free_pos;    /* [lock(ft_fat_lock)] Next cluster index that should be considered when search for free clusters. */
	struct fflatsuper       ft_super;       /* Underlying superblock */
	FatNodeData             ft_fdat;        /* Fat root directory node data. */
};
#define fflatsuper_asfat(self) COMPILER_CONTAINER_OF(self, FatSuperblock, ft_super)
#define fsuper_asfat(self)     COMPILER_CONTAINER_OF(self, FatSuperblock, ft_super.ffs_super)


/* Helpers for accessing `ft_fat_lock' */
#define _fatsuper_fatlock_reap(self)      (void)0
#define fatsuper_fatlock_reap(self)       (void)0
#define fatsuper_fatlock_write(self)      shared_rwlock_write(&(self)->ft_fat_lock)
#define fatsuper_fatlock_write_nx(self)   shared_rwlock_write_nx(&(self)->ft_fat_lock)
#define fatsuper_fatlock_trywrite(self)   shared_rwlock_trywrite(&(self)->ft_fat_lock)
#define fatsuper_fatlock_endwrite(self)   (shared_rwlock_endwrite(&(self)->ft_fat_lock), fatsuper_fatlock_reap(self))
#define _fatsuper_fatlock_endwrite(self)  shared_rwlock_endwrite(&(self)->ft_fat_lock)
#define fatsuper_fatlock_read(self)       shared_rwlock_read(&(self)->ft_fat_lock)
#define fatsuper_fatlock_read_nx(self)    shared_rwlock_read_nx(&(self)->ft_fat_lock)
#define fatsuper_fatlock_tryread(self)    shared_rwlock_tryread(&(self)->ft_fat_lock)
#define _fatsuper_fatlock_endread(self)   shared_rwlock_endread(&(self)->ft_fat_lock)
#define fatsuper_fatlock_endread(self)    (void)(shared_rwlock_endread(&(self)->ft_fat_lock) && (fatsuper_fatlock_reap(self), 0))
#define _fatsuper_fatlock_end(self)       shared_rwlock_end(&(self)->ft_fat_lock)
#define fatsuper_fatlock_end(self)        (void)(shared_rwlock_end(&(self)->ft_fat_lock) && (fatsuper_fatlock_reap(self), 0))
#define fatsuper_fatlock_upgrade(self)    shared_rwlock_upgrade(&(self)->ft_fat_lock)
#define fatsuper_fatlock_upgrade_nx(self) shared_rwlock_upgrade_nx(&(self)->ft_fat_lock)
#define fatsuper_fatlock_tryupgrade(self) shared_rwlock_tryupgrade(&(self)->ft_fat_lock)
#define fatsuper_fatlock_downgrade(self)  shared_rwlock_downgrade(&(self)->ft_fat_lock)
#define fatsuper_fatlock_reading(self)    shared_rwlock_reading(&(self)->ft_fat_lock)
#define fatsuper_fatlock_writing(self)    shared_rwlock_writing(&(self)->ft_fat_lock)
#define fatsuper_fatlock_canread(self)    shared_rwlock_canread(&(self)->ft_fat_lock)
#define fatsuper_fatlock_canwrite(self)   shared_rwlock_canwrite(&(self)->ft_fat_lock)



/* Get/Set  a  FAT table  indirection.  (These function  access  the `ft_fat_table'  memory mapping)
 * As such, changes made by these functions must be synced to-disk via `mfile_sync(ft_super.fs_dev)' */
#define Fat_GetFatIndirection(self, index)                     (*(self)->ft_fat_get)(self, index)
#define Fat_SetFatIndirection(self, index, indirection_target) (*(self)->ft_fat_set)(self, index, indirection_target)

/* Returns the on-disk address of a given sector number. */
#define FAT_SECTORADDR(self, sector_num)   \
	((pos_t)(sector_num) << (self)->ft_sectorshift)

/* Returns the sector number of a given cluster, which then spans `self->ft_sec4clus' sectors. */
#define FAT_CLUSTERSTART(self, cluster_id) \
	((FatSectorIndex)((self)->ft_dat_start + (((cluster_id) - 2) * (self)->ft_sec4clus)))

/* Returns the on-disk address of a given cluster number. */
#define FAT_CLUSTERADDR(self, cluster_id) \
	FAT_SECTORADDR(self, FAT_CLUSTERSTART(self, cluster_id))


#else /* CONFIG_USE_NEW_FS */

typedef struct inode_data {
	union ATTR_PACKED {
		struct ATTR_PACKED {
			pos_t              r16_rootpos;  /* [const] On-disk starting address of the root directory segment. */
			u32                r16_rootsiz;  /* [const] Max size of the root-directory segment (in bytes) */
		}                      fn16_root;    /* [valid_if(:ft_type != FAT32 && :self == :s_root)] */
		struct ATTR_PACKED {
			size_t             fn_clusterc;  /* [lock(:mf_lock)]
			                                  * [if(:ft_type != FAT32 && :self == :s_root,[== 0])]
			                                  * [if(:ft_type == FAT32 || :self != :s_root,[!0])]
			                                  * Amount of loaded cluster indices. */
			size_t             fn_clustera;  /* [lock(:mf_lock)]
			                                  * [if(:ft_type != FAT32 && :self == :s_root,[== 0])]
			                                  * [if(:ft_type == FAT32 || :self != :s_root,[!0])]
			                                  * Allocated amount of cluster indices. */
			FatClusterIndex   *fn_clusterv;  /* [lock(:mf_lock)]
			                                  * [if(:ft_type != FAT32 && :self == :s_root,[== NULL])]
			                                  * [if(:ft_type == FAT32 || :self != :s_root,[1..fn_clusterc|alloc(fn_clustera)][owned])]
			                                  * Vector    of    file    cluster    starting     indices.
			                                  * Indices   are   passed    to   `FAT_CLUSTERADDR()'    to
			                                  * convert   them   into   absolute   on-disk    locations.
			                                  * Each cluster has  a length  of `:ft_clustersize'  bytes.
			                                  * If `fn_clusterv[fn_clusterc-1] >= :ft_cluster_eof', then
			                                  * all clusters have been loaded. */
		};
	};
	struct ATTR_PACKED { /* File header data. */
		u8                     ff_attr;       /* File attr. */
		u8                     ff_ntflags;    /* NT Flags (Set of `NTFLAG_*'). */
		u16                    ff_arb;        /* [valid_if(SUPERBLOCK->ft_features & FAT_FEATURE_ARB)] ARB. */
	}                          fn_file;
} FatNodeData;



/* Returns the cluster index of the `nth_cluster' cluster that is allocated for `self'.
 * NOTE: The caller must be holding at least a read-lock on `self'
 * @param: mode: Set of `FAT_GETCLUSTER_MODE_F*' */
INTDEF NONNULL((1)) FatClusterIndex KCALL
Fat_GetFileCluster(struct inode *__restrict self,
                   size_t nth_cluster,
                   unsigned int mode);
#define FAT_GETCLUSTER_MODE_FNORMAL 0x0000 /* If  that  cluster  hasn't  been  loaded  yet,  load  it  now.
                                            * If the cluster doesn't exist, return `ft_cluster_eof_marker'. */
#define FAT_GETCLUSTER_MODE_FCREATE 0x0001 /* Allocate missing clusters. */
#define FAT_GETCLUSTER_MODE_FNOZERO 0x0002 /* Do not ZERO-initialize newly allocated clusters.
                                            * NOTE: This flag is implied when `node' isn't a regular file. */
#define FAT_GETCLUSTER_MODE_FNCHNGE 0x0004 /* Don't mark the node as changed if the initial cluster was allocated. */


typedef FatClusterIndex (KCALL *PFatGetFatIndirection)(FatSuperblock const *__restrict self, FatClusterIndex index);
typedef void (KCALL *PFatSetFatIndirection)(FatSuperblock *__restrict self, FatClusterIndex index, FatClusterIndex indirection_target);

/* Returns a sector number offset from `ft_fat_start', within
 * which the data associated with  the given `id' is  stored. */
typedef FatSectorIndex (KCALL *PFatGetTableSector)(FatSuperblock const *__restrict self, FatClusterIndex id);

#define FAT_METALOAD  0x1 /* When set, the associated sector has been loaded. */
#define FAT_METACHNG  0x2 /* When set, the associated sector has been changed (Write data when syncing the filesystem). */
#define FAT_METAMASK  0x3 /* Mask of known meta-data bits. */
#define FAT_METABITS    2 /* The number of FAT metadata bits per FileAllocationTable cluster. */







struct fatsuper: superblock {
	FatNodeData             ft_root;        /* Fat INode data for the root node. */
	mode_t                  ft_mode;        /* [valid_if(!(ft_features & FAT_FEATURE_ARB))] Default permissions for every file on this filesystem (Defaults to 0777). */
	uid_t                   ft_uid;         /* [valid_if(!(ft_features & FAT_FEATURE_UGID))] Owner UID for every file on this filesystem (Defaults to 0). */
	gid_t                   ft_gid;         /* [valid_if(!(ft_features & FAT_FEATURE_UGID))] Owner GID for every file on this filesystem (Defaults to 0). */
	u16                     ft_type;        /* [const] FAT filesystem type (One of `FAT12', `FAT16' or `FAT32'). */
#define FAT_FEATURE_SEC32             0x0000 /* struct fat_dirent+0x14: High 16 bits of the 32-bit starting sector number */
#define FAT_FEATURE_ARB               0x0001 /* struct fat_dirent+0x14: 16-bit access rights bitmap (set of `FAT_ARB_NO_*') */
#define FAT_FEATURE_ATIME             0x0000 /* struct fat_dirent+0x12: 16-bit last-access timestamp */
#define FAT_FEATURE_UGID              0x0002 /* struct fat_dirent+0x12: 8-bit user/group IDs */
#ifdef CONFIG_FAT_CYGWIN_SYMLINKS
#define FAT_FEATURE_NO_CYGWIN_SYMLINK 0x8000 /* Disable cygwin symlink support */
#endif /* CONFIG_FAT_CYGWIN_SYMLINKS */
	u16                     ft_features;    /* [const] Fat features (Set of `FAT_FEATURE_*'). */
	char                    ft_oem[9];      /* [const] OEM identifier. */
	char                    ft_label[12];   /* [const] Volume label string (zero-terminated). */
	char                    ft_sysname[9];  /* [const] System identifier string (zero-terminated). */
	u32                     ft_volid;       /* [const] FAT Volume ID. */
#define FAT_FNORMAL         0x0000          /* Normal fat flags. */
#define FAT_FCHANGED        0x0001          /* [lock(ft_fat_lock)] At least one of the `FAT_METACHNG' bits in `ft_fat_meta' is set. */
	u16                     ft_flags;       /* Set of `FAT_F*' */
	u8                     _ft_pad;         /* ... */
	u8                      ft_fat_count;   /* [const] Amount of redundant FAT copies. */
#ifdef __INTELLISENSE__
	size_t                  ft_sectorshift; /* [const] ilog2(ft_sectorsize) (in bytes). */
#else /* __INTELLISENSE__ */
#define ft_sectorshift      mf_blockshift   /* [const] ilog2(ft_sectorsize) (in bytes). */
#endif /* !__INTELLISENSE__ */
	size_t                  ft_sectorsize;  /* [const][== 1 << ft_sectorshift] Size of a sector (in bytes). */
	size_t                  ft_clustersize; /* [const][== ft_sec4clus << ft_sectorshift] Size of a cluster (in bytes). */
	size_t                  ft_fat_size;    /* [const][== ft_sec4fat << ft_sectorshift] Size of a single FileAllocationTable (in bytes). */
	FatSectorIndex          ft_sec4clus;    /* [const] Amount of sectors per cluster. */
	FatSectorIndex          ft_sec4fat;     /* [const] Amount of sectors per FileAllocationTable. */
	FatSectorIndex          ft_dat_start;   /* [const] First data sector. */
	FatSectorIndex          ft_fat_start;   /* [const] Sector number of the first FileAllocationTable. */
	union ATTR_PACKED {
		FatClusterIndex     ft_fat_length;  /* [const] The max number of the FAT indirection entries. */
		FatClusterIndex     ft_cluster_eof; /* [const] Cluster indices greater than or equal to this are considered EOF. */
	};
	FatClusterIndex         ft_cluster_eof_marker; /* [const] Marker used to indicate EOF entries in the FAT. */
	PFatGetFatIndirection   ft_fat_get;     /* [const][1..1] Read an entry from the FileAllocationTable. */
	PFatSetFatIndirection   ft_fat_set;     /* [const][1..1] Write an entry to the FileAllocationTable. */
	PFatGetTableSector      ft_fat_sector;  /* [const][1..1] Return a sector offset from `ft_fat_start' of a given FileAllocationTable index.
	                                         *              (That is the sector in which that part of the the FileAllocationTable is stored on-disk).
	                                         * HINT: The number returned by this may be used to interact with the
	                                         *      `ft_fat_meta' bitset-vector, preferably using the `FAT_META_*' macros. */
	struct rwlock           ft_fat_lock;    /* Lock for accessing the FileAllocationTable cache. */
	void                   *ft_fat_table;   /* [lock(ft_fat_lock)][1..ft_fat_size|LOGICAL_LENGTH(ft_fat_length)][owned][const]
	                                         * Memory-cached version of the FileAllocationTable.
	                                         * NOTE: The way  that entries  within this  table are  read/written  depends
	                                         *       on the type of FAT, but `f_fat_(g|s)et' can be used for convenience.
	                                         * NOTE: The amount of entries can be read from `ft_fat_length'.
	                                         * NOTE: The amount  of bytes  can be  read from  `ft_fat_size'. */
	uintptr_t              *ft_fat_meta;    /* [lock(ft_fat_lock)][1..CEILDIV(ft_sec4fat,BITS_PER_POINTER/FAT_METABITS)|LOCIAL_LENGTH(ft_sec4fat)]
	                                         * [BITSET(FAT_METABITS)][owned][const]
	                                         * A bitset used to track the load/change status of `ft_fat_table'.
	                                         * Stored inside  this, one  can find  information about  what  FAT
	                                         * sectors have already been loaded, and which have changed.
	                                         * NOTE: This bitset contains one entry of `FAT_METABITS'
	                                         *       for  each  sector within  the FAT  lookup table.
	                                         * NOTE: `f_fat_changed' must be set to `true' while changed fat entries exist. */
	FatClusterIndex         ft_free_pos;    /* [lock(ft_fat_lock)] Next cluster index that should be considered when search for free clusters. */
};

#define FAT_META_GTLOAD(self, fat_sector_index)                                    \
	((self)->ft_fat_meta[(fat_sector_index) / (BITS_PER_POINTER / FAT_METABITS)] & \
	 ((uintptr_t)FAT_METALOAD << (((fat_sector_index) % (BITS_PER_POINTER / FAT_METABITS)) * FAT_METABITS)))
#define FAT_META_STLOAD(self, fat_sector_index)                                     \
	((self)->ft_fat_meta[(fat_sector_index) / (BITS_PER_POINTER / FAT_METABITS)] |= \
	 ((uintptr_t)FAT_METALOAD << (((fat_sector_index) % (BITS_PER_POINTER / FAT_METABITS)) * FAT_METABITS)))
#define FAT_META_UTLOAD(self, fat_sector_index)                                     \
	((self)->ft_fat_meta[(fat_sector_index) / (BITS_PER_POINTER / FAT_METABITS)] &= \
	 ~((uintptr_t)FAT_METALOAD << (((fat_sector_index) % (BITS_PER_POINTER / FAT_METABITS)) * FAT_METABITS)))
#define FAT_META_GTCHNG(self, fat_sector_index)                                    \
	((self)->ft_fat_meta[(fat_sector_index) / (BITS_PER_POINTER / FAT_METABITS)] & \
	 ((uintptr_t)FAT_METACHNG << (((fat_sector_index) % (BITS_PER_POINTER / FAT_METABITS)) * FAT_METABITS)))
#define FAT_META_STCHNG(self, fat_sector_index)                                     \
	((self)->ft_fat_meta[(fat_sector_index) / (BITS_PER_POINTER / FAT_METABITS)] |= \
	 ((uintptr_t)FAT_METACHNG << (((fat_sector_index) % (BITS_PER_POINTER / FAT_METABITS)) * FAT_METABITS)))
#define FAT_META_UTCHNG(self, fat_sector_index)                                     \
	((self)->ft_fat_meta[(fat_sector_index) / (BITS_PER_POINTER / FAT_METABITS)] &= \
	 ~((uintptr_t)FAT_METACHNG << (((fat_sector_index) % (BITS_PER_POINTER / FAT_METABITS)) * FAT_METABITS)))


/* Get/Set   FAT   indirection,  automatically   loading   missing  parts
 * of the FileAllocationTable, as well as mark modified parts as changed.
 * NOTE: When  calling  `Fat_SetFatIndirection()',  the
 *       caller must be holding a lock on `ft_fat_lock' */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) FatClusterIndex KCALL
Fat_GetFatIndirection(FatSuperblock *__restrict self,
                      FatClusterIndex index);

INTDEF NONNULL((1)) void KCALL
Fat_SetFatIndirection(FatSuperblock *__restrict self,
                      FatClusterIndex index,
                      FatClusterIndex indirection_target);

/* Find a free cluster index.
 * NOTE: The caller will probably want to be holding a lock on `ft_fat_lock' for this.
 * @throw: E_FILESYSTEM_ERROR.ERROR_FS_DISK_FULL: There are no more free clusters. */
INTDEF WUNUSED NONNULL((1)) FatClusterIndex KCALL
Fat_FindFreeCluster(FatSuperblock *__restrict self);

/* Delete a chain of free clusters, starting with `first_delete_index'
 * NOTE: The  caller   must  be   holding  a   lock  on   `ft_fat_lock' */
INTDEF NONNULL((1)) void KCALL
Fat_DeleteClusterChain(FatSuperblock *__restrict self,
                       FatClusterIndex first_delete_index);

/* Read/Write to/from a given INode at the specified offset.
 * NOTE: These  functions  do not  truncate/update the  size value
 *       of the associated INode. However allocating an additional
 *       sector will  cause `Fat32_WriteToINode()'  to update  the
 *       the `a_blocks' attribute of `self'.
 * NOTE: Attempting to read data from beyond the allocated end
 *       of an INode will yield all ZEROes.
 * NOTE: These functions must not be used for I/O operations
 *       on the root directory of a FAT12/FAT16 file system.
 * @throw: E_FILESYSTEM_ERROR.ERROR_FS_DISK_FULL: [...] */
INTDEF NONNULL((1)) void KCALL Fat32_VReadFromINode(struct inode *__restrict self, CHECKED USER byte_t *buf, size_t bufsize, pos_t pos) THROWS(...);
INTDEF NONNULL((1)) void KCALL Fat32_VWriteToINode(struct inode *__restrict self, CHECKED USER byte_t const *buf, size_t bufsize, pos_t pos) THROWS(...);
INTDEF NONNULL((1)) size_t KCALL Fat32_VTryReadFromINode(struct inode *__restrict self, CHECKED USER byte_t *buf, size_t bufsize, pos_t pos) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat32_ReadFromINode(struct inode *__restrict self, CHECKED USER void *buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat32_WriteToINode(struct inode *__restrict self, CHECKED USER void const *buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat32_ReadFromINodePhys(struct inode *__restrict self, physaddr_t dst, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat32_WriteToINodePhys(struct inode *__restrict self, physaddr_t src, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat32_ReadFromINodeVector(struct inode *__restrict self, struct iov_buffer *__restrict buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat32_WriteToINodeVector(struct inode *__restrict self, struct iov_buffer *__restrict buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat32_ReadFromINodeVectorPhys(struct inode *__restrict self, struct iov_physbuffer *__restrict buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat32_WriteToINodeVectorPhys(struct inode *__restrict self, struct iov_physbuffer *__restrict buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);

/* Same  as the functions  above, but used for
 * operating with the FAT12/16 root directory.
 * @throw: E_FILESYSTEM_ERROR.ERROR_FS_DISK_FULL:
 *         The given `pos + bufsize' extends beyond
 *         the max size of the root directory. */
INTDEF NONNULL((1)) void KCALL Fat16_VReadFromRootDirectory(FatSuperblock *__restrict self, CHECKED USER byte_t *buf, size_t bufsize, pos_t pos) THROWS(...);
INTDEF NONNULL((1)) void KCALL Fat16_VWriteToRootDirectory(FatSuperblock *__restrict self, CHECKED USER byte_t const *buf, size_t bufsize, pos_t pos) THROWS(...);
INTDEF NONNULL((1)) size_t KCALL Fat16_VTryReadFromRootDirectory(FatSuperblock *__restrict self, CHECKED USER byte_t *buf, size_t bufsize, pos_t pos) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat16_ReadFromRootDirectory(FatSuperblock *__restrict self, CHECKED USER void *buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat16_WriteToRootDirectory(FatSuperblock *__restrict self, CHECKED USER void const *buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat16_ReadFromRootDirectoryPhys(FatSuperblock *__restrict self, physaddr_t dst, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat16_WriteToRootDirectoryPhys(FatSuperblock *__restrict self, physaddr_t src, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat16_ReadFromRootDirectoryVector(FatSuperblock *__restrict self, struct iov_buffer *__restrict buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat16_WriteToRootDirectoryVector(FatSuperblock *__restrict self, struct iov_buffer *__restrict buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat16_ReadFromRootDirectoryVectorPhys(FatSuperblock *__restrict self, struct iov_physbuffer *__restrict buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat16_WriteToRootDirectoryVectorPhys(FatSuperblock *__restrict self, struct iov_physbuffer *__restrict buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);

/* Hybrid of the functions above:
 * Determine the type, then read from the INode. */
INTDEF NONNULL((1)) void KCALL Fat_VReadFromINode(struct inode *__restrict self, CHECKED USER byte_t *buf, size_t bufsize, pos_t pos) THROWS(...);
INTDEF NONNULL((1)) void KCALL Fat_VWriteToINode(struct inode *__restrict self, CHECKED USER byte_t const *buf, size_t bufsize, pos_t pos) THROWS(...);
INTDEF NONNULL((1)) size_t KCALL Fat_VTryReadFromINode(struct inode *__restrict self, CHECKED USER byte_t *buf, size_t bufsize, pos_t pos) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat_ReadFromINode(struct inode *__restrict self, CHECKED USER void *buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat_WriteToINode(struct inode *__restrict self, CHECKED USER void const *buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat_ReadFromINodePhys(struct inode *__restrict self, physaddr_t dst, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat_WriteToINodePhys(struct inode *__restrict self, physaddr_t src, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat_ReadFromINodeVector(struct inode *__restrict self, struct iov_buffer *__restrict buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat_WriteToINodeVector(struct inode *__restrict self, struct iov_buffer *__restrict buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat_ReadFromINodeVectorPhys(struct inode *__restrict self, struct iov_physbuffer *__restrict buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF NONNULL((1, 5)) void KCALL Fat_WriteToINodeVectorPhys(struct inode *__restrict self, struct iov_physbuffer *__restrict buf, size_t bufsize, pos_t pos, struct aio_multihandle *__restrict aio) THROWS(...);

/* Returns the absolute on-disk position of `pos' in `self' */
INTDEF NONNULL((1)) pos_t KCALL
Fat_GetAbsDiskPos(struct inode *__restrict self, pos_t pos) THROWS(...);


/* Returns the on-disk address of a given cluster number. */
#define FAT_CLUSTERADDR(self, cluster_id) \
	FAT_SECTORADDR(self, FAT_CLUSTERSTART(self, cluster_id))

/* Returns the on-disk address of a given sector number. */
#define FAT_SECTORADDR(self, sector_num)   \
	((pos_t)(sector_num) << (self)->ft_sectorshift)

/* Returns the sector number of a given cluster, which then spans `self->ft_sec4clus' sectors. */
#define FAT_CLUSTERSTART(self, cluster_id) \
	((FatSectorIndex)((self)->ft_dat_start + (((cluster_id) - 2) * (self)->ft_sec4clus)))

/* In FAT, we store the raw 8.3 filename (without case-fix) immediately after the regular name. */
#define FAT_DIRECTORY_ENTRY83(x)  ((char *)(x)->de_fsdata.de_data)

#endif /* !CONFIG_USE_NEW_FS */

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_MODFAT_FAT_H */
