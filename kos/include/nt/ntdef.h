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
#ifndef _NTDEF_
#define _NTDEF_

#include "__winstd.h"

/* Dependencies */
#include <ctype.h>
#include "basetsd.h"
#include "excpt.h"
#include "sdkddkver.h"

// FIXME: Shouldn't be included!
#include <stdarg.h>
#include <string.h>

/* Pseudo Modifiers for Input Parameters */

#ifndef IN
#define IN
#endif /* !IN */
#ifndef OUT
#define OUT
#endif /* !OUT */
#ifndef OPTIONAL
#define OPTIONAL
#endif /* !OPTIONAL */
#ifndef NOTHING
#define NOTHING
#endif /* !NOTHING */
#ifndef CRITICAL
#define CRITICAL
#endif /* !CRITICAL */
#ifndef FAR
#define FAR
#endif /* !FAR */
#ifndef ANYSIZE_ARRAY
#define ANYSIZE_ARRAY 1
#endif /* !ANYSIZE_ARRAY */
#ifndef CONST
#define CONST const
#endif /* !CONST */
#ifndef FALSE
#define FALSE 0
#endif /* !FALSE */
#ifndef TRUE
#define TRUE 1
#endif /* !TRUE */
#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */
#ifndef NULL64
#ifdef __cplusplus
#define NULL64 0LL
#else /* __cplusplus */
#define NULL64 ((void *POINTER_64)0)
#endif /* !__cplusplus */
#endif /* NULL64 */

#define ARGUMENT_PRESENT(ArgumentPointer) ((CHAR *)((ULONG_PTR)(ArgumentPointer)) != (CHAR *)NULL)

#ifndef CONTAINING_RECORD
#define CONTAINING_RECORD __COMPILER_CONTAINER_OF
#endif /* !CONTAINING_RECORD */

#ifndef FIELD_OFFSET
#define FIELD_OFFSET __builtin_offsetof
#endif /* !FIELD_OFFSET */

#ifndef FASTCALL
#define FASTCALL __ATTR_FASTCALL
#endif /* !FASTCALL */

#ifndef NTAPI
#define NTAPI __ATTR_STDCALL
#endif /* !NTAPI */

#ifndef DECLSPEC_ADDRSAFE
#if (defined(_MSC_VER) && (_MSC_VER >= 1200) && \
     (defined(_M_ALPHA) || defined(_M_AXP64)))
#define DECLSPEC_ADDRSAFE  __declspec(address_safe)
#else /* ... */
#define DECLSPEC_ADDRSAFE
#endif /* !... */
#endif /* !DECLSPEC_ADDRSAFE */

#ifndef NTSYSAPI
#ifndef _NTSYSTEM_
#define NTSYSAPI     DECLSPEC_IMPORT
#define NTSYSCALLAPI DECLSPEC_IMPORT
#else /* !_NTSYSTEM_ */
#define NTSYSAPI
#ifdef _NTDLLBUILD_
#define NTSYSCALLAPI
#else /* _NTDLLBUILD_ */
#define NTSYSCALLAPI DECLSPEC_ADDRSAFE
#endif /* !_NTDLLBUILD_ */
#endif /* _NTSYSTEM_ */
#endif /* !NTSYSAPI */

#ifndef NTAPI_INLINE
#ifndef _M_CEE_PURE
#define NTAPI_INLINE NTAPI
#else /* !_M_CEE_PURE */
#define NTAPI_INLINE
#endif /* _M_CEE_PURE */
#endif /* !NTAPI_INLINE */

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P)          {(P) = (P);}
#define UNREFERENCED_LOCAL_VARIABLE(V)     {(V) = (V);}
#define DBG_UNREFERENCED_PARAMETER(P)      (P)
#define DBG_UNREFERENCED_LOCAL_VARIABLE(V) (V)
#endif /* !UNREFERENCED_PARAMETER */

#ifndef NOMINMAX
#include <hybrid/__minmax.h>
#ifndef min
#define min __hybrid_min2
#endif /* !min */
#ifndef max
#define max __hybrid_max2
#endif /* !max */
#endif /* !NOMINMAX */

#ifdef __CC__
__DECL_BEGIN

#ifndef _PVOID_DEFINED
#define _PVOID_DEFINED 1
typedef void *PVOID;
typedef __POINTER64(void) PVOID64;
#endif /* !_PVOID_DEFINED */

#ifndef DECLARE_HANDLE
#ifdef STRICT
#define DECLARE_HANDLE(name)         \
	struct name##__ { int unused; }; \
	typedef struct name##__ *name
#else /* STRICT */
#define DECLARE_HANDLE(name) \
	typedef HANDLE name
#endif /* !STRICT */
typedef void *HANDLE;
typedef HANDLE *PHANDLE;
#endif /* !DECLARE_HANDLE */

/* Upper-Case Versions of Some Standard C Types */
#ifndef VOID
#define VOID void
typedef char CHAR;
typedef __INT16_TYPE__ SHORT;
typedef __LONG32_TYPE__ LONG;
#endif /* !VOID */

#ifndef MIDL_PASS
#ifndef _INT_DEFINED
#define _INT_DEFINED 1
typedef int INT;
#endif /* !_INT_DEFINED */
#endif /* !MIDL_PASS */

typedef double DOUBLE;

/* Unsigned Types */
#ifndef BASETYPES
#define BASETYPES 1
typedef __ULONG32_TYPE__ ULONG, *PULONG;
typedef __UINT16_TYPE__ USHORT, *PUSHORT;
typedef __UINT8_TYPE__ UCHAR, *PUCHAR;
typedef char *PSZ;
#endif /* !BASETYPES */

typedef CONST UCHAR *PCUCHAR;
typedef CONST USHORT *PCUSHORT;
typedef CONST ULONG *PCULONG;
typedef ULONG LOGICAL;
typedef ULONG *PLOGICAL;
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
typedef LONG NTSTATUS, *PNTSTATUS;
typedef __INT8_TYPE__ SCHAR, *PSCHAR;

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
typedef CONST char *PCSZ;

/* UNICODE (Wide Character) types */
#ifndef __WCHAR_DEFINED
#define __WCHAR_DEFINED
typedef __CHAR16_TYPE__ WCHAR;
#endif /* !__WCHAR_DEFINED */
#ifndef _PWCHAR_DEFINED
#define _PWCHAR_DEFINED 1
typedef WCHAR *PWCHAR, *LPWCH, *PWCH;
#endif /* !_PWCHAR_DEFINED */
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
typedef CCHAR *PCCHAR;
typedef short CSHORT, *PCSHORT;
typedef ULONG CLONG, *PCLONG;

/* NLS basics (Locale and Language Ids) */
#ifndef __DWORD_defined
#define __DWORD_defined
typedef __ULONG32_TYPE__ DWORD;
#endif /* !__DWORD_defined */
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

/* Used to store a non-float 8 byte aligned structure */
typedef struct _QUAD {
	union {
		__INT64_TYPE__ UseThisFieldToCopy;
		double DoNotUseThisField;
	} DUMMYUNIONNAME;
} QUAD, *PQUAD, UQUAD, *PUQUAD;

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

/* Physical Addresses are always treated as 64-bit wide */
typedef LARGE_INTEGER PHYSICAL_ADDRESS, *PPHYSICAL_ADDRESS;

/* Locally Unique Identifier */
#ifndef __LUID_DEFINED
#define __LUID_DEFINED 1
typedef struct _LUID {
	ULONG LowPart;
	LONG  HighPart;
} LUID, *PLUID;
#endif /* !__LUID_DEFINED */

/* Native API Return Value Macros */
#define NT_SUCCESS(Status)     (((NTSTATUS)(Status)) >= 0)
#define NT_INFORMATION(Status) ((((ULONG)(Status)) >> 30) == 1)
#define NT_WARNING(Status)     ((((ULONG)(Status)) >> 30) == 2)
#define NT_ERROR(Status)       ((((ULONG)(Status)) >> 30) == 3)

/* String Types */
typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
} UNICODE_STRING, *PUNICODE_STRING;
typedef UNICODE_STRING const *PCUNICODE_STRING;
#define UNICODE_NULL ((WCHAR)0)

typedef struct _CSTRING {
	USHORT Length;
	USHORT MaximumLength;
	CONST CHAR *Buffer;
} CSTRING, *PCSTRING;
#define ANSI_NULL ((CHAR)0)

typedef struct _STRING {
	USHORT Length;
	USHORT MaximumLength;
	PCHAR  Buffer;
} STRING, *PSTRING;

typedef STRING ANSI_STRING;
typedef PSTRING PANSI_STRING;
typedef STRING OEM_STRING;
typedef PSTRING POEM_STRING;
typedef CONST STRING *PCOEM_STRING;
typedef STRING CANSI_STRING;
typedef PSTRING PCANSI_STRING;

typedef struct _STRING32 {
	USHORT Length;
	USHORT MaximumLength;
	ULONG  Buffer;
} STRING32, *PSTRING32, UNICODE_STRING32, *PUNICODE_STRING32, ANSI_STRING32, *PANSI_STRING32;

typedef struct _STRING64 {
	USHORT Length;
	USHORT MaximumLength;
	ULONGLONG Buffer;
} STRING64, *PSTRING64, UNICODE_STRING64, *PUNICODE_STRING64, ANSI_STRING64, *PANSI_STRING64;

/* LangID and NLS */
#ifndef MAKELANGID
#define MAKELANGID(p, s) ((((USHORT)(s)) << 10) | (USHORT)(p))
#endif /* !MAKELANGID */
#ifndef PRIMARYLANGID
#define PRIMARYLANGID(lgid) ((USHORT)(lgid)&0x3ff)
#endif /* !PRIMARYLANGID */
#ifndef SUBLANGID
#define SUBLANGID(lgid) ((USHORT)(lgid) >> 10)
#endif /* !SUBLANGID */

#ifndef NLS_VALID_LOCALE_MASK
#define NLS_VALID_LOCALE_MASK 0x000fffff
#endif /* !NLS_VALID_LOCALE_MASK */

#ifndef MAKELCID
#define MAKELCID(lgid, srtid) ((ULONG)((((ULONG)((USHORT)(srtid))) << 16) | ((ULONG)((USHORT)(lgid)))))
#endif /* !MAKELCID */
#ifndef MAKESORTLCID
#define MAKESORTLCID(lgid, srtid, ver) \
	((ULONG)((MAKELCID(lgid, srtid)) | (((ULONG)((USHORT)(ver))) << 20)))
#endif /* !MAKESORTLCID */
#ifndef LANGIDFROMLCID
#define LANGIDFROMLCID(lcid) ((USHORT)(lcid))
#endif /* !LANGIDFROMLCID */
#ifndef SORTIDFROMLCID
#define SORTIDFROMLCID(lcid) ((USHORT)((((ULONG)(lcid)) >> 16) & 0xf))
#endif /* !SORTIDFROMLCID */
#ifndef SORTVERSIONFROMLCID
#define SORTVERSIONFROMLCID(lcid) ((USHORT)((((ULONG)(lcid)) >> 20) & 0xf))
#endif /* !SORTVERSIONFROMLCID */


/* Object Attributes */
typedef struct _OBJECT_ATTRIBUTES {
	ULONG           Length;
	HANDLE          RootDirectory;
	PUNICODE_STRING ObjectName;
	ULONG           Attributes;
	PVOID           SecurityDescriptor;
	PVOID           SecurityQualityOfService;
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;
typedef CONST OBJECT_ATTRIBUTES *PCOBJECT_ATTRIBUTES;

/* Values for the Attributes member */
#define OBJ_INHERIT             0x00000002
#define OBJ_PERMANENT           0x00000010
#define OBJ_EXCLUSIVE           0x00000020
#define OBJ_CASE_INSENSITIVE    0x00000040
#define OBJ_OPENIF              0x00000080
#define OBJ_OPENLINK            0x00000100
#define OBJ_KERNEL_HANDLE       0x00000200
#define OBJ_FORCE_ACCESS_CHECK  0x00000400
#define OBJ_VALID_ATTRIBUTES    0x000007F2

/* Helper Macro */
#define InitializeObjectAttributes(p, n, a, r, s)               \
	((p)->Length                   = sizeof(OBJECT_ATTRIBUTES), \
	 (p)->RootDirectory            = (r),                       \
	 (p)->Attributes               = (a),                       \
	 (p)->ObjectName               = (n),                       \
	 (p)->SecurityDescriptor       = (s),                       \
	 (p)->SecurityQualityOfService = NULL)

/* Product Types */
typedef enum _NT_PRODUCT_TYPE {
	NtProductWinNt = 1,
	NtProductLanManNt,
	NtProductServer
} NT_PRODUCT_TYPE, *PNT_PRODUCT_TYPE;

typedef enum _EVENT_TYPE {
	NotificationEvent,
	SynchronizationEvent
} EVENT_TYPE;

typedef enum _TIMER_TYPE {
	NotificationTimer,
	SynchronizationTimer
} TIMER_TYPE;

typedef enum _WAIT_TYPE {
	WaitAll,
	WaitAny
} WAIT_TYPE;

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
typedef struct _PROCESSOR_NUMBER {
	USHORT Group;
	UCHAR Number;
	UCHAR Reserved;
} PROCESSOR_NUMBER, *PPROCESSOR_NUMBER;

struct _CONTEXT;
struct _EXCEPTION_RECORD;
typedef EXCEPTION_DISPOSITION
(NTAPI *PEXCEPTION_ROUTINE)(struct _EXCEPTION_RECORD *ExceptionRecord,
                            PVOID EstablisherFrame,
                            struct _CONTEXT *ContextRecord,
                            PVOID DispatcherContext);

typedef struct _GROUP_AFFINITY {
	KAFFINITY Mask;
	USHORT    Group;
	USHORT    Reserved[3];
} GROUP_AFFINITY, *PGROUP_AFFINITY;

__DECL_END
#endif /* __CC__ */

/* Helper Macros */
#ifndef RTL_CONSTANT_STRING
#define RTL_CONSTANT_STRING(s) { sizeof(s)-sizeof((s)[0]), sizeof(s), s }
#endif /* !RTL_CONSTANT_STRING */
#ifndef RTL_FIELD_SIZE
#define RTL_FIELD_SIZE(type, field) (sizeof(((type *)0)->field))
#endif /* !RTL_FIELD_SIZE */
#ifndef RTL_NUMBER_OF_V1
#define RTL_NUMBER_OF_V1(A) (sizeof(A) / sizeof((A)[0]))
#endif /* !RTL_NUMBER_OF_V1 */
#ifndef RTL_NUMBER_OF_V2
#define RTL_NUMBER_OF_V2(A) RTL_NUMBER_OF_V1(A)
#endif /* !RTL_NUMBER_OF_V2 */
#ifndef RTL_NUMBER_OF
#ifdef ENABLE_RTL_NUMBER_OF_V2
#define RTL_NUMBER_OF(A) RTL_NUMBER_OF_V2(A)
#else /* ENABLE_RTL_NUMBER_OF_V2 */
#define RTL_NUMBER_OF(A) RTL_NUMBER_OF_V1(A)
#endif /* !ENABLE_RTL_NUMBER_OF_V2 */
#endif /* !RTL_NUMBER_OF */
#ifndef ARRAYSIZE
#define ARRAYSIZE(A) RTL_NUMBER_OF_V2(A)
#endif /* !ARRAYSIZE */

/* Type Limits */
#ifndef MINCHAR
#define MINCHAR 0x80
#endif /* !MINCHAR */
#ifndef MAXCHAR
#define MAXCHAR 0x7f
#endif /* !MAXCHAR */
#ifndef MINSHORT
#define MINSHORT 0x8000
#endif /* !MINSHORT */
#ifndef MAXSHORT
#define MAXSHORT 0x7fff
#endif /* !MAXSHORT */
#ifndef MINLONG
#define MINLONG 0x80000000
#endif /* !MINLONG */
#ifndef MAXLONG
#define MAXLONG 0x7fffffff
#endif /* !MAXLONG */
#ifndef MAXUCHAR
#define MAXUCHAR 0xff
#endif /* !MAXUCHAR */
#ifndef MAXUSHORT
#define MAXUSHORT 0xffff
#endif /* !MAXUSHORT */
#ifndef MAXULONG
#define MAXULONG 0xffffffff
#endif /* !MAXULONG */
#ifndef MAXLONGLONG
#define MAXLONGLONG 0x7fffffffffffffffLL
#endif /* !MAXLONGLONG */

/* Multiplication and Shift Operations */
#ifndef Int32x32To64
#define Int32x32To64(a, b) ((LONGLONG)(a) * (LONGLONG)(b))
#endif /* !Int32x32To64 */
#ifndef UInt32x32To64
#define UInt32x32To64(a, b) ((ULONGLONG)(a) * (ULONGLONG)(b))
#endif /* !UInt32x32To64 */
#ifndef Int64ShllMod32
#define Int64ShllMod32(a, b) ((ULONGLONG)(a) << (b))
#endif /* !Int64ShllMod32 */
#ifndef Int64ShraMod32
#define Int64ShraMod32(a, b) ((LONGLONG)(a) >> (b))
#endif /* !Int64ShraMod32 */
#ifndef Int64ShrlMod32
#define Int64ShrlMod32(a, b) ((ULONGLONG)(a) >> (b))
#endif /* !Int64ShrlMod32 */

#define VER_WORKSTATION_NT                  0x40000000
#define VER_SERVER_NT                       0x80000000
#define VER_SUITE_SMALLBUSINESS             0x00000001
#define VER_SUITE_ENTERPRISE                0x00000002
#define VER_SUITE_BACKOFFICE                0x00000004
#define VER_SUITE_COMMUNICATIONS            0x00000008
#define VER_SUITE_TERMINAL                  0x00000010
#define VER_SUITE_SMALLBUSINESS_RESTRICTED  0x00000020
#define VER_SUITE_EMBEDDEDNT                0x00000040
#define VER_SUITE_DATACENTER                0x00000080
#define VER_SUITE_SINGLEUSERTS              0x00000100
#define VER_SUITE_PERSONAL                  0x00000200
#define VER_SUITE_BLADE                     0x00000400
#define VER_SUITE_EMBEDDED_RESTRICTED       0x00000800
#define VER_SUITE_SECURITY_APPLIANCE        0x00001000
#define VER_SUITE_STORAGE_SERVER            0x00002000
#define VER_SUITE_COMPUTE_SERVER            0x00004000
#define VER_SUITE_WH_SERVER                 0x00008000

/*  Primary language IDs. */
#define LANG_NEUTRAL                              0x00
#define LANG_INVARIANT                            0x7f

#define LANG_AFRIKAANS                            0x36
#define LANG_ALBANIAN                             0x1c
#define LANG_ALSATIAN                             0x84
#define LANG_AMHARIC                              0x5e
#define LANG_ARABIC                               0x01
#define LANG_ARMENIAN                             0x2b
#define LANG_ASSAMESE                             0x4d
#define LANG_AZERI                                0x2c
#define LANG_BASHKIR                              0x6d
#define LANG_BASQUE                               0x2d
#define LANG_BELARUSIAN                           0x23
#define LANG_BENGALI                              0x45
#define LANG_BRETON                               0x7e
#define LANG_BOSNIAN                              0x1a
#define LANG_BOSNIAN_NEUTRAL                    0x781a
#define LANG_BULGARIAN                            0x02
#define LANG_CATALAN                              0x03
#define LANG_CHINESE                              0x04
#define LANG_CHINESE_SIMPLIFIED                   0x04
#define LANG_CHINESE_TRADITIONAL                0x7c04
#define LANG_CORSICAN                             0x83
#define LANG_CROATIAN                             0x1a
#define LANG_CZECH                                0x05
#define LANG_DANISH                               0x06
#define LANG_DARI                                 0x8c
#define LANG_DIVEHI                               0x65
#define LANG_DUTCH                                0x13
#define LANG_ENGLISH                              0x09
#define LANG_ESTONIAN                             0x25
#define LANG_FAEROESE                             0x38
#define LANG_FARSI                                0x29
#define LANG_FILIPINO                             0x64
#define LANG_FINNISH                              0x0b
#define LANG_FRENCH                               0x0c
#define LANG_FRISIAN                              0x62
#define LANG_GALICIAN                             0x56
#define LANG_GEORGIAN                             0x37
#define LANG_GERMAN                               0x07
#define LANG_GREEK                                0x08
#define LANG_GREENLANDIC                          0x6f
#define LANG_GUJARATI                             0x47
#define LANG_HAUSA                                0x68
#define LANG_HEBREW                               0x0d
#define LANG_HINDI                                0x39
#define LANG_HUNGARIAN                            0x0e
#define LANG_ICELANDIC                            0x0f
#define LANG_IGBO                                 0x70
#define LANG_INDONESIAN                           0x21
#define LANG_INUKTITUT                            0x5d
#define LANG_IRISH                                0x3c
#define LANG_ITALIAN                              0x10
#define LANG_JAPANESE                             0x11
#define LANG_KANNADA                              0x4b
#define LANG_KASHMIRI                             0x60
#define LANG_KAZAK                                0x3f
#define LANG_KHMER                                0x53
#define LANG_KICHE                                0x86
#define LANG_KINYARWANDA                          0x87
#define LANG_KONKANI                              0x57
#define LANG_KOREAN                               0x12
#define LANG_KYRGYZ                               0x40
#define LANG_LAO                                  0x54
#define LANG_LATVIAN                              0x26
#define LANG_LITHUANIAN                           0x27
#define LANG_LOWER_SORBIAN                        0x2e
#define LANG_LUXEMBOURGISH                        0x6e
#define LANG_MACEDONIAN                           0x2f
#define LANG_MALAY                                0x3e
#define LANG_MALAYALAM                            0x4c
#define LANG_MALTESE                              0x3a
#define LANG_MANIPURI                             0x58
#define LANG_MAORI                                0x81
#define LANG_MAPUDUNGUN                           0x7a
#define LANG_MARATHI                              0x4e
#define LANG_MOHAWK                               0x7c
#define LANG_MONGOLIAN                            0x50
#define LANG_NEPALI                               0x61
#define LANG_NORWEGIAN                            0x14
#define LANG_OCCITAN                              0x82
#define LANG_ORIYA                                0x48
#define LANG_PASHTO                               0x63
#define LANG_PERSIAN                              0x29
#define LANG_POLISH                               0x15
#define LANG_PORTUGUESE                           0x16
#define LANG_PUNJABI                              0x46
#define LANG_QUECHUA                              0x6b
#define LANG_ROMANIAN                             0x18
#define LANG_ROMANSH                              0x17
#define LANG_RUSSIAN                              0x19
#define LANG_SAMI                                 0x3b
#define LANG_SANSKRIT                             0x4f
#define LANG_SERBIAN                              0x1a
#define LANG_SERBIAN_NEUTRAL                    0x7c1a
#define LANG_SINDHI                               0x59
#define LANG_SINHALESE                            0x5b
#define LANG_SLOVAK                               0x1b
#define LANG_SLOVENIAN                            0x24
#define LANG_SOTHO                                0x6c
#define LANG_SPANISH                              0x0a
#define LANG_SWAHILI                              0x41
#define LANG_SWEDISH                              0x1d
#define LANG_SYRIAC                               0x5a
#define LANG_TAJIK                                0x28
#define LANG_TAMAZIGHT                            0x5f
#define LANG_TAMIL                                0x49
#define LANG_TATAR                                0x44
#define LANG_TELUGU                               0x4a
#define LANG_THAI                                 0x1e
#define LANG_TIBETAN                              0x51
#define LANG_TIGRIGNA                             0x73
#define LANG_TSWANA                               0x32
#define LANG_TURKISH                              0x1f
#define LANG_TURKMEN                              0x42
#define LANG_UIGHUR                               0x80
#define LANG_UKRAINIAN                            0x22
#define LANG_UPPER_SORBIAN                        0x2e
#define LANG_URDU                                 0x20
#define LANG_UZBEK                                0x43
#define LANG_VIETNAMESE                           0x2a
#define LANG_WELSH                                0x52
#define LANG_WOLOF                                0x88
#define LANG_XHOSA                                0x34
#define LANG_YAKUT                                0x85
#define LANG_YI                                   0x78
#define LANG_YORUBA                               0x6a
#define LANG_ZULU                                 0x35

#endif /* !_NTDEF_ */
