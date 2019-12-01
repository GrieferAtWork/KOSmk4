/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_API_H
#define GUARD_LIBC_API_H 1
#define __BUILDING_LIBC 1

#ifdef __KERNEL__
#define __CRT_KOS_KERNEL 1
#else /* __KERNEL__ */
#define __CRT_KOS 1
#endif /* !__KERNEL__ */

#ifndef __OPTIMIZE_SIZE__
/* Enable system call inlining, causing calls to `sys_*' functions from <kos/syscalls.h>
 * to be inlined (as far as possible), rather than being declared as entry points to the
 * libc system call export table (libc also exports all system calls as `sys_*' symbols)
 * NOTE: When optimizing for size, we don't do this, in which case system calls used
 *       by libc library functions get linked against the system call wrappers that
 *       are always exported from libc unconditionally. */
#define __WANT_INLINE_SYSCALLS 1
#endif /* !__OPTIMIZE_SIZE__ */


/* Enable access to a variety of header functions normally
 * locked away behind various feature macros (us being libc,
 * we obviously want access to anything we intend on defining,
 * so we make our job simple by unlocking everything) */
#define _KOS_SOURCE 1
#define _KOS_KERNEL_SOURCE 1
#define _STRING_BWLQ_SOURCE 1
#define _STRING_XCHR_SOURCE 1
#define _CTYPE_MACRO_SOURCE 1
#define _DOS_SOURCE 1
#define _BSD_SOURCE 1
#define _SVID_SOURCE 1
#define _GNU_SOURCE 1
#define _LARGEFILE_SOURCE 1
#define __DEFINE_DOS_STAT_STRUCTURES 1
#define __DEFINE_KOS_STAT_STRUCTURES 1
#define __DEFINE_GLC_STAT_STRUCTURES 1
#define __DEFINE_CYG_STAT_STRUCTURES 1


/* Must load headers in 32-bit time/file-offset mode, so-as to prevent
 * any symbol re-directions from happening, which might otherwise screw
 * up libc linkage. - Instead, libc itself must always explicitly specify
 * the *64 variants of functions (e.g. `mmap64()'; `mmap()' is always the
 * 32-bit variant) */
#undef _LARGEFILE64_SOURCE
#undef _TIME64_SOURCE
#define _LARGEFILE64_SOURCE 1
#define _TIME64_SOURCE 1
#undef _TIME_T_BITS
#define _TIME_T_BITS 32
#undef _FILE_OFFSET_BITS
#define _FILE_OFFSET_BITS 32

#include <__crt.h>
#include <hybrid/compiler.h>

#include <hybrid/host.h>

#include <kos/anno.h>
#include <kos/kernel/types.h>
#include <kos/types.h>

#include <stdarg.h>
#include <stddef.h>

/* Delete CRT features for stuff that we don't implement (yet)
 * TODO: Once we do implement this stuff, delete this part! */
#undef __CRT_HAVE___ctype_b_loc
#undef __CRT_HAVE___ctype_tolower_loc
#undef __CRT_HAVE___ctype_toupper_loc
#undef __CRT_HAVE___locale_ctype_ptr
#undef __CRT_HAVE___locale_ctype_ptr_l
#undef __CRT_HAVE__isctype
#define __CRT_HAVE_unicode_utf8seqlen 1

/* Indicate that we have support for all of the different assert functions. */
#define __CRT_HAVE___afail 1
#define __CRT_HAVE___afailf 1
#define __CRT_HAVE___assert 1
#define __CRT_HAVE___assert_fail 1
#define __CRT_HAVE___assert_func 1
#define __CRT_HAVE___assertfail 1
#define __CRT_HAVE__assert 1


#ifdef __KERNEL__
#include <kernel/compiler.h>
#endif /* __KERNEL__ */

#define LIBCCALL  __LIBCCALL
#define LIBDCALL  __LIBDCALL
#define VLIBCCALL __VLIBCCALL
#define VLIBDCALL __VLIBDCALL
#undef LIBCCALL_CALLER_CLEANUP
#undef VLIBCCALL_CALLER_CLEANUP
#undef LIBDCALL_CALLER_CLEANUP
#undef VLIBDCALL_CALLER_CLEANUP
#ifdef __LIBCCALL_CALLER_CLEANUP
#define LIBCCALL_CALLER_CLEANUP 1
#endif /* !__LIBCCALL_CALLER_CLEANUP */
#ifdef __VLIBCCALL_CALLER_CLEANUP
#define VLIBCCALL_CALLER_CLEANUP 1
#endif /* __VLIBCCALL_CALLER_CLEANUP */
#ifdef __LIBDCALL_CALLER_CLEANUP
#define LIBDCALL_CALLER_CLEANUP 1
#endif /* __LIBDCALL_CALLER_CLEANUP */
#ifdef __VLIBDCALL_CALLER_CLEANUP
#define VLIBDCALL_CALLER_CLEANUP 1
#endif /* __VLIBDCALL_CALLER_CLEANUP */


#ifndef NOBLOCK
#define NOBLOCK __NOBLOCK
#endif
#ifndef THROWS
#define THROWS __THROWS
#endif

#define ATTR_LIBC_PRINTF(a, b)    __ATTR_LIBC_PRINTF(a, b)
#define ATTR_LIBC_PRINTF_P(a, b)  __ATTR_LIBC_PRINTF_P(a, b)
#define ATTR_LIBC_SCANF(a, b)     __ATTR_LIBC_SCANF(a, b)
#define ATTR_LIBC_STRFMON(a, b)   __ATTR_LIBC_STRFMON(a, b)
#define ATTR_LIBC_WPRINTF(a, b)   __ATTR_LIBC_WPRINTF(a, b)
#define ATTR_LIBC_WPRINTF_P(a, b) __ATTR_LIBC_WPRINTF_P(a, b)
#define ATTR_LIBC_WSCANF(a, b)    __ATTR_LIBC_WSCANF(a, b)

#include <ctype.h>

#define libc_isalnum(ch)  isalnum(ch)
#define libc_isalpha(ch)  isalpha(ch)
#define libc_isupper(ch)  isupper(ch)
#define libc_islower(ch)  islower(ch)
#define libc_isdigit(ch)  isdigit(ch)
#define libc_isxdigit(ch) isxdigit(ch)
#define libc_isspace(ch)  isspace(ch)
#define libc_ispunct(ch)  ispunct(ch)
#define libc_isprint(ch)  isprint(ch)
#define libc_isgraph(ch)  isgraph(ch)
#define libc_iscntrl(ch)  iscntrl(ch)
#ifdef __USE_ISOC99
#define libc_isblank(ch)  isblank(ch)
#endif /* __USE_ISOC99 */


#include <errno.h>
#define libc_seterrno_syserr(e)       (likely(!E_ISERR(e)) ? (e) : libc_seterrno((errno_t)-(syscall_slong_t)(syscall_ulong_t)(e)))
#define libc_seterrno_syserr2(e,ERR)  (likely(!E_ISERR(e)) ? (e) : (libc_seterrno((errno_t)-(syscall_slong_t)(syscall_ulong_t)(e)),(ERR)))
#define ISSEP(x)                  ((x) == '/') /* TODO: In DOS-mode, `\\' must also be accepted */
#define GET_PATHLIST_SEP()         ':'         /* TODO: In DOS-mode, `;' must be used */


#define ATTR_MALL_DEFAULT_ALIGNED   __ATTR_MALL_DEFAULT_ALIGNED
#define ATTR_MALL_PAGEALIGNED       __ATTR_MALL_PAGEALIGNED

/* Attribute for global data that is mostly read from */
#ifndef ATTR_READMOSTLY
#define ATTR_READMOSTLY   ATTR_SECTION(".data.read_mostly")
#endif /* !ATTR_READMOSTLY */

#undef __libc_geterrno
#undef __libc_seterrno
#define __libc_geterrno   libc_geterrno
#define __libc_seterrno   libc_seterrno

#ifdef __CC__
DECL_BEGIN

#ifndef __locale_t_defined
#define __locale_t_defined 1
typedef __locale_t locale_t;
#endif /* !__locale_t_defined */

#ifndef __errno_t_defined
#define __errno_t_defined 1
typedef __errno_t errno_t;
#endif /* !errno_t_defined */

INTDEF NOBLOCK ATTR_CONST errno_t *NOTHROW(LIBCCALL libc_errno_p)(void);
INTDEF NOBLOCK ATTR_PURE errno_t NOTHROW(LIBCCALL libc_geterrno)(void);
INTDEF NOBLOCK ATTR_PURE errno_t NOTHROW(LIBCCALL libc_geterrno_safe)(void);
/* Always returns (syscall_slong_t)-1 */
INTDEF NOBLOCK syscall_slong_t NOTHROW(__FCALL libc_seterrno)(errno_t value);

#if 1
#define CONFIG_LOG_LIBC_UNIMPLEMENTED 1
INTDEF void LIBCCALL libc_unimplemented(char const *__restrict name);
#define CRT_UNIMPLEMENTED(name)  libc_unimplemented(name)
#else
#define CRT_UNIMPLEMENTED(name) (void)0
#endif


DECL_END


#ifndef __KERNEL__
#if defined(__OPTIMIZE_SIZE__)
/* Disable norel access. */
#define GET_NOREL_GLOBAL(name)             __bind_##name
#define DECLARE_NOREL_GLOBAL_META(T, name) DATDEF T __bind_##name ASMNAME(#name)
#define DEFINE_NOREL_GLOBAL_META(T, name)  DATDEF T __bind_##name ASMNAME(#name)
#else /* __OPTIMIZE_SIZE__ */
#define GET_NOREL_GLOBAL(name) (*(__pdyn_##name ? __pdyn_##name : __##name##_impl()))
#define DECLARE_NOREL_GLOBAL_META(T, name) \
	INTDEF T *__pdyn_##name;               \
	INTDEF ATTR_CONST T *(LIBCCALL __##name##_impl)(void)
#ifdef __INTELLISENSE__
#define DEFINE_NOREL_GLOBAL_META(T, name, section)                                            \
	INTERN ATTR_SECTION(".bss" section "." #name) T *__pdyn_##name               = __NULLPTR; \
	PRIVATE ATTR_SECTION(".rodata" section "." #name) char const __name_##name[] = #name;     \
	INTERN ATTR_CONST ATTR_SECTION(".text" section "." #name) T *(LIBCCALL __##name##_impl)(void)
#else /* __INTELLISENSE__ */
#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#include <dlfcn.h>
#define DEFINE_NOREL_GLOBAL_META(T, name, section)                                                  \
	INTERN ATTR_SECTION(".bss" section "." #name) T *__pdyn_##name               = __NULLPTR;       \
	PRIVATE ATTR_SECTION(".rodata" section "." #name) char const __name_##name[] = #name;           \
	INTERN ATTR_CONST ATTR_SECTION(".text" section "." #name) T *(LIBCCALL __##name##_impl)(void) { \
		T *ptr = (T *)dlsym(RTLD_DEFAULT, __name_##name);                                           \
		__hybrid_assert(ptr);                                                                       \
		__hybrid_atomic_store(__pdyn_##name, ptr, __ATOMIC_RELEASE);                                \
		return ptr;                                                                                 \
	}
#endif /* !__INTELLISENSE__ */
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* !__KERNEL__ */

#endif /* __CC__ */


#endif /* !GUARD_LIBC_API_H */
