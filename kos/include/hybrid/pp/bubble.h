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
#ifndef __GUARD_HYBRID_PP_BUBBLE_H
#define __GUARD_HYBRID_PP_BUBBLE_H 1

#include <hybrid/compiler.h>
#include "__bubble.h"

/* Evaluates to the size of a bubble.
 * >> PP_BUBBLE_SIZE((a))       -- 1
 * >> PP_BUBBLE_SIZE((a)(b)(c)) -- 3 */
#define PP_BUBBLE_SIZE(x)            __HYBRID_PP_PRIVATE_BUBBLE_SIZE_0 x (__STOP__)

/* Evaluates to the i'th element of a bubble.
 * >> PP_BUBBLE_GET((a)(b)(c),0) -- a
 * >> PP_BUBBLE_GET((a)(b)(c),2) -- c */
#define PP_BUBBLE_GET(x,i)           __HYBRID_PP_PRIVATE_BUBBLE_GET(x,i,PP_BUBBLE_SIZE(x))

#endif /* !__GUARD_HYBRID_PP_BUBBLE_H */
