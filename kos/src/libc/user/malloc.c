/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_MALLOC_C
#define GUARD_LIBC_USER_MALLOC_C 1

#include "../api.h"
/**/

#include <hybrid/overflow.h>

#include <asm/redirect.h>
#include <bits/crt/mallinfo.h>
#include <kos/except.h>
#include <kos/exec/idata.h>
#include <kos/sys/mman.h>

#include <assert.h>
#include <atomic.h>
#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

#include "../libc/dl.h"
#include "../libc/globals.h"
#include "malloc.h"
#include "stdlib.h"

DECL_BEGIN

/*[[[skip:libc_valloc]]]*/
/*[[[skip:libc_realloc_in_place]]]*/
/*[[[skip:libc_posix_memalign]]]*/
/*[[[skip:libc_memalign]]]*/
/*[[[skip:libc_pvalloc]]]*/
/*[[[skip:libc_malloc_usable_size]]]*/
/*[[[skip:libc_malloc_trim]]]*/
/*[[[skip:libc_mallopt]]]*/
/*[[[skip:libc_mallinfo]]]*/
/*[[[skip:libc_mallinfo2]]]*/

#if __ARCH_REDIRECT_MAXBYTES != 0

#define FATAL(format, ...)                                         \
	do {                                                           \
		syslog(LOG_ERR, "[libc] " format "\n", ##__VA_ARGS__);     \
		if (isatty(STDERR_FILENO)) {                               \
			dprintf(STDERR_FILENO, "%s: " format "\n",             \
			        program_invocation_short_name, ##__VA_ARGS__); \
		}                                                          \
		abort();                                                   \
	}	__WHILE0


typedef void *(LIBCCALL *LPMALLOC)(size_t num_bytes);
typedef void (LIBCCALL *LPFREE)(void *ptr);
typedef void *(LIBCCALL *LPCALLOC)(size_t elem_count, size_t elem_size);
typedef void *(LIBCCALL *LPREALLOC)(void *ptr, size_t num_bytes);
typedef void *(LIBCCALL *LPREALLOC_IN_PLACE)(void *ptr, size_t num_bytes);
typedef void *(LIBCCALL *LPMEMALIGN)(size_t alignment, size_t num_bytes);
typedef errno_t (LIBCCALL *LPPOSIX_MEMALIGN)(void **p_ptr, size_t alignment, size_t num_bytes);
typedef void *(LIBCCALL *LPVALLOC)(size_t num_bytes);
typedef void *(LIBCCALL *LPPVALLOC)(size_t num_bytes);
typedef int (LIBCCALL *LPMALLOPT)(int param_number, int value);
typedef struct mallinfo (LIBCCALL *LPMALLINFO)(void);
typedef struct mallinfo2 (LIBCCALL *LPMALLINFO2)(void);
typedef int (LIBCCALL *LPMALLOC_TRIM)(size_t pad);
typedef size_t (LIBCCALL *LPMALLOC_USABLE_SIZE)(void *ptr);
typedef void *(LIBCCALL *LPMEMDUP)(void const *ptr, size_t n_bytes);
typedef void *(LIBCCALL *LPMEMCDUP)(void const *ptr, int needle, size_t n_bytes);
typedef void *(LIBCCALL *LPREALLOCARRAY)(void *ptr, size_t elem_count, size_t elem_size);
typedef void *(LIBCCALL *LPRECALLOC)(void *mallptr, size_t num_bytes);
typedef void *(LIBCCALL *LPRECALLOCV)(void *mallptr, size_t elem_count, size_t elem_size);


/* ABI for how malloc should be implemented. */
struct user_malloc_abi {
	/* Core heap functions */
	LPMALLOC             uma_malloc;
	LPFREE               uma_free;
	LPCALLOC             uma_calloc;
	LPREALLOC            uma_realloc;
	LPREALLOC_IN_PLACE   uma_realloc_in_place;
	LPMEMALIGN           uma_memalign;
	LPPOSIX_MEMALIGN     uma_posix_memalign;
	LPVALLOC             uma_valloc;
	LPPVALLOC            uma_pvalloc;
	LPMALLOPT            uma_mallopt;
	LPMALLINFO           uma_mallinfo;
#if __SIZEOF_INT__ != __SIZEOF_SIZE_T__
	LPMALLINFO2          uma_mallinfo2;
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
	LPMALLOC_TRIM        uma_malloc_trim;
	LPMALLOC_USABLE_SIZE uma_malloc_usable_size;

	/* Non-core heap functions (only redirected if defined differently from libc) */
	LPMEMDUP             uma_memdup;
	LPMEMCDUP            uma_memcdup;
	LPREALLOCARRAY       uma_reallocarray;
	LPRECALLOC           uma_recalloc;
	LPRECALLOCV          uma_recallocv;
};

PRIVATE ATTR_SECTION(".rodata.crt.heap.malloc") char const nameof_malloc[] = "malloc";
PRIVATE ATTR_SECTION(".rodata.crt.heap.rare_helpers") char const nameof_free[] = "free";
PRIVATE ATTR_SECTION(".rodata.crt.heap.rare_helpers") char const nameof_cfree[] = "cfree";
PRIVATE ATTR_SECTION(".rodata.crt.heap.rare_helpers") char const nameof_calloc[] = "calloc";
PRIVATE ATTR_SECTION(".rodata.crt.heap.rare_helpers") char const nameof_realloc[] = "realloc";
PRIVATE ATTR_SECTION(".rodata.crt.heap.rare_helpers") char const nameof_realloc_in_place[] = "realloc_in_place";
PRIVATE ATTR_SECTION(".rodata.crt.heap.rare_helpers") char const nameof_memalign[] = "memalign";
PRIVATE ATTR_SECTION(".rodata.crt.heap.rare_helpers") char const nameof_aligned_alloc[] = "aligned_alloc";
PRIVATE ATTR_SECTION(".rodata.crt.heap.rare_helpers") char const nameof_posix_memalign[] = "posix_memalign";
PRIVATE ATTR_SECTION(".rodata.crt.heap.rare_helpers") char const nameof_valloc[] = "valloc";
PRIVATE ATTR_SECTION(".rodata.crt.heap.rare_helpers") char const nameof_pvalloc[] = "pvalloc";
PRIVATE ATTR_SECTION(".rodata.crt.heap.rare_helpers") char const nameof_mallopt[] = "mallopt";
PRIVATE ATTR_SECTION(".rodata.crt.heap.rare_helpers") char const nameof_mallinfo[] = "mallinfo";
PRIVATE ATTR_SECTION(".rodata.crt.heap.rare_helpers") char const nameof_mallinfo2[] = "mallinfo2";
PRIVATE ATTR_SECTION(".rodata.crt.heap.rare_helpers") char const nameof_malloc_trim[] = "malloc_trim";
PRIVATE ATTR_SECTION(".rodata.crt.heap.rare_helpers") char const nameof_malloc_usable_size[] = "malloc_usable_size";
PRIVATE ATTR_SECTION(".rodata.crt.heap.rare_helpers") char const nameof__msize[] = "_msize";
PRIVATE ATTR_SECTION(".rodata.crt.heap.rare_helpers") char const nameof_memdup[] = "memdup";
PRIVATE ATTR_SECTION(".rodata.crt.heap.rare_helpers") char const nameof_memcdup[] = "memcdup";
PRIVATE ATTR_SECTION(".rodata.crt.heap.rare_helpers") char const nameof_reallocarray[] = "reallocarray";
PRIVATE ATTR_SECTION(".rodata.crt.heap.rare_helpers") char const nameof_recalloc[] = "recalloc";
PRIVATE ATTR_SECTION(".rodata.crt.heap.rare_helpers") char const nameof_recallocv[] = "recallocv";



PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") void
NOTHROW(LIBCCALL fallback_free_NOOP)(void *ptr) {
	(void)ptr;
	COMPILER_IMPURE();
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") void *LIBCCALL
fallback_calloc_with_malloc(size_t elem_count, size_t elem_size) {
	void *result;
	size_t num_bytes;
	if (OVERFLOW_UMUL(elem_count, elem_size, &num_bytes))
		num_bytes = (size_t)-1;
	result = malloc(num_bytes);
	if likely(result)
		bzero(result, num_bytes);
	return result;
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") void *LIBCCALL
fallback_realloc_with_malloc_and_usable_size(void *ptr, size_t num_bytes) {
	void *result;
	size_t usable_size;
	usable_size = malloc_usable_size(ptr);
	if (num_bytes <= usable_size) {
		result = ptr;
		if (num_bytes < usable_size) {
			result = realloc_in_place(ptr, num_bytes);
			if (result == NULL)
				result = ptr;
		} else if (ptr == NULL) {
			result = malloc(num_bytes);
		}
	} else {
		result = malloc(num_bytes);
		if likely(result) {
			result = memcpy(result, ptr, num_bytes);
			free(ptr);
		}
	}
	return result;
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") void *LIBCCALL
fallback_realloc_with_NULL(void *ptr, size_t num_bytes) {
	void *result;
	if (ptr == NULL) {
		result = malloc(num_bytes);
	} else {
		result = NULL;
	}
	return result;
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") void *LIBCCALL
fallback_realloc_in_place_with_usable_size(void *ptr, size_t num_bytes) {
	size_t usable_size = malloc_usable_size(ptr);
	if (usable_size >= num_bytes)
		return ptr;
	return NULL;
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") void *LIBCCALL
fallback_realloc_in_place_with_NULL(void *ptr, size_t num_bytes) {
	COMPILER_IMPURE();
	(void)ptr;
	(void)num_bytes;
	return NULL;
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") void *LIBCCALL
fallback_memalign_with_posix_memalign(size_t alignment, size_t num_bytes) {
	errno_t error;
	void *result;
	error = posix_memalign(&result, alignment, num_bytes);
	if (error == 0)
		return result;
	(void)libc_seterrno(error);
	return NULL;
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") void *LIBCCALL
fallback_memalign_with_malloc(size_t alignment, size_t num_bytes) {
	if (alignment <= __ALIGNOF_MAX_ALIGN_T__)
		return malloc(num_bytes);
	return NULL;
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") errno_t LIBCCALL
fallback_posix_memalign_with_memalign(void **p_ptr, size_t alignment, size_t num_bytes) {
	errno_t saved_errno, error;
	void *result;
	saved_errno = libc_geterrno();
	result      = memalign(alignment, num_bytes);
	if (result != NULL) {
		*p_ptr = result;
		return 0;
	}
	error = libc_geterrno();
	if unlikely(!error)
		error = ENOMEM;
	(void)libc_seterrno(saved_errno);
	return error;
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") void *LIBCCALL
fallback_valloc_with_memalign(size_t num_bytes) {
	size_t ps = getpagesize();
	return memalign(ps, num_bytes);
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") void *LIBCCALL
fallback_pvalloc_with_valloc(size_t num_bytes) {
	size_t ps = getpagesize();
	if (OVERFLOW_UADD(num_bytes, ps - 1, &num_bytes))
		num_bytes = (size_t)-1;
	num_bytes &= ~(ps - 1);
	return valloc(num_bytes);
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") int LIBCCALL
fallback_mallopt_NOOP(int param_number, int value) {
	(void)param_number;
	(void)value;
	COMPILER_IMPURE();
	return 0;
}

#if __SIZEOF_INT__ != __SIZEOF_SIZE_T__
PRIVATE struct mallinfo2 LIBCCALL
fallback_mallinfo2_with_mallinfo(void) {
	struct mallinfo info = mallinfo();
	struct mallinfo2 result;
	result.arena    = (size_t)info.arena;
	result.ordblks  = (size_t)info.ordblks;
	result.smblks   = (size_t)info.smblks;
	result.hblks    = (size_t)info.hblks;
	result.hblkhd   = (size_t)info.hblkhd;
	result.usmblks  = (size_t)info.usmblks;
	result.fsmblks  = (size_t)info.fsmblks;
	result.uordblks = (size_t)info.uordblks;
	result.fordblks = (size_t)info.fordblks;
	result.keepcost = (size_t)info.keepcost;
	return result;
}

PRIVATE struct mallinfo2 LIBCCALL
fallback_mallinfo2_NOOP(void) {
	struct mallinfo2 result;
	bzero(&result, sizeof(result));
	return result;
}

PRIVATE struct mallinfo LIBCCALL
fallback_mallinfo_with_mallinfo2(void) {
	struct mallinfo2 info = mallinfo2();
	struct mallinfo result;
	result.arena    = (int)(unsigned int)info.arena;
	result.ordblks  = (int)(unsigned int)info.ordblks;
	result.smblks   = (int)(unsigned int)info.smblks;
	result.hblks    = (int)(unsigned int)info.hblks;
	result.hblkhd   = (int)(unsigned int)info.hblkhd;
	result.usmblks  = (int)(unsigned int)info.usmblks;
	result.fsmblks  = (int)(unsigned int)info.fsmblks;
	result.uordblks = (int)(unsigned int)info.uordblks;
	result.fordblks = (int)(unsigned int)info.fordblks;
	result.keepcost = (int)(unsigned int)info.keepcost;
	return result;
}
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */

PRIVATE struct mallinfo LIBCCALL
fallback_mallinfo_NOOP(void) {
	struct mallinfo result;
	bzero(&result, sizeof(result));
	return result;
}


PRIVATE int LIBCCALL
fallback_malloc_trim_NOOP(size_t pad) {
	(void)pad;
	COMPILER_IMPURE();
	return 0;
}

PRIVATE ATTR_SECTION(".bss.crt.heap.rare_helpers")
LPMALLOC_USABLE_SIZE libc_user__msize = NULL;

PRIVATE size_t LIBCCALL
fallback_malloc_usable_size_with__msize(void *ptr) {
	return ptr ? (*libc_user__msize)(ptr) : 0;
}

PRIVATE size_t LIBCCALL
fallback_malloc_usable_size_NOOP(void *ptr) {
	/* NOTE: Returning `0' here might not be ABI-compliant in
	 *       every situation, but it's the best we can  do... */
	(void)ptr;
	COMPILER_IMPURE();
	return 0;
}


PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") WUNUSED NONNULL((1, 2)) void *LIBCCALL
user_malloc_abi_dlsym(char const *name, void *libc_addr) {
	void *result = dlsym(RTLD_DEFAULT, name);
	if (result == libc_addr)
		result = NULL;
	return result;
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") NONNULL((1)) void LIBCCALL
user_malloc_abi_load(struct user_malloc_abi *__restrict self) {
	/* Load user-definable overrides for all symbols first (malloc was already loaded) */
	*(void **)&self->uma_free = user_malloc_abi_dlsym(nameof_free, (void *)&libc_free);
	if (*(void **)&self->uma_free == NULL)
		*(void **)&self->uma_free = user_malloc_abi_dlsym(nameof_cfree, (void *)&libc_free);
	*(void **)&self->uma_calloc = user_malloc_abi_dlsym(nameof_calloc, (void *)&libc_calloc);
	*(void **)&self->uma_realloc = user_malloc_abi_dlsym(nameof_realloc, (void *)&libc_realloc);
	*(void **)&self->uma_realloc_in_place = user_malloc_abi_dlsym(nameof_realloc_in_place, (void *)&libc_realloc_in_place);
	*(void **)&self->uma_memalign = user_malloc_abi_dlsym(nameof_memalign, (void *)&libc_memalign);
	if (*(void **)&self->uma_memalign == NULL)
		*(void **)&self->uma_memalign = user_malloc_abi_dlsym(nameof_aligned_alloc, (void *)&libc_memalign);
	*(void **)&self->uma_posix_memalign = user_malloc_abi_dlsym(nameof_posix_memalign, (void *)&libc_posix_memalign);
	*(void **)&self->uma_valloc = user_malloc_abi_dlsym(nameof_valloc, (void *)&libc_valloc);
	*(void **)&self->uma_pvalloc = user_malloc_abi_dlsym(nameof_pvalloc, (void *)&libc_pvalloc);
	*(void **)&self->uma_mallopt = user_malloc_abi_dlsym(nameof_mallopt, (void *)&libc_mallopt);
	*(void **)&self->uma_mallinfo = user_malloc_abi_dlsym(nameof_mallinfo, (void *)&libc_mallinfo);
#if __SIZEOF_INT__ != __SIZEOF_SIZE_T__
	*(void **)&self->uma_mallinfo2 = user_malloc_abi_dlsym(nameof_mallinfo2, (void *)&libc_mallinfo2);
#else /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
	if (self->uma_mallinfo == NULL)
		*(void **)&self->uma_mallinfo = user_malloc_abi_dlsym(nameof_mallinfo2, (void *)&libc_mallinfo2);
#endif /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ */
	*(void **)&self->uma_malloc_trim = user_malloc_abi_dlsym(nameof_malloc_trim, (void *)&libc_malloc_trim);
	*(void **)&self->uma_malloc_usable_size = user_malloc_abi_dlsym(nameof_malloc_usable_size, (void *)&libc_malloc_usable_size);
	if (*(void **)&self->uma_malloc_usable_size == NULL) {
		/* Also support users defining DOS's `_msize', but note that
		 * `_msize' doesn't accept NULL, so we still need a wrapper. */
		void *user__msize = user_malloc_abi_dlsym(nameof__msize, (void *)&libc_malloc_usable_size);
		if (user__msize != NULL) {
			*(void **)&libc_user__msize  = user__msize;
			self->uma_malloc_usable_size = &fallback_malloc_usable_size_with__msize;
		}
	}

	/* Load overrides for optional functions */
	*(void **)&self->uma_memdup = user_malloc_abi_dlsym(nameof_memdup, (void *)&libc_memdup);
	*(void **)&self->uma_memcdup = user_malloc_abi_dlsym(nameof_memcdup, (void *)&libc_memcdup);
	*(void **)&self->uma_reallocarray = user_malloc_abi_dlsym(nameof_reallocarray, (void *)&libc_reallocarray);
	*(void **)&self->uma_recalloc = user_malloc_abi_dlsym(nameof_recalloc, (void *)&libc_recalloc);
	*(void **)&self->uma_recallocv = user_malloc_abi_dlsym(nameof_recallocv, (void *)&libc_recallocv);

	/* Substitute missing functions. */
	if (self->uma_free == NULL)
		self->uma_free = &fallback_free_NOOP;
	if (self->uma_calloc == NULL)
		self->uma_calloc = &fallback_calloc_with_malloc;
	if (self->uma_realloc == NULL) {
		if (self->uma_malloc_usable_size) {
			self->uma_realloc = &fallback_realloc_with_malloc_and_usable_size;
		} else {
			self->uma_realloc = &fallback_realloc_with_NULL;
		}
	}
	if (self->uma_realloc_in_place == NULL) {
		if (self->uma_malloc_usable_size) {
			self->uma_realloc_in_place = &fallback_realloc_in_place_with_usable_size;
		} else {
			self->uma_realloc_in_place = &fallback_realloc_in_place_with_NULL;
		}
	}
	if (self->uma_memalign == NULL) {
		if (self->uma_posix_memalign) {
			self->uma_memalign = &fallback_memalign_with_posix_memalign;
		} else {
			self->uma_memalign = &fallback_memalign_with_malloc;
		}
	}
	if (self->uma_posix_memalign == NULL)
		self->uma_posix_memalign = &fallback_posix_memalign_with_memalign;
	if (self->uma_valloc == NULL)
		self->uma_valloc = &fallback_valloc_with_memalign;
	if (self->uma_pvalloc == NULL)
		self->uma_pvalloc = &fallback_pvalloc_with_valloc;
	if (self->uma_mallopt == NULL)
		self->uma_mallopt = &fallback_mallopt_NOOP;
#if __SIZEOF_INT__ != __SIZEOF_SIZE_T__
	if (self->uma_mallinfo2 == NULL) {
		if (self->uma_mallinfo != NULL) {
			self->uma_mallinfo2 = &fallback_mallinfo2_with_mallinfo;
		} else {
			self->uma_mallinfo2 = &fallback_mallinfo2_NOOP;
			self->uma_mallinfo  = &fallback_mallinfo_NOOP;
		}
	}
	if (self->uma_mallinfo == NULL) {
		if (self->uma_mallinfo2 != NULL) {
			self->uma_mallinfo = &fallback_mallinfo_with_mallinfo2;
		} else {
			self->uma_mallinfo = &fallback_mallinfo_NOOP;
		}
	}
#else /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
	if (self->uma_mallinfo == NULL)
		self->uma_mallinfo = &fallback_mallinfo_NOOP;
#endif /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ */
	if (self->uma_malloc_trim == NULL)
		self->uma_malloc_trim = &fallback_malloc_trim_NOOP;
	if (self->uma_malloc_usable_size == NULL)
		self->uma_malloc_usable_size = &fallback_malloc_usable_size_NOOP;
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") NONNULL((1, 2, 3)) void LIBCCALL
libc_malloc_redirect(char const *name, void *from_pc, void *to_pc) {
#ifdef __arch_redirect_size
	size_t size = __arch_redirect_size(from_pc, to_pc);
#else /* __arch_redirect_size */
	size_t size = __ARCH_REDIRECT_MAXBYTES;
#endif /* !__arch_redirect_size */
#ifdef __arch_redirect_possible
	if (!__arch_redirect_possible(from_pc, to_pc))
		FATAL("Impossible to redirect `%s' from %p to %p", name, from_pc, to_pc);
#endif /* __arch_redirect_possible */
	(void)name;
	MProtect(from_pc, size, PROT_EXEC | PROT_WRITE | PROT_READ);
	__arch_redirect(from_pc, to_pc);
	MProtect(from_pc, size, PROT_EXEC | PROT_READ);
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") NONNULL((1, 2)) void LIBCCALL
libc_malloc_redirect_opt(char const *name, void *from_pc, void *to_pc) {
	if (to_pc != NULL)
		libc_malloc_redirect(name, from_pc, to_pc);
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") void LIBCCALL
user_malloc_abi_install(struct user_malloc_abi *__restrict self) {
	libc_malloc_redirect(nameof_malloc, (void *)&libc_malloc, *(void **)&self->uma_malloc);
	libc_malloc_redirect(nameof_free, (void *)&libc_free, *(void **)&self->uma_free);
	libc_malloc_redirect(nameof_calloc, (void *)&libc_calloc, *(void **)&self->uma_calloc);
	libc_malloc_redirect(nameof_realloc, (void *)&libc_realloc, *(void **)&self->uma_realloc);
	libc_malloc_redirect(nameof_realloc_in_place, (void *)&libc_realloc_in_place, *(void **)&self->uma_realloc_in_place);
	libc_malloc_redirect(nameof_memalign, (void *)&libc_memalign, *(void **)&self->uma_memalign);
	libc_malloc_redirect(nameof_posix_memalign, (void *)&libc_posix_memalign, *(void **)&self->uma_posix_memalign);
	libc_malloc_redirect(nameof_valloc, (void *)&libc_valloc, *(void **)&self->uma_valloc);
	libc_malloc_redirect(nameof_pvalloc, (void *)&libc_pvalloc, *(void **)&self->uma_pvalloc);
	libc_malloc_redirect(nameof_mallopt, (void *)&libc_mallopt, *(void **)&self->uma_mallopt);
	libc_malloc_redirect(nameof_mallinfo, (void *)&libc_mallinfo, *(void **)&self->uma_mallinfo);
#if __SIZEOF_INT__ != __SIZEOF_SIZE_T__
	libc_malloc_redirect(nameof_mallinfo2, (void *)&libc_mallinfo2, *(void **)&self->uma_mallinfo2);
#endif /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
	libc_malloc_redirect(nameof_malloc_trim, (void *)&libc_malloc_trim, *(void **)&self->uma_malloc_trim);
	libc_malloc_redirect(nameof_malloc_usable_size, (void *)&libc_malloc_usable_size, *(void **)&self->uma_malloc_usable_size);
	libc_malloc_redirect_opt(nameof_memdup, (void *)&libc_memdup, *(void **)&self->uma_memdup);
	libc_malloc_redirect_opt(nameof_memcdup, (void *)&libc_memcdup, *(void **)&self->uma_memcdup);
	libc_malloc_redirect_opt(nameof_reallocarray, (void *)&libc_reallocarray, *(void **)&self->uma_reallocarray);
	libc_malloc_redirect_opt(nameof_recalloc, (void *)&libc_recalloc, *(void **)&self->uma_recalloc);
	libc_malloc_redirect_opt(nameof_recallocv, (void *)&libc_recallocv, *(void **)&self->uma_recallocv);
}

PRIVATE ATTR_NOINLINE ATTR_SECTION(".text.crt.heap.rare_helpers") NONNULL((1)) int LIBCCALL
libc_do_init_malloc_hooks(LPMALLOC user_malloc) {
	struct user_malloc_abi abi;
	if unlikely(!user_malloc)
		return 0; /* Shouldn't happen, since we should have seen our own version... */

	syslog(LOG_INFO, "[libc] Using malloc override at %p\n", user_malloc);
	bzero(&abi, sizeof(abi));
	abi.uma_malloc = user_malloc;

	/* Load the rest of the ABI. */
	user_malloc_abi_load(&abi);

	/* Install the ABI. */
	user_malloc_abi_install(&abi);

	/* Indicate to the malloc implementation that the call must be restarted. */
	return 1;
}



/* Called when one of the malloc functions is called for the first time.
 * Used  to check if some other library  (or the main app) is overriding
 * our `malloc()' function, and if so, modifies libc code to always call
 * that override.
 *
 * We do this using self-modifying code, since this sort of thing doesn't
 * happen very often, and this way, we don't have any extra overhead that
 * would arise when doing it any other way.
 *
 * This also allows us to  be extra-intuitive when only *some*  functions
 * are being overwritten (like we can emulate the default system `calloc'
 * using only a user-defined `malloc')
 *
 * In order to activate this system, you must define
 * >> extern void *malloc(size_t num_bytse);
 *
 * If you don't define malloc, but define any of the other functions,
 * your functions will NOT be used! */
INTERN ATTR_SECTION(".text.crt.heap.malloc") int LIBCCALL
libc_init_malloc_hooks(void) {
	LPMALLOC user_malloc;
	*(void **)&user_malloc = dlsym(RTLD_DEFAULT, nameof_malloc);
	if likely(user_malloc == &libc_malloc)
		return 0; /* *highly* likely case: malloc isn't being overwritten */
	return libc_do_init_malloc_hooks(user_malloc);
}



/* Support for Glibc malloc hook function pointers.
 *
 * In order to support these, we do something similar to `libc_init_malloc_hooks()',
 * in  that we in-place modify all implementations  of heap functions found in libc.
 * However,  since Glibc malloc hooks *are* meant as proxy wrappers that can also be
 * disabled at any time, we run into a problem:
 * - If we redirect all of our heap functions to invoke optional, user-defined
 *   overrides for malloc functions, then we aren't able to invoke the  normal
 *   heap functions anymore in case the user sets hooks to NULL.
 * - The solution is  to have a  secondary, fully-featured malloc  implementation,
 *   which we do by simply loading `libdlmalloc.so' and using *its* implementation
 *   as fallback to replace  our (then broken one),  prior to also invoking  user-
 *   defined malloc hooks!
 *
 * NOTE: Since  this part happens *before* malloc() normally gets called, we don't
 *       have to worry about `libc_init_malloc_hooks()', since it will *never* get
 *       called! */
typedef void (*LP__MALLOC_INITIALIZE_HOOK)(void);
typedef void (LIBCCALL *LP__FREE_HOOK)(void *ptr, void const *return_address);
typedef void *(LIBCCALL *LP__MALLOC_HOOK)(size_t num_bytes, void const *return_address);
typedef void *(LIBCCALL *LP__REALLOC_HOOK)(void *ptr, size_t num_bytes, void const *return_address);
typedef void *(LIBCCALL *LP__MEMALIGN_HOOK)(size_t alignment, size_t num_bytes, void const *return_address);

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers")
ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) void *LIBCCALL
get_dlmalloc_function(void *lib_dlmalloc, char const *__restrict name) {
	void *result = dlsym(lib_dlmalloc, name);
	if unlikely(!result) {
		char *msg = dlerror();
		FATAL("symbol %s not found in libdlmalloc: %s", name, msg);
	}
	return result;
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") NONNULL((1)) void LIBCCALL
libdlmalloc_so_abi_load(struct user_malloc_abi *__restrict self) {
	void *lib_dlmalloc = dlopen("libdlmalloc.so", RTLD_GLOBAL);
	if (lib_dlmalloc == NULL) {
		char *msg = dlerror();
		FATAL("failed to load libdlmalloc: %s", msg);
	}
	*(void **)&self->uma_malloc = get_dlmalloc_function(lib_dlmalloc, nameof_malloc);
	*(void **)&self->uma_free = get_dlmalloc_function(lib_dlmalloc, nameof_free);
	*(void **)&self->uma_calloc = get_dlmalloc_function(lib_dlmalloc, nameof_calloc);
	*(void **)&self->uma_realloc = get_dlmalloc_function(lib_dlmalloc, nameof_realloc);
	*(void **)&self->uma_realloc_in_place = get_dlmalloc_function(lib_dlmalloc, nameof_realloc_in_place);
	*(void **)&self->uma_memalign = get_dlmalloc_function(lib_dlmalloc, nameof_memalign);
	*(void **)&self->uma_posix_memalign = get_dlmalloc_function(lib_dlmalloc, nameof_posix_memalign);
	*(void **)&self->uma_valloc = get_dlmalloc_function(lib_dlmalloc, nameof_valloc);
	*(void **)&self->uma_pvalloc = get_dlmalloc_function(lib_dlmalloc, nameof_pvalloc);
	*(void **)&self->uma_mallopt = get_dlmalloc_function(lib_dlmalloc, nameof_mallopt);
#if __SIZEOF_INT__ != __SIZEOF_SIZE_T__
	*(void **)&self->uma_mallinfo2 = get_dlmalloc_function(lib_dlmalloc, nameof_mallinfo2);
	self->uma_mallinfo             = &fallback_mallinfo_with_mallinfo2;
#else /* __SIZEOF_INT__ != __SIZEOF_SIZE_T__ */
	*(void **)&self->uma_mallinfo = get_dlmalloc_function(lib_dlmalloc, nameof_mallinfo2);
#endif /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ */
	*(void **)&self->uma_malloc_trim = get_dlmalloc_function(lib_dlmalloc, nameof_malloc_trim);
	*(void **)&self->uma_malloc_usable_size = get_dlmalloc_function(lib_dlmalloc, nameof_malloc_usable_size);
}

/* User-exported malloc hooks */
#undef __malloc_initialize_hook
#undef __free_hook
#undef __malloc_hook
#undef __realloc_hook
#undef __memalign_hook
DECLARE_NOREL_GLOBAL_META(LP__MALLOC_INITIALIZE_HOOK, __malloc_initialize_hook);
DECLARE_NOREL_GLOBAL_META(LP__FREE_HOOK, __free_hook);
DECLARE_NOREL_GLOBAL_META(LP__MALLOC_HOOK, __malloc_hook);
DECLARE_NOREL_GLOBAL_META(LP__REALLOC_HOOK, __realloc_hook);
DECLARE_NOREL_GLOBAL_META(LP__MEMALIGN_HOOK, __memalign_hook);
PRIVATE ATTR_SECTION(".bss.crt.heap.rare_helpers") LP__MALLOC_INITIALIZE_HOOK libc___malloc_initialize_hook = NULL;
PRIVATE ATTR_SECTION(".bss.crt.heap.rare_helpers") LP__FREE_HOOK libc___free_hook = NULL;
PRIVATE ATTR_SECTION(".bss.crt.heap.rare_helpers") LP__MALLOC_HOOK libc___malloc_hook = NULL;
PRIVATE ATTR_SECTION(".bss.crt.heap.rare_helpers") LP__REALLOC_HOOK libc___realloc_hook = NULL;
PRIVATE ATTR_SECTION(".bss.crt.heap.rare_helpers") LP__MEMALIGN_HOOK libc___memalign_hook = NULL;
DEFINE_NOREL_GLOBAL_META(LP__MALLOC_INITIALIZE_HOOK, __malloc_initialize_hook, ".crt.heap.rare_helpers");
DEFINE_NOREL_GLOBAL_META(LP__FREE_HOOK, __free_hook, ".crt.heap.rare_helpers");
DEFINE_NOREL_GLOBAL_META(LP__MALLOC_HOOK, __malloc_hook, ".crt.heap.rare_helpers");
DEFINE_NOREL_GLOBAL_META(LP__REALLOC_HOOK, __realloc_hook, ".crt.heap.rare_helpers");
DEFINE_NOREL_GLOBAL_META(LP__MEMALIGN_HOOK, __memalign_hook, ".crt.heap.rare_helpers");
#define __malloc_initialize_hook GET_NOREL_GLOBAL(__malloc_initialize_hook)
#define __free_hook              GET_NOREL_GLOBAL(__free_hook)
#define __malloc_hook            GET_NOREL_GLOBAL(__malloc_hook)
#define __realloc_hook           GET_NOREL_GLOBAL(__realloc_hook)
#define __memalign_hook          GET_NOREL_GLOBAL(__memalign_hook)


/* Internal hook-core functions (called when user-defined malloc hooks aren't defined) */
PRIVATE ATTR_SECTION(".bss.crt.heap.rare_helpers") LPMALLOC libc_hookcore_malloc = NULL;
PRIVATE ATTR_SECTION(".bss.crt.heap.rare_helpers") LPFREE libc_hookcore_free = NULL;
PRIVATE ATTR_SECTION(".bss.crt.heap.rare_helpers") LPCALLOC libc_hookcore_calloc = NULL;
PRIVATE ATTR_SECTION(".bss.crt.heap.rare_helpers") LPREALLOC libc_hookcore_realloc = NULL;
PRIVATE ATTR_SECTION(".bss.crt.heap.rare_helpers") LPREALLOC_IN_PLACE libc_hookcore_realloc_in_place = NULL;
PRIVATE ATTR_SECTION(".bss.crt.heap.rare_helpers") LPMEMALIGN libc_hookcore_memalign = NULL;
PRIVATE ATTR_SECTION(".bss.crt.heap.rare_helpers") LPPOSIX_MEMALIGN libc_hookcore_posix_memalign = NULL;
PRIVATE ATTR_SECTION(".bss.crt.heap.rare_helpers") LPVALLOC libc_hookcore_valloc = NULL;
PRIVATE ATTR_SECTION(".bss.crt.heap.rare_helpers") LPPVALLOC libc_hookcore_pvalloc = NULL;
PRIVATE ATTR_SECTION(".bss.crt.heap.rare_helpers") LPMEMDUP libc_hookcore_memdup = NULL;
PRIVATE ATTR_SECTION(".bss.crt.heap.rare_helpers") LPMEMCDUP libc_hookcore_memcdup = NULL;
PRIVATE ATTR_SECTION(".bss.crt.heap.rare_helpers") LPREALLOCARRAY libc_hookcore_reallocarray = NULL;
PRIVATE ATTR_SECTION(".bss.crt.heap.rare_helpers") LPRECALLOC libc_hookcore_recalloc = NULL;
PRIVATE ATTR_SECTION(".bss.crt.heap.rare_helpers") LPRECALLOCV libc_hookcore_recallocv = NULL;

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") void LIBCCALL
libc_doinvoke___malloc_initialize_hook(void) {
	LP__MALLOC_INITIALIZE_HOOK hook = atomic_read(&__malloc_initialize_hook);
	if (hook != NULL)
		(*hook)();
}

PRIVATE ATTR_SECTION(".bss.crt.heap.rare_helpers")
pthread_once_t libc_didinvoke___malloc_initialize_hook = PTHREAD_ONCE_INIT;

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") void
libc_invoke___malloc_initialize_hook(void) {
	pthread_once(&libc_didinvoke___malloc_initialize_hook,
	             &libc_doinvoke___malloc_initialize_hook);
}


PRIVATE ATTR_SECTION(".data.crt.heap.rare_helpers")
pthread_key_t libc_in_malloc_hook_key = PTHREAD_ONCE_KEY_NP;

/* Called (and must return true) before a user-defined malloc hook is invoked. */
PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") bool LIBCCALL
libc_malloc_hook_begin(void) {
	void **p_tls;
	if unlikely(pthread_key_create_once_np(&libc_in_malloc_hook_key, NULL) != EOK)
		return false; /* Failed to initialize TLS */
	p_tls = pthread_getspecificptr_np(libc_in_malloc_hook_key);
	if unlikely(p_tls == NULL)
		return false; /* Failed to allocate TLS */
	if (*p_tls != (void *)0)
		return false; /* Already active */
	*p_tls = (void *)-1;
	return true;
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") void
NOTHROW(LIBCCALL libc_malloc_hook_end)(void) {
	void **p_tls = pthread_getspecificptr_np(libc_in_malloc_hook_key);
	assertf(p_tls != NULL, "Should have already been allocated by `libc_malloc_hook_begin()'");
	assertf(*p_tls == (void *)-1, "Then how did `libc_malloc_hook_begin()' return true?");
	*p_tls = (void *)0;
}



PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers")
void *LIBCCALL libc_hooked_malloc(size_t num_bytes) {
	LP__MALLOC_HOOK hook;
	libc_invoke___malloc_initialize_hook();
	hook = atomic_read(&__malloc_hook);
	if (hook != NULL && libc_malloc_hook_begin()) {
		RAII_FINALLY { libc_malloc_hook_end(); };
		return (*hook)(num_bytes, __builtin_return_address(0));
	}
	return (*libc_hookcore_malloc)(num_bytes);
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers")
void LIBCCALL libc_hooked_free(void *ptr) {
	LP__FREE_HOOK hook;
	libc_invoke___malloc_initialize_hook();
	hook = atomic_read(&__free_hook);
	if (hook != NULL && libc_malloc_hook_begin()) {
		RAII_FINALLY { libc_malloc_hook_end(); };
		(*hook)(ptr, __builtin_return_address(0));
	} else {
		(*libc_hookcore_free)(ptr);
	}
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers")
void *LIBCCALL libc_hooked_calloc(size_t elem_count, size_t elem_size) {
	LP__MALLOC_HOOK hook;
	libc_invoke___malloc_initialize_hook();
	hook = atomic_read(&__malloc_hook);
	if (hook != NULL && libc_malloc_hook_begin()) {
		void *result;
		size_t num_bytes;
		RAII_FINALLY { libc_malloc_hook_end(); };
		if (OVERFLOW_UMUL(elem_count, elem_size, &num_bytes))
			num_bytes = (size_t)-1;
		result = (*hook)(num_bytes, __builtin_return_address(0));
		if (result)
			bzero(result, num_bytes);
		return result;
	}
	return (*libc_hookcore_calloc)(elem_count, elem_size);
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers")
void *LIBCCALL libc_hooked_realloc(void *ptr, size_t num_bytes) {
	LP__REALLOC_HOOK hook;
	libc_invoke___malloc_initialize_hook();
	hook = atomic_read(&__realloc_hook);
	if (hook != NULL && libc_malloc_hook_begin()) {
		RAII_FINALLY { libc_malloc_hook_end(); };
		return (*hook)(ptr, num_bytes, __builtin_return_address(0));
	}
	return (*libc_hookcore_realloc)(ptr, num_bytes);
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers")
void *LIBCCALL libc_hooked_realloc_in_place(void *ptr, size_t num_bytes) {
	LP__REALLOC_HOOK hook;
	libc_invoke___malloc_initialize_hook();
	hook = atomic_read(&__realloc_hook);
	if (hook != NULL && libc_malloc_hook_begin()) {
		size_t usable_size;
		RAII_FINALLY { libc_malloc_hook_end(); };
		usable_size = malloc_usable_size(ptr);
		if (num_bytes <= usable_size)
			return ptr; /* Can't actually realloc in this case... */
		return NULL;
	}
	return (*libc_hookcore_realloc_in_place)(ptr, num_bytes);
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers")
void *LIBCCALL libc_hooked_memalign(size_t alignment, size_t num_bytes) {
	LP__MEMALIGN_HOOK hook;
	libc_invoke___malloc_initialize_hook();
	hook = atomic_read(&__memalign_hook);
	if (hook != NULL && libc_malloc_hook_begin()) {
		RAII_FINALLY { libc_malloc_hook_end(); };
		return (*hook)(alignment, num_bytes, __builtin_return_address(0));
	}
	return (*libc_hookcore_memalign)(alignment, num_bytes);
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers")
errno_t LIBCCALL libc_hooked_posix_memalign(void **p_ptr, size_t alignment, size_t num_bytes) {
	LP__MEMALIGN_HOOK hook;
	libc_invoke___malloc_initialize_hook();
	hook = atomic_read(&__memalign_hook);
	if (hook != NULL && libc_malloc_hook_begin()) {
		void *result;
		errno_t error, saved_error;
		RAII_FINALLY { libc_malloc_hook_end(); };
		saved_error = libc_geterrno();
		result = (*hook)(alignment, num_bytes, __builtin_return_address(0));
		if (result != NULL) {
			*p_ptr = result;
			return 0;
		}
		error = libc_geterrno();
		libc_seterrno(saved_error);
		if unlikely(!error)
			error = ENOMEM;
		return error;
	}
	return (*libc_hookcore_posix_memalign)(p_ptr, alignment, num_bytes);
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers")
void *LIBCCALL libc_hooked_valloc(size_t num_bytes) {
	LP__MEMALIGN_HOOK hook;
	libc_invoke___malloc_initialize_hook();
	hook = atomic_read(&__memalign_hook);
	if (hook != NULL && libc_malloc_hook_begin()) {
		RAII_FINALLY { libc_malloc_hook_end(); };
		return (*hook)(getpagesize(), num_bytes, __builtin_return_address(0));
	}
	return (*libc_hookcore_valloc)(num_bytes);
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers")
void *LIBCCALL libc_hooked_pvalloc(size_t num_bytes) {
	LP__MEMALIGN_HOOK hook;
	libc_invoke___malloc_initialize_hook();
	hook = atomic_read(&__memalign_hook);
	if (hook != NULL && libc_malloc_hook_begin()) {
		size_t ps;
		RAII_FINALLY { libc_malloc_hook_end(); };
		ps = getpagesize();
		if (OVERFLOW_UADD(num_bytes, ps - 1, &num_bytes))
			num_bytes = (size_t)-1;
		num_bytes &= ~(ps - 1);
		return (*hook)(ps, num_bytes, __builtin_return_address(0));
	}
	return (*libc_hookcore_pvalloc)(num_bytes);
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers")
void *LIBCCALL libc_hooked_memdup(void const *ptr, size_t n_bytes) {
	LP__MALLOC_HOOK hook;
	libc_invoke___malloc_initialize_hook();
	hook = atomic_read(&__malloc_hook);
	if (hook != NULL && libc_malloc_hook_begin()) {
		void *result;
		RAII_FINALLY { libc_malloc_hook_end(); };
		result = (*hook)(n_bytes, __builtin_return_address(0));
		if likely(result)
			result = memcpy(result, ptr, n_bytes);
		return result;
	}
	return (*libc_hookcore_memdup)(ptr, n_bytes);
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers")
void *LIBCCALL libc_hooked_memcdup(void const *ptr, int needle, size_t n_bytes) {
	LP__MALLOC_HOOK hook;
	libc_invoke___malloc_initialize_hook();
	hook = atomic_read(&__malloc_hook);
	if (hook != NULL && libc_malloc_hook_begin()) {
		void *result;
		RAII_FINALLY { libc_malloc_hook_end(); };
		if likely(n_bytes) {
			void const *endaddr;
			endaddr = memchr(ptr, needle, n_bytes - 1);
			if (endaddr)
				n_bytes = ((uintptr_t)endaddr - (uintptr_t)ptr) + 1;
		}
		result = (*hook)(n_bytes, __builtin_return_address(0));
		if likely(result)
			result = memcpy(result, ptr, n_bytes);
		return result;
	}
	return (*libc_hookcore_memcdup)(ptr, needle, n_bytes);
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers")
void *LIBCCALL libc_hooked_reallocarray(void *ptr, size_t elem_count, size_t elem_size) {
	LP__REALLOC_HOOK hook;
	libc_invoke___malloc_initialize_hook();
	hook = atomic_read(&__realloc_hook);
	if (hook != NULL && libc_malloc_hook_begin()) {
		size_t num_bytes;
		RAII_FINALLY { libc_malloc_hook_end(); };
		if (OVERFLOW_UMUL(elem_count, elem_size, &num_bytes))
			num_bytes = (size_t)-1;
		return (*hook)(ptr, num_bytes, __builtin_return_address(0));
	}
	return (*libc_hookcore_reallocarray)(ptr, elem_count, elem_size);
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers")
void *LIBCCALL libc_hooked_recalloc(void *mallptr, size_t num_bytes) {
	LP__REALLOC_HOOK hook;
	libc_invoke___malloc_initialize_hook();
	hook = atomic_read(&__realloc_hook);
	if (hook != NULL && libc_malloc_hook_begin()) {
		void *result;
		size_t old_size;
		RAII_FINALLY { libc_malloc_hook_end(); };
		old_size = malloc_usable_size(mallptr);
		result   = (*hook)(mallptr, num_bytes, __builtin_return_address(0));
		if likely(result) {
			size_t new_size = malloc_usable_size(result);
			if (old_size < new_size)
				bzero((byte_t *)result + old_size, new_size - old_size);
		}
		return result;
	}
	return (*libc_hookcore_recalloc)(mallptr, num_bytes);
}

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers")
void *LIBCCALL libc_hooked_recallocv(void *mallptr, size_t elem_count, size_t elem_size) {
	LP__REALLOC_HOOK hook;
	libc_invoke___malloc_initialize_hook();
	hook = atomic_read(&__realloc_hook);
	if (hook != NULL && libc_malloc_hook_begin()) {
		void *result;
		size_t old_size;
		size_t num_bytes;
		RAII_FINALLY { libc_malloc_hook_end(); };
		if (OVERFLOW_UMUL(elem_count, elem_size, &num_bytes))
			num_bytes = (size_t)-1;
		old_size = malloc_usable_size(mallptr);
		result   = (*hook)(mallptr, num_bytes, __builtin_return_address(0));
		if likely(result) {
			size_t new_size = malloc_usable_size(result);
			if (old_size < new_size)
				bzero((byte_t *)result + old_size, new_size - old_size);
		}
		return result;
	}
	return (*libc_hookcore_recallocv)(mallptr, elem_count, elem_size);
}



PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") void
libc_malloc_hooks_doinit(void) {
	struct user_malloc_abi abi;
	syslog(LOG_INFO, "[libc] Enable support for `__malloc_hook'\n");

	/* Check if malloc gets defined by the main application. */
	bzero(&abi, sizeof(abi));
	*(void **)&abi.uma_malloc = user_malloc_abi_dlsym(nameof_free, (void *)&libc_free);
	if (abi.uma_malloc != NULL) {
		user_malloc_abi_load(&abi);
	} else {
		/* If not, load our own malloc through use of `libdlmalloc.so' */
		libdlmalloc_so_abi_load(&abi);

		/* Define "optional" parts of the ABI */
		abi.uma_memdup       = &libc_hooked_memdup;
		abi.uma_memcdup      = &libc_hooked_memcdup;
		abi.uma_reallocarray = &libc_hooked_reallocarray;
		abi.uma_recalloc     = &libc_hooked_recalloc;
		abi.uma_recallocv    = &libc_hooked_recallocv;
	}

	/* Remember abi-pointers and inject wrappers that
	 * will  invoke  user-defined hooks  (if defined) */
#define INJECT_HOOK(name) \
	(libc_hookcore_##name = abi.uma_##name, abi.uma_##name = &libc_hooked_##name)
	INJECT_HOOK(malloc);
	INJECT_HOOK(free);
	INJECT_HOOK(calloc);
	INJECT_HOOK(realloc);
	INJECT_HOOK(realloc_in_place);
	INJECT_HOOK(memalign);
	INJECT_HOOK(posix_memalign);
	INJECT_HOOK(valloc);
	INJECT_HOOK(pvalloc);
	INJECT_HOOK(memdup);
	INJECT_HOOK(memcdup);
	INJECT_HOOK(reallocarray);
	INJECT_HOOK(recalloc);
	INJECT_HOOK(recallocv);
#undef INJECT_HOOK

	/* Install the ABI */
	user_malloc_abi_install(&abi);
}


PRIVATE ATTR_SECTION(".bss.crt.heap.rare_helpers")
pthread_once_t libc_malloc_hooks_didinit = PTHREAD_ONCE_INIT;

PRIVATE ATTR_SECTION(".text.crt.heap.rare_helpers") void
libc_malloc_hooks_init(void) {
	pthread_once(&libc_malloc_hooks_didinit,
	             &libc_malloc_hooks_doinit);
}

/* Define IDATA symbols for Glibc malloc hooks. When an application
 * resolves  one  of these,  `libc_malloc_hooks_init()'  is called. */
#undef __malloc_initialize_hook
#undef __free_hook
#undef __malloc_hook
#undef __realloc_hook
#undef __memalign_hook
DEFINE_PUBLIC_IDATA(__malloc_initialize_hook, libc_resolve___malloc_initialize_hook, __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA(__free_hook, libc_resolve___free_hook, __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA(__malloc_hook, libc_resolve___malloc_hook, __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA(__realloc_hook, libc_resolve___realloc_hook, __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA(__memalign_hook, libc_resolve___memalign_hook, __SIZEOF_POINTER__);

INTERN ATTR_SECTION(".text.crt.heap.rare_helpers")
LP__MALLOC_INITIALIZE_HOOK *LIBCCALL libc_resolve___malloc_initialize_hook(void) {
	libc_malloc_hooks_init();
	return &libc___malloc_initialize_hook;
}

INTERN ATTR_SECTION(".text.crt.heap.rare_helpers")
LP__FREE_HOOK *LIBCCALL libc_resolve___free_hook(void) {
	libc_malloc_hooks_init();
	return &libc___free_hook;
}

INTERN ATTR_SECTION(".text.crt.heap.rare_helpers")
LP__MALLOC_HOOK *LIBCCALL libc_resolve___malloc_hook(void) {
	libc_malloc_hooks_init();
	return &libc___malloc_hook;
}

INTERN ATTR_SECTION(".text.crt.heap.rare_helpers")
LP__REALLOC_HOOK *LIBCCALL libc_resolve___realloc_hook(void) {
	libc_malloc_hooks_init();
	return &libc___realloc_hook;
}

INTERN ATTR_SECTION(".text.crt.heap.rare_helpers")
LP__MEMALIGN_HOOK *LIBCCALL libc_resolve___memalign_hook(void) {
	libc_malloc_hooks_init();
	return &libc___memalign_hook;
}

#else /* __ARCH_REDIRECT_MAXBYTES != 0 */
INTERN ATTR_SECTION(".text.crt.heap.malloc") int LIBCCALL
libc_init_malloc_hooks(void) {
	COMPILER_IMPURE();
	return 0;
}
#endif /* __ARCH_REDIRECT_MAXBYTES == 0 */

/* These are never used by libc, but need to be defined for binary compatibility. */
INTERN ATTR_SECTION(".bss.crt.heap.rare_helpers") void (*libc___after_morecore_hook)(void)  = NULL;
INTERN ATTR_SECTION(".bss.crt.heap.rare_helpers") void *(*libc___morecore)(ptrdiff_t delta) = NULL;
DEFINE_PUBLIC_ALIAS(__after_morecore_hook, libc___after_morecore_hook);
DEFINE_PUBLIC_ALIAS(__morecore, libc___morecore);



/*[[[head:libc_memcdup,hash:CRC-32=0xe2f0ddeb]]]*/
INTERN ATTR_SECTION(".text.crt.heap.rare_helpers") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) ATTR_INS(1, 3) void *
NOTHROW_NCX(LIBCCALL libc_memcdup)(void const *__restrict ptr,
                                   int needle,
                                   size_t n_bytes)
/*[[[body:libc_memcdup]]]*/
{
	if likely(n_bytes) {
		void const *endaddr;
		endaddr = memchr(ptr, needle, n_bytes - 1);
		if (endaddr)
			n_bytes = ((uintptr_t)endaddr - (uintptr_t)ptr) + 1;
	}
	return memdup(ptr, n_bytes);
}
/*[[[end:libc_memcdup]]]*/

/*[[[head:libc_memdup,hash:CRC-32=0xcbec1ab6]]]*/
INTERN ATTR_SECTION(".text.crt.heap.rare_helpers") ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) ATTR_INS(1, 2) void *
NOTHROW_NCX(LIBCCALL libc_memdup)(void const *__restrict ptr,
                                  size_t n_bytes)
/*[[[body:libc_memdup]]]*/
{
	void *result;
	result = malloc(n_bytes);
	if likely(result)
		memcpy(result, ptr, n_bytes);
	return result;
}
/*[[[end:libc_memdup]]]*/

/*[[[head:libc_reallocarray,hash:CRC-32=0xff244eca]]]*/
INTERN ATTR_SECTION(".text.crt.heap.rare_helpers") ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *
NOTHROW_NCX(LIBCCALL libc_reallocarray)(void *ptr,
                                        size_t elem_count,
                                        size_t elem_size)
/*[[[body:libc_reallocarray]]]*/
/*AUTO*/{
	size_t total_bytes;
	if unlikely(__hybrid_overflow_umul(elem_count, elem_size, &total_bytes))
		total_bytes = (size_t)-1; /* Force down-stream failure */
	return realloc(ptr, total_bytes);
}
/*[[[end:libc_reallocarray]]]*/

/*[[[head:libc_recalloc,hash:CRC-32=0x6198e8db]]]*/
INTERN ATTR_SECTION(".text.crt.heap.rare_helpers") ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) void *
NOTHROW_NCX(LIBCCALL libc_recalloc)(void *mallptr,
                                    size_t num_bytes)
/*[[[body:libc_recalloc]]]*/
/*AUTO*/{
	void *result;
	size_t oldsize;
	oldsize = malloc_usable_size(mallptr);
	result  = realloc(mallptr, num_bytes);
	if likely(result) {
		if (num_bytes > oldsize)
			bzero((byte_t *)result + oldsize, num_bytes - oldsize);
	}
	return result;
}
/*[[[end:libc_recalloc]]]*/

/*[[[head:libc_recallocv,hash:CRC-32=0x5fcdcb24]]]*/
INTERN ATTR_SECTION(".text.crt.heap.rare_helpers") ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *
NOTHROW_NCX(LIBCCALL libc_recallocv)(void *mallptr,
                                     size_t elem_count,
                                     size_t elem_size)
/*[[[body:libc_recallocv]]]*/
/*AUTO*/{
	void *result;
	size_t total_bytes, oldsize;
	oldsize = malloc_usable_size(mallptr);
	if unlikely(__hybrid_overflow_umul(elem_count, elem_size, &total_bytes))
		total_bytes = (size_t)-1; /* Force down-stream failure */
	result = realloc(mallptr, total_bytes);
	if likely(result) {
		if (total_bytes > oldsize)
			bzero((byte_t *)result + oldsize, total_bytes - oldsize);
	}
	return result;
}
/*[[[end:libc_recallocv]]]*/





/*[[[start:exports,hash:CRC-32=0xfdd7a9ce]]]*/
DEFINE_PUBLIC_ALIAS(__memdup, libc_memdup);
DEFINE_PUBLIC_ALIAS(memdup, libc_memdup);
DEFINE_PUBLIC_ALIAS(__memcdup, libc_memcdup);
DEFINE_PUBLIC_ALIAS(memcdup, libc_memcdup);
DEFINE_PUBLIC_ALIAS(__libc_reallocarray, libc_reallocarray);
DEFINE_PUBLIC_ALIAS(reallocarray, libc_reallocarray);
DEFINE_PUBLIC_ALIAS(recalloc, libc_recalloc);
DEFINE_PUBLIC_ALIAS(_recalloc, libc_recallocv);
DEFINE_PUBLIC_ALIAS(recallocv, libc_recallocv);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_MALLOC_C */
