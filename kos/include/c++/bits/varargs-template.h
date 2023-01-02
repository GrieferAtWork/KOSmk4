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
#ifndef _CXX_BITS_VARARGS_TEMPLATE_H
#define _CXX_BITS_VARARGS_TEMPLATE_H 1

#include <__stdcxx.h>

#if defined(__COMPILER_HAVE_CXX_VARIABLE_TEMPLATES)
#define __CXX_VARARGS_TEMPLATE_USED  1
#define __CXX_VARARGS_TEMPLATE_ARGS(class,name)           class ...name
#define __CXX_VARARGS_TEMPLATE_ARGS_DEF(class,name,defl)  class ...name
#define __CXX_VARARGS_TYPENAME_ARGS(name)                 name...
#else /* __COMPILER_HAVE_CXX_VARIABLE_TEMPLATES */
#undef __CXX_VARARGS_TEMPLATE_USED
#include "varargs-template-emulate.h"
#endif /* !__COMPILER_HAVE_CXX_VARIABLE_TEMPLATES */

#endif /* !_CXX_BITS_VARARGS_TEMPLATE_H */
