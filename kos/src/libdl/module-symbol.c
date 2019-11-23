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
#ifndef GUARD_LIBDL_MODULE_SYMBOL_C
#define GUARD_LIBDL_MODULE_SYMBOL_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

/* Keep this one the first */
#include "elf.h"
/**/

#include <string.h>
#include <syslog.h>

DECL_BEGIN


LOCAL WUNUSED ATTR_PURE NONNULL((1)) u32 CC
elf_symhash(char const *__restrict name) {
	u32 h = 0;
	while (*name) {
		u32 g;
		h = (h << 4) + *name++;
		g = h & 0xf0000000;
		if (g)
			h ^= g >> 24;
		h &= ~g;
	}
	return h;
}

/* Same as the functions above, but only return symbols defined within the same module! */
INTERN Elf_Sym const *CC
DlModule_GetLocalSymbol(DlModule *__restrict self,
                        char const *__restrict name,
                        uintptr_t *__restrict phash_elf,
                        uintptr_t *__restrict phash_gnu) {
	Elf_Sym *result;
	Elf_HashTable *elf_ht;
	if ((elf_ht = self->dm_hashtab) != NULL) {
		Elf_Word *ht_chains;
		Elf_Word max_attempts, chain;
		uintptr_t hash = *phash_elf;
		if (hash == DLMODULE_GETLOCALSYMBOL_HASH_UNSET)
			hash = *phash_elf = elf_symhash(name);
		if unlikely(!elf_ht->ht_nbuckts || !elf_ht->ht_nchains)
			goto nosym_no_elf_ht;
		max_attempts = elf_ht->ht_nchains;
		ht_chains    = elf_ht->ht_table + elf_ht->ht_nbuckts;
		chain        = elf_ht->ht_table[hash % elf_ht->ht_nbuckts];
		do {
			if unlikely(chain == STN_UNDEF)
				break; /* End of chain. */
			if unlikely(chain >= elf_ht->ht_nchains)
				goto nosym_no_elf_ht; /* Corrupted hash-table */
			result = self->dm_dynsym_tab + chain;
			if (strcmp(name, self->dm_dynstr + result->st_name) == 0)
				return result; /* Found it! */
			/* Load the next chain entry. */
			chain = ht_chains[chain];
		} while likely(--max_attempts);
		goto nosym;
	}
	/* TODO: GNU hash table support */
	(void)phash_gnu;

nosym:
	return NULL;
nosym_no_elf_ht:
	self->dm_hashtab = NULL;
	goto nosym;
}



DECL_END

#endif /* !GUARD_LIBDL_MODULE_SYMBOL_C */
