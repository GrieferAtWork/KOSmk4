/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.removeif(x -> x.startswith("-O"));
gcc_opt.append("-O3"); // Force _all_ optimizations because stuff in here is performance-critical
]]]*/
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
#ifndef GUARD_MODSVGA_GFXTTY_C
#define GUARD_MODSVGA_GFXTTY_C 1
#define NDEBUG_UNREACHABLE
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

/**/
#include "svga.h"

#ifndef __INTELLISENSE__
#define BPP 1
#include "gfxtty.c.inl"

#define BPP 1
#define PLANAR
#include "gfxtty.c.inl"

#define BPP 2
#define PLANAR
#include "gfxtty.c.inl"

//TODO:#define BPP 4
//TODO:#include "gfxtty.c.inl"

#define BPP 8
#include "gfxtty.c.inl"

#define BPP 16
#include "gfxtty.c.inl"

#define BPP 24
#include "gfxtty.c.inl"

#define BPP 32
#include "gfxtty.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_MODSVGA_GFXTTY_C */
