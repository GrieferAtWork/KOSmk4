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
#ifndef _I386_KOS_KOS_BITS_EXCEPTION_DATA32_H
#define _I386_KOS_KOS_BITS_EXCEPTION_DATA32_H 1

#include <__stdinc.h>

#include <hybrid/__pointer.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <kos/bits/except.h> /* Optional: EXCEPTION_DATA_POINTERS */


#if defined(__i386__) && !defined(__x86_64__)
#undef __EXCEPT_UNWIND_CC
#undef __EXCEPT_THROW_CC
#undef __EXCEPT_THROWN_CC
#undef __EXCEPT_NESTING_BEGIN_CC
#undef __EXCEPT_NESTING_END_CC
#define __EXCEPT_UNWIND_CC        __ATTR_FASTCALL
#define __EXCEPT_THROW_CC         __ATTR_FASTCALL
#define __EXCEPT_THROWN_CC        __ATTR_CDECL
#define __EXCEPT_NESTING_BEGIN_CC __ATTR_FASTCALL
#define __EXCEPT_NESTING_END_CC   __ATTR_FASTCALL

#define __OFFSET_EXCEPTION_DATA_CODE      __OFFSET_EXCEPTION_DATA32_CODE
#define __OFFSET_EXCEPTION_DATA_CLASS     __OFFSET_EXCEPTION_DATA32_CLASS
#define __OFFSET_EXCEPTION_DATA_SUBCLASS  __OFFSET_EXCEPTION_DATA32_SUBCLASS
#define __OFFSET_EXCEPTION_DATA_ARGS      __OFFSET_EXCEPTION_DATA32_ARGS
#define __OFFSET_EXCEPTION_DATA_POINTER   __OFFSET_EXCEPTION_DATA32_POINTER
#define __OFFSET_EXCEPTION_DATA_FAULTADDR __OFFSET_EXCEPTION_DATA32_FAULTADDR
#define __SIZEOF_EXCEPTION_DATA           __SIZEOF_EXCEPTION_DATA32
#define __SIZEOF_EXCEPT_CODE_T__          __SIZEOF_EXCEPT_CODE32_T__
#define __SIZEOF_EXCEPT_CLASS_T__         __SIZEOF_EXCEPT_CLASS32_T__
#define __SIZEOF_EXCEPT_SUBCLASS_T__      __SIZEOF_EXCEPT_SUBCLASS32_T__
#define __except_code32_t                 __except_code_t
#define __except_class32_t                __except_class_t
#define __except_subclass32_t             __except_subclass_t
#define __exception_data32                exception_data
#endif /* __i386__ && !__x86_64__ */


#ifndef EXCEPTION_DATA_POINTERS
#define EXCEPTION_DATA_POINTERS  8 /* Default value */
#endif /* !EXCEPTION_DATA_POINTERS */

#define __OFFSET_EXCEPTION_DATA32_CODE       0
#define __OFFSET_EXCEPTION_DATA32_CLASS      0
#define __OFFSET_EXCEPTION_DATA32_SUBCLASS   2
#define __OFFSET_EXCEPTION_DATA32_ARGS       4
#define __OFFSET_EXCEPTION_DATA32_POINTER(i) (((i) + 1) * 4)
#define __OFFSET_EXCEPTION_DATA32_FAULTADDR  __OFFSET_EXCEPTION_DATA32_POINTER(EXCEPTION_DATA_POINTERS)
#define __SIZEOF_EXCEPTION_DATA32            ((EXCEPTION_DATA_POINTERS + 2) * 4)

#define __SIZEOF_EXCEPT_CODE32_T__     4
#define __SIZEOF_EXCEPT_CLASS32_T__    2
#define __SIZEOF_EXCEPT_SUBCLASS32_T__ 2

#if defined(__CC__) || defined(__DEEMON__)
__SYSDECL_BEGIN

typedef __UINT32_TYPE__ __except_code32_t;
typedef __UINT16_TYPE__ __except_class32_t;
typedef __UINT16_TYPE__ __except_subclass32_t;

/*[[[deemon
import * from deemon;
local tempfp = File.Writer();
local usedStructNames = [];
(printExceptionDataStructs from .....misc.libgen.exceptinfo)(
	fp: tempfp,
	escapeTypename: x -> "__UINT32_TYPE__ /" "*{}*" "/".format({ x }),
	keyStructName:  x {
		if (x !in usedStructNames)
			usedStructNames.append(x);
		return f"__{x}32";
	},
	exceptionDataPointerType: "__UINT32_TYPE__",
);
print("#if defined(__i386__) && !defined(__x86_64__)");
local longestStructName = usedStructNames.each.length > ...;
for (local n: usedStructNames) {
	print("#define __", n, "32 ", " " * (longestStructName - #n), n);
}
print("#endif /" "* __i386__ && !__x86_64__ *" "/");
print(tempfp.string),;
]]]*/
#if defined(__i386__) && !defined(__x86_64__)
#define __exception_badalloc_data32            exception_badalloc_data
#define __exception_buffer_too_small_data32    exception_buffer_too_small_data
#define __exception_exit_process_data32        exception_exit_process_data
#define __exception_exit_thread_data32         exception_exit_thread_data
#define __exception_fserror_data32             exception_fserror_data
#define __exception_illegal_instruction_data32 exception_illegal_instruction_data
#define __exception_illegal_operation_data32   exception_illegal_operation_data
#define __exception_index_error_data32         exception_index_error_data
#define __exception_insufficient_rights_data32 exception_insufficient_rights_data
#define __exception_invalid_argument_data32    exception_invalid_argument_data
#define __exception_invalid_handle_data32      exception_invalid_handle_data
#define __exception_ioerror_data32             exception_ioerror_data
#define __exception_net_error_data32           exception_net_error_data
#define __exception_not_executable_data32      exception_not_executable_data
#define __exception_no_device_data32           exception_no_device_data
#define __exception_process_exited_data32      exception_process_exited_data
#define __exception_segfault_data32            exception_segfault_data
#define __exception_unhandled_interrupt_data32 exception_unhandled_interrupt_data
#define __exception_unknown_systemcall_data32  exception_unknown_systemcall_data
#define __exception_data_pointers32            exception_data_pointers
#endif /* __i386__ && !__x86_64__ */
/* E_BADALLOC */
struct __exception_badalloc_data32 {
	union {
#undef ba_insufficient_heap_memory
#undef ba_insufficient_virtual_memory
#undef ba_address_already_exists
#undef ba_insufficient_physical_memory
#undef ba_insufficient_swap_space
#undef ba_insufficient_handle_numbers
#undef ba_insufficient_handle_range
#undef ba_insufficient_device_numbers
#undef ba_insufficient_interrupt_vectors
#undef ba_insufficient_port_numbers

		struct {
			__UINT32_TYPE__ /*size_t*/ ihm_num_bytes; /* The number of bytes that could not be allocated */
		} ba_insufficient_heap_memory; /* E_BADALLOC_INSUFFICIENT_HEAP_MEMORY */

		struct {
			__UINT32_TYPE__ /*size_t*/ ivm_num_bytes; /* The number of bytes that could not be mapped */
		} ba_insufficient_virtual_memory; /* E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY */

		struct {
			__UINT32_TYPE__ /*void **/ aae_minaddr;       /* Lowest address that was requested */
			__UINT32_TYPE__ /*void **/ aae_maxaddr;       /* Greatest address that was requested */
			__UINT32_TYPE__ /*void **/ aae_inuse_minaddr; /* Lowest address already in use */
			__UINT32_TYPE__ /*void **/ aae_inuse_maxaddr; /* Greatest address already in use */
		} ba_address_already_exists; /* E_BADALLOC_ADDRESS_ALREADY_EXISTS */

		struct {
			__UINT32_TYPE__ /*size_t*/ ipm_num_pages; /* The number of bytes that could not be allocated */
		} ba_insufficient_physical_memory; /* E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY */

		struct {
			__UINT32_TYPE__ /*size_t*/ iss_num_pages; /* The number of bytes that could not be allocated */
		} ba_insufficient_swap_space; /* E_BADALLOC_INSUFFICIENT_SWAP_SPACE */

		struct {
			__UINT32_TYPE__ /*unsigned int*/ ihn_num_handles; /* The number of handles that were attempted to be allocated (usually 1) */
			__UINT32_TYPE__ /*unsigned int*/ ihn_cur_handles; /* The number of handles currently allocated */
			__UINT32_TYPE__ /*unsigned int*/ ihn_max_handles; /* The max number of handles that may be allocated by the caller */
		} ba_insufficient_handle_numbers; /* E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS */

		struct {
			__UINT32_TYPE__ /*unsigned int*/ ihr_req_handle; /* The requested handle number, past which no more unused handles exist. */
			__UINT32_TYPE__ /*unsigned int*/ ihr_cur_max;    /* The max handle id that is currently in use */
			__UINT32_TYPE__ /*unsigned int*/ ihr_cur_limit;  /* The set handle id which may not be exceeded */
		} ba_insufficient_handle_range; /* E_BADALLOC_INSUFFICIENT_HANDLE_RANGE */

		struct {
			__UINT32_TYPE__ /*unsigned int*/ idn_dev_kind; /* The kind of device number lacking (One of `E_NO_DEVICE_KIND_*') */
		} ba_insufficient_device_numbers; /* E_BADALLOC_INSUFFICIENT_DEVICE_NUMBERS */

		struct {
			__UINT32_TYPE__ /*uintptr_t*/ iiv_vector; /* The given vector (if that specific vector is already in use),
			                                           * or (uintptr_t)-1 when all vectors are already in use. */
		} ba_insufficient_interrupt_vectors; /* E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS */

		struct {
			__UINT32_TYPE__ /*syscall_ulong_t*/ ipn_address_family; /* The socket's address family (one of `AF_*') */
			__UINT32_TYPE__ /*syscall_ulong_t*/ ipn_socket_type;    /* The socket's type (one of `SOCK_*') */
			__UINT32_TYPE__ /*syscall_ulong_t*/ ipn_protocol;       /* The socket's protocol (dependent on `address_family' and `socket_type') */
		} ba_insufficient_port_numbers; /* E_BADALLOC_INSUFFICIENT_PORT_NUMBERS */

	}
#ifndef __COMPILER_HAVE_TRANSPARENT_UNION
	_ba_classes
#define ba_insufficient_heap_memory       _ba_classes.ba_insufficient_heap_memory
#define ba_insufficient_virtual_memory    _ba_classes.ba_insufficient_virtual_memory
#define ba_address_already_exists         _ba_classes.ba_address_already_exists
#define ba_insufficient_physical_memory   _ba_classes.ba_insufficient_physical_memory
#define ba_insufficient_swap_space        _ba_classes.ba_insufficient_swap_space
#define ba_insufficient_handle_numbers    _ba_classes.ba_insufficient_handle_numbers
#define ba_insufficient_handle_range      _ba_classes.ba_insufficient_handle_range
#define ba_insufficient_device_numbers    _ba_classes.ba_insufficient_device_numbers
#define ba_insufficient_interrupt_vectors _ba_classes.ba_insufficient_interrupt_vectors
#define ba_insufficient_port_numbers      _ba_classes.ba_insufficient_port_numbers
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
	;
};

/* E_BUFFER_TOO_SMALL */
struct __exception_buffer_too_small_data32 {
	__UINT32_TYPE__ /*size_t*/ bts_req_size;   /* The required buffer size */
	__UINT32_TYPE__ /*size_t*/ bts_given_size; /* The given buffer size */
};

/* E_EXIT_PROCESS */
struct __exception_exit_process_data32 {
	__UINT32_TYPE__ /*uintptr_t*/ ep_exit_code; /* The process exit status */
};

/* E_EXIT_THREAD */
struct __exception_exit_thread_data32 {
	__UINT32_TYPE__ /*uintptr_t*/ et_exit_code; /* The thread exit status */
};

/* E_FSERROR */
struct __exception_fserror_data32 {
	union {
#undef f_deleted
#undef f_path_not_found
#undef f_not_a_directory
#undef f_is_a_directory
#undef f_is_a_symbolic_link
#undef f_unsupported_operation

		struct {
			__UINT32_TYPE__ /*unsigned int*/ d_reason; /* The reason/context in which the file was deleted (One of `E_FILESYSTEM_DELETED_*') */
		} f_deleted; /* E_FSERROR_DELETED */

		struct {
			__UINT32_TYPE__ /*unsigned int*/ pnf_reason; /* The reason/context why the path wasn't found (One of `E_FILESYSTEM_PATH_NOT_FOUND_*') */
		} f_path_not_found; /* E_FSERROR_PATH_NOT_FOUND */

		struct {
			__UINT32_TYPE__ /*uintptr_t*/ nad_action_context; /* The context in which a filesystem component was required to be
			                                                   * a directory, but wasn't (One of `E_FILESYSTEM_NOT_A_DIRECTORY_*') */
		} f_not_a_directory; /* E_FSERROR_NOT_A_DIRECTORY */

		struct {
			__UINT32_TYPE__ /*uintptr_t*/ iad_action_context; /* The context in which a filesystem component was required to not be
			                                                   * a directory, but was one (One of `E_FILESYSTEM_IS_A_DIRECTORY_*') */
		} f_is_a_directory; /* E_FSERROR_IS_A_DIRECTORY */

		struct {
			__UINT32_TYPE__ /*uintptr_t*/ iasl_action_context; /* The context in which a filesystem component was required to not be
			                                                    * a symlink, but was one (One of `E_FILESYSTEM_IS_A_SYMBOLIC_LINK_*') */
		} f_is_a_symbolic_link; /* E_FSERROR_IS_A_SYMBOLIC_LINK */

		struct {
			__UINT32_TYPE__ /*uintptr_t*/ uo_operation_id; /* The unsupported operation (One of `E_FILESYSTEM_OPERATION_*') */
		} f_unsupported_operation; /* E_FSERROR_UNSUPPORTED_OPERATION */

	}
#ifndef __COMPILER_HAVE_TRANSPARENT_UNION
	_f_classes
#define f_deleted               _f_classes.f_deleted
#define f_path_not_found        _f_classes.f_path_not_found
#define f_not_a_directory       _f_classes.f_not_a_directory
#define f_is_a_directory        _f_classes.f_is_a_directory
#define f_is_a_symbolic_link    _f_classes.f_is_a_symbolic_link
#define f_unsupported_operation _f_classes.f_unsupported_operation
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
	;
};

/* E_ILLEGAL_INSTRUCTION */
#if !defined(__i386__) && !defined(__x86_64__)
struct __exception_illegal_instruction_data32 {
	__UINT32_TYPE__ /*uintptr_t*/ ii_opcode; /* The opcode that caused the exception */
	union {
#undef ii_bad_operand
#undef ii_register

		struct {
			__UINT32_TYPE__ /*uintptr_t*/ bo_what;   /* For what reason was the operand invalid (One of `E_ILLEGAL_INSTRUCTION_BAD_OPERAND_*') */
			__UINT32_TYPE__ /*uintptr_t*/ bo_regno;  /* The accessed register index (from `<asm/register.h>') */
			__UINT32_TYPE__ /*uintptr_t*/ bo_regval; /* The associated register value */
		} ii_bad_operand; /* E_ILLEGAL_INSTRUCTION_BAD_OPERAND */

		struct {
			__UINT32_TYPE__ /*uintptr_t*/ r_how;    /* How was the register accessed (One of `E_ILLEGAL_INSTRUCTION_REGISTER_*') */
			__UINT32_TYPE__ /*uintptr_t*/ r_regno;  /* The accessed register index (from `<asm/register.h>') */
			__UINT32_TYPE__ /*uintptr_t*/ r_regval; /* The associated register value (or 0 for read operations) */
		} ii_register; /* E_ILLEGAL_INSTRUCTION_REGISTER */

	}
#ifndef __COMPILER_HAVE_TRANSPARENT_UNION
	_ii_classes
#define ii_bad_operand _ii_classes.ii_bad_operand
#define ii_register    _ii_classes.ii_register
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
	;
};
#endif /* !__i386__ && !__x86_64__ */

/* E_ILLEGAL_INSTRUCTION */
#if defined(__i386__) || defined(__x86_64__)
struct __exception_illegal_instruction_data32 {
	__UINT32_TYPE__ /*uintptr_t*/ ii_opcode;   /* The opcode that caused the exception
	                                            * NOTE: This field should be decoded using `E_ILLEGAL_INSTRUCTION_X86_OPCODE_*' */
	__UINT32_TYPE__ /*uintptr_t*/ ii_op_flags; /* Opcode flags (set of `EMU86_F_*') */
	union {
#undef ii_bad_operand
#undef ii_x86_interrupt
#undef ii_register

		struct {
			__UINT32_TYPE__ /*uintptr_t*/ bo_what;    /* For what reason was the operand invalid (One of `E_ILLEGAL_INSTRUCTION_BAD_OPERAND_*') */
			__UINT32_TYPE__ /*uintptr_t*/ bo_regno;   /* The accessed register index (from `<asm/register.h>')
			                                           * NOTE: When set to `X86_REGISTER_MSR', then the next 3
			                                           *       pointers are index(%ecx), loval(%eax), hival(%edx) */
			__UINT32_TYPE__ /*uintptr_t*/ bo_offset;  /* An offset applied to the register (set in case of an illegal lcall/ljmp; 0 otherwise)
			                                           * In case an MSR register was accessed, this is the MSR index */
			__UINT32_TYPE__ /*uintptr_t*/ bo_regval;  /* The associated register value */
			__UINT32_TYPE__ /*uintptr_t*/ bo_regval2; /* The associated register value (high 32 bits in case of an MSR write) */
		} ii_bad_operand; /* E_ILLEGAL_INSTRUCTION_BAD_OPERAND */

		struct {
			__UINT32_TYPE__ /*uintptr_t*/ xi_intno;  /* The system interrupt that occurred */
			__UINT32_TYPE__ /*uintptr_t*/ xi_ecode;  /* The error code associated with that interrupt */
			__UINT32_TYPE__ /*uintptr_t*/ xi_segval; /* The segment value of the segment in question */
		} ii_x86_interrupt; /* E_ILLEGAL_INSTRUCTION_X86_INTERRUPT */

		struct {
			__UINT32_TYPE__ /*uintptr_t*/ r_how;     /* How was the register accessed (One of `E_ILLEGAL_INSTRUCTION_REGISTER_*') */
			__UINT32_TYPE__ /*uintptr_t*/ r_regno;   /* The accessed register index (from `<asm/register.h>')
			                                          * NOTE: When set to `X86_REGISTER_MSR', then the next 3
			                                          *       pointers are index(%ecx), loval(%eax), hival(%edx) */
			__UINT32_TYPE__ /*uintptr_t*/ r_offset;  /* An offset applied to the register (set in case of an illegal lcall/ljmp; 0 otherwise)
			                                          * In case an MSR register was accessed, this is the MSR index */
			__UINT32_TYPE__ /*uintptr_t*/ r_regval;  /* The associated register value (or 0 for read operations) */
			__UINT32_TYPE__ /*uintptr_t*/ r_regval2; /* The associated register value (or 0 for read operations) (high 32 bits in case of an MSR write) */
		} ii_register; /* E_ILLEGAL_INSTRUCTION_REGISTER */

	}
#ifndef __COMPILER_HAVE_TRANSPARENT_UNION
	_ii_classes
#define ii_bad_operand   _ii_classes.ii_bad_operand
#define ii_x86_interrupt _ii_classes.ii_x86_interrupt
#define ii_register      _ii_classes.ii_register
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
	;
};
#endif /* __i386__ || __x86_64__ */

/* E_ILLEGAL_OPERATION */
struct __exception_illegal_operation_data32 {
	__UINT32_TYPE__ /*syscall_ulong_t*/ io_reason; /* One of `E_ILLEGAL_OPERATION_CONTEXT_*' */
};

/* E_INDEX_ERROR */
struct __exception_index_error_data32 {
	union {
#undef ie_out_of_bounds

		struct {
			__UINT32_TYPE__ /*intptr_t*/ oob_index; /* The addressed index */
			__UINT32_TYPE__ /*intptr_t*/ oob_min;   /* The low bound of valid indices */
			__UINT32_TYPE__ /*intptr_t*/ oob_max;   /* The high bound of valid indices */
		} ie_out_of_bounds; /* E_INDEX_ERROR_OUT_OF_BOUNDS */

	}
#ifndef __COMPILER_HAVE_TRANSPARENT_UNION
	_ie_classes
#define ie_out_of_bounds _ie_classes.ie_out_of_bounds
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
	;
};

/* E_INSUFFICIENT_RIGHTS */
struct __exception_insufficient_rights_data32 {
	__UINT32_TYPE__ /*intptr_t*/ ir_capability; /* The missing capability (one of `CAP_*' from `<kos/capability.h>') */
};

/* E_INVALID_ARGUMENT */
struct __exception_invalid_argument_data32 {
	__UINT32_TYPE__ /*syscall_ulong_t*/ ia_context; /* Argument context (One of `E_INVALID_ARGUMENT_CONTEXT_*') */
	union {
#undef ia_unknown_flag
#undef ia_reserved_flag
#undef ia_bad_flag_combination
#undef ia_bad_flag_mask
#undef ia_bad_alignment
#undef ia_bad_value
#undef ia_unknown_command
#undef ia_socket_opt
#undef ia_unexpected_command

		struct {
			__UINT32_TYPE__ /*uintptr_t*/ uf_value;  /* The value that was given */
			__UINT32_TYPE__ /*uintptr_t*/ uf_mask;   /* The mask of illegal & fixed bits */
			__UINT32_TYPE__ /*uintptr_t*/ uf_result; /* The mask of fixed bits */
		} ia_unknown_flag; /* E_INVALID_ARGUMENT_UNKNOWN_FLAG */

		struct {
			__UINT32_TYPE__ /*uintptr_t*/ rf_value;  /* The value that was given */
			__UINT32_TYPE__ /*uintptr_t*/ rf_mask;   /* The mask of illegal & fixed bits */
			__UINT32_TYPE__ /*uintptr_t*/ rf_result; /* The mask of fixed bits */
		} ia_reserved_flag; /* E_INVALID_ARGUMENT_RESERVED_FLAG */

		struct {
			__UINT32_TYPE__ /*uintptr_t*/ bfc_value;  /* The value that was given */
			__UINT32_TYPE__ /*uintptr_t*/ bfc_mask;   /* The mask of relevant bits */
			__UINT32_TYPE__ /*uintptr_t*/ bfc_result; /* The invalid resulting value */
		} ia_bad_flag_combination; /* E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION */

		struct {
			__UINT32_TYPE__ /*uintptr_t*/ bfm_value; /* The value that was given */
			__UINT32_TYPE__ /*uintptr_t*/ bfm_mask;  /* The mask of relevant bits */
		} ia_bad_flag_mask; /* E_INVALID_ARGUMENT_BAD_FLAG_MASK */

		struct {
			__UINT32_TYPE__ /*uintptr_t*/ ba_value;                 /* The value that was given */
			__UINT32_TYPE__ /*uintptr_t*/ ba_mask;                  /* The mask in which the bits of `value' must match `required_masked_value' */
			__UINT32_TYPE__ /*uintptr_t*/ ba_required_masked_value; /* The required result of masking `value' */
		} ia_bad_alignment; /* E_INVALID_ARGUMENT_BAD_ALIGNMENT */

		struct {
			__UINT32_TYPE__ /*uintptr_t*/ bv_value; /* The value that was given */
		} ia_bad_value; /* E_INVALID_ARGUMENT_BAD_VALUE */

		struct {
			__UINT32_TYPE__ /*uintptr_t*/ uc_command; /* The command that was given */
		} ia_unknown_command; /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND */

		struct {
			__UINT32_TYPE__ /*uintptr_t*/ so_level;          /* The level that was given to `getoptname()' or `setoptname()' */
			__UINT32_TYPE__ /*uintptr_t*/ so_optname;        /* The optname that was given to `getoptname()' or `setoptname()' */
			__UINT32_TYPE__ /*uintptr_t*/ so_address_family; /* The socket's address family (one of `AF_*') */
			__UINT32_TYPE__ /*uintptr_t*/ so_socket_type;    /* The socket's type (one of `SOCK_*') */
			__UINT32_TYPE__ /*uintptr_t*/ so_protocol;       /* The socket's protocol (dependent on `address_family' and `socket_type') */
		} ia_socket_opt; /* E_INVALID_ARGUMENT_SOCKET_OPT */

		struct {
			__UINT32_TYPE__ /*uintptr_t*/ uc_command;          /* The command that was given */
			__UINT32_TYPE__ /*uintptr_t*/ uc_expected_command; /* The command that had been expected */
		} ia_unexpected_command; /* E_INVALID_ARGUMENT_UNEXPECTED_COMMAND */

	}
#ifndef __COMPILER_HAVE_TRANSPARENT_UNION
	_ia_classes
#define ia_unknown_flag         _ia_classes.ia_unknown_flag
#define ia_reserved_flag        _ia_classes.ia_reserved_flag
#define ia_bad_flag_combination _ia_classes.ia_bad_flag_combination
#define ia_bad_flag_mask        _ia_classes.ia_bad_flag_mask
#define ia_bad_alignment        _ia_classes.ia_bad_alignment
#define ia_bad_value            _ia_classes.ia_bad_value
#define ia_unknown_command      _ia_classes.ia_unknown_command
#define ia_socket_opt           _ia_classes.ia_socket_opt
#define ia_unexpected_command   _ia_classes.ia_unexpected_command
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
	;
};

/* E_INVALID_HANDLE */
struct __exception_invalid_handle_data32 {
	__UINT32_TYPE__ /*fd_t*/ ih_fd; /* The FD number that was accessed */
	union {
#undef ih_file
#undef ih_filetype
#undef ih_operation
#undef ih_net_operation

		struct {
			__UINT32_TYPE__ /*syscall_ulong_t*/ f_reason;   /* One of `E_INVALID_HANDLE_FILE_*' */
			__UINT32_TYPE__ /*unsigned int*/    f_fd_max;   /* 1+ the max FD number that is currently in use */
			__UINT32_TYPE__ /*unsigned int*/    f_fd_limit; /* The max allowed FD number that may be assigned */
		} ih_file; /* E_INVALID_HANDLE_FILE */

		struct {
			__UINT32_TYPE__ /*syscall_ulong_t*/ f_needed_handle_type; /* The type of handle that was needed (One of `HANDLE_TYPE_*' from <kos/kernel/handle.h>) */
			__UINT32_TYPE__ /*syscall_ulong_t*/ f_actual_handle_type; /* The type of handle that was found (One of `HANDLE_TYPE_*' from <kos/kernel/handle.h>) */
			__UINT32_TYPE__ /*syscall_ulong_t*/ f_needed_handle_kind; /* The type-kind of handle that was needed (One of `HANDLE_TYPEKIND_*' from <kos/kernel/handle.h>) */
			__UINT32_TYPE__ /*syscall_ulong_t*/ f_actual_handle_kind; /* The type-kind of handle that was found (One of `HANDLE_TYPEKIND_*' from <kos/kernel/handle.h>) */
		} ih_filetype; /* E_INVALID_HANDLE_FILETYPE */

		struct {
			__UINT32_TYPE__ /*unsigned int*/ o_op;          /* One of `E_INVALID_HANDLE_OPERATION_*' */
			__UINT32_TYPE__ /*iomode_t*/     o_handle_mode; /* The access permissions of the handle */
		} ih_operation; /* E_INVALID_HANDLE_OPERATION */

		struct {
			__UINT32_TYPE__ /*syscall_ulong_t*/ no_operation_id;   /* The attempted network operation (One of `E_NET_OPERATION_*') */
			__UINT32_TYPE__ /*syscall_ulong_t*/ no_address_family; /* The socket's address family (one of `AF_*') */
			__UINT32_TYPE__ /*syscall_ulong_t*/ no_socket_type;    /* The socket's type (one of `SOCK_*') */
			__UINT32_TYPE__ /*syscall_ulong_t*/ no_protocol;       /* The socket's protocol (dependent on `address_family' and `socket_type') */
		} ih_net_operation; /* E_INVALID_HANDLE_NET_OPERATION */

	}
#ifndef __COMPILER_HAVE_TRANSPARENT_UNION
	_ih_classes
#define ih_file          _ih_classes.ih_file
#define ih_filetype      _ih_classes.ih_filetype
#define ih_operation     _ih_classes.ih_operation
#define ih_net_operation _ih_classes.ih_net_operation
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
	;
};

/* E_IOERROR */
struct __exception_ioerror_data32 {
	__UINT32_TYPE__ /*uintptr_t*/ i_subsystem; /* The miss-behaving sub-system (One of `E_IOERROR_SUBSYSTEM_*') */
	__UINT32_TYPE__ /*uintptr_t*/ i_reason;    /* A more precise description of the error (One of `E_IOERROR_REASON_*') */
};

/* E_NET_ERROR */
struct __exception_net_error_data32 {
	union {
#undef ne_address_in_use
#undef ne_message_too_long

		struct {
			__UINT32_TYPE__ /*unsigned int*/ iu_context; /* The context under which the address is already in use (one of `E_NET_ADDRESS_IN_USE_CONTEXT_*') */
		} ne_address_in_use; /* E_NET_ADDRESS_IN_USE */

		struct {
			__UINT32_TYPE__ /*size_t*/ tl_req_length; /* The requested message length */
			__UINT32_TYPE__ /*size_t*/ tl_max_length; /* The max possible message length */
		} ne_message_too_long; /* E_NET_MESSAGE_TOO_LONG */

	}
#ifndef __COMPILER_HAVE_TRANSPARENT_UNION
	_ne_classes
#define ne_address_in_use   _ne_classes.ne_address_in_use
#define ne_message_too_long _ne_classes.ne_message_too_long
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
	;
};

/* E_NOT_EXECUTABLE */
struct __exception_not_executable_data32 {
	union {
#undef ne_faulty

		struct {
			__UINT32_TYPE__ /*uintptr_t*/ f_format; /* The binary format (One of `E_NOT_EXECUTABLE_FAULTY_FORMAT_*') */
			__UINT32_TYPE__ /*uintptr_t*/ f_reason; /* The format-specific reason why the load failed (One of `E_NOT_EXECUTABLE_FAULTY_REASON_*_*') */
		} ne_faulty; /* E_NOT_EXECUTABLE_FAULTY */

	}
#ifndef __COMPILER_HAVE_TRANSPARENT_UNION
	_ne_classes
#define ne_faulty _ne_classes.ne_faulty
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
	;
};

/* E_NO_DEVICE */
struct __exception_no_device_data32 {
	__UINT32_TYPE__ /*uintptr_t*/ nd_kind;  /* The kind of device (One of `E_NO_DEVICE_KIND_*') */
	__UINT32_TYPE__ /*dev_t*/     nd_devno; /* The number for the named device */
};

/* E_PROCESS_EXITED */
struct __exception_process_exited_data32 {
	__UINT32_TYPE__ /*pid_t*/ pe_pid; /* The pid of the exited process */
};

/* E_SEGFAULT */
struct __exception_segfault_data32 {
	__UINT32_TYPE__ /*void **/    s_addr;    /* The virtual memory address where the fault happened */
	__UINT32_TYPE__ /*uintptr_t*/ s_context; /* Fault context (Set of `E_SEGFAULT_CONTEXT_*') */
	union {
#undef s_notatomic
#undef s_unaligned

		struct {
			__UINT32_TYPE__ /*size_t*/    n_size;      /* The number of consecutive bytes accessed */
			__UINT32_TYPE__ /*uintptr_t*/ n_oldval_lo; /* Low data word of the expected old value */
			__UINT32_TYPE__ /*uintptr_t*/ n_oldval_hi; /* High data word of the expected old value */
			__UINT32_TYPE__ /*uintptr_t*/ n_newval_lo; /* Low data word of the intended new value */
			__UINT32_TYPE__ /*uintptr_t*/ n_newval_hi; /* High data word of the intended new value */
		} s_notatomic; /* E_SEGFAULT_NOTATOMIC */

		struct {
			__UINT32_TYPE__ /*size_t*/ u_required_alignemnt; /* The required alignment of `addr' (power-of-2) */
		} s_unaligned; /* E_SEGFAULT_UNALIGNED */

	}
#ifndef __COMPILER_HAVE_TRANSPARENT_UNION
	_s_classes
#define s_notatomic _s_classes.s_notatomic
#define s_unaligned _s_classes.s_unaligned
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
	;
};

/* E_UNHANDLED_INTERRUPT */
struct __exception_unhandled_interrupt_data32 {
	__UINT32_TYPE__ /*uintptr_t*/ ui_opcode;
	__UINT32_TYPE__ /*uintptr_t*/ ui_intno;
	__UINT32_TYPE__ /*uintptr_t*/ ui_ecode;
};

/* E_UNKNOWN_SYSTEMCALL */
struct __exception_unknown_systemcall_data32 {
	__UINT32_TYPE__ /*syscall_ulong_t*/ us_flags; /* System call invocation flags (Set of `RPC_SYSCALL_INFO_*') */
	__UINT32_TYPE__ /*syscall_ulong_t*/ us_sysno;
	__UINT32_TYPE__ /*syscall_ulong_t*/ us_arg0;
	__UINT32_TYPE__ /*syscall_ulong_t*/ us_arg1;
	__UINT32_TYPE__ /*syscall_ulong_t*/ us_arg2;
	__UINT32_TYPE__ /*syscall_ulong_t*/ us_arg3;
	__UINT32_TYPE__ /*syscall_ulong_t*/ us_arg4;
	__UINT32_TYPE__ /*syscall_ulong_t*/ us_arg5;
};

union __exception_data_pointers32 {
	__UINT32_TYPE__                               e_pointers[EXCEPTION_DATA_POINTERS];
	struct __exception_badalloc_data32            e_badalloc;            /* E_BADALLOC */
	struct __exception_buffer_too_small_data32    e_buffer_too_small;    /* E_BUFFER_TOO_SMALL */
	struct __exception_exit_process_data32        e_exit_process;        /* E_EXIT_PROCESS */
	struct __exception_exit_thread_data32         e_exit_thread;         /* E_EXIT_THREAD */
	struct __exception_fserror_data32             e_fserror;             /* E_FSERROR */
#if !defined(__i386__) && !defined(__x86_64__)
	struct __exception_illegal_instruction_data32 e_illegal_instruction; /* E_ILLEGAL_INSTRUCTION */
#endif /* !__i386__ && !__x86_64__ */
#if defined(__i386__) || defined(__x86_64__)
	struct __exception_illegal_instruction_data32 e_illegal_instruction; /* E_ILLEGAL_INSTRUCTION */
#endif /* __i386__ || __x86_64__ */
	struct __exception_illegal_operation_data32   e_illegal_operation;   /* E_ILLEGAL_OPERATION */
	struct __exception_index_error_data32         e_index_error;         /* E_INDEX_ERROR */
	struct __exception_insufficient_rights_data32 e_insufficient_rights; /* E_INSUFFICIENT_RIGHTS */
	struct __exception_invalid_argument_data32    e_invalid_argument;    /* E_INVALID_ARGUMENT */
	struct __exception_invalid_handle_data32      e_invalid_handle;      /* E_INVALID_HANDLE */
	struct __exception_ioerror_data32             e_ioerror;             /* E_IOERROR */
	struct __exception_net_error_data32           e_net_error;           /* E_NET_ERROR */
	struct __exception_not_executable_data32      e_not_executable;      /* E_NOT_EXECUTABLE */
	struct __exception_no_device_data32           e_no_device;           /* E_NO_DEVICE */
	struct __exception_process_exited_data32      e_process_exited;      /* E_PROCESS_EXITED */
	struct __exception_segfault_data32            e_segfault;            /* E_SEGFAULT */
	struct __exception_unhandled_interrupt_data32 e_unhandled_interrupt; /* E_UNHANDLED_INTERRUPT */
	struct __exception_unknown_systemcall_data32  e_unknown_systemcall;  /* E_UNKNOWN_SYSTEMCALL */
};
/*[[[end]]]*/


#undef e_code
#undef e_class
#undef e_subclass

/* Exception information. */
struct __exception_data32 /*[NAME(exception_data32)][PREFIX(e_)]*/ {
	union {
		__except_code32_t          e_code;   /* Exception code. */
		struct {
			__except_class32_t     e_class;    /* Current exception class. */
			__except_subclass32_t  e_subclass; /* Current exception sub-class. */
		}
#ifndef __COMPILER_HAVE_TRANSPARENT_STRUCT
		_ed_class_subclass
#endif /* !__COMPILER_HAVE_TRANSPARENT_STRUCT */
		;
	}
#ifndef __COMPILER_HAVE_TRANSPARENT_UNION
	_ed_code
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
	;
	/* Exception-specific arguments */
	union __exception_data_pointers32 e_args;
	/* The address of the instruction that caused the fault.
	 * Unlike  the  program counter  stored within  the `except_register_state_t'
	 * structure which can  be accessed  through `except_register_state()',  this
	 * one  _may_ point _before_  the instruction that  caused the error, however
	 * it may also point after  the instruction. Which of  the two it is  depends
	 * on  how the  specific exception was  generated, though it  should be noted
	 * that in the case of errors thrown by `THROW()', this address will _always_
	 * point  _after_ the instruction  (meaning it's always  equal to the program
	 * counter stored in `except_register_state()')
	 *  - e_faultaddr: Either equal to `GETPC(except_register_state())', or points
	 *                 to  the  instruction  that  is   `except_register_state()'.
	 *  - GETPC(except_register_state()):
	 *                 Always points to the instruction that would have been
	 *                 executed next if  the exception  hadn't been  thrown. */
	__HYBRID_PTR32(void const) e_faultaddr;
};

#if !defined(__COMPILER_HAVE_TRANSPARENT_UNION) && !defined(__COMPILER_HAVE_TRANSPARENT_STRUCT)
#define e_code      _ed_code.e_code
#define e_class     _ed_code._ed_class_subclass.e_class
#define e_subclass  _ed_code._ed_class_subclass.e_subclass
#elif !defined(__COMPILER_HAVE_TRANSPARENT_UNION)
#define e_code      _ed_code.e_code
#define e_class     _ed_code.e_class
#define e_subclass  _ed_code.e_subclass
#elif !defined(__COMPILER_HAVE_TRANSPARENT_STRUCT)
#define e_class     _ed_class_subclass.e_class
#define e_subclass  _ed_class_subclass.e_subclass
#endif

__SYSDECL_END
#endif /* !__CC__ */

#endif /* !_I386_KOS_KOS_BITS_EXCEPTION_DATA32_H */
