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
#ifdef __INTELLISENSE__
#include "module-reloc.c"

#define DEFINE_DlModule_ApplyRelocations
//#define DEFINE_DlModule_ApplyRelocationsWithAddend
#endif /* __INTELLISENSE__ */

DECL_BEGIN

/* Apply relocations for `self'
 * @param: flags: Set of `DL_MODULE_INITIALIZE_F*' */
#ifdef DEFINE_DlModule_ApplyRelocationsWithAddend
INTERN WUNUSED NONNULL((1)) int CC
DlModule_ApplyRelocationsWithAddend(DlModule *__restrict self,
                                    ElfW(Rela) const *__restrict vector,
                                    size_t count, unsigned int flags)
		THROWS(...)
#define LOCAL_HAVE_ADDENDS 1
#elif defined(DEFINE_DlModule_ApplyRelocations)
INTERN WUNUSED NONNULL((1)) int CC
DlModule_ApplyRelocations(DlModule *__restrict self,
                          ElfW(Rel) const *__restrict vector,
                          size_t count, unsigned int flags)
		THROWS(...)
#undef LOCAL_HAVE_ADDENDS
#else /* ... */
#error "Invalid configuration"
#endif /* !... */
{
#ifdef LOCAL_HAVE_ADDENDS
#define LOCAL_setoradd =
#define LOCAL_IE_ADDENDS(if_rel, if_rela) if_rela
#else /* LOCAL_HAVE_ADDENDS */
#define LOCAL_setoradd +=
#define LOCAL_IE_ADDENDS(if_rel, if_rela) if_rel
#endif /* !LOCAL_HAVE_ADDENDS */
	size_t i;
	ElfW(Addr) value;
	uintptr_t loadaddr = self->dm_loadaddr;
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
#define LOOKUP_SYMBOL()                                                    \
		if unlikely(!DlModule_ElfFindSymbol(self, ELFW(R_SYM)(rel.r_info), \
		                                    &value, NULL, NULL))           \
			goto err

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
		ELF_ARCH_CASE_R_SIZE32: {
			size_t symbol_size;
			if unlikely(!DlModule_ElfFindSymbol(self, ELFW(R_SYM)(rel.r_info),
			                                    &value, &symbol_size, NULL))
				goto err;
			*(u32 *)reladdr LOCAL_setoradd (u32)(symbol_size + LOCAL_addend);
		}	break;
#endif /* ELF_ARCH_CASE_R_SIZE32 */


#ifdef ELF_ARCH_CASE_R_SIZE64
		ELF_ARCH_CASE_R_SIZE64: {
			size_t symbol_size;
			if unlikely(!DlModule_ElfFindSymbol(self, ELFW(R_SYM)(rel.r_info),
			                                    &value, &symbol_size, NULL))
				goto err;
			*(u64 *)reladdr LOCAL_setoradd (u64)(symbol_size + LOCAL_addend);
		}	break;
#endif /* ELF_ARCH_CASE_R_SIZE64 */


#ifdef ELF_ARCH_CASE_R_COPY
		ELF_ARCH_CASE_R_COPY: {
			ElfW(Sym) const *dst_sym;
			size_t src_size;
			DlModule *src_module;
			dst_sym = self->dm_elf.de_dynsym_tab + ELFW(R_SYM)(rel.r_info);
			if unlikely(!DlModule_ElfFindSymbol(self,
			                                    ELFW(R_SYM)(rel.r_info),
			                                    &value,
			                                    &src_size,
			                                    &src_module))
				goto err;
			if unlikely(dst_sym->st_size != src_size) {
				/* Special  handling  for  symbols  exported   by  the  RTLD  module   itself.
				 * Since builtin symbols don't have size information associated with themself,
				 * we ignore import sizes and solely  rely on whatever the hosted  application
				 * is telling us to be expecting. */
				if (src_size == 0 && src_module == &dl_rtld_module) {
					src_size = dst_sym->st_size;
				} else {
					syslog(LOG_WARN, "[rtld] %q: Symbol %q imported with %" PRIuSIZ " "
					                 "bytes, but exported with %" PRIuSIZ " from %q\n",
					       self->dm_filename, self->dm_elf.de_dynstr + dst_sym->st_name,
					       dst_sym->st_size, src_size, src_module->dm_filename);
					/* NOTE: When `src_size' is  ZERO(0), then always  copy the size  information
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
#endif /* ELF_ARCH_CASE_R_COPY */


#if defined(ELF_ARCH_CASE_R_8) || defined(ELF_ARCH_CASE_R_8S)
#ifdef ELF_ARCH_CASE_R_8
		ELF_ARCH_CASE_R_8:
#endif /* ELF_ARCH_CASE_R_8 */
#ifdef ELF_ARCH_CASE_R_8S
		ELF_ARCH_CASE_R_8S:
#endif /* ELF_ARCH_CASE_R_8S */
			LOOKUP_SYMBOL();
			*(u8 *)reladdr LOCAL_setoradd (u8)(value + LOCAL_addend);
			break;
#endif /* ELF_ARCH_CASE_R_8 || ELF_ARCH_CASE_R_8S */


#ifdef ELF_ARCH_CASE_R_PC8
		ELF_ARCH_CASE_R_PC8:
			LOOKUP_SYMBOL();
			*(u8 *)reladdr LOCAL_setoradd (u8)((value + LOCAL_addend) - (uintptr_t)reladdr);
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
			*(u16 *)reladdr LOCAL_setoradd (u16)(value + LOCAL_addend);
			break;
#endif /* ELF_ARCH_CASE_R_16 || ELF_ARCH_CASE_R_16S */


#ifdef ELF_ARCH_CASE_R_PC16
		ELF_ARCH_CASE_R_PC16:
			LOOKUP_SYMBOL();
			*(u16 *)reladdr LOCAL_setoradd (u16)((value + LOCAL_addend) - (uintptr_t)reladdr);
			break;
#endif /* ELF_ARCH_CASE_R_PC16 */


#if defined(ELF_ARCH_CASE_R_32) || defined(ELF_ARCH_CASE_R_32S) || \
    defined(ELF_ARCH_CASE_R_DTPOFF32)
#ifdef ELF_ARCH_CASE_R_32
		ELF_ARCH_CASE_R_32:
#endif /* ELF_ARCH_CASE_R_32 */
#ifdef ELF_ARCH_CASE_R_32S
		ELF_ARCH_CASE_R_32S:
#endif /* ELF_ARCH_CASE_R_32S */
#ifdef ELF_ARCH_CASE_R_DTPOFF32
		ELF_ARCH_CASE_R_DTPOFF32:
#endif /* ELF_ARCH_CASE_R_DTPOFF32 */
			LOOKUP_SYMBOL();
			*(u32 *)reladdr LOCAL_setoradd (u32)(value + LOCAL_addend);
			break;
#endif /* ELF_ARCH_CASE_R_32 || ELF_ARCH_CASE_R_32S || ELF_ARCH_CASE_R_DTPOFF32 */


#ifdef ELF_ARCH_CASE_R_PC32
		ELF_ARCH_CASE_R_PC32:
			LOOKUP_SYMBOL();
			*(u32 *)reladdr LOCAL_setoradd (u32)((value + LOCAL_addend) - (uintptr_t)reladdr);
			break;
#endif /* ELF_ARCH_CASE_R_PC32 */


#if defined(ELF_ARCH_CASE_R_64) || defined(ELF_ARCH_CASE_R_DTPOFF64)
#ifdef ELF_ARCH_CASE_R_64
		ELF_ARCH_CASE_R_64:
#endif /* ELF_ARCH_CASE_R_64 */
#ifdef ELF_ARCH_CASE_R_DTPOFF64
		ELF_ARCH_CASE_R_DTPOFF64:
#endif /* ELF_ARCH_CASE_R_DTPOFF64 */
			LOOKUP_SYMBOL();
			*(u64 *)reladdr LOCAL_setoradd (u64)(value + LOCAL_addend);
			break;
#endif /* ELF_ARCH_CASE_R_64 || ELF_ARCH_CASE_R_DTPOFF64 */


#ifdef ELF_ARCH_CASE_R_PC64
		ELF_ARCH_CASE_R_PC64:
			LOOKUP_SYMBOL();
			*(u64 *)reladdr LOCAL_setoradd (u64)((value + LOCAL_addend) - (uintptr_t)reladdr);
			break;
#endif /* ELF_ARCH_CASE_R_PC64 */


#ifdef ELF_ARCH_CASE_R_JMP_SLOT
		ELF_ARCH_CASE_R_JMP_SLOT:
			if (!(flags & DL_MODULE_ELF_INITIALIZE_FBINDNOW)) {
				/* Lazy binding. */
				*(uintptr_t *)reladdr += loadaddr;
				break;
			}
			LOOKUP_SYMBOL();
			*(uintptr_t *)reladdr = (uintptr_t)(value + LOCAL_addend);
			break;
#endif /* ELF_ARCH_CASE_R_JMP_SLOT */


#ifdef ELF_ARCH_CASE_R_GLOB_DAT
		ELF_ARCH_CASE_R_GLOB_DAT:
			LOOKUP_SYMBOL();
			*(uintptr_t *)reladdr LOCAL_setoradd (uintptr_t)(value + LOCAL_addend);
			break;
#endif /* ELF_ARCH_CASE_R_GLOB_DAT */


#ifdef ELF_ARCH_CASE_R_DTPMOD32
		ELF_ARCH_CASE_R_DTPMOD32:
			/* ID of module containing this relocation */
			*(u32 *)reladdr LOCAL_setoradd (u32)((uintptr_t)self + LOCAL_addend);
			break;
#endif /* ELF_ARCH_CASE_R_DTPMOD32 */


#ifdef ELF_ARCH_CASE_R_DTPMOD64
		ELF_ARCH_CASE_R_DTPMOD64:
			/* ID of module containing this relocation */
			*(u64 *)reladdr LOCAL_setoradd (u64)((uintptr_t)self + LOCAL_addend);
			break;
#endif /* ELF_ARCH_CASE_R_DTPMOD64 */


#ifdef ELF_ARCH_CASE_R_NEG_TPOFF32
#ifndef ELF_ARCH_NAME_R_NEG_TPOFF32
#define ELF_ARCH_NAME_R_NEG_TPOFF32 "R_" ELF_EMNAME(ELF_ARCH_MACHINE) "_NEG_TPOFF32"
#endif /* !ELF_ARCH_NAME_R_NEG_TPOFF32 */
		ELF_ARCH_CASE_R_NEG_TPOFF32: {
			DlModule *tls_module;
			/* Negated offset in static TLS block */
			if unlikely(!DlModule_ElfFindSymbol(self, ELFW(R_SYM)(rel.r_info),
			                                    &value, NULL, &tls_module))
				goto err;
			/* NOTE: `dm_tlsstoff' is negative, `sym.ds_symval' is positive.
			 *        This relocation is applied to `movl %gs:symbol, %eax' (386)
			 *        or  `movq %fs:symbol, %rax'  (x86_64), so  we need  to have
			 *       `symbol' evaluate to its position within the static TLS segment. */
			if unlikely(tls_module->dm_tlsstoff == 0) {
				/* Symbol points to a module that isn't apart of the static TLS segment.
				 * -> This relocation can _only_ be used for static TLS symbols. */
				dl_seterrorf("%q: Cannot apply `" ELF_ARCH_NAME_R_NEG_TPOFF32 "' to %q stored in the dynamic TLS segment of %q",
				             self->dm_filename,
				             self->dm_elf.de_dynstr +
				             self->dm_elf.de_dynsym_tab[ELFW(R_SYM)(rel.r_info)].st_name,
				             tls_module->dm_filename);
				goto err;
			}
			*(s32 *)reladdr LOCAL_setoradd (s32)-(tls_module->dm_tlsstoff + (value + LOCAL_addend));
		}	break;
#endif /* ELF_ARCH_CASE_R_NEG_TPOFF32 */

#ifdef ELF_ARCH_CASE_R_NEG_TPOFF64
#ifndef ELF_ARCH_NAME_R_NEG_TPOFF64
#define ELF_ARCH_NAME_R_NEG_TPOFF64 "R_" ELF_EMNAME(ELF_ARCH_MACHINE) "_NEG_TPOFF64"
#endif /* !ELF_ARCH_NAME_R_NEG_TPOFF64 */
		ELF_ARCH_CASE_R_NEG_TPOFF64: {
			DlModule *tls_module;
			/* Negated offset in static TLS block */
			if unlikely(!DlModule_ElfFindSymbol(self, ELFW(R_SYM)(rel.r_info),
			                                    &value, NULL, &tls_module))
				goto err;
			/* NOTE: `dm_tlsstoff' is negative, `sym.ds_symval' is positive.
			 *        This relocation is applied to `movl %gs:symbol, %eax' (386)
			 *        or  `movq %fs:symbol, %rax'  (x86_64), so  we need  to have
			 *       `symbol' evaluate to its position within the static TLS segment. */
			if unlikely(tls_module->dm_tlsstoff == 0) {
				/* Symbol points to a module that isn't apart of the static TLS segment.
				 * -> This relocation can _only_ be used for static TLS symbols. */
				dl_seterrorf("%q: Cannot apply `" ELF_ARCH_NAME_R_NEG_TPOFF64 "' to %q stored in the dynamic TLS segment of %q",
				             self->dm_filename,
				             self->dm_elf.de_dynstr +
				             self->dm_elf.de_dynsym_tab[ELFW(R_SYM)(rel.r_info)].st_name,
				             tls_module->dm_filename);
				goto err;
			}
			*(s64 *)reladdr LOCAL_setoradd (s64)-(tls_module->dm_tlsstoff + (value + LOCAL_addend));
		}	break;
#endif /* ELF_ARCH_CASE_R_NEG_TPOFF64 */

#ifdef ELF_ARCH_CASE_R_TPOFF32
#ifndef ELF_ARCH_NAME_R_TPOFF32
#define ELF_ARCH_NAME_R_TPOFF32 "R_" ELF_EMNAME(ELF_ARCH_MACHINE) "_TPOFF32"
#endif /* !ELF_ARCH_NAME_R_TPOFF32 */
		ELF_ARCH_CASE_R_TPOFF32: {
			DlModule *tls_module;
			/* Offset in static TLS block */
			if unlikely(!DlModule_ElfFindSymbol(self, ELFW(R_SYM)(rel.r_info),
			                                    &value, NULL, &tls_module))
				goto err;
			if unlikely(tls_module->dm_tlsstoff == 0) {
				dl_seterrorf("%q: Cannot apply `" ELF_ARCH_NAME_R_TPOFF32 "' to %q stored in the dynamic TLS segment of %q",
				             self->dm_filename,
				             self->dm_elf.de_dynstr +
				             self->dm_elf.de_dynsym_tab[ELFW(R_SYM)(rel.r_info)].st_name,
				             tls_module->dm_filename);
				goto err;
			}
			*(s32 *)reladdr LOCAL_setoradd (tls_module->dm_tlsstoff + (value + LOCAL_addend));
		}	break;
#endif /* ELF_ARCH_CASE_R_TPOFF32 */

#ifdef ELF_ARCH_CASE_R_TPOFF64
#ifndef ELF_ARCH_NAME_R_TPOFF64
#define ELF_ARCH_NAME_R_TPOFF64 "R_" ELF_EMNAME(ELF_ARCH_MACHINE) "_TPOFF64"
#endif /* !ELF_ARCH_NAME_R_TPOFF64 */
		ELF_ARCH_CASE_R_TPOFF64: {
			DlModule *tls_module;
			/* Offset in static TLS block */
			if unlikely(!DlModule_ElfFindSymbol(self, ELFW(R_SYM)(rel.r_info),
			                                    &value, NULL, &tls_module))
				goto err;
			if unlikely(tls_module->dm_tlsstoff == 0) {
				dl_seterrorf("%q: Cannot apply `" ELF_ARCH_NAME_R_TPOFF64 "' to %q stored in the dynamic TLS segment of %q",
				             self->dm_filename,
				             self->dm_elf.de_dynstr +
				             self->dm_elf.de_dynsym_tab[ELFW(R_SYM)(rel.r_info)].st_name,
				             tls_module->dm_filename);
				goto err;
			}
			*(s64 *)reladdr LOCAL_setoradd (tls_module->dm_tlsstoff + (value + LOCAL_addend));
		}	break;
#endif /* ELF_ARCH_CASE_R_TPOFF64 */



#if 0
#ifdef ELF_ARCH_CASE_R_TLSDESC
		ELF_ARCH_CASE_R_TLSDESC: {
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
#endif /* ELF_ARCH_CASE_R_TLSDESC */
#endif


		default:
			syslog(LOG_WARN, "[rtld] %q: Relocation #%" PRIuSIZ " at %p ("
			                 "%#" PRIxPTR "+%#" PRIxN(__SIZEOF_ELFW(ADDR__)) ") "
			                 "has unknown type %u (%#x)"
#ifdef LOCAL_HAVE_ADDENDS
			                 " [addend=%s%#" PRIxPTR "]"
#endif /* LOCAL_HAVE_ADDENDS */
			                 "\n",
			       self->dm_filename,
			       (size_t)i, reladdr, loadaddr, rel.r_offset,
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
	return 0;
err:
	return -1;
#undef LOCAL_IE_ADDENDS
#undef LOCAL_setoradd
}
#undef LOCAL_HAVE_ADDENDS

DECL_END

#undef DEFINE_DlModule_ApplyRelocations
#undef DEFINE_DlModule_ApplyRelocationsWithAddend
