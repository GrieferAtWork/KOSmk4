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
#ifndef __GUARD_HYBRID___LIMITS_H
#define __GUARD_HYBRID___LIMITS_H 1

#include "host.h"

#ifndef __SIZEOF_PAGE__
#ifdef __PAGESIZE
#define __SIZEOF_PAGE__        __PAGESIZE
#elif defined(PAGESIZE)
#define __SIZEOF_PAGE__        PAGESIZE
#elif defined(__i386__) || defined(__x86_64__) || defined(__arm__)
#define __SIZEOF_PAGE__        4096
#endif
#endif /* !__SIZEOF_PAGE__ */

#ifndef __SIZEOF_CACHELINE__
#ifdef __CACHELINE
#   define __SIZEOF_CACHELINE__  __CACHELINE
#elif defined(CACHELINE)
#   define __SIZEOF_CACHELINE__  CACHELINE
#elif defined(__i386__) || defined(__x86_64__)
#   define __SIZEOF_CACHELINE__  64
#elif 0
#   define __SIZEOF_CACHELINE__  64 /* Just guess... */
#endif
#endif /* __SIZEOF_CACHELINE__ */

#ifndef __ATTR_CACHELINE_ALIGNED
#ifdef __SIZEOF_CACHELINE__
#define __ATTR_CACHELINE_ALIGNED __ATTR_ALIGNED(__SIZEOF_CACHELINE__)
#else /* __SIZEOF_CACHELINE__ */
#define __ATTR_CACHELINE_ALIGNED /* nothing */
#endif /* !__SIZEOF_CACHELINE__ */
#endif /* !__ATTR_CACHELINE_ALIGNED */

#endif /* !__GUARD_HYBRID___LIMITS_H */
