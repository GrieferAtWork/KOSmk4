/* HASH CRC-32:0xb0519daf */
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
#ifndef GUARD_LIBC_AUTO_UCHAR_C
#define GUARD_LIBC_AUTO_UCHAR_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "uchar.h"
#include "format-printer.h"
#include "parts.wchar.format-printer.h"
#include "../user/stdlib.h"
#include "string.h"
#include "../user/unicode.h"
#include "../user/wchar.h"

DECL_BEGIN

#include "../libc/globals.h"
#ifndef __KERNEL__
/* >> mbrtoc8(3)
 * Convert a multi-byte string into utf-8
 * @param: pc8:    Output buffer for utf-8 byte (or `NULL' to discard conversion output)
 * @param: str:    Multi-byte input string (when `NULL', same as `mbrtoc8(pc8, "", 1, mbs)')
 * @param: maxlen: The max # of bytes to read starting at `str'
 * @param: mbs:    Multi-byte shift state, or `NULL' to use an internal buffer
 * @return: * : The number of bytes consumed from `str' to fill
 *              in `*pc8' and update `mbs' (always `<= maxlen')
 * @return: 0 : The character written to `*pc8' is the NUL-character, and `*mbs' was reset
 * @return: (size_t)-3: `*pc8' was populated from `mbs', but nothing was read from `str'
 * @return: (size_t)-2: Incomplete sequence; "mbs" was updated and all "maxlen"
 *                      bytes were read, but no  full utf-8 byte was  produced.
 * @return: (size_t)-1: [errno=EILSEQ] Given `mbs+str+maxlen' cannot be decoded */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_INOUT_OPT(4) ATTR_IN_OPT(2) ATTR_OUT_OPT(1) size_t
NOTHROW_NCX(LIBCCALL libc_mbrtoc8)(char8_t *pc8,
                                   char const *__restrict str,
                                   size_t maxlen,
                                   mbstate_t *mbs) {
	/* We only support UTF-8 locales, so this function is pretty
	 * much just a  no-op that simply  forwards data from  `str'
	 * into `*pc8' */

	if (mbs == NULL)
		mbs = &_mb_shift;

	if (str == NULL) {
reset_mbs:



		{
			mbstate_init(mbs);
		}
		return 0;
	}
	if (maxlen == 0)
		return 0;
	if (*str == '\0')
		goto reset_mbs;
	if likely(pc8 != NULL)
		*pc8 = *str;
	return 1;
}
/* >> c8rtomb(3)
 * Convert utf-8 into a multi-byte string
 * @param: str: Multi-byte output buffer (when `NULL', same as `char buf[MB_CUR_MAX]; c8rtomb(buf, u8'\0', mbs);')
 * @param: c8:  UTF-8 byte to convert into its multi-byte representation
 * @param: mbs: Multi-byte shift state, or `NULL' to use an internal buffer
 * @return: * : The number of bytes written starting at `str'
 * @return: (size_t)-1: [errno=EILSEQ] Given `mbs+c8' cannot be encoded as multi-byte */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") ATTR_INOUT_OPT(3) ATTR_OUT_OPT(1) size_t
NOTHROW_NCX(LIBCCALL libc_c8rtomb)(char *__restrict str,
                                   char8_t c8,
                                   mbstate_t *mbs) {
	/* We only support UTF-8 locales, so this function is pretty
	 * much  just a  no-op that  simply forwards  data from `c8'
	 * into `*str' */
	if (str == NULL) {

		if (!mbs)
			mbs = &_mb_shift;



		{
			mbstate_init(mbs);
		}
	} else {
		*str = c8;
	}
	return 1;
}
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.convert") ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char *
NOTHROW_NCX(LIBDCALL libd_convert_wcstombs)(char16_t const *str) {
	if unlikely(!str) {

		(void)libc_seterrno(EINVAL);

		return NULL;
	}
	return libd_convert_wcstombsn(str, libd_wcslen(str), NULL);
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.convert") ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char *
NOTHROW_NCX(LIBKCALL libc_convert_wcstombs)(char32_t const *str) {
	if unlikely(!str) {

		(void)libc_seterrno(EINVAL);

		return NULL;
	}
	return libc_convert_wcstombsn(str, libc_wcslen(str), NULL);
}
#include <libc/errno.h>
#include <bits/crt/format-printer.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.convert") ATTR_MALLOC WUNUSED ATTR_INS(1, 2) ATTR_OUT_OPT(3) char *
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
INTERN ATTR_SECTION(".text.crt.wchar.unicode.convert") ATTR_MALLOC WUNUSED ATTR_INS(1, 2) ATTR_OUT_OPT(3) char *
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.convert") ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char **
NOTHROW_NCX(LIBDCALL libd_convert_wcstombsv)(char16_t const *const *__restrict vector) {
	size_t count;
	if unlikely(!vector) {

		(void)libc_seterrno(EINVAL);

		return NULL;
	}
#if __SIZEOF_POINTER__ == 4
	count = libc_rawmemlenl(vector, 0);
#elif __SIZEOF_POINTER__ == 8
	count = libc_rawmemlenq(vector, 0);
#else /* ... */
	for (count = 0; vector[count]; ++count)
		;
#endif /* !... */
	return libd_convert_wcstombsvn(vector, count);
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.convert") ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char **
NOTHROW_NCX(LIBKCALL libc_convert_wcstombsv)(char32_t const *const *__restrict vector) {
	size_t count;
	if unlikely(!vector) {

		(void)libc_seterrno(EINVAL);

		return NULL;
	}
#if __SIZEOF_POINTER__ == 4
	count = libc_rawmemlenl(vector, 0);
#elif __SIZEOF_POINTER__ == 8
	count = libc_rawmemlenq(vector, 0);
#else /* ... */
	for (count = 0; vector[count]; ++count)
		;
#endif /* !... */
	return libc_convert_wcstombsvn(vector, count);
}
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.convert") ATTR_MALLOC WUNUSED ATTR_INS(1, 2) char **
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
INTERN ATTR_SECTION(".text.crt.wchar.unicode.convert") ATTR_MALLOC WUNUSED ATTR_INS(1, 2) char **
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.convert") ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char16_t *
NOTHROW_NCX(LIBDCALL libd_convert_mbstowcs)(char const *__restrict str) {
	if unlikely(!str) {

		(void)libc_seterrno(EINVAL);

		return NULL;
	}
	return libd_convert_mbstowcsn(str, libc_strlen(str), NULL);
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.convert") ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char32_t *
NOTHROW_NCX(LIBKCALL libc_convert_mbstowcs)(char const *__restrict str) {
	if unlikely(!str) {

		(void)libc_seterrno(EINVAL);

		return NULL;
	}
	return libc_convert_mbstowcsn(str, libc_strlen(str), NULL);
}
#include <libc/errno.h>
#include <bits/crt/uformat-printer.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.convert") ATTR_MALLOC WUNUSED ATTR_INS(1, 2) ATTR_OUT_OPT(3) char16_t *
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
INTERN ATTR_SECTION(".text.crt.wchar.unicode.convert") ATTR_MALLOC WUNUSED ATTR_INS(1, 2) ATTR_OUT_OPT(3) char32_t *
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.convert") ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char16_t **
NOTHROW_NCX(LIBDCALL libd_convert_mbstowcsv)(char const *const *__restrict vector) {
	size_t count;
	if unlikely(!vector) {

		(void)libc_seterrno(EINVAL);

		return NULL;
	}
#if __SIZEOF_POINTER__ == 4
	count = libc_rawmemlenl(vector, 0);
#elif __SIZEOF_POINTER__ == 8
	count = libc_rawmemlenq(vector, 0);
#else /* ... */
	for (count = 0; vector[count]; ++count)
		;
#endif /* !... */
	return libd_convert_mbstowcsvn(vector, count);
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.wchar.unicode.convert") ATTR_MALLOC WUNUSED ATTR_IN_OPT(1) char32_t **
NOTHROW_NCX(LIBKCALL libc_convert_mbstowcsv)(char const *const *__restrict vector) {
	size_t count;
	if unlikely(!vector) {

		(void)libc_seterrno(EINVAL);

		return NULL;
	}
#if __SIZEOF_POINTER__ == 4
	count = libc_rawmemlenl(vector, 0);
#elif __SIZEOF_POINTER__ == 8
	count = libc_rawmemlenq(vector, 0);
#else /* ... */
	for (count = 0; vector[count]; ++count)
		;
#endif /* !... */
	return libc_convert_mbstowcsvn(vector, count);
}
#include <libc/errno.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.unicode.convert") ATTR_MALLOC WUNUSED ATTR_INS(1, 2) char16_t **
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
INTERN ATTR_SECTION(".text.crt.wchar.unicode.convert") ATTR_MALLOC WUNUSED ATTR_INS(1, 2) char32_t **
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
DEFINE_PUBLIC_ALIAS_P(mbrtoc8,libc_mbrtoc8,ATTR_INOUT_OPT(4) ATTR_IN_OPT(2) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBCCALL,(char8_t *pc8, char const *__restrict str, size_t maxlen, mbstate_t *mbs),(pc8,str,maxlen,mbs));
DEFINE_PUBLIC_ALIAS_P(c8rtomb,libc_c8rtomb,ATTR_INOUT_OPT(3) ATTR_OUT_OPT(1),size_t,NOTHROW_NCX,LIBCCALL,(char *__restrict str, char8_t c8, mbstate_t *mbs),(str,c8,mbs));
DEFINE_PUBLIC_ALIAS_P_VOID(convert_freev,libc_convert_freev,,NOTHROW_NCX,LIBCCALL,(void *vector),(vector));
DEFINE_PUBLIC_ALIAS_P_VOID(convert_freevn,libc_convert_freevn,,NOTHROW_NCX,LIBCCALL,(void *vector, size_t count),(vector,count));
DEFINE_PUBLIC_ALIAS_P(DOS$convert_wcstombs,libd_convert_wcstombs,ATTR_MALLOC WUNUSED ATTR_IN_OPT(1),char *,NOTHROW_NCX,LIBDCALL,(char16_t const *str),(str));
DEFINE_PUBLIC_ALIAS_P(convert_wcstombs,libc_convert_wcstombs,ATTR_MALLOC WUNUSED ATTR_IN_OPT(1),char *,NOTHROW_NCX,LIBKCALL,(char32_t const *str),(str));
DEFINE_PUBLIC_ALIAS_P(DOS$convert_wcstombsn,libd_convert_wcstombsn,ATTR_MALLOC WUNUSED ATTR_INS(1, 2) ATTR_OUT_OPT(3),char *,NOTHROW_NCX,LIBDCALL,(char16_t const *__restrict str, size_t len, size_t *preslen),(str,len,preslen));
DEFINE_PUBLIC_ALIAS_P(convert_wcstombsn,libc_convert_wcstombsn,ATTR_MALLOC WUNUSED ATTR_INS(1, 2) ATTR_OUT_OPT(3),char *,NOTHROW_NCX,LIBKCALL,(char32_t const *__restrict str, size_t len, size_t *preslen),(str,len,preslen));
DEFINE_PUBLIC_ALIAS_P(DOS$convert_wcstombsv,libd_convert_wcstombsv,ATTR_MALLOC WUNUSED ATTR_IN_OPT(1),char **,NOTHROW_NCX,LIBDCALL,(char16_t const *const *__restrict vector),(vector));
DEFINE_PUBLIC_ALIAS_P(convert_wcstombsv,libc_convert_wcstombsv,ATTR_MALLOC WUNUSED ATTR_IN_OPT(1),char **,NOTHROW_NCX,LIBKCALL,(char32_t const *const *__restrict vector),(vector));
DEFINE_PUBLIC_ALIAS_P(DOS$convert_wcstombsvn,libd_convert_wcstombsvn,ATTR_MALLOC WUNUSED ATTR_INS(1, 2),char **,NOTHROW_NCX,LIBDCALL,(char16_t const *const *__restrict vector, size_t count),(vector,count));
DEFINE_PUBLIC_ALIAS_P(convert_wcstombsvn,libc_convert_wcstombsvn,ATTR_MALLOC WUNUSED ATTR_INS(1, 2),char **,NOTHROW_NCX,LIBKCALL,(char32_t const *const *__restrict vector, size_t count),(vector,count));
DEFINE_PUBLIC_ALIAS_P(DOS$convert_mbstowcs,libd_convert_mbstowcs,ATTR_MALLOC WUNUSED ATTR_IN_OPT(1),char16_t *,NOTHROW_NCX,LIBDCALL,(char const *__restrict str),(str));
DEFINE_PUBLIC_ALIAS_P(convert_mbstowcs,libc_convert_mbstowcs,ATTR_MALLOC WUNUSED ATTR_IN_OPT(1),char32_t *,NOTHROW_NCX,LIBKCALL,(char const *__restrict str),(str));
DEFINE_PUBLIC_ALIAS_P(DOS$convert_mbstowcsn,libd_convert_mbstowcsn,ATTR_MALLOC WUNUSED ATTR_INS(1, 2) ATTR_OUT_OPT(3),char16_t *,NOTHROW_NCX,LIBDCALL,(char const *__restrict str, size_t len, size_t *preslen),(str,len,preslen));
DEFINE_PUBLIC_ALIAS_P(convert_mbstowcsn,libc_convert_mbstowcsn,ATTR_MALLOC WUNUSED ATTR_INS(1, 2) ATTR_OUT_OPT(3),char32_t *,NOTHROW_NCX,LIBKCALL,(char const *__restrict str, size_t len, size_t *preslen),(str,len,preslen));
DEFINE_PUBLIC_ALIAS_P(DOS$convert_mbstowcsv,libd_convert_mbstowcsv,ATTR_MALLOC WUNUSED ATTR_IN_OPT(1),char16_t **,NOTHROW_NCX,LIBDCALL,(char const *const *__restrict vector),(vector));
DEFINE_PUBLIC_ALIAS_P(convert_mbstowcsv,libc_convert_mbstowcsv,ATTR_MALLOC WUNUSED ATTR_IN_OPT(1),char32_t **,NOTHROW_NCX,LIBKCALL,(char const *const *__restrict vector),(vector));
DEFINE_PUBLIC_ALIAS_P(DOS$convert_mbstowcsvn,libd_convert_mbstowcsvn,ATTR_MALLOC WUNUSED ATTR_INS(1, 2),char16_t **,NOTHROW_NCX,LIBDCALL,(char const *const *__restrict vector, size_t count),(vector,count));
DEFINE_PUBLIC_ALIAS_P(convert_mbstowcsvn,libc_convert_mbstowcsvn,ATTR_MALLOC WUNUSED ATTR_INS(1, 2),char32_t **,NOTHROW_NCX,LIBKCALL,(char const *const *__restrict vector, size_t count),(vector,count));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_UCHAR_C */
