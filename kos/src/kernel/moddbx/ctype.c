/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODDBX_CTYPE_C
#define GUARD_MODDBX_CTYPE_C 1
#define _KOS_SOURCE 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/rt.h>
#include <kernel/types.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <compat/config.h>
#include <kos/exec/module.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include <libdebuginfo/debug_info.h>

/**/
#include "include/ctype.h"
#include "include/malloc.h"

#if defined(__x86_64__) || defined(__i386__)
#include <asm/registers.h>
#include <asm/registers-compat.h>
#endif /* __x86_64__ || __i386__ */

#ifdef CONFIG_HAVE_DEBUGGER
DECL_BEGIN

PUBLIC NONNULL((1)) void
NOTHROW(FCALL ctype_destroy)(struct ctype *__restrict self) {
	STATIC_ASSERT(offsetof(struct ctype, ct_enum) == offsetof(struct ctype, ct_struct));
	switch (CTYPE_KIND_CLASSOF(self->ct_kind)) {

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_ENUM):
		if (CTYPE_KIND_ISENUM(self->ct_kind)) {
	case CTYPE_KIND_CLASSOF(CTYPE_KIND_STRUCT):
			dw_debugloc_fini(&self->ct_enum);
		}
		break;

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_FUNCTION): {
		size_t i;
		for (i = 0; i < self->ct_function.cf_argc; ++i)
			ctyperef_fini(&self->ct_function.cf_argv[i]);
	}	ATTR_FALLTHROUGH
	case CTYPE_KIND_CLASSOF(CTYPE_KIND_PTR):
	case CTYPE_KIND_CLASSOF(CTYPE_KIND_ARRAY): {
		STATIC_ASSERT(offsetof(struct ctype, ct_pointer.cp_base.ct_typ) == offsetof(struct ctype, ct_function.cf_base));
		STATIC_ASSERT(offsetof(struct ctype, ct_pointer.cp_base.ct_typ) == offsetof(struct ctype, ct_array.ca_elem));
		STATIC_ASSERT(offsetof(struct ctype, ct_pointer.cp_base.ct_info) == offsetof(struct ctype, ct_array.ca_eleminfo));
		if (self->ct_pointer.cp_base.ct_typ != NULL) {
			/* Remove `self' from its sibling-chain. */
			struct ctype **piter, *iter;
			piter = &self->ct_pointer.cp_base.ct_typ->ct_children;
			while ((iter = *piter) != NULL) {
				if (iter == self) {
					*piter = iter->ct_sibling;
					break;
				}
				piter = &iter->ct_sibling;
			}
			decref(self->ct_pointer.cp_base.ct_typ);
		}
	}	break;

	default:
		break;
	}
	dbx_free(self);
}


/* Return the pointer-version of the given C-type
 * @param: flags: Type-reference-flags (set of `CTYPEREF_FLAG_*') */
PUBLIC NONNULL((1)) REF struct ctype *
NOTHROW(FCALL ctype_ptr)(struct ctyperef const *__restrict self,
                         size_t sizeof_pointer) {
	REF struct ctype *result;
	uintptr_half_t wanted_kind;
	wanted_kind = CTYPE_KIND_CLASSOF(CTYPE_KIND_PTR) | sizeof_pointer;
	for (result = self->ct_typ->ct_children; result;
	     result = result->ct_sibling) {
		assert(result->ct_parent == self->ct_typ);
		if (result->ct_kind == wanted_kind &&
		    ctyperef_equal_assume_same_type(&result->ct_pointer.cp_base, self))
			return incref(result);
	}
	/* Create a new sibling. */
	result = (REF struct ctype *)dbx_malloc(offsetafter(struct ctype, ct_pointer));
	if unlikely(!result)
		return NULL;
	result->ct_refcnt   = 1; /* Returned reference. */
	result->ct_kind     = wanted_kind;
	result->ct_children = NULL;
	ctyperef_initcopy(&result->ct_pointer.cp_base, self);
	/* Add the new pointer type to the chain of children of `self' */
	ctype_addchild(self->ct_typ, result);
	return result;
}


/* Return the array-version of the given C-type
 * NOTE: The returned type must inherit `self->ct_flags'
 * @param: flags: Type-reference-flags (set of `CTYPEREF_FLAG_*') */
PUBLIC NONNULL((1)) REF struct ctype *
NOTHROW(FCALL ctype_array)(struct ctyperef const *__restrict self,
                           size_t elem_count) {
	REF struct ctype *result;
	for (result = self->ct_typ->ct_children; result;
	     result = result->ct_sibling) {
		assert(result->ct_parent == self->ct_typ);
		if (result->ct_kind == CTYPE_KIND_ARRAY &&
		    result->ct_array.ca_count == elem_count &&
		    ctypeinfo_equal(&result->ct_array.ca_eleminfo, &self->ct_info))
			return incref(result);
	}
	/* Create a new sibling. */
	result = (REF struct ctype *)dbx_malloc(offsetafter(struct ctype, ct_array));
	if unlikely(!result)
		return NULL;
	result->ct_refcnt   = 1; /* Returned reference. */
	result->ct_kind     = CTYPE_KIND_ARRAY;
	result->ct_children = NULL;
	ctypeinfo_initcopy(&result->ct_array.ca_eleminfo, &self->ct_info);
	result->ct_array.ca_elem  = incref(self->ct_typ);
	result->ct_array.ca_count = elem_count;
	/* Add the new type to the chain of children of `self' */
	ctype_addchild(self->ct_typ, result);
	return result;
}

/* Return a function-type C-type. */
PUBLIC NONNULL((1)) REF struct ctype *
NOTHROW(FCALL ctype_function)(struct ctyperef const *return_type, size_t argc,
                              struct ctyperef const *argv, uint16_t cc) {
	size_t i;
	REF struct ctype *result;
	cc |= CTYPE_KIND_FUNCTION;
	for (result = return_type->ct_typ->ct_children; result;
	     result = result->ct_sibling) {
		assert(result->ct_parent == return_type->ct_typ);
		if (result->ct_kind == cc && result->ct_function.cf_argc == argc &&
		    ctyperef_equal_assume_same_type(&result->ct_function.cf_base, return_type)) {
			size_t i;
			/* Check if argument types are identical. */
			for (i = 0; i < argc; ++i) {
				struct ctyperef const *lhs, *rhs;
				lhs = &result->ct_function.cf_argv[i];
				rhs = &argv[i];
				if (lhs->ct_typ != rhs->ct_typ ||
				    lhs->ct_flags != rhs->ct_flags ||
				    !ctypeinfo_equal(&lhs->ct_info, &rhs->ct_info))
					goto next_typ;
			}
			return incref(result);
		}
next_typ:
		;
	}
	/* Create a new sibling. */
	result = (REF struct ctype *)dbx_malloc(offsetof(struct ctype, ct_function.cf_argv) +
	                                        (argc * sizeof(struct ctyperef)));
	if unlikely(!result)
		return NULL;
	result->ct_refcnt   = 1; /* Returned reference. */
	result->ct_kind     = cc;
	result->ct_children = NULL;
	/* Fill in the new function type */
	ctyperef_initcopy(&result->ct_function.cf_base, return_type);
	result->ct_function.cf_argc = argc;
	memcpy(result->ct_function.cf_argv, argv,
	       argc, sizeof(struct ctyperef));
	for (i = 0; i < argc; ++i) {
		incref(result->ct_function.cf_argv[i].ct_typ);
		xincref(result->ct_function.cf_argv[i].ct_info.ci_nameref);
	}
	/* Add the new type to the chain of children of `self' */
	ctype_addchild(return_type->ct_typ, result);
	return result;
}

/* Return the actual size of the given C-type. (as per `sizeof()') */
PUBLIC ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW(FCALL ctype_sizeof)(struct ctype const *__restrict self) {
	size_t result;
	result = CTYPE_KIND_SIZEOF(self->ct_kind);
	if (result == 0) {
		/* Special handling required. */
		switch (CTYPE_KIND_CLASSOF(self->ct_kind)) {

		case CTYPE_KIND_CLASSOF(CTYPE_KIND_STRUCT):
			result = self->ct_struct.ct_sizeof;
			break;

		case CTYPE_KIND_CLASSOF(CTYPE_KIND_ARRAY):
			result = self->ct_array.ca_count;
			if (result)
				result *= ctype_sizeof(self->ct_array.ca_elem);
			break;

		default:
			result = 1;
			break;
		}
	}
	return result;
}

/* Check if 2 given C-types are equal. */
PUBLIC ATTR_PURE NONNULL((1, 2)) bool
NOTHROW(FCALL ctype_equal)(struct ctype const *a,
                           struct ctype const *b) {
again:
	if (a == b)
		return true;
	if (a->ct_kind != b->ct_kind)
		goto nope;
	switch (CTYPE_KIND_CLASSOF(a->ct_kind)) {

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_VOID):
	case CTYPE_KIND_CLASSOF(CTYPE_KIND_BOOL):
	case CTYPE_KIND_CLASSOF(CTYPE_KIND_ENUM):
	case CTYPE_KIND_CLASSOF(CTYPE_KIND_IEEE754_FLOAT):
		break;

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_PTR):
		if (a->ct_pointer.cp_base.ct_flags !=
		    b->ct_pointer.cp_base.ct_flags)
			goto nope;
		a = a->ct_pointer.cp_base.ct_typ;
		b = b->ct_pointer.cp_base.ct_typ;
		goto again;

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_STRUCT):
		if (a->ct_struct.ct_info.ddl_di_pos != b->ct_struct.ct_info.ddl_di_pos)
			goto nope;
		break;

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_ARRAY):
		if (a->ct_array.ca_count != b->ct_array.ca_count)
			goto nope;
		a = a->ct_array.ca_elem;
		b = b->ct_array.ca_elem;
		goto again;

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_FUNCTION): {
		size_t i;
		if (a->ct_function.cf_argc != b->ct_function.cf_argc)
			goto nope;
		if (a->ct_function.cf_base.ct_flags != b->ct_function.cf_base.ct_flags)
			goto nope;
		for (i = 0; i < a->ct_function.cf_argc; ++i) {
			if (a->ct_function.cf_argv[i].ct_flags !=
			    b->ct_function.cf_argv[i].ct_flags)
				goto nope;
			if (!ctype_equal(a->ct_function.cf_argv[i].ct_typ,
			                 b->ct_function.cf_argv[i].ct_typ))
				goto nope;
		}
		a = a->ct_function.cf_base.ct_typ;
		b = b->ct_function.cf_base.ct_typ;
		goto again;
	}	break;

	default:
		goto nope;
	}
	return true;
nope:
	return false;
}

/* Return the common type which can be used to represent both `a' and `b'.
 * This common type is the promotion of `a' and `b' if those types are equal,
 * and otherwise is the larger integer type of the two. If neither types are
 * integers, then a common type doesn't exist and `NULL' is returned. */
PUBLIC WUNUSED NONNULL((1, 2)) REF struct ctype *
NOTHROW(FCALL ctype_common)(struct ctype *a,
                            struct ctype *b) {
	uintptr_half_t akind, bkind;
	akind = a->ct_kind;
	bkind = b->ct_kind;
	if ((CTYPE_KIND_ISINT(akind) || CTYPE_KIND_ISBOOL(akind)) &&
	    (CTYPE_KIND_ISINT(bkind) || CTYPE_KIND_ISBOOL(bkind))) {
		/* Return the larger of the two types. */
		if (CTYPE_KIND_SIZEOF(akind) > CTYPE_KIND_SIZEOF(bkind))
			return incref(a);
		if (CTYPE_KIND_SIZEOF(akind) < CTYPE_KIND_SIZEOF(bkind))
			return incref(b);
		/* Same type sizes. -> Return the signed of the two types. */
		if (!CTYPE_KIND_INT_ISUNSIGNED(akind))
			return incref(a);
		if (!CTYPE_KIND_INT_ISUNSIGNED(bkind))
			return incref(b);
		/* Both types are unsigned. -> Return whichever isn't a boolean. */
		if (CTYPE_KIND_ISINT(akind))
			return incref(a);
		return incref(b);
	}
	if (ctype_equal(a, b))
		return incref(a);
	if (CTYPE_KIND_ISPOINTER(akind) && CTYPE_KIND_ISPOINTER(bkind) &&
	    CTYPE_KIND_SIZEOF(akind) == CTYPE_KIND_SIZEOF(bkind)) {
		/* EXTENSION: Both types are (non-equal) pointers.
		 * -> Just return a void-pointer. */
		if (CTYPE_KIND_SIZEOF(akind) == sizeof(void *))
			return incref(&ctype_void_ptr);
#ifdef __ARCH_HAVE_COMPAT
		if (CTYPE_KIND_SIZEOF(akind) == __ARCH_COMPAT_SIZEOF_POINTER)
			return incref(&ctype_void_compat_ptr);
#endif /* __ARCH_HAVE_COMPAT */
		{
			struct ctyperef ct;
			memset(&ct, 0, sizeof(ct));
			ct.ct_typ = &ctype_void;
			return ctype_ptr(&ct, CTYPE_KIND_SIZEOF(akind));
		}
	}
	return NULL;
}


/* Builtin types. */
struct _basic_ctype {
	uintptr_half_t ct_refcnt;   /* Reference counter. */
	uintptr_half_t ct_kind;     /* The kind of type (one of `CTYPE_KIND_*'). */
	struct ctype  *ct_children; /* [0..1] Derived types (all of these have `CTYPE_KIND_HASSIBLING()') */
};
#define _BASIC_CTYPE_INIT(kind, children) \
	{ 0x7fff, kind, children }

struct _pointer_ctype {
	uintptr_half_t          ct_refcnt;   /* Reference counter. */
	uintptr_half_t          ct_kind;     /* The kind of type (one of `CTYPE_KIND_*'). */
	struct ctype           *ct_children; /* [0..1] Derived types (all of these have `CTYPE_KIND_HASSIBLING()') */
	struct ctype           *_cp_sib;     /* [0..1] Sibling type */
	struct ctyperef         cp_base;     /* Pointed-to type (and const/volatile flags) */
};
#define _POINTER_CTYPE_INIT(children, sib, base_typ, base_flags) \
	{ 0x7fff, CTYPE_KIND_PTR, children, sib, { base_typ, { NULL, NULL }, base_flags } }


#define DEFINE_CTYPE(T, name)        \
	DATDEF T _##name ASMNAME(#name); \
	PUBLIC T _##name 
#ifdef __ARCH_HAVE_COMPAT
#define DEFINE_CTYPE_TRIPLE(kind, name)                                                                                                                                      \
	DEFINE_CTYPE(struct _basic_ctype, ctype_##name)                      = _BASIC_CTYPE_INIT(kind, &ctype_##name##_ptr);                                                     \
	DEFINE_CTYPE(struct _pointer_ctype, ctype_##name##_ptr)              = _POINTER_CTYPE_INIT(NULL, &ctype_##name##_const_ptr, &ctype_##name, CTYPEREF_FLAG_NORMAL);        \
	DEFINE_CTYPE(struct _pointer_ctype, ctype_##name##_const_ptr)        = _POINTER_CTYPE_INIT(NULL, &ctype_##name##_compat_ptr, &ctype_##name, CTYPEREF_FLAG_CONST);        \
	DEFINE_CTYPE(struct _pointer_ctype, ctype_##name##_compat_ptr)       = _POINTER_CTYPE_INIT(NULL, &ctype_##name##_const_compat_ptr, &ctype_##name, CTYPEREF_FLAG_NORMAL); \
	DEFINE_CTYPE(struct _pointer_ctype, ctype_##name##_const_compat_ptr) = _POINTER_CTYPE_INIT(NULL, NULL, &ctype_##name, CTYPEREF_FLAG_CONST);
#else /* __ARCH_HAVE_COMPAT */
#define DEFINE_CTYPE_TRIPLE(kind, name)                                                                                                                        \
	DEFINE_CTYPE(struct _basic_ctype, ctype_##name)               = _BASIC_CTYPE_INIT(kind, &ctype_##name##_ptr);                                              \
	DEFINE_CTYPE(struct _pointer_ctype, ctype_##name##_ptr)       = _POINTER_CTYPE_INIT(NULL, &ctype_##name##_const_ptr, &ctype_##name, CTYPEREF_FLAG_NORMAL); \
	DEFINE_CTYPE(struct _pointer_ctype, ctype_##name##_const_ptr) = _POINTER_CTYPE_INIT(NULL, NULL, &ctype_##name, CTYPEREF_FLAG_CONST);
#endif /* !__ARCH_HAVE_COMPAT */

DEFINE_CTYPE(struct _basic_ctype, ctype_bool)                = _BASIC_CTYPE_INIT(CTYPE_KIND_BOOL, NULL);
DEFINE_CTYPE(struct _basic_ctype, ctype_ieee754_float)       = _BASIC_CTYPE_INIT(CTYPE_KIND_IEEE754_FLOAT, NULL);
DEFINE_CTYPE(struct _basic_ctype, ctype_ieee754_double)      = _BASIC_CTYPE_INIT(CTYPE_KIND_IEEE754_DOUBLE, NULL);
DEFINE_CTYPE(struct _basic_ctype, ctype_ieee854_long_double) = _BASIC_CTYPE_INIT(CTYPE_KIND_IEEE854_LONG_DOUBLE, NULL);
DEFINE_CTYPE_TRIPLE(CTYPE_KIND_VOID, void)
#ifdef __CHAR_UNSIGNED__
DEFINE_CTYPE_TRIPLE(CTYPE_KIND_Un(__SIZEOF_CHAR__), char)
#else /* __CHAR_UNSIGNED__ */
DEFINE_CTYPE_TRIPLE(CTYPE_KIND_Sn(__SIZEOF_CHAR__), char)
#endif /* !__CHAR_UNSIGNED__ */
DEFINE_CTYPE_TRIPLE(CTYPE_KIND_Sn(__SIZEOF_CHAR__), signed_char)
DEFINE_CTYPE_TRIPLE(CTYPE_KIND_Un(__SIZEOF_CHAR__), unsigned_char)
DEFINE_CTYPE_TRIPLE(CTYPE_KIND_Sn(__SIZEOF_SHORT__), short)
DEFINE_CTYPE_TRIPLE(CTYPE_KIND_Un(__SIZEOF_SHORT__), unsigned_short)
DEFINE_CTYPE_TRIPLE(CTYPE_KIND_Sn(__SIZEOF_INT__), int)
DEFINE_CTYPE_TRIPLE(CTYPE_KIND_Un(__SIZEOF_INT__), unsigned_int)
DEFINE_CTYPE_TRIPLE(CTYPE_KIND_Sn(__SIZEOF_LONG__), long)
DEFINE_CTYPE_TRIPLE(CTYPE_KIND_Un(__SIZEOF_LONG__), unsigned_long)
DEFINE_CTYPE_TRIPLE(CTYPE_KIND_Sn(__SIZEOF_LONG_LONG__), long_long)
DEFINE_CTYPE_TRIPLE(CTYPE_KIND_Un(__SIZEOF_LONG_LONG__), unsigned_long_long)
DEFINE_CTYPE_TRIPLE(CTYPE_KIND_Un(2), char16_t)
DEFINE_CTYPE_TRIPLE(CTYPE_KIND_Un(4), char32_t)
#undef DEFINE_CTYPE_TRIPLE
#undef DEFINE_CTYPE

PRIVATE struct ctype *const standalong_ctypes[] = {
	&ctype_bool,
	&ctype_ieee754_float,
	&ctype_ieee754_double,
	&ctype_ieee854_long_double,
};

struct ctype_triple {
	struct ctype *ct_base;
	struct ctype *ct_ptr;
	struct ctype *ct_const_ptr;
#ifdef __ARCH_HAVE_COMPAT
	struct ctype *ct_compat_ptr;
	struct ctype *ct_const_compat_ptr;
#define CTYPE_TRIPLE_INIT(name)                                      \
	{ &ctype_##name, &ctype_##name##_ptr, &ctype_##name##_const_ptr, \
	  &ctype_##name##_compat_ptr, &ctype_##name##_const_compat_ptr }
#else /* __ARCH_HAVE_COMPAT */
#define CTYPE_TRIPLE_INIT(name) \
	{ &ctype_##name, &ctype_##name##_ptr, &ctype_##name##_const_ptr }
#endif /* !__ARCH_HAVE_COMPAT */
};

PRIVATE struct ctype_triple const builtin_triples[] = {
	CTYPE_TRIPLE_INIT(void),
	CTYPE_TRIPLE_INIT(char),
	CTYPE_TRIPLE_INIT(signed_char),
	CTYPE_TRIPLE_INIT(unsigned_char),
	CTYPE_TRIPLE_INIT(short),
	CTYPE_TRIPLE_INIT(unsigned_short),
	CTYPE_TRIPLE_INIT(int),
	CTYPE_TRIPLE_INIT(unsigned_int),
	CTYPE_TRIPLE_INIT(long),
	CTYPE_TRIPLE_INIT(unsigned_long),
	CTYPE_TRIPLE_INIT(long_long),
	CTYPE_TRIPLE_INIT(unsigned_long_long),
	CTYPE_TRIPLE_INIT(char16_t),
	CTYPE_TRIPLE_INIT(char32_t),
};


INTERN void NOTHROW(KCALL reset_builtin_types)(void) {
	unsigned int i;
	for (i = 0; i < COMPILER_LENOF(standalong_ctypes); ++i) {
		standalong_ctypes[i]->ct_refcnt   = 0x7fff;
		standalong_ctypes[i]->ct_children = NULL;
	}
	for (i = 0; i < COMPILER_LENOF(builtin_triples); ++i) {
		builtin_triples[i].ct_base->ct_refcnt         = 0x7fff;
		builtin_triples[i].ct_base->ct_children       = builtin_triples[i].ct_ptr;
		builtin_triples[i].ct_ptr->ct_refcnt          = 0x7fff;
		builtin_triples[i].ct_ptr->ct_children        = NULL;
		builtin_triples[i].ct_ptr->ct_sibling         = builtin_triples[i].ct_const_ptr;
		builtin_triples[i].ct_const_ptr->ct_refcnt    = 0x7fff;
		builtin_triples[i].ct_const_ptr->ct_children  = NULL;
#ifdef __ARCH_HAVE_COMPAT
		builtin_triples[i].ct_const_ptr->ct_sibling         = builtin_triples[i].ct_compat_ptr;
		builtin_triples[i].ct_compat_ptr->ct_refcnt         = 0x7fff;
		builtin_triples[i].ct_compat_ptr->ct_children       = NULL;
		builtin_triples[i].ct_compat_ptr->ct_sibling        = builtin_triples[i].ct_const_compat_ptr;
		builtin_triples[i].ct_const_compat_ptr->ct_refcnt   = 0x7fff;
		builtin_triples[i].ct_const_compat_ptr->ct_children = NULL;
		builtin_triples[i].ct_const_compat_ptr->ct_sibling  = NULL;
#else /* __ARCH_HAVE_COMPAT */
		builtin_triples[i].ct_const_ptr->ct_sibling = NULL;
#endif /* !__ARCH_HAVE_COMPAT */
	}
}




/* Return the appropriate C-type for a given arch-specific register `regno'
 * If no such type exists, return `NULL' instead.
 * @param: buflen: The required buffer size to hold `regno' */
PUBLIC WUNUSED REF struct ctype *
NOTHROW(FCALL ctype_for_register)(unsigned int regno, size_t buflen) {
	REF struct ctype *result;
#if defined(__x86_64__) || defined(__i386__)
	switch (regno & X86_REGISTER_CLASSMASK) {

	case X86_REGISTER_GENERAL_PURPOSE:
		switch (regno & X86_REGISTER_IDMASK) {

		case X86_REGISTER_GENERAL_PURPOSE_PSP & X86_REGISTER_IDMASK:
		case X86_REGISTER_GENERAL_PURPOSE_PBP & X86_REGISTER_IDMASK:
		case X86_REGISTER_GENERAL_PURPOSE_PSI & X86_REGISTER_IDMASK:
		case X86_REGISTER_GENERAL_PURPOSE_PDI & X86_REGISTER_IDMASK:
try_pointer_register:
			if (buflen == dbg_current_sizeof_pointer()) {
#ifdef __x86_64__
				if (buflen == 4)
					return incref(&ctype_void_compat_ptr);
#endif /* __x86_64__ */
				return incref(&ctype_void_ptr);
			}
			break;

		default: break;
		}
		break;

	case X86_REGISTER_FLOAT:
		if (buflen == SIZEOF_CTYPE_IEEE754_FLOAT) {
			return incref(&ctype_ieee754_float);
		} else if (buflen == SIZEOF_CTYPE_IEEE754_DOUBLE) {
			return incref(&ctype_ieee754_double);
		} else if (buflen == SIZEOF_CTYPE_IEEE854_LONG_DOUBLE) {
			return incref(&ctype_ieee854_long_double);
		}
		break;

	case X86_REGISTER_CONTROL:
		switch (regno & X86_REGISTER_IDMASK) {

		case X86_REGISTER_CONTROL_CR2 & X86_REGISTER_IDMASK:
		case X86_REGISTER_CONTROL_CR3 & X86_REGISTER_IDMASK:
			goto try_pointer_register;

		default:
			break;
		}
		break;

	case X86_REGISTER_MISC:
		switch (regno & X86_REGISTER_IDMASK) {

		case X86_REGISTER_MISC_PIP & X86_REGISTER_IDMASK:
		case X86_REGISTER_MISC_GDT_BASE & X86_REGISTER_IDMASK:
		case X86_REGISTER_MISC_IDT_BASE & X86_REGISTER_IDMASK:
		case X86_REGISTER_MISC_FSBASE & X86_REGISTER_IDMASK:
		case X86_REGISTER_MISC_GSBASE & X86_REGISTER_IDMASK:
		case X86_REGISTER_MISC_FIP & X86_REGISTER_IDMASK:
		case X86_REGISTER_MISC_FDP & X86_REGISTER_IDMASK:
			goto try_pointer_register;

		default:
			break;
		}
		break;

	default:
		break;
	}
#endif /* __x86_64__ || __i386__ */
	if unlikely(regno == ARCH_REGISTER_NONE)
		return NULL;
	if (buflen == 1) {
		result = &ctype_u8;
	} else if (buflen == 2) {
		result = &ctype_u16;
	} else if (buflen == 4) {
		result = &ctype_u32;
	} else if (buflen == 8) {
		result = &ctype_u64;
	} else {
		return NULL;
	}
	return incref(result);
}



/* Enumerate/find the fields of a given struct.
 * @param: cb:   Callback to-be invoked for the field.
 * @param: arg:  Cookie-argument for `cb'
 * @return: * :  The sum of return values of `cb'
 * @return: < 0: A propagated, negative return value of `cb'. */
PUBLIC NONNULL((1, 2)) ssize_t
NOTHROW(FCALL ctype_struct_field)(struct ctype *__restrict self,
                                  ctype_struct_field_callback_t cb,
                                  void *arg) {
	ssize_t temp, result = 0;
	di_debuginfo_cu_parser_t parser;
	di_debuginfo_cu_abbrev_t abbrev;
	unsigned int error;
	struct debugmodule *mod;
	byte_t const *reader;
	size_t depth;
	/* Sanity check: we're actually dealing with a struct! */
	if unlikely(!CTYPE_KIND_ISSTRUCT(self->ct_kind))
		goto done0;
	reader = self->ct_struct.ct_info.ddl_di_hdr;
	mod    = self->ct_struct.ct_info.ddl_module;
	error = debuginfo_cu_parser_loadunit(&reader, mod->dm_sections.ds_debug_info_end,
	                                     di_debug_sections_as_di_debuginfo_cu_parser_sections(&mod->dm_sections),
	                                     &parser, &abbrev, self->ct_struct.ct_info.ddl_di_pos);
	if unlikely(error != DEBUG_INFO_ERROR_SUCCESS)
		goto done;
	depth = parser.dup_child_depth;
	do {
		if (parser.dup_child_depth == depth &&
		    parser.dup_comp.dic_tag == DW_TAG_member) {
			di_debuginfo_member_t member;
			if unlikely(!debuginfo_cu_parser_loadattr_member(&parser, &member))
				break;
			/* Special case: When the offset is unknown, but we're working on a union,
			 *               then we know that the offset should actually be `0' */
			if (member.m_offset == (uintptr_t)-1 && CTYPE_KIND_STRUCT_ISUNION(self->ct_kind))
				member.m_offset = 0;
			if (!member.m_name) {
				/* TODO: Enumerate an inlined struct/union */
			} else {
				/* Enumerate this member. */
				temp = (*cb)(arg, &member, &parser, mod);
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
		} else {
			debuginfo_cu_parser_skipattr(&parser);
		}
	} while (debuginfo_cu_parser_next(&parser) &&
	         parser.dup_child_depth >= depth);
done:
	debuginfo_cu_abbrev_fini(&abbrev);
done0:
	return result;
err:
	debuginfo_cu_abbrev_fini(&abbrev);
	return temp;
}


/* Find a field of a given struct-kind C-type.
 * @return: DBX_EOK:     Success.
 * @return: DBX_ENOENT:  No field with this name.
 * @return: DBX_EINTERN: Debug information is corrupted. */
PUBLIC WUNUSED NONNULL((1, 2, 4, 5)) dbx_errno_t
NOTHROW(FCALL ctype_struct_getfield)(struct ctype *__restrict self,
                                     char const *__restrict name, size_t namelen,
                                     /*out*/ struct ctyperef *__restrict pfield_type,
                                     /*out*/ ptrdiff_t *__restrict pfield_offset) {
	di_debuginfo_cu_parser_t parser;
	di_debuginfo_cu_abbrev_t abbrev;
	unsigned int error;
	struct debugmodule *mod;
	byte_t const *reader;
	size_t depth;
	/* Sanity check: we're actually dealing with a struct! */
	if unlikely(!CTYPE_KIND_ISSTRUCT(self->ct_kind))
		goto done0;
	reader = self->ct_struct.ct_info.ddl_di_hdr;
	mod    = self->ct_struct.ct_info.ddl_module;
	error = debuginfo_cu_parser_loadunit(&reader, mod->dm_sections.ds_debug_info_end,
	                                     di_debug_sections_as_di_debuginfo_cu_parser_sections(&mod->dm_sections),
	                                     &parser, &abbrev, self->ct_struct.ct_info.ddl_di_pos);
	if unlikely(error != DEBUG_INFO_ERROR_SUCCESS)
		goto done;
	depth = parser.dup_child_depth;
	do {
		if (parser.dup_child_depth == depth &&
		    parser.dup_comp.dic_tag == DW_TAG_member) {
			di_debuginfo_member_t member;
			if unlikely(!debuginfo_cu_parser_loadattr_member(&parser, &member))
				break;
			if (!member.m_name) {
				/* TODO: Enumerate an inlined struct/union */
			} else {
				if (strlen(member.m_name) == namelen &&
					memcmp(member.m_name, name, namelen * sizeof(char)) == 0) {
					dbx_errno_t result;
					/* Found the requested field! */
					if (member.m_offset == (uintptr_t)-1)
						member.m_offset = 0;
					/* Write-back the field's offset. */
					*pfield_offset = member.m_offset;
					/* Load the field's type. */
					result = ctype_fromdw(mod, &parser, member.m_type, pfield_type);
					debuginfo_cu_abbrev_fini(&abbrev);
					return result;
				}
			}
		} else {
			debuginfo_cu_parser_skipattr(&parser);
		}
	} while (debuginfo_cu_parser_next(&parser) &&
	         parser.dup_child_depth >= depth);
done:
	debuginfo_cu_abbrev_fini(&abbrev);
done0:
	return DBX_ENOENT;
}



/* Load a C-type from a given `type_debug_info' which should be
 * loaded with the help of an internal copy made from `cu_parser'.
 * The given `type_debug_info' is a pointer like `di_debuginfo_member_t::m_type'
 * @param: ptyperef_flags: When non-NULL, store type-reference flags here (`CTYPEREF_FLAG_*')
 * @return: DBX_EOK:     A reference to the associated type.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: Debug information was corrupted. */
PUBLIC WUNUSED NONNULL((1, 2, 4)) dbx_errno_t
NOTHROW(FCALL ctype_fromdw)(struct debugmodule *__restrict mod,
                            di_debuginfo_cu_parser_t const *__restrict cu_parser,
                            byte_t const *type_debug_info,
                            /*out*/ struct ctyperef *__restrict presult) {
	dbx_errno_t result = DBX_EOK;
	di_debuginfo_cu_parser_t parser;
	di_debuginfo_type_t typinfo;
	memset(presult, 0, sizeof(*presult));
again:
	if unlikely(!type_debug_info)
		goto err_corrupt;
	memcpy(&parser, cu_parser, sizeof(di_debuginfo_cu_parser_t));
	parser.dup_cu_info_pos = (byte_t *)type_debug_info;
	if (!debuginfo_cu_parser_next(&parser))
		goto err_corrupt;
	if (!debuginfo_cu_parser_loadattr_type(&parser, &typinfo))
		goto err_corrupt;
	if (!presult->ct_info.ci_name) {
		presult->ct_info.ci_name = typinfo.t_name;
		if (!presult->ct_info.ci_name)
			presult->ct_info.ci_name = typinfo.t_rawname;
		if (!presult->ct_info.ci_name)
			presult->ct_info.ci_name = (char *)-1;
		else {
			presult->ct_info.ci_nameref = incref(mod);
		}
	}
	switch (parser.dup_comp.dic_tag) {

	case DW_TAG_unspecified_type:
		presult->ct_typ = incref(&ctype_int);
		break;

	case DW_TAG_base_type:
		switch (typinfo.t_encoding) {

		case DW_ATE_address:
			if (!typinfo.t_sizeof)
				typinfo.t_sizeof = dbg_current_sizeof_pointer();
			/* void-pointer. */
			if (typinfo.t_sizeof == sizeof(void *)) {
				presult->ct_typ = incref(&ctype_void_ptr);
			} else
#ifdef __ARCH_HAVE_COMPAT
			if (typinfo.t_sizeof == __ARCH_COMPAT_SIZEOF_POINTER) {
				presult->ct_typ = incref(&ctype_void_compat_ptr);
			} else
#endif /* __ARCH_HAVE_COMPAT */
			{
				struct ctyperef ctr;
				memset(&ctr, 0, sizeof(ctr));
				ctr.ct_typ = &ctype_void;
				presult->ct_typ = ctype_ptr(&ctr, typinfo.t_sizeof);
			}
			break;

		case DW_ATE_boolean:
			if (!typinfo.t_sizeof || typinfo.t_sizeof == sizeof(bool)) {
				presult->ct_typ = incref(&ctype_bool);
			} else {
				REF struct ctype *ct;
				ct = (REF struct ctype *)dbx_malloc(sizeof(struct _basic_ctype));
				if unlikely(!ct)
					goto err_nomem;
				ct->ct_refcnt   = 1;
				ct->ct_kind     = CTYPE_KIND_BOOL | typinfo.t_sizeof;
				ct->ct_children = NULL;
				presult->ct_typ  = ct;
			}
			break;

		case DW_ATE_float:
			if (typinfo.t_sizeof == SIZEOF_CTYPE_IEEE854_LONG_DOUBLE) {
				presult->ct_typ = incref(&ctype_ieee854_long_double);
			} else if (typinfo.t_sizeof == SIZEOF_CTYPE_IEEE754_DOUBLE) {
				presult->ct_typ = incref(&ctype_ieee754_double);
			} else if (typinfo.t_sizeof == SIZEOF_CTYPE_IEEE754_FLOAT) {
				presult->ct_typ = incref(&ctype_ieee754_float);
			} else {
				goto err_corrupt;
			}
			break;

		case DW_ATE_signed:
do_signed: ATTR_UNUSED;
			if (!typinfo.t_sizeof)
				typinfo.t_sizeof = sizeof(int);
			if (typinfo.t_sizeof == 1)
				presult->ct_typ = incref(&ctype_s8);
			else if (typinfo.t_sizeof == 2)
				presult->ct_typ = incref(&ctype_s16);
			else if (typinfo.t_sizeof == 4)
				presult->ct_typ = incref(&ctype_s32);
			else if (typinfo.t_sizeof == 8)
				presult->ct_typ = incref(&ctype_s64);
			else {
				goto err_corrupt;
			}
			break;

		case DW_ATE_unsigned:
do_unsigned: ATTR_UNUSED;
			if (!typinfo.t_sizeof)
				typinfo.t_sizeof = sizeof(int);
			if (typinfo.t_sizeof == 1)
				presult->ct_typ = incref(&ctype_u8);
			else if (typinfo.t_sizeof == 2)
				presult->ct_typ = incref(&ctype_u16);
			else if (typinfo.t_sizeof == 4)
				presult->ct_typ = incref(&ctype_u32);
			else if (typinfo.t_sizeof == 8)
				presult->ct_typ = incref(&ctype_u64);
			else {
				goto err_corrupt;
			}
			break;

		case DW_ATE_signed_char:
		case DW_ATE_unsigned_char:
		case DW_ATE_UTF:
			if (!typinfo.t_sizeof)
				typinfo.t_sizeof = sizeof(char);
			if (typinfo.t_sizeof == sizeof(char))
				presult->ct_typ = incref(&ctype_char);
			else {
#ifdef __CHAR_UNSIGNED__
				goto do_unsigned;
#else /* __CHAR_UNSIGNED__ */
				goto do_signed;
#endif /* !__CHAR_UNSIGNED__ */
			}
			break;

		default:
			break;
		}
		break;

	case DW_TAG_array_type: {
		struct ctyperef elem_type;
		uintptr_t elem_count = 0;
		if (debuginfo_cu_parser_nextchild(&parser)) {
			size_t depth = parser.dup_child_depth;
			do {
				if (parser.dup_child_depth == depth &&
				    parser.dup_comp.dic_tag == DW_TAG_subrange_type) {
					di_debuginfo_component_attrib_t attr;
					DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, &parser) {
						if (attr.dica_name == DW_AT_upper_bound) {
							if (debuginfo_cu_parser_getconst(&parser, attr.dica_form, &elem_count))
								++elem_count;
							goto got_elem_count;
						}
					}
				} else {
					debuginfo_cu_parser_skipattr(&parser);
				}
			} while (debuginfo_cu_parser_next(&parser) &&
			         parser.dup_child_depth >= depth);
		}
got_elem_count:
		result = ctype_fromdw(mod, &parser, typinfo.t_type, &elem_type);
		if unlikely(result != DBX_EOK)
			goto done;
		presult->ct_flags = elem_type.ct_flags; /* Copy-over type flags from the element type. */
		presult->ct_typ   = ctype_array(&elem_type, elem_count);
		ctyperef_fini(&elem_type);
		if unlikely(!presult->ct_typ)
			goto err_nomem;
	}	break;

	case DW_TAG_enumeration_type: {
		REF struct ctype *result_type;
		if (!typinfo.t_sizeof)
			typinfo.t_sizeof = sizeof(int);
		result_type = (REF struct ctype *)dbx_malloc(offsetafter(struct ctype, ct_enum));
		if unlikely(!result_type)
			goto err_nomem;
		result_type->ct_refcnt   = 1;
		result_type->ct_kind     = CTYPE_KIND_CLASSOF(CTYPE_KIND_ENUM) | typinfo.t_sizeof;
		result_type->ct_children = NULL;
		result_type->ct_enum.ddl_module = incref(mod);
		result_type->ct_enum.ddl_di_hdr = parser.dup_cu_info_hdr;
		result_type->ct_enum.ddl_di_pos = parser.dup_cu_info_pos;
		presult->ct_typ = result_type; /* Inherit reference */
	}	break;

	case DW_TAG_pointer_type:
	case DW_TAG_reference_type:
	case DW_TAG_rvalue_reference_type: {
		struct ctyperef pointed_to_type;
		/* Parse the inner type. */
		result = ctype_fromdw(mod, &parser, typinfo.t_type, &pointed_to_type);
		if unlikely(result != DBX_EOK)
			goto done;
		presult->ct_flags = CTYPEREF_FLAG_NORMAL;
		if (!typinfo.t_sizeof)
			typinfo.t_sizeof = dbg_current_sizeof_pointer();
		presult->ct_typ = ctype_ptr(&pointed_to_type, typinfo.t_sizeof);
		ctyperef_fini(&pointed_to_type);
		if unlikely(!presult->ct_typ)
			goto err_nomem;
	}	break;

	case DW_TAG_subroutine_type: {
		struct ctyperef return_type;
		struct ctyperef *argv;
		size_t argc;
		uint16_t cc = CTYPE_KIND_FUNPROTO_CC_DEFAULT;
		/* Load the function return type. */
		if (!typinfo.t_type) {
			memset(&return_type, 0, sizeof(return_type));
			return_type.ct_typ = incref(&ctype_int);
		} else {
			result = ctype_fromdw(mod, &parser, typinfo.t_type, &return_type);
			if unlikely(result != DBX_EOK)
				goto done;
		}
		argv = NULL;
		argc = 0;
		if (debuginfo_cu_parser_nextchild(&parser)) {
			/* Load function argument types. */
			size_t depth = parser.dup_child_depth;
			do {
				if (parser.dup_child_depth == depth &&
				    (parser.dup_comp.dic_tag == DW_TAG_formal_parameter ||
				     parser.dup_comp.dic_tag == DW_TAG_unspecified_parameters)) {
					if (parser.dup_comp.dic_tag == DW_TAG_unspecified_parameters) {
						cc |= CTYPE_KIND_FUNPROTO_VARARGS;
					} else {
						byte_t const *parameter_type_pointer = NULL;
						di_debuginfo_component_attrib_t attr;
						if ((argc + 1) > dbx_malloc_usable_size(argv) / sizeof(struct ctyperef)) {
							struct ctyperef *new_argv;
							new_argv = (struct ctyperef *)dbx_realloc(argv, (argc + 1) * sizeof(struct ctyperef));
							if unlikely(!new_argv) {
								result = DBX_ENOMEM;
								goto err_fuction_argv;
							}
							argv = new_argv;
						}
						DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, &parser) {
							if (attr.dica_name == DW_AT_type)
								debuginfo_cu_parser_getref(&parser, attr.dica_form, &parameter_type_pointer);
						}
						if (!parameter_type_pointer) {
							ctypeinfo_init(&argv[argc].ct_info);
							argv[argc].ct_flags = CTYPEREF_FLAG_NORMAL;
							argv[argc].ct_typ   = incref(&ctype_int);
						} else {
							result = ctype_fromdw(mod, &parser, parameter_type_pointer, &argv[argc]);
							if unlikely(result != DBX_EOK)
								goto err_fuction_argv;
						}
						++argc;
					}
				} else {
					debuginfo_cu_parser_skipattr(&parser);
				}
			} while (debuginfo_cu_parser_next(&parser) &&
			         parser.dup_child_depth >= depth);
		}
		/* Form the actual function type. */
		presult->ct_typ = ctype_function(&return_type, argc, argv, cc);
		if unlikely(!presult->ct_typ) {
			result = DBX_ENOMEM;
err_fuction_argv:
			while (argc) {
				--argc;
				ctyperef_fini(&argv[argc]);
			}
			dbx_free(argv);
			goto done;
		}
		while (argc) {
			--argc;
			ctyperef_fini(&argv[argc]);
		}
		dbx_free(argv);
		ctyperef_fini(&return_type);
	}	break;

	case DW_TAG_class_type:
	case DW_TAG_structure_type:
	case DW_TAG_union_type:
	case DW_TAG_interface_type: {
		REF struct ctype *struct_type;
		struct_type = (REF struct ctype *)dbx_malloc(offsetafter(struct ctype, ct_struct));
		if unlikely(!struct_type)
			goto err_nomem;
		struct_type->ct_refcnt = 1;
		struct_type->ct_kind   = CTYPE_KIND_STRUCT;
		if (parser.dup_comp.dic_tag == DW_TAG_union_type)
			struct_type->ct_kind = CTYPE_KIND_UNION;
		struct_type->ct_children = NULL;
		struct_type->ct_struct.ct_info.ddl_module = incref(mod);
		struct_type->ct_struct.ct_info.ddl_di_hdr = parser.dup_cu_info_hdr;
		struct_type->ct_struct.ct_info.ddl_di_pos = parser.dup_cu_info_pos;
		struct_type->ct_struct.ct_sizeof          = typinfo.t_sizeof;
		presult->ct_typ = struct_type; /* Inherit reference */
	}	break;

	case DW_TAG_typedef:
		type_debug_info = typinfo.t_type;
		goto again;

	case DW_TAG_const_type:
		presult->ct_flags |= CTYPEREF_FLAG_CONST;
		type_debug_info = typinfo.t_type;
		goto again;

	case DW_TAG_volatile_type:
		presult->ct_flags |= CTYPEREF_FLAG_VOLATILE;
		type_debug_info = typinfo.t_type;
		goto again;

	case DW_TAG_restrict_type:
		presult->ct_flags |= CTYPEREF_FLAG_RESTRICT;
		type_debug_info = typinfo.t_type;
		goto again;

	case DW_TAG_atomic_type:
		presult->ct_flags |= CTYPEREF_FLAG_ATOMIC;
		type_debug_info = typinfo.t_type;
		goto again;

	default:
		goto err_corrupt;
	}
done:
	if (presult->ct_info.ci_name == (char const *)-1 || result != DBX_EOK) {
		presult->ct_info.ci_name = NULL;
		xdecref(presult->ct_info.ci_nameref);
		presult->ct_info.ci_nameref = NULL;
	}
	return result;
err_corrupt:
	result = DBX_EINTERN;
	goto done;
err_nomem:
	result = DBX_ENOMEM;
	goto done;
}

DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_MODDBX_CTYPE_C */
