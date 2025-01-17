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
#ifndef _ASM_OS_SOLARIS_FILE_IOCTLS_H
#define _ASM_OS_SOLARIS_FILE_IOCTLS_H 1

#include <__stdinc.h>

#include <asm/ioctl.h>

/* Arguments for `_FIODIRECTIO' from <sys/filio.h> */
#define __DIRECTIO_OFF 0 /* Disable optional direct I/O */
#define __DIRECTIO_ON  1 /* Enable optional direct I/O */

#define __FIOLFS                  _IO('f', 64)
#define __FIOLFSS                 _IO('f', 65)
#define __FIOFFS                  _IO('f', 66)
#define __FIOAI                   _IO('f', 67)
#define __FIOOBSOLETE67           __FIOAI
#define __FIOSATIME               _IO('f', 68)
#define __FIOSDIO                 _IO('f', 69)
#define __FIOGDIO                 _IO('f', 70)
#define __FIOIO                   _IO('f', 71)
#define __FIOISLOG                _IO('f', 72)
#define __FIOISLOGOK              _IO('f', 73)
#define __FIOLOGRESET             _IO('f', 74)
#define __FIOISBUSY               _IO('f', 75)
#define __FIODIRECTIO             _IO('f', 76) /* Enable/disable optional direct I/O */
#define __FIOTUNE                 _IO('f', 77)
#define __FIOLOGENABLE            _IO('f', 87)
#define __FIOLOGDISABLE           _IO('f', 88)
#define __FIOSNAPSHOTCREATE       _IO('f', 89)
#define __FIOSNAPSHOTDELETE       _IO('f', 90)
#define __FIOGETSUPERBLOCK        _IO('f', 91)
#define __FIOGETMAXPHYS           _IO('f', 92)
#define __FIO_SET_LUFS_DEBUG      _IO('f', 93)
#define __FIO_SET_LUFS_ERROR      _IO('f', 94)
#define __FIO_GET_TOP_STATS       _IO('f', 95)
#define __FIOSNAPSHOTCREATE_MULTI _IO('f', 96)
#define __FIO_SEEK_DATA           _IO('f', 97)
#define __FIO_SEEK_HOLE           _IO('f', 98)
#define __FIO_COMPRESSED          _IO('f', 99)

#endif /* !_ASM_OS_SOLARIS_FILE_IOCTLS_H */
