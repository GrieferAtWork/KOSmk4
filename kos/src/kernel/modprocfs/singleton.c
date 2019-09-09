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
#ifndef GUARD_MODPROCFS_SINGLETON_C
#define GUARD_MODPROCFS_SINGLETON_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>
#include <kernel/driver.h>
#include <fs/node.h>
#include <sys/stat.h>
#include <assert.h>
#include <string.h>

#include "procfs.h"

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
/* Singleton Runtime Data                                               */
/************************************************************************/
#define ROOT_DIRECTORY_ENTRY(name, type, id)                                           \
	PRIVATE DEFINE_DIRECTORY_ENTRY(srd_rootent_##id,                                   \
	                               PROCFS_INOMAKE_SINGLETON(PROCFS_SINGLETON_ID_##id), \
	                               type, name);
#define MKDIR(id, mode, files) files
#define F(parent_id, name, type, id)                                                   \
	PRIVATE DEFINE_DIRECTORY_ENTRY(srd_dent_##parent_id##_ent_##id,                    \
	                               PROCFS_INOMAKE_SINGLETON(PROCFS_SINGLETON_ID_##id), \
	                               type, name);
#define END /* nothing */
#include "singleton.h"
#undef END
#undef F

#define MKDIR(id, mode, files)                                         \
	PRIVATE struct procfs_singleton_dir_data srd_fsdata_dir_##id = { \
		/* .psd_atime = */ { 0, 0 },                                 \
		/* .psd_mtime = */ { 0, 0 },                                 \
		/* .psd_ctime = */ { 0, 0 },                                 \
		/* .psd_mode  = */ S_IFDIR | (mode),                         \
		/* .psd_uid   = */ 0,                                        \
		/* .psd_gid   = */ 0,                                        \
		/* .pdd_ents  = */ { files },                                \
	};
#define F(parent_id, name, type, id) &srd_dent_##parent_id##_ent_##id,
#define END NULL /* Sentinel */
#define MKREG_RO(id, mode, printer)                                        \
	PRIVATE struct procfs_singleton_reg_ro_data srd_fsdata_reg_ro_##id = { \
		/* .psd_atime   = */ { 0, 0 },                                     \
		/* .psd_mtime   = */ { 0, 0 },                                     \
		/* .psd_ctime   = */ { 0, 0 },                                     \
		/* .psd_mode    = */ S_IFREG | (mode),                             \
		/* .psd_uid     = */ 0,                                            \
		/* .psd_gid     = */ 0,                                            \
		/* .psr_printer = */ &printer,                                     \
	};
#include "singleton.h"
#undef END
#undef F


INTERN_CONST struct procfs_singleton_data *const ProcFS_Singleton_FsData[PROCFS_SINGLETON_COUNT] = {
	[PROCFS_SINGLETON_ROOT] = (struct procfs_singleton_data *)&ProcFS_RootDirectory_FsData,
#define MKDIR(id, mode, files) \
	[PROCFS_SINGLETON_ID_##id] = (struct procfs_singleton_data *)&srd_fsdata_dir_##id,
#include "singleton.h"
#define MKREG_RO(id, mode, printer) \
	[PROCFS_SINGLETON_ID_##id] = (struct procfs_singleton_data *)&srd_fsdata_reg_ro_##id,
#include "singleton.h"
};



PRIVATE NONNULL((1)) void KCALL
ProcFS_Singleton_LoadAttr(struct inode *__restrict self) {
	struct procfs_singleton_data *data;
	data = (struct procfs_singleton_data *)self->i_fsdata;
	self->i_fileatime = data->psd_atime;
	self->i_filemtime = data->psd_mtime;
	self->i_filectime = data->psd_ctime;
	assertf(IFTODT(self->i_filemode) == IFTODT(data->psd_mode),
	        "Miss-matched file modes: %u != %u",
	        IFTODT(self->i_filemode), IFTODT(data->psd_mode));
	self->i_filemode  = data->psd_mode;
	self->i_fileuid   = data->psd_uid;
	self->i_filegid   = data->psd_gid;
	self->i_filenlink = (nlink_t)1;
	self->i_filesize  = (pos_t)4096;
}

PRIVATE NONNULL((1)) void KCALL
ProcFS_Singleton_SaveAttr(struct inode *__restrict self) {
	struct procfs_singleton_data *data;
	data = (struct procfs_singleton_data *)self->i_fsdata;
	data->psd_atime = self->i_fileatime;
	data->psd_mtime = self->i_filemtime;
	data->psd_ctime = self->i_filectime;
	assertf(IFTODT(self->i_filemode) == IFTODT(data->psd_mode),
	        "Miss-matched file modes: %u != %u",
	        IFTODT(self->i_filemode), IFTODT(data->psd_mode));
	data->psd_mode = self->i_filemode;
	data->psd_uid  = self->i_fileuid;
	data->psd_gid  = self->i_filegid;
}

PRIVATE NONNULL((1, 2)) REF struct directory_entry *KCALL
ProcFS_Singleton_Directory_Lookup(struct directory_node *__restrict self,
                                  CHECKED USER /*utf-8*/ char const *__restrict name,
                                  u16 namelen, uintptr_t hash, fsmode_t mode)
		THROWS(E_SEGFAULT, E_FSERROR_FILE_NOT_FOUND,
		       E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	unsigned int i;
	struct procfs_singleton_dir_data *data;
	struct directory_entry *dent;
	data = (struct procfs_singleton_dir_data *)self->i_fsdata;
	for (i = 0; (dent = data->pdd_ents[i]) != NULL; ++i) {
		if (dent->de_namelen != namelen)
			continue;
		if (dent->de_hash == (uintptr_t)-1)
			dent->de_hash = directory_entry_hash(dent->de_name, dent->de_namelen);
		if (dent->de_hash != hash)
			continue;
		if (memcmp(dent->de_name, name, namelen * sizeof(char)) != 0)
			continue;
		/* Found it! */
		return incref(dent);
	}
	if (mode & FS_MODE_FDOSPATH) {
		/* Do a second pass where we ignore casing. */
		for (i = 0; (dent = data->pdd_ents[i]) != NULL; ++i) {
			if (dent->de_namelen != namelen)
				continue;
			if (memcasecmp(dent->de_name, name, namelen * sizeof(char)) != 0)
				continue;
			/* Found it! */
			return incref(dent);
		}
	}
	return NULL;
}

PRIVATE NONNULL((1, 2)) void KCALL
ProcFS_Singleton_Directory_Enum(struct directory_node *__restrict self,
                                directory_enum_callback_t callback,
                                void *arg)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	unsigned int i;
	struct procfs_singleton_dir_data *data;
	struct directory_entry *dent;
	data = (struct procfs_singleton_dir_data *)self->i_fsdata;
	for (i = 0; (dent = data->pdd_ents[i]) != NULL; ++i) {
		(*callback)(arg,
		            dent->de_name,
		            dent->de_namelen,
		            dent->de_type,
		            dent->de_ino);
	}
}



typedef struct {
	size_t             ssp_offset; /* Remaining number of bytes to skip */
	size_t             ssp_size;   /* Remaining number of bytes to print */
	USER CHECKED char *ssp_buf;    /* Destination buffer. */
} ProcFS_SubStringPrinterData;

PRIVATE ssize_t
NOTHROW(KCALL ProcFS_SubStringPrinter)(void *arg, char const *__restrict data, size_t datalen) {
	ProcFS_SubStringPrinterData *closure;
	ssize_t result = (ssize_t)datalen;
	closure = (ProcFS_SubStringPrinterData *)arg;
	if (closure->ssp_offset != 0) {
		if (closure->ssp_offset >= datalen) {
			closure->ssp_offset -= datalen;
			goto done;
		}
		data    += closure->ssp_offset;
		datalen -= closure->ssp_offset;
		closure->ssp_offset = 0;
	}
	if (datalen >= closure->ssp_size) {
		memcpy(closure->ssp_buf, data, closure->ssp_size);
		closure->ssp_buf += closure->ssp_size;
		closure->ssp_size = 0;
		return __SSIZE_MIN__; /* Stop printing (we've gotten everything) */
	}
	/* Print everything */
	memcpy(closure->ssp_buf, data, datalen);
	closure->ssp_size -= datalen;
	closure->ssp_buf  += datalen;
done:
	return result;
}


PRIVATE NONNULL((1)) size_t KCALL
ProcFS_Singleton_RegularRo_FlexRead(struct inode *__restrict self,
                                    USER CHECKED void *dst, size_t num_bytes,
                                    pos_t file_position)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	struct procfs_singleton_reg_ro_data *data;
	ProcFS_SubStringPrinterData closure;
#if __SIZEOF_OFF64_T__ > __SIZEOF_SIZE_T__
	if unlikely(file_position > (pos_t)(size_t)-1)
		return 0;
#endif /* __SIZEOF_OFF64_T__ > __SIZEOF_SIZE_T__ */
	data = (struct procfs_singleton_reg_ro_data *)self->i_fsdata;
	closure.ssp_offset = (size_t)file_position;
	closure.ssp_buf    = (USER CHECKED char *)dst;
	closure.ssp_size   = num_bytes;
	/* Print the contents of the file using a sub-string printer. */
	(*data->psr_printer)(self, &ProcFS_SubStringPrinter, &closure);
	return (size_t)((USER CHECKED byte_t *)closure.ssp_buf - (USER CHECKED byte_t *)dst);
}




/* Type for general-purpose singleton directories */
INTERN struct inode_type ProcFS_Singleton_Directory_Type = {
	/* .it_fini = */ NULL,
	/* .it_attr = */ {
		/* .a_loadattr = */ &ProcFS_Singleton_LoadAttr,
		/* .a_saveattr = */ &ProcFS_Singleton_SaveAttr,
	},
	/* .it_file = */ { },
	{
		/* .it_directory = */ {
			/* .d_readdir = */ NULL,
			/* .d_oneshot = */ {
				/* .o_lookup = */ &ProcFS_Singleton_Directory_Lookup,
				/* .o_enum   = */ &ProcFS_Singleton_Directory_Enum,
			}
		}
	}
};

/* Type for general-purpose singleton read-only files */
INTERN struct inode_type ProcFS_Singleton_RegularRo_Type = {
	/* .it_fini = */ NULL,
	/* .it_attr = */ {
		/* .a_loadattr = */ &ProcFS_Singleton_LoadAttr,
		/* .a_saveattr = */ &ProcFS_Singleton_SaveAttr,
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
		/* .f_flexread = */ &ProcFS_Singleton_RegularRo_FlexRead,
	},
};




/************************************************************************/
/* ROOT DIRECTORY                                                       */
/************************************************************************/

PRIVATE NONNULL((1, 2)) REF struct directory_entry *KCALL
ProcFS_RootDirectory_Lookup(struct directory_node *__restrict self,
                            CHECKED USER /*utf-8*/ char const *__restrict name,
                            u16 namelen, uintptr_t hash, fsmode_t mode)
		THROWS(E_SEGFAULT, E_FSERROR_FILE_NOT_FOUND,
		       E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	assert(self->i_fsdata == (struct inode_data *)&ProcFS_RootDirectory_FsData);
	/* TODO: Evaluate running process PIDs */
	return ProcFS_Singleton_Directory_Lookup(self, name, namelen, hash, mode);
}

PRIVATE NONNULL((1, 2)) void KCALL
ProcFS_RootDirectory_Enum(struct directory_node *__restrict self,
                          directory_enum_callback_t callback,
                          void *arg)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	assert(self->i_fsdata == (struct inode_data *)&ProcFS_RootDirectory_FsData);
	/* TODO: Enumerate running process PIDs */
	ProcFS_Singleton_Directory_Enum(self, callback, arg);
}



INTERN struct procfs_singleton_dir_data ProcFS_RootDirectory_FsData = {
	/* .psd_atime = */ { 0, 0 },
	/* .psd_mtime = */ { 0, 0 },
	/* .psd_ctime = */ { 0, 0 },
	/* .psd_mode  = */ S_IFDIR | 0555,
	/* .psd_uid   = */ 0,
	/* .psd_gid   = */ 0,
	/* .pdd_ents  = */ {
#define ROOT_DIRECTORY_ENTRY(name, type, id) &srd_rootent_##id,
#include "singleton.h"
		NULL
	},
};

INTERN struct inode_type ProcFS_RootDirectory_Type = {
	/* .it_fini = */ NULL,
	/* .it_attr = */ {
		/* .a_loadattr = */ &ProcFS_Singleton_LoadAttr,
		/* .a_saveattr = */ &ProcFS_Singleton_SaveAttr,
	},
	/* .it_file = */ {
	},
	{
		/* .it_directory = */ {
			/* .d_readdir = */ NULL,
			/* .d_oneshot = */ {
				/* .o_lookup = */ &ProcFS_RootDirectory_Lookup,
				/* .o_enum   = */ &ProcFS_RootDirectory_Enum,
			}
		}
	}
};



DECL_END

#endif /* !GUARD_MODPROCFS_SINGLETON_C */
