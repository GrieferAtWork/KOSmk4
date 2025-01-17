/* HASH CRC-32:0x5fa9918f */
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
#ifndef __local_hdestroy_defined
#define __local_hdestroy_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_hdestroy_r_defined
#define __local___localdep_hdestroy_r_defined
#ifdef __CRT_HAVE_hdestroy_r
__NAMESPACE_LOCAL_END
struct hsearch_data;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_hdestroy_r,(struct hsearch_data *__htab),hdestroy_r,(__htab))
#else /* __CRT_HAVE_hdestroy_r */
__NAMESPACE_LOCAL_END
#include <libc/local/search/hdestroy_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_hdestroy_r __LIBC_LOCAL_NAME(hdestroy_r)
#endif /* !__CRT_HAVE_hdestroy_r */
#endif /* !__local___localdep_hdestroy_r_defined */
__NAMESPACE_LOCAL_END
#ifndef __hsearch_data_defined
#define __hsearch_data_defined
struct _ENTRY;
struct hsearch_data {
	struct _ENTRY  *table;
	__UINT32_TYPE__ size;
	__UINT32_TYPE__ filled;
};
#endif /* !__hsearch_data_defined */
#ifndef __local_htab_defined
#define __local_htab_defined
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__htab) struct hsearch_data __htab = { __NULLPTR, 0, 0 };
__NAMESPACE_LOCAL_END
#endif /* !__local_htab_defined */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(hdestroy) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(hdestroy))(void) {
	(__NAMESPACE_LOCAL_SYM __localdep_hdestroy_r)(&__NAMESPACE_LOCAL_SYM __htab);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_hdestroy_defined
#define __local___localdep_hdestroy_defined
#define __localdep_hdestroy __LIBC_LOCAL_NAME(hdestroy)
#endif /* !__local___localdep_hdestroy_defined */
#endif /* !__local_hdestroy_defined */
