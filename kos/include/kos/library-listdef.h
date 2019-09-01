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
#ifndef _KOS_LIBRARY_LISTDEF_H
#define _KOS_LIBRARY_LISTDEF_H 1

/* Helper functions for telling the KOS kernel how to inspect/detect
 * source loaded into user-space, thus allowing the kernel gdb-stub driver to
 * properly enumerate these modules, as well as tell the GDB remote about them. */

#include <__stdinc.h>
#include <__crt.h>
#include <bits/types.h>

__SYSDECL_BEGIN

/* Module enumeration variants:
 *
 * Linked list + pointer-to-module
 * >> struct module {
 * >>      char  *m_filename;
 * >>      void  *m_loadaddr;
 * >>      void  *m_loadstart;
 * >> };
 * >> struct module_entry {
 * >>      struct module_entry *me_next;
 * >>      struct module       *me_module;
 * >> };
 * >> struct module_entry *module_list;
 * >>
 * >> struct library_listdef listdef = {
 * >>      ...
 * >>      .lld_flags                     = LIBRARY_LISTDEF_FPFIRST    // Because `module_list' is set as a pointer
 * >>                                     | LIBRARY_LISTDEF_FLINKLST   // Because we're using a linked list
 * >>                                     | LIBRARY_LISTDEF_FPELEMENT, // Because `module_entry' has a pointer to `module'
 * >>      .lld_first                     = &module_list,
 * >>      .lld_count                     = NULL,                         // No count field
 * >>      .lld_module_offsetof_filename  = offsetof(struct module, m_filename),
 * >>      .lld_module_offsetof_loadaddr  = offsetof(struct module, m_loadaddr),
 * >>      .lld_module_offsetof_loadstart = offsetof(struct module, m_loadstart),
 * >>      .lld_entry_offsetof_next       = offsetof(struct module_entry, me_next),
 * >>      .lld_entry_offsetof_module     = offsetof(struct module_entry, me_module),
 * >> };
 *
 * Linked list + immediate module
 * >> struct module {
 * >>      char          *m_filename;
 * >>      void          *m_loadaddr;
 * >>      void          *m_loadstart;
 * >>      struct module *m_next;
 * >> };
 * >> struct module *module_list;
 * >>
 * >> struct library_listdef listdef = {
 * >>      ...
 * >>      .lld_flags                     = LIBRARY_LISTDEF_FPFIRST   // Because `module_list' is set as a pointer
 * >>                                     | LIBRARY_LISTDEF_FLINKLST, // Because we're using a linked list
 * >>      .lld_first                     = &module_list,
 * >>      .lld_count                     = NULL,                         // No count field
 * >>      .lld_module_offsetof_filename  = offsetof(struct module, m_filename),
 * >>      .lld_module_offsetof_loadaddr  = offsetof(struct module, m_loadaddr),
 * >>      .lld_module_offsetof_loadstart = offsetof(struct module, m_loadstart),
 * >>      .lld_entry_offsetof_next       = offsetof(struct module, m_next),
 * >>      .lld_entry_offsetof_module     = 0, // Unused
 * >> };
 *
 * Vector + pointer-to-module
 * >> struct module {
 * >>      char  *m_filename;
 * >>      void  *m_loadaddr;
 * >>      void  *m_loadstart;
 * >> };
 * >> struct module **module_list;   // List of module pointer
 * >> size_t          module_count;
 * >>
 * >> struct library_listdef listdef = {
 * >>      ...
 * >>      .lld_flags                     = LIBRARY_LISTDEF_FPFIRST    // Because `module_list' is set as a pointer
 * >>                                     | LIBRARY_LISTDEF_FPELEMENT, // Because `module_list' is filled with pointer-to-modules
 * >>      .lld_first                     = &module_list,
 * >>      .lld_count                     = &module_count,
 * >>      .lld_module_offsetof_filename  = offsetof(struct module, m_filename),
 * >>      .lld_module_offsetof_loadaddr  = offsetof(struct module, m_loadaddr),
 * >>      .lld_module_offsetof_loadstart = offsetof(struct module, m_loadstart),
 * >>      .lld_entry_offsetof_next       = sizeof(struct module *),       // Element stride within the `module_list' vector
 * >>      .lld_entry_offsetof_module     = 0, // Might be non-zero if we had `struct module_vector_entry *module_list', where it would be `offsetof(struct module_vector_entry, mve_module)'
 * >> };
 *
 * Other data layouts are also possible, but I hope this documentation
 * is sufficient to help you understand what each flag does when it comes
 * to the actual enumeration of library lists.
 */


#define LIBRARY_LISTDEF_FNORMAL      0x0000 /* Normal library list flags. */
#define LIBRARY_LISTDEF_FPFIRST      0x0001 /* `gll_first' should be loaded with an additional level of indirection. */
#define LIBRARY_LISTDEF_FLINKLST     0x0002 /* `lld_entry_offsetof_next' is the offset to a pointer-to-next-loaded-modules. */
#define LIBRARY_LISTDEF_FINLNAME     0x0004 /* `lld_module_offsetof_filename' is the offset of an inlined c-string. */
#define LIBRARY_LISTDEF_FPELEMENT    0x0008 /* Given some module element (either an entry in a vector, or linked list)
                                             * `lld_entry_offsetof_module' is the offset to a pointer to the actual module structure. */
#define LIBRARY_LISTDEF_FRELFILENAME 0x4000 /* The filename of the library may be a relative pathname to the current PWD. */
#define LIBRARY_LISTDEF_FSINGLE      0x8000 /* Ignore `lld_offsetof_next' entirely. - Only a single library exists
                                             * When set, `lld_offsetof_loadaddr' and `lld_offsetof_loadstart' aren't
                                             * offsets, but the actual load addresses themself! */

#ifdef __CC__
struct library_listdef {
	__size_t       lld_size;                      /* [== sizeof(struct gdb_library_listdef)] Used for versioning */
	__size_t       lld_sizeof_pointer;            /* [== sizeof(void *)] Used for versioning and COMPAT32-mode */
	__uintptr_t    lld_flags;                     /* Definition flags (Set of `LIBRARY_LISTDEF_F*') */
	void          *lld_first;                     /* [1..1] User-space pointer to the first module
	                                               * When `LIBRARY_LISTDEF_FPFIRST' isn't set: `first = (MODULE *)gll_first'
	                                               * When `LIBRARY_LISTDEF_FPFIRST' is set:    `first = *(MODULE **)gll_first' */
	__size_t      *lld_count;                     /* [0..1] Optional: Number of loaded modules.
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

#endif /* !_KOS_LIBRARY_LISTDEF_H */
