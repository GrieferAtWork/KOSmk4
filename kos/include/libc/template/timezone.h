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
#ifndef __LOCAL_timezone
#include <__crt.h>
#ifndef __LOCAL_timezone
__DECL_BEGIN
#ifdef timezone
#define __LOCAL_timezone timezone
#elif defined(_timezone)
#define __LOCAL_timezone _timezone
#elif defined(__timezone)
#define __LOCAL_timezone __timezone
#elif defined(__CRT_HAVE_timezone)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,long,timezone)
#define timezone         timezone
#define __LOCAL_timezone timezone
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,long,__LOCAL_timezone,timezone)
#define __LOCAL_timezone __LOCAL_timezone
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE__timezone)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,long,_timezone)
#define _timezone        _timezone
#define __LOCAL_timezone _timezone
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,long,__LOCAL_timezone,_timezone)
#define __LOCAL_timezone __LOCAL_timezone
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE___timezone)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,long,__timezone)
#define __timezone       __timezone
#define __LOCAL_timezone __timezone
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,long,__LOCAL_timezone,__timezone)
#define __LOCAL_timezone __LOCAL_timezone
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(____p__timezone_defined)
#define __LOCAL_timezone (*__p__timezone())
#elif defined(__CRT_HAVE___p__timezone)
#define ____p__timezone_defined
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,long *,__NOTHROW,__p__timezone,(void),())
#define __LOCAL_timezone (*__p__timezone())
#elif defined(__CRT_HAVE__get_timezone)
#ifndef ___get_timezone_defined
#define ___get_timezone_defined
__CDECLARE(,int,__NOTHROW,_get_timezone,(long *__p_timezone),())
#endif /* !___get_timezone_defined */
#ifndef _____get_timezone_wrapper_defined
#define _____get_timezone_wrapper_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST long
__NOTHROW(__LIBCCALL ___get_timezone_wrapper)(void) {
	long __result;
	if __unlikely(_get_timezone(&__result) != 0)
		__result = 0;
	return __result;
}
#endif /* !_____get_timezone_wrapper_defined */
#define __LOCAL_timezone ___get_timezone_wrapper()
#endif /* ... */
__DECL_END
#endif /* !__LOCAL_timezone */
#endif /* !__LOCAL_timezone */
