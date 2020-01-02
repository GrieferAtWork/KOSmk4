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
#ifndef GUARD_LIBDEBUGINFO_DEBUG_LINE_H
#define GUARD_LIBDEBUGINFO_DEBUG_LINE_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <libdebuginfo/debug_line.h>

DECL_BEGIN

/* Given a pointer to the start of a debug_line CU (or a pointer to the start of
 * the .debug_line section), initialize the given debugline CU structure `result',
 * and advance `*preader' to the start of the next unit.
 * @return: DEBUG_INFO_ERROR_SUCCESS: ...
 * @return: DEBUG_INFO_ERROR_NOFRAME: All units have been loaded.
 * @return: DEBUG_INFO_ERROR_CORRUPT: ... */
INTDEF NONNULL((1, 2, 3)) unsigned int
NOTHROW_NCX(CC libdi_debugline_loadunit)(byte_t **__restrict preader,
                                         byte_t *__restrict text_end,
                                         di_debugline_unit_t *__restrict result);


/* Scan the given .debug_line unit `self' for information related to the
 * given `module_relative_pc', and store that information into `*result' upon success.
 * @return: DEBUG_INFO_ERROR_SUCCESS: ...
 * @return: DEBUG_INFO_ERROR_NOFRAME: ...
 * @return: DEBUG_INFO_ERROR_CORRUPT: ... */
INTDEF NONNULL((1, 2)) unsigned int
NOTHROW_NCX(CC libdi_debugline_scanunit)(di_debugline_unit_t const *__restrict self,
                                         di_debugline_info_t *__restrict result,
                                         uintptr_t module_relative_pc);



DECL_END

#endif /* !GUARD_LIBDEBUGINFO_DEBUG_LINE_H */
