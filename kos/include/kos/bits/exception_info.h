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
/*!replace_with_include <kos/except.h>*/
#ifndef _KOS_BITS_EXCEPTION_INFO_H
#define _KOS_BITS_EXCEPTION_INFO_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/byteorder.h>
#include <hybrid/typecore.h>

#include <bits/types.h>
#include <kos/bits/except-register-state.h> /* __EXCEPT_REGISTER_STATE_TYPE */
#include <kos/bits/exception_data.h>        /* struct exception_data */
#include <kos/bits/exception_nest.h>        /* __EXCEPT_BACKTRACE_SIZE */

#undef EXCEPT_BACKTRACE_SIZE
#define EXCEPT_BACKTRACE_SIZE __EXCEPT_BACKTRACE_SIZE

#define EXCEPT_FNORMAL    0x00 /* Normal exception handler flags. */
#define EXCEPT_FRETHROW   0x01 /* FLAG: The exception should be rethrown.
                                * Unless set when `__cxa_end_catch()' is called, `ei_code'
                                * will  be  changed  to `E_OK',  indicating  no exception. */
#ifndef __KERNEL__
#define EXCEPT_FINEXCEPT  0x20 /* FLAG: Currently within `libc_except_handler(3|4)()' (used to  prevent
                                *       an infinite loop when the exception handler itself is faulting) */
#define EXCEPT_FINEXCEPT2 0x40 /* FLAG: Same as `EXCEPT_FINEXCEPT', but set when that flag was already set. When both
                                *       flags are already set, a coredump is triggered. Using this double-indirection
                                *       mechanism, it becomes possible to  handle things such as segmentation  faults
                                *       when  accessing memory during unwinding, and ensuring that the correct unwind
                                *       error codes (in this case  `UNWIND_SEGFAULT') get produced instead of  always
                                *       causing `UNWIND_USER_RECURSION' (which should only be produced if the  unwind
                                *       machinery itself has become faulty) */
#define EXCEPT_FMAYSIGNAL 0x80 /* FLAG: The exception may be converted into a signal when `except_unwind(3)' cannot find
                                *       a handler  apart of  some except-aware  module (s.a.  set_exception_handler:#4).
                                *       If the exception cannot be translated, a coredump is performed. */
#endif /* !__KERNEL__ */
#define OFFSET_EXCEPTION_INFO_STATE    0
#define OFFSET_EXCEPTION_INFO_DATA     __SIZEOF_EXCEPT_REGISTER_STATE
#define OFFSET_EXCEPTION_INFO_CODE     (__SIZEOF_EXCEPT_REGISTER_STATE + __OFFSET_EXCEPTION_DATA_CODE)
#define OFFSET_EXCEPTION_INFO_POINTERS (__SIZEOF_EXCEPT_REGISTER_STATE + __OFFSET_EXCEPTION_DATA_ARGS)
#define OFFSET_EXCEPTION_INFO_TRACE    (__SIZEOF_EXCEPT_REGISTER_STATE + __SIZEOF_EXCEPTION_DATA)
#define OFFSET_EXCEPTION_INFO_FLAGS    (__SIZEOF_EXCEPT_REGISTER_STATE + __SIZEOF_EXCEPTION_DATA + (__EXCEPT_BACKTRACE_SIZE * __SIZEOF_POINTER__))

#ifdef __CC__
__DECL_BEGIN

#ifndef __except_register_state_t_defined
#define __except_register_state_t_defined
typedef __EXCEPT_REGISTER_STATE_TYPE except_register_state_t;
#endif /* !__except_register_state_t_defined */
struct exception_info;

#undef ei_data
#undef ei_code
#undef ei_class
#undef ei_subclass
struct exception_info {
	/* The CPU state at the time the exception was originally thrown.
	 * NOTE: The  PC  register  of  this  state  represents  the   program
	 *       location  _AFTER_ the instruction  that caused the exception.
	 *       In the case  of the  exception being caused  by a  `THROW()',
	 *       this is the return address of the call to the throw-function.
	 *       In the case of cpu-specific  exceptions, it points after  the
	 *       instruction responsible for the exception.
	 *    -> With that in mind, when querying for special properties of PC,
	 *       you  must always subtract  `1' from the  address, such as when
	 *       calling  `unwind_at()', which requires you to provide `PC - 1'
	 *       for its `abs_pc' argument. */
	except_register_state_t     ei_state;
	union {
		__except_code_t         ei_code;     /* Current exception code. */
		struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			__except_class_t    ei_class;    /* Current exception class. */
			__except_subclass_t ei_subclass; /* Current exception sub-class. */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			__except_subclass_t ei_subclass; /* Current exception sub-class. */
			__except_class_t    ei_class;    /* Current exception class. */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		}
#ifndef __COMPILER_HAVE_TRANSPARENT_STRUCT
		_ei_class_subclass
#endif /* !__COMPILER_HAVE_TRANSPARENT_STRUCT */
		;
		struct exception_data  ei_data;     /* Exception data. */
	}
#ifndef __COMPILER_HAVE_TRANSPARENT_UNION
	_ei_code_data
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
	;
#if __EXCEPT_BACKTRACE_SIZE != 0
	/* Exception backtrace (from least-recent[0] to most-recent[__EXCEPT_BACKTRACE_SIZE - 1])
	 * This vector is populated as  the stack is unwound, until  it is either full, or  until
	 * the exception is handled.
	 * The  vector's ends either  when `__EXCEPT_BACKTRACE_SIZE' were found,  or upon the first
	 * entry that evaluates to `NULL'. If a `NULL' entry was found, and the caller is currently
	 * in the process of unwinding the stack,  the traceback continues where their CPU  context
	 * meets with the next unwind location.
	 * NOTE: In order to prevent redundancy, this trace only starts with the first  unwind
	 *       location of the exception, with the exception's original throw-location found
	 *       stored within the PC register of `ei_state'
	 * NOTE: The pointers in this traceback have not been adjusted, meaning that they probably
	 *       point  to the first  instruction after some `call'  instruction (i.e. they're the
	 *       return addresses loaded during unwinding) */
	void const                *ei_trace[__EXCEPT_BACKTRACE_SIZE];
#endif /* __EXCEPT_BACKTRACE_SIZE != 0 */
	__uint8_t                  ei_flags;    /* Flags describing the current exception state (Set of `EXCEPT_F*'). */
#if __SIZEOF_POINTER__ < 4
	__uint8_t                  ei_nesting;  /* # of times that `except_nesting_begin()' was called (as a non-no-op). */
#elif __SIZEOF_POINTER__ == 4
	__uint8_t                __ei_pad[1];   /* ... */
	__uint16_t                 ei_nesting;  /* # of times that `except_nesting_begin()' was called (as a non-no-op). */
#elif __SIZEOF_POINTER__ == 8
	__uint8_t                __ei_pad[3];   /* ... */
	__uint32_t                 ei_nesting;  /* # of times that `except_nesting_begin()' was called (as a non-no-op). */
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported `__SIZEOF_POINTER__'"
#endif /* __SIZEOF_POINTER__ != ... */
};
#if !defined(__COMPILER_HAVE_TRANSPARENT_UNION) && !defined(__COMPILER_HAVE_TRANSPARENT_STRUCT)
#define ei_data     _ei_code_data.ei_data
#define ei_code     _ei_code_data.ei_code
#define ei_class    _ei_code_data._ei_class_subclass.ei_class
#define ei_subclass _ei_code_data._ei_class_subclass.ei_subclass
#elif !defined(__COMPILER_HAVE_TRANSPARENT_UNION)
#define ei_data     _ei_code_data.ei_data
#define ei_code     _ei_code_data.ei_code
#define ei_class    _ei_code_data.ei_class
#define ei_subclass _ei_code_data.ei_subclass
#elif !defined(__COMPILER_HAVE_TRANSPARENT_STRUCT)
#define ei_class    _ei_class_subclass.ei_class
#define ei_subclass _ei_class_subclass.ei_subclass
#endif /* ... */

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_BITS_EXCEPTION_INFO_H */
