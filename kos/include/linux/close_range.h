/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Linux (/include/linux/close_range.h) */
#ifndef _LINUX_CLOSE_RANGE_H
#define _LINUX_CLOSE_RANGE_H 1

#include <__stdinc.h>

/* Flags for `close_range(2)' */
#if defined(__linux__) || defined(__KOS__)
#define CLOSE_RANGE_UNSHARE 0x0001 /* Unshare handles first (s.a. `handman_fork_and_closerange()') */
#define CLOSE_RANGE_CLOEXEC 0x0002 /* Don't close files. -- Instead, set the `IO_CLOEXEC' bit for them */
#endif /* __linux__ || __KOS__ */

#endif /* _LINUX_CLOSE_RANGE_H */