/* HASH CRC-32:0xab957a13 */
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
#ifndef GUARD_LIBC_USER_RESOLV_H
#define GUARD_LIBC_USER_RESOLV_H 1

#include "../api.h"
#include "../auto/resolv.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <resolv.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED struct __res_state *NOTHROW(LIBCCALL libc___res_state)(void);
INTDEF void NOTHROW_NCX(LIBCCALL libc_fp_nquery)(u_char const *a, int b, FILE *c);
INTDEF void NOTHROW_NCX(LIBCCALL libc_fp_query)(u_char const *a, FILE *b);
INTDEF char const *NOTHROW_NCX(LIBCCALL libc_hostalias)(char const *a);
INTDEF void NOTHROW_NCX(LIBCCALL libc_p_query)(u_char const *a);
INTDEF void NOTHROW_NCX(LIBCCALL libc_res_close)(void);
INTDEF int NOTHROW_NCX(LIBCCALL libc_res_init)(void);
INTDEF int NOTHROW_NCX(LIBCCALL libc_res_isourserver)(struct sockaddr_in const *a);
INTDEF int NOTHROW_NCX(LIBCCALL libc_res_mkquery)(int a, char const *b, int c, int d, u_char const *e, int f, u_char const *g, u_char *h, int i);
INTDEF int NOTHROW_NCX(LIBCCALL libc_res_query)(char const *a, int b, int c, u_char *d, int e);
INTDEF int NOTHROW_NCX(LIBCCALL libc_res_querydomain)(char const *a, char const *b, int c, int d, u_char *e, int f);
INTDEF int NOTHROW_NCX(LIBCCALL libc_res_search)(char const *a, int b, int c, u_char *d, int e);
INTDEF int NOTHROW_NCX(LIBCCALL libc_res_send)(u_char const *a, int b, u_char *c, int d);
INTDEF int NOTHROW_NCX(LIBCCALL libc_res_hnok)(char const *a);
INTDEF int NOTHROW_NCX(LIBCCALL libc_res_ownok)(char const *a);
INTDEF int NOTHROW_NCX(LIBCCALL libc_res_mailok)(char const *a);
INTDEF int NOTHROW_NCX(LIBCCALL libc_res_dnok)(char const *a);
INTDEF int NOTHROW_NCX(LIBCCALL libc_b64_ntop)(u_char const *a, size_t b, char *c, size_t d);
INTDEF int NOTHROW_NCX(LIBCCALL libc_b64_pton)(char const *a, u_char *b, size_t c);
INTDEF int NOTHROW_NCX(LIBCCALL libc_loc_aton)(char const *a, u_char *b);
INTDEF char const *NOTHROW_NCX(LIBCCALL libc_loc_ntoa)(u_char const *a, char *b);
INTDEF char const *NOTHROW_NCX(LIBCCALL libc_p_class)(int a);
INTDEF char const *NOTHROW_NCX(LIBCCALL libc_p_time)(u_int32_t a);
INTDEF char const *NOTHROW_NCX(LIBCCALL libc_p_type)(int a);
INTDEF char const *NOTHROW_NCX(LIBCCALL libc_p_rcode)(int a);
INTDEF u_char const *NOTHROW_NCX(LIBCCALL libc_p_cdnname)(u_char const *a, u_char const *b, int c, FILE *d);
INTDEF u_char const *NOTHROW_NCX(LIBCCALL libc_p_cdname)(u_char const *a, u_char const *b, FILE *c);
INTDEF u_char const *NOTHROW_NCX(LIBCCALL libc_p_fqnname)(u_char const *a, u_char const *b, int c, char *d, int e);
INTDEF u_char const *NOTHROW_NCX(LIBCCALL libc_p_fqname)(u_char const *a, u_char const *b, FILE *c);
INTDEF char const *NOTHROW_NCX(LIBCCALL libc_p_option)(u_long a);
INTDEF char *NOTHROW_NCX(LIBCCALL libc_p_secstodate)(u_long a);
INTDEF int NOTHROW_NCX(LIBCCALL libc_dn_count_labels)(char const *a);
INTDEF u_int NOTHROW_NCX(LIBCCALL libc_res_randomid)(void);
INTDEF int NOTHROW_NCX(LIBCCALL libc_res_nameinquery)(char const *a, int b, int c, u_char const *d, u_char const *e);
INTDEF int NOTHROW_NCX(LIBCCALL libc_res_queriesmatch)(u_char const *a, u_char const *b, u_char const *c, u_char const *d);
INTDEF char const *NOTHROW_NCX(LIBCCALL libc_p_section)(int a, int b);
INTDEF int NOTHROW_NCX(LIBCCALL libc_res_ninit)(res_state a);
INTDEF int NOTHROW_NCX(LIBCCALL libc_res_nisourserver)(res_state a, struct sockaddr_in const *b);
INTDEF void NOTHROW_NCX(LIBCCALL libc_fp_resstat)(res_state a, FILE *b);
INTDEF void NOTHROW_NCX(LIBCCALL libc_res_npquery)(res_state a, u_char const *b, int c, FILE *d);
INTDEF char const *NOTHROW_NCX(LIBCCALL libc_res_hostalias)(res_state a, char const *b, char *c, size_t d);
INTDEF int NOTHROW_NCX(LIBCCALL libc_res_nquery)(res_state a, char const *b, int c, int d, u_char *e, int f);
INTDEF int NOTHROW_NCX(LIBCCALL libc_res_nsearch)(res_state a, char const *b, int c, int d, u_char *e, int f);
INTDEF int NOTHROW_NCX(LIBCCALL libc_res_nquerydomain)(res_state a, char const *b, char const *c, int d, int e, u_char *f, int g);
INTDEF int NOTHROW_NCX(LIBCCALL libc_res_nmkquery)(res_state a, int b, char const *c, int d, int e, u_char const *f, int g, u_char const *h, u_char *i, int j);
INTDEF int NOTHROW_NCX(LIBCCALL libc_res_nsend)(res_state a, u_char const *b, int c, u_char *d, int e);
INTDEF void NOTHROW_NCX(LIBCCALL libc_res_nclose)(res_state a);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_RESOLV_H */
