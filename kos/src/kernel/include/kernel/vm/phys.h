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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_VM_PHYS_H
#define GUARD_KERNEL_INCLUDE_KERNEL_VM_PHYS_H 1

#include <kernel/compiler.h>

#include <kernel/mman/phys.h>

#define vm_readphysb(addr)                   peekphysb(addr)
#define vm_readphysw(addr)                   peekphysw(addr)
#define vm_readphysl(addr)                   peekphysl(addr)
#define vm_readphysw_unaligned(addr)         peekphysw_unaligned(addr)
#define vm_readphysl_unaligned(addr)         peekphysl_unaligned(addr)
#define vm_writephysb(addr, value)           pokephysb(addr, value)
#define vm_writephysw(addr, value)           pokephysw(addr, value)
#define vm_writephysl(addr, value)           pokephysl(addr, value)
#define vm_writephysw_unaligned(addr, value) pokephysw_unaligned(addr, value)
#define vm_writephysl_unaligned(addr, value) pokephysl_unaligned(addr, value)
#ifdef __UINT64_TYPE__
#define vm_readphysq(addr)                   peekphysq(addr)
#define vm_readphysq_unaligned(addr)         peekphysq_unaligned(addr)
#define vm_writephysq(addr, value)           pokephysq(addr, value)
#define vm_writephysq_unaligned(addr, value) pokephysq_unaligned(addr, value)
#endif /* __UINT64_TYPE__ */
#define vm_insb_phys(port, buf, num_bytes)                insphysb(port, buf, num_bytes)
#define vm_insw_phys(port, buf, num_words)                insphysw(port, buf, num_words)
#define vm_insl_phys(port, buf, num_dwords)               insphysl(port, buf, num_dwords)
#define vm_outsb_phys(port, buf, num_bytes)               outsphysb(port, buf, num_bytes)
#define vm_outsw_phys(port, buf, num_words)               outsphysw(port, buf, num_words)
#define vm_outsl_phys(port, buf, num_dwords)              outsphysl(port, buf, num_dwords)
#define vm_copyfromphys(dst, src, num_bytes)              copyfromphys(dst, src, num_bytes)
#define vm_copytophys(dst, src, num_bytes)                copytophys(dst, src, num_bytes)
#define vm_copyinphys(dst, src, num_bytes)                copyinphys(dst, src, num_bytes)
#define vm_memsetphys(dst, byte, num_bytes)               memsetphys(dst, byte, num_bytes)
#define vm_copyfromphys_nopf(dst, src, num_bytes)         copyfromphys_nopf(dst, src, num_bytes)
#define vm_copytophys_nopf(dst, src, num_bytes)           copytophys_nopf(dst, src, num_bytes)
#define vm_copyfromphys_onepage(dst, src, num_bytes)      copyfromphys_onepage(dst, src, num_bytes)
#define vm_copytophys_onepage(dst, src, num_bytes)        copytophys_onepage(dst, src, num_bytes)
#define vm_copyinphys_onepage(dst, src, num_bytes)        copyinphys_onepage(dst, src, num_bytes)
#define vm_memsetphys_onepage(dst, byte, num_bytes)       memsetphys_onepage(dst, byte, num_bytes)
#define vm_copyfromphys_onepage_nopf(dst, src, num_bytes) copyfromphys_onepage_nopf(dst, src, num_bytes)
#define vm_copytophys_onepage_nopf(dst, src, num_bytes)   copytophys_onepage_nopf(dst, src, num_bytes)
#define vm_copypagefromphys(dst, src)                     copypagefromphys(dst, src)
#define vm_copypagetophys(dst, src)                       copypagetophys(dst, src)
#define vm_copypageinphys(dst, src)                       copypageinphys(dst, src)
#define vm_copypagesinphys(dst, src, num_pages)           copypagesinphys(dst, src, (num_pages) * PAGESIZE)
#define vm_memsetphyspage(dst, byte)                      memsetphyspage(dst, byte)
#define vm_memsetphyspages(dst, byte, num_pages)          memsetphyspages(dst, byte, (num_pages) * PAGESIZE)
#define vm_copypagefromphys_nopf(dst, src)                copypagefromphys_nopf(dst, src)
#define vm_copypagetophys_nopf(dst, src)                  copypagetophys_nopf(dst, src)
#define vm_ptram                                          mptram
#define pt_pushval                                        mpt_pushval
#define VM_PTRAM_INIT                                     MPTRAM_INIT
#define vm_ptram_init(self)                               mptram_init(self)
#define vm_ptram_cinit(self)                              mptram_cinit(self)
#define vm_ptram_fini(self)                               mptram_fini(self)
#define vm_ptram_mappage_noidentity(self, page, ...)      mptram_mappage_noidentity(self, page)
#define vm_ptram_mappage(self, page, ...)                 mptram_mappage(self, page)
#define vm_ptram_map_noidentity(self, addr, ...)          mptram_map_noidentity(self, addr)
#define vm_ptram_map(self, addr, ...)                     mptram_map(self, addr)

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_VM_PHYS_H */
