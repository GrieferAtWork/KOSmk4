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
#ifndef GUARD_LIBC_USER_STRING_C
#define GUARD_LIBC_USER_STRING_C 1

#include "../api.h"
/**/

#include <parts/dos/errno.h>

#include <assert.h>
#include <errno.h>
#include <malloc.h>
#include <signal.h>
#include <string.h>

#include "../libc/errno.h"
#include "malloc.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

DECL_BEGIN


DEFINE_PUBLIC_ALIAS(memcasemem0_l, libc_memcasemem0_l);
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.locale.memory.memcasemem0_l") void *
NOTHROW_NCX(LIBCCALL libc_memcasemem0_l)(void const *haystack, size_t haystacklen,
                                         void const *needle, size_t needlelen,
                                         locale_t locale) {
	byte_t *candidate, marker;
	byte_t *hayend;
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
	haystacklen -= (needlelen - 1);
	marker       = tolower_l(*(byte_t *)needle, locale);
	hayend       = (byte_t *)haystack + haystacklen;
	for (;;) {
		for (candidate = (byte_t *)haystack; candidate < hayend; ++candidate) {
			byte_t b = *candidate;
			if (b == marker || tolower_l(b, locale) == marker)
				goto got_candidate;
		}
		break;
got_candidate:
		if (memcasecmp_l(candidate, needle, needlelen, locale) == 0)
			return (void *)candidate;
		++candidate;
		haystacklen = ((byte_t *)haystack + haystacklen) - candidate;
		haystack    = (void const *)candidate;
	}
	return NULL;
}

DEFINE_PUBLIC_ALIAS(memcasemem0, libc_memcasemem0);
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.unicode.static.memory.memcasemem0") void *
NOTHROW_NCX(LIBCCALL libc_memcasemem0)(void const *haystack, size_t haystacklen,
                                       void const *needle, size_t needlelen) {
	byte_t *candidate, marker;
	byte_t *hayend;
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
	haystacklen -= (needlelen - 1);
	marker       = tolower(*(byte_t *)needle);
	hayend       = (byte_t *)haystack + haystacklen;
	for (;;) {
		for (candidate = (byte_t *)haystack; candidate < hayend; ++candidate) {
			byte_t b = *candidate;
			if (b == marker || tolower(b) == marker)
				goto got_candidate;
		}
		break;
got_candidate:
		if (memcasecmp(candidate, needle, needlelen) == 0)
			return (void *)candidate;
		++candidate;
		haystacklen = ((byte_t *)haystack + haystacklen) - candidate;
		haystack    = (void const *)candidate;
	}
	return NULL;
}

DEFINE_PUBLIC_ALIAS(memmem0, libc_memmem0);
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memmem0") void *
NOTHROW_NCX(LIBCCALL libc_memmem0)(void const *haystack, size_t haystacklen,
                                   void const *needle, size_t needlelen) {
	byte_t *candidate, marker;
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
	haystacklen -= (needlelen - 1);
	marker       = *(byte_t *)needle;
	while ((candidate = (byte_t *)memchr(haystack, marker, haystacklen)) != NULL) {
		if (memcmp(candidate, needle, needlelen) == 0)
			return (void *)candidate;
		++candidate;
		haystacklen = ((byte_t *)haystack + haystacklen) - candidate;
		haystack    = (void const *)candidate;
	}
	return NULL;
}

DEFINE_PUBLIC_ALIAS(memrmem0, libc_memrmem0);
INTERN WUNUSED ATTR_PURE NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.string.memory.memrmem0") void *
NOTHROW_NCX(LIBCCALL libc_memrmem0)(void const *haystack, size_t haystacklen,
                                    void const *needle, size_t needlelen) {
	byte_t *candidate, marker;
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
	haystacklen -= needlelen - 1;
	marker = *(uint8_t *)needle;
	while ((candidate = (byte_t *)memrchr(haystack, marker, haystacklen)) != NULL) {
		if (memcmp(candidate, needle, needlelen) == 0)
			return (void *)candidate;
		haystacklen = (size_t)(candidate - (byte_t *)haystack);
	}
	return NULL;
}


/*[[[start:implementation]]]*/

/* These 2 functions are implemented in libc/errno.c */
/*[[[skip:libc_strerror_s]]]*/
/*[[[skip:libc_strerrorname_s]]]*/


#ifndef sys_siglist
#undef _sys_siglist
#ifndef ____p_sys_siglist_defined
#define ____p_sys_siglist_defined 1
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED __ATTR_RETNONNULL,char const *const *,__NOTHROW_NCX,__p_sys_siglist,(void),())
#endif /* !____p_sys_siglist_defined */
#define _sys_siglist  __p_sys_siglist()
#define sys_siglist   __p_sys_siglist()
#endif /* !sys_siglist */

/*[[[head:libc_strsignal_s,hash:CRC-32=0x4ff1fbbd]]]*/
INTERN ATTR_SECTION(".text.crt.errno") ATTR_CONST WUNUSED char const *
NOTHROW(LIBCCALL libc_strsignal_s)(int signum)
/*[[[body:libc_strsignal_s]]]*/
{
	if unlikely(signum >= NSIG)
		return NULL;
	return sys_siglist[signum];
}
/*[[[end:libc_strsignal_s]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x9710ba89]]]*/
DEFINE_PUBLIC_ALIAS(strsignal_s, libc_strsignal_s);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_STRING_C */
