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
#ifndef _NT_HANDLEAPI_H
#define _NT_HANDLEAPI_H 1

#include "__stdinc.h"
/**/

#ifdef __KOS__
#include <kos/types.h>
#include <kos/kernel/paging.h>
#endif /* __KOS__ */

#include "types.h"

/* We define NT handles in such a manner that you can implicitly  cast
 * pointers to user-space  only handle-like objects  into HANDLE.  But
 * to also support fd-style handles, we construct addresses that would
 * overlap  with kernel-space,  which (when  used as  handles) will be
 * interpreted as such, allowing us to differentiate.
 */

#ifdef __CC__
__DECL_BEGIN

#ifdef __KOS__
#ifdef KERNELSPACE_HIGHMEM
#if KERNELSPACE_BASE == __UINT32_C(0xc0000000)
#define _NTHANDLE_FDMASK __UINT32_C(0x3fffffff)
#define _NTHANDLE_FDBITS 30
#elif KERNELSPACE_BASE == __UINT64_C(0xffff800000000000)
#define _NTHANDLE_FDMASK __UINT32_C(0x7fffffffffff)
#define _NTHANDLE_FDBITS 47
#else /* KERNELSPACE_BASE == ... */
#error "Unsupported `KERNELSPACE_BASE'"
#endif /* KERNELSPACE_BASE != ... */
#define NTHANDLE_ISFD(handle) ((__UINTPTR_TYPE__)(handle) >= KERNELSPACE_BASE)
#if _NTHANDLE_FDBITS >= (__SIZEOF_INT__ * 8)
#define NTHANDLE_ASFD(handle) ((int)(unsigned int)(__UINTPTR_TYPE__)(handle))
#else /* _NTHANDLE_FDBITS >= (__SIZEOF_INT__ * 8) */
#define _NTHANDLE_FDSHIFT     ((__SIZEOF_INT__ * 8) - _NTHANDLE_FDBITS)
#define NTHANDLE_ASFD(handle) (((int)(unsigned int)(__UINTPTR_TYPE__)(handle) << _NTHANDLE_FDSHIFT) >> _NTHANDLE_FDSHIFT)
#endif /* _NTHANDLE_FDBITS < (__SIZEOF_INT__ * 8) */
#define NTHANDLE_FROMFD(fd) ((HANDLE)((__UINTPTR_TYPE__)((int)(fd)&_NTHANDLE_FDMASK) + KERNELSPACE_BASE))
#else /* KERNELSPACE_HIGHMEM */
#error "Unsupported configuration"
#endif /* !KERNELSPACE_HIGHMEM */
#define NTHANDLE_ISPTR(x) (!NTHANDLE_ISFD(x))
#endif /* __KOS__ */


#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)

#define HANDLE_FLAG_INHERIT            0x1
#define HANDLE_FLAG_PROTECT_FROM_CLOSE 0x2

WINBASEAPI WINBOOL WINAPI CloseHandle(HANDLE hObject);
WINBASEAPI WINBOOL WINAPI DuplicateHandle(HANDLE hSourceProcessHandle, HANDLE hSourceHandle, HANDLE hTargetProcessHandle, LPHANDLE lpTargetHandle, DWORD dwDesiredAccess, WINBOOL bInheritHandle, DWORD dwOptions);
WINBASEAPI WINBOOL WINAPI CompareObjectHandles(HANDLE hFirstObjectHandle, HANDLE hSecondObjectHandle);
WINBASEAPI WINBOOL WINAPI GetHandleInformation(HANDLE hObject, LPDWORD lpdwFlags);
WINBASEAPI WINBOOL WINAPI SetHandleInformation(HANDLE hObject, DWORD dwMask, DWORD dwFlags);


__DECL_END
#endif /* __CC__ */

#endif /* !_NT_HANDLEAPI_H */
