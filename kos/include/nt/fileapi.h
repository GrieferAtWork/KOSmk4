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
#ifndef _NT_FILEAPI_H
#define _NT_FILEAPI_H 1

#include "__stdinc.h"
/**/

#include "types.h"
/**/

#ifdef __CC__
__DECL_BEGIN

#ifndef MAX_PATH
#define MAX_PATH 260
#endif /* !MAX_PATH */

#ifndef ERROR_NO_MORE_FILES
#define ERROR_NO_MORE_FILES 18
#endif /* !ERROR_NO_MORE_FILES */
#ifndef ERROR_FILE_NOT_FOUND
#define ERROR_FILE_NOT_FOUND 2
#endif /* !ERROR_FILE_NOT_FOUND */

#define GENERIC_READ    0x80000000
#define GENERIC_WRITE   0x40000000
#define GENERIC_EXECUTE 0x20000000
#define GENERIC_ALL     0x10000000

#define FILE_SHARE_READ        0x00000001
#define FILE_SHARE_WRITE       0x00000002
#define FILE_SHARE_DELETE      0x00000004
#define FILE_SHARE_VALID_FLAGS 0x00000007

#define FILE_ATTRIBUTE_READONLY            0x00000001
#define FILE_ATTRIBUTE_HIDDEN              0x00000002
#define FILE_ATTRIBUTE_SYSTEM              0x00000004
#define FILE_ATTRIBUTE_DIRECTORY           0x00000010
#define FILE_ATTRIBUTE_ARCHIVE             0x00000020
#define FILE_ATTRIBUTE_DEVICE              0x00000040
#define FILE_ATTRIBUTE_NORMAL              0x00000080
#define FILE_ATTRIBUTE_TEMPORARY           0x00000100
#define FILE_ATTRIBUTE_SPARSE_FILE         0x00000200
#define FILE_ATTRIBUTE_REPARSE_POINT       0x00000400
#define FILE_ATTRIBUTE_COMPRESSED          0x00000800
#define FILE_ATTRIBUTE_OFFLINE             0x00001000
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED 0x00002000
#define FILE_ATTRIBUTE_ENCRYPTED           0x00004000
#define FILE_ATTRIBUTE_VIRTUAL             0x00010000
#define FILE_FLAG_OPEN_REQUIRING_OPLOCK    0x00040000
#define FILE_FLAG_FIRST_PIPE_INSTANCE      0x00080000
#define FILE_FLAG_OPEN_NO_RECALL           0x00100000
#define FILE_FLAG_OPEN_REPARSE_POINT       0x00200000
#define FILE_FLAG_SESSION_AWARE            0x00800000
#define FILE_FLAG_POSIX_SEMANTICS          0x01000000
#define FILE_FLAG_BACKUP_SEMANTICS         0x02000000
#define FILE_FLAG_DELETE_ON_CLOSE          0x04000000
#define FILE_FLAG_SEQUENTIAL_SCAN          0x08000000
#define FILE_FLAG_RANDOM_ACCESS            0x10000000
#define FILE_FLAG_NO_BUFFERING             0x20000000
#define FILE_FLAG_OVERLAPPED               0x40000000
#define FILE_FLAG_WRITE_THROUGH            0x80000000

#define FILE_TYPE_UNKNOWN 0x0
#define FILE_TYPE_DISK    0x1
#define FILE_TYPE_CHAR    0x2
#define FILE_TYPE_PIPE    0x3
#define FILE_TYPE_REMOTE  0x8000

/* Values for `dwCreationDisposition' */
#define CREATE_NEW        1
#define CREATE_ALWAYS     2
#define OPEN_EXISTING     3
#define OPEN_ALWAYS       4
#define TRUNCATE_EXISTING 5

#define INVALID_FILE_SIZE        ((DWORD)0xffffffff)
#define INVALID_SET_FILE_POINTER ((DWORD)-1)
#define INVALID_FILE_ATTRIBUTES  ((DWORD)-1)

#define FILE_BEGIN   0
#define FILE_CURRENT 1
#define FILE_END     2

#ifndef _FILETIME_
#define _FILETIME_
typedef struct _FILETIME {
	DWORD dwLowDateTime;
	DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;
#endif /* !_FILETIME_ */




/************************************************************************/
/* DIRECTORY ENUMERATION                                                */
/************************************************************************/
typedef struct _WIN32_FIND_DATAA {
	DWORD dwFileAttributes;
	FILETIME ftCreationTime;
	FILETIME ftLastAccessTime;
	FILETIME ftLastWriteTime;
	DWORD nFileSizeHigh;
	DWORD nFileSizeLow;
	DWORD dwReserved0;
	DWORD dwReserved1;
	CHAR cFileName[MAX_PATH];
	CHAR cAlternateFileName[14];
#ifdef _MAC
	DWORD dwFileType;
	DWORD dwCreatorType;
	WORD wFinderFlags;
#endif /* _MAC */
} WIN32_FIND_DATAA, *PWIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;

typedef struct _WIN32_FIND_DATAW {
	DWORD dwFileAttributes;
	FILETIME ftCreationTime;
	FILETIME ftLastAccessTime;
	FILETIME ftLastWriteTime;
	DWORD nFileSizeHigh;
	DWORD nFileSizeLow;
	DWORD dwReserved0;
	DWORD dwReserved1;
	WCHAR cFileName[MAX_PATH];
	WCHAR cAlternateFileName[14];
#ifdef _MAC
	DWORD dwFileType;
	DWORD dwCreatorType;
	WORD wFinderFlags;
#endif /* _MAC */
} WIN32_FIND_DATAW, *PWIN32_FIND_DATAW, *LPWIN32_FIND_DATAW;

WINBASEAPI HANDLE WINAPI FindFirstFileA(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData);
WINBASEAPI HANDLE WINAPI FindFirstFileW(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData);
WINBASEAPI WINBOOL WINAPI FindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData);
WINBASEAPI WINBOOL WINAPI FindNextFileW(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData);
WINBASEAPI WINBOOL WINAPI FindClose(HANDLE hFindFile);
WINBASEAPI DWORD WINAPI GetLogicalDrives(VOID);
WINBASEAPI DWORD WINAPI GetLogicalDriveStringsA(DWORD nBufferLength, LPSTR lpBuffer);
WINBASEAPI DWORD WINAPI GetLogicalDriveStringsW(DWORD nBufferLength, LPWSTR lpBuffer);




/************************************************************************/
/* FILE MANAGEMENT                                                      */
/************************************************************************/
WINBASEAPI DWORD WINAPI GetFullPathNameA(LPCSTR lpFileName, DWORD nBufferLength, LPSTR lpBuffer, LPSTR *lpFilePart);
WINBASEAPI DWORD WINAPI GetFullPathNameW(LPCWSTR lpFileName, DWORD nBufferLength, LPWSTR lpBuffer, LPWSTR *lpFilePart);
WINBASEAPI WINBOOL WINAPI CreateDirectoryA(LPCSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
WINBASEAPI WINBOOL WINAPI CreateDirectoryW(LPCWSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
WINBASEAPI WINBOOL WINAPI DeleteFileA(LPCSTR lpFileName);
WINBASEAPI WINBOOL WINAPI DeleteFileW(LPCWSTR lpFileName);
WINBASEAPI WINBOOL WINAPI RemoveDirectoryA(LPCSTR lpPathName);
WINBASEAPI WINBOOL WINAPI RemoveDirectoryW(LPCWSTR lpPathName);




/************************************************************************/
/* FILE I/O                                                             */
/************************************************************************/
typedef struct _CREATEFILE2_EXTENDED_PARAMETERS {
	DWORD dwSize;
	DWORD dwFileAttributes;
	DWORD dwFileFlags;
	DWORD dwSecurityQosFlags;
	LPSECURITY_ATTRIBUTES lpSecurityAttributes;
	HANDLE hTemplateFile;
} CREATEFILE2_EXTENDED_PARAMETERS, *PCREATEFILE2_EXTENDED_PARAMETERS, *LPCREATEFILE2_EXTENDED_PARAMETERS;

typedef union _FILE_SEGMENT_ELEMENT {
	PVOID64 Buffer;
	ULONGLONG Alignment;
} FILE_SEGMENT_ELEMENT, *PFILE_SEGMENT_ELEMENT;

WINBASEAPI HANDLE WINAPI CreateFile2(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, DWORD dwCreationDisposition, LPCREATEFILE2_EXTENDED_PARAMETERS pCreateExParams);
WINBASEAPI HANDLE WINAPI CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
WINBASEAPI HANDLE WINAPI CreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
WINBASEAPI DWORD WINAPI SetFilePointer(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod);
WINBASEAPI WINBOOL WINAPI SetFilePointerEx(HANDLE hFile, LARGE_INTEGER liDistanceToMove, PLARGE_INTEGER lpNewFilePointer, DWORD dwMoveMethod);
WINBASEAPI WINBOOL WINAPI ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
WINBASEAPI WINBOOL WINAPI WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);
WINBASEAPI DWORD WINAPI GetFinalPathNameByHandleA(HANDLE hFile, LPSTR lpszFilePath, DWORD cchFilePath, DWORD dwFlags);
WINBASEAPI DWORD WINAPI GetFinalPathNameByHandleW(HANDLE hFile, LPWSTR lpszFilePath, DWORD cchFilePath, DWORD dwFlags);
WINBASEAPI WINBOOL WINAPI FlushFileBuffers(HANDLE hFile);
WINBASEAPI WINBOOL WINAPI SetEndOfFile(HANDLE hFile);







/************************************************************************/
/* FILE ATTRIBUTES                                                      */
/************************************************************************/
typedef struct _WIN32_FILE_ATTRIBUTE_DATA {
	DWORD dwFileAttributes;
	FILETIME ftCreationTime;
	FILETIME ftLastAccessTime;
	FILETIME ftLastWriteTime;
	DWORD nFileSizeHigh;
	DWORD nFileSizeLow;
} WIN32_FILE_ATTRIBUTE_DATA, *LPWIN32_FILE_ATTRIBUTE_DATA;

typedef enum _GET_FILEEX_INFO_LEVELS {
	GetFileExInfoStandard, /* WIN32_FILE_ATTRIBUTE_DATA */
	GetFileExMaxInfoLevel
} GET_FILEEX_INFO_LEVELS;

typedef struct _BY_HANDLE_FILE_INFORMATION {
	DWORD dwFileAttributes;
	FILETIME ftCreationTime;
	FILETIME ftLastAccessTime;
	FILETIME ftLastWriteTime;
	DWORD dwVolumeSerialNumber;
	DWORD nFileSizeHigh;
	DWORD nFileSizeLow;
	DWORD nNumberOfLinks;
	DWORD nFileIndexHigh;
	DWORD nFileIndexLow;
} BY_HANDLE_FILE_INFORMATION, *PBY_HANDLE_FILE_INFORMATION, *LPBY_HANDLE_FILE_INFORMATION;

WINBASEAPI DWORD WINAPI GetFileAttributesA(LPCSTR lpFileName);
WINBASEAPI DWORD WINAPI GetFileAttributesW(LPCWSTR lpFileName);
WINBASEAPI WINBOOL WINAPI GetFileAttributesExA(LPCSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, LPVOID lpFileInformation);
WINBASEAPI WINBOOL WINAPI GetFileAttributesExW(LPCWSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, LPVOID lpFileInformation);
WINBASEAPI WINBOOL WINAPI SetFileAttributesA(LPCSTR lpFileName, DWORD dwFileAttributes);
WINBASEAPI WINBOOL WINAPI SetFileAttributesW(LPCWSTR lpFileName, DWORD dwFileAttributes);
WINBASEAPI WINBOOL WINAPI GetFileInformationByHandle(HANDLE hFile, LPBY_HANDLE_FILE_INFORMATION lpFileInformation);
WINBASEAPI LONG WINAPI CompareFileTime(CONST FILETIME *lpFileTime1, CONST FILETIME *lpFileTime2);
WINBASEAPI DWORD WINAPI GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh);
WINBASEAPI WINBOOL WINAPI GetFileSizeEx(HANDLE hFile, PLARGE_INTEGER lpFileSize);
WINBASEAPI WINBOOL WINAPI GetFileTime(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime);
WINBASEAPI WINBOOL WINAPI SetFileTime(HANDLE hFile, CONST FILETIME *lpCreationTime, CONST FILETIME *lpLastAccessTime, CONST FILETIME *lpLastWriteTime);
WINBASEAPI DWORD WINAPI GetFileType(HANDLE hFile);
WINBASEAPI WINBOOL WINAPI FileTimeToLocalFileTime(CONST FILETIME *lpFileTime, LPFILETIME lpLocalFileTime);
WINBASEAPI WINBOOL WINAPI LocalFileTimeToFileTime(CONST FILETIME *lpLocalFileTime, LPFILETIME lpFileTime);





/************************************************************************/
/* UNICODE                                                              */
/************************************************************************/
__MINGW_TYPEDEF_AW(WIN32_FIND_DATA)
__MINGW_TYPEDEF_AW(PWIN32_FIND_DATA)
__MINGW_TYPEDEF_AW(LPWIN32_FIND_DATA)
#define FindFirstFile            __MINGW_NAME_AW(FindFirstFile)
#define FindNextFile             __MINGW_NAME_AW(FindNextFile)
#define GetLogicalDriveStrings   __MINGW_NAME_AW(GetLogicalDriveStrings)
#define GetFullPathName          __MINGW_NAME_AW(GetFullPathName)
#define CreateDirectory          __MINGW_NAME_AW(CreateDirectory)
#define DeleteFile               __MINGW_NAME_AW(DeleteFile)
#define RemoveDirectory          __MINGW_NAME_AW(RemoveDirectory)
#define CreateFile               __MINGW_NAME_AW(CreateFile)
#define GetFinalPathNameByHandle __MINGW_NAME_AW(GetFinalPathNameByHandle)
#define GetFileAttributes        __MINGW_NAME_AW(GetFileAttributes)
#define GetFileAttributesEx      __MINGW_NAME_AW(GetFileAttributesEx)
#define SetFileAttributes        __MINGW_NAME_AW(SetFileAttributes)

__DECL_END
#endif /* __CC__ */

#endif /* !_NT_FILEAPI_H */
