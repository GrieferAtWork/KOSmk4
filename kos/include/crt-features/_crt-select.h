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
/* Select used CRT based on `-D_CRT=...' */
#include <__stdinc.h>


/*[[[deemon
import util;

// CRT names and macros to define in the resp. CRT-mode
global CRT_NAMES = {
	"cygwin"        : { "__CRT_CYG_PRIMARY", "__CRT_CYG" },
	"msvcrt"        : { "__CRT_DOS_PRIMARY", "__CRT_DOS" },
	"glibc"         : { "__CRT_GLC_PRIMARY", "__CRT_GLC" },
	"kos"           : { "__CRT_KOS_PRIMARY", "__CRT_KOS", "__CRT_GLC", "__CRT_DOS" },
	"kos_kernel"    : { "__CRT_KOS_PRIMARY", "__CRT_KOS", "__CRT_KOS_KERNEL" },
	"freestanding"  : { "__CRT_FREESTANDING" },
	"generic"       : { "__CRT_GENERIC" },
};

global keys = CRT_NAMES.keys.sorted();
print("#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO");
for (local name: keys)
	print("#pragma push_macro(", repr name, ")");
for (local name: keys)
	print("#undef ", name);
for (local i, name: util.enumerate(keys))
	print("#define ", name, " ", (i+1));
print("#else /" "* __COMPILER_HAVE_PRAGMA_PUSHMACRO *" "/");
for (local i, name: util.enumerate(keys)) {
	print("#ifndef ", name);
	print("#define ", name, " ", (i+1));
	print("#define __PRIVATE_CRT_FEATURES_DEFINES_", name);
	print("#endif /" "* !", name, " *" "/");
}
print("#endif /" "* __COMPILER_HAVE_PRAGMA_PUSHMACRO *" "/");

local isFirst = true;
for (local i, name: util.enumerate(keys)) {
	print("#"),;
	if (!isFirst)
		print("el"),;
	isFirst = false;
	print("if _CRT == ", name);
	for (local def: CRT_NAMES[name])
		print("#define ", def);
}
print("#else /" "* ... *" "/");
print("#error \"Unsupported '-D_CRT=...' Must be one of [", ",".join(keys), "]\"");
print("#endif /" "* !... *" "/");

print("#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO");
for (local name: keys)
	print("#pragma pop_macro(", repr name, ")");
print("#else /" "* __COMPILER_HAVE_PRAGMA_PUSHMACRO *" "/");
for (local i, name: util.enumerate(keys)) {
	print("#ifdef __PRIVATE_CRT_FEATURES_DEFINES_", name);
	print("#undef __PRIVATE_CRT_FEATURES_DEFINES_", name);
	print("#undef ", name);
	print("#endif /" "* __PRIVATE_CRT_FEATURES_DEFINES_", name, " *" "/");
}
print("#endif /" "* __COMPILER_HAVE_PRAGMA_PUSHMACRO *" "/");
]]]*/
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("cygwin")
#pragma push_macro("freestanding")
#pragma push_macro("generic")
#pragma push_macro("glibc")
#pragma push_macro("kos")
#pragma push_macro("kos_kernel")
#pragma push_macro("msvcrt")
#undef cygwin
#undef freestanding
#undef generic
#undef glibc
#undef kos
#undef kos_kernel
#undef msvcrt
#define cygwin 1
#define freestanding 2
#define generic 3
#define glibc 4
#define kos 5
#define kos_kernel 6
#define msvcrt 7
#else /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#ifndef cygwin
#define cygwin 1
#define __PRIVATE_CRT_FEATURES_DEFINES_cygwin
#endif /* !cygwin */
#ifndef freestanding
#define freestanding 2
#define __PRIVATE_CRT_FEATURES_DEFINES_freestanding
#endif /* !freestanding */
#ifndef generic
#define generic 3
#define __PRIVATE_CRT_FEATURES_DEFINES_generic
#endif /* !generic */
#ifndef glibc
#define glibc 4
#define __PRIVATE_CRT_FEATURES_DEFINES_glibc
#endif /* !glibc */
#ifndef kos
#define kos 5
#define __PRIVATE_CRT_FEATURES_DEFINES_kos
#endif /* !kos */
#ifndef kos_kernel
#define kos_kernel 6
#define __PRIVATE_CRT_FEATURES_DEFINES_kos_kernel
#endif /* !kos_kernel */
#ifndef msvcrt
#define msvcrt 7
#define __PRIVATE_CRT_FEATURES_DEFINES_msvcrt
#endif /* !msvcrt */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#if _CRT == cygwin
#define __CRT_CYG_PRIMARY
#define __CRT_CYG
#elif _CRT == freestanding
#define __CRT_FREESTANDING
#elif _CRT == generic
#define __CRT_GENERIC
#elif _CRT == glibc
#define __CRT_GLC_PRIMARY
#define __CRT_GLC
#elif _CRT == kos
#define __CRT_KOS_PRIMARY
#define __CRT_KOS
#define __CRT_GLC
#define __CRT_DOS
#elif _CRT == kos_kernel
#define __CRT_KOS_PRIMARY
#define __CRT_KOS
#define __CRT_KOS_KERNEL
#elif _CRT == msvcrt
#define __CRT_DOS_PRIMARY
#define __CRT_DOS
#else /* ... */
#error "Unsupported '-D_CRT=...' Must be one of [cygwin,freestanding,generic,glibc,kos,kos_kernel,msvcrt]"
#endif /* !... */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("cygwin")
#pragma pop_macro("freestanding")
#pragma pop_macro("generic")
#pragma pop_macro("glibc")
#pragma pop_macro("kos")
#pragma pop_macro("kos_kernel")
#pragma pop_macro("msvcrt")
#else /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#ifdef __PRIVATE_CRT_FEATURES_DEFINES_cygwin
#undef __PRIVATE_CRT_FEATURES_DEFINES_cygwin
#undef cygwin
#endif /* __PRIVATE_CRT_FEATURES_DEFINES_cygwin */
#ifdef __PRIVATE_CRT_FEATURES_DEFINES_freestanding
#undef __PRIVATE_CRT_FEATURES_DEFINES_freestanding
#undef freestanding
#endif /* __PRIVATE_CRT_FEATURES_DEFINES_freestanding */
#ifdef __PRIVATE_CRT_FEATURES_DEFINES_generic
#undef __PRIVATE_CRT_FEATURES_DEFINES_generic
#undef generic
#endif /* __PRIVATE_CRT_FEATURES_DEFINES_generic */
#ifdef __PRIVATE_CRT_FEATURES_DEFINES_glibc
#undef __PRIVATE_CRT_FEATURES_DEFINES_glibc
#undef glibc
#endif /* __PRIVATE_CRT_FEATURES_DEFINES_glibc */
#ifdef __PRIVATE_CRT_FEATURES_DEFINES_kos
#undef __PRIVATE_CRT_FEATURES_DEFINES_kos
#undef kos
#endif /* __PRIVATE_CRT_FEATURES_DEFINES_kos */
#ifdef __PRIVATE_CRT_FEATURES_DEFINES_kos_kernel
#undef __PRIVATE_CRT_FEATURES_DEFINES_kos_kernel
#undef kos_kernel
#endif /* __PRIVATE_CRT_FEATURES_DEFINES_kos_kernel */
#ifdef __PRIVATE_CRT_FEATURES_DEFINES_msvcrt
#undef __PRIVATE_CRT_FEATURES_DEFINES_msvcrt
#undef msvcrt
#endif /* __PRIVATE_CRT_FEATURES_DEFINES_msvcrt */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
/*[[[end]]]*/
