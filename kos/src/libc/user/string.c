/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
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


/* TODO: Declare these functions through magic
 * -> Simply use the [[ignore]] annotation to hide these from headers! */
DEFINE_PUBLIC_ALIAS(memcasemem0_l, libc_memcasemem0_l);
INTERN ATTR_PURE WUNUSED NONNULL((1, 3))
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
INTERN ATTR_PURE WUNUSED NONNULL((1, 3))
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
INTERN ATTR_PURE WUNUSED NONNULL((1, 3))
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
INTERN ATTR_PURE WUNUSED NONNULL((1, 3))
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


PRIVATE ATTR_SECTION(".rodata.crt.errno")
struct ATTR_PACKED strerror_names_db_struct {
#define E(id, message)                          \
	char name_##id[sizeof(#id) / sizeof(char)]; \
	char mesg_##id[sizeof(message) / sizeof(char)];
#include "../libc/sys_errlist.def"
#undef E
} const strerror_names_db = {
#define E(id, message)      \
	/* .name_##id = */ #id, \
	/* .mesg_##id = */ message,
#include "../libc/sys_errlist.def"
#undef E
};

typedef u16 strerror_offset_t;
STATIC_ASSERT(sizeof(strerror_names_db) <= 0x10000);

PRIVATE ATTR_SECTION(".rodata.crt.errno") strerror_offset_t const strerror_offsets_db[__ECOUNT] = {
#define E(id, message) offsetof(struct strerror_names_db_struct, name_##id),
#include "../libc/sys_errlist.def"
#undef E
};



/*[[[head:libc_strerrorname_s,hash:CRC-32=0xfe8886ba]]]*/
INTERN ATTR_SECTION(".text.crt.errno") ATTR_CONST WUNUSED char const *
NOTHROW(LIBCCALL libc_strerrorname_s)(errno_t errnum)
/*[[[body:libc_strerrorname_s]]]*/
{
	char const *result;
	if ((unsigned int)errnum >= COMPILER_LENOF(strerror_offsets_db))
		return NULL;
	result = (char const *)((byte_t const *)&strerror_names_db +
	                        strerror_offsets_db[(unsigned int)errnum]);
	return result;
}
/*[[[end:libc_strerrorname_s]]]*/

/*[[[head:libd_strerrorname_s,hash:CRC-32=0x6b8637d7]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno") ATTR_CONST WUNUSED char const *
NOTHROW(LIBDCALL libd_strerrorname_s)(errno_t errnum)
/*[[[body:libd_strerrorname_s]]]*/
{
	/* Special handling for a hand full of errno
	 * values that don't have KOS equivalents. */
	switch (errnum) {
	case DOS_STRUNCATE:
		return "STRUNCATE\0" "Truncated";
	case DOS_EOTHER:
		return "EOTHER\0" "Other";
	default:
		break;
	}
	errnum = libd_errno_dos2kos(errnum);
	return libc_strerrorname_s(errnum);
}
/*[[[end:libd_strerrorname_s]]]*/

/*[[[head:libc_strerror_s,hash:CRC-32=0x68ec1d4d]]]*/
INTERN ATTR_SECTION(".text.crt.errno") ATTR_CONST WUNUSED char const *
NOTHROW(LIBCCALL libc_strerror_s)(errno_t errnum)
/*[[[body:libc_strerror_s]]]*/
{
	char const *result;
	result = libc_strerrorname_s(errnum);
	if (result)
		result = strend(result) + 1;
	return result;
}
/*[[[end:libc_strerror_s]]]*/

/*[[[head:libd_strerror_s,hash:CRC-32=0xa1dfa641]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno") ATTR_CONST WUNUSED char const *
NOTHROW(LIBDCALL libd_strerror_s)(errno_t errnum)
/*[[[body:libd_strerror_s]]]*/
{
	char const *result;
	result = libd_strerrorname_s(errnum);
	if (result)
		result = strend(result) + 1;
	return result;
}
/*[[[end:libd_strerror_s]]]*/


PRIVATE ATTR_SECTION(".rodata.crt.errno")
struct ATTR_PACKED strsignal_names_db_struct {
#define S(id, msg) char name_##id[sizeof(#id) / sizeof(char)];
#include "../libc/sys_siglist.def"
#undef S
} const strsignal_names_db = {
#define S(id, msg) /* .name_##id = */ #id,
#include "../libc/sys_siglist.def"
#undef S
};

typedef u8 strsignal_offset_t;
STATIC_ASSERT(sizeof(strsignal_names_db) <= 0x100);

PRIVATE ATTR_SECTION(".rodata.crt.errno")
strsignal_offset_t const strsignal_offsets_db[NSIG] = {
#define S(id, msg)  offsetof(struct strsignal_names_db_struct, name_##id),
#define S_UNDEF(id) (sizeof(strsignal_names_db) - 1),
#include "../libc/sys_siglist.def"
#undef S_UNDEF
#undef S
};


/*[[[head:libc_strsignal_s,hash:CRC-32=0x889d7ce2]]]*/
INTERN ATTR_SECTION(".text.crt.errno") ATTR_CONST WUNUSED char const *
NOTHROW(LIBCCALL libc_strsignal_s)(signo_t signum)
/*[[[body:libc_strsignal_s]]]*/
{
	char const *result;
	if ((unsigned int)signum >= COMPILER_LENOF(strsignal_offsets_db))
		return NULL;
	result = (char const *)((byte_t const *)&strsignal_names_db +
	                        strsignal_offsets_db[(unsigned int)signum]);
	return result;
}
/*[[[end:libc_strsignal_s]]]*/



/* TODO: Unify this function with "user/signal.c" */
LOCAL int LIBCCALL
libc_signo_dos2kos(int dos_signo) {
	if (dos_signo == DOS_SIGABRT)
		return SIGABRT;
	return dos_signo;
}


/*[[[head:libd_strsignal_s,hash:CRC-32=0x81e20372]]]*/
INTERN ATTR_SECTION(".text.crt.dos.errno") ATTR_CONST WUNUSED char const *
NOTHROW(LIBDCALL libd_strsignal_s)(signo_t signum)
/*[[[body:libd_strsignal_s]]]*/
{
	signum = libc_signo_dos2kos(signum);
	return libc_strsignal_s(signum);
}
/*[[[end:libd_strsignal_s]]]*/




/*[[[start:exports,hash:CRC-32=0xd90888cf]]]*/
DEFINE_PUBLIC_ALIAS(DOS$strerror_s, libd_strerror_s);
DEFINE_PUBLIC_ALIAS(strerror_s, libc_strerror_s);
DEFINE_PUBLIC_ALIAS(DOS$strerrorname_s, libd_strerrorname_s);
DEFINE_PUBLIC_ALIAS(strerrorname_s, libc_strerrorname_s);
DEFINE_PUBLIC_ALIAS(DOS$strsignal_s, libd_strsignal_s);
DEFINE_PUBLIC_ALIAS(strsignal_s, libc_strsignal_s);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_STRING_C */
