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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_READWRITE_C
#define GUARD_KERNEL_SRC_MEMORY_VM_READWRITE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/vm.h>

#include <hybrid/align.h>

#include <asm/cacheline.h>

#include <alloca.h>
#include <assert.h>
#include <string.h>

DECL_BEGIN

#ifndef CONFIG_VM_ARCH_DEFINES_MEMSET_NOPF

/* Same as memcpy_nopf(), but implements memset() functionality */
PUBLIC NOBLOCK WUNUSED size_t
NOTHROW(KCALL memset_nopf)(USER CHECKED void *dst,
                           int byte,
                           size_t num_bytes) {
	PRIVATE byte_t src[64];
	if (num_bytes < COMPILER_LENOF(src)) {
		memset(src, byte, num_bytes);
		return memcpy_nopf(dst, src, num_bytes);
	}
	memset(src, byte, sizeof(src));
	while (num_bytes) {
		size_t count, error;
		count = num_bytes > COMPILER_LENOF(src)
		        ? COMPILER_LENOF(src)
		        : num_bytes;
		error = memcpy_nopf(dst, src, count);
		num_bytes -= count;
		if unlikely(error)
			return num_bytes + error;
		dst = (byte_t *)dst + count;
	}
	return 0;
}
#endif /* !CONFIG_VM_ARCH_DEFINES_MEMSET_NOPF */


#ifndef CONFIG_VM_ARCH_DEFINES_MEMEQ_NOPF
/* Compare the data pointed to by 2 potentially faulty memory buffers.
 * @return: >0: The contents of the 2 buffers differ from each other.
 * @return:  0: The contents of the 2 buffers are identical.
 * @return: <0: At least one of the 2 buffers is faulty. */
PUBLIC NOBLOCK WUNUSED ssize_t
NOTHROW(KCALL memeq_nopf)(USER CHECKED void const *lhs,
                          USER CHECKED void const *rhs,
                          size_t num_bytes) {
	byte_t lhs_buffer[__ARCH_CACHELINESIZE];
	byte_t rhs_buffer[__ARCH_CACHELINESIZE];
	while (num_bytes) {
		size_t error, temp;
		temp = num_bytes;
		if (temp > __ARCH_CACHELINESIZE)
			temp = __ARCH_CACHELINESIZE;
		error = memcpy_nopf(lhs_buffer, lhs, temp);
		if unlikely(error)
			return -1; /* Left buffer is faulty. */
		error = memcpy_nopf(rhs_buffer, rhs, temp);
		if unlikely(error)
			return -1; /* Right buffer is faulty. */
		if (memcmp(lhs_buffer, rhs_buffer, temp) != 0)
			return 1;
		num_bytes -= temp;
		lhs = (byte_t *)lhs + temp;
		rhs = (byte_t *)rhs + temp;
	}
	return 0;
}

/* Same as `memeq_nopf()', but the function may assume that only `user_buffer' can be faulty. */
PUBLIC NOBLOCK WUNUSED ssize_t
NOTHROW(KCALL memeq_ku_nopf)(KERNEL void const *kernel_buffer,
                             USER CHECKED void const *user_buffer,
                             size_t num_bytes) {
	byte_t rhs_buffer[__ARCH_CACHELINESIZE];
	while (num_bytes) {
		size_t error, temp;
		temp = num_bytes;
		if (temp > __ARCH_CACHELINESIZE)
			temp = __ARCH_CACHELINESIZE;
		error = memcpy_nopf(rhs_buffer, user_buffer, temp);
		if unlikely(error)
			return -1; /* Right buffer is faulty. */
		if (memcmp(kernel_buffer, rhs_buffer, temp) != 0)
			return 1;
		num_bytes -= temp;
		kernel_buffer = (byte_t *)kernel_buffer + temp;
		user_buffer = (byte_t *)user_buffer + temp;
	}
	return 0;
}
#endif /* !CONFIG_VM_ARCH_DEFINES_MEMEQ_NOPF */



#if defined(__INTELLISENSE__)
#define DEFINE_PAGEDIR_P_BEGIN(pagedir_phys) if (((pagedir_phys), 0)); else do
#define DEFINE_PAGEDIR_P_END                 __WHILE0
#else

#ifdef CONFIG_PAGEDIR_GETSET_USES_POINTER
typedef PHYS pagedir_t *pdir_set_type_t;
#else
typedef PHYS vm_phys_t  pdir_set_type_t;
#endif

#define DEFINE_PAGEDIR_P_BEGIN(pagedir_phys) \
	do {                                                                    \
		pdir_set_type_t _old_pdir;                                          \
		pflag_t _p_was = PREEMPTION_PUSHOFF();                              \
		_old_pdir      = pagedir_get();                                     \
		assert(IS_ALIGNED((uintptr_t)(pagedir_phys), PAGEDIR_ALIGN));       \
		pagedir_set((pdir_set_type_t)(pagedir_phys));                       \
		do
#define DEFINE_PAGEDIR_P_END \
		__WHILE0;                \
		pagedir_set(_old_pdir);  \
		PREEMPTION_POP(_p_was);  \
	} __WHILE0
#endif


LOCAL NOBLOCK size_t
NOTHROW(KCALL copy_kernelspace_from_vm_nopf)(struct vm *__restrict self,
                                             UNCHECKED void const *addr,
                                             KERNEL CHECKED void *buf,
                                             size_t num_bytes) {
	size_t result;
	/* Temporarily switch to the foreign VM */
	/* XXX: What about TLB shootdowns happening while we do this? */
	DEFINE_PAGEDIR_P_BEGIN(self->v_pdir_phys_ptr) {
		result = memcpy_nopf(buf, addr, num_bytes);
	}
	DEFINE_PAGEDIR_P_END;
	return result;
}

LOCAL NOBLOCK size_t
NOTHROW(KCALL copy_kernelspace_into_vm_nopf)(struct vm *__restrict self,
                                             UNCHECKED void *addr,
                                             KERNEL CHECKED void const *buf,
                                             size_t num_bytes) {
	size_t result;
	/* Temporarily switch to the foreign VM */
	/* XXX: What about TLB shootdowns happening while we do this? */
	DEFINE_PAGEDIR_P_BEGIN(self->v_pdir_phys_ptr) {
		result = memcpy_nopf(addr, buf, num_bytes);
	}
	DEFINE_PAGEDIR_P_END;
	return result;
}

LOCAL NOBLOCK size_t
NOTHROW(KCALL memset_into_vm_nopf)(struct vm *__restrict self,
                                   UNCHECKED void *addr,
                                   int byte, size_t num_bytes) {
	size_t result;
	/* Temporarily switch to the foreign VM */
	/* XXX: What about TLB shootdowns happening while we do this? */
	DEFINE_PAGEDIR_P_BEGIN(self->v_pdir_phys_ptr) {
		result = memset_nopf(addr, byte, num_bytes);
	}
	DEFINE_PAGEDIR_P_END;
	return result;
}



/* read/write memory to/form the address space of a given VM
 * Note that these functions behave similar to memcpy_nopf(), in that they
 * will only ever copy _true_ RAM, and never access VIO or cause LOA/COW.
 * @return: 0 : The copy operation completed without any problems.
 * @return: * : The number of bytes that could not be transfered.
 *              The affected memory range is:
 *               - `buf + num_bytes - return ... buf + num_bytes - 1' */
PUBLIC NOBLOCK size_t
NOTHROW(KCALL vm_read_nopf)(struct vm *__restrict self, UNCHECKED void const *addr,
                            USER CHECKED void *buf, size_t num_bytes) {
	size_t result = 0;
	if unlikely((uintptr_t)addr + num_bytes < (uintptr_t)addr) {
		uintptr_t temp = (uintptr_t)addr + num_bytes;
		result    += ((uintptr_t)0 - temp);
		num_bytes -= ((uintptr_t)0 - temp);
	}
	if unlikely((uintptr_t)buf + num_bytes < (uintptr_t)buf) {
		uintptr_t temp = (uintptr_t)buf + num_bytes;
		result    += ((uintptr_t)0 - temp);
		num_bytes -= ((uintptr_t)0 - temp);
	}
	if (ADDRRANGE_ISKERN((uintptr_t)addr, (uintptr_t)addr + num_bytes)) {
		/* Simple case: read from kernel memory (can just be copied directly). */
direct_copy:
		result += memcpy_nopf(buf, addr, num_bytes);
	} else {
		if (THIS_VM == self)
			goto direct_copy; /* Simple case: same VM */
		if (ADDRRANGE_ISKERN((uintptr_t)buf, (uintptr_t)buf + num_bytes)) {
			/* Target buffer is located in kernel-space.
			 * For this case, we can simply switch to the other VM and directly copy data. */
			result += copy_kernelspace_from_vm_nopf(self, addr, buf, num_bytes);
		} else {
			/* The most difficult case: copy from one userspace buffer into another. */
			byte_t *buffer; size_t bufsize;
			if unlikely(!num_bytes)
				goto done;
			bufsize = get_stack_avail() / 2;
			if (bufsize > 1024)
				bufsize -= 1024;
			if (bufsize > num_bytes)
				bufsize = num_bytes;
			assert(bufsize != 0);
			buffer = (byte_t *)alloca(bufsize);
			for (;;) {
				size_t transfer_size, error;
				transfer_size = bufsize;
				if (transfer_size > num_bytes)
					transfer_size = num_bytes;
				error = copy_kernelspace_from_vm_nopf(self,
				                                      addr,
				                                      buffer,
				                                      transfer_size);
				if unlikely(error) {
handle_transfer_error:
					result += error;
					result += num_bytes;
					result -= transfer_size;
					goto done;
				}
				error = memcpy_nopf(buf, buffer, transfer_size);
				if unlikely(error)
					goto handle_transfer_error;
				if (transfer_size >= num_bytes)
					break;
				buf      = (byte_t *)buf + transfer_size;
				addr = (byte_t *)addr + transfer_size;
				num_bytes -= transfer_size;
			}
		}
	}
done:
	return result;
}

PUBLIC NOBLOCK size_t
NOTHROW(KCALL vm_write_nopf)(struct vm *__restrict self, UNCHECKED void *addr,
                             USER CHECKED void const *buf, size_t num_bytes) {
	size_t result = 0;
	if unlikely((uintptr_t)addr + num_bytes < (uintptr_t)addr) {
		uintptr_t temp = (uintptr_t)addr + num_bytes;
		result    += ((uintptr_t)0 - temp);
		num_bytes -= ((uintptr_t)0 - temp);
	}
	if unlikely((uintptr_t)buf + num_bytes < (uintptr_t)buf) {
		uintptr_t temp = (uintptr_t)buf + num_bytes;
		result    += ((uintptr_t)0 - temp);
		num_bytes -= ((uintptr_t)0 - temp);
	}
	if (ADDRRANGE_ISKERN((uintptr_t)addr, (uintptr_t)addr + num_bytes)) {
		/* Simple case: write to kernel memory (can just be copied directly). */
direct_copy:
		result += memcpy_nopf(addr, buf, num_bytes);
	} else {
		if (THIS_VM == self)
			goto direct_copy; /* Simple case: same VM */
		if (ADDRRANGE_ISKERN((uintptr_t)buf, (uintptr_t)buf + num_bytes)) {
			/* Source buffer is located in kernel-space.
			 * For this case, we can simply switch to the other VM and directly copy data. */
			result += copy_kernelspace_into_vm_nopf(self, addr,
			                                        buf, num_bytes);
		} else {
			/* The most difficult case: copy from one userspace buffer into another. */
			byte_t *buffer; size_t bufsize;
			if unlikely(!num_bytes)
				goto done;
			bufsize = get_stack_avail() / 2;
			if (bufsize > 1024)
				bufsize -= 1024;
			if (bufsize > num_bytes)
				bufsize = num_bytes;
			assert(bufsize != 0);
			buffer = (byte_t *)alloca(bufsize);
			for (;;) {
				size_t transfer_size, error;
				transfer_size = bufsize;
				if (transfer_size > num_bytes)
					transfer_size = num_bytes;
				error = memcpy_nopf(buffer, buf, transfer_size);
				if unlikely(error) {
handle_transfer_error:
					result += error;
					result += num_bytes;
					result -= transfer_size;
					goto done;
				}
				error = copy_kernelspace_into_vm_nopf(self, addr,
				                                      buffer, transfer_size);
				if unlikely(error)
					goto handle_transfer_error;
				if (transfer_size >= num_bytes)
					break;
				buf      = (byte_t *)buf + transfer_size;
				addr = (byte_t *)addr + transfer_size;
				num_bytes -= transfer_size;
			}
		}
	}
done:
	return result;
}

PUBLIC NOBLOCK size_t
NOTHROW(KCALL vm_memset_nopf)(struct vm *__restrict self, UNCHECKED void *addr,
                              int byte, size_t num_bytes) {
	size_t result = 0;
	if unlikely((uintptr_t)addr + num_bytes < (uintptr_t)addr) {
		uintptr_t temp = (uintptr_t)addr + num_bytes;
		result    += ((uintptr_t)0 - temp);
		num_bytes -= ((uintptr_t)0 - temp);
	}
	if (ADDRRANGE_ISKERN((uintptr_t)addr, (uintptr_t)addr + num_bytes)) {
		/* Simple case: write to kernel memory (can just be copied directly). */
direct_copy:
		result += memset_nopf(addr, byte, num_bytes);
	} else {
		if (THIS_VM == self)
			goto direct_copy; /* Simple case: same VM */
		result += memset_into_vm_nopf(self, addr, byte, num_bytes);
	}
	return result;
}


#ifndef __INTELLISENSE__
DECL_END

#define COPY_KERNEL2USER 1
#include "readwrite-proto-impl.c.inl"
#define COPY_USER2KERNEL 1
#include "readwrite-proto-impl.c.inl"
#define VM_MEMSET_IMPL 1
#include "readwrite-proto-impl.c.inl"

DECL_BEGIN
#else

LOCAL void KCALL
copy_kernelspace_from_vm(struct vm *__restrict effective_vm,
                         UNCHECKED void const *addr, KERNEL CHECKED void *buf,
                         size_t num_bytes, bool force_accessible)
		THROWS(E_SEGFAULT, E_WOULDBLOCK);
LOCAL void KCALL
copy_kernelspace_into_vm(struct vm *__restrict effective_vm,
                         UNCHECKED void *addr, KERNEL CHECKED void const *buf,
                         size_t num_bytes, bool force_accessible)
		THROWS(E_SEGFAULT, E_WOULDBLOCK);
LOCAL void KCALL
memset_into_vm(struct vm *__restrict effective_vm,
               UNCHECKED void *addr, int byte,
               size_t num_bytes, bool force_accessible)
		THROWS(E_SEGFAULT, E_WOULDBLOCK);

#endif

/* High-level read/write memory to/from the given `src_vm'.
 * These functions do all the things necessary to read/write memory
 * the same way a regular memory access would, including LOA/COW, as
 * well as properly accessing VIO. */
PUBLIC void KCALL
vm_read(struct vm *__restrict self,
        UNCHECKED void const *addr, USER CHECKED void *buf,
        size_t num_bytes, bool force_readable_source)
		THROWS(E_SEGFAULT, E_WOULDBLOCK) {
	if unlikely((uintptr_t)addr + num_bytes < (uintptr_t)addr)
		THROW(E_SEGFAULT_UNMAPPED, (void *)-1, E_SEGFAULT_CONTEXT_FAULT | E_SEGFAULT_CONTEXT_NONCANON);
	if unlikely((uintptr_t)buf + num_bytes < (uintptr_t)buf)
		THROW(E_SEGFAULT_UNMAPPED, (void *)-1, E_SEGFAULT_CONTEXT_FAULT | E_SEGFAULT_CONTEXT_WRITING | E_SEGFAULT_CONTEXT_NONCANON);
	if (ADDRRANGE_ISKERN((uintptr_t)addr, (uintptr_t)addr + num_bytes)) {
		/* Simple case: read from kernel memory (can just be copied directly). */
		TRY {
			memcpy(buf, addr, num_bytes);
		} EXCEPT {
			if (!force_readable_source || !was_thrown(E_SEGFAULT_NOTREADABLE))
				RETHROW();
			self = &vm_kernel;
			goto copy_from_vm;
		}
	} else {
		if (THIS_VM == self) {
			/* Simple case: same VM */
			TRY {
				memcpy(buf, addr, num_bytes);
			} EXCEPT {
				if (!force_readable_source || !was_thrown(E_SEGFAULT_NOTREADABLE))
					RETHROW();
				goto copy_from_vm;
			}
			return;
		}
copy_from_vm:
		if (ADDRRANGE_ISKERN((uintptr_t)buf, (uintptr_t)buf + num_bytes)) {
			/* Target buffer is located in kernel-space.
			 * For this case, we can simply switch to the other VM and directly copy data. */
			copy_kernelspace_from_vm(self,
			                         addr,
			                         buf,
			                         num_bytes,
			                         force_readable_source);
		} else {
			/* The most difficult case: copy from one userspace buffer into another. */
			byte_t *buffer; size_t bufsize;
			if unlikely(!num_bytes)
				return;
			bufsize = get_stack_avail() / 2;
			if (bufsize > 1024)
				bufsize -= 1024;
			if (bufsize > num_bytes)
				bufsize = num_bytes;
			assert(bufsize != 0);
			buffer = (byte_t *)alloca(bufsize);
			for (;;) {
				size_t transfer_size;
				transfer_size = bufsize;
				if (transfer_size > num_bytes)
					transfer_size = num_bytes;
				copy_kernelspace_from_vm(self,
				                         addr,
				                         buffer,
				                         transfer_size,
				                         force_readable_source);
				memcpy(buf, buffer, transfer_size);
				if (transfer_size >= num_bytes)
					break;
				buf      = (byte_t *)buf + transfer_size;
				addr = (byte_t *)addr + transfer_size;
				num_bytes -= transfer_size;
			}
		}
	}
}


PUBLIC void KCALL
vm_write(struct vm *__restrict self,
         UNCHECKED void *addr, USER CHECKED void const *buf,
         size_t num_bytes, bool force_writable_destination)
		THROWS(E_SEGFAULT, E_WOULDBLOCK) {
	if unlikely((uintptr_t)addr + num_bytes < (uintptr_t)addr)
		THROW(E_SEGFAULT_UNMAPPED, (void *)-1, E_SEGFAULT_CONTEXT_FAULT | E_SEGFAULT_CONTEXT_WRITING | E_SEGFAULT_CONTEXT_NONCANON);
	if unlikely((uintptr_t)buf + num_bytes < (uintptr_t)buf)
		THROW(E_SEGFAULT_UNMAPPED, (void *)-1, E_SEGFAULT_CONTEXT_FAULT | E_SEGFAULT_CONTEXT_NONCANON);
	if (ADDRRANGE_ISKERN((uintptr_t)addr, (uintptr_t)addr + num_bytes)) {
		/* Simple case: write to kernel memory (can just be copied directly). */
		TRY {
			memcpy(addr, buf, num_bytes);
		} EXCEPT {
			if (!force_writable_destination || !was_thrown(E_SEGFAULT_READONLY))
				RETHROW();
			self = &vm_kernel;
			goto copy_to_vm;
		}
	} else {
		if (THIS_VM == self) {
			/* Simple case: same VM */
			TRY {
				memcpy(addr, buf, num_bytes);
			} EXCEPT {
				if (!force_writable_destination || !was_thrown(E_SEGFAULT_READONLY))
					RETHROW();
				goto copy_to_vm;
			}
			return;
		}
copy_to_vm:
		if (ADDRRANGE_ISKERN((uintptr_t)buf, (uintptr_t)buf + num_bytes)) {
			/* Source buffer is located in kernel-space.
			 * For this case, we can simply switch to the other VM and directly copy data. */
			copy_kernelspace_into_vm(self, addr,
			                         buf, num_bytes,
			                         force_writable_destination);
		} else {
			/* The most difficult case: copy from one userspace buffer into another. */
			byte_t *buffer; size_t bufsize;
			if unlikely(!num_bytes)
				return;
			bufsize = get_stack_avail() / 2;
			if (bufsize > 1024)
				bufsize -= 1024;
			if (bufsize > num_bytes)
				bufsize = num_bytes;
			assert(bufsize != 0);
			buffer = (byte_t *)alloca(bufsize);
			for (;;) {
				size_t transfer_size;
				transfer_size = bufsize;
				if (transfer_size > num_bytes)
					transfer_size = num_bytes;
				memcpy(buffer, buf, transfer_size);
				copy_kernelspace_into_vm(self, addr,
				                         buffer, transfer_size,
				                         force_writable_destination);
				if (transfer_size >= num_bytes)
					break;
				buf      = (byte_t *)buf + transfer_size;
				addr = (byte_t *)addr + transfer_size;
				num_bytes -= transfer_size;
			}
		}
	}
}


/* Same as `vm_write()', but implement memset() semantics instead. */
PUBLIC void KCALL
vm_memset(struct vm *__restrict self,
          UNCHECKED void *addr, int byte, size_t num_bytes,
          bool force_writable_destination)
		THROWS(E_SEGFAULT, E_WOULDBLOCK) {
	if unlikely((uintptr_t)addr + num_bytes < (uintptr_t)addr)
		THROW(E_SEGFAULT_UNMAPPED, (void *)-1, E_SEGFAULT_CONTEXT_FAULT | E_SEGFAULT_CONTEXT_WRITING | E_SEGFAULT_CONTEXT_NONCANON);
	if (ADDRRANGE_ISKERN((uintptr_t)addr, (uintptr_t)addr + num_bytes)) {
		/* Simple case: write to kernel memory (can just be copied directly). */
		TRY {
			memset(addr, byte, num_bytes);
		} EXCEPT {
			if (!force_writable_destination || !was_thrown(E_SEGFAULT_READONLY))
				RETHROW();
			self = &vm_kernel;
			goto copy_to_vm;
		}
	} else {
		if (THIS_VM == self) {
			/* Simple case: same VM */
			TRY {
				memset(addr, byte, num_bytes);
			} EXCEPT {
				if (!force_writable_destination || !was_thrown(E_SEGFAULT_READONLY))
					RETHROW();
				goto copy_to_vm;
			}
			return;
		}
copy_to_vm:
		memset_into_vm(self, addr,
		               byte, num_bytes,
		               force_writable_destination);
	}
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_READWRITE_C */
