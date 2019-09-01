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
#include "sys.timeb.h"
#include <string.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:_ftime32,hash:0x89a38007]]]*/
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

/*[[[head:_ftime64,hash:0xe63cc1c8]]]*/
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

/*[[[head:_ftime32_s,hash:0x702cba31]]]*/
/* Fill in TIMEBUF with information about the current time */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted._ftime32_s") errno_t
NOTHROW_NCX(LIBCCALL libc__ftime32_s)(struct __timeb32 *timebuf)
/*[[[body:_ftime32_s]]]*/
{
	CRT_UNIMPLEMENTED("_ftime32_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_ftime32_s]]]*/

/*[[[head:_ftime64_s,hash:0xdcbdd160]]]*/
/* Fill in TIMEBUF with information about the current time */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc__ftime64_s, libc__ftime32_s);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted._ftime64_s") errno_t
NOTHROW_NCX(LIBCCALL libc__ftime64_s)(struct __timeb64 *timebuf)
/*[[[body:_ftime64_s]]]*/
{
	CRT_UNIMPLEMENTED("_ftime64_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:alias */
/*[[[end:_ftime64_s]]]*/

/*[[[head:ftime,hash:0x83b2f66c]]]*/
/* Fill in TIMEBUF with information about the current time */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.ftime") int
NOTHROW_NCX(LIBCCALL libc_ftime)(struct timeb *timebuf)
/*[[[body:ftime]]]*/
{
	CRT_UNIMPLEMENTED("ftime"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:ftime]]]*/

/*[[[head:ftime64,hash:0x1d629c0]]]*/
/* Fill in TIMEBUF with information about the current time */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_ftime64, libc_ftime);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.ftime64") int
NOTHROW_NCX(LIBCCALL libc_ftime64)(struct timeb64 *timebuf)
/*[[[body:ftime64]]]*/
{
	CRT_UNIMPLEMENTED("ftime64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:ftime64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0xb0ac4777]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(_ftime32, libc__ftime32);
DEFINE_PUBLIC_WEAK_ALIAS(_ftime64, libc__ftime64);
DEFINE_PUBLIC_WEAK_ALIAS(_ftime32_s, libc__ftime32_s);
DEFINE_PUBLIC_WEAK_ALIAS(_ftime64_s, libc__ftime64_s);
DEFINE_PUBLIC_WEAK_ALIAS(ftime, libc_ftime);
DEFINE_PUBLIC_WEAK_ALIAS(ftime64, libc_ftime64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_TIMEB_C */
