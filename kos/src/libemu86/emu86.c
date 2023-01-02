/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBEMU86_EMU86_C
#define GUARD_LIBEMU86_EMU86_C 1

#include "api.h"
/**/

#include <libemu86/emu86.c>

DECL_BEGIN

#undef emu86_opcode_decode
#undef emu86_modrm_decode
DEFINE_PUBLIC_ALIAS(emu86_opcode_decode, libemu86_opcode_decode);
DEFINE_PUBLIC_ALIAS(emu86_modrm_decode, libemu86_modrm_decode);

DECL_END

#endif /* !GUARD_LIBEMU86_EMU86_C */
