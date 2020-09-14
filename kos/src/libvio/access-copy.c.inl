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
#include "access.c"
#define DEFINE_IO_READ 1
//#define DEFINE_IO_WRITE 1
#endif /* __INTELLISENSE__ */

#ifdef __KERNEL__
#include <kernel/vm/phys.h>

DECL_BEGIN

#if (defined(DEFINE_IO_READ) + defined(DEFINE_IO_WRITE)) != 1
#error "Must #define DEFINE_IO_READ or DEFINE_IO_WRITE before #include-ing  this file"
#endif /* (DEFINE_IO_READ + DEFINE_IO_WRITE) != 1 */


#ifdef DEFINE_IO_READ
INTERN NONNULL((1)) void KCALL
libvio_copyfromvio_to_phys(struct vio_args *__restrict args,
                           vio_addr_t offset, physaddr_t buf,
                           size_t num_bytes)
#elif defined(DEFINE_IO_WRITE)
INTERN NONNULL((1)) void KCALL
libvio_copytovio_from_phys(struct vio_args *__restrict args,
                           vio_addr_t offset, physaddr_t buf,
                           size_t num_bytes)
#endif /* ... */
		__THROWS(...) {
	bool is_first;
	pagedir_pushval_t backup;
	byte_t *tramp;
	if unlikely(!num_bytes)
		return;
	/* TODO: Support for the phys2virt identity mapping! */
	is_first = true;
	tramp    = THIS_TRAMPOLINE_BASE;
	for (;;) {
		size_t page_bytes;
		page_bytes = PAGESIZE - (buf & PAGEMASK);
		if (page_bytes > num_bytes)
			page_bytes = num_bytes;
#ifdef DEFINE_IO_READ
		if (is_first) {
			backup = pagedir_push_mapone(tramp,
			                             buf & ~PAGEMASK,
			                             PAGEDIR_MAP_FWRITE);
			is_first = false;
		} else {
			pagedir_mapone(tramp,
			               buf & ~PAGEMASK,
			               PAGEDIR_MAP_FWRITE);
		}
#elif defined(DEFINE_IO_WRITE)
		if (is_first) {
			backup = pagedir_push_mapone(tramp,
			                             buf & ~PAGEMASK,
			                             PAGEDIR_MAP_FREAD);
			is_first = false;
		} else {
			pagedir_mapone(tramp,
			               buf & ~PAGEMASK,
			               PAGEDIR_MAP_FREAD);
		}
#endif /* ... */
		pagedir_syncone(tramp);
		TRY {
			/* Copy memory. */
#ifdef DEFINE_IO_READ
			libvio_copyfromvio(args,
			                   offset,
			                   tramp + ((ptrdiff_t)buf & PAGEMASK),
			                   page_bytes);
#elif defined(DEFINE_IO_WRITE)
			libvio_copytovio(args,
			                 offset,
			                 tramp + ((ptrdiff_t)buf & PAGEMASK),
			                 page_bytes);
#endif /* ... */
		} EXCEPT {
			/* Try-catch is required, because VIO access may throw exceptions. */
			pagedir_pop_mapone(tramp, backup);
			RETHROW();
		}
		if (page_bytes >= num_bytes)
			break;
		num_bytes -= page_bytes;
		buf += page_bytes;
		offset += page_bytes;
	}
	pagedir_pop_mapone(tramp, backup);
}


#undef DEFINE_IO_WRITE
#undef DEFINE_IO_READ


DECL_END
#endif /* __KERNEL__ */

