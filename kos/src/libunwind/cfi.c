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
#ifndef GUARD_LIBUNWIND_CFI_C
#define GUARD_LIBUNWIND_CFI_C 1
#define _KOS_SOURCE 1
#define _KOS_KERNEL_SOURCE 1

#include "api.h"
/**/

#include "cfi.h"

#include <hybrid/compiler.h>

#include <hybrid/byteorder.h>
#include <hybrid/unaligned.h>

#include <kos/bits/thread.h>
#include <kos/except.h>
#include <kos/types.h>

#include <alloca.h>
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include <libdebuginfo/debug_info.h>
#include <libdebuginfo/dwarf.h>
#include <libunwind/cfi.h>
#include <libunwind/eh_frame.h>

#include "eh_frame.h"

#ifndef __KERNEL__
#include <hybrid/atomic.h>

#include <dlfcn.h>
#include <malloc.h>
#else /* !__KERNEL__ */
#include <kernel/except.h>
#include <sched/task.h> /* get_stack_avail() */
#endif /* !__KERNEL__ */


/* In kernel-space, memory accesses can also cause E_WOULDBLOCK to be thrown
 * when preemption is disabled. - Handle that error like we do SEGFAULTS. */
#ifdef __KERNEL__
#define WAS_SEGFAULT_THROWN() (was_thrown(E_SEGFAULT) || was_thrown(E_WOULDBLOCK))
#else /* __KERNEL__ */
#define WAS_SEGFAULT_THROWN() was_thrown(E_SEGFAULT)
#endif /* !__KERNEL__ */


DECL_BEGIN

#define EXCEPTION_INFO_SAVE()         \
	struct exception_info old_except; \
	memcpy(&old_except, error_info(), sizeof(struct exception_info))
#define EXCEPTION_INFO_LOAD() \
	memcpy(error_info(), &old_except, sizeof(struct exception_info))


PRIVATE WUNUSED NONNULL((2)) bool
NOTHROW(CC guarded_readb)(uint8_t *ptr, uintptr_t *__restrict result) {
	uint8_t value;
	EXCEPTION_INFO_SAVE();
	TRY {
		value = *ptr;
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW(); /* This will panic() because we're NOTHROW */
		goto err_segfault;
	}
	*result = (uintptr_t)value;
	return true;
err_segfault:
	EXCEPTION_INFO_LOAD();
	return false;
}

PRIVATE WUNUSED NONNULL((2)) bool
NOTHROW(CC guarded_readw)(uint16_t *ptr, uintptr_t *__restrict result) {
	uint16_t value;
	EXCEPTION_INFO_SAVE();
	TRY {
		value = UNALIGNED_GET16(ptr);
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW(); /* This will panic() because we're NOTHROW */
		goto err_segfault;
	}
	*result = (uintptr_t)value;
	return true;
err_segfault:
	EXCEPTION_INFO_LOAD();
	return false;
}

PRIVATE WUNUSED NONNULL((2)) bool
NOTHROW(CC guarded_readl)(uint32_t *ptr, uintptr_t *__restrict result) {
	uint32_t value;
	EXCEPTION_INFO_SAVE();
	TRY {
		value = UNALIGNED_GET32(ptr);
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW(); /* This will panic() because we're NOTHROW */
		goto err_segfault;
	}
	*result = (uintptr_t)value;
	return true;
err_segfault:
	EXCEPTION_INFO_LOAD();
	return false;
}

#if __SIZEOF_POINTER__ > 4
PRIVATE WUNUSED NONNULL((2)) bool
NOTHROW(CC guarded_readq)(uint64_t *ptr, uintptr_t *__restrict result) {
	uint64_t value;
	EXCEPTION_INFO_SAVE();
	TRY {
		value = UNALIGNED_GET64(ptr);
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW(); /* This will panic() because we're NOTHROW */
		goto err_segfault;
	}
	*result = (uintptr_t)value;
	return true;
err_segfault:
	EXCEPTION_INFO_LOAD();
	return false;
}
#define guarded_readptr guarded_readq
#else /* __SIZEOF_POINTER__ > 4 */
#define guarded_readptr guarded_readl
#endif /* __SIZEOF_POINTER__ <= 4 */

INTERN WUNUSED bool
NOTHROW(CC guarded_memcpy)(void *dst, void const *src, size_t num_bytes) {
	EXCEPTION_INFO_SAVE();
	TRY {
		memcpy(dst, src, num_bytes);
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW(); /* This will panic() because we're NOTHROW */
		goto err_segfault;
	}
	return true;
err_segfault:
	EXCEPTION_INFO_LOAD();
	return false;
}



#ifndef __KERNEL__
PRIVATE void *pdyn_libdebuginfo                                         = NULL;
PRIVATE PDEBUGINFO_CU_ABBREV_FINI     pdyn_debuginfo_cu_abbrev_fini     = NULL;
PRIVATE PDEBUGINFO_CU_PARSER_LOADUNIT pdyn_debuginfo_cu_parser_loadunit = NULL;
PRIVATE PDEBUGINFO_CU_PARSER_SKIPFORM pdyn_debuginfo_cu_parser_skipform = NULL;
PRIVATE PDEBUGINFO_CU_PARSER_GETEXPR  pdyn_debuginfo_cu_parser_getexpr  = NULL;
#define debuginfo_cu_abbrev_fini      (*pdyn_debuginfo_cu_abbrev_fini)
#define debuginfo_cu_parser_loadunit  (*pdyn_debuginfo_cu_parser_loadunit)
#define debuginfo_cu_parser_skipform  (*pdyn_debuginfo_cu_parser_skipform)
#define debuginfo_cu_parser_getexpr   (*pdyn_debuginfo_cu_parser_getexpr)

PRIVATE __attribute__((__destructor__))
void libuw_unload_libdebuginfo(void) {
	/* pdyn_libdebuginfo.so was loaded by us, unload it when our library gets destroyed. */
	if (pdyn_libdebuginfo && pdyn_libdebuginfo != (void *)-1)
		dlclose(pdyn_libdebuginfo);
}

PRIVATE WUNUSED bool
NOTHROW_NCX(CC libuw_load_libdebuginfo)(void) {
	void *pdyn_libdebuginfo;
again:
	if (pdyn_libdebuginfo == (void *)-1)
		return false; /* Cannot be loaded... */
	pdyn_libdebuginfo = dlopen(LIBDEBUGINFO_LIBRARY_NAME, RTLD_LOCAL);
	if (!pdyn_libdebuginfo)
		goto err;
	*(void **)&pdyn_debuginfo_cu_parser_getexpr  = dlsym(pdyn_libdebuginfo, "debuginfo_cu_parser_getexpr");
	if unlikely(!pdyn_debuginfo_cu_parser_getexpr)
		goto err_close;
	*(void **)&pdyn_debuginfo_cu_parser_skipform = dlsym(pdyn_libdebuginfo, "debuginfo_cu_parser_skipform");
	if unlikely(!pdyn_debuginfo_cu_parser_skipform)
		goto err_close;
	*(void **)&pdyn_debuginfo_cu_parser_loadunit = dlsym(pdyn_libdebuginfo, "debuginfo_cu_parser_loadunit");
	if unlikely(!pdyn_debuginfo_cu_parser_loadunit)
		goto err_close;
	COMPILER_WRITE_BARRIER();
	/* This one has to be loaded last, since it's
	 * used as the fast-pass for already-loaded */
	*(void **)&pdyn_debuginfo_cu_abbrev_fini = dlsym(pdyn_libdebuginfo, "debuginfo_cu_abbrev_fini");
	if unlikely(!pdyn_debuginfo_cu_abbrev_fini)
		goto err_close;
	if (!ATOMIC_CMPXCH(pdyn_libdebuginfo, NULL, pdyn_libdebuginfo)) {
		dlclose(pdyn_libdebuginfo);
		if (ATOMIC_READ(pdyn_libdebuginfo) == (void *)-1)
			return false;
	}
	return true;
err_close:
	dlclose(pdyn_libdebuginfo);
err:
	if (!ATOMIC_CMPXCH(pdyn_libdebuginfo, NULL, (void *)-1))
		goto again;
	return false;
}
#endif /* !__KERNEL__ */

PRIVATE NONNULL((1, 2)) unsigned int CC
libuw_unwind_emulator_make_const(unwind_emulator_t *__restrict self,
                                 unwind_ste_t *__restrict ste) {
	if (ste->s_type != UNWIND_STE_CONSTANT) {
		if (ste->s_type == UNWIND_STE_REGISTER) {
			union {
				uintptr_t p;
				byte_t buf[CFI_UNWIND_REGISTER_MAXSIZE];
			} regval;
			if unlikely(!(*self->ue_regget)(self->ue_regget_arg, ste->s_register, regval.buf))
				ERRORF(err_invalid_register, "ste->s_register = %u\n", (unsigned int)ste->s_register);
			ste->s_uconst = regval.p + ste->s_regoffset;
		} else if (ste->s_type == UNWIND_STE_RW_LVALUE ||
		           ste->s_type == UNWIND_STE_RO_LVALUE) {
			if (ste->s_lsize >= sizeof(uintptr_t)) {
				if unlikely(!guarded_readptr((uintptr_t *)ste->s_lvalue, &ste->s_uconst))
					ERROR(err_segfault);
#if __SIZEOF_POINTER__ > 4
			} else if (self->ue_addrsize >= 4) {
				if unlikely(!guarded_readl((uint32_t *)ste->s_lvalue, &ste->s_uconst))
					ERROR(err_segfault);
#endif /* __SIZEOF_POINTER__ > 4 */
			} else if (self->ue_addrsize >= 2) {
				if unlikely(!guarded_readw((uint16_t *)ste->s_lvalue, &ste->s_uconst))
					ERROR(err_segfault);
			} else {
				if unlikely(!guarded_readb((uint8_t *)ste->s_lvalue, &ste->s_uconst))
					ERROR(err_segfault);
			}
		} else if (ste->s_type == UNWIND_STE_STACKVALUE) {
			ste->s_type = UNWIND_STE_CONSTANT;
		} else {
			/* Shouldn't get here... */
			ERROR(err_illegal_instruction);
		}
		ste->s_type = UNWIND_STE_CONSTANT;
	}
	return UNWIND_SUCCESS;
err_invalid_register:
	return UNWIND_INVALID_REGISTER;
err_illegal_instruction:
	return UNWIND_EMULATOR_ILLEGAL_INSTRUCTION;
err_segfault:
	return UNWIND_SEGFAULT;
}

PRIVATE NONNULL((1)) unsigned int CC
libuw_unwind_emulator_make_top_const(unwind_emulator_t *__restrict self) {
	unwind_ste_t *ste;
	assert(self->ue_stacksz >= 1);
	ste = &self->ue_stack[self->ue_stacksz - 1];
	return libuw_unwind_emulator_make_const(self, ste);
}

INTERN ATTR_NOINLINE NONNULL((1, 2)) unsigned int CC
libuw_unwind_call_function(unwind_emulator_t *__restrict self,
                           byte_t *__restrict component_pointer) {
	di_debuginfo_cu_parser_t parser;
	di_debuginfo_cu_abbrev_t abbrev;
	byte_t *di_reader;
	unsigned int di_error;
	di_debuginfo_component_attrib_t attr;
	di_debuginfo_cu_parser_sections_t sect;
	if unlikely(!self->ue_sectinfo)
		ERROR(err_invalid_function);
#ifndef __KERNEL__
	/* Lazily load pdyn_libdebuginfo.so, so we can parser the .debug_info section */
	if (!pdyn_debuginfo_cu_abbrev_fini && unlikely(libuw_load_libdebuginfo()))
		ERROR(err_invalid_function);
	COMPILER_READ_BARRIER();
#endif /* !__KERNEL__ */
	di_reader                   = self->ue_sectinfo->ues_debug_info_start;
	sect.cps_debug_abbrev_start = self->ue_sectinfo->ues_debug_abbrev_start;
	sect.cps_debug_abbrev_end   = self->ue_sectinfo->ues_debug_abbrev_end;
	sect.cps_debug_str_start    = NULL;
	sect.cps_debug_str_end      = NULL;
	sect.cps_debug_loc_start    = self->ue_sectinfo->ues_debug_loc_start;
	sect.cps_debug_loc_end      = self->ue_sectinfo->ues_debug_loc_end;
	di_error = debuginfo_cu_parser_loadunit(&di_reader, self->ue_sectinfo->ues_debug_info_end,
	                                        &sect, &parser, &abbrev, component_pointer);
	if unlikely(di_error != DEBUG_INFO_ERROR_SUCCESS)
		ERROR(err_invalid_function);
	/* Load attributes of the component, and look for `DW_AT_location'.
	 * If present, it describes the CFA expression which we're supposed
	 * to execute. - Otherwise, ignore and return immediately. */
	DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, &parser) {
		unsigned int result;
		di_debuginfo_location_t expr;
		size_t length;
		byte_t *old_pc_start, *old_pc_end;
		if (attr.dica_name != DW_AT_location)
			continue;
		/* Found it! */
		if unlikely(!debuginfo_cu_parser_getexpr(&parser, attr.dica_form, &expr))
			ERROR(err_invalid_function_abbrev);
		/* Select the appropriate function. */
		self->ue_pc = libuw_debuginfo_location_select(&expr,
		                                              self->ue_module_base,
		                                              self->ue_module_relative_pc,
		                                              self->ue_addrsize,
		                                              &length);
		if unlikely(!self->ue_pc)
			ERROR(err_invalid_function_abbrev);
		old_pc_start      = self->ue_pc_start;
		old_pc_end        = self->ue_pc_end;
		self->ue_pc_start = self->ue_pc;
		self->ue_pc_end   = self->ue_pc + length;
		/* Execute the selected function. */
		result            = libuw_unwind_emulator_exec(self);
		self->ue_pc_start = old_pc_start;
		self->ue_pc_end   = old_pc_end;
		return result;
	}
	debuginfo_cu_abbrev_fini(&abbrev);
	return UNWIND_SUCCESS;
err_invalid_function_abbrev:
	debuginfo_cu_abbrev_fini(&abbrev);
err_invalid_function:
	return UNWIND_EMULATOR_INVALID_FUNCTION;
}


PRIVATE ATTR_NOINLINE NONNULL((1)) unsigned int CC
libuw_unwind_emulator_calculate_cfa(unwind_emulator_t *__restrict self) {
	unwind_fde_t fde;
	unwind_cfa_value_t cfa;
	unsigned int error;
	union {
		byte_t buf[CFI_REGISTER_SIZE(CFI_UNWIND_REGISTER_PC)];
		void *pc;
	} pc_buf;
	if unlikely(!self->ue_sectinfo)
		goto err_no_cfa;
	/* Load the current program counter position. */
	if unlikely(!(*self->ue_regget)(self->ue_regget_arg,
	                                CFI_UNWIND_REGISTER_PC,
	                                pc_buf.buf))
		ERROR(err_invalid_register);
	/* Search for an FDE descriptor for the program counter within the .eh_frame section. */
	error = libuw_unwind_fde_scan(self->ue_sectinfo->ues_eh_frame_start,
	                              self->ue_sectinfo->ues_eh_frame_end,
	                              pc_buf.pc,
	                              &fde,
	                              self->ue_addrsize);
	if unlikely(error != UNWIND_SUCCESS) {
		if (error == UNWIND_NO_FRAME)
			goto err_no_cfa;
		goto done;
	}
	/* Evaluate the FDE program to extract the CFA descriptor. */
	error = libuw_unwind_fde_exec_cfa(&fde, &cfa, pc_buf.pc);
	if unlikely(error != UNWIND_SUCCESS)
		goto done;
	/* Calculate the absolute address of the associated CFA,
	 * and store the result in `self->ue_call_frame_cfa' */
	error = libuw_unwind_cfa_calculate_cfa(&cfa,
	                                       self->ue_regget,
	                                       self->ue_regget_arg,
	                                       &self->ue_call_frame_cfa);
done:
	return error;
err_invalid_register:
	return UNWIND_INVALID_REGISTER;
err_no_cfa:
	return UNWIND_EMULATOR_NO_CFA;
}

PRIVATE NONNULL((1, 3)) void CC
copy_bits(byte_t *__restrict dst_base, unsigned int dst_bit_offset,
          byte_t const *__restrict src_base, unsigned int src_bit_offset,
          size_t num_bits) {
	TRACE("copy_bits(%p,%u,%p,%u,%Iu)\n",
	      dst_base, dst_bit_offset,
	      src_base, src_bit_offset,
	      num_bits);
	while (num_bits) {
		uint8_t remaining;
		uint8_t src_value, remaining_temp;
		src_base += src_bit_offset / 8;
		src_bit_offset &= 7;
		remaining = 8 - src_bit_offset;
		if (remaining > num_bits)
			remaining = num_bits;
		src_value      = *src_base >> src_bit_offset;
		remaining_temp = remaining;
		while (remaining_temp) {
			uint8_t avail;
			dst_base += dst_bit_offset / 8;
			dst_bit_offset &= 7;
			avail = 8 - dst_bit_offset;
			if (avail > remaining_temp)
				avail = remaining_temp;
			*dst_base &= ~(((1 << avail) - 1) << dst_bit_offset);
			*dst_base |= (src_value & ((1 << avail) - 1)) << dst_bit_offset;
			dst_bit_offset += avail;
			remaining_temp -= avail;
			src_value >>= avail;
		}
		src_bit_offset += remaining;
		num_bits -= remaining;
	}
}

PRIVATE ATTR_NOINLINE NONNULL((1, 2)) unsigned int CC
libuw_unwind_emulator_write_to_piece(unwind_emulator_t *__restrict self,
                                     unwind_ste_t const *__restrict ste,
                                     uintptr_t num_bits,
                                     unsigned int target_left_shift) {
	assert(UNWIND_STE_ISWRITABLE(ste->s_type));
	if unlikely(((self->ue_piecebits + num_bits + 7) / 8) > self->ue_piecesiz)
		ERROR(err_buffer_too_small);
	if (ste->s_type == UNWIND_STE_REGISTER) {
		byte_t buf[CFI_UNWIND_REGISTER_MAXSIZE];
		if unlikely(!self->ue_regset)
			ERROR(err_not_writable);
		if unlikely(num_bits > CFI_REGISTER_SIZE(ste->s_register) * 8)
			num_bits = CFI_REGISTER_SIZE(ste->s_register) * 8;
		/* Write to a register. */
		if (target_left_shift == 0 &&
		    num_bits == CFI_REGISTER_SIZE(ste->s_register) * 8) {
			/* Write whole register. */
		} else {
			if unlikely(!(*self->ue_regget)(self->ue_regget_arg,
			                                ste->s_register,
			                                buf))
				ERROR(err_invalid_register);
			UNALIGNED_SET((uintptr_t *)buf, UNALIGNED_GET((uintptr_t *)buf) - ste->s_regoffset);
		}
		copy_bits(buf,
		          target_left_shift,
		          self->ue_piecebuf,
		          self->ue_piecebits,
		          num_bits);
		UNALIGNED_SET((uintptr_t *)buf, UNALIGNED_GET((uintptr_t *)buf) + ste->s_regoffset);
		/* Update the register value. */
		if unlikely(!(*self->ue_regset)(self->ue_regset_arg,
		                                ste->s_register,
		                                buf))
			ERROR(err_invalid_register);
	} else {
		/* Copy data into the l-value. */
		TRY {
			copy_bits(ste->s_lvalue,
			          target_left_shift,
			          self->ue_piecebuf,
			          self->ue_piecebits,
			          num_bits);
		} EXCEPT {
			if (!WAS_SEGFAULT_THROWN())
				RETHROW();
			ERROR(err_segfault);
		}
	}
	/* Update the number of consumed piece bits. */
	self->ue_piecebits += num_bits;
	return UNWIND_SUCCESS;
err_segfault:
	return UNWIND_SEGFAULT;
err_invalid_register:
	return UNWIND_INVALID_REGISTER;
err_buffer_too_small:
	return UNWIND_EMULATOR_BUFFER_TOO_SMALL;
err_not_writable:
	return UNWIND_EMULATOR_NOT_WRITABLE;
}

PRIVATE ATTR_NOINLINE NONNULL((1, 2)) unsigned int CC
libuw_unwind_emulator_read_from_piece(unwind_emulator_t *__restrict self,
                                      unwind_ste_t const *__restrict ste,
                                      uintptr_t num_bits,
                                      unsigned int target_left_shift) {
	switch (ste->s_type) {

	case UNWIND_STE_CONSTANT:
	case UNWIND_STE_STACKVALUE: {
		uintptr_t temp;
		temp = ste->s_uconst;
		temp >>= target_left_shift;
		while (num_bits) {
			uintptr_t part;
			part = sizeof(temp) * 8;
			if (part > num_bits)
				part = num_bits;
			copy_bits(self->ue_piecebuf,
			          self->ue_piecebits,
			          (byte_t const *)&temp,
			          0,
			          part);
			/* Update the number of stored piece bits. */
			self->ue_piecebits += part;
			num_bits -= part;
			temp >>= part;
		}
	}	break;

	case UNWIND_STE_REGISTER: {
		byte_t buf[CFI_UNWIND_REGISTER_MAXSIZE];
		size_t max_bits;
		memset(buf, 0, sizeof(buf));
		if unlikely(!(*self->ue_regget)(self->ue_regget_arg, ste->s_register, buf))
			ERROR(err_invalid_register);
		UNALIGNED_SET((uintptr_t *)buf, UNALIGNED_GET((uintptr_t *)buf) + ste->s_regoffset);
		if unlikely(target_left_shift >= (sizeof(buf) * 8)) {
			max_bits = 0;
		} else {
			max_bits = (sizeof(buf) * 8) - target_left_shift;
			if (max_bits > num_bits)
				max_bits = num_bits;
		}
		/* Copy in-bounds register data. */
		copy_bits(self->ue_piecebuf,
		          self->ue_piecebits,
		          buf,
		          target_left_shift,
		          max_bits);
		self->ue_piecebits += max_bits;
		num_bits -= max_bits;
		while (num_bits) {
			/* Fill out-of-bounds register data with all zeros. */
			memset(buf, 0, sizeof(buf));
			max_bits = sizeof(buf) * 8;
			if (max_bits > num_bits)
				max_bits = num_bits;
			copy_bits(self->ue_piecebuf,
			          self->ue_piecebits,
			          buf,
			          0,
			          max_bits);
			self->ue_piecebits += max_bits;
			num_bits -= max_bits;
		}
	}	break;

	case UNWIND_STE_RO_LVALUE:
	case UNWIND_STE_RW_LVALUE:
		copy_bits(self->ue_piecebuf,
		          self->ue_piecebits,
		          ste->s_lvalue,
		          target_left_shift,
		          num_bits);
		/* Update the number of stored piece bits. */
		self->ue_piecebits += num_bits;
		break;

	default:
		ERRORF(err_illegal_instruction, "ste->s_type = %I8u\n", ste->s_type);
	}
	return UNWIND_SUCCESS;
err_invalid_register:
	return UNWIND_INVALID_REGISTER;
err_illegal_instruction:
	return UNWIND_EMULATOR_ILLEGAL_INSTRUCTION;
}


/* Execute the CFI expression loaded into the given unwind-emulator `SELF'.
 * Upon success, `SELF->ue_stacksz' will have been updated to the new stack
 * size, allowing the caller to read the expression's return values from it.
 * NOTE: `unwind_emulator_exec_autostack()' behaves the same as `unwind_emulator_exec()',
 *        but will automatically allocated/free the expression stack upon entry/return, pushing
 *       `PENTRY_STACK_TOP' upon entry, and storing the last stack-entry in `*PEXIT_STACK_TOP'
 *        before returning (if no such value exists, `UNWIND_EMULATOR_NO_RETURN_VALUE' is returned).
 *        If no stack of sufficient size could be allocated (or if the required stack size is
 *        absurdly large), `UNWIND_EMULATOR_STACK_OVERFLOW' will be returned instead.
 * @param: PENTRY_STACK_TOP:      A value to-be pushed onto the stack upon entry (or NULL).
 * @param: PEXIT_STACK_TOP:       A value to-be popped off of the stack upon exit (or NULL).
 * @param: PEXIT_STACK_TOP_CONST: Same as `PEXIT_STACK_TOP', but casted into a constant.
 * @return: UNWIND_SUCCESS:          ...
 * @return: UNWIND_INVALID_REGISTER: ...
 * @return: UNWIND_SEGFAULT:         ...
 * @return: UNWIND_BADALLOC:         ...
 * @return: UNWIND_EMULATOR_*:       ... */
INTERN ATTR_NOINLINE NONNULL((1)) unsigned int CC
libuw_unwind_emulator_exec(unwind_emulator_t *__restrict self) {
	byte_t *pc     = self->ue_pc;
	size_t stacksz = self->ue_stacksz;
	byte_t opcode;
	/*again:*/
	while (pc < self->ue_pc_end) {
		opcode = *pc++;
again_switch_opcode:
		assert(stacksz < self->ue_stackmax);
		switch (opcode) {

#define TOP    self->ue_stack[stacksz - 1]
#define SECOND self->ue_stack[stacksz - 2]
#define THIRD  self->ue_stack[stacksz - 3]

		CASE(DW_OP_addr) {
			uintptr_t value;
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			if (self->ue_addrsize >= sizeof(uintptr_t)) {
				value = UNALIGNED_GET((uintptr_t *)pc);
#if __SIZEOF_POINTER__ > 4
			} else if (self->ue_addrsize >= 4) {
				value = (uintptr_t)UNALIGNED_GET32((uint32_t *)pc);
#endif /* __SIZEOF_POINTER__ > 4 */
			} else if (self->ue_addrsize >= 2) {
				value = (uintptr_t)UNALIGNED_GET16((uint16_t *)pc);
			} else {
				value = (uintptr_t) * (uint8_t *)pc;
			}
			pc += self->ue_addrsize;
			self->ue_stack[stacksz].s_type   = UNWIND_STE_CONSTANT;
			self->ue_stack[stacksz].s_uconst = value;
			++stacksz;
		}	break;

		CASE(DW_OP_deref)
			if unlikely(!stacksz)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT) {
do_make_top_const:
				if (TOP.s_type == UNWIND_STE_REGISTER) {
					union {
						uintptr_t p;
						byte_t buf[CFI_UNWIND_REGISTER_MAXSIZE];
					} regval;
					if unlikely(!(*self->ue_regget)(self->ue_regget_arg, TOP.s_register, regval.buf))
						ERROR(err_invalid_register);
					TOP.s_uconst = regval.p + TOP.s_regoffset;
				} else if (TOP.s_type == UNWIND_STE_RW_LVALUE ||
				           TOP.s_type == UNWIND_STE_RO_LVALUE) {
					if (TOP.s_lsize >= sizeof(uintptr_t)) {
						if unlikely(!guarded_readptr((uintptr_t *)TOP.s_lvalue, &TOP.s_uconst))
							ERROR(err_segfault);
#if __SIZEOF_POINTER__ > 4
					} else if (self->ue_addrsize >= 4) {
						if unlikely(!guarded_readl((uint32_t *)TOP.s_lvalue, &TOP.s_uconst))
							ERROR(err_segfault);
#endif /* __SIZEOF_POINTER__ > 4 */
					} else if (self->ue_addrsize >= 2) {
						if unlikely(!guarded_readw((uint16_t *)TOP.s_lvalue, &TOP.s_uconst))
							ERROR(err_segfault);
					} else {
						if unlikely(!guarded_readb((uint8_t *)TOP.s_lvalue, &TOP.s_uconst))
							ERROR(err_segfault);
					}
				} else if (TOP.s_type == UNWIND_STE_STACKVALUE) {
					TOP.s_type = UNWIND_STE_CONSTANT;
				} else {
					/* Shouldn't get here... */
					ERROR(err_illegal_instruction);
				}
				TOP.s_type = UNWIND_STE_CONSTANT;
				goto again_switch_opcode;
			}
			/* Turn a constant into an l-value. */
			TOP.s_type  = UNWIND_STE_RW_LVALUE;
			TOP.s_lsize = self->ue_addrsize;
			break;

#define DEFINE_PUSH_CONSTANT(opcode, field, expr, size)           \
		CASE(opcode)                                              \
			if unlikely(stacksz >= self->ue_stackmax)             \
				ERROR(err_stack_overflow);                        \
			self->ue_stack[stacksz].s_type = UNWIND_STE_CONSTANT; \
			self->ue_stack[stacksz].field  = expr;                \
			pc += size;                                           \
			++stacksz;                                            \
			break;
		DEFINE_PUSH_CONSTANT(DW_OP_const1u, s_uconst, (uintptr_t) * (uint8_t *)pc, 1)
		DEFINE_PUSH_CONSTANT(DW_OP_const1s, s_sconst, (intptr_t) * (int8_t *)pc, 1)
		DEFINE_PUSH_CONSTANT(DW_OP_const2u, s_uconst, (uintptr_t)UNALIGNED_GET16((uint16_t *)pc), 2)
		DEFINE_PUSH_CONSTANT(DW_OP_const2s, s_sconst, (intptr_t)(int16_t)UNALIGNED_GET16((uint16_t *)pc), 2)
		DEFINE_PUSH_CONSTANT(DW_OP_const4u, s_uconst, (uintptr_t)UNALIGNED_GET32((uint32_t *)pc), 4)
		DEFINE_PUSH_CONSTANT(DW_OP_const4s, s_sconst, (intptr_t)(int32_t)UNALIGNED_GET32((uint32_t *)pc), 4)
#if __SIZEOF_POINTER__ > 4
		DEFINE_PUSH_CONSTANT(DW_OP_const8u, s_uconst, (uintptr_t)UNALIGNED_GET64((uint64_t *)pc), 8)
		DEFINE_PUSH_CONSTANT(DW_OP_const8s, s_sconst, (intptr_t)(int64_t)UNALIGNED_GET64((uint64_t *)pc), 8)
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		DEFINE_PUSH_CONSTANT(DW_OP_const8u, s_uconst, (uintptr_t)UNALIGNED_GET32((uint32_t *)pc), 8)
		DEFINE_PUSH_CONSTANT(DW_OP_const8s, s_sconst, (intptr_t)(int32_t)UNALIGNED_GET32((uint32_t *)pc), 8)
#else /* ... */
		DEFINE_PUSH_CONSTANT(DW_OP_const8u, s_uconst, (uintptr_t)UNALIGNED_GET32((uint32_t *)pc + 1), 8)
		DEFINE_PUSH_CONSTANT(DW_OP_const8s, s_sconst, (intptr_t)(int32_t)UNALIGNED_GET32((uint32_t *)pc + 1), 8)
#endif /* !... */
#undef DEFINE_PUSH_CONSTANT

		CASE(DW_OP_constu)
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			self->ue_stack[stacksz].s_type   = UNWIND_STE_CONSTANT;
			self->ue_stack[stacksz].s_uconst = (uintptr_t)dwarf_decode_uleb128(&pc);
			++stacksz;
			break;

		CASE(DW_OP_consts)
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			self->ue_stack[stacksz].s_type   = UNWIND_STE_CONSTANT;
			self->ue_stack[stacksz].s_sconst = (intptr_t)dwarf_decode_sleb128(&pc);
			++stacksz;
			break;

		CASE(DW_OP_dup)
			if unlikely(stacksz < 1)
				ERROR(err_stack_underflow);
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			self->ue_stack[stacksz] = TOP;
			++stacksz;
			break;

		CASE(DW_OP_drop)
			if unlikely(!stacksz)
				ERROR(err_stack_underflow);
			--stacksz;
			break;

		CASE(DW_OP_over)
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			self->ue_stack[stacksz] = SECOND;
			++stacksz;
			break;

		CASE(DW_OP_pick) {
			uint8_t offset;
			offset = *(uint8_t *)pc;
			if unlikely(offset >= stacksz)
				ERROR(err_stack_underflow);
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			pc += 1;
			self->ue_stack[stacksz] = self->ue_stack[(stacksz - 1) - offset];
			++stacksz;
		}	break;

		CASE(DW_OP_swap) {
			unwind_ste_t temp;
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			temp   = SECOND;
			SECOND = TOP;
			TOP    = temp;
		}	break;

		CASE(DW_OP_rot) {
			unwind_ste_t temp;
			if unlikely(stacksz < 3)
				ERROR(err_stack_underflow);
			temp   = TOP;
			TOP    = SECOND;
			SECOND = THIRD;
			THIRD  = temp;
		}	break;

		CASE(DW_OP_xderef)
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			SECOND.s_type   = UNWIND_STE_RW_LVALUE;
			SECOND.s_lvalue = (byte_t *)TOP.s_uconst;
			SECOND.s_lsize  = self->ue_addrsize;
			--stacksz;
			break;

		CASE(DW_OP_abs)
			if unlikely(stacksz < 1)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			if (TOP.s_sconst < 0)
				TOP.s_sconst = -TOP.s_sconst;
			break;

		CASE(DW_OP_and)
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			if (SECOND.s_type != UNWIND_STE_CONSTANT) {
do_make_second_const:
				if (SECOND.s_type == UNWIND_STE_REGISTER) {
					union {
						uintptr_t p;
						byte_t buf[CFI_UNWIND_REGISTER_MAXSIZE];
					} regval;
					if unlikely(!(*self->ue_regget)(self->ue_regget_arg, SECOND.s_register, regval.buf))
						ERROR(err_invalid_register);
					SECOND.s_uconst = regval.p + SECOND.s_regoffset;
				} else if (SECOND.s_type == UNWIND_STE_RW_LVALUE ||
				           SECOND.s_type == UNWIND_STE_RO_LVALUE) {
					if (SECOND.s_lsize >= sizeof(uintptr_t)) {
						if unlikely(!guarded_readptr((uintptr_t *)SECOND.s_lvalue, &SECOND.s_uconst))
							ERROR(err_segfault);
#if __SIZEOF_POINTER__ > 4
					} else if (self->ue_addrsize >= 4) {
						if unlikely(!guarded_readl((uint32_t *)SECOND.s_lvalue, &SECOND.s_uconst))
							ERROR(err_segfault);
#endif /* __SIZEOF_POINTER__ > 4 */
					} else if (self->ue_addrsize >= 2) {
						if unlikely(!guarded_readw((uint16_t *)SECOND.s_lvalue, &SECOND.s_uconst))
							ERROR(err_segfault);
					} else {
						if unlikely(!guarded_readb((uint8_t *)SECOND.s_lvalue, &SECOND.s_uconst))
							ERROR(err_segfault);
					}
				} else if (SECOND.s_type == UNWIND_STE_STACKVALUE) {
					SECOND.s_type = UNWIND_STE_CONSTANT;
				} else {
					/* Shouldn't get here... */
					ERROR(err_illegal_instruction);
				}
				SECOND.s_type = UNWIND_STE_CONSTANT;
				goto again_switch_opcode;
			}
			SECOND.s_uconst &= TOP.s_uconst;
			--stacksz;
			break;

		CASE(DW_OP_div)
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			if (SECOND.s_type != UNWIND_STE_CONSTANT)
				goto do_make_second_const;
			if unlikely(TOP.s_uconst == 0)
				goto err_divide_by_zero;
			SECOND.s_uconst /= TOP.s_uconst;
			--stacksz;
			break;

		CASE(DW_OP_minus)
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			if (SECOND.s_type != UNWIND_STE_CONSTANT &&
			    SECOND.s_type != UNWIND_STE_REGISTER)
				goto do_make_second_const;
			SECOND.s_uconst -= TOP.s_uconst;
			--stacksz;
			break;

		CASE(DW_OP_mod)
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			if (SECOND.s_type != UNWIND_STE_CONSTANT)
				goto do_make_second_const;
			if unlikely(TOP.s_uconst == 0)
				ERROR(err_divide_by_zero);
			SECOND.s_uconst %= TOP.s_uconst;
			--stacksz;
			break;

		CASE(DW_OP_mul)
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			if (SECOND.s_type != UNWIND_STE_CONSTANT)
				goto do_make_second_const;
			SECOND.s_uconst *= TOP.s_uconst;
			--stacksz;
			break;

		CASE(DW_OP_neg)
			if unlikely(stacksz < 1)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			TOP.s_sconst = -TOP.s_sconst;
			break;

		CASE(DW_OP_not)
			if unlikely(stacksz < 1)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			TOP.s_uconst = ~TOP.s_uconst;
			break;

		CASE(DW_OP_or)
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			if (SECOND.s_type != UNWIND_STE_CONSTANT)
				goto do_make_second_const;
			SECOND.s_uconst |= TOP.s_uconst;
			--stacksz;
			break;

		CASE(DW_OP_plus)
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			if (SECOND.s_type != UNWIND_STE_CONSTANT &&
			    SECOND.s_type != UNWIND_STE_REGISTER)
				goto do_make_second_const;
			SECOND.s_uconst += TOP.s_uconst;
			--stacksz;
			break;

		CASE(DW_OP_plus_uconst)
			if unlikely(stacksz < 1)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT &&
			    TOP.s_type != UNWIND_STE_REGISTER)
				goto do_make_top_const;
			TOP.s_uconst += dwarf_decode_uleb128(&pc);
			break;

		CASE(DW_OP_shl)
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			if (SECOND.s_type != UNWIND_STE_CONSTANT)
				goto do_make_second_const;
			SECOND.s_uconst <<= TOP.s_uconst;
			--stacksz;
			break;

		CASE(DW_OP_shr)
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			if (SECOND.s_type != UNWIND_STE_CONSTANT)
				goto do_make_second_const;
			SECOND.s_uconst >>= TOP.s_uconst;
			--stacksz;
			break;

		CASE(DW_OP_shra)
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			if (SECOND.s_type != UNWIND_STE_CONSTANT)
				goto do_make_second_const;
			SECOND.s_sconst >>= TOP.s_uconst;
			--stacksz;
			break;

		CASE(DW_OP_xor)
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			if (SECOND.s_type != UNWIND_STE_CONSTANT)
				goto do_make_second_const;
			SECOND.s_uconst ^= TOP.s_uconst;
			--stacksz;
			break;

		CASE(DW_OP_skip) {
			int16_t offset;
			offset = (int16_t)UNALIGNED_GET16((uint16_t *)pc);
			pc += 2;
			if (offset < 0) {
				if unlikely(!self->ue_bjmprem)
					ERROR(err_loop);
				--self->ue_bjmprem;
			}
			pc += offset;
			if unlikely(pc < self->ue_pc_start ||
			            pc >= self->ue_pc_end) {
				if likely(pc == self->ue_pc_end)
					goto done;
				pc -= offset;
				pc -= 3;
				ERROR(err_badjmp);
			}
			/* KOS-specific CFI code:
			 * >>     skip 1f
			 * >>     .byte 'K', 'O', 'S'
			 * >> 1:  skip 1f
			 * >>     -- Only execute this part on KOS
			 * >> 1:
			 */
			if (offset == 3 && (pc + 3) <= self->ue_pc_end &&
			    pc[-3] == 'K' && pc[-2] == 'O' && pc[-1] == 'S' &&
			    pc[0] == DW_OP_skip)
				pc += 3; /* Ignore the second `skip' instruction */
		}	break;

		CASE(DW_OP_bra) {
			int16_t offset;
			if unlikely(stacksz < 1)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			if (TOP.s_uconst != 0) {
				offset = (int16_t)UNALIGNED_GET16((uint16_t *)pc);
				pc += 2;
				if (offset < 0) {
					if unlikely(!self->ue_bjmprem)
						ERROR(err_loop);
					--self->ue_bjmprem;
				}
				pc += offset;
				if unlikely(pc < self->ue_pc_start ||
				            pc >= self->ue_pc_end) {
					if likely(pc == self->ue_pc_end)
						goto done;
					pc -= offset;
					pc -= 3;
					ERROR(err_badjmp);
				}
			} else {
				pc += 2;
			}
			--stacksz;
		}	break;

		CASE(DW_OP_eq)
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			if (SECOND.s_type != UNWIND_STE_CONSTANT)
				goto do_make_second_const;
			SECOND.s_uconst = SECOND.s_uconst == TOP.s_uconst ? 1 : 0;
			--stacksz;
			break;

		CASE(DW_OP_ge)
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			if (SECOND.s_type != UNWIND_STE_CONSTANT)
				goto do_make_second_const;
			SECOND.s_uconst = SECOND.s_uconst >= TOP.s_uconst ? 1 : 0;
			--stacksz;
			break;

		CASE(DW_OP_gt)
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			if (SECOND.s_type != UNWIND_STE_CONSTANT)
				goto do_make_second_const;
			SECOND.s_uconst = SECOND.s_uconst > TOP.s_uconst ? 1 : 0;
			--stacksz;
			break;

		CASE(DW_OP_le)
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			if (SECOND.s_type != UNWIND_STE_CONSTANT)
				goto do_make_second_const;
			SECOND.s_uconst = SECOND.s_uconst <= TOP.s_uconst ? 1 : 0;
			--stacksz;
			break;

		CASE(DW_OP_lt)
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			if (SECOND.s_type != UNWIND_STE_CONSTANT)
				goto do_make_second_const;
			SECOND.s_uconst = SECOND.s_uconst < TOP.s_uconst ? 1 : 0;
			--stacksz;
			break;

		CASE(DW_OP_ne)
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			if (SECOND.s_type != UNWIND_STE_CONSTANT)
				goto do_make_second_const;
			SECOND.s_uconst = SECOND.s_uconst != TOP.s_uconst ? 1 : 0;
			--stacksz;
			break;

		CASE(DW_OP_lit0 ... DW_OP_lit31)
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			self->ue_stack[stacksz].s_type   = UNWIND_STE_CONSTANT;
			self->ue_stack[stacksz].s_uconst = opcode - DW_OP_lit0;
			++stacksz;
			break;

		CASE(DW_OP_reg0 ... DW_OP_reg31)
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			self->ue_stack[stacksz].s_type      = UNWIND_STE_REGISTER;
			self->ue_stack[stacksz].s_register  = opcode - DW_OP_reg0;
			self->ue_stack[stacksz].s_regoffset = 0;
			++stacksz;
			break;

		CASE(DW_OP_breg0 ... DW_OP_breg31) {
			union {
				uintptr_t p;
				byte_t buf[CFI_UNWIND_REGISTER_MAXSIZE];
			} regval;
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			if unlikely(!(*self->ue_regget)(self->ue_regget_arg,
			                                opcode - DW_OP_breg0,
			                                regval.buf))
				ERROR(err_invalid_register);
			self->ue_stack[stacksz].s_lvalue = (byte_t *)regval.p + dwarf_decode_sleb128(&pc);
			self->ue_stack[stacksz].s_type   = UNWIND_STE_RW_LVALUE;
			++stacksz;
		}	break;

		CASE(DW_OP_regx)
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			self->ue_stack[stacksz].s_type      = UNWIND_STE_REGISTER;
			self->ue_stack[stacksz].s_register  = (unwind_regno_t)dwarf_decode_uleb128(&pc);
			self->ue_stack[stacksz].s_regoffset = 0;
			++stacksz;
			break;

		CASE(DW_OP_fbreg) {
			byte_t *expr, *old_pc_start, *old_pc_end;
			di_debuginfo_location_t const *old_frame_base;
			unsigned int error;
			size_t length;
			if unlikely(!self->ue_framebase)
				ERROR(err_illegal_instruction);
			expr = libuw_debuginfo_location_select(self->ue_framebase,
			                                       self->ue_module_base,
			                                       self->ue_module_relative_pc,
			                                       self->ue_addrsize,
			                                       &length);
			if unlikely(!expr)
				ERROR(err_illegal_instruction);
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			self->ue_stacksz   = stacksz;
			old_pc_start       = self->ue_pc_start;
			old_pc_end         = self->ue_pc_end;
			old_frame_base     = self->ue_framebase;
			self->ue_pc        = expr;
			self->ue_pc_start  = expr;
			self->ue_pc_end    = expr + length;
			self->ue_framebase = NULL; /* Prevent recursion */
			/* Execute the frame-base expression. */
			error              = libuw_unwind_emulator_exec(self);
			self->ue_framebase = old_frame_base;
			if unlikely(error != UNWIND_SUCCESS)
				return error;
			self->ue_pc_start = old_pc_start;
			self->ue_pc_end   = old_pc_end;
			/* Make sure that the frame-base expression returned some value. */
			if unlikely(self->ue_stacksz != stacksz + 1) {
				self->ue_pc = self->ue_pc - 1;
				if (self->ue_stacksz > stacksz)
					self->ue_stacksz = stacksz;
				ERROR(err_illegal_instruction_direct);
			}
			/* Ensure that the top-most expression is a constant */
			stacksz = self->ue_stacksz;
			error   = libuw_unwind_emulator_make_top_const(self);
			if unlikely(error != UNWIND_SUCCESS)
				return error;
			TOP.s_type = UNWIND_STE_RW_LVALUE;
			TOP.s_sconst += dwarf_decode_sleb128(&pc);
		}	break;

		CASE(DW_OP_bregx) {
			union {
				uintptr_t p;
				byte_t buf[CFI_UNWIND_REGISTER_MAXSIZE];
			} regval;
			unwind_regno_t regno;
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			regno = (unwind_regno_t)dwarf_decode_uleb128(&pc);
			if unlikely(!(*self->ue_regget)(self->ue_regget_arg,
			                                regno, regval.buf))
				ERROR(err_invalid_register);
			self->ue_stack[stacksz].s_lvalue = (byte_t *)regval.p + dwarf_decode_sleb128(&pc);
			self->ue_stack[stacksz].s_type   = UNWIND_STE_RW_LVALUE;
			++stacksz;
		}	break;

		CASE(DW_OP_piece) {
			uintptr_t num_bits;
			unsigned int target_left_shift;
			unsigned int error;
			if unlikely(stacksz < 1)
				ERROR(err_stack_underflow);
			target_left_shift = 0;
			if (self->ue_piecewrite) {
				if unlikely(TOP.s_type != UNWIND_STE_REGISTER &&
				            TOP.s_type != UNWIND_STE_RW_LVALUE)
					ERROR(err_not_writable);
				num_bits = dwarf_decode_uleb128(&pc) * 8;
				goto do_write_bit_pieces;
			}
			num_bits = dwarf_decode_uleb128(&pc) * 8;
			goto do_read_bit_pieces;
		CASE(DW_OP_bit_piece)
			if unlikely(stacksz < 1)
				ERROR(err_stack_underflow);
			if (self->ue_piecewrite) {
				if unlikely(TOP.s_type != UNWIND_STE_REGISTER &&
				            TOP.s_type != UNWIND_STE_RW_LVALUE)
					ERROR(err_not_writable); /* Read-only target location. */
				num_bits          = dwarf_decode_uleb128(&pc);
				target_left_shift = (unsigned int)dwarf_decode_uleb128(&pc);
do_write_bit_pieces:
				error = libuw_unwind_emulator_write_to_piece(self, &TOP, num_bits, target_left_shift);
				if unlikely(error != UNWIND_SUCCESS)
					return error;
				--stacksz;
				break;
			}
			num_bits          = dwarf_decode_uleb128(&pc);
			target_left_shift = dwarf_decode_uleb128(&pc);
do_read_bit_pieces:
			error = libuw_unwind_emulator_read_from_piece(self, &TOP, num_bits, target_left_shift);
			if unlikely(error != UNWIND_SUCCESS)
				return error;
			--stacksz;
		}	break;

		CASE(DW_OP_deref_size)
			if unlikely(stacksz < 1)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			/* Turn a constant into an l-value. */
			TOP.s_type  = UNWIND_STE_RW_LVALUE;
			TOP.s_lsize = *(uint8_t *)pc;
			pc += 1;
			break;

		CASE(DW_OP_xderef_size)
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			/* Turn a constant into an l-value. */
			SECOND.s_type   = UNWIND_STE_RW_LVALUE;
			SECOND.s_lsize  = *(uint8_t *)pc;
			SECOND.s_lvalue = (byte_t *)TOP.s_uconst;
			pc += 1;
			--stacksz;
			break;

		CASE(DW_OP_nop)
			break;

		CASE(DW_OP_push_object_address)
			if unlikely(!self->ue_objaddr)
				ERROR(err_illegal_instruction);
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			self->ue_stack[stacksz].s_type   = UNWIND_STE_CONSTANT;
			self->ue_stack[stacksz].s_uconst = (uintptr_t)self->ue_objaddr;
			++stacksz;
			break;

		CASE(DW_OP_call2)
		CASE(DW_OP_call4)
		CASE(DW_OP_call_ref) {
			byte_t *component_address;
			unsigned int error;
			if unlikely(!self->ue_sectinfo ||
			             self->ue_sectinfo->ues_debug_info_start >= self->ue_sectinfo->ues_debug_info_end ||
			             self->ue_sectinfo->ues_debug_abbrev_start >= self->ue_sectinfo->ues_debug_abbrev_end)
				ERROR(err_illegal_instruction);
			self->ue_pc = pc - 1;
			if (opcode == DW_OP_call2) {
				component_address = self->ue_sectinfo->ues_debug_info_start +
					                (uintptr_t)UNALIGNED_GET16((uint16_t *)pc);
				pc += 2;
			} else if (opcode == DW_OP_call4 || self->ue_ptrsize == 4) {
				component_address = self->ue_sectinfo->ues_debug_info_start +
					                (uintptr_t)UNALIGNED_GET32((uint32_t *)pc);
				pc += 4;
			} else {
				assert(self->ue_ptrsize == 8);
				component_address = self->ue_sectinfo->ues_debug_info_start +
					                (uintptr_t)UNALIGNED_GET64((uint64_t *)pc);
				pc += 8;
			}
			if unlikely(component_address < self->ue_sectinfo->ues_debug_info_start ||
			            component_address >= self->ue_sectinfo->ues_debug_info_end) {
				self->ue_stacksz = stacksz;
				ERROR(err_invalid_function_direct);
			}
			self->ue_stacksz = stacksz;
			/* Call the function stored at the given location. */
			error = libuw_unwind_call_function(self, component_address);
			if unlikely(error != UNWIND_SUCCESS)
				return error;
			stacksz = self->ue_stacksz;
		}	break;

		CASE(DW_OP_form_tls_address)
			if unlikely(!self->ue_tlsbase)
				ERROR(err_illegal_instruction);
			if unlikely(stacksz < 1)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT &&
			    TOP.s_type != UNWIND_STE_REGISTER)
				goto do_make_top_const;
			TOP.s_uconst += (uintptr_t)self->ue_tlsbase;
			break;

		CASE(DW_OP_call_frame_cfa)
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			if (!self->ue_call_frame_cfa) {
				unsigned int error;
				/* Evaluate the CFA value using the register state + regno-getter */
				error = libuw_unwind_emulator_calculate_cfa(self);
				if unlikely(error != UNWIND_SUCCESS) {
					self->ue_pc      = pc - 1;
					self->ue_stacksz = stacksz;
					return error;
				}
			}
			self->ue_stack[stacksz].s_type   = UNWIND_STE_CONSTANT;
			self->ue_stack[stacksz].s_uconst = self->ue_call_frame_cfa;
			++stacksz;
			break;

		CASE(DW_OP_implicit_value) {
			size_t size;
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			size                             = dwarf_decode_uleb128(&pc);
			self->ue_stack[stacksz].s_type   = UNWIND_STE_RO_LVALUE;
			self->ue_stack[stacksz].s_lvalue = pc;
			self->ue_stack[stacksz].s_lsize  = (unwind_regno_t)size;
			pc += size;
			++stacksz;
		}	break;

		CASE(DW_OP_stack_value)
			if unlikely(stacksz < 1)
				ERROR(err_stack_underflow);
			/* L-Value operands are converted back into their address-form */
			if (TOP.s_type != UNWIND_STE_RW_LVALUE &&
			    TOP.s_type != UNWIND_STE_RO_LVALUE &&
			    !UNWIND_STE_ISCONSTANT(TOP.s_type))
				goto do_make_top_const;
			TOP.s_type = UNWIND_STE_STACKVALUE;
			break;

		CASE(DW_OP_GNU_push_tls_address)
			if unlikely(!self->ue_tlsbase)
				ERROR(err_illegal_instruction);
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			if (self->ue_tlsbase == (byte_t *)-1) {
#ifdef __KERNEL__
				self->ue_tlsbase = (byte_t *)RD_TLS_BASE_REGISTER();
#else /* __KERNEL__ */
				{
					/* Try to use the TLS-base of the associated module */
					void *base = dltlsaddr(dlgethandle(pc));
					self->ue_tlsbase = base ? (byte_t *)base : (byte_t *)RD_TLS_BASE_REGISTER();
				}
#endif /* !__KERNEL__ */
			}
			self->ue_stack[stacksz].s_type   = UNWIND_STE_CONSTANT;
			self->ue_stack[stacksz].s_uconst = (uintptr_t)self->ue_tlsbase;
			++stacksz;
			break;

		CASE(DW_OP_GNU_uninit)
			/* ??? */
			break;

		default:
			ERRORF(err_unknown_instruction, "opcode = %#.2I8x (%p/%p/%p/%Iu)\n%$[hex]\n",
			       opcode, pc - 1, self->ue_pc_start, self->ue_pc_end,
			       (size_t)(self->ue_pc_end - (pc - 1)),
			       (size_t)(self->ue_pc_end - self->ue_pc_start),
			       self->ue_pc_start);
		}
	}
done:
	TRACE("Done at %p\n", pc);
	self->ue_pc      = pc;
	self->ue_stacksz = stacksz;
	return UNWIND_SUCCESS;
	{
		unsigned int error;
err_not_writable:
		error = UNWIND_EMULATOR_NOT_WRITABLE;
		goto err_common;
err_badjmp:
		error = UNWIND_EMULATOR_BADJMP;
		goto err_common;
err_loop:
		error = UNWIND_EMULATOR_LOOP;
		goto err_common;
err_divide_by_zero:
		error = UNWIND_EMULATOR_DIVIDE_BY_ZERO;
		goto err_common;
err_illegal_instruction:
		error = UNWIND_EMULATOR_ILLEGAL_INSTRUCTION;
		goto err_common;
err_unknown_instruction:
		error = UNWIND_EMULATOR_UNKNOWN_INSTRUCTION;
		goto err_common;
err_segfault:
		error = UNWIND_SEGFAULT;
		goto err_common;
err_invalid_register:
		error = UNWIND_INVALID_REGISTER;
		goto err_common;
err_stack_underflow:
		error = UNWIND_EMULATOR_STACK_UNDERFLOW;
		goto err_common;
err_stack_overflow:
		error = UNWIND_EMULATOR_STACK_OVERFLOW;
err_common:
		self->ue_pc      = pc - 1;
		self->ue_stacksz = stacksz;
		return error;
	}
err_illegal_instruction_direct:
	return UNWIND_EMULATOR_ILLEGAL_INSTRUCTION;
err_invalid_function_direct:
	return UNWIND_EMULATOR_INVALID_FUNCTION;
}


#define ALLOCA_STACK_SIZE      64
#define STACK_SIZE_INCREMENTS  16
#define STACK_SIZE_LIMIT       512

PRIVATE ATTR_NOINLINE NONNULL((1)) unsigned int CC
libuw_unwind_emulator_exec_alloca_stack(unwind_emulator_t *__restrict self,
                                        unwind_ste_t const *pentry_stack_top,
                                        unwind_ste_t *pexit_stack_top,
                                        uintptr_t *pexit_stack_top_const
#ifdef __KERNEL__
                                        ,
                                        size_t stack_size
#endif
                                        ) {
	unsigned int result;
#ifdef __KERNEL__
	unwind_ste_t *stack;
	if (get_stack_avail() < ((256 * sizeof(void *)) + (stack_size * sizeof(unwind_ste_t))))
		ERROR(err_badalloc);
	stack = (unwind_ste_t *)alloca(stack_size * sizeof(unwind_ste_t));
#else /* __KERNEL__ */
	unwind_ste_t stack[ALLOCA_STACK_SIZE];
#endif /* !__KERNEL__ */
	self->ue_stack   = stack;
	self->ue_stacksz = 0;
#ifdef __KERNEL__
	self->ue_stackmax = stack_size;
#else /* __KERNEL__ */
	self->ue_stackmax = ALLOCA_STACK_SIZE;
#endif /* !__KERNEL__ */
	if (pentry_stack_top) {
		self->ue_stacksz = 1;
		stack[0]         = *pentry_stack_top;
	}
	result = libuw_unwind_emulator_exec(self);
	assert(self->ue_stacksz < self->ue_stackmax);
	if likely(result == UNWIND_SUCCESS) {
		if (pexit_stack_top) {
			if unlikely(!self->ue_stacksz)
				ERROR(err_no_return_value);
			*pexit_stack_top = self->ue_stack[self->ue_stacksz - 1];
		}
		if (pexit_stack_top_const) {
			if unlikely(!self->ue_stacksz)
				ERROR(err_no_return_value);
			result = libuw_unwind_emulator_make_top_const(self);
			if likely(result == UNWIND_SUCCESS)
				*pexit_stack_top_const = self->ue_stack[self->ue_stacksz - 1].s_uconst;
		}
	}
	return result;
err_no_return_value:
	return UNWIND_EMULATOR_NO_RETURN_VALUE;
#ifdef __KERNEL__
err_badalloc:
	return UNWIND_BADALLOC;
#endif
}

INTERN NONNULL((1)) unsigned int CC
libuw_unwind_emulator_exec_autostack(unwind_emulator_t *__restrict self,
                                     unwind_ste_t const *pentry_stack_top,
                                     unwind_ste_t *pexit_stack_top,
                                     uintptr_t *pexit_stack_top_const) {
	unsigned int error;
	/* First off: Try to allocate an execution stack on our own stack.
	 *            If that stack overflows, move on to allocating a stack
	 *            on the heap (userspace), or carefully increase the stack
	 *            size up to a certain point (kernelspace) */
	error = libuw_unwind_emulator_exec_alloca_stack(self,
	                                                pentry_stack_top,
	                                                pexit_stack_top,
	                                                pexit_stack_top_const
#ifdef __KERNEL__
	                                                ,
	                                                ALLOCA_STACK_SIZE
#endif /* __KERNEL__ */
	                                                );
	if (error != UNWIND_EMULATOR_STACK_OVERFLOW) {
#ifdef __KERNEL__
		if (error == UNWIND_BADALLOC)
			error = UNWIND_EMULATOR_STACK_OVERFLOW;
#endif /* __KERNEL__ */
		return error;
	}
	/* Try a larger stack */
	{
		size_t new_stack_size;
		for (new_stack_size = ALLOCA_STACK_SIZE + 16;
		     new_stack_size < STACK_SIZE_LIMIT;
		     new_stack_size += STACK_SIZE_INCREMENTS) {
#ifdef __KERNEL__
			error = libuw_unwind_emulator_exec_alloca_stack(self,
			                                                pentry_stack_top,
			                                                pexit_stack_top,
			                                                pexit_stack_top_const,
			                                                new_stack_size);
			if (error != UNWIND_EMULATOR_STACK_OVERFLOW) {
				if (error == UNWIND_BADALLOC)
					break;
				return error;
			}
#else /* __KERNEL__ */
			unwind_ste_t *stack;
			stack = (unwind_ste_t *)malloc(new_stack_size * sizeof(unwind_ste_t));
			if unlikely(!stack)
				break;
			self->ue_stack = stack;
			self->ue_stacksz = 0;
			self->ue_stackmax = ALLOCA_STACK_SIZE;
			if (pentry_stack_top) {
				stack[0] = *pentry_stack_top;
				self->ue_stacksz = 1;
			}
			/* Execute the emulator again. */
			error = libuw_unwind_emulator_exec(self);
			if likely(error != UNWIND_EMULATOR_STACK_OVERFLOW) {
				if likely(error == UNWIND_SUCCESS) {
					if (pexit_stack_top) {
						if unlikely(!self->ue_stacksz)
							ERROR(err_no_return_value);
						*pexit_stack_top = self->ue_stack[self->ue_stacksz - 1];
					}
					if (pexit_stack_top_const) {
						if unlikely(!self->ue_stacksz)
							ERROR(err_no_return_value);
						error = libuw_unwind_emulator_make_top_const(self);
						if likely(error == UNWIND_SUCCESS)
							*pexit_stack_top_const = self->ue_stack[self->ue_stacksz - 1].s_uconst;
					}
				}
				free(stack);
				return error;
			}
			free(stack);
#endif /* !__KERNEL__ */
		}
	}
	return UNWIND_EMULATOR_STACK_OVERFLOW;
#ifndef __KERNEL__
err_no_return_value:
	return UNWIND_EMULATOR_NO_RETURN_VALUE;
#endif /* !__KERNEL__ */
}


/* Return a pointer to the next unwind instruction following `UNWIND_PC'
 * -> Useful for dumping unwind instruction without having to take care
 *    of handling all possible instruction (after all: CFI has a CISC
 *    instruction set with variable-length instructions)
 * @param: ADDRSIZE: Size of a target address.
 * @param: PTRSIZE:  Size of a DWARF pointer (4 for 32-bit dwarf; 8 for 64-bit dwarf).
 * @return: NULL: The instruction at `UNWIND_PC' wasn't recognized. */
INTERN ATTR_PURE WUNUSED NONNULL((1)) byte_t const *
NOTHROW_NCX(CC libuw_unwind_instruction_succ)(byte_t const *__restrict unwind_pc,
                                              uint8_t addrsize, uint8_t ptrsize) {
	byte_t op = *unwind_pc++;
	switch (op) {

	case DW_OP_addr:
		unwind_pc += addrsize;
		break;

	case DW_OP_deref:
	case DW_OP_dup:
	case DW_OP_drop:
	case DW_OP_over:
	case DW_OP_swap:
	case DW_OP_rot:
	case DW_OP_xderef:
	case DW_OP_abs:
	case DW_OP_and:
	case DW_OP_div:
	case DW_OP_minus:
	case DW_OP_mod:
	case DW_OP_mul:
	case DW_OP_neg:
	case DW_OP_not:
	case DW_OP_or:
	case DW_OP_plus:
	case DW_OP_plus_uconst:
	case DW_OP_shl:
	case DW_OP_shr:
	case DW_OP_shra:
	case DW_OP_xor:
	case DW_OP_eq:
	case DW_OP_ge:
	case DW_OP_gt:
	case DW_OP_le:
	case DW_OP_lt:
	case DW_OP_ne:
	case DW_OP_lit0:
	case DW_OP_lit1:
	case DW_OP_lit2:
	case DW_OP_lit3:
	case DW_OP_lit4:
	case DW_OP_lit5:
	case DW_OP_lit6:
	case DW_OP_lit7:
	case DW_OP_lit8:
	case DW_OP_lit9:
	case DW_OP_lit10:
	case DW_OP_lit11:
	case DW_OP_lit12:
	case DW_OP_lit13:
	case DW_OP_lit14:
	case DW_OP_lit15:
	case DW_OP_lit16:
	case DW_OP_lit17:
	case DW_OP_lit18:
	case DW_OP_lit19:
	case DW_OP_lit20:
	case DW_OP_lit21:
	case DW_OP_lit22:
	case DW_OP_lit23:
	case DW_OP_lit24:
	case DW_OP_lit25:
	case DW_OP_lit26:
	case DW_OP_lit27:
	case DW_OP_lit28:
	case DW_OP_lit29:
	case DW_OP_lit30:
	case DW_OP_lit31:
	case DW_OP_reg0:
	case DW_OP_reg1:
	case DW_OP_reg2:
	case DW_OP_reg3:
	case DW_OP_reg4:
	case DW_OP_reg5:
	case DW_OP_reg6:
	case DW_OP_reg7:
	case DW_OP_reg8:
	case DW_OP_reg9:
	case DW_OP_reg10:
	case DW_OP_reg11:
	case DW_OP_reg12:
	case DW_OP_reg13:
	case DW_OP_reg14:
	case DW_OP_reg15:
	case DW_OP_reg16:
	case DW_OP_reg17:
	case DW_OP_reg18:
	case DW_OP_reg19:
	case DW_OP_reg20:
	case DW_OP_reg21:
	case DW_OP_reg22:
	case DW_OP_reg23:
	case DW_OP_reg24:
	case DW_OP_reg25:
	case DW_OP_reg26:
	case DW_OP_reg27:
	case DW_OP_reg28:
	case DW_OP_reg29:
	case DW_OP_reg30:
	case DW_OP_reg31:
	case DW_OP_nop:
	case DW_OP_push_object_address:
	case DW_OP_form_tls_address:
	case DW_OP_call_frame_cfa:
	case DW_OP_stack_value:
	case DW_OP_GNU_push_tls_address:
	case DW_OP_GNU_uninit:
		break;

	case DW_OP_const1u:
	case DW_OP_const1s:
	case DW_OP_pick:
	case DW_OP_deref_size:
	case DW_OP_xderef_size:
		unwind_pc += 1;
		break;

	case DW_OP_const2u:
	case DW_OP_const2s:
	case DW_OP_skip:
	case DW_OP_bra:
	case DW_OP_call2:
		unwind_pc += 2;
		break;

	case DW_OP_const4u:
	case DW_OP_const4s:
	case DW_OP_call4:
		unwind_pc += 4;
		break;

	case DW_OP_const8u:
	case DW_OP_const8s:
		unwind_pc += 8;
		break;

	case DW_OP_constu:
	case DW_OP_regx:
	case DW_OP_piece:
		dwarf_decode_uleb128((byte_t **)&unwind_pc);
		break;

	case DW_OP_call_ref:
		unwind_pc += ptrsize;
		break;

	case DW_OP_consts:
	case DW_OP_breg0:
	case DW_OP_breg1:
	case DW_OP_breg2:
	case DW_OP_breg3:
	case DW_OP_breg4:
	case DW_OP_breg5:
	case DW_OP_breg6:
	case DW_OP_breg7:
	case DW_OP_breg8:
	case DW_OP_breg9:
	case DW_OP_breg10:
	case DW_OP_breg11:
	case DW_OP_breg12:
	case DW_OP_breg13:
	case DW_OP_breg14:
	case DW_OP_breg15:
	case DW_OP_breg16:
	case DW_OP_breg17:
	case DW_OP_breg18:
	case DW_OP_breg19:
	case DW_OP_breg20:
	case DW_OP_breg21:
	case DW_OP_breg22:
	case DW_OP_breg23:
	case DW_OP_breg24:
	case DW_OP_breg25:
	case DW_OP_breg26:
	case DW_OP_breg27:
	case DW_OP_breg28:
	case DW_OP_breg29:
	case DW_OP_breg30:
	case DW_OP_breg31:
	case DW_OP_fbreg:
		dwarf_decode_sleb128((byte_t **)&unwind_pc);
		break;

	case DW_OP_bregx:
		dwarf_decode_uleb128((byte_t **)&unwind_pc);
		dwarf_decode_sleb128((byte_t **)&unwind_pc);
		break;

	case DW_OP_bit_piece:
		dwarf_decode_uleb128((byte_t **)&unwind_pc);
		dwarf_decode_uleb128((byte_t **)&unwind_pc);
		break;

	case DW_OP_implicit_value: {
		dwarf_uleb128_t size;
		size = dwarf_decode_uleb128((byte_t **)&unwind_pc);
		unwind_pc += size;
	}	break;

	default:
		unwind_pc = NULL;
		break;
	}
	return unwind_pc;
}



/* Return a pointer to a CFI expression that is applicable for `CU_BASE + MODULE_RELATIVE_PC'
 * If no such expression exists, return `NULL' instead. */
INTERN WUNUSED NONNULL((1, 5)) byte_t *
NOTHROW_NCX(CC libuw_debuginfo_location_select)(di_debuginfo_location_t const *__restrict self,
                                                uintptr_t cu_base,
                                                uintptr_t module_relative_pc,
                                                uint8_t addrsize,
                                                size_t *__restrict pexpr_length) {
	/* Check for simple case: Only a single, universal expression is defined */
	byte_t *reader;
	if (self->l_expr) {
		reader        = self->l_expr;
		*pexpr_length = dwarf_decode_uleb128(&reader);
		return reader;
	}
	if (self->l_llist) {
		/* Scan the location list for a match for `module_relative_pc' */
		uintptr_t range_start, range_end;
		reader = self->l_llist;
		for (;;) {
			if (addrsize >= sizeof(uintptr_t)) {
				range_start = UNALIGNED_GET((uintptr_t *)reader);
				reader += addrsize;
				range_end = UNALIGNED_GET((uintptr_t *)reader);
				reader += addrsize;
#if __SIZEOF_POINTER__ > 4
			} else if (addrsize >= 4) {
				range_start = UNALIGNED_GET32((uint32_t *)reader);
				reader += addrsize;
				range_end = UNALIGNED_GET32((uint32_t *)reader);
				reader += addrsize;
#endif /* __SIZEOF_POINTER__ > 4 */
			} else if (addrsize >= 2) {
				range_start = UNALIGNED_GET16((uint16_t *)reader);
				reader += addrsize;
				range_end = UNALIGNED_GET16((uint16_t *)reader);
				reader += addrsize;
			} else {
				range_start = *(uint8_t *)reader;
				reader += addrsize;
				range_end = *(uint8_t *)reader;
				reader += addrsize;
			}
			/* Handle special entries */
			if (range_start == (uintptr_t)-1) {
				/* Base address selection entry! */
				cu_base = range_end;
			} else if (!range_start && !range_end) {
				/* Location list end entry. */
				break;
			} else {
				range_start += cu_base;
				range_end += cu_base;
			}
			TRACE("%p: RANGE(%p-%p) with %I16u\n",
			      reader - 2 * addrsize,
			      range_start,
			      range_end,
			      UNALIGNED_GET16((uint16_t *)reader));
			if (module_relative_pc >= range_start &&
			    module_relative_pc < range_end) {
				*pexpr_length = (size_t)UNALIGNED_GET16((uint16_t *)reader);
				reader += 2;
				return reader; /* Found it! */
			}
			/* Skip the associated expression. */
			{
				uint16_t expr_length;
				expr_length = UNALIGNED_GET16((uint16_t *)reader);
				reader += 2;
				reader += expr_length;
			}
		}
	}
	*pexpr_length = 0;
	return NULL;
}




/* Read/Write the value associated with a given debuginfo location descriptor.
 * @param: SELF:                  The debug info location descriptor (s.a. libdebuginfo.so)
 * @param: SECTINFO:              Emulator section information (to-be filled in by the caller)
 *                                Optionally, this argument may be `NULL', however if this is the
 *                                case, the function may fail in cases where it would have otherwise
 *                                succeeded.
 * @param: REGGET:                Register getter callback.
 * @param: REGGET_ARG:            Register getter callback argument.
 * @param: REGSET:                Register setter callback.
 * @param: REGSET_ARG:            Register setter callback argument.
 * @param: CU_BASE:               Base address of the associated CU (or `0') (== `di_debuginfo_compile_unit_t::cu_ranges::r_startpc')
 * @param: MODULE_RELATIVE_PC:    The module-relative program counter, to-be used to select
 *                                the appropriate expression within a location list.
 * @param: BUF:                   Source/target buffer containing the value read from,
 *                                or written to the location expression.
 * @param: BUFSIZE:               Size of the given `BUF' in bytes.
 * @param: PNUM_WRITTEN_BITS:     The number of _BITS_ (not bytes!) read from the location expression,
 *                                and written to the given `BUF' (any trailing bits of buffer memory
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
INTERN NONNULL((1, 3, 7, 9)) unsigned int CC
libuw_debuginfo_location_getvalue(di_debuginfo_location_t const *__restrict self,
                                  unwind_emulator_sections_t const *sectinfo,
                                  unwind_getreg_t regget, void *regget_arg,
                                  uintptr_t cu_base, uintptr_t module_relative_pc,
                                  void *__restrict buf, size_t bufsize,
                                  size_t *__restrict pnum_written_bits,
                                  di_debuginfo_location_t const *frame_base_expression,
                                  void *objaddr, uint8_t addrsize, uint8_t ptrsize) {
	unwind_ste_t ste_top;
	unwind_emulator_t emulator;
	size_t expr_length;
	unsigned int result;
	memset(&emulator, 0, sizeof(emulator));
	memset(buf, 0, bufsize); /* Pre-initialize the buffer to all zeroes */
	/* Select the proper function. */
	emulator.ue_pc = libuw_debuginfo_location_select(self,
	                                                 cu_base,
	                                                 module_relative_pc,
	                                                 addrsize,
	                                                 &expr_length);
	if unlikely(!emulator.ue_pc)
		ERROR(err_no_function);
	emulator.ue_pc_start           = emulator.ue_pc;
	emulator.ue_pc_end             = emulator.ue_pc + expr_length;
	emulator.ue_sectinfo           = sectinfo;
	emulator.ue_regget             = regget;
	emulator.ue_regget_arg         = regget_arg;
	emulator.ue_framebase          = frame_base_expression;
	emulator.ue_objaddr            = objaddr;
	emulator.ue_bjmprem            = UNWIND_EMULATOR_BJMPREM_DEFAULT;
	emulator.ue_addrsize           = addrsize;
	emulator.ue_ptrsize            = ptrsize;
	emulator.ue_piecebuf           = (byte_t *)buf;
	emulator.ue_piecesiz           = bufsize;
	emulator.ue_module_base        = cu_base;
	emulator.ue_module_relative_pc = module_relative_pc;
	/* Execute the emulator. */
	result = libuw_unwind_emulator_exec_autostack(&emulator, NULL, &ste_top, NULL);
	assert(emulator.ue_piecebits <= bufsize * 8);
	if (result == UNWIND_EMULATOR_NO_RETURN_VALUE)
		result = UNWIND_SUCCESS; /* No stack-entry location. */
	else if (result == UNWIND_SUCCESS) {
		/* Use the last stack entry to as the missing data-piece. */
		if (ste_top.s_type == UNWIND_STE_CONSTANT)
			ste_top.s_type = UNWIND_STE_RW_LVALUE;
		result = libuw_unwind_emulator_read_from_piece(&emulator,
		                                               &ste_top,
		                                               (bufsize * 8) - emulator.ue_piecebits,
		                                               0);
	}
	*pnum_written_bits = emulator.ue_piecebits;
	return result;
err_no_function:
	return UNWIND_EMULATOR_NO_FUNCTION;
}


INTERN NONNULL((1, 3, 5, 9, 11)) unsigned int CC
libuw_debuginfo_location_setvalue(di_debuginfo_location_t const *__restrict self,
                                  unwind_emulator_sections_t const *sectinfo,
                                  unwind_getreg_t regget, void *regget_arg,
                                  unwind_setreg_t regset, void *regset_arg,
                                  uintptr_t cu_base, uintptr_t module_relative_pc,
                                  void const *__restrict buf, size_t bufsize,
                                  size_t *__restrict pnum_read_bits,
                                  di_debuginfo_location_t const *frame_base_expression,
                                  void *objaddr, uint8_t addrsize, uint8_t ptrsize) {
	unwind_ste_t ste_top;
	unwind_emulator_t emulator;
	size_t expr_length;
	unsigned int result;
	memset(&emulator, 0, sizeof(emulator));
	/* Select the proper function. */
	emulator.ue_pc = libuw_debuginfo_location_select(self,
	                                                 cu_base,
	                                                 module_relative_pc,
	                                                 addrsize,
	                                                 &expr_length);
	if unlikely(!emulator.ue_pc)
		ERROR(err_no_function);
	emulator.ue_pc_start           = emulator.ue_pc;
	emulator.ue_pc_end             = emulator.ue_pc + expr_length;
	emulator.ue_sectinfo           = sectinfo;
	emulator.ue_regget             = regget;
	emulator.ue_regset             = regset;
	emulator.ue_regget_arg         = regget_arg;
	emulator.ue_regset_arg         = regset_arg;
	emulator.ue_framebase          = frame_base_expression;
	emulator.ue_objaddr            = objaddr;
	emulator.ue_bjmprem            = UNWIND_EMULATOR_BJMPREM_DEFAULT;
	emulator.ue_addrsize           = addrsize;
	emulator.ue_ptrsize            = ptrsize;
	emulator.ue_piecewrite         = 1;
	emulator.ue_piecebuf           = (byte_t *)buf;
	emulator.ue_piecesiz           = bufsize;
	emulator.ue_module_base        = cu_base;
	emulator.ue_module_relative_pc = module_relative_pc;
	/* Execute the emulator. */
	result = libuw_unwind_emulator_exec_autostack(&emulator, NULL, &ste_top, NULL);
	assert(emulator.ue_piecebits <= bufsize * 8);
	if (result == UNWIND_EMULATOR_NO_RETURN_VALUE)
		result = UNWIND_SUCCESS; /* No stack-entry location. */
	else if (result == UNWIND_SUCCESS) {
		if (ste_top.s_type == UNWIND_STE_CONSTANT)
			ste_top.s_type = UNWIND_STE_RW_LVALUE;
		if (!UNWIND_STE_ISWRITABLE(ste_top.s_type))
			goto not_writable;
		/* Use the last stack entry to as the missing data-piece. */
		result = libuw_unwind_emulator_write_to_piece(&emulator,
		                                              &ste_top,
		                                              (bufsize * 8) - emulator.ue_piecebits,
		                                              0);
	} else {
not_writable:
		result = UNWIND_EMULATOR_NOT_WRITABLE;
	}
	*pnum_read_bits = emulator.ue_piecebits;
	return result;
err_no_function:
	return UNWIND_EMULATOR_NO_FUNCTION;
}




DEFINE_PUBLIC_ALIAS(unwind_emulator_exec, libuw_unwind_emulator_exec);
DEFINE_PUBLIC_ALIAS(unwind_emulator_exec_autostack, libuw_unwind_emulator_exec_autostack);
DEFINE_PUBLIC_ALIAS(unwind_instruction_succ, libuw_unwind_instruction_succ);
DEFINE_PUBLIC_ALIAS(debuginfo_location_select, libuw_debuginfo_location_select);
DEFINE_PUBLIC_ALIAS(debuginfo_location_getvalue, libuw_debuginfo_location_getvalue);
DEFINE_PUBLIC_ALIAS(debuginfo_location_setvalue, libuw_debuginfo_location_setvalue);

DECL_END

#endif /* !GUARD_LIBUNWIND_CFI_C */
