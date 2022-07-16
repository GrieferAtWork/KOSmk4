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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_EXECABI_H
#define GUARD_KERNEL_INCLUDE_KERNEL_EXECABI_H 1

#include <kernel/compiler.h>

#include <kernel/arch/execabi.h>
#include <kernel/types.h>

#include <hybrid/typecore.h>

#include <compat/config.h>
#include <kos/aref.h>

/* Executable format  ABI  definition  hook  (for  drivers
 * that wish to provide extended support for exec formats) */

/* Max  #  of ~magic~  bytes that  may be  provided by  exec ABIs.
 * Also specifies the # of bytes that get pre-read by the exec-ABI
 * invocation machinery before the ABI's exec callback is invoked. */
#ifndef EXECABI_MAXHEADER
#include <elf.h>
#include <hybrid/typecore.h>
#if defined(__ARCH_HAVE_COMPAT) && __ARCH_COMPAT_SIZEOF_POINTER != __SIZEOF_POINTER__
#if __SIZEOF_ELF64_EHDR > __SIZEOF_ELF32_EHDR
#define EXECABI_MAXHEADER __SIZEOF_ELF64_EHDR
#else /* __SIZEOF_ELF64_EHDR > __SIZEOF_ELF32_EHDR */
#define EXECABI_MAXHEADER __SIZEOF_ELF32_EHDR
#endif /* __SIZEOF_ELF64_EHDR <= __SIZEOF_ELF32_EHDR */
#elif __SIZEOF_POINTER__ == 8
#define EXECABI_MAXHEADER __SIZEOF_ELF64_EHDR
#else /* ... */
#define EXECABI_MAXHEADER __SIZEOF_ELF32_EHDR
#endif /* !... */
#endif /* !EXECABI_MAXHEADER */


 /* Define feature test macros for ABIs built into the kernel core */
#undef EXECABI_HAVE_BUILTIN_ELF
#define EXECABI_HAVE_BUILTIN_ELF 1
#undef EXECABI_HAVE_BUILTIN_SHEBANG
#define EXECABI_HAVE_BUILTIN_SHEBANG 1


#ifdef __CC__
DECL_BEGIN

/* Base address and size symbols for the system RTLD */
#ifndef __execabi_system_rtld_defined
#define __execabi_system_rtld_defined
DATDEF byte_t execabi_system_rtld[];
#endif /* !__execabi_system_rtld_defined */

#ifndef __execabi_system_rtld_size_defined
#define __execabi_system_rtld_size_defined
#undef execabi_system_rtld_size
#ifdef __INTELLISENSE__
DATDEF size_t const execabi_system_rtld_size;
#else /* __INTELLISENSE__ */
DATDEF byte_t execabi_system_rtld_size[];
#define execabi_system_rtld_size ((size_t)execabi_system_rtld_size)
#endif /* !__INTELLISENSE__ */
#endif /* !__execabi_system_rtld_size_defined */

/* A static VM file blob  for the built-in RTLD user-space  program.
 * This is a raw ELF binary blob that is hard-linked into the kernel
 * core, and is mapped via copy-on-write into any user-space process
 * that requests the use of a dynamic linker
 * NOTE: The associated source code can be found in `/kos/src/libdl/...',  and
 *       the (unstripped) library file can be found on-disk as `/lib/libdl.so' */
#ifndef __execabi_system_rtld_file_defined
#define __execabi_system_rtld_file_defined
DATDEF struct mramfile execabi_system_rtld_file;
#endif /* !__execabi_system_rtld_file_defined */

#ifdef __ARCH_HAVE_COMPAT
/* Base address and size symbols for the system RTLD */
#ifndef __compat_execabi_system_rtld_defined
#define __compat_execabi_system_rtld_defined
DATDEF byte_t compat_execabi_system_rtld[];
#endif /* !__compat_execabi_system_rtld_defined */

#ifndef __compat_execabi_system_rtld_size_defined
#define __compat_execabi_system_rtld_size_defined
#undef compat_execabi_system_rtld_size
#ifdef __INTELLISENSE__
DATDEF size_t const compat_execabi_system_rtld_size;
#else /* __INTELLISENSE__ */
DATDEF byte_t compat_execabi_system_rtld_size[];
#define compat_execabi_system_rtld_size  ((size_t)compat_execabi_system_rtld_size)
#endif /* !__INTELLISENSE__ */
#endif /* !__compat_execabi_system_rtld_size_defined */

/* A static VM file blob  for the building RTLD user-space  program.
 * This is a raw ELF binary blob that is hard-linked into the kernel
 * core, and is mapped via copy-on-write into any user-space process
 * that requests the use of a dynamic linker
 * NOTE: The associated source code can be found in `/kos/src/libdl/...' */
#ifndef __compat_execabi_system_rtld_file_defined
#define __compat_execabi_system_rtld_file_defined
DATDEF struct mramfile compat_execabi_system_rtld_file;
#endif /* !__compat_execabi_system_rtld_file_defined */
#endif /* __ARCH_HAVE_COMPAT */



#ifdef __ARCH_HAVE_COMPAT
typedef USER CHECKED void const *execabi_strings_t;
#else /* __ARCH_HAVE_COMPAT */
typedef USER UNCHECKED char const *USER CHECKED const *execabi_strings_t;
#endif /* !__ARCH_HAVE_COMPAT */

struct driver;
struct icpustate;
struct mman;
struct path;
struct fdirent;

struct execargs {
	struct mman        *ea_mman;        /* [1..1] The mman into which to map the executable.
	                                     * This must not be the kernel mman, which causes an assertion failure.
	                                     * NOTE: When `ea_change_mman_to_effective_mman' is `true', prior to a successful
	                                     *       return of `execabi::ea_exec', it will also do a `task_setmman(ea_mman)',
	                                     *       meaning that the caller will become apart of the given mman. */
	struct icpustate   *ea_state;       /* [1..1] The user-space CPU state to update upon success in a manner
	                                     *        that proper execution of the loaded binary is possible.
	                                     * Note however that  in the  case of a  dynamic binary,  a dynamic  linker
	                                     * may be injected to perform dynamic linking whilst already in user-space. */
	REF struct path    *ea_xpath;       /* [0..1] Filesystem path for the directory inside of which `ea_xfile' is located. */
	REF struct fdirent *ea_xdentry;     /* [0..1] Directory entry containing the filename of `ea_xfile'. */
	REF struct mfile   *ea_xfile;       /* [1..1] The filesystem node which should be loaded as an executable binary. */
	byte_t              ea_header[EXECABI_MAXHEADER];
	                                    /* The first `EXECABI_MAXHEADER' bytes of `ea_xfile'. Of this buffer, the
	                                     * leading `ea_magsiz' bytes are known to be equal to `ea_magic'. If  the
	                                     * executable file is  smaller than  `EXECABI_MAXHEADER', trailing  bytes
	                                     * are simply zero-initialized. */
	bool                ea_change_mman_to_effective_mman;
	                                    /* When set to `true', `ea_mman' should be set as the effective mman upon a
	                                     * successful return of `execabi::ea_exec'. */
#ifdef __ARCH_HAVE_COMPAT
	bool                ea_argv_is_compat; /* When `true', `ea_argv' and `ea_envp' are compatibility-mode vectors. */
#endif /* !__ARCH_HAVE_COMPAT */
	execabi_strings_t   ea_argv;        /* [0..1] NULL-terminated vector of arguments to-be passed to program being loaded. */
	execabi_strings_t   ea_envp;        /* [0..1] NULL-terminated vector of environment variables to-be passed to program being loaded. */
	size_t              ea_argc_inject; /* The number of arguments from `ea_argv_inject' to inject at the beginning of the user-space argc/argv vector. */
	char              **ea_argv_inject; /* [1..1][owned][ea_argc_inject][owned] Vector of arguments to inject at the beginning of the user-space argc/argv vector. */
};

/* Finalize the given set of exec() arguments. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL execargs_fini)(struct execargs *__restrict self);

/* Helper macro to allocate a PEB from `struct execargs *args' */
#ifdef __ARCH_HAVE_COMPAT
#define mbuilder_alloc_peb32_from_execargs(self, args)                                                           \
	((args)->ea_argv_is_compat                                                                                   \
	 ? mbuilder_alloc_peb32_p32(self,                                                                            \
	                            (args)->ea_argc_inject, (args)->ea_argv_inject,                                  \
	                            (USER UNCHECKED __HYBRID_PTR32(char const) USER CHECKED const *)(args)->ea_argv, \
	                            (USER UNCHECKED __HYBRID_PTR32(char const) USER CHECKED const *)(args)->ea_envp) \
	 : mbuilder_alloc_peb32_p64(self,                                                                            \
	                            (args)->ea_argc_inject, (args)->ea_argv_inject,                                  \
	                            (USER UNCHECKED __HYBRID_PTR64(char const) USER CHECKED const *)(args)->ea_argv, \
	                            (USER UNCHECKED __HYBRID_PTR64(char const) USER CHECKED const *)(args)->ea_envp))
#define mbuilder_alloc_peb64_from_execargs(self, args)                                                           \
	((args)->ea_argv_is_compat                                                                                   \
	 ? mbuilder_alloc_peb64_p32(self,                                                                            \
	                            (args)->ea_argc_inject, (args)->ea_argv_inject,                                  \
	                            (USER UNCHECKED __HYBRID_PTR32(char const) USER CHECKED const *)(args)->ea_argv, \
	                            (USER UNCHECKED __HYBRID_PTR32(char const) USER CHECKED const *)(args)->ea_envp) \
	 : mbuilder_alloc_peb64_p64(self,                                                                            \
	                            (args)->ea_argc_inject, (args)->ea_argv_inject,                                  \
	                            (USER UNCHECKED __HYBRID_PTR64(char const) USER CHECKED const *)(args)->ea_argv, \
	                            (USER UNCHECKED __HYBRID_PTR64(char const) USER CHECKED const *)(args)->ea_envp))
#if __SIZEOF_POINTER__ >= 8
#define mbuilder_alloc_peb_from_execargs       mbuilder_alloc_peb64_from_execargs
#define mbuilder_alloc_compatpeb_from_execargs mbuilder_alloc_peb32_from_execargs
#else /* __SIZEOF_POINTER__ >= 8 */
#define mbuilder_alloc_peb_from_execargs       mbuilder_alloc_peb32_from_execargs
#define mbuilder_alloc_compatpeb_from_execargs mbuilder_alloc_peb64_from_execargs
#endif /* __SIZEOF_POINTER__ < 8 */
#else /* __ARCH_HAVE_COMPAT */
#define mbuilder_alloc_peb_from_execargs(self, args)                   \
	mbuilder_alloc_peb(self,                                           \
	                   (args)->ea_argc_inject, (args)->ea_argv_inject, \
	                   (args)->ea_argv, (args)->ea_envp)
#endif /* !__ARCH_HAVE_COMPAT */


struct execabi {
	/* NOTE: All fields of this structure are [const] */
	WEAK REF struct driver *ea_driver; /* [1..1] Weak   reference   to   the   implementing   driver.
	                                    * Before  any of  the callbacks  below are  invoked, a strong
	                                    * reference is acquired to this driver (using `tryincref()'),
	                                    * and in case this fails, an  attempt is made to discard  the
	                                    * associated ABI (and  the kernel will  behave as though  the
	                                    * ABI hadn't actually been defined) */
	u8                      ea_magsiz; /* # of provided magic bytes (s.a. `ea_magic')
	                                    * When  non-zero,  this ABI  will only  be  used for  files that
	                                    * start with a byte sequence identical to `ea_magic[:ea_magsiz]'
	                                    * When set to  0, all files  are considered suitable  candidates
	                                    * for this ABI. */
	byte_t                  ea_magic[EXECABI_MAXHEADER]; /* ABI ~magic~ */

	/* [1..1] ABI execution callback.
	 * @param: args: Exec arguments
	 * @return: * :  One of `EXECABI_EXEC_*'
	 * @throw: E_NOT_EXECUTABLE_NOT_A_BINARY: Same as returning `NULL'. */
	BLOCKING WUNUSED_T NONNULL_T((1)) unsigned int
	(FCALL *ea_exec)(/*in|out*/ struct execargs *__restrict args)
			THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR, ...);

	/* TODO: Add callbacks to implement to implement
	 *       format-specific support for `struct usermod' here. */
};

/* Return codes for `ea_exec' */
#define EXECABI_EXEC_SUCCESS 0 /* Success. */
#define EXECABI_EXEC_NOTBIN  1 /* File doesn't belong to this ABI. (Even though the magic header was correct) */
#define EXECABI_EXEC_RESTART 2 /* Restart execution with an updated `ea_xfile' (used to implement #!-scripts) */


struct execabis_struct {
	WEAK refcnt_t                           eas_refcnt; /* Reference counter. */
	size_t                                  eas_count;  /* [const] # of ABIs defined. */
	COMPILER_FLEXIBLE_ARRAY(struct execabi, eas_abis);  /* [eas_count] Defined ABIs. */
};

/* Destroy a given exec-ABIs listing. */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL execabis_destroy)(struct execabis_struct *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct execabis_struct, eas_refcnt, execabis_destroy)

#ifndef __execabis_arref_defined
#define __execabis_arref_defined
ARREF(execabis_arref, execabis_struct);
#endif /* !__execabis_arref_defined */

/* [1..1] Currently registered exec-ABIs */
DATDEF struct execabis_arref execabis;

/* Register  a given exec-ABI. Note that the only way to unregister
 * an ABI is to unload the associated driver (in which case the ABI
 * is automatically unregistered)
 * @return: true:  Successfully registered the given `abi'.
 * @return: false: The given `abi' had already been registered. */
FUNDEF NONNULL((1)) bool FCALL
execabis_register(struct execabi const *__restrict abi)
		THROWS(E_BADALLOC, E_WOULDBLOCK);

#ifdef CONFIG_BUILDING_KERNEL_CORE
INTDEF NONNULL((1)) bool FCALL
driver_clear_execabis(struct driver *__restrict self)
		THROWS(E_BADALLOC, E_WOULDBLOCK);
#endif /* CONFIG_BUILDING_KERNEL_CORE */


#endif /* __CC__ */



DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_EXECABI_H */
