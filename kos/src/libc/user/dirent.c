/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_DIRENT_C
#define GUARD_LIBC_USER_DIRENT_C 1
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/overflow.h>

#include <kos/exec/ifunc.h>
#include <kos/syscalls.h>

#include <assert.h>
#include <fcntl.h>
#include <limits.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <syscall.h>
#include <unistd.h>

#include "../libc/compat.h"
#include "dirent.h"


DECL_BEGIN

#ifndef _DIRENT_MATCHES_DIRENT64
#error "Unsupported configuration"
#endif /* !_DIRENT_MATCHES_DIRENT64 */

struct __dirstream {
	fd_t           ds_fd;      /* [const][owned] The handle for the underlying file stream object. */
	size_t         ds_lodsize; /* Amount of bytes returned by the `kreaddir()' system call during its last invocation. */
	size_t         ds_bufsize; /* Size of the directory stream buffer (`ds_buf') in bytes. */
	struct dirent *ds_next;    /* [1..1][in(ds_buf)] Pointer to the next directory entry yet to-be read. */
	struct dirent *ds_buf;     /* [1..ds_bufsize][owned_if(!= ds_sbuf)] Directory entry buffer. */
	byte_t         ds_sbuf[offsetof(struct dirent, d_name) + 512]; /* Pre-allocated static dirent buffer.
	                                                                * NOTE: When  a dynamic buffer  has to be used,
	                                                                *       `realloc_in_place()' is used to attempt
	                                                                *       to free this buffer. */
};

/* # of leading bytes to allocate before `ds_buf' (for linux compatibility) */
/*ATTR_SECTION(".bss.crt.compat.linux.dirent")*/
PRIVATE ATTR_SECTION(".bss.crt.fs.dir") size_t dirbuf_compat_offset = 0;

#define dirstream_init_nofd(self)                                         \
	((self)->ds_lodsize = 0,                                              \
	 (self)->ds_bufsize = sizeof((self)->ds_sbuf) - dirbuf_compat_offset, \
	 (self)->ds_next = (self)->ds_buf = (struct dirent *)((self)->ds_sbuf + dirbuf_compat_offset))
#define dirstream_init(self, fd) \
	((self)->ds_fd = (fd), dirstream_init_nofd(self))
#define dirstream_fini_keepfd(self)                                                \
	(((self)->ds_buf != (struct dirent *)((self)->ds_sbuf + dirbuf_compat_offset)) \
	 ? free((byte_t *)(self)->ds_buf - dirbuf_compat_offset)                       \
	 : (void)0)
#define dirstream_fini(self)      \
	(dirstream_fini_keepfd(self), \
	 sys_close((self)->ds_fd))






/*[[[head:libd_opendir,hash:CRC-32=0x4310dc25]]]*/
/* >> opendir(3)
 * Open and return a new directory stream for reading, referring to `name' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED ATTR_IN(1) DIR *
NOTHROW_RPC(LIBDCALL libd_opendir)(char const *name)
/*[[[body:libd_opendir]]]*/
{
	return libd_opendirat(AT_FDCWD, name);
}
/*[[[end:libd_opendir]]]*/

/*[[[head:libc_opendir,hash:CRC-32=0x7d92fb23]]]*/
/* >> opendir(3)
 * Open and return a new directory stream for reading, referring to `name' */
INTERN ATTR_SECTION(".text.crt.fs.dir") WUNUSED ATTR_IN(1) DIR *
NOTHROW_RPC(LIBCCALL libc_opendir)(char const *name)
/*[[[body:libc_opendir]]]*/
{
	DIR *result;
	fd_t fd = open(name, O_RDONLY | O_DIRECTORY | O_CLOEXEC);
	if unlikely(fd < 0)
		goto err;
	result = fdopendir(fd);
	if unlikely(!result)
		sys_close(fd);
	return result;
err:
	return NULL;
}
/*[[[end:libc_opendir]]]*/

/*[[[head:libd_fopendirat,hash:CRC-32=0x8c70c5dc]]]*/
/* >> fopendirat(3)
 * Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED ATTR_IN(2) DIR *
NOTHROW_RPC(LIBDCALL libd_fopendirat)(fd_t dirfd,
                                      char const *name,
                                      oflag_t oflags)
/*[[[body:libd_fopendirat]]]*/
{
	return libc_fopendirat(dirfd, name, oflags | libd_O_DOSPATH);
}
/*[[[end:libd_fopendirat]]]*/

/*[[[head:libc_fopendirat,hash:CRC-32=0xe9c9e85f]]]*/
/* >> fopendirat(3)
 * Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
INTERN ATTR_SECTION(".text.crt.fs.dir") WUNUSED ATTR_IN(2) DIR *
NOTHROW_RPC(LIBCCALL libc_fopendirat)(fd_t dirfd,
                                      char const *name,
                                      oflag_t oflags)
/*[[[body:libc_fopendirat]]]*/
{
	DIR *result;
	fd_t fd = openat(dirfd,
	                 name,
	                 oflags);
	if unlikely(fd < 0)
		goto err;
	result = fdopendir(fd);
	if unlikely(!result)
		sys_close(fd);
	return result;
err:
	return NULL;
}
/*[[[end:libc_fopendirat]]]*/

/*[[[head:libd_opendirat,hash:CRC-32=0x975689d2]]]*/
/* >> opendirat(3)
 * Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.dir") WUNUSED ATTR_IN(2) DIR *
NOTHROW_RPC(LIBDCALL libd_opendirat)(fd_t dirfd,
                                     char const *name)
/*[[[body:libd_opendirat]]]*/
{
	return libc_fopendirat(dirfd, name, O_RDONLY | O_DIRECTORY | libd_O_DOSPATH);
}
/*[[[end:libd_opendirat]]]*/

/*[[[head:libc_opendirat,hash:CRC-32=0x374a1363]]]*/
/* >> opendirat(3)
 * Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
INTERN ATTR_SECTION(".text.crt.fs.dir") WUNUSED ATTR_IN(2) DIR *
NOTHROW_RPC(LIBCCALL libc_opendirat)(fd_t dirfd,
                                     char const *name)
/*[[[body:libc_opendirat]]]*/
{
	return libc_fopendirat(dirfd, name, O_RDONLY | O_DIRECTORY);
}
/*[[[end:libc_opendirat]]]*/

/*[[[head:libc_closedir,hash:CRC-32=0xc5965c1]]]*/
/* >> closedir(3)
 * Close a directory stream previously returned by `opendir(3)' and friends */
INTERN ATTR_SECTION(".text.crt.fs.dir") ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_closedir)(DIR *dirp)
/*[[[body:libc_closedir]]]*/
{
	if unlikely(!dirp)
		goto err_null;
	dirstream_fini(dirp);
	free(dirp);
	return 0;
err_null:
	return libc_seterrno(EINVAL);
}
/*[[[end:libc_closedir]]]*/

/*[[[head:libc_fdclosedir,hash:CRC-32=0xd1d40668]]]*/
/* >> fdclosedir(3)
 * Same as `closedir()', but instead of also closing the underlying file descriptor, return it */
INTERN ATTR_SECTION(".text.crt.fs.dir") WUNUSED ATTR_INOUT(1) fd_t
NOTHROW_NCX(LIBCCALL libc_fdclosedir)(DIR *dirp)
/*[[[body:libc_fdclosedir]]]*/
{
	fd_t result;
	if unlikely(!dirp)
		goto err_null;
	result = dirp->ds_fd;
	dirstream_fini_keepfd(dirp);
	free(dirp);
	return result;
err_null:
	return libc_seterrno(EINVAL);
}
/*[[[end:libc_fdclosedir]]]*/

/*[[[head:libc_rewinddir,hash:CRC-32=0x6db55224]]]*/
/* >> rewinddir(3)
 * Rewind the given directory stream in such a way that the next call
 * to `readdir(3)' will once again  return the first directory  entry */
INTERN ATTR_SECTION(".text.crt.fs.dir") ATTR_INOUT(1) void
NOTHROW_NCX(LIBCCALL libc_rewinddir)(DIR *__restrict dirp)
/*[[[body:libc_rewinddir]]]*/
{
	if likely(dirp) {
#if defined(SYS_lseek)
		sys_lseek(dirp->ds_fd, 0, SEEK_SET);
#elif defined(SYS_lseek64)
		sys_lseek64(dirp->ds_fd, 0, SEEK_SET);
#elif defined(SYS__llseek)
		{
			uint64_t res;
			sys__llseek(dirp->ds_fd, 0, &res, SEEK_SET);
		}
#else /* ... */
#error "No suitable sys_lseek() function"
#endif /* !... */
		dirp->ds_lodsize = 0;
	}
}
/*[[[end:libc_rewinddir]]]*/

/*[[[head:libc_fdopendir,hash:CRC-32=0xdeb2b048]]]*/
/* >> fdopendir(3)
 * Create a new directory stream by inheriting the given `fd' as stream handle */
INTERN ATTR_SECTION(".text.crt.fs.dir") WUNUSED ATTR_FDREAD(1) DIR *
NOTHROW_NCX(LIBCCALL libc_fdopendir)(fd_t fd)
/*[[[body:libc_fdopendir]]]*/
{
	DIR *result = (DIR *)malloc(sizeof(DIR));
	if unlikely(!result)
		goto done;
	dirstream_init(result, fd);
done:
	return result;
}
/*[[[end:libc_fdopendir]]]*/

/*[[[head:libc_seekdir,hash:CRC-32=0xc12cdbd]]]*/
/* >> seekdir(3)
 * Get the directory stream position */
INTERN ATTR_SECTION(".text.crt.fs.dir") ATTR_INOUT(1) void
NOTHROW_NCX(LIBCCALL libc_seekdir)(DIR *__restrict dirp,
                                   longptr_t pos)
/*[[[body:libc_seekdir]]]*/
{
	if likely(dirp) {
		dirp->ds_lodsize = 0;
#if defined(SYS_lseek) && (__SIZEOF_LONG__ <= __SIZEOF_OFF32_T__)
		sys_lseek(dirp->ds_fd, (off32_t)pos, SEEK_SET);
#elif defined(SYS_lseek64) && (__SIZEOF_LONG__ <= __SIZEOF_OFF64_T__)
		sys_lseek64(dirp->ds_fd, (off32_t)pos, SEEK_SET);
#elif defined(SYS_lseek64)
		sys_lseek64(dirp->ds_fd, (off32_t)pos, SEEK_SET);
#elif defined(SYS_lseek)
		sys_lseek(dirp->ds_fd, (off32_t)pos, SEEK_SET);
#elif defined(SYS__llseek)
		{
			uint64_t res;
			sys__llseek(dirp->ds_fd, (int64_t)pos, &res, SEEK_SET);
		}
#else /* ... */
#error "No suitable sys_lseek() function"
#endif /* !... */
	}
}
/*[[[end:libc_seekdir]]]*/

/*[[[head:libc_telldir,hash:CRC-32=0x50ddce5d]]]*/
/* >> telldir(3)
 * Get the directory stream position */
INTERN ATTR_SECTION(".text.crt.fs.dir") ATTR_INOUT(1) longptr_t
NOTHROW_NCX(LIBCCALL libc_telldir)(DIR *__restrict dirp)
/*[[[body:libc_telldir]]]*/
{
	if unlikely(!dirp)
		goto err_null;
	/* XXX: Adjust for unread, but pre-cached directory entries? */
#if __SIZEOF_LONG__ == 4
	return (long int)lseek(dirp->ds_fd, 0, SEEK_CUR);
#else /* __SIZEOF_LONG__ == 4 */
	return (long int)lseek64(dirp->ds_fd, 0, SEEK_CUR);
#endif /* __SIZEOF_LONG__ != 4 */
err_null:
	return libc_seterrno(EINVAL);
}
/*[[[end:libc_telldir]]]*/

/*[[[head:libc_dirfd,hash:CRC-32=0xf81eb32f]]]*/
/* >> dirfd(3)
 * Return the underlying file descriptor of the given directory stream */
INTERN ATTR_SECTION(".text.crt.fs.dir") ATTR_PURE ATTR_IN(1) fd_t
NOTHROW_NCX(LIBCCALL libc_dirfd)(DIR __KOS_FIXED_CONST *__restrict dirp)
/*[[[body:libc_dirfd]]]*/
{
	if unlikely(!dirp)
		goto err_null;
	return dirp->ds_fd;
err_null:
	return libc_seterrno(EINVAL);
}
/*[[[end:libc_dirfd]]]*/

/*[[[head:libc_getdirentries,hash:CRC-32=0xba383c0d]]]*/
/* >> getdirentries(2), getdirentries64(2)
 * Linux's underlying system call for reading the entries of a directory */
INTERN ATTR_SECTION(".text.crt.fs.dir") ATTR_FDREAD(1) ATTR_INOUT(4) ATTR_OUTS(2, 3) ssize_t
NOTHROW_RPC(LIBCCALL libc_getdirentries)(fd_t fd,
                                         char *__restrict buf,
                                         size_t nbytes,
                                         off_t *__restrict basep)
/*[[[body:libc_getdirentries]]]*/
{
	ssize_t result;
	if unlikely(lseek(fd, *basep, SEEK_SET) < 0)
		goto err;
	result = kreaddir(fd, (struct dirent *)buf,
	                  nbytes, READDIR_MULTIPLE);
	if (result > 0)
		*basep += result;
	return result;
err:
	return -1;
}
/*[[[end:libc_getdirentries]]]*/

/*[[[impl:libc_getdirentries64]]]*/
DEFINE_INTERN_ALIAS(libc_getdirentries64, libc_getdirentries);

/*[[[impl:libc_kreaddirf64]]]*/
/*[[[impl:libc_kreaddir64]]]*/
DEFINE_INTERN_WEAK_ALIAS(libc_kreaddirf64, libc_kreaddirf);
DEFINE_INTERN_WEAK_ALIAS(libc_kreaddir64, libc_kreaddir);

/*[[[head:libc_kreaddirf,hash:CRC-32=0x5bcdadfe]]]*/
/* >> kreaddir(2), kreaddirf(2), kreaddir64(2), kreaddirf64(2)
 * The KOS-specific system call for reading a single directory entry
 * from  a file  descriptor referring  to an  open directory stream.
 * @param: mode: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When  `READDIR_DEFAULT' was passed for `mode', the directory
 *                    stream will only be advanced when this value is >= 'bufsize'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
INTERN ATTR_SECTION(".text.crt.fs.dir") WUNUSED ATTR_FDREAD(1) ssize_t
NOTHROW_RPC(LIBCCALL libc_kreaddirf)(fd_t fd,
                                     struct dirent *buf,
                                     size_t bufsize,
                                     unsigned int mode,
                                     oflag_t flags)
/*[[[body:libc_kreaddirf]]]*/
{
	ssize_t result;
	result = sys_kreaddirf(fd, buf, bufsize, mode, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_kreaddirf]]]*/

/*[[[head:libc_kreaddir,hash:CRC-32=0x2e47e624]]]*/
/* >> kreaddir(2), kreaddirf(2), kreaddir64(2), kreaddirf64(2)
 * The KOS-specific system call for reading a single directory entry
 * from  a file  descriptor referring  to an  open directory stream.
 * @param: mode: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When  `READDIR_DEFAULT' was passed for `mode', the directory
 *                    stream will only be advanced when this value is >= 'bufsize'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
INTERN ATTR_SECTION(".text.crt.fs.dir") WUNUSED ATTR_FDREAD(1) ssize_t
NOTHROW_RPC(LIBCCALL libc_kreaddir)(fd_t fd,
                                    struct dirent *buf,
                                    size_t bufsize,
                                    unsigned int mode)
/*[[[body:libc_kreaddir]]]*/
{
	ssize_t result;
	result = sys_kreaddir(fd, buf, bufsize, mode);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_kreaddir]]]*/


/*[[[head:libc_readdirk,hash:CRC-32=0x5abc9f7e]]]*/
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
INTERN ATTR_SECTION(".text.crt.fs.dir") ATTR_INOUT(1) struct dirent *
NOTHROW_RPC(LIBCCALL libc_readdirk)(DIR *__restrict dirp)
/*[[[body:libc_readdirk]]]*/
{
	struct dirent *result;
	ssize_t load_size;
	if unlikely(!dirp)
		goto err_null;
again:
	result = dirp->ds_next;

	/* Check if the pre-loaded next-pointer is valid. */
	if (READDIR_MULTIPLE_ISVALID(result, dirp->ds_buf, dirp->ds_lodsize)) {
		if (READDIR_MULTIPLE_ISEOF(result))
			return NULL; /* End of directory */
		dirp->ds_next = READDIR_MULTIPLE_GETNEXT(result);
		return result;
	}

	/* Read more entries. */
	load_size = kreaddir(dirp->ds_fd,
	                     dirp->ds_buf,
	                     dirp->ds_bufsize,
	                     READDIR_MULTIPLE |
	                     READDIR_WANTEOF);
	if unlikely(load_size <= 0)
		return NULL; /* Error, or end-of-directory. */

	if unlikely((size_t)load_size > dirp->ds_bufsize) {
		size_t new_bufsize;
		struct dirent *new_buffer;
		errno_t error;

		/* Buffer is too small. -> Must allocate one that is larger. */
		if (dirp->ds_buf == (struct dirent *)(dirp->ds_sbuf + dirbuf_compat_offset)) {
			/* Free the static buffer. */
			realloc_in_place(dirp, offsetof(DIR, ds_sbuf));
			dirp->ds_buf = NULL;
		}
		new_bufsize = load_size << 1;
		if unlikely(new_bufsize < (size_t)load_size)
			new_bufsize = (size_t)load_size;

		/* Must preserve errno when this realloc fails */
		error      = libc_geterrno();
		new_buffer = (struct dirent *)realloc(dirp->ds_buf, new_bufsize + dirbuf_compat_offset);
		if unlikely(!new_buffer) {
			libc_seterrno(error);
			new_bufsize = (size_t)load_size;
			new_buffer  = (struct dirent *)realloc(dirp->ds_buf, new_bufsize + dirbuf_compat_offset);
			if unlikely(!new_buffer)
				return NULL;
		}

		/* Install the new buffer. */
		dirp->ds_buf     = (struct dirent *)((byte_t *)new_buffer + dirbuf_compat_offset);
		dirp->ds_bufsize = new_bufsize;
	}
	dirp->ds_next    = dirp->ds_buf;
	dirp->ds_lodsize = (size_t)load_size;
	goto again;
err_null:
	libc_seterrno(EINVAL);
	return NULL;
}
/*[[[end:libc_readdirk]]]*/

/*[[[impl:libc_readdirk64]]]*/
DEFINE_INTERN_ALIAS(libc_readdirk64, libc_readdirk);

/*[[[head:libc_readdirk_r,hash:CRC-32=0x31800f65]]]*/
/* >> readdir_r(3), readdir64_r(3)
 * Reentrant version of `readdir(3)'
 * NOTE: This ~reentrant~ version of readdir()  is strongly discouraged from being  used in KOS, as  the
 *       kernel does not impose a limit on the length of a single directory entry name (s.a. 'kreaddir')
 * >> Instead, simply use `readdir()' / `readdir64()', which will automatically (re-)allocate an internal,
 *    per-directory  buffer  of sufficient  size to  house any  directory entry  (s.a.: `READDIR_DEFAULT') */
INTERN ATTR_SECTION(".text.crt.fs.dir") ATTR_INOUT(1) ATTR_OUT(2) ATTR_OUT(3) int
NOTHROW_RPC(LIBCCALL libc_readdirk_r)(DIR *__restrict dirp,
                                      struct dirent *__restrict entry,
                                      struct dirent **__restrict result)
/*[[[body:libc_readdirk_r]]]*/
{
	errno_t old_error;
	struct dirent *ent;
	old_error = libc_geterrno();
	libc_seterrno(EOK);
	ent = libc_readdirk(dirp);
	if (!ent) {
		errno_t error;
		error = libc_geterrno();
		libc_seterrno(old_error); /* Restore the old error. */
		*result = NULL;
		return error;
	}
	libc_seterrno(old_error); /* Restore the old error. */
	if unlikely(ent->d_namlen >= NAME_MAX) {
		*result = NULL;
		return ENAMETOOLONG;
	}
	memcpy(entry, ent,
	       offsetof(struct dirent, d_name) +
	       (ent->d_namlen + 1) * sizeof(char));
	*result = entry;
	return 0;
}
/*[[[end:libc_readdirk_r]]]*/

/*[[[impl:libc_readdirk64_r]]]*/
DEFINE_INTERN_ALIAS(libc_readdirk64_r, libc_readdirk_r);

/*[[[head:libc_scandirk,hash:CRC-32=0x27f0733a]]]*/
/* >> scandir(3), scandir64(3)
 * Scan a directory `dir' for all contained directory entries */
INTERN ATTR_SECTION(".text.crt.fs.dir") ATTR_IN(1) ATTR_OUT(2) __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(LIBCCALL libc_scandirk)(char const *__restrict dir,
                                    struct dirent ***__restrict namelist,
                                    int (LIBKCALL *selector)(struct dirent const *entry),
                                    int (LIBKCALL *cmp)(struct dirent const **a, struct dirent const **b))
/*[[[body:libc_scandirk]]]*/
{
	return libc_scandiratk(AT_FDCWD, dir, namelist, selector, cmp);
}
/*[[[end:libc_scandirk]]]*/

/*[[[head:libc_scandiratk,hash:CRC-32=0x11bdce34]]]*/
/* >> scandirat(3), scandirat64(3)
 * Scan a directory `dirfd:dir' for all contained directory entries */
INTERN ATTR_SECTION(".text.crt.fs.dir") ATTR_IN(2) ATTR_OUT(3) __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(LIBCCALL libc_scandiratk)(fd_t dirfd,
                                      char const *__restrict dir,
                                      struct dirent ***__restrict namelist,
                                      int (LIBKCALL *selector)(struct dirent const *entry),
                                      int (LIBKCALL *cmp)(struct dirent const **a, struct dirent const **b))
/*[[[body:libc_scandiratk]]]*/
{
	DIR stream;
	ssize_t result;
	struct dirent **ents_list;
	size_t ents_used, ents_size;
	errno_t saved_errno;
	result    = -1;
	*namelist = NULL;

	/* Open the named directory. */
	stream.ds_fd = openat(dirfd, dir, O_RDONLY | O_DIRECTORY | O_CLOEXEC);
	if unlikely(stream.ds_fd < 0)
		goto done_nostream;

	/* Initialize the directory stream. */
	dirstream_init_nofd(&stream);

	/* Enumerate the directory's contents. */
	ents_list = NULL; /* Vector of selected directories */
	ents_used = 0;    /* # of used entries in `ent_list' */
	ents_size = 0;    /* # of allocated entries in `ent_list' */
	saved_errno = libc_geterrno();
	libc_seterrno(EOK);
	for (;;) {
		struct dirent *ent, *ent_copy;
		size_t ent_size;
		ent = libc_readdirk(&stream);
		if (!ent) {
			/* Check if this is an error, or if it's EOF */
			if (libc_geterrno() != EOK)
				goto err; /* It's an error! */
			/* Its EOF */
			break;
		}
		/* Check with the filter-function if we should use this entry. */
		if (selector) {
			if ((*selector)(ent) == 0)
				continue; /* Don't include this one. */
		}

		/* Make sure `ent_list' has sufficient space for another entry. */
		if (ents_used >= ents_size) {
			struct dirent **new_ents_list;
			size_t new_alloc;
			if (OVERFLOW_UMUL(ents_size, 2, &new_alloc))
				new_alloc = (size_t)-1;
			if (!new_alloc)
				new_alloc = 16;
			new_ents_list = (struct dirent **)realloc(ents_list,
			                                          new_alloc,
			                                          sizeof(struct dirent *));
			if unlikely(!new_ents_list) {
				new_alloc = ents_used + 1;
				new_ents_list = (struct dirent **)realloc(ents_list,
				                                          new_alloc,
				                                          sizeof(struct dirent *));
				if unlikely(!new_ents_list)
					goto err;
			}
			ents_list = new_ents_list;
			ents_size = new_alloc;
		}

		/* Append a copy of `ent' to `ent_list' */
		ent_size = offsetof(struct dirent, d_name) +
		           (ent->d_namlen + 1) * sizeof(char);
		ent_copy = (struct dirent *)malloc(ent_size);
		if unlikely(!ent_copy)
			goto err;
		ent_copy = (struct dirent *)memcpy(ent_copy, ent, ent_size);

		/* Actually append the entry copy. */
		ents_list[ents_used++] = ent_copy;
}
	libc_seterrno(saved_errno);
	result = (ssize_t)ents_used;
	if (!ents_list) {
		/* Don't return a NULL-pointer on success! */
		assert(ents_used == 0);
#ifdef __MALLOC_ZERO_IS_NONNULL
		ents_list = (struct dirent **)malloc(0);
#else /* __MALLOC_ZERO_IS_NONNULL */
		ents_list = (struct dirent **)malloc(1);
#endif /* !__MALLOC_ZERO_IS_NONNULL */
		if unlikely(!ents_list)
			result = -1;
	} else if (ents_size > ents_used) {
		/* Try to reclaim unused memory. */
		struct dirent **new_ents_list;
		new_ents_list = (struct dirent **)realloc(ents_list,
		                                          ents_used,
		                                          sizeof(struct dirent *));
		if likely(new_ents_list)
			ents_list = new_ents_list;
	}

	/* Finally, we must qsort() the list as a whole. */
	if (cmp) {
		qsort(ents_list, ents_used,
		      sizeof(struct dirent *),
		      (comparison_fn_t)cmp);
	}
done:
	*namelist = ents_list; /* Inherit */
	dirstream_fini(&stream);
done_nostream:
	return result;
err:

	/* Free already-allocated dirent copies, as well as the dirent list. */
	while (ents_used) {
		--ents_used;
		free(ents_list[ents_used]);
	}
	free(ents_list);
	ents_list = NULL; /* Write-back a NULL-pointer on error */
	goto done;
}
/*[[[end:libc_scandiratk]]]*/

/*[[[impl:libc_scandirk64]]]*/
DEFINE_INTERN_ALIAS(libc_scandirk64, libc_scandirk);

/*[[[impl:libc_scandiratk64]]]*/
DEFINE_INTERN_ALIAS(libc_scandiratk64, libc_scandiratk);



/************************************************************************/
/* Linux compatibility                                                  */
/************************************************************************/
struct glibc_dirent32 {
	uintptr_t d_ino;
	intptr_t  d_off;
	uint16_t  d_reclen;
	uint8_t   d_type;
	char      d_name[256];
};
struct glibc_dirent64 {
	uint64_t d_ino;
	int64_t  d_off;
	uint16_t d_reclen;
	uint8_t  d_type;
	char     d_name[256];
};

#undef SIZEOF_GLIBC_DIRENT32_MATCHES_KOS_DIRENT
#undef SIZEOF_GLIBC_DIRENT32_MATCHES_GLIBC_DIRENT64
#if __SIZEOF_POINTER__ == 4
/* Well... Not really so much "matches", and more so much "same-sized" and  "same-field-offsets"
 * The difference is that KOS's `struct dirent' doesn't have a `d_off' field, and always defines
 * its `d_ino' field as 64-bit, meaning that the user  will read `d_off' as the high 32 bits  of
 * the INO field, which probably won't make much sense. But then again: what would you even want
 * to  use the `d_off' for anyways? -- seekdir(3) maybe? Because that's already kind-of iffy, as
 * `d_off' and `seekdir(3)'s argument don't even have the same typing... */
#define SIZEOF_GLIBC_DIRENT32_MATCHES_KOS_DIRENT
#else /* __SIZEOF_POINTER__ == 4 */
#define SIZEOF_GLIBC_DIRENT32_MATCHES_GLIBC_DIRENT64
#endif /* __SIZEOF_POINTER__ != 4 */


#ifdef SIZEOF_GLIBC_DIRENT32_MATCHES_KOS_DIRENT
/* Evaluates to true if the `d_type' must be removed for compatibility */
#define get_glibc_dirent32_compat_libc5() libc_compat_islibc5()

PRIVATE ATTR_SECTION(".text.crt.compat.linux.dirent")
ATTR_RETNONNULL WUNUSED NONNULL((1)) struct glibc_dirent32 *
NOTHROW_NCX(__FCALL dirent_glibc32_to_libc5)(struct glibc_dirent32 *__restrict self) {
	/* Old versions of libc4/5 didn't have the `d_type' field.
	 * Instead, their `struct dirent' matched `struct old_linux_direntx32',
	 * which is identical to `struct glibc_dirent32', except that it  lacks
	 * the `d_type' field (which becomes the first name-char instead) */
	self = (struct glibc_dirent32 *)memmoveup((byte_t *)self + 1, self, 10);
	return self;
}

PRIVATE ATTR_SECTION(".text.crt.compat.linux.dirent")
ATTR_RETNONNULL WUNUSED NONNULL((1)) struct glibc_dirent32 *
NOTHROW_NCX(__FCALL dirent2glibc32)(struct dirent *__restrict self) {
	static_assert(offsetof(struct glibc_dirent32, d_ino) == offsetof(struct dirent, d_ino));
	static_assert(offsetof(struct glibc_dirent32, d_reclen) == offsetof(struct dirent, d_namlen));
	static_assert(offsetof(struct glibc_dirent32, d_type) == offsetof(struct dirent, d_type));
	static_assert(offsetof(struct glibc_dirent32, d_name) == offsetof(struct dirent, d_name));
	struct glibc_dirent32 *result;
	result = (struct glibc_dirent32 *)self;
	result->d_off = 0; /* We don't have this one... */
	result->d_reclen += offsetof(struct glibc_dirent32, d_name) + 1;
	return result;
}

INTERN ATTR_SECTION(".text.crt.compat.linux.dirent") NONNULL((1)) struct glibc_dirent32 *
NOTHROW_RPC(LIBCCALL libc_readdir)(DIR *__restrict dirp) {
	struct dirent *result;
	struct glibc_dirent32 *resent;
	result = libc_readdirk(dirp);
	if unlikely(!result)
		return NULL;
	resent = dirent2glibc32(result);
	if (get_glibc_dirent32_compat_libc5())
		resent = dirent_glibc32_to_libc5(resent);
	return resent;
}

INTERN ATTR_SECTION(".text.crt.compat.linux.dirent") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBCCALL libc_readdir_r)(DIR *__restrict dirp,
                                     struct glibc_dirent32 *__restrict entry,
                                     struct glibc_dirent32 **__restrict result) {
	int retval;
	retval = libc_readdirk_r(dirp, (struct dirent *)entry, (struct dirent **)result);
	if (retval == 0) {
		*result = dirent2glibc32((struct dirent *)*result);
		if (get_glibc_dirent32_compat_libc5())
			*result = dirent_glibc32_to_libc5(*result);
	}
	return retval;
}

INTERN ATTR_SECTION(".text.crt.compat.linux.dirent") NONNULL((2, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(LIBCCALL libc_scandirat)(fd_t dirfd,
                                     char const *__restrict dir,
                                     struct glibc_dirent32 ***__restrict namelist,
                                     int (LIBKCALL *selector)(struct glibc_dirent32 const *entry),
                                     int (LIBKCALL *cmp)(struct glibc_dirent32 const **a, struct glibc_dirent32 const **b)) {
	DIR stream;
	ssize_t result;
	struct glibc_dirent32 **ents_list;
	size_t ents_used, ents_size;
	errno_t saved_errno;
	result    = -1;
	*namelist = NULL;

	/* Open the named directory. */
	stream.ds_fd = openat(dirfd, dir, O_RDONLY | O_DIRECTORY | O_CLOEXEC);
	if unlikely(stream.ds_fd < 0)
		goto done_nostream;

	/* Initialize the directory stream. */
	dirstream_init_nofd(&stream);

	/* Enumerate the directory's contents. */
	ents_list = NULL; /* Vector of selected directories */
	ents_used = 0;    /* # of used entries in `ent_list' */
	ents_size = 0;    /* # of allocated entries in `ent_list' */
	saved_errno = libc_geterrno();
	libc_seterrno(EOK);
	for (;;) {
		struct dirent *kos_ent;
		struct glibc_dirent32 *ent;
		struct glibc_dirent32 *ent_copy;
		kos_ent = libc_readdirk(&stream);
		if (!kos_ent) {
			/* Check if this is an error, or if it's EOF */
			if (libc_geterrno() != EOK)
				goto err; /* It's an error! */
			break; /* Its EOF */
		}
		ent = dirent2glibc32(kos_ent);

		/* Check with the filter-function if we should use this entry. */
		if (selector) {
			if ((*selector)(ent) == 0)
				continue; /* Don't include this one. */
		}

		/* Make sure `ent_list' has sufficient space for another entry. */
		if (ents_used >= ents_size) {
			struct glibc_dirent32 **new_ents_list;
			size_t new_alloc;
			if (OVERFLOW_UMUL(ents_size, 2, &new_alloc))
				new_alloc = (size_t)-1;
			if (!new_alloc)
				new_alloc = 16;
			new_ents_list = (struct glibc_dirent32 **)realloc(ents_list,
			                                                  new_alloc,
			                                                  sizeof(struct glibc_dirent32 *));
			if unlikely(!new_ents_list) {
				new_alloc = ents_used + 1;
				new_ents_list = (struct glibc_dirent32 **)realloc(ents_list,
				                                                  new_alloc,
				                                                  sizeof(struct glibc_dirent32 *));
				if unlikely(!new_ents_list)
					goto err;
			}
			ents_list = new_ents_list;
			ents_size = new_alloc;
		}

		/* Append a copy of `ent' to `ent_list' */
		ent_copy = (struct glibc_dirent32 *)malloc(ent->d_reclen);
		if unlikely(!ent_copy)
			goto err;
		ent_copy = (struct glibc_dirent32 *)memcpy(ent_copy, ent, ent->d_reclen);

		/* Actually append the entry copy. */
		ents_list[ents_used++] = ent_copy;
	}
	libc_seterrno(saved_errno);
	result = (ssize_t)ents_used;
	if (!ents_list) {
		/* Don't return a NULL-pointer on success! */
		assert(ents_used == 0);
#ifdef __MALLOC_ZERO_IS_NONNULL
		ents_list = (struct glibc_dirent32 **)malloc(0);
#else /* __MALLOC_ZERO_IS_NONNULL */
		ents_list = (struct glibc_dirent32 **)malloc(1);
#endif /* !__MALLOC_ZERO_IS_NONNULL */
		if unlikely(!ents_list)
			result = -1;
	} else if (ents_size > ents_used) {
		/* Try to reclaim unused memory. */
		struct glibc_dirent32 **new_ents_list;
		new_ents_list = (struct glibc_dirent32 **)realloc(ents_list,
		                                                  ents_used,
		                                                  sizeof(struct glibc_dirent32 *));
		if likely(new_ents_list)
			ents_list = new_ents_list;
	}

	/* Finally, we must qsort() the list as a whole. */
	if (cmp) {
		qsort(ents_list, ents_used,
		      sizeof(struct glibc_dirent32 *),
		      (comparison_fn_t)cmp);
	}
done:
	/* Yes: libc4/5 did have a scandir(3) function! */
	if (get_glibc_dirent32_compat_libc5()) {
		size_t i;
		for (i = 0; i < ents_used; ++i)
			ents_list[i] = dirent_glibc32_to_libc5(ents_list[i]);
	}
	*namelist = ents_list; /* Inherit */
	dirstream_fini(&stream);
done_nostream:
	return result;
err:

	/* Free already-allocated dirent copies, as well as the dirent list. */
	while (ents_used) {
		--ents_used;
		free(ents_list[ents_used]);
	}
	free(ents_list);
	ents_list = NULL; /* Write-back a NULL-pointer on error */
	goto done;
}

INTERN ATTR_SECTION(".text.crt.compat.linux.dirent") NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(LIBCCALL libc_scandir)(char const *__restrict dir,
                                   struct glibc_dirent32 ***__restrict namelist,
                                   int (LIBKCALL *selector)(struct glibc_dirent32 const *entry),
                                   int (LIBKCALL *cmp)(struct glibc_dirent32 const **a, struct glibc_dirent32 const **b)) {
	return libc_scandirat(AT_FDCWD, dir, namelist, selector, cmp);
}
#elif defined(SIZEOF_GLIBC_DIRENT32_MATCHES_GLIBC_DIRENT64)
static_assert(sizeof(struct glibc_dirent32) == sizeof(struct glibc_dirent64));
DEFINE_INTERN_ALIAS(libc_readdir, libc_readdir64);
DEFINE_INTERN_ALIAS(libc_readdir_r, libc_readdir64_r);
DEFINE_INTERN_ALIAS(libc_scandirat, libc_scandirat64);
DEFINE_INTERN_ALIAS(libc_scandir, libc_scandir64);
#else /* ... */
#error "Invalid configuration"
#endif /* !... */

PRIVATE ATTR_SECTION(".text.crt.compat.linux.dirent") NONNULL((1))
ATTR_RETNONNULL WUNUSED struct glibc_dirent64 *__FCALL
dirent2glibc64(struct dirent *__restrict self) {
	static_assert(offsetof(struct glibc_dirent64, d_ino) == offsetof(struct dirent, d_ino));
	static_assert(offsetof(struct glibc_dirent64, d_reclen) == 8 + offsetof(struct dirent, d_namlen));
	static_assert(offsetof(struct glibc_dirent64, d_type) == 8 + offsetof(struct dirent, d_type));
	static_assert(offsetof(struct glibc_dirent64, d_name) == 8 + offsetof(struct dirent, d_name));
	struct glibc_dirent64 *result;
	assertf(dirbuf_compat_offset >= 8, "We need at least 8 bytes of compat space!");
	result = (struct glibc_dirent64 *)((byte_t *)self - 8);
	result->d_ino = self->d_ino64;
	result->d_off = 0; /* We don't have this one... */
	result->d_reclen += offsetof(struct glibc_dirent64, d_name) + 1;
	return result;
}

INTERN ATTR_SECTION(".text.crt.compat.linux.dirent") NONNULL((1)) struct glibc_dirent64 *
NOTHROW_RPC(LIBCCALL libc_readdir64)(DIR *__restrict dirp) {
	struct dirent *result;
	result = libc_readdirk(dirp);
	if unlikely(!result)
		return NULL;
	return dirent2glibc64(result);
}

INTERN ATTR_SECTION(".text.crt.compat.linux.dirent") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBCCALL libc_readdir64_r)(DIR *__restrict dirp,
                                       struct glibc_dirent64 *__restrict entry,
                                       struct glibc_dirent64 **__restrict result) {
	errno_t old_error;
	struct dirent *kos_ent;
	struct glibc_dirent64 *ent;
	old_error = libc_geterrno();
	libc_seterrno(EOK);
	kos_ent = libc_readdirk(dirp);
	if (!kos_ent) {
		errno_t error;
		error = libc_geterrno();
		libc_seterrno(old_error); /* Restore the old error. */
		*result = NULL;
		return error;
	}
	libc_seterrno(old_error); /* Restore the old error. */
	if unlikely(kos_ent->d_namlen >= NAME_MAX) {
		*result = NULL;
		return ENAMETOOLONG;
	}
	ent = dirent2glibc64(kos_ent);
	memcpy(entry, ent, ent->d_reclen);
	*result = entry;
	return 0;
}

INTERN ATTR_SECTION(".text.crt.compat.linux.dirent") NONNULL((2, 3)) __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(LIBCCALL libc_scandirat64)(fd_t dirfd,
                                       char const *__restrict dir,
                                       struct glibc_dirent64 ***__restrict namelist,
                                       int (LIBKCALL *selector)(struct glibc_dirent64 const *entry),
                                       int (LIBKCALL *cmp)(struct glibc_dirent64 const **a, struct glibc_dirent64 const **b)) {
	DIR stream;
	ssize_t result;
	struct glibc_dirent64 **ents_list;
	size_t ents_used, ents_size;
	errno_t saved_errno;
	result    = -1;
	*namelist = NULL;

	/* Open the named directory. */
	stream.ds_fd = openat(dirfd, dir, O_RDONLY | O_DIRECTORY | O_CLOEXEC);
	if unlikely(stream.ds_fd < 0)
		goto done_nostream;

	/* Initialize the directory stream. */
	dirstream_init_nofd(&stream);

	/* Enumerate the directory's contents. */
	ents_list = NULL; /* Vector of selected directories */
	ents_used = 0;    /* # of used entries in `ent_list' */
	ents_size = 0;    /* # of allocated entries in `ent_list' */
	saved_errno = libc_geterrno();
	libc_seterrno(EOK);
	for (;;) {
		struct dirent *kos_ent;
		struct glibc_dirent64 *ent;
		struct glibc_dirent64 *ent_copy;
		kos_ent = libc_readdirk(&stream);
		if (!kos_ent) {
			/* Check if this is an error, or if it's EOF */
			if (libc_geterrno() != EOK)
				goto err; /* It's an error! */
			break; /* Its EOF */
		}
		ent = dirent2glibc64(kos_ent);

		/* Check with the filter-function if we should use this entry. */
		if (selector) {
			if ((*selector)(ent) == 0)
				continue; /* Don't include this one. */
		}

		/* Make sure `ent_list' has sufficient space for another entry. */
		if (ents_used >= ents_size) {
			struct glibc_dirent64 **new_ents_list;
			size_t new_alloc;
			if (OVERFLOW_UMUL(ents_size, 2, &new_alloc))
				new_alloc = (size_t)-1;
			if (!new_alloc)
				new_alloc = 16;
			new_ents_list = (struct glibc_dirent64 **)realloc(ents_list,
			                                                  new_alloc,
			                                                  sizeof(struct glibc_dirent64 *));
			if unlikely(!new_ents_list) {
				new_alloc = ents_used + 1;
				new_ents_list = (struct glibc_dirent64 **)realloc(ents_list,
				                                                  new_alloc,
				                                                  sizeof(struct glibc_dirent64 *));
				if unlikely(!new_ents_list)
					goto err;
			}
			ents_list = new_ents_list;
			ents_size = new_alloc;
		}

		/* Append a copy of `ent' to `ent_list' */
		ent_copy = (struct glibc_dirent64 *)malloc(ent->d_reclen);
		if unlikely(!ent_copy)
			goto err;
		ent_copy = (struct glibc_dirent64 *)memcpy(ent_copy, ent, ent->d_reclen);

		/* Actually append the entry copy. */
		ents_list[ents_used++] = ent_copy;
	}
	libc_seterrno(saved_errno);
	result = (ssize_t)ents_used;
	if (!ents_list) {
		/* Don't return a NULL-pointer on success! */
		assert(ents_used == 0);
#ifdef __MALLOC_ZERO_IS_NONNULL
		ents_list = (struct glibc_dirent64 **)malloc(0);
#else /* __MALLOC_ZERO_IS_NONNULL */
		ents_list = (struct glibc_dirent64 **)malloc(1);
#endif /* !__MALLOC_ZERO_IS_NONNULL */
		if unlikely(!ents_list)
			result = -1;
	} else if (ents_size > ents_used) {
		/* Try to reclaim unused memory. */
		struct glibc_dirent64 **new_ents_list;
		new_ents_list = (struct glibc_dirent64 **)realloc(ents_list,
		                                                  ents_used,
		                                                  sizeof(struct glibc_dirent64 *));
		if likely(new_ents_list)
			ents_list = new_ents_list;
	}

	/* Finally, we must qsort() the list as a whole. */
	if (cmp) {
		qsort(ents_list, ents_used,
		      sizeof(struct glibc_dirent64 *),
		      (comparison_fn_t)cmp);
	}
done:
	*namelist = ents_list; /* Inherit */
	dirstream_fini(&stream);
done_nostream:
	return result;
err:

	/* Free already-allocated dirent copies, as well as the dirent list. */
	while (ents_used) {
		--ents_used;
		free(ents_list[ents_used]);
	}
	free(ents_list);
	ents_list = NULL; /* Write-back a NULL-pointer on error */
	goto done;
}

INTERN ATTR_SECTION(".text.crt.compat.linux.dirent") NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
NOTHROW_RPC(LIBCCALL libc_scandir64)(char const *__restrict dir,
                                     struct glibc_dirent64 ***__restrict namelist,
                                     int (LIBKCALL *selector)(struct glibc_dirent64 const *entry),
                                     int (LIBKCALL *cmp)(struct glibc_dirent64 const **a, struct glibc_dirent64 const **b)) {
	return libc_scandirat64(AT_FDCWD, dir, namelist, selector, cmp);
}



/*[[[head:libc_alphasortk,hash:CRC-32=0x9a080a7d]]]*/
/* >> alphasort(3), alphasort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strcmp(3)' would */
INTERN ATTR_SECTION(".text.crt.fs.dir") ATTR_PURE ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_alphasortk)(struct dirent const **e1,
                                      struct dirent const **e2)
/*[[[body:libc_alphasortk]]]*/
/*AUTO*/{
	return strcoll((*e1)->d_name, (*e2)->d_name);
}
/*[[[end:libc_alphasortk]]]*/

/*[[[head:libc_alphasortk64,hash:CRC-32=0x806f4afd]]]*/
#ifdef _DIRENT_MATCHES_DIRENT64
DEFINE_INTERN_ALIAS(libc_alphasortk64, libc_alphasortk);
#else /* MAGIC:alias */
/* >> alphasort(3), alphasort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strcmp(3)' would */
INTERN ATTR_SECTION(".text.crt.fs.dir") ATTR_PURE ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_alphasortk64)(struct dirent64 const **e1,
                                        struct dirent64 const **e2)
/*[[[body:libc_alphasortk64]]]*/
/*AUTO*/{
	return strcoll((*e1)->d_name, (*e2)->d_name);
}
#endif /* MAGIC:alias */
/*[[[end:libc_alphasortk64]]]*/

/*[[[head:libc_versionsortk,hash:CRC-32=0x542e42ea]]]*/
/* >> versionsort(3), versionsort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strvercmp(3)' would. */
INTERN ATTR_SECTION(".text.crt.fs.dir") ATTR_PURE ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_versionsortk)(struct dirent const **e1,
                                        struct dirent const **e2)
/*[[[body:libc_versionsortk]]]*/
/*AUTO*/{
	return strverscmp((*e1)->d_name, (*e2)->d_name);
}
/*[[[end:libc_versionsortk]]]*/

/*[[[head:libc_versionsortk64,hash:CRC-32=0x7589c6d0]]]*/
#ifdef _DIRENT_MATCHES_DIRENT64
DEFINE_INTERN_ALIAS(libc_versionsortk64, libc_versionsortk);
#else /* MAGIC:alias */
/* >> versionsort(3), versionsort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strvercmp(3)' would. */
INTERN ATTR_SECTION(".text.crt.fs.dir") ATTR_PURE ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_versionsortk64)(struct dirent64 const **e1,
                                          struct dirent64 const **e2)
/*[[[body:libc_versionsortk64]]]*/
/*AUTO*/{
	return strverscmp((*e1)->d_name, (*e2)->d_name);
}
#endif /* MAGIC:alias */
/*[[[end:libc_versionsortk64]]]*/


static_assert(offsetof(struct glibc_dirent64, d_name) != offsetof(struct dirent64, d_name),
              "If this fails, then there is either ");
INTERN ATTR_SECTION(".text.crt.fs.dir") ATTR_PURE NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_alphasort64)(struct glibc_dirent64 const **e1,
                                       struct glibc_dirent64 const **e2) {
	return strcoll((*e1)->d_name, (*e2)->d_name);
}
INTERN ATTR_SECTION(".text.crt.fs.dir") ATTR_PURE NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_versionsort64)(struct glibc_dirent64 const **e1,
                                         struct glibc_dirent64 const **e2) {
	return strverscmp((*e1)->d_name, (*e2)->d_name);
}



/* Export compatibility mode symbols. */
#ifdef SIZEOF_GLIBC_DIRENT32_MATCHES_KOS_DIRENT
DEFINE_PUBLIC_ALIAS(__libc_readdir, libc_readdir);
DEFINE_PUBLIC_ALIAS(__libc_readdir_r, libc_readdir_r);
DEFINE_PUBLIC_ALIAS(readdir, libc_readdir);
DEFINE_PUBLIC_ALIAS(readdir_r, libc_readdir_r);
DEFINE_PUBLIC_ALIAS(scandir, libc_scandir);
DEFINE_PUBLIC_ALIAS(scandirat, libc_scandirat);
DEFINE_PUBLIC_ALIAS(alphasort, libc_alphasortk);
DEFINE_PUBLIC_ALIAS(versionsort, libc_versionsortk);
#elif defined(SIZEOF_GLIBC_DIRENT32_MATCHES_GLIBC_DIRENT64)
DEFINE_PUBLIC_IFUNC(__libc_readdir, libc_get_readdir64);
DEFINE_PUBLIC_IFUNC(__libc_readdir_r, libc_get_readdir64_r);
DEFINE_PUBLIC_IFUNC(readdir, libc_get_readdir64);
DEFINE_PUBLIC_IFUNC(readdir_r, libc_get_readdir64_r);
DEFINE_PUBLIC_IFUNC(scandir, libc_get_scandir64);
DEFINE_PUBLIC_IFUNC(scandirat, libc_get_scandirat64);
DEFINE_PUBLIC_IFUNC(alphasort, libc_get_alphasort64);
DEFINE_PUBLIC_IFUNC(versionsort, libc_get_versionsort64);
#else /* ... */
#error "Invalid configuration"
#endif /* !... */

PRIVATE ATTR_SECTION(".text.crt.compat.linux.dirent") void
NOTHROW(LIBCCALL enable_glibc_dirent64_compat)(void) {
	static_assert((offsetof(struct glibc_dirent64, d_name) -
	               offsetof(struct dirent, d_name)) == 8);
	dirbuf_compat_offset = offsetof(struct glibc_dirent64, d_name) -
	                       offsetof(struct dirent, d_name);
}

/* Use indirect functions to auto-enable compat support
 * in  the  event that  relevant symbols  are imported. */
DEFINE_PUBLIC_IFUNC(readdir64, libc_get_readdir64);
DEFINE_PUBLIC_IFUNC(readdir64_r, libc_get_readdir64_r);
DEFINE_PUBLIC_IFUNC(scandir64, libc_get_scandir64);
DEFINE_PUBLIC_IFUNC(scandirat64, libc_get_scandirat64);
DEFINE_PUBLIC_IFUNC(alphasort64, libc_get_alphasort64);
DEFINE_PUBLIC_IFUNC(versionsort64, libc_get_versionsort64);
INTERN ATTR_SECTION(".text.crt.compat.linux.dirent") void *
NOTHROW(LIBCCALL libc_get_readdir64)(void) {
	enable_glibc_dirent64_compat();
	return (void *)&libc_readdir64;
}

INTERN ATTR_SECTION(".text.crt.compat.linux.dirent") void *
NOTHROW(LIBCCALL libc_get_readdir64_r)(void) {
	enable_glibc_dirent64_compat();
	return (void *)&libc_readdir64_r;
}

INTERN ATTR_SECTION(".text.crt.compat.linux.dirent") void *
NOTHROW(LIBCCALL libc_get_scandir64)(void) {
	enable_glibc_dirent64_compat();
	return (void *)&libc_scandir64;
}

INTERN ATTR_SECTION(".text.crt.compat.linux.dirent") void *
NOTHROW(LIBCCALL libc_get_scandirat64)(void) {
	enable_glibc_dirent64_compat();
	return (void *)&libc_scandirat64;
}

INTERN ATTR_SECTION(".text.crt.compat.linux.dirent") void *
NOTHROW(LIBCCALL libc_get_alphasort64)(void) {
	enable_glibc_dirent64_compat();
	return (void *)&libc_alphasort64;
}

INTERN ATTR_SECTION(".text.crt.compat.linux.dirent") void *
NOTHROW(LIBCCALL libc_get_versionsort64)(void) {
	enable_glibc_dirent64_compat();
	return (void *)&libc_versionsort64;
}





/*[[[start:exports,hash:CRC-32=0xba18a3a9]]]*/
DEFINE_PUBLIC_ALIAS(DOS$__libc_opendir, libd_opendir);
DEFINE_PUBLIC_ALIAS(DOS$opendir, libd_opendir);
DEFINE_PUBLIC_ALIAS(__libc_opendir, libc_opendir);
DEFINE_PUBLIC_ALIAS(opendir, libc_opendir);
DEFINE_PUBLIC_ALIAS(DOS$fopendirat, libd_fopendirat);
DEFINE_PUBLIC_ALIAS(fopendirat, libc_fopendirat);
DEFINE_PUBLIC_ALIAS(DOS$opendirat, libd_opendirat);
DEFINE_PUBLIC_ALIAS(opendirat, libc_opendirat);
DEFINE_PUBLIC_ALIAS(__libc_closedir, libc_closedir);
DEFINE_PUBLIC_ALIAS(closedir, libc_closedir);
DEFINE_PUBLIC_ALIAS(fdclosedir, libc_fdclosedir);
DEFINE_PUBLIC_ALIAS(readdirk, libc_readdirk);
DEFINE_PUBLIC_ALIAS(__libc_rewinddir, libc_rewinddir);
DEFINE_PUBLIC_ALIAS(rewinddir, libc_rewinddir);
DEFINE_PUBLIC_ALIAS(fdopendir, libc_fdopendir);
DEFINE_PUBLIC_ALIAS(readdirk64, libc_readdirk64);
DEFINE_PUBLIC_ALIAS(readdirk_r, libc_readdirk_r);
DEFINE_PUBLIC_ALIAS(readdirk64_r, libc_readdirk64_r);
DEFINE_PUBLIC_ALIAS(__libc_seekdir, libc_seekdir);
DEFINE_PUBLIC_ALIAS(seekdir, libc_seekdir);
DEFINE_PUBLIC_ALIAS(__libc_telldir, libc_telldir);
DEFINE_PUBLIC_ALIAS(telldir, libc_telldir);
DEFINE_PUBLIC_ALIAS(dirfd, libc_dirfd);
DEFINE_PUBLIC_ALIAS(scandirk, libc_scandirk);
DEFINE_PUBLIC_ALIAS(alphasortk, libc_alphasortk);
DEFINE_PUBLIC_ALIAS(alphasortk64, libc_alphasortk64);
DEFINE_PUBLIC_ALIAS(scandiratk, libc_scandiratk);
DEFINE_PUBLIC_ALIAS(scandirk64, libc_scandirk64);
DEFINE_PUBLIC_ALIAS(scandiratk64, libc_scandiratk64);
DEFINE_PUBLIC_ALIAS(__getdirentries, libc_getdirentries);
DEFINE_PUBLIC_ALIAS(__libc_getdirentries, libc_getdirentries);
DEFINE_PUBLIC_ALIAS(getdirentries, libc_getdirentries);
DEFINE_PUBLIC_ALIAS(getdirentries64, libc_getdirentries64);
DEFINE_PUBLIC_ALIAS(versionsortk, libc_versionsortk);
DEFINE_PUBLIC_ALIAS(versionsortk64, libc_versionsortk64);
DEFINE_PUBLIC_ALIAS(kreaddir, libc_kreaddir);
DEFINE_PUBLIC_ALIAS(kreaddirf, libc_kreaddirf);
DEFINE_PUBLIC_ALIAS(kreaddir64, libc_kreaddir64);
DEFINE_PUBLIC_ALIAS(kreaddirf64, libc_kreaddirf64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_DIRENT_C */
