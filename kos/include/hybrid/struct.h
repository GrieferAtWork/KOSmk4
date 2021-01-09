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
#ifndef __GUARD_HYBRID_STRUCT_H
#define __GUARD_HYBRID_STRUCT_H 1

#include "../__stdinc.h"
#include "__bit.h"

__DECL_BEGIN

#if defined(__CC__) || defined(__INTELLISENSE__)
#define TYPEDEF(type, name)                               typedef type name;
#define STRUCT_BEGIN(name)                                struct name {
#define STRUCT_FIELD(struct_name, field_type, field_name) field_type field_name;
#define STRUCT_END                                        };
#elif defined(__ASSEMBLER__)
#define TYPEDEF(type, name) \
	.macro .name x:req; .type \x; .endm;
#define STRUCT_BEGIN(name) \
	.pushsection .discard; .struct 0;
#define STRUCT_FIELD(struct_name, field_type, field_name) \
	struct_name.field_name: .field_type 0; .size struct_name.field_name, . - struct_name.field_name;
#define STRUCT_END \
	.popsection
#else /* __CC__ */
#define TYPEDEF(type, name)                               /* nothing */
#define STRUCT_BEGIN(name)                                /* nothing */
#define STRUCT_FIELD(struct_name, field_type, field_name) /* nothing */
#define STRUCT_END                                        /* nothing */
#endif /* !__CC__ */

__DECL_END

#endif /* !__GUARD_HYBRID_STRUCT_H */
