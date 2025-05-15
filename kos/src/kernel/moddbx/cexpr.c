/*[[[magic
local cflags = options.get("COMPILE.cflags");
for (local o: { "-mno-sse", "-mno-sse2", "-mno-sse3", "-mno-sse4", "-mno-ssse3", "-mno-mmx", "-mno-3dnow", "-mno-avx" })
	cflags.remove(o);
]]]*/
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
#ifndef GUARD_MODDBX_CEXPR_C
#define GUARD_MODDBX_CEXPR_C 1
#define _KOS_SOURCE 1
#define __HAVE_FPU 1 /* Enable FPU access */

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER

#include <debugger/rt.h>
#include <kernel/fs/dirent.h>
#include <kernel/mman.h>
#include <kernel/mman/driver.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/module.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <sched/pertask.h>
#include <sched/task.h>

#include <hybrid/byteorder.h>
#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <asm/isa.h>
#include <asm/registers.h>
#include <compat/config.h>
#include <kos/except.h>
#include <kos/exec/module.h>
#include <kos/exec/rtld.h>
#include <kos/types.h>

#include <alloca.h>
#include <assert.h>
#include <elf.h>
#include <ieee754.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <libcpustate/register.h>
#include <libdebuginfo/debug_info.h>
#include <libdebuginfo/dwarf.h>
#include <libunwind/cfi.h>
#include <libunwind/errno.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/exec/rtld.h>
#include <compat/kos/types.h>

#include <libunwind/register.h> /* unwind_getreg_compat() */
#endif /* __ARCH_HAVE_COMPAT */

/**/
#include "include/cexpr.h"
#include "include/cmodule.h"
#include "include/cparser.h"
#include "include/ctype.h"
#include "include/error.h"
#include "include/malloc.h"

DECL_BEGIN


#define _GETFLOAT(T, addr, Tresult, result, handle_fault)     \
	do {                                                      \
		T _temp;                                              \
		if (dbg_readmemory(addr, &_temp, sizeof(_temp)) != 0) \
			handle_fault;                                     \
		(result) = (Tresult)_temp;                            \
	}	__WHILE0
#define _SETFLOAT(T, addr, value, handle_fault)                                  \
	do {                                                                         \
		T _temp = (T)(value);                                                    \
		if (dbg_writememory(addr, &_temp, sizeof(_temp), cexpr_forcewrite) != 0) \
			handle_fault;                                                        \
	}	__WHILE0

#define _GETFLOAT_NOFAULT(T, addr, Tresult, result) \
	do {                                            \
		T _temp;                                    \
		memcpy(&_temp, addr, sizeof(_temp));        \
		(result) = (Tresult)_temp;                  \
	}	__WHILE0
#define _SETFLOAT_NOFAULT(T, addr, value)                      \
	do {                                                       \
		T _temp = (T)(value);                                  \
		memcpy(addr, &_temp, sizeof(_temp), cexpr_forcewrite); \
	}	__WHILE0

#define GETFLOAT_IEEE754_FLOAT(addr, Tresult, result, handle_fault)       _GETFLOAT(__IEEE754_FLOAT_TYPE__, addr, Tresult, result, handle_fault)
#define SETFLOAT_IEEE754_FLOAT(addr, value, handle_fault)                 _SETFLOAT(__IEEE754_FLOAT_TYPE__, addr, value, handle_fault)
#define GETFLOAT_IEEE754_DOUBLE(addr, Tresult, result, handle_fault)      _GETFLOAT(__IEEE754_DOUBLE_TYPE__, addr, Tresult, result, handle_fault)
#define SETFLOAT_IEEE754_DOUBLE(addr, value, handle_fault)                _SETFLOAT(__IEEE754_DOUBLE_TYPE__, addr, value, handle_fault)
#define GETFLOAT_IEEE854_LONG_DOUBLE(addr, Tresult, result, handle_fault) _GETFLOAT(__IEEE854_LONG_DOUBLE_TYPE__, addr, Tresult, result, handle_fault)
#define SETFLOAT_IEEE854_LONG_DOUBLE(addr, value, handle_fault)           _SETFLOAT(__IEEE854_LONG_DOUBLE_TYPE__, addr, value, handle_fault)

#define GETFLOAT_IEEE754_FLOAT_NOFAULT(addr, Tresult, result)       _GETFLOAT_NOFAULT(__IEEE754_FLOAT_TYPE__, addr, Tresult, result)
#define SETFLOAT_IEEE754_FLOAT_NOFAULT(addr, value)                 _SETFLOAT_NOFAULT(__IEEE754_FLOAT_TYPE__, addr, value)
#define GETFLOAT_IEEE754_DOUBLE_NOFAULT(addr, Tresult, result)      _GETFLOAT_NOFAULT(__IEEE754_DOUBLE_TYPE__, addr, Tresult, result)
#define SETFLOAT_IEEE754_DOUBLE_NOFAULT(addr, value)                _SETFLOAT_NOFAULT(__IEEE754_DOUBLE_TYPE__, addr, value)
#define GETFLOAT_IEEE854_LONG_DOUBLE_NOFAULT(addr, Tresult, result) _GETFLOAT_NOFAULT(__IEEE854_LONG_DOUBLE_TYPE__, addr, Tresult, result)
#define SETFLOAT_IEEE854_LONG_DOUBLE_NOFAULT(addr, value)           _SETFLOAT_NOFAULT(__IEEE854_LONG_DOUBLE_TYPE__, addr, value)

#ifdef CTYPE_KIND_IEEE854_LONG_DOUBLE
#define IF_HAVE_CTYPE_KIND_IEEE854_LONG_DOUBLE(...) __VA_ARGS__
#else /* CTYPE_KIND_IEEE854_LONG_DOUBLE */
#define IF_HAVE_CTYPE_KIND_IEEE854_LONG_DOUBLE(...) /* nothing */
#endif /* !CTYPE_KIND_IEEE854_LONG_DOUBLE */


#define GETFLOAT_BYKIND(kind, addr, Tresult, result, handle_bad_kind, handle_fault) \
	do {                                                                            \
		switch (kind) {                                                             \
		case CTYPE_KIND_IEEE754_FLOAT:                                              \
			GETFLOAT_IEEE754_FLOAT(addr, Tresult, result, handle_fault);            \
			break;                                                                  \
		case CTYPE_KIND_IEEE754_DOUBLE:                                             \
			GETFLOAT_IEEE754_DOUBLE(addr, Tresult, result, handle_fault);           \
			break;                                                                  \
		IF_HAVE_CTYPE_KIND_IEEE854_LONG_DOUBLE(                                     \
		case CTYPE_KIND_IEEE854_LONG_DOUBLE:                                        \
			GETFLOAT_IEEE854_LONG_DOUBLE(addr, Tresult, result, handle_fault);      \
			break);                                                                 \
		default: handle_bad_kind;                                                   \
		}                                                                           \
	}	__WHILE0

#define SETFLOAT_BYKIND(kind, addr, value, handle_bad_kind, handle_fault) \
	do {                                                                  \
		switch (kind) {                                                   \
		case CTYPE_KIND_IEEE754_FLOAT:                                    \
			SETFLOAT_IEEE754_FLOAT(addr, value, handle_fault);            \
			break;                                                        \
		case CTYPE_KIND_IEEE754_DOUBLE:                                   \
			SETFLOAT_IEEE754_DOUBLE(addr, value, handle_fault);           \
			break;                                                        \
		IF_HAVE_CTYPE_KIND_IEEE854_LONG_DOUBLE(                           \
		case CTYPE_KIND_IEEE854_LONG_DOUBLE:                              \
			SETFLOAT_IEEE854_LONG_DOUBLE(addr, value, handle_fault);      \
			break);                                                       \
		default: handle_bad_kind;                                         \
		}                                                                 \
	}	__WHILE0

#define GETFLOAT_BYKIND_NOFAULT(kind, addr, Tresult, result, handle_bad_kind) \
	do {                                                                      \
		switch (kind) {                                                       \
		case CTYPE_KIND_IEEE754_FLOAT:                                        \
			GETFLOAT_IEEE754_FLOAT_NOFAULT(addr, Tresult, result);            \
			break;                                                            \
		case CTYPE_KIND_IEEE754_DOUBLE:                                       \
			GETFLOAT_IEEE754_DOUBLE_NOFAULT(addr, Tresult, result);           \
			break;                                                            \
		IF_HAVE_CTYPE_KIND_IEEE854_LONG_DOUBLE(                               \
		case CTYPE_KIND_IEEE854_LONG_DOUBLE:                                  \
			GETFLOAT_IEEE854_LONG_DOUBLE_NOFAULT(addr, Tresult, result);      \
			break);                                                           \
		default: handle_bad_kind;                                             \
		}                                                                     \
	}	__WHILE0

#define SETFLOAT_BYKIND_NOFAULT(kind, addr, value, handle_bad_kind) \
	do {                                                            \
		switch (kind) {                                             \
		case CTYPE_KIND_IEEE754_FLOAT:                              \
			SETFLOAT_IEEE754_FLOAT_NOFAULT(addr, value);            \
			break;                                                  \
		case CTYPE_KIND_IEEE754_DOUBLE:                             \
			SETFLOAT_IEEE754_DOUBLE_NOFAULT(addr, value);           \
			break;                                                  \
		IF_HAVE_CTYPE_KIND_IEEE854_LONG_DOUBLE(                     \
		case CTYPE_KIND_IEEE854_LONG_DOUBLE:                        \
			SETFLOAT_IEEE854_LONG_DOUBLE_NOFAULT(addr, value);      \
			break);                                                 \
		default: handle_bad_kind;                                   \
		}                                                           \
	}	__WHILE0


/* [1..cexpr_stacksize] Stack of currently pushed C-values. (see the below API) */
PUBLIC struct cvalue *cexpr_stack        = NULL;
PUBLIC struct cvalue cexpr_stack_stub[1] = {};

/* # of used stack entries */
PUBLIC size_t cexpr_stacksize = 0;

/* When true, only allow read-only C expression operations.
 * During a debugger reset, this option is reset to `false' */
PUBLIC bool cexpr_readonly = false;

/* Don't calculate/keep track of C expression values, but
 * only simulate the effective expression type. - Used to
 * implement `typeof()' in C expressions, as well as  for
 * the  purpose of auto-completion of struct member names
 * and the like. */
PUBLIC bool cexpr_typeonly = false;

/* Set  to  true  if  memory  writes  should  be   forced.
 * This is the 4'th argument in calls to dbg_writememory()
 * Defaults to `false' */
PUBLIC bool cexpr_forcewrite = false;


/* Finalize the given C-value. */
PUBLIC NONNULL((1)) void
NOTHROW(FCALL cvalue_fini)(struct cvalue *__restrict self) {
	switch (self->cv_kind) {

	case CVALUE_KIND_DATA:
		dbx_free(self->cv_data);
		break;

	case CVALUE_KIND_EXPR:
		dbx_free(self->cv_expr.v_buffer);
		ATTR_FALLTHROUGH
	case CVALUE_KIND_IEXPR:
		cvalue_cfiexpr_fini(&self->cv_expr.v_expr);
		break;

	default:
		break;
	}
	ctyperef_fini(&self->cv_type);
}


DECL_END

#if defined(__x86_64__) || defined(__i386__)
#include <kernel/x86/gdt.h>
#endif /* __x86_64__ || __i386__ */

#include <compat/kos/exec/elf.h> /* COMPAT_ELF_ARCH_CLASS */
#include <kos/exec/elf.h>        /* ELF_ARCH_CLASS */

#undef ELFV_HAVE_32
#undef ELFV_HAVE_64
#if (defined(_MODULE_HAVE_SIZEOF_POINTER) && \
     defined(COMPAT_ELF_ARCH_CLASS) &&       \
     COMPAT_ELF_ARCH_CLASS != ELF_ARCH_CLASS)
#if COMPAT_ELF_ARCH_CLASS == ELFCLASS32
#define ELFV_HAVE_32
#elif COMPAT_ELF_ARCH_CLASS == ELFCLASS64
#define ELFV_HAVE_64
#endif /* COMPAT_ELF_ARCH_CLASS == ... */
#endif /* ... */
#if ELF_ARCH_CLASS == ELFCLASS32
#define ELFV_HAVE_32
#elif ELF_ARCH_CLASS == ELFCLASS64
#define ELFV_HAVE_64
#endif /* ELF_ARCH_CLASS == ... */

DECL_BEGIN


/* Return the user-space TLS base register for `dbg_current' */
PRIVATE ATTR_PURE WUNUSED uintptr_t
NOTHROW(FCALL get_user_tls_base_register)(void) {
	uintptr_t result;
#ifdef __x86_64__
	dbg_rt_getregbyid(DBG_RT_REGLEVEL_VIEW, X86_REGISTER_MISC_FSBASEQ,
	                  &result, sizeof(result));
#elif defined(__i386__)
	if (!dbg_rt_getregbyid(DBG_RT_REGLEVEL_VIEW, X86_REGISTER_MISC_GSBASEL,
	                       &result, sizeof(result)))
		result = FORTASK(dbg_current, this_x86_user_gsbase);
#elif defined(__arm__)
#if 0 /* TODO */
	if (!dbg_rt_getregbyid(DBG_RT_REGLEVEL_VIEW, ARM_REGISTER_TLSBASE,
	                       &result, sizeof(result)))
		result = FORTASK(dbg_current, this_arm_user_tlsbase);
#else
	dbg_rt_getregbyid(DBG_RT_REGLEVEL_VIEW, ARM_REGISTER_TLSBASE,
	                  &result, sizeof(result));
#endif
#else /* ... */
#error "Unsupported architecture"
#endif /* !... */
	return result;
}

#if defined(ELFV_HAVE_32) && defined(ELFV_HAVE_64)
#ifndef _MODULE_HAVE_SIZEOF_POINTER
#error "Unsupported configuration"
#endif /* !_MODULE_HAVE_SIZEOF_POINTER */
#define ElfV(x)                      union { Elf32_##x _32; Elf64_##x _64; }
#define ElfV_any(self)               (self)._32
#define ElfV_sizeof(mod, T)          ((mod)->md_sizeof_pointer == 4 ? sizeof(Elf32_##T) : sizeof(Elf64_##T))
#define ElfV_field(mod, self, name)  ((mod)->md_sizeof_pointer == 4 ? (self)._32.name : (self)._64.name)
#define ElfV_fieldP(mod, self, name) ((mod)->md_sizeof_pointer == 4 ? (self)._32 name : (self)._64 name)
#elif defined(ELFV_HAVE_32)
#define ElfV(x)                      Elf32_##x
#define ElfV_any(self)               (self)
#define ElfV_sizeof(mod, T)          sizeof(Elf32_##T)
#define ElfV_field(mod, self, name)  (self).name
#define ElfV_fieldP(mod, self, name) (self) name
#elif defined(ELFV_HAVE_64)
#define ElfV(x)                      Elf64_##x
#define ElfV_any(self)               (self)
#define ElfV_sizeof(mod, T)          sizeof(Elf64_##T)
#define ElfV_field(mod, self, name)  (self).name
#define ElfV_fieldP(mod, self, name) (self) name
#else /* ... */
#error "Invalid configuration (no known elf word size configuration is active)"
#endif /* !... */

typedef ElfV(Ehdr)   ElfV_Ehdr;
typedef ElfV(Shdr)   ElfV_Shdr;
typedef ElfV(Phdr)   ElfV_Phdr;
typedef ElfV(Phdr *) ElfV_PhdrP;
typedef ElfV(Dyn)    ElfV_Dyn;
typedef ElfV(Rel)    ElfV_Rel;
typedef ElfV(Rela)   ElfV_Rela;


/* Member indices (to-be multiplied by the pointer-size) of libdl internals */
#define STRUCT_dlmodule_INDEXOF_dm_loadaddr             0
#define STRUCT_dlmodule_INDEXOF_dm_filename             1
#define STRUCT_dlmodule_INDEXOF_dm_dynhdr               2
#define STRUCT_dlmodule_INDEXOF_dm_modules_next         3
#define STRUCT_dlmodule_INDEXOF_dm_modules_prev         4
#define STRUCT_dlmodule_INDEXOF_dm_tlsoff               5
#define STRUCT_dlmodule_INDEXOF_dm_tlsinit              6
#define STRUCT_dlmodule_INDEXOF_dm_tlsfsize             7
#define STRUCT_dlmodule_INDEXOF_dm_tlsmsize             8
#define STRUCT_dlmodule_INDEXOF_dm_tlsalign             9
#define STRUCT_dlmodule_INDEXOF_dm_tlsstoff             10
#define STRUCT_tls_segment_INDEXOF_ts_self              0
#define STRUCT_tls_segment_INDEXOF_ts_threads__ln_next  1
#define STRUCT_tls_segment_INDEXOF_ts_threads__ln_pself 2
#define STRUCT_tls_segment_INDEXOF_ts_exlock            3
#define STRUCT_tls_segment_INDEXOF_ts_extree            4
#define STRUCT_dtls_extension_INDEXOF_te_tree__rb_lhs   0
#define STRUCT_dtls_extension_INDEXOF_te_tree__rb_rhs   1
#define STRUCT_dtls_extension_INDEXOF_te_module         2
#define STRUCT_dtls_extension_INDEXOF_te_data           3

struct libdl_dlmodule;
struct libdl_tls_segment;
struct libdl_dtls_extension;

/* Read out a user-space pointer who's size is defined by `self',
 * and store the  resulting pointer in  `*presult'. The  original
 * pointer may be zero-extended if necessary. */
PRIVATE NONNULL((1, 2)) bool
NOTHROW(FCALL module_getpointer)(struct module *__restrict self,
                                 NCX void *address,
                                 void **__restrict presult) {
#if defined(ELFV_HAVE_32) && defined(ELFV_HAVE_64)
	if (self->md_sizeof_pointer == 4) {
		uint32_t p32;
		if (dbg_readmemory(address, &p32, 4) != 0)
			goto err;
		*presult = (void *)(uintptr_t)p32;
	} else {
		uint64_t p64;
		if (dbg_readmemory(address, &p64, 8) != 0)
			goto err;
		*presult = (void *)(uintptr_t)p64;
	}
#elif defined(ELFV_HAVE_32)
	uint32_t p32;
	(void)self;
	if (dbg_readmemory(address, &p32, 4) != 0)
		goto err;
	*presult = (void *)(uintptr_t)p32;
#elif defined(ELFV_HAVE_64)
	uint64_t p64;
	(void)self;
	if (dbg_readmemory(address, &p64, 8) != 0)
		goto err;
	*presult = (void *)(uintptr_t)p64;
#else /* ... */
#error "Invalid configuration (no known elf word size configuration is active)"
#endif /* !... */
	return true;
err:
	return false;
}

PRIVATE NONNULL((1, 2)) bool
NOTHROW(FCALL module_scan_reloc_for_DlModule)(struct module *__restrict self,
                                              struct libdl_dlmodule **__restrict presult,
                                              uintptr_t r_offset, uintptr_t r_info,
                                              uintptr_t r_addend) {
	uintptr_t r_type;
	(void)r_addend;
	r_type = module_sizeof_pointer(self) == 4
	         ? ELF32_R_TYPE(r_info)
	         : ELF64_R_TYPE(r_info);
	switch (r_type) {

#ifdef __x86_64__
	case R_X86_64_DTPMOD64: {
		NCX uint64_t *uaddr;
		if (self->md_sizeof_pointer == 4)
			break;
		uaddr = (NCX uint64_t *)(self->md_loadaddr + r_offset);
		if (!ADDR_ISUSER(uaddr))
			break;
		/* Try to read the pointer from this location. */
		return module_getpointer(self, uaddr, (void **)presult);
	}	break;
#endif /* __x86_64__ */

#if defined(__x86_64__) || defined(__i386__)
	case R_386_TLS_DTPMOD32: {
		NCX uint32_t *uaddr;
#ifdef __x86_64__
		if (self->md_sizeof_pointer != 4)
			break;
#endif /* __x86_64__ */
		uaddr = (NCX uint32_t *)(self->md_loadaddr + r_offset);
		if (!ADDR_ISUSER(uaddr))
			break;
		/* Try to read the pointer from this location. */
		return module_getpointer(self, uaddr, (void **)presult);
	}	break;
#endif /* __x86_64__ || __i386__ */

#ifdef __arm__
	case R_ARM_TLS_DTPMOD32: {
		NCX uint32_t *uaddr;
		uaddr = (NCX uint32_t *)(self->md_loadaddr + r_offset);
		if (!ADDR_ISUSER(uaddr))
			break;
		/* Try to read the pointer from this location. */
		return module_getpointer(self, uaddr, (void **)presult);
	}	break;
#endif /* __arm__ */

	default:
		break;
	}
	return false;
}

PRIVATE NONNULL((1, 2)) bool
NOTHROW(FCALL module_scan_rel_for_DlModule)(struct module *__restrict self,
                                            struct libdl_dlmodule **__restrict presult,
                                            NCX ElfV_Rel const *base, size_t count) {
	size_t sizeof_rel;
	sizeof_rel = ElfV_sizeof(self, Rel);
	for (; count; --count) {
		ElfV_Rel rel;
		if (dbg_readmemory(base, &rel, sizeof_rel) != 0)
			break;
		if (module_scan_reloc_for_DlModule(self, presult,
		                                   ElfV_field(self, rel, r_offset),
		                                   ElfV_field(self, rel, r_info),
		                                   0))
			return true;
		base = (NCX ElfV_Rel const *)((byte_t const *)base + sizeof_rel);
	}
	return false;
}

PRIVATE NONNULL((1, 2)) bool
NOTHROW(FCALL module_scan_rela_for_DlModule)(struct module *__restrict self,
                                              struct libdl_dlmodule **__restrict presult,
                                              NCX ElfV_Rela const *base, size_t count) {
	size_t sizeof_rel;
	sizeof_rel = ElfV_sizeof(self, Rela);
	for (; count; --count) {
		ElfV_Rela rel;
		if (dbg_readmemory(base, &rel, sizeof_rel) != 0)
			break;
		if (module_scan_reloc_for_DlModule(self, presult,
		                                   ElfV_field(self, rel, r_offset),
		                                   ElfV_field(self, rel, r_info),
		                                   ElfV_field(self, rel, r_addend)))
			return true;
		base = (NCX ElfV_Rela const *)((byte_t const *)base + sizeof_rel);
	}
	return false;
}

PRIVATE NONNULL((1, 2)) bool
NOTHROW(FCALL module_scan_dynamic_for_DlModule)(struct module *__restrict self,
                                                struct libdl_dlmodule **__restrict presult,
                                                NCX ElfV_Dyn const *dyn_start,
                                                NCX ElfV_Dyn const *dyn_end) {
	ElfV_Rela const *rela_base;
	ElfV_Rel const *rel_base, *jmp_base;
	size_t rela_count, rel_count;
	size_t jmp_count, entsize;
	bool jmp_rels_have_addend;
	rela_base            = NULL;
	rela_count           = 0;
	jmp_rels_have_addend = false;
	rel_base             = NULL;
	rel_count            = 0;
	jmp_base             = NULL;
	jmp_count            = 0;
	entsize              = ElfV_sizeof(self, Dyn);
	while (dyn_start < dyn_end) {
		ElfV_Dyn ent;
		uintptr_t d_tag, d_val;
		if (dbg_readmemory(dyn_start, &ent, entsize) != 0)
			goto nope;
		d_tag = ElfV_field(self, ent, d_tag);
		d_val = ElfV_field(self, ent, d_un.d_val);
		switch (d_tag) {

		case DT_NULL:
			goto done_dynamic;

		case DT_REL:
			rel_base = (ElfV_Rel *)(self->md_loadaddr + d_val);
			break;

		case DT_RELSZ:
			rel_count = d_val / ElfV_sizeof(self, Rel);
			break;

		case DT_JMPREL:
			jmp_base = (ElfV_Rel *)(self->md_loadaddr + d_val);
			break;

		case DT_PLTRELSZ:
			jmp_count = d_val / ElfV_sizeof(self, Rel);
			break;

		case DT_RELA:
			rela_base = (ElfV_Rela *)(self->md_loadaddr + d_val);
			break;

		case DT_RELASZ:
			rela_count = d_val / ElfV_sizeof(self, Rela);
			break;

		case DT_PLTREL:
			if (d_val == DT_RELA)
				jmp_rels_have_addend = true;
			break;

		default:
			break;
		}
		dyn_start = (NCX ElfV_Dyn const *)((byte_t const *)dyn_start + entsize);
	}
done_dynamic:

	/* Scan the different relocation tables for what we're looking for. */
	if (module_scan_rel_for_DlModule(self, presult, rel_base, rel_count))
		return true;
	if (module_scan_rela_for_DlModule(self, presult, rela_base, rela_count))
		return true;
	if (jmp_rels_have_addend) {
		if (module_scan_rela_for_DlModule(self, presult, (ElfV_Rela const *)jmp_base, jmp_count))
			return true;
	} else {
		if (module_scan_rel_for_DlModule(self, presult, jmp_base, jmp_count))
			return true;
	}
nope:
	return false;
}

/* Calculate the value of the user-space `DlModule' for `self' by looking at relocations.
 * @param: p_tls_msize: Fill with the size of the PT_TLS segment when returning `false',
 *                      or `0' on error, or if no PT_TLS segment exists (undefined  when
 *                      returning `true')
 * @param: p_ehdr_type: Filled with the value of `ehdr.e_type' when returning `false'. */
PRIVATE NONNULL((1, 2, 3, 4)) bool
NOTHROW(FCALL module_get_libdl_DlModule_address_byrel)(struct module *__restrict self,
                                                       struct libdl_dlmodule **__restrict presult,
                                                       size_t *__restrict p_tls_msize,
                                                       uint16_t *__restrict p_ehdr_type) {
	ElfV_Dyn const *dyn_start, *dyn_end;
	ElfV_PhdrP phdr;
	ElfV_Ehdr ehdr;
	uint16_t pt_dyn_header;
	*p_tls_msize = 0;
	*p_ehdr_type = ET_NONE;

	if unlikely(!self->md_file)
		goto nope;

	/* Load the ELF header. */
	TRY {
		mfile_readall(self->md_file, &ehdr, sizeof(ehdr), 0);
	} EXCEPT {
		goto nope;
	}

	/* Sanity check. */
	if (ElfV_any(ehdr).e_ident[EI_MAG0] != ELFMAG0 ||
	    ElfV_any(ehdr).e_ident[EI_MAG1] != ELFMAG1 ||
	    ElfV_any(ehdr).e_ident[EI_MAG2] != ELFMAG2 ||
	    ElfV_any(ehdr).e_ident[EI_MAG3] != ELFMAG3)
		goto nope;
	if (ElfV_field(self, ehdr, e_phentsize) != ElfV_sizeof(self, Phdr))
		goto nope;
	*p_ehdr_type = ElfV_field(self, ehdr, e_type);

	ElfV_any(phdr) = (typeof(ElfV_any(phdr)))dbx_malloc(ElfV_field(self, ehdr, e_phnum) *
	                                                    ElfV_field(self, ehdr, e_phentsize));
	if unlikely(!ElfV_any(phdr))
		goto nope;

	/* Load program headers. (so we can find the PT_DYNAMIC header) */
	TRY {
		mfile_readall(self->md_file,
		              ElfV_any(phdr),
		              ElfV_field(self, ehdr, e_phnum) *
		              ElfV_field(self, ehdr, e_phentsize),
		              (pos_t)ElfV_field(self, ehdr, e_phoff));
	} EXCEPT {
		goto nope_phdr;
	}

	/* Check if there is a PT_TLS segment. */
	for (pt_dyn_header = 0; pt_dyn_header < ElfV_field(self, ehdr, e_phnum); ++pt_dyn_header) {
		if (ElfV_fieldP(self, phdr, [pt_dyn_header].p_type) == PT_TLS) {
			*p_tls_msize = ElfV_fieldP(self, phdr, [pt_dyn_header].p_memsz);
			break;
		}
	}

	/* Find the PT_DYNAMIC header. */
	for (pt_dyn_header = 0; pt_dyn_header < ElfV_field(self, ehdr, e_phnum); ++pt_dyn_header) {
		if (ElfV_fieldP(self, phdr, [pt_dyn_header].p_type) == PT_DYNAMIC)
			goto got_pt_dynamic;
	}
	goto nope_phdr;
got_pt_dynamic:

	/* Load the bounds of the user-space .dynamic section. */
	dyn_start = (ElfV_Dyn const *)(self->md_loadaddr + ElfV_fieldP(self, phdr, [pt_dyn_header].p_vaddr));
	dyn_end   = (ElfV_Dyn const *)((byte_t const *)dyn_start + ElfV_fieldP(self, phdr, [pt_dyn_header].p_memsz));
	dbx_free(ElfV_any(phdr));

	/* Validate loaded pointers. */
	if unlikely(dyn_start >= dyn_end)
		goto nope;
	if unlikely(!ADDR_ISUSER(dyn_start))
		goto nope;
	if unlikely(!ADDR_ISUSER((byte_t const *)dyn_end - 1))
		goto nope;

	/* Now scan the .dynamic section for meta-data related to relocations. */
	return module_scan_dynamic_for_DlModule(self, presult, dyn_start, dyn_end);
nope_phdr:
	dbx_free(ElfV_any(phdr));
nope:
	return false;
}

/* Calculate   the  TLS-base  address  of  `self'  for
 * `dbg_current', and store the result in `*ptls_base' */
PRIVATE NONNULL((1, 2)) bool
NOTHROW(FCALL module_get_user_tls_base)(struct module *__restrict self,
                                        byte_t **__restrict ptls_base) {
	struct libdl_tls_segment *utls;
	struct libdl_dlmodule *dlmod;
	size_t tls_msize;
	uint16_t ehdr_type;

	/* Don't do all of this trickery when the kernel's been poisoned.
	 * The below code may call-back to (possibly) faulty kernel  code
	 * due to the dependency on `mfile_readall()' */
	if (kernel_poisoned())
		goto nope;

	/* This is where it gets really hacky, since we rely on  internals
	 * from `libdl.so' that aren't normally exposed to any other APIs:
	 *
	 *  #1: We need to figure out the address of the user-space `DlModule *'
	 *      that is associated with `self'.  Luckily, we can do this  fairly
	 *      easily by searching the module's relocations table for an  entry
	 *      that uses `R_386_TLS_DTPMOD32' (or the equivalent for the target
	 *      architecture of `self')
	 *
	 *  #2: Since KOS's system libdl.so (re-)uses the `DlModule *' pointer
	 *      as TLS  index, we  can take  the offset  contained within  the
	 *      `R_386_TLS_DTPMOD32' relocation and add it to the load address
	 *      taken from `self',  to get a  user-space memory location  that
	 *      should  contain  the `DlModule *'  pointer we're  looking for.
	 *
	 *  #3: With the  `DlModule *'  pointer  at hand,  we  can  proceed  to
	 *      essentially re-implement `dltlsaddr2(tls_handle, tls_segment)',
	 *      using the `DlModule *' we've discovered above for `tls_handle',
	 *      and simply using `utls_base' for `tls_segment' */

	/* Start by calculating the user-space `DlModule *' pointer. */
	if (!module_get_libdl_DlModule_address_byrel(self, &dlmod, &tls_msize, &ehdr_type)) {
		/* Determining the libdl handle by relocations only works for  shared
		 * libraries, but not if the main program also uses TLS variables, or
		 * a library was (for some reason) compiled to use static TLS.
		 *
		 * In this case, we assume that an `ET_EXEC' module uses static TLS. */
		if (ehdr_type == ET_EXEC && tls_msize > 0) {
			utls = (struct libdl_tls_segment *)get_user_tls_base_register();
			if (!ADDR_ISUSER(utls))
				goto nope;
			*ptls_base = (byte_t *)utls - tls_msize; /* XXX: This '-' is arch-specific I believe... */
			return ADDR_ISUSER(*ptls_base);
		}

		/* TODO: Enumerate libdl's module list (~ala `dl_globals.dg_alllist')
		 *       in search  of  a  module  matching  `self->md_load(min|max)' */
		goto nope;
	}

	if unlikely(!dlmod || !ADDR_ISUSER(dlmod))
		goto nope;

	/* Calculate the TLS-base register as (presumably) used
	 * by  user-space in order  to implement TLS variables. */
	utls = (struct libdl_tls_segment *)get_user_tls_base_register();
	if (!ADDR_ISUSER(utls))
		goto nope;

	{
		ptrdiff_t tls_offset;
		if (!module_getpointer(self,
		                       (byte_t *)dlmod +
		                       STRUCT_dlmodule_INDEXOF_dm_tlsstoff *
		                       module_sizeof_pointer(self),
		                       (void **)&tls_offset))
			goto nope;

		/* Check if this module has a static TLS offset. */
		if (tls_offset != 0) {
			*ptls_base = (byte_t *)utls + tls_offset;
			return ADDR_ISUSER(*ptls_base);
		}
	}

	/* The module uses the dynamic TLS model. As such, we must scan the
	 * TLS extension table for a matching module. Note that  user-space
	 * uses  a binary tree for this purpose, so we can use that to find
	 * the module that we're looking for.
	 *
	 * Also  note that we set a max indirection limit of `BITSOF(void *)'
	 * before we error out, thus preventing infinite recursion when user-
	 * space has set-up  their TLS  extension table to  form an  infinite
	 * loop. */
	{
		struct libdl_dtls_extension *ext;
		unsigned int max_indirection;
		if (!module_getpointer(self,
		                       (byte_t *)utls +
		                       STRUCT_tls_segment_INDEXOF_ts_extree *
		                       module_sizeof_pointer(self),
		                       (void **)&ext))
			goto nope;
		max_indirection = BITSOF(void *);
		while (ext) {
			struct libdl_dlmodule *extab_dlmod;
			uintptr_t indexof_next;
			if (!ext)
				goto nope;
			if (!ADDR_ISUSER(ext))
				goto nope;
			if (!module_getpointer(self,
			                       (byte_t *)ext +
			                       STRUCT_dtls_extension_INDEXOF_te_module *
			                       module_sizeof_pointer(self),
			                       (void **)&extab_dlmod))
				goto nope;

			/* The least significant bit is used as red/black indicator.
			 * As such, we must clear that bit here. */
			extab_dlmod = (struct libdl_dlmodule *)((uintptr_t)extab_dlmod & ~1);
			if (!extab_dlmod || !ADDR_ISUSER(extab_dlmod))
				goto nope;
			if (dlmod < extab_dlmod) {
				indexof_next = STRUCT_dtls_extension_INDEXOF_te_tree__rb_lhs;
			} else if (dlmod > extab_dlmod) {
				indexof_next = STRUCT_dtls_extension_INDEXOF_te_tree__rb_rhs;
			} else {
				/* Found it! */
				break;
			}
			if (!max_indirection)
				goto nope;
			--max_indirection;

			/* Load the next extension pointer. */
			if (!module_getpointer(self,
			                       (byte_t *)ext +
			                       indexof_next *
			                       module_sizeof_pointer(self),
			                       (void **)&ext))
				goto nope;
		}

		/* Found the proper TLS extension.
		 * The result we're looking for is stored in its `te_data' field. */
		if (!module_getpointer(self,
		                       (byte_t *)ext +
		                       STRUCT_dtls_extension_INDEXOF_te_data *
		                       module_sizeof_pointer(self),
		                       (void **)ptls_base))
			goto nope;

		/* Make sure that the pointer is actually user-space! */
		if (!ADDR_ISUSER(*ptls_base))
			goto nope;
	} /* Scope */
	return true;
nope:
	return false;
}

PRIVATE ATTR_NOINLINE NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cexpr_cfi_set_address)(struct cvalue *__restrict self,
                                     NCX void *addr) {
	/* Always include the expression  address addend in the  calculation!
	 * Without this, you'd be unable to access (e.g.) members of a struct
	 * who's address must be calculated via a CFI expression. */
	addr = (byte_t *)addr + self->cv_expr.v_bufoff;

	/* We must  still write-back  any unwritten  modifications,
	 * even though there really shouldn't be any at this point. */
	if (self->cv_kind == CVALUE_KIND_EXPR) {
		if (self->cv_expr.v_buffer) {
			if (dbg_writememory(addr, self->cv_expr.v_buffer,
			                    self->cv_expr.v_buflen,
			                    cexpr_forcewrite) != 0)
				goto err_fault;
			dbx_free(self->cv_expr.v_buffer);
		}
	} else {
		if (dbg_writememory(addr, self->cv_expr.v_ibuffer,
		                    self->cv_expr.v_buflen,
		                    cexpr_forcewrite) != 0)
			goto err_fault;
	}

	/* Change the value-kind to become a memory reference. */
	self->cv_kind = CVALUE_KIND_ADDR;
	self->cv_addr = addr;
	return DBX_EOK;
err_fault:
	return DBX_EFAULT;
}

/* Try to convert a `CVALUE_KIND_EXPR' or `CVALUE_KIND_IEXPR'
 * expression  into  a `CVALUE_KIND_ADDR'  object,  such that
 * its address may be taken, and data can be accessed without
 * having to use an intermediate buffer.
 * @return: DBX_EOK:    Success (`self' has become `CVALUE_KIND_ADDR')
 * @return: DBX_EOK:    Not possible (`self' remains unchanged)
 * @return: DBX_EFAULT: Segmentation fault. */
PRIVATE ATTR_NOINLINE NONNULL((1)) dbx_errno_t
NOTHROW_NCX(FCALL cexpr_cfi_to_address_impl)(struct cvalue *__restrict self,
                                             struct cmodule *mod) {
	unwind_ste_t ste_top;
	unwind_emulator_t emulator;
	size_t expr_length;
	void const *pc;
	uintptr_t module_relative_pc;
	unwind_errno_t result;
	di_debuginfo_compile_unit_simple_t cu;
	byte_t temp_buffer[1];
	bool second_pass;
#ifdef __ARCH_HAVE_COMPAT
	struct unwind_getreg_compat_data compat_getreg_data;
#endif /* __ARCH_HAVE_COMPAT */

	bzero(&emulator, sizeof(emulator));
	emulator.ue_tlsbase = (byte_t *)-1; /* Lazily calculate so we can detect if this was used. */
	second_pass         = false;        /* Used to lazily calculate the correct `ue_tlsbase' (if used) */
do_second_pass:
	bzero(&cu, sizeof(cu));
	pc = dbg_getpcreg(DBG_RT_REGLEVEL_VIEW);

	/* Select the proper function. */
	module_relative_pc = (uintptr_t)pc;
	if (mod) {
		emulator.ue_sectinfo   = cmodule_unwind_emulator_sections(mod);
		emulator.ue_addroffset = module_getloadaddr(mod->cm_module);
		module_relative_pc -= emulator.ue_addroffset;
		emulator.ue_pc = debuginfo_location_select(&self->cv_expr.v_expr.v_expr,
		                                           self->cv_expr.v_expr.v_cu_ranges_startpc,
		                                           module_relative_pc,
		                                           self->cv_expr.v_expr.v_addrsize,
		                                           &expr_length);
	} else {
		emulator.ue_pc = self->cv_expr.v_expr.v_expr.l_expr;
	}
	if unlikely(!emulator.ue_pc)
		goto done;
	cu.cu_ranges.r_startpc         = self->cv_expr.v_expr.v_cu_ranges_startpc;
	cu.cu_addr_base                = self->cv_expr.v_expr.v_cu_addr_base;
	emulator.ue_pc_start           = emulator.ue_pc;
	emulator.ue_pc_end             = emulator.ue_pc + expr_length;
	emulator.ue_regget             = &dbg_getreg;
	emulator.ue_regget_arg         = (void *)(uintptr_t)DBG_RT_REGLEVEL_VIEW;
	emulator.ue_framebase          = &self->cv_expr.v_expr.v_framebase;
	emulator.ue_objaddr            = self->cv_expr.v_expr.v_objaddr;
	emulator.ue_bjmprem            = UNWIND_EMULATOR_BJMPREM_DEFAULT;
	emulator.ue_addrsize           = self->cv_expr.v_expr.v_addrsize;
	emulator.ue_ptrsize            = self->cv_expr.v_expr.v_ptrsize;
	emulator.ue_piecebuf           = temp_buffer; /* Needed to detect `ue_piecebits' below */
	emulator.ue_piecesiz           = sizeof(temp_buffer);
	emulator.ue_cu                 = &cu;
	emulator.ue_module_relative_pc = module_relative_pc;
#ifdef __ARCH_HAVE_COMPAT
	if (dbg_current_iscompat()) {
		unwind_getreg_compat_data_init(&compat_getreg_data, &dbg_getreg,
		                               (void *)(uintptr_t)DBG_RT_REGLEVEL_VIEW);
		emulator.ue_regget     = &unwind_getreg_compat;
		emulator.ue_regget_arg = &compat_getreg_data;
	}
#define LOCAL_ue_regget     emulator.ue_regget
#define LOCAL_ue_regget_arg emulator.ue_regget_arg
#else /* __ARCH_HAVE_COMPAT */
#define LOCAL_ue_regget     (&dbg_getreg)
#define LOCAL_ue_regget_arg ((void *)(uintptr_t)DBG_RT_REGLEVEL_VIEW)
#endif /* !__ARCH_HAVE_COMPAT */

	/* Execute the emulator. */
	result = unwind_emulator_exec_autostack(&emulator, NULL, &ste_top, NULL);
#if 0 /* No stack-entry location. */
	if (result == UNWIND_EMULATOR_NO_RETURN_VALUE)
		goto done;
#endif
	if (result != UNWIND_SUCCESS)
		goto done; /* Ignore all errors... */
	if unlikely(emulator.ue_piecebits != 0)
		goto done; /* The value isn't continuous (and so its address cannot be taken) */

	/* Switch on what was left in the stack-top entry to
	 * determine  if we can extract an absolute address. */
	switch (ste_top.s_type) {

		/* NOTE: The reason  why specifically  these 4  types of  stack-values
		 *       can be dereferenced can be  traced back to the  documentation
		 *       of these constants in "<libunwind/cfi.h>", following the line
		 *       """Effective return values (for location expressions):""""
		 * If you compare this list with it, you will see that this is the list
		 * of expressions that are dereferenced during evaluation, meaning that
		 * internally they always first evaluate to an address. */
	case UNWIND_STE_CONSTANT:
	case UNWIND_STE_REGISTER:
	case UNWIND_STE_RO_LVALUE:
	case UNWIND_STE_RW_LVALUE: {
		NCX byte_t *lvalue;

		/* Check if the TLS-base address was used by the CFI expression.
		 * If it was, then we must repeat the expression with the proper
		 * TLS address, since the one calculated by libunwind only works
		 * for the kernel core and drivers (but not for userspace) */
		if (emulator.ue_tlsbase != (byte_t *)-1 && mod &&
		    cmodule_isuser(mod) && !second_pass) {
			bool ok;

			/* Calculate the TLS-base address for `mod' in the context of `dbg_current' */
			ok = module_get_user_tls_base(mod->cm_module, &emulator.ue_tlsbase);
			if unlikely(!ok)
				goto done;      /* Not possible to take the address. */
			second_pass = true; /* Remember that we've filled in the proper user-space TLS base. */
			goto do_second_pass;
		}
		lvalue = ste_top.s_lvalue;
		if (ste_top.s_type == UNWIND_STE_REGISTER) {
			/* Convert to l-value */
			union {
				uintptr_t p;
				byte_t buf[CFI_REGISTER_MAXSIZE];
			} regval;
			unwind_errno_t getreg_error;
			getreg_error = (*LOCAL_ue_regget)(LOCAL_ue_regget_arg,
			                                  ste_top.s_register,
			                                  regval.buf);
			if unlikely(getreg_error != UNWIND_SUCCESS)
				goto done;
			lvalue = (byte_t *)regval.p + ste_top.s_regoffset;
		}

		/* Got it! The address can now be found in `lvalue' */
		return cexpr_cfi_set_address(self, lvalue);
	}	break;

	default:
		break;
	}
#undef LOCAL_ue_regget_arg
#undef LOCAL_ue_regget
done:
	return DBX_EOK;
}

PRIVATE ATTR_NOINLINE NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cexpr_cfi_to_address)(struct cvalue *__restrict self) {
	dbx_errno_t result;
	pagedir_phys_t old_pdir, req_pdir;
	struct cmodule *mod;

	/* Sanity check: are we actually dealing with a CFI expression? */
	if (self->cv_kind != CVALUE_KIND_EXPR &&
	    self->cv_kind != CVALUE_KIND_IEXPR)
		return DBX_EOK;
	if (self->cv_expr.v_expr.v_gotaddr &&
	    !self->cv_expr.v_expr.v_expr.l_expr &&
	    !self->cv_expr.v_expr.v_expr.l_llist4 &&
	    !self->cv_expr.v_expr.v_expr.l_llist5) {
		/* Special case: We're already been given the address.
		 *               it's `self->cv_expr.v_expr.v_objaddr' */
		return cexpr_cfi_set_address(self, self->cv_expr.v_expr.v_objaddr);
	}
#if 0 /* Enable to force use of `debuginfo_location_(get|set)value' */
	(void)&cexpr_cfi_to_address_impl;
	(void)result;
	(void)old_pdir;
	(void)req_pdir;
	(void)mod;
	return DBX_EOK;
#else
	old_pdir = pagedir_get();
	req_pdir = old_pdir;
	mod      = self->cv_expr.v_expr.v_module;
	if (mod && !wasdestroyed(cmodule_mman(mod)))
		req_pdir = cmodule_mman(mod)->mm_pagedir_p;

	/* This must run in the context of `cmodule_mman(mod)' */
	if (old_pdir != req_pdir) {
		if unlikely(!dbg_rt_verifypagedir(req_pdir))
			return DBX_EFAULT;
		pagedir_set(req_pdir);
	}
	TRY {
		/* Do the actual work. */
		result = cexpr_cfi_to_address_impl(self, mod);
	} EXCEPT {
		/* Exceptions thrown in this function currently crash the kernel.
		 * Instead,  they  should  be  handled  by  returning DBX_EFAULT! */
		result = DBX_EFAULT;
	}
	if (old_pdir != req_pdir)
		pagedir_set(old_pdir);
	return result;
#endif
}


PRIVATE dbx_errno_t const errno_unwind2dbx[] = {
	[UNWIND_SUCCESS]                      = DBX_EOK,
	[UNWIND_NO_FRAME]                     = DBX_EINTERN,
	[UNWIND_INVALID_REGISTER]             = DBX_EINTERN,
	[UNWIND_SEGFAULT]                     = DBX_EFAULT,
	[UNWIND_BADALLOC]                     = DBX_ENOMEM,
	[UNWIND_EMULATOR_UNKNOWN_INSTRUCTION] = DBX_EINTERN,
	[UNWIND_EMULATOR_ILLEGAL_INSTRUCTION] = DBX_EINTERN,
	[UNWIND_EMULATOR_STACK_OVERFLOW]      = DBX_EINTERN,
	[UNWIND_EMULATOR_STACK_UNDERFLOW]     = DBX_EINTERN,
	[UNWIND_EMULATOR_BADJMP]              = DBX_EINTERN,
	[UNWIND_EMULATOR_LOOP]                = DBX_EINTERN,
	[UNWIND_EMULATOR_BUFFER_TOO_SMALL]    = DBX_EINTERN,
	[UNWIND_EMULATOR_DIVIDE_BY_ZERO]      = DBX_EFAULT,
	[UNWIND_EMULATOR_NO_FUNCTION]         = DBX_EOPTIMIZED,
	[UNWIND_EMULATOR_INVALID_FUNCTION]    = DBX_EINTERN,
	[UNWIND_EMULATOR_NO_CFA]              = DBX_EINTERN,
	[UNWIND_EMULATOR_NO_RETURN_VALUE]     = DBX_EINTERN,
	[UNWIND_EMULATOR_NOT_WRITABLE]        = DBX_ERDONLY,
	[UNWIND_CFA_UNKNOWN_INSTRUCTION]      = DBX_EINTERN,
	[UNWIND_CFA_ILLEGAL_INSTRUCTION]      = DBX_EINTERN,
	[UNWIND_APPLY_NOADDR_REGISTER]        = DBX_EINTERN, /* DBX_ENOADDR */
	[UNWIND_PERSONALITY_ERROR]            = DBX_EINTERN,
	[UNWIND_OPTIMIZED_AWAY]               = DBX_EOPTIMIZED,
	[UNWIND_CORRUPTED]                    = DBX_ECORRUPT,
};

PRIVATE WUNUSED ATTR_CONST dbx_errno_t
NOTHROW(FCALL map_unwind_errno)(unwind_errno_t error) {
	if (error < COMPILER_LENOF(errno_unwind2dbx))
		return errno_unwind2dbx[error];
	return DBX_EINTERN;
}

/* Read/write the value of the given CFI expression to/from buf.
 * @return: DBX_EOK:     Success.
 * @return: DBX_EFAULT:  Faulty memory location accessed.
 * @return: DBX_EINTERN: Internal error. */
PUBLIC NONNULL((1, 2)) dbx_errno_t
NOTHROW(KCALL cvalue_cfiexpr_readwrite)(struct cvalue_cfiexpr const *__restrict self,
                                        void *buf, size_t buflen, bool write) {
	unwind_errno_t error;
	TRY {
		if (self->v_gotaddr && !self->v_expr.l_expr &&
		    !self->v_expr.l_llist4 && !self->v_expr.l_llist5) {
			size_t copy_error;
			copy_error = write ? dbg_writememory(self->v_objaddr, buf, buflen, cexpr_forcewrite)
			                   : dbg_readmemory(self->v_objaddr, buf, buflen);
			error = UNWIND_SUCCESS;
			if unlikely(copy_error)
				error = UNWIND_SEGFAULT;
		} else {
			void const *pc;
			di_debuginfo_compile_unit_simple_t cu;
			size_t num_accessed_bits;
			struct cmodule *mod;
			bzero(&cu, sizeof(cu));
			cu.cu_ranges.r_startpc = self->v_cu_ranges_startpc;
			cu.cu_addr_base        = self->v_cu_addr_base;
			pc  = dbg_getpcreg(DBG_RT_REGLEVEL_VIEW);
			mod = self->v_module;
			/* Must execute these functions in the context of the VM associated with their module. */
			{
				pagedir_phys_t old_pdir, req_pdir;
				old_pdir = pagedir_get();
				req_pdir = old_pdir;
				if (!wasdestroyed(cmodule_mman(mod)))
					req_pdir = cmodule_mman(mod)->mm_pagedir_p;
				if (old_pdir != req_pdir) {
					if unlikely(!dbg_rt_verifypagedir(req_pdir))
						return DBX_EFAULT;
					pagedir_set(req_pdir);
				}
				RAII_FINALLY {
					if (old_pdir != req_pdir)
						pagedir_set(old_pdir);
				};
				/* TODO: Proper user-space  support for  `unwind_emulator_t::ue_tlsbase'
				 *       When used by the expression, then we mustn't rely on the native
				 *       TLS-base  calculation function from libunwind, but must instead
				 *       make use of `module_get_user_tls_base()' from above. */
#ifdef __ARCH_HAVE_COMPAT
				if (dbg_current_iscompat()) {
					struct unwind_getreg_compat_data compat_getreg_data;
					unwind_getreg_compat_data_init(&compat_getreg_data, &dbg_getreg,
					                               (void *)(uintptr_t)DBG_RT_REGLEVEL_VIEW);
					if (write) {
						struct unwind_setreg_compat_data compat_setreg_data;
						unwind_setreg_compat_data_init(&compat_setreg_data, &dbg_setreg,
						                               (void *)(uintptr_t)DBG_RT_REGLEVEL_VIEW);
						error = debuginfo_location_setvalue(&self->v_expr,
						                                    cmodule_unwind_emulator_sections(mod),
						                                    &unwind_getreg_compat, &compat_getreg_data,
						                                    &unwind_setreg_compat, &compat_setreg_data, &cu,
						                                    (uintptr_t)pc - module_getloadaddr(mod->cm_module),
						                                    module_getloadaddr(mod->cm_module),
						                                    buf, buflen, &num_accessed_bits, &self->v_framebase,
						                                    self->v_objaddr, self->v_addrsize, self->v_ptrsize);
					} else {
						error = debuginfo_location_getvalue(&self->v_expr,
						                                    cmodule_unwind_emulator_sections(mod),
						                                    &unwind_getreg_compat, &compat_getreg_data, &cu,
						                                    (uintptr_t)pc - module_getloadaddr(mod->cm_module),
						                                    module_getloadaddr(mod->cm_module),
						                                    buf, buflen, &num_accessed_bits, &self->v_framebase,
						                                    self->v_objaddr, self->v_addrsize, self->v_ptrsize);
					}
				} else
#endif /* __ARCH_HAVE_COMPAT */
				{
					if (write) {
						error = debuginfo_location_setvalue(&self->v_expr,
						                                    cmodule_unwind_emulator_sections(mod),
						                                    &dbg_getreg, (void *)(uintptr_t)DBG_RT_REGLEVEL_VIEW,
						                                    &dbg_setreg, (void *)(uintptr_t)DBG_RT_REGLEVEL_VIEW, &cu,
						                                    (uintptr_t)pc - module_getloadaddr(mod->cm_module),
						                                    module_getloadaddr(mod->cm_module),
						                                    buf, buflen, &num_accessed_bits, &self->v_framebase,
						                                    self->v_objaddr, self->v_addrsize, self->v_ptrsize);
					} else {
						error = debuginfo_location_getvalue(&self->v_expr,
						                                    cmodule_unwind_emulator_sections(mod),
						                                    &dbg_getreg, (void *)(uintptr_t)DBG_RT_REGLEVEL_VIEW, &cu,
						                                    (uintptr_t)pc - module_getloadaddr(mod->cm_module),
						                                    module_getloadaddr(mod->cm_module),
						                                    buf, buflen, &num_accessed_bits, &self->v_framebase,
						                                    self->v_objaddr, self->v_addrsize, self->v_ptrsize);
					}
				}
			}
		}
	} EXCEPT {
		error = UNWIND_SEGFAULT;
	}
	if unlikely(error != UNWIND_SUCCESS)
		return map_unwind_errno(error);
	return DBX_EOK;
}


PRIVATE NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cvalue_rw_expr)(struct cvalue *__restrict self,
                              bool write) {
	dbx_errno_t result;
	void *buffer;
	buffer = self->cv_expr.v_ibuffer;
	if (self->cv_kind == CVALUE_KIND_EXPR) {
		buffer = self->cv_expr.v_buffer;
		if (!buffer) {
			if (write)
				return DBX_EOK; /* Not loaded */

			/* Load a new buffer. */
			if (self->cv_expr.v_buflen <= sizeof(self->cv_expr.v_ibuffer)) {
				self->cv_kind = CVALUE_KIND_IEXPR;
				result = cvalue_rw_expr(self, false);
				if unlikely(result != DBX_EOK) {
					self->cv_kind          = CVALUE_KIND_EXPR;
					self->cv_expr.v_buffer = NULL;
				}
				return result;
			}

			/* Allocate a dynamic buffer. */
			buffer = dbx_malloc(self->cv_expr.v_buflen);
			if unlikely(!buffer)
				return DBX_ENOMEM;
			self->cv_expr.v_buffer = buffer;
			result = cvalue_rw_expr(self, false);
			if unlikely(result != DBX_EOK) {
				self->cv_expr.v_buffer = NULL;
				dbx_free(buffer);
			}
			return result;
		}
	}
	result = cvalue_cfiexpr_readwrite(&self->cv_expr.v_expr,
	                                  buffer,
	                                  self->cv_expr.v_buflen,
	                                  write);
	return result;
}

/* Sign- or zero-extend a given buffer. */
PRIVATE WUNUSED dbx_errno_t
NOTHROW(FCALL buffer_extend)(byte_t *data, size_t old_size,
                             size_t new_size, bool sign_extend) {
	if (new_size > old_size) {
		uint8_t sign;
		sign = 0x00;
		if (sign_extend) {
			/* Check if we should sign-extend. */
			byte_t b;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			if (dbg_readmemory(&data[old_size - 1], &b, 1) != 0)
				goto err_fault;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
			if (dbg_readmemory(&data[0], &b, 1) != 0)
				goto err_fault;
#else /* __BYTE_ORDER__ == ... */
#error "Unsupported __BYTE_ORDER__"
#endif /* __BYTE_ORDER__ != ... */
			if (b & 0x80)
				sign = 0xff;
		}
		/* Zero-/sign-extend the pointed-to data. */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		if (dbg_setmemory(&data[old_size], sign,
		                  new_size - old_size,
		                  cexpr_forcewrite) != 0)
			goto err_fault;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		if (dbg_movememoryup(&data[new_size - old_size],
		                     &data[0], old_size,
		                     cexpr_forcewrite) != 0)
			goto err_fault;
		if (dbg_setmemory(&data[0], sign,
		                  new_size - old_size,
		                  cexpr_forcewrite) != 0)
			goto err_fault;
#else /* __BYTE_ORDER__ == ... */
#error "Unsupported __BYTE_ORDER__"
#endif /* __BYTE_ORDER__ != ... */
	} else {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		/* Truncate the value */
		if (new_size < old_size) {
			if (dbg_movememorydown((byte_t *)data,
			                       (byte_t *)data + (old_size - new_size),
			                       new_size, cexpr_forcewrite) != 0)
				goto err_fault;
		}
#endif /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	}
	return DBX_EOK;
err_fault:
	return DBX_EFAULT;
}

/* @return: 1:          Buffer contains a non-zero byte.
 * @return: 0:          Buffer is empty, or contains only zero bytes.
 * @return: DBX_EFAULT: Buffer is faulty. */
PRIVATE ATTR_NOINLINE ATTR_PURE WUNUSED dbx_errno_t
NOTHROW(FCALL buffer_istrue)(void const *addr, size_t num_bytes) {
	byte_t *buf;
	size_t buflen;
	buflen = num_bytes;
	if (buflen > 128)
		buflen = 128;
	buf = (byte_t *)alloca(buflen);
	while (num_bytes) {
		size_t i, temp;
		temp = num_bytes;
		if (temp > buflen)
			temp = buflen;
		if (dbg_readmemory(addr, buf, temp) != 0)
			goto err_fault;
		for (i = 0; i < temp; ++i) {
			if (buf[i] != 0)
				return 1;
		}
		num_bytes -= temp;
		addr = (byte_t *)addr + temp;
	}
	return 0;
err_fault:
	return DBX_EFAULT;
}

PRIVATE NONNULL((1)) void
NOTHROW(FCALL buffer_inv_nofault)(byte_t *buf, size_t buflen) {
	while (buflen) {
		*buf ^= 0xff;
		--buflen;
		++buf;
	}
}

PRIVATE NONNULL((1)) void
NOTHROW(FCALL buffer_dec_nofault)(byte_t *buf, size_t buflen) {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	while (buflen) {
		if (--*buf != 0xff)
			break;
		--buflen;
		++buf;
	}
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	buf += buflen;
	while (buflen) {
		--buf;
		if (--*buf != 0xff)
			break;
		--buflen;
	}
#else /* __BYTE_ORDER__ == ... */
#error "Unsupported endian"
#endif /* __BYTE_ORDER__ != ... */
}




/* Write-back changes made by `self'
 * @return: DBX_EOK:     Success.
 * @return: DBX_EFAULT:  Faulty memory access.
 * @return: DBX_EINTERN: Internal error. */
PUBLIC NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cvalue_flush)(struct cvalue *__restrict self) {
	dbx_errno_t result = DBX_EOK;
	switch (self->cv_kind) {

	case CVALUE_KIND_EXPR:
	case CVALUE_KIND_IEXPR:
		result = cvalue_rw_expr(self, true);
		break;

	case CVALUE_KIND_REGISTER: {
		size_t bufsize, bufneed, reqsize;
		bufsize = ctype_sizeof(self->cv_type.ct_typ);
		bufneed = self->cv_register.r_buflen;
		if unlikely(bufsize != bufneed) {
			/* Sign-/Zero-extend the value based on if the old type was signed. */
			uintptr_t kind;
			kind   = self->cv_type.ct_typ->ct_kind;
			result = buffer_extend(self->cv_register.r_ibuffer, bufsize, bufneed,
			                       CTYPE_KIND_ISINT(kind) && !CTYPE_KIND_INT_ISUNSIGNED(kind));
			if unlikely(result != DBX_EOK)
				goto done;
		}
		reqsize = dbg_rt_setregbyid(DBG_RT_REGLEVEL_VIEW,
		                            self->cv_register.r_regid,
		                            self->cv_register.r_ibuffer,
		                            bufneed);
		if unlikely(reqsize != bufneed)
			result = DBX_EINTERN;
	}	break;

	default:
		break;
	}
done:
	return result;
}


/* Initialize a copy `self' of the given C-value `src'.
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory. */
PUBLIC WUNUSED NONNULL((1, 2)) dbx_errno_t
NOTHROW(FCALL cvalue_initcopy)(struct cvalue *__restrict self,
                               struct cvalue const *__restrict src) {
	memcpy(self, src, sizeof(struct cvalue));
	switch (self->cv_kind) {

	case CVALUE_KIND_DATA:
		if (src->cv_data != NULL) {
			size_t buflen;
			void *buffer;
			buflen = ctype_sizeof(src->cv_type.ct_typ);
			buffer = dbx_malloc(buflen);
			if unlikely(!buffer)
				return DBX_ENOMEM;
			buffer = memcpy(buffer, src->cv_data, buflen);
			self->cv_expr.v_buffer = buffer;
		}
		break;

	case CVALUE_KIND_EXPR:
		if (self->cv_expr.v_buffer) {
			void *buffer;
			buffer = dbx_malloc(self->cv_expr.v_buflen);
			if unlikely(!buffer)
				return DBX_ENOMEM;
			buffer = memcpy(buffer, src->cv_expr.v_buffer,
			                self->cv_expr.v_buflen);
			self->cv_expr.v_buffer = buffer;
		}
		ATTR_FALLTHROUGH
	case CVALUE_KIND_IEXPR:
		incref(self->cv_expr.v_expr.v_module);
		break;

	default:
		break;
	}
	incref(self->cv_type.ct_typ);
	xincref(self->cv_type.ct_info.ci_nameref);
	return DBX_EOK;
}


PRIVATE WUNUSED struct cvalue *
NOTHROW(FCALL _cexpr_pushalloc)(void) {
	size_t alloc_size;
	struct cvalue *result = cexpr_stack - 1;
	if (result == cexpr_stack_stub)
		result = NULL;
	alloc_size = dbx_malloc_usable_size(result) / sizeof(struct cvalue);
	if ((cexpr_stacksize + 2) > alloc_size) {
		result = (struct cvalue *)dbx_realloc(result,
		                                      (cexpr_stacksize + 2) *
		                                      sizeof(struct cvalue));
		if unlikely(!result)
			goto done;
		result = (struct cvalue *)memcpy(result, cexpr_stack_stub,
		                                 sizeof(struct cvalue));
		cexpr_stack = result + 1;
	}
	result += cexpr_stacksize + 1;
done:
	return result;
}

/* Push an element into the C-expression stack.
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory.
 * @return: DBX_ENOENT: [cexpr_pushregister_by_id] No such register. */
PUBLIC NONNULL((1)) dbx_errno_t /* Push `*(typ *)addr' */
NOTHROW(FCALL cexpr_pushaddr)(struct ctyperef const *__restrict typ,
                              NCX void *addr) {
	struct cvalue *valp;
	valp = _cexpr_pushalloc();
	if unlikely(!valp)
		return DBX_ENOMEM;
	ctyperef_initcopy(&valp->cv_type, typ);
	if (cexpr_typeonly) {
		valp->cv_kind = CVALUE_KIND_VOID;
	} else {
		valp->cv_kind = CVALUE_KIND_ADDR;
		valp->cv_addr = addr;
	}
	++cexpr_stacksize;
	return DBX_EOK;
}

PUBLIC NONNULL((1, 2)) dbx_errno_t /* Push a CFI expression. */
NOTHROW(FCALL cexpr_pushexpr)(struct ctyperef const *__restrict typ,
                              struct cvalue_cfiexpr const *__restrict expr,
                              size_t buflen, size_t bufoff) {
	struct cvalue *valp;
	valp = _cexpr_pushalloc();
	if unlikely(!valp)
		return DBX_ENOMEM;
	ctyperef_initcopy(&valp->cv_type, typ);
	if (cexpr_typeonly) {
		valp->cv_kind = CVALUE_KIND_VOID;
	} else if (expr->v_gotaddr &&
	           !expr->v_expr.l_expr &&
	           !expr->v_expr.l_llist4 &&
	           !expr->v_expr.l_llist5) {
		/* Special case: non-CFI object-address expression. */
		valp->cv_kind = CVALUE_KIND_ADDR;
		valp->cv_addr = (byte_t *)expr->v_objaddr + bufoff;
	} else {
		cvalue_cfiexpr_initcopy(&valp->cv_expr.v_expr, expr);
		valp->cv_kind          = CVALUE_KIND_EXPR;
		valp->cv_expr.v_buffer = NULL;
		valp->cv_expr.v_bufoff = bufoff;
		valp->cv_expr.v_buflen = buflen;
	}
	++cexpr_stacksize;
	return DBX_EOK;
}

PUBLIC NONNULL((1)) dbx_errno_t /* Push `(typ)(*(typ const *)data)' */
NOTHROW_NCX(FCALL cexpr_pushdata)(struct ctyperef const *__restrict typ,
                                  NCX void const *data) {
	struct cvalue *valp;
	valp = _cexpr_pushalloc();
	if unlikely(!valp)
		return DBX_ENOMEM;
	if (cexpr_typeonly) {
		valp->cv_kind = CVALUE_KIND_VOID;
	} else {
		void *buffer;
		size_t buflen;
		buflen = ctype_sizeof(typ->ct_typ);
		if (buflen <= sizeof(valp->cv_idata)) {
			buffer        = valp->cv_idata;
			valp->cv_kind = CVALUE_KIND_IDATA;
		} else {
			buffer = dbx_malloc(buflen);
			if unlikely(!buffer)
				return DBX_ENOMEM;
			valp->cv_data = (byte_t *)buffer;
			valp->cv_kind = CVALUE_KIND_DATA;
		}
		memcpy(buffer, data, buflen);
	}
	ctyperef_initcopy(&valp->cv_type, typ);
	++cexpr_stacksize;
	return DBX_EOK;
}

PUBLIC NONNULL((1)) dbx_errno_t /* Push `(typ)value' */
NOTHROW(FCALL cexpr_pushint)(struct ctyperef const *__restrict typ,
                             uintmax_t value) {
	struct cvalue *valp;
	valp = _cexpr_pushalloc();
	if unlikely(!valp)
		return DBX_ENOMEM;
	if (cexpr_typeonly) {
		valp->cv_kind = CVALUE_KIND_VOID;
	} else {
		size_t buflen;
		buflen = ctype_sizeof(typ->ct_typ);
		switch (buflen) {
		case 1: UNALIGNED_SET8(valp->cv_idata, (uint8_t)value); break;
		case 2: UNALIGNED_SET16(valp->cv_idata, (uint16_t)value); break;
		case 4: UNALIGNED_SET32(valp->cv_idata, (uint32_t)value); break;
		case 8: UNALIGNED_SET64(valp->cv_idata, (uint64_t)value); break;
		default:
			return DBX_EINTERN;
		}
		valp->cv_kind = CVALUE_KIND_IDATA;
	}
	ctyperef_initcopy(&valp->cv_type, typ);
	++cexpr_stacksize;
	return DBX_EOK;
}

/* Push a register, given its arch-specific ID, automatically selecting a proper type.
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory.
 * @return: DBX_ENOENT: No such register. */
PUBLIC dbx_errno_t /* Push `(auto)%[reg:regno]' */
NOTHROW(FCALL cexpr_pushregister_by_id)(cpu_regno_t regno) {
	struct cvalue *valp;
	size_t buflen;
	valp = _cexpr_pushalloc();
	if unlikely(!valp)
		return DBX_ENOMEM;
	buflen = dbg_rt_getregbyid(DBG_RT_REGLEVEL_VIEW, regno,
	                           valp->cv_register.r_ibuffer,
	                           sizeof(valp->cv_register.r_ibuffer));
	if unlikely(buflen > sizeof(valp->cv_register.r_ibuffer))
		return DBX_EINTERN; /* Internal error */
	if unlikely(!buflen)
		return DBX_ENOENT; /* No such register */
	valp->cv_type.ct_typ = ctype_for_register(regno, buflen);
	if unlikely(!valp->cv_type.ct_typ)
		return DBX_EINTERN; /* Internal error */
	ctypeinfo_init(&valp->cv_type.ct_info);
	valp->cv_type.ct_flags    = CTYPEREF_FLAG_NORMAL;
	valp->cv_kind             = CVALUE_KIND_REGISTER;
	valp->cv_register.r_regid = regno;
	if (cexpr_typeonly)
		valp->cv_kind = CVALUE_KIND_VOID;
	++cexpr_stacksize;
	return DBX_EOK;
}


/* Same as above, but only require basic typ
 * information (typ flags, and name are pushed as 0/NULL) */
PUBLIC NONNULL((1)) dbx_errno_t /* Push `*(typ *)addr' */
NOTHROW(FCALL cexpr_pushaddr_simple)(struct ctype *__restrict typ,
                                     NCX void *addr) {
	struct ctyperef ct;
	bzero(&ct, sizeof(ct));
	ct.ct_typ = typ;
	return cexpr_pushaddr(&ct, addr);
}

PUBLIC NONNULL((1)) dbx_errno_t /* Push `(typ)(*(typ const *)data)' */
NOTHROW_NCX(FCALL cexpr_pushdata_simple)(struct ctype *__restrict typ,
                                         NCX void const *data) {
	struct ctyperef ct;
	bzero(&ct, sizeof(ct));
	ct.ct_typ = typ;
	return cexpr_pushdata(&ct, data);
}

PUBLIC NONNULL((1)) dbx_errno_t /* Push `(typ)value' */
NOTHROW(FCALL cexpr_pushint_simple)(struct ctype *__restrict typ,
                                    uintmax_t value) {
	struct ctyperef ct;
	bzero(&ct, sizeof(ct));
	ct.ct_typ = typ;
	return cexpr_pushint(&ct, value);
}



/* Pop the top element from the C expression stack.
 * @return: DBX_EOK:     Success.
 * @return: DBX_EINTERN: Stack was already empty. */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_pop)(void) {
	if unlikely(!cexpr_stacksize)
		return DBX_EINTERN;
	--cexpr_stacksize;
	cvalue_fini(&cexpr_stack[cexpr_stacksize]);
	return DBX_EOK;
}

/* Pop exactly `count' elements from the C expression stack.
 * @return: DBX_EOK:     Success.
 * @return: DBX_EINTERN: Stack has less than `count' elements. */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_pop_n)(size_t count) {
	if unlikely(cexpr_stacksize < count)
		return DBX_EINTERN;
	for (; count; --count) {
		--cexpr_stacksize;
		cvalue_fini(&cexpr_stack[cexpr_stacksize]);
	}
	return DBX_EOK;
}

/* Clear the C expression stack. */
PUBLIC void NOTHROW(FCALL cexpr_empty)(void) {
	while (cexpr_stacksize)
		cexpr_pop();
}

/* Duplicate the C expression top element.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: The stack is empty. */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_dup)(void) {
	dbx_errno_t result;
	struct cvalue *valp;
	if unlikely(!cexpr_stacksize)
		return DBX_EINTERN;
	valp = _cexpr_pushalloc();
	if unlikely(!valp)
		return DBX_ENOMEM;
	result = cvalue_initcopy(valp, &cexpr_stacktop);
	if likely(result == DBX_EOK)
		++cexpr_stacksize;
	return result;
}

#define MOVE_CVALUE(dst, src) memcpy(&(dst), &(src), sizeof(struct cvalue))

/* Swap the two 2 C expression stack elements.
 * @return: DBX_EOK:     Success
 * @return: DBX_EINTERN: The stack size is < 2 */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_swap)(void) {
	struct cvalue temp;
	if unlikely(cexpr_stacksize < 2)
		return DBX_EINTERN;
	MOVE_CVALUE(temp, cexpr_stack[cexpr_stacksize - 1]);
	MOVE_CVALUE(cexpr_stack[cexpr_stacksize - 1], cexpr_stack[cexpr_stacksize - 2]);
	MOVE_CVALUE(cexpr_stack[cexpr_stacksize - 2], temp);
	return DBX_EOK;
}

/* Rotate the top n C expression stack elements left/right.
 * When  `n <= 1', these  calls are  a no-op  in regards to
 * @return: DBX_EOK:     Success
 * @return: DBX_EINTERN: The stack size is < n */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_lrot)(size_t n) {
	struct cvalue temp;
	if unlikely(cexpr_stacksize < n)
		return DBX_EINTERN;
	if unlikely(n <= 1)
		return DBX_EOK; /* no-op */
	MOVE_CVALUE(temp, cexpr_stack[cexpr_stacksize - n]);
	memmovedown(&cexpr_stack[cexpr_stacksize - n],
	            &cexpr_stack[cexpr_stacksize - (n - 1)],
	            n - 1, sizeof(struct cvalue));
	MOVE_CVALUE(cexpr_stack[cexpr_stacksize - 1], temp);
	return DBX_EOK;
}

PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_rrot)(size_t n) {
	struct cvalue temp;
	if unlikely(cexpr_stacksize < n)
		return DBX_EINTERN;
	if unlikely(n <= 1)
		return DBX_EOK; /* no-op */
	MOVE_CVALUE(temp, cexpr_stack[cexpr_stacksize - 1]);
	memmoveup(&cexpr_stack[cexpr_stacksize - (n - 1)],
	          &cexpr_stack[cexpr_stacksize - n],
	          n - 1, sizeof(struct cvalue));
	MOVE_CVALUE(cexpr_stack[cexpr_stacksize - n], temp);
	return DBX_EOK;
}



/* Return a pointer to the data associated with the given `self' stack element.
 * WARNING: The pointer written back to `*presult' may point to arbitrary
 *          user- or out-of-mman memory, meaning that it must be accessed
 *          through use of `dbg_(read|write)memory'!
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Insufficient memory to allocate an intermediate buffer.
 * @return: DBX_EFAULT:  A CFI expression caused a memory fault.
 * @return: DBX_EINTERN: Internal error. */
PUBLIC WUNUSED NONNULL((1, 2)) dbx_errno_t
NOTHROW(FCALL cexpr_getdata_ex)(struct cvalue *__restrict self,
                                NCX byte_t **__restrict presult) {
again:
	switch (self->cv_kind) {

	case CVALUE_KIND_ADDR:
		/* This right here can cause an arbitrary pointer to be written back! */
		*presult = (byte_t *)self->cv_addr;
		break;

	case CVALUE_KIND_DATA:
		*presult = self->cv_data;
		break;

	case CVALUE_KIND_IDATA:
		*presult = self->cv_idata;
		break;

	case CVALUE_KIND_EXPR: {
		size_t bufavail;
		*presult = (byte_t *)self->cv_expr.v_buffer;

		/* Lazily load a CFI expression. */
		if (!*presult) {
			dbx_errno_t error;
			/* Try to load the address of the CFI expression. */
			error = cexpr_cfi_to_address(self);
			if unlikely(error != DBX_EOK)
				return error;
			if (self->cv_kind != CVALUE_KIND_EXPR)
				goto again;
			error = cvalue_rw_expr(self, false);
			if (error == DBX_EOK)
				goto again;
			return error;
		}

		/* Assert  that sufficient space is available for the type in use.
		 * If less space is available, return NULL to prevent writing past
		 * the end of the internal buffer for expressions.
		 * Note though, that this really shouldn't happen... */
		if (OVERFLOW_USUB(self->cv_expr.v_buflen, self->cv_expr.v_bufoff, &bufavail))
			return DBX_EINTERN;
		if (bufavail < ctype_sizeof(self->cv_type.ct_typ))
			return DBX_EINTERN;

		/* Adjust the  buffer pointer  for the  expression-base-offset.
		 * This is used (e.g.) for accessing struct-through-CFI fields. */
		*presult += self->cv_expr.v_bufoff;
	}	break;

	case CVALUE_KIND_IEXPR:
		*presult = self->cv_expr.v_ibuffer + self->cv_expr.v_bufoff;
		break;

	case CVALUE_KIND_REGISTER:
		*presult = self->cv_register.r_ibuffer;
		break;

	default:
		goto nodata;
	}
	return DBX_EOK;
nodata:
	*presult = NULL;
	return DBX_EOK;
}

/* Return a pointer to the data associated with the top expression stack element.
 * If the  stack  is empty,  write-back  a  NULL pointer  and  return  `DBX_EOK'.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Insufficient memory to allocate an intermediate buffer.
 * @return: DBX_EFAULT:  A CFI expression caused a memory fault.
 * @return: DBX_EINTERN: Internal error. */
PUBLIC WUNUSED NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cexpr_getdata)(byte_t **__restrict presult) {
	if unlikely(cexpr_stacksize == 0) {
		*presult = NULL;
		return DBX_EOK;
	}
	return cexpr_getdata_ex(&cexpr_stacktop, presult);
}

/* Return the actual size of the top element of the C expression stack.
 * If the stack is empty,  return `0' instead. (s.a.  `ctype_sizeof()') */
PUBLIC ATTR_PURE WUNUSED size_t
NOTHROW(FCALL cexpr_getsize)(void) {
	if unlikely(cexpr_stacksize == 0)
		return 0;
	return cexpr_getsize_ex(&cexpr_stacktop);
}




/* Return the boolean value of the top stack element.
 * When `cexpr_typeonly' is set to true, this function's return value is undefined.
 * @return: 1:           Value is true.
 * @return: 0:           Value is false.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: The stack is empty.
 * @return: DBX_ESYNTAX: The top stack element cannot be cast to bool. */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_bool)(void) {
	dbx_errno_t error;
	struct ctype *ct;
	byte_t *data;
	size_t datalen;
	if unlikely(!cexpr_stacksize)
		return DBX_EINTERN;
	if (cexpr_stacktop.cv_kind == CVALUE_KIND_VOID)
		return 0;
	ct    = cexpr_stacktop.cv_type.ct_typ;
	error = cexpr_getdata(&data);
	if unlikely(error != DBX_EOK)
		return error;
	datalen = cexpr_getsize();
	switch (CTYPE_KIND_CLASSOF(ct->ct_kind)) {

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_FUNCTION):
		/* This behaves like pointer-to-function */
		return data != NULL;

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_BOOL):
	case CTYPE_KIND_CLASSOF(CTYPE_KIND_ENUM):
	case CTYPE_KIND_CLASSOF(CTYPE_KIND_PTR):
do_check_for_non_zero_byte:
		return buffer_istrue(data, datalen);

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_IEEE754_FLOAT):
		switch (ct->ct_kind) {

		case CTYPE_KIND_IEEE754_FLOAT: {
			float f;
			if (dbg_readmemory(data, &f, sizeof(f)) != 0)
				goto err_fault;
			if (f != 0.0f)
				return 1;
		}	break;

		case CTYPE_KIND_IEEE754_DOUBLE: {
			double d;
			if (dbg_readmemory(data, &d, sizeof(d)) != 0)
				goto err_fault;
			if (d != 0.0)
				return 1;
		}	break;

#ifdef CTYPE_KIND_IEEE854_LONG_DOUBLE
		case CTYPE_KIND_IEEE854_LONG_DOUBLE: {
			__LONGDOUBLE ld;
			if (dbg_readmemory(data, &ld, sizeof(ld)) != 0)
				goto err_fault;
			if (ld != 0.0l)
				return 1;
		}	break;
#endif /* CTYPE_KIND_IEEE854_LONG_DOUBLE */

		default:
			goto do_check_for_non_zero_byte;
		}
		break;

	default:
		return DBX_ESYNTAX;
	}
	return 0; /* false */
err_fault:
	return DBX_EFAULT;
}

/* Cast the stack-top element to `typ'.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: The stack is empty.
 * @return: DBX_ESYNTAX: The top stack element cannot be cast to `typ'. */
PUBLIC NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cexpr_cast)(struct ctyperef const *__restrict typ) {
	dbx_errno_t result;
	struct ctype *old_typ;
	struct ctype *new_typ;
	struct cvalue *top;
	byte_t *data;
again:
	if unlikely(!cexpr_stacksize)
		return DBX_EINTERN;
	top     = &cexpr_stacktop;
	new_typ = typ->ct_typ;
	if (CTYPE_KIND_ISVOID(new_typ->ct_kind)) {
		/* Anything can be cast to void */
		cvalue_fini(top);
		ctyperef_initcopy(&top->cv_type, typ);
		top->cv_kind = CVALUE_KIND_VOID;
		return DBX_EOK;
	}

	/* Make sure that stack-top is an R-value. */
	result = cexpr_rvalue();
	if unlikely(result != DBX_EOK)
		return result;
	if unlikely(top->cv_kind != CVALUE_KIND_DATA &&
	            top->cv_kind != CVALUE_KIND_IDATA &&
	            top->cv_kind != CVALUE_KIND_VOID)
		return DBX_EINTERN; /* Shouldn't happen... */
	data = top->cv_idata;
	if (top->cv_kind == CVALUE_KIND_DATA)
		data = top->cv_data;
	old_typ = top->cv_type.ct_typ;

	/* Check for special case: cast from float. */
	if (CTYPE_KIND_ISFLOAT(old_typ->ct_kind)) {
		if (CTYPE_KIND_ISFLOAT(new_typ->ct_kind)) {
			/* Cast between floating-point types. */
			if (top->cv_kind != CVALUE_KIND_VOID) {
				__LONGDOUBLE value;
				GETFLOAT_BYKIND_NOFAULT(old_typ->ct_kind, data, __LONGDOUBLE, value, return DBX_EINTERN);
				SETFLOAT_BYKIND_NOFAULT(new_typ->ct_kind, data, value, return DBX_EINTERN);
			}
		} else {
			intmax_t floatval = 0;
			/* Re-push the float value as an integer */
			if (top->cv_kind != CVALUE_KIND_VOID) {
				GETFLOAT_BYKIND_NOFAULT(old_typ->ct_kind, data,
				                        intmax_t, floatval,
				                        return DBX_EINTERN);
			}
			result = cexpr_pop();
			if unlikely(result != DBX_EOK)
				return result;
			result = cexpr_pushint_simple(&ctype_intmax_t, (uintmax_t)floatval);
			if unlikely(result != DBX_EOK)
				return result;
			goto again;
		}
		goto set_new_type;
	}

	/* Check for special case: cast to float. */
	if (CTYPE_KIND_ISFLOAT(new_typ->ct_kind)) {
		switch (CTYPE_KIND_CLASSOF(old_typ->ct_kind)) {

		case CTYPE_KIND_CLASSOF(CTYPE_KIND_BOOL):
		case CTYPE_KIND_CLASSOF(CTYPE_KIND_ENUM):
		case CTYPE_KIND_CLASSOF(CTYPE_KIND_PTR): {
			uintmax_t value;
			if (top->cv_kind == CVALUE_KIND_VOID)
				goto set_new_type;
			switch (CTYPE_KIND_SIZEOF(old_typ->ct_kind)) {
			case 1: value = UNALIGNED_GET8(data); break;
			case 2: value = UNALIGNED_GET16(data); break;
			case 4: value = UNALIGNED_GET32(data); break;
			case 8: value = UNALIGNED_GET64(data); break;
			default: return DBX_EINTERN;
			}
			if (CTYPE_KIND_CLASSOF(old_typ->ct_kind) ==
			    CTYPE_KIND_CLASSOF(CTYPE_KIND_BOOL))
				value = !!value;
			/* Write-back the integer value as a float. */
			SETFLOAT_BYKIND_NOFAULT(new_typ->ct_kind, data, value,
			                        return DBX_EINTERN);
			goto set_new_type;
		}	break;

		default:
			return DBX_ESYNTAX;
		}
		goto set_new_type;
	}

	/* All right! With  floating-point out of  the way, move  on to integer  casts.
	 * For this purpose, allow any sort of cast to/from integer/bool/pointer types. */
	if (CTYPE_KIND_ISINT_OR_BOOL_OR_POINTER(old_typ->ct_kind) &&
	    CTYPE_KIND_ISINT_OR_BOOL_OR_POINTER(new_typ->ct_kind))
		goto ok;

	/* All other types of casts aren't allowed. */
	return DBX_ESYNTAX;
ok:
	/* Confirmed (apply value transformations) */
	if (top->cv_kind != CVALUE_KIND_VOID) {
		size_t old_size, new_size;
		old_size = ctype_sizeof(old_typ);
		new_size = ctype_sizeof(new_typ);
		if (new_size != old_size) {
			if (new_size > CVALUE_INLINE_MAXSIZE) {
				/* Must allocate a new heap-buffer */
				byte_t *old_data;
				byte_t *new_data;
				old_data = data;
				if (old_data == top->cv_idata)
					old_data = NULL;
				new_data = (byte_t *)dbx_realloc(old_data, new_size);
				if unlikely(!new_data)
					return DBX_ENOMEM;
				if (data == top->cv_idata)
					memcpy(new_data, data, old_size);
				top->cv_data = data = new_data;
				top->cv_kind = CVALUE_KIND_DATA;
			}

			/* Sign-/Zero-extend the value based on if the old type was signed. */
			result = buffer_extend(data, old_size, new_size,
			                       CTYPE_KIND_ISINT(old_typ->ct_kind) &&
			                       !CTYPE_KIND_INT_ISUNSIGNED(old_typ->ct_kind));
			if unlikely(result != DBX_EOK)
				return result;
		}
	}
set_new_type:
	ctyperef_fini(&top->cv_type);
	ctyperef_initcopy(&top->cv_type, typ);
/*done:*/
	return DBX_EOK;
}

PUBLIC NONNULL((1)) dbx_errno_t
NOTHROW(FCALL cexpr_cast_simple)(struct ctype *__restrict typ) {
	struct ctyperef ct;
	bzero(&ct, sizeof(ct));
	ct.ct_typ = typ;
	return cexpr_cast(&ct);
}



/* Convert  the  top C  expression  stack element  into  an R-value,
 * such that if a potentially pointed-to memory location is changed,
 * then the stack element retains the original value. This  function
 * also promotes array->pointer types.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: The stack is empty.
 * @return: DBX_ESYNTAX: Attempted to promote an address-less array to a pointer. */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_rvalue)(void) {
	struct cvalue *top;
	dbx_errno_t result;
	if unlikely(!cexpr_stacksize)
		return DBX_EINTERN;
	top = &cexpr_stacktop;
	if (CTYPE_KIND_ISARRAY(top->cv_type.ct_typ->ct_kind)) {
		struct ctyperef array_elem_type;
		REF struct ctype *array_elem_pointer_type;
		static_assert(offsetof(struct cvalue, cv_addr) == offsetof(struct cvalue, cv_idata),
		              "This is required so we don't have to copy the old address into the "
		              "new inline-data field");

		/* Try to load the address of a CFI expression. */
		if (top->cv_kind == CVALUE_KIND_EXPR ||
		    top->cv_kind == CVALUE_KIND_IEXPR) {
			result = cexpr_cfi_to_address(top);
			if unlikely(result != DBX_EOK)
				return result;
		}

		/* Check if the address of the top-element can be taken. */
		if (top->cv_kind != CVALUE_KIND_ADDR &&
		    top->cv_kind != CVALUE_KIND_VOID)
			return DBX_ESYNTAX;
		ctypeinfo_init(&array_elem_type.ct_info);
		array_elem_type.ct_typ   = top->cv_type.ct_typ->ct_array.ca_elem;
		array_elem_type.ct_flags = top->cv_type.ct_flags;
		array_elem_pointer_type  = ctype_ptr(&array_elem_type, dbg_current_sizeof_pointer());
		if unlikely(!array_elem_pointer_type)
			return DBX_ENOMEM;
		ctyperef_fini(&top->cv_type);
		ctypeinfo_init(&top->cv_type.ct_info);
		top->cv_type.ct_typ   = array_elem_pointer_type; /* Inherit reference */
		top->cv_type.ct_flags = CTYPEREF_FLAG_NORMAL;
		if (top->cv_kind == CVALUE_KIND_ADDR)
			top->cv_kind = CVALUE_KIND_IDATA; /* Re-use the address-field as inline-rvalue-data. */
		return DBX_EOK;
	}
again_switch_kind:
	switch (top->cv_kind) {

	case CVALUE_KIND_VOID:
		/* No-op */
		break;

	case CVALUE_KIND_EXPR: {
		byte_t *data;
		result = cexpr_getdata(&data);
		if unlikely(result != DBX_EOK)
			return result;
		if (top->cv_kind != CVALUE_KIND_EXPR)
			goto again_switch_kind;

		/* Just inherit the expression buffer. */
		cvalue_cfiexpr_fini(&top->cv_expr.v_expr);
		if (top->cv_expr.v_bufoff != 0) {
			/* Deal with custom buffer-offsets. */
			size_t datalen = ctype_sizeof(top->cv_type.ct_typ);
			if (datalen <= sizeof(top->cv_idata)) {
				memcpy(top->cv_idata, data, datalen);
				dbx_free(top->cv_expr.v_buffer);
				top->cv_kind = CVALUE_KIND_IDATA;
				break;
			}
			memmovedown(top->cv_expr.v_buffer, data, datalen);
			data = (byte_t *)dbx_realloc(top->cv_expr.v_buffer, datalen);
			if unlikely(!data)
				data = (byte_t *)top->cv_expr.v_buffer;
		}
		top->cv_kind = CVALUE_KIND_DATA;
		top->cv_data = (byte_t *)data;
	}	break;

	case CVALUE_KIND_ADDR:
	case CVALUE_KIND_IEXPR:
	case CVALUE_KIND_REGISTER: {
		uintptr_t newkind;
		byte_t *buffer;
		size_t buflen;
		buflen  = ctype_sizeof(top->cv_type.ct_typ);
		buffer  = top->cv_idata;
		newkind = CVALUE_KIND_IDATA;
		if (buflen > CVALUE_INLINE_MAXSIZE) {
			newkind = CVALUE_KIND_DATA;
			buffer  = (byte_t *)dbx_malloc(buflen);
			if unlikely(!buffer)
				return DBX_ENOMEM;
		}
		result = DBX_EOK;
		switch (top->cv_kind) {

		case CVALUE_KIND_ADDR:
			if (dbg_readmemory(top->cv_addr, buffer, buflen) != 0)
				goto err_fault;
			break;

		case CVALUE_KIND_IEXPR:
			cvalue_cfiexpr_fini(&top->cv_expr.v_expr);
			memmove(buffer, top->cv_expr.v_ibuffer, buflen);
			break;

		case CVALUE_KIND_REGISTER:
			memcpy(buffer, top->cv_register.r_ibuffer, buflen);
			break;

		default:
			__builtin_unreachable();
		}
		if unlikely(result != DBX_EOK) {
			__IF0 {
err_fault:
				result = DBX_EFAULT;
			}
			if (newkind == CVALUE_KIND_DATA)
				dbx_free(buffer);
			return result;
		}
		top->cv_kind = newkind;
		if (newkind == CVALUE_KIND_DATA)
			top->cv_data = buffer;
	}	break;

	case CVALUE_KIND_DATA:
	case CVALUE_KIND_IDATA:
		/* Already an R-value! */
		break;

	default:
		return DBX_EINTERN;
	}
	return DBX_EOK;
}

/* Force R-value, and promote the top C-expression-stack element:
 *   - Convert `int[42]'        -> `int *'     (already done by `cexpr_rvalue()')
 *   - Convert `int(int, long)' -> `int(*)(int, long)'
 *   - Convert `char'           -> `int'
 *   - Convert `short'          -> `int'
 *   - Convert `unsigned char'  -> `unsigned int'
 *   - Convert `unsigned short' -> `unsigned int'
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: The stack is empty.
 * @return: DBX_ESYNTAX: Attempted to promote an address-less array to a pointer. */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_promote)(void) {
	struct cvalue *top;
	dbx_errno_t result;
	struct ctype *old_type;
	result = cexpr_rvalue();
	if unlikely(result != DBX_EOK)
		return result;
	if unlikely(!cexpr_stacksize)
		return DBX_EINTERN; /* Shouldn't happen */
	top = &cexpr_stacktop;
	if unlikely(top->cv_kind != CVALUE_KIND_DATA &&
	            top->cv_kind != CVALUE_KIND_IDATA &&
	            top->cv_kind != CVALUE_KIND_VOID)
		return DBX_EINTERN; /* Shouldn't happen */
	old_type = top->cv_type.ct_typ;
	if (CTYPE_KIND_ISINT_OR_BOOL(old_type->ct_kind) &&
	    CTYPE_KIND_SIZEOF(old_type->ct_kind) < sizeof(int))
		return cexpr_cast_simple(&ctype_int); /* Cast to `int' */
	if (old_type->ct_kind == CTYPE_KIND_IEEE754_FLOAT)
		return cexpr_cast_simple(&ctype_ieee754_double); /* Promote `float' to `double' */
	return DBX_EOK;
}


/* Access a field of a struct/union object in the C expression stack top element.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: The C expression stack is empty.
 * @return: DBX_ESYNTAX: The C expression stack top-element isn't a struct/union.
 * @return: DBX_ENOENT:  The given `name' doesn't name a member of the top-element struct. */
PUBLIC NONNULL((1)) dbx_errno_t
NOTHROW_NCX(FCALL cexpr_field)(NCX char const *name,
                               size_t namelen) {
	dbx_errno_t result;
	struct ctyperef field_type;
	struct cvalue *top;
	ptrdiff_t field_offset;
	size_t field_size, temp, container_size;
	if unlikely(!cexpr_stacksize)
		return DBX_EINTERN;
	top    = &cexpr_stacktop;
	result = ctype_struct_getfield(top->cv_type.ct_typ,
	                               name,
	                               namelen,
	                               &field_type,
	                               &field_offset);
	if unlikely(result != DBX_EOK)
		return result;
	field_size = ctype_sizeof(field_type.ct_typ);

	/* Make sure that the field is in-bounds of the structure as a whole. */
	if unlikely(OVERFLOW_UADD(field_offset, field_size, &temp))
		return DBX_EINTERN;
	container_size = ctype_sizeof(top->cv_type.ct_typ);

	/* Allow zero-sized structs, which is indicative of containing a variable-length array. */
	if unlikely(container_size && temp > container_size)
		return DBX_EINTERN;
	switch (top->cv_kind) {

	case CVALUE_KIND_VOID:
		break;

	case CVALUE_KIND_ADDR:
		top->cv_addr = (byte_t *)top->cv_addr + field_offset;
		break;

	case CVALUE_KIND_EXPR:
	case CVALUE_KIND_IEXPR:
		top->cv_expr.v_bufoff += field_offset;
		break;

	case CVALUE_KIND_DATA: {
		byte_t *oldbuf = top->cv_data;
		if (field_size <= CVALUE_INLINE_MAXSIZE) {
			/* Switch over to the inline buffer */
			memcpy(top->cv_idata, oldbuf + field_offset, field_size);
			top->cv_kind = CVALUE_KIND_IDATA;
			dbx_free(oldbuf);
		} else {
			byte_t *newbuf;
			memmovedown(oldbuf, oldbuf + field_offset, field_size);
			/* Try to truncate the used buffer size. */
			newbuf = (byte_t *)dbx_realloc(oldbuf, field_size);
			if likely(newbuf)
				top->cv_data = newbuf;
		}
	}	break;

	case CVALUE_KIND_IDATA:
		memmovedown(&top->cv_idata[0],
		            &top->cv_idata[field_offset],
		            field_size);
		break;

	default:
		result = DBX_EINTERN;
		break;
	}
	if unlikely(result != DBX_EOK) {
		ctyperef_fini(&field_type);
		return result;
	}

	/* Copy over the field type into the C-value. */
	ctyperef_fini(&top->cv_type);
	memcpy(&top->cv_type, &field_type, sizeof(struct ctyperef));
	return DBX_EOK;
}


/* Ref/Deref the c-expression-stack top element.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_ESYNTAX: Operation not allowed.
 * @return: DBX_ENOADDR: Cannot take address of optimized variable.
 * @return: DBX_EINTERN: The C expression stack is empty. */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_ref)(void) {
	struct cvalue *top;
	struct ctype *typ;
	static_assert(offsetof(struct cvalue, cv_addr) == offsetof(struct cvalue, cv_idata),
	              "This is required so we don't have to copy the old address into the "
	              "new inline-data field");
	if unlikely(!cexpr_stacksize)
		return DBX_EINTERN;
	top = &cexpr_stacktop;

	/* Try to load the address of a CFI expression. */
	if (top->cv_kind == CVALUE_KIND_EXPR ||
	    top->cv_kind == CVALUE_KIND_IEXPR) {
		dbx_errno_t error;
		error = cexpr_cfi_to_address(top);
		if unlikely(error != DBX_EOK)
			return error;
	}

	/* Make sure that the top-element is located in-memory. */
	if (top->cv_kind != CVALUE_KIND_ADDR &&
	    top->cv_kind != CVALUE_KIND_VOID) {
		/* Return  a special error when we can't
		 * take the address of a CFI expression. */
		if (top->cv_kind == CVALUE_KIND_EXPR ||
		    top->cv_kind == CVALUE_KIND_IEXPR)
			return DBX_ENOADDR;
		return DBX_ESYNTAX;
	}

	/* Construct the pointer-type. */
	typ = ctype_ptr(&top->cv_type, dbg_current_sizeof_pointer());
	if unlikely(!typ)
		return DBX_ENOMEM;

	/* Switch over to inline-data, thus re-using the object address as the inline pointer value. */
	ctyperef_fini(&top->cv_type);
	bzero(&top->cv_type, sizeof(top->cv_type));
	top->cv_type.ct_typ = typ; /* Inherit reference. */
	if (top->cv_kind == CVALUE_KIND_ADDR)
		top->cv_kind = CVALUE_KIND_IDATA;
	return DBX_EOK;
}

PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_deref)(void) {
	dbx_errno_t result;
	struct cvalue *top;
	struct ctype *typ;
	byte_t *pointed_to_addr;

	/* Force an R-value expression (which we can dereference) */
	result = cexpr_rvalue();
	if unlikely(result != DBX_EOK)
		return result;
	if unlikely(!cexpr_stacksize)
		return DBX_EINTERN;
	top = &cexpr_stacktop;

	/* Make sure that `top' has pointer typing.
	 * Note  that we need  to check for arrays  here, since those will
	 * have already been promoted to base-pointers by `cexpr_rvalue()' */
	typ = top->cv_type.ct_typ;
	if unlikely(!CTYPE_KIND_ISPOINTER(typ->ct_kind))
		return DBX_ESYNTAX;
	switch (top->cv_kind) {

	case CVALUE_KIND_VOID:
		goto do_set_type;

	case CVALUE_KIND_IDATA:
#ifdef __ARCH_HAVE_COMPAT
		if (CTYPE_KIND_SIZEOF(typ->ct_kind) == sizeof(compat_uintptr_t)) {
			pointed_to_addr = (byte_t *)(uintptr_t)(*(compat_uintptr_t *)top->cv_idata);
		} else
#endif /* __ARCH_HAVE_COMPAT */
		{
			pointed_to_addr = *(byte_t **)top->cv_idata;
		}
		break;

	case CVALUE_KIND_DATA:
#ifdef __ARCH_HAVE_COMPAT
		if (CTYPE_KIND_SIZEOF(typ->ct_kind) == sizeof(compat_uintptr_t)) {
			pointed_to_addr = (byte_t *)(uintptr_t)(*(compat_uintptr_t *)top->cv_data);
		} else
#endif /* __ARCH_HAVE_COMPAT */
		{
			pointed_to_addr = *(byte_t **)top->cv_data;
		}
		dbx_free(top->cv_data);
		break;

	default:
		return DBX_EINTERN; /* Shouldn't happen... */
	}

	/* switch back to referencing a memory location. */
	top->cv_addr = pointed_to_addr;
	top->cv_kind = CVALUE_KIND_ADDR;

	/* Replace the top item's pointer-type with the pointed-to type. */
do_set_type:
	ctypeinfo_fini(&top->cv_type.ct_info); /* inherit:`top->cv_type.ct_typ' in `typ' */
	ctyperef_initcopy(&top->cv_type, &typ->ct_pointer.cp_base);
	decref(typ);
	return DBX_EOK;
}


PRIVATE NONNULL((1)) void
NOTHROW(FCALL cvalue_setbool)(struct cvalue *__restrict self,
                              bool value) {
	if (self->cv_kind == CVALUE_KIND_VOID)
		return;
	assert(self->cv_kind == CVALUE_KIND_DATA ||
	       self->cv_kind == CVALUE_KIND_IDATA);
	if (self->cv_kind == CVALUE_KIND_DATA)
		dbx_free(self->cv_data);
	self->cv_kind = CVALUE_KIND_IDATA;
	bzero(self->cv_idata, sizeof(self->cv_idata));
	ctyperef_fini(&self->cv_type);
	bzero(&self->cv_type, sizeof(self->cv_type));
	self->cv_type.ct_typ = incref(&ctype_bool);
	*(bool *)self->cv_idata = value;
}

PRIVATE NONNULL((1)) void
NOTHROW(FCALL cvalue_setptrdiff_t)(struct cvalue *__restrict self,
                                   ptrdiff_t value) {
	if (self->cv_kind == CVALUE_KIND_VOID)
		return;
	assert(self->cv_kind == CVALUE_KIND_DATA ||
	       self->cv_kind == CVALUE_KIND_IDATA);
	if (self->cv_kind == CVALUE_KIND_DATA)
		dbx_free(self->cv_data);
	self->cv_kind = CVALUE_KIND_IDATA;
	bzero(self->cv_idata, sizeof(self->cv_idata));
	ctyperef_fini(&self->cv_type);
	bzero(&self->cv_type, sizeof(self->cv_type));
	self->cv_type.ct_typ = incref(&ctype_ptrdiff_t);
	*(ptrdiff_t *)self->cv_idata = value;
}


/* Perform a unary operation `op' on the top C expression stack element.
 * NOTE: This   function   automatically   performs   type   promotions.
 * @param: op: One of:
 *             '+': Assert integer type / cast enum to integer.
 *             '-': Negate a value.
 *             '~': Bit-wise not.
 *             '!': Logical  not.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: The stack is empty or invalid `op'.
 * @return: DBX_EINTERN: `op' is not one of the above constants.
 * @return: DBX_ESYNTAX: `op' not allowed here. */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_op1)(unsigned int op) {
	dbx_errno_t result;
	struct cvalue *top;
	struct ctype *typ;
	byte_t *data;
	result = cexpr_promote(); /* R-value+promote */
	if unlikely(result != DBX_EOK)
		return result;
	if unlikely(!cexpr_stacksize)
		return DBX_EINTERN; /* Shouldn't happen */
	top = &cexpr_stacktop;
	if unlikely(top->cv_kind != CVALUE_KIND_DATA &&
	            top->cv_kind != CVALUE_KIND_IDATA &&
	            top->cv_kind != CVALUE_KIND_VOID)
		return DBX_EINTERN; /* Shouldn't happen */
	typ  = top->cv_type.ct_typ;
	data = top->cv_idata;
	if (top->cv_kind == CVALUE_KIND_DATA) {
		data = top->cv_data;
	} else if (top->cv_kind == CVALUE_KIND_VOID) {
		data = NULL;
	}
	switch (op) {

	case '+':
		if (!CTYPE_KIND_ISINT_OR_BOOL_OR_FLOAT(typ->ct_kind))
			return DBX_ESYNTAX;
		break;

	case '-': {
		if (!CTYPE_KIND_ISINT_OR_BOOL_OR_FLOAT(typ->ct_kind))
			return DBX_ESYNTAX;
		switch (CTYPE_KIND_CLASSOF(typ->ct_kind)) {

		case CTYPE_KIND_CLASSOF(CTYPE_KIND_BOOL):
			/* No-op for boolean values. */
			break;

		case CTYPE_KIND_CLASSOF(CTYPE_KIND_ENUM):
			/* Drop the enum-part and force signed. */
			if (CTYPE_KIND_ISENUM(typ->ct_kind))
				cmoduledip_fini(&typ->ct_enum);
#define CTYPE_KIND_SIGNBIT (CTYPE_KIND_S8 ^ CTYPE_KIND_U8)
#define CTYPE_KIND_ENUMBIT ((CTYPE_KIND_ENUM8 & ~CTYPE_KIND_SIGNBIT) ^ (CTYPE_KIND_U8 & ~CTYPE_KIND_SIGNBIT))
			typ->ct_kind &= ~(CTYPE_KIND_SIGNBIT | CTYPE_KIND_ENUMBIT);
			/* Implement -x as `~(x - 1)' */
			if (data) {
				buffer_dec_nofault(data, CTYPE_KIND_SIZEOF(typ->ct_kind));
				buffer_inv_nofault(data, CTYPE_KIND_SIZEOF(typ->ct_kind));
			}
			break;

		case CTYPE_KIND_CLASSOF(CTYPE_KIND_IEEE754_FLOAT):
			if (data) {
				__LONGDOUBLE ld;
				GETFLOAT_BYKIND_NOFAULT(typ->ct_kind, data,
				                        __LONGDOUBLE, ld,
				                        return DBX_EINTERN);
				ld = -ld;
				SETFLOAT_BYKIND_NOFAULT(typ->ct_kind, data, ld,
				                        return DBX_EINTERN);
			}
			break;

		default:
			return DBX_EINTERN;
		}
	}	break;

	case '~':
		if (!CTYPE_KIND_ISINT_OR_BOOL(typ->ct_kind))
			return DBX_ESYNTAX;
		if (CTYPE_KIND_ISINT(typ->ct_kind)) {
			/* Drop the enum-part and force signed. */
			if (CTYPE_KIND_ISENUM(typ->ct_kind))
				cmoduledip_fini(&typ->ct_enum);
			typ->ct_kind &= ~(CTYPE_KIND_SIGNBIT | CTYPE_KIND_ENUMBIT);
		}
		if (data)
			buffer_inv_nofault(data, CTYPE_KIND_SIZEOF(typ->ct_kind));
		break;

	case '!':
		result = cexpr_bool();
		if unlikely(DBX_EISERR(result))
			return result;
		if (data)
			cvalue_setbool(top, !result);
		break;

	default:
		return DBX_EINTERN;
	}
	return DBX_EOK;
}


/* Perform a binary operation `op' on the top 2 C expression stack elements.
 * As  far as operands go, STACK.TOP is  RHS and STACK.TOP-1 is LHS (meaning
 * that LHS must be pushed first, and RHS second)
 * NOTE: This function automatically performs type promotions.
 * @param: op: One of:
 *             '+':                      Add.
 *             '-':                      Subtract.
 *             '*':                      Multiply.
 *             '/':                      Divide.
 *             '%':                      Remainder (modulo).
 *             '&':                      Bit-wise        and
 *             '|':                      Bit-wise         or
 *             '^':                      Bit-wise        xor
 *             CTOKEN_TOK_LANGLE_LANGLE: Shift-left
 *             CTOKEN_TOK_RANGLE_RANGLE: Shift-right
 *             CTOKEN_TOK_EQUALS_EQUALS: Equals
 *             CTOKEN_TOK_XCLAIM_EQUALS: Not-Equals
 *             '<':                      Lower
 *             CTOKEN_TOK_LANGLE_EQUALS: Lower-or-equal
 *             '>':                      Greater
 *             CTOKEN_TOK_RANGLE_EQUALS: Greater-or-equal
 * @return: DBX_EOK:      Success.
 * @return: DBX_ENOMEM:   Out of memory.
 * @return: DBX_EDIVZERO: `op' is `/' or `%' and the rhs-operand is equal to 0
 * @return: DBX_EINTERN:  The stack contains less than 2 elements or invalid `op'.
 * @return: DBX_EINTERN:  `op' is not one of the above constants.
 * @return: DBX_ESYNTAX:  `op' not allowed for its operands. */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_op2)(unsigned int op) {
	dbx_errno_t result;
	struct cvalue *lhs, *rhs;
	struct ctype *lhs_typ, *rhs_typ;
	byte_t *lhs_data, *rhs_data;
	result = cexpr_promote(); /* R-value+promote */
	if unlikely(result != DBX_EOK)
		return result;
	result = cexpr_swap();
	if unlikely(result != DBX_EOK)
		return result;
	result = cexpr_promote(); /* R-value+promote */
	if unlikely(result != DBX_EOK)
		return result;
	result = cexpr_swap();
	if unlikely(result != DBX_EOK)
		return result;
again:
	if unlikely(cexpr_stacksize < 2)
		return DBX_EINTERN; /* Shouldn't happen */
	lhs = &cexpr_stack[cexpr_stacksize - 2];
	rhs = &cexpr_stack[cexpr_stacksize - 1];
	if unlikely(lhs->cv_kind != CVALUE_KIND_DATA &&
	            lhs->cv_kind != CVALUE_KIND_IDATA &&
	            rhs->cv_kind != CVALUE_KIND_VOID)
		return DBX_EINTERN; /* Shouldn't happen */
	if unlikely(rhs->cv_kind != CVALUE_KIND_DATA &&
	            rhs->cv_kind != CVALUE_KIND_IDATA &&
	            rhs->cv_kind != CVALUE_KIND_VOID)
		return DBX_EINTERN; /* Shouldn't happen */
	lhs_typ  = lhs->cv_type.ct_typ;
	rhs_typ  = rhs->cv_type.ct_typ;
	lhs_data = lhs->cv_idata;
	rhs_data = rhs->cv_idata;
	if (lhs->cv_kind == CVALUE_KIND_DATA) {
		lhs_data = lhs->cv_data;
	} else if (lhs->cv_kind == CVALUE_KIND_VOID) {
		lhs_data = NULL;
	}
	if (rhs->cv_kind == CVALUE_KIND_DATA) {
		rhs_data = rhs->cv_data;
	} else if (rhs->cv_kind == CVALUE_KIND_VOID) {
		rhs_data = NULL;
	}

	/* Swap operands such that a float always appears left. */
	if (CTYPE_KIND_ISFLOAT(lhs_typ->ct_kind)) {
		__LONGDOUBLE lhs_value, rhs_value;
		if (!rhs_data) {
			rhs_value = 0.0L;
		} else if (CTYPE_KIND_ISFLOAT(rhs_typ->ct_kind)) {
			GETFLOAT_BYKIND_NOFAULT(rhs_typ->ct_kind, rhs_data,
			                        __LONGDOUBLE, rhs_value,
			                        return DBX_EINTERN);
		} else {
			if (!CTYPE_KIND_ISINT_OR_BOOL(rhs_typ->ct_kind))
				return DBX_ESYNTAX;
			if (CTYPE_KIND_ISBOOL(rhs_typ->ct_kind)) {
				rhs_value = 0.0L;
				if (buffer_istrue(rhs_data, CTYPE_KIND_SIZEOF(rhs_typ->ct_kind)))
					rhs_value = 1.0L;
			} else {
				uintmax_t irhs_value;
				switch (CTYPE_KIND_SIZEOF(rhs_typ->ct_kind)) {
				case 1: irhs_value = UNALIGNED_GET8(rhs_data); break;
				case 2: irhs_value = UNALIGNED_GET16(rhs_data); break;
				case 4: irhs_value = UNALIGNED_GET32(rhs_data); break;
				case 8: irhs_value = UNALIGNED_GET64(rhs_data); break;
				default: return DBX_EINTERN;
				}
				rhs_value = (__LONGDOUBLE)irhs_value;
			}
		}
		if (lhs_data) {
			GETFLOAT_BYKIND_NOFAULT(lhs_typ->ct_kind, lhs_data,
			                        __LONGDOUBLE, lhs_value,
			                        return DBX_EINTERN);
		} else {
			lhs_value = 0.0L;
		}
		switch (op) {

		case '+':
			lhs_value = lhs_value + rhs_value;
			break;

		case '-':
			lhs_value = lhs_value - rhs_value;
			break;

		case '*':
			lhs_value = lhs_value * rhs_value;
			break;

		case '/':
			/* Because of floats, divide-by-zero won't fault, but would become NaN */
			lhs_value = lhs_value / rhs_value;
			break;

		case CTOKEN_TOK_EQUALS_EQUALS:
		case CTOKEN_TOK_XCLAIM_EQUALS:
		case '<':
		case CTOKEN_TOK_LANGLE_EQUALS:
		case '>':
		case CTOKEN_TOK_RANGLE_EQUALS: {
			bool retval;
			switch (op) {
			case CTOKEN_TOK_EQUALS_EQUALS: retval = lhs_value == rhs_value; break;
			case CTOKEN_TOK_XCLAIM_EQUALS: retval = lhs_value != rhs_value; break;
			case '<': /*                */ retval = lhs_value < rhs_value; break;
			case CTOKEN_TOK_LANGLE_EQUALS: retval = lhs_value <= rhs_value; break;
			case '>': /*                */ retval = lhs_value > rhs_value; break;
			case CTOKEN_TOK_RANGLE_EQUALS: retval = lhs_value >= rhs_value; break;
			default: __builtin_unreachable();
			}
			if (lhs_data)
				cvalue_setbool(lhs, retval);
		}	break;

		case '%':
		case '&':
		case '|':
		case '^':
		case CTOKEN_TOK_LANGLE_LANGLE:
		case CTOKEN_TOK_RANGLE_RANGLE:
			return DBX_ESYNTAX;

		default:
			return DBX_EINTERN;
		}
		/* Write-back the result. */
		if (lhs_data) {
			SETFLOAT_BYKIND_NOFAULT(lhs_typ->ct_kind,
			                        lhs_data, lhs_value,
			                        return DBX_EINTERN);
		}
		goto done_pop_rhs;
	}
	if (CTYPE_KIND_ISFLOAT(rhs_typ->ct_kind)) {
		/* Cast the left operand to the type of the right one. */
		result = cexpr_swap();
		if unlikely(result != DBX_EOK)
			return result;
		result = cexpr_cast_simple(rhs_typ);
		if unlikely(result != DBX_EOK)
			return result;
swap_operands_and_again:
		result = cexpr_swap();
		if unlikely(result != DBX_EOK)
			return result;
		goto again;
	}

	/* And with that, everything relating to floating-point types is off the table.
	 * Next up: Deal with pointer types. */
	if (CTYPE_KIND_ISPOINTER(lhs_typ->ct_kind)) {
		uintptr_t lhs_value, rhs_value;
		/* Only integer, bool or pointers can be used with pointers. */
		if (!CTYPE_KIND_ISINT_OR_BOOL_OR_POINTER(rhs_typ->ct_kind))
			return DBX_ESYNTAX;
		if (!lhs_data) {
			lhs_value = 0;
		} else {
			switch (CTYPE_KIND_SIZEOF(lhs_typ->ct_kind)) {
			case 1: lhs_value = UNALIGNED_GET8(lhs_data); break;
			case 2: lhs_value = UNALIGNED_GET16(lhs_data); break;
			case 4: lhs_value = UNALIGNED_GET32(lhs_data); break;
			case 8: lhs_value = UNALIGNED_GET64(lhs_data); break;
			default: return DBX_EINTERN;
			}
		}
		if (!rhs_data) {
			rhs_value = 0;
		} else if (CTYPE_KIND_ISBOOL(rhs_typ->ct_kind)) {
			rhs_value = buffer_istrue(rhs_data, CTYPE_KIND_SIZEOF(rhs_typ->ct_kind)) ? 1 : 0;
		} else {
			switch (CTYPE_KIND_SIZEOF(rhs_typ->ct_kind)) {
			case 1: rhs_value = UNALIGNED_GET8(rhs_data); break;
			case 2: rhs_value = UNALIGNED_GET16(rhs_data); break;
			case 4: rhs_value = UNALIGNED_GET32(rhs_data); break;
			case 8: rhs_value = UNALIGNED_GET64(rhs_data); break;
			default: return DBX_EINTERN;
			}
			if (CTYPE_KIND_ISINT(rhs_typ->ct_kind) && !CTYPE_KIND_INT_ISUNSIGNED(rhs_typ->ct_kind)) {
				/* Must sign-extend loaded values */
				switch (CTYPE_KIND_SIZEOF(rhs_typ->ct_kind)) {
				case 1: rhs_value = (uintmax_t)(intmax_t)(int8_t)(uint8_t)rhs_value; break;
				case 2: rhs_value = (uintmax_t)(intmax_t)(int16_t)(uint16_t)rhs_value; break;
				case 4: rhs_value = (uintmax_t)(intmax_t)(int32_t)(uint32_t)rhs_value; break;
				case 8: rhs_value = (uintmax_t)(intmax_t)(int64_t)(uint64_t)rhs_value; break;
				default: return DBX_EINTERN;
				}
			}
		}
		if (CTYPE_KIND_ISPOINTER(rhs_typ->ct_kind)) {
			/* Make sure that pointer bases are identical. */
			if (!ctype_equal(lhs_typ->ct_pointer.cp_base.ct_typ,
			                 rhs_typ->ct_pointer.cp_base.ct_typ))
				return DBX_ESYNTAX;

			/* Only '-' and compare operators can be used when both operands are pointers. */
do_pointer_pointer_op:
			switch (op) {

			case '-': {
				size_t sizeof_base;
				sizeof_base = ctype_sizeof(lhs_typ->ct_pointer.cp_base.ct_typ);
				lhs_value -= rhs_value;
				if (sizeof_base)
					lhs_value /= sizeof_base;
				/* Write-back as a `ptrdiff_t' value. */
				cvalue_setptrdiff_t(lhs, (ptrdiff_t)lhs_value);
				goto done_pop_rhs;
			}	break;

			case '+':
			case '*':
			case '/':
			case '%':
			case '&':
			case '|':
			case '^':
			case CTOKEN_TOK_LANGLE_LANGLE:
			case CTOKEN_TOK_RANGLE_RANGLE:
				return DBX_ESYNTAX;

			case CTOKEN_TOK_EQUALS_EQUALS:
			case CTOKEN_TOK_XCLAIM_EQUALS:
			case '<':
			case CTOKEN_TOK_LANGLE_EQUALS:
			case '>':
			case CTOKEN_TOK_RANGLE_EQUALS: {
				/* Handle the case of comparing pointers. */
				bool retval;
				if (!lhs_data)
					goto done_pop_rhs;
				switch (op) {
				case CTOKEN_TOK_EQUALS_EQUALS: retval = lhs_value == rhs_value; break;
				case CTOKEN_TOK_XCLAIM_EQUALS: retval = lhs_value != rhs_value; break;
				case '<': /*                */ retval = lhs_value < rhs_value; break;
				case CTOKEN_TOK_LANGLE_EQUALS: retval = lhs_value <= rhs_value; break;
				case '>': /*                */ retval = lhs_value > rhs_value; break;
				case CTOKEN_TOK_RANGLE_EQUALS: retval = lhs_value >= rhs_value; break;
				default: __builtin_unreachable();
				}
				cvalue_setbool(lhs, retval);
				goto done_pop_rhs;
			}	break;

			default:
				return DBX_EINTERN;
			}
		} else {
			switch (op) {

			case '-':
				rhs_value = 0 - rhs_value;
				ATTR_FALLTHROUGH
			case '+':
				/* Multiply `rhs_value' by the size of the underlying type of `lhs' */
				rhs_value *= ctype_sizeof(lhs_typ->ct_pointer.cp_base.ct_typ);
				lhs_value += rhs_value;
				break;

			case '*':
			case '/':
			case '%':
			case '&':
			case '|':
			case '^':
			case CTOKEN_TOK_LANGLE_LANGLE:
			case CTOKEN_TOK_RANGLE_RANGLE:
				return DBX_ESYNTAX;

			case CTOKEN_TOK_EQUALS_EQUALS:
			case CTOKEN_TOK_XCLAIM_EQUALS:
			case '<':
			case CTOKEN_TOK_LANGLE_EQUALS:
			case '>':
			case CTOKEN_TOK_RANGLE_EQUALS:
				/* Handle  PTR  <=>  INT  the  same  as  PTR  <=> PTR.
				 * Normally, C only allows this when INT is a constant
				 * literal  equal  to  `0', but  for  convenience, and
				 * simplicity, we always allow such a comparison to be
				 * made. */
				goto do_pointer_pointer_op;

			default:
				return DBX_EINTERN;
			}
		}

		/* Write-back the LHS-value. */
		if (lhs_data) {
			switch (CTYPE_KIND_SIZEOF(lhs_typ->ct_kind)) {
			case 1: UNALIGNED_SET8(lhs_data, (uint8_t)lhs_value); break;
			case 2: UNALIGNED_SET16(lhs_data, (uint16_t)lhs_value); break;
			case 4: UNALIGNED_SET32(lhs_data, (uint32_t)lhs_value); break;
			case 8: UNALIGNED_SET64(lhs_data, (uint64_t)lhs_value); break;
			default: return DBX_EINTERN;
			}
		}
		goto done_pop_rhs;
	}

	if (CTYPE_KIND_ISPOINTER(rhs_typ->ct_kind)) {
		switch (op) {

		case '+':
			/* NON_POINTER + POINTER -> POINTER + NON_POINTER */
			goto swap_operands_and_again;

			/* We know that `lhs_typ' isn't a pointer, but `rhs_typ' is.
			 * For  the comparison operators,  simply flip the operands,
			 * as well as  the operation  so we can  re-use the  special
			 * handling already done when the LHS-operand is a  pointer. */
		case CTOKEN_TOK_EQUALS_EQUALS:
		case CTOKEN_TOK_XCLAIM_EQUALS: goto swap_operands_and_again;
		case '<': /*                */ op = '>'; /*                */ goto swap_operands_and_again;
		case CTOKEN_TOK_LANGLE_EQUALS: op = CTOKEN_TOK_RANGLE_EQUALS; goto swap_operands_and_again;
		case '>': /*                */ op = '<'; /*                */ goto swap_operands_and_again;
		case CTOKEN_TOK_RANGLE_EQUALS: op = CTOKEN_TOK_LANGLE_EQUALS; goto swap_operands_and_again;

		case '-':
		case '*':
		case '/':
		case '%':
		case '&':
		case '|':
		case '^':
		case CTOKEN_TOK_LANGLE_LANGLE:
		case CTOKEN_TOK_RANGLE_RANGLE:
			/* None of these combinations are allowed. */
			return DBX_ESYNTAX;

		default:
			/* Bad `op' */
			return DBX_EINTERN;
		}
		__builtin_unreachable();
	}

	/* The last case: Operations with bool/integer/enum */
	if (!CTYPE_KIND_ISINT_OR_BOOL(lhs_typ->ct_kind))
		return DBX_ESYNTAX;
	if (!CTYPE_KIND_ISINT_OR_BOOL(rhs_typ->ct_kind))
		return DBX_ESYNTAX;
	{
		uintmax_t lhs_value, rhs_value;
		bool is_signed = false;
		/* Load the LHS-value. */
		if (!lhs_data) {
			lhs_value = 0;
		} else if (CTYPE_KIND_ISBOOL(lhs_typ->ct_kind)) {
			lhs_value = buffer_istrue(lhs_data, CTYPE_KIND_SIZEOF(lhs_typ->ct_kind)) ? 1 : 0;
		} else {
			switch (CTYPE_KIND_SIZEOF(lhs_typ->ct_kind)) {
			case 1: lhs_value = UNALIGNED_GET8(lhs_data); break;
			case 2: lhs_value = UNALIGNED_GET16(lhs_data); break;
			case 4: lhs_value = UNALIGNED_GET32(lhs_data); break;
			case 8: lhs_value = UNALIGNED_GET64(lhs_data); break;
			default: return DBX_EINTERN;
			}
			if (!CTYPE_KIND_INT_ISUNSIGNED(lhs_typ->ct_kind)) {
				/* Must sign-extend loaded values */
				switch (CTYPE_KIND_SIZEOF(lhs_typ->ct_kind)) {
				case 1: lhs_value = (uintmax_t)(intmax_t)(int8_t)(uint8_t)lhs_value; break;
				case 2: lhs_value = (uintmax_t)(intmax_t)(int16_t)(uint16_t)lhs_value; break;
				case 4: lhs_value = (uintmax_t)(intmax_t)(int32_t)(uint32_t)lhs_value; break;
				case 8: lhs_value = (uintmax_t)(intmax_t)(int64_t)(uint64_t)lhs_value; break;
				default: return DBX_EINTERN;
				}
				is_signed = true;
			}
		}

		/* Load the RHS-value. */
		if (!rhs_data) {
			rhs_value = 0;
		} else if (CTYPE_KIND_ISBOOL(rhs_typ->ct_kind)) {
			rhs_value = buffer_istrue(rhs_data, CTYPE_KIND_SIZEOF(rhs_typ->ct_kind)) ? 1 : 0;
		} else {
			switch (CTYPE_KIND_SIZEOF(rhs_typ->ct_kind)) {
			case 1: rhs_value = UNALIGNED_GET8(rhs_data); break;
			case 2: rhs_value = UNALIGNED_GET16(rhs_data); break;
			case 4: rhs_value = UNALIGNED_GET32(rhs_data); break;
			case 8: rhs_value = UNALIGNED_GET64(rhs_data); break;
			default: return DBX_EINTERN;
			}
			if (!CTYPE_KIND_INT_ISUNSIGNED(rhs_typ->ct_kind)) {
				/* Must sign-extend loaded values */
				switch (CTYPE_KIND_SIZEOF(rhs_typ->ct_kind)) {
				case 1: rhs_value = (uintmax_t)(intmax_t)(int8_t)(uint8_t)rhs_value; break;
				case 2: rhs_value = (uintmax_t)(intmax_t)(int16_t)(uint16_t)rhs_value; break;
				case 4: rhs_value = (uintmax_t)(intmax_t)(int32_t)(uint32_t)rhs_value; break;
				case 8: rhs_value = (uintmax_t)(intmax_t)(int64_t)(uint64_t)rhs_value; break;
				default: return DBX_EINTERN;
				}
			}
		}

		/* Perform the requested operation. */
		switch (op) {

		case '+': lhs_value += rhs_value; break;
		case '-': lhs_value -= rhs_value; break;
		case '*': lhs_value *= rhs_value; break;
		case '&': lhs_value &= rhs_value; break;
		case '|': lhs_value |= rhs_value; break;
		case '^': lhs_value ^= rhs_value; break;

		case '/':
			if (!lhs_data)
				break;
			if unlikely(!rhs_value)
				return DBX_EDIVZERO;
			if (is_signed) {
				lhs_value = (uintmax_t)((intmax_t)lhs_value / rhs_value);
			} else {
				lhs_value /= rhs_value;
			}
			break;

		case '%':
			if (!lhs_data)
				break;
			if unlikely(!rhs_value)
				return DBX_EDIVZERO;
			if (is_signed) {
				lhs_value = (uintmax_t)((intmax_t)lhs_value % rhs_value);
			} else {
				lhs_value %= rhs_value;
			}
			break;

		case CTOKEN_TOK_LANGLE_LANGLE:
			lhs_value <<= rhs_value;
			break;

		case CTOKEN_TOK_RANGLE_RANGLE:
			/* Must differentiate between signed/unsigned right-shift */
			if (is_signed) {
				lhs_value = (uintmax_t)((intmax_t)lhs_value >> rhs_value);
			} else {
				lhs_value >>= rhs_value;
			}
			break;

		case CTOKEN_TOK_EQUALS_EQUALS:
		case CTOKEN_TOK_XCLAIM_EQUALS:
		case '<':
		case CTOKEN_TOK_LANGLE_EQUALS:
		case '>':
		case CTOKEN_TOK_RANGLE_EQUALS: {
			/* Handle generic compare. */
			bool retval;
			if (!lhs_data)
				goto done_pop_rhs;
			if (op == CTOKEN_TOK_EQUALS_EQUALS) {
				retval = lhs_value == rhs_value;
			} else if (op == CTOKEN_TOK_XCLAIM_EQUALS) {
				retval = lhs_value != rhs_value;
			} else {
				/* Must account for the sign when comparing lower/greater */
				if (is_signed) {
					/* Signed compare */
					switch (op) {
					case '<': /*                */ retval = (intmax_t)lhs_value < (intmax_t)rhs_value; break;
					case CTOKEN_TOK_LANGLE_EQUALS: retval = (intmax_t)lhs_value <= (intmax_t)rhs_value; break;
					case '>': /*                */ retval = (intmax_t)lhs_value > (intmax_t)rhs_value; break;
					case CTOKEN_TOK_RANGLE_EQUALS: retval = (intmax_t)lhs_value >= (intmax_t)rhs_value; break;
					default: __builtin_unreachable();
					}
				} else {
					/* Unsigned compare */
					switch (op) {
					case '<': /*                */ retval = lhs_value < rhs_value; break;
					case CTOKEN_TOK_LANGLE_EQUALS: retval = lhs_value <= rhs_value; break;
					case '>': /*                */ retval = lhs_value > rhs_value; break;
					case CTOKEN_TOK_RANGLE_EQUALS: retval = lhs_value >= rhs_value; break;
					default: __builtin_unreachable();
					}
				}
			}
			cvalue_setbool(lhs, retval);
			goto done_pop_rhs;
		}	break;

		default:
			return DBX_EINTERN;
		}

		/* Write-back the LHS-value. */
		if (lhs_data) {
			switch (CTYPE_KIND_SIZEOF(lhs_typ->ct_kind)) {
			case 1: UNALIGNED_SET8(lhs_data, (uint8_t)lhs_value); break;
			case 2: UNALIGNED_SET16(lhs_data, (uint16_t)lhs_value); break;
			case 4: UNALIGNED_SET32(lhs_data, (uint32_t)lhs_value); break;
			case 8: UNALIGNED_SET64(lhs_data, (uint64_t)lhs_value); break;
			default: return DBX_EINTERN;
			}
		}
	} /* Scope... */
done_pop_rhs:
	return cexpr_pop(); /* Pop `rhs' */
}




/* Perform an assignment operation between the top 2 stack  elements,
 * where TOP is RHS, and the one before is LHS. When `cexpr_readonly'
 * is set to `true', then this function fails with `DBX_ERDONLY' */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_store)(void) {
	dbx_errno_t result;
	struct cvalue *lhs, *rhs;
	byte_t *lhs_data, *rhs_data;
	size_t num_bytes;
	if unlikely(cexpr_stacksize < 2)
		return DBX_EINTERN; /* Shouldn't happen */
	lhs = &cexpr_stack[cexpr_stacksize - 2];
	rhs = &cexpr_stack[cexpr_stacksize - 1];
	switch (lhs->cv_kind) {

	case CVALUE_KIND_VOID:
		/* This is needed for `cexpr_typeonly' */
		goto done_pop;

	case CVALUE_KIND_DATA:
	case CVALUE_KIND_IDATA:
		/* Cannot write to R-value expressions */
		return DBX_ESYNTAX;

	default: break;
	}
	if (cexpr_readonly)
		return DBX_ERDONLY; /* Refuse to perform store operations in read-only mode. */
	result = cexpr_promote(); /* R-value+promote */
	if unlikely(result != DBX_EOK)
		goto done;

	/* Cast the RHS-operand to the same type as the LHS-operand */
	result = cexpr_cast(&lhs->cv_type);
	if unlikely(result != DBX_EOK)
		goto done;

	/* Load data pointers for the LHS and RHS operands. */
	result = cexpr_getdata_ex(lhs, &lhs_data);
	if unlikely(result != DBX_EOK)
		goto done;
	result = cexpr_getdata_ex(rhs, &rhs_data);
	if unlikely(result != DBX_EOK)
		goto done;

	/* Figure out how many bytes to transfer (and assert that the number is equal on both sides) */
	num_bytes = cexpr_getsize_ex(lhs);
	if unlikely(num_bytes != cexpr_getsize_ex(rhs))
		return DBX_EINTERN;

	/* Do the actual job of copying data from `rhs_data' to `lhs_data' */
	if (dbg_movememory(lhs_data, rhs_data, num_bytes, cexpr_forcewrite) != 0)
		return DBX_EFAULT;

	/* Write-back the changes made to the LHS operand. */
	result = cvalue_flush(lhs);
	if unlikely(result != DBX_EOK)
		goto done;
done_pop:
	result = cexpr_pop(); /* Pop the RHS-expression */
done:
	return result;
}

/* Pop `argc' operands, followed by popping the function to call.
 * Then,  invoke  the  function   and  push  its  return   value.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: The stack does not contain enough elements. */
PUBLIC dbx_errno_t NOTHROW(FCALL cexpr_call)(size_t argc) {
	size_t i;
	dbx_errno_t result;
	struct cvalue *func, *argv;
	struct ctype *func_type;
	struct ctype *return_type;
	byte_t *func_addr;
	byte_t *return_buffer;
	size_t return_size;
	if (cexpr_stacksize < (argc + 1))
		return DBX_EINTERN;

	/* Dereference function pointers. */
	result = cexpr_lrot(argc + 1);
	if unlikely(result != DBX_EOK)
		goto done;
	for (;;) {
		uintptr_half_t kind;
		kind = cexpr_stacktop.cv_type.ct_typ->ct_kind;
		if (!CTYPE_KIND_ISARRAY_OR_POINTER(kind))
			break;
		result = cexpr_deref();
		if unlikely(result != DBX_EOK)
			goto done;
	}
	result = cexpr_rrot(argc + 1);
	if unlikely(result != DBX_EOK)
		goto done;

	/* Load cvalue pointers. */
	argv = cexpr_stackend - argc;
	func = argv - 1;

	/* Ensure that `func' is actually a function type. */
	func_type = func->cv_type.ct_typ;
	if unlikely(!CTYPE_KIND_ISFUNCTION(func_type->ct_kind))
		return DBX_ESYNTAX;
	if (func_type->ct_function.cf_argc != argc) {
		if (func_type->ct_function.cf_argc > argc)
			return DBX_ESYNTAX; /* Need more arguments */
		if (!(func_type->ct_kind & CTYPE_KIND_FUNPROTO_VARARGS))
			return DBX_ESYNTAX; /* Need less arguments */
	}

	/* Special handling for `cexpr_typeonly' */
	if (func->cv_kind == CVALUE_KIND_VOID) {
		/* Pop arguments. */
		result = cexpr_pop_n(argc);
		if unlikely(result != DBX_EOK)
			goto done;

		/* Re-load the function stack element. */
		func = &cexpr_stacktop;
		if unlikely(func->cv_kind != CVALUE_KIND_VOID)
			return DBX_EINTERN;
		if unlikely(func_type != func->cv_type.ct_typ)
			return DBX_EINTERN;

		/* Change the typing of the function element into its own return type. */
		incref(func_type);
		ctyperef_fini(&func->cv_type);
		ctyperef_initcopy(&func->cv_type, &func_type->ct_function.cf_base);
		decref(func_type);
		goto done;
	}

	/* Cast caller-given arguments to their required types. */
	for (i = 0; i < func_type->ct_function.cf_argc; ++i) {
		size_t delta = argc - i;
		result = cexpr_lrot(delta);
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_cast(&func_type->ct_function.cf_argv[i]);
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_promote(); /* Promote argument types after casting */
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_rrot(delta);
		if unlikely(result != DBX_EOK)
			goto done;
	}
	argv = cexpr_stackend - argc;
	func = argv - 1;
	if unlikely(func->cv_kind == CVALUE_KIND_VOID)
		return DBX_EINTERN;
	if unlikely(func_type != func->cv_type.ct_typ)
		return DBX_EINTERN;

	/* Load the address of the function to call. */
	result = cexpr_getdata_ex(func, &func_addr);
	if unlikely(result != DBX_EOK)
		goto done;

	/* Figure out the storage required for the return type, and change
	 * the  function stack element into an R-value slot for the return
	 * value. */
	incref(func_type);
	return_type = func_type->ct_function.cf_base.ct_typ;
	return_size = ctype_sizeof(return_type);
	cvalue_fini(func);
	ctyperef_initcopy(&func->cv_type, &func_type->ct_function.cf_base);
	func->cv_kind = CVALUE_KIND_IDATA;
	return_buffer = func->cv_idata;
	if (return_size > sizeof(func->cv_idata)) {
		/* Must dynamically allocate a return value buffer. */
		return_buffer = (byte_t *)dbx_malloc(return_size);
		if unlikely(!return_buffer) {
			decref(func_type);
			return DBX_ENOMEM;
		}
		func->cv_kind = CVALUE_KIND_DATA;
		func->cv_data = return_buffer;
	}

	/* Perform the actual function call. */
	result = cfunction_call((void const *)func_addr,
	                        func_type->ct_kind & CTYPE_KIND_FUNPROTO_CCMASK,
	                        argc, argv, return_type, return_buffer);
	decref(func_type);
	if unlikely(result != DBX_EOK)
		goto done;

	/* Pop arguments. */
	result = cexpr_pop_n(argc);
done:
	return result;
}



/* Perform custom handling of special symbols exported by the system `libdl.so' */
PRIVATE dbx_errno_t
NOTHROW_NCX(FCALL cexpr_load_special_libdl_symbol)(NCX char const *name) {
#define LIBDL_VAR___peb                         0 /* "__peb" */
#define LIBDL_VAR_environ                       1 /* "environ", "_environ", "__environ" */
#define LIBDL_VAR___argc                        2 /* "__argc" */
#define LIBDL_VAR___argv                        3 /* "__argv" */
#define LIBDL_VAR_program_invocation_name       4 /* "_pgmptr", "__progname_full", "program_invocation_name" */
#define LIBDL_VAR_program_invocation_short_name 5 /* "__progname", "program_invocation_short_name" */
	unsigned int varid = (unsigned int)-1;
	dbx_errno_t result = DBX_EOK;
	/* Figure what (if any) special variable is being accessed. */
	if (*name == '_') {
		++name;
		if (*name == '_') {
			++name;
			if (strcmp(name, "peb") == 0) {
				varid = LIBDL_VAR___peb;
			} else if (strcmp(name, "environ") == 0) {
				varid = LIBDL_VAR_environ;
			} else if (strcmp(name, "argc") == 0) {
				varid = LIBDL_VAR___argc;
			} else if (strcmp(name, "argv") == 0) {
				varid = LIBDL_VAR___argv;
			} else if (strcmp(name, "progname_full") == 0) {
				varid = LIBDL_VAR_program_invocation_name;
			} else if (strcmp(name, "progname") == 0) {
				varid = LIBDL_VAR_program_invocation_short_name;
			}
		} else if (strcmp(name, "environ") == 0) {
			varid = LIBDL_VAR_environ;
		} else if (strcmp(name, "pgmptr") == 0) {
			varid = LIBDL_VAR_program_invocation_name;
		}
	} else if (strcmp(name, "environ") == 0) {
		varid = LIBDL_VAR_environ;
	} else if (bcmp(name, "program_invocation_", 19, sizeof(char)) == 0) {
		name += 19;
		if (strcmp(name, "name") == 0) {
			varid = LIBDL_VAR_program_invocation_name;
		} else if (strcmp(name, "short_name") == 0) {
			varid = LIBDL_VAR_program_invocation_short_name;
		}
	}
	if (varid != (unsigned int)-1) {
		result = cexpr_pop();
		if unlikely(result != DBX_EOK)
			goto done;

		/* All of the special symbols somehow interact with "dl_globals",
		 * which  should be an  INTERN-visibility symbol from `libdl.so'! */
		result = cexpr_pushsymbol_byname("dl_globals", 10);
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_field("dg_peb", 6);
		if unlikely(result != DBX_EOK)
			goto done;
		result = cexpr_deref();
		if unlikely(result != DBX_EOK)
			goto done;
		switch (varid) {

		case LIBDL_VAR___peb:
			/* &__peb == dl_globals.dg_peb */
			break;

		case LIBDL_VAR_environ:
			/* &environ == &dl_globals.dg_peb->pp_envp */
			result = cexpr_field("pp_envp", 7);
			break;

		case LIBDL_VAR___argc:
			/* &__argc == &dl_globals.dg_peb->pp_argc */
			result = cexpr_field("pp_argc", 7);
			break;

		case LIBDL_VAR___argv:
			/* &__argv == &dl_globals.dg_peb->pp_argv */
			result = cexpr_field("pp_argv", 7);
			break;

		case LIBDL_VAR_program_invocation_name:
			/* &program_invocation_name == &dl_globals.dg_peb->pp_argv[0] */
			result = cexpr_field("pp_argv", 7);
			if likely(result == 0)
				result = cexpr_deref();
			break;

		case LIBDL_VAR_program_invocation_short_name: {
			/* This is where it gets a bit complicated, since `program_invocation_short_name'
			 * is  lazily initialized upon first access (meaning that we have to do that init
			 * for ourselves if it wasn't already done)
			 * s.a. `libdl:dlget_p_program_invocation_short_name()' */
			static char const str_dl_program_invocation_short_name[] = "dl_program_invocation_short_name";
			char const *argv0;
			byte_t *addrof_dl_program_invocation_short_name;
			size_t sizeof_dl_program_invocation_short_name;
			result = cexpr_pushsymbol_byname(str_dl_program_invocation_short_name,
			                                 COMPILER_STRLEN(str_dl_program_invocation_short_name));
			if unlikely(result != DBX_EOK)
				goto done;
			result = cexpr_getdata(&addrof_dl_program_invocation_short_name);
			if unlikely(result != DBX_EOK)
				goto done;
			sizeof_dl_program_invocation_short_name = cexpr_getsize();
			if (sizeof_dl_program_invocation_short_name == sizeof(void *)) {
				uintptr_t pointed_addr;
				if (dbg_readmemory(addrof_dl_program_invocation_short_name,
				                   &pointed_addr, sizeof(pointed_addr)) != 0)
					goto err_fault;
				if (pointed_addr != 0)
					goto push_normal_dl_program_invocation_short_name;
#ifdef __ARCH_HAVE_COMPAT
			} else if (sizeof_dl_program_invocation_short_name == __ARCH_COMPAT_SIZEOF_POINTER) {
				compat_uintptr_t pointed_addr;
				if (dbg_readmemory(addrof_dl_program_invocation_short_name,
				                   &pointed_addr, sizeof(pointed_addr)) != 0)
					goto err_fault;
				if (pointed_addr != 0)
					goto push_normal_dl_program_invocation_short_name;
#endif /* __ARCH_HAVE_COMPAT */
			} else {
push_normal_dl_program_invocation_short_name:
				result = cexpr_swap();
				if unlikely(result != DBX_EOK)
					goto done;
				result = cexpr_pop();
				goto done;
			}

			/* Must lazily initialize `dl_program_invocation_short_name' */
			result = cexpr_swap();
			if unlikely(result != DBX_EOK)
				goto done;
			result = cexpr_field("pp_argv", 7);
			if unlikely(result != DBX_EOK)
				goto done;
			result = cexpr_deref();
			if unlikely(result != DBX_EOK)
				goto done;
			result = cexpr_deref();
			if unlikely(result != DBX_EOK)
				goto done;

			/* Right now, the top of the stack points at `*dl_globals.dg_peb->pp_argv[0]', which
			 * contains the address that we want to  write back to the program invocation  short
			 * name symbol. */
			result = cexpr_getdata((byte_t **)&argv0);
			if unlikely(result != DBX_EOK)
				goto done;
			if (!argv0 || !ADDR_ISUSER(argv0))
				goto push_normal_dl_program_invocation_short_name;

			/* Pop the dl_globals.dg_peb-based expression off of the stack! */
			result = cexpr_pop();
			if unlikely(result != DBX_EOK)
				goto done;

			/* Find the position of the last '/' in the `argv0' string.
			 * Then, write-back the position 1 past that character back
			 * to `*addrof_dl_program_invocation_short_name' */
			{
				char const *iter;
				for (iter = argv0;; ++iter) {
					char ch;
					if (dbg_readmemory(iter, &ch, sizeof(ch)) != 0)
						goto err_fault;
					if (ch == '\0')
						break;
					if (ch == '/')
						argv0 = iter + 1;
				}
			}

#if defined(__ARCH_COMPAT) && __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
			if (sizeof_dl_program_invocation_short_name != sizeof(void *)) {
				compat_uintptr_t compat_argv0;
				compat_argv0 = (compat_uintptr_t)(uintptr_t)argv0;
				argv0        = NULL;
				memcpy(&argv0, &compat_argv0, sizeof(compat_uintptr_t));
			}
#endif /* __ARCH_COMPAT && __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
			if (dbg_writememory(addrof_dl_program_invocation_short_name, &argv0,
			                    sizeof_dl_program_invocation_short_name, false) != 0)
				goto err_fault;
		}	break;

		default:
			break;
		}
	}
done:
	return result;
err_fault:
	return DBX_EFAULT;
}


/* Push  a  currently visible  symbol, as  selected by  the code  location from
 * `dbg_current' and any possibly modifications made to `DBG_RT_REGLEVEL_VIEW',
 * given that symbol's  `name'. For  this purpose,  `name' can  be (in  order):
 *   - A function-to-compilation-unit-scoped variable/argument/enum
 *   - A PUBLIC/INTERN variable from the module containing the current PC
 * if (ADDR_ISUSER(CURRENT_PC)) {
 *   - A PUBLIC/INTERN variable from any loaded user-space module
 *   - A PUBLIC/INTERN variable from any loaded kernel-space module
 * } else {
 *   - A PUBLIC/INTERN variable from any loaded kernel-space module
 *   - A PUBLIC/INTERN variable from any loaded user-space module
 * }
 * Note that special handling is done for kernel-space PERxxx variables, which  are
 * automatically  linked to the associated address space for `dbg_current', such as
 * `this_task' automatically being loaded as the equivalent of `this_task@%fs_base'
 * This detection is done for  all PUBLIC/INTERN+KERNEL_CORE symbols starting  with
 * one of the following prefixes:
 *   - this_*      Addend is `(uintptr_t)dbg_current'
 *   - thiscpu_*   Addend is `(uintptr_t)dbg_current->t_cpu'
 *   - thismman_*  Addend is `(uintptr_t)dbg_current->t_mman'
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory.
 * @return: DBX_ENOENT: No object matches the given `name' */
PUBLIC NONNULL((1)) dbx_errno_t
NOTHROW_NCX(FCALL cexpr_pushsymbol)(struct cmodsyminfo *__restrict sym,
                                    bool automatic_symbol_addend) {
	dbx_errno_t result;
	struct ctyperef symtype;
	if (cmodsyminfo_istype(sym))
		return DBX_ENOENT;
	if (!sym->clv_data.s_var.v_typeinfo && cmodsyminfo_issip(sym)) {
		/* XXX: This  right here  can happen if  a symbol appears  in a module's
		 *      symbol table,  but  doesn't  actually end  up  appearing  within
		 *      the module's .debug_info, not even as some kind of alias created
		 *      by something like `DEFINE_PUBLIC_ALIAS()'.
		 * In this case, check  if `sym' is part  of the _public_ symbol  table
		 * of its associated module (i.e. `.dynsym'), and if so: search through
		 * loaded modules that  claim dependencies on  that module. Then,  look
		 * through the debug information of those modules in search of one that
		 * makes  a reference to an external symbol of the same name, and if we
		 * manage to find such a  reference, then we can  make use of its  type
		 * information to complete what we couldn't find earlier!
		 *
		 * This  can happen if `sym' is exported from hand-written assembly, in
		 * which case there won't be  any C-style debug information  associated
		 * with it, but it probably can still be accessed using a C-type (after
		 * all: everything can), so if some other module does so, we can re-use
		 * it's debug information!
		 */
	}

	if (!sym->clv_data.s_var.v_typeinfo && cmodsyminfo_issip(sym)) {
		/* If we weren't able to  figure out the proper typing  for
		 * the symbol (and it may not even have any proper typing),
		 * then try to induce its type from information taken  from
		 * the symbol's Elf(32|64)_Sym entry.
		 *
		 * Using that entry, we can:
		 *  - Determine if  it's a  function,  and if  it  is:
		 *    Use `int(...)' as type (i.e. int-return+varargs)
		 *  - Figure  out  the  symbol's  size,  and  select an
		 *    appropriate integer type based on that knowledge:
		 *     - If the size is the same as that of a pointer, assume that it's a pointer
		 *     - Otherwise, select the proper 1,2,4 or 8-byte unsigned integer type
		 *     - Otherwise, interpret as an array of byte_t-s. */
		NCX CLinkerSymbol const *sip;
		unsigned char st_info;
		size_t st_size;
		sip = cmodsyminfo_getsip(sym);
		if (CLinkerSymbol_IsElf32(sym->clv_mod)) {
			st_info = sip->cls_elf32.st_info;
			st_size = sip->cls_elf32.st_size;
		} else if (CLinkerSymbol_IsElf64(sym->clv_mod)) {
			st_info = sip->cls_elf64.st_info;
			st_size = sip->cls_elf64.st_size;
		} else {
			goto fallback_load_opt_type;
		}
		bzero(&symtype, sizeof(symtype));
		if (ELF_ST_TYPE(st_info) == STT_FUNC) {
			symtype.ct_typ = &ctype_int;
			symtype.ct_typ = ctype_function(&symtype, 0, NULL,
			                                CTYPE_KIND_FUNPROTO_VARARGS);
			if unlikely(!symtype.ct_typ)
				goto err_csym_nomem;
		} else if (ELF_ST_TYPE(st_info) == STT_OBJECT) {
			if (st_size == dbg_current_sizeof_pointer()) {
				symtype.ct_typ = incref(&ctype_void_ptr);
			} else {
				switch (st_size) {
				case 1: symtype.ct_typ = incref(&ctype_u8); break;
				case 2: symtype.ct_typ = incref(&ctype_u16); break;
				case 4: symtype.ct_typ = incref(&ctype_u32); break;
				case 8: symtype.ct_typ = incref(&ctype_u64); break;
				default:
					symtype.ct_typ = &ctype_byte_t;
					symtype.ct_typ = ctype_array(&symtype, st_size);
					break;
				}
				if unlikely(!symtype.ct_typ)
					goto err_csym_nomem;
			}
		} else {
			goto fallback_load_opt_type;
		}
		goto got_symbol_type;
	}
fallback_load_opt_type:

	/* Load the type of the variable. */
	result = ctype_fromdw_opt(sym->clv_mod, sym->clv_unit,
	                          &sym->clv_parser,
	                          sym->clv_data.s_var.v_typeinfo,
	                          &symtype);
	if (sym->clv_parser.dup_comp.dic_tag == DW_TAG_subprogram) {
		/* Special case: Must complete `symtype' by loading argument types. */
		REF struct ctype *function_type;
		sym->clv_parser.dsp_cu_info_pos = sym->clv_dip;
		if (sym->clv_parser.dsp_cu_info_pos && debuginfo_cu_parser_next(&sym->clv_parser)) {
			debuginfo_cu_parser_skipattr(&sym->clv_parser);
			result = ctype_fromdw_subroutine(sym->clv_mod,
			                                 sym->clv_unit,
			                                 &sym->clv_parser,
			                                 &function_type,
			                                 &symtype);
		} else {
			/* Fallback */
			function_type = ctype_function(&symtype, 0, NULL,
			                               CTYPE_KIND_FUNPROTO_VARARGS);
			if unlikely(!function_type)
				result = DBX_ENOMEM;
		}
		ctyperef_fini(&symtype);
		if unlikely(result != DBX_EOK)
			goto done;
		bzero(&symtype, sizeof(symtype));
		symtype.ct_typ = function_type; /* Inherit reference */
	}
	if likely(result == DBX_EOK) {
got_symbol_type:
		if (sym->clv_data.s_var.v_gotaddr &&
		    sym->clv_data.s_var.v_objaddr == sym->clv_data.s_var._v_objdata) {
			result = cexpr_pushdata(&symtype, sym->clv_data.s_var.v_objaddr);
		} else {
			struct cvalue_cfiexpr expr;

			/* Fill in the expression for loading the symbol. */
			expr.v_module            = sym->clv_mod;
			expr.v_expr              = sym->clv_data.s_var.v_location;
			expr.v_framebase         = sym->clv_data.s_var.v_framebase;
			expr.v_cu_ranges_startpc = sym->clv_cu.cu_ranges.r_startpc;
			expr.v_cu_addr_base      = sym->clv_cu.cu_addr_base;
			expr.v_addrsize          = sym->clv_parser.dsp_addrsize;
			expr.v_ptrsize           = sym->clv_parser.dsp_ptrsize;
			expr.v_gotaddr           = sym->clv_data.s_var.v_gotaddr;
			expr.v_objaddr           = sym->clv_data.s_var.v_objaddr;

			/* Push the symbol expression. */
			result = cexpr_pushexpr(&symtype,
			                        &expr,
			                        ctype_sizeof(symtype.ct_typ),
			                        0);

			if likely(result == DBX_EOK) {
				/* Special handling for ".fakedata" symbols exported by `libdl.so'.
				 *
				 * Libdl claims to  export these  symbols like  any others  are, however  in
				 * actuality, their address/size aren't resolved to the suggested locations,
				 * but rather to custom locations relative to `dl_globals.dg_peb'.
				 *
				 * As such, and because there really are some rather important symbols
				 * in  here, we have  to do some special  filtering to duplicate those
				 * custom routers, as already seen in `dlsym_builtin()':
				 *
				 *    &__peb                         == dl_globals.dg_peb;
				 *    &environ                       == &dl_globals.dg_peb->pp_envp;
				 *    &_environ                      == &dl_globals.dg_peb->pp_envp;
				 *    &__environ                     == &dl_globals.dg_peb->pp_envp;
				 *    &__argc                        == &dl_globals.dg_peb->pp_argc;
				 *    &__argv                        == &dl_globals.dg_peb->pp_argv;
				 *    &_pgmptr                       == &dl_globals.dg_peb->pp_argv[0];
				 *    &__progname_full               == &dl_globals.dg_peb->pp_argv[0];
				 *    &program_invocation_name       == &dl_globals.dg_peb->pp_argv[0];
				 *    &__progname                    == dlget_p_program_invocation_short_name();
				 *    &program_invocation_short_name == dlget_p_program_invocation_short_name();
				 *
				 */
				if (cmodule_isuser(expr.v_module) &&
				    expr.v_module->cm_module->md_fspath == NULL &&
				    expr.v_module->cm_module->md_fsname != NULL) {
					struct fdirent *dent = expr.v_module->cm_module->md_fsname;
					if ((dent->fd_hash == _RTLD_LIBDL_HASH &&
					     dent->fd_namelen == COMPILER_STRLEN(RTLD_LIBDL) &&
					     bcmp(dent->fd_name, RTLD_LIBDL, sizeof(RTLD_LIBDL)) == 0)
#ifdef __ARCH_HAVE_COMPAT
					    ||
					    (dent->fd_hash == _COMPAT_RTLD_LIBDL_HASH &&
					     dent->fd_namelen == COMPILER_STRLEN(COMPAT_RTLD_LIBDL) &&
					     bcmp(dent->fd_name, COMPAT_RTLD_LIBDL, sizeof(COMPAT_RTLD_LIBDL)) == 0)
#endif /* __ARCH_HAVE_COMPAT */
					    ) {
						NCX char const *name;
						name   = cmodsyminfo_name(sym);
						result = cexpr_load_special_libdl_symbol(name);
						goto done_symtype;
					}
				}

				/* Do special handling for this(|mman|cpu)_* globals from the kernel core.
				 * When accessed, automatically include an  addend to the relevant  object
				 * in relation to dbg_current, such  that the user can directly  reference
				 * these objects without having to manually sym@object them.
				 *
				 * Note however that in normal code, this is only done when the  symbol
				 * doesn't already appear in an @-expression (i.e. isn't followed by an
				 * @-token) or within __identifier, meaning that:
				 *   - `&__identifier(this_cred)' == `&__identifier(this_cred)'
				 *   - `this_cred'                == `*(typeof(this_cred) *)((uintptr_t)&__identifier(this_cred) + (uintptr_t)dbg_current)'
				 *   - `this_cred@foo'            == `*(typeof(this_cred) *)((uintptr_t)&__identifier(this_cred) + (uintptr_t)foo)'
				 *   - `(this_cred)@foo'          == `*(typeof(this_cred) *)((uintptr_t)&__identifier(this_cred) + (uintptr_t)dbg_current + (uintptr_t)foo)'
				 */
				if (automatic_symbol_addend && !cexpr_typeonly &&
				    sym->clv_mod && sym->clv_mod->cm_module == (module_t *)&kernel_driver &&
				    !CTYPE_KIND_ISFUNCTION(symtype.ct_typ->ct_kind)) {
					uintptr_t addend;
					char const *name = cmodsyminfo_name(sym);
					if (name && bcmp(name, "this", 4, sizeof(char)) == 0) {
						if (name[4] == '_') {
							REF struct ctype *symtype_ptr;
							addend = (uintptr_t)dbg_current;
do_increase_addend:
							/* Offset by the given addend, essentially doing `this_foo@dbg_current' */
							result = cexpr_ref();
							if unlikely(result != DBX_EOK)
								goto done_symtype;
							result = cexpr_cast_simple(&ctype_uintptr_t);
							if unlikely(result != DBX_EOK)
								goto done_symtype;
							result = cexpr_pushint_simple(&ctype_uintptr_t, addend);
							if unlikely(result != DBX_EOK)
								goto done_symtype;
							result = cexpr_op2('+');
							if unlikely(result != DBX_EOK)
								goto done_symtype;
							symtype_ptr = ctype_ptr(&symtype, dbg_current_sizeof_pointer());
							if unlikely(!symtype_ptr) {
								result = DBX_ENOMEM;
								goto done_symtype;
							}
							result = cexpr_cast_simple(symtype_ptr);
							decref(symtype_ptr);
							if unlikely(result != DBX_EOK)
								goto done_symtype;
							result = cexpr_deref();
						} else {
							/* Guard against bad memory accesses when `dbg_current'
							 * has become corrupt for whatever reason. */
							TRY {
								if (name[4] == 'm' && name[5] == 'm' &&
								    name[6] == 'a' && name[7] == 'n' &&
								    name[8] == '_') {
									if unlikely(!ADDR_ISKERN(dbg_current))
										goto err_fefault_symtype;
									addend = (uintptr_t)dbg_current->t_mman;
									goto do_increase_addend;
								}
								if (name[4] == 'c' && name[5] == 'p' &&
								    name[6] == 'u' && name[7] == '_') {
									if unlikely(!ADDR_ISKERN(dbg_current))
										goto err_fefault_symtype;
									addend = (uintptr_t)dbg_current->t_cpu;
									goto do_increase_addend;
								}
							} EXCEPT {
								goto err_fefault_symtype;
							}
						}
					}
				}
			}
		}
done_symtype:
		ctyperef_fini(&symtype);
	}
done:
	return result;
err_csym_nomem:
	result = DBX_ENOMEM;
	goto done;
err_fefault_symtype:
	result = DBX_EFAULT;
	goto done_symtype;
}

PUBLIC NONNULL((1)) dbx_errno_t
NOTHROW_NCX(FCALL cexpr_pushsymbol_byname)(NCX char const *name, size_t namelen,
                                           bool automatic_symbol_addend) {
	dbx_errno_t result;
	struct cmodsyminfo csym;
	result = cmod_syminfo_local(&csym, name, namelen,
	                            CMODSYM_DIP_NS_NONTYPE);
	if (result != DBX_EOK)
		return result;
	result = cexpr_pushsymbol(&csym, automatic_symbol_addend);
	cmod_syminfo_local_fini(&csym);
	return result;
}



/* Push a register with its native typing, given its `name'
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOMEM: Insufficient memory.
 * @return: DBX_ENOENT: No register matches the given `name' */
PUBLIC NONNULL((1)) dbx_errno_t
NOTHROW_NCX(FCALL cexpr_pushregister)(NCX char const *name, size_t namelen) {
	isa_t isa = dbg_rt_getisa(DBG_RT_REGLEVEL_VIEW);
	cpu_regno_t regno = register_byname(isa, name, namelen);
	if (regno == CPU_REGISTER_NONE)
		return DBX_ENOENT;
	return cexpr_pushregister_by_id(regno);
}



DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_MODDBX_CEXPR_C */
