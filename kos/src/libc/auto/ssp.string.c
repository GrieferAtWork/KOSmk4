/* HASH CRC-32:0x6ae0de66 */
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
#ifndef GUARD_LIBC_AUTO_SSP_STRING_C
#define GUARD_LIBC_AUTO_SSP_STRING_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "ssp.string.h"
#include "string.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memcpy_chk") void *
NOTHROW_NCX(LIBCCALL libc___memcpy_chk)(void *__restrict dst,
                                        void const *__restrict src,
                                        size_t n_bytes,
                                        size_t dst_objsize) {
#line 37 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memcpy", dst, n_bytes, dst_objsize);
	return memcpy(dst, src, n_bytes);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memmove_chk") void *
NOTHROW_NCX(LIBCCALL libc___memmove_chk)(void *dst,
                                         void const *src,
                                         size_t n_bytes,
                                         size_t dst_objsize) {
#line 38 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memmove", dst, n_bytes, dst_objsize);
	return memmove(dst, src, n_bytes);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memset_chk") void *
NOTHROW_NCX(LIBCCALL libc___memset_chk)(void *__restrict dst,
                                        int byte,
                                        size_t n_bytes,
                                        size_t dst_objsize) {
#line 39 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memset", dst, n_bytes, dst_objsize);
	return memset(dst, byte, n_bytes);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__strcat_chk") char *
NOTHROW_NCX(LIBCCALL libc___strcat_chk)(char *__restrict dst,
                                        char const *__restrict src,
                                        size_t dst_objsize) {
#line 40 "kos/src/libc/magic/ssp.string.c"
	(void)dst_objsize; /* TODO */;
	return libc_strcat(dst, src);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__strcpy_chk") char *
NOTHROW_NCX(LIBCCALL libc___strcpy_chk)(char *__restrict dst,
                                        char const *__restrict src,
                                        size_t dst_objsize) {
#line 41 "kos/src/libc/magic/ssp.string.c"
	(void)dst_objsize; /* TODO */;
	return libc_strcpy(dst, src);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__strncat_chk") char *
NOTHROW_NCX(LIBCCALL libc___strncat_chk)(char *__restrict dst,
                                         char const *__restrict src,
                                         size_t buflen,
                                         size_t dst_objsize) {
#line 42 "kos/src/libc/magic/ssp.string.c"
	(void)dst_objsize; /* TODO */;
	return libc_strncat(dst, src, buflen);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__strncpy_chk") char *
NOTHROW_NCX(LIBCCALL libc___strncpy_chk)(char *__restrict dst,
                                         char const *__restrict src,
                                         size_t buflen,
                                         size_t dst_objsize) {
#line 43 "kos/src/libc/magic/ssp.string.c"
	(void)dst_objsize; /* TODO */;
	return libc_strncpy(dst, src, buflen);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempcpy_chk") void *
NOTHROW_NCX(LIBCCALL libc___mempcpy_chk)(void *__restrict dst,
                                         void const *__restrict src,
                                         size_t n_bytes,
                                         size_t dst_objsize) {
#line 47 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempcpy", dst, n_bytes, dst_objsize);
	return mempcpy(dst, src, n_bytes);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__stpcpy_chk") char *
NOTHROW_NCX(LIBCCALL libc___stpcpy_chk)(char *__restrict dst,
                                        char const *__restrict src,
                                        size_t dst_objsize) {
#line 52 "kos/src/libc/magic/ssp.string.c"
	(void)dst_objsize; /* TODO */;
	return libc_stpcpy(dst, src);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__stpncpy_chk") char *
NOTHROW_NCX(LIBCCALL libc___stpncpy_chk)(char *__restrict dst,
                                         char const *__restrict src,
                                         size_t buflen,
                                         size_t dst_objsize) {
#line 53 "kos/src/libc/magic/ssp.string.c"
	(void)dst_objsize; /* TODO */;
	return libc_stpncpy(dst, src, buflen);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempmove_chk") void *
NOTHROW_NCX(LIBCCALL libc___mempmove_chk)(void *dst,
                                          void const *src,
                                          size_t n_bytes,
                                          size_t dst_objsize) {
#line 58 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempmove", dst, n_bytes, dst_objsize);
	return mempmove(dst, src, n_bytes);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempset_chk") void *
NOTHROW_NCX(LIBCCALL libc___mempset_chk)(void *__restrict dst,
                                         int byte,
                                         size_t n_bytes,
                                         size_t dst_objsize) {
#line 59 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempset", dst, n_bytes, dst_objsize);
	return mempset(dst, byte, n_bytes);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memmoveup_chk") void *
NOTHROW_NCX(LIBCCALL libc___memmoveup_chk)(void *dst,
                                           void const *src,
                                           size_t n_bytes,
                                           size_t dst_objsize) {
#line 60 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memmoveup", dst, n_bytes, dst_objsize);
	return memmoveup(dst, src, n_bytes);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memmovedown_chk") void *
NOTHROW_NCX(LIBCCALL libc___memmovedown_chk)(void *dst,
                                             void const *src,
                                             size_t n_bytes,
                                             size_t dst_objsize) {
#line 61 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memmovedown", dst, n_bytes, dst_objsize);
	return memmovedown(dst, src, n_bytes);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempmoveup_chk") void *
NOTHROW_NCX(LIBCCALL libc___mempmoveup_chk)(void *dst,
                                            void const *src,
                                            size_t n_bytes,
                                            size_t dst_objsize) {
#line 62 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempmoveup", dst, n_bytes, dst_objsize);
	return mempmoveup(dst, src, n_bytes);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempmovedown_chk") void *
NOTHROW_NCX(LIBCCALL libc___mempmovedown_chk)(void *dst,
                                              void const *src,
                                              size_t n_bytes,
                                              size_t dst_objsize) {
#line 63 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempmovedown", dst, n_bytes, dst_objsize);
	return mempmovedown(dst, src, n_bytes);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memcpyc_chk") void *
NOTHROW_NCX(LIBCCALL libc___memcpyc_chk)(void *__restrict dst,
                                         void const *__restrict src,
                                         size_t elem_count,
                                         size_t elem_size,
                                         size_t dst_objsize) {
#line 64 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memcpyc", dst, elem_count * elem_size, dst_objsize);
	return memcpyc(dst, src, elem_count, elem_size);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memmovec_chk") void *
NOTHROW_NCX(LIBCCALL libc___memmovec_chk)(void *dst,
                                          void const *src,
                                          size_t elem_count,
                                          size_t elem_size,
                                          size_t dst_objsize) {
#line 65 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memmovec", dst, elem_count * elem_size, dst_objsize);
	return memmovec(dst, src, elem_count, elem_size);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempcpyc_chk") void *
NOTHROW_NCX(LIBCCALL libc___mempcpyc_chk)(void *__restrict dst,
                                          void const *__restrict src,
                                          size_t elem_count,
                                          size_t elem_size,
                                          size_t dst_objsize) {
#line 66 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempcpyc", dst, elem_count * elem_size, dst_objsize);
	return mempcpyc(dst, src, elem_count, elem_size);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempmovec_chk") void *
NOTHROW_NCX(LIBCCALL libc___mempmovec_chk)(void *dst,
                                           void const *src,
                                           size_t elem_count,
                                           size_t elem_size,
                                           size_t dst_objsize) {
#line 67 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempmovec", dst, elem_count * elem_size, dst_objsize);
	return mempmovec(dst, src, elem_count, elem_size);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memmoveupc_chk") void *
NOTHROW_NCX(LIBCCALL libc___memmoveupc_chk)(void *dst,
                                            void const *src,
                                            size_t elem_count,
                                            size_t elem_size,
                                            size_t dst_objsize) {
#line 68 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memmoveupc", dst, elem_count * elem_size, dst_objsize);
	return memmoveupc(dst, src, elem_count, elem_size);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memmovedownc_chk") void *
NOTHROW_NCX(LIBCCALL libc___memmovedownc_chk)(void *dst,
                                              void const *src,
                                              size_t elem_count,
                                              size_t elem_size,
                                              size_t dst_objsize) {
#line 69 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memmovedownc", dst, elem_count * elem_size, dst_objsize);
	return memmovedownc(dst, src, elem_count, elem_size);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempmoveupc_chk") void *
NOTHROW_NCX(LIBCCALL libc___mempmoveupc_chk)(void *dst,
                                             void const *src,
                                             size_t elem_count,
                                             size_t elem_size,
                                             size_t dst_objsize) {
#line 70 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempmoveupc", dst, elem_count * elem_size, dst_objsize);
	return mempmoveupc(dst, src, elem_count, elem_size);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempmovedownc_chk") void *
NOTHROW_NCX(LIBCCALL libc___mempmovedownc_chk)(void *dst,
                                               void const *src,
                                               size_t elem_count,
                                               size_t elem_size,
                                               size_t dst_objsize) {
#line 71 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempmovedownc", dst, elem_count * elem_size, dst_objsize);
	return mempmovedownc(dst, src, elem_count, elem_size);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memcpyw_chk") uint16_t *
NOTHROW_NCX(LIBCCALL libc___memcpyw_chk)(/*aligned(2)*/ void *__restrict dst,
                                         /*aligned(2)*/ void const *__restrict src,
                                         size_t n_words,
                                         size_t dst_objsize) {
#line 76 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memcpyw", dst, n_words * 2, dst_objsize);
	return memcpyw(dst, src, n_words);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempcpyw_chk") uint16_t *
NOTHROW_NCX(LIBCCALL libc___mempcpyw_chk)(/*aligned(2)*/ void *__restrict dst,
                                          /*aligned(2)*/ void const *__restrict src,
                                          size_t n_words,
                                          size_t dst_objsize) {
#line 77 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempcpyw", dst, n_words * 2, dst_objsize);
	return mempcpyw(dst, src, n_words);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memmovew_chk") uint16_t *
NOTHROW_NCX(LIBCCALL libc___memmovew_chk)(/*aligned(2)*/ void *dst,
                                          /*aligned(2)*/ void const *src,
                                          size_t n_words,
                                          size_t dst_objsize) {
#line 78 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memmovew", dst, n_words * 2, dst_objsize);
	return memmovew(dst, src, n_words);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memcpyl_chk") uint32_t *
NOTHROW_NCX(LIBCCALL libc___memcpyl_chk)(/*aligned(4)*/ void *__restrict dst,
                                         /*aligned(4)*/ void const *__restrict src,
                                         size_t n_dwords,
                                         size_t dst_objsize) {
#line 79 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memcpyl", dst, n_dwords * 4, dst_objsize);
	return memcpyl(dst, src, n_dwords);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempcpyl_chk") uint32_t *
NOTHROW_NCX(LIBCCALL libc___mempcpyl_chk)(/*aligned(4)*/ void *__restrict dst,
                                          /*aligned(4)*/ void const *__restrict src,
                                          size_t n_dwords,
                                          size_t dst_objsize) {
#line 80 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempcpyl", dst, n_dwords * 4, dst_objsize);
	return mempcpyl(dst, src, n_dwords);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memmovel_chk") uint32_t *
NOTHROW_NCX(LIBCCALL libc___memmovel_chk)(/*aligned(4)*/ void *dst,
                                          /*aligned(4)*/ void const *src,
                                          size_t n_dwords,
                                          size_t dst_objsize) {
#line 81 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memmovel", dst, n_dwords * 4, dst_objsize);
	return memmovel(dst, src, n_dwords);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempmovew_chk") uint16_t *
NOTHROW_NCX(LIBCCALL libc___mempmovew_chk)(/*aligned(2)*/ void *dst,
                                           /*aligned(2)*/ void const *src,
                                           size_t n_words,
                                           size_t dst_objsize) {
#line 82 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempmovew", dst, n_words * 2, dst_objsize);
	return mempmovew(dst, src, n_words);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempmovel_chk") uint32_t *
NOTHROW_NCX(LIBCCALL libc___mempmovel_chk)(/*aligned(4)*/ void *dst,
                                           /*aligned(4)*/ void const *src,
                                           size_t n_dwords,
                                           size_t dst_objsize) {
#line 83 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempmovel", dst, n_dwords * 4, dst_objsize);
	return mempmovel(dst, src, n_dwords);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memsetw_chk") uint16_t *
NOTHROW_NCX(LIBCCALL libc___memsetw_chk)(/*aligned(2)*/ void *__restrict dst,
                                         uint16_t word,
                                         size_t n_words,
                                         size_t dst_objsize) {
#line 84 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memsetw", dst, n_words * 2, dst_objsize);
	return memsetw(dst, word, n_words);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempsetw_chk") uint16_t *
NOTHROW_NCX(LIBCCALL libc___mempsetw_chk)(/*aligned(2)*/ void *__restrict dst,
                                          uint16_t word,
                                          size_t n_words,
                                          size_t dst_objsize) {
#line 85 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempsetw", dst, n_words * 2, dst_objsize);
	return mempsetw(dst, word, n_words);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memsetl_chk") uint32_t *
NOTHROW_NCX(LIBCCALL libc___memsetl_chk)(/*aligned(4)*/ void *__restrict dst,
                                         uint32_t dword,
                                         size_t n_dwords,
                                         size_t dst_objsize) {
#line 86 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memsetl", dst, n_dwords * 4, dst_objsize);
	return memsetl(dst, dword, n_dwords);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempsetl_chk") uint32_t *
NOTHROW_NCX(LIBCCALL libc___mempsetl_chk)(/*aligned(4)*/ void *__restrict dst,
                                          uint32_t dword,
                                          size_t n_dwords,
                                          size_t dst_objsize) {
#line 87 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempsetl", dst, n_dwords * 4, dst_objsize);
	return mempsetl(dst, dword, n_dwords);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memmoveupw_chk") uint16_t *
NOTHROW_NCX(LIBCCALL libc___memmoveupw_chk)(/*aligned(2)*/ void *dst,
                                            /*aligned(2)*/ void const *src,
                                            size_t n_words,
                                            size_t dst_objsize) {
#line 89 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memmoveupw", dst, n_words * 2, dst_objsize);
	return memmoveupw(dst, src, n_words);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memmovedownw_chk") uint16_t *
NOTHROW_NCX(LIBCCALL libc___memmovedownw_chk)(/*aligned(2)*/ void *dst,
                                              /*aligned(2)*/ void const *src,
                                              size_t n_words,
                                              size_t dst_objsize) {
#line 90 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memmovedownw", dst, n_words * 2, dst_objsize);
	return memmovedownw(dst, src, n_words);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memmoveupl_chk") uint32_t *
NOTHROW_NCX(LIBCCALL libc___memmoveupl_chk)(/*aligned(4)*/ void *dst,
                                            /*aligned(4)*/ void const *src,
                                            size_t n_dwords,
                                            size_t dst_objsize) {
#line 91 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memmoveupl", dst, n_dwords * 4, dst_objsize);
	return memmoveupl(dst, src, n_dwords);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memmovedownl_chk") uint32_t *
NOTHROW_NCX(LIBCCALL libc___memmovedownl_chk)(/*aligned(4)*/ void *dst,
                                              /*aligned(4)*/ void const *src,
                                              size_t n_dwords,
                                              size_t dst_objsize) {
#line 92 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memmovedownl", dst, n_dwords * 4, dst_objsize);
	return memmovedownl(dst, src, n_dwords);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempmoveupw_chk") uint16_t *
NOTHROW_NCX(LIBCCALL libc___mempmoveupw_chk)(/*aligned(2)*/ void *dst,
                                             /*aligned(2)*/ void const *src,
                                             size_t n_words,
                                             size_t dst_objsize) {
#line 93 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempmoveupw", dst, n_words * 2, dst_objsize);
	return mempmoveupw(dst, src, n_words);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempmovedownw_chk") uint16_t *
NOTHROW_NCX(LIBCCALL libc___mempmovedownw_chk)(/*aligned(2)*/ void *dst,
                                               /*aligned(2)*/ void const *src,
                                               size_t n_words,
                                               size_t dst_objsize) {
#line 94 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempmovedownw", dst, n_words * 2, dst_objsize);
	return mempmovedownw(dst, src, n_words);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempmoveupl_chk") uint32_t *
NOTHROW_NCX(LIBCCALL libc___mempmoveupl_chk)(/*aligned(4)*/ void *dst,
                                             /*aligned(4)*/ void const *src,
                                             size_t n_dwords,
                                             size_t dst_objsize) {
#line 95 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempmoveupl", dst, n_dwords * 4, dst_objsize);
	return mempmoveupl(dst, src, n_dwords);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempmovedownl_chk") uint32_t *
NOTHROW_NCX(LIBCCALL libc___mempmovedownl_chk)(/*aligned(4)*/ void *dst,
                                               /*aligned(4)*/ void const *src,
                                               size_t n_dwords,
                                               size_t dst_objsize) {
#line 96 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempmovedownl", dst, n_dwords * 4, dst_objsize);
	return mempmovedownl(dst, src, n_dwords);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memcpyq_chk") uint64_t *
NOTHROW_NCX(LIBCCALL libc___memcpyq_chk)(/*aligned(8)*/ void *__restrict dst,
                                         /*aligned(8)*/ void const *__restrict src,
                                         size_t n_qwords,
                                         size_t dst_objsize) {
#line 99 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memcpyq", dst, n_qwords * 8, dst_objsize);
	return memcpyq(dst, src, n_qwords);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempcpyq_chk") uint64_t *
NOTHROW_NCX(LIBCCALL libc___mempcpyq_chk)(/*aligned(8)*/ void *__restrict dst,
                                          /*aligned(8)*/ void const *__restrict src,
                                          size_t n_qwords,
                                          size_t dst_objsize) {
#line 100 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempcpyq", dst, n_qwords * 8, dst_objsize);
	return mempcpyq(dst, src, n_qwords);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memmoveq_chk") uint64_t *
NOTHROW_NCX(LIBCCALL libc___memmoveq_chk)(/*aligned(8)*/ void *dst,
                                          /*aligned(8)*/ void const *src,
                                          size_t n_qwords,
                                          size_t dst_objsize) {
#line 101 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memmoveq", dst, n_qwords * 8, dst_objsize);
	return memmoveq(dst, src, n_qwords);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempmoveq_chk") uint64_t *
NOTHROW_NCX(LIBCCALL libc___mempmoveq_chk)(/*aligned(8)*/ void *__restrict dst,
                                           /*aligned(8)*/ void const *__restrict src,
                                           size_t n_qwords,
                                           size_t dst_objsize) {
#line 102 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempmoveq", dst, n_qwords * 8, dst_objsize);
	return mempmoveq(dst, src, n_qwords);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memsetq_chk") uint64_t *
NOTHROW_NCX(LIBCCALL libc___memsetq_chk)(/*aligned(8)*/ void *__restrict dst,
                                         uint64_t qword,
                                         size_t n_qwords,
                                         size_t dst_objsize) {
#line 103 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memsetq", dst, n_qwords * 8, dst_objsize);
	return memsetq(dst, qword, n_qwords);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempsetq_chk") uint64_t *
NOTHROW_NCX(LIBCCALL libc___mempsetq_chk)(/*aligned(8)*/ void *__restrict dst,
                                          uint64_t qword,
                                          size_t n_qwords,
                                          size_t dst_objsize) {
#line 104 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempsetq", dst, n_qwords * 8, dst_objsize);
	return mempsetq(dst, qword, n_qwords);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memmoveupq_chk") uint64_t *
NOTHROW_NCX(LIBCCALL libc___memmoveupq_chk)(/*aligned(8)*/ void *dst,
                                            /*aligned(8)*/ void const *src,
                                            size_t n_qwords,
                                            size_t dst_objsize) {
#line 106 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memmoveupq", dst, n_qwords * 8, dst_objsize);
	return memmoveupq(dst, src, n_qwords);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__memmovedownq_chk") uint64_t *
NOTHROW_NCX(LIBCCALL libc___memmovedownq_chk)(/*aligned(8)*/ void *dst,
                                              /*aligned(8)*/ void const *src,
                                              size_t n_qwords,
                                              size_t dst_objsize) {
#line 107 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("memmovedownq", dst, n_qwords * 8, dst_objsize);
	return memmovedownq(dst, src, n_qwords);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempmoveupq_chk") uint64_t *
NOTHROW_NCX(LIBCCALL libc___mempmoveupq_chk)(/*aligned(8)*/ void *__restrict dst,
                                             /*aligned(8)*/ void const *__restrict src,
                                             size_t n_qwords,
                                             size_t dst_objsize) {
#line 108 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempmoveupq", dst, n_qwords * 8, dst_objsize);
	return mempmoveupq(dst, src, n_qwords);
}


#include <ssp/chk.h>
INTERN ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.ssp.string.memory.__mempmovedownq_chk") uint64_t *
NOTHROW_NCX(LIBCCALL libc___mempmovedownq_chk)(/*aligned(8)*/ void *__restrict dst,
                                               /*aligned(8)*/ void const *__restrict src,
                                               size_t n_qwords,
                                               size_t dst_objsize) {
#line 109 "kos/src/libc/magic/ssp.string.c"
	__ssp_chk_dstbuf("mempmovedownq", dst, n_qwords * 8, dst_objsize);
	return mempmovedownq(dst, src, n_qwords);
}


#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(__memcpy_chk, libc___memcpy_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memmove_chk, libc___memmove_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memset_chk, libc___memset_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__strcat_chk, libc___strcat_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__strcpy_chk, libc___strcpy_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__strncat_chk, libc___strncat_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__strncpy_chk, libc___strncpy_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempcpy_chk, libc___mempcpy_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__stpcpy_chk, libc___stpcpy_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__stpncpy_chk, libc___stpncpy_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempmove_chk, libc___mempmove_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempset_chk, libc___mempset_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memmoveup_chk, libc___memmoveup_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memmovedown_chk, libc___memmovedown_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempmoveup_chk, libc___mempmoveup_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempmovedown_chk, libc___mempmovedown_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memcpyc_chk, libc___memcpyc_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memmovec_chk, libc___memmovec_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempcpyc_chk, libc___mempcpyc_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempmovec_chk, libc___mempmovec_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memmoveupc_chk, libc___memmoveupc_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memmovedownc_chk, libc___memmovedownc_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempmoveupc_chk, libc___mempmoveupc_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempmovedownc_chk, libc___mempmovedownc_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memcpyw_chk, libc___memcpyw_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempcpyw_chk, libc___mempcpyw_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memmovew_chk, libc___memmovew_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memcpyl_chk, libc___memcpyl_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempcpyl_chk, libc___mempcpyl_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memmovel_chk, libc___memmovel_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempmovew_chk, libc___mempmovew_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempmovel_chk, libc___mempmovel_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memsetw_chk, libc___memsetw_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempsetw_chk, libc___mempsetw_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memsetl_chk, libc___memsetl_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempsetl_chk, libc___mempsetl_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memmoveupw_chk, libc___memmoveupw_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memmovedownw_chk, libc___memmovedownw_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memmoveupl_chk, libc___memmoveupl_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memmovedownl_chk, libc___memmovedownl_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempmoveupw_chk, libc___mempmoveupw_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempmovedownw_chk, libc___mempmovedownw_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempmoveupl_chk, libc___mempmoveupl_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempmovedownl_chk, libc___mempmovedownl_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memcpyq_chk, libc___memcpyq_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempcpyq_chk, libc___mempcpyq_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memmoveq_chk, libc___memmoveq_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempmoveq_chk, libc___mempmoveq_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memsetq_chk, libc___memsetq_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempsetq_chk, libc___mempsetq_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memmoveupq_chk, libc___memmoveupq_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__memmovedownq_chk, libc___memmovedownq_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempmoveupq_chk, libc___mempmoveupq_chk);
DEFINE_PUBLIC_WEAK_ALIAS(__mempmovedownq_chk, libc___mempmovedownq_chk);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SSP_STRING_C */
