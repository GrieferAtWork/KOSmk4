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
#ifndef GUARD_LIBC_USER_FTW_C
#define GUARD_LIBC_USER_FTW_C 1

#include "../api.h"
/**/

#include "ftw.h"

DECL_BEGIN

/*[[[head:libc_ftw,hash:CRC-32=0xa00de196]]]*/
/* >> ftw(3), ftw64(3) */
INTERN ATTR_SECTION(".text.crt.fs.ftw") ATTR_IN(1) NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_ftw)(char const *dir,
                               __ftw_func_t func,
                               __STDC_INT_AS_UINT_T nopenfd)
/*[[[body:libc_ftw]]]*/
/*AUTO*/{
	(void)dir;
	(void)func;
	(void)nopenfd;
	CRT_UNIMPLEMENTEDF("ftw(%q, %p, %x)", dir, func, nopenfd); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ftw]]]*/

/*[[[head:libc_ftw64,hash:CRC-32=0x4e81456f]]]*/
#ifdef __STAT32_MATCHES_STAT64
DEFINE_INTERN_ALIAS(libc_ftw64, libc_ftw);
#else /* MAGIC:alias */
/* >> ftw(3), ftw64(3) */
INTERN ATTR_SECTION(".text.crt.fs.ftw") ATTR_IN(1) NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_ftw64)(char const *dir,
                                 __ftw64_func_t func,
                                 __STDC_INT_AS_UINT_T nopenfd)
/*[[[body:libc_ftw64]]]*/
/*AUTO*/{
	(void)dir;
	(void)func;
	(void)nopenfd;
	CRT_UNIMPLEMENTEDF("ftw64(%q, %p, %x)", dir, func, nopenfd); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_ftw64]]]*/

/*[[[head:libc_nftw,hash:CRC-32=0xf2a136a5]]]*/
/* >> nftw(3), nftw64(3)
 * @param: flags: Set of `FTW_PHYS | FTW_MOUNT | FTW_CHDIR | FTW_DEPTH | FTW_ACTIONRETVAL' */
INTERN ATTR_SECTION(".text.crt.fs.ftw") ATTR_IN(1) NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_nftw)(char const *dir,
                                __nftw_func_t func,
                                __STDC_INT_AS_UINT_T descriptors,
                                __STDC_INT_AS_UINT_T flags)
/*[[[body:libc_nftw]]]*/
/*AUTO*/{
	(void)dir;
	(void)func;
	(void)descriptors;
	(void)flags;
	CRT_UNIMPLEMENTEDF("nftw(%q, %p, %x, %x)", dir, func, descriptors, flags); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_nftw]]]*/

/*[[[head:libc_nftw64,hash:CRC-32=0x13d08eda]]]*/
#ifdef __STAT32_MATCHES_STAT64
DEFINE_INTERN_ALIAS(libc_nftw64, libc_nftw);
#else /* MAGIC:alias */
/* >> nftw(3), nftw64(3)
 * @param: flags: Set of `FTW_PHYS | FTW_MOUNT | FTW_CHDIR | FTW_DEPTH | FTW_ACTIONRETVAL' */
INTERN ATTR_SECTION(".text.crt.fs.ftw") ATTR_IN(1) NONNULL((2)) int
NOTHROW_RPC(LIBCCALL libc_nftw64)(char const *dir,
                                  __nftw64_func_t func,
                                  __STDC_INT_AS_UINT_T descriptors,
                                  __STDC_INT_AS_UINT_T flags)
/*[[[body:libc_nftw64]]]*/
/*AUTO*/{
	(void)dir;
	(void)func;
	(void)descriptors;
	(void)flags;
	CRT_UNIMPLEMENTEDF("nftw64(%q, %p, %x, %x)", dir, func, descriptors, flags); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:libc_nftw64]]]*/

/*[[[start:exports,hash:CRC-32=0x5b98419e]]]*/
DEFINE_PUBLIC_ALIAS(ftw, libc_ftw);
DEFINE_PUBLIC_ALIAS(ftw64, libc_ftw64);
DEFINE_PUBLIC_ALIAS(nftw, libc_nftw);
DEFINE_PUBLIC_ALIAS(nftw64, libc_nftw64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_FTW_C */
