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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_SLAB_C
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_SLAB_C 1
#define NO_INSTRUMENT_KMALLOC
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/malloc-defs.h>
#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS

#include <kernel/driver-param.h>
#include <kernel/heap.h>
#include <kernel/malloc.h>

#include <hybrid/byteswap.h>
#include <hybrid/unaligned.h>

DECL_BEGIN

PRIVATE ATTR_FREETEXT void KCALL
override_slab_malloc(byte_t *p_slab_malloc) {
	/* slab_malloc[SZ]:
	 *     xorP %Pax, %Pax
	 *     ret   IF_32($4) */
#ifdef __x86_64__
	*p_slab_malloc++ = 0x48; /* REX */
#endif /* __x86_64__ */
	*p_slab_malloc++ = 0x31; /* xorl */
	*p_slab_malloc++ = 0xc0; /* %eax, %eax */
#ifdef __x86_64__
	*p_slab_malloc++ = 0xc3; /* ret */
#else /* __x86_64__ */
	*p_slab_malloc++ = 0xc2; /* ret $4 */
	*p_slab_malloc++ = 4;
	*p_slab_malloc++ = 0;
#endif /* !__x86_64__ */
}

PRIVATE ATTR_FREETEXT void KCALL
override_slab_kmalloc_x(byte_t *p_slab_kmalloc, size_t sz,
                        byte_t *kmalloc_xnx) {
	/* slab_kmalloc[SZ]:
	 * >> #ifdef __x86_64__
	 * >>     movl %edi, %esi // flags
	 * >>     movl $sz,  %edi // num_bytes
	 * >> #else
	 * >>     // NOTE: Because kmalloc is STDCALL, it will cleanup the +1
	 * >>     //       additional word that we've pushed onto the stack here.
	 * >>     popl  %eax
	 * >>     pushl  $sz
	 * >>     pushl %eax
	 * >> #endif
	 * >>     jmp   kmalloc */
#ifdef __x86_64__
	*p_slab_kmalloc++ = 0x89; /* movl */
	*p_slab_kmalloc++ = 0xfe; /* %edi, %esi */
	*p_slab_kmalloc++ = 0xbf; /* movl $..., %edi */
	UNALIGNED_SETLE32((u32 *)p_slab_kmalloc, (u32)sz);
	p_slab_kmalloc += 4;
#else /* __x86_64__ */
	*p_slab_kmalloc++ = 0x58; /* popl %eax */
	*p_slab_kmalloc++ = 0x68; /* pushl $... */
	UNALIGNED_SETLE32((u32 *)p_slab_kmalloc, (u32)sz);
	p_slab_kmalloc += 4;
	*p_slab_kmalloc++ = 0x50; /* pushl %eax */
#endif /* !__x86_64__ */
	*p_slab_kmalloc++ = 0xe9; /* jmp ... */
	UNALIGNED_SETLE32((u32 *)p_slab_kmalloc,
	                  (u32)(s32)((kmalloc_xnx) -
	                             (p_slab_kmalloc + 4)));
}

PRIVATE ATTR_FREETEXT void KCALL
override_slab_kmalloc(byte_t *p_slab_kmalloc, size_t sz) {
	override_slab_kmalloc_x(p_slab_kmalloc, sz, (byte_t *)(void *)&__os_malloc);
}

PRIVATE ATTR_FREETEXT void KCALL
override_slab_kmalloc_nx(byte_t *p_slab_kmalloc_nx, size_t sz) {
	override_slab_kmalloc_x(p_slab_kmalloc_nx, sz, (byte_t *)(void *)&__os_malloc_nx);
}

struct slab_api {
	size_t  slab_size;         /* Slab size. */
	byte_t *p_slab_malloc;     /* [1..1] Pointer to `slab_malloc[slab_size]' */
	byte_t *p_slab_kmalloc;    /* [1..1] Pointer to `slab_kmalloc[slab_size]' */
	byte_t *p_slab_kmalloc_nx; /* [1..1] Pointer to `slab_kmalloc_nx[slab_size]' */
};

PRIVATE ATTR_FREERODATA struct slab_api const slab_api_functions[] = {
#define OVERRIDE_SLAB_FUNCTIONS(sz, _)         \
	{                                          \
		sz,                                    \
		(byte_t *)(void *)&slab_malloc##sz,    \
		(byte_t *)(void *)&slab_kmalloc##sz,   \
		(byte_t *)(void *)&slab_kmalloc_nx##sz \
	},
	SLAB_FOREACH_SIZE(OVERRIDE_SLAB_FUNCTIONS, _)
#undef OVERRIDE_SLAB_FUNCTIONS
};

PRIVATE ATTR_USED ATTR_FREETEXT void KCALL kernel_disable_slab(void) {
	unsigned int i;
	for (i = 0; i < COMPILER_LENOF(slab_api_functions); ++i) {
		override_slab_malloc(slab_api_functions[i].p_slab_malloc);
		override_slab_kmalloc(slab_api_functions[i].p_slab_kmalloc,
		                      slab_api_functions[i].slab_size);
		override_slab_kmalloc_nx(slab_api_functions[i].p_slab_kmalloc_nx,
		                         slab_api_functions[i].slab_size);
	}
}

DEFINE_VERY_EARLY_KERNEL_COMMANDLINE_OPTION(kernel_disable_slab,
                                            KERNEL_COMMANDLINE_OPTION_TYPE_PRESENT,
                                            "noslab");

DECL_END

#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_SLAB_C */
