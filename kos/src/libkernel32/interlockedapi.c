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
#ifndef GUARD_LIBKERNEL32_INTERLOCKEDAPI_C
#define GUARD_LIBKERNEL32_INTERLOCKEDAPI_C 1

#include "api.h"
/**/

#include <nt/interlockedapi.h>

#include <syslog.h>
#include <string.h>

DECL_BEGIN

/************************************************************************/
INTERN VOID WINAPI
libk32_InitializeSListHead(PSLIST_HEADER ListHead) {
	bzero(ListHead, sizeof(*ListHead));
}

INTERN PSLIST_ENTRY WINAPI
libk32_InterlockedPopEntrySList(PSLIST_HEADER ListHead) {
	syslog(LOG_WARNING, "[k32] NotImplemented: InterlockedPopEntrySList(%p)\n", ListHead);
	return NULL;
}

INTERN PSLIST_ENTRY WINAPI
libk32_InterlockedPushEntrySList(PSLIST_HEADER ListHead, PSLIST_ENTRY ListEntry) {
	syslog(LOG_WARNING, "[k32] NotImplemented: InterlockedPushEntrySList(%p, %p)\n", ListHead, ListEntry);
	return NULL;
}

INTERN PSLIST_ENTRY WINAPI
libk32_InterlockedFlushSList(PSLIST_HEADER ListHead) {
	syslog(LOG_WARNING, "[k32] NotImplemented: InterlockedFlushSList(%p)\n", ListHead);
	return NULL;
}

INTERN USHORT WINAPI
libk32_QueryDepthSList(PSLIST_HEADER ListHead) {
	syslog(LOG_WARNING, "[k32] NotImplemented: QueryDepthSList(%p)\n", ListHead);
	return 0;
}

INTERN PSLIST_ENTRY WINAPI
libk32_InterlockedPushListSListEx(PSLIST_HEADER ListHead, PSLIST_ENTRY List,
                                  PSLIST_ENTRY ListEnd, ULONG Count) {
	syslog(LOG_WARNING, "[k32] NotImplemented: InterlockedPushListSListEx(%p, %p, %p, %u)\n",
	       ListHead, List, ListEnd, Count);
	return 0;
}

DEFINE_PUBLIC_ALIAS(InitializeSListHead, libk32_InitializeSListHead);
DEFINE_PUBLIC_ALIAS(InterlockedPopEntrySList, libk32_InterlockedPopEntrySList);
DEFINE_PUBLIC_ALIAS(InterlockedPushEntrySList, libk32_InterlockedPushEntrySList);
DEFINE_PUBLIC_ALIAS(InterlockedFlushSList, libk32_InterlockedFlushSList);
DEFINE_PUBLIC_ALIAS(QueryDepthSList, libk32_QueryDepthSList);
DEFINE_PUBLIC_ALIAS(InterlockedPushListSListEx, libk32_InterlockedPushListSListEx);
/************************************************************************/

DECL_END

#endif /* !GUARD_LIBKERNEL32_INTERLOCKEDAPI_C */
