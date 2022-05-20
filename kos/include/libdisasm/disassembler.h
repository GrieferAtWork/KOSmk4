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
#ifndef _LIBDISASM_DISASSEMBLER_H
#define _LIBDISASM_DISASSEMBLER_H 1

#include "api.h"
/**/

#include <hybrid/host.h>

#include <bits/crt/format-printer.h>
#include <bits/types.h>

#include <libc/string.h>

#include "format.h"

/* Known disassembler target IDs. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	DISASSEMBLER_TARGET_UNKNOWN = 0x0000, /* Unknown target */
	DISASSEMBLER_TARGET_8086    = 0x8086, /* Disassemble for 8086 (16-bit mode) (in AT&T syntax) */
	DISASSEMBLER_TARGET_I386    = 0x0386, /* Disassemble for i386+ (32-bit mode) (in AT&T syntax) */
	DISASSEMBLER_TARGET_X86_64  = 0x8664, /* Disassemble for x86_64 (64-bit mode) (in AT&T syntax) */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define DISASSEMBLER_TARGET_UNKNOWN DISASSEMBLER_TARGET_UNKNOWN /* Unknown target */
#define DISASSEMBLER_TARGET_8086    DISASSEMBLER_TARGET_8086    /* Disassemble for 8086 (16-bit mode) (in AT&T syntax) */
#define DISASSEMBLER_TARGET_I386    DISASSEMBLER_TARGET_I386    /* Disassemble for i386+ (32-bit mode) (in AT&T syntax) */
#define DISASSEMBLER_TARGET_X86_64  DISASSEMBLER_TARGET_X86_64  /* Disassemble for x86_64 (64-bit mode) (in AT&T syntax) */
#else /* __COMPILER_PREFERR_ENUMS */
#define DISASSEMBLER_TARGET_UNKNOWN 0     /* Unknown target */
#define DISASSEMBLER_TARGET_8086    32902 /* Disassemble for 8086 (16-bit mode) (in AT&T syntax) */
#define DISASSEMBLER_TARGET_I386    902   /* Disassemble for i386+ (32-bit mode) (in AT&T syntax) */
#define DISASSEMBLER_TARGET_X86_64  34404 /* Disassemble for x86_64 (64-bit mode) (in AT&T syntax) */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

/* The target ID for the hosting machine. */
#ifdef __x86_64__
#define DISASSEMBLER_TARGET_CURRENT DISASSEMBLER_TARGET_X86_64
#elif defined(__i386__)
#define DISASSEMBLER_TARGET_CURRENT DISASSEMBLER_TARGET_I386
#else /* ... */
#define DISASSEMBLER_TARGET_CURRENT DISASSEMBLER_TARGET_UNKNOWN
#endif /* !... */

/* Disassembler flags. */
#define DISASSEMBLER_FNORMAL  0x0000 /* Normal flags. */
#define DISASSEMBLER_FNOADDR  0x0001 /* Don't prefix a line with its address. */
#define DISASSEMBLER_FNOBYTES 0x0002 /* Don't include the raw instruction bytes in the disassembly. */

#ifdef __CC__
__DECL_BEGIN

struct disassembler;

/* Optional user-callback  for  printing  the name/address  of  a  symbol.
 * Used to  print the  operands of  instructions taking  text pointers  as
 * operands and (if provided) may be used to print the name of the nearest
 * symbol, as well as the offset from that symbol (if non-zero).
 * @param: self:        The associated disassembler.
 * @param: symbol_addr: The absolute address of the symbol (already offset by `d_baseoff')
 * @return: * :         The sum of return  values from calls to  `self->d_printer',
 *                      or a negative  value if an  error occurred while  printing,
 *                      or  alternatively `0' in  case `disasm_print()' and friends
 *                      were used to print output, rather than the printer callback
 *                      itself directly. */
typedef __ATTR_NONNULL_T((1)) __ssize_t
(LIBDISASM_CC *diasm_symbol_printer_t)(struct disassembler *__restrict self,
                                       void const *symbol_addr);

struct disassembler {
	__byte_t const        *d_pc;       /* [1..1] Next address to-be disassembled. */
	__ptrdiff_t            d_baseoff;  /* Offset added to `d_pc' for the purpose of relative relocations. */
	__pformatprinter       d_printer;  /* [1..1][const] The printer used to output disassembly text. */
	void                  *d_arg;      /* [const] Argument passed to `d_printer'. */
	__ssize_t              d_result;   /* Sum of all calls to `d_printer' (When negative, don't print anymore) */
	diasm_symbol_printer_t d_symbol;   /* [0..1][const]  An optional callback  for printing symbol names.
	                                    * When `NULL', the library will try to make use of `dladdr()' for
	                                    * the same purpose, but will default to printing symbol  operands
	                                    * as the ordinal value of their absolute address. */
	diasm_print_format_t   d_format;   /* [0..1][const] An optional callback for inserting format strings. */
	__UINTPTR_HALF_TYPE__  d_target;   /* Disassembler target (One of `DISASSEMBLER_TARGET_*'). */
	__UINTPTR_HALF_TYPE__  d_flags;    /* Disassembler flags (Set of `DISASSEMBLER_F*'). */
	__UINTPTR_HALF_TYPE__  d_maxbytes; /* The max number of instruction bytes to output onto a single  line.
	                                    * When ZERO(0), use a target-specific default value, but ignore this
	                                    * option  completely when the  `DISASSEMBLER_FNOBYTES' flag was set,
	                                    * in which case instruction bytes aren't printed at all. */
	__UINTPTR_HALF_TYPE__  d_pad0;     /* ... */
	void                  *d_pad1[4];  /* ... */
};


/* Initialize a given disassembler structure. */
__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(LIBDISASM_CC disasm_init)(struct disassembler *__restrict self,
                                        __pformatprinter printer, void *arg, void const *pc,
                                        __UINTPTR_HALF_TYPE__ target __DFL(DISASSEMBLER_TARGET_CURRENT),
                                        __UINTPTR_HALF_TYPE__ flags __DFL(DISASSEMBLER_FNORMAL),
                                        __ptrdiff_t baseoff __DFL(0)) {
	self->d_pc       = (__byte_t const *)pc;
	self->d_baseoff  = baseoff;
	self->d_printer  = printer;
	self->d_arg      = arg;
	self->d_result   = 0;
	self->d_format   = __NULLPTR;
	self->d_symbol   = __NULLPTR;
	self->d_target   = target;
	self->d_flags    = flags;
	self->d_maxbytes = 0;
	self->d_pad0     = 0;
	__libc_memset(self->d_pad1, 0, sizeof(self->d_pad1));
}

/* Helper functions to safely print using a given disassembler. */
__LOCAL __ATTR_NONNULL((1, 2)) void LIBDISASM_CC
disasm_print(struct disassembler *__restrict self,
             char const *__restrict text, __size_t len) {
	if __likely(self->d_result >= 0) {
		__ssize_t temp;
		temp = (*self->d_printer)(self->d_arg, text, len);
		if __unlikely(temp < 0)
			self->d_result = temp;
		else {
			self->d_result += temp;
		}
	}
}

__LOCAL __ATTR_NONNULL((1, 2)) void LIBDISASM_CC
disasm_puts(struct disassembler *__restrict self,
            char const *__restrict text) {
	disasm_print(self, text, __libc_strlen(text));
}

__LOCAL __ATTR_NONNULL((1)) void LIBDISASM_CC
disasm_puts_s(struct disassembler *__restrict self,
              char const *text) {
	if __likely(text)
		disasm_print(self, text, __libc_strlen(text));
}

__LOCAL __ATTR_NONNULL((1, 2)) void LIBDISASM_CC
disasm_vprintf(struct disassembler *__restrict self,
               char const *__restrict format,
               __builtin_va_list args);
__LOCAL __ATTR_NONNULL((1, 2)) void LIBDISASM_CC
disasm_printf(struct disassembler *__restrict self,
              char const *__restrict format, ...) {
	__builtin_va_list args;
	__builtin_va_start(args, format);
	disasm_vprintf(self, format, args);
	__builtin_va_end(args);
}

__LOCAL __ATTR_NONNULL((1)) void LIBDISASM_CC
disasm_print_format(struct disassembler *__restrict self,
                    unsigned int format_code) {
	if (self->d_format && __likely(self->d_result >= 0)) {
		__ssize_t temp;
		temp = (*self->d_format)(self, format_code);
		if __unlikely(temp < 0)
			self->d_result = temp;
		else {
			self->d_result += temp;
		}
	}
}



/* Quick and simple function for disassembling text into a given printer.
 * This is equivalent to:
 * >> struct disassembler da;
 * >> disasm_init(&da, printer, arg, pc, target, flags, 0);
 * >> return disasm_print_until(&da,(byte_t *)pc + num_bytes);
 * @return: * : The sum of all callbacks to `printer' ever executed with `self'
 * @return: <0: The first negative return value of `printer'. */
typedef __ATTR_NONNULL_T((1)) __ssize_t
(LIBDISASM_CC *PDISASM)(__pformatprinter printer, void *arg, void const *pc, __size_t num_bytes,
                        __UINTPTR_HALF_TYPE__ target /*__DFL(DISASSEMBLER_TARGET_CURRENT)*/,
                        __UINTPTR_HALF_TYPE__ flags /*__DFL(DISASSEMBLER_FNORMAL)*/);
#ifdef LIBDISASM_WANT_PROTOTYPES
LIBDISASM_DECL __ATTR_NONNULL((1)) __ssize_t LIBDISASM_CC
disasm(__pformatprinter printer, void *arg, void const *pc, __size_t num_bytes,
       __UINTPTR_HALF_TYPE__ target __DFL(DISASSEMBLER_TARGET_CURRENT),
       __UINTPTR_HALF_TYPE__ flags __DFL(DISASSEMBLER_FNORMAL));
#endif /* LIBDISASM_WANT_PROTOTYPES */


/* Quick and simple function for disassembling a single instruction.
 * This is equivalent to:
 * >> struct disassembler da;
 * >> disasm_init(&da, printer, arg, pc, target, flags, 0);
 * >> return disasm_print_instruction(&da);
 * @return: * : The sum of all callbacks to `printer' ever executed with `self'
 * @return: <0: The first negative return value of `printer'. */
typedef __ATTR_NONNULL_T((1)) __ssize_t
(LIBDISASM_CC *PDISASM_SINGLE)(__pformatprinter printer, void *arg, void const *pc,
                               __UINTPTR_HALF_TYPE__ target /*__DFL(DISASSEMBLER_TARGET_CURRENT)*/,
                               __UINTPTR_HALF_TYPE__ flags /*__DFL(DISASSEMBLER_FNORMAL)*/);
#ifdef LIBDISASM_WANT_PROTOTYPES
LIBDISASM_DECL __ATTR_NONNULL((1)) __ssize_t LIBDISASM_CC
disasm_single(__pformatprinter printer, void *arg, void const *pc,
              __UINTPTR_HALF_TYPE__ target __DFL(DISASSEMBLER_TARGET_CURRENT),
              __UINTPTR_HALF_TYPE__ flags __DFL(DISASSEMBLER_FNORMAL));
#endif /* LIBDISASM_WANT_PROTOTYPES */


/* Disassembly and print lines (s.a. `disasm_print_line()') until `endpc'
 * has been reached, or a printer error has occurred.
 * @return: * : The sum of all printer callbacks ever executed with `self'
 * @return: <0: The printer error that has occurred. */
typedef __ATTR_NONNULL_T((1)) __ssize_t
(LIBDISASM_CC *PDISASM_PRINT_UNTIL)(struct disassembler *__restrict self,
                                    void const *endpc);
#ifdef LIBDISASM_WANT_PROTOTYPES
LIBDISASM_DECL __ATTR_NONNULL((1)) __ssize_t LIBDISASM_CC
disasm_print_until(struct disassembler *__restrict self,
                   void const *endpc);
#endif /* LIBDISASM_WANT_PROTOTYPES */

/* Disassemble a single  instruction line, following  formatting rules  specified
 * by `DISASSEMBLER_F*', potentially printing multiple lines of the instruction's
 * bytes don't all fit into a single line (s.a. `').
 * @return: * : The sum of all printer callbacks ever executed with `self'
 * @return: <0: The printer error that has occurred. */
typedef __ATTR_NONNULL_T((1)) __ssize_t
(LIBDISASM_CC *PDISASM_PRINT_LINE)(struct disassembler *__restrict self);
#ifdef LIBDISASM_WANT_PROTOTYPES
LIBDISASM_DECL __ATTR_NONNULL((1)) __ssize_t LIBDISASM_CC
disasm_print_line(struct disassembler *__restrict self);
#endif /* LIBDISASM_WANT_PROTOTYPES */

/* Same as `libda_disasm_print_line()', but don't print a trailing line-feed. */
typedef __ATTR_NONNULL_T((1)) __ssize_t
(LIBDISASM_CC *PDISASM_PRINT_LINE_NOLF)(struct disassembler *__restrict self);
#ifdef LIBDISASM_WANT_PROTOTYPES
LIBDISASM_DECL __ATTR_NONNULL((1)) __ssize_t LIBDISASM_CC
disasm_print_line_nolf(struct disassembler *__restrict self);
#endif /* LIBDISASM_WANT_PROTOTYPES */

/* Disassemble a single instruction, including its mnemonic, and all operands.
 * This  function does not include any prefix,  nor does it append a trailing.
 * @return: * : The sum of all printer callbacks ever executed with `self'
 * @return: <0: The printer error that has occurred. */
typedef __ATTR_NONNULL_T((1)) __ssize_t
(LIBDISASM_CC *PDISASM_PRINT_INSTRUCTION)(struct disassembler *__restrict self);
#ifdef LIBDISASM_WANT_PROTOTYPES
LIBDISASM_DECL __ATTR_NONNULL((1)) __ssize_t LIBDISASM_CC
disasm_print_instruction(struct disassembler *__restrict self);
#endif /* LIBDISASM_WANT_PROTOTYPES */

/* Print the name+offset/address of a symbol at `symbol_addr'
 * @return: * : The sum of all printer callbacks ever executed with `self'
 * @return: <0: The printer error that has occurred. */
typedef __ATTR_NONNULL_T((1)) __ssize_t
(LIBDISASM_CC *PDISASM_PRINT_SYMBOL)(struct disassembler *__restrict self, void const *symbol_addr);
#ifdef LIBDISASM_WANT_PROTOTYPES
LIBDISASM_DECL __ATTR_NONNULL((1)) __ssize_t LIBDISASM_CC
disasm_print_symbol(struct disassembler *__restrict self, void const *symbol_addr);
#endif /* LIBDISASM_WANT_PROTOTYPES */

/* Returns the length (in bytes) of the next instruction to-be disassembled. */
typedef __ATTR_NONNULL_T((1)) __size_t
(LIBDISASM_CC *PDISASM_INSTRLEN)(struct disassembler *__restrict self);
#ifdef LIBDISASM_WANT_PROTOTYPES
LIBDISASM_DECL __ATTR_NONNULL((1)) __size_t LIBDISASM_CC
disasm_instrlen(struct disassembler *__restrict self);
#endif /* LIBDISASM_WANT_PROTOTYPES */

/* Return the default number of max instruction bytes to print for `target' */
typedef __ATTR_CONST_T __UINTPTR_HALF_TYPE__
(LIBDISASM_CC *PDISASM_DEFAULT_MAXBYTES)(__UINTPTR_HALF_TYPE__ target /*__DFL(DISASSEMBLER_TARGET_CURRENT)*/);
#ifdef LIBDISASM_WANT_PROTOTYPES
LIBDISASM_DECL __ATTR_CONST __UINTPTR_HALF_TYPE__ LIBDISASM_CC
disasm_default_maxbytes(__UINTPTR_HALF_TYPE__ target __DFL(DISASSEMBLER_TARGET_CURRENT));
#endif /* LIBDISASM_WANT_PROTOTYPES */

#ifndef __INTELLISENSE__

/* Fix cyclic dependency when the local implementation of `format_vprintf'
 * includes this  header  in  order to  provide  support  for  `%[disasm]' */
#ifdef __local_format_vprintf_defined
__NAMESPACE_LOCAL_BEGIN /* Forward-definition. */
__LOCAL_LIBC(format_vprintf) __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((1, 3, 4)) __SSIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(format_vprintf))(__pformatprinter __printer,
                                               void *__arg,
                                               char const *__restrict __format,
                                               __builtin_va_list __args);
__NAMESPACE_LOCAL_END
#else /* __local_format_vprintf_defined */
#include <format-printer.h>
#endif /* !__local_format_vprintf_defined */

__LOCAL __ATTR_NONNULL((1, 2)) void LIBDISASM_CC
disasm_vprintf(struct disassembler *__restrict self,
               char const *__restrict format,
               __builtin_va_list args) {
	if (self->d_result >= 0) {
		__ssize_t temp;
#ifdef __local_format_vprintf_defined
		temp = __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_vprintf)(self->d_printer,
		                                                               self->d_arg,
		                                                               format,
		                                                               args);
#else /* __local_format_vprintf_defined */
		temp = format_vprintf(self->d_printer,
		                      self->d_arg,
		                      format,
		                      args);
#endif /* !__local_format_vprintf_defined */
		if __unlikely(temp < 0)
			self->d_result = temp;
		else {
			self->d_result += temp;
		}
	}
}

#endif /* !__INTELLISENSE__ */

__DECL_END

#endif /* __CC__ */

#endif /* !_LIBDISASM_DISASSEMBLER_H */
