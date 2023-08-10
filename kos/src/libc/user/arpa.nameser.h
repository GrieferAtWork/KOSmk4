/* HASH CRC-32:0x80e65a2f */
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
#ifndef GUARD_LIBC_USER_ARPA_NAMESER_H
#define GUARD_LIBC_USER_ARPA_NAMESER_H 1

#include "../api.h"
#include "../auto/arpa.nameser.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <arpa/nameser.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_initparse)(u_char const *a, int b, ns_msg *c);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_skiprr)(u_char const *a, u_char const *b, ns_sect c, int d);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_parserr)(ns_msg *a, ns_sect b, int c, ns_rr *d);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_sprintrr)(ns_msg const *a, ns_rr const *b, char const *c, char const *d, char *e, size_t f);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_sprintrrf)(u_char const *a, size_t, char const *b, ns_class c, ns_type d, u_long e, u_char const *f, size_t g, char const *h, char const *i, char *j, size_t k);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_format_ttl)(u_long a, char *b, size_t c);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_parse_ttl)(char const *a, u_long *b);
INTDEF u_int32_t NOTHROW_NCX(LIBCCALL libc_ns_datetosecs)(char const *a, int *b);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_name_ntol)(u_char const *a, u_char *b, size_t c);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_name_ntop)(u_char const *a, char *b, size_t c);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_name_pton)(char const *a, u_char *b, size_t c);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_name_unpack)(u_char const *a, u_char const *b, u_char const *c, u_char *d, size_t e);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_name_pack)(u_char const *a, u_char *b, int c, u_char const **d, u_char const **e);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_name_uncompress)(u_char const *a, u_char const *b, u_char const *c, char *d, size_t e);
INTDEF ATTR_INOUT(1) NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_ns_name_skip)(u_char const **p_msg_ptr, u_char const *msg_end);
INTDEF void NOTHROW_NCX(LIBCCALL libc_ns_name_rollback)(u_char const *a, u_char const **b, u_char const **c);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_sign)(u_char *a, int *b, int c, int d, void *e, u_char const *f, int g, u_char *h, int *i, time_t j);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_sign2)(u_char *a, int *b, int c, int d, void *e, u_char const *f, int g, u_char *h, int *i, time_t j, u_char **k, u_char **l);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_sign_tcp)(u_char *a, int *b, int c, int d, ns_tcp_tsig_state *e, int f);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_sign_tcp2)(u_char *a, int *b, int c, int d, ns_tcp_tsig_state *e, int f, u_char **g, u_char **h);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_sign_tcp_init)(void *a, u_char const *b, int c, ns_tcp_tsig_state *d);
INTDEF u_char *NOTHROW_NCX(LIBCCALL libc_ns_find_tsig)(u_char *a, u_char *b);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_verify)(u_char *a, int *b, void *c, u_char const *d, int e, u_char *f, int *g, time_t *h, int i);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_verify_tcp)(u_char *a, int *b, ns_tcp_tsig_state *c, int d);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_verify_tcp_init)(void *a, u_char const *b, int c, ns_tcp_tsig_state *d);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_samedomain)(char const *a, char const *b);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_subdomain)(char const *a, char const *b);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_makecanon)(char const *a, char *b, size_t c);
INTDEF int NOTHROW_NCX(LIBCCALL libc_ns_samename)(char const *a, char const *b);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_ARPA_NAMESER_H */
