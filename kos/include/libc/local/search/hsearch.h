/* HASH CRC-32:0x696a9fec */
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
#ifndef __local_hsearch_defined
#define __local_hsearch_defined 1
#include <__crt.h>
struct entry;
__NAMESPACE_LOCAL_BEGIN
/* Dependency: hsearch_r from search */
#ifndef __local___localdep_hsearch_r_defined
#define __local___localdep_hsearch_r_defined 1
#ifdef __CRT_HAVE_hsearch_r
__NAMESPACE_LOCAL_END
struct hsearch_data;
__NAMESPACE_LOCAL_BEGIN
/* >> hsearch_r(3)
 * Reentrant versions which can handle multiple hashing tables at the same time */
__CREDIRECT(__ATTR_NONNULL((3, 4)),int,__NOTHROW_NCX,__localdep_hsearch_r,(struct entry __item, int __action, struct entry **__retval, struct hsearch_data *__htab),hsearch_r,(__item,__action,__retval,__htab))
#else /* __CRT_HAVE_hsearch_r */
__NAMESPACE_LOCAL_END
#include <libc/local/search/hsearch_r.h>
__NAMESPACE_LOCAL_BEGIN
/* >> hsearch_r(3)
 * Reentrant versions which can handle multiple hashing tables at the same time */
#define __localdep_hsearch_r __LIBC_LOCAL_NAME(hsearch_r)
#endif /* !__CRT_HAVE_hsearch_r */
#endif /* !__local___localdep_hsearch_r_defined */
__NAMESPACE_LOCAL_END
#ifndef __hsearch_data_defined
#define __hsearch_data_defined 1
struct _ENTRY;
struct hsearch_data {
	struct _ENTRY  *table;
	__UINT32_TYPE__ size;
	__UINT32_TYPE__ filled;
};
#endif /* !__hsearch_data_defined */
#ifndef __local_htab_defined
#define __local_htab_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__htab) struct hsearch_data __htab = { __NULLPTR, 0, 0 };
__NAMESPACE_LOCAL_END
#endif /* !__local_htab_defined */
__NAMESPACE_LOCAL_BEGIN
/* >> hsearch(3)
 * Search for entry matching `item.key' in internal hash table.
 * If `action' is `FIND' return found entry or signal error by returning `NULL'.
 * If `action' is `ENTER' replace existing data (if any) with `item.data' */
__LOCAL_LIBC(hsearch) struct entry *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(hsearch))(struct entry __item, int __action) {
	struct entry *__result;
	__localdep_hsearch_r(__item, __action, &__result, &__NAMESPACE_LOCAL_SYM __htab);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_hsearch_defined
#define __local___localdep_hsearch_defined 1
#define __localdep_hsearch __LIBC_LOCAL_NAME(hsearch)
#endif /* !__local___localdep_hsearch_defined */
#endif /* !__local_hsearch_defined */
