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
#ifndef GUARD_LIBC_USER_SSP_STRING_C
#define GUARD_LIBC_USER_SSP_STRING_C 1

#include "../api.h"
/**/

#include <string.h>

#include "ssp.string.h"
#include "string.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:__memcpy_chk,hash:CRC-32=0x9ed0e8a3]]]*/
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memcpy_chk") void *
NOTHROW_NCX(LIBCCALL libc___memcpy_chk)(void *__restrict dst,
                                        void const *__restrict src,
                                        size_t num_bytes,
                                        size_t dst_bufsize)
/*[[[body:__memcpy_chk]]]*/
/*AUTO*/{
	(void)dst_bufsize;
	return memcpy(dst, src, num_bytes);
}
/*[[[end:__memcpy_chk]]]*/

/*[[[head:__memmove_chk,hash:CRC-32=0xc64365da]]]*/
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memmove_chk") void *
NOTHROW_NCX(LIBCCALL libc___memmove_chk)(void *dst,
                                         void const *src,
                                         size_t num_bytes,
                                         size_t dst_bufsize)
/*[[[body:__memmove_chk]]]*/
/*AUTO*/{
	(void)dst_bufsize;
	return memmove(dst, src, num_bytes);
}
/*[[[end:__memmove_chk]]]*/

/*[[[head:__mempcpy_chk,hash:CRC-32=0x5ed631f5]]]*/
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempcpy_chk") void *
NOTHROW_NCX(LIBCCALL libc___mempcpy_chk)(void *__restrict dst,
                                         void const *__restrict src,
                                         size_t num_bytes,
                                         size_t dst_bufsize)
/*[[[body:__mempcpy_chk]]]*/
/*AUTO*/{
	(void)dst_bufsize;
	return memmove(dst, src, num_bytes);
}
/*[[[end:__mempcpy_chk]]]*/

/*[[[head:__memset_chk,hash:CRC-32=0x4d22b6f5]]]*/
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memset_chk") void *
NOTHROW_NCX(LIBCCALL libc___memset_chk)(void *__restrict dst,
                                        int byte,
                                        size_t num_bytes,
                                        size_t dst_bufsize)
/*[[[body:__memset_chk]]]*/
/*AUTO*/{
	(void)dst_bufsize;
	return memset(dst, byte, num_bytes);
}
/*[[[end:__memset_chk]]]*/

/*[[[head:__stpcpy_chk,hash:CRC-32=0x7b1ab8f7]]]*/
INTERN ATTR_LEAF NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__stpcpy_chk") char *
NOTHROW_NCX(LIBCCALL libc___stpcpy_chk)(char *__restrict dst,
                                        char const *__restrict src,
                                        size_t dst_bufsize)
/*[[[body:__stpcpy_chk]]]*/
/*AUTO*/{
	(void)dst_bufsize;
	return libc_stpcpy(dst, src);
}
/*[[[end:__stpcpy_chk]]]*/

/*[[[head:__strcat_chk,hash:CRC-32=0x74d27bce]]]*/
INTERN ATTR_LEAF NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__strcat_chk") char *
NOTHROW_NCX(LIBCCALL libc___strcat_chk)(char *__restrict dst,
                                        char const *__restrict src,
                                        size_t dst_bufsize)
/*[[[body:__strcat_chk]]]*/
/*AUTO*/{
	(void)dst_bufsize;
	return libc_strcat(dst, src);
}
/*[[[end:__strcat_chk]]]*/

/*[[[head:__strcpy_chk,hash:CRC-32=0x22d73402]]]*/
INTERN ATTR_LEAF NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__strcpy_chk") char *
NOTHROW_NCX(LIBCCALL libc___strcpy_chk)(char *__restrict dst,
                                        char const *__restrict src,
                                        size_t dst_bufsize)
/*[[[body:__strcpy_chk]]]*/
/*AUTO*/{
	(void)dst_bufsize;
	return libc_strcpy(dst, src);
}
/*[[[end:__strcpy_chk]]]*/

/*[[[head:__strncat_chk,hash:CRC-32=0x6662c587]]]*/
INTERN ATTR_LEAF NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__strncat_chk") char *
NOTHROW_NCX(LIBCCALL libc___strncat_chk)(char *__restrict dst,
                                         char const *__restrict src,
                                         size_t buflen,
                                         size_t dst_bufsize)
/*[[[body:__strncat_chk]]]*/
/*AUTO*/{
	(void)dst_bufsize;
	return libc_strncat(dst, src, buflen);
}
/*[[[end:__strncat_chk]]]*/

/*[[[head:__strncpy_chk,hash:CRC-32=0x4358fce7]]]*/
INTERN ATTR_LEAF NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__strncpy_chk") char *
NOTHROW_NCX(LIBCCALL libc___strncpy_chk)(char *__restrict dst,
                                         char const *__restrict src,
                                         size_t buflen,
                                         size_t dst_bufsize)
/*[[[body:__strncpy_chk]]]*/
/*AUTO*/{
	(void)dst_bufsize;
	return libc_strncpy(dst, src, buflen);
}
/*[[[end:__strncpy_chk]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x1c6b3316]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(__memcpy_chk, libc___memcpy_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memmove_chk, libc___memmove_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempcpy_chk, libc___mempcpy_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memset_chk, libc___memset_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__stpcpy_chk, libc___stpcpy_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__strcat_chk, libc___strcat_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__strcpy_chk, libc___strcpy_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__strncat_chk, libc___strncat_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__strncpy_chk, libc___strncpy_chk);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SSP_STRING_C */
