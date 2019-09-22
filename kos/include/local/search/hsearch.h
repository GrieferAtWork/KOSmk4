/* HASH CRC-32:0x7d56ae52 */
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
#ifndef __local_hsearch_defined
#if 1
#define __local_hsearch_defined 1
#ifndef __hsearch_data_defined
#define __hsearch_data_defined 1
struct _ENTRY;
struct hsearch_data {
	struct _ENTRY *table;
	unsigned int     size;
	unsigned int     filled;
};
#endif /* !__hsearch_data_defined */
/* Dependency: "hsearch_r" from "search" */
#ifndef ____localdep_hsearch_r_defined
#define ____localdep_hsearch_r_defined 1
#if defined(__CRT_HAVE_hsearch_r)
/* Reentrant versions which can handle multiple hashing tables at the same time */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_hsearch_r,(ENTRY __item, ACTION __action, ENTRY **__retval, struct hsearch_data *__htab),hsearch_r,(__item,__action,__retval,__htab))
#else /* LIBC: hsearch_r */
#include <local/search/hsearch_r.h>
/* Reentrant versions which can handle multiple hashing tables at the same time */
#define __localdep_hsearch_r (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hsearch_r))
#endif /* hsearch_r... */
#endif /* !____localdep_hsearch_r_defined */

__NAMESPACE_LOCAL_BEGIN
#ifndef __local_htab_defined
#define __local_htab_defined 1
__LOCAL_LIBC_DATA(__htab) struct hsearch_data __htab = {__NULLPTR, 0, 0};
#endif /* !__local_htab_defined */
/* Search for entry matching ITEM.key in internal hash table.
 * If ACTION is `FIND' return found entry or signal error by returning NULL.
 * If ACTION is `ENTER' replace existing data (if any) with ITEM.data */
__LOCAL_LIBC(hsearch) ENTRY *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(hsearch))(ENTRY __item,
                                                     ACTION __action) {
#line 187 "kos/src/libc/magic/search.c"
	ENTRY *__result;
	__localdep_hsearch_r(__item, __action, &__result, &__htab);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* 1 */
#endif /* !__local_hsearch_defined */
