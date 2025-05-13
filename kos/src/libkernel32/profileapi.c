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
#ifndef GUARD_LIBKERNEL32_PROFILEAPI_C
#define GUARD_LIBKERNEL32_PROFILEAPI_C 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <nt/__stdinc.h>
#include <nt/profileapi.h>
#include <nt/types.h>
#include <sys/time.h>

#include <stddef.h>
#include <stdint.h>

DECL_BEGIN

/************************************************************************/
INTERN WINBOOL WINAPI
libk32_QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount) {
	struct timeval tv;
	TRACE("QueryPerformanceCounter(%p)", lpPerformanceCount);
	if (gettimeofday(&tv, NULL) != 0)
		return FALSE;
	lpPerformanceCount->QuadPart = ((uint64_t)tv.tv_sec * 1000000) +
	                               ((uint64_t)tv.tv_usec);
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency) {
	TRACE("QueryPerformanceFrequency(%p)", lpFrequency);
	lpFrequency->QuadPart = 1000000;
	return TRUE;
}

DEFINE_PUBLIC_ALIAS(QueryPerformanceCounter, libk32_QueryPerformanceCounter);
DEFINE_PUBLIC_ALIAS(QueryPerformanceFrequency, libk32_QueryPerformanceFrequency);
/************************************************************************/

DECL_END

#endif /* !GUARD_LIBKERNEL32_PROFILEAPI_C */
