/* HASH CRC-32:0xe413696a */
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
#ifndef __local__get_narrow_winmain_command_line_defined
#define __local__get_narrow_winmain_command_line_defined
#include <__crt.h>
#ifdef __CRT_HAVE___p__acmdln
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___p__acmdln_defined
#define __local___localdep___p__acmdln_defined
__COMPILER_CREDIRECT(__LIBC,,char **,__NOTHROW_NCX,__LIBDCALL,__localdep___p__acmdln,(void),__p__acmdln,())
#endif /* !__local___localdep___p__acmdln_defined */
__LOCAL_LIBC(_get_narrow_winmain_command_line) __ATTR_PURE __ATTR_WUNUSED char *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_get_narrow_winmain_command_line))(void) {
	return *(__NAMESPACE_LOCAL_SYM __localdep___p__acmdln)();
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__get_narrow_winmain_command_line_defined
#define __local___localdep__get_narrow_winmain_command_line_defined
#define __localdep__get_narrow_winmain_command_line __LIBC_LOCAL_NAME(_get_narrow_winmain_command_line)
#endif /* !__local___localdep__get_narrow_winmain_command_line_defined */
#else /* __CRT_HAVE___p__acmdln */
#undef __local__get_narrow_winmain_command_line_defined
#endif /* !__CRT_HAVE___p__acmdln */
#endif /* !__local__get_narrow_winmain_command_line_defined */
