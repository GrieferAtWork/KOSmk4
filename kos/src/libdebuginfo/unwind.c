/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif(x -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBDEBUGINFO_UNWIND_C
#define GUARD_LIBDEBUGINFO_UNWIND_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <libdebuginfo/unwind.h>
#include <libunwind/errno.h> /* `UNWIND_*' error codes. */
#include <libunwind/unwind.h>

#include "unwind.h"

#ifndef REF
#define REF __REF
#endif /* !REF */

#ifndef HAVE_UNWIND_FOR_DEBUG_EXTERNALLY
#include <assert.h>
#include <dlfcn.h>
#include <stdbool.h>
#include <stddef.h>

#include "debug_frame.h"

DECL_BEGIN


#ifndef __KERNEL__
PRIVATE ATTR_NOINLINE NONNULL((2, 4)) unwind_errno_t CC
unwind_through_debug_frame(void const *absolute_pc,
                           unwind_getreg_t reg_getter, void const *reg_getter_arg,
                           unwind_setreg_t reg_setter, void *reg_setter_arg) {
	unwind_errno_t result = UNWIND_NO_FRAME;
	REF void *mod;
	/* Lookup the backing module for the given `absolute_pc' */
	mod = dlgethandle(absolute_pc, DLGETHANDLE_FINCREF);
	if (mod) {
		REF struct dl_section *sect;
		/* Check for a `.debug_frame' section */
		sect = dllocksection(mod, ".debug_frame",
		                     DLLOCKSECTION_FNORMAL);
		if (sect) {
			void *debug_frame_data;
			size_t debug_frame_size;
			uintptr_t loadaddr;
			loadaddr = dlmodulebase(mod);

			/* Support for a compressed .debug_frame! */
			debug_frame_data = dlinflatesection(sect, &debug_frame_size);
			if (debug_frame_data) {
				unwind_fde_t fde;
				/* Scan the .debug_frame section for an FDE matching `absolute_pc' */
				result = libdi_unwind_fde_scan_df((byte_t const *)debug_frame_data,
				                                  (byte_t const *)debug_frame_data + debug_frame_size,
				                                  (uintptr_t)absolute_pc - loadaddr,
				                                  &fde,
				                                  sizeof(void *));
				if (result == UNWIND_SUCCESS) {
					unwind_cfa_state_t cfa;

					/* Must adjust for load address. */
					fde.f_pcstart = (void *)((uintptr_t)fde.f_pcstart + loadaddr);
					fde.f_pcend   = (void *)((uintptr_t)fde.f_pcend + loadaddr);
					assert(fde.f_persofun == NULL);
					assert(fde.f_lsdaaddr == NULL);

					/* Found the FDE. - Now to execute it's program! */
					result = unwind_fde_exec(&fde, &cfa, absolute_pc);
					if unlikely(result == UNWIND_SUCCESS) {
						/* And finally: Apply register modifications. */
						result = unwind_cfa_apply(&cfa, &fde, absolute_pc,
						                          reg_getter, reg_getter_arg,
						                          reg_setter, reg_setter_arg);
					}
				}
			}
			dlunlocksection(sect);
		}
		dlclose(mod);
	}
	return result;
}
#endif /* !__KERNEL__ */


/* Same as the regular unwind(3) (from libunwind.so), however (if configured),
 * this  one also handles the case where `absolute_pc' points into user-space,
 * allowing user-space text locations to be correctly unwound.
 * NOTE: This function should only be used when printing tracebacks for
 *       debugging purposes, but _NEVER_  for the purpose of  something
 *       like exception unwinding!
 * To improve the success-rate of unwinding, this function does a number of things:
 *   - Try to make use of the regular, old `unwind(3)' from `libunwind.so'
 *   - Make use of DWARF `.debug_frame' debug information (if present)
 *   - Inspect/emulate  the underlying program  text to detect patterns
 *     that lead to known return instructions. Though this is only done
 *     if implemented and supported for the hosting architecture.
 * Also note that in kernel-space, once the kernel has been poisoned, no
 * additional user-space module information can be loaded, and unwinding
 * for user-space location for which the kernel doesn't already know how
 * to unwind them will fail with `UNWIND_NO_FRAME'.
 * @return: * : One of `UNWIND_*' (UNWIND_SUCCESS on success, other values on failure) */
INTERN NONNULL((2, 4)) unwind_errno_t CC
libdi_unwind_for_debug(void const *absolute_pc,
                       unwind_getreg_t reg_getter, void const *reg_getter_arg,
                       unwind_setreg_t reg_setter, void *reg_setter_arg) {
	unwind_errno_t result;

	/* Try the regular unwind(3) function (from `libunwind.so'). */
	result = unwind(absolute_pc,
	                reg_getter, reg_getter_arg,
	                reg_setter, reg_setter_arg);

	/* Supporting .debug_frame for kernel-space drivers doesn't make any  sense,
	 * since  the same information  also exists in .eh_frame,  and since the KOS
	 * kernel is written in C++, and requires .eh_frame-based unwind information
	 * support  to have exceptions work correctly, no kernel driver should exist
	 * that doesn't have a .eh_frame section which already contains _all_ of the
	 * information we could ever need.
	 * As such, only parse .debug_frame while in user-space! */
#ifndef __KERNEL__
	if (result == UNWIND_NO_FRAME) {
		/* Try to make use of `.debug_frame' */
		result = unwind_through_debug_frame(absolute_pc,
		                                    reg_getter, reg_getter_arg,
		                                    reg_setter, reg_setter_arg);
	}
#endif /* !__KERNEL__ */

	if (result == UNWIND_NO_FRAME) {
		/* TODO: Try to inspect/emulate the underlying program text
		 *       to  unwind until the next return-like instruction. */
	}
	return result;
}


DEFINE_PUBLIC_ALIAS(unwind_for_debug, libdi_unwind_for_debug);

DECL_END
#endif /* !HAVE_UNWIND_FOR_DEBUG_EXTERNALLY */

#endif /* !GUARD_LIBDEBUGINFO_UNWIND_C */
