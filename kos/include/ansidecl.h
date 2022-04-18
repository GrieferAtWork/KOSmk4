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
/* (#) Portability: EMX kLIBC (/libc/include/ansidecl.h) */
/* (#) Portability: libc4/5   (/include/ansidecl.h) */
#ifndef _ANSIDECL_H
#define _ANSIDECL_H 1

#include <sys/cdefs.h>

#define PTR         _PTR
#define PTRCONST    _PTR _CONST
#define LONG_DOUBLE __LONGDOUBLE
#define AND         _AND
#define NOARGS      _NOARGS
#define CONST       _CONST
#define VOLATILE    _VOLATILE
#define SIGNED      _SIGNED
#define DOTS        _DOTS
#define EXFUN       _EXFUN
#define DEFUN       _DEFUN
#define DEFUN_VOID  _DEFUN_VOID

#endif /* !_ANSIDECL_H */
