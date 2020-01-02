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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _COMPAT_KOS_EXCEPT_HANDLER_H
#define _COMPAT_KOS_EXCEPT_HANDLER_H 1

#include <compat/config.h>
#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/bits/except-handler.h>

__DECL_BEGIN

#ifdef __CC__

#ifndef __compat_except_handler_t_defined
#define __compat_except_handler_t_defined 1
typedef __compat_except_handler_t compat_except_handler_t;
#endif /* !__compat_except_handler_t_defined */

#endif /* __CC__ */

__DECL_END

#endif /* __ARCH_HAVE_COMPAT */

#endif /* !_COMPAT_KOS_EXCEPT_HANDLER_H */
