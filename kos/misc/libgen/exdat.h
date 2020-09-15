E_INVALID_HANDLE:[msg("Bad file descriptor")]
struct exception_invalid_handle_data {
	fd_t ih_fd; /* The FD number that was accessed*/
	union {

		struct {
			syscall_ulong_t f_reason;   /* One of `E_INVALID_HANDLE_FILE_*'*/
			unsigned int    f_fd_max;   /* 1+ the max FD number that is currently in use*/
			unsigned int    f_fd_limit; /* The max allowed FD number that may be assigned*/
		} ih_file; /* E_INVALID_HANDLE_FILE */

		struct {
			syscall_ulong_t f_needed_handle_type; /* The type of handle that was needed (One of `HANDLE_TYPE_*' from <kos/kernel/handle.h>)*/
			syscall_ulong_t f_actual_handle_type; /* The type of handle that was found (One of `HANDLE_TYPE_*' from <kos/kernel/handle.h>)*/
			syscall_ulong_t f_needed_handle_kind; /* The type-kind of handle that was needed (One of `HANDLE_TYPEKIND_*' from <kos/kernel/handle.h>)*/
			syscall_ulong_t f_actual_handle_kind; /* The type-kind of handle that was found (One of `HANDLE_TYPEKIND_*' from <kos/kernel/handle.h>)*/
		} ih_filetype; /* E_INVALID_HANDLE_FILETYPE */

		struct {
			unsigned int o_op;          /* One of `E_INVALID_HANDLE_OPERATION_*'*/
			iomode_t     o_handle_mode; /* The access permissions of the handle*/
		} ih_operation; /* E_INVALID_HANDLE_OPERATION */

		struct {
			syscall_ulong_t no_operation_id;   /* The attempted network operation (One of `E_NET_OPERATION_*')*/
			syscall_ulong_t no_address_family; /* The socket's address family (one of `AF_*')*/
			syscall_ulong_t no_socket_type;    /* The socket's type (one of `SOCK_*')*/
			syscall_ulong_t no_protocol;       /* The socket's protocol (dependent on `address_family' and `socket_type')*/
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
E_PROCESS_EXITED:[msg("Process no longer exists")]
struct exception_process_exited_data {
	pid_t pe_pid; /* The pid of the exited process*/
};
E_INVALID_ARGUMENT:[msg("Invalid argument")]
struct exception_invalid_argument_data {
	syscall_ulong_t ia_context; /* Argument context (One of `E_INVALID_ARGUMENT_CONTEXT_*')*/
	union {

		struct {
			uintptr_t uf_value;  /* The value that was given*/
			uintptr_t uf_mask;   /* The mask of illegal & fixed bits*/
			uintptr_t uf_result; /* The mask of fixed bits*/
		} ia_unknown_flag; /* E_INVALID_ARGUMENT_UNKNOWN_FLAG */

		struct {
			uintptr_t rf_value;  /* The value that was given*/
			uintptr_t rf_mask;   /* The mask of illegal & fixed bits*/
			uintptr_t rf_result; /* The mask of fixed bits*/
		} ia_reserved_flag; /* E_INVALID_ARGUMENT_RESERVED_FLAG */

		struct {
			uintptr_t bfc_value;  /* The value that was given*/
			uintptr_t bfc_mask;   /* The mask of relevant bits*/
			uintptr_t bfc_result; /* The invalid resulting value*/
		} ia_bad_flag_combination; /* E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION */

		struct {
			uintptr_t bfm_value; /* The value that was given*/
			uintptr_t bfm_mask;  /* The mask of relevant bits*/
		} ia_bad_flag_mask; /* E_INVALID_ARGUMENT_BAD_FLAG_MASK */

		struct {
			uintptr_t ba_value;                 /* The value that was given*/
			uintptr_t ba_mask;                  /* The mask in which the bits of `value' must match `required_masked_value'*/
			uintptr_t ba_required_masked_value; /* The required result of masking `value'*/
		} ia_bad_alignment; /* E_INVALID_ARGUMENT_BAD_ALIGNMENT */

		struct {
			uintptr_t bv_value; /* The value that was given*/
		} ia_bad_value; /* E_INVALID_ARGUMENT_BAD_VALUE */

		struct {
			uintptr_t uc_command; /* The command that was given*/
		} ia_unknown_command; /* E_INVALID_ARGUMENT_UNKNOWN_COMMAND */

		struct {
			uintptr_t so_level;          /* The level that was given to `getoptname()' or `setoptname()'*/
			uintptr_t so_optname;        /* The optname that was given to `getoptname()' or `setoptname()'*/
			uintptr_t so_address_family; /* The socket's address family (one of `AF_*')*/
			uintptr_t so_socket_type;    /* The socket's type (one of `SOCK_*')*/
			uintptr_t so_protocol;       /* The socket's protocol (dependent on `address_family' and `socket_type')*/
		} ia_socket_opt; /* E_INVALID_ARGUMENT_SOCKET_OPT */

		struct {
			uintptr_t uc_command;          /* The command that was given*/
			uintptr_t uc_expected_command; /* The command that had been expected*/
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
E_BADALLOC:[msg("Failed to allocate sufficient resources")]
struct exception_badalloc_data {
	union {

		struct {
			size_t ihm_num_bytes; /* The number of bytes that could not be allocated*/
		} ba_insufficient_heap_memory; /* E_BADALLOC_INSUFFICIENT_HEAP_MEMORY */

		struct {
			size_t ivm_num_pages; /* The number of bytes that could not be mapped*/
		} ba_insufficient_virtual_memory; /* E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY */

		struct {
			size_t ipm_num_pages; /* The number of bytes that could not be allocated*/
		} ba_insufficient_physical_memory; /* E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY */

		struct {
			size_t iss_num_pages; /* The number of bytes that could not be allocated*/
		} ba_insufficient_swap_space; /* E_BADALLOC_INSUFFICIENT_SWAP_SPACE */

		struct {
			unsigned int ihn_num_handles; /* The number of handles that were attempted to be allocated (usually 1)*/
			unsigned int ihn_cur_handles; /* The number of handles currently allocated*/
			unsigned int ihn_max_handles; /* The max number of handles that may be allocated by the caller*/
		} ba_insufficient_handle_numbers; /* E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS */

		struct {
			unsigned int ihr_req_handle; /* The requested handle number, past which no more unused handles exist.*/
			unsigned int ihr_cur_max;    /* The max handle id that is currently in use*/
			unsigned int ihr_cur_limit;  /* The set handle id which may not be exceeded*/
		} ba_insufficient_handle_range; /* E_BADALLOC_INSUFFICIENT_HANDLE_RANGE */

		struct {
			unsigned int idn_dev_kind; /* The kind of device number lacking (One of `E_NO_DEVICE_KIND_*')*/
		} ba_insufficient_device_numbers; /* E_BADALLOC_INSUFFICIENT_DEVICE_NUMBERS */

		struct {
			uintptr_t iiv_vector; /* The given vector (if that specific vector is already in use),
			                       * or (uintptr_t)-1 when all vectors are already in use.*/
		} ba_insufficient_interrupt_vectors; /* E_BADALLOC_INSUFFICIENT_INTERRUPT_VECTORS */

		struct {
			syscall_ulong_t ipn_address_family; /* The socket's address family (one of `AF_*')*/
			syscall_ulong_t ipn_socket_type;    /* The socket's type (one of `SOCK_*')*/
			syscall_ulong_t ipn_protocol;       /* The socket's protocol (dependent on `address_family' and `socket_type')*/
		} ba_insufficient_port_numbers; /* E_BADALLOC_INSUFFICIENT_PORT_NUMBERS */

	}
#ifndef __COMPILER_HAVE_TRANSPARENT_UNION
	_ba_classes
#define ba_insufficient_heap_memory       _ba_classes.ba_insufficient_heap_memory
#define ba_insufficient_virtual_memory    _ba_classes.ba_insufficient_virtual_memory
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
E_UNKNOWN_SYSTEMCALL:[msg("Unknown system call")]
#if !defined(__i386__) && defined(__x86_64__)
struct exception_unknown_systemcall_data {
	syscall_ulong_t us_flags; /* System call invocation flags (Set of `RPC_SYSCALL_INFO_*')*/
	syscall_ulong_t us_sysno;
	syscall_ulong_t us_arg0;
	syscall_ulong_t us_arg1;
	syscall_ulong_t us_arg2;
	syscall_ulong_t us_arg3;
	syscall_ulong_t us_arg4;
	syscall_ulong_t us_arg5;
};
#endif /* !__i386__ && __x86_64__ */
E_UNKNOWN_SYSTEMCALL:[msg("Unknown system call")]
#ifdef __i386__
struct exception_unknown_systemcall_data {
	syscall_ulong_t us_flags; /* System call invocation flags (Set of `RPC_SYSCALL_INFO_*')*/
	syscall_ulong_t us_sysno;
	syscall_ulong_t us_arg0;
	syscall_ulong_t us_arg1;
	syscall_ulong_t us_arg2;
	syscall_ulong_t us_arg3;
	syscall_ulong_t us_arg4;
	syscall_ulong_t us_arg5;
};
#endif /* __i386__ */
E_NO_DEVICE:[msg("No such device")]
struct exception_no_device_data {
	uintptr_t nd_kind;  /* The kind of device (One of `E_NO_DEVICE_KIND_*')*/
	dev_t     nd_devno; /* The number for the named device*/
};
