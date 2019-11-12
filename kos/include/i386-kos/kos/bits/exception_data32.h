/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
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

#include <kos/asm/except.h> /* Optional: EXCEPTION_DATA_POINTERS */


#if defined(__i386__) && !defined(__x86_64__)
#undef __ERROR_UNWIND_CC
#undef __ERROR_THROW_CC
#undef __ERROR_THROWN_CC
#define __ERROR_UNWIND_CC __ATTR_FASTCALL
#define __ERROR_THROW_CC  __ATTR_FASTCALL
#define __ERROR_THROWN_CC __ATTR_CDECL

#define __OFFSET_EXCEPTION_DATA_CODE      __OFFSET_EXCEPTION_DATA32_CODE
#define __OFFSET_EXCEPTION_DATA_CLASS     __OFFSET_EXCEPTION_DATA32_CLASS
#define __OFFSET_EXCEPTION_DATA_SUBCLASS  __OFFSET_EXCEPTION_DATA32_SUBCLASS
#define __OFFSET_EXCEPTION_DATA_POINTERS  __OFFSET_EXCEPTION_DATA32_POINTERS
#define __OFFSET_EXCEPTION_DATA_POINTER   __OFFSET_EXCEPTION_DATA32_POINTER
#define __OFFSET_EXCEPTION_DATA_FAULTADDR __OFFSET_EXCEPTION_DATA32_FAULTADDR
#define __SIZEOF_EXCEPTION_DATA           __SIZEOF_EXCEPTION_DATA32
#define __SIZEOF_ERROR_CODE_T__           __SIZEOF_ERROR_CODE32_T__
#define __SIZEOF_ERROR_CLASS_T__          __SIZEOF_ERROR_CLASS32_T__
#define __SIZEOF_ERROR_SUBCLASS_T__       __SIZEOF_ERROR_SUBCLASS32_T__
#define error_code32_t      error_code_t
#define error_class32_t     error_class_t
#define error_subclass32_t  error_subclass_t
#define exception_data32    exception_data
#endif /* __i386__ && !__x86_64__ */


#ifndef EXCEPTION_DATA_POINTERS
#define EXCEPTION_DATA_POINTERS  8 /* Default value */
#endif /* !EXCEPTION_DATA_POINTERS */

#define __OFFSET_EXCEPTION_DATA32_CODE       0
#define __OFFSET_EXCEPTION_DATA32_CLASS      0
#define __OFFSET_EXCEPTION_DATA32_SUBCLASS   2
#define __OFFSET_EXCEPTION_DATA32_POINTERS   4
#define __OFFSET_EXCEPTION_DATA32_POINTER(i) (((i) + 1) * 4)
#define __OFFSET_EXCEPTION_DATA32_FAULTADDR  __OFFSET_EXCEPTION_DATA32_POINTER(EXCEPTION_DATA_POINTERS)
#define __SIZEOF_EXCEPTION_DATA32            ((EXCEPTION_DATA_POINTERS + 2) * 4)

#define __SIZEOF_ERROR_CODE32_T__     4
#define __SIZEOF_ERROR_CLASS32_T__    2
#define __SIZEOF_ERROR_SUBCLASS32_T__ 2

#ifdef __CC__
__SYSDECL_BEGIN

typedef __UINT32_TYPE__ error_code32_t;
typedef __UINT16_TYPE__ error_class32_t;
typedef __UINT16_TYPE__ error_subclass32_t;

#undef e_code
#undef e_class
#undef e_subclass

/* Exception information. */
struct exception_data32 /*[PREFIX(e_)]*/ {
	union {
		error_code32_t          e_code;   /* Exception code. */
		struct {
			error_class32_t     e_class;    /* Current exception class. */
			error_subclass32_t  e_subclass; /* Current exception sub-class. */
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
	/* Exception-specific data pointers */
	__UINT32_TYPE__      e_pointers[EXCEPTION_DATA_POINTERS];
	/* The address of the instruction that caused the fault.
	 * Unlike the program counter stored within the `error_register_state_t'
	 * structure which can be accessed through `error_register_state()', this
	 * one _may_ point _before_ the instruction that caused the error, however
	 * it may also point after the instruction. Which of the two it is depends
	 * on how the specific exception was generated, though it should be noted
	 * that in the case of errors thrown by `THROW()', this address will _always_
	 * point _after_ the instruction (meaning it's always equal to the program
	 * counter stored in `error_register_state()')
	 *  - e_faultaddr: Either equal to `GETPC(error_register_state())', or points
	 *                 to the instruction that is `error_register_state()'.
	 *  - GETPC(error_register_state()):
	 *                 Always points to the instruction that would have been
	 *                 executed next if the exception hadn't been thrown. */
	__HYBRID_PTR32(void) e_faultaddr;
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
