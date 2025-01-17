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
#ifndef __LOCAL_suboptarg
#include <__crt.h>
#ifndef __LOCAL_suboptarg
#ifdef suboptarg
#define __LOCAL_suboptarg suboptarg
#elif defined(__CRT_HAVE_suboptarg)
__DECL_BEGIN
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,char *,__LOCAL_suboptarg,suboptarg)
#define __LOCAL_suboptarg __LOCAL_suboptarg
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE(,char *,suboptarg)
#define suboptarg         suboptarg
#define __LOCAL_suboptarg suboptarg
#endif /* __NO_COMPILER_SREDIRECT */
__DECL_END
#endif /* ... */
#endif /* !__LOCAL_suboptarg */
#endif /* !__LOCAL_suboptarg */
