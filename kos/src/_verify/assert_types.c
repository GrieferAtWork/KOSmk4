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
#ifndef GUARD__VERIFY_ASSERT_TYPES_C
#define GUARD__VERIFY_ASSERT_TYPES_C 1
#define _KOS_SOURCE 1
#define _TIME64_SOURCE 1
#define _LARGEFILE64_SOURCE 1
#define _KOS_KERNEL_SOURCE 1

#include <hybrid/compiler.h>

#include <hybrid/floatcore.h>
#include <hybrid/typecore.h>

#include <kos/types.h>
#include <sys/types.h>

#include <stdalign.h>
#include <stddef.h>

STATIC_ASSERT(sizeof(char) == __SIZEOF_CHAR__);
STATIC_ASSERT(sizeof(signed char) == __SIZEOF_CHAR__);
STATIC_ASSERT(sizeof(unsigned char) == __SIZEOF_CHAR__);
STATIC_ASSERT(sizeof(short) == __SIZEOF_SHORT__);
STATIC_ASSERT(sizeof(signed short) == __SIZEOF_SHORT__);
STATIC_ASSERT(sizeof(unsigned short) == __SIZEOF_SHORT__);
STATIC_ASSERT(sizeof(int) == __SIZEOF_INT__);
STATIC_ASSERT(sizeof(signed int) == __SIZEOF_INT__);
STATIC_ASSERT(sizeof(unsigned int) == __SIZEOF_INT__);
STATIC_ASSERT(sizeof(long) == __SIZEOF_LONG__);
STATIC_ASSERT(sizeof(signed long) == __SIZEOF_LONG__);
STATIC_ASSERT(sizeof(unsigned long) == __SIZEOF_LONG__);
#ifdef __COMPILER_HAVE_LONGLONG
STATIC_ASSERT(sizeof(long long) == __SIZEOF_LONG_LONG__);
STATIC_ASSERT(sizeof(signed long long) == __SIZEOF_LONG_LONG__);
STATIC_ASSERT(sizeof(unsigned long long) == __SIZEOF_LONG_LONG__);
#endif /* __COMPILER_HAVE_LONGLONG */
STATIC_ASSERT(sizeof(float) == __SIZEOF_FLOAT__);
STATIC_ASSERT(sizeof(double) == __SIZEOF_DOUBLE__);
#ifdef __COMPILER_HAVE_LONGDOUBLE
STATIC_ASSERT(sizeof(long double) == __SIZEOF_LONG_DOUBLE__);
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#ifdef __native_wchar_t_defined
STATIC_ASSERT(sizeof(wchar_t) == __SIZEOF_WCHAR_T__);
#endif /* __native_wchar_t_defined */
#ifdef __native_char16_t_defined
STATIC_ASSERT(sizeof(char16_t) == 2);
STATIC_ASSERT(sizeof(char32_t) == 4);
#endif /* __native_char16_t_defined */

#include <stdint.h>


STATIC_ASSERT(__builtin_types_compatible_p(intmax_t, __INTMAX_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(uintmax_t, __UINTMAX_TYPE__));
STATIC_ASSERT(sizeof(intmax_t) == __SIZEOF_INTMAX_T__);
STATIC_ASSERT(sizeof(uintmax_t) == __SIZEOF_INTMAX_T__);

STATIC_ASSERT(__builtin_types_compatible_p(int_least8_t, __INT_LEAST8_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(int_least16_t, __INT_LEAST16_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(int_least32_t, __INT_LEAST32_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(int_least64_t, __INT_LEAST64_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(uint_least8_t, __UINT_LEAST8_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(uint_least16_t, __UINT_LEAST16_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(uint_least32_t, __UINT_LEAST32_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(uint_least64_t, __UINT_LEAST64_TYPE__));
STATIC_ASSERT(sizeof(int_least8_t) == __SIZEOF_INT_LEAST8_T__);
STATIC_ASSERT(sizeof(int_least16_t) == __SIZEOF_INT_LEAST16_T__);
STATIC_ASSERT(sizeof(int_least32_t) == __SIZEOF_INT_LEAST32_T__);
STATIC_ASSERT(sizeof(int_least64_t) == __SIZEOF_INT_LEAST64_T__);
STATIC_ASSERT(sizeof(uint_least8_t) == __SIZEOF_INT_LEAST8_T__);
STATIC_ASSERT(sizeof(uint_least16_t) == __SIZEOF_INT_LEAST16_T__);
STATIC_ASSERT(sizeof(uint_least32_t) == __SIZEOF_INT_LEAST32_T__);
STATIC_ASSERT(sizeof(uint_least64_t) == __SIZEOF_INT_LEAST64_T__);

STATIC_ASSERT(__builtin_types_compatible_p(int_fast8_t, __INT_FAST8_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(int_fast16_t, __INT_FAST16_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(int_fast32_t, __INT_FAST32_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(int_fast64_t, __INT_FAST64_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(uint_fast8_t, __UINT_FAST8_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(uint_fast16_t, __UINT_FAST16_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(uint_fast32_t, __UINT_FAST32_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(uint_fast64_t, __UINT_FAST64_TYPE__));
STATIC_ASSERT(sizeof(int_fast8_t) == __SIZEOF_INT_FAST8_T__);
STATIC_ASSERT(sizeof(int_fast16_t) == __SIZEOF_INT_FAST16_T__);
STATIC_ASSERT(sizeof(int_fast32_t) == __SIZEOF_INT_FAST32_T__);
STATIC_ASSERT(sizeof(int_fast64_t) == __SIZEOF_INT_FAST64_T__);
STATIC_ASSERT(sizeof(uint_fast8_t) == __SIZEOF_INT_FAST8_T__);
STATIC_ASSERT(sizeof(uint_fast16_t) == __SIZEOF_INT_FAST16_T__);
STATIC_ASSERT(sizeof(uint_fast32_t) == __SIZEOF_INT_FAST32_T__);
STATIC_ASSERT(sizeof(uint_fast64_t) == __SIZEOF_INT_FAST64_T__);


STATIC_ASSERT(sizeof(__LONG32_TYPE__) == 4);
STATIC_ASSERT(sizeof(__ULONG32_TYPE__) == 4);
#ifdef __LONG64_TYPE__
STATIC_ASSERT(sizeof(__LONG64_TYPE__) == 8);
STATIC_ASSERT(sizeof(__ULONG64_TYPE__) == 8);
#endif /* __LONG64_TYPE__ */

STATIC_ASSERT(__builtin_types_compatible_p(int8_t, __INT8_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(int16_t, __INT16_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(int32_t, __INT32_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(uint8_t, __UINT8_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(uint16_t, __UINT16_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(uint32_t, __UINT32_TYPE__));
STATIC_ASSERT(sizeof(int8_t) == 1);
STATIC_ASSERT(sizeof(int16_t) == 2);
STATIC_ASSERT(sizeof(int32_t) == 4);
STATIC_ASSERT(sizeof(uint8_t) == 1);
STATIC_ASSERT(sizeof(uint16_t) == 2);
STATIC_ASSERT(sizeof(uint32_t) == 4);
#ifdef __UINT64_TYPE__
STATIC_ASSERT(__builtin_types_compatible_p(int64_t, __INT64_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(uint64_t, __UINT64_TYPE__));
STATIC_ASSERT(sizeof(int64_t) == 8);
STATIC_ASSERT(sizeof(uint64_t) == 8);
#endif /* __UINT64_TYPE__ */

STATIC_ASSERT(__builtin_types_compatible_p(intptr_t, __INTPTR_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(uintptr_t, __UINTPTR_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(longptr_t, __LONGPTR_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(ulongptr_t, __ULONGPTR_TYPE__));
STATIC_ASSERT(sizeof(__INTPTR_TYPE__) == __SIZEOF_POINTER__);
STATIC_ASSERT(sizeof(__UINTPTR_TYPE__) == __SIZEOF_POINTER__);
STATIC_ASSERT(sizeof(__LONGPTR_TYPE__) == __SIZEOF_POINTER__);
STATIC_ASSERT(sizeof(__ULONGPTR_TYPE__) == __SIZEOF_POINTER__);
STATIC_ASSERT(sizeof(void *) == __SIZEOF_POINTER__);

STATIC_ASSERT(__builtin_types_compatible_p(size_t, __SIZE_TYPE__));
STATIC_ASSERT(__builtin_types_compatible_p(ssize_t, __SSIZE_TYPE__));
STATIC_ASSERT(sizeof(size_t) == __SIZEOF_SIZE_T__);
STATIC_ASSERT(sizeof(ssize_t) == __SIZEOF_SIZE_T__);


STATIC_ASSERT(INTMAX_MIN        == __INTMAX_MIN__);
STATIC_ASSERT(INTMAX_MAX        == __INTMAX_MAX__);
STATIC_ASSERT(UINTMAX_MAX       == __UINTMAX_MAX__);
STATIC_ASSERT(INT8_MIN          == __INT8_MIN__);
STATIC_ASSERT(INT16_MIN         == __INT16_MIN__);
STATIC_ASSERT(INT32_MIN         == __INT32_MIN__);
STATIC_ASSERT(INT64_MIN         == __INT64_MIN__);
STATIC_ASSERT(INT8_MAX          == __INT8_MAX__);
STATIC_ASSERT(INT16_MAX         == __INT16_MAX__);
STATIC_ASSERT(INT32_MAX         == __INT32_MAX__);
STATIC_ASSERT(INT64_MAX         == __INT64_MAX__);
STATIC_ASSERT(UINT8_MAX         == __UINT8_MAX__);
STATIC_ASSERT(UINT16_MAX        == __UINT16_MAX__);
STATIC_ASSERT(UINT32_MAX        == __UINT32_MAX__);
STATIC_ASSERT(UINT64_MAX        == __UINT64_MAX__);
STATIC_ASSERT(INT_LEAST8_MIN    == __INT_LEAST8_MIN__);
STATIC_ASSERT(INT_LEAST16_MIN   == __INT_LEAST16_MIN__);
STATIC_ASSERT(INT_LEAST32_MIN   == __INT_LEAST32_MIN__);
STATIC_ASSERT(INT_LEAST64_MIN   == __INT_LEAST64_MIN__);
STATIC_ASSERT(INT_LEAST8_MAX    == __INT_LEAST8_MAX__);
STATIC_ASSERT(INT_LEAST16_MAX   == __INT_LEAST16_MAX__);
STATIC_ASSERT(INT_LEAST32_MAX   == __INT_LEAST32_MAX__);
STATIC_ASSERT(INT_LEAST64_MAX   == __INT_LEAST64_MAX__);
STATIC_ASSERT(UINT_LEAST8_MAX   == __UINT_LEAST8_MAX__);
STATIC_ASSERT(UINT_LEAST16_MAX  == __UINT_LEAST16_MAX__);
STATIC_ASSERT(UINT_LEAST32_MAX  == __UINT_LEAST32_MAX__);
STATIC_ASSERT(UINT_LEAST64_MAX  == __UINT_LEAST64_MAX__);
STATIC_ASSERT(INT_FAST8_MIN     == __INT_FAST8_MIN__);
STATIC_ASSERT(INT_FAST16_MIN    == __INT_FAST16_MIN__);
STATIC_ASSERT(INT_FAST32_MIN    == __INT_FAST32_MIN__);
STATIC_ASSERT(INT_FAST64_MIN    == __INT_FAST64_MIN__);
STATIC_ASSERT(INT_FAST8_MAX     == __INT_FAST8_MAX__);
STATIC_ASSERT(INT_FAST16_MAX    == __INT_FAST16_MAX__);
STATIC_ASSERT(INT_FAST32_MAX    == __INT_FAST32_MAX__);
STATIC_ASSERT(INT_FAST64_MAX    == __INT_FAST64_MAX__);
STATIC_ASSERT(UINT_FAST8_MAX    == __UINT_FAST8_MAX__);
STATIC_ASSERT(UINT_FAST16_MAX   == __UINT_FAST16_MAX__);
STATIC_ASSERT(UINT_FAST32_MAX   == __UINT_FAST32_MAX__);
STATIC_ASSERT(UINT_FAST64_MAX   == __UINT_FAST64_MAX__);
STATIC_ASSERT(INTPTR_MIN        == __INTPTR_MIN__);
STATIC_ASSERT(INTPTR_MAX        == __INTPTR_MAX__);
STATIC_ASSERT(UINTPTR_MAX       == __UINTPTR_MAX__);
STATIC_ASSERT(SIZE_MAX          == __SIZE_MAX__);
STATIC_ASSERT(PTRDIFF_MIN       == __PTRDIFF_MIN__);
STATIC_ASSERT(PTRDIFF_MAX       == __PTRDIFF_MAX__);
STATIC_ASSERT(SIG_ATOMIC_MIN    == __SIG_ATOMIC_MIN__);
STATIC_ASSERT(SIG_ATOMIC_MAX    == __SIG_ATOMIC_MAX__);
STATIC_ASSERT(WCHAR_MIN         == __WCHAR_MIN__);
STATIC_ASSERT(WCHAR_MAX         == __WCHAR_MAX__);
STATIC_ASSERT(WINT_MIN          == __WINT_MIN__);
STATIC_ASSERT(WINT_MAX          == __WINT_MAX__);



#include <pthread.h>
STATIC_ASSERT(sizeof(pthread_t) == __SIZEOF_PTHREAD_T);
STATIC_ASSERT(sizeof(pthread_key_t) == __SIZEOF_PTHREAD_KEY_T);
STATIC_ASSERT(sizeof(pthread_once_t) == __SIZEOF_PTHREAD_ONCE_T);
STATIC_ASSERT(sizeof(pthread_attr_t) == __SIZEOF_PTHREAD_ATTR_T);
STATIC_ASSERT(sizeof(pthread_mutex_t) == __SIZEOF_PTHREAD_MUTEX_T);
STATIC_ASSERT(sizeof(pthread_mutexattr_t) == __SIZEOF_PTHREAD_MUTEXATTR_T);
STATIC_ASSERT(sizeof(pthread_cond_t) == __SIZEOF_PTHREAD_COND_T);
STATIC_ASSERT(sizeof(pthread_condattr_t) == __SIZEOF_PTHREAD_CONDATTR_T);
STATIC_ASSERT(sizeof(pthread_rwlock_t) == __SIZEOF_PTHREAD_RWLOCK_T);
STATIC_ASSERT(sizeof(pthread_rwlockattr_t) == __SIZEOF_PTHREAD_RWLOCKATTR_T);
STATIC_ASSERT(sizeof(pthread_barrier_t) == __SIZEOF_PTHREAD_BARRIER_T);
STATIC_ASSERT(sizeof(pthread_barrierattr_t) == __SIZEOF_PTHREAD_BARRIERATTR_T);


#include <threads.h>
STATIC_ASSERT(sizeof(thrd_t) == __SIZEOF_PTHREAD_T);
STATIC_ASSERT(sizeof(tss_t) == __SIZEOF_PTHREAD_KEY_T);
STATIC_ASSERT(sizeof(once_flag) == __SIZEOF_PTHREAD_ONCE_T);
STATIC_ASSERT(sizeof(mtx_t) == __SIZEOF_PTHREAD_MUTEX_T);
STATIC_ASSERT(sizeof(cnd_t) == __SIZEOF_PTHREAD_COND_T);


#include <elf.h>
STATIC_ASSERT(sizeof(Elf32_Half) == __SIZEOF_ELF32_HALF__);
STATIC_ASSERT(sizeof(Elf64_Half) == __SIZEOF_ELF64_HALF__);
STATIC_ASSERT(sizeof(Elf32_Word) == __SIZEOF_ELF32_WORD__);
STATIC_ASSERT(sizeof(Elf64_Word) == __SIZEOF_ELF64_WORD__);
STATIC_ASSERT(sizeof(Elf32_Xword) == __SIZEOF_ELF32_XWORD__);
STATIC_ASSERT(sizeof(Elf64_Xword) == __SIZEOF_ELF64_XWORD__);
STATIC_ASSERT(sizeof(Elf32_Addr) == __SIZEOF_ELF32_ADDR__);
STATIC_ASSERT(sizeof(Elf64_Addr) == __SIZEOF_ELF64_ADDR__);
STATIC_ASSERT(sizeof(Elf32_Off) == __SIZEOF_ELF32_OFF__);
STATIC_ASSERT(sizeof(Elf64_Off) == __SIZEOF_ELF64_OFF__);
STATIC_ASSERT(sizeof(Elf32_Section) == __SIZEOF_ELF32_SECTION__);
STATIC_ASSERT(sizeof(Elf64_Section) == __SIZEOF_ELF64_SECTION__);
STATIC_ASSERT(sizeof(Elf32_Versym) == __SIZEOF_ELF32_VERSYM__);
STATIC_ASSERT(sizeof(Elf64_Versym) == __SIZEOF_ELF64_VERSYM__);


/*[[[deemon
import * from ...misc.libgen.assert_offsetof;
local files = {
	"../../include/bits/itimerspec.h",
	"../../include/bits/timespec.h",
	"../../include/bits/timeval.h",
	"../../include/bits/siginfo-struct.h",
	"../../include/bits/sigaction-struct.h",
	"../../include/elf.h",
	"../../include/kos/hop.h",
	"../../include/kos/sysctl.h",
	"../../include/kos/bits/ukern-struct.h",
	"../../include/kos/bits/debugtrap.h",
	"../../include/kos/bits/library-listdef.h",
};

local include_prefixes = {
	"../../include",
};

function genAsserts(f) {
	for (local pfx: include_prefixes) {
		if (f.startswith(pfx)) {
			print "#include <" + f[#pfx:].lstrip("/") + ">";
			goto do_gen_asserts;
		}
	}
	print "#include", repr(f);
do_gen_asserts:
	generateAssertions(f);
	print;
	print;
	print;
	print;
	print;
}

for (local f: files)
	genAsserts(f);

]]]*/
#include <bits/itimerspec.h>

/* struct itimerspec */
STATIC_ASSERT(offsetof(struct itimerspec, it_value) == __OFFSET_ITIMERSPEC_VALUE);
STATIC_ASSERT(offsetof(struct itimerspec, it_interval) == __OFFSET_ITIMERSPEC_INTERVAL);
STATIC_ASSERT(sizeof(struct itimerspec) == __SIZEOF_ITIMERSPEC);

/* struct itimerspec64 */
STATIC_ASSERT(offsetof(struct itimerspec64, it_value) == __OFFSET_ITIMERSPEC64_VALUE);
STATIC_ASSERT(offsetof(struct itimerspec64, it_interval) == __OFFSET_ITIMERSPEC64_INTERVAL);
STATIC_ASSERT(sizeof(struct itimerspec64) == __SIZEOF_ITIMERSPEC64);





#include <bits/timespec.h>

/* struct timespec */
STATIC_ASSERT(offsetof(struct timespec, tv_sec) == __OFFSET_TIMESPEC_SEC);
STATIC_ASSERT(offsetof(struct timespec, tv_nsec) == __OFFSET_TIMESPEC_NSEC);
STATIC_ASSERT(sizeof(struct timespec) == __SIZEOF_TIMESPEC);

/* struct timespec64 */
STATIC_ASSERT(offsetof(struct timespec64, tv_sec) == __OFFSET_TIMESPEC64_SEC);
STATIC_ASSERT(offsetof(struct timespec64, tv_nsec) == __OFFSET_TIMESPEC64_NSEC);
STATIC_ASSERT(sizeof(struct timespec64) == __SIZEOF_TIMESPEC64);





#include <bits/timeval.h>

/* struct timeval */
STATIC_ASSERT(offsetof(struct timeval, tv_usec) == __OFFSET_TIMEVAL_USEC);
STATIC_ASSERT(offsetof(struct timeval, tv_sec) == __OFFSET_TIMEVAL_SEC);
STATIC_ASSERT(sizeof(struct timeval) == __SIZEOF_TIMEVAL);

/* struct timeval64 */
STATIC_ASSERT(offsetof(struct timeval64, tv_usec) == __OFFSET_TIMEVAL64_USEC);
STATIC_ASSERT(offsetof(struct timeval64, tv_sec) == __OFFSET_TIMEVAL64_SEC);
STATIC_ASSERT(sizeof(struct timeval64) == __SIZEOF_TIMEVAL64);





#include <bits/siginfo-struct.h>

/* struct __siginfo_struct */
STATIC_ASSERT(offsetof(struct __siginfo_struct, si_addr) == __OFFSET_SIGINFO_ADDR);
STATIC_ASSERT(offsetof(struct __siginfo_struct, si_addr_lsb) == __OFFSET_SIGINFO_ADDR_LSB);
STATIC_ASSERT(offsetof(struct __siginfo_struct, si_arch) == __OFFSET_SIGINFO_ARCH);
STATIC_ASSERT(offsetof(struct __siginfo_struct, si_band) == __OFFSET_SIGINFO_BAND);
STATIC_ASSERT(offsetof(struct __siginfo_struct, si_call_addr) == __OFFSET_SIGINFO_CALL_ADDR);
STATIC_ASSERT(offsetof(struct __siginfo_struct, si_code) == __OFFSET_SIGINFO_CODE);
STATIC_ASSERT(offsetof(struct __siginfo_struct, si_errno) == __OFFSET_SIGINFO_ERRNO);
STATIC_ASSERT(offsetof(struct __siginfo_struct, si_fd) == __OFFSET_SIGINFO_FD);
STATIC_ASSERT(offsetof(struct __siginfo_struct, si_int) == __OFFSET_SIGINFO_INT);
STATIC_ASSERT(offsetof(struct __siginfo_struct, si_lower) == __OFFSET_SIGINFO_LOWER);
STATIC_ASSERT(offsetof(struct __siginfo_struct, si_overrun) == __OFFSET_SIGINFO_OVERRUN);
STATIC_ASSERT(offsetof(struct __siginfo_struct, si_pid) == __OFFSET_SIGINFO_PID);
STATIC_ASSERT(offsetof(struct __siginfo_struct, si_ptr) == __OFFSET_SIGINFO_PTR);
STATIC_ASSERT(offsetof(struct __siginfo_struct, si_signo) == __OFFSET_SIGINFO_SIGNO);
STATIC_ASSERT(offsetof(struct __siginfo_struct, si_status) == __OFFSET_SIGINFO_STATUS);
STATIC_ASSERT(offsetof(struct __siginfo_struct, si_stime) == __OFFSET_SIGINFO_STIME);
STATIC_ASSERT(offsetof(struct __siginfo_struct, si_syscall) == __OFFSET_SIGINFO_SYSCALL);
STATIC_ASSERT(offsetof(struct __siginfo_struct, si_timerid) == __OFFSET_SIGINFO_TIMERID);
STATIC_ASSERT(offsetof(struct __siginfo_struct, si_uid) == __OFFSET_SIGINFO_UID);
STATIC_ASSERT(offsetof(struct __siginfo_struct, si_upper) == __OFFSET_SIGINFO_UPPER);
STATIC_ASSERT(offsetof(struct __siginfo_struct, si_utime) == __OFFSET_SIGINFO_UTIME);
STATIC_ASSERT(offsetof(struct __siginfo_struct, si_value) == __OFFSET_SIGINFO_VALUE);





#include <bits/sigaction-struct.h>

/* struct sigaction */
STATIC_ASSERT(offsetof(struct sigaction, sa_flags) == __OFFSET_SIGACTION_FLAGS);
STATIC_ASSERT(offsetof(struct sigaction, sa_handler) == __OFFSET_SIGACTION_HANDLER);
STATIC_ASSERT(offsetof(struct sigaction, sa_mask) == __OFFSET_SIGACTION_MASK);
STATIC_ASSERT(offsetof(struct sigaction, sa_restorer) == __OFFSET_SIGACTION_RESTORER);
STATIC_ASSERT(offsetof(struct sigaction, sa_sigaction) == __OFFSET_SIGACTION_SIGACTION);
STATIC_ASSERT(sizeof(struct sigaction) == __SIZEOF_SIGACTION);
STATIC_ASSERT(alignof(struct sigaction) == __ALIGNOF_SIGACTION);





#include <elf.h>

/* struct elf32_ehdr */
STATIC_ASSERT(offsetof(struct elf32_ehdr, e_ehsize) == __OFFSET_ELF32_EHDR_EHSIZE);
STATIC_ASSERT(offsetof(struct elf32_ehdr, e_entry) == __OFFSET_ELF32_EHDR_ENTRY);
STATIC_ASSERT(offsetof(struct elf32_ehdr, e_flags) == __OFFSET_ELF32_EHDR_FLAGS);
STATIC_ASSERT(offsetof(struct elf32_ehdr, e_ident) == __OFFSET_ELF32_EHDR_IDENT);
STATIC_ASSERT(offsetof(struct elf32_ehdr, e_machine) == __OFFSET_ELF32_EHDR_MACHINE);
STATIC_ASSERT(offsetof(struct elf32_ehdr, e_phentsize) == __OFFSET_ELF32_EHDR_PHENTSIZE);
STATIC_ASSERT(offsetof(struct elf32_ehdr, e_phnum) == __OFFSET_ELF32_EHDR_PHNUM);
STATIC_ASSERT(offsetof(struct elf32_ehdr, e_phoff) == __OFFSET_ELF32_EHDR_PHOFF);
STATIC_ASSERT(offsetof(struct elf32_ehdr, e_shentsize) == __OFFSET_ELF32_EHDR_SHENTSIZE);
STATIC_ASSERT(offsetof(struct elf32_ehdr, e_shnum) == __OFFSET_ELF32_EHDR_SHNUM);
STATIC_ASSERT(offsetof(struct elf32_ehdr, e_shoff) == __OFFSET_ELF32_EHDR_SHOFF);
STATIC_ASSERT(offsetof(struct elf32_ehdr, e_shstrndx) == __OFFSET_ELF32_EHDR_SHSTRNDX);
STATIC_ASSERT(offsetof(struct elf32_ehdr, e_type) == __OFFSET_ELF32_EHDR_TYPE);
STATIC_ASSERT(offsetof(struct elf32_ehdr, e_version) == __OFFSET_ELF32_EHDR_VERSION);
STATIC_ASSERT(sizeof(struct elf32_ehdr) == __SIZEOF_ELF32_EHDR);

/* struct elf64_ehdr */
STATIC_ASSERT(offsetof(struct elf64_ehdr, e_ehsize) == __OFFSET_ELF64_EHDR_EHSIZE);
STATIC_ASSERT(offsetof(struct elf64_ehdr, e_entry) == __OFFSET_ELF64_EHDR_ENTRY);
STATIC_ASSERT(offsetof(struct elf64_ehdr, e_flags) == __OFFSET_ELF64_EHDR_FLAGS);
STATIC_ASSERT(offsetof(struct elf64_ehdr, e_ident) == __OFFSET_ELF64_EHDR_IDENT);
STATIC_ASSERT(offsetof(struct elf64_ehdr, e_machine) == __OFFSET_ELF64_EHDR_MACHINE);
STATIC_ASSERT(offsetof(struct elf64_ehdr, e_phentsize) == __OFFSET_ELF64_EHDR_PHENTSIZE);
STATIC_ASSERT(offsetof(struct elf64_ehdr, e_phnum) == __OFFSET_ELF64_EHDR_PHNUM);
STATIC_ASSERT(offsetof(struct elf64_ehdr, e_phoff) == __OFFSET_ELF64_EHDR_PHOFF);
STATIC_ASSERT(offsetof(struct elf64_ehdr, e_shentsize) == __OFFSET_ELF64_EHDR_SHENTSIZE);
STATIC_ASSERT(offsetof(struct elf64_ehdr, e_shnum) == __OFFSET_ELF64_EHDR_SHNUM);
STATIC_ASSERT(offsetof(struct elf64_ehdr, e_shoff) == __OFFSET_ELF64_EHDR_SHOFF);
STATIC_ASSERT(offsetof(struct elf64_ehdr, e_shstrndx) == __OFFSET_ELF64_EHDR_SHSTRNDX);
STATIC_ASSERT(offsetof(struct elf64_ehdr, e_type) == __OFFSET_ELF64_EHDR_TYPE);
STATIC_ASSERT(offsetof(struct elf64_ehdr, e_version) == __OFFSET_ELF64_EHDR_VERSION);
STATIC_ASSERT(sizeof(struct elf64_ehdr) == __SIZEOF_ELF64_EHDR);

/* struct elf32_shdr */
STATIC_ASSERT(offsetof(struct elf32_shdr, sh_addr) == __OFFSET_ELF32_SHDR_ADDR);
STATIC_ASSERT(offsetof(struct elf32_shdr, sh_addralign) == __OFFSET_ELF32_SHDR_ADDRALIGN);
STATIC_ASSERT(offsetof(struct elf32_shdr, sh_entsize) == __OFFSET_ELF32_SHDR_ENTSIZE);
STATIC_ASSERT(offsetof(struct elf32_shdr, sh_flags) == __OFFSET_ELF32_SHDR_FLAGS);
STATIC_ASSERT(offsetof(struct elf32_shdr, sh_info) == __OFFSET_ELF32_SHDR_INFO);
STATIC_ASSERT(offsetof(struct elf32_shdr, sh_link) == __OFFSET_ELF32_SHDR_LINK);
STATIC_ASSERT(offsetof(struct elf32_shdr, sh_name) == __OFFSET_ELF32_SHDR_NAME);
STATIC_ASSERT(offsetof(struct elf32_shdr, sh_offset) == __OFFSET_ELF32_SHDR_OFFSET);
STATIC_ASSERT(offsetof(struct elf32_shdr, sh_size) == __OFFSET_ELF32_SHDR_SIZE);
STATIC_ASSERT(offsetof(struct elf32_shdr, sh_type) == __OFFSET_ELF32_SHDR_TYPE);
STATIC_ASSERT(sizeof(struct elf32_shdr) == __SIZEOF_ELF32_SHDR);

/* struct elf64_shdr */
STATIC_ASSERT(offsetof(struct elf64_shdr, sh_addr) == __OFFSET_ELF64_SHDR_ADDR);
STATIC_ASSERT(offsetof(struct elf64_shdr, sh_addralign) == __OFFSET_ELF64_SHDR_ADDRALIGN);
STATIC_ASSERT(offsetof(struct elf64_shdr, sh_entsize) == __OFFSET_ELF64_SHDR_ENTSIZE);
STATIC_ASSERT(offsetof(struct elf64_shdr, sh_flags) == __OFFSET_ELF64_SHDR_FLAGS);
STATIC_ASSERT(offsetof(struct elf64_shdr, sh_info) == __OFFSET_ELF64_SHDR_INFO);
STATIC_ASSERT(offsetof(struct elf64_shdr, sh_link) == __OFFSET_ELF64_SHDR_LINK);
STATIC_ASSERT(offsetof(struct elf64_shdr, sh_name) == __OFFSET_ELF64_SHDR_NAME);
STATIC_ASSERT(offsetof(struct elf64_shdr, sh_offset) == __OFFSET_ELF64_SHDR_OFFSET);
STATIC_ASSERT(offsetof(struct elf64_shdr, sh_size) == __OFFSET_ELF64_SHDR_SIZE);
STATIC_ASSERT(offsetof(struct elf64_shdr, sh_type) == __OFFSET_ELF64_SHDR_TYPE);
STATIC_ASSERT(sizeof(struct elf64_shdr) == __SIZEOF_ELF64_SHDR);

/* struct elf32_chdr */
STATIC_ASSERT(offsetof(struct elf32_chdr, ch_addralign) == __OFFSET_ELF32_CHDR_ADDRALIGN);
STATIC_ASSERT(offsetof(struct elf32_chdr, ch_size) == __OFFSET_ELF32_CHDR_SIZE);
STATIC_ASSERT(offsetof(struct elf32_chdr, ch_type) == __OFFSET_ELF32_CHDR_TYPE);
STATIC_ASSERT(sizeof(struct elf32_chdr) == __SIZEOF_ELF32_CHDR);

/* struct elf64_chdr */
STATIC_ASSERT(offsetof(struct elf64_chdr, ch_addralign) == __OFFSET_ELF64_CHDR_ADDRALIGN);
STATIC_ASSERT(offsetof(struct elf64_chdr, ch_size) == __OFFSET_ELF64_CHDR_SIZE);
STATIC_ASSERT(offsetof(struct elf64_chdr, ch_type) == __OFFSET_ELF64_CHDR_TYPE);
STATIC_ASSERT(sizeof(struct elf64_chdr) == __SIZEOF_ELF64_CHDR);





#include <kos/hop.h>

/* struct hop_openfd */
STATIC_ASSERT(offsetof(struct hop_openfd, of_flags) == __OFFSET_HOP_OPENFD_FLAGS);
STATIC_ASSERT(offsetof(struct hop_openfd, of_hint) == __OFFSET_HOP_OPENFD_HINT);
STATIC_ASSERT(offsetof(struct hop_openfd, of_mode) == __OFFSET_HOP_OPENFD_MODE);
STATIC_ASSERT(sizeof(struct hop_openfd) == __SIZEOF_HOP_OPENFD);

/* struct hop_handle_stat */
STATIC_ASSERT(offsetof(struct hop_handle_stat, hs_address) == __OFFSET_HOP_HANDLE_STAT_ADDRESS);
STATIC_ASSERT(offsetof(struct hop_handle_stat, hs_kind) == __OFFSET_HOP_HANDLE_STAT_KIND);
STATIC_ASSERT(offsetof(struct hop_handle_stat, hs_mode) == __OFFSET_HOP_HANDLE_STAT_MODE);
STATIC_ASSERT(offsetof(struct hop_handle_stat, hs_refcnt) == __OFFSET_HOP_HANDLE_STAT_REFCNT);
STATIC_ASSERT(offsetof(struct hop_handle_stat, hs_struct_size) == __OFFSET_HOP_HANDLE_STAT_STRUCT_SIZE);
STATIC_ASSERT(offsetof(struct hop_handle_stat, hs_type) == __OFFSET_HOP_HANDLE_STAT_TYPE);
STATIC_ASSERT(offsetof(struct hop_handle_stat, hs_typename) == __OFFSET_HOP_HANDLE_STAT_TYPENAME);
STATIC_ASSERT(sizeof(struct hop_handle_stat) == __SIZEOF_HOP_HANDLE_STAT);

/* struct hop_datablock_stat */
STATIC_ASSERT(offsetof(struct hop_datablock_stat, ds_features) == __OFFSET_HOP_DATABLOCK_STAT_FEATURES);
STATIC_ASSERT(offsetof(struct hop_datablock_stat, ds_pageshift) == __OFFSET_HOP_DATABLOCK_STAT_PAGESHIFT);
STATIC_ASSERT(offsetof(struct hop_datablock_stat, ds_part_changed_pages) == __OFFSET_HOP_DATABLOCK_STAT_PART_CHANGED_PAGES);
STATIC_ASSERT(offsetof(struct hop_datablock_stat, ds_part_f_changed) == __OFFSET_HOP_DATABLOCK_STAT_PART_F_CHANGED);
STATIC_ASSERT(offsetof(struct hop_datablock_stat, ds_part_f_changed_pages) == __OFFSET_HOP_DATABLOCK_STAT_PART_F_CHANGED_PAGES);
STATIC_ASSERT(offsetof(struct hop_datablock_stat, ds_part_f_locked) == __OFFSET_HOP_DATABLOCK_STAT_PART_F_LOCKED);
STATIC_ASSERT(offsetof(struct hop_datablock_stat, ds_part_f_locked_pages) == __OFFSET_HOP_DATABLOCK_STAT_PART_F_LOCKED_PAGES);
STATIC_ASSERT(offsetof(struct hop_datablock_stat, ds_part_init_pages) == __OFFSET_HOP_DATABLOCK_STAT_PART_INIT_PAGES);
STATIC_ASSERT(offsetof(struct hop_datablock_stat, ds_part_mapped) == __OFFSET_HOP_DATABLOCK_STAT_PART_MAPPED);
STATIC_ASSERT(offsetof(struct hop_datablock_stat, ds_part_mapped_pages) == __OFFSET_HOP_DATABLOCK_STAT_PART_MAPPED_PAGES);
STATIC_ASSERT(offsetof(struct hop_datablock_stat, ds_part_ram_blocks) == __OFFSET_HOP_DATABLOCK_STAT_PART_RAM_BLOCKS);
STATIC_ASSERT(offsetof(struct hop_datablock_stat, ds_part_st_incore) == __OFFSET_HOP_DATABLOCK_STAT_PART_ST_INCORE);
STATIC_ASSERT(offsetof(struct hop_datablock_stat, ds_part_st_incore_pages) == __OFFSET_HOP_DATABLOCK_STAT_PART_ST_INCORE_PAGES);
STATIC_ASSERT(offsetof(struct hop_datablock_stat, ds_part_st_inswap) == __OFFSET_HOP_DATABLOCK_STAT_PART_ST_INSWAP);
STATIC_ASSERT(offsetof(struct hop_datablock_stat, ds_part_st_inswap_pages) == __OFFSET_HOP_DATABLOCK_STAT_PART_ST_INSWAP_PAGES);
STATIC_ASSERT(offsetof(struct hop_datablock_stat, ds_part_st_locked) == __OFFSET_HOP_DATABLOCK_STAT_PART_ST_LOCKED);
STATIC_ASSERT(offsetof(struct hop_datablock_stat, ds_part_st_locked_pages) == __OFFSET_HOP_DATABLOCK_STAT_PART_ST_LOCKED_PAGES);
STATIC_ASSERT(offsetof(struct hop_datablock_stat, ds_part_swap_blocks) == __OFFSET_HOP_DATABLOCK_STAT_PART_SWAP_BLOCKS);
STATIC_ASSERT(offsetof(struct hop_datablock_stat, ds_part_uninit_pages) == __OFFSET_HOP_DATABLOCK_STAT_PART_UNINIT_PAGES);
STATIC_ASSERT(offsetof(struct hop_datablock_stat, ds_struct_size) == __OFFSET_HOP_DATABLOCK_STAT_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct hop_datablock_stat) == __SIZEOF_HOP_DATABLOCK_STAT);

/* struct hop_datablock_syncpages */
STATIC_ASSERT(offsetof(struct hop_datablock_syncpages, dsp_count) == __OFFSET_HOP_DATABLOCK_SYNCPAGES_COUNT);
STATIC_ASSERT(offsetof(struct hop_datablock_syncpages, dsp_maxpage) == __OFFSET_HOP_DATABLOCK_SYNCPAGES_MAXPAGE);
STATIC_ASSERT(offsetof(struct hop_datablock_syncpages, dsp_minpage) == __OFFSET_HOP_DATABLOCK_SYNCPAGES_MINPAGE);
STATIC_ASSERT(offsetof(struct hop_datablock_syncpages, dsp_struct_size) == __OFFSET_HOP_DATABLOCK_SYNCPAGES_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct hop_datablock_syncpages) == __SIZEOF_HOP_DATABLOCK_SYNCPAGES);

/* struct hop_datablock_syncbytes */
STATIC_ASSERT(offsetof(struct hop_datablock_syncbytes, dsb_count) == __OFFSET_HOP_DATABLOCK_SYNCBYTES_COUNT);
STATIC_ASSERT(offsetof(struct hop_datablock_syncbytes, dsb_maxbyte) == __OFFSET_HOP_DATABLOCK_SYNCBYTES_MAXBYTE);
STATIC_ASSERT(offsetof(struct hop_datablock_syncbytes, dsb_minbyte) == __OFFSET_HOP_DATABLOCK_SYNCBYTES_MINBYTE);
STATIC_ASSERT(offsetof(struct hop_datablock_syncbytes, dsb_struct_size) == __OFFSET_HOP_DATABLOCK_SYNCBYTES_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct hop_datablock_syncbytes) == __SIZEOF_HOP_DATABLOCK_SYNCBYTES);

/* struct hop_datablock_openpart */
STATIC_ASSERT(offsetof(struct hop_datablock_openpart, dop_openfd) == __OFFSET_HOP_DATABLOCK_OPENPART_OPENFD);
STATIC_ASSERT(offsetof(struct hop_datablock_openpart, dop_pageno) == __OFFSET_HOP_DATABLOCK_OPENPART_PAGENO);
STATIC_ASSERT(offsetof(struct hop_datablock_openpart, dop_pages_hint) == __OFFSET_HOP_DATABLOCK_OPENPART_PAGES_HINT);
STATIC_ASSERT(offsetof(struct hop_datablock_openpart, dop_struct_size) == __OFFSET_HOP_DATABLOCK_OPENPART_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct hop_datablock_openpart) == __SIZEOF_HOP_DATABLOCK_OPENPART);

/* struct hop_datablock_haschanged */
STATIC_ASSERT(offsetof(struct hop_datablock_haschanged, dhc_maxbyte) == __OFFSET_HOP_DATABLOCK_HASCHANGED_MAXBYTE);
STATIC_ASSERT(offsetof(struct hop_datablock_haschanged, dhc_minbyte) == __OFFSET_HOP_DATABLOCK_HASCHANGED_MINBYTE);
STATIC_ASSERT(offsetof(struct hop_datablock_haschanged, dhc_struct_size) == __OFFSET_HOP_DATABLOCK_HASCHANGED_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct hop_datablock_haschanged) == __SIZEOF_HOP_DATABLOCK_HASCHANGED);

/* struct hop_datablock_open_futex */
STATIC_ASSERT(offsetof(struct hop_datablock_open_futex, dof_address) == __OFFSET_HOP_DATABLOCK_OPEN_FUTEX_ADDRESS);
STATIC_ASSERT(offsetof(struct hop_datablock_open_futex, dof_openfd) == __OFFSET_HOP_DATABLOCK_OPEN_FUTEX_OPENFD);
STATIC_ASSERT(offsetof(struct hop_datablock_open_futex, dof_struct_size) == __OFFSET_HOP_DATABLOCK_OPEN_FUTEX_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct hop_datablock_open_futex) == __SIZEOF_HOP_DATABLOCK_OPEN_FUTEX);

/* struct hop_blockdevice_stat */
STATIC_ASSERT(offsetof(struct hop_blockdevice_stat, bs_device_flag) == __OFFSET_HOP_BLOCKDEVICE_STAT_DEVICE_FLAG);
STATIC_ASSERT(offsetof(struct hop_blockdevice_stat, bs_devno) == __OFFSET_HOP_BLOCKDEVICE_STAT_DEVNO);
STATIC_ASSERT(offsetof(struct hop_blockdevice_stat, bs_name) == __OFFSET_HOP_BLOCKDEVICE_STAT_NAME);
STATIC_ASSERT(offsetof(struct hop_blockdevice_stat, bs_partcount) == __OFFSET_HOP_BLOCKDEVICE_STAT_PARTCOUNT);
STATIC_ASSERT(offsetof(struct hop_blockdevice_stat, bs_sector_count) == __OFFSET_HOP_BLOCKDEVICE_STAT_SECTOR_COUNT);
STATIC_ASSERT(offsetof(struct hop_blockdevice_stat, bs_sector_size) == __OFFSET_HOP_BLOCKDEVICE_STAT_SECTOR_SIZE);
STATIC_ASSERT(offsetof(struct hop_blockdevice_stat, bs_struct_size) == __OFFSET_HOP_BLOCKDEVICE_STAT_STRUCT_SIZE);
STATIC_ASSERT(offsetof(struct hop_blockdevice_stat, bs_total_bytes) == __OFFSET_HOP_BLOCKDEVICE_STAT_TOTAL_BYTES);
STATIC_ASSERT(sizeof(struct hop_blockdevice_stat) == __SIZEOF_HOP_BLOCKDEVICE_STAT);

/* struct hop_blockdevice_openpart */
STATIC_ASSERT(offsetof(struct hop_blockdevice_openpart, bop_openfd) == __OFFSET_HOP_BLOCKDEVICE_OPENPART_OPENFD);
STATIC_ASSERT(offsetof(struct hop_blockdevice_openpart, bop_partno) == __OFFSET_HOP_BLOCKDEVICE_OPENPART_PARTNO);
STATIC_ASSERT(offsetof(struct hop_blockdevice_openpart, bop_struct_size) == __OFFSET_HOP_BLOCKDEVICE_OPENPART_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct hop_blockdevice_openpart) == __SIZEOF_HOP_BLOCKDEVICE_OPENPART);

/* struct hop_inode_chmod */
STATIC_ASSERT(offsetof(struct hop_inode_chmod, icm_perm_flag) == __OFFSET_HOP_INODE_CHMOD_PERM_FLAG);
STATIC_ASSERT(offsetof(struct hop_inode_chmod, icm_perm_mask) == __OFFSET_HOP_INODE_CHMOD_PERM_MASK);
STATIC_ASSERT(offsetof(struct hop_inode_chmod, icm_perm_old) == __OFFSET_HOP_INODE_CHMOD_PERM_OLD);
STATIC_ASSERT(offsetof(struct hop_inode_chmod, icm_struct_size) == __OFFSET_HOP_INODE_CHMOD_STRUCT_SIZE);

/* struct hop_inode_chown */
STATIC_ASSERT(offsetof(struct hop_inode_chown, ico_newgroup) == __OFFSET_HOP_INODE_CHOWN_NEWGROUP);
STATIC_ASSERT(offsetof(struct hop_inode_chown, ico_newowner) == __OFFSET_HOP_INODE_CHOWN_NEWOWNER);
STATIC_ASSERT(offsetof(struct hop_inode_chown, ico_oldgroup) == __OFFSET_HOP_INODE_CHOWN_OLDGROUP);
STATIC_ASSERT(offsetof(struct hop_inode_chown, ico_oldowner) == __OFFSET_HOP_INODE_CHOWN_OLDOWNER);
STATIC_ASSERT(offsetof(struct hop_inode_chown, ico_struct_size) == __OFFSET_HOP_INODE_CHOWN_STRUCT_SIZE);

/* struct hop_directory_opennode */
STATIC_ASSERT(offsetof(struct hop_directory_opennode, don_dent) == __OFFSET_HOP_DIRECTORY_OPENNODE_DENT);
STATIC_ASSERT(offsetof(struct hop_directory_opennode, don_flags) == __OFFSET_HOP_DIRECTORY_OPENNODE_FLAGS);
STATIC_ASSERT(offsetof(struct hop_directory_opennode, don_len) == __OFFSET_HOP_DIRECTORY_OPENNODE_LEN);
STATIC_ASSERT(offsetof(struct hop_directory_opennode, don_name) == __OFFSET_HOP_DIRECTORY_OPENNODE_NAME);
STATIC_ASSERT(offsetof(struct hop_directory_opennode, don_node) == __OFFSET_HOP_DIRECTORY_OPENNODE_NODE);
STATIC_ASSERT(offsetof(struct hop_directory_opennode, don_struct_size) == __OFFSET_HOP_DIRECTORY_OPENNODE_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct hop_directory_opennode) == __SIZEOF_HOP_DIRECTORY_OPENNODE);

/* struct hop_directory_creatfile */
STATIC_ASSERT(offsetof(struct hop_directory_creatfile, dcf_dent) == __OFFSET_HOP_DIRECTORY_CREATFILE_DENT);
STATIC_ASSERT(offsetof(struct hop_directory_creatfile, dcf_group) == __OFFSET_HOP_DIRECTORY_CREATFILE_GROUP);
STATIC_ASSERT(offsetof(struct hop_directory_creatfile, dcf_len) == __OFFSET_HOP_DIRECTORY_CREATFILE_LEN);
STATIC_ASSERT(offsetof(struct hop_directory_creatfile, dcf_mode) == __OFFSET_HOP_DIRECTORY_CREATFILE_MODE);
STATIC_ASSERT(offsetof(struct hop_directory_creatfile, dcf_name) == __OFFSET_HOP_DIRECTORY_CREATFILE_NAME);
STATIC_ASSERT(offsetof(struct hop_directory_creatfile, dcf_node) == __OFFSET_HOP_DIRECTORY_CREATFILE_NODE);
STATIC_ASSERT(offsetof(struct hop_directory_creatfile, dcf_oflags) == __OFFSET_HOP_DIRECTORY_CREATFILE_OFLAGS);
STATIC_ASSERT(offsetof(struct hop_directory_creatfile, dcf_owner) == __OFFSET_HOP_DIRECTORY_CREATFILE_OWNER);
STATIC_ASSERT(offsetof(struct hop_directory_creatfile, dcf_status) == __OFFSET_HOP_DIRECTORY_CREATFILE_STATUS);
STATIC_ASSERT(offsetof(struct hop_directory_creatfile, dcf_struct_size) == __OFFSET_HOP_DIRECTORY_CREATFILE_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct hop_directory_creatfile) == __SIZEOF_HOP_DIRECTORY_CREATFILE);

/* struct hop_directory_remove */
STATIC_ASSERT(offsetof(struct hop_directory_remove, drm_dent) == __OFFSET_HOP_DIRECTORY_REMOVE_DENT);
STATIC_ASSERT(offsetof(struct hop_directory_remove, drm_flags) == __OFFSET_HOP_DIRECTORY_REMOVE_FLAGS);
STATIC_ASSERT(offsetof(struct hop_directory_remove, drm_len) == __OFFSET_HOP_DIRECTORY_REMOVE_LEN);
STATIC_ASSERT(offsetof(struct hop_directory_remove, drm_name) == __OFFSET_HOP_DIRECTORY_REMOVE_NAME);
STATIC_ASSERT(offsetof(struct hop_directory_remove, drm_node) == __OFFSET_HOP_DIRECTORY_REMOVE_NODE);
STATIC_ASSERT(offsetof(struct hop_directory_remove, drm_status) == __OFFSET_HOP_DIRECTORY_REMOVE_STATUS);
STATIC_ASSERT(offsetof(struct hop_directory_remove, drm_struct_size) == __OFFSET_HOP_DIRECTORY_REMOVE_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct hop_directory_remove) == __SIZEOF_HOP_DIRECTORY_REMOVE);

/* struct hop_directory_rename */
STATIC_ASSERT(offsetof(struct hop_directory_rename, drn_dstdent) == __OFFSET_HOP_DIRECTORY_RENAME_DSTDENT);
STATIC_ASSERT(offsetof(struct hop_directory_rename, drn_dstdir) == __OFFSET_HOP_DIRECTORY_RENAME_DSTDIR);
STATIC_ASSERT(offsetof(struct hop_directory_rename, drn_dstlen) == __OFFSET_HOP_DIRECTORY_RENAME_DSTLEN);
STATIC_ASSERT(offsetof(struct hop_directory_rename, drn_dstname) == __OFFSET_HOP_DIRECTORY_RENAME_DSTNAME);
STATIC_ASSERT(offsetof(struct hop_directory_rename, drn_dstnode) == __OFFSET_HOP_DIRECTORY_RENAME_DSTNODE);
STATIC_ASSERT(offsetof(struct hop_directory_rename, drn_flags) == __OFFSET_HOP_DIRECTORY_RENAME_FLAGS);
STATIC_ASSERT(offsetof(struct hop_directory_rename, drn_srcdent) == __OFFSET_HOP_DIRECTORY_RENAME_SRCDENT);
STATIC_ASSERT(offsetof(struct hop_directory_rename, drn_srclen) == __OFFSET_HOP_DIRECTORY_RENAME_SRCLEN);
STATIC_ASSERT(offsetof(struct hop_directory_rename, drn_srcname) == __OFFSET_HOP_DIRECTORY_RENAME_SRCNAME);
STATIC_ASSERT(offsetof(struct hop_directory_rename, drn_srcnode) == __OFFSET_HOP_DIRECTORY_RENAME_SRCNODE);
STATIC_ASSERT(offsetof(struct hop_directory_rename, drn_struct_size) == __OFFSET_HOP_DIRECTORY_RENAME_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct hop_directory_rename) == __SIZEOF_HOP_DIRECTORY_RENAME);

/* struct hop_directory_link */
STATIC_ASSERT(offsetof(struct hop_directory_link, dli_dent) == __OFFSET_HOP_DIRECTORY_LINK_DENT);
STATIC_ASSERT(offsetof(struct hop_directory_link, dli_flags) == __OFFSET_HOP_DIRECTORY_LINK_FLAGS);
STATIC_ASSERT(offsetof(struct hop_directory_link, dli_len) == __OFFSET_HOP_DIRECTORY_LINK_LEN);
STATIC_ASSERT(offsetof(struct hop_directory_link, dli_linknode) == __OFFSET_HOP_DIRECTORY_LINK_LINKNODE);
STATIC_ASSERT(offsetof(struct hop_directory_link, dli_name) == __OFFSET_HOP_DIRECTORY_LINK_NAME);
STATIC_ASSERT(offsetof(struct hop_directory_link, dli_struct_size) == __OFFSET_HOP_DIRECTORY_LINK_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct hop_directory_link) == __SIZEOF_HOP_DIRECTORY_LINK);

/* struct hop_directory_symlink */
STATIC_ASSERT(offsetof(struct hop_directory_symlink, dsl_dent) == __OFFSET_HOP_DIRECTORY_SYMLINK_DENT);
STATIC_ASSERT(offsetof(struct hop_directory_symlink, dsl_flags) == __OFFSET_HOP_DIRECTORY_SYMLINK_FLAGS);
STATIC_ASSERT(offsetof(struct hop_directory_symlink, dsl_group) == __OFFSET_HOP_DIRECTORY_SYMLINK_GROUP);
STATIC_ASSERT(offsetof(struct hop_directory_symlink, dsl_len) == __OFFSET_HOP_DIRECTORY_SYMLINK_LEN);
STATIC_ASSERT(offsetof(struct hop_directory_symlink, dsl_mode) == __OFFSET_HOP_DIRECTORY_SYMLINK_MODE);
STATIC_ASSERT(offsetof(struct hop_directory_symlink, dsl_name) == __OFFSET_HOP_DIRECTORY_SYMLINK_NAME);
STATIC_ASSERT(offsetof(struct hop_directory_symlink, dsl_node) == __OFFSET_HOP_DIRECTORY_SYMLINK_NODE);
STATIC_ASSERT(offsetof(struct hop_directory_symlink, dsl_owner) == __OFFSET_HOP_DIRECTORY_SYMLINK_OWNER);
STATIC_ASSERT(offsetof(struct hop_directory_symlink, dsl_struct_size) == __OFFSET_HOP_DIRECTORY_SYMLINK_STRUCT_SIZE);
STATIC_ASSERT(offsetof(struct hop_directory_symlink, dsl_text) == __OFFSET_HOP_DIRECTORY_SYMLINK_TEXT);
STATIC_ASSERT(offsetof(struct hop_directory_symlink, dsl_textlen) == __OFFSET_HOP_DIRECTORY_SYMLINK_TEXTLEN);
STATIC_ASSERT(sizeof(struct hop_directory_symlink) == __SIZEOF_HOP_DIRECTORY_SYMLINK);

/* struct hop_directory_mknod */
STATIC_ASSERT(offsetof(struct hop_directory_mknod, dmn_dent) == __OFFSET_HOP_DIRECTORY_MKNOD_DENT);
STATIC_ASSERT(offsetof(struct hop_directory_mknod, dmn_device) == __OFFSET_HOP_DIRECTORY_MKNOD_DEVICE);
STATIC_ASSERT(offsetof(struct hop_directory_mknod, dmn_flags) == __OFFSET_HOP_DIRECTORY_MKNOD_FLAGS);
STATIC_ASSERT(offsetof(struct hop_directory_mknod, dmn_group) == __OFFSET_HOP_DIRECTORY_MKNOD_GROUP);
STATIC_ASSERT(offsetof(struct hop_directory_mknod, dmn_len) == __OFFSET_HOP_DIRECTORY_MKNOD_LEN);
STATIC_ASSERT(offsetof(struct hop_directory_mknod, dmn_mode) == __OFFSET_HOP_DIRECTORY_MKNOD_MODE);
STATIC_ASSERT(offsetof(struct hop_directory_mknod, dmn_name) == __OFFSET_HOP_DIRECTORY_MKNOD_NAME);
STATIC_ASSERT(offsetof(struct hop_directory_mknod, dmn_node) == __OFFSET_HOP_DIRECTORY_MKNOD_NODE);
STATIC_ASSERT(offsetof(struct hop_directory_mknod, dmn_owner) == __OFFSET_HOP_DIRECTORY_MKNOD_OWNER);
STATIC_ASSERT(offsetof(struct hop_directory_mknod, dmn_struct_size) == __OFFSET_HOP_DIRECTORY_MKNOD_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct hop_directory_mknod) == __SIZEOF_HOP_DIRECTORY_MKNOD);

/* struct hop_directory_mkdir */
STATIC_ASSERT(offsetof(struct hop_directory_mkdir, dmd_dent) == __OFFSET_HOP_DIRECTORY_MKDIR_DENT);
STATIC_ASSERT(offsetof(struct hop_directory_mkdir, dmd_flags) == __OFFSET_HOP_DIRECTORY_MKDIR_FLAGS);
STATIC_ASSERT(offsetof(struct hop_directory_mkdir, dmd_group) == __OFFSET_HOP_DIRECTORY_MKDIR_GROUP);
STATIC_ASSERT(offsetof(struct hop_directory_mkdir, dmd_len) == __OFFSET_HOP_DIRECTORY_MKDIR_LEN);
STATIC_ASSERT(offsetof(struct hop_directory_mkdir, dmd_mode) == __OFFSET_HOP_DIRECTORY_MKDIR_MODE);
STATIC_ASSERT(offsetof(struct hop_directory_mkdir, dmd_name) == __OFFSET_HOP_DIRECTORY_MKDIR_NAME);
STATIC_ASSERT(offsetof(struct hop_directory_mkdir, dmd_node) == __OFFSET_HOP_DIRECTORY_MKDIR_NODE);
STATIC_ASSERT(offsetof(struct hop_directory_mkdir, dmd_owner) == __OFFSET_HOP_DIRECTORY_MKDIR_OWNER);
STATIC_ASSERT(offsetof(struct hop_directory_mkdir, dmd_struct_size) == __OFFSET_HOP_DIRECTORY_MKDIR_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct hop_directory_mkdir) == __SIZEOF_HOP_DIRECTORY_MKDIR);

/* struct hop_file_cmpxchg_offset */
STATIC_ASSERT(offsetof(struct hop_file_cmpxchg_offset, cxo_expoffset) == __OFFSET_HOP_FILE_CMPXCHG_OFFSET_EXPOFFSET);
STATIC_ASSERT(offsetof(struct hop_file_cmpxchg_offset, cxo_newoffset) == __OFFSET_HOP_FILE_CMPXCHG_OFFSET_NEWOFFSET);
STATIC_ASSERT(offsetof(struct hop_file_cmpxchg_offset, cxo_oldoffset) == __OFFSET_HOP_FILE_CMPXCHG_OFFSET_OLDOFFSET);
STATIC_ASSERT(offsetof(struct hop_file_cmpxchg_offset, cxo_struct_size) == __OFFSET_HOP_FILE_CMPXCHG_OFFSET_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct hop_file_cmpxchg_offset) == __SIZEOF_HOP_FILE_CMPXCHG_OFFSET);

/* struct hop_task_join */
STATIC_ASSERT(offsetof(struct hop_task_join, tj_reltimeout_nsec) == __OFFSET_HOP_TASK_JOIN_RELTIMEOUT_NSEC);
STATIC_ASSERT(offsetof(struct hop_task_join, tj_reltimeout_sec) == __OFFSET_HOP_TASK_JOIN_RELTIMEOUT_SEC);
STATIC_ASSERT(offsetof(struct hop_task_join, tj_status) == __OFFSET_HOP_TASK_JOIN_STATUS);
STATIC_ASSERT(offsetof(struct hop_task_join, tj_struct_size) == __OFFSET_HOP_TASK_JOIN_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct hop_task_join) == __SIZEOF_HOP_TASK_JOIN);

/* struct hop_task_setprocessgroupleader */
STATIC_ASSERT(offsetof(struct hop_task_setprocessgroupleader, tspgl_leader) == __OFFSET_HOP_TASK_SETPROCESSGROUPLEADER_LEADER);
STATIC_ASSERT(offsetof(struct hop_task_setprocessgroupleader, tspgl_new_leader) == __OFFSET_HOP_TASK_SETPROCESSGROUPLEADER_NEW_LEADER);
STATIC_ASSERT(offsetof(struct hop_task_setprocessgroupleader, tspgl_old_leader) == __OFFSET_HOP_TASK_SETPROCESSGROUPLEADER_OLD_LEADER);
STATIC_ASSERT(offsetof(struct hop_task_setprocessgroupleader, tspgl_struct_size) == __OFFSET_HOP_TASK_SETPROCESSGROUPLEADER_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct hop_task_setprocessgroupleader) == __SIZEOF_HOP_TASK_SETPROCESSGROUPLEADER);

/* struct hop_task_setsessionleader */
STATIC_ASSERT(offsetof(struct hop_task_setsessionleader, tssl_leader) == __OFFSET_HOP_TASK_SETSESSIONLEADER_LEADER);
STATIC_ASSERT(offsetof(struct hop_task_setsessionleader, tssl_new_leader) == __OFFSET_HOP_TASK_SETSESSIONLEADER_NEW_LEADER);
STATIC_ASSERT(offsetof(struct hop_task_setsessionleader, tssl_old_grp_leader) == __OFFSET_HOP_TASK_SETSESSIONLEADER_OLD_GRP_LEADER);
STATIC_ASSERT(offsetof(struct hop_task_setsessionleader, tssl_old_leader) == __OFFSET_HOP_TASK_SETSESSIONLEADER_OLD_LEADER);
STATIC_ASSERT(offsetof(struct hop_task_setsessionleader, tssl_struct_size) == __OFFSET_HOP_TASK_SETSESSIONLEADER_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct hop_task_setsessionleader) == __SIZEOF_HOP_TASK_SETSESSIONLEADER);

/* struct hop_pipe_stat */
STATIC_ASSERT(offsetof(struct hop_pipe_stat, ps_avail) == __OFFSET_HOP_PIPE_STAT_AVAIL);
STATIC_ASSERT(offsetof(struct hop_pipe_stat, ps_bufcur) == __OFFSET_HOP_PIPE_STAT_BUFCUR);
STATIC_ASSERT(offsetof(struct hop_pipe_stat, ps_buflim) == __OFFSET_HOP_PIPE_STAT_BUFLIM);
STATIC_ASSERT(offsetof(struct hop_pipe_stat, ps_rdtotal) == __OFFSET_HOP_PIPE_STAT_RDTOTAL);
STATIC_ASSERT(offsetof(struct hop_pipe_stat, ps_struct_size) == __OFFSET_HOP_PIPE_STAT_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct hop_pipe_stat) == __SIZEOF_HOP_PIPE_STAT);

/* struct hop_pipe_writesome */
STATIC_ASSERT(offsetof(struct hop_pipe_writesome, pws_buf) == __OFFSET_HOP_PIPE_WRITESOME_BUF);
STATIC_ASSERT(offsetof(struct hop_pipe_writesome, pws_buflen) == __OFFSET_HOP_PIPE_WRITESOME_BUFLEN);
STATIC_ASSERT(offsetof(struct hop_pipe_writesome, pws_struct_size) == __OFFSET_HOP_PIPE_WRITESOME_STRUCT_SIZE);
STATIC_ASSERT(offsetof(struct hop_pipe_writesome, pws_written) == __OFFSET_HOP_PIPE_WRITESOME_WRITTEN);
STATIC_ASSERT(sizeof(struct hop_pipe_writesome) == __SIZEOF_HOP_PIPE_WRITESOME);

/* struct hop_pipe_vwritesome */
STATIC_ASSERT(offsetof(struct hop_pipe_vwritesome, pvws_buf) == __OFFSET_HOP_PIPE_VWRITESOME_BUF);
STATIC_ASSERT(offsetof(struct hop_pipe_vwritesome, pvws_bufcnt) == __OFFSET_HOP_PIPE_VWRITESOME_BUFCNT);
STATIC_ASSERT(offsetof(struct hop_pipe_vwritesome, pvws_struct_size) == __OFFSET_HOP_PIPE_VWRITESOME_STRUCT_SIZE);
STATIC_ASSERT(offsetof(struct hop_pipe_vwritesome, pvws_written) == __OFFSET_HOP_PIPE_VWRITESOME_WRITTEN);
STATIC_ASSERT(sizeof(struct hop_pipe_vwritesome) == __SIZEOF_HOP_PIPE_VWRITESOME);

/* struct hop_pipe_skipdata */
STATIC_ASSERT(offsetof(struct hop_pipe_skipdata, psd_num_bytes) == __OFFSET_HOP_PIPE_SKIPDATA_NUM_BYTES);
STATIC_ASSERT(offsetof(struct hop_pipe_skipdata, psd_rdpos) == __OFFSET_HOP_PIPE_SKIPDATA_RDPOS);
STATIC_ASSERT(offsetof(struct hop_pipe_skipdata, psd_skipped) == __OFFSET_HOP_PIPE_SKIPDATA_SKIPPED);
STATIC_ASSERT(offsetof(struct hop_pipe_skipdata, psd_struct_size) == __OFFSET_HOP_PIPE_SKIPDATA_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct hop_pipe_skipdata) == __SIZEOF_HOP_PIPE_SKIPDATA);

/* struct hop_pipe_unread */
STATIC_ASSERT(offsetof(struct hop_pipe_unread, pur_num_bytes) == __OFFSET_HOP_PIPE_UNREAD_NUM_BYTES);
STATIC_ASSERT(offsetof(struct hop_pipe_unread, pur_rdpos) == __OFFSET_HOP_PIPE_UNREAD_RDPOS);
STATIC_ASSERT(offsetof(struct hop_pipe_unread, pur_struct_size) == __OFFSET_HOP_PIPE_UNREAD_STRUCT_SIZE);
STATIC_ASSERT(offsetof(struct hop_pipe_unread, pur_unread) == __OFFSET_HOP_PIPE_UNREAD_UNREAD);
STATIC_ASSERT(sizeof(struct hop_pipe_unread) == __SIZEOF_HOP_PIPE_UNREAD);

/* struct hop_pipe_unwrite */
STATIC_ASSERT(offsetof(struct hop_pipe_unwrite, puw_num_bytes) == __OFFSET_HOP_PIPE_UNWRITE_NUM_BYTES);
STATIC_ASSERT(offsetof(struct hop_pipe_unwrite, puw_struct_size) == __OFFSET_HOP_PIPE_UNWRITE_STRUCT_SIZE);
STATIC_ASSERT(offsetof(struct hop_pipe_unwrite, puw_unwritten) == __OFFSET_HOP_PIPE_UNWRITE_UNWRITTEN);
STATIC_ASSERT(offsetof(struct hop_pipe_unwrite, puw_wrpos) == __OFFSET_HOP_PIPE_UNWRITE_WRPOS);
STATIC_ASSERT(sizeof(struct hop_pipe_unwrite) == __SIZEOF_HOP_PIPE_UNWRITE);

/* struct hop_datapart_stat */
STATIC_ASSERT(offsetof(struct hop_datapart_stat, ds_features) == __OFFSET_HOP_DATAPART_STAT_FEATURES);
STATIC_ASSERT(offsetof(struct hop_datapart_stat, ds_maxaddr) == __OFFSET_HOP_DATAPART_STAT_MAXADDR);
STATIC_ASSERT(offsetof(struct hop_datapart_stat, ds_maxdpage) == __OFFSET_HOP_DATAPART_STAT_MAXDPAGE);
STATIC_ASSERT(offsetof(struct hop_datapart_stat, ds_maxvpage) == __OFFSET_HOP_DATAPART_STAT_MAXVPAGE);
STATIC_ASSERT(offsetof(struct hop_datapart_stat, ds_minaddr) == __OFFSET_HOP_DATAPART_STAT_MINADDR);
STATIC_ASSERT(offsetof(struct hop_datapart_stat, ds_mindpage) == __OFFSET_HOP_DATAPART_STAT_MINDPAGE);
STATIC_ASSERT(offsetof(struct hop_datapart_stat, ds_minvpage) == __OFFSET_HOP_DATAPART_STAT_MINVPAGE);
STATIC_ASSERT(offsetof(struct hop_datapart_stat, ds_state) == __OFFSET_HOP_DATAPART_STAT_STATE);
STATIC_ASSERT(offsetof(struct hop_datapart_stat, ds_struct_size) == __OFFSET_HOP_DATAPART_STAT_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct hop_datapart_stat) == __SIZEOF_HOP_DATAPART_STAT);





#include <kos/sysctl.h>

/* struct hop_openfd */
STATIC_ASSERT(offsetof(struct hop_openfd, of_flags) == __OFFSET_HOP_OPENFD_FLAGS);
STATIC_ASSERT(offsetof(struct hop_openfd, of_hint) == __OFFSET_HOP_OPENFD_HINT);
STATIC_ASSERT(offsetof(struct hop_openfd, of_mode) == __OFFSET_HOP_OPENFD_MODE);
STATIC_ASSERT(sizeof(struct hop_openfd) == __SIZEOF_HOP_OPENFD);

/* struct sysctl_driver_insmod */
STATIC_ASSERT(offsetof(struct sysctl_driver_insmod, im_blob.b_base) == __OFFSET_SYSCTL_DRIVER_INSMOD_BLOB_BASE);
STATIC_ASSERT(offsetof(struct sysctl_driver_insmod, im_blob.b_size) == __OFFSET_SYSCTL_DRIVER_INSMOD_BLOB_SIZE);
STATIC_ASSERT(offsetof(struct sysctl_driver_insmod, im_cmdline) == __OFFSET_SYSCTL_DRIVER_INSMOD_CMDLINE);
STATIC_ASSERT(offsetof(struct sysctl_driver_insmod, im_driver) == __OFFSET_SYSCTL_DRIVER_INSMOD_DRIVER);
STATIC_ASSERT(offsetof(struct sysctl_driver_insmod, im_file.f_dentry) == __OFFSET_SYSCTL_DRIVER_INSMOD_FILE_DENTRY);
STATIC_ASSERT(offsetof(struct sysctl_driver_insmod, im_file.f_node) == __OFFSET_SYSCTL_DRIVER_INSMOD_FILE_NODE);
STATIC_ASSERT(offsetof(struct sysctl_driver_insmod, im_file.f_path) == __OFFSET_SYSCTL_DRIVER_INSMOD_FILE_PATH);
STATIC_ASSERT(offsetof(struct sysctl_driver_insmod, im_flags) == __OFFSET_SYSCTL_DRIVER_INSMOD_FLAGS);
STATIC_ASSERT(offsetof(struct sysctl_driver_insmod, im_format) == __OFFSET_SYSCTL_DRIVER_INSMOD_FORMAT);
STATIC_ASSERT(offsetof(struct sysctl_driver_insmod, im_name) == __OFFSET_SYSCTL_DRIVER_INSMOD_NAME);
STATIC_ASSERT(offsetof(struct sysctl_driver_insmod, im_newdriver) == __OFFSET_SYSCTL_DRIVER_INSMOD_NEWDRIVER);
STATIC_ASSERT(offsetof(struct sysctl_driver_insmod, im_struct_size) == __OFFSET_SYSCTL_DRIVER_INSMOD_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct sysctl_driver_insmod) == __SIZEOF_SYSCTL_DRIVER_INSMOD);

/* struct sysctl_driver_delmod */
STATIC_ASSERT(offsetof(struct sysctl_driver_delmod, dm_file) == __OFFSET_SYSCTL_DRIVER_DELMOD_FILE);
STATIC_ASSERT(offsetof(struct sysctl_driver_delmod, dm_flags) == __OFFSET_SYSCTL_DRIVER_DELMOD_FLAGS);
STATIC_ASSERT(offsetof(struct sysctl_driver_delmod, dm_format) == __OFFSET_SYSCTL_DRIVER_DELMOD_FORMAT);
STATIC_ASSERT(offsetof(struct sysctl_driver_delmod, dm_name) == __OFFSET_SYSCTL_DRIVER_DELMOD_NAME);
STATIC_ASSERT(offsetof(struct sysctl_driver_delmod, dm_struct_size) == __OFFSET_SYSCTL_DRIVER_DELMOD_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct sysctl_driver_delmod) == __SIZEOF_SYSCTL_DRIVER_DELMOD);

/* struct sysctl_driver_getmod */
STATIC_ASSERT(offsetof(struct sysctl_driver_getmod, gm_addr) == __OFFSET_SYSCTL_DRIVER_GETMOD_ADDR);
STATIC_ASSERT(offsetof(struct sysctl_driver_getmod, gm_driver) == __OFFSET_SYSCTL_DRIVER_GETMOD_DRIVER);
STATIC_ASSERT(offsetof(struct sysctl_driver_getmod, gm_file) == __OFFSET_SYSCTL_DRIVER_GETMOD_FILE);
STATIC_ASSERT(offsetof(struct sysctl_driver_getmod, gm_format) == __OFFSET_SYSCTL_DRIVER_GETMOD_FORMAT);
STATIC_ASSERT(offsetof(struct sysctl_driver_getmod, gm_name) == __OFFSET_SYSCTL_DRIVER_GETMOD_NAME);
STATIC_ASSERT(offsetof(struct sysctl_driver_getmod, gm_struct_size) == __OFFSET_SYSCTL_DRIVER_GETMOD_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct sysctl_driver_getmod) == __SIZEOF_SYSCTL_DRIVER_GETMOD);

/* struct sysctl_driver_get_library_path */
STATIC_ASSERT(offsetof(struct sysctl_driver_get_library_path, glp_buf) == __OFFSET_SYSCTL_DRIVER_GET_LIBRARY_PATH_BUF);
STATIC_ASSERT(offsetof(struct sysctl_driver_get_library_path, glp_size) == __OFFSET_SYSCTL_DRIVER_GET_LIBRARY_PATH_SIZE);
STATIC_ASSERT(offsetof(struct sysctl_driver_get_library_path, glp_struct_size) == __OFFSET_SYSCTL_DRIVER_GET_LIBRARY_PATH_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct sysctl_driver_get_library_path) == __SIZEOF_SYSCTL_DRIVER_GET_LIBRARY_PATH);

/* struct sysctl_driver_set_library_path */
STATIC_ASSERT(offsetof(struct sysctl_driver_set_library_path, slp_newpath) == __OFFSET_SYSCTL_DRIVER_SET_LIBRARY_PATH_NEWPATH);
STATIC_ASSERT(offsetof(struct sysctl_driver_set_library_path, slp_oldpath) == __OFFSET_SYSCTL_DRIVER_SET_LIBRARY_PATH_OLDPATH);
STATIC_ASSERT(offsetof(struct sysctl_driver_set_library_path, slp_struct_size) == __OFFSET_SYSCTL_DRIVER_SET_LIBRARY_PATH_STRUCT_SIZE);
STATIC_ASSERT(sizeof(struct sysctl_driver_set_library_path) == __SIZEOF_SYSCTL_DRIVER_SET_LIBRARY_PATH);





#include <kos/bits/ukern-struct.h>

/* struct userkern */
STATIC_ASSERT(offsetof(struct userkern, uk_base) == OFFSET_USERKERN_BASE);
STATIC_ASSERT(offsetof(struct userkern, uk_egid) == OFFSET_USERKERN_EGID);
STATIC_ASSERT(offsetof(struct userkern, uk_euid) == OFFSET_USERKERN_EUID);
STATIC_ASSERT(offsetof(struct userkern, uk_gid) == OFFSET_USERKERN_GID);
STATIC_ASSERT(offsetof(struct userkern, uk_pgid) == OFFSET_USERKERN_PGID);
STATIC_ASSERT(offsetof(struct userkern, uk_pid) == OFFSET_USERKERN_PID);
STATIC_ASSERT(offsetof(struct userkern, uk_ppid) == OFFSET_USERKERN_PPID);
STATIC_ASSERT(offsetof(struct userkern, uk_regs) == OFFSET_USERKERN_REGS);
STATIC_ASSERT(offsetof(struct userkern, uk_sgid) == OFFSET_USERKERN_SGID);
STATIC_ASSERT(offsetof(struct userkern, uk_sid) == OFFSET_USERKERN_SID);
STATIC_ASSERT(offsetof(struct userkern, uk_suid) == OFFSET_USERKERN_SUID);
STATIC_ASSERT(offsetof(struct userkern, uk_tid) == OFFSET_USERKERN_TID);
STATIC_ASSERT(offsetof(struct userkern, uk_uid) == OFFSET_USERKERN_UID);
STATIC_ASSERT(sizeof(struct userkern) == SIZEOF_USERKERN);





#include <kos/bits/debugtrap.h>

/* struct debugtrap_reason */
STATIC_ASSERT(offsetof(struct debugtrap_reason, dtr_intarg) == __OFFSET_DEBUGTRAP_REASON_INTARG);
STATIC_ASSERT(offsetof(struct debugtrap_reason, dtr_ptrarg) == __OFFSET_DEBUGTRAP_REASON_PTRARG);
STATIC_ASSERT(offsetof(struct debugtrap_reason, dtr_reason) == __OFFSET_DEBUGTRAP_REASON_REASON);
STATIC_ASSERT(offsetof(struct debugtrap_reason, dtr_signo) == __OFFSET_DEBUGTRAP_REASON_SIGNO);
STATIC_ASSERT(offsetof(struct debugtrap_reason, dtr_strarg) == __OFFSET_DEBUGTRAP_REASON_STRARG);
STATIC_ASSERT(sizeof(struct debugtrap_reason) == __SIZEOF_DEBUGTRAP_REASON);





#include <kos/bits/library-listdef.h>

/* struct library_listdef */
STATIC_ASSERT(offsetof(struct library_listdef, lld_count) == __OFFSET_LIBRARY_LISTDEF_COUNT);
STATIC_ASSERT(offsetof(struct library_listdef, lld_entry_offsetof_module) == __OFFSET_LIBRARY_LISTDEF_ENTRY_OFFSETOF_MODULE);
STATIC_ASSERT(offsetof(struct library_listdef, lld_entry_offsetof_next) == __OFFSET_LIBRARY_LISTDEF_ENTRY_OFFSETOF_NEXT);
STATIC_ASSERT(offsetof(struct library_listdef, lld_first) == __OFFSET_LIBRARY_LISTDEF_FIRST);
STATIC_ASSERT(offsetof(struct library_listdef, lld_flags) == __OFFSET_LIBRARY_LISTDEF_FLAGS);
STATIC_ASSERT(offsetof(struct library_listdef, lld_module_offsetof_filename) == __OFFSET_LIBRARY_LISTDEF_MODULE_OFFSETOF_FILENAME);
STATIC_ASSERT(offsetof(struct library_listdef, lld_module_offsetof_loadaddr) == __OFFSET_LIBRARY_LISTDEF_MODULE_OFFSETOF_LOADADDR);
STATIC_ASSERT(offsetof(struct library_listdef, lld_module_offsetof_loadstart) == __OFFSET_LIBRARY_LISTDEF_MODULE_OFFSETOF_LOADSTART);
STATIC_ASSERT(offsetof(struct library_listdef, lld_size) == __OFFSET_LIBRARY_LISTDEF_SIZE);
STATIC_ASSERT(offsetof(struct library_listdef, lld_sizeof_pointer) == __OFFSET_LIBRARY_LISTDEF_SIZEOF_POINTER);
STATIC_ASSERT(sizeof(struct library_listdef) == __SIZEOF_LIBRARY_LISTDEF);
//[[[end]]]


#endif /* !GUARD__VERIFY_ASSERT_TYPES_C */
