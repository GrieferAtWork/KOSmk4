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
#ifndef _NT_TIB_H
#define _NT_TIB_H 1

#include "__stdinc.h"
/**/

#include "types.h"
/**/

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#if defined(__i386__) || defined(__x86_64__)
#include <kos/bits/thread.h>
#endif /* __i386__ || __x86_64__ */

/* Thread Information Block (mainly for SEH) */

#ifdef __CC__
__DECL_BEGIN

struct _EXCEPTION_REGISTRATION_RECORD;

#ifndef _NT_TIB_DEFINED
#define _NT_TIB_DEFINED
__C89_NAMELESS typedef struct _NT_TIB {
	struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList;
	PVOID StackBase;
	PVOID StackLimit;
	PVOID SubSystemTib;
	__C89_NAMELESS union {
		PVOID FiberData;
		DWORD Version;
	};
	PVOID ArbitraryUserPointer;
	struct _NT_TIB *Self;
	/* BELOW: https://en.wikipedia.org/wiki/Win32_Thread_Information_Block */
	PVOID _UnknownName_EnvironmentPointer;
	PVOID _UnknownName_ProcessIdOrDebugContext;
	PVOID _UnknownName_ThreadId;
	PVOID _UnknownName_ActiveRpcHandle;
	void **NativePeTlsArray; /* Used for native PE TLS memory. */
} NT_TIB;
typedef NT_TIB *PNT_TIB;

#ifdef __x86_64__
#define _GetTibFieldEx(bwlq, offset) __rdgs##bwlq(offset)
#define _SetTib(addr)                __x86_fast_wrgsbase(addr)
#elif defined(__i386__)
#define _GetTibFieldEx(bwlq, offset) __rdfs##bwlq(offset)
#define _SetTib(addr)                __x86_fast_wrfsbase(addr)
#endif /* ... */
#define _GetTib()              ((NT_TIB *)_GetTibFieldEx(ptr, __builtin_offsetof(NT_TIB, Self)))
#define _GetNativePeTlsArray() ((void **)_GetTibFieldEx(ptr, __builtin_offsetof(NT_TIB, NativePeTlsArray)))

#endif /* _NT_TIB_DEFINED */

__DECL_END
#endif /* __CC__ */

#endif /* !_NT_TIB_H */
