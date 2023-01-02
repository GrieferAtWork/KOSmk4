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
#ifndef __LOCAL_dstbias
#include <__crt.h>
#ifndef __LOCAL_dstbias
#include <hybrid/typecore.h>
__DECL_BEGIN
#ifdef _dstbias
#define __LOCAL_dstbias _dstbias
#elif defined(__dstbias)
#define __LOCAL_dstbias __dstbias
#elif defined(__CRT_HAVE__dstbias)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,__LONG32_TYPE__,_dstbias)
#define _dstbias        _dstbias
#define __LOCAL_dstbias _dstbias
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,__LONG32_TYPE__,__LOCAL_dstbias,_dstbias)
#define __LOCAL_dstbias __LOCAL_dstbias
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE___dstbias)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,__LONG32_TYPE__,__dstbias)
#define __dstbias       __dstbias
#define __LOCAL_dstbias __dstbias
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,__LONG32_TYPE__,__LOCAL_dstbias,__dstbias)
#define __LOCAL_dstbias __LOCAL_dstbias
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(____p__dstbias_defined)
#define __LOCAL_dstbias (*__p__dstbias())
#elif defined(__CRT_HAVE___p__dstbias)
#define ____p__dstbias_defined
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,__LONG32_TYPE__ *,__NOTHROW,__p__dstbias,(void),())
#define __LOCAL_dstbias (*__p__dstbias())
#elif defined(__CRT_HAVE__get_dstbias)
#ifndef ___get_dstbias_defined
#define ___get_dstbias_defined
__CDECLARE(,int,__NOTHROW,_get_dstbias,(__LONG32_TYPE__ *__p_dstbias),())
#endif /* !___get_dstbias_defined */
#ifndef _____get_dstbias_wrapper_defined
#define _____get_dstbias_wrapper_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __LONG32_TYPE__
__NOTHROW(__LIBCCALL ___get_dstbias_wrapper)(void) {
	__LONG32_TYPE__ __result;
	if __unlikely(_get_dstbias(&__result) != 0)
		__result = 0;
	return __result;
}
#endif /* !_____get_dstbias_wrapper_defined */
#define __LOCAL_dstbias ___get_dstbias_wrapper()
#endif /* ... */
__DECL_END
#endif /* !__LOCAL_dstbias */
#endif /* !__LOCAL_dstbias */
