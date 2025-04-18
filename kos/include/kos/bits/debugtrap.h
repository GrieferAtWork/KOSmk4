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
/*!replace_with_include <kos/debugtrap.h>*/
#ifndef _KOS_BITS_DEBUGTRAP_H
#define _KOS_BITS_DEBUGTRAP_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#define __OFFSET_DEBUGTRAP_REASON_SIGNO  0
#define __OFFSET_DEBUGTRAP_REASON_REASON 4
#define __OFFSET_DEBUGTRAP_REASON_INTARG 8
#define __OFFSET_DEBUGTRAP_REASON_STRARG 8
#define __OFFSET_DEBUGTRAP_REASON_PTRARG 8
#define __SIZEOF_DEBUGTRAP_REASON (8 + __SIZEOF_POINTER__)

#ifdef __CC__
__DECL_BEGIN

struct debugtrap_reason /*[PREFIX(dtr_)]*/ {
	__uint32_t dtr_signo;  /* Trap signal number (one of `SIG*' from <signal.h>) */
	__uint32_t dtr_reason; /* Trap reason (one of `DEBUGTRAP_REASON_*') */
	union {
		__uintptr_t dtr_intarg; /* Integer argument. */
		char const *dtr_strarg; /* String argument. */
		void       *dtr_ptrarg; /* Pointer argument. */
	};
};

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_BITS_DEBUGTRAP_H */
