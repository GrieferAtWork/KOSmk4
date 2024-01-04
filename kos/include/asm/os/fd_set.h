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
#ifndef _ASM_OS_FD_SET_H
#define _ASM_OS_FD_SET_H 1

#include <__stdinc.h>

/* Optional, os-specific override for `__FD_SETSIZE', which is 1 plus
 * the max FD which may be stored in a `fd_set' from `<sys/select.h>'
 *
 * If not defined, defaults to 1024 */

#ifndef __FD_SETSIZE
#define __FD_SETSIZE 1024
#endif /* !__FD_SETSIZE */

#endif /* !_ASM_OS_FD_SET_H */
