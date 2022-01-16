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
#ifndef _BASETSD_H_
#define _BASETSD_H_ 1

#include "__winstd.h"
/**/

#include <hybrid/__pointer.h>
#include <hybrid/typecore.h>

#ifdef __CC__
#if defined(_MSC_VER) && !defined(__clang__)
#define POINTER_32 __ptr32
#define POINTER_64 __ptr64
#else /* ... */
#define POINTER_32 /* Nothing */
#define POINTER_64 /* Nothing */
#endif /* !... */
#define FIRMWARE_PTR /* Nothing */

#ifndef _W64
#define _W64
#endif

#if __SIZEOF_POINTER__ >= 8
#define __int3264 __int64
#else /* __SIZEOF_POINTER__ >= 8 */
#define __int3264 __int32
#endif /* __SIZEOF_POINTER__ < 8 */

__DECL_BEGIN
typedef __UINTPTR_TYPE__ POINTER_64_INT;

typedef __INT8_TYPE__ INT8, *PINT8;
typedef __INT16_TYPE__ INT16, *PINT16;
typedef __INT32_TYPE__ INT32, *PINT32;
typedef __INT64_TYPE__ INT64, *PINT64;
typedef __UINT8_TYPE__ UINT8, *PUINT8;
typedef __UINT16_TYPE__ UINT16, *PUINT16;
typedef __UINT32_TYPE__ UINT32, *PUINT32;
typedef __UINT64_TYPE__ UINT64, *PUINT64;
typedef __INT32_TYPE__ LONG32, *PLONG32;
typedef __UINT32_TYPE__ ULONG32, *PULONG32;
typedef __UINT32_TYPE__ DWORD32, *PDWORD32;

typedef __INTPTR_TYPE__ INT_PTR,*PINT_PTR;
typedef __UINTPTR_TYPE__ UINT_PTR,*PUINT_PTR;
typedef __LONGPTR_TYPE__ LONG_PTR,*PLONG_PTR;
typedef __ULONGPTR_TYPE__ ULONG_PTR,*PULONG_PTR;

typedef __UINTPTR_HALF_TYPE__ UHALF_PTR, *PUHALF_PTR;
typedef __INTPTR_HALF_TYPE__ HALF_PTR, *PHALF_PTR;
typedef __LONGPTR_TYPE__ SHANDLE_PTR;
typedef __ULONGPTR_TYPE__ HANDLE_PTR;

typedef ULONG_PTR SIZE_T, *PSIZE_T;
typedef LONG_PTR SSIZE_T, *PSSIZE_T;
typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;
typedef __LONG64_TYPE__ LONG64, *PLONG64;
typedef __ULONG64_TYPE__ ULONG64, *PULONG64;
typedef __UINT64_TYPE__ DWORD64, *PDWORD64;
typedef ULONG_PTR KAFFINITY;
typedef KAFFINITY *PKAFFINITY;

#if __SIZEOF_POINTER__ >= 8
#define ADDRESS_TAG_BIT     __UINT64_C(0x40000000000)
#define HandleToULong(h)    ((__ULONG32_TYPE__)(ULONG_PTR)(void const *)(h))
#define HandleToLong(h)     ((__LONG32_TYPE__)(LONG_PTR)(void const *)(h))
#define ULongToHandle(h)    ((void *)(UINT_PTR)(__ULONG32_TYPE__)(h))
#define LongToHandle(h)     ((void *)(INT_PTR)(__LONG32_TYPE__)(h))
#define PtrToUlong(p)       ((__ULONG32_TYPE__)(ULONG_PTR)(void const *)(p))
#define PtrToUint(p)        ((__UINT32_TYPE__)(UINT_PTR)(void const *)(p))
#define PtrToUshort(p)      ((__UINT16_TYPE__)(__ULONG32_TYPE__)(ULONG_PTR)(void const *)(p))
#define PtrToLong(p)        ((__LONG32_TYPE__)(LONG_PTR)(void const *)(p))
#define PtrToInt(p)         ((__INT32_TYPE__)(INT_PTR)(void const *)(p))
#define PtrToShort(p)       ((__INT16_TYPE__)(__LONG32_TYPE__)(LONG_PTR)(void const *)(p))
#define IntToPtr(i)         ((void *)(INT_PTR)(__INT32_TYPE__)(i))
#define UIntToPtr(ui)       ((void *)(UINT_PTR)(__UINT32_TYPE__)(ui))
#define LongToPtr(l)        ((void *)(LONG_PTR)(__LONG32_TYPE__)(l))
#define ULongToPtr(ul)      ((void *)(ULONG_PTR)(__ULONG32_TYPE__)(ul))
#define PtrToPtr64(p)       ((void *)(p))
#define Ptr64ToPtr(p)       ((void *)(p))
#define HandleToHandle64(h) PtrToPtr64(h)
#define Handle64ToHandle(h) Ptr64ToPtr(h)
#define Ptr32ToPtr(p)       ((void *)(void const *)(p))
#define Handle32ToHandle(h) ((void *)(void const *)(h))
#define PtrToPtr32(p)       ((void *)(ULONG_PTR)(void const *)(p))
#define HandleToHandle32(h) PtrToPtr32(h)
#else /* __SIZEOF_POINTER__ >= 8 */
#define ADDRESS_TAG_BIT     __UINT32_C(0x80000000)
#define HandleToULong(h)    ((ULONG)(ULONG_PTR)(h))
#define HandleToLong(h)     ((LONG)(LONG_PTR)(h))
#define ULongToHandle(ul)   ((HANDLE)(ULONG_PTR)(ul))
#define LongToHandle(h)     ((HANDLE)(LONG_PTR)(h))
#define PtrToUlong(p)       ((ULONG)(ULONG_PTR)(p))
#define PtrToLong(p)        ((LONG)(LONG_PTR)(p))
#define PtrToUint(p)        ((UINT)(UINT_PTR)(p))
#define PtrToInt(p)         ((INT)(INT_PTR)(p))
#define PtrToUshort(p)      ((__UINT16_TYPE__)(ULONG_PTR)(p))
#define PtrToShort(p)       ((__INT16_TYPE__)(LONG_PTR)(p))
#define IntToPtr(i)         ((void *)(INT_PTR)((__INT32_TYPE__)(i)))
#define UIntToPtr(ui)       ((void *)(UINT_PTR)((__UINT32_TYPE__)(ui)))
#define LongToPtr(l)        ((void *)(LONG_PTR)((__LONG32_TYPE__)(l)))
#define ULongToPtr(ul)      ((void *)(ULONG_PTR)((__ULONG32_TYPE__)(ul)))
#define PtrToPtr64(p)       ((void *)(ULONG_PTR)(void const *)(p))
#define Ptr64ToPtr(p)       ((void *)(ULONG_PTR)(void const *)(p))
#define HandleToHandle64(h) ((void *)(void const *)(h))
#define Handle64ToHandle(h) ((void *)(ULONG_PTR)(void const *)(h))
#define Ptr32ToPtr(p)       ((void *)p)
#define Handle32ToHandle(h) (Ptr32ToPtr(h))
#define PtrToPtr32(p)       ((void *)p)
#define HandleToHandle32(h) (PtrToPtr32(h))
#endif /* __SIZEOF_POINTER__ < 8 */

#define HandleToUlong(h)  HandleToULong(h)
#define UlongToHandle(ul) ULongToHandle(ul)
#define UlongToPtr(ul)    ULongToPtr(ul)
#define UintToPtr(ui)     UIntToPtr(ui)
#define MAXUINT_PTR       (~((UINT_PTR)0))
#define MAXINT_PTR        ((INT_PTR)(MAXUINT_PTR >> 1))
#define MININT_PTR        (~MAXINT_PTR)
#define MAXULONG_PTR      (~((ULONG_PTR)0))
#define MAXLONG_PTR       ((LONG_PTR)(MAXULONG_PTR >> 1))
#define MINLONG_PTR       (~MAXLONG_PTR)
#define MAXUHALF_PTR      ((UHALF_PTR)~0)
#define MAXHALF_PTR       ((HALF_PTR)(MAXUHALF_PTR >> 1))
#define MINHALF_PTR       (~MAXHALF_PTR)

__DECL_END
#endif /* __CC__ */

#endif /* !_BASETSD_H_ */
