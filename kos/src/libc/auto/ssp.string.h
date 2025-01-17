/* HASH CRC-32:0x31e45d47 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
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

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd___memcpy_chk)(void *__restrict dst, void const *__restrict src, size_t n_bytes, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___memcpy_chk)(void *__restrict dst, void const *__restrict src, size_t n_bytes, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd___memmove_chk)(void *dst, void const *src, size_t n_bytes, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___memmove_chk)(void *dst, void const *src, size_t n_bytes, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *NOTHROW_NCX(LIBDCALL libd___memset_chk)(void *__restrict dst, int byte, size_t n_bytes, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc___memset_chk)(void *__restrict dst, int byte, size_t n_bytes, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBDCALL libd___strcat_chk)(char *__restrict dst, char const *__restrict src, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc___strcat_chk)(char *__restrict dst, char const *__restrict src, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBDCALL libd___strcpy_chk)(char *__restrict dst, char const *__restrict src, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc___strcpy_chk)(char *__restrict dst, char const *__restrict src, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBDCALL libd___strncat_chk)(char *__restrict dst, char const *__restrict src, size_t buflen, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc___strncat_chk)(char *__restrict dst, char const *__restrict src, size_t buflen, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBDCALL libd___strncpy_chk)(char *__restrict dst, char const *__restrict src, size_t buflen, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc___strncpy_chk)(char *__restrict dst, char const *__restrict src, size_t buflen, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd___mempcpy_chk)(void *__restrict dst, void const *__restrict src, size_t n_bytes, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___mempcpy_chk)(void *__restrict dst, void const *__restrict src, size_t n_bytes, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBDCALL libd___stpcpy_chk)(char *__restrict dst, char const *__restrict src, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc___stpcpy_chk)(char *__restrict dst, char const *__restrict src, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBDCALL libd___stpncpy_chk)(char *__restrict dst, char const *__restrict src, size_t buflen, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc___stpncpy_chk)(char *__restrict dst, char const *__restrict src, size_t buflen, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd___mempmove_chk)(void *dst, void const *src, size_t n_bytes, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___mempmove_chk)(void *dst, void const *src, size_t n_bytes, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *NOTHROW_NCX(LIBDCALL libd___mempset_chk)(void *__restrict dst, int byte, size_t n_bytes, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc___mempset_chk)(void *__restrict dst, int byte, size_t n_bytes, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd___memmoveup_chk)(void *dst, void const *src, size_t n_bytes, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___memmoveup_chk)(void *dst, void const *src, size_t n_bytes, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd___memmovedown_chk)(void *dst, void const *src, size_t n_bytes, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___memmovedown_chk)(void *dst, void const *src, size_t n_bytes, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd___mempmoveup_chk)(void *dst, void const *src, size_t n_bytes, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___mempmoveup_chk)(void *dst, void const *src, size_t n_bytes, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd___mempmovedown_chk)(void *dst, void const *src, size_t n_bytes, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___mempmovedown_chk)(void *dst, void const *src, size_t n_bytes, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd___memcpyc_chk)(void *__restrict dst, void const *__restrict src, size_t elem_count, size_t elem_size, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___memcpyc_chk)(void *__restrict dst, void const *__restrict src, size_t elem_count, size_t elem_size, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd___memmovec_chk)(void *dst, void const *src, size_t elem_count, size_t elem_size, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___memmovec_chk)(void *dst, void const *src, size_t elem_count, size_t elem_size, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd___mempcpyc_chk)(void *__restrict dst, void const *__restrict src, size_t elem_count, size_t elem_size, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___mempcpyc_chk)(void *__restrict dst, void const *__restrict src, size_t elem_count, size_t elem_size, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd___mempmovec_chk)(void *dst, void const *src, size_t elem_count, size_t elem_size, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___mempmovec_chk)(void *dst, void const *src, size_t elem_count, size_t elem_size, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd___memmoveupc_chk)(void *dst, void const *src, size_t elem_count, size_t elem_size, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___memmoveupc_chk)(void *dst, void const *src, size_t elem_count, size_t elem_size, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd___memmovedownc_chk)(void *dst, void const *src, size_t elem_count, size_t elem_size, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___memmovedownc_chk)(void *dst, void const *src, size_t elem_count, size_t elem_size, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd___mempmoveupc_chk)(void *dst, void const *src, size_t elem_count, size_t elem_size, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___mempmoveupc_chk)(void *dst, void const *src, size_t elem_count, size_t elem_size, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBDCALL libd___mempmovedownc_chk)(void *dst, void const *src, size_t elem_count, size_t elem_size, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) void *NOTHROW_NCX(LIBCCALL libc___mempmovedownc_chk)(void *dst, void const *src, size_t elem_count, size_t elem_size, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBDCALL libd___memcpyw_chk)(void *__restrict dst, void const *__restrict src, size_t n_words, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc___memcpyw_chk)(void *__restrict dst, void const *__restrict src, size_t n_words, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBDCALL libd___mempcpyw_chk)(void *__restrict dst, void const *__restrict src, size_t n_words, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc___mempcpyw_chk)(void *__restrict dst, void const *__restrict src, size_t n_words, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBDCALL libd___memmovew_chk)(void *dst, void const *src, size_t n_words, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc___memmovew_chk)(void *dst, void const *src, size_t n_words, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBDCALL libd___memcpyl_chk)(void *__restrict dst, void const *__restrict src, size_t n_dwords, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc___memcpyl_chk)(void *__restrict dst, void const *__restrict src, size_t n_dwords, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBDCALL libd___mempcpyl_chk)(void *__restrict dst, void const *__restrict src, size_t n_dwords, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc___mempcpyl_chk)(void *__restrict dst, void const *__restrict src, size_t n_dwords, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBDCALL libd___memmovel_chk)(void *dst, void const *src, size_t n_dwords, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc___memmovel_chk)(void *dst, void const *src, size_t n_dwords, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBDCALL libd___mempmovew_chk)(void *dst, void const *src, size_t n_words, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc___mempmovew_chk)(void *dst, void const *src, size_t n_words, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBDCALL libd___mempmovel_chk)(void *dst, void const *src, size_t n_dwords, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc___mempmovel_chk)(void *dst, void const *src, size_t n_dwords, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint16_t *NOTHROW_NCX(LIBDCALL libd___memsetw_chk)(void *__restrict dst, uint16_t word, size_t n_words, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc___memsetw_chk)(void *__restrict dst, uint16_t word, size_t n_words, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint16_t *NOTHROW_NCX(LIBDCALL libd___mempsetw_chk)(void *__restrict dst, uint16_t word, size_t n_words, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint16_t *NOTHROW_NCX(LIBCCALL libc___mempsetw_chk)(void *__restrict dst, uint16_t word, size_t n_words, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint32_t *NOTHROW_NCX(LIBDCALL libd___memsetl_chk)(void *__restrict dst, uint32_t dword, size_t n_dwords, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc___memsetl_chk)(void *__restrict dst, uint32_t dword, size_t n_dwords, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint32_t *NOTHROW_NCX(LIBDCALL libd___mempsetl_chk)(void *__restrict dst, uint32_t dword, size_t n_dwords, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint32_t *NOTHROW_NCX(LIBCCALL libc___mempsetl_chk)(void *__restrict dst, uint32_t dword, size_t n_dwords, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBDCALL libd___memmoveupw_chk)(void *dst, void const *src, size_t n_words, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc___memmoveupw_chk)(void *dst, void const *src, size_t n_words, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBDCALL libd___memmovedownw_chk)(void *dst, void const *src, size_t n_words, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc___memmovedownw_chk)(void *dst, void const *src, size_t n_words, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBDCALL libd___memmoveupl_chk)(void *dst, void const *src, size_t n_dwords, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc___memmoveupl_chk)(void *dst, void const *src, size_t n_dwords, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBDCALL libd___memmovedownl_chk)(void *dst, void const *src, size_t n_dwords, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc___memmovedownl_chk)(void *dst, void const *src, size_t n_dwords, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBDCALL libd___mempmoveupw_chk)(void *dst, void const *src, size_t n_words, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc___mempmoveupw_chk)(void *dst, void const *src, size_t n_words, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBDCALL libd___mempmovedownw_chk)(void *dst, void const *src, size_t n_words, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint16_t *NOTHROW_NCX(LIBCCALL libc___mempmovedownw_chk)(void *dst, void const *src, size_t n_words, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBDCALL libd___mempmoveupl_chk)(void *dst, void const *src, size_t n_dwords, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc___mempmoveupl_chk)(void *dst, void const *src, size_t n_dwords, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBDCALL libd___mempmovedownl_chk)(void *dst, void const *src, size_t n_dwords, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint32_t *NOTHROW_NCX(LIBCCALL libc___mempmovedownl_chk)(void *dst, void const *src, size_t n_dwords, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBDCALL libd___memcpyq_chk)(void *__restrict dst, void const *__restrict src, size_t n_qwords, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc___memcpyq_chk)(void *__restrict dst, void const *__restrict src, size_t n_qwords, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBDCALL libd___mempcpyq_chk)(void *__restrict dst, void const *__restrict src, size_t n_qwords, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc___mempcpyq_chk)(void *__restrict dst, void const *__restrict src, size_t n_qwords, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBDCALL libd___memmoveq_chk)(void *dst, void const *src, size_t n_qwords, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc___memmoveq_chk)(void *dst, void const *src, size_t n_qwords, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBDCALL libd___mempmoveq_chk)(void *__restrict dst, void const *__restrict src, size_t n_qwords, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc___mempmoveq_chk)(void *__restrict dst, void const *__restrict src, size_t n_qwords, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint64_t *NOTHROW_NCX(LIBDCALL libd___memsetq_chk)(void *__restrict dst, uint64_t qword, size_t n_qwords, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc___memsetq_chk)(void *__restrict dst, uint64_t qword, size_t n_qwords, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint64_t *NOTHROW_NCX(LIBDCALL libd___mempsetq_chk)(void *__restrict dst, uint64_t qword, size_t n_qwords, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1)) uint64_t *NOTHROW_NCX(LIBCCALL libc___mempsetq_chk)(void *__restrict dst, uint64_t qword, size_t n_qwords, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBDCALL libd___memmoveupq_chk)(void *dst, void const *src, size_t n_qwords, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc___memmoveupq_chk)(void *dst, void const *src, size_t n_qwords, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBDCALL libd___memmovedownq_chk)(void *dst, void const *src, size_t n_qwords, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc___memmovedownq_chk)(void *dst, void const *src, size_t n_qwords, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBDCALL libd___mempmoveupq_chk)(void *__restrict dst, void const *__restrict src, size_t n_qwords, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc___mempmoveupq_chk)(void *__restrict dst, void const *__restrict src, size_t n_qwords, size_t dst_objsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBDCALL libd___mempmovedownq_chk)(void *__restrict dst, void const *__restrict src, size_t n_qwords, size_t dst_objsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LEAF ATTR_RETNONNULL NONNULL((1, 2)) uint64_t *NOTHROW_NCX(LIBCCALL libc___mempmovedownq_chk)(void *__restrict dst, void const *__restrict src, size_t n_qwords, size_t dst_objsize);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SSP_STRING_H */
