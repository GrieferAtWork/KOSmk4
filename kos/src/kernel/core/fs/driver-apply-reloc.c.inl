/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "driver.c"
#define APPLY_RELA 1
#endif /* __INTELLISENSE__ */

DECL_BEGIN

#ifdef APPLY_RELA
#define SET_OR_INPLACE_ADD =
#define IFELSE_RELA(if_rel, if_rela) if_rela
#else /* APPLY_RELA */
#define SET_OR_INPLACE_ADD +=
#define IFELSE_RELA(if_rel, if_rela) if_rel
#endif /* !APPLY_RELA */


#ifdef APPLY_RELA
/* @param: reloc_flags: Set of `DRIVER_RELOC_FLAG_*' */
INTERN NONNULL((1, 2)) void KCALL
driver_do_apply_relocations_vector_addend(struct driver *__restrict self,
                                          ElfW(Rela) *__restrict vector,
                                          size_t count, unsigned int reloc_flags)
#else /* APPLY_RELA */
/* @param: reloc_flags: Set of `DRIVER_RELOC_FLAG_*' */
INTERN NONNULL((1, 2)) void KCALL
driver_do_apply_relocations_vector(struct driver *__restrict self,
                                   ElfW(Rel) *__restrict vector,
                                   size_t count, unsigned int reloc_flags)
#endif /* !APPLY_RELA */
{
	size_t i;
	ElfW(Addr) value;
	byte_t *loadaddr = (byte_t *)self->d_loadaddr;
	for (i = 0; i < count; ++i) {
#ifdef APPLY_RELA
		ElfW(Rela) rel = vector[i];
#define REL_ADDEND rel.r_addend
#else /* APPLY_RELA */
		ElfW(Rel) rel = vector[i];
#define REL_ADDEND 0
#endif /* !APPLY_RELA */
		byte_t *reladdr = loadaddr + rel.r_offset;
		switch (ELFW(R_TYPE)(rel.r_info)) {
#define LOOKUP_SYMBOL()                                                                  \
	value = (ElfW(Addr))driver_find_symbol_for_relocation(self, ELFW(R_SYM)(rel.r_info), \
	                                                      NULL, NULL, reloc_flags)


#ifdef ELF_ARCH_CASE_R_NONE
		ELF_ARCH_CASE_R_NONE:
			break;
#endif /* ELF_ARCH_CASE_R_NONE */


#ifdef ELF_ARCH_CASE_R_RELATIVE32
		ELF_ARCH_CASE_R_RELATIVE32:
			*(u32 *)reladdr SET_OR_INPLACE_ADD (u32)(uintptr_t)loadaddr;
			break;
#endif /* ELF_ARCH_CASE_R_RELATIVE32 */


#ifdef ELF_ARCH_CASE_R_RELATIVE64
		ELF_ARCH_CASE_R_RELATIVE64:
			*(u64 *)reladdr SET_OR_INPLACE_ADD (u64)(uintptr_t)(loadaddr + REL_ADDEND);
			break;
#endif /* ELF_ARCH_CASE_R_RELATIVE64 */


#ifdef ELF_ARCH_CASE_R_IRELATIVE32
		ELF_ARCH_CASE_R_IRELATIVE32:
			*(u32 *)reladdr = IFELSE_RELA((*(Elf32_Addr(*)(void))((uintptr_t)*(u32 *)reladdr + (uintptr_t)loadaddr))(),
			                              (*(Elf32_Addr(*)(void))((uintptr_t)loadaddr + REL_ADDEND))());
			break;
#endif /* ELF_ARCH_CASE_R_IRELATIVE32 */


#ifdef ELF_ARCH_CASE_R_IRELATIVE64
		ELF_ARCH_CASE_R_IRELATIVE64:
			*(u64 *)reladdr = IFELSE_RELA((*(Elf64_Addr(*)(void))((uintptr_t)*(u64 *)reladdr + (uintptr_t)loadaddr))(),
			                              (*(Elf64_Addr(*)(void))((uintptr_t)loadaddr + REL_ADDEND))());
			break;
#endif /* ELF_ARCH_CASE_R_IRELATIVE64 */


#ifdef ELF_ARCH_CASE_R_SIZE32
		ELF_ARCH_CASE_R_SIZE32: {
			size_t symbol_size;
			driver_find_symbol_for_relocation(self,
			                                  ELFW(R_SYM)(rel.r_info),
			                                  &symbol_size,
			                                  NULL,
			                                  reloc_flags);
			*(u32 *)reladdr SET_OR_INPLACE_ADD (u32)(symbol_size + REL_ADDEND);
		}	break;
#endif /* ELF_ARCH_CASE_R_SIZE32 */


#ifdef ELF_ARCH_CASE_R_SIZE64
		ELF_ARCH_CASE_R_SIZE64: {
			size_t symbol_size;
			driver_find_symbol_for_relocation(self,
			                                  ELFW(R_SYM)(rel.r_info),
			                                  &symbol_size,
			                                  NULL,
			                                  reloc_flags);
			*(u64 *)reladdr SET_OR_INPLACE_ADD (u64)(symbol_size + REL_ADDEND);
		}	break;
#endif /* ELF_ARCH_CASE_R_SIZE64 */


#ifdef ELF_ARCH_CASE_R_COPY
		ELF_ARCH_CASE_R_COPY: {
			ElfW(Sym) const *dst_sym;
			size_t src_size;
			struct driver *src_module;
			dst_sym = self->d_dynsym_tab + ELFW(R_SYM)(rel.r_info);
			value = (ElfW(Addr))driver_find_symbol_for_relocation(self,
			                                                      ELFW(R_SYM)(rel.r_info),
			                                                      &src_size,
			                                                      &src_module,
			                                                      reloc_flags);
			if unlikely(dst_sym->st_size != src_size) {
				printk(KERN_WARNING "[mod] %q: Symbol %q imported with %Iu bytes, but exported with %Iu from %q\n",
				       self->d_filename ? self->d_filename : self->d_name,
				       self->d_dynstr + dst_sym->st_name,
				       dst_sym->st_size, src_size, src_module->d_filename);
			}
			if unlikely(src_size > dst_sym->st_size)
				src_size = dst_sym->st_size;
			memcpy((void *)reladdr, (void *)value, src_size);
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
			*(u8 *)reladdr SET_OR_INPLACE_ADD (u8)(value + REL_ADDEND);
			break;
#endif /* ELF_ARCH_CASE_R_8 || ELF_ARCH_CASE_R_8S */


#ifdef ELF_ARCH_CASE_R_PC8
		ELF_ARCH_CASE_R_PC8:
			LOOKUP_SYMBOL();
			*(u8 *)reladdr SET_OR_INPLACE_ADD (u8)((value + REL_ADDEND) - (uintptr_t)reladdr);
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
			*(u16 *)reladdr SET_OR_INPLACE_ADD (u16)(value + REL_ADDEND);
			break;
#endif /* ELF_ARCH_CASE_R_16 || ELF_ARCH_CASE_R_16S */


#ifdef ELF_ARCH_CASE_R_PC16
		ELF_ARCH_CASE_R_PC16:
			LOOKUP_SYMBOL();
			*(u16 *)reladdr SET_OR_INPLACE_ADD (u16)((value + REL_ADDEND) - (uintptr_t)reladdr);
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
			*(u32 *)reladdr SET_OR_INPLACE_ADD (u32)(value + REL_ADDEND);
			break;
#endif /* ELF_ARCH_CASE_R_32 || ELF_ARCH_CASE_R_32S */


#ifdef ELF_ARCH_CASE_R_PC32
		ELF_ARCH_CASE_R_PC32:
			LOOKUP_SYMBOL();
			*(u32 *)reladdr SET_OR_INPLACE_ADD (u32)((value + REL_ADDEND) - (uintptr_t)reladdr);
			break;
#endif /* ELF_ARCH_CASE_R_PC32 */


#ifdef ELF_ARCH_CASE_R_64
		ELF_ARCH_CASE_R_64:
			LOOKUP_SYMBOL();
			*(u64 *)reladdr SET_OR_INPLACE_ADD (u64)(value + REL_ADDEND);
			break;
#endif /* ELF_ARCH_CASE_R_64 */


#ifdef ELF_ARCH_CASE_R_PC64
		ELF_ARCH_CASE_R_PC64:
			LOOKUP_SYMBOL();
			*(u64 *)reladdr SET_OR_INPLACE_ADD (u64)((value + REL_ADDEND) - (uintptr_t)reladdr);
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
			*(uintptr_t *)reladdr SET_OR_INPLACE_ADD (uintptr_t)(value + REL_ADDEND);
			break;
#endif /* ELF_ARCH_CASE_R_JMP_SLOT || ELF_ARCH_CASE_R_GLOB_DAT */


		default:
#ifdef APPLY_RELA
			printk(KERN_WARNING "[mod] %q: Relocation #%Iu at %p (%#Ix+%#Ix) has unknown type %u (%#x) [addend=%s%#Ix]\n",
			       self->d_filename ? self->d_filename : self->d_name,
			       (size_t)i, reladdr, (uintptr_t)loadaddr, (uintptr_t)rel.r_offset,
			       (unsigned int)ELFW(R_TYPE)(rel.r_info),
			       (unsigned int)ELFW(R_TYPE)(rel.r_info),
			       rel.r_addend < 0 ? "-" : "",
			       rel.r_addend < 0 ? (uintptr_t)-rel.r_addend
			                        : (uintptr_t)rel.r_addend);
#else /* APPLY_RELA */
			printk(KERN_WARNING "%q: Relocation #%Iu at %p (%#Ix+%#Ix) has unknown type %u (%#x)\n",
			       self->d_filename ? self->d_filename : self->d_name,
			       (size_t)i, reladdr, (uintptr_t)loadaddr, (uintptr_t)rel.r_offset,
			       (unsigned int)ELFW(R_TYPE)(rel.r_info),
			       (unsigned int)ELFW(R_TYPE)(rel.r_info));
#endif /* !APPLY_RELA */
			break;
		}
#undef REL_ADDEND
	}
}


DECL_END

#undef SET_OR_INPLACE_ADD
#undef IFELSE_RELA
#undef APPLY_RELA
