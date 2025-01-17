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
#ifndef __LOCAL_environ
#include <__crt.h>
#ifndef __LOCAL_environ
__DECL_BEGIN
#ifdef environ
#define __LOCAL_environ environ
#elif defined(_environ)
#define __LOCAL_environ _environ
#elif defined(__environ)
#define __LOCAL_environ __environ
#elif defined(__CRT_HAVE_environ)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,char **,environ)
#define environ         environ
#define __LOCAL_environ environ
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,char **,__LOCAL_environ,environ)
#define __LOCAL_environ __LOCAL_environ
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE__environ)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,char **,_environ)
#define _environ        _environ
#define __LOCAL_environ _environ
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,char **,__LOCAL_environ,_environ)
#define __LOCAL_environ __LOCAL_environ
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE___environ)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,char **,__environ)
#define __environ       __environ
#define __LOCAL_environ __environ
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,char **,__LOCAL_environ,__environ)
#define __LOCAL_environ __LOCAL_environ
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(____p__environ_defined)
#define __LOCAL_environ (*__p__environ())
#elif defined(__CRT_HAVE___p__environ)
#define ____p__environ_defined
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,char ***,__NOTHROW,__p__environ,(void),())
#define __LOCAL_environ (*__p__environ())
#elif defined(__CRT_HAVE__get_environ)
#ifndef ___get_environ_defined
#define ___get_environ_defined
__CDECLARE(,int,__NOTHROW,_get_environ,(char ***__p_environ),())
#endif /* !___get_environ_defined */
#ifndef _____get_environ_wrapper_defined
#define _____get_environ_wrapper_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST char **
__NOTHROW(__LIBCCALL ___get_environ_wrapper)(void) {
	char **__result;
	if __unlikely(_get_environ(&__result) != 0)
		__result = __NULLPTR;
	return __result;
}
#endif /* !_____get_environ_wrapper_defined */
#define __LOCAL_environ ___get_environ_wrapper()
#endif /* ... */
__DECL_END
#endif /* !__LOCAL_environ */
#endif /* !__LOCAL_environ */
