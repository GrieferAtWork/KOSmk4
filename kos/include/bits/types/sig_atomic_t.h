/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef __sig_atomic_t_defined
#include <__stdinc.h>
#include <hybrid/typecore.h>
#ifndef __sig_atomic_t_defined
#define __sig_atomic_t_defined 1
#ifdef __CC__
__DECL_BEGIN
typedef __SIG_ATOMIC_TYPE__ sig_atomic_t;
__DECL_END
#endif /* __CC__ */
#endif /* !__sig_atomic_t_defined */
#endif /* !__sig_atomic_t_defined */
