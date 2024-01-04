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
#ifndef _KOS_EXEC_PEB_H
#define _KOS_EXEC_PEB_H 1

#include <__stdinc.h>

#include <bits/types.h>
#include <kos/exec/bits/peb.h>

#include <libc/string.h>

/* Information about data passed by the kernel following an exec() system  call.
 * These are the data structures and formats for information about where to find
 * argc+argv, as well as environ, in  addition to specific information given  to
 * the dynamic linker program (even though in the case of KOS, the RTLD is hard-
 * coded as a simple one-segment application always loaded from kernel-memory) */

#ifdef __CC__
__DECL_BEGIN

#if defined(__KOS__) && !defined(__KERNEL__)
#ifndef ____peb_defined
#define ____peb_defined
/* The PEB of the current process. */
__LIBC struct process_peb __peb;
#endif /* !____peb_defined */
#endif /* __KOS__ && !__KERNEL__ */

/* Helper functions to lookup an environment variable within a given PEB. */
__LOCAL __ATTR_WUNUSED char *
__NOTHROW_NCX(__LIBCCALL process_peb_getenv)(struct process_peb *__restrict self,
                                             char const *__restrict varname) {
	char **iter, *env;
	__size_t varlen = __libc_strlen(varname);
	/* Search for the matching environment variable. */
	for (iter = self->pp_envp; (env = *iter) != __NULLPTR; ++iter) {
		if (__libc_memcmp(env, varname, varlen * sizeof(char)) != 0)
			continue;
		if (env[varlen] != '=')
			continue;
		return env + varlen + 1;
	}
	return __NULLPTR;
}


__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_EXEC_PEB_H */
