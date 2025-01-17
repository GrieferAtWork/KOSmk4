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
#ifndef _KOS_COREDUMP_H
#define _KOS_COREDUMP_H 1

#include <__stdinc.h>

#include <kos/bits/coredump.h> /* union coredump_info */

#include <libunwind/errno.h> /* UNWIND_* */


/* Coredump message string limits.
 * WARNING: These values are used as alloca() limits, so don't set
 *          them too high, or else user-space may be able to cause
 *          a kernel-space stack overflow... */
#define COREDUMP_ASSERT_EXPR_MAXLEN 512  /* ci_assert.ca_expr */
#define COREDUMP_ASSERT_FILE_MAXLEN 512  /* ci_assert.ca_file */
#define COREDUMP_ASSERT_FUNC_MAXLEN 256  /* ci_assert.ca_func */
#define COREDUMP_ASSERT_MESG_MAXLEN 2048 /* ci_assert.ca_mesg */
#define COREDUMP_ABORTF_MESG_MAXLEN 2048 /* ci_abrtmsg */
#define COREDUMP_DLERROR_MAXLEN     2048 /* ci_dlerror */
#define COREDUMP_TRACEBACK_LIMIT    128  /* Max # of extended traceback entries. */


#define COREDUMP_INFO_ISEXCEPT(unwind_error)  \
	((unwind_error) != UNWIND_SUCCESS &&      \
	 (unwind_error) != UNWIND_USER_DLERROR && \
	 (unwind_error) != UNWIND_USER_ASSERT &&  \
	 (unwind_error) != UNWIND_USER_ACHECK &&  \
	 (unwind_error) != UNWIND_USER_ABORT)
#define COREDUMP_INFO_ISSIGNAL(unwind_error) \
	((unwind_error) == UNWIND_SUCCESS)
#define COREDUMP_INFO_ISDLERROR(unwind_error) \
	((unwind_error) == UNWIND_USER_DLERROR)
#define COREDUMP_INFO_ISABORT(unwind_error) \
	((unwind_error) == UNWIND_USER_ABORT)
#define COREDUMP_INFO_ISASSERT(unwind_error) \
	((unwind_error) == UNWIND_USER_ASSERT || \
	 (unwind_error) == UNWIND_USER_ACHECK)

#endif /* !_KOS_COREDUMP_H */
