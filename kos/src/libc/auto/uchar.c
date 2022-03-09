/* HASH CRC-32:0x7967ffd8 */
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
#ifndef GUARD_LIBC_AUTO_UCHAR_C
#define GUARD_LIBC_AUTO_UCHAR_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "uchar.h"
#include "format-printer.h"
#include "parts.wchar.format-printer.h"
#include "../user/stdlib.h"
#include "../user/string.h"
#include "../user/unicode.h"
#include "../user/wchar.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.wchar.unicode.convert") void
NOTHROW_NCX(LIBCCALL libc_convert_freev)(void *vector) {
	void **iter, *temp;
	if unlikely(!vector)
		return;
	for (iter = (void **)vector; (temp = *iter) != NULL; ++iter)
		libc_free(temp);
	libc_free(vector);
}
INTERN ATTR_SECTION(".text.crt.wchar.unicode.convert") void
NOTHROW_NCX(LIBCCALL libc_convert_freevn)(void *vector,
                                          size_t count) {
	size_t i;
	if unlikely(!vector)
		return;
	for (i = 0; i < count; ++i)
		libc_free(((void **)vector)[i]);
	libc_free(vector);
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.convert") ATTR_MALLOC WUNUSED char *
NOTHROW_NCX(LIBDCALL libd_convert_wcstombs)(char16_t const *str) {
	if unlikely(!str) {
#ifdef EINVAL
		(void)libc_seterrno(EINVAL);
#endif /* EINVAL */
		return NULL;
	}
	return libd_convert_wcstombsn(str, libd_wcslen(str), NULL);
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.convert") ATTR_MALLOC WUNUSED char *
NOTHROW_NCX(LIBKCALL libc_convert_wcstombs)(char32_t const *str) {
	if unlikely(!str) {
#ifdef EINVAL
		(void)libc_seterrno(EINVAL);
#endif /* EINVAL */
		return NULL;
	}
	return libc_convert_wcstombsn(str, libc_wcslen(str), NULL);
}
#include <libc/errno.h>
#include <bits/crt/format-printer.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.convert") ATTR_MALLOC WUNUSED char *
NOTHROW_NCX(LIBDCALL libd_convert_wcstombsn)(char16_t const *__restrict str,
                                             size_t len,
                                             size_t *preslen) {
	struct __local_format_wto8_data {
		__pformatprinter fd_printer;   /* [1..1] Inner printer */
		void            *fd_arg;       /* Argument for `fd_printer' */

		char16_t         fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */

	};
	struct __local_format_aprintf_data {
		char         *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
		__SIZE_TYPE__ ap_avail; /* Unused buffer size */
		__SIZE_TYPE__ ap_used;  /* Used buffer size */
	};
	struct __local_format_aprintf_data printer_data = { NULL, 0, 0 };
	struct __local_format_wto8_data convert_data;
	convert_data.fd_printer   = &libc_format_aprintf_printer;
	convert_data.fd_arg       = &printer_data;

	convert_data.fd_surrogate = 0;

	if unlikely(libd_format_wto8(&convert_data, str, len) < 0) {

		libc_free(printer_data.ap_base);

		return NULL;
	}
	return libc_format_aprintf_pack((struct format_aprintf_data *)&printer_data, preslen);
}
#include <libc/errno.h>
#include <bits/crt/format-printer.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.convert") ATTR_MALLOC WUNUSED char *
NOTHROW_NCX(LIBKCALL libc_convert_wcstombsn)(char32_t const *__restrict str,
                                             size_t len,
                                             size_t *preslen) {
	struct __local_format_wto8_data {
		__pformatprinter fd_printer;   /* [1..1] Inner printer */
		void            *fd_arg;       /* Argument for `fd_printer' */



	};
	struct __local_format_aprintf_data {
		char         *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
		__SIZE_TYPE__ ap_avail; /* Unused buffer size */
		__SIZE_TYPE__ ap_used;  /* Used buffer size */
	};
	struct __local_format_aprintf_data printer_data = { NULL, 0, 0 };
	struct __local_format_wto8_data convert_data;
	convert_data.fd_printer   = &libc_format_aprintf_printer;
	convert_data.fd_arg       = &printer_data;



	if unlikely(libc_format_wto8(&convert_data, str, len) < 0) {

		libc_free(printer_data.ap_base);

		return NULL;
	}
	return libc_format_aprintf_pack((struct format_aprintf_data *)&printer_data, preslen);
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.convert") ATTR_MALLOC WUNUSED char **
NOTHROW_NCX(LIBDCALL libd_convert_wcstombsv)(char16_t const *const *__restrict vector) {
	size_t count = 0;
	if unlikely(!vector) {
#ifdef EINVAL
		(void)libc_seterrno(EINVAL);
#endif /* EINVAL */
		return NULL;
	}
	for (count = 0; vector[count]; ++count)
		;
	return libd_convert_wcstombsvn(vector, count);
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.convert") ATTR_MALLOC WUNUSED char **
NOTHROW_NCX(LIBKCALL libc_convert_wcstombsv)(char32_t const *const *__restrict vector) {
	size_t count = 0;
	if unlikely(!vector) {
#ifdef EINVAL
		(void)libc_seterrno(EINVAL);
#endif /* EINVAL */
		return NULL;
	}
	for (count = 0; vector[count]; ++count)
		;
	return libc_convert_wcstombsvn(vector, count);
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.convert") ATTR_MALLOC WUNUSED char **
NOTHROW_NCX(LIBDCALL libd_convert_wcstombsvn)(char16_t const *const *__restrict vector,
                                              size_t count) {
	size_t i;
	char **result;
	result = (char **)libc_malloc((count + 1) * sizeof(char *));
	if likely(result) {
		for (i = 0; i < count; ++i) {
			char *temp;
			temp = libd_convert_wcstombs(vector[i]);
			if unlikely(!temp)
				goto err;
			result[i] = temp;
		}
		result[i] = NULL;
	}
	return result;
err:

	while (i--)
		libc_free(result[i]);
	libc_free(result);

	return NULL;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.convert") ATTR_MALLOC WUNUSED char **
NOTHROW_NCX(LIBKCALL libc_convert_wcstombsvn)(char32_t const *const *__restrict vector,
                                              size_t count) {
	size_t i;
	char **result;
	result = (char **)libc_malloc((count + 1) * sizeof(char *));
	if likely(result) {
		for (i = 0; i < count; ++i) {
			char *temp;
			temp = libc_convert_wcstombs(vector[i]);
			if unlikely(!temp)
				goto err;
			result[i] = temp;
		}
		result[i] = NULL;
	}
	return result;
err:

	while (i--)
		libc_free(result[i]);
	libc_free(result);

	return NULL;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.convert") ATTR_MALLOC WUNUSED char16_t *
NOTHROW_NCX(LIBDCALL libd_convert_mbstowcs)(char const *__restrict str) {
	if unlikely(!str) {
#ifdef EINVAL
		(void)libc_seterrno(EINVAL);
#endif /* EINVAL */
		return NULL;
	}
	return libd_convert_mbstowcsn(str, libc_strlen(str), NULL);
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.convert") ATTR_MALLOC WUNUSED char32_t *
NOTHROW_NCX(LIBKCALL libc_convert_mbstowcs)(char const *__restrict str) {
	if unlikely(!str) {
#ifdef EINVAL
		(void)libc_seterrno(EINVAL);
#endif /* EINVAL */
		return NULL;
	}
	return libc_convert_mbstowcsn(str, libc_strlen(str), NULL);
}
#include <libc/errno.h>
#include <bits/crt/uformat-printer.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.convert") ATTR_MALLOC WUNUSED char16_t *
NOTHROW_NCX(LIBDCALL libd_convert_mbstowcsn)(char const *__restrict str,
                                             size_t len,
                                             size_t *preslen) {
	struct __local_format_waprintf_data {
		char16_t      *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
		__SIZE_TYPE__ ap_avail; /* Unused buffer size */
		__SIZE_TYPE__ ap_used;  /* Used buffer size */
	};
	struct __local_format_8tow_data {
		__pc16formatprinter fd_printer;    /* [1..1] Inner printer */
		void             *fd_arg;        /* Argument for `fd_printer' */
		__UINT32_TYPE__   fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	};
	struct __local_format_waprintf_data printer_data = { NULL, 0, 0 };
	struct __local_format_8tow_data convert_data;
	convert_data.fd_printer    = &libd_format_waprintf_printer;
	convert_data.fd_arg        = &printer_data;
	convert_data.fd_incomplete = 0;
	if unlikely(libd_format_8tow(&convert_data, str, len) < 0) {

		libc_free(printer_data.ap_base);

		return NULL;
	}
	return libd_format_waprintf_pack((struct format_c16aprintf_data *)&printer_data, preslen);
}
#include <libc/errno.h>
#include <bits/crt/uformat-printer.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.convert") ATTR_MALLOC WUNUSED char32_t *
NOTHROW_NCX(LIBKCALL libc_convert_mbstowcsn)(char const *__restrict str,
                                             size_t len,
                                             size_t *preslen) {
	struct __local_format_waprintf_data {
		char32_t      *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
		__SIZE_TYPE__ ap_avail; /* Unused buffer size */
		__SIZE_TYPE__ ap_used;  /* Used buffer size */
	};
	struct __local_format_8tow_data {
		__pc32formatprinter fd_printer;    /* [1..1] Inner printer */
		void             *fd_arg;        /* Argument for `fd_printer' */
		__UINT32_TYPE__   fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	};
	struct __local_format_waprintf_data printer_data = { NULL, 0, 0 };
	struct __local_format_8tow_data convert_data;
	convert_data.fd_printer    = &libc_format_waprintf_printer;
	convert_data.fd_arg        = &printer_data;
	convert_data.fd_incomplete = 0;
	if unlikely(libc_format_8tow(&convert_data, str, len) < 0) {

		libc_free(printer_data.ap_base);

		return NULL;
	}
	return libc_format_waprintf_pack((struct format_c32aprintf_data *)&printer_data, preslen);
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.convert") ATTR_MALLOC WUNUSED char16_t **
NOTHROW_NCX(LIBDCALL libd_convert_mbstowcsv)(char const *const *__restrict vector) {
	size_t count = 0;
	if unlikely(!vector) {
#ifdef EINVAL
		(void)libc_seterrno(EINVAL);
#endif /* EINVAL */
		return NULL;
	}
	for (count = 0; vector[count]; ++count)
		;
	return libd_convert_mbstowcsvn(vector, count);
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.convert") ATTR_MALLOC WUNUSED char32_t **
NOTHROW_NCX(LIBKCALL libc_convert_mbstowcsv)(char const *const *__restrict vector) {
	size_t count = 0;
	if unlikely(!vector) {
#ifdef EINVAL
		(void)libc_seterrno(EINVAL);
#endif /* EINVAL */
		return NULL;
	}
	for (count = 0; vector[count]; ++count)
		;
	return libc_convert_mbstowcsvn(vector, count);
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.convert") ATTR_MALLOC WUNUSED char16_t **
NOTHROW_NCX(LIBDCALL libd_convert_mbstowcsvn)(char const *const *__restrict vector,
                                              size_t count) {
	size_t i;
	char16_t **result;
	result = (char16_t **)libc_malloc((count + 1) * sizeof(char16_t *));
	if likely(result) {
		for (i = 0; i < count; ++i) {
			char16_t *temp;
			temp = libd_convert_mbstowcs(vector[i]);
			if unlikely(!temp)
				goto err;
			result[i] = temp;
		}
		result[i] = NULL;
	}
	return result;
err:

	while (i--)
		libc_free(result[i]);
	libc_free(result);

	return NULL;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.convert") ATTR_MALLOC WUNUSED char32_t **
NOTHROW_NCX(LIBKCALL libc_convert_mbstowcsvn)(char const *const *__restrict vector,
                                              size_t count) {
	size_t i;
	char32_t **result;
	result = (char32_t **)libc_malloc((count + 1) * sizeof(char32_t *));
	if likely(result) {
		for (i = 0; i < count; ++i) {
			char32_t *temp;
			temp = libc_convert_mbstowcs(vector[i]);
			if unlikely(!temp)
				goto err;
			result[i] = temp;
		}
		result[i] = NULL;
	}
	return result;
err:

	while (i--)
		libc_free(result[i]);
	libc_free(result);

	return NULL;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(convert_freev, libc_convert_freev);
DEFINE_PUBLIC_ALIAS(convert_freevn, libc_convert_freevn);
DEFINE_PUBLIC_ALIAS(DOS$convert_wcstombs, libd_convert_wcstombs);
DEFINE_PUBLIC_ALIAS(convert_wcstombs, libc_convert_wcstombs);
DEFINE_PUBLIC_ALIAS(DOS$convert_wcstombsn, libd_convert_wcstombsn);
DEFINE_PUBLIC_ALIAS(convert_wcstombsn, libc_convert_wcstombsn);
DEFINE_PUBLIC_ALIAS(DOS$convert_wcstombsv, libd_convert_wcstombsv);
DEFINE_PUBLIC_ALIAS(convert_wcstombsv, libc_convert_wcstombsv);
DEFINE_PUBLIC_ALIAS(DOS$convert_wcstombsvn, libd_convert_wcstombsvn);
DEFINE_PUBLIC_ALIAS(convert_wcstombsvn, libc_convert_wcstombsvn);
DEFINE_PUBLIC_ALIAS(DOS$convert_mbstowcs, libd_convert_mbstowcs);
DEFINE_PUBLIC_ALIAS(convert_mbstowcs, libc_convert_mbstowcs);
DEFINE_PUBLIC_ALIAS(DOS$convert_mbstowcsn, libd_convert_mbstowcsn);
DEFINE_PUBLIC_ALIAS(convert_mbstowcsn, libc_convert_mbstowcsn);
DEFINE_PUBLIC_ALIAS(DOS$convert_mbstowcsv, libd_convert_mbstowcsv);
DEFINE_PUBLIC_ALIAS(convert_mbstowcsv, libc_convert_mbstowcsv);
DEFINE_PUBLIC_ALIAS(DOS$convert_mbstowcsvn, libd_convert_mbstowcsvn);
DEFINE_PUBLIC_ALIAS(convert_mbstowcsvn, libc_convert_mbstowcsvn);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_UCHAR_C */
