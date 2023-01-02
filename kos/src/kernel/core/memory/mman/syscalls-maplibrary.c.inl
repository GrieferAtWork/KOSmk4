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
#ifdef __INTELLISENSE__
#include "syscalls.c"
#define DEFINE_sys_maplibrary
//#define DEFINE_compat_sys_maplibrary
#endif /* __INTELLISENSE__ */

#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/flags.h>
#include <kernel/mman/mbuilder.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart-blkst.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/phys-access.h>
#include <kernel/user.h>
#include <misc/unlockinfo.h>

#include <hybrid/align.h>

#include <kos/exec/elf.h>

#include <elf.h>
#include <string.h>

#ifdef DEFINE_compat_sys_maplibrary
#include <compat/kos/exec/elf.h>
#endif /* DEFINE_compat_sys_maplibrary */

DECL_BEGIN

#ifndef DBG_memset
#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */
#endif /* !DBG_memset */


#ifndef MMAN_UNLOCKINFO_DEFINED
#define MMAN_UNLOCKINFO_DEFINED
struct mman_unlockinfo: unlockinfo {
	struct mman *mui_mman; /* [1..1][const] The mman to unlock. */
};
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mman_unlockinfo_cb)(struct unlockinfo *__restrict self) {
	struct mman_unlockinfo *me;
	me = (struct mman_unlockinfo *)self;
	mman_lock_release(me->mui_mman);
}
#endif /* !MMAN_UNLOCKINFO_DEFINED */

#if defined(DEFINE_sys_maplibrary)
#define LOCAL_ELFW ELFW
#define LOCAL_ElfW ElfW
#define LOCAL_elfW elfW
DEFINE_SYSCALL5(void *, maplibrary,
                void *, addr, syscall_ulong_t, flags, fd_t, fd,
                USER UNCHECKED ElfW(Phdr) const *, hdrv, size_t, hdrc)
#elif defined(DEFINE_compat_sys_maplibrary)
#define LOCAL_ELFW COMPAT_ELFW
#define LOCAL_ElfW COMPAT_ElfW
#define LOCAL_elfW COMPAT_elfW
DEFINE_COMPAT_SYSCALL5(void *, maplibrary,
                       void *, addr, syscall_ulong_t, flags, fd_t, fd,
                       USER UNCHECKED COMPAT_ElfW(Phdr) const *, hdrv, size_t, hdrc)
#else /* ... */
#error "Invalid configuration"
#endif /* !... */
{
	uintptr_t result;
	struct mbuilder_norpc builder;
	struct mman *mm = THIS_MMAN;
	struct mnode_slist deadnodes;
	struct handle_mmap_info file;

	/* Validate arguments. */
	validate_readablem(hdrv, hdrc, sizeof(*hdrv));
	VALIDATE_FLAGSET(flags,
	                 MAP_FIXED | MAP_32BIT | MAP_GROWSDOWN |
	                 MAP_GROWSUP | MAP_LOCKED | MAP_NORESERVE |
	                 MAP_POPULATE | MAP_NONBLOCK | MAP_SYNC |
	                 MAP_FIXED_NOREPLACE | MAP_NOASLR,
	                 E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_FLAGS);

	/* Special case: Use `KERNEL_MHINT_USER_LIBRARY' as the default mapping
	 *               hint when  none was  given by  our user-space  caller. */
	if (!(flags & MAP_FIXED) && (uintptr_t)addr < (uintptr_t)mman_getunmapped_user_minaddr)
		addr = MHINT_GETADDR(KERNEL_MHINT_USER_LIBRARY);

	/* Load information on the file that's being mapped. */
	file.hmi_minaddr = (pos_t)0;
	file.hmi_maxaddr = (pos_t)-1;
	file.hmi_fspath  = NULL;
	file.hmi_fsname  = NULL;
	{
		/* Specific file. */
		REF struct handle hand;
		hand = handles_lookup(fd);
#ifndef NDEBUG
		file.hmi_file = NULL;
#endif /* !NDEBUG */
		TRY {
			handle_mmap(hand, &file);
#ifndef NDEBUG
			assert(file.hmi_file != NULL);
#endif /* !NDEBUG */
		} EXCEPT {
			xdecref_unlikely(file.hmi_fspath);
			xdecref_unlikely(file.hmi_fsname);
			decref(hand);
			RETHROW();
		}
		decref(hand);
	}
	FINALLY_DECREF_UNLIKELY(file.hmi_file);
	FINALLY_XDECREF_UNLIKELY(file.hmi_fspath);
	FINALLY_XDECREF_UNLIKELY(file.hmi_fsname);

	/* Setup our mem-builder */
	mbuilder_norpc_init(&builder);
	TRY {
		size_t i;
		unsigned int map_flags;

		/* All of the  program header  mappings must be  created at  fixed
		 * displacement offsets from each. Additionally, set the NOREPLACE
		 * flag to cause an exception to be thrown if the caller's program
		 * headers overlap with each other. */
		map_flags = MAP_FIXED | MAP_FIXED_NOREPLACE | flags;

		/* Build file mappings as described by `hdrv...+=hdrc'. */
		for (i = 0; i < hdrc; ++i) {
			unsigned int map_prot;
			LOCAL_ElfW(Phdr) phdr;
			PAGEDIR_PAGEALIGNED byte_t *destaddr;   /* Target mapping address iterator. */
			PAGEDIR_PAGEALIGNED size_t mapsize_fil; /* Page-aligned size of the leading file mapping */
			size_t mapsize_gap;                     /* # of leading file-bytes within the file->bss gap area. (or 0 if no gap area is needed) */
			PAGEDIR_PAGEALIGNED size_t mapsize_bss; /* Page-aligned size of the trailing .bss mapping */
			PAGEDIR_PAGEALIGNED size_t mapsize_mem; /* Page-aligned total mapping size */
			memcpy(&phdr, &hdrv[i], sizeof(phdr));
			if (phdr.p_type != PT_LOAD)
				continue;

			map_prot = prot_from_elfpf(phdr.p_flags);

			/* Align program header memory offsets. */
			if (phdr.p_vaddr & PAGEMASK) {
				phdr.p_filesz += phdr.p_vaddr & PAGEMASK;
				phdr.p_memsz += phdr.p_vaddr & PAGEMASK;
				phdr.p_offset -= phdr.p_vaddr & PAGEMASK;
				phdr.p_vaddr &= ~PAGEMASK;
			}
			mapsize_mem = CEIL_ALIGN(phdr.p_memsz, PAGESIZE);

			/* Calculate the sizes of the (up to) 3 different parts of the mapping. */
			mapsize_fil = phdr.p_filesz;
			mapsize_gap = 0;
			mapsize_bss = 0;
			if (mapsize_mem > mapsize_fil) {
				mapsize_bss = mapsize_mem - mapsize_fil;
				if (mapsize_fil & PAGEMASK) {
					/* Special case: the  last page of  the file mapping  crosses
					 * over into the .bss area. In this case, we must immediately
					 * load that page so that we  may initialize it the way  that
					 * the caller has requested it. */
					mapsize_gap = mapsize_fil & PAGEMASK;
					mapsize_fil &= ~PAGEMASK;
					mapsize_bss = 0;
					if (mapsize_mem > mapsize_fil + PAGESIZE) {
						mapsize_bss = mapsize_mem - (mapsize_fil + PAGESIZE);
					} else if (phdr.p_memsz <= phdr.p_filesz) {
						/* No explicit .bss section (can just include the gap-page
						 * as part of the file mapping portion!) */
						mapsize_fil += PAGESIZE;
						mapsize_gap = 0;
					}
				}
			}

			destaddr = (byte_t *)(uintptr_t)phdr.p_vaddr;

			/* Create mappings. */
			if (mapsize_fil != 0) {
				/* Leading file mapping. */
				mbuilder_map_subrange(/* self:             */ &builder,
				                      /* hint:             */ destaddr,
				                      /* num_bytes:        */ mapsize_fil,
				                      /* prot:             */ map_prot,
				                      /* flags:            */ map_flags,
				                      /* file:             */ file.hmi_file,
				                      /* file_fspath:      */ file.hmi_fspath,
				                      /* file_fsname:      */ file.hmi_fsname,
				                      /* file_pos:         */ file.hmi_minaddr + (pos_t)phdr.p_offset,
				                      /* file_map_minaddr: */ file.hmi_minaddr,
				                      /* file_map_maxaddr: */ file.hmi_maxaddr);
				destaddr += mapsize_fil;
			}
			if (mapsize_gap != 0) {
				struct mpart *part;
				struct mbnode *node;
				pos_t fpos = file.hmi_minaddr + (pos_t)phdr.p_offset + mapsize_fil;
				assert(mapsize_gap < PAGESIZE);
				/* Make sure that there isn't already something at this address! */
				if unlikely((node = mbuilder_mappings_locate(&builder, destaddr)) != NULL) {
					THROW(E_BADALLOC_ADDRESS_ALREADY_EXISTS,
					      destaddr, destaddr + PAGEMASK,
					      mbnode_getminaddr(node),
					      mbnode_getmaxaddr(node));
				}

				/* Create a 1-page mapping at `destaddr' with the first `mapsize_gap'
				 * bytes loaded from file.hmi_file@fpos, and the remaining bytes  all
				 * set to zeroes. */
				node = (struct mbnode *)kmalloc(sizeof(struct mnode), GFP_LOCKED | GFP_PREFLT);
				TRY {
					part = (struct mpart *)kmalloc(sizeof(struct mpart), GFP_LOCKED | GFP_PREFLT);
					TRY {
						physaddr_t paddr;
						part->mp_mem.mc_start = page_mallocone();
						if unlikely(part->mp_mem.mc_start == PHYSPAGE_INVALID)
							THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
						paddr = physpage2addr(part->mp_mem.mc_start);
#ifndef NO_PHYS_IDENTITY
						/* TODO */
#endif /* !NO_PHYS_IDENTITY */
						/* Copy leading file data into the part's backing page. */
						/* TODO: Check bounds of `file.hmi_minaddr' / `file.hmi_maxaddr' */
						mapsize_gap = mfile_read_p(file.hmi_file, paddr, mapsize_gap, fpos);

						/* Zero-initialize trailing .bss */
						if (!page_iszero(part->mp_mem.mc_start))
							memsetphys_onepage(paddr + mapsize_gap, 0, PAGESIZE - mapsize_gap);
					} EXCEPT {
						kfree(part);
						RETHROW();
					}
				} EXCEPT {
					kfree(node);
					RETHROW();
				}
				/* All of the remaining init is all NOTHROW. */

				/* Initialize the part. */
				part->mp_refcnt = 1; /* +1: `node->mbn_part' */
				part->mp_xflags = MPART_XF_NORMAL;
#if MPART_F_MLOCK == MAP_LOCKED
				part->mp_flags = MPART_F_NORMAL | (map_flags & MAP_LOCKED);
#else /* MPART_F_MLOCK == MAP_LOCKED */
				part->mp_flags = ((map_flags & MAP_LOCKED)
				                  ? (MPART_F_NORMAL | MPART_F_MLOCK)
				                  : (MPART_F_NORMAL));
#endif /* MPART_F_MLOCK != MAP_LOCKED */
				part->mp_state = MPART_ST_MEM;
				part->mp_file  = incref(&mfile_zero);
				LIST_INIT(&part->mp_copy);
				LIST_INIT(&part->mp_share);
				SLIST_INIT(&part->mp_lockops);
				LIST_ENTRY_UNBOUND_INIT(&part->mp_allparts);
				part->mp_minaddr = (pos_t)(0);
				part->mp_maxaddr = (pos_t)(PAGESIZE - 1);
				DBG_memset(&part->mp_changed, 0xcc, sizeof(part->mp_changed));
				_mpart_init_asanon(part);
				part->mp_blkst_ptr   = NULL;
				part->mp_mem.mc_size = 1;
				part->mp_meta        = NULL;

				/* Initialize the node. */
				node->mbn_minaddr = destaddr;
				node->mbn_maxaddr = destaddr + PAGESIZE - 1;
				node->mbn_flags   = mbnodeflags_from_mapflags_usronly(map_flags) |
				                    mnodeflags_from_prot_noshared(map_prot);
				node->mbn_part    = part; /* Inherit reference */
				node->mbn_fspath  = xincref(file.hmi_fspath);
				node->mbn_fsname  = xincref(file.hmi_fsname);
				node->mbn_file    = incref(&mfile_zero);
				mnode_mbn_filpos_set(node, 0);

				/* Insert the node into the builder. */
				mbuilder_insert_fmnode(&builder, node);
				destaddr += PAGESIZE;
			}
			if (mapsize_bss != 0) {
				/* Trailing .bss mapping. */
				mbuilder_map(/* self:      */ &builder,
				             /* hint:      */ destaddr,
				             /* num_bytes: */ mapsize_bss,
				             /* prot:      */ map_prot,
				             /* flags:     */ map_flags,
				             /* file:      */ &mfile_zero);
			}
		}

		/* Check for special case: The mem-builder is empty. */
		if unlikely(builder.mb_mappings == NULL) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_NOMAPPINGS,
			      hdrc);
		}

		/* Lock the mman */
again_lock_mman:
		mman_lock_acquire(mm);

		/* Figure out the lock address that we'll end up using. */
		result = mman_getunmapped_mbuilder_or_unlock(mm, (uintptr_t)addr,
		                                             &builder, flags, NULL);
		if (result == (uintptr_t)MAP_FAILED)
			goto again_lock_mman;

		/* With the target address decided,  lock all of the  mem-parts
		 * that will end up being mapped once `builder' ends up loaded. */
		{
			struct mman_unlockinfo unlock;
			unlock.ui_unlock = &mman_unlockinfo_cb;
			unlock.mui_mman  = mm;
			if (!mbuilder_partlocks_acquire_or_unlock(&builder, &unlock))
				goto again_lock_mman;
		}

		/* Destroy already-existing mappings when `MAP_FIXED' was given. */
		SLIST_INIT(&deadnodes);
		if ((flags & (MAP_FIXED | MAP_FIXED_NOREPLACE)) == MAP_FIXED) {
			if (!mman_unmap_mbuilder(mm, &builder, result, &deadnodes)) {
				mbuilder_partlocks_release(&builder);
				mman_lock_release(mm);
				/*mbuilder_norpc_fini(&builder);*/ /* s.a. EXCEPT below! */
				THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
			}
		}
	} EXCEPT {
		mbuilder_norpc_fini(&builder);
		RETHROW();
	}

	/* With  all of the locks held, a target address selected, and
	 * everything being consistent, we can now move on to actually
	 * load our new mappings into memory.
	 * NOTE: This call will also release all of the part-locks that
	 *       were acquired above! */
	mman_map_mbuilder(mm, &builder, result, MMAN_MAP_MBUILDER_F_NORMAL);

	/* Release our mman-lock. */
	mman_lock_release(mm);

	/* Destroy unmapped, pre-existing nodes. */
	while (!SLIST_EMPTY(&deadnodes)) {
		struct mnode *oldnode;
		oldnode = SLIST_FIRST(&deadnodes);
		SLIST_REMOVE_HEAD(&deadnodes, _mn_dead);
		assert(oldnode->mn_flags & MNODE_F_UNMAPPED);
		mnode_destroy(oldnode);
	}

	mbuilder_norpc_fini(&builder);
	return (void *)result;
}
#undef LOCAL_elfW
#undef LOCAL_ElfW
#undef LOCAL_ELFW


DECL_END

#undef DEFINE_compat_sys_maplibrary
#undef DEFINE_sys_maplibrary
