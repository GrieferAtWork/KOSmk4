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
#ifndef GUARD_LIBUNWIND_CFI_H
#define GUARD_LIBUNWIND_CFI_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <libunwind/cfi.h>
#include <libunwind/errno.h>

DECL_BEGIN


/* Execute the CFI expression loaded into the given unwind-emulator  `self'.
 * Upon  success, `self->ue_stacksz' will have been updated to the new stack
 * size, allowing the caller to read the expression's return values from it.
 * NOTE: `unwind_emulator_exec_autostack()'  behaves the same as `unwind_emulator_exec()', but
 *       will automatically  allocated/free the  expression stack  upon entry/return,  pushing
 *       `pentry_stack_top' upon entry, and storing the last stack-entry in `*pexit_stack_top'
 *       before returning  (if  no  such value  exists,  `UNWIND_EMULATOR_NO_RETURN_VALUE'  is
 *       returned). If no  stack of sufficient  size could  be allocated (or  if the  required
 *       stack size  is absurdly  large),  `UNWIND_EMULATOR_STACK_OVERFLOW' will  be  returned
 *       instead.
 * @param: pentry_stack_top:      A value to-be pushed onto the stack upon entry (or NULL).
 * @param: pexit_stack_top:       A value to-be popped off of the stack upon exit (or NULL).
 * @param: pexit_stack_top_const: Same as `pexit_stack_top', but casted into a constant.
 * @return: UNWIND_SUCCESS:          ...
 * @return: UNWIND_INVALID_REGISTER: ...
 * @return: UNWIND_SEGFAULT:         ...
 * @return: UNWIND_BADALLOC:         ...
 * @return: UNWIND_EMULATOR_*:       ... */
INTDEF NONNULL((1)) unwind_errno_t CC
libuw_unwind_emulator_exec(unwind_emulator_t *__restrict self);
INTDEF NONNULL((1)) unwind_errno_t CC
libuw_unwind_emulator_exec_autostack(unwind_emulator_t *__restrict self,
                                     unwind_ste_t const *pentry_stack_top,
                                     unwind_ste_t *pexit_stack_top,
                                     uintptr_t *pexit_stack_top_const);



/* Return a pointer to the next unwind instruction following `unwind_pc'
 * -> Useful for dumping unwind instruction without having to take care
 *    of handling all possible instruction  (after all: CFI has a  CISC
 *    instruction set with variable-length instructions)
 * @param: addrsize: Size of a target address.
 * @param: ptrsize:  Size of a DWARF pointer (4 for 32-bit dwarf; 8 for 64-bit dwarf).
 * @return: NULL: The instruction at `unwind_pc' wasn't recognized. */
INTDEF ATTR_PURE WUNUSED NCX byte_t const *
NOTHROW_NCX(CC libuw_unwind_instruction_succ)(NCX byte_t const *unwind_pc,
                                              uint8_t addrsize, uint8_t ptrsize);

/* Return a pointer to a CFI expression that is applicable for `module_relative_pc'
 * If no such expression exists, return `NULL' instead. */
INTDEF WUNUSED NONNULL((1)) ATTR_OUT(5) NCX byte_t const *
NOTHROW_NCX(CC libuw_debuginfo_location_select)(di_debuginfo_location_t const *__restrict self,
                                                uintptr_t cu_base,
                                                uintptr_t module_relative_pc,
                                                uint8_t addrsize,
                                                size_t *__restrict p_expr_length);

/* Load the effective l-value address of `self' into `*p_addr':
 *   UNWIND_STE_CONSTANT:     Write-back s_uconst or s_sconst
 *   UNWIND_STE_STACKVALUE:   Write-back s_uconst or s_sconst
 *   UNWIND_STE_REGISTER:     Write-back REGISTER[s_register] + s_regoffset
 *   UNWIND_STE_REGPOINTER:   Write-back REGISTER[s_register]       (NOTE: Technically, this case isn't allowed)
 *   UNWIND_STE_RW_LVALUE:    Write-back s_lvalue
 *   UNWIND_STE_RO_LVALUE:    Write-back s_lvalue
 * @return: UNWIND_SUCCESS:                      Success.
 * @return: UNWIND_INVALID_REGISTER:             Invalid register referenced by `self'
 * @return: UNWIND_EMULATOR_ILLEGAL_INSTRUCTION: Invalid stack-value type in `self' */
INTDEF NONNULL((1, 2)) ATTR_OUT(4) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_ste_addr)(unwind_ste_t const *__restrict self,
                                      unwind_getreg_t regget, void const *regget_arg,
                                      NCX void **__restrict p_addr);

/* Read/write bit-wise data to/from an unwind stack-entry location.
 * @param: self:           The unwind STE-element to/from which to read/write.
 * @param: regget:         Register getter.
 * @param: regget_arg:     Register getter argument.
 * @param: regset:         Register setter.
 * @param: regset_arg:     Register setter argument.
 * @param: dst:            Destination memory buffer.
 * @param: src:            Source memory buffer.
 * @param: num_bits:       The # of bits to read/write to/from `dst' or `src'
 * @param: src_left_shift: The # of leading bits to leave unchanged in the source.
 * @param: dst_left_shift: The # of leading bits to leave unchanged in the destination.
 * @return: UNWIND_SUCCESS:                      Success.
 * @return: UNWIND_INVALID_REGISTER:             Invalid register referenced by `self'
 * @return: UNWIND_EMULATOR_ILLEGAL_INSTRUCTION: Invalid stack-value type in `self'
 * @return: UNWIND_SEGFAULT:                     Attempted to access faulty memory. */
INTDEF NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_ste_read)(unwind_ste_t const *__restrict self, uint8_t addrsize,
                                      unwind_getreg_t regget, void const *regget_arg,
                                      NCX void *dst, size_t num_bits,
                                      size_t dst_left_shift, size_t src_left_shift);
INTDEF NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_ste_write)(unwind_ste_t const *__restrict self, uint8_t addrsize,
                                       /*[1..1]*/ unwind_getreg_t regget, void const *regget_arg,
                                       /*[0..1]*/ unwind_setreg_t regset, void *regset_arg,
                                       NCX void const *src, size_t num_bits,
                                       size_t dst_left_shift, size_t src_left_shift);

/* Read/Write the value associated with a given debuginfo location descriptor.
 * @param: self:                  The debug info location descriptor (s.a. libdebuginfo.so)
 * @param: sectinfo:              Emulator section  information  (to-be  filled in  by  the  caller)
 *                                Optionally,  this argument may  be `NULL', however  if this is the
 *                                case, the function may fail in cases where it would have otherwise
 *                                succeeded.
 * @param: regget:                Register getter callback.
 * @param: regget_arg:            Register getter callback argument.
 * @param: regset:                Register setter callback.
 * @param: regset_arg:            Register setter callback argument.
 * @param: cu:                    Associated compilation unit debug info (or NULL).
 *                                When  non-NULL, the following fields may be used:
 *                                  - cu->cu_ranges.r_startpc
 *                                  - cu->cu_addr_base
 * @param: module_relative_pc:    The module-relative program counter, to-be used to select
 *                                the   appropriate  expression  within  a  location  list.
 * @param: module_addroffset:     The load address of the associated module. (addend for DW_OP_addr)
 * @param: buf:                   Source/target buffer containing the value read from,
 *                                or written to the location expression.
 * @param: bufsize:               Size of the given `buf' in bytes.
 * @param: pnum_written_bits:     The number of _BITS_ (not bytes!) read from the location expression,
 *                                and written to the given `buf'  (any trailing bits of buffer  memory
 *                                that weren't written will be filled with `0' upon success)
 * @param: pnum_read_bits:        The number of _BITS_ (not bytes!) written to the location expression,
 *                                and read from the given `buf'.
 * @param: frame_base_expression: The expression used to calculate the frame-base address (or NULL if unknown)
 * @param: objaddr:               The address of the base-object (used e.g. for structure member expressions)
 * @param: addrsize:              Size of an address (defined by the associated CU, and usually == sizeof(void *))
 * @param: ptrsize:               DWARF pointer size (4 for 32-bit dwarf; 8 for 64-bit dwarf)
 * @return: * :                               One of `UNWIND_*'
 * @return: UNWIND_EMULATOR_NOT_WRITABLE:     Attempted to write to a read-only location expression.
 * @return: UNWIND_EMULATOR_BUFFER_TOO_SMALL: The given `bufsize' is too small.
 * @return: UNWIND_EMULATOR_NO_FUNCTION:      The associated location list is undefined for `module_relative_pc' */
INTDEF NONNULL((1, 3, 10)) unwind_errno_t CC
libuw_debuginfo_location_getvalue(di_debuginfo_location_t const *__restrict self,
                                  unwind_emulator_sections_t const *sectinfo,
                                  unwind_getreg_t regget, void *regget_arg,
                                  struct di_debuginfo_compile_unit_simple_struct const *cu,
                                  uintptr_t module_relative_pc, uintptr_t module_addroffset,
                                  NCX void *buf, size_t bufsize,
                                  size_t *__restrict pnum_written_bits,
                                  di_debuginfo_location_t const *frame_base_expression,
                                  NCX void const *objaddr, uint8_t addrsize, uint8_t ptrsize);
INTDEF NONNULL((1, 3, 5, 12)) unwind_errno_t CC
libuw_debuginfo_location_setvalue(di_debuginfo_location_t const *__restrict self,
                                  unwind_emulator_sections_t const *sectinfo,
                                  unwind_getreg_t regget, void *regget_arg,
                                  unwind_setreg_t regset, void *regset_arg,
                                  struct di_debuginfo_compile_unit_simple_struct const *cu,
                                  uintptr_t module_relative_pc, uintptr_t module_addroffset,
                                  NCX void const *buf, size_t bufsize,
                                  size_t *__restrict pnum_read_bits,
                                  di_debuginfo_location_t const *frame_base_expression,
                                  NCX void *objaddr, uint8_t addrsize, uint8_t ptrsize);


DECL_END

#endif /* !GUARD_LIBUNWIND_CFI_H */
