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

/*[[[head:libc__mbsbtype_l,hash:CRC-32=0xdc354c86]]]*/
INTERN ATTR_SECTION(".text.crt.dos.string.memory") WUNUSED NONNULL((1)) int
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



/*[[[start:exports,hash:CRC-32=0x29fd5420]]]*/
DEFINE_PUBLIC_ALIAS(_mbsbtype_l, libc__mbsbtype_l);
DEFINE_PUBLIC_ALIAS(_mbbtombc_l, libc__mbbtombc_l);
DEFINE_PUBLIC_ALIAS(_mbctombb_l, libc__mbctombb_l);
DEFINE_PUBLIC_ALIAS(_mbbtype_l, libc__mbbtype_l);
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
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_MBSTRING_C */
