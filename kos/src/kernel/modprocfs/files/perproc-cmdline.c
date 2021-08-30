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
#ifndef GUARD_MODPROCFS_FILES_PERPROC_CMDLINE_C
#define GUARD_MODPROCFS_FILES_PERPROC_CMDLINE_C 1

#include <kernel/compiler.h>

#include <kernel/mman.h>
#include <kernel/mman/execinfo.h>
#include <kernel/mman/rw.h>
#include <kernel/user.h>
#include <sched/pid.h>

#include <hybrid/overflow.h>

#include <compat/config.h>
#include <kos/exec/peb.h>

#include <format-printer.h>
#include <stddef.h>
#include <string.h>

#include "../procfs.h"

#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/exec/peb.h>
#include <compat/kos/types.h>
#include <compat/pointer.h>
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

/* Print the given c-string, or do nothing if the address is faulty.
 * NOTE: The trailing NUL-character is also printed by this function! */
PRIVATE NONNULL((1, 2)) ssize_t KCALL
print_userspace_cstring(struct mman *__restrict mm, pformatprinter printer,
                        void *arg, USER CHECKED char const *cstr) {
	char buf[512], *endptr;
	ssize_t temp, result = 0;
	size_t num_bytes;
again:
	num_bytes = sizeof(buf) - mman_read_nopf(mm, cstr, buf, sizeof(buf));
	endptr    = (char *)memchr(buf, 0, num_bytes);
	if (endptr)
		num_bytes = (size_t)((endptr + 1) - buf);
	temp = (*printer)(arg, buf, num_bytes);
	if unlikely(result < 0)
		goto err;
	result += temp;
	if (!endptr) {
		/* Keep reading more data until we hit the trailing NUL! */
		cstr += num_bytes;
		mman_read(mm, cstr, buf, 1); /* Force read 1 bytes */
		temp = (*printer)(arg, buf, 1);
		if unlikely(temp < 0)
			goto err;
		result += temp;
		if likely(buf[0] != 0) {
			/* Keep reading. */
			++cstr;
			goto again;
		}
	}
	return result;
err:
	return temp;
}

INTERN NONNULL((1, 2)) ssize_t KCALL
ProcFS_PrintUserSpaceStringArray(struct mman *__restrict mm, pformatprinter printer, void *arg,
                                 size_t strc, char const *USER UNCHECKED const *USER CHECKED strv) {
	ssize_t temp, result = 0;
	size_t i;

	/* Verify bounds. */
	if unlikely(OVERFLOW_UMUL(strc, sizeof(*strv), &i))
		goto done;
	if unlikely(OVERFLOW_UADD((uintptr_t)strv, i, &i))
		goto done;
	if unlikely(!ADDRRANGE_ISUSER(strv, i))
		goto done;
	while (strc) {
		USER UNCHECKED char const *strings[32];
		size_t count = strc;
		if (count > COMPILER_STRLEN(strings))
			count = COMPILER_STRLEN(strings);
		mman_read(mm, strv, strings, count * sizeof(USER UNCHECKED char const *));
		for (i = 0; i < count; ++i) {
			USER UNCHECKED char const *str = strings[i];
			if (!str || !ADDR_ISUSER(str))
				goto done;
			temp = print_userspace_cstring(mm, printer, arg, str);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
		strv += count;
		strc -= count;
	}
done:
	return result;
err:
	return temp;
}

#ifdef __ARCH_HAVE_COMPAT
INTERN NONNULL((1, 2)) ssize_t KCALL
ProcFS_PrintCompatUserSpaceStringArray(struct mman *__restrict mm, pformatprinter printer, void *arg,
                                       size_t strc, compat_uintptr_t USER UNCHECKED const *USER CHECKED strv) {
	ssize_t temp, result = 0;
	size_t i;

	/* Verify bounds. */
	if unlikely(OVERFLOW_UMUL(strc, sizeof(*strv), &i))
		goto done;
	if unlikely(OVERFLOW_UADD((uintptr_t)strv, i, &i))
		goto done;
	if unlikely(!ADDRRANGE_ISUSER(strv, i))
		goto done;
	while (strc) {
		USER UNCHECKED compat_uintptr_t strings[32];
		size_t count = strc;
		if (count > COMPILER_STRLEN(strings))
			count = COMPILER_STRLEN(strings);
		mman_read(mm, strv, strings, count * sizeof(USER UNCHECKED compat_uintptr_t));
		for (i = 0; i < count; ++i) {
			USER UNCHECKED compat_uintptr_t str = strings[i];
			if (!str || !ADDR_ISUSER(str))
				goto done;
			temp = print_userspace_cstring(mm, printer, arg,
			                               (USER CHECKED char const *)(uintptr_t)str);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
		strv += count;
		strc -= count;
	}
done:
	return result;
err:
	return temp;
}
#endif /* __ARCH_HAVE_COMPAT */




struct _peb_cmdline_buffer {
#if OFFSET_PROCESS_PEB_ARGC < OFFSET_PROCESS_PEB_ARGV
	size_t pp_argc;
#if (OFFSET_PROCESS_PEB_ARGC + __SIZEOF_SIZE_T__) < OFFSET_PROCESS_PEB_ARGV
	byte_t __pp_pad[OFFSET_PROCESS_PEB_ARGV - (OFFSET_PROCESS_PEB_ARGC + __SIZEOF_SIZE_T__)];
#elif (OFFSET_PROCESS_PEB_ARGC + __SIZEOF_SIZE_T__) > OFFSET_PROCESS_PEB_ARGV
#error "Invalid offsets"
#endif /* ... */
	char const *USER UNCHECKED const *USER UNCHECKED pp_argv;
#else /* OFFSET_PROCESS_PEB_ARGC < OFFSET_PROCESS_PEB_ARGV */
	char const *USER UNCHECKED const *USER UNCHECKED pp_argv;
#if (OFFSET_PROCESS_PEB_ARGV + __SIZEOF_SIZE_T__) < OFFSET_PROCESS_PEB_ARGC
	byte_t __pp_pad[OFFSET_PROCESS_PEB_ARGC - (OFFSET_PROCESS_PEB_ARGV + __SIZEOF_SIZE_T__)];
#elif (OFFSET_PROCESS_PEB_ARGV + __SIZEOF_SIZE_T__) > OFFSET_PROCESS_PEB_ARGC
#error "Invalid offsets"
#endif /* ... */
	size_t pp_argc;
#endif /* OFFSET_PROCESS_PEB_ARGC >= OFFSET_PROCESS_PEB_ARGV */
};

PRIVATE NONNULL((1, 2)) ssize_t KCALL
peb_print_cmdline(struct mman *__restrict mm, pformatprinter printer,
                   void *arg, USER CHECKED struct process_peb const *peb) {
	struct _peb_cmdline_buffer info;
	mman_read(mm, (byte_t const *)peb + OFFSET_PROCESS_PEB_ARGC, &info, sizeof(info));
	return ProcFS_PrintUserSpaceStringArray(mm, printer, arg, info.pp_argc, info.pp_argv);
}


#ifdef __ARCH_HAVE_COMPAT
struct _compat_peb_cmdline_buffer {
#if OFFSET_COMPAT_PROCESS_PEB_ARGC < OFFSET_COMPAT_PROCESS_PEB_ARGV
	compat_size_t pp_argc;
#if (OFFSET_COMPAT_PROCESS_PEB_ARGC + __ARCH_COMPAT_SIZEOF_SIZE_T) < OFFSET_COMPAT_PROCESS_PEB_ARGV
	byte_t __pp_pad[OFFSET_COMPAT_PROCESS_PEB_ARGV - (OFFSET_COMPAT_PROCESS_PEB_ARGC + __ARCH_COMPAT_SIZEOF_SIZE_T)];
#elif (OFFSET_COMPAT_PROCESS_PEB_ARGC + __ARCH_COMPAT_SIZEOF_SIZE_T) > OFFSET_COMPAT_PROCESS_PEB_ARGV
#error "Invalid offsets"
#endif /* ... */
	compat_ptr(compat_uintptr_t) pp_argv;
#else /* OFFSET_COMPAT_PROCESS_PEB_ARGC < OFFSET_COMPAT_PROCESS_PEB_ARGV */
	compat_ptr(compat_uintptr_t) pp_argv;
#if (OFFSET_COMPAT_PROCESS_PEB_ARGV + __ARCH_COMPAT_SIZEOF_SIZE_T) < OFFSET_COMPAT_PROCESS_PEB_ARGC
	byte_t __pp_pad[OFFSET_COMPAT_PROCESS_PEB_ARGC - (OFFSET_COMPAT_PROCESS_PEB_ARGV + __ARCH_COMPAT_SIZEOF_SIZE_T)];
#elif (OFFSET_COMPAT_PROCESS_PEB_ARGV + __ARCH_COMPAT_SIZEOF_SIZE_T) > OFFSET_COMPAT_PROCESS_PEB_ARGC
#error "Invalid offsets"
#endif /* ... */
	size_t pp_argc;
#endif /* OFFSET_COMPAT_PROCESS_PEB_ARGC >= OFFSET_COMPAT_PROCESS_PEB_ARGV */
};

PRIVATE NONNULL((1, 2)) ssize_t KCALL
compat_peb_print_cmdline(struct mman *__restrict mm, pformatprinter printer,
                         void *arg, USER CHECKED struct compat_process_peb const *peb) {
	struct _compat_peb_cmdline_buffer info;
	mman_read(mm, (byte_t const *)peb + OFFSET_COMPAT_PROCESS_PEB_ARGC, &info, sizeof(info));
	return ProcFS_PrintCompatUserSpaceStringArray(mm, printer, arg, info.pp_argc, info.pp_argv);
}
#endif /* __ARCH_HAVE_COMPAT */



INTERN NONNULL((1)) ssize_t KCALL
ProcFS_PerProc_Cmdline_Printer(struct regular_node *__restrict self,
                               pformatprinter printer, void *arg) {
	REF struct task *thread;
	REF struct mman *threadmm;
	ssize_t result = 0;
	upid_t pid;
	/* Lookup the associated thread. */
	pid    = (upid_t)(self->i_fileino & PROCFS_INOTYPE_PERPROC_PIDMASK);
	thread = pidns_trylookup_task(THIS_PIDNS, pid);
	if unlikely(!thread)
		goto done;
	/* Lookup the associated mman. */
	{
		FINALLY_DECREF_UNLIKELY(thread);
		threadmm = task_getmman(thread);
	}
	{
		USER CHECKED void *peb;
		FINALLY_DECREF_UNLIKELY(threadmm);
		peb = FORMMAN(threadmm, thismman_execinfo).mei_peb;

#ifdef __ARCH_HAVE_COMPAT
		if (FORMMAN(threadmm, thismman_execinfo).mei_peb_iscompat) {
			result = compat_peb_print_cmdline(threadmm, printer, arg,
			                                  (USER CHECKED struct compat_process_peb const *)peb);
		} else
#endif /* __ARCH_HAVE_COMPAT */
		{
			result = peb_print_cmdline(threadmm, printer, arg,
			                           (USER CHECKED struct process_peb const *)peb);
		}
	}
done:
	return result;
}


DECL_END

#endif /* !GUARD_MODPROCFS_FILES_PERPROC_CMDLINE_C */
