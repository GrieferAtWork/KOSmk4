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
#ifndef GUARD_LIBKEYMAP_EN_US_H
#define GUARD_LIBKEYMAP_EN_US_H 1

#include "api.h"
#include <libkeymap/keymap.h>

DECL_BEGIN

/* Initialize the given keymap to represent the map keys according to the en_US layout.
 * This function should be used as fallback when the caller is unable to initialize the
 * desired keyboard layout, as ~any~ mapping is still better than no mapping at all. */
INTDEF NONNULL((1)) void
NOTHROW_NCX(CC libkeymap_init_en_US)(struct keymap *__restrict self);


DECL_END

#endif /* !GUARD_LIBKEYMAP_EN_US_H */
