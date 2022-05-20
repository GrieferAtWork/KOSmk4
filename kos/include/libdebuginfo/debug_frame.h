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
#ifndef _LIBDEBUGINFO_DEBUG_FRAME_H
#define _LIBDEBUGINFO_DEBUG_FRAME_H 1

#include "api.h"
/**/

#include <bits/types.h>

#include <libunwind/eh_frame.h>

/* The .debug_frame section is (somewhat) different, such that we need
 * our own  versions of  `unwind_fde_scan()' and  `unwind_fde_load()'.
 * These .debug_frame-versions are exported from libdebuginfo.so under
 * the names `unwind_fde_scan_df()' and `unwind_fde_load_df()' */

#ifdef __CC__
__DECL_BEGIN

/* Load the  next  debug_frame  function  descriptor  from  `*pdebug_frame_reader',  which
 * must either be a pointer  to the start of the  `.debug_frame' section, or be the  value
 * written back to `*pdebug_frame_reader' after a previous call to `unwind_fde_load_df()'.
 * @return: UNWIND_SUCCESS:  Successfully read the next FDE entry.
 * @return: UNWIND_NO_FRAME: Failed to read an FDE entry (Assume EOF) */
typedef __ATTR_NONNULL_T((1, 2, 3, 4)) unsigned int
(LIBDEBUGINFO_CC *PUNWIND_FDE_LOAD_DF)(__byte_t **__restrict __pdebug_frame_reader,
                                       __byte_t *__restrict __debug_frame_start,
                                       __byte_t *__restrict __debug_frame_end,
                                       unwind_fde_t *__restrict __result,
                                       __uint8_t __sizeof_address);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 2, 3, 4)) unsigned int
__NOTHROW_NCX(LIBDEBUGINFO_CC unwind_fde_load_df)(__byte_t **__restrict __pdebug_frame_reader,
                                                  __byte_t *__restrict __debug_frame_start,
                                                  __byte_t *__restrict __debug_frame_end,
                                                  unwind_fde_t *__restrict __result,
                                                  __uint8_t __sizeof_address);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */

/* Same as `unwind_fde_load_df()', but quickly search for and return the
 * FDE  descriptor  containing  the  given  `absolute_pc'  text address.
 * @assume(!return || result->f_pcstart <= absolute_pc);
 * @assume(!return || result->f_pcend > absolute_pc);
 * @return: UNWIND_SUCCESS:  Found the FDE entry associated with `absolute_pc'.
 * @return: UNWIND_NO_FRAME: Failed to read an FDE entry (Assume EOF) */
typedef __ATTR_NONNULL_T((1, 2, 4)) unsigned int
(LIBDEBUGINFO_CC *PUNWIND_FDE_SCAN_DF)(__byte_t const *__restrict __debug_frame_start,
                                       __byte_t const *__restrict __debug_frame_end,
                                       void const *__absolute_pc,
                                       unwind_fde_t *__restrict __result,
                                       __uint8_t __sizeof_address);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 2, 4)) unsigned int
__NOTHROW_NCX(LIBDEBUGINFO_CC unwind_fde_scan_df)(__byte_t const *__restrict __debug_frame_start,
                                                  __byte_t const *__restrict __debug_frame_end,
                                                  void const *__absolute_pc,
                                                  unwind_fde_t *__restrict __result,
                                                  __uint8_t __sizeof_address);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBDEBUGINFO_DEBUG_FRAME_H */
