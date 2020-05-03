/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBINSTRLEN_ISA_H
#define _LIBINSTRLEN_ISA_H 1

#include "../api.h"

/* Default ISA type. */
#define INSTRLEN_ISA_DEFAULT 0

/* Return the ISA type, given a CPU state structure. */
#define instrlen_isa_from_icpustate(s) INSTRLEN_ISA_DEFAULT
#define instrlen_isa_from_scpustate(s) INSTRLEN_ISA_DEFAULT
#define instrlen_isa_from_ucpustate(s) INSTRLEN_ISA_DEFAULT
#define instrlen_isa_from_kcpustate(s) INSTRLEN_ISA_DEFAULT
#define instrlen_isa_from_lcpustate(s) INSTRLEN_ISA_DEFAULT
#define instrlen_isa_from_fcpustate(s) INSTRLEN_ISA_DEFAULT

#ifdef __CC__
__DECL_BEGIN

typedef unsigned int instrlen_isa_t;

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBINSTRLEN_ISA_H */
