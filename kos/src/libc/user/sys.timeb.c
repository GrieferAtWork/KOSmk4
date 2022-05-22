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
#ifndef GUARD_LIBC_USER_SYS_TIMEB_C
#define GUARD_LIBC_USER_SYS_TIMEB_C 1

#include "../api.h"
/**/

#include "sys.timeb.h"
#include <string.h>
#include <sys/time.h>
#include <kos/syscalls.h>

DECL_BEGIN

/*[[[head:libc__ftime32,hash:CRC-32=0x41268b9c]]]*/
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_OUT(1) void
NOTHROW_NCX(LIBCCALL libc__ftime32)(struct timeb32 *timebuf)
/*[[[body:libc__ftime32]]]*/
{
	if (ftime(timebuf) != 0)
		bzero(timebuf, sizeof(*timebuf));
}
/*[[[end:libc__ftime32]]]*/

/*[[[head:libc__ftime64,hash:CRC-32=0x6eb92f19]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc__ftime64, libc__ftime32);
#else /* MAGIC:alias */
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_OUT(1) void
NOTHROW_NCX(LIBCCALL libc__ftime64)(struct timeb64 *timebuf)
/*[[[body:libc__ftime64]]]*/
{
	if (ftime64(timebuf) != 0)
		bzero(timebuf, sizeof(*timebuf));
}
#endif /* MAGIC:alias */
/*[[[end:libc__ftime64]]]*/

/*[[[head:libc__ftime32_s,hash:CRC-32=0x47ec2ffa]]]*/
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc__ftime32_s)(struct timeb32 *timebuf)
/*[[[body:libc__ftime32_s]]]*/
{
	if (ftime(timebuf) != 0)
		return libc_geterrno();
	return EOK;
}
/*[[[end:libc__ftime32_s]]]*/

/*[[[head:libc__ftime64_s,hash:CRC-32=0x91a9d241]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc__ftime64_s, libc__ftime32_s);
#else /* MAGIC:alias */
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc__ftime64_s)(struct timeb64 *timebuf)
/*[[[body:libc__ftime64_s]]]*/
{
	if (ftime64(timebuf) != 0)
		return libc_geterrno();
	return EOK;
}
#endif /* MAGIC:alias */
/*[[[end:libc__ftime64_s]]]*/

/*[[[head:libc_ftime,hash:CRC-32=0x92d7809e]]]*/
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_ftime)(struct timeb *timebuf)
/*[[[body:libc_ftime]]]*/
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
/*[[[end:libc_ftime]]]*/

/*[[[head:libc_ftime64,hash:CRC-32=0x40235ff8]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_ftime64, libc_ftime);
#else /* MAGIC:alias */
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_ftime64)(struct timeb64 *timebuf)
/*[[[body:libc_ftime64]]]*/
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
/*[[[end:libc_ftime64]]]*/





/*[[[start:exports,hash:CRC-32=0xc93952b6]]]*/
DEFINE_PUBLIC_ALIAS(_ftime, libc__ftime32);
DEFINE_PUBLIC_ALIAS(_ftime32, libc__ftime32);
DEFINE_PUBLIC_ALIAS(_ftime64, libc__ftime64);
DEFINE_PUBLIC_ALIAS(_ftime32_s, libc__ftime32_s);
DEFINE_PUBLIC_ALIAS(_ftime64_s, libc__ftime64_s);
DEFINE_PUBLIC_ALIAS(ftime, libc_ftime);
DEFINE_PUBLIC_ALIAS(ftime64, libc_ftime64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_TIMEB_C */
