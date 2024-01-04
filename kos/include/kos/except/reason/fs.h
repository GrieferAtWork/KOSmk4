/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_EXCEPT_REASON_FS_H
#define _KOS_EXCEPT_REASON_FS_H 1

#include <__stdinc.h>

__DECL_BEGIN


/* `reason' codes for `E_FSERROR_DELETED' */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	E_FILESYSTEM_DELETED_GENERIC,   /* Generic reason for `E_FSERROR_DELETED' */
	E_FILESYSTEM_DELETED_FILE,      /* The file being accessed was deleted. (set if the problem was caused by the last component of a path) */
	E_FILESYSTEM_DELETED_PATH,      /* The path being accessed was deleted. (set if the problem was caused by some other than the last component of the path) */
	E_FILESYSTEM_DELETED_UNMOUNTED  /* The hosting file system has been unmounted */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define E_FILESYSTEM_DELETED_GENERIC   E_FILESYSTEM_DELETED_GENERIC   /* Generic reason for `E_FSERROR_DELETED' */
#define E_FILESYSTEM_DELETED_FILE      E_FILESYSTEM_DELETED_FILE      /* The file being accessed was deleted. (set if the problem was caused by the last component of a path) */
#define E_FILESYSTEM_DELETED_PATH      E_FILESYSTEM_DELETED_PATH      /* The path being accessed was deleted. (set if the problem was caused by some other than the last component of the path) */
#define E_FILESYSTEM_DELETED_UNMOUNTED E_FILESYSTEM_DELETED_UNMOUNTED /* The hosting file system has been unmounted */
#else /* __COMPILER_PREFERR_ENUMS */
#define E_FILESYSTEM_DELETED_GENERIC   0 /* Generic reason for `E_FSERROR_DELETED' */
#define E_FILESYSTEM_DELETED_FILE      1 /* The file being accessed was deleted. (set if the problem was caused by the last component of a path) */
#define E_FILESYSTEM_DELETED_PATH      2 /* The path being accessed was deleted. (set if the problem was caused by some other than the last component of the path) */
#define E_FILESYSTEM_DELETED_UNMOUNTED 3 /* The hosting file system has been unmounted */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


/* `reason' codes for `E_FSERROR_PATH_NOT_FOUND' */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	E_FILESYSTEM_PATH_NOT_FOUND_GENERIC, /* Generic reason for `E_FSERROR_PATH_NOT_FOUND' */
	E_FILESYSTEM_PATH_NOT_FOUND_DIR,     /* Directory does not exist */
	E_FILESYSTEM_PATH_NOT_FOUND_DRIVE    /* Drive does not exist */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define E_FILESYSTEM_PATH_NOT_FOUND_GENERIC E_FILESYSTEM_PATH_NOT_FOUND_GENERIC /* Generic reason for `E_FSERROR_PATH_NOT_FOUND' */
#define E_FILESYSTEM_PATH_NOT_FOUND_DIR     E_FILESYSTEM_PATH_NOT_FOUND_DIR     /* Directory does not exist */
#define E_FILESYSTEM_PATH_NOT_FOUND_DRIVE   E_FILESYSTEM_PATH_NOT_FOUND_DRIVE   /* Drive does not exist */
#else /* __COMPILER_PREFERR_ENUMS */
#define E_FILESYSTEM_PATH_NOT_FOUND_GENERIC 0 /* Generic reason for `E_FSERROR_PATH_NOT_FOUND' */
#define E_FILESYSTEM_PATH_NOT_FOUND_DIR     1 /* Directory does not exist */
#define E_FILESYSTEM_PATH_NOT_FOUND_DRIVE   2 /* Drive does not exist */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


/* `action_context' codes for `E_FSERROR_NOT_A_DIRECTORY' */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	E_FILESYSTEM_IS_A_DIRECTORY_GENERIC, /* Generic reason for `E_FSERROR_IS_A_DIRECTORY' */
	E_FILESYSTEM_IS_A_DIRECTORY_UNLINK,  /* Thrown as the result of `unlink(path)', where `path' is a directory */
	E_FILESYSTEM_IS_A_DIRECTORY_EXEC,    /* Thrown as the result of `exec(path)', where `path' is a directory */
	E_FILESYSTEM_IS_A_DIRECTORY_READ,    /* Thrown as the result of attempting to read from a directory */
	E_FILESYSTEM_IS_A_DIRECTORY_RENAME,  /* `rename(2)' tried to override a non-directory with a directory */
	E_FILESYSTEM_IS_A_DIRECTORY_LINK,    /* Tried to create a hard-link (`link(2)') for a directory. */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define E_FILESYSTEM_IS_A_DIRECTORY_GENERIC E_FILESYSTEM_IS_A_DIRECTORY_GENERIC /* Generic reason for `E_FSERROR_IS_A_DIRECTORY' */
#define E_FILESYSTEM_IS_A_DIRECTORY_UNLINK  E_FILESYSTEM_IS_A_DIRECTORY_UNLINK  /* Thrown as the result of `unlink(path)', where `path' is a directory */
#define E_FILESYSTEM_IS_A_DIRECTORY_EXEC    E_FILESYSTEM_IS_A_DIRECTORY_EXEC    /* Thrown as the result of `exec(path)', where `path' is a directory */
#define E_FILESYSTEM_IS_A_DIRECTORY_READ    E_FILESYSTEM_IS_A_DIRECTORY_READ    /* Thrown as the result of attempting to read from a directory */
#define E_FILESYSTEM_IS_A_DIRECTORY_RENAME  E_FILESYSTEM_IS_A_DIRECTORY_RENAME  /* `rename(2)' tried to override a non-directory with a directory */
#define E_FILESYSTEM_IS_A_DIRECTORY_LINK    E_FILESYSTEM_IS_A_DIRECTORY_LINK    /* Tried to create a hard-link (`link(2)') for a directory. */
#else /* __COMPILER_PREFERR_ENUMS */
#define E_FILESYSTEM_IS_A_DIRECTORY_GENERIC 0 /* Generic reason for `E_FSERROR_IS_A_DIRECTORY' */
#define E_FILESYSTEM_IS_A_DIRECTORY_UNLINK  1 /* Thrown as the result of `unlink(path)', where `path' is a directory */
#define E_FILESYSTEM_IS_A_DIRECTORY_EXEC    2 /* Thrown as the result of `exec(path)', where `path' is a directory */
#define E_FILESYSTEM_IS_A_DIRECTORY_READ    3 /* Thrown as the result of attempting to read from a directory */
#define E_FILESYSTEM_IS_A_DIRECTORY_RENAME  4 /* `rename(2)' tried to override a non-directory with a directory */
#define E_FILESYSTEM_IS_A_DIRECTORY_LINK    5 /* Tried to create a hard-link (`link(2)') for a directory. */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


/* `operation_id' codes for `E_FSERROR_UNSUPPORTED_OPERATION' */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	E_FILESYSTEM_OPERATION_GENERIC,  /* Generic file-system operation */
	E_FILESYSTEM_OPERATION_READ,     /* The object does not support read(2) */
	E_FILESYSTEM_OPERATION_PREAD,    /* The object does not support pread(2) */
	E_FILESYSTEM_OPERATION_WRITE,    /* The object does not support write(2) */
	E_FILESYSTEM_OPERATION_PWRITE,   /* The object does not support pwrite(2) */
	E_FILESYSTEM_OPERATION_TRUNC,    /* The object does not support being resized */
	E_FILESYSTEM_OPERATION_READDIR,  /* The object does not support being read from as a directory */
	E_FILESYSTEM_OPERATION_CREAT,    /* The object does not support creation of new files */
	E_FILESYSTEM_OPERATION_MKDIR,    /* The object does not support creation of new directories */
	E_FILESYSTEM_OPERATION_SYMLINK,  /* The object does not support creation of symbolic links */
	E_FILESYSTEM_OPERATION_MKNOD,    /* The object does not support creation of device nodes */
	E_FILESYSTEM_OPERATION_LINK,     /* The object does not support creation of hard links */
	E_FILESYSTEM_OPERATION_RENAME,   /* The object does not support renaming of items */
	E_FILESYSTEM_OPERATION_UNLINK,   /* The object does not support unlinking files */
	E_FILESYSTEM_OPERATION_RMDIR,    /* The object does not support removal of directories */
	E_FILESYSTEM_OPERATION_ATTRIB,   /* The values specified by chmod() or chown() cannot be applied within the file system */
	E_FILESYSTEM_OPERATION_WRATTR,   /* The object does not support changes to attributes being written to disk */
	E_FILESYSTEM_OPERATION_SEEK,     /* The object does not support seeking in file stream */
	E_FILESYSTEM_OPERATION_MMAP,     /* The object does not support mapping data into memory */
	E_FILESYSTEM_OPERATION_SYNC,     /* The object does not support the fsync() operator */
	E_FILESYSTEM_OPERATION_DATASYNC, /* The object does not support the fdatasync() operator */
	E_FILESYSTEM_OPERATION_STAT,     /* The object does not support the fstat() operator */
	E_FILESYSTEM_OPERATION_ALLOCATE, /* The object does not support the fallocate() operator */
	E_FILESYSTEM_OPERATION_FLOCK     /* The object does not support the flock() operator */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define E_FILESYSTEM_OPERATION_GENERIC  E_FILESYSTEM_OPERATION_GENERIC  /* Generic file-system operation */
#define E_FILESYSTEM_OPERATION_READ     E_FILESYSTEM_OPERATION_READ     /* The object does not support read(2) */
#define E_FILESYSTEM_OPERATION_PREAD    E_FILESYSTEM_OPERATION_PREAD    /* The object does not support pread(2) */
#define E_FILESYSTEM_OPERATION_WRITE    E_FILESYSTEM_OPERATION_WRITE    /* The object does not support write(2) */
#define E_FILESYSTEM_OPERATION_PWRITE   E_FILESYSTEM_OPERATION_PWRITE   /* The object does not support pwrite(2) */
#define E_FILESYSTEM_OPERATION_TRUNC    E_FILESYSTEM_OPERATION_TRUNC    /* The object does not support being resized */
#define E_FILESYSTEM_OPERATION_READDIR  E_FILESYSTEM_OPERATION_READDIR  /* The object does not support being read from as a directory */
#define E_FILESYSTEM_OPERATION_CREAT    E_FILESYSTEM_OPERATION_CREAT    /* The object does not support creation of new files */
#define E_FILESYSTEM_OPERATION_MKDIR    E_FILESYSTEM_OPERATION_MKDIR    /* The object does not support creation of new directories */
#define E_FILESYSTEM_OPERATION_SYMLINK  E_FILESYSTEM_OPERATION_SYMLINK  /* The object does not support creation of symbolic links */
#define E_FILESYSTEM_OPERATION_MKNOD    E_FILESYSTEM_OPERATION_MKNOD    /* The object does not support creation of device nodes */
#define E_FILESYSTEM_OPERATION_LINK     E_FILESYSTEM_OPERATION_LINK     /* The object does not support creation of hard links */
#define E_FILESYSTEM_OPERATION_RENAME   E_FILESYSTEM_OPERATION_RENAME   /* The object does not support renaming of items */
#define E_FILESYSTEM_OPERATION_UNLINK   E_FILESYSTEM_OPERATION_UNLINK   /* The object does not support unlinking files */
#define E_FILESYSTEM_OPERATION_RMDIR    E_FILESYSTEM_OPERATION_RMDIR    /* The object does not support removal of directories */
#define E_FILESYSTEM_OPERATION_ATTRIB   E_FILESYSTEM_OPERATION_ATTRIB   /* The values specified by chmod() or chown() cannot be applied within the file system */
#define E_FILESYSTEM_OPERATION_WRATTR   E_FILESYSTEM_OPERATION_WRATTR   /* The object does not support changes to attributes being written to disk */
#define E_FILESYSTEM_OPERATION_SEEK     E_FILESYSTEM_OPERATION_SEEK     /* The object does not support seeking in file stream */
#define E_FILESYSTEM_OPERATION_MMAP     E_FILESYSTEM_OPERATION_MMAP     /* The object does not support mapping data into memory */
#define E_FILESYSTEM_OPERATION_SYNC     E_FILESYSTEM_OPERATION_SYNC     /* The object does not support the fsync() operator */
#define E_FILESYSTEM_OPERATION_DATASYNC E_FILESYSTEM_OPERATION_DATASYNC /* The object does not support the fdatasync() operator */
#define E_FILESYSTEM_OPERATION_STAT     E_FILESYSTEM_OPERATION_STAT     /* The object does not support the fstat() operator */
#define E_FILESYSTEM_OPERATION_ALLOCATE E_FILESYSTEM_OPERATION_ALLOCATE /* The object does not support the fallocate() operator */
#define E_FILESYSTEM_OPERATION_FLOCK    E_FILESYSTEM_OPERATION_FLOCK    /* The object does not support the flock() operator */
#else /* __COMPILER_PREFERR_ENUMS */
#define E_FILESYSTEM_OPERATION_GENERIC  0  /* Generic file-system operation */
#define E_FILESYSTEM_OPERATION_READ     1  /* The object does not support read(2) */
#define E_FILESYSTEM_OPERATION_PREAD    2  /* The object does not support pread(2) */
#define E_FILESYSTEM_OPERATION_WRITE    3  /* The object does not support write(2) */
#define E_FILESYSTEM_OPERATION_PWRITE   4  /* The object does not support pwrite(2) */
#define E_FILESYSTEM_OPERATION_TRUNC    5  /* The object does not support being resized */
#define E_FILESYSTEM_OPERATION_READDIR  6  /* The object does not support being read from as a directory */
#define E_FILESYSTEM_OPERATION_CREAT    7  /* The object does not support creation of new files */
#define E_FILESYSTEM_OPERATION_MKDIR    8  /* The object does not support creation of new directories */
#define E_FILESYSTEM_OPERATION_SYMLINK  9  /* The object does not support creation of symbolic links */
#define E_FILESYSTEM_OPERATION_MKNOD    10 /* The object does not support creation of device nodes */
#define E_FILESYSTEM_OPERATION_LINK     11 /* The object does not support creation of hard links */
#define E_FILESYSTEM_OPERATION_RENAME   12 /* The object does not support renaming of items */
#define E_FILESYSTEM_OPERATION_UNLINK   13 /* The object does not support unlinking files */
#define E_FILESYSTEM_OPERATION_RMDIR    14 /* The object does not support removal of directories */
#define E_FILESYSTEM_OPERATION_ATTRIB   15 /* The values specified by chmod() or chown() cannot be applied within the file system */
#define E_FILESYSTEM_OPERATION_WRATTR   16 /* The object does not support changes to attributes being written to disk */
#define E_FILESYSTEM_OPERATION_SEEK     17 /* The object does not support seeking in file stream */
#define E_FILESYSTEM_OPERATION_MMAP     18 /* The object does not support mapping data into memory */
#define E_FILESYSTEM_OPERATION_SYNC     19 /* The object does not support the fsync() operator */
#define E_FILESYSTEM_OPERATION_DATASYNC 20 /* The object does not support the fdatasync() operator */
#define E_FILESYSTEM_OPERATION_STAT     21 /* The object does not support the fstat() operator */
#define E_FILESYSTEM_OPERATION_ALLOCATE 22 /* The object does not support the fallocate() operator */
#define E_FILESYSTEM_OPERATION_FLOCK    23 /* The object does not support the flock() operator */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


__DECL_END

#endif /* !_KOS_EXCEPT_REASON_FS_H */
