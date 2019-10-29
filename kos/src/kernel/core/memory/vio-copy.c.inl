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
#include "vio.c"
#define DEFINE_IO_READ 1
//#define DEFINE_IO_WRITE 1
#endif /* __INTELLISENSE__ */

DECL_BEGIN

#if (defined(DEFINE_IO_READ) + defined(DEFINE_IO_WRITE)) != 1
#error "Must #define DEFINE_IO_READ or DEFINE_IO_WRITE before #include-ing  this file"
#endif


#ifdef DEFINE_IO_READ
PUBLIC NONNULL((1)) void KCALL
vio_copyfromvio_to_phys(struct vio_args *__restrict args,
                        vm_phys_t dst, vm_daddr_t src,
                        size_t num_bytes)
#elif defined(DEFINE_IO_WRITE)
PUBLIC NONNULL((1)) void KCALL
vio_copytovio_from_phys(struct vio_args *__restrict args,
                        vm_daddr_t dst, vm_phys_t src,
                        size_t num_bytes)
#endif
		THROWS(...) {
	bool is_first;
	uintptr_t backup;
	vm_vpage_t tramp;
	if unlikely(!num_bytes)
		return;
	is_first = true;
	tramp    = THIS_TRAMPOLINE_PAGE;
	TRY {
#ifdef DEFINE_IO_READ
#define PHYS_BUF   dst
#elif defined(DEFINE_IO_WRITE)
#define PHYS_BUF   src
#endif
		for (;;) {
			vm_ppage_t pageaddr;
			size_t page_bytes;
			pageaddr   = (vm_ppage_t)VM_ADDR2PAGE(PHYS_BUF);
			page_bytes = PAGESIZE - (PHYS_BUF & (PAGESIZE - 1));
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
#elif defined(DEFINE_IO_WRITE)
			if (is_first) {
				backup = pagedir_push_mapone(tramp, pageaddr,
				                             PAGEDIR_MAP_FREAD);
			} else {
				pagedir_mapone(tramp, pageaddr,
				               PAGEDIR_MAP_FREAD);
			}
#endif
			pagedir_syncone(tramp);
			/* Copy memory. */
#ifdef DEFINE_IO_READ
			vio_copyfromvio(args,
			                (byte_t *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(PHYS_BUF & (PAGESIZE - 1))),
			                src,
			                page_bytes);
#elif defined(DEFINE_IO_WRITE)
			vio_copytovio(args,
			              dst,
			              (byte_t *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(PHYS_BUF & (PAGESIZE - 1))),
			              page_bytes);
#endif
			if (page_bytes >= num_bytes)
				break;
			num_bytes -= page_bytes;
			PHYS_BUF += page_bytes;
#ifdef DEFINE_IO_READ
			src += page_bytes;
#elif defined(DEFINE_IO_WRITE)
			dst += page_bytes;
#endif
		}
#undef PHYS_BUF
	} EXCEPT {
		/* Try-catch is required, because VIO access may throw exceptions. */
		pagedir_pop_mapone(tramp, backup);
		RETHROW();
	}
	pagedir_pop_mapone(tramp, backup);
}


#undef DEFINE_IO_WRITE
#undef DEFINE_IO_READ


DECL_END

