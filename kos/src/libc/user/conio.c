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
#ifndef GUARD_LIBC_USER_CONIO_C
#define GUARD_LIBC_USER_CONIO_C 1

#include "../api.h"
/**/

#include <bits/crt/io-file.h>
#include <kos/io.h>
#include <kos/syscalls.h>

#include <stdio.h>

#include "../libc/globals.h"
#include "conio.h"

DECL_BEGIN

/*[[[head:libc__kbhit,hash:CRC-32=0xcb5aaa5b]]]*/
INTERN ATTR_SECTION(".text.crt.dos.conio") WUNUSED int
NOTHROW(LIBCCALL libc__kbhit)(void)
/*[[[body:libc__kbhit]]]*/
{
	int result = 0;
	FILE *fp = stdtty;
	flockfile(fp);
	if (fp->if_cnt == 0) {
		/* Ask the OS for pending input. */
		char kb[1];
		fd_t fd = fileno_unlocked(fp);
		ssize_t ok;
		/* Do a non-blocking read from the underlying file descriptor (KOS-specific system call). */
		ok = sys_readf(fd, kb, sizeof(kb), IO_NONBLOCK);
		if (ok > 0) {
			/* Unread the read byte int the file's buffer. */
			ungetc_unlocked(kb[0], fp);

			/* Indicate that input is available. */
			result = 1;
		}
	} else {
		/* Pending input is present. */
		result = 1;
	}
	funlockfile(fp);
	return result;
}
/*[[[end:libc__kbhit]]]*/

/*[[[start:exports,hash:CRC-32=0xd0266c61]]]*/
DEFINE_PUBLIC_ALIAS_P(_kbhit,libc__kbhit,WUNUSED,int,NOTHROW,LIBCCALL,(void),());
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_CONIO_C */
