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
#ifndef _LIBDEBUGINFO_DEBUG_INFO_H
#define _LIBDEBUGINFO_DEBUG_INFO_H 1

#include "api.h"
#include "dwarf.h"
#include <bits/types.h>
#include <bits/format-printer.h>
#include <libc/string.h>
#include <hybrid/typecore.h>
#include <hybrid/__unaligned.h>

/* Example program layout:
 * >> int foo(int y) {
 * >>     int z = y + 10;
 * >>     if (z == 3) {
 * >>         int w = z * 2;
 * >>         z = w;
 * >>     }
 * >>     return z;
 * >> }
 *
 * DW_TAG_compile_unit:
 *     ...
 *     DW_TAG_subprogram:
 *        name   = "foo"
 *        ranges = ...
 *        ...
 *        DW_TAG_formal_parameter:
 *            name = "y"
 *            ...
 *        DW_TAG_variable:
 *            name = "z"
 *            ...
 *        DW_TAG_lexical_block:
 *            ranges = ...
 *            ...
 *            DW_TAG_variable:
 *                name = "w"
 *                ...
 */


#define DEBUGINFO_PRINT_FORMAT_KEYWORD_PREFIX   0x0002 /* Prefix for `struct', `class', `union', `enum' */
#define DEBUGINFO_PRINT_FORMAT_KEYWORD_SUFFIX   0x0003 /* ... */
#define DEBUGINFO_PRINT_FORMAT_MODIFIER_PREFIX  0x0004 /* Prefix for `const', `volatile', `atomic', `restrict' */
#define DEBUGINFO_PRINT_FORMAT_MODIFIER_SUFFIX  0x0005 /* ... */
#define DEBUGINFO_PRINT_FORMAT_PAREN_PREFIX     0x0006 /* Prefix for `(', `)' */
#define DEBUGINFO_PRINT_FORMAT_PAREN_SUFFIX     0x0007 /* ... */
#define DEBUGINFO_PRINT_FORMAT_BRACE_PREFIX     0x0008 /* Prefix for `{', `}' */
#define DEBUGINFO_PRINT_FORMAT_BRACE_SUFFIX     0x0009 /* ... */
#define DEBUGINFO_PRINT_FORMAT_BRACKET_PREFIX   0x000a /* Prefix for `[', `]' */
#define DEBUGINFO_PRINT_FORMAT_BRACKET_SUFFIX   0x000b /* ... */
#define DEBUGINFO_PRINT_FORMAT_POINTER_PREFIX   0x000c /* Prefix for `*', `&', `&&' */
#define DEBUGINFO_PRINT_FORMAT_POINTER_SUFFIX   0x000d /* ... */
#define DEBUGINFO_PRINT_FORMAT_FIELD_PREFIX     0x000e /* Prefix for `.field_name' (in struct initializers) */
#define DEBUGINFO_PRINT_FORMAT_FIELD_SUFFIX     0x000f /* ... */
#define DEBUGINFO_PRINT_FORMAT_STRING_PREFIX    0x0010 /* Prefix for `"foobar"' */
#define DEBUGINFO_PRINT_FORMAT_STRING_SUFFIX    0x0011 /* ... */
#define DEBUGINFO_PRINT_FORMAT_CHARACTER_PREFIX 0x0012 /* Prefix for `'f'' */
#define DEBUGINFO_PRINT_FORMAT_CHARACTER_SUFFIX 0x0013 /* ... */
#define DEBUGINFO_PRINT_FORMAT_INTEGER_PREFIX   0x0014 /* Prefix for `1234' */
#define DEBUGINFO_PRINT_FORMAT_INTEGER_SUFFIX   0x0015 /* ... */
#define DEBUGINFO_PRINT_FORMAT_FLOAT_PREFIX     0x0016 /* Prefix for `1234.5678' */
#define DEBUGINFO_PRINT_FORMAT_FLOAT_SUFFIX     0x0017 /* ... */
#define DEBUGINFO_PRINT_FORMAT_BOOL_PREFIX      0x0018 /* Prefix for `true' / `false' */
#define DEBUGINFO_PRINT_FORMAT_BOOL_SUFFIX      0x0019 /* ... */
#define DEBUGINFO_PRINT_FORMAT_TYPENAME_PREFIX  0x001a /* Prefix for type names */
#define DEBUGINFO_PRINT_FORMAT_TYPENAME_SUFFIX  0x001b /* ... */
#define DEBUGINFO_PRINT_FORMAT_VARNAME_PREFIX   0x001c /* Prefix for variable names */
#define DEBUGINFO_PRINT_FORMAT_VARNAME_SUFFIX   0x001d /* ... */
#define DEBUGINFO_PRINT_FORMAT_COMMA_PREFIX     0x001e /* Prefix for `,' */
#define DEBUGINFO_PRINT_FORMAT_COMMA_SUFFIX     0x001f /* ... */
#define DEBUGINFO_PRINT_FORMAT_DOTS_PREFIX      0x0020 /* Prefix for `...' */
#define DEBUGINFO_PRINT_FORMAT_DOTS_SUFFIX      0x0021 /* ... */
#define DEBUGINFO_PRINT_FORMAT_ASSIGN_PREFIX    0x0022 /* Prefix for `=' */
#define DEBUGINFO_PRINT_FORMAT_ASSIGN_SUFFIX    0x0023 /* ... */
#define DEBUGINFO_PRINT_FORMAT_UNKNOWN_PREFIX   0x0024 /* Prefix for unknown (raw) data */
#define DEBUGINFO_PRINT_FORMAT_UNKNOWN_SUFFIX   0x0025 /* ... */


#ifdef __CC__
__DECL_BEGIN

typedef struct di_debuginfo_component_attrib_struct {
	dwarf_uleb128_t   dica_name; /* Attribute name (one of `DW_AT_*'; e.g. `DW_AT_producer') */
	dwarf_uleb128_t   dica_form; /* Attribute form (one of `DW_FORM_*'; e.g. `DW_FORM_strp') */
} di_debuginfo_component_attrib_t;

typedef struct di_debuginfo_component_struct {
	__uintptr_t                      dic_tag;          /* Component tag (one of `DW_TAG_*'; e.g. `DW_TAG_compile_unit') */
	di_debuginfo_component_attrib_t *dic_attrib_start; /* [1..1] Pointer to the list of (attr_name,attr_form) ULEB pairs of this entry */
	di_debuginfo_component_attrib_t *dic_attrib_end;   /* [1..1] End of attributes. */
	__uint8_t                        dic_haschildren;  /* `DW_CHILDREN_yes' if follow-up on this entry is a child */
} di_debuginfo_component_t;

typedef struct di_debuginfo_cu_parser_sections_struct {
	__byte_t                *cps_debug_abbrev_start; /* [1..1][const] Starting address of `.debug_abbrev' */
	__byte_t                *cps_debug_abbrev_end;   /* [1..1][const] End address of `.debug_abbrev' */
	__byte_t                *cps_debug_loc_start;    /* [0..1][const] Starting address of `.debug_loc'
	                                                  * NOTE: When set equal to `cps_debug_loc_end', location list expression
	                                                  *       cannot be used and will appear as though they weren't present at
	                                                  *       all. */
	__byte_t                *cps_debug_loc_end;      /* [0..1][const] End address of `.debug_loc' */
	__byte_t                *cps_debug_str_start;    /* [0..1][const] Starting address of `.debug_str'
	                                                  * NOTE: When set equal to `cps_debug_str_end', strings referring to
	                                                  *       this section will be returned as `???' (3 question marks) */
	__byte_t                *cps_debug_str_end;      /* [0..1][const] End address of `.debug_str' */
} di_debuginfo_cu_parser_sections_t;

typedef struct di_debuginfo_cu_parser_struct {
	di_debuginfo_cu_parser_sections_t const
	                        *dup_sections;        /* [0..1][const] Section information. */
	__byte_t                *dup_cu_abbrev_start; /* [1..1][const] Starting address of debug abbreviations (in .debug_abbrev). */
	__byte_t                *dup_cu_abbrev_end;   /* [1..1][const] End address of debug abbreviations (in .debug_abbrev). */
	__byte_t                *dup_cu_info_hdr;     /* [1..1][const] Address of the debug information header (in .debug_info). */
	__byte_t                *dup_cu_info_end;     /* [1..1][const] End address of debug information data (in .debug_info). */
	__byte_t                *dup_cu_info_pos;     /* [1..1][>= dup_cu_info_hdr && <= dup_cu_info_pos] Current position in debug information data (in .debug_info). */
	__uintptr_t              dup_child_depth;     /* The child-recursion-depth of `dp_comp' */
	di_debuginfo_component_t dup_comp;            /* The component currently being parsed. */
	__uint8_t                dup_addrsize;        /* Address size */
	__uint16_t               dup_version;         /* DWARF version */
} di_debuginfo_cu_parser_t;

#ifndef __di_debuginfo_location_t_defined
#define __di_debuginfo_location_t_defined 1
/* NOTE: The user-interface API for this type is exported
 *       by `libunwind', rather than `libdebuginfo'! */
typedef struct di_debuginfo_location_struct {
	__byte_t *l_expr;  /* [0..1] Pointer to a CFI expression (for use with `unwind_emulator_exec') for the pointed-to expression. */
	__byte_t *l_llist; /* [0..1] Pointer to a CFI location list (points into the `.debug_loc' section). */
} di_debuginfo_location_t;
#endif /* !__di_debuginfo_location_t_defined */

/* Parse and enumerate the attributes of the current component.
 * NOTE: This must be done _exactly_ once before the next call
 *       to one of `debuginfo_cu_parser_next*'
 * >> di_debuginfo_cu_parser_t parser;
 * >> while (debuginfo_cu_parser_loadunit(..., &parser) == DEBUG_INFO_ERROR_SUCCESS) {
 * >>     do {
 * >>         di_debuginfo_component_attrib_t attr;
 * >>         DI_DEBUGINFO_CU_PARSER_EACHATTR(attr,& parser) {
 * >>             ...
 * >>         }
 * >>     } while (debuginfo_cu_parser_next(&parser) == DEBUG_INFO_ERROR_SUCCESS);
 * >> }
 */
#define DI_DEBUGINFO_CU_PARSER_EACHATTR(attr,self)                                \
	for (__byte_t *_attr_reader = (__byte_t *)(self)->dup_comp.dic_attrib_start;  \
	               _attr_reader < (__byte_t *)(self)->dup_comp.dic_attrib_end &&  \
	              (self)->dup_cu_info_pos < (self)->dup_cu_info_end;              \
	     debuginfo_cu_parser_skipform(self,(attr).dica_form))                     \
	if (((attr).dica_name = dwarf_decode_uleb128((__byte_t **)&_attr_reader),     \
	     (attr).dica_form = dwarf_decode_uleb128((__byte_t **)&_attr_reader),0)); \
	else if (!(attr).dica_name && !(attr).dica_form) break; else


/* Given a pointer to the start of a debug_info CU (or a pointer to the start
 * of the .debug_info section), as well as the start & end of the .debug_abbrev
 * section, initialize the given debuginfo CU parser structure `result', and
 * advance `*pdebug_info_reader' to the start of the next unit.
 * @param: first_component_pointer: A pointer to the first component to load, or `NULL'
 *                                  to simply load the first component following the
 *                                  start of the associated CU descriptor.
 * @return: DEBUG_INFO_ERROR_SUCCESS: ...
 * @return: DEBUG_INFO_ERROR_NOFRAME: All units have been loaded.
 * @return: DEBUG_INFO_ERROR_CORRUPT: ... */
typedef unsigned int
(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_LOADUNIT)(__byte_t **__restrict pdebug_info_reader,
                                                 __byte_t *__restrict debug_info_end,
                                                 di_debuginfo_cu_parser_sections_t const *__restrict sectinfo,
                                                 di_debuginfo_cu_parser_t *__restrict result,
                                                 __byte_t *first_component_pointer);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL unsigned int
__NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_loadunit)(__byte_t **__restrict pdebug_info_reader,
                                                            __byte_t *__restrict debug_info_end,
                                                            di_debuginfo_cu_parser_sections_t const *__restrict sectinfo,
                                                            di_debuginfo_cu_parser_t *__restrict result,
                                                            __byte_t *first_component_pointer);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */



/* Skip data associated with the given attribute form.
 * @param: form: One of `DW_FORM_*' */
typedef void
(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_SKIPFORM)(di_debuginfo_cu_parser_t *__restrict self,
                                                 dwarf_uleb128_t form);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL void
__NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_skipform)(di_debuginfo_cu_parser_t *__restrict self,
                                                            dwarf_uleb128_t form);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */

/* Start a new component.
 * NOTE: Prior to calling of these functions, you may assign `self->dup_cu_info_pos' to
 *       the starting address of the next component to-be read. - Valid values for this
 *       are usually returned by `debuginfo_cu_parser_getref()', and can be found in some
 *       of the structures initialized by the `debuginfo_cu_parser_loadattr_*()' functions.
 * @return: true: ...
 * @return: false: [debuginfo_cu_parser_next] All components have been parsed.
 * @return: false: [*] The next component doesn't exist, or isn't a child/sibling/parent. */
typedef __BOOL (LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_NEXT)(di_debuginfo_cu_parser_t *__restrict self);
typedef __BOOL (LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_NEXTCHILD)(di_debuginfo_cu_parser_t *__restrict self);
typedef __BOOL (LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_NEXTSIBLING)(di_debuginfo_cu_parser_t *__restrict self);
typedef __BOOL (LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_NEXTPARENT)(di_debuginfo_cu_parser_t *__restrict self);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_next)(di_debuginfo_cu_parser_t *__restrict self);
LIBDEBUGINFO_DECL __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_nextchild)(di_debuginfo_cu_parser_t *__restrict self);
LIBDEBUGINFO_DECL __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_nextsibling)(di_debuginfo_cu_parser_t *__restrict self);
LIBDEBUGINFO_DECL __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_nextparent)(di_debuginfo_cu_parser_t *__restrict self);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */

/* Skip the attributes of the current component (must be called if not
 * parsed explicitly prior to the next call to `debuginfo_cu_parser_next*') */
typedef void (LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_SKIPATTR)(di_debuginfo_cu_parser_t *__restrict self);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL void __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_skipattr)(di_debuginfo_cu_parser_t *__restrict self);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */

/* Load the current debug information as an attribute encoded as
 * `form' into a storage class matching the given result-operand.
 *  - debuginfo_cu_parser_getstring(): DW_FORM_strp, DW_FORM_string
 *  - debuginfo_cu_parser_getaddr():   DW_FORM_addr
 *  - debuginfo_cu_parser_getconst():  DW_FORM_data1, DW_FORM_data2, DW_FORM_data4, DW_FORM_data8, DW_FORM_sdata, DW_FORM_udata, DW_FORM_sec_offset
 *  - debuginfo_cu_parser_getflag():   DW_FORM_flag, DW_FORM_flag_present
 *  - debuginfo_cu_parser_getref():    DW_FORM_ref_addr, DW_FORM_ref1, DW_FORM_ref2, DW_FORM_ref4, DW_FORM_ref8, DW_FORM_ref_sig8, DW_FORM_ref_udata
 *  - debuginfo_cu_parser_getexpr():   DW_FORM_exprloc */
typedef __BOOL (LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_GETSTRING)(di_debuginfo_cu_parser_t const *__restrict self, __uintptr_t form, char **__restrict presult);
typedef __BOOL (LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_GETADDR)(di_debuginfo_cu_parser_t const *__restrict self, __uintptr_t form, __uintptr_t *__restrict presult);
typedef __BOOL (LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_GETCONST)(di_debuginfo_cu_parser_t const *__restrict self, __uintptr_t form, __uintptr_t *__restrict presult);
typedef __BOOL (LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_GETFLAG)(di_debuginfo_cu_parser_t const *__restrict self, __uintptr_t form, __BOOL *__restrict presult);
typedef __BOOL (LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_GETREF)(di_debuginfo_cu_parser_t const *__restrict self, __uintptr_t form, __byte_t **__restrict presult);
typedef __BOOL (LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_GETEXPR)(di_debuginfo_cu_parser_t const *__restrict self, __uintptr_t form, di_debuginfo_location_t *__restrict result);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_getstring)(di_debuginfo_cu_parser_t const *__restrict self, __uintptr_t form, char **__restrict presult);
LIBDEBUGINFO_DECL __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_getaddr)(di_debuginfo_cu_parser_t const *__restrict self, __uintptr_t form, __uintptr_t *__restrict presult);
LIBDEBUGINFO_DECL __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_getconst)(di_debuginfo_cu_parser_t const *__restrict self, __uintptr_t form, __uintptr_t *__restrict presult);
LIBDEBUGINFO_DECL __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_getflag)(di_debuginfo_cu_parser_t const *__restrict self, __uintptr_t form, __BOOL *__restrict presult);
LIBDEBUGINFO_DECL __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_getref)(di_debuginfo_cu_parser_t const *__restrict self, __uintptr_t form, __byte_t **__restrict presult);
LIBDEBUGINFO_DECL __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_getexpr)(di_debuginfo_cu_parser_t const *__restrict self, __uintptr_t form, di_debuginfo_location_t *__restrict result);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */



typedef struct {
	__uintptr_t   r_ranges_offset; /* Offset to into .debug_ranges to a list of exact ranges, or `(uintptr_t)-1' if unused. */
	__uintptr_t   r_startpc;       /* Starting program counter position (or `r_ranges != (uintptr_t)-1 ? 0 : (uintptr_t)-1' if unknown). */
	__uintptr_t   r_endpc;         /* Ending program counter position (or `0' if unknown). */
} di_debuginfo_ranges_t;
#define DEBUGINFO_RANGES_ISSINGLERANGE(x) ((x)->r_ranges_offset == (__uintptr_t)-1)

typedef struct {
	di_debuginfo_ranges_t const *ri_ranges;   /* [1..1][const] The underlying range object. */
	__byte_t                    *ri_pos;      /* [1..1] Current iterator position (or >= ri_end if the iterator was exhausted) */
	__byte_t                    *ri_end;      /* [1..1][const] Iterator end position */
	__uintptr_t                  ri_initbase; /* Initial base */
	__uint8_t                    ri_addrsize; /* [const] Address size. */
} di_debuginfo_ranges_iterator_t;

/* Initialize an iterator for enumerating ranges stored within a given debug_info range selector.
 * >> __uintptr_t start_pc,end_pc;
 * >> di_debuginfo_ranges_iterator_t iter;
 * >> di_debuginfo_ranges_iterator_init(&iter,...);
 * >> while (di_debuginfo_ranges_iterator_next(&iter,&start_pc,&end_pc)) {
 * >>     ...
 * >> }
 * @param: debug_ranges_start: Starting address of the `.debug_ranges' section.
 * @param: debug_ranges_end:   End address of the `.debug_ranges' section. */
__LOCAL void
__NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_ranges_iterator_init)(di_debuginfo_ranges_iterator_t *__restrict self,
                                                              di_debuginfo_ranges_t const *__restrict ranges,
                                                              di_debuginfo_cu_parser_t const *__restrict parser,
                                                              __uintptr_t cu_base,
                                                              __byte_t *__restrict debug_ranges_start,
                                                              __byte_t *__restrict debug_ranges_end) {
	self->ri_ranges   = ranges;
	self->ri_addrsize = parser->dup_addrsize;
	self->ri_initbase = ranges->r_startpc != (__uintptr_t)-1 ? ranges->r_startpc : cu_base;
	if (DEBUGINFO_RANGES_ISSINGLERANGE(ranges)) {
		self->ri_pos = self->ri_end = (__byte_t *)-1;
	} else if (ranges->r_ranges_offset >= (__size_t)(debug_ranges_end - debug_ranges_start)) {
		self->ri_pos = self->ri_end = __NULLPTR;
	} else {
		self->ri_pos = debug_ranges_start + ranges->r_ranges_offset;
		self->ri_end = debug_ranges_end;
	}
}

/* Yield the next range accessible through a given debug-ranges iterator. */
__LOCAL __BOOL
__NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_ranges_iterator_next)(di_debuginfo_ranges_iterator_t *__restrict self,
                                                              __uintptr_t *__restrict pmodule_relative_start_pc,
                                                              __uintptr_t *__restrict pmodule_relative_end_pc) {
	__uintptr_t range_start,range_end;
again:
	if (self->ri_pos >= self->ri_end) {
		if (self->ri_end == (__byte_t *)-1) {
			*pmodule_relative_start_pc = self->ri_ranges->r_startpc;
			*pmodule_relative_end_pc   = self->ri_ranges->r_endpc;
			self->ri_end = __NULLPTR;
			return 1;
		}
		return 0;
	}
	switch (self->ri_addrsize) {
	case 1:
		range_start   = *(__uint8_t *)self->ri_pos;
		self->ri_pos += 1;
		range_end     = *(__uint8_t *)self->ri_pos;
		self->ri_pos += 1;
		break;
	case 2:
		range_start   = __hybrid_unaligned_get16((__uint16_t *)self->ri_pos);
		self->ri_pos += 2;
		range_end     = __hybrid_unaligned_get16((__uint16_t *)self->ri_pos);
		self->ri_pos += 2;
		break;
	case 4:
		range_start   = __hybrid_unaligned_get32((__uint32_t *)self->ri_pos);
		self->ri_pos += 4;
		range_end     = __hybrid_unaligned_get32((__uint32_t *)self->ri_pos);
		self->ri_pos += 4;
		break;
#if __SIZEOF_POINTER__ > 4
	case 8:
		range_start   = __hybrid_unaligned_get64((__uint64_t *)self->ri_pos);
		self->ri_pos += 8;
		range_end     = __hybrid_unaligned_get64((__uint64_t *)self->ri_pos);
		self->ri_pos += 8;
		break;
#endif
	default: __builtin_unreachable();
	}
	if (range_start == (__uintptr_t)-1) {
		/* Base address selection entry! */
		self->ri_initbase = range_end;
		goto again;
	} else if (!range_start && !range_end) {
		/* Range list end entry. */
		self->ri_pos = self->ri_end;
		return 0;
	} else {
		range_start += self->ri_initbase;
		range_end   += self->ri_initbase;
	}
	*pmodule_relative_start_pc = range_start;
	*pmodule_relative_end_pc   = range_end;
	return 1;
}



/* Check if a given `module_relative_pc' is apart of the given range selector.
 * @param: self: The ranges object to query for `module_relative_pc' */
__LOCAL unsigned int
__NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_ranges_contains)(di_debuginfo_ranges_t const *__restrict self,
                                                         di_debuginfo_cu_parser_t const *__restrict parser,
                                                         __uintptr_t cu_base,
                                                         __uintptr_t module_relative_pc,
                                                         __byte_t *__restrict debug_ranges_start,
                                                         __byte_t *__restrict debug_ranges_end) {
	__byte_t *iter;
	if (DEBUGINFO_RANGES_ISSINGLERANGE(self)) {
		return (module_relative_pc >= self->r_startpc &&
		        module_relative_pc < self->r_endpc)
		      ? DEBUG_INFO_ERROR_SUCCESS
		      : DEBUG_INFO_ERROR_NOFRAME
		      ;
	}
	if __unlikely(self->r_ranges_offset >= (__size_t)(debug_ranges_end - debug_ranges_start))
		return DEBUG_INFO_ERROR_CORRUPT;
	if (self->r_startpc != (__uintptr_t)-1)
		cu_base = self->r_startpc;
	iter = debug_ranges_start + self->r_ranges_offset;
	while (iter < debug_ranges_end) {
		__uintptr_t range_start,range_end;
		switch (parser->dup_addrsize) {
		case 1:
			range_start = *(__uint8_t *)iter;
			iter       += 1;
			range_end   = *(__uint8_t *)iter;
			iter       += 1;
			break;
		case 2:
			range_start = __hybrid_unaligned_get16((__uint16_t *)iter);
			iter       += 2;
			range_end   = __hybrid_unaligned_get16((__uint16_t *)iter);
			iter       += 2;
			break;
		case 4:
			range_start = __hybrid_unaligned_get32((__uint32_t *)iter);
			iter       += 4;
			range_end   = __hybrid_unaligned_get32((__uint32_t *)iter);
			iter       += 4;
			break;
#if __SIZEOF_POINTER__ > 4
		case 8:
			range_start = __hybrid_unaligned_get64((__uint64_t *)iter);
			iter       += 8;
			range_end   = __hybrid_unaligned_get64((__uint64_t *)iter);
			iter       += 8;
			break;
#endif
		default:
			__builtin_unreachable();
		}
		if (range_start == (__uintptr_t)-1) {
			/* Base address selection entry! */
			cu_base = range_end;
			continue;
		} else if (!range_start && !range_end) {
			/* Range list end entry. */
			break;
		} else {
			range_start += cu_base;
			range_end   += cu_base;
		}
		if (module_relative_pc >= range_start &&
		    module_relative_pc < range_end)
			return DEBUG_INFO_ERROR_SUCCESS;
	}
	return DEBUG_INFO_ERROR_NOFRAME;
}

__LOCAL unsigned int
__NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_ranges_contains_ex)(di_debuginfo_ranges_t const *__restrict self,
                                                            di_debuginfo_cu_parser_t const *__restrict parser,
                                                            __uintptr_t cu_base,
                                                            __uintptr_t module_relative_pc,
                                                            __byte_t *__restrict debug_ranges_start,
                                                            __byte_t *__restrict debug_ranges_end,
                                                            __uintptr_t *__restrict poverlap_start,
                                                            __uintptr_t *__restrict poverlap_end) {
	__byte_t *iter;
	__COMPILER_IGNORE_UNINITIALIZED(*poverlap_start);
	__COMPILER_IGNORE_UNINITIALIZED(*poverlap_end);
	if (DEBUGINFO_RANGES_ISSINGLERANGE(self)) {
		if (module_relative_pc < self->r_startpc ||
		    module_relative_pc >= self->r_endpc)
			return DEBUG_INFO_ERROR_NOFRAME;
		*poverlap_start = self->r_startpc;
		*poverlap_end   = self->r_endpc;
		return DEBUG_INFO_ERROR_SUCCESS;
	}
	if __unlikely(self->r_ranges_offset >= (__size_t)(debug_ranges_end - debug_ranges_start))
		return DEBUG_INFO_ERROR_CORRUPT;
	if (self->r_startpc != (__uintptr_t)-1)
		cu_base = self->r_startpc;
	iter = debug_ranges_start + self->r_ranges_offset;
	while (iter < debug_ranges_end) {
		__uintptr_t range_start,range_end;
		switch (parser->dup_addrsize) {
		case 1:
			range_start = *(__uint8_t *)iter;
			iter       += 1;
			range_end   = *(__uint8_t *)iter;
			iter       += 1;
			break;
		case 2:
			range_start = __hybrid_unaligned_get16((__uint16_t *)iter);
			iter       += 2;
			range_end   = __hybrid_unaligned_get16((__uint16_t *)iter);
			iter       += 2;
			break;
		case 4:
			range_start = __hybrid_unaligned_get32((__uint32_t *)iter);
			iter       += 4;
			range_end   = __hybrid_unaligned_get32((__uint32_t *)iter);
			iter       += 4;
			break;
#if __SIZEOF_POINTER__ > 4
		case 8:
			range_start = __hybrid_unaligned_get64((__uint64_t *)iter);
			iter       += 8;
			range_end   = __hybrid_unaligned_get64((__uint64_t *)iter);
			iter       += 8;
			break;
#endif
		default:
			__builtin_unreachable();
		}
		if (range_start == (__uintptr_t)-1) {
			/* Base address selection entry! */
			cu_base = range_end;
			continue;
		} else if (!range_start && !range_end) {
			/* Range list end entry. */
			break;
		} else {
			range_start += cu_base;
			range_end   += cu_base;
		}
		if (module_relative_pc >= range_start &&
		    module_relative_pc < range_end) {
			*poverlap_start = range_start;
			*poverlap_end   = range_end;
			return DEBUG_INFO_ERROR_SUCCESS;
		}
	}
	return DEBUG_INFO_ERROR_NOFRAME;
}










/* Helper types/functions for loading specific debug information tags. */
typedef struct di_debuginfo_compile_unit_struct {
	/* For `DW_TAG_compile_unit'
	 * NOTE: This TAG is followed by a tree/sequence of child-nodes containing information
	 *       about the individual components that make up this compilation unit.
	 *       These components are enumerated as follows:
	 * >> __uintptr_t cu_depth = parser.dup_child_depth;
	 * >> if (debuginfo_cu_parser_nextchild(&parser)) {
	 * >>     do {
	 * >>         ... Handle a child
	 * >>     } while (debuginfo_cu_parser_next(&parser) && parser.dup_child_depth > cu_depth);
	 * >> }
	 * >> // At this point, the parser should point to the next sibling of the CU.
	 * >> // Usually, these are definition components for types and the like, which
	 * >> // are referred to by other components found previously.
	 */
	__uintptr_t           cu_stmt_list; /* Offset into `.debug_line' (to-be used with `debugline_loadunit')
	                                     * to this CU's address-to-line data blob.
	                                     * If unknown, set to `(__uintptr_t)-1' (but always assume undefined
	                                     * if this offset points past- or at the end of the .debug_line section) */
	char                 *cu_name;      /* [0..1] Name of the compilation unit. */
	char                 *cu_comp_dir;  /* [0..1] Path to the compiler base directory (prepended before filenames,
	                                     * this is essentially the getcwd() of the compiler when the CU was assembled). */
	di_debuginfo_ranges_t cu_ranges;    /* List of debug ranges associated with addresses apart of this CU. */
} di_debuginfo_compile_unit_t;

typedef struct di_debuginfo_subprogram_struct {
	/* For `DW_TAG_subprogram' */
#define DW_SUBPROGRAM_FNORMAL   0x00000000 /* Normal program flags. */
#define DW_SUBPROGRAM_FEXTERN   0x00000001 /* The function is either INTERN or PUBLIC */
#define DW_SUBPROGRAM_FNORETURN 0x00000002 /* The function is either NORETURN */
	__uintptr_t             sp_flags;        /* Function flags (Set of `DW_SUBPROGRAM_F*') */
	char                   *sp_name;         /* [0..1] Name of the function. */
	char                   *sp_rawname;      /* [0..1] Raw (linkage) name of the function. */
	di_debuginfo_location_t sp_frame_base;   /* Frame base expression. */
	di_debuginfo_ranges_t   sp_ranges;       /* Program counter ranges. */
	__uintptr_t             sp_decl_file;    /* Declaring file index (used with the addr2line program pointed
	                                          * to by the associated CU's `cu_stmt_list') (or 0 if undefined) */
	__uintptr_t             sp_decl_line;    /* Declaring line number (or 0 if undefined) */
	__uintptr_t             sp_decl_column;  /* Declaring column offset (or 0 if undefined) */
} di_debuginfo_subprogram_t;

typedef struct di_debuginfo_inlined_subroutine_struct {
	/* For `DW_TAG_inlined_subroutine' */
	__byte_t             *is_subprogram;    /* [0..1] Pointer to the debug_info for the function's declaration (i.e. its `DW_TAG_subprogram').
	                                         * To load this structure, do the following:
	                                         * >> if ((...).is_subprogram != NULL) {
	                                         * >>     parser.dup_cu_info_pos = (...).is_subprogram;
	                                         * >>     debuginfo_cu_parser_next(&parser);
	                                         * >>     if (parser.dup_comp.dic_tag == DW_TAG_subprogram) {
	                                         * >>         di_debuginfo_subprogram_t prog;
	                                         * >>         if (debuginfo_cu_parser_loadattr_subprogram(&parser,&prog) == DEBUG_INFO_ERROR_SUCCESS) {
	                                         * >>             // Success
	                                         * >>             ...
	                                         * >>         }
	                                         * >>     }
	                                         * >> } */
	di_debuginfo_ranges_t is_ranges;        /* Program counter ranges. */
	__uintptr_t           is_call_file;     /* Call source file index (used with the addr2line program pointed
	                                         * to by the associated CU's `cu_stmt_list') (or 0 if undefined) */
	__uintptr_t           is_call_line;     /* Call source line number (or 0 if undefined) */
	__uintptr_t           is_call_column;   /* Call source column offset (or 0 if undefined) */
} di_debuginfo_inlined_subroutine_t;

typedef struct di_debuginfo_lexical_block_struct {
	/* For `DW_TAG_lexical_block' / `DW_TAG_try_block' / `DW_TAG_catch_block' */
	di_debuginfo_ranges_t lb_ranges;        /* Program counter ranges. */
} di_debuginfo_lexical_block_t;

typedef struct di_debuginfo_type_struct {
	/* For `DW_TAG_*_type' */
	char                 *t_name;          /* [0..1] Name of the type. */
	char                 *t_rawname;       /* [0..1] Raw (linkage) name of the type. */
	__uintptr_t           t_decl_file;     /* Call source file index (used with the addr2line program pointed
	                                        * to by the associated CU's `cu_stmt_list') (or 0 if undefined) */
	__uintptr_t           t_decl_line;     /* Call source line number (or 0 if undefined) */
	__uintptr_t           t_decl_column;   /* Call source column offset (or 0 if undefined) */
	__uintptr_t           t_sizeof;        /* Size of this type (in bytes) (or 0 if undefined) */
	__byte_t             *t_type;          /* [0..1] Underlying type (e.g. array element type). */
	__uintptr_t           t_encoding;      /* Value of `DW_AT_encoding' (one of `DW_ATE_UTF', or 0 if undefined) */
} di_debuginfo_type_t;


typedef struct di_debuginfo_member_struct {
	/* For `DW_TAG_member' */
	__byte_t             *m_type;           /* [0..1] Pointer to the debug_info for the member's type (which is one of `DW_TAG_*_type').
	                                         * To load this structure, create a copy of your parser and assign this pointer to it's `dup_cu_info_pos'
	                                         * field. Afterwards, call `debuginfo_cu_parser_next()' to load the pointed-to component. */
	char                 *m_name;           /* [0..1] Name of the member. */
	__uintptr_t           m_decl_file;      /* Declaring file index (used with the addr2line program pointed
	                                         * to by the associated CU's `cu_stmt_list') (or 0 if undefined) */
	__uintptr_t           m_decl_line;      /* Declaring line number (or 0 if undefined) */
	__uintptr_t           m_decl_column;    /* Declaring column offset (or 0 if undefined) */
	__uintptr_t           m_offset;         /* offsetof() this member (or (__uintptr_t)-1 if undefined) */
	__uintptr_t           m_bit_size;       /* Number of bits apart of a bit-field (or `0' if this isn't a bit-field) */
	__uintptr_t           m_bit_offset;     /* Number of bits to the left of the leftmost (most significant) bit of the bit field value. */
} di_debuginfo_member_t;

typedef struct di_debuginfo_variable_struct {
	/* For `DW_TAG_variable' / `DW_TAG_formal_parameter' */
	__byte_t               *v_type;           /* [0..1] Type of this variable. */
	di_debuginfo_location_t v_location;       /* CFI expression to decode the storage location of this variable. */
	char                   *v_name;           /* [0..1] Name of the variable. */
	char                   *v_rawname;        /* [0..1] Raw (linkage) name of the variable. */
	__uintptr_t             v_decl_file;      /* Declaring file index (used with the addr2line program pointed
	                                           * to by the associated CU's `cu_stmt_list') (or 0 if undefined) */
	__uintptr_t             v_decl_line;      /* Declaring line number (or 0 if undefined) */
	__uintptr_t             v_decl_column;    /* Declaring column offset (or 0 if undefined) */
} di_debuginfo_variable_t;

#define DW_TAG_entry_point            0x03
#define DW_TAG_label                  0x0a
#define DW_TAG_inheritance            0x1c

/* Load attributes specific to a certain component:
 *   - debuginfo_cu_parser_loadattr_compile_unit():       DW_TAG_compile_unit
 *   - debuginfo_cu_parser_loadattr_subprogram():         DW_TAG_subprogram
 *   - debuginfo_cu_parser_loadattr_inlined_subroutine(): DW_TAG_inlined_subroutine
 *   - debuginfo_cu_parser_loadattr_lexical_block():      DW_TAG_lexical_block, DW_TAG_try_block, DW_TAG_catch_block
 *   - debuginfo_cu_parser_loadattr_type():               DW_TAG_*_type
 *   - debuginfo_cu_parser_loadattr_member():             DW_TAG_member
 *   - debuginfo_cu_parser_loadattr_variable():           DW_TAG_variable, DW_TAG_formal_parameter
 * @return: true:  Successfully loaded the component attributes.
 * @return: false: Corrupted/incomplete attributes. */
typedef __BOOL (LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_LOADATTR_COMPILE_UNIT)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_compile_unit_t *__restrict result);
typedef __BOOL (LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_LOADATTR_SUBPROGRAM)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_subprogram_t *__restrict result);
typedef __BOOL (LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_LOADATTR_INLINED_SUBROUTINE)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_inlined_subroutine_t *__restrict result);
typedef __BOOL (LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_LOADATTR_LEXICAL_BLOCK)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_lexical_block_t *__restrict result);
typedef __BOOL (LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_LOADATTR_TYPE)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_type_t *__restrict result);
typedef __BOOL (LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_LOADATTR_MEMBER)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_member_t *__restrict result);
typedef __BOOL (LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_LOADATTR_VARIABLE)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_variable_t *__restrict result);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_loadattr_compile_unit)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_compile_unit_t *__restrict result);
LIBDEBUGINFO_DECL __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_loadattr_subprogram)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_subprogram_t *__restrict result);
LIBDEBUGINFO_DECL __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_loadattr_inlined_subroutine)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_inlined_subroutine_t *__restrict result);
LIBDEBUGINFO_DECL __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_loadattr_lexical_block)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_lexical_block_t *__restrict result);
LIBDEBUGINFO_DECL __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_loadattr_type)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_type_t *__restrict result);
LIBDEBUGINFO_DECL __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_loadattr_member)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_member_t *__restrict result);
LIBDEBUGINFO_DECL __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_loadattr_variable)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_variable_t *__restrict result);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */



/* Print prefix/suffix strings for various syntax components.
 *  -> Intended for encoding ANSI-TTY color codes in order to allow for syntax highlighting
 * @param: format_option: The format string being requested (one of `DEBUGINFO_PRINT_FORMAT_*')
 * @return: * :  The sum of return values from calls to `*printer', or
 *               a negative value if an error occurred while printing. */
typedef __ssize_t
(LIBDEBUGINFO_CC *debuginfo_print_format_t)(void *format_arg, __pformatprinter printer,
                                            void *arg, unsigned int format_option);


/* Print the C/C++-like representation of a given value, given DWARF debug information
 * about its typing, where `parser' must have been set up to have already loaded the
 * given `type' component for the given data blob:
 * >> di_debuginfo_variable_t var;
 * >> ... // Load `var'
 * >> {
 * >>     di_debuginfo_cu_parser_t pp = parser;
 * >>     di_debuginfo_type_t typ;
 * >>     void *buffer;
 * >>
 * >>     // Load type information for the variable.
 * >>     pp.dup_cu_info_pos = var.v_type;
 * >>     debuginfo_cu_parser_loadattr_type(&pp,&typ);
 * >>
 * >>     // Load the value of this variable.
 * >>     buffer = malloca(typ.t_sizeof);
 * >>     debug_cfa_getvalue(&REGISTERS,&GET_REGISTER,var.v_location,buffer,typ.t_sizeof);
 * >>
 * >>     // Print a representation of the variable, and its data.
 * >>     debuginfo_print_value(PRINTER,ARG,&pp,&type,v.v_name,buffer,typ.t_sizeof);
 * >> }
 * @param: varname: Name of the value (when NULL, print as a cast-like expression;
 *                  otherwise, print as an declaration)
 * @param: flags:   Set of `DEBUGINFO_PRINT_VALUE_F*'
 */
typedef __ssize_t
(LIBDEBUGINFO_CC *PDEBUGINFO_PRINT_VALUE)(__pformatprinter printer, void *arg,
                                          di_debuginfo_cu_parser_t const *__restrict parser,
                                          di_debuginfo_type_t const *__restrict type,
                                          char const *varname, void const *__restrict data,
                                          __size_t datasize, __size_t newline_indentation,
                                          debuginfo_print_format_t format_printer,
                                          void *format_arg, unsigned int flags);
typedef __ssize_t
(LIBDEBUGINFO_CC *PDEBUGINFO_PRINT_TYPENAME)(__pformatprinter printer, void *arg,
                                             di_debuginfo_cu_parser_t const *__restrict parser,
                                             di_debuginfo_type_t const *__restrict type,
                                             char const *varname,
                                             debuginfo_print_format_t format_printer,
                                             void *format_arg);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ssize_t LIBDEBUGINFO_CC
debuginfo_print_value(__pformatprinter printer, void *arg,
                      di_debuginfo_cu_parser_t const *__restrict parser,
                      di_debuginfo_type_t const *__restrict type,
                      char const *varname, void const *__restrict data,
                      __size_t datasize, __size_t newline_indentation,
                      debuginfo_print_format_t format_printer,
                      void *format_arg, unsigned int flags);
LIBDEBUGINFO_DECL __ssize_t LIBDEBUGINFO_CC
debuginfo_print_typename(__pformatprinter printer, void *arg,
                         di_debuginfo_cu_parser_t const *__restrict parser,
                         di_debuginfo_type_t const *__restrict type,
                         char const *varname,
                         debuginfo_print_format_t format_printer,
                         void *format_arg);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */

#define DEBUGINFO_PRINT_VALUE_FNORMAL        0x0000
#define DEBUGINFO_PRINT_VALUE_FCASTALL       0x0001 /* Include explicit type casts for all expressions */


typedef struct di_enum_locals_sections_struct {
	__byte_t *el_eh_frame_start;      /* [0..1] Starting address of the .eh_frame section. */
	__byte_t *el_eh_frame_end;        /* [0..1] End address of the .eh_frame section. */
	__byte_t *el_debug_info_start;    /* [0..1] Starting address of the `.debug_info' section */
	__byte_t *el_debug_info_end;      /* [0..1] End address of the `.debug_info' section */
	__byte_t *el_debug_abbrev_start;  /* [0..1] Starting address of `.debug_abbrev' */
	__byte_t *el_debug_abbrev_end;    /* [0..1] End address of `.debug_abbrev' */
	__byte_t *el_debug_loc_start;     /* [0..1] Starting address of `.debug_loc' */
	__byte_t *el_debug_loc_end;       /* [0..1] End address of `.debug_loc' */
	__byte_t *el_debug_str_start;     /* [0..1] Starting address of `.debug_str' */
	__byte_t *el_debug_str_end;       /* [0..1] End address of `.debug_str' */
	__byte_t *el_debug_aranges_start; /* [0..1] Starting address of the `.debug_aranges' section */
	__byte_t *el_debug_aranges_end;   /* [0..1] End address of the `.debug_aranges' section */
	__byte_t *el_debug_ranges_start;  /* [0..1] Starting address of the `.debug_ranges' section */
	__byte_t *el_debug_ranges_end;    /* [0..1] End address of the `.debug_ranges' section */
} di_enum_locals_sections_t;
#define di_enum_locals_sections_as_unwind_emulator_sections(x)        ((struct unwind_emulator_sections_struct *)(x))
#define di_enum_locals_sections_as_di_debuginfo_cu_parser_sections(x) ((struct di_debuginfo_cu_parser_sections_struct *)&(x)->el_debug_abbrev_start)


/* Callback for `debuginfo_enum_locals()' */
typedef __ssize_t
(LIBDEBUGINFO_CC *debuginfo_enum_locals_callback_t)(void *arg,
                                                    di_debuginfo_cu_parser_t const *__restrict parser,
                                                    di_enum_locals_sections_t const *__restrict sections,
                                                    di_debuginfo_compile_unit_t *__restrict cu,
                                                    di_debuginfo_subprogram_t *__restrict sp,
                                                    di_debuginfo_variable_t *__restrict var,
                                                    di_debuginfo_type_t *__restrict type,
                                                    __uintptr_t module_relative_pc);

/* Enumerate all local variables visible at a given source location
 * @return: >= 0: The sum of all invocations of `*callback'.
 * @return: <  0: The first negative return value of `*callback'. */
typedef __ssize_t
(LIBDEBUGINFO_CC *PDEBUGINFO_ENUM_LOCALS)(di_enum_locals_sections_t const *__restrict sectinfo,
                                          __uintptr_t module_relative_pc,
                                          debuginfo_enum_locals_callback_t callback, void *arg);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ssize_t LIBDEBUGINFO_CC
debuginfo_enum_locals(di_enum_locals_sections_t const *__restrict sectinfo,
                      __uintptr_t module_relative_pc,
                      debuginfo_enum_locals_callback_t callback, void *arg);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBDEBUGINFO_DEBUG_INFO_H */
