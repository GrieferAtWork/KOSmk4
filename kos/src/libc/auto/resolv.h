/* HASH CRC-32:0x33d9df2e */
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
#ifndef GUARD_LIBC_AUTO_RESOLV_H
#define GUARD_LIBC_AUTO_RESOLV_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <resolv.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF void NOTHROW_NCX(LIBDCALL libd_fp_nquery)(u_char const *a, int b, FILE *c);
INTDEF void NOTHROW_NCX(LIBDCALL libd_fp_query)(u_char const *a, FILE *b);
INTDEF char const *NOTHROW_NCX(LIBDCALL libd_hostalias)(char const *a);
INTDEF void NOTHROW_NCX(LIBDCALL libd_p_query)(u_char const *a);
INTDEF int NOTHROW_NCX(LIBDCALL libd_res_isourserver)(struct sockaddr_in const *a);
INTDEF int NOTHROW_NCX(LIBDCALL libd_res_mkquery)(int a, char const *b, int c, int d, u_char const *e, int f, u_char const *g, u_char *h, int i);
INTDEF int NOTHROW_NCX(LIBDCALL libd_res_query)(char const *a, int b, int c, u_char *d, int e);
INTDEF int NOTHROW_NCX(LIBDCALL libd_res_querydomain)(char const *a, char const *b, int c, int d, u_char *e, int f);
INTDEF int NOTHROW_NCX(LIBDCALL libd_res_search)(char const *a, int b, int c, u_char *d, int e);
INTDEF int NOTHROW_NCX(LIBDCALL libd_res_send)(u_char const *a, int b, u_char *c, int d);
INTDEF int NOTHROW_NCX(LIBDCALL libd_res_hnok)(char const *a);
INTDEF int NOTHROW_NCX(LIBDCALL libd_res_ownok)(char const *a);
INTDEF int NOTHROW_NCX(LIBDCALL libd_res_mailok)(char const *a);
INTDEF int NOTHROW_NCX(LIBDCALL libd_res_dnok)(char const *a);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_sym_ston)(struct res_sym const *symbols, char const *wanted_name, int *p_success);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_sym_ston)(struct res_sym const *symbols, char const *wanted_name, int *p_success);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_RETNONNULL NONNULL((1)) char const *NOTHROW_NCX(LIBDCALL libd_sym_ntos)(struct res_sym const *symbols, int wanted_number, int *p_success);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_RETNONNULL NONNULL((1)) char const *NOTHROW_NCX(LIBCCALL libc_sym_ntos)(struct res_sym const *symbols, int wanted_number, int *p_success);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_RETNONNULL NONNULL((1)) char const *NOTHROW_NCX(LIBDCALL libd_sym_ntop)(struct res_sym const *symbols, int wanted_number, int *p_success);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_RETNONNULL NONNULL((1)) char const *NOTHROW_NCX(LIBCCALL libc_sym_ntop)(struct res_sym const *symbols, int wanted_number, int *p_success);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF int NOTHROW_NCX(LIBDCALL libd_b64_ntop)(u_char const *a, size_t b, char *c, size_t d);
INTDEF int NOTHROW_NCX(LIBDCALL libd_b64_pton)(char const *a, u_char *b, size_t c);
INTDEF int NOTHROW_NCX(LIBDCALL libd_loc_aton)(char const *a, u_char *b);
INTDEF char const *NOTHROW_NCX(LIBDCALL libd_loc_ntoa)(u_char const *a, char *b);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBDCALL libd_dn_skipname)(u_char const *msg_ptr, u_char const *end_of_msg);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_dn_skipname)(u_char const *msg_ptr, u_char const *end_of_msg);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF char const *NOTHROW_NCX(LIBDCALL libd_p_class)(int a);
INTDEF char const *NOTHROW_NCX(LIBDCALL libd_p_time)(u_int32_t a);
INTDEF char const *NOTHROW_NCX(LIBDCALL libd_p_type)(int a);
INTDEF char const *NOTHROW_NCX(LIBDCALL libd_p_rcode)(int a);
INTDEF u_char const *NOTHROW_NCX(LIBDCALL libd_p_cdnname)(u_char const *a, u_char const *b, int c, FILE *d);
INTDEF u_char const *NOTHROW_NCX(LIBDCALL libd_p_cdname)(u_char const *a, u_char const *b, FILE *c);
INTDEF u_char const *NOTHROW_NCX(LIBDCALL libd_p_fqnname)(u_char const *a, u_char const *b, int c, char *d, int e);
INTDEF u_char const *NOTHROW_NCX(LIBDCALL libd_p_fqname)(u_char const *a, u_char const *b, FILE *c);
INTDEF char const *NOTHROW_NCX(LIBDCALL libd_p_option)(u_long a);
INTDEF char *NOTHROW_NCX(LIBDCALL libd_p_secstodate)(u_long a);
INTDEF int NOTHROW_NCX(LIBDCALL libd_dn_count_labels)(char const *a);
INTDEF int NOTHROW_NCX(LIBDCALL libd_dn_expand)(u_char const *msg_ptr, u_char const *end_of_msg, u_char const *srcbuf, char *dstbuf, int dstbufsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF int NOTHROW_NCX(LIBCCALL libc_dn_expand)(u_char const *msg_ptr, u_char const *end_of_msg, u_char const *srcbuf, char *dstbuf, int dstbufsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF int NOTHROW_NCX(LIBDCALL libd_res_nameinquery)(char const *a, int b, int c, u_char const *d, u_char const *e);
INTDEF int NOTHROW_NCX(LIBDCALL libd_res_queriesmatch)(u_char const *a, u_char const *b, u_char const *c, u_char const *d);
INTDEF char const *NOTHROW_NCX(LIBDCALL libd_p_section)(int a, int b);
INTDEF int NOTHROW_NCX(LIBDCALL libd_res_ninit)(res_state a);
INTDEF int NOTHROW_NCX(LIBDCALL libd_res_nisourserver)(res_state a, struct sockaddr_in const *b);
INTDEF void NOTHROW_NCX(LIBDCALL libd_fp_resstat)(res_state a, FILE *b);
INTDEF void NOTHROW_NCX(LIBDCALL libd_res_npquery)(res_state a, u_char const *b, int c, FILE *d);
INTDEF char const *NOTHROW_NCX(LIBDCALL libd_res_hostalias)(res_state a, char const *b, char *c, size_t d);
INTDEF int NOTHROW_NCX(LIBDCALL libd_res_nquery)(res_state a, char const *b, int c, int d, u_char *e, int f);
INTDEF int NOTHROW_NCX(LIBDCALL libd_res_nsearch)(res_state a, char const *b, int c, int d, u_char *e, int f);
INTDEF int NOTHROW_NCX(LIBDCALL libd_res_nquerydomain)(res_state a, char const *b, char const *c, int d, int e, u_char *f, int g);
INTDEF int NOTHROW_NCX(LIBDCALL libd_res_nmkquery)(res_state a, int b, char const *c, int d, int e, u_char const *f, int g, u_char const *h, u_char *i, int j);
INTDEF int NOTHROW_NCX(LIBDCALL libd_res_nsend)(res_state a, u_char const *b, int c, u_char *d, int e);
INTDEF void NOTHROW_NCX(LIBDCALL libd_res_nclose)(res_state a);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#undef __fp_nquery
#undef __fp_query
#undef __hostalias
#undef __p_query
#undef __res_close
#undef __res_init
#undef __res_isourserver
#undef __res_mkquery
#undef __res_query
#undef __res_querydomain
#undef __res_search
#undef __res_send
#undef __b64_ntop
#undef __b64_pton
#undef __dn_comp
#undef __dn_count_labels
#undef __dn_expand
#undef __dn_skipname
#undef __fp_resstat
#undef __loc_aton
#undef __loc_ntoa
#undef __p_cdname
#undef __p_cdnname
#undef __p_class
#undef __p_fqname
#undef __p_fqnname
#undef __p_option
#undef __p_secstodate
#undef __p_section
#undef __p_time
#undef __p_type
#undef __p_rcode
#undef __putlong
#undef __putshort
#undef __res_dnok
#undef __res_hnok
#undef __res_hostalias
#undef __res_mailok
#undef __res_nameinquery
#undef __res_nclose
#undef __res_ninit
#undef __res_nmkquery
#undef __res_npquery
#undef __res_nquery
#undef __res_nquerydomain
#undef __res_nsearch
#undef __res_nsend
#undef __res_nisourserver
#undef __res_ownok
#undef __res_queriesmatch
#undef __res_randomid
#undef __sym_ntop
#undef __sym_ntos
#undef __sym_ston

DECL_END

#endif /* !GUARD_LIBC_AUTO_RESOLV_H */
