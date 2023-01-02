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
#ifndef GUARD_LIBC_USER_SYS_STATVFS_C
#define GUARD_LIBC_USER_SYS_STATVFS_C 1

#include "../api.h"
/**/

#include <sys/statfs.h>

#include "sys.statvfs.h"

DECL_BEGIN


FORCELOCAL void LIBCCALL
statfs_to_statvfs(struct statvfs *__restrict dst,
                  struct statfs const *__restrict src) {
	dst->f_bsize   = src->f_bsize;
	dst->f_frsize  = src->f_frsize;
	dst->f_blocks  = src->f_blocks;
	dst->f_bfree   = src->f_bfree;
	dst->f_bavail  = src->f_bavail;
	dst->f_files   = src->f_files;
	dst->f_ffree   = src->f_ffree;
	dst->f_favail  = src->f_ffree; /* ??? */
	{
		union {
			ulongptr_t ptr;
			__fsid_t   fsid;
		} temp;
		temp.fsid   = src->f_fsid;
		dst->f_fsid = temp.ptr;
	}
	dst->f_flag    = src->f_flags;
	dst->f_namemax = src->f_namelen;
}

FORCELOCAL void LIBCCALL
statfs64_to_statvfs64(struct statvfs64 *__restrict dst,
                      struct statfs64 const *__restrict src) {
	dst->f_bsize   = src->f_bsize;
	dst->f_frsize  = src->f_frsize;
	dst->f_blocks  = src->f_blocks;
	dst->f_bfree   = src->f_bfree;
	dst->f_bavail  = src->f_bavail;
	dst->f_files   = src->f_files;
	dst->f_ffree   = src->f_ffree;
	dst->f_favail  = src->f_ffree; /* ??? */
	{
		union {
			ulongptr_t ptr;
			__fsid_t   fsid;
		} temp;
		temp.fsid   = src->f_fsid;
		dst->f_fsid = temp.ptr;
	}
	dst->f_flag    = src->f_flags;
	dst->f_namemax = src->f_namelen;
}



/*[[[head:libc_statvfs,hash:CRC-32=0xd7e1d108]]]*/
INTERN ATTR_SECTION(".text.crt.fs.statfs.statvfs") ATTR_IN(1) ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_statvfs)(char const *file,
                                   struct statvfs *buf)
/*[[[body:libc_statvfs]]]*/
{
	int result;
	struct statfs data;
	result = statfs(file, &data);
	if likely(result == 0)
		statfs_to_statvfs(buf, &data);
	return result;
}
/*[[[end:libc_statvfs]]]*/

/*[[[head:libc_fstatvfs,hash:CRC-32=0x310d6bac]]]*/
INTERN ATTR_SECTION(".text.crt.fs.statfs.statvfs") ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_fstatvfs)(fd_t filedes,
                                    struct statvfs *buf)
/*[[[body:libc_fstatvfs]]]*/
{
	int result;
	struct statfs data;
	result = fstatfs(filedes, &data);
	if likely(result == 0)
		statfs_to_statvfs(buf, &data);
	return result;
}
/*[[[end:libc_fstatvfs]]]*/

/*[[[head:libc_statvfs64,hash:CRC-32=0x79fc557b]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_statvfs64, libc_statvfs);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.fs.statfs.statvfs") ATTR_IN(1) ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_statvfs64)(const char *file,
                                     struct statvfs64 *buf)
/*[[[body:libc_statvfs64]]]*/
{
	int result;
	struct statfs64 data;
	result = statfs64(file, &data);
	if likely(result == 0)
		statfs64_to_statvfs64(buf, &data);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:libc_statvfs64]]]*/

/*[[[head:libc_fstatvfs64,hash:CRC-32=0x67caddf5]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_fstatvfs64, libc_fstatvfs);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.fs.statfs.statvfs") ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_fstatvfs64)(fd_t filedes,
                                      struct statvfs64 *buf)
/*[[[body:libc_fstatvfs64]]]*/
{
	int result;
	struct statfs64 data;
	result = fstatfs64(filedes, &data);
	if likely(result == 0)
		statfs64_to_statvfs64(buf, &data);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:libc_fstatvfs64]]]*/





/*[[[start:exports,hash:CRC-32=0xd435bc45]]]*/
DEFINE_PUBLIC_ALIAS(statvfs, libc_statvfs);
DEFINE_PUBLIC_ALIAS(fstatvfs, libc_fstatvfs);
DEFINE_PUBLIC_ALIAS(statvfs64, libc_statvfs64);
DEFINE_PUBLIC_ALIAS(fstatvfs64, libc_fstatvfs64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_STATVFS_C */
