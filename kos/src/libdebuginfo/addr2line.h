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
#ifndef GUARD_LIBDEBUGINFO_ADDR2LINE_H
#define GUARD_LIBDEBUGINFO_ADDR2LINE_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <format-printer.h>

#include <libdebuginfo/addr2line.h>
#include <libdebuginfo/errno.h>

DECL_BEGIN

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
 * >> debuginfo_errno_t error;
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
INTDEF NONNULL((1, 2)) debuginfo_errno_t
NOTHROW_NCX(CC libdi_debug_addr2line)(di_addr2line_sections_t const *__restrict sections,
                                      di_debug_addr2line_t *__restrict result,
                                      uintptr_t module_relative_pc,
                                      uintptr_t level,
                                      uintptr_t flags);

/* Print the fully qualified filename for a given string
 * triplet, as extractable from  `di_debug_addr2line_t':
 *   - debug_addr2line_print_filename(..., info.al_cubase, info.al_srcpath, info.al_srcfile); // /home/me/project/c/foo/src/bar.c
 *   - debug_addr2line_print_filename(..., info.al_cubase, info.al_dclpath, info.al_dclfile); // /home/me/project/c/foo/include/bar.h
 * NOTE: When `filename' is NULL, print `???' (3 question marks) instead. */
INTDEF NONNULL((1)) ssize_t CC
libdi_debug_addr2line_print_filename(pformatprinter printer, void *arg,
                                     char const *cubase, char const *pathname,
                                     char const *filename);


/* Load debug sections, given a handle to a module, as returned by dlopen()
 * >> These functions are simply light-weight wrappers around `dllocksection(3D)',
 *    taking the job  of locking  debug information  sections into  memory off  of
 *    the user.
 * @return: DEBUG_INFO_ERROR_SUCCESS: Successfully loaded debug sections.
 * @return: DEBUG_INFO_ERROR_NOFRAME: Either `dl_handle' is invalid, or the specified library
 *                                    doesn't  provide any of the necessary debug information
 *                                    sections.
 *                                    In this case, `sections' and `dl_sections' will have both
 *                                    been initialized to all NULL-values. */
INTDEF NONNULL((2, 3)) debuginfo_errno_t
NOTHROW_NCX(CC libdi_debug_addr2line_sections_lock)(module_t *dl_handle,
                                                    di_addr2line_sections_t *__restrict sections,
                                                    di_addr2line_dl_sections_t *__restrict dl_sections);
INTDEF NONNULL((1)) void
NOTHROW_NCX(CC libdi_debug_addr2line_sections_unlock)(di_addr2line_dl_sections_t *__restrict dl_sections);




DECL_END

#endif /* !GUARD_LIBDEBUGINFO_ADDR2LINE_H */
