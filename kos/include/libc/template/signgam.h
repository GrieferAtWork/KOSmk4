/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __LOCAL_signgam
#include <__crt.h>
#ifndef __LOCAL_signgam
#ifdef signgam
#define __LOCAL_signgam signgam
#elif defined(__CRT_HAVE_signgam)
#ifndef __NO_COMPILER_SREDIRECT
#define __LOCAL_signgam __LOCAL_signgam
#ifdef __CC__
__DECL_BEGIN
__CSREDIRECT(,int *,__LOCAL_signgam,signgam)
__DECL_END
#endif /* __CC__ */
#else /* !__NO_COMPILER_SREDIRECT */
#define __LOCAL_signgam signgam
#define signgam         signgam
#ifdef __CC__
__DECL_BEGIN
__CSDECLARE(,int *,signgam)
__DECL_END
#endif /* __CC__ */
#endif /* __NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE___signgam)
#ifdef __CC__
__DECL_BEGIN
#ifndef ____signgam_defined
#define ____signgam_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,int *,__NOTHROW_NCX,__signgam,(void),())
#endif /* !____signgam_defined */
__DECL_END
#endif /* __CC__ */
#define __LOCAL_signgam (*__signgam())
#endif /* ... */
#endif /* !__LOCAL_signgam */
#endif /* !__LOCAL_signgam */
