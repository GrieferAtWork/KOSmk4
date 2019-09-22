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
#ifndef GUARD_LIBC_USER_SYS_TIMEX_C
#define GUARD_LIBC_USER_SYS_TIMEX_C 1

#include "../api.h"
#include "sys.timex.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:adjtimex,hash:CRC-32=0xc1a051d9]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.adjtimex") int
NOTHROW_NCX(LIBCCALL libc_adjtimex)(struct timex *__restrict ntx)
/*[[[body:adjtimex]]]*/
{
	CRT_UNIMPLEMENTED("adjtimex"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:adjtimex]]]*/

/*[[[head:ntp_adjtime,hash:CRC-32=0x93e56b1b]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.ntp_adjtime") int
NOTHROW_NCX(LIBCCALL libc_ntp_adjtime)(struct timex *__restrict tntx)
/*[[[body:ntp_adjtime]]]*/
{
	CRT_UNIMPLEMENTED("ntp_adjtime"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:ntp_adjtime]]]*/

/*[[[head:adjtimex64,hash:CRC-32=0x48cedaf9]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_adjtimex64, libc_adjtimex);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.adjtimex64") int
NOTHROW_NCX(LIBCCALL libc_adjtimex64)(struct timex64 *__restrict ntx)
/*[[[body:adjtimex64]]]*/
{
	CRT_UNIMPLEMENTED("adjtimex64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:adjtimex64]]]*/

/*[[[head:ntp_adjtime64,hash:CRC-32=0x15fd2c51]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_ntp_adjtime64, libc_ntp_adjtime);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.ntp_adjtime64") int
NOTHROW_NCX(LIBCCALL libc_ntp_adjtime64)(struct timex64 *__restrict tntx)
/*[[[body:ntp_adjtime64]]]*/
{
	CRT_UNIMPLEMENTED("ntp_adjtime64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:ntp_adjtime64]]]*/

/*[[[head:ntp_gettime,hash:CRC-32=0x59596c4e]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.ntp_gettime") int
NOTHROW_NCX(LIBCCALL libc_ntp_gettime)(struct ntptimeval *__restrict ntv)
/*[[[body:ntp_gettime]]]*/
{
	CRT_UNIMPLEMENTED("ntp_gettime"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:ntp_gettime]]]*/

/*[[[head:ntp_gettime64,hash:CRC-32=0xfd2c51df]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_ntp_gettime64, libc_ntp_gettime);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.ntp_gettime64") int
NOTHROW_NCX(LIBCCALL libc_ntp_gettime64)(struct ntptimeval64 *__restrict ntv)
/*[[[body:ntp_gettime64]]]*/
{
	CRT_UNIMPLEMENTED("ntp_gettime64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:ntp_gettime64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x68ec3c1c]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(adjtimex, libc_adjtimex);
DEFINE_PUBLIC_WEAK_ALIAS(__adjtimex, libc_adjtimex);
DEFINE_PUBLIC_WEAK_ALIAS(ntp_gettimex, libc_ntp_gettime);
DEFINE_PUBLIC_WEAK_ALIAS(ntp_adjtime, libc_ntp_adjtime);
DEFINE_PUBLIC_WEAK_ALIAS(adjtimex64, libc_adjtimex64);
DEFINE_PUBLIC_WEAK_ALIAS(ntp_adjtime64, libc_ntp_adjtime64);
DEFINE_PUBLIC_WEAK_ALIAS(ntp_gettimex64, libc_ntp_gettime64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_TIMEX_C */
