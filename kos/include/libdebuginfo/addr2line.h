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
#ifndef _LIBDEBUGINFO_ADDR2LINE_H
#define _LIBDEBUGINFO_ADDR2LINE_H 1

#include "api.h"
/**/

#include <bits/crt/format-printer.h>
#include <bits/types.h>
#include <kos/anno.h>
#include <kos/exec/module.h>

#include <libc/string.h>

#ifdef __CC__
__DECL_BEGIN

typedef struct di_addr2line_sections_struct {
	/* Debug information sections required for implementing addr2line.
	 * NOTE: The order of members in this struct is important!
	 *       s.a. `Section containers & overlap' in `/kos/include/libdebuginfo/debug_info.h' */
	__byte_t const *ds_debug_abbrev_start;  /* [0..1] `.debug_abbrev' start */
	__byte_t const *ds_debug_abbrev_end;    /* [0..1] `.debug_abbrev' end */
	__byte_t const *ds_debug_info_start;    /* [0..1] `.debug_info' start */
	__byte_t const *ds_debug_info_end;      /* [0..1] `.debug_info' end */
	__byte_t const *ds_debug_str_start;     /* [0..1] `.debug_str' start */
	__byte_t const *ds_debug_str_end;       /* [0..1] `.debug_str' end */
	__byte_t const *ds_debug_aranges_start; /* [0..1] `.debug_aranges' start */
	__byte_t const *ds_debug_aranges_end;   /* [0..1] `.debug_aranges' end */
	__byte_t const *ds_debug_ranges_start;  /* [0..1] `.debug_ranges' start */
	__byte_t const *ds_debug_ranges_end;    /* [0..1] `.debug_ranges' end */
	__byte_t const *ds_debug_line_start;    /* [0..1] `.debug_line' start */
	__byte_t const *ds_debug_line_end;      /* [0..1] `.debug_line' end */
	__byte_t const *ds_strtab_start;        /* [0..1] `.strtab' / `.dynstr' start */
	__byte_t const *ds_strtab_end;          /* [0..1] `.strtab' / `.dynstr' end */
	__byte_t const *ds_symtab_start;        /* [0..1] `.symtab' / `.dynsym' start */
	__byte_t const *ds_symtab_end;          /* [0..1] `.symtab' / `.dynsym' end */
	__size_t        ds_symtab_ent;          /* Entity size of `.symtab' / `.dynsym' */
} di_addr2line_sections_t;

typedef struct di_addr2line_dl_sections_struct {
	__REF module_section_t *dl_debug_abbrev;  /* [0..1] Reference to the `.debug_abbrev' section */
	__REF module_section_t *dl_debug_info;    /* [0..1] Reference to the `.debug_info' section */
	__REF module_section_t *dl_debug_str;     /* [0..1] Reference to the `.debug_str' section */
	__REF module_section_t *dl_debug_aranges; /* [0..1] Reference to the `.debug_aranges' section */
	__REF module_section_t *dl_debug_ranges;  /* [0..1] Reference to the `.debug_ranges' section */
	__REF module_section_t *dl_debug_line;    /* [0..1] Reference to the `.debug_line' section */
	__REF module_section_t *dl_strtab;        /* [0..1] Reference to the `.strtab' or `.dynstr' section */
	__REF module_section_t *dl_symtab;        /* [0..1] Reference to the `.symtab' or `.dynsym' section */
} di_addr2line_dl_sections_t;


typedef struct {
	/* Notes about address ranges on inlined/top-level/inline-caller levels:
	 *   - al_symstart...al_symend:
	 *     INLINE: The bounds of the matched address range of the associated inline function.
	 *     REGULAR: The start/end of the surrounding function symbol.
	 *   - al_linestart...al_lineend:
	 *     INLINE/TOP-LEVEL FUNCTION: address of the previous/next A2L label.
	 *     INLINE-RETURN-ADDR: The bounds of the inline function being called.
	 * Example (using abs_pc == c01bd839; aka. the return value of `test_function()'):
	 *    LEVEL | FUNCTION         | al_symstart  al_symend | al_linestart  al_lineend
	 *        0 | inline_function  | c01bd82f ... c01bd83d  | c01bd839 ... c01bd83a
	 *        1 | inline_function2 | c01bd82e ... c01bd844  | c01bd82f ... c01bd83d
	 *        2 | inline_function3 | c01bd82d ... c01bd84b  | c01bd82e ... c01bd844
	 *        3 | test_function    | c01bd826 ... c01bd854  | c01bd82d ... c01bd84b
	 * Assembly (i386):
	 * >> c01bd826 <test_function>:
	 * >> c01bd826:	55                   	push   %ebp
	 * >> c01bd827:	89 e5                	mov    %esp,%ebp
	 * >> c01bd829:	83 ec 10             	sub    $0x10,%esp
	 * >> c01bd82c:	90                   	nop
	 * >> c01bd82d:	90                   	nop
	 * >> c01bd82e:	90                   	nop
	 * >> c01bd82f:	b8 39 d8 1b c0       	mov    $0xc01bd839,%eax
	 * >> c01bd834:	89 c0                	mov    %eax,%eax
	 * >> c01bd836:	89 45 f4             	mov    %eax,-0xc(%ebp)
	 * >> c01bd839:	90                   	nop
	 * >> c01bd83a:	8b 45 f4             	mov    -0xc(%ebp),%eax
	 * >> c01bd83d:	89 45 f8             	mov    %eax,-0x8(%ebp)
	 * >> c01bd840:	90                   	nop
	 * >> c01bd841:	8b 45 f8             	mov    -0x8(%ebp),%eax
	 * >> c01bd844:	89 45 fc             	mov    %eax,-0x4(%ebp)
	 * >> c01bd847:	90                   	nop
	 * >> c01bd848:	8b 45 fc             	mov    -0x4(%ebp),%eax
	 * >> c01bd84b:	89 45 f0             	mov    %eax,-0x10(%ebp)
	 * >> c01bd84e:	90                   	nop
	 * >> c01bd84f:	8b 45 f0             	mov    -0x10(%ebp),%eax
	 * >> c01bd852:	c9                   	leave
	 * >> c01bd853:	c3                   	ret
	 * >> c01bd854:	...
	 * Source (C/C++):
	 * >> inline __attribute__((always_inline)) void *inline_function(void) {
	 * >> 	void *result;
	 * >> 	__asm__ __volatile__("mov %1, %0" : "=g" (result) : "r" (&&foo));
	 * >> foo:
	 * >> 	__asm__("nop");
	 * >> 	return result;
	 * >> }
	 * >> inline __attribute__((always_inline)) void *inline_function2(void) {
	 * >> 	void *result;
	 * >> 	__asm__("nop");
	 * >> 	result = inline_function();
	 * >> 	__asm__("nop");
	 * >> 	return result;
	 * >> }
	 * >> inline __attribute__((always_inline)) void *inline_function3(void) {
	 * >> 	void *result;
	 * >> 	__asm__("nop");
	 * >> 	result = inline_function2();
	 * >> 	__asm__("nop");
	 * >> 	return result;
	 * >> }
	 * >> extern __attribute__((visibility("hidden"))) void *test_function(void) {
	 * >> 	void *result;
	 * >> 	__asm__("nop");
	 * >> 	result = inline_function3();
	 * >> 	__asm__("nop");
	 * >> 	return result;
	 * >> }
	 */
	__uintptr_t al_levelcnt;  /* The number of available source levels (The argument
	                           * passed  to  `level'  must  be  smaller  than  this) */
	__uintptr_t al_symstart;  /* Starting address of the surrounding symbol (module-relative). */
	__uintptr_t al_symend;    /* End address of the surrounding symbol (module-relative). */
	__uintptr_t al_linestart; /* Starting address of the associated source location (module-relative). */
	__uintptr_t al_lineend;   /* End address of the associated source location (module-relative). */
	__uintptr_t al_linediscr; /* Source location discriminator. */
	char const *al_rawname;   /* [0..1] Raw name of the surrounding symbol. */
	char const *al_name;      /* [0..1] Symbol name of the surrounding symbol (managed). */
	char const *al_cuname;    /* [0..1] Name of the associated compilation unit (aka. __BASENAME__). */
	char const *al_cubase;    /* [0..1] First component of the associated source file. */
	char const *al_srcpath;   /* [0..1] Second component of the associated source file. */
	char const *al_srcfile;   /* [0..1] Third component of the associated source file. */
	__uintptr_t al_srcline;   /* Source line number (1-based; 0 if unknown) */
	__uintptr_t al_srccol;    /* Source column number (1-based; 0 if unknown) */
	char const *al_dclpath;   /* [0..1] Second component of the source file that declared the function. */
	char const *al_dclfile;   /* [0..1] Third component of the source file that declared the function. */
	__uintptr_t al_dclline;   /* Declaration source line number of the surrounding function (1-based; 0 if unknown) */
	__uintptr_t al_dclcol;    /* Declaration source column number of the surrounding function (1-based; 0 if unknown) */
} di_debug_addr2line_t;


/* Analyze data from the given `sections' to locate source-level information about `module_relative_pc'.
 * HINT: Using this function, you can implement the behavior of `$ addr2line -ife ...' entirely in
 *       software, by combining this api with functions from <dlfcn.h>
 * @param: sections: The mapping locations for the different debug sections associated with the  program.
 *                   This structure must be initialized with available section information by the caller,
 *                   although for  minimal  functionality,  only the  .debug_line  section  is  required.
 *                   Note however  that  other sections  are  mandatory  (and recommended)  in  order  to
 *                   provide full support of available features.
 * @param: level:    Inline  function  indirection  depth   for  the  location  to   query.
 *                   Level  #0 always refers  to the exact  source location, as retrievable
 *                   via  the .debug_line program, while all levels greater than this refer
 *                   to  the  call-sites  of  inlined  functions  found  at  that location.
 *                   Alternatively, you may also pass `DEBUG_ADDR2LINE_LEVEL_SOURCE', which
 *                   always refers to the top-most, non-inlined source location.
 * @param: flags:    Set of `DEBUG_ADDR2LINE_F*'
 * >> di_debug_addr2line_t info;
 * >> unsigned int error;
 * >> uintptr_t level = 0;
 * >> do {
 * >>     error = debug_addr2line((uintptr_t)ptr, &info, level);
 * >>     if (error != DEBUG_INFO_ERROR_SUCCESS)
 * >>         break;
 * >>     printf("%s(%" PRIuPTR ") : %s : HERE\n",
 * >>            info.al_srcfile,
 * >>            info.al_srcline,
 * >>            info.al_name);
 * >> } while (++level < info.al_levelcnt);
 * NOTE: The return value differs from `DEBUG_INFO_ERROR_SUCCESS', `*result' will have
 *       been initialized as follows:
 *        - al_levelcnt:  The  number of known  information levels for the
 *                        address, or 0 if no information is known at all.
 *        - al_symstart:  Set to `module_relative_pc'
 *        - al_symend:    Set to `module_relative_pc'
 *        - al_linestart: Set to `module_relative_pc'
 *        - al_lineend:   Set to `module_relative_pc'
 *        - * :           All other fields are 0/NULL
 * @return: DEBUG_INFO_ERROR_SUCCESS: Successfully retrieved information.
 * @return: DEBUG_INFO_ERROR_NOFRAME: Either no information is known about `module_relative_pc',
 *                                    or the given `level >= OUT(result->al_levelcnt)', and also
 *                                    isn't  equal   to  `DEBUG_ADDR2LINE_LEVEL_SOURCE',   where
 *                                    `result->al_levelcnt' is  set to  0 if  no information  is
 *                                    known at all, or whatever the total number of  information
 *                                    levels know is. (all other  fields of `*result' are  NULL-
 *                                    initialized)
 * @return: DEBUG_INFO_ERROR_CORRUPT: Debug information is corrupted (`*result' was NULL-initialized). */
typedef __ATTR_NONNULL_T((1, 2)) unsigned int
(LIBDEBUGINFO_CC *PDEBUG_ADDR2LINE)(di_addr2line_sections_t const *__restrict sections,
                                    di_debug_addr2line_t *__restrict result,
                                    __uintptr_t module_relative_pc,
                                    __uintptr_t level, __uintptr_t flags);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 2)) unsigned int
__NOTHROW_NCX(LIBDEBUGINFO_CC debug_addr2line)(di_addr2line_sections_t const *__restrict sections,
                                               di_debug_addr2line_t *__restrict result,
                                               __uintptr_t module_relative_pc,
                                               __uintptr_t level, __uintptr_t flags);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */


/* Print the fully qualified filename for a given string
 * triplet, as extractable from  `di_debug_addr2line_t':
 *   - debug_addr2line_print_filename(..., info.al_cubase, info.al_srcpath, info.al_srcfile);
 *     "/home/me/project/c/foo/src/bar.c"
 *   - debug_addr2line_print_filename(..., info.al_cubase, info.al_dclpath, info.al_dclfile);
 *     "/home/me/project/c/foo/include/bar.h"
 */
typedef __ATTR_NONNULL_T((1)) __ssize_t
(LIBDEBUGINFO_CC *PDEBUG_ADDR2LINE_PRINT_FILENAME)(__pformatprinter printer, void *arg,
                                                   char const *cubase, char const *pathname,
                                                   char const *filename);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1)) __ssize_t
(LIBDEBUGINFO_CC debug_addr2line_print_filename)(__pformatprinter printer, void *arg,
                                                 char const *cubase, char const *pathname,
                                                 char const *filename);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */

/* Load debug sections, given a handle to a module, as returned by dlopen()
 * >> These functions are simply light-weight wrappers around `dllocksection()',
 *    taking  the job of  locking debug information sections  into memory off of
 *    the user.
 * @return: DEBUG_INFO_ERROR_SUCCESS: Successfully loaded debug sections.
 * @return: DEBUG_INFO_ERROR_NOFRAME: Either `dl_handle' is invalid, or the specified library
 *                                    doesn't  provide any of the necessary debug information
 *                                    sections.
 *                                    In this case, `sections' and `dl_sections' will have both
 *                                    been initialized to all NULL-values. */
typedef __ATTR_NONNULL_T((2, 3)) unsigned int
(LIBDEBUGINFO_CC *PDEBUG_ADDR2LINE_SECTIONS_LOCK)(module_t *dl_handle,
                                                  di_addr2line_sections_t *__restrict sections,
                                                  di_addr2line_dl_sections_t *__restrict dl_sections);
typedef __ATTR_NONNULL_T((1)) void
(LIBDEBUGINFO_CC *PDEBUG_ADDR2LINE_SECTIONS_UNLOCK)(di_addr2line_dl_sections_t *__restrict dl_sections);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((2, 3)) unsigned int
__NOTHROW_NCX(LIBDEBUGINFO_CC debug_addr2line_sections_lock)(module_t *dl_handle,
                                                             di_addr2line_sections_t *__restrict sections,
                                                             di_addr2line_dl_sections_t *__restrict dl_sections);
LIBDEBUGINFO_DECL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(LIBDEBUGINFO_CC debug_addr2line_sections_unlock)(di_addr2line_dl_sections_t *__restrict dl_sections);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */

/* A special source level that always refers to `LEVEL_COUNT - 1' */
#define DEBUG_ADDR2LINE_LEVEL_SOURCE (__CCAST(__uintptr_t)-1)

#define DEBUG_ADDR2LINE_FNORMAL  0x0000 /* Normal flags. */
#define DEBUG_ADDR2LINE_FTRYHARD 0x0001 /* Try really hard to find debug information (takes
                                         * very long if information _really_ doesn't exist) */


#endif /* !_LIBDEBUGINFO_ADDR2LINE_H */
