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
#ifndef _LIBDEBUGINFO_DEBUG_INFO_H
#define _LIBDEBUGINFO_DEBUG_INFO_H 1

#include "api.h"
/**/

#include <hybrid/__unaligned.h>
#include <hybrid/typecore.h>
#include <hybrid/int128.h>

#include <bits/crt/format-printer.h>
#include <bits/types.h>
#include <kos/anno.h>
#include <kos/exec/module.h>

#include <libc/string.h>
#include <libunwind/dwarf.h>

/* Section containers & overlap:
 *
 * unwind_emulator_sections_t: .eh_frame_hdr, .eh_frame, .debug_frame, .debug_addr, .debug_loc, .debug_abbrev, .debug_info
 * di_addr2line_sections_t:                                                                     .debug_abbrev, .debug_info, .debug_str, .debug_line_str, .debug_aranges, .debug_ranges, .debug_line, .strtab, .symtab
 * di_enum_locals_sections_t:                                          .debug_addr, .debug_loc, .debug_abbrev, .debug_info, .debug_str, .debug_line_str, .debug_aranges, .debug_ranges
 * di_debuginfo_cu_parser_sections_t:                                               .debug_loc, .debug_abbrev, .debug_info, .debug_str, .debug_line_str
 * di_string_sections_t:                                                                                                    .debug_str, .debug_line_str
 */



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
#define DEBUGINFO_PRINT_FORMAT_ATTRIBUTE_PREFIX 0x0024 /* Prefix for `__cdecl', `__attribute__((cdecl))', ... */
#define DEBUGINFO_PRINT_FORMAT_ATTRIBUTE_SUFFIX 0x0025 /* ... */
#define DEBUGINFO_PRINT_FORMAT_UNKNOWN_PREFIX   0x0024 /* Prefix for unknown (raw) data */
#define DEBUGINFO_PRINT_FORMAT_UNKNOWN_SUFFIX   0x0025 /* ... */
#define DEBUGINFO_PRINT_FORMAT_CONSTANT_PREFIX  0x0026 /* Prefix for constant names (enums and macros) */
#define DEBUGINFO_PRINT_FORMAT_CONSTANT_SUFFIX  0x0027 /* ... */
#define DEBUGINFO_PRINT_FORMAT_ERROR_PREFIX     0x0028 /* Prefix for data-access error messages (e.g. `<segfault>') */
#define DEBUGINFO_PRINT_FORMAT_ERROR_SUFFIX     0x0029 /* ... */
#define DEBUGINFO_PRINT_FORMAT_TRUEFALSE_PREFIX 0x002a /* Prefix for `true' and `false' */
#define DEBUGINFO_PRINT_FORMAT_TRUEFALSE_SUFFIX 0x002b /* ... */
#define DEBUGINFO_PRINT_FORMAT_NOTES_PREFIX     0x002c /* Prefix for custom annotation notes. */
#define DEBUGINFO_PRINT_FORMAT_NOTES_SUFFIX     0x002d /* ... */
#define DEBUGINFO_PRINT_FORMAT_BADNOTES_PREFIX  0x002e /* Prefix for custom error annotation notes. */
#define DEBUGINFO_PRINT_FORMAT_BADNOTES_SUFFIX  0x002f /* ... */
#define DEBUGINFO_PRINT_FORMAT_ISPREFIX(x) (!((x) & 1))
#define DEBUGINFO_PRINT_FORMAT_ISSUFFIX(x) ((x) & 1)


#ifdef __CC__
__DECL_BEGIN

typedef struct di_debuginfo_component_attrib_struct {
	dwarf_uleb128_t   dica_name; /* Attribute name (one of `DW_AT_*'; e.g. `DW_AT_producer') */
	dwarf_uleb128_t   dica_form; /* Attribute form (one of `DW_FORM_*'; e.g. `DW_FORM_strp') */
} di_debuginfo_component_attrib_t;

typedef struct di_debuginfo_component_struct {
	__UINTPTR_HALF_TYPE__                  dic_tag;         /* Component tag (one of `DW_TAG_*'; e.g. `DW_TAG_compile_unit') */
	__uint8_t                              dic_haschildren; /* `DW_CHILDREN_yes' if follow-up on this entry is a child */
#if __SIZEOF_POINTER__ >= 4
	__uint8_t                            __dic_pad[(sizeof(void *) / 2) - 1]; /* ... */
#endif /* __SIZEOF_POINTER__ >= 4 */
	di_debuginfo_component_attrib_t const *dic_attrib;      /* [1..1] Pointer to the list of (attr_name, attr_form) ULEB pairs
	                                                         *        of this entry. This list is terminated by a pair (0, 0). */
} di_debuginfo_component_t;

typedef struct di_string_sections_struct {
	/* NOTE: The order of members in this struct is important!
	 *       s.a. `Section containers & overlap' in `/kos/include/libdebuginfo/debug_info.h' */
	__byte_t const *dss_debug_str_start;      /* [0..1] `.debug_str' start */
	__byte_t const *dss_debug_str_end;        /* [0..1] `.debug_str' end */
	__byte_t const *dss_debug_line_str_start; /* [0..1] `.debug_str' start */
	__byte_t const *dss_debug_line_str_end;   /* [0..1] `.debug_str' end */
} di_string_sections_t;

typedef struct di_debuginfo_cu_parser_sections_struct {
	/* NOTE: The order of members in this struct is important!
	 *       s.a. `Section containers & overlap' in `/kos/include/libdebuginfo/debug_info.h' */
	__byte_t const *cps_debug_loc_start;      /* [0..1][const] `.debug_loc' start
	                                           * NOTE: When  set equal to `cps_debug_loc_end', location list expression
	                                           *       cannot be used and will appear as though they weren't present at
	                                           *       all. */
	__byte_t const *cps_debug_loc_end;        /* [0..1][const] `.debug_loc' end */
	__byte_t const *cps_debug_abbrev_start;   /* [1..1][const] `.debug_abbrev' start */
	__byte_t const *cps_debug_abbrev_end;     /* [1..1][const] `.debug_abbrev' end */
	__byte_t const *cps_debug_info_start;     /* [0..1][const] `.debug_info' start */
	__byte_t const *cps_debug_info_end;       /* [0..1][const] `.debug_info' end */
	/*BEGIN:compat(di_string_sections_t)*/
	__byte_t const *cps_debug_str_start;      /* [0..1][const] `.debug_str' start
	                                           * NOTE: When set equal to `cps_debug_str_end', strings referring to
	                                           *       this section will be returned  as `???' (3 question  marks) */
	__byte_t const *cps_debug_str_end;        /* [0..1][const] `.debug_str' end */
	__byte_t const *cps_debug_line_str_start; /* [0..1][const] `.debug_line_str' start
	                                           * NOTE: When set equal to `cps_debug_line_str_end', strings referring
	                                           *       to  this section will be returned as `???' (3 question marks) */
	__byte_t const *cps_debug_line_str_end;   /* [0..1][const] `.debug_line_str' end */
	/*END:compat(di_string_sections_t)*/
} di_debuginfo_cu_parser_sections_t;
#define di_debuginfo_cu_parser_sections_as_di_string_sections(self) \
	((di_string_sections_t *)&(self)->cps_debug_str_start)

typedef struct di_debuginfo_cu_abbrev_cache_entry_struct {
	__uintptr_t     ace_code; /* The abbreviation code (or 0 if this cache entry is unused) */
	__byte_t const *ace_data; /* [1..1][valid_if(ace_code)] Abbreviation code data.
	                           * This pointer points into the .debug_info section and should be loaded as:
	                           * >> byte_t const *reader = ace_data;
	                           * >> component.dic_tag         = dwarf_decode_uleb128(&reader);
	                           * >> component.dic_haschildren = *reader++;
	                           * >> component.dic_attrib      = reader; */
} di_debuginfo_cu_abbrev_cache_entry_t;

#ifndef CONFIG_DEBUGINFO_ABBREV_CACHE_MINSIZE
#define CONFIG_DEBUGINFO_ABBREV_CACHE_MINSIZE 16 /* This equates to ~256 (on 32-bit) bytes allocated for the cache. */
#endif /* !CONFIG_DEBUGINFO_ABBREV_CACHE_MINSIZE */
#ifndef CONFIG_DEBUGINFO_ABBREV_CACHE_MAXSIZE
#define CONFIG_DEBUGINFO_ABBREV_CACHE_MAXSIZE 256
#endif /* !CONFIG_DEBUGINFO_ABBREV_CACHE_MAXSIZE */

typedef struct di_debuginfo_cu_abbrev_struct {
	__byte_t const                       *dua_abbrev;     /* [1..1][const] Starting address of debug abbreviations (in .debug_abbrev). */
	di_debuginfo_cu_abbrev_cache_entry_t *dua_cache_list; /* [1..dua_cache_size][owned_if(!= dua_stcache)] Cache vector, or (di_debuginfo_cu_abbrev_cache_entry_t *)-1 if unused. */
	__size_t                              dua_cache_size; /* Allocated (dua_cache_list != dua_stcache) or initialiezd (dua_cache_list == dua_stcache) cache size. */
	__size_t                              dua_cache_next; /* Index to the cache entry that should be overwritten next. */
	di_debuginfo_cu_abbrev_cache_entry_t  dua_stcache[CONFIG_DEBUGINFO_ABBREV_CACHE_MINSIZE]; /* Statically allocated cache. */
} di_debuginfo_cu_abbrev_t;

typedef struct di_debuginfo_cu_simple_parser_struct {
	__byte_t const *dsp_cu_info_end; /* [1..1][const] End address of debug information data (usually in .debug_info). */
	__byte_t const *dsp_cu_info_pos; /* [1..1][>= dup_cu_info_hdr && <= dup_base.dsp_cu_info_pos] Current position in debug information data (usually in .debug_info). */
	__uint8_t       dsp_ptrsize;     /* Pointer size (4 in 32-bit DWARF; 8 in 64-bit DWARF). */
	__uint8_t       dsp_addrsize;    /* Address size */
	__uint16_t      dsp_version;     /* DWARF version */
} di_debuginfo_cu_simple_parser_t;

typedef struct di_debuginfo_cu_parser_struct
#ifdef __cplusplus
    : di_debuginfo_cu_simple_parser_struct
#endif /* __cplusplus */
{
#ifndef __cplusplus
	di_debuginfo_cu_simple_parser_t          dup_base;        /* Underlying simple parser. */
#define _di_debuginfo_cu_parser_struct_asbase(x) &(x)->dup_base
#define _di_debuginfo_cu_parser_struct_base_     dup_base.
#else /* !__cplusplus */
#define _di_debuginfo_cu_parser_struct_asbase(x) x
#define _di_debuginfo_cu_parser_struct_base_     /* nothing */
#endif /* __cplusplus */
	di_debuginfo_cu_parser_sections_t const *dup_sections;    /* [1..1][const] Section information. */
	di_debuginfo_cu_abbrev_t                *dup_cu_abbrev;   /* [1..1][const] Abbreviation code controller. */
	di_debuginfo_component_t                 dup_comp;        /* The component currently being parsed. */
	__uintptr_t                              dup_child_depth; /* The child-recursion-depth of `dp_comp' */
	__byte_t const                          *dup_cu_info_hdr; /* [1..1][const] Address of the debug information header (in .debug_info). */
} di_debuginfo_cu_parser_t;

#ifndef __di_debuginfo_location_t_defined
#define __di_debuginfo_location_t_defined
/* NOTE: The user-interface API for this type is exported
 *       by  `libunwind',  rather  than   `libdebuginfo'! */
typedef struct di_debuginfo_location_struct {
	__byte_t const *l_expr;  /* [0..1] Pointer to a CFI expression (for use with `unwind_emulator_exec') for the pointed-to expression. */
	__byte_t const *l_llist; /* [0..1] Pointer to a CFI location list (points into the `.debug_loc' section). */
} di_debuginfo_location_t;
#endif /* !__di_debuginfo_location_t_defined */

/* Parse and enumerate the attributes of the current component.
 * NOTE: This must be done _exactly_ once before the next call
 *       to one of `debuginfo_cu_parser_next*'
 * >> di_debuginfo_cu_parser_t parser;
 * >> while (debuginfo_cu_parser_loadunit(..., &parser) == DEBUG_INFO_ERROR_SUCCESS) {
 * >>     do {
 * >>         di_debuginfo_component_attrib_t attr;
 * >>         DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, &parser) {
 * >>             ...
 * >>         }
 * >>     } while (debuginfo_cu_parser_next(&parser) == DEBUG_INFO_ERROR_SUCCESS);
 * >> }
 */
#define DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, self)                                         \
	for (__byte_t const *_attr_reader = (__byte_t const *)(self)->dup_comp.dic_attrib;      \
	     (self)->_di_debuginfo_cu_parser_struct_base_ dsp_cu_info_pos <                     \
	     (self)->_di_debuginfo_cu_parser_struct_base_ dsp_cu_info_end;                      \
	     debuginfo_cu_parser_skipform(_di_debuginfo_cu_parser_struct_asbase(self),          \
	                                  (attr).dica_form, (__byte_t const **)&_attr_reader))  \
		if (((attr).dica_name = dwarf_decode_uleb128((__byte_t const **)&_attr_reader),     \
		     (attr).dica_form = dwarf_decode_uleb128((__byte_t const **)&_attr_reader), 0)) \
			;                                                                               \
		else if (!(attr).dica_name && !(attr).dica_form)                                    \
			break;                                                                          \
		else

/* Helper to break out of a `DI_DEBUGINFO_CU_PARSER_EACHATTR()'
 * loop, whilst  keep the  parser state  consistent and  valid. */
#define DI_DEBUGINFO_CU_PARSER_EACHATTR_BREAK(attr, self)                                     \
	do {                                                                                      \
		for (;;) {                                                                            \
			debuginfo_cu_parser_skipform(_di_debuginfo_cu_parser_struct_asbase(self),         \
			                             (attr).dica_form, (__byte_t const **)&_attr_reader); \
			if ((self)->_di_debuginfo_cu_parser_struct_base_ dsp_cu_info_pos >=               \
			    (self)->_di_debuginfo_cu_parser_struct_base_ dsp_cu_info_end)                 \
				break;                                                                        \
			(attr).dica_name = dwarf_decode_uleb128((__byte_t const **)&_attr_reader);        \
			(attr).dica_form = dwarf_decode_uleb128((__byte_t const **)&_attr_reader);        \
			if (!(attr).dica_name && !(attr).dica_form)                                       \
				break;                                                                        \
		}                                                                                     \
	}	__WHILE0


/* Given  a pointer to the start of a  debug_info CU (or a pointer to the start
 * of the .debug_info section), as well as the start & end of the .debug_abbrev
 * section, initialize the  given debuginfo CU  parser structure `result',  and
 * advance `*pdebug_info_reader' to the start of the next unit.
 * NOTE: Upon success (return == DEBUG_INFO_ERROR_SUCCESS), the caller is responsible for
 *       finalizing the given `abbrev' through use of `debuginfo_cu_abbrev_fini(abbrev)',
 *       once the associated parser `result' is no longer being used.
 * @param: first_component_pointer: A pointer to the first component to load, or `NULL'
 *                                  to simply load  the first  component following  the
 *                                  start of the associated CU descriptor.
 * @return: DEBUG_INFO_ERROR_SUCCESS: ...
 * @return: DEBUG_INFO_ERROR_NOFRAME: All units have been loaded.
 * @return: DEBUG_INFO_ERROR_CORRUPT: ... */
typedef __ATTR_NONNULL_T((1, 2, 3, 4, 5)) unsigned int
__NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_LOADUNIT)(__byte_t const **__restrict pdebug_info_reader,
                                                                __byte_t const *__restrict debug_info_end,
                                                                di_debuginfo_cu_parser_sections_t const *__restrict sectinfo,
                                                                di_debuginfo_cu_parser_t *__restrict result,
                                                                di_debuginfo_cu_abbrev_t *__restrict abbrev,
                                                                __byte_t const *first_component_pointer);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 2, 3, 4, 5)) unsigned int
__NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_loadunit)(__byte_t const **__restrict pdebug_info_reader,
                                                            __byte_t const *__restrict debug_info_end,
                                                            di_debuginfo_cu_parser_sections_t const *__restrict sectinfo,
                                                            di_debuginfo_cu_parser_t *__restrict result,
                                                            di_debuginfo_cu_abbrev_t *__restrict abbrev,
                                                            __byte_t const *first_component_pointer);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */



/* Finalize the given abbreviation code controller. */
typedef __ATTR_NONNULL_T((1)) void
__NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_ABBREV_FINI)(di_debuginfo_cu_abbrev_t *__restrict self);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_abbrev_fini)(di_debuginfo_cu_abbrev_t *__restrict self);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */



/* Skip data associated with the given attribute form.
 * @param: form: One of `DW_FORM_*' */
typedef __ATTR_NONNULL_T((1, 3)) void
__NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_SKIPFORM)(di_debuginfo_cu_simple_parser_t *__restrict self,
                                                                dwarf_uleb128_t form,
                                                                __byte_t const **__restrict p_attr_reader);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 3)) void
__NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_skipform)(di_debuginfo_cu_simple_parser_t *__restrict self,
                                                            dwarf_uleb128_t form,
                                                            __byte_t const **__restrict p_attr_reader);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */

/* Start a new component.
 * NOTE: Prior to calling  of these  functions, you may  assign `self->dsp_cu_info_pos'  to
 *       the starting address of  the next component  to-be read. -  Valid values for  this
 *       are usually returned by `debuginfo_cu_parser_getref()',  and can be found in  some
 *       of the structures initialized by the `debuginfo_cu_parser_loadattr_*()' functions.
 * @return: true: ...
 * @return: false: [debuginfo_cu_parser_next] All components have been parsed.
 * @return: false: [*] The next component doesn't exist, or isn't a child/sibling/parent. */
typedef __ATTR_NONNULL_T((1)) __BOOL __NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_NEXT)(di_debuginfo_cu_parser_t *__restrict self);
typedef __ATTR_NONNULL_T((1)) __BOOL __NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_NEXTCHILD)(di_debuginfo_cu_parser_t *__restrict self);
typedef __ATTR_NONNULL_T((1)) __BOOL __NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_NEXTSIBLING)(di_debuginfo_cu_parser_t *__restrict self);
typedef __ATTR_NONNULL_T((1)) __BOOL __NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_NEXTPARENT)(di_debuginfo_cu_parser_t *__restrict self);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1)) __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_next)(di_debuginfo_cu_parser_t *__restrict self);
LIBDEBUGINFO_DECL __ATTR_NONNULL((1)) __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_nextchild)(di_debuginfo_cu_parser_t *__restrict self);
LIBDEBUGINFO_DECL __ATTR_NONNULL((1)) __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_nextsibling)(di_debuginfo_cu_parser_t *__restrict self);
LIBDEBUGINFO_DECL __ATTR_NONNULL((1)) __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_nextparent)(di_debuginfo_cu_parser_t *__restrict self);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */

/* Same as `libdi_debuginfo_cu_parser_next()', but store a pointer to the
 * debug information start location of  the next componet within  `*pdip' */
typedef __ATTR_NONNULL_T((1, 2)) __BOOL
__NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_NEXT_WITH_DIP)(di_debuginfo_cu_parser_t *__restrict self,
                                                                     __byte_t const **__restrict pdip);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 2)) __BOOL
__NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_next_with_dip)(di_debuginfo_cu_parser_t *__restrict self,
                                                                 __byte_t const **__restrict pdip);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */


/* Skip the attributes  of the  current component  (must be  called if  not
 * parsed explicitly prior to the next call to `debuginfo_cu_parser_next*') */
typedef __ATTR_NONNULL_T((1)) void
__NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_SKIPATTR)(di_debuginfo_cu_parser_t *__restrict self);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_skipattr)(di_debuginfo_cu_parser_t *__restrict self);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */

typedef struct di_debuginfo_block_struct {
	__byte_t const *b_addr; /* [0..b_size] Block base-pointer */
	__size_t        b_size; /* Block length (in bytes) */
} di_debuginfo_block_t;

/* Load the current debug information as an attribute encoded  as
 * `form' into a storage class matching the given result-operand.
 *  - debuginfo_cu_parser_getstring(): DW_FORM_strp, DW_FORM_string, DW_FORM_line_strp, DW_FORM_strp_sup, DW_FORM_strx, DW_FORM_strx1, DW_FORM_strx2, DW_FORM_strx3, DW_FORM_strx4
 *  - debuginfo_cu_parser_getaddr():   DW_FORM_addr, DW_FORM_addrx, DW_FORM_addrx1, DW_FORM_addrx2, DW_FORM_addrx3, DW_FORM_addrx4
 *  - debuginfo_cu_parser_getconst():  DW_FORM_data1, DW_FORM_data2, DW_FORM_data4, DW_FORM_data8, DW_FORM_sdata, DW_FORM_udata, DW_FORM_sec_offset, DW_FORM_implicit_const
 *  - debuginfo_cu_parser_getflag():   DW_FORM_flag, DW_FORM_flag_present
 *  - debuginfo_cu_parser_getref():    DW_FORM_ref_addr, DW_FORM_ref1, DW_FORM_ref2, DW_FORM_ref4, DW_FORM_ref8, DW_FORM_ref_sig8, DW_FORM_ref_udata, DW_FORM_ref_sup4, DW_FORM_ref_sig8, DW_FORM_ref_sup8
 *  - debuginfo_cu_parser_getexpr():   DW_FORM_exprloc
 *  - debuginfo_cu_parser_getblock():  DW_FORM_block, DW_FORM_block1, DW_FORM_block2, DW_FORM_block4 */
typedef __ATTR_NONNULL_T((1, 3)) __BOOL __NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_GETSTRING)(di_debuginfo_cu_parser_t const *__restrict self, __uintptr_t form, char const **__restrict presult);
typedef __ATTR_NONNULL_T((1, 3)) __BOOL __NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_GETSTRING_EX)(di_debuginfo_cu_simple_parser_t const *__restrict self, __uintptr_t form, char const **__restrict presult, di_string_sections_t const *__restrict sections);
typedef __ATTR_NONNULL_T((1, 3)) __BOOL __NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_GETADDR)(di_debuginfo_cu_simple_parser_t const *__restrict self, __uintptr_t form, __uintptr_t *__restrict presult);
typedef __ATTR_NONNULL_T((1, 3)) __BOOL __NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_GETCONST)(di_debuginfo_cu_simple_parser_t const *__restrict self, __uintptr_t form, __uintptr_t *__restrict presult, __byte_t const *__restrict attr_reader);
typedef __ATTR_NONNULL_T((1, 3)) __BOOL __NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_GETCONST64)(di_debuginfo_cu_simple_parser_t const *__restrict self, __uintptr_t form, __uintptr_t *__restrict presult, __byte_t const *__restrict attr_reader);
typedef __ATTR_NONNULL_T((1, 3)) __BOOL __NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_GETCONST128)(di_debuginfo_cu_simple_parser_t const *__restrict self, __uintptr_t form, __hybrid_uint128_t *__restrict presult, __byte_t const *__restrict attr_reader);
typedef __ATTR_NONNULL_T((1, 3)) __BOOL __NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_GETFLAG)(di_debuginfo_cu_simple_parser_t const *__restrict self, __uintptr_t form, __BOOL *__restrict presult);
typedef __ATTR_NONNULL_T((1, 3)) __BOOL __NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_GETREF)(di_debuginfo_cu_parser_t const *__restrict self, __uintptr_t form, __byte_t const **__restrict presult);
typedef __ATTR_NONNULL_T((1, 3)) __BOOL __NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_GETEXPR)(di_debuginfo_cu_parser_t const *__restrict self, __uintptr_t form, di_debuginfo_location_t *__restrict result);
typedef __ATTR_NONNULL_T((1, 3)) __BOOL __NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_GETBLOCK)(di_debuginfo_cu_simple_parser_t const *__restrict self, __uintptr_t form, di_debuginfo_block_t *__restrict result);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_getstring)(di_debuginfo_cu_parser_t const *__restrict self, __uintptr_t form, char const **__restrict presult);
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_getstring_ex)(di_debuginfo_cu_simple_parser_t const *__restrict self, __uintptr_t form, char const **__restrict presult, di_string_sections_t const *__restrict sections);
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_getaddr)(di_debuginfo_cu_simple_parser_t const *__restrict self, __uintptr_t form, __uintptr_t *__restrict presult);
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_getconst)(di_debuginfo_cu_simple_parser_t const *__restrict self, __uintptr_t form, __uintptr_t *__restrict presult, __byte_t const *__restrict attr_reader);
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_getconst64)(di_debuginfo_cu_simple_parser_t const *__restrict self, __uintptr_t form, __uint64_t *__restrict presult, __byte_t const *__restrict attr_reader);
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_getconst128)(di_debuginfo_cu_simple_parser_t const *__restrict self, __uintptr_t form, __hybrid_uint128_t *__restrict presult, __byte_t const *__restrict attr_reader);
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_getflag)(di_debuginfo_cu_simple_parser_t const *__restrict self, __uintptr_t form, __BOOL *__restrict presult);
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_getref)(di_debuginfo_cu_parser_t const *__restrict self, __uintptr_t form, __byte_t const **__restrict presult);
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_getexpr)(di_debuginfo_cu_parser_t const *__restrict self, __uintptr_t form, di_debuginfo_location_t *__restrict result);
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 3)) __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_getblock)(di_debuginfo_cu_simple_parser_t const *__restrict self, __uintptr_t form, di_debuginfo_block_t *__restrict result);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */



typedef struct {
	__uintptr_t r_ranges_offset; /* Offset to into .debug_ranges to a list of exact ranges, or `(uintptr_t)-1' if unused. */
	__uintptr_t r_startpc;       /* Starting program counter position (or `r_ranges != (uintptr_t)-1 ? 0 : (uintptr_t)-1' if unknown). */
	__uintptr_t r_endpc;         /* Ending program counter position (or `0' if unknown). */
} di_debuginfo_ranges_t;
#define DI_DEBUGINFO_RANGES_ISSINGLERANGE(x) ((x)->r_ranges_offset == (__uintptr_t)-1)

typedef struct {
	di_debuginfo_ranges_t const *ri_ranges;   /* [1..1][const] The underlying range object. */
	__byte_t const              *ri_pos;      /* [1..1] Current iterator position (or >= ri_end if the iterator was exhausted) */
	__byte_t const              *ri_end;      /* [1..1][const] Iterator end position */
	__uintptr_t                  ri_initbase; /* Initial base */
	__uint8_t                    ri_addrsize; /* [const] Address size. */
} di_debuginfo_ranges_iterator_t;

/* Initialize an iterator for enumerating ranges stored within a given debug_info range selector.
 * >> uintptr_t start_pc, end_pc;
 * >> di_debuginfo_ranges_iterator_t iter;
 * >> di_debuginfo_ranges_iterator_init(&iter, ...);
 * >> while (di_debuginfo_ranges_iterator_next(&iter, &start_pc, &end_pc)) {
 * >>     ...
 * >> }
 * @param: debug_ranges_start: Starting address of the `.debug_ranges' section.
 * @param: debug_ranges_end:   End address of the `.debug_ranges' section. */
typedef __ATTR_NONNULL_T((1, 2, 3, 5, 6)) void
__NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_RANGES_ITERATOR_INIT)(di_debuginfo_ranges_iterator_t *__restrict self,
                                                                  di_debuginfo_ranges_t const *__restrict ranges,
                                                                  di_debuginfo_cu_parser_t const *__restrict parser,
                                                                  __uintptr_t cu_base,
                                                                  __byte_t const *__restrict debug_ranges_start,
                                                                  __byte_t const *__restrict debug_ranges_end);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 2, 3, 5, 6)) void
__NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_ranges_iterator_init)(di_debuginfo_ranges_iterator_t *__restrict self,
                                                              di_debuginfo_ranges_t const *__restrict ranges,
                                                              di_debuginfo_cu_parser_t const *__restrict parser,
                                                              __uintptr_t cu_base,
                                                              __byte_t const *__restrict debug_ranges_start,
                                                              __byte_t const *__restrict debug_ranges_end);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */

/* Yield the next range accessible through a given debug-ranges iterator. */
typedef __ATTR_NONNULL_T((1, 2, 3)) __BOOL
__NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_RANGES_ITERATOR_NEXT)(di_debuginfo_ranges_iterator_t *__restrict self,
                                                                  __uintptr_t *__restrict pmodule_relative_start_pc,
                                                                  __uintptr_t *__restrict pmodule_relative_end_pc);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 2, 3)) __BOOL
__NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_ranges_iterator_next)(di_debuginfo_ranges_iterator_t *__restrict self,
                                                              __uintptr_t *__restrict pmodule_relative_start_pc,
                                                              __uintptr_t *__restrict pmodule_relative_end_pc);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */

/* Check if a given `module_relative_pc' is apart of the given range selector.
 * @param: self: The ranges object to query for `module_relative_pc' */
typedef __ATTR_NONNULL_T((1, 2, 5, 6)) unsigned int
__NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_RANGES_CONTAINS)(di_debuginfo_ranges_t const *__restrict self,
                                                             di_debuginfo_cu_parser_t const *__restrict parser,
                                                             __uintptr_t cu_base,
                                                             __uintptr_t module_relative_pc,
                                                             __byte_t const *__restrict debug_ranges_start,
                                                             __byte_t const *__restrict debug_ranges_end);
typedef __ATTR_NONNULL_T((1, 2, 5, 6, 7, 8)) unsigned int
__NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_RANGES_CONTAINS_EX)(di_debuginfo_ranges_t const *__restrict self,
                                                                di_debuginfo_cu_parser_t const *__restrict parser,
                                                                __uintptr_t cu_base,
                                                                __uintptr_t module_relative_pc,
                                                                __byte_t const *__restrict debug_ranges_start,
                                                                __byte_t const *__restrict debug_ranges_end,
                                                                __uintptr_t *__restrict poverlap_start,
                                                                __uintptr_t *__restrict poverlap_end);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 2, 5, 6)) unsigned int
__NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_ranges_contains)(di_debuginfo_ranges_t const *__restrict self,
                                                         di_debuginfo_cu_parser_t const *__restrict parser,
                                                         __uintptr_t cu_base,
                                                         __uintptr_t module_relative_pc,
                                                         __byte_t const *__restrict debug_ranges_start,
                                                         __byte_t const *__restrict debug_ranges_end);
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 2, 5, 6, 7, 8)) unsigned int
__NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_ranges_contains_ex)(di_debuginfo_ranges_t const *__restrict self,
                                                            di_debuginfo_cu_parser_t const *__restrict parser,
                                                            __uintptr_t cu_base,
                                                            __uintptr_t module_relative_pc,
                                                            __byte_t const *__restrict debug_ranges_start,
                                                            __byte_t const *__restrict debug_ranges_end,
                                                            __uintptr_t *__restrict poverlap_start,
                                                            __uintptr_t *__restrict poverlap_end);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */









/* Helper types/functions for loading specific debug information tags. */
typedef struct di_debuginfo_compile_unit_struct {
	/* For `DW_TAG_compile_unit'
	 * NOTE: This TAG is followed by a tree/sequence of child-nodes containing information
	 *       about  the  individual  components  that  make  up  this  compilation   unit.
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
	di_debuginfo_ranges_t cu_ranges;    /* List of debug ranges associated with addresses apart of this CU. */
	__uintptr_t           cu_addr_base; /* Base address for `DW_OP_addrx' offsets (s.a. `DW_AT_addr_base') */
	__uintptr_t           cu_stmt_list; /* Offset into `.debug_line' (to-be used with `debugline_loadunit')
	                                     * to this CU's address-to-line data blob.
	                                     * If unknown,  set to  `(__uintptr_t)-1' (but  always assume  undefined
	                                     * if this offset points past- or at the end of the .debug_line section) */
	char const           *cu_name;      /* [0..1] Name of the compilation unit. */
	char const           *cu_comp_dir;  /* [0..1] Path to  the compiler  base  directory (prepended  before  filenames,
	                                     * this is essentially the getcwd() of the compiler when the CU was assembled). */
} di_debuginfo_compile_unit_t;
#define di_debuginfo_compile_unit_as_simple(self) ((di_debuginfo_compile_unit_simple_t *)&(self)->cu_ranges)

typedef struct di_debuginfo_compile_unit_simple_struct {
	/* For `DW_TAG_compile_unit' (simplified) */
	di_debuginfo_ranges_t cu_ranges;    /* List of debug ranges associated with addresses apart of this CU. */
	__uintptr_t           cu_addr_base; /* Base address for `DW_OP_addrx' offsets (s.a. `DW_AT_addr_base') */
} di_debuginfo_compile_unit_simple_t;

typedef struct di_debuginfo_subprogram_struct {
	/* For `DW_TAG_subprogram' */
#define DW_SUBPROGRAM_FNORMAL   0x00000000 /* Normal program flags. */
#define DW_SUBPROGRAM_FEXTERN   0x00000001 /* The function is either INTERN or PUBLIC */
#define DW_SUBPROGRAM_FNORETURN 0x00000002 /* The function is either NORETURN */
	__uintptr_t             sp_flags;        /* Function flags (Set of `DW_SUBPROGRAM_F*') */
	char const             *sp_name;         /* [0..1] Name of the function. */
	char const             *sp_rawname;      /* [0..1] Raw (linkage) name of the function. */
	di_debuginfo_location_t sp_frame_base;   /* Frame base expression. */
	di_debuginfo_ranges_t   sp_ranges;       /* Program counter ranges. */
	__uintptr_t             sp_decl_file;    /* Declaring file index (used with the addr2line program pointed
	                                          * to by the associated CU's `cu_stmt_list') (or 0 if undefined) */
	__uintptr_t             sp_decl_line;    /* Declaring line number (or 0 if undefined) */
	__uintptr_t             sp_decl_column;  /* Declaring column offset (or 0 if undefined) */
} di_debuginfo_subprogram_t;

typedef struct di_debuginfo_inlined_subroutine_struct {
	/* For `DW_TAG_inlined_subroutine' */
	__byte_t const       *is_subprogram;    /* [0..1] Pointer to the debug_info for the function's declaration (i.e. its `DW_TAG_subprogram').
	                                         * To load this structure, do the following:
	                                         * >> if ((...).is_subprogram != NULL) {
	                                         * >>     parser.dsp_cu_info_pos = (...).is_subprogram;
	                                         * >>     debuginfo_cu_parser_next(&parser);
	                                         * >>     if (parser.dup_comp.dic_tag == DW_TAG_subprogram) {
	                                         * >>         di_debuginfo_subprogram_t prog;
	                                         * >>         if (debuginfo_cu_parser_loadattr_subprogram(&parser, &prog) == DEBUG_INFO_ERROR_SUCCESS) {
	                                         * >>             // Success
	                                         * >>             ...
	                                         * >>         }
	                                         * >>     }
	                                         * >> } */
	di_debuginfo_ranges_t is_ranges;        /* Program counter ranges. */
	__uintptr_t           is_call_file;     /* Call source file index (used with the addr2line program pointed
	                                         * to by the associated CU's  `cu_stmt_list') (or 0 if  undefined) */
	__uintptr_t           is_call_line;     /* Call source line number (or 0 if undefined) */
	__uintptr_t           is_call_column;   /* Call source column offset (or 0 if undefined) */
} di_debuginfo_inlined_subroutine_t;

typedef struct di_debuginfo_lexical_block_struct {
	/* For `DW_TAG_lexical_block' / `DW_TAG_try_block' / `DW_TAG_catch_block' */
	di_debuginfo_ranges_t lb_ranges;        /* Program counter ranges. */
} di_debuginfo_lexical_block_t;

typedef struct di_debuginfo_type_struct {
	/* For `DW_TAG_*_type' */
	char const           *t_name;          /* [0..1] Name of the type. */
	char const           *t_rawname;       /* [0..1] Raw (linkage) name of the type. */
	__uintptr_t           t_decl_file;     /* Declaring file index (used with the addr2line program pointed
	                                        * to by the associated CU's `cu_stmt_list') (or 0 if undefined) */
	__uintptr_t           t_decl_line;     /* Declaring line number (or 0 if undefined) */
	__uintptr_t           t_decl_column;   /* Declaring column offset (or 0 if undefined) */
	__uintptr_t           t_sizeof;        /* Size of this type (in bytes) (or 0 if undefined) */
	__byte_t const       *t_type;          /* [0..1] Underlying type (e.g. array element type). */
	__uintptr_t           t_encoding;      /* Value of `DW_AT_encoding' (one of `DW_ATE_*', or 0 if undefined) */
} di_debuginfo_type_t;


typedef struct di_debuginfo_member_struct {
	/* For `DW_TAG_member' */
	__byte_t const       *m_type;           /* [0..1] Pointer  to  the  debug_info  for  the  member's  type  (which  is  one  of   `DW_TAG_*_type').
	                                         * To load this structure, create a copy of your parser and assign this pointer to it's `dsp_cu_info_pos'
	                                         * field. Afterwards, call `debuginfo_cu_parser_next()' to load the pointed-to component. */
	char const           *m_name;           /* [0..1] Name of the member. */
	__uintptr_t           m_decl_file;      /* Declaring file index (used with the addr2line program pointed
	                                         * to by the associated CU's `cu_stmt_list') (or 0 if undefined) */
	__uintptr_t           m_decl_line;      /* Declaring line number (or 0 if undefined) */
	__uintptr_t           m_decl_column;    /* Declaring column offset (or 0 if undefined) */
	__uintptr_t           m_offset;         /* offsetof() this member (or (uintptr_t)-1 if undefined) */
	__uintptr_t           m_bit_size;       /* Number of bits apart of a bit-field (or `0' if this isn't a bit-field) */
	__uintptr_t           m_bit_offset;     /* Number of bits to the left of the leftmost (most significant) bit of the bit field value. */
} di_debuginfo_member_t;

typedef struct di_debuginfo_variable_struct {
	/* For `DW_TAG_variable' / `DW_TAG_formal_parameter' */
	__byte_t const         *v_type;           /* [0..1] Type of this variable. */
	di_debuginfo_location_t v_location;       /* CFI expression to decode the storage location of this variable. */
	char const             *v_name;           /* [0..1] Name of the variable. */
	char const             *v_rawname;        /* [0..1] Raw (linkage) name of the variable. */
	__uintptr_t             v_decl_file;      /* Declaring file index (used with the addr2line program pointed
	                                           * to by the associated CU's `cu_stmt_list') (or 0 if undefined) */
	__uintptr_t             v_decl_line;      /* Declaring line number (or 0 if undefined) */
	__uintptr_t             v_decl_column;    /* Declaring column offset (or 0 if undefined) */
} di_debuginfo_variable_t;

/* Load attributes specific to a certain component:
 *   - debuginfo_cu_parser_loadattr_compile_unit():        DW_TAG_compile_unit
 *   - debuginfo_cu_parser_loadattr_compile_unit_simple(): DW_TAG_compile_unit
 *   - debuginfo_cu_parser_loadattr_subprogram():          DW_TAG_subprogram
 *   - debuginfo_cu_parser_loadattr_inlined_subroutine():  DW_TAG_inlined_subroutine
 *   - debuginfo_cu_parser_loadattr_lexical_block():       DW_TAG_lexical_block, DW_TAG_try_block, DW_TAG_catch_block
 *   - debuginfo_cu_parser_loadattr_type():                DW_TAG_*_type
 *   - debuginfo_cu_parser_loadattr_member():              DW_TAG_member
 *   - debuginfo_cu_parser_loadattr_variable():            DW_TAG_variable, DW_TAG_formal_parameter
 * @return: true:  Successfully loaded the component attributes.
 * @return: false: Corrupted/incomplete attributes. */
typedef __ATTR_NONNULL_T((1, 2)) __BOOL __NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_LOADATTR_COMPILE_UNIT)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_compile_unit_t *__restrict result);
typedef __ATTR_NONNULL_T((1, 2)) __BOOL __NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_LOADATTR_COMPILE_UNIT_SIMPLE)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_compile_unit_simple_t *__restrict result);
typedef __ATTR_NONNULL_T((1, 2)) __BOOL __NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_LOADATTR_SUBPROGRAM)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_subprogram_t *__restrict result);
typedef __ATTR_NONNULL_T((1, 2)) __BOOL __NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_LOADATTR_INLINED_SUBROUTINE)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_inlined_subroutine_t *__restrict result);
typedef __ATTR_NONNULL_T((1, 2)) __BOOL __NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_LOADATTR_LEXICAL_BLOCK)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_lexical_block_t *__restrict result);
typedef __ATTR_NONNULL_T((1, 2)) __BOOL __NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_LOADATTR_TYPE)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_type_t *__restrict result);
typedef __ATTR_NONNULL_T((1, 2)) __BOOL __NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_LOADATTR_MEMBER)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_member_t *__restrict result);
typedef __ATTR_NONNULL_T((1, 2)) __BOOL __NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGINFO_CU_PARSER_LOADATTR_VARIABLE)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_variable_t *__restrict result);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 2)) __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_loadattr_compile_unit)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_compile_unit_t *__restrict result);
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 2)) __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_loadattr_compile_unit_simple)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_compile_unit_simple_t *__restrict result);
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 2)) __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_loadattr_subprogram)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_subprogram_t *__restrict result);
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 2)) __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_loadattr_inlined_subroutine)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_inlined_subroutine_t *__restrict result);
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 2)) __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_loadattr_lexical_block)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_lexical_block_t *__restrict result);
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 2)) __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_loadattr_type)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_type_t *__restrict result);
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 2)) __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_loadattr_member)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_member_t *__restrict result);
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 2)) __BOOL __NOTHROW_NCX(LIBDEBUGINFO_CC debuginfo_cu_parser_loadattr_variable)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_variable_t *__restrict result);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */



/* Print prefix/suffix strings for various syntax components.
 *  -> Intended for encoding ANSI-TTY color codes in order to allow for syntax highlighting
 * @param: format_option: The format string being requested (one of `DEBUGINFO_PRINT_FORMAT_*')
 * @return: * :  The sum of return values from calls to `*printer', or
 *               a negative value if an error occurred while printing. */
typedef __ATTR_NONNULL_T((2)) __ssize_t
(LIBDEBUGINFO_CC *debuginfo_print_format_t)(void *format_arg, __pformatprinter printer,
                                            void *arg, unsigned int format_option);


/* Print the C/C++-like representation of a given value, given DWARF debug information
 * about  its typing, where `parser' must have been  set up to have already loaded the
 * given `type' component for the given data blob:
 * >> di_debuginfo_variable_t var;
 * >> ... // Load `var'
 * >> {
 * >>     di_debuginfo_cu_parser_t pp = parser;
 * >>     di_debuginfo_type_t typ;
 * >>     void *buffer;
 * >>
 * >>     // Load type information for the variable.
 * >>     pp.dsp_cu_info_pos = var.v_type;
 * >>     debuginfo_cu_parser_loadattr_type(&pp, &typ);
 * >>
 * >>     // Load the value of this variable.
 * >>     buffer = malloca(typ.t_sizeof);
 * >>     size_t num_written_bits;
 * >>     debuginfo_location_getvalue(&var.v_location,
 * >>                                 <sections>,
 * >>                                 &<get_register>,
 * >>                                 &<registers>,
 * >>                                 &<cu>,
 * >>                                 module_relative_pc,
 * >>                                 buffer,
 * >>                                 typ.t_sizeof,
 * >>                                 &num_written_bits,
 * >>                                 &<sp>->sp_frame_base,
 * >>                                 NULL,
 * >>                                 parser->_di_debuginfo_cu_parser_struct_base_ dsp_addrsize,
 * >>                                 parser->_di_debuginfo_cu_parser_struct_base_ dsp_ptrsize);
 * >>
 * >>     // Print a representation of the variable, and its data.
 * >>     debuginfo_print_value(printer, arg, &pp, &type, v.v_name, buffer, typ.t_sizeof);
 * >> }
 * @param: varname: Name of the value (when NULL, print as a cast-like expression;
 *                  otherwise, print as an declaration)
 * @param: flags:   Set of `DEBUGINFO_PRINT_VALUE_F*' */
typedef __ATTR_NONNULL_T((1, 3, 4, 6)) __ssize_t
(LIBDEBUGINFO_CC *PDEBUGINFO_PRINT_VALUE)(__pformatprinter printer, void *arg,
                                          di_debuginfo_cu_parser_t const *__restrict parser,
                                          di_debuginfo_type_t const *__restrict type,
                                          char const *varname, void const *__restrict data,
                                          __size_t datasize, __size_t newline_indentation,
                                          debuginfo_print_format_t format_printer,
                                          void *format_arg, unsigned int flags);
typedef __ATTR_NONNULL_T((1, 3, 4)) __ssize_t
(LIBDEBUGINFO_CC *PDEBUGINFO_PRINT_TYPENAME)(__pformatprinter printer, void *arg,
                                             di_debuginfo_cu_parser_t const *__restrict parser,
                                             di_debuginfo_type_t const *__restrict type,
                                             char const *varname,
                                             debuginfo_print_format_t format_printer,
                                             void *format_arg);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 3, 4, 6)) __ssize_t LIBDEBUGINFO_CC
debuginfo_print_value(__pformatprinter printer, void *arg,
                      di_debuginfo_cu_parser_t const *__restrict parser,
                      di_debuginfo_type_t const *__restrict type,
                      char const *varname, void const *__restrict data,
                      __size_t datasize, __size_t newline_indentation,
                      debuginfo_print_format_t format_printer,
                      void *format_arg, unsigned int flags);
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 3, 4)) __ssize_t LIBDEBUGINFO_CC
debuginfo_print_typename(__pformatprinter printer, void *arg,
                         di_debuginfo_cu_parser_t const *__restrict parser,
                         di_debuginfo_type_t const *__restrict type,
                         char const *varname,
                         debuginfo_print_format_t format_printer,
                         void *format_arg);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */

#define DEBUGINFO_PRINT_VALUE_FNORMAL  0x0000
#define DEBUGINFO_PRINT_VALUE_FCASTALL 0x0001 /* Include explicit type casts for all expressions */




typedef struct di_enum_locals_sections_struct {
	/* NOTE: The order of members in this struct is important!
	 *       s.a. `Section containers & overlap' in `/kos/include/libdebuginfo/debug_info.h' */
	__byte_t const *el_debug_addr_start;     /* [0..1] `.debug_addr' start */
	__byte_t const *el_debug_addr_end;       /* [0..1] `.debug_addr' end */
	/*BEGIN:compat(di_debuginfo_cu_parser_sections_t)*/
	__byte_t const *el_debug_loc_start;      /* [0..1] `.debug_loc' start */
	__byte_t const *el_debug_loc_end;        /* [0..1] `.debug_loc' end */
	__byte_t const *el_debug_abbrev_start;   /* [0..1] `.debug_abbrev' start */
	__byte_t const *el_debug_abbrev_end;     /* [0..1] `.debug_abbrev' end */
	__byte_t const *el_debug_info_start;     /* [0..1] `.debug_info' start */
	__byte_t const *el_debug_info_end;       /* [0..1] `.debug_info' end */
	/*BEGIN:compat(di_string_sections_t)*/
	__byte_t const *el_debug_str_start;      /* [0..1] `.debug_str' start */
	__byte_t const *el_debug_str_end;        /* [0..1] `.debug_str' end */
	__byte_t const *el_debug_line_str_start; /* [0..1] `.debug_str' start */
	__byte_t const *el_debug_line_str_end;   /* [0..1] `.debug_str' end */
	/*END:compat(di_string_sections_t)*/
	/*END:compat(di_debuginfo_cu_parser_sections_t)*/
	__byte_t const *el_debug_aranges_start;  /* [0..1] `.debug_aranges' start */
	__byte_t const *el_debug_aranges_end;    /* [0..1] `.debug_aranges' end */
	__byte_t const *el_debug_ranges_start;   /* [0..1] `.debug_ranges' start */
	__byte_t const *el_debug_ranges_end;     /* [0..1] `.debug_ranges' end */
} di_enum_locals_sections_t;

#define di_enum_locals_sections_as_di_debuginfo_cu_parser_sections(x) \
	((struct di_debuginfo_cu_parser_sections_struct *)&(x)->el_debug_loc_start)

/* Callback for `debuginfo_enum_locals()' */
typedef __ATTR_NONNULL_T((2, 3, 4, 5, 6, 7)) __ssize_t
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
typedef __ATTR_NONNULL_T((1, 3)) __ssize_t
(LIBDEBUGINFO_CC *PDEBUGINFO_ENUM_LOCALS)(di_enum_locals_sections_t const *__restrict sectinfo,
                                          __uintptr_t module_relative_pc,
                                          debuginfo_enum_locals_callback_t callback, void *arg);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 3)) __ssize_t LIBDEBUGINFO_CC
debuginfo_enum_locals(di_enum_locals_sections_t const *__restrict sectinfo,
                      __uintptr_t module_relative_pc,
                      debuginfo_enum_locals_callback_t callback, void *arg);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */


/* Super-structure containing pointers for _all_ debug-related sections */
typedef struct di_debug_sections_struct {
	/*BEGIN:compat(unwind_emulator_sections_t)*/
	__byte_t const *ds_eh_frame_hdr_start;   /* [0..1] `.eh_frame_hdr' start */
	__byte_t const *ds_eh_frame_hdr_end;     /* [0..1] `.eh_frame_hdr' end */
	__byte_t const *ds_eh_frame_start;       /* [0..1] `.eh_frame' start */
	__byte_t const *ds_eh_frame_end;         /* [0..1] `.eh_frame' end */
	__byte_t const *ds_debug_frame_start;    /* [0..1] `.debug_frame' start */
	__byte_t const *ds_debug_frame_end;      /* [0..1] `.debug_frame' end */
	/*BEGIN:compat(di_enum_locals_sections_t)*/
	__byte_t const *ds_debug_addr_start;     /* [0..1] `.debug_addr' start */
	__byte_t const *ds_debug_addr_end;       /* [0..1] `.debug_addr' end */
	/*BEGIN:compat(di_debuginfo_cu_parser_sections_t)*/
	__byte_t const *ds_debug_loc_start;      /* [0..1] `.debug_loc' start */
	__byte_t const *ds_debug_loc_end;        /* [0..1] `.debug_loc' end */
	/*BEGIN:compat(di_addr2line_sections_t)*/
	__byte_t const *ds_debug_abbrev_start;   /* [0..1] `.debug_abbrev' start */
	__byte_t const *ds_debug_abbrev_end;     /* [0..1] `.debug_abbrev' end */
	__byte_t const *ds_debug_info_start;     /* [0..1] `.debug_info' start */
	__byte_t const *ds_debug_info_end;       /* [0..1] `.debug_info' end */
	/*END:compat(unwind_emulator_sections_t)*/
	/*BEGIN:compat(di_string_sections_t)*/
	__byte_t const *ds_debug_str_start;      /* [0..1] `.debug_str' start */
	__byte_t const *ds_debug_str_end;        /* [0..1] `.debug_str' end */
	__byte_t const *ds_debug_line_str_start; /* [0..1] `.debug_line_str' start */
	__byte_t const *ds_debug_line_str_end;   /* [0..1] `.debug_line_str' end */
	/*END:compat(di_string_sections_t)*/
	/*END:compat(di_debuginfo_cu_parser_sections_t)*/
	__byte_t const *ds_debug_aranges_start;  /* [0..1] `.debug_aranges' start */
	__byte_t const *ds_debug_aranges_end;    /* [0..1] `.debug_aranges' end */
	__byte_t const *ds_debug_ranges_start;   /* [0..1] `.debug_ranges' start */
	__byte_t const *ds_debug_ranges_end;     /* [0..1] `.debug_ranges' end */
	/*END:compat(di_enum_locals_sections_t)*/
	__byte_t const *ds_debug_line_start;     /* [0..1] `.debug_line' start */
	__byte_t const *ds_debug_line_end;       /* [0..1] `.debug_line' end */
	__byte_t const *ds_strtab_start;         /* [0..1] `.strtab' / `.dynstr' start */
	__byte_t const *ds_strtab_end;           /* [0..1] `.strtab' / `.dynstr' end */
	__byte_t const *ds_symtab_start;         /* [0..1] `.symtab' / `.dynsym' start */
	__byte_t const *ds_symtab_end;           /* [0..1] `.symtab' / `.dynsym' end */
	__size_t        ds_symtab_ent;           /* Entity size of `.symtab' / `.dynsym' */
	/*END:compat(di_addr2line_sections_t)*/
} di_debug_sections_t;

#define di_debug_sections_as_unwind_emulator_sections(x)        ((unwind_emulator_sections_t *)&(x)->ds_eh_frame_hdr_start)
#define di_debug_sections_as_di_string_sections(x)              ((di_string_sections_t *)&(x)->ds_debug_str_start)
#define di_debug_sections_as_di_enum_locals_sections(x)         ((di_enum_locals_sections_t *)&(x)->ds_debug_addr_start)
#define di_debug_sections_as_di_debuginfo_cu_parser_sections(x) ((di_debuginfo_cu_parser_sections_t *)&(x)->ds_debug_loc_start)
#define di_debug_sections_as_di_addr2line_sections(x)           ((di_addr2line_sections_t *)&(x)->ds_debug_abbrev_start)
#define di_debug_sections_from_di_enum_locals_sections(x)       __COMPILER_CONTAINER_OF((__byte_t const **)(x), di_debug_sections_t, ds_debug_addr_start)

typedef struct di_debug_dl_sections_struct {
	__REF module_section_t *ds_eh_frame_hdr;   /* [0..1] `.eh_frame_hdr' */
	__REF module_section_t *ds_eh_frame;       /* [0..1] `.eh_frame' */
	__REF module_section_t *ds_debug_frame;    /* [0..1] `.debug_frame' */
	__REF module_section_t *ds_debug_addr;     /* [0..1] `.debug_addr' */
	__REF module_section_t *ds_debug_loc;      /* [0..1] `.debug_loc' */
	__REF module_section_t *ds_debug_abbrev;   /* [0..1] `.debug_abbrev' */
	__REF module_section_t *ds_debug_info;     /* [0..1] `.debug_info' */
	__REF module_section_t *ds_debug_str;      /* [0..1] `.debug_str' */
	__REF module_section_t *ds_debug_line_str; /* [0..1] `.debug_line_str' */
	__REF module_section_t *ds_debug_aranges;  /* [0..1] `.debug_aranges' */
	__REF module_section_t *ds_debug_ranges;   /* [0..1] `.debug_ranges' */
	__REF module_section_t *ds_debug_line;     /* [0..1] `.debug_line' */
	__REF module_section_t *ds_strtab;         /* [0..1] `.strtab' / `.dynstr' */
	__REF module_section_t *ds_symtab;         /* [0..1] `.symtab' / `.dynsym' */
} di_debug_dl_sections_t;

/* Load debug sections, given a handle to a module, as returned by dlopen() */
typedef __ATTR_NONNULL_T((2, 3)) void
__NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUG_SECTIONS_LOCK)(module_t *dl_handle,
                                                       di_debug_sections_t *__restrict sections,
                                                       di_debug_dl_sections_t *__restrict dl_sections);
typedef __ATTR_NONNULL_T((1)) void
__NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUG_SECTIONS_UNLOCK)(di_debug_dl_sections_t *__restrict dl_sections);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((2, 3)) void
__NOTHROW_NCX(LIBDEBUGINFO_CC debug_sections_lock)(module_t *dl_handle,
                                                   di_debug_sections_t *__restrict sections,
                                                   di_debug_dl_sections_t *__restrict dl_sections);
LIBDEBUGINFO_DECL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(LIBDEBUGINFO_CC debug_sections_unlock)(di_debug_dl_sections_t *__restrict dl_sections);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */



__DECL_END
#endif /* __CC__ */

#endif /* !_LIBDEBUGINFO_DEBUG_INFO_H */
