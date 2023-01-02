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
#ifndef GUARD_LIBINSTRLEN_ARCH_ARM_CONFIG_H
#define GUARD_LIBINSTRLEN_ARCH_ARM_CONFIG_H 1

/* Define source files */
#define ARCH_INSTRLEN_SOURCE_FILE "arch/arm/instrlen.c"

/* Define features defined in source files */
#define ARCH_HAVE_INSTRUCTION_LENGTH  1 /* Defined in arch/arm/instrlen.c */
#define ARCH_HAVE_INSTRUCTION_PRED    1 /* Defined in arch/arm/instrlen.c */
#define ARCH_HAVE_INSTRUCTION_TRYSUCC 1 /* Defined in arch/arm/instrlen.c */
#define ARCH_HAVE_INSTRUCTION_TRYPRED 1 /* Defined in arch/arm/instrlen.c */
#define ARCH_INSTRUCTION_MAXLENGTH    4 /* ARM has 4-byte instructions, and thumb has varying 2/4-byte */

#endif /* !GUARD_LIBINSTRLEN_ARCH_ARM_CONFIG_H */
