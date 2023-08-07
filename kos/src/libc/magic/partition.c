/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: EMX kLIBC (/libc/include/partition.h) */
/* (#) Portability: libiberty (/include/partition.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.libiberty")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/crt/partition.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

typedef struct partition_def *partition;

#ifndef __FILE_defined
#define __FILE_defined
typedef __FILE FILE;
#endif /* !__FILE_defined */

/*
 * Example usage:
 *
 * >> partition part = partition_new(42);
 * >> assert(partition_find(part, 10) == 10);
 * >> assert(partition_find(part, 20) == 20);
 * >> assert(partition_find(part, 30) == 30);
 * >> partition_union(part, 10, 20);
 * >> partition_union(part, 10, 30);
 * >> assert(partition_find(part, 10) == partition_find(part, 20));
 * >> assert(partition_find(part, 10) == partition_find(part, 30));
 */

}

%[define_decl_include([
	"struct partition_elem",
	"struct partition_def",
] = "<bits/crt/partition.h>")]


@@>> partition_new(3)
@@Create a new partition for `num_elements' elements.
@@ - Uses `xmalloc(3)', so never returns `NULL'!
[[nonnull, decl_include("<features.h>", "<bits/crt/partition.h>")]]
[[requires_function(xmalloc)]]
[[impl_include("<bits/crt/partition.h>")]]
struct partition_def *partition_new(__STDC_INT_AS_UINT_T num_elements) {
	unsigned int i;
	struct partition_def *result;
	result = (struct partition_def *)xmalloc(offsetof(struct partition_def, @elements@) +
	                                         ((unsigned int)num_elements *
	                                          sizeof(struct partition_elem)));
	result->@num_elements@ = num_elements;
	for (i = 0; i < (unsigned int)num_elements; ++i) {
		struct partition_elem *elem = &result->@elements@[i];
		elem->@next@          = elem;
		elem->@class_element@ = (__STDC_INT_AS_UINT_T)i;
		elem->@class_count@   = 1;
	}
	return result;
}

@@>> partition_delete(3)
@@Destroy a given partition
[[decl_include("<bits/crt/partition.h>")]]
[[requires_function(free)]]
[[impl_include("<bits/crt/partition.h>")]]
void partition_delete([[nullable]] struct partition_def *self) {
	free(self);
}

@@>> partition_union(3)
@@Join the classes containing elements `a' and `b' into the same class
@@For  this, choose one  of the class's canonical  elements as the new
@@canonical element of the total  class, which is then also  returned.
[[decl_include("<features.h>", "<bits/crt/partition.h>")]]
[[impl_include("<bits/crt/partition.h>")]]
[[impl_include("<hybrid/__assert.h>")]]
__STDC_INT_AS_UINT_T partition_union([[inout]] struct partition_def *self,
                                     __STDC_INT_AS_UINT_T a,
                                     __STDC_INT_AS_UINT_T b) {
	struct partition_elem *a_elem, *b_elem, *iter;
	__hybrid_assert((unsigned int)a < (unsigned int)self->@num_elements@);
	__hybrid_assert((unsigned int)b < (unsigned int)self->@num_elements@);

	/* Normalize to always reference the canonical element */
	a_elem = &self->@elements@[(unsigned int)a];
	b_elem = &self->@elements@[(unsigned int)b];
	a      = a_elem->@class_element@;
	b      = b_elem->@class_element@;
	a_elem = &self->@elements@[(unsigned int)a];
	b_elem = &self->@elements@[(unsigned int)b];

	/* Check for special case: already the same class. */
	if (a == b)
		return a; /* Nothing to do here! */

	/* We  want  `a' to  be the  larger  class, so  when we
	 * update elements of `b', we have to do less updating! */
	if (a_elem->@class_count@ < b_elem->@class_count@) {
		struct partition_elem *temp;
		temp   = a_elem;
		a_elem = b_elem;
		b_elem = temp;
		a = a_elem->@class_element@;
		/*b = b_elem->@class_element@;*/ /* Unused... */
	}

	/* Account for the now larger number of elements. */
	a_elem->@class_count@ += b_elem->@class_count@;

	/* Update `class_element' of every member of `b_elem' */
	iter = b_elem;
	do {
		__hybrid_assert(iter->@class_element@ == b);
		iter->@class_element@ = a;
		iter = iter->@next@;
	} while (iter != b_elem);

	/* Merge the `b_elem'-ring with the one of `a_elem' */
	{
		struct partition_elem *temp;
		temp           = b_elem->@next@;
		b_elem->@next@ = a_elem->@next@;
		a_elem->@next@ = temp;
	}

	return a;
}



@@>> partition_print(3)
@@Print classes (and  their elements) of  `self' to  `fp'
@@The format used is: '[' ['(' [0 1 2 3 4]... ')']... ']'
@@Example: "[(0 1 2 4 8)(3 6)(5 7)]"
[[cp_stdio, decl_include("<bits/crt/partition.h>")]]
[[impl_include("<bits/crt/partition.h>")]]
[[requires_function(fprintf, fputc)]]
void partition_print([[in]] struct partition_def __KOS_FIXED_CONST *self,
                     [[inout]] FILE *fp) {
	unsigned int i;
	fputc('[', fp);
	for (i = 0; i < (unsigned int)self->@num_elements@; ++i) {
		struct partition_elem const *elem = &self->@elements@[i];
		struct partition_elem const *iter;
		unsigned int prev_index;

		/* Check if the class of `elem' contains any element < i.
		 * -> If so, then we've already printed this class. */
		iter = elem->@next@;
		while (iter != elem) {
			if ((unsigned int)(iter - self->@elements@) < i)
				goto already_printed;
			iter = iter->@next@;
		}

		/* At this point we know that `i' is the smallest
		 * member  of whatever class it belongs to. Since
		 * we need to print sorted, we can start with `i' */
		fprintf(fp, "(%u", i);
		prev_index = i;
		for (;;) {
			unsigned int winner_index;
			struct partition_elem const *winner;
			winner_index = (unsigned int)-1;
			winner       = NULL;
			/* Check if the class contains an element `> prev_index && < winner_index' */
			iter = elem->@next@;
			for (;;) {
				unsigned int iter_index;
				if (iter == elem)
					break;
				iter_index = (unsigned int)(iter - self->@elements@);
				if (iter_index > prev_index && iter_index < winner_index) {
					winner       = iter;
					winner_index = iter_index;
				}
				iter = iter->@next@;
			}
			if (!winner)
				break; /* Last element was printed. */
			fprintf(fp, " %u", winner_index);
			prev_index = winner_index;
		}
		fputc(')', fp);
already_printed:
		;
	}
	fputc(']', fp);
}


%{

/* Return the canonical element for the class containing `element' */
#define partition_find(self, element) \
	((self)->elements[element].class_element)

__SYSDECL_END
#endif /* __CC__ */

}
