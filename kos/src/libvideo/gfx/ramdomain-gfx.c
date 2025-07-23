/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.removeif(x -> x.startswith("-O"));
gcc_opt.append("-O3"); // Force _all_ optimizations because stuff in here is performance-critical
]]]*/
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
#ifndef GUARD_LIBVIDEO_GFX_RAMDOMAIN_GFX_C
#define GUARD_LIBVIDEO_GFX_RAMDOMAIN_GFX_C 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <libvideo/gfx/gfx.h>

#include "ramdomain.h"

DECL_BEGIN

#ifndef __INTELLISENSE__
DECL_END
#define DEFINE_rambuffer__initgfx
#include "ramdomain-gfx.c.inl"
#define DEFINE_rambuffer_revokable__initgfx
#include "ramdomain-gfx.c.inl"
#define DEFINE_rambuffer_revokable_xoff__initgfx
#include "ramdomain-gfx.c.inl"
DECL_BEGIN
#endif /* !__INTELLISENSE__ */

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_RAMDOMAIN_GFX_C */
