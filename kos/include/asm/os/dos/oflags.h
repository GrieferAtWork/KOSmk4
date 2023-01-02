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
#ifndef _ASM_OS_DOS_OFLAGS_H
#define _ASM_OS_DOS_OFLAGS_H 1

#include <__stdinc.h>

/************************************************************************/
/* DOS/MSVCRT                                                           */
/************************************************************************/
#define __O_ACCMODE      0x00003 /* Mask for access modes (O_RDONLY, O_WRONLY, O_RDWR) */
#define __O_RDONLY       0x00000 /* Read-only file access */
#define __O_WRONLY       0x00001 /* Write-only file access */
#define __O_RDWR         0x00002 /* Read/Write file access */
#define __O_APPEND       0x00008 /* Always append data to the end of the file */
#define __O_RANDOM       0x00010 /* Ignored */
#define __O_SEQUENTIAL   0x00020 /* Ignored */
#define __O_TMPFILE      0x00040 /* Open a temporary file */
#define __O_CLOEXEC      0x00080 /* Close the file during exec() */
#define __O_CREAT        0x00100 /* If missing, create a new file */
#define __O_TRUNC        0x00200 /* Truncate (clear) the named file if it already exists,
                                  * and  `O_WRONLY'  or  `O_RDWR'  access  is  specified. */
#define __O_EXCL         0x00400 /* When used with `O_CREAT', throw an `E_FSERROR_FILE_ALREADY_EXISTS'
                                  * exception if the file already exists. */
#define __O_SHORT_LIVED  0x01000 /* Ignored */
#define __O_OBTAIN_DIR   0x02000 /* Similar to `O_DIRECTORY'  (while `O_DIRECTORY'  requires that  the
                                  * named file be a  directory, this flag will  _allow_ it to be  one)
                                  * However, when it comes to the use-cases, this flag usually ends up
                                  * being used in the same places. */
#define __O_TEXT         0x04000 /* ??? */
#define __O_BINARY       0x08000 /* ??? */
#define __O_WTEXT        0x10000 /* ??? */
#define __O_U16TEXT      0x20000 /* ??? */
#define __O_U8TEXT       0x40000 /* ??? */
#define __O_NOCTTY       0x00000 /* Concept doesn't exist under DOS */
#define __O_ANYTHING     __O_OBTAIN_DIR

#endif /* !_ASM_OS_DOS_OFLAGS_H */
