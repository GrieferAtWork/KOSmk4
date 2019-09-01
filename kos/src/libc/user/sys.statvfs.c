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
#ifndef GUARD_LIBC_USER_SYS_STATVFS_C
#define GUARD_LIBC_USER_SYS_STATVFS_C 1

#include "../api.h"
#include "sys.statvfs.h"
#include <sys/statfs.h>

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
	dst->f_fsid    = *(__ULONGPTR_TYPE__ *)&src->f_fsid;
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
	dst->f_fsid    = *(__ULONGPTR_TYPE__ *)&src->f_fsid;
	dst->f_flag    = src->f_flags;
	dst->f_namemax = src->f_namelen;
}



/*[[[start:implementation]]]*/

/*[[[head:statvfs,hash:0xd4ff9a46]]]*/
/* Return information about the filesystem on which FILE resides */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.statfs.statvfs.statvfs") int
NOTHROW_NCX(LIBCCALL libc_statvfs)(char const *file,
                                   struct statvfs *buf)
/*[[[body:statvfs]]]*/
{
	int result;
	struct statfs data;
	result = statfs(file, &data);
	if likely(result == 0)
		statfs_to_statvfs(buf, &data);
	return result;
}
/*[[[end:statvfs]]]*/

/*[[[head:fstatvfs,hash:0x31202059]]]*/
/* Return information about the filesystem containing the file FILDES refers to */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.statfs.statvfs.fstatvfs") int
NOTHROW_NCX(LIBCCALL libc_fstatvfs)(fd_t filedes,
                                    struct statvfs *buf)
/*[[[body:fstatvfs]]]*/
{
	int result;
	struct statfs data;
	result = fstatfs(filedes, &data);
	if likely(result == 0)
		statfs_to_statvfs(buf, &data);
	return result;
}
/*[[[end:fstatvfs]]]*/

/*[[[head:statvfs64,hash:0xd71a06e9]]]*/
/* Return information about the filesystem on which FILE resides */
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_statvfs64, libc_statvfs);
#else
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.statfs.statvfs.statvfs64") int
NOTHROW_NCX(LIBCCALL libc_statvfs64)(const char *file,
                                     struct statvfs64 *buf)
/*[[[body:statvfs64]]]*/
{
	int result;
	struct statfs64 data;
	result = statfs64(file, &data);
	if likely(result == 0)
		statfs64_to_statvfs64(buf, &data);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:statvfs64]]]*/

/*[[[head:fstatvfs64,hash:0xa2d29bc]]]*/
/* Return information about the filesystem containing the file FILDES refers to */
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_fstatvfs64, libc_fstatvfs);
#else
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.fs.statfs.statvfs.fstatvfs64") int
NOTHROW_NCX(LIBCCALL libc_fstatvfs64)(fd_t filedes,
                                      struct statvfs64 *buf)
/*[[[body:fstatvfs64]]]*/
{
	int result;
	struct statfs64 data;
	result = fstatfs64(filedes, &data);
	if likely(result == 0)
		statfs64_to_statvfs64(buf, &data);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:fstatvfs64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0x31ac869b]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(statvfs, libc_statvfs);
DEFINE_PUBLIC_WEAK_ALIAS(fstatvfs, libc_fstatvfs);
DEFINE_PUBLIC_WEAK_ALIAS(statvfs64, libc_statvfs64);
DEFINE_PUBLIC_WEAK_ALIAS(fstatvfs64, libc_fstatvfs64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_STATVFS_C */
