/* HASH CRC-32:0xed8bf200 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_WCTYPE_C
#define GUARD_LIBC_AUTO_WCTYPE_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "wctype.h"
#include "../user/ctype.h"
#include "string.h"
#include "../user/unicode.h"
#include "../user/wchar.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <bits/crt/wctype.h>
/* >> iswcntrl(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswcntrl)(wint16_t wc) {

	return __crt_iswcntrl(wc);



}
#include <bits/crt/wctype.h>
/* >> iswcntrl(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswcntrl)(wint32_t wc) {

	return __crt_iswcntrl(wc);



}
#include <bits/crt/wctype.h>
/* >> iswspace(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswspace)(wint16_t wc) {

	return __crt_iswspace(wc);



}
#include <bits/crt/wctype.h>
/* >> iswspace(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswspace)(wint32_t wc) {

	return __crt_iswspace(wc);



}
#include <bits/crt/wctype.h>
/* >> iswupper(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswupper)(wint16_t wc) {

	return __crt_iswupper(wc);



}
#include <bits/crt/wctype.h>
/* >> iswupper(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswupper)(wint32_t wc) {

	return __crt_iswupper(wc);



}
#include <bits/crt/wctype.h>
/* >> iswlower(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswlower)(wint16_t wc) {

	return __crt_iswlower(wc);



}
#include <bits/crt/wctype.h>
/* >> iswlower(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswlower)(wint32_t wc) {

	return __crt_iswlower(wc);



}
#include <bits/crt/wctype.h>
/* >> iswalpha(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswalpha)(wint16_t wc) {

	return __crt_iswalpha(wc);



}
#include <bits/crt/wctype.h>
/* >> iswalpha(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswalpha)(wint32_t wc) {

	return __crt_iswalpha(wc);



}
#include <bits/crt/wctype.h>
/* >> iswdigit(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswdigit)(wint16_t wc) {

	return __crt_iswdigit(wc);



}
#include <bits/crt/wctype.h>
/* >> iswdigit(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswdigit)(wint32_t wc) {

	return __crt_iswdigit(wc);



}
#include <bits/crt/wctype.h>
/* >> iswxdigit(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswxdigit)(wint16_t wc) {

	return __crt_iswxdigit(wc);



}
#include <bits/crt/wctype.h>
/* >> iswxdigit(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswxdigit)(wint32_t wc) {

	return __crt_iswxdigit(wc);



}
#include <bits/crt/wctype.h>
/* >> iswalnum(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswalnum)(wint16_t wc) {

	return __crt_iswalnum(wc);



}
#include <bits/crt/wctype.h>
/* >> iswalnum(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswalnum)(wint32_t wc) {

	return __crt_iswalnum(wc);



}
#include <bits/crt/wctype.h>
/* >> iswpunct(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswpunct)(wint16_t wc) {

	return __crt_iswpunct(wc);



}
#include <bits/crt/wctype.h>
/* >> iswpunct(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswpunct)(wint32_t wc) {

	return __crt_iswpunct(wc);



}
#include <bits/crt/wctype.h>
/* >> iswgraph(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswgraph)(wint16_t wc) {

	return __crt_iswgraph(wc);



}
#include <bits/crt/wctype.h>
/* >> iswgraph(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswgraph)(wint32_t wc) {

	return __crt_iswgraph(wc);



}
#include <bits/crt/wctype.h>
/* >> iswprint(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswprint)(wint16_t wc) {

	return __crt_iswprint(wc);



}
#include <bits/crt/wctype.h>
/* >> iswprint(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswprint)(wint32_t wc) {

	return __crt_iswprint(wc);



}
#include <bits/crt/wctype.h>
/* >> towlower(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED wint16_t
NOTHROW(LIBDCALL libd_towlower)(wint16_t wc) {

	return __crt_towlower(wc);



}
#include <bits/crt/wctype.h>
/* >> towlower(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED wint32_t
NOTHROW(LIBKCALL libc_towlower)(wint32_t wc) {

	return __crt_towlower(wc);



}
#include <bits/crt/wctype.h>
/* >> towupper(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED wint16_t
NOTHROW(LIBDCALL libd_towupper)(wint16_t wc) {

	return __crt_towupper(wc);



}
#include <bits/crt/wctype.h>
/* >> towupper(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED wint32_t
NOTHROW(LIBKCALL libc_towupper)(wint32_t wc) {

	return __crt_towupper(wc);



}
#include <bits/crt/wctype.h>
/* >> iswblank(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswblank)(wint16_t wc) {

	return __crt_iswblank(wc);



}
#include <bits/crt/wctype.h>
/* >> iswblank(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswblank)(wint32_t wc) {

	return __crt_iswblank(wc);



}
#include <bits/crt/unicode.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_PURE WUNUSED ATTR_IN(1) wctrans_t
NOTHROW_NCX(LIBCCALL libc_wctrans)(char const *prop) {
	struct wctrans_entry {
		char     we_name[8]; /* Name (including the leading "to") */
		uint16_t we_offset;  /* Offset to `int32_t' field in `struct __unitraits' */
	};
	static struct wctrans_entry const entries[] = {
		{ "tolower", offsetof(struct __unitraits, __ut_lower) },
		{ "toupper", offsetof(struct __unitraits, __ut_upper) },
		{ "totitle", offsetof(struct __unitraits, __ut_title) }, /* Kos extension! */
	};
	unsigned int i;
	for (i = 0; i < COMPILER_LENOF(entries); ++i) {
		if (libc_strcmp(prop, entries[i].we_name) == 0)
			return (wctrans_t)(uintptr_t)entries[i].we_offset;
	}
	return (wctrans_t)0;
}
#include <bits/crt/unicode.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED wint16_t
NOTHROW(LIBDCALL libd_towctrans)(wint16_t wc,
                                 wctrans_t desc) {
	struct __unitraits const *traits = libc___unicode_descriptor(wc);
	return wc + *((s32 const *)traits + (uintptr_t)desc);
}
#include <bits/crt/unicode.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED wint32_t
NOTHROW(LIBKCALL libc_towctrans)(wint32_t wc,
                                 wctrans_t desc) {
	struct __unitraits const *traits = libc___unicode_descriptor(wc);
	return wc + *((s32 const *)traits + (uintptr_t)desc);
}
#include <bits/crt/unicode.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_PURE WUNUSED ATTR_IN(1) wctype_t
NOTHROW_NCX(LIBCCALL libc_wctype)(char const *prop) {
	struct wctype_entry {
		char     we_name[8]; /* Name (with leading "is" stripped) */
		uint16_t we_flags;   /* Flags that must be set. */
	};
	static struct wctype_entry const entries[] = {
		{ "cntrl",   __UNICODE_ISCNTRL },
		{ "space",   __UNICODE_ISSPACE },
		{ "lower",   __UNICODE_ISLOWER },
		{ "upper",   __UNICODE_ISUPPER },
		{ "alpha",   __UNICODE_ISALPHA },
		{ "digit",   __UNICODE_ISDIGIT },
		{ "xdigit",  __UNICODE_ISXDIGIT },
		{ "alnum",   __UNICODE_ISALNUM },
		{ "punct",   __UNICODE_ISPUNCT },
		{ "graph",   __UNICODE_ISGRAPH },
		{ "print",   __UNICODE_ISPRINT },
		{ "blank",   __UNICODE_ISBLANK },
		/* All of the following are KOS extensions! */
		{ "tab",     __UNICODE_ISTAB },
		{ "white",   __UNICODE_ISWHITE },
		{ "empty",   __UNICODE_ISEMPTY },
		{ "lf",      __UNICODE_ISLF },
		{ "hex",     __UNICODE_ISHEX },
		{ "title",   __UNICODE_ISTITLE },
		{ "numeric", __UNICODE_ISNUMERIC },
		{ "symstrt", __UNICODE_ISSYMSTRT },
		{ "symcont", __UNICODE_ISSYMCONT },
	};
	unsigned int i;
	for (i = 0; i < COMPILER_LENOF(entries); ++i) {
		if (libc_strcmp(prop, entries[i].we_name) == 0)
			return entries[i].we_flags;
	}
	return 0;
}
#include <bits/crt/unicode.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswctype)(wint16_t wc,
                                wctype_t desc) {
	struct __unitraits const *traits = libc___unicode_descriptor(wc);
	return (int)(traits->__ut_flags & (uint16_t)desc);
}
#include <bits/crt/unicode.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswctype)(wint32_t wc,
                                wctype_t desc) {
	struct __unitraits const *traits = libc___unicode_descriptor(wc);
	return (int)(traits->__ut_flags & (uint16_t)desc);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswascii)(wint16_t wc) {
	return wc >= 0 && wc <= 0x7f;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswascii)(wint32_t wc) {
	return wc >= 0 && wc <= 0x7f;
}
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libd_iswcntrl_l,libd_iswcntrl,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswcntrl_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswcntrl_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswcntrl(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libc_iswcntrl_l,libc_iswcntrl,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
#else /* __LIBKCALL_CALLER_CLEANUP */
/* >> iswcntrl_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBKCALL libc_iswcntrl_l)(wint32_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_iswcntrl(ch);
}
#endif /* !__LIBKCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libd_iswspace_l,libd_iswspace,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswspace_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswspace_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswspace(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libc_iswspace_l,libc_iswspace,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
#else /* __LIBKCALL_CALLER_CLEANUP */
/* >> iswspace_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBKCALL libc_iswspace_l)(wint32_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_iswspace(ch);
}
#endif /* !__LIBKCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libd_iswupper_l,libd_iswupper,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswupper_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswupper_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswupper(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libc_iswupper_l,libc_iswupper,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
#else /* __LIBKCALL_CALLER_CLEANUP */
/* >> iswupper_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBKCALL libc_iswupper_l)(wint32_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_iswupper(ch);
}
#endif /* !__LIBKCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libd_iswlower_l,libd_iswlower,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswlower_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswlower_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswlower(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libc_iswlower_l,libc_iswlower,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
#else /* __LIBKCALL_CALLER_CLEANUP */
/* >> iswlower_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBKCALL libc_iswlower_l)(wint32_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_iswlower(ch);
}
#endif /* !__LIBKCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libd_iswalpha_l,libd_iswalpha,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswalpha_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswalpha_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswalpha(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libc_iswalpha_l,libc_iswalpha,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
#else /* __LIBKCALL_CALLER_CLEANUP */
/* >> iswalpha_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBKCALL libc_iswalpha_l)(wint32_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_iswalpha(ch);
}
#endif /* !__LIBKCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libd_iswdigit_l,libd_iswdigit,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswdigit_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswdigit_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswdigit(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libc_iswdigit_l,libc_iswdigit,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
#else /* __LIBKCALL_CALLER_CLEANUP */
/* >> iswdigit_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBKCALL libc_iswdigit_l)(wint32_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_iswdigit(ch);
}
#endif /* !__LIBKCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libd_iswxdigit_l,libd_iswxdigit,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswxdigit_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswxdigit_l)(wint16_t ch,
                                       locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswxdigit(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libc_iswxdigit_l,libc_iswxdigit,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
#else /* __LIBKCALL_CALLER_CLEANUP */
/* >> iswxdigit_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBKCALL libc_iswxdigit_l)(wint32_t ch,
                                       locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_iswxdigit(ch);
}
#endif /* !__LIBKCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libd_iswalnum_l,libd_iswalnum,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswalnum_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswalnum_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswalnum(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libc_iswalnum_l,libc_iswalnum,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
#else /* __LIBKCALL_CALLER_CLEANUP */
/* >> iswalnum_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBKCALL libc_iswalnum_l)(wint32_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_iswalnum(ch);
}
#endif /* !__LIBKCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libd_iswpunct_l,libd_iswpunct,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswpunct_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswpunct_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswpunct(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libc_iswpunct_l,libc_iswpunct,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
#else /* __LIBKCALL_CALLER_CLEANUP */
/* >> iswpunct_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBKCALL libc_iswpunct_l)(wint32_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_iswpunct(ch);
}
#endif /* !__LIBKCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libd_iswgraph_l,libd_iswgraph,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswgraph_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswgraph_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswgraph(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libc_iswgraph_l,libc_iswgraph,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
#else /* __LIBKCALL_CALLER_CLEANUP */
/* >> iswgraph_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBKCALL libc_iswgraph_l)(wint32_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_iswgraph(ch);
}
#endif /* !__LIBKCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libd_iswprint_l,libd_iswprint,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswprint_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswprint_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswprint(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libc_iswprint_l,libc_iswprint,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
#else /* __LIBKCALL_CALLER_CLEANUP */
/* >> iswprint_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBKCALL libc_iswprint_l)(wint32_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_iswprint(ch);
}
#endif /* !__LIBKCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libd_iswblank_l,libd_iswblank,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswblank_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswblank_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswblank(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libc_iswblank_l,libc_iswblank,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
#else /* __LIBKCALL_CALLER_CLEANUP */
/* >> iswblank_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBKCALL libc_iswblank_l)(wint32_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_iswblank(ch);
}
#endif /* !__LIBKCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libd_towlower_l,libd_towlower,ATTR_PURE WUNUSED,wint16_t,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> towlower_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED wint16_t
NOTHROW_NCX(LIBDCALL libd_towlower_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_towlower(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libc_towlower_l,libc_towlower,ATTR_PURE WUNUSED,wint32_t,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
#else /* __LIBKCALL_CALLER_CLEANUP */
/* >> towlower_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED wint32_t
NOTHROW_NCX(LIBKCALL libc_towlower_l)(wint32_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_towlower(ch);
}
#endif /* !__LIBKCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libd_towupper_l,libd_towupper,ATTR_PURE WUNUSED,wint16_t,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> towupper_l(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED wint16_t
NOTHROW_NCX(LIBDCALL libd_towupper_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_towupper(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libc_towupper_l,libc_towupper,ATTR_PURE WUNUSED,wint32_t,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
#else /* __LIBKCALL_CALLER_CLEANUP */
/* >> towupper_l(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED wint32_t
NOTHROW_NCX(LIBKCALL libc_towupper_l)(wint32_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_towupper(ch);
}
#endif /* !__LIBKCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libd_iswctype_l,libd_iswctype,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t wc, wctype_t type, locale_t locale),(wc,type,locale));
#else /* __LIBDCALL_CALLER_CLEANUP */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswctype_l)(wint16_t wc,
                                      wctype_t type,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswctype(wc, type);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libc_iswctype_l,libc_iswctype,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t wc, wctype_t type, locale_t locale),(wc,type,locale));
#else /* __LIBKCALL_CALLER_CLEANUP */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBKCALL libc_iswctype_l)(wint32_t wc,
                                      wctype_t type,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_iswctype(wc, type);
}
#endif /* !__LIBKCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libc_wctype_l,libc_wctype,WUNUSED ATTR_IN(1),wctype_t,NOTHROW_NCX,LIBCCALL,(char const *prop, locale_t locale),(prop,locale));
#else /* __LIBKCALL_CALLER_CLEANUP */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") WUNUSED ATTR_IN(1) wctype_t
NOTHROW_NCX(LIBCCALL libc_wctype_l)(char const *prop,
                                    locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_wctype(prop);
}
#endif /* !__LIBKCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libd_towctrans_l,libd_towctrans,WUNUSED,wint16_t,NOTHROW_NCX,LIBDCALL,(wint16_t wc, wctrans_t desc, locale_t locale),(wc,desc,locale));
#else /* __LIBDCALL_CALLER_CLEANUP */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") WUNUSED wint16_t
NOTHROW_NCX(LIBDCALL libd_towctrans_l)(wint16_t wc,
                                       wctrans_t desc,
                                       locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_towctrans(wc, desc);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libc_towctrans_l,libc_towctrans,WUNUSED,wint32_t,NOTHROW_NCX,LIBKCALL,(wint32_t wc, wctrans_t desc, locale_t locale),(wc,desc,locale));
#else /* __LIBKCALL_CALLER_CLEANUP */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") WUNUSED wint32_t
NOTHROW_NCX(LIBKCALL libc_towctrans_l)(wint32_t wc,
                                       wctrans_t desc,
                                       locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_towctrans(wc, desc);
}
#endif /* !__LIBKCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libc_wctrans_l,libc_wctrans,WUNUSED ATTR_IN(1),wctrans_t,NOTHROW_NCX,LIBCCALL,(char const *prop, locale_t locale),(prop,locale));
#else /* __LIBKCALL_CALLER_CLEANUP */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") WUNUSED ATTR_IN(1) wctrans_t
NOTHROW_NCX(LIBCCALL libc_wctrans_l)(char const *prop,
                                     locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_wctrans(prop);
}
#endif /* !__LIBKCALL_CALLER_CLEANUP */
#include <bits/crt/unicode.h>
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd___iswcsymf)(wint16_t wc) {

	struct __unitraits const *traits = libc___unicode_descriptor(wc);
	return (int)(traits->__ut_flags & __UNICODE_ISSYMSTRT);



}
#include <bits/crt/unicode.h>
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc___iswcsymf)(wint32_t wc) {

	struct __unitraits const *traits = libc___unicode_descriptor(wc);
	return (int)(traits->__ut_flags & __UNICODE_ISSYMSTRT);



}
#include <bits/crt/unicode.h>
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd___iswcsym)(wint16_t wc) {

	struct __unitraits const *traits = libc___unicode_descriptor(wc);
	return (int)(traits->__ut_flags & __UNICODE_ISSYMCONT);



}
#include <bits/crt/unicode.h>
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc___iswcsym)(wint32_t wc) {

	struct __unitraits const *traits = libc___unicode_descriptor(wc);
	return (int)(traits->__ut_flags & __UNICODE_ISSYMCONT);



}
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libd__iswcsymf_l,libd___iswcsymf,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t wc, locale_t locale),(wc,locale));
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.mbs") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd__iswcsymf_l)(wint16_t wc,
                                       locale_t locale) {

	COMPILER_IMPURE();
	(void)locale;
	return libd___iswcsymf(wc);



}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libc__iswcsymf_l,libc___iswcsymf,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t wc, locale_t locale),(wc,locale));
#else /* __LIBKCALL_CALLER_CLEANUP */
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.mbs") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBKCALL libc__iswcsymf_l)(wint32_t wc,
                                       locale_t locale) {

	COMPILER_IMPURE();
	(void)locale;
	return libc___iswcsymf(wc);



}
#endif /* !__LIBKCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libd__iswcsym_l,libd___iswcsym,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t wc, locale_t locale),(wc,locale));
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.mbs") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd__iswcsym_l)(wint16_t wc,
                                      locale_t locale) {

	COMPILER_IMPURE();
	(void)locale;
	return libd___iswcsym(wc);



}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libc__iswcsym_l,libc___iswcsym,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t wc, locale_t locale),(wc,locale));
#else /* __LIBKCALL_CALLER_CLEANUP */
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.mbs") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBKCALL libc__iswcsym_l)(wint32_t wc,
                                      locale_t locale) {

	COMPILER_IMPURE();
	(void)locale;
	return libc___iswcsym(wc);



}
#endif /* !__LIBKCALL_CALLER_CLEANUP */
/* >> isleadbyte(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW(LIBCCALL libc_isleadbyte)(int wc) {
	return wc >= 192 && wc <= 255;
}
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS_P(libc__isleadbyte_l,libc_isleadbyte,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(int wc, locale_t locale),(wc,locale));
#else /* __LIBKCALL_CALLER_CLEANUP */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.mbs") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__isleadbyte_l)(int wc,
                                         locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libc_isleadbyte(wc);
}
#endif /* !__LIBKCALL_CALLER_CLEANUP */
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(DOS$iswcntrl,libd_iswcntrl,ATTR_CONST WUNUSED,int,NOTHROW,LIBDCALL,(wint16_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(iswcntrl,libc_iswcntrl,ATTR_CONST WUNUSED,int,NOTHROW,LIBKCALL,(wint32_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(DOS$iswspace,libd_iswspace,ATTR_CONST WUNUSED,int,NOTHROW,LIBDCALL,(wint16_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(iswspace,libc_iswspace,ATTR_CONST WUNUSED,int,NOTHROW,LIBKCALL,(wint32_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(DOS$iswupper,libd_iswupper,ATTR_CONST WUNUSED,int,NOTHROW,LIBDCALL,(wint16_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(iswupper,libc_iswupper,ATTR_CONST WUNUSED,int,NOTHROW,LIBKCALL,(wint32_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(DOS$iswlower,libd_iswlower,ATTR_CONST WUNUSED,int,NOTHROW,LIBDCALL,(wint16_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(iswlower,libc_iswlower,ATTR_CONST WUNUSED,int,NOTHROW,LIBKCALL,(wint32_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(DOS$iswalpha,libd_iswalpha,ATTR_CONST WUNUSED,int,NOTHROW,LIBDCALL,(wint16_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(iswalpha,libc_iswalpha,ATTR_CONST WUNUSED,int,NOTHROW,LIBKCALL,(wint32_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(DOS$iswdigit,libd_iswdigit,ATTR_CONST WUNUSED,int,NOTHROW,LIBDCALL,(wint16_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(iswdigit,libc_iswdigit,ATTR_CONST WUNUSED,int,NOTHROW,LIBKCALL,(wint32_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(DOS$iswxdigit,libd_iswxdigit,ATTR_CONST WUNUSED,int,NOTHROW,LIBDCALL,(wint16_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(iswxdigit,libc_iswxdigit,ATTR_CONST WUNUSED,int,NOTHROW,LIBKCALL,(wint32_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(DOS$iswalnum,libd_iswalnum,ATTR_CONST WUNUSED,int,NOTHROW,LIBDCALL,(wint16_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(iswalnum,libc_iswalnum,ATTR_CONST WUNUSED,int,NOTHROW,LIBKCALL,(wint32_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(DOS$iswpunct,libd_iswpunct,ATTR_CONST WUNUSED,int,NOTHROW,LIBDCALL,(wint16_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(iswpunct,libc_iswpunct,ATTR_CONST WUNUSED,int,NOTHROW,LIBKCALL,(wint32_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(DOS$iswgraph,libd_iswgraph,ATTR_CONST WUNUSED,int,NOTHROW,LIBDCALL,(wint16_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(iswgraph,libc_iswgraph,ATTR_CONST WUNUSED,int,NOTHROW,LIBKCALL,(wint32_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(DOS$iswprint,libd_iswprint,ATTR_CONST WUNUSED,int,NOTHROW,LIBDCALL,(wint16_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(iswprint,libc_iswprint,ATTR_CONST WUNUSED,int,NOTHROW,LIBKCALL,(wint32_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(DOS$towlower,libd_towlower,ATTR_CONST WUNUSED,wint16_t,NOTHROW,LIBDCALL,(wint16_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(towlower,libc_towlower,ATTR_CONST WUNUSED,wint32_t,NOTHROW,LIBKCALL,(wint32_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(DOS$towupper,libd_towupper,ATTR_CONST WUNUSED,wint16_t,NOTHROW,LIBDCALL,(wint16_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(towupper,libc_towupper,ATTR_CONST WUNUSED,wint32_t,NOTHROW,LIBKCALL,(wint32_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(DOS$iswblank,libd_iswblank,ATTR_CONST WUNUSED,int,NOTHROW,LIBDCALL,(wint16_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(iswblank,libc_iswblank,ATTR_CONST WUNUSED,int,NOTHROW,LIBKCALL,(wint32_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(wctrans,libc_wctrans,ATTR_PURE WUNUSED ATTR_IN(1),wctrans_t,NOTHROW_NCX,LIBCCALL,(char const *prop),(prop));
DEFINE_PUBLIC_ALIAS_P(DOS$__towctrans,libd_towctrans,ATTR_CONST WUNUSED,wint16_t,NOTHROW,LIBDCALL,(wint16_t wc, wctrans_t desc),(wc,desc));
DEFINE_PUBLIC_ALIAS_P(DOS$towctrans,libd_towctrans,ATTR_CONST WUNUSED,wint16_t,NOTHROW,LIBDCALL,(wint16_t wc, wctrans_t desc),(wc,desc));
DEFINE_PUBLIC_ALIAS_P(__towctrans,libc_towctrans,ATTR_CONST WUNUSED,wint32_t,NOTHROW,LIBKCALL,(wint32_t wc, wctrans_t desc),(wc,desc));
DEFINE_PUBLIC_ALIAS_P(towctrans,libc_towctrans,ATTR_CONST WUNUSED,wint32_t,NOTHROW,LIBKCALL,(wint32_t wc, wctrans_t desc),(wc,desc));
DEFINE_PUBLIC_ALIAS_P(wctype,libc_wctype,ATTR_PURE WUNUSED ATTR_IN(1),wctype_t,NOTHROW_NCX,LIBCCALL,(char const *prop),(prop));
DEFINE_PUBLIC_ALIAS_P(DOS$is_wctype,libd_iswctype,ATTR_CONST WUNUSED,int,NOTHROW,LIBDCALL,(wint16_t wc, wctype_t desc),(wc,desc));
DEFINE_PUBLIC_ALIAS_P(DOS$__iswctype,libd_iswctype,ATTR_CONST WUNUSED,int,NOTHROW,LIBDCALL,(wint16_t wc, wctype_t desc),(wc,desc));
DEFINE_PUBLIC_ALIAS_P(DOS$iswctype,libd_iswctype,ATTR_CONST WUNUSED,int,NOTHROW,LIBDCALL,(wint16_t wc, wctype_t desc),(wc,desc));
DEFINE_PUBLIC_ALIAS_P(is_wctype,libc_iswctype,ATTR_CONST WUNUSED,int,NOTHROW,LIBKCALL,(wint32_t wc, wctype_t desc),(wc,desc));
DEFINE_PUBLIC_ALIAS_P(__iswctype,libc_iswctype,ATTR_CONST WUNUSED,int,NOTHROW,LIBKCALL,(wint32_t wc, wctype_t desc),(wc,desc));
DEFINE_PUBLIC_ALIAS_P(iswctype,libc_iswctype,ATTR_CONST WUNUSED,int,NOTHROW,LIBKCALL,(wint32_t wc, wctype_t desc),(wc,desc));
DEFINE_PUBLIC_ALIAS_P(DOS$iswascii,libd_iswascii,ATTR_CONST WUNUSED,int,NOTHROW,LIBDCALL,(wint16_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(iswascii,libc_iswascii,ATTR_CONST WUNUSED,int,NOTHROW,LIBKCALL,(wint32_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(DOS$_iswcntrl_l,libd_iswcntrl_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__iswcntrl_l,libd_iswcntrl_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$iswcntrl_l,libd_iswcntrl_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(__iswcntrl_l,libc_iswcntrl_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(iswcntrl_l,libc_iswcntrl_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_iswspace_l,libd_iswspace_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__iswspace_l,libd_iswspace_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$iswspace_l,libd_iswspace_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(__iswspace_l,libc_iswspace_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(iswspace_l,libc_iswspace_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_iswupper_l,libd_iswupper_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__iswupper_l,libd_iswupper_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$iswupper_l,libd_iswupper_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(__iswupper_l,libc_iswupper_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(iswupper_l,libc_iswupper_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_iswlower_l,libd_iswlower_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__iswlower_l,libd_iswlower_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$iswlower_l,libd_iswlower_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(__iswlower_l,libc_iswlower_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(iswlower_l,libc_iswlower_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_iswalpha_l,libd_iswalpha_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__iswalpha_l,libd_iswalpha_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$iswalpha_l,libd_iswalpha_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(__iswalpha_l,libc_iswalpha_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(iswalpha_l,libc_iswalpha_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_iswdigit_l,libd_iswdigit_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__iswdigit_l,libd_iswdigit_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$iswdigit_l,libd_iswdigit_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(__iswdigit_l,libc_iswdigit_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(iswdigit_l,libc_iswdigit_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_iswxdigit_l,libd_iswxdigit_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__iswxdigit_l,libd_iswxdigit_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$iswxdigit_l,libd_iswxdigit_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(__iswxdigit_l,libc_iswxdigit_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(iswxdigit_l,libc_iswxdigit_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_iswalnum_l,libd_iswalnum_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__iswalnum_l,libd_iswalnum_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$iswalnum_l,libd_iswalnum_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(__iswalnum_l,libc_iswalnum_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(iswalnum_l,libc_iswalnum_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_iswpunct_l,libd_iswpunct_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__iswpunct_l,libd_iswpunct_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$iswpunct_l,libd_iswpunct_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(__iswpunct_l,libc_iswpunct_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(iswpunct_l,libc_iswpunct_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_iswgraph_l,libd_iswgraph_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__iswgraph_l,libd_iswgraph_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$iswgraph_l,libd_iswgraph_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(__iswgraph_l,libc_iswgraph_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(iswgraph_l,libc_iswgraph_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_iswprint_l,libd_iswprint_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__iswprint_l,libd_iswprint_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$iswprint_l,libd_iswprint_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(__iswprint_l,libc_iswprint_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(iswprint_l,libc_iswprint_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_iswblank_l,libd_iswblank_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__iswblank_l,libd_iswblank_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$iswblank_l,libd_iswblank_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(__iswblank_l,libc_iswblank_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(iswblank_l,libc_iswblank_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_towlower_l,libd_towlower_l,ATTR_PURE WUNUSED,wint16_t,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__towlower_l,libd_towlower_l,ATTR_PURE WUNUSED,wint16_t,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$towlower_l,libd_towlower_l,ATTR_PURE WUNUSED,wint16_t,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(__towlower_l,libc_towlower_l,ATTR_PURE WUNUSED,wint32_t,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(towlower_l,libc_towlower_l,ATTR_PURE WUNUSED,wint32_t,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_towupper_l,libd_towupper_l,ATTR_PURE WUNUSED,wint16_t,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__towupper_l,libd_towupper_l,ATTR_PURE WUNUSED,wint16_t,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$towupper_l,libd_towupper_l,ATTR_PURE WUNUSED,wint16_t,NOTHROW_NCX,LIBDCALL,(wint16_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(__towupper_l,libc_towupper_l,ATTR_PURE WUNUSED,wint32_t,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(towupper_l,libc_towupper_l,ATTR_PURE WUNUSED,wint32_t,NOTHROW_NCX,LIBKCALL,(wint32_t ch, locale_t locale),(ch,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_iswctype_l,libd_iswctype_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t wc, wctype_t type, locale_t locale),(wc,type,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__iswctype_l,libd_iswctype_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t wc, wctype_t type, locale_t locale),(wc,type,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$iswctype_l,libd_iswctype_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t wc, wctype_t type, locale_t locale),(wc,type,locale));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_iswctype_l,libc_iswctype_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t wc, wctype_t type, locale_t locale),(wc,type,locale));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(__iswctype_l,libc_iswctype_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t wc, wctype_t type, locale_t locale),(wc,type,locale));
DEFINE_PUBLIC_ALIAS_P(iswctype_l,libc_iswctype_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t wc, wctype_t type, locale_t locale),(wc,type,locale));
DEFINE_PUBLIC_ALIAS_P(__wctype_l,libc_wctype_l,WUNUSED ATTR_IN(1),wctype_t,NOTHROW_NCX,LIBCCALL,(char const *prop, locale_t locale),(prop,locale));
DEFINE_PUBLIC_ALIAS_P(wctype_l,libc_wctype_l,WUNUSED ATTR_IN(1),wctype_t,NOTHROW_NCX,LIBCCALL,(char const *prop, locale_t locale),(prop,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__towctrans_l,libd_towctrans_l,WUNUSED,wint16_t,NOTHROW_NCX,LIBDCALL,(wint16_t wc, wctrans_t desc, locale_t locale),(wc,desc,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$towctrans_l,libd_towctrans_l,WUNUSED,wint16_t,NOTHROW_NCX,LIBDCALL,(wint16_t wc, wctrans_t desc, locale_t locale),(wc,desc,locale));
DEFINE_PUBLIC_ALIAS_P(__towctrans_l,libc_towctrans_l,WUNUSED,wint32_t,NOTHROW_NCX,LIBKCALL,(wint32_t wc, wctrans_t desc, locale_t locale),(wc,desc,locale));
DEFINE_PUBLIC_ALIAS_P(towctrans_l,libc_towctrans_l,WUNUSED,wint32_t,NOTHROW_NCX,LIBKCALL,(wint32_t wc, wctrans_t desc, locale_t locale),(wc,desc,locale));
DEFINE_PUBLIC_ALIAS_P(__wctrans_l,libc_wctrans_l,WUNUSED ATTR_IN(1),wctrans_t,NOTHROW_NCX,LIBCCALL,(char const *prop, locale_t locale),(prop,locale));
DEFINE_PUBLIC_ALIAS_P(wctrans_l,libc_wctrans_l,WUNUSED ATTR_IN(1),wctrans_t,NOTHROW_NCX,LIBCCALL,(char const *prop, locale_t locale),(prop,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$__iswcsymf,libd___iswcsymf,ATTR_CONST WUNUSED,int,NOTHROW,LIBDCALL,(wint16_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(__iswcsymf,libc___iswcsymf,ATTR_CONST WUNUSED,int,NOTHROW,LIBKCALL,(wint32_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(DOS$__iswcsym,libd___iswcsym,ATTR_CONST WUNUSED,int,NOTHROW,LIBDCALL,(wint16_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(__iswcsym,libc___iswcsym,ATTR_CONST WUNUSED,int,NOTHROW,LIBKCALL,(wint32_t wc),(wc));
DEFINE_PUBLIC_ALIAS_P(DOS$_iswcsymf_l,libd__iswcsymf_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t wc, locale_t locale),(wc,locale));
DEFINE_PUBLIC_ALIAS_P(_iswcsymf_l,libc__iswcsymf_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t wc, locale_t locale),(wc,locale));
DEFINE_PUBLIC_ALIAS_P(DOS$_iswcsym_l,libd__iswcsym_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBDCALL,(wint16_t wc, locale_t locale),(wc,locale));
DEFINE_PUBLIC_ALIAS_P(_iswcsym_l,libc__iswcsym_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBKCALL,(wint32_t wc, locale_t locale),(wc,locale));
DEFINE_PUBLIC_ALIAS_P(isleadbyte,libc_isleadbyte,ATTR_CONST WUNUSED,int,NOTHROW,LIBCCALL,(int wc),(wc));
DEFINE_PUBLIC_ALIAS_P(_isleadbyte_l,libc__isleadbyte_l,ATTR_PURE WUNUSED,int,NOTHROW_NCX,LIBCCALL,(int wc, locale_t locale),(wc,locale));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_WCTYPE_C */
