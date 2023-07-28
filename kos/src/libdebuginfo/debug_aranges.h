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
#ifndef GUARD_LIBDEBUGINFO_DEBUG_ARANGES_H
#define GUARD_LIBDEBUGINFO_DEBUG_ARANGES_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <libdebuginfo/debug_aranges.h>
#include <libdebuginfo/errno.h>

DECL_BEGIN

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
INTDEF NONNULL((3)) debuginfo_errno_t
NOTHROW_NCX(CC libdi_debugaranges_locate)(__CHECKED byte_t const *debug_aranges_start,
                                          __CHECKED byte_t const *debug_aranges_end,
                                          uintptr_t *__restrict pdebug_info_cu_offset,
                                          uintptr_t module_relative_pc);

DECL_END

#endif /* !GUARD_LIBDEBUGINFO_DEBUG_ARANGES_H */
