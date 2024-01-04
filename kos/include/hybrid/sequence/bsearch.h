/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID_SEQUENCE_BSEARCH_H
#define __GUARD_HYBRID_SEQUENCE_BSEARCH_H 1

#include "../typecore.h"

/* Same as `BSEARCH()', but given an ascendingly sorted vector of
 * non-overlapping, inclusive ranges `vector[index] field_lo' ...
 * `vector[index] field_hi', find the one that contains `key' */
#define BSEARCH_RANGE(index, vector, count, field_lo, field_hi, key)   \
	for (__SIZE_TYPE__ _bs_lo = 0, _bs_hi = (count); _bs_lo < _bs_hi;) \
		if (((index) = (_bs_lo + _bs_hi) / 2,                          \
		     (key) < (vector)[index] field_lo))                        \
			_bs_hi = (index);                                          \
		else if ((key) > (vector)[index] field_hi)                     \
			_bs_lo = (index) + 1;                                      \
		else if ((_bs_lo = _bs_hi, 0))                                 \
			; /* Found it! (element is in `vector[index]') */          \
		else

/* >> BSEARCH (size_t &index, T vector[], size_t count,
 * >>          UNARY_SUFFIX_EXPR field,
 * >>          typeof(vector[index] field) key) {
 * >>     <SUCC>
 * >> }
 * >> <FAIL>
 *
 * Helper macro for a bsearch()-style search algorithm:
 * >> struct number { int value; };
 * >> ssize_t find_number(struct number num[], size_t count, int v) {
 * >>     size_t i;
 * >>     BSEARCH (i, num, count, .value, v) {
 * >>         return i; // Found it!
 * >>     }
 * >>     return -1; // Not found
 * >> }
 *
 * BSEARCH  is  a  O(log(N))  search  algorithm  for  pre-sorted  arrays,   making
 * it  optimal  in  situations  where   pre-computed  arrays  must  be   searched.
 * This macro behaves the same as the libc function `bsearch(3)' / `bsearch_r(3)',
 * however unlike the libc function, this one doesn't require the use of a compare
 * predicate,  rather allowing you to implement the entire search function in-line
 *
 * Upon success, the statement immediately following this macro will be executed.
 * Upon  failure, that same  statement is skipped as  though pre-fixed by `if(0)'
 *
 * @param: index: [out] The matching vector index (on success; undefined on failure)
 * @param: vector: [in] The vector to-be searched
 * @param: count:  [in] # of elements in `vector'
 * @param: field:       An optional expression to narrow down a specific field of `vector'
 * @param: key:    [in] The key that's supposed to be found. */
#define BSEARCH(index, vector, count, field, key) \
	BSEARCH_RANGE(index, vector, count, field, field, key)


/* Same  as `BSEARCH_RANGE()', but  on failure, the  index where the element
 * should have been placed into is stored in `lo' and `hi' (with `lo == hi') */
#define BSEARCH_RANGE_EX(index, lo, hi, vector, count, field_lo, field_hi, key) \
	for ((lo) = 0, (hi) = (count); (lo) < (hi);)                                \
		if (((index) = ((lo) + (hi)) / 2,                                       \
		     (key) < (vector)[index] field_lo))                                 \
			(hi) = (index);                                                     \
		else if ((key) > (vector)[index] field_hi)                              \
			(lo) = (index) + 1;                                                 \
		else if (((lo) = (hi), 0))                                              \
			; /* Found it! (element is in `vector[index]') */                   \
		else
#define BSEARCH_EX(index, lo, hi, vector, count, field, key) \
	BSEARCH_RANGE_EX (index, lo, hi, vector, count, field, field, key)


#endif /* !__GUARD_HYBRID_SEQUENCE_BSEARCH_H */
