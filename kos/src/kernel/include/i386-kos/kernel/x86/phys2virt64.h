/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_PHYS2VIRT64_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_PHYS2VIRT64_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/host.h>

#include <kos/kernel/paging.h>

#if defined(__x86_64__) && defined(KERNEL_PHYS2VIRT_BASE)

DECL_BEGIN

/*[[[config CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MAXALLOC = 4
 * The max # of pages which may be allocated for the purpose of
 * describing  the mappings required  for the physical identity
 * mapping.
 * Because the identity area is as  large as it is (64TiB),  one
 * would need an insane amount of page table vectors (128 *  512
 * pages  in total) in order to describe the entire region using
 * only 2MiB pages (when 1GiB pages are available, this  problem
 * would  become manageable  since we'd  only need  128 pages to
 * describe the entire  are, which also  means that this  entire
 * mechanism doesn't actually end up being used when this config
 * is found to be possible at runtime)
 * Anyways: In  order  to limit  the  memory consumption  of  the phys.
 *          identity area, at most `CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MAXALLOC'
 *          E1+E2 vectors  (and thereby  physical  pages) can  ever  be
 *          allocated at the  same time. When  another E1 vector  needs
 *          to be  allocated at  a point  when there  are already  this
 *          many vectors  in use,  all identity  mappings are  deleted,
 *          and the  one  currently  being  accessed  will  get  mapped
 *          (all of  this happens  lazily during  #PF handling,  except
 *          the physical memory available for this purpose is allocated
 *          during early boot)
 * ]]]*/
#ifdef CONFIG_NO_KERNEL_X86_PHYS2VIRT_IDENTITY_MAXALLOC
#undef CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MAXALLOC
#define CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MAXALLOC 0
#elif !defined(CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MAXALLOC)
#define CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MAXALLOC 4
#elif (CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MAXALLOC + 0) <= 0
#undef CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MAXALLOC
#define CONFIG_NO_KERNEL_X86_PHYS2VIRT_IDENTITY_MAXALLOC
#define CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MAXALLOC 0
#endif /* ... */
/*[[[end]]]*/

/*[[[config CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MINALLOC = 2
 * Need at least 2 control vectors to allow for the case
 * where  an unaligned physical memory access happens to
 * cross a 1GiB  boundary, in which  case 2 vectors  are
 * needed to allow the request to complete successfully.
 * ]]]*/
#ifdef CONFIG_NO_KERNEL_X86_PHYS2VIRT_IDENTITY_MINALLOC
#undef CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MINALLOC
#define CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MINALLOC 0
#elif !defined(CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MINALLOC)
#define CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MINALLOC 2
#elif (CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MINALLOC + 0) <= 0
#undef CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MINALLOC
#define CONFIG_NO_KERNEL_X86_PHYS2VIRT_IDENTITY_MINALLOC
#define CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MINALLOC 0
#endif /* ... */
/*[[[end]]]*/

#if (!defined(CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MINALLOC) || \
     (CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MINALLOC + 0) < 2)
#undef CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MINALLOC
#define CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MINALLOC 2
#endif /* !CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MINALLOC */



#if CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MAXALLOC == 0
#undef CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MAXALLOC
#undef CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MINALLOC
#elif CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MINALLOC > CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MAXALLOC
#undef CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MINALLOC
#define CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MINALLOC CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MAXALLOC
#endif /* ... */

#ifdef __CC__

/* Ensure that the  given `addr', which  must be  located
 * inside of [KERNEL_PHYS2VIRT_MIN, KERNEL_PHYS2VIRT_MAX]
 * is  mapped  against its  designated  physical address.
 * This function is  called from within  the #PF  handler
 * when a kernel-originating fault happens for an address
 * within that range.
 * NOTE: When called before `x86_initialize_phys2virt64()',
 *       this function may throw an E_SEGFAULT. Afterwards,
 *       this function is unconditionally NOTHROW! */
FUNDEF NOBLOCK NOPREEMPT void FCALL
x86_phys2virt64_require(void *addr);

/* A  special VM  node (that isn't  linked to any  backing data part,
 * and is thus a so-called ~reserved~ memory mapping), but is checked
 * for  by the #PF handler, where it  indicates an access made to the
 * physical identity area.
 * Separately, this node's  presence within the  kernel VM  prevents
 * anything else from being mapped into the physical identity range. */
DATDEF struct mnode x86_phys2virt64_node;

#endif /* __CC__ */

DECL_END

#else /* __x86_64__ && KERNEL_PHYS2VIRT_BASE */
#undef CONFIG_KERNEL_X86_PHYS2VIRT_IDENTITY_MAXALLOC
#endif /* !__x86_64__ || !KERNEL_PHYS2VIRT_BASE */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_PHYS2VIRT64_H */
