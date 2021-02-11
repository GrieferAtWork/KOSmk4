/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBUNWIND_CFI_H
#define GUARD_LIBUNWIND_CFI_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <libunwind/cfi.h>

DECL_BEGIN


/* Execute the CFI expression loaded into the given unwind-emulator  `SELF'.
 * Upon  success, `SELF->ue_stacksz' will have been updated to the new stack
 * size, allowing the caller to read the expression's return values from it.
 * NOTE: `unwind_emulator_exec_autostack()' behaves the same as `unwind_emulator_exec()',
 *        but will automatically allocated/free the expression stack upon entry/return, pushing
 *       `PENTRY_STACK_TOP' upon entry, and storing the last stack-entry in `*PEXIT_STACK_TOP'
 *        before returning (if no such value exists, `UNWIND_EMULATOR_NO_RETURN_VALUE' is returned).
 *        If no stack  of sufficient  size could  be allocated  (or if  the required  stack size  is
 *        absurdly large), `UNWIND_EMULATOR_STACK_OVERFLOW' will be returned instead.
 * @param: PENTRY_STACK_TOP:      A value to-be pushed onto the stack upon entry (or NULL).
 * @param: PEXIT_STACK_TOP:       A value to-be popped off of the stack upon exit (or NULL).
 * @param: PEXIT_STACK_TOP_CONST: Same as `PEXIT_STACK_TOP', but casted into a constant.
 * @return: UNWIND_SUCCESS:          ...
 * @return: UNWIND_INVALID_REGISTER: ...
 * @return: UNWIND_SEGFAULT:         ...
 * @return: UNWIND_BADALLOC:         ...
 * @return: UNWIND_EMULATOR_*:       ... */
INTDEF NONNULL((1)) unsigned int CC
libuw_unwind_emulator_exec(unwind_emulator_t *__restrict self);
INTDEF NONNULL((1)) unsigned int CC
libuw_unwind_emulator_exec_autostack(unwind_emulator_t *__restrict self,
                                     unwind_ste_t const *pentry_stack_top,
                                     unwind_ste_t *pexit_stack_top,
                                     uintptr_t *pexit_stack_top_const);



/* Return a pointer to the next unwind instruction following `UNWIND_PC'
 * -> Useful for dumping unwind instruction without having to take care
 *    of handling all possible instruction  (after all: CFI has a  CISC
 *    instruction set with variable-length instructions)
 * @param: ADDRSIZE: Size of a target address.
 * @param: PTRSIZE:  Size of a DWARF pointer (4 for 32-bit dwarf; 8 for 64-bit dwarf).
 * @return: NULL: The instruction at `UNWIND_PC' wasn't recognized. */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) byte_t const *
NOTHROW_NCX(CC libuw_unwind_instruction_succ)(byte_t const *__restrict unwind_pc,
                                              uint8_t addrsize, uint8_t ptrsize);

/* Return a pointer to a CFI expression that is applicable for `CU_BASE + MODULE_RELATIVE_PC'
 * If no such expression exists, return `NULL' instead. */
INTDEF WUNUSED NONNULL((1, 5)) byte_t const *
NOTHROW_NCX(CC libuw_debuginfo_location_select)(di_debuginfo_location_t const *__restrict self,
                                                uintptr_t cu_base,
                                                uintptr_t module_relative_pc,
                                                uint8_t addrsize,
                                                size_t *__restrict pexpr_length);

/* Load the effective l-value address of `SELF' into `*PADDR':
 *   UNWIND_STE_CONSTANT:     Write-back s_uconst or s_sconst
 *   UNWIND_STE_STACKVALUE:   Write-back s_uconst or s_sconst
 *   UNWIND_STE_REGISTER:     Write-back REGISTER[s_register] + s_regoffset
 *   UNWIND_STE_REGPOINTER:   Write-back REGISTER[s_register]       (NOTE: Technically, this case isn't allowed)
 *   UNWIND_STE_RW_LVALUE:    Write-back s_lvalue
 *   UNWIND_STE_RO_LVALUE:    Write-back s_lvalue
 * @return: UNWIND_SUCCESS:                      Success.
 * @return: UNWIND_INVALID_REGISTER:             Invalid register referenced by `SELF'
 * @return: UNWIND_EMULATOR_ILLEGAL_INSTRUCTION: Invalid stack-value type in `SELF' */
INTDEF NONNULL((1, 2, 4)) unsigned int
NOTHROW_NCX(CC libuw_unwind_ste_addr)(unwind_ste_t const *__restrict self,
                                      unwind_getreg_t regget, void const *regget_arg,
                                      void **__restrict paddr);

/* Read/write bit-wise data to/from an unwind stack-entry location.
 * @param: SELF:           The unwind STE-element to/from which to read/write.
 * @param: REGGET:         Register getter.
 * @param: REGGET_ARG:     Register getter argument.
 * @param: REGSET:         Register setter.
 * @param: REGSET_ARG:     Register setter argument.
 * @param: DST:            Destination memory buffer.
 * @param: SRC:            Source memory buffer.
 * @param: NUM_BITS:       The # of bits to read/write to/from `DST' or `SRC'
 * @param: SRC_LEFT_SHIFT: The # of leading bits to leave unchanged in the source.
 * @param: DST_LEFT_SHIFT: The # of leading bits to leave unchanged in the destination.
 * @return: UNWIND_SUCCESS:                      Success.
 * @return: UNWIND_INVALID_REGISTER:             Invalid register referenced by `SELF'
 * @return: UNWIND_EMULATOR_ILLEGAL_INSTRUCTION: Invalid stack-value type in `SELF'
 * @return: UNWIND_SEGFAULT:                     Attempted to access faulty memory. */
INTDEF NONNULL((1, 2, 4)) unsigned int
NOTHROW_NCX(CC libuw_unwind_ste_read)(unwind_ste_t const *__restrict self,
                                      unwind_getreg_t regget, void const *regget_arg,
                                      void *__restrict dst, size_t num_bits,
                                      unsigned int dst_left_shift, unsigned int src_left_shift);
INTDEF NONNULL((1, 2, 6)) unsigned int
NOTHROW_NCX(CC libuw_unwind_ste_write)(unwind_ste_t const *__restrict self,
                                       /*[1..1]*/ unwind_getreg_t regget, void const *regget_arg,
                                       /*[0..1]*/ unwind_setreg_t regset, void *regset_arg,
                                       void const *__restrict src, size_t num_bits,
                                       unsigned int dst_left_shift, unsigned int src_left_shift);

/* Read/Write the value associated with a given debuginfo location descriptor.
 * @param: SELF:                  The debug info location descriptor (s.a. libdebuginfo.so)
 * @param: SECTINFO:              Emulator section  information  (to-be  filled in  by  the  caller)
 *                                Optionally,  this argument may  be `NULL', however  if this is the
 *                                case, the function may fail in cases where it would have otherwise
 *                                succeeded.
 * @param: REGGET:                Register getter callback.
 * @param: REGGET_ARG:            Register getter callback argument.
 * @param: REGSET:                Register setter callback.
 * @param: REGSET_ARG:            Register setter callback argument.
 * @param: CU:                    Associated compilation unit debug info (or NULL).
 *                                When  non-NULL, the following fields may be used:
 *                                  - CU->cu_ranges.r_startpc
 *                                  - CU->cu_addr_base
 * @param: MODULE_RELATIVE_PC:    The module-relative program counter, to-be used to select
 *                                the   appropriate  expression  within  a  location  list.
 * @param: MODULE_ADDROFFSET:     The load address of the associated module. (addend for DW_OP_addr)
 * @param: BUF:                   Source/target buffer containing the value read from,
 *                                or written to the location expression.
 * @param: BUFSIZE:               Size of the given `BUF' in bytes.
 * @param: PNUM_WRITTEN_BITS:     The number of _BITS_ (not bytes!) read from the location expression,
 *                                and written to the given `BUF'  (any trailing bits of buffer  memory
 *                                that weren't written will be filled with `0' upon success)
 * @param: PNUM_READ_BITS:        The number of _BITS_ (not bytes!) written to the location expression,
 *                                and read from the given `BUF'.
 * @param: FRAME_BASE_EXPRESSION: The expression used to calculate the frame-base address (or NULL if unknown)
 * @param: OBJADDR:               The address of the base-object (used e.g. for structure member expressions)
 * @param: ADDRSIZE:              Size of an address (defined by the associated CU, and usually == sizeof(void *))
 * @param: PTRSIZE:               DWARF pointer size (4 for 32-bit dwarf; 8 for 64-bit dwarf)
 * @return: * :                               One of `UNWIND_*'
 * @return: UNWIND_EMULATOR_NOT_WRITABLE:     Attempted to write to a read-only location expression.
 * @return: UNWIND_EMULATOR_BUFFER_TOO_SMALL: The given `BUFSIZE' is too small.
 * @return: UNWIND_EMULATOR_NO_FUNCTION:      The associated location list is undefined for `MODULE_RELATIVE_PC' */
INTDEF NONNULL((1, 3, 8, 10)) unsigned int CC
libuw_debuginfo_location_getvalue(di_debuginfo_location_t const *__restrict self,
                                  unwind_emulator_sections_t const *sectinfo,
                                  unwind_getreg_t regget, void *regget_arg,
                                  struct di_debuginfo_compile_unit_simple_struct const *cu,
                                  uintptr_t module_relative_pc, uintptr_t module_addroffset,
                                  void *__restrict buf, size_t bufsize,
                                  size_t *__restrict pnum_written_bits,
                                  di_debuginfo_location_t const *frame_base_expression,
                                  void const *objaddr, uint8_t addrsize, uint8_t ptrsize);
INTDEF NONNULL((1, 3, 5, 10, 12)) unsigned int CC
libuw_debuginfo_location_setvalue(di_debuginfo_location_t const *__restrict self,
                                  unwind_emulator_sections_t const *sectinfo,
                                  unwind_getreg_t regget, void *regget_arg,
                                  unwind_setreg_t regset, void *regset_arg,
                                  struct di_debuginfo_compile_unit_simple_struct const *cu,
                                  uintptr_t module_relative_pc, uintptr_t module_addroffset,
                                  void const *__restrict buf, size_t bufsize,
                                  size_t *__restrict pnum_read_bits,
                                  di_debuginfo_location_t const *frame_base_expression,
                                  void *objaddr, uint8_t addrsize, uint8_t ptrsize);


DECL_END

#endif /* !GUARD_LIBUNWIND_CFI_H */
