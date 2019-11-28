/* HASH CRC-32:0x2c73b0a3 */
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
#ifndef __local_feenableexcept_defined
#define __local_feenableexcept_defined 1
#include <bits/fenv-inline.h>
__NAMESPACE_LOCAL_BEGIN
/* Enable individual exceptions.  Will not enable more exceptions than
 * EXCEPTS specifies.  Returns the previous enabled exceptions if all
 * exceptions are successfully set, otherwise returns -1 */
__LOCAL_LIBC(feenableexcept) int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(feenableexcept))(int __excepts) {
#line 184 "kos/src/libc/magic/fenv.c"
	return __inline_feenableexcept(__excepts);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_feenableexcept_defined */
