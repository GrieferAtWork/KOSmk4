/* HASH CRC-32:0xa1c8ddf8 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_rtm_test_defined
#define __local_rtm_test_defined 1
#include <__crt.h>
#include <kos/bits/rtm.h>
#ifdef __arch_rtm_test
__NAMESPACE_LOCAL_BEGIN
/* >> rtm_test(2)
 * Check if a transaction is currently in progress
 * @return: 0 : No RTM operation in progress
 * @return: 1 : An RTM operation is currently in progress */
__LOCAL_LIBC(rtm_test) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(rtm_test))(void) {
	return __arch_rtm_test();
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_rtm_test_defined
#define __local___localdep_rtm_test_defined 1
#define __localdep_rtm_test __LIBC_LOCAL_NAME(rtm_test)
#endif /* !__local___localdep_rtm_test_defined */
#else /* __arch_rtm_test */
#undef __local_rtm_test_defined
#endif /* !__arch_rtm_test */
#endif /* !__local_rtm_test_defined */
