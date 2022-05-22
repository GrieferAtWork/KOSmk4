/* HASH CRC-32:0x8f5ba96b */
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
#ifndef __local_countargv_defined
#define __local_countargv_defined
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(countargv) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN_OPT(1) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(countargv))(char *const *___argv) {
	__STDC_INT_AS_SIZE_T __result = 0;
	if (___argv != __NULLPTR) {
		for (; ___argv[__result]; ++__result)
			;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_countargv_defined
#define __local___localdep_countargv_defined
#define __localdep_countargv __LIBC_LOCAL_NAME(countargv)
#endif /* !__local___localdep_countargv_defined */
#endif /* !__local_countargv_defined */
