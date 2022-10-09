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
#ifndef GUARD_KERNEL_SRC_SCHED_RPC_PROGRAM_C
#define GUARD_KERNEL_SRC_SCHED_RPC_PROGRAM_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/fpu.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/fault.h>
#include <kernel/mman/mpartmeta.h>
#include <kernel/mman/rw.h>
#include <kernel/rt/except-handler.h>
#include <kernel/rt/except-syscall.h> /* CONFIG_HAVE_KERNEL_USERPROCMASK */
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/sig.h>
#include <sched/sigmask.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/host.h>
#include <hybrid/overflow.h>
#include <hybrid/sequence/bsearch.h>
#include <hybrid/unaligned.h>

#include <asm/signed-shift.h>
#include <compat/config.h>
#include <kos/except/reason/illop.h>
#include <kos/except/reason/inval.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state-verify.h>
#include <kos/kernel/cpu-state.h>
#include <kos/nopf.h>
#include <kos/rpc.h>
#include <sys/param.h>

#include <alloca.h>
#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <signal.h>
#include <stdalign.h>
#include <stddef.h>
#include <string.h>

#include <libunwind/arch-register.h>
#include <libunwind/cfi.h> /* unwind_getreg_t, unwind_setreg_t */

#if defined(__i386__) || defined(__x86_64__)
#include <sched/x86/eflags-mask.h>
#endif /* __i386__ || __x86_64__ */

#if defined(__i386__) && !defined(__x86_64__)
#include <kernel/x86/gdt.h> /* x86_set_user_fsbase(), x86_set_user_gsbase() */
#endif /* __i386__ && !__x86_64__ */

#ifdef __arm__
#include <kernel/arm/tls.h> /* x86_set_user_fsbase(), x86_set_user_gsbase() */
#endif /* __arm__ */

#ifdef CONFIG_HAVE_FPU
#include <kos/kernel/fpu-state.h>
#endif /* CONFIG_HAVE_FPU */

#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/bits/syscall-info.h>
#include <compat/kos/types.h>
#endif /* __ARCH_HAVE_COMPAT */

#undef RPC_TRACE_INSTRUCTIONS
#if 0
#define RPC_TRACE_INSTRUCTIONS
#endif

#ifdef RPC_TRACE_INSTRUCTIONS
#include <kernel/printk.h>
#endif /* RPC_TRACE_INSTRUCTIONS */

DECL_BEGIN

#ifndef SIZEOF_POINTER
#define SIZEOF_POINTER __SIZEOF_POINTER__
#endif /* !SIZEOF_POINTER */

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */


/* Destroy a "!RPC_CONTEXT_KERN && !RPC_CONTEXT_SIGNAL"-rpc once `self->pr_user.pur_refcnt == 0' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _pending_rpc_destroy_user)(struct pending_rpc *__restrict self) {
	sig_broadcast_for_fini(&self->pr_user.pur_stchng);
	decref(self->pr_user.pur_mman);
	assert(!(self->pr_flags & _RPC_CONTEXT_DONTFREE));
	pending_rpc_free(self);
}

/* Mark  the given `rpc' as canceled. This function is guarantied to
 * not be called at the same time as `task_userrpc_runprogram()', as
 * it is only used to  implement handling for `!RPC_CONTEXT_KERN  &&
 * !RPC_CONTEXT_SIGNAL' RPCs left-over during thread/process exit. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_userrpc_cancelprogram)(struct pending_rpc *__restrict rpc) {
	assert(!(rpc->pr_flags & RPC_CONTEXT_KERN));
	assert(!(rpc->pr_flags & RPC_CONTEXT_SIGNAL));

	/* Indicate that the program was canceled. */
	ATOMIC_WRITE(rpc->pr_user.pur_status, PENDING_USER_RPC_STATUS_CANCELED);
	sig_broadcast(&rpc->pr_user.pur_stchng);
}

/* 2 neighboring RPC mem-banks are joined when <= this # of unbound bytes are located in-between. */
#define RPC_MEMBANK_JOIN_THRESHOLD 64
#if RPC_MEMBANK_JOIN_THRESHOLD > PAGESIZE
#undef RPC_MEMBANK_JOIN_THRESHOLD
#define RPC_MEMBANK_JOIN_THRESHOLD PAGESIZE
#endif /* RPC_MEMBANK_JOIN_THRESHOLD > PAGESIZE */

/* # of bytes by which to over-cache memory bank extensions.
 * Larger values mean more wasted memory; lower values  mean
 * that memory banks need to be resized more often. */
#define RPC_MEMBANK_EXPAND_OVERCACHE 32


struct rpc_membank {
	USER CHECKED byte_t            *rmb_addrlo;  /* [const] Lowest bank address. (1-byte granularity) */
	USER CHECKED byte_t            *rmb_addrhi;  /* [const] Greatest bank address. */
	size_t                          rmb_datoff;  /* [const] Offset of mem-bank data. */
	COMPILER_FLEXIBLE_ARRAY(byte_t, rmb_status); /* Bitset of bytes that were modified. */
};
#define RPC_MEMBANK_STATUS_BITS      2 /* # of status bits per byte */
#define _RPC_MEMBANK_STATUS_MASK     ((1 << RPC_MEMBANK_STATUS_BITS) - 1)
#define RPC_MEMBANK_STATUS_UNDEF     0 /* Default: contents of this byte are undefined */
#define RPC_MEMBANK_STATUS_F_LOADED  1 /* FLAG: Byte was loaded. */
#define RPC_MEMBANK_STATUS_F_CHANGED 2 /* FLAG: Byte got changed. */

#define _rpc_membank_changed_indx(bankrel_addr) ((bankrel_addr) / (NBBY / RPC_MEMBANK_STATUS_BITS))
#define _rpc_membank_changed_shft(bankrel_addr) (((bankrel_addr) % (NBBY / RPC_MEMBANK_STATUS_BITS)) * RPC_MEMBANK_STATUS_BITS)
#define rpc_membank_size(self)                  (size_t)(((self)->rmb_addrhi - (self)->rmb_addrlo) + 1)
#define rpc_membank_data(self)                  ((byte_t *)(self) + (self)->rmb_datoff)
#define rpc_membank_waschanged(self, bankrel_addr) (rpc_membank_getstatus(self, bankrel_addr) & RPC_MEMBANK_STATUS_F_CHANGED)
#define rpc_membank_getstatus(self, bankrel_addr)                    \
	(((self)->rmb_status[_rpc_membank_changed_indx(bankrel_addr)] >> \
	  _rpc_membank_changed_shft(bankrel_addr)) &                     \
	 _RPC_MEMBANK_STATUS_MASK)
#define rpc_membank_setstatus(self, bankrel_addr, v)                             \
	((self)->rmb_status[_rpc_membank_changed_indx(bankrel_addr)] =               \
	 (((self)->rmb_status[_rpc_membank_changed_indx(bankrel_addr)] &             \
	   ~(_RPC_MEMBANK_STATUS_MASK << _rpc_membank_changed_shft(bankrel_addr))) | \
	  (v) << _rpc_membank_changed_shft(bankrel_addr)))

PRIVATE ATTR_RETNONNULL WUNUSED struct rpc_membank *FCALL
rpc_membank_create(USER CHECKED byte_t *addr, size_t num_bytes)
		THROWS(E_BADALLOC) {
	struct rpc_membank *result;
	size_t struct_size, data_offset, bitset_size;
	static_assert(RPC_MEMBANK_STATUS_UNDEF == 0);
	data_offset = offsetof(struct rpc_membank, rmb_status);
	bitset_size = CEILDIV(num_bytes, NBBY / RPC_MEMBANK_STATUS_BITS);
	data_offset += bitset_size;
	struct_size = data_offset + num_bytes;
	result = (struct rpc_membank *)kmalloc(struct_size, GFP_NORMAL);
	result->rmb_datoff = data_offset;
	result->rmb_addrlo = addr;
	result->rmb_addrhi = addr + num_bytes - 1;
	bzero(result->rmb_status, bitset_size);
	return result;
}

PRIVATE ATTR_RETNONNULL WUNUSED struct rpc_membank *FCALL
rpc_membank_insert_back(struct rpc_membank *__restrict self, size_t more_bytes)
		THROWS(E_BADALLOC) {
	struct rpc_membank *result;
	size_t i, old_byte_count, new_byte_count;
	size_t new_struct_size, new_data_offset;
	old_byte_count  = rpc_membank_size(self);
	new_byte_count  = old_byte_count + more_bytes;
	new_data_offset = offsetof(struct rpc_membank, rmb_status);
	new_data_offset += CEILDIV(new_byte_count, NBBY / RPC_MEMBANK_STATUS_BITS);
	new_struct_size = new_data_offset + new_byte_count;
	result = (struct rpc_membank *)krealloc(self, new_struct_size, GFP_NORMAL);
	if (result->rmb_datoff != new_data_offset) {
		assert(new_data_offset > result->rmb_datoff);
		memmoveup((byte_t *)result + new_data_offset,
		          (byte_t *)result + result->rmb_datoff,
		          old_byte_count);
		result->rmb_datoff = new_data_offset;
	}
	result->rmb_addrhi += more_bytes;
	DBG_memset((byte_t *)result + new_data_offset, 0xcc, more_bytes);
	for (i = 0; i < more_bytes; ++i) {
		size_t reladdr = old_byte_count + i;
		rpc_membank_setstatus(result, reladdr, RPC_MEMBANK_STATUS_UNDEF);
	}
	return result;
}

PRIVATE ATTR_RETNONNULL WUNUSED struct rpc_membank *FCALL
rpc_membank_insert_front(struct rpc_membank *__restrict self, size_t more_bytes)
		THROWS(E_BADALLOC) {
	struct rpc_membank *result;
	size_t i, old_byte_count, new_byte_count;
	size_t new_struct_size, new_data_offset;
	old_byte_count  = rpc_membank_size(self);
	new_byte_count  = more_bytes + old_byte_count;
	new_data_offset = offsetof(struct rpc_membank, rmb_status);
	new_data_offset += CEILDIV(new_byte_count, NBBY / RPC_MEMBANK_STATUS_BITS);
	new_struct_size = new_data_offset + new_byte_count;
	result = (struct rpc_membank *)krealloc(self, new_struct_size, GFP_NORMAL);
	memmoveup((byte_t *)result + new_data_offset + more_bytes,
	          (byte_t *)result + result->rmb_datoff,
	          old_byte_count);
	DBG_memset((byte_t *)result + new_data_offset, 0xcc, more_bytes);
	result->rmb_addrlo -= more_bytes;
	result->rmb_datoff = new_data_offset;
	/* Important: move bits in reverse because we move then upwards. */
	for (i = old_byte_count; i--;) {
		size_t new_reladdr = i + more_bytes;
		int status = rpc_membank_getstatus(result, i);
		rpc_membank_setstatus(result, new_reladdr, status);
	}
	for (i = 0; i < more_bytes; ++i)
		rpc_membank_setstatus(result, i, RPC_MEMBANK_STATUS_UNDEF);
	return result;
}

PRIVATE ATTR_RETNONNULL WUNUSED struct rpc_membank *FCALL
rpc_membank_join(struct rpc_membank *__restrict lo,
                 struct rpc_membank *__restrict hi)
		THROWS(E_BADALLOC) {
	struct rpc_membank *result;
	size_t i, old_byte_count, new_byte_count;
	size_t new_struct_size, new_data_offset;
	size_t more_bytes;
	assert(lo->rmb_addrhi + 1 == hi->rmb_addrlo);
	more_bytes      = rpc_membank_size(hi);
	old_byte_count  = rpc_membank_size(lo);
	new_byte_count  = old_byte_count + more_bytes;
	new_data_offset = offsetof(struct rpc_membank, rmb_status);
	new_data_offset += CEILDIV(new_byte_count, NBBY / RPC_MEMBANK_STATUS_BITS);
	new_struct_size = new_data_offset + new_byte_count;
	result = (struct rpc_membank *)krealloc(lo, new_struct_size, GFP_NORMAL);
	if (result->rmb_datoff != new_data_offset) {
		assert(new_data_offset > result->rmb_datoff);
		memmoveup((byte_t *)result + new_data_offset,
		          (byte_t *)result + result->rmb_datoff,
		          old_byte_count);
		result->rmb_datoff = new_data_offset;
	}
	result->rmb_addrhi = hi->rmb_addrhi;
	memcpy((byte_t *)result + new_data_offset, rpc_membank_data(hi), more_bytes);
	/* TODO: Use `bitcpy' */
	for (i = 0; i < more_bytes; ++i) {
		int st         = rpc_membank_getstatus(hi, i);
		size_t reladdr = old_byte_count + i;
		rpc_membank_setstatus(result, reladdr, st);
	}
	kfree(hi);
	return result;
}


struct rpc_futex {
	USER CHECKED void *rf_addr; /* [const] Futex address. */
	size_t             rf_wake; /* # of threads that should be woken. */
};


struct rpc_mem {
	size_t               rm_bankc;  /* # of memory banks. */
	struct rpc_membank **rm_bankv;  /* [1..1][owned][0..rm_bankc][owned] Vector of memory banks (sorted ascendingly by `rmb_addrlo') */
	size_t               rm_access; /* Total # of bytes ever accessed. */
	size_t               rm_futxc;  /* Total # of bytes ever accessed. */
	struct rpc_futex    *rm_futxv;  /* Total # of bytes ever accessed. */
};

#define rpc_mem_init(self)     \
	((self)->rm_bankc  = 0,    \
	 (self)->rm_bankv  = NULL, \
	 (self)->rm_access = 0,    \
	 (self)->rm_futxc  = 0,    \
	 (self)->rm_futxv  = NULL)
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL rpc_mem_fini)(struct rpc_mem *__restrict self) {
	size_t i;
	kfree(self->rm_futxv);
	for (i = 0; i < self->rm_bankc; ++i)
		kfree(self->rm_bankv[i]);
	kfree(self->rm_bankv);
}


/* Returns the futex control word for `addr'. */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) struct rpc_futex *FCALL
rpc_mem_getfutex(struct rpc_mem *__restrict self, USER UNCHECKED void *addr) {
	size_t reqalloc, i = 0;
	struct rpc_futex *result;
	BSEARCH(i, self->rm_futxv, self->rm_futxc, .rf_addr, addr) {
		return &self->rm_futxv[i];
	}

	/* Must construct a new descriptor entry. */
	if (self->rm_futxc >= RPC_PROG_FUTEX_MAX) {
		THROW(E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED,
		      E_ILLEGAL_OPERATION_CONTEXT_RPC_PROGRAM_FUTEX_COUNT_EXCEEDED);
	}

	/* Insert the new futex descriptor. */
	reqalloc = (self->rm_futxc + 1) * sizeof(struct rpc_futex);
	if (kmalloc_usable_size(self->rm_futxv) < reqalloc)
		self->rm_futxv = (struct rpc_futex *)krealloc(self->rm_futxv, reqalloc, GFP_NORMAL);
	memmoveup(&self->rm_futxv[i + 1],
	          &self->rm_futxv[i],
	          self->rm_futxc - i,
	          sizeof(struct rpc_futex));
	result = &self->rm_futxv[i];
	++self->rm_futxc;

	/* Initialize the new futex descriptor. */
	result->rf_addr = addr;
	result->rf_wake = 0; /* No wake-ups for now... */
	return result;
}


/* Write-back all modifications made to memory. */
PRIVATE NONNULL((1)) void FCALL
rpc_mem_writeback(struct rpc_mem *__restrict self) {
	size_t i;
	for (i = 0; i < self->rm_bankc; ++i) {
		size_t j, size;
		struct rpc_membank *bank;
		bank = self->rm_bankv[i];
		size = rpc_membank_size(bank);
		for (j = 0; j < size;) {
			size_t num_changed;
			while (j < size && !rpc_membank_waschanged(bank, j))
				++j;
			num_changed = 0;
			while ((j + num_changed) < size && rpc_membank_waschanged(bank, j + num_changed))
				++num_changed;
			memcpy(bank->rmb_addrlo + j,
			       rpc_membank_data(bank) + j,
			       num_changed);
			j += num_changed;
		}
	}

	/* Once memory modifications are done, perform futex wakeups. */
	for (i = 0; i < self->rm_futxc; ++i) {
		/* Look for a futex at the given address (if one exists)
		 * Note that this lookup can only be done _after_ memory
		 * modifications  are made, as  anything else would ruin
		 * interlocked synchronization! */
		REF struct mfutex *ftx;
		ftx = mman_lookupfutex(THIS_MMAN, self->rm_futxv[i].rf_addr);
		if (ftx != NULL) {
			sig_sendmany(&ftx->mfu_signal, self->rm_futxv[i].rf_wake);
			decref_unlikely(ftx);
		}
	}
}

/* Verify that `addr' is writable (VIO is allowed), but DON'T invoke VIO (if `addr' points to such a mapping) */
LOCAL void FCALL verify_writable_byte(USER CHECKED byte_t *addr) {
	byte_t buf;
	if (!readb_nopf(addr, &buf) || !writeb_nopf(addr, buf)) {
		/* Force a fault for the given address */
		mman_forcefault(THIS_MMAN, addr, 1, MMAN_FAULT_F_WRITE);
	}
}

#define rpc_mem_read(self, addr, buf, num_bytes)  rpc_mem_readwrite(self, (byte_t *)(addr), buf, num_bytes, false)
#define rpc_mem_write(self, addr, buf, num_bytes) rpc_mem_readwrite(self, (byte_t *)(addr), (void *)(buf), num_bytes, true)
PRIVATE NONNULL((1, 3)) void FCALL
rpc_mem_readwrite(struct rpc_mem *__restrict self,
                  USER UNCHECKED byte_t *addr,
                  void *buf, size_t num_bytes,
                  bool is_writing)
		THROWS(E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED) {
	size_t i;
	struct rpc_membank *bank;
	struct rpc_membank *pred, *succ;
	validate_readwrite(addr, num_bytes);
again:
	i = 0;
	BSEARCH_RANGE (i, self->rm_bankv, self->rm_bankc,
	                                  ->rmb_addrlo,
	                                  ->rmb_addrhi,
	               addr) {
		/* Found it! */
		bank = self->rm_bankv[i];
		goto rw_bank;
	}
	{
		pred = succ = NULL;
		if (i != 0)
			pred = self->rm_bankv[i - 1];
		if (i < self->rm_bankc)
			succ = self->rm_bankv[i];
		if (pred) {
			/* Try to expand the predecessor back */
			size_t distance, num_insert;
			distance = (size_t)(addr - (pred->rmb_addrhi + 1));
			if (distance <= RPC_MEMBANK_JOIN_THRESHOLD) {
				num_insert = num_bytes;
				if (num_insert < RPC_MEMBANK_EXPAND_OVERCACHE)
					num_insert = RPC_MEMBANK_EXPAND_OVERCACHE;
				if (succ) {
					size_t max = (size_t)(succ->rmb_addrlo - addr);
					if (num_insert > max)
						num_insert = max;
				}
				num_insert += distance;
				pred = rpc_membank_insert_back(pred, num_insert);
				self->rm_bankv[i - 1] = pred;
				if (succ && pred->rmb_addrhi + 1 + RPC_MEMBANK_JOIN_THRESHOLD >= succ->rmb_addrlo) {
					/* Re-join with successor bank. */
					size_t missing;
join_pred_succ:
					missing = (size_t)(succ->rmb_addrlo - (pred->rmb_addrhi + 1));
					if (missing != 0) {
						pred = rpc_membank_insert_back(pred, missing);
						self->rm_bankv[i - 1] = pred;
					}
					pred = rpc_membank_join(pred, succ);
					--self->rm_bankc;
					memmovedown(&self->rm_bankv[i - 1],
					            &self->rm_bankv[i],
					            self->rm_bankc - i,
					            sizeof(struct rpc_membank *));
					self->rm_bankv[i - 1] = pred;
				}
				bank = pred;
				goto rw_bank;
			}
		}
		if (succ) {
			/* Try to expand the successor bank */
			size_t distance;
			if (OVERFLOW_USUB((uintptr_t)succ->rmb_addrlo,
			                  (uintptr_t)(addr + num_bytes),
			                  &distance))
				distance = 0;
			if (distance <= RPC_MEMBANK_JOIN_THRESHOLD) {
				size_t num_insert;
				num_insert = (size_t)(succ->rmb_addrlo - addr);
				if (num_insert > num_bytes)
					num_insert = num_bytes;
				if (num_insert < RPC_MEMBANK_EXPAND_OVERCACHE)
					num_insert = RPC_MEMBANK_EXPAND_OVERCACHE;
				num_insert += distance;
				if (pred) {
					size_t max_insert = (size_t)(succ->rmb_addrlo - (pred->rmb_addrhi + 1));
					if (num_insert > max_insert)
						num_insert = max_insert;
				}
				succ = rpc_membank_insert_front(succ, num_insert);
				self->rm_bankv[i] = succ;
				if (pred && pred->rmb_addrhi + 1 + RPC_MEMBANK_JOIN_THRESHOLD >= succ->rmb_addrlo)
					goto join_pred_succ;
				bank = succ;
				goto rw_bank;
			}
		}
	}

	/* Ensure that the vector has enough space for +1 more bank. */
	{
		size_t new_req_vector_size = (self->rm_bankc + 1) * sizeof(struct rpc_membank *);
		if (kmalloc_usable_size(self->rm_bankv) < new_req_vector_size)
			self->rm_bankv = (struct rpc_membank **)krealloc(self->rm_bankv, new_req_vector_size, GFP_NORMAL);
	}

	/* Create a new bank and insert at `i' */
	bank = rpc_membank_create(addr, num_bytes);
	memmoveup(&self->rm_bankv[i + 1],
	          &self->rm_bankv[i],
	          self->rm_bankc - i,
	          sizeof(struct rpc_membank *));
	self->rm_bankv[i] = bank;
	++self->rm_bankc;

	/* Do read/write I/O with `bank' */
	{
		size_t avail, reladdr;
		byte_t *bankdat;
rw_bank:
		assert(addr >= bank->rmb_addrlo);
		assert(addr <= bank->rmb_addrhi);
		avail = (size_t)((bank->rmb_addrhi + 1) - addr);
		if (avail > num_bytes)
			avail = num_bytes;
		reladdr = (size_t)(addr - bank->rmb_addrlo);
		bankdat = rpc_membank_data(bank) + reladdr;
		if (is_writing) {
			size_t j;
			for (j = 0; j < avail; ++j, ++reladdr) {
				int st = rpc_membank_getstatus(bank, reladdr);
				if (st != (RPC_MEMBANK_STATUS_F_LOADED | RPC_MEMBANK_STATUS_F_CHANGED)) {
					if (!(st & RPC_MEMBANK_STATUS_F_LOADED)) {
						if (++self->rm_access >= RPC_PROG_MEMORY_MAX)
							THROW(E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED,
							      E_ILLEGAL_OPERATION_CONTEXT_RPC_PROGRAM_MEMORY_EXCEEDED);
					}
					/* Ensure that the address is writable, but don't write the final value, yet. */
					verify_writable_byte(addr + j);
					st = RPC_MEMBANK_STATUS_F_LOADED | RPC_MEMBANK_STATUS_F_CHANGED;
					rpc_membank_setstatus(bank, reladdr, st);
				}
			}
			memcpy(bankdat, buf, avail);
		} else {
			size_t j;
			for (j = 0; j < avail; ++j, ++reladdr) {
				int st = rpc_membank_getstatus(bank, reladdr);
				if (!(st & RPC_MEMBANK_STATUS_F_LOADED)) {
					if (++self->rm_access >= RPC_PROG_MEMORY_MAX)
						THROW(E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED,
						      E_ILLEGAL_OPERATION_CONTEXT_RPC_PROGRAM_MEMORY_EXCEEDED);
					bankdat[j] = ATOMIC_READ(addr[j]);
					st |= RPC_MEMBANK_STATUS_F_LOADED;
					rpc_membank_setstatus(bank, reladdr, st);
				}
			}
			memcpy(buf, bankdat, avail);
		}
		if (avail >= num_bytes)
			return;
		addr += avail;
		buf = (byte_t *)buf + avail;
		num_bytes -= avail;
	}
	goto again;
}

PRIVATE NONNULL((1)) void FCALL
rpc_mem_fill(struct rpc_mem *__restrict self,
             USER UNCHECKED byte_t *addr,
             byte_t filler, size_t num_bytes)
		THROWS(E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED) {
	void *buffer;
	size_t bufsize = 256;
	if (bufsize > num_bytes)
		bufsize = num_bytes;
	buffer = memset(alloca(bufsize), filler, bufsize);
	while (num_bytes) {
		if (bufsize > num_bytes)
			bufsize = num_bytes;
		rpc_mem_write(self, addr, buffer, bufsize);
		num_bytes -= bufsize;
		addr += bufsize;
	}
}



/* Flags for `struct rpc_vm::rv_flags' */
#define RPC_VM_NORMAL           0x0000 /* Normal flags. */
#define RPC_VM_HAVESIGMASK      0x0001 /* `rv_sigmask' must be or'd with the calling thread's signal mask. */
#ifdef CONFIG_HAVE_FPU
#define RPC_VM_HAVEFPU          0x0002 /* FPU state loaded */
#define RPC_VM_HAVEFPU_MODIFIED 0x0004 /* FPU state was modified */
#endif /* CONFIG_HAVE_FPU */
#if defined(__i386__) && !defined(__x86_64__)
#define RPC_VM_HAVE_FSBASE      0x4000 /* `rv_386_fsbase' must be set during exit. */
#define RPC_VM_HAVE_GSBASE      0x8000 /* `rv_386_gsbase' must be set during exit. */
#elif defined(__arm__)
#define RPC_VM_HAVE_TLSBASE     0x8000 /* `rv_arm_tlsbase' must be set during exit. */
#endif /* ... */

struct rpc_vm {
	struct rpc_mem                 rv_mem;                       /* Memory access controller. */
	struct ucpustate               rv_cpu;                       /* Cpu state. */
	struct pending_rpc            *rv_rpc;                       /* [1..1][const] The RPC in question. */
	unsigned int                   rv_reason;                    /* [const] RPC reason (one of `_RPC_REASONCTX_*') */
	struct rpc_syscall_info const *rv_sc_info;                   /* [1..1][valid_if(rv_reason == _RPC_REASONCTX_SYSCALL ||
	                                                              *                 rv_reason == _RPC_REASONCTX_SYSINT)]
	                                                              * [const] System call information */
#ifdef CONFIG_HAVE_FPU
	struct fpustate                rv_fpu;                       /* [valid_if(RPC_VM_HAVEFPU)] FPU context. */
#endif /* CONFIG_HAVE_FPU */
	uintptr_t                      rv_flags;                     /* Set of `RPC_VM_*'. */
	size_t                         rv_stacksz;                   /* # of in-use elements in `rv_stack' */
	uintptr_t                      rv_stack[RPC_PROG_STACK_MAX]; /* [rv_stacksz] RPC program stack. */
	USER CHECKED byte_t const     *rv_pc;                        /* [?..1] User-space address of next PC byte. */
	byte_t                         rv_pcbuf_ptr;                 /* Index of next byte to read from `rv_pcbuf' */
	byte_t                         rv_pcbuf_siz;                 /* # of unread bytes at `&rv_pcbuf[rv_pcbuf_ptr]' */
	byte_t                         rv_pcbuf[32];                 /* Program text buffer. */
	sigset_t                       rv_sigmask;                   /* [valid_if(RPC_VM_HAVESIGMASK)] Additional signals to mask. */
#if defined(__i386__) && !defined(__x86_64__)
	uintptr_t                      rv_386_fsbase;                /* [valid_if(RPC_VM_HAVE_FSBASE)] Value for %fs.base (to-be loaded during exit) */
	uintptr_t                      rv_386_gsbase;                /* [valid_if(RPC_VM_HAVE_GSBASE)] Value for %gs.base (to-be loaded during exit) */
#elif defined(__arm__)
	uintptr_t                      rv_arm_tlsbase;               /* [valid_if(RPC_VM_HAVE_TLSBASE)] Value for user-space TLS base (to-be loaded during exit) */
#endif /* __i386__ && !__x86_64__ */
#ifdef __ARCH_HAVE_COMPAT
	unwind_getreg_t                rv_unwind_getreg;             /* [1..1][const] Unwind get register function. */
	void                          *rv_unwind_getreg_arg;         /* Argument for `rv_unwind_getreg'. */
	unwind_setreg_t                rv_unwind_setreg;             /* [1..1][const] Unwind set register function. */
	void                          *rv_unwind_setreg_arg;         /* Argument for `rv_unwind_setreg'. */
#endif /* __ARCH_HAVE_COMPAT */
};

#define rpc_vm_fini(self) rpc_mem_fini(&(self)->rv_mem)

/* Return the size of an address. */
#ifdef __ARCH_HAVE_COMPAT
#define rpc_vm_addrsize(self) \
	(ucpustate_iscompat(&(self)->rv_cpu) ? __ARCH_COMPAT_SIZEOF_POINTER : SIZEOF_POINTER)
#else /* __ARCH_HAVE_COMPAT */
#define rpc_vm_addrsize(self) SIZEOF_POINTER
#endif /* !__ARCH_HAVE_COMPAT */

/* Return a pointer to the get/set-register function or its cookie-argument */
#ifdef __ARCH_HAVE_COMPAT
#define rpc_vm_getreg_cb(self)  (self)->rv_unwind_getreg
#define rpc_vm_getreg_arg(self) (self)->rv_unwind_getreg_arg
#define rpc_vm_setreg_cb(self)  (self)->rv_unwind_setreg
#define rpc_vm_setreg_arg(self) (self)->rv_unwind_setreg_arg
#else /* __ARCH_HAVE_COMPAT */
#define rpc_vm_getreg_cb(self)  (&rpc_vm_getreg_impl)
#define rpc_vm_getreg_arg(self) (self)
#define rpc_vm_setreg_cb(self)  (&rpc_vm_setreg_impl)
#define rpc_vm_setreg_arg(self) (self)
#endif /* !__ARCH_HAVE_COMPAT */

/* Directly get or set a register. */
#define rpc_vm_getreg(self, dw_regno, dst) (*rpc_vm_getreg_cb(self))(rpc_vm_getreg_arg(self), dw_regno, dst)
#define rpc_vm_setreg(self, dw_regno, src) (*rpc_vm_setreg_cb(self))(rpc_vm_setreg_arg(self), dw_regno, src)

/* Access user-space memory. */
#define rpc_vm_rdmem(self, addr, buf, num_bytes)   rpc_mem_read(&(self)->rv_mem, addr, buf, num_bytes)
#define rpc_vm_wrmem(self, addr, buf, num_bytes)   rpc_mem_write(&(self)->rv_mem, addr, buf, num_bytes)
#define rpc_vm_memset(self, addr, byte, num_bytes) rpc_mem_fill(&(self)->rv_mem, addr, byte, num_bytes)


PRIVATE NONNULL((1, 3)) unsigned int LIBUNWIND_CC
rpc_vm_getreg_impl(void const *arg, unwind_regno_t dw_regno, void *__restrict dst) {
	struct rpc_vm *me = (struct rpc_vm *)arg;
	unsigned int result;
	result = unwind_getreg_ucpustate(&me->rv_cpu, dw_regno, dst);
#ifdef CONFIG_HAVE_FPU
	/* Check for FPU register */
	if (result == UNWIND_INVALID_REGISTER && CFI_UNWIND_IS_FPU_REGISTER(sizeof(void *), dw_regno)) {
		if (!(me->rv_flags & RPC_VM_HAVEFPU)) {
			fpustate_saveinto(&me->rv_fpu);
			me->rv_flags |= RPC_VM_HAVEFPU;
		}
#if defined(__x86_64__) || defined(__i386__)
		result = x86_fpustate_variant == FPU_STATE_SSTATE
		         ? unwind_getreg_sfpustate(&me->rv_fpu, dw_regno, dst)
		         : unwind_getreg_xfpustate(&me->rv_fpu, dw_regno, dst);
#else /* __x86_64__ || __i386__ */
		result = unwind_getreg_fpustate(&me->rv_fpu, dw_regno, dst);
#endif /* !__x86_64__ && !__i386__ */
	}
#endif /* CONFIG_HAVE_FPU */
	return result;
}

PRIVATE NONNULL((1, 3)) unsigned int LIBUNWIND_CC
rpc_vm_setreg_impl(void *arg, unwind_regno_t dw_regno, void const *__restrict src) {
	struct rpc_vm *me = (struct rpc_vm *)arg;
	unsigned int result;
	result = unwind_setreg_ucpustate(&me->rv_cpu, dw_regno, src);
#ifdef CONFIG_HAVE_FPU
	/* Check for FPU register */
	if (result == UNWIND_INVALID_REGISTER && CFI_UNWIND_IS_FPU_REGISTER(sizeof(void *), dw_regno)) {
		if (!(me->rv_flags & RPC_VM_HAVEFPU)) {
			fpustate_saveinto(&me->rv_fpu);
			me->rv_flags |= RPC_VM_HAVEFPU;
		}
#if defined(__x86_64__) || defined(__i386__)
		result = x86_fpustate_variant == FPU_STATE_SSTATE
		         ? unwind_setreg_sfpustate(&me->rv_fpu, dw_regno, src)
		         : unwind_setreg_xfpustate(&me->rv_fpu, dw_regno, src);
#else /* __x86_64__ || __i386__ */
		result = unwind_setreg_fpustate(&me->rv_fpu, dw_regno, src);
#endif /* !__x86_64__ && !__i386__ */
		if (result == UNWIND_SUCCESS)
			me->rv_flags |= RPC_VM_HAVEFPU_MODIFIED;
	}
#endif /* CONFIG_HAVE_FPU */
	return result;
}




/* Return the user-space stack pointer register */
#ifdef ucpustate_getsp
#define rpc_vm_getsp(self) ((USER UNCHECKED byte_t *)ucpustate_getsp(&(self)->rv_cpu))
#else /* ucpustate_getsp */
PRIVATE WUNUSED NONNULL((1)) USER UNCHECKED byte_t *FCALL
rpc_vm_getsp(struct rpc_vm *__restrict self) {
	byte_t *result;
#ifdef NDEBUG
	rpc_vm_getreg(self, CFI_UNWIND_REGISTER_SP(sizeof(void *)), &result);
#else /* NDEBUG */
	unsigned int error;
	error = rpc_vm_getreg(self, CFI_UNWIND_REGISTER_SP(sizeof(void *)), &result);
	assertf(error == UNWIND_SUCCESS, "%u", error);
#endif /* !NDEBUG */
	return result;
}
#endif /* !ucpustate_getsp */

/* Set the user-space stack pointer register */
#ifdef ucpustate_setsp
#define rpc_vm_setsp(self, value) ucpustate_setsp(&(self)->rv_cpu, value)
#else /*ucpustate_setsp */
PRIVATE NONNULL((1)) void FCALL
rpc_vm_setsp(struct rpc_vm *__restrict self, USER UNCHECKED byte_t *value) {
#ifdef NDEBUG
	rpc_vm_setreg(self, CFI_UNWIND_REGISTER_SP(sizeof(void *)), &value);
#else /* NDEBUG */
	unsigned int error;
	error = rpc_vm_setreg(self, CFI_UNWIND_REGISTER_SP(sizeof(void *)), &value);
	assertf(error == UNWIND_SUCCESS, "%u", error);
#endif /* !NDEBUG */
}
#endif /* !ucpustate_setsp */

/* Fill the RPC program text buffer and ensure that at least `minbytes' bytes are available */
PRIVATE NONNULL((1)) void FCALL
rpc_vm_pc_filbuf(struct rpc_vm *__restrict self, size_t minbytes) THROWS(E_SEGFAULT) {
	size_t error, ok;
	assert(minbytes > self->rv_pcbuf_siz);
	validate_readable(self->rv_pc, 1);
	if (self->rv_pcbuf_siz != 0) {
		size_t have = self->rv_pcbuf_siz;
		if likely(self->rv_pcbuf_ptr != 0) {
			/* Reclaim unused buffer space. */
			memmovedown(&self->rv_pcbuf[0],
			            &self->rv_pcbuf[self->rv_pcbuf_ptr],
			            have);
			self->rv_pcbuf_ptr = 0;
		}
		error = mman_read_nopf(self->rv_rpc->pr_user.pur_mman,
		                       self->rv_pc + have, self->rv_pcbuf + have,
		                       sizeof(self->rv_pcbuf) - have);
		ok = (sizeof(self->rv_pcbuf) - error) + have;
	} else {
		self->rv_pcbuf_ptr = 0;
		error = mman_read_nopf(self->rv_rpc->pr_user.pur_mman,
		                       self->rv_pc, self->rv_pcbuf,
		                       sizeof(self->rv_pcbuf));
		ok = (sizeof(self->rv_pcbuf) - error);
	}
	self->rv_pcbuf_siz = ok;
	if unlikely(ok < minbytes) {
		mman_read(self->rv_rpc->pr_user.pur_mman,
		          self->rv_pc + ok, self->rv_pcbuf + ok,
		          minbytes - ok);
		self->rv_pcbuf_siz = minbytes;
	}
}

/* Dereference & read from program memory before incrementing the program counter. */
PRIVATE NONNULL((1)) void FCALL
rpc_vm_pc_rdx(struct rpc_vm *__restrict self, void *buf, size_t num_bytes) THROWS(E_SEGFAULT) {
	if (self->rv_pcbuf_siz < num_bytes)
		rpc_vm_pc_filbuf(self, num_bytes);
	memcpy(buf, &self->rv_pcbuf[self->rv_pcbuf_ptr], num_bytes);
	self->rv_pc += num_bytes;
	self->rv_pcbuf_ptr += num_bytes;
	self->rv_pcbuf_siz -= num_bytes;
}

PRIVATE NONNULL((1)) uint8_t FCALL
rpc_vm_pc_rdb(struct rpc_vm *__restrict self) THROWS(E_SEGFAULT) {
	uint8_t result;
	if (self->rv_pcbuf_siz < 1)
		rpc_vm_pc_filbuf(self, 1);
	result = self->rv_pcbuf[self->rv_pcbuf_ptr];
	++self->rv_pc;
	++self->rv_pcbuf_ptr;
	--self->rv_pcbuf_siz;
	return result;
}

PRIVATE NONNULL((1)) uint16_t FCALL
rpc_vm_pc_rdw(struct rpc_vm *__restrict self) THROWS(E_SEGFAULT) {
	uint16_t result;
	if (self->rv_pcbuf_siz < 2)
		rpc_vm_pc_filbuf(self, 2);
	result = UNALIGNED_GET16((uint16_t const *)&self->rv_pcbuf[self->rv_pcbuf_ptr]);
	self->rv_pc += 2;
	self->rv_pcbuf_ptr += 2;
	self->rv_pcbuf_siz -= 2;
	return result;
}

PRIVATE NONNULL((1)) uint32_t FCALL
rpc_vm_pc_rdl(struct rpc_vm *__restrict self) THROWS(E_SEGFAULT) {
	uint32_t result;
	if (self->rv_pcbuf_siz < 4)
		rpc_vm_pc_filbuf(self, 4);
	result = UNALIGNED_GET32((uint32_t const *)&self->rv_pcbuf[self->rv_pcbuf_ptr]);
	self->rv_pc += 4;
	self->rv_pcbuf_ptr += 4;
	self->rv_pcbuf_siz -= 4;
	return result;
}

#if SIZEOF_POINTER >= 8
PRIVATE NONNULL((1)) uint64_t FCALL
rpc_vm_pc_rdq(struct rpc_vm *__restrict self) THROWS(E_SEGFAULT) {
	uint64_t result;
	if (self->rv_pcbuf_siz < 8)
		rpc_vm_pc_filbuf(self, 8);
	result = UNALIGNED_GET64((uint64_t const *)&self->rv_pcbuf[self->rv_pcbuf_ptr]);
	self->rv_pc += 8;
	self->rv_pcbuf_ptr += 8;
	self->rv_pcbuf_siz -= 8;
	return result;
}
#endif /* SIZEOF_POINTER >= 8 */

PRIVATE NONNULL((1)) uintptr_t FCALL
rpc_vm_pc_rduleb128(struct rpc_vm *__restrict self) THROWS(E_SEGFAULT) {
	byte_t byte;
	uintptr_t result = 0;
	shift_t shift    = 0;
	for (;;) {
		byte = rpc_vm_pc_rdb(self);
		result |= ((byte & 0x7f) << shift);
		shift += 7;
		if (!(byte & 0x80))
			break;
	}
	return result;
}


/* Push the given buffer onto the user-space. */
PRIVATE NONNULL((1)) void FCALL
rpc_vm_push2user(struct rpc_vm *__restrict self,
                 void const *buf, size_t num_bytes)
		THROWS(E_SEGFAULT) {
	USER UNCHECKED byte_t *sp;
	sp = rpc_vm_getsp(self);
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
	sp -= num_bytes;
#endif /* __ARCH_STACK_GROWS_DOWNWARDS */
	rpc_vm_wrmem(self, sp, buf, num_bytes);
#ifndef __ARCH_STACK_GROWS_DOWNWARDS
	sp += num_bytes;
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
	rpc_vm_setsp(self, sp);
}


PRIVATE NONNULL((1)) void FCALL
rpc_vm_push2user_fill(struct rpc_vm *__restrict self,
                      byte_t byte, size_t num_bytes)
		THROWS(E_SEGFAULT) {
	USER UNCHECKED byte_t *sp;
	sp = rpc_vm_getsp(self);
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
	sp -= num_bytes;
#endif /* __ARCH_STACK_GROWS_DOWNWARDS */
	rpc_vm_memset(self, sp, byte, num_bytes);
#ifndef __ARCH_STACK_GROWS_DOWNWARDS
	sp += num_bytes;
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
	rpc_vm_setsp(self, sp);
}


PRIVATE ATTR_NOINLINE NONNULL((1)) void FCALL
rpc_vm_push2user_sigset(struct rpc_vm *__restrict self,
                        size_t sigsetsize)
		THROWS(E_SEGFAULT) {
	size_t overflow = 0;
	sigset_t sigset;
	sigmask_getmask(&sigset);
	if (sigsetsize > sizeof(sigset_t)) {
		overflow   = sigsetsize - sizeof(sigset_t);
		sigsetsize = sizeof(sigset_t);
	}
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
	if (overflow != 0)
		rpc_vm_push2user_fill(self, 0xff, overflow);
	rpc_vm_push2user(self, &sigset, sigsetsize);
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
	rpc_vm_push2user(self, &sigset, sigsetsize);
	if (overflow != 0)
		rpc_vm_push2user_fill(self, 0xff, overflow);
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
}


#define CANPUSH(n) (self->rv_stacksz <= RPC_PROG_STACK_MAX - (n))
#define CANPOP(n)  (self->rv_stacksz >= (n))
#define POP()      self->rv_stack[--self->rv_stacksz]
#define PUSH(v)    (void)(self->rv_stack[self->rv_stacksz++] = (v))
#define TOP        self->rv_stack[self->rv_stacksz - 1]
#define FIRST      self->rv_stack[self->rv_stacksz - 1]
#define SECOND     self->rv_stack[self->rv_stacksz - 2]
#define THIRD      self->rv_stack[self->rv_stacksz - 3]


/* Push the given buffer onto the user-space. */
PRIVATE NONNULL((1)) void FCALL
rpc_vm_pushreg(struct rpc_vm *__restrict self, unwind_regno_t regno)
		THROWS(E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED, ...) {
	unsigned int error;
	alignas(alignof(uintptr_t))
	byte_t buf[CFI_REGISTER_MAXSIZE];
	size_t adrsz = rpc_vm_addrsize(self);
	size_t regsz = CFI_REGISTER_MEMSIZE(adrsz, regno);
	size_t words = CEILDIV(regsz, adrsz);
	assert(words);

	/* Load the register */
	bzero(buf, regsz);
	error = rpc_vm_getreg(self, regno, buf);
	if unlikely(error != UNWIND_SUCCESS) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RPC_PROGRAM_UNKNOWN_REGISTER,
		      regno);
	}
	if unlikely(!CANPUSH(words)) {
		THROW(E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED,
		      E_ILLEGAL_OPERATION_CONTEXT_RPC_PROGRAM_STACK_OVERFLOW);
	}
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	while unlikely(words > 1) {
		--words;
		PUSH(((uintptr_t *)buf)[words]);
	}
	PUSH(*(uintptr_t *)buf);
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
	PUSH(*(uintptr_t *)buf);
	if unlikely(words > 1) {
		size_t i;
		for (i = 1; i < words; ++i)
			PUSH(((uintptr_t *)buf)[i]);
	}
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
}

PRIVATE NONNULL((1)) void FCALL
rpc_vm_popreg(struct rpc_vm *__restrict self, unwind_regno_t regno) {
	unsigned int error;
	alignas(alignof(uintptr_t))
	byte_t buf[CFI_REGISTER_MAXSIZE];
	size_t adrsz = rpc_vm_addrsize(self);
	size_t regsz = CFI_REGISTER_MEMSIZE(adrsz, regno);
	size_t words = CEILDIV(regsz, adrsz);
	assert(words);
	if unlikely(!CANPOP(words)) {
		THROW(E_INVALID_OPERATION,
		      E_ILLEGAL_OPERATION_CONTEXT_RPC_PROGRAM_STACK_UNDERFLOW);
	}
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	*(uintptr_t *)buf = POP();
	if unlikely(words > 1) {
		size_t i;
		for (i = 1; i < words; ++i)
			((uintptr_t *)buf)[i] = POP();
	}
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
	while unlikely(words > 1) {
		--words;
		((uintptr_t *)buf)[words] = POP();
	}
	*(uintptr_t *)buf = POP();
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */

	/* Save the register */
	error = rpc_vm_setreg(self, regno, buf);
	if unlikely(error != UNWIND_SUCCESS) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RPC_PROGRAM_UNKNOWN_REGISTER,
		      regno);
	}
}

/* Push the given register onto the user-space. */
PRIVATE NONNULL((1)) void FCALL
rpc_vm_pushreg2user(struct rpc_vm *__restrict self, unwind_regno_t regno) {
	unsigned int error;
	alignas(alignof(uintptr_t))
	byte_t buf[CFI_REGISTER_MAXSIZE];
	size_t adrsz = rpc_vm_addrsize(self);
	size_t regsz = CFI_REGISTER_MEMSIZE(adrsz, regno);
	size_t words = CEILDIV(regsz, adrsz);
	assert(words);

	/* Load the register */
	bzero(buf, regsz);
	error = rpc_vm_getreg(self, regno, buf);
	if unlikely(error != UNWIND_SUCCESS) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RPC_PROGRAM_UNKNOWN_REGISTER,
		      regno);
	}
	rpc_vm_push2user(self, buf, words * adrsz);
}




/* Parse & execute a single instruction
 * @return: true:  Success
 * @return: false: Success, but the instruction was `RPC_OP_ret' */
PRIVATE NONNULL((1)) bool FCALL
rpc_vm_instr(struct rpc_vm *__restrict self)
		THROWS(...) {
#if defined(__ARCH_HAVE_COMPAT) && __ARCH_COMPAT_SIZEOF_POINTER < SIZEOF_POINTER
	/* In compatibility mode, stack values are sign extended */
#define COMPAT_SIGN_EXTEND(value)                                                  \
	do {                                                                           \
		if (ucpustate_iscompat(&self->rv_cpu)) {                                   \
			value = (uintptr_t)(intptr_t)(compat_intptr_t)(compat_uintptr_t)value; \
		}                                                                          \
	}	__WHILE0
#else /* __ARCH_HAVE_COMPAT && __ARCH_COMPAT_SIZEOF_POINTER < SIZEOF_POINTER */
#define COMPAT_SIGN_EXTEND(value) /* nothing */
#endif /* !__ARCH_HAVE_COMPAT || __ARCH_COMPAT_SIZEOF_POINTER >= SIZEOF_POINTER */
	byte_t opcode = rpc_vm_pc_rdb(self);
	switch (opcode) {
#ifdef RPC_TRACE_INSTRUCTIONS
#define TRACE_INSTRUCTION(...) printk(KERN_TRACE "[rpc] " __VA_ARGS__)
#define CASE(x) __IF0 { case x: printk(KERN_TRACE "[rpc] " #x "\n"); }
#else /* RPC_TRACE_INSTRUCTIONS */
#define TRACE_INSTRUCTION(...) /* nothing */
#define CASE(x) case x:
#endif /* !RPC_TRACE_INSTRUCTIONS */

	CASE(RPC_OP_ret)
		return false;

	case RPC_OP_sppush_const: {
		byte_t buf[SIZEOF_POINTER];
		size_t siz = rpc_vm_addrsize(self);
		rpc_vm_pc_rdx(self, buf, siz);
#ifdef __ARCH_HAVE_COMPAT
		TRACE_INSTRUCTION("RPC_OP_sppush_const %#" PRIxPTR "\n",
		                  siz == sizeof(uintptr_t) ? UNALIGNED_GET((uintptr_t *)buf)
		                                           : (uintptr_t)UNALIGNED_GET((compat_uintptr_t *)buf));
#else /* __ARCH_HAVE_COMPAT */
		TRACE_INSTRUCTION("RPC_OP_sppush_const %#" PRIxPTR "\n", UNALIGNED_GET((uintptr_t *)buf));
#endif /* !__ARCH_HAVE_COMPAT */
		rpc_vm_push2user(self, buf, siz);
	}	break;

	CASE(RPC_OP_sppush_pop) {
		size_t siz = rpc_vm_addrsize(self);
		if unlikely(!CANPOP(1))
			goto err_stack_underflow;
		rpc_vm_push2user(self, &TOP, siz);
		--self->rv_stacksz;
	}	break;

	case RPC_OP_const1u: {
		uint8_t value;
		value = rpc_vm_pc_rdb(self);
		TRACE_INSTRUCTION("RPC_OP_const1u %#" PRIx8 "\n", value);
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
		PUSH((uintptr_t)value);
	}	break;

	case RPC_OP_const1s: {
		int8_t value;
		value = (int8_t)rpc_vm_pc_rdb(self);
		TRACE_INSTRUCTION("RPC_OP_const1s %" PRId8 "\n", value);
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
		PUSH((uintptr_t)(intptr_t)value);
	}	break;

	case RPC_OP_const2u: {
		uint16_t value;
		value = rpc_vm_pc_rdw(self);
		TRACE_INSTRUCTION("RPC_OP_const2u %#" PRIx16 "\n", value);
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
		PUSH((uintptr_t)value);
	}	break;

	case RPC_OP_const2s: {
		int16_t value;
		value = (int16_t)rpc_vm_pc_rdw(self);
		TRACE_INSTRUCTION("RPC_OP_const2s %" PRId16 "\n", value);
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
		PUSH((uintptr_t)(intptr_t)value);
	}	break;

	case RPC_OP_const4s:
#if SIZEOF_POINTER < 8
	case RPC_OP_const4u:
#endif /* SIZEOF_POINTER < 8 */
	{
		int32_t value;
		value = (int32_t)rpc_vm_pc_rdl(self);
#if SIZEOF_POINTER < 8 && defined(RPC_TRACE_INSTRUCTIONS)
		if (opcode == RPC_OP_const4u) {
			TRACE_INSTRUCTION("RPC_OP_const4u %#" PRIx32 "\n", value);
		} else
#endif /* SIZEOF_POINTER >= 8 || !RPC_TRACE_INSTRUCTIONS */
		{
			TRACE_INSTRUCTION("RPC_OP_const4s %" PRId32 "\n", value);
		}
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
		PUSH((uintptr_t)(intptr_t)value);
	}	break;

#if SIZEOF_POINTER >= 8
	case RPC_OP_const4u: {
		uintptr_t value;
		value = (uintptr_t)rpc_vm_pc_rdl(self);
		TRACE_INSTRUCTION("RPC_OP_const4u %#" PRIx32 "\n", (uint32_t)value);
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
		/* Force sign extension in compatibility mode. */
#if defined(__ARCH_HAVE_COMPAT) && __ARCH_COMPAT_SIZEOF_POINTER < SIZEOF_POINTER
		if (ucpustate_iscompat(&self->rv_cpu))
			value = (uintptr_t)(intptr_t)(int32_t)value;
#endif /* !__ARCH_HAVE_COMPAT || __ARCH_COMPAT_SIZEOF_POINTER >= SIZEOF_POINTER */
		PUSH(value);
	}	break;

	case RPC_OP_const8u:
	case RPC_OP_const8s: {
		uintptr_t value;
#if defined(__ARCH_HAVE_COMPAT) && __ARCH_COMPAT_SIZEOF_POINTER < 8
		if (rpc_vm_addrsize(self) < 8)
			goto err_illegal_instruction;
#define WANT_err_illegal_instruction
#endif /* __ARCH_HAVE_COMPAT && __ARCH_COMPAT_SIZEOF_POINTER < 8 */
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
		value = (uintptr_t)rpc_vm_pc_rdq(self);
#ifdef RPC_TRACE_INSTRUCTIONS
		if (opcode == RPC_OP_const8u) {
			TRACE_INSTRUCTION("RPC_OP_const8u %#" PRIx64 "\n", value);
		} else
#endif /* RPC_TRACE_INSTRUCTIONS */
		{
			TRACE_INSTRUCTION("RPC_OP_const8s %" PRId64 "\n", value);
		}
		PUSH(value);
	}	break;
#endif /* SIZEOF_POINTER >= 8 */

	CASE(RPC_OP_dup) {
		uintptr_t value;
		if unlikely(!CANPOP(1))
			goto err_stack_underflow;
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
		value = TOP;
		PUSH(value);
	}	break;

	CASE(RPC_OP_drop)
		if unlikely(!CANPOP(1))
			goto err_stack_underflow;
		--self->rv_stacksz;
		break;

	CASE(RPC_OP_over) {
		uintptr_t value;
		if unlikely(!CANPOP(2))
			goto err_stack_underflow;
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
		value = SECOND;
		PUSH(value);
	}	break;

	case RPC_OP_pick: {
		uint8_t nth = rpc_vm_pc_rdb(self);
		TRACE_INSTRUCTION("RPC_OP_pick %" PRIu8 "\n", nth);
		if unlikely(nth >= self->rv_stacksz)
			goto err_stack_underflow;
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
		self->rv_stack[self->rv_stacksz] = self->rv_stack[(self->rv_stacksz - 1) - nth];
		++self->rv_stacksz;
	}	break;

	CASE(RPC_OP_swap) {
		uintptr_t temp;
		if unlikely(self->rv_stacksz < 2)
			goto err_stack_underflow;
		temp   = SECOND;
		SECOND = TOP;
		TOP    = temp;
	}	break;

	CASE(RPC_OP_rot) {
		uintptr_t temp;
		if unlikely(self->rv_stacksz < 3)
			goto err_stack_underflow;
		temp   = TOP;
		TOP    = SECOND;
		SECOND = THIRD;
		THIRD  = temp;
	}	break;

	CASE(RPC_OP_abs)
	CASE(RPC_OP_neg)
	CASE(RPC_OP_not)
		/* Unary (1-operand) arithmetic and bit-wise operators. */
		if unlikely(self->rv_stacksz < 1)
			goto err_stack_underflow;
		switch (opcode) {
		case RPC_OP_abs:
			if ((intptr_t)TOP < 0)
				TOP = (uintptr_t)(-(intptr_t)TOP);
			break;
		case RPC_OP_neg:
			TOP = (uintptr_t)(-(intptr_t)TOP);
			break;
		case RPC_OP_not:
			TOP = ~TOP;
			break;
		default:
			__builtin_unreachable();
		}
		break;

	CASE(RPC_OP_and)
	CASE(RPC_OP_div)
	CASE(RPC_OP_minus)
	CASE(RPC_OP_mod)
	CASE(RPC_OP_mul)
	CASE(RPC_OP_or)
	CASE(RPC_OP_plus)
	CASE(RPC_OP_shl)
	CASE(RPC_OP_shr)
	CASE(RPC_OP_shra)
	CASE(RPC_OP_xor)
	CASE(RPC_OP_eq)
	CASE(RPC_OP_ge)
	CASE(RPC_OP_gt)
	CASE(RPC_OP_le)
	CASE(RPC_OP_lt)
	CASE(RPC_OP_ne)
	CASE(RPC_OP_uge)
	CASE(RPC_OP_ugt)
	CASE(RPC_OP_ule)
	CASE(RPC_OP_ult)
		/* Binary (2-operand) arithmetic and bit-wise operators. */
		if unlikely(self->rv_stacksz < 2)
			goto err_stack_underflow;
		switch (opcode) {
#if 0 /* Not needed; already done by the CPU throwing `E_DIVIDE_BY_ZERO' */
		case RPC_OP_div:
		case RPC_OP_mod:
			if unlikely(TOP == 0)
				THROW(E_DIVIDE_BY_ZERO);
			if (opcode == DW_OP_div) {
				SECOND = (uintptr_t)((intptr_t)SECOND / (intptr_t)TOP);
			} else {
				SECOND = (uintptr_t)((intptr_t)SECOND % (intptr_t)TOP);
			}
			break;
#else
		case RPC_OP_div:
			SECOND = (uintptr_t)((intptr_t)SECOND / (intptr_t)TOP);
			break;
		case RPC_OP_mod:
			SECOND = (uintptr_t)((intptr_t)SECOND % (intptr_t)TOP);
			break;
#endif
		case RPC_OP_and:
			SECOND &= TOP;
			break;
		case RPC_OP_mul:
			SECOND = (uintptr_t)((intptr_t)SECOND * (intptr_t)TOP);
			break;
		case RPC_OP_or:
			SECOND |= TOP;
			break;
		case RPC_OP_shl:
			SECOND <<= TOP;
			break;
		case RPC_OP_shr:
			SECOND >>= TOP;
			break;
		case RPC_OP_shra:
#ifdef __ARCH_SIGNED_SHIFT_IS_SDIV
			SECOND = (uintptr_t)((intptr_t)SECOND >> TOP);
#else /* __ARCH_SIGNED_SHIFT_IS_SDIV */
			SECOND = (uintptr_t)((intptr_t)SECOND < 0
			                     ? (intptr_t)-1 - (((intptr_t)-1 - (intptr_t)SECOND) >> TOP)
			                     : (intptr_t)SECOND >> TOP);
#endif /* !__ARCH_SIGNED_SHIFT_IS_SDIV */
			break;
		case RPC_OP_xor:
			SECOND ^= TOP;
			break;
		case RPC_OP_eq:
			SECOND = SECOND == TOP ? 1 : 0;
			break;
		case RPC_OP_ge:
			SECOND = (intptr_t)SECOND >= (intptr_t)TOP ? 1 : 0;
			break;
		case RPC_OP_gt:
			SECOND = (intptr_t)SECOND > (intptr_t)TOP ? 1 : 0;
			break;
		case RPC_OP_le:
			SECOND = (intptr_t)SECOND <= (intptr_t)TOP ? 1 : 0;
			break;
		case RPC_OP_lt:
			SECOND = (intptr_t)SECOND < (intptr_t)TOP ? 1 : 0;
			break;
		case RPC_OP_ne:
			SECOND = SECOND != TOP ? 1 : 0;
			break;
		case RPC_OP_uge:
			SECOND = SECOND >= TOP ? 1 : 0;
			break;
		case RPC_OP_ugt:
			SECOND = SECOND > TOP ? 1 : 0;
			break;
		case RPC_OP_ule:
			SECOND = SECOND <= TOP ? 1 : 0;
			break;
		case RPC_OP_ult:
			SECOND = SECOND < TOP ? 1 : 0;
			break;
		default:
			__builtin_unreachable();
		}
		/* Force sign-extension in compatibility mode. */
		COMPAT_SIGN_EXTEND(SECOND);
		--self->rv_stacksz;
		break;

#ifdef RPC_TRACE_INSTRUCTIONS
	case RPC_OP_bra: {
		int16_t delta;
		delta = (int16_t)rpc_vm_pc_rdw(self);
		TRACE_INSTRUCTION("RPC_OP_bra %" PRId16 "\n", delta);
		if unlikely(!CANPOP(1))
			goto err_stack_underflow;
		--self->rv_stacksz;
		if (self->rv_stack[self->rv_stacksz] != 0)
			goto follow_jmp;
		break;

	case RPC_OP_nbra:
		delta = (int16_t)rpc_vm_pc_rdw(self);
		TRACE_INSTRUCTION("RPC_OP_nbra %" PRId16 "\n", delta);
		if unlikely(!CANPOP(1))
			goto err_stack_underflow;
		--self->rv_stacksz;
		if (self->rv_stack[self->rv_stacksz] == 0)
			goto follow_jmp;
		break;

	case RPC_OP_skip:
		delta = (int16_t)rpc_vm_pc_rdw(self);
		TRACE_INSTRUCTION("RPC_OP_skip %" PRId16 "\n", delta);
follow_jmp:
		self->rv_pc += delta;   /* Adjust program counter */
		self->rv_pcbuf_siz = 0; /* Clear program text buffer */
	}	break;

#else /* RPC_TRACE_INSTRUCTIONS */

	CASE(RPC_OP_bra)
		if unlikely(!CANPOP(1))
			goto err_stack_underflow;
		--self->rv_stacksz;
		if (self->rv_stack[self->rv_stacksz] != 0)
			goto follow_jmp;
		rpc_vm_pc_rdw(self);
		break;

	CASE(RPC_OP_nbra)
		if unlikely(!CANPOP(1))
			goto err_stack_underflow;
		--self->rv_stacksz;
		if (self->rv_stack[self->rv_stacksz] == 0)
			goto follow_jmp;
		rpc_vm_pc_rdw(self);
		break;

	CASE(RPC_OP_skip) {
		int16_t delta;
follow_jmp:
		delta = (int16_t)rpc_vm_pc_rdw(self);
		self->rv_pc += delta;   /* Adjust program counter */
		self->rv_pcbuf_siz = 0; /* Clear program text buffer */
	}	break;
#endif /* !RPC_TRACE_INSTRUCTIONS */

	case RPC_OP_popreg0 ...  RPC_OP_popreg31:
		TRACE_INSTRUCTION("RPC_OP_popreg%u\n", opcode - RPC_OP_popreg0);
		rpc_vm_popreg(self, opcode - RPC_OP_popreg0);
		break;

	case RPC_OP_pushreg0 ...  RPC_OP_pushreg31:
		TRACE_INSTRUCTION("RPC_OP_pushreg%u\n", opcode - RPC_OP_pushreg0);
		rpc_vm_pushreg(self, opcode - RPC_OP_pushreg0);
		break;

	case RPC_OP_sppushreg0 ...  RPC_OP_sppushreg31:
		TRACE_INSTRUCTION("RPC_OP_sppushreg%u\n", opcode - RPC_OP_sppushreg0);
		rpc_vm_pushreg2user(self, opcode - RPC_OP_sppushreg0);
		break;

	case RPC_OP_popregx: {
		uintptr_t regno = rpc_vm_pc_rduleb128(self);
		TRACE_INSTRUCTION("RPC_OP_popregx %" PRIuPTR "\n", regno);
		rpc_vm_popreg(self, regno);
	}	break;

	case RPC_OP_pushregx: {
		uintptr_t regno = rpc_vm_pc_rduleb128(self);
		TRACE_INSTRUCTION("RPC_OP_pushregx %" PRIuPTR "\n", regno);
		rpc_vm_pushreg(self, regno);
	}	break;

	case RPC_OP_sppushregx: {
		uintptr_t regno = rpc_vm_pc_rduleb128(self);
		TRACE_INSTRUCTION("RPC_OP_sppushregx %" PRIuPTR "\n", regno);
		rpc_vm_pushreg2user(self, regno);
	}	break;

	CASE(RPC_OP_deref) {
		size_t siz = rpc_vm_addrsize(self);
		if unlikely(!CANPOP(1))
			goto err_stack_underflow;
		rpc_vm_rdmem(self, TOP, &TOP, siz);
	}	break;

	case RPC_OP_deref_size: {
		uint8_t siz = rpc_vm_pc_rdb(self);
		TRACE_INSTRUCTION("RPC_OP_deref_size %" PRIu8 "\n", siz);
		if unlikely(!CANPOP(1))
			goto err_stack_underflow;
		switch (siz) {
		case 1:
		case 2:
		case 4:
			break;

#if SIZEOF_POINTER >= 8
		case 8:
#ifdef __ARCH_HAVE_COMPAT
			if (rpc_vm_addrsize(self) >= 8)
				break;
			ATTR_FALLTHROUGH
#else /* __ARCH_HAVE_COMPAT */
			break;
#endif /* !__ARCH_HAVE_COMPAT */
#endif /* SIZEOF_POINTER >= 8 */

		default:
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_RPC_PROGRAM_BAD_WORD_SIZE,
			      siz);
		}
		rpc_vm_rdmem(self, TOP, &TOP, siz);
	}	break;

	CASE(RPC_OP_write) {
		size_t siz = rpc_vm_addrsize(self);
		uintptr_t addr, val;
		if unlikely(!CANPOP(2))
			goto err_stack_underflow;
		addr = POP();
		val  = POP();
		rpc_vm_wrmem(self, addr, &val, siz);
	}	break;

	case RPC_OP_write_size: {
		uint8_t siz = rpc_vm_pc_rdb(self);
		TRACE_INSTRUCTION("RPC_OP_write_size %" PRIu8 "\n", siz);
		uintptr_t addr, val;
		if unlikely(!CANPOP(2))
			goto err_stack_underflow;
		switch (siz) {
		case 1:
		case 2:
		case 4:
			break;

#if SIZEOF_POINTER >= 8
		case 8:
#ifdef __ARCH_HAVE_COMPAT
			if (rpc_vm_addrsize(self) >= 8)
				break;
			ATTR_FALLTHROUGH
#else /* __ARCH_HAVE_COMPAT */
			break;
#endif /* !__ARCH_HAVE_COMPAT */
#endif /* SIZEOF_POINTER >= 8 */

		default:
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_RPC_PROGRAM_BAD_WORD_SIZE,
			      siz);
		}
		addr = POP();
		val  = POP();
		rpc_vm_wrmem(self, addr, &val, siz);
	}	break;

	CASE(RPC_OP_nop)
		break;

	case RPC_OP_widenz: {
		uint8_t siz = rpc_vm_pc_rdb(self);
		uintptr_t value;
		TRACE_INSTRUCTION("RPC_OP_widenz %" PRIu8 "\n", siz);
		if unlikely(!CANPOP(1))
			goto err_stack_underflow;
		value = TOP;
		switch (siz) {
		case 1:
			value = (uintptr_t)(uint8_t)value;
			break;
		case 2:
			value = (uintptr_t)(uint16_t)value;
			break;

#if SIZEOF_POINTER >= 8
		case 4:
#ifdef __ARCH_HAVE_COMPAT
			if (rpc_vm_addrsize(self) >= 8) {
				value = (uintptr_t)(uint32_t)value;
				break;
			}
			ATTR_FALLTHROUGH
#else /* __ARCH_HAVE_COMPAT */
			value = (uintptr_t)(uint32_t)value;
			break;
#endif /* !__ARCH_HAVE_COMPAT */
#endif /* SIZEOF_POINTER >= 8 */

		default:
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_RPC_PROGRAM_BAD_WIDTH,
			      siz);
		}
		TOP = value;
	}	break;

	case RPC_OP_widens: {
		uint8_t siz = rpc_vm_pc_rdb(self);
		uintptr_t value;
		TRACE_INSTRUCTION("RPC_OP_widens %" PRIu8 "\n", siz);
		if unlikely(!CANPOP(1))
			goto err_stack_underflow;
		value = TOP;
		switch (siz) {
		case 1:
			value = (uintptr_t)(intptr_t)(int8_t)(uint8_t)value;
			break;
		case 2:
			value = (uintptr_t)(intptr_t)(int16_t)(uint16_t)value;
			break;

#if SIZEOF_POINTER >= 8
		case 4:
#ifdef __ARCH_HAVE_COMPAT
			if (rpc_vm_addrsize(self) >= 8) {
				value = (uintptr_t)(intptr_t)(int32_t)(uint32_t)value;
				break;
			}
			ATTR_FALLTHROUGH
#else /* __ARCH_HAVE_COMPAT */
			value = (uintptr_t)(intptr_t)(int32_t)(uint32_t)value;
			break;
#endif /* !__ARCH_HAVE_COMPAT */
#endif /* SIZEOF_POINTER >= 8 */

		default:
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_RPC_PROGRAM_BAD_WIDTH,
			      siz);
		}
		TOP = value;
	}	break;






	/************************************************************************/
	/* Special-purpose instructions                                         */
	/************************************************************************/
	CASE(RPC_OP_push_reason)
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
		PUSH(self->rv_reason);
		break;

	CASE(RPC_OP_push_dorestart)
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
		PUSH(self->rv_reason == _RPC_REASONCTX_SYSCALL ? 1 : 0);
		break;

	CASE(RPC_OP_push_issyscall)
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
		PUSH((self->rv_reason == _RPC_REASONCTX_SYSCALL ||
		      self->rv_reason == _RPC_REASONCTX_SYSINT)
		     ? 1
		     : 0);
		break;

	case RPC_OP_push_sc_info: {
		uint8_t index = rpc_vm_pc_rdb(self);
		TRACE_INSTRUCTION("RPC_OP_push_sc_info %" PRIu8 "\n", index);
		if unlikely(index >= sizeof(struct rpc_syscall_info) / sizeof(void *)) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_RPC_PROGRAM_BAD_SYSINFO_WORD,
			      index);
		}
		if unlikely(self->rv_reason != _RPC_REASONCTX_SYSCALL &&
		            self->rv_reason != _RPC_REASONCTX_SYSINT)
			goto err_no_syscall_info;
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
		PUSH(((uintptr_t *)self->rv_sc_info)[index]);
		/* Force sign-extension in compatibility mode. */
		COMPAT_SIGN_EXTEND(TOP);
	}	break;

	CASE(RPC_OP_sppush_sc_info) {
		struct rpc_syscall_info const *info = self->rv_sc_info;
		if unlikely(self->rv_reason != _RPC_REASONCTX_SYSCALL &&
		            self->rv_reason != _RPC_REASONCTX_SYSINT)
			goto err_no_syscall_info;
#ifdef __ARCH_HAVE_COMPAT
		if (ucpustate_iscompat(&self->rv_cpu)) {
			unsigned int i;
			struct compat_rpc_syscall_info compat_sc_info;
			compat_sc_info.rsi_flags = (compat_uintptr_t)info->rsi_flags;
			compat_sc_info.rsi_sysno = (compat_uintptr_t)info->rsi_sysno;
			for (i = 0; i < lengthof(compat_sc_info.rsi_regs); ++i)
				compat_sc_info.rsi_regs[i] = (compat_uintptr_t)info->rsi_regs[i];
			rpc_vm_push2user(self, &compat_sc_info, sizeof(compat_sc_info));
		} else
#endif /* __ARCH_HAVE_COMPAT */
		{
			rpc_vm_push2user(self, info, sizeof(struct rpc_syscall_info));
		}
	}	break;

	case RPC_OP_push_param: {
		uint8_t index = rpc_vm_pc_rdb(self);
		TRACE_INSTRUCTION("RPC_OP_push_param %" PRIu8 "\n", index);
		if unlikely(index >= self->rv_rpc->pr_user.pur_argc) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_RPC_PROGRAM_PARAM_INDEX_OOB,
			      index);
		}
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
		PUSH((uintptr_t)self->rv_rpc->pr_user.pur_argv[index]);
		/* Force sign-extension in compatibility mode. */
		COMPAT_SIGN_EXTEND(TOP);
	}	break;

	CASE(RPC_OP_futex_wake) {
		uintptr_t addr, count;
		struct rpc_futex *ftx;
		if unlikely(!CANPOP(2))
			goto err_stack_underflow;
		count = POP();
		addr  = POP();
		/* Lookup a futex controller at the given address. */
		ftx = rpc_mem_getfutex(&self->rv_mem, (USER UNCHECKED void *)addr);
		if (ftx) {
			/* If a futex object exists (as indicative of some thread currently
			 * being connected to ) */
			if (OVERFLOW_UADD(ftx->rf_wake, count, &ftx->rf_wake))
				ftx->rf_wake = (size_t)-1;
		}
	}	break;

	CASE(RPC_OP_sigblock) {
		signo_t signo;
		if unlikely(!CANPOP(1))
			goto err_stack_underflow;
		signo = (signo_t)TOP;
		if unlikely(!sigvalid(signo)) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO,
			      signo);
		}
		if unlikely(signo == SIGKILL || signo == SIGSTOP)
			break; /* Don't allow masking of these signals! */
		if (!(self->rv_flags & RPC_VM_HAVESIGMASK)) {
			sigemptyset(&self->rv_sigmask);
			self->rv_flags |= RPC_VM_HAVESIGMASK;
		}
		sigaddset(&self->rv_sigmask, signo);
	}	break;

	case RPC_OP_push_sigmask_word: {
		uint8_t index = rpc_vm_pc_rdb(self);
		ulongptr_t sigmask_word;
		TRACE_INSTRUCTION("RPC_OP_push_sigmask_word %" PRIu8 "\n", index);
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
#if defined(__ARCH_HAVE_COMPAT) && (__ARCH_COMPAT_SIZEOF_POINTER != __SIZEOF_POINTER__)
		if (ucpustate_iscompat(&self->rv_cpu)) {
#if __ARCH_COMPAT_SIZEOF_POINTER == (__SIZEOF_POINTER__ / 2)
			sigmask_word = sigmask_getmask_word_s(index >> 1);
			if (index & 1)
				sigmask_word >>= ((__SIZEOF_POINTER__ / 2) * NBBY);
			/* Force sign-extension in compatibility mode. */
			sigmask_word = (uintptr_t)(intptr_t)(compat_longptr_t)(compat_ulongptr_t)sigmask_word;
#else /* ... */
#error "Unsupported configuration"
#endif /* !... */
		} else
#endif /* __ARCH_HAVE_COMPAT */
		{
			sigmask_word = sigmask_getmask_word_s(index);
		}
		PUSH(sigmask_word);
	}	break;

	case RPC_OP_sppush_sigmask: {
		uint16_t sigsetsz = rpc_vm_pc_rdw(self);
		TRACE_INSTRUCTION("RPC_OP_sppush_sigmask %" PRIu16 "\n", sigsetsz);
		rpc_vm_push2user_sigset(self, sigsetsz);
	}	break;

	CASE(RPC_OP_push_signal)
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
		PUSH(_RPC_GETSIGNO(self->rv_rpc->pr_flags));
		break;





	/************************************************************************/
	/* Arch-specific instructions                                           */
	/************************************************************************/
#ifdef __x86_64__
	CASE(RPC_OP_x86_push_is32bit)
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
		PUSH(ucpustate_iscompat(&self->rv_cpu) ? 1 : 0);
		break;

	CASE(RPC_OP_386_pushreg_fsbase)
		if unlikely(!ucpustate_is32bit(&self->rv_cpu))
			goto err_illegal_instruction;
#define WANT_err_illegal_instruction
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
		/* Force sign-extension in compatibility mode. */
		PUSH((u64)(s64)(s32)(u32)self->rv_cpu.ucs_sgbase.sg_fsbase);
		break;

	CASE(RPC_OP_386_pushreg_gsbase)
		if unlikely(!ucpustate_is32bit(&self->rv_cpu))
			goto err_illegal_instruction;
#define WANT_err_illegal_instruction
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
		/* Force sign-extension in compatibility mode. */
		PUSH((u64)(s64)(s32)(u32)self->rv_cpu.ucs_sgbase.sg_gsbase);
		break;

	CASE(RPC_OP_386_popreg_fsbase)
		if unlikely(!ucpustate_is32bit(&self->rv_cpu))
			goto err_illegal_instruction;
#define WANT_err_illegal_instruction
		if unlikely(!CANPOP(1))
			goto err_stack_underflow;
		self->rv_cpu.ucs_sgbase.sg_fsbase = POP();
		break;

	CASE(RPC_OP_386_popreg_gsbase)
		if unlikely(!ucpustate_is32bit(&self->rv_cpu))
			goto err_illegal_instruction;
#define WANT_err_illegal_instruction
		if unlikely(!CANPOP(1))
			goto err_stack_underflow;
		self->rv_cpu.ucs_sgbase.sg_gsbase = POP();
		break;
#elif defined(__i386__)
	CASE(RPC_OP_x86_push_is32bit)
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
		PUSH(1);
		break;

	CASE(RPC_OP_386_pushreg_fsbase)
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
		PUSH(self->rv_flags & RPC_VM_HAVE_FSBASE ? self->rv_386_fsbase
		                                         : x86_get_user_fsbase());
		break;

	CASE(RPC_OP_386_pushreg_gsbase)
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
		PUSH(self->rv_flags & RPC_VM_HAVE_GSBASE ? self->rv_386_gsbase
		                                         : x86_get_user_gsbase());
		break;

	CASE(RPC_OP_386_popreg_fsbase)
		if unlikely(!CANPOP(1))
			goto err_stack_underflow;
		self->rv_flags |= RPC_VM_HAVE_FSBASE;
		self->rv_386_fsbase = POP();
		break;

	CASE(RPC_OP_386_popreg_gsbase)
		if unlikely(!CANPOP(1))
			goto err_stack_underflow;
		self->rv_flags |= RPC_VM_HAVE_GSBASE;
		self->rv_386_gsbase = POP();
		break;
#elif defined(__arm__)
	CASE(RPC_OP_arm_pushreg_tlsbase)
		if unlikely(!CANPUSH(1))
			goto err_stack_overflow;
		PUSH(self->rv_flags & RPC_VM_HAVE_TLSBASE ? self->rv_arm_tlsbase
		                                          : (uintptr_t)arm_get_user_tlsbase());
		break;

	CASE(RPC_OP_arm_popreg_tlsbase)
		if unlikely(!CANPOP(1))
			goto err_stack_underflow;
		self->rv_flags |= RPC_VM_HAVE_TLSBASE;
		self->rv_arm_tlsbase = POP();
		break;
#else /* ... */
	/* No arch-specific instructions for this platform... */
#endif /* !... */





	default:
		/* Unknown instruction. */
#ifdef WANT_err_illegal_instruction
#undef WANT_err_illegal_instruction
err_illegal_instruction:
#endif /* WANT_err_illegal_instruction */
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_RPC_PROGRAM_INSTRUCTION,
		      opcode);
		break;
#undef TRACE_INSTRUCTION
#undef CASE
	}
	return true;
err_stack_overflow:
	THROW(E_ILLEGAL_RESOURCE_LIMIT_EXCEEDED,
	      E_ILLEGAL_OPERATION_CONTEXT_RPC_PROGRAM_STACK_OVERFLOW);
err_stack_underflow:
	THROW(E_INVALID_OPERATION,
	      E_ILLEGAL_OPERATION_CONTEXT_RPC_PROGRAM_STACK_UNDERFLOW);
err_no_syscall_info:
	THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
	      E_INVALID_ARGUMENT_CONTEXT_RPC_PROGRAM_NO_SYSINFO,
	      opcode);
#undef COMPAT_SIGN_EXTEND
}

#undef THIRD
#undef SECOND
#undef FIRST
#undef TOP
#undef PUSH
#undef POP
#undef CANPOP
#undef CANPUSH







/* Execute a user-space RPC program
 * @param: reason:  One of `_RPC_REASONCTX_ASYNC', `_RPC_REASONCTX_SYNC', `_RPC_REASONCTX_SYSCALL' or `_RPC_REASONCTX_SYSINT'
 * @param: sc_info: [valid_if(reason == _RPC_REASONCTX_SYSCALL || reason == _RPC_REASONCTX_SYSINT)]
 *                  The  system call that was active at the  time of the RPC being handled. Note that
 *                  this system call only has to be restarted when `reason == _RPC_REASONCTX_SYSCALL'
 * @return: * :   The updated CPU state.
 * @return: NULL: The RPC was canceled before it could be fully executed.
 * @throw: E_INTERRUPT_USER_RPC: Must serve other RPCs first, then try to serve this one again.
 * @throw: * : RPCs serving failed, simply `decref(&rpc->pr_user)'; message passing is already done. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) rpc_cpustate_t *FCALL
task_userrpc_runprogram(rpc_cpustate_t *__restrict state,
                        struct pending_rpc *__restrict rpc,
                        unsigned int reason,
                        struct rpc_syscall_info const *sc_info)
		THROWS(E_INTERRUPT_USER_RPC, ...) {
	struct rpc_vm vm;
#ifdef __ARCH_HAVE_COMPAT
	struct unwind_getreg_compat_data compat_getreg;
	struct unwind_setreg_compat_data compat_setreg;
#endif /* __ARCH_HAVE_COMPAT */
	assert(reason == _RPC_REASONCTX_ASYNC ||
	       reason == _RPC_REASONCTX_SYNC ||
	       reason == _RPC_REASONCTX_SYSCALL ||
	       reason == _RPC_REASONCTX_SYSINT);
	assert(icpustate_isuser(state));
	assert(rpc->pr_user.pur_status == PENDING_USER_RPC_STATUS_PENDING ||
	       rpc->pr_user.pur_status == PENDING_USER_RPC_STATUS_CANCELED);

	/* Quick check if the RPC has already been canceled. */
	if unlikely(rpc->pr_user.pur_status != PENDING_USER_RPC_STATUS_PENDING) {
		state = NULL;
		goto done_nofini;
	}

	/* Initialize the RPC program VM */
	rpc_mem_init(&vm.rv_mem);
#ifdef ICPUSTATE_IS_UCPUSTATE
	vm.rv_cpu = *state;
#else /* ICPUSTATE_IS_UCPUSTATE */
	icpustate_to_ucpustate(state, &vm.rv_cpu);
#endif /* !ICPUSTATE_IS_UCPUSTATE */
	vm.rv_rpc       = rpc;
	vm.rv_reason    = reason;
	vm.rv_sc_info   = sc_info;
	vm.rv_flags     = RPC_VM_NORMAL;
	vm.rv_pc        = (USER CHECKED byte_t *)rpc->pr_user.pur_prog;
	vm.rv_pcbuf_siz = 0;

	/* As  per specs, RPC programs start execution with 1 element on-
	 * stack that is indicative of the need to restart a system call. */
	vm.rv_stacksz  = 1;
	vm.rv_stack[0] = reason == _RPC_REASONCTX_SYSCALL ? 1 : 0;

#ifdef __ARCH_HAVE_COMPAT
	/* Initialize register getter/setter based on compatibility mode setting
	 * of  the target process. This way (as documented), RPC programs always
	 * execute in the architecture-context of the thread they were sent to. */
	if (icpustate_iscompat(state)) {
		unwind_getreg_compat_data_init(&compat_getreg, &rpc_vm_getreg_impl, &vm);
		unwind_setreg_compat_data_init(&compat_setreg, &rpc_vm_setreg_impl, &vm);
		vm.rv_unwind_getreg     = &unwind_getreg_compat;
		vm.rv_unwind_getreg_arg = &compat_getreg;
		vm.rv_unwind_setreg     = &unwind_setreg_compat;
		vm.rv_unwind_setreg_arg = &compat_setreg;
	} else {
		vm.rv_unwind_getreg     = &rpc_vm_getreg_impl;
		vm.rv_unwind_getreg_arg = &vm;
		vm.rv_unwind_setreg     = &rpc_vm_setreg_impl;
		vm.rv_unwind_setreg_arg = &vm;
	}
#endif /* __ARCH_HAVE_COMPAT */

	TRY {
		/* Execute the RPC program VM */
		for (;;) {
			/* Check if the RPC should be canceled. */
			if (ATOMIC_READ(rpc->pr_user.pur_status) != PENDING_USER_RPC_STATUS_PENDING) {
				assert(rpc->pr_user.pur_status == PENDING_USER_RPC_STATUS_CANCELED);
				state = NULL;
				goto done;
			}

			/* Execute a single instruction. */
			if (!rpc_vm_instr(&vm))
				break; /* `RPC_OP_ret' instruction was reached. */

			/* To  ensure that  RPC programs  with infinite  loops don't cause
			 * the kernel to hang itself, a call to `task_serve_with_sigmask',
			 * with a signal mask that is  masking all signals except for  the
			 * mandatory `SIGKILL' and `SIGSTOP'  is made after executing  any
			 * given instruction. */
			task_serve_with_sigmask(&sigmask_full);
		}

		/* Write-back the register state (and verify that all values are allowed) */
#if defined(__i386__) || defined(__x86_64__)
		cpustate_verify_userpflags(icpustate_getpflags(state),
		                           ucpustate_getpflags(&vm.rv_cpu),
		                           cred_allow_eflags_modify_mask());
#ifndef __x86_64__
#ifndef __I386_NO_VM86
		if (!(ucpustate_getpflags(&vm.rv_cpu) & EFLAGS_VM))
#endif /* !__I386_NO_VM86 */
#endif /* !__x86_64__ */
		{
			/* Validate segment register indices before actually restoring them. */
			cpustate_verify_usercs(ucpustate_getcs(&vm.rv_cpu));
			cpustate_verify_userss(ucpustate_getss(&vm.rv_cpu));
			cpustate_verify_usergs(ucpustate_getgs(&vm.rv_cpu));
			cpustate_verify_userfs(ucpustate_getfs(&vm.rv_cpu));
			cpustate_verify_useres(ucpustate_getes(&vm.rv_cpu));
			cpustate_verify_userds(ucpustate_getds(&vm.rv_cpu));
		}

		/* NOTE: Even though some of the stuff  below is still able to  throw
		 *       exceptions, this _has_ to be the point of no return in terms
		 *       of cancelability, since from this point forth, we have to do
		 *       stuff that cannot be undone. */

		/* Indicate that the RPC was successfully executed. */
		if (!ATOMIC_CMPXCH(rpc->pr_user.pur_status,
		                   PENDING_USER_RPC_STATUS_PENDING,
		                   PENDING_USER_RPC_STATUS_COMPLETE)) {
			assert(rpc->pr_user.pur_status == PENDING_USER_RPC_STATUS_CANCELED);
			state = NULL;
			goto done;
		}

		/* Signal anyone waiting for the RPC to complete to wake up. */
		sig_broadcast(&rpc->pr_user.pur_stchng);

		/* Write-back memory modifications. */
		rpc_mem_writeback(&vm.rv_mem);

		/* Check for special restore options. */
		if (vm.rv_flags & (RPC_VM_HAVESIGMASK |
#ifdef CONFIG_HAVE_FPU
		                   RPC_VM_HAVEFPU_MODIFIED |
#endif /* CONFIG_HAVE_FPU */
#if defined(__i386__) && !defined(__x86_64__)
		                   RPC_VM_HAVE_FSBASE |
		                   RPC_VM_HAVE_GSBASE |
#endif /* __i386__ && !__x86_64__ */
		                   0)) {

			/* Mask additional signals */
			if (vm.rv_flags & RPC_VM_HAVESIGMASK) {
				assert(!sigismember(&vm.rv_sigmask, SIGKILL));
				assert(!sigismember(&vm.rv_sigmask, SIGSTOP));
				sigmask_blockmask(&vm.rv_sigmask);
			}

#ifdef CONFIG_HAVE_FPU
			/* Write-back FPU register modifications and masked signals. */
			if (vm.rv_flags & RPC_VM_HAVEFPU_MODIFIED)
				fpustate_loadfrom(&vm.rv_fpu);
#endif /* CONFIG_HAVE_FPU */

#if defined(__i386__) && !defined(__x86_64__)
			if (vm.rv_flags & RPC_VM_HAVE_FSBASE)
				x86_set_user_fsbase(vm.rv_386_fsbase);
			if (vm.rv_flags & RPC_VM_HAVE_GSBASE)
				x86_set_user_gsbase(vm.rv_386_gsbase);
#endif /* __i386__ && !__x86_64__ */
		}

		/* Write-back register modifications. */
#ifndef __x86_64__
#ifndef __I386_NO_VM86
		if (ucpustate_getpflags(&vm.rv_cpu) & EFLAGS_VM) {
			state->ics_irregs_v.ir_es = ucpustate_getes(&vm.rv_cpu);
			state->ics_irregs_v.ir_ds = ucpustate_getds(&vm.rv_cpu);
			state->ics_irregs_v.ir_fs = ucpustate_getfs(&vm.rv_cpu);
			state->ics_irregs_v.ir_gs = ucpustate_getgs(&vm.rv_cpu);
		} else
#endif /* !__I386_NO_VM86 */
#endif /* !__x86_64__ */
		{
			icpustate_setgs_novm86(state, ucpustate_getgs(&vm.rv_cpu));
			icpustate_setfs_novm86(state, ucpustate_getfs(&vm.rv_cpu));
			icpustate_setes_novm86(state, ucpustate_getes(&vm.rv_cpu));
			icpustate_setds_novm86(state, ucpustate_getds(&vm.rv_cpu));
		}
		icpustate_setcs(state, ucpustate_getcs(&vm.rv_cpu));
		icpustate_setuserss(state, ucpustate_getss(&vm.rv_cpu));
		gpregs_to_gpregsnsp(&vm.rv_cpu.ucs_gpregs, &state->ics_gpregs);
		{
			union x86_user_eflags_mask_union word;
			/* Mask %Pflags, as specified by `x86_user_eflags_mask' */
			word.uem_word = atomic64_read(&x86_user_eflags_mask);
			ucpustate_mskpflags(&vm.rv_cpu, word.uem_mask, word.uem_flag);
		}
		icpustate_setpflags(state, ucpustate_getpflags(&vm.rv_cpu));
		icpustate_setpip(state, ucpustate_getpip(&vm.rv_cpu));
		icpustate_setuserpsp(state, ucpustate_getpsp(&vm.rv_cpu));
#elif defined(__arm__)
		cpustate_verify_apsr(icpustate_getcpsr(state),
		                     ucpustate_getcpsr(&vm.rv_cpu));

		/* NOTE: Even though some of the stuff  below is still able to  throw
		 *       exceptions, this _has_ to be the point of no return in terms
		 *       of cancelability, since from this point forth, we have to do
		 *       stuff that cannot be undone. */

		/* Indicate that the RPC was successfully executed. */
		if (!ATOMIC_CMPXCH(rpc->pr_user.pur_status,
		                   PENDING_USER_RPC_STATUS_PENDING,
		                   PENDING_USER_RPC_STATUS_COMPLETE)) {
			assert(rpc->pr_user.pur_status == PENDING_USER_RPC_STATUS_CANCELED);
			state = NULL;
			goto done;
		}

		/* Signal anyone waiting for the RPC to complete to wake up. */
		sig_broadcast(&rpc->pr_user.pur_stchng);

		/* Write-back memory modifications. */
		rpc_mem_writeback(&vm.rv_mem);

		/* Check for special restore options. */
		if (vm.rv_flags & (RPC_VM_HAVESIGMASK |
		                   RPC_VM_HAVE_TLSBASE |
#ifdef CONFIG_HAVE_FPU
		                   RPC_VM_HAVEFPU_MODIFIED |
#endif /* CONFIG_HAVE_FPU */
		                   0)) {

			/* Mask additional signals */
			if (vm.rv_flags & RPC_VM_HAVESIGMASK) {
				assert(!sigismember(&vm.rv_sigmask, SIGKILL));
				assert(!sigismember(&vm.rv_sigmask, SIGSTOP));
				sigmask_blockmask(&vm.rv_sigmask);
			}

#ifdef CONFIG_HAVE_FPU
			/* Write-back FPU register modifications and masked signals. */
			if (vm.rv_flags & RPC_VM_HAVEFPU_MODIFIED)
				fpustate_loadfrom(&vm.rv_fpu);
#endif /* CONFIG_HAVE_FPU */

			if (vm.rv_flags & RPC_VM_HAVE_TLSBASE)
				arm_set_user_tlsbase((void *)vm.rv_arm_tlsbase);
		}

		/* Write-back register modifications. */
		*state = vm.rv_cpu;
#else /* ... */
#error "Unsupported arch"
#endif /* !... */

	} EXCEPT {
		struct exception_info *tls = except_info();
		rpc_vm_fini(&vm);
		if (tls->ei_code == EXCEPT_CODEOF(E_INTERRUPT_USER_RPC))
			RETHROW(); /* Handled by the caller (causes the RPC to be re-attempted later) */
		if (EXCEPTCLASS_ISRTLPRIORITY(tls->ei_class)) {
			/* Too important to discard. Instead, cancel the RPC and rethrow */
			if (ATOMIC_CMPXCH(rpc->pr_user.pur_status,
			                  PENDING_USER_RPC_STATUS_PENDING,
			                  PENDING_USER_RPC_STATUS_CANCELED)) {
				sig_broadcast(&rpc->pr_user.pur_stchng);
			} else {
				assert(rpc->pr_user.pur_status == PENDING_USER_RPC_STATUS_CANCELED);
			}
			RETHROW();
		}

		/* Propagate the exception back to the sender. */
		if (isshared(&rpc->pr_user) &&
		    ATOMIC_CMPXCH(rpc->pr_user.pur_status,
		                  PENDING_USER_RPC_STATUS_PENDING,
		                  PENDING_USER_RPC_STATUS_ERROR)) {
			rpc->pr_user.pur_error.e_code = tls->ei_code;
			memcpy(&rpc->pr_user.pur_error.e_args, &tls->ei_data.e_args,
			       sizeof(union exception_data_pointers));
			sig_broadcast(&rpc->pr_user.pur_stchng);
		} else {
			/* If no one's there to receive the error, dump it to the system log */
			except_printf("executing async user RPC program");
		}
		goto done_nofini;
	}
done:
	rpc_vm_fini(&vm);
done_nofini:
	return state;
}








/************************************************************************/
/* RPC related system calls                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_RPC_SERVE
DEFINE_SYSCALL0(errno_t, rpc_serve) {
	/* Somewhat similar to `rpc_serve_sysret(2)', however this one does  a
	 * hard check for pending RPCs, including any that can only be handled
	 * in  the context of a cancellation-point system call (which this one
	 * is marked as being)
	 *
	 * s.a. `pthread_testcancel(3)' */
	task_serve();
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_RPC_SERVE */

#ifdef __ARCH_WANT_SYSCALL_RPC_SERVE_SYSRET
DEFINE_SYSCALL0(errno_t, rpc_serve_sysret) {
	/* This system call is supposed to check for pending async (aka. sysret) RPCs,
	 * mainly  for the purpose  of updating the  calling thread userprocmask's (if
	 * that thread is using one) set of  pending signals, as well as handling  any
	 * that have become unmasked.
	 *
	 * This sort of behavior is needed for when the userprocmask just became  less
	 * restrictive while there are pending RPCs (or posix signals) that have  just
	 * become unmasked. In this situation, the kernel must be told that the caller
	 * is now ready to service the related RPC programs (or posix signals),  which
	 * is exactly what this system call does, and is there for.
	 *
	 * s.a. `chkuserprocmask(3)' */
	userexcept_sysret_inject_self();
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_RPC_SERVE_SYSRET */

DECL_END

#ifndef __INTELLISENSE__
#ifdef __ARCH_WANT_SYSCALL_RPC_SCHEDULE
#define DEFINE_sys_rpc_schedule
#include "rpc-program-schedule.c.inl"
#endif /* __ARCH_WANT_SYSCALL_RPC_SCHEDULE */
#ifdef __ARCH_WANT_COMPAT_SYSCALL_RPC_SCHEDULE
#define DEFINE_compat_sys_rpc_schedule
#include "rpc-program-schedule.c.inl"
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RPC_SCHEDULE */
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_SRC_SCHED_RPC_PROGRAM_C */
