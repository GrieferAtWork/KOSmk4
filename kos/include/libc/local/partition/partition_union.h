/* HASH CRC-32:0x6d4e5ffc */
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
#ifndef __local_partition_union_defined
#define __local_partition_union_defined
#include <__crt.h>
#include <features.h>
#include <bits/crt/partition.h>
#include <hybrid/__assert.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(partition_union) __ATTR_NONNULL((1)) __STDC_INT_AS_UINT_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(partition_union))(struct partition_def *__self, __STDC_INT_AS_UINT_T __a, __STDC_INT_AS_UINT_T __b) {
	struct partition_elem *__a_elem, *__b_elem, *__iter;
	__hybrid_assert((unsigned int)__a < (unsigned int)__self->num_elements);
	__hybrid_assert((unsigned int)__b < (unsigned int)__self->num_elements);

	/* Normalize to always reference the canonical element */
	__a_elem = &__self->elements[(unsigned int)__a];
	__b_elem = &__self->elements[(unsigned int)__b];
	__a      = __a_elem->class_element;
	__b      = __b_elem->class_element;
	__a_elem = &__self->elements[(unsigned int)__a];
	__b_elem = &__self->elements[(unsigned int)__b];

	/* Check for special case: already the same class. */
	if (__a == __b)
		return __a; /* Nothing to do here! */

	/* We  want  `a' to  be the  larger  class, so  when we
	 * update elements of `b', we have to do less updating! */
	if (__a_elem->class_count < __b_elem->class_count) {
		struct partition_elem *__temp;
		__temp   = __a_elem;
		__a_elem = __b_elem;
		__b_elem = __temp;
		__a = __a_elem->class_element;
		/*b = b_elem->@class_element@;*/ /* Unused... */
	}

	/* Account for the now larger number of elements. */
	__a_elem->class_count += __b_elem->class_count;

	/* Update `class_element' of every member of `b_elem' */
	__iter = __b_elem;
	do {
		__hybrid_assert(__iter->class_element == __b);
		__iter->class_element = __a;
		__iter = __iter->next;
	} while (__iter != __b_elem);

	/* Merge the `b_elem'-ring with the one of `a_elem' */
	{
		struct partition_elem *__temp;
		__temp           = __b_elem->next;
		__b_elem->next = __a_elem->next;
		__a_elem->next = __temp;
	}

	return __a;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_partition_union_defined
#define __local___localdep_partition_union_defined
#define __localdep_partition_union __LIBC_LOCAL_NAME(partition_union)
#endif /* !__local___localdep_partition_union_defined */
#endif /* !__local_partition_union_defined */
