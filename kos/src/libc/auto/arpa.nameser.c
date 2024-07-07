/* HASH CRC-32:0xa7417835 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_ARPA_NAMESER_C
#define GUARD_LIBC_AUTO_ARPA_NAMESER_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/arpa.nameser.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <hybrid/__byteswap.h>
#include <hybrid/__unaligned.h>
INTERN ATTR_SECTION(".text.crt.net.nameser") ATTR_PURE WUNUSED ATTR_IN(1) u_int
NOTHROW_NCX(LIBCCALL libc_ns_get16)(u_char const *srcptr) {
	return __hybrid_unaligned_getbe16(srcptr);
}
#include <hybrid/__byteswap.h>
#include <hybrid/__unaligned.h>
INTERN ATTR_SECTION(".text.crt.net.nameser") ATTR_PURE WUNUSED ATTR_IN(1) u_long
NOTHROW_NCX(LIBCCALL libc_ns_get32)(u_char const *srcptr) {
	return __hybrid_unaligned_getbe32(srcptr);
}
#include <hybrid/__byteswap.h>
#include <hybrid/__unaligned.h>
INTERN ATTR_SECTION(".text.crt.net.nameser") ATTR_OUT(2) void
NOTHROW_NCX(LIBCCALL libc_ns_put16)(u_int val,
                                    u_char *destptr) {
	__hybrid_unaligned_setbe16(destptr, val);
}
#include <hybrid/__byteswap.h>
#include <hybrid/__unaligned.h>
INTERN ATTR_SECTION(".text.crt.net.nameser") ATTR_OUT(2) void
NOTHROW_NCX(LIBCCALL libc_ns_put32)(u_long val,
                                    u_char *destptr) {
	__hybrid_unaligned_setbe32(destptr, val);
}
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_ns_name_compress)(char const *srcbuf,
                                            u_char *dstbuf,
                                            size_t dstbufsize,
                                            u_char const **d,
                                            u_char const **e) {
	COMPILER_IMPURE();
	(void)srcbuf;
	(void)dstbuf;
	(void)dstbufsize;
	(void)d;
	(void)e;
	/* TODO */
	return 0;
}
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__
DEFINE_INTERN_ALIAS_P(libc_dn_comp,libc_ns_name_compress,,int,NOTHROW_NCX,LIBCCALL,(char const *srcbuf, u_char *dstbuf, int dstbufsize, u_char **d, u_char **e),(srcbuf,dstbuf,dstbufsize,d,e));
#else /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ */
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_dn_comp)(char const *srcbuf,
                                   u_char *dstbuf,
                                   int dstbufsize,
                                   u_char **d,
                                   u_char **e) {
	return libc_ns_name_compress(srcbuf, dstbuf, (size_t)dstbufsize, (u_char const **)d, (u_char const **)e);
}
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(ns_get16,libc_ns_get16,ATTR_PURE WUNUSED ATTR_IN(1),u_int,NOTHROW_NCX,LIBCCALL,(u_char const *srcptr),(srcptr));
DEFINE_PUBLIC_ALIAS_P(ns_get32,libc_ns_get32,ATTR_PURE WUNUSED ATTR_IN(1),u_long,NOTHROW_NCX,LIBCCALL,(u_char const *srcptr),(srcptr));
DEFINE_PUBLIC_ALIAS_P_VOID(putshort,libc_ns_put16,ATTR_OUT(2),NOTHROW_NCX,LIBCCALL,(u_int val, u_char *destptr),(val,destptr));
DEFINE_PUBLIC_ALIAS_P_VOID(__putshort,libc_ns_put16,ATTR_OUT(2),NOTHROW_NCX,LIBCCALL,(u_int val, u_char *destptr),(val,destptr));
DEFINE_PUBLIC_ALIAS_P_VOID(ns_put16,libc_ns_put16,ATTR_OUT(2),NOTHROW_NCX,LIBCCALL,(u_int val, u_char *destptr),(val,destptr));
DEFINE_PUBLIC_ALIAS_P_VOID(putlong,libc_ns_put32,ATTR_OUT(2),NOTHROW_NCX,LIBCCALL,(u_long val, u_char *destptr),(val,destptr));
DEFINE_PUBLIC_ALIAS_P_VOID(__putlong,libc_ns_put32,ATTR_OUT(2),NOTHROW_NCX,LIBCCALL,(u_long val, u_char *destptr),(val,destptr));
DEFINE_PUBLIC_ALIAS_P_VOID(ns_put32,libc_ns_put32,ATTR_OUT(2),NOTHROW_NCX,LIBCCALL,(u_long val, u_char *destptr),(val,destptr));
DEFINE_PUBLIC_ALIAS_P(ns_name_compress,libc_ns_name_compress,,int,NOTHROW_NCX,LIBCCALL,(char const *srcbuf, u_char *dstbuf, size_t dstbufsize, u_char const **d, u_char const **e),(srcbuf,dstbuf,dstbufsize,d,e));
DEFINE_PUBLIC_ALIAS_P(__dn_comp,libc_dn_comp,,int,NOTHROW_NCX,LIBCCALL,(char const *srcbuf, u_char *dstbuf, int dstbufsize, u_char **d, u_char **e),(srcbuf,dstbuf,dstbufsize,d,e));
DEFINE_PUBLIC_ALIAS_P(dn_comp,libc_dn_comp,,int,NOTHROW_NCX,LIBCCALL,(char const *srcbuf, u_char *dstbuf, int dstbufsize, u_char **d, u_char **e),(srcbuf,dstbuf,dstbufsize,d,e));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_ARPA_NAMESER_C */
