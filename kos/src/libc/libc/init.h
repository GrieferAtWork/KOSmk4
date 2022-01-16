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
#ifndef GUARD_LIBC_LIBC_INIT_H
#define GUARD_LIBC_LIBC_INIT_H 1

/* Keep this one the first */
#include "../api.h"
/**/

DECL_BEGIN

#ifdef __CC__

/* Libc library initializer / finalizer.
 * These  functions are  bound to the  DT_INIT / DT_FINI  tags of libc.so.
 * Since use of __attribute__((constructor)) / __attribute__((destructor))
 * causes the creation  of 1 R_386_RELATIVE  relocation each (even  though
 * such a relocation  would have  been completely unnecessary  if ELF  had
 * been designed to specify pointers  apart of .init/.fini to be  relative
 * to the associated module)
 * Anyways: Anything that  cannot be  initialized lazily,  and anything  that
 *          needs to be finalized once libc.so gets unloaded (usually  caused
 *          by `exit(2)' being invoked), should  instead place a hook  within
 *          the implementation  of these  functions found  in the  associated
 *          init.c file, thus preventing the need of unnecessary relocations,
 *          as well as  making it plain  and simple to  control the order  of
 *          initialization/finalization */
INTDEF void LIBCCALL libc_init(void);
INTDEF void LIBCCALL libc_fini(void);

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_LIBC_LIBC_INIT_H */
