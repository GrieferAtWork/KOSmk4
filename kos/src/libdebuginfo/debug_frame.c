/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif(x -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_LIBDEBUGINFO_DEBUG_FRAME_C
#define GUARD_LIBDEBUGINFO_DEBUG_FRAME_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <kos/types.h>

#include <libdebuginfo/debug_frame.h>

#include "debug_frame.h"

#define libuw_unwind_fde_load libdi_unwind_fde_load_df
#define libuw_unwind_fde_scan libdi_unwind_fde_scan_df


/* Re-use the  implementation from  `libunwind.so', but  re-
 * compile with `DEBUG_FRAME' to get `.debug_frame' support. */
#define DEBUG_FRAME 1
#ifndef __INTELLISENSE__
#undef CC
#undef CASE
#undef CORRUPT
#undef ERROR
#undef ERRORF
#undef TRACE
#undef DOTRACE

#include "../libunwind/api.h"
#include "../libunwind/dwarf.h"
#undef CC
#undef dwarf_decode_sleb128
#undef dwarf_decode_uleb128
#undef dwarf_decode_pointer
#define CC LIBDEBUGINFO_CC

#define FIND_SPECIFIC_ADDRESS
#include "../libunwind/eh_frame-find_fde.c.inl"
/**/
#include "../libunwind/eh_frame-find_fde.c.inl"
#endif /* !__INTELLISENSE__ */

DECL_BEGIN

/* Export the .debug_frame scanner API */
DEFINE_PUBLIC_ALIAS(unwind_fde_load_df, libdi_unwind_fde_load_df);
DEFINE_PUBLIC_ALIAS(unwind_fde_scan_df, libdi_unwind_fde_scan_df);

DECL_END

#endif /* !GUARD_LIBDEBUGINFO_DEBUG_FRAME_C */
