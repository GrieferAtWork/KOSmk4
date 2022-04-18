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
/* (#) Portability: GNU C Library (/include/bits/xopen_lim.h) */
/* (#) Portability: mintlib       (/include/bits/xopen_lim.h) */
#ifndef _BITS_XOPEN_LIM_H
#define _BITS_XOPEN_LIM_H 1

/* NOTE: This file must _always_ be kept for GLibc compatibility! */

#include "../features.h"

#ifndef _XOPEN_IOV_MAX
#undef _LIMITS_H
#ifdef __USE_XOPEN
#include "../limits.h"
#else /* __USE_XOPEN */
#define __USE_XOPEN 1
#include "../limits.h"
#undef __USE_XOPEN
#endif /* !... */
#endif /* !_XOPEN_IOV_MAX */

#endif /* !_BITS_XOPEN_LIM_H */
