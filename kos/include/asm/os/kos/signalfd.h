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
#ifndef _ASM_OS_KOS_SIGNALFD_H
#define _ASM_OS_KOS_SIGNALFD_H 1

#include <__stdinc.h>

/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

#define __SFD_NONBLOCK 0x0000800 /* Do not block when trying to read data that hasn't been written, yet. */
#define __SFD_CLOEXEC  0x0080000 /* Close the file during exec() */
#ifdef __KOS__
#define __SFD_CLOFORK  0x1000000 /* Close the handle when the file descriptors are unshared (s.a. `CLONE_FILES') */
#endif /* __KOS__ */

#endif /* !_ASM_OS_KOS_SIGNALFD_H */
