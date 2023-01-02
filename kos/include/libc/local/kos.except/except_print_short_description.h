/* HASH CRC-32:0xc04a6cb5 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_except_print_short_description_defined
#define __local_except_print_short_description_defined
#include <__crt.h>
#include <kos/bits/exception_data.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_except_as_errno_defined
#define __local___localdep_except_as_errno_defined
#ifdef __CRT_HAVE_except_as_errno
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__errno_t,__NOTHROW_NCX,__LIBKCALL,__localdep_except_as_errno,(struct exception_data const *__restrict __self),except_as_errno,(__self))
#else /* __CRT_HAVE_except_as_errno */
__NAMESPACE_LOCAL_END
#include <libc/local/kos.except/except_as_errno.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_except_as_errno __LIBC_LOCAL_NAME(except_as_errno)
#endif /* !__CRT_HAVE_except_as_errno */
#endif /* !__local___localdep_except_as_errno_defined */
#ifndef __local___localdep_except_name_defined
#define __local___localdep_except_name_defined
#ifdef __CRT_HAVE_except_name
__COMPILER_CREDIRECT(__LIBC,__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__LIBKCALL,__localdep_except_name,(__except_code_t __code),except_name,(__code))
#else /* __CRT_HAVE_except_name */
__NAMESPACE_LOCAL_END
#include <libc/local/kos.except/except_name.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_except_name __LIBC_LOCAL_NAME(except_name)
#endif /* !__CRT_HAVE_except_name */
#endif /* !__local___localdep_except_name_defined */
#ifndef __local___localdep_format_printf_defined
#define __local___localdep_format_printf_defined
#ifdef __CRT_HAVE_format_printf
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_IN(3) __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((1)) __SSIZE_TYPE__ (__VLIBCCALL __localdep_format_printf)(__pformatprinter __printer, void *__arg, char const *__restrict __format, ...) __THROWS(...) __CASMNAME("format_printf");
#else /* __CRT_HAVE_format_printf */
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_printf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_printf __LIBC_LOCAL_NAME(format_printf)
#endif /* !__CRT_HAVE_format_printf */
#endif /* !__local___localdep_format_printf_defined */
#ifndef __local___localdep_strerrorname_np_defined
#define __local___localdep_strerrorname_np_defined
#ifdef __CRT_HAVE_strerrorname_np
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_strerrorname_np,(__errno_t __errnum),strerrorname_np,(__errnum))
#elif defined(__CRT_HAVE_strerrno)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_strerrorname_np,(__errno_t __errnum),strerrno,(__errnum))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strerrorname_np.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strerrorname_np __LIBC_LOCAL_NAME(strerrorname_np)
#endif /* !... */
#endif /* !__local___localdep_strerrorname_np_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/host.h>
#include <kos/except/codes.h>
#include <bits/crt/inttypes.h>
#include <libregdump/register.h>
#include <dlfcn.h>
#include <libansitty/ctl.h>
#if defined(__i386__) || defined(__x86_64__)
#include <asm/registers.h>
#endif /* __i386__ || __x86_64__ */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(except_print_short_description) __ATTR_IN(3) __ATTR_NONNULL((1)) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(except_print_short_description))(__pformatprinter __printer, void *__arg, struct exception_data const *__data, __UINTPTR_TYPE__ __flags) {
#ifndef __PRIxPTR
#ifdef __PRIP_PREFIX
#define __PRIxPTR __PRIP_PREFIX "x"
#else /* __PRIP_PREFIX */
#define __PRIxPTR "zx"
#endif /* !__PRIP_PREFIX */
#endif /* !__PRIxPTR */
#define __FMT(__tty, __notty) (__flags & 1 ? __tty : __notty)
	__SSIZE_TYPE__ __temp, __result = 0;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_format_printf)(__printer, __arg,
	                       __FMT("exception "
	                           AC_WHITE("%#" __PRIN_PREFIX(__SIZEOF_EXCEPT_CLASS_T__) "x") ":"
	                           AC_WHITE("%#" __PRIN_PREFIX(__SIZEOF_EXCEPT_SUBCLASS_T__) "x"),
	                           "exception "
	                           "%#" __PRIN_PREFIX(__SIZEOF_EXCEPT_CLASS_T__) "x:"
	                           "%#" __PRIN_PREFIX(__SIZEOF_EXCEPT_SUBCLASS_T__) "x"),
	                       __data->e_class, __data->e_subclass);
	if __unlikely(__result < 0)
		goto __done;
	{
		char const *__name;
		char const *__errno_name; /* XXX: Also print in kernel-space? */
		__name = (__NAMESPACE_LOCAL_SYM __localdep_except_name)(__data->e_code);
		__errno_name = (__NAMESPACE_LOCAL_SYM __localdep_strerrorname_np)((__NAMESPACE_LOCAL_SYM __localdep_except_as_errno)(__data));
		if (__name) {
			__temp = (__NAMESPACE_LOCAL_SYM __localdep_format_printf)(__printer, __arg,
			                     __FMT(" [" AC_WHITE("%s") "%s" AC_WHITE("%s") "]",
			                         " [%s%s%s]"),
			                     __name,
			                     __errno_name ? "," : "",
			                     __errno_name ? __errno_name : "");
			if __unlikely(__temp < 0)
				goto __err;
			__result += __temp;
		}
	}
	__temp = 0;
	switch (__data->e_class) {

	case EXCEPT_CLASS(EXCEPT_CODEOF(E_BADALLOC)):
		switch (__data->e_subclass) {

		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY)):
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY)):
			__temp = (__NAMESPACE_LOCAL_SYM __localdep_format_printf)(__printer, __arg,
			                     __FMT(" [num_bytes:" AC_WHITE("%#" __PRIxPTR) "]",
			                         " [num_bytes:%#" __PRIxPTR "]"),
			                     __data->e_args.e_badalloc.ba_insufficient_heap_memory);
			break;

		default:
			break;
		}
		break;

	/* TODO: More error classes */

	case EXCEPT_CLASS(EXCEPT_CODEOF(E_SEGFAULT)): {
		__temp = (__NAMESPACE_LOCAL_SYM __localdep_format_printf)(__printer, __arg,
#if defined(__i386__) || defined(__x86_64__)
		                     __FMT(" [cr2:" AC_WHITE("%p") "," AC_WHITE("%c%c%c%c%c%c") "]",
		                         " [cr2:%p,%c%c%c%c%c%c]")
#else /* __i386__ || __x86_64__ */
		                     __FMT(" [addr:" AC_WHITE("%p") "," AC_WHITE("%c%c%c%c%c%c") "]",
		                         " [addr:%p,%c%c%c%c%c%c]")
#endif /* !__i386__ && !__x86_64__ */
		                     ,
		                     __data->e_args.e_segfault.s_addr,
		                     __data->e_args.e_segfault.s_context & E_SEGFAULT_CONTEXT_FAULT ? 'f' : '-',
		                     __data->e_args.e_segfault.s_context & E_SEGFAULT_CONTEXT_WRITING ? 'w' : '-',
		                     __data->e_args.e_segfault.s_context & E_SEGFAULT_CONTEXT_USERCODE ? 'u' : '-',
		                     __data->e_args.e_segfault.s_context & E_SEGFAULT_CONTEXT_NONCANON ? 'c' : '-',
		                     __data->e_args.e_segfault.s_context & E_SEGFAULT_CONTEXT_EXEC ? 'x' : '-',
		                     __data->e_args.e_segfault.s_context & E_SEGFAULT_CONTEXT_VIO ? 'v' : '-');
	}	break;

	case EXCEPT_CLASS(EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION)): {
#if defined(__i386__) || defined(__x86_64__)
		__UINTPTR_TYPE__ __opcode, __opno;
		__opcode = __data->e_args.e_illegal_instruction.ii_opcode;
		__opno   = E_ILLEGAL_INSTRUCTION_X86_OPCODE_GETOPC(__opcode);
		if (__opno <= 0xff) {
			__temp = (__NAMESPACE_LOCAL_SYM __localdep_format_printf)(__printer, __arg,
			                     __FMT(" [opcode:" AC_WHITE("%#.2" __PRIxPTR),
			                         " [opcode:%#.2" __PRIxPTR),
			                     __opno);
		} else if (__opno <= 0xffff) {
			__temp = (__NAMESPACE_LOCAL_SYM __localdep_format_printf)(__printer, __arg,
			                     __FMT(" [opcode:" AC_WHITE("%#.4" __PRIxPTR),
			                         " [opcode:%#.4" __PRIxPTR),
			                     __opno);
		} else {
			__temp = (__NAMESPACE_LOCAL_SYM __localdep_format_printf)(__printer, __arg,
			                     __FMT(" [opcode:" AC_WHITE("%#" __PRIxPTR),
			                         " [opcode:%#" __PRIxPTR),
			                     __opno);
		}
		if __unlikely(__temp < 0)
			goto __err;
		__result += __temp;
		if (E_ILLEGAL_INSTRUCTION_X86_OPCODE_HASREG(__opcode)) {
			__temp = (__NAMESPACE_LOCAL_SYM __localdep_format_printf)(__printer, __arg, "/%u", (unsigned int)E_ILLEGAL_INSTRUCTION_X86_OPCODE_GETREG(__opcode));
			if __unlikely(__temp < 0)
				goto __err;
			__result += __temp;
		}
		__temp = (*__printer)(__arg, "]", 1);
#else /* __i386__ || __x86_64__ */
		__UINTPTR_TYPE__ __opcode = __data->e_args.e_illegal_instruction.ii_opcode;
		if (__opcode <= 0xff) {
			__temp = (__NAMESPACE_LOCAL_SYM __localdep_format_printf)(__printer, __arg,
			                     __FMT(" [opcode:" AC_WHITE("%#.2" __PRIxPTR) "]",
			                         " [opcode:%#.2" __PRIxPTR "]"),
			                     __opcode);
		} else if (__opcode <= 0xffff) {
			__temp = (__NAMESPACE_LOCAL_SYM __localdep_format_printf)(__printer, __arg,
			                     __FMT(" [opcode:" AC_WHITE("%#.4" __PRIxPTR) "]",
			                         " [opcode:%#.4" __PRIxPTR "]"),
			                     __opcode);
		} else {
			__temp = (__NAMESPACE_LOCAL_SYM __localdep_format_printf)(__printer, __arg,
			                     __FMT(" [opcode:" AC_WHITE("%#" __PRIxPTR) "]",
			                         " [opcode:%#" __PRIxPTR "]"),
			                     __opcode);
		}
#endif /* !__i386__ && !__x86_64__ */
		if __unlikely(__temp < 0)
			goto __err;
		__result += __temp;
		switch (__data->e_subclass) {

#ifdef E_ILLEGAL_INSTRUCTION_X86_INTERRUPT
		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_X86_INTERRUPT)):
			__temp = (__NAMESPACE_LOCAL_SYM __localdep_format_printf)(__printer, __arg,
			                     __FMT(" [int:" AC_WHITE("%#.2" __PRIxPTR) ","
			                                  AC_WHITE("%#" __PRIxPTR) ","
			                                  "seg:" AC_WHITE("%#" __PRIxPTR) "]",
			                         " [int:%#.2" __PRIxPTR ",%#" __PRIxPTR ",seg:%#" __PRIxPTR "]"),
			                     __data->e_args.e_illegal_instruction.ii_x86_interrupt.xi_intno,
			                     __data->e_args.e_illegal_instruction.ii_x86_interrupt.xi_ecode,
			                     __data->e_args.e_illegal_instruction.ii_x86_interrupt.xi_segval);
			break;
#endif /* E_ILLEGAL_INSTRUCTION_X86_INTERRUPT */

		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPERAND)): {
			char const *__what_name;
			switch (__data->e_args.e_illegal_instruction.ii_bad_operand.bo_what) {

			case E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_MEMORY:
			case E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_REGISTER:
				__what_name = "addrmode";
				break;

			case E_ILLEGAL_INSTRUCTION_BAD_OPERAND_VALUE:
				__what_name = "value";
				break;

			default:
				__what_name = __NULLPTR;
				break;
			}
			if (__what_name) {
				__temp = (__NAMESPACE_LOCAL_SYM __localdep_format_printf)(__printer, __arg,
				                     __FMT(" [what=" AC_WHITE("%s") "]",
				                         " [what=%s]"),
				                     __what_name);
			} else {
				__temp = (__NAMESPACE_LOCAL_SYM __localdep_format_printf)(__printer, __arg,
				                     __FMT(" [what=" AC_WHITE("?(%#" __PRIxPTR ")") "]",
				                         " [what=?(%#" __PRIxPTR ")]"),
				                     __data->e_args.e_illegal_instruction.ii_bad_operand.bo_what);
			}
		}	break;

		case EXCEPT_SUBCLASS(EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER)): {
			char const *__what;
			__UINTPTR_TYPE__ __regno;
			switch (__data->e_args.e_illegal_instruction.ii_register.r_how) {
			case E_ILLEGAL_INSTRUCTION_REGISTER_RDINV: __what = "rdinv"; break; /* Read from invalid register */
			case E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV: __what = "rdprv"; break; /* Read from privileged register */
			case E_ILLEGAL_INSTRUCTION_REGISTER_WRINV: __what = "wrinv"; break; /* Write to invalid register */
			case E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV: __what = "wrprv"; break; /* Write to privileged register */
			case E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD: __what = "wrbad"; break; /* Bad value written to register */
			default: __what = __NULLPTR; break;
			}
			if (__what) {
				__temp = (__NAMESPACE_LOCAL_SYM __localdep_format_printf)(__printer, __arg, " [%s:", __what);
			} else {
				__temp = (__NAMESPACE_LOCAL_SYM __localdep_format_printf)(__printer, __arg, " [?(%#" __PRIxPTR "):",
				                     __data->e_args.e_illegal_instruction.ii_register.r_how);
			}
			if __unlikely(__temp < 0)
				goto __err;
			__result += __temp;
			__regno = __data->e_args.e_illegal_instruction.ii_register.r_regno;
#if defined(__i386__) || defined(__x86_64__)
			if (__regno == X86_REGISTER_XCR || __regno == X86_REGISTER_PCR || __regno == X86_REGISTER_MSR) {
				char __extname[4];
				__extname[0] = 'x';
				__extname[1] = 'c';
				__extname[2] = 'r';
				__extname[3] = 0;
				if (__regno == X86_REGISTER_PCR) {
					__extname[0] = 'p';
				} else if (__regno == X86_REGISTER_MSR) {
					__extname[0] = 'm';
					__extname[1] = 's';
				}
				__temp = (__NAMESPACE_LOCAL_SYM __localdep_format_printf)(__printer, __arg,
				                     __FMT(AC_WHITE("%s(%#" __PRIxPTR ")") "," AC_WHITE("%#" __PRI8_PREFIX "x") "]",
				                         "%s(%#" __PRIxPTR "),%#" __PRI8_PREFIX "x]"),
				                     __extname, __data->e_args.e_illegal_instruction.ii_register.r_offset,
				                     (__UINT64_TYPE__)__data->e_args.e_illegal_instruction.ii_register.r_regval |
				                     (__UINT64_TYPE__)__data->e_args.e_illegal_instruction.ii_register.r_regval2 << 32);
			} else
#endif /* __i386__ || __x86_64__ */
			{
				if (__flags & 1) {
					static char const __beginfg[] = AC_FG(ANSITTY_CL_WHITE);
					__temp = (*__printer)(__arg, __beginfg, __COMPILER_STRLEN(__beginfg));
					if __unlikely(__temp < 0)
						goto __err;
					__result += __temp;
				}
#ifdef __LIBREGDUMP_WANT_PROTOTYPES
				__temp = __regdump_register_name(__printer, __arg, __regno);
#else /* __LIBREGDUMP_WANT_PROTOTYPES */
#if defined(__CRT_HAVE_dlopen) && defined(__CRT_HAVE_dlsym)
				void *__libregdump;
#ifdef __RTLD_LOCAL
				__libregdump = dlopen(LIBREGDUMP_LIBRARY_NAME, RTLD_LOCAL);
#else /* __RTLD_LOCAL */
				__libregdump = dlopen(LIBREGDUMP_LIBRARY_NAME, 0);
#endif /* !__RTLD_LOCAL */
				if (__libregdump != __NULLPTR) {
					PREGDUMP_REGISTER_NAME __pdyn_regdump_register_name;
					*(void **)&__pdyn_regdump_register_name = dlsym(__libregdump, "regdump_register_name");
					if __unlikely(!__pdyn_regdump_register_name) {
#ifdef __CRT_HAVE_dlclose
						dlclose(__libregdump);
#endif /* __CRT_HAVE_dlclose */
						goto __print_generic_register_name;
					}
					__temp = (*__pdyn_regdump_register_name)(__printer, __arg, __regno);
#ifdef __CRT_HAVE_dlclose
					dlclose(__libregdump);
#endif /* __CRT_HAVE_dlclose */
				} else
#endif /* __CRT_HAVE_dlopen && __CRT_HAVE_dlsym */
				{
__print_generic_register_name:
					__temp = (__NAMESPACE_LOCAL_SYM __localdep_format_printf)(__printer, __arg, "reg.%#" __PRIxPTR, __regno);
				}
#endif /* !__LIBREGDUMP_WANT_PROTOTYPES */
				if __unlikely(__temp < 0)
					goto __err;
				__result += __temp;
				if (__flags & 1) {
					static char const __endfg[] = AC_FGDEF;
					__temp = (*__printer)(__arg, __endfg, __COMPILER_STRLEN(__endfg));
					if __unlikely(__temp < 0)
						goto __err;
					__result += __temp;
				}
				if (__data->e_args.e_illegal_instruction.ii_register.r_regval != 0 ||
				    (__data->e_args.e_illegal_instruction.ii_register.r_how != E_ILLEGAL_INSTRUCTION_REGISTER_RDINV &&
				     __data->e_args.e_illegal_instruction.ii_register.r_how != E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV)) {
					__temp = (__NAMESPACE_LOCAL_SYM __localdep_format_printf)(__printer, __arg,
					                     __FMT("," AC_WHITE("%#" __PRIxPTR) "]",
					                         ",%#" __PRIxPTR "]"),
					                     __data->e_args.e_illegal_instruction.ii_register.r_regval);
				} else {
					__temp = (*__printer)(__arg, "]", 1);
				}
			}
		}	break;

		default:
			__temp = 0;
			break;
		}
	}	break;

	default:
		break;
	}
	if __unlikely(__temp < 0)
		goto __err;
	__result += __temp;
__done:
	return __result;
__err:
	return __temp;
#undef __FMT
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_except_print_short_description_defined
#define __local___localdep_except_print_short_description_defined
#define __localdep_except_print_short_description __LIBC_LOCAL_NAME(except_print_short_description)
#endif /* !__local___localdep_except_print_short_description_defined */
#endif /* !__local_except_print_short_description_defined */
