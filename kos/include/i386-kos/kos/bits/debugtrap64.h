/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef _I386_KOS_KOS_BITS_DEBUGTRAP64_H
#define _I386_KOS_KOS_BITS_DEBUGTRAP64_H 1

#include <__stdinc.h>

#include <hybrid/__pointer.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

__DECL_BEGIN

#ifdef __x86_64__
#define __OFFSET_DEBUGTRAP_REASON_SIGNO   __OFFSET_DEBUGTRAP_REASON64_SIGNO
#define __OFFSET_DEBUGTRAP_REASON_REASON  __OFFSET_DEBUGTRAP_REASON64_REASON
#define __OFFSET_DEBUGTRAP_REASON_INTARG  __OFFSET_DEBUGTRAP_REASON64_INTARG
#define __OFFSET_DEBUGTRAP_REASON_STRARG  __OFFSET_DEBUGTRAP_REASON64_STRARG
#define __OFFSET_DEBUGTRAP_REASON_PTRARG  __OFFSET_DEBUGTRAP_REASON64_PTRARG
#define __SIZEOF_DEBUGTRAP_REASON         __SIZEOF_DEBUGTRAP_REASON64
#define debugtrap_reason64 debugtrap_reason
#endif /* __x86_64__ */


#define __OFFSET_DEBUGTRAP_REASON64_SIGNO  0
#define __OFFSET_DEBUGTRAP_REASON64_REASON 8
#define __OFFSET_DEBUGTRAP_REASON64_INTARG 16
#define __OFFSET_DEBUGTRAP_REASON64_STRARG 16
#define __OFFSET_DEBUGTRAP_REASON64_PTRARG 16
#define __SIZEOF_DEBUGTRAP_REASON64        24

#ifdef __CC__
struct debugtrap_reason64 /*[PREFIX(dtr_)]*/ {
	__uint64_t dtr_signo;  /* Trap signal number (one of `SIG*' from <bits/signum.h>) */
	__uint64_t dtr_reason; /* Trap reason (one of `DEBUGTRAP_REASON_*') */
	union {
		__uint64_t                 dtr_intarg; /* Integer argument. */
		__HYBRID_PTR64(char const) dtr_strarg; /* String argument. */
		__HYBRID_PTR64(void)       dtr_ptrarg; /* Pointer argument. */
	};
};
#endif /* __CC__ */

__DECL_END

#endif /* !_I386_KOS_KOS_BITS_DEBUGTRAP64_H */
