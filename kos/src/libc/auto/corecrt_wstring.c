/* HASH CRC-32:0xc6e1033b */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_CORECRT_WSTRING_C
#define GUARD_LIBC_AUTO_CORECRT_WSTRING_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "corecrt_wstring.h"
#include "../user/stdlib.h"
#include "string.h"
#include "uchar.h"
#include "../user/wchar.h"
#include "wctype.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <libc/errno.h>
#include <bits/types.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.errno") char16_t *
NOTHROW_NCX(LIBDCALL libd__wcserror)(errno_t errno_value) {
	static char16_t *saved = NULL;
	char const *newmsg;

	errno_t saved_errno;

	newmsg = libd_strerror(errno_value);
	/*if unlikely(!newmsg) // `strerror()' returns non-NULL
		return NULL;*/

	/* Convert message. */

	saved_errno = __libc_geterrno();


	libc_free(saved);

	saved = libd_convert_mbstowcs(newmsg);

	__libc_seterrno(saved_errno);

	return saved;
}
#include <libc/errno.h>
#include <bits/types.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.errno") char32_t *
NOTHROW_NCX(LIBKCALL libc__wcserror)(errno_t errno_value) {
	static char32_t *saved = NULL;
	char const *newmsg;

	errno_t saved_errno;

	newmsg = libc_strerror(errno_value);
	/*if unlikely(!newmsg) // `strerror()' returns non-NULL
		return NULL;*/

	/* Convert message. */

	saved_errno = __libc_geterrno();


	libc_free(saved);

	saved = libc_convert_mbstowcs(newmsg);

	__libc_seterrno(saved_errno);

	return saved;
}
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.errno") ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBDCALL libd__wcserror_s)(char16_t *buf,
                                       size_t buflen,
                                       errno_t errno_value) {
	char16_t *msg  = libd__wcserror(errno_value);
	size_t msglen = libd_wcslen(msg) + 1;
	if (msglen >= buflen) {

		return 34;



	}
	(void)(char16_t *)libc_memcpyw(buf, msg, msglen);
	return 0;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.errno") ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBKCALL libc__wcserror_s)(char32_t *buf,
                                       size_t buflen,
                                       errno_t errno_value) {
	char32_t *msg  = libc__wcserror(errno_value);
	size_t msglen = libc_wcslen(msg) + 1;
	if (msglen >= buflen) {

		return ERANGE;



	}
	(void)(char32_t *)libc_memcpyl(buf, msg, msglen);
	return 0;
}
#include <libc/errno.h>
#include <bits/types.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.errno") ATTR_IN_OPT(1) char16_t *
NOTHROW_NCX(LIBDCALL libd___wcserror)(char16_t const *message) {
	static char16_t *saved = NULL;
	char const *newmsg;
	char *utf8_message;

	errno_t saved_errno;

	if (message == NULL) {
		newmsg = libc__strerror(NULL);
	} else {
		utf8_message = libd_convert_wcstombs(message);
		if unlikely(!utf8_message)
			return NULL;
		newmsg = libc__strerror(utf8_message);

		libc_free(utf8_message);

		if unlikely(!newmsg)
			return NULL;
	}

	/* Convert message. */

	saved_errno = __libc_geterrno();


	libc_free(saved);

	saved = libd_convert_mbstowcs(newmsg);

	__libc_seterrno(saved_errno);

	return saved;
}
#include <libc/errno.h>
#include <bits/types.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.errno") ATTR_IN_OPT(1) char32_t *
NOTHROW_NCX(LIBKCALL libc___wcserror)(char32_t const *message) {
	static char32_t *saved = NULL;
	char const *newmsg;
	char *utf8_message;

	errno_t saved_errno;

	if (message == NULL) {
		newmsg = libc__strerror(NULL);
	} else {
		utf8_message = libc_convert_wcstombs(message);
		if unlikely(!utf8_message)
			return NULL;
		newmsg = libc__strerror(utf8_message);

		libc_free(utf8_message);

		if unlikely(!newmsg)
			return NULL;
	}

	/* Convert message. */

	saved_errno = __libc_geterrno();


	libc_free(saved);

	saved = libc_convert_mbstowcs(newmsg);

	__libc_seterrno(saved_errno);

	return saved;
}
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.errno") ATTR_IN_OPT(3) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBDCALL libd___wcserror_s)(char16_t *buf,
                                        size_t buflen,
                                        char16_t const *message) {
	char16_t *msg  = libd___wcserror(message);
	size_t msglen;
	if (!msg) {

		return 22;



	}
	msglen = libd_wcslen(msg) + 1;
	if (msglen >= buflen) {

		return 34;



	}
	(void)(char16_t *)libc_memcpyw(buf, msg, msglen);
	return 0;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.errno") ATTR_IN_OPT(3) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBKCALL libc___wcserror_s)(char32_t *buf,
                                        size_t buflen,
                                        char32_t const *message) {
	char32_t *msg  = libc___wcserror(message);
	size_t msglen;
	if (!msg) {

		return EINVAL;



	}
	msglen = libc_wcslen(msg) + 1;
	if (msglen >= buflen) {

		return ERANGE;



	}
	(void)(char32_t *)libc_memcpyl(buf, msg, msglen);
	return 0;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
#include <libc/string.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_INOUTS(1, 4) errno_t
NOTHROW_NCX(LIBDCALL libd__wcsnset_s)(char16_t *__restrict buf,
                                      size_t buflen,
                                      char16_t ch,
                                      size_t maxlen) {
	char16_t *iter;
	size_t remaining;
	if (maxlen == 0 && buf == NULL && buflen == 0)
		return 0;
	if (!buf && buflen)
		return 22;
	if (maxlen >= buflen)
		return 34;
	iter = buf;
	remaining = buflen;
	while (*iter != 0 && maxlen && --remaining) {
		*iter++ = (char16_t)ch;
		--maxlen;
	}
	if (!maxlen) {
		while (*iter && --remaining)
			++iter;
	}
	if (!remaining) {
		__libc_memsetc(buf, 0, buflen, 2);
		return 22;
	}
	__libc_memsetc(iter, 0, remaining, 2);
	return 0;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_INOUTS(1, 4) errno_t
NOTHROW_NCX(LIBKCALL libc__wcsnset_s)(char32_t *__restrict buf,
                                      size_t buflen,
                                      char32_t ch,
                                      size_t maxlen) {
	char32_t *iter;
	size_t remaining;
	if (maxlen == 0 && buf == NULL && buflen == 0)
		return 0;
	if (!buf && buflen)
		return 22;
	if (maxlen >= buflen)
		return 34;
	iter = buf;
	remaining = buflen;
	while (*iter != 0 && maxlen && --remaining) {
		*iter++ = (char32_t)ch;
		--maxlen;
	}
	if (!maxlen) {
		while (*iter && --remaining)
			++iter;
	}
	if (!remaining) {
		__libc_memsetc(buf, 0, buflen, 4);
		return 22;
	}
	__libc_memsetc(iter, 0, remaining, 4);
	return 0;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
#include <libc/string.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_INOUTS(1, 2) errno_t
NOTHROW_NCX(LIBDCALL libd__wcsset_s)(char16_t *dst,
                                     size_t dstsize,
                                     char16_t ch) {
	char16_t *p;
	size_t remaining;
	if (!dst && dstsize != 0)
		return 22;
	p = dst;
	remaining = dstsize;
	while (*p && --remaining != 0)
		*p++ = (char16_t)ch;
	if (remaining == 0) {
		__libc_memsetc(dst, 0, dstsize, 2);
		return 22;
	}
	__libc_memsetc(p, 0, remaining, 2);
	return 0;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_INOUTS(1, 2) errno_t
NOTHROW_NCX(LIBKCALL libc__wcsset_s)(char32_t *dst,
                                     size_t dstsize,
                                     char32_t ch) {
	char32_t *p;
	size_t remaining;
	if (!dst && dstsize != 0)
		return 22;
	p = dst;
	remaining = dstsize;
	while (*p && --remaining != 0)
		*p++ = (char32_t)ch;
	if (remaining == 0) {
		__libc_memsetc(dst, 0, dstsize, 4);
		return 22;
	}
	__libc_memsetc(p, 0, remaining, 4);
	return 0;
}
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_INOUT_OPT(1) errno_t
NOTHROW_NCX(LIBDCALL libd__wcslwr_s)(char16_t *buf,
                                     size_t buflen) {
	char16_t *iter, ch;
	if (buf == NULL)
		return 22;
	if (libd_wcsnlen(buf, buflen) >= buflen)
		return 22;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libd_towlower((char16_t)ch);
	return 0;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_INOUT_OPT(1) errno_t
NOTHROW_NCX(LIBKCALL libc__wcslwr_s)(char32_t *buf,
                                     size_t buflen) {
	char32_t *iter, ch;
	if (buf == NULL)
		return 22;
	if (libc_wcsnlen(buf, buflen) >= buflen)
		return 22;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towlower((char32_t)ch);
	return 0;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_INOUT_OPT(1) errno_t
NOTHROW_NCX(LIBDCALL libd__wcsupr_s)(char16_t *buf,
                                     size_t buflen) {
	char16_t *iter, ch;
	if (buf == NULL)
		return 22;
	if (libd_wcsnlen(buf, buflen) >= buflen)
		return 22;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libd_towupper((char16_t)ch);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.memory") ATTR_INOUT_OPT(1) errno_t
NOTHROW_NCX(LIBKCALL libc__wcsupr_s)(char32_t *buf,
                                     size_t buflen) {
	char32_t *iter, ch;
	if (buf == NULL)
		return 22;
	if (libc_wcsnlen(buf, buflen) >= buflen)
		return 22;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towupper((char32_t)ch);
	return 0;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_INOUT_OPT(1) errno_t
NOTHROW_NCX(LIBDCALL libd__wcslwr_s_l)(char16_t *buf,
                                       size_t buflen,
                                       locale_t locale) {
	char16_t *iter, ch;
	if (buf == NULL)
		return 22;
	if (libd_wcsnlen(buf, buflen) >= buflen)
		return 22;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libd_towlower_l((char16_t)ch, locale);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_INOUT_OPT(1) errno_t
NOTHROW_NCX(LIBKCALL libc__wcslwr_s_l)(char32_t *buf,
                                       size_t buflen,
                                       locale_t locale) {
	char32_t *iter, ch;
	if (buf == NULL)
		return 22;
	if (libc_wcsnlen(buf, buflen) >= buflen)
		return 22;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towlower_l((char32_t)ch, locale);
	return 0;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_INOUT_OPT(1) errno_t
NOTHROW_NCX(LIBDCALL libd__wcsupr_s_l)(char16_t *buf,
                                       size_t buflen,
                                       locale_t locale) {
	char16_t *iter, ch;
	if (buf == NULL)
		return 22;
	if (libd_wcsnlen(buf, buflen) >= buflen)
		return 22;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char16_t)libd_towupper_l((char16_t)ch, locale);
	return 0;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") ATTR_INOUT_OPT(1) errno_t
NOTHROW_NCX(LIBKCALL libc__wcsupr_s_l)(char32_t *buf,
                                       size_t buflen,
                                       locale_t locale) {
	char32_t *iter, ch;
	if (buf == NULL)
		return 22;
	if (libc_wcsnlen(buf, buflen) >= buflen)
		return 22;
	for (iter = buf; (ch = *iter) != '\0'; ++iter)
		*iter = (char32_t)libc_towupper_l((char32_t)ch, locale);
	return 0;
}
#include <libc/errno.h>
#include <libc/string.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_INS(3, 4) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBDCALL libd_wmemcpy_s)(char16_t *dst,
                                     rsize_t dstlength,
                                     char16_t const *src,
                                     rsize_t srclength) {
	if (!srclength)
		return 0;
	if (dst == NULL)
		return 22;
	if (!src || dstlength < srclength) {
		__libc_memsetc(dst, 0, dstlength, 2);
		if (!src)
			return 22;
		if (dstlength < srclength)
			return 34;
		return 22;
	}
	__libc_memcpyc(dst, src, srclength, 2);
	return 0;
}
#include <libc/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_INS(3, 4) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBKCALL libc_wmemcpy_s)(char32_t *dst,
                                     rsize_t dstlength,
                                     char32_t const *src,
                                     rsize_t srclength) {
	if (!srclength)
		return 0;
	if (dst == NULL)
		return 22;
	if (!src || dstlength < srclength) {
		__libc_memsetc(dst, 0, dstlength, 4);
		if (!src)
			return 22;
		if (dstlength < srclength)
			return 34;
		return 22;
	}
	__libc_memcpyc(dst, src, srclength, 4);
	return 0;
}
#include <libc/errno.h>
#include <libc/string.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_INS(3, 4) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBDCALL libd_wmemmove_s)(char16_t *dst,
                                      rsize_t dstlength,
                                      char16_t const *src,
                                      rsize_t srclength) {
	if (!srclength)
		return 0;
	if (!dst || !src)
		return 22;
	if (dstlength < srclength)
		return 34;
	__libc_memmovec(dst, src, srclength, 2);
	return 0;
}
#include <libc/errno.h>
#include <libc/string.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_INS(3, 4) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBKCALL libc_wmemmove_s)(char32_t *dst,
                                      rsize_t dstlength,
                                      char32_t const *src,
                                      rsize_t srclength) {
	if (!srclength)
		return 0;
	if (!dst || !src)
		return 22;
	if (dstlength < srclength)
		return 34;
	__libc_memmovec(dst, src, srclength, 4);
	return 0;
}
#include <libc/errno.h>
/* >> wcscat_s(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_INOUT_OPT(1) ATTR_IN_OPT(3) errno_t
NOTHROW_NCX(LIBDCALL libd_wcscat_s)(char16_t *dst,
                                    size_t dstsize,
                                    char16_t const *src) {
	if (!dst || !src)
		return 22;
	while (dstsize && *dst) {
		++dst;
		--dstsize;
	}
	if (!dstsize)
		return 22;
	while ((*dst++ = *src++) != 0 && --dstsize)
		;
	if (!dstsize)
		return 34;
	return 0;
}
#include <libc/errno.h>
/* >> wcscat_s(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_INOUT_OPT(1) ATTR_IN_OPT(3) errno_t
NOTHROW_NCX(LIBKCALL libc_wcscat_s)(char32_t *dst,
                                    size_t dstsize,
                                    char32_t const *src) {
	if (!dst || !src)
		return 22;
	while (dstsize && *dst) {
		++dst;
		--dstsize;
	}
	if (!dstsize)
		return 22;
	while ((*dst++ = *src++) != 0 && --dstsize)
		;
	if (!dstsize)
		return 34;
	return 0;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
#include <libc/string.h>
/* >> wcscpy_s(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_IN_OPT(3) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBDCALL libd_wcscpy_s)(char16_t *dst,
                                    size_t dstsize,
                                    char16_t const *src) {
	char16_t *iter;
	size_t remaining;
	if ((!dst && dstsize) || !src)
		return 22;
	iter = dst;
	remaining = dstsize;
	while ((*iter++ = *src++) != 0 && --remaining)
		;
	if (!remaining) {
		__libc_memsetc(dst, 0, dstsize, 2);
		return 34;
	}
	__libc_memsetc(iter, 0, remaining, 2);
	return 0;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
#include <libc/string.h>
/* >> wcscpy_s(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_IN_OPT(3) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBKCALL libc_wcscpy_s)(char32_t *dst,
                                    size_t dstsize,
                                    char32_t const *src) {
	char32_t *iter;
	size_t remaining;
	if ((!dst && dstsize) || !src)
		return 22;
	iter = dst;
	remaining = dstsize;
	while ((*iter++ = *src++) != 0 && --remaining)
		;
	if (!remaining) {
		__libc_memsetc(dst, 0, dstsize, 4);
		return 34;
	}
	__libc_memsetc(iter, 0, remaining, 4);
	return 0;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
#include <libc/string.h>
/* >> wcsncat_s(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_INOUT_OPT(1) ATTR_IN_OPT(3) errno_t
NOTHROW_NCX(LIBDCALL libd_wcsncat_s)(char16_t *dst,
                                     rsize_t dstsize,
                                     const char16_t *src,
                                     rsize_t maxlen) {
	char16_t *iter;
	size_t remaining;
	if (!maxlen && !dst && !dstsize)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return 22;
	for (iter = dst, remaining = dstsize; remaining && *iter; ++iter, --remaining)
		;
	if (!remaining) {
		__libc_memsetc(dst, 0, dstsize, 2);
		return 22;
	}
	if (maxlen == (size_t)-1) {
		while ((*iter++ = *src++) != 0 && --dstsize)
			;
	} else {
		if (maxlen >= remaining)
			return 34;
		while (maxlen && (*iter++ = *src++) != 0 && --remaining)
			--maxlen;
		if (!maxlen)
			*iter = 0;
	}
	if (!remaining) {
		if (maxlen == (size_t)-1) {
			dst[dstsize - 1] = 0;
			return 80;
		}
		__libc_memsetc(dst, 0, dstsize, 2);
		return 34;
	}
	__libc_memsetc(iter, 0, remaining, 2);
	return 0;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
#include <libc/string.h>
/* >> wcsncat_s(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_INOUT_OPT(1) ATTR_IN_OPT(3) errno_t
NOTHROW_NCX(LIBKCALL libc_wcsncat_s)(char32_t *dst,
                                     rsize_t dstsize,
                                     const char32_t *src,
                                     rsize_t maxlen) {
	char32_t *iter;
	size_t remaining;
	if (!maxlen && !dst && !dstsize)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return 22;
	for (iter = dst, remaining = dstsize; remaining && *iter; ++iter, --remaining)
		;
	if (!remaining) {
		__libc_memsetc(dst, 0, dstsize, 4);
		return 22;
	}
	if (maxlen == (size_t)-1) {
		while ((*iter++ = *src++) != 0 && --dstsize)
			;
	} else {
		if (maxlen >= remaining)
			return 34;
		while (maxlen && (*iter++ = *src++) != 0 && --remaining)
			--maxlen;
		if (!maxlen)
			*iter = 0;
	}
	if (!remaining) {
		if (maxlen == (size_t)-1) {
			dst[dstsize - 1] = 0;
			return 80;
		}
		__libc_memsetc(dst, 0, dstsize, 4);
		return 34;
	}
	__libc_memsetc(iter, 0, remaining, 4);
	return 0;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
#include <libc/string.h>
/* >> wcsncpy_s(3) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_IN_OPT(3) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBDCALL libd_wcsncpy_s)(char16_t *dst,
                                     size_t dstsize,
                                     char16_t const *src,
                                     size_t maxlen) {
	char16_t *iter;
	size_t remaining;
	if (maxlen == 0 && dst == NULL && dstsize == 0)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return 22;
	if (!maxlen) {
		__libc_memsetc(dst, 0, dstsize, 2);
		return 0;
	}
	iter = dst;
	remaining = dstsize;
	if (maxlen == (size_t)-1) {
		while ((*iter++ = *src++) != 0 && --remaining)
			;
	} else {
		if (maxlen >= remaining)
			return 34;
		while ((*iter++ = *src++) != 0 && --remaining && --maxlen)
			;
		if (!maxlen)
			*iter = 0;
	}
	if (!remaining) {
		if (maxlen == (size_t)-1) {
			dst[dstsize - 1] = 0;
			return 80;
		}
		__libc_memsetc(dst, 0, dstsize, 2);
		return 34;
	}
	__libc_memsetc(iter, 0, remaining, 2);
	return 0;
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
#include <libc/string.h>
/* >> wcsncpy_s(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") ATTR_IN_OPT(3) ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBKCALL libc_wcsncpy_s)(char32_t *dst,
                                     size_t dstsize,
                                     char32_t const *src,
                                     size_t maxlen) {
	char32_t *iter;
	size_t remaining;
	if (maxlen == 0 && dst == NULL && dstsize == 0)
		return 0;
	if ((!dst && dstsize) || (!src && maxlen))
		return 22;
	if (!maxlen) {
		__libc_memsetc(dst, 0, dstsize, 4);
		return 0;
	}
	iter = dst;
	remaining = dstsize;
	if (maxlen == (size_t)-1) {
		while ((*iter++ = *src++) != 0 && --remaining)
			;
	} else {
		if (maxlen >= remaining)
			return 34;
		while ((*iter++ = *src++) != 0 && --remaining && --maxlen)
			;
		if (!maxlen)
			*iter = 0;
	}
	if (!remaining) {
		if (maxlen == (size_t)-1) {
			dst[dstsize - 1] = 0;
			return 80;
		}
		__libc_memsetc(dst, 0, dstsize, 4);
		return 34;
	}
	__libc_memsetc(iter, 0, remaining, 4);
	return 0;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$_wcserror, libd__wcserror);
DEFINE_PUBLIC_ALIAS(_wcserror, libc__wcserror);
DEFINE_PUBLIC_ALIAS(DOS$_wcserror_s, libd__wcserror_s);
DEFINE_PUBLIC_ALIAS(_wcserror_s, libc__wcserror_s);
DEFINE_PUBLIC_ALIAS(DOS$__wcserror, libd___wcserror);
DEFINE_PUBLIC_ALIAS(__wcserror, libc___wcserror);
DEFINE_PUBLIC_ALIAS(DOS$__wcserror_s, libd___wcserror_s);
DEFINE_PUBLIC_ALIAS(__wcserror_s, libc___wcserror_s);
DEFINE_PUBLIC_ALIAS(DOS$_wcsnset_s, libd__wcsnset_s);
DEFINE_PUBLIC_ALIAS(_wcsnset_s, libc__wcsnset_s);
DEFINE_PUBLIC_ALIAS(DOS$_wcsset_s, libd__wcsset_s);
DEFINE_PUBLIC_ALIAS(_wcsset_s, libc__wcsset_s);
DEFINE_PUBLIC_ALIAS(DOS$_wcslwr_s, libd__wcslwr_s);
DEFINE_PUBLIC_ALIAS(_wcslwr_s, libc__wcslwr_s);
DEFINE_PUBLIC_ALIAS(DOS$_wcsupr_s, libd__wcsupr_s);
DEFINE_PUBLIC_ALIAS(_wcsupr_s, libc__wcsupr_s);
DEFINE_PUBLIC_ALIAS(DOS$_wcslwr_s_l, libd__wcslwr_s_l);
DEFINE_PUBLIC_ALIAS(_wcslwr_s_l, libc__wcslwr_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_wcsupr_s_l, libd__wcsupr_s_l);
DEFINE_PUBLIC_ALIAS(_wcsupr_s_l, libc__wcsupr_s_l);
DEFINE_PUBLIC_ALIAS(DOS$wmemcpy_s, libd_wmemcpy_s);
DEFINE_PUBLIC_ALIAS(wmemcpy_s, libc_wmemcpy_s);
DEFINE_PUBLIC_ALIAS(DOS$wmemmove_s, libd_wmemmove_s);
DEFINE_PUBLIC_ALIAS(wmemmove_s, libc_wmemmove_s);
DEFINE_PUBLIC_ALIAS(DOS$wcscat_s, libd_wcscat_s);
DEFINE_PUBLIC_ALIAS(wcscat_s, libc_wcscat_s);
DEFINE_PUBLIC_ALIAS(DOS$wcscpy_s, libd_wcscpy_s);
DEFINE_PUBLIC_ALIAS(wcscpy_s, libc_wcscpy_s);
DEFINE_PUBLIC_ALIAS(DOS$wcsncat_s, libd_wcsncat_s);
DEFINE_PUBLIC_ALIAS(wcsncat_s, libc_wcsncat_s);
DEFINE_PUBLIC_ALIAS(DOS$wcsncpy_s, libd_wcsncpy_s);
DEFINE_PUBLIC_ALIAS(wcsncpy_s, libc_wcsncpy_s);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_CORECRT_WSTRING_C */
