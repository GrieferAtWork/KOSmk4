/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif(x -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_LIBDEBUGINFO_SYMTAB_C
#define GUARD_LIBDEBUGINFO_SYMTAB_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING /* Don't profile this file */

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <kos/types.h>

#include <elf.h>
#include <string.h>

#include <libdebuginfo/symtab.h>

#include "symtab.h"

DECL_BEGIN

/* Scan the given symbol table for:
 *   #1: A symbol containing the given `module_relative_pc' (or starting at it)
 *   #2: The nearest symbol with an address <= module_relative_pc
 * NOTE: Symbols to which #1 applies are preferred over ones to which only #2 applies.
 * @return: * :   A pointer to the symbol's Elf32_Sym or Elf64_Sym structure.
 * @return: NULL: All defined symbols have an address > module_relative_pc
 * @return: NULL: The given symbol table is empty, too small, or corrupted.
 * @return: NULL: The given `symtab_entsize' is neither `sizeof(Elf32_Sym)', nor `sizeof(Elf64_Sym)' */
INTERN TEXTSECTION ATTR_PURE WUNUSED NONNULL((1, 2)) byte_t const *
NOTHROW_NCX(CC libdi_symtab_scantable)(byte_t const *__restrict symtab_start,
                                       byte_t const *__restrict symtab_end,
                                       size_t symtab_entsize,
                                       uintptr_t module_relative_pc) {
	byte_t const *result;
	if (symtab_start >= symtab_end)
		goto done_null;
	if (symtab_entsize == sizeof(Elf32_Sym)) {
		Elf32_Sym const *iter;
		Elf32_Addr result_value;
		symtab_end -= (sizeof(Elf32_Sym) - 1);
		for (iter = (Elf32_Sym const *)symtab_start;
		     iter < (Elf32_Sym const *)symtab_end; ++iter) {
			Elf32_Section st_shndx; /* Section index */
			Elf32_Addr st_value;    /* Symbol value */
			st_shndx = UNALIGNED_GET(&iter->st_shndx);
			if (st_shndx == SHN_UNDEF ||
			    st_shndx == SHN_ABS)
				continue;
			st_value = UNALIGNED_GET(&iter->st_value);
			if ((st_value == module_relative_pc) ||
			    (module_relative_pc >= (uintptr_t)st_value &&
			     module_relative_pc < (uintptr_t)st_value + UNALIGNED_GET(&iter->st_size)))
				return (byte_t const *)iter; /* Perfect match! */
		}
		/* Fallback: return the nearest symbol. */
		result       = NULL;
		result_value = (Elf32_Addr)-1;
		for (iter = (Elf32_Sym const *)symtab_start;
		     iter < (Elf32_Sym const *)symtab_end; ++iter) {
			Elf32_Section st_shndx; /* Section index */
			Elf32_Addr st_value;    /* Symbol value */
			st_shndx = UNALIGNED_GET(&iter->st_shndx);
			if (st_shndx == SHN_UNDEF ||
			    st_shndx == SHN_ABS)
				continue;
			st_value = UNALIGNED_GET(&iter->st_value);
			if (st_value > module_relative_pc)
				continue; /* Defined above the result */
			if (st_value < result_value) {
				result       = (byte_t const *)iter;
				result_value = st_value;
			}
		}
	} else if (symtab_entsize == sizeof(Elf64_Sym)) {
		Elf64_Sym const *iter;
		Elf64_Addr result_value;
		symtab_end -= (sizeof(Elf64_Sym) - 1);
		for (iter = (Elf64_Sym const *)symtab_start;
		     iter < (Elf64_Sym const *)symtab_end; ++iter) {
			Elf64_Section st_shndx; /* Section index */
			Elf64_Addr st_value;    /* Symbol value */
			st_shndx = UNALIGNED_GET(&iter->st_shndx);
			if (st_shndx == SHN_UNDEF ||
			    st_shndx == SHN_ABS)
				continue;
			st_value = UNALIGNED_GET(&iter->st_value);
			if ((st_value == module_relative_pc) ||
			    (module_relative_pc >= st_value &&
			     module_relative_pc < st_value + UNALIGNED_GET(&iter->st_size)))
				return (byte_t const *)iter; /* Perfect match! */
		}
		/* Fallback: return the nearest symbol. */
		result       = NULL;
		result_value = (Elf64_Addr)-1;
		for (iter = (Elf64_Sym const *)symtab_start;
		     iter < (Elf64_Sym const *)symtab_end; ++iter) {
			Elf64_Section st_shndx; /* Section index */
			Elf64_Addr st_value;    /* Symbol value */
			st_shndx = UNALIGNED_GET(&iter->st_shndx);
			if (st_shndx == SHN_UNDEF ||
			    st_shndx == SHN_ABS)
				continue;
			st_value = UNALIGNED_GET(&iter->st_value);
			if (st_value > module_relative_pc)
				continue; /* Defined above the result */
			if (st_value < result_value) {
				result       = (byte_t const *)iter;
				result_value = st_value;
			}
		}
	} else {
done_null:
		result = NULL;
	}
	return result;
}

DEFINE_PUBLIC_ALIAS(symtab_scantable, libdi_symtab_scantable);

DECL_END

#endif /* !GUARD_LIBDEBUGINFO_SYMTAB_C */
