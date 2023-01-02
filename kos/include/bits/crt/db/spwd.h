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

#ifdef __CC__
__DECL_BEGIN

/* Structure of the password file. */
struct spwd {
	char             *sp_namp;    /* Login name. */
	char             *sp_pwdp;    /* Encrypted password. */
	__LONGPTR_TYPE__  sp_lstchg;  /* Date of last change. */
	__LONGPTR_TYPE__  sp_min;     /* Minimum number of days between changes. */
	__LONGPTR_TYPE__  sp_max;     /* Maximum number of days between changes. */
	__LONGPTR_TYPE__  sp_warn;    /* Number of days to warn user to change the password. */
	__LONGPTR_TYPE__  sp_inact;   /* Number of days the account may be inactive. */
	__LONGPTR_TYPE__  sp_expire;  /* Number of days since 1970-01-01 until account expires. */
	__ULONGPTR_TYPE__ sp_flag;    /* Reserved. */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_DB_SPWD_H */
