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
#ifndef _KOS_BITS_EXCEPTION_DATA_H
#define _KOS_BITS_EXCEPTION_DATA_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>
#include <hybrid/__byteorder.h>
#include <kos/asm/except.h> /* Optional: EXCEPTION_DATA_POINTERS */

#ifndef EXCEPTION_DATA_POINTERS
#define EXCEPTION_DATA_POINTERS  8 /* Default value */
#endif /* !EXCEPTION_DATA_POINTERS */


#define __OFFSET_EXCEPTION_DATA_CODE      0
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define __OFFSET_EXCEPTION_DATA_CLASS     0
#define __OFFSET_EXCEPTION_DATA_SUBCLASS (__SIZEOF_POINTER__ / 2)
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#define __OFFSET_EXCEPTION_DATA_CLASS    (__SIZEOF_POINTER__ / 2)
#define __OFFSET_EXCEPTION_DATA_SUBCLASS  0
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
#define __OFFSET_EXCEPTION_DATA_POINTERS  __SIZEOF_POINTER__
#define __OFFSET_EXCEPTION_DATA_POINTER(i) (((i) + 1) * __SIZEOF_POINTER__)
#define __SIZEOF_EXCEPTION_DATA          ((EXCEPTION_DATA_POINTERS + 1) * __SIZEOF_POINTER__)


#define __SIZEOF_ERROR_CODE_T__       __SIZEOF_POINTER__
#define __SIZEOF_ERROR_CLASS_T__     (__SIZEOF_POINTER__/2)
#define __SIZEOF_ERROR_SUBCLASS_T__  (__SIZEOF_POINTER__/2)


#ifdef __CC__
__SYSDECL_BEGIN

typedef __UINTPTR_TYPE__      error_code_t;
typedef __UINTPTR_HALF_TYPE__ error_class_t;
typedef __UINTPTR_HALF_TYPE__ error_subclass_t;

#undef e_code
#undef e_class
#undef e_subclass

/* Exception information. */
struct __ATTR_PACKED exception_data /*[PREFIX(e_)]*/ {
	union __ATTR_PACKED {
		error_code_t          e_code;   /* Exception code. */
		struct __ATTR_PACKED {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			error_class_t     e_class;    /* Current exception class. */
			error_subclass_t  e_subclass; /* Current exception sub-class. */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
			error_subclass_t  e_subclass; /* Current exception sub-class. */
			error_class_t     e_class;    /* Current exception class. */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
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
	__UINTPTR_TYPE__      e_pointers[EXCEPTION_DATA_POINTERS];
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

#endif /* !_KOS_BITS_EXCEPTION_DATA_H */
