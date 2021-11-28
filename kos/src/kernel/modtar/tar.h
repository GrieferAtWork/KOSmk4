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
#ifndef GUARD_MODTAR_TAR_H
#define GUARD_MODTAR_TAR_H 1

/*
 * Filesystem driver for mounting `*.tar'-files as (read-only) superblocks
 */

#include <kernel/compiler.h>

DECL_BEGIN
struct tarfdat;
DECL_END
#define FNODE_FSDATA_T struct tarfdat

#include <kernel/fs/devnode.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/lnknode.h>
#include <kernel/fs/regnode.h>
#include <kernel/fs/super.h>
#include <kernel/malloc.h>
#include <kernel/types.h>

#include <hybrid/sequence/list.h>

#include <kos/sched/shared-rwlock.h>

#include <stddef.h>

DECL_BEGIN

/* Tar filesystem constants. */
#define TARFS_BLOCKSIZE  512
#define TARFS_BLOCKSHIFT 9 /* == log2(TARFS_BLOCKSIZE) */


/* Possible values for `struct tarhdr::th_type' */
#define TARHDR_TYPE_REG  '0'  /* Normal file */
#define TARHDR_TYPE_REG2 '\0' /* Regular file (alias) */
#define TARHDR_TYPE_HRD  '1'  /* Hard-link */
#define TARHDR_TYPE_SYM  '2'  /* Symlink */
#define TARHDR_TYPE_CHR  '3'  /* [valid_if(th_ustar == "ustar\0")] Character special */
#define TARHDR_TYPE_BLK  '4'  /* [valid_if(th_ustar == "ustar\0")] Block special */
#define TARHDR_TYPE_DIR  '5'  /* [valid_if(th_ustar == "ustar\0")] Directory */
#define TARHDR_TYPE_FIFO '6'  /* [valid_if(th_ustar == "ustar\0")] FIFO */
#define TARHDR_TYPE_REG3 '7'  /* [valid_if(th_ustar == "ustar\0")] Another alias for regular files */

struct tarhdr {
	char th_filename[100]; /* Absolute filename. */
	char th_mode[8];       /* File mode (octal-ascii). */
	char th_uid[8];        /* File uid (octal-ascii). */
	char th_gid[8];        /* File gid (octal-ascii). */
	char th_size[12];      /* File size (in bytes; octal-ascii). */
	char th_mtime[12];     /* Last-modified time (seconds-since-01.01.1970T00:00; octal-ascii). */
	char th_chksum[8];     /* Checksum (octal-ascii). */
	char th_type;          /* File type (one of `TARHDR_TYPE_*'). */
	char th_lnkname[100];  /* [valid_if(th_type == TARHDR_TYPE_HRD || th_type == TARHDR_TYPE_SYM)]
	                        * Linked file filename, or symlink text. */
	/* Everything that follows is [valid_if(th_ustar == "ustar\0")] */
	char th_ustar[6];      /* The string "ustar\0" (if ustar format is used) */
	char th_uvers[2];      /* ustar version string ("00") */
	char th_uname[32];     /* Name for `th_uid' */
	char th_gname[32];     /* Name for `th_gid' */
	char th_devmajor[8];   /* [valid_if(TARHDR_TYPE_CHR || TARHDR_TYPE_BLK)] Major number for device. */
	char th_devminor[8];   /* [valid_if(TARHDR_TYPE_CHR || TARHDR_TYPE_BLK)] Minor number for device. */
	char th_filepfx[155];  /* Prefix for `th_filename' */
};

STATIC_ASSERT(offsetof(struct tarhdr, th_type) == 156);
STATIC_ASSERT(offsetof(struct tarhdr, th_devmajor) == 329);
STATIC_ASSERT(sizeof(struct tarhdr) == 500);


/* Decoded tar file information */
struct tarfile {
	pos_t                         tf_pos;     /* [const] On-disk starting position of file data (also re-used as INode number) */
	union {
		TAILQ_ENTRY(tarfile)      tf_bypos;   /* [lock(:ts_lock)] List of all files, sorted by `tf_pos'. */
		SLIST_ENTRY(tarfile)     _tf_dead;    /* Used internally. */
	};
	refcnt_t                      tf_refcnt;  /* Reference counter. */
	uint32_t                      tf_size;    /* [const] File size (in bytes) */
	int32_t                       tf_mtim;    /* [const] Last-modified timestamp */
	uint16_t                      tf_mode;    /* [const] File mode+permissions (S_IFMT | 07777) */
	uint16_t                      tf_uid;     /* [const] User ID */
	uint16_t                      tf_gid;     /* [const] Group ID */
	COMPILER_FLEXIBLE_ARRAY(char, tf_name);   /* [const] Absolute filename (with leading "/./././"-nonsense removed) */
/*	uint32_t                      tf_devno;    * [EXISTS_IF(S_IFDEV(tf_mode))][ALIGN(., 4)] Device number */
/*	char                          tf_lnkstr[]; * [EXISTS_IF(S_IFLNK(tf_mode))] Symbolic link text */
/*	char                          tf_hrdstr[]; * [EXISTS_IF((tf_mode & S_IFMT) == 0)] Name of linked file */
};
#define tarfile_destroy(self) kfree(self)
DEFINE_REFCOUNT_FUNCTIONS(struct tarfile, tf_refcnt, tarfile_destroy)

/* Accessors for hidden fields. */
#define __tarfile_hidden(self)  (strend((self)->tf_name) + 1)
#define tarfile_getdevno(self)  ((dev_t)(*(uint32_t const *)CEIL_ALIGN((uintptr_t)__tarfile_hidden(self), 4)))
#define tarfile_getlnkstr(self) ((char const *)__tarfile_hidden(self))
#define tarfile_gethrdstr(self) ((char const *)__tarfile_hidden(self))


/* Allocate a new tarfile descriptor. The caller must still fill in `return->tf_pos'
 * Returns `NULL' for unknown file types (that  will only be defined in the  future) */
INTDEF WUNUSED struct tarfile *FCALL
tarfile_new(struct tarhdr const *__restrict self,
            uint32_t *__restrict p_filesize)
		THROWS(E_FSERROR_CORRUPTED_FILE_SYSTEM);


struct tarfdat {
	REF struct tarfile *tfd_filp; /* [0..1][const]  Referenced file (or `NULL' for root directory)
	                               * For directories, this is either the tarfile for the directory
	                               * itself, or some random file reachable from the directory, but
	                               * note the special case for the root directory. */
	char const         *tfd_name; /* [0..tfd_nlen][const] Absolute filename (points into `tfd_filp',
	                               * but  may not necessary  NUL-term in case  this is a directory). */
	uint8_t             tfd_nlen; /* [const] Length of `tfd_name' (in characters); anything after must be ignored. */
};


/* Tar file types. */
struct tardirnode: fdirnode {
	struct tarfdat tdn_fdat; /* Common file data */
};

struct tarregnode: fregnode {
	struct tarfdat trn_fdat; /* Common file data */
};

struct tarlnknode: flnknode {
	struct tarfdat tln_fdat; /* Common file data */
};

struct tardevnode: fdevnode {
	struct tarfdat tln_fdat; /* Common file data */
};


/* Tar directory entry. */
struct tardirent {
	REF struct tarfile *td_filp; /* [1..1][const] Referenced file. In case of a directory, this
	                              * may either be the directory's  file object itself, or  some
	                              * random  file inside  that directory.  These 2  cases can be
	                              * differentiated by looking at `td_filp->tf_mode'. */
	struct fdirent      td_ent;  /* Underlying directory entry. */
};

SLIST_HEAD(tarfile_slist, tarfile);
TAILQ_HEAD(tarfile_tailq, tarfile);

/* Tar superblock. */
struct tarsuper {
	struct shared_rwlock ts_lock;   /* Lock for the global file table. */
	REF struct tarfile **ts_filev;  /* [1..1][0..ts_filec][owned][lock(ts_lock)]   Global
	                                 * file table. (sorted lex. ascendingly by `tf_name') */
	size_t               ts_filec;  /* [lock(ts_lock)] # of files in `ts_filev' */
	struct tarfile_tailq ts_bypos;  /* [0..n][lock(ts_lock)]  List of tar files, sorted by position.
	                                 * The files in this list are identical to those from `ts_filev' */
	pos_t                ts_nfile;  /* [lock(ts_lock)] Absolute on-disk position of the  next
	                                 * tarhdr-file that (may) have not been loaded, yet. When
	                                 * >= the size of the underlying device, then all files
	                                 * are loaded.
	                                 * In  order  to  conserve memory,  tarfs  implements the
	                                 * clear caches operator such that all global files  that
	                                 * are not externally referenced are discarded, following
	                                 * `ts_nfile' being set to `0'. */
	struct fsuper        ts_super;  /* Underlying superblock. */
	struct tarfdat       ts_fdat;   /* Root directory file data. */
};

/* Helpers for accessing `struct tarsuper::ts_lock' */
#define /*        */ _tarsuper_reap(self)        (void)0
#define /*        */ tarsuper_reap(self)         (void)0
#define /*        */ tarsuper_mustreap(self)     0
#define /*BLOCKING*/ tarsuper_write(self)        shared_rwlock_write(&(self)->ts_lock)
#define /*BLOCKING*/ tarsuper_write_nx(self)     shared_rwlock_write_nx(&(self)->ts_lock)
#define /*        */ tarsuper_trywrite(self)     shared_rwlock_trywrite(&(self)->ts_lock)
#define /*        */ tarsuper_endwrite(self)     (shared_rwlock_endwrite(&(self)->ts_lock), tarsuper_reap(self))
#define /*        */ _tarsuper_endwrite(self)    shared_rwlock_endwrite(&(self)->ts_lock)
#define /*BLOCKING*/ tarsuper_read(self)         shared_rwlock_read(&(self)->ts_lock)
#define /*BLOCKING*/ tarsuper_read_nx(self)      shared_rwlock_read_nx(&(self)->ts_lock)
#define /*        */ tarsuper_tryread(self)      shared_rwlock_tryread(&(self)->ts_lock)
#define /*        */ _tarsuper_endread(self)     shared_rwlock_endread(&(self)->ts_lock)
#define /*        */ tarsuper_endread(self)      (void)(shared_rwlock_endread(&(self)->ts_lock) && (tarsuper_reap(self), 0))
#define /*        */ _tarsuper_end(self)         shared_rwlock_end(&(self)->ts_lock)
#define /*        */ tarsuper_end(self)          (void)(shared_rwlock_end(&(self)->ts_lock) && (tarsuper_reap(self), 0))
#define /*BLOCKING*/ tarsuper_upgrade(self)      shared_rwlock_upgrade(&(self)->ts_lock)
#define /*        */ tarsuper_tryupgrade(self)   shared_rwlock_tryupgrade(&(self)->ts_lock)
#define /*        */ tarsuper_downgrade(self)    shared_rwlock_downgrade(&(self)->ts_lock)
#define /*        */ tarsuper_reading(self)      shared_rwlock_reading(&(self)->ts_lock)
#define /*        */ tarsuper_writing(self)      shared_rwlock_writing(&(self)->ts_lock)
#define /*        */ tarsuper_canread(self)      shared_rwlock_canread(&(self)->ts_lock)
#define /*        */ tarsuper_canwrite(self)     shared_rwlock_canwrite(&(self)->ts_lock)
#define /*BLOCKING*/ tarsuper_waitread(self)     shared_rwlock_waitread(&(self)->ts_lock)
#define /*BLOCKING*/ tarsuper_waitwrite(self)    shared_rwlock_waitwrite(&(self)->ts_lock)
#define /*BLOCKING*/ tarsuper_waitread_nx(self)  shared_rwlock_waitread_nx(&(self)->ts_lock)
#define /*BLOCKING*/ tarsuper_waitwrite_nx(self) shared_rwlock_waitwrite_nx(&(self)->ts_lock)


/* Operator tables. */
INTDEF struct fdirent_ops const tardirent_ops;   /* For `struct tardirent' */
INTDEF struct fdirnode_ops const tardirnode_ops; /* For `struct tardirnode' */
INTDEF struct fregnode_ops const tarregnode_ops; /* For `struct tarregnode' */
INTDEF struct flnknode_ops const tarlnknode_ops; /* For `struct tarlnknode' */
INTDEF struct fdevnode_ops const tardevnode_ops; /* For `struct tardevnode' */
INTDEF struct fsuper_ops const tarsuper_ops;     /* For `struct tarsuper' */


/* Read a new tarfile descriptor  at `self->ts_nfile', or endread  `self'.
 * The new file is automatically inserted into `self->ts_filev', for which
 * this function will temporarily upgrade  to a write-lock. When doing  so
 * would  block, the caller's read-lock is released, and a blocking write-
 * lock is acquired which is  then used to insert  the new file, prior  to
 * the  function returning `TARSUPER_READDIR_AGAIN'  (to indicate the loss
 * of the read-lock).
 *
 * Locking logic:
 * @return: * :                     No lock was ever released
 * @return: TARSUPER_READDIR_EOF:   Read-lock released
 * @return: TARSUPER_READDIR_AGAIN: Read-lock released */
INTDEF BLOCKING WUNUSED struct tarfile *FCALL
tarsuper_readdir_or_endread(struct tarsuper *__restrict self)
		THROWS(E_BADALLOC, E_WOULDBLOCK);

/* Special return values for `tarsuper_readdir_or_endread()' */
#define TARSUPER_READDIR_EOF   NULL                   /* All files read */
#define TARSUPER_READDIR_AGAIN ((struct tarfile *)-1) /* Lock released; try again */



DECL_END

#endif /* !GUARD_MODTAR_TAR_H */
