/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBKERNEL32_STARTUP_C
#define GUARD_LIBKERNEL32_STARTUP_C 1
#define _KOS_SOURCE 1

#include "api.h"

#include <nt/handleapi.h>
#include <nt/startup.h>

#include <assert.h>
#include <string.h>
#include <unistd.h>

DECL_BEGIN

/************************************************************************/
static_assert(sizeof(STARTUPINFOA) == sizeof(STARTUPINFOW));

INTERN VOID WINAPI
libk32_GetStartupInfo(LPSTARTUPINFO lpStartupInfo) {
	TRACE("GetStartupInfo(%p)", lpStartupInfo);
	bzero(lpStartupInfo, sizeof(*lpStartupInfo));
	lpStartupInfo->cb         = sizeof(*lpStartupInfo);
	lpStartupInfo->dwFlags    = STARTF_USESTDHANDLES;
	lpStartupInfo->hStdInput  = NTHANDLE_FROMFD(STDIN_FILENO);
	lpStartupInfo->hStdOutput = NTHANDLE_FROMFD(STDOUT_FILENO);
	lpStartupInfo->hStdError  = NTHANDLE_FROMFD(STDERR_FILENO);
}

DEFINE_PUBLIC_ALIAS(GetStartupInfoA, libk32_GetStartupInfo);
DEFINE_PUBLIC_ALIAS(GetStartupInfoW, libk32_GetStartupInfo);
/************************************************************************/

DECL_END

#endif /* !GUARD_LIBKERNEL32_STARTUP_C */
