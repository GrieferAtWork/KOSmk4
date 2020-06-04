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

%[define_ccompat_header(cuchar)]
%[define_replacement(locale_t = __locale_t)]
%[define_replacement(wint_t = __WINT_TYPE__)]
%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]
%[default_impl_section(.text.crt.unicode.mbr)]

%[declare_known_section(.text.crt.wchar.unicode.convert)]
%[declare_known_section(.text.crt.dos.wchar.unicode.convert)]


%{
#include <features.h>
#include <hybrid/typecore.h>
#include <bits/mbstate.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __std_mbstate_t_defined
#define __std_mbstate_t_defined 1
__NAMESPACE_STD_BEGIN
typedef __mbstate_t mbstate_t;
__NAMESPACE_STD_END
#endif /* !__std_mbstate_t_defined */

#ifndef __CXX_SYSTEM_HEADER
}%(c,ccompat){
#ifndef __mbstate_t_defined
#define __mbstate_t_defined 1
__NAMESPACE_STD_USING(mbstate_t)
#endif /* !__mbstate_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */


/* Define `size_t' */
#ifndef __std_size_t_defined
#define __std_size_t_defined 1
__NAMESPACE_STD_BEGIN
typedef __SIZE_TYPE__ size_t;
__NAMESPACE_STD_END
#endif /* !__std_size_t_defined */
#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef __char16_t_defined
#define __char16_t_defined 1
typedef __CHAR16_TYPE__ char16_t;
typedef __CHAR32_TYPE__ char32_t;
#endif /* !__char16_t_defined */

/* Libc uses utf16/utf32 to encode/decode char16_t and char32_t */
#define __STD_UTF_16__ 1
#define __STD_UTF_32__ 1

}

%[insert:std]


[std]
[impl_include("<parts/errno.h>")]
[impl_prefix(
@__LOCAL_LIBC_DATA@(mbrtoc16_mbs) __mbstate_t mbrtoc16_mbs = __MBSTATE_INIT;
)]
mbrtoc16:(char16_t *__restrict pc16,
          char const *__restrict s, size_t n,
          __mbstate_t *__restrict mbs) -> size_t {
	char16_t c16;
	size_t result;
	if (!s) {
		if (mbs)
			mbs->__word = 0;
		return 0;
	}
	if (!mbs)
		mbs = &mbrtoc16_mbs;
	if (!pc16)
		pc16 = &c16;
	result = unicode_c8toc16(pc16, s, n, mbs);
#ifdef EILSEQ
	if unlikely(result == (size_t)-1)
		__libc_seterrno(EILSEQ);
#endif /* EILSEQ */
	return result;
}


[std]
[impl_include("<parts/errno.h>")]
[dependency_include(<bits/mbstate.h>)]
[impl_prefix(
@__LOCAL_LIBC_DATA@(mbrtoc32_mbs) __mbstate_t mbrtoc32_mbs = __MBSTATE_INIT;
)]
mbrtoc32:(char32_t *__restrict pc32,
          char const *__restrict s, size_t n,
          __mbstate_t *__restrict mbs) -> size_t {
	char32_t c32;
	size_t result;
	if (!s) {
		if (mbs)
			mbs->__word = 0;
		return 0;
	}
	if (!mbs)
		mbs = &mbrtoc32_mbs;
	if (!pc32)
		pc32 = &c32;
	result = unicode_c8toc32(pc32, s, n, mbs);
#ifdef EILSEQ
	if unlikely(result == (size_t)-1)
		__libc_seterrno(EILSEQ);
#endif /* EILSEQ */
	return result;
}

[std]
[impl_include("<parts/errno.h>")]
[dependency_include(<bits/mbstate.h>)]
[impl_prefix(
@__LOCAL_LIBC_DATA@(c16rtomb_mbs) __mbstate_t c16rtomb_mbs = __MBSTATE_INIT;
)]
c16rtomb:(char *__restrict s, char16_t c16, __mbstate_t *__restrict mbs) -> size_t {
	char32_t ch32;
	if (!s) {
		if (mbs)
			mbs->__word = __MBSTATE_TYPE_EMPTY;
		return 1;
	}
	if (!mbs)
		mbs = &c16rtomb_mbs;
	switch (mbs->__word & __MBSTATE_TYPE_MASK) {

	case __MBSTATE_TYPE_EMPTY:
		if (c16 >= 0xd800 && c16 <= 0xdbff) {
			/* High surrogate (set the MBS to accept a low surrogate as the next character) */
			mbs->__word = __MBSTATE_TYPE_UTF16_LO | ((c16 - 0xd800) & 0x3ff);
			return 0;
		}
		ch32 = (char32_t)c16;
		break;

	case __MBSTATE_TYPE_UTF16_LO:
		/* c16 should be a low surrogate */
		if unlikely(!(c16 >= 0xdc00 && c16 <= 0xdfff))
			goto error_ilseq;
		ch32 = ((mbs->__word & 0x000003ff) << 10) + 0x10000 + (c16 - 0xdc00);
		mbs->__word = __MBSTATE_TYPE_EMPTY;
		break;

	default:
error_ilseq:
#ifdef EILSEQ
		__libc_seterrno(EILSEQ);
#endif /* EILSEQ */
		return (size_t)-1;
	}
	/* Write a utf-8 sequence */
	return (size_t)(unicode_writeutf8(s, ch32) - s);
}

[std]
[impl_include("<parts/errno.h>")]
[dependency_include(<bits/mbstate.h>)]
c32rtomb:(char *__restrict s, char32_t c32, __mbstate_t *__restrict mbs) -> size_t {
	if (!s) {
		if (mbs)
			mbs->__word = __MBSTATE_TYPE_EMPTY;
		return 1;
	}
	if unlikely((c32 > 0x10ffff) ||
	            (mbs && (mbs->__word & __MBSTATE_TYPE_MASK) != __MBSTATE_TYPE_EMPTY)) {
#ifdef EILSEQ
		__libc_seterrno(EILSEQ);
#endif /* EILSEQ */
		return (size_t)-1;
	}
	/* Write a utf-8 sequence */
	return (size_t)(unicode_writeutf8(s, c32) - s);
}


%{

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_UTF

#if defined(_STRING_H) && !defined(_PARTS_UCHAR_STRING_H)
#include <parts/uchar/string.h>
#endif

#if defined(_PROCESS_H) && !defined(_PARTS_UCHAR_PROCESS_H)
#include <parts/uchar/process.h>
#endif

#if defined(_STDLIB_H) && !defined(_PARTS_UCHAR_STDLIB_H)
#include <parts/uchar/stdlib.h>
#endif

#if defined(_FCNTL_H) && !defined(_PARTS_UCHAR_FCNTL_H)
#include <parts/uchar/fcntl.h>
#endif

#if defined(_UNISTD_H) && !defined(_PARTS_UCHAR_UNISTD_H)
#include <parts/uchar/unistd.h>
#endif

#if defined(_UTIME_H) && !defined(_PARTS_UCHAR_UTIME_H)
#include <parts/uchar/utime.h>
#endif

#if defined(_FORMAT_PRINTER_H) && !defined(_PARTS_UCHAR_FORMATPRINTER_H)
#include <parts/uchar/format-printer.h>
#endif

#if defined(_IO_H) && !defined(_PARTS_UCHAR_IO_H)
#include <parts/uchar/io.h>
#endif

#if defined(_STDIO_H) && !defined(_PARTS_UCHAR_STDIO_H)
#include <parts/uchar/stdio.h>
#endif

#if defined(_TIME_H) && !defined(_PARTS_UCHAR_TIME_H)
#include <parts/uchar/time.h>
#endif

#if defined(_SYS_STAT_H) && !defined(_PARTS_UCHAR_SYS_STAT_H)
#include <parts/uchar/sys/stat.h>
#endif

#if defined(_SYS_MMAN_H) && !defined(_PARTS_UCHAR_SYS_MMAN_H)
#include <parts/uchar/sys/mman.h>
#endif

#if defined(_INTTYPES_H) && !defined(_PARTS_UCHAR_INTTYPES_H)
#include <parts/uchar/inttypes.h>
#endif

#endif /* __USE_UTF */

}

