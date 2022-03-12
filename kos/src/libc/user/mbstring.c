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
#ifndef GUARD_LIBC_USER_MBSTRING_C
#define GUARD_LIBC_USER_MBSTRING_C 1

#include "../api.h"
/**/

#include "mbstring.h"

DECL_BEGIN

/*[[[head:libc__mbbtombc_l,hash:CRC-32=0xd3c447ff]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbbtombc_l)(unsigned int ch,
                                       locale_t locale)
/*[[[body:libc__mbbtombc_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbbtombc_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbbtombc_l]]]*/

/*[[[head:libc__mbbtype_l,hash:CRC-32=0xd1da82ac]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__mbbtype_l)(unsigned char ch,
                                      int ctype,
                                      locale_t locale)
/*[[[body:libc__mbbtype_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)ctype;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbbtype_l(%hhx, %x, %p)", ch, ctype, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbbtype_l]]]*/

/*[[[head:libc__mbctombb_l,hash:CRC-32=0x28188524]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbctombb_l)(unsigned int ch,
                                       locale_t locale)
/*[[[body:libc__mbctombb_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbctombb_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbctombb_l]]]*/

/*[[[head:libc__mbsbtype_l,hash:CRC-32=0x4181912]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") int
NOTHROW_NCX(LIBCCALL libc__mbsbtype_l)(unsigned char const *str,
                                       size_t pos,
                                       locale_t locale)
/*[[[body:libc__mbsbtype_l]]]*/
/*AUTO*/{
	(void)str;
	(void)pos;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsbtype_l(%p, %Ix, %p)", str, pos, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbsbtype_l]]]*/

/*[[[head:libc__mbscat_s_l,hash:CRC-32=0xe77b2c49]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbscat_s_l)(unsigned char *buf,
                                       size_t bufsize,
                                       unsigned char const *src,
                                       locale_t locale)
/*[[[body:libc__mbscat_s_l]]]*/
/*AUTO*/{
	(void)buf;
	(void)bufsize;
	(void)src;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbscat_s_l(%p, %Ix, %p, %p)", buf, bufsize, src, locale); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__mbscat_s_l]]]*/


/*[[[head:libc__mbschr_l,hash:CRC-32=0x4c3e5f1a]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbschr_l)(unsigned char const *__restrict haystack,
                                     unsigned int needle,
                                     locale_t locale)
/*[[[body:libc__mbschr_l]]]*/
/*AUTO*/{
	(void)haystack;
	(void)needle;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbschr_l(%p, %x, %p)", haystack, needle, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__mbschr_l]]]*/

/*[[[head:libc__mbscmp_l,hash:CRC-32=0xb8dd16e2]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbscmp_l)(unsigned char const *lhs,
                                     unsigned char const *rhs,
                                     locale_t locale)
/*[[[body:libc__mbscmp_l]]]*/
/*AUTO*/{
	(void)lhs;
	(void)rhs;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbscmp_l(%p, %p, %p)", lhs, rhs, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbscmp_l]]]*/

/*[[[head:libc__mbscoll_l,hash:CRC-32=0x7dfdfbf8]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbscoll_l)(unsigned char const *lhs,
                                      unsigned char const *rhs,
                                      locale_t locale)
/*[[[body:libc__mbscoll_l]]]*/
/*AUTO*/{
	(void)lhs;
	(void)rhs;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbscoll_l(%p, %p, %p)", lhs, rhs, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbscoll_l]]]*/

/*[[[head:libc__mbscpy_s_l,hash:CRC-32=0x8e715a6f]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbscpy_s_l)(unsigned char *buf,
                                       size_t bufsize,
                                       unsigned char const *src,
                                       locale_t locale)
/*[[[body:libc__mbscpy_s_l]]]*/
/*AUTO*/{
	(void)buf;
	(void)bufsize;
	(void)src;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbscpy_s_l(%p, %Ix, %p, %p)", buf, bufsize, src, locale); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__mbscpy_s_l]]]*/


/*[[[head:libc__mbscspn_l,hash:CRC-32=0x39e82522]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBCCALL libc__mbscspn_l)(unsigned char const *haystack,
                                      unsigned char const *reject,
                                      locale_t locale)
/*[[[body:libc__mbscspn_l]]]*/
/*AUTO*/{
	(void)haystack;
	(void)reject;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbscspn_l(%p, %p, %p)", haystack, reject, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbscspn_l]]]*/

/*[[[head:libc__mbsdec_l,hash:CRC-32=0xd45e3e23]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsdec_l)(unsigned char const *start,
                                     unsigned char const *pos,
                                     locale_t locale)
/*[[[body:libc__mbsdec_l]]]*/
/*AUTO*/{
	(void)start;
	(void)pos;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsdec_l(%p, %p, %p)", start, pos, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__mbsdec_l]]]*/

/*[[[head:libc__mbsicmp_l,hash:CRC-32=0x794f48b6]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsicmp_l)(unsigned char const *lhs,
                                      unsigned char const *rhs,
                                      locale_t locale)
/*[[[body:libc__mbsicmp_l]]]*/
/*AUTO*/{
	(void)lhs;
	(void)rhs;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsicmp_l(%p, %p, %p)", lhs, rhs, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbsicmp_l]]]*/

/*[[[head:libc__mbsicoll_l,hash:CRC-32=0x9f9a22b5]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsicoll_l)(unsigned char const *lhs,
                                       unsigned char const *rhs,
                                       locale_t locale)
/*[[[body:libc__mbsicoll_l]]]*/
/*AUTO*/{
	(void)lhs;
	(void)rhs;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsicoll_l(%p, %p, %p)", lhs, rhs, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbsicoll_l]]]*/

/*[[[head:libc__mbsinc_l,hash:CRC-32=0x35ecbc6]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsinc_l)(unsigned char const *ptr,
                                     locale_t locale)
/*[[[body:libc__mbsinc_l]]]*/
/*AUTO*/{
	(void)ptr;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsinc_l(%p, %p)", ptr, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__mbsinc_l]]]*/

/*[[[head:libc__mbslen_l,hash:CRC-32=0xc60640cb]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbslen_l)(unsigned char const *str,
                                     locale_t locale)
/*[[[body:libc__mbslen_l]]]*/
/*AUTO*/{
	(void)str;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbslen_l(%p, %p)", str, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbslen_l]]]*/

/*[[[head:libc__mbsnlen_l,hash:CRC-32=0x711c75d1]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbsnlen_l)(unsigned char const *str,
                                      size_t maxlen,
                                      locale_t locale)
/*[[[body:libc__mbsnlen_l]]]*/
/*AUTO*/{
	(void)str;
	(void)maxlen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsnlen_l(%p, %Ix, %p)", str, maxlen, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbsnlen_l]]]*/

/*[[[head:libc__mbslwr_s_l,hash:CRC-32=0xab0555eb]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbslwr_s_l)(unsigned char *buf,
                                       size_t buflen,
                                       locale_t locale)
/*[[[body:libc__mbslwr_s_l]]]*/
/*AUTO*/{
	(void)buf;
	(void)buflen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbslwr_s_l(%p, %Ix, %p)", buf, buflen, locale); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__mbslwr_s_l]]]*/

/*[[[head:libc__mbslwr_l,hash:CRC-32=0xb399545d]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbslwr_l)(unsigned char *buf,
                                     locale_t locale)
/*[[[body:libc__mbslwr_l]]]*/
/*AUTO*/{
	(void)buf;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbslwr_l(%p, %p)", buf, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__mbslwr_l]]]*/

/*[[[head:libc__mbsnbcat_s_l,hash:CRC-32=0x7d1a7679]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsnbcat_s_l)(unsigned char *buf,
                                         size_t bufsize,
                                         unsigned char const *src,
                                         size_t maxlen,
                                         locale_t locale)
/*[[[body:libc__mbsnbcat_s_l]]]*/
/*AUTO*/{
	(void)buf;
	(void)bufsize;
	(void)src;
	(void)maxlen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsnbcat_s_l(%p, %Ix, %p, %Ix, %p)", buf, bufsize, src, maxlen, locale); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__mbsnbcat_s_l]]]*/

/*[[[head:libc__mbsnbcat_l,hash:CRC-32=0xdd49c6bf]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsnbcat_l)(unsigned char *buf,
                                       unsigned char const *src,
                                       size_t srclen,
                                       locale_t locale)
/*[[[body:libc__mbsnbcat_l]]]*/
/*AUTO*/{
	(void)buf;
	(void)src;
	(void)srclen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsnbcat_l(%p, %p, %Ix, %p)", buf, src, srclen, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__mbsnbcat_l]]]*/

/*[[[head:libc__mbsnbcmp_l,hash:CRC-32=0xab97ad2c]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnbcmp_l)(unsigned char const *lhs,
                                       unsigned char const *rhs,
                                       size_t maxlen,
                                       locale_t locale)
/*[[[body:libc__mbsnbcmp_l]]]*/
/*AUTO*/{
	(void)lhs;
	(void)rhs;
	(void)maxlen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsnbcmp_l(%p, %p, %Ix, %p)", lhs, rhs, maxlen, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbsnbcmp_l]]]*/

/*[[[head:libc__mbsnbcoll_l,hash:CRC-32=0x61f26c9e]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnbcoll_l)(unsigned char const *lhs,
                                        unsigned char const *rhs,
                                        size_t maxlen,
                                        locale_t locale)
/*[[[body:libc__mbsnbcoll_l]]]*/
/*AUTO*/{
	(void)lhs;
	(void)rhs;
	(void)maxlen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsnbcoll_l(%p, %p, %Ix, %p)", lhs, rhs, maxlen, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbsnbcoll_l]]]*/

/*[[[head:libc__mbsnbcnt_l,hash:CRC-32=0x69e55901]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbsnbcnt_l)(unsigned char const *str,
                                       size_t maxlen,
                                       locale_t locale)
/*[[[body:libc__mbsnbcnt_l]]]*/
/*AUTO*/{
	(void)str;
	(void)maxlen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsnbcnt_l(%p, %Ix, %p)", str, maxlen, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbsnbcnt_l]]]*/

/*[[[head:libc__mbsnbcpy_s_l,hash:CRC-32=0x172c362b]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsnbcpy_s_l)(unsigned char *buf,
                                         size_t bufsize,
                                         unsigned char const *src,
                                         size_t srclen,
                                         locale_t locale)
/*[[[body:libc__mbsnbcpy_s_l]]]*/
/*AUTO*/{
	(void)buf;
	(void)bufsize;
	(void)src;
	(void)srclen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsnbcpy_s_l(%p, %Ix, %p, %Ix, %p)", buf, bufsize, src, srclen, locale); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__mbsnbcpy_s_l]]]*/

/*[[[head:libc__mbsnbcpy_l,hash:CRC-32=0x7371077c]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsnbcpy_l)(unsigned char *buf,
                                       unsigned char const *src,
                                       size_t srclen,
                                       locale_t locale)
/*[[[body:libc__mbsnbcpy_l]]]*/
/*AUTO*/{
	(void)buf;
	(void)src;
	(void)srclen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsnbcpy_l(%p, %p, %Ix, %p)", buf, src, srclen, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__mbsnbcpy_l]]]*/

/*[[[head:libc__mbsnbicmp_l,hash:CRC-32=0xa48c99a6]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnbicmp_l)(unsigned char const *lhs,
                                        unsigned char const *rhs,
                                        size_t maxlen,
                                        locale_t locale)
/*[[[body:libc__mbsnbicmp_l]]]*/
/*AUTO*/{
	(void)lhs;
	(void)rhs;
	(void)maxlen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsnbicmp_l(%p, %p, %Ix, %p)", lhs, rhs, maxlen, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbsnbicmp_l]]]*/

/*[[[head:libc__mbsnbicoll_l,hash:CRC-32=0x78608dd1]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnbicoll_l)(unsigned char const *lhs,
                                         unsigned char const *rhs,
                                         size_t maxlen,
                                         locale_t locale)
/*[[[body:libc__mbsnbicoll_l]]]*/
/*AUTO*/{
	(void)lhs;
	(void)rhs;
	(void)maxlen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsnbicoll_l(%p, %p, %Ix, %p)", lhs, rhs, maxlen, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbsnbicoll_l]]]*/

/*[[[head:libc__mbsnbset_s_l,hash:CRC-32=0xbf54393c]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsnbset_s_l)(unsigned char *buf,
                                         size_t bufsize,
                                         unsigned int ch,
                                         size_t num_chars,
                                         locale_t locale)
/*[[[body:libc__mbsnbset_s_l]]]*/
/*AUTO*/{
	(void)buf;
	(void)bufsize;
	(void)ch;
	(void)num_chars;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsnbset_s_l(%p, %Ix, %x, %Ix, %p)", buf, bufsize, ch, num_chars, locale); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__mbsnbset_s_l]]]*/

/*[[[head:libc__mbsnbset_l,hash:CRC-32=0x62b20a71]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsnbset_l)(unsigned char *buf,
                                       unsigned int ch,
                                       size_t buflen,
                                       locale_t locale)
/*[[[body:libc__mbsnbset_l]]]*/
/*AUTO*/{
	(void)buf;
	(void)ch;
	(void)buflen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsnbset_l(%p, %x, %Ix, %p)", buf, ch, buflen, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__mbsnbset_l]]]*/

/*[[[head:libc__mbsncat_s_l,hash:CRC-32=0xbb39fe5c]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsncat_s_l)(unsigned char *buf,
                                        size_t bufsize,
                                        unsigned char const *src,
                                        size_t srclen,
                                        locale_t locale)
/*[[[body:libc__mbsncat_s_l]]]*/
/*AUTO*/{
	(void)buf;
	(void)bufsize;
	(void)src;
	(void)srclen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsncat_s_l(%p, %Ix, %p, %Ix, %p)", buf, bufsize, src, srclen, locale); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__mbsncat_s_l]]]*/

/*[[[head:libc__mbsncat_l,hash:CRC-32=0x9d65b2bc]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsncat_l)(unsigned char *buf,
                                      unsigned char const *src,
                                      size_t srclen,
                                      locale_t locale)
/*[[[body:libc__mbsncat_l]]]*/
/*AUTO*/{
	(void)buf;
	(void)src;
	(void)srclen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsncat_l(%p, %p, %Ix, %p)", buf, src, srclen, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__mbsncat_l]]]*/

/*[[[head:libc__mbsnccnt_l,hash:CRC-32=0x4f52553c]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbsnccnt_l)(unsigned char const *str,
                                       size_t maxlen,
                                       locale_t locale)
/*[[[body:libc__mbsnccnt_l]]]*/
/*AUTO*/{
	(void)str;
	(void)maxlen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsnccnt_l(%p, %Ix, %p)", str, maxlen, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbsnccnt_l]]]*/

/*[[[head:libc__mbsncmp_l,hash:CRC-32=0x5678008]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsncmp_l)(unsigned char const *lhs,
                                      unsigned char const *rhs,
                                      size_t maxlen,
                                      locale_t locale)
/*[[[body:libc__mbsncmp_l]]]*/
/*AUTO*/{
	(void)lhs;
	(void)rhs;
	(void)maxlen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsncmp_l(%p, %p, %Ix, %p)", lhs, rhs, maxlen, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbsncmp_l]]]*/

/*[[[head:libc__mbsncoll_l,hash:CRC-32=0xc17f2144]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsncoll_l)(unsigned char const *lhs,
                                       unsigned char const *rhs,
                                       size_t maxlen,
                                       locale_t locale)
/*[[[body:libc__mbsncoll_l]]]*/
/*AUTO*/{
	(void)lhs;
	(void)rhs;
	(void)maxlen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsncoll_l(%p, %p, %Ix, %p)", lhs, rhs, maxlen, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbsncoll_l]]]*/

/*[[[head:libc__mbsncpy_s_l,hash:CRC-32=0x880ebbe7]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsncpy_s_l)(unsigned char *buf,
                                        size_t bufsize,
                                        unsigned char const *src,
                                        size_t maxlen,
                                        locale_t locale)
/*[[[body:libc__mbsncpy_s_l]]]*/
/*AUTO*/{
	(void)buf;
	(void)bufsize;
	(void)src;
	(void)maxlen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsncpy_s_l(%p, %Ix, %p, %Ix, %p)", buf, bufsize, src, maxlen, locale); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__mbsncpy_s_l]]]*/

/*[[[head:libc__mbsncpy_l,hash:CRC-32=0x66e9348e]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsncpy_l)(unsigned char *buf,
                                      unsigned char const *src,
                                      size_t srclen,
                                      locale_t locale)
/*[[[body:libc__mbsncpy_l]]]*/
/*AUTO*/{
	(void)buf;
	(void)src;
	(void)srclen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsncpy_l(%p, %p, %Ix, %p)", buf, src, srclen, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__mbsncpy_l]]]*/

/*[[[head:libc__mbsnextc_l,hash:CRC-32=0xed0edf65]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) unsigned int
NOTHROW_NCX(LIBCCALL libc__mbsnextc_l)(unsigned char const *str,
                                       locale_t locale)
/*[[[body:libc__mbsnextc_l]]]*/
/*AUTO*/{
	(void)str;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsnextc_l(%p, %p)", str, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbsnextc_l]]]*/

/*[[[head:libc__mbsnicmp_l,hash:CRC-32=0x76494ed]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnicmp_l)(unsigned char const *lhs,
                                       unsigned char const *rhs,
                                       size_t maxlen,
                                       locale_t locale)
/*[[[body:libc__mbsnicmp_l]]]*/
/*AUTO*/{
	(void)lhs;
	(void)rhs;
	(void)maxlen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsnicmp_l(%p, %p, %Ix, %p)", lhs, rhs, maxlen, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbsnicmp_l]]]*/

/*[[[head:libc__mbsnicoll_l,hash:CRC-32=0x6448665f]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__mbsnicoll_l)(unsigned char const *lhs,
                                        unsigned char const *rhs,
                                        size_t maxlen,
                                        locale_t locale)
/*[[[body:libc__mbsnicoll_l]]]*/
/*AUTO*/{
	(void)lhs;
	(void)rhs;
	(void)maxlen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsnicoll_l(%p, %p, %Ix, %p)", lhs, rhs, maxlen, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbsnicoll_l]]]*/

/*[[[head:libc__mbsninc_l,hash:CRC-32=0x771232f1]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsninc_l)(unsigned char const *str,
                                      size_t maxlen,
                                      locale_t locale)
/*[[[body:libc__mbsninc_l]]]*/
/*AUTO*/{
	(void)str;
	(void)maxlen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsninc_l(%p, %Ix, %p)", str, maxlen, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__mbsninc_l]]]*/

/*[[[head:libc__mbsnset_s_l,hash:CRC-32=0x804a74bd]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsnset_s_l)(unsigned char *buf,
                                        size_t bufsize,
                                        unsigned int ch,
                                        size_t maxlen,
                                        locale_t locale)
/*[[[body:libc__mbsnset_s_l]]]*/
/*AUTO*/{
	(void)buf;
	(void)bufsize;
	(void)ch;
	(void)maxlen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsnset_s_l(%p, %Ix, %x, %Ix, %p)", buf, bufsize, ch, maxlen, locale); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__mbsnset_s_l]]]*/

/*[[[head:libc__mbsnset_l,hash:CRC-32=0x4834e609]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_RETNONNULL NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsnset_l)(unsigned char *buf,
                                      unsigned int ch,
                                      size_t maxlen,
                                      locale_t locale)
/*[[[body:libc__mbsnset_l]]]*/
/*AUTO*/{
	(void)buf;
	(void)ch;
	(void)maxlen;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsnset_l(%p, %x, %Ix, %p)", buf, ch, maxlen, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__mbsnset_l]]]*/

/*[[[head:libc__mbspbrk_l,hash:CRC-32=0xab972b1b]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbspbrk_l)(unsigned char const *haystack,
                                      unsigned char const *accept,
                                      locale_t locale)
/*[[[body:libc__mbspbrk_l]]]*/
/*AUTO*/{
	(void)haystack;
	(void)accept;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbspbrk_l(%p, %p, %p)", haystack, accept, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__mbspbrk_l]]]*/

/*[[[head:libc__mbsrchr_l,hash:CRC-32=0xdd3426e8]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsrchr_l)(unsigned char const *haystack,
                                      unsigned int needle,
                                      locale_t locale)
/*[[[body:libc__mbsrchr_l]]]*/
/*AUTO*/{
	(void)haystack;
	(void)needle;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsrchr_l(%p, %x, %p)", haystack, needle, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__mbsrchr_l]]]*/

/*[[[head:libc__mbsrev_l,hash:CRC-32=0xd19293cb]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_RETNONNULL NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsrev_l)(unsigned char *buf,
                                     locale_t locale)
/*[[[body:libc__mbsrev_l]]]*/
/*AUTO*/{
	(void)buf;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsrev_l(%p, %p)", buf, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__mbsrev_l]]]*/

/*[[[head:libc__mbsset_s_l,hash:CRC-32=0xcc0e0f9a]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsset_s_l)(unsigned char *buf,
                                       size_t bufsize,
                                       unsigned int ch,
                                       locale_t locale)
/*[[[body:libc__mbsset_s_l]]]*/
/*AUTO*/{
	(void)buf;
	(void)bufsize;
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsset_s_l(%p, %Ix, %x, %p)", buf, bufsize, ch, locale); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__mbsset_s_l]]]*/

/*[[[head:libc__mbsset_l,hash:CRC-32=0x1078d8e3]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_RETNONNULL NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsset_l)(unsigned char *buf,
                                     unsigned int ch,
                                     locale_t locale)
/*[[[body:libc__mbsset_l]]]*/
/*AUTO*/{
	(void)buf;
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsset_l(%p, %x, %p)", buf, ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__mbsset_l]]]*/

/*[[[head:libc__mbsspn_l,hash:CRC-32=0x217c2c9e]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) size_t
NOTHROW_NCX(LIBCCALL libc__mbsspn_l)(unsigned char const *haystack,
                                     unsigned char const *accept,
                                     locale_t locale)
/*[[[body:libc__mbsspn_l]]]*/
/*AUTO*/{
	(void)haystack;
	(void)accept;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsspn_l(%p, %p, %p)", haystack, accept, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbsspn_l]]]*/

/*[[[head:libc__mbsspnp_l,hash:CRC-32=0xf1efe533]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsspnp_l)(unsigned char const *lhs,
                                      unsigned char const *rhs,
                                      locale_t locale)
/*[[[body:libc__mbsspnp_l]]]*/
/*AUTO*/{
	(void)lhs;
	(void)rhs;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsspnp_l(%p, %p, %p)", lhs, rhs, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__mbsspnp_l]]]*/

/*[[[head:libc__mbsstr_l,hash:CRC-32=0xbb698d9e]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsstr_l)(unsigned char const *haystack,
                                     unsigned char const *needle,
                                     locale_t locale)
/*[[[body:libc__mbsstr_l]]]*/
/*AUTO*/{
	(void)haystack;
	(void)needle;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsstr_l(%p, %p, %p)", haystack, needle, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__mbsstr_l]]]*/

/*[[[head:libc__mbstok_s_l,hash:CRC-32=0x952e43e1]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((2, 3)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbstok_s_l)(unsigned char *str,
                                       unsigned char const *delim,
                                       unsigned char **__restrict save_ptr,
                                       locale_t locale)
/*[[[body:libc__mbstok_s_l]]]*/
/*AUTO*/{
	(void)str;
	(void)delim;
	(void)save_ptr;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbstok_s_l(%p, %p, %p, %p)", str, delim, save_ptr, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__mbstok_s_l]]]*/

/*[[[head:libc__mbsupr_s_l,hash:CRC-32=0x11a750b0]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbsupr_s_l)(unsigned char *buf,
                                       size_t bufsize,
                                       locale_t locale)
/*[[[body:libc__mbsupr_s_l]]]*/
/*AUTO*/{
	(void)buf;
	(void)bufsize;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsupr_s_l(%p, %Ix, %p)", buf, bufsize, locale); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__mbsupr_s_l]]]*/

/*[[[head:libc__mbsupr_l,hash:CRC-32=0x8a837986]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") ATTR_RETNONNULL NONNULL((1)) unsigned char *
NOTHROW_NCX(LIBCCALL libc__mbsupr_l)(unsigned char *buf,
                                     locale_t locale)
/*[[[body:libc__mbsupr_l]]]*/
/*AUTO*/{
	(void)buf;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbsupr_l(%p, %p)", buf, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__mbsupr_l]]]*/

/*[[[head:libc__mbclen_l,hash:CRC-32=0xba05d29c]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(LIBCCALL libc__mbclen_l)(unsigned char const *str,
                                     locale_t locale)
/*[[[body:libc__mbclen_l]]]*/
/*AUTO*/{
	(void)str;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbclen_l(%p, %p)", str, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbclen_l]]]*/

/*[[[head:libc__mbccpy_l,hash:CRC-32=0x80e20d72]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 2)) void
NOTHROW_NCX(LIBCCALL libc__mbccpy_l)(unsigned char *buf,
                                     unsigned char const *src,
                                     locale_t locale)
/*[[[body:libc__mbccpy_l]]]*/
/*AUTO*/{
	(void)buf;
	(void)src;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbccpy_l(%p, %p, %p)", buf, src, locale); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc__mbccpy_l]]]*/

/*[[[head:libc__mbccpy_s_l,hash:CRC-32=0x12e5ad8a]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 4)) errno_t
NOTHROW_NCX(LIBCCALL libc__mbccpy_s_l)(unsigned char *buf,
                                       size_t bufsize,
                                       int *p_copied,
                                       unsigned char const *src,
                                       locale_t locale)
/*[[[body:libc__mbccpy_s_l]]]*/
/*AUTO*/{
	(void)buf;
	(void)bufsize;
	(void)p_copied;
	(void)src;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbccpy_s_l(%p, %Ix, %p, %p, %p)", buf, bufsize, p_copied, src, locale); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__mbccpy_s_l]]]*/

/*[[[head:libc__ismbcalnum_l,hash:CRC-32=0x7e69f1a8]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcalnum_l)(unsigned int ch,
                                         locale_t locale)
/*[[[body:libc__ismbcalnum_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_ismbcalnum_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__ismbcalnum_l]]]*/

/*[[[head:libc__ismbcalpha_l,hash:CRC-32=0x5b51d26e]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcalpha_l)(unsigned int ch,
                                         locale_t locale)
/*[[[body:libc__ismbcalpha_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_ismbcalpha_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__ismbcalpha_l]]]*/

/*[[[head:libc__ismbcdigit_l,hash:CRC-32=0x866e4c7a]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcdigit_l)(unsigned int ch,
                                         locale_t locale)
/*[[[body:libc__ismbcdigit_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_ismbcdigit_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__ismbcdigit_l]]]*/

/*[[[head:libc__ismbcgraph_l,hash:CRC-32=0xbb10ae95]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcgraph_l)(unsigned int ch,
                                         locale_t locale)
/*[[[body:libc__ismbcgraph_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_ismbcgraph_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__ismbcgraph_l]]]*/

/*[[[head:libc__ismbclegal_l,hash:CRC-32=0x3139e46a]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbclegal_l)(unsigned int ch,
                                         locale_t locale)
/*[[[body:libc__ismbclegal_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_ismbclegal_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__ismbclegal_l]]]*/

/*[[[head:libc__ismbclower_l,hash:CRC-32=0xf2aedab7]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbclower_l)(unsigned int ch,
                                         locale_t locale)
/*[[[body:libc__ismbclower_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_ismbclower_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__ismbclower_l]]]*/

/*[[[head:libc__ismbcprint_l,hash:CRC-32=0x36a6550a]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcprint_l)(unsigned int ch,
                                         locale_t locale)
/*[[[body:libc__ismbcprint_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_ismbcprint_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__ismbcprint_l]]]*/

/*[[[head:libc__ismbcpunct_l,hash:CRC-32=0xef34080c]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcpunct_l)(unsigned int ch,
                                         locale_t locale)
/*[[[body:libc__ismbcpunct_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_ismbcpunct_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__ismbcpunct_l]]]*/

/*[[[head:libc__ismbcblank_l,hash:CRC-32=0x32b78308]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcblank_l)(unsigned int ch,
                                         locale_t locale)
/*[[[body:libc__ismbcblank_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_ismbcblank_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__ismbcblank_l]]]*/

/*[[[head:libc__ismbcspace_l,hash:CRC-32=0xf593c82a]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcspace_l)(unsigned int ch,
                                         locale_t locale)
/*[[[body:libc__ismbcspace_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_ismbcspace_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__ismbcspace_l]]]*/

/*[[[head:libc__ismbcupper_l,hash:CRC-32=0xe1840306]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcupper_l)(unsigned int ch,
                                         locale_t locale)
/*[[[body:libc__ismbcupper_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_ismbcupper_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__ismbcupper_l]]]*/

/*[[[head:libc__mbctolower_l,hash:CRC-32=0x944f291c]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbctolower_l)(unsigned int ch,
                                         locale_t locale)
/*[[[body:libc__mbctolower_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbctolower_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbctolower_l]]]*/

/*[[[head:libc__mbctoupper_l,hash:CRC-32=0x8765f0ad]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbctoupper_l)(unsigned int ch,
                                         locale_t locale)
/*[[[body:libc__mbctoupper_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbctoupper_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbctoupper_l]]]*/

/*[[[head:libc__ismbchira_l,hash:CRC-32=0xa2401c82]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbchira_l)(unsigned int ch,
                                        locale_t locale)
/*[[[body:libc__ismbchira_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_ismbchira_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__ismbchira_l]]]*/

/*[[[head:libc__ismbckata_l,hash:CRC-32=0xb2ae7e68]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbckata_l)(unsigned int ch,
                                        locale_t locale)
/*[[[body:libc__ismbckata_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_ismbckata_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__ismbckata_l]]]*/

/*[[[head:libc__ismbcsymbol_l,hash:CRC-32=0x522d3d47]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcsymbol_l)(unsigned int ch,
                                          locale_t locale)
/*[[[body:libc__ismbcsymbol_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_ismbcsymbol_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__ismbcsymbol_l]]]*/

/*[[[head:libc__ismbcl0_l,hash:CRC-32=0xc97cf4c1]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcl0_l)(unsigned int ch,
                                      locale_t locale)
/*[[[body:libc__ismbcl0_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_ismbcl0_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__ismbcl0_l]]]*/

/*[[[head:libc__ismbcl1_l,hash:CRC-32=0x893abdb]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcl1_l)(unsigned int ch,
                                      locale_t locale)
/*[[[body:libc__ismbcl1_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_ismbcl1_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__ismbcl1_l]]]*/

/*[[[head:libc__ismbcl2_l,hash:CRC-32=0x91d34cb4]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbcl2_l)(unsigned int ch,
                                      locale_t locale)
/*[[[body:libc__ismbcl2_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_ismbcl2_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__ismbcl2_l]]]*/

/*[[[head:libc__mbcjistojms_l,hash:CRC-32=0x3a606f8c]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbcjistojms_l)(unsigned int ch,
                                          locale_t locale)
/*[[[body:libc__mbcjistojms_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbcjistojms_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbcjistojms_l]]]*/

/*[[[head:libc__mbcjmstojis_l,hash:CRC-32=0x73621d09]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbcjmstojis_l)(unsigned int ch,
                                          locale_t locale)
/*[[[body:libc__mbcjmstojis_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbcjmstojis_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbcjmstojis_l]]]*/

/*[[[head:libc__mbctohira_l,hash:CRC-32=0xd20cc18c]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbctohira_l)(unsigned int ch,
                                        locale_t locale)
/*[[[body:libc__mbctohira_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbctohira_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbctohira_l]]]*/

/*[[[head:libc__mbctokata_l,hash:CRC-32=0xc2e2a366]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED unsigned int
NOTHROW_NCX(LIBCCALL libc__mbctokata_l)(unsigned int ch,
                                        locale_t locale)
/*[[[body:libc__mbctokata_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_mbctokata_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__mbctokata_l]]]*/

/*[[[head:libc__ismbblead_l,hash:CRC-32=0x1cdde07]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbblead_l)(unsigned int ch,
                                        locale_t locale)
/*[[[body:libc__ismbblead_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_ismbblead_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__ismbblead_l]]]*/

/*[[[head:libc__ismbbtrail_l,hash:CRC-32=0x51e2103a]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED int
NOTHROW_NCX(LIBCCALL libc__ismbbtrail_l)(unsigned int ch,
                                         locale_t locale)
/*[[[body:libc__ismbbtrail_l]]]*/
/*AUTO*/{
	(void)ch;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_ismbbtrail_l(%x, %p)", ch, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__ismbbtrail_l]]]*/

/*[[[head:libc__ismbslead_l,hash:CRC-32=0x7dc7c957]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__ismbslead_l)(unsigned char const *str,
                                        unsigned char const *pos,
                                        locale_t locale)
/*[[[body:libc__ismbslead_l]]]*/
/*AUTO*/{
	(void)str;
	(void)pos;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_ismbslead_l(%p, %p, %p)", str, pos, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__ismbslead_l]]]*/

/*[[[head:libc__ismbstrail_l,hash:CRC-32=0x6acc673c]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL libc__ismbstrail_l)(unsigned char const *str,
                                         unsigned char const *pos,
                                         locale_t locale)
/*[[[body:libc__ismbstrail_l]]]*/
/*AUTO*/{
	(void)str;
	(void)pos;
	(void)locale;
	CRT_UNIMPLEMENTEDF("_ismbstrail_l(%p, %p, %p)", str, pos, locale); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__ismbstrail_l]]]*/

/*[[[start:exports,hash:CRC-32=0x459b6f48]]]*/
DEFINE_PUBLIC_ALIAS(_mbbtombc_l, libc__mbbtombc_l);
DEFINE_PUBLIC_ALIAS(_mbbtype_l, libc__mbbtype_l);
DEFINE_PUBLIC_ALIAS(_mbctombb_l, libc__mbctombb_l);
DEFINE_PUBLIC_ALIAS(_mbsbtype_l, libc__mbsbtype_l);
DEFINE_PUBLIC_ALIAS(_mbscat_s_l, libc__mbscat_s_l);
DEFINE_PUBLIC_ALIAS(_mbschr_l, libc__mbschr_l);
DEFINE_PUBLIC_ALIAS(_mbscmp_l, libc__mbscmp_l);
DEFINE_PUBLIC_ALIAS(_mbscoll_l, libc__mbscoll_l);
DEFINE_PUBLIC_ALIAS(_mbscpy_s_l, libc__mbscpy_s_l);
DEFINE_PUBLIC_ALIAS(_mbscspn_l, libc__mbscspn_l);
DEFINE_PUBLIC_ALIAS(_mbsdec_l, libc__mbsdec_l);
DEFINE_PUBLIC_ALIAS(_mbsicmp_l, libc__mbsicmp_l);
DEFINE_PUBLIC_ALIAS(_mbsicoll_l, libc__mbsicoll_l);
DEFINE_PUBLIC_ALIAS(_mbsinc_l, libc__mbsinc_l);
DEFINE_PUBLIC_ALIAS(_mbslen_l, libc__mbslen_l);
DEFINE_PUBLIC_ALIAS(_mbsnlen_l, libc__mbsnlen_l);
DEFINE_PUBLIC_ALIAS(_mbslwr_s_l, libc__mbslwr_s_l);
DEFINE_PUBLIC_ALIAS(_mbslwr_l, libc__mbslwr_l);
DEFINE_PUBLIC_ALIAS(_mbsnbcat_s_l, libc__mbsnbcat_s_l);
DEFINE_PUBLIC_ALIAS(_mbsnbcat_l, libc__mbsnbcat_l);
DEFINE_PUBLIC_ALIAS(_mbsnbcmp_l, libc__mbsnbcmp_l);
DEFINE_PUBLIC_ALIAS(_mbsnbcoll_l, libc__mbsnbcoll_l);
DEFINE_PUBLIC_ALIAS(_mbsnbcnt_l, libc__mbsnbcnt_l);
DEFINE_PUBLIC_ALIAS(_mbsnbcpy_s_l, libc__mbsnbcpy_s_l);
DEFINE_PUBLIC_ALIAS(_mbsnbcpy_l, libc__mbsnbcpy_l);
DEFINE_PUBLIC_ALIAS(_mbsnbicmp_l, libc__mbsnbicmp_l);
DEFINE_PUBLIC_ALIAS(_mbsnbicoll_l, libc__mbsnbicoll_l);
DEFINE_PUBLIC_ALIAS(_mbsnbset_s_l, libc__mbsnbset_s_l);
DEFINE_PUBLIC_ALIAS(_mbsnbset_l, libc__mbsnbset_l);
DEFINE_PUBLIC_ALIAS(_mbsncat_s_l, libc__mbsncat_s_l);
DEFINE_PUBLIC_ALIAS(_mbsncat_l, libc__mbsncat_l);
DEFINE_PUBLIC_ALIAS(_mbsnccnt_l, libc__mbsnccnt_l);
DEFINE_PUBLIC_ALIAS(_mbsncmp_l, libc__mbsncmp_l);
DEFINE_PUBLIC_ALIAS(_mbsncoll_l, libc__mbsncoll_l);
DEFINE_PUBLIC_ALIAS(_mbsncpy_s_l, libc__mbsncpy_s_l);
DEFINE_PUBLIC_ALIAS(_mbsncpy_l, libc__mbsncpy_l);
DEFINE_PUBLIC_ALIAS(_mbsnextc_l, libc__mbsnextc_l);
DEFINE_PUBLIC_ALIAS(_mbsnicmp_l, libc__mbsnicmp_l);
DEFINE_PUBLIC_ALIAS(_mbsnicoll_l, libc__mbsnicoll_l);
DEFINE_PUBLIC_ALIAS(_mbsninc_l, libc__mbsninc_l);
DEFINE_PUBLIC_ALIAS(_mbsnset_s_l, libc__mbsnset_s_l);
DEFINE_PUBLIC_ALIAS(_mbsnset_l, libc__mbsnset_l);
DEFINE_PUBLIC_ALIAS(_mbspbrk_l, libc__mbspbrk_l);
DEFINE_PUBLIC_ALIAS(_mbsrchr_l, libc__mbsrchr_l);
DEFINE_PUBLIC_ALIAS(_mbsrev_l, libc__mbsrev_l);
DEFINE_PUBLIC_ALIAS(_mbsset_s_l, libc__mbsset_s_l);
DEFINE_PUBLIC_ALIAS(_mbsset_l, libc__mbsset_l);
DEFINE_PUBLIC_ALIAS(_mbsspn_l, libc__mbsspn_l);
DEFINE_PUBLIC_ALIAS(_mbsspnp_l, libc__mbsspnp_l);
DEFINE_PUBLIC_ALIAS(_mbsstr_l, libc__mbsstr_l);
DEFINE_PUBLIC_ALIAS(_mbstok_s_l, libc__mbstok_s_l);
DEFINE_PUBLIC_ALIAS(_mbsupr_s_l, libc__mbsupr_s_l);
DEFINE_PUBLIC_ALIAS(_mbsupr_l, libc__mbsupr_l);
DEFINE_PUBLIC_ALIAS(_mbclen_l, libc__mbclen_l);
DEFINE_PUBLIC_ALIAS(_mbccpy_l, libc__mbccpy_l);
DEFINE_PUBLIC_ALIAS(_mbccpy_s_l, libc__mbccpy_s_l);
DEFINE_PUBLIC_ALIAS(_ismbcalnum_l, libc__ismbcalnum_l);
DEFINE_PUBLIC_ALIAS(_ismbcalpha_l, libc__ismbcalpha_l);
DEFINE_PUBLIC_ALIAS(_ismbcdigit_l, libc__ismbcdigit_l);
DEFINE_PUBLIC_ALIAS(_ismbcgraph_l, libc__ismbcgraph_l);
DEFINE_PUBLIC_ALIAS(_ismbclegal_l, libc__ismbclegal_l);
DEFINE_PUBLIC_ALIAS(_ismbclower_l, libc__ismbclower_l);
DEFINE_PUBLIC_ALIAS(_ismbcprint_l, libc__ismbcprint_l);
DEFINE_PUBLIC_ALIAS(_ismbcpunct_l, libc__ismbcpunct_l);
DEFINE_PUBLIC_ALIAS(_ismbcblank_l, libc__ismbcblank_l);
DEFINE_PUBLIC_ALIAS(_ismbcspace_l, libc__ismbcspace_l);
DEFINE_PUBLIC_ALIAS(_ismbcupper_l, libc__ismbcupper_l);
DEFINE_PUBLIC_ALIAS(_mbctolower_l, libc__mbctolower_l);
DEFINE_PUBLIC_ALIAS(_mbctoupper_l, libc__mbctoupper_l);
DEFINE_PUBLIC_ALIAS(_ismbchira_l, libc__ismbchira_l);
DEFINE_PUBLIC_ALIAS(_ismbckata_l, libc__ismbckata_l);
DEFINE_PUBLIC_ALIAS(_ismbcsymbol_l, libc__ismbcsymbol_l);
DEFINE_PUBLIC_ALIAS(_ismbcl0_l, libc__ismbcl0_l);
DEFINE_PUBLIC_ALIAS(_ismbcl1_l, libc__ismbcl1_l);
DEFINE_PUBLIC_ALIAS(_ismbcl2_l, libc__ismbcl2_l);
DEFINE_PUBLIC_ALIAS(_mbcjistojms_l, libc__mbcjistojms_l);
DEFINE_PUBLIC_ALIAS(_mbcjmstojis_l, libc__mbcjmstojis_l);
DEFINE_PUBLIC_ALIAS(_mbctohira_l, libc__mbctohira_l);
DEFINE_PUBLIC_ALIAS(_mbctokata_l, libc__mbctokata_l);
DEFINE_PUBLIC_ALIAS(_ismbblead_l, libc__ismbblead_l);
DEFINE_PUBLIC_ALIAS(_ismbbtrail_l, libc__ismbbtrail_l);
DEFINE_PUBLIC_ALIAS(_ismbslead_l, libc__ismbslead_l);
DEFINE_PUBLIC_ALIAS(_ismbstrail_l, libc__ismbstrail_l);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_MBSTRING_C */
