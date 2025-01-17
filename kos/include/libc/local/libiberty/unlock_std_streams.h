/* HASH CRC-32:0x8cec231a */
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
#ifndef __local_unlock_std_streams_defined
#define __local_unlock_std_streams_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_unlock_stream_defined
#define __local___localdep_unlock_stream_defined
#ifdef __CRT_HAVE_unlock_stream
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_unlock_stream,(__FILE *__fp),unlock_stream,(__fp))
#else /* __CRT_HAVE_unlock_stream */
__NAMESPACE_LOCAL_END
#include <libc/local/libiberty/unlock_stream.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unlock_stream __LIBC_LOCAL_NAME(unlock_stream)
#endif /* !__CRT_HAVE_unlock_stream */
#endif /* !__local___localdep_unlock_stream_defined */
__NAMESPACE_LOCAL_END
#include <libc/template/stdstreams.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(unlock_std_streams) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unlock_std_streams))(void) {
#ifdef __LOCAL_stdin
	(__NAMESPACE_LOCAL_SYM __localdep_unlock_stream)(__LOCAL_stdin);
#endif /* __LOCAL_stdin */
#ifdef __LOCAL_stdout
	(__NAMESPACE_LOCAL_SYM __localdep_unlock_stream)(__LOCAL_stdout);
#endif /* __LOCAL_stdout */
#ifdef __LOCAL_stderr
	(__NAMESPACE_LOCAL_SYM __localdep_unlock_stream)(__LOCAL_stderr);
#endif /* __LOCAL_stderr */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_unlock_std_streams_defined
#define __local___localdep_unlock_std_streams_defined
#define __localdep_unlock_std_streams __LIBC_LOCAL_NAME(unlock_std_streams)
#endif /* !__local___localdep_unlock_std_streams_defined */
#endif /* !__local_unlock_std_streams_defined */
