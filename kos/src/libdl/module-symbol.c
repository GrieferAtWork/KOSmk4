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
#ifndef GUARD_LIBDL_MODULE_SYMBOL_C
#define GUARD_LIBDL_MODULE_SYMBOL_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

/* Keep this one the first */
#include "dl.h"
/**/

#include <hybrid/typecore.h>

#include <kos/exec/elf.h>

#include <elf.h>
#include <string.h>
#include <syslog.h>

DECL_BEGIN

LOCAL ATTR_PURE WUNUSED NONNULL((1)) u32
NOTHROW_NCX(CC gnu_symhash)(NCX char const *name)
		THROWS(E_SEGFAULT) {
	u32 h = 5381;
	for (; *name; ++name) {
		h = h * 33 + (u8)*name;
	}
	return h;
}

LOCAL ATTR_PURE WUNUSED NONNULL((1)) u32
NOTHROW_NCX(CC elf_symhash)(NCX char const *name)
		THROWS(E_SEGFAULT) {
	u32 h = 0;
	for (; *name; ++name) {
		u32 g;
		h = (h << 4) + (u8)*name;
		g = h & 0xf0000000;
		if (g)
			h ^= g >> 24;
		h &= ~g;
	}
	return h;
}

#if ELF_ARCH_CLASS == ELFCLASS32
#define ELF_CLASSBITS 32
#elif ELF_ARCH_CLASS == ELFCLASS64
#define ELF_CLASSBITS 64
#else /* ELF_ARCH_CLASS == ... */
#define ELF_CLASSBITS (__SIZEOF_POINTER__ * 8)
#endif /* ELF_ARCH_CLASS != ... */



/* Return a pointer to the Elf_Sym object assigned with `name'.
 * WARNING: The returned symbol  may not necessarily  be defined by  `self'.
 *          This function merely returns the associated entry from `.dynsym'
 * NOTE: This function ~may~ set `dlerror()' when returning `NULL' in
 *       case of the error is the  result of a corrupted hash  table. */
INTERN WUNUSED NONNULL((1, 2, 3, 4)) ElfW(Sym) const *
NOTHROW_NCX(CC DlModule_ElfGetLocalSymbol)(NCX DlModule *self,
                                           NCX char const *name,
                                           uintptr_t *__restrict phash_elf,
                                           uintptr_t *__restrict phash_gnu)
		THROWS(E_SEGFAULT) {
	ElfW(Sym) const *result;
	/************************************************************************/
	/* GNU hash table support                                               */
	/************************************************************************/
	{
		ElfW(GnuHashTable) const *gnu_ht;
		if ((gnu_ht = self->dm_elf.de_gnuhashtab) != NULL) {
			/* This implementation is derived from:
			 * https://flapenguin.me/2017/05/10/elf-lookup-dt-gnu-hash/
			 * https://sourceware.org/ml/binutils/2006-10/msg00377.html
			 */
			ElfW(Word) symid, gh_symoffset;
			ElfW(Word) const *gh_buckets;
			ElfW(Word) const *gh_chains;
			ElfW(Addr) bloom_word, bloom_mask;
			uintptr_t hash = *phash_gnu;
			if (hash == DLMODULE_GETLOCALSYMBOL_HASH_UNSET)
				hash = *phash_gnu = gnu_symhash(name);
			if unlikely(!gnu_ht->gh_bloom_size || !gnu_ht->gh_bloom_size)
				goto nosym_no_gnu_ht;
			gh_symoffset = gnu_ht->gh_symoffset;
			gh_buckets   = (ElfW(Word) const *)(gnu_ht->gh_bloom + gnu_ht->gh_bloom_size);
			gh_chains    = (ElfW(Word) const *)(gh_buckets + gnu_ht->gh_nbuckets);
			bloom_word   = gnu_ht->gh_bloom[(hash / ELF_CLASSBITS) % gnu_ht->gh_bloom_size];
			bloom_mask   = ((ElfW(Addr))1 << (hash % ELF_CLASSBITS)) |
			               ((ElfW(Addr))1 << ((hash >> gnu_ht->gh_bloom_shift) % ELF_CLASSBITS));
			if ((bloom_word & bloom_mask) != bloom_mask)
				goto nosym;
			symid = gh_buckets[hash % gnu_ht->gh_nbuckets];
			if unlikely(symid < gh_symoffset)
				goto nosym;
			/* Search for the symbol. */
			for (;; ++symid) {
				ElfW(Word) enthash;
				result  = self->dm_elf.de_dynsym_tab + symid;
				enthash = gh_chains[symid - gh_symoffset];
				if likely((hash | 1) == (enthash | 1)) {
					if likely(strcmp(name, self->dm_elf.de_dynstr + result->st_name) == 0)
						return result; /* Found it! */
				}
				if unlikely(enthash & 1)
					break; /* End of chain */
			}
			goto nosym;
		}
	}

search_elf_table:
	/************************************************************************/
	/* ELF hash table support                                               */
	/************************************************************************/
	{
		ElfW(HashTable) const *elf_ht;
		if ((elf_ht = self->dm_elf.de_hashtab) != NULL) {
			ElfW(Word) const *ht_chains;
			ElfW(Word) max_attempts, chain;
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
				result = self->dm_elf.de_dynsym_tab + chain;
				if likely(strcmp(name, self->dm_elf.de_dynstr + result->st_name) == 0)
					return result; /* Found it! */
				/* Load the next chain entry. */
				chain = ht_chains[chain];
			} while likely(--max_attempts);
			goto nosym;
		}
	}

search_dynsym:
	/************************************************************************/
	/* Do a linear search over the symbol table.                            */
	/************************************************************************/
	{
		ElfW(Sym) const *dynsym;
		if ((dynsym = self->dm_elf.de_dynsym_tab) != NULL) {
			size_t i, dyncnt;
			dyncnt = DlModule_ElfGetDynSymCnt(self);
			for (i = 0; i < dyncnt; ++i) {
				char const *symname;
				symname = self->dm_elf.de_dynstr + dynsym[i].st_name;
				if (strcmp(name, symname) != 0)
					continue;
				/* Found it! */
				return &dynsym[i];
			}
		}
	}

nosym:
	return NULL;
nosym_no_gnu_ht:
	syslog(LOG_WARNING, "[rtld] GNU symbol hash table of %q is corrupt\n",
	       self->dm_filename);
	self->dm_elf.de_gnuhashtab = NULL;
	goto search_elf_table;
nosym_no_elf_ht:
	syslog(LOG_WARNING, "[rtld] Elf symbol hash table of %q is corrupt\n",
	       self->dm_filename);
	self->dm_elf.de_hashtab = NULL;
	goto search_dynsym;
}



DECL_END

#endif /* !GUARD_LIBDL_MODULE_SYMBOL_C */
