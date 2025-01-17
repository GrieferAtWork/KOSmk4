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
#ifndef GUARD_LIBC_LIBC_CXX_H
#define GUARD_LIBC_LIBC_CXX_H 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <kos/types.h>

#ifdef __CC__
DECL_BEGIN

/* Various functions primarily meant for c++ (so you don't have to necessarily link against libstdc++) */
INTDEF ATTR_MALLOC WUNUSED void *LIBCCALL libc__Znam(size_t num_bytes);                                                            /* operator new[](unsigned long) */
INTDEF ATTR_MALLOC WUNUSED void *LIBCCALL libc__ZnamSt11align_val_t(size_t num_bytes, size_t min_alignment);                       /* operator new[](unsigned long, std::align_val_t) */
INTDEF ATTR_MALLOC WUNUSED void *LIBCCALL libc__ZnamRKSt9nothrow_t(size_t num_bytes, void *);                                      /* operator new[](unsigned long, std::nothrow_t const&) */
INTDEF ATTR_MALLOC WUNUSED void *LIBCCALL libc__ZnamSt11align_val_tRKSt9nothrow_t(size_t num_bytes, size_t min_alignment, void *); /* operator new[](unsigned long, std::align_val_t, std::nothrow_t const&) */
INTDEF ATTR_MALLOC WUNUSED void *LIBCCALL libc__Znwm(size_t num_bytes);                                                            /* operator new(unsigned long) */
INTDEF ATTR_MALLOC WUNUSED void *LIBCCALL libc__ZnwmSt11align_val_t(size_t num_bytes, size_t min_alignment);                       /* operator new(unsigned long, std::align_val_t) */
INTDEF ATTR_MALLOC WUNUSED void *LIBCCALL libc__ZnwmRKSt9nothrow_t(size_t num_bytes, void *);                                      /* operator new(unsigned long, std::nothrow_t const&) */
INTDEF ATTR_MALLOC WUNUSED void *LIBCCALL libc__ZnwmSt11align_val_tRKSt9nothrow_t(size_t num_bytes, size_t min_alignment, void *); /* operator new(unsigned long, std::align_val_t, std::nothrow_t const&) */

typedef void (LIBCCALL *cxx_new_handler_t)(void);
INTDEF ATTR_PURE WUNUSED cxx_new_handler_t NOTHROW(LIBCCALL libc__ZSt15get_new_handlerv)(void);
INTDEF WUNUSED cxx_new_handler_t NOTHROW(LIBCCALL libc__ZSt15set_new_handlerPFvvE)(cxx_new_handler_t handler);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_LIBC_LIBC_CXX_H */
