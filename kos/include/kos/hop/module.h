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
#ifndef _KOS_HOP_MODULE_H
#define _KOS_HOP_MODULE_H 1

#include "api.h"

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#include "openfd.h"

__DECL_BEGIN

#define HOP_DRIVER_STATE_NORMAL       0x0000 /* Normal (initial) driver state. */
#define HOP_DRIVER_STATE_DEPLOADING   0x0001 /* Driver dependencies have been loaded / are being loaded */
#define HOP_DRIVER_STATE_DEPLOADED    0x0002 /* Driver dependencies have been loaded */
#define HOP_DRIVER_STATE_RELOCATING   0x0004 /* Driver relocations have been applied / are being been applied */
#define HOP_DRIVER_STATE_RELOCATED    0x0008 /* Driver relocations have been applied */
#define HOP_DRIVER_STATE_INITIALIZING 0x0010 /* Initializers (constructors) have been executed / are currently being executed. */
#define HOP_DRIVER_STATE_INITIALIZED  0x0020 /* Initializers (constructors) have been executed. */
#define HOP_DRIVER_STATE_FINALIZING   0x0040 /* Finalizers (destructors) have been executed / are currently being executed. */
#define HOP_DRIVER_STATE_FINALIZED    0x0080 /* Finalizers (destructors) have been executed.
                                              * NOTE: This flag also means that the driver is no  longer
                                              *       registered as part  of the  current driver  state,
                                              *       meaning that the  current driver  state no  longer
                                              *       holds  a  reference  to  the  driver  in question.
                                              *       Though an older, dangling driver state might still
                                              *       hold such a reference.
                                              * NOTE: When this flag is set, additional driver sections can no
                                              *       longer be mapped into memory! */
#define HOP_DRIVER_STATE_FINALIZED_C  0x0100 /* INTERNAL: Finalizer callbacks were executed (and dependencies were decref()'ed),
                                              *           but other finalization components are still missing. */

#define HOP_DRIVER_FLAG_NORMAL       0x0000 /* Normal driver flags. */
#define HOP_DRIVER_FLAG_HAS_FILE     0x0001 /* The driver has an associated file. */
#define HOP_DRIVER_FLAG_HAS_FILENAME 0x0002 /* The driver has an associated filename. */
#define HOP_DRIVER_FLAG_HAS_EH_FRAME 0x0004 /* The driver has a `.eh_frame' section. */
#define HOP_DRIVER_FLAG_HAS_DYNSYM   0x0008 /* The driver has a `.dynsym' section. */



#define __OFFSET_HOP_DRIVER_STAT_STRUCT_SIZE 0
#define __OFFSET_HOP_DRIVER_STAT_STATE       4
#define __OFFSET_HOP_DRIVER_STAT_FLAGS       8
#define __OFFSET_HOP_DRIVER_STAT_LOADADDR    16
#define __OFFSET_HOP_DRIVER_STAT_LOADSTART   24
#define __OFFSET_HOP_DRIVER_STAT_LOADEND     32
#define __OFFSET_HOP_DRIVER_STAT_ARGC        40
#define __OFFSET_HOP_DRIVER_STAT_DEPC        48
#define __OFFSET_HOP_DRIVER_STAT_SYMCNT      56
#define __OFFSET_HOP_DRIVER_STAT_SHNUM       64
#define __OFFSET_HOP_DRIVER_STAT_STRTABSZ    72
#define __OFFSET_HOP_DRIVER_STAT_SHSTRTABSZ  80
#define __SIZEOF_HOP_DRIVER_STAT             88
#ifdef __CC__
struct hop_driver_stat /*[PREFIX(ds_)]*/ {
	__uint32_t            ds_struct_size;  /* [== sizeof(struct hop_driver_stat)]
	                                        * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                        * this value is too small  or doesn't match any  recognized
	                                        * structure version. */
	__uint32_t            ds_state;        /* Driver state (set of `HOP_DRIVER_STATE_*') */
	__uint32_t            ds_flags;        /* Driver flags (set of `HOP_DRIVER_FLAG_*') */
	__uint32_t          __ds_pad;          /* ... */
	__uint64_t            ds_loadaddr;     /* Load address of the driver. */
	__uint64_t            ds_loadstart;    /* Lowest address mapped by this driver (already adjusted for `ds_loadaddr'). */
	__uint64_t            ds_loadend;      /* Greatest address mapped by this driver (already adjusted for `ds_loadaddr'). */
	__uint64_t            ds_argc;         /* # of driver argument strings. */
	__uint64_t            ds_depc;         /* # of drivers that are dependencies of this one. */
	__uint64_t            ds_symcnt;       /* # of public symbols exported by the this driver. */
	__uint64_t            ds_shnum;        /* # of section headers defined by this driver */
	__uint64_t            ds_strtabsz;     /* Length of this driver's .strtab section (in bytes). */
	__uint64_t            ds_shstrtabsz;   /* Length of this driver's .shstrtab section (in bytes). */
};
#endif /* __CC__ */

#define __OFFSET_HOP_DRIVER_STRING_STRUCT_SIZE 0
#define __OFFSET_HOP_DRIVER_STRING_BUF         8
#define __OFFSET_HOP_DRIVER_STRING_SIZE        16
#define __OFFSET_HOP_DRIVER_STRING_INDEX       24
#define __SIZEOF_HOP_DRIVER_STRING             32
#ifdef __CC__
struct hop_driver_string /*[PREFIX(ds_)]*/ {
	__uint32_t          ds_struct_size; /* [== sizeof(struct hop_driver_string)]
	                                     * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                     * this value is too small  or doesn't match any  recognized
	                                     * structure version. */
	__uint32_t        __ds_pad1;        /* ... */
	char               *ds_buf;         /* [1..ds_size] User-space buffer to-be filled with the string. */
	__HOP_PAD_POINTER(__ds_pad2);       /* ... */
	__size_t            ds_size;        /* [IN] Available buffer size (in bytes).
	                                     * [OUT] Required buffer size (in bytes; including a trailing NUL) */
	__HOP_PAD_POINTER(__ds_pad3);       /* ... */
	__uint64_t          ds_index;       /* [IN] String index (meaning depends on command) */
};
#endif /* __CC__ */

#define __OFFSET_HOP_DRIVER_OPEN_DEPENDENCY_STRUCT_SIZE 0
#define __OFFSET_HOP_DRIVER_OPEN_DEPENDENCY_DEPNO       8
#define __OFFSET_HOP_DRIVER_OPEN_DEPENDENCY_RESULT      16
#define __SIZEOF_HOP_DRIVER_OPEN_DEPENDENCY             24
#ifdef __CC__
struct hop_driver_open_dependency /*[PREFIX(dod_)]*/ {
	__uint32_t        dod_struct_size; /* [== sizeof(struct hop_driver_open_dependency)]
	                                    * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                    * this value is too small  or doesn't match any  recognized
	                                    * structure version. */
	__uint32_t      __dod_pad1;        /* ... */
	__uint64_t        dod_depno;       /* Dependency ID */
	struct hop_openfd dod_result;      /* Resulting handle */
};
#endif /* __CC__ */

/************************************************************************/
/* HANDLE_TYPE_MODULE                                                   */
/************************************************************************/
/* [struct hop_driver_stat *result] Return statistics about the driver */
#define HOP_DRIVER_STAT                HOP_CMD(HANDLE_TYPE_MODULE, 0x0001)

/* [struct hop_driver_string *result] Return the driver's name (`ds_index' must be `0') */
#define HOP_DRIVER_GET_NAME            HOP_CMD(HANDLE_TYPE_MODULE, 0x0002)

/* [struct hop_driver_string *result] Return the driver's cmdline (`ds_index' must be `0') */
#define HOP_DRIVER_GET_CMDLINE         HOP_CMD(HANDLE_TYPE_MODULE, 0x0003)

/* [struct hop_driver_string *result] Return the driver's filename (`ds_index' must be `0') */
#define HOP_DRIVER_GET_FILENAME        HOP_CMD(HANDLE_TYPE_MODULE, 0x0004)

/* [struct hop_driver_string *result]
 * Return one of the driver's argument string. (`ds_index' specifies the argument index) */
#define HOP_DRIVER_GET_ARGV            HOP_CMD(HANDLE_TYPE_MODULE, 0x0005)

/* [struct hop_openfd *result] Open the driver's file
 * @return: == arg->of_hint */
#define HOP_DRIVER_OPEN_FILE           HOP_CMD(HANDLE_TYPE_MODULE, 0x0006)

/* [struct hop_driver_open_dependency *result] Open the driver's file
 * @return: == result->dod_result.of_hint */
#define HOP_DRIVER_OPEN_DEPENDENCY     HOP_CMD(HANDLE_TYPE_MODULE, 0x0007)

/* Run driver initializers (if those hadn't been run already) */
#define HOP_DRIVER_INITIALIZE          HOP_CMD(HANDLE_TYPE_MODULE, 0x0008)

/* Run driver finalizers (if those hadn't been run already) */
#define HOP_DRIVER_FINALIZE            HOP_CMD(HANDLE_TYPE_MODULE, 0x0009)



/************************************************************************/
/* HANDLE_TYPE_DRIVER_LOADLIST                                          */
/************************************************************************/
/* [uint64_t *result] Return the # of drivers contained with this driver state. */
#define HOP_DRIVER_LOADLIST_GET_COUNT  HOP_CMD(HANDLE_TYPE_DRIVER_LOADLIST, 0x0002)

/* [struct hop_driver_open_dependency *result] Open one of the individual drivers.
 * @throw: E_NO_SUCH_OBJECT: The indexed driver has been destroyed.
 * @return: == result->dod_result.of_hint */
#define HOP_DRIVER_LOADLIST_GET_DRIVER HOP_CMD(HANDLE_TYPE_DRIVER_LOADLIST, 0x0003)

__DECL_END

#endif /* !_KOS_HOP_MODULE_H */
