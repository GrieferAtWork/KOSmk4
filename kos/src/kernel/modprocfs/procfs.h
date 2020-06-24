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
#ifndef GUARD_MODPROCFS_PROCFS_H
#define GUARD_MODPROCFS_PROCFS_H 1

#include <kernel/compiler.h>

#include <fs/node.h>

#include <format-printer.h>
#include <stdint.h>

DECL_BEGIN

/* Mask and shift for the type of some given INode.
 * All remaining bits of any given INO are interpreted depending of the type mask,
 * which is one of the `PROCFS_INOTYPE_*' constants. */
#define PROCFS_INO_TYPEMASK UINT64_C(0xff00000000000000)
#define PROCFS_INO_TYPESHFT 56

#define PROCFS_INOTYPE_SINGLETON        0x00   /* Singleton INode (anything that appears only once in /proc) */
#define PROCFS_INOTYPE_SINGLETON_IDMASK 0xffff /* Mask for the ID of a singleton */
/* @param: id: One of PROCFS_SINGLETON_* */
#define PROCFS_INOMAKE_SINGLETON(id) \
	(((ino_t)PROCFS_INOTYPE_SINGLETON << PROCFS_INO_TYPESHFT) | (id))

/* Per-process data */
#define PROCFS_INOTYPE_PERPROC         0x01                         /* Per-process INode */
#define PROCFS_INOTYPE_PERPROC_PIDMASK UINT64_C(0x000000007fffffff) /* PID mask */
#define PROCFS_INOTYPE_PERPROC_IDMASK  UINT64_C(0x0000ffff00000000) /* ID mask */
#define PROCFS_INOTYPE_PERPROC_IDSHIFT 32
/* @param: id: One of PROCFS_PERPROC_* */
#define PROCFS_INOMAKE_PERPROC(pid, id)                       \
	(((ino_t)PROCFS_INOTYPE_PERPROC << PROCFS_INO_TYPESHFT) | \
	 ((ino_t)(id) << PROCFS_INOTYPE_PERPROC_IDSHIFT) | (ino_t)(pid))

/* DOS Drive bindings. `readlink /proc/[pid]/kos/drives/[a-z]' */
#define PROCFS_INOTYPE_DRIVE          0x02                         /* Per-process drives */
#define PROCFS_INOTYPE_DRIVE_PIDMASK  UINT64_C(0x000000007fffffff) /* PID mask */
#define PROCFS_INOTYPE_DRIVE_DRVMASK  UINT64_C(0x0000001f00000000) /* DOS Drive id ('a' + .) */
#define PROCFS_INOTYPE_DRIVE_DRVSHIFT 32
#define PROCFS_INOMAKE_DRIVE(pid, drive_id)                 \
	(((ino_t)PROCFS_INOTYPE_DRIVE << PROCFS_INO_TYPESHFT) | \
	 ((ino_t)(drive_id) << PROCFS_INOTYPE_DRIVE_DRVSHIFT) | (ino_t)(pid))

/* DOS Drive cwd bindings. `readlink /proc/[pid]/kos/dcwd/[a-z]' */
#define PROCFS_INOTYPE_DCWD          0x03                         /* Per-process drives */
#define PROCFS_INOTYPE_DCWD_PIDMASK  UINT64_C(0x000000007fffffff) /* PID mask */
#define PROCFS_INOTYPE_DCWD_DRVMASK  UINT64_C(0x0000001f00000000) /* DOS Drive id ('a' + .) */
#define PROCFS_INOTYPE_DCWD_DRVSHIFT 32
#define PROCFS_INOMAKE_DCWD(pid, drive_id)                 \
	(((ino_t)PROCFS_INOTYPE_DCWD << PROCFS_INO_TYPESHFT) | \
	 ((ino_t)(drive_id) << PROCFS_INOTYPE_DCWD_DRVSHIFT) | (ino_t)(pid))

/* File handle bindings. `readlink /proc/[pid]/fd/[id]' */
#define PROCFS_INOTYPE_FD_LO      0x80                         /* Per-process file handles */
#define PROCFS_INOTYPE_FD_HI      0xff                         /* Per-process file handles */
#define PROCFS_INOTYPE_FD_PIDMASK UINT64_C(0x000000007fffffff) /* PID mask */
#define PROCFS_INOTYPE_FD_FDMASK  UINT64_C(0x7fffffff80000000) /* File handle number */
#define PROCFS_INOTYPE_FD_FDSHIFT 31
#define PROCFS_INOMAKE_FD(pid, fd)                          \
	(((ino_t)PROCFS_INOTYPE_FD_LO << PROCFS_INO_TYPESHFT) | \
	 ((ino_t)(fd) << PROCFS_INOTYPE_FD_FDSHIFT) | (ino_t)(pid))



#define PROCFS_SINGLETON_DATA_FIELDS                                                                                          \
	struct timespec psd_atime; /* File last-accessed timestamp (initialized to the time when the procfs driver was loaded) */ \
	struct timespec psd_mtime; /* File last-modified timestamp (initialized to the time when the procfs driver was loaded) */ \
	struct timespec psd_ctime; /* File creation timestamp (initialized to the time when the procfs driver was loaded) */      \
	mode_t          psd_mode;  /* File access mode (NOTE: Also encodes the file type, however that part is [const]) */        \
	uid_t           psd_uid;   /* File owner UID (initialized to 0) */                                                        \
	gid_t           psd_gid;   /* File group GID (initialized to 0) */
	
struct procfs_singleton_data {
	/* Pointed to by the `struct inode_data *i_fsdata' of singleton INodes.
	 * These are the saved, non-volatile values of various file attributes,
	 * thus allowing user-space to (e.g.) change the access permissions, or
	 * ownership of some given file under /proc, so-long as that file is a
	 * singleton inside of the filesystem */
	PROCFS_SINGLETON_DATA_FIELDS
};

struct procfs_singleton_dir_data {
	/* FS-data for singletons defined as `MKDIR()' */
	PROCFS_SINGLETON_DATA_FIELDS
	COMPILER_FLEXIBLE_ARRAY(REF struct directory_entry *, pdd_ents); /* [1..1|SENTINEL(NULL)][const]
	                                                                  * NULL-terminated list of contained files
	                                                                  * Hash set to `(uintptr_t)-1' are calculated lazily. */
};

/* Prototype for printer functions defined by `MKREG_RO()' */
typedef NONNULL((1, 2)) ssize_t
(KCALL *PROCFS_REG_PRINTER)(struct regular_node *__restrict self,
                            pformatprinter printer, void *arg);
typedef NONNULL((1)) void
(KCALL *PROCFS_REG_WRITER)(struct regular_node *__restrict self,
                           USER CHECKED void const *buf, size_t buflen);

struct procfs_singleton_reg_ro_data {
	PROCFS_SINGLETON_DATA_FIELDS
	PROCFS_REG_PRINTER psr_printer; /* [1..1][const] Printer for generating the contents of the file. */
};

struct procfs_singleton_reg_rw_data {
	PROCFS_SINGLETON_DATA_FIELDS
	PROCFS_REG_PRINTER psr_printer; /* [1..1][const] Printer for generating the contents of the file. */
	PROCFS_REG_WRITER  psr_writer;  /* [1..1][const] Writer for setting the contents of the file. */
};

struct procfs_perproc_reg_rw_data {
	PROCFS_REG_PRINTER ppr_printer; /* [1..1][const] Printer for generating the contents of the file. */
	PROCFS_REG_WRITER  ppr_writer;  /* [1..1][const] Writer for setting the contents of the file. */
};

/* Prototype for printer functions defined by `SYMLINK()' */
typedef NONNULL((2)) size_t (KCALL *PROCFS_SYMLINK_READLINK)(struct symlink_node *__restrict self,
                                                             USER CHECKED /*utf-8*/ char *buf,
                                                             size_t bufsize);

struct procfs_singleton_dynamic_symlink_data {
	PROCFS_SINGLETON_DATA_FIELDS
	PROCFS_SYMLINK_READLINK pss_readlink; /* [1..1][const] Dynamically invoked readlink() function. */
};


/* Values for singleton Inodes (for use with `PROCFS_INOMAKE_SINGLETON(PROCFS_SINGLETON_*)'). */
enum {
	PROCFS_SINGLETON_ROOT = 0, /* /proc  (Must always remain `0') */

#define MKDIR(id, mode, files) PROCFS_SINGLETON_ID_##id,
#include "singleton.def"
	PROCFS_SINGLETON_START_REG_RO,
	__PROCFS_SINGLETON_START_REG_RO = PROCFS_SINGLETON_START_REG_RO - 1,
#define MKREG_RO(id, mode, printer) PROCFS_SINGLETON_ID_##id,
#include "singleton.def"
	PROCFS_SINGLETON_START_REG_RW,
	__PROCFS_SINGLETON_START_REG_RW = PROCFS_SINGLETON_START_REG_RW - 1,
#define MKREG_RW(id, mode, reader, writer) PROCFS_SINGLETON_ID_##id,
#include "singleton.def"
	PROCFS_SINGLETON_START_LNK_DYN,
	__PROCFS_SINGLETON_START_LNK_DYN = PROCFS_SINGLETON_START_LNK_DYN - 1,
#define DYNAMIC_SYMLINK(id, mode, readlink) PROCFS_SINGLETON_ID_##id,
#include "singleton.def"
#ifndef PROCFS_NO_CUSTOM
	PROCFS_SINGLETON_START_CUSTOM,
	__PROCFS_SINGLETON_START_CUSTOM = PROCFS_SINGLETON_START_CUSTOM - 1,
#define CUSTOM(id, type) PROCFS_SINGLETON_ID_##id,
#include "singleton.def"
#endif /* !PROCFS_NO_CUSTOM */
	PROCFS_SINGLETON_COUNT
};


enum {
	PROCFS_PERPROC_ROOT = 0, /* /proc/[pid]  (Must always remain `0') */
#define MKDIR(id, mode, files) PROCFS_PERPROC_ID_##id,
#include "perproc.def"
	PROCFS_PERPROC_START_REG_RO,
	__PROCFS_PERPROC_START_REG_RO = PROCFS_PERPROC_START_REG_RO - 1,
#define MKREG_RO(id, mode, printer) PROCFS_PERPROC_ID_##id,
#include "perproc.def"
	PROCFS_PERPROC_START_REG_RW,
	__PROCFS_PERPROC_START_REG_RW = PROCFS_PERPROC_START_REG_RW - 1,
#define MKREG_RW(id, mode, reader, writer) PROCFS_PERPROC_ID_##id,
#include "perproc.def"
	PROCFS_PERPROC_START_LNK_DYN,
	__PROCFS_PERPROC_START_LNK_DYN = PROCFS_PERPROC_START_LNK_DYN - 1,
#define DYNAMIC_SYMLINK(id, mode, readlink) PROCFS_PERPROC_ID_##id,
#include "perproc.def"
#ifndef PROCFS_PERPROC_NO_CUSTOM
	PROCFS_PERPROC_START_CUSTOM,
	__PROCFS_PERPROC_START_CUSTOM = PROCFS_PERPROC_START_CUSTOM - 1,
#define CUSTOM(id, mode, type) PROCFS_PERPROC_ID_##id,
#include "perproc.def"
#endif /* !PROCFS_PERPROC_NO_CUSTOM */
	PROCFS_PERPROC_COUNT
};



/* [1..1][*] Fs-specific data pointers for singleton nodes.
 * The index to this array is one of `PROCFS_SINGLETON_*' */
INTDEF struct procfs_singleton_data *const ProcFS_Singleton_FsData[PROCFS_SINGLETON_COUNT];
#ifndef PROCFS_NO_CUSTOM
INTDEF struct inode_type *const ProcFS_Singleton_CustomTypes[PROCFS_SINGLETON_COUNT - PROCFS_SINGLETON_START_CUSTOM];
#endif /* !PROCFS_NO_CUSTOM */
INTDEF struct inode_type ProcFS_Singleton_Directory_Type;      /* Type for general-purpose singleton directories */
INTDEF struct inode_type ProcFS_Singleton_RegularRo_Type;      /* Type for general-purpose singleton read-only files */
INTDEF struct inode_type ProcFS_Singleton_RegularRw_Type;      /* Type for general-purpose singleton read/write files */
INTDEF struct inode_type ProcFS_Singleton_DynamicSymlink_Type; /* Type for general-purpose singleton dynamic symlink files */

/* For MIDIR:           `REF struct directory_entry **'
 * For MKREG_RO:        `PROCFS_REG_PRINTER'
 * For DYNAMIC_SYMLINK: `PROCFS_SYMLINK_READLINK'
 * For CUSTOM:          `NULL' */
INTDEF void *const ProcFS_PerProc_FsData[PROCFS_PERPROC_COUNT];
INTDEF mode_t const ProcFS_PerProc_FileMode[PROCFS_PERPROC_COUNT];
#ifndef PROCFS_PERPROC_NO_CUSTOM
INTDEF struct inode_type *const ProcFS_PerProc_CustomTypes[PROCFS_PERPROC_COUNT - PROCFS_PERPROC_START_CUSTOM];
#endif /* !PROCFS_PERPROC_NO_CUSTOM */
INTDEF struct inode_type ProcFS_PerProc_Directory_Type;      /* Type for general-purpose singleton directories */
INTDEF struct inode_type ProcFS_PerProc_RegularRo_Type;      /* Type for general-purpose singleton read-only files */
INTDEF struct inode_type ProcFS_PerProc_RegularRw_Type;      /* Type for general-purpose singleton read/write files */
INTDEF struct inode_type ProcFS_PerProc_DynamicSymlink_Type; /* Type for general-purpose singleton dynamic symlink files */

INTDEF NONNULL((1)) void KCALL ProcFS_Singleton_LoadAttr(struct inode *__restrict self) THROWS(E_IOERROR, ...);
INTDEF NONNULL((1)) void KCALL ProcFS_Singleton_SaveAttr(struct inode *__restrict self) THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_READONLY, E_IOERROR, ...);

/* ProcFS_Singleton_Directory_Type.it_directory.d_oneshot.o_lookup */
INTDEF NONNULL((1, 2)) REF struct directory_entry *KCALL
ProcFS_Singleton_Directory_Lookup(struct directory_node *__restrict self,
                                  CHECKED USER /*utf-8*/ char const *__restrict name,
                                  u16 namelen, uintptr_t hash, fsmode_t mode)
		THROWS(E_SEGFAULT, E_FSERROR_FILE_NOT_FOUND,
		       E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...);

/* ProcFS_Singleton_Directory_Type.it_directory.d_oneshot.o_enum */
INTDEF NONNULL((1, 2)) void KCALL
ProcFS_Singleton_Directory_Enum(struct directory_node *__restrict self,
                                directory_enum_callback_t callback,
                                void *arg)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...);


INTDEF REF struct directory_entry *ProcFS_PerProcRootDirectory_FsData[];
INTDEF struct procfs_singleton_dir_data ProcFS_RootDirectory_FsData;
INTDEF struct inode_type ProcFS_RootDirectory_Type;
INTDEF struct inode_type ProcFS_PerProcRootDirectory_Type;
INTDEF struct inode_type ProcFS_PerProc_Kos_Drives_Entry_Type; /* For `PROCFS_INOTYPE_DRIVE' */
INTDEF struct inode_type ProcFS_PerProc_Kos_Dcwd_Entry_Type; /* For `PROCFS_INOTYPE_DCWD' */
INTDEF struct inode_type ProcFS_PerProc_Fd_Entry_Type; /* For `PROCFS_INOTYPE_FD_(LO|HI)' */

INTDEF struct superblock_type ProcFS_Type;
INTDEF struct superblock ProcFS;

INTDEF NONNULL((1, 2, 3, 4)) void KCALL
ProcFS_OpenNode(struct superblock *__restrict self,
                struct inode *__restrict node,
                struct directory_node *__restrict parent_directory,
                struct directory_entry *__restrict parent_directory_entry);


/* Define printer functions used by singleton files */
#define DYNAMIC_SYMLINK(id, mode, readlink)                                         \
	INTDEF NONNULL((1)) size_t KCALL readlink(struct symlink_node *__restrict self, \
	                                          USER CHECKED /*utf-8*/ char *buf,     \
	                                          size_t bufsize);
#define MKREG_RO(id, mode, printer)                                                    \
	INTDEF NONNULL((1, 2)) ssize_t KCALL printer(struct regular_node *__restrict self, \
	                                             pformatprinter printer_, void *arg);
#define MKREG_RW(id, mode, reader, writer)                                            \
	INTDEF NONNULL((1, 2)) ssize_t KCALL reader(struct regular_node *__restrict self, \
	                                            pformatprinter printer_, void *arg);  \
	INTDEF NONNULL((1)) void KCALL writer(struct regular_node *__restrict self,     \
	                                      USER CHECKED void const *buf, size_t buflen);
#define CUSTOM(id, type) \
	INTDEF struct inode_type type;
#include "singleton.def"


/* Define printer functions used by singleton files */
#define DYNAMIC_SYMLINK(id, mode, readlink)                                         \
	INTDEF NONNULL((1)) size_t KCALL readlink(struct symlink_node *__restrict self, \
	                                          USER CHECKED /*utf-8*/ char *buf,     \
	                                          size_t bufsize);
#define MKREG_RO(id, mode, printer)                                                    \
	INTDEF NONNULL((1, 2)) ssize_t KCALL printer(struct regular_node *__restrict self, \
	                                             pformatprinter printer_, void *arg);
#define MKREG_RW(id, mode, reader, writer)                                            \
	INTDEF NONNULL((1, 2)) ssize_t KCALL reader(struct regular_node *__restrict self, \
	                                            pformatprinter printer_, void *arg);  \
	INTDEF NONNULL((1)) void KCALL writer(struct regular_node *__restrict self,     \
	                                      USER CHECKED void const *buf, size_t buflen);
#define CUSTOM(id, mode, type) \
	INTDEF struct inode_type type;
#include "perproc.def"


DECL_END

#endif /* !GUARD_MODPROCFS_PROCFS_H */
