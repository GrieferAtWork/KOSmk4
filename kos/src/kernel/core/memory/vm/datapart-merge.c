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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_DATAPART_MERGE_C
#define GUARD_KERNEL_SRC_MEMORY_VM_DATAPART_MERGE_C 1

#include <kernel/compiler.h>
#include <kernel/vm.h>

DECL_BEGIN

/* Decrement the reference counter of `self', and try to merge it with sibling data parts.
 * This functionality is combined with a decref() since a data part can only be merged when
 * it is only visible from within its own data block, or for any VM mapping, the latter only
 * allowing the part to the merged if _all_ mappings are layed out in a way that has the part
 * be mapped alongside its closest siblings in a continuous memory mapping.
 * Note that a data part will never be merged if it has any outside references which would
 * keep it being visible outside the small region that is controllable by the part itself.
 * These references are: `self->dp_block->db_parts*' (1), `self->dp_crefs*' (n) and `self->dp_srefs*' (n)
 *                        Should references exist beyond those explainable via these pointers, plus
 *                        one additional reference that is gifted to this function by its caller, merging
 *                        will not be done.
 * If merging is impossible for any other reason (blocking locks, insufficient memory, etc.), the
 * operation will stop, and the function behaves identical to a regular `decref(self)' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_decref_and_merge)(REF struct vm_datapart *__restrict self) {
	/* TODO */
	decref(self);
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_DATAPART_MERGE_C */
