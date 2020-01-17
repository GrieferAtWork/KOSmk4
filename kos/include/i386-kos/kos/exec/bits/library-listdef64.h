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
#ifndef _I386_KOS_KOS_EXEC_BITS_LIBRARY_LISTDEF64_H
#define _I386_KOS_KOS_EXEC_BITS_LIBRARY_LISTDEF64_H 1

#include <__stdinc.h>

#include <hybrid/__pointer.h>
#include <hybrid/host.h>

#include <bits/types.h>

__SYSDECL_BEGIN

#ifdef __x86_64__
#define library_listdef64 library_listdef
#define __OFFSET_LIBRARY_LISTDEF_SIZE                      __OFFSET_LIBRARY_LISTDEF64_SIZE
#define __OFFSET_LIBRARY_LISTDEF_SIZEOF_POINTER            __OFFSET_LIBRARY_LISTDEF64_SIZEOF_POINTER
#define __OFFSET_LIBRARY_LISTDEF_FLAGS                     __OFFSET_LIBRARY_LISTDEF64_FLAGS
#define __OFFSET_LIBRARY_LISTDEF_FIRST                     __OFFSET_LIBRARY_LISTDEF64_FIRST
#define __OFFSET_LIBRARY_LISTDEF_COUNT                     __OFFSET_LIBRARY_LISTDEF64_COUNT
#define __OFFSET_LIBRARY_LISTDEF_MODULE_OFFSETOF_FILENAME  __OFFSET_LIBRARY_LISTDEF64_MODULE_OFFSETOF_FILENAME
#define __OFFSET_LIBRARY_LISTDEF_MODULE_OFFSETOF_LOADADDR  __OFFSET_LIBRARY_LISTDEF64_MODULE_OFFSETOF_LOADADDR
#define __OFFSET_LIBRARY_LISTDEF_MODULE_OFFSETOF_LOADSTART __OFFSET_LIBRARY_LISTDEF64_MODULE_OFFSETOF_LOADSTART
#define __OFFSET_LIBRARY_LISTDEF_ENTRY_OFFSETOF_NEXT       __OFFSET_LIBRARY_LISTDEF64_ENTRY_OFFSETOF_NEXT
#define __OFFSET_LIBRARY_LISTDEF_ENTRY_OFFSETOF_MODULE     __OFFSET_LIBRARY_LISTDEF64_ENTRY_OFFSETOF_MODULE
#define __SIZEOF_LIBRARY_LISTDEF                           __SIZEOF_LIBRARY_LISTDEF64
#endif /* __x86_64__ */

#define __OFFSET_LIBRARY_LISTDEF64_SIZE                      0
#define __OFFSET_LIBRARY_LISTDEF64_SIZEOF_POINTER            8
#define __OFFSET_LIBRARY_LISTDEF64_FLAGS                     16
#define __OFFSET_LIBRARY_LISTDEF64_FIRST                     24
#define __OFFSET_LIBRARY_LISTDEF64_COUNT                     32
#define __OFFSET_LIBRARY_LISTDEF64_MODULE_OFFSETOF_FILENAME  40
#define __OFFSET_LIBRARY_LISTDEF64_MODULE_OFFSETOF_LOADADDR  48
#define __OFFSET_LIBRARY_LISTDEF64_MODULE_OFFSETOF_LOADSTART 56
#define __OFFSET_LIBRARY_LISTDEF64_ENTRY_OFFSETOF_NEXT       64
#define __OFFSET_LIBRARY_LISTDEF64_ENTRY_OFFSETOF_MODULE     72
#define __SIZEOF_LIBRARY_LISTDEF64                           80
#ifdef __CC__
struct library_listdef64 /*[prefix(lld_)]*/ {
	__uint64_t     lld_size;                      /* [== sizeof(struct gdb_library_listdef)] Used for versioning */
	__uint64_t     lld_sizeof_pointer;            /* [== sizeof(void *)] Used for versioning and COMPAT64-mode */
	__uint64_t     lld_flags;                     /* Definition flags (Set of `LIBRARY_LISTDEF_F*') */
	__HYBRID_PTR64(void) lld_first;               /* [1..1] User-space pointer to the first module
	                                               * When `LIBRARY_LISTDEF_FPFIRST' isn't set: `first = (MODULE *)gll_first'
	                                               * When `LIBRARY_LISTDEF_FPFIRST' is set:    `first = *(MODULE **)gll_first' */
	__HYBRID_PTR64(void) lld_count;               /* [0..1] Optional: Number of loaded modules. (the size of this field is `lld_sizeof_pointer')
	                                               * When given, this is the max number of modules to enumerate before stopping.
	                                               * When used without `LIBRARY_LISTDEF_FLINKLST', this is exact number of modules
	                                               * When `LIBRARY_LISTDEF_FLINKLST' isn't set and this is field `NULL',
	                                               * then a NULL/empty filename is used as sentinal. */
	__int64_t      lld_module_offsetof_filename;  /* Offset to the module's filename field.
	                                               * When `LIBRARY_LISTDEF_FINLNAME' is set:    `name = (char *)((byte_t *)curr + lld_module_offsetof_filename)'
	                                               * When `LIBRARY_LISTDEF_FINLNAME' isn't set: `name = *(char **)((byte_t *)curr + lld_module_offsetof_filename)' */
	__int64_t      lld_module_offsetof_loadaddr;  /* Offset to the module's in-memory load address.          (`loadaddr = *(uintptr_t *)((byte_t *)curr + lld_module_offsetof_loadaddr)') */
	__int64_t      lld_module_offsetof_loadstart; /* Offset to the module's in-memory start mapping address. (`loadstart = *(uintptr_t *)((byte_t *)curr + lld_module_offsetof_loadstart)') */
	__int64_t      lld_entry_offsetof_next;       /* Offset-of-pointer-to / stride to the next
	                                               * When `LIBRARY_LISTDEF_FLINKLST' is set:    `next = *(MODULE **)((byte_t *)prev + lld_entry_offsetof_next)'
	                                               * When `LIBRARY_LISTDEF_FLINKLST' isn't set: `next = (MODULE *)((byte_t *)prev + lld_entry_offsetof_next)' */
	__int64_t      lld_entry_offsetof_module;     /* [valid_if(LIBRARY_LISTDEF_FPELEMENT)] Offset to the actual module structure (from individual elements) */
};
#endif /* __CC__ */


__SYSDECL_END

#endif /* !_I386_KOS_KOS_EXEC_BITS_LIBRARY_LISTDEF64_H */
