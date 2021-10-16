/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_HOP_MFILE_H
#define _KOS_HOP_MFILE_H 1

#include "api.h"

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#include "openfd.h"

/* TODO: Refactor to <kos/hop/mfile.h> */

__DECL_BEGIN

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
	                                       * this value is too small  or doesn't match any  recognized
	                                       * structure version. */
	__uint32_t   ds_features;             /* Set of `HOP_DATABLOCK_STAT_FEATURE_*' */
	__uint32_t   ds_pageshift;            /* `struct mfile::db_pageshift'
	                                       * NOTE: Used to convert to/from data-pages and physical/virtual memory pages
	                                       * HINT: VIRT_PAGE == DATA_PAGE << ds_pageshift
	                                       *       DATA_PAGE == VIRT_PAGE >> ds_pageshift */
	__uint32_t __ds_pad;                  /* ... */
	__uint64_t   ds_part_mapped;          /* The number of parts chained via `struct mfile::mf_parts' */
	__uint64_t   ds_part_mapped_pages;    /* Sum of `vm_datapart_numdpages()' of all mapped parts */
	__uint64_t   ds_part_st_incore;       /* The number of MPART_ST_MEM-parts chained via `struct mfile::mf_parts' */
	__uint64_t   ds_part_st_incore_pages; /* Sum of `vm_datapart_numdpages()' of all MPART_ST_MEM parts */
	__uint64_t   ds_part_st_locked;       /* The number of VM_DATAPART_STATE_LOCKED-parts chained via `struct mfile::mf_parts' */
	__uint64_t   ds_part_st_locked_pages; /* Sum of `vm_datapart_numdpages()' of all VM_DATAPART_STATE_LOCKED parts */
	__uint64_t   ds_part_st_inswap;       /* The number of MPART_ST_SWP-parts chained via `struct mfile::mf_parts' */
	__uint64_t   ds_part_st_inswap_pages; /* Sum of `vm_datapart_numdpages()' of all MPART_ST_SWP parts */
	__uint64_t   ds_part_f_locked;        /* Number of parts with the `MPART_F_MLOCK' flag set */
	__uint64_t   ds_part_f_locked_pages;  /* Sum of `vm_datapart_numdpages()' of all parts with the `MPART_F_MLOCK' flag set */
	__uint64_t   ds_part_f_changed;       /* Number of parts with the `MPART_F_CHANGED' flag set */
	__uint64_t   ds_part_f_changed_pages; /* Sum of `vm_datapart_numdpages()' of all parts with the `MPART_F_CHANGED' flag set */
	__uint64_t   ds_part_ram_blocks;      /* Total number of individual RAM blocks allocated by INCORE/LOCKED parts */
	__uint64_t   ds_part_swap_blocks;     /* Total number of SWAP blocks allocated by INSWAP parts */
	__uint64_t   ds_part_uninit_pages;    /* Total number of data-pages set to `MPART_BLOCK_ST_NDEF' */
	__uint64_t   ds_part_init_pages;      /* Total number of data-pages set to `MPART_BLOCK_ST_LOAD' */
	__uint64_t   ds_part_changed_pages;   /* Total number of data-pages set to `MPART_BLOCK_ST_CHNG' */
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
	                                    * this value is too small  or doesn't match any  recognized
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
	                                    * this value is too small  or doesn't match any  recognized
	                                    * structure version. */
	__uint32_t      __dsb_pad;         /* ... */
	/* NOTE: `bsr_minbyte' and `bsr_maxbyte' are simply adjusted such that
	 *        they span  whole  data  pages, meaning  that  `bsr_count'  will  always
	 *        be a multiple of  `getpagesize() >> [HOP_DATABLOCK_STAT]:ds_pageshift',
	 *        and may be greater than the total number of bytes between `bsr_minbyte'
	 *        and `bsr_maxbyte'. */
	__uint64_t        dsb_minbyte;     /* [IN] Offset of the lowest byte that should be synced. */
	__uint64_t        dsb_maxbyte;     /* [IN] Offset of the greatest byte that should be synced. */
	__uint64_t        dsb_count;       /* [OUT] Number of synced data bytes. */
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
	                                    * this value is too small  or doesn't match any  recognized
	                                    * structure version. */
	__uint32_t      __dop_pad;         /* ... */
	__uint64_t        dop_pageno;      /* [IN]  The page-index (pageid64_t) of the first page that should be opened.
	                                    * [OUT] The page-index (pageid64_t) of the first page that was opened.
	                                    *       This is equal to the  `ds_minpage' field return by  `HOP_MPART_STAT',
	                                    *       and  may  be  lower  than  the  originally  given  `dop_pageno'  when
	                                    *       `HOP_DATABLOCK_OPEN_PART' was used, but guarantied to be equal to the
	                                    *       original   value   when  `HOP_DATABLOCK_OPEN_PART_EXACT'   was  used. */
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
	                                    * this value is too small  or doesn't match any  recognized
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
	                                      * this value is too small  or doesn't match any  recognized
	                                      * structure version. */
	__uint32_t        __dof_pad;         /* ... */
	__uint64_t          dof_address;     /* [IN] Address of the futex */
	struct hop_openfd   dof_openfd;      /* File descriptor open controller (filled with a handle for the futex). */
};
#endif /* __CC__ */


#define __OFFSET_HOP_INODE_CHMOD_STRUCT_SIZE 0
#define __OFFSET_HOP_INODE_CHMOD_PERM_MASK   4
#define __OFFSET_HOP_INODE_CHMOD_PERM_FLAG   8
#define __OFFSET_HOP_INODE_CHMOD_PERM_OLD    12
#define __SIZEOF_HOP_INODE_CHMOD             16
#ifdef __CC__
struct hop_inode_chmod /*[PREFIX(icm_)]*/ {
	__uint32_t            icm_struct_size; /* [== sizeof(struct hop_inode_chmod)]
	                                        * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                        * this value is too small  or doesn't match any  recognized
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
#define __SIZEOF_HOP_INODE_CHOWN             20
#ifdef __CC__
struct hop_inode_chown /*[PREFIX(ico_)]*/ {
	__uint32_t            ico_struct_size; /* [== sizeof(struct hop_inode_chown)]
	                                        * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                        * this value is too small  or doesn't match any  recognized
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
	                                        * this value is too small  or doesn't match any  recognized
	                                        * structure version. */
	__uint32_t          __don_pad1;        /* ... */
	/* Open the INode/Directory entry of a given child of some directory.
	 * WARNING: This function does not follow symbolic links, doesn't understand
	 *          the special paths `.' and `..', and will not even traverse  more
	 *          than   a   single   directory   component   (aka.   no  slashes)
	 *          These  are  the  low-level  functions  used  to  lookup  a child
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
	                                          * this value is too small  or doesn't match any  recognized
	                                          * structure version. */
	__uint32_t          __dcf_pad1;          /* ... */
	/* Create/open a child within a given directory.
	 * WARNING: This function does not follow symbolic links, doesn't understand
	 *          the special paths `.' and `..', and will not even traverse  more
	 *          than   a   single   directory   component   (aka.   no  slashes)
	 *          These  are  the  low-level  functions  used  to  lookup  a child
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
                                                     * This  flag is set when the node's NLINK counter has reached
                                                     * ZERO(0) as a result of the remove operation, at which point
                                                     * the `INODE_FDELETED' flag is set,  and the node is  removed
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
	                                         * this value is too small  or doesn't match any  recognized
	                                         * structure version. */
	__uint32_t          __drm_pad1;         /* ... */
	/* Remove a child from a given directory.
	 * WARNING: This function does not follow symbolic links, doesn't understand
	 *          the special paths `.' and `..', and will not even traverse  more
	 *          than   a   single   directory   component   (aka.   no  slashes)
	 *          These  are  the  low-level  functions  used  to  lookup  a child
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
	                                         * this value is too small  or doesn't match any  recognized
	                                         * structure version. */
	__uint32_t          __drn_pad1;         /* ... */
	/* Rename a child in a given directory, potentially also moving it into another directory.
	 * WARNING: This function does not follow symbolic links, doesn't understand
	 *          the special paths `.' and `..', and will not even traverse  more
	 *          than   a   single   directory   component   (aka.   no  slashes)
	 *          These  are  the  low-level  functions  used  to  lookup  a child
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
	                                          * this value is too small  or doesn't match any  recognized
	                                          * structure version. */
	__uint32_t          __dli_pad1;          /* ... */
	/* Create hard links within a given directory.
	 * WARNING: This function does not follow symbolic links, doesn't understand
	 *          the special paths `.' and `..', and will not even traverse  more
	 *          than   a   single   directory   component   (aka.   no  slashes)
	 *          These  are  the  low-level  functions  used  to  lookup  a child
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
	                                          * this value is too small  or doesn't match any  recognized
	                                          * structure version. */
	__uint32_t          __dsl_pad1;          /* ... */
	/* Create a new symbolic link within a given directory.
	 * WARNING: This function does not follow symbolic links, doesn't understand
	 *          the special paths `.' and `..', and will not even traverse  more
	 *          than   a   single   directory   component   (aka.   no  slashes)
	 *          These  are  the  low-level  functions  used  to  lookup  a child
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
	                                          * this value is too small  or doesn't match any  recognized
	                                          * structure version. */
	__uint32_t          __dmn_pad1;          /* ... */
	/* Create a new symbolic link within a given directory.
	 * WARNING: This function does not follow symbolic links, doesn't understand
	 *          the special paths `.' and `..', and will not even traverse  more
	 *          than   a   single   directory   component   (aka.   no  slashes)
	 *          These  are  the  low-level  functions  used  to  lookup  a child
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
	                                          * this value is too small  or doesn't match any  recognized
	                                          * structure version. */
	__uint32_t          __dmd_pad1;          /* ... */
	/* Create a new symbolic link within a given directory.
	 * WARNING: This function does not follow symbolic links, doesn't understand
	 *          the special paths `.' and `..', and will not even traverse  more
	 *          than   a   single   directory   component   (aka.   no  slashes)
	 *          These  are  the  low-level  functions  used  to  lookup  a child
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


#define HOP_SUPERBLOCK_FEAT_NORMAL   0x00000000
#define HOP_SUPERBLOCK_FEAT_SYMLINKS 0x00000001 /* The filesystem supports symbolic links (when clear, `sbs_symlink_max' is `0')
                                                 * s.a.: `pathconf(_PC_2_SYMLINKS)' */
#define HOP_SUPERBLOCK_FEAT_HRDLINKS 0x00000002 /* The filesystem supports hard links (when clear, `sbs_link_max' is `1') */

#define __OFFSET_HOP_SUPERBLOCK_FEATURES_STRUCT_SIZE        0
#define __OFFSET_HOP_SUPERBLOCK_FEATURES_FEATURES           4
#define __OFFSET_HOP_SUPERBLOCK_FEATURES_SECTOR_SIZE        8
#define __OFFSET_HOP_SUPERBLOCK_FEATURES_LINK_MAX           16
#define __OFFSET_HOP_SUPERBLOCK_FEATURES_NAME_MAX           24
#define __OFFSET_HOP_SUPERBLOCK_FEATURES_SYMLINK_MAX        32
#define __OFFSET_HOP_SUPERBLOCK_FEATURES_REC_INCR_XFER_SIZE 40
#define __OFFSET_HOP_SUPERBLOCK_FEATURES_REC_MAX_XFER_SIZE  44
#define __OFFSET_HOP_SUPERBLOCK_FEATURES_REC_MIN_XFER_SIZE  48
#define __OFFSET_HOP_SUPERBLOCK_FEATURES_REC_XFER_ALIGN     52
#define __OFFSET_HOP_SUPERBLOCK_FEATURES_FILESIZEBITS       56
#define __OFFSET_HOP_SUPERBLOCK_FEATURES_MAGIC              60
#define __SIZEOF_HOP_SUPERBLOCK_FEATURES                    64
#ifdef __CC__
struct hop_superblock_features /*[PREFIX(sbf_)]*/ {
	__uint32_t            sbf_struct_size;        /* [== sizeof(struct hop_superblock_features)]
	                                               * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                               * this value is too small  or doesn't match any  recognized
	                                               * structure version. */
	__uint32_t            sbf_features;           /* Filesystem features (Set of `HOP_SUPERBLOCK_FEAT_*') */
	__uint64_t            sbf_sector_size;        /* Sector/Fragment/Cluster/Frame/Page/whatever-you-want-to-call-it  size  of
	                                               * the filesystem. Calculated from `struct hop_datablock_stat::ds_pageshift'
	                                               * s.a.: `struct statfs::f_frsize' */
	__uint64_t            sbf_link_max;           /* Max # of links a file may have
	                                               * s.a.: `pathconf(_PC_LINK_MAX)' */
	__uint64_t            sbf_name_max;           /* Max # of chars in a file name
	                                               * s.a.: `struct statfs::f_namelen', `pathconf(_PC_NAME_MAX)' */
	__uint64_t            sbf_symlink_max;        /* Max length of text contained within symbolic links
	                                               * s.a.: `pathconf(_PC_SYMLINK_MAX)' */
	__uint32_t            sbf_rec_incr_xfer_size; /* Buffer size increments for efficient disk transfer operations
	                                               * s.a.: `pathconf(_PC_REC_INCR_XFER_SIZE)' */
	__uint32_t            sbf_rec_max_xfer_size;  /* Max buffer size for efficient disk transfer operations
	                                               * s.a.: `pathconf(_PC_REC_MAX_XFER_SIZE)' */
	__uint32_t            sbf_rec_min_xfer_size;  /* Min buffer size for efficient disk transfer operations
	                                               * s.a.: `struct statfs::f_bsize', `pathconf(_PC_REC_MIN_XFER_SIZE)' */
	__uint32_t            sbf_rec_xfer_align;     /* Required in-memory buffer alignment for efficient disk transfer operations */
	__uint8_t             sbf_filesizebits;       /* Max # of bits in a file's size field (usually 64 or 32) */
	__uint8_t           __sbf_pad1[3];            /* ... */
	__uint32_t            sbf_magic;              /* Filesystem ~magic~ (one of the constants from `<linux/magic.h>')
	                                               * s.a.: `struct statfs::f_type' */
};
#endif /* __CC__ */




/************************************************************************/
/* HANDLE_TYPE_MFILE                                                    */
/************************************************************************/

/* [struct hop_datablock_stat *result] Read information about the datablock */
#define HOP_DATABLOCK_STAT                        HOP_CMD(HANDLE_TYPE_MFILE, 0x0001)

/* [uint64_t *result] Save all modified parts, and store the number of synced bytes in `*result' */
#define HOP_MFILE_SYNCALL                         HOP_CMD(HANDLE_TYPE_MFILE, 0x0002)

/* [struct hop_datablock_syncpages *arg] Save all modified parts within the given range. */
#define HOP_DATABLOCK_SYNCPAGES                   HOP_CMD(HANDLE_TYPE_MFILE, 0x0003)

/* [struct hop_datablock_syncbytes *arg] Save all modified bytes within the given range. */
#define HOP_DATABLOCK_SYNCBYTES                   HOP_CMD(HANDLE_TYPE_MFILE, 0x0004)

/* Anonymize all of the mem-parts of this mem-file. */
#define HOP_DATABLOCK_ANONYMIZE                   HOP_CMD(HANDLE_TYPE_MFILE, 0x0005)

/* [int *result] Deanonymize this datablock, allowing parts to be tracked once again.
 * @throw: E_INVALID_CONTEXT: The given datablock must remain anonymous.
 * Write 0/1 to *result, indicative of:
 *  - 0: The data block wasn't anonymous (aka. was already deanonymized).
 *  - 1: The data block has been deanonymized. */
#define HOP_DATABLOCK_DEANONYMIZE                 HOP_CMD(HANDLE_TYPE_MFILE, 0x0006)

/* [struct hop_datablock_openpart *arg] Lookup (and  create  if  missing)  the  data
 * part associated with a given page offset (s.a. `vm_paged_datablock_locatepart()')
 * @return: == arg->dop_openfd.of_hint */
#define HOP_DATABLOCK_OPEN_PART                   HOP_CMD(HANDLE_TYPE_MFILE, 0x0007)

/* [struct hop_datablock_openpart *arg] Same   as   `HOP_DATABLOCK_OPEN_PART',  but   make  sure
 * that the part begins at the exact given offset (s.a. `vm_paged_datablock_locatepart_exact()')
 * @return: == arg->dop_openfd.of_hint */
#define HOP_DATABLOCK_OPEN_PART_EXACT             HOP_CMD(HANDLE_TYPE_MFILE, 0x0008)

/* [struct hop_datablock_haschanged *arg] Check  for  changes
 * within the given address range (s.a. `mfile_haschanged()') */
#define HOP_DATABLOCK_HASCHANGED                  HOP_CMD(HANDLE_TYPE_MFILE, 0x0009)

/* [struct hop_datablock_open_futex *result] Return, or create a futex for the given address.
 * @return: == result->dof_openfd.of_hint */
#define HOP_DATABLOCK_OPEN_FUTEX                  HOP_CMD(HANDLE_TYPE_MFILE, 0x000a)

/* [struct hop_datablock_open_futex *result] Return an existing a futex for the given address.
 * @return: == result->dof_openfd.of_hint
 * @return: -ENOENT: No futex exists for the given address */
#define HOP_DATABLOCK_OPEN_FUTEX_EXISTING         HOP_CMD(HANDLE_TYPE_MFILE, 0x000b)

/* [struct hop_openfd *arg] Open the superblock associated with an INode.
 * @throw: E_INVALID_HANDLE_FILETYPE: The given handle wasn't an INode.
 * @return: == arg->of_hint */
#define HOP_INODE_OPEN_SUPERBLOCK                 HOP_CMD(HANDLE_TYPE_MFILE, 0x0101)

/* [struct hop_inode_chmod *arg] Extended interface for changing file permissions in a more controlled manner.
 * @throw: E_INVALID_HANDLE_FILETYPE: The given handle wasn't an INode. */
#define HOP_INODE_CHMOD                           HOP_CMD(HANDLE_TYPE_MFILE, 0x0102)

/* [struct hop_inode_chown *arg] Extended interface for changing file ownership in a more controlled manner.
 * @throw: E_INVALID_HANDLE_FILETYPE: The given handle wasn't an INode. */
#define HOP_INODE_CHOWN                           HOP_CMD(HANDLE_TYPE_MFILE, 0x0103)

/* TODO: HOP_INODE_READ_BLOCKING -- An always-blocking version of read(2) that uses the kernel-space function
 *                                 `inode_read_blocking', which starts blocking when reading past the end of
 *                                  a regular file, and gets unblocked when another process writes the missing
 *                                  data. */

/* [struct hop_directory_opennode *arg] Extended interface for traversing a directory.
 * @throw: E_INVALID_HANDLE_FILETYPE: The given handle wasn't a directory INode.
 * @throw: E_FSERROR_FILE_NOT_FOUND: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_READDIR: [...]
 * @throw: E_IOERROR: [...] */
#define HOP_DIRECTORY_OPENNODE                    HOP_CMD(HANDLE_TYPE_MFILE, 0x0301)

/* [struct hop_directory_creatfile *arg] Extended interface for creating new files.
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
#define HOP_DIRECTORY_CREATFILE                   HOP_CMD(HANDLE_TYPE_MFILE, 0x0302)

/* [struct hop_directory_remove *arg] Extended interface for removing files.
 * WARNING: This function may  leave behind  stale PATH nodes  which may  still be  accessible,
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
#define HOP_DIRECTORY_REMOVE                      HOP_CMD(HANDLE_TYPE_MFILE, 0x0303)

/* [struct hop_directory_rename *arg] Extended interface for renaming files.
 * WARNING: This function may  leave behind  stale PATH nodes  which may  still be  accessible,
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
#define HOP_DIRECTORY_RENAME                      HOP_CMD(HANDLE_TYPE_MFILE, 0x0304)

/* [struct hop_directory_link *arg] Extended interface for creating hard links.
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
#define HOP_DIRECTORY_LINK                        HOP_CMD(HANDLE_TYPE_MFILE, 0x0305)

/* [struct hop_directory_symlink *arg] Extended interface for creating symbolic links.
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
#define HOP_DIRECTORY_SYMLINK                     HOP_CMD(HANDLE_TYPE_MFILE, 0x0306)

/* [struct hop_directory_mknod *arg] Extended interface for create filesystem nodes.
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
#define HOP_DIRECTORY_MKNOD                       HOP_CMD(HANDLE_TYPE_MFILE, 0x0307)

/* [struct hop_directory_mkdir *arg] Extended interface for create directories.
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
#define HOP_DIRECTORY_MKDIR                       HOP_CMD(HANDLE_TYPE_MFILE, 0x0308)

/* [struct hop_openfd *arg] Open the block-device associated with a superblock.
 * @throw: E_INVALID_HANDLE_FILETYPE:                 The given handle wasn't a superblock.
 * @throw: E_NO_DEVICE:E_NO_DEVICE_KIND_BLKDEV: No block device is bound to the given superblock.
 * @return: == arg->of_hint */
#define HOP_SUPERBLOCK_OPEN_BLKDEV                HOP_CMD(HANDLE_TYPE_MFILE, 0x0501)

/* [struct hop_openfd *arg] Open the driver associated with a superblock.
 * @throw: E_INVALID_HANDLE_FILETYPE: The given handle wasn't a superblock.
 * @return: == arg->of_hint */
#define HOP_SUPERBLOCK_OPEN_DRIVER                HOP_CMD(HANDLE_TYPE_MFILE, 0x0502)

/* [unsigned int sync_device] Synchronize the given superblock (when `sync_device' is non-zero, also sync the associated block device (if any)).
 * @throw: E_INVALID_HANDLE_FILETYPE: The given handle wasn't a superblock. */
#define HOP_SUPERBLOCK_SYNC                       HOP_CMD(HANDLE_TYPE_MFILE, 0x0503)

/* [struct hop_superblock_features *arg] Gather features of the superblock associated with a given fd.
 * NOTE: When the given fd isn't a super-block, a cast to a superblock is attempted. */
#define HOP_SUPERBLOCK_FEATURES                   HOP_CMD(HANDLE_TYPE_MFILE, 0x0504)

__DECL_END

#endif /* !_KOS_HOP_MFILE_H */
