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
#ifndef GUARD_LIBC_LIBC_UCHAR_C
#define GUARD_LIBC_LIBC_UCHAR_C 1
#define _UTF_SOURCE 1

/* Keep this one the first */
#include "../api.h"
/**/

#include "uchar.h"
#include <malloc.h>
#include <format-printer.h>
#include <string.h>
#include <unicode.h>
#include <uchar.h>

DECL_BEGIN

#ifdef __CC__

#define SECTION_TEXT_UCHAR16 ".text.crt.dos.wchar.unicode.convert"
#define SECTION_TEXT_UCHAR32 ".text.crt.wchar.unicode.convert"
#define SECTION_TEXT_UCHAR   SECTION_TEXT_UCHAR32


/* Helper functions for converting wide-character strings
 * into  UTF-8,  so  they  may  be  used  by  the kernel. */
INTERN ATTR_SECTION(SECTION_TEXT_UCHAR) void LIBCCALL
libc_uchar_freev(/*utf-8*/ char **ptr) {
	char **iter, *temp;
	if unlikely(!ptr)
		return;
	for (iter = ptr; (temp = *iter) != NULL; ++iter)
		free(temp);
	free(ptr);
}

INTERN ATTR_SECTION(SECTION_TEXT_UCHAR) void LIBCCALL
libc_uchar_freevn(/*utf-8*/ char **ptr, size_t count) {
	size_t i;
	if unlikely(!ptr)
		return;
	for (i = 0; i < count; ++i) {
		free(ptr[i]);
	}
	free(ptr);
}

INTERN ATTR_SECTION(SECTION_TEXT_UCHAR16) ATTR_MALLOC WUNUSED NONNULL((1)) /*utf-8*/ char *LIBDCALL
libc_uchar_c16tombs(char16_t const *__restrict str) {
	size_t len;
	if unlikely(!str) {
		libc_seterrno(EINVAL);
		return NULL;
	}
	len = c16slen(str);
	return libc_uchar_c16tombsn(str, len, NULL);
}

INTERN ATTR_SECTION(SECTION_TEXT_UCHAR32) ATTR_MALLOC WUNUSED NONNULL((1)) /*utf-8*/ char *LIBCCALL
libc_uchar_c32tombs(char32_t const *__restrict str) {
	size_t len;
	if unlikely(!str) {
		libc_seterrno(EINVAL);
		return NULL;
	}
	len = c32slen(str);
	return libc_uchar_c32tombsn(str, len, NULL);
}

INTERN ATTR_SECTION(SECTION_TEXT_UCHAR16) ATTR_MALLOC WUNUSED NONNULL((1)) /*utf-8*/ char *LIBDCALL
libc_uchar_c16tombsn(char16_t const *__restrict str, size_t len, size_t *preslen) {
	struct format_aprintf_data printer_data = FORMAT_APRINTF_DATA_INIT;
	struct format_16to8_data convert_data;
	convert_data.fd_printer   = &format_aprintf_printer;
	convert_data.fd_arg       = &printer_data;
	convert_data.fd_surrogate = 0;
	if unlikely(format_16to8(&convert_data, str, len) < 0) {
		format_aprintf_data_fini(&printer_data);
		return NULL;
	}
	return format_aprintf_pack(&printer_data, preslen);
}

INTERN ATTR_SECTION(SECTION_TEXT_UCHAR32) ATTR_MALLOC WUNUSED NONNULL((1)) /*utf-8*/ char *LIBCCALL
libc_uchar_c32tombsn(char32_t const *__restrict str, size_t len, size_t *preslen) {
	struct format_aprintf_data printer_data = FORMAT_APRINTF_DATA_INIT;
	struct format_32to8_data convert_data;
	convert_data.fd_printer = &format_aprintf_printer;
	convert_data.fd_arg     = &printer_data;
	if unlikely(format_32to8(&convert_data, str, len) < 0) {
		format_aprintf_data_fini(&printer_data);
		return NULL;
	}
	return format_aprintf_pack(&printer_data, preslen);
}

INTERN ATTR_SECTION(SECTION_TEXT_UCHAR16) ATTR_MALLOC WUNUSED NONNULL((1)) /*utf-8*/ char **LIBDCALL
libc_uchar_c16tombsv(char16_t const *const *__restrict vector) {
	size_t i, count = 0;
	char **result;
	if unlikely(!vector) {
		libc_seterrno(EINVAL);
		return NULL;
	}
	while (vector[count])
		++count;
	result = (char **)malloc((count + 1) * sizeof(char *));
	if likely(result) {
		for (i = 0; i < count; ++i) {
			char *temp;
			temp = libc_uchar_c16tombs(vector[i]);
			if unlikely(!temp)
				goto err;
			result[i] = temp;
		}
	}
	return result;
err:
	while (i--)
		free(result[i]);
	free(result);
	return NULL;
}

INTERN ATTR_SECTION(SECTION_TEXT_UCHAR32) ATTR_MALLOC WUNUSED NONNULL((1)) /*utf-8*/ char **LIBCCALL
libc_uchar_c32tombsv(char32_t const *const *__restrict vector) {
	size_t i, count = 0;
	char **result;
	if unlikely(!vector) {
		libc_seterrno(EINVAL);
		return NULL;
	}
	while (vector[count])
		++count;
	result = (char **)malloc((count + 1) * sizeof(char *));
	if likely(result) {
		for (i = 0; i < count; ++i) {
			char *temp;
			temp = libc_uchar_c32tombs(vector[i]);
			if unlikely(!temp)
				goto err;
			result[i] = temp;
		}
	}
	return result;
err:
	while (i--)
		free(result[i]);
	free(result);
	return NULL;
}


INTERN ATTR_SECTION(SECTION_TEXT_UCHAR16) ATTR_MALLOC WUNUSED NONNULL((1)) /*utf-8*/ char **LIBDCALL
libc_uchar_c16tombsvn(char16_t const *const *__restrict vector, size_t count) {
	size_t i;
	char **result;
	if unlikely(!count)
		return (char **)calloc(1, sizeof(char *));
	if unlikely(!vector) {
		libc_seterrno(EINVAL);
		return NULL;
	}
	result = (char **)malloc((count + 1) * sizeof(char *));
	if likely(result) {
		for (i = 0; i < count; ++i) {
			char *temp;
			temp = libc_uchar_c16tombs(vector[i]);
			if unlikely(!temp)
				goto err;
			result[i] = temp;
		}
	}
	return result;
err:
	while (i--)
		free(result[i]);
	free(result);
	return NULL;
}

INTERN ATTR_SECTION(SECTION_TEXT_UCHAR32) ATTR_MALLOC WUNUSED NONNULL((1)) /*utf-8*/ char **LIBCCALL
libc_uchar_c32tombsvn(char32_t const *const *__restrict vector, size_t count) {
	size_t i;
	char **result;
	if unlikely(!count)
		return (char **)calloc(1, sizeof(char *));
	if unlikely(!vector) {
		libc_seterrno(EINVAL);
		return NULL;
	}
	result = (char **)malloc((count + 1) * sizeof(char *));
	if likely(result) {
		for (i = 0; i < count; ++i) {
			char *temp;
			temp = libc_uchar_c32tombs(vector[i]);
			if unlikely(!temp)
				goto err;
			result[i] = temp;
		}
	}
	return result;
err:
	while (i--)
		free(result[i]);
	free(result);
	return NULL;
}



INTERN ATTR_SECTION(SECTION_TEXT_UCHAR16) ATTR_MALLOC WUNUSED NONNULL((1)) char16_t *LIBDCALL
libc_uchar_mbstoc16(/*utf-8*/ char const *__restrict str) {
	size_t len = strlen(str);
	return libc_uchar_mbstoc16n(str, len, NULL);
}

INTERN ATTR_SECTION(SECTION_TEXT_UCHAR32) ATTR_MALLOC WUNUSED NONNULL((1)) char32_t *LIBCCALL
libc_uchar_mbstoc32(/*utf-8*/ char const *__restrict str) {
	size_t len = strlen(str);
	return libc_uchar_mbstoc32n(str, len, NULL);
}

INTERN ATTR_SECTION(SECTION_TEXT_UCHAR16) ATTR_MALLOC WUNUSED NONNULL((1)) char16_t *LIBDCALL
libc_uchar_mbstoc16n(/*utf-8*/ char const *__restrict str,
                     size_t len, size_t *preslen) {
	struct format_c16aprintf_data printer_data = FORMAT_C16APRINTF_DATA_INIT;
	struct format_8to16_data convert_data;
	convert_data.fd_printer    = &format_c16aprintf_printer;
	convert_data.fd_arg        = &printer_data;
	convert_data.fd_incomplete = 0;
	if unlikely(format_8to16(&convert_data, str, len) < 0) {
		format_c16aprintf_data_fini(&printer_data);
		return NULL;
	}
	return format_c16aprintf_pack(&printer_data, preslen);
}


INTERN ATTR_SECTION(SECTION_TEXT_UCHAR32) ATTR_MALLOC WUNUSED NONNULL((1)) char32_t *LIBCCALL
libc_uchar_mbstoc32n(/*utf-8*/ char const *__restrict str,
                     size_t len, size_t *preslen) {
	struct format_c32aprintf_data printer_data = FORMAT_C32APRINTF_DATA_INIT;
	struct format_8to32_data convert_data;
	convert_data.fd_printer    = &format_c32aprintf_printer;
	convert_data.fd_arg        = &printer_data;
	convert_data.fd_incomplete = 0;
	if unlikely(format_8to32(&convert_data, str, len) < 0) {
		format_c32aprintf_data_fini(&printer_data);
		return NULL;
	}
	return format_c32aprintf_pack(&printer_data, preslen);
}



#endif /* __CC__ */

DECL_END

#endif /* !GUARD_LIBC_LIBC_UCHAR_C */
