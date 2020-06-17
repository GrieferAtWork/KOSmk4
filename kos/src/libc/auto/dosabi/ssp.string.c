/* HASH CRC-32:0xc07d876c */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SSP_STRING_C
#define GUARD_LIBC_AUTO_DOSABI_SSP_STRING_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../ssp.string.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd___memcpy_chk)(void *__restrict dst,
                                        void const *__restrict src,
                                        size_t n_bytes,
                                        size_t dst_objsize) {
	return libc___memcpy_chk(dst, src, n_bytes, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd___memmove_chk)(void *dst,
                                         void const *src,
                                         size_t n_bytes,
                                         size_t dst_objsize) {
	return libc___memmove_chk(dst, src, n_bytes, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *
NOTHROW_NCX(LIBDCALL libd___memset_chk)(void *__restrict dst,
                                        int byte,
                                        size_t n_bytes,
                                        size_t dst_objsize) {
	return libc___memset_chk(dst, byte, n_bytes, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd___strcat_chk)(char *__restrict dst,
                                        char const *__restrict src,
                                        size_t dst_objsize) {
	return libc___strcat_chk(dst, src, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd___strcpy_chk)(char *__restrict dst,
                                        char const *__restrict src,
                                        size_t dst_objsize) {
	return libc___strcpy_chk(dst, src, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd___strncat_chk)(char *__restrict dst,
                                         char const *__restrict src,
                                         size_t buflen,
                                         size_t dst_objsize) {
	return libc___strncat_chk(dst, src, buflen, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd___strncpy_chk)(char *__restrict dst,
                                         char const *__restrict src,
                                         size_t buflen,
                                         size_t dst_objsize) {
	return libc___strncpy_chk(dst, src, buflen, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd___mempcpy_chk)(void *__restrict dst,
                                         void const *__restrict src,
                                         size_t n_bytes,
                                         size_t dst_objsize) {
	return libc___mempcpy_chk(dst, src, n_bytes, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd___stpcpy_chk)(char *__restrict dst,
                                        char const *__restrict src,
                                        size_t dst_objsize) {
	return libc___stpcpy_chk(dst, src, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd___stpncpy_chk)(char *__restrict dst,
                                         char const *__restrict src,
                                         size_t buflen,
                                         size_t dst_objsize) {
	return libc___stpncpy_chk(dst, src, buflen, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd___mempmove_chk)(void *dst,
                                          void const *src,
                                          size_t n_bytes,
                                          size_t dst_objsize) {
	return libc___mempmove_chk(dst, src, n_bytes, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *
NOTHROW_NCX(LIBDCALL libd___mempset_chk)(void *__restrict dst,
                                         int byte,
                                         size_t n_bytes,
                                         size_t dst_objsize) {
	return libc___mempset_chk(dst, byte, n_bytes, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd___memmoveup_chk)(void *dst,
                                           void const *src,
                                           size_t n_bytes,
                                           size_t dst_objsize) {
	return libc___memmoveup_chk(dst, src, n_bytes, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd___memmovedown_chk)(void *dst,
                                             void const *src,
                                             size_t n_bytes,
                                             size_t dst_objsize) {
	return libc___memmovedown_chk(dst, src, n_bytes, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd___mempmoveup_chk)(void *dst,
                                            void const *src,
                                            size_t n_bytes,
                                            size_t dst_objsize) {
	return libc___mempmoveup_chk(dst, src, n_bytes, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd___mempmovedown_chk)(void *dst,
                                              void const *src,
                                              size_t n_bytes,
                                              size_t dst_objsize) {
	return libc___mempmovedown_chk(dst, src, n_bytes, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd___memcpyc_chk)(void *__restrict dst,
                                         void const *__restrict src,
                                         size_t elem_count,
                                         size_t elem_size,
                                         size_t dst_objsize) {
	return libc___memcpyc_chk(dst, src, elem_count, elem_size, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd___memmovec_chk)(void *dst,
                                          void const *src,
                                          size_t elem_count,
                                          size_t elem_size,
                                          size_t dst_objsize) {
	return libc___memmovec_chk(dst, src, elem_count, elem_size, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd___mempcpyc_chk)(void *__restrict dst,
                                          void const *__restrict src,
                                          size_t elem_count,
                                          size_t elem_size,
                                          size_t dst_objsize) {
	return libc___mempcpyc_chk(dst, src, elem_count, elem_size, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd___mempmovec_chk)(void *dst,
                                           void const *src,
                                           size_t elem_count,
                                           size_t elem_size,
                                           size_t dst_objsize) {
	return libc___mempmovec_chk(dst, src, elem_count, elem_size, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd___memmoveupc_chk)(void *dst,
                                            void const *src,
                                            size_t elem_count,
                                            size_t elem_size,
                                            size_t dst_objsize) {
	return libc___memmoveupc_chk(dst, src, elem_count, elem_size, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd___memmovedownc_chk)(void *dst,
                                              void const *src,
                                              size_t elem_count,
                                              size_t elem_size,
                                              size_t dst_objsize) {
	return libc___memmovedownc_chk(dst, src, elem_count, elem_size, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd___mempmoveupc_chk)(void *dst,
                                             void const *src,
                                             size_t elem_count,
                                             size_t elem_size,
                                             size_t dst_objsize) {
	return libc___mempmoveupc_chk(dst, src, elem_count, elem_size, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *
NOTHROW_NCX(LIBDCALL libd___mempmovedownc_chk)(void *dst,
                                               void const *src,
                                               size_t elem_count,
                                               size_t elem_size,
                                               size_t dst_objsize) {
	return libc___mempmovedownc_chk(dst, src, elem_count, elem_size, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBDCALL libd___memcpyw_chk)(void *__restrict dst,
                                         void const *__restrict src,
                                         size_t n_words,
                                         size_t dst_objsize) {
	return libc___memcpyw_chk(dst, src, n_words, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBDCALL libd___mempcpyw_chk)(void *__restrict dst,
                                          void const *__restrict src,
                                          size_t n_words,
                                          size_t dst_objsize) {
	return libc___mempcpyw_chk(dst, src, n_words, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBDCALL libd___memmovew_chk)(void *dst,
                                          void const *src,
                                          size_t n_words,
                                          size_t dst_objsize) {
	return libc___memmovew_chk(dst, src, n_words, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBDCALL libd___memcpyl_chk)(void *__restrict dst,
                                         void const *__restrict src,
                                         size_t n_dwords,
                                         size_t dst_objsize) {
	return libc___memcpyl_chk(dst, src, n_dwords, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBDCALL libd___mempcpyl_chk)(void *__restrict dst,
                                          void const *__restrict src,
                                          size_t n_dwords,
                                          size_t dst_objsize) {
	return libc___mempcpyl_chk(dst, src, n_dwords, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBDCALL libd___memmovel_chk)(void *dst,
                                          void const *src,
                                          size_t n_dwords,
                                          size_t dst_objsize) {
	return libc___memmovel_chk(dst, src, n_dwords, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBDCALL libd___mempmovew_chk)(void *dst,
                                           void const *src,
                                           size_t n_words,
                                           size_t dst_objsize) {
	return libc___mempmovew_chk(dst, src, n_words, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBDCALL libd___mempmovel_chk)(void *dst,
                                           void const *src,
                                           size_t n_dwords,
                                           size_t dst_objsize) {
	return libc___mempmovel_chk(dst, src, n_dwords, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBDCALL libd___memsetw_chk)(void *__restrict dst,
                                         uint16_t word,
                                         size_t n_words,
                                         size_t dst_objsize) {
	return libc___memsetw_chk(dst, word, n_words, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint16_t *
NOTHROW_NCX(LIBDCALL libd___mempsetw_chk)(void *__restrict dst,
                                          uint16_t word,
                                          size_t n_words,
                                          size_t dst_objsize) {
	return libc___mempsetw_chk(dst, word, n_words, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBDCALL libd___memsetl_chk)(void *__restrict dst,
                                         uint32_t dword,
                                         size_t n_dwords,
                                         size_t dst_objsize) {
	return libc___memsetl_chk(dst, dword, n_dwords, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint32_t *
NOTHROW_NCX(LIBDCALL libd___mempsetl_chk)(void *__restrict dst,
                                          uint32_t dword,
                                          size_t n_dwords,
                                          size_t dst_objsize) {
	return libc___mempsetl_chk(dst, dword, n_dwords, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBDCALL libd___memmoveupw_chk)(void *dst,
                                            void const *src,
                                            size_t n_words,
                                            size_t dst_objsize) {
	return libc___memmoveupw_chk(dst, src, n_words, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBDCALL libd___memmovedownw_chk)(void *dst,
                                              void const *src,
                                              size_t n_words,
                                              size_t dst_objsize) {
	return libc___memmovedownw_chk(dst, src, n_words, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBDCALL libd___memmoveupl_chk)(void *dst,
                                            void const *src,
                                            size_t n_dwords,
                                            size_t dst_objsize) {
	return libc___memmoveupl_chk(dst, src, n_dwords, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBDCALL libd___memmovedownl_chk)(void *dst,
                                              void const *src,
                                              size_t n_dwords,
                                              size_t dst_objsize) {
	return libc___memmovedownl_chk(dst, src, n_dwords, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBDCALL libd___mempmoveupw_chk)(void *dst,
                                             void const *src,
                                             size_t n_words,
                                             size_t dst_objsize) {
	return libc___mempmoveupw_chk(dst, src, n_words, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *
NOTHROW_NCX(LIBDCALL libd___mempmovedownw_chk)(void *dst,
                                               void const *src,
                                               size_t n_words,
                                               size_t dst_objsize) {
	return libc___mempmovedownw_chk(dst, src, n_words, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBDCALL libd___mempmoveupl_chk)(void *dst,
                                             void const *src,
                                             size_t n_dwords,
                                             size_t dst_objsize) {
	return libc___mempmoveupl_chk(dst, src, n_dwords, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *
NOTHROW_NCX(LIBDCALL libd___mempmovedownl_chk)(void *dst,
                                               void const *src,
                                               size_t n_dwords,
                                               size_t dst_objsize) {
	return libc___mempmovedownl_chk(dst, src, n_dwords, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBDCALL libd___memcpyq_chk)(void *__restrict dst,
                                         void const *__restrict src,
                                         size_t n_qwords,
                                         size_t dst_objsize) {
	return libc___memcpyq_chk(dst, src, n_qwords, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBDCALL libd___mempcpyq_chk)(void *__restrict dst,
                                          void const *__restrict src,
                                          size_t n_qwords,
                                          size_t dst_objsize) {
	return libc___mempcpyq_chk(dst, src, n_qwords, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBDCALL libd___memmoveq_chk)(void *dst,
                                          void const *src,
                                          size_t n_qwords,
                                          size_t dst_objsize) {
	return libc___memmoveq_chk(dst, src, n_qwords, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBDCALL libd___mempmoveq_chk)(void *__restrict dst,
                                           void const *__restrict src,
                                           size_t n_qwords,
                                           size_t dst_objsize) {
	return libc___mempmoveq_chk(dst, src, n_qwords, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBDCALL libd___memsetq_chk)(void *__restrict dst,
                                         uint64_t qword,
                                         size_t n_qwords,
                                         size_t dst_objsize) {
	return libc___memsetq_chk(dst, qword, n_qwords, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint64_t *
NOTHROW_NCX(LIBDCALL libd___mempsetq_chk)(void *__restrict dst,
                                          uint64_t qword,
                                          size_t n_qwords,
                                          size_t dst_objsize) {
	return libc___mempsetq_chk(dst, qword, n_qwords, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBDCALL libd___memmoveupq_chk)(void *dst,
                                            void const *src,
                                            size_t n_qwords,
                                            size_t dst_objsize) {
	return libc___memmoveupq_chk(dst, src, n_qwords, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBDCALL libd___memmovedownq_chk)(void *dst,
                                              void const *src,
                                              size_t n_qwords,
                                              size_t dst_objsize) {
	return libc___memmovedownq_chk(dst, src, n_qwords, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBDCALL libd___mempmoveupq_chk)(void *__restrict dst,
                                             void const *__restrict src,
                                             size_t n_qwords,
                                             size_t dst_objsize) {
	return libc___mempmoveupq_chk(dst, src, n_qwords, dst_objsize);
}
INTERN ATTR_SECTION(".text.crt.dos.ssp.string.memory") ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *
NOTHROW_NCX(LIBDCALL libd___mempmovedownq_chk)(void *__restrict dst,
                                               void const *__restrict src,
                                               size_t n_qwords,
                                               size_t dst_objsize) {
	return libc___mempmovedownq_chk(dst, src, n_qwords, dst_objsize);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$__memcpy_chk, libd___memcpy_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmove_chk, libd___memmove_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memset_chk, libd___memset_chk);
DEFINE_PUBLIC_ALIAS(DOS$__strcat_chk, libd___strcat_chk);
DEFINE_PUBLIC_ALIAS(DOS$__strcpy_chk, libd___strcpy_chk);
DEFINE_PUBLIC_ALIAS(DOS$__strncat_chk, libd___strncat_chk);
DEFINE_PUBLIC_ALIAS(DOS$__strncpy_chk, libd___strncpy_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempcpy_chk, libd___mempcpy_chk);
DEFINE_PUBLIC_ALIAS(DOS$__stpcpy_chk, libd___stpcpy_chk);
DEFINE_PUBLIC_ALIAS(DOS$__stpncpy_chk, libd___stpncpy_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmove_chk, libd___mempmove_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempset_chk, libd___mempset_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmoveup_chk, libd___memmoveup_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmovedown_chk, libd___memmovedown_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmoveup_chk, libd___mempmoveup_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmovedown_chk, libd___mempmovedown_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memcpyc_chk, libd___memcpyc_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmovec_chk, libd___memmovec_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempcpyc_chk, libd___mempcpyc_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmovec_chk, libd___mempmovec_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmoveupc_chk, libd___memmoveupc_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmovedownc_chk, libd___memmovedownc_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmoveupc_chk, libd___mempmoveupc_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmovedownc_chk, libd___mempmovedownc_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memcpyw_chk, libd___memcpyw_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempcpyw_chk, libd___mempcpyw_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmovew_chk, libd___memmovew_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memcpyl_chk, libd___memcpyl_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempcpyl_chk, libd___mempcpyl_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmovel_chk, libd___memmovel_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmovew_chk, libd___mempmovew_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmovel_chk, libd___mempmovel_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memsetw_chk, libd___memsetw_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempsetw_chk, libd___mempsetw_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memsetl_chk, libd___memsetl_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempsetl_chk, libd___mempsetl_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmoveupw_chk, libd___memmoveupw_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmovedownw_chk, libd___memmovedownw_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmoveupl_chk, libd___memmoveupl_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmovedownl_chk, libd___memmovedownl_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmoveupw_chk, libd___mempmoveupw_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmovedownw_chk, libd___mempmovedownw_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmoveupl_chk, libd___mempmoveupl_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmovedownl_chk, libd___mempmovedownl_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memcpyq_chk, libd___memcpyq_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempcpyq_chk, libd___mempcpyq_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmoveq_chk, libd___memmoveq_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmoveq_chk, libd___mempmoveq_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memsetq_chk, libd___memsetq_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempsetq_chk, libd___mempsetq_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmoveupq_chk, libd___memmoveupq_chk);
DEFINE_PUBLIC_ALIAS(DOS$__memmovedownq_chk, libd___memmovedownq_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmoveupq_chk, libd___mempmoveupq_chk);
DEFINE_PUBLIC_ALIAS(DOS$__mempmovedownq_chk, libd___mempmovedownq_chk);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SSP_STRING_C */
