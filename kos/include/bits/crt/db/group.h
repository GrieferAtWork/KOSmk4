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
#ifndef _BITS_CRT_DB_GROUP_H
#define _BITS_CRT_DB_GROUP_H 1

#include <__stdinc.h>

#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

/*
 * C structure for describing a password database entry from /etc/group
 *
 * Every line from /etc/group that isn't empty, or a comment will match
 * exactly one of the following formats:
 *
 *    gr_name:gr_passwd:gr_gid
 *    gr_name:gr_passwd:gr_gid:gr_mem[0],gr_mem[1],...
 *
 * For processing, libc uses `fparseln()' with default with `delim = "\0\0#"'
 *
 * FILES:
 *   - /etc/group
 */
struct group {
	char   *gr_name;   /* [1..1] Group name. */
	char   *gr_passwd; /* [1..1] Password. */
	__gid_t gr_gid;    /* Group ID. */
	char  **gr_mem;    /* [0..1][1..1] Member list. (`NULL' is used as sentinel) */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_DB_GROUP_H */
