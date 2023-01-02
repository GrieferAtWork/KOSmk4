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
#ifndef GUARD_LIBC_LIBC_EXCEPT_PERSONALITY_C
#define GUARD_LIBC_LIBC_EXCEPT_PERSONALITY_C 1

/* Keep this one the first */
#include "../api.h"
/**/

#include "except.h"


DECL_BEGIN

/* NOTE: These functions _have_ to be exported weakly!
 *       Otherwise, they might accidentally override the same functions
 *       exported from `libstdc++.so'
 *       The idea in  exporting these  from libc.so  as well  is that  libc.so
 *       should provide a minimal, self-contained implementation of everything
 *       that is required to get the KOS-specific exception handling  provided
 *       by the <kos/except.h> header working.
 *       Additionally, then  libstdc++.so is  loaded,  we must  remain  compatible
 *       with its API, in that kos exceptions should show up as foreign exceptions
 *       when interfaced with the standard c++ API (which they do) */
DEFINE_PUBLIC_WEAK_ALIAS(__gxx_personality_v0, libc_gxx_personality_v0);
DEFINE_PUBLIC_WEAK_ALIAS(__gcc_personality_v0, libc_gxx_personality_v0);


/* Defined in "libc/except.c" */
INTDEF _Unwind_Reason_Code LIBCCALL
libc_gxx_personality_kernexcept(struct _Unwind_Context *__restrict context, bool phase_2);

INTERN SECTION_EXCEPT_TEXT _Unwind_Reason_Code LIBCCALL
libc_gxx_personality_v0(int version /* = 1 */,
                        _Unwind_Action actions,
                        _Unwind_Exception_Class exception_class,
                        struct _Unwind_Exception *ue_header,
                        struct _Unwind_Context *context) {
	if unlikely(version != 1)
		return _URC_FATAL_PHASE1_ERROR;
	if likely(exception_class == _UEC_KERNKOS)
		return libc_gxx_personality_kernexcept(context, (actions & _UA_FORCE_UNWIND) != 0);
	/* This implementation only support KOS exceptions.
	 * When linking against libstdc++.so, this function gets overridden by its implementation. */
	(void)actions;
	(void)exception_class;
	(void)ue_header;
	(void)context;
	return _URC_FATAL_PHASE1_ERROR;
}

DECL_END

#endif /* !GUARD_LIBC_LIBC_EXCEPT_PERSONALITY_C */
