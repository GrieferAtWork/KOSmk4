/* HASH CRC-32:0xc8631e2f */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
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
/* Weird function that just returns "/dev/shm/" */
INTERN ATTR_SECTION(".text.crt.compat.glibc") const char *
NOTHROW_NCX(LIBCCALL libc___shm_directory)(size_t *len) {
	*len = COMPILER_STRLEN(__PATH_SHM "/");
	return __PATH_SHM "/";
}
#include <asm/os/paths.h>
#include <asm/os/oflags.h>
#include <parts/malloca.h>
#include <libc/errno.h>
#include <bits/types.h>
/* >> shm_open(3) */
INTERN ATTR_SECTION(".text.crt.system.mman") ATTR_IN(1) fd_t
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
INTERN ATTR_SECTION(".text.crt.system.mman") ATTR_IN(1) int
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
#include <asm/os/mman.h>
#include <libc/errno.h>
/* >> posix_madvise(3)
 * Wrapper around `madvise(2)'
 * @param: advice: One of `POSIX_MADV_*' */
INTERN ATTR_SECTION(".text.crt.system.mman") ATTR_ACCESS_NONE(1) errno_t
NOTHROW_NCX(LIBCCALL libc_posix_madvise)(void *addr,
                                         size_t len,
                                         __STDC_INT_AS_UINT_T advice) {

	int result;
	switch (advice) {
#if __POSIX_MADV_NORMAL == __MADV_NORMAL && __POSIX_MADV_RANDOM == __MADV_RANDOM && __POSIX_MADV_SEQUENTIAL == __MADV_SEQUENTIAL && __POSIX_MADV_WILLNEED == __MADV_WILLNEED && __POSIX_MADV_DONTNEED == __MADV_DONTNEED





	case __POSIX_MADV_NORMAL:


	case __POSIX_MADV_RANDOM:


	case __POSIX_MADV_SEQUENTIAL:


	case __POSIX_MADV_WILLNEED:


	case __POSIX_MADV_DONTNEED:

		break;
#else /* __POSIX_MADV_NORMAL == __MADV_NORMAL && __POSIX_MADV_RANDOM == __MADV_RANDOM && __POSIX_MADV_SEQUENTIAL == __MADV_SEQUENTIAL && __POSIX_MADV_WILLNEED == __MADV_WILLNEED && __POSIX_MADV_DONTNEED == __MADV_DONTNEED */

	case __POSIX_MADV_NORMAL:
		advice = __MADV_NORMAL;
		break;


	case __POSIX_MADV_RANDOM:
		advice = __MADV_RANDOM;
		break;


	case __POSIX_MADV_SEQUENTIAL:
		advice = __MADV_SEQUENTIAL;
		break;


	case __POSIX_MADV_WILLNEED:
		advice = __MADV_WILLNEED;
		break;


	case __POSIX_MADV_DONTNEED:
		advice = __MADV_DONTNEED;
		break;

#endif /* __POSIX_MADV_NORMAL != __MADV_NORMAL || __POSIX_MADV_RANDOM != __MADV_RANDOM || __POSIX_MADV_SEQUENTIAL != __MADV_SEQUENTIAL || __POSIX_MADV_WILLNEED != __MADV_WILLNEED || __POSIX_MADV_DONTNEED != __MADV_DONTNEED */
	default:

		return EINVAL;



	}

	{
		errno_t saved_errno;
		saved_errno = __libc_geterrno();
		result = libc_madvise(addr, len, advice);
		if unlikely(result != 0)
			result = __libc_geterrno();
		(void)__libc_seterrno(saved_errno);
	}







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
#include <hybrid/__overflow.h>
#include <asm/crt/malloc.h>
/* >> fmapfile(3)
 * A function that can be used to map a specific sub-range of some file into memory.
 * This function tries the following (in this order) in order to create the mapping:
 *  - mmap(2):                        If `fd' can be mmap'd, then that is how the mapping is created
 *  - malloc(3) + pread(2):           If `fd' supports pread(2), use that to fill a buffer
 *  - malloc(3) + lseek(2) + read(2): For a non-zero offset, try to use lseek(2) to move to `offset'
 *  - malloc(3) + read(2):            When lseek(2) returns an error, use read(2) to skip `offset',
 *                                    after which  up  to  `max_bytes'  bytes  are  read  normally.
 * Upon success (return == 0), the given `mapping' must be deleted using `unmapfile(3)'
 * @param: fd:        The file that should be loaded into memory.
 * @param: mapping:   Filled with mapping information. This structure contains at least 2 fields:
 *                     - mf_addr: Filled with the base address of a mapping of the file's contents
 *                     - mf_size: The actual number of mapped bytes (excluding `num_trailing_nulbytes')
 *                                This will always be `>= min_bytes && <= max_bytes'.
 *                     - Other fields are implementation-specific
 *                    Note that the memory located at `mapping->mf_addr' is writable, though changes  to
 *                    it are guarantied not to be written back to `fd'. iow: it behaves like MAP_PRIVATE
 *                    mapped as PROT_READ|PROT_WRITE.
 * @param: offset:    File offset / number of leading bytes that should not be  mapped
 *                    When set to `(Dee_pos_t)-1', use the fd's current file position.
 * @param: min_bytes: The  min number of bytes (excluding num_trailing_nulbytes) that should be mapped
 *                    starting  at `offset'. If the file is smaller than this, or indicates EOF before
 *                    this number of bytes has been reached,  nul bytes are mapped for its  remainder.
 *                    Note that this doesn't include `num_trailing_nulbytes', meaning that (e.g.) when
 *                    an entirely empty file is mapped you get a buffer like:
 *                    >> mf_addr = calloc(min_size + num_trailing_nulbytes);
 *                    >> mf_size = min_size;
 *                    This argument essentially acts as if `fd' was at least `min_bytes' bytes large
 *                    by filling the non-present address range with all zeroes.
 * @param: max_bytes: The  max number of bytes (excluding num_trailing_nulbytes) that should be mapped
 *                    starting  at `offset'. If the file is smaller than this, or indicates EOF before
 *                    this number of bytes has been reached, simply stop there. - The actual number of
 *                    mapped bytes (excluding `num_trailing_nulbytes') is `mapping->mf_size'.
 * @param: num_trailing_nulbytes: When non-zero, append this many trailing NUL-bytes at the end of
 *                    the mapping. More bytes than this may be appended if necessary, but at least
 *                    this many are guarantied  to be. - Useful  if you want to  load a file as  a
 *                    string,  in which case you can specify `1' to always have a trailing '\0' be
 *                    appended:
 *                    >> bzero(mapping->mf_addr + mapping->mf_size, num_trailing_nulbytes);
 * @param: flags:     Set of `FMAPFILE_*'
 * @return: 0 : Success (the given `mapping' must be deleted using `unmapfile(3)')
 * @return: -1: [errno=EINVAL]  The given `flags' contains invalid bits.
 * @return: -1: [errno=EINVAL]  `FMAPFILE_MAPSHARED' was set,  an mmap  was
 *                              attempted, and `num_trailing_nulbytes != 0'
 * @return: -1: [errno=EPERM]   `fd' doesn't support read(2)ing
 * @return: -1: [errno=ENOMEM]  Out of memory (or file is too large for a continuous heap-buffer to be posible)
 * @return: -1: [errno=EBADF]   Invalid `fd'
 * @return: -1: [errno=ENOTSUP] `FMAPFILE_ONLYMMAP' was given, and mmap  wasn't possible, either because a  call
 *                              to  `mmap(2)' with the  given `fd' returned an  error (including indicating that
 *                              the file doesn't support mmap(), or that there isn't enough space t map the file
 *                              in its entirety), or because  `max_bytes == (size_t)-1', and the effective  area
 *                              that you are trying to map is larger than the entirety of your address space.
 * @return: -1: [errno=*]       Read error */
INTERN ATTR_SECTION(".text.crt.system.mman") WUNUSED ATTR_FDARG(2) ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_fmapfile)(struct mapfile *__restrict mapping,
                                    fd_t fd,
                                    pos64_t offset,
                                    size_t min_bytes,
                                    size_t max_bytes,
                                    size_t num_trailing_nulbytes,
                                    unsigned int flags) {
	byte_t *buf;
	size_t bufsize;
	size_t bufused;
	size_t buffree;

	/* Helper macro that makes sure `errno(3)' is preserved across `expr' */

#define __LOCAL_preserve_errno(expr)              \
	do {                                          \
		errno_t _saved_errno = __libc_geterrno(); \
		expr;                                     \
		__libc_seterrno(_saved_errno);            \
	}	__WHILE0




	/* Validate the given `flags' */
	if unlikely(flags & ~(__FMAPFILE_READALL | __FMAPFILE_MUSTMMAP |
	                      __FMAPFILE_MAPSHARED | __FMAPFILE_ATSTART)) {

		return __libc_seterrno(EINVAL);



	}

	/* Check for special case: map an empty portion of the file. */
	if unlikely(max_bytes == 0) {
#ifndef __REALLOC_ZERO_IS_NONNULL
		if (num_trailing_nulbytes == 0)
			num_trailing_nulbytes = 1;
#endif /* !__REALLOC_ZERO_IS_NONNULL */
		buf = (byte_t *)libc_calloc(1, num_trailing_nulbytes);
		if unlikely(!buf)
			return -1;
		mapping->mf_addr = buf;
		mapping->mf_size = 0;
		mapping->__mf_mapsize = 0;
		return 0;
	}

	/* Try to use mmap(2) */

	{
		struct stat64 st;
		if (fstat64(fd, &st) == 0) {

			errno_t saved_errno = __libc_geterrno();

			pos64_t map_offset = offset;
			size_t map_bytes;
			if (map_offset == (pos64_t)-1) {
				if unlikely(flags & __FMAPFILE_ATSTART) {
					map_offset = 0;
				} else {
					/* Use the file descriptors current offset. */
					map_offset = (pos64_t)libc_lseek64(fd, 0, __SEEK_CUR);
					if (map_offset == (pos64_t)-1)
						goto after_mmap_attempt;
				}
			}
			if (__hybrid_overflow_usub(st.st_size, map_offset, &map_bytes)) {
				map_bytes = 0;
				if (st.st_size > map_offset)
					map_bytes = (size_t)-1;
			}
			if (map_bytes >= max_bytes) {
				map_bytes = max_bytes;
#if __SIZEOF_SIZE_T__ < __SIZEOF_OFF64_T__
				if (map_bytes == (size_t)-1) {
					/* Special case: caller wants to map the entire file, but it's too large. */
					uint64_t true_size = st.st_size - map_offset;
					if (true_size > (uint64_t)(size_t)-1) {
						/* File is too large to be loaded into memory in its entirety. */
						if (flags & __FMAPFILE_MUSTMMAP) {

							return __libc_seterrno(ENOTSUP);





						}

						/* File is too large for a continuous heap-buffer to be posible */

						return __libc_seterrno(ENOMEM);



					}
				}
#endif /* __SIZEOF_SIZE_T__ < __SIZEOF_OFF64_T__ */
			}
			if (map_bytes) {
				/* Map file into memory. */
				size_t mapsize, used_nulbytes;
				used_nulbytes = num_trailing_nulbytes;
				if (min_bytes > map_bytes) {
					if unlikely(__hybrid_overflow_uadd(used_nulbytes, min_bytes - map_bytes, &used_nulbytes))
						goto err_2big;
				}
				if unlikely(__hybrid_overflow_uadd(map_bytes, used_nulbytes, &mapsize))
					mapsize = (size_t)-1; /* Force mmap failure */

				if (flags & __FMAPFILE_MAPSHARED) {
					if unlikely(num_trailing_nulbytes) {

						return __libc_seterrno(EINVAL);



					}
					buf = (byte_t *)libc_mmap64(NULL, mapsize, __PROT_READ | __PROT_WRITE,
					                       __MAP_SHARED, fd, (__PIO_OFFSET64)map_offset);
				} else {
					buf = (byte_t *)libc_mmap64(NULL, mapsize, __PROT_READ | __PROT_WRITE,
					                       __MAP_PRIVATE, fd, (__PIO_OFFSET64)map_offset);
				}


















				if (buf != (byte_t *)__MAP_FAILED) {
					/* Clear  out the caller-required trailing NUL bytes.
					 * We do this in a kind-of special way that tries not
					 * to write-fault memory if it already contains NULs. */
					byte_t *nul = buf + map_bytes;
					while (used_nulbytes) {
						if (*nul) {
							libc_bzero(nul, used_nulbytes);
							break;
						}
						--used_nulbytes;
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
	}
after_mmap_attempt:


	/* Check if we're to error out if mmap can't be used */
	if (flags & __FMAPFILE_MUSTMMAP) {

		return __libc_seterrno(ENOTSUP);





	}

	/* Allocate a heap buffer. */
	bufsize = max_bytes;
	if (bufsize > 0x10000)
		bufsize = 0x10000;
	if (bufsize < min_bytes)
		bufsize = min_bytes;
	{
		size_t alcsize;
		if unlikely(__hybrid_overflow_uadd(bufsize, num_trailing_nulbytes, &alcsize))
			goto err_2big;
		__LOCAL_preserve_errno(buf = (byte_t *)libc_malloc(alcsize));
	}
	if unlikely(!buf) {
		bufsize = 1;
		if (bufsize < min_bytes)
			bufsize = min_bytes;
		buf = (byte_t *)libc_malloc(bufsize + num_trailing_nulbytes);
		if unlikely(!buf)
			return -1;
	}
	bufused = 0;
	buffree = bufsize;

	if (offset != (pos64_t)-1 && (offset != 0 || !(flags & __FMAPFILE_ATSTART))) {
		/* Try to use pread(2) */

		for (;;) {
			ssize_t error;
			error = libc_pread64(fd, buf + bufused, buffree, offset);
			if (error <= 0 || (!(flags & __FMAPFILE_READALL) && (size_t)error < buffree)) {
				if ((size_t)error < buffree) {
					/* End-of-file! */
					byte_t *newbuf;
					size_t used_nulbytes;
					bufused += (size_t)error;
					used_nulbytes = num_trailing_nulbytes;
					if (min_bytes > bufused)
						used_nulbytes += min_bytes - bufused;
					__LOCAL_preserve_errno(newbuf = (byte_t *)libc_realloc(buf, bufused + used_nulbytes));
					if likely(newbuf)
						buf = newbuf;
					libc_bzero(buf + bufused, used_nulbytes); /* Trailing NUL-bytes */
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
				size_t newsize, alcsize;
				if unlikely(__hybrid_overflow_umul(bufsize, 2, &newsize))
					newsize = (size_t)-1;
				if unlikely(__hybrid_overflow_uadd(newsize, num_trailing_nulbytes, &alcsize))
					alcsize = (size_t)-1;
				__LOCAL_preserve_errno(newbuf = (byte_t *)libc_realloc(buf, alcsize));
				if (!newbuf) {
					if unlikely(__hybrid_overflow_uadd(bufsize, 1024, &newsize))
						newsize = (size_t)-1;
					if unlikely(__hybrid_overflow_uadd(newsize, num_trailing_nulbytes, &alcsize))
						alcsize = (size_t)-1;
					__LOCAL_preserve_errno(newbuf = (byte_t *)libc_realloc(buf, alcsize));
					if (!newbuf) {
						if (!buffree) {
							if unlikely(__hybrid_overflow_uadd(bufsize, 1, &newsize))
								goto err_buf_2big;
							if unlikely(__hybrid_overflow_uadd(newsize, num_trailing_nulbytes, &alcsize))
								goto err_buf_2big;
							newbuf  = (byte_t *)libc_realloc(buf, alcsize);
							if unlikely(!newbuf)
								goto err_buf;
						} else {
							newsize = bufsize;
							newbuf  = buf;
						}
					}
				}
				buffree += newsize - bufsize;
				bufsize = newsize;
				buf     = newbuf;
			}
		}


		/* For a custom offset, try to use lseek() (or read()) */

		if (libc_lseek64(fd, (off64_t)offset, __SEEK_SET) != -1) {
			/* Was able to lseek(2) */
		} else

		{
			/* Try to use read(2) to skip leading data. */
			while (offset) {
				ssize_t error;
				size_t skip = bufsize + num_trailing_nulbytes;
				if ((pos64_t)skip > offset)
					skip = (size_t)offset;
				error = libc_read(fd, buf, skip);
				if (error <= 0 || (!(flags & __FMAPFILE_READALL) && (size_t)error < skip)) {
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
		if (error <= 0 || (!(flags & __FMAPFILE_READALL) && (size_t)error < buffree)) {
			if (error >= 0) {
				/* End-of-file! */
				byte_t *newbuf;
				size_t used_nulbytes;
				bufused += (size_t)error;
				used_nulbytes = num_trailing_nulbytes;
				if (min_bytes > bufused)
					used_nulbytes += min_bytes - bufused;
				__LOCAL_preserve_errno(newbuf = (byte_t *)libc_realloc(buf, bufused + used_nulbytes));
				if likely(newbuf)
					buf = newbuf;
				libc_bzero(buf + bufused, used_nulbytes); /* Trailing NUL-bytes */
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
			size_t newsize, alcsize;
			if unlikely(__hybrid_overflow_umul(bufsize, 2, &newsize))
				newsize = (size_t)-1;
			if unlikely(__hybrid_overflow_uadd(newsize, num_trailing_nulbytes, &alcsize))
				alcsize = (size_t)-1;
			__LOCAL_preserve_errno(newbuf = (byte_t *)libc_realloc(buf, alcsize));
			if (!newbuf) {
				if unlikely(__hybrid_overflow_uadd(bufsize, 1024, &newsize))
					newsize = (size_t)-1;
				if unlikely(__hybrid_overflow_uadd(newsize, num_trailing_nulbytes, &alcsize))
					alcsize = (size_t)-1;
				__LOCAL_preserve_errno(newbuf = (byte_t *)libc_realloc(buf, alcsize));
				if (!newbuf) {
					if (!buffree) {
						if unlikely(__hybrid_overflow_uadd(bufsize, 1, &newsize))
							goto err_buf_2big;
						if unlikely(__hybrid_overflow_uadd(newsize, num_trailing_nulbytes, &alcsize))
							goto err_buf_2big;
						newbuf = (byte_t *)libc_realloc(buf, alcsize);
						if unlikely(!newbuf)
							goto err_buf;
					} else {
						newsize = bufsize;
						newbuf  = buf;
					}
				}
			}
			buffree += newsize - bufsize;
			bufsize = newsize;
			buf     = newbuf;
		}
	}

	/*--------------------------------------------------------------------*/
	{
		byte_t *newbuf;
		size_t used_nulbytes;
		/* Because of how large our original buffer was, and because at this
		 * point all  we want  to do  is return  a  `num_trailing_nulbytes'-
		 * large buffer of  all NUL-bytes, it's  probably more efficient  to
		 * allocate a new  (small) buffer,  than trying to  realloc the  old
		 * buffer. If we try  to do realloc(), the  heap might see that  all
		 * we're  trying to do  is truncate the buffer,  and so might choose
		 * not to alter its base  address, which (if done repeatedly)  might
		 * lead to memory becoming very badly fragmented. */
empty_file:
		used_nulbytes = min_bytes + num_trailing_nulbytes;
		__LOCAL_preserve_errno(newbuf = (byte_t *)libc_calloc(1, used_nulbytes));
		if likely(newbuf) {

			libc_free(buf);

		} else {
#ifndef __REALLOC_ZERO_IS_NONNULL
			if unlikely(!used_nulbytes)
				used_nulbytes = 1;
#endif /* !__REALLOC_ZERO_IS_NONNULL */
			__LOCAL_preserve_errno(newbuf = (byte_t *)libc_realloc(buf, used_nulbytes));
			if (!newbuf)
				newbuf = buf;
			libc_bzero(newbuf, used_nulbytes);
		}
		mapping->mf_addr = newbuf;
		mapping->mf_size = 0;
		mapping->__mf_mapsize = 0;
	}
#undef __LOCAL_preserve_errno
	return 0;
err_2big:

	buf = NULL;

err_buf_2big:

	__libc_seterrno(ENOMEM);



err_buf:

	libc_free(buf);

	return -1;
}
/* >> fmapfileat(3)
 * Map the specified `filename' into memory. s.a. `fmapfile(3)'
 * @param: atflags: Set of `0 | AT_DOSPATH | AT_EMPTY_PATH' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.system.mman") WUNUSED ATTR_IN(3) ATTR_OUT(1) int
NOTHROW_NCX(LIBDCALL libd_fmapfileat)(struct mapfile *__restrict mapping,
                                      fd_t dirfd,
                                      char const *filename,
                                      pos64_t offset,
                                      size_t min_bytes,
                                      size_t max_bytes,
                                      size_t num_trailing_nulbytes,
                                      unsigned int flags,
                                      atflag_t atflags) {
	return libc_fmapfileat(mapping, dirfd, filename, offset,
	                       min_bytes, max_bytes, num_trailing_nulbytes,
	                       flags, atflags | libd_AT_DOSPATH);
}
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#include <libc/errno.h>
/* >> fmapfileat(3)
 * Map the specified `filename' into memory. s.a. `fmapfile(3)'
 * @param: atflags: Set of `0 | AT_DOSPATH | AT_EMPTY_PATH' */
INTERN ATTR_SECTION(".text.crt.system.mman") WUNUSED ATTR_IN(3) ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_fmapfileat)(struct mapfile *__restrict mapping,
                                      fd_t dirfd,
                                      char const *filename,
                                      pos64_t offset,
                                      size_t min_bytes,
                                      size_t max_bytes,
                                      size_t num_trailing_nulbytes,
                                      unsigned int flags,
                                      atflag_t atflags) {
	fd_t fd;
	int result;
	oflag_t oflags = __O_RDONLY | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK;

	if (atflags & __AT_DOSPATH) {
		oflags |= __O_DOSPATH;
		atflags &= ~__AT_DOSPATH;
	}


	if (atflags & __AT_EMPTY_PATH) {
		if (!*filename) {
			return libc_fmapfile(mapping, dirfd,
			                offset, min_bytes, max_bytes,
			                num_trailing_nulbytes, flags);
		}
		atflags &= ~__AT_EMPTY_PATH;
	}

	if unlikely(atflags != 0) {

		return libc_seterrno(EINVAL);



	}
	fd = libc_openat(dirfd, filename, oflags);
	if unlikely(fd < 0)
		return -1;
	result = libc_fmapfile(mapping, fd,
	                  offset, min_bytes, max_bytes,
	                  num_trailing_nulbytes,
	                  flags | __FMAPFILE_ATSTART);

	libc_close(fd);

	return result;
}
/* >> mapfile(3)
 * Map the specified `filename' into memory. s.a. `fmapfile(3)' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.system.mman") WUNUSED ATTR_IN(2) ATTR_OUT(1) int
NOTHROW_NCX(LIBDCALL libd_mapfile)(struct mapfile *__restrict mapping,
                                   char const *filename,
                                   pos64_t offset,
                                   size_t min_bytes,
                                   size_t max_bytes,
                                   size_t num_trailing_nulbytes,
                                   unsigned int flags) {

	return libd_fmapfileat(mapping, __AT_FDCWD, filename,
	                  offset, min_bytes, max_bytes,
	                  num_trailing_nulbytes, flags, 0);













}
/* >> mapfile(3)
 * Map the specified `filename' into memory. s.a. `fmapfile(3)' */
INTERN ATTR_SECTION(".text.crt.system.mman") WUNUSED ATTR_IN(2) ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_mapfile)(struct mapfile *__restrict mapping,
                                   char const *filename,
                                   pos64_t offset,
                                   size_t min_bytes,
                                   size_t max_bytes,
                                   size_t num_trailing_nulbytes,
                                   unsigned int flags) {

	return libc_fmapfileat(mapping, __AT_FDCWD, filename,
	                  offset, min_bytes, max_bytes,
	                  num_trailing_nulbytes, flags, 0);













}
/* >> unmapfile(3)
 * Delete a file mapping previously created by `mapfile(3)' */
INTERN ATTR_SECTION(".text.crt.system.mman") ATTR_INOUT(1) int
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
DEFINE_PUBLIC_ALIAS_P(__shm_directory,libc___shm_directory,,const char *,NOTHROW_NCX,LIBCCALL,(size_t *len),(len));
DEFINE_PUBLIC_ALIAS_P(shm_open,libc_shm_open,ATTR_IN(1),fd_t,NOTHROW_RPC,LIBCCALL,(char const *name, oflag_t oflags, mode_t mode),(name,oflags,mode));
DEFINE_PUBLIC_ALIAS_P(shm_unlink,libc_shm_unlink,ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *name),(name));
DEFINE_PUBLIC_ALIAS_P(posix_madvise,libc_posix_madvise,ATTR_ACCESS_NONE(1),errno_t,NOTHROW_NCX,LIBCCALL,(void *addr, size_t len, __STDC_INT_AS_UINT_T advice),(addr,len,advice));
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY)
DEFINE_PUBLIC_ALIAS_P(pkey_set,libc_pkey_set,,int,NOTHROW_NCX,LIBCCALL,(int pkey, unsigned int access_rights),(pkey,access_rights));
DEFINE_PUBLIC_ALIAS_P(pkey_get,libc_pkey_get,,int,NOTHROW_NCX,LIBCCALL,(int pkey),(pkey));
#endif /* !__KERNEL__ && __ARCH_HAVE_PKEY */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(fmapfile,libc_fmapfile,WUNUSED ATTR_FDARG(2) ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(struct mapfile *__restrict mapping, fd_t fd, pos64_t offset, size_t min_bytes, size_t max_bytes, size_t num_trailing_nulbytes, unsigned int flags),(mapping,fd,offset,min_bytes,max_bytes,num_trailing_nulbytes,flags));
DEFINE_PUBLIC_ALIAS_P(DOS$fmapfileat,libd_fmapfileat,WUNUSED ATTR_IN(3) ATTR_OUT(1),int,NOTHROW_NCX,LIBDCALL,(struct mapfile *__restrict mapping, fd_t dirfd, char const *filename, pos64_t offset, size_t min_bytes, size_t max_bytes, size_t num_trailing_nulbytes, unsigned int flags, atflag_t atflags),(mapping,dirfd,filename,offset,min_bytes,max_bytes,num_trailing_nulbytes,flags,atflags));
DEFINE_PUBLIC_ALIAS_P(fmapfileat,libc_fmapfileat,WUNUSED ATTR_IN(3) ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(struct mapfile *__restrict mapping, fd_t dirfd, char const *filename, pos64_t offset, size_t min_bytes, size_t max_bytes, size_t num_trailing_nulbytes, unsigned int flags, atflag_t atflags),(mapping,dirfd,filename,offset,min_bytes,max_bytes,num_trailing_nulbytes,flags,atflags));
DEFINE_PUBLIC_ALIAS_P(DOS$mapfile,libd_mapfile,WUNUSED ATTR_IN(2) ATTR_OUT(1),int,NOTHROW_NCX,LIBDCALL,(struct mapfile *__restrict mapping, char const *filename, pos64_t offset, size_t min_bytes, size_t max_bytes, size_t num_trailing_nulbytes, unsigned int flags),(mapping,filename,offset,min_bytes,max_bytes,num_trailing_nulbytes,flags));
DEFINE_PUBLIC_ALIAS_P(mapfile,libc_mapfile,WUNUSED ATTR_IN(2) ATTR_OUT(1),int,NOTHROW_NCX,LIBCCALL,(struct mapfile *__restrict mapping, char const *filename, pos64_t offset, size_t min_bytes, size_t max_bytes, size_t num_trailing_nulbytes, unsigned int flags),(mapping,filename,offset,min_bytes,max_bytes,num_trailing_nulbytes,flags));
DEFINE_PUBLIC_ALIAS_P(unmapfile,libc_unmapfile,ATTR_INOUT(1),int,NOTHROW_NCX,LIBCCALL,(struct mapfile *__restrict mapping),(mapping));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_SYS_MMAN_C */
