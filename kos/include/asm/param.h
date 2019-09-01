/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_PARAM_H
#define _ASM_PARAM_H 1

#ifndef HZ
#if defined(__KERNEL__) && defined(CONFIG_HZ)
#   define HZ            CONFIG_HZ
#elif 1
#   define HZ            20
#else
#   define HZ            100
#endif
#endif

#ifndef EXEC_PAGESIZE
#include <hybrid/__limits.h>
#define EXEC_PAGESIZE    __SIZEOF_PAGE__
#endif

#ifndef NOGROUP
#define NOGROUP        (-1)
#endif

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN   64 /* max length of hostname. */
#endif

#endif /* !_ASM_PARAM_H */
