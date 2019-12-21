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
#ifndef _KOS_EXEC_BITS_LIBRARY_LISTDEF_H
#define _KOS_EXEC_BITS_LIBRARY_LISTDEF_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

__SYSDECL_BEGIN

#define __OFFSET_LIBRARY_LISTDEF_SIZE                      0
#define __OFFSET_LIBRARY_LISTDEF_SIZEOF_POINTER            __SIZEOF_SIZE_T__
#define __OFFSET_LIBRARY_LISTDEF_FLAGS                     (__SIZEOF_SIZE_T__ * 2)
#define __OFFSET_LIBRARY_LISTDEF_FIRST                     (__SIZEOF_SIZE_T__ * 2 + __SIZEOF_POINTER__)
#define __OFFSET_LIBRARY_LISTDEF_COUNT                     (__SIZEOF_SIZE_T__ * 2 + __SIZEOF_POINTER__ * 2)
#define __OFFSET_LIBRARY_LISTDEF_MODULE_OFFSETOF_FILENAME  (__SIZEOF_SIZE_T__ * 2 + __SIZEOF_POINTER__ * 3)
#define __OFFSET_LIBRARY_LISTDEF_MODULE_OFFSETOF_LOADADDR  (__SIZEOF_SIZE_T__ * 2 + __SIZEOF_POINTER__ * 3 + __SIZEOF_PTRDIFF_T__)
#define __OFFSET_LIBRARY_LISTDEF_MODULE_OFFSETOF_LOADSTART (__SIZEOF_SIZE_T__ * 2 + __SIZEOF_POINTER__ * 3 + __SIZEOF_PTRDIFF_T__ * 2)
#define __OFFSET_LIBRARY_LISTDEF_ENTRY_OFFSETOF_NEXT       (__SIZEOF_SIZE_T__ * 2 + __SIZEOF_POINTER__ * 3 + __SIZEOF_PTRDIFF_T__ * 3)
#define __OFFSET_LIBRARY_LISTDEF_ENTRY_OFFSETOF_MODULE     (__SIZEOF_SIZE_T__ * 2 + __SIZEOF_POINTER__ * 3 + __SIZEOF_PTRDIFF_T__ * 4)
#define __SIZEOF_LIBRARY_LISTDEF                           (__SIZEOF_SIZE_T__ * 2 + __SIZEOF_POINTER__ * 3 + __SIZEOF_PTRDIFF_T__ * 5)
#ifdef __CC__
struct library_listdef /*[prefix(lld_)]*/ {
	__size_t       lld_size;                      /* [== sizeof(struct gdb_library_listdef)] Used for versioning */
	__size_t       lld_sizeof_pointer;            /* [== sizeof(void *)] Used for versioning and COMPAT32-mode */
	__uintptr_t    lld_flags;                     /* Definition flags (Set of `LIBRARY_LISTDEF_F*') */
	void          *lld_first;                     /* [1..1] User-space pointer to the first module
	                                               * When `LIBRARY_LISTDEF_FPFIRST' isn't set: `first = (MODULE *)gll_first'
	                                               * When `LIBRARY_LISTDEF_FPFIRST' is set:    `first = *(MODULE **)gll_first' */
	void          *lld_count;                     /* [0..1] Optional: Number of loaded modules. (the size of this field is `lld_sizeof_pointer')
	                                               * When given, this is the max number of modules to enumerate before stopping.
	                                               * When used without `LIBRARY_LISTDEF_FLINKLST', this is exact number of modules
	                                               * When `LIBRARY_LISTDEF_FLINKLST' isn't set and this is field `NULL',
	                                               * then a NULL/empty filename is used as sentinal. */
	__ptrdiff_t    lld_module_offsetof_filename;  /* Offset to the module's filename field.
	                                               * When `LIBRARY_LISTDEF_FINLNAME' is set:    `name = (char *)((byte_t *)curr + lld_module_offsetof_filename)'
	                                               * When `LIBRARY_LISTDEF_FINLNAME' isn't set: `name = *(char **)((byte_t *)curr + lld_module_offsetof_filename)' */
	__ptrdiff_t    lld_module_offsetof_loadaddr;  /* Offset to the module's in-memory load address.          (`loadaddr = *(uintptr_t *)((byte_t *)curr + lld_module_offsetof_loadaddr)') */
	__ptrdiff_t    lld_module_offsetof_loadstart; /* Offset to the module's in-memory start mapping address. (`loadstart = *(uintptr_t *)((byte_t *)curr + lld_module_offsetof_loadstart)') */
	__ptrdiff_t    lld_entry_offsetof_next;       /* Offset-of-pointer-to / stride to the next
	                                               * When `LIBRARY_LISTDEF_FLINKLST' is set:    `next = *(MODULE **)((byte_t *)prev + lld_entry_offsetof_next)'
	                                               * When `LIBRARY_LISTDEF_FLINKLST' isn't set: `next = (MODULE *)((byte_t *)prev + lld_entry_offsetof_next)' */
	__ptrdiff_t    lld_entry_offsetof_module;     /* [valid_if(LIBRARY_LISTDEF_FPELEMENT)] Offset to the actual module structure (from individual elements) */
};
#endif /* __CC__ */


__SYSDECL_END

#endif /* !_KOS_EXEC_BITS_LIBRARY_LISTDEF_H */
