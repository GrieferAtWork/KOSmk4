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
#ifndef GUARD_LIBDEBUGINFO_DEBUG_LINE_H
#define GUARD_LIBDEBUGINFO_DEBUG_LINE_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <libdebuginfo/debug_line.h>

DECL_BEGIN

/* Decode a given file index into its filename and pathname components. */
INTDEF NONNULL((1, 3, 4)) void
NOTHROW_NCX(CC libdi_debugline_loadfile)(di_debugline_unit_t *__restrict self, /* Only non-const for lazy init */
                                         dwarf_uleb128_t index, di_debugline_fileinfo_t *__restrict result,
                                         struct di_string_sections_struct const *__restrict sections);

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
INTDEF NONNULL((1, 2, 3)) debuginfo_errno_t
NOTHROW_NCX(CC libdi_debugline_loadunit)(byte_t const **__restrict preader,
                                         byte_t const *__restrict text_end,
                                         di_debugline_unit_t *__restrict result);


/* Scan the given .debug_line unit `self'  for information related to the  given
 * `module_relative_pc', and store that information into `*result' upon success.
 * @param: module_relative_pc: The starting address of the instruction to scan for.
 * @return: DEBUG_INFO_ERROR_SUCCESS: ...
 * @return: DEBUG_INFO_ERROR_NOFRAME: ...
 * @return: DEBUG_INFO_ERROR_CORRUPT: ... */
INTDEF NONNULL((1, 2)) debuginfo_errno_t
NOTHROW_NCX(CC libdi_debugline_scanunit)(di_debugline_unit_t const *__restrict self,
                                         di_debugline_info_t *__restrict result,
                                         uintptr_t module_relative_pc);



DECL_END

#endif /* !GUARD_LIBDEBUGINFO_DEBUG_LINE_H */
