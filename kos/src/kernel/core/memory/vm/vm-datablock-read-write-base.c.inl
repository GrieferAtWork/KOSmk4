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
#include "vm.c"
#define DEFINE_IO_READ 1
//#define DEFINE_IO_WRITE 1
//#define DEFINE_IO_PHYS 1
//#define DEFINE_IO_VECTOR 1
//#define DEFINE_IO_UNSAFE 1
#endif /* __INTELLISENSE__ */

#include <kernel/aio.h>
#include <kernel/vio.h>
#include <hybrid/unaligned.h>

DECL_BEGIN

#ifdef DEFINE_IO_READ
#define FUNC_RW(x)     vm_datablock_read##x
#define FUNC_VIO_RW(x) vm_datablock_vio_read##x
#else /* DEFINE_IO_READ */
#define FUNC_RW(x)     vm_datablock_write##x
#define FUNC_VIO_RW(x) vm_datablock_vio_write##x
#endif /* !DEFINE_IO_READ */


#ifdef DEFINE_IO_READ
#if defined(DEFINE_IO_PHYS) && defined(DEFINE_IO_VECTOR)
#define DO_PART_IO vm_datapart_readv_phys
#elif defined(DEFINE_IO_VECTOR)
#define DO_PART_IO vm_datapart_readv
#elif defined(DEFINE_IO_PHYS)
#define DO_PART_IO vm_datapart_read_phys
#elif defined(DEFINE_IO_UNSAFE)
#define DO_PART_IO vm_datapart_read_unsafe
#else
#define DO_PART_IO vm_datapart_read
#endif
#else /* DEFINE_IO_READ */
#if defined(DEFINE_IO_PHYS) && defined(DEFINE_IO_VECTOR)
#define DO_PART_IO vm_datapart_writev_phys
#elif defined(DEFINE_IO_VECTOR)
#define DO_PART_IO vm_datapart_writev
#elif defined(DEFINE_IO_PHYS)
#define DO_PART_IO vm_datapart_write_phys
#elif defined(DEFINE_IO_UNSAFE)
#define DO_PART_IO vm_datapart_write_unsafe
#else
#define DO_PART_IO vm_datapart_write
#endif
#endif /* !DEFINE_IO_READ */


#ifndef CONFIG_NO_VIO
/* Perform datablock access through VIO callbacks. */
#ifdef DEFINE_IO_READ
#if defined(DEFINE_IO_PHYS) && defined(DEFINE_IO_VECTOR)
#define DO_VIO_ACCESS  vm_datablock_vio_readv_phys
#elif defined(DEFINE_IO_VECTOR)
#define DO_VIO_ACCESS  vm_datablock_vio_readv
#elif defined(DEFINE_IO_PHYS)
#define DO_VIO_ACCESS  vm_datablock_vio_read_phys
#else
#define DO_VIO_ACCESS  vm_datablock_vio_read
#endif
#else /* DEFINE_IO_READ */
#if defined(DEFINE_IO_PHYS) && defined(DEFINE_IO_VECTOR)
#define DO_VIO_ACCESS  vm_datablock_vio_writev_phys
#elif defined(DEFINE_IO_VECTOR)
#define DO_VIO_ACCESS  vm_datablock_vio_writev
#elif defined(DEFINE_IO_PHYS)
#define DO_VIO_ACCESS  vm_datablock_vio_write_phys
#else
#define DO_VIO_ACCESS  vm_datablock_vio_write
#endif
#endif /* !DEFINE_IO_READ */
#endif /* !CONFIG_NO_VIO */



PUBLIC
#ifdef DEFINE_IO_VECTOR
	NONNULL((1, 2))
#else /* DEFINE_IO_VECTOR */
	NONNULL((1))
#endif /* !DEFINE_IO_VECTOR */
void
#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
KCALL FUNC_RW(vp)
#elif defined(DEFINE_IO_VECTOR)
KCALL FUNC_RW(v)
#elif defined(DEFINE_IO_PHYS)
KCALL FUNC_RW(p)
#elif defined(DEFINE_IO_UNSAFE)
/* Same as the `vm_datablock_(read|write)', however make the assumption that the
 * memory backing is `safe' (i.e. access could never cause a #PF attempting to
 * acquire a lock to `self' when doing so is impossible) */
KCALL FUNC_RW(_unsafe)
#elif defined(DEFINE_IO_READ)
KCALL vm_datablock_read
#else
KCALL vm_datablock_write
#endif
                          (struct vm_datablock *__restrict self,
#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
                           struct aio_pbuffer const *__restrict buf,
#elif defined(DEFINE_IO_VECTOR)
                           struct aio_buffer const *__restrict buf,
#elif defined(DEFINE_IO_PHYS)
                           vm_phys_t buf,
#elif defined(DEFINE_IO_READ) && defined(DEFINE_IO_UNSAFE)
                           void *buf,
#elif defined(DEFINE_IO_UNSAFE)
                           void const *buf,
#elif defined(DEFINE_IO_READ)
                           USER CHECKED void *buf,
#else
                           USER CHECKED void const *buf,
#endif
                           size_t num_bytes,
                           vm_daddr_t src_offset)
#ifdef DEFINE_IO_PHYS
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...)
#else /* DEFINE_IO_PHYS */
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...)
#endif /* !DEFINE_IO_PHYS */
{
	REF struct vm_datapart *part;
#ifdef DEFINE_IO_VECTOR
#ifdef DEFINE_IO_PHYS
	struct aio_pbuffer view,view2;
#else /* DEFINE_IO_PHYS */
	struct aio_buffer view,view2;
#endif /* !DEFINE_IO_PHYS */
#endif /* DEFINE_IO_VECTOR */
#ifndef CONFIG_NO_VIO
	if (self->db_vio) {
		/* Perform I/O through VIO functionality. */
		DO_VIO_ACCESS(self,
		              buf,
#ifndef DEFINE_IO_VECTOR
		              num_bytes,
#endif /* !DEFINE_IO_VECTOR */
		              src_offset);
		return;
	}
#endif /* !CONFIG_NO_VIO */
	for (;;) {
		size_t temp;
		part = vm_datablock_locatepart(self,
		                               (vm_vpage64_t)(src_offset >> VM_DATABLOCK_ADDRSHIFT(self)),
		                               CEILDIV(num_bytes + (src_offset & (VM_DATABLOCK_PAGESIZE(self) - 1)),
		                                       PAGESIZE));
		TRY {
			temp = DO_PART_IO(part,
			                  buf,
#ifndef DEFINE_IO_VECTOR
			                  num_bytes,
#endif /* !DEFINE_IO_VECTOR */
#ifdef DEFINE_IO_WRITE
			                  num_bytes,
#endif /* !DEFINE_IO_WRITE */
			                  src_offset - vm_datapart_startbyte(part));
		} EXCEPT {
			decref(part);
			RETHROW();
		}
		decref(part);
		assert(temp <= num_bytes);
		if (temp >= num_bytes)
			break;
		num_bytes -= temp;
#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
		if (buf == &view) {
			aio_pbuffer_init_view_after(&view2, &view, temp);
			buf = &view2;
		} else {
			aio_pbuffer_init_view_after(&view, buf, temp);
			buf = &view;
		}
#elif defined(DEFINE_IO_VECTOR)
		if (buf == &view) {
			aio_buffer_init_view_after(&view2, &view, temp);
			buf = &view2;
		} else {
			aio_buffer_init_view_after(&view, buf, temp);
			buf = &view;
		}
#elif defined(DEFINE_IO_PHYS)
		buf += temp;
#else
		buf = (byte_t *)buf + temp;
#endif
	}
}



#ifndef CONFIG_NO_VIO
#if !defined(DEFINE_IO_UNSAFE)

/* Perform datablock access through VIO callbacks. */
PUBLIC
#ifdef DEFINE_IO_VECTOR
	NONNULL((1, 2))
#else /* DEFINE_IO_VECTOR */
	NONNULL((1))
#endif /* !DEFINE_IO_VECTOR */
	void
#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
KCALL FUNC_VIO_RW(v_phys)
#elif defined(DEFINE_IO_VECTOR)
KCALL FUNC_VIO_RW(v)
#elif defined(DEFINE_IO_PHYS)
KCALL FUNC_VIO_RW(_phys)
#elif defined(DEFINE_IO_READ)
KCALL vm_datablock_vio_read
#else
KCALL vm_datablock_vio_write
#endif
                              (struct vm_datablock *__restrict self,
#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
                               struct aio_pbuffer const *__restrict buf,
#elif defined(DEFINE_IO_VECTOR)
                               struct aio_buffer const *__restrict buf,
#elif defined(DEFINE_IO_PHYS)
                               vm_phys_t buf,
                               size_t num_bytes,
#elif defined(DEFINE_IO_READ)
                               USER CHECKED void *buf,
                               size_t num_bytes,
#else
                               USER CHECKED void const *buf,
                               size_t num_bytes,
#endif
                               vm_daddr_t src_offset)
#ifdef DEFINE_IO_PHYS
       THROWS(...)
#else /* DEFINE_IO_PHYS */
       THROWS(E_SEGFAULT,...)
#endif /* !DEFINE_IO_PHYS */
{
#if defined(DEFINE_IO_PHYS) && defined(DEFINE_IO_VECTOR)
	struct aio_pbuffer_entry ent;
	AIO_PBUFFER_FOREACH(ent, buf) {
		FUNC_VIO_RW(_phys)(self,
		                   ent.ab_base,
		                   ent.ab_size,
		                   src_offset);
		src_offset += ent.ab_size;
	}
#elif defined(DEFINE_IO_VECTOR)
	struct aio_buffer_entry ent;
	AIO_BUFFER_FOREACH(ent,buf) {
#ifdef DEFINE_IO_READ
		vm_datablock_vio_read
#else /* DEFINE_IO_READ */
		vm_datablock_vio_write
#endif /* !DEFINE_IO_READ */
		                      (self,
		                       ent.ab_base,
		                       ent.ab_size,
		                       src_offset);
		src_offset += ent.ab_size;
	}
#elif defined(DEFINE_IO_PHYS)
	pagedir_pushval_t backup; vm_vpage_t tramp;
	bool is_first;
	if unlikely(!num_bytes) return;
	is_first = true;
	tramp = THIS_TRAMPOLINE_PAGE;
	TRY {
		for (;;) {
			vm_ppage_t pageaddr;
			size_t page_bytes;
			pageaddr   = (vm_ppage_t)VM_ADDR2PAGE(buf);
			page_bytes = PAGESIZE - (buf & (PAGESIZE - 1));
			if (page_bytes > num_bytes)
				page_bytes = num_bytes;
#ifdef DEFINE_IO_READ
			if (is_first) {
				backup = pagedir_push_mapone(tramp, pageaddr,
				                             PAGEDIR_MAP_FWRITE);
			} else {
				pagedir_mapone(tramp, pageaddr,
				               PAGEDIR_MAP_FWRITE);
			}
#else /* DEFINE_IO_READ */
			if (is_first) {
				backup = pagedir_push_mapone(tramp, pageaddr,
				                             PAGEDIR_MAP_FREAD);
			} else {
				pagedir_mapone(tramp, pageaddr,
				               PAGEDIR_MAP_FREAD);
			}
#endif /* !DEFINE_IO_READ */
			pagedir_syncone(tramp);
			/* Perform VIO memory access. */
#ifdef DEFINE_IO_READ
			vm_datablock_vio_read
#else /* DEFINE_IO_READ */
			vm_datablock_vio_write
#endif /* !DEFINE_IO_READ */
			                      (self,
			                       (byte_t *)VM_PAGE2ADDR(tramp) + (ptrdiff_t)(buf & (PAGESIZE - 1)),
			                       page_bytes,
			                       src_offset);
			if (page_bytes >= num_bytes)
				break;
			num_bytes -= page_bytes;
			src_offset += page_bytes;
			buf += page_bytes;
		}
	} EXCEPT {
		/* Try-catch is required, because `dst' may be a user-buffer,
		 * in which case access may cause an exception to be thrown. */
		pagedir_pop_mapone(tramp, backup);
		RETHROW();
	}
	pagedir_pop_mapone(tramp, backup);
#else
	struct vio_args args;
	args.va_type            = self->db_vio;
	args.va_block           = self;
	args.va_part            = NULL;
	args.va_access_partoff  = 0;
	args.va_access_pageaddr = 0;
	args.va_state           = NULL;
#ifdef CONFIG_VIO_HAS_QWORD
#define VIO_LARGEBLOCK_SIZE 8
#define VIO_LARGEBLOCK_TYPE u64
#else /* CONFIG_VIO_HAS_QWORD */
#define VIO_LARGEBLOCK_SIZE 4
#define VIO_LARGEBLOCK_TYPE u32
#endif /* !CONFIG_VIO_HAS_QWORD */

#ifdef DEFINE_IO_READ
#define DO_VIO(T, w, n) UNALIGNED_SET##n((T *)buf, vio_read##w(&args, src_offset))
#else /* DEFINE_IO_READ */
#define DO_VIO(T, w, n) vio_write##w(&args, src_offset, UNALIGNED_GET##n((T *)buf))
#endif /* !DEFINE_IO_READ */
	for (; num_bytes >= VIO_LARGEBLOCK_SIZE;
	     src_offset += VIO_LARGEBLOCK_SIZE,
	     num_bytes -= VIO_LARGEBLOCK_SIZE,
	     buf = (byte_t *)buf + VIO_LARGEBLOCK_SIZE) {
#ifdef CONFIG_VIO_HAS_QWORD
		DO_VIO(u64, q, 64);
#else /* CONFIG_VIO_HAS_QWORD */
		DO_VIO(u32, l, 32);
#endif /* !CONFIG_VIO_HAS_QWORD */
	}
	/* Access unaligned memory. */
#ifdef CONFIG_VIO_HAS_QWORD
	if (num_bytes & 4) {
		DO_VIO(u32, l, 32);
		buf = (byte_t *)buf + 4;
		src_offset += 4;
	}
#endif /* CONFIG_VIO_HAS_QWORD */
	if (num_bytes & 2) {
		DO_VIO(u16, w, 16);
		buf = (byte_t *)buf + 2;
		src_offset += 2;
	}
#undef DO_VIO
	if (num_bytes & 1) {
#ifdef DEFINE_IO_READ
		*(u8 *)buf = vio_readb(&args, src_offset);
#else /* DEFINE_IO_READ */
		vio_writeb(&args, src_offset, *(u8 *)buf);
#endif /* !DEFINE_IO_READ */
	}
#undef VIO_LARGEBLOCK_TYPE
#undef VIO_LARGEBLOCK_SIZE
#endif
}

#endif /* !DEFINE_IO_UNSAFE */
#endif /* !CONFIG_NO_VIO */



DECL_END

#undef FUNC_VIO_RW
#undef FUNC_RW
#undef DO_VIO_ACCESS
#undef DO_PART_IO
#undef DEFINE_IO_READ
#undef DEFINE_IO_WRITE
#undef DEFINE_IO_PHYS
#undef DEFINE_IO_VECTOR
#undef DEFINE_IO_UNSAFE
