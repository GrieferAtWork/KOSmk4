/* HASH CRC-32:0x1464a071 */
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
#ifndef GUARD_LIBC_AUTO_PARTITION_C
#define GUARD_LIBC_AUTO_PARTITION_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "partition.h"
#include "../user/libiberty.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <bits/crt/partition.h>
/* >> partition_new(3)
 * Create a new partition for `num_elements' elements.
 *  - Uses `xmalloc(3)', so never returns `NULL'! */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_RETNONNULL struct partition_def *
NOTHROW_NCX(LIBCCALL libc_partition_new)(__STDC_INT_AS_UINT_T num_elements) {
	unsigned int i;
	struct partition_def *result;
	result = (struct partition_def *)libc_xmalloc(offsetof(struct partition_def, elements) +
	                                         ((unsigned int)num_elements *
	                                          sizeof(struct partition_elem)));
	result->num_elements = num_elements;
	for (i = 0; i < (unsigned int)num_elements; ++i) {
		struct partition_elem *elem = &result->elements[i];
		elem->next          = elem;
		elem->class_element = (__STDC_INT_AS_UINT_T)i;
		elem->class_count   = 1;
	}
	return result;
}
#include <bits/crt/partition.h>
/* >> partition_delete(3)
 * Destroy a given partition */
INTERN ATTR_SECTION(".text.crt.libiberty") void
NOTHROW_NCX(LIBCCALL libc_partition_delete)(struct partition_def *self) {
	libc_free(self);
}
#include <bits/crt/partition.h>
#include <hybrid/__assert.h>
/* >> partition_union(3)
 * Join the classes containing elements `a' and `b' into the same class
 * For  this, choose one  of the class's canonical  elements as the new
 * canonical element of the total  class, which is then also  returned. */
INTERN ATTR_SECTION(".text.crt.libiberty") NONNULL((1)) __STDC_INT_AS_UINT_T
NOTHROW_NCX(LIBCCALL libc_partition_union)(struct partition_def *self,
                                           __STDC_INT_AS_UINT_T a,
                                           __STDC_INT_AS_UINT_T b) {
	struct partition_elem *a_elem, *b_elem, *iter;
	__hybrid_assert((unsigned int)a < (unsigned int)self->num_elements);
	__hybrid_assert((unsigned int)b < (unsigned int)self->num_elements);

	/* Normalize to always reference the canonical element */
	a_elem = &self->elements[(unsigned int)a];
	b_elem = &self->elements[(unsigned int)b];
	a      = a_elem->class_element;
	b      = b_elem->class_element;
	a_elem = &self->elements[(unsigned int)a];
	b_elem = &self->elements[(unsigned int)b];

	/* Check for special case: already the same class. */
	if (a == b)
		return a; /* Nothing to do here! */

	/* We  want  `a' to  be the  larger  class, so  when we
	 * update elements of `b', we have to do less updating! */
	if (a_elem->class_count < b_elem->class_count) {
		struct partition_elem *temp;
		temp   = a_elem;
		a_elem = b_elem;
		b_elem = temp;
		a = a_elem->class_element;
		/*b = b_elem->@class_element@;*/ /* Unused... */
	}

	/* Account for the now larger number of elements. */
	a_elem->class_count += b_elem->class_count;

	/* Update `class_element' of every member of `b_elem' */
	iter = b_elem;
	do {
		__hybrid_assert(iter->class_element == b);
		iter->class_element = a;
		iter = iter->next;
	} while (iter != b_elem);

	/* Merge the `b_elem'-ring with the one of `a_elem' */
	{
		struct partition_elem *temp;
		temp           = b_elem->next;
		b_elem->next = a_elem->next;
		a_elem->next = temp;
	}

	return a;
}
#include <bits/crt/partition.h>
/* >> partition_print(3)
 * Print classes (and  their elements) of  `self' to  `fp'
 * The format used is: '[' ['(' [0 1 2 3 4]... ')']... ']'
 * Example: "[(0 1 2 4 8)(3 6)(5 7)]" */
INTERN ATTR_SECTION(".text.crt.libiberty") ATTR_ACCESS_RW(2) NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc_partition_print)(struct partition_def __KOS_FIXED_CONST *self,
                                           FILE *fp) {
	unsigned int i;
	libc_fputc('[', fp);
	for (i = 0; i < (unsigned int)self->num_elements; ++i) {
		struct partition_elem const *elem = &self->elements[i];
		struct partition_elem const *iter;
		unsigned int prev_index;

		/* Check if the class of `elem' contains any element < i.
		 * -> If so, then we've already printed this class. */
		iter = elem->next;
		while (iter != elem) {
			if ((unsigned int)(iter - self->elements) < i)
				goto already_printed;
			iter = iter->next;
		}

		/* At this point we know that `i' is the smallest
		 * member  of whatever class it belongs to. Since
		 * we need to print sorted, we can start with `i' */
		libc_fprintf(fp, "(%u", i);
		prev_index = i;
		for (;;) {
			unsigned int winner_index;
			struct partition_elem const *winner;
			winner_index = (unsigned int)-1;
			winner       = NULL;
			/* Check if the class contains an element `> prev_index && < winner_index' */
			iter = elem->next;
			for (;;) {
				unsigned int iter_index;
				if (iter == elem)
					break;
				iter_index = (unsigned int)(iter - self->elements);
				if (iter_index > prev_index && iter_index < winner_index) {
					winner       = iter;
					winner_index = iter_index;
				}
				iter = iter->next;
			}
			if (!winner)
				break; /* Last element was printed. */
			libc_fprintf(fp, " %u", winner_index);
			prev_index = winner_index;
		}
		libc_fputc(')', fp);
already_printed:
		;
	}
	libc_fputc(']', fp);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(partition_new, libc_partition_new);
DEFINE_PUBLIC_ALIAS(partition_delete, libc_partition_delete);
DEFINE_PUBLIC_ALIAS(partition_union, libc_partition_union);
DEFINE_PUBLIC_ALIAS(partition_print, libc_partition_print);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PARTITION_C */
