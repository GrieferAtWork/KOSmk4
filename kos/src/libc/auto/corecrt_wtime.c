/* HASH CRC-32:0x8e2771be */
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
#ifndef GUARD_LIBC_AUTO_CORECRT_WTIME_C
#define GUARD_LIBC_AUTO_CORECRT_WTIME_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "corecrt_wtime.h"
#include "../user/time.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.time") WUNUSED ATTR_IN(1) char16_t *
NOTHROW_NCX(LIBDCALL libd__wasctime)(struct tm const *tp) {
	static char16_t wasctime_retbuf[26] = { 0 };
	return libd__wasctime_s(wasctime_retbuf, 26, tp) ? NULL : wasctime_retbuf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.time") WUNUSED ATTR_IN(1) char32_t *
NOTHROW_NCX(LIBKCALL libc__wasctime)(struct tm const *tp) {
	static char32_t wasctime_retbuf[26] = { 0 };
	return libc__wasctime_s(wasctime_retbuf, 26, tp) ? NULL : wasctime_retbuf;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.time") ATTR_IN(3) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBDCALL libd__wasctime_s)(char16_t *buf,
                                       size_t buflen,
                                       struct tm const *tp) {
	char abuf[26], *ptr;
	unsigned int i;
	if unlikely(buflen < 26)
		return 34;
	/* asctime --> ASCiiTIME --> No unicode here --> directly  copy
	 * This is also why its  kind of <redacted for profanity>  that
	 * a function like `_wasctime_s()' even exists, but whatever... */
	ptr = libc_asctime_r(tp, abuf);
	for (i = 0; i < 26; ++i)
		buf[i] = (char16_t)ptr[i];
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.time") ATTR_IN(3) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBKCALL libc__wasctime_s)(char32_t *buf,
                                       size_t buflen,
                                       struct tm const *tp) {
	char abuf[26], *ptr;
	unsigned int i;
	if unlikely(buflen < 26)
		return ERANGE;
	/* asctime --> ASCiiTIME --> No unicode here --> directly  copy
	 * This is also why its  kind of <redacted for profanity>  that
	 * a function like `_wasctime_s()' even exists, but whatever... */
	ptr = libc_asctime_r(tp, abuf);
	for (i = 0; i < 26; ++i)
		buf[i] = (char32_t)ptr[i];
	return 0;
}
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libd__wctime32, libd__wctime64);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.time") WUNUSED ATTR_IN(1) char16_t *
NOTHROW_NCX(LIBDCALL libd__wctime32)(time32_t const *timer) {
	time64_t timer64 = (time64_t)*timer;
	return libd__wctime64(&timer64);
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc__wctime32, libc__wctime64);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
INTERN ATTR_SECTION(".text.crt.dos.wchar.time") WUNUSED ATTR_IN(1) char32_t *
NOTHROW_NCX(LIBKCALL libc__wctime32)(time32_t const *timer) {
	time64_t timer64 = (time64_t)*timer;
	return libc__wctime64(&timer64);
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.time") WUNUSED ATTR_IN(1) char16_t *
NOTHROW_NCX(LIBDCALL libd__wctime64)(time64_t const *timer) {
	static char16_t wctime64_retbuf[26];

	libd__wctime64_s(wctime64_retbuf, 26, timer);
	return wctime64_retbuf;



}
INTERN ATTR_SECTION(".text.crt.dos.wchar.time") WUNUSED ATTR_IN(1) char32_t *
NOTHROW_NCX(LIBKCALL libc__wctime64)(time64_t const *timer) {
	static char32_t wctime64_retbuf[26];

	libc__wctime64_s(wctime64_retbuf, 26, timer);
	return wctime64_retbuf;



}
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libd__wctime32_s, libd__wctime64_s);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.time") ATTR_IN(3) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBDCALL libd__wctime32_s)(char16_t *buf,
                                       size_t buflen,
                                       time32_t const *timer) {
	time64_t timer64 = (time64_t)*timer;
	return libd__wctime64_s(buf, buflen, &timer64);
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc__wctime32_s, libc__wctime64_s);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
INTERN ATTR_SECTION(".text.crt.dos.wchar.time") ATTR_IN(3) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBKCALL libc__wctime32_s)(char32_t *buf,
                                       size_t buflen,
                                       time32_t const *timer) {
	time64_t timer64 = (time64_t)*timer;
	return libc__wctime64_s(buf, buflen, &timer64);
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.time") ATTR_IN(3) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBDCALL libd__wctime64_s)(char16_t *buf,
                                       size_t buflen,
                                       time64_t const *timer) {
	char abuf[26], *ptr;
	unsigned int i;
	if unlikely(buflen < 26)
		return 34;
	ptr = libc_ctime64_r(timer, abuf);




	for (i = 0; i < 26; ++i)
		buf[i] = (char16_t)ptr[i]; /* Guarantied no unicode in here! */
	return 0;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.time") ATTR_IN(3) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBKCALL libc__wctime64_s)(char32_t *buf,
                                       size_t buflen,
                                       time64_t const *timer) {
	char abuf[26], *ptr;
	unsigned int i;
	if unlikely(buflen < 26)
		return ERANGE;
	ptr = libc_ctime64_r(timer, abuf);




	for (i = 0; i < 26; ++i)
		buf[i] = (char32_t)ptr[i]; /* Guarantied no unicode in here! */
	return 0;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.time") ATTR_OUT(1) char16_t *
NOTHROW_NCX(LIBDCALL libd__wstrtime)(char16_t buf[9]) {
	unsigned int i;
	char abuf[9], *ptr;
	ptr = libc__strtime(abuf);




	for (i = 0; i < 9; ++i)
		buf[i] = (char16_t)ptr[i]; /* Guarantied no unicode in here! */
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.time") ATTR_OUT(1) char32_t *
NOTHROW_NCX(LIBKCALL libc__wstrtime)(char32_t buf[9]) {
	unsigned int i;
	char abuf[9], *ptr;
	ptr = libc__strtime(abuf);




	for (i = 0; i < 9; ++i)
		buf[i] = (char32_t)ptr[i]; /* Guarantied no unicode in here! */
	return buf;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.time") ATTR_OUT(1) char16_t *
NOTHROW_NCX(LIBDCALL libd__wstrdate)(char16_t buf[9]) {
	unsigned int i;
	char abuf[9], *ptr;
	ptr = libc__strdate(abuf);




	for (i = 0; i < 9; ++i)
		buf[i] = (char16_t)ptr[i]; /* Guarantied no unicode in here! */
	return buf;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.time") ATTR_OUT(1) char32_t *
NOTHROW_NCX(LIBKCALL libc__wstrdate)(char32_t buf[9]) {
	unsigned int i;
	char abuf[9], *ptr;
	ptr = libc__strdate(abuf);




	for (i = 0; i < 9; ++i)
		buf[i] = (char32_t)ptr[i]; /* Guarantied no unicode in here! */
	return buf;
}
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.time") ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBDCALL libd__wstrtime_s)(char16_t *buf,
                                       size_t buflen) {
	if unlikely(buflen < 9)
		return 34;

	libd__wstrtime(buf);




	return 0;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.time") ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBKCALL libc__wstrtime_s)(char32_t *buf,
                                       size_t buflen) {
	if unlikely(buflen < 9)
		return ERANGE;

	libc__wstrtime(buf);




	return 0;
}
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.time") ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBDCALL libd__wstrdate_s)(char16_t *buf,
                                       size_t buflen) {
	if unlikely(buflen < 9)
		return 34;

	libd__wstrdate(buf);




	return 0;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.time") ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBKCALL libc__wstrdate_s)(char32_t *buf,
                                       size_t buflen) {
	if unlikely(buflen < 9)
		return ERANGE;

	libc__wstrdate(buf);




	return 0;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$_wasctime, libd__wasctime);
DEFINE_PUBLIC_ALIAS(_wasctime, libc__wasctime);
DEFINE_PUBLIC_ALIAS(DOS$_wasctime_s, libd__wasctime_s);
DEFINE_PUBLIC_ALIAS(_wasctime_s, libc__wasctime_s);
DEFINE_PUBLIC_ALIAS(DOS$_wctime, libd__wctime32);
DEFINE_PUBLIC_ALIAS(DOS$_wctime32, libd__wctime32);
DEFINE_PUBLIC_ALIAS(_wctime32, libc__wctime32);
DEFINE_PUBLIC_ALIAS(DOS$_wctime64, libd__wctime64);
DEFINE_PUBLIC_ALIAS(_wctime64, libc__wctime64);
DEFINE_PUBLIC_ALIAS(DOS$_wctime32_s, libd__wctime32_s);
DEFINE_PUBLIC_ALIAS(_wctime32_s, libc__wctime32_s);
DEFINE_PUBLIC_ALIAS(DOS$_wctime64_s, libd__wctime64_s);
DEFINE_PUBLIC_ALIAS(_wctime64_s, libc__wctime64_s);
DEFINE_PUBLIC_ALIAS(DOS$_wstrtime, libd__wstrtime);
DEFINE_PUBLIC_ALIAS(_wstrtime, libc__wstrtime);
DEFINE_PUBLIC_ALIAS(DOS$_wstrdate, libd__wstrdate);
DEFINE_PUBLIC_ALIAS(_wstrdate, libc__wstrdate);
DEFINE_PUBLIC_ALIAS(DOS$_wstrtime_s, libd__wstrtime_s);
DEFINE_PUBLIC_ALIAS(_wstrtime_s, libc__wstrtime_s);
DEFINE_PUBLIC_ALIAS(DOS$_wstrdate_s, libd__wstrdate_s);
DEFINE_PUBLIC_ALIAS(_wstrdate_s, libc__wstrdate_s);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_CORECRT_WTIME_C */
