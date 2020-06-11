/* HASH CRC-32:0x84d10b39 */
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_hsearch_r_defined
#define __local_hsearch_r_defined 1
#include <__crt.h>
struct entry;
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strcmp from string */
#ifndef __local___localdep_strcmp_defined
#define __local___localdep_strcmp_defined 1
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,{ return __builtin_strcmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcmp)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,(__s1,__s2))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/strcmp.h>
__NAMESPACE_LOCAL_BEGIN
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
#define __localdep_strcmp __LIBC_LOCAL_NAME(strcmp)
#endif /* !... */
#endif /* !__local___localdep_strcmp_defined */
/* Dependency: strlen from string */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined 1
#ifdef __CRT_HAVE_strlen
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __string),strlen,(__string))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__NAMESPACE_LOCAL_END
#include <parts/errno.h>
#ifndef __hsearch_data_defined
#define __hsearch_data_defined 1
struct _ENTRY;
struct hsearch_data {
	struct _ENTRY  *table;
	__UINT32_TYPE__ size;
	__UINT32_TYPE__ filled;
};
#endif /* !__hsearch_data_defined */
#ifndef __ENTRY_defined
#define __ENTRY_defined 1
typedef struct entry {
	char *key;
	void *data;
} ENTRY;
#endif /* !__ENTRY_defined */
__NAMESPACE_LOCAL_BEGIN
/* Reentrant versions which can handle multiple hashing tables at the same time */
__LOCAL_LIBC(hsearch_r) __ATTR_NONNULL((3, 4)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(hsearch_r))(struct entry __item, int __action, struct entry **__retval, struct hsearch_data *__htab) {
	typedef struct {
		unsigned int __used;
		struct entry        __entry;
	} __entry_type;
	unsigned int __hval, __count, __idx;
	unsigned int __len = __localdep_strlen(__item.key);
	__hval = __count = __len;
	while (__count-- > 0) {
		__hval <<= 4;
		__hval += __item.key[__count];
	}
	if (__hval == 0)
		++__hval;
	__idx = __hval % __htab->size + 1;
	if (((__entry_type *)__htab->table)[__idx].__used) {
		unsigned int __hval2, __first_idx;
		if (((__entry_type *)__htab->table)[__idx].__used == __hval &&
		    __localdep_strcmp(__item.key, ((__entry_type *)__htab->table)[__idx].__entry.key) == 0) {
			*__retval = &((__entry_type *)__htab->table)[__idx].__entry;
			return 1;
		}
		__hval2 = 1 + __hval % (__htab->size - 2);
		__first_idx = __idx;
		do {
			if (__idx <= __hval2)
				__idx = __htab->size + __idx - __hval2;
			else
				__idx -= __hval2;
			if (__idx == __first_idx)
				break;
			if (((__entry_type *)__htab->table)[__idx].__used == __hval &&
			    __localdep_strcmp(__item.key, ((__entry_type *)__htab->table)[__idx].__entry.key) == 0) {
				*__retval = &((__entry_type *)__htab->table)[__idx].__entry;
				return 1;
			}
		} while (((__entry_type *)__htab->table)[__idx].__used);
	}
	if (__action == 1) {
		if (__htab->filled == __htab->size) {
#ifdef ENOMEM
			__libc_seterrno(__ENOMEM);
#endif /* ENOMEM */
			*__retval = __NULLPTR;
			return 0;
		}
		((__entry_type *)__htab->table)[__idx].__used  = __hval;
		((__entry_type *)__htab->table)[__idx].__entry = __item;
		++__htab->filled;
		*__retval = &((__entry_type *)__htab->table)[__idx].__entry;
		return 1;
	}
#ifdef ESRCH
	__libc_seterrno(__ESRCH);
#endif /* ESRCH */
	*__retval = __NULLPTR;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_hsearch_r_defined
#define __local___localdep_hsearch_r_defined 1
#define __localdep_hsearch_r __LIBC_LOCAL_NAME(hsearch_r)
#endif /* !__local___localdep_hsearch_r_defined */
#endif /* !__local_hsearch_r_defined */
