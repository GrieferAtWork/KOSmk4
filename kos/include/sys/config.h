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
#ifndef _SYS_CONFIG_H
#define _SYS_CONFIG_H 1
#ifndef _SYS_CONFIG_H_
#define _SYS_CONFIG_H_ 1

#include <__stdinc.h>
#include <hybrid/typecore.h>

/* DISCLAIMER: This file is based off of cygwin's `/usr/include/sys/config.h' */

#if !defined(__KOS__) && __has_include("/usr/local/include/sys/config.h")
#include "/usr/local/include/sys/config.h"
#elif !defined(__KOS__) && __has_include("/usr/include/sys/config.h")
#include "/usr/include/sys/config.h"
#else /* ... */
#include <features.h>
#define __DYNAMIC_REENT__ 1
#define _READ_WRITE_RETURN_TYPE  __SSIZE_TYPE__
#define _READ_WRITE_BUFSIZE_TYPE __SIZE_TYPE__
#define __LINUX_ERRNO_EXTENSIONS__ 1
#endif /* !... */

#ifndef _READ_WRITE_RETURN_TYPE
#define _READ_WRITE_RETURN_TYPE  int
#endif /* !_READ_WRITE_RETURN_TYPE */
#ifndef _READ_WRITE_BUFSIZE_TYPE
#define _READ_WRITE_BUFSIZE_TYPE int
#endif /* !_READ_WRITE_BUFSIZE_TYPE */

#ifndef __size_t_defined
#define __size_t_defined 1
__DECL_BEGIN
typedef __SIZE_TYPE__ size_t;
__DECL_END
#endif /* !__size_t_defined */

#endif /* !_SYS_CONFIG_H_ */
#endif /* !_SYS_CONFIG_H */
