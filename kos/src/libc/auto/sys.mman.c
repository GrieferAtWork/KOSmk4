/* HASH CRC-32:0xff6504c9 */
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
#ifndef GUARD_LIBC_AUTO_SYS_MMAN_C
#define GUARD_LIBC_AUTO_SYS_MMAN_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/sys.mman.h"
#include "../user/fcntl.h"
#include "../user/stdlib.h"
#include "string.h"
#include "../user/sys.stat.h"
#include "../user/unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <asm/os/paths.h>
#include <asm/os/oflags.h>
#include <parts/malloca.h>
#include <libc/errno.h>
#include <bits/types.h>
/* >> shm_open(3) */
INTERN ATTR_SECTION(".text.crt.system.mman") NONNULL((1)) fd_t
NOTHROW_RPC(LIBCCALL libc_shm_open)(char const *name,
                                    oflag_t oflags,
                                    mode_t mode) {
	fd_t result;
	char *fullname;
	size_t namelen;

	if (oflags & O_DOSPATH) {
		while (*name == '/' || *name == '\\')
			++name;
	} else {
		while (*name == '/')
			++name;
	}







	namelen  = libc_strlen(name);
	fullname = (char *)__malloca((__COMPILER_STRLEN(__PATH_SHM) + 1 +
	                              namelen + 1) *
	                             sizeof(char));
	if unlikely(!fullname)
		return -1;
	libc_memcpy(libc_mempcpy(fullname, __PATH_SHM "/",
	               (__COMPILER_STRLEN(__PATH_SHM) + 1) *
	               sizeof(char)),
	       fullname,
	       (namelen + 1) *
	       sizeof(char));
	result = libc_open(fullname, oflags, mode);

	if (result < 0 && (oflags & O_CREAT) != 0 && __libc_geterrno_or(ENOENT) == ENOENT) {
		/* Lazily create the SHM directory (/dev/shm), if it hadn't been created already.
		 * XXX:   This    assumes    that    `headof(__PATH_SHM)'    already    exists... */
		libc_mkdir(__PATH_SHM, 0777);
		result = libc_open(fullname, oflags, mode);
	}

	__freea(fullname);
	return result;
}
#include <asm/os/paths.h>
#include <hybrid/typecore.h>
#include <parts/malloca.h>
/* >> shm_unlink(3) */
INTERN ATTR_SECTION(".text.crt.system.mman") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_shm_unlink)(char const *name) {
	int result;
	char *fullname;
	size_t namelen;




	while (*name == '/')
		++name;

	namelen  = libc_strlen(name);
	fullname = (char *)__malloca((__COMPILER_STRLEN(__PATH_SHM) + 1 +
	                              namelen + 1) *
	                             sizeof(char));
	if unlikely(!fullname)
		return -1;
	libc_memcpy(libc_mempcpy(fullname, __PATH_SHM "/",
	               (__COMPILER_STRLEN(__PATH_SHM) + 1) *
	               sizeof(char)),
	       fullname,
	       (namelen + 1) *
	       sizeof(char));
	result = libc_unlink(fullname);
	__freea(fullname);
	return result;
}
#endif /* !__KERNEL__ */
#include <asm/pkey.h>
#if !defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY)
#include <libc/errno.h>
/* >> pkey_set(3) */
INTERN ATTR_SECTION(".text.crt.system.mman") int
NOTHROW_NCX(LIBCCALL libc_pkey_set)(int pkey,
                                    unsigned int access_rights) {
	if unlikely(!__arch_pkey_verify_key(pkey) ||
	            !__arch_pkey_verify_rights(access_rights))
		goto badkey_or_rights;
	__arch_pkey_set(pkey, access_rights);
	return 0;
badkey_or_rights:

	return libc_seterrno(EINVAL);



}
#include <libc/errno.h>
/* >> pkey_get(3) */
INTERN ATTR_SECTION(".text.crt.system.mman") int
NOTHROW_NCX(LIBCCALL libc_pkey_get)(int pkey) {
	if unlikely(!__arch_pkey_verify_key(pkey))
		goto badkey;
	return __arch_pkey_get(pkey);
badkey:

	return libc_seterrno(EINVAL);



}
#endif /* !__KERNEL__ && __ARCH_HAVE_PKEY */
#ifndef __KERNEL__
#include <bits/os/stat.h>
#include <bits/crt/mapfile.h>
#include <asm/os/mman.h>
#include <libc/errno.h>
#include <asm/os/stdio.h>
/* >> fmapfile(3)
 * A helper function that can be used to map a specific sub-range of a given file into memory.
 * This  function  tries  the   following  (in  order)  in   order  to  create  the   mapping:
 *  - mmap(2):                        If `fd' can be mmap'd, then that is how the mapping is created
 *  - malloc(3) + pread(2):           If `fd' supports pread(2), use that to fill a buffer
 *  - malloc(3) + lseek(2) + read(2): For a non-zero offset, try to use lseek(2) to move to `offset'
 *  - malloc(3) + read(2):            When lseek(2) returns an error, use read(2) to skip `offset',
 *                                    after which  up  to  `max_bytes'  bytes  are  read  normally.
 * Upon success (return == 0), the given `mapping' must be deleted using `unmapfile(3)'
 * @param: fd:        The  file that should be loaded into memory.  Upon entry to this function it is
 *                    assumed that the file position of `fd' is `0'. If it isn't, then incorrect data
 *                    may be mapped. Upon return, the file position of `fd' is undefined.
 * @param: mapping:   Filled with mapping information. This structure contains at least 2 fields:
 *                     - mf_addr: Filled with the base address of a mapping of the file's contents
 *                     - mf_size: The actual number of mapped bytes (excluding `num_trailing_nulbytes')
 *                     - Other fields are implementation-specific
 *                    Note that the memory located as `mapping->mf_addr' is writable, though changes  to
 *                    it are guarantied not to be written back to `fd'. iow: it behaves like MAP_PRIVATE
 *                    mapped as PROT_READ|PROT_WRITE.
 * @param: offset:    File offset / number of leading bytes that should not be mapped
 * @param: max_bytes: The  max number of bytes (excluding num_trailing_nulbytes) that should be mapped
 *                    starting at `offset'. If the file is  smaller than this, or indicate EOF  before
 *                    this number of bytes has been reached, simply stop there. - The actual number of
 *                    mapped bytes is returned in `mapping->mf_size'.
 * @param: num_trailing_nulbytes: When non-zero, append this many trailing NUL-bytes at the end of the
 *                    mapping. More bytes than this may be appened if necessary, but at least this many
 *                    are guarantied to be. - Useful if you want  to load a file as a string, in  which
 *                    case you can specify `1' to always have a trailing '\0' be appended.
 * @return: 0 : Success (the given `mapping' must be deleted using `unmapfile(3)')
 * @return: -1: [errno=EPERM]  `fd' doesn't support read(2)ing
 * @return: -1: [errno=ENOMEM] Out of memory
 * @return: -1: [errno=EBADF]  Invalid `fd'
 * @return: -1: [errno=*]      Read error */
INTERN ATTR_SECTION(".text.crt.system.mman") WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_fmapfile)(struct mapfile *__restrict mapping,
                                    fd_t fd,
                                    pos64_t offset,
                                    size_t max_bytes,
                                    size_t num_trailing_nulbytes) {
	byte_t *buf;
	size_t bufsize;
	size_t bufused;
	size_t buffree;

	/* Try to use mmap(2) */
#if defined(__PROT_READ) && defined(__PROT_WRITE) && defined(__MAP_PRIVATE)
	struct stat64 st;
	if (fstat64(fd, &st) == 0) {

		errno_t saved_errno = __libc_geterrno();

		pos64_t map_offset = offset;
		size_t  map_bytes  = max_bytes;
		if (map_offset > (size_t)st.st_size) {
			map_offset = 0;
			map_bytes  = 0;
		}
		if (map_bytes > (size_t)(st.st_size - map_offset))
			map_bytes = (size_t)(st.st_size - map_offset);
		if (map_bytes) {
			/* Map file into memory. */
			size_t mapsize = map_bytes + num_trailing_nulbytes;
			buf = (byte_t *)libc_mmap64(NULL, mapsize,
			                       __PROT_READ | __PROT_WRITE,
			                       __MAP_PRIVATE, fd, (__PIO_OFFSET64)offset);
			if (buf != (byte_t *)__MAP_FAILED) {
				/* Clear out the caller-required trailing NUL bytes.
				 * We  do this in a kind-of special was that try not
				 * to write-fault memory if it already contains NULs */
				byte_t *nul = buf + map_bytes;
				while (num_trailing_nulbytes) {
					if (*nul) {
						libc_bzero(nul, num_trailing_nulbytes);
						break;
					}
					--num_trailing_nulbytes;
					++nul;
				}
				mapping->mf_addr = buf;
				mapping->mf_size = map_bytes;
				mapping->__mf_mapsize = mapsize;
				return 0;
			}

			__libc_seterrno(saved_errno);

		} else {
			/* Special files from procfs indicate their size as `0',  even
			 * though they aren't actually empty. - As such, we can't just
			 * use the normal approach of read(2)-ing the file.
			 *
			 * Only if at that point it still indicates being empty, are we
			 * actually allowed to believe that claim! */
		}
	}
#endif /* __PROT_READ && __PROT_WRITE && __MAP_PRIVATE */

	/* Allocate a heap buffer. */
	bufsize = max_bytes;
	if (bufsize > 0x10000)
		bufsize = 0x10000;
	buf = (byte_t *)libc_malloc(bufsize + num_trailing_nulbytes);
	if unlikely(!buf) {
		bufsize = 1;
		buf = (byte_t *)libc_malloc(bufsize + num_trailing_nulbytes);
		if unlikely(!buf)
			return -1;
	}
	bufused = 0;
	buffree = bufsize;

	if (offset != 0) {
		/* Try to use pread(2) */

		for (;;) {
			ssize_t error;
			error = libc_pread64(fd, buf + bufused, buffree, offset);
			if ((size_t)error != buffree) {
				if (error >= 0) {
					/* End-of-file! */
					byte_t *newbuf;
					bufused += (size_t)error;
					newbuf = (byte_t *)libc_realloc(buf, bufused + num_trailing_nulbytes);
					if likely(newbuf)
						buf = newbuf;
					libc_bzero(buf + bufused, num_trailing_nulbytes); /* Trailing NUL-bytes */
					mapping->mf_addr = buf;
					mapping->mf_size = bufused;
					mapping->__mf_mapsize = 0;
					return 0;
				}
				if (bufused == 0)
					break; /* File probably doesn't support `pread(2)'... */
				/* Read error */
				goto err_buf;
			}
			offset  += (size_t)error;
			bufused += (size_t)error;
			buffree -= (size_t)error;
			if (buffree < 1024) {
				byte_t *newbuf;
				size_t newsize = bufsize * 2;
				newbuf = (byte_t *)libc_realloc(buf, newsize + num_trailing_nulbytes);
				if (!newbuf) {
					newsize = bufsize + 1024;
					newbuf = (byte_t *)libc_realloc(buf, newsize + num_trailing_nulbytes);
					if (!newbuf) {
						if (!buffree)
							goto err_buf;
						newsize = bufsize;
						newbuf  = buf;
					}
				}
				buffree += newsize - bufsize;
				bufsize = newsize;
				buf     = newbuf;
			}
		}


		/* For a non-zero offset, try to use lseek() (or read()) */
#ifdef __SEEK_SET
		if (libc_lseek64(fd, (off64_t)offset, __SEEK_SET) != -1) {
			/* Was able to lseek(2) */
		} else
#endif /* __SEEK_SET */
		{
			/* Try to use read(2) to skip leading data. */
			while (offset) {
				ssize_t error;
				size_t skip = bufsize + num_trailing_nulbytes;
				if ((pos64_t)skip > offset)
					skip = (size_t)offset;
				error = libc_read(fd, buf, skip);
				if (error < (ssize_t)skip) {
					if (error < 0)
						goto err_buf;
					goto empty_file; /* EOF reached before `offset' */
				}
				offset -= error;
			}
		}
	}

	/* Use read(2) as fallback */
	for (;;) {
		ssize_t error;
		error = libc_read(fd, buf + bufused, buffree);
		if ((size_t)error != buffree) {
			if (error >= 0) {
				/* End-of-file! */
				byte_t *newbuf;
				bufused += (size_t)error;
				newbuf = (byte_t *)libc_realloc(buf, bufused + num_trailing_nulbytes);
				if likely(newbuf)
					buf = newbuf;
				libc_bzero(buf + bufused, num_trailing_nulbytes); /* Trailing NUL-bytes */
				mapping->mf_addr = buf;
				mapping->mf_size = bufused;
				mapping->__mf_mapsize = 0;
				return 0;
			}
			/* Read error */
			goto err_buf;
		}
		bufused += (size_t)error;
		buffree -= (size_t)error;
		if (buffree < 1024) {
			byte_t *newbuf;
			size_t newsize = bufsize * 2;
			newbuf = (byte_t *)libc_realloc(buf, newsize + num_trailing_nulbytes);
			if (!newbuf) {
				newsize = bufsize + 1024;
				newbuf = (byte_t *)libc_realloc(buf, newsize + num_trailing_nulbytes);
				if (!newbuf) {
					if (!buffree)
						goto err_buf;
					newsize = bufsize;
					newbuf  = buf;
				}
			}
			buffree += newsize - bufsize;
			bufsize = newsize;
			buf     = newbuf;
		}
	}

empty_file:
	{
		byte_t *newbuf;
		newbuf = (byte_t *)libc_calloc(1, num_trailing_nulbytes);
		if likely(newbuf) {

			libc_free(buf);

		} else {
			newbuf = (byte_t *)libc_realloc(buf, num_trailing_nulbytes);
			if (!newbuf)
				newbuf = buf;
			libc_bzero(newbuf, num_trailing_nulbytes);
		}
		mapping->mf_addr = newbuf;
		mapping->mf_size = 0;
		mapping->__mf_mapsize = 0;
	}
	return 0;
err_buf:

	libc_free(buf);

	return -1;
}
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#include <libc/errno.h>
/* >> fmapfileat(3)
 * Map the specified `filename' into memory. s.a. `fmapfile(3)'
 * @param: atflags: Set of `0 | AT_DOSPATH | AT_EMPTY_PATH' */
INTERN ATTR_SECTION(".text.crt.system.mman") WUNUSED NONNULL((1, 3)) int
NOTHROW_NCX(LIBCCALL libc_fmapfileat)(struct mapfile *__restrict mapping,
                                      fd_t dirfd,
                                      char const *filename,
                                      pos64_t offset,
                                      size_t max_bytes,
                                      size_t num_trailing_nulbytes,
                                      atflag_t atflags) {
	fd_t fd;
	int result;

	oflag_t oflags = __O_RDONLY | __O_CLOEXEC | __O_CLOFORK;








	if (atflags & __AT_DOSPATH) {
		oflags |= __O_DOSPATH;
		atflags &= ~__AT_DOSPATH;
	}


	if (atflags & __AT_EMPTY_PATH) {
		if (!*filename)
			return libc_fmapfile(mapping, dirfd, offset, max_bytes, num_trailing_nulbytes);
		atflags &= ~__AT_EMPTY_PATH;
	}

	if unlikely(atflags != 0) {

		return libc_seterrno(EINVAL);



	}
	fd = libc_openat(dirfd, filename, oflags);
	if unlikely(fd < 0)
		return -1;
	result = libc_fmapfile(mapping, fd, offset, max_bytes, num_trailing_nulbytes);

	libc_close(fd);

	return result;
}
/* >> mapfile(3)
 * Map the specified `filename' into memory. s.a. `fmapfile(3)' */
INTERN ATTR_SECTION(".text.crt.system.mman") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc_mapfile)(struct mapfile *__restrict mapping,
                                   char const *filename,
                                   pos64_t offset,
                                   size_t max_bytes,
                                   size_t num_trailing_nulbytes) {

	return libc_fmapfileat(mapping, __AT_FDCWD, filename, offset, max_bytes, num_trailing_nulbytes, 0);


















}
/* >> unmapfile(3)
 * Delete a file mapping previously created by `mapfile(3)' */
INTERN ATTR_SECTION(".text.crt.system.mman") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_unmapfile)(struct mapfile *__restrict mapping) {
	if (mapping->__mf_mapsize) {

		return libc_munmap(mapping->mf_addr, mapping->__mf_mapsize);

	} else {
		libc_free(mapping->mf_addr);
	}
	return 0;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(shm_open, libc_shm_open);
DEFINE_PUBLIC_ALIAS(shm_unlink, libc_shm_unlink);
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY)
DEFINE_PUBLIC_ALIAS(pkey_set, libc_pkey_set);
DEFINE_PUBLIC_ALIAS(pkey_get, libc_pkey_get);
#endif /* !__KERNEL__ && __ARCH_HAVE_PKEY */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(fmapfile, libc_fmapfile);
DEFINE_PUBLIC_ALIAS(fmapfileat, libc_fmapfileat);
DEFINE_PUBLIC_ALIAS(mapfile, libc_mapfile);
DEFINE_PUBLIC_ALIAS(unmapfile, libc_unmapfile);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_SYS_MMAN_C */
