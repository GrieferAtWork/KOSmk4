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
#ifndef GUARD_LIBC_LIBC_ERRNO_H
#define GUARD_LIBC_LIBC_ERRNO_H 1

#include "../api.h"

DECL_BEGIN

#ifdef __CC__
/* Defined in "../api.h" */ /*
INTDEF NOBLOCK ATTR_CONST errno_t *NOTHROW(LIBCCALL libc_errno_p)(void);
INTDEF NOBLOCK errno_t NOTHROW(LIBCCALL libc_geterrno)(void);
INTDEF NOBLOCK syscall_slong_t NOTHROW(__FCALL libc_seterrno)(errno_t value);
*/

/* Defined in "../api.h" */ /*
INTDEF NOBLOCK ATTR_CONST / *dos* / errno_t *NOTHROW(LIBDCALL libd_errno_p)(void);
INTDEF NOBLOCK ATTR_PURE / *dos* / errno_t NOTHROW(LIBDCALL libd_geterrno)(void);
INTDEF NOBLOCK syscall_slong_t NOTHROW(LIBDCALL libd_seterrno)(/ *dos* / errno_t value);
*/

INTDEF NOBLOCK ATTR_CONST /*nt*/ errno_t *NOTHROW(LIBDCALL libd_nterrno_p)(void);
INTDEF NOBLOCK ATTR_PURE /*nt*/ errno_t NOTHROW(LIBDCALL libd_getnterrno)(void);
INTDEF NOBLOCK syscall_slong_t NOTHROW(LIBDCALL libd_setnterrno)(/*nt*/ errno_t value);

INTDEF NOBLOCK ATTR_CONST /*cyg*/ errno_t *NOTHROW(LIBDCALL libd_cygerrno_p)(void);
INTDEF NOBLOCK ATTR_PURE /*cyg*/ errno_t NOTHROW(LIBDCALL libd_getcygerrno)(void);
INTDEF NOBLOCK syscall_slong_t NOTHROW(LIBDCALL libd_setcygerrno)(/*cyg*/ errno_t value);

INTDEF NOBLOCK ATTR_CONST /*kos*/ errno_t NOTHROW(LIBDCALL libd_errno_cyg2kos)(/*cyg*/ errno_t value);
/*INTDEF NOBLOCK ATTR_CONST / *kos* / errno_t NOTHROW(LIBDCALL libd_errno_dos2kos)(/ *dos* / errno_t value);*/ /* Defined in "../api.h" */
INTDEF NOBLOCK ATTR_CONST /*kos*/ errno_t NOTHROW(LIBDCALL libd_errno_nt2kos)(/*nt*/ errno_t value);
INTDEF NOBLOCK ATTR_CONST /*cyg*/ errno_t NOTHROW(LIBDCALL libd_errno_kos2cyg)(/*kos*/ errno_t value);
INTDEF NOBLOCK ATTR_CONST /*cyg*/ errno_t NOTHROW(LIBDCALL libd_errno_dos2cyg)(/*dos*/ errno_t value);
INTDEF NOBLOCK ATTR_CONST /*cyg*/ errno_t NOTHROW(LIBDCALL libd_errno_nt2cyg)(/*nt*/ errno_t value);
/*INTDEF NOBLOCK ATTR_CONST / *dos* / errno_t NOTHROW(LIBDCALL libd_errno_kos2dos)(/ *kos* / errno_t value);*/ /* Defined in "../api.h" */
INTDEF NOBLOCK ATTR_CONST /*dos*/ errno_t NOTHROW(LIBDCALL libd_errno_cyg2dos)(/*cyg*/ errno_t value);
INTDEF NOBLOCK ATTR_CONST /*dos*/ errno_t NOTHROW(LIBDCALL libd_errno_nt2dos)(/*nt*/ errno_t value);
INTDEF NOBLOCK ATTR_CONST /*nt*/ errno_t NOTHROW(LIBDCALL libd_errno_kos2nt)(/*kos*/ errno_t value);
INTDEF NOBLOCK ATTR_CONST /*nt*/ errno_t NOTHROW(LIBDCALL libd_errno_cyg2nt)(/*cyg*/ errno_t value);
INTDEF NOBLOCK ATTR_CONST /*nt*/ errno_t NOTHROW(LIBDCALL libd_errno_dos2nt)(/*dos*/ errno_t value);

/*INTDEF NOBLOCK ATTR_CONST / *kos* / signo_t NOTHROW(LIBDCALL libd_signo_dos2kos)(/ *dos* / signo_t value);*/ /* Defined in "../api.h" */
/*INTDEF NOBLOCK ATTR_CONST / *dos* / signo_t NOTHROW(LIBDCALL libd_signo_kos2dos)(/ *kos* / signo_t value);*/ /* Defined in "../api.h" */


INTDEF ATTR_CONST WUNUSED char const *const *NOTHROW(LIBCCALL libc___sys_errlist)(void);
INTDEF ATTR_CONST WUNUSED int *NOTHROW(LIBCCALL libc___sys_nerr)(void);
#endif /* __CC__ */


DECL_END

#endif /* !GUARD_LIBC_LIBC_ERRNO_H */
