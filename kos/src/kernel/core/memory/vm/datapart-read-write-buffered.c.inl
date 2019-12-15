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
#ifdef __INTELLISENSE__
#include "datapart-read-write.c"
//#define DEFINE_IO_READ 1
#define DEFINE_IO_WRITE 1
#endif

DECL_BEGIN

#if (defined(DEFINE_IO_READ) + defined(DEFINE_IO_WRITE)) != 1
#error "Must #define exactly one of (DEFINE_IO_READ, DEFINE_IO_WRITE)"
#endif

#ifdef DEFINE_IO_READ
#define IFELSE_RW(r, w) r
#elif defined(DEFINE_IO_WRITE)
#define IFELSE_RW(r, w) w
#endif


#ifndef CONFIG_VM_DATABLOCK_BUFFEREDIO_MAXBUFSIZE
#define CONFIG_VM_DATABLOCK_BUFFEREDIO_MAXBUFSIZE (128 * sizeof(void *))
#endif /* !CONFIG_VM_DATABLOCK_BUFFEREDIO_MAXBUFSIZE */


/* Perform I/O using an intermediate buffer, thus solving the deadlock
 * scenario possible when using `vm_datapart_(read|write)_unsafe', as
 * well as to perform the faulting/vio-interaction needed when a call
 * to `vm_datapart_(read|write)_nopf()' returned a negative value.
 * Even though they can, these functions should _not_ be used to transfer
 * a data part in its entirety, since they rely on a limited-size buffer
 * allocated on the kernel stack, meaning that their use requires the
 * indirection of an intermediate memory location.
 * In general, raw I/O on data parts should always be performed with the
 * help of `vm_datapart_(read|write)()', which will automatically try to
 * call the `*_nopf()' function, and fall back for a limited number of
 * bytes to making use of `vm_datapart_(read|write)_buffered()' for handling
 * VIO, as well as faulting memory mappings. (s.a. `vm_prefault()')
 * @return: * : The number of read/written bytes (limited by `num_bytes',
 *              and `vm_datapart_numbytes(self) - (src|dst)_offset'). */
PUBLIC NONNULL((1)) size_t KCALL
#ifdef DEFINE_IO_READ
vm_datapart_read_buffered(struct vm_datapart *__restrict self,
                          USER CHECKED void *buf /*dst*/,
                          size_t num_bytes,
                          size_t part_offset /*src_offset*/)
#elif defined(DEFINE_IO_WRITE)
vm_datapart_write_buffered(struct vm_datapart *__restrict self,
                           USER CHECKED void const *buf /*src*/,
                           size_t num_bytes,
                           size_t split_bytes,
                           size_t part_offset /*dst_offset*/)
#endif
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...)
{
	byte_t *temp_buf;
	size_t bufsize;
	size_t result = 0;
	bufsize = CONFIG_VM_DATABLOCK_BUFFEREDIO_MAXBUFSIZE;
	if (bufsize > num_bytes)
		bufsize = num_bytes;
	temp_buf = (byte_t *)alloca(bufsize);
	while (num_bytes) {
		size_t temp;
		if (bufsize > num_bytes)
			bufsize = num_bytes;
		assert(bufsize <= num_bytes);
#ifdef DEFINE_IO_WRITE
		COMPILER_BARRIER();
		memcpy(temp_buf, buf, bufsize);
		COMPILER_BARRIER();
#endif /* DEFINE_IO_WRITE */

		/* Do perform unsafe I/O using the kernel-space buffer (meaning that
		 * it's actually safe because the buffer is locked into memory, meaning
		 * that accessing it not only cannot cause a #PF that may try to re-lock
		 * the given data part `self', but cannot cause a #PF at all) */
		temp = IFELSE_RW(vm_datapart_read_unsafe(self, temp_buf, bufsize,
		                                         part_offset),
		                 vm_datapart_write_unsafe(self, temp_buf, bufsize,
		                                          split_bytes, part_offset));
		if (!temp)
			break;
		assert(temp <= bufsize);
#ifdef DEFINE_IO_READ
		COMPILER_BARRIER();
		buf = mempcpy(buf, temp_buf, temp);
		COMPILER_BARRIER();
#else /* DEFINE_IO_READ */
		buf = (byte_t *)buf + temp;
#endif /* !DEFINE_IO_READ */
		part_offset += temp;
		result    += temp;
		num_bytes -= temp;
	}
	return result;
}

DECL_END

#undef IFELSE_RW
#undef DEFINE_IO_READ
#undef DEFINE_IO_WRITE
