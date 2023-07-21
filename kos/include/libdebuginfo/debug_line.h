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
#ifndef _LIBDEBUGINFO_DEBUG_LINE_H
#define _LIBDEBUGINFO_DEBUG_LINE_H 1

#include "api.h"
/**/

#include <bits/types.h>
#include <kos/anno.h>

#include <libc/string.h>
#include <libunwind/dwarf.h>

#include "errno.h"

#define DI_DEBUGLINE_INFO_FNORMAL  0x0000 /* Normal flags */
#define DI_DEBUGLINE_INFO_FISSTMT  0x0001 /* Part of a statement */
#define DI_DEBUGLINE_INFO_FBBLOCK  0x0002 /* Part of a basic block */
#define DI_DEBUGLINE_INFO_FPROLOG  0x0004 /* Part of the function prolog */
#define DI_DEBUGLINE_INFO_FEPILOG  0x0008 /* Part of the function epilog */

#ifdef __CC__
__DECL_BEGIN

/* Representation of `directory_entry_format' and `file_name_entry_format' */
typedef struct __ATTR_PACKED {
	dwarf_uleb128_t dlffe_type; /* One of `DW_LNCT_*' */
	dwarf_uleb128_t dlffe_form; /* One of `DW_FORM_*' */
} di_debugline_fileinfo_format_entry_t;

typedef struct __ATTR_PACKED {
	__uint8_t                                                     dlff_count;    /* directory_entry_format_count, file_name_entry_format_count */
	COMPILER_FLEXIBLE_ARRAY(di_debugline_fileinfo_format_entry_t, dlff_entries); /* directory_entry_format, file_name_entry_format */
} di_debugline_fileinfo_format_t;

typedef struct {
	/* Compilation unit descriptor, as decoded from `.debug_line' */
	__CHECKED __byte_t const                       *dlu_headerbase;       /* [1..1] Base address of the CU header. */
	__CHECKED __byte_t const                       *dlu_textbase;         /* [1..1] Base address of the CU resolver text. */
	__CHECKED __byte_t const                       *dlu_cuend;            /* [1..1] End address of the CU segment. */
	__CHECKED di_debugline_fileinfo_format_t const *dlu_pathfmt;          /* [1..1] Format of path names. */
	__size_t                                        dlu_pathcount;        /* # of path-items in `dlu_pathdata' */
	__CHECKED __byte_t const                       *dlu_pathdata;         /* [0..dlu_pathcount] Path data (array of `dlu_pathfmt') */
	__CHECKED di_debugline_fileinfo_format_t const *dlu_filefmt;          /* [1..1] Format of file names. */
	__size_t                                        dlu_filecount;        /* # of file-items in `dlu_filedata' */
	__CHECKED __byte_t const                       *dlu_filedata;         /* [0..dlu_filecount] Path data (array of `dlu_filefmt') */
	__uint16_t                                      dlu_version;          /* Used during decoding... */
	__uint8_t                                       dlu_min_insn_length;  /* Used during decoding... */
	__uint8_t                                       dlu_max_ops_per_insn; /* Used during decoding... */
	__uint8_t                                       dlu_default_isstmt;   /* Used during decoding... */
	__int8_t                                        dlu_line_base;        /* Used during decoding... */
	__uint8_t                                       dlu_line_range;       /* Used during decoding... */
	__uint8_t                                       dlu_opcode_base;      /* Used during decoding... */
	__CHECKED __uint8_t const                      *dlu_opcode_lengths;   /* Used during decoding... */
	__uint8_t                                       dlu_ptrsize;          /* Pointer size (4 in 32-bit DWARF; 8 in 64-bit DWARF). */
	__uint8_t                                       dlu_addrsize;         /* Address size */
} di_debugline_unit_t;


typedef struct {
	__CHECKED char const *dlfi_path; /* [0..1] File path */
	__CHECKED char const *dlfi_file; /* [0..1] File name */
} di_debugline_fileinfo_t;

#define di_debug_addr2line_srcas_debugline_fileinfo(x) \
	((di_debugline_fileinfo_t *)&(x)->al_srcpath)
#define di_debug_addr2line_dclas_debugline_fileinfo(x) \
	((di_debugline_fileinfo_t *)&(x)->al_dclpath)

struct di_string_sections_struct;

/* Decode a given file index into its filename and pathname components. */
typedef __ATTR_NONNULL_T((1, 3, 4)) void
__NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGLINE_LOADFILE)(di_debugline_unit_t *__restrict self, /* Only non-const for lazy init */
                                                      dwarf_uleb128_t index, di_debugline_fileinfo_t *__restrict result,
                                                      struct di_string_sections_struct const *__restrict sections);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 3, 4)) void
__NOTHROW_NCX(LIBDEBUGINFO_CC debugline_loadfile)(di_debugline_unit_t *__restrict self, /* Only non-const for lazy init */
                                                  dwarf_uleb128_t index, di_debugline_fileinfo_t *__restrict result,
                                                  struct di_string_sections_struct const *__restrict sections);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */


typedef struct {
	__uintptr_t     dl_linestart;     /* Starting address of the associated source location. */
	__uintptr_t     dl_lineend;       /* End address of the associated source location. */
	dwarf_uleb128_t dl_srcfile;       /* Source file index (Use with `debugline_loadfile()' to extract strings) */
	dwarf_sleb128_t dl_srcline;       /* Source line number (1-based; 0 if unknown) */
	dwarf_uleb128_t dl_srccol;        /* Source column number (1-based; 0 if unknown) */
	dwarf_uleb128_t dl_discriminator; /* Source discriminator */
	__uintptr_t     dl_flags;         /* Source flags (Set of `DI_DEBUGLINE_INFO_F*') */
} di_debugline_info_t;



/* Given a pointer to the start of a  debug_line CU (or a pointer to the start  of
 * the .debug_line section), initialize the given debugline CU structure `result',
 * and advance `*preader' to the start of the next unit:
 * >> #define _KOS_SOURCE 1
 * >> #include <dlfcn.h>
 * >> #include <stdio.h>
 * >> #include <libdebuginfo/debug_line.h>
 * >>
 * >> // Print the source location for a given address `p'
 * >> void print_addr2line(void *p) {
 * >>     struct dl_section *s = NULL;
 * >>     di_debugline_unit_t unit;
 * >>     byte_t const *reader;
 * >>     uintptr_t relpc;
 * >>     void *m;
 * >>     if ((m = dlgethandle(p, DLGETHANDLE_FNORMAL)) == NULL)
 * >>         goto done;
 * >>     if ((s = dllocksection(m, ".debug_line")) == NULL)
 * >>         goto done;
 * >>     reader = (byte_t *)s->ds_data;
 * >>     relpc = (uintptr_t)((byte_t *)p - (byte_t *)dlmodulebase(m));
 * >>     while (debugline_loadunit(reader, reader + s->ds_size, &unit) == DEBUG_INFO_ERROR_SUCCESS) {
 * >>         di_debugline_info_t info;
 * >>         if (debugline_scanunit(&unit, &info, relpc) == DEBUG_INFO_ERROR_SUCCESS) {
 * >>             char *file, *path;
 * >>             debugline_loadfile(&unit, info.dl_srcfile, &file, &path);
 * >>             printf("path: %s\n", path);
 * >>             printf("file: %s\n", file);
 * >>             printf("line: %d\n", (int)info.dl_srcline);
 * >>             printf("col:  %u\n", (unsigned int)info.dl_srccol);
 * >>             goto done;
 * >>         }
 * >>     }
 * >>     printf("Unknown: %p\n", p);
 * >> done:
 * >>     dlunlocksection(s);
 * >> }
 * @return: DEBUG_INFO_ERROR_SUCCESS: ...
 * @return: DEBUG_INFO_ERROR_NOFRAME: All units have been loaded.
 * @return: DEBUG_INFO_ERROR_CORRUPT: ... */
typedef __ATTR_NONNULL_T((1, 2, 3)) debuginfo_errno_t
__NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGLINE_LOADUNIT)(__CHECKED __byte_t const **__restrict preader,
                                                      __CHECKED __byte_t const *__restrict text_end,
                                                      di_debugline_unit_t *__restrict result);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 2, 3)) debuginfo_errno_t
__NOTHROW_NCX(LIBDEBUGINFO_CC debugline_loadunit)(__CHECKED __byte_t const **__restrict preader,
                                                  __CHECKED __byte_t const *__restrict text_end,
                                                  di_debugline_unit_t *__restrict result);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */


/* Scan the given .debug_line unit `self'  for information related to the  given
 * `module_relative_pc', and store that information into `*result' upon success.
 * @param: module_relative_pc: The starting address of the instruction to scan for.
 * @return: DEBUG_INFO_ERROR_SUCCESS: ...
 * @return: DEBUG_INFO_ERROR_NOFRAME: ...
 * @return: DEBUG_INFO_ERROR_CORRUPT: ... */
typedef __ATTR_NONNULL_T((1, 2)) debuginfo_errno_t
__NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDEBUGLINE_SCANUNIT)(di_debugline_unit_t const *__restrict self,
                                                      di_debugline_info_t *__restrict result,
                                                      __uintptr_t module_relative_pc);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 2)) debuginfo_errno_t
__NOTHROW_NCX(LIBDEBUGINFO_CC debugline_scanunit)(di_debugline_unit_t const *__restrict self,
                                                  di_debugline_info_t *__restrict result,
                                                  __uintptr_t module_relative_pc);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */






__DECL_END
#endif /* __CC__ */

#endif /* !_LIBDEBUGINFO_DEBUG_LINE_H */
