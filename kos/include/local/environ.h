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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __LOCAL_environ
#include <__crt.h>
__DECL_BEGIN
#if defined(__environ_defined) || defined(environ)
#define __LOCAL_environ environ
#elif defined(___environ_defined) || defined(_environ)
#define __LOCAL_environ _environ
#elif defined(____environ_defined) || defined(__environ)
#define __LOCAL_environ __environ
#elif defined(__CRT_HAVE_environ) && !defined(__NO_ASMNAME)
__LIBC char **__LOCAL_environ __ASMNAME("environ");
#define __LOCAL_environ __LOCAL_environ
#elif defined(__CRT_HAVE_environ)
__LIBC char **environ;
#define __environ_defined 1
#define environ         environ
#define __LOCAL_environ environ
#elif defined(__CRT_HAVE__environ) && !defined(__NO_ASMNAME)
__LIBC char **__LOCAL_environ __ASMNAME("_environ");
#define __LOCAL_environ __LOCAL_environ
#elif defined(__CRT_HAVE__environ)
__LIBC char **_environ;
#define ___environ_defined 1
#define _environ        _environ
#define __LOCAL_environ _environ
#elif defined(__CRT_HAVE___environ) && !defined(__NO_ASMNAME)
__LIBC char **__LOCAL_environ __ASMNAME("__environ");
#define __LOCAL_environ __LOCAL_environ
#elif defined(__CRT_HAVE___environ)
__LIBC char **__environ;
#define ____environ_defined 1
#define __environ       __environ
#define __LOCAL_environ __environ
#elif defined(__CRT_HAVE___p__environ)
#ifndef ____p__environ_defined
#define ____p__environ_defined 1
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,char ***,__NOTHROW,__p__environ,(void),())
#endif /* !____p__environ_defined */
#define __LOCAL_environ (*__p__environ())
#endif /* ... */
__DECL_END
#endif /* !__LOCAL_environ */
