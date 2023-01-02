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
#ifndef _ASM_OS_STDIO_H
#define _ASM_OS_STDIO_H 1

#include <__stdinc.h>

#if defined(__KOS__) || defined(__linux__)
#include <asm/os/kos/stdio.h>
#endif /* ... */

#ifndef __SEEK_SET
#define __SEEK_SET  0 /* Seek from beginning of file. */
#endif /* !__SEEK_SET */
#ifndef __SEEK_CUR
#define __SEEK_CUR  1 /* Seek from current position. */
#endif /* !__SEEK_CUR */
#ifndef __SEEK_END
#define __SEEK_END  2 /* Seek from end of file. */
#endif /* !__SEEK_END */

#ifndef __STDIN_FILENO
#define __STDIN_FILENO  0 /* Standard input. */
#endif /* !__STDIN_FILENO */

#ifndef __STDOUT_FILENO
#if __STDIN_FILENO == 0
#define __STDOUT_FILENO 1 /* Standard output. */
#else /* __STDIN_FILENO == 0 */
#define __STDOUT_FILENO (__STDIN_FILENO + 1) /* Standard output. */
#endif /* __STDIN_FILENO != 0 */
#endif /* !__STDOUT_FILENO */

#ifndef __STDERR_FILENO
#if __STDOUT_FILENO == 1
#define __STDERR_FILENO 2 /* Standard error output. */
#else /* __STDOUT_FILENO == 1 */
#define __STDERR_FILENO (__STDOUT_FILENO + 1) /* Standard error output. */
#endif /* __STDOUT_FILENO != 1 */
#endif /* !__STDERR_FILENO */

#if (__STDOUT_FILENO == __STDIN_FILENO + 1 && \
     __STDERR_FILENO == __STDIN_FILENO + 2)
#define __PRIVATE_FOREACH_STDFILENO(fd) \
	for ((fd) = __STDIN_FILENO; (fd) <= __STDERR_FILENO; ++(fd))
#else /* ... */
#define __PRIVATE_FOREACH_STDFILENO(fd)                     \
	for ((fd) = __STDIN_FILENO; (fd) != -1;                 \
	     (fd) = (fd) == __STDIN_FILENO  ? __STDOUT_FILENO : \
	            (fd) == __STDOUT_FILENO ? __STDERR_FILENO : -1)
#endif /* !... */


#ifndef __F_OK
#define __F_OK 0 /* Test for existence. */
#define __X_OK 1 /* Test for execute permission. */
#define __W_OK 2 /* Test for write permission. */
#define __R_OK 4 /* Test for read permission. */
#endif /* !__F_OK */

#endif /* !_ASM_OS_STDIO_H */
