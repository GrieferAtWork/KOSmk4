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
#ifndef GUARD_LIBC_USER_CTHREADS_C
#define GUARD_LIBC_USER_CTHREADS_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/atomic.h>
#include <hybrid/host.h>

#include <assert.h>
#include <err.h>
#include <malloc.h>
#include <pthread.h>
#include <string.h>

#include <libiberty.h>

#include "../libc/dl.h"
#include "cthreads.h"

DECL_BEGIN

/*[[[head:libc_cond_signal,hash:CRC-32=0xe00e4fe3]]]*/
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") int
NOTHROW_NCX(LIBCCALL libc_cond_signal)(condition_t self)
/*[[[body:libc_cond_signal]]]*/
/*AUTO*/{
	(void)self;
	CRT_UNIMPLEMENTEDF("cond_signal(self: %p)", self); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_cond_signal]]]*/

/*[[[head:libc_cond_broadcast,hash:CRC-32=0xf93317c3]]]*/
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") void
NOTHROW_NCX(LIBCCALL libc_cond_broadcast)(condition_t self)
/*[[[body:libc_cond_broadcast]]]*/
/*AUTO*/{
	(void)self;
	CRT_UNIMPLEMENTEDF("cond_broadcast(self: %p)", self); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_cond_broadcast]]]*/

/*[[[head:libc_condition_wait,hash:CRC-32=0x2c0bb692]]]*/
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") void
NOTHROW_NCX(LIBCCALL libc_condition_wait)(condition_t self,
                                          mutex_t mutex)
/*[[[body:libc_condition_wait]]]*/
/*AUTO*/{
	(void)self;
	(void)mutex;
	CRT_UNIMPLEMENTEDF("condition_wait(self: %p, mutex: %p)", self, mutex); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_condition_wait]]]*/


/*[[[head:libc_condition_implies,hash:CRC-32=0x16aae42d]]]*/
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") void
NOTHROW_NCX(LIBCCALL libc_condition_implies)(condition_t implicator,
                                             condition_t implicatand)
/*[[[body:libc_condition_implies]]]*/
/*AUTO*/{
	(void)implicator;
	(void)implicatand;
	CRT_UNIMPLEMENTEDF("condition_implies(implicator: %p, implicatand: %p)", implicator, implicatand); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_condition_implies]]]*/

/*[[[head:libc_condition_unimplies,hash:CRC-32=0x5166a61d]]]*/
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") void
NOTHROW_NCX(LIBCCALL libc_condition_unimplies)(condition_t implicator,
                                               condition_t implicatand)
/*[[[body:libc_condition_unimplies]]]*/
/*AUTO*/{
	(void)implicator;
	(void)implicatand;
	CRT_UNIMPLEMENTEDF("condition_unimplies(implicator: %p, implicatand: %p)", implicator, implicatand); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_condition_unimplies]]]*/


/* Define `cthread_stack_mask' such that our `cthread_sp(3)' works correctly. */
#ifdef __ARCH_STACK_GROWS_UPWARDS
/*#define ur_cthread_ptr(sp) (*(struct ur_cthread **)((sp) & cthread_stack_mask))*/
PUBLIC ATTR_SECTION(".data.crt.compat.hurd.cthreads") vm_offset_t cthread_stack_mask = (vm_offset_t)-1;
#define CTHREAD_SP_OFFSET 0
#else /* __ARCH_STACK_GROWS_UPWARDS */
/*#define ur_cthread_ptr(sp) (*(struct ur_cthread **)(((sp) | cthread_stack_mask) + 1 - sizeof(struct ur_cthread **)))*/
PUBLIC ATTR_SECTION(".data.crt.compat.hurd.cthreads") vm_offset_t cthread_stack_mask = 0;
#define CTHREAD_SP_OFFSET (sizeof(struct ur_cthread **) - 1)
#endif /* !__ARCH_STACK_GROWS_UPWARDS */

struct used_ur_cthread {
	struct ur_cthread  uuc_base;  /* cthread self descriptor */
	struct ur_cthread *uuc_self;  /* [== &uuc_base] */
};

/*[[[head:libc_cthread_sp,hash:CRC-32=0x6b62e437]]]*/
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") vm_offset_t
NOTHROW_NCX(LIBCCALL libc_cthread_sp)(void)
/*[[[body:libc_cthread_sp]]]*/
{
	byte_t *result;
	struct used_ur_cthread *ur_self;
	/* Must return a pointer `struct ur_cthread **', offset by `CTHREAD_SP_OFFSET' bytes. */
	ur_self = container_of(ur_cthread_self(), struct used_ur_cthread, uuc_base);
	result  = (byte_t *)&ur_self->uuc_self;
	result += CTHREAD_SP_OFFSET;
	return (vm_offset_t)result;
}
/*[[[end:libc_cthread_sp]]]*/


PRIVATE ATTR_SECTION(".data.crt.compat.hurd.cthreads")
pthread_key_t libc_ur_cthread_self_key = PTHREAD_ONCE_KEY_NP;

/*[[[head:libc_ur_cthread_self,hash:CRC-32=0x97ca6daa]]]*/
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") ur_cthread_t
NOTHROW_NCX(LIBCCALL libc_ur_cthread_self)(void)
/*[[[body:libc_ur_cthread_self]]]*/
{
	struct used_ur_cthread *result;
	errno_t error;
	error = pthread_key_create_once_np(&libc_ur_cthread_self_key, &free);
	if unlikely(error != EOK)
		errc(1, error, "failed to allocate TLS for ur_cthread_self-emulation");
	result = (struct used_ur_cthread *)pthread_getspecific(libc_ur_cthread_self_key);
	if (result == NULL) {
		result = (struct used_ur_cthread *)xmalloc(sizeof(struct used_ur_cthread));
		result->uuc_base.next        = NULL;
		result->uuc_base.incarnation = cthread_self();
		result->uuc_self             = &result->uuc_base;
		error = pthread_setspecific(libc_ur_cthread_self_key, result);
		if unlikely(error != EOK)
			errc(1, error, "failed to assign TLS for ur_cthread_self-emulation");
	}
	return &result->uuc_base;
}
/*[[[end:libc_ur_cthread_self]]]*/

struct pthread_name_entry {
	void                         *pne_tseg;  /* [1..1] Linked tls segment */
	COMPILER_FLEXIBLE_ARRAY(char, pne_name); /* Most up-to-date name of this thread. */
};

PRIVATE ATTR_SECTION(".text.crt.compat.hurd.cthreads") struct pthread_name_entry *
NOTHROW_NCX(LIBCCALL pthread_name_entry_alloc)(pthread_t self) {
	size_t bufsize = 64;
	struct pthread_name_entry *new_entry;
	struct pthread_name_entry *entry = NULL;
	for (;;) {
		errno_t error;
		new_entry = (struct pthread_name_entry *)realloc(entry,
		                                                 offsetof(struct pthread_name_entry, pne_name) +
		                                                 (bufsize * sizeof(char)));
		if unlikely(!new_entry) {
			free(entry);
			return NULL;
		}
		entry = new_entry;
		error = pthread_getname_np(self, entry->pne_name, bufsize);
		if (error == EOK)
			break;
		if unlikely(error != ERANGE) {
			free(entry);
			libc_seterrno(error);
			return NULL;
		}
		bufsize += 64;
	}
	/* Ree unused memory. */
	bufsize = offsetof(struct pthread_name_entry, pne_name);
	bufsize += strlen(entry->pne_name) * sizeof(char);
	new_entry = (struct pthread_name_entry *)realloc(entry, bufsize);
	if likely(new_entry)
		entry = new_entry;
	entry->pne_tseg = self->pt_tls;
	return entry;
}

struct pthread_name_table {
	struct pthread_name_entry **pnt_start; /* [1..1][owned][0..n][owned] pthread name cache table base (sorted by `pne_tseg'). */
	struct pthread_name_entry **pnt_end;   /* End pointer for `pnt_start'. */
};

PRIVATE ATTR_SECTION(".text.crt.compat.hurd.cthreads") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL pthread_name_table_free)(void *self) {
	struct pthread_name_entry **iter;
	struct pthread_name_table *me = (struct pthread_name_table *)self;
	for (iter = me->pnt_start; iter < me->pnt_end; ++iter)
		free(*iter);
	free(me->pnt_start);
	free(me);
}

/* Prune threads that have been destroyed from `self' */
PRIVATE ATTR_SECTION(".text.crt.compat.hurd.cthreads") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL pthread_name_table_prune)(struct pthread_name_table *__restrict self) {
	bool has_null_entries = false;
	struct pthread_name_entry **iter;
	size_t num_item;
	for (iter = self->pnt_start; iter < self->pnt_end; ++iter) {
		struct pthread_name_entry *ent = *iter;
		if (!dlauxctrl(NULL, DLAUXCTRL_GET_TLSSEG_VALID, ent->pne_tseg)) {
			ent->pne_tseg    = NULL; /* Thread descriptor has since been destroyed. */
			has_null_entries = true;
		}
	}
	if (!has_null_entries)
		return; /* Already done! */

	/* Remove NULL-entries from the table. */
	iter = self->pnt_end;
	while (iter > self->pnt_start) {
		struct pthread_name_entry *ent;
		ent = *--iter;
		if (ent->pne_tseg != NULL)
			continue;
		/* Remove this entry */
		--self->pnt_end;
		memmovedown(iter, iter + 1,
		            (size_t)(self->pnt_end - iter),
		            sizeof(struct pthread_name_entry *));
		free(ent);
	}

	/* Free unused memory. */
	num_item = (size_t)(self->pnt_end - self->pnt_start);
	if (num_item == 0) {
		free(self->pnt_start);
		self->pnt_start = NULL;
		self->pnt_end   = NULL;
	} else {
		iter = (struct pthread_name_entry **)realloc(self->pnt_start, num_item,
		                                             sizeof(struct pthread_name_entry *));
		if likely(iter) {
			self->pnt_start = iter;
			self->pnt_end   = iter + num_item;
		}
	}
}

/* Insert `entry' into `self'.
 * - If an exiting entry already describes `entry->pne_tseg', check if said
 *   existing entry also features the same  name as is present in  `entry'.
 *   - If so, `free(entry)' and return the existing entry
 *   - If not, `free(existing_entry)', replace it with `entry' in `self', and re-return `entry'
 * - If no entry matching `entry->pne_tseg' already exists,
 *   insert `entry'  into  `self'  and  re-return  `entry'.
 * Upon error, `free(entry)' and return NULL */
PRIVATE ATTR_SECTION(".text.crt.compat.hurd.cthreads") NONNULL((1, 2)) struct pthread_name_entry *
NOTHROW_NCX(LIBCCALL pthread_name_table_remember)(struct pthread_name_table *__restrict self,
                                                  /*inherit(always)*/ struct pthread_name_entry *__restrict entry) {
	void *tseg = entry->pne_tseg;
	struct pthread_name_entry **lo, **hi;
	size_t pos, oldsize, newsize;
	lo = self->pnt_start;
	hi = self->pnt_end;
	while (lo < hi) {
		struct pthread_name_entry **mid, *mident;
		mid    = lo + ((hi - lo) >> 1);
		mident = *mid;
		if (tseg < mident->pne_tseg) {
			hi = mid;
		} else if (tseg > mident->pne_tseg) {
			lo = mid + 1;
		} else {
			/* Thread already exists within the table.
			 * -> Check if its name changed, and if so: override the entry */
			if (strcmp(mident->pne_name, entry->pne_name) == 0) {
				/* Name is unchanged -> keep using `mident' */
				free(entry);
				return mident;
			} else {
				/* Name changed -> replace `mident' with `entry' */
				*mid = entry;
				free(mident);
				return entry;
			}
		}
	}

	/* Must insert a new entry into `self' (specifically, at `lo') */
	assert(lo == hi);
	pos     = (size_t)(lo - self->pnt_start);
	oldsize = (size_t)(self->pnt_end - self->pnt_start);
	newsize = oldsize + 1;
	lo      = (struct pthread_name_entry **)realloc(self->pnt_start, newsize,
	                                                sizeof(struct pthread_name_entry *));
	if unlikely(!lo)
		goto err;
	self->pnt_start = lo;
	self->pnt_end   = lo + newsize;

	/* Make space for the new entry and insert it into the list. */
	memmoveup(&lo[pos + 1], &lo[pos], oldsize - pos,
	          sizeof(struct pthread_name_entry *));
	lo[pos] = entry;
	return entry;
err:
	free(entry);
	return NULL;
}


PRIVATE ATTR_SECTION(".data.crt.compat.hurd.cthreads")
pthread_key_t libc_cthread_name_key = PTHREAD_ONCE_KEY_NP;


/*[[[head:libc_cthread_name,hash:CRC-32=0x6a3913d0]]]*/
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") ATTR_IN(1) char const *
NOTHROW_NCX(LIBCCALL libc_cthread_name)(cthread_t self)
/*[[[body:libc_cthread_name]]]*/
{
	struct pthread_name_entry *entry;
	struct pthread_name_table *table;
	errno_t error;

	/* Load the pthread name cache table. */
	error = pthread_key_create_once_np(&libc_cthread_name_key,
	                                   &pthread_name_table_free);
	if unlikely(error != EOK)
		goto set_error;
	table = (struct pthread_name_table *)pthread_getspecific(libc_cthread_name_key);
	if (table == NULL) {
		table = (struct pthread_name_table *)malloc(sizeof(struct pthread_name_table));
		if unlikely(!table)
			goto err;
		error = pthread_setspecific(libc_cthread_name_key, table);
		if unlikely(error != EOK) {
			free(table);
			goto set_error;
		}
	}

	/* Prune any threads from the table that have since been destroyed. */
	pthread_name_table_prune(table);

	/* Allocate a new entry with the up-to-date name of `self' */
	entry = pthread_name_entry_alloc((pthread_t)self);
	if unlikely(!entry)
		goto err;

	/* Normalize the up-to-date name entry, and cache it in our thread's private name cache. */
	entry = pthread_name_table_remember(table, entry);
	if unlikely(!entry)
		goto err;

	/* Now we can simply give our caller a pointer to our own,
	 * private TLS-cache containing  the given thread's  name.
	 *
	 * The returned pointer remains valid until (at least one of):
	 * - The calling thread exits
	 * - The given thread exits, and another call is made to `cthread_name(3)'
	 */
	return entry->pne_name;
set_error:
	libc_seterrno(error);
err:
	return NULL;
}
/*[[[end:libc_cthread_name]]]*/

/*[[[head:libc_cthread_count,hash:CRC-32=0xbf5f5753]]]*/
/* >> cthread_count(3)
 * Return the number of running threads (s.a. `DLAUXCTRL_GET_MAIN_TLSSEG') */
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") int
NOTHROW_NCX(LIBCCALL libc_cthread_count)(void)
/*[[[body:libc_cthread_count]]]*/
{
	size_t result;
	result = (size_t)dlauxctrl(NULL, DLAUXCTRL_GET_TLSSEG_COUNT);
	return (int)(unsigned int)result;
}
/*[[[end:libc_cthread_count]]]*/


/* DL TLS-handle for `get_cthread_tls_segment()' */
PRIVATE ATTR_SECTION(".bss.crt.compat.hurd.cthreads")
void *cdata_handle = NULL;

struct cthread_tls_segment {
	void *ccs_cdata; /* [0..1] cdata field. */
};

PRIVATE ATTR_SECTION(".text.crt.compat.hurd.cthreads")
NONNULL((1)) struct cthread_tls_segment *
NOTHROW_NCX(LIBCCALL get_cthread_tls_segment)(pthread_t self) {
	void *result;
	void *handle = ATOMIC_READ(cdata_handle);
	/* Totally  overkill to create a new DL TLS segment for this, but <pthread.h> doesn't
	 * expose a way of accessing TLS variables of threads other than the main thread, nor
	 * could such a function even be implemented without slowing down the current impl --
	 * which makes the (correct) assumption that only the owning thread will ever  access
	 * the pthread TLS area of some given thread --
	 *
	 * As such, just go all way to the low-level stuff and create our own segment. */
	if unlikely(!handle) {
		void *real_handle;
		/* Allocate on first access. */
		handle = dltlsalloc(/* num_bytes:              */ sizeof(struct cthread_tls_segment),
		                    /* min_alignment:          */ alignof(struct cthread_tls_segment),
		                    /* template_data:          */ NULL,
		                    /* template_size:          */ 0,
		                    /* perthread_init:         */ NULL,
		                    /* perthread_fini:         */ NULL,
		                    /* perthread_callback_arg: */ NULL);
		if unlikely(!handle)
			return NULL;

		/* Remember the handle. */
		real_handle = ATOMIC_CMPXCH_VAL(cdata_handle, NULL, handle);
		if unlikely(real_handle != NULL) {
			dltlsfree(handle);
			handle = real_handle;
		}
	}

	/* Now load the segment for the given thread. */
	result = dltlsaddr2(handle, self->pt_tls);

	/* And return its address. */
	return (struct cthread_tls_segment *)result;
}

/*[[[head:libc_cthread_set_data,hash:CRC-32=0x696ab4e3]]]*/
/* >> cthread_set_data(3)
 * Set the value of a TLS variable for `self' */
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") ATTR_ACCESS_NONE(2) int
NOTHROW_NCX(LIBCCALL libc_cthread_set_data)(cthread_t self,
                                            void *value)
/*[[[body:libc_cthread_set_data]]]*/
{
	struct cthread_tls_segment *seg;
	seg = get_cthread_tls_segment((pthread_t)self);
	if unlikely(!seg)
		return -1;
	seg->ccs_cdata = value;
	return 0;
}
/*[[[end:libc_cthread_set_data]]]*/

/*[[[head:libc_cthread_data,hash:CRC-32=0xb7359d0e]]]*/
/* >> cthread_data(3)
 * Get the value of a TLS variable for `self' */
INTERN ATTR_SECTION(".text.crt.compat.hurd.cthreads") void *
NOTHROW_NCX(LIBCCALL libc_cthread_data)(cthread_t self)
/*[[[body:libc_cthread_data]]]*/
{
	struct cthread_tls_segment *seg;
	seg = get_cthread_tls_segment((pthread_t)self);
	if unlikely(!seg)
		return NULL;
	return seg->ccs_cdata;
}
/*[[[end:libc_cthread_data]]]*/

/*[[[start:exports,hash:CRC-32=0x986f97a6]]]*/
DEFINE_PUBLIC_ALIAS(cond_signal, libc_cond_signal);
DEFINE_PUBLIC_ALIAS(cond_broadcast, libc_cond_broadcast);
DEFINE_PUBLIC_ALIAS(condition_wait, libc_condition_wait);
DEFINE_PUBLIC_ALIAS(condition_implies, libc_condition_implies);
DEFINE_PUBLIC_ALIAS(condition_unimplies, libc_condition_unimplies);
DEFINE_PUBLIC_ALIAS(cthread_sp, libc_cthread_sp);
DEFINE_PUBLIC_ALIAS(ur_cthread_self, libc_ur_cthread_self);
DEFINE_PUBLIC_ALIAS(cthread_name, libc_cthread_name);
DEFINE_PUBLIC_ALIAS(cthread_count, libc_cthread_count);
DEFINE_PUBLIC_ALIAS(cthread_set_data, libc_cthread_set_data);
DEFINE_PUBLIC_ALIAS(cthread_data, libc_cthread_data);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_CTHREADS_C */
