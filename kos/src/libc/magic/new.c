/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: MinGW        (/mingw-w64-headers/crt/new.h) */
/* (#) Portability: Windows Kits (/ucrt/new.h) */
}

%[define_replacement(locale_t = __locale_t)]
%[default:section(".text.crt.dos.heap.malloc")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <crtdefs.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

}

%[define(DEFINE__PNH =
@@pp_ifndef ___PNH_defined@@
#define ___PNH_defined
typedef int (__CRTDECL *_PNH)(size_t);
@@pp_endif@@
)]

%[define_replacement(_PNH = _PNH)]
%[define_type_class(_PNH = "TP")]

%[insert:prefix(DEFINE__PNH)]

[[crt_dos_only, decl_prefix(DEFINE__PNH)]]
_PNH _query_new_handler(void);

[[crt_dos_only, decl_prefix(DEFINE__PNH)]]
_PNH _set_new_handler(_PNH newhandler);

[[crt_dos_only]] int _query_new_mode(void);
[[crt_dos_only]] int _set_new_mode(int newmode);

%{

__SYSDECL_END
#endif /* __CC__ */

}
