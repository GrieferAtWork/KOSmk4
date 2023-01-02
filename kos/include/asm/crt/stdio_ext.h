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
#ifndef _ASM_CRT_STDIO_EXT_H
#define _ASM_CRT_STDIO_EXT_H 1

#include <__crt.h>

#define __FSETLOCKING_QUERY    0 /* Query current state of the locking status. */
#define __FSETLOCKING_INTERNAL 1 /* The library protects  all uses  of the stream  functions, except  for
                                  * uses of the *_unlocked functions, by calls equivalent to flockfile(). */
#define __FSETLOCKING_BYCALLER 2 /* The user will take care of locking.
                                  * This is the equivalent of `__USE_STDIO_UNLOCKED' on a per-file basis. */

#endif /* !_ASM_CRT_STDIO_EXT_H */
