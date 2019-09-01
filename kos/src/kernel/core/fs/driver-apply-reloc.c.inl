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
#endif

DECL_BEGIN

#ifdef APPLY_RELA
#define SET_OR_INPLACE_ADD =
#else /* APPLY_RELA */
#define SET_OR_INPLACE_ADD +=
#endif /* !APPLY_RELA */


#ifdef APPLY_RELA
/* @param: reloc_flags: Set of `DRIVER_RELOC_FLAG_*' */
INTERN NONNULL((1, 2)) void KCALL
driver_do_apply_relocations_vector_addend(struct driver *__restrict self,
                                          Elf_Rela *__restrict vector,
                                          size_t count, unsigned int reloc_flags)
#else /* APPLY_RELA */
/* @param: reloc_flags: Set of `DRIVER_RELOC_FLAG_*' */
INTERN NONNULL((1, 2)) void KCALL
driver_do_apply_relocations_vector(struct driver *__restrict self,
                                   Elf_Rel *__restrict vector,
                                   size_t count, unsigned int reloc_flags)
#endif /* !APPLY_RELA */
{
	size_t i;
	Elf_Addr value;
	byte_t *loadaddr = (byte_t *)self->d_loadaddr;
	for (i = 0; i < count; ++i) {
#ifdef APPLY_RELA
		Elf_Rela rel = vector[i];
#define REL_ADDEND rel.r_addend
#else /* APPLY_RELA */
		Elf_Rel rel = vector[i];
#define REL_ADDEND 0
#endif /* !APPLY_RELA */
		byte_t *reladdr = loadaddr + rel.r_offset;
		switch (ELF_R_TYPE(rel.r_info)) {
#define LOOKUP_SYMBOL() \
		value = (Elf_Addr)driver_find_symbol_for_relocation(self, ELF_R_SYM(rel.r_info), NULL, NULL, reloc_flags)

#if defined(__x86_64__)
#define R_USED_NONE           R_X86_64_NONE
#define R_USED_COPY           R_X86_64_COPY
#define R_USED_8              R_X86_64_8
#define R_USED_16             R_X86_64_16
#define R_USED_32             R_X86_64_32
#define R_USED_32_ALT         R_X86_64_32S
#define R_USED_64             R_X86_64_64
#define R_USED_PC8            R_X86_64_PC8
#define R_USED_PC16           R_X86_64_PC16
#define R_USED_PC32           R_X86_64_PC32
#define R_USED_PC64           R_X86_64_PC64
#define R_USED_GLOB_DAT       R_X86_64_GLOB_DAT
#define R_USED_JMP_SLOT       R_X86_64_JMP_SLOT
#define R_USED_RELATIVE32     R_X86_64_RELATIVE
#define R_USED_RELATIVE64     R_X86_64_RELATIVE64
#define R_USED_IRELATIVE64    R_X86_64_IRELATIVE
#define R_USED_SIZE32         R_X86_64_SIZE32
#define R_USED_SIZE64         R_X86_64_SIZE64
#elif defined(__i386__)
#define R_USED_NONE        R_386_NONE
#define R_USED_COPY        R_386_COPY
#define R_USED_8           R_386_8
#define R_USED_16          R_386_16
#define R_USED_32          R_386_32
#define R_USED_PC8         R_386_PC8
#define R_USED_PC16        R_386_PC16
#define R_USED_PC32        R_386_PC32
#define R_USED_GLOB_DAT    R_386_GLOB_DAT
#define R_USED_JMP_SLOT    R_386_JMP_SLOT
#define R_USED_RELATIVE32  R_386_RELATIVE
#define R_USED_IRELATIVE32 R_386_IRELATIVE
#else
#error "Unsupported architecture"
#endif


#ifdef R_USED_RELATIVE32
		case R_USED_RELATIVE32:
#undef R_USED_RELATIVE32
			*(u32 *)reladdr SET_OR_INPLACE_ADD (u32)(uintptr_t)loadaddr;
			break;
#endif /* R_USED_RELATIVE32 */


#ifdef R_USED_RELATIVE64
		case R_USED_RELATIVE64:
#undef R_USED_RELATIVE64
			*(u64 *)reladdr SET_OR_INPLACE_ADD (u64)(uintptr_t)(loadaddr + REL_ADDEND);
			break;
#endif /* R_USED_RELATIVE64 */


#ifdef R_USED_IRELATIVE32
		case R_USED_IRELATIVE32:
#undef R_USED_IRELATIVE32
#ifdef APPLY_RELA
			*(u32 *)reladdr = (*(Elf32_Addr(*)(void))((uintptr_t)loadaddr + REL_ADDEND))();
#else /* APPLY_RELA */
			*(u32 *)reladdr = (*(Elf32_Addr(*)(void))((uintptr_t)*(u32 *)reladdr + (uintptr_t)loadaddr))();
#endif /* !APPLY_RELA */
			break;
#endif /* R_USED_RELATIVE32 */


#ifdef R_USED_IRELATIVE64
		case R_USED_IRELATIVE64:
#undef R_USED_IRELATIVE64
#ifdef APPLY_RELA
			*(u64 *)reladdr = (*(Elf64_Addr(*)(void))((uintptr_t)loadaddr + REL_ADDEND))();
#else /* APPLY_RELA */
			*(u64 *)reladdr = (*(Elf64_Addr(*)(void))((uintptr_t)*(u64 *)reladdr + (uintptr_t)loadaddr))();
#endif /* !APPLY_RELA */
			break;
#endif /* R_USED_RELATIVE64 */


#ifdef R_USED_SIZE32
		case R_USED_SIZE32:
#undef R_USED_SIZE32
		{
			size_t symbol_size;
			driver_find_symbol_for_relocation(self,
			                                  ELF_R_SYM(rel.r_info),
			                                  &symbol_size,
			                                  NULL,
			                                  reloc_flags);
			*(u32 *)reladdr SET_OR_INPLACE_ADD (u32)(symbol_size + REL_ADDEND);
		}	break;
#endif /* R_USED_SIZE32 */


#ifdef R_USED_SIZE64
		case R_USED_SIZE64:
#undef R_USED_SIZE64
		{
			size_t symbol_size;
			driver_find_symbol_for_relocation(self,
			                                  ELF_R_SYM(rel.r_info),
			                                  &symbol_size,
			                                  NULL,
			                                  reloc_flags);
			*(u64 *)reladdr SET_OR_INPLACE_ADD (u64)(symbol_size + REL_ADDEND);
		}	break;
#endif /* R_USED_SIZE64 */


#ifdef R_USED_NONE
		case R_USED_NONE:
#undef R_USED_NONE
			break;
#endif /* R_USED_COPY */


#ifdef R_USED_COPY
		case R_USED_COPY:
#undef R_USED_COPY
		{
			Elf_Sym const *dst_sym;
			size_t src_size;
			struct driver *src_module;
			dst_sym = self->d_dynsym_tab + ELF_R_SYM(rel.r_info);
			value = (Elf_Addr)driver_find_symbol_for_relocation(self,
			                                                    ELF_R_SYM(rel.r_info),
			                                                    &src_size,
			                                                    &src_module,
                                                                reloc_flags);
			if unlikely(dst_sym->st_size != src_size) {
				printk(KERN_WARNING "%q: Symbol %q imported with %Iu bytes, but exported with %Iu from %q\n",
				       self->d_name, self->d_dynstr + dst_sym->st_name,
				       dst_sym->st_info, src_size, src_module->d_filename);
			}
			if unlikely(src_size > dst_sym->st_size)
				src_size = dst_sym->st_size;
			memcpy((void *)reladdr, (void *)value, src_size);
		}	break;
#endif /* R_USED_COPY */


#ifdef R_USED_8
		case R_USED_8:
#undef R_USED_8
			LOOKUP_SYMBOL();
			*(u8 *)reladdr SET_OR_INPLACE_ADD (u8)(value + REL_ADDEND);
			break;
#endif /* R_USED_8 */


#ifdef R_USED_PC8
		case R_USED_PC8:
#undef R_USED_PC8
			LOOKUP_SYMBOL();
			*(u8 *)reladdr SET_OR_INPLACE_ADD (u8)((value + REL_ADDEND) - (uintptr_t)reladdr);
			break;
#endif /* R_USED_PC8 */


#ifdef R_USED_16
		case R_USED_16:
#undef R_USED_16
			LOOKUP_SYMBOL();
			*(u16 *)reladdr SET_OR_INPLACE_ADD (u16)(value + REL_ADDEND);
			break;
#endif /* R_USED_16 */


#ifdef R_USED_PC16
		case R_USED_PC16:
#undef R_USED_PC16
			LOOKUP_SYMBOL();
			*(u16 *)reladdr SET_OR_INPLACE_ADD (u16)((value + REL_ADDEND) - (uintptr_t)reladdr);
			break;
#endif /* R_USED_PC16 */


#if defined(R_USED_32) || defined(R_USED_32_ALT)
#ifdef R_USED_32
		case R_USED_32:
#undef R_USED_32
#endif /* R_USED_32 */
#ifdef R_USED_32_ALT
		case R_USED_32_ALT:
#undef R_USED_32_ALT
#endif /* R_USED_32_ALT */
			LOOKUP_SYMBOL();
			*(u32 *)reladdr SET_OR_INPLACE_ADD (u32)(value + REL_ADDEND);
			break;
#endif /* R_USED_32 || R_USED_32_ALT */


#ifdef R_USED_PC32
		case R_USED_PC32:
#undef R_USED_PC32
			LOOKUP_SYMBOL();
			*(u32 *)reladdr SET_OR_INPLACE_ADD (u32)((value + REL_ADDEND) - (uintptr_t)reladdr);
			break;
#endif /* R_USED_PC32 */


#ifdef R_USED_64
		case R_USED_64:
#undef R_USED_64
			LOOKUP_SYMBOL();
			*(u64 *)reladdr SET_OR_INPLACE_ADD (u64)(value + REL_ADDEND);
			break;
#endif /* R_USED_64 */


#ifdef R_USED_PC64
		case R_USED_PC64:
#undef R_USED_PC64
			LOOKUP_SYMBOL();
			*(u64 *)reladdr SET_OR_INPLACE_ADD (u64)((value + REL_ADDEND) - (uintptr_t)reladdr);
			break;
#endif /* R_USED_PC64 */


#if defined(R_USED_GLOB_DAT) || defined(R_USED_JMP_SLOT)
#ifdef R_USED_JMP_SLOT
		case R_USED_JMP_SLOT:
#undef R_USED_JMP_SLOT
#endif /* R_USED_JMP_SLOT */
#ifdef R_USED_GLOB_DAT
		case R_USED_GLOB_DAT:
#undef R_USED_GLOB_DAT
#endif /* R_USED_GLOB_DAT */
			LOOKUP_SYMBOL();
			*(u32 *)reladdr SET_OR_INPLACE_ADD (u32)(value + REL_ADDEND);
			break;
#endif /* R_USED_GLOB_DAT || R_USED_JMP_SLOT */



		default:
			printk(KERN_WARNING "%q: Relocation #%Iu has unknown type type %u (%#x)\n",
			       self->d_name, (size_t)i,
			       (unsigned int)ELF_R_TYPE(rel.r_info),
			       (unsigned int)ELF_R_TYPE(rel.r_info));
			break;
		}
#undef REL_ADDEND
	}
}


DECL_END

#undef SET_OR_INPLACE_ADD
#undef APPLY_RELA
