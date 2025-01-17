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
#ifndef GUARD_MODELF_ELF_C
#define GUARD_MODELF_ELF_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/debugtrap.h>
#include <kernel/driver-param.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/execabi.h>
#include <kernel/mman/mbuilder.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/phys.h>

#include <hybrid/align.h>
#include <hybrid/pointer.h>

#include <compat/config.h>
#include <kos/except/reason/fs.h>
#include <kos/except/reason/noexec.h>
#include <kos/exec/elf.h>
#include <kos/exec/peb.h>

#include <assert.h>
#include <elf.h>
#include <malloca.h>
#include <signal.h> /* SIGTRAP */
#include <stddef.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/exec/elf.h>
#endif /* __ARCH_HAVE_COMPAT */

/**/
#include "elf.h"

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Check if a given `Elfxx_Ehdr::e_type' can be exec'd */
#define ELF_ISEXECTYPE(e_type) \
	(likely((e_type) == ET_EXEC) || unlikely((e_type) == ET_DYN))

LOCAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) uintptr_t
NOTHROW(KCALL elf_validate_ehdr)(ElfW(Ehdr) const *__restrict ehdr) {
	uintptr_t result;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADCLASS;
	if unlikely(ehdr->e_ident[EI_CLASS] != ELF_ARCH_CLASS)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADORDER;
	if unlikely(ehdr->e_ident[EI_DATA] != ELF_ARCH_DATA)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION;
	if unlikely(ehdr->e_ident[EI_VERSION] != EV_CURRENT)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION2;
	if unlikely(ehdr->e_version != EV_CURRENT)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADTYPE;
	if unlikely(!ELF_ISEXECTYPE(ehdr->e_type))
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADMACH;
	if unlikely(ehdr->e_machine != ELF_ARCH_MACHINE)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADHEADER;
	if unlikely(ehdr->e_ehsize < offsetafter(ElfW(Ehdr), e_phnum))
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NOSEGMENTS;
	if unlikely(!ehdr->e_phnum)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADSEGMENTS;
	if unlikely(ehdr->e_phentsize != sizeof(ElfW(Phdr)))
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_TOOMANYSEGMENTS;
	if unlikely(ehdr->e_phnum > ELF_ARCH_MAXPHCOUNT)
		goto done; /* Too many program headers. */
	result = 0;
done:
	return result;
}

#ifdef __ARCH_HAVE_COMPAT
LOCAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) uintptr_t
NOTHROW(KCALL compat_elf_validate_ehdr)(COMPAT_ElfW(Ehdr) const *__restrict ehdr) {
	uintptr_t result;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADCLASS;
	if unlikely(ehdr->e_ident[EI_CLASS] != COMPAT_ELF_ARCH_CLASS)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADORDER;
	if unlikely(ehdr->e_ident[EI_DATA] != COMPAT_ELF_ARCH_DATA)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION;
	if unlikely(ehdr->e_ident[EI_VERSION] != EV_CURRENT)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADVERSION2;
	if unlikely(ehdr->e_version != EV_CURRENT)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADTYPE;
	if unlikely(!ELF_ISEXECTYPE(ehdr->e_type))
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADMACH;
	if unlikely(ehdr->e_machine != COMPAT_ELF_ARCH_MACHINE)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADHEADER;
	if unlikely(ehdr->e_ehsize < offsetafter(COMPAT_ElfW(Ehdr), e_phnum))
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_NOSEGMENTS;
	if unlikely(!ehdr->e_phnum)
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_BADSEGMENTS;
	if unlikely(ehdr->e_phentsize != sizeof(COMPAT_ElfW(Phdr)))
		goto done;
	result = E_NOT_EXECUTABLE_FAULTY_REASON_ELF_TOOMANYSEGMENTS;
	if unlikely(ehdr->e_phnum > COMPAT_ELF_ARCH_MAXPHCOUNT)
		goto done; /* Too many program headers. */
	result = 0;
done:
	return result;
}
#endif /* __ARCH_HAVE_COMPAT */


#ifndef __INTELLISENSE__
DECL_END
#define LOCAL_PTR(x)      x *
#define LOCAL_FUNC(x)     x
#define LOCAL_ELFW        ELFW
#define LOCAL_ElfW        ElfW
#define LOCAL_POINTERSIZE __SIZEOF_POINTER__
#ifdef __ARCH_HAVE_COMPAT
#define LOCAL_EXEC_ARGV_SIZE 1
#endif /* __ARCH_HAVE_COMPAT */
#include "elf-exec.c.inl"

#ifdef __ARCH_HAVE_COMPAT
#define LOCAL_PTR            __ARCH_COMPAT_PTR
#define LOCAL_FUNC(x)        compat_##x
#define LOCAL_ELFW           COMPAT_ELFW
#define LOCAL_ElfW           COMPAT_ElfW
#define LOCAL_POINTERSIZE    __ARCH_COMPAT_SIZEOF_POINTER
#define LOCAL_EXEC_ARGV_SIZE 1
#include "elf-exec.c.inl"
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN
#else /* !__INTELLISENSE__ */
LOCAL WUNUSED NONNULL((1)) unsigned int FCALL
elf_exec_impl(/*in|out*/ struct execargs *__restrict args)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR);
#ifdef __ARCH_HAVE_COMPAT
LOCAL WUNUSED NONNULL((1)) unsigned int FCALL
compat_elf_exec_impl(/*in|out*/ struct execargs *__restrict args)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR);
#endif /* __ARCH_HAVE_COMPAT */
#endif /* __INTELLISENSE__ */

/* Exec-abi callback for ELF files */
INTERN WUNUSED NONNULL((1)) unsigned int FCALL
elfabi_exec(/*in|out*/ struct execargs *__restrict args) {
	static_assert(EXECABI_MAXHEADER >= sizeof(ElfW(Ehdr)));
#ifdef __ARCH_HAVE_COMPAT
	static_assert(EXECABI_MAXHEADER >= sizeof(COMPAT_ElfW(Ehdr)));
#endif /* __ARCH_HAVE_COMPAT */
	uintptr_t reason;
	reason = elf_validate_ehdr((ElfW(Ehdr) const *)args->ea_header);
	if (reason == 0)
		return elf_exec_impl(args);
#ifdef __ARCH_HAVE_COMPAT
	reason = compat_elf_validate_ehdr((COMPAT_ElfW(Ehdr) const *)args->ea_header);
	if (reason == 0)
		return compat_elf_exec_impl(args);
#endif /* __ARCH_HAVE_COMPAT */
	THROW(E_NOT_EXECUTABLE_FAULTY,
	      E_NOT_EXECUTABLE_FAULTY_FORMAT_ELF,
	      reason);
}

#ifndef BUILDING_KERNEL_CORE
PRIVATE struct execabi elfabi = EXECABI_INIT_ELF;
PRIVATE DRIVER_INIT void KCALL init(void) {
	execabis_register(&elfabi);
}
#endif /* BUILDING_KERNEL_CORE */

DECL_END

#endif /* !GUARD_MODELF_ELF_C */
