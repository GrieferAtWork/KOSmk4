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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_SHARE_H
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_SHARE_H 1

#include <kernel/compiler.h>
#include <kernel/paging.h>

DECL_BEGIN

#ifndef CONFIG_NO_KERNEL_X86_PAGING_P32
struct ATTR_ALIGNED(4096) p32_kernel_share {
	/* These 255 E1-vectors are  used to fill  in the last  1GiB of virtual  memory
	 * with mappings to identity-map the first 1GiB of physical memory during boot.
	 * Later on then,  these mappings are  re-used to provide  a common mapping  of
	 * kernel-space  memory within all  page directories by  only ever changing the
	 * contents of these E1-entries which  are pointed-to by every page  directory.
	 * Note that we don't  need 256 of  these entries, since  the last one  already
	 * gets used as the identity vector (s.a. `P32_MMAN_KERNEL_PDIR_IDENTITY_BASE')
	 *
	 * The initialization in _start32.S looks like this:
	 * >> VECTOR_FLAGS = P32_PAGE_FACCESSED | P32_PAGE_FWRITE | P32_PAGE_FPRESENT;
	 * >> PAGE_FLAGS   = P32_PAGE_FACCESSED | P32_PAGE_FWRITE | P32_PAGE_FPRESENT |
	 * >>                P32_PAGE_FDIRTY | P32_PAGE_FGLOBAL | P32_PAGE_FPREPARED;
	 * >> for (i = 768; i < 1023; ++i) {
	 * >>     pagedir_kernel.pd_p32.p_e2[i].p_word = PHYS_ADDR(&ks_share[i - 768][0]) | VECTOR_FLAGS;
	 * >> }
	 * >> pagedir_kernel.pd_p32.p_e2[1023].p_word = PHYS_ADDR(&pagedir_kernel) | VECTOR_FLAGS; // Self-map
	 * >> for (i = 0; i < 255 * 1024; ++i) {
	 * >>     ((union p32_pdir_e1 *)&ks_share[0][0])[i].p_word = (i * 4096) | PAGE_FLAGS;
	 * >> }
	 * >> i = __x86_p32_identity_mapped_text_4mib_index;
	 * >> pagedir_kernel.pd_p32.p_e2[i].p_word = PHYS_ADDR(&ks_share[i][0]) | VECTOR_FLAGS;
	 */
	union p32_pdir_e1 ks_share[255][1024];
};
#endif /* !CONFIG_NO_KERNEL_X86_PAGING_P32 */

#ifndef CONFIG_NO_KERNEL_X86_PAGING_PAE
struct ATTR_ALIGNED(4096) pae_kernel_share {
	/* `ks_share_e1' here is the same deal as `p32_kernel_share', used to fill in
	 * the  last 1GiB of virtual memory with an identity-map of the first 1GiB of
	 * physical  memory. - However we only need  508 instead of 512 vectors since
	 * the last 4 vectors are needed in order to identity-map the page directory.
	 * The second vector `ks_share_e2' is  needed to allocate the top-level  page
	 * directory vectors for the kernel page directory.
	 *
	 * The initialization in _start32.S looks like this:
	 * >> VECTOR_FLAGS = PAE_PAGE_FACCESSED | PAE_PAGE_FWRITE | PAE_PAGE_FPRESENT;
	 * >> PAGE_FLAGS   = PAE_PAGE_FACCESSED | PAE_PAGE_FWRITE | PAE_PAGE_FPRESENT |
	 * >>                PAE_PAGE_FDIRTY | PAE_PAGE_FGLOBAL | PAE_PAGE_FPREPARED;
	 * >> pagedir_kernel.pd_pae.p_e3[0].p_word = PHYS_ADDR(&ks_share_e2[3][0]) | PAE_PAGE_FPRESENT; // Low-memory identity map (removed later)
	 * >> pagedir_kernel.pd_pae.p_e3[1].p_word = PHYS_ADDR(&ks_share_e2[1][0]) | PAE_PAGE_FPRESENT;
	 * >> pagedir_kernel.pd_pae.p_e3[2].p_word = PHYS_ADDR(&ks_share_e2[2][0]) | PAE_PAGE_FPRESENT;
	 * >> pagedir_kernel.pd_pae.p_e3[3].p_word = PHYS_ADDR(&ks_share_e2[3][0]) | PAE_PAGE_FPRESENT;
	 * >> // Note that this init is already done by .bss (it is only
	 * >> // explicitly stated here since this zero-init is required)
	 * >> memsetq(ks_share_e2, 0, 3 * 512);
	 * >> for (i = 0; i < 508; ++i) {
	 * >>     ks_share_e2[3][i] = PHYS_ADDR(&ks_share_e1[i][0]) | VECTOR_FLAGS;
	 * >> }
	 * >> ks_share_e2[3][508] = PHYS_ADDR(&ks_share_e2[0][0]) | VECTOR_FLAGS; // Self-map
	 * >> ks_share_e2[3][509] = PHYS_ADDR(&ks_share_e2[1][0]) | VECTOR_FLAGS; // Self-map
	 * >> ks_share_e2[3][510] = PHYS_ADDR(&ks_share_e2[2][0]) | VECTOR_FLAGS; // Self-map
	 * >> ks_share_e2[3][511] = PHYS_ADDR(&ks_share_e2[3][0]) | VECTOR_FLAGS; // Self-map
	 * >> for (i = 0; i < 508 * 512; ++i) {
	 * >>     ((union pae_pdir_e1 *)&ks_share_e1[0][0])[i].p_word = (i * 4096) | PAGE_FLAGS;
	 * >> }
	 */
	union pae_pdir_e2 ks_share_e2[4][512];
	union pae_pdir_e1 ks_share_e1[508][512];
};

#endif /* !CONFIG_NO_KERNEL_X86_PAGING_PAE */


typedef union {
#ifndef CONFIG_NO_KERNEL_X86_PAGING_P32
	struct p32_kernel_share ks_p32;
#endif /* !CONFIG_NO_KERNEL_X86_PAGING_P32 */
#ifndef CONFIG_NO_KERNEL_X86_PAGING_PAE
	struct pae_kernel_share ks_pae;
#endif /* !CONFIG_NO_KERNEL_X86_PAGING_PAE */
} kernel_share_t;

/* Allocate BSS memory for the initial shared+identity mapping
 * that  will later be shared with, and re-appear in all other
 * page directories (except for the identity page)
 * NOTE: This buffer is quite large (1Mb), but we'd need
 *       to allocate it sooner or later, no matter what. */
INTDEF kernel_share_t __x86_pagedir_kernel_share;

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_SHARE_H */
