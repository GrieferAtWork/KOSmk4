/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_EXCEPT_H
#define GUARD_KERNEL_CORE_ARCH_I386_EXCEPT_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <libdebuginfo/dwarf.h>
#include <libunwind/eh_frame.h>
#include <libunwind/unwind.h>

DECL_BEGIN

struct ucpustate;

/* BEGIN::: GCC DATA LAYOUT */
struct ATTR_PACKED gcc_lsda_callsite {
	/* Exception handling in GCC works as follows:
	 *   - If a function doesn't have a .cfi_personality function,
	 *     exceptions will simply be propagated through it.
	 *   - If a function does have a `__gxx_personality_v0' as a personality
	 *     function, its callsite table is searched for the associated unwind PC.
	 *      - If the unwind PC wasn't found, then the program must terminate (in our case: panic())
	 *      - If the unwind PC was found as a valid call-site,
	 *        then the associated action must be taken. */
	uintptr_t gcs_start;       /* [ENCODING(:gl_callsite_enc)]
	                            * Offset from the LSDA landing base to the first instruction byte that is
	                            * covered by this exception handler. (i.e. to the start of guarded assembly) */
	uintptr_t gcs_size;        /* [ENCODING(:gl_callsite_enc)]
	                            * The number of contiguous bytes of text guarded, starting at `gcs_start' */
	uintptr_t gcs_handler;     /* [ENCODING(:gl_callsite_enc)]
	                            * Offset from the LSDA landing base to the first instruction apart of the
	                            * exception handler's executing block. (i.e. the start of the catch-handler)
	                            * If there is no handler, this field is ZERO(0)
	                            * NOTE: Dependent on architecture, certain registers must be filled with
	                            *       exception-related data before the runtime may jump to this location. */
	uintptr_t gcs_action;      /* [ENCODING(:gl_callsite_enc)]
	                            * The action to take???
	                            * When zero, don't perform any action. (continue propagating the exception)
	                            * Otherwise, this is 1+ a byte offset into the action table?? */
};
struct ATTR_PACKED gcc_lsda {
	/* Format the the GCC LanguageSpecificData pointed to by `unwind_fde_struct::f_lsdaaddr' */
	u8              gl_landing_enc;  /* Encoding used for `gl_landing_pad' (One of `DW_EH_PE_*') */
	uintptr_t       gl_landing_pad;  /* [exists_if(gl_landing_enc != DW_EH_PE_omit)]
	                                  * [ENCODING(gl_landing_enc)] Base address of the landing pad
	                                  * When this field doesn't exist, `unwind_fde_struct::f_pcstart' will be used instead.
	                                  * -> This field usually doesn't exist. */
	u8              gl_typetab_enc;  /* Encoding used for fields in the type-table (One of `DW_EH_PE_*') */
	dwarf_uleb128_t gl_typetab_off;  /* [exists_if(gl_typetab_enc != DW_EH_PE_omit)]
	                                  * Offset from the next field to the start of the types
	                                  * table used for matching exception types. */
	u8              gl_callsite_enc; /* Encoding used for fields in the call-site table (One of `DW_EH_PE_*') */
	dwarf_uleb128_t gl_callsite_siz; /* The size of the call-site table (in bytes) */
	/* -- This is where the callsite table goes. */
	struct gcc_lsda_callsite gl_callsites[1]; /* [* = AUTO(sizeof(.) == gl_callsite_siz)] */
	/* -- This is where the type table goes. */
};
/* END::: GCC DATA LAYOUT */



DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_EXCEPT_H */
