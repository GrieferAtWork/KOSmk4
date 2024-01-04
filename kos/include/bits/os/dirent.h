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
#ifndef _BITS_OS_DIRENT_H
#define _BITS_OS_DIRENT_H 1

/* File:
 *    <bits/os/dirent.h>
 *
 * Definitions:
 *    struct dirent {
 *        ...
 *    };
 *    #ifdef    __USE_LARGEFILE64
 *    #define __dirent64 dirent64
 *    struct dirent64 {
 *        ...
 *    };
 *    #else // __USE_LARGEFILE64
 *    struct __dirent64 {
 *        ...
 *    };
 *    #endif // __USE_LARGEFILE64
 */

#include <__stdinc.h>
#include <__crt.h> /* __CRT_DOS_PRIMARY */

/**/
#ifdef __CRT_DOS_PRIMARY
#include <bits/os/dos/dirent.h>
#else /* __CRT_DOS_PRIMARY */
#include <bits/os/kos/dirent.h>
#endif /* !__CRT_DOS_PRIMARY */

#ifdef _DIRENT_HAVE_D_FILENO
#ifndef d_fileno
#define d_fileno d_fileno
#endif /* !d_fileno */
#endif /* _DIRENT_HAVE_D_FILENO */

#endif /* !_BITS_OS_DIRENT_H */
