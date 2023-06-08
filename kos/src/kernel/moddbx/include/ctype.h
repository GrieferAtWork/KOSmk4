/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODDBX_INCLUDE_CTYPE_H
#define GUARD_MODDBX_INCLUDE_CTYPE_H 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER

#include <debugger/rt.h>
#include <kernel/types.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <compat/config.h>
#include <kos/exec/module.h>
#include <kos/refcnt-nonatomic.h>

#include <ieee754.h>
#include <stdint.h> /* intmax_t */

#include <libcpustate/register.h> /* cpu_regno_t */
#include <libdebuginfo/debug_info.h>

#ifdef __x86_64__
#include <debugger/arch/rt.h>
#endif /* __x86_64__ */

/**/
#include "cmodule.h"
#include "error.h"

DECL_BEGIN

#define CTYPE_KIND_VOID                   0x0001
#define CTYPE_KIND_BOOL8                  0x1001
#define CTYPE_KIND_BOOL16                 0x1002
#define CTYPE_KIND_BOOL32                 0x1004
#define CTYPE_KIND_BOOL64                 0x1008
#define CTYPE_KIND_Sn(sizeof)            (0x2000 | (sizeof))
#define CTYPE_KIND_S8                     0x2001
#define CTYPE_KIND_S16                    0x2002
#define CTYPE_KIND_S32                    0x2004
#define CTYPE_KIND_S64                    0x2008
#define CTYPE_KIND_Un(sizeof)            (0x2100 | (sizeof))
#define CTYPE_KIND_U8                     0x2101
#define CTYPE_KIND_U16                    0x2102
#define CTYPE_KIND_U32                    0x2104
#define CTYPE_KIND_U64                    0x2108
#define CTYPE_KIND_ENUM8                  0x2201
#define CTYPE_KIND_ENUM16                 0x2202
#define CTYPE_KIND_ENUM32                 0x2204
#define CTYPE_KIND_ENUM64                 0x2208
#define CTYPE_KIND_IEEE754_FLOAT          0x3004
#define CTYPE_KIND_IEEE754_DOUBLE         0x3008
#define CTYPE_KIND_IEEE854_LONG_DOUBLE_12 0x300c
#define CTYPE_KIND_IEEE854_LONG_DOUBLE_16 0x3010
#define CTYPE_KIND_STRUCT                 0x4000
#define CTYPE_KIND_UNION                  0x4100
#define CTYPE_KIND_PTR32                  0x8004
#define CTYPE_KIND_PTR64                  0x8008
#define CTYPE_KIND_ARRAY                  0x9000
#define CTYPE_KIND_FUNCTION               0xa000
#define    CTYPE_KIND_FUNPROTO_CCMASK     0x0700 /* == CTYPE_KIND_FLAGMASK */
#define    CTYPE_KIND_FUNPROTO_VARARGS    0x0800 /* FLAG: var-args function */
#if defined(__x86_64__) || defined(__i386__)
#define    CTYPE_KIND_FUNPROTO_CC_CDECL    0x0000
#define    CTYPE_KIND_FUNPROTO_CC_FASTCALL 0x0100
#define    CTYPE_KIND_FUNPROTO_CC_STDCALL  0x0200
#ifdef __x86_64__
#define    CTYPE_KIND_FUNPROTO_CC_SYSVABI  0x0400
#define    CTYPE_KIND_FUNPROTO_CC_MSABI    0x0500
#define    CTYPE_KIND_FUNPROTO_CC_DEFAULT                                                  \
	(__KOS64_IS_CS32BIT(dbg_rt_getregbyidp(DBG_RT_REGLEVEL_VIEW, X86_REGISTER_SEGMENT_CS)) \
	 ? CTYPE_KIND_FUNPROTO_CC_CDECL                                                        \
	 : CTYPE_KIND_FUNPROTO_CC_SYSVABI)
#else /* __x86_64__ */
#define    CTYPE_KIND_FUNPROTO_CC_DEFAULT  CTYPE_KIND_FUNPROTO_CC_CDECL
#endif /* !__x86_64__ */
#else /* __x86_64__ || __i386__ */
#define    CTYPE_KIND_FUNPROTO_CC_DEFAULT 0x0000
#endif /* !__x86_64__ && !__i386__ */

#define CTYPE_KIND_SIZEMASK               0x00ff
#define CTYPE_KIND_FLAGMASK               0x0f00
#define CTYPE_KIND_CLASSMASK              0xf000
#define CTYPE_KIND_CLASSOF(kind)          ((kind) & CTYPE_KIND_CLASSMASK)

#define CTYPE_KIND_ISVOID(kind)      (((kind) & 0xf000) == 0x0000) /* Check for void type */
#define CTYPE_KIND_ISBOOL(kind)      (((kind) & 0xf000) == 0x1000) /* Check for boolean type */
#define CTYPE_KIND_ISINT(kind)       (((kind) & 0xf000) == 0x2000) /* Check for integer/enum type */
#define CTYPE_KIND_ISENUM(kind)      (((kind) & 0xf200) == 0x2200) /* Check for enum type */
#define    CTYPE_KIND_INT_ISUNSIGNED(kind) ((kind) & 0x0100)       /* For integer/enum: Is the type unsigned? */
#define CTYPE_KIND_ISFLOAT(kind)     (((kind) & 0xf000) == 0x3000) /* Check for floating-point types. */
#define CTYPE_KIND_ISSTRUCT(kind)    (((kind) & 0xf000) == 0x4000) /* Check for struct/enum */
#define    CTYPE_KIND_STRUCT_ISUNION(kind) ((kind) & 0x0100)       /* For struct types: Is the type a union */
#define CTYPE_KIND_ISPOINTER(kind)   (((kind) & 0xf000) == 0x8000) /* Check for pointer type */
#define CTYPE_KIND_ISARRAY(kind)     (((kind) & 0xf000) == 0x9000) /* Check for array types */
#define CTYPE_KIND_SIZEOF(kind)      ((kind) & 0xff)               /* Basic type size (or 0 for array/struct/enum) */
#define CTYPE_KIND_HASSIBLING(kind)  (((kind) & 0xf000) >= 0x8000) /* Check if the type has a sibling. */
#define CTYPE_KIND_ISFUNCTION(kind)  (((kind) & 0xf000) == 0xa000) /* Check for function-pointer type */

#define CTYPE_KIND_ISINT_OR_BOOL(kind) \
	(CTYPE_KIND_ISINT(kind) || CTYPE_KIND_ISBOOL(kind))
#define CTYPE_KIND_ISINT_OR_BOOL_OR_POINTER(kind) \
	(CTYPE_KIND_ISINT(kind) || CTYPE_KIND_ISBOOL(kind) || CTYPE_KIND_ISPOINTER(kind))
#define CTYPE_KIND_ISINT_OR_BOOL_OR_FLOAT(kind) \
	(CTYPE_KIND_ISINT(kind) || CTYPE_KIND_ISBOOL(kind) || CTYPE_KIND_ISFLOAT(kind))
#define CTYPE_KIND_ISARRAY_OR_POINTER(kind) \
	(CTYPE_KIND_ISARRAY(kind) || CTYPE_KIND_ISPOINTER(kind))
#define CTYPE_KIND_ISARRAY_OR_STRUCT(kind) \
	(CTYPE_KIND_ISARRAY(kind) || CTYPE_KIND_ISSTRUCT(kind))

#define CTYPE_KIND_BOOL CTYPE_KIND_BOOL8
#define CTYPE_KIND_ENUM ((CTYPE_KIND_ENUM8 & ~CTYPE_KIND_SIZEMASK) | __SIZEOF_INT__)
#define CTYPE_KIND_PTR  ((CTYPE_KIND_PTR32 & ~CTYPE_KIND_SIZEMASK) | __SIZEOF_POINTER__)
#ifdef __ARCH_HAVE_COMPAT
#define CTYPE_KIND_COMPAT_PTR ((CTYPE_KIND_PTR32 & ~CTYPE_KIND_SIZEMASK) | __ARCH_COMPAT_SIZEOF_POINTER)
#endif /* __ARCH_HAVE_COMPAT */

#define CTYPEREF_FLAG_NORMAL   0x0000 /* Normal flags. */
#define CTYPEREF_FLAG_CONST    0x0001 /* `const' */
#define CTYPEREF_FLAG_VOLATILE 0x0002 /* `volatile' */
#define CTYPEREF_FLAG_ATOMIC   0x0004 /* `_Atomic' */
#define CTYPEREF_FLAG_RESTRICT 0x0008 /* `__restrict' */
#if defined(__x86_64__) || defined(__i386__)
#define CTYPEREF_FLAG_SEGMASK  0xc000
#define CTYPEREF_FLAG_SEG_FS   0x4000
#define CTYPEREF_FLAG_SEG_GS   0x8000
#endif /* __x86_64__ || __i386__ */

struct ctype;
struct ctypeinfo {
	char const         *ci_name;    /* [0..1] Name of this type (or NULL if anonymous). */
	REF struct cmodule *ci_nameref; /* [0..1] Module reference for keeping `ct_name' alive. */
};
#define ctypeinfo_equal(a, b) \
	((a)->ci_name == (b)->ci_name)
#define ctypeinfo_init(self)         \
	((self)->ci_name    = __NULLPTR, \
	 (self)->ci_nameref = __NULLPTR)
#define ctypeinfo_fini(self) \
	(xdecref((self)->ci_nameref))
#define ctypeinfo_initcopy(self, src)              \
	(void)((self)->ci_nameref = (src)->ci_nameref, \
	       (self)->ci_name    = (src)->ci_name,    \
	       xincref((self)->ci_nameref))

struct ctyperef {
	REF struct ctype *ct_typ;   /* [1..1] Referenced type. */
	struct ctypeinfo  ct_info;  /* Name information. */
	uintptr_t         ct_flags; /* Type flags. (set of `CTYPEREF_FLAG_*') */
};

#define ctyperef_fini(self) \
	(decref((self)->ct_typ), ctypeinfo_fini(&(self)->ct_info))
#define ctyperef_initcopy(self, src)                              \
	(void)((self)->ct_typ = (src)->ct_typ,                        \
	       incref((self)->ct_typ),                                \
	       ctypeinfo_initcopy(&(self)->ct_info, &(src)->ct_info), \
	       (self)->ct_flags = (src)->ct_flags)
#define ctyperef_equal(a, b)           \
	((a)->ct_typ == (b)->ct_typ &&     \
	 (a)->ct_flags == (b)->ct_flags && \
	 ctypeinfo_equal(&(a)->ct_info, &(b)->ct_info))
#define ctyperef_equal_assume_same_type(a, b) \
	((a)->ct_flags == (b)->ct_flags &&        \
	 ctypeinfo_equal(&(a)->ct_info, &(b)->ct_info))


struct ctype {
	uintptr_half_t ct_refcnt;   /* Reference counter. */
	uintptr_half_t ct_kind;     /* The kind of type (one of `CTYPE_KIND_*'). */
	struct ctype  *ct_children; /* [0..1] Derived types (all of these have `CTYPE_KIND_HASSIBLING()') */
	union {
		struct cmoduledip ct_enum; /* [valid_if(CTYPE_KIND_ISENUM)] Enum information. Points just past
		                            * the  `DW_TAG_enumeration_type' tag of the surrounding enumerator
		                            * (scan this region for `DW_TAG_enumerator' child elements). */

		struct {
			struct cmoduledip ct_info;   /* Struct information. Points just past the `DW_TAG_structure_type'
			                              * (or similar) tag of the surrounding structure (scan this  region
			                              * for `DW_TAG_member' child elements). */
			size_t            ct_sizeof; /* Sizeof() this struct. */
		} ct_struct; /* [valid_if(CTYPE_KIND_ISSTRUCT)] */

		struct {
			struct ctype     *ct_sibling; /* [0..1][valid_if(CTYPE_KIND_HASSIBLING)] Sibling type */
			REF struct ctype *ct_parent;  /* [0..1][valid_if(CTYPE_KIND_HASSIBLING)] Parent type */
		};

		struct {
			struct ctype   *_cp_sib; /* [0..1] Sibling type */
			struct ctyperef cp_base; /* Pointed-to type (and const/volatile flags) */
		} ct_pointer;                /* [valid_if(CTYPE_KIND_ISPOINTER)] */

		struct {
			struct ctype     *_ca_sib;     /* [0..1] Sibling type */
			REF struct ctype *ca_elem;     /* Element type. */
			struct ctypeinfo  ca_eleminfo; /* Element information. */
			size_t            ca_count;    /* Element count. (or `0' for flexible arrays) */
		} ct_array;                        /* [valid_if(CTYPE_KIND_ARRAY)] */

		struct {
			struct ctype                            *_cf_sib;  /* [0..1] Sibling type */
			struct ctyperef                          cf_base;  /* Return-type */
			size_t                                   cf_argc;  /* Argument count. */
			COMPILER_FLEXIBLE_ARRAY(struct ctyperef, cf_argv); /* [1..1][cfp_argc] Argument vector. */
		} ct_function; /* [valid_if(CTYPE_KIND_ISFUNCTION)] */
	};
};

#define ctype_addchild(self, child)                   \
	(void)((child)->ct_sibling = (self)->ct_children, \
	       (self)->ct_children = (child))


/* Destroy the given C-type. */
FUNDEF NONNULL((1)) void
NOTHROW(FCALL ctype_destroy)(struct ctype *__restrict self);
__DEFINE_NONATOMIC_REFCNT_FUNCTIONS(struct ctype, ct_refcnt, ctype_destroy)


/* Return the pointer-version of the given C-type
 * @param: flags: Type-reference-flags (set of `CTYPEREF_FLAG_*') */
FUNDEF NONNULL((1)) REF struct ctype *
NOTHROW(FCALL ctype_ptr)(struct ctyperef const *__restrict self,
                         size_t sizeof_pointer);

/* Return  the   array-version  of   the  given   C-type
 * NOTE: The returned type must inherit `self->ct_flags'
 * @param: flags: Type-reference-flags (set of `CTYPEREF_FLAG_*') */
FUNDEF NONNULL((1)) REF struct ctype *
NOTHROW(FCALL ctype_array)(struct ctyperef const *__restrict self,
                           size_t elem_count);

/* Return a function-type C-type. */
FUNDEF NONNULL((1)) REF struct ctype *
NOTHROW(FCALL ctype_function)(struct ctyperef const *return_type, size_t argc,
                              struct ctyperef const *argv, uint16_t cc);

/* Return the actual size of the given C-type. (as per `sizeof()') */
FUNDEF ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW(FCALL ctype_sizeof)(struct ctype const *__restrict self);

/* Check if 2 given C-types are equal. */
FUNDEF ATTR_PURE NONNULL((1, 2)) __BOOL
NOTHROW(FCALL ctype_equal)(struct ctype const *a,
                           struct ctype const *b);

/* Return the common type which  can be used to  represent both `a' and  `b'.
 * This common type is the promotion of `a' and `b' if those types are equal,
 * and  otherwise is the larger integer type of the two. If neither types are
 * integers, then a common type doesn't exist and `NULL' is returned. */
FUNDEF WUNUSED NONNULL((1, 2)) REF struct ctype *
NOTHROW(FCALL ctype_common)(struct ctype *a,
                            struct ctype *b);

/* Return the appropriate C-type for a given arch-specific register `regno'
 * If no such type exists, return `NULL' instead.
 * @param: buflen: The required buffer size to hold `regno' */
FUNDEF WUNUSED REF struct ctype *
NOTHROW(FCALL ctype_for_register)(cpu_regno_t regno, size_t buflen);

struct ctypeenumname {
	char const           *en_name;    /* [1..1] Name of the enum. */
	REF struct cmodule *en_nameref; /* [1..1] Module reference for keeping `en_name' alive. */
};
#define ctypeenumname_fini(self) decref((self)->en_nameref)


/* Lookup the enum-name for a given `value'
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOENT: `self' isn't an enum type.
 * @return: DBX_ENOENT: No name associated with `value' */
FUNDEF WUNUSED NONNULL((1, 2)) dbx_errno_t
NOTHROW(FCALL ctype_enumname)(struct ctype const *__restrict self,
                              /*out*/ struct ctypeenumname *__restrict result,
                              intmax_t value);




#define SIZEOF_CTYPE_IEEE754_FLOAT  4
#define SIZEOF_CTYPE_IEEE754_DOUBLE 8
#ifdef __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__
#define SIZEOF_CTYPE_IEEE854_LONG_DOUBLE __SIZEOF_LONG_DOUBLE__
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#define SIZEOF_CTYPE_IEEE854_LONG_DOUBLE __SIZEOF_DOUBLE__
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
#define SIZEOF_CTYPE_IEEE854_LONG_DOUBLE __SIZEOF_FLOAT__
#endif /* ... */

#ifdef SIZEOF_CTYPE_IEEE854_LONG_DOUBLE
#define CTYPE_KIND_IEEE854_LONG_DOUBLE \
	((CTYPE_KIND_IEEE854_LONG_DOUBLE_12 & ~CTYPE_KIND_SIZEMASK) | SIZEOF_CTYPE_IEEE854_LONG_DOUBLE)
#endif /* SIZEOF_CTYPE_IEEE854_LONG_DOUBLE */



/* Builtin types. */
DATDEF struct ctype ctype_bool;
DATDEF struct ctype ctype_ieee754_float;
DATDEF struct ctype ctype_ieee754_double;
#ifdef CTYPE_KIND_IEEE854_LONG_DOUBLE
DATDEF struct ctype ctype_ieee854_long_double;
#endif /* CTYPE_KIND_IEEE854_LONG_DOUBLE */
DATDEF struct ctype ctype_void;
DATDEF struct ctype ctype_void_ptr;
DATDEF struct ctype ctype_void_const_ptr;
DATDEF struct ctype ctype_char;
DATDEF struct ctype ctype_char_ptr;
DATDEF struct ctype ctype_char_const_ptr;
DATDEF struct ctype ctype_signed_char;
DATDEF struct ctype ctype_signed_char_ptr;
DATDEF struct ctype ctype_signed_char_const_ptr;
DATDEF struct ctype ctype_unsigned_char;
DATDEF struct ctype ctype_unsigned_char_ptr;
DATDEF struct ctype ctype_unsigned_char_const_ptr;
DATDEF struct ctype ctype_short;
DATDEF struct ctype ctype_short_ptr;
DATDEF struct ctype ctype_short_const_ptr;
DATDEF struct ctype ctype_unsigned_short;
DATDEF struct ctype ctype_unsigned_short_ptr;
DATDEF struct ctype ctype_unsigned_short_const_ptr;
DATDEF struct ctype ctype_int;
DATDEF struct ctype ctype_int_ptr;
DATDEF struct ctype ctype_int_const_ptr;
DATDEF struct ctype ctype_unsigned_int;
DATDEF struct ctype ctype_unsigned_int_ptr;
DATDEF struct ctype ctype_unsigned_int_const_ptr;
DATDEF struct ctype ctype_long;
DATDEF struct ctype ctype_long_ptr;
DATDEF struct ctype ctype_long_const_ptr;
DATDEF struct ctype ctype_unsigned_long;
DATDEF struct ctype ctype_unsigned_long_ptr;
DATDEF struct ctype ctype_unsigned_long_const_ptr;
DATDEF struct ctype ctype_long_long;
DATDEF struct ctype ctype_long_long_ptr;
DATDEF struct ctype ctype_long_long_const_ptr;
DATDEF struct ctype ctype_unsigned_long_long;
DATDEF struct ctype ctype_unsigned_long_long_ptr;
DATDEF struct ctype ctype_unsigned_long_long_const_ptr;
DATDEF struct ctype ctype_char16_t;
DATDEF struct ctype ctype_char16_t_ptr;
DATDEF struct ctype ctype_char16_t_const_ptr;
DATDEF struct ctype ctype_char32_t;
DATDEF struct ctype ctype_char32_t_ptr;
DATDEF struct ctype ctype_char32_t_const_ptr;
#define ctype_char8_t           ctype_char
#define ctype_char8_t_ptr       ctype_char_ptr
#define ctype_char8_t_const_ptr ctype_char_const_ptr


#ifdef __ARCH_HAVE_COMPAT
DATDEF struct ctype ctype_void_compat_ptr;
DATDEF struct ctype ctype_void_const_compat_ptr;
DATDEF struct ctype ctype_char_compat_ptr;
DATDEF struct ctype ctype_char_const_compat_ptr;
DATDEF struct ctype ctype_signed_char_compat_ptr;
DATDEF struct ctype ctype_signed_char_const_compat_ptr;
DATDEF struct ctype ctype_unsigned_char_compat_ptr;
DATDEF struct ctype ctype_unsigned_char_const_compat_ptr;
DATDEF struct ctype ctype_short_compat_ptr;
DATDEF struct ctype ctype_short_const_compat_ptr;
DATDEF struct ctype ctype_unsigned_short_compat_ptr;
DATDEF struct ctype ctype_unsigned_short_const_compat_ptr;
DATDEF struct ctype ctype_int_compat_ptr;
DATDEF struct ctype ctype_int_const_compat_ptr;
DATDEF struct ctype ctype_unsigned_int_compat_ptr;
DATDEF struct ctype ctype_unsigned_int_const_compat_ptr;
DATDEF struct ctype ctype_long_compat_ptr;
DATDEF struct ctype ctype_long_const_compat_ptr;
DATDEF struct ctype ctype_unsigned_long_compat_ptr;
DATDEF struct ctype ctype_unsigned_long_const_compat_ptr;
DATDEF struct ctype ctype_long_long_compat_ptr;
DATDEF struct ctype ctype_long_long_const_compat_ptr;
DATDEF struct ctype ctype_unsigned_long_long_compat_ptr;
DATDEF struct ctype ctype_unsigned_long_long_const_compat_ptr;
DATDEF struct ctype ctype_char16_t_compat_ptr;
DATDEF struct ctype ctype_char16_t_const_compat_ptr;
DATDEF struct ctype ctype_char32_t_compat_ptr;
DATDEF struct ctype ctype_char32_t_const_compat_ptr;
#endif /* __ARCH_HAVE_COMPAT */


#if __SIZEOF_CHAR__ == 1
#ifndef ctype_s8
#define ctype_s8  ctype_signed_char
#define ctype_u8  ctype_unsigned_char
#endif /* !ctype_s8 */
#elif __SIZEOF_CHAR__ == 2
#ifndef ctype_s16
#define ctype_s16 ctype_signed_char
#define ctype_u16 ctype_unsigned_char
#endif /* !ctype_s16 */
#elif __SIZEOF_CHAR__ == 4
#ifndef ctype_s32
#define ctype_s32 ctype_signed_char
#define ctype_u32 ctype_unsigned_char
#endif /* !ctype_s32 */
#elif __SIZEOF_CHAR__ == 8
#ifndef ctype_s64
#define ctype_s64 ctype_signed_char
#define ctype_u64 ctype_unsigned_char
#endif /* !ctype_s64 */
#endif /* __SIZEOF_SHORT__ == ... */

#if __SIZEOF_SHORT__ == 1
#ifndef ctype_s8
#define ctype_s8  ctype_short
#define ctype_u8  ctype_unsigned_short
#endif /* !ctype_s8 */
#elif __SIZEOF_SHORT__ == 2
#ifndef ctype_s16
#define ctype_s16 ctype_short
#define ctype_u16 ctype_unsigned_short
#endif /* !ctype_s16 */
#elif __SIZEOF_SHORT__ == 4
#ifndef ctype_s32
#define ctype_s32 ctype_short
#define ctype_u32 ctype_unsigned_short
#endif /* !ctype_s32 */
#elif __SIZEOF_SHORT__ == 8
#ifndef ctype_s64
#define ctype_s64 ctype_short
#define ctype_u64 ctype_unsigned_short
#endif /* !ctype_s64 */
#endif /* __SIZEOF_SHORT__ == ... */

#if __SIZEOF_INT__ == 1
#ifndef ctype_s8
#define ctype_s8  ctype_int
#define ctype_u8  ctype_unsigned_int
#endif /* !ctype_s8 */
#elif __SIZEOF_INT__ == 2
#ifndef ctype_s16
#define ctype_s16 ctype_int
#define ctype_u16 ctype_unsigned_int
#endif /* !ctype_s16 */
#elif __SIZEOF_INT__ == 4
#ifndef ctype_s32
#define ctype_s32 ctype_int
#define ctype_u32 ctype_unsigned_int
#endif /* !ctype_s32 */
#elif __SIZEOF_INT__ == 8
#ifndef ctype_s64
#define ctype_s64 ctype_int
#define ctype_u64 ctype_unsigned_int
#endif /* !ctype_s64 */
#endif /* __SIZEOF_INT__ == ... */

#if __SIZEOF_LONG__ == 1
#ifndef ctype_s8
#define ctype_s8  ctype_long
#define ctype_u8  ctype_unsigned_long
#endif /* !ctype_s8 */
#elif __SIZEOF_LONG__ == 2
#ifndef ctype_s16
#define ctype_s16 ctype_long
#define ctype_u16 ctype_unsigned_long
#endif /* !ctype_s16 */
#elif __SIZEOF_LONG__ == 4
#ifndef ctype_s32
#define ctype_s32 ctype_long
#define ctype_u32 ctype_unsigned_long
#endif /* !ctype_s32 */
#elif __SIZEOF_LONG__ == 8
#ifndef ctype_s64
#define ctype_s64 ctype_long
#define ctype_u64 ctype_unsigned_long
#endif /* !ctype_s64 */
#endif /* __SIZEOF_LONG__ == ... */

#if __SIZEOF_LONG_LONG__ == 1
#ifndef ctype_s8
#define ctype_s8  ctype_long_long
#define ctype_u8  ctype_unsigned_long_long
#endif /* !ctype_s8 */
#elif __SIZEOF_LONG_LONG__ == 2
#ifndef ctype_s16
#define ctype_s16 ctype_long_long
#define ctype_u16 ctype_unsigned_long_long
#endif /* !ctype_s16 */
#elif __SIZEOF_LONG_LONG__ == 4
#ifndef ctype_s32
#define ctype_s32 ctype_long_long
#define ctype_u32 ctype_unsigned_long_long
#endif /* !ctype_s32 */
#elif __SIZEOF_LONG_LONG__ == 8
#ifndef ctype_s64
#define ctype_s64 ctype_long_long
#define ctype_u64 ctype_unsigned_long_long
#endif /* !ctype_s64 */
#endif /* __SIZEOF_LONG_LONG__ == ... */

#ifndef ctype_u8
#error "Missing type: ctype_u8"
#endif /* !ctype_u8 */
#ifndef ctype_u16
#error "Missing type: ctype_u16"
#endif /* !ctype_u16 */
#ifndef ctype_u32
#error "Missing type: ctype_u32"
#endif /* !ctype_u32 */
#ifndef ctype_u64
#error "Missing type: ctype_u64"
#endif /* !ctype_u64 */

#define _ctype_s1 ctype_s8
#define _ctype_s2 ctype_s16
#define _ctype_s4 ctype_s32
#define _ctype_s8 ctype_s64
#define _ctype_u1 ctype_u8
#define _ctype_u2 ctype_u16
#define _ctype_u4 ctype_u32
#define _ctype_u8 ctype_u64
#define _ctype_sN(sizeof) _ctype_s##sizeof
#define _ctype_uN(sizeof) _ctype_u##sizeof
#define ctype_sN(sizeof)  _ctype_sN(sizeof)
#define ctype_uN(sizeof)  _ctype_uN(sizeof)

#define ctype_size_t    ctype_uN(__SIZEOF_SIZE_T__)
#define ctype_ssize_t   ctype_sN(__SIZEOF_SIZE_T__)
#define ctype_ptrdiff_t ctype_sN(__SIZEOF_PTRDIFF_T__)
#define ctype_intptr_t  ctype_sN(__SIZEOF_POINTER__)
#define ctype_uintptr_t ctype_uN(__SIZEOF_POINTER__)
#define ctype_intmax_t  ctype_sN(__SIZEOF_INTMAX_T__)
#define ctype_uintmax_t ctype_uN(__SIZEOF_INTMAX_T__)
#define ctype_byte_t    ctype_u8

#if __SIZEOF_WCHAR_T__ == 4
#define ctype_wchar_t           ctype_char32_t
#define ctype_wchar_t_ptr       ctype_char32_t_ptr
#define ctype_wchar_t_const_ptr ctype_char32_t_const_ptr
#elif __SIZEOF_WCHAR_T__ == 2
#define ctype_wchar_t           ctype_char16_t
#define ctype_wchar_t_ptr       ctype_char16_t_ptr
#define ctype_wchar_t_const_ptr ctype_char16_t_const_ptr
#else /* __SIZEOF_WCHAR_T__ == ... */
#error "Unsupported __SIZEOF_WCHAR_T__"
#endif /* __SIZEOF_WCHAR_T__ != ... */

#ifdef __ARCH_HAVE_COMPAT
#define ctype_compat_size_t    ctype_uN(__ARCH_COMPAT_SIZEOF_SIZE_T)
#define ctype_compat_ssize_t   ctype_sN(__ARCH_COMPAT_SIZEOF_SIZE_T)
#define ctype_compat_ptrdiff_t ctype_sN(__ARCH_COMPAT_SIZEOF_PTRDIFF_T)
#define ctype_compat_intptr_t  ctype_sN(__ARCH_COMPAT_SIZEOF_POINTER)
#define ctype_compat_uintptr_t ctype_uN(__ARCH_COMPAT_SIZEOF_POINTER)
#endif /* __ARCH_HAVE_COMPAT */



/* Callback type for `ctype_struct_field_callback_t'
 * @param: cookie: Cookie-argument.
 * @param: member: [1..1] The struct member being enumerated.
 * @param: parser: [1..1] A parser that may be used to load additional debug information.
 * @param: mod:    [1..1] The module containing the struct definition.
 * @param: cu:     [1..1] The compilation unit containing the struct definition.
 * @return: >= 0: Sum up this value, and continue enumeration.
 * @return: < 0:  Stop enumeration and have `ctype_struct_enumfields()' re-return this value. */
typedef NONNULL_T((2, 3, 4, 5)) ssize_t
NOTHROW_T(KCALL *ctype_struct_field_callback_t)(void *cookie,
                                                di_debuginfo_member_t const *__restrict member,
                                                di_debuginfo_cu_parser_t const *__restrict parser,
                                                struct cmodule *__restrict mod,
                                                struct cmodunit *__restrict cu);

/* Enumerate/find the fields of a given struct.
 * @param: cb:     Callback to-be invoked for the field.
 * @param: cookie: Cookie-argument for `cb'
 * @return: * :    The sum of return values of `cb'
 * @return: < 0:   A propagated, negative return value of `cb'. */
FUNDEF NONNULL((1, 2)) ssize_t
NOTHROW(FCALL ctype_struct_enumfields)(struct ctype *__restrict self,
                                       ctype_struct_field_callback_t cb,
                                       void *cookie);

/* Find a field of a given struct-kind C-type.
 * @return: DBX_EOK:    Success.
 * @return: DBX_ENOENT: No field with this name. */
FUNDEF WUNUSED NONNULL((1, 2, 4, 5)) dbx_errno_t
NOTHROW(FCALL ctype_struct_getfield)(struct ctype *__restrict self,
                                     char const *__restrict name, size_t namelen,
                                     /*out*/ struct ctyperef *__restrict pfield_type,
                                     /*out*/ ptrdiff_t *__restrict pfield_offset);

/* Return the name of a structure type, or `NULL' if unknown or `self' isn't a struct. */
FUNDEF WUNUSED NONNULL((1)) char const *
NOTHROW(FCALL ctype_struct_getname)(struct ctype const *__restrict self);


/* Load a C-type from a given `type_debug_info' which should be loaded
 * with the help of an internal copy made from `cu_parser'. The  given
 * `type_debug_info' is a pointer like `di_debuginfo_member_t::m_type'
 * @param: ptyperef_flags: When non-NULL, store type-reference flags here (`CTYPEREF_FLAG_*')
 * @return: DBX_EOK:     A reference to the associated type.
 * @return: DBX_ENOMEM:  Out of memory.
 * @return: DBX_EINTERN: Debug information was corrupted. */
FUNDEF WUNUSED NONNULL((1, 2, 3, 4, 5)) dbx_errno_t
NOTHROW(FCALL ctype_fromdw)(struct cmodule *__restrict mod,
                            struct cmodunit const *__restrict cunit,
                            di_debuginfo_cu_parser_t const *__restrict cu_parser,
                            byte_t const *__restrict type_debug_info,
                            /*out*/ struct ctyperef *__restrict presult);

/* Same as `ctype_fromdw()', but when `type_debug_info'
 * is  NULL,   fill   `*presult'   with   `ctype_void'. */
FUNDEF WUNUSED NONNULL((1, 2, 3, 5)) dbx_errno_t
NOTHROW(FCALL ctype_fromdw_opt)(struct cmodule *__restrict mod,
                                struct cmodunit const *__restrict cunit,
                                di_debuginfo_cu_parser_t const *__restrict cu_parser,
                                byte_t const *type_debug_info,
                                /*out*/ struct ctyperef *__restrict presult);

/* Parse the parameters of a subroutine or subroutine type. */
FUNDEF WUNUSED NONNULL((1, 2, 3, 4, 5)) dbx_errno_t
NOTHROW(FCALL ctype_fromdw_subroutine)(struct cmodule *__restrict mod,
                                       struct cmodunit const *__restrict cunit,
                                       di_debuginfo_cu_parser_t *__restrict parser,
                                       /*out*/ REF struct ctype **__restrict presult,
                                       /*in*/ struct ctyperef const *__restrict return_type);

#define ctype_from_cmodsyminfo(self, presult)                            \
	ctype_fromdw((self)->clv_mod, (self)->clv_unit, &(self)->clv_parser, \
	             cmodsyminfo_getdip(self), presult)

DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_MODDBX_INCLUDE_CTYPE_H */
