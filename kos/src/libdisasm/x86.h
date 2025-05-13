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
#ifndef GUARD_LIBDISASM_X86_H
#define GUARD_LIBDISASM_X86_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/host.h>

#include <libdisasm/disassembler.h>

DECL_BEGIN

#define DA86_IS16(self) ((self)->d_target == DISASSEMBLER_TARGET_8086)
#define DA86_IS32(self) ((self)->d_target == DISASSEMBLER_TARGET_I386)
#define DA86_IS64(self) ((self)->d_target == DISASSEMBLER_TARGET_X86_64)

INTDEF void CC libda_single_x86(struct disassembler *__restrict self);

DECL_END

#endif /* !GUARD_LIBDISASM_X86_H */
