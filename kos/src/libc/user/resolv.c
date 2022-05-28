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
#ifndef GUARD_LIBC_USER_RESOLV_C
#define GUARD_LIBC_USER_RESOLV_C 1

#include "../api.h"
/**/

#include "resolv.h"

DECL_BEGIN

/*[[[head:libc___res_state,hash:CRC-32=0xe7539e71]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") ATTR_CONST struct __res_state *
NOTHROW_NCX(LIBCCALL libc___res_state)(void)
/*[[[body:libc___res_state]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("__res_state"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc___res_state]]]*/

/*[[[head:libc_fp_nquery,hash:CRC-32=0x3536c828]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") void
NOTHROW_NCX(LIBCCALL libc_fp_nquery)(u_char const *a,
                                     int b,
                                     FILE *c)
/*[[[body:libc_fp_nquery]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	CRT_UNIMPLEMENTEDF("fp_nquery(%p, %x, %p)", a, b, c); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_fp_nquery]]]*/

/*[[[head:libc_fp_query,hash:CRC-32=0x3955b75e]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") void
NOTHROW_NCX(LIBCCALL libc_fp_query)(u_char const *a,
                                    FILE *b)
/*[[[body:libc_fp_query]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	CRT_UNIMPLEMENTEDF("fp_query(%p, %p)", a, b); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_fp_query]]]*/

/*[[[head:libc_hostalias,hash:CRC-32=0x40707eba]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") char const *
NOTHROW_NCX(LIBCCALL libc_hostalias)(char const *a)
/*[[[body:libc_hostalias]]]*/
/*AUTO*/{
	(void)a;
	CRT_UNIMPLEMENTEDF("hostalias(%q)", a); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_hostalias]]]*/

/*[[[head:libc_p_query,hash:CRC-32=0xa6e18b3f]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") void
NOTHROW_NCX(LIBCCALL libc_p_query)(u_char const *a)
/*[[[body:libc_p_query]]]*/
/*AUTO*/{
	(void)a;
	CRT_UNIMPLEMENTEDF("p_query(%p)", a); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_p_query]]]*/

/*[[[head:libc_res_close,hash:CRC-32=0xdd21ba23]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") void
NOTHROW_NCX(LIBCCALL libc_res_close)(void)
/*[[[body:libc_res_close]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("res_close"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_close]]]*/

/*[[[head:libc_res_init,hash:CRC-32=0xf88a5996]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_res_init)(void)
/*[[[body:libc_res_init]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("res_init"); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_init]]]*/

/*[[[head:libc_res_isourserver,hash:CRC-32=0x2bc59404]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_res_isourserver)(struct sockaddr_in const *a)
/*[[[body:libc_res_isourserver]]]*/
/*AUTO*/{
	(void)a;
	CRT_UNIMPLEMENTEDF("res_isourserver(%p)", a); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_isourserver]]]*/

/*[[[head:libc_res_mkquery,hash:CRC-32=0x6ddce12b]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_res_mkquery)(int a,
                                       char const *b,
                                       int c,
                                       int d,
                                       u_char const *e,
                                       int f,
                                       u_char const *g,
                                       u_char *h,
                                       int i)
/*[[[body:libc_res_mkquery]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	(void)d;
	(void)e;
	(void)f;
	(void)g;
	(void)h;
	(void)i;
	CRT_UNIMPLEMENTEDF("res_mkquery(%x, %q, %x, %x, %p, %x, %p, %p, %x)", a, b, c, d, e, f, g, h, i); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_mkquery]]]*/

/*[[[head:libc_res_query,hash:CRC-32=0xba41060a]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_res_query)(char const *a,
                                     int b,
                                     int c,
                                     u_char *d,
                                     int e)
/*[[[body:libc_res_query]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	(void)d;
	(void)e;
	CRT_UNIMPLEMENTEDF("res_query(%q, %x, %x, %p, %x)", a, b, c, d, e); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_query]]]*/

/*[[[head:libc_res_querydomain,hash:CRC-32=0x39339430]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_res_querydomain)(char const *a,
                                           char const *b,
                                           int c,
                                           int d,
                                           u_char *e,
                                           int f)
/*[[[body:libc_res_querydomain]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	(void)d;
	(void)e;
	(void)f;
	CRT_UNIMPLEMENTEDF("res_querydomain(%q, %q, %x, %x, %p, %x)", a, b, c, d, e, f); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_querydomain]]]*/

/*[[[head:libc_res_search,hash:CRC-32=0x477a1dd4]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_res_search)(char const *a,
                                      int b,
                                      int c,
                                      u_char *d,
                                      int e)
/*[[[body:libc_res_search]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	(void)d;
	(void)e;
	CRT_UNIMPLEMENTEDF("res_search(%q, %x, %x, %p, %x)", a, b, c, d, e); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_search]]]*/

/*[[[head:libc_res_send,hash:CRC-32=0xf4c526e1]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_res_send)(u_char const *a,
                                    int b,
                                    u_char *c,
                                    int d)
/*[[[body:libc_res_send]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	(void)d;
	CRT_UNIMPLEMENTEDF("res_send(%p, %x, %p, %x)", a, b, c, d); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_send]]]*/

/*[[[head:libc_res_hnok,hash:CRC-32=0xf6356a9]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_res_hnok)(char const *a)
/*[[[body:libc_res_hnok]]]*/
/*AUTO*/{
	(void)a;
	CRT_UNIMPLEMENTEDF("res_hnok(%q)", a); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_hnok]]]*/

/*[[[head:libc_res_ownok,hash:CRC-32=0x51d30385]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_res_ownok)(char const *a)
/*[[[body:libc_res_ownok]]]*/
/*AUTO*/{
	(void)a;
	CRT_UNIMPLEMENTEDF("res_ownok(%q)", a); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_ownok]]]*/

/*[[[head:libc_res_mailok,hash:CRC-32=0x62f94a8b]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_res_mailok)(char const *a)
/*[[[body:libc_res_mailok]]]*/
/*AUTO*/{
	(void)a;
	CRT_UNIMPLEMENTEDF("res_mailok(%q)", a); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_mailok]]]*/

/*[[[head:libc_res_dnok,hash:CRC-32=0x38685b64]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_res_dnok)(char const *a)
/*[[[body:libc_res_dnok]]]*/
/*AUTO*/{
	(void)a;
	CRT_UNIMPLEMENTEDF("res_dnok(%q)", a); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_dnok]]]*/




/*[[[head:libc_b64_ntop,hash:CRC-32=0xe00d0a02]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_b64_ntop)(u_char const *a,
                                    size_t b,
                                    char *c,
                                    size_t d)
/*[[[body:libc_b64_ntop]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	(void)d;
	CRT_UNIMPLEMENTEDF("b64_ntop(%p, %Ix, %q, %Ix)", a, b, c, d); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_b64_ntop]]]*/

/*[[[head:libc_b64_pton,hash:CRC-32=0x458be6bc]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_b64_pton)(char const *a,
                                    u_char *b,
                                    size_t c)
/*[[[body:libc_b64_pton]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	CRT_UNIMPLEMENTEDF("b64_pton(%q, %p, %Ix)", a, b, c); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_b64_pton]]]*/

/*[[[head:libc_loc_aton,hash:CRC-32=0xfe40f521]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_loc_aton)(char const *a,
                                    u_char *b)
/*[[[body:libc_loc_aton]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	CRT_UNIMPLEMENTEDF("loc_aton(%q, %p)", a, b); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_loc_aton]]]*/

/*[[[head:libc_loc_ntoa,hash:CRC-32=0xb3c99be0]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") char const *
NOTHROW_NCX(LIBCCALL libc_loc_ntoa)(u_char const *a,
                                    char *b)
/*[[[body:libc_loc_ntoa]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	CRT_UNIMPLEMENTEDF("loc_ntoa(%p, %q)", a, b); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_loc_ntoa]]]*/




/*[[[head:libc_p_class,hash:CRC-32=0x44130675]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") char const *
NOTHROW_NCX(LIBCCALL libc_p_class)(int a)
/*[[[body:libc_p_class]]]*/
/*AUTO*/{
	(void)a;
	CRT_UNIMPLEMENTEDF("p_class(%x)", a); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_p_class]]]*/

/*[[[head:libc_p_time,hash:CRC-32=0x5d7b8da2]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") char const *
NOTHROW_NCX(LIBCCALL libc_p_time)(u_int32_t a)
/*[[[body:libc_p_time]]]*/
/*AUTO*/{
	(void)a;
	CRT_UNIMPLEMENTEDF("p_time(%" PRIx32 ")", a); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_p_time]]]*/

/*[[[head:libc_p_type,hash:CRC-32=0x514967d7]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") char const *
NOTHROW_NCX(LIBCCALL libc_p_type)(int a)
/*[[[body:libc_p_type]]]*/
/*AUTO*/{
	(void)a;
	CRT_UNIMPLEMENTEDF("p_type(%x)", a); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_p_type]]]*/

/*[[[head:libc_p_rcode,hash:CRC-32=0xdc92fda3]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") char const *
NOTHROW_NCX(LIBCCALL libc_p_rcode)(int a)
/*[[[body:libc_p_rcode]]]*/
/*AUTO*/{
	(void)a;
	CRT_UNIMPLEMENTEDF("p_rcode(%x)", a); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_p_rcode]]]*/

/*[[[head:libc_p_cdnname,hash:CRC-32=0xd3ee27c4]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") u_char const *
NOTHROW_NCX(LIBCCALL libc_p_cdnname)(u_char const *a,
                                     u_char const *b,
                                     int c,
                                     FILE *d)
/*[[[body:libc_p_cdnname]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	(void)d;
	CRT_UNIMPLEMENTEDF("p_cdnname(%p, %p, %x, %p)", a, b, c, d); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_p_cdnname]]]*/

/*[[[head:libc_p_cdname,hash:CRC-32=0x89375b8e]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") u_char const *
NOTHROW_NCX(LIBCCALL libc_p_cdname)(u_char const *a,
                                    u_char const *b,
                                    FILE *c)
/*[[[body:libc_p_cdname]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	CRT_UNIMPLEMENTEDF("p_cdname(%p, %p, %p)", a, b, c); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_p_cdname]]]*/

/*[[[head:libc_p_fqnname,hash:CRC-32=0x5a609765]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") u_char const *
NOTHROW_NCX(LIBCCALL libc_p_fqnname)(u_char const *a,
                                     u_char const *b,
                                     int c,
                                     char *d,
                                     int e)
/*[[[body:libc_p_fqnname]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	(void)d;
	(void)e;
	CRT_UNIMPLEMENTEDF("p_fqnname(%p, %p, %x, %q, %x)", a, b, c, d, e); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_p_fqnname]]]*/

/*[[[head:libc_p_fqname,hash:CRC-32=0xc1d59f6b]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") u_char const *
NOTHROW_NCX(LIBCCALL libc_p_fqname)(u_char const *a,
                                    u_char const *b,
                                    FILE *c)
/*[[[body:libc_p_fqname]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	CRT_UNIMPLEMENTEDF("p_fqname(%p, %p, %p)", a, b, c); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_p_fqname]]]*/

/*[[[head:libc_p_option,hash:CRC-32=0x87a33574]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") char const *
NOTHROW_NCX(LIBCCALL libc_p_option)(u_long a)
/*[[[body:libc_p_option]]]*/
/*AUTO*/{
	(void)a;
	CRT_UNIMPLEMENTEDF("p_option(%lx)", a); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_p_option]]]*/

/*[[[head:libc_p_secstodate,hash:CRC-32=0xb338e51]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") char *
NOTHROW_NCX(LIBCCALL libc_p_secstodate)(u_long a)
/*[[[body:libc_p_secstodate]]]*/
/*AUTO*/{
	(void)a;
	CRT_UNIMPLEMENTEDF("p_secstodate(%lx)", a); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_p_secstodate]]]*/

/*[[[head:libc_dn_count_labels,hash:CRC-32=0x3faa3176]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_dn_count_labels)(char const *a)
/*[[[body:libc_dn_count_labels]]]*/
/*AUTO*/{
	(void)a;
	CRT_UNIMPLEMENTEDF("dn_count_labels(%q)", a); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_dn_count_labels]]]*/



/*[[[head:libc_res_randomid,hash:CRC-32=0xd0aa2c8b]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") u_int
NOTHROW_NCX(LIBCCALL libc_res_randomid)(void)
/*[[[body:libc_res_randomid]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("res_randomid"); /* TODO */
	return (u_int)libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_randomid]]]*/

/*[[[head:libc_res_nameinquery,hash:CRC-32=0xab66d9bf]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_res_nameinquery)(char const *a,
                                           int b,
                                           int c,
                                           u_char const *d,
                                           u_char const *e)
/*[[[body:libc_res_nameinquery]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	(void)d;
	(void)e;
	CRT_UNIMPLEMENTEDF("res_nameinquery(%q, %x, %x, %p, %p)", a, b, c, d, e); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_nameinquery]]]*/

/*[[[head:libc_res_queriesmatch,hash:CRC-32=0x343a9e21]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_res_queriesmatch)(u_char const *a,
                                            u_char const *b,
                                            u_char const *c,
                                            u_char const *d)
/*[[[body:libc_res_queriesmatch]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	(void)d;
	CRT_UNIMPLEMENTEDF("res_queriesmatch(%p, %p, %p, %p)", a, b, c, d); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_queriesmatch]]]*/

/*[[[head:libc_p_section,hash:CRC-32=0xfbc3433]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") char const *
NOTHROW_NCX(LIBCCALL libc_p_section)(int a,
                                     int b)
/*[[[body:libc_p_section]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	CRT_UNIMPLEMENTEDF("p_section(%x, %x)", a, b); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_p_section]]]*/

/*[[[head:libc_res_ninit,hash:CRC-32=0x7999fd73]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_res_ninit)(res_state a)
/*[[[body:libc_res_ninit]]]*/
/*AUTO*/{
	(void)a;
	CRT_UNIMPLEMENTEDF("res_ninit(%p)", a); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_ninit]]]*/

/*[[[head:libc_res_nisourserver,hash:CRC-32=0xe2c9fae9]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_res_nisourserver)(res_state a,
                                            struct sockaddr_in const *b)
/*[[[body:libc_res_nisourserver]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	CRT_UNIMPLEMENTEDF("res_nisourserver(%p, %p)", a, b); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_nisourserver]]]*/

/*[[[head:libc_fp_resstat,hash:CRC-32=0x76d076a4]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") void
NOTHROW_NCX(LIBCCALL libc_fp_resstat)(res_state a,
                                      FILE *b)
/*[[[body:libc_fp_resstat]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	CRT_UNIMPLEMENTEDF("fp_resstat(%p, %p)", a, b); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_fp_resstat]]]*/

/*[[[head:libc_res_npquery,hash:CRC-32=0xf7accae4]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") void
NOTHROW_NCX(LIBCCALL libc_res_npquery)(res_state a,
                                       u_char const *b,
                                       int c,
                                       FILE *d)
/*[[[body:libc_res_npquery]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	(void)d;
	CRT_UNIMPLEMENTEDF("res_npquery(%p, %p, %x, %p)", a, b, c, d); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_npquery]]]*/

/*[[[head:libc_res_hostalias,hash:CRC-32=0xb1364c16]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") char const *
NOTHROW_NCX(LIBCCALL libc_res_hostalias)(res_state a,
                                         char const *b,
                                         char *c,
                                         size_t d)
/*[[[body:libc_res_hostalias]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	(void)d;
	CRT_UNIMPLEMENTEDF("res_hostalias(%p, %q, %q, %Ix)", a, b, c, d); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_res_hostalias]]]*/

/*[[[head:libc_res_nquery,hash:CRC-32=0x5a8cb70a]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_res_nquery)(res_state a,
                                      char const *b,
                                      int c,
                                      int d,
                                      u_char *e,
                                      int f)
/*[[[body:libc_res_nquery]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	(void)d;
	(void)e;
	(void)f;
	CRT_UNIMPLEMENTEDF("res_nquery(%p, %q, %x, %x, %p, %x)", a, b, c, d, e, f); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_nquery]]]*/

/*[[[head:libc_res_nsearch,hash:CRC-32=0x96d8544f]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_res_nsearch)(res_state a,
                                       char const *b,
                                       int c,
                                       int d,
                                       u_char *e,
                                       int f)
/*[[[body:libc_res_nsearch]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	(void)d;
	(void)e;
	(void)f;
	CRT_UNIMPLEMENTEDF("res_nsearch(%p, %q, %x, %x, %p, %x)", a, b, c, d, e, f); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_nsearch]]]*/

/*[[[head:libc_res_nquerydomain,hash:CRC-32=0x553de11]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_res_nquerydomain)(res_state a,
                                            char const *b,
                                            char const *c,
                                            int d,
                                            int e,
                                            u_char *f,
                                            int g)
/*[[[body:libc_res_nquerydomain]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	(void)d;
	(void)e;
	(void)f;
	(void)g;
	CRT_UNIMPLEMENTEDF("res_nquerydomain(%p, %q, %q, %x, %x, %p, %x)", a, b, c, d, e, f, g); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_nquerydomain]]]*/

/*[[[head:libc_res_nmkquery,hash:CRC-32=0x19a081e0]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_res_nmkquery)(res_state a,
                                        int b,
                                        char const *c,
                                        int d,
                                        int e,
                                        u_char const *f,
                                        int g,
                                        u_char const *h,
                                        u_char *i,
                                        int j)
/*[[[body:libc_res_nmkquery]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	(void)d;
	(void)e;
	(void)f;
	(void)g;
	(void)h;
	(void)i;
	(void)j;
	CRT_UNIMPLEMENTEDF("res_nmkquery(%p, %x, %q, %x, %x, %p, %x, %p, %p, %x)", a, b, c, d, e, f, g, h, i, j); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_nmkquery]]]*/

/*[[[head:libc_res_nsend,hash:CRC-32=0x5417ae9b]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_res_nsend)(res_state a,
                                     u_char const *b,
                                     int c,
                                     u_char *d,
                                     int e)
/*[[[body:libc_res_nsend]]]*/
/*AUTO*/{
	(void)a;
	(void)b;
	(void)c;
	(void)d;
	(void)e;
	CRT_UNIMPLEMENTEDF("res_nsend(%p, %p, %x, %p, %x)", a, b, c, d, e); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_nsend]]]*/

/*[[[head:libc_res_nclose,hash:CRC-32=0x5dee1903]]]*/
INTERN ATTR_SECTION(".text.crt.net.nameser") void
NOTHROW_NCX(LIBCCALL libc_res_nclose)(res_state a)
/*[[[body:libc_res_nclose]]]*/
/*AUTO*/{
	(void)a;
	CRT_UNIMPLEMENTEDF("res_nclose(%p)", a); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_res_nclose]]]*/

/*[[[start:exports,hash:CRC-32=0x153c5c7d]]]*/
DEFINE_PUBLIC_ALIAS(__res_state, libc___res_state);
DEFINE_PUBLIC_ALIAS(__fp_nquery, libc_fp_nquery);
DEFINE_PUBLIC_ALIAS(fp_nquery, libc_fp_nquery);
DEFINE_PUBLIC_ALIAS(__fp_query, libc_fp_query);
DEFINE_PUBLIC_ALIAS(fp_query, libc_fp_query);
DEFINE_PUBLIC_ALIAS(__hostalias, libc_hostalias);
DEFINE_PUBLIC_ALIAS(hostalias, libc_hostalias);
DEFINE_PUBLIC_ALIAS(__p_query, libc_p_query);
DEFINE_PUBLIC_ALIAS(p_query, libc_p_query);
DEFINE_PUBLIC_ALIAS(__res_close, libc_res_close);
DEFINE_PUBLIC_ALIAS(res_close, libc_res_close);
DEFINE_PUBLIC_ALIAS(__res_init, libc_res_init);
DEFINE_PUBLIC_ALIAS(res_init, libc_res_init);
DEFINE_PUBLIC_ALIAS(__res_isourserver, libc_res_isourserver);
DEFINE_PUBLIC_ALIAS(res_isourserver, libc_res_isourserver);
DEFINE_PUBLIC_ALIAS(__res_mkquery, libc_res_mkquery);
DEFINE_PUBLIC_ALIAS(res_mkquery, libc_res_mkquery);
DEFINE_PUBLIC_ALIAS(__res_query, libc_res_query);
DEFINE_PUBLIC_ALIAS(res_query, libc_res_query);
DEFINE_PUBLIC_ALIAS(__res_querydomain, libc_res_querydomain);
DEFINE_PUBLIC_ALIAS(res_querydomain, libc_res_querydomain);
DEFINE_PUBLIC_ALIAS(__res_search, libc_res_search);
DEFINE_PUBLIC_ALIAS(res_search, libc_res_search);
DEFINE_PUBLIC_ALIAS(__res_send, libc_res_send);
DEFINE_PUBLIC_ALIAS(res_send, libc_res_send);
DEFINE_PUBLIC_ALIAS(__res_hnok, libc_res_hnok);
DEFINE_PUBLIC_ALIAS(res_hnok, libc_res_hnok);
DEFINE_PUBLIC_ALIAS(__res_ownok, libc_res_ownok);
DEFINE_PUBLIC_ALIAS(res_ownok, libc_res_ownok);
DEFINE_PUBLIC_ALIAS(__res_mailok, libc_res_mailok);
DEFINE_PUBLIC_ALIAS(res_mailok, libc_res_mailok);
DEFINE_PUBLIC_ALIAS(__res_dnok, libc_res_dnok);
DEFINE_PUBLIC_ALIAS(res_dnok, libc_res_dnok);
DEFINE_PUBLIC_ALIAS(__b64_ntop, libc_b64_ntop);
DEFINE_PUBLIC_ALIAS(b64_ntop, libc_b64_ntop);
DEFINE_PUBLIC_ALIAS(__b64_pton, libc_b64_pton);
DEFINE_PUBLIC_ALIAS(b64_pton, libc_b64_pton);
DEFINE_PUBLIC_ALIAS(__loc_aton, libc_loc_aton);
DEFINE_PUBLIC_ALIAS(loc_aton, libc_loc_aton);
DEFINE_PUBLIC_ALIAS(__loc_ntoa, libc_loc_ntoa);
DEFINE_PUBLIC_ALIAS(loc_ntoa, libc_loc_ntoa);
DEFINE_PUBLIC_ALIAS(__p_class, libc_p_class);
DEFINE_PUBLIC_ALIAS(p_class, libc_p_class);
DEFINE_PUBLIC_ALIAS(__p_time, libc_p_time);
DEFINE_PUBLIC_ALIAS(p_time, libc_p_time);
DEFINE_PUBLIC_ALIAS(__p_type, libc_p_type);
DEFINE_PUBLIC_ALIAS(p_type, libc_p_type);
DEFINE_PUBLIC_ALIAS(__p_rcode, libc_p_rcode);
DEFINE_PUBLIC_ALIAS(p_rcode, libc_p_rcode);
DEFINE_PUBLIC_ALIAS(__p_cdnname, libc_p_cdnname);
DEFINE_PUBLIC_ALIAS(p_cdnname, libc_p_cdnname);
DEFINE_PUBLIC_ALIAS(__p_cdname, libc_p_cdname);
DEFINE_PUBLIC_ALIAS(p_cdname, libc_p_cdname);
DEFINE_PUBLIC_ALIAS(__p_fqnname, libc_p_fqnname);
DEFINE_PUBLIC_ALIAS(p_fqnname, libc_p_fqnname);
DEFINE_PUBLIC_ALIAS(__p_fqname, libc_p_fqname);
DEFINE_PUBLIC_ALIAS(p_fqname, libc_p_fqname);
DEFINE_PUBLIC_ALIAS(__p_option, libc_p_option);
DEFINE_PUBLIC_ALIAS(p_option, libc_p_option);
DEFINE_PUBLIC_ALIAS(__p_secstodate, libc_p_secstodate);
DEFINE_PUBLIC_ALIAS(p_secstodate, libc_p_secstodate);
DEFINE_PUBLIC_ALIAS(__dn_count_labels, libc_dn_count_labels);
DEFINE_PUBLIC_ALIAS(dn_count_labels, libc_dn_count_labels);
DEFINE_PUBLIC_ALIAS(__res_randomid, libc_res_randomid);
DEFINE_PUBLIC_ALIAS(res_randomid, libc_res_randomid);
DEFINE_PUBLIC_ALIAS(__res_nameinquery, libc_res_nameinquery);
DEFINE_PUBLIC_ALIAS(res_nameinquery, libc_res_nameinquery);
DEFINE_PUBLIC_ALIAS(__res_queriesmatch, libc_res_queriesmatch);
DEFINE_PUBLIC_ALIAS(res_queriesmatch, libc_res_queriesmatch);
DEFINE_PUBLIC_ALIAS(__p_section, libc_p_section);
DEFINE_PUBLIC_ALIAS(p_section, libc_p_section);
DEFINE_PUBLIC_ALIAS(__res_ninit, libc_res_ninit);
DEFINE_PUBLIC_ALIAS(res_ninit, libc_res_ninit);
DEFINE_PUBLIC_ALIAS(__res_nisourserver, libc_res_nisourserver);
DEFINE_PUBLIC_ALIAS(res_nisourserver, libc_res_nisourserver);
DEFINE_PUBLIC_ALIAS(__fp_resstat, libc_fp_resstat);
DEFINE_PUBLIC_ALIAS(fp_resstat, libc_fp_resstat);
DEFINE_PUBLIC_ALIAS(__res_npquery, libc_res_npquery);
DEFINE_PUBLIC_ALIAS(res_npquery, libc_res_npquery);
DEFINE_PUBLIC_ALIAS(__res_hostalias, libc_res_hostalias);
DEFINE_PUBLIC_ALIAS(res_hostalias, libc_res_hostalias);
DEFINE_PUBLIC_ALIAS(__res_nquery, libc_res_nquery);
DEFINE_PUBLIC_ALIAS(res_nquery, libc_res_nquery);
DEFINE_PUBLIC_ALIAS(__res_nsearch, libc_res_nsearch);
DEFINE_PUBLIC_ALIAS(res_nsearch, libc_res_nsearch);
DEFINE_PUBLIC_ALIAS(__res_nquerydomain, libc_res_nquerydomain);
DEFINE_PUBLIC_ALIAS(res_nquerydomain, libc_res_nquerydomain);
DEFINE_PUBLIC_ALIAS(__res_nmkquery, libc_res_nmkquery);
DEFINE_PUBLIC_ALIAS(res_nmkquery, libc_res_nmkquery);
DEFINE_PUBLIC_ALIAS(__res_nsend, libc_res_nsend);
DEFINE_PUBLIC_ALIAS(res_nsend, libc_res_nsend);
DEFINE_PUBLIC_ALIAS(__res_nclose, libc_res_nclose);
DEFINE_PUBLIC_ALIAS(res_nclose, libc_res_nclose);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_RESOLV_C */
