/* HASH CRC-32:0x25da73bd */
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
#ifndef __local_except_name_defined
#define __local_except_name_defined
#include <__crt.h>
#include <kos/bits/exception_data.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_rawmemchr_defined
#define __local___localdep_rawmemchr_defined
#ifdef __CRT_HAVE_rawmemchr
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),void *,__NOTHROW_NCX,__localdep_rawmemchr,(void const *__restrict __haystack, int __needle),rawmemchr,(__haystack,__needle))
#elif defined(__CRT_HAVE___rawmemchr)
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),void *,__NOTHROW_NCX,__localdep_rawmemchr,(void const *__restrict __haystack, int __needle),__rawmemchr,(__haystack,__needle))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/rawmemchr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_rawmemchr __LIBC_LOCAL_NAME(rawmemchr)
#endif /* !... */
#endif /* !__local___localdep_rawmemchr_defined */
#ifndef __local___localdep_strend_defined
#define __local___localdep_strend_defined
#ifdef __CRT_HAVE_strend
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __str),strend,(__str))
#else /* __CRT_HAVE_strend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strend __LIBC_LOCAL_NAME(strend)
#endif /* !__CRT_HAVE_strend */
#endif /* !__local___localdep_strend_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/host.h>
#include <kos/except/codes.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(except_name) __ATTR_CONST __ATTR_WUNUSED char const *
__NOTHROW(__LIBKCALL __LIBC_LOCAL_NAME(except_name))(__except_code_t __code) {
	__except_class_t __err_class       = EXCEPT_CLASS(__code);
	__except_subclass_t __err_subclass = EXCEPT_SUBCLASS(__code);
/*[[[deemon
(printExceptNameFunctionBody from ....misc.libgen.exceptinfo)(
	classVariableName:    "err_class",
	subClassVariableName: "err_subclass");
]]]*/
#if !defined(__i386__) && !defined(__x86_64__)
	static char const __e_linear_0000h_000ch[] =
	"E_OK\0\1E_BADALLOC\0E_BADALLOC_INSUFFICIENT_HEAP_MEMORY\0E_BADALLOC_"
	"INSUFFICIENT_VIRTUAL_MEMORY\0E_BADALLOC_ADDRESS_ALREADY_EXISTS\0E_"
	"BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY\0E_BADALLOC_INSUFFICIENT_SW"
	"AP_SPACE\0E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS\0E_BADALLOC_INSUF"
	"FICIENT_HANDLE_RANGE\0E_BADALLOC_INSUFFICIENT_DEVICE_NUMBERS\0E_BA"
	"DALLOC_INSUFFICIENT_INTERRUPT_VECTORS\0E_BADALLOC_INSUFFICIENT_PO"
	"RT_NUMBERS\0\1E_INVALID_ARGUMENT\0E_INVALID_ARGUMENT_UNKNOWN_FLAG\0E"
	"_INVALID_ARGUMENT_RESERVED_FLAG\0E_INVALID_ARGUMENT_BAD_FLAG_COMB"
	"INATION\0E_INVALID_ARGUMENT_BAD_FLAG_MASK\0E_INVALID_ARGUMENT_BAD_"
	"ALIGNMENT\0E_INVALID_ARGUMENT_BAD_VALUE\0E_INVALID_ARGUMENT_RESERV"
	"ED_ARGUMENT\0E_INVALID_ARGUMENT_UNKNOWN_COMMAND\0E_INVALID_ARGUMEN"
	"T_SOCKET_OPT\0E_INVALID_ARGUMENT_UNEXPECTED_COMMAND\0\1E_NOT_IMPLEM"
	"ENTED\0E_NOT_IMPLEMENTED_UNSUPPORTED\0E_NOT_IMPLEMENTED_TODO\0E_SER"
	"VICE_EXITED\0\1E_INVALID_HANDLE\0E_INVALID_HANDLE_FILE\0E_INVALID_HA"
	"NDLE_FILETYPE\0E_INVALID_HANDLE_OPERATION\0E_INVALID_HANDLE_NET_OP"
	"ERATION\0\1E_WOULDBLOCK\0E_WOULDBLOCK_PREEMPTED\0E_WOULDBLOCK_WAITFO"
	"RSIGNAL\0\1E_PROCESS_EXITED\0E_PROCESS_GROUP_EXITED\0\1E_NO_DEVICE\0\1E"
	"_UNKNOWN_SYSTEMCALL\0\1E_NO_SUCH_OBJECT\0E_NO_CTTY\0\1E_ILLEGAL_OPERA"
	"TION\0E_ILLEGAL_REFERENCE_LOOP\0E_ILLEGAL_BECAUSE_NOT_READY\0E_ILLE"
	"GAL_BECAUSE_GROUPING\0E_ILLEGAL_IO_OPERATION\0E_ILLEGAL_RESOURCE_L"
	"IMIT_EXCEEDED\0E_INVALID_OPERATION\0\1E_BROKEN_PIPE\0\1E_UNSUPPORTED_"
	"DEVICE\0\1";
	static char const __e_linear_0081h_0091h[] =
	"E_NET_ERROR\0E_NET_HOST_UNREACHABLE\0E_NET_ADDRESS_IN_USE\0E_NET_ME"
	"SSAGE_TOO_LONG\0E_NET_CONNECTION_ABORT\0E_NET_CONNECTION_REFUSED\0E"
	"_NET_CONNECTION_RESET\0E_NET_TIMEOUT\0E_NET_UNREACHABLE\0E_NET_ADDR"
	"ESS_NOT_AVAILABLE\0E_NET_SHUTDOWN\0\1E_IOERROR\0E_IOERROR_ERRORBIT\0E"
	"_IOERROR_TIMEOUT\0E_IOERROR_READONLY\0E_IOERROR_BADBOUNDS\0E_IOERRO"
	"R_NODATA\0\1E_NOT_EXECUTABLE\0E_NOT_EXECUTABLE_NOEXEC\0E_NOT_EXECUTA"
	"BLE_NOT_REGULAR\0E_NOT_EXECUTABLE_NOT_A_BINARY\0E_NOT_EXECUTABLE_F"
	"AULTY\0E_NOT_EXECUTABLE_TOOLARGE\0E_NOT_EXECUTABLE_TOOSMALL\0\1E_INS"
	"UFFICIENT_RIGHTS\0\1\1\1\1\1\1\1\1\1\1\1\1E_BUFFER_TOO_SMALL\0_E_BUFFER_TOO_SM"
	"ALL_EINVAL\0\1E_UNICODE_ERROR\0\1";
	static char const __e_linear_f000h_f000h[] =
	"E_INTERRUPT\0E_INTERRUPT_USER_RPC\0\1";
	static char const __e_linear_fe40h_fe40h[] =
	"E_EXIT_THREAD\0\1";
	static char const __e_linear_fe81h_fe81h[] =
	"E_EXIT_PROCESS\0\1";
	static char const __e_linear_feffh_ff07h[] =
	"E_UNHANDLED_INTERRUPT\0\1\1E_SEGFAULT\0E_SEGFAULT_UNMAPPED\0E_SEGFAUL"
	"T_READONLY\0E_SEGFAULT_NOTREADABLE\0E_SEGFAULT_NOTEXECUTABLE\0E_SEG"
	"FAULT_NOTATOMIC\0E_SEGFAULT_UNALIGNED\0E_SEGFAULT_NONCONTINUOUS\0\1E"
	"_BREAKPOINT\0\1E_DIVIDE_BY_ZERO\0\1E_OVERFLOW\0\1E_ILLEGAL_INSTRUCTION"
	"\0E_ILLEGAL_INSTRUCTION_BAD_OPCODE\0E_ILLEGAL_INSTRUCTION_UNSUPPOR"
	"TED_OPCODE\0E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE\0E_ILLEGAL_INS"
	"TRUCTION_BAD_OPERAND\0\0\0\0\0\0\0\0\0\0\0\0\0E_ILLEGAL_INSTRUCTION_REGISTER\0"
	"\1E_STACK_OVERFLOW\0\1E_INDEX_ERROR\0E_INDEX_ERROR_OUT_OF_BOUNDS\0\1";
	char const *__result;
	__except_class_t __class_offset;
	__except_subclass_t __subclass_offset;
	if (__err_class <= 0x000c) {
		__result = __e_linear_0000h_000ch;
		__class_offset = __err_class;
	} else if (__err_class >= 0x0081 && __err_class <= 0x0091) {
		__result = __e_linear_0081h_0091h;
		__class_offset = __err_class - 0x0081;
	} else if (__err_class >= 0xf000 && __err_class <= 0xf000) {
		__result = __e_linear_f000h_f000h;
		__class_offset = __err_class - 0xf000;
	} else if (__err_class >= 0xfe40 && __err_class <= 0xfe40) {
		__result = __e_linear_fe40h_fe40h;
		__class_offset = __err_class - 0xfe40;
	} else if (__err_class >= 0xfe81 && __err_class <= 0xfe81) {
		__result = __e_linear_fe81h_fe81h;
		__class_offset = __err_class - 0xfe81;
	} else if (__err_class >= 0xfeff && __err_class <= 0xff07) {
		__result = __e_linear_feffh_ff07h;
		__class_offset = __err_class - 0xfeff;
	} else {
		goto __non_linear_prefix;
	}
	while (__class_offset) {
		--__class_offset;
		__result = (char *)(__NAMESPACE_LOCAL_SYM __localdep_rawmemchr)(__result, '\1') + 1;
	}
	__subclass_offset = __err_subclass;
	for (;;) {
		if (*__result == '\1')
			break; /* End-of-class */
		if (!__subclass_offset) {
			if (!*__result)
				__result = __NULLPTR;
			return __result;
		}
		--__subclass_offset;
		__result = (__NAMESPACE_LOCAL_SYM __localdep_strend)(__result) + 1;
	}
__non_linear_prefix:
	switch(__err_class) {

	case 0x0080: {
		static char const __e_0080h_linear_0000h_001ah[] =
		"E_FSERROR\0E_FSERROR_DELETED\0E_FSERROR_FILE_NOT_FOUND\0E_FSERROR_P"
		"ATH_NOT_FOUND\0E_FSERROR_ILLEGAL_PATH\0E_FSERROR_NOT_A_DIRECTORY\0E"
		"_FSERROR_TOO_MANY_SYMBOLIC_LINKS\0E_FSERROR_ACCESS_DENIED\0E_FSERR"
		"OR_DISK_FULL\0E_FSERROR_READONLY\0E_FSERROR_TOO_MANY_HARD_LINKS\0E_"
		"FSERROR_IS_A_DIRECTORY\0E_FSERROR_NOT_A_SYMBOLIC_LINK\0E_FSERROR_I"
		"S_A_SYMBOLIC_LINK\0E_FSERROR_FILE_ALREADY_EXISTS\0E_FSERROR_DIRECT"
		"ORY_NOT_EMPTY\0E_FSERROR_CROSS_DEVICE_LINK\0E_FSERROR_DIRECTORY_MO"
		"VE_TO_CHILD\0E_FSERROR_MOUNT_UNSUPPORTED_DEVICE\0E_FSERROR_MOUNT_N"
		"EEDS_DEVICE\0E_FSERROR_WRONG_FILE_SYSTEM\0E_FSERROR_UNKNOWN_FILE_S"
		"YSTEM\0E_FSERROR_CORRUPTED_FILE_SYSTEM\0E_FSERROR_PATH_ALREADY_MOU"
		"NTED\0E_FSERROR_NOT_A_MOUNTING_POINT\0E_FSERROR_IS_A_MOUNTING_POIN"
		"T\0E_FSERROR_FILE_TOO_BIG";
		static char const __e_0080h_linear_0100h_0100h[] =
		"E_FSERROR_UNSUPPORTED_OPERATION";
		if (__err_subclass <= 0x001a) {
			__result = __e_0080h_linear_0000h_001ah;
			__subclass_offset = __err_subclass;
		} else if (__err_subclass >= 0x0100 && __err_subclass <= 0x0100) {
			__result = __e_0080h_linear_0100h_0100h;
			__subclass_offset = __err_subclass - 0x0100;
		} else {
			return __NULLPTR;
		}
	}	break;

	default:
		return __NULLPTR;
	}
	while (__subclass_offset) {
		--__subclass_offset;
		__result = (__NAMESPACE_LOCAL_SYM __localdep_strend)(__result) + 1;
	}
	if (!*__result)
		__result = __NULLPTR;
	return __result;
#else /* ... */
	static char const __e_linear_0000h_000ch[] =
	"E_OK\0\1E_BADALLOC\0E_BADALLOC_INSUFFICIENT_HEAP_MEMORY\0E_BADALLOC_"
	"INSUFFICIENT_VIRTUAL_MEMORY\0E_BADALLOC_ADDRESS_ALREADY_EXISTS\0E_"
	"BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY\0E_BADALLOC_INSUFFICIENT_SW"
	"AP_SPACE\0E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS\0E_BADALLOC_INSUF"
	"FICIENT_HANDLE_RANGE\0E_BADALLOC_INSUFFICIENT_DEVICE_NUMBERS\0E_BA"
	"DALLOC_INSUFFICIENT_INTERRUPT_VECTORS\0E_BADALLOC_INSUFFICIENT_PO"
	"RT_NUMBERS\0\1E_INVALID_ARGUMENT\0E_INVALID_ARGUMENT_UNKNOWN_FLAG\0E"
	"_INVALID_ARGUMENT_RESERVED_FLAG\0E_INVALID_ARGUMENT_BAD_FLAG_COMB"
	"INATION\0E_INVALID_ARGUMENT_BAD_FLAG_MASK\0E_INVALID_ARGUMENT_BAD_"
	"ALIGNMENT\0E_INVALID_ARGUMENT_BAD_VALUE\0E_INVALID_ARGUMENT_RESERV"
	"ED_ARGUMENT\0E_INVALID_ARGUMENT_UNKNOWN_COMMAND\0E_INVALID_ARGUMEN"
	"T_SOCKET_OPT\0E_INVALID_ARGUMENT_UNEXPECTED_COMMAND\0\1E_NOT_IMPLEM"
	"ENTED\0E_NOT_IMPLEMENTED_UNSUPPORTED\0E_NOT_IMPLEMENTED_TODO\0E_SER"
	"VICE_EXITED\0\1E_INVALID_HANDLE\0E_INVALID_HANDLE_FILE\0E_INVALID_HA"
	"NDLE_FILETYPE\0E_INVALID_HANDLE_OPERATION\0E_INVALID_HANDLE_NET_OP"
	"ERATION\0\1E_WOULDBLOCK\0E_WOULDBLOCK_PREEMPTED\0E_WOULDBLOCK_WAITFO"
	"RSIGNAL\0\1E_PROCESS_EXITED\0E_PROCESS_GROUP_EXITED\0\1E_NO_DEVICE\0\1E"
	"_UNKNOWN_SYSTEMCALL\0\1E_NO_SUCH_OBJECT\0E_NO_CTTY\0\1E_ILLEGAL_OPERA"
	"TION\0E_ILLEGAL_REFERENCE_LOOP\0E_ILLEGAL_BECAUSE_NOT_READY\0E_ILLE"
	"GAL_BECAUSE_GROUPING\0E_ILLEGAL_IO_OPERATION\0E_ILLEGAL_RESOURCE_L"
	"IMIT_EXCEEDED\0E_INVALID_OPERATION\0\1E_BROKEN_PIPE\0\1E_UNSUPPORTED_"
	"DEVICE\0\1";
	static char const __e_linear_0081h_0091h[] =
	"E_NET_ERROR\0E_NET_HOST_UNREACHABLE\0E_NET_ADDRESS_IN_USE\0E_NET_ME"
	"SSAGE_TOO_LONG\0E_NET_CONNECTION_ABORT\0E_NET_CONNECTION_REFUSED\0E"
	"_NET_CONNECTION_RESET\0E_NET_TIMEOUT\0E_NET_UNREACHABLE\0E_NET_ADDR"
	"ESS_NOT_AVAILABLE\0E_NET_SHUTDOWN\0\1E_IOERROR\0E_IOERROR_ERRORBIT\0E"
	"_IOERROR_TIMEOUT\0E_IOERROR_READONLY\0E_IOERROR_BADBOUNDS\0E_IOERRO"
	"R_NODATA\0\1E_NOT_EXECUTABLE\0E_NOT_EXECUTABLE_NOEXEC\0E_NOT_EXECUTA"
	"BLE_NOT_REGULAR\0E_NOT_EXECUTABLE_NOT_A_BINARY\0E_NOT_EXECUTABLE_F"
	"AULTY\0E_NOT_EXECUTABLE_TOOLARGE\0E_NOT_EXECUTABLE_TOOSMALL\0\1E_INS"
	"UFFICIENT_RIGHTS\0\1\1\1\1\1\1\1\1\1\1\1\1E_BUFFER_TOO_SMALL\0_E_BUFFER_TOO_SM"
	"ALL_EINVAL\0\1E_UNICODE_ERROR\0\1";
	static char const __e_linear_f000h_f000h[] =
	"E_INTERRUPT\0E_INTERRUPT_USER_RPC\0\1";
	static char const __e_linear_fe40h_fe40h[] =
	"E_EXIT_THREAD\0\1";
	static char const __e_linear_fe81h_fe81h[] =
	"E_EXIT_PROCESS\0\1";
	static char const __e_linear_feffh_ff0eh[] =
	"E_UNHANDLED_INTERRUPT\0\1E_DIVIDE_BY_ZERO\0\1\1\1E_BREAKPOINT\0\1E_OVERF"
	"LOW\0\1E_INDEX_ERROR\0E_INDEX_ERROR_OUT_OF_BOUNDS\0\1\1\1E_STACK_OVERFL"
	"OW\0\1\1\1\1\1\1E_SEGFAULT\0E_SEGFAULT_UNMAPPED\0E_SEGFAULT_READONLY\0E_SE"
	"GFAULT_NOTREADABLE\0E_SEGFAULT_NOTEXECUTABLE\0E_SEGFAULT_NOTATOMIC"
	"\0E_SEGFAULT_UNALIGNED\0E_SEGFAULT_NONCONTINUOUS\0\1";
	char const *__result;
	__except_class_t __class_offset;
	__except_subclass_t __subclass_offset;
	if (__err_class <= 0x000c) {
		__result = __e_linear_0000h_000ch;
		__class_offset = __err_class;
	} else if (__err_class >= 0x0081 && __err_class <= 0x0091) {
		__result = __e_linear_0081h_0091h;
		__class_offset = __err_class - 0x0081;
	} else if (__err_class >= 0xf000 && __err_class <= 0xf000) {
		__result = __e_linear_f000h_f000h;
		__class_offset = __err_class - 0xf000;
	} else if (__err_class >= 0xfe40 && __err_class <= 0xfe40) {
		__result = __e_linear_fe40h_fe40h;
		__class_offset = __err_class - 0xfe40;
	} else if (__err_class >= 0xfe81 && __err_class <= 0xfe81) {
		__result = __e_linear_fe81h_fe81h;
		__class_offset = __err_class - 0xfe81;
	} else if (__err_class >= 0xfeff && __err_class <= 0xff0e) {
		__result = __e_linear_feffh_ff0eh;
		__class_offset = __err_class - 0xfeff;
	} else {
		goto __non_linear_prefix;
	}
	while (__class_offset) {
		--__class_offset;
		__result = (char *)(__NAMESPACE_LOCAL_SYM __localdep_rawmemchr)(__result, '\1') + 1;
	}
	__subclass_offset = __err_subclass;
	for (;;) {
		if (*__result == '\1')
			break; /* End-of-class */
		if (!__subclass_offset) {
			if (!*__result)
				__result = __NULLPTR;
			return __result;
		}
		--__subclass_offset;
		__result = (__NAMESPACE_LOCAL_SYM __localdep_strend)(__result) + 1;
	}
__non_linear_prefix:
	switch(__err_class) {

	case 0x0080: {
		static char const __e_0080h_linear_0000h_001ah[] =
		"E_FSERROR\0E_FSERROR_DELETED\0E_FSERROR_FILE_NOT_FOUND\0E_FSERROR_P"
		"ATH_NOT_FOUND\0E_FSERROR_ILLEGAL_PATH\0E_FSERROR_NOT_A_DIRECTORY\0E"
		"_FSERROR_TOO_MANY_SYMBOLIC_LINKS\0E_FSERROR_ACCESS_DENIED\0E_FSERR"
		"OR_DISK_FULL\0E_FSERROR_READONLY\0E_FSERROR_TOO_MANY_HARD_LINKS\0E_"
		"FSERROR_IS_A_DIRECTORY\0E_FSERROR_NOT_A_SYMBOLIC_LINK\0E_FSERROR_I"
		"S_A_SYMBOLIC_LINK\0E_FSERROR_FILE_ALREADY_EXISTS\0E_FSERROR_DIRECT"
		"ORY_NOT_EMPTY\0E_FSERROR_CROSS_DEVICE_LINK\0E_FSERROR_DIRECTORY_MO"
		"VE_TO_CHILD\0E_FSERROR_MOUNT_UNSUPPORTED_DEVICE\0E_FSERROR_MOUNT_N"
		"EEDS_DEVICE\0E_FSERROR_WRONG_FILE_SYSTEM\0E_FSERROR_UNKNOWN_FILE_S"
		"YSTEM\0E_FSERROR_CORRUPTED_FILE_SYSTEM\0E_FSERROR_PATH_ALREADY_MOU"
		"NTED\0E_FSERROR_NOT_A_MOUNTING_POINT\0E_FSERROR_IS_A_MOUNTING_POIN"
		"T\0E_FSERROR_FILE_TOO_BIG";
		static char const __e_0080h_linear_0100h_0100h[] =
		"E_FSERROR_UNSUPPORTED_OPERATION";
		if (__err_subclass <= 0x001a) {
			__result = __e_0080h_linear_0000h_001ah;
			__subclass_offset = __err_subclass;
		} else if (__err_subclass >= 0x0100 && __err_subclass <= 0x0100) {
			__result = __e_0080h_linear_0100h_0100h;
			__subclass_offset = __err_subclass - 0x0100;
		} else {
			return __NULLPTR;
		}
	}	break;

	case 0xff06: {
		static char const __e_ff06h_linear_0000h_0011h[] =
		"E_ILLEGAL_INSTRUCTION\0E_ILLEGAL_INSTRUCTION_BAD_OPCODE\0E_ILLEGAL"
		"_INSTRUCTION_UNSUPPORTED_OPCODE\0E_ILLEGAL_INSTRUCTION_PRIVILEGED"
		"_OPCODE\0E_ILLEGAL_INSTRUCTION_BAD_OPERAND\0\0\0\0\0\0\0\0\0\0\0\0\0E_ILLEGAL_"
		"INSTRUCTION_REGISTER";
		static char const __e_ff06h_linear_8601h_8603h[] =
		"E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX\0E_ILLEGAL_INSTRUCTION_X86_T"
		"OO_LONG\0E_ILLEGAL_INSTRUCTION_X86_INTERRUPT";
		if (__err_subclass <= 0x0011) {
			__result = __e_ff06h_linear_0000h_0011h;
			__subclass_offset = __err_subclass;
		} else if (__err_subclass >= 0x8601 && __err_subclass <= 0x8603) {
			__result = __e_ff06h_linear_8601h_8603h;
			__subclass_offset = __err_subclass - 0x8601;
		} else {
			return __NULLPTR;
		}
	}	break;

	default:
		return __NULLPTR;
	}
	while (__subclass_offset) {
		--__subclass_offset;
		__result = (__NAMESPACE_LOCAL_SYM __localdep_strend)(__result) + 1;
	}
	if (!*__result)
		__result = __NULLPTR;
	return __result;
#endif /* !... */
/*[[[end]]]*/
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_except_name_defined
#define __local___localdep_except_name_defined
#define __localdep_except_name __LIBC_LOCAL_NAME(except_name)
#endif /* !__local___localdep_except_name_defined */
#endif /* !__local_except_name_defined */
