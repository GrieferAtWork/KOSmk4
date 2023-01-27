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
#ifndef _BITS_CRT_DB_SPWD_H
#define _BITS_CRT_DB_SPWD_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

/*
 * C structure for describing a password database entry from /etc/shadow
 *
 * Every line from /etc/shadow that isn't empty, or a comment will match
 * the following formats:
 *
 *    sp_namp:sp_pwdp:sp_lstchg:sp_min:sp_max:sp_warn:sp_inact:sp_expire:sp_flag
 *
 * NOTES:
 * - Notes on fields:
 *   - sp_namp: Login name (which must also exist in /etc/passwd)
 *   - sp_pwdp: The following special values for `sp_pwdp' exist:
 *     - "":   No password is needed (though for safety, some programs treat this as login-impossible)
 *     - "!*": A password field that starts with "!", it was locked (making login impossible)
 *   - sp_lstchg:
 *     - "":   Password changing is disabled (same as `LONGPTR_MAX')
 *     - "0":  User much change password the next time they log in
 *   - sp_min:
 *     - "", "0": Passwords can always be changed (why would you want to prevent that???)
 *   - sp_max:
 *     - "":   Passwords never expire (same as `LONGPTR_MAX')
 *   - sp_warn: (only meaningful when `sp_max' isn't an empty string)
 *     - "", "0": There is no warning period
 *   - sp_inact: (only meaningful when `sp_max' isn't an empty string)
 *     - "", "0": Login becomes disabled immediately
 *   - sp_expire:
 *     - "": The account never expires (same as `LONGPTR_MAX')
 *   - sp_flag: Unused. Should be an empty field (treated as `sp_flag = 0')
 *              Else: parsed as a number field like the others preceding it
 *
 * For processing, libc uses `fparseln()' with default with `delim = "\0\0#"'
 *
 * FILES:
 *   - /etc/shadow
 */
#ifdef __CC__
__DECL_BEGIN

/* Structure of the shadow-password file. */
struct spwd {
	char             *sp_namp;    /* [1..1] Login name. */
	char             *sp_pwdp;    /* [1..1] Encrypted password. */
	__LONGPTR_TYPE__  sp_lstchg;  /* # of days since 1970-01-01 of lass password change. */
	__LONGPTR_TYPE__  sp_min;     /* [>= 0] # of days that must have passed before password may be changed. */
	__LONGPTR_TYPE__  sp_max;     /* [>= 0] # of days that must have passed before password must be changed. */
	__LONGPTR_TYPE__  sp_warn;    /* [>= 0] # of days where user is given a warning of impending password force-change before `sp_max' */
	__LONGPTR_TYPE__  sp_inact;   /* [>= 0] # of extra days after `sp_max' before the account becomes disabled */
	__LONGPTR_TYPE__  sp_expire;  /* # of days since 1970-01-01 for date when account becomes disabled */
	__ULONGPTR_TYPE__ sp_flag;    /* Reserved. */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_DB_SPWD_H */
