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
#ifndef GUARD_LIBC_USER_SYS_TIMEX_C
#define GUARD_LIBC_USER_SYS_TIMEX_C 1

#include "../api.h"
#include "sys.timex.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_adjtimex,hash:CRC-32=0xfff02b48]]]*/
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_adjtimex)(struct timex *__restrict ntx)
/*[[[body:libc_adjtimex]]]*/
{
	(void)ntx;
	CRT_UNIMPLEMENTED("adjtimex"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:libc_adjtimex]]]*/

/*[[[head:libc_ntp_gettimex,hash:CRC-32=0xfb4798d2]]]*/
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_ntp_gettimex)(struct ntptimeval *__restrict ntv)
/*[[[body:libc_ntp_gettimex]]]*/
{
	(void)ntv;
	CRT_UNIMPLEMENTED("ntp_gettimex"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:libc_ntp_gettimex]]]*/

/*[[[head:libc_ntp_adjtime,hash:CRC-32=0x4ff3a4b]]]*/
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_ntp_adjtime)(struct timex *__restrict tntx)
/*[[[body:libc_ntp_adjtime]]]*/
{
	(void)tntx;
	CRT_UNIMPLEMENTED("ntp_adjtime"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:libc_ntp_adjtime]]]*/

/*[[[head:libc_adjtimex64,hash:CRC-32=0xba95dc83]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_adjtimex64, libc_adjtimex);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_adjtimex64)(struct timex64 *__restrict ntx)
/*[[[body:libc_adjtimex64]]]*/
{
	(void)ntx;
	CRT_UNIMPLEMENTED("adjtimex64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:libc_adjtimex64]]]*/

/*[[[head:libc_ntp_adjtime64,hash:CRC-32=0x23aaeb28]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_ntp_adjtime64, libc_ntp_adjtime);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_ntp_adjtime64)(struct timex64 *__restrict tntx)
/*[[[body:libc_ntp_adjtime64]]]*/
{
	(void)tntx;
	CRT_UNIMPLEMENTED("ntp_adjtime64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:libc_ntp_adjtime64]]]*/

/*[[[head:libc_ntp_gettimex64,hash:CRC-32=0xcf37f2b4]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_ntp_gettimex64, libc_ntp_gettimex);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.unsorted") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_ntp_gettimex64)(struct ntptimeval64 *__restrict ntv)
/*[[[body:libc_ntp_gettimex64]]]*/
{
	(void)ntv;
	CRT_UNIMPLEMENTED("ntp_gettimex64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:libc_ntp_gettimex64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x813b6bf0]]]*/
DEFINE_PUBLIC_ALIAS(__adjtimex, libc_adjtimex);
DEFINE_PUBLIC_ALIAS(adjtimex, libc_adjtimex);
DEFINE_PUBLIC_ALIAS(ntp_gettimex, libc_ntp_gettimex);
DEFINE_PUBLIC_ALIAS(ntp_adjtime, libc_ntp_adjtime);
DEFINE_PUBLIC_ALIAS(__adjtimex64, libc_adjtimex64);
DEFINE_PUBLIC_ALIAS(adjtimex64, libc_adjtimex64);
DEFINE_PUBLIC_ALIAS(ntp_adjtime64, libc_ntp_adjtime64);
DEFINE_PUBLIC_ALIAS(ntp_gettimex64, libc_ntp_gettimex64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_TIMEX_C */
