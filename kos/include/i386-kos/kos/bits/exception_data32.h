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
#include <hybrid/host.h>
#include <hybrid/typecore.h>
#include <kos/asm/except.h> /* Optional: EXCEPTION_DATA_POINTERS */


#ifndef __x86_64__
#define __OFFSET_EXCEPTION_DATA_CODE     __OFFSET_EXCEPTION_DATA32_CODE
#define __OFFSET_EXCEPTION_DATA_CLASS    __OFFSET_EXCEPTION_DATA32_CLASS
#define __OFFSET_EXCEPTION_DATA_SUBCLASS __OFFSET_EXCEPTION_DATA32_SUBCLASS
#define __OFFSET_EXCEPTION_DATA_POINTERS __OFFSET_EXCEPTION_DATA32_POINTERS
#define __OFFSET_EXCEPTION_DATA_POINTER  __OFFSET_EXCEPTION_DATA32_POINTER
#define __SIZEOF_EXCEPTION_DATA          __SIZEOF_EXCEPTION_DATA32
#define __SIZEOF_ERROR_CODE_T__          __SIZEOF_ERROR_CODE32_T__
#define __SIZEOF_ERROR_CLASS_T__         __SIZEOF_ERROR_CLASS32_T__
#define __SIZEOF_ERROR_SUBCLASS_T__      __SIZEOF_ERROR_SUBCLASS32_T__
#define error_code32_t      error_code_t
#define error_class32_t     error_class_t
#define error_subclass32_t  error_subclass_t
#define exception_data32    exception_data
#endif /* !__x86_64__ */


#ifndef EXCEPTION_DATA_POINTERS
#define EXCEPTION_DATA_POINTERS  8 /* Default value */
#endif /* !EXCEPTION_DATA_POINTERS */

#define __OFFSET_EXCEPTION_DATA32_CODE        0
#define __OFFSET_EXCEPTION_DATA32_CLASS       0
#define __OFFSET_EXCEPTION_DATA32_SUBCLASS    2
#define __OFFSET_EXCEPTION_DATA32_POINTERS    4
#define __OFFSET_EXCEPTION_DATA32_POINTER(i) (((i) + 1) * 4)
#define __SIZEOF_EXCEPTION_DATA32            ((EXCEPTION_DATA_POINTERS + 1) * 4)

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
struct __ATTR_PACKED exception_data32 /*[PREFIX(e_)]*/ {
	union __ATTR_PACKED {
		error_code32_t          e_code;   /* Exception code. */
		struct __ATTR_PACKED {
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
