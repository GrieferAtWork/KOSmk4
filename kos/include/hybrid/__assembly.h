/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID___ASSEMBLY_H
#define __GUARD_HYBRID___ASSEMBLY_H 1

#include "../__stdinc.h"

#ifdef __ASSEMBLER__
#undef PRIVATE
#undef INTERN
#undef PUBLIC
#undef EXTERN
#undef BEGIN
#undef END
#undef INTERN_CONST
#undef PUBLIC_CONST

#define PRIVATE(sym)  .local sym;
#define INTERN(sym)   .global sym; .hidden sym;
#define PUBLIC(sym)   .global sym;
#define EXTERN(sym)   .global sym;
#define BEGIN(sym)    sym:
#define END(sym)      .size sym, . - sym;

#define FUNCTION(sym) .type sym, "function"; BEGIN(sym)
#define OBJECT(sym)   .type sym, "object"; BEGIN(sym)

#define PRIVATE_BEGIN(sym) PRIVATE(sym) BEGIN(sym)
#define INTERN_BEGIN(sym)  INTERN(sym) BEGIN(sym)
#define PUBLIC_BEGIN(sym)  PUBLIC(sym) BEGIN(sym)

#define PRIVATE_FUNCTION(sym)   PRIVATE(sym) FUNCTION(sym)
#define INTERN_FUNCTION(sym)    INTERN(sym) FUNCTION(sym)
#define PUBLIC_FUNCTION(sym)    PUBLIC(sym) FUNCTION(sym)

#define PRIVATE_OBJECT(sym)     PRIVATE(sym) OBJECT(sym)
#define INTERN_OBJECT(sym)      INTERN(sym) OBJECT(sym)
#define PUBLIC_OBJECT(sym)      PUBLIC(sym) OBJECT(sym)

#define PRIVATE_LABEL(sym)      PRIVATE(sym) sym
#define INTERN_LABEL(sym)       INTERN(sym) sym
#define PUBLIC_LABEL(sym)       PUBLIC(sym) sym

#define PRIVATE_CONST(sym, val) PRIVATE(sym) .set sym, val;
#define INTERN_CONST(sym, val)  INTERN(sym) .set sym, val;
#define PUBLIC_CONST(sym, val)  PUBLIC(sym) .set sym, val;
#endif /* __ASSEMBLER__ */


#endif /* !__GUARD_HYBRID___ASSEMBLY_H */
