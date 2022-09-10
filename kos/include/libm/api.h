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
#ifndef _LIBM_API_H
#define _LIBM_API_H 1

#include <__crt.h>

/* Pretty  much just  a stub header  (but required by  the general library
 * exposure  rules under KOS), as all math functions are actually exported
 * from libc. However, you can still `dlopen(3D)' `libm.so' and `dlsym(3)'
 * any math  function from  that handle  (since `dlsym(3)'  walks  library
 * dependencies, and  kos's  default  system `libm.so'  has  a  dependency
 * on `libc.so') */

#define LIBM_CC   __LIBCCALL
#define LIBM_VCC  __VLIBCCALL
#define LIBM_DECL __LIBC

#define LIBM_LIBRARY_NAME "libm.so"

#endif /* !_LIBM_API_H */
