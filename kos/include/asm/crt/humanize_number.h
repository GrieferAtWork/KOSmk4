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
#ifndef _ASM_CRT_HUMANIZE_NUMBER_H
#define _ASM_CRT_HUMANIZE_NUMBER_H 1

/* Flags for `humanize_number(3)::flags' */
#define __HN_DECIMAL      0x01
#define __HN_NOSPACE      0x02
#define __HN_B            0x04
#define __HN_DIVISOR_1000 0x08
#define __HN_IEC_PREFIXES 0x10

/* Flags for `humanize_number(3)::scale' */
#define __HN_GETSCALE     0x10
#define __HN_AUTOSCALE    0x20

#endif /* !_ASM_CRT_HUMANIZE_NUMBER_H */
