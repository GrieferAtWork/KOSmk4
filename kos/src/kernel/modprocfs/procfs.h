/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef GUARD_MODPROCFS_PROCFS_H
#define GUARD_MODPROCFS_PROCFS_H 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <stdint.h>
#include <format-printer.h>

DECL_BEGIN

/* Mask and shift for the type of some given INode.
 * All remaining bits of any given INO are interpreted depending of the type mask,
 * which is one of the `PROCFS_INOTYPE_*' constants. */
#define PROCFS_INO_TYPEMASK UINT64_C(0xff0000ff00000000)
#define PROCFS_INO_TYPESHFT 56

#define PROCFS_INOTYPE_SINGLETON 0x00 /* Singleton INode (anything that appears only once in /proc) */
#define PROCFS_INOTYPE_SINGLETON_IDMASK 0xffff /* Mask for the ID of a singleton */
#define PROCFS_INOMAKE_SINGLETON(id) (((ino_t)PROCFS_INOTYPE_SINGLETON << PROCFS_INO_TYPESHFT) | (id))

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
typedef NONNULL((2)) ssize_t (KCALL *PROCFS_REG_PRINTER)(struct inode *__restrict self,
                                                         pformatprinter printer, void *arg);

struct procfs_singleton_reg_ro_data {
	PROCFS_SINGLETON_DATA_FIELDS
	PROCFS_REG_PRINTER psr_printer; /* [1..1][const] Printer for generating the contents of the file. */
};

/* Values for singleton Inodes (for use with `PROCFS_INOMAKE_SINGLETON(PROCFS_SINGLETON_*)'). */
enum {
	PROCFS_SINGLETON_ROOT = 0, /* /proc  (Must always remain `0') */

#define MKDIR(id, mode, files) PROCFS_SINGLETON_ID_##id,
#include "singleton.h"
	PROCFS_SINGLETON_START_REG_RO,
	__PROCFS_SINGLETON_START_REG_RO = PROCFS_SINGLETON_START_REG_RO - 1,
#define MKREG_RO(id, mode, printer) PROCFS_SINGLETON_ID_##id,
#include "singleton.h"
	PROCFS_SINGLETON_COUNT
};


/* [1..1][*] Fs-specific data pointers for singleton nodes.
 * The index to this array is one of `PROCFS_SINGLETON_*' */
INTDEF struct procfs_singleton_data *const ProcFS_Singleton_FsData[PROCFS_SINGLETON_COUNT];
INTDEF struct inode_type ProcFS_Singleton_Directory_Type; /* Type for general-purpose singleton directories */
INTDEF struct inode_type ProcFS_Singleton_RegularRo_Type; /* Type for general-purpose singleton read-only files */


INTDEF struct procfs_singleton_dir_data ProcFS_RootDirectory_FsData;
INTDEF struct inode_type ProcFS_RootDirectory_Type;

INTDEF struct superblock_type ProcFS_Type;
INTDEF struct superblock ProcFS;

INTDEF NONNULL((1, 2, 3, 4)) void KCALL
ProcFS_OpenNode(struct superblock *__restrict self,
                struct inode *__restrict node,
                struct directory_node *__restrict parent_directory,
                struct directory_entry *__restrict parent_directory_entry);


/* Define printer functions used by singleton files */
#define MKREG_RO(id, mode, printer)                                          \
	INTDEF NONNULL((2)) ssize_t KCALL printer(struct inode *__restrict self, \
	                                          pformatprinter printer_, void *arg);
#include "singleton.h"


DECL_END

#endif /* !GUARD_MODPROCFS_PROCFS_H */
