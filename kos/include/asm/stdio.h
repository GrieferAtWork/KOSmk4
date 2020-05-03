/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_STDIO_H
#define _ASM_STDIO_H 1

#include <__crt.h>
#include <hybrid/typecore.h>

#define __SEEK_SET  0 /* Seek from beginning of file. */
#define __SEEK_CUR  1 /* Seek from current position. */
#define __SEEK_END  2 /* Seek from end of file. */
#if defined(__KOS__) || defined(__linux__) || defined(__CRT_KOS) || defined(__CRT_KOS_KERNEL) || defined(__CRT_GLC)
#define __SEEK_DATA 3 /* Seek to next data. */
#define __SEEK_HOLE 4 /* Seek to next hole. */
#endif /* __KOS__ || __linux__ || __CRT_KOS || __CRT_KOS_KERNEL || __CRT_GLC */

#define __STDIN_FILENO  0 /* Standard input. */
#define __STDOUT_FILENO 1 /* Standard output. */
#define __STDERR_FILENO 2 /* Standard error output. */

#define __F_OK 0 /* Test for existence. */
#define __X_OK 1 /* Test for execute permission. */
#define __W_OK 2 /* Test for write permission. */
#define __R_OK 4 /* Test for read permission. */

#ifdef __CRT_DOS_PRIMARY
#define ___IOFBF 0x0000 /* Fully buffered. */
#define ___IOLBF 0x0040 /* Line buffered. */
#define ___IONBF 0x0004 /* No buffering. */
#else /* __CRT_DOS_PRIMARY */
#define ___IOFBF 0 /* Fully buffered. */
#define ___IOLBF 1 /* Line buffered. */
#define ___IONBF 2 /* No buffering. */
#endif /* !__CRT_DOS_PRIMARY */

#ifdef __CRT_DOS_PRIMARY
#define __BUFSIZ 512
#else /* __CRT_DOS_PRIMARY */
#define __BUFSIZ 8192
#endif /* !__CRT_DOS_PRIMARY */


#define __EOF    (-1)
#define __WEOF16 (__CCAST(__WINT_TYPE__)__UINT16_C(0xffff))
#define __WEOF32 (__CCAST(__WINT_TYPE__)__UINT32_C(0xffffffff))
#if __SIZEOF_WCHAR_T__ == 4
#define __WEOF __WEOF32
#else /* __SIZEOF_WCHAR_T__ == 4 */
#define __WEOF __WEOF16
#endif /* __SIZEOF_WCHAR_T__ != 4 */


#endif /* !_ASM_STDIO_H */
