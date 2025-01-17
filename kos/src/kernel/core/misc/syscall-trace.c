/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MISC_SYSCALL_TRACE_C
#define GUARD_KERNEL_SRC_MISC_SYSCALL_TRACE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/debugger.h>
#include <kernel/driver-param.h>
#include <kernel/handle.h>
#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/syscall-trace.h>
#include <kernel/syscall.h>
#include <sched/task.h>

#include <hybrid/sched/preemption.h>

#include <kos/aref.h>
#include <kos/except.h>

#include <assert.h>
#include <atomic.h>
#include <format-printer.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#ifndef CONFIG_NO_KERNEL_SYSCALL_TRACING
DECL_BEGIN

#ifndef CONFIG_NO_SMP
#define IF_SMP(...) __VA_ARGS__
#else /* !CONFIG_NO_SMP */
#define IF_SMP(...) /* nothing */
#endif /* CONFIG_NO_SMP */

/* SCT == SysCallTrace */
struct sct_entry {
	WEAK refcnt_t            te_refcnt;   /* Reference counter */
	syscall_trace_callback_t te_callback; /* [1..1][const] Callback. */
	void                    *te_object;   /* [1..1][lock(CLEAR_ONCE && SMP(te_inuse))] Associated object. */
	uintptr_half_t           te_obtype;   /* [const] Associated object type. */
#ifndef CONFIG_NO_SMP
	uintptr_half_t           te_inuse;    /* # of CPUs using `te_object' right now. */
#endif /* !CONFIG_NO_SMP */
};
DEFINE_REFCNT_FUNCTIONS(struct sct_entry, te_refcnt, kfree)


LOCAL NOBLOCK bool
NOTHROW(FCALL sct_entry_clearobj)(struct sct_entry *__restrict self) {
	void *old_value;
#ifdef CONFIG_NO_SMP
	preemption_flag_t was;
	preemption_pushoff(&was);
#endif /* CONFIG_NO_SMP */
	old_value = atomic_xch(&self->te_object, NULL);
#ifndef CONFIG_NO_SMP
	while (atomic_read(&self->te_inuse))
		task_tryyield_or_pause();
#else /* !CONFIG_NO_SMP */
	preemption_pop(&was);
#endif /* CONFIG_NO_SMP */
	return old_value != NULL;
}

#define sct_entry_decref_obj(self, obj) \
	(*handle_type_db.h_decref[(self)->te_obtype])(obj);

LOCAL WUNUSED NONNULL((1)) /*nullable*/ REF void *
NOTHROW(FCALL sct_entry_getref)(struct sct_entry *__restrict self) {
	REF void *result;
	PREEMPTION_DISABLE();
	IF_SMP(atomic_inc(&self->te_inuse));
	COMPILER_READ_BARRIER();
	result = self->te_object;
	COMPILER_READ_BARRIER();
	/* Try to acquire a reference. */
	if (likely(result) && unlikely(!(*handle_type_db.h_tryincref[self->te_obtype])(result)))
		result = NULL;
	IF_SMP(atomic_dec(&self->te_inuse));
	PREEMPTION_ENABLE();
	return result;
}



struct sct_table_struct {
	WEAK refcnt_t                                   tt_refcnt; /* Reference counter */
	size_t                                          tt_count;  /* [const] # of registered trace-entries. */
	COMPILER_FLEXIBLE_ARRAY(REF struct sct_entry *, tt_table); /* [1..1][const][tt_count] Table of trace-entries. */
};
#define sizeof_sct_table(count) \
	(offsetof(struct sct_table_struct, tt_table) + (count) * sizeof(REF struct sct_entry *))


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL sct_table_destroy)(struct sct_table_struct *__restrict self) {
	size_t i;
	/* Drop references from trace entries. */
	for (i = 0; i < self->tt_count; ++i)
		decref_unlikely(self->tt_table[i]);
	/* Free the table itself. */
	kfree(self);
}

DEFINE_REFCNT_FUNCTIONS(struct sct_table_struct, tt_refcnt, sct_table_destroy)

/* Define the empty SCT Table. */
PRIVATE struct sct_table_struct empty_sct_table = {
	.tt_refcnt = 2, /* +1: sct_table, +1: empty_sct_table */
	.tt_count  = 0,
};

ARREF(sct_table_struct_arref, sct_table_struct);

/* [1..1] The global SCT callback table. */
PRIVATE struct sct_table_struct_arref
sct_table = ARREF_INIT(&empty_sct_table);



/* Start/stop the  tracing of  system  calls by  installing/deleting  callbacks
 * that are invoked for every system call invoked after `syscall_trace_start()'
 * returns, and before `syscall_trace_stop()' returns.
 * NOTE: The internal structures related to these functions don't keep a permanent
 *       reference to the given `ob_pointer'  object, meaning that so-long as  you
 *       make sure to call `syscall_trace_stop()' from the object's finalizer, you
 *       can safely use these functions with arbitrary kernel objects.
 * @param: cb:         The callback to-be invoked when a system call is performed.
 * @param: ob_pointer: A pointer to an object of type `ob_type'
 * @param: ob_type:    One of `HANDLE_TYPE_*' that describes the type of object that `ob_pointer' is.
 * @return: true:      Successfully registered/deleted the given callback/object pair.
 * @return: false:     The same callback/object pair was already registered/was never registered at all. */
PUBLIC NONNULL((1, 2)) bool FCALL
syscall_trace_start(syscall_trace_callback_t cb,
                    void *__restrict ob_pointer,
                    uintptr_half_t ob_type)  {
	REF struct sct_entry *entry;
	bool old_table_was_empty;
	assert(cb);
	assert(ob_pointer);
	assert(ob_type < HANDLE_TYPE_COUNT);

	/* Allocate the SCT entry for this tracing sink. */
	entry = (REF struct sct_entry *)kmalloc(sizeof(struct sct_entry), GFP_NORMAL);
	/* Fill in the new SCT entry. */
	entry->te_refcnt   = 1;
	entry->te_callback = cb;
	entry->te_object   = ob_pointer;
	entry->te_obtype   = ob_type;
#ifndef CONFIG_NO_SMP
	entry->te_inuse = 0;
#endif /* !CONFIG_NO_SMP */

	TRY {
		size_t i, new_count;
		REF struct sct_table_struct *old_table;
		REF struct sct_table_struct *new_table;
		/* Insert the entry into the SCT table. */
again_insert:
		old_table = arref_get(&sct_table);
		/* Check for an existing match for `entry' */
		for (i = 0, new_count = 0; i < old_table->tt_count; ++i) {
			struct sct_entry *old_entry;
			void *obj;
			old_entry = old_table->tt_table[i];
			obj       = atomic_read(&old_entry->te_object);
			if (obj != NULL)
				++new_count;
			if (old_entry->te_obtype != ob_type)
				continue; /* Wrong object type */
			if (old_entry->te_callback != cb)
				continue; /* Wrong callback */
			if (obj != ob_pointer)
				continue; /* Wrong object */
			/* Already registered! */
			destroy(entry);
			return false;
		}
		/* Construct the new table. */
		++new_count; /* +1 for the new trace callback. */
		new_table = (struct sct_table_struct *)kmalloc(sizeof_sct_table(new_count),
		                                               GFP_NORMAL);
		new_table->tt_refcnt = 1;
		new_table->tt_count  = new_count;
		/* Copy over existing entries. */
		for (i = 0, new_count = 0; i < old_table->tt_count; ++i) {
			struct sct_entry *old_entry;
			old_entry = old_table->tt_table[i];
			if (!atomic_read(&old_entry->te_object))
				continue; /* Deleted */
			assert(new_count < new_table->tt_count);
			new_table->tt_table[new_count] = incref(old_entry);
			++new_count;
		}
		assert(new_count < new_table->tt_count);
		new_table->tt_table[new_count] = entry; /* Inherit reference */
		++new_count;
		assert(new_count <= new_table->tt_count);
		if unlikely(new_count < new_table->tt_count) {
			/* More entries got deleted. -> Try to truncate our object futher. */
			struct sct_table_struct *new_table2;
			new_table2 = (struct sct_table_struct *)krealloc_nx(new_table,
			                                                    sizeof_sct_table(new_count),
			                                                    GFP_ATOMIC);
			if likely(new_table2)
				new_table = new_table2;
			new_table->tt_count = new_count;
		}
		/* Try to replace the existing table with our new one. */
		if unlikely(!arref_cmpxch_inherit_new(&sct_table, old_table, new_table)) {
			/* The global SCT table has changed.
			 * -> Must load the new table and try again! */
			assert(new_table->tt_table[new_count - 1] == entry);
			/* Hide our new entry, so it doesn't get destroyed alongside `new_table' */
			new_table->tt_count = new_count - 1;
			destroy(new_table);
			decref(old_table);
			goto again_insert;
		}
		old_table_was_empty = old_table->tt_count == 0;
		decref_likely(old_table);
	} EXCEPT {
		destroy(entry);
		RETHROW();
	}
	/* Handle special case: if the old table was empty, then we
	 *                      must enable  system  call  tracing. */
	if (old_table_was_empty) {
		TRY {
			/* Enable system call tracing */
			arch_syscall_tracing_setenabled(true, false);
		} EXCEPT {
			/* Handle  an exception during arch-level tracing enable
			 * by deleting the freshly installed tracing hook before
			 * re-throwing the exception. */
			syscall_trace_stop(cb, ob_pointer, ob_type);
			RETHROW();
		}
	}
	return true;
}



PRIVATE NOBLOCK ATTR_NOINLINE NONNULL((1)) void
NOTHROW(FCALL sct_table_truncate)(struct sct_table_struct *old_table)  {
	size_t i, new_count;
	struct sct_table_struct *new_table;
	bool has_old_table_ref;
	has_old_table_ref = false;
again:
	/* Figure out how many entries will be required. */
	for (i = 0, new_count = 0; i < old_table->tt_count; ++i) {
		if (atomic_read(&old_table->tt_table[i]->te_object) != NULL)
			++new_count;
	}
	assert(new_count <= old_table->tt_count);
	if unlikely(new_count >= old_table->tt_count)
		goto done; /* Nothing to delete! */
	if (new_count == 0) {
		/* Special case: All tables are empty! */
		new_table = incref(&empty_sct_table);
		goto set_new_table;
	}
	new_table = (struct sct_table_struct *)kmalloc_nx(sizeof_sct_table(new_count),
	                                                  GFP_ATOMIC);
	if unlikely(!new_table)
		goto done; /* Failed to truncate the table... */
	/* Fill in the new table. */
	new_table->tt_refcnt = 1;
	new_table->tt_count  = new_count;
	for (i = 0, new_count = 0; i < old_table->tt_count; ++i) {
		struct sct_entry *entry;
		entry = old_table->tt_table[i];
		if (atomic_read(&entry->te_object) == NULL)
			continue;
		new_table->tt_table[new_count] = incref(entry);
		++new_count;
	}
	assert(new_count <= new_table->tt_count);
	if unlikely(new_count < new_table->tt_count) {
		/* More object were deleted in the mean time.
		 * -> We may be able to truncate the new table further! */
		struct sct_table_struct *new_table2;
		new_table2 = (struct sct_table_struct *)krealloc_nx(new_table,
		                                                    sizeof_sct_table(new_count),
		                                                    GFP_ATOMIC);
		if likely(new_table2)
			new_table = new_table2;
		new_table->tt_count = new_count;
	}
set_new_table:
	if (!arref_cmpxch_inherit_new_nokill(&sct_table, old_table, new_table)) {
		/* The table has changed in the meantime.
		 * -> Try again! */
		if (has_old_table_ref)
			decref(old_table);
		old_table = arref_get(&sct_table);
		has_old_table_ref = true;
		goto again;
	}
	assert(new_table->tt_count < old_table->tt_count);
	/* Check for special  case: The new  table is  empty.
	 * In this case, we must disable system call tracing. */
	if (new_table->tt_count == 0)
		arch_syscall_tracing_setenabled(false, true);
done:
	if (has_old_table_ref)
		decref(old_table);
}

PUBLIC NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL syscall_trace_stop)(syscall_trace_callback_t cb,
                                  void *__restrict ob_pointer,
                                  uintptr_half_t ob_type)  {
	size_t i;
	REF struct sct_table_struct *table;
again:
	table = arref_get(&sct_table);
	/* Find the entry in question. */
	for (i = 0; i < table->tt_count; ++i) {
		struct sct_entry *entry;
		entry = table->tt_table[i];
		if (entry->te_obtype != ob_type)
			continue; /* Wrong object type */
		if (entry->te_callback != cb)
			continue; /* Wrong callback */
		if (atomic_read(&entry->te_object) != ob_pointer)
			continue; /* Wrong object */
		/* Clear this callback entry, thus nullifying it. */
		if (!sct_entry_clearobj(entry))
			goto again;
		/* Try to allocate a new tracing table that no
		 * longer contains an entry for our component. */
		sct_table_truncate(table);
		/* Drop our reference to the table. */
		decref_likely(table);
		/* Indicate success */
		return true;
	}
	/* Failed to find the caller's entry within the table. */
	decref_unlikely(table);
	return false;
}




/* Trace a given system call.
 * This  function is called  at the start  of any user-level system
 * call   so-long   as  `arch_syscall_tracing_getenabled() == true'
 * Custom system call invocation mechanisms that directly call into
 * the underlying system call tables, rather than going through the
 * provided `syscall_emulate()' family  of functions must  manually
 * invoke this callback */
PUBLIC void FCALL
syscall_trace(struct rpc_syscall_info const *__restrict info) {
	size_t i;
	REF struct sct_table_struct *table;
	table = arref_get(&sct_table);
	FINALLY_DECREF_UNLIKELY(table);
	if unlikely(!table->tt_count) {
		/* Try to disable system call tracing.
		 * This may have failed before, since we only ever try
		 * to disable tracing in NX-mode, meaning that it  may
		 * fail arbitrarily! */
		if (arch_syscall_tracing_getenabled())
			arch_syscall_tracing_setenabled(false, true);
		return;
	}
	/* Invoke all registered callbacks. */
	for (i = 0; i < table->tt_count; ++i) {
		struct sct_entry *entry;
		REF void *obj;
		entry = table->tt_table[i];
		/* Try to acquire a reference to the bound object. */
		obj = sct_entry_getref(entry);
		if likely(obj) {
			/* Invoke the callback. */
			RAII_FINALLY { sct_entry_decref_obj(entry, obj); };
			(*entry->te_callback)(obj, info);
		} else if (atomic_read(&entry->te_object) == NULL) {
			/* Try to truncate the table to get rid of unused entries. */
			sct_table_truncate(table);
		}
	}
}



#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
PRIVATE ATTR_DBGRODATA char const sctrace_str_0[] = "0";
PRIVATE ATTR_DBGRODATA char const sctrace_str_1[] = "1";

DBG_AUTOCOMPLETE(sctrace,
                 /*size_t*/ argc, /*char **/ argv /*[]*/,
                 /*dbg_autocomplete_cb_t*/ cb, /*void **/arg) {
	(void)argv;
	if (argc == 1) {
		(*cb)(arg, sctrace_str_0, COMPILER_STRLEN(sctrace_str_0));
		(*cb)(arg, sctrace_str_1, COMPILER_STRLEN(sctrace_str_1));
	}
}

DBG_COMMAND_AUTO(sctrace, DBG_COMMANDHOOK_FLAG_AUTOEXCLUSIVE,
                 "sctrace [0|1]\n"
                 "\tGet or set system call tracing\n",
                 argc, argv) {
	bool enabled;
	if (argc == 1) {
		enabled = arch_syscall_tracing_getenabled();
		dbg_print(enabled ? DBGSTR("enabled\n") : DBGSTR("disabled\n"));
		return enabled ? 0 : 1;
	}
	if (argc != 2)
		return DBG_STATUS_INVALID_ARGUMENTS;
	if (strcmp(argv[1], sctrace_str_1) == 0) {
		enabled = true;
	} else if (strcmp(argv[1], sctrace_str_0) == 0) {
		enabled = false;
	} else {
		return DBG_STATUS_INVALID_ARGUMENTS;
	}
	arch_syscall_tracing_setenabled(enabled, false);
	return 0;
}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

DECL_END
#endif /* !CONFIG_NO_KERNEL_SYSCALL_TRACING */

#endif /* !GUARD_KERNEL_SRC_MISC_SYSCALL_TRACE_C */
