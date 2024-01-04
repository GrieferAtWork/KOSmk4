/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_ENUM_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_ENUM_H 1

#include <kernel/compiler.h>

#include <kernel/mman/mpart.h>
#include <kernel/paging.h>
#include <kernel/types.h>

#include <kos/kernel/paging.h> /* USERSPACE_END, USERSPACE_START */

#ifdef __CC__
DECL_BEGIN

/* Mask of MNODE_F_* flags found in `struct mmapinfo::mmi_flags' */
#define MMAPINFO_FLAGS_MASK                               \
	(MNODE_F_PMASK | MNODE_F_SHARED | MNODE_F_MPREPARED | \
	 MNODE_F_MHINT | MNODE_F_MLOCK | MNODE_F_NOSPLIT |    \
	 MNODE_F_NOMERGE)


struct mmapinfo {
	/* VM Memory mapping information (as passed to `mman_enum_callback_t') */
	UNCHECKED void     *mmi_min;    /* Address of the lowest mapped byte */
	UNCHECKED void     *mmi_max;    /* [> mmi_min] Address of the greatest mapped byte */
	uintptr_t           mmi_flags;  /* Mem-node flags (Set of flags from `MMAPINFO_FLAGS_MASK'). */
	REF struct mfile   *mmi_file;   /* [0..1] Mapped mem-file (or `NULL' of reserved memory mappings) */
	pos_t               mmi_offset; /* [valid_if(mmi_file)] Byte-offset into `mmi_file', where the mapping at `mmi_min' starts. */
	REF struct path    *mmi_fspath; /* [0..1] Mapped object filesystem path (or NULL if unknown or N/A) */
	REF struct fdirent *mmi_fsname; /* [0..1] Mapped object filesystem name (or NULL if unknown or N/A) */
	void              *_mmi_node;   /* [1..1] Address of the first mem-node apart of this range (!!DONT DEREF!!)
	                                 * This  address is only used by procfs to assign unique INO values to links
	                                 * in `/proc/[pid]/map_files/...' */
};
#define mmapinfo_size(self) \
	((size_t)((byte_t *)(self)->mmi_max - (byte_t *)(self)->mmi_min) + 1)
#define mmapinfo_fini(self)                \
	(xdecref_unlikely((self)->mmi_file),   \
	 xdecref_unlikely((self)->mmi_fspath), \
	 xdecref_unlikely((self)->mmi_fsname))


/* Callback for `mman_enum()'
 * @param: arg:   The argument (cookie) originally passed to `mman_enum()'
 * @param: info:  Information about the mapping range being enumerated.
 * @return: >= 0: Continue enumeration and add the result to the sum eventually returned by `mman_enum()'
 * @return: < 0:  Halt enumeration immediately by having `mman_enum()' re-return this same value. */
typedef BLOCKING ssize_t
(FCALL *mman_enum_callback_t)(void *arg, struct mmapinfo *__restrict info);

/* Enumerate all mappings contained within the given `enum_minaddr...enum_maxaddr'
 * address range within the given VM `self'. This function will automatically  re-
 * assemble  memory mappings that  had previously been  split into multiple nodes,
 * such that adjacent  `struct mnode's that describe  a contiguous memory  mapping
 * do not appear as individual, separate nodes.
 * @param: cb:           A callback  that  should  be  invoked for  every  mapped  memory  region
 *                       contained with the given address range `enum_minaddr' ... `enum_maxaddr'
 *                       The  sum of return  values returned by this  callback will eventually be
 *                       returned by this function, unless `cb()' returns a negative value, which
 *                       will  cause enumeration to  halt immediately, and that  same value to be
 *                       propagated to the caller.
 *                       Note that mappings are enumerated  in strictly ascending order, and  that
 *                       this function guaranties that even in the modifications being made to the
 *                       given `self' while enumeration takes  place, the `mmi_min' of all  future
 *                       mappings will always be `> mmi_max' of every already/currently enumerated
 *                       mapping.
 * @param: arg:          An argument (cookie) to-be passed to `cb()'
 * @param: enum_minaddr: The starting address of mappings to-be enumerated, such that any mapping
 *                       that overlap  with `enum_minaddr ... enum_maxaddr'  will be  enumerated.
 * @param: enum_maxaddr: Same as `enum_minaddr', but specifies the max address of any enumerated
 *                       mapping. */
FUNDEF BLOCKING_IF(BLOCKING(cb)) NONNULL((1, 2)) ssize_t KCALL
mman_enum(struct mman *__restrict self, mman_enum_callback_t cb, void *arg,
          UNCHECKED void *enum_minaddr DFL((UNCHECKED void *)0),
          UNCHECKED void *enum_maxaddr DFL((UNCHECKED void *)-1))
		THROWS(E_WOULDBLOCK);

/* Enumerate all of userspace. */
#ifdef USERSPACE_END
#define mman_enum_userspace(self, cb, arg) \
	mman_enum(self, cb, arg,               \
	          (UNCHECKED void *)0,         \
	          (UNCHECKED void *)(USERSPACE_END - 1))
#else /* USERSPACE_END */
#define mman_enum_userspace(self, cb, arg)       \
	mman_enum(self, cb, arg,                     \
	          (UNCHECKED void *)USERSPACE_START, \
	          (UNCHECKED void *)-1);
#endif /* !USERSPACE_END */


/* Lookup information about the mapping at `addr' and write that information to `*info'
 * Upon success, the caller must `mmapinfo_fini(info);'
 * @return: true:  Success: mapping information was stored in `*info'
 * @return: false: No mapping exists at `addr' */
FUNDEF WUNUSED NONNULL((1, 2)) __BOOL KCALL
mman_mapinfo(struct mman *__restrict self,
             struct mmapinfo *__restrict info,
             UNCHECKED void *addr)
		THROWS(E_WOULDBLOCK);

/* Return map information for the first node with a base-address `>= addr'
 * Upon success, the caller must `mmapinfo_fini(info);'
 * @return: true:  Success: mapping information was stored in `*info'
 * @return: false: No mapping exists at `addr' */
FUNDEF WUNUSED NONNULL((1, 2)) __BOOL KCALL
mman_mapinfo_above(struct mman *__restrict self,
                   struct mmapinfo *__restrict info,
                   UNCHECKED void *addr)
		THROWS(E_WOULDBLOCK);


struct mmapinfo_ex
#ifdef __cplusplus
    : mmapinfo                    /* Basic info */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct mmapinfo mmix_info;    /* Basic info */
#endif /* !__cplusplus */
	size_t          mmix_locked;  /* Total number of bytes belonging to parts with `MPART_F_MLOCK' set */
	size_t          mmix_alloc;   /* Total number of bytes mapped by parts not set to `MPART_ST_VOID' */
	size_t          mmix_loaded;  /* Total number of bytes within the range marked as `MPART_BLOCK_ST_LOAD' or `MPART_BLOCK_ST_CHNG' */
	size_t          mmix_changed; /* Total number of bytes within the range marked as `MPART_BLOCK_ST_CHNG' */
	size_t          mmix_swap;    /* Total number of bytes within the range marked as `MPART_BLOCK_ST_CHNG' and backed by `MPART_ST_SWP[_SC]' */
};


/* Callback for `mman_enum_ex()'
 * @param: arg:   The argument (cookie) originally passed to `mman_enum_ex()'
 * @param: info:  Information about the mapping range being enumerated.
 * @return: >= 0: Continue enumeration and add the result to the sum eventually returned by `mman_enum_ex()'
 * @return: < 0:  Halt enumeration immediately by having `mman_enum_ex()' re-return this same value. */
typedef BLOCKING ssize_t
(FCALL *mman_enum_ex_callback_t)(void *arg, struct mmapinfo_ex *__restrict info);

/* Same as `mman_enum()', but provide some more (additional) accounting info about mappings. */
FUNDEF BLOCKING_IF(BLOCKING(cb)) NONNULL((1, 2)) ssize_t KCALL
mman_enum_ex(struct mman *__restrict self, mman_enum_ex_callback_t cb, void *arg,
             UNCHECKED void *enum_minaddr DFL((UNCHECKED void *)0),
             UNCHECKED void *enum_maxaddr DFL((UNCHECKED void *)-1))
		THROWS(E_WOULDBLOCK);

/* Enumerate all of userspace. */
#ifdef USERSPACE_END
#define mman_enum_userspace_ex(self, cb, arg) \
	mman_enum_ex(self, cb, arg,               \
	             (UNCHECKED void *)0,         \
	             (UNCHECKED void *)(USERSPACE_END - 1))
#else /* USERSPACE_END */
#define mman_enum_userspace_ex(self, cb, arg)       \
	mman_enum_ex(self, cb, arg,                     \
	             (UNCHECKED void *)USERSPACE_START, \
	             (UNCHECKED void *)-1);
#endif /* !USERSPACE_END */


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_ENUM_H */
