/* HASH CRC-32:0x9a63c891 */
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
#ifndef GUARD_LIBC_AUTO_LOCALE_C
#define GUARD_LIBC_AUTO_LOCALE_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/locale.h"
#include "langinfo.h"
#include "../user/stdlib.h"
#include "string.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <asm/crt/langinfo.h>
INTERN ATTR_SECTION(".text.crt.dos.i18n") WUNUSED char *
NOTHROW_NCX(LIBCCALL libc__Getdays)(void) {
	/* Essentially, we do:
	 * >> strdup(":Sun:Sunday:Mon:Monday:Tue:Tuesday:Wed:Wednesday:Thu:Thursday:Fri:Friday:Sat:Saturday") */
	size_t len = 0;
	unsigned int i;
	char *result;
	for (i = 0; i < 7; ++i) {
		char const *p;
		len += 2; /* 2x ':' */
		if ((p = libc_nl_langinfo(_NL_TIME_ABDAY_1 + i)) != NULL)
			len += libc_strlen(p);
		if ((p = libc_nl_langinfo(_NL_TIME_DAY_1 + i)) != NULL)
			len += libc_strlen(p);
	}
	result = (char *)libc_malloc((len + 1) * sizeof(char));
	if likely(result) {
		char *dst = result;
		for (i = 0; i < 7; ++i) {
			char const *p;
			*dst++ = ':';
			if ((p = libc_nl_langinfo(_NL_TIME_ABDAY_1 + i)) != NULL)
				dst = libc_stpcpy(dst, p);
			*dst++ = ':';
			if ((p = libc_nl_langinfo(_NL_TIME_DAY_1 + i)) != NULL)
				dst = libc_stpcpy(dst, p);
		}
		*dst++ = '\0';
	}
	return result;
}
#include <asm/crt/langinfo.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.i18n") WUNUSED char16_t *
NOTHROW_NCX(LIBDCALL libd__W_Getdays)(void) {
	/* Essentially, we do:
	 * >> wcsdup(L":Sun:Sunday:Mon:Monday:Tue:Tuesday:Wed:Wednesday:Thu:Thursday:Fri:Friday:Sat:Saturday") */
	size_t len = 0;
	unsigned int i;
	char16_t *result;
	for (i = 0; i < 7; ++i) {
		char const *p;
		len += 2; /* 2x ':' */
		if ((p = libc_nl_langinfo(_NL_TIME_ABDAY_1 + i)) != NULL)
			len += libc_strlen(p);
		if ((p = libc_nl_langinfo(_NL_TIME_DAY_1 + i)) != NULL)
			len += libc_strlen(p);
	}
	result = (char16_t *)libc_malloc((len + 1) * sizeof(char16_t));
	if likely(result) {
		char16_t *dst = result;
		for (i = 0; i < 7; ++i) {
			unsigned int id;
			for (id = 0; id < 2; ++id) {
				char const *p;
				*dst++ = ':';
				if ((p = libc_nl_langinfo(id ? (_NL_TIME_DAY_1 + i)
				                        : (_NL_TIME_ABDAY_1 + i))) != NULL) {
					while (*p)
						*dst++ = (char16_t)(unsigned char)*p++;
				}
			}
		}
		*dst++ = (char16_t)'\0';
	}
	return result;
}
#include <asm/crt/langinfo.h>
INTERN ATTR_SECTION(".text.crt.dos.i18n") WUNUSED char32_t *
NOTHROW_NCX(LIBKCALL libc__W_Getdays)(void) {
	/* Essentially, we do:
	 * >> wcsdup(L":Sun:Sunday:Mon:Monday:Tue:Tuesday:Wed:Wednesday:Thu:Thursday:Fri:Friday:Sat:Saturday") */
	size_t len = 0;
	unsigned int i;
	char32_t *result;
	for (i = 0; i < 7; ++i) {
		char const *p;
		len += 2; /* 2x ':' */
		if ((p = libc_nl_langinfo(_NL_TIME_ABDAY_1 + i)) != NULL)
			len += libc_strlen(p);
		if ((p = libc_nl_langinfo(_NL_TIME_DAY_1 + i)) != NULL)
			len += libc_strlen(p);
	}
	result = (char32_t *)libc_malloc((len + 1) * sizeof(char32_t));
	if likely(result) {
		char32_t *dst = result;
		for (i = 0; i < 7; ++i) {
			unsigned int id;
			for (id = 0; id < 2; ++id) {
				char const *p;
				*dst++ = ':';
				if ((p = libc_nl_langinfo(id ? (_NL_TIME_DAY_1 + i)
				                        : (_NL_TIME_ABDAY_1 + i))) != NULL) {
					while (*p)
						*dst++ = (char32_t)(unsigned char)*p++;
				}
			}
		}
		*dst++ = (char32_t)'\0';
	}
	return result;
}
#include <asm/crt/langinfo.h>
INTERN ATTR_SECTION(".text.crt.dos.i18n") WUNUSED char *
NOTHROW_NCX(LIBCCALL libc__Getmonths)(void) {
	/* Essentially, we do:
	 * >> strdup(":Jan:January:Feb:February:Mar:March:Apr:April:May:May:Jun:June:Jul:July:Aug:August:Sep:September:Oct:October:Nov:November:Dec:December") */
	size_t len = 0;
	unsigned int i;
	char *result;
	for (i = 0; i < 12; ++i) {
		char const *p;
		len += 2; /* 2x ':' */
		if ((p = libc_nl_langinfo(_NL_TIME_ABMON_1 + i)) != NULL)
			len += libc_strlen(p);
		if ((p = libc_nl_langinfo(_NL_TIME_MON_1 + i)) != NULL)
			len += libc_strlen(p);
	}
	result = (char *)libc_malloc((len + 1) * sizeof(char));
	if likely(result) {
		char *dst = result;
		for (i = 0; i < 12; ++i) {
			char const *p;
			*dst++ = ':';
			if ((p = libc_nl_langinfo(_NL_TIME_ABMON_1 + i)) != NULL)
				dst = libc_stpcpy(dst, p);
			*dst++ = ':';
			if ((p = libc_nl_langinfo(_NL_TIME_MON_1 + i)) != NULL)
				dst = libc_stpcpy(dst, p);
		}
		*dst++ = '\0';
	}
	return result;
}
#include <asm/crt/langinfo.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.i18n") WUNUSED char16_t *
NOTHROW_NCX(LIBDCALL libd__W_Getmonths)(void) {
	/* Essentially, we do:
	 * >> wcsdup(L":Jan:January:Feb:February:Mar:March:Apr:April:May:May:Jun:June:Jul:July:Aug:August:Sep:September:Oct:October:Nov:November:Dec:December") */
	size_t len = 0;
	unsigned int i;
	char16_t *result;
	for (i = 0; i < 12; ++i) {
		char const *p;
		len += 2; /* 2x ':' */
		if ((p = libc_nl_langinfo(_NL_TIME_ABMON_1 + i)) != NULL)
			len += libc_strlen(p);
		if ((p = libc_nl_langinfo(_NL_TIME_MON_1 + i)) != NULL)
			len += libc_strlen(p);
	}
	result = (char16_t *)libc_malloc((len + 1) * sizeof(char16_t));
	if likely(result) {
		char16_t *dst = result;
		for (i = 0; i < 12; ++i) {
			unsigned int id;
			for (id = 0; id < 2; ++id) {
				char const *p;
				*dst++ = ':';
				if ((p = libc_nl_langinfo(id ? (_NL_TIME_MON_1 + i)
				                        : (_NL_TIME_ABMON_1 + i))) != NULL) {
					while (*p)
						*dst++ = (char16_t)(unsigned char)*p++;
				}
			}
		}
		*dst++ = (char16_t)'\0';
	}
	return result;
}
#include <asm/crt/langinfo.h>
INTERN ATTR_SECTION(".text.crt.dos.i18n") WUNUSED char32_t *
NOTHROW_NCX(LIBKCALL libc__W_Getmonths)(void) {
	/* Essentially, we do:
	 * >> wcsdup(L":Jan:January:Feb:February:Mar:March:Apr:April:May:May:Jun:June:Jul:July:Aug:August:Sep:September:Oct:October:Nov:November:Dec:December") */
	size_t len = 0;
	unsigned int i;
	char32_t *result;
	for (i = 0; i < 12; ++i) {
		char const *p;
		len += 2; /* 2x ':' */
		if ((p = libc_nl_langinfo(_NL_TIME_ABMON_1 + i)) != NULL)
			len += libc_strlen(p);
		if ((p = libc_nl_langinfo(_NL_TIME_MON_1 + i)) != NULL)
			len += libc_strlen(p);
	}
	result = (char32_t *)libc_malloc((len + 1) * sizeof(char32_t));
	if likely(result) {
		char32_t *dst = result;
		for (i = 0; i < 12; ++i) {
			unsigned int id;
			for (id = 0; id < 2; ++id) {
				char const *p;
				*dst++ = ':';
				if ((p = libc_nl_langinfo(id ? (_NL_TIME_MON_1 + i)
				                        : (_NL_TIME_ABMON_1 + i))) != NULL) {
					while (*p)
						*dst++ = (char32_t)(unsigned char)*p++;
				}
			}
		}
		*dst++ = (char32_t)'\0';
	}
	return result;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_Getdays, libc__Getdays);
DEFINE_PUBLIC_ALIAS(DOS$_W_Getdays, libd__W_Getdays);
DEFINE_PUBLIC_ALIAS(_W_Getdays, libc__W_Getdays);
DEFINE_PUBLIC_ALIAS(_Getmonths, libc__Getmonths);
DEFINE_PUBLIC_ALIAS(DOS$_W_Getmonths, libd__W_Getmonths);
DEFINE_PUBLIC_ALIAS(_W_Getmonths, libc__W_Getmonths);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_LOCALE_C */
