/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_LIBC_EXCEPT_LIBUNWIND_H
#define GUARD_LIBC_LIBC_EXCEPT_LIBUNWIND_H 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <atomic.h>
#include <stddef.h>

#include <libunwind/dwarf.h>
#include <libunwind/eh_frame.h>
#include <libunwind/register.h>
#include <libunwind/unwind.h>

#ifndef __KERNEL__
DECL_BEGIN

INTDEF void /*                          */ *pdyn_libunwind;
INTDEF PUNWIND_FDE_FIND /*               */ pdyn_unwind_fde_find;
INTDEF PUNWIND_GETREG_EXCEPT_REGISTER_STATE pdyn_unwind_getreg_except_register_state;
INTDEF PUNWIND_SETREG_EXCEPT_REGISTER_STATE pdyn_unwind_setreg_except_register_state;
INTDEF PUNWIND_FDE_EXEC /*               */ pdyn_unwind_fde_exec;
INTDEF PUNWIND_CFA_APPLY /*              */ pdyn_unwind_cfa_apply;
INTDEF PUNWIND_FDE_EXEC_CFA /*           */ pdyn_unwind_fde_exec_cfa;
INTDEF PUNWIND_FDE_CALCULATE_CFA /*      */ pdyn_unwind_fde_calculate_cfa;
INTDEF PUNWIND_FDE_LANDING_EXEC /*       */ pdyn_unwind_fde_landing_exec;
INTDEF PUNWIND_CFA_LANDING_APPLY /*      */ pdyn_unwind_cfa_landing_apply;
INTDEF PDWARF_DECODE_POINTER /*          */ pdyn_dwarf_decode_pointer;
INTDEF PDWARF_DECODE_ULEB128 /*          */ pdyn_dwarf_decode_uleb128;
INTDEF PDWARF_DECODE_SLEB128 /*          */ pdyn_dwarf_decode_sleb128;
#ifndef CFI_UNWIND_NO_SIGFRAME_COMMON_UNCOMMON_REGISTERS
INTDEF PUNWIND_FDE_SIGFRAME_EXEC /*      */ pdyn_unwind_fde_sigframe_exec;
INTDEF PUNWIND_CFA_SIGFRAME_APPLY /*     */ pdyn_unwind_cfa_sigframe_apply;
#endif /* !CFI_UNWIND_NO_SIGFRAME_COMMON_UNCOMMON_REGISTERS */

#define unwind_fde_find                     (*pdyn_unwind_fde_find)
#define unwind_getreg_except_register_state (*pdyn_unwind_getreg_except_register_state)
#define unwind_setreg_except_register_state (*pdyn_unwind_setreg_except_register_state)
#define unwind_fde_exec                     (*pdyn_unwind_fde_exec)
#define unwind_cfa_apply                    (*pdyn_unwind_cfa_apply)
#define unwind_fde_exec_cfa                 (*pdyn_unwind_fde_exec_cfa)
#define unwind_fde_calculate_cfa            (*pdyn_unwind_fde_calculate_cfa)
#define unwind_fde_landing_exec             (*pdyn_unwind_fde_landing_exec)
#define unwind_cfa_landing_apply            (*pdyn_unwind_cfa_landing_apply)
#define unwind_fde_sigframe_exec            (*pdyn_unwind_fde_sigframe_exec)
#define unwind_cfa_sigframe_apply           (*pdyn_unwind_cfa_sigframe_apply)
#define dwarf_decode_pointer                (*pdyn_dwarf_decode_pointer)
#define dwarf_decode_uleb128                (*pdyn_dwarf_decode_uleb128)
#define dwarf_decode_sleb128                (*pdyn_dwarf_decode_sleb128)

INTDEF ATTR_NOINLINE bool LIBCCALL libc_except_libunwind_tryinitialize(void);
INTDEF ATTR_NOINLINE void LIBCCALL libc_except_libunwind_initialize(void);

#define ENSURE_LIBUNWIND_LOADED() \
	(void)(atomic_read(&pdyn_libunwind) != NULL || (libc_except_libunwind_initialize(), 0))
#define TRY_ENSURE_LIBUNWIND_LOADED() \
	(atomic_read(&pdyn_libunwind) != NULL || libc_except_libunwind_tryinitialize())

DECL_END
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_LIBC_EXCEPT_LIBUNWIND_H */
