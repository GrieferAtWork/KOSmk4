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
#ifndef GUARD_MODPROCFS_PERPROC_C
#define GUARD_MODPROCFS_PERPROC_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <kernel/driver.h>
#include <sched/pid.h>

#include <kos/except/reason/io.h>
#include <sys/stat.h>

#include <assert.h>
#include <string.h>

#include "procfs.h"
#include "util.h"

DECL_BEGIN

#define DEFINE_DIRECTORY_ENTRY(symbol_name, ino, type, entry_name) \
	struct directory_entry symbol_name = {                         \
		/* .de_refcnt   = */ 1,                                    \
		/* .de_heapsize = */ sizeof(symbol_name),                  \
		/* .de_next     = */ NULL,                                 \
		/* .de_bypos    = */ LLIST_INITNODE,                       \
		/* .de_fsdata   = */ { 0, { 0 } },                         \
		/* .de_pos      = */ 0,                                    \
		/* .de_ino      = */ ino,                                  \
		/* .de_hash     = */ (uintptr_t)-1,                        \
		/* .de_namelen  = */ COMPILER_STRLEN(entry_name),          \
		/* .de_type     = */ type,                                 \
		/* .de_name     = */ entry_name,                           \
	}

/************************************************************************/
/* PerProc Runtime Data                                               */
/************************************************************************/
#define PERPROC_DIRECTORY_ENTRY(name, type, id)                                       \
	PRIVATE DEFINE_DIRECTORY_ENTRY(prd_perprocent_##id,                               \
	                               PROCFS_INOMAKE_PERPROC(0, PROCFS_PERPROC_ID_##id), \
	                               type, name);
#define MKDIR(id, mode, files) files
#define F(parent_id, name, type, id)                                                  \
	PRIVATE DEFINE_DIRECTORY_ENTRY(prd_dent_##parent_id##_ent_##id,                   \
	                               PROCFS_INOMAKE_PERPROC(0, PROCFS_PERPROC_ID_##id), \
	                               type, name);
#define F_END /* nothing */
#define MKREG_RW(id, mode, reader, writer)                               \
	PRIVATE struct procfs_perproc_reg_rw_data prd_fsdata_reg_rw_##id = { \
		/* .psr_printer = */ &reader,                                    \
		/* .psr_writer  = */ &writer,                                    \
	};
#include "perproc.def"
#undef F_END
#undef F

#define MKDIR(id, mode, files) \
	PRIVATE REF struct directory_entry *prd_fsdata_dir_##id[] = { files };
#define F(parent_id, name, type, id) &prd_dent_##parent_id##_ent_##id,
#define F_END NULL /* Sentinel */
#include "perproc.def"
#undef F_END
#undef F


INTERN_CONST void *const
ProcFS_PerProc_FsData[PROCFS_PERPROC_COUNT] = {
	[PROCFS_PERPROC_ROOT] = (void *)ProcFS_PerProcRootDirectory_FsData,
#define MKDIR(id, mode, files) \
	[PROCFS_PERPROC_ID_##id] = &prd_fsdata_dir_##id,
#include "perproc.def"
#define MKREG_RO(id, mode, printer) \
	[PROCFS_PERPROC_ID_##id] = (void *)&printer,
#include "perproc.def"
#define MKREG_RW(id, mode, reader, writer) \
	[PROCFS_PERPROC_ID_##id] = &prd_fsdata_reg_rw_##id,
#include "perproc.def"
#define DYNAMIC_SYMLINK(id, mode, readlink) \
	[PROCFS_PERPROC_ID_##id] = (void *)&readlink,
#include "perproc.def"
#ifndef PROCFS_PERPROC_NO_CUSTOM
#define CUSTOM(id, mode, type) \
	[PROCFS_PERPROC_ID_##id] = NULL,
#include "perproc.def"
#endif /* !PROCFS_PERPROC_NO_CUSTOM */
};

INTERN_CONST mode_t const
ProcFS_PerProc_FileMode[PROCFS_PERPROC_COUNT] = {
	[PROCFS_PERPROC_ROOT] = S_IFDIR | 0555,
#define MKDIR(id, mode, files) \
	[PROCFS_PERPROC_ID_##id] = S_IFDIR | mode,
#include "perproc.def"
#define MKREG_RO(id, mode, printer) \
	[PROCFS_PERPROC_ID_##id] = S_IFREG | mode,
#include "perproc.def"
#define MKREG_RW(id, mode, reader, writer) \
	[PROCFS_PERPROC_ID_##id] = S_IFREG | mode,
#include "perproc.def"
#define DYNAMIC_SYMLINK(id, mode, readlink) \
	[PROCFS_PERPROC_ID_##id] = S_IFLNK | mode,
#include "perproc.def"
#ifndef PROCFS_PERPROC_NO_CUSTOM
#define CUSTOM(id, mode, type) \
	[PROCFS_PERPROC_ID_##id] = mode,
#include "perproc.def"
#endif /* !PROCFS_PERPROC_NO_CUSTOM */
};


#ifndef PROCFS_PERPROC_NO_CUSTOM
INTERN_CONST struct inode_type *const
ProcFS_PerProc_CustomTypes[PROCFS_PERPROC_COUNT - PROCFS_PERPROC_START_CUSTOM] = {
#define CUSTOM(id, mode, type) \
	[PROCFS_PERPROC_ID_##id - PROCFS_PERPROC_START_CUSTOM] = &type,
#include "perproc.def"
};
#endif /* !PROCFS_PERPROC_NO_CUSTOM */

INTERN NONNULL((1)) void KCALL
ProcFS_PerProc_LoadAttr(struct inode *__restrict self)
		THROWS(E_IOERROR, ...) {
	/* XXX: Load attributes from dynamically allocated thread-local storage?
	 *      NOTE: PID can be accessed by `self->i_fileino & PROCFS_INOTYPE_PERPROC_PIDMASK' */
	(void)self;
}

INTERN NONNULL((1)) void KCALL
ProcFS_PerProc_SaveAttr(struct inode *__restrict self)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION,
		       E_FSERROR_READONLY, E_IOERROR, ...) {
	/* XXX: Save attributes in dynamically allocated thread-local storage?
	 *      NOTE: PID can be accessed by `self->i_fileino & PROCFS_INOTYPE_PERPROC_PIDMASK' */
	(void)self;
}


INTERN NONNULL((1, 2)) REF struct directory_entry *KCALL
ProcFS_PerProc_MakeDirent(struct directory_node *__restrict self,
                          struct directory_entry *__restrict ent) {
	REF struct directory_entry *result;
	/* XXX: Come up with a better solution that having to copy the directory_entry each time. */
	result = directory_entry_alloc(ent->de_namelen);
	result->de_ino  = ent->de_ino | (self->i_fileino & PROCFS_INOTYPE_PERPROC_PIDMASK);
	result->de_hash = ent->de_hash;
	result->de_type = ent->de_type;
	memcpy(result->de_name, ent->de_name, ent->de_namelen, sizeof(char));
	return result;
}

PRIVATE NONNULL((1, 2)) struct directory_entry *KCALL
ProcFS_PerProc_Directory_Locate(struct directory_node *__restrict self,
                                CHECKED USER /*utf-8*/ char const *__restrict name,
                                u16 namelen, uintptr_t hash, fsmode_t mode) {
	unsigned int i;
	struct directory_entry **data;
	struct directory_entry *dent;
	data = (directory_entry **)self->i_fsdata;
	for (i = 0; (dent = data[i]) != NULL; ++i) {
		if (dent->de_namelen != namelen)
			continue;
		if (dent->de_hash == (uintptr_t)-1)
			dent->de_hash = directory_entry_hash(dent->de_name, dent->de_namelen);
		if (dent->de_hash != hash)
			continue;
		if (memcmp(dent->de_name, name, namelen * sizeof(char)) != 0)
			continue;
		/* Found it! */
		return dent;
	}
	if (mode & FS_MODE_FDOSPATH) {
		/* Do a second pass where we ignore casing. */
		for (i = 0; (dent = data[i]) != NULL; ++i) {
			if (dent->de_namelen != namelen)
				continue;
			if (memcasecmp(dent->de_name, name, namelen * sizeof(char)) != 0)
				continue;
			/* Found it! */
			return dent;
		}
	}
	return NULL;
}

INTERN NONNULL((1, 2)) REF struct directory_entry *KCALL
ProcFS_PerProc_Directory_Lookup(struct directory_node *__restrict self,
                                CHECKED USER /*utf-8*/ char const *__restrict name,
                                u16 namelen, uintptr_t hash, fsmode_t mode)
		THROWS(E_SEGFAULT, E_FSERROR_FILE_NOT_FOUND,
		       E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	REF struct directory_entry *result;
	result = ProcFS_PerProc_Directory_Locate(self, name, namelen, hash, mode);
	if (result) /* Create the unique copy */
		result = ProcFS_PerProc_MakeDirent(self, result);
	return result;
}

INTERN NONNULL((1, 2)) void KCALL
ProcFS_PerProc_Directory_Enum(struct directory_node *__restrict self,
                              directory_enum_callback_t callback,
                              void *arg)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	unsigned int i;
	struct directory_entry **data;
	struct directory_entry *dent;
	data = (struct directory_entry **)self->i_fsdata;
	for (i = 0; (dent = data[i]) != NULL; ++i) {
		ino_t real_ino;
		real_ino = dent->de_ino;
		real_ino |= self->i_fileino & PROCFS_INOTYPE_PERPROC_PIDMASK;
		(*callback)(arg,
		            dent->de_name,
		            dent->de_namelen,
		            dent->de_type,
		            real_ino);
	}
}



PRIVATE NONNULL((1)) size_t KCALL
ProcFS_PerProc_FlexRead(struct inode *__restrict self,
                        USER CHECKED void *dst, size_t num_bytes,
                        pos_t file_position, PROCFS_REG_PRINTER printer)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	ProcFS_SubStringPrinterData closure;
#if __SIZEOF_OFF64_T__ > __SIZEOF_SIZE_T__
	if unlikely(file_position > (pos_t)(size_t)-1)
		return 0;
#endif /* __SIZEOF_OFF64_T__ > __SIZEOF_SIZE_T__ */
	closure.ssp_offset = (size_t)file_position;
	closure.ssp_buf    = (USER CHECKED char *)dst;
	closure.ssp_size   = num_bytes;
	/* Print the contents of the file using a sub-string printer. */
	(*printer)((struct regular_node *)self, &ProcFS_SubStringPrinter, &closure);
	return (size_t)((USER CHECKED byte_t *)closure.ssp_buf - (USER CHECKED byte_t *)dst);
}

PRIVATE NONNULL((1)) size_t KCALL
ProcFS_PerProc_RegularRo_FlexRead(struct inode *__restrict self,
                                  USER CHECKED void *dst, size_t num_bytes,
                                  pos_t file_position)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	PROCFS_REG_PRINTER printer;
	printer = (PROCFS_REG_PRINTER)self->i_fsdata;
	return ProcFS_PerProc_FlexRead(self, dst, num_bytes,
	                               file_position,
	                               printer);
}

PRIVATE NONNULL((1)) size_t KCALL
ProcFS_SingleTon_DynamicSymlink_Readlink(struct symlink_node *__restrict self,
                                         USER CHECKED /*utf-8*/ char *buf,
                                         size_t bufsize)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	PROCFS_SYMLINK_READLINK data;
	data = (PROCFS_SYMLINK_READLINK)self->i_fsdata;
	return (*data)(self, buf, bufsize);
}

PRIVATE NONNULL((1, 5)) void KCALL
ProcFS_PerProc_RegularRw_Write(struct inode *__restrict self,
                               USER CHECKED void const *src,
                               size_t num_bytes, pos_t file_position,
                               struct aio_multihandle *__restrict UNUSED(aio))
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY,
		       E_IOERROR_BADBOUNDS, E_IOERROR_READONLY,
		       E_IOERROR, ...) {
	struct procfs_perproc_reg_rw_data *data;
	data = (struct procfs_perproc_reg_rw_data *)self->i_fsdata;
	if (file_position != 0)
		THROW(E_IOERROR_BADBOUNDS, E_IOERROR_SUBSYSTEM_FILE);
	(*data->ppr_writer)((struct regular_node *)self, src, num_bytes);
}

PRIVATE NONNULL((1)) size_t KCALL
ProcFS_PerProc_RegularRw_FlexRead(struct inode *__restrict self,
                                  USER CHECKED void *dst, size_t num_bytes,
                                  pos_t file_position)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	struct procfs_perproc_reg_rw_data *data;
	data = (struct procfs_perproc_reg_rw_data *)self->i_fsdata;
	return ProcFS_PerProc_FlexRead(self, dst, num_bytes,
	                               file_position,
	                               data->ppr_printer);
}

INTDEF NONNULL((1)) void KCALL
ProcFS_Singleton_RegularRw_Truncate(struct inode *__restrict self, pos_t new_size)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY,
		       E_IOERROR_BADBOUNDS, E_IOERROR_READONLY, E_IOERROR, ...);
#define ProcFS_PerProc_RegularRw_Truncate \
	ProcFS_Singleton_RegularRw_Truncate




/* Type for general-purpose perproc directories */
INTERN struct inode_type ProcFS_PerProc_Directory_Type = {
	/* .it_fini = */ NULL,
	/* .it_attr = */ {
		/* .a_loadattr = */ &ProcFS_PerProc_LoadAttr,
		/* .a_saveattr = */ &ProcFS_PerProc_SaveAttr,
		/* .a_maskattr = */ NULL,
		/* .a_stat     = */ &ProcFS_PerProc_StatInode,
	},
	/* .it_file = */ { },
	{
		/* .it_directory = */ {
			/* .d_readdir = */ NULL,
			/* .d_oneshot = */ {
				/* .o_lookup = */ &ProcFS_PerProc_Directory_Lookup,
				/* .o_enum   = */ &ProcFS_PerProc_Directory_Enum,
			}
		}
	}
};

/* Type for general-purpose perproc read-only files */
INTERN struct inode_type ProcFS_PerProc_RegularRo_Type = {
	/* .it_fini = */ NULL,
	/* .it_attr = */ {
		/* .a_loadattr = */ &ProcFS_PerProc_LoadAttr,
		/* .a_saveattr = */ &ProcFS_PerProc_SaveAttr,
		/* .a_maskattr = */ NULL,
		/* .a_stat     = */ &ProcFS_PerProc_StatInode,
	},
	/* .it_file = */ {
		/* .f_read     = */ NULL,
		/* .f_pread    = */ NULL,
		/* .f_readv    = */ NULL,
		/* .f_preadv   = */ NULL,
		/* .f_write    = */ NULL,
		/* .f_pwrite   = */ NULL,
		/* .f_writev   = */ NULL,
		/* .f_pwritev  = */ NULL,
		/* .f_truncate = */ NULL,
		/* .f_flexread = */ &ProcFS_PerProc_RegularRo_FlexRead,
	},
};

/* Type for general-purpose perproc read/write files */
INTERN struct inode_type ProcFS_PerProc_RegularRw_Type = {
	/* .it_fini = */ NULL,
	/* .it_attr = */ {
		/* .a_loadattr = */ &ProcFS_PerProc_LoadAttr,
		/* .a_saveattr = */ &ProcFS_PerProc_SaveAttr,
		/* .a_maskattr = */ NULL,
		/* .a_stat     = */ &ProcFS_PerProc_StatInode,
	},
	/* .it_file = */ {
		/* .f_read     = */ NULL,
		/* .f_pread    = */ NULL,
		/* .f_readv    = */ NULL,
		/* .f_preadv   = */ NULL,
		/* .f_write    = */ &ProcFS_PerProc_RegularRw_Write,
		/* .f_pwrite   = */ &inode_file_pwrite_with_write,
		/* .f_writev   = */ &inode_file_writev_with_write,
		/* .f_pwritev  = */ &inode_file_pwritev_with_pwrite,
		/* .f_truncate = */ &ProcFS_PerProc_RegularRw_Truncate,
		/* .f_flexread = */ &ProcFS_PerProc_RegularRw_FlexRead,
	},
};


/* Type for general-purpose perproc dynamic symlink files */
INTERN struct inode_type ProcFS_PerProc_DynamicSymlink_Type = {
	/* .it_fini = */ NULL,
	/* .it_attr = */ {
		/* .a_loadattr = */ &ProcFS_PerProc_LoadAttr,
		/* .a_saveattr = */ &ProcFS_PerProc_SaveAttr,
		/* .a_maskattr = */ NULL,
		/* .a_stat     = */ &ProcFS_PerProc_StatInode,
	},
	/* .it_file = */ {
	},
	{
		.it_symlink = {
			/* .sl_readlink = */ NULL,
			/* .sl_readlink = */ &ProcFS_SingleTon_DynamicSymlink_Readlink,
		}
	}
};




/************************************************************************/
/* ROOT DIRECTORY                                                       */
/************************************************************************/
INTERN REF struct directory_entry *ProcFS_PerProcRootDirectory_FsData[] = {
#define PERPROC_DIRECTORY_ENTRY(name, type, id) &prd_perprocent_##id,
#include "perproc.def"
	NULL
};

PRIVATE WUNUSED bool KCALL
is_process_leader_pid(upid_t pid) {
	bool result;
	REF struct task *thread;
	/* Lookup the associated thread. */
	thread = pidns_trylookup_task(THIS_PIDNS, pid);
	if unlikely(!thread)
		return false;
	result = task_isprocessleader_p(thread);
	decref_unlikely(thread);
	return result;
}

PRIVATE NONNULL((1, 2)) struct directory_entry *KCALL
ProcFS_PerProc_RootDirectory_TranslateSpecialEntry(struct directory_node *__restrict self,
                                                   struct directory_entry *__restrict ent) {
	/* Check for special case: Only a process leader has the `task' sub-directory! */
	if (ent->de_ino == PROCFS_INOMAKE_PERPROC(0, PROCFS_PERPROC_ID_task)) {
		if (!is_process_leader_pid((upid_t)(self->i_fileino & PROCFS_INOTYPE_PERPROC_PIDMASK)))
			return NULL;
	}
	return ent;
}

PRIVATE NONNULL((1, 2)) REF struct directory_entry *KCALL
ProcFS_PerProc_RootDirectory_Lookup(struct directory_node *__restrict self,
                                    CHECKED USER /*utf-8*/ char const *__restrict name,
                                    u16 namelen, uintptr_t hash, fsmode_t mode)
		THROWS(E_SEGFAULT, E_FSERROR_FILE_NOT_FOUND,
		       E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	REF struct directory_entry *result;
	result = ProcFS_PerProc_Directory_Locate(self, name, namelen, hash, mode);
	if (result) {
		/* Deal with special entires. */
		result = ProcFS_PerProc_RootDirectory_TranslateSpecialEntry(self, result);
		if (result) {
			/* Create the unique copy */
			result = ProcFS_PerProc_MakeDirent(self, result);
		}
	}
	return result;
}

PRIVATE NONNULL((1, 2)) void KCALL
ProcFS_PerProc_RootDirectory_Enum(struct directory_node *__restrict self,
                                  directory_enum_callback_t callback,
                                  void *arg)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	unsigned int i;
	struct directory_entry **data;
	struct directory_entry *dent;
	data = (struct directory_entry **)self->i_fsdata;
	for (i = 0; (dent = data[i]) != NULL; ++i) {
		/* Deal with special entires. */
		dent = ProcFS_PerProc_RootDirectory_TranslateSpecialEntry(self, dent);
		if (dent) {
			ino_t real_ino;
			real_ino = dent->de_ino;
			real_ino |= self->i_fileino & PROCFS_INOTYPE_PERPROC_PIDMASK;
			(*callback)(arg,
			            dent->de_name,
			            dent->de_namelen,
			            dent->de_type,
			            real_ino);
		}
	}
}


INTERN struct inode_type ProcFS_PerProcRootDirectory_Type = {
	/* .it_fini = */ NULL,
	/* .it_attr = */ {
		/* .a_loadattr = */ &ProcFS_PerProc_LoadAttr,
		/* .a_saveattr = */ &ProcFS_PerProc_SaveAttr,
		/* .a_maskattr = */ NULL,
		/* .a_stat     = */ &ProcFS_PerProc_StatInode,
	},
	/* .it_file = */ {
	},
	{
		/* .it_directory = */ {
			/* .d_readdir = */ NULL,
			/* .d_oneshot = */ {
				/* .o_lookup = */ &ProcFS_PerProc_RootDirectory_Lookup,
				/* .o_enum   = */ &ProcFS_PerProc_RootDirectory_Enum,
			}
		}
	}
};



/************************************************************************/
/* Per-process stat() operator for procfs INode objects.                */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
ProcFS_PerProc_StatInode(struct inode *__restrict self,
                         USER CHECKED struct stat *result)
		THROWS(E_WOULDBLOCK, E_SEGFAULT) {
	REF struct task *thread;
	upid_t pid;
	pid = (upid_t)(self->i_fileino & PROCFS_INOTYPE_PERPROC_PIDMASK);
	/* Lookup the associated thread. */
	thread = pidns_trylookup_task(THIS_PIDNS, pid);
	if unlikely(!thread)
		return;
	FINALLY_DECREF_UNLIKELY(thread);
	/* Use the thread's creation timestamp for a/m/c-timestamps. */
	result->st_atimespec.tv_sec  = thread->t_ctime.tv_sec;
	result->st_atimespec.tv_nsec = thread->t_ctime.tv_nsec;
	result->st_mtimespec.tv_sec  = thread->t_ctime.tv_sec;
	result->st_mtimespec.tv_nsec = thread->t_ctime.tv_nsec;
	result->st_ctimespec.tv_sec  = thread->t_ctime.tv_sec;
	result->st_ctimespec.tv_nsec = thread->t_ctime.tv_nsec;
}


DECL_END

#endif /* !GUARD_MODPROCFS_PERPROC_C */
