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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_PREFAULT_C
#define GUARD_KERNEL_SRC_MEMORY_VM_PREFAULT_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/panic.h>
#include <kernel/vm.h>

#include <hybrid/align.h>

#include <assert.h>

DECL_BEGIN

/* Try to prefault memory for the given address range within the current VM.
 * This function is intended to be used in conjunction with `memcpy_nopf()',
 * as well as functions using it in order to speed up the lock-copy-unlock-do_buffered_io-repeat
 * cycle by potentially allowing the caller to skip having to perform buffered I/O
 * in cases where the backing memory can be made to be backed by real, physical memory,
 * as opposed to not being mapped at all, or being mapped by VIO memory.
 * NOTE: This function should only be used as a hint for figuring out how buffered I/O should
 *       be performed in face of a memory range that cannot be accessed by `memcpy_nopf()'.
 *       In practice, this means that code using it should be aware that as far as the reliable
 *       semantics of this function go, one valid implementation could simply look like this:
 *       >> PUBLIC size_t FCALL
 *       >> vm_prefault(USER CHECKED void const *addr, size_t num_bytes, bool for_writing)
 *       >>         THROWS(E_WOULDBLOCK, E_BADALLOC) {
 *       >>     assert(num_bytes != 0);
 *       >>     (void)addr;
 *       >>     (void)num_bytes;
 *       >>     (void)for_writing;
 *       >>     // Always return 1, indicating a the necessity of performing just a bit of
 *       >>     // buffered I/O, which will automatically fault at least some memory on access,
 *       >>     // as well as handle the case of VIO memory being accessed.
 *       >>     return 1;
 *       >> }
 * NOTE: For a valid usage example of this function, you may look at the implementation of
 *       the `vm_datapart_(read|write)()' function pair, which uses it in order to determine
 *       the number of bytes that must be processed using `vm_datapart_(read|write)_buffered()'
 * @param: for_writing: When true, make sure that memory within the associated gets
 *                      faulted such that copy-on-write operations are carried out.
 *                      Otherwise, only make sure that memory from the given range
 *                      can be read from (though again: even this is only to be taken
 *                      as a hint. - This function is allowed to just do nothing if
 *                      it wants to)
 * @assume(num_bytes != 0);
 * @return: 0 :
 *     At least 1 page of memory (the one containing `addr') was faulted.
 *     In this case, the caller can immediately go back to performing direct I/O,
 *     though the possibility exists that either due to the backing physical memory
 *     for the given address range being swapped out, or this function choosing not
 *     to prefault the given range in its entirety, more transfer errors may still
 *     occur as memory from the given range is accessed using `memcpy_nopf()'.
 *     Another possible reason for more transfer errors could be a VIO, or unmapped
 *     segment of memory starting further into the given range.
 * @return: >= 1 && <= num_bytes:
 *     In this case, the return value indicates the number of bytes that could not
 *     be faulted (either because not being mapped, or due to being mapped to VIO) */
PUBLIC size_t FCALL
vm_prefault(USER CHECKED void const *addr,
            size_t num_bytes, bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	assert(num_bytes != 0);
	/* This function shares some of its code with `vm_read()' / `vm_write()', except that
	 * the contents of memory don't actually get modified.
	 * In practice, try to prefault the entirety of the indicated address range, but stop
	 * at the first gap within the VM where either no mapping exists for some part of the
	 * indicated range, or the part that does exist is a VIO mapping.
	 * If the indicated range starts with...
	 *     ... an unmapped memory segment (i.e. no `vm_node' exists for `addr'), then
	 *         immediately return some non-zero value < num_bytes. (for simplicitly, we
	 *         we can just always return `1', thus forgoing the need of additional
	 *         calculations needing to be done)
	 *     ... a memory segment that is backed by VIO, then return the number of bytes
	 *         within a span starting at `addr', and ending at either the end of the
	 *         indicate ranged, or at the first byte that is either not mapped any more,
	 *         or is no longer part of a memory block backed by VIO, whichever comes first:
	 *      >> return (MIN(addr + num_bytes, END_ADDRESS_OF_LAST_CONSECUTIVE_VIO_MAPPING_STARTING_AT(addr)) - addr);
	 *         Additionally, when `END_ADDRESS_OF_LAST_CONSECUTIVE_VIO_MAPPING_STARTING_AT(addr) > addr + num_bytes',
	 *         recursively call ourself:
	 *         >> void *p = END_ADDRESS_OF_LAST_CONSECUTIVE_VIO_MAPPING_STARTING_AT(addr);
	 *         >> if (p > addr + num_bytes) {
	 *         >>     TRY {
	 *         >>         vm_prefault(p, p - (addr + num_bytes));
	 *         >>     } EXCEPT {
	 *         >>         if (!was_thrown(E_BADALLOC) &&
	 *         >>             !was_thrown(E_WOULDBLOCK))
	 *         >>             RETHROW();
	 *         >>     }
	 *         >> }
	 *         >> return (MIN(addr + num_bytes, p) - addr);;
	 *         Thus allowing the caller to write code that immediately accesses memory
	 *         past a block of data for which buffered I/O is necessary using direct I/O,
	 *         without having to consult `vm_prefault()' yet again.
	 * Otherwise, slowly work through all consecutively mapped `vm_node's, starting with
	 * the node used for backing `addr' itself, and look at each of their data parts.
	 *   - If `addr + num_bytes' is reached, then stop iteration
	 *   - If at any point a gap between two consecutive is found, also stop
	 *   - Otherwise, with respect to `for_writing', as well as `VM_PROT_SHARED',
	 *     and also `VM_PROT_WRITE' when `for_writing' is `true', make use of
	 *     `vm_datapart_lockread_setcore_unsharecow()' and `vm_datapart_lockread_setcore()'
	 *     in order to lock mapped data parts, before potentially updating memory mappings
	 *     within the VM associated with the current address, and finally updating the backing
	 *     page directory mapping. Note that this last part is _mandatory_, since the only
	 *     real requirement for `vm_prefault()' in terms of semantics is:
	 *         When `vm_prefault()' returns `0', it is guarantied that at some point in
	 *         the past, presence, or future, virtual memory located at `addr' has/is/or
	 *         will be backed by true, physical memory.
	 *   - If at least a single byte of memory was already successfully faulted using this
	 *     memory, any `E_BADALLOC' or `E_WOULDBLOCK' exceptions thrown whilst attempting
	 *     to fault additional memory are caught, and will also cause the iteration to stop.
	 *     In practice this simply means:
	 *     >> if (ITER_ADDR == addr)
	 *     >>     RETHROW();
	 *     >> else {
	 *     >>     break;
	 *     >> }
	 *     Where ITER_ADDR is initialized to `addr', and during `continue' is updated to
	 *     instead refer to `vm_node_getend(CURRENT_NODE)'.
	 * Regardless of why iteration stops, always return `0' at this point, indicating that
	 * at least some part of the given range can be accessed using direct I/O.
	 */

	/* TODO: Implement me! :) */
	(void)addr;
	(void)num_bytes;
	(void)for_writing;

	return 1;
}



/* Force all bytes within the given address range to be faulted for either reading
 * or writing. If any page within the specified range isn't mapped, throw an E_SEGFAULT
 * exception. Otherwise, ensure that copy-on-write is invoked when `for_writing' is true,
 * and that irregardless of `for_writing', physical memory is allocated for any mapping
 * that can be made to be backed by RAM.
 * Any VIO mappings within the specified range are simply ignored (and will not count
 * towards the returned value)
 * @return: * : The total number of bytes that become faulted as the resule of this
 *              function being called. Note that even if you may be expecting that some
 *              specified address within the range wasn't faulted before, you must still
 *              allow for this function to return `0', since there always exists a
 *              possibility of some other thread changing the backing mappings, or
 *              faulting the mappings themself.
 *              As such, the return value should only be used for probability optimizations,
 *              as well as profiling, but not for the purpose of actual logic decisions.
 * NOTE: This function will also update the page directory mappings for any dataparts
 *       that get faulted during its invocation, meaning that use of `memcpy_nopf()'
 *       within the indicated address range (whilst still checking it for errors for
 *       the even of the mapping changing, or the mapping being a VIO mapping) becomes
 *       possible immediately, without having to force any soft of additional memory
 *       access (note though that this only applies to the page directory of `self',
 *       though also note that if some datapart within the range was already faulted, its
 *       page directory mapping in `self' will still be updated). */
FUNDEF size_t FCALL
vm_paged_forcefault(struct vm *__restrict self,
                    pageid_t minpageid,
                    pageid_t maxpageid,
                    bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT) {
	assert(minpageid <= maxpageid);
	(void)self;
	(void)minpageid;
	(void)maxpageid;
	(void)for_writing;

	kernel_panic("TODO");

	return 0;
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_PREFAULT_C */
