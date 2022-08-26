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
#ifndef GUARD_LIBDISASM_ARM_H
#define GUARD_LIBDISASM_ARM_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/host.h>

#include "common.h"

DECL_BEGIN

#define DAARM_ISARM(self)   ((self)->d_target == DISASSEMBLER_TARGET_ARM_ARM)
#define DAARM_ISTHUMB(self) ((self)->d_target == DISASSEMBLER_TARGET_ARM_THUMB)

INTDEF void CC libda_single_arm(struct disassembler *__restrict self);

DECL_END

#endif /* !GUARD_LIBDISASM_ARM_H */
