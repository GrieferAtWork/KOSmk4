/* HASH CRC-32:0x5625ad11 */
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
#ifndef GUARD_LIBC_USER_LIBIBERTY_H
#define GUARD_LIBC_USER_LIBIBERTY_H 1

#include "../api.h"
#include "../auto/libiberty.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <libiberty.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF void NOTHROW_NCX(LIBCCALL libc_xmalloc_set_program_name)(char const *progname);
INTDEF ATTR_NORETURN void (LIBCCALL libc_xmalloc_failed)(size_t num_bytes) THROWS(...);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc_fdmatch)(fd_t fd1, fd_t fd2);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF char *NOTHROW_NCX(VLIBDCALL libd_concat_copy2)(char const *first, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF char *NOTHROW_NCX(VLIBCCALL libc_concat_copy2)(char const *first, ...);
INTDEF long NOTHROW_NCX(LIBCCALL libc_get_run_time)(void);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED char *NOTHROW_NCX(LIBCCALL libc_make_relative_prefix)(char const *a, char const *b, char const *c);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED char *NOTHROW_NCX(LIBCCALL libc_make_relative_prefix_ignore_links)(char const *a, char const *b, char const *c);
INTDEF void NOTHROW_NCX(LIBCCALL libc_hex_init)(void);
INTDEF char const *NOTHROW_NCX(LIBCCALL libc_pex_run)(struct pex_obj *obj, int flags, char const *executable, char *const *argv, char const *outname, char const *errname, int *err);
INTDEF char const *NOTHROW_NCX(LIBCCALL libc_pex_run_in_environment)(struct pex_obj *obj, int flags, char const *executable, char *const *argv, char *const *env, char const *outname, char const *errname, int *err);
INTDEF FILE *NOTHROW_NCX(LIBCCALL libc_pex_input_file)(struct pex_obj *obj, int flags, char const *in_name);
INTDEF FILE *NOTHROW_NCX(LIBCCALL libc_pex_input_pipe)(struct pex_obj *obj, int binary);
INTDEF FILE *NOTHROW_NCX(LIBCCALL libc_pex_read_output)(struct pex_obj *obj, int binary);
INTDEF FILE *NOTHROW_NCX(LIBCCALL libc_pex_read_err)(struct pex_obj *obj, int binary);
INTDEF int NOTHROW_NCX(LIBCCALL libc_pex_get_status)(struct pex_obj *obj, int count, int *vector);
INTDEF struct pex_obj *NOTHROW_NCX(LIBCCALL libc_pex_init)(int flags, char const *pname, char const *tempbase);
INTDEF int NOTHROW_NCX(LIBCCALL libc_pex_get_times)(struct pex_obj *obj, int count, struct pex_time *vector);
INTDEF void NOTHROW_NCX(LIBCCALL libc_pex_free)(struct pex_obj *obj);
INTDEF char const *NOTHROW_NCX(LIBCCALL libc_pex_one)(int flags, char const *executable, char *const *argv, char const *pname, char const *outname, char const *errname, int *status, int *err);
INTDEF int NOTHROW_NCX(LIBCCALL libc_pexecute)(char const *a, char *const *b, char const *c, char const *d, char **e, char **f, int g);
INTDEF int NOTHROW_NCX(LIBCCALL libc_pwait)(int a, int *b, int c);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_LIBIBERTY_H */
