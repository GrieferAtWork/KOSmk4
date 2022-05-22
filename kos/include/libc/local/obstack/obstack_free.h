/* HASH CRC-32:0x294fcb23 */
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
#ifndef __local_obstack_free_defined
#define __local_obstack_free_defined
#include <__crt.h>
#include <bits/crt/obstack.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memset_defined
#define __local___localdep_memset_defined
#ifdef __CRT_HAVE_memset
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_ACCESS_WRS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),memset,(__dst,__byte,__n_bytes))
#else /* __CRT_HAVE_memset */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memset.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memset __LIBC_LOCAL_NAME(memset)
#endif /* !__CRT_HAVE_memset */
#endif /* !__local___localdep_memset_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/__assert.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(obstack_free) __ATTR_ACCESS_RW(1) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(obstack_free))(struct obstack *__self, void *__obj) {
	struct _obstack_chunk *__iter;
	for (__iter = __self->chunk; __iter;) {
		struct _obstack_chunk *__prev;
		if (__obj >= (void *)__iter && __obj < (void *)__iter->limit)
			break;
		__prev = __iter->prev;
		__obstack_free(__self, __iter);
		__iter = __prev;
		__self->maybe_empty_object = 1;
	}
	if (__iter) {
		__self->object_base = (char *)(__obj);
		__self->next_free   = (char *)(__obj);
		__self->chunk_limit = __iter->limit;
		__self->chunk       = __iter;
	} else {
		/* If `obj == NULL', then it's allowed to not belong to `self' */
		__hybrid_assertf(__obj == __NULLPTR,
		                 "Object %p does not belong to this obstack",
		                 __obj);
#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
		(__NAMESPACE_LOCAL_SYM __localdep_memset)(__self, 0xcc, sizeof(*__self));
#endif /* !NDEBUG && !NDEBUG_FINI */
	}
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_obstack_free_defined
#define __local___localdep_obstack_free_defined
#define __localdep_obstack_free __LIBC_LOCAL_NAME(obstack_free)
#endif /* !__local___localdep_obstack_free_defined */
#endif /* !__local_obstack_free_defined */
