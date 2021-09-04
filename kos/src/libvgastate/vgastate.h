/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBVGASTATE_VGASTATE_H
#define GUARD_LIBVGASTATE_VGASTATE_H 1

#include "api.h"
/**/

#include <kos/kernel/types.h>
#include <kos/types.h>

#include <libvgastate/vga.h>

DECL_BEGIN

INTDEF NONNULL((1)) unsigned int NOTHROW_KERNEL(CC libvga_state_save)(struct vga_state *__restrict self);
INTDEF NONNULL((1)) unsigned int NOTHROW_KERNEL(CC libvga_state_load)(struct vga_state const *__restrict self);
INTDEF NONNULL((1)) void NOTHROW_KERNEL(CC libvga_state_fini)(struct vga_state const *__restrict self);
INTDEF unsigned int NOTHROW_KERNEL(CC libvga_state_text)(void);

/* Encode a given unicode character and return the VGA codepage ordinal with
 * which that character should be represented. As a fallback for glyphs that
 * don't appear in the VGA codepage, the ordinal of a replacement  character
 * will be returned instead.
 * This function also does some internal transliteration in order to provide
 * more support  for  similar-looking  unicode characters  (e.g.  ►  and  ▶) */
INTDEF ATTR_CONST byte_t NOTHROW(CC libvga_state_encode)(char32_t ch);

DECL_END

#endif /* !GUARD_LIBVGASTATE_VGASTATE_H */
