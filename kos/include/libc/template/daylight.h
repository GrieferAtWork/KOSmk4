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
#ifndef __LOCAL_daylight
#include <__crt.h>
#ifndef __LOCAL_daylight
__DECL_BEGIN
#ifdef daylight
#define __LOCAL_daylight daylight
#elif defined(_daylight)
#define __LOCAL_daylight _daylight
#elif defined(__daylight)
#define __LOCAL_daylight __daylight
#elif defined(__CRT_HAVE_daylight)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,int,daylight)
#define daylight         daylight
#define __LOCAL_daylight daylight
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,int,__LOCAL_daylight,daylight)
#define __LOCAL_daylight __LOCAL_daylight
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE__daylight)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,int,_daylight)
#define _daylight        _daylight
#define __LOCAL_daylight _daylight
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,int,__LOCAL_daylight,_daylight)
#define __LOCAL_daylight __LOCAL_daylight
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE___daylight)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,int,__daylight)
#define __daylight       __daylight
#define __LOCAL_daylight __daylight
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,int,__LOCAL_daylight,__daylight)
#define __LOCAL_daylight __LOCAL_daylight
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(____p__daylight_defined)
#define __LOCAL_daylight (*__p__daylight())
#elif defined(__CRT_HAVE___p__daylight)
#define ____p__daylight_defined
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,int *,__NOTHROW,__p__daylight,(void),())
#define __LOCAL_daylight (*__p__daylight())
#elif defined(__CRT_HAVE__get_daylight)
#ifndef ___get_daylight_defined
#define ___get_daylight_defined
__CDECLARE(,int,__NOTHROW,_get_daylight,(int *__p_daylight),())
#endif /* !___get_daylight_defined */
#ifndef _____get_daylight_wrapper_defined
#define _____get_daylight_wrapper_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST int
__NOTHROW(__LIBCCALL ___get_daylight_wrapper)(void) {
	int __result;
	if __unlikely(_get_daylight(&__result) != 0)
		__result = 0;
	return __result;
}
#endif /* !_____get_daylight_wrapper_defined */
#define __LOCAL_daylight ___get_daylight_wrapper()
#endif /* ... */
__DECL_END
#endif /* !__LOCAL_daylight */
#endif /* !__LOCAL_daylight */
