/* HASH CRC-32:0x3ee4a717 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_VIS_H
#define GUARD_LIBC_AUTO_VIS_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <vis.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_vis)(char *dst, int c, int flags, int nextc);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_vis)(char *dst, int c, int flags, int nextc);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_OUTS(1, 2) char *NOTHROW_NCX(LIBDCALL libd_nvis)(char *dst, size_t dstsize, int c, int flags, int nextc);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_OUTS(1, 2) char *NOTHROW_NCX(LIBCCALL libc_nvis)(char *dst, size_t dstsize, int c, int flags, int nextc);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(5) NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd_svis)(char *dst, int c, int flags, int nextc, char const *mbextra);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(5) NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_svis)(char *dst, int c, int flags, int nextc, char const *mbextra);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(6) ATTR_OUTS(1, 2) char *NOTHROW_NCX(LIBDCALL libd_snvis)(char *dst, size_t dstsize, int c, int flags, int nextc, char const *mbextra);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(6) ATTR_OUTS(1, 2) char *NOTHROW_NCX(LIBCCALL libc_snvis)(char *dst, size_t dstsize, int c, int flags, int nextc, char const *mbextra);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(2) NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_strvis)(char *dst, char const *src, int flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(2) NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_strvis)(char *dst, char const *src, int flags);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN_OPT(2) ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_stravis)(char **p_resstr, char const *src, int flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN_OPT(2) ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_stravis)(char **p_resstr, char const *src, int flags);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_OUTS(1, 2) int NOTHROW_NCX(LIBDCALL libd_strnvis_netbsd)(char *dst, size_t dstsize, char const *src, int flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_OUTS(1, 2) int NOTHROW_NCX(LIBCCALL libc_strnvis_netbsd)(char *dst, size_t dstsize, char const *src, int flags);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_OUTS(1, 3) int NOTHROW_NCX(LIBDCALL libd_strnvis)(char *dst, char const *src, size_t dstsize, int flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_OUTS(1, 3) int NOTHROW_NCX(LIBCCALL libc_strnvis)(char *dst, char const *src, size_t dstsize, int flags);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(4) ATTR_IN_OPT(2) NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_strsvis)(char *dst, char const *src, int flags, char const *mbextra);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(4) ATTR_IN_OPT(2) NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_strsvis)(char *dst, char const *src, int flags, char const *mbextra);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(5) ATTR_IN_OPT(3) ATTR_OUTS(1, 2) int NOTHROW_NCX(LIBDCALL libd_strsnvis)(char *dst, size_t dstsize, char const *src, int flags, char const *mbextra);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(5) ATTR_IN_OPT(3) ATTR_OUTS(1, 2) int NOTHROW_NCX(LIBCCALL libc_strsnvis)(char *dst, size_t dstsize, char const *src, int flags, char const *mbextra);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INS(2, 3) NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_strvisx)(char *dst, char const *src, size_t srclen, int flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INS(2, 3) NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_strvisx)(char *dst, char const *src, size_t srclen, int flags);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INS(3, 4) ATTR_OUTS(1, 2) int NOTHROW_NCX(LIBDCALL libd_strnvisx)(char *dst, size_t dstsize, char const *src, size_t srclen, int flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INS(3, 4) ATTR_OUTS(1, 2) int NOTHROW_NCX(LIBCCALL libc_strnvisx)(char *dst, size_t dstsize, char const *src, size_t srclen, int flags);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_INS(3, 4) ATTR_OUTS(1, 2) ATTR_OUT_OPT(6) int NOTHROW_NCX(LIBDCALL libd_strenvisx)(char *dst, size_t dstsize, char const *src, size_t srclen, int flags, int *cerr_ptr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INS(3, 4) ATTR_OUTS(1, 2) ATTR_OUT_OPT(6) int NOTHROW_NCX(LIBCCALL libc_strenvisx)(char *dst, size_t dstsize, char const *src, size_t srclen, int flags, int *cerr_ptr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(5) NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_strsvisx)(char *dst, char const *src, size_t srclen, int flags, char const *mbextra);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(5) NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_strsvisx)(char *dst, char const *src, size_t srclen, int flags, char const *mbextra);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(6) ATTR_INS(3, 4) ATTR_OUTS(1, 2) int NOTHROW_NCX(LIBDCALL libd_strsnvisx)(char *dst, size_t dstsize, char const *src, size_t srclen, int flags, char const *mbextra);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(6) ATTR_INS(3, 4) ATTR_OUTS(1, 2) int NOTHROW_NCX(LIBCCALL libc_strsnvisx)(char *dst, size_t dstsize, char const *src, size_t srclen, int flags, char const *mbextra);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(6) ATTR_INS(3, 4) ATTR_OUTS(1, 2) int NOTHROW_NCX(LIBDCALL libd_strsenvisx)(char *dst, size_t dstsize, char const *src, size_t srclen, int flags, char const *mbextra, int *cerr_ptr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(6) ATTR_INS(3, 4) ATTR_OUTS(1, 2) int NOTHROW_NCX(LIBCCALL libc_strsenvisx)(char *dst, size_t dstsize, char const *src, size_t srclen, int flags, char const *mbextra, int *cerr_ptr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(2) NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_strunvis)(char *dst, char const *src);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(2) NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_strunvis)(char *dst, char const *src);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) int NOTHROW_NCX(LIBDCALL libd_strnunvis_netbsd)(char *dst, size_t dstsize, char const *src);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) int NOTHROW_NCX(LIBCCALL libc_strnunvis_netbsd)(char *dst, size_t dstsize, char const *src);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(2) ATTR_OUTS(1, 3) int NOTHROW_NCX(LIBDCALL libd_strnunvis)(char *dst, char const *src, size_t dstsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(2) ATTR_OUTS(1, 3) int NOTHROW_NCX(LIBCCALL libc_strnunvis)(char *dst, char const *src, size_t dstsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(2) NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_strunvisx)(char *dst, char const *src, int flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(2) NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_strunvisx)(char *dst, char const *src, int flags);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) int NOTHROW_NCX(LIBDCALL libd_strnunvisx)(char *dst, size_t dstsize, char const *src, int flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) int NOTHROW_NCX(LIBCCALL libc_strnunvisx)(char *dst, size_t dstsize, char const *src, int flags);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unvis(3)
 * WARNING: When returning `UNVIS_NOCHAR', `*p_outbyte' may be part of the internal state  and
 *          has to be copied alongside `*p_state' if you wish to state (and later restore) the
 *          state of this function!
 * @param: flags: Set of `VIS_HTTP1808 | VIS_MIMESTYLE | VIS_HTTP1866 | VIS_NOESCAPE | UNVIS_END'
 * @return: UNVIS_SYNBAD:    [...]
 * @return: UNVIS_VALID:     [...]
 * @return: UNVIS_VALIDPUSH: [...]
 * @return: UNVIS_NOCHAR:    [...] */
INTDEF ATTR_INOUT(3) NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_unvis)(char *p_outbyte, int inbyte, int *p_state, int flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> unvis(3)
 * WARNING: When returning `UNVIS_NOCHAR', `*p_outbyte' may be part of the internal state  and
 *          has to be copied alongside `*p_state' if you wish to state (and later restore) the
 *          state of this function!
 * @param: flags: Set of `VIS_HTTP1808 | VIS_MIMESTYLE | VIS_HTTP1866 | VIS_NOESCAPE | UNVIS_END'
 * @return: UNVIS_SYNBAD:    [...]
 * @return: UNVIS_VALID:     [...]
 * @return: UNVIS_VALIDPUSH: [...]
 * @return: UNVIS_NOCHAR:    [...] */
INTDEF ATTR_INOUT(3) NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_unvis)(char *p_outbyte, int inbyte, int *p_state, int flags);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_VIS_H */
