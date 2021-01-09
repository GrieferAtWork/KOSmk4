/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBDL_MODULE_OPEN_C
#define GUARD_LIBDL_MODULE_OPEN_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

/* Keep this one the first */
#include "dl.h"
/**/

#include <hybrid/minmax.h>

#include <kos/exec/elf.h>
#include <kos/hop/handle.h>
#include <kos/io.h>
#include <kos/syscalls.h>

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <malloc.h>
#include <malloca.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

DECL_BEGIN


/* [1..1] Global chain of loaded modules.
 * WARNING: Contained modules may have a reference counter of ZERO(0)! */
INTERN struct dlmodule_list DlModule_GlobalList = LIST_HEAD_INITIALIZER(DlModule_GlobalList);
INTERN struct atomic_rwlock DlModule_GlobalLock = ATOMIC_RWLOCK_INIT;

/* [1..1] List of all loaded modules. */
INTERN struct dlmodule_dlist DlModule_AllList = DLIST_HEAD_INITIALIZER(DlModule_AllList);
INTERN struct atomic_rwlock DlModule_AllLock  = ATOMIC_RWLOCK_INIT;


INTERN WUNUSED fd_t CC reopen_bigfd(fd_t fd) {
	enum {
		MAX_RESERVED_FD_2 = STDIN_FILENO > STDOUT_FILENO
		                    ? STDIN_FILENO
		                    : STDOUT_FILENO,
		MAX_RESERVED_FD = MAX_RESERVED_FD_2 > STDERR_FILENO
		                  ? MAX_RESERVED_FD_2
		                  : STDERR_FILENO
	};
	if unlikely((unsigned int)fd <= (unsigned int)MAX_RESERVED_FD) {
		struct hop_openfd ofd;
		syscall_slong_t error;
		ofd.of_mode  = HOP_OPENFD_MODE_HINT;
		ofd.of_flags = IO_CLOEXEC;
		ofd.of_hint  = MAX_RESERVED_FD + 1;
		error = sys_hop(fd, HOP_HANDLE_REOPEN, &ofd);
		if (E_ISOK(error)) {
			sys_close(fd);
			return (fd_t)ofd.of_hint;
		}
	}
	return fd;
}


PRIVATE ATTR_MALLOC WUNUSED char *CC
realpath_malloc(fd_t fd) {
	char *resolved, *buffer;
	ssize_t result;
	size_t bufsize;
	/* Automatically allocate + determine buffer size. */
	bufsize = PATH_MAX;
	buffer  = (char *)malloc(bufsize);
	if unlikely(!buffer)
		bufsize = 0;
	for (;;) {
		result = sys_frealpath4(fd,
		                        buffer,
		                        bufsize,
		                        AT_READLINK_REQSIZE);
		if unlikely(E_ISERR(result))
			goto err_buffer;
		if likely((size_t)result <= bufsize)
			break;
		/* Allocate the required amount of memory. */
		resolved = (char *)realloc(buffer, (size_t)result);
		if unlikely(!resolved)
			goto err_buffer;
		bufsize = (size_t)result;
		buffer  = resolved;
	}
	if ((size_t)result != bufsize) {
		resolved = (char *)realloc(buffer, (size_t)result);
		if likely(resolved)
			buffer = resolved;
	}
	return buffer;
err_buffer:
	free(buffer);
/*err:*/
	return NULL;
}

INTERN NONNULL((2)) ssize_t CC
preadall(fd_t fd, void *buf, size_t bufsize, ElfW(Off) offset) {
	ssize_t result, temp;
	result = sys_pread64(fd, buf, bufsize, offset);
	if unlikely(E_ISERR(result))
		goto err;
	if ((size_t)result < bufsize) {
		/* Keep on reading */
		for (;;) {
			temp = sys_pread64(fd,
			                   (byte_t *)buf + (size_t)result,
			                   bufsize - (size_t)result,
			                   offset + (size_t)result);
			if unlikely(E_ISERR(result))
				goto err;
			if unlikely(!temp)
				goto err;
			result += temp;
			if ((size_t)result >= bufsize)
				break;
		}
	}
	return result;
err:
	return 0;
}

LOCAL NONNULL((1)) void CC
update_module_flags(DlModule *__restrict self, int mode) {
	uintptr_t old_flags;
again_old_flags:
	old_flags = ATOMIC_READ(self->dm_flags);
	if ((mode & RTLD_GLOBAL) && !(old_flags & RTLD_GLOBAL)) {
		/* Make the module global. */
		atomic_rwlock_write(&DlModule_GlobalLock);
		if (!ATOMIC_CMPXCH_WEAK(self->dm_flags, old_flags,
		                        old_flags | RTLD_GLOBAL)) {
			atomic_rwlock_endwrite(&DlModule_GlobalLock);
			goto again_old_flags;
		}
		assert(!LIST_ISBOUND(self, dm_globals));
		DlModule_AddToGlobals(self);
		assert(LIST_ISBOUND(self, dm_globals));
		atomic_rwlock_endwrite(&DlModule_GlobalLock);
	}
}






DEFINE_INTERN_ALIAS(libdl_dlfopen, DlModule_OpenFd);
DEFINE_PUBLIC_ALIAS(dlfopen, libdl_dlfopen);
INTERN WUNUSED REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *DLFCN_CC
DlModule_OpenFd(/*inherit(on_success)*/ fd_t fd, unsigned int mode) {
	REF DlModule *result;
	char *rp = realpath_malloc(fd);
	if unlikely(!rp)
		goto err;
	result = DlModule_OpenFilenameAndFd(rp,
	                                    fd,
	                                    mode);
	if unlikely(!result)
		goto err_rp;
	return result;
err_rp:
	free(rp);
err:
	return NULL;
}

INTERN WUNUSED NONNULL((1)) REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *CC
DlModule_OpenFilename(char const *__restrict filename,
                      unsigned int mode) {
	fd_t fd;
	REF DlModule *result;
	result = DlModule_FindFromFilename(filename);
	if (result)
		goto done_existing;
	fd = sys_open(filename, O_RDONLY | O_CLOEXEC, 0);
	if unlikely(E_ISERR(fd))
		goto err; /* No error on file-access-failure! */
	/* Make sure to only use big file descriptor indices, so-as
	 * to prevent use of reserved file numbers, as used by the
	 * standard I/O handles (aka. `STD(IN|OUT|ERR)_FILENO') */
	fd     = reopen_bigfd(fd);
	result = DlModule_OpenFd(fd, mode);
	if unlikely(!result)
		sys_close(fd);
done:
	return result;
done_existing:
	update_module_flags(result, mode);
	goto done;
err:
	return NULL;
}

INTERN WUNUSED ATTR_NOINLINE NONNULL((1, 3))
REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *CC
DlModule_OpenFilenameInPath(char const *__restrict path,
                            size_t pathlen,
                            char const *__restrict filename,
                            size_t filenamelen,
                            unsigned int mode) {
	char *buf;
	REF DlModule *result;
	while (pathlen && path[pathlen - 1] == '/')
		--pathlen;
	/* TODO: The specs state that we must expand special tokens within library paths:
	 *        - $ORIGIN / ${ORIGIN}:     DIRECTORY_WITHOUT_TRAILING_SLASH_OF(BASE_APPLICATION)
	 *        - $LIB / ${LIB}:           Expand to `RTLD_LIB'
	 *        - $PLATFORM / ${PLATFORM}: Expand to `RTLD_PLATFORM'
	 */
	buf = (char *)malloca((pathlen + 1 + filenamelen + 1) *
	                      sizeof(char));
	if unlikely(!buf) {
		dl_seterror_nomem();
		return NULL;
	}
	memcpy(buf, path, pathlen, sizeof(char));
	buf[pathlen] = '/';
	memcpy(buf + pathlen + 1, filename, filenamelen, sizeof(char));
	buf[pathlen + 1 + filenamelen] = '\0';
	result = DlModule_OpenFilename(buf, mode);
	freea(buf);
	return result;
}

INTERN WUNUSED ATTR_NOINLINE NONNULL((1, 3))
REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *CC
DlModule_FindFilenameInPathFromAll(char const *__restrict path,
                                   size_t pathlen,
                                   char const *__restrict filename,
                                   size_t filenamelen) {
	char *buf;
	REF DlModule *result;
	while (pathlen && path[pathlen - 1] == '/')
		--pathlen;
	buf = (char *)malloca((pathlen + 1 + filenamelen + 1) *
	                      sizeof(char));
	if unlikely(!buf) {
		dl_seterror_nomem();
		return NULL;
	}
	memcpy(buf, path, pathlen, sizeof(char));
	buf[pathlen] = '/';
	memcpy(buf + pathlen + 1, filename, filenamelen, sizeof(char));
	buf[pathlen + 1 + filenamelen] = '\0';
	result = DlModule_FindFromFilename(buf);
	freea(buf);
	return result;
}

INTERN WUNUSED NONNULL((1)) REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *CC
DlModule_FindFilenameInPathListFromAll(char const *__restrict filename) {
	REF DlModule *result;
	char const *sep;
	char const *path   = dl_library_path;
	size_t filenamelen = strlen(filename);
	for (;;) {
		sep    = strchrnul(path, ':');
		result = DlModule_FindFilenameInPathFromAll(path,
		                                            (size_t)(sep - path),
		                                            filename,
		                                            filenamelen);
		if (result || dl_error_message != NULL)
			break;
		if (!*sep)
			break;
		path = sep + 1;
	}
	return result;
}

#undef CONFIG_DLOPEN_TRYHARD_NO_VERSION_SUFFIX
#if 1
#define CONFIG_DLOPEN_TRYHARD_NO_VERSION_SUFFIX 1
#endif

INTERN WUNUSED NONNULL((1, 2)) REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *CC
DlModule_OpenFilenameInPathList(char const *__restrict path,
                                char const *__restrict filename,
                                unsigned int mode) {
	REF DlModule *result;
	char const *sep;
	size_t filenamelen;
#ifdef CONFIG_DLOPEN_TRYHARD_NO_VERSION_SUFFIX
	char const *orig_path;
#endif /* CONFIG_DLOPEN_TRYHARD_NO_VERSION_SUFFIX */
	filenamelen = strlen(filename);
#ifdef CONFIG_DLOPEN_TRYHARD_NO_VERSION_SUFFIX
	orig_path = path;
again:
#endif /* CONFIG_DLOPEN_TRYHARD_NO_VERSION_SUFFIX */
	for (;;) {
		char ch;
		sep = path;
		for (;; ++sep) {
			ch = *sep;
			/* The specs state that both ':' and ';' are valid separators */
			if (!ch || ch == ':' || ch == ';')
				break;
		}
		result = DlModule_OpenFilenameInPath(path,
		                                     (size_t)(sep - path),
		                                     filename,
		                                     filenamelen,
		                                     mode);
		if (result || dl_error_message != NULL)
			goto done;
		if (!ch)
			break;
		path = sep + 1;
	}
#ifdef CONFIG_DLOPEN_TRYHARD_NO_VERSION_SUFFIX
	/* Check if the filename ends with `.<number>'.
	 * If so, strip that number and try again. */
	if (filenamelen && isdigit(filename[filenamelen - 1])) {
		do {
			--filenamelen;
		} while (filenamelen && isdigit(filename[filenamelen - 1]));
		if (filenamelen && filename[filenamelen - 1] == '.') {
			--filenamelen;
			path = orig_path;
			goto again;
		}
	}
#endif /* CONFIG_DLOPEN_TRYHARD_NO_VERSION_SUFFIX */
done:
	return result;
}



PRIVATE NONNULL((1)) int CC
DlModule_ElfLoadLoadedProgramHeaders(DlModule *__restrict self) {
	uint16_t pidx;
	for (pidx = 0; pidx < self->dm_elf.de_phnum; ++pidx) {
		uintptr_t base = self->dm_loadaddr + self->dm_elf.de_phdr[pidx].p_vaddr;
		switch (self->dm_elf.de_phdr[pidx].p_type) {

		case PT_DYNAMIC: {
			size_t i;
			self->dm_dynhdr        = (ElfW(Dyn) *)base;
			self->dm_elf.de_dyncnt = self->dm_elf.de_phdr[pidx].p_memsz / sizeof(ElfW(Dyn));
			self->dm_depcnt = 0;
			/* Load dynamic tag meta-data. */
			for (i = 0; i < self->dm_elf.de_dyncnt; ++i) {
				ElfW(Dyn) tag;
				tag = ((ElfW(Dyn) *)base)[i];

				switch (tag.d_tag) {

				case DT_NEEDED:
					++self->dm_depcnt;
					break;

				case DT_RPATH:
					if (!self->dm_elf.de_runpath)
						self->dm_elf.de_runpath = (char const*)tag.d_un.d_ptr;
					break;

				case DT_RUNPATH:
					self->dm_elf.de_runpath = (char const*)tag.d_un.d_ptr;
					break;

				case DT_HASH:
					self->dm_elf.de_hashtab = (ElfW(HashTable) const*)(self->dm_loadaddr + tag.d_un.d_ptr);
					break;

				case DT_GNU_HASH:
					self->dm_elf.de_gnuhashtab = (ElfW(GnuHashTable) const*)(self->dm_loadaddr + tag.d_un.d_ptr);
					break;

				case DT_STRTAB:
					self->dm_elf.de_dynstr = (char const*)(self->dm_loadaddr + tag.d_un.d_ptr);
					break;

				case DT_SYMTAB:
					self->dm_elf.de_dynsym_tab = (ElfW(Sym) const*)(self->dm_loadaddr + tag.d_un.d_ptr);
					break;

				case DT_SYMENT:
					if (tag.d_un.d_val != sizeof(ElfW(Sym))) {
						dl_seterrorf("%q: Invalid `DT_SYMENT' %Iu != %Iu",
						                (size_t)tag.d_un.d_val,
						                (size_t)sizeof(ElfW(Sym)));
						goto err;
					}
					break;

#if ELF_ARCH_USESRELA
				case DT_RELAENT:
					if (tag.d_un.d_val != sizeof(ElfW(Rela))) {
						dl_seterrorf("%q: Invalid `DT_RELAENT' %Iu != %Iu",
						                (size_t)tag.d_un.d_val,
						                (size_t)sizeof(ElfW(Rela)));
						goto err;
					}
					break;
#endif /* ELF_ARCH_USESRELA */

				case DT_RELENT:
					if (tag.d_un.d_val != sizeof(ElfW(Rel))) {
						dl_seterrorf("%q: Invalid `DT_RELENT' %Iu != %Iu",
						                (size_t)tag.d_un.d_val,
						                (size_t)sizeof(ElfW(Rel)));
						goto err;
					}
					break;

				default: break;
				}
			}
			if (self->dm_elf.de_runpath)
				self->dm_elf.de_runpath = self->dm_elf.de_dynstr + (uintptr_t)self->dm_elf.de_runpath;
		}	break;

		case PT_TLS:
			self->dm_tlsoff   = self->dm_elf.de_phdr[pidx].p_offset;
			self->dm_tlsfsize = self->dm_elf.de_phdr[pidx].p_filesz;
			self->dm_tlsmsize = self->dm_elf.de_phdr[pidx].p_memsz;
			self->dm_tlsalign = self->dm_elf.de_phdr[pidx].p_align;
			if unlikely(self->dm_tlsfsize > self->dm_tlsmsize)
				self->dm_tlsfsize = self->dm_tlsmsize;
			/* Validate/Fix the TLS alignment requirements. */
			if (!self->dm_tlsalign || self->dm_tlsalign < sizeof(void *))
				self->dm_tlsalign = sizeof(void *);
			else if unlikely(self->dm_tlsalign & (self->dm_tlsalign - 1)) {
				size_t real_align = sizeof(void *);
				while (real_align < self->dm_tlsalign &&
				       !(real_align & ((size_t)1 << ((sizeof(void *) * 8) - 1))))
					real_align <<= 1;
				self->dm_tlsalign = real_align;
			}
			break;

		default: break;
		}
	}

	/* Register the module as globally loaded (if RTLD_GLOBAL is set). */
	if (self->dm_flags & RTLD_GLOBAL) {
		atomic_rwlock_write(&DlModule_GlobalLock);
		if (!LIST_ISBOUND(self, dm_globals))
			DlModule_AddToGlobals(self);
		atomic_rwlock_endwrite(&DlModule_GlobalLock);
	}

	if (!DLIST_PREV(self, dm_modules)) {
		atomic_rwlock_write(&DlModule_AllLock);
		COMPILER_READ_BARRIER();
		if likely(!DLIST_PREV(self, dm_modules))
			DlModule_AddToAll(self);
		COMPILER_READ_BARRIER();
		atomic_rwlock_endwrite(&DlModule_AllLock);
	}

	/* Apply relocations and invoke module initializers. */
	if unlikely(DlModule_ElfInitialize(self,
	                                   (self->dm_flags & RTLD_BINDING_MASK) == RTLD_NOW
	                                   ? DL_MODULE_ELF_INITIALIZE_FBINDNOW
	                                   : DL_MODULE_ELF_INITIALIZE_FNORMAL))
		goto err;
	/* And with that, we've successfully initialize the module! */
	ATOMIC_AND(self->dm_flags, ~RTLD_LOADING);
	return 0;
err:
	return -1;
}


INTERN WUNUSED NONNULL((1, 2)) REF DlModule *CC
DlModule_ElfOpenLoadedProgramHeaders(/*inherit(on_success,HEAP)*/ char *__restrict filename,
                                     struct elfexec_info *__restrict info, uintptr_t loadaddr) {
	REF DlModule *result;
	uint16_t pidx;
	result = (REF DlModule *)calloc(offsetof(DlModule, dm_elf.de_phdr) +
	                                (info->ei_pnum * sizeof(ElfW(Phdr))));
	if unlikely(!result)
		goto err_nomem;
	memcpy(result->dm_elf.de_phdr, info->ei_phdr, info->ei_pnum, sizeof(ElfW(Phdr)));
	/*result->dm_ops     = NULL;*/ /* Implicitly done by `calloc()' */
	result->dm_loadstart = (uintptr_t)-1;
	/*result->dm_loadend = 0;*/
	for (pidx = 0; pidx < info->ei_pnum; ++pidx) {
		uintptr_t base = result->dm_loadaddr + info->ei_phdr[pidx].p_vaddr;
		if (info->ei_phdr[pidx].p_type == PT_LOAD) {
			uintptr_t end = base + info->ei_phdr[pidx].p_memsz;
			if (result->dm_loadstart > base)
				result->dm_loadstart = base;
			if (result->dm_loadend < end)
				result->dm_loadend = end;
		}
	}
	result->dm_refcnt   = 1;
	result->dm_file     = (fd_t)-1;
	result->dm_flags    = (uint32_t)(RTLD_LAZY | RTLD_GLOBAL | RTLD_NODELETE | RTLD_NOINIT | RTLD_LOADING);
	result->dm_filename = filename; /* Inherit data */
	result->dm_loadaddr = loadaddr;
	result->dm_loadstart += loadaddr;
	result->dm_loadend   += loadaddr;
	result->dm_elf.de_phnum    = info->ei_pnum;
	result->dm_elf.de_abi      = info->ei_abi;
	result->dm_elf.de_abiver   = info->ei_abiver;
	result->dm_shnum           = (size_t)-1;     /* Unknown */
	result->dm_elf.de_shstrndx = (ElfW(Half))-1; /* Unknown */
	if unlikely(DlModule_ElfLoadLoadedProgramHeaders(result))
		goto err_r;
	return result;
err_nomem:
	dl_seterror_nomem();
	return NULL;
err_r:
	DlModule_Decref(result);
	return NULL;
}


INTERN WUNUSED NONNULL((1, 2)) int CC
DlModule_ElfVerifyEhdr(ElfW(Ehdr) const *__restrict ehdr,
                       char const *__restrict filename,
                       bool requires_ET_DYN) {
	char const *reason;
	reason = "ehdr.e_ident[EI_MAG*] != " PP_STR(ELFMAG);
	if unlikely(ehdr->e_ident[EI_MAG0] != ELFMAG0 ||
	            ehdr->e_ident[EI_MAG1] != ELFMAG1 ||
	            ehdr->e_ident[EI_MAG2] != ELFMAG2 ||
	            ehdr->e_ident[EI_MAG3] != ELFMAG3)
		goto err;
	reason = "e_ident[EI_CLASS] != ELF" ELF_CLASSNAME(ELF_ARCH_CLASS);
	if unlikely(ehdr->e_ident[EI_CLASS] != ELF_ARCH_CLASS)
		goto err;
	reason = "e_ident[EI_DATA] != ELF" ELF_DATANAME(ELF_ARCH_DATA);
	if unlikely(ehdr->e_ident[EI_DATA] != ELF_ARCH_DATA)
		goto err;
	reason = "e_ident[EI_VERSION] != EV_CURRENT";
	if unlikely(ehdr->e_ident[EI_VERSION] != EV_CURRENT)
		goto err;
	reason = "e_version != EV_CURRENT";
	if unlikely(ehdr->e_version != EV_CURRENT)
		goto err;
	if (requires_ET_DYN) {
		reason = "e_type != ET_DYN";
		if unlikely(ehdr->e_type != ET_DYN)
			goto err;
	}
	reason = "e_machine != EM_" ELF_EMNAME(ELF_ARCH_MACHINE);
	if unlikely(ehdr->e_machine != ELF_ARCH_MACHINE)
		goto err;
	reason = "ehdr.e_ehsize < offsetafter(ElfW(Ehdr), e_phnum)";
	if unlikely(ehdr->e_ehsize < offsetafter(ElfW(Ehdr), e_phnum))
		goto err;
	reason = "ehdr.e_phnum == 0";
	if unlikely(ehdr->e_phnum == 0)
		goto err;
	reason = "ehdr.e_phentsize != sizeof(ElfW(Phdr))";
	if unlikely(ehdr->e_phentsize != sizeof(ElfW(Phdr)))
		goto err;
	return 0;
err:
	return dl_seterrorf("%q: Faulty ELF header: %q", filename, reason);
}


PRIVATE WUNUSED NONNULL((1, 2)) REF DlModule *CC
DlModule_ElfMapProgramHeaders(ElfW(Ehdr) const *__restrict ehdr,
                              /*inherit(on_success,HEAP)*/ char *__restrict filename,
                              /*inherit(on_success)*/ fd_t fd) {
	uint16_t pidx;
	REF DlModule *result;
	if unlikely(DlModule_ElfVerifyEhdr(ehdr, filename, true))
		goto err;
	result = (REF DlModule *)calloc(offsetof(DlModule, dm_elf.de_phdr) +
	                                (ehdr->e_phnum * sizeof(ElfW(Phdr))));
	if unlikely(!result)
		goto err_nomem;
	if (preadall(fd, result->dm_elf.de_phdr, ehdr->e_phnum * sizeof(ElfW(Phdr)), ehdr->e_phoff) <= 0)
		goto err_r_io;
	/*result->dm_ops           = NULL;*/   /* Implicitly done by `calloc()' */
	result->dm_filename        = filename; /* Inherit data */
	result->dm_file            = fd;       /* Inherit data */
	result->dm_elf.de_abi      = ehdr->e_ident[EI_OSABI];
	result->dm_elf.de_abiver   = ehdr->e_ident[EI_ABIVERSION];
	result->dm_elf.de_phnum    = ehdr->e_phnum;
	result->dm_shnum           = ehdr->e_shnum;
	result->dm_elf.de_shoff    = ehdr->e_shoff;
	result->dm_elf.de_shstrndx = ehdr->e_shstrndx;
	if unlikely(ehdr->e_shentsize != sizeof(ElfW(Shdr))) {
		result->dm_elf.de_shoff    = 0;
		result->dm_shnum           = (size_t)-1;
		result->dm_elf.de_shstrndx = (ElfW(Half))-1;
	}
	result->dm_refcnt    = 1;
	result->dm_loadstart = (uintptr_t)-1;
	/*result->dm_loadend = 0;*/
	for (pidx = 0; pidx < result->dm_elf.de_phnum; ++pidx) {
		uintptr_t base = result->dm_loadaddr + result->dm_elf.de_phdr[pidx].p_vaddr;
		if (result->dm_elf.de_phdr[pidx].p_type == PT_LOAD) {
			uintptr_t end = base + result->dm_elf.de_phdr[pidx].p_memsz;
			if (result->dm_loadstart > base)
				result->dm_loadstart = base;
			if (result->dm_loadend < end)
				result->dm_loadend = end;
		}
	}
	/* Use a dedicated system call for mapping the library into memory.
	 * This functionality could technically be implemented via `MAP_FIXED_NOREPLACE',
	 * however using this method, we leave it entirely up to the kernel to decide
	 * how it is going to map the library, and more importantly: where. */
	{
		void *libbase;
		libbase = sys_maplibrary(NULL,
		                         0,
		                         fd,
		                         result->dm_elf.de_phdr,
		                         result->dm_elf.de_phnum);
		if (E_ISERR(libbase)) {
			free(result);
			dl_seterrorf("%q: Failed to map library into memory: %u",
			             filename,
			             (unsigned int)-(errno_t)(intptr_t)(uintptr_t)libbase);
			goto err;
		}
		result->dm_loadaddr = (uintptr_t)libbase;
	}
	result->dm_loadstart += result->dm_loadaddr;
	result->dm_loadend += result->dm_loadaddr;
	return result;
err_r_io:
	free(result);
/*err_io:*/
	dl_seterror_header_read_error(filename);
	goto err;
err_nomem:
	dl_seterror_nomem();
err:
	return NULL;
}

INTERN ATTR_COLD int CC
dl_seterror_header_read_error(char const *__restrict filename) {
	return dl_seterrorf("%q: Failed to read headers", filename);
}

INTERN ATTR_COLD int CC
dl_seterror_notelf(DlModule *__restrict self) {
	return dl_seterrorf("%q: Not an ELF object", self->dm_filename);
}


INTERN WUNUSED NONNULL((1)) REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *CC
DlModule_OpenFilenameAndFd(/*inherit(on_success,HEAP)*/ char *__restrict filename,
                           /*inherit(on_success)*/ fd_t fd, unsigned int mode) {
	ElfW(Ehdr) ehdr;
	REF DlModule *result;
	result = DlModule_FindFromFilename(filename);
	if (result) {
		sys_close(fd);
		free(filename);
		update_module_flags(result, mode);
		goto done;
	}
	if unlikely(preadall(fd, &ehdr, sizeof(ehdr), 0) <= 0)
		goto err_io;
	/* Support for formats other than ELF. */
	if unlikely(ehdr.e_ident[EI_MAG0] != ELFMAG0 ||
	            ehdr.e_ident[EI_MAG1] != ELFMAG1 ||
	            ehdr.e_ident[EI_MAG2] != ELFMAG2 ||
	            ehdr.e_ident[EI_MAG3] != ELFMAG3) {
		struct dlmodule_format *ext;
		ext = ATOMIC_READ(dl_extensions);
		for (; ext; ext = ext->df_next) {
			if (memcmp(&ehdr, ext->df_magic, ext->df_magsz) != 0)
				continue; /* Non-matching magic. */
			/* Found the format! */
			result = (*ext->df_open)((byte_t const *)&ehdr, filename, fd);
			if unlikely(result == NULL)
				goto err;
			if unlikely(result == DLMODULE_FORMAT_OPEN_BAD_MAGIC)
				continue; /* Continue searching */
			/* Got it! */
			goto done;
		}
	}
	/* Map the executable into memory. */
	result = DlModule_ElfMapProgramHeaders(&ehdr, filename, fd);
	if unlikely(!result)
		goto done;
	result->dm_flags = (uint32_t)mode | RTLD_LOADING;
	/* Load the execute via its program headers. */
	if unlikely(DlModule_ElfLoadLoadedProgramHeaders(result))
		goto err_r;
done:
	return result;
err_io:
	dl_seterror_header_read_error(filename);
	goto err;
err_r:
	result->dm_file     = -1;
	result->dm_filename = NULL;
	DlModule_Destroy(result);
err:
	result = NULL;
	goto done;
}




/* Find the DL module mapping the specified file.
 * If no such module is loaded, `NULL' is returned instead. */
INTERN WUNUSED NONNULL((1))
REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *CC
DlModule_FindFromFilename(char const *__restrict filename) {
	REF DlModule *result;
	atomic_rwlock_read(&DlModule_AllLock);
	DlModule_AllList_FOREACH(result) {
		if (strcmp(result->dm_filename, filename) != 0)
			continue;
		if (!(result->dm_flags & RTLD_NODELETE))
			DlModule_Incref(result);
		break;
	}
	atomic_rwlock_endread(&DlModule_AllLock);
	return result;
}

INTERN ATTR_COLD int CC
dl_seterror_no_mod_at_addr(void const *static_pointer) {
	return dl_seterrorf("Address %p does not map to any module",
	                    static_pointer);
}


/* Find the DL module containing a given static pointer. */
INTERN WUNUSED DlModule *CC
DlModule_FindFromStaticPointer(void const *static_pointer) {
	REF DlModule *result;
	atomic_rwlock_read(&DlModule_AllLock);
	DlModule_AllList_FOREACH(result) {
		uint16_t i;
		if ((uintptr_t)static_pointer < result->dm_loadstart)
			continue;
		if ((uintptr_t)static_pointer >= result->dm_loadend)
			continue;
		/* Support for formats other than ELF. */
		if (result->dm_ops) {
			if (!(*result->dm_ops->df_ismapped)(result,
			                                    (uintptr_t)static_pointer -
			                                    result->dm_loadaddr))
				continue;
			goto got_result;
		}
		/* Make sure that `static_pointer' maps to some program segment. */
		for (i = 0; i < result->dm_elf.de_phnum; ++i) {
			uintptr_t segment_base;
			if (result->dm_elf.de_phdr[i].p_type != PT_LOAD)
				continue;
			segment_base = result->dm_loadaddr + result->dm_elf.de_phdr[i].p_vaddr;
			if ((uintptr_t)static_pointer < segment_base)
				continue;
			if ((uintptr_t)static_pointer >= segment_base + result->dm_elf.de_phdr[i].p_memsz)
				continue;
			/* Found the segment! */
			goto got_result;
		}
	}
	atomic_rwlock_endread(&DlModule_AllLock);
	dl_seterror_no_mod_at_addr(static_pointer);
	return NULL;
got_result:
	/*DlModule_Incref(result);*/ /* This function doesn't return a reference! */
	atomic_rwlock_endread(&DlModule_GlobalLock);
	return result;
}



DECL_END

#endif /* !GUARD_LIBDL_MODULE_OPEN_C */
