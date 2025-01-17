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
#ifndef GUARD_LIBKERNEL32_NAMEDPIPEAPI_C
#define GUARD_LIBKERNEL32_NAMEDPIPEAPI_C 1
#define _AT_SOURCE 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "api.h"
/**/

#include <hybrid/minmax.h>

#include <kos/ioctl/pipe.h>
#include <kos/types.h>
#include <nt/handleapi.h>
#include <nt/namedpipeapi.h>
#include <sys/ioctl.h>

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

DECL_BEGIN

/************************************************************************/
INTERN WINBOOL WINAPI
libk32_CreatePipe(PHANDLE hReadPipe, PHANDLE hWritePipe,
                  LPSECURITY_ATTRIBUTES lpPipeAttributes, DWORD nSize) {
	fd_t fds[2];
	TRACE("CreatePipe(%p, %p, %p, %#x)",
	      hReadPipe, hWritePipe, lpPipeAttributes, nSize);
	(void)lpPipeAttributes;
	(void)nSize;
	if (pipe2(fds, O_CLOEXEC) != 0)
		return FALSE;
	*hReadPipe  = NTHANDLE_FROMFD(fds[0]);
	*hWritePipe = NTHANDLE_FROMFD(fds[1]);
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_PeekNamedPipe(HANDLE hNamedPipe, LPVOID lpBuffer,
                     DWORD nBufferSize, LPDWORD lpBytesRead,
                     LPDWORD lpTotalBytesAvail,
                     LPDWORD lpBytesLeftThisMessage) {
	struct pipe_peek peek;
	TRACE("PeekNamedPipe(%p, %p, %#x, %p, %p, %p)",
	      hNamedPipe, lpBuffer, nBufferSize, lpBytesRead,
	      lpTotalBytesAvail, lpBytesLeftThisMessage);
	if (!NTHANDLE_ISFD(hNamedPipe)) {
		errno = EBADF;
		return FALSE;
	}
	bzero(&peek, sizeof(peek));
	peek.pp_buf   = lpBuffer;
	peek.pp_bufof = 0;
	peek.pp_bufsz = lpBuffer ? nBufferSize : 0;
	if (ioctl(NTHANDLE_ASFD(hNamedPipe), PIPE_IOC_PEEK, &peek) < 0)
		return FALSE;
	if (lpBytesRead)
		*lpBytesRead = MIN(nBufferSize, peek.pp_bufsz);
	if (lpTotalBytesAvail)
		*lpTotalBytesAvail = peek.pp_bufsz;
	if (lpBytesLeftThisMessage)
		*lpBytesLeftThisMessage = peek.pp_bufsz;
	return TRUE;
}

DEFINE_PUBLIC_ALIAS(CreatePipe, libk32_CreatePipe);
DEFINE_PUBLIC_ALIAS(PeekNamedPipe, libk32_PeekNamedPipe);
/************************************************************************/

DECL_END

#endif /* !GUARD_LIBKERNEL32_NAMEDPIPEAPI_C */
