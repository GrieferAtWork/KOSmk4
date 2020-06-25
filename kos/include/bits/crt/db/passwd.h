/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_CRT_DB_PASSWD_H
#define _BITS_CRT_DB_PASSWD_H 1

#include <__stdinc.h>

#include <bits/types.h>

__SYSDECL_BEGIN

#ifdef __CC__

struct passwd {
	char   *pw_name;   /* Username. */
	char   *pw_passwd; /* Password. */
	__uid_t pw_uid;    /* User ID. */
	__gid_t pw_gid;    /* Group ID. */
	char   *pw_gecos;  /* Real name. */
	char   *pw_dir;    /* Home directory. */
	char   *pw_shell;  /* Shell program. */
};

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_BITS_CRT_DB_PASSWD_H */
