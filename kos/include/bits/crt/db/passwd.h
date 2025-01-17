/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_CRT_DB_PASSWD_H
#define _BITS_CRT_DB_PASSWD_H 1

#include <__stdinc.h>

#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

/*
 * C structure for describing a password database entry from /etc/passwd
 *
 * Every line from /etc/passwd that isn't empty, or a comment will match
 * exactly one of the following formats:
 *
 *    pw_name:pw_passwd:pw_uid:pw_gid:pw_gecos:pw_dir:pw_shell
 *    pw_name:pw_passwd:pw_uid:pw_gid:pw_dir:pw_shell
 *    pw_name:pw_passwd:pw_uid:pw_gid
 *
 * NOTE: The  `pw_passwd' field  (used to  be) the  encrypted password for
 *       the user,  though because  /etc/passwd is  readable by  everyone,
 *       this  was changed  to make it  harder to dump  password hashes of
 *       user accounts. Nowadays,  the actual password  hashes are  stored
 *       in  /etc/shadow (which  is only  readable by  the superuser), and
 *       in order  to communicate  this fact,  `pw_passwd' is  set to  "x"
 *       Additionally, the following special values for `pw_passwd' exist:
 *  - "*":    No password has yet to be set (assign one with `passwd(1)')
 *  - "*NP*": A shadow record may be obtained from a NIS+ server.
 *  - "":     No password is needed
 *
 * For processing, libc uses `fparseln()' with default with `delim = "\0\0#"'
 *
 * FILES:
 *   - /etc/passwd
 */
struct passwd {
	char   *pw_name;   /* [1..1] Username. */
	char   *pw_passwd; /* [1..1] Password. */
	__uid_t pw_uid;    /* User ID. */
	__gid_t pw_gid;    /* Group ID. */
	char   *pw_gecos;  /* [1..1] Real name. (empty string if not set) */
	char   *pw_dir;    /* [1..1] Home directory. (empty string if not set) */
	char   *pw_shell;  /* [1..1] Shell program. (empty string if not set) */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_DB_PASSWD_H */
