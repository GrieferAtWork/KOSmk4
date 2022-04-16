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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MAP_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MAP_H 1

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/types.h>

#include <hybrid/host.h> /* __ARCH_STACK_GROWS_DOWNWARDS */

#include <asm/os/mman.h>       /* __PROT_* and __MAP_* constants */
#include <kos/kernel/paging.h> /* KERNEL_MHINT_* */



/************************************************************************/
/* Flags for `mman_map*::prot'                                          */
/************************************************************************/

/* Data cannot be accessed. */
#if !defined(PROT_NONE) && defined(__PROT_NONE)
#define PROT_NONE __PROT_NONE
#endif /* !PROT_NONE && __PROT_NONE */

/* Data can be executed. */
#if !defined(PROT_EXEC) && defined(__PROT_EXEC)
#define PROT_EXEC __PROT_EXEC
#endif /* !PROT_EXEC && __PROT_EXEC */

/* Data can be written. */
#if !defined(PROT_WRITE) && defined(__PROT_WRITE)
#define PROT_WRITE __PROT_WRITE
#endif /* !PROT_WRITE && __PROT_WRITE */

/* Data can be read. */
#if !defined(PROT_READ) && defined(__PROT_READ)
#define PROT_READ __PROT_READ
#endif /* !PROT_READ && __PROT_READ */

/* Changes are shared, even after the VM was cloned (`CLONE_VM').
 * NOTE: Same as the `MAP_SHARED' map flag, but
 *       can  be set like any other protection. */
#if !defined(PROT_SHARED) && defined(__PROT_SHARED)
#define PROT_SHARED __PROT_SHARED
#endif /* !PROT_SHARED && __PROT_SHARED */

/* Kernel-only flag: force creation of PROT_WRITE|PROT_SHARED mappings,
 *                   even if the  backing file is  marked as  READONLY.
 *
 * When this flag is used, the mapping will be created and trying to
 * read from it will function like normal. However, attempting to do
 * a write operation will result in the write instruction  returning
 * with an `E_FSERROR_READONLY' exception.
 *
 * Note that when a file becomes READONLY but already has preexisting
 * PROT_WRITE|PROT_SHARED mappings, write access will be revoked from
 * those mappings, and the next time they perform a write access, the
 * same `E_FSERROR_READONLY' exception is thrown.
 *
 * As such, this flag could theoretically be exposed to user-space,
 * but for the time being its intended purpose is to force creation
 * of PROT_WRITE|PROT_SHARED mappings of device files in filesystem
 * drivers.
 *
 * When this flag isn't given (default), then mman_map() will fail
 * and throw an exception `E_FSERROR_READONLY' when trying to  map
 * a READONLY file as WRITE+SHARED. */
#ifndef PROT_FORCEWRITE
#define PROT_FORCEWRITE 0x40
#endif /* !PROT_FORCEWRITE */


/* Kernel-only flag: disallow use of mprotect(2) to gain write access. Trying  to
 * do so will throw `E_INVALID_HANDLE_OPERATION:E_INVALID_HANDLE_OPERATION_MMAP'. */
#ifndef PROT_DENYWRITE
#define PROT_DENYWRITE 0x10
#endif /* !PROT_DENYWRITE */



/************************************************************************/
/* Flags for `mman_map*::flags'                                         */
/************************************************************************/

/* Interpret addr exactly. */
#if !defined(MAP_FIXED) && defined(__MAP_FIXED)
#define MAP_FIXED __MAP_FIXED
#endif /* !MAP_FIXED && __MAP_FIXED */

/* Only give out 32-bit addresses. */
#if !defined(MAP_32BIT) && defined(__MAP_32BIT)
#define MAP_32BIT __MAP_32BIT
#endif /* !MAP_32BIT && __MAP_32BIT */

/* Stack-like segment. */
#if !defined(MAP_GROWSDOWN) && defined(__MAP_GROWSDOWN)
#define MAP_GROWSDOWN __MAP_GROWSDOWN
#endif /* !MAP_GROWSDOWN && __MAP_GROWSDOWN */

/* Stack-like segment growing upwards. */
#if !defined(MAP_GROWSUP) && defined(__MAP_GROWSUP)
#define MAP_GROWSUP __MAP_GROWSUP
#endif /* !MAP_GROWSUP && __MAP_GROWSUP */

/* Lock the mapping. */
#if !defined(MAP_LOCKED) && defined(__MAP_LOCKED)
#define MAP_LOCKED __MAP_LOCKED
#endif /* !MAP_LOCKED && __MAP_LOCKED */

/* Populate (prefault) pagetables. */
#if !defined(MAP_POPULATE) && defined(__MAP_POPULATE)
#define MAP_POPULATE __MAP_POPULATE
#endif /* !MAP_POPULATE && __MAP_POPULATE */

/* Do not block on IO. */
#if !defined(MAP_NONBLOCK) && defined(__MAP_NONBLOCK)
#define MAP_NONBLOCK __MAP_NONBLOCK
#endif /* !MAP_NONBLOCK && __MAP_NONBLOCK */

/* Allocation is for a stack.
 * NOTE: KOS  uses  this  flag  to  determine  where
 *       automatic memory mappings are allocated at. */
#if !defined(MAP_STACK) && defined(__MAP_STACK)
#define MAP_STACK __MAP_STACK
#endif /* !MAP_STACK && __MAP_STACK */

/* Don't  override  existing mappings  when `MAP_FIXED'  is passed.
 * Instead, throw an exception `E_BADALLOC_ADDRESS_ALREADY_EXISTS'. */
#if !defined(MAP_FIXED_NOREPLACE) && defined(__MAP_FIXED_NOREPLACE)
#define MAP_FIXED_NOREPLACE __MAP_FIXED_NOREPLACE
#endif /* !MAP_FIXED_NOREPLACE && __MAP_FIXED_NOREPLACE */

/* Disable ASLR (iow: don't randomize automatically determined mmap addresses)  */
#if !defined(MAP_NOASLR) && defined(__MAP_NOASLR)
#define MAP_NOASLR __MAP_NOASLR
#endif /* !MAP_NOASLR && __MAP_NOASLR */

/* Kernel-only mmap flag:  Set the  `MNODE_F_MPREPARED' node  flag,
 * and ensure that the backing page directory address range is kept
 * prepared for the duration of the node's lifetime. */
#define MAP_PREPARED 0x00000080

/* Set the `MNODE_F_NOSPLIT' flag for newly created nodes. */
#define MAP_NOSPLIT 0x00040000

/* Set the `MNODE_F_NOMERGE' flag for newly created nodes,
 * and don't try to extend a pre-existing node in order to
 * perform the requested mapping. */
#define MAP_NOMERGE 0x00080000

#ifdef __CC__
DECL_BEGIN

struct mman;
struct mfile;
struct path;
struct fdirent;

#ifndef __mfile_phys_defined
#define __mfile_phys_defined
DATDEF struct mfile mfile_phys; /* Physical memory access (file position is physical memory address) */
#endif /* !__mfile_phys_defined */

#ifndef __mfile_ndef_defined
#define __mfile_ndef_defined
DATDEF struct mfile mfile_ndef; /* Random, uninitialized, anonymous memory. */
#endif /* !__mfile_ndef_defined */

#ifndef __mfile_zero_defined
#define __mfile_zero_defined
DATDEF struct mfile mfile_zero; /* Zero-initialized, anonymous memory. */
#endif /* !__mfile_zero_defined */


/* Helper macros to extract the addr/flags from KERNEL_MHINT_* macros. */
#ifndef MHINT_GETADDR
#define __PRIVATE_MHINT_ADDR(x, y) x
#define __PRIVATE_MHINT_MODE(x, y) y
#define MHINT_GETADDR(x) __PRIVATE_MHINT_ADDR x
#define MHINT_GETMODE(x) __PRIVATE_MHINT_MODE x
#endif /* !MHINT_GETADDR */


/* Map a given file into the specified mman.
 * @param: hint:          s.a. `mman_findunmapped'
 * @param: prot:          Set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SHARED | PROT_FORCEWRITE' (Other bits are silently ignored)
 * @param: flags:         Set  of  `MAP_LOCKED | MAP_POPULATE | MAP_NONBLOCK | MAP_PREPARED'   (Other  bits   are
 *                        silently ignored)  Additionally,  the following  flags  may  be set  to  customize  how
 *                        a  suitable   address  is   located  (s.a.   `mman_findunmapped()'  for   more   info):
 *                        `MAP_FIXED | MAP_32BIT | MAP_GROWSDOWN | MAP_GROWSUP | MAP_STACK | MAP_FIXED_NOREPLACE'
 * @param: file:          The file that is being mapped.
 * @param: file_fspath:   Optional mapping path (only used for memory->disk mapping listings)
 * @param: file_fsname:   Optional mapping name (only used for memory->disk mapping listings)
 * @param: file_pos:      Offset into the file being mapped, of where the mapping should start.
 *                        If this value isn't page-aligned,  then its sub-page offset is  added
 *                        to  the   return  value   eventually  returned   by  this   function.
 *                        But  that that when  `MAP_FIXED' flag is also  set, then the sub-page
 *                        offset of `hint' will be silently ignored, meaning that in this  case
 *                        the return value may differ from `hint'!
 * @param: min_alignment:        s.a. `mman_findunmapped'
 * @param: min_alignment_offset: s.a. `mman_findunmapped'
 * @return: * : The effective mapping  base at which `file->DATA.BYTES[file_pos]' can be found. */
FUNDEF BLOCKING_IF(flags & MAP_POPULATE) NONNULL((1, 6)) void *KCALL
mman_map(struct mman *__restrict self,
         UNCHECKED void *hint, size_t num_bytes,
         unsigned int prot DFL(PROT_READ | PROT_WRITE | PROT_SHARED),
         unsigned int flags DFL(0),
         struct mfile *__restrict file DFL(&mfile_zero),
         struct path *file_fspath DFL(__NULLPTR),
         struct fdirent *file_fsname DFL(__NULLPTR),
         pos_t file_pos DFL(0),
         size_t min_alignment DFL(PAGESIZE),
         ptrdiff_t min_alignment_offset DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS);
#if 0
mman_map(/* self:        */ self,
         /* hint:        */ hint,
         /* num_bytes:   */ num_bytes,
         /* prot:        */ prot,
         /* flags:       */ flags,
         /* file:        */ file,
         /* file_fspath: */ file_fspath,
         /* file_fsname: */ file_fsname,
         /* file_pos:    */ file_pos);
#endif


/* Same as `mman_map()', but only allow pages entirely contained  within
 * the file-relative address range `file_map_minaddr...file_map_maxaddr'
 * to be mapped. Attempting to map file contents beyond this range  will
 * instead result in `&mfile_zero' getting mapped instead.
 * This function is mainly used to  restrict access to raw physical  memory
 * when user-space is allowed to directly mmap() device ram, but the driver
 * want's to prevent user-space from mapping more than the physical address
 * ranges actually associated with a device. */
FUNDEF BLOCKING_IF(flags & MAP_POPULATE) NONNULL((1, 6)) void *KCALL
mman_map_subrange(struct mman *__restrict self,
                  UNCHECKED void *hint, size_t num_bytes,
                  unsigned int prot DFL(PROT_READ | PROT_WRITE | PROT_SHARED),
                  unsigned int flags DFL(0),
                  struct mfile *__restrict file DFL(&mfile_zero),
                  struct path *file_fspath DFL(__NULLPTR),
                  struct fdirent *file_fsname DFL(__NULLPTR),
                  pos_t file_pos DFL(0),
                  pos_t file_map_minaddr DFL(0),
                  pos_t file_map_maxaddr DFL((pos_t)-1),
                  size_t min_alignment DFL(PAGESIZE),
                  ptrdiff_t min_alignment_offset DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS);


/* Same  as  `mman_map()',  but  instead  of  actually  mapping  something,  leave the
 * address range as empty (but possibly prepared), making it a reserved address range.
 * @param: flags: Set of `MAP_PREPARED' (Other bits are silently ignored)
 *                Additionally,  the  usual   bits  relating  to   `mman_findunmapped()'  are   accepted:
 *                `MAP_FIXED | MAP_32BIT | MAP_GROWSDOWN | MAP_GROWSUP | MAP_STACK | MAP_FIXED_NOREPLACE' */
FUNDEF NONNULL((1)) void *KCALL
mman_map_res(struct mman *__restrict self,
             UNCHECKED void *hint, size_t num_bytes,
             unsigned int flags DFL(0),
             size_t min_alignment DFL(PAGESIZE),
             ptrdiff_t min_alignment_offset DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
		       E_BADALLOC_ADDRESS_ALREADY_EXISTS);


/* Flags for `mman_unmap()' and `mman_protect()' */
#define MMAN_UNMAP_FAULTIFUNUSED 0x0001 /* Throw an  `E_SEGFAULT_UNMAPPED' exception  with  the lowest  address  of
                                         * the  first segment of memory apart of  the given range that isn't mapped
                                         * to some node that's allowed to be unmapped. This check is done such that
                                         * it happens before any memory may get unmapped, meaning that when  given,
                                         * the function will only succeed when the entire range can be unmapped  at
                                         * once, and  fail with  an E_SEGFAULT  otherwise. When  not set,  unmapped
                                         * portions of the given address range are silently ignored. */
#define MMAN_UNMAP_NOSPLIT       0x0002 /* Don't split nodes in order to be  able to partially unmap one of  them.
                                         * Instead, only unmap whole nodes, or nothing at all. When set, all nodes
                                         * that overlap with the given address address range will be unmapped.
                                         * NOTE: When  this flag  isn't given, and  an attempt is  made to unmap
                                         *       node with the `MNODE_F_NOSPLIT' flag  set, then the node  won't
                                         *       be split, but the affected address range is expanded to include
                                         *       that node in its entirety, the same way this would also be done
                                         *       had the `MMAN_UNMAP_NOSPLIT' been given. */
#define MMAN_UNMAP_NOKERNPART    0x0004 /* Instead of causing kernel  panic when attempting to  unmap
                                         * a kernel part, simply ignore the request (this flag is set
                                         * when user-space tries to unmap memory) */

/* Unmap all memory mappings within the given address range.
 * The actual range is widened to include all whole pages that overlap the given range.
 * @param: addr:      The base address at which to start unmapping memory.
 * @param: num_bytes: The # of continuous bytes of memory to unmap, starting at `addr'
 * @param: flags:     Set of `MMAN_UNMAP_*'
 * @return: * :       The actual # of unmapped bytes of memory. */
FUNDEF NONNULL((1)) size_t KCALL
mman_unmap(struct mman *__restrict self,
           UNCHECKED void *addr, size_t num_bytes,
           unsigned int flags DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);



/* Update access protection flags within the given address range.
 * @param: addr:      The base address at which to start changing protection.
 * @param: num_bytes: The number of continuous bytes of memory to change, starting at `addr'
 * @param: prot_mask: Mask of protection bits that should be kept (Set of `PROT_EXEC | PROT_WRITE | PROT_READ').
 *                    Other bits are silently ignored.
 * @param: prot_more: Set of protection bits that should be added (Set of `PROT_EXEC | PROT_WRITE | PROT_READ').
 *                    Other bits are silently ignored.
 * @param: flags:     Set of `MMAN_UNMAP_*'
 * @return: * :       The actual # of (possibly) altered bytes of memory. */
FUNDEF NONNULL((1)) size_t KCALL
mman_protect(struct mman *__restrict self,
             UNCHECKED void *addr, size_t num_bytes,
             unsigned int prot_mask, unsigned int prot_more,
             unsigned int flags DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MAP_H */
