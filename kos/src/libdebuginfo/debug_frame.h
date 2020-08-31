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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBDEBUGINFO_DEBUG_FRAME_H
#define GUARD_LIBDEBUGINFO_DEBUG_FRAME_H 1

#include "api.h"
/**/

#include <kos/types.h>

#include <libdebuginfo/debug_frame.h>

DECL_BEGIN

/* Load the next debug_frame function descriptor from `*PDEBUG_FRAME_READER', which
 * must either be a pointer to the start of the `.debug_frame' section, or be the
 * value written back to `*PDEBUG_FRAME_READER' after a previous call to `unwind_fde_load_df()'.
 * @return: UNWIND_SUCCESS:  Successfully read the next FDE entry.
 * @return: UNWIND_NO_FRAME: Failed to read an FDE entry (Assume EOF) */
INTDEF NONNULL((1, 2, 3, 4)) unsigned int
NOTHROW_NCX(CC libdi_unwind_fde_load_df)(byte_t **__restrict pdebug_frame_reader,
                                         byte_t *__restrict debug_frame_start,
                                         byte_t *__restrict debug_frame_end,
                                         unwind_fde_t *__restrict result,
                                         uint8_t sizeof_address);

/* Same as `unwind_fde_load_df()', but quickly search for and return the
 * FDE descriptor containing the given `ABSOLUTE_PC' text address.
 * @assume(!return || RESULT->f_pcstart <= ABSOLUTE_PC);
 * @assume(!return || RESULT->f_pcend > ABSOLUTE_PC);
 * @return: UNWIND_SUCCESS:  Found the FDE entry associated with `ABSOLUTE_PC'.
 * @return: UNWIND_NO_FRAME: Failed to read an FDE entry (Assume EOF) */
INTDEF NONNULL((1, 2, 4)) unsigned int
NOTHROW_NCX(CC libdi_unwind_fde_scan_df)(byte_t *__restrict debug_frame_start,
                                         byte_t *__restrict debug_frame_end,
                                         void *absolute_pc,
                                         unwind_fde_t *__restrict result,
                                         uint8_t sizeof_address);

DECL_END

#endif /* !GUARD_LIBDEBUGINFO_DEBUG_FRAME_H */
