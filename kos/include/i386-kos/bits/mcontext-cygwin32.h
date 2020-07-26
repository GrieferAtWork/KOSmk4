/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_BITS_MCONTEXT_CYGWIN32_H
#define _I386_KOS_BITS_MCONTEXT_CYGWIN32_H 1

/* File:
 *    <i386-kos/bits/mcontext-cygwin32.h>
 * 
 * Definitions:
 *    - struct __cygwin32_mcontext { ... };
 * #if defined(__CRT_CYG) && (!defined(__x86_64__) && defined(__i386__))
 *    - struct mcontext { ... };
 * #endif
 */

#include <__stdinc.h>
#include <__crt.h> /* __CRT_CYG */

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#if defined(__CRT_CYG) && (!defined(__x86_64__) && defined(__i386__))
#define __cygwin32_uc_fpreg _uc_fpreg
#define __cygwin32_fpstate  _fpstate
#define __cygwin32_mcontext mcontext
#endif /* __CRT_CYG && (!__x86_64__ && __i386__) */

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("significand")
#pragma push_macro("exponent")
#pragma push_macro("_fpstate")
#pragma push_macro("ctxflags")
#pragma push_macro("cs")
#pragma push_macro("ds")
#pragma push_macro("es")
#pragma push_macro("fs")
#pragma push_macro("gs")
#pragma push_macro("ss")
#pragma push_macro("eflags")
#pragma push_macro("dr0")
#pragma push_macro("dr1")
#pragma push_macro("dr2")
#pragma push_macro("dr3")
#pragma push_macro("dr6")
#pragma push_macro("dr7")
#pragma push_macro("oldmask")
#pragma push_macro("cr2")
#pragma push_macro("_uc_fpreg")
#pragma push_macro("cw")
#pragma push_macro("sw")
#pragma push_macro("tag")
#pragma push_macro("ipoff")
#pragma push_macro("cssel")
#pragma push_macro("dataoff")
#pragma push_macro("datasel")
#pragma push_macro("_st")
#pragma push_macro("nxst")
#pragma push_macro("fpstate")
#pragma push_macro("edi")
#pragma push_macro("esi")
#pragma push_macro("ebx")
#pragma push_macro("edx")
#pragma push_macro("ecx")
#pragma push_macro("eax")
#pragma push_macro("ebp")
#pragma push_macro("eip")
#pragma push_macro("esp")
#pragma push_macro("reserved")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef significand
#undef exponent
#undef _fpstate
#undef ctxflags
#undef cs
#undef ds
#undef es
#undef fs
#undef gs
#undef ss
#undef eflags
#undef dr0
#undef dr1
#undef dr2
#undef dr3
#undef dr6
#undef dr7
#undef oldmask
#undef cr2
#undef _uc_fpreg
#undef cw
#undef sw
#undef tag
#undef ipoff
#undef cssel
#undef dataoff
#undef datasel
#undef _st
#undef nxst
#undef fpstate
#undef edi
#undef esi
#undef ebx
#undef edx
#undef ecx
#undef eax
#undef ebp
#undef eip
#undef esp
#undef reserved

struct __cygwin32_uc_fpreg {
	__UINT16_TYPE__ significand[4];
	__UINT16_TYPE__ exponent;
};

struct __cygwin32_fpstate {
	__UINT32_TYPE__            cw;
	__UINT32_TYPE__            sw;
	__UINT32_TYPE__            tag;
	__UINT32_TYPE__            ipoff;
	__UINT32_TYPE__            cssel;
	__UINT32_TYPE__            dataoff;
	__UINT32_TYPE__            datasel;
	struct __cygwin32_uc_fpreg _st[8];
	__UINT32_TYPE__            nxst;
};

struct __cygwin32_mcontext {
	__UINT32_TYPE__           ctxflags;
	__UINT32_TYPE__           dr0;
	__UINT32_TYPE__           dr1;
	__UINT32_TYPE__           dr2;
	__UINT32_TYPE__           dr3;
	__UINT32_TYPE__           dr6;
	__UINT32_TYPE__           dr7;
	struct __cygwin32_fpstate fpstate;
	__UINT32_TYPE__           gs;
	__UINT32_TYPE__           fs;
	__UINT32_TYPE__           es;
	__UINT32_TYPE__           ds;
	__UINT32_TYPE__           edi;
	__UINT32_TYPE__           esi;
	__UINT32_TYPE__           ebx;
	__UINT32_TYPE__           edx;
	__UINT32_TYPE__           ecx;
	__UINT32_TYPE__           eax;
	__UINT32_TYPE__           ebp;
	__UINT32_TYPE__           eip;
	__UINT32_TYPE__           cs;
	__UINT32_TYPE__           eflags;
	__UINT32_TYPE__           esp;
	__UINT32_TYPE__           ss;
	__UINT32_TYPE__           reserved[128];
	__UINT32_TYPE__           oldmask;
	__UINT32_TYPE__           cr2;
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("reserved")
#pragma pop_macro("esp")
#pragma pop_macro("eip")
#pragma pop_macro("ebp")
#pragma pop_macro("eax")
#pragma pop_macro("ecx")
#pragma pop_macro("edx")
#pragma pop_macro("ebx")
#pragma pop_macro("esi")
#pragma pop_macro("edi")
#pragma pop_macro("fpstate")
#pragma pop_macro("nxst")
#pragma pop_macro("_st")
#pragma pop_macro("datasel")
#pragma pop_macro("dataoff")
#pragma pop_macro("cssel")
#pragma pop_macro("ipoff")
#pragma pop_macro("tag")
#pragma pop_macro("sw")
#pragma pop_macro("cw")
#pragma pop_macro("_uc_fpreg")
#pragma pop_macro("cr2")
#pragma pop_macro("oldmask")
#pragma pop_macro("dr7")
#pragma pop_macro("dr6")
#pragma pop_macro("dr3")
#pragma pop_macro("dr2")
#pragma pop_macro("dr1")
#pragma pop_macro("dr0")
#pragma pop_macro("eflags")
#pragma pop_macro("ss")
#pragma pop_macro("gs")
#pragma pop_macro("fs")
#pragma pop_macro("es")
#pragma pop_macro("ds")
#pragma pop_macro("cs")
#pragma pop_macro("ctxflags")
#pragma pop_macro("_fpstate")
#pragma pop_macro("exponent")
#pragma pop_macro("significand")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_BITS_MCONTEXT_CYGWIN32_H */
