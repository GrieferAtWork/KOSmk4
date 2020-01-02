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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBDEBUGINFO_DEBUG_LINE_H
#define _LIBDEBUGINFO_DEBUG_LINE_H 1

#include "api.h"
#include "dwarf.h"
#include <bits/types.h>
#include <libc/string.h>

#define DI_DEBUGLINE_INFO_FNORMAL  0x0000 /* Normal flags */
#define DI_DEBUGLINE_INFO_FISSTMT  0x0001 /* Part of a statement */
#define DI_DEBUGLINE_INFO_FBBLOCK  0x0002 /* Part of a basic block */
#define DI_DEBUGLINE_INFO_FPROLOG  0x0004 /* Part of the function prolog */
#define DI_DEBUGLINE_INFO_FEPILOG  0x0008 /* Part of the function epilog */

#ifdef __CC__
__DECL_BEGIN

typedef struct {
	char            fe_name[1024]; /* Filename (NUL-terminated) */
	dwarf_uleb128_t fe_path;       /* File path index. */
	dwarf_uleb128_t fe_b;          /* timestamp... */
	dwarf_uleb128_t fe_c;          /* timestamp... */
} di_debugline_fileent_t;

typedef struct {
	/* Compilation unit descriptor, as decoded from `.debug_line' */
	__byte_t               *dlu_headerbase;       /* [1..1] Base address of the CU header. */
	__byte_t               *dlu_textbase;         /* [1..1] Base address of the CU resolver text. */
	__byte_t               *dlu_cuend;            /* [1..1] End address of the CU segment. */
	char                   *dlu_pathtable;        /* [1..1] Table to path names (e.g. "include/headers\0source/files\0\0") */
	__size_t                dlu_pathcount;        /* Number of path strings located in `dlu_pathtable' */
	di_debugline_fileent_t *dlu_filetable;        /* [1..1] Table to file names */
	__uint16_t              dlu_version;          /* Used during decoding... */
	__uint8_t               dlu_min_insn_length;  /* Used during decoding... */
	__uint8_t               dlu_max_ops_per_insn; /* Used during decoding... */
	__uint8_t               dlu_default_isstmt;   /* Used during decoding... */
	__int8_t                dlu_line_base;        /* Used during decoding... */
	__uint8_t               dlu_line_range;       /* Used during decoding... */
	__uint8_t               dlu_opcode_base;      /* Used during decoding... */
	__uint8_t              *dlu_opcode_lengths;   /* Used during decoding... */
} di_debugline_unit_t;

/* Decode a given file index into its filename and pathname components. */
__LOCAL __ATTR_NONNULL((1, 3, 4)) void
__NOTHROW_NCX(LIBDEBUGINFO_CC debugline_loadfile)(di_debugline_unit_t *__restrict self,
                                                  dwarf_uleb128_t index,
                                                  char **__restrict ppathname,
                                                  char **__restrict pfilename) {
	if (!index) {
		*ppathname = __NULLPTR;
		*pfilename = __NULLPTR;
	} else {
		char *iter;
		iter = (char *)self->dlu_filetable;
		while (--index && (__byte_t *)iter < self->dlu_textbase) {
			if (!*iter)
				break; /* Invalid file ID */
			iter = __libc_strend(iter) + 1;
			dwarf_decode_uleb128((__byte_t **)&iter);
			dwarf_decode_uleb128((__byte_t **)&iter);
			dwarf_decode_uleb128((__byte_t **)&iter);
		}
		*pfilename = iter;
		/* Parse the directory number. */
		iter = __libc_strend(iter) + 1;
		index = (__uintptr_t)dwarf_decode_uleb128((__byte_t **)&iter);
		if (!index || --index >= self->dlu_pathcount)
			*ppathname = __NULLPTR;
		else {
			iter = self->dlu_pathtable;
			while (index--)
				iter = __libc_strend(iter) + 1;
			*ppathname = iter;
		}
	}
}

typedef struct {
	__uintptr_t     dl_linestart;     /* Starting address of the associated source location. */
	__uintptr_t     dl_lineend;       /* End address of the associated source location. */
	dwarf_uleb128_t dl_srcfile;       /* Source file index (Use with `debugline_loadfile()' to extract strings) */
	dwarf_sleb128_t dl_srcline;       /* Source line number (1-based; 0 if unknown) */
	dwarf_uleb128_t dl_srccol;        /* Source column number (1-based; 0 if unknown) */
	dwarf_uleb128_t dl_discriminator; /* Source discriminator */
	__uintptr_t     dl_flags;         /* Source flags (Set of `DI_DEBUGLINE_INFO_F*') */
} di_debugline_info_t;



/* Given a pointer to the start of a debug_line CU (or a pointer to the start of
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
 * >>     __byte_t *reader;
 * >>     __uintptr_t relpc;
 * >>     void *m;
 * >>     if ((m = dlgethandle(p,DLGETHANDLE_FNORMAL)) == NULL) goto done;
 * >>     if ((s = dllocksection(m,".debug_line")) == NULL) goto done;
 * >>     reader = (__byte_t *)s->ds_data;
 * >>     relpc = (__uintptr_t)((__byte_t *)p - (__byte_t *)dlmodulebase(m));
 * >>     while (debugline_loadunit(reader,reader + s->ds_size,&unit) == DEBUG_INFO_ERROR_SUCCESS) {
 * >>         di_debugline_info_t info;
 * >>         if (debugline_scanunit(&unit,&info,relpc) == DEBUG_INFO_ERROR_SUCCESS) {
 * >>             char *file,*path;
 * >>             debugline_loadfile(&unit,info.dl_srcfile,&file,&path);
 * >>             printf("path: %s\n",path);
 * >>             printf("file: %s\n",file);
 * >>             printf("line: %d\n",(int)info.dl_srcline);
 * >>             printf("col:  %u\n",(unsigned int)info.dl_srccol);
 * >>             goto done;
 * >>         }
 * >>     }
 * >>     printf("Unknown: %p\n",p);
 * >> done:
 * >>     dlunlocksection(s);
 * >> }
 * @return: DEBUG_INFO_ERROR_SUCCESS: ...
 * @return: DEBUG_INFO_ERROR_NOFRAME: All units have been loaded.
 * @return: DEBUG_INFO_ERROR_CORRUPT: ... */
typedef __ATTR_NONNULL((1, 2, 3)) unsigned int
(LIBDEBUGINFO_CC *PDEBUGLINE_LOADUNIT)(__byte_t **__restrict preader,
                                       __byte_t *__restrict text_end,
                                       di_debugline_unit_t *__restrict result);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 2, 3)) unsigned int
__NOTHROW_NCX(LIBDEBUGINFO_CC debugline_loadunit)(__byte_t **__restrict preader,
                                                  __byte_t *__restrict text_end,
                                                  di_debugline_unit_t *__restrict result);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */


/* Scan the given .debug_line unit `self' for information related to the given
 * `module_relative_pc', and store that information into `*result' upon success.
 * @param: module_relative_pc: The starting address of the instruction to scan for.
 * @return: DEBUG_INFO_ERROR_SUCCESS: ...
 * @return: DEBUG_INFO_ERROR_NOFRAME: ...
 * @return: DEBUG_INFO_ERROR_CORRUPT: ... */
typedef __ATTR_NONNULL((1, 2)) unsigned int
(LIBDEBUGINFO_CC *PDEBUGLINE_SCANUNIT)(di_debugline_unit_t const *__restrict self,
                                       di_debugline_info_t *__restrict result,
                                       __uintptr_t module_relative_pc);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 2)) unsigned int
__NOTHROW_NCX(LIBDEBUGINFO_CC debugline_scanunit)(di_debugline_unit_t const *__restrict self,
                                                  di_debugline_info_t *__restrict result,
                                                  __uintptr_t module_relative_pc);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */






__DECL_END
#endif /* __CC__ */

#endif /* !_LIBDEBUGINFO_DEBUG_LINE_H */
