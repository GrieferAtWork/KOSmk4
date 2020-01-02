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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _NEWLIB_VERSION_H__
#define _NEWLIB_VERSION_H__ 1

/* DISCLAIMER: This file is based off of cygwin's `/usr/include/_newlib_version.h' */

#include <__stdinc.h>

#if defined(__CYGWIN__) || defined(__CYGWIN32__)
#if __has_include("/usr/local/include/_newlib_version.h")
#include "/usr/local/include/_newlib_version.h"
#elif __has_include("/usr/include/_newlib_version.h")
#include "/usr/include/_newlib_version.h"
#endif
#endif /* __CYGWIN__ || __CYGWIN32__ */

#ifndef _NEWLIB_VERSION
#define _NEWLIB_VERSION      "2.5.0"
#define __NEWLIB__            2
#define __NEWLIB_MINOR__      5
#define __NEWLIB_PATCHLEVEL__ 0
#endif /* !_NEWLIB_VERSION */

#endif /* !_NEWLIB_VERSION_H__ */
