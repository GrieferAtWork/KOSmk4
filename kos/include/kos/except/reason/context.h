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
#ifndef _KOS_EXCEPT_REASON_CONTEXT_H
#define _KOS_EXCEPT_REASON_CONTEXT_H 1

#include <__stdinc.h>

__DECL_BEGIN

/* Context codes for E_INVALID_CONTEXT exceptions */

/*[[[enum]]]*/
#ifdef __CC__
enum {
	E_INVALID_CONTEXT_GENERIC,                               /* Generic context */
	E_INVALID_CONTEXT_PRCTL_SET_KEEPCAPS_LOCKED,             /* E_INVALID_CONTEXT_NOT_PERMITTED: Tried to use `PR_SET_KEEPCAPS' when `SECBIT_KEEP_CAPS_LOCKED' is set. */
	E_INVALID_CONTEXT_PRCTL_SET_SECUREBITS_UNLOCK,           /* E_INVALID_CONTEXT_NOT_PERMITTED: Tried to use `PR_SET_KEEPCAPS' to clear a `SECBIT_*_LOCKED' bit. */
	E_INVALID_CONTEXT_PRCTL_SET_SECUREBITS_LOCKED,           /* E_INVALID_CONTEXT_NOT_PERMITTED: Tried to use `PR_SET_KEEPCAPS' to change a bit that was `*_LOCKED'-ed. */
	E_INVALID_CONTEXT_PRCTL_SET_NO_NEW_PRIVS_CANNOT_DISABLE, /* E_INVALID_CONTEXT_NOT_PERMITTED: Tried to use `PR_SET_NO_NEW_PRIVS' change `THIS_CRED->c_no_new_privs' from `1' to `0' */
	E_INVALID_CONTEXT_PRCTL_CAP_AMBIENT_RAISE_DISABLED,      /* E_INVALID_CONTEXT_NOT_PERMITTED: Tried to use `prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, cap)' when `SECBIT_NO_CAP_AMBIENT_RAISE' is set. */
	E_INVALID_CONTEXT_PRCTL_CAP_AMBIENT_RAISE_DENIED,        /* E_INVALID_CONTEXT_NOT_PERMITTED: Tried to use `prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, cap)', but `cap' is missing from `c_cap_permitted' ro `c_cap_inheritable' */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define E_INVALID_CONTEXT_GENERIC                               E_INVALID_CONTEXT_GENERIC                               /* Generic context */
#define E_INVALID_CONTEXT_PRCTL_SET_KEEPCAPS_LOCKED             E_INVALID_CONTEXT_PRCTL_SET_KEEPCAPS_LOCKED             /* E_INVALID_CONTEXT_NOT_PERMITTED: Tried to use `PR_SET_KEEPCAPS' when `SECBIT_KEEP_CAPS_LOCKED' is set. */
#define E_INVALID_CONTEXT_PRCTL_SET_SECUREBITS_UNLOCK           E_INVALID_CONTEXT_PRCTL_SET_SECUREBITS_UNLOCK           /* E_INVALID_CONTEXT_NOT_PERMITTED: Tried to use `PR_SET_KEEPCAPS' to clear a `SECBIT_*_LOCKED' bit. */
#define E_INVALID_CONTEXT_PRCTL_SET_SECUREBITS_LOCKED           E_INVALID_CONTEXT_PRCTL_SET_SECUREBITS_LOCKED           /* E_INVALID_CONTEXT_NOT_PERMITTED: Tried to use `PR_SET_KEEPCAPS' to change a bit that was `*_LOCKED'-ed. */
#define E_INVALID_CONTEXT_PRCTL_SET_NO_NEW_PRIVS_CANNOT_DISABLE E_INVALID_CONTEXT_PRCTL_SET_NO_NEW_PRIVS_CANNOT_DISABLE /* E_INVALID_CONTEXT_NOT_PERMITTED: Tried to use `PR_SET_NO_NEW_PRIVS' change `THIS_CRED->c_no_new_privs' from `1' to `0' */
#define E_INVALID_CONTEXT_PRCTL_CAP_AMBIENT_RAISE_DISABLED      E_INVALID_CONTEXT_PRCTL_CAP_AMBIENT_RAISE_DISABLED      /* E_INVALID_CONTEXT_NOT_PERMITTED: Tried to use `prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, cap)' when `SECBIT_NO_CAP_AMBIENT_RAISE' is set. */
#define E_INVALID_CONTEXT_PRCTL_CAP_AMBIENT_RAISE_DENIED        E_INVALID_CONTEXT_PRCTL_CAP_AMBIENT_RAISE_DENIED        /* E_INVALID_CONTEXT_NOT_PERMITTED: Tried to use `prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, cap)', but `cap' is missing from `c_cap_permitted' ro `c_cap_inheritable' */
#else /* __COMPILER_PREFERR_ENUMS */
#define E_INVALID_CONTEXT_GENERIC                               0 /* Generic context */
#define E_INVALID_CONTEXT_PRCTL_SET_KEEPCAPS_LOCKED             1 /* E_INVALID_CONTEXT_NOT_PERMITTED: Tried to use `PR_SET_KEEPCAPS' when `SECBIT_KEEP_CAPS_LOCKED' is set. */
#define E_INVALID_CONTEXT_PRCTL_SET_SECUREBITS_UNLOCK           2 /* E_INVALID_CONTEXT_NOT_PERMITTED: Tried to use `PR_SET_KEEPCAPS' to clear a `SECBIT_*_LOCKED' bit. */
#define E_INVALID_CONTEXT_PRCTL_SET_SECUREBITS_LOCKED           3 /* E_INVALID_CONTEXT_NOT_PERMITTED: Tried to use `PR_SET_KEEPCAPS' to change a bit that was `*_LOCKED'-ed. */
#define E_INVALID_CONTEXT_PRCTL_SET_NO_NEW_PRIVS_CANNOT_DISABLE 4 /* E_INVALID_CONTEXT_NOT_PERMITTED: Tried to use `PR_SET_NO_NEW_PRIVS' change `THIS_CRED->c_no_new_privs' from `1' to `0' */
#define E_INVALID_CONTEXT_PRCTL_CAP_AMBIENT_RAISE_DISABLED      5 /* E_INVALID_CONTEXT_NOT_PERMITTED: Tried to use `prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, cap)' when `SECBIT_NO_CAP_AMBIENT_RAISE' is set. */
#define E_INVALID_CONTEXT_PRCTL_CAP_AMBIENT_RAISE_DENIED        6 /* E_INVALID_CONTEXT_NOT_PERMITTED: Tried to use `prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, cap)', but `cap' is missing from `c_cap_permitted' ro `c_cap_inheritable' */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

__DECL_END

#endif /* !_KOS_EXCEPT_REASON_CONTEXT_H */
