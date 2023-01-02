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
#ifndef GUARD_MODPE_PE_H
#define GUARD_MODPE_PE_H 1

#include <kernel/compiler.h>

#include <kernel/execabi.h>
#include <kernel/types.h>

#include <hybrid/host.h>

#include <nt/pe.h>


DECL_BEGIN

#if defined(__x86_64__)
#define IMAGE_FILE_MACHINE_HOST IMAGE_FILE_MACHINE_AMD64
#elif defined(__i386__)
#define IMAGE_FILE_MACHINE_HOST IMAGE_FILE_MACHINE_I386
#elif defined(__arm__)
#define IMAGE_FILE_MACHINE_HOST IMAGE_FILE_MACHINE_ARM
#else
#error "Unknown host"
#endif

typedef struct _IMAGE_NT_HEADERSX {
	DWORD Signature;
	IMAGE_FILE_HEADER FileHeader;
#ifdef __x86_64__
	union {
		IMAGE_OPTIONAL_HEADER32 OptionalHeader32;
		IMAGE_OPTIONAL_HEADER64 OptionalHeader64;
	};
#else /* __x86_64__ */
	IMAGE_OPTIONAL_HEADER32 OptionalHeader32;
#endif /* !__x86_64__ */
} IMAGE_NT_HEADERSX, *PIMAGE_NT_HEADERSX;



/* Populate a given `effective_vm' by loading an PE executable file. */
INTDEF WUNUSED NONNULL((1)) unsigned int FCALL
peabi_exec(/*in|out*/ struct execargs *__restrict args);

/* ExecABI initializer for PE. */
#define EXECABI_INIT_PE            \
	{                              \
		.ea_driver = &drv_self,    \
		.ea_magsiz = 2,            \
		.ea_magic  = { 'M', 'Z' }, \
		.ea_exec   = &peabi_exec,  \
	}



DECL_END

#endif /* !GUARD_MODPE_PE_H */
