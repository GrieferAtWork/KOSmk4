/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "driver.c"
//#define DEFINE_driver_do_apply_relocations_vector
#define DEFINE_driver_do_apply_relocations_vector_addend
#endif /* __INTELLISENSE__ */

#include <kos/exec/elf-rel.h>

DECL_BEGIN

/* @param: reloc_flags: Set of `DRIVER_RELOC_FLAG_*' */
#ifdef DEFINE_driver_do_apply_relocations_vector
PRIVATE BLOCKING NONNULL((1, 2)) void KCALL
driver_do_apply_relocations_vector(struct driver *__restrict self,
                                   ElfW(Rel) *__restrict vector,
                                   size_t count, unsigned int reloc_flags)
#undef LOCAL_HAVE_ADDENDS
#elif defined(DEFINE_driver_do_apply_relocations_vector_addend)
PRIVATE BLOCKING NONNULL((1, 2)) void KCALL
driver_do_apply_relocations_vector_addend(struct driver *__restrict self,
                                          ElfW(Rela) *__restrict vector,
                                          size_t count, unsigned int reloc_flags)
#define LOCAL_HAVE_ADDENDS
#else /* ... */
#error "Invalid configuration"
#endif /* !... */
{
#ifdef LOCAL_HAVE_ADDENDS
#define LOCAL_setoradd                    =
#define LOCAL_IE_ADDENDS(if_rel, if_rela) if_rela
#else /* LOCAL_HAVE_ADDENDS */
#define LOCAL_setoradd                    +=
#define LOCAL_IE_ADDENDS(if_rel, if_rela) if_rel
#endif /* !LOCAL_HAVE_ADDENDS */
	size_t i;
	struct driver_reloc_syminfo si;
	uintptr_t loadaddr;
	si.drs_self   = self;
	si.drs_rflags = reloc_flags;
	loadaddr      = self->d_module.md_loadaddr;
	for (i = 0; i < count; ++i) {
#ifdef LOCAL_HAVE_ADDENDS
		ElfW(Rela) rel = vector[i];
#define LOCAL_addend rel.r_addend
#else /* LOCAL_HAVE_ADDENDS */
		ElfW(Rel) rel = vector[i];
#define LOCAL_addend 0
#endif /* !LOCAL_HAVE_ADDENDS */
		byte_t *reladdr = (byte_t *)(loadaddr + rel.r_offset);
		switch (ELFW(R_TYPE)(rel.r_info)) {
#define LOOKUP_SYMBOL() driver_dlsym_for_reloc(&si, ELFW(R_SYM)(rel.r_info))

#ifdef ELF_ARCH_CASE_R_NONE
		ELF_ARCH_CASE_R_NONE:
			break;
#endif /* ELF_ARCH_CASE_R_NONE */


#ifdef ELF_ARCH_CASE_R_RELATIVE32
		ELF_ARCH_CASE_R_RELATIVE32:
			*(u32 *)reladdr LOCAL_setoradd (u32)loadaddr;
			break;
#endif /* ELF_ARCH_CASE_R_RELATIVE32 */


#ifdef ELF_ARCH_CASE_R_RELATIVE64
		ELF_ARCH_CASE_R_RELATIVE64:
			*(u64 *)reladdr LOCAL_setoradd (u64)(loadaddr + LOCAL_addend);
			break;
#endif /* ELF_ARCH_CASE_R_RELATIVE64 */


#ifdef ELF_ARCH_CASE_R_IRELATIVE32
		ELF_ARCH_CASE_R_IRELATIVE32:
			*(u32 *)reladdr = LOCAL_IE_ADDENDS((*(Elf32_Addr(*)(void))(void *)((uintptr_t)(*(u32 const *)reladdr) + loadaddr))(),
			                                   (*(Elf32_Addr(*)(void))(void *)(loadaddr + LOCAL_addend))());
			break;
#endif /* ELF_ARCH_CASE_R_IRELATIVE32 */


#ifdef ELF_ARCH_CASE_R_IRELATIVE64
		ELF_ARCH_CASE_R_IRELATIVE64:
			*(u64 *)reladdr = LOCAL_IE_ADDENDS((*(Elf64_Addr(*)(void))(void *)((uintptr_t)(*(u64 const *)reladdr) + loadaddr))(),
			                                   (*(Elf64_Addr(*)(void))(void *)(loadaddr + LOCAL_addend))());
			break;
#endif /* ELF_ARCH_CASE_R_IRELATIVE64 */


#ifdef ELF_ARCH_CASE_R_SIZE32
		ELF_ARCH_CASE_R_SIZE32:
			LOOKUP_SYMBOL();
			*(u32 *)reladdr LOCAL_setoradd (u32)(si.dsi_size + LOCAL_addend);
			break;
#endif /* ELF_ARCH_CASE_R_SIZE32 */


#ifdef ELF_ARCH_CASE_R_SIZE64
		ELF_ARCH_CASE_R_SIZE64:
			LOOKUP_SYMBOL();
			*(u64 *)reladdr LOCAL_setoradd (u64)(si.dsi_size + LOCAL_addend);
			break;
#endif /* ELF_ARCH_CASE_R_SIZE64 */


#ifdef ELF_ARCH_CASE_R_COPY
		ELF_ARCH_CASE_R_COPY: {
			ElfW(Sym) const *dst_sym;
			dst_sym = self->d_dynsym_tab + ELFW(R_SYM)(rel.r_info);
			LOOKUP_SYMBOL();
			if unlikely(dst_sym->st_size != si.dsi_size) {
				printk(KERN_WARNING "[mod][%s] Symbol %q imported with %" PRIuSIZ " bytes, "
				                    "but exported from %q with %" PRIuSIZ " bytes\n",
				       self->d_name, self->d_dynstr + dst_sym->st_name,
				       dst_sym->st_size, si.drs_orig ? si.drs_orig->d_name : "?", si.dsi_size);
			}
			if unlikely(si.dsi_size > dst_sym->st_size)
				si.dsi_size = dst_sym->st_size;
			memcpy(reladdr, si.dsi_addr, si.dsi_size);
		}	break;
#endif /* ELF_ARCH_CASE_R_COPY */


#if defined(ELF_ARCH_CASE_R_8) || defined(ELF_ARCH_CASE_R_8S)
#ifdef ELF_ARCH_CASE_R_8
		ELF_ARCH_CASE_R_8:
#endif /* ELF_ARCH_CASE_R_8 */
#ifdef ELF_ARCH_CASE_R_8S
		ELF_ARCH_CASE_R_8S:
#endif /* ELF_ARCH_CASE_R_8S */
			LOOKUP_SYMBOL();
			*(u8 *)reladdr LOCAL_setoradd (u8)((uintptr_t)si.dsi_addr + LOCAL_addend);
			break;
#endif /* ELF_ARCH_CASE_R_8 || ELF_ARCH_CASE_R_8S */


#ifdef ELF_ARCH_CASE_R_PC8
		ELF_ARCH_CASE_R_PC8:
			LOOKUP_SYMBOL();
			*(u8 *)reladdr LOCAL_setoradd (u8)(((uintptr_t)si.dsi_addr + LOCAL_addend) - (uintptr_t)reladdr);
			break;
#endif /* ELF_ARCH_CASE_R_PC8 */


#if defined(ELF_ARCH_CASE_R_16) || defined(ELF_ARCH_CASE_R_16S)
#ifdef ELF_ARCH_CASE_R_16
		ELF_ARCH_CASE_R_16:
#endif /* ELF_ARCH_CASE_R_16 */
#ifdef ELF_ARCH_CASE_R_16S
		ELF_ARCH_CASE_R_16S:
#endif /* ELF_ARCH_CASE_R_16S */
			LOOKUP_SYMBOL();
			*(u16 *)reladdr LOCAL_setoradd (u16)((uintptr_t)si.dsi_addr + LOCAL_addend);
			break;
#endif /* ELF_ARCH_CASE_R_16 || ELF_ARCH_CASE_R_16S */


#ifdef ELF_ARCH_CASE_R_PC16
		ELF_ARCH_CASE_R_PC16:
			LOOKUP_SYMBOL();
			*(u16 *)reladdr LOCAL_setoradd (u16)(((uintptr_t)si.dsi_addr + LOCAL_addend) - (uintptr_t)reladdr);
			break;
#endif /* ELF_ARCH_CASE_R_PC16 */


#if defined(ELF_ARCH_CASE_R_32) || defined(ELF_ARCH_CASE_R_32S)
#ifdef ELF_ARCH_CASE_R_32
		ELF_ARCH_CASE_R_32:
#endif /* ELF_ARCH_CASE_R_32 */
#ifdef ELF_ARCH_CASE_R_32S
		ELF_ARCH_CASE_R_32S:
#endif /* ELF_ARCH_CASE_R_32S */
			LOOKUP_SYMBOL();
			*(u32 *)reladdr LOCAL_setoradd (u32)((uintptr_t)si.dsi_addr + LOCAL_addend);
			break;
#endif /* ELF_ARCH_CASE_R_32 || ELF_ARCH_CASE_R_32S */


#ifdef ELF_ARCH_CASE_R_PC32
		ELF_ARCH_CASE_R_PC32:
			LOOKUP_SYMBOL();
			*(u32 *)reladdr LOCAL_setoradd (u32)(((uintptr_t)si.dsi_addr + LOCAL_addend) - (uintptr_t)reladdr);
			break;
#endif /* ELF_ARCH_CASE_R_PC32 */


#ifdef ELF_ARCH_CASE_R_64
		ELF_ARCH_CASE_R_64:
			LOOKUP_SYMBOL();
			*(u64 *)reladdr LOCAL_setoradd (u64)((uintptr_t)si.dsi_addr + LOCAL_addend);
			break;
#endif /* ELF_ARCH_CASE_R_64 */


#ifdef ELF_ARCH_CASE_R_PC64
		ELF_ARCH_CASE_R_PC64:
			LOOKUP_SYMBOL();
			*(u64 *)reladdr LOCAL_setoradd (u64)(((uintptr_t)si.dsi_addr + LOCAL_addend) - (uintptr_t)reladdr);
			break;
#endif /* ELF_ARCH_CASE_R_PC64 */


#if defined(ELF_ARCH_CASE_R_JMP_SLOT) || defined(ELF_ARCH_CASE_R_GLOB_DAT)
#ifdef ELF_ARCH_CASE_R_JMP_SLOT
		ELF_ARCH_CASE_R_JMP_SLOT:
#endif /* ELF_ARCH_CASE_R_JMP_SLOT */
#ifdef ELF_ARCH_CASE_R_GLOB_DAT
		ELF_ARCH_CASE_R_GLOB_DAT:
#endif /* ELF_ARCH_CASE_R_GLOB_DAT */
			LOOKUP_SYMBOL();
			*(uintptr_t *)reladdr LOCAL_setoradd (uintptr_t)((uintptr_t)si.dsi_addr + LOCAL_addend);
			break;
#endif /* ELF_ARCH_CASE_R_JMP_SLOT || ELF_ARCH_CASE_R_GLOB_DAT */


		default:
			printk(KERN_WARNING "[mod][%s]: Relocation #%" PRIuSIZ " at %p ("
			                    "%#" PRIxPTR "+%#" PRIxN(__SIZEOF_ELFW(ADDR__)) ") "
			                    "has unknown type %u (%#x)"
#ifdef LOCAL_HAVE_ADDENDS
			                    " [addend=%s%#" PRIxPTR "]"
#endif /* LOCAL_HAVE_ADDENDS */
			                    "\n",
			       self->d_name, (size_t)i, reladdr, loadaddr,
			       (uintptr_t)rel.r_offset,
			       (unsigned int)ELFW(R_TYPE)(rel.r_info),
			       (unsigned int)ELFW(R_TYPE)(rel.r_info)
#ifdef LOCAL_HAVE_ADDENDS
			       ,
			       rel.r_addend < 0 ? "-" : "",
			       rel.r_addend < 0 ? (uintptr_t)-rel.r_addend
			                        : (uintptr_t)rel.r_addend
#endif /* LOCAL_HAVE_ADDENDS */
			       );
			break;
		}
#undef LOCAL_addend
	}
#undef LOCAL_IE_ADDENDS
#undef LOCAL_setoradd
}
#undef LOCAL_HAVE_ADDENDS

DECL_END

#undef DEFINE_driver_do_apply_relocations_vector_addend
#undef DEFINE_driver_do_apply_relocations_vector
