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

#include "api.h"
/**/

#include "pe.h"
/**/

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/wordbits.h>

#include <kos/except.h>
#include <kos/syscalls.h>
#include <sys/ioctl.h>

#include <assert.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <link.h>
#include <malloca.h>
#include <stdlib.h>
#include <syslog.h>
#include <termios.h>
#include <unistd.h>

DECL_BEGIN

INTERN char *CC dlstrdup(char const *str) {
	syslog(LOG_DEBUG, "dlstrdup(%q)\n", str);
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
INTERN void *ATTR_STDCALL
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
		*dl.dl_error_message = NULL;
	}
	return result;
}


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
		 * dlopenat() variant), so to ensure uniform filenames, we  just
		 * convert everything to lowercase.
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
	if (strcmp(usedname, "msvcrt.so") == 0) {
		strcpy(usedname, "libc.so");
		result = (REF DlModule *)dlopen(fullname, flags);
		if (result)
			return result;
	} else {
		/* No replacement for this -- maybe it can be found in another folder? */
	}

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
	 * #3: GetSystemDirectory             (we use `dl_library_path' in place of this)
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
		appname = dl.DlModule_GlobalList->lh_first->dm_filename;
		result = libpe_LoadLibraryInPath(appname, strroff(appname, '/'),
		                                 filename, flags);
		if (result)
			goto done;
	}

	/* #2: Search the current working directory. */
	result = libpe_LoadLibraryInPath(".", 1, filename, flags);
	if (result)
		goto done;

	/* #3: Search `dl_library_path' */
	result = libpe_LoadLibraryInPathList(*dl.dl_library_path, filename, flags);
	if (result)
		goto done;

	/* #6: $PATH (#4 + #5 we skip) */
	{
		char *path = getenv("PATH");
		result = libpe_LoadLibraryInPathList(path, filename, flags);
		if (result)
			goto done;
	}

	*dl.dl_error_message = NULL;
err:
	return NULL;
done:
	*dl.dl_error_message = NULL;
	return result;
}


PRIVATE NONNULL((1)) int CC
DlModule_PeInitialize(DlModule *__restrict self) {
	/* Load dependencies of the module. */
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
			char const *filename;
			REF DlModule *dependency;
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
				if (ATOMIC_READ(*dl.dl_error_message) == NULL)
					dl.dl_seterrorf("Failed to load dependency %q of %q",
					                filename, self->dm_filename);
				goto err;
			}
			self->dm_depvec[self->dm_depcnt++] = dependency; /* Inherit reference */
		}
	}

	/* TODO: Apply relocations */
	asm("int3");

	return 0;
err_nomem:
	dl_seterror_nomem();
err:
	return -1;
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


INTERN struct dlmodule_format libpe_fmt = {
	.df_magic       = { 'M', 'Z' },
	.df_magsz       = 2,
	.df_open        = &libpe_v_open,
	.df_fini        = &libpe_v_fini,
	.df_ismapped    = &libpe_v_ismapped,
	.df_dlsym       = &libpe_v_dlsym,
	.df_dladdr      = &libpe_v_dladdr,
	.df_dlsectindex = &libpe_v_dlsectindex,
	.df_dlsectinfo  = &libpe_v_dlsectinfo,
	.df_dlsectname  = &libpe_v_dlsectname,
	.df_lsphdrs     = &libpe_v_lsphdrs,
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

/* Replacement for `linker_main' from `libdl.so' when a PE binary gets executed. */
DEFINE_PUBLIC_ALIAS(__linker_main, libpe_linker_main);
INTERN void *FCALL
libpe_linker_main(struct peexec_info *__restrict info,
                  uintptr_t loadaddr,
                  struct process_peb *__restrict UNUSED(peb)) {
	void *result;
	DlModule *mod;
	char *filename;
	struct peexec_data *pe = peexec_info__pi_pe(info);

#if 1
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

	/* Allocate the DL module descriptor for the PE binary. */
	mod = (DlModule *)malloc(offsetof(DlModule, dm_pe.dp_sect) +
	                         (pe->pd_nt.FileHeader.NumberOfSections *
	                          sizeof(IMAGE_SECTION_HEADER)));
	if unlikely(!mod)
		goto err_nomem;

	/* Duplicate the caller-given filename. */
	filename = peexec_data__pd_name(pe);
	result   = (void *)CEIL_ALIGN((uintptr_t)strend(filename), sizeof(void *));
	filename = strdup(filename);
	if unlikely(!filename)
		goto err_nomem; /* Leaks don't matter; we're only called once during init! */

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
	mod->dm_flags      = RTLD_LAZY | RTLD_NODELETE | RTLD_LOADING;
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
			syslog(LOG_DEBUG, "[pe] import: %q\n", (char *)(mod->dm_loadaddr + iter->Name));
			++mod->dm_depcnt;
		}
	}

	/* Hook the newly created module. */
	DLIST_INSERT_TAIL(dl.DlModule_AllList, mod, dm_modules);
	LIST_INSERT_HEAD(dl.DlModule_GlobalList, mod, dm_globals); /* NOTE: _MUST_ insert at head! */

	/* Initialize the PE module. */
	if (DlModule_PeInitialize(mod) != 0)
		return NULL;

	/* Mark this module as having been fully loaded. */
	ATOMIC_AND(mod->dm_flags, ~RTLD_LOADING);

	/* Return a pointer to the PE program entry point. */
	return result;
err_nomem:
	dl_seterror_nomem();
	return NULL;
}

DECL_END

#endif /* !GUARD_LIBDL_PE_PE_C */
