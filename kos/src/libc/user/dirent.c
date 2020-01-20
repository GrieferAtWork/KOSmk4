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
#ifndef GUARD_LIBC_USER_DIRENT_C
#define GUARD_LIBC_USER_DIRENT_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include <fcntl.h>
#include <malloc.h>
#include <stdlib.h>
#include <syscall.h>
#include <unistd.h>

#include "dirent.h"

DECL_BEGIN


struct __dirstream {
	int            ds_fd;      /* [const][owned] The handle for the underlying file stream object. */
	size_t         ds_lodsize; /* Amount of bytes returned by the `xreaddir()' system call during its last invocation. */
	size_t         ds_bufsize; /* Size of the directory stream buffer (`ds_buf') in bytes. */
	struct dirent *ds_next;    /* [1..1][in(ds_buf)] Pointer to the next directory yet to-be read. */
	struct dirent *ds_buf;     /* [1..ds_bufsize][owned_if(!= ds_sbuf)] Directory entry buffer. */
	byte_t         ds_sbuf[offsetof(struct dirent, d_name) + 512]; /* Pre-allocated static dirent buffer.
	                                                                * NOTE: When a dynamic buffer has to be used,
	                                                                *      `realloc_in_place()' is used to attempt
	                                                                *       to free this buffer. */
};

#define dirstream_init(self, fd)                            \
	((self)->ds_fd      = fd,                               \
	 (self)->ds_lodsize = 0,                                \
	 (self)->ds_bufsize = sizeof((self)->ds_sbuf),          \
	 (self)->ds_next    = (struct dirent *)(self)->ds_sbuf, \
	 (self)->ds_buf     = (struct dirent *)(self)->ds_sbuf)
#define dirstream_fini_keepfd(self)                       \
	(((self)->ds_buf != (struct dirent *)(self)->ds_sbuf) \
	 ? free((self)->ds_buf)                               \
	 : (void)0)
#define dirstream_fini(self)      \
	(dirstream_fini_keepfd(self), \
	 sys_close((self)->ds_fd))



/*[[[start:implementation]]]*/

/*[[[head:opendir,hash:CRC-32=0x18bfb71c]]]*/
/* Open and return a new directory stream for reading, referring to `name' */
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.dir.opendir") DIR *
NOTHROW_RPC(LIBCCALL libc_opendir)(char const *name)
/*[[[body:opendir]]]*/
{
	DIR *result;
	fd_t fd = open(name, O_RDONLY | O_DIRECTORY);
	if unlikely(fd < 0)
		goto err;
	result = fdopendir(fd);
	if unlikely(!result)
		sys_close(fd);
	return result;
err:
	return NULL;
}
/*[[[end:opendir]]]*/

/*[[[head:fopendirat,hash:CRC-32=0xfc4ad71]]]*/
/* Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
INTERN WUNUSED NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.dir.fopendirat") DIR *
NOTHROW_RPC(LIBCCALL libc_fopendirat)(fd_t dirfd,
                                      char const *name,
                                      oflag_t oflags)
/*[[[body:fopendirat]]]*/
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
/*[[[end:fopendirat]]]*/

/*[[[head:opendirat,hash:CRC-32=0xde3f20f5]]]*/
/* Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
INTERN WUNUSED NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.dir.opendirat") DIR *
NOTHROW_RPC(LIBCCALL libc_opendirat)(fd_t dirfd,
                                     char const *name)
/*[[[body:opendirat]]]*/
{
	return fopendirat(dirfd,
	                  name,
	                  O_RDONLY | O_DIRECTORY);
}
/*[[[end:opendirat]]]*/

/*[[[head:closedir,hash:CRC-32=0xce4b29d0]]]*/
/* Close a directory stream previously returned by `opendir(3)' and friends */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.dir.closedir") int
NOTHROW_NCX(LIBCCALL libc_closedir)(DIR *dirp)
/*[[[body:closedir]]]*/
{
	if unlikely(!dirp)
		goto err_null;
	dirstream_fini(dirp);
	free(dirp);
	return 0;
err_null:
	return (int)libc_seterrno(EINVAL);
}
/*[[[end:closedir]]]*/

/*[[[head:fdclosedir,hash:CRC-32=0x71604758]]]*/
/* Same as `closedir()', but instead of closing the underlying file descriptor, return it */
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.dir.fdclosedir") fd_t
NOTHROW_NCX(LIBCCALL libc_fdclosedir)(DIR *dirp)
/*[[[body:fdclosedir]]]*/
{
	fd_t result;
	if unlikely(!dirp)
		goto err_null;
	result = dirp->ds_fd;
	dirstream_fini_keepfd(dirp);
	free(dirp);
	return result;
err_null:
	return (fd_t)libc_seterrno(EINVAL);
}
/*[[[end:fdclosedir]]]*/

/*[[[head:rewinddir,hash:CRC-32=0xcdb2c099]]]*/
/* Rewind the given directory stream in such a way that the next call
 * to `readdir(3)' will once again return the first directory entry */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.dir.rewinddir") void
NOTHROW_NCX(LIBCCALL libc_rewinddir)(DIR *__restrict dirp)
/*[[[body:rewinddir]]]*/
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
#else
#error "No suitable sys_lseek() function"
#endif
		dirp->ds_lodsize = 0;
	}
}
/*[[[end:rewinddir]]]*/

/*[[[head:fdopendir,hash:CRC-32=0x2e2ba4d3]]]*/
/* Create a new directory stream by inheriting the given `FD' as stream handle */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.fs.dir.fdopendir") DIR *
NOTHROW_NCX(LIBCCALL libc_fdopendir)(fd_t fd)
/*[[[body:fdopendir]]]*/
{
	DIR *result = (DIR *)malloc(sizeof(DIR));
	if unlikely(!result)
		goto done;
	dirstream_init(result, fd);
done:
	return result;
}
/*[[[end:fdopendir]]]*/

/*[[[head:seekdir,hash:CRC-32=0x31f23e16]]]*/
/* Get the directory stream position */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.dir.seekdir") void
NOTHROW_NCX(LIBCCALL libc_seekdir)(DIR *__restrict dirp,
                                   long int pos)
/*[[[body:seekdir]]]*/
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
#else
#error "No suitable sys_lseek() function"
#endif
	}
}
/*[[[end:seekdir]]]*/

/*[[[head:telldir,hash:CRC-32=0x17cc87aa]]]*/
/* Get the directory stream position */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.dir.telldir") long int
NOTHROW_NCX(LIBCCALL libc_telldir)(DIR *__restrict dirp)
/*[[[body:telldir]]]*/
{
	if unlikely(!dirp)
		goto err_null;
	/* XXX: Adjust for unread, but pre-cached directory entries? */
#if __SIZEOF_LONG__ == 4
	return (long int)lseek(dirp->ds_fd, 0, SEEK_CUR);
#else
	return (long int)lseek64(dirp->ds_fd, 0, SEEK_CUR);
#endif
err_null:
	libc_seterrno(EINVAL);
	return -1;
}
/*[[[end:telldir]]]*/

/*[[[head:dirfd,hash:CRC-32=0xa79788a]]]*/
/* Return the underlying file descriptor of the given directory stream */
INTERN ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.dir.dirfd") fd_t
NOTHROW_NCX(LIBCCALL libc_dirfd)(DIR __KOS_FIXED_CONST *__restrict dirp)
/*[[[body:dirfd]]]*/
{
	return dirp->ds_fd;
}
/*[[[end:dirfd]]]*/

/*[[[head:readdir,hash:CRC-32=0x60024c5a]]]*/
/* Read and return the next pending directory entry of the given directory stream `DIRP'
 * @EXCEPT: Returns NULL for end-of-directory; throws an error if something else went wrong */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.dir.readdir") struct dirent *
NOTHROW_RPC(LIBCCALL libc_readdir)(DIR *__restrict dirp)
/*[[[body:readdir]]]*/
{
	struct dirent *result;
	ssize_t load_size;
	if unlikely(!dirp)
		goto err_null;
again:
	result = dirp->ds_next;
	/* Check if there the pre-loaded next-pointer is valid. */
	if (READDIR_MULTIPLE_ISVALID(result, dirp->ds_buf, dirp->ds_lodsize)) {
		if (READDIR_MULTIPLE_ISEOF(result))
			return NULL; /* End of directory */
		dirp->ds_next = READDIR_MULTIPLE_GETNEXT(result);
		return result;
	}
	/* Read more entires. */
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
		/* Buffer is too small. -> Must allocate one that is larger. */
		if (dirp->ds_buf == (struct dirent *)dirp->ds_sbuf) {
			/* Free the static buffer. */
			realloc_in_place(dirp, offsetof(DIR, ds_sbuf));
			dirp->ds_buf = NULL;
		}
		new_bufsize = load_size << 1;
		if unlikely(new_bufsize < (size_t)load_size)
			new_bufsize = (size_t)load_size;
		new_buffer  = (struct dirent *)realloc(dirp->ds_buf, new_bufsize);
		if unlikely(!new_buffer) {
			new_bufsize = (size_t)load_size;
			new_buffer  = (struct dirent *)realloc(dirp->ds_buf, new_bufsize);
			if unlikely(!new_buffer)
				return NULL;
		}
		/* Install the new buffer. */
		dirp->ds_buf     = new_buffer;
		dirp->ds_bufsize = new_bufsize;
	}
	dirp->ds_next    = dirp->ds_buf;
	dirp->ds_lodsize = (size_t)load_size;
	goto again;
err_null:
	libc_seterrno(EINVAL);
	return NULL;
}
/*[[[end:readdir]]]*/

/*[[[impl:readdir64]]]*/
DEFINE_INTERN_WEAK_ALIAS(libc_readdir64,libc_readdir);

/*[[[head:readdir_r,hash:CRC-32=0x898461b5]]]*/
/* Reentrant version of `readdir(3)' (Using this is not recommended in KOS) */
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.dir.readdir_r") int
NOTHROW_RPC(LIBCCALL libc_readdir_r)(DIR *__restrict dirp,
                                     struct dirent *__restrict entry,
                                     struct dirent **__restrict result)
/*[[[body:readdir_r]]]*/
{
	(void)dirp;
	(void)entry;
	(void)result;
	CRT_UNIMPLEMENTED("readdir_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:readdir_r]]]*/

/*[[[head:readdir64_r,hash:CRC-32=0x6366cd63]]]*/
/* NOTE: This ~reentrant~ version of readdir() is strongly discouraged from being used in KOS, as the
 *       kernel does not impose a limit on the length of a single directory entry name (s.a. 'kreaddir')
 * >> Instead, simply use `readdir()' / `readdir64()', which will automatically (re-)allocate an internal,
 *    per-directory buffer of sufficient size to house any directory entry (s.a.: `READDIR_DEFAULT') */
#if defined(_DIRENT_MATCHES_DIRENT64)
DEFINE_INTERN_ALIAS(libc_readdir64_r, libc_readdir_r);
#else
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.dir.readdir64_r") int
NOTHROW_RPC(LIBCCALL libc_readdir64_r)(DIR *__restrict dirp,
                                       struct dirent64 *__restrict entry,
                                       struct dirent64 **__restrict result)
/*[[[body:readdir64_r]]]*/
{
	(void)dirp;
	(void)entry;
	(void)result;
	CRT_UNIMPLEMENTED("readdir64_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:readdir64_r]]]*/

/*[[[head:scandir,hash:CRC-32=0xde1a0c61]]]*/
/* Scan a directory `DIR' for all contained directory entries */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.dir.scandir") int
NOTHROW_RPC(LIBCCALL libc_scandir)(char const *__restrict dir,
                                   struct dirent ***__restrict namelist,
                                   __scandir_selector_t selector,
                                   __scandir_cmp_t cmp)
/*[[[body:scandir]]]*/
{
	(void)dir;
	(void)namelist;
	(void)selector;
	(void)cmp;
	CRT_UNIMPLEMENTED("scandir"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:scandir]]]*/

/*[[[head:scandirat,hash:CRC-32=0x287c1967]]]*/
/* Scan a directory `DIRFD:DIR' for all contained directory entries */
INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.dir.scandirat") int
NOTHROW_RPC(LIBCCALL libc_scandirat)(fd_t dirfd,
                                     char const *__restrict dir,
                                     struct dirent ***__restrict namelist,
                                     __scandir_selector_t selector,
                                     __scandir_cmp_t cmp)
/*[[[body:scandirat]]]*/
{
	(void)dirfd;
	(void)dir;
	(void)namelist;
	(void)selector;
	(void)cmp;
	CRT_UNIMPLEMENTED("scandirat"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:scandirat]]]*/

/*[[[impl:scandir64]]]*/
/*[[[impl:scandirat64]]]*/
DEFINE_INTERN_WEAK_ALIAS(libc_scandir64, libc_scandir);
DEFINE_INTERN_WEAK_ALIAS(libc_scandirat64, libc_scandirat);


/*[[[head:getdirentries,hash:CRC-32=0x2e0c7f33]]]*/
/* Linux's underlying system call for reading the entries of a directory */
INTERN NONNULL((2, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.dir.getdirentries") ssize_t
NOTHROW_RPC(LIBCCALL libc_getdirentries)(fd_t fd,
                                         char *__restrict buf,
                                         size_t nbytes,
                                         off_t *__restrict basep)
/*[[[body:getdirentries]]]*/
{
	ssize_t result;
	if unlikely(lseek(fd, *basep, SEEK_SET) < 0)
		goto err;
	result = kreaddir(fd, (struct dirent *)buf, nbytes, READDIR_MULTIPLE);
	if (result > 0)
		*basep += result;
	return result;
err:
	return -1;
}
/*[[[end:getdirentries]]]*/

/*[[[head:getdirentries64,hash:CRC-32=0x80f05f96]]]*/
/* 64-bit variant of `getdirentries()' */
#if defined(_DIRENT_MATCHES_DIRENT64)
DEFINE_INTERN_ALIAS(libc_getdirentries64, libc_getdirentries);
#else
INTERN NONNULL((2, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.dir.getdirentries64") ssize_t
NOTHROW_RPC(LIBCCALL libc_getdirentries64)(fd_t fd,
                                           char *__restrict buf,
                                           size_t nbytes,
                                           off64_t *__restrict basep)
/*[[[body:getdirentries64]]]*/
{
	ssize_t result;
	if unlikely(lseek64(fd, *basep, SEEK_SET) < 0)
		goto err;
	result = kreaddir(fd, (struct dirent *)buf, nbytes, READDIR_MULTIPLE);
	if (result > 0)
		*basep += result;
	return result;
err:
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:getdirentries64]]]*/

/*[[[impl:kreaddirf64]]]*/
/*[[[impl:kreaddir64]]]*/
DEFINE_INTERN_WEAK_ALIAS(libc_kreaddirf64, libc_kreaddirf);
DEFINE_INTERN_WEAK_ALIAS(libc_kreaddir64, libc_kreaddir);

/*[[[head:kreaddirf,hash:CRC-32=0xe7bd10f]]]*/
/* The KOS-specific system call for reading a single directory entry
 * from a file descriptor referring to an open directory stream.
 * @param: MODE: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When `READDIR_DEFAULT' was passed for `MODE', the directory
 *                    stream will only be advanced when this value is >= 'BUFSIZE'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.fs.dir.kreaddirf") ssize_t
NOTHROW_RPC(LIBCCALL libc_kreaddirf)(fd_t fd,
                                     struct dirent *buf,
                                     size_t bufsize,
                                     unsigned int mode,
                                     oflag_t flags)
/*[[[body:kreaddirf]]]*/
{
	ssize_t result;
	result = sys_kreaddirf(fd, buf, bufsize, mode, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:kreaddirf]]]*/

/*[[[head:kreaddir,hash:CRC-32=0x3da31234]]]*/
/* The KOS-specific system call for reading a single directory entry
 * from a file descriptor referring to an open directory stream.
 * @param: MODE: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When `READDIR_DEFAULT' was passed for `MODE', the directory
 *                    stream will only be advanced when this value is >= 'BUFSIZE'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.fs.dir.kreaddir") ssize_t
NOTHROW_RPC(LIBCCALL libc_kreaddir)(fd_t fd,
                                    struct dirent *buf,
                                    size_t bufsize,
                                    unsigned int mode)
/*[[[body:kreaddir]]]*/
{
	ssize_t result;
	result = sys_kreaddir(fd, buf, bufsize, mode);
	return libc_seterrno_syserr(result);
}
/*[[[end:kreaddir]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x4cb9453f]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(opendir, libc_opendir);
DEFINE_PUBLIC_WEAK_ALIAS(fopendirat, libc_fopendirat);
DEFINE_PUBLIC_WEAK_ALIAS(opendirat, libc_opendirat);
DEFINE_PUBLIC_WEAK_ALIAS(closedir, libc_closedir);
DEFINE_PUBLIC_WEAK_ALIAS(fdclosedir, libc_fdclosedir);
DEFINE_PUBLIC_WEAK_ALIAS(readdir, libc_readdir);
DEFINE_PUBLIC_WEAK_ALIAS(rewinddir, libc_rewinddir);
DEFINE_PUBLIC_WEAK_ALIAS(fdopendir, libc_fdopendir);
DEFINE_PUBLIC_WEAK_ALIAS(readdir64, libc_readdir64);
DEFINE_PUBLIC_WEAK_ALIAS(readdir_r, libc_readdir_r);
DEFINE_PUBLIC_WEAK_ALIAS(readdir64_r, libc_readdir64_r);
DEFINE_PUBLIC_WEAK_ALIAS(seekdir, libc_seekdir);
DEFINE_PUBLIC_WEAK_ALIAS(telldir, libc_telldir);
DEFINE_PUBLIC_WEAK_ALIAS(dirfd, libc_dirfd);
DEFINE_PUBLIC_WEAK_ALIAS(scandir, libc_scandir);
DEFINE_PUBLIC_WEAK_ALIAS(scandirat, libc_scandirat);
DEFINE_PUBLIC_WEAK_ALIAS(scandir64, libc_scandir64);
DEFINE_PUBLIC_WEAK_ALIAS(scandirat64, libc_scandirat64);
DEFINE_PUBLIC_WEAK_ALIAS(getdirentries, libc_getdirentries);
DEFINE_PUBLIC_WEAK_ALIAS(getdirentries64, libc_getdirentries64);
DEFINE_PUBLIC_WEAK_ALIAS(kreaddir, libc_kreaddir);
DEFINE_PUBLIC_WEAK_ALIAS(kreaddirf, libc_kreaddirf);
DEFINE_PUBLIC_WEAK_ALIAS(kreaddir64, libc_kreaddir64);
DEFINE_PUBLIC_WEAK_ALIAS(kreaddirf64, libc_kreaddirf64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_DIRENT_C */
