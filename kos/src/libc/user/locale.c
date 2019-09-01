/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_LOCALE_C
#define GUARD_LIBC_USER_LOCALE_C 1

#include "../api.h"
#include "locale.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:setlocale,hash:0x15100da8]]]*/
/* Set and/or return the current locale */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.setlocale") char *
NOTHROW_NCX(LIBCCALL libc_setlocale)(int category,
                                     char const *locale)
/*[[[body:setlocale]]]*/
{
	CRT_UNIMPLEMENTED("setlocale"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:setlocale]]]*/

/*[[[head:localeconv,hash:0xb8928fdc]]]*/
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

/*[[[head:newlocale,hash:0xef858b88]]]*/
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
	CRT_UNIMPLEMENTED("newlocale"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:newlocale]]]*/

/*[[[head:duplocale,hash:0x7a60a08]]]*/
/* Return a duplicate of the set of locale in DATASET.
 * All usage counters are increased if necessary */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.duplocale") locale_t
NOTHROW_NCX(LIBCCALL libc_duplocale)(locale_t dataset)
/*[[[body:duplocale]]]*/
{
	CRT_UNIMPLEMENTED("duplocale"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:duplocale]]]*/

/*[[[head:freelocale,hash:0xc985b0eb]]]*/
/* Free the data associated with a locale dataset
 * previously returned by a call to `setlocale_r' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.freelocale") void
NOTHROW_NCX(LIBCCALL libc_freelocale)(locale_t dataset)
/*[[[body:freelocale]]]*/
{
	CRT_UNIMPLEMENTED("freelocale"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:freelocale]]]*/

/*[[[head:uselocale,hash:0xa655c840]]]*/
/* Switch the current thread's locale to DATASET.
 * If DATASET is null, instead just return the current setting.
 * The special value LC_GLOBAL_LOCALE is the initial setting
 * for all threads and can also be installed any time, meaning
 * the thread uses the global settings controlled by `setlocale' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.uselocale") locale_t
NOTHROW_NCX(LIBCCALL libc_uselocale)(locale_t dataset)
/*[[[body:uselocale]]]*/
{
	CRT_UNIMPLEMENTED("uselocale"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:uselocale]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0x57da9bed]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(setlocale, libc_setlocale);
DEFINE_PUBLIC_WEAK_ALIAS(localeconv, libc_localeconv);
DEFINE_PUBLIC_WEAK_ALIAS(newlocale, libc_newlocale);
DEFINE_PUBLIC_WEAK_ALIAS(duplocale, libc_duplocale);
DEFINE_PUBLIC_WEAK_ALIAS(freelocale, libc_freelocale);
DEFINE_PUBLIC_WEAK_ALIAS(uselocale, libc_uselocale);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_LOCALE_C */
