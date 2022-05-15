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
#ifndef GUARD_LIBUNWIND_CFI_C
#define GUARD_LIBUNWIND_CFI_C 1
#define _KOS_SOURCE 1
#define _KOS_KERNEL_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/atomic.h>
#include <hybrid/byteorder.h>
#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <asm/signed-shift.h>
#include <kos/bits/thread.h>
#include <kos/except.h>
#include <kos/nopf.h>
#include <kos/types.h>
#include <sys/param.h>

#include <alloca.h>
#include <assert.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <libdebuginfo/cfi_entry.h>
#include <libdebuginfo/debug_frame.h>
#include <libdebuginfo/debug_info.h>
#include <libdebuginfo/dwarf.h>
#include <libunwind/cfi.h>
#include <libunwind/eh_frame.h>

#include "cfi.h"
#include "dwarf.h"
#include "eh_frame.h"
#include "unwind.h"

#ifndef __KERNEL__
#include <hybrid/atomic.h>

#include <dlfcn.h>
#include <malloc.h>
#else /* !__KERNEL__ */
#include <debugger/rt.h> /* dbg_active, dbg_current */
#include <sched/task.h>  /* get_stack_avail() */
#endif /* __KERNEL__ */

DECL_BEGIN

PRIVATE WUNUSED NONNULL((2)) bool
NOTHROW(CC guarded_readb)(uint8_t *ptr, uintptr_t *__restrict result) {
	uint8_t value;
	/* Attempt the read using *_nopf before doing a NESTED_TRY */
#ifdef __readb_nopf_defined
	if unlikely(!readb_nopf(ptr, &value))
#endif /* __readb_nopf_defined */
	{
		NESTED_TRY {
			value = *ptr;
		} EXCEPT {
			return false;
		}
	}
	*result = (uintptr_t)value;
	return true;
}

PRIVATE WUNUSED NONNULL((2)) bool
NOTHROW(CC guarded_readw)(uint16_t *ptr, uintptr_t *__restrict result) {
	uint16_t value;
	/* Attempt the read using *_nopf before doing a NESTED_TRY */
#ifdef __readw_nopf_defined
	if unlikely(!readw_nopf(ptr, &value))
#endif /* __readw_nopf_defined */
	{
		NESTED_TRY {
			value = UNALIGNED_GET16(ptr);
		} EXCEPT {
			return false;
		}
	}
	*result = (uintptr_t)value;
	return true;
}

PRIVATE WUNUSED NONNULL((2)) bool
NOTHROW(CC guarded_readl)(uint32_t *ptr, uintptr_t *__restrict result) {
	uint32_t value;
	/* Attempt the read using *_nopf before doing a NESTED_TRY */
#ifdef __readl_nopf_defined
	if unlikely(!readl_nopf(ptr, &value))
#endif /* __readl_nopf_defined */
	{
		NESTED_TRY {
			value = UNALIGNED_GET32(ptr);
		} EXCEPT {
			return false;
		}
	}
	*result = (uintptr_t)value;
	return true;
}

#if __SIZEOF_POINTER__ >= 8
PRIVATE WUNUSED NONNULL((2)) bool
NOTHROW(CC guarded_readq)(uint64_t *ptr, uintptr_t *__restrict result) {
	uint64_t value;
	/* Attempt the read using *_nopf before doing a NESTED_TRY */
#ifdef __readq_nopf_defined
	if unlikely(!readq_nopf(ptr, &value))
#endif /* __readq_nopf_defined */
	{
		NESTED_TRY {
			value = UNALIGNED_GET64(ptr);
		} EXCEPT {
			return false;
		}
	}
	*result = (uintptr_t)value;
	return true;
}
#define guarded_readptr guarded_readq
#else /* __SIZEOF_POINTER__ >= 8 */
#define guarded_readptr guarded_readl
#endif /* __SIZEOF_POINTER__ < 8 */

INTERN WUNUSED bool
NOTHROW(CC guarded_memcpy)(void *dst, void const *src, size_t num_bytes) {
	/* Attempt the read using *_nopf before doing a NESTED_TRY */
#ifdef __memcpy_nopf_defined
	if unlikely(memcpy_nopf(dst, src, num_bytes) != 0)
#endif /* __memcpy_nopf_defined */
	{
		NESTED_TRY {
			memcpy(dst, src, num_bytes);
		} EXCEPT {
			return false;
		}
	}
	return true;
}



#ifndef __KERNEL__
PRIVATE void *pdyn_libdebuginfo                                                     = NULL;
PRIVATE PDEBUGINFO_CU_ABBREV_FINI /*     */ pdyn_debuginfo_cu_abbrev_fini           = NULL;
PRIVATE PDEBUGINFO_CU_PARSER_LOADUNIT /* */ pdyn_debuginfo_cu_parser_loadunit       = NULL;
PRIVATE PDEBUGINFO_CU_PARSER_SKIPFORM /* */ pdyn_debuginfo_cu_parser_skipform       = NULL;
PRIVATE PDEBUGINFO_CU_PARSER_GETEXPR /*  */ pdyn_debuginfo_cu_parser_getexpr        = NULL;
PRIVATE PDEBUGINFO_RUN_ENTRY_VALUE_EMULATOR pdyn_debuginfo_run_entry_value_emulator = NULL;
PRIVATE PUNWIND_FDE_SCAN_DF /*           */ pdyn_unwind_fde_scan_df                 = NULL;
#define debuginfo_cu_abbrev_fini           (*pdyn_debuginfo_cu_abbrev_fini)
#define debuginfo_cu_parser_loadunit       (*pdyn_debuginfo_cu_parser_loadunit)
#define debuginfo_cu_parser_skipform       (*pdyn_debuginfo_cu_parser_skipform)
#define debuginfo_cu_parser_getexpr        (*pdyn_debuginfo_cu_parser_getexpr)
#define debuginfo_run_entry_value_emulator (*pdyn_debuginfo_run_entry_value_emulator)
#define unwind_fde_scan_df                 (*pdyn_unwind_fde_scan_df)

PRIVATE __attribute__((__destructor__))
void libuw_unload_libdebuginfo(void) {
	/* libdebuginfo.so was loaded by us, unload it when our library gets destroyed. */
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
	*(void **)&pdyn_debuginfo_run_entry_value_emulator = dlsym(pdyn_libdebuginfo, "debuginfo_run_entry_value_emulator");
	if unlikely(!pdyn_debuginfo_run_entry_value_emulator)
		goto err_close;
	*(void **)&pdyn_debuginfo_cu_parser_getexpr = dlsym(pdyn_libdebuginfo, "debuginfo_cu_parser_getexpr");
	if unlikely(!pdyn_debuginfo_cu_parser_getexpr)
		goto err_close;
	*(void **)&pdyn_debuginfo_cu_parser_skipform = dlsym(pdyn_libdebuginfo, "debuginfo_cu_parser_skipform");
	if unlikely(!pdyn_debuginfo_cu_parser_skipform)
		goto err_close;
	*(void **)&pdyn_debuginfo_cu_parser_loadunit = dlsym(pdyn_libdebuginfo, "debuginfo_cu_parser_loadunit");
	if unlikely(!pdyn_debuginfo_cu_parser_loadunit)
		goto err_close;
	*(void **)&pdyn_unwind_fde_scan_df = dlsym(pdyn_libdebuginfo, "unwind_fde_scan_df");
	if unlikely(!pdyn_unwind_fde_scan_df)
		goto err_close;
	COMPILER_WRITE_BARRIER();
	/* This one has to be loaded last, since it's
	 * used as the  fast-pass for  already-loaded */
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
	unsigned int error;
	if (ste->s_type != UNWIND_STE_CONSTANT) {
		if (ste->s_type == UNWIND_STE_REGISTER ||
		    ste->s_type == UNWIND_STE_REGPOINTER) {
			union {
				uintptr_t p;
				byte_t buf[CFI_REGISTER_MAXSIZE];
			} regval;
			error = (*self->ue_regget)(self->ue_regget_arg, ste->s_register, regval.buf);
			if unlikely(error != UNWIND_SUCCESS)
				ERRORF(err, "ste->s_register = %u (%u)\n", (unsigned int)ste->s_register, error);
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
err:
	return error;
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
                           byte_t const *__restrict component_pointer) {
	di_debuginfo_cu_parser_t parser;
	di_debuginfo_cu_abbrev_t abbrev;
	byte_t const *di_reader;
	unsigned int di_error;
	di_debuginfo_component_attrib_t attr;
	di_debuginfo_cu_parser_sections_t sect;
	if unlikely(!self->ue_sectinfo)
		ERROR(err_invalid_function);
#ifndef __KERNEL__
	/* Lazily load libdebuginfo.so, so we can parser the .debug_info section */
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
		byte_t const *old_pc_start, *old_pc_end;
		if (attr.dica_name != DW_AT_location)
			continue;
		/* Found it! */
		if unlikely(!debuginfo_cu_parser_getexpr(&parser, attr.dica_form, &expr))
			ERROR(err_invalid_function_abbrev);
		/* Select the appropriate function. */
		self->ue_pc = libuw_debuginfo_location_select(&expr,
		                                              self->ue_cu ? self->ue_cu->cu_ranges.r_startpc : 0,
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
		byte_t buf[CFI_REGISTER_MAXSIZE];
		void *pc;
	} pc_buf;
	if unlikely(!self->ue_sectinfo)
		goto err_no_cfa;

	/* Load the current program counter position. */
	error = (*self->ue_regget)(self->ue_regget_arg,
	                           CFI_UNWIND_REGISTER_PC(self->ue_addrsize),
	                           pc_buf.buf);
	if unlikely(error != UNWIND_SUCCESS)
		ERRORF(err, "%u\n", error);

	/* Search for an FDE descriptor for the program counter within the .eh_frame section. */
	/* TODO: Support for `self->ue_sectinfo->ues_eh_frame_hdr_start' */
	fde.f_bases.ub_tbase = self->ue_bases.ub_tbase;
	fde.f_bases.ub_dbase = self->ue_bases.ub_dbase;
	error = libuw_unwind_fde_scan(self->ue_sectinfo->ues_eh_frame_start,
	                              self->ue_sectinfo->ues_eh_frame_end,
	                              pc_buf.pc, &fde, self->ue_addrsize);
	if unlikely(error != UNWIND_SUCCESS) {
		if (error != UNWIND_NO_FRAME)
			goto done;
		if (self->ue_sectinfo->ues_debug_frame_start >=
		    self->ue_sectinfo->ues_debug_frame_end)
			goto err_no_cfa;

#ifndef __KERNEL__
		/* Lazily load libdebuginfo.so, so we can parse the .debug_info section */
		if (!pdyn_debuginfo_cu_abbrev_fini && unlikely(libuw_load_libdebuginfo()))
			goto err_no_cfa;
#endif /* !__KERNEL__ */

		/* Also search the `.debug_frame' section, using `unwind_fde_scan_df()' */
		error = unwind_fde_scan_df(self->ue_sectinfo->ues_debug_frame_start,
		                           self->ue_sectinfo->ues_debug_frame_end,
		                           pc_buf.pc,
		                           &fde,
		                           self->ue_addrsize);
		if unlikely(error != UNWIND_SUCCESS)
			goto done;
	}

	/* Evaluate the FDE program to extract the CFA descriptor. */
	error = libuw_unwind_fde_exec_cfa(&fde, &cfa, pc_buf.pc);
	if unlikely(error != UNWIND_SUCCESS)
		goto done;

	/* Calculate the absolute address of the associated CFA,
	 * and store  the  result  in  `self->ue_call_frame_cfa' */
	error = libuw_unwind_fde_calculate_cfa(&fde, &cfa,
	                                       self->ue_regget,
	                                       self->ue_regget_arg,
	                                       &self->ue_call_frame_cfa);
done:
	return error;
err_no_cfa:
	return UNWIND_EMULATOR_NO_CFA;
err:
	return error;
}

/* Load the effective l-value address of `self' into `*paddr':
 *   UNWIND_STE_CONSTANT:     Write-back s_uconst or s_sconst
 *   UNWIND_STE_STACKVALUE:   Write-back s_uconst or s_sconst
 *   UNWIND_STE_REGISTER:     Write-back REGISTER[s_register] + s_regoffset
 *   UNWIND_STE_REGPOINTER:   Write-back REGISTER[s_register]       (NOTE: Technically, this case isn't allowed)
 *   UNWIND_STE_RW_LVALUE:    Write-back s_lvalue
 *   UNWIND_STE_RO_LVALUE:    Write-back s_lvalue
 * @return: UNWIND_SUCCESS:                      Success.
 * @return: UNWIND_INVALID_REGISTER:             Invalid register referenced by `self'
 * @return: UNWIND_EMULATOR_ILLEGAL_INSTRUCTION: Invalid stack-value type in `self' */
INTERN NONNULL((1, 2, 4)) unsigned int
NOTHROW_NCX(CC libuw_unwind_ste_addr)(unwind_ste_t const *__restrict self,
                                      unwind_getreg_t regget, void const *regget_arg,
                                      void **__restrict paddr) {
	unsigned int error;
	switch (self->s_type) {

	case UNWIND_STE_REGISTER:
	case UNWIND_STE_REGPOINTER: {
		union {
			uintptr_t word;
			byte_t data[CFI_REGISTER_MAXSIZE];
		} regval;
		error = (*regget)(regget_arg, self->s_register, regval.data);
		if unlikely(error != UNWIND_SUCCESS)
			ERRORF(err, "self->s_register = %u (%u)\n", (unsigned int)self->s_register, error);
		if (self->s_type == UNWIND_STE_REGISTER)
			regval.word += self->s_regoffset;
		*paddr = (void *)regval.word;
	}	break;

	case UNWIND_STE_CONSTANT:
	case UNWIND_STE_STACKVALUE:
	case UNWIND_STE_RW_LVALUE:
	case UNWIND_STE_RO_LVALUE:
		*paddr = (void *)self->s_uconst;
		break;

	default:
		goto err_illegal_instruction;
	}
	return UNWIND_SUCCESS;
err_illegal_instruction:
	return UNWIND_EMULATOR_ILLEGAL_INSTRUCTION;
err:
	return error;
}

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
INTERN NONNULL((1, 3, 5)) unsigned int
NOTHROW_NCX(CC libuw_unwind_ste_read)(unwind_ste_t const *__restrict self, uint8_t addrsize,
                                      unwind_getreg_t regget, void const *regget_arg,
                                      void *__restrict dst, size_t num_bits,
                                      size_t dst_left_shift, size_t src_left_shift) {
	unsigned int error;
	(void)addrsize;
	switch (self->s_type) {

	case UNWIND_STE_STACKVALUE: {
		uintptr_t temp;
		temp = self->s_uconst;
		temp >>= src_left_shift;
		while (num_bits) {
			uintptr_t part;
			part = sizeof(temp) * NBBY;
			if (part > num_bits)
				part = num_bits;
			bitcpy(dst, dst_left_shift, (byte_t const *)&temp, 0, part);
			/* Update the number of stored piece bits. */
			dst_left_shift += part;
			num_bits -= part;
			temp >>= part;
		}
	}	break;

	case UNWIND_STE_REGPOINTER: {
		union {
			uintptr_t word;
			byte_t data[CFI_REGISTER_MAXSIZE];
		} regval;
		size_t reg_bits, max_bits;
		bzero(regval.data, sizeof(regval.data));
		error = (*regget)(regget_arg, self->s_register, regval.data);
		if unlikely(error != UNWIND_SUCCESS)
			ERRORF(err, "self->s_register = %u (%u)\n", (unsigned int)self->s_register, error);
		regval.word += self->s_regoffset;
		reg_bits = CFI_REGISTER_MEMSIZE(addrsize, self->s_register) * NBBY;
		if unlikely(src_left_shift >= reg_bits) {
			max_bits = 0;
		} else {
			max_bits = reg_bits - src_left_shift;
			if (max_bits > num_bits)
				max_bits = num_bits;
		}
		/* Copy in-bounds register data. */
		bitcpy(dst, dst_left_shift,
		       regval.data, src_left_shift,
		       max_bits);
		dst_left_shift += max_bits;
		num_bits -= max_bits;
		while (num_bits) {
			/* Fill out-of-bounds register data with all zeros. */
			bzero(regval.data, sizeof(regval.data));
			max_bits = sizeof(regval.data) * NBBY;
			if (max_bits > num_bits)
				max_bits = num_bits;
			bitcpy(dst, dst_left_shift,
			       regval.data, 0,
			       max_bits);
			dst_left_shift += max_bits;
			num_bits -= max_bits;
		}
	}	break;

	case UNWIND_STE_CONSTANT:
	case UNWIND_STE_REGISTER:
	case UNWIND_STE_RO_LVALUE:
	case UNWIND_STE_RW_LVALUE: {
		byte_t const *src;
		src = self->s_lvalue;
		if (self->s_type == UNWIND_STE_REGISTER) {
			/* Convert to l-value */
			union {
				uintptr_t p;
				byte_t buf[CFI_REGISTER_MAXSIZE];
			} regval;
			error = (*regget)(regget_arg, self->s_register, regval.buf);
			if unlikely(error != UNWIND_SUCCESS)
				ERRORF(err, "self->s_register = %u (%u)\n", (unsigned int)self->s_register, error);
			src = (byte_t *)regval.p + self->s_regoffset;
		}
		NESTED_TRY {
			bitcpy(dst, dst_left_shift,
			       src, src_left_shift,
			       num_bits);
		} EXCEPT {
			return UNWIND_SEGFAULT;
		}
	}	break;

	default:
		ERRORF(err_illegal_instruction, "self->s_type = %" PRIu8 "\n", self->s_type);
	}
	return UNWIND_SUCCESS;
err_illegal_instruction:
	return UNWIND_EMULATOR_ILLEGAL_INSTRUCTION;
err:
	return error;
}

INTERN NONNULL((1, 3, 7)) unsigned int
NOTHROW_NCX(CC libuw_unwind_ste_write)(unwind_ste_t const *__restrict self, uint8_t addrsize,
                                       /*[1..1]*/ unwind_getreg_t regget, void const *regget_arg,
                                       /*[0..1]*/ unwind_setreg_t regset, void *regset_arg,
                                       void const *__restrict src, size_t num_bits,
                                       size_t dst_left_shift, size_t src_left_shift) {
	unsigned int error;
	(void)addrsize;
	switch (self->s_type) {

	case UNWIND_STE_REGPOINTER: {
		union {
			uintptr_t word;
			byte_t data[CFI_REGISTER_MAXSIZE];
		} regval;
		size_t reg_bits;
		if unlikely(!regset)
			ERROR(err_not_writable);
		reg_bits = CFI_REGISTER_MEMSIZE(addrsize, self->s_register) * NBBY;
		if unlikely(dst_left_shift >= reg_bits)
			ERROR(err_not_writable);
		if unlikely(dst_left_shift + num_bits > reg_bits)
			num_bits = reg_bits - dst_left_shift;
		/* Write to a register. */
		if (dst_left_shift == 0 && num_bits == reg_bits) {
			/* Write whole register. */
		} else {
			error = (*regget)(regget_arg, self->s_register, regval.data);
			if unlikely(error != UNWIND_SUCCESS)
				ERRORF(err, "self->s_register = %u (%u)\n", (unsigned int)self->s_register, error);
			regval.word -= self->s_regoffset;
		}
		bitcpy(regval.data, dst_left_shift, src, src_left_shift, num_bits);
		regval.word += self->s_regoffset;
		/* Update the register value. */
		error = (*regset)(regset_arg, self->s_register, regval.data);
		if unlikely(error != UNWIND_SUCCESS)
			ERRORF(err, "self->s_register = %u (%u)\n", (unsigned int)self->s_register, error);
	}	break;

	case UNWIND_STE_CONSTANT:
	case UNWIND_STE_REGISTER:
	case UNWIND_STE_RW_LVALUE: {
/* 	case UNWIND_STE_RO_LVALUE: */
		byte_t *dst;
		dst = self->s_lvalue;
		if (self->s_type == UNWIND_STE_REGISTER) {
			/* Convert to l-value */
			union {
				uintptr_t word;
				byte_t data[CFI_REGISTER_MAXSIZE];
			} regval;
			error = (*regget)(regget_arg, self->s_register, regval.data);
			if unlikely(error != UNWIND_SUCCESS)
				ERRORF(err, "self->s_register = %u (%u)\n", (unsigned int)self->s_register, error);
			dst = (byte_t *)regval.word + self->s_regoffset;
		}
		/* Copy data into the l-value. */
		NESTED_TRY {
			bitcpy(dst, dst_left_shift,
			       src, src_left_shift,
			       num_bits);
		} EXCEPT {
			ERROR(err_segfault);
		}
	}	break;

	default:
		goto err_not_writable;
	}
	return UNWIND_SUCCESS;
err_segfault:
	return UNWIND_SEGFAULT;
err_not_writable:
	return UNWIND_EMULATOR_NOT_WRITABLE;
err:
	return error;
}

/* Do the equivalent of `READ_BITS(*ADDR_OF(ste))' */
PRIVATE ATTR_NOINLINE NONNULL((1, 2)) unsigned int CC
libuw_unwind_emulator_read_from_piece(unwind_emulator_t *__restrict self,
                                      unwind_ste_t const *__restrict ste,
                                      uintptr_t num_bits,
                                      size_t target_left_shift) {
	unsigned int result;
	if unlikely(((self->ue_piecebits + num_bits + NBBY - 1) / NBBY) > self->ue_piecesiz)
		ERROR(err_buffer_too_small);
	result = libuw_unwind_ste_read(ste,
	                               self->ue_addrsize,
	                               self->ue_regget,
	                               self->ue_regget_arg,
	                               self->ue_piecebuf,
	                               num_bits,
	                               self->ue_piecebits,
	                               target_left_shift);
	if (result == UNWIND_SUCCESS)
		self->ue_piecebits += num_bits; /* Update the number of consumed piece bits. */
	return result;
err_buffer_too_small:
	return UNWIND_EMULATOR_BUFFER_TOO_SMALL;
}


/* Do the equivalent of `WRITE_BITS(*ADDR_OF(ste))' */
PRIVATE ATTR_NOINLINE NONNULL((1, 2)) unsigned int CC
libuw_unwind_emulator_write_to_piece(unwind_emulator_t *__restrict self,
                                     unwind_ste_t const *__restrict ste,
                                     uintptr_t num_bits,
                                     size_t target_left_shift) {
	unsigned int result;
	if unlikely(((self->ue_piecebits + num_bits + NBBY - 1) / NBBY) > self->ue_piecesiz)
		ERROR(err_buffer_too_small);
	result = libuw_unwind_ste_write(ste,
	                                self->ue_addrsize,
	                                self->ue_regget,
	                                self->ue_regget_arg,
	                                self->ue_regset,
	                                self->ue_regset_arg,
	                                self->ue_piecebuf,
	                                num_bits,
	                                target_left_shift,
	                                self->ue_piecebits);
	if (result == UNWIND_SUCCESS)
		self->ue_piecebits += num_bits; /* Update the number of consumed piece bits. */
	return result;
err_buffer_too_small:
	return UNWIND_EMULATOR_BUFFER_TOO_SMALL;
}


PRIVATE NONNULL((1)) unsigned int CC
dispatch_DW_OP_entry_value(unwind_emulator_t *__restrict self) {
	unsigned int result;
	uintptr_t length;
	byte_t const *start_pc, *end_pc;
	length   = dwarf_decode_uleb128(&self->ue_pc);
	start_pc = self->ue_pc;
	end_pc   = self->ue_pc + length;

	/* Verify that the PC value fits into the current program bounds. */
	if unlikely(start_pc > end_pc ||
	            end_pc < self->ue_pc_start ||
	            end_pc > self->ue_pc_end)
		return UNWIND_EMULATOR_ILLEGAL_INSTRUCTION;

	/* Set-up the return-pc for later. */
	self->ue_pc = end_pc;

#ifndef __KERNEL__
	/* Lazily load libdebuginfo.so */
	if (!pdyn_debuginfo_run_entry_value_emulator &&
	    unlikely(libuw_load_libdebuginfo())) {
		/* If we can't get libdebuginfo.so to load, act  like
		 * we don't know the `DW_OP_entry_value' instruction. */
		return UNWIND_EMULATOR_UNKNOWN_INSTRUCTION;
	}
#endif /* !__KERNEL__ */

	/* Dispatch the call into `libdebuginfo.so'. */
	result = debuginfo_run_entry_value_emulator(self, start_pc, end_pc);
	return result;
}


/* Try to determine the base-address of the CFI-function containing `pc'
 * This does the same as `_Unwind_FindEnclosingFunction(3)', and is used
 * to resolve `DW_OP_GNU_encoded_addr+DW_EH_PE_funcrel' addresses.
 *
 * If the given `pc' doesn't belong to a function, return `0' */
PRIVATE ATTR_NOINLINE WUNUSED NONNULL((2)) unsigned int
NOTHROW_NCX(CC libuw_get_bases)(void const *pc, struct unwind_bases *__restrict bases) {
	unsigned int unwind_error;
	unwind_fde_t fde;
	unwind_error = libuw_unwind_fde_find(pc, &fde);
	if (unwind_error == UNWIND_SUCCESS)
		*bases = fde.f_bases;
	return unwind_error;
}



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
INTERN ATTR_NOINLINE NONNULL((1)) unsigned int CC
libuw_unwind_emulator_exec(unwind_emulator_t *__restrict self) {
	byte_t const *pc;
	size_t stacksz;
	byte_t opcode;
	unsigned int error;
	pc      = self->ue_pc;
	stacksz = self->ue_stacksz;
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
				value = (uintptr_t)UNALIGNED_GET32((uint32_t const *)pc);
#endif /* __SIZEOF_POINTER__ > 4 */
			} else if (self->ue_addrsize >= 2) {
				value = (uintptr_t)UNALIGNED_GET16((uint16_t const *)pc);
			} else {
				value = (uintptr_t)(*(uint8_t const *)pc);
			}

			/* To quote a comment found within the GDB source tree:
			 * """
			 *   Some versions of GCC emit DW_OP_addr before
			 *   DW_OP_GNU_push_tls_address. In this case the value is an
			 *   index, not  an address.  We  don't support  things  like
			 *   branching between the address and the TLS op.
			 * """
			 * So just mirror what it  does, and don't include the  module
			 * offset when the next opcode is `DW_OP_GNU_push_tls_address' */
			if (pc < self->ue_pc_end && *pc == DW_OP_GNU_push_tls_address) {
				/* ... */
			} else {
				value += self->ue_addroffset; /* Include the module loadaddr. */
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
do_make_top_const_or_register:
				if (TOP.s_type == UNWIND_STE_REGPOINTER) {
					TOP.s_type = UNWIND_STE_REGISTER;
					goto again_switch_opcode;
				}
do_make_top_const:
				if (TOP.s_type == UNWIND_STE_REGISTER ||
				    TOP.s_type == UNWIND_STE_REGPOINTER) {
					union {
						uintptr_t p;
						byte_t buf[CFI_REGISTER_MAXSIZE];
					} regval;
					error = (*self->ue_regget)(self->ue_regget_arg, TOP.s_register, regval.buf);
					if unlikely(error != UNWIND_SUCCESS)
						ERRORF(err, "TOP.s_register = %u (%u)\n", (unsigned int)TOP.s_register, error);
					TOP.s_uconst = regval.p + TOP.s_regoffset;
				} else if (TOP.s_type == UNWIND_STE_RW_LVALUE ||
				           TOP.s_type == UNWIND_STE_RO_LVALUE) {
					if (TOP.s_lsize >= sizeof(uintptr_t)) {
						if unlikely(!guarded_readptr((uintptr_t *)TOP.s_lvalue, &TOP.s_uconst))
							ERROR(err_segfault);
#if __SIZEOF_POINTER__ > 4
					} else if (TOP.s_lsize >= 4) {
						if unlikely(!guarded_readl((uint32_t *)TOP.s_lvalue, &TOP.s_uconst))
							ERROR(err_segfault);
#endif /* __SIZEOF_POINTER__ > 4 */
					} else if (TOP.s_lsize >= 2) {
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
		DEFINE_PUSH_CONSTANT(DW_OP_const1u, s_uconst, (uintptr_t)(*(uint8_t const *)pc), 1)
		DEFINE_PUSH_CONSTANT(DW_OP_const1s, s_sconst, (intptr_t)(*(int8_t const *)pc), 1)
		DEFINE_PUSH_CONSTANT(DW_OP_const2u, s_uconst, (uintptr_t)UNALIGNED_GET16((uint16_t const *)pc), 2)
		DEFINE_PUSH_CONSTANT(DW_OP_const2s, s_sconst, (intptr_t)(int16_t)UNALIGNED_GET16((uint16_t const *)pc), 2)
		DEFINE_PUSH_CONSTANT(DW_OP_const4u, s_uconst, (uintptr_t)UNALIGNED_GET32((uint32_t const *)pc), 4)
		DEFINE_PUSH_CONSTANT(DW_OP_const4s, s_sconst, (intptr_t)(int32_t)UNALIGNED_GET32((uint32_t const *)pc), 4)
#if __SIZEOF_POINTER__ > 4
		DEFINE_PUSH_CONSTANT(DW_OP_const8u, s_uconst, (uintptr_t)UNALIGNED_GET64((uint64_t const *)pc), 8)
		DEFINE_PUSH_CONSTANT(DW_OP_const8s, s_sconst, (intptr_t)(int64_t)UNALIGNED_GET64((uint64_t const *)pc), 8)
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		DEFINE_PUSH_CONSTANT(DW_OP_const8u, s_uconst, (uintptr_t)UNALIGNED_GET32((uint32_t const *)pc), 8)
		DEFINE_PUSH_CONSTANT(DW_OP_const8s, s_sconst, (intptr_t)(int32_t)UNALIGNED_GET32((uint32_t const *)pc), 8)
#else /* ... */
		DEFINE_PUSH_CONSTANT(DW_OP_const8u, s_uconst, (uintptr_t)UNALIGNED_GET32((uint32_t const *)(pc + 4)), 8)
		DEFINE_PUSH_CONSTANT(DW_OP_const8s, s_sconst, (intptr_t)(int32_t)UNALIGNED_GET32((uint32_t const *)(pc + 4)), 8)
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
			uint8_t nth = *(uint8_t const *)pc;
			if unlikely(nth >= stacksz)
				ERROR(err_stack_underflow);
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			pc += 1;
			self->ue_stack[stacksz] = self->ue_stack[(stacksz - 1) - nth];
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

		CASE(DW_OP_plus)
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			if (SECOND.s_type != UNWIND_STE_CONSTANT) {
do_make_second_const_or_register:
				if (SECOND.s_type == UNWIND_STE_REGPOINTER) {
					SECOND.s_type = UNWIND_STE_REGISTER;
					goto again_switch_opcode;
				}
do_make_second_const:
				if (SECOND.s_type == UNWIND_STE_REGISTER ||
				    SECOND.s_type == UNWIND_STE_REGPOINTER) {
					union {
						uintptr_t p;
						byte_t buf[CFI_REGISTER_MAXSIZE];
					} regval;
					error = (*self->ue_regget)(self->ue_regget_arg, SECOND.s_register, regval.buf);
					if unlikely(error != UNWIND_SUCCESS)
						ERRORF(err, "SECOND.s_register = %u (%u)\n", (unsigned int)SECOND.s_register, error);
					SECOND.s_uconst = regval.p + SECOND.s_regoffset;
				} else if (SECOND.s_type == UNWIND_STE_RW_LVALUE ||
				           SECOND.s_type == UNWIND_STE_RO_LVALUE) {
					if (SECOND.s_lsize >= sizeof(uintptr_t)) {
						if unlikely(!guarded_readptr((uintptr_t *)SECOND.s_lvalue, &SECOND.s_uconst))
							ERROR(err_segfault);
#if __SIZEOF_POINTER__ > 4
					} else if (SECOND.s_lsize >= 4) {
						if unlikely(!guarded_readl((uint32_t *)SECOND.s_lvalue, &SECOND.s_uconst))
							ERROR(err_segfault);
#endif /* __SIZEOF_POINTER__ > 4 */
					} else if (SECOND.s_lsize >= 2) {
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
			SECOND.s_uconst += TOP.s_uconst;
			--stacksz;
			break;

		CASE(DW_OP_plus_uconst)
			if unlikely(stacksz < 1)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT &&
			    TOP.s_type != UNWIND_STE_REGISTER)
				goto do_make_top_const_or_register;
			TOP.s_uconst += dwarf_decode_uleb128(&pc);
			break;

		CASE(DW_OP_minus)
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			if (SECOND.s_type != UNWIND_STE_CONSTANT &&
			    SECOND.s_type != UNWIND_STE_REGISTER)
				goto do_make_second_const_or_register;
			SECOND.s_uconst -= TOP.s_uconst;
			--stacksz;
			break;

		CASE(DW_OP_abs)
		CASE(DW_OP_neg)
		CASE(DW_OP_not)
			/* Unary (1-operand) arithmetic and bit-wise operators. */
			if unlikely(stacksz < 1)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			switch (opcode) {
			case DW_OP_abs:
				TOP.s_sconst = abs(TOP.s_sconst);
				break;
			case DW_OP_neg:
				TOP.s_sconst = -TOP.s_sconst;
				break;
			case DW_OP_not:
				TOP.s_uconst = ~TOP.s_uconst;
				break;
			default:
				__builtin_unreachable();
			}
			break;

		CASE(DW_OP_div)
		CASE(DW_OP_mod)
		CASE(DW_OP_and)
		CASE(DW_OP_mul)
		CASE(DW_OP_or)
		CASE(DW_OP_shl)
		CASE(DW_OP_shr)
		CASE(DW_OP_shra)
		CASE(DW_OP_xor)
		CASE(DW_OP_eq)
		CASE(DW_OP_ge)
		CASE(DW_OP_gt)
		CASE(DW_OP_le)
		CASE(DW_OP_lt)
		CASE(DW_OP_ne)
			/* Binary (2-operand) arithmetic and bit-wise operators. */
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			if (SECOND.s_type != UNWIND_STE_CONSTANT)
				goto do_make_second_const;
			switch (opcode) {
			case DW_OP_div:
			case DW_OP_mod:
				if unlikely(TOP.s_sconst == 0)
					ERROR(err_divide_by_zero);
				if (opcode == DW_OP_div) {
					SECOND.s_sconst /= TOP.s_sconst;
				} else {
					SECOND.s_sconst %= TOP.s_sconst;
				}
				break;
			case DW_OP_and:
				SECOND.s_uconst &= TOP.s_uconst;
				break;
			case DW_OP_mul:
				SECOND.s_sconst *= TOP.s_sconst;
				break;
			case DW_OP_or:
				SECOND.s_uconst |= TOP.s_uconst;
				break;
			case DW_OP_shl:
				SECOND.s_uconst <<= TOP.s_uconst;
				break;
			case DW_OP_shr:
				SECOND.s_uconst >>= TOP.s_uconst;
				break;
			case DW_OP_shra:
#ifdef __ARCH_SIGNED_SHIFT_IS_SDIV
				SECOND.s_sconst >>= TOP.s_uconst;
#else /* __ARCH_SIGNED_SHIFT_IS_SDIV */
				SECOND.s_sconst = SECOND.s_sconst < 0
				                  ? (intptr_t)-1 - (((intptr_t)-1 - SECOND.s_sconst) >> TOP.s_uconst)
				                  : SECOND.s_sconst >> TOP.s_uconst;
#endif /* !__ARCH_SIGNED_SHIFT_IS_SDIV */
				break;
			case DW_OP_xor:
				SECOND.s_uconst ^= TOP.s_uconst;
				break;
			case DW_OP_eq:
				SECOND.s_uconst = SECOND.s_uconst == TOP.s_uconst ? 1 : 0;
				break;
			case DW_OP_ge:
				SECOND.s_uconst = SECOND.s_sconst >= TOP.s_sconst ? 1 : 0;
				break;
			case DW_OP_gt:
				SECOND.s_uconst = SECOND.s_sconst > TOP.s_sconst ? 1 : 0;
				break;
			case DW_OP_le:
				SECOND.s_uconst = SECOND.s_sconst <= TOP.s_sconst ? 1 : 0;
				break;
			case DW_OP_lt:
				SECOND.s_uconst = SECOND.s_sconst < TOP.s_sconst ? 1 : 0;
				break;
			case DW_OP_ne:
				SECOND.s_uconst = SECOND.s_uconst != TOP.s_uconst ? 1 : 0;
				break;
			default:
				__builtin_unreachable();
			}
			--stacksz;
			break;

		CASE(DW_OP_skip) {
			int16_t offset;
			offset = (int16_t)UNALIGNED_GET16((uint16_t const *)pc);
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
			if unlikely(stacksz < 1)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			if (TOP.s_uconst != 0) {
				int16_t offset;
				offset = (int16_t)UNALIGNED_GET16((uint16_t const *)pc);
				pc += 2;
				if (offset < 0) {
					if unlikely(!self->ue_bjmprem)
						ERROR(err_loop);
					--self->ue_bjmprem;
				}
				pc += offset;
				if unlikely(pc < self->ue_pc_start ||
				            pc >= self->ue_pc_end) {
					if likely(pc == self->ue_pc_end) {
						--stacksz;
						goto done;
					}
					pc -= offset;
					pc -= 3;
					ERROR(err_badjmp);
				}
			} else {
				pc += 2;
			}
			--stacksz;
		}	break;

		CASE(DW_OP_lit0 ... DW_OP_lit31)
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			self->ue_stack[stacksz].s_type   = UNWIND_STE_CONSTANT;
			self->ue_stack[stacksz].s_uconst = opcode - DW_OP_lit0;
			++stacksz;
			break;

		CASE(DW_OP_reg0 ... DW_OP_reg31)
			/* NOTE: These opcodes push the address of a register (within an imaginary register map)!
			 *       Not  the actual value of the register  (except when interpreted in arithmetic or
			 *       as the result of a .eh_frame expression) */
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			self->ue_stack[stacksz].s_type      = UNWIND_STE_REGPOINTER;
			self->ue_stack[stacksz].s_register  = opcode - DW_OP_reg0;
			self->ue_stack[stacksz].s_regoffset = 0;
			++stacksz;
			break;

		CASE(DW_OP_regx)
			/* NOTE: This opcode pushes the address of a register (within an imaginary register map)!
			 *       Not  the actual value of the register  (except when interpreted in arithmetic or
			 *       as the result of a .eh_frame expression) */
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			self->ue_stack[stacksz].s_type      = UNWIND_STE_REGPOINTER;
			self->ue_stack[stacksz].s_register  = (unwind_regno_t)dwarf_decode_uleb128(&pc);
			self->ue_stack[stacksz].s_regoffset = 0;
			++stacksz;
			break;

		CASE(DW_OP_fbreg) {
			byte_t const *expr, *old_pc_start, *old_pc_end;
			di_debuginfo_location_t const *old_frame_base;
			unsigned int error;
			size_t length;
			if unlikely(!self->ue_framebase)
				ERROR(err_illegal_instruction);
			expr = libuw_debuginfo_location_select(self->ue_framebase,
			                                       self->ue_cu ? self->ue_cu->cu_ranges.r_startpc : 0,
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

		CASE(DW_OP_breg0 ... DW_OP_breg31) {
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			self->ue_stack[stacksz].s_type      = UNWIND_STE_REGISTER;
			self->ue_stack[stacksz].s_register  = opcode - DW_OP_breg0;
			self->ue_stack[stacksz].s_regoffset = dwarf_decode_sleb128(&pc);
			++stacksz;
		}	break;

		CASE(DW_OP_bregx) {
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			self->ue_stack[stacksz].s_type      = UNWIND_STE_REGISTER;
			self->ue_stack[stacksz].s_register  = (unwind_regno_t)dwarf_decode_uleb128(&pc);
			self->ue_stack[stacksz].s_regoffset = dwarf_decode_sleb128(&pc);
			++stacksz;
		}	break;

		CASE(DW_OP_piece) {
			uintptr_t num_bits;
			size_t target_left_shift;
			unsigned int error;
			if unlikely(stacksz < 1)
				ERROR(err_stack_underflow);
			target_left_shift = 0;
			if (self->ue_piecewrite) {
				if unlikely(TOP.s_type != UNWIND_STE_REGISTER &&
				            TOP.s_type != UNWIND_STE_RW_LVALUE)
					ERROR(err_not_writable);
				num_bits = dwarf_decode_uleb128(&pc) * NBBY;
				goto do_write_bit_pieces;
			}
			num_bits = dwarf_decode_uleb128(&pc) * NBBY;
			goto do_read_bit_pieces;
		CASE(DW_OP_bit_piece)
			if unlikely(stacksz < 1)
				ERROR(err_stack_underflow);
			if (self->ue_piecewrite) {
				if unlikely(TOP.s_type != UNWIND_STE_REGISTER &&
				            TOP.s_type != UNWIND_STE_RW_LVALUE)
					ERROR(err_not_writable); /* Read-only target location. */
				num_bits          = dwarf_decode_uleb128(&pc);
				target_left_shift = dwarf_decode_uleb128(&pc);
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
			TOP.s_lsize = *(uint8_t const *)pc;
			pc += 1;
			break;

		CASE(DW_OP_xderef_size)
			if unlikely(stacksz < 2)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			/* Turn a constant into an l-value. */
			SECOND.s_type   = UNWIND_STE_RW_LVALUE;
			SECOND.s_lsize  = *(uint8_t const *)pc;
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
			byte_t const *component_address;
			unsigned int error;
			if unlikely(self->ue_sectinfo == NULL ||
			            self->ue_sectinfo->ues_debug_info_start >= self->ue_sectinfo->ues_debug_info_end ||
			            self->ue_sectinfo->ues_debug_abbrev_start >= self->ue_sectinfo->ues_debug_abbrev_end)
				ERROR(err_illegal_instruction);
			self->ue_pc = pc - 1;
			if (opcode == DW_OP_call2) {
				component_address = self->ue_sectinfo->ues_debug_info_start +
					                (uintptr_t)UNALIGNED_GET16((uint16_t const *)pc);
				pc += 2;
			} else if (opcode == DW_OP_call4 || self->ue_ptrsize == 4) {
				component_address = self->ue_sectinfo->ues_debug_info_start +
					                (uintptr_t)UNALIGNED_GET32((uint32_t const *)pc);
				pc += 4;
			} else {
				assert(self->ue_ptrsize == 8);
				component_address = self->ue_sectinfo->ues_debug_info_start +
					                (uintptr_t)UNALIGNED_GET64((uint64_t const *)pc);
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
		CASE(DW_OP_GNU_push_tls_address)
			if unlikely(!self->ue_tlsbase)
				ERROR(err_illegal_instruction);
			if unlikely(stacksz < 1)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT &&
			    TOP.s_type != UNWIND_STE_REGISTER)
				goto do_make_top_const_or_register;
			if (self->ue_tlsbase == (byte_t *)-1) {
#ifdef __KERNEL__
				RD_TLS_BASE_REGISTER(*(void **)&self->ue_tlsbase);
#ifdef CONFIG_HAVE_DEBUGGER
				if unlikely(dbg_active)
					self->ue_tlsbase = (byte_t *)dbg_current;
#endif /* CONFIG_HAVE_DEBUGGER */
#else /* __KERNEL__ */
				{
					/* Try to use the TLS-base of the associated module */
					void *base = dltlsaddr(dlgethandle(pc));
					if (base != NULL) {
						self->ue_tlsbase = (byte_t *)base;
					} else {
						RD_TLS_BASE_REGISTER(*(void **)&self->ue_tlsbase);
					}
				}
#endif /* !__KERNEL__ */
			}
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
			self->ue_stack[stacksz].s_lvalue = (byte_t *)pc;
			self->ue_stack[stacksz].s_lsize  = (unwind_regno_t)size;
			pc += size;
			++stacksz;
		}	break;

		CASE(DW_OP_stack_value)
			if unlikely(stacksz < 1)
				ERROR(err_stack_underflow);
			if (TOP.s_type != UNWIND_STE_CONSTANT)
				goto do_make_top_const;
			TOP.s_type = UNWIND_STE_STACKVALUE;
			break;

		CASE(DW_OP_addrx)
		CASE(DW_OP_GNU_addr_index)
		CASE(DW_OP_constx)
		CASE(DW_OP_GNU_const_index) {
			byte_t const *debug_addr_loc, *debug_addr_end;
			uintptr_t value;
			if unlikely(!self->ue_sectinfo)
				ERROR(err_illegal_instruction);
			debug_addr_loc = self->ue_sectinfo->ues_debug_addr_start;
			debug_addr_loc += dwarf_decode_uleb128(&pc);
			if (self->ue_cu)
				debug_addr_loc += self->ue_cu->cu_addr_base;
			if (debug_addr_loc < self->ue_sectinfo->ues_debug_addr_start)
				ERROR(err_illegal_instruction); /* Out-of-bounds */
			if (OVERFLOW_UADD((uintptr_t)debug_addr_loc, self->ue_addrsize,
			                  (uintptr_t *)&debug_addr_end))
				ERROR(err_illegal_instruction); /* Out-of-bounds */
			if (debug_addr_end > self->ue_sectinfo->ues_debug_addr_end)
				ERROR(err_illegal_instruction); /* Out-of-bounds */
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			if (self->ue_addrsize >= sizeof(uintptr_t)) {
				value = UNALIGNED_GET((uintptr_t *)debug_addr_loc);
#if __SIZEOF_POINTER__ > 4
			} else if (self->ue_addrsize >= 4) {
				value = (uintptr_t)UNALIGNED_GET32((uint32_t const *)debug_addr_loc);
#endif /* __SIZEOF_POINTER__ > 4 */
			} else if (self->ue_addrsize >= 2) {
				value = (uintptr_t)UNALIGNED_GET16((uint16_t const *)debug_addr_loc);
			} else {
				value = (uintptr_t)(*(uint8_t const *)debug_addr_loc);
			}
			self->ue_stack[stacksz].s_type   = UNWIND_STE_CONSTANT;
			self->ue_stack[stacksz].s_uconst = value;
			++stacksz;
		}	break;

		CASE(DW_OP_GNU_uninit)
			/* ??? */
			break;

		CASE(DW_OP_GNU_encoded_addr) {
			uint8_t format;
			uintptr_t value;
			if unlikely(stacksz >= self->ue_stackmax)
				ERROR(err_stack_overflow);
			format = *pc++;
			if ((DW_EH_PE_BASE(format) == DW_EH_PE_textrel && self->ue_bases.ub_tbase == NULL) ||
			    (DW_EH_PE_BASE(format) == DW_EH_PE_datarel && self->ue_bases.ub_dbase == NULL) ||
			    (DW_EH_PE_BASE(format) == DW_EH_PE_funcrel && self->ue_bases.ub_fbase == NULL)) {
				/* Figure out base addresses. */
				union {
					void const *p;
					byte_t buf[CFI_REGISTER_MAXSIZE];
				} regval;
				error = (*self->ue_regget)(self->ue_regget_arg,
					                       CFI_UNWIND_REGISTER_PC(self->ue_addrsize),
					                       regval.buf);
				if unlikely(error != UNWIND_SUCCESS)
					ERRORF(err, "Can't get PC register: %u\n", error);
				error = libuw_get_bases(regval.p, &self->ue_bases);
				if unlikely(error != UNWIND_SUCCESS) {
					/* Failed to determine function base address. */
					error = UNWIND_NO_FRAME;
					ERRORF(err, "No FDE at pc %p\n", regval.p);
				}
			}
			value = (uintptr_t)dwarf_decode_pointer(&pc, format, self->ue_addrsize, &self->ue_bases);
			self->ue_stack[stacksz].s_type   = UNWIND_STE_CONSTANT;
			self->ue_stack[stacksz].s_uconst = value;
			++stacksz;
		}	break;

		CASE(DW_OP_entry_value)
		CASE(DW_OP_GNU_entry_value) {
			unsigned int error;
			self->ue_pc      = pc;
			self->ue_stacksz = stacksz;
			/* Dispatch the instruction. */
			error = dispatch_DW_OP_entry_value(self);
			if unlikely(error != UNWIND_SUCCESS) {
				self->ue_pc      = pc - 1;
				self->ue_stacksz = stacksz;
				return error;
			}
			pc      = self->ue_pc;
			stacksz = self->ue_stacksz;
		}	break;

		default:
			ERRORF(err_unknown_instruction, "opcode = %#.2" PRIx8 " (%p/%p/%p/%" PRIuSIZ ")\n%$[hex]\n",
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
err_not_writable:
	error = UNWIND_EMULATOR_NOT_WRITABLE;
	goto err;
err_badjmp:
	error = UNWIND_EMULATOR_BADJMP;
	goto err;
err_loop:
	error = UNWIND_EMULATOR_LOOP;
	goto err;
err_divide_by_zero:
	error = UNWIND_EMULATOR_DIVIDE_BY_ZERO;
	goto err;
err_illegal_instruction:
	error = UNWIND_EMULATOR_ILLEGAL_INSTRUCTION;
	goto err;
err_unknown_instruction:
	error = UNWIND_EMULATOR_UNKNOWN_INSTRUCTION;
	goto err;
err_segfault:
	error = UNWIND_SEGFAULT;
	goto err;
err_stack_underflow:
	error = UNWIND_EMULATOR_STACK_UNDERFLOW;
	goto err;
err_stack_overflow:
	error = UNWIND_EMULATOR_STACK_OVERFLOW;
err:
	self->ue_pc      = pc - 1;
	self->ue_stacksz = stacksz;
	return error;
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
#endif /* __KERNEL__ */
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
#if 0 /* This  also  works,  but generates  FPU  instructions on
       * x86_64 (which may fault if the kernel is out-of-memory) */
		stack[0] = *pentry_stack_top;
#else
		memcpy(&stack[0], pentry_stack_top,
		       sizeof(*pentry_stack_top));
#endif
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
#endif /* __KERNEL__ */
}

INTERN NONNULL((1)) unsigned int CC
libuw_unwind_emulator_exec_autostack(unwind_emulator_t *__restrict self,
                                     unwind_ste_t const *pentry_stack_top,
                                     unwind_ste_t *pexit_stack_top,
                                     uintptr_t *pexit_stack_top_const) {
	unsigned int error;
	/* First off: Try  to allocate  an execution  stack on  our own stack.
	 *            If that stack overflows, move  on to allocating a  stack
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
#if 0 /* This  also  works,  but generates  FPU  instructions on
       * x86_64 (which may fault if the kernel is out-of-memory) */
				stack[0] = *pentry_stack_top;
#else
				memcpy(&stack[0], pentry_stack_top,
				       sizeof(*pentry_stack_top));
#endif
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


/* Return a pointer to the next unwind instruction following `unwind_pc'
 * -> Useful for dumping unwind instruction without having to take care
 *    of handling all possible instruction  (after all: CFI has a  CISC
 *    instruction set with variable-length instructions)
 * @param: addrsize: Size of a target address.
 * @param: ptrsize:  Size of a DWARF pointer (4 for 32-bit dwarf; 8 for 64-bit dwarf).
 * @return: NULL: The instruction at `unwind_pc' wasn't recognized. */
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
	case DW_OP_lit0 ... DW_OP_lit31:
	case DW_OP_reg0 ... DW_OP_reg31:
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

	case DW_OP_call_ref:
		unwind_pc += ptrsize;
		break;

	case DW_OP_bregx:
		dwarf_decode_uleb128((byte_t const **)&unwind_pc);
		ATTR_FALLTHROUGH
	case DW_OP_consts:
	case DW_OP_breg0 ... DW_OP_breg31:
	case DW_OP_fbreg:
skip_1_sleb128:
		dwarf_decode_sleb128((byte_t const **)&unwind_pc);
		break;

	case DW_OP_bit_piece:
		dwarf_decode_uleb128((byte_t const **)&unwind_pc);
		ATTR_FALLTHROUGH
	case DW_OP_constu:
	case DW_OP_regx:
	case DW_OP_piece:
	case DW_OP_addrx:
	case DW_OP_GNU_addr_index:
	case DW_OP_constx:
	case DW_OP_GNU_const_index:
skip_1_uleb128:
		dwarf_decode_uleb128((byte_t const **)&unwind_pc);
		break;

	case DW_OP_implicit_value:
	case DW_OP_entry_value:
	case DW_OP_GNU_entry_value: {
		dwarf_uleb128_t size;
		size = dwarf_decode_uleb128((byte_t const **)&unwind_pc);
		unwind_pc += size;
	}	break;

	case DW_OP_GNU_encoded_addr: {
		uint8_t encoding;
		encoding = *unwind_pc++;
#if 0
		dwarf_decode_pointer((byte_t const **)&unwind_pc, encoding, addrsize, NULL);
#else
		if (DW_EH_PE_BASE(encoding) == DW_EH_PE_aligned)
			unwind_pc = (byte_t const *)(((uintptr_t)unwind_pc + (addrsize - 1)) & ~(addrsize - 1));
		switch (DW_EH_PE_OFF(encoding)) {
		case DW_EH_PE_absptr:
			unwind_pc += addrsize;
			break;
		case DW_EH_PE_udata2:
		case DW_EH_PE_sdata2:
			unwind_pc += 2;
			break;
		case DW_EH_PE_udata4:
		case DW_EH_PE_sdata4:
			unwind_pc += 4;
			break;
		case DW_EH_PE_udata8:
		case DW_EH_PE_sdata8:
			unwind_pc += 8;
			break;
		case DW_EH_PE_uleb128:
			goto skip_1_uleb128;
		case DW_EH_PE_sleb128:
			goto skip_1_sleb128;

		default:
			unwind_pc += 1; /* ??? */
			break;
		}
#endif
	}	break;

	default:
		unwind_pc = NULL;
		break;
	}
	return unwind_pc;
}



/* Return a pointer to a CFI expression that is applicable for `cu_base + module_relative_pc'
 * If no such expression exists, return `NULL' instead. */
INTERN WUNUSED NONNULL((1, 5)) byte_t const *
NOTHROW_NCX(CC libuw_debuginfo_location_select)(di_debuginfo_location_t const *__restrict self,
                                                uintptr_t cu_base,
                                                uintptr_t module_relative_pc,
                                                uint8_t addrsize,
                                                size_t *__restrict pexpr_length) {
	/* Check for simple case: Only a single, universal expression is defined */
	byte_t const *reader;
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
				range_start = UNALIGNED_GET((uintptr_t const *)reader);
				reader += addrsize;
				range_end = UNALIGNED_GET((uintptr_t const *)reader);
				reader += addrsize;
#if __SIZEOF_POINTER__ > 4
			} else if (addrsize >= 4) {
				range_start = UNALIGNED_GET32((uint32_t const *)reader);
				reader += addrsize;
				range_end = UNALIGNED_GET32((uint32_t const *)reader);
				reader += addrsize;
#endif /* __SIZEOF_POINTER__ > 4 */
			} else if (addrsize >= 2) {
				range_start = UNALIGNED_GET16((uint16_t const *)reader);
				reader += addrsize;
				range_end = UNALIGNED_GET16((uint16_t const *)reader);
				reader += addrsize;
			} else {
				range_start = *(uint8_t const *)reader;
				reader += addrsize;
				range_end = *(uint8_t const *)reader;
				reader += addrsize;
			}
			/* Handle special entries */
			if (range_start == (uintptr_t)-1) {
				/* Base address selection entry! */
				cu_base = range_end;
				goto skip_entry;
			}
			if (!range_start && !range_end)
				break; /* Location list end entry. */
			range_start += cu_base;
			range_end += cu_base;
			TRACE("%p: RANGE(%p-%p) with %" PRIu16 "\n",
			      reader - 2 * addrsize,
			      range_start,
			      range_end,
			      UNALIGNED_GET16((uint16_t const *)reader));
			if (module_relative_pc >= range_start &&
			    module_relative_pc < range_end) {
				*pexpr_length = (size_t)UNALIGNED_GET16((uint16_t const *)reader);
				reader += 2;
				return reader; /* Found it! */
			}
			/* Skip the associated expression. */
			{
				uint16_t expr_length;
skip_entry:
				expr_length = UNALIGNED_GET16((uint16_t const *)reader);
				reader += 2;
				reader += expr_length;
			}
		}
	}
	*pexpr_length = 0;
	return NULL;
}




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
INTERN NONNULL((1, 3, 8, 10)) unsigned int CC
libuw_debuginfo_location_getvalue(di_debuginfo_location_t const *__restrict self,
                                  unwind_emulator_sections_t const *sectinfo,
                                  unwind_getreg_t regget, void *regget_arg,
                                  struct di_debuginfo_compile_unit_simple_struct const *cu,
                                  uintptr_t module_relative_pc, uintptr_t module_addroffset,
                                  void *__restrict buf, size_t bufsize,
                                  size_t *__restrict pnum_written_bits,
                                  di_debuginfo_location_t const *frame_base_expression,
                                  void const *objaddr, uint8_t addrsize, uint8_t ptrsize) {
	unwind_ste_t ste_top;
	unwind_emulator_t emulator;
	size_t expr_length;
	unsigned int result;
	bzero(&emulator, sizeof(emulator));
	bzero(buf, bufsize); /* Pre-initialize the buffer to all zeroes */

	/* Select the proper function. */
	emulator.ue_pc = libuw_debuginfo_location_select(self,
	                                                 cu ? cu->cu_ranges.r_startpc : 0,
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
	emulator.ue_addroffset         = module_addroffset;
	emulator.ue_objaddr            = (void *)objaddr;
	emulator.ue_bjmprem            = UNWIND_EMULATOR_BJMPREM_DEFAULT;
	emulator.ue_addrsize           = addrsize;
	emulator.ue_ptrsize            = ptrsize;
	emulator.ue_piecebuf           = (byte_t *)buf;
	emulator.ue_piecesiz           = bufsize;
	emulator.ue_cu                 = cu;
	emulator.ue_module_relative_pc = module_relative_pc;
	/* Execute the emulator. */
	result = libuw_unwind_emulator_exec_autostack(&emulator, NULL, &ste_top, NULL);
	assert(emulator.ue_piecebits <= bufsize * NBBY);
	if (result == UNWIND_EMULATOR_NO_RETURN_VALUE)
		result = UNWIND_SUCCESS; /* No stack-entry location. */
	else if (result == UNWIND_SUCCESS) {
		/* Dereference the last stack to fill in the missing data pieces. */
		result = libuw_unwind_emulator_read_from_piece(&emulator,
		                                               &ste_top,
		                                               (bufsize * NBBY) -
		                                               emulator.ue_piecebits,
		                                               0);
	}
	*pnum_written_bits = emulator.ue_piecebits;
	return result;
err_no_function:
	return UNWIND_EMULATOR_NO_FUNCTION;
}


INTERN NONNULL((1, 3, 5, 10, 12)) unsigned int CC
libuw_debuginfo_location_setvalue(di_debuginfo_location_t const *__restrict self,
                                  unwind_emulator_sections_t const *sectinfo,
                                  unwind_getreg_t regget, void *regget_arg,
                                  unwind_setreg_t regset, void *regset_arg,
                                  struct di_debuginfo_compile_unit_simple_struct const *cu,
                                  uintptr_t module_relative_pc, uintptr_t module_addroffset,
                                  void const *__restrict buf, size_t bufsize,
                                  size_t *__restrict pnum_read_bits,
                                  di_debuginfo_location_t const *frame_base_expression,
                                  void *objaddr, uint8_t addrsize, uint8_t ptrsize) {
	unwind_ste_t ste_top;
	unwind_emulator_t emulator;
	size_t expr_length;
	unsigned int result;
	bzero(&emulator, sizeof(emulator));

	/* Select the proper function. */
	emulator.ue_pc = libuw_debuginfo_location_select(self,
	                                                 cu ? cu->cu_ranges.r_startpc : 0,
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
	emulator.ue_addroffset         = module_addroffset;
	emulator.ue_objaddr            = objaddr;
	emulator.ue_bjmprem            = UNWIND_EMULATOR_BJMPREM_DEFAULT;
	emulator.ue_addrsize           = addrsize;
	emulator.ue_ptrsize            = ptrsize;
	emulator.ue_piecewrite         = 1;
	emulator.ue_piecebuf           = (byte_t *)buf;
	emulator.ue_piecesiz           = bufsize;
	emulator.ue_cu                 = cu;
	emulator.ue_module_relative_pc = module_relative_pc;
	/* Execute the emulator. */
	result = libuw_unwind_emulator_exec_autostack(&emulator, NULL, &ste_top, NULL);
	assert(emulator.ue_piecebits <= bufsize * NBBY);
	if (result == UNWIND_EMULATOR_NO_RETURN_VALUE)
		result = UNWIND_SUCCESS; /* No stack-entry location. */
	else if (result == UNWIND_SUCCESS) {
		/* Dereference the last stack to fill in the missing data pieces. */
		result = libuw_unwind_emulator_write_to_piece(&emulator,
		                                              &ste_top,
		                                              (bufsize * NBBY) -
		                                              emulator.ue_piecebits,
		                                              0);
	} else {
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
DEFINE_PUBLIC_ALIAS(unwind_ste_addr, libuw_unwind_ste_addr);
DEFINE_PUBLIC_ALIAS(unwind_ste_read, libuw_unwind_ste_read);
DEFINE_PUBLIC_ALIAS(unwind_ste_write, libuw_unwind_ste_write);
DEFINE_PUBLIC_ALIAS(debuginfo_location_select, libuw_debuginfo_location_select);
DEFINE_PUBLIC_ALIAS(debuginfo_location_getvalue, libuw_debuginfo_location_getvalue);
DEFINE_PUBLIC_ALIAS(debuginfo_location_setvalue, libuw_debuginfo_location_setvalue);

DECL_END

#endif /* !GUARD_LIBUNWIND_CFI_C */
