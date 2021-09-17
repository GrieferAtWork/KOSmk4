/* HASH CRC-32:0x4b6101d6 */
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
#ifndef GUARD_LIBC_AUTO_WCTYPE_C
#define GUARD_LIBC_AUTO_WCTYPE_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "wctype.h"
#include "../user/ctype.h"
#include "../user/string.h"
#include "../user/unicode.h"
#include "../user/wchar.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <bits/crt/wctype.h>
/* >> iswcntrl(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswcntrl)(wint16_t wc) {
#ifdef __crt_iswcntrl
	return __crt_iswcntrl(wc);
#else /* __crt_iswcntrl */
	return libc_iscntrl(libd_wctob(wc));
#endif /* !__crt_iswcntrl */
}
#include <bits/crt/wctype.h>
/* >> iswcntrl(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswcntrl)(wint32_t wc) {
#ifdef __crt_iswcntrl
	return __crt_iswcntrl(wc);
#else /* __crt_iswcntrl */
	return libc_iscntrl(libc_wctob(wc));
#endif /* !__crt_iswcntrl */
}
#include <bits/crt/wctype.h>
/* >> iswspace(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswspace)(wint16_t wc) {
#ifdef __crt_iswspace
	return __crt_iswspace(wc);
#else /* __crt_iswspace */
	return libc_isspace(libd_wctob(wc));
#endif /* !__crt_iswspace */
}
#include <bits/crt/wctype.h>
/* >> iswspace(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswspace)(wint32_t wc) {
#ifdef __crt_iswspace
	return __crt_iswspace(wc);
#else /* __crt_iswspace */
	return libc_isspace(libc_wctob(wc));
#endif /* !__crt_iswspace */
}
#include <bits/crt/wctype.h>
/* >> iswupper(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswupper)(wint16_t wc) {
#ifdef __crt_iswupper
	return __crt_iswupper(wc);
#else /* __crt_iswupper */
	return libc_isupper(libd_wctob(wc));
#endif /* !__crt_iswupper */
}
#include <bits/crt/wctype.h>
/* >> iswupper(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswupper)(wint32_t wc) {
#ifdef __crt_iswupper
	return __crt_iswupper(wc);
#else /* __crt_iswupper */
	return libc_isupper(libc_wctob(wc));
#endif /* !__crt_iswupper */
}
#include <bits/crt/wctype.h>
/* >> iswlower(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswlower)(wint16_t wc) {
#ifdef __crt_iswlower
	return __crt_iswlower(wc);
#else /* __crt_iswlower */
	return libc_islower(libd_wctob(wc));
#endif /* !__crt_iswlower */
}
#include <bits/crt/wctype.h>
/* >> iswlower(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswlower)(wint32_t wc) {
#ifdef __crt_iswlower
	return __crt_iswlower(wc);
#else /* __crt_iswlower */
	return libc_islower(libc_wctob(wc));
#endif /* !__crt_iswlower */
}
#include <bits/crt/wctype.h>
/* >> iswalpha(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswalpha)(wint16_t wc) {
#ifdef __crt_iswalpha
	return __crt_iswalpha(wc);
#else /* __crt_iswalpha */
	return libc_isalpha(libd_wctob(wc));
#endif /* !__crt_iswalpha */
}
#include <bits/crt/wctype.h>
/* >> iswalpha(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswalpha)(wint32_t wc) {
#ifdef __crt_iswalpha
	return __crt_iswalpha(wc);
#else /* __crt_iswalpha */
	return libc_isalpha(libc_wctob(wc));
#endif /* !__crt_iswalpha */
}
#include <bits/crt/wctype.h>
/* >> iswdigit(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswdigit)(wint16_t wc) {
#ifdef __crt_iswdigit
	return __crt_iswdigit(wc);
#else /* __crt_iswdigit */
	return libc_isdigit(libd_wctob(wc));
#endif /* !__crt_iswdigit */
}
#include <bits/crt/wctype.h>
/* >> iswdigit(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswdigit)(wint32_t wc) {
#ifdef __crt_iswdigit
	return __crt_iswdigit(wc);
#else /* __crt_iswdigit */
	return libc_isdigit(libc_wctob(wc));
#endif /* !__crt_iswdigit */
}
#include <bits/crt/wctype.h>
/* >> iswxdigit(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswxdigit)(wint16_t wc) {
#ifdef __crt_iswxdigit
	return __crt_iswxdigit(wc);
#else /* __crt_iswxdigit */
	return libc_isxdigit(libd_wctob(wc));
#endif /* !__crt_iswxdigit */
}
#include <bits/crt/wctype.h>
/* >> iswxdigit(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswxdigit)(wint32_t wc) {
#ifdef __crt_iswxdigit
	return __crt_iswxdigit(wc);
#else /* __crt_iswxdigit */
	return libc_isxdigit(libc_wctob(wc));
#endif /* !__crt_iswxdigit */
}
#include <bits/crt/wctype.h>
/* >> iswalnum(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswalnum)(wint16_t wc) {
#ifdef __crt_iswalnum
	return __crt_iswalnum(wc);
#else /* __crt_iswalnum */
	return libc_isalnum(libd_wctob(wc));
#endif /* !__crt_iswalnum */
}
#include <bits/crt/wctype.h>
/* >> iswalnum(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswalnum)(wint32_t wc) {
#ifdef __crt_iswalnum
	return __crt_iswalnum(wc);
#else /* __crt_iswalnum */
	return libc_isalnum(libc_wctob(wc));
#endif /* !__crt_iswalnum */
}
#include <bits/crt/wctype.h>
/* >> iswpunct(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswpunct)(wint16_t wc) {
#ifdef __crt_iswpunct
	return __crt_iswpunct(wc);
#else /* __crt_iswpunct */
	return libc_ispunct(libd_wctob(wc));
#endif /* !__crt_iswpunct */
}
#include <bits/crt/wctype.h>
/* >> iswpunct(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswpunct)(wint32_t wc) {
#ifdef __crt_iswpunct
	return __crt_iswpunct(wc);
#else /* __crt_iswpunct */
	return libc_ispunct(libc_wctob(wc));
#endif /* !__crt_iswpunct */
}
#include <bits/crt/wctype.h>
/* >> iswgraph(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswgraph)(wint16_t wc) {
#ifdef __crt_iswgraph
	return __crt_iswgraph(wc);
#else /* __crt_iswgraph */
	return libc_isgraph(libd_wctob(wc));
#endif /* !__crt_iswgraph */
}
#include <bits/crt/wctype.h>
/* >> iswgraph(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswgraph)(wint32_t wc) {
#ifdef __crt_iswgraph
	return __crt_iswgraph(wc);
#else /* __crt_iswgraph */
	return libc_isgraph(libc_wctob(wc));
#endif /* !__crt_iswgraph */
}
#include <bits/crt/wctype.h>
/* >> iswprint(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswprint)(wint16_t wc) {
#ifdef __crt_iswprint
	return __crt_iswprint(wc);
#else /* __crt_iswprint */
	return libc_isprint(libd_wctob(wc));
#endif /* !__crt_iswprint */
}
#include <bits/crt/wctype.h>
/* >> iswprint(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswprint)(wint32_t wc) {
#ifdef __crt_iswprint
	return __crt_iswprint(wc);
#else /* __crt_iswprint */
	return libc_isprint(libc_wctob(wc));
#endif /* !__crt_iswprint */
}
#include <bits/crt/wctype.h>
/* >> towlower(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED wint16_t
NOTHROW(LIBDCALL libd_towlower)(wint16_t wc) {
#ifdef __crt_towlower
	return __crt_towlower(wc);
#else /* __crt_towlower */
	return libd_btowc(libc_tolower(libd_wctob(wc)));
#endif /* !__crt_towlower */
}
#include <bits/crt/wctype.h>
/* >> towlower(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED wint32_t
NOTHROW(LIBKCALL libc_towlower)(wint32_t wc) {
#ifdef __crt_towlower
	return __crt_towlower(wc);
#else /* __crt_towlower */
	return libc_btowc(libc_tolower(libc_wctob(wc)));
#endif /* !__crt_towlower */
}
#include <bits/crt/wctype.h>
/* >> towupper(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED wint16_t
NOTHROW(LIBDCALL libd_towupper)(wint16_t wc) {
#ifdef __crt_towupper
	return __crt_towupper(wc);
#else /* __crt_towupper */
	return libd_btowc(libc_toupper(libd_wctob(wc)));
#endif /* !__crt_towupper */
}
#include <bits/crt/wctype.h>
/* >> towupper(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED wint32_t
NOTHROW(LIBKCALL libc_towupper)(wint32_t wc) {
#ifdef __crt_towupper
	return __crt_towupper(wc);
#else /* __crt_towupper */
	return libc_btowc(libc_toupper(libc_wctob(wc)));
#endif /* !__crt_towupper */
}
#include <bits/crt/wctype.h>
/* >> iswblank(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswblank)(wint16_t wc) {
#ifdef __crt_iswblank
	return __crt_iswblank(wc);
#else /* __crt_iswblank */
	return libc_isblank(libd_wctob(wc));
#endif /* !__crt_iswblank */
}
#include <bits/crt/wctype.h>
/* >> iswblank(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswblank)(wint32_t wc) {
#ifdef __crt_iswblank
	return __crt_iswblank(wc);
#else /* __crt_iswblank */
	return libc_isblank(libc_wctob(wc));
#endif /* !__crt_iswblank */
}
#include <bits/crt/unicode.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_PURE WUNUSED NONNULL((1)) wctrans_t
NOTHROW_NCX(LIBCCALL libc_wctrans)(char const *prop) {
	struct wctrans_entry {
		char     we_name[8]; /* Name (with leading 'to' stripped) */
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
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED wint16_t
NOTHROW_NCX(LIBDCALL libd_towctrans)(wint16_t wc,
                                     wctrans_t desc) {
	struct __unitraits const *traits = libc___unicode_descriptor(wc);
	return wc + *((s32 const *)traits + (uintptr_t)desc);
}
#include <bits/crt/unicode.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED wint32_t
NOTHROW_NCX(LIBKCALL libc_towctrans)(wint32_t wc,
                                     wctrans_t desc) {
	struct __unitraits const *traits = libc___unicode_descriptor(wc);
	return wc + *((s32 const *)traits + (uintptr_t)desc);
}
#include <bits/crt/unicode.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_PURE WUNUSED NONNULL((1)) wctype_t
NOTHROW_NCX(LIBCCALL libc_wctype)(char const *prop) {
	struct wctype_entry {
		char     we_name[8]; /* Name (with leading 'to' stripped) */
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
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswctype)(wint16_t wc,
                                    wctype_t desc) {
	struct __unitraits const *traits = libc___unicode_descriptor(wc);
	return (int)(traits->__ut_flags & (uint16_t)desc);
}
#include <bits/crt/unicode.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBKCALL libc_iswctype)(wint32_t wc,
                                    wctype_t desc) {
	struct __unitraits const *traits = libc___unicode_descriptor(wc);
	return (int)(traits->__ut_flags & (uint16_t)desc);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBDCALL libd_iswascii)(wint16_t wc) {
	return wc >= 0 && wc <= 0x7f;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.ctype") ATTR_CONST WUNUSED int
NOTHROW(LIBKCALL libc_iswascii)(wint32_t wc) {
	return wc >= 0 && wc <= 0x7f;
}
#ifdef __LIBDCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libd_iswcntrl_l, libd_iswcntrl);
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswcntrl_l(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswcntrl_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswcntrl(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libc_iswcntrl_l, libc_iswcntrl);
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
DEFINE_INTERN_ALIAS(libd_iswspace_l, libd_iswspace);
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswspace_l(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswspace_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswspace(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libc_iswspace_l, libc_iswspace);
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
DEFINE_INTERN_ALIAS(libd_iswupper_l, libd_iswupper);
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswupper_l(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswupper_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswupper(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libc_iswupper_l, libc_iswupper);
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
DEFINE_INTERN_ALIAS(libd_iswlower_l, libd_iswlower);
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswlower_l(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswlower_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswlower(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libc_iswlower_l, libc_iswlower);
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
DEFINE_INTERN_ALIAS(libd_iswalpha_l, libd_iswalpha);
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswalpha_l(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswalpha_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswalpha(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libc_iswalpha_l, libc_iswalpha);
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
DEFINE_INTERN_ALIAS(libd_iswdigit_l, libd_iswdigit);
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswdigit_l(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswdigit_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswdigit(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libc_iswdigit_l, libc_iswdigit);
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
DEFINE_INTERN_ALIAS(libd_iswxdigit_l, libd_iswxdigit);
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswxdigit_l(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswxdigit_l)(wint16_t ch,
                                       locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswxdigit(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libc_iswxdigit_l, libc_iswxdigit);
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
DEFINE_INTERN_ALIAS(libd_iswalnum_l, libd_iswalnum);
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswalnum_l(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswalnum_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswalnum(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libc_iswalnum_l, libc_iswalnum);
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
DEFINE_INTERN_ALIAS(libd_iswpunct_l, libd_iswpunct);
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswpunct_l(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswpunct_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswpunct(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libc_iswpunct_l, libc_iswpunct);
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
DEFINE_INTERN_ALIAS(libd_iswgraph_l, libd_iswgraph);
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswgraph_l(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswgraph_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswgraph(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libc_iswgraph_l, libc_iswgraph);
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
DEFINE_INTERN_ALIAS(libd_iswprint_l, libd_iswprint);
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswprint_l(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswprint_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswprint(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libc_iswprint_l, libc_iswprint);
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
DEFINE_INTERN_ALIAS(libd_iswblank_l, libd_iswblank);
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> iswblank_l(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswblank_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_iswblank(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libc_iswblank_l, libc_iswblank);
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
DEFINE_INTERN_ALIAS(libd_towlower_l, libd_towlower);
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> towlower_l(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED wint16_t
NOTHROW_NCX(LIBDCALL libd_towlower_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_towlower(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libc_towlower_l, libc_towlower);
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
DEFINE_INTERN_ALIAS(libd_towupper_l, libd_towupper);
#else /* __LIBDCALL_CALLER_CLEANUP */
/* >> towupper_l(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED wint16_t
NOTHROW_NCX(LIBDCALL libd_towupper_l)(wint16_t ch,
                                      locale_t locale) {
	COMPILER_IMPURE();
	(void)locale;
	return libd_towupper(ch);
}
#endif /* !__LIBDCALL_CALLER_CLEANUP */
#ifdef __LIBKCALL_CALLER_CLEANUP
DEFINE_INTERN_ALIAS(libc_towupper_l, libc_towupper);
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
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd_iswctype_l)(wint16_t wc,
                                      wctype_t type,
                                      locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return libd_iswctype(wc, type);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBKCALL libc_iswctype_l)(wint32_t wc,
                                      wctype_t type,
                                      locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return libc_iswctype(wc, type);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") WUNUSED NONNULL((1)) wctype_t
NOTHROW_NCX(LIBCCALL libc_wctype_l)(char const *prop,
                                    locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return libc_wctype(prop);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.ctype") WUNUSED wint16_t
NOTHROW_NCX(LIBDCALL libd_towctrans_l)(wint16_t wc,
                                       wctrans_t desc,
                                       locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return libd_towctrans(wc, desc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") WUNUSED wint32_t
NOTHROW_NCX(LIBKCALL libc_towctrans_l)(wint32_t wc,
                                       wctrans_t desc,
                                       locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return libc_towctrans(wc, desc);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.ctype") WUNUSED NONNULL((1)) wctrans_t
NOTHROW_NCX(LIBCCALL libc_wctrans_l)(char const *prop,
                                     locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return libc_wctrans(prop);
}
#include <bits/crt/unicode.h>
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBDCALL libd___iswcsymf)(wint16_t wc) {
#if defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
	struct __unitraits const *traits = libc___unicode_descriptor(wc);
	return (int)(traits->__ut_flags & __UNICODE_ISSYMSTRT);
#else /* __CRT_KOS && __CRT_HAVE___unicode_descriptor */
	return libd_iswalpha(wc) || wc == '_' || wc == '$';
#endif /* !__CRT_KOS || !__CRT_HAVE___unicode_descriptor */
}
#include <bits/crt/unicode.h>
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBKCALL libc___iswcsymf)(wint32_t wc) {
#if defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
	struct __unitraits const *traits = libc___unicode_descriptor(wc);
	return (int)(traits->__ut_flags & __UNICODE_ISSYMSTRT);
#else /* __CRT_KOS && __CRT_HAVE___unicode_descriptor */
	return libc_iswalpha(wc) || wc == '_' || wc == '$';
#endif /* !__CRT_KOS || !__CRT_HAVE___unicode_descriptor */
}
#include <bits/crt/unicode.h>
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBDCALL libd___iswcsym)(wint16_t wc) {
#if defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
	struct __unitraits const *traits = libc___unicode_descriptor(wc);
	return (int)(traits->__ut_flags & __UNICODE_ISSYMCONT);
#else /* __CRT_KOS && __CRT_HAVE___unicode_descriptor */
	return libd_iswalnum(wc) || wc == '_' || wc == '$';
#endif /* !__CRT_KOS || !__CRT_HAVE___unicode_descriptor */
}
#include <bits/crt/unicode.h>
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBKCALL libc___iswcsym)(wint32_t wc) {
#if defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
	struct __unitraits const *traits = libc___unicode_descriptor(wc);
	return (int)(traits->__ut_flags & __UNICODE_ISSYMCONT);
#else /* __CRT_KOS && __CRT_HAVE___unicode_descriptor */
	return libc_iswalnum(wc) || wc == '_' || wc == '$';
#endif /* !__CRT_KOS || !__CRT_HAVE___unicode_descriptor */
}
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.mbs") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd__iswcsymf_l)(wint16_t wc,
                                       locale_t locale) {
#if defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
	(void)locale;
	COMPILER_IMPURE();
	return __iswcsymf(wc);
#else /* __CRT_KOS && __CRT_HAVE___unicode_descriptor */
	return libd_iswalpha_l(wc, locale) || wc == '_' || wc == '$';
#endif /* !__CRT_KOS || !__CRT_HAVE___unicode_descriptor */
}
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.mbs") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBKCALL libc__iswcsymf_l)(wint32_t wc,
                                       locale_t locale) {
#if defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
	(void)locale;
	COMPILER_IMPURE();
	return __iswcsymf(wc);
#else /* __CRT_KOS && __CRT_HAVE___unicode_descriptor */
	return libc_iswalpha_l(wc, locale) || wc == '_' || wc == '$';
#endif /* !__CRT_KOS || !__CRT_HAVE___unicode_descriptor */
}
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.mbs") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBDCALL libd__iswcsym_l)(wint16_t wc,
                                      locale_t locale) {
#if defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
	(void)locale;
	COMPILER_IMPURE();
	return __iswcsym(wc);
#else /* __CRT_KOS && __CRT_HAVE___unicode_descriptor */
	return libd_iswalnum_l(wc, locale) || wc == '_' || wc == '$';
#endif /* !__CRT_KOS || !__CRT_HAVE___unicode_descriptor */
}
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.mbs") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBKCALL libc__iswcsym_l)(wint32_t wc,
                                      locale_t locale) {
#if defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
	(void)locale;
	COMPILER_IMPURE();
	return __iswcsym(wc);
#else /* __CRT_KOS && __CRT_HAVE___unicode_descriptor */
	return libc_iswalnum_l(wc, locale) || wc == '_' || wc == '$';
#endif /* !__CRT_KOS || !__CRT_HAVE___unicode_descriptor */
}
/* >> isleadbyte(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_CONST WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isleadbyte)(int wc) {
	return wc >= 192 && wc <= 255;
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.mbs") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc__isleadbyte_l)(int wc,
                                         locale_t locale) {
	(void)locale;
	COMPILER_IMPURE();
	return libc_isleadbyte(wc);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$iswcntrl, libd_iswcntrl);
DEFINE_PUBLIC_ALIAS(iswcntrl, libc_iswcntrl);
DEFINE_PUBLIC_ALIAS(DOS$iswspace, libd_iswspace);
DEFINE_PUBLIC_ALIAS(iswspace, libc_iswspace);
DEFINE_PUBLIC_ALIAS(DOS$iswupper, libd_iswupper);
DEFINE_PUBLIC_ALIAS(iswupper, libc_iswupper);
DEFINE_PUBLIC_ALIAS(DOS$iswlower, libd_iswlower);
DEFINE_PUBLIC_ALIAS(iswlower, libc_iswlower);
DEFINE_PUBLIC_ALIAS(DOS$iswalpha, libd_iswalpha);
DEFINE_PUBLIC_ALIAS(iswalpha, libc_iswalpha);
DEFINE_PUBLIC_ALIAS(DOS$iswdigit, libd_iswdigit);
DEFINE_PUBLIC_ALIAS(iswdigit, libc_iswdigit);
DEFINE_PUBLIC_ALIAS(DOS$iswxdigit, libd_iswxdigit);
DEFINE_PUBLIC_ALIAS(iswxdigit, libc_iswxdigit);
DEFINE_PUBLIC_ALIAS(DOS$iswalnum, libd_iswalnum);
DEFINE_PUBLIC_ALIAS(iswalnum, libc_iswalnum);
DEFINE_PUBLIC_ALIAS(DOS$iswpunct, libd_iswpunct);
DEFINE_PUBLIC_ALIAS(iswpunct, libc_iswpunct);
DEFINE_PUBLIC_ALIAS(DOS$iswgraph, libd_iswgraph);
DEFINE_PUBLIC_ALIAS(iswgraph, libc_iswgraph);
DEFINE_PUBLIC_ALIAS(DOS$iswprint, libd_iswprint);
DEFINE_PUBLIC_ALIAS(iswprint, libc_iswprint);
DEFINE_PUBLIC_ALIAS(DOS$towlower, libd_towlower);
DEFINE_PUBLIC_ALIAS(towlower, libc_towlower);
DEFINE_PUBLIC_ALIAS(DOS$towupper, libd_towupper);
DEFINE_PUBLIC_ALIAS(towupper, libc_towupper);
DEFINE_PUBLIC_ALIAS(DOS$iswblank, libd_iswblank);
DEFINE_PUBLIC_ALIAS(iswblank, libc_iswblank);
DEFINE_PUBLIC_ALIAS(wctrans, libc_wctrans);
DEFINE_PUBLIC_ALIAS(DOS$__towctrans, libd_towctrans);
DEFINE_PUBLIC_ALIAS(DOS$towctrans, libd_towctrans);
DEFINE_PUBLIC_ALIAS(__towctrans, libc_towctrans);
DEFINE_PUBLIC_ALIAS(towctrans, libc_towctrans);
DEFINE_PUBLIC_ALIAS(wctype, libc_wctype);
DEFINE_PUBLIC_ALIAS(DOS$is_wctype, libd_iswctype);
DEFINE_PUBLIC_ALIAS(DOS$__iswctype, libd_iswctype);
DEFINE_PUBLIC_ALIAS(DOS$iswctype, libd_iswctype);
DEFINE_PUBLIC_ALIAS(is_wctype, libc_iswctype);
DEFINE_PUBLIC_ALIAS(__iswctype, libc_iswctype);
DEFINE_PUBLIC_ALIAS(iswctype, libc_iswctype);
DEFINE_PUBLIC_ALIAS(DOS$iswascii, libd_iswascii);
DEFINE_PUBLIC_ALIAS(iswascii, libc_iswascii);
DEFINE_PUBLIC_ALIAS(DOS$_iswcntrl_l, libd_iswcntrl_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswcntrl_l, libd_iswcntrl_l);
DEFINE_PUBLIC_ALIAS(DOS$iswcntrl_l, libd_iswcntrl_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_iswcntrl_l, libc_iswcntrl_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__iswcntrl_l, libc_iswcntrl_l);
DEFINE_PUBLIC_ALIAS(iswcntrl_l, libc_iswcntrl_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswspace_l, libd_iswspace_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswspace_l, libd_iswspace_l);
DEFINE_PUBLIC_ALIAS(DOS$iswspace_l, libd_iswspace_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_iswspace_l, libc_iswspace_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__iswspace_l, libc_iswspace_l);
DEFINE_PUBLIC_ALIAS(iswspace_l, libc_iswspace_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswupper_l, libd_iswupper_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswupper_l, libd_iswupper_l);
DEFINE_PUBLIC_ALIAS(DOS$iswupper_l, libd_iswupper_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_iswupper_l, libc_iswupper_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__iswupper_l, libc_iswupper_l);
DEFINE_PUBLIC_ALIAS(iswupper_l, libc_iswupper_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswlower_l, libd_iswlower_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswlower_l, libd_iswlower_l);
DEFINE_PUBLIC_ALIAS(DOS$iswlower_l, libd_iswlower_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_iswlower_l, libc_iswlower_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__iswlower_l, libc_iswlower_l);
DEFINE_PUBLIC_ALIAS(iswlower_l, libc_iswlower_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswalpha_l, libd_iswalpha_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswalpha_l, libd_iswalpha_l);
DEFINE_PUBLIC_ALIAS(DOS$iswalpha_l, libd_iswalpha_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_iswalpha_l, libc_iswalpha_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__iswalpha_l, libc_iswalpha_l);
DEFINE_PUBLIC_ALIAS(iswalpha_l, libc_iswalpha_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswdigit_l, libd_iswdigit_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswdigit_l, libd_iswdigit_l);
DEFINE_PUBLIC_ALIAS(DOS$iswdigit_l, libd_iswdigit_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_iswdigit_l, libc_iswdigit_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__iswdigit_l, libc_iswdigit_l);
DEFINE_PUBLIC_ALIAS(iswdigit_l, libc_iswdigit_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswxdigit_l, libd_iswxdigit_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswxdigit_l, libd_iswxdigit_l);
DEFINE_PUBLIC_ALIAS(DOS$iswxdigit_l, libd_iswxdigit_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_iswxdigit_l, libc_iswxdigit_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__iswxdigit_l, libc_iswxdigit_l);
DEFINE_PUBLIC_ALIAS(iswxdigit_l, libc_iswxdigit_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswalnum_l, libd_iswalnum_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswalnum_l, libd_iswalnum_l);
DEFINE_PUBLIC_ALIAS(DOS$iswalnum_l, libd_iswalnum_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_iswalnum_l, libc_iswalnum_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__iswalnum_l, libc_iswalnum_l);
DEFINE_PUBLIC_ALIAS(iswalnum_l, libc_iswalnum_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswpunct_l, libd_iswpunct_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswpunct_l, libd_iswpunct_l);
DEFINE_PUBLIC_ALIAS(DOS$iswpunct_l, libd_iswpunct_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_iswpunct_l, libc_iswpunct_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__iswpunct_l, libc_iswpunct_l);
DEFINE_PUBLIC_ALIAS(iswpunct_l, libc_iswpunct_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswgraph_l, libd_iswgraph_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswgraph_l, libd_iswgraph_l);
DEFINE_PUBLIC_ALIAS(DOS$iswgraph_l, libd_iswgraph_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_iswgraph_l, libc_iswgraph_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__iswgraph_l, libc_iswgraph_l);
DEFINE_PUBLIC_ALIAS(iswgraph_l, libc_iswgraph_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswprint_l, libd_iswprint_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswprint_l, libd_iswprint_l);
DEFINE_PUBLIC_ALIAS(DOS$iswprint_l, libd_iswprint_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_iswprint_l, libc_iswprint_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__iswprint_l, libc_iswprint_l);
DEFINE_PUBLIC_ALIAS(iswprint_l, libc_iswprint_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswblank_l, libd_iswblank_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswblank_l, libd_iswblank_l);
DEFINE_PUBLIC_ALIAS(DOS$iswblank_l, libd_iswblank_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_iswblank_l, libc_iswblank_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__iswblank_l, libc_iswblank_l);
DEFINE_PUBLIC_ALIAS(iswblank_l, libc_iswblank_l);
DEFINE_PUBLIC_ALIAS(DOS$_towlower_l, libd_towlower_l);
DEFINE_PUBLIC_ALIAS(DOS$__towlower_l, libd_towlower_l);
DEFINE_PUBLIC_ALIAS(DOS$towlower_l, libd_towlower_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_towlower_l, libc_towlower_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__towlower_l, libc_towlower_l);
DEFINE_PUBLIC_ALIAS(towlower_l, libc_towlower_l);
DEFINE_PUBLIC_ALIAS(DOS$_towupper_l, libd_towupper_l);
DEFINE_PUBLIC_ALIAS(DOS$__towupper_l, libd_towupper_l);
DEFINE_PUBLIC_ALIAS(DOS$towupper_l, libd_towupper_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_towupper_l, libc_towupper_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__towupper_l, libc_towupper_l);
DEFINE_PUBLIC_ALIAS(towupper_l, libc_towupper_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswctype_l, libd_iswctype_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswctype_l, libd_iswctype_l);
DEFINE_PUBLIC_ALIAS(DOS$iswctype_l, libd_iswctype_l);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_iswctype_l, libc_iswctype_l);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__iswctype_l, libc_iswctype_l);
DEFINE_PUBLIC_ALIAS(iswctype_l, libc_iswctype_l);
DEFINE_PUBLIC_ALIAS(__wctype_l, libc_wctype_l);
DEFINE_PUBLIC_ALIAS(wctype_l, libc_wctype_l);
DEFINE_PUBLIC_ALIAS(DOS$__towctrans_l, libd_towctrans_l);
DEFINE_PUBLIC_ALIAS(DOS$towctrans_l, libd_towctrans_l);
DEFINE_PUBLIC_ALIAS(__towctrans_l, libc_towctrans_l);
DEFINE_PUBLIC_ALIAS(towctrans_l, libc_towctrans_l);
DEFINE_PUBLIC_ALIAS(__wctrans_l, libc_wctrans_l);
DEFINE_PUBLIC_ALIAS(wctrans_l, libc_wctrans_l);
DEFINE_PUBLIC_ALIAS(DOS$__iswcsymf, libd___iswcsymf);
DEFINE_PUBLIC_ALIAS(__iswcsymf, libc___iswcsymf);
DEFINE_PUBLIC_ALIAS(DOS$__iswcsym, libd___iswcsym);
DEFINE_PUBLIC_ALIAS(__iswcsym, libc___iswcsym);
DEFINE_PUBLIC_ALIAS(DOS$_iswcsymf_l, libd__iswcsymf_l);
DEFINE_PUBLIC_ALIAS(_iswcsymf_l, libc__iswcsymf_l);
DEFINE_PUBLIC_ALIAS(DOS$_iswcsym_l, libd__iswcsym_l);
DEFINE_PUBLIC_ALIAS(_iswcsym_l, libc__iswcsym_l);
DEFINE_PUBLIC_ALIAS(isleadbyte, libc_isleadbyte);
DEFINE_PUBLIC_ALIAS(_isleadbyte_l, libc__isleadbyte_l);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_WCTYPE_C */
