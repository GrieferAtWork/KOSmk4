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
#ifndef GUARD_LIBC_USER_STRING_C
#define GUARD_LIBC_USER_STRING_C 1

#include "../api.h"
/**/

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <malloc.h>
#include <signal.h>
#include <string.h>

#include "../libc/compat.h"
#include "../libc/errno.h"
#include "malloc.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

DECL_BEGIN

/* TODO: Unify this function with "user/signal.c" */
LOCAL int LIBCCALL
libc_signo_dos2kos(int dos_signo) {
	if (dos_signo == DOS_SIGABRT)
		return SIGABRT;
	return dos_signo;
}



/* TODO: Declare these functions through magic
 * -> Simply use the [[ignore]] annotation to hide these from headers! */
DEFINE_PUBLIC_ALIAS(memcasemem0_l, libc_memcasemem0_l);
INTERN ATTR_PURE WUNUSED ATTR_SECTION(".text.crt.unicode.locale.memory") NONNULL((1, 3)) void *
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
INTERN ATTR_PURE WUNUSED ATTR_SECTION(".text.crt.unicode.static.memory") NONNULL((1, 3)) void *
NOTHROW_NCX(LIBCCALL libc_memcasemem0)(void const *haystack, size_t haystacklen,
                                       void const *needle, size_t needlelen) {
	byte_t *candidate, marker;
	byte_t *hayend;
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
	haystacklen -= (needlelen - 1);
	marker       = (byte_t)tolower(*(byte_t *)needle);
	hayend       = (byte_t *)haystack + haystacklen;
	for (;;) {
		for (candidate = (byte_t *)haystack; candidate < hayend; ++candidate) {
			byte_t b = *candidate;
			if (b == marker || (byte_t)tolower(b) == marker)
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
INTERN ATTR_PURE WUNUSED ATTR_SECTION(".text.crt.string.memory") NONNULL((1, 3)) void *
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
INTERN ATTR_PURE WUNUSED ATTR_SECTION(".text.crt.string.memory") NONNULL((1, 3)) void *
NOTHROW_NCX(LIBCCALL libc_memrmem0)(void const *haystack, size_t haystacklen,
                                    void const *needle, size_t needlelen) {
	byte_t *candidate, marker;
	if unlikely(!needlelen || needlelen > haystacklen)
		return NULL;
	haystacklen -= needlelen - 1;
	marker = *(uint8_t const *)needle;
	while ((candidate = (byte_t *)memrchr(haystack, marker, haystacklen)) != NULL) {
		if (memcmp(candidate, needle, needlelen) == 0)
			return (void *)candidate;
		haystacklen = (size_t)(candidate - (byte_t *)haystack);
	}
	return NULL;
}



PRIVATE ATTR_SECTION(".rodata.crt.errno")
struct ATTR_PACKED strsignal_names_db_struct {
#define S(id, msg)                              \
	char name_##id[sizeof(#id) / sizeof(char)]; \
	char mesg_##id[sizeof(msg) / sizeof(char)];
#include "../libc/sys_siglist.def"
#undef S
} const strsignal_names_db = {
#define S(id, msg)          \
	/* .name_##id = */ #id, \
	/* .mesg_##id = */ msg,
#include "../libc/sys_siglist.def"
#undef S
};

typedef u16 strsignal_offset_t;
STATIC_ASSERT(sizeof(strsignal_names_db) <= 0x10000);

PRIVATE ATTR_SECTION(".rodata.crt.errno")
strsignal_offset_t const strsignal_offsets_db[NSIG] = {
#define S(id, msg)  [SIG##id] = offsetof(struct strsignal_names_db_struct, name_##id),
#define S_UNDEF(id) [id] = (sizeof(strsignal_names_db) - 1),
#include "../libc/sys_siglist.def"
#undef S_UNDEF
#undef S
};


/*[[[head:libd_sigabbrev_np,hash:CRC-32=0xc83b79a2]]]*/
/* >> sigabbrev_np(3)
 * Return the name of a given signal, _without_ the leading `SIG*' prefix.
 * When the given `signum' isn't  recognized, `NULL' is returned  instead. */
INTERN ATTR_SECTION(".text.crt.dos.errno") ATTR_CONST WUNUSED char const *
NOTHROW(LIBDCALL libd_sigabbrev_np)(signo_t signum)
/*[[[body:libd_sigabbrev_np]]]*/
{
	signum = libc_signo_dos2kos(signum);
	return libc_sigabbrev_np(signum);
}
/*[[[end:libd_sigabbrev_np]]]*/

/*[[[head:libc_sigabbrev_np,hash:CRC-32=0x4b4864f7]]]*/
/* >> sigabbrev_np(3)
 * Return the name of a given signal, _without_ the leading `SIG*' prefix.
 * When the given `signum' isn't  recognized, `NULL' is returned  instead. */
INTERN ATTR_SECTION(".text.crt.errno") ATTR_CONST WUNUSED char const *
NOTHROW(LIBCCALL libc_sigabbrev_np)(signo_t signum)
/*[[[body:libc_sigabbrev_np]]]*/
{
	char const *result;
	if ((unsigned int)signum >= COMPILER_LENOF(strsignal_offsets_db))
		return NULL;
	result = (char const *)((byte_t const *)&strsignal_names_db +
	                        strsignal_offsets_db[(unsigned int)signum]);
	if unlikely(!*result)
		result = NULL;
	return result;
}
/*[[[end:libc_sigabbrev_np]]]*/

/*[[[head:libd_sigdescr_np,hash:CRC-32=0x4e882862]]]*/
/* >> sigdescr_np(3)
 * Return a description for the given signal.
 * If the given `signum' isn't recognized, return `NULL' instead. */
INTERN ATTR_SECTION(".text.crt.dos.errno") ATTR_CONST WUNUSED char const *
NOTHROW(LIBDCALL libd_sigdescr_np)(signo_t signum)
/*[[[body:libd_sigdescr_np]]]*/
{
	signum = libc_signo_dos2kos(signum);
	return libc_sigdescr_np(signum);
}
/*[[[end:libd_sigdescr_np]]]*/

/*[[[head:libc_sigdescr_np,hash:CRC-32=0x5d22cb1a]]]*/
/* >> sigdescr_np(3)
 * Return a description for the given signal.
 * If the given `signum' isn't recognized, return `NULL' instead. */
INTERN ATTR_SECTION(".text.crt.errno") ATTR_CONST WUNUSED char const *
NOTHROW(LIBCCALL libc_sigdescr_np)(signo_t signum)
/*[[[body:libc_sigdescr_np]]]*/
{
	char const *result;
	result = libc_sigabbrev_np(signum);
	if (result != NULL)
		result = strend(result) + 1;
	return result;
}
/*[[[end:libc_sigdescr_np]]]*/





/*[[[start:exports,hash:CRC-32=0xa60227ea]]]*/
DEFINE_PUBLIC_ALIAS(DOS$signalname, libd_sigabbrev_np);
DEFINE_PUBLIC_ALIAS(DOS$sigabbrev_np, libd_sigabbrev_np);
DEFINE_PUBLIC_ALIAS(signalname, libc_sigabbrev_np);
DEFINE_PUBLIC_ALIAS(sigabbrev_np, libc_sigabbrev_np);
DEFINE_PUBLIC_ALIAS(DOS$sigdescr_np, libd_sigdescr_np);
DEFINE_PUBLIC_ALIAS(sigdescr_np, libc_sigdescr_np);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_STRING_C */
