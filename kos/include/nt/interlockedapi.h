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
#ifndef _NT_INTERLOCKEDAPI_H
#define _NT_INTERLOCKEDAPI_H 1

#include "__stdinc.h"
/**/

#include "types.h"
/**/

#ifdef __CC__
__DECL_BEGIN

#ifndef _SLIST_HEADER_
#define _SLIST_HEADER_
#if __SIZEOF_POINTER__ >= 8
typedef struct DECLSPEC_ALIGN(16) _SLIST_ENTRY {
	struct _SLIST_ENTRY *Next;
} SLIST_ENTRY, *PSLIST_ENTRY;

typedef union DECLSPEC_ALIGN(16) _SLIST_HEADER {
	__C89_NAMELESS struct {
		ULONGLONG Alignment;
		ULONGLONG Region;
	} DUMMYSTRUCTNAME;
	struct {
		ULONGLONG Depth : 16;
		ULONGLONG Sequence : 9;
		ULONGLONG NextEntry : 39;
		ULONGLONG HeaderType : 1;
		ULONGLONG Init : 1;
		ULONGLONG Reserved : 59;
		ULONGLONG Region : 3;
	} Header8;
	struct {
		ULONGLONG Depth : 16;
		ULONGLONG Sequence : 48;
		ULONGLONG HeaderType : 1;
		ULONGLONG Reserved : 3;
		ULONGLONG NextEntry : 60;
	} HeaderX64;
} SLIST_HEADER, *PSLIST_HEADER;
#else /* __SIZEOF_POINTER__ >= 8 */
typedef struct _SINGLE_LIST_ENTRY SLIST_ENTRY, *PSLIST_ENTRY;
typedef union _SLIST_HEADER {
	ULONGLONG Alignment;
	__C89_NAMELESS struct {
		SLIST_ENTRY Next;
		WORD Depth;
		WORD Sequence;
	} DUMMYSTRUCTNAME;
} SLIST_HEADER, *PSLIST_HEADER;
#endif /* __SIZEOF_POINTER__ < 8 */
#endif /* _SLIST_HEADER_ */

WINBASEAPI VOID WINAPI InitializeSListHead(PSLIST_HEADER ListHead);
WINBASEAPI PSLIST_ENTRY WINAPI InterlockedPopEntrySList(PSLIST_HEADER ListHead);
WINBASEAPI PSLIST_ENTRY WINAPI InterlockedPushEntrySList(PSLIST_HEADER ListHead, PSLIST_ENTRY ListEntry);
WINBASEAPI PSLIST_ENTRY WINAPI InterlockedFlushSList(PSLIST_HEADER ListHead);
WINBASEAPI USHORT WINAPI QueryDepthSList(PSLIST_HEADER ListHead);
WINBASEAPI PSLIST_ENTRY WINAPI InterlockedPushListSListEx(PSLIST_HEADER ListHead, PSLIST_ENTRY List, PSLIST_ENTRY ListEnd, ULONG Count);
#define InterlockedPushListSList InterlockedPushListSListEx

__DECL_END
#endif /* __CC__ */

#endif /* !_NT_INTERLOCKEDAPI_H */
