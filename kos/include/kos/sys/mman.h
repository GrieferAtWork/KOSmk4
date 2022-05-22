/* HASH CRC-32:0xf2a84f05 */
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
#ifndef _KOS_SYS_MMAN_H
#define _KOS_SYS_MMAN_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <sys/mman.h>
#include <kos/anno.h>

#ifdef __CC__
__SYSDECL_BEGIN

#include <bits/types.h>
#if defined(__CRT_HAVE_MMap) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> mmap(2), mmap64(2)
 * @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE  | MAP_STACK | MAP_SYNC  |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE' */
__CDECLARE(__ATTR_WUNUSED __ATTR_ACCESS_NONE(1),void *,__THROWING,MMap,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __FS_TYPE(pos) __offset),(__addr,__len,__prot,__flags,__fd,__offset))
#elif defined(__CRT_HAVE_MMap64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> mmap(2), mmap64(2)
 * @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE  | MAP_STACK | MAP_SYNC  |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_NONE(1),void *,__THROWING,MMap,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __FS_TYPE(pos) __offset),MMap64,(__addr,__len,__prot,__flags,__fd,__offset))
#elif defined(__CRT_HAVE_MMap64) || defined(__CRT_HAVE_MMap)
#include <libc/local/kos.sys.mman/MMap.h>
/* >> mmap(2), mmap64(2)
 * @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE  | MAP_STACK | MAP_SYNC  |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(MMap, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ACCESS_NONE(1) void *(__LIBCCALL MMap)(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __FS_TYPE(pos) __offset) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(MMap))(__addr, __len, __prot, __flags, __fd, __offset); })
#endif /* ... */
/* >> munmap(2)
 * Unmap memory from `addr...+=len' */
__CDECLARE_VOID_OPT(__ATTR_ACCESS_NONE(1),__THROWING,MUnmap,(void *__addr, size_t __len),(__addr,__len))
/* >> mprotect(2)
 * @param prot: Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE |
 *              PROT_READ | PROT_SEM | PROT_GROWSUP | PROT_GROWSDOWN' */
__CDECLARE_VOID_OPT(__ATTR_ACCESS_NONE(1),__THROWING,MProtect,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot),(__addr,__len,__prot))
/* >> msync(2)
 * @param flags: Set of `MS_ASYNC | MS_INVALIDATE | MS_SYNC' */
__CDECLARE_VOID_OPT(__ATTR_ACCESS_NONE(1),__THROWING,MSync,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __flags),(__addr,__len,__flags))
/* >> mlock(2) */
__CDECLARE_VOID_OPT(__ATTR_ACCESS_NONE(1),__THROWING,MLock,(void const *__addr, size_t __len),(__addr,__len))
/* >> munlock(2) */
__CDECLARE_VOID_OPT(__ATTR_ACCESS_NONE(1),__THROWING,MUnlock,(void const *__addr, size_t __len),(__addr,__len))
/* >> mlockall(2)
 * @param flags: Set of `MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT' */
__CDECLARE_VOID_OPT(,__THROWING,MLockAll,(__STDC_INT_AS_UINT_T __flags),(__flags))
/* >> munlockall(2) */
__CDECLARE_VOID_OPT(,__THROWING,MUnlockAll,(void),())
#ifdef __CRT_HAVE_ShmOpen
__CDECLARE(__ATTR_ACCESS_RO(1),__fd_t,__THROWING,ShmOpen,(char const *__name, __oflag_t __oflags, mode_t __mode),(__name,__oflags,__mode))
#else /* __CRT_HAVE_ShmOpen */
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_Open64) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_OpenAt64) || defined(__CRT_HAVE_OpenAt))) || defined(__CRT_HAVE_Open)
#include <libc/local/kos.sys.mman/ShmOpen.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ShmOpen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(1) __fd_t (__LIBCCALL ShmOpen)(char const *__name, __oflag_t __oflags, mode_t __mode) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ShmOpen))(__name, __oflags, __mode); })
#endif /* __CRT_HAVE_Open64 || (__AT_FDCWD && (__CRT_HAVE_OpenAt64 || __CRT_HAVE_OpenAt)) || __CRT_HAVE_Open */
#endif /* !__CRT_HAVE_ShmOpen */
#ifdef __CRT_HAVE_ShmUnlink
__CDECLARE_VOID(__ATTR_ACCESS_RO(1),__THROWING,ShmUnlink,(char const *__name),(__name))
#else /* __CRT_HAVE_ShmUnlink */
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_Unlink) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_UnlinkAt))
#include <libc/local/kos.sys.mman/ShmUnlink.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ShmUnlink, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(1) void (__LIBCCALL ShmUnlink)(char const *__name) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ShmUnlink))(__name); })
#endif /* __CRT_HAVE_Unlink || (__AT_FDCWD && __CRT_HAVE_UnlinkAt) */
#endif /* !__CRT_HAVE_ShmUnlink */

#ifdef __USE_MISC
#ifdef __CRT_HAVE_MAdvise
__CDECLARE_VOID(__ATTR_ACCESS_NONE(1),__THROWING,MAdvise,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __advice),(__addr,__len,__advice))
#else /* __CRT_HAVE_MAdvise */
#include <libc/local/kos.sys.mman/MAdvise.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(MAdvise, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_NONE(1) void (__LIBCCALL MAdvise)(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __advice) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(MAdvise))(__addr, __len, __advice); })
#endif /* !__CRT_HAVE_MAdvise */
__CDECLARE_VOID_OPT(__ATTR_ACCESS_NONE(1),__THROWING,MInCore,(void *__start, size_t __len, unsigned char *__vec),(__start,__len,__vec))
#endif /* __USE_MISC */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_MMap) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> mmap(2), mmap64(2)
 * @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE  | MAP_STACK | MAP_SYNC  |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_NONE(1),void *,__THROWING,MMap64,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __pos64_t __offset),MMap,(__addr,__len,__prot,__flags,__fd,__offset))
#elif defined(__CRT_HAVE_MMap64)
/* >> mmap(2), mmap64(2)
 * @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE  | MAP_STACK | MAP_SYNC  |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE' */
__CDECLARE(__ATTR_WUNUSED __ATTR_ACCESS_NONE(1),void *,__THROWING,MMap64,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __pos64_t __offset),(__addr,__len,__prot,__flags,__fd,__offset))
#elif defined(__CRT_HAVE_MMap)
#include <libc/local/kos.sys.mman/MMap64.h>
/* >> mmap(2), mmap64(2)
 * @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE  | MAP_STACK | MAP_SYNC  |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(MMap64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ACCESS_NONE(1) void *(__LIBCCALL MMap64)(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __pos64_t __offset) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(MMap64))(__addr, __len, __prot, __flags, __fd, __offset); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */

#ifdef __USE_XOPEN2K
#ifdef __CRT_HAVE_PosixMAdvise
__CDECLARE_VOID(__ATTR_ACCESS_NONE(1),__THROWING,PosixMAdvise,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __advice),(__addr,__len,__advice))
#else /* __CRT_HAVE_PosixMAdvise */
#include <libc/local/kos.sys.mman/PosixMAdvise.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(PosixMAdvise, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_NONE(1) void (__LIBCCALL PosixMAdvise)(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __advice) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(PosixMAdvise))(__addr, __len, __advice); })
#endif /* !__CRT_HAVE_PosixMAdvise */
#endif /* __USE_XOPEN2K */

#ifdef __USE_GNU
#ifdef __CRT_HAVE_MRemap
/* >> mremap(2)
 * @param flags: Set of `MREMAP_MAYMOVE | MREMAP_FIXED' */
__LIBC __ATTR_ACCESS_NONE(1) void *(__VLIBCCALL MRemap)(void *__addr, size_t __old_len, size_t __new_len, __STDC_INT_AS_UINT_T __flags, ...) __THROWS(...) __CASMNAME_SAME("MRemap");
#endif /* __CRT_HAVE_MRemap */
/* >> remap_file_pages(2) */
__CDECLARE_VOID_OPT(__ATTR_ACCESS_NONE(1),__THROWING,RemapFilePages,(void *__start, size_t __size, __STDC_INT_AS_UINT_T __prot, size_t __pgoff, __STDC_INT_AS_UINT_T __flags),(__start,__size,__prot,__pgoff,__flags))
/* >> memfd_create(2)
 * @param: name:  Set `/proc/[pid]/fd/[return]' = "memfd:${name}"
 * @param: flags: Set of `MFD_CLOEXEC | MFD_CLOFORK | MFD_ALLOW_SEALING | MFD_HUGETLB' */
__CDECLARE_OPT(,__fd_t,__THROWING,MemFdCreate,(char const *__name, unsigned int __flags),(__name,__flags))
/* >> mlock2(2) */
__CDECLARE_VOID_OPT(__ATTR_ACCESS_NONE(1),__THROWING,MLock2,(void const *__addr, size_t __length, unsigned int __flags),(__addr,__length,__flags))
/* >> pkey_alloc(2) */
__CDECLARE_OPT(,int,__THROWING,PKeyAlloc,(unsigned int __flags, unsigned int __access_rights),(__flags,__access_rights))
#ifdef __CRT_HAVE_PKeySet
/* >> pkey_set(3) */
__CDECLARE_VOID(,__THROWING,PKeySet,(int __pkey, unsigned int __access_rights),(__pkey,__access_rights))
#else /* __CRT_HAVE_PKeySet */
#include <asm/pkey.h>
#if defined(__ARCH_HAVE_PKEY) && defined(__CRT_HAVE_except_thrown)
#include <libc/local/kos.sys.mman/PKeySet.h>
/* >> pkey_set(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(PKeySet, __FORCELOCAL __ATTR_ARTIFICIAL void (__LIBCCALL PKeySet)(int __pkey, unsigned int __access_rights) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(PKeySet))(__pkey, __access_rights); })
#endif /* __ARCH_HAVE_PKEY && __CRT_HAVE_except_thrown */
#endif /* !__CRT_HAVE_PKeySet */
#ifdef __CRT_HAVE_PKeyGet
/* >> pkey_get(3) */
__CDECLARE(,unsigned int,__THROWING,PKeyGet,(int __pkey),(__pkey))
#else /* __CRT_HAVE_PKeyGet */
#include <asm/pkey.h>
#if defined(__ARCH_HAVE_PKEY) && defined(__CRT_HAVE_except_thrown)
#include <libc/local/kos.sys.mman/PKeyGet.h>
/* >> pkey_get(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(PKeyGet, __FORCELOCAL __ATTR_ARTIFICIAL unsigned int (__LIBCCALL PKeyGet)(int __pkey) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(PKeyGet))(__pkey); })
#endif /* __ARCH_HAVE_PKEY && __CRT_HAVE_except_thrown */
#endif /* !__CRT_HAVE_PKeyGet */
/* >> pkey_free(2) */
__CDECLARE_VOID_OPT(,__THROWING,PKeyFree,(int __pkey),(__pkey))
/* >> pkey_mprotect(2) */
__CDECLARE_VOID_OPT(__ATTR_ACCESS_NONE(1),__THROWING,PKeyMprotect,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot, int __pkey),(__addr,__len,__prot,__pkey))
#endif /* __USE_GNU */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_SYS_MMAN_H */
