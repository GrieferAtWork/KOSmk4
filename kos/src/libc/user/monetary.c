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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_MONETARY_C
#define GUARD_LIBC_USER_MONETARY_C 1

#include "../api.h"
#include "monetary.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:strfmon,hash:CRC-32=0xb8cc79dc]]]*/
INTERN NONNULL((1, 3)) ATTR_LIBC_STRFMON(3, 4)
ATTR_WEAK ATTR_SECTION(".text.crt.utility.monetary.strfmon") ssize_t
NOTHROW_NCX(VLIBCCALL libc_strfmon)(char *__restrict s,
                                    size_t maxsize,
                                    char const *__restrict format,
                                    ...)
/*[[[body:strfmon]]]*/
{
	(void)s;
	(void)maxsize;
	(void)format;
	CRT_UNIMPLEMENTED("strfmon"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:strfmon]]]*/

/*[[[head:strfmon_l,hash:CRC-32=0xb5fdf0cf]]]*/
INTERN NONNULL((1, 4)) ATTR_LIBC_STRFMON(4, 5)
ATTR_WEAK ATTR_SECTION(".text.crt.utility.monetary.strfmon_l") ssize_t
NOTHROW_NCX(VLIBCCALL libc_strfmon_l)(char *__restrict s,
                                      size_t maxsize,
                                      locale_t loc,
                                      const char *__restrict format,
                                      ...)
/*[[[body:strfmon_l]]]*/
{
	(void)s;
	(void)maxsize;
	(void)loc;
	(void)format;
	CRT_UNIMPLEMENTED("strfmon_l"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:strfmon_l]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x8cfe79bd]]]*/
#undef strfmon
#undef strfmon_l
#undef __strfmon_l
DEFINE_PUBLIC_WEAK_ALIAS(strfmon, libc_strfmon);
DEFINE_PUBLIC_WEAK_ALIAS(strfmon_l, libc_strfmon_l);
DEFINE_PUBLIC_WEAK_ALIAS(__strfmon_l, libc_strfmon_l);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_MONETARY_C */
