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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_LIBRARY_C
#define GUARD_KERNEL_SRC_MEMORY_VM_LIBRARY_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/printk.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <kernel/vm.h>
#include <kernel/vm/library.h>

#include <hybrid/atomic.h>

#include <kos/library-listdef.h>

#include <errno.h>
#include <signal.h>
#include <string.h>

#define POINTER_SET_BUFSIZE 16
#include <misc/pointer-set.h>


DECL_BEGIN

/* Library listing information, as set by user-space.
 * When unavailable, `lld_size' is set to ZERO(0). */
PUBLIC ATTR_PERVM struct library_listdef thisvm_library_listdef = { 0 };


typedef struct anonymous_module_struct MODULE;
typedef struct anonymous_module_entry_struct MODULE_ENTRY;


LOCAL void KCALL getuser(struct vm *__restrict effective_vm,
                         KERNEL void *__restrict dst,
                         USER void const *src, size_t num_bytes) {
	validate_readable(src, num_bytes);
	vm_read(effective_vm, src, dst, num_bytes, false);
}


/* Using information set through `set_library_listdef(2)', try to enumerate
 * libraries that have been loaded by user-space into the given `effective_vm'.
 * Note that information enumerated by this cannot be trusted in any serious context.
 * Nor can it be guarantied that this enumeration will not result in a SEGFAULT being
 * thrown. - Information enumerated is entirely under the control of user-space, with
 * the kernel having absolutely no control of what's going on. - So care must be taken
 * to _always_ handle the E_SEGFAULT which may be thrown by this function!
 * NOTE: This function does however take care to prevent:
 *   - Infinite loops resulting from user-space creating a
 *     linked list pointing back to one of its previous nodes.
 *   - Kernel-space pointers appearing somewhere where a pointer needs to be dereferenced.
 *     Note however that the loadaddr/loadstart argument are not validated at all!
 * @throws: E_BADALLOC: To prevent loops in the event of a linked list, a pointer set is
 *                      used internally. - However this set may get allocated on the heap...
 * @return: < 0:  Error (First negative return value of `*func')
 * @return: >= 0: Success (sum of all calls to `*func') */
PUBLIC ssize_t KCALL
vm_library_enumerate(struct vm *__restrict effective_vm,
                     vm_library_enumerate_callback_t func,
                     void *arg, size_t maxcount)
		THROWS(E_SEGFAULT, E_BADALLOC) {
	ssize_t temp, result = 0;
	struct library_listdef libdef;
	bool filename_maybe_relative;
	if unlikely(!maxcount)
		goto done;
	memcpy(&libdef, &FORVM(effective_vm, thisvm_library_listdef),
	       sizeof(struct library_listdef));
	if unlikely(!libdef.lld_size)
		goto done;
	if unlikely(libdef.lld_sizeof_pointer != sizeof(void *))
		goto done; /* TODO: Add support for COMPAT32 in x86_64-mode */
	filename_maybe_relative = (libdef.lld_flags & LIBRARY_LISTDEF_FRELFILENAME) != 0;
	if (libdef.lld_flags & LIBRARY_LISTDEF_FSINGLE) {
		USER MODULE *mod;
		USER char *filename;
		mod = (USER MODULE *)libdef.lld_first;
		if (libdef.lld_flags & LIBRARY_LISTDEF_FPFIRST)
			getuser(effective_vm, &mod, mod, sizeof(USER MODULE *));
		if (libdef.lld_flags & LIBRARY_LISTDEF_FPELEMENT) {
			getuser(effective_vm, &mod,
			        (byte_t *)mod + libdef.lld_entry_offsetof_module,
			        sizeof(USER MODULE *));
		}
		filename = (char *)((byte_t *)mod + libdef.lld_module_offsetof_filename);
		if (!(libdef.lld_flags & LIBRARY_LISTDEF_FINLNAME))
			getuser(effective_vm, &filename, filename, sizeof(USER char *));
		validate_readable(filename, 1);
		result = (*func)(arg, effective_vm, filename,
		                 (USER void *)(uintptr_t)libdef.lld_module_offsetof_loadaddr,
		                 (USER void *)(uintptr_t)libdef.lld_module_offsetof_loadstart,
		                 filename_maybe_relative);
	} else if (!(libdef.lld_flags & LIBRARY_LISTDEF_FLINKLST)) {
		/* User-space probides a module vector.
		 * This is declared as:
		 * >> if (LIBRARY_LISTDEF_FPELEMENT) {
		 * >>     MODULE **vector;
		 * >> } else {
		 * >>     MODULE *vector; // `MODULE' has a stride of `lld_entry_offsetof_next'
		 * >> }
		 */
		size_t i, count = maxcount;
		USER byte_t *module_vector;
		if (libdef.lld_count) {
			getuser(effective_vm, &count, libdef.lld_count, sizeof(size_t));
			if (count > maxcount)
				count = maxcount;
		}
		module_vector = (byte_t *)libdef.lld_first;
		if (libdef.lld_flags & LIBRARY_LISTDEF_FPFIRST)
			getuser(effective_vm, &module_vector, module_vector, sizeof(byte_t *));
		for (i = 0; i < count; ++i) {
			USER char *filename;
			USER void *loadaddr, *loadstart;
			MODULE *mod;
			mod = (MODULE *)(module_vector + i * libdef.lld_entry_offsetof_next);
			if (libdef.lld_flags & LIBRARY_LISTDEF_FPELEMENT) {
				getuser(effective_vm, &mod,
				        (byte_t *)mod + libdef.lld_entry_offsetof_module,
				        sizeof(MODULE *));
			}

			/* Figure out the filename of the module */
			filename = (char *)((byte_t *)mod + libdef.lld_module_offsetof_filename);
			if (!(libdef.lld_flags & LIBRARY_LISTDEF_FINLNAME))
				getuser(effective_vm, &filename, filename, sizeof(USER char *));
			validate_readable(filename, 1);
			getuser(effective_vm, &loadaddr, (byte_t *)mod + libdef.lld_module_offsetof_loadaddr, sizeof(void *));
			getuser(effective_vm, &loadstart, (byte_t *)mod + libdef.lld_module_offsetof_loadstart, sizeof(void *));
			temp = (*func)(arg, effective_vm, filename, loadaddr,
			               loadstart, filename_maybe_relative);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}

	} else {
		struct pointer_set enumerated_modules;
		pointer_set_init(&enumerated_modules);
		TRY {
			MODULE_ENTRY *modent;
			modent = (MODULE_ENTRY *)libdef.lld_first;
			if (libdef.lld_flags & LIBRARY_LISTDEF_FPFIRST)
				getuser(effective_vm, &modent, modent, sizeof(MODULE_ENTRY *));
			while (modent && maxcount) {
				USER char *filename;
				USER void *loadaddr, *loadstart;
				MODULE *mod;
				/* Keep a set of all enumerated modules to prevent duplicates */
				if unlikely(!pointer_set_insert(&enumerated_modules, modent))
					break; /* Linked list loop */
				if (libdef.lld_flags & LIBRARY_LISTDEF_FPELEMENT) {
					getuser(effective_vm, &mod,
					        (byte_t *)modent + libdef.lld_entry_offsetof_module,
					        sizeof(MODULE *));
				} else {
					mod = (MODULE *)modent;
				}

				/* Figure out the filename of the module */
				filename = (char *)((byte_t *)mod + libdef.lld_module_offsetof_filename);
				if (!(libdef.lld_flags & LIBRARY_LISTDEF_FINLNAME))
					getuser(effective_vm, &filename, filename, sizeof(USER char *));
				validate_readable(filename, 1);
				getuser(effective_vm, &loadaddr, (byte_t *)mod + libdef.lld_module_offsetof_loadaddr, sizeof(void *));
				getuser(effective_vm, &loadstart, (byte_t *)mod + libdef.lld_module_offsetof_loadstart, sizeof(void *));
				/* Enumerate this module */
				temp = (*func)(arg, effective_vm, filename, loadaddr,
				               loadstart, filename_maybe_relative);
				if unlikely(temp < 0)
					goto err;
				result += temp;
				getuser(effective_vm, &modent,
				        (byte_t *)modent + libdef.lld_entry_offsetof_next,
				        sizeof(MODULE_ENTRY *));
				--maxcount;
			}
		} EXCEPT {
			pointer_set_fini(&enumerated_modules);
			RETHROW();
		}
		pointer_set_fini(&enumerated_modules);
	}
done:
	return result;
err:
	return temp;
}






DEFINE_SYSCALL1(errno_t, set_library_listdef,
                USER UNCHECKED struct library_listdef const *, listdef) {
	size_t size;
	struct library_listdef *dst;
	validate_readable(listdef, sizeof(*listdef));
	size = ATOMIC_READ(listdef->lld_size);
	if unlikely(size != sizeof(struct library_listdef))
		THROW(E_BUFFER_TOO_SMALL, sizeof(struct library_listdef), size);
	dst = &THIS_LIBRARY_LISTDEF;
	COMPILER_WRITE_BARRIER();
	dst->lld_size = 0; /* Invalidate the previous definition */
	COMPILER_WRITE_BARRIER();
	/* Copy the contents of the new definition */
	memcpy((byte_t *)dst + offsetafter(struct library_listdef, lld_size),
	       (byte_t *)listdef + offsetafter(struct library_listdef, lld_size),
	       (sizeof(struct library_listdef) - offsetafter(struct library_listdef, lld_size)));
	COMPILER_WRITE_BARRIER();
	dst->lld_size = size; /* Mark the new definition as valid. */
	COMPILER_WRITE_BARRIER();
#if 0 /* TODO: Enable me once libdl loads the library list after initialization, and
       *       the inital library list definition loaded by exec() already includes
       *       both libdl _and_ the hosted application. */
	if (kernel_debugtrap_enabled()) {
		struct debugtrap_reason r;
		r.dtr_signo  = SIGTRAP;
		r.dtr_reason = DEBUGTRAP_REASON_LIBRARY;
		kernel_debugtrap(&r);
	}
#endif
	return -EOK;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_LIBRARY_C */
