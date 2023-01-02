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
/* (#) Portability: DJGPP (/include/mem.h) */
/* (#) Portability: MinGW (/mingw-w64-headers/crt/mem.h) */
#ifndef _MEM_H
#define _MEM_H 1

#include <memory.h>

#ifndef __ptrdiff_t_defined
#include <hybrid/typecore.h>
#ifndef __ptrdiff_t_defined
#define __ptrdiff_t_defined
#ifdef __CC__
__DECL_BEGIN
typedef __PTRDIFF_TYPE__ ptrdiff_t;
__DECL_END
#endif /* __CC__ */
#endif /* !__ptrdiff_t_defined */
#endif /* !__ptrdiff_t_defined */

#endif /* !_MEM_H */
