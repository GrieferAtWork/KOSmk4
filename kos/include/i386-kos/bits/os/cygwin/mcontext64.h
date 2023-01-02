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
#ifndef _I386_KOS_BITS_OS_CYGWIN_MCONTEXT64_H
#define _I386_KOS_BITS_OS_CYGWIN_MCONTEXT64_H 1

/* File:
 *    <i386-kos/bits/os/cygwin/mcontext64.h>
 *
 * Definitions:
 *    - struct __cygwin64_mcontext { ... };
 * #if defined(__CRT_CYG) && (!defined(__x86_64__) && defined(__i386__))
 *    - struct mcontext { ... };
 * #endif
 */

#include <__stdinc.h>
#include <__crt.h> /* __CRT_CYG */

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#if defined(__CRT_CYG) && (!defined(__x86_64__) && defined(__i386__))
#define __cygwin64_uc_fpxreg           _uc_fpxreg
#define __cygwin64_uc_xmmreg           _uc_xmmreg
#define __cygwin64_fpstate             _fpstate
#define __cygwin64_mcontext            mcontext
#define __OFFSET_UC_FPXREG_SIGNIFICAND __OFFSET_CYGWIN64_UC_FPXREG_SIGNIFICAND
#define __OFFSET_UC_FPXREG_EXPONENT    __OFFSET_CYGWIN64_UC_FPXREG_EXPONENT
#define __OFFSET_UC_FPXREG_PADDING     __OFFSET_CYGWIN64_UC_FPXREG_PADDING
#define __SIZEOF_UC_FPXREG             __SIZEOF_CYGWIN64_UC_FPXREG
#define __ALIGNOF_UC_FPXREG            __ALIGNOF_CYGWIN64_UC_FPXREG
#define __OFFSET_UC_XMMREG_ELEMENT     __OFFSET_CYGWIN64_UC_XMMREG_ELEMENT
#define __SIZEOF_UC_XMMREG             __SIZEOF_CYGWIN64_UC_XMMREG
#define __ALIGNOF_UC_XMMREG            __ALIGNOF_CYGWIN64_UC_XMMREG
#define __OFFSET_FPSTATE_CWD           __OFFSET_CYGWIN64_FPSTATE_CWD
#define __OFFSET_FPSTATE_SWD           __OFFSET_CYGWIN64_FPSTATE_SWD
#define __OFFSET_FPSTATE_FTW           __OFFSET_CYGWIN64_FPSTATE_FTW
#define __OFFSET_FPSTATE_FOP           __OFFSET_CYGWIN64_FPSTATE_FOP
#define __OFFSET_FPSTATE_RIP           __OFFSET_CYGWIN64_FPSTATE_RIP
#define __OFFSET_FPSTATE_RDP           __OFFSET_CYGWIN64_FPSTATE_RDP
#define __OFFSET_FPSTATE_MXCSR         __OFFSET_CYGWIN64_FPSTATE_MXCSR
#define __OFFSET_FPSTATE_MXCR_MASK     __OFFSET_CYGWIN64_FPSTATE_MXCR_MASK
#define __OFFSET_FPSTATE_ST            __OFFSET_CYGWIN64_FPSTATE_ST
#define __OFFSET_FPSTATE_XMM           __OFFSET_CYGWIN64_FPSTATE_XMM
#define __OFFSET_FPSTATE_PADDING       __OFFSET_CYGWIN64_FPSTATE_PADDING
#define __SIZEOF_FPSTATE               __SIZEOF_CYGWIN64_FPSTATE
#define __ALIGNOF_FPSTATE              __ALIGNOF_CYGWIN64_FPSTATE
#define __OFFSET_MCONTEXT_P1HOME       __OFFSET_CYGWIN64_MCONTEXT_P1HOME
#define __OFFSET_MCONTEXT_P2HOME       __OFFSET_CYGWIN64_MCONTEXT_P2HOME
#define __OFFSET_MCONTEXT_P3HOME       __OFFSET_CYGWIN64_MCONTEXT_P3HOME
#define __OFFSET_MCONTEXT_P4HOME       __OFFSET_CYGWIN64_MCONTEXT_P4HOME
#define __OFFSET_MCONTEXT_P5HOME       __OFFSET_CYGWIN64_MCONTEXT_P5HOME
#define __OFFSET_MCONTEXT_P6HOME       __OFFSET_CYGWIN64_MCONTEXT_P6HOME
#define __OFFSET_MCONTEXT_CTXFLAGS     __OFFSET_CYGWIN64_MCONTEXT_CTXFLAGS
#define __OFFSET_MCONTEXT_MXCSR        __OFFSET_CYGWIN64_MCONTEXT_MXCSR
#define __OFFSET_MCONTEXT_CS           __OFFSET_CYGWIN64_MCONTEXT_CS
#define __OFFSET_MCONTEXT_DS           __OFFSET_CYGWIN64_MCONTEXT_DS
#define __OFFSET_MCONTEXT_ES           __OFFSET_CYGWIN64_MCONTEXT_ES
#define __OFFSET_MCONTEXT_FS           __OFFSET_CYGWIN64_MCONTEXT_FS
#define __OFFSET_MCONTEXT_GS           __OFFSET_CYGWIN64_MCONTEXT_GS
#define __OFFSET_MCONTEXT_SS           __OFFSET_CYGWIN64_MCONTEXT_SS
#define __OFFSET_MCONTEXT_EFLAGS       __OFFSET_CYGWIN64_MCONTEXT_EFLAGS
#define __OFFSET_MCONTEXT_DR0          __OFFSET_CYGWIN64_MCONTEXT_DR0
#define __OFFSET_MCONTEXT_DR1          __OFFSET_CYGWIN64_MCONTEXT_DR1
#define __OFFSET_MCONTEXT_DR2          __OFFSET_CYGWIN64_MCONTEXT_DR2
#define __OFFSET_MCONTEXT_DR3          __OFFSET_CYGWIN64_MCONTEXT_DR3
#define __OFFSET_MCONTEXT_DR6          __OFFSET_CYGWIN64_MCONTEXT_DR6
#define __OFFSET_MCONTEXT_DR7          __OFFSET_CYGWIN64_MCONTEXT_DR7
#define __OFFSET_MCONTEXT_RAX          __OFFSET_CYGWIN64_MCONTEXT_RAX
#define __OFFSET_MCONTEXT_RCX          __OFFSET_CYGWIN64_MCONTEXT_RCX
#define __OFFSET_MCONTEXT_RDX          __OFFSET_CYGWIN64_MCONTEXT_RDX
#define __OFFSET_MCONTEXT_RBX          __OFFSET_CYGWIN64_MCONTEXT_RBX
#define __OFFSET_MCONTEXT_RSP          __OFFSET_CYGWIN64_MCONTEXT_RSP
#define __OFFSET_MCONTEXT_RBP          __OFFSET_CYGWIN64_MCONTEXT_RBP
#define __OFFSET_MCONTEXT_RSI          __OFFSET_CYGWIN64_MCONTEXT_RSI
#define __OFFSET_MCONTEXT_RDI          __OFFSET_CYGWIN64_MCONTEXT_RDI
#define __OFFSET_MCONTEXT_R8           __OFFSET_CYGWIN64_MCONTEXT_R8
#define __OFFSET_MCONTEXT_R9           __OFFSET_CYGWIN64_MCONTEXT_R9
#define __OFFSET_MCONTEXT_R10          __OFFSET_CYGWIN64_MCONTEXT_R10
#define __OFFSET_MCONTEXT_R11          __OFFSET_CYGWIN64_MCONTEXT_R11
#define __OFFSET_MCONTEXT_R12          __OFFSET_CYGWIN64_MCONTEXT_R12
#define __OFFSET_MCONTEXT_R13          __OFFSET_CYGWIN64_MCONTEXT_R13
#define __OFFSET_MCONTEXT_R14          __OFFSET_CYGWIN64_MCONTEXT_R14
#define __OFFSET_MCONTEXT_R15          __OFFSET_CYGWIN64_MCONTEXT_R15
#define __OFFSET_MCONTEXT_RIP          __OFFSET_CYGWIN64_MCONTEXT_RIP
#define __OFFSET_MCONTEXT_FPREGS       __OFFSET_CYGWIN64_MCONTEXT_FPREGS
#define __OFFSET_MCONTEXT_VREGS        __OFFSET_CYGWIN64_MCONTEXT_VREGS
#define __OFFSET_MCONTEXT_VCX          __OFFSET_CYGWIN64_MCONTEXT_VCX
#define __OFFSET_MCONTEXT_DBC          __OFFSET_CYGWIN64_MCONTEXT_DBC
#define __OFFSET_MCONTEXT_BTR          __OFFSET_CYGWIN64_MCONTEXT_BTR
#define __OFFSET_MCONTEXT_BFR          __OFFSET_CYGWIN64_MCONTEXT_BFR
#define __OFFSET_MCONTEXT_ETR          __OFFSET_CYGWIN64_MCONTEXT_ETR
#define __OFFSET_MCONTEXT_EFR          __OFFSET_CYGWIN64_MCONTEXT_EFR
#define __OFFSET_MCONTEXT_OLDMASK      __OFFSET_CYGWIN64_MCONTEXT_OLDMASK
#define __OFFSET_MCONTEXT_CR2          __OFFSET_CYGWIN64_MCONTEXT_CR2
#define __SIZEOF_MCONTEXT              __SIZEOF_CYGWIN64_MCONTEXT
#define __ALIGNOF_MCONTEXT             __ALIGNOF_CYGWIN64_MCONTEXT
#endif /* __CRT_CYG && (!__x86_64__ && __i386__) */

#define __OFFSET_CYGWIN64_UC_FPXREG_SIGNIFICAND 0
#define __OFFSET_CYGWIN64_UC_FPXREG_EXPONENT    8
#define __OFFSET_CYGWIN64_UC_FPXREG_PADDING     10
#define __SIZEOF_CYGWIN64_UC_FPXREG             16
#define __ALIGNOF_CYGWIN64_UC_FPXREG            2

#define __OFFSET_CYGWIN64_UC_XMMREG_ELEMENT 0
#define __SIZEOF_CYGWIN64_UC_XMMREG         16
#define __ALIGNOF_CYGWIN64_UC_XMMREG        4

#define __OFFSET_CYGWIN64_FPSTATE_CWD       0
#define __OFFSET_CYGWIN64_FPSTATE_SWD       2
#define __OFFSET_CYGWIN64_FPSTATE_FTW       4
#define __OFFSET_CYGWIN64_FPSTATE_FOP       6
#define __OFFSET_CYGWIN64_FPSTATE_RIP       8
#define __OFFSET_CYGWIN64_FPSTATE_RDP       16
#define __OFFSET_CYGWIN64_FPSTATE_MXCSR     24
#define __OFFSET_CYGWIN64_FPSTATE_MXCR_MASK 28
#define __OFFSET_CYGWIN64_FPSTATE_ST        32
#define __OFFSET_CYGWIN64_FPSTATE_XMM       160
#define __OFFSET_CYGWIN64_FPSTATE_PADDING   416
#define __SIZEOF_CYGWIN64_FPSTATE           512
#define __ALIGNOF_CYGWIN64_FPSTATE          16

#define __OFFSET_CYGWIN64_MCONTEXT_P1HOME   0
#define __OFFSET_CYGWIN64_MCONTEXT_P2HOME   8
#define __OFFSET_CYGWIN64_MCONTEXT_P3HOME   16
#define __OFFSET_CYGWIN64_MCONTEXT_P4HOME   24
#define __OFFSET_CYGWIN64_MCONTEXT_P5HOME   32
#define __OFFSET_CYGWIN64_MCONTEXT_P6HOME   40
#define __OFFSET_CYGWIN64_MCONTEXT_CTXFLAGS 48
#define __OFFSET_CYGWIN64_MCONTEXT_MXCSR    52
#define __OFFSET_CYGWIN64_MCONTEXT_CS       56
#define __OFFSET_CYGWIN64_MCONTEXT_DS       58
#define __OFFSET_CYGWIN64_MCONTEXT_ES       60
#define __OFFSET_CYGWIN64_MCONTEXT_FS       62
#define __OFFSET_CYGWIN64_MCONTEXT_GS       64
#define __OFFSET_CYGWIN64_MCONTEXT_SS       66
#define __OFFSET_CYGWIN64_MCONTEXT_EFLAGS   68
#define __OFFSET_CYGWIN64_MCONTEXT_DR0      72
#define __OFFSET_CYGWIN64_MCONTEXT_DR1      80
#define __OFFSET_CYGWIN64_MCONTEXT_DR2      88
#define __OFFSET_CYGWIN64_MCONTEXT_DR3      96
#define __OFFSET_CYGWIN64_MCONTEXT_DR6      104
#define __OFFSET_CYGWIN64_MCONTEXT_DR7      112
#define __OFFSET_CYGWIN64_MCONTEXT_RAX      120
#define __OFFSET_CYGWIN64_MCONTEXT_RCX      128
#define __OFFSET_CYGWIN64_MCONTEXT_RDX      136
#define __OFFSET_CYGWIN64_MCONTEXT_RBX      144
#define __OFFSET_CYGWIN64_MCONTEXT_RSP      152
#define __OFFSET_CYGWIN64_MCONTEXT_RBP      160
#define __OFFSET_CYGWIN64_MCONTEXT_RSI      168
#define __OFFSET_CYGWIN64_MCONTEXT_RDI      176
#define __OFFSET_CYGWIN64_MCONTEXT_R8       184
#define __OFFSET_CYGWIN64_MCONTEXT_R9       192
#define __OFFSET_CYGWIN64_MCONTEXT_R10      200
#define __OFFSET_CYGWIN64_MCONTEXT_R11      208
#define __OFFSET_CYGWIN64_MCONTEXT_R12      216
#define __OFFSET_CYGWIN64_MCONTEXT_R13      224
#define __OFFSET_CYGWIN64_MCONTEXT_R14      232
#define __OFFSET_CYGWIN64_MCONTEXT_R15      240
#define __OFFSET_CYGWIN64_MCONTEXT_RIP      248
#define __OFFSET_CYGWIN64_MCONTEXT_FPREGS   256
#define __OFFSET_CYGWIN64_MCONTEXT_VREGS    768
#define __OFFSET_CYGWIN64_MCONTEXT_VCX      1184
#define __OFFSET_CYGWIN64_MCONTEXT_DBC      1192
#define __OFFSET_CYGWIN64_MCONTEXT_BTR      1200
#define __OFFSET_CYGWIN64_MCONTEXT_BFR      1208
#define __OFFSET_CYGWIN64_MCONTEXT_ETR      1216
#define __OFFSET_CYGWIN64_MCONTEXT_EFR      1224
#define __OFFSET_CYGWIN64_MCONTEXT_OLDMASK  1232
#define __OFFSET_CYGWIN64_MCONTEXT_CR2      1240
#define __SIZEOF_CYGWIN64_MCONTEXT          1248
#define __ALIGNOF_CYGWIN64_MCONTEXT         16

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
#pragma push_macro("_uc_fpxreg")
#pragma push_macro("_uc_xmmreg")
#pragma push_macro("element")
#pragma push_macro("cwd")
#pragma push_macro("swd")
#pragma push_macro("ftw")
#pragma push_macro("fop")
#pragma push_macro("rdp")
#pragma push_macro("mxcr_mask")
#pragma push_macro("st")
#pragma push_macro("xmm")
#pragma push_macro("padding")
#pragma push_macro("p1home")
#pragma push_macro("p2home")
#pragma push_macro("p3home")
#pragma push_macro("p4home")
#pragma push_macro("p5home")
#pragma push_macro("p6home")
#pragma push_macro("mxcsr")
#pragma push_macro("rax")
#pragma push_macro("rcx")
#pragma push_macro("rdx")
#pragma push_macro("rbx")
#pragma push_macro("rsp")
#pragma push_macro("rbp")
#pragma push_macro("rsi")
#pragma push_macro("rdi")
#pragma push_macro("r8")
#pragma push_macro("r9")
#pragma push_macro("r10")
#pragma push_macro("r11")
#pragma push_macro("r12")
#pragma push_macro("r13")
#pragma push_macro("r14")
#pragma push_macro("r15")
#pragma push_macro("rip")
#pragma push_macro("fpregs")
#pragma push_macro("vregs")
#pragma push_macro("vcx")
#pragma push_macro("dbc")
#pragma push_macro("btr")
#pragma push_macro("bfr")
#pragma push_macro("etr")
#pragma push_macro("efr")
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
#undef _uc_fpxreg
#undef _uc_xmmreg
#undef element
#undef cwd
#undef swd
#undef ftw
#undef fop
#undef rdp
#undef mxcr_mask
#undef st
#undef xmm
#undef padding
#undef p1home
#undef p2home
#undef p3home
#undef p4home
#undef p5home
#undef p6home
#undef mxcsr
#undef rax
#undef rcx
#undef rdx
#undef rbx
#undef rsp
#undef rbp
#undef rsi
#undef rdi
#undef r8
#undef r9
#undef r10
#undef r11
#undef r12
#undef r13
#undef r14
#undef r15
#undef rip
#undef fpregs
#undef vregs
#undef vcx
#undef dbc
#undef btr
#undef bfr
#undef etr
#undef efr

struct __cygwin64_uc_fpxreg /*[NAME(cygwin64_uc_fpxreg)][PREFIX()]*/ {
	__UINT16_TYPE__ significand[4];
	__UINT16_TYPE__ exponent;
	__UINT16_TYPE__ padding[3];
};

struct __cygwin64_uc_xmmreg /*[NAME(cygwin64_uc_xmmreg)][PREFIX()]*/ {
	__UINT32_TYPE__ element[4];
};

struct __ATTR_ALIGNED(16) __cygwin64_fpstate /*[NAME(cygwin64_fpstate)][PREFIX()]*/ {
	__UINT16_TYPE__             cwd;
	__UINT16_TYPE__             swd;
	__UINT16_TYPE__             ftw;
	__UINT16_TYPE__             fop;
	__UINT64_TYPE__             rip;
	__UINT64_TYPE__             rdp;
	__UINT32_TYPE__             mxcsr;
	__UINT32_TYPE__             mxcr_mask;
	struct __cygwin64_uc_fpxreg st[8];
	struct __cygwin64_uc_xmmreg xmm[16];
	__UINT32_TYPE__             padding[24];
};

struct __ATTR_ALIGNED(16) __cygwin64_mcontext /*[NAME(cygwin64_mcontext)][PREFIX()]*/ {
	__UINT64_TYPE__           p1home;
	__UINT64_TYPE__           p2home;
	__UINT64_TYPE__           p3home;
	__UINT64_TYPE__           p4home;
	__UINT64_TYPE__           p5home;
	__UINT64_TYPE__           p6home;
	__UINT32_TYPE__           ctxflags;
	__UINT32_TYPE__           mxcsr;
	__UINT16_TYPE__           cs;
	__UINT16_TYPE__           ds;
	__UINT16_TYPE__           es;
	__UINT16_TYPE__           fs;
	__UINT16_TYPE__           gs;
	__UINT16_TYPE__           ss;
	__UINT32_TYPE__           eflags;
	__UINT64_TYPE__           dr0;
	__UINT64_TYPE__           dr1;
	__UINT64_TYPE__           dr2;
	__UINT64_TYPE__           dr3;
	__UINT64_TYPE__           dr6;
	__UINT64_TYPE__           dr7;
	__UINT64_TYPE__           rax;
	__UINT64_TYPE__           rcx;
	__UINT64_TYPE__           rdx;
	__UINT64_TYPE__           rbx;
	__UINT64_TYPE__           rsp;
	__UINT64_TYPE__           rbp;
	__UINT64_TYPE__           rsi;
	__UINT64_TYPE__           rdi;
	__UINT64_TYPE__           r8;
	__UINT64_TYPE__           r9;
	__UINT64_TYPE__           r10;
	__UINT64_TYPE__           r11;
	__UINT64_TYPE__           r12;
	__UINT64_TYPE__           r13;
	__UINT64_TYPE__           r14;
	__UINT64_TYPE__           r15;
	__UINT64_TYPE__           rip;
	struct __cygwin64_fpstate fpregs;
	__UINT64_TYPE__           vregs[52];
	__UINT64_TYPE__           vcx;
	__UINT64_TYPE__           dbc;
	__UINT64_TYPE__           btr;
	__UINT64_TYPE__           bfr;
	__UINT64_TYPE__           etr;
	__UINT64_TYPE__           efr;
	__UINT64_TYPE__           oldmask;
	__UINT64_TYPE__           cr2;
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("efr")
#pragma pop_macro("etr")
#pragma pop_macro("bfr")
#pragma pop_macro("btr")
#pragma pop_macro("dbc")
#pragma pop_macro("vcx")
#pragma pop_macro("vregs")
#pragma pop_macro("fpregs")
#pragma pop_macro("rip")
#pragma pop_macro("r15")
#pragma pop_macro("r14")
#pragma pop_macro("r13")
#pragma pop_macro("r12")
#pragma pop_macro("r11")
#pragma pop_macro("r10")
#pragma pop_macro("r9")
#pragma pop_macro("r8")
#pragma pop_macro("rdi")
#pragma pop_macro("rsi")
#pragma pop_macro("rbp")
#pragma pop_macro("rsp")
#pragma pop_macro("rbx")
#pragma pop_macro("rdx")
#pragma pop_macro("rcx")
#pragma pop_macro("rax")
#pragma pop_macro("mxcsr")
#pragma pop_macro("p6home")
#pragma pop_macro("p5home")
#pragma pop_macro("p4home")
#pragma pop_macro("p3home")
#pragma pop_macro("p2home")
#pragma pop_macro("p1home")
#pragma pop_macro("padding")
#pragma pop_macro("xmm")
#pragma pop_macro("st")
#pragma pop_macro("mxcr_mask")
#pragma pop_macro("rdp")
#pragma pop_macro("fop")
#pragma pop_macro("ftw")
#pragma pop_macro("swd")
#pragma pop_macro("cwd")
#pragma pop_macro("element")
#pragma pop_macro("_uc_xmmreg")
#pragma pop_macro("_uc_fpxreg")
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


#endif /* !_I386_KOS_BITS_OS_CYGWIN_MCONTEXT64_H */
