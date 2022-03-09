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
#ifndef GUARD_LIBDL_PE_PE_C
#define GUARD_LIBDL_PE_PE_C 1
#define _KOS_SOURCE 1
#define _KOS_KERNEL_SOURCE 1
#define _KOS_ALTERATIONS_SOURCE 1
#define _GNU_SOURCE 1
#define _DOS_SOURCE 1

#include "api.h"
/**/

#include "pe.h"
/**/

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/wordbits.h>

#include <asm/intrin.h>
#include <kos/dosfs.h>
#include <kos/except.h>
#include <kos/exec/bits/peb.h>
#include <kos/syscalls.h>
#include <kos/thread.h>
#include <nt/libloaderapi.h>
#include <nt/tib.h>
#include <sys/ioctl.h>

#include <assert.h>
#include <ctype.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <limits.h>
#include <link.h>
#include <malloca.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <termios.h>
#include <unistd.h>

DECL_BEGIN

INTERN char *CC dlstrdup(char const *str) {
	size_t len   = (strlen(str) + 1) * sizeof(char);
	char *result = (char *)malloc(len);
	if (result)
		result = (char *)memcpy(result, str, len);
	return result;
}

INTERN ATTR_COLD int
NOTHROW(CC dl_seterror_nomem)(void) {
	return dl.dl_seterrorf("Insufficient memory");
}


PRIVATE WUNUSED NONNULL((2)) char *CC
dlfrealpathat(fd_t dirfd, char const *filename, atflag_t flags) {
	ssize_t result;
	size_t buflen;
	char *buffer, *resolved;
	/* Automatically allocate + determine buffer size. */
	buflen = PATH_MAX;
	buffer = (char *)malloc(buflen);
	if unlikely(!buffer)
		buflen = 0;
	for (;;) {
		result = sys_frealpathat(dirfd, filename, buffer, buflen,
		                         flags | AT_READLINK_REQSIZE);
		if unlikely(E_ISERR(result))
			goto err_buffer_result_errno;
		if likely((size_t)result <= buflen)
			break;
		/* Allocate the required amount of memory. */
		resolved = (char *)realloc(buffer, (size_t)result);
		if unlikely(!resolved) {
			free(buffer);
			dl_seterror_nomem();
			return NULL;
		}
		buflen = (size_t)result;
		buffer = resolved;
	}
	if ((size_t)result != buflen) {
		resolved = (char *)realloc(buffer, (size_t)result);
		if likely(resolved)
			buffer = resolved;
	}
	return buffer;
err_buffer_result_errno:
	free(buffer);
	dl.dl_seterrorf("dlfrealpathat(%q) failed: %s", filename,
	                strerrorname_np(-result));
	return NULL;
}



/* Wrapper for `dlsym()' that does all of the "DOS$" / "KOS$" prefix handling. */
DEFINE_PUBLIC_ALIAS(GetProcAddress, libpe_GetProcAddress);
INTERN void *WINAPI
libpe_GetProcAddress(DlModule *self, char const *symbol_name) {
	void *result;
	char *dos_symbol_name;
	size_t symbol_name_len;

	/* Check for special case: don't try to link against DOS symbols */
	if (memcmp(symbol_name, "KOS$", 4 * sizeof(char)) == 0)
		return dlsym(self, symbol_name + 4);

	/* Firstly: try to link against "DOS$"-prefixed symbols. */
	symbol_name_len = strlen(symbol_name);
	dos_symbol_name = (char *)malloca(4 + symbol_name_len + 1, sizeof(char));
	if unlikely(!dos_symbol_name) {
		dl_seterror_nomem();
		return NULL;
	}
	{
		RAII_FINALLY { freea(dos_symbol_name); };

		/* Construct the DOS$-prefixed symbol name. */
		*(uint32_t *)dos_symbol_name = ENCODE_INT32('D', 'O', 'S', '$');
		memcpy(dos_symbol_name + 4, symbol_name, symbol_name_len + 1, sizeof(char));
		result = dlsym(self, dos_symbol_name);
	}
	if (result)
		return result;

	/* Try again with the non-prefixed name. */
	result = dlsym(self, symbol_name);
	if (result) {
		/* Clear the error message set by the initial failed `dlsym()' */
		dl_globals.dg_errmsg = NULL;
	}
	return result;
}



struct librepl {
	char lr_orig[24]; /* Original file name */
	char lr_repl[8];  /* Replacement file name */
};

/* KOS replacements for NT system dlls. */
PRIVATE struct librepl const lib_replacements[] = {
	{ "msvcrt", /*          */ "libc.so" },
	{ "vcruntime140", /*    */ "libc.so" },
	{ "vcruntime140d", /*   */ "libc.so" },
	{ "ucrtbase", /*        */ "libc.so" },
	{ "ucrtbased", /*       */ "libc.so" },
	{ "msvcr80", /*         */ "libc.so" },
	{ "msvcr90", /*         */ "libc.so" },
	{ "msvcr100", /*        */ "libc.so" },
	{ "msvcr120", /*        */ "libc.so" },
	{ "msvcr120_clr0400", /**/ "libc.so" },
	{ "msvcrt20", /*        */ "libc.so" },
	{ "msvcrt40", /*        */ "libc.so" },
};



/* NOTE: `path[pathlen-1]' may or may not be a `/'
 * However, it is guarantied to not be a '\\', as well as that `path'
 * is  a unix path (though `filename' may contain NT path characters,
 * but is also guarantied not to be an absolute NT path, meaning that
 * sanitization only needs to replace '\\' with '/') */
PRIVATE NONNULL((1, 3)) REF DlModule *CC
libpe_LoadLibraryInPath(char const *__restrict path, size_t pathlen,
                        char const *__restrict filename, unsigned int flags) {
	char *usedname;
	REF DlModule *result;
	char *fullname, *iter;
	size_t i, fullnamelen, filenamelen;
	int has_nonstandard_extension = 0;
	if (!pathlen)
		return NULL; /* Disallow empty leading paths. */

	/* Strip trailing slashes. (NOTE: `path' is a unix path, so only strip '/') */
	while (pathlen && path[pathlen - 1] == '/')
		--pathlen;
	filenamelen = strlen(filename);
	if (filenamelen >= 4 && memcasecmp(filename + filenamelen - 4,
	                                   ".dll", 4 * sizeof(char)) == 0) {
		has_nonstandard_extension = INT_MIN;
		filenamelen -= 4;
	}
	if (!filenamelen)
		return NULL; /* Disallow empty filenames. */
	fullnamelen = pathlen +     /* "/lib" */
	              1 +           /* "/" */
	              3 +           /* "lib" */
	              filenamelen + /* "foo" */
	              4;            /* ".dll" */
	fullname = (char *)malloca(fullnamelen + 1, sizeof(char));
	RAII_FINALLY { freea(fullname); };

	/* Construct the full filename. */
	iter = (char *)mempcpy(fullname, path, pathlen, sizeof(char));
	*iter++ = '/';
	for (i = 0; i < filenamelen; ++i) {
		char ch = filename[i];

		/* Technically, we'd need to tell the kernel to ignore casing for
		 * this part of the filename. And technically that can be done by
		 * doing `openat(open("/lib"), "KERNEL32.dll", O_DOSPATH)'.
		 *
		 * However, that's a lot of overhead, and doesn't work well with
		 * the established dlopen()  function (which  doesn't feature  a
		 * dlopenat() variant; though I guess we could do the open here,
		 * and  then  use  `fdlopen()'...). Anyways:  to  ensure uniform
		 * filenames, we just convert everything to lowercase (for now).
		 *
		 * Sadly, this means that any dll you put on the system, you  have
		 * to rename to all lower-case in order for us to find it. If this
		 * ever  becomes too much of a hassle,  I might end up making this
		 * a 2-step process as described  above, just so the lookup  would
		 * ignore casing. */
		ch = tolower(ch);
		if (ch == '\\')
			ch = '/';
		if (ch == '.')
			++has_nonstandard_extension;
		iter[i] = ch;
	}
	usedname = iter;
	iter += filenamelen;
	*iter = '\0';
	if (has_nonstandard_extension <= 0)
		strcpy(iter, ".dll");

	/* Do the initial open attempt. */
	result = (REF DlModule *)dlopen(fullname, flags);
	if (result || has_nonstandard_extension > 0)
		return result;

	/* Replace the ".dll" suffix with ".so" */
	strcpy(iter, ".so");
	result = (REF DlModule *)dlopen(fullname, flags);
	if (result)
		return result;

	/* Insert a "lib" prefix before the library name. */
	memmoveup(usedname + 3, usedname,
	          (size_t)((iter + 4) - usedname),
	          sizeof(char));
	memcpy(usedname, "lib", 3, sizeof(char));
	iter += 3;

	/* Go back to the ".dll" suffix. */
	strcpy(iter, ".dll");
	result = (REF DlModule *)dlopen(fullname, flags);
	if (result)
		return result;

	/* And try once more with a ".so" suffix. */
	strcpy(iter, ".so");
	result = (REF DlModule *)dlopen(fullname, flags);
	if (result)
		return result;

	/* If stuff is still failing, check for special replacement files. */
	memmovedown(usedname, usedname + 3, (size_t)(iter - (usedname + 3)), sizeof(char));
	iter -= 3;
	*iter = '\0';
	{
		unsigned int i;
		for (i = 0; i < COMPILER_LENOF(lib_replacements); ++i) {
			if (strcmp(usedname, lib_replacements[i].lr_orig) != 0)
				continue;
			strcpy(usedname, lib_replacements[i].lr_repl);
			result = (REF DlModule *)dlopen(fullname, flags);
			/* Don't keep trying after the first match. -- We  can
			 * assume that there would be at most 1 match anyways. */
			return result;
		}
	}
	/* No replacement for this -- maybe it can be found in another folder? */

	return NULL;
}

/* NOTE: `pathlist' is a ':'-separated list of unix paths! */
PRIVATE NONNULL((1, 2)) REF DlModule *CC
libpe_LoadLibraryInPathList(char const *__restrict pathlist,
                            char const *__restrict filename,
                            unsigned int flags) {
	REF DlModule *result;
	for (;;) {
		size_t len;
		len    = stroff(pathlist, ':');
		result = libpe_LoadLibraryInPath(pathlist, len, filename, flags);
		if (result != NULL)
			break;
		if (pathlist[len] == '\0')
			break;
		pathlist += len + 1;
	}
	return result;
}



DEFINE_PUBLIC_ALIAS(PeLoadLibrary, libpe_LoadLibrary);
INTERN NONNULL((1)) REF DlModule *CC
libpe_LoadLibrary(char const *__restrict filename, unsigned int flags) {
	REF DlModule *result;
	if ((filename[0] && filename[1] == ':') ||
	    (filename[0] == '\\' || filename[0] == '/')) {
		/* Absolute NT path. */
		char *nixpath = dlfrealpathat(AT_FDCWD, filename, AT_DOSPATH | AT_ALTPATH);
		if unlikely(!nixpath)
			goto err;
		result = (REF DlModule *)dlopen(nixpath, flags);
		free(nixpath);
		return result;
	}

	/* The library search order on NT works as follows:
	 * #1: `dirname $(dlmodulename(dlopen(NULL, 0)))` -- The directory from which the application loaded.
	 * #2: `pwd`                                      -- The current directory.
	 * #3: GetSystemDirectory             (we use `dl_globals.dg_libpath' ($LD_LIBRARY_PATH) in place of this)
	 * #4: <The 16-bit system directory>  (we skip this one)
	 * #5: GetWindowsDirectory            (we skip this one)
	 * #6: $PATH
	 *
	 * NOTES:
	 *  - For every path  searched, we automatically  convert NT  paths
	 *    into unix paths (via `frealpathat(AT_DOSPATH | AT_ALTPATH)').
	 *  - If a filename matches "*.dll", we do a second search for another
	 *    file for "*.so", followed by yet another file matching "lib*.so"
	 *  - We replace a couple of library names with known KOS equivalents:
	 *    "msvcrt.dll" --> "libc.so"
	 *    But note that this is only done after an initial search attempt
	 *    already failed.
	 */

	/* #1: Search dirname of the base application. */
	{
		char *appname;
		appname = dlglobals_mainapp(&dl_globals)->dm_filename;
		result  = libpe_LoadLibraryInPath(appname, strroff(appname, '/'), filename, flags);
		if (result)
			goto done;
	}

	/* #2: Search the current working directory. */
	result = libpe_LoadLibraryInPath(".", 1, filename, flags);
	if (result)
		goto done;

	/* #3: Search `dl_globals.dg_libpath' ($LD_LIBRARY_PATH) */
	result = libpe_LoadLibraryInPathList(dl_globals.dg_libpath, filename, flags);
	if (result)
		goto done;

	/* #6: $PATH (#4 + #5 we skip) */
	{
		char *path = getenv("PATH");
		result = libpe_LoadLibraryInPathList(path, filename, flags);
		if (result)
			goto done;
	}

	dl_globals.dg_errmsg = NULL;
err:
	return NULL;
done:
	dl_globals.dg_errmsg = NULL;
	return result;
}


PRIVATE NONNULL((1)) int CC
DlModule_PeInitializeImportTable(DlModule *__restrict self) {
	if (self->dm_depcnt) {
		PIMAGE_DATA_DIRECTORY imports = DlModule_GetImports(self);
		PIMAGE_IMPORT_DESCRIPTOR iter, end;
		unsigned int dep_flags;
		size_t count    = self->dm_depcnt;
		self->dm_depcnt = 0;
		self->dm_depvec = (REF DlModule **)malloc(count * sizeof(REF DlModule *));
		if unlikely(!self->dm_depvec)
			goto err_nomem;
		dep_flags = RTLD_GLOBAL | (self->dm_flags & RTLD_NOINIT);
		iter = (PIMAGE_IMPORT_DESCRIPTOR)(self->dm_loadaddr + imports->VirtualAddress);
		end  = (PIMAGE_IMPORT_DESCRIPTOR)((byte_t *)iter + imports->Size);
		for (; iter < end; ++iter) {
			/* Import module symbols. */
			PIMAGE_THUNK_DATA thunk_iter1, thunk_iter2;
			char const *filename;
			REF DlModule *dependency;
			DWORD thunk1, thunk2;
			size_t i;

			/* The import table can be terminated by a ZERO-entry.
			 * https://msdn.microsoft.com/en-us/library/ms809762.aspx */
			if (!iter->Characteristics && !iter->TimeDateStamp &&
			    !iter->ForwarderChain && !iter->Name && !iter->FirstThunk)
				break;
			assert(self->dm_depcnt < count);
			filename = (char *)(self->dm_loadaddr + iter->Name);
			syslog(LOG_DEBUG, "[pe] import: %q\n", filename);
			dependency = libpe_LoadLibrary(filename, dep_flags);
			if (!dependency) {
				if (ATOMIC_READ(dl_globals.dg_errmsg) == NULL)
					dl.dl_seterrorf("Failed to load dependency %q of %q",
					                filename, self->dm_filename);
				goto err;
			}
			self->dm_depvec[self->dm_depcnt++] = dependency; /* Inherit reference */

			/* Resolve imported symbols. */
			thunk1 = iter->OriginalFirstThunk ? iter->OriginalFirstThunk : iter->FirstThunk;
			thunk2 = iter->FirstThunk ? iter->FirstThunk : iter->OriginalFirstThunk;
			thunk_iter1 = (PIMAGE_THUNK_DATA)(self->dm_loadaddr + thunk1);
			thunk_iter2 = (PIMAGE_THUNK_DATA)(self->dm_loadaddr + thunk2);
			for (;; ++thunk_iter1, ++thunk_iter2) {
				PIMAGE_IMPORT_BY_NAME ent;
				void *addr;
				if (!thunk_iter1->u1.AddressOfData)
					break; /* ZERO-Terminated. */
				ent = (PIMAGE_IMPORT_BY_NAME)(self->dm_loadaddr + thunk_iter1->u1.AddressOfData);
				/* Import the symbol. */
				syslog(LOG_DEBUG, "[pe] GetProcAddress(%q, %q)\n",
				       dependency->dm_filename, ent->Name);
				addr = libpe_GetProcAddress(dependency, ent->Name);
				if (!addr && dl_globals.dg_errmsg != NULL) {
					dl.dl_seterrorf("%q: Symbol %q missing from %q",
					                self->dm_filename, ent->Name,
					                dependency->dm_filename);
					goto err;
				}
				thunk_iter1->u1.AddressOfData = (uintptr_t)addr;
				thunk_iter2->u1.AddressOfData = (uintptr_t)addr;
			}

			/* Check if `dependency' had already been loaded
			 * -> This can happen due to `lib_replacements' */
			for (i = 0; i < self->dm_depcnt - 1; ++i) {
				if (self->dm_depvec[i] == dependency) {
					/* Don't duplicate dependencies */
					--self->dm_depcnt;
					dlclose(dependency);
					break;
				}
			}

		}
	}
	return 0;
err_nomem:
	dl_seterror_nomem();
err:
	return -1;
}

PRIVATE NONNULL((1)) int CC
DlModule_PeInitializeRelocations(DlModule *__restrict self) {
	PIMAGE_DATA_DIRECTORY relocs;
	PIMAGE_BASE_RELOCATION iter, end;
	uintptr_t delta;
	if (!DlModule_HasRelocs(self))
		goto done;
	delta = self->dm_loadaddr - self->dm_pe.dp_nt.OptionalHeader.ImageBase;
	if (delta == 0)
		goto done; /* Already properly relocated. */
	relocs = DlModule_GetRelocs(self);
	iter   = (PIMAGE_BASE_RELOCATION)(self->dm_loadaddr + relocs->VirtualAddress);
	end    = (PIMAGE_BASE_RELOCATION)((uintptr_t)iter + relocs->Size);
	while (iter < end) {
		uintptr_t rel_base;
		WORD *rel_iter, *rel_end;
		if (iter->SizeOfBlock < sizeof(IMAGE_BASE_RELOCATION))
			break;
		/* Load this relocation block. */
		rel_base = self->dm_loadaddr + iter->VirtualAddress;
		rel_iter = (WORD *)(self + 1);
		iter     = (PIMAGE_BASE_RELOCATION)((byte_t *)iter + iter->SizeOfBlock);
		rel_end  = (WORD *)iter;
		for (; rel_iter < rel_end; ++rel_iter) {
			WORD word = *rel_iter;
			uintptr_t rel_addr;
			uint8_t rel_type; /* actually 4-bit (uint_least4_t) */
			rel_addr = rel_base + (word & 0xfff);
			rel_type = word >> 12;
			switch (rel_type) {

			case IMAGE_REL_BASED_ABSOLUTE:
				/* QUOTE: "The base relocation is skipped" */
				break;

#if __SIZEOF_POINTER__ > 4
			case IMAGE_REL_BASED_HIGHLOW:
				*(u32 *)rel_addr += (uint32_t)delta;
				break;
			case IMAGE_REL_BASED_HIGHADJ:
				*(u32 *)rel_addr += (uint32_t)(delta >> 32);
				break;
#else /* __SIZEOF_POINTER__ > 4 */
			case IMAGE_REL_BASED_HIGHLOW:
			case IMAGE_REL_BASED_HIGHADJ:
				*(u32 *)rel_addr += delta;
				break;
#endif /* __SIZEOF_POINTER__ <= 4 */

			case IMAGE_REL_BASED_LOW:
				*(u16 *)rel_addr += delta & 0xffff;
				break;
			case IMAGE_REL_BASED_HIGH:
				*(u16 *)rel_addr += (delta & 0xffff0000) >> 16;
				break;

			case IMAGE_REL_BASED_DIR64:
				*(u64 *)rel_addr += (u64)delta;
				break;

			default:
				return dl.dl_seterrorf("%q: Unknown relocation %" PRIu8 " at %p (%p)",
				                       self->dm_filename, rel_type, rel_addr,
				                       rel_addr - self->dm_loadaddr);
			}
		}
	}
done:
	return 0;
}


PRIVATE NONNULL((1)) void CC
DlModule_PeTlsDoExec(DlModule *__restrict self, DWORD reason) {
	PIMAGE_TLS_CALLBACK const *functions;
	for (functions = self->dm_pe.dp_tlscalls; *functions; ++functions)
		(**functions)(self, reason, NULL);
}

PRIVATE NONNULL((1, 2)) void CC
DlModule_PeTlsExec(DlModule *__restrict self, void *base, DWORD reason) {
	void **pmodtls, *oldbase;

	/* Technically,  PE TLS should be initialized in the context of the
	 * thread it is meant to be used for. -- This isn't something  that
	 * is guarantied for KOS-style dlfcn tls initializers (which we are
	 * basing our's on, so that `dltlsaddr()' will work for PE modules)
	 *
	 * As such, we hijack the calling thread's TLS base pointer for  the
	 * relevant module and temporarily override it. If it already didn't
	 * differ, then nothing will be lost and emulation is 100%. */
	pmodtls  = &_GetNativePeTlsArray()[self->dm_pe.dp_tlsindex];
	oldbase  = *pmodtls;
	*pmodtls = base;
	RAII_FINALLY { *pmodtls = oldbase; };
	DlModule_PeTlsDoExec(self, reason);
}

PRIVATE void DLFCN_CC
DlModule_PeTlsInit(void *arg, void *base) {
	DlModule_PeTlsExec((DlModule *)arg, base, DLL_THREAD_ATTACH);
}

PRIVATE void DLFCN_CC
DlModule_PeTlsFini(void *arg, void *base) {
	DlModule_PeTlsExec((DlModule *)arg, base, DLL_THREAD_DETACH);
}


/* Next TLS index to hand out. */
PRIVATE uintptr_t pe_nexttlsindex = 0;
PRIVATE uintptr_t NOTHROW(CC PeTls_AllocIndex)(void) {
	return pe_nexttlsindex++;
}
PRIVATE void NOTHROW(CC PeTls_FreeIndex)(uintptr_t index) {
	COMPILER_IMPURE();
	(void)index;
}

/* Allocate a TLS vector for use as `_GetNativePeTlsArray()'. */
PRIVATE void **CC PeTls_AllocVector(bool forme) {
	size_t count;
	void **result;
	DlModule *iter;
	count  = ATOMIC_READ(pe_nexttlsindex);
	result = (void **)calloc(count, sizeof(void *));
	if (!result)
		return NULL;
	atomic_rwlock_read(&dl_globals.dg_alllock);
	DLIST_FOREACH (iter, &dl_globals.dg_alllist, dm_modules) {
		void *block;
		if (iter->dm_ops != &libpe_fmt)
			continue;
		if (iter->dm_tlsmsize == 0)
			continue;
		if (iter->dm_pe.dp_tlsindex >= count)
			continue; /* Shouldn't happen... */
		block = memalign(iter->dm_tlsalign, iter->dm_tlsmsize);
		if (!block)
			goto err;
		result[iter->dm_pe.dp_tlsindex] = block;
		if (iter->dm_pe.dp_tlscalls) {
			if (forme) {
				DlModule_PeTlsDoExec(iter, DLL_THREAD_ATTACH);
			} else {
				DlModule_PeTlsInit(iter, block);
			}
		}
	}
	atomic_rwlock_endread(&dl_globals.dg_alllock);
	return result;
err:
	DLIST_FOREACH (iter, &dl_globals.dg_alllist, dm_modules) {
		void *block;
		if (iter->dm_ops != &libpe_fmt)
			continue;
		if (iter->dm_tlsmsize == 0)
			continue;
		if (iter->dm_pe.dp_tlsindex >= count)
			continue;
		block = result[iter->dm_pe.dp_tlsindex];
		if (!block)
			continue;
		if (iter->dm_pe.dp_tlscalls) {
			if (forme) {
				DlModule_PeTlsDoExec(iter, DLL_THREAD_DETACH);
			} else {
				DlModule_PeTlsFini(iter, block);
			}
		}
		free(block);
	}
	atomic_rwlock_endread(&dl_globals.dg_alllock);
	free(result);
	return NULL;
}



PRIVATE NONNULL((1)) int CC
DlModule_PeInitialize(DlModule *__restrict self) {
	int result;

	/* Load dependencies of the module. */
	result = DlModule_PeInitializeImportTable(self);
	if (result != 0)
		goto done;

	/* Apply relocations */
	result = DlModule_PeInitializeRelocations(self);
	if (result != 0)
		goto done;

	if (DlModule_HasTls(self)) {
		/* Load TLS, as per the specs:
		 * >> https://en.wikipedia.org/wiki/Win32_Thread_Information_Block
		 * >> https://docs.microsoft.com/en-us/windows/win32/debug/pe-format
		 *
		 * On PE, TLS works as follows:
		 * >> __declspec(thread) int my_symbol;
		 * >> static void set() {
		 * >>     my_symbol = 42;
		 * >> }
		 *
		 * Same as:
		 * >> uintptr_t *tls_index = tls->AddressOfIndex;  // DlModule_GetTlsDir(self)
		 * >> #ifdef __x86_64__
		 * >> void **tls_vector = *(void ***)%gs:0x58;
		 * >> #else
		 * >> void **tls_vector = *(void ***)%fs:0x2c;
		 * >> #endif
		 * >> void *mytls    = tls_vector[*tls_index];
		 * >> int *my_symbol = mytls + OFFSET_OF_MY_SYMBOL;
		 * >> *my_symbol = 42;
		 *
		 * This is  pretty much  the same  as ELF's  dynamic TLS  approach.
		 * However, there's a  problem here  when it comes  to loading  new
		 * libraries that require TLS: because there is no __tls_get_addr()
		 * function, we can't  do lazy  initialization of TLS  blocks on  a
		 * per-thread  basis; no: _all_ TLS must be allocated from the very
		 * start of a thread, and  loading new libraries with TLS  requires
		 * us to expand the TLS vector of every running thread also.
		 *
		 * Because of how complicated that would be, for now we take  the
		 * easy way out by saying that a PE library w/ TLS that is loaded
		 * after  the fact, will only be allocated the thread that loaded
		 * it, or any thread created thereafter. */
		PIMAGE_TLS_DIRECTORY tls;
		tls = DlModule_GetTlsDir(self);

		self->dm_tlsoff   = (ElfW(Off))-1; /* Unused for PE */
		self->dm_tlsinit  = (byte_t *)(/*self->dm_loadaddr + */ tls->StartAddressOfRawData);
		self->dm_tlsfsize = tls->EndAddressOfRawData - tls->StartAddressOfRawData;
		self->dm_tlsmsize = self->dm_tlsfsize + tls->SizeOfZeroFill;
		/*self->dm_tlsstoff = 0;*/ /* We don't have ELF-style static TLS (iow: direct %fs/%gs-offsets) */

		if (self->dm_tlsmsize) {
			/* We can figure out the required alignment from `tls->Characteristics' */
			self->dm_tlsalign = 1;
			if (tls->Characteristics & IMAGE_SCN_ALIGN_MASK)
				self->dm_tlsalign = (size_t)1 << (((tls->Characteristics & IMAGE_SCN_ALIGN_MASK) >> 20) - 1);
			self->dm_tls_init = NULL;
			self->dm_tls_fini = NULL;

			/* Allocate a TLS index */
			self->dm_pe.dp_tlsindex = PeTls_AllocIndex();

			/* Store TLS index in module structure. */
			*(uintptr_t *)(/*self->dm_loadaddr + */tls->AddressOfIndex) = self->dm_pe.dp_tlsindex;

			/* Check for TLS initialization callbacks. */
			if (tls->AddressOfCallBacks) {
				PIMAGE_TLS_CALLBACK *tls_callbacks;
				tls_callbacks = (PIMAGE_TLS_CALLBACK *)(/*self->dm_loadaddr + */tls->AddressOfCallBacks);
				if (*tls_callbacks) {
					self->dm_pe.dp_tlscalls = tls_callbacks;
					self->dm_tls_init       = &DlModule_PeTlsInit;
					self->dm_tls_fini       = &DlModule_PeTlsFini;
					self->dm_tls_arg        = self;
				}
			}
		}
	}

	/* TODO: Make non-writable sections read-only. */

done:
	return result;
}



PRIVATE NONNULL((1, 2)) REF DlModule *LIBDL_CC
libpe_v_open(byte_t const header[DL_MODULE_MAXMAGIC],
             /*inherit(on_success,HEAP)*/ char *__restrict filename,
             /*inherit(on_success)*/ fd_t fd) {
	/* TODO */
	(void)header;
	(void)filename;
	(void)fd;
	COMPILER_IMPURE();
	return DLMODULE_FORMAT_OPEN_BAD_MAGIC;
}

PRIVATE NONNULL((1)) void LIBDL_CC
libpe_v_fini(DlModule *__restrict self) {
	if (self->dm_tlsmsize != 0)
		PeTls_FreeIndex(self->dm_pe.dp_tlsindex);
	/* TODO */
	(void)self;
	COMPILER_IMPURE();
}

PRIVATE NONNULL((1)) bool LIBDL_CC
libpe_v_ismapped(DlModule *__restrict self,
                 uintptr_t module_relative_pointer) {
	/* TODO */
	(void)self;
	(void)module_relative_pointer;
	COMPILER_IMPURE();
	return false;
}

PRIVATE NONNULL((1, 2, 3)) int LIBDL_CC
libpe_v_dlsym(DlModule *__restrict self,
              char const *__restrict symbol_name,
              void **__restrict psymbol_addr,
              size_t *psymbol_size) {
	/* TODO */
	(void)self;
	(void)symbol_name;
	(void)psymbol_addr;
	(void)psymbol_size;
	COMPILER_IMPURE();
	return DLMODULE_FORMAT_DLSYM_ERROR;
}

PRIVATE NONNULL((1)) int LIBDL_CC
libpe_v_dladdr(DlModule *__restrict self,
               uintptr_t module_relative_pointer,
               struct __dl_info_struct *info) {
	/* TODO */
	(void)self;
	(void)module_relative_pointer;
	(void)info;
	COMPILER_IMPURE();
	return -1;
}

PRIVATE NONNULL((1, 2)) uintptr_t LIBDL_CC
libpe_v_dlsectindex(DlModule *__restrict self,
                    char const *__restrict name) {
	/* TODO */
	(void)self;
	(void)name;
	return (uintptr_t)-1;
}

PRIVATE NONNULL((1, 3)) int LIBDL_CC
libpe_v_dlsectinfo(DlModule *__restrict self, uintptr_t index,
                   struct dl_sect_info *__restrict result) {
	/* TODO */
	(void)self;
	(void)index;
	(void)result;
	return (*dl.dl_seterrorf)("Not implemented");
}

PRIVATE NONNULL((1)) char const *LIBDL_CC
libpe_v_dlsectname(DlModule *__restrict self, uintptr_t index) {
	/* TODO */
	(void)self;
	(void)index;
	(*dl.dl_seterrorf)("Not implemented");
	return NULL;
}

PRIVATE NONNULL((1, 2, 3)) int LIBDL_CC
libpe_v_lsphdrs(DlModule *__restrict self,
                struct dl_phdr_info *__restrict info,
                __dl_iterator_callback callback, void *arg) {
	/* TODO */
	(void)self;
	(void)info;
	(void)callback;
	(void)arg;
	return 0;
}

PRIVATE PNT_TIB CC libpe_AllocateTib(void) {
	PNT_TIB result;
	result = (PNT_TIB)calloc(1, sizeof(NT_TIB));
	if (result)
		result->Self = result;
	return result;
}



INTERN struct dlmodule_format libpe_fmt = {
	.df_magic            = { 'M', 'Z' },
	.df_magsz            = 2,
	.df_open             = &libpe_v_open,
	.df_fini             = &libpe_v_fini,
	.df_run_initializers = NULL, /* XXX: Call DllMain()? */
	.df_run_finalizers   = NULL, /* XXX: Call DllMain()? */
	.df_ismapped         = &libpe_v_ismapped,
	.df_dlsym            = &libpe_v_dlsym,
	.df_dladdr           = &libpe_v_dladdr,
	.df_dlsectindex      = &libpe_v_dlsectindex,
	.df_dlsectinfo       = &libpe_v_dlsectinfo,
	.df_dlsectname       = &libpe_v_dlsectname,
	.df_lsphdrs          = &libpe_v_lsphdrs,
};


/* Called by `-Wl,-init=libpe_init' */
INTERN void libpe_init(void) {
	/* Register the PE loader extension for libdl */
	dlauxctrl(NULL, DLAUXCTRL_REGISTER_EXTENSION,
	          &libpe_fmt,
	          sizeof(struct dlmodule_format),
	          sizeof(struct dlcore_ops));

	/* Make sure that the registration was successful */
	if unlikely(libpe_fmt.df_core == NULL) {
		struct termios ios;
		char const *error = dlerror();
		syslog(LOG_ERR, "Failed to hook PE libdl-extension: %s\n", error);
		if (sys_ioctl(STDERR_FILENO, TCGETA, &ios) >= 0) {
			sys_write(STDERR_FILENO, "PE: ", 4);
			sys_write(STDERR_FILENO, error, strlen(error));
			sys_write(STDERR_FILENO, "\n", 1);
		}
		sys_exit_group(EXIT_FAILURE);
	}
}


/************************************************************************/
/* Handling for when a PE program's _start() does a `ret'               */
/************************************************************************/
INTERN ATTR_NORETURN void FCALL
pe_exit_wrapper(int exit_code) {
	_Exit(exit_code);
}

INTDEF void pe_exit_wrapper_asm(void);
__asm__(".pushsection .text\n"
        ".global pe_exit_wrapper_asm\n"
        ".hidden pe_exit_wrapper_asm\n"
        ".type pe_exit_wrapper_asm, @function\n"
        "pe_exit_wrapper_asm:\n"
#ifdef __x86_64__
        "	movq   %rax, %rdi\n"
#else /* __x86_64__ */
        "	movl   %eax, %ecx\n"
#endif /* !__x86_64__ */
        "	call   pe_exit_wrapper\n"
        "	.size pe_exit_wrapper_asm, . - pe_exit_wrapper_asm\n"
        ".popsection");


/* Replacement for `linker_main' from `libdl.so' when a PE binary gets executed. */
DEFINE_PUBLIC_ALIAS(__linker_main, libpe_linker_main);
INTERN void *FCALL
libpe_linker_main(struct peexec_info *__restrict info,
                  uintptr_t loadaddr,
                  struct process_peb *__restrict peb) {
	PNT_TIB tib;
	void *result;
	DlModule *mod;
	char *filename;
	struct peexec_data *pe = peexec_info__pi_pe(info);

	/* Turn on dosfs emulation for `DOS$'-prefixed functions in libc. */
	dosfs_setenabled(DOSFS_ENABLED);

	/* Another dos compatibility detail: support for '%n' in format strings is disabled by default. */
	_set_printf_count_output(0);

#if 0
	/* Dump some information to the system log. */
	syslog(LOG_DEBUG, "[pe] info->pi_rtldaddr                         = %p\n", info->pi_rtldaddr);
	syslog(LOG_DEBUG, "[pe] info->pi_pnum                             = %#I16x\n", info->pi_pnum);
	syslog(LOG_DEBUG, "[pe] info->pi_libdl_pe                         = %q\n", info->pi_libdl_pe);
	syslog(LOG_DEBUG, "[pe] pe->pd_nt.Signature                       = %#I32x\n", pe->pd_nt.Signature);
	syslog(LOG_DEBUG, "[pe] pe->pd_nt.FileHeader.Machine              = %#I16x\n", pe->pd_nt.FileHeader.Machine);
	syslog(LOG_DEBUG, "[pe] pe->pd_nt.FileHeader.NumberOfSections     = %#I16x\n", pe->pd_nt.FileHeader.NumberOfSections);
	syslog(LOG_DEBUG, "[pe] pe->pd_nt.FileHeader.TimeDateStamp        = %#I32x\n", pe->pd_nt.FileHeader.TimeDateStamp);
	syslog(LOG_DEBUG, "[pe] pe->pd_nt.FileHeader.PointerToSymbolTable = %#I32x\n", pe->pd_nt.FileHeader.PointerToSymbolTable);
	syslog(LOG_DEBUG, "[pe] pe->pd_nt.FileHeader.NumberOfSymbols      = %#I32x\n", pe->pd_nt.FileHeader.NumberOfSymbols);
	syslog(LOG_DEBUG, "[pe] pe->pd_nt.FileHeader.SizeOfOptionalHeader = %#I16x\n", pe->pd_nt.FileHeader.SizeOfOptionalHeader);
	syslog(LOG_DEBUG, "[pe] pe->pd_nt.FileHeader.Characteristics      = %#I16x\n", pe->pd_nt.FileHeader.Characteristics);
	syslog(LOG_DEBUG, "[pe] pe->pd_name                               = %q\n", peexec_data__pd_name(pe));
#endif

	if (peb->pp_argc) {
		char *argv0 = peb->pp_argv[0];
		if (argv0 && argv0[0] == '/') {
			/* The system gave  us an absolute  unix-style path as  argv[0].
			 * Because argv[0]  is traditionally  the  name of  the  program
			 * (even though use of `exec*()' doesn't make that a necessity),
			 * we automagically convert that argument into a DOS-path. */
			argv0 = dlfrealpathat(AT_FDCWD, argv0, AT_ALTPATH);
			if unlikely(!argv0)
				goto err_nomem;
			peb->pp_argv[0] = argv0;
		}
	}

	/* Allocate the DL module descriptor for the PE binary. */
	mod = (DlModule *)malloc(offsetof(DlModule, dm_pe.dp_sect) +
	                         (pe->pd_nt.FileHeader.NumberOfSections *
	                          sizeof(IMAGE_SECTION_HEADER)));
	if unlikely(!mod)
		goto err_nomem;

	/* Duplicate the caller-given filename. */
	filename = peexec_data__pd_name(pe);
	result   = (void *)CEIL_ALIGN((uintptr_t)(strend(filename) + 1), sizeof(void *));
	filename = strdup(filename);
	if unlikely(!filename)
		goto err_nomem; /* Leaks don't matter; we're only called once during init! */
#if 0
	syslog(LOG_DEBUG, "[pe] ENTRY:%p@%p\n", *(void **)result, (void **)result + 1);
#endif

	/* Initialize simple fields of the new module. */
	mod->dm_loadaddr   = loadaddr;
	mod->dm_filename   = filename; /* Inherit */
	mod->dm_dynhdr     = NULL;     /* Only exists under ELF */
	mod->dm_tlsoff     = 0;
	mod->dm_tlsinit    = NULL;
	mod->dm_tlsfsize   = 0;
	mod->dm_tlsmsize   = 0;
	mod->dm_tlsalign   = 0;
	mod->dm_tlsstoff   = 0;
	mod->dm_tls_init   = NULL;
	mod->dm_tls_fini   = NULL;
	mod->dm_tls_arg    = NULL;
	mod->dm_refcnt     = 1;
	mod->dm_weakrefcnt = 1;
	mod->dm_file       = -1;
	mod->dm_flags      = RTLD_LAZY | RTLD_GLOBAL | RTLD_NODELETE | RTLD_NOINIT | RTLD_LOADING;
	mod->dm_loadstart  = pe->pd_loadmin;
	mod->dm_loadend    = pe->pd_loadmax + 1;
	mod->dm_finalize   = NULL;

	/* Fill in section information. */
	mod->dm_shnum = pe->pd_nt.FileHeader.NumberOfSections;
	atomic_rwlock_init(&mod->dm_sections_lock);
	mod->dm_sections = (DlSection **)calloc(mod->dm_shnum, sizeof(DlSection *));
	if unlikely(!mod->dm_sections)
		goto err_nomem; /* Leaks don't matter; we're only called once during init! */
	mod->dm_sections_dangling = NULL;
	mod->dm_ops               = &libpe_fmt;

	/* Copy over PE information. */
	{
		size_t size;
		size = offsetof(IMAGE_NT_HEADERS, OptionalHeader) + pe->pd_nt.FileHeader.SizeOfOptionalHeader;
		if unlikely(size > sizeof(IMAGE_NT_HEADERS))
			size = sizeof(IMAGE_NT_HEADERS);
		bzero(mempcpy(&mod->dm_pe.dp_nt, &pe->pd_nt, size),
		      sizeof(IMAGE_NT_HEADERS) - size);
		memcpy(&mod->dm_pe.dp_sect, peexec_data__pd_sect(pe),
		       pe->pd_nt.FileHeader.NumberOfSections,
		       sizeof(IMAGE_SECTION_HEADER));
	}

	/* Count the # of in library dependencies */
	mod->dm_depcnt = 0;
	mod->dm_depvec = NULL;
	if (DlModule_HasImports(mod)) {
		PIMAGE_DATA_DIRECTORY imports = DlModule_GetImports(mod);
		PIMAGE_IMPORT_DESCRIPTOR iter, end;
		iter = (PIMAGE_IMPORT_DESCRIPTOR)(mod->dm_loadaddr + imports->VirtualAddress);
		end  = (PIMAGE_IMPORT_DESCRIPTOR)((byte_t *)iter + imports->Size);
		for (; iter < end; ++iter) {
			/* The import table can be terminated by a ZERO-entry.
			 * https://msdn.microsoft.com/en-us/library/ms809762.aspx */
			if (!iter->Characteristics && !iter->TimeDateStamp &&
			    !iter->ForwarderChain && !iter->Name && !iter->FirstThunk)
				break;
			++mod->dm_depcnt;
		}
	}

	/* Allocate a TIB for the calling thread. - Required to
	 * prevent SEH inline code from talking to the userkern
	 * segment.
	 *
	 * TODO: This must also happen in `pthread_create(3)'! */
	tib = libpe_AllocateTib();
	if (!tib)
		goto err_nomem;

	/* Assign TIB */
	_SetTib(tib);

	/* Hack: temporarily use the TIB's self-pointer as ELF TLS  register.
	 * This will be overwritten sometime later in `libdl.so:linker_main',
	 * but until then we need `%segtls:0'  to already resolve to a  valid
	 * value, since that one's used by `__hybrid_gettid()', which is used
	 * by  `atomic_owner_rwlock_write()',  which is  used  by `dlopen()',
	 * which we are using to load dependencies of the main PE. */
	WR_TLS_BASE_REGISTER(&tib->Self);

	/* Fill in some missing fields in the TIB */
	{
#define USER_STACK_SIZE (64 * __ARCH_PAGESIZE) /* TODO: Don't put this here! */
		uintptr_t stackend = (uintptr_t)((void **)result + 1);
		tib->StackBase  = (PVOID)(stackend - USER_STACK_SIZE);
		tib->StackLimit = (PVOID)stackend;
	}

	/* Hook the newly created module. */
	DLIST_INSERT_AFTER(dl.dl_rtld_module, mod, dm_modules);        /* NOTE: _MUST_ insert after builtin DL module! */
	TAILQ_INSERT_HEAD(&dl_globals.dg_globallist, mod, dm_globals); /* NOTE: _MUST_ insert at head! */

	/* Initialize the PE module. */
	if (DlModule_PeInitialize(mod) != 0)
		return NULL;

	/* Mark this module as having been fully loaded. */
	ATOMIC_AND(mod->dm_flags, ~RTLD_LOADING);

	/* Initial the PE TLS vector for the calling thread. */
	if (pe_nexttlsindex != 0)
		tib->NativePeTlsArray = PeTls_AllocVector(true);

	/* The entry point of PE applications is allowed to return normally.
	 * -> When it does, we simply have to `_Exit(%Pax)' the application. */
	result = (byte_t *)result - sizeof(void *);
	((void **)result)[0] = ((void **)result)[1];         /* Original entry point */
	((void **)result)[1] = (void *)&pe_exit_wrapper_asm; /* Have entry point return here */

	if (pe_nexttlsindex != 0) {
		/* TODO: Must inject another indirect function to-be called before `*result',
		 *       that will copy the base addresses of PE TLS segments allocated above
		 *       into the TLS  extension table  of the  ELF-TLS context  of the  main
		 *       thread.
		 * >> struct tls_segment *me;
		 * >> RD_TLS_BASE_REGISTER(*(void **)&me);
		 * >> FOREACH (pemod: dl_globals.dg_alllist) {
		 * >>     if (!HAS_TLS(pemod))
		 * >>         continue;
		 * >>     struct dtls_extension *node = malloc();
		 * >>     node->te_module = pemod;
		 * >>     node->te_data   = TLS_BASE_IN_MAIN_THREAD(pemod);
		 * >>     dtls_extension_tree_insert(&me->ts_extree, node);
		 * >> }
		 */
	}

	/* Return a pointer to the PE program entry point. */
	return result;
err_nomem:
	dl_seterror_nomem();
	return NULL;
}

DECL_END

#endif /* !GUARD_LIBDL_PE_PE_C */
