/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _NT_TYPES_H
#define _NT_TYPES_H 1

#include "__stdinc.h"
/**/

#include <hybrid/__pointer.h>
#include <hybrid/limitcore.h>
#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

#ifndef _PVOID_DEFINED
#define _PVOID_DEFINED
typedef void *PVOID;
typedef __HYBRID_PTR64(void) PVOID64;
#endif /* !_PVOID_DEFINED */
#ifndef _PVOID32_DEFINED
#define _PVOID32_DEFINED
typedef __HYBRID_PTR32(void) PVOID32;
#endif /* !_PVOID32_DEFINED */

#ifndef DECLARE_HANDLE
#ifdef STRICT
#define DECLARE_HANDLE(name)  \
	typedef struct name##__ { \
		int unused;           \
	} * name
#else /* STRICT */
#define DECLARE_HANDLE(name) \
	typedef HANDLE name
#endif /* !STRICT */
typedef void *HANDLE, **PHANDLE;
#endif /* !DECLARE_HANDLE */

#ifndef _INT8_DEFINED
#define _INT8_DEFINED
typedef __INT8_TYPE__ INT8, *PINT8;
#endif /* !_INT8_DEFINED */
#ifndef _INT16_DEFINED
#define _INT16_DEFINED
typedef __INT16_TYPE__ INT16, *PINT16;
#endif /* !_INT16_DEFINED */
#ifndef _INT32_DEFINED
#define _INT32_DEFINED
typedef __INT32_TYPE__ INT32, *PINT32;
#endif /* !_INT32_DEFINED */
#ifndef _INT64_DEFINED
#define _INT64_DEFINED
typedef __INT64_TYPE__ INT64, *PINT64;
#endif /* !_INT64_DEFINED */
#ifndef _UINT8_DEFINED
#define _UINT8_DEFINED
typedef __UINT8_TYPE__ UINT8, *PUINT8;
#endif /* !_UINT8_DEFINED */
#ifndef _UINT16_DEFINED
#define _UINT16_DEFINED
typedef __UINT16_TYPE__ UINT16, *PUINT16;
#endif /* !_UINT16_DEFINED */
#ifndef _UINT32_DEFINED
#define _UINT32_DEFINED
typedef __UINT32_TYPE__ UINT32, *PUINT32;
#endif /* !_UINT32_DEFINED */
#ifndef _UINT64_DEFINED
#define _UINT64_DEFINED
typedef __UINT64_TYPE__ UINT64, *PUINT64;
#endif /* !_UINT64_DEFINED */
#ifndef _LONG32_DEFINED
#define _LONG32_DEFINED
typedef __INT32_TYPE__ LONG32, *PLONG32;
#endif /* !_LONG32_DEFINED */
#ifndef _ULONG32_DEFINED
#define _ULONG32_DEFINED
typedef __UINT32_TYPE__ ULONG32, *PULONG32;
#endif /* !_ULONG32_DEFINED */
#ifndef _DWORD32_DEFINED
#define _DWORD32_DEFINED
typedef __UINT32_TYPE__ DWORD32, *PDWORD32;
#endif /* !_DWORD32_DEFINED */

#ifndef _INT_PTR_DEFINED
#define _INT_PTR_DEFINED
typedef __INTPTR_TYPE__ INT_PTR, *PINT_PTR;
#endif /* !_INT_PTR_DEFINED */
#ifndef _UINT_PTR_DEFINED
#define _UINT_PTR_DEFINED
typedef __UINTPTR_TYPE__ UINT_PTR, *PUINT_PTR;
#endif /* !_UINT_PTR_DEFINED */
#ifndef _LONG_PTR_DEFINED
#define _LONG_PTR_DEFINED
typedef __LONGPTR_TYPE__ LONG_PTR, *PLONG_PTR;
#endif /* !_LONG_PTR_DEFINED */
#ifndef _ULONG_PTR_DEFINED
#define _ULONG_PTR_DEFINED
typedef __ULONGPTR_TYPE__ ULONG_PTR, *PULONG_PTR;
#endif /* !_ULONG_PTR_DEFINED */

#ifndef __NT_UHALF_PTR_DEFINED
#define __NT_UHALF_PTR_DEFINED
typedef __UINTPTR_HALF_TYPE__ UHALF_PTR, *PUHALF_PTR;
#endif /* !__NT_UHALF_PTR_DEFINED */
#ifndef __NT_HALF_PTR_DEFINED
#define __NT_HALF_PTR_DEFINED
typedef __INTPTR_HALF_TYPE__ HALF_PTR, *PHALF_PTR;
#endif /* !__NT_HALF_PTR_DEFINED */
#ifndef _SHANDLE_PTR_DEFINED
#define _SHANDLE_PTR_DEFINED
typedef __LONGPTR_TYPE__ SHANDLE_PTR;
#endif /* !_SHANDLE_PTR_DEFINED */
#ifndef _HANDLE_PTR_DEFINED
#define _HANDLE_PTR_DEFINED
typedef __ULONGPTR_TYPE__ HANDLE_PTR;
#endif /* !_HANDLE_PTR_DEFINED */

#ifndef __NT_SIZE_T_DEFINED
#define __NT_SIZE_T_DEFINED
typedef ULONG_PTR SIZE_T, *PSIZE_T;
#endif /* !__NT_SIZE_T_DEFINED */
#ifndef __NT_SSIZE_T_DEFINED
#define __NT_SSIZE_T_DEFINED
typedef LONG_PTR SSIZE_T, *PSSIZE_T;
#endif /* !__NT_SSIZE_T_DEFINED */
#ifndef _DWORD_PTR_DEFINED
#define _DWORD_PTR_DEFINED
typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;
#endif /* !_DWORD_PTR_DEFINED */
#ifndef _DWORD_DEFINED
#define _DWORD_DEFINED
typedef __ULONG32_TYPE__ DWORD;
#endif /* !_DWORD_DEFINED */
#ifndef _PDWORD_DEFINED
#define _PDWORD_DEFINED
typedef DWORD *PDWORD, *LPDWORD;
#endif /* !_PDWORD_DEFINED */
#ifndef _LONG64_DEFINED
#define _LONG64_DEFINED
typedef __LONG64_TYPE__ LONG64, *PLONG64;
#endif /* !_LONG64_DEFINED */
#ifndef _ULONG64_DEFINED
#define _ULONG64_DEFINED
typedef __ULONG64_TYPE__ ULONG64, *PULONG64;
#endif /* !_ULONG64_DEFINED */
#ifndef _DWORD64_DEFINED
#define _DWORD64_DEFINED
typedef __UINT64_TYPE__ DWORD64, *PDWORD64;
#endif /* !_DWORD64_DEFINED */


/* Upper-Case Versions of Some Standard C Types */
#ifndef VOID
#define VOID void
typedef char CHAR;
typedef __INT16_TYPE__ SHORT;
typedef __LONG32_TYPE__ LONG;
#endif /* !VOID */
#ifndef _INT_DEFINED
#define _INT_DEFINED 1
typedef int INT;
#endif /* !_INT_DEFINED */

#ifndef _INT_DEFINED
#define _INT_DEFINED 1
typedef __INT32_TYPE__ INT;
#endif /* !_INT_DEFINED */
#ifndef _PINT_DEFINED
#define _PINT_DEFINED
typedef INT *PINT, *LPINT;
#endif /* !_PINT_DEFINED */
#ifndef _BYTE_DEFINED
#define _BYTE_DEFINED
typedef __BYTE_TYPE__ BYTE, *PBYTE, *LPBYTE;
#endif /* !_BYTE_DEFINED */
#ifndef _WORD_DEFINED
#define _WORD_DEFINED
typedef __UINT16_TYPE__ WORD, *PWORD, *LPWORD;
#endif /* !_WORD_DEFINED */
#ifndef _UINT_DEFINED
#define _UINT_DEFINED
typedef __UINT32_TYPE__ UINT, *PUINT;
#endif /* !_UINT_DEFINED */
#ifndef _LPLONG_DEFINED
#define _LPLONG_DEFINED
typedef __LONG32_TYPE__ *LPLONG;
#endif /* !_LPLONG_DEFINED */
#ifndef _FLOAT_DEFINED
#define _FLOAT_DEFINED
typedef float FLOAT, *PFLOAT;
#endif /* !_FLOAT_DEFINED */
#ifndef _DOUBLE_DEFINED
#define _DOUBLE_DEFINED
typedef double DOUBLE;
#endif /* !_DOUBLE_DEFINED */
#ifndef _LPVOID_DEFINED
#define _LPVOID_DEFINED
typedef void *LPVOID;
#endif /* !_LPVOID_DEFINED */
#ifndef _LPCVOID_DEFINED
#define _LPCVOID_DEFINED
typedef CONST void *LPCVOID;
#endif /* !_LPCVOID_DEFINED */

/* Unsigned Types */
#ifndef BASETYPES
#define BASETYPES 1
typedef __ULONG32_TYPE__ ULONG, *PULONG;
typedef __UINT16_TYPE__ USHORT, *PUSHORT;
typedef __UINT8_TYPE__ UCHAR, *PUCHAR;
typedef char *PSZ;
#endif /* !BASETYPES */

#ifndef _PCUCHAR_DEFINED
#define _PCUCHAR_DEFINED
typedef CONST UCHAR *PCUCHAR;
#endif /* !_PCUCHAR_DEFINED */
#ifndef _PCUSHORT_DEFINED
#define _PCUSHORT_DEFINED
typedef CONST USHORT *PCUSHORT;
#endif /* !_PCUSHORT_DEFINED */
#ifndef _PCULONG_DEFINED
#define _PCULONG_DEFINED
typedef CONST ULONG *PCULONG;
#endif /* !_PCULONG_DEFINED */
#ifndef _LOGICAL_DEFINED
#define _LOGICAL_DEFINED
typedef ULONG LOGICAL;
#endif /* !_LOGICAL_DEFINED */
#ifndef _PLOGICAL_DEFINED
#define _PLOGICAL_DEFINED
typedef ULONG *PLOGICAL;
#endif /* !_PLOGICAL_DEFINED */
#ifndef _FCHAR_DEFINED
#define _FCHAR_DEFINED 1
typedef UCHAR FCHAR;
#endif /* !_FCHAR_DEFINED */
#ifndef _FSHORT_DEFINED
#define _FSHORT_DEFINED 1
typedef USHORT FSHORT;
#endif /* !_FSHORT_DEFINED */
#ifndef _FLONG_DEFINED
#define _FLONG_DEFINED 1
typedef ULONG FLONG;
#endif /* !_FLONG_DEFINED */
#ifndef _BOOLEAN_
#define _BOOLEAN_ 1
typedef UCHAR BOOLEAN, *PBOOLEAN;
#endif /* !_BOOLEAN_ */

/* Signed Types */
#ifndef _PSHORT_DEFINED
#define _PSHORT_DEFINED 1
typedef SHORT *PSHORT;
#endif /* !_PSHORT_DEFINED */
#ifndef _PLONG_DEFINED
#define _PLONG_DEFINED 1
typedef LONG *PLONG;
#endif /* !_PLONG_DEFINED */
#ifndef _NTSTATUS_DEFINED
#define _NTSTATUS_DEFINED
typedef LONG NTSTATUS, *PNTSTATUS;
#endif /* !_NTSTATUS_DEFINED */
#ifndef _SCHAR_DEFINED
#define _SCHAR_DEFINED
typedef __INT8_TYPE__ SCHAR, *PSCHAR;
#endif /* !_SCHAR_DEFINED */

#ifndef _DEF_WINBOOL_
#define _DEF_WINBOOL_ 1
typedef int WINBOOL;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("BOOL")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef BOOL
#if !defined(__OBJC__) && !defined(__OBJC_BOOL) && !defined(__objc_INCLUDE_GNU)
typedef WINBOOL BOOL;
#endif /* !__OBJC__ && !__OBJC_BOOL && !__objc_INCLUDE_GNU */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("BOOL")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
typedef WINBOOL *PBOOL;
typedef WINBOOL *LPBOOL;
#endif /* !_DEF_WINBOOL_ */

#ifndef _HRESULT_DEFINED
#define _HRESULT_DEFINED 1
typedef LONG HRESULT;
#endif /* !_HRESULT_DEFINED */

/* 64-bit types */
#ifndef _ULONGLONG_
#define _ULONGLONG_
typedef __INT64_TYPE__ LONGLONG, *PLONGLONG;
typedef __UINT64_TYPE__ ULONGLONG, *PULONGLONG;
#define MAXLONGLONG __INT64_MAX__
typedef LONGLONG USN; /* Update Sequence Number */
#endif /* !_ULONGLONG_ */

#ifndef _DWORDLONG_
#define _DWORDLONG_ 1
typedef ULONGLONG DWORDLONG, *PDWORDLONG;
#endif /* !_DWORDLONG_ */

/* ANSI (Multi-byte Character) types */
#ifndef _PCHAR_DEFINED
#define _PCHAR_DEFINED 1
typedef CHAR *PCHAR, *LPCH, *PCH;
#endif /* !_PCHAR_DEFINED */
#ifndef _LPCCH_DEFINED
#define _LPCCH_DEFINED 1
typedef CONST CHAR *LPCCH, *PCCH;
#endif /* !_LPCCH_DEFINED */
#ifndef _NPSTR_DEFINED
#define _NPSTR_DEFINED 1
typedef CHAR *NPSTR, *LPSTR, *PSTR;
#endif /* !_NPSTR_DEFINED */
#ifndef _PZPSTR_DEFINED
#define _PZPSTR_DEFINED 1
typedef PSTR *PZPSTR;
#endif /* !_PZPSTR_DEFINED */
#ifndef _PCZPSTR_DEFINED
#define _PCZPSTR_DEFINED 1
typedef CONST PSTR *PCZPSTR;
#endif /* !_PCZPSTR_DEFINED */
#ifndef _LPCSTR_DEFINED
#define _LPCSTR_DEFINED 1
typedef CONST CHAR *LPCSTR,*PCSTR;
#endif /* !_LPCSTR_DEFINED */
#ifndef _PZPCSTR_DEFINED
#define _PZPCSTR_DEFINED 1
typedef PCSTR *PZPCSTR;
#endif /* !_PZPCSTR_DEFINED */

/* Pointer to an Asciiz string */
#ifndef _PCSZ_DEFINED
#define _PCSZ_DEFINED
typedef CONST char *PCSZ;
#endif /* !_PCSZ_DEFINED */

/* UNICODE (Wide Character) types */
#ifndef __WCHAR_DEFINED
#define __WCHAR_DEFINED
typedef __CHAR16_TYPE__ WCHAR;
#endif /* !__WCHAR_DEFINED */
#ifndef _PWCHAR_DEFINED
#define _PWCHAR_DEFINED 1
typedef WCHAR *PWCHAR, *LPWCH, *PWCH;
#endif /* !_PWCHAR_DEFINED */
#ifndef _LPCWCH_DEFINED
#define _LPCWCH_DEFINED 1
typedef CONST WCHAR *LPCWCH, *PCWCH;
#endif /* !_LPCWCH_DEFINED */
#ifndef _NWPSTR_DEFINED
#define _NWPSTR_DEFINED 1
typedef WCHAR *NWPSTR, *LPWSTR, *PWSTR;
#endif /* !_NWPSTR_DEFINED */
#ifndef _PZPWSTR_DEFINED
#define _PZPWSTR_DEFINED 1
typedef PWSTR *PZPWSTR;
#endif /* !_PZPWSTR_DEFINED */
#ifndef _PCZPWSTR_DEFINED
#define _PCZPWSTR_DEFINED 1
typedef CONST PWSTR *PCZPWSTR;
#endif /* !_PCZPWSTR_DEFINED */
#ifndef _LPUWSTR_DEFINED
#define _LPUWSTR_DEFINED 1
typedef WCHAR UNALIGNED *LPUWSTR,*PUWSTR;
#endif /* !_LPUWSTR_DEFINED */
#ifndef _LPCWSTR_DEFINED
#define _LPCWSTR_DEFINED 1
typedef CONST WCHAR *LPCWSTR,*PCWSTR;
#endif /* !_LPCWSTR_DEFINED */
#ifndef _PZPCWSTR_DEFINED
#define _PZPCWSTR_DEFINED 1
typedef PCWSTR *PZPCWSTR;
#endif /* !_PZPCWSTR_DEFINED */
#ifndef _LPCUWSTR_DEFINED
#define _LPCUWSTR_DEFINED 1
typedef CONST WCHAR UNALIGNED *LPCUWSTR,*PCUWSTR;
#endif /* !_LPCUWSTR_DEFINED */

/* Cardinal Data Types */
#ifndef _CCHAR_DEFINED
#define _CCHAR_DEFINED 1
typedef char CCHAR;
#endif /* !_CCHAR_DEFINED */
#ifndef _PCCHAR_DEFINED
#define _PCCHAR_DEFINED
typedef CCHAR *PCCHAR;
#endif /* !_PCCHAR_DEFINED */
#ifndef _CSHORT_DEFINED
#define _CSHORT_DEFINED
typedef short CSHORT, *PCSHORT;
#endif /* !_CSHORT_DEFINED */
#ifndef _CLONG_DEFINED
#define _CLONG_DEFINED
typedef ULONG CLONG, *PCLONG;
#endif /* !_CLONG_DEFINED */

/* NLS basics (Locale and Language Ids) */
#ifndef _LCID_DEFINED
#define _LCID_DEFINED 1
typedef DWORD LCID;
#endif /* !_LCID_DEFINED */
#ifndef _PLCID_DEFINED
#define _PLCID_DEFINED 1
typedef PULONG PLCID;
#endif /* !_PLCID_DEFINED */
#ifndef _LANGID_DEFINED
#define _LANGID_DEFINED 1
typedef USHORT LANGID;
#endif /* !_LANGID_DEFINED */

/* Large Integer Unions */
#ifndef __LARGE_INTEGER_DEFINED
#define __LARGE_INTEGER_DEFINED 1
#ifdef MIDL_PASS
typedef struct _LARGE_INTEGER
#else /* MIDL_PASS */
typedef union _LARGE_INTEGER
#endif /* !MIDL_PASS */
{
#ifndef MIDL_PASS
	struct {
		ULONG LowPart;
		LONG HighPart;
	} DUMMYSTRUCTNAME;
	struct {
		ULONG LowPart;
		LONG HighPart;
	} u;
#endif /* !MIDL_PASS */
	LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

#ifdef MIDL_PASS
typedef struct _ULARGE_INTEGER
#else /* MIDL_PASS */
typedef union _ULARGE_INTEGER
#endif /* !MIDL_PASS */
{
#ifndef MIDL_PASS
	struct {
		ULONG LowPart;
		ULONG HighPart;
	} DUMMYSTRUCTNAME;
	struct {
		ULONG LowPart;
		ULONG HighPart;
	} u;
#endif /* !MIDL_PASS */
	ULONGLONG QuadPart;
} ULARGE_INTEGER, *PULARGE_INTEGER;
#endif /* !__LARGE_INTEGER_DEFINED */

/* Doubly Linked Lists */
#ifndef __LIST_ENTRY_DEFINED
#define __LIST_ENTRY_DEFINED 1
typedef struct _LIST_ENTRY {
	struct _LIST_ENTRY *Flink;
	struct _LIST_ENTRY *Blink;
} LIST_ENTRY, *PLIST_ENTRY, *RESTRICTED_POINTER PRLIST_ENTRY;
typedef struct LIST_ENTRY32 {
	ULONG Flink;
	ULONG Blink;
} LIST_ENTRY32, *PLIST_ENTRY32;
typedef struct LIST_ENTRY64 {
	ULONGLONG Flink;
	ULONGLONG Blink;
} LIST_ENTRY64, *PLIST_ENTRY64;
typedef struct _SINGLE_LIST_ENTRY {
	struct _SINGLE_LIST_ENTRY *Next;
} SINGLE_LIST_ENTRY, *PSINGLE_LIST_ENTRY;
#endif /* !__LIST_ENTRY_DEFINED */

#ifndef _COORD_DEFINED
#define _COORD_DEFINED
typedef struct _COORD {
	SHORT X;
	SHORT Y;
} COORD, *PCOORD;
#endif /* !_COORD_DEFINED */

#ifndef _SMALL_RECT_DEFINED
#define _SMALL_RECT_DEFINED
typedef struct _SMALL_RECT {
	SHORT Left;
	SHORT Top;
	SHORT Right;
	SHORT Bottom;
} SMALL_RECT, *PSMALL_RECT;
#endif /* !_SMALL_RECT_DEFINED */

#ifndef _SECURITY_ATTRIBUTES_DEFINED
#define _SECURITY_ATTRIBUTES_DEFINED
typedef struct _SECURITY_ATTRIBUTES {
	DWORD nLength;
	LPVOID lpSecurityDescriptor;
	WINBOOL bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;
#endif /* !_SECURITY_ATTRIBUTES_DEFINED */

#ifndef _OVERLAPPED_DEFINED
#define _OVERLAPPED_DEFINED
typedef struct _OVERLAPPED {
	ULONG_PTR Internal;
	ULONG_PTR InternalHigh;
	__C89_NAMELESS union {
		struct {
			DWORD Offset;
			DWORD OffsetHigh;
		} DUMMYSTRUCTNAME;
		PVOID Pointer;
	} DUMMYUNIONNAME;
	HANDLE hEvent;
} OVERLAPPED, *LPOVERLAPPED;
#endif /* !_OVERLAPPED_DEFINED */

typedef DWORD COLORREF;

typedef HANDLE *SPHANDLE;
typedef HANDLE *LPHANDLE;
typedef HANDLE HGLOBAL;
typedef HANDLE HLOCAL;
typedef HANDLE GLOBALHANDLE;
typedef HANDLE LOCALHANDLE;
typedef __INTPTR_TYPE__ (WINAPI *FARPROC)();
typedef __INTPTR_TYPE__ (WINAPI *NEARPROC)();
typedef __INTPTR_TYPE__ (WINAPI *PROC)();

#define __NT_VA_LIST void *

__DECL_END
#endif /* __CC__ */

#endif /* !_NT_TYPES_H */
