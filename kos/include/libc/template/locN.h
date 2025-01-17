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
#ifndef __LOCAL_locN_defined
#define __LOCAL_locN_defined
#include <__crt.h>
#ifndef __LOCAL_loc1
__DECL_BEGIN
#ifdef loc1
#define __LOCAL_loc1 loc1
#elif defined(__CRT_HAVE_loc1)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,char *,loc1)
#define loc1         loc1
#define __LOCAL_loc1 loc1
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,char *,__LOCAL_loc1,loc1)
#define __LOCAL_loc1 __LOCAL_loc1
#endif /* !__NO_COMPILER_SREDIRECT */
#endif /* ... */
__DECL_END
#endif /* !__LOCAL_loc1 */
#ifndef __LOCAL_loc2
__DECL_BEGIN
#ifdef loc2
#define __LOCAL_loc2 loc2
#elif defined(__CRT_HAVE_loc2)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,char *,loc2)
#define loc2         loc2
#define __LOCAL_loc2 loc2
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,char *,__LOCAL_loc2,loc2)
#define __LOCAL_loc2 __LOCAL_loc2
#endif /* !__NO_COMPILER_SREDIRECT */
#endif /* ... */
__DECL_END
#endif /* !__LOCAL_loc2 */
#ifndef __LOCAL_locs
__DECL_BEGIN
#ifdef locs
#define __LOCAL_locs locs
#elif defined(__CRT_HAVE_locs)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,char *,locs)
#define locs         locs
#define __LOCAL_locs locs
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,char *,__LOCAL_locs,locs)
#define __LOCAL_locs __LOCAL_locs
#endif /* !__NO_COMPILER_SREDIRECT */
#endif /* ... */
__DECL_END
#endif /* !__LOCAL_locs */
#endif /* !__LOCAL_locN_defined */
