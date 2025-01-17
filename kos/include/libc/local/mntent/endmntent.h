/* HASH CRC-32:0x54cc4fd7 */
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
#ifndef __local_endmntent_defined
#define __local_endmntent_defined
#include <__crt.h>
#if defined(__CRT_HAVE_fclose) || defined(__CRT_HAVE__fclose_nolock) || defined(__CRT_HAVE__IO_fclose)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fclose_defined
#define __local___localdep_fclose_defined
#ifdef __CRT_HAVE_fclose
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fclose,(__FILE *__restrict __stream),fclose,(__stream))
#elif defined(__CRT_HAVE__fclose_nolock)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fclose,(__FILE *__restrict __stream),_fclose_nolock,(__stream))
#elif defined(__CRT_HAVE__IO_fclose)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fclose,(__FILE *__restrict __stream),_IO_fclose,(__stream))
#else /* ... */
#undef __local___localdep_fclose_defined
#endif /* !... */
#endif /* !__local___localdep_fclose_defined */
__LOCAL_LIBC(endmntent) __ATTR_INOUT(1) int
__NOTHROW_RPC_NOKOS(__LIBCCALL __LIBC_LOCAL_NAME(endmntent))(__FILE *__stream) {
	(__NAMESPACE_LOCAL_SYM __localdep_fclose)(__stream);
	return 1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_endmntent_defined
#define __local___localdep_endmntent_defined
#define __localdep_endmntent __LIBC_LOCAL_NAME(endmntent)
#endif /* !__local___localdep_endmntent_defined */
#else /* __CRT_HAVE_fclose || __CRT_HAVE__fclose_nolock || __CRT_HAVE__IO_fclose */
#undef __local_endmntent_defined
#endif /* !__CRT_HAVE_fclose && !__CRT_HAVE__fclose_nolock && !__CRT_HAVE__IO_fclose */
#endif /* !__local_endmntent_defined */
