/* HASH CRC-32:0x3c0f4468 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
#ifndef __local_feraiseexcept_defined
#define __local_feraiseexcept_defined 1
#include <kos/anno.h>
#include <bits/fenv-inline.h>
__NAMESPACE_LOCAL_BEGIN
/* Raise the supported exceptions represented by EXCEPTS */
__LOCAL_LIBC(feraiseexcept) int
(__LIBCCALL __LIBC_LOCAL_NAME(feraiseexcept))(int __excepts) __THROWS(...) {
#line 92 "kos/src/libc/magic/fenv.c"
	__inline_feraiseexcept(__excepts);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_feraiseexcept_defined */
