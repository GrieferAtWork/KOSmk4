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
/* (#) Portability: GNU C Library (/posix/bits/types.h) */
/* (#) Portability: mintlib       (/include/bits/types.h) */
#ifndef _BITS_TYPES_H
#define _BITS_TYPES_H 1

/* NOTE: This file must _always_ be kept for GLibc compatibility! */

#include <__crt.h>
#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/typesizes.h>

/* Default sizes */
#ifndef __SIZEOF_FD_T__
#define __SIZEOF_FD_T__ __SIZEOF_INT__
#endif /* !__SIZEOF_FD_T__ */
#ifndef __SIZEOF_ERRNO_T__
#define __SIZEOF_ERRNO_T__ __SIZEOF_INT__
#endif /* !__SIZEOF_ERRNO_T__ */
#ifndef __SIZEOF_SIGNO_T__
#define __SIZEOF_SIGNO_T__ __SIZEOF_INT__
#endif /* !__SIZEOF_SIGNO_T__ */
#ifndef __SIZEOF_OFLAG_T__
#define __SIZEOF_OFLAG_T__ __SIZEOF_INT__
#endif /* !__SIZEOF_OFLAG_T__ */
#ifndef __SIZEOF_SYSCALL_LONG_T__
#define __SIZEOF_SYSCALL_LONG_T__ __SIZEOF_REGISTER__
#endif /* !__SIZEOF_SYSCALL_LONG_T__ */
#ifndef __SIZEOF_MODE_T__
#define __SIZEOF_MODE_T__ 4
#endif /* !__SIZEOF_MODE_T__ */
#ifndef __SIZEOF_ATFLAG_T__
#define __SIZEOF_ATFLAG_T__ __SIZEOF_INT__
#endif /* !__SIZEOF_ATFLAG_T__ */
#ifndef __SIZEOF_IOMODE_T__
#if __SIZEOF_POINTER__ >= 8
#define __SIZEOF_IOMODE_T__ 4
#else /* __SIZEOF_POINTER__ >= 8 */
#define __SIZEOF_IOMODE_T__ 2
#endif /* __SIZEOF_POINTER__ < 8 */
#endif /* !__SIZEOF_IOMODE_T__ */
#ifndef __SIZEOF_MAJOR_T__
#define __SIZEOF_MAJOR_T__ 4
#endif /* !__SIZEOF_MAJOR_T__ */
#ifndef __SIZEOF_MINOR_T__
#define __SIZEOF_MINOR_T__ 4
#endif /* !__SIZEOF_MINOR_T__ */
#ifndef __SIZEOF_DEV_T__
#define __SIZEOF_DEV_T__ 8
#endif /* !__SIZEOF_DEV_T__ */
#ifndef __SIZEOF_ID_T__
#define __SIZEOF_ID_T__ 4
#endif /* !__SIZEOF_ID_T__ */
#ifndef __SIZEOF_PID_T__
#define __SIZEOF_PID_T__ 4
#endif /* !__SIZEOF_PID_T__ */
#ifndef __SIZEOF_KEY_T__
#define __SIZEOF_KEY_T__ 4
#endif /* !__SIZEOF_KEY_T__ */
#ifndef __SIZEOF_DADDR_T__
#define __SIZEOF_DADDR_T__ 4
#endif /* !__SIZEOF_DADDR_T__ */
#ifndef __SIZEOF_CADDR_T__
#define __SIZEOF_CADDR_T__ __SIZEOF_POINTER__
#endif /* !__SIZEOF_CADDR_T__ */
#ifndef __SIZEOF_FSID_T__
#define __SIZEOF_FSID_T__ 8
#endif /* !__SIZEOF_FSID_T__ */
#ifndef __SIZEOF_BLKSIZE_T__
#define __SIZEOF_BLKSIZE_T__ __SIZEOF_SYSCALL_LONG_T__
#endif /* !__SIZEOF_BLKSIZE_T__ */
#ifndef __SIZEOF_NLINK_T__
#define __SIZEOF_NLINK_T__ 4
#endif /* !__SIZEOF_NLINK_T__ */
#ifndef __SIZEOF_OFF32_T__
#define __SIZEOF_OFF32_T__ 4
#endif /* !__SIZEOF_OFF32_T__ */
#ifndef __SIZEOF_OFF64_T__
#define __SIZEOF_OFF64_T__ 8
#endif /* !__SIZEOF_OFF64_T__ */
#ifndef __SIZEOF_LOFF_T__
#define __SIZEOF_LOFF_T__ 8
#endif /* !__SIZEOF_LOFF_T__ */
#ifndef __SIZEOF_BLKCNT32_T__
#define __SIZEOF_BLKCNT32_T__ 4
#endif /* !__SIZEOF_BLKCNT32_T__ */
#ifndef __SIZEOF_BLKCNT64_T__
#define __SIZEOF_BLKCNT64_T__ 8
#endif /* !__SIZEOF_BLKCNT64_T__ */
#ifndef __SIZEOF_FSBLKCNT32_T__
#define __SIZEOF_FSBLKCNT32_T__ 4
#endif /* !__SIZEOF_FSBLKCNT32_T__ */
#ifndef __SIZEOF_FSBLKCNT64_T__
#define __SIZEOF_FSBLKCNT64_T__ 8
#endif /* !__SIZEOF_FSBLKCNT64_T__ */
#ifndef __SIZEOF_FSFILCNT32_T__
#define __SIZEOF_FSFILCNT32_T__ 4
#endif /* !__SIZEOF_FSFILCNT32_T__ */
#ifndef __SIZEOF_FSFILCNT64_T__
#define __SIZEOF_FSFILCNT64_T__ 8
#endif /* !__SIZEOF_FSFILCNT64_T__ */
#ifndef __SIZEOF_INO32_T__
#define __SIZEOF_INO32_T__ 4
#endif /* !__SIZEOF_INO32_T__ */
#ifndef __SIZEOF_INO64_T__
#define __SIZEOF_INO64_T__ 8
#endif /* !__SIZEOF_INO64_T__ */
#ifndef __SIZEOF_RLIM32_T__
#define __SIZEOF_RLIM32_T__ 4
#endif /* !__SIZEOF_RLIM32_T__ */
#ifndef __SIZEOF_RLIM64_T__
#define __SIZEOF_RLIM64_T__ 8
#endif /* !__SIZEOF_RLIM64_T__ */
#ifndef __SIZEOF_TIME32_T__
#define __SIZEOF_TIME32_T__ 4
#endif /* !__SIZEOF_TIME32_T__ */
#ifndef __SIZEOF_TIME64_T__
#define __SIZEOF_TIME64_T__ 8
#endif /* !__SIZEOF_TIME64_T__ */
#ifndef __SIZEOF_SOCKLEN_T__
#define __SIZEOF_SOCKLEN_T__ __SIZEOF_SIZE_T__
#endif /* !__SIZEOF_SOCKLEN_T__ */
#ifndef __SIZEOF_QUANTUM_DIFF_T__
#define __SIZEOF_QUANTUM_DIFF_T__ 4
#endif /* !__SIZEOF_QUANTUM_DIFF_T__ */
#ifndef __SIZEOF_CLOCK_T__
#define __SIZEOF_CLOCK_T__ __SIZEOF_SYSCALL_LONG_T__
#endif /* !__SIZEOF_CLOCK_T__ */
#ifndef __SIZEOF_USECONDS_T__
#define __SIZEOF_USECONDS_T__ 4
#endif /* !__SIZEOF_USECONDS_T__ */
#ifndef __SIZEOF_SUSECONDS_T__
#define __SIZEOF_SUSECONDS_T__ __SIZEOF_SYSCALL_LONG_T__
#endif /* !__SIZEOF_SUSECONDS_T__ */
#ifndef __SIZEOF_CLOCKID_T__
#define __SIZEOF_CLOCKID_T__ 4
#endif /* !__SIZEOF_CLOCKID_T__ */
#ifndef __SIZEOF_GID_T__
#define __SIZEOF_GID_T__ 4
#endif /* !__SIZEOF_GID_T__ */
#ifndef __SIZEOF_UID_T__
#define __SIZEOF_UID_T__ 4
#endif /* !__SIZEOF_UID_T__ */
#ifndef __SIZEOF_TIMER_T__
#define __SIZEOF_TIMER_T__ __SIZEOF_POINTER__
#endif /* !__SIZEOF_TIMER_T__ */
#ifndef __SIZEOF_FSWORD_T__
#define __SIZEOF_FSWORD_T__ __SIZEOF_SYSCALL_LONG_T__
#endif /* !__SIZEOF_FSWORD_T__ */
#ifndef __SIZEOF_PHYSADDR_T__
#define __SIZEOF_PHYSADDR_T__ __SIZEOF_POINTER__
#endif /* !__SIZEOF_PHYSADDR_T__ */
#ifndef __SIZEOF_PHYSPAGE_T__
#define __SIZEOF_PHYSPAGE_T__ __SIZEOF_POINTER__
#endif /* !__SIZEOF_PHYSPAGE_T__ */
#ifndef __SIZEOF_SA_FAMILY_T__
#define __SIZEOF_SA_FAMILY_T__ 2
#endif /* !__SIZEOF_SA_FAMILY_T__ */
#ifndef __SIZEOF_IOCTL_T__
#define __SIZEOF_IOCTL_T__ __SIZEOF_SYSCALL_LONG_T__
#endif /* !__SIZEOF_IOCTL_T__ */
#ifndef __SIZEOF_FCNTL_T__
#define __SIZEOF_FCNTL_T__ __SIZEOF_INT__
#endif /* !__SIZEOF_FCNTL_T__ */


/* Default alignments */
#ifndef __ALIGNOF_FD_T__
#define __ALIGNOF_FD_T__ __HYBRID_ALIGNOF(__SIZEOF_FD_T__)
#endif /* !__ALIGNOF_FD_T__ */
#ifndef __ALIGNOF_ERRNO_T__
#define __ALIGNOF_ERRNO_T__ __HYBRID_ALIGNOF(__SIZEOF_ERRNO_T__)
#endif /* !__ALIGNOF_ERRNO_T__ */
#ifndef __ALIGNOF_SIGNO_T__
#define __ALIGNOF_SIGNO_T__ __HYBRID_ALIGNOF(__SIZEOF_SIGNO_T__)
#endif /* !__ALIGNOF_SIGNO_T__ */
#ifndef __ALIGNOF_OFLAG_T__
#define __ALIGNOF_OFLAG_T__ __HYBRID_ALIGNOF(__SIZEOF_OFLAG_T__)
#endif /* !__ALIGNOF_OFLAG_T__ */
#ifndef __ALIGNOF_SYSCALL_LONG_T__
#define __ALIGNOF_SYSCALL_LONG_T__ __HYBRID_ALIGNOF(__SIZEOF_SYSCALL_LONG_T__)
#endif /* !__ALIGNOF_SYSCALL_LONG_T__ */
#ifndef __ALIGNOF_MODE_T__
#define __ALIGNOF_MODE_T__ __HYBRID_ALIGNOF(__SIZEOF_MODE_T__)
#endif /* !__ALIGNOF_MODE_T__ */
#ifndef __ALIGNOF_ATFLAG_T__
#define __ALIGNOF_ATFLAG_T__ __HYBRID_ALIGNOF(__SIZEOF_ATFLAG_T__)
#endif /* !__ALIGNOF_ATFLAG_T__ */
#ifndef __ALIGNOF_IOMODE_T__
#define __ALIGNOF_IOMODE_T__ __HYBRID_ALIGNOF(__SIZEOF_IOMODE_T__)
#endif /* !__ALIGNOF_IOMODE_T__ */
#ifndef __ALIGNOF_MAJOR_T__
#define __ALIGNOF_MAJOR_T__ __HYBRID_ALIGNOF(__SIZEOF_MAJOR_T__)
#endif /* !__ALIGNOF_MAJOR_T__ */
#ifndef __ALIGNOF_MINOR_T__
#define __ALIGNOF_MINOR_T__ __HYBRID_ALIGNOF(__SIZEOF_MINOR_T__)
#endif /* !__ALIGNOF_MINOR_T__ */
#ifndef __ALIGNOF_DEV_T__
#define __ALIGNOF_DEV_T__ __HYBRID_ALIGNOF(__SIZEOF_DEV_T__)
#endif /* !__ALIGNOF_DEV_T__ */
#ifndef __ALIGNOF_ID_T__
#define __ALIGNOF_ID_T__ __HYBRID_ALIGNOF(__SIZEOF_ID_T__)
#endif /* !__ALIGNOF_ID_T__ */
#ifndef __ALIGNOF_PID_T__
#define __ALIGNOF_PID_T__ __HYBRID_ALIGNOF(__SIZEOF_PID_T__)
#endif /* !__ALIGNOF_PID_T__ */
#ifndef __ALIGNOF_KEY_T__
#define __ALIGNOF_KEY_T__ __HYBRID_ALIGNOF(__SIZEOF_KEY_T__)
#endif /* !__ALIGNOF_KEY_T__ */
#ifndef __ALIGNOF_DADDR_T__
#define __ALIGNOF_DADDR_T__ __HYBRID_ALIGNOF(__SIZEOF_DADDR_T__)
#endif /* !__ALIGNOF_DADDR_T__ */
#ifndef __ALIGNOF_CADDR_T__
#define __ALIGNOF_CADDR_T__ __HYBRID_ALIGNOF(__SIZEOF_CADDR_T__)
#endif /* !__ALIGNOF_CADDR_T__ */
#ifndef __ALIGNOF_FSID_T__
#define __ALIGNOF_FSID_T__ __HYBRID_ALIGNOF(__SIZEOF_FSID_T__)
#endif /* !__ALIGNOF_FSID_T__ */
#ifndef __ALIGNOF_BLKSIZE_T__
#define __ALIGNOF_BLKSIZE_T__ __HYBRID_ALIGNOF(__SIZEOF_BLKSIZE_T__)
#endif /* !__ALIGNOF_BLKSIZE_T__ */
#ifndef __ALIGNOF_NLINK_T__
#define __ALIGNOF_NLINK_T__ __HYBRID_ALIGNOF(__SIZEOF_NLINK_T__)
#endif /* !__ALIGNOF_NLINK_T__ */
#ifndef __ALIGNOF_OFF32_T__
#define __ALIGNOF_OFF32_T__ __HYBRID_ALIGNOF(__SIZEOF_OFF32_T__)
#endif /* !__ALIGNOF_OFF32_T__ */
#ifndef __ALIGNOF_OFF64_T__
#define __ALIGNOF_OFF64_T__ __HYBRID_ALIGNOF(__SIZEOF_OFF64_T__)
#endif /* !__ALIGNOF_OFF64_T__ */
#ifndef __ALIGNOF_LOFF_T__
#define __ALIGNOF_LOFF_T__ __HYBRID_ALIGNOF(__SIZEOF_LOFF_T__)
#endif /* !__ALIGNOF_LOFF_T__ */
#ifndef __ALIGNOF_BLKCNT32_T__
#define __ALIGNOF_BLKCNT32_T__ __HYBRID_ALIGNOF(__SIZEOF_BLKCNT32_T__)
#endif /* !__ALIGNOF_BLKCNT32_T__ */
#ifndef __ALIGNOF_BLKCNT64_T__
#define __ALIGNOF_BLKCNT64_T__ __HYBRID_ALIGNOF(__SIZEOF_BLKCNT64_T__)
#endif /* !__ALIGNOF_BLKCNT64_T__ */
#ifndef __ALIGNOF_FSBLKCNT32_T__
#define __ALIGNOF_FSBLKCNT32_T__ __HYBRID_ALIGNOF(__SIZEOF_FSBLKCNT32_T__)
#endif /* !__ALIGNOF_FSBLKCNT32_T__ */
#ifndef __ALIGNOF_FSBLKCNT64_T__
#define __ALIGNOF_FSBLKCNT64_T__ __HYBRID_ALIGNOF(__SIZEOF_FSBLKCNT64_T__)
#endif /* !__ALIGNOF_FSBLKCNT64_T__ */
#ifndef __ALIGNOF_FSFILCNT32_T__
#define __ALIGNOF_FSFILCNT32_T__ __HYBRID_ALIGNOF(__SIZEOF_FSFILCNT32_T__)
#endif /* !__ALIGNOF_FSFILCNT32_T__ */
#ifndef __ALIGNOF_FSFILCNT64_T__
#define __ALIGNOF_FSFILCNT64_T__ __HYBRID_ALIGNOF(__SIZEOF_FSFILCNT64_T__)
#endif /* !__ALIGNOF_FSFILCNT64_T__ */
#ifndef __ALIGNOF_INO32_T__
#define __ALIGNOF_INO32_T__ __HYBRID_ALIGNOF(__SIZEOF_INO32_T__)
#endif /* !__ALIGNOF_INO32_T__ */
#ifndef __ALIGNOF_INO64_T__
#define __ALIGNOF_INO64_T__ __HYBRID_ALIGNOF(__SIZEOF_INO64_T__)
#endif /* !__ALIGNOF_INO64_T__ */
#ifndef __ALIGNOF_RLIM32_T__
#define __ALIGNOF_RLIM32_T__ __HYBRID_ALIGNOF(__SIZEOF_RLIM32_T__)
#endif /* !__ALIGNOF_RLIM32_T__ */
#ifndef __ALIGNOF_RLIM64_T__
#define __ALIGNOF_RLIM64_T__ __HYBRID_ALIGNOF(__SIZEOF_RLIM64_T__)
#endif /* !__ALIGNOF_RLIM64_T__ */
#ifndef __ALIGNOF_TIME32_T__
#define __ALIGNOF_TIME32_T__ __HYBRID_ALIGNOF(__SIZEOF_TIME32_T__)
#endif /* !__ALIGNOF_TIME32_T__ */
#ifndef __ALIGNOF_TIME64_T__
#define __ALIGNOF_TIME64_T__ __HYBRID_ALIGNOF(__SIZEOF_TIME64_T__)
#endif /* !__ALIGNOF_TIME64_T__ */
#ifndef __ALIGNOF_SOCKLEN_T__
#define __ALIGNOF_SOCKLEN_T__ __HYBRID_ALIGNOF(__SIZEOF_SOCKLEN_T__)
#endif /* !__ALIGNOF_SOCKLEN_T__ */
#ifndef __ALIGNOF_QUANTUM_DIFF_T__
#define __ALIGNOF_QUANTUM_DIFF_T__ __HYBRID_ALIGNOF(__SIZEOF_QUANTUM_DIFF_T__)
#endif /* !__ALIGNOF_QUANTUM_DIFF_T__ */
#ifndef __ALIGNOF_CLOCK_T__
#define __ALIGNOF_CLOCK_T__ __HYBRID_ALIGNOF(__SIZEOF_CLOCK_T__)
#endif /* !__ALIGNOF_CLOCK_T__ */
#ifndef __ALIGNOF_USECONDS_T__
#define __ALIGNOF_USECONDS_T__ __HYBRID_ALIGNOF(__SIZEOF_USECONDS_T__)
#endif /* !__ALIGNOF_USECONDS_T__ */
#ifndef __ALIGNOF_SUSECONDS_T__
#define __ALIGNOF_SUSECONDS_T__ __HYBRID_ALIGNOF(__SIZEOF_SUSECONDS_T__)
#endif /* !__ALIGNOF_SUSECONDS_T__ */
#ifndef __ALIGNOF_CLOCKID_T__
#define __ALIGNOF_CLOCKID_T__ __HYBRID_ALIGNOF(__SIZEOF_CLOCKID_T__)
#endif /* !__ALIGNOF_CLOCKID_T__ */
#ifndef __ALIGNOF_GID_T__
#define __ALIGNOF_GID_T__ __HYBRID_ALIGNOF(__SIZEOF_GID_T__)
#endif /* !__ALIGNOF_GID_T__ */
#ifndef __ALIGNOF_UID_T__
#define __ALIGNOF_UID_T__ __HYBRID_ALIGNOF(__SIZEOF_UID_T__)
#endif /* !__ALIGNOF_UID_T__ */
#ifndef __ALIGNOF_TIMER_T__
#define __ALIGNOF_TIMER_T__ __HYBRID_ALIGNOF(__SIZEOF_TIMER_T__)
#endif /* !__ALIGNOF_TIMER_T__ */
#ifndef __ALIGNOF_FSWORD_T__
#define __ALIGNOF_FSWORD_T__ __HYBRID_ALIGNOF(__SIZEOF_FSWORD_T__)
#endif /* !__ALIGNOF_FSWORD_T__ */
#ifndef __ALIGNOF_PHYSADDR_T__
#define __ALIGNOF_PHYSADDR_T__ __HYBRID_ALIGNOF(__SIZEOF_PHYSADDR_T__)
#endif /* !__ALIGNOF_PHYSADDR_T__ */
#ifndef __ALIGNOF_PHYSPAGE_T__
#define __ALIGNOF_PHYSPAGE_T__ __HYBRID_ALIGNOF(__SIZEOF_PHYSPAGE_T__)
#endif /* !__ALIGNOF_PHYSPAGE_T__ */
#ifndef __ALIGNOF_SA_FAMILY_T__
#define __ALIGNOF_SA_FAMILY_T__ __HYBRID_ALIGNOF(__SIZEOF_SA_FAMILY_T__)
#endif /* !__ALIGNOF_SA_FAMILY_T__ */
#ifndef __ALIGNOF_IOCTL_T__
#define __ALIGNOF_IOCTL_T__ __HYBRID_ALIGNOF(__SIZEOF_IOCTL_T__)
#endif /* !__ALIGNOF_IOCTL_T__ */
#ifndef __ALIGNOF_FCNTL_T__
#define __ALIGNOF_FCNTL_T__ __HYBRID_ALIGNOF(__SIZEOF_FCNTL_T__)
#endif /* !__ALIGNOF_FCNTL_T__ */


#ifdef __CC__
#define __CRT_PRIVATE_SINT_1   __INT8_TYPE__
#define __CRT_PRIVATE_SINT_2   __INT16_TYPE__
#define __CRT_PRIVATE_SINT_4   __INT32_TYPE__
#define __CRT_PRIVATE_UINT_1   __UINT8_TYPE__
#define __CRT_PRIVATE_UINT_2   __UINT16_TYPE__
#define __CRT_PRIVATE_UINT_4   __UINT32_TYPE__
#define __CRT_PRIVATE_SLNG_1   __INT8_TYPE__
#define __CRT_PRIVATE_SLNG_2   __INT16_TYPE__
#define __CRT_PRIVATE_SLNG_4   __LONG32_TYPE__
#define __CRT_PRIVATE_ULNG_1   __UINT8_TYPE__
#define __CRT_PRIVATE_ULNG_2   __UINT16_TYPE__
#define __CRT_PRIVATE_ULNG_4   __ULONG32_TYPE__

#ifdef __UINT64_TYPE__
#define __CRT_PRIVATE_SINT_8 __INT64_TYPE__
#define __CRT_PRIVATE_UINT_8 __UINT64_TYPE__
#define __CRT_PRIVATE_SLNG_8 __LONG64_TYPE__
#define __CRT_PRIVATE_ULNG_8 __ULONG64_TYPE__
#define __int64_t            __INT64_TYPE__
#define __uint64_t           __UINT64_TYPE__
#else /* __UINT64_TYPE__ */
#undef  __int64_t
typedef struct { __INT32_TYPE__ __lo,__hi; } __int64_t;
#define __int64_t __int64_t
#undef  __uint64_t
typedef struct { __UINT32_TYPE__ __lo,__hi; } __uint64_t;
#define __uint64_t           __uint64_t
#define __CRT_PRIVATE_SINT_8 __int64_t
#define __CRT_PRIVATE_UINT_8 __uint64_t
#define __CRT_PRIVATE_SLNG_8 __int64_t
#define __CRT_PRIVATE_ULNG_8 __uint64_t
#endif /* !__UINT64_TYPE__ */

#define __CRT_PRIVATE_SINT2(sizeof) __CRT_PRIVATE_SINT_##sizeof
#define __CRT_PRIVATE_UINT2(sizeof) __CRT_PRIVATE_UINT_##sizeof
#define __CRT_PRIVATE_SLNG2(sizeof) __CRT_PRIVATE_SLNG_##sizeof
#define __CRT_PRIVATE_ULNG2(sizeof) __CRT_PRIVATE_ULNG_##sizeof
#define __CRT_PRIVATE_SINT(sizeof)  __CRT_PRIVATE_SINT2(sizeof)
#define __CRT_PRIVATE_UINT(sizeof)  __CRT_PRIVATE_UINT2(sizeof)
#define __CRT_PRIVATE_SLNG(sizeof)  __CRT_PRIVATE_SLNG2(sizeof)
#define __CRT_PRIVATE_ULNG(sizeof)  __CRT_PRIVATE_ULNG2(sizeof)

__DECL_BEGIN

#ifndef ____s8_defined
#define ____s8_defined
/* These need to be typedefs, since 3rd party headers like
 * <drm.h>  will try to re-define these through additional
 * typedefs that would cause compiler errors if we defined
 * them as pure macros here.
 * Think: `typedef int8_t __s8;', which would break if
 *        it expanded to `typedef int8_t signed char;'
 * NOTE: STDC allows for re-typedef-ing a declaration, so
 *       long as  nothing changes,  so as  long as  these
 *       typedefs match what is  found in said 3rd  party
 *       headers, there'll be no problem. */
typedef __INT8_TYPE__ __s8;
#define __s8 __s8
typedef __UINT8_TYPE__ __u8;
#define __u8 __u8
typedef __INT16_TYPE__ __s16;
#define __s16 __s16
typedef __UINT16_TYPE__ __u16;
#define __u16 __u16
typedef __INT32_TYPE__ __s32;
#define __s32 __s32
typedef __UINT32_TYPE__ __u32;
#define __u32 __u32
#ifdef __INT64_TYPE__
typedef __INT64_TYPE__ __s64;
#define __s64 __s64
#endif /* __INT64_TYPE__ */
#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ __u64;
#define __u64 __u64
#endif /* __UINT64_TYPE__ */
#endif /* !____s8_defined */

#ifndef ____le8_defined
#define ____le8_defined
#ifdef __INTELLISENSE__
typedef __intern::____intellisense_endianint<1234, __UINT8_TYPE__> __le8;
typedef __intern::____intellisense_endianint<4321, __UINT8_TYPE__> __be8;
typedef __intern::____intellisense_endianint<1234, __UINT16_TYPE__> __le16;
typedef __intern::____intellisense_endianint<4321, __UINT16_TYPE__> __be16;
typedef __intern::____intellisense_endianint<1234, __UINT32_TYPE__> __le32;
typedef __intern::____intellisense_endianint<4321, __UINT32_TYPE__> __be32;
#define __le8  __le8
#define __be8  __be8
#define __le16 __le16
#define __be16 __be16
#define __le32 __le32
#define __be32 __be32
#ifdef __UINT64_TYPE__
typedef __intern::____intellisense_endianint<1234, __UINT64_TYPE__> __le64;
typedef __intern::____intellisense_endianint<4321, __UINT64_TYPE__> __be64;
#define __le64 __le64
#define __be64 __be64
#endif /* __UINT64_TYPE__ */
#elif defined(__bitwise)
typedef __bitwise __UINT8_TYPE__  __le8;
typedef __bitwise __UINT8_TYPE__  __be8;
typedef __bitwise __UINT16_TYPE__ __le16;
typedef __bitwise __UINT16_TYPE__ __be16;
typedef __bitwise __UINT32_TYPE__ __le32;
typedef __bitwise __UINT32_TYPE__ __be32;
#define __le8  __le8
#define __be8  __be8
#define __le16 __le16
#define __be16 __be16
#define __le32 __le32
#define __be32 __be32
#ifdef __UINT64_TYPE__
typedef __bitwise __UINT64_TYPE__ __le64;
typedef __bitwise __UINT64_TYPE__ __be64;
#define __le64 __le64
#define __be64 __be64
#endif /* __UINT64_TYPE__ */
#elif (defined(__bitwise__) || defined(__CHECKER__)) && defined(__CHECK_ENDIAN__)
#ifndef __bitwise__
#define __bitwise__ __attribute__((bitwise))
#endif /* !__bitwise__ */
typedef __bitwise__ __UINT8_TYPE__ __le8;
typedef __bitwise__ __UINT8_TYPE__ __be8;
typedef __bitwise__ __UINT16_TYPE__ __le16;
typedef __bitwise__ __UINT16_TYPE__ __be16;
typedef __bitwise__ __UINT32_TYPE__ __le32;
typedef __bitwise__ __UINT32_TYPE__ __be32;
#define __le8  __le8
#define __be8  __be8
#define __le16 __le16
#define __be16 __be16
#define __le32 __le32
#define __be32 __be32
#ifdef __UINT64_TYPE__
typedef __bitwise__ __UINT64_TYPE__ __le64;
typedef __bitwise__ __UINT64_TYPE__ __be64;
#define __le64 __le64
#define __be64 __be64
#endif /* __UINT64_TYPE__ */
#else /* ... */
#define __le8  __UINT8_TYPE__
#define __be8  __UINT8_TYPE__
#define __le16 __UINT16_TYPE__
#define __be16 __UINT16_TYPE__
#define __le32 __UINT32_TYPE__
#define __be32 __UINT32_TYPE__
#ifdef __UINT64_TYPE__
#define __le64 __UINT64_TYPE__
#define __be64 __UINT64_TYPE__
#endif /* __UINT64_TYPE__ */
#endif /* !... */
#endif /* !____le8_defined */

/* Special integral types (defined via <hybrid/typecore.h>) */
#define __int8_t          __INT8_TYPE__
#define __int16_t         __INT16_TYPE__
#define __int32_t         __INT32_TYPE__
#define __uint8_t         __UINT8_TYPE__
#define __uint16_t        __UINT16_TYPE__
#define __uint32_t        __UINT32_TYPE__
#define __u_char          unsigned char
#define __u_short         unsigned short
#define __u_int           unsigned int
#define __u_long          unsigned long
#define __ptrdiff_t       __PTRDIFF_TYPE__
#define __size_t          __SIZE_TYPE__
#define __ssize_t         __SSIZE_TYPE__
#define __intptr_t        __INTPTR_TYPE__
#define __uintptr_t       __UINTPTR_TYPE__
#define __byte_t          __BYTE_TYPE__
#define __register_t      __REGISTER_TYPE__
#define __sregister_t     __SREGISTER_TYPE__
#define __quad_t          __CRT_PRIVATE_SLNG_8
#define __u_quad_t        __CRT_PRIVATE_ULNG_8
#define __syscall_slong_t __CRT_PRIVATE_SLNG(__SIZEOF_SYSCALL_LONG_T__)
#define __syscall_ulong_t __CRT_PRIVATE_ULNG(__SIZEOF_SYSCALL_LONG_T__)
#define __errno_t         __CRT_PRIVATE_SINT(__SIZEOF_ERRNO_T__)
#define __signo_t         __CRT_PRIVATE_SINT(__SIZEOF_SIGNO_T__)
#define __iomode_t        __CRT_PRIVATE_UINT(__SIZEOF_IOMODE_T__)
#define __fd_t            __CRT_PRIVATE_SINT(__SIZEOF_FD_T__)
#define __ufd_t           __CRT_PRIVATE_UINT(__SIZEOF_FD_T__)
#define __major_t         __CRT_PRIVATE_UINT(__SIZEOF_MAJOR_T__)
#define __minor_t         __CRT_PRIVATE_UINT(__SIZEOF_MINOR_T__)
#define __dev_t           __CRT_PRIVATE_UINT(__SIZEOF_DEV_T__)
#define __id_t            __CRT_PRIVATE_UINT(__SIZEOF_ID_T__)
#define __pid_t           __CRT_PRIVATE_SINT(__SIZEOF_PID_T__)
#define __upid_t          __CRT_PRIVATE_UINT(__SIZEOF_PID_T__)
#define __key_t           __CRT_PRIVATE_SINT(__SIZEOF_KEY_T__)
#define __daddr_t         __CRT_PRIVATE_SINT(__SIZEOF_DADDR_T__)
#define __qaddr_t         __CRT_PRIVATE_SLNG_8
#define __off32_t         __CRT_PRIVATE_SLNG(__SIZEOF_OFF32_T__)
#define __off64_t         __CRT_PRIVATE_SLNG(__SIZEOF_OFF64_T__)
#define __fsblkcnt32_t    __CRT_PRIVATE_ULNG(__SIZEOF_FSBLKCNT32_T__)
#define __fsblkcnt64_t    __CRT_PRIVATE_ULNG(__SIZEOF_FSBLKCNT64_T__)
#define __fsfilcnt32_t    __CRT_PRIVATE_ULNG(__SIZEOF_FSFILCNT32_T__)
#define __fsfilcnt64_t    __CRT_PRIVATE_ULNG(__SIZEOF_FSFILCNT64_T__)
#define __ino32_t         __CRT_PRIVATE_ULNG(__SIZEOF_INO32_T__)
#define __ino64_t         __CRT_PRIVATE_ULNG(__SIZEOF_INO64_T__)
#define __pos32_t         __CRT_PRIVATE_ULNG(__SIZEOF_OFF32_T__)
#define __pos64_t         __CRT_PRIVATE_ULNG(__SIZEOF_OFF64_T__)
#define __loff_t          __CRT_PRIVATE_SLNG(__SIZEOF_LOFF_T__)
#define __lpos_t          __CRT_PRIVATE_ULNG(__SIZEOF_LOFF_T__)
#define __socklen_t       __CRT_PRIVATE_UINT(__SIZEOF_SOCKLEN_T__)
#define __ssocklen_t      __CRT_PRIVATE_SINT(__SIZEOF_SOCKLEN_T__)
#define __rlim32_t        __CRT_PRIVATE_UINT(__SIZEOF_RLIM32_T__)
#define __rlim64_t        __CRT_PRIVATE_UINT(__SIZEOF_RLIM64_T__)
#define __nlink_t         __CRT_PRIVATE_ULNG(__SIZEOF_NLINK_T__)
#define __quantum_diff_t  __CRT_PRIVATE_UINT(__SIZEOF_QUANTUM_DIFF_T__)
#define __clock_t         __CRT_PRIVATE_SLNG(__SIZEOF_CLOCK_T__)
#define __suseconds_t     __CRT_PRIVATE_SLNG(__SIZEOF_SUSECONDS_T__)
#define __clockid_t       __CRT_PRIVATE_SINT(__SIZEOF_CLOCKID_T__)
#define __gid_t           __CRT_PRIVATE_UINT(__SIZEOF_GID_T__)
#define __uid_t           __CRT_PRIVATE_UINT(__SIZEOF_UID_T__)
#define __useconds_t      __CRT_PRIVATE_UINT(__SIZEOF_USECONDS_T__)
#define __fsword_t        __CRT_PRIVATE_SLNG(__SIZEOF_FSWORD_T__)
#define __port_t          __CRT_PRIVATE_UINT(__SIZEOF_PORT_T__)
#define __physaddr_t      __CRT_PRIVATE_ULNG(__SIZEOF_PHYSADDR_T__)
#define __physpage_t      __CRT_PRIVATE_ULNG(__SIZEOF_PHYSPAGE_T__)
#define __sa_family_t     __CRT_PRIVATE_UINT(__SIZEOF_SA_FAMILY_T__)
#define _TIME32_T_DEFINED 1
#define __time32_t        __CRT_PRIVATE_SINT(__SIZEOF_TIME32_T__)
#define _TIME64_T_DEFINED 1
#define __time64_t        __CRT_PRIVATE_SINT(__SIZEOF_TIME64_T__)
#define __ioctl_t         __CRT_PRIVATE_ULNG(__SIZEOF_IOCTL_T__) /* Type for `ioctl(2)'s `cmd' argument. */

/* Types that change sign based on feature flags. */
#ifdef __USE_KOS_ALTERATIONS
#define __fcntl_t    __CRT_PRIVATE_UINT(__SIZEOF_FCNTL_T__) /* Type for `fcntl(2)'s `cmd' argument. */
#define __oflag_t    __CRT_PRIVATE_UINT(__SIZEOF_OFLAG_T__)
#define __atflag_t   __CRT_PRIVATE_UINT(__SIZEOF_ATFLAG_T__)
#define __blkcnt32_t __CRT_PRIVATE_ULNG(__SIZEOF_BLKCNT32_T__)
#define __blkcnt64_t __CRT_PRIVATE_ULNG(__SIZEOF_BLKCNT64_T__)
#define __blksize_t  __CRT_PRIVATE_ULNG(__SIZEOF_BLKSIZE_T__)
#else /* __USE_KOS_ALTERATIONS */
#define __fcntl_t    __CRT_PRIVATE_SINT(__SIZEOF_FCNTL_T__) /* Type for `fcntl(2)'s `cmd' argument. */
#define __oflag_t    __CRT_PRIVATE_SINT(__SIZEOF_OFLAG_T__)
#define __atflag_t   __CRT_PRIVATE_SINT(__SIZEOF_ATFLAG_T__)
#define __blkcnt32_t __CRT_PRIVATE_SLNG(__SIZEOF_BLKCNT32_T__)
#define __blkcnt64_t __CRT_PRIVATE_SLNG(__SIZEOF_BLKCNT64_T__)
#define __blksize_t  __CRT_PRIVATE_SLNG(__SIZEOF_BLKSIZE_T__)
#endif /* !__USE_KOS_ALTERATIONS */

#if defined(__USE_DOS) && !defined(__USE_KOS_ALTERATIONS)
/* Simple enough: DOS defines this one as signed, rather than unsigned. */
#define __mode_t __CRT_PRIVATE_SINT(__SIZEOF_MODE_T__)
#else /* __USE_DOS */
#define __mode_t __CRT_PRIVATE_UINT(__SIZEOF_MODE_T__)
#endif /* !__USE_DOS */


/* Special types that may require typedef-s */
#if __SIZEOF_CADDR_T__ == __SIZEOF_POINTER__
#define __caddr_t char *
#else /* __SIZEOF_CADDR_T__ == __SIZEOF_POINTER__ */
#define __caddr_t __CRT_PRIVATE_ULNG(__SIZEOF_CADDR_T__)
#endif /* __SIZEOF_CADDR_T__ != __SIZEOF_POINTER__ */

#if __SIZEOF_FSID_T__ == 8
typedef struct { __INT32_TYPE__ __val[2]; } __fsid_t;
#elif __SIZEOF_FSID_T__ == 4
typedef struct { __INT32_TYPE__ __val[1]; } __fsid_t;
#elif __SIZEOF_FSID_T__ == 2
typedef struct { __INT16_TYPE__ __val[1]; } __fsid_t;
#else /* __SIZEOF_FSID_T__ == ... */
typedef struct { __INT8_TYPE__  __val[__SIZEOF_FSID_T__]; } __fsid_t;
#endif /* __SIZEOF_FSID_T__ != ... */
#define __fsid_t __fsid_t

#if __SIZEOF_TIMER_T__ == __SIZEOF_POINTER__
#define __timer_t void *
#else /* __SIZEOF_TIMER_T__ == __SIZEOF_POINTER__ */
#define __timer_t __CRT_PRIVATE_ULNG(__SIZEOF_TIMER_T__)
#endif /* __SIZEOF_TIMER_T__ != __SIZEOF_POINTER__ */
#endif /* __CC__ */

__DECL_END


#define __SIZEOF_INO_T__   __FS_SIZEOF(INO)   /* == sizeof(ino_t) */
#define __SIZEOF_OFF_T__   __FS_SIZEOF(OFF)   /* == sizeof(off_t) */
#define __SIZEOF_POS_T__   __FS_SIZEOF(OFF)   /* == sizeof(pos_t) */
#define __SIZEOF_TIME_T__  __TM_SIZEOF(TIME)  /* == sizeof(time_t) */
#define __ALIGNOF_INO_T__  __FS_ALIGNOF(INO)  /* == alignof(ino_t) */
#define __ALIGNOF_OFF_T__  __FS_ALIGNOF(OFF)  /* == alignof(off_t) */
#define __ALIGNOF_POS_T__  __FS_ALIGNOF(OFF)  /* == alignof(pos_t) */
#define __ALIGNOF_TIME_T__ __TM_ALIGNOF(TIME) /* == alignof(time_t) */



#ifdef __CRT_DOS_PRIMARY
/* DOS filesystem headers contain different types for these... */
#undef __dev_t
#undef __ino32_t
#undef __ino64_t
#undef __off_t
#undef __off32_t
#undef __off64_t
#undef __pos_t
#undef __pos32_t
#undef __pos64_t
#undef __clock_t
#undef __SIZEOF_DEV_T__
#undef __SIZEOF_INO32_T__
#undef __SIZEOF_INO64_T__
#undef __SIZEOF_OFF32_T__
#undef __SIZEOF_OFF64_T__
#undef __SIZEOF_CLOCK_T__
#define __dev_t            __UINT32_TYPE__
#define __ino32_t          __UINT16_TYPE__
#define __ino64_t          __UINT16_TYPE__
#define __off32_t          __INT32_TYPE__
#define __off64_t          __INT32_TYPE__
#define __pos32_t          __UINT32_TYPE__
#define __pos64_t          __UINT32_TYPE__
#define __clock_t          __LONG32_TYPE__
#define __SIZEOF_DEV_T__   4
#define __SIZEOF_INO32_T__ 2
#define __SIZEOF_INO64_T__ 2
#define __SIZEOF_OFF32_T__ 4
#define __SIZEOF_OFF64_T__ 4
#define __SIZEOF_CLOCK_T__ 4
#endif /* __CRT_DOS_PRIMARY */

#endif /* !_BITS_TYPES_H */
