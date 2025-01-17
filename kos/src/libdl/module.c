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
#ifndef GUARD_LIBDL_MODULE_C
#define GUARD_LIBDL_MODULE_C 1
#define _KOS_SOURCE 1
#define _KOS_KERNEL_SOURCE 1
#define _GNU_SOURCE 1

/* Keep this one the first */
#include "dl.h"
/**/

#include <kos/debugtrap.h>
#include <kos/syscalls.h>

#include <assert.h>
#include <atomic.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <link.h>
#include <malloc.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */


/* Make sure that offsets in `struct link_map' are correct. */
static_assert(offsetof(struct link_map, l_addr) == offsetof(DlModule, dm_loadaddr));
static_assert(offsetof(struct link_map, l_name) == offsetof(DlModule, dm_filename));
static_assert(offsetof(struct link_map, l_ld) == offsetof(DlModule, dm_dynhdr));
static_assert(offsetof(struct link_map, l_next) == offsetof(DlModule, dm_modules.dle_next));
static_assert(offsetof(struct link_map, l_prev) == offsetof(DlModule, dm_modules.dle_prev));

INTERN ElfW(Shdr) empty_shdr[1] = { { 0 } };

/* Module finalizer functions. */
INTERN NONNULL((1)) void CC
dlmodule_finalizers_run(struct dlmodule_finalizers *__restrict self)
		THROWS(...) {
	size_t count;

	/* Prevent new finalizers from being registered.
	 * Yes: we intentionally leave this lock dangling! */
	atomic_rwlock_read(&self->df_lock);

	/* Ensure that only a single thread may invoke finalizers. */
	count = atomic_xch(&self->df_size, 0);
	if (count) {
		RAII_FINALLY { free(self->df_list); };
		do {
			struct dlmodule_finalizer *ent;
			--count;
			ent = &self->df_list[count];
			(*ent->df_func)(ent->df_arg);
		} while (count);
	}
}



/* DlModule functions */
INTERN NONNULL((1)) void CC
DlModule_Destroy(NCX DlModule *self)
		THROWS(E_SEGFAULT, ...) {

	/* Unbind the module from the list of all modules. */
	dlglobals_all_write(&dl_globals);
	dlglobals_all_del(&dl_globals, self);
	assertf(!DLIST_EMPTY(&dl_globals.dg_alllist),
	        "The all-modules list should never become empty (libdl's "
	        "own module and main program should never disappear)");
	dlglobals_all_endwrite(&dl_globals);

	/* Trigger the trap informing a debugger of the change in loaded libraries. */
	if (!sys_debugtrap_disabled) {
		struct debugtrap_reason r;
		r.dtr_signo  = SIGTRAP;
		r.dtr_reason = DEBUGTRAP_REASON_LIBRARY;
		if (sys_debugtrap(NULL, &r) == -ENOENT)
			sys_debugtrap_disabled = true;
	}

	/* Unbind the module from the global symbol table. */
	assert(TAILQ_ISBOUND(self, dm_globals) ==
	       ((self->dm_flags & RTLD_GLOBAL) != 0));
	if (TAILQ_ISBOUND(self, dm_globals)) {
		dlglobals_global_write(&dl_globals);
		COMPILER_READ_BARRIER();
		if (TAILQ_ISBOUND(self, dm_globals))
			dlglobals_global_del(&dl_globals, self);
		dlglobals_global_endwrite(&dl_globals);
	}

	/* Invoke dynamically registered module finalizers (s.a. `__cxa_atexit()') */
	if (self->dm_finalize) {
		dlmodule_finalizers_run(self->dm_finalize);
		free(self->dm_finalize);
	}

	/* Skip finalizers if the library was never initialized. */
	if unlikely(self->dm_flags & RTLD_NOINIT)
		goto done_fini;
	/* Support for formats other than ELF. */
	if (self->dm_ops) {
		if (self->dm_ops->df_run_finalizers)
			(*self->dm_ops->df_run_finalizers)(self);
	} else {
		size_t i;
		uintptr_t fini_func        = 0;
		uintptr_t *fini_array_base = NULL;
		size_t fini_array_size     = 0;
		for (i = 0; i < self->dm_elf.de_dyncnt; ++i) {
			switch (self->dm_dynhdr[i].d_tag) {

			case DT_NULL:
				goto done_dyntag;

			case DT_FINI:
				fini_func = (uintptr_t)self->dm_dynhdr[i].d_un.d_ptr;
				break;

			case DT_FINI_ARRAY:
				fini_array_base = (uintptr_t *)(self->dm_loadaddr +
				                                self->dm_dynhdr[i].d_un.d_ptr);
				break;

			case DT_FINI_ARRAYSZ:
				fini_array_size = (size_t)self->dm_dynhdr[i].d_un.d_val / sizeof(void (*)(void));
				break;

			default: break;
			}
		}
done_dyntag:
		/* Service fini-array functions in reverse order. */
		while (fini_array_size--)
			(*(void (*)(void))(fini_array_base[fini_array_size] /* + self->dm_loadaddr*/))();
		/* Service a fini function, if one was specified. */
		if (fini_func)
			(*(void (*)(void))(fini_func + self->dm_loadaddr))();
	}
done_fini:
	if (self->dm_ops) {
		(*self->dm_ops->df_fini)(self);
	} else {
		ElfW(Half) i;
		/* Delete memory mappings of the module. */
		COMPILER_BARRIER();
		for (i = 0; i < self->dm_elf.de_phnum; ++i) {
			if (self->dm_elf.de_phdr[i].p_type != PT_LOAD)
				continue;
			sys_munmap((void *)(self->dm_elf.de_phdr[i].p_vaddr + self->dm_loadaddr),
			           self->dm_elf.de_phdr[i].p_memsz);
		}
		if (self->dm_elf.de_shdr != empty_shdr)
			free(self->dm_elf.de_shdr);
		free(self->dm_elf.de_shstrtab);
	}
	COMPILER_BARRIER();

	/* Drop references from dependent modules. */
	if (self->dm_depvec) {
		size_t i;
		for (i = 0; i < self->dm_depcnt; ++i) {
			DlModule *temp;
			temp = self->dm_depvec[i];
			if (!(temp->dm_flags & RTLD_NODELETE))
				decref(temp);
		}
		free(self->dm_depvec);
	}

	/* Close the module's file (if loaded) */
	if (self->dm_file > 0)
		(void)sys_close(self->dm_file);

	/* Free dynamically allocated heap-memory. */
	if (self->dm_sections) {
		size_t i;
again_free_sections:
		DlModule_SectionsWrite(self);
		for (i = 0; i < self->dm_shnum; ++i) {
			DlSection *sect;
			sect = self->dm_sections[i];
			if (!sect)
				continue;
			if (!DlSection_ModuleTryWrite(sect)) {
				bool hasref;
				hasref = DlSection_TryIncref(sect);
				DlModule_SectionsEndWrite(self);
				if (hasref) {
					DlSection_ModuleWaitWrite(sect);
					DlSection_Decref(sect);
				}
				goto again_free_sections;
			}
			assertf(sect->ds_flags & DLSECTION_FLAG_OWNED,
			        "If this was true, then the section should have kept a reference to us!");
			sect->ds_module = NULL;
			DlSection_ModuleEndWrite(sect);
			DBG_memset(&self->dm_sections[i], 0xcc, sizeof(self->dm_sections[i]));
		}
		{
			REF DlSection *dangle, *next;
			dangle = self->dm_sections_dangling;
			self->dm_sections_dangling = NULL;
			DlModule_SectionsEndWrite(self);
			while (dangle) {
				next = dangle->ds_dangling;
				DlSection_Decref(dangle);
				dangle = next;
			}
		}
		free(self->dm_sections);
	}
	if (self->dm_tlsmsize) {
		if (self->dm_tlsstoff == 0)
			DlModule_RemoveTLSExtension(self);
		if (self->dm_tlsfsize)
			free((void *)self->dm_tlsinit);
	} else {
		assert(!self->dm_tlsfsize);
	}
	free(self->dm_filename);
	weakdecref_likely(self);
}

/* DlModule functions */
INTERN NONNULL((1)) void
NOTHROW_NCX(CC DlModule_Free)(NCX DlModule *self)
		THROWS(E_SEGFAULT) {
	free(self);
}


INTDEF WUNUSED fd_t NOTHROW_RPC(CC reopen_bigfd)(fd_t fd);

/* Lazily allocate if necessary, and return the file descriptor for `self' */
INTERN WUNUSED NONNULL((1)) fd_t
NOTHROW_NCX(CC DlModule_GetFd)(NCX DlModule *self)
		THROWS(E_SEGFAULT) {
	fd_t result = self->dm_file;
	if (result == -1) {
		fd_t newresult;
		result = sys_open(self->dm_filename, O_RDONLY | O_CLOEXEC, 0);
		if unlikely(E_ISERR(result))
			goto err;
		/* Make sure to only use big file descriptor indices, so-as
		 * to  prevent use of reserved file numbers, as used by the
		 * standard I/O handles (aka. `STD(IN|OUT|ERR)_FILENO') */
		result    = reopen_bigfd(result);
		newresult = atomic_cmpxch_val(&self->dm_file, -1, result);
		if unlikely(newresult != -1) {
			(void)sys_close(result);
			result = newresult;
		}
	}
	return result;
err:
	return dl_seterrorf("%q: Failed to open module for reading",
	                    self->dm_filename);
}

/* Lazily allocate  if  necessary,  and  return  the vector  of  section  headers  for  `self'
 * NOTE: On success, this function guaranties that the following fields have been initialized:
 *  - self->dm_elf.de_shnum
 *  - self->dm_elf.de_shoff
 *  - self->dm_elf.de_shstrndx
 *  - self->dm_elf.de_shdr
 * @return: NULL: Error */
INTERN WUNUSED NONNULL((1)) ElfW(Shdr) *
NOTHROW_NCX(CC DlModule_ElfGetShdrs)(NCX DlModule *self)
		THROWS(E_SEGFAULT) {
	fd_t fd;
	ssize_t error;
	char error_fallback_buf[DL_STRERRORNAME_FALLBACK_LEN];
	ElfW(Shdr) *result;
	assert(!self->dm_ops);
	result = self->dm_elf.de_shdr;
	if (result != NULL)
		return result;

	/* Must load the section headers. */
	fd = DlModule_GetFd(self);
	if unlikely(fd < 0)
		goto err;
	if (self->dm_elf.de_shnum == (ElfW(Half))-1 ||
	    self->dm_elf.de_shoff == 0 ||
	    self->dm_elf.de_shstrndx == (ElfW(Half))-1) {
		ElfW(Ehdr) ehdr;

		/* Must initialize information about section headers. */
		error = preadall(fd, &ehdr, sizeof(ehdr), 0);
		if (E_ISERR(error))
			goto err_read_ehdr;

		/* Quickly verify that the ehdr is valid. */
		if unlikely(DlModule_ElfVerifyEhdr(&ehdr, self->dm_filename, false))
			goto err;
		if unlikely(ehdr.e_shstrndx >= ehdr.e_shnum) {
			dl_seterrorf("%q: Invalid `e_shstrndx=%" PRIuN(__SIZEOF_ELFW(HALF__)) "' "
			             "is greater than or equal to `e_shnum=%" PRIuN(__SIZEOF_ELFW(HALF__)) "'",
			             self->dm_filename, ehdr.e_shstrndx, ehdr.e_shnum);
			goto err;
		}
		atomic_cmpxch(&self->dm_elf.de_shnum, (ElfW(Half))-1, ehdr.e_shnum);
		atomic_cmpxch(&self->dm_elf.de_shoff, 0, ehdr.e_shoff);
		atomic_cmpxch(&self->dm_elf.de_shstrndx, (ElfW(Half))-1, ehdr.e_shstrndx);
	}
	if unlikely(!self->dm_elf.de_shnum) {
		atomic_cmpxch(&self->dm_elf.de_shdr, NULL, (ElfW(Shdr) *)empty_shdr);
		return empty_shdr;
	}

	/* Allocate the section header vector. */
	result = (ElfW(Shdr) *)malloc(self->dm_elf.de_shnum * sizeof(ElfW(Shdr)));
	if unlikely(!result)
		goto err_nomem;
	error = preadall(fd, result, self->dm_elf.de_shnum * sizeof(ElfW(Shdr)), self->dm_elf.de_shoff);
	if (E_ISERR(error))
		goto err_read_shdr;
	{
		ElfW(Shdr) *new_result;
		/* Save the newly loaded section header vector. */
		new_result = atomic_cmpxch_val(&self->dm_elf.de_shdr,
		                               NULL,
		                               result);
		if unlikely(new_result != NULL) {
			free(result);
			result = new_result;
		}
	}
	return result;
err_read_shdr:
	free(result);
	dl_seterrorf("%q: Failed to read section header vector: %s",
	             self->dm_filename,
	             dl_strerrorname_np_s((errno_t)-error, error_fallback_buf));
	goto err;
err_nomem:
	dl_seterrorf("%q: Failed to allocate section header vector",
	             self->dm_filename);
	goto err;
err_read_ehdr:
	dl_seterrorf("%q: Failed to read ElfW(Ehdr): %s",
	             self->dm_filename,
	             dl_strerrorname_np_s((errno_t)-error, error_fallback_buf));
err:
	return NULL;
}

/* Lazily allocate if necessary, and return the section header string table for `self'
 * @return: NULL: Error (s.a. dlerror()) */
INTERN WUNUSED NONNULL((1)) char *
NOTHROW_NCX(CC DlModule_ElfGetShstrtab)(DlModule *self)
		THROWS(E_SEGFAULT) {
	char *result;
	ElfW(Shdr) *shdrs;
	ssize_t error;
	char error_fallback_buf[DL_STRERRORNAME_FALLBACK_LEN];
	assert(!self->dm_ops);
	result = self->dm_elf.de_shstrtab;
	if (result)
		return result;
	shdrs = DlModule_ElfGetShdrs(self);
	if unlikely(!shdrs)
		goto err;
	shdrs += self->dm_elf.de_shstrndx;
	if unlikely(shdrs->sh_type == SHT_NOBITS) {
		dl_seterrorf("%q: Section `e_shstrndx=%" PRIuN(__SIZEOF_ELFW(HALF__)) "' has type `SHT_NOBITS'",
		             self->dm_filename, self->dm_elf.de_shstrndx);
		goto err;
	}
	/* Allocate the section header string table. */
	result = (char *)malloc(shdrs->sh_size + 1);
	if unlikely(!result)
		goto err_nomem;
	result[shdrs->sh_size] = '\0'; /* Ensure NUL-termination */

	/* Read the string table into memory. */
	error = preadall(self->dm_file, result, shdrs->sh_size, shdrs->sh_offset);
	if (E_ISERR(error))
		goto err_read_shstrtab;
	{
		char *new_result;
		/* Save the newly loaded section header string table. */
		new_result = atomic_cmpxch_val(&self->dm_elf.de_shstrtab,
		                               NULL,
		                               result);
		if unlikely(new_result != NULL) {
			free(result);
			result = new_result;
		}
	}
	return result;
err_read_shstrtab:
	dl_seterrorf("%q: Failed to read contents of "
	             "`e_shstrndx=%" PRIuN(__SIZEOF_ELFW(HALF__)) "' ("
	             "`sh_offset=%" PRIuN(__SIZEOF_ELFW(OFF__)) "'): %s",
	             self->dm_filename,
	             self->dm_elf.de_shstrndx,
	             shdrs->sh_offset,
	             dl_strerrorname_np_s((errno_t)-error, error_fallback_buf));
	goto err;
err_nomem:
	dl_seterrorf("%q: Failed to allocate section header string table",
	             self->dm_filename);
err:
	return NULL;
}

/* Lazily calculates  and  returns  the #  of  symbols  in  `de_dynsym_tab'
 * NOTE: This function may only be called with `de_dynsym_tab' is non-NULL!
 * @return: * : The # of symbols in `de_dynsym_tab'
 * @return: 0 : Error (dlerror() was modified) */
INTERN WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(CC DlModule_ElfGetDynSymCnt)(NCX DlModule *self)
		THROWS(E_SEGFAULT) {
	size_t result;
	assert(!self->dm_ops);
	assert(self->dm_elf.de_dynsym_tab);
	result = self->dm_elf.de_dynsym_cnt;
	if unlikely(!result) {
		/* Lazily calculate. */
		if (self->dm_elf.de_hashtab) {
			/* Legacy (ELF) hash tables contain a field for the # of symbols. */
			result = self->dm_elf.de_hashtab->ht_nchains;
		} else if (self->dm_elf.de_gnuhashtab) {
			ElfW(GnuHashTable) const *ht;
			ElfW(Word) const *buckets, *chains;
			/* GNU hash tables are a bit more complicated, since we need  to
			 * find the symbol with the greatest index, then add +1 to that. */
			ht      = self->dm_elf.de_gnuhashtab;
			buckets = (ElfW(Word) const *)(ht->gh_bloom + ht->gh_bloom_size);
			chains  = (ElfW(Word) const *)(buckets + ht->gh_nbuckets);
			result  = chains[-1];
			while ((chains[result - ht->gh_symoffset] & 1) == 0)
				++result;
		} else {
			/* Lastly,  we can figure out the # of symbols by looking
			 * as  section headers. We only do this as a last resort,
			 * since  the presence of  section headers isn't actually
			 * something that would be necessary to parse in a normal
			 * ELF binary, and as such  KOS's libdl tries to make  as
			 * few demands about its behavior as possible.
			 * Also: Section headers don't get loaded into memory by
			 *       default,  so accessing them carries the risk of
			 *       causing some kind of I/O or NOMEM error. */
			ElfW(Shdr) *sh;
			sh = DlModule_ElfGetShdrs(self);

			/* NOTE: Section headers may not be present, or we may have failed to load them... */
			if likely(sh) {
				ElfW(Addr) modrel_dynsym;
				size_t i, count;
				modrel_dynsym = ((ElfW(Addr))self->dm_elf.de_dynsym_tab -
				                 self->dm_loadaddr);

				/* Find  the section header that contains `.dynsym'. We could look at
				 * section names here, or even just search for a section that  starts
				 * with `modrel_dynsym'. However to minimize our expectations on what
				 * section headers  are actually  present, simply  assume that  we're
				 * looking for a `SHF_ALLOC' section containing `modrel_dynsym' */
				count = self->dm_elf.de_shnum;
				for (i = 0; i < count; ++i) {
					if (!(sh[i].sh_flags & SHF_ALLOC))
						continue;
					if (modrel_dynsym < sh[i].sh_addr)
						continue;
					if (modrel_dynsym >= sh[i].sh_addr + sh[i].sh_size)
						continue;

					/* Found it! */
					result = ((sh[i].sh_addr + sh[i].sh_size) - modrel_dynsym) /
					         sizeof(ElfW(Sym));
					break;
				}
			}
		}
		COMPILER_WRITE_BARRIER();
		self->dm_elf.de_dynsym_cnt = result;
		COMPILER_WRITE_BARRIER();
	}
	return result;
}



/* Return the section header associated with a given `name'
 * @return: NULL:             Error (w/ dlerror() set)
 * @return: (ElfW(Shdr) *)-1: Not found (w/o dlerror() set) */
INTERN WUNUSED NONNULL((1, 2)) ElfW(Shdr) *
NOTHROW_NCX(CC DlModule_ElfGetSection)(NCX DlModule *self,
                                       NCX char const *name)
		THROWS(E_SEGFAULT) {
	ElfW(Shdr) *result;
	uint16_t i;
	char *strtab;
	assert(!self->dm_ops);
	strtab = DlModule_ElfGetShstrtab(self);
	if unlikely(!strtab)
		goto err;
	result = self->dm_elf.de_shdr;
	assert(result);
	for (i = 0; i < self->dm_elf.de_shnum; ++i, ++result) {
		if (strcmp(strtab + result->sh_name, name) == 0)
			return result; /* Got it! */
	}
	return (ElfW(Shdr) *)-1;
err:
	return NULL;
}




DECL_END

#endif /* !GUARD_LIBDL_MODULE_C */
