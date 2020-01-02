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
#ifndef _KOS_HOP_H
#define _KOS_HOP_H 1

#include <__stdinc.h>
#include <__crt.h>
#include <bits/types.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#if defined(__KERNEL__) && __SIZEOF_SIZE_T__ < 8
#define __HOP_SIZE64_FIELD(name) union { __size_t name; __uint64_t __##name##64; }
#else /* __KERNEL__ */
/* For compatibility, user-space must always write the full 64-bit field,
 * while the kernel will only ever read a size_t-sized field.
 * This is required when a 32-bit application is running under a 64-bit kernel,
 * allowing the kernel to not have to look out for user-space running in
 * compatibility mode, but can instead always read the full 64-bit value,
 * with is simply zero-extended from 32-bit by user-space. */
#define __HOP_SIZE64_FIELD(name) __uint64_t name
#endif /* !__KERNEL__ */

/* Special HandleOPeration control codes for extended handle types.
 * These are function codes with may be used alongside the `hop()'
 * system call provided by the KOSmk4 kernel.
 * WARNING: The interface exposed here is _extremely_ volatile!
 *          It may be changed without notice, get removed, or changed in other
 *          ways that may break existing code using it. - Use with caution!
 * WARNING: All padding data must be initialized to zero by user-space! */


#if __SIZEOF_POINTER__ < 8
#define __HOP_PAD_POINTER(name) __uint32_t name;
#else /* __SIZEOF_POINTER__ < 8 */
#define __HOP_PAD_POINTER(name) /* nothing */
#endif /* __SIZEOF_POINTER__ >= 8 */

#ifndef __hop_openfd_defined
#define __hop_openfd_defined 1
#define HOP_OPENFD_MODE_AUTO       0x0000 /* Ignore `of_hint' and automatically select an appropriate handle
                                           * This is the same as `HOP_OPENFD_MODE_HINT' with `of_hint=0' */
#define HOP_OPENFD_MODE_HINT       0x0001 /* Install the newly opened handle into the lowest unused handle that is `>= of_hint' */
#define HOP_OPENFD_MODE_INTO       0x0002 /* Install the newly opened handle into `of_hint', automatically
                                           * closing any handle that may have been stored inside before.
                                           * Additionally, `of_hint' may be any writable symbolic handle */
#define HOP_OPENFD_MODE_INTO_EXACT 0x0003 /* Same as `HOP_OPENFD_MODE_INTO', but don't recognize symbolic
                                           * handles, and throw an `E_INVALID_HANDLE_FILE' error instead. */
#define __OFFSET_HOP_OPENFD_MODE  0
#define __OFFSET_HOP_OPENFD_FLAGS 2
#define __OFFSET_HOP_OPENFD_HINT  4
#define __SIZEOF_HOP_OPENFD       8
#ifdef __CC__
struct hop_openfd /*[PREFIX(of_)]*/ {
	__uint16_t of_mode;  /* Open mode (One of `HOP_OPENFD_MODE_*') */
	__uint16_t of_flags; /* Set of `IO_CLOEXEC|IO_CLOFORK' */
	__uint32_t of_hint;  /* [IN]  Open hint (s.a. `HOP_OPENFD_MODE_INTO')
	                      * [OUT] The ID of the handle that has been opened (must be close(2)'ed). */
};
#endif /* __CC__ */
#endif /* !__hop_openfd_defined */


#define __OFFSET_HOP_HANDLE_STAT_STRUCT_SIZE 0
#define __OFFSET_HOP_HANDLE_STAT_MODE        4
#define __OFFSET_HOP_HANDLE_STAT_TYPE        8
#define __OFFSET_HOP_HANDLE_STAT_KIND        10
#define __OFFSET_HOP_HANDLE_STAT_REFCNT      16
#define __OFFSET_HOP_HANDLE_STAT_ADDRESS     24
#define __OFFSET_HOP_HANDLE_STAT_TYPENAME    32
#define __SIZEOF_HOP_HANDLE_STAT             64
#ifdef __CC__
struct hop_handle_stat /*[PREFIX(hs_)]*/ {
	__uint32_t            hs_struct_size;  /* [== sizeof(struct hop_handle_stat)]
	                                        * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                        * this value is too small or doesn't match any recognized
	                                        * structure version. */
	__uint16_t            hs_mode;         /* The I/O mode with which this handle operates (set of `IO_*'). */
	__uint16_t          __hs_pad1;         /* ... */
	__uint16_t            hs_type;         /* The handle type (one of `HANDLE_TYPE_*'). */
	__uint16_t            hs_kind;         /* The handle kind (one of `HANDLE_TYPEKIND_*'). */
	__uint32_t          __hs_pad2;         /* ... */
	__uintptr_t           hs_refcnt;       /* Reference counter of this handle. */
	__HOP_PAD_POINTER  (__hs_pad3)         /* ... */
	__uint64_t            hs_address;      /* Kernel-space pointer to the address where data of this handle is stored.
	                                        * Note: Do not rely on this actually being the proper address when interfacing
	                                        *       with custom drivers (as a matter of fact: custom drivers should never
	                                        *       blindly trust kernel-space pointers passed from user-space, and should
	                                        *       always instead make use of handles to kernel-space objects).
	                                        *       Anyways: the kernel is allowed to mangle the actual address however
	                                        *                it pleases, so-long as the value stored here ends up being
	                                        *                unique. */
	char                  hs_typename[32]; /* The name of the handle's type. */
};
#endif /* __CC__ */


#define HOP_DATABLOCK_STAT_FEATURE_NONE    0x00000000 /* No special features. */
#define HOP_DATABLOCK_STAT_FEATURE_ISANON  0x00000001 /* The datablock only carries anonymous parts. */
#define HOP_DATABLOCK_STAT_FEATURE_ISEMPTY 0x00000002 /* The datablock doesn't carry any parts at the moment. */
#define HOP_DATABLOCK_STAT_FEATURE_ISVIO   0x00000010 /* The datablock implements VIO. */
#define HOP_DATABLOCK_STAT_FEATURE_INIT    0x00000020 /* The datablock provides a custom init function */
#define HOP_DATABLOCK_STAT_FEATURE_LOAD    0x00000040 /* The datablock provides a custom load function */
#define HOP_DATABLOCK_STAT_FEATURE_SAVE    0x00000080 /* The datablock provides a custom save function */
#define HOP_DATABLOCK_STAT_FEATURE_CHANGE  0x00000100 /* The datablock provides a custom changed-callback */
#define __OFFSET_HOP_DATABLOCK_STAT_STRUCT_SIZE          0
#define __OFFSET_HOP_DATABLOCK_STAT_FEATURES             4
#define __OFFSET_HOP_DATABLOCK_STAT_PAGESHIFT            8
#define __OFFSET_HOP_DATABLOCK_STAT_PART_MAPPED          16
#define __OFFSET_HOP_DATABLOCK_STAT_PART_MAPPED_PAGES    24
#define __OFFSET_HOP_DATABLOCK_STAT_PART_ST_INCORE       32
#define __OFFSET_HOP_DATABLOCK_STAT_PART_ST_INCORE_PAGES 40
#define __OFFSET_HOP_DATABLOCK_STAT_PART_ST_LOCKED       48
#define __OFFSET_HOP_DATABLOCK_STAT_PART_ST_LOCKED_PAGES 56
#define __OFFSET_HOP_DATABLOCK_STAT_PART_ST_INSWAP       64
#define __OFFSET_HOP_DATABLOCK_STAT_PART_ST_INSWAP_PAGES 72
#define __OFFSET_HOP_DATABLOCK_STAT_PART_F_LOCKED        80
#define __OFFSET_HOP_DATABLOCK_STAT_PART_F_LOCKED_PAGES  88
#define __OFFSET_HOP_DATABLOCK_STAT_PART_F_CHANGED       96
#define __OFFSET_HOP_DATABLOCK_STAT_PART_F_CHANGED_PAGES 104
#define __OFFSET_HOP_DATABLOCK_STAT_PART_RAM_BLOCKS      112
#define __OFFSET_HOP_DATABLOCK_STAT_PART_SWAP_BLOCKS     120
#define __OFFSET_HOP_DATABLOCK_STAT_PART_UNINIT_PAGES    128
#define __OFFSET_HOP_DATABLOCK_STAT_PART_INIT_PAGES      136
#define __OFFSET_HOP_DATABLOCK_STAT_PART_CHANGED_PAGES   144
#define __SIZEOF_HOP_DATABLOCK_STAT                      152
#ifdef __CC__
struct hop_datablock_stat /*[PREFIX(ds_)]*/ {
	__uint32_t   ds_struct_size;          /* [== sizeof(struct hop_datablock_stat)]
	                                       * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                       * this value is too small or doesn't match any recognized
	                                       * structure version. */
	__uint32_t   ds_features;             /* Set of `HOP_DATABLOCK_STAT_FEATURE_*' */
	__uint32_t   ds_pageshift;            /* `struct vm_datablock::db_pageshift'
	                                       * NOTE: Used to convert to/from data-pages and physical/virtual memory pages
	                                       * HINT: VIRT_PAGE == DATA_PAGE << ds_pageshift
	                                       *       DATA_PAGE == VIRT_PAGE >> ds_pageshift */
	__uint32_t __ds_pad;                  /* ... */
	__uint64_t   ds_part_mapped;          /* The number of parts chained via `struct vm_datablock::db_parts' */
	__uint64_t   ds_part_mapped_pages;    /* Sum of `vm_datapart_numdpages()' of all mapped parts */
	__uint64_t   ds_part_st_incore;       /* The number of VM_DATAPART_STATE_INCORE-parts chained via `struct vm_datablock::db_parts' */
	__uint64_t   ds_part_st_incore_pages; /* Sum of `vm_datapart_numdpages()' of all VM_DATAPART_STATE_INCORE parts */
	__uint64_t   ds_part_st_locked;       /* The number of VM_DATAPART_STATE_LOCKED-parts chained via `struct vm_datablock::db_parts' */
	__uint64_t   ds_part_st_locked_pages; /* Sum of `vm_datapart_numdpages()' of all VM_DATAPART_STATE_LOCKED parts */
	__uint64_t   ds_part_st_inswap;       /* The number of VM_DATAPART_STATE_INSWAP-parts chained via `struct vm_datablock::db_parts' */
	__uint64_t   ds_part_st_inswap_pages; /* Sum of `vm_datapart_numdpages()' of all VM_DATAPART_STATE_INSWAP parts */
	__uint64_t   ds_part_f_locked;        /* Number of parts with the `VM_DATAPART_FLAG_LOCKED' flag set */
	__uint64_t   ds_part_f_locked_pages;  /* Sum of `vm_datapart_numdpages()' of all parts with the `VM_DATAPART_FLAG_LOCKED' flag set */
	__uint64_t   ds_part_f_changed;       /* Number of parts with the `VM_DATAPART_FLAG_CHANGED' flag set */
	__uint64_t   ds_part_f_changed_pages; /* Sum of `vm_datapart_numdpages()' of all parts with the `VM_DATAPART_FLAG_CHANGED' flag set */
	__uint64_t   ds_part_ram_blocks;      /* Total number of individual RAM blocks allocated by INCORE/LOCKED parts */
	__uint64_t   ds_part_swap_blocks;     /* Total number of SWAP blocks allocated by INSWAP parts */
	__uint64_t   ds_part_uninit_pages;    /* Total number of data-pages set to `VM_DATAPART_PPP_UNINITIALIZED' */
	__uint64_t   ds_part_init_pages;      /* Total number of data-pages set to `VM_DATAPART_PPP_INITIALIZED' */
	__uint64_t   ds_part_changed_pages;   /* Total number of data-pages set to `VM_DATAPART_PPP_HASCHANGED' */
};
#endif /* __CC__ */

#define __OFFSET_HOP_DATABLOCK_SYNCPAGES_STRUCT_SIZE 0
#define __OFFSET_HOP_DATABLOCK_SYNCPAGES_MINPAGE     8
#define __OFFSET_HOP_DATABLOCK_SYNCPAGES_MAXPAGE     16
#define __OFFSET_HOP_DATABLOCK_SYNCPAGES_COUNT       24
#define __SIZEOF_HOP_DATABLOCK_SYNCPAGES             32
#ifdef __CC__
struct hop_datablock_syncpages /*[PREFIX(dsp_)]*/ {
	__uint32_t        dsp_struct_size; /* [== sizeof(struct hop_datablock_syncpages)]
	                                    * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                    * this value is too small or doesn't match any recognized
	                                    * structure version. */
	__uint32_t      __dsp_pad;         /* ... */
	__uint64_t        dsp_minpage;     /* [IN] Index of the lowest data page that should be synced. */
	__uint64_t        dsp_maxpage;     /* [IN] Index of the greatest data page that should be synced. */
	__uint64_t        dsp_count;       /* [OUT] Number of synced data pages (pages that had been modified). */
};
#endif /* __CC__ */

#define __OFFSET_HOP_DATABLOCK_SYNCBYTES_STRUCT_SIZE 0
#define __OFFSET_HOP_DATABLOCK_SYNCBYTES_MINBYTE     8
#define __OFFSET_HOP_DATABLOCK_SYNCBYTES_MAXBYTE     16
#define __OFFSET_HOP_DATABLOCK_SYNCBYTES_COUNT       24
#define __SIZEOF_HOP_DATABLOCK_SYNCBYTES             32
#ifdef __CC__
struct hop_datablock_syncbytes /*[PREFIX(dsb_)]*/ {
	__uint32_t        dsb_struct_size; /* [== sizeof(struct hop_datablock_syncpages)]
	                                    * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                    * this value is too small or doesn't match any recognized
	                                    * structure version. */
	__uint32_t      __dsb_pad;         /* ... */
	/* NOTE: `bsr_minbyte' and `bsr_maxbyte' are simply adjusted such that
	 *        they span whole data pages, meaning that `bsr_count' will always
	 *        be a multiple of `getpagesize() >> [HOP_DATABLOCK_STAT]:ds_pageshift',
	 *        and may be greater than the total number of bytes between `bsr_minbyte'
	 *        and `bsr_maxbyte'. */
	__uint64_t        dsb_minbyte;     /* [IN] Offset of the lowest byte that should be synced. */
	__uint64_t        dsb_maxbyte;     /* [IN] Offset of the greatest byte that should be synced. */
	__uint64_t        dsb_count;       /* [OUT] Number of synced data pages (pages that had been modified). */
};
#endif /* __CC__ */

#define __OFFSET_HOP_DATABLOCK_OPENPART_STRUCT_SIZE 0
#define __OFFSET_HOP_DATABLOCK_OPENPART_PAGENO      8
#define __OFFSET_HOP_DATABLOCK_OPENPART_PAGES_HINT  16
#define __OFFSET_HOP_DATABLOCK_OPENPART_OPENFD      24
#define __SIZEOF_HOP_DATABLOCK_OPENPART             32
#ifdef __CC__
struct hop_datablock_openpart /*[PREFIX(dop_)]*/ {
	__uint32_t        dop_struct_size; /* [== sizeof(struct hop_datablock_openpart)]
	                                    * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                    * this value is too small or doesn't match any recognized
	                                    * structure version. */
	__uint32_t      __dop_pad;         /* ... */
	__uint64_t        dop_pageno;      /* [IN]  The page-index (vm_vpage64_t) of the first page that should be opened.
	                                    * [OUT] The page-index (vm_vpage64_t) of the first page that was opened.
	                                    *       This is equal to the `ds_minpage' field return by `HOP_DATAPART_STAT',
	                                    *       and may be lower than the originally given `dop_pageno' when
	                                    *       `HOP_DATABLOCK_OPEN_PART' was used, but guarantied to be equal to the
	                                    *       original value when `HOP_DATABLOCK_OPEN_PART_EXACT' was used. */
	__uint64_t        dop_pages_hint;  /* [IN]  Hint for the number of pages across which the part should span. */
	struct hop_openfd dop_openfd;      /* File descriptor open controller (filled with a handle for the part). */
};
#endif /* __CC__ */


#define HOP_DATABLOCK_HASCHANGED_FLAG_UNCHANGED 0x0000 /* No changes were made */
#define HOP_DATABLOCK_HASCHANGED_FLAG_DIDCHANGE 0x0001 /* Changes have been found */
#define __OFFSET_HOP_DATABLOCK_HASCHANGED_STRUCT_SIZE 0
#define __OFFSET_HOP_DATABLOCK_HASCHANGED_MINBYTE     8
#define __OFFSET_HOP_DATABLOCK_HASCHANGED_MAXBYTE     16
#define __SIZEOF_HOP_DATABLOCK_HASCHANGED             24
#ifdef __CC__
struct hop_datablock_haschanged /*[PREFIX(dhc_)]*/ {
	__uint32_t        dhc_struct_size; /* [== sizeof(struct hop_datablock_haschanged)]
	                                    * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                    * this value is too small or doesn't match any recognized
	                                    * structure version. */
	__uint32_t        dhc_result;      /* [OUT] Set to a set of `HOP_DATABLOCK_HASCHANGED_FLAG_*'. */
	__uint64_t        dhc_minbyte;     /* [IN] Lowest byte to check for changes */
	__uint64_t        dhc_maxbyte;     /* [IN] Greatest byte to check for changes */
};
#endif /* __CC__ */


#define __OFFSET_HOP_DATABLOCK_OPEN_FUTEX_STRUCT_SIZE 0
#define __OFFSET_HOP_DATABLOCK_OPEN_FUTEX_ADDRESS     8
#define __OFFSET_HOP_DATABLOCK_OPEN_FUTEX_OPENFD      16
#define __SIZEOF_HOP_DATABLOCK_OPEN_FUTEX             24
#ifdef __CC__
struct hop_datablock_open_futex /*[PREFIX(dof_)]*/ {
	__uint32_t          dof_struct_size; /* [== sizeof(struct hop_datablock_open_futex)]
	                                      * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                      * this value is too small or doesn't match any recognized
	                                      * structure version. */
	__uint32_t        __dof_pad1;        /* ... */
	__uint64_t          dof_address;     /* [IN] Address of the futex */
	struct hop_openfd   dof_openfd;      /* File descriptor open controller (filled with a handle for the futex). */
};
#endif /* __CC__ */


#ifndef BLOCK_DEVICE_FLAG_NORMAL
#define BLOCK_DEVICE_FLAG_NORMAL    0x0000 /* Normal block-device flags. */
#define BLOCK_DEVICE_FLAG_READONLY  0x0001 /* Read-only device / partition (attempting to write will cause `E_IOERROR_READONLY' to be thrown). */
#define BLOCK_DEVICE_FLAG_PARTITION 0x8000 /* [const] This one's a partition */
#endif /* !BLOCK_DEVICE_FLAG_NORMAL */

#define __OFFSET_HOP_BLOCKDEVICE_STAT_STRUCT_SIZE  0
#define __OFFSET_HOP_BLOCKDEVICE_STAT_TOTAL_BYTES  8
#define __OFFSET_HOP_BLOCKDEVICE_STAT_SECTOR_COUNT 16
#define __OFFSET_HOP_BLOCKDEVICE_STAT_SECTOR_SIZE  24
#define __OFFSET_HOP_BLOCKDEVICE_STAT_DEVICE_FLAG  32
#define __OFFSET_HOP_BLOCKDEVICE_STAT_DEVNO        36
#define __OFFSET_HOP_BLOCKDEVICE_STAT_PARTCOUNT    40
#define __OFFSET_HOP_BLOCKDEVICE_STAT_NAME         44
#define __SIZEOF_HOP_BLOCKDEVICE_STAT              128
#ifdef __CC__
struct hop_blockdevice_stat /*[PREFIX(bs_)]*/ {
	__uint32_t   bs_struct_size;   /* [== sizeof(struct hop_blockdevice_stat)]
	                                * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                * this value is too small or doesn't match any recognized
	                                * structure version. */
	__uint32_t __bs_pad;           /* ... */
	__uint64_t   bs_total_bytes;   /* Total number of bytes available. */
	__uint64_t   bs_sector_count;  /* Total number of sectors available. */
	__uint64_t   bs_sector_size;   /* Size of a single sector (in bytes). */
	__uint32_t   bs_device_flag;   /* Active device flags (Set of `BD_F*').
	                                * NOTE: If this device is a partition, the `BLOCK_DEVICE_FLAG_PARTITION' bit is set */
	__uint32_t   bs_devno;         /* Device number (`dev_t') */
	__uint32_t   bs_partcount;     /* Number of child partitions of thsi block device. */
	char         bs_name[84];      /* Name of the device (as used for the auto-node that may appear in `/dev') */
};
#endif /* __CC__ */

#define __OFFSET_HOP_BLOCKDEVICE_OPENPART_STRUCT_SIZE 0
#define __OFFSET_HOP_BLOCKDEVICE_OPENPART_PARTNO      4
#define __OFFSET_HOP_BLOCKDEVICE_OPENPART_OPENFD      8
#define __SIZEOF_HOP_BLOCKDEVICE_OPENPART             16
#ifdef __CC__
struct hop_blockdevice_openpart /*[PREFIX(bop_)]*/ {
	__uint32_t        bop_struct_size; /* [== sizeof(struct hop_blockdevice_openpart)]
	                                    * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                    * this value is too small or doesn't match any recognized
	                                    * structure version. */
	__uint32_t        bop_partno;      /* Total number of bytes available. */
	struct hop_openfd bop_openfd;      /* File descriptor open controller. */
};
#endif /* __CC__ */

#define __OFFSET_HOP_INODE_CHMOD_STRUCT_SIZE 0
#define __OFFSET_HOP_INODE_CHMOD_PERM_MASK   4
#define __OFFSET_HOP_INODE_CHMOD_PERM_FLAG   8
#define __OFFSET_HOP_INODE_CHMOD_PERM_OLD    12
#define __SIEZOF_HOP_INODE_CHMOD             16
#ifdef __CC__
struct hop_inode_chmod /*[PREFIX(icm_)]*/ {
	__uint32_t            icm_struct_size; /* [== sizeof(struct hop_inode_chmod)]
	                                        * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                        * this value is too small or doesn't match any recognized
	                                        * structure version. */
	/* Atomically change INode permissions:
	 * >> icm_perm_old = OLD_PERM;
	 * >> SET_PERM((OLD_PERM & icm_perm_mask) | icm_perm_flag); */
	__uint32_t            icm_perm_mask;   /* [IN] The mask with which to and'd (&) old permissions. */
	__uint32_t            icm_perm_flag;   /* [IN] Flag which should be or'd (|) to old permissions. */
	__uint32_t            icm_perm_old;    /* [OUT] The old INode permissions. */
};
#endif /* __CC__ */

#define __OFFSET_HOP_INODE_CHOWN_STRUCT_SIZE 0
#define __OFFSET_HOP_INODE_CHOWN_NEWOWNER    4
#define __OFFSET_HOP_INODE_CHOWN_NEWGROUP    8
#define __OFFSET_HOP_INODE_CHOWN_OLDOWNER    12
#define __OFFSET_HOP_INODE_CHOWN_OLDGROUP    16
#define __SIEZOF_HOP_INODE_CHOWN             20
#ifdef __CC__
struct hop_inode_chown /*[PREFIX(ico_)]*/ {
	__uint32_t            ico_struct_size; /* [== sizeof(struct hop_inode_chown)]
	                                        * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                        * this value is too small or doesn't match any recognized
	                                        * structure version. */
	/* Atomically change INode ownership and store the old owner information */
	__uint32_t            ico_newowner;    /* [IN] The new owner that should be assigned. */
	__uint32_t            ico_newgroup;    /* [IN] The new group that should be assigned. */
	__uint32_t            ico_oldowner;    /* [OUT] The old owner that got overwritten. */
	__uint32_t            ico_oldgroup;    /* [OUT] The old group that got overwritten. */
};
#endif /* __CC__ */


#define HOP_DIRECTORY_OPENNODE_FNORMAL 0x0000 /* Perform a normal child lookup */
#define HOP_DIRECTORY_OPENNODE_FNOCASE 0x8000 /* Ignore casing during the lookup */
#define __OFFSET_HOP_DIRECTORY_OPENNODE_STRUCT_SIZE 0
#define __OFFSET_HOP_DIRECTORY_OPENNODE_NAME        8
#define __OFFSET_HOP_DIRECTORY_OPENNODE_LEN         16
#define __OFFSET_HOP_DIRECTORY_OPENNODE_FLAGS       18
#define __OFFSET_HOP_DIRECTORY_OPENNODE_NODE        24
#define __OFFSET_HOP_DIRECTORY_OPENNODE_DENT        32
#define __SIZEOF_HOP_DIRECTORY_OPENNODE             40
#ifdef __CC__
struct hop_directory_opennode /*[PREFIX(don_)]*/ {
	__uint32_t            don_struct_size; /* [== sizeof(struct hop_directory_opennode)]
	                                        * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                        * this value is too small or doesn't match any recognized
	                                        * structure version. */
	__uint32_t          __don_pad1;        /* ... */
	/* Open the INode/Directory entry of a given child of some directory.
	 * WARNING: This function does not follow symbolic links, understands
	 *          the special paths `.' and `..', or will even traverse more
	 *          than a single directory component (aka. no slashes)
	 *          These are the low-level functions used to lookup a child
	 *          entry within some given directory. */
	char const           *don_name;        /* [IN][1..don_len] Name of the child to lookup */
	__HOP_PAD_POINTER  (__don_pad2)        /* ... */
	__uint16_t            don_len;         /* [IN] Length of the name to look up */
	__uint16_t            don_flags;       /* [IN] Lookup flags (Set of `HOP_DIRECTORY_OPENNODE_FLAG_*') */
	__uint32_t          __don_pad3;        /* ... */
	struct hop_openfd    *don_node;        /* [OUT_OPT][0..1] When non-NULL, store a handle to the child node in here. */
	__HOP_PAD_POINTER  (__don_pad4)        /* ... */
	struct hop_openfd    *don_dent;        /* [OUT_OPT][0..1] When non-NULL, store a handle to the child directory entry in here. */
	__HOP_PAD_POINTER  (__don_pad5)        /* ... */
};
#endif /* __CC__ */

#define HOP_DIRECTORY_CREATFILE_STATUS_ALREADY_EXISTED 0 /* The file already existed before. */
#define HOP_DIRECTORY_CREATFILE_STATUS_CREATED_NEW     1 /* A new file was created. */
#define __OFFSET_HOP_DIRECTORY_CREATFILE_STRUCT_SIZE 0
#define __OFFSET_HOP_DIRECTORY_CREATFILE_NAME        8
#define __OFFSET_HOP_DIRECTORY_CREATFILE_LEN         16
#define __OFFSET_HOP_DIRECTORY_CREATFILE_STATUS      18
#define __OFFSET_HOP_DIRECTORY_CREATFILE_OFLAGS      20
#define __OFFSET_HOP_DIRECTORY_CREATFILE_NODE        24
#define __OFFSET_HOP_DIRECTORY_CREATFILE_DENT        32
#define __OFFSET_HOP_DIRECTORY_CREATFILE_OWNER       40
#define __OFFSET_HOP_DIRECTORY_CREATFILE_GROUP       44
#define __OFFSET_HOP_DIRECTORY_CREATFILE_MODE        48
#define __SIZEOF_HOP_DIRECTORY_CREATFILE             56
#ifdef __CC__
struct hop_directory_creatfile /*[PREFIX(dcf_)]*/ {
	__uint32_t            dcf_struct_size;   /* [== sizeof(struct hop_directory_creatfile)]
	                                          * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                          * this value is too small or doesn't match any recognized
	                                          * structure version. */
	__uint32_t          __dcf_pad1;          /* ... */
	/* Create/open a child within a given directory.
	 * WARNING: This function does not follow symbolic links, understands
	 *          the special paths `.' and `..', or will even traverse more
	 *          than a single directory component (aka. no slashes)
	 *          These are the low-level functions used to lookup a child
	 *          entry within some given directory.
	 * NOTE: When `open_mode & O_EXCL' is set, throw an `E_FSERROR_FILE_ALREADY_EXISTS' if the file already existed.
	 * NOTE: When `open_mode & O_DOSPATH' is set, ignore casing when checking for existing files. */
	char const           *dcf_name;          /* [IN][1..dcf_len] Name of the child to lookup */
	__HOP_PAD_POINTER  (__dcf_pad2)          /* ... */
	__uint16_t            dcf_len;           /* [IN] Length of the name to look up */
	__uint16_t            dcf_status;        /* [OUT] Resulting file creation status (One of `HOP_DIRECTORY_CREATFILE_STATUS_*') */
	__uint32_t            dcf_oflags;        /* [IN] Open flags (Set of `O_CREAT|O_EXCL|O_DOSPATH') */
	struct hop_openfd    *dcf_node;          /* [OUT_OPT][0..1] When non-NULL, store a handle to the child node in here. */
	__HOP_PAD_POINTER  (__dcf_pad3)          /* ... */
	struct hop_openfd    *dcf_dent;          /* [OUT_OPT][0..1] When non-NULL, store a handle to the child directory entry in here. */
	__HOP_PAD_POINTER  (__dcf_pad4)          /* ... */
	__uint32_t            dcf_owner;         /* [IN] The owner set when a new file is created (or `(uint32_t)-1' to use the calling thread's filesystem owner) */
	__uint32_t            dcf_group;         /* [IN] The group set when a new file is created (or `(uint32_t)-1' to use the calling thread's filesystem group) */
	__uint32_t            dcf_mode;          /* [IN] The file access mode set when a new file is created */
	__uint32_t          __dcf_pad5;          /* ... */
};
#endif /* __CC__ */



/* Operation flags accepted by `HOP_DIRECTORY_REMOVE' */
#define HOP_DIRECTORY_REMOVE_FLAG_REGULAR   0x0001 /* Remove regular files (`unlink()') */
#define HOP_DIRECTORY_REMOVE_FLAG_DIRECTORY 0x0002 /* Remove directories (`rmdir()') */
#define HOP_DIRECTORY_REMOVE_FLAG_NOCASE    0x8000 /* Ignore casing. */

/* Status code flags set by `HOP_DIRECTORY_REMOVE' */
#define HOP_DIRECTORY_REMOVE_STATUS_UNLINK   0x0001 /* The operation has removed or unlinked a file. */
#define HOP_DIRECTORY_REMOVE_STATUS_RMDIR    0x0002 /* The operation has removed or unlinked a directory. */
#define HOP_DIRECTORY_REMOVE_STATUS_FDELETED 0x4000 /* FLAG: The associated node has been deleted.
                                                     * This flag is set when the node's NLINK counter has reached
                                                     * ZERO(0) as a result of the remove operation, at which point
                                                     * the `INODE_FDELETED' flag is set, and the node is removed
                                                     * from the INode tree of the associated superblock. */

#define __OFFSET_HOP_DIRECTORY_REMOVE_STRUCT_SIZE 0
#define __OFFSET_HOP_DIRECTORY_REMOVE_NAME        8
#define __OFFSET_HOP_DIRECTORY_REMOVE_LEN         16
#define __OFFSET_HOP_DIRECTORY_REMOVE_FLAGS       18
#define __OFFSET_HOP_DIRECTORY_REMOVE_STATUS      20
#define __OFFSET_HOP_DIRECTORY_REMOVE_NODE        24
#define __OFFSET_HOP_DIRECTORY_REMOVE_DENT        32
#define __SIZEOF_HOP_DIRECTORY_REMOVE             40
#ifdef __CC__
struct hop_directory_remove /*[PREFIX(drm_)]*/ {
	__uint32_t            drm_struct_size;  /* [== sizeof(struct hop_directory_remove)]
	                                         * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                         * this value is too small or doesn't match any recognized
	                                         * structure version. */
	__uint32_t          __drm_pad1;         /* ... */
	/* Remove a child from a given directory.
	 * WARNING: This function does not follow symbolic links, understands
	 *          the special paths `.' and `..', or will even traverse more
	 *          than a single directory component (aka. no slashes)
	 *          These are the low-level functions used to lookup a child
	 *          entry within some given directory. */
	char const           *drm_name;         /* [IN][1..drm_len] Name of the child to lookup */
	__HOP_PAD_POINTER  (__drm_pad2)         /* ... */
	__uint16_t            drm_len;          /* [IN] Length of the name to look up */
	__uint16_t            drm_flags;        /* [IN] Remove flags (Set of `HOP_DIRECTORY_REMOVE_FLAG_*') */
	__uint16_t            drm_status;       /* [OUT] Resulting deletion status (One of `HOP_DIRECTORY_CREATFILE_STATUS_*') */
	__uint16_t          __drm_pad3;         /* ... */
	struct hop_openfd    *drm_node;         /* [OUT_OPT][0..1] When non-NULL, store a handle to the removed child node in here. */
	__HOP_PAD_POINTER  (__drm_pad4)         /* ... */
	struct hop_openfd    *drm_dent;         /* [OUT_OPT][0..1] When non-NULL, store a handle to the removed child directory entry in here. */
	__HOP_PAD_POINTER  (__drm_pad5)         /* ... */
};
#endif /* __CC__ */


#define HOP_DIRECTORY_RENAME_FNORMAL 0x0000 /* Normal rename flags. */
#define HOP_DIRECTORY_RENAME_FNOCASE 0x8000 /* Ignore casing. */
#define __OFFSET_HOP_DIRECTORY_RENAME_STRUCT_SIZE 0
#define __OFFSET_HOP_DIRECTORY_RENAME_SRCNAME     8
#define __OFFSET_HOP_DIRECTORY_RENAME_DSTNAME     16
#define __OFFSET_HOP_DIRECTORY_RENAME_SRCLEN      24
#define __OFFSET_HOP_DIRECTORY_RENAME_DSTLEN      26
#define __OFFSET_HOP_DIRECTORY_RENAME_FLAGS       28
#define __OFFSET_HOP_DIRECTORY_RENAME_DSTDIR      32
#define __OFFSET_HOP_DIRECTORY_RENAME_SRCNODE     40
#define __OFFSET_HOP_DIRECTORY_RENAME_SRCDENT     48
#define __OFFSET_HOP_DIRECTORY_RENAME_DSTNODE     56
#define __OFFSET_HOP_DIRECTORY_RENAME_DSTDENT     64
#define __SIZEOF_HOP_DIRECTORY_RENAME             72
#ifdef __CC__
struct hop_directory_rename /*[PREFIX(drn_)]*/ {
	__uint32_t            drn_struct_size;  /* [== sizeof(struct hop_directory_rename)]
	                                         * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                         * this value is too small or doesn't match any recognized
	                                         * structure version. */
	__uint32_t          __drn_pad1;         /* ... */
	/* Rename a child in a given directory, potentially also moving it into another directory.
	 * WARNING: This function does not follow symbolic links, understands
	 *          the special paths `.' and `..', or will even traverse more
	 *          than a single directory component (aka. no slashes)
	 *          These are the low-level functions used to lookup a child
	 *          entry within some given directory. */
	char const           *drn_srcname;      /* [IN][1..drn_srclen] Name of the source file */
	__HOP_PAD_POINTER  (__drn_pad2)         /* ... */
	char const           *drn_dstname;      /* [IN][1..drn_dstlen] Name of the target file */
	__HOP_PAD_POINTER  (__drn_pad3)         /* ... */
	__uint16_t            drn_srclen;       /* [IN] Length of the source child name */
	__uint16_t            drn_dstlen;       /* [IN] Length of the target child name */
	__uint16_t            drn_flags;        /* [IN] Rename flags (Set of `HOP_DIRECTORY_RENAME_FLAG_*') */
	__uint16_t          __drn_pad4;         /* ... */
	__uint32_t            drn_dstdir;       /* [IN] Handle number for the target directory (or (uint32_t)-1 to re-use the source directory) */
	__uint32_t          __drn_pad5;         /* ... */
	struct hop_openfd    *drn_srcnode;      /* [OUT_OPT][0..1] When non-NULL, store a handle to the source node in here. */
	__HOP_PAD_POINTER  (__drn_pad6)         /* ... */
	struct hop_openfd    *drn_srcdent;      /* [OUT_OPT][0..1] When non-NULL, store a handle to the source directory entry in here. */
	__HOP_PAD_POINTER  (__drn_pad7)         /* ... */
	struct hop_openfd    *drn_dstnode;      /* [OUT_OPT][0..1] When non-NULL, store a handle to the target node in here. */
	__HOP_PAD_POINTER  (__drn_pad8)         /* ... */
	struct hop_openfd    *drn_dstdent;      /* [OUT_OPT][0..1] When non-NULL, store a handle to the target directory entry in here. */
	__HOP_PAD_POINTER  (__drn_pad9)         /* ... */
};
#endif /* __CC__ */

#define HOP_DIRECTORY_LINK_FNORMAL 0x0000 /* Normal link flags. */
#define HOP_DIRECTORY_LINK_FNOCASE 0x8000 /* Ignore casing. */
#define __OFFSET_HOP_DIRECTORY_LINK_STRUCT_SIZE 0
#define __OFFSET_HOP_DIRECTORY_LINK_NAME        8
#define __OFFSET_HOP_DIRECTORY_LINK_LEN         16
#define __OFFSET_HOP_DIRECTORY_LINK_FLAGS       18
#define __OFFSET_HOP_DIRECTORY_LINK_LINKNODE    20
#define __OFFSET_HOP_DIRECTORY_LINK_DENT        24
#define __SIZEOF_HOP_DIRECTORY_LINK             32
#ifdef __CC__
struct hop_directory_link /*[PREFIX(dli_)]*/ {
	__uint32_t            dli_struct_size;   /* [== sizeof(struct hop_directory_link)]
	                                          * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                          * this value is too small or doesn't match any recognized
	                                          * structure version. */
	__uint32_t          __dli_pad1;          /* ... */
	/* Create hard links within a given directory.
	 * WARNING: This function does not follow symbolic links, understands
	 *          the special paths `.' and `..', or will even traverse more
	 *          than a single directory component (aka. no slashes)
	 *          These are the low-level functions used to lookup a child
	 *          entry within some given directory. */
	char const           *dli_name;          /* [IN][1..dli_len] Name of the link to create */
	__HOP_PAD_POINTER  (__dli_pad2)          /* ... */
	__uint16_t            dli_len;           /* [IN] Length of the name to look up */
	__uint16_t            dli_flags;         /* [IN] Link flags (Set of `HOP_DIRECTORY_LINK_FLAG_*') */
	__uint32_t            dli_linknode;      /* [IN] Handle number for the INode that should be linked */
	struct hop_openfd    *dli_dent;          /* [OUT_OPT][0..1] When non-NULL, store a handle to the newly created directory entry in here. */
	__HOP_PAD_POINTER  (__dli_pad4)          /* ... */
};
#endif /* __CC__ */


#define HOP_DIRECTORY_SYMLINK_FNORMAL    0x0000 /* Normal symlink flags. */
#define HOP_DIRECTORY_SYMLINK_FNOCASE    0x8000 /* Ignore casing when checking for existing files. */
#define __OFFSET_HOP_DIRECTORY_SYMLINK_STRUCT_SIZE 0
#define __OFFSET_HOP_DIRECTORY_SYMLINK_NAME        8
#define __OFFSET_HOP_DIRECTORY_SYMLINK_LEN         16
#define __OFFSET_HOP_DIRECTORY_SYMLINK_FLAGS       18
#define __OFFSET_HOP_DIRECTORY_SYMLINK_TEXT        24
#define __OFFSET_HOP_DIRECTORY_SYMLINK_TEXTLEN     32
#define __OFFSET_HOP_DIRECTORY_SYMLINK_NODE        40
#define __OFFSET_HOP_DIRECTORY_SYMLINK_DENT        48
#define __OFFSET_HOP_DIRECTORY_SYMLINK_OWNER       56
#define __OFFSET_HOP_DIRECTORY_SYMLINK_GROUP       60
#define __OFFSET_HOP_DIRECTORY_SYMLINK_MODE        64
#define __SIZEOF_HOP_DIRECTORY_SYMLINK             72
#ifdef __CC__
struct hop_directory_symlink /*[PREFIX(dsl_)]*/ {
	__uint32_t            dsl_struct_size;   /* [== sizeof(struct hop_directory_symlink)]
	                                          * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                          * this value is too small or doesn't match any recognized
	                                          * structure version. */
	__uint32_t          __dsl_pad1;          /* ... */
	/* Create a new symbolic link within a given directory.
	 * WARNING: This function does not follow symbolic links, understands
	 *          the special paths `.' and `..', or will even traverse more
	 *          than a single directory component (aka. no slashes)
	 *          These are the low-level functions used to lookup a child
	 *          entry within some given directory. */
	char const           *dsl_name;          /* [IN][1..dsl_len] Name of the symlink to create */
	__HOP_PAD_POINTER  (__dsl_pad2)          /* ... */
	__uint16_t            dsl_len;           /* [IN] Length of the name for the symlink */
	__uint16_t            dsl_flags;         /* [IN] Symlink creation flags (Set of `HOP_DIRECTORY_SYMLINK_FLAG_*') */
	__uint32_t          __dsl_pad3;          /* ... */
	char const           *dsl_text;          /* [IN][1..dsl_textlen] The text that should be contained within the symlink. */
	__HOP_PAD_POINTER  (__dsl_pad4)          /* ... */
	__size_t              dsl_textlen;       /* [IN] Length of the symlink's text. */
	__HOP_PAD_POINTER  (__dsl_pad5)          /* ... */
	struct hop_openfd    *dsl_node;          /* [OUT_OPT][0..1] When non-NULL, store a handle to the newly created node in here. */
	__HOP_PAD_POINTER  (__dsl_pad6)          /* ... */
	struct hop_openfd    *dsl_dent;          /* [OUT_OPT][0..1] When non-NULL, store a handle to the newly created directory entry in here. */
	__HOP_PAD_POINTER  (__dsl_pad7)          /* ... */
	__uint32_t            dsl_owner;         /* [IN] The owner set for the symlink node (or `(uint32_t)-1' to use the calling thread's filesystem owner) */
	__uint32_t            dsl_group;         /* [IN] The group set for the symlink node (or `(uint32_t)-1' to use the calling thread's filesystem group) */
	__uint32_t            dsl_mode;          /* [IN] The file access mode set for the symlink node */
	__uint32_t          __dsl_pad8;          /* ... */
};
#endif /* __CC__ */

#define HOP_DIRECTORY_MKNOD_FNORMAL    0x0000 /* Normal mknod flags. */
#define HOP_DIRECTORY_MKNOD_FNOCASE    0x8000 /* Ignore casing when checking for existing files. */
#define __OFFSET_HOP_DIRECTORY_MKNOD_STRUCT_SIZE 0
#define __OFFSET_HOP_DIRECTORY_MKNOD_NAME        8
#define __OFFSET_HOP_DIRECTORY_MKNOD_LEN         16
#define __OFFSET_HOP_DIRECTORY_MKNOD_FLAGS       18
#define __OFFSET_HOP_DIRECTORY_MKNOD_DEVICE      20
#define __OFFSET_HOP_DIRECTORY_MKNOD_NODE        24
#define __OFFSET_HOP_DIRECTORY_MKNOD_DENT        32
#define __OFFSET_HOP_DIRECTORY_MKNOD_OWNER       40
#define __OFFSET_HOP_DIRECTORY_MKNOD_GROUP       44
#define __OFFSET_HOP_DIRECTORY_MKNOD_MODE        48
#define __SIZEOF_HOP_DIRECTORY_MKNOD             56
#ifdef __CC__
struct hop_directory_mknod /*[PREFIX(dmn_)]*/ {
	__uint32_t            dmn_struct_size;   /* [== sizeof(struct hop_directory_symlink)]
	                                          * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                          * this value is too small or doesn't match any recognized
	                                          * structure version. */
	__uint32_t          __dmn_pad1;          /* ... */
	/* Create a new symbolic link within a given directory.
	 * WARNING: This function does not follow symbolic links, understands
	 *          the special paths `.' and `..', or will even traverse more
	 *          than a single directory component (aka. no slashes)
	 *          These are the low-level functions used to lookup a child
	 *          entry within some given directory. */
	char const           *dmn_name;          /* [IN][1..dmn_len] Name of the symlink to create */
	__HOP_PAD_POINTER  (__dmn_pad2)          /* ... */
	__uint16_t            dmn_len;           /* [IN] Length of the name for the symlink */
	__uint16_t            dmn_flags;         /* [IN] Node creation flags (Set of `HOP_DIRECTORY_MKNOD_FLAG_*') */
	__uint32_t            dmn_device;        /* [IN] The referenced device number. */
	struct hop_openfd    *dmn_node;          /* [OUT_OPT][0..1] When non-NULL, store a handle to the newly created node in here. */
	__HOP_PAD_POINTER  (__dmn_pad3)          /* ... */
	struct hop_openfd    *dmn_dent;          /* [OUT_OPT][0..1] When non-NULL, store a handle to the newly created directory entry in here. */
	__HOP_PAD_POINTER  (__dmn_pad4)          /* ... */
	__uint32_t            dmn_owner;         /* [IN] The owner set for the symlink node (or `(uint32_t)-1' to use the calling thread's filesystem owner) */
	__uint32_t            dmn_group;         /* [IN] The group set for the symlink node (or `(uint32_t)-1' to use the calling thread's filesystem group) */
	__uint32_t            dmn_mode;          /* [IN] The file access mode set for the symlink node
	                                          * NOTE: What kind of node is created is controlled by `S_IFCHR' / `S_IFBLK' being apart of this field.
	                                          *       Also note that you may pass `S_IFREG' to create regular files.
	                                          * s.a. `E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKNOD_MODE' */
	__uint32_t          __dmn_pad5;          /* ... */
};
#endif /* __CC__ */


#define HOP_DIRECTORY_MKDIR_FNORMAL    0x0000 /* Normal mkdir flags. */
#define HOP_DIRECTORY_MKDIR_FNOCASE    0x8000 /* Ignore casing when checking for existing files. */
#define __OFFSET_HOP_DIRECTORY_MKDIR_STRUCT_SIZE 0
#define __OFFSET_HOP_DIRECTORY_MKDIR_NAME        8
#define __OFFSET_HOP_DIRECTORY_MKDIR_LEN         16
#define __OFFSET_HOP_DIRECTORY_MKDIR_FLAGS       18
#define __OFFSET_HOP_DIRECTORY_MKDIR_NODE        24
#define __OFFSET_HOP_DIRECTORY_MKDIR_DENT        32
#define __OFFSET_HOP_DIRECTORY_MKDIR_OWNER       40
#define __OFFSET_HOP_DIRECTORY_MKDIR_GROUP       44
#define __OFFSET_HOP_DIRECTORY_MKDIR_MODE        48
#define __SIZEOF_HOP_DIRECTORY_MKDIR             56
#ifdef __CC__
struct hop_directory_mkdir /*[PREFIX(dmd_)]*/ {
	__uint32_t            dmd_struct_size;   /* [== sizeof(struct hop_directory_symlink)]
	                                          * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                          * this value is too small or doesn't match any recognized
	                                          * structure version. */
	__uint32_t          __dmd_pad1;          /* ... */
	/* Create a new symbolic link within a given directory.
	 * WARNING: This function does not follow symbolic links, understands
	 *          the special paths `.' and `..', or will even traverse more
	 *          than a single directory component (aka. no slashes)
	 *          These are the low-level functions used to lookup a child
	 *          entry within some given directory. */
	char const           *dmd_name;          /* [IN][1..dmd_len] Name of the symlink to create */
	__HOP_PAD_POINTER  (__dmd_pad2)          /* ... */
	__uint16_t            dmd_len;           /* [IN] Length of the name for the symlink */
	__uint16_t            dmd_flags;         /* [IN] Node creation flags (Set of `HOP_DIRECTORY_MKNOD_FLAG_*') */
	__uint32_t          __dmd_pad3;           /* ... */
	struct hop_openfd    *dmd_node;          /* [OUT_OPT][0..1] When non-NULL, store a handle to the newly created node in here. */
	__HOP_PAD_POINTER  (__dmd_pad4)          /* ... */
	struct hop_openfd    *dmd_dent;          /* [OUT_OPT][0..1] When non-NULL, store a handle to the newly created directory entry in here. */
	__HOP_PAD_POINTER  (__dmd_pad5)          /* ... */
	__uint32_t            dmd_owner;         /* [IN] The owner set for the symlink node (or `(uint32_t)-1' to use the calling thread's filesystem owner) */
	__uint32_t            dmd_group;         /* [IN] The group set for the symlink node (or `(uint32_t)-1' to use the calling thread's filesystem group) */
	__uint32_t            dmd_mode;          /* [IN] The file access mode set for the symlink node
	                                          * NOTE: What kind of node is created is controlled by `S_IFCHR' / `S_IFBLK' being apart of this field.
	                                          *       Also note that you may pass `S_IFREG' to create regular files.
	                                          * s.a. `E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKNOD_MODE' */
	__uint32_t          __dmd_pad6;          /* ... */
};
#endif /* __CC__ */


#define __OFFSET_HOP_FILE_CMPXCHG_OFFSET_STRUCT_SIZE 0
#define __OFFSET_HOP_FILE_CMPXCHG_OFFSET_EXPOFFSET   8
#define __OFFSET_HOP_FILE_CMPXCHG_OFFSET_NEWOFFSET   16
#define __OFFSET_HOP_FILE_CMPXCHG_OFFSET_OLDOFFSET   24
#define __SIZEOF_HOP_FILE_CMPXCHG_OFFSET             32
#ifdef __CC__
struct hop_file_cmpxchg_offset /*[PREFIX(cxo_)]*/ {
	__uint32_t            cxo_struct_size;   /* [== sizeof(struct hop_file_cmpxchg_offset)]
	                                          * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                          * this value is too small or doesn't match any recognized
	                                          * structure version. */
	__uint32_t          __cxo_pad1;          /* ... */
	__uint64_t            cxo_expoffset;     /* [IN] The expected old file offset that must be matched
	                                          *      in order for `cxo_newoffset' to be successfully applied. */
	__uint64_t            cxo_newoffset;     /* [IN] The new file offset to set when `cxo_expoffset' was found. */
	__uint64_t            cxo_oldoffset;     /* [OUT] The actual old file-offset (always written) */
};
#endif /* __CC__ */


#define __OFFSET_HOP_TASK_JOIN_STRUCT_SIZE     0
#define __OFFSET_HOP_TASK_JOIN_RELTIMEOUT_SEC  8
#define __OFFSET_HOP_TASK_JOIN_RELTIMEOUT_NSEC 16
#define __OFFSET_HOP_TASK_JOIN_STATUS          20
#define __SIZEOF_HOP_TASK_JOIN                 24
#ifdef __CC__
struct hop_task_join /*[PREFIX(tj_)]*/ {
	__uint32_t            tj_struct_size;     /* [== sizeof(struct hop_task_join)]
	                                           * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                           * this value is too small or doesn't match any recognized
	                                           * structure version. */
	__uint32_t          __tj_pad1;            /* ... */
	__uint64_t            tj_reltimeout_sec;  /* Relative timeout seconds (or (__uint64_t)-1 to wait indefinitely) */
	__uint32_t            tj_reltimeout_nsec; /* Relative timeout nano seconds (<= 1000000000 == 1_000_000_000) */
	__uint32_t            tj_status;          /* [OUT][TYPE(union wait)] The exit status of the thread.
	                                           * If the thread has yet to exit, this field is set to `0' */
};
#endif /* __CC__ */


/* Return value of hop() for `HOP_TASK_SETPROCESSGROUPLEADER' */
#define HOP_TASK_SETPROCESSGROUPLEADER_SUCCESS 0 /* Successfully added `HOP_TASK_OPEN_PROCESS(thread)' to the process group
                                                  * that `tspgl_leader' is apart of (which is `HOP_TASK_OPEN_PROCESS_GROUP_LEADER(tspgl_leader)'),
                                                  * or make `thread' become its own process group when
                                                  * `HOP_TASK_OPEN_PROCESS(thread) == HOP_TASK_OPEN_PROCESS(tspgl_leader) */
#define HOP_TASK_SETPROCESSGROUPLEADER_LEADER  1 /*  The given `thread' is already the tspgl_leader of its own process group.
                                                  * -> Once promoted to a group leader, a process cannot back out and no longer be one! */
#define HOP_TASK_SETPROCESSGROUPLEADER_EXITED  2 /* The given `tspgl_leader' has already terminated. */
#define __OFFSET_HOP_TASK_SETPROCESSGROUPLEADER_STRUCT_SIZE 0
#define __OFFSET_HOP_TASK_SETPROCESSGROUPLEADER_LEADER      4
#define __OFFSET_HOP_TASK_SETPROCESSGROUPLEADER_OLD_LEADER  8
#define __OFFSET_HOP_TASK_SETPROCESSGROUPLEADER_NEW_LEADER  16
#define __SIZEOF_HOP_TASK_SETPROCESSGROUPLEADER             24
#ifdef __CC__
struct hop_task_setprocessgroupleader /*[PREFIX(tspgl_)]*/ {
	__uint32_t            tspgl_struct_size; /* [== sizeof(struct hop_task_setprocessgroupleader)]
	                                          * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                          * this value is too small or doesn't match any recognized
	                                          * structure version. */
	__uint32_t            tspgl_leader;      /* [IN] Handle for to a thread who's process should be used as leader */
	struct hop_openfd    *tspgl_old_leader;  /* [OUT_OPT][0..1] When non-NULL store a handle to the old process group leader of `HOP_TASK_OPEN_PROCESS(<thread>)'. (NOTE: Only written to on HOP_TASK_SETPROCESSGROUPLEADER_SUCCESS) */
    __HOP_PAD_POINTER  (__tspgl_pad1)
	struct hop_openfd    *tspgl_new_leader;  /* [OUT_OPT][0..1] When non-NULL store a handle to the new process group leader of `HOP_TASK_OPEN_PROCESS(<thread>)'. (NOTE: Only written to on HOP_TASK_SETPROCESSGROUPLEADER_SUCCESS) */
    __HOP_PAD_POINTER  (__tspgl_pad2)

};
#endif /* __CC__ */


/* Return value of hop() for `HOP_TASK_SETPROCESSGROUPLEADER' */
#define HOP_TASK_SETSESSIONLEADER_SUCCESS 0 /* Successfully added `HOP_TASK_OPEN_PROCESS(thread)' (which at that
                                             * point is guarantied to be identical to `HOP_TASK_OPEN_PROCESS_GROUP_LEADER(thread)')
                                             * to the session that `tssl_leader' is apart of (which is
                                             * `HOP_TASK_OPEN_SESSION_LEADER(tssl_leader)'), or make `thread' become a new session when
                                             * `HOP_TASK_OPEN_PROCESS_GROUP_LEADER(thread) == HOP_TASK_OPEN_PROCESS_GROUP_LEADER(tssl_leader)' */
#define HOP_TASK_SETSESSIONLEADER_LEADER  1 /* The given `thread' is already the leader of a different session than `tssl_leader'.
                                             * -> Once promoted to a session leader, a process group cannot back out and no longer be one!  */
#define __OFFSET_HOP_TASK_SETSESSIONLEADER_STRUCT_SIZE    0
#define __OFFSET_HOP_TASK_SETSESSIONLEADER_LEADER         4
#define __OFFSET_HOP_TASK_SETSESSIONLEADER_OLD_GRP_LEADER 8
#define __OFFSET_HOP_TASK_SETSESSIONLEADER_OLD_LEADER     16
#define __OFFSET_HOP_TASK_SETSESSIONLEADER_NEW_LEADER     24
#define __SIZEOF_HOP_TASK_SETSESSIONLEADER                32
#ifdef __CC__
struct hop_task_setsessionleader /*[PREFIX(tssl_)]*/ {
	__uint32_t            tssl_struct_size;    /* [== sizeof(struct hop_task_setsessionleader)]
	                                             * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                             * this value is too small or doesn't match any recognized
	                                             * structure version. */
	__uint32_t            tssl_leader;         /* [IN] Handle for to a thread who's process should be used as leader */
	struct hop_openfd    *tssl_old_grp_leader; /* [OUT_OPT][0..1] When non-NULL store a handle to the old process group leader of `HOP_TASK_OPEN_PROCESS(<thread>)'. (NOTE: Only written to on HOP_TASK_SETSESSIONLEADER_SUCCESS) */
    __HOP_PAD_POINTER  (__tspgl_pad1)
	struct hop_openfd    *tssl_old_leader;     /* [OUT_OPT][0..1] When non-NULL store a handle to the old session leader of `HOP_TASK_OPEN_PROCESS(<thread>)'. (NOTE: Only written to on HOP_TASK_SETSESSIONLEADER_SUCCESS) */
    __HOP_PAD_POINTER  (__tspgl_pad2)
	struct hop_openfd    *tssl_new_leader;     /* [OUT_OPT][0..1] When non-NULL store a handle to the new session leader of `HOP_TASK_OPEN_PROCESS(<thread>)'. (NOTE: Only written to on HOP_TASK_SETSESSIONLEADER_SUCCESS) */
    __HOP_PAD_POINTER  (__tspgl_pad3)

};
#endif /* __CC__ */


#define __OFFSET_HOP_PIPE_STAT_STRUCT_SIZE 0
#define __OFFSET_HOP_PIPE_STAT_RDTOTAL     8
#define __OFFSET_HOP_PIPE_STAT_AVAIL       16
#define __OFFSET_HOP_PIPE_STAT_BUFCUR      24
#define __OFFSET_HOP_PIPE_STAT_BUFLIM      32
#define __SIZEOF_HOP_PIPE_STAT             40
#ifdef __CC__
struct hop_pipe_stat /*[PREFIX(ps_)]*/ {
	__uint32_t            ps_struct_size;    /* [== sizeof(struct hop_pipe_stat)]
	                                          * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                          * this value is too small or doesn't match any recognized
	                                          * structure version. */
	__uint32_t          __ps_pad1;           /* ... */
	__uint64_t            ps_rdtotal;        /* Total number of bytes read since the pipe buffer was last defragmented (which must be done before it can be re-allocated) */
	__uint64_t            ps_avail;          /* Number of bytes currently available for reading */
	__uint64_t            ps_bufcur;         /* Current buffer size of the pipe */
	__uint64_t            ps_buflim;         /* Max buffer size of the pipe */
};
#endif /* __CC__ */


#define __OFFSET_HOP_PIPE_WRITESOME_STRUCT_SIZE 0
#define __OFFSET_HOP_PIPE_WRITESOME_BUF         8
#define __OFFSET_HOP_PIPE_WRITESOME_BUFLEN      16
#define __OFFSET_HOP_PIPE_WRITESOME_WRITTEN     24
#define __SIZEOF_HOP_PIPE_WRITESOME             32
#ifdef __CC__
struct hop_pipe_writesome /*[PREFIX(pws_)]*/ {
	__uint32_t            pws_struct_size;   /* [== sizeof(struct hop_pipe_writesome)]
	                                          * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                          * this value is too small or doesn't match any recognized
	                                          * structure version. */
	__uint32_t          __pws_pad1;          /* ... */
	void                 *pws_buf;           /* [IN] Base address of the data to write to the pipe */
	__HOP_PAD_POINTER  (__pws_pad2)          /* ... */
	__size_t              pws_buflen;        /* [IN] Length of the given `pws_buf' (in bytes) */
	__HOP_PAD_POINTER  (__pws_pad3)          /* ... */
	__size_t              pws_written;       /* [OUT] The number of written bytes */
	__HOP_PAD_POINTER  (__pws_pad4)          /* ... */
};
#endif /* __CC__ */


#define __OFFSET_HOP_PIPE_VWRITESOME_STRUCT_SIZE 0
#define __OFFSET_HOP_PIPE_VWRITESOME_BUF         8
#define __OFFSET_HOP_PIPE_VWRITESOME_BUFCNT      16
#define __OFFSET_HOP_PIPE_VWRITESOME_WRITTEN     24
#define __SIZEOF_HOP_PIPE_VWRITESOME             32
#ifdef __CC__
struct iovec;
struct hop_pipe_vwritesome /*[PREFIX(pvws_)]*/ {
	__uint32_t            pvws_struct_size;  /* [== sizeof(struct hop_pipe_vwritesome)]
	                                          * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                          * this value is too small or doesn't match any recognized
	                                          * structure version. */
	__uint32_t          __pvws_pad1;         /* ... */
	struct iovec const   *pvws_buf;          /* [IN] Vector of buffer locations */
	__HOP_PAD_POINTER  (__pvws_pad2)         /* ... */
	__size_t              pvws_bufcnt;       /* [IN] Number of IO-vectors (count) */
	__HOP_PAD_POINTER  (__pvws_pad3)         /* ... */
	__size_t              pvws_written;      /* [OUT] The number of written bytes */
	__HOP_PAD_POINTER  (__pvws_pad4)         /* ... */
};
#endif /* __CC__ */


#define __OFFSET_HOP_PIPE_SKIPDATA_STRUCT_SIZE 0
#define __OFFSET_HOP_PIPE_SKIPDATA_NUM_BYTES   8
#define __OFFSET_HOP_PIPE_SKIPDATA_SKIPPED     16
#define __OFFSET_HOP_PIPE_SKIPDATA_RDPOS       24
#define __SIZEOF_HOP_PIPE_SKIPDATA             32
#ifdef __CC__
struct hop_pipe_skipdata /*[PREFIX(psd_)]*/ {
	__uint32_t            psd_struct_size;   /* [== sizeof(struct hop_pipe_skipdata)]
	                                          * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                          * this value is too small or doesn't match any recognized
	                                          * structure version. */
	__uint32_t          __psd_pad1;          /* ... */
	__HOP_SIZE64_FIELD   (psd_num_bytes);    /* [IN] The max number of bytes to skip. */
	__uint64_t            psd_skipped;       /* [OUT] The number of skipped bytes */
	__uint64_t            psd_rdpos;         /* [OUT] The total number of read/skipped bytes since the buffer was last re-sized */
};
#endif /* __CC__ */

#define __OFFSET_HOP_PIPE_UNREAD_STRUCT_SIZE 0
#define __OFFSET_HOP_PIPE_UNREAD_NUM_BYTES   8
#define __OFFSET_HOP_PIPE_UNREAD_UNREAD      16
#define __OFFSET_HOP_PIPE_UNREAD_RDPOS       24
#define __SIZEOF_HOP_PIPE_UNREAD             32
#ifdef __CC__
struct hop_pipe_unread /*[PREFIX(pur_)]*/ {
	__uint32_t            pur_struct_size;   /* [== sizeof(struct hop_pipe_unread)]
	                                          * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                          * this value is too small or doesn't match any recognized
	                                          * structure version. */
	__uint32_t          __pur_pad1;          /* ... */
	__HOP_SIZE64_FIELD   (pur_num_bytes);    /* [IN] The max number of bytes to unread. */
	__uint64_t            pur_unread;        /* [OUT] The number of unread bytes */
	__uint64_t            pur_rdpos;         /* [OUT] The total number of read/skipped bytes since the buffer was last re-sized */
};
#endif /* __CC__ */

#define __OFFSET_HOP_PIPE_UNWRITE_STRUCT_SIZE 0
#define __OFFSET_HOP_PIPE_UNWRITE_NUM_BYTES   8
#define __OFFSET_HOP_PIPE_UNWRITE_UNWRITTEN   16
#define __OFFSET_HOP_PIPE_UNWRITE_WRPOS       24
#define __SIZEOF_HOP_PIPE_UNWRITE             32
#ifdef __CC__
struct hop_pipe_unwrite /*[PREFIX(puw_)]*/ {
	__uint32_t            puw_struct_size;   /* [== sizeof(struct hop_pipe_unwrite)]
	                                          * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                          * this value is too small or doesn't match any recognized
	                                          * structure version. */
	__uint32_t          __puw_pad1;          /* ... */
	__HOP_SIZE64_FIELD   (puw_num_bytes);    /* [IN] The max number of bytes to unwrite. */
	__uint64_t            puw_unwritten;     /* [OUT] The number of unwritten bytes */
	__uint64_t            puw_wrpos;         /* [OUT] The total number of written bytes since the buffer was last re-sized */
};
#endif /* __CC__ */



#define HOP_DATAPART_STAT_FEATURE_NONE         0x00000000 /* No special features. */
#define HOP_DATAPART_STAT_FEATURE_ISLOCKED     0x00000001 /* s.a. VM_DATAPART_FLAG_LOCKED. */
#define HOP_DATAPART_STAT_FEATURE_HASCHANGED   0x00000004 /* s.a. VM_DATAPART_FLAG_CHANGED. */
#define HOP_DATAPART_STAT_FEATURE_KEEPRAM      0x00000800 /* s.a. `VM_DATAPART_FLAG_KEEPRAM'. */
#define HOP_DATAPART_STAT_FEATURE_TRKCHNG      0x00001000 /* s.a. `VM_DATAPART_FLAG_TRKCHNG'. */
#define HOP_DATAPART_STAT_FEATURE_COREPRT      0x00004000 /* s.a. `VM_DATAPART_FLAG_COREPRT'. */
#define HOP_DATAPART_STAT_FEATURE_KERNPRT      0x00008000 /* s.a. `VM_DATAPART_FLAG_KERNPRT'. */
#define HOP_DATAPART_STAT_FEATURE_ISANON       0x00010000 /* The datapart is anonymous. */
#define HOP_DATAPART_STAT_FEATURE_HASFUTEXCTRL 0x00020000 /* The datapart has a futex controller. */
#define HOP_DATAPART_STAT_FEATURE_HASFUTEXLIVE 0x00040000 /* The datapart has live futex objects (implies `HOP_DATAPART_STAT_FEATURE_HASFUTEXCTRL'). */
#define HOP_DATAPART_STAT_FEATURE_HASCMAP      0x00100000 /* The datapart has copy-on-write memory mappings. */
#define HOP_DATAPART_STAT_FEATURE_HASSMAP      0x00200000 /* The datapart has shared memory mappings. */
#define HOP_DATAPART_STAT_STATE_ABSENT 0x0000 /* s.a. `VM_DATAPART_STATE_ABSENT' */
#define HOP_DATAPART_STAT_STATE_INCORE 0x0001 /* s.a. `VM_DATAPART_STATE_INCORE' */
#define HOP_DATAPART_STAT_STATE_LOCKED 0x0002 /* s.a. `VM_DATAPART_STATE_LOCKED' */
#define HOP_DATAPART_STAT_STATE_INSWAP 0x0003 /* s.a. `VM_DATAPART_STATE_INSWAP' */
#define HOP_DATAPART_STAT_STATE_VIOPRT 0x0004 /* s.a. `VM_DATAPART_STATE_VIOPRT' */
#define __OFFSET_HOP_DATAPART_STAT_STRUCT_SIZE 0
#define __OFFSET_HOP_DATAPART_STAT_FEATURES    4
#define __OFFSET_HOP_DATAPART_STAT_STATE       8
#define __OFFSET_HOP_DATAPART_STAT_MINADDR     16
#define __OFFSET_HOP_DATAPART_STAT_MAXADDR     24
#define __OFFSET_HOP_DATAPART_STAT_MINVPAGE    32
#define __OFFSET_HOP_DATAPART_STAT_MAXVPAGE    40
#define __OFFSET_HOP_DATAPART_STAT_MINDPAGE    48
#define __OFFSET_HOP_DATAPART_STAT_MAXDPAGE    56
#define __SIZEOF_HOP_DATAPART_STAT             64
#ifdef __CC__
struct hop_datapart_stat /*[PREFIX(ds_)]*/ {
	__uint32_t   ds_struct_size;          /* [== sizeof(struct hop_datablock_stat)]
	                                       * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                       * this value is too small or doesn't match any recognized
	                                       * structure version. */
	__uint32_t   ds_features;             /* [OUT] Set of `HOP_DATAPART_STAT_FEATURE_*' */
	__uint32_t   ds_state;                /* [OUT] One of `HOP_DATAPART_STAT_STATE_*' */
	__uint32_t __ds_pad;                  /* ... */
	__uint64_t   ds_minaddr;              /* [OUT] Lowest address within the associated datablock mapped by this part. */
	__uint64_t   ds_maxaddr;              /* [OUT] Greatest address within the associated datablock mapped by this part.
	                                       *       Note that this value may decrease over time, as the data part gets split. */
	__uint64_t   ds_minvpage;             /* [OUT] Lowest virt-page number mapped by this part. */
	__uint64_t   ds_maxvpage;             /* [OUT] Greatest virt-page number mapped by this part (may decrease over time). */
	__uint64_t   ds_mindpage;             /* [OUT] Lowest data-page number mapped by this part. */
	__uint64_t   ds_maxdpage;             /* [OUT] Greatest data-page number mapped by this part (may decrease over time). */
};
#endif /* __CC__ */


#undef __HOP_SIZE64_FIELD
#undef __HOP_PAD_POINTER


/* For any kind of handle */
#define HOP_HANDLE_STAT                           0xffff0001 /* [struct hop_handle_stat *result] Read information about the given handle */
#define HOP_HANDLE_NOOP                           0xffff0002 /* Do nothing other than verifying that `fd' is a valid handle. */
#define HOP_HANDLE_REOPEN                         0xffff0003 /* [struct hop_openfd *result] Re-open the given handle
                                                              * NOTE: The value returned by `hop()' is identical to the value written to `result->of_hint'. */
#define HOP_HANDLE_GETREFCNT                      0xffff0004 /* [uintptr_t *result] Return the reference counter for the given handle. */
#define HOP_HANDLE_GETADDRESS                     0xffff0005 /* [uint64_t *result] Return the kernel-space address of the handle (s.a. `struct hop_handle_stat::hs_address'). */
#define HOP_HANDLE_GETTYPE                        0xffff0006 /* [uint16_t *result] Return the handle's type. */
#define HOP_HANDLE_GETKIND                        0xffff0007 /* [uint16_t *result] Return the handle's kind. */
#define HOP_HANDLE_GETMODE                        0xffff0008 /* [uint16_t *result] Return the handle's I/O mode (s.a. `iomode_t'). */
#define HOP_HANDLE_DUP                            0xffff0009 /* Quick alias for `dup(fd)' (`hop()' returns the new file handle) */
#define HOP_HANDLE_DUP_CLOEXEC                    0xffff000a /* Quick alias for `dup(fd)' + set the CLOEXEC flag (`hop()' returns the new file handle) */
#define HOP_HANDLE_DUP_CLOFORK                    0xffff000b /* Quick alias for `dup(fd)' + set the CLOFORK flag (`hop()' returns the new file handle) */
#define HOP_HANDLE_DUP_CLOEXEC_CLOFORK            0xffff000c /* Quick alias for `dup(fd)' + set the CLOEXEC+CLOFORK flag (`hop()' returns the new file handle) */

/* For `HANDLE_TYPE_DATABLOCK' */
#define HOP_DATABLOCK_STAT                        0x00010001 /* [struct hop_datablock_stat *result] Read information about the datablock */
#define HOP_DATABLOCK_SYNCALL                     0x00010002 /* [uint64_t *result] Save all modified parts, and store the number of saved data-pages in `*result' */
#define HOP_DATABLOCK_SYNCPAGES                   0x00010003 /* [struct hop_datablock_syncpages *arg] Save all modified parts within the given range. */
#define HOP_DATABLOCK_SYNCBYTES                   0x00010004 /* [struct hop_datablock_syncbytes *arg] Save all modified bytes within the given range. */
#define HOP_DATABLOCK_ANONYMIZE                   0x00010005 /* [int *result] Anonymize all of the data parts of this datablock.
                                                              * Write 0/1 to *result, indicative of:
                                                              *  - 0: The data block had already been anonymized.
                                                              *  - 1: The data block is now anonymized, but wasn't before. */
#define HOP_DATABLOCK_DEANONYMIZE                 0x00010006 /* [int *result] Deanonymize this datablock, allowing parts to be tracked once again.
                                                              * Write 0/1 to *result, indicative of:
                                                              *  - 0: The data block wasn't anonymous (aka. was already deanonymized).
                                                              *  - 1: The data block has been deanonymized. */
#define HOP_DATABLOCK_OPEN_PART                   0x00010007 /* [struct hop_datablock_openpart *arg] Lookup (and create if missing) the data
                                                              * part associated with a given page offset (s.a. `vm_paged_datablock_locatepart()')
                                                              * @return: * : The value written to `arg->dop_openfd.of_hint' */
#define HOP_DATABLOCK_OPEN_PART_EXACT             0x00010008 /* [struct hop_datablock_openpart *arg] Same as `HOP_DATABLOCK_OPEN_PART', but make sure
                                                              * that the part begins at the exact given offset (s.a. `vm_paged_datablock_locatepart_exact()')
                                                              * @return: * : The value written to `arg->dop_openfd.of_hint' */
#define HOP_DATABLOCK_HASCHANGED                  0x00010009 /* [struct hop_datablock_haschanged *arg] Check for changes within
                                                              * the given address range (s.a. `vm_datablock_haschanged()') */
#define HOP_DATABLOCK_OPEN_FUTEX                  0x0001000a /* [struct hop_datablock_open_futex *result] Return, or create a futex for the given address.
                                                              * @return: * : The value written to `result->dof_openfd.of_hint' */
#define HOP_DATABLOCK_OPEN_FUTEX_EXISTING         0x0001000b /* [struct hop_datablock_open_futex *result] Return an existing a futex for the given address.
                                                              * @return: * : The value written to `result->dof_openfd.of_hint'
                                                              * @return: -ENOENT: No futex exists for the given address */
#define HOP_INODE_OPEN_SUPERBLOCK                 0x00010101 /* [struct hop_openfd *arg] Open the superblock associated with an INode.
                                                              * @throw: E_INVALID_HANDLE_FILETYPE: The given handle wasn't an INode.
                                                              * @return: * : The value written to `arg->of_hint' */
#define HOP_INODE_CHMOD                           0x00010102 /* [struct hop_inode_chmod *arg] Extended interface for changing file permissions in a more controlled manner.
                                                              * @throw: E_INVALID_HANDLE_FILETYPE: The given handle wasn't an INode. */
#define HOP_INODE_CHOWN                           0x00010103 /* [struct hop_inode_chown *arg] Extended interface for changing file ownership in a more controlled manner.
                                                              * @throw: E_INVALID_HANDLE_FILETYPE: The given handle wasn't an INode. */
/* TODO: HOP_INODE_READ_BLOCKING -- An always-blocking version of read(2) that uses the kernel-space function
 *                                 `inode_read_blocking', which starts blocking when reading past the end of
 *                                  a regular file, and gets unblocked when another process writes the missing
 *                                  data. */
#define HOP_DIRECTORY_OPENNODE                    0x00010301 /* [struct hop_directory_opennode *arg] Extended interface for traversing a directory.
                                                              * @throw: E_INVALID_HANDLE_FILETYPE: The given handle wasn't a directory INode.
                                                              * @throw: E_FSERROR_FILE_NOT_FOUND: [...]
                                                              * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...]
                                                              * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
                                                              * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_READDIR: [...]
                                                              * @throw: E_IOERROR: [...] */
#define HOP_DIRECTORY_CREATFILE                   0x00010302 /* [struct hop_directory_creatfile *arg] Extended interface for creating new files.
                                                              * @throw: E_INVALID_HANDLE_FILETYPE: The given handle wasn't a directory INode.
                                                              * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: [...] (The containing directory was deleted)
                                                              * @throw: E_FSERROR_ILLEGAL_PATH: [...]
                                                              * @throw: E_FSERROR_ILLEGAL_PATH: `dcf_len' was ZERO(0)
                                                              * @throw: E_FSERROR_FILE_ALREADY_EXISTS: [...] (Only when `open_mode & O_EXCL' is set)
                                                              * @throw: E_FSERROR_FILE_NOT_FOUND: [...]      (Only when `open_mode & O_CREAT' isn't set)
                                                              * @throw: E_FSERROR_DISK_FULL: [...]
                                                              * @throw: E_FSERROR_UNSUPPORTED_OPERATION: [...]
                                                              * @throw: E_FSERROR_READONLY: [...]
                                                              * @throw: E_IOERROR: [...] */
#define HOP_DIRECTORY_REMOVE                      0x00010303 /* [struct hop_directory_remove *arg] Extended interface for removing files.
                                                              * WARNING: This function may leave behind stale PATH nodes which may still be accessible,
                                                              *          with most operations performed on them resulting in `E_FSERROR_DELETED' exceptions.
                                                              * @throw: E_INVALID_HANDLE_FILETYPE: The given handle wasn't a directory INode.
                                                              * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...] (the specified file was already deleted)
                                                              * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: [...] (the given directory was deleted)
                                                              * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
                                                              * @throw: E_FSERROR_FILE_NOT_FOUND:      The specified `dr_name' could not be found
                                                              * @throw: E_FSERROR_ACCESS_DENIED:       The calling thread is not allowed to delete the file.
                                                              * @throw: E_FSERROR_NOT_A_DIRECTORY:E_FILESYSTEM_NOT_A_DIRECTORY_RMDIR:  The given `dr_name' refers to a regular file, but `HOP_DIRECTORY_REMOVE_FLAG_REGULAR' isn't set
                                                              * @throw: E_FSERROR_IS_A_DIRECTORY:E_FILESYSTEM_IS_A_DIRECTORY_UNLINK:   The given `dr_name' refers to a directory, but `HOP_DIRECTORY_REMOVE_FLAG_DIRECTORY' isn't set
                                                              * @throw: E_FSERROR_IS_A_MOUNTING_POINT:                                 The given `dr_name' refers to a mounting point when a child directory is being removed, and `containing_path' is given
                                                              * @throw: E_FSERROR_DIRECTORY_NOT_EMPTY:                                 Attempted to remove a non-empty directory.
                                                              * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_UNLINK: Cannot unlink files within the given directory
                                                              * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_RMDIR:  Cannot remove sub-directories of within the given directory
                                                              * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_TRUNC:  Cannot truncate non-empty files to 0 bytes in order to delete their data
                                                              * @throw: E_FSERROR_READONLY:            [...]
                                                              * @throw: E_IOERROR:                     [...] */
#define HOP_DIRECTORY_RENAME                      0x00010304 /* [struct hop_directory_rename *arg] Extended interface for renaming files.
                                                              * WARNING: This function may leave behind stale PATH nodes which may still be accessible,
                                                              *          with most operations performed on them resulting in `E_FSERROR_DELETED' exceptions.
                                                              * @throw: E_INVALID_HANDLE_FILETYPE: The given handle wasn't a directory INode.
                                                              * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_RENAME: [...]
                                                              * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...] (the specified source file was deleted)
                                                              * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: [...] (The source- or target-directory was deleted)
                                                              * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
                                                              * @throw: E_FSERROR_FILE_NOT_FOUND:      `drn_srcname' wasn't found
                                                              * @throw: E_FSERROR_CROSS_DEVICE_LINK:   [...]
                                                              * @throw: E_FSERROR_ILLEGAL_PATH:        [...]
                                                              * @throw: E_FSERROR_ILLEGAL_PATH:        `drn_dstlen' was ZERO(0)
                                                              * @throw: E_FSERROR_FILE_ALREADY_EXISTS: [...]
                                                              * @throw: E_FSERROR_DISK_FULL:           [...]
                                                              * @throw: E_FSERROR_TOO_MANY_HARD_LINKS: [...] (Only when emulated using `link()' + `unlink()')
                                                              * @throw: E_FSERROR_DIRECTORY_MOVE_TO_CHILD: [...]
                                                              * @throw: E_FSERROR_ACCESS_DENIED:       [...]
                                                              * @throw: E_FSERROR_READONLY:            [...]
                                                              * @throw: E_IOERROR:                     [...] */
#define HOP_DIRECTORY_LINK                        0x00010305 /* [struct hop_directory_link *arg] Extended interface for creating hard links.
                                                              * @throw: E_INVALID_HANDLE_FILETYPE: The given handle wasn't a directory INode.
                                                              * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_LINK: [...]
                                                              * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...] (`dli_linknode' was deleted)
                                                              * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: [...] (The given directory was deleted)
                                                              * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
                                                              * @throw: E_FSERROR_CROSS_DEVICE_LINK:   [...]
                                                              * @throw: E_FSERROR_ILLEGAL_PATH:        [...]
                                                              * @throw: E_FSERROR_ILLEGAL_PATH:        `dli_len' was ZERO(0)
                                                              * @throw: E_FSERROR_FILE_ALREADY_EXISTS: [...]
                                                              * @throw: E_FSERROR_DISK_FULL:           [...]
                                                              * @throw: E_FSERROR_TOO_MANY_HARD_LINKS: [...]
                                                              * @throw: E_FSERROR_READONLY:            [...]
                                                              * @throw: E_IOERROR:                     [...] */
#define HOP_DIRECTORY_SYMLINK                     0x00010306 /* [struct hop_directory_symlink *arg] Extended interface for creating symbolic links.
                                                              * @throw: E_INVALID_HANDLE_FILETYPE: The given handle wasn't a directory INode.
                                                              * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_SYMLINK: [...]
                                                              * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: [...] (The given directory was deleted)
                                                              * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
                                                              * @throw: E_FSERROR_ILLEGAL_PATH:        [...]
                                                              * @throw: E_FSERROR_ILLEGAL_PATH:        `dsl_len' was ZERO(0)
                                                              * @throw: E_FSERROR_FILE_ALREADY_EXISTS: [...]
                                                              * @throw: E_FSERROR_DISK_FULL:           [...]
                                                              * @throw: E_FSERROR_READONLY:            [...]
                                                              * @throw: E_IOERROR:                     [...] */
#define HOP_DIRECTORY_MKNOD                       0x00010307 /* [struct hop_directory_mknod *arg] Extended interface for create filesystem nodes.
                                                              * @throw: E_INVALID_HANDLE_FILETYPE: The given handle wasn't a directory INode.
                                                              * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_MKNOD: [...]
                                                              * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: [...] (The given directory was deleted)
                                                              * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
                                                              * @throw: E_FSERROR_ILLEGAL_PATH:        [...]
                                                              * @throw: E_FSERROR_ILLEGAL_PATH:        `dmn_len' was ZERO(0)
                                                              * @throw: E_FSERROR_FILE_ALREADY_EXISTS: [...]
                                                              * @throw: E_FSERROR_DISK_FULL:           [...]
                                                              * @throw: E_FSERROR_READONLY:            [...]
                                                              * @throw: E_IOERROR:                     [...] */
#define HOP_DIRECTORY_MKDIR                       0x00010308 /* [struct hop_directory_mkdir *arg] Extended interface for create directories.
                                                              * @throw: E_INVALID_HANDLE_FILETYPE: The given handle wasn't a directory INode.
                                                              * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_MKDIR: [...]
                                                              * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: [...] (The given directory was deleted)
                                                              * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
                                                              * @throw: E_FSERROR_ILLEGAL_PATH:        [...]
                                                              * @throw: E_FSERROR_ILLEGAL_PATH:        `dmd_len' was ZERO(0)
                                                              * @throw: E_FSERROR_FILE_ALREADY_EXISTS: [...]
                                                              * @throw: E_FSERROR_DISK_FULL:           [...]
                                                              * @throw: E_FSERROR_READONLY:            [...]
                                                              * @throw: E_IOERROR:                     [...] */
#define HOP_SUPERBLOCK_OPEN_BLOCKDEVICE           0x00010501 /* [struct hop_openfd *arg] Open the block-device associated with a superblock.
                                                              * @throw: E_INVALID_HANDLE_FILETYPE: The given handle wasn't a superblock.
                                                              * @throw: E_NO_SUCH_BLOCKDEVICE: No block device is bound to the given superblock.
                                                              * @return: * : The value written to `arg->of_hint' */
#define HOP_SUPERBLOCK_OPEN_WALL                  0x00010502 /* [struct hop_openfd *arg] Open the wall-clock associated with a superblock.
                                                              * @throw: E_INVALID_HANDLE_FILETYPE: The given handle wasn't a superblock.
                                                              * @return: * : The value written to `arg->of_hint' */
#define HOP_SUPERBLOCK_OPEN_DRIVER                0x00010503 /* [struct hop_openfd *arg] Open the driver associated with a superblock.
                                                              * @throw: E_INVALID_HANDLE_FILETYPE: The given handle wasn't a superblock.
                                                              * @return: * : The value written to `arg->of_hint' */
#define HOP_SUPERBLOCK_SYNC                       0x00010504 /* [unsigned int sync_device] Synchronize the given superblock (when `sync_device' is non-zero, also sync the associated block device (if any)).
                                                              * @throw: E_INVALID_HANDLE_FILETYPE: The given handle wasn't a superblock. */


/* For `HANDLE_TYPE_BLOCKDEVICE' */
#define HOP_BLOCKDEVICE_STAT                      0x00020001 /* [struct hop_blockdevice_stat *result] Read information about the datablock */
#define HOP_BLOCKDEVICE_SYNC                      0x00020002 /* Write any modified, but unsaved sectors to disk. */
#define HOP_BLOCKDEVICE_RDREADONLY                0x00020003 /* [uint32_t *result] Check if the given block-device is in read-only mode */
#define HOP_BLOCKDEVICE_WRREADONLY                0x00020004 /* [uint32_t enabled] Set the read-only mode for the given block-device.
                                                              * WARNING: Setting a drive root to read-only will prevent writes to partitions,
                                                              *          even though the partitions will continue to indicate being writable!
                                                              * To ensure that read-only is disabled for a partition & drive, do this:
                                                              * >> hop(fd,HOP_BLOCKDEVICE_WRREADONLY,0);           // Drive
                                                              * >> struct hop_openfd root;
                                                              * >> root.of_mode  = HOP_OPENFD_MODE_AUTO;
                                                              * >> root.of_flags = 0;
                                                              * >> hop(fd,HOP_BLOCKDEVICE_OPENDRIVEROOT,&root);
                                                              * >> hop(root.of_hint,HOP_BLOCKDEVICE_WRREADONLY,0);
                                                              * >> close(root.of_hint); */
#define HOP_BLOCKDEVICE_OPENDRIVEROOT             0x00020005 /* [struct hop_openfd *arg] Open the drive root of a partition, or re-open a partition.
                                                              * @throw: E_INVALID_HANDLE_FILETYPE: The given handle wasn't a block-device. */
#define HOP_BLOCKDEVICE_OPENDRIVEPART             0x00020006 /* [struct hop_blockdevice_openpart *arg] Open a given partition.
                                                              * If the given handle already refers to a partition, open a sibling partition instead.
                                                              * @throw: E_INVALID_HANDLE_FILETYPE:   The given handle wasn't a block-device.
                                                              * @throw: E_INDEX_ERROR_OUT_OF_BOUNDS: The given partition index is invalid. */


/* For `HANDLE_TYPE_FILE' */
#define HOP_FILE_CMPXCHG_OFFSET                   0x00040001 /* [struct hop_file_cmpxchg_offset *arg] Compare-exchange the current file offset. */
#define HOP_FILE_OPENNODE                         0x00040002 /* [struct hop_openfd *result] Open the Inode that is backing the file. */
#define HOP_FILE_OPENPATH                         0x00040003 /* [struct hop_openfd *result] Open the path within which the file is stored (aka. the VFS path of its containing directory). */
#define HOP_FILE_OPENDIR                          0x00040004 /* [struct hop_openfd *result] Open the directory Inode within which the file is stored. */
#define HOP_FILE_OPENDENTRY                       0x00040005 /* [struct hop_openfd *result] Open the directory entry used to describe the file's INode. */



/* For `HANDLE_TYPE_PATH' */
#define HOP_PATH_RECENT                           0x00060001 /* Cache the given path as having been used recently. */
#define HOP_PATH_OPENPARENT                       0x00060002 /* [struct hop_openfd *result] Open the parent node of a given path.
                                                              * @throw: E_NO_SUCH_OBJECT: The given path already describes the filesystem root
                                                              *                          (either the real one, or the one set by `chroot()') */
#define HOP_PATH_OPENVFS                          0x00060003 /* [struct hop_openfd *result] Open the filesystem root object
                                                              * @throw: E_NO_SUCH_OBJECT: The VFS root isn't accessible due to `chroot()' having
                                                              *                           being used to hide it from view. */
#define HOP_PATH_OPENNODE                         0x00060004 /* [struct hop_openfd *result] Open the mounted/bound INode associated with the path */
#define HOP_PATH_OPENDENTRY                       0x00060005 /* [struct hop_openfd *result] Open the directory entry detailing the name of the path */
#define HOP_PATH_ISDRIVE                          0x00060006 /* [uint32_t *result] Return the number of times that the given path is bound as a DOS-drive */
#define HOP_PATH_GETNAME                          0x00060007 /* [struct hop_path_getname *data] Read the name of the given path */
#define HOP_PATH_OPENCHILD                        0x00060008 /* [struct hop_path_openchild *data] Open a child of the given path */
#define HOP_PATH_RENAME                           0x00060009 /* [struct hop_path_rename *data] Rename a child entry within a given path (wrapper for `path_rename()') */
#define HOP_PATH_TRAVERSE                         0x0006000a /* [struct hop_path_traverse *data] Traverse the filesystem, starting at the given path (wrapper for `path_traverse_ex()') */


/* For HANDLE_TYPE_TASK */
#define HOP_TASK_JOIN                             0x00090001 /* [struct hop_task_join *data] Join a given thread
                                                              * HINT: You may also use a task handle with poll() to wait for the thread to terminate.
                                                              * @return: 0:          The thread has terminated. (Its exit status was written to `data->tj_status')
                                                              * @return: -ETIMEDOUT: The given timeout has expired. (data->tj_status was set to 0) */
#define HOP_TASK_GETTID                           0x00090002 /* hop() returns the TID of the given thread */
#define HOP_TASK_GETPID                           0x00090003 /* hop() returns the process ID of the given thread
                                                              * @throw: E_PROCESS_EXITED: [...] */
#define HOP_TASK_GETPPID                          0x00090004 /* hop() returns the parent process ID of the given thread
                                                              * If the thread doesn't have a parent, return 0 instead
                                                              * @throw: E_PROCESS_EXITED: [...] */
#define HOP_TASK_GETPGID                          0x00090005 /* hop() returns the process group ID of the given thread
                                                              * @throw: E_PROCESS_EXITED: [...] */
#define HOP_TASK_GETSID                           0x00090006 /* hop() returns the session ID of the given thread
                                                              * @throw: E_PROCESS_EXITED: [...] */
#define HOP_TASK_OPEN_PROCESS                     0x00090007 /* [struct hop_openfd *result] Open the process leader of the given thread.
                                                              * @throw: E_PROCESS_EXITED: [...] */
#define HOP_TASK_OPEN_PROCESS_PARENT              0x00090008 /* [struct hop_openfd *result] Open the parent process of the given thread.
                                                              * If the thread doesn't have a parent, return 0 instead
                                                              * @throw: E_NO_SUCH_PROCESS: The thread was detached from its parent process.
                                                              * @throw: E_PROCESS_EXITED:  [...] */
#define HOP_TASK_OPEN_PROCESS_GROUP_LEADER        0x00090009 /* [struct hop_openfd *result] Open the process group leader of the given thread.
                                                              * @throw: E_PROCESS_EXITED: [...] */
#define HOP_TASK_OPEN_SESSION_LEADER              0x0009000a /* [struct hop_openfd *result] Open the process group leader of the given thread.
                                                              * @throw: E_PROCESS_EXITED: [...] */
#define HOP_TASK_IS_PROCESS_LEADER                0x0009000b /* hop() returns 0/1 indicating if the thread is a process leader
                                                              * @throw: E_PROCESS_EXITED: [...] */
#define HOP_TASK_IS_PROCESS_GROUP_LEADER          0x0009000c /* hop() returns 0/1 indicating if the thread is a process group leader
                                                              * @throw: E_PROCESS_EXITED: [...] */
#define HOP_TASK_IS_SESSION_LEADER                0x0009000d /* hop() returns 0/1 indicating if the thread is a session leader
                                                              * @throw: E_PROCESS_EXITED: [...] */
#define HOP_TASK_DETACH                           0x0009000e /* Detach the given thread from its parent
                                                              * @return: true:  Successfully detached the given thread'
                                                              * @return: false: The given thread had already been detached.
                                                              * @throw: E_PROCESS_EXITED: [...] */
#define HOP_TASK_DETACH_CHILDREN                  0x0009000f /* Detach all child threads/processes of the given process
                                                              * @return: * : The number of detached children.
                                                              * @throw: E_PROCESS_EXITED: [...] */
#define HOP_TASK_SETPROCESSGROUPLEADER            0x00090010 /* [struct hop_task_setprocessgroupleader *data]
                                                              * Set the group leader for the process of the given thread.
                                                              * NOTE: If the given leader isn't a process leader,
                                                              *      `HOP_TASK_OPEN_PROCESS(leader)' will be used instead.
                                                              * @throw: E_PROCESS_EXITED: [...] */
#define HOP_TASK_SETSESSIONLEADER                 0x00090011 /* [struct hop_task_setsessionleader *data]
                                                              * Set the session leader for the process of the given thread.
                                                              * NOTE: If the given leader isn't a process leader,
                                                              *      `HOP_TASK_OPEN_PROCESS(leader)' will be used instead.
                                                              * @throw: E_PROCESS_EXITED: [...] */
/* TODO: HOP_TASK_SIGNAL -- FD-interface for the kill() and friends */
/* TODO: HOP_TASK_SIGNAL -- This should also include a function to raise a signal with a custom CPU context. */
/* TODO: HOP_TASK_RPC -- FD-interface for the `rpc_schedule()' system call */




/* For `HANDLE_TYPE_PIPE', `HANDLE_TYPE_PIPE_READER' and `HANDLE_TYPE_PIPE_WRITER' */
#define HOP_PIPE_STAT          0x000c0001 /* [struct hop_pipe_stat *result] Return statistics about the pipe */
#define HOP_PIPE_GETLIM        0x000c0002 /* [uint64_t *result] Return the max allocated size of the pipe. */
#define HOP_PIPE_SETLIM        0x000c0003 /* [size_t value] Set the max allocated pipe size to `value'. */
#define HOP_PIPE_XCHLIM        0x000c0004 /* [uint64_t *value] Exchange the old max allocated pipe size with `*value'. */
#define HOP_PIPE_WRITESOME     0x000c0005 /* [struct hop_pipe_writesome *data] A hybrid between `write()' with and without IO_NONBLOCK:
                                           * write() w/o IO_NONBLOCK: Block until _all_ data was written
                                           * write() w/ IO_NONBLOCK:  Don't block and only write data until the pipe limit is reached
                                           * HOP_PIPE_WRITESOME:      Block until _any_ data was written
                                           *                          NOTE: When this HOP is invoked with the `IO_NONBLOCK' flag,
                                           *                          it will behave identical to `write() w/ IO_NONBLOCK' */
#define HOP_PIPE_VWRITESOME    0x000c0006 /* [struct hop_pipe_vwritesome *data] Vectored variant of `HOP_PIPE_WRITESOME' */
#define HOP_PIPE_SKIPDATA      0x000c0007 /* [struct hop_pipe_skipdata *data] Skip buffered data, rather than reading it. */
#define HOP_PIPE_UNREAD        0x000c0008 /* [struct hop_pipe_unread *data] Try to unread previously read, but not yet written data. */
#define HOP_PIPE_UNWRITE       0x000c0009 /* [struct hop_pipe_unwrite *data] Try to unwrite previously written, but not yet read data. */
#define HOP_PIPE_SETWRITTEN    0x000c000a /* [IN:uint64_t *data] Set the total number of written bytes to `*data' (no-op if `*data' is greater than what is currently written, but not read)
                                           * [OUT:uint64_t *data] Return the number of available bytes for reading afterwards. */
#define HOP_PIPE_CLOSE         0x000c000b /* Explicitly close the pipe (same as `HOP_PIPE_SETLIM(0)')
                                           * Internally, this is automatically done when either last reader,
                                           * or the last writer object associated with some pipe is destroyed.
                                           * When a pipe is closed, no new data can be written to it (since it's
                                           * limit is set to 0), once all remaining data has been read, read() on
                                           * the pipe will no longer block, but instead always return 0 immediately.
                                           * A pipe can be un-closed by re-assigning a new limit value. */
#define HOP_PIPE_OPEN_PIPE     0x000c000c /* [struct hop_openfd *arg] Open the associated `HANDLE_TYPE_PIPE' of a `HANDLE_TYPE_PIPE_READER' or `HANDLE_TYPE_PIPE_WRITER' */
#define HOP_PIPE_CREATE_READER 0x000c000d /* [struct hop_openfd *arg] Create a new reader object for the associated pipe.
                                           * When the pipe(2) system call is used to create a new pipe, the internal `HANDLE_TYPE_PIPE'
                                           * object is hidden from user-space, and instead is wrapped by 1 reader, and 1 writer object.
                                           * By using `HOP_PIPE_CREATE_READER' and `HOP_PIPE_CREATE_WRITER', additional reader/writer
                                           * objects can be created for a pipe (although pretty much identical behavior can be achieved by
                                           * simply dup(2)-ing the original reader/writer).
                                           * Once either all reader objects have been destroyed, or all writer objects have, the underlying
                                           * pipe object is closed by having its limit set to 0 (s.a. `HOP_PIPE_CLOSE') */
#define HOP_PIPE_CREATE_WRITER 0x000c000e /* [struct hop_openfd *arg] Create a new writer object for the associated pipe.
                                           * When the pipe(2) system call is used to create a new pipe, the internal `HANDLE_TYPE_PIPE'
                                           * object is hidden from user-space, and instead is wrapped by 1 reader, and 1 writer object.
                                           * By using `HOP_PIPE_CREATE_READER' and `HOP_PIPE_CREATE_WRITER', additional reader/writer
                                           * objects can be created for a pipe (although pretty much identical behavior can be achieved by
                                           * simply dup(2)-ing the original reader/writer).
                                           * Once either all reader objects have been destroyed, or all writer objects have, the underlying
                                           * pipe object is closed by having its limit set to 0 (s.a. `HOP_PIPE_CLOSE') */


/* For `HANDLE_TYPE_PIDNS' */
#define HOP_PIDNS_GET_INDIRECTION 0x000f0001 /* [uint64_t *result] Return the indirection level of the given pidns */
#define HOP_PIDNS_OPEN_PARENT     0x000f0002 /* [struct hop_openfd *result] Open the parent of a given pidns.
                                              * @throw: E_NO_SUCH_PIDNS: The given PID namespace is the root-namespace. */



/* HANDLE_TYPE_DATAPART */
#define HOP_DATAPART_OPEN_DATABLOCK      0x00150001 /* [struct hop_openfd *result] Open the datablock associated with the given datapart.
                                                     * @return: * : The value written to `result->of_hint' */
#define HOP_DATAPART_OPEN_FUTEX          0x00150002 /* [struct hop_datablock_open_futex *result] Return, or create a futex for the given address.
                                                     * @return: * : The value written to `result->dof_openfd.of_hint' */
#define HOP_DATAPART_OPEN_FUTEX_EXISTING 0x00150003 /* [struct hop_datablock_open_futex *result] Return an existing a futex for the given address.
                                                     * @return: * : The value written to `result->dof_openfd.of_hint'
                                                     * @return: -ENOENT: No futex exists for the given address
                                                     * @return: -ERANGE: The given address lies outside of the bounds of this datapart
                                                     *                   Note that this can happen arbitrarily since it is possible that
                                                     *                   the datapart is truncated between the time of you accessing it,
                                                     *                   and invoking this command! */
#define HOP_DATAPART_STAT                0x00150004 /* [struct hop_datapart_stat *result] Read information about the datapart */
#define HOP_DATAPART_HASCHANGED          0x00150005 /* [struct hop_datablock_haschanged *result] Check for changes within the data part (s.a. `vm_datapart_haschanged()') */
//TODO:#define HOP_DATAPART_SYNC         -- vm_datapart_sync() */
//TODO:#define HOP_DATAPART_SPLIT        -- vm_datapart_split() */

/* HANDLE_TYPE_FUTEX */
#define HOP_FUTEX_OPEN_DATAPART          0x00160001 /* [struct hop_openfd *arg] Open the datapart associated with a given futex.
                                                     * @return: * : The value written to `result->of_hint'
                                                     * @return: -EOWNERDEAD: The datapart associated with the futex was destroyed. */
#define HOP_FUTEX_OPEN_DATABLOCK         0x00160002 /* [struct hop_openfd *arg] Open the datablock associated with the datapart associated with a given futex.
                                                     * @return: * : The value written to `result->of_hint'
                                                     * @return: -EOWNERDEAD: The datapart associated with the futex was destroyed. */
#define HOP_FUTEX_ISWAITING              0x00160003 /* @return: 1: There are threads are currently waiting on the futex
                                                     * @return: 0: No threads are waiting for this futex */
#define HOP_FUTEX_BROADCAST              0x00160004 /* Broadcast a wakeup-signal to all threads waiting for this futex.
                                                     * @return: *: The number of threads to which the signal was sent. */
/* TODO: HOP_FUTEX_GET_ADDRESS        (returns the address of the futex within its data-block) */
/* TODO: HOP_FUTEX_STAT               (Return HOP_FUTEX_ISWAITING, HOP_FUTEX_GET_ADDRESS, and some generalized info about HOP_FUTEX_OPEN_DATABLOCK) */

/* HANDLE_TYPE_FUTEXFD */
/* TODO: HOP_FUTEXFD_STAT             (returns a `HANDLE_TYPE_FUTEX' object) */
/* TODO: HOP_FUTEXFD_OPEN_FUTEX       (returns a `HANDLE_TYPE_FUTEX' object) */
/* TODO: HOP_FUTEXFD_OPEN_DATABLOCK   (returns a `HANDLE_TYPE_DATABLOCK' object) */
/* TODO: HANDLE_TYPE_DRIVER */
/* TODO: HANDLE_TYPE_DRIVER:d_cmdline */
/* TODO: HANDLE_TYPE_DRIVER:STAT:d_flags */
/* TODO: HANDLE_TYPE_DRIVER:STAT:d_loadaddr */
/* TODO: HANDLE_TYPE_DRIVER:STAT:d_loadstart */
/* TODO: HANDLE_TYPE_DRIVER:STAT:d_loadend */
/* TODO: HANDLE_TYPE_DRIVER:d_depvec (dereferencable as `for (d: driver_get_state()) if (d in self->d_depvec) yield d;') */
/* TODO: HANDLE_TYPE_DRIVER:driver_getname() */
/* TODO: HANDLE_TYPE_DRIVER:driver_getfile() */
/* TODO: HANDLE_TYPE_DRIVER:driver_getfilename() */
/* TODO: HANDLE_TYPE_DRIVER:driver_initialize() */
/* TODO: HANDLE_TYPE_DRIVER:driver_finalize() */
/* TODO: HANDLE_TYPE_DRIVER_STATE */
/* TODO: HANDLE_TYPE_DRIVER_STATE:Enumerate drivers */
/* TODO: HANDLE_TYPE_VM: */




#ifdef __CC__

/* Perform a handle operation specified by `cmd' */
#if defined(__CRT_HAVE_hop)
__LIBC __syscall_slong_t __NOTHROW_NCX(__VLIBCCALL hop)(__fd_t __fd, __syscall_ulong_t __cmd, ... /*, void *arg*/) __CASMNAME_SAME("hop");
#endif /* hop... */
#if defined(__CRT_HAVE_hopf)
__LIBC __syscall_slong_t __NOTHROW_NCX(__VLIBCCALL hopf)(__fd_t __fd, __syscall_ulong_t __cmd, __iomode_t __mode, ... /*, void *arg*/) __CASMNAME_SAME("hopf");
#endif /* hopf... */
#if defined(__CRT_HAVE_Hop)
__LIBC __syscall_slong_t __NOTHROW_NCX(__VLIBCCALL Hop)(__fd_t __fd, __syscall_ulong_t __cmd, ... /*, void *arg*/) __CASMNAME_SAME("Hop");
#endif /* hop... */
#if defined(__CRT_HAVE_Hopf)
__LIBC __syscall_slong_t __NOTHROW_NCX(__VLIBCCALL Hopf)(__fd_t __fd, __syscall_ulong_t __cmd, __iomode_t __mode, ... /*, void *arg*/) __CASMNAME_SAME("Hopf");
#endif /* hopf... */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_KOS_HOP_H */
