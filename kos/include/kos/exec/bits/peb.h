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
#ifndef _KOS_EXEC_BITS_PEB_H
#define _KOS_EXEC_BITS_PEB_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#define OFFSET_PROCESS_PEB_ARGC 0
#define OFFSET_PROCESS_PEB_ARGV (__SIZEOF_POINTER__)
#define OFFSET_PROCESS_PEB_ENVC (2 * __SIZEOF_POINTER__)
#define OFFSET_PROCESS_PEB_ENVP (3 * __SIZEOF_POINTER__)

#ifdef __CC__
__DECL_BEGIN

struct process_peb /*[PREFIX(pp_)]*/ {
	__SIZE_TYPE__ pp_argc;  /* Number of arguments passed to the program. */
	char        **pp_argv;  /* [1..pp_argc] Vector of argument strings (NOTE: pp_argv[pp_argc] == NULL). */
	__SIZE_TYPE__ pp_envc;  /* Number of environment strings passed to the program. */
	char        **pp_envp;  /* [1..pp_envc] Vector of environment strings (NOTE: pp_envv[pp_envc] == NULL). */
	/* ... Additional (possibly arch-specific) data goes here. */
//	char         *pp_argv_vector[pp_argc]; /* [pp_argc + 1] Vector of pointers to argument strings */
//	char         *pp_envp_vector[pp_argp]; /* [pp_envc + 1] Vector of pointers to environment strings */
//	char          pp_argv_strings[];       /* Buffer containing argument strings */
//	char          pp_envp_strings[];       /* Buffer containing environment strings */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_EXEC_BITS_PEB_H */
