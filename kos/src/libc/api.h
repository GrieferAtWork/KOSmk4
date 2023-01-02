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
#ifndef GUARD_LIBC_API_H
#define GUARD_LIBC_API_H 1

#ifndef __BUILDING_LIBC
#define __BUILDING_LIBC
#endif /* !__BUILDING_LIBC */
#define __CRT_KOS_PRIMARY
#define __CRT_KOS
#ifdef __KERNEL__
#define __CRT_KOS_KERNEL
#endif /* __KERNEL__ */

#ifndef __OPTIMIZE_SIZE__
/* Enable system call inlining, causing calls to `sys_*' functions from <kos/syscalls.h>
 * to be inlined (as far as possible), rather than being declared as entry points to the
 * libc system call export table (libc also exports all system calls as `sys_*' symbols)
 * NOTE: When optimizing for size, we don't do this, in which case system calls used
 *       by libc library functions get linked against the system call wrappers  that
 *       are always exported from libc unconditionally. */
#define __WANT_INLINE_SYSCALLS
#endif /* !__OPTIMIZE_SIZE__ */


/* Enable access  to a  variety of  header functions  normally
 * locked away behind various  feature macros (us being  libc,
 * we obviously want access to anything we intend on defining,
 * so we make our job simple by unlocking everything) */
#define _KOS_SOURCE             1
#define _KOS_KERNEL_SOURCE      1
#define _KOS_ALTERATIONS_SOURCE 1
#define _STRING_BWLQ_SOURCE     1
#define _STRING_XCHR_SOURCE     1
#define _CTYPE_MACRO_SOURCE     1
#define _DOS_SOURCE             1
#define _BSD_SOURCE             1
#define _SVID_SOURCE            1
#define _GNU_SOURCE             1
#define _NETBSD_SOURCE          1
#define _LARGEFILE_SOURCE       1
#define __EXTENSIONS__          1

/* Must load  headers in  32-bit time/file-offset  mode, so-as  to  prevent
 * any symbol  re-directions from  happening, which  might otherwise  screw
 * up libc linkage. - Instead,  libc itself must always explicitly  specify
 * the *64 variants of functions (e.g. `mmap64(2)'; `mmap(2)' is always the
 * 32-bit variant) */
#undef _LARGEFILE64_SOURCE
#define _LARGEFILE64_SOURCE 1
#undef _TIME64_SOURCE
#define _TIME64_SOURCE 1
#undef _TIME_T_BITS
#define _TIME_T_BITS 32
#undef _FILE_OFFSET_BITS
#define _FILE_OFFSET_BITS 32

/* This right here allows for some neat tricks, as well as less overall
 * code which needs to be compiled. */
#undef _STRUCT64_MACRO_SOURCE
#define _STRUCT64_MACRO_SOURCE 1

#include <__stdinc.h>

#include <kos/config/config.h> /* Pull in config-specific macro overrides */

/* Do some assembler trickery to prevent some unnecessary relocations. */
#ifdef __CC__
#ifndef GUARD_LIBC_LIBC_SSP_C
__asm__("__stack_chk_guard = libc_stack_chk_guard");
__asm__("__stack_chk_fail = libc_stack_chk_fail");
__asm__("__stack_chk_fail_local = libc_stack_chk_fail");
#endif /* !GUARD_LIBC_LIBC_SSP_C */

/* NOTE: Even though some of the  following functions can (and are)  overwritten
 *       by libstdc++, even in the event of that happening, we (libc) can  still
 *       continue to use our own, original variants, since while ours are unable
 *       to  properly  catch non-KOS  exceptions  (like `throw std::exception'),
 *       they're fully  still capable  of re-throwing  them (in  case they  were
 *       thrown by user-provided callbacks to functions like `qsort(3)', as well
 *       as being able to handle KOS exceptions (s.a. `<kos/except.h>') */
#ifndef GUARD_LIBC_HYBRID_EXCEPT_C
__asm__("__cxa_end_catch = libc_cxa_end_catch");
__asm__("__cxa_begin_catch = libc_cxa_begin_catch");
__asm__("_Unwind_Resume = libc_Unwind_Resume");
#endif /* !GUARD_LIBC_HYBRID_EXCEPT_C */
/* TODO: Because of how GCC generates code, even if we were to prevent  it
 *       from  generating relocations against  these symbols, we'd instead
 *       end  up with a  `R_386_RELATIVE' relocation, as  gcc places a ref
 *       to these symbols in ".data.rel.local.DW.ref.__gxx_personality_v0" */
//#ifndef GUARD_LIBC_LIBC_EXCEPT_PERSONALITY_C
//__asm__("__gcc_personality_v0 = libc_gxx_personality_v0");
//__asm__("__gxx_personality_v0 = libc_gxx_personality_v0");
//#endif /* !GUARD_LIBC_LIBC_EXCEPT_PERSONALITY_C */

#ifndef GUARD_LIBC_HYBRID_ARCH_I386_ASSERT_S
__asm__("__ubsan_handle_builtin_unreachable = libc___ubsan_handle_builtin_unreachable");
#endif /* !GUARD_LIBC_HYBRID_ARCH_I386_ASSERT_S */
#endif /* __CC__ */

#include <__crt.h>

/* Pull in CRT feature definitions */
#ifdef __CC__
#include "crt-features.h" /* Auto-generated file (by generate_headers.dee) */
#ifndef __KERNEL__
/* The user-space libc provides exports for defined system calls (by name).
 * As  such, these symbols also exists within the libc_* namespace, meaning
 * that we're allowed to advertise this fact while building libc itself. */
#include <crt-features/crt-kos-syscalls.h>
#else /* !__KERNEL__ */

#if defined(CONFIG_NO_ASSERT_RESTARTABLE) || defined(CONFIG_NO_KERNEL_DEBUGGER)
#undef __CRT_HAVE___acheck
#undef __CRT_HAVE___acheckf
#endif /* CONFIG_NO_ASSERT_RESTARTABLE || CONFIG_NO_KERNEL_DEBUGGER */

#endif /* __KERNEL__ */

/* Do some quick probing if crt linkage was configured correctly */
#ifndef __CRT_HAVE_memmove
#error "Bad libc build environment"
#endif /* !__CRT_HAVE_memmove */

#endif /* __CC__ */

#include <features.h>
#include <hybrid/compiler.h>

/* We may define a couple of functions that are annotated as  deprecated.
 * As such, prevent potential compiler warnings related to them, as we're
 * actually supposed to use/define them. */
#undef ATTR_DEPRECATED
#undef ATTR_DEPRECATED_
#undef __ATTR_DEPRECATED
#undef __ATTR_DEPRECATED_
#define ATTR_DEPRECATED(msg)   /* nothing */
#define ATTR_DEPRECATED_       /* nothing */
#define __ATTR_DEPRECATED(msg) /* nothing */
#define __ATTR_DEPRECATED_     /* nothing */


#include <hybrid/host.h>

#include <bits/types.h>
#include <kos/anno.h>
#include <kos/kernel/types.h>
#include <kos/types.h>

#include <inttypes.h>
#include <limits.h>
#include <stdarg.h>
#include <stddef.h>

/* Pull in arch-specific LIBC feature information */
#if defined(__i386__) || defined(__x86_64__)
#include "hybrid/arch/i386/config.h"
#elif defined(__arm__)
#include "hybrid/arch/arm/config.h"
#endif /* ARCH... */


#ifdef __KERNEL__
#include <kernel/compiler.h>
#endif /* __KERNEL__ */

#define LIBCCALL  __LIBCCALL
#define LIBDCALL  __LIBDCALL
#define LIBKCALL  __LIBKCALL
#define VLIBCCALL __VLIBCCALL
#define VLIBDCALL __VLIBDCALL
#define VLIBKCALL __VLIBKCALL
#define CC        LIBCCALL
#define VCC       VLIBCCALL

#ifndef NOBLOCK
#define NOBLOCK __NOBLOCK
#endif /* !NOBLOCK */
#ifndef THROWS
#define THROWS __THROWS
#endif /* !THROWS */
#ifndef ASMCALL
#define ASMCALL /* nothing */
#endif /* !ASMCALL */

#define ATTR_LIBC_PRINTF(a, b)      __ATTR_LIBC_PRINTF(a, b)
#define ATTR_LIBC_PRINTF_P(a, b)    __ATTR_LIBC_PRINTF_P(a, b)
#define ATTR_LIBC_SCANF(a, b)       __ATTR_LIBC_SCANF(a, b)
#define ATTR_LIBC_STRFMON(a, b)     __ATTR_LIBC_STRFMON(a, b)
#define ATTR_LIBC_STRFTIME(a, b)    __ATTR_LIBC_STRFTIME(a, b)
#define ATTR_LIBC_WPRINTF(a, b)     __ATTR_LIBC_WPRINTF(a, b)
#define ATTR_LIBC_WPRINTF_P(a, b)   __ATTR_LIBC_WPRINTF_P(a, b)
#define ATTR_LIBC_WSCANF(a, b)      __ATTR_LIBC_WSCANF(a, b)
#define ATTR_LIBC_WCSFTIME(a, b)    __ATTR_LIBC_WCSFTIME(a, b)
#define ATTR_LIBC_C16PRINTF(a, b)   __ATTR_LIBC_C16PRINTF(a, b)
#define ATTR_LIBC_C16PRINTF_P(a, b) __ATTR_LIBC_C16PRINTF_P(a, b)
#define ATTR_LIBC_C16SCANF(a, b)    __ATTR_LIBC_C16SCANF(a, b)
#define ATTR_LIBC_C16FTIME(a, b)    __ATTR_LIBC_C16FTIME(a, b)
#define ATTR_LIBC_C32PRINTF(a, b)   __ATTR_LIBC_C32PRINTF(a, b)
#define ATTR_LIBC_C32PRINTF_P(a, b) __ATTR_LIBC_C32PRINTF_P(a, b)
#define ATTR_LIBC_C32SCANF(a, b)    __ATTR_LIBC_C32SCANF(a, b)
#define ATTR_LIBC_C32FTIME(a, b)    __ATTR_LIBC_C32FTIME(a, b)

#include <errno.h>
#include <libc/errno.h>

#define ATTR_MALL_DEFAULT_ALIGNED __ATTR_MALL_DEFAULT_ALIGNED
#define ATTR_MALL_PAGEALIGNED     __ATTR_MALL_PAGEALIGNED


/* Extra  attribute for CRT functions that should be optimized for size
 * rather than speed when it comes to optimizing builds of the library.
 *
 * By  default,  magic sets  this attribute  for the  DOS variants  of all
 * functions, but this can be turned off with [[no_crt_dos_optimize_size]] */
#ifndef ATTR_OPTIMIZE_SIZE
#ifdef __OPTIMIZE__
#define ATTR_OPTIMIZE_SIZE __ATTR_OPTIMIZE("-Os")
#else /* __OPTIMIZE__ */
#define ATTR_OPTIMIZE_SIZE /* nothing */
#endif /* !__OPTIMIZE__ */
#endif /* !ATTR_OPTIMIZE_SIZE */

/* Attribute for global data that is mostly read from */
#ifndef ATTR_READMOSTLY
#define ATTR_READMOSTLY ATTR_SECTION(".data.read_mostly")
#endif /* !ATTR_READMOSTLY */


/* Re-bind errno memory locations. */
#undef errno
#undef __errno
#undef libc_errno
#undef __libc_errno
#undef libc_geterrno
#undef __libc_geterrno
#undef libc_geterrno_or
#undef __libc_geterrno_or
#undef libc_seterrno
#undef __libc_seterrno
#undef libd_errno
#undef __libd_errno
#undef libd_geterrno
#undef __libd_geterrno
#undef libd_geterrno_or
#undef __libd_geterrno_or
#undef libd_seterrno
#undef __libd_seterrno
#undef ____errno_location_defined

#ifndef __KERNEL__
#define errno                   (*libc_errno_p())
#define __errno                 (*libc_errno_p())
#define __libc_errno            (*libc_errno_p())
#define __libc_geterrno         libc_geterrno
#define __libc_geterrno_or(alt) libc_geterrno()
#define libc_geterrno_or(alt)   libc_geterrno()
#define __libc_seterrno         libc_seterrno
#define __libd_errno            (*libd_errno_p())
#define __libd_geterrno         libd_geterrno
#define __libd_geterrno_or(alt) libd_geterrno()
#define libd_geterrno_or(alt)   libd_geterrno()
#define __libd_seterrno         libd_seterrno
#define ____errno_location_defined
#define __errno_location()            libc_errno_p()
#define libc_seterrno_syserr(e)       (likely(!E_ISERR(e)) ? (e) : libc_seterrno_neg((errno_t)(syscall_slong_t)(syscall_ulong_t)(e)))
#define libc_seterrno_syserr2(e, ERR) (likely(!E_ISERR(e)) ? (e) : (libc_seterrno_neg((errno_t)(syscall_slong_t)(syscall_ulong_t)(e)), (ERR)))
#endif /* !__KERNEL__ */


#ifdef __CC__
DECL_BEGIN

#ifndef __locale_t_defined
#define __locale_t_defined
typedef __locale_t locale_t;
#endif /* !__locale_t_defined */

#ifndef __errno_t_defined
#define __errno_t_defined
typedef __errno_t errno_t;
#endif /* !__errno_t_defined */

#ifndef __KERNEL__
INTDEF NOBLOCK ATTR_CONST /*kos*/ errno_t *NOTHROW(LIBCCALL libc_errno_p)(void);
INTDEF NOBLOCK ATTR_CONST /*dos*/ errno_t *NOTHROW(LIBDCALL libd_errno_p)(void);
INTDEF NOBLOCK ATTR_PURE /*kos*/ errno_t NOTHROW(LIBCCALL libc_geterrno)(void);
INTDEF NOBLOCK ATTR_PURE /*dos*/ errno_t NOTHROW(LIBDCALL libd_geterrno)(void);
INTDEF NOBLOCK ATTR_PURE errno_t NOTHROW(LIBCCALL libc_geterrno_safe)(void);

/* Always returns (syscall_slong_t)-1 */
INTDEF NOBLOCK syscall_slong_t NOTHROW(__FCALL libc_seterrno)(/*kos*/ errno_t value);
INTDEF NOBLOCK syscall_slong_t NOTHROW(LIBDCALL libd_seterrno)(/*dos*/ errno_t value);
/* Same as `libc_seterrno(-value)' */
INTDEF NOBLOCK syscall_slong_t NOTHROW(__FCALL libc_seterrno_neg)(errno_t value);
INTDEF NOBLOCK ATTR_CONST /*kos*/ errno_t NOTHROW(LIBDCALL libd_errno_dos2kos)(/*dos*/ errno_t value);
INTDEF NOBLOCK ATTR_CONST /*dos*/ errno_t NOTHROW(LIBDCALL libd_errno_kos2dos)(/*kos*/ errno_t value);

INTDEF NOBLOCK ATTR_CONST /*kos*/ signo_t NOTHROW(LIBDCALL libd_signo_dos2kos)(/*dos*/ signo_t value);
INTDEF NOBLOCK ATTR_CONST /*dos*/ signo_t NOTHROW(LIBDCALL libd_signo_kos2dos)(/*kos*/ signo_t value);

/* DOS filesystem compatibility controls. */
INTDEF oflag_t libd_O_DOSPATH;   /* Either `0' or `O_DOSPATH' */
INTDEF atflag_t libd_AT_DOSPATH; /* Either `0' or `AT_DOSPATH' */

/* Check if DOS filesystem emulation should be used for `DOS$' functions. */
#define libd_have_dosfs() (libd_O_DOSPATH != 0)


#if 1
#define LIBC_HAVE_LOG_UNIMPLEMENTED 1
INTDEF void LIBCCALL libc_unimplemented(char const *__restrict name);
INTDEF void VLIBCCALL libc_unimplementedf(char const *__restrict format, ...);
#define CRT_UNIMPLEMENTED(name) libc_unimplemented(name)
#define CRT_UNIMPLEMENTEDF(...) libc_unimplementedf(__VA_ARGS__)
#else
#define CRT_UNIMPLEMENTED(name) (void)0
#define CRT_UNIMPLEMENTEDF(...) (void)0
#endif
#else /* !__KERNEL__ */
/* The kernel doesn't have an ERRNO binding */
#undef libc_seterrno_syserr
#undef libc_seterrno_syserr2
#undef errno
#undef __errno
#undef __errno_location
#undef libc_geterrno
#undef __libc_geterrno
#undef libc_geterrno_or
#undef __libc_geterrno_or
#undef libc_seterrno
#undef __libc_seterrno
#undef libd_geterrno
#undef __libd_geterrno
#undef libd_geterrno_or
#undef __libd_geterrno_or
#undef libd_seterrno
#undef __libd_seterrno
#define __libc_geterrno_or(alt) alt
#define __libc_seterrno(v)      ((void)0, -1)
#define __libd_geterrno_or(alt) alt
#define __libd_seterrno(v)      ((void)0, -1)
#define libc_geterrno_or(alt)   alt
#define libc_seterrno(v)        ((void)0, -1)
#define libd_geterrno_or(alt)   alt
#define libd_seterrno(v)        ((void)0, -1)
#endif /* __KERNEL__ */


DECL_END

#endif /* __CC__ */


#endif /* !GUARD_LIBC_API_H */
