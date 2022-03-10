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

#define PHYS
#define __PHYS
#define VIRT
#define __VIRT
#define USER
#define __USER
#define CHECKED
#define __CHECKED
#define UNCHECKED
#define __UNCHECKED
#define KERNEL
#define __KERNEL
#define WEAK
#define __WEAK
#define REF
#define __REF
#define REF_IF(x)
#define __REF_IF(x)
#define NOBLOCK
#define __NOBLOCK
#define NOBLOCK_IF(x)
#define __NOBLOCK_IF(x)
#define BLOCKING
#define __BLOCKING
#define BLOCKING_IF(x)
#define __BLOCKING_IF(x)
#define NOPREEMPT
#define __NOPREEMPT
#define ABNORMAL_RETURN
#define __ABNORMAL_RETURN
#define THROWS(...)
#define __THROWS(...)
#define THROWING
#define __THROWING

#xdefine __SIZEOF_FD_T__             __SIZEOF_INT__
#xdefine __SIZEOF_ERRNO_T__          __SIZEOF_INT__
#xdefine __SIZEOF_SIGNO_T__          __SIZEOF_INT__
#xdefine __SIZEOF_OFLAG_T__          __SIZEOF_INT__
#xdefine __SIZEOF_SYSCALL_LONG_T__   __SIZEOF_REGISTER__
#xdefine __SIZEOF_MODE_T__           4
#xdefine __SIZEOF_ATFLAG_T__         __SIZEOF_INT__
#if __SIZEOF_POINTER__ >= 8
#xdefine __SIZEOF_IOMODE_T__         4
#else /* __SIZEOF_POINTER__ >= 8 */
#xdefine __SIZEOF_IOMODE_T__         2
#endif /* __SIZEOF_POINTER__ < 8 */
#xdefine __SIZEOF_MAJOR_T__          4
#xdefine __SIZEOF_MINOR_T__          4
#xdefine __SIZEOF_DEV_T__            8
#xdefine __SIZEOF_ID_T__             4
#xdefine __SIZEOF_PID_T__            4
#xdefine __SIZEOF_KEY_T__            4
#xdefine __SIZEOF_DADDR_T__          4
#xdefine __SIZEOF_CADDR_T__          __SIZEOF_POINTER__
#xdefine __SIZEOF_FSID_T__           8
#xdefine __SIZEOF_BLKSIZE_T__        __SIZEOF_SYSCALL_LONG_T__
#xdefine __SIZEOF_NLINK_T__          4
#xdefine __SIZEOF_OFF32_T__          4
#xdefine __SIZEOF_OFF64_T__          8
#xdefine __SIZEOF_LOFF_T__           8
#xdefine __SIZEOF_BLKCNT32_T__       4
#xdefine __SIZEOF_BLKCNT64_T__       8
#xdefine __SIZEOF_FSBLKCNT32_T__     4
#xdefine __SIZEOF_FSBLKCNT64_T__     8
#xdefine __SIZEOF_FSFILCNT32_T__     4
#xdefine __SIZEOF_FSFILCNT64_T__     8
#xdefine __SIZEOF_INO32_T__          4
#xdefine __SIZEOF_INO64_T__          8
#xdefine __SIZEOF_RLIM32_T__         4
#xdefine __SIZEOF_RLIM64_T__         8
#xdefine __SIZEOF_TIME32_T__         4
#xdefine __SIZEOF_TIME64_T__         8
#xdefine __SIZEOF_SOCKLEN_T__        __SIZEOF_SIZE_T__
#xdefine __SIZEOF_QUANTUM_DIFF_T__   4
#xdefine __SIZEOF_CLOCK_T__          __SIZEOF_SYSCALL_LONG_T__
#xdefine __SIZEOF_USECONDS_T__       4
#xdefine __SIZEOF_SUSECONDS_T__      __SIZEOF_SYSCALL_LONG_T__
#xdefine __SIZEOF_CLOCKID_T__        4
#xdefine __SIZEOF_GID_T__            4
#xdefine __SIZEOF_UID_T__            4
#xdefine __SIZEOF_TIMER_T__          __SIZEOF_POINTER__
#xdefine __SIZEOF_FSWORD_T__         __SIZEOF_SYSCALL_LONG_T__
#xdefine __SIZEOF_PHYSADDR_T__       __SIZEOF_POINTER__
#xdefine __SIZEOF_PHYSPAGE_T__       __SIZEOF_POINTER__
#xdefine __SIZEOF_SA_FAMILY_T__      2
#xdefine __SIZEOF_IOCTL_T__          __SIZEOF_SYSCALL_LONG_T__
#xdefine __SIZEOF_FCNTL_T__          __SIZEOF_INT__

#if __SIZEOF_FD_T__ == __SIZEOF_INT__
#xdefine __fd_t int
#endif
#if __SIZEOF_OFF64_T__ == 8
#xdefine __off64_t __INT64_TYPE__
#xdefine __pos64_t __UINT64_TYPE__
#endif


#xdefine __CHAR_BIT__ 8
#xdefine __SIZEOF_CHAR__  1
#xdefine __SIZEOF_SHORT__ 2
#xdefine __SIZEOF_INT__ 4
#xdefine __SIZEOF_LONG__ __SIZEOF_POINTER__
#xdefine __SIZEOF_LONG_LONG__ 8
#xdefine __SIZEOF_PTRDIFF_T__ __SIZEOF_POINTER__
#xdefine __SIZEOF_SIZE_T__ __SIZEOF_POINTER__
#xdefine __SIZEOF_INT_FAST8_T__ 1
#xdefine __SIZEOF_INT_FAST16_T__ 2
#xdefine __SIZEOF_INT_FAST32_T__ 4
#xdefine __SIZEOF_INT_FAST64_T__ 8
#xdefine __SIZEOF_SIG_ATOMIC_T__ __SIZEOF_INT__
#xdefine __SIZEOF_WINT_T__ __SIZEOF_INT__
#xdefine __SIZEOF_WCHAR_T__ 4
#xdefine __CHAR8_TYPE__ char
#xdefine __INT8_TYPE__ signed char
#xdefine __INT16_TYPE__ short
#xdefine __INT32_TYPE__ int
#xdefine __INT64_TYPE__ long long
#xdefine __UINT8_TYPE__ unsigned char
#xdefine __UINT16_TYPE__ unsigned short
#xdefine __UINT32_TYPE__ unsigned int
#xdefine __UINT64_TYPE__ unsigned long long

#xdefine __SIZEOF_INT_LEAST64_T__ 8
#xdefine __SIZEOF_INT_LEAST32_T__ 4
#xdefine __SIZEOF_INT_LEAST16_T__ 2
#xdefine __SIZEOF_INT_LEAST8_T__ 1
#xdefine __INT_LEAST8_TYPE__ __INT8_TYPE__
#xdefine __INT_LEAST16_TYPE__ __INT16_TYPE__
#xdefine __INT_LEAST32_TYPE__ __INT32_TYPE__
#xdefine __INT_LEAST64_TYPE__ __INT64_TYPE__
#xdefine __UINT_LEAST8_TYPE__ __UINT8_TYPE__
#xdefine __UINT_LEAST16_TYPE__ __UINT16_TYPE__
#xdefine __UINT_LEAST32_TYPE__ __UINT32_TYPE__
#xdefine __UINT_LEAST64_TYPE__ __UINT64_TYPE__
#xdefine __INT_FAST8_TYPE__ __INT8_TYPE__
#xdefine __INT_FAST16_TYPE__ __INT16_TYPE__
#xdefine __INT_FAST32_TYPE__ __INT32_TYPE__
#xdefine __INT_FAST64_TYPE__ __INT64_TYPE__
#xdefine __UINT_FAST8_TYPE__ __UINT8_TYPE__
#xdefine __UINT_FAST16_TYPE__ __UINT16_TYPE__
#xdefine __UINT_FAST32_TYPE__ __UINT32_TYPE__
#xdefine __UINT_FAST64_TYPE__ __UINT64_TYPE__
#xdefine __LONGPTR_TYPE__ long
#xdefine __ULONGPTR_TYPE__ unsigned long
#if __SIZEOF_POINTER__ == __SIZEOF_INT__
#xdefine __INTPTR_TYPE__ int
#xdefine __UINTPTR_TYPE__ unsigned int
#else /* __SIZEOF_POINTER__ == __SIZEOF_INT__ */
#xdefine __INTPTR_TYPE__ long long
#xdefine __UINTPTR_TYPE__ unsigned long long
#endif /* __SIZEOF_POINTER__ != __SIZEOF_INT__ */
#xdefine __SIZE_TYPE__ __UINTPTR_TYPE__
#xdefine __SSIZE_TYPE__ __INTPTR_TYPE__
#xdefine __PTRDIFF_TYPE__ __INTPTR_TYPE__
#xdefine __SBYTE_TYPE__ signed char
#xdefine __BYTE_TYPE__ unsigned char

#xdefine __SIZEOF_SHIFT_T__ 1
#xdefine __SHIFT_TYPE__ unsigned char
#xdefine __SIG_ATOMIC_TYPE__ int
#xdefine __SIZEOF_BUSINT__ __SIZEOF_POINTER__
#xdefine __BUSINT_TYPE__   __INTPTR_TYPE__
#xdefine __UBUSIINT_TYPE__ __UINTPTR_TYPE__
#xdefine __SIZEOF_REGISTER__  __SIZEOF_POINTER__
#xdefine __REGISTER_TYPE__    __ULONGPTR_TYPE__
#xdefine __SREGISTER_TYPE__   __LONGPTR_TYPE__

#define __ATTR_LIBC_PRINTF(a, b)
#define __ATTR_LIBC_PRINTF_P(a, b)
#define __ATTR_LIBC_SCANF(a, b)
#define __ATTR_LIBC_STRFMON(a, b)
#define __ATTR_LIBC_STRFTIME(a, b)
#define __ATTR_LIBC_WPRINTF(a, b)
#define __ATTR_LIBC_WPRINTF_P(a, b)
#define __ATTR_LIBC_WSCANF(a, b)
#define __ATTR_LIBC_WCSFTIME(a, b)
#define __ATTR_LIBC_C16PRINTF(a, b)
#define __ATTR_LIBC_C16PRINTF_P(a, b)
#define __ATTR_LIBC_C16SCANF(a, b)
#define __ATTR_LIBC_C16FTIME(a, b)
#define __ATTR_LIBC_C32PRINTF(a, b)
#define __ATTR_LIBC_C32PRINTF_P(a, b)
#define __ATTR_LIBC_C32SCANF(a, b)
#define __ATTR_LIBC_C32FTIME(a, b)

/* NOTE: This right here would break `__WANT_NO_PLT_RELOCATIONS' */
//#define __IMPDEF  extern __ATTR_VISIBILITY("default")

#define __LIBC    __IMPDEF
#define __IMPDAT  extern __ATTR_VISIBILITY("default")
#define __EXPDEF  extern __ATTR_VISIBILITY("default")
#define __PUBDEF  extern __ATTR_VISIBILITY("default")
#define __PUBLIC         __ATTR_VISIBILITY("default")
#define __PRIVATE static
#define __INTDEF  extern __ATTR_VISIBILITY("hidden")
#define __INTERN         __ATTR_VISIBILITY("hidden")
