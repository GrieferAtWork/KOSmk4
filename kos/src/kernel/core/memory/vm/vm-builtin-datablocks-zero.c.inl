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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#define _KOS_SOURCE 1
//#define DATAPAGE_SHIFT 0
#endif

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/vm.h>
#include <kernel/vm/phys.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN


#define DATA_PAGESIZE          (PAGESIZE >> DATAPAGE_SHIFT)
#define DATA_PAGESHIFT         (PAGESHIFT - DATAPAGE_SHIFT)
#define DATA_PAGES_PER_V_PAGE  (1 << DATAPAGE_SHIFT)

#if __SIZEOF_POINTER__ >= 8 && (DATA_PAGESIZE % 8) == 0
#define CLEAR_DATA_PAGE(base, n) memsetq(base, 0, (n) * (DATA_PAGESIZE / 8))
#elif __SIZEOF_POINTER__ >= 4 && (DATA_PAGESIZE % 4) == 0
#define CLEAR_DATA_PAGE(base, n) memsetl(base, 0, (n) * (DATA_PAGESIZE / 4))
#else
#define CLEAR_DATA_PAGE(base, n) memset(base, 0, (n)*DATA_PAGESIZE)
#endif


PRIVATE NONNULL((1)) void KCALL
PP_CAT2(anon_zero_loadpart, DATAPAGE_SHIFT)(struct vm_datablock *__restrict UNUSED(self),
                                            datapage_t UNUSED(start),
                                            vm_phys_t buffer,
                                            size_t num_pages) {
	pagedir_pushval_t backup;
	byte_t *tramp;
	vm_phys_t phys = buffer & ~PAGEMASK;
	assert(num_pages != 0);
	for (;;) {
		/* Skip all pages that are already zero-initialized. */
		if (page_iszero(addr2page(phys))) {
#if DATA_PAGES_PER_V_PAGE == 1
			if (!num_pages)
				break;
			--num_pages;
#else /* DATA_PAGES_PER_V_PAGE == 1 */
			if (num_pages <= DATA_PAGES_PER_V_PAGE)
				break;
			num_pages -= DATA_PAGES_PER_V_PAGE;
#endif /* DATA_PAGES_PER_V_PAGE != 1 */
			phys += PAGESIZE;
			continue;
		}
		tramp  = THIS_TRAMPOLINE_BASE;
		backup = pagedir_push_mapone(tramp, phys,
		                              PAGEDIR_MAP_FREAD |
		                              PAGEDIR_MAP_FWRITE);
		for (;;) {
			pagedir_syncone(tramp);
#if DATA_PAGES_PER_V_PAGE == 1
			CLEAR_DATA_PAGE(tramp, 1);
			/* Skip all pages that are already zero-initialized. */
			do {
				if (!--num_pages)
					goto done;
				phys += PAGESIZE;
			} while (page_iszero(addr2page(phys)));
#else /* DATA_PAGES_PER_V_PAGE == 1 */
			{
				size_t off_pages, max_pages;
				off_pages = (size_t)(((uintptr_t)buffer >> DATA_PAGESHIFT) & (DATA_PAGESIZE - 1));
				max_pages = DATA_PAGES_PER_V_PAGE - off_pages;
				if (max_pages > num_pages)
					max_pages = num_pages;
				CLEAR_DATA_PAGE(tramp + (off_pages << DATA_PAGESHIFT),
				                max_pages);
				if (max_pages >= num_pages)
					goto done;
				num_pages -= max_pages;
				buffer = 0;
				phys += max_pages * PAGESIZE;
			}
			/* Skip pages that have already been zero-initialized. */
			while (page_iszero(addr2page(phys))) {
				if (num_pages <= DATA_PAGES_PER_V_PAGE)
					goto done;
				num_pages -= DATA_PAGES_PER_V_PAGE;
				phys += PAGESIZE;
			}
#endif /* DATA_PAGES_PER_V_PAGE != 1 */
			pagedir_mapone(tramp, phys,
			               PAGEDIR_MAP_FREAD |
			               PAGEDIR_MAP_FWRITE);
		}
done:
		pagedir_pop_mapone(tramp, backup);
		break;
	}
}


DECL_END

#undef CLEAR_DATA_PAGE
#undef DATA_PAGES_PER_V_PAGE
#undef DATAPAGE_SHIFT
#undef DATA_PAGESHIFT
#undef DATA_PAGESIZE


