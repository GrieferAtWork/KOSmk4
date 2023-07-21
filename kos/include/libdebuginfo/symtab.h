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
#ifndef _LIBDEBUGINFO_DEBUG_SYMTAB_H
#define _LIBDEBUGINFO_DEBUG_SYMTAB_H 1

#include "api.h"
/**/

#include <bits/types.h>
#include <kos/anno.h>


#ifdef __CC__
__DECL_BEGIN

/* Scan the given symbol table for:
 *   #1: A symbol containing the given `module_relative_pc' (or starting at it)
 *   #2: The nearest symbol with an address <= module_relative_pc
 * NOTE: Symbols to which #1 applies are preferred over ones to which only #2 applies.
 * @return: * :   A pointer to the symbol's Elf32_Sym or Elf64_Sym structure.
 * @return: NULL: All defined symbols have an address > module_relative_pc
 * @return: NULL: The given symbol table is empty, too small, or corrupted.
 * @return: NULL: The given `symtab_entsize' is neither `sizeof(Elf32_Sym)', nor `sizeof(Elf64_Sym)' */
typedef __ATTR_PURE_T __ATTR_WUNUSED_T __CHECKED __byte_t const *
__NOTHROW_NCX_T(LIBDEBUGINFO_CC *PSYMTAB_SCANTABLE)(__CHECKED __byte_t const *symtab_start,
                                                    __CHECKED __byte_t const *symtab_end,
                                                    __size_t symtab_entsize,
                                                    __uintptr_t module_relative_pc);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_PURE __ATTR_WUNUSED __CHECKED __byte_t const *
__NOTHROW_NCX(LIBDEBUGINFO_CC symtab_scantable)(__CHECKED __byte_t const *symtab_start,
                                                __CHECKED __byte_t const *symtab_end,
                                                __size_t symtab_entsize,
                                                __uintptr_t module_relative_pc);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */



__DECL_END
#endif /* __CC__ */

#endif /* !_LIBDEBUGINFO_DEBUG_SYMTAB_H */
