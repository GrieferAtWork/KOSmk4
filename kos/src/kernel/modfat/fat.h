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
#ifndef GUARD_MODFAT_FAT_H
#define GUARD_MODFAT_FAT_H 1

#include <kernel/compiler.h>

DECL_BEGIN
struct inode_data;
DECL_END
#define FNODE_FSDATA_T struct inode_data

#include <kernel/fs/dirent.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/flat.h>
#include <kernel/fs/lnknode.h>
#include <kernel/fs/node.h>
#include <kernel/fs/regnode.h>
#include <kernel/fs/super.h>
#include <kernel/types.h>

#include <hybrid/minmax.h>

#include <kos/sched/shared-rwlock.h>

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

/* NOTE: This implementation uses the absolute on-disk location of a  FAT
 *       directory entry (The  `struct fat_dirent' structure) as  `ino_t'
 *       Here, the `struct fat_dirent'  that is  actually describing  the
 *       file is meant, meaning that LFN-entries are _NOT_ used as index,
 *       but the actual file entry following thereafter! */

#ifdef __CC__
DECL_BEGIN

struct fatsuper;
typedef struct fatsuper FatSuperblock;

/* FAT filesystem type (One of `FAT12', `FAT16' or `FAT32'). */
#define FAT12 0
#define FAT16 1
#define FAT32 2

#define FAT12_MAXCLUSTERS 0xff4      /* 4084 */
#define FAT16_MAXCLUSTERS 0xfff4     /* 65524 */
#define FAT32_MAXCLUSTERS 0xfffffff4 /* 4294967284 */


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

struct ATTR_PACKED fat_filebtime {
	u8                  fb_sectenth; /* Birth time in 10ms resolution (0-199). */
	struct fat_filetime fb_time;     /* Birth time. */
	struct fat_filedate fb_date;     /* Birth date. */
};

struct ATTR_PACKED fat_filemtime {
	struct fat_filetime fc_time; /* Modification time. */
	struct fat_filedate fc_date; /* Modification date. */
};
#define fat_fileatime fat_filedate


struct ATTR_PACKED ATTR_ALIGNED(4) fat_dirent {
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
			union ATTR_PACKED {
				u8                   f_delchr;   /* First character of deleted file. */
				struct fat_filebtime f_btime;    /* Birth time. */
			};
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
			u8   lfn_attr;              /* Attributes (always `FATATTR_LFN') */
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

typedef struct fatregnode FatRegNode;
typedef struct fatdirnode FatDirNode;

/*
 * To prevent dead-locks, the following locking order must be ensured:
 *
 * #1: if (fnode_isdir(self)) self->fdn_data.fdd_lock;
 * #2: self->fn_fsdata->fn_lock;
 * #3: fsuper_asfat(self->fn_super)->ft_fat_lock;
 *
 * (If multiple locks are needed, those with a higher priority must
 * be acquired first if later locks are still allowed to block when
 * being acquired).
 */


struct fatdirent {
	struct fat_dirent fad_dos; /* [lock(:DIR->fdn_data.fdd_lock)] DOS directory  entry.
	                            * This entry lives on-disk at `fatdirent_dosaddr(self)' */
	struct flatdirent fad_ent; /* Underlying directory entry. */
};
#define fdirent_asfat(self)    COMPILER_CONTAINER_OF(self, struct fatdirent, fad_ent.fde_ent)
#define flatdirent_asfat(self) COMPILER_CONTAINER_OF(self, struct fatdirent, fad_ent)

/* Return the in-directory stream address where `fad_dos' lives. */
#define fatdirent_dosaddr(self) (flatdirent_endaddr(&(self)->fad_ent) - sizeof(struct fat_dirent))

#define _fatdirent_alloc(namelen)                                                                \
	((struct fatdirent *)kmalloc(__builtin_offsetof(struct fatdirent, fad_ent.fde_ent.fd_name) + \
	                             ((namelen) + 1) * sizeof(char),                                 \
	                             GFP_NORMAL))
#define _fatdirent_free(self) kfree(__COMPILER_REQTYPE(struct fatdirent *, self))



typedef struct inode_data {
	REF struct fatdirent *fn_ent; /* [0..1][lock(fn_dir->fdn_data.fdd_lock + _MFILE_F_SMP_TSLOCK)] Directory entry of this INode (or `NULL' for root directory, or when deleted) */
	REF FatDirNode       *fn_dir; /* [0..1][lock(fn_dir->fdn_data.fdd_lock + _MFILE_F_SMP_TSLOCK)] Directory containing this INode (or `NULL' for root directory, or when deleted) */
	union {
		struct {
			pos_t              r16_rootpos;   /* [const] On-disk starting address of the root directory segment. (Aligned by `result->ft_sectormask + 1') */
			u32                r16_rootsiz;   /* [const] Max size of the root-directory segment (in bytes) */
		}                      fn16_root;     /* [valid_if(:ft_type != FAT32 && :self == :s_root)] */
		struct {
			struct shared_rwlock fn_lock;     /* Lock for the vector of clusters. */
			size_t               fn_clusterc; /* [!0][lock(fn_lock)] Amount of loaded cluster indices. */
			FatClusterIndex     *fn_clusterv; /* [1..fn_clusterc][lock(fn_lock)]
			                                   * - Vector of file cluster starting indices. Indices are  passed
			                                   *   to `FAT_CLUSTERADDR()' to convert them into absolute on-disk
			                                   *   locations.
			                                   * - Each cluster has a length of `:ft_clustersize' bytes.  If
			                                   *   `fn_clusterv[fn_clusterc-1] >= :ft_cluster_eof', then all
			                                   *   clusters have been loaded. */
		};
	};
} FatNodeData;

/* Helpers for accessing `fn_lock' */
#define /*        */ _FatNodeData_Reap(self)       (void)0
#define /*        */ FatNodeData_Reap(self)        (void)0
#define /*        */ FatNodeData_MustReap(self)    0
#define /*BLOCKING*/ FatNodeData_Write(self)       shared_rwlock_write(&(self)->fn_lock)
#define /*BLOCKING*/ FatNodeData_WriteNx(self)     shared_rwlock_write_nx(&(self)->fn_lock)
#define /*        */ FatNodeData_TryWrite(self)    shared_rwlock_trywrite(&(self)->fn_lock)
#define /*        */ FatNodeData_EndWrite(self)    (shared_rwlock_endwrite(&(self)->fn_lock), FatNodeData_Reap(self))
#define /*        */ _FatNodeData_EndWrite(self)   shared_rwlock_endwrite(&(self)->fn_lock)
#define /*BLOCKING*/ FatNodeData_Read(self)        shared_rwlock_read(&(self)->fn_lock)
#define /*BLOCKING*/ FatNodeData_ReadNx(self)      shared_rwlock_read_nx(&(self)->fn_lock)
#define /*        */ FatNodeData_TryRead(self)     shared_rwlock_tryread(&(self)->fn_lock)
#define /*        */ _FatNodeData_EndRead(self)    shared_rwlock_endread(&(self)->fn_lock)
#define /*        */ FatNodeData_EndRead(self)     (void)(shared_rwlock_endread(&(self)->fn_lock) && (FatNodeData_Reap(self), 0))
#define /*        */ _FatNodeData_End(self)        shared_rwlock_end(&(self)->fn_lock)
#define /*        */ FatNodeData_End(self)         (void)(shared_rwlock_end(&(self)->fn_lock) && (FatNodeData_Reap(self), 0))
#define /*BLOCKING*/ FatNodeData_Upgrade(self)     shared_rwlock_upgrade(&(self)->fn_lock)
#define /*        */ FatNodeData_TryUpgrade(self)  shared_rwlock_tryupgrade(&(self)->fn_lock)
#define /*        */ FatNodeData_Downgrade(self)   shared_rwlock_downgrade(&(self)->fn_lock)
#define /*        */ FatNodeData_Reading(self)     shared_rwlock_reading(&(self)->fn_lock)
#define /*        */ FatNodeData_Writing(self)     shared_rwlock_writing(&(self)->fn_lock)
#define /*        */ FatNodeData_CanRead(self)     shared_rwlock_canread(&(self)->fn_lock)
#define /*        */ FatNodeData_CanWrite(self)    shared_rwlock_canwrite(&(self)->fn_lock)
#define /*BLOCKING*/ FatNodeData_WaitRead(self)    shared_rwlock_waitread(&(self)->fn_lock)
#define /*BLOCKING*/ FatNodeData_WaitWrite(self)   shared_rwlock_waitwrite(&(self)->fn_lock)
#define /*BLOCKING*/ FatNodeData_WaitReadNx(self)  shared_rwlock_waitread_nx(&(self)->fn_lock)
#define /*BLOCKING*/ FatNodeData_WaitWriteNx(self) shared_rwlock_waitwrite_nx(&(self)->fn_lock)



struct fatregnode: fregnode {
	FatNodeData frn_fdat; /* Fat node data. */
};

struct fatdirnode: flatdirnode {
	FatNodeData fdn_fdat; /* Fat node data. */
	uint32_t    fdn_1dot; /* [lock(ATOMIC && WRITE_ONCE)] Position of "." entry in directory stream (or `(uint32_t)-1' if unknown). */
	uint32_t    fdn_2dot; /* [lock(ATOMIC && WRITE_ONCE)] Position of ".." entry in directory stream (or `(uint32_t)-1' if unknown). */
};
#define FatDirNode_AsSuper(self) \
	flatsuper_asfat(flatdirnode_assuper((struct flatdirnode *)(self)))

#ifdef CONFIG_FAT_CYGWIN_SYMLINKS
typedef struct fatlnknode FatLnkNode;
struct fatlnknode: flnknode {
	FatNodeData fln_fdat; /* Fat node data. */
};
#endif /* CONFIG_FAT_CYGWIN_SYMLINKS */

#define fregnode_asfat(self)    ((FatRegNode *)(self))
#define flatdirnode_asfat(self) ((FatDirNode *)(self))
#define fdirnode_asfat(self)    flatdirnode_asfat(fdirnode_asflat(self))
#define fdirnode_asfatsup(self) FatDirNode_AsSuper(fdirnode_asfat(self))
#ifdef CONFIG_FAT_CYGWIN_SYMLINKS
#define flnknode_asfat(self) ((FatLnkNode *)(self))
#endif /* CONFIG_FAT_CYGWIN_SYMLINKS */
#define fnode_asfatreg(self) fregnode_asfat(fnode_asreg(self))
#define fnode_asfatdir(self) flatdirnode_asfat(fnode_asflatdir(self))
#define fnode_asfatlnk(self) flnknode_asfat(fnode_aslnk(self))
#define fnode_asfatsup(self) FatDirNode_AsSuper(fnode_asfatdir(self))
#define mfile_asfatreg(self) fregnode_asfat(mfile_asreg(self))
#define mfile_asfatdir(self) flatdirnode_asfat(mfile_asflatdir(self))
#define mfile_asfatlnk(self) flnknode_asfat(mfile_aslnk(self))
#define mfile_asfatsup(self) FatDirNode_AsSuper(mfile_asfatdir(self))


typedef NOBLOCK NONNULL_T((1)) FatClusterIndex (FCALL *PFatGetFatIndirection)(FatSuperblock const *__restrict self, FatClusterIndex index);
typedef NOBLOCK NONNULL_T((1)) void (FCALL *PFatSetFatIndirection)(FatSuperblock *__restrict self, FatClusterIndex index, FatClusterIndex indirection_target);

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
#ifndef CONFIG_NO_SMP
	struct atomic_lock      fs_stringslock; /* SMP-Lock for `ft_oem', `ft_label' and `ft_sysname' */
#endif /* !CONFIG_NO_SMP */
	char                    ft_oem[9];      /* [const] OEM identifier. */
	char                    ft_label[12];   /* [const] Volume label string (zero-terminated). */
	char                    ft_sysname[9];  /* [const] System identifier string (zero-terminated). */
	u32                     ft_volid;       /* [const] FAT Volume ID. */
	u8                     _ft_pad;         /* ... */
	u8                      ft_fat_count;   /* [const] Amount of redundant FAT copies. */
#ifdef __INTELLISENSE__
	shift_t                 ft_sectorshift; /* [const] ilog2(SECTOR_SIZE) (in bytes). */
#else /* __INTELLISENSE__ */
#define ft_sectorshift      ft_super.ffs_super.fs_root.mf_blockshift  /* [const] ilog2(SECTOR_SIZE) (in bytes). */
#endif /* !__INTELLISENSE__ */
	size_t                  ft_sectormask;  /* [const][== (1 << ft_sectorshift) - 1] Size of a sector (in bytes). */
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
	void                   *ft_freefat;     /* [1..1][owned][const] Used for unmapping `ft_fat_table' */
	REF struct mfile       *ft_fat_file;    /* [1..1][const] The mem-file used to map `ft_fat_table'. */
	FatClusterIndex         ft_free_pos;    /* [lock(ft_fat_lock)] Next cluster index that should be considered when search for free clusters. */
	struct flatsuper        ft_super;       /* Underlying superblock */
	FatNodeData             ft_fdat;        /* Fat root directory node data. */
	uint32_t                _ft_1dot;       /* s.a. `struct fatdirnode::fdn_1dot' */
	uint32_t                _ft_2dot;       /* s.a. `struct fatdirnode::fdn_2dot' */
};
#define flatsuper_asfat(self) COMPILER_CONTAINER_OF(self, FatSuperblock, ft_super)
#define fsuper_asfat(self)    COMPILER_CONTAINER_OF(self, FatSuperblock, ft_super.ffs_super)


/* Helpers for accessing `ft_fat_lock' */
#define /*        */ _FatSuper_FatLockReap(self)       (void)0
#define /*        */ FatSuper_FatLockReap(self)        (void)0
#define /*        */ FatSuper_FatLockMustReap(self)    0
#define /*BLOCKING*/ FatSuper_FatLockWrite(self)       shared_rwlock_write(&(self)->ft_fat_lock)
#define /*BLOCKING*/ FatSuper_FatLockWriteNx(self)     shared_rwlock_write_nx(&(self)->ft_fat_lock)
#define /*        */ FatSuper_FatLockTryWrite(self)    shared_rwlock_trywrite(&(self)->ft_fat_lock)
#define /*        */ FatSuper_FatLockEndWrite(self)    (shared_rwlock_endwrite(&(self)->ft_fat_lock), FatSuper_FatLockReap(self))
#define /*        */ _FatSuper_FatLockEndWrite(self)   shared_rwlock_endwrite(&(self)->ft_fat_lock)
#define /*BLOCKING*/ FatSuper_FatLockRead(self)        shared_rwlock_read(&(self)->ft_fat_lock)
#define /*BLOCKING*/ FatSuper_FatLockReadNx(self)      shared_rwlock_read_nx(&(self)->ft_fat_lock)
#define /*        */ FatSuper_FatLockTryRead(self)     shared_rwlock_tryread(&(self)->ft_fat_lock)
#define /*        */ _FatSuper_FatLockEndRead(self)    shared_rwlock_endread(&(self)->ft_fat_lock)
#define /*        */ FatSuper_FatLockEndRead(self)     (void)(shared_rwlock_endread(&(self)->ft_fat_lock) && (FatSuper_FatLockReap(self), 0))
#define /*        */ _FatSuper_FatLockEnd(self)        shared_rwlock_end(&(self)->ft_fat_lock)
#define /*        */ FatSuper_FatLockEnd(self)         (void)(shared_rwlock_end(&(self)->ft_fat_lock) && (FatSuper_FatLockReap(self), 0))
#define /*BLOCKING*/ FatSuper_FatLockUpgrade(self)     shared_rwlock_upgrade(&(self)->ft_fat_lock)
#define /*        */ FatSuper_FatLockTryUpgrade(self)  shared_rwlock_tryupgrade(&(self)->ft_fat_lock)
#define /*        */ FatSuper_FatLockDowngrade(self)   shared_rwlock_downgrade(&(self)->ft_fat_lock)
#define /*        */ FatSuper_FatLockReading(self)     shared_rwlock_reading(&(self)->ft_fat_lock)
#define /*        */ FatSuper_FatLockWriting(self)     shared_rwlock_writing(&(self)->ft_fat_lock)
#define /*        */ FatSuper_FatLockCanRead(self)     shared_rwlock_canread(&(self)->ft_fat_lock)
#define /*        */ FatSuper_FatLockCanWrite(self)    shared_rwlock_canwrite(&(self)->ft_fat_lock)
#define /*BLOCKING*/ FatSuper_FatLockWaitRead(self)    shared_rwlock_waitread(&(self)->ft_fat_lock)
#define /*BLOCKING*/ FatSuper_FatLockWaitWrite(self)   shared_rwlock_waitwrite(&(self)->ft_fat_lock)
#define /*BLOCKING*/ FatSuper_FatLockWaitReadNx(self)  shared_rwlock_waitread_nx(&(self)->ft_fat_lock)
#define /*BLOCKING*/ FatSuper_FatLockWaitWriteNx(self) shared_rwlock_waitwrite_nx(&(self)->ft_fat_lock)

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

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_MODFAT_FAT_H */
