/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_POSIX_LIM1_H
#define _BITS_POSIX_LIM1_H 1

/* NOTE: This file must _always_ be kept for Glibc compatibility! */

#include "../features.h"

#ifndef _POSIX_ARG_MAX
#undef _LIMITS_H
#ifdef __USE_POSIX
#include "../limits.h"
#else /* __USE_POSIX */
#define __USE_POSIX 1
#include "../limits.h"
#undef __USE_POSIX
#endif /* !... */
#endif /* !_POSIX_ARG_MAX */

#endif /* !_BITS_POSIX_LIM1_H */
