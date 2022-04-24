/* HASH CRC-32:0x9732ca91 */
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
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc___memcpy_chk)(void *__restrict dst,
                                        void const *__restrict src,
                                        size_t n_bytes,
                                        size_t dst_objsize) {
	__ssp_chk_dstbuf("memcpy", dst, n_bytes, dst_objsize);
	return libc_memcpy(dst, src, n_bytes);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc___memmove_chk)(void *dst,
                                         void const *src,
                                         size_t n_bytes,
                                         size_t dst_objsize) {
	__ssp_chk_dstbuf("memmove", dst, n_bytes, dst_objsize);
	return libc_memmove(dst, src, n_bytes);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc___memset_chk)(void *__restrict dst,
                                        int byte,
                                        size_t n_bytes,
                                        size_t dst_objsize) {
	__ssp_chk_dstbuf("memset", dst, n_bytes, dst_objsize);
	return libc_memset(dst, byte, n_bytes);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc___strcat_chk)(char *__restrict dst,
                                        char const *__restrict src,
                                        size_t dst_objsize) {
	(void)dst_objsize; /* TODO */;
	return libc_strcat(dst, src);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc___strcpy_chk)(char *__restrict dst,
                                        char const *__restrict src,
                                        size_t dst_objsize) {
	(void)dst_objsize; /* TODO */;
	return libc_strcpy(dst, src);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc___strncat_chk)(char *__restrict dst,
                                         char const *__restrict src,
                                         size_t buflen,
                                         size_t dst_objsize) {
	(void)dst_objsize; /* TODO */;
	return libc_strncat(dst, src, buflen);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc___strncpy_chk)(char *__restrict dst,
                                         char const *__restrict src,
                                         size_t buflen,
                                         size_t dst_objsize) {
	(void)dst_objsize; /* TODO */;
	return libc_strncpy(dst, src, buflen);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc___mempcpy_chk)(void *__restrict dst,
                                         void const *__restrict src,
                                         size_t n_bytes,
                                         size_t dst_objsize) {
	__ssp_chk_dstbuf("mempcpy", dst, n_bytes, dst_objsize);
	return libc_mempcpy(dst, src, n_bytes);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc___stpcpy_chk)(char *__restrict dst,
                                        char const *__restrict src,
                                        size_t dst_objsize) {
	(void)dst_objsize; /* TODO */;
	return libc_stpcpy(dst, src);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc___stpncpy_chk)(char *__restrict dst,
                                         char const *__restrict src,
                                         size_t buflen,
                                         size_t dst_objsize) {
	(void)dst_objsize; /* TODO */;
	return libc_stpncpy(dst, src, buflen);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc___mempmove_chk)(void *dst,
                                          void const *src,
                                          size_t n_bytes,
                                          size_t dst_objsize) {
	__ssp_chk_dstbuf("mempmove", dst, n_bytes, dst_objsize);
	return libc_mempmove(dst, src, n_bytes);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *
NOTHROW_NCX(LIBCCALL libc___mempset_chk)(void *__restrict dst,
                                         int byte,
                                         size_t n_bytes,
                                         size_t dst_objsize) {
	__ssp_chk_dstbuf("mempset", dst, n_bytes, dst_objsize);
	return libc_mempset(dst, byte, n_bytes);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc___memmoveup_chk)(void *dst,
                                           void const *src,
                                           size_t n_bytes,
                                           size_t dst_objsize) {
	__ssp_chk_dstbuf("memmoveup", dst, n_bytes, dst_objsize);
	return libc_memmoveup(dst, src, n_bytes);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc___memmovedown_chk)(void *dst,
                                             void const *src,
                                             size_t n_bytes,
                                             size_t dst_objsize) {
	__ssp_chk_dstbuf("memmovedown", dst, n_bytes, dst_objsize);
	return libc_memmovedown(dst, src, n_bytes);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc___mempmoveup_chk)(void *dst,
                                            void const *src,
                                            size_t n_bytes,
                                            size_t dst_objsize) {
	__ssp_chk_dstbuf("mempmoveup", dst, n_bytes, dst_objsize);
	return libc_mempmoveup(dst, src, n_bytes);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc___mempmovedown_chk)(void *dst,
                                              void const *src,
                                              size_t n_bytes,
                                              size_t dst_objsize) {
	__ssp_chk_dstbuf("mempmovedown", dst, n_bytes, dst_objsize);
	return libc_mempmovedown(dst, src, n_bytes);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc___memcpyc_chk)(void *__restrict dst,
                                         void const *__restrict src,
                                         size_t elem_count,
                                         size_t elem_size,
                                         size_t dst_objsize) {
	__ssp_chk_dstbuf("memcpyc", dst, elem_count * elem_size, dst_objsize);
	return libc_memcpyc(dst, src, elem_count, elem_size);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc___memmovec_chk)(void *dst,
                                          void const *src,
                                          size_t elem_count,
                                          size_t elem_size,
                                          size_t dst_objsize) {
	__ssp_chk_dstbuf("memmovec", dst, elem_count * elem_size, dst_objsize);
	return libc_memmovec(dst, src, elem_count, elem_size);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc___mempcpyc_chk)(void *__restrict dst,
                                          void const *__restrict src,
                                          size_t elem_count,
                                          size_t elem_size,
                                          size_t dst_objsize) {
	__ssp_chk_dstbuf("mempcpyc", dst, elem_count * elem_size, dst_objsize);
	return libc_mempcpyc(dst, src, elem_count, elem_size);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc___mempmovec_chk)(void *dst,
                                           void const *src,
                                           size_t elem_count,
                                           size_t elem_size,
                                           size_t dst_objsize) {
	__ssp_chk_dstbuf("mempmovec", dst, elem_count * elem_size, dst_objsize);
	return libc_mempmovec(dst, src, elem_count, elem_size);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc___memmoveupc_chk)(void *dst,
                                            void const *src,
                                            size_t elem_count,
                                            size_t elem_size,
                                            size_t dst_objsize) {
	__ssp_chk_dstbuf("memmoveupc", dst, elem_count * elem_size, dst_objsize);
	return libc_memmoveupc(dst, src, elem_count, elem_size);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc___memmovedownc_chk)(void *dst,
                                              void const *src,
                                              size_t elem_count,
                                              size_t elem_size,
                                              size_t dst_objsize) {
	__ssp_chk_dstbuf("memmovedownc", dst, elem_count * elem_size, dst_objsize);
	return libc_memmovedownc(dst, src, elem_count, elem_size);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc___mempmoveupc_chk)(void *dst,
                                             void const *src,
                                             size_t elem_count,
                                             size_t elem_size,
                                             size_t dst_objsize) {
	__ssp_chk_dstbuf("mempmoveupc", dst, elem_count * elem_size, dst_objsize);
	return libc_mempmoveupc(dst, src, elem_count, elem_size);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBCCALL libc___mempmovedownc_chk)(void *dst,
                                               void const *src,
                                               size_t elem_count,
                                               size_t elem_size,
                                               size_t dst_objsize) {
	__ssp_chk_dstbuf("mempmovedownc", dst, elem_count * elem_size, dst_objsize);
	return libc_mempmovedownc(dst, src, elem_count, elem_size);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBCCALL libc___memcpyw_chk)(void *__restrict dst,
                                         void const *__restrict src,
                                         size_t n_words,
                                         size_t dst_objsize) {
	__ssp_chk_dstbuf("memcpyw", dst, n_words * 2, dst_objsize);
	return libc_memcpyw(dst, src, n_words);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBCCALL libc___mempcpyw_chk)(void *__restrict dst,
                                          void const *__restrict src,
                                          size_t n_words,
                                          size_t dst_objsize) {
	__ssp_chk_dstbuf("mempcpyw", dst, n_words * 2, dst_objsize);
	return libc_mempcpyw(dst, src, n_words);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBCCALL libc___memmovew_chk)(void *dst,
                                          void const *src,
                                          size_t n_words,
                                          size_t dst_objsize) {
	__ssp_chk_dstbuf("memmovew", dst, n_words * 2, dst_objsize);
	return libc_memmovew(dst, src, n_words);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBCCALL libc___memcpyl_chk)(void *__restrict dst,
                                         void const *__restrict src,
                                         size_t n_dwords,
                                         size_t dst_objsize) {
	__ssp_chk_dstbuf("memcpyl", dst, n_dwords * 4, dst_objsize);
	return libc_memcpyl(dst, src, n_dwords);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBCCALL libc___mempcpyl_chk)(void *__restrict dst,
                                          void const *__restrict src,
                                          size_t n_dwords,
                                          size_t dst_objsize) {
	__ssp_chk_dstbuf("mempcpyl", dst, n_dwords * 4, dst_objsize);
	return libc_mempcpyl(dst, src, n_dwords);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBCCALL libc___memmovel_chk)(void *dst,
                                          void const *src,
                                          size_t n_dwords,
                                          size_t dst_objsize) {
	__ssp_chk_dstbuf("memmovel", dst, n_dwords * 4, dst_objsize);
	return libc_memmovel(dst, src, n_dwords);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBCCALL libc___mempmovew_chk)(void *dst,
                                           void const *src,
                                           size_t n_words,
                                           size_t dst_objsize) {
	__ssp_chk_dstbuf("mempmovew", dst, n_words * 2, dst_objsize);
	return libc_mempmovew(dst, src, n_words);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBCCALL libc___mempmovel_chk)(void *dst,
                                           void const *src,
                                           size_t n_dwords,
                                           size_t dst_objsize) {
	__ssp_chk_dstbuf("mempmovel", dst, n_dwords * 4, dst_objsize);
	return libc_mempmovel(dst, src, n_dwords);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBCCALL libc___memsetw_chk)(void *__restrict dst,
                                         uint16_t word,
                                         size_t n_words,
                                         size_t dst_objsize) {
	__ssp_chk_dstbuf("memsetw", dst, n_words * 2, dst_objsize);
	return libc_memsetw(dst, word, n_words);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBCCALL libc___mempsetw_chk)(void *__restrict dst,
                                          uint16_t word,
                                          size_t n_words,
                                          size_t dst_objsize) {
	__ssp_chk_dstbuf("mempsetw", dst, n_words * 2, dst_objsize);
	return libc_mempsetw(dst, word, n_words);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBCCALL libc___memsetl_chk)(void *__restrict dst,
                                         uint32_t dword,
                                         size_t n_dwords,
                                         size_t dst_objsize) {
	__ssp_chk_dstbuf("memsetl", dst, n_dwords * 4, dst_objsize);
	return libc_memsetl(dst, dword, n_dwords);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBCCALL libc___mempsetl_chk)(void *__restrict dst,
                                          uint32_t dword,
                                          size_t n_dwords,
                                          size_t dst_objsize) {
	__ssp_chk_dstbuf("mempsetl", dst, n_dwords * 4, dst_objsize);
	return libc_mempsetl(dst, dword, n_dwords);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBCCALL libc___memmoveupw_chk)(void *dst,
                                            void const *src,
                                            size_t n_words,
                                            size_t dst_objsize) {
	__ssp_chk_dstbuf("memmoveupw", dst, n_words * 2, dst_objsize);
	return libc_memmoveupw(dst, src, n_words);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBCCALL libc___memmovedownw_chk)(void *dst,
                                              void const *src,
                                              size_t n_words,
                                              size_t dst_objsize) {
	__ssp_chk_dstbuf("memmovedownw", dst, n_words * 2, dst_objsize);
	return libc_memmovedownw(dst, src, n_words);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBCCALL libc___memmoveupl_chk)(void *dst,
                                            void const *src,
                                            size_t n_dwords,
                                            size_t dst_objsize) {
	__ssp_chk_dstbuf("memmoveupl", dst, n_dwords * 4, dst_objsize);
	return libc_memmoveupl(dst, src, n_dwords);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBCCALL libc___memmovedownl_chk)(void *dst,
                                              void const *src,
                                              size_t n_dwords,
                                              size_t dst_objsize) {
	__ssp_chk_dstbuf("memmovedownl", dst, n_dwords * 4, dst_objsize);
	return libc_memmovedownl(dst, src, n_dwords);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBCCALL libc___mempmoveupw_chk)(void *dst,
                                             void const *src,
                                             size_t n_words,
                                             size_t dst_objsize) {
	__ssp_chk_dstbuf("mempmoveupw", dst, n_words * 2, dst_objsize);
	return libc_mempmoveupw(dst, src, n_words);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBCCALL libc___mempmovedownw_chk)(void *dst,
                                               void const *src,
                                               size_t n_words,
                                               size_t dst_objsize) {
	__ssp_chk_dstbuf("mempmovedownw", dst, n_words * 2, dst_objsize);
	return libc_mempmovedownw(dst, src, n_words);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBCCALL libc___mempmoveupl_chk)(void *dst,
                                             void const *src,
                                             size_t n_dwords,
                                             size_t dst_objsize) {
	__ssp_chk_dstbuf("mempmoveupl", dst, n_dwords * 4, dst_objsize);
	return libc_mempmoveupl(dst, src, n_dwords);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBCCALL libc___mempmovedownl_chk)(void *dst,
                                               void const *src,
                                               size_t n_dwords,
                                               size_t dst_objsize) {
	__ssp_chk_dstbuf("mempmovedownl", dst, n_dwords * 4, dst_objsize);
	return libc_mempmovedownl(dst, src, n_dwords);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBCCALL libc___memcpyq_chk)(void *__restrict dst,
                                         void const *__restrict src,
                                         size_t n_qwords,
                                         size_t dst_objsize) {
	__ssp_chk_dstbuf("memcpyq", dst, n_qwords * 8, dst_objsize);
	return libc_memcpyq(dst, src, n_qwords);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBCCALL libc___mempcpyq_chk)(void *__restrict dst,
                                          void const *__restrict src,
                                          size_t n_qwords,
                                          size_t dst_objsize) {
	__ssp_chk_dstbuf("mempcpyq", dst, n_qwords * 8, dst_objsize);
	return libc_mempcpyq(dst, src, n_qwords);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBCCALL libc___memmoveq_chk)(void *dst,
                                          void const *src,
                                          size_t n_qwords,
                                          size_t dst_objsize) {
	__ssp_chk_dstbuf("memmoveq", dst, n_qwords * 8, dst_objsize);
	return libc_memmoveq(dst, src, n_qwords);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBCCALL libc___mempmoveq_chk)(void *__restrict dst,
                                           void const *__restrict src,
                                           size_t n_qwords,
                                           size_t dst_objsize) {
	__ssp_chk_dstbuf("mempmoveq", dst, n_qwords * 8, dst_objsize);
	return libc_mempmoveq(dst, src, n_qwords);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBCCALL libc___memsetq_chk)(void *__restrict dst,
                                         uint64_t qword,
                                         size_t n_qwords,
                                         size_t dst_objsize) {
	__ssp_chk_dstbuf("memsetq", dst, n_qwords * 8, dst_objsize);
	return libc_memsetq(dst, qword, n_qwords);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBCCALL libc___mempsetq_chk)(void *__restrict dst,
                                          uint64_t qword,
                                          size_t n_qwords,
                                          size_t dst_objsize) {
	__ssp_chk_dstbuf("mempsetq", dst, n_qwords * 8, dst_objsize);
	return libc_mempsetq(dst, qword, n_qwords);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBCCALL libc___memmoveupq_chk)(void *dst,
                                            void const *src,
                                            size_t n_qwords,
                                            size_t dst_objsize) {
	__ssp_chk_dstbuf("memmoveupq", dst, n_qwords * 8, dst_objsize);
	return libc_memmoveupq(dst, src, n_qwords);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBCCALL libc___memmovedownq_chk)(void *dst,
                                              void const *src,
                                              size_t n_qwords,
                                              size_t dst_objsize) {
	__ssp_chk_dstbuf("memmovedownq", dst, n_qwords * 8, dst_objsize);
	return libc_memmovedownq(dst, src, n_qwords);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBCCALL libc___mempmoveupq_chk)(void *__restrict dst,
                                             void const *__restrict src,
                                             size_t n_qwords,
                                             size_t dst_objsize) {
	__ssp_chk_dstbuf("mempmoveupq", dst, n_qwords * 8, dst_objsize);
	return libc_mempmoveupq(dst, src, n_qwords);
}
#include <ssp/chk.h>
INTERN ATTR_SECTION(".text.crt.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBCCALL libc___mempmovedownq_chk)(void *__restrict dst,
                                               void const *__restrict src,
                                               size_t n_qwords,
                                               size_t dst_objsize) {
	__ssp_chk_dstbuf("mempmovedownq", dst, n_qwords * 8, dst_objsize);
	return libc_mempmovedownq(dst, src, n_qwords);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__memcpy_chk, libc___memcpy_chk);
DEFINE_PUBLIC_ALIAS(__memmove_chk, libc___memmove_chk);
DEFINE_PUBLIC_ALIAS(__memset_chk, libc___memset_chk);
DEFINE_PUBLIC_ALIAS(__strcat_chk, libc___strcat_chk);
DEFINE_PUBLIC_ALIAS(__strcpy_chk, libc___strcpy_chk);
DEFINE_PUBLIC_ALIAS(__strncat_chk, libc___strncat_chk);
DEFINE_PUBLIC_ALIAS(__strncpy_chk, libc___strncpy_chk);
DEFINE_PUBLIC_ALIAS(__mempcpy_chk, libc___mempcpy_chk);
DEFINE_PUBLIC_ALIAS(__stpcpy_chk, libc___stpcpy_chk);
DEFINE_PUBLIC_ALIAS(__stpncpy_chk, libc___stpncpy_chk);
DEFINE_PUBLIC_ALIAS(__mempmove_chk, libc___mempmove_chk);
DEFINE_PUBLIC_ALIAS(__mempset_chk, libc___mempset_chk);
DEFINE_PUBLIC_ALIAS(__memmoveup_chk, libc___memmoveup_chk);
DEFINE_PUBLIC_ALIAS(__memmovedown_chk, libc___memmovedown_chk);
DEFINE_PUBLIC_ALIAS(__mempmoveup_chk, libc___mempmoveup_chk);
DEFINE_PUBLIC_ALIAS(__mempmovedown_chk, libc___mempmovedown_chk);
DEFINE_PUBLIC_ALIAS(__memcpyc_chk, libc___memcpyc_chk);
DEFINE_PUBLIC_ALIAS(__memmovec_chk, libc___memmovec_chk);
DEFINE_PUBLIC_ALIAS(__mempcpyc_chk, libc___mempcpyc_chk);
DEFINE_PUBLIC_ALIAS(__mempmovec_chk, libc___mempmovec_chk);
DEFINE_PUBLIC_ALIAS(__memmoveupc_chk, libc___memmoveupc_chk);
DEFINE_PUBLIC_ALIAS(__memmovedownc_chk, libc___memmovedownc_chk);
DEFINE_PUBLIC_ALIAS(__mempmoveupc_chk, libc___mempmoveupc_chk);
DEFINE_PUBLIC_ALIAS(__mempmovedownc_chk, libc___mempmovedownc_chk);
DEFINE_PUBLIC_ALIAS(__memcpyw_chk, libc___memcpyw_chk);
DEFINE_PUBLIC_ALIAS(__mempcpyw_chk, libc___mempcpyw_chk);
DEFINE_PUBLIC_ALIAS(__memmovew_chk, libc___memmovew_chk);
DEFINE_PUBLIC_ALIAS(__memcpyl_chk, libc___memcpyl_chk);
DEFINE_PUBLIC_ALIAS(__mempcpyl_chk, libc___mempcpyl_chk);
DEFINE_PUBLIC_ALIAS(__memmovel_chk, libc___memmovel_chk);
DEFINE_PUBLIC_ALIAS(__mempmovew_chk, libc___mempmovew_chk);
DEFINE_PUBLIC_ALIAS(__mempmovel_chk, libc___mempmovel_chk);
DEFINE_PUBLIC_ALIAS(__memsetw_chk, libc___memsetw_chk);
DEFINE_PUBLIC_ALIAS(__mempsetw_chk, libc___mempsetw_chk);
DEFINE_PUBLIC_ALIAS(__memsetl_chk, libc___memsetl_chk);
DEFINE_PUBLIC_ALIAS(__mempsetl_chk, libc___mempsetl_chk);
DEFINE_PUBLIC_ALIAS(__memmoveupw_chk, libc___memmoveupw_chk);
DEFINE_PUBLIC_ALIAS(__memmovedownw_chk, libc___memmovedownw_chk);
DEFINE_PUBLIC_ALIAS(__memmoveupl_chk, libc___memmoveupl_chk);
DEFINE_PUBLIC_ALIAS(__memmovedownl_chk, libc___memmovedownl_chk);
DEFINE_PUBLIC_ALIAS(__mempmoveupw_chk, libc___mempmoveupw_chk);
DEFINE_PUBLIC_ALIAS(__mempmovedownw_chk, libc___mempmovedownw_chk);
DEFINE_PUBLIC_ALIAS(__mempmoveupl_chk, libc___mempmoveupl_chk);
DEFINE_PUBLIC_ALIAS(__mempmovedownl_chk, libc___mempmovedownl_chk);
DEFINE_PUBLIC_ALIAS(__memcpyq_chk, libc___memcpyq_chk);
DEFINE_PUBLIC_ALIAS(__mempcpyq_chk, libc___mempcpyq_chk);
DEFINE_PUBLIC_ALIAS(__memmoveq_chk, libc___memmoveq_chk);
DEFINE_PUBLIC_ALIAS(__mempmoveq_chk, libc___mempmoveq_chk);
DEFINE_PUBLIC_ALIAS(__memsetq_chk, libc___memsetq_chk);
DEFINE_PUBLIC_ALIAS(__mempsetq_chk, libc___mempsetq_chk);
DEFINE_PUBLIC_ALIAS(__memmoveupq_chk, libc___memmoveupq_chk);
DEFINE_PUBLIC_ALIAS(__memmovedownq_chk, libc___memmovedownq_chk);
DEFINE_PUBLIC_ALIAS(__mempmoveupq_chk, libc___mempmoveupq_chk);
DEFINE_PUBLIC_ALIAS(__mempmovedownq_chk, libc___mempmovedownq_chk);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_SSP_STRING_C */
