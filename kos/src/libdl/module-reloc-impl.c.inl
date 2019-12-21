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
#include "module-reloc.c"

#define APPLY_RELA 1
#endif /* __INTELLISENSE__ */

DECL_BEGIN

#ifdef APPLY_RELA
#define SET_OR_INPLACE_ADD =
#else /* APPLY_RELA */
#define SET_OR_INPLACE_ADD +=
#endif /* !APPLY_RELA */

/* Apply relocations for `self'
 * @param: flags: Set of `DL_MODULE_INITIALIZE_F*' */
#ifdef APPLY_RELA
INTERN int CC
DlModule_ApplyRelocationsWithAddend(DlModule *__restrict self,
                                    ElfW(Rela) *__restrict vector,
                                    size_t count,
                                    unsigned int flags)
#else /* APPLY_RELA */
INTERN int CC
DlModule_ApplyRelocations(DlModule *__restrict self,
                          ElfW(Rel) *__restrict vector,
                          size_t count,
                          unsigned int flags)
#endif /* !APPLY_RELA */
{
	size_t i;
	ElfW(Addr) value;
	byte_t *loadaddr = (byte_t *)self->dm_loadaddr;
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
#define LOOKUP_SYMBOL() \
		if unlikely(!DlModule_FindSymbol(self, ELFW(R_SYM)(rel.r_info), &value, NULL, NULL)) \
			goto err

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
#if __SIZEOF_POINTER__ == 4
#define R_USED_RELATIVE32     R_X86_64_RELATIVE
#else /* __SIZEOF_POINTER__ == 4 */
#define R_USED_RELATIVE64_ALT R_X86_64_RELATIVE
#endif /* __SIZEOF_POINTER__ != 4 */
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
#define R_USED_RELATIVE32  R_386_RELATIVE
#define R_USED_IRELATIVE64 R_386_IRELATIVE
#else
#error "Unsupported architecture"
#endif


#ifdef R_USED_RELATIVE32
		case R_USED_RELATIVE32:
#undef R_USED_RELATIVE32
			*(u32 *)reladdr SET_OR_INPLACE_ADD (u32)(uintptr_t)loadaddr;
			break;
#endif /* R_USED_RELATIVE32 */


#if defined(R_USED_RELATIVE64) || defined(R_USED_RELATIVE64_ALT)
#ifdef R_USED_RELATIVE64
		case R_USED_RELATIVE64:
#undef R_USED_RELATIVE64
#endif /* R_USED_RELATIVE64 */
#ifdef R_USED_RELATIVE64_ALT
		case R_USED_RELATIVE64_ALT:
#undef R_USED_RELATIVE64_ALT
#endif /* R_USED_RELATIVE64_ALT */
			*(u64 *)reladdr SET_OR_INPLACE_ADD (u64)(uintptr_t)(loadaddr + REL_ADDEND);
			break;
#endif /* R_USED_RELATIVE64 || R_USED_RELATIVE64_ALT */


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
			if unlikely(!DlModule_FindSymbol(self, ELFW(R_SYM)(rel.r_info),
			                                 &symbol_size, NULL, NULL))
				goto err;
			*(u32 *)reladdr SET_OR_INPLACE_ADD (u32)(symbol_size + REL_ADDEND);
		}	break;
#endif /* R_USED_SIZE32 */


#ifdef R_USED_SIZE64
		case R_USED_SIZE64:
#undef R_USED_SIZE64
		{
			size_t symbol_size;
			if unlikely(!DlModule_FindSymbol(self, ELFW(R_SYM)(rel.r_info),
			                                 &symbol_size, NULL, NULL))
				goto err;
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
			ElfW(Sym) *dst_sym;
			ElfW(Word) src_size;
			DlModule *src_module;
			dst_sym = self->dm_dynsym_tab + ELFW(R_SYM)(rel.r_info);
			if unlikely(!DlModule_FindSymbol(self,
			                                 ELFW(R_SYM)(rel.r_info),
			                                 &value,
			                                 &src_size,
			                                 &src_module))
				goto err;
			if unlikely(dst_sym->st_size != src_size) {
				/* Special handling for symbols exported by the RTLD module itself.
				 * Since builtin symbols don't have size information associated with themself,
				 * we ignore import sizes and solely rely on whatever the hosted application
				 * is telling us to be expecting. */
				if (src_size == 0 && src_module == &ld_rtld_module)
					src_size = dst_sym->st_size;
				else {
					syslog(LOG_WARN, "%q: Symbol %q imported with %Iu bytes, but exported with %Iu from %q\n",
					       self->dm_filename, self->dm_dynstr + dst_sym->st_name,
					       dst_sym->st_info, src_size, src_module->dm_filename);
					/* NOTE: When `src_size' is ZERO(0), then always copy the size information
					 *       that is expected by the hosted module (though still emit the warning
					 *       in this case) */
					if (!src_size || src_size > dst_sym->st_size)
						src_size = dst_sym->st_size;
				}
			}
			memcpy((void *)reladdr,
			       (void *)value,
			       src_size);
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


#ifdef R_JMP_SLOT
		case R_JMP_SLOT:
			if (!(flags & DL_MODULE_INITIALIZE_FBINDNOW)) {
				/* Lazy binding. */
				*(uintptr_t *)reladdr += (uintptr_t)loadaddr;
				break;
			}
			LOOKUP_SYMBOL();
			*(uintptr_t *)reladdr = (uintptr_t)(value + REL_ADDEND);
			break;
//#undef R_JMP_SLOT /* Don't undef this one! */
#endif /* R_JMP_SLOT */

#ifdef R_USED_GLOB_DAT
		case R_USED_GLOB_DAT:
			LOOKUP_SYMBOL();
			*(uintptr_t *)reladdr SET_OR_INPLACE_ADD (uintptr_t)(value + REL_ADDEND);
			break;
#undef R_USED_GLOB_DAT
#endif /* R_USED_GLOB_DAT */




#if defined(__x86_64__)

			/* TODO */
		case R_X86_64_DTPMOD64:
		case R_X86_64_DTPOFF64:
		case R_X86_64_TPOFF64:
		case R_X86_64_DTPOFF32:
		case R_X86_64_TPOFF32:
		case R_X86_64_TLSDESC:

#elif defined(__i386__)

		case R_386_TLS_DTPMOD32:
			/* ID of module containing this relocation */
			*(u32 *)reladdr SET_OR_INPLACE_ADD (u32)(self + REL_ADDEND);
			break;

		case R_386_TLS_DTPOFF32:
			/* Offset in TLS block */
			LOOKUP_SYMBOL();
			*(u32 *)reladdr SET_OR_INPLACE_ADD (u32)(value + REL_ADDEND);
			break;

		case R_386_TLS_TPOFF32: {
			DlModule *tls_module;
			/* Negated offset in static TLS block */
			if unlikely(!DlModule_FindSymbol(self, ELFW(R_SYM)(rel.r_info),
			                                 &value,
			                                 NULL,
			                                 &tls_module))
				goto err;
			/* NOTE: `dm_tlsstoff' is negative, `sym.ds_symval' is positive.
			 *        This relocation is applied to `movl %gs:symbol, %eax' (386)
			 *        or `movq %fs:symbol, %rax' (x86_64), so we need to have
			 *       `symbol' evaluate to its position within the static TLS segment. */
			if unlikely(tls_module->dm_tlsstoff == 0) {
				/* Symbol points to a module that isn't apart of the static TLS segment.
				 * -> This relocation can _only_ be used for static TLS symbols. */
				elf_setdlerrorf("%q: Cannot apply `R_386_TLS_TPOFF32' to %q stored in the dynamic TLS segment of %q",
				                self->dm_filename,
				                self->dm_dynstr + self->dm_dynsym_tab[ELFW(R_SYM)(rel.r_info)].st_name,
				                tls_module->dm_filename);
				goto err;
			}
			*(s32 *)reladdr SET_OR_INPLACE_ADD -(tls_module->dm_tlsstoff + (value + REL_ADDEND));
		}	break;

		case R_386_TLS_TPOFF: {
			DlModule *tls_module;
			/* Offset in static TLS block */
			if unlikely(!DlModule_FindSymbol(self, ELFW(R_SYM)(rel.r_info),
			                                 &value,
			                                 NULL,
			                                 &tls_module))
				goto err;
			if unlikely(tls_module->dm_tlsstoff == 0) {
				elf_setdlerrorf("%q: Cannot apply `R_386_TLS_TPOFF' to %q stored in the dynamic TLS segment of %q",
				                self->dm_filename,
				                self->dm_dynstr + self->dm_dynsym_tab[ELFW(R_SYM)(rel.r_info)].st_name,
				                tls_module->dm_filename);
				goto err;
			}
			*(s32 *)reladdr SET_OR_INPLACE_ADD (tls_module->dm_tlsstoff + (value + REL_ADDEND));
		}	break;

#if 0
		case R_386_TLS_DESC: {
			struct tlsdesc;
			typedef ptrdiff_t (__attribute__((regparm(1))) *PTLSDESC_ENTRY)(struct tlsdesc * self);
			struct tlsdesc {
				PTLSDESC_ENTRY td_entry; /*  */
				void          *td_arg;
			};
			struct tlsdesc *desc;
			desc = (struct tlsdesc *)reladdr;
			/* ??? I don't get it... */
		}	break;
#endif

#else
#error "Unsupported architecture"
#endif

		default:
			syslog(LOG_WARN, "%q: Relocation #%Iu has unknown type type %u (%#x)\n",
			       self->dm_filename,
			       (size_t)i,
			       (unsigned int)ELFW(R_TYPE)(rel.r_info),
			       (unsigned int)ELFW(R_TYPE)(rel.r_info));
			break;
		}
#undef REL_ADDEND
	}
	return 0;
err:
	return -1;
}

DECL_END

#undef SET_OR_INPLACE_ADD
#undef APPLY_RELA
