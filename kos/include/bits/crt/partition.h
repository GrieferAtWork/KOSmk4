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
#ifndef _BITS_CRT_PARTITION_H
#define _BITS_CRT_PARTITION_H 1

#include <__crt.h>
#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

struct partition_elem {
	struct partition_elem *next;          /* [1..1] Next element also part of this partition (forms a circle) */
	__STDC_INT_AS_UINT_T   class_element; /* [== next->class_element] "canonical" partition element */
	unsigned int           class_count;   /* [valid_if(this == :elements[class_element])] # of elements in this class */
};

struct partition_def {
	__STDC_INT_AS_UINT_T                             num_elements; /* [const] Total number of elements. */
	__COMPILER_FLEXIBLE_ARRAY(struct partition_elem, elements);    /* [num_elements] Partition elements. */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_PARTITION_H */
