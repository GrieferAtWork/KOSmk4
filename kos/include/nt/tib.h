/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
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

#include <hybrid/typecore.h>

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
} NT_TIB;
typedef NT_TIB *PNT_TIB;
#endif /* _NT_TIB_DEFINED */

__DECL_END
#endif /* __CC__ */

#endif /* !_NT_TIB_H */
