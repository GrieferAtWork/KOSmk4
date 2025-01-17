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
#ifndef _BITS_OS_KOS_PTRACE_H
#define _BITS_OS_KOS_PTRACE_H 1

#include <__stdinc.h>

#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("off")
#pragma push_macro("flags")
#pragma push_macro("nr")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef off
#undef flags
#undef nr
/* Arguments for PTRACE_PEEKSIGINFO. */
struct __ptrace_peeksiginfo_args {
	__uint64_t off;   /* From which siginfo to start. */
	__uint32_t flags; /* Flags for peeksiginfo. */
	__int32_t  nr;    /* How many siginfos to take. */
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("nr")
#pragma pop_macro("flags")
#pragma pop_macro("off")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_PTRACE_H */
