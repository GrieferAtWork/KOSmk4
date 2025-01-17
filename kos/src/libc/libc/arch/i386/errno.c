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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_ERRNO_C
#define GUARD_LIBC_LIBC_ARCH_I386_ERRNO_C 1

#include "../../../api.h"
/**/

#include <hybrid/host.h>

/* Only define for i386 (x86_64 would also be possible, but
 * would be more complicated and there shouldn't really  be
 * any 64-bit programs that don't use the proper `errno' as
 * accessed via `__errno_location(3)') */
#if !defined(__x86_64__) && defined(__i386__)
#include <hybrid/unaligned.h>

#include <kos/except.h>
#include <kos/exec/elf.h>
#include <kos/exec/idata.h>
#include <kos/sys/mman.h>
#include <kos/types.h>

#include <elf.h>

#include "../../dl.h"
#include "../../globals.h"

/*
 * For compatibility with old programs that did `extern int errno;',
 * we  define a fallback system (using IDATA symbols) that allows an
 * alternate (non-thread-safe) symbol location to be used as storage
 * for `errno'.
 */

#undef errno
#undef _errno
DECL_BEGIN

PRIVATE ATTR_SECTION(".bss.crt.glibc.application.init") errno_t nontls_errno_fallback = 0;
PRIVATE ATTR_SECTION(".bss.crt.glibc.application.init") errno_t *nontls_errno_addr    = NULL;

INTDEF byte_t __libc_errno_access_core_start[];
INTDEF byte_t __libc_errno_access_core_end[];
INTDEF byte_t b_libc_errno_p[] ASMNAME("libc_errno_p");
INTDEF byte_t b_libc_geterrno[] ASMNAME("libc_geterrno");
INTDEF byte_t b_libc_geterrno_safe[] ASMNAME("libc_geterrno_safe");
INTDEF byte_t b_libc_seterrno_compat[] ASMNAME("libc_seterrno_compat");
INTDEF byte_t b_libc_seterrno[] ASMNAME("libc_seterrno");
INTDEF byte_t b_libc_seterrno_neg[] ASMNAME("libc_seterrno_neg");

PRIVATE ATTR_SECTION(".text.crt.glibc.application.init") errno_t *
NOTHROW(LIBCCALL nontls_errno_redirect)(void) {
	/* Check if the main  application defines a symbol  "errno".
	 * If so, then we must use its address in all of libc's code
	 * paths for setting the errno.  Otherwise, we just use  the
	 * address of `nontls_errno_fallback' for this purpose. */
	void *mainapp = dlopen(NULL, 0);
	ElfW(Sym) const *g_errno_sym;
	errno_t *g_errno;
	byte_t *writer;
	size_t core_size;

	/* Can't use normal dlsym() here since that one might end up recursing! */
	g_errno_sym = (ElfW(Sym) const *)dlauxctrl(mainapp, DLAUXCTRL_ELF_GET_LSYMBOL, "errno");
	if (g_errno_sym == NULL || g_errno_sym->st_shndx == SHN_UNDEF)
		g_errno_sym = (ElfW(Sym) const *)dlauxctrl(mainapp, DLAUXCTRL_ELF_GET_LSYMBOL, "_errno");
	g_errno = (errno_t *)dlauxctrl(mainapp, DLAUXCTRL_ELF_SYMADDR, g_errno_sym);
	if (g_errno == NULL)
		g_errno = &nontls_errno_fallback;

	/* Re-write the implementation of some functions:
	 * >> libc_errno_p:
	 * >>     movl  $<g_errno>, %eax # { 0xb8, <u32:g_errno>... }
	 * >>     ret                    # { 0xc3 }
	 * >> libc_geterrno:
	 * >>     movl  <g_errno>, %eax  # { 0xa1, <u32:g_errno>... }
	 * >>     ret                    # { 0xc3 }
	 * >> libc_geterrno_safe:
	 * >>     movl  <g_errno>, %eax  # { 0xa1, <u32:g_errno>... }
	 * >>     ret                    # { 0xc3 }
	 * >> libc_seterrno_compat:
	 * >>     movl  4(%esp), %eax    # { 0x8b, 0x44, 0x24, 0x04 }
	 * >>     movl  %eax, <g_errno>  # { 0xa3, <u32:g_errno>... }
	 * >>     movl  $-1, %eax        # { 0xb8, 0xff, 0xff, 0xff, 0xff }
	 * >>     ret                    # { 0xc3 }
	 * >> libc_seterrno:
	 * >>     movl  %ecx, <g_errno>  # { 0x89, 0x0d, <u32:g_errno>... }
	 * >>     movl  $-1, %eax        # { 0xb8, 0xff, 0xff, 0xff, 0xff }
	 * >>     ret                    # { 0xc3 }
	 * >> libc_seterrno_neg:
	 * >>     negl  %ecx             # { 0xf7, 0xd9 }
	 * >>     movl  %ecx, <g_errno>  # { 0x89, 0x0d, <u32:g_errno>... }
	 * >>     movl  $-1, %eax        # { 0xb8, 0xff, 0xff, 0xff, 0xff }
	 * >>     ret                    # { 0xc3 }
	 */

	/* Acquire write access to the affected functions */
	core_size = (size_t)(__libc_errno_access_core_end - __libc_errno_access_core_start);
	NOEXCEPT_DO(MProtect(__libc_errno_access_core_start, core_size, PROT_READ | PROT_WRITE | PROT_EXEC));
#define PUTB(b) (*writer++ = (b))
#define PUTL(l) (UNALIGNED_SET32(writer, (uintptr_t)(l)), writer += 4)

	/* >> libc_errno_p:
	 * >>     movl  $<g_errno>, %eax # { 0xb8, <u32:g_errno>... }
	 * >>     ret                    # { 0xc3 } */
	writer = b_libc_errno_p;
	PUTB(0xb8), PUTL(g_errno);
	PUTB(0xc3);

	/* >> libc_geterrno:
	 * >>     movl  <g_errno>, %eax  # { 0xa1, <u32:g_errno>... }
	 * >>     ret                    # { 0xc3 } */
	writer = b_libc_geterrno;
	PUTB(0xa1), PUTL(g_errno);
	PUTB(0xc3);

	/* >> libc_geterrno_safe:
	 * >>     movl  <g_errno>, %eax  # { 0xa1, <u32:g_errno>... }
	 * >>     ret                    # { 0xc3 } */
	writer = b_libc_geterrno_safe;
	PUTB(0xa1), PUTL(g_errno);
	PUTB(0xc3);

	/* >> libc_seterrno_compat:
	 * >>     movl  4(%esp), %eax    # { 0x8b, 0x44, 0x24, 0x04 }
	 * >>     movl  %eax, <g_errno>  # { 0xa3, <u32:g_errno>... }
	 * >>     movl  $-1, %eax        # { 0xb8, 0xff, 0xff, 0xff, 0xff }
	 * >>     ret                    # { 0xc3 } */
	writer = b_libc_seterrno_compat;
	PUTB(0x8b), PUTB(0x44), PUTB(0x24), PUTB(0x04);
	PUTB(0xa3), PUTL(g_errno);
	PUTB(0xb8), PUTB(0xff), PUTB(0xff), PUTB(0xff), PUTB(0xff);
	PUTB(0xc3);

	/* >> libc_seterrno:
	 * >>     movl  %ecx, <g_errno>  # { 0x89, 0x0d, <u32:g_errno>... }
	 * >>     movl  $-1, %eax        # { 0xb8, 0xff, 0xff, 0xff, 0xff }
	 * >>     ret                    # { 0xc3 } */
	writer = b_libc_seterrno;
	PUTB(0x89), PUTB(0x0d), PUTL(g_errno);
	PUTB(0xb8), PUTB(0xff), PUTB(0xff), PUTB(0xff), PUTB(0xff);
	PUTB(0xc3);

	/* >> libc_seterrno_neg:
	 * >>     negl  %ecx             # { 0xf7, 0xd9 }
	 * >>     movl  %ecx, <g_errno>  # { 0x89, 0x0d, <u32:g_errno>... }
	 * >>     movl  $-1, %eax        # { 0xb8, 0xff, 0xff, 0xff, 0xff }
	 * >>     ret                    # { 0xc3 } */
	writer = b_libc_seterrno_neg;
	PUTB(0xf7), PUTB(0xd9);
	PUTB(0x89), PUTB(0x0d), PUTL(g_errno);
	PUTB(0xb8), PUTB(0xff), PUTB(0xff), PUTB(0xff), PUTB(0xff);
	PUTB(0xc3);

	/* Revoke write access from the affected functions */
	NOEXCEPT_DO(MProtect(__libc_errno_access_core_start, core_size, PROT_READ | PROT_EXEC));

	/* Remember that we did this whole re-assignment thingy. */
	COMPILER_WRITE_BARRIER();
	nontls_errno_addr = g_errno;
	COMPILER_WRITE_BARRIER();
	return g_errno;
}


DEFINE_PUBLIC_IDATA(errno, nontls_errno_getaddr, __SIZEOF_ERRNO_T__);
DEFINE_PUBLIC_IDATA(_errno, nontls_errno_getaddr, __SIZEOF_ERRNO_T__);
INTERN ATTR_SECTION(".text.crt.glibc.application.init") errno_t *
NOTHROW(LIBCCALL nontls_errno_getaddr)(void) {
	/* The return value here is either the address to-be linked for
	 * non-TLS library access to `errno',  or a source buffer  from
	 * which a  copy-relocation initializes  the primary  program's
	 * `errno' variable copy. */
	errno_t *result = nontls_errno_addr;
	if (result == NULL)
		result = nontls_errno_redirect();
	return result;
}


DECL_END
#endif /* !__x86_64__ && __i386__ */

#endif /* GUARD_LIBC_LIBC_ARCH_I386_ERRNO_C */
