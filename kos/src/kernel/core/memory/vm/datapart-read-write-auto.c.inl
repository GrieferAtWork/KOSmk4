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
#ifdef __INTELLISENSE__
#include "datapart-read-write.c"
//#define DEFINE_IO_READ 1
#define DEFINE_IO_WRITE 1
#endif

#include <stdint.h> /* SIZE_MAX */

DECL_BEGIN

#if (defined(DEFINE_IO_READ) + defined(DEFINE_IO_WRITE)) != 1
#error "Must #define exactly one of (DEFINE_IO_READ, DEFINE_IO_WRITE)"
#endif

#ifdef DEFINE_IO_READ
#define IFELSE_RW(r, w) r
#elif defined(DEFINE_IO_WRITE)
#define IFELSE_RW(r, w) w
#endif


/* Read/write data to/from the given data part.
 * NOTE: When given a virtual memory buffer, these functions automatically
 *       check if the memory backing that buffer could potentially overlap
 *       with `self', in which case reading is performed using an intermediate
 *       buffer, so-as to prevent a possible dead-lock when `self' is already
 *       locked, whilst a #PF caused by writing to the target buffer attempts
 *       to acquire another lock to `self'
 * NOTE: The caller must _NOT_ be holding any lock to `self', the associated
 *       block, or any VM-tree when calling this function.
 * @param: split_bytes: The number of bytes after which to split the part in
 *                      order to minimize the memory impact of copy-on-write.
 *                      Usually the same as `num_bytes'
 * @return: * : The number of read/written bytes (limited by `num_bytes',
 *              and `vm_datapart_numbytes(self) - (src|dst)_offset'). */
PUBLIC NONNULL((1)) size_t KCALL
#ifdef DEFINE_IO_READ
vm_datapart_read(struct vm_datapart *__restrict self,
                 USER CHECKED void *buf /*dst*/,
                 size_t num_bytes,
                 size_t part_offset /*src_offset*/)
#elif defined(DEFINE_IO_WRITE)
vm_datapart_write(struct vm_datapart *__restrict self,
                  USER CHECKED void const *buf /*src*/,
                  size_t num_bytes,
                  size_t split_bytes,
                  size_t part_offset /*dst_offset*/)
#endif
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...)
{
	size_t result;
	ssize_t transfer_status;
	/* Check for the _extremely_ _unlikely_ case of a transfer so
	 * large that it would cause an overflow if done in a single pass.
	 * This is required because `vm_datapart_(read|write)_nopf()' must
	 * not be called with buffer sizes that are larger than a SSIZE_MAX */
	if unlikely(num_bytes > SSIZE_MAX) {
		size_t large_result;
		large_result = IFELSE_RW(vm_datapart_read(self, buf, (size_t)SSIZE_MAX, part_offset),
		                         vm_datapart_write(self, buf, (size_t)SSIZE_MAX, split_bytes, part_offset));
		assert(large_result <= (size_t)SSIZE_MAX);
		if (large_result == (size_t)SSIZE_MAX) {
			/* Transfer the remainder.
			 * We know that 2 steps are always sufficient to handle
			 * this, because of the following static assertion: */
			STATIC_ASSERT((SIZE_MAX / 2) <= (size_t)SSIZE_MAX);
#ifdef DEFINE_IO_WRITE
			if (OVERFLOW_USUB(split_bytes, (size_t)SSIZE_MAX, &split_bytes))
				split_bytes = 0;
#endif /* DEFINE_IO_WRITE */
			large_result += IFELSE_RW(vm_datapart_read(self,
			                                           (byte_t *)buf + (size_t)SSIZE_MAX,
			                                           num_bytes - (size_t)SSIZE_MAX,
			                                           part_offset + (size_t)SSIZE_MAX),
			                          vm_datapart_write(self,
			                                            (byte_t const *)buf + (size_t)SSIZE_MAX,
			                                            num_bytes - (size_t)SSIZE_MAX,
			                                            split_bytes,
			                                            part_offset + (size_t)SSIZE_MAX));
		}
		return large_result;
	}
	/* Try to perform direct I/O by default, thus optimizing for
	 * the likely case where the entire transfer can be performed
	 * in one go. */
	transfer_status = IFELSE_RW(vm_datapart_read_nopf(self, buf, num_bytes, part_offset),
	                            vm_datapart_write_nopf(self, buf, num_bytes, split_bytes, part_offset));
	/* Check for simple case: Everything could be transferred without any problems. */
	if (transfer_status >= 0)
		return (size_t)transfer_status;
	/* This is where it gets a bit complicated.
	 * At this point we've already transferred:
	 *    - A total of `num_bytes - ((size_t)-transfer_status)' bytes
	 *    - from the memory range `dst ... dst + (num_bytes - ((size_t)-transfer_status)) - 1'
	 * And the remaining memory must either be pre-faulted, or transferred using buffered I/O */
	assert(num_bytes != 0);
	assert((size_t)-transfer_status <= num_bytes);
	result = num_bytes - ((size_t)-transfer_status);
	buf = (byte_t *)buf + result;
	num_bytes -= result;
	part_offset += result;
#ifdef DEFINE_IO_WRITE
	if (OVERFLOW_USUB(split_bytes, result, &split_bytes))
		split_bytes = 0;
#endif /* DEFINE_IO_WRITE */
	for (;;) {
		size_t bio_mincount, transfer_ok;
		/* Make use of `vm_prefault()' to get a hint as to how many bytes need
		 * to be transferred through use of buffered I/O, thus allowing us to
		 * achieve much better throughput for user-space ranges that weren't fully
		 * faulted when we got here originally, as well as allow for much better
		 * handling of the case where the user-space buffer is implemented as a VIO
		 * memory mapping. */
		bio_mincount = vm_prefault(buf, num_bytes, IFELSE_RW(false, true));
		assert(bio_mincount < num_bytes);
		if (bio_mincount != 0) {
			/* Perform buffered I/O for `buf...+=bio_mincount' */
			transfer_ok = IFELSE_RW(vm_datapart_read_buffered(self, buf, num_bytes, part_offset),
			                        vm_datapart_write_buffered(self, buf, num_bytes, split_bytes, part_offset));
			result += transfer_ok;
			if (transfer_ok <= bio_mincount)
				break; /* EOF has been reached, or all requested data was transferred. */
			buf = (byte_t *)buf + transfer_ok;
			num_bytes -= transfer_ok;
			part_offset += transfer_ok;
#ifdef DEFINE_IO_WRITE
			if (OVERFLOW_USUB(split_bytes, transfer_ok, &split_bytes))
				split_bytes = 0;
#endif /* DEFINE_IO_WRITE */
			/* Fall through to try to use direct I/O for memory past the range for
			 * which `vm_prefault()' indicated that we should use bufferred I/O. */
		}
		transfer_status = IFELSE_RW(vm_datapart_read_nopf(self, buf, num_bytes, part_offset),
		                            vm_datapart_write_nopf(self, buf, num_bytes, split_bytes, part_offset));
		if (transfer_status >= 0) {
			/* Success! All remaining data could be transferred using direct I/O, or
			 *          there was no more remaining data (in which case `num_bytes == 0')
			 *          Alternatively, we may get here when no more data can be transferred
			 *          to/from the given data part at `part_offset', which is the case when
			 *          `part_offset >= vm_datapart_numbytes(self)' */
			result += transfer_status;
			break;
		}
		/* Figure out how many bytes (if any at all) were transferred by use of direct I/O */
		assert((size_t)-transfer_status <= num_bytes);
		transfer_ok = num_bytes - (size_t)-transfer_status;
#ifndef __OPTIMIZE_SIZE__
		if (transfer_ok != 0)
#endif /* !__OPTIMIZE_SIZE__ */
		{
			result += transfer_ok;
			buf = (byte_t *)buf + transfer_ok;
			num_bytes -= transfer_ok;
			part_offset += transfer_ok;
#ifdef DEFINE_IO_WRITE
			if (OVERFLOW_USUB(split_bytes, transfer_ok, &split_bytes))
				split_bytes = 0;
#endif /* DEFINE_IO_WRITE */
		}
	}
	return result;
}

DECL_END

#undef IFELSE_RW
#undef DEFINE_IO_READ
#undef DEFINE_IO_WRITE
