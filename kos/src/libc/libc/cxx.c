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
#ifndef GUARD_LIBC_LIBC_CXX_C
#define GUARD_LIBC_LIBC_CXX_C 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <kos/except.h>
#include <kos/types.h>

#include <atomic.h>
#include <dlfcn.h>
#include <malloc.h>
#include <stdlib.h>

#include "cxx.h"
#include "dl.h"

/* Various functions primarily meant for c++ (so you don't have to necessarily link against libstdc++) */

#ifdef __CC__
DECL_BEGIN

#define SECTION ".crt.compat.cxx.malloc"

#define dynsym(name) (*libc_resolve_##name())
#define DEFINE_dynsym(name)                                                            \
	PRIVATE ATTR_SECTION(".rodata" SECTION) char const libc_name_##name[] = #name;     \
	PRIVATE ATTR_SECTION(".bss" SECTION) typeof(libc_##name) *libc_pdyn_##name = NULL; \
	PRIVATE ATTR_SECTION(".text" SECTION) ATTR_RETNONNULL ATTR_CONST WUNUSED           \
	typeof(libc_##name) *NOTHROW(LIBCCALL libc_resolve_##name)(void) {                 \
		typeof(libc_##name) *result = libc_pdyn_##name;                                \
		if (result == NULL) {                                                          \
			*(void **)&result = dlsym(RTLD_DEFAULT, libc_name_##name);                 \
			if (result == NULL)                                                        \
				result = &libc_##name;                                                 \
			atomic_write(&libc_pdyn_##name, result);                                   \
		}                                                                              \
		return result;                                                                 \
	}


/* Lazy dlsym() wrappers. */
DEFINE_dynsym(_ZSt15get_new_handlerv); /* std::get_new_handler() */
DEFINE_dynsym(_Znwm);                  /* operator new(unsigned long) */
DEFINE_dynsym(_ZnwmSt11align_val_t);   /* operator new(unsigned long, std::align_val_t) */



PRIVATE ATTR_SECTION(".bss.crt.compat.cxx.malloc") cxx_new_handler_t libc_new_handler = NULL;

DEFINE_PUBLIC_WEAK_ALIAS(_ZSt15get_new_handlerv, libc__ZSt15get_new_handlerv);
INTDEF ATTR_SECTION(".text.crt.compat.cxx.malloc") ATTR_PURE WUNUSED cxx_new_handler_t
NOTHROW(LIBCCALL libc__ZSt15get_new_handlerv)(void) {
	return atomic_read(&libc_new_handler);
}

DEFINE_PUBLIC_WEAK_ALIAS(_ZSt15set_new_handlerPFvvE, libc__ZSt15set_new_handlerPFvvE);
INTDEF ATTR_SECTION(".text.crt.compat.cxx.malloc") WUNUSED cxx_new_handler_t
NOTHROW(LIBCCALL libc__ZSt15set_new_handlerPFvvE)(cxx_new_handler_t handler) {
	return atomic_xch(&libc_new_handler, handler);
}


ATTR_SECTION(".text.crt.compat.cxx.malloc")
PRIVATE ATTR_NORETURN void throw_bad_alloc(size_t num_bytes) {
	/* Intentionally don't use "normal" c++ exceptions here (though
	 * note that KOS's throw can be caught with c++  "catch(...)"):
	 *
	 * Reason is that we only get here when the caller didn't link
	 * against libstdc++, meaning the "normal" suite of c++  utils
	 * isn't available anyways. */
	THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, num_bytes);
}

PRIVATE ATTR_SECTION(".text.crt.compat.cxx.malloc") void LIBCCALL
call_new_handler_or_throw_bad_alloc(size_t num_bytes) {
	cxx_new_handler_t handler = dynsym(_ZSt15get_new_handlerv)();
	if (!handler)
		throw_bad_alloc(num_bytes);
	(*handler)();
}

DEFINE_PUBLIC_WEAK_ALIAS(_Znam, libc__Znwm); /* operator new[](unsigned long) */
DEFINE_PUBLIC_WEAK_ALIAS(_Znwm, libc__Znwm); /* operator new(unsigned long) */
INTERN ATTR_SECTION(".text.crt.compat.cxx.malloc") ATTR_MALLOC WUNUSED void *LIBCCALL
libc__Znwm(size_t num_bytes) {
	void *result;
	while ((result = malloc(num_bytes)) == NULL)
		call_new_handler_or_throw_bad_alloc(num_bytes);
	return result;
}

DEFINE_PUBLIC_WEAK_ALIAS(_ZnamSt11align_val_t, libc__ZnwmSt11align_val_t); /* operator new[](unsigned long, std::align_val_t) */
DEFINE_PUBLIC_WEAK_ALIAS(_ZnwmSt11align_val_t, libc__ZnwmSt11align_val_t); /* operator new(unsigned long, std::align_val_t) */
INTERN ATTR_SECTION(".text.crt.compat.cxx.malloc") ATTR_MALLOC WUNUSED void *LIBCCALL
libc__ZnwmSt11align_val_t(size_t num_bytes, size_t min_alignment) {
	void *result;
	if (min_alignment & (min_alignment - 1))
		throw_bad_alloc((size_t)-1);
	while ((result = aligned_alloc(num_bytes, min_alignment)) == NULL)
		call_new_handler_or_throw_bad_alloc(num_bytes);
	return result;
}

DEFINE_PUBLIC_WEAK_ALIAS(_ZnamRKSt9nothrow_t, libc__ZnwmRKSt9nothrow_t); /* operator new[](unsigned long, std::nothrow_t const&) */
DEFINE_PUBLIC_WEAK_ALIAS(_ZnwmRKSt9nothrow_t, libc__ZnwmRKSt9nothrow_t); /* operator new(unsigned long, std::nothrow_t const&) */
INTERN ATTR_SECTION(".text.crt.compat.cxx.malloc") ATTR_MALLOC WUNUSED void *LIBCCALL
libc__ZnwmRKSt9nothrow_t(size_t num_bytes, void *) {
	try {
		return dynsym(_Znwm)(num_bytes);
	} catch (...) {
		return NULL;
	}
}

DEFINE_PUBLIC_WEAK_ALIAS(_ZnamSt11align_val_tRKSt9nothrow_t, libc__ZnwmSt11align_val_tRKSt9nothrow_t); /* operator new[](unsigned long, std::align_val_t, std::nothrow_t const&) */
DEFINE_PUBLIC_WEAK_ALIAS(_ZnwmSt11align_val_tRKSt9nothrow_t, libc__ZnwmSt11align_val_tRKSt9nothrow_t); /* operator new(unsigned long, std::align_val_t, std::nothrow_t const&) */
INTERN ATTR_SECTION(".text.crt.compat.cxx.malloc") ATTR_MALLOC WUNUSED void *LIBCCALL
libc__ZnwmSt11align_val_tRKSt9nothrow_t(size_t num_bytes, size_t min_alignment, void *) {
	try {
		return dynsym(_ZnwmSt11align_val_t)(num_bytes, min_alignment);
	} catch (...) {
		return NULL;
	}
}



#ifndef __LIBCCALL_CALLER_CLEANUP
DEFINE_PUBLIC_WEAK_ALIAS(_ZdaPvRKSt9nothrow_t, libc__ZdlPvRKSt9nothrow_t);                               /* operator delete[](void*, std::nothrow_t const&) */
DEFINE_PUBLIC_WEAK_ALIAS(_ZdaPvSt11align_val_t, libc__ZdlPvSt11align_val_t);                             /* operator delete[](void*, std::align_val_t) */
DEFINE_PUBLIC_WEAK_ALIAS(_ZdaPvmSt11align_val_t, libc__ZdlPvmSt11align_val_t);                           /* operator delete[](void*, unsigned long, std::align_val_t) */
DEFINE_PUBLIC_WEAK_ALIAS(_ZdaPvSt11align_val_tRKSt9nothrow_t, libc__ZdlPvSt11align_val_tRKSt9nothrow_t); /* operator delete[](void*, std::align_val_t, std::nothrow_t const&) */

/* operator delete(void*, std::nothrow_t const&) */
DEFINE_PUBLIC_WEAK_ALIAS(_ZdlPvRKSt9nothrow_t, libc__ZdlPvRKSt9nothrow_t);
INTERN ATTR_SECTION(".text.crt.compat.cxx.malloc") void
libc__ZdlPvRKSt9nothrow_t(void *mallptr, void *) {
	free(mallptr);
}

/* operator delete(void*, std::align_val_t) */
DEFINE_PUBLIC_WEAK_ALIAS(_ZdlPvSt11align_val_t, libc__ZdlPvSt11align_val_t);
INTERN ATTR_SECTION(".text.crt.compat.cxx.malloc") void
libc__ZdlPvSt11align_val_t(void *mallptr, size_t) {
	free(mallptr);
}

/* operator delete(void*, unsigned long, std::align_val_t) */
DEFINE_PUBLIC_WEAK_ALIAS(_ZdlPvmSt11align_val_t, libc__ZdlPvmSt11align_val_t);
INTERN ATTR_SECTION(".text.crt.compat.cxx.malloc") void
libc__ZdlPvmSt11align_val_t(void *mallptr, size_t, size_t) {
	free(mallptr);
}

/* operator delete(void*, std::align_val_t, std::nothrow_t const&) */
DEFINE_PUBLIC_WEAK_ALIAS(_ZdlPvSt11align_val_tRKSt9nothrow_t, libc__ZdlPvSt11align_val_tRKSt9nothrow_t);
INTERN ATTR_SECTION(".text.crt.compat.cxx.malloc") void
libc__ZdlPvSt11align_val_tRKSt9nothrow_t(void *mallptr, size_t, void *) {
	free(mallptr);
}
#endif /* __LIBCCALL_CALLER_CLEANUP */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_LIBC_LIBC_CXX_C */
