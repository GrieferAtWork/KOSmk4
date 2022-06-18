/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
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
#ifdef CONFIG_HAVE_DEBUGGER

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
#include <libdebuginfo/dwarf.h>

/**/
#include "include/cmodule.h"
#include "include/ctype.h"
#include "include/malloc.h"

#if defined(__x86_64__) || defined(__i386__)
#include <asm/registers.h>
#include <asm/registers-compat.h>
#endif /* __x86_64__ || __i386__ */

DECL_BEGIN

PUBLIC NONNULL((1)) void
NOTHROW(FCALL ctype_destroy)(struct ctype *__restrict self) {
	static_assert(offsetof(struct ctype, ct_enum) == offsetof(struct ctype, ct_struct));
	switch (CTYPE_KIND_CLASSOF(self->ct_kind)) {

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_ENUM):
		if (CTYPE_KIND_ISENUM(self->ct_kind)) {
	case CTYPE_KIND_CLASSOF(CTYPE_KIND_STRUCT):
			cmoduledip_fini(&self->ct_enum);
		}
		break;

	case CTYPE_KIND_CLASSOF(CTYPE_KIND_FUNCTION): {
		size_t i;
		for (i = 0; i < self->ct_function.cf_argc; ++i)
			ctyperef_fini(&self->ct_function.cf_argv[i]);
	}	ATTR_FALLTHROUGH
	case CTYPE_KIND_CLASSOF(CTYPE_KIND_PTR):
	case CTYPE_KIND_CLASSOF(CTYPE_KIND_ARRAY): {
		static_assert(offsetof(struct ctype, ct_pointer.cp_base.ct_typ) == offsetof(struct ctype, ct_function.cf_base));
		static_assert(offsetof(struct ctype, ct_pointer.cp_base.ct_typ) == offsetof(struct ctype, ct_array.ca_elem));
		static_assert(offsetof(struct ctype, ct_pointer.cp_base.ct_info) == offsetof(struct ctype, ct_array.ca_eleminfo));
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


/* Return  the   array-version  of   the  given   C-type
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
		if (a->ct_struct.ct_info.cd_dip != b->ct_struct.ct_info.cd_dip)
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

/* Return the common type which  can be used to  represent both `a' and  `b'.
 * This common type is the promotion of `a' and `b' if those types are equal,
 * and  otherwise is the larger integer type of the two. If neither types are
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
			goto return_a;
		if (CTYPE_KIND_SIZEOF(akind) < CTYPE_KIND_SIZEOF(bkind))
			goto return_b;
		/* Return whichever isn't a boolean. */
		if (CTYPE_KIND_ISBOOL(bkind))
			goto return_a;
		if (CTYPE_KIND_ISBOOL(akind))
			goto return_b;
		/* Same type sizes. -> Return the signed of the two types. */
		if (!CTYPE_KIND_INT_ISUNSIGNED(akind) && CTYPE_KIND_INT_ISUNSIGNED(bkind))
			goto return_a;
		if (!CTYPE_KIND_INT_ISUNSIGNED(bkind) && CTYPE_KIND_INT_ISUNSIGNED(akind))
			goto return_b;
		/* Both types are integers, and have the same size and sign.
		 * Prefer `long long' over `long', `long' over `int', and `int' over `short' */
#if __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
		if (a == &ctype_long_long || a == &ctype_unsigned_long_long)
			goto return_a;
		if (b == &ctype_long_long || b == &ctype_unsigned_long_long)
			goto return_b;
#endif /* __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ */
#if __SIZEOF_INT__ == __SIZEOF_LONG__
		if (a == &ctype_long || a == &ctype_unsigned_long)
			goto return_a;
		if (b == &ctype_long || b == &ctype_unsigned_long)
			goto return_b;
#endif /* __SIZEOF_INT__ == __SIZEOF_LONG__ */
#if __SIZEOF_SHORT__ == __SIZEOF_INT__
		if (a == &ctype_int || a == &ctype_unsigned_int)
			goto return_a;
		if (b == &ctype_int || b == &ctype_unsigned_int)
			goto return_b;
#endif /* __SIZEOF_SHORT__ == __SIZEOF_INT__ */
		/* Fallback: The 2 types seem to be identical, so just return `a' over `b' */
		goto return_a;
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
			bzero(&ct, sizeof(ct));
			ct.ct_typ = &ctype_void;
			return ctype_ptr(&ct, CTYPE_KIND_SIZEOF(akind));
		}
	}
	return NULL;
return_a:
	return incref(a);
return_b:
	return incref(b);
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
#ifdef __ARCH_HAVE_COMPAT
#define _COMPAT_POINTER_CTYPE_INIT(children, sib, base_typ, base_flags) \
	{ 0x7fff, CTYPE_KIND_COMPAT_PTR, children, sib, { base_typ, { NULL, NULL }, base_flags } }
#endif /* __ARCH_HAVE_COMPAT */


#define DEFINE_CTYPE(T, name)        \
	DATDEF T _##name ASMNAME(#name); \
	PUBLIC T _##name
#ifdef __ARCH_HAVE_COMPAT
#define DEFINE_CTYPE_TRIPLE(kind, name)                                                                                                                                             \
	DEFINE_CTYPE(struct _basic_ctype, ctype_##name)                      = _BASIC_CTYPE_INIT(kind, &ctype_##name##_ptr);                                                            \
	DEFINE_CTYPE(struct _pointer_ctype, ctype_##name##_ptr)              = _POINTER_CTYPE_INIT(NULL, &ctype_##name##_const_ptr, &ctype_##name, CTYPEREF_FLAG_NORMAL);               \
	DEFINE_CTYPE(struct _pointer_ctype, ctype_##name##_const_ptr)        = _POINTER_CTYPE_INIT(NULL, &ctype_##name##_compat_ptr, &ctype_##name, CTYPEREF_FLAG_CONST);               \
	DEFINE_CTYPE(struct _pointer_ctype, ctype_##name##_compat_ptr)       = _COMPAT_POINTER_CTYPE_INIT(NULL, &ctype_##name##_const_compat_ptr, &ctype_##name, CTYPEREF_FLAG_NORMAL); \
	DEFINE_CTYPE(struct _pointer_ctype, ctype_##name##_const_compat_ptr) = _COMPAT_POINTER_CTYPE_INIT(NULL, NULL, &ctype_##name, CTYPEREF_FLAG_CONST);
#else /* __ARCH_HAVE_COMPAT */
#define DEFINE_CTYPE_TRIPLE(kind, name)                                                                                                                        \
	DEFINE_CTYPE(struct _basic_ctype, ctype_##name)               = _BASIC_CTYPE_INIT(kind, &ctype_##name##_ptr);                                              \
	DEFINE_CTYPE(struct _pointer_ctype, ctype_##name##_ptr)       = _POINTER_CTYPE_INIT(NULL, &ctype_##name##_const_ptr, &ctype_##name, CTYPEREF_FLAG_NORMAL); \
	DEFINE_CTYPE(struct _pointer_ctype, ctype_##name##_const_ptr) = _POINTER_CTYPE_INIT(NULL, NULL, &ctype_##name, CTYPEREF_FLAG_CONST);
#endif /* !__ARCH_HAVE_COMPAT */

DEFINE_CTYPE(struct _basic_ctype, ctype_bool)           = _BASIC_CTYPE_INIT(CTYPE_KIND_BOOL, NULL);
DEFINE_CTYPE(struct _basic_ctype, ctype_ieee754_float)  = _BASIC_CTYPE_INIT(CTYPE_KIND_IEEE754_FLOAT, NULL);
DEFINE_CTYPE(struct _basic_ctype, ctype_ieee754_double) = _BASIC_CTYPE_INIT(CTYPE_KIND_IEEE754_DOUBLE, NULL);
#ifdef CTYPE_KIND_IEEE854_LONG_DOUBLE
DEFINE_CTYPE(struct _basic_ctype, ctype_ieee854_long_double) = _BASIC_CTYPE_INIT(CTYPE_KIND_IEEE854_LONG_DOUBLE, NULL);
#endif /* CTYPE_KIND_IEEE854_LONG_DOUBLE */
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
#ifdef CTYPE_KIND_IEEE854_LONG_DOUBLE
	&ctype_ieee854_long_double,
#endif /* CTYPE_KIND_IEEE854_LONG_DOUBLE */
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
	case X86_REGISTER_MMX:
	case X86_REGISTER_XMM:
	case X86_REGISTER_YMM:
		if (buflen == SIZEOF_CTYPE_IEEE754_FLOAT) {
			return incref(&ctype_ieee754_float);
		} else if (buflen == SIZEOF_CTYPE_IEEE754_DOUBLE) {
			return incref(&ctype_ieee754_double);
#ifdef CTYPE_KIND_IEEE854_LONG_DOUBLE
		} else if (buflen == SIZEOF_CTYPE_IEEE854_LONG_DOUBLE) {
			return incref(&ctype_ieee854_long_double);
#endif /* CTYPE_KIND_IEEE854_LONG_DOUBLE */
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




PRIVATE NONNULL((1, 2)) ssize_t
NOTHROW(FCALL dw_enumerate_fields)(struct cmodule *__restrict mod,
                                   byte_t const *__restrict dip,
                                   ctype_struct_field_callback_t cb,
                                   void *cookie,
                                   ptrdiff_t base_offset,
                                   bool *__restrict pstruct_has_children) {
	ssize_t temp, result = 0;
	di_debuginfo_cu_parser_t parser;
	struct cmodunit *cunit;
	size_t depth;
	bool is_union;
	/* Sanity check: we're actually dealing with a struct! */
	cunit = cmodule_findunit_from_dip(mod, dip);
	if unlikely(!cunit)
		goto done;
	cmodunit_parser_from_dip(cunit, mod, &parser, dip);
	if (parser.dup_comp.dic_tag != DW_TAG_class_type &&
	    parser.dup_comp.dic_tag != DW_TAG_structure_type &&
	    parser.dup_comp.dic_tag != DW_TAG_union_type &&
	    parser.dup_comp.dic_tag != DW_TAG_interface_type)
		goto done;
	is_union = parser.dup_comp.dic_tag == DW_TAG_union_type;
	debuginfo_cu_parser_skipattr(&parser);
	if (!debuginfo_cu_parser_nextchild(&parser))
		goto done;
	*pstruct_has_children = true;
	depth = parser.dup_child_depth;
	do {
		if (parser.dup_child_depth == depth) {
			switch (parser.dup_comp.dic_tag) {

			case DW_TAG_member: {
				di_debuginfo_member_t member;
				if unlikely(!debuginfo_cu_parser_loadattr_member(&parser, &member))
					break;
				if (member.m_type) {
					/* Special case: When the offset is unknown, but we're working on a union,
					 *               then  we  know that  the  offset should  actually  be `0' */
					if (member.m_offset == (uintptr_t)-1 && is_union)
						member.m_offset = 0;
					member.m_offset += base_offset;
					if (!member.m_name) {
						/* Enumerate an inlined struct/union */
						temp = dw_enumerate_fields(mod, member.m_type, cb, cookie,
						                           member.m_offset,
						                           pstruct_has_children);
					} else {
						/* Enumerate this member. */
						temp = (*cb)(cookie, &member, &parser, mod, cunit);
					}
					if unlikely(temp < 0)
						goto err;
					result += temp;
				}
			}	break;

			case DW_TAG_inheritance: {
				byte_t const *inherited_type = NULL;
				uintptr_t data_member_location = 0;
				di_debuginfo_component_attrib_t attr;
				/* Enumerate members from base-structures (in case of a c++-style derived type)
				 * NOTE: Dwarf uses `DW_TAG_inheritance' for this purpose, which in  turn
				 *       contains 2 attributes DW_AT_type and DW_AT_data_member_location! */
				DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, &parser) {
					switch (attr.dica_name) {

					case DW_AT_type:
						if unlikely(!debuginfo_cu_parser_getref(&parser, attr.dica_form,
						                                        &inherited_type))
							inherited_type = NULL;
						break;

					case DW_AT_data_member_location:
						if unlikely(!debuginfo_cu_parser_getconst(&parser, attr.dica_form,
						                                          &data_member_location,
						                                          _attr_reader))
							data_member_location = 0;
						break;

					default:
						break;
					}
				}
				if (inherited_type != NULL) {
					data_member_location += base_offset;
					temp = dw_enumerate_fields(mod, inherited_type,
					                           cb, cookie,
					                           data_member_location,
					                           pstruct_has_children);
					if unlikely(temp < 0)
						goto err;
					result += temp;
				}
			}	break;

			default:
				debuginfo_cu_parser_skipattr(&parser);
				break;
			}
		} else {
			debuginfo_cu_parser_skipattr(&parser);
		}
	} while (debuginfo_cu_parser_next(&parser) &&
	         parser.dup_child_depth >= depth);
done:
	return result;
err:
	return temp;
}

PRIVATE NONNULL((1, 2)) void
NOTHROW(FCALL dw_determine_type_size)(struct cmodule *__restrict mod,
                                      byte_t const *__restrict dip,
                                      size_t *__restrict ptype_size) {
	di_debuginfo_cu_parser_t parser;
	di_debuginfo_component_attrib_t attr;
	cmodule_parser_from_dip(mod, &parser, dip);
	DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, &parser) {
		if (attr.dica_name == DW_AT_byte_size) {
			uintptr_t temp;
			if (debuginfo_cu_parser_getconst(&parser, attr.dica_form,
			                                 &temp, _attr_reader))
				*ptype_size = (size_t)temp;
		}
	}
}

/* Return the name of a structure type, or `NULL' if unknown or `self' isn't a struct. */
PUBLIC WUNUSED NONNULL((1)) char const *
NOTHROW(FCALL ctype_struct_getname)(struct ctype const *__restrict self) {
	di_debuginfo_cu_parser_t parser;
	di_debuginfo_component_attrib_t attr;
	char const *result;
	/* Sanity check: we're actually dealing with a struct! */
	if unlikely(!CTYPE_KIND_ISSTRUCT(self->ct_kind))
		return NULL;
	cmodule_parser_from_dip(self->ct_struct.ct_info.cd_mod, &parser,
	                        self->ct_struct.ct_info.cd_dip);
	result = NULL;
	DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, &parser) {
		if (attr.dica_name == DW_AT_name) {
			if (!debuginfo_cu_parser_getstring(&parser, attr.dica_form, &result))
				result = NULL;
		}
	}
	return result;
}

/* Try to find the definition of a given struct. */
PRIVATE NONNULL((1, 2)) byte_t const *
NOTHROW(FCALL dw_enumerate_find_struct_definition)(struct cmodule *__restrict mod,
                                                   byte_t const *__restrict dip,
                                                   /*out*/ REF struct cmodule **__restrict def_module) {
	di_debuginfo_cu_parser_t parser;
	di_debuginfo_component_attrib_t attr;
	char const *name;
	struct cmodsym const *csym;
	uintptr_t ns;
	cmodule_parser_from_dip(mod, &parser, dip);
	if (parser.dup_comp.dic_tag == DW_TAG_class_type) {
		ns = CMODSYM_DIP_NS_CLASS;
	} else if (parser.dup_comp.dic_tag == DW_TAG_structure_type) {
		ns = CMODSYM_DIP_NS_STRUCT;
	} else if (parser.dup_comp.dic_tag == DW_TAG_union_type) {
		ns = CMODSYM_DIP_NS_UNION;
	} else if (parser.dup_comp.dic_tag == DW_TAG_interface_type) {
		ns = CMODSYM_DIP_NS_TYPEDEF;
	} else {
		return NULL;
	}
	name = NULL;
	DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, &parser) {
		if (attr.dica_name == DW_AT_name) {
			if (!debuginfo_cu_parser_getstring(&parser, attr.dica_form, &name))
				name = NULL;
		}
	}
	if (!name)
		return NULL;
	/* Now try to find the proper definition of the structure. */
	csym = cmodule_getsym_withhint(mod, name, strlen(name), def_module, ns);
	if (!csym)
		return NULL;
	if unlikely(!cmodsym_istype(csym)) {
		/* Shouldn't happen... */
		decref(*def_module);
		*def_module = NULL;
		return NULL;
	}
	/* Found something! */
	return cmodsym_getdip(csym, *def_module);
}


/* Enumerate/find the fields of a given struct.
 * @param: cb:     Callback to-be invoked for the field.
 * @param: cookie: Cookie-argument for `cb'
 * @return: * :    The sum of return values of `cb'
 * @return: < 0:   A propagated, negative return value of `cb'. */
PUBLIC NONNULL((1, 2)) ssize_t
NOTHROW(FCALL ctype_struct_enumfields)(struct ctype *__restrict self,
                                       ctype_struct_field_callback_t cb,
                                       void *cookie) {
	ssize_t result;
	bool struct_has_children;
	/* Sanity check: we're actually dealing with a struct! */
	if unlikely(!CTYPE_KIND_ISSTRUCT(self->ct_kind))
		return 0;
	struct_has_children = false;
again:
	result = dw_enumerate_fields(self->ct_struct.ct_info.cd_mod,
	                             self->ct_struct.ct_info.cd_dip,
	                             cb, cookie, 0, &struct_has_children);
	if (!struct_has_children && !result && !self->ct_struct.ct_sizeof) {
		/* If  the struct is anonymous in the  context of the CU that `self'
		 * got loaded from, then we'll be unable to load its fields. In this
		 * case,  we should instead  search for a struct  with the same name
		 * in a number of different places:
		 *  - All other CUs of the current module.
		 *  - All CUs of all other modules from the current address space.
		 *  - All CUs of all other modules from the other address space. */
		byte_t const *def;
		REF struct cmodule *def_module;
		def = dw_enumerate_find_struct_definition(self->ct_struct.ct_info.cd_mod,
		                                          self->ct_struct.ct_info.cd_dip,
		                                          &def_module);
		if (def && def != self->ct_struct.ct_info.cd_dip) {
			/* Remember the new definition. */
			decref(self->ct_struct.ct_info.cd_mod);
			self->ct_struct.ct_info.cd_mod = def_module;
			self->ct_struct.ct_info.cd_dip = def;
			dw_determine_type_size(def_module, def, &self->ct_struct.ct_sizeof);
			struct_has_children = true;
			goto again;
		}
	}
	return result;
}



struct ctype_struct_getfield_data {
	char const              *name;
	size_t                   namelen;
	/*out*/ struct ctyperef *pfield_type;   /* [1..1] */
	/*out*/ ptrdiff_t       *pfield_offset; /* [1..1] */
	dbx_errno_t              error;
};

PRIVATE NONNULL((2, 3, 4, 5)) ssize_t
NOTHROW(KCALL ctype_struct_getfield_cb)(void *cookie,
                                        di_debuginfo_member_t const *__restrict member,
                                        di_debuginfo_cu_parser_t const *__restrict parser,
                                        struct cmodule *__restrict mod,
                                        struct cmodunit *__restrict cu) {
	struct ctype_struct_getfield_data *arg;
	arg = (struct ctype_struct_getfield_data *)cookie;
	if (!member->m_name || unlikely(!member->m_type))
		return 0;
	if (strcmpz(member->m_name, arg->name, arg->namelen) != 0)
		return 0;
	/* Write-back results. */
	*arg->pfield_offset = member->m_offset;
	// TODO: member->m_bit_size;
	// TODO: member->m_bit_offset;
	arg->error = ctype_fromdw(mod, cu, parser, member->m_type, arg->pfield_type);
	return -1; /* Stop enumeration (we've found what we're looking for) */
}


/* Find a field of a given struct-kind C-type.
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOENT: No field with this name. */
PUBLIC WUNUSED NONNULL((1, 2, 4, 5)) dbx_errno_t
NOTHROW(FCALL ctype_struct_getfield)(struct ctype *__restrict self,
                                     char const *__restrict name, size_t namelen,
                                     /*out*/ struct ctyperef *__restrict pfield_type,
                                     /*out*/ ptrdiff_t *__restrict pfield_offset) {
	struct ctype_struct_getfield_data data;
	data.name          = name;
	data.namelen       = namelen;
	data.pfield_type   = pfield_type;
	data.pfield_offset = pfield_offset;
	data.error         = DBX_ENOENT;
	/* Enumerate fields in search for one matching `name' */
	ctype_struct_enumfields(self, &ctype_struct_getfield_cb, &data);
	return data.error;
}



/* Same as `ctype_fromdw()', but when `type_debug_info'
 * is  NULL,   fill   `*presult'   with   `ctype_void'. */
PUBLIC WUNUSED NONNULL((1, 2, 3, 5)) dbx_errno_t
NOTHROW(FCALL ctype_fromdw_opt)(struct cmodule *__restrict mod,
                                struct cmodunit const *__restrict cunit,
                                di_debuginfo_cu_parser_t const *__restrict cu_parser,
                                byte_t const *type_debug_info,
                                /*out*/ struct ctyperef *__restrict presult) {
	dbx_errno_t result;
	if (!type_debug_info) {
		bzero(presult, sizeof(*presult));
		presult->ct_typ = incref(&ctype_void);
		result          = DBX_EOK;
	} else {
		result = ctype_fromdw(mod, cunit, cu_parser, type_debug_info, presult);
	}
	return result;
}


PUBLIC WUNUSED NONNULL((1, 2, 3, 4, 5)) dbx_errno_t
NOTHROW(FCALL ctype_fromdw_subroutine)(struct cmodule *__restrict mod,
                                       struct cmodunit const *__restrict cunit,
                                       di_debuginfo_cu_parser_t *__restrict parser,
                                       /*out*/ REF struct ctype **__restrict presult,
                                       /*in*/ struct ctyperef const *__restrict return_type) {
	dbx_errno_t result;
	struct ctyperef *argv;
	size_t argc;
	uint16_t cc = CTYPE_KIND_FUNPROTO_CC_DEFAULT;
	argv = NULL;
	argc = 0;
	if (debuginfo_cu_parser_nextchild(parser)) {
		/* Load function argument types. */
		size_t depth = parser->dup_child_depth;
		do {
			if (parser->dup_child_depth == depth &&
			    (parser->dup_comp.dic_tag == DW_TAG_formal_parameter ||
			     parser->dup_comp.dic_tag == DW_TAG_unspecified_parameters)) {
				if (parser->dup_comp.dic_tag == DW_TAG_unspecified_parameters) {
					cc |= CTYPE_KIND_FUNPROTO_VARARGS;
				} else {
					byte_t const *parameter_type_pointer = NULL;
					di_debuginfo_component_attrib_t attr;
					if ((argc + 1) > dbx_malloc_usable_size(argv) / sizeof(struct ctyperef)) {
						struct ctyperef *new_argv;
						new_argv = (struct ctyperef *)dbx_realloc(argv, (argc + 1) * sizeof(struct ctyperef));
						if unlikely(!new_argv) {
							result = DBX_ENOMEM;
							goto done_fuction_argv;
						}
						argv = new_argv;
					}
					DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, parser) {
						if (attr.dica_name == DW_AT_type)
							debuginfo_cu_parser_getref(parser, attr.dica_form, &parameter_type_pointer);
					}
					if (!parameter_type_pointer) {
						ctypeinfo_init(&argv[argc].ct_info);
						argv[argc].ct_flags = CTYPEREF_FLAG_NORMAL;
						argv[argc].ct_typ   = incref(&ctype_int);
					} else {
						result = ctype_fromdw(mod, cunit, parser, parameter_type_pointer, &argv[argc]);
						if unlikely(result != DBX_EOK)
							goto done_fuction_argv;
					}
					++argc;
				}
			} else {
				debuginfo_cu_parser_skipattr(parser);
			}
		} while (debuginfo_cu_parser_next(parser) &&
		         parser->dup_child_depth >= depth);
	}
	/* Form the actual function type. */
	result   = DBX_EOK;
	*presult = ctype_function(return_type, argc, argv, cc);
	if unlikely(!*presult)
		result = DBX_ENOMEM;
done_fuction_argv:
	while (argc) {
		--argc;
		ctyperef_fini(&argv[argc]);
	}
	dbx_free(argv);
/*done:*/
	return result;
}


/* Load a C-type from a given `type_debug_info' which should be loaded
 * with the help of an internal copy made from `cu_parser'. The  given
 * `type_debug_info' is a pointer like `di_debuginfo_member_t::m_type'
 * @param: ptyperef_flags: When non-NULL, store type-reference flags here (`CTYPEREF_FLAG_*')
 * @return: DBX_EOK:     A reference to the associated type.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: Debug information was corrupted. */
PUBLIC WUNUSED NONNULL((1, 2, 3, 4, 5)) dbx_errno_t
NOTHROW(FCALL ctype_fromdw)(struct cmodule *__restrict mod,
                            struct cmodunit const *__restrict cunit,
                            di_debuginfo_cu_parser_t const *__restrict cu_parser,
                            byte_t const *__restrict type_debug_info,
                            /*out*/ struct ctyperef *__restrict presult) {
	dbx_errno_t result = DBX_EOK;
	di_debuginfo_cu_parser_t parser;
	di_debuginfo_type_t typinfo;
	bzero(presult, sizeof(*presult));
again:
	if unlikely(!type_debug_info)
		goto err_corrupt;
	memcpy(&parser, cu_parser, sizeof(di_debuginfo_cu_parser_t));
	parser.dsp_cu_info_pos = (byte_t *)type_debug_info;
	if (!debuginfo_cu_parser_next(&parser))
		goto err_corrupt;
	if (!debuginfo_cu_parser_loadattr_type(&parser, &typinfo))
		goto err_corrupt;
	if (!presult->ct_info.ci_name) {
		presult->ct_info.ci_name = typinfo.t_name;
		if (!presult->ct_info.ci_name)
			presult->ct_info.ci_name = typinfo.t_rawname;
		if (presult->ct_info.ci_name)
			presult->ct_info.ci_nameref = incref(mod);
	}
	switch (parser.dup_comp.dic_tag) {

	case DW_TAG_unspecified_type:
		presult->ct_typ = incref(&ctype_int);
		break;

	case DW_TAG_base_type:
		switch (typinfo.t_encoding) {

		case DW_ATE_void:
			presult->ct_typ = incref(&ctype_void);
			break;

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
				bzero(&ctr, sizeof(ctr));
				ctr.ct_typ = &ctype_void;
				presult->ct_typ = ctype_ptr(&ctr, typinfo.t_sizeof);
			}
			break;

		case DW_ATE_boolean:
			if (!typinfo.t_sizeof || typinfo.t_sizeof == sizeof(bool)) {
				presult->ct_typ = incref(&ctype_bool);
				/* Keep a bit  of consistency, and  discard boolean  types
				 * that have been  named as `_Bool'.  This happens when  a
				 * program written in  C uses <stdbool.h>,  and we  filter
				 * out this kind of thing, so that `cprinter.c' will print
				 * all conforming boolean types as `bool' */
				if (presult->ct_info.ci_name &&
				    strcmp(presult->ct_info.ci_name, "_Bool") == 0) {
					presult->ct_info.ci_name = NULL;
					if (presult->ct_info.ci_nameref) {
						decref(presult->ct_info.ci_nameref);
						presult->ct_info.ci_nameref = NULL;
					}
				}
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
#ifdef CTYPE_KIND_IEEE854_LONG_DOUBLE
			if (typinfo.t_sizeof == SIZEOF_CTYPE_IEEE854_LONG_DOUBLE) {
				presult->ct_typ = incref(&ctype_ieee854_long_double);
			} else
#endif /* CTYPE_KIND_IEEE854_LONG_DOUBLE */
			if (typinfo.t_sizeof == SIZEOF_CTYPE_IEEE754_DOUBLE) {
				presult->ct_typ = incref(&ctype_ieee754_double);
			} else if (typinfo.t_sizeof == SIZEOF_CTYPE_IEEE754_FLOAT) {
				presult->ct_typ = incref(&ctype_ieee754_float);
			} else {
				goto err_corrupt;
			}
			break;

		case DW_ATE_signed:
		case DW_ATE_unsigned:
			if (!typinfo.t_name)
				typinfo.t_name = typinfo.t_rawname;
			if (typinfo.t_name) {
				if (strcmp(typinfo.t_name, "char") == 0) {
					if (!typinfo.t_sizeof)
						typinfo.t_sizeof = sizeof(char);
					goto do_character;
				}
				if (strcmp(typinfo.t_name, "wchar_t") == 0) {
					if (!typinfo.t_sizeof)
						typinfo.t_sizeof = sizeof(wchar_t);
					goto do_character;
				}
				if (strcmp(typinfo.t_name, "char16_t") == 0) {
					if (!typinfo.t_sizeof)
						typinfo.t_sizeof = sizeof(char16_t);
					goto do_character;
				}
				if (strcmp(typinfo.t_name, "char32_t") == 0) {
					if (!typinfo.t_sizeof)
						typinfo.t_sizeof = sizeof(char32_t);
					goto do_character;
				}
			}
			if (typinfo.t_encoding == DW_ATE_signed) {
do_signed:
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
			} else {
do_unsigned:
				if (!typinfo.t_sizeof)
					typinfo.t_sizeof = sizeof(int);
				if (typinfo.t_sizeof == 1) {
					presult->ct_typ = incref(&ctype_u8);
				} else if (typinfo.t_sizeof == 2) {
					presult->ct_typ = incref(&ctype_u16);
				} else if (typinfo.t_sizeof == 4) {
					presult->ct_typ = incref(&ctype_u32);
				} else if (typinfo.t_sizeof == 8) {
					presult->ct_typ = incref(&ctype_u64);
				} else {
					goto err_corrupt;
				}
			}
			break;

		case DW_ATE_unsigned_char:
		case DW_ATE_signed_char:
		case DW_ATE_UTF:
		case DW_ATE_UCS:
		case DW_ATE_ASCII:
			if (!typinfo.t_sizeof)
				typinfo.t_sizeof = sizeof(char);
			if (!typinfo.t_name)
				typinfo.t_name = typinfo.t_rawname;
			/* The only way to differentiate between `signed char' and `char'
			 * in debug information (which we need to do, since we only allow
			 * `char *' to be printed  as strings, but leave  `signed char *'
			 * alone), is to look at the name field of the type:
			 * ```
			 * <1><xxx>: Abbrev Number: xxx (DW_TAG_base_type)
			 *    <xxx>   DW_AT_byte_size   : 1
			 *    <xxx>   DW_AT_encoding    : 6	(signed char)
			 *    <xxx>   DW_AT_name        : (indirect string, offset: xxx): char
			 * <1><xxx>: Abbrev Number: xxx (DW_TAG_base_type)
			 *    <xxx>   DW_AT_byte_size   : 1
			 *    <xxx>   DW_AT_encoding    : 6	(signed char)
			 *    <xxx>   DW_AT_name        : (indirect string, offset: xxx): signed char
			 * ```
			 */
			if (typinfo.t_encoding == DW_ATE_UTF ||
			    typinfo.t_encoding == DW_ATE_UCS ||
			    typinfo.t_encoding == DW_ATE_ASCII ||
			    (typinfo.t_name && strcmp(typinfo.t_name, "char") == 0)) {
do_character:
				if (typinfo.t_sizeof == sizeof(char)) {
					presult->ct_typ = incref(&ctype_char);
					break;
				} else if (typinfo.t_sizeof == sizeof(char16_t)) {
					presult->ct_typ = incref(&ctype_char16_t);
					break;
				} else if (typinfo.t_sizeof == sizeof(char32_t)) {
					presult->ct_typ = incref(&ctype_char32_t);
					break;
				}
			}
			if (typinfo.t_encoding == DW_ATE_signed_char ||
			    typinfo.t_encoding == DW_ATE_signed)
				goto do_signed;
			goto do_unsigned;

		default:
			goto err_corrupt;
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
							if (debuginfo_cu_parser_getconst(&parser, attr.dica_form,
							                                 &elem_count, _attr_reader))
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
		result = ctype_fromdw(mod, cunit, &parser, typinfo.t_type, &elem_type);
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
		result_type->ct_refcnt      = 1;
		result_type->ct_kind        = CTYPE_KIND_CLASSOF(CTYPE_KIND_ENUM) | typinfo.t_sizeof;
		result_type->ct_children    = NULL;
		result_type->ct_enum.cd_mod = incref(mod);
		result_type->ct_enum.cd_dip = type_debug_info;
		presult->ct_typ             = result_type; /* Inherit reference */
	}	break;

	case DW_TAG_pointer_type:
	case DW_TAG_reference_type:
	case DW_TAG_rvalue_reference_type: {
		struct ctyperef pointed_to_type;
		/* Parse the inner type. */
		result = ctype_fromdw_opt(mod, cunit, &parser, typinfo.t_type, &pointed_to_type);
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
		/* Load the function return type. */
		result = ctype_fromdw_opt(mod, cunit, &parser, typinfo.t_type, &return_type);
		if unlikely(result != DBX_EOK)
			goto done;
		result = ctype_fromdw_subroutine(mod, cunit, &parser,
		                                 &presult->ct_typ,
		                                 &return_type);
		ctyperef_fini(&return_type);
		if unlikely(result != DBX_EOK)
			goto done;
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
		struct_type->ct_children              = NULL;
		struct_type->ct_struct.ct_info.cd_mod = incref(mod);
		struct_type->ct_struct.ct_info.cd_dip = type_debug_info;
		struct_type->ct_struct.ct_sizeof      = typinfo.t_sizeof;
		presult->ct_typ                       = struct_type; /* Inherit reference */
	}	break;

	case DW_TAG_typedef:
		type_debug_info = typinfo.t_type;
again_opt:
		/* Optional, since `typedef void MY_VOID;' is something you're allowed to do! */
		if (!type_debug_info) {
			presult->ct_typ = incref(&ctype_void);
			break;
		}
		goto again;

	case DW_TAG_const_type:
		presult->ct_flags |= CTYPEREF_FLAG_CONST;
		type_debug_info = typinfo.t_type;
		goto again_opt; /* Optional, since `void const' is allowed (and often used in e.g. `void const *') */

	case DW_TAG_volatile_type:
		presult->ct_flags |= CTYPEREF_FLAG_VOLATILE;
		type_debug_info = typinfo.t_type;
		goto again_opt; /* Optional, since `void volatile' is allowed (and often used in e.g. `void volatile*') */

	case DW_TAG_restrict_type:
		presult->ct_flags |= CTYPEREF_FLAG_RESTRICT;
		type_debug_info = typinfo.t_type;
		goto again; /* `restrict' must reference a pointer type, so the type field can't be optional,
		             * since its absene  would mean  `void restrict', which doesn't  make any  sense. */

	case DW_TAG_atomic_type:
		presult->ct_flags |= CTYPEREF_FLAG_ATOMIC;
		type_debug_info = typinfo.t_type;
		goto again; /* Just like with `restrict', `void atomic' doesn't make any sense. */

	default:
		goto err_corrupt;
	}
done:
	if (result != DBX_EOK) {
		presult->ct_info.ci_name = NULL;
		if (presult->ct_info.ci_nameref) {
			decref(presult->ct_info.ci_nameref);
			presult->ct_info.ci_nameref = NULL;
		}
	}
	return result;
err_corrupt:
	result = DBX_EINTERN;
	goto done;
err_nomem:
	result = DBX_ENOMEM;
	goto done;
}

/* Lookup the enum-name for a given `value'
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOENT: `self' isn't an enum type.
 * @return: DBX_ENOENT: No name associated with `value' */
PUBLIC WUNUSED NONNULL((1, 2)) dbx_errno_t
NOTHROW(FCALL ctype_enumname)(struct ctype const *__restrict self,
                              /*out*/ struct ctypeenumname *__restrict result,
                              intmax_t value) {
	/* TODO */
	COMPILER_IMPURE();
	(void)self;
	(void)result;
	(void)value;
	return DBX_ENOENT;
}




DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_MODDBX_CTYPE_C */
