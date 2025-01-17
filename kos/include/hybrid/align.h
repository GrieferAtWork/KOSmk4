/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID_ALIGN_H
#define __GUARD_HYBRID_ALIGN_H 1

#include "../__stdinc.h"

#define IS_ALIGNED(x, align)  (!((x) % (align)))
#define IS_POWER_OF_TWO(x)    (((x) & ((x)-1)) == 0)
#if 0 /* Assuming `align' is constant, this is 2 ops: `add $(align - 1), %x; and $(~(align - 1)), %x' */
#define CEIL_ALIGN(x, align)  (((x) + ((align)-1)) & ~((align)-1))
#else /* Assuming `align' is constant, this is 3 ops: `dec %x; or $(align - 1), %x; inc %x'
       * But  because inc/dec are  much easier to  execute than immediate-instruction, this
       * method id probably still the better one when it comes to speed. */
#define CEIL_ALIGN(x, align)  ((((x) - 1) | ((align) - 1)) + 1)
#endif
#define FLOOR_ALIGN(x, align) ((x) & ~((align)-1))
#define FLOORDIV(x, y)        ((x) / (y))
#define CEILDIV(x, y)         (((x) + (y)-1) / (y))

#endif /* !__GUARD_HYBRID_ALIGN_H */
