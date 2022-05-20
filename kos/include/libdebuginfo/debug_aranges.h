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
#ifndef _LIBDEBUGINFO_DEBUG_ARANGES_H
#define _LIBDEBUGINFO_DEBUG_ARANGES_H 1

#include "api.h"
/**/

#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

/* NOTE: `.debug_ranges' and `.debug_aranges' may sound similar, but are 2 different sections! */


/* Scan through  the given  debug_aranges blob  for a  descriptor referring  to
 * the given `module_relative_pc'. - If  found, store that descriptor's  offset
 * into the .debug_info section in `*pdebug_info_cu_offset' and return success.
 * @param: pdebug_info_cu_offset: Pointer that will  receive an  offset into  `.debug_info',
 *                                which may then be used with `debuginfo_cu_parser_loadunit'
 *                                in order to load the compilation unit associated with  the
 *                                `module_relative_pc' originally passed  to this  function.
 * @return: DEBUG_INFO_ERROR_SUCCESS: ...
 * @return: DEBUG_INFO_ERROR_NOFRAME: ...
 * @return: DEBUG_INFO_ERROR_CORRUPT: ... */
typedef __ATTR_NONNULL_T((1, 2, 3)) unsigned int
(LIBDEBUGINFO_CC *PDEBUGARANGES_LOCATE)(__byte_t const *__restrict debug_aranges_start,
                                        __byte_t const *__restrict debug_aranges_end,
                                        __uintptr_t *__restrict pdebug_info_cu_offset,
                                        __uintptr_t module_relative_pc);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 2, 3)) unsigned int
__NOTHROW_NCX(LIBDEBUGINFO_CC debugaranges_locate)(__byte_t const *__restrict debug_aranges_start,
                                                   __byte_t const *__restrict debug_aranges_end,
                                                   __uintptr_t *__restrict pdebug_info_cu_offset,
                                                   __uintptr_t module_relative_pc);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBDEBUGINFO_DEBUG_ARANGES_H */
