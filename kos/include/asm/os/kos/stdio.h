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
/*!replace_with_include <asm/os/stdio.h>*/
#ifndef _ASM_OS_KOS_STDIO_H
#define _ASM_OS_KOS_STDIO_H 1

#include <__stdinc.h>

/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

#define __SEEK_SET  0 /* Seek from beginning of file. */
#define __SEEK_CUR  1 /* Seek from current position. */
#define __SEEK_END  2 /* Seek from end of file. */
#define __SEEK_DATA 3 /* Seek to next data. */
#define __SEEK_HOLE 4 /* Seek to next hole. */


/* Flags for `renameat2(2)' */
#define __RENAME_NOREPLACE 0x01 /* Don't overwrite target */
#define __RENAME_EXCHANGE  0x02 /* Exchange source and dest */
#define __RENAME_WHITEOUT  0x04 /* Whiteout source */
#ifdef __KOS__
#define __RENAME_MOVETODIR 0x80 /* If `newpath' is a directory, move `oldpath' into it. */
#endif /* __KOS__ */


#endif /* !_ASM_OS_KOS_STDIO_H */
