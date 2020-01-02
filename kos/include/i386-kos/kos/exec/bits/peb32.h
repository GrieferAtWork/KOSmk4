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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_KOS_EXEC_BITS_PEB32_H
#define _I386_KOS_KOS_EXEC_BITS_PEB32_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>
#include <hybrid/__pointer.h>
#include <hybrid/host.h>

__DECL_BEGIN

#ifndef __x86_64__
#define OFFSET_PROCESS_PEB_ARGC OFFSET_PROCESS_PEB32_ARGC
#define OFFSET_PROCESS_PEB_ARGV OFFSET_PROCESS_PEB32_ARGV
#define OFFSET_PROCESS_PEB_ENVC OFFSET_PROCESS_PEB32_ENVC
#define OFFSET_PROCESS_PEB_ENVP OFFSET_PROCESS_PEB32_ENVP
#define process_peb32           process_peb
#endif /* !__x86_64__ */


#define OFFSET_PROCESS_PEB32_ARGC 0
#define OFFSET_PROCESS_PEB32_ARGV 4
#define OFFSET_PROCESS_PEB32_ENVC 8
#define OFFSET_PROCESS_PEB32_ENVP 12
#ifdef __CC__
struct process_peb32 /*[PREFIX(pp_)]*/ {
	__UINT32_TYPE__                      pp_argc;  /* Number of arguments passed to the program. */
	__HYBRID_PTR32(__HYBRID_PTR32(char)) pp_argv;  /* [1..pp_argc] Vector of argument strings (NOTE: pp_argv[pp_argc] == NULL). */
	__UINT32_TYPE__                      pp_envc;  /* Number of environment strings passed to the program. */
	__HYBRID_PTR32(__HYBRID_PTR32(char)) pp_envp;  /* [1..pp_envc] Vector of environment strings (NOTE: pp_envv[pp_envc] == NULL). */
	/* ... Possibly additional (maybe arch-specific) data goes here. */
//	__HYBRID_PTR32(char)                 pp_argv_vector[pp_argc]; /* [pp_argc + 1] Vector of pointers to argument strings */
//	__HYBRID_PTR32(char)                 pp_envp_vector[pp_argp]; /* [pp_envc + 1] Vector of pointers to environment strings */
//	char                                 pp_argv_strings[];       /* Buffer containing argument strings */
//	char                                 pp_envp_strings[];       /* Buffer containing environment strings */
};
#endif /* __CC__ */

__DECL_END

#endif /* !_I386_KOS_KOS_EXEC_BITS_PEB32_H */
