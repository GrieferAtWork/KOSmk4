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
#ifndef _BITS_PARAM_H
#define _BITS_PARAM_H 1

#ifndef ARG_MAX
#define __undef_ARG_MAX
#endif

#include <linux/limits.h>
#include <linux/param.h>

#ifdef __undef_ARG_MAX
#undef ARG_MAX
#undef __undef_ARG_MAX
#endif

#ifndef MAXSYMLINKS
#define MAXSYMLINKS 20
#endif /* !MAXSYMLINKS */
#ifndef NOFILE
#define NOFILE      256
#endif /* !NOFILE */
#ifndef NCARGS
#define NCARGS      131072
#endif /* !NCARGS */

#endif /* !_BITS_PARAM_H */
