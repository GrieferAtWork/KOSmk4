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
#ifndef GUARD_KERNEL_INCLUDE_DEBUGGER_ARCH_RT_H
#define GUARD_KERNEL_INCLUDE_DEBUGGER_ARCH_RT_H 1

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <kernel/types.h>
#include <compat/config.h>

#ifdef __CC__
DECL_BEGIN

/* Return the pointer-size of `dbg_current' */
#define dbg_current_sizeof_pointer() __SIZEOF_POINTER__

/* Get/set a register, given its ID
 * NOTE: When `return > buflen', then
 *       dbg_getregbyname: The contents of `buf' are undefined.
 *       dbg_setregbyname:  The  register   was  not   written.
 * NOTE: Accepted register names are those found in comments in `<asm/registers.h>'
 * @param: regno: One of the values from <asm/registers.h>
 * @return: * :   The required buffer size, or 0 when `regno' isn't recognized. */
FUNDEF size_t NOTHROW(KCALL arch_dbg_getregbyid)(unsigned int level, unsigned int regno, void *__restrict buf, size_t buflen);
FUNDEF size_t NOTHROW(KCALL arch_dbg_setregbyid)(unsigned int level, unsigned int regno, void const *__restrict buf, size_t buflen);

/* Get/Set a pointer-sized register, given its ID */
FUNDEF ATTR_PURE WUNUSED uintptr_t NOTHROW(KCALL arch_dbg_getregbyidp)(unsigned int level, unsigned int regno);
FUNDEF bool NOTHROW(KCALL arch_dbg_setregbyidp)(unsigned int level, unsigned int regno, uintptr_t value);

/* Return the ID (one of the values from <asm/registers.h>), from a given register name.
 * @return: ARCH_REGISTER_NONE: Unknown register. */
FUNDEF ATTR_PURE WUNUSED NONNULL((1)) unsigned int
NOTHROW(KCALL arch_dbg_regfromname)(char const *__restrict name, size_t namelen);

/* Arch-specific register names. */
#define ARCH_REGISTER_NONE 0

DECL_END
#endif /* __CC__ */
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_INCLUDE_DEBUGGER_ARCH_RT_H */
