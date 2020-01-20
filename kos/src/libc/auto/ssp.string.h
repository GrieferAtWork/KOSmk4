/* HASH CRC-32:0x61bbe453 */
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
#ifndef GUARD_LIBC_AUTO_SSP_STRING_H
#define GUARD_LIBC_AUTO_SSP_STRING_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <ssp/string.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___memcpy_chk)(void *__restrict dst, void const *__restrict src, size_t n_bytes, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___memmove_chk)(void *dst, void const *src, size_t n_bytes, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc___memset_chk)(void *__restrict dst, int byte, size_t n_bytes, size_t dst_objsize);
INTDEF ATTR_LEAF NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc___strcat_chk)(char *__restrict dst, char const *__restrict src, size_t dst_objsize);
INTDEF ATTR_LEAF NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc___strcpy_chk)(char *__restrict dst, char const *__restrict src, size_t dst_objsize);
INTDEF ATTR_LEAF NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc___strncat_chk)(char *__restrict dst, char const *__restrict src, size_t buflen, size_t dst_objsize);
INTDEF ATTR_LEAF NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc___strncpy_chk)(char *__restrict dst, char const *__restrict src, size_t buflen, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___mempcpy_chk)(void *__restrict dst, void const *__restrict src, size_t n_bytes, size_t dst_objsize);
INTDEF ATTR_LEAF NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc___stpcpy_chk)(char *__restrict dst, char const *__restrict src, size_t dst_objsize);
INTDEF ATTR_LEAF NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc___stpncpy_chk)(char *__restrict dst, char const *__restrict src, size_t buflen, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___mempmove_chk)(void *dst, void const *src, size_t n_bytes, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc___mempset_chk)(void *__restrict dst, int byte, size_t n_bytes, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___memmoveup_chk)(void *dst, void const *src, size_t n_bytes, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___memmovedown_chk)(void *dst, void const *src, size_t n_bytes, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___mempmoveup_chk)(void *dst, void const *src, size_t n_bytes, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___mempmovedown_chk)(void *dst, void const *src, size_t n_bytes, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___memcpyc_chk)(void *__restrict dst, void const *__restrict src, size_t elem_count, size_t elem_size, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___memmovec_chk)(void *dst, void const *src, size_t elem_count, size_t elem_size, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___mempcpyc_chk)(void *__restrict dst, void const *__restrict src, size_t elem_count, size_t elem_size, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___mempmovec_chk)(void *dst, void const *src, size_t elem_count, size_t elem_size, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___memmoveupc_chk)(void *dst, void const *src, size_t elem_count, size_t elem_size, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___memmovedownc_chk)(void *dst, void const *src, size_t elem_count, size_t elem_size, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___mempmoveupc_chk)(void *dst, void const *src, size_t elem_count, size_t elem_size, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___mempmovedownc_chk)(void *dst, void const *src, size_t elem_count, size_t elem_size, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc___memcpyw_chk)(/*aligned(2)*/ void *__restrict dst, /*aligned(2)*/ void const *__restrict src, size_t n_words, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc___mempcpyw_chk)(/*aligned(2)*/ void *__restrict dst, /*aligned(2)*/ void const *__restrict src, size_t n_words, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc___memmovew_chk)(/*aligned(2)*/ void *dst, /*aligned(2)*/ void const *src, size_t n_words, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc___memcpyl_chk)(/*aligned(4)*/ void *__restrict dst, /*aligned(4)*/ void const *__restrict src, size_t n_dwords, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc___mempcpyl_chk)(/*aligned(4)*/ void *__restrict dst, /*aligned(4)*/ void const *__restrict src, size_t n_dwords, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc___memmovel_chk)(/*aligned(4)*/ void *dst, /*aligned(4)*/ void const *src, size_t n_dwords, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc___mempmovew_chk)(/*aligned(2)*/ void *dst, /*aligned(2)*/ void const *src, size_t n_words, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc___mempmovel_chk)(/*aligned(4)*/ void *dst, /*aligned(4)*/ void const *src, size_t n_dwords, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc___memsetw_chk)(/*aligned(2)*/ void *__restrict dst, uint16_t word, size_t n_words, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc___mempsetw_chk)(/*aligned(2)*/ void *__restrict dst, uint16_t word, size_t n_words, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc___memsetl_chk)(/*aligned(4)*/ void *__restrict dst, uint32_t dword, size_t n_dwords, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc___mempsetl_chk)(/*aligned(4)*/ void *__restrict dst, uint32_t dword, size_t n_dwords, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc___memmoveupw_chk)(/*aligned(2)*/ void *dst, /*aligned(2)*/ void const *src, size_t n_words, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc___memmovedownw_chk)(/*aligned(2)*/ void *dst, /*aligned(2)*/ void const *src, size_t n_words, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc___memmoveupl_chk)(/*aligned(4)*/ void *dst, /*aligned(4)*/ void const *src, size_t n_dwords, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc___memmovedownl_chk)(/*aligned(4)*/ void *dst, /*aligned(4)*/ void const *src, size_t n_dwords, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc___mempmoveupw_chk)(/*aligned(2)*/ void *dst, /*aligned(2)*/ void const *src, size_t n_words, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc___mempmovedownw_chk)(/*aligned(2)*/ void *dst, /*aligned(2)*/ void const *src, size_t n_words, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc___mempmoveupl_chk)(/*aligned(4)*/ void *dst, /*aligned(4)*/ void const *src, size_t n_dwords, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc___mempmovedownl_chk)(/*aligned(4)*/ void *dst, /*aligned(4)*/ void const *src, size_t n_dwords, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc___memcpyq_chk)(/*aligned(8)*/ void *__restrict dst, /*aligned(8)*/ void const *__restrict src, size_t n_qwords, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc___mempcpyq_chk)(/*aligned(8)*/ void *__restrict dst, /*aligned(8)*/ void const *__restrict src, size_t n_qwords, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc___memmoveq_chk)(/*aligned(8)*/ void *dst, /*aligned(8)*/ void const *src, size_t n_qwords, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc___mempmoveq_chk)(/*aligned(8)*/ void *__restrict dst, /*aligned(8)*/ void const *__restrict src, size_t n_qwords, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc___memsetq_chk)(/*aligned(8)*/ void *__restrict dst, uint64_t qword, size_t n_qwords, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc___mempsetq_chk)(/*aligned(8)*/ void *__restrict dst, uint64_t qword, size_t n_qwords, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc___memmoveupq_chk)(/*aligned(8)*/ void *dst, /*aligned(8)*/ void const *src, size_t n_qwords, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc___memmovedownq_chk)(/*aligned(8)*/ void *dst, /*aligned(8)*/ void const *src, size_t n_qwords, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc___mempmoveupq_chk)(/*aligned(8)*/ void *__restrict dst, /*aligned(8)*/ void const *__restrict src, size_t n_qwords, size_t dst_objsize);
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc___mempmovedownq_chk)(/*aligned(8)*/ void *__restrict dst, /*aligned(8)*/ void const *__restrict src, size_t n_qwords, size_t dst_objsize);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SSP_STRING_H */
