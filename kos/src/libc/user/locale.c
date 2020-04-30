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
#ifndef GUARD_LIBC_USER_LOCALE_C
#define GUARD_LIBC_USER_LOCALE_C 1

#include "../api.h"
#include "locale.h"

DECL_BEGIN



/* TODO: On startup, `current_locale' should be "C"
 *       Once `setlocale(LC_ALL, "");' is called, it
 *       should become some string that contains ".UTF-8".
 *       The later is checked for by libncursesw and must
 *       be present for full unicode support. */
PRIVATE ATTR_SECTION(".data.crt.unsorted.current_locale")
char current_locale[] = "C.UTF-8";


/*[[[start:implementation]]]*/

/*[[[head:setlocale,hash:CRC-32=0xfb0ee566]]]*/
/* Set and/or return the current locale */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.setlocale") char *
NOTHROW_NCX(LIBCCALL libc_setlocale)(int category,
                                     char const *locale)
/*[[[body:setlocale]]]*/
{
	(void)category;
	(void)locale;
	CRT_UNIMPLEMENTED("setlocale"); /* TODO */
	libc_seterrno(ENOSYS);
	return current_locale;
}
/*[[[end:setlocale]]]*/

/*[[[head:localeconv,hash:CRC-32=0x1ee9be68]]]*/
/* Return the numeric/monetary information for the current locale */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.localeconv") struct lconv *
NOTHROW_NCX(LIBCCALL libc_localeconv)(void)
/*[[[body:localeconv]]]*/
{
	CRT_UNIMPLEMENTED("localeconv"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:localeconv]]]*/

/*[[[head:newlocale,hash:CRC-32=0x172b0606]]]*/
/* Return a reference to a data structure representing a set of locale
 * datasets. Unlike for the CATEGORY parameter for `setlocale' the
 * CATEGORY_MASK parameter here uses a single bit for each category,
 * made by OR'ing together LC_*_MASK bits above */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.newlocale") locale_t
NOTHROW_NCX(LIBCCALL libc_newlocale)(int category_mask,
                                     char const *locale,
                                     locale_t base)
/*[[[body:newlocale]]]*/
{
	(void)category_mask;
	(void)locale;
	(void)base;
	CRT_UNIMPLEMENTED("newlocale"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:newlocale]]]*/

/*[[[head:duplocale,hash:CRC-32=0xb1bab76c]]]*/
/* Return a duplicate of the set of locale in DATASET.
 * All usage counters are increased if necessary */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.duplocale") locale_t
NOTHROW_NCX(LIBCCALL libc_duplocale)(locale_t dataset)
/*[[[body:duplocale]]]*/
{
	(void)dataset;
	CRT_UNIMPLEMENTED("duplocale"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:duplocale]]]*/

/*[[[head:freelocale,hash:CRC-32=0xfa9bb671]]]*/
/* Free the data associated with a locale dataset
 * previously returned by a call to `setlocale_r' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.freelocale") void
NOTHROW_NCX(LIBCCALL libc_freelocale)(locale_t dataset)
/*[[[body:freelocale]]]*/
{
	(void)dataset;
	CRT_UNIMPLEMENTED("freelocale"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:freelocale]]]*/

/*[[[head:uselocale,hash:CRC-32=0x10db78cf]]]*/
/* Switch the current thread's locale to DATASET.
 * If DATASET is null, instead just return the current setting.
 * The special value LC_GLOBAL_LOCALE is the initial setting
 * for all threads and can also be installed any time, meaning
 * the thread uses the global settings controlled by `setlocale' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.uselocale") locale_t
NOTHROW_NCX(LIBCCALL libc_uselocale)(locale_t dataset)
/*[[[body:uselocale]]]*/
{
	(void)dataset;
	CRT_UNIMPLEMENTED("uselocale"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:uselocale]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xf248928a]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(setlocale, libc_setlocale);
DEFINE_PUBLIC_WEAK_ALIAS(localeconv, libc_localeconv);
DEFINE_PUBLIC_WEAK_ALIAS(newlocale, libc_newlocale);
DEFINE_PUBLIC_WEAK_ALIAS(__newlocale, libc_newlocale);
DEFINE_PUBLIC_WEAK_ALIAS(duplocale, libc_duplocale);
DEFINE_PUBLIC_WEAK_ALIAS(__duplocale, libc_duplocale);
DEFINE_PUBLIC_WEAK_ALIAS(freelocale, libc_freelocale);
DEFINE_PUBLIC_WEAK_ALIAS(__freelocale, libc_freelocale);
DEFINE_PUBLIC_WEAK_ALIAS(uselocale, libc_uselocale);
DEFINE_PUBLIC_WEAK_ALIAS(__uselocale, libc_uselocale);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_LOCALE_C */
