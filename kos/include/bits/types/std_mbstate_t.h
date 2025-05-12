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
/*!replace_with_include <cwchar>*/
#ifndef __std_mbstate_t_defined
#include <bits/crt/mbstate.h>
#ifndef __std_mbstate_t_defined
#define __std_mbstate_t_defined
#ifdef __CC__
__NAMESPACE_STD_BEGIN
#ifdef __mbstate_t_defined
__NAMESPACE_GLB_USING(mbstate_t)
#else /* __mbstate_t_defined */
typedef struct __mbstate mbstate_t;
#endif /* !__mbstate_t_defined */
__NAMESPACE_STD_END
#endif /* __CC__ */
#endif /* !__std_mbstate_t_defined */
#endif /* !__std_mbstate_t_defined */
