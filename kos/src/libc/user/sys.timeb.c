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
#ifndef GUARD_LIBC_USER_SYS_TIMEB_C
#define GUARD_LIBC_USER_SYS_TIMEB_C 1

#include "../api.h"
/**/

#include "../libc/errno.h"
#include "sys.timeb.h"
#include <string.h>
#include <sys/time.h>
#include <kos/syscalls.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:_ftime32,hash:CRC-32=0x1bf7dc]]]*/
/* Fill in TIMEBUF with information about the current time */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted._ftime32") void
NOTHROW_NCX(LIBCCALL libc__ftime32)(struct __timeb32 *timebuf)
/*[[[body:_ftime32]]]*/
{
	if (ftime(timebuf) != 0)
		memset(timebuf, 0, sizeof(*timebuf));
}
/*[[[end:_ftime32]]]*/

/*[[[head:_ftime64,hash:CRC-32=0x6f7c2c7]]]*/
/* Fill in TIMEBUF with information about the current time */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc__ftime64, libc__ftime32);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted._ftime64") void
NOTHROW_NCX(LIBCCALL libc__ftime64)(struct __timeb64 *timebuf)
/*[[[body:_ftime64]]]*/
{
	if (ftime64(timebuf) != 0)
		memset(timebuf, 0, sizeof(*timebuf));
}
#endif /* MAGIC:alias */
/*[[[end:_ftime64]]]*/

/*[[[head:_ftime32_s,hash:CRC-32=0x676e05ac]]]*/
/* Fill in TIMEBUF with information about the current time */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted._ftime32_s") errno_t
NOTHROW_NCX(LIBCCALL libc__ftime32_s)(struct __timeb32 *timebuf)
/*[[[body:_ftime32_s]]]*/
{
	if (ftime(timebuf) != 0)
		return libc_geterrno();
	return EOK;
}
/*[[[end:_ftime32_s]]]*/

/*[[[head:DOS$_ftime32_s,hash:CRC-32=0xc9400339]]]*/
/* Fill in TIMEBUF with information about the current time */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._ftime32_s") errno_t
NOTHROW_NCX(LIBDCALL libd__ftime32_s)(struct __timeb32 *timebuf)
/*[[[body:DOS$_ftime32_s]]]*/
{
	if (ftime(timebuf) != 0)
		return libd_geterrno();
	return EOK;
}
/*[[[end:DOS$_ftime32_s]]]*/

/*[[[head:_ftime64_s,hash:CRC-32=0xf70724a5]]]*/
/* Fill in TIMEBUF with information about the current time */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc__ftime64_s, libc__ftime32_s);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted._ftime64_s") errno_t
NOTHROW_NCX(LIBCCALL libc__ftime64_s)(struct __timeb64 *timebuf)
/*[[[body:_ftime64_s]]]*/
{
	if (ftime64(timebuf) != 0)
		return libc_geterrno();
	return EOK;
}
#endif /* MAGIC:alias */
/*[[[end:_ftime64_s]]]*/

/*[[[head:DOS$_ftime64_s,hash:CRC-32=0x134b62dd]]]*/
/* Fill in TIMEBUF with information about the current time */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libd__ftime64_s, libd__ftime32_s);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.unsorted._ftime64_s") errno_t
NOTHROW_NCX(LIBDCALL libd__ftime64_s)(struct __timeb64 *timebuf)
/*[[[body:DOS$_ftime64_s]]]*/
{
	if (ftime64(timebuf) != 0)
		return libd_geterrno();
	return EOK;
}
#endif /* MAGIC:alias */
/*[[[end:DOS$_ftime64_s]]]*/

/*[[[head:ftime,hash:CRC-32=0x545ff154]]]*/
/* Fill in TIMEBUF with information about the current time */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.ftime") int
NOTHROW_NCX(LIBCCALL libc_ftime)(struct timeb *timebuf)
/*[[[body:ftime]]]*/
{
#ifdef __NR_ftime
	errno_t error;
	error = sys_ftime(timebuf);
	return libc_seterrno_syserr(error);
#else /* __NR_ftime */
	struct timeval tv;
	struct timezone tz;
	int result;
	result = gettimeofday(&tv, &tz);
	if likely(result == 0) {
		timebuf->dstflag  = tz.tz_dsttime;
		timebuf->timezone = tz.tz_minuteswest;
		timebuf->millitm  = tv.tv_usec / 1000;
		timebuf->time     = tv.tv_sec;
	}
	return result;
#endif /* !__NR_ftime */
}
/*[[[end:ftime]]]*/

/*[[[head:ftime64,hash:CRC-32=0xe6d2664f]]]*/
/* Fill in TIMEBUF with information about the current time */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_ftime64, libc_ftime);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.ftime64") int
NOTHROW_NCX(LIBCCALL libc_ftime64)(struct timeb64 *timebuf)
/*[[[body:ftime64]]]*/
{
	struct timeval64 tv;
	struct timezone tz;
	int result;
	result = gettimeofday64(&tv, &tz);
	if likely(result == 0) {
		timebuf->dstflag  = tz.tz_dsttime;
		timebuf->timezone = tz.tz_minuteswest;
		timebuf->millitm  = tv.tv_usec / 1000;
		timebuf->time     = tv.tv_sec;
	}
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:ftime64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x4cdbeeb0]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(_ftime32, libc__ftime32);
DEFINE_PUBLIC_WEAK_ALIAS(_ftime64, libc__ftime64);
DEFINE_PUBLIC_WEAK_ALIAS(_ftime32_s, libc__ftime32_s);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_ftime32_s, libd__ftime32_s);
DEFINE_PUBLIC_WEAK_ALIAS(_ftime64_s, libc__ftime64_s);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_ftime64_s, libd__ftime64_s);
DEFINE_PUBLIC_WEAK_ALIAS(ftime, libc_ftime);
DEFINE_PUBLIC_WEAK_ALIAS(ftime64, libc_ftime64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_TIMEB_C */
