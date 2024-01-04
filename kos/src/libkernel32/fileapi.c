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
#ifndef GUARD_LIBKERNEL32_FILEAPI_C
#define GUARD_LIBKERNEL32_FILEAPI_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#define _UTF_SOURCE 1
#define _TIME64_SOURCE 1
#define _LARGEFILE64_SOURCE 1

#include "api.h"

#include <kos/types.h>
#include <nt/fileapi.h>
#include <nt/handleapi.h>
#include <sys/stat.h>
#include <sys/time.h>

#include <assert.h>
#include <direct.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>
#include <uchar.h>
#include <unistd.h>
#include <wchar.h>

DECL_BEGIN

INTERN struct timespec64 CC
libk32_FileTimeToTimeSpec(CONST FILETIME *ft) {
	struct timespec64 result;
	/* TODO */
	(void)ft;
	COMPILER_IMPURE();
	result.tv_sec  = 0;
	result.tv_nsec = 0;
	return result;
}

INTERN FILETIME CC
libk32_TimeSpecToFileTime(struct timespec64 const *ts) {
	FILETIME result;
	/* TODO */
	(void)ts;
	COMPILER_IMPURE();
	result.dwLowDateTime  = 0;
	result.dwHighDateTime = 0;
	return result;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) DWORD CC
libk32_FileAttributesFromStat(struct stat64 const *__restrict st) {
	DWORD result = 0;
	if (!(st->st_mode & 0222))
		result |= FILE_ATTRIBUTE_READONLY;
	if (S_ISDIR(st->st_mode))
		result |= FILE_ATTRIBUTE_DIRECTORY;
	if (S_ISDEV(st->st_mode))
		result |= FILE_ATTRIBUTE_DEVICE;
	if (S_ISLNK(st->st_mode))
		result |= FILE_ATTRIBUTE_REPARSE_POINT;
	if (result == 0)
		result = FILE_ATTRIBUTE_NORMAL;
	return result;
}





/************************************************************************/
/* DIRECTORY ENUMERATION                                                */
/************************************************************************/
struct dfind {
	DIR  *df_dir;   /* [1..1][owned] The underlying directory stream. */
	char *df_query; /* [1..1][owned] The wildcard-enabled query pattern. */
};

#define DFIND_INVALID ((struct dfind *)-1) /* INVALID_HANDLE_VALUE */
__LIBC WUNUSED struct dfind *LIBCCALL __find_open(char const *__restrict filename, oflag_t oflags);
__LIBC WUNUSED struct dfind *LIBCCALL DOS$__find_wopen(char16_t const *__restrict filename, oflag_t oflags);
__LIBC WUNUSED struct dirent *LIBCCALL __find_readdir(struct dfind *__restrict self);
__LIBC int LIBCCALL __find_close(struct dfind *__restrict self) ASMNAME("_findclose");

INTERN WINBOOL WINAPI
libk32_FindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData) {
	struct dirent *ent;
	struct stat64 st;
	TRACE("FindNextFileA(%p, %p)", hFindFile, lpFindFileData);
again_readdir:
	ent = __find_readdir((struct dfind *)hFindFile);
	if (!ent) {
		_nterrno = ERROR_NO_MORE_FILES;
		return FALSE;
	}
	if (fstatat64(dirfd(((struct dfind *)hFindFile)->df_dir),
	              ent->d_name, &st, AT_SYMLINK_NOFOLLOW) != 0)
		goto again_readdir;
	lpFindFileData->dwFileAttributes = libk32_FileAttributesFromStat(&st);
	lpFindFileData->ftCreationTime   = libk32_TimeSpecToFileTime(&st.st_btimespec64);
	lpFindFileData->ftLastAccessTime = libk32_TimeSpecToFileTime(&st.st_atimespec64);
	lpFindFileData->ftLastWriteTime  = libk32_TimeSpecToFileTime(&st.st_mtimespec64);
	lpFindFileData->nFileSizeHigh    = (DWORD)(st.st_size64 >> 32);
	lpFindFileData->nFileSizeLow     = (DWORD)(st.st_size64);
	lpFindFileData->dwReserved0      = 0;
	lpFindFileData->dwReserved1      = 0;
	*(CHAR *)mempcpy(lpFindFileData->cFileName, ent->d_name,
	                 strnlen(ent->d_name, MAX_PATH - 1),
	                 sizeof(CHAR)) = 0;
	lpFindFileData->cAlternateFileName[0] = 0;
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_FindNextFileW(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData) {
	struct dirent *ent;
	struct stat64 st;
	char16_t *wname;
	TRACE("FindNextFileW(%p, %p)", hFindFile, lpFindFileData);
again_readdir:
	ent = __find_readdir((struct dfind *)hFindFile);
	if (!ent) {
		_nterrno = ERROR_NO_MORE_FILES;
		return FALSE;
	}
	if (fstatat64(dirfd(((struct dfind *)hFindFile)->df_dir),
	              ent->d_name, &st, AT_SYMLINK_NOFOLLOW) != 0)
		goto again_readdir;
	lpFindFileData->dwFileAttributes = libk32_FileAttributesFromStat(&st);
	lpFindFileData->ftCreationTime   = libk32_TimeSpecToFileTime(&st.st_btimespec64);
	lpFindFileData->ftLastAccessTime = libk32_TimeSpecToFileTime(&st.st_atimespec64);
	lpFindFileData->ftLastWriteTime  = libk32_TimeSpecToFileTime(&st.st_mtimespec64);
	lpFindFileData->nFileSizeHigh    = (DWORD)(st.st_size64 >> 32);
	lpFindFileData->nFileSizeLow     = (DWORD)(st.st_size64);
	lpFindFileData->dwReserved0      = 0;
	lpFindFileData->dwReserved1      = 0;
	/* Convert name and copy to user-buffer. */
	wname = convert_mbstoc16(ent->d_name);
	if (!wname)
		return FALSE;
	*(WCHAR *)mempcpy(lpFindFileData->cFileName, wname,
	                  c16nlen(wname, MAX_PATH - 1),
	                  sizeof(WCHAR)) = 0;
	free(wname);
	lpFindFileData->cAlternateFileName[0] = 0;
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_FindClose(HANDLE hFindFile) {
	TRACE("FindClose(%p)", hFindFile);
	return __find_close((struct dfind *)hFindFile) == 0;
}


INTERN HANDLE WINAPI
libk32_FindFirstFileA(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData) {
	struct dfind *find;
	TRACE("FindFirstFileA(%q, %p)", lpFileName, lpFindFileData);
	find = __find_open(lpFileName, O_DOSPATH);
	if (find != DFIND_INVALID) {
		if (!libk32_FindNextFileA((HANDLE)find, lpFindFileData)) {
			if (_nterrno == ERROR_NO_MORE_FILES)
				_nterrno = ERROR_FILE_NOT_FOUND;
			libk32_FindClose((HANDLE)find);
			find = DFIND_INVALID;
		}
	}
	return (HANDLE)find;
}

INTERN HANDLE WINAPI
libk32_FindFirstFileW(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData) {
	struct dfind *find;
	TRACE("FindFirstFileW(%I16q, %p)", lpFileName, lpFindFileData);
	find = DOS$__find_wopen(lpFileName, O_DOSPATH);
	if (find != DFIND_INVALID) {
		if (!libk32_FindNextFileW((HANDLE)find, lpFindFileData)) {
			if (_nterrno == ERROR_NO_MORE_FILES)
				_nterrno = ERROR_FILE_NOT_FOUND;
			libk32_FindClose((HANDLE)find);
			find = DFIND_INVALID;
		}
	}
	return (HANDLE)find;
}

DEFINE_PUBLIC_ALIAS(FindFirstFileA, libk32_FindFirstFileA);
DEFINE_PUBLIC_ALIAS(FindFirstFileW, libk32_FindFirstFileW);
DEFINE_PUBLIC_ALIAS(FindNextFileA, libk32_FindNextFileA);
DEFINE_PUBLIC_ALIAS(FindNextFileW, libk32_FindNextFileW);
DEFINE_PUBLIC_ALIAS(FindClose, libk32_FindClose);
/************************************************************************/





/************************************************************************/
INTERN DWORD WINAPI
libk32_GetLogicalDrives(VOID) {
	TRACE("GetLogicalDrives()");
	return _getdrives();
}

#define MAX_LOGICAL_DRIVE_STRINGS (((('Z' - 'A') + 1) * 4) + 1)
INTERN DWORD WINAPI
libk32_GetLogicalDriveStringsA(DWORD nBufferLength, LPSTR lpBuffer) {
	char buf[MAX_LOGICAL_DRIVE_STRINGS], *iter = buf;
	unsigned char letter;
	DWORD result, mask;
	TRACE("GetLogicalDriveStringsA(%#x, %p)", nBufferLength, lpBuffer);
	mask = libk32_GetLogicalDrives();
	for (letter = 'A'; letter <= 'Z'; ++letter, mask >>= 1) {
		if (!(mask & 1))
			continue;
		*iter++ = letter;
		*iter++ = ':';
		*iter++ = '\\';
		*iter++ = '\0';
	}
	*iter++ = '\0';
	result = (DWORD)(iter - buf);
	if (nBufferLength >= result) {
		memcpy(lpBuffer, buf, result);
		--result;
	}
	return result;
}

INTERN DWORD WINAPI
libk32_GetLogicalDriveStringsW(DWORD nBufferLength, LPWSTR lpBuffer) {
	char buf[MAX_LOGICAL_DRIVE_STRINGS], *iter = buf;
	unsigned char letter;
	DWORD result, mask;
	TRACE("GetLogicalDriveStringsW(%#x, %p)", nBufferLength, lpBuffer);
	mask = libk32_GetLogicalDrives();
	for (letter = 'A'; letter <= 'Z'; ++letter, mask >>= 1) {
		if (!(mask & 1))
			continue;
		*iter++ = letter;
		*iter++ = ':';
		*iter++ = '\\';
		*iter++ = '\0';
	}
	*iter++ = '\0';
	result = (DWORD)(iter - buf);
	if (nBufferLength >= result) {
		DWORD i;
		for (i = 0; i < result; ++i)
			lpBuffer[i] = buf[i];
		--result;
	}
	return result;
}

DEFINE_PUBLIC_ALIAS(GetLogicalDrives, libk32_GetLogicalDrives);
DEFINE_PUBLIC_ALIAS(GetLogicalDriveStringsA, libk32_GetLogicalDriveStringsA);
DEFINE_PUBLIC_ALIAS(GetLogicalDriveStringsW, libk32_GetLogicalDriveStringsW);
/************************************************************************/




/************************************************************************/
/* FILE MANAGEMENT                                                      */
/************************************************************************/
__LIBC WUNUSED NONNULL((1)) char *LIBDCALL DOS$realpath(char const *filename, char *resolved);

INTERN DWORD WINAPI
libk32_GetFullPathNameA(LPCSTR lpFileName, DWORD nBufferLength,
                        LPSTR lpBuffer, LPSTR *lpFilePart) {
	DWORD len;
	char *rp;
	TRACE("GetFullPathNameA(%q, %#x, %p, %p)", lpFileName, nBufferLength, lpBuffer, lpFilePart);
	rp = DOS$realpath(lpFileName, NULL);
	if (!rp)
		return 0;
	len = (DWORD)(strlen(rp) + 1);
	if (nBufferLength >= len) {
		memcpy(lpBuffer, rp, len, sizeof(CHAR));
		if (lpFilePart)
			*lpFilePart = strrchrnul(lpBuffer, '\\') + 1;
		--len;
	}
	free(rp);
	return len;
}

INTERN DWORD WINAPI
libk32_GetFullPathNameW(LPCWSTR lpFileName, DWORD nBufferLength,
                        LPWSTR lpBuffer, LPWSTR *lpFilePart) {
	DWORD len;
	char *utf8_path, *rp;
	char16_t *wrp;
	TRACE("GetFullPathNameW(%I16q, %#x, %p, %p)", lpFileName, nBufferLength, lpBuffer, lpFilePart);
	utf8_path = convert_c16tombs(lpFileName);
	if (!utf8_path)
		return 0;
	rp = DOS$realpath(utf8_path, NULL);
	free(utf8_path);
	if (!rp)
		return 0;
	wrp = convert_mbstoc16(rp);
	free(rp);
	if (!wrp)
		return 0;
	len = (DWORD)(c16len(wrp) + 1);
	if (nBufferLength >= len) {
		memcpy(lpBuffer, wrp, len, sizeof(WCHAR));
		if (lpFilePart)
			*lpFilePart = c16rchrnul(lpBuffer, '\\') + 1;
		--len;
	}
	free(wrp);
	return len;
}

__LIBC NONNULL((1)) int LIBDCALL DOS$_mkdir(char const *path);
__LIBC NONNULL((1)) int LIBDCALL DOS$_wmkdir(char16_t const *path);
__LIBC NONNULL((1)) int LIBDCALL DOS$_unlink(char const *path);
__LIBC NONNULL((1)) int LIBDCALL DOS$_wunlink(char16_t const *path);
__LIBC NONNULL((1)) int LIBDCALL DOS$_rmdir(char const *path);
__LIBC NONNULL((1)) int LIBDCALL DOS$_wrmdir(char16_t const *path);

INTERN WINBOOL WINAPI
libk32_CreateDirectoryA(LPCSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes) {
	TRACE("CreateDirectoryA(%q, %p)", lpPathName, lpSecurityAttributes);
	(void)lpSecurityAttributes;
	return DOS$_mkdir(lpPathName) == 0;
}

INTERN WINBOOL WINAPI
libk32_CreateDirectoryW(LPCWSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes) {
	TRACE("CreateDirectoryW(%I16q, %p)", lpPathName, lpSecurityAttributes);
	(void)lpSecurityAttributes;
	return DOS$_wmkdir(lpPathName) == 0;
}

INTERN WINBOOL WINAPI
libk32_DeleteFileA(LPCSTR lpFileName) {
	TRACE("DeleteFileA(%q)", lpFileName);
	return DOS$_unlink(lpFileName) == 0;
}

INTERN WINBOOL WINAPI
libk32_DeleteFileW(LPCWSTR lpFileName) {
	TRACE("DeleteFileW(%I16q)", lpFileName);
	return DOS$_wunlink(lpFileName) == 0;
}

INTERN WINBOOL WINAPI
libk32_RemoveDirectoryA(LPCSTR lpPathName) {
	TRACE("RemoveDirectoryA(%q)", lpPathName);
	return DOS$_rmdir(lpPathName) == 0;
}

INTERN WINBOOL WINAPI
libk32_RemoveDirectoryW(LPCWSTR lpPathName) {
	TRACE("RemoveDirectoryW(%I16q)", lpPathName);
	return DOS$_wrmdir(lpPathName) == 0;
}

DEFINE_PUBLIC_ALIAS(GetFullPathNameA, libk32_GetFullPathNameA);
DEFINE_PUBLIC_ALIAS(GetFullPathNameW, libk32_GetFullPathNameW);
DEFINE_PUBLIC_ALIAS(CreateDirectoryA, libk32_CreateDirectoryA);
DEFINE_PUBLIC_ALIAS(CreateDirectoryW, libk32_CreateDirectoryW);
DEFINE_PUBLIC_ALIAS(DeleteFileA, libk32_DeleteFileA);
DEFINE_PUBLIC_ALIAS(DeleteFileW, libk32_DeleteFileW);
DEFINE_PUBLIC_ALIAS(RemoveDirectoryA, libk32_RemoveDirectoryA);
DEFINE_PUBLIC_ALIAS(RemoveDirectoryW, libk32_RemoveDirectoryW);
/************************************************************************/




/************************************************************************/
/* FILE I/O                                                             */
/************************************************************************/
INTERN HANDLE WINAPI
libk32_CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
                   LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
                   DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
	fd_t fd;
	oflag_t oflags = 0;
	mode_t mode    = 0644;
	TRACE("CreateFileA(%q, %#x, %#x, %p, %#x, %#x, %p)",
	      lpFileName, dwDesiredAccess, dwShareMode,
	      lpSecurityAttributes, dwCreationDisposition,
	      dwFlagsAndAttributes, hTemplateFile);
	(void)dwShareMode;
	(void)lpSecurityAttributes;
	(void)hTemplateFile;
	switch (dwCreationDisposition) {
	case CREATE_NEW:
		oflags = O_CREAT | O_EXCL | O_TRUNC;
		break;
	case CREATE_ALWAYS:
		oflags = O_CREAT | O_TRUNC;
		break;
	case OPEN_EXISTING:
		break;
	case OPEN_ALWAYS:
		oflags = O_CREAT;
		break;
	case TRUNCATE_EXISTING:
		oflags = O_TRUNC;
		break;
	default:
		errno = EINVAL;
		return INVALID_HANDLE_VALUE;
	}
	oflags |= O_DOSPATH;
	if (dwFlagsAndAttributes & FILE_ATTRIBUTE_READONLY)
		mode &= ~0222;
	if (dwFlagsAndAttributes & FILE_FLAG_OPEN_REPARSE_POINT)
		oflags |= O_PATH | O_NOFOLLOW;
	if (dwFlagsAndAttributes & FILE_FLAG_NO_BUFFERING)
		oflags |= O_DIRECT;
	if (dwFlagsAndAttributes & FILE_FLAG_WRITE_THROUGH)
		oflags |= O_DSYNC;
	if ((dwDesiredAccess & GENERIC_ALL) ||
	    ((dwDesiredAccess & (GENERIC_READ | GENERIC_WRITE)) == (GENERIC_READ | GENERIC_WRITE))) {
		oflags |= O_RDWR;
	} else if (dwDesiredAccess & GENERIC_WRITE) {
		oflags |= O_WRONLY;
	} else {
		oflags |= O_RDONLY;
	}

	/* XXX: `FILE_FLAG_POSIX_SEMANTICS' to turn off case-insensitive
	 *      (but keep  '\' for  '/', and  DOS drive  parsing  rules) */
	fd = open(lpFileName, oflags, mode);
	if (fd == -1)
		return INVALID_HANDLE_VALUE;
	return NTHANDLE_FROMFD(fd);
}

INTERN HANDLE WINAPI
libk32_CreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
                   LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
                   DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
	char *utf8;
	HANDLE result;
	TRACE("CreateFileW(%I16q, %#x, %#x, %p, %#x, %#x, %p)",
	      lpFileName, dwDesiredAccess, dwShareMode,
	      lpSecurityAttributes, dwCreationDisposition,
	      dwFlagsAndAttributes, hTemplateFile);
	utf8 = convert_c16tombs(lpFileName);
	if (!utf8)
		return INVALID_HANDLE_VALUE;
	result = libk32_CreateFileA(utf8, dwDesiredAccess, dwShareMode,
	                            lpSecurityAttributes, dwCreationDisposition,
	                            dwFlagsAndAttributes, hTemplateFile);
	free(utf8);
	return result;
}

INTERN HANDLE WINAPI
libk32_CreateFile2(LPCWSTR lpFileName, DWORD dwDesiredAccess,
                   DWORD dwShareMode, DWORD dwCreationDisposition,
                   LPCREATEFILE2_EXTENDED_PARAMETERS pCreateExParams) {
	HANDLE result;
	TRACE("CreateFile2(%I16q, %#x, %#x, %#x, %p)",
	      lpFileName, dwDesiredAccess, dwShareMode,
	      dwCreationDisposition, pCreateExParams);
	if (pCreateExParams && pCreateExParams->dwSize != sizeof(*pCreateExParams)) {
		errno = EINVAL;
		return INVALID_HANDLE_VALUE;
	}
	result = libk32_CreateFileW(lpFileName, dwDesiredAccess, dwShareMode,
	                            pCreateExParams ? pCreateExParams->lpSecurityAttributes : NULL,
	                            dwCreationDisposition,
	                            pCreateExParams ? (pCreateExParams->dwFileAttributes |
	                                               pCreateExParams->dwFileFlags)
	                                            : 0,
	                            pCreateExParams ? pCreateExParams->hTemplateFile : NULL);
	return result;
}


static_assert(FILE_BEGIN == SEEK_SET);
static_assert(FILE_CURRENT == SEEK_CUR);
static_assert(FILE_END == SEEK_END);
INTERN DWORD WINAPI
libk32_SetFilePointer(HANDLE hFile, LONG lDistanceToMove,
                      PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod) {
	off64_t newpos;
	TRACE("SetFilePointer(%p, %d, %p, %#x)",
	      hFile, lDistanceToMove,
	      lpDistanceToMoveHigh, dwMoveMethod);
	if (!NTHANDLE_ISFD(hFile)) {
		errno = EBADF;
		return INVALID_SET_FILE_POINTER;
	}
	if (lpDistanceToMoveHigh) {
		newpos = lseek(NTHANDLE_ASFD(hFile),
		               lDistanceToMove,
		               dwMoveMethod);
	} else {
		newpos = lseek64(NTHANDLE_ASFD(hFile),
		                 ((off64_t)*lpDistanceToMoveHigh << 32) |
		                 ((off64_t)lDistanceToMove),
		                 dwMoveMethod);
	}
	if (newpos == -1)
		return INVALID_SET_FILE_POINTER;
	if (lpDistanceToMoveHigh)
		*lpDistanceToMoveHigh = (DWORD)(newpos >> 32);
	return (DWORD)newpos;
}

INTERN WINBOOL WINAPI
libk32_SetFilePointerEx(HANDLE hFile, LARGE_INTEGER liDistanceToMove,
                        PLARGE_INTEGER lpNewFilePointer, DWORD dwMoveMethod) {
	off64_t newpos;
	TRACE("SetFilePointerEx(%p, %I64d, %p, %#x)",
	      hFile, liDistanceToMove.QuadPart,
	      lpNewFilePointer, dwMoveMethod);
	if (!NTHANDLE_ISFD(hFile)) {
		errno = EBADF;
		return FALSE;
	}
	newpos = lseek64(NTHANDLE_ASFD(hFile), liDistanceToMove.QuadPart, dwMoveMethod);
	if (newpos == -1)
		return FALSE;
	lpNewFilePointer->QuadPart = newpos;
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead,
                LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped) {
	ssize_t total;
	TRACE("ReadFile(%p, %p, %#x, %p, %p)",
	      hFile, lpBuffer, nNumberOfBytesToRead,
	      lpNumberOfBytesRead, lpOverlapped);
	if (!NTHANDLE_ISFD(hFile)) {
		errno = EBADF;
		return FALSE;
	}
	if (lpOverlapped) {
		total = pread64(NTHANDLE_ASFD(hFile), lpBuffer, nNumberOfBytesToRead,
		                ((uint64_t)lpOverlapped->OffsetHigh << 32) |
		                ((uint64_t)lpOverlapped->Offset));
	} else {
		total = read(NTHANDLE_ASFD(hFile), lpBuffer, nNumberOfBytesToRead);
	}
	if (total == -1)
		return FALSE;
	*lpNumberOfBytesRead = (DWORD)total;
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite,
                 LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped) {
	ssize_t total;
	TRACE("WriteFile(%p, %p, %#x, %p, %p)",
	      hFile, lpBuffer, nNumberOfBytesToWrite,
	      lpNumberOfBytesWritten, lpOverlapped);
	if (!NTHANDLE_ISFD(hFile)) {
		errno = EBADF;
		return FALSE;
	}
	if (lpOverlapped) {
		total = pwrite64(NTHANDLE_ASFD(hFile), lpBuffer, nNumberOfBytesToWrite,
		                ((uint64_t)lpOverlapped->OffsetHigh << 32) |
		                ((uint64_t)lpOverlapped->Offset));
	} else {
		total = write(NTHANDLE_ASFD(hFile), lpBuffer, nNumberOfBytesToWrite);
	}
	if (total == -1)
		return FALSE;
	*lpNumberOfBytesWritten = (DWORD)total;
	return TRUE;
}

__LIBC WUNUSED char *LIBDCALL DOS$frealpath4(fd_t fd, char *resolved, size_t buflen, atflag_t flags);

INTERN DWORD WINAPI
libk32_GetFinalPathNameByHandleA(HANDLE hFile, LPSTR lpszFilePath,
                                 DWORD cchFilePath, DWORD dwFlags) {
	char *path;
	DWORD len;
	TRACE("GetFinalPathNameByHandleA(%p, %p, %#x, %#x)",
	      hFile, lpszFilePath, cchFilePath, dwFlags);
	(void)dwFlags;
	if (!NTHANDLE_ISFD(hFile)) {
		errno = EBADF;
		return FALSE;
	}
	path = DOS$frealpath4(NTHANDLE_ASFD(hFile), NULL, 0, 0);
	if (!path)
		return FALSE;
	len = (DWORD)strlen(path) + 1;
	if (cchFilePath >= len)
		memcpy(lpszFilePath, path, len, sizeof(CHAR));
	free(path);
	return (DWORD)len;
}

INTERN DWORD WINAPI
libk32_GetFinalPathNameByHandleW(HANDLE hFile, LPWSTR lpszFilePath,
                                 DWORD cchFilePath, DWORD dwFlags) {
	char *path;
	char16_t *wpath;
	DWORD len;
	TRACE("GetFinalPathNameByHandleW(%p, %p, %#x, %#x)",
	      hFile, lpszFilePath, cchFilePath, dwFlags);
	(void)dwFlags;
	if (!NTHANDLE_ISFD(hFile)) {
		errno = EBADF;
		return FALSE;
	}
	path = DOS$frealpath4(NTHANDLE_ASFD(hFile), NULL, 0, 0);
	if (!path)
		return FALSE;
	wpath = convert_mbstoc16(path);
	free(path);
	len = (DWORD)c16len(wpath) + 1;
	if (cchFilePath >= len)
		memcpy(lpszFilePath, wpath, len, sizeof(WCHAR));
	free(wpath);
	return (DWORD)len;
}

INTERN WINBOOL WINAPI
libk32_FlushFileBuffers(HANDLE hFile) {
	TRACE("FlushFileBuffers(%p)", hFile);
	if (!NTHANDLE_ISFD(hFile)) {
		errno = EBADF;
		return FALSE;
	}
	return fdatasync(NTHANDLE_ASFD(hFile)) == 0;
}

INTERN WINBOOL WINAPI
libk32_SetEndOfFile(HANDLE hFile) {
	off64_t offset;
	TRACE("SetEndOfFile(%p)", hFile);
	if (!NTHANDLE_ISFD(hFile)) {
		errno = EBADF;
		return FALSE;
	}
	offset = lseek64(NTHANDLE_ASFD(hFile), 0, SEEK_CUR);
	if (offset == -1)
		return FALSE;
	return ftruncate64(NTHANDLE_ASFD(hFile), (pos64_t)offset);
}

DEFINE_PUBLIC_ALIAS(CreateFile2, libk32_CreateFile2);
DEFINE_PUBLIC_ALIAS(CreateFileA, libk32_CreateFileA);
DEFINE_PUBLIC_ALIAS(CreateFileW, libk32_CreateFileW);
DEFINE_PUBLIC_ALIAS(SetFilePointer, libk32_SetFilePointer);
DEFINE_PUBLIC_ALIAS(SetFilePointerEx, libk32_SetFilePointerEx);
DEFINE_PUBLIC_ALIAS(ReadFile, libk32_ReadFile);
DEFINE_PUBLIC_ALIAS(WriteFile, libk32_WriteFile);
DEFINE_PUBLIC_ALIAS(GetFinalPathNameByHandleA, libk32_GetFinalPathNameByHandleA);
DEFINE_PUBLIC_ALIAS(GetFinalPathNameByHandleW, libk32_GetFinalPathNameByHandleW);
DEFINE_PUBLIC_ALIAS(FlushFileBuffers, libk32_FlushFileBuffers);
DEFINE_PUBLIC_ALIAS(SetEndOfFile, libk32_SetEndOfFile);
/************************************************************************/








/************************************************************************/
/* FILE ATTRIBUTES                                                      */
/************************************************************************/
__LIBC NONNULL((2)) int LIBDCALL DOS$kstat64(char const *__restrict filename, struct stat64 *__restrict buf);
__LIBC NONNULL((2)) int LIBDCALL DOS$klstat64(char const *__restrict filename, struct stat64 *__restrict buf);

INTERN DWORD WINAPI
libk32_GetFileAttributesA(LPCSTR lpFileName) {
	struct stat64 st;
	TRACE("GetFileAttributesA(%q)", lpFileName);
	if (DOS$klstat64(lpFileName, &st) != 0)
		return INVALID_FILE_ATTRIBUTES;
	return libk32_FileAttributesFromStat(&st);
}

INTERN DWORD WINAPI
libk32_GetFileAttributesW(LPCWSTR lpFileName) {
	DWORD result;
	char *utf8;
	TRACE("GetFileAttributesW(%I16q)", lpFileName);
	utf8 = convert_c16tombs(lpFileName);
	if (!utf8)
		return INVALID_FILE_ATTRIBUTES;
	result = libk32_GetFileAttributesA(utf8);
	free(utf8);
	return result;
}

INTERN WINBOOL WINAPI
libk32_GetFileAttributesExA(LPCSTR lpFileName,
                            GET_FILEEX_INFO_LEVELS fInfoLevelId,
                            LPVOID lpFileInformation) {
	TRACE("GetFileAttributesExA(%q, %u, %p)",
	      lpFileName, fInfoLevelId, lpFileInformation);
	switch (fInfoLevelId) {

	case GetFileExInfoStandard: {
		struct stat64 st;
		LPWIN32_FILE_ATTRIBUTE_DATA info;
		info = (LPWIN32_FILE_ATTRIBUTE_DATA)lpFileInformation;
		if (DOS$klstat64(lpFileName, &st) != 0)
			return INVALID_FILE_ATTRIBUTES;
		info->dwFileAttributes     = libk32_FileAttributesFromStat(&st);
		info->ftCreationTime       = libk32_TimeSpecToFileTime(&st.st_btimespec64);
		info->ftLastAccessTime     = libk32_TimeSpecToFileTime(&st.st_atimespec64);
		info->ftLastWriteTime      = libk32_TimeSpecToFileTime(&st.st_mtimespec64);
		info->nFileSizeHigh        = (DWORD)(st.st_size64 >> 32);
		info->nFileSizeLow         = (DWORD)st.st_size64;
	}	break;

	default:
		errno = EINVAL;
		return FALSE;
	}
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_GetFileAttributesExW(LPCWSTR lpFileName,
                            GET_FILEEX_INFO_LEVELS fInfoLevelId,
                            LPVOID lpFileInformation) {
	WINBOOL result;
	char *utf8;
	TRACE("GetFileAttributesExW(%I16q, %u, %p)",
	      lpFileName, fInfoLevelId, lpFileInformation);
	utf8 = convert_c16tombs(lpFileName);
	if (!utf8)
		return INVALID_FILE_ATTRIBUTES;
	result = libk32_GetFileAttributesExA(utf8, fInfoLevelId, lpFileInformation);
	free(utf8);
	return result;
}

__LIBC NONNULL((1)) int LIBDCALL DOS$lchmod(char const *filename, mode_t mode);

INTERN WINBOOL WINAPI
libk32_SetFileAttributesA(LPCSTR lpFileName, DWORD dwFileAttributes) {
	struct stat64 st;
	mode_t newmode;
	TRACE("SetFileAttributesA(%q, %#x)",
	      lpFileName, dwFileAttributes);
	if (DOS$klstat64(lpFileName, &st) != 0)
		return FALSE;
	newmode = st.st_mode;
	if (dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
		newmode &= ~0222;
	} else {
		newmode |= 0222;
	}
	if (st.st_mode == newmode)
		return TRUE;
	return DOS$lchmod(lpFileName, newmode) == 0;
}

INTERN WINBOOL WINAPI
libk32_SetFileAttributesW(LPCWSTR lpFileName, DWORD dwFileAttributes) {
	WINBOOL result;
	char *utf8;
	TRACE("SetFileAttributesW(%I16q, %#x)",
	      lpFileName, dwFileAttributes);
	utf8 = convert_c16tombs(lpFileName);
	if (!utf8)
		return INVALID_FILE_ATTRIBUTES;
	result = libk32_SetFileAttributesA(utf8, dwFileAttributes);
	free(utf8);
	return result;
}

INTERN WINBOOL WINAPI
libk32_GetFileInformationByHandle(HANDLE hFile, LPBY_HANDLE_FILE_INFORMATION lpFileInformation) {
	struct stat64 st;
	TRACE("GetFileInformationByHandle(%p, %p)",
	      hFile, lpFileInformation);
	if (!NTHANDLE_ISFD(hFile)) {
		errno = EBADF;
		return FALSE;
	}
	if (fstat64(NTHANDLE_ASFD(hFile), &st) != 0)
		return FALSE;
	lpFileInformation->dwFileAttributes     = libk32_FileAttributesFromStat(&st);
	lpFileInformation->ftCreationTime       = libk32_TimeSpecToFileTime(&st.st_btimespec64);
	lpFileInformation->ftLastAccessTime     = libk32_TimeSpecToFileTime(&st.st_atimespec64);
	lpFileInformation->ftLastWriteTime      = libk32_TimeSpecToFileTime(&st.st_mtimespec64);
	lpFileInformation->dwVolumeSerialNumber = (DWORD)st.st_dev;
	lpFileInformation->nFileSizeHigh        = (DWORD)(st.st_size64 >> 32);
	lpFileInformation->nFileSizeLow         = (DWORD)st.st_size64;
	lpFileInformation->nNumberOfLinks       = (DWORD)st.st_nlink;
	lpFileInformation->nFileIndexHigh       = (DWORD)(st.st_ino >> 32);
	lpFileInformation->nFileIndexLow        = (DWORD)st.st_ino;
	return TRUE;
}

INTERN LONG WINAPI
libk32_CompareFileTime(CONST FILETIME *lpFileTime1,
                       CONST FILETIME *lpFileTime2) {
	uint64_t lhs, rhs;
	TRACE("CompareFileTime(%p, %p)", lpFileTime1, lpFileTime2);
	lhs = ((uint64_t)lpFileTime1->dwLowDateTime | (uint64_t)lpFileTime1->dwHighDateTime << 32);
	rhs = ((uint64_t)lpFileTime2->dwLowDateTime | (uint64_t)lpFileTime2->dwHighDateTime << 32);
	if (lhs < rhs)
		return -1;
	if (lhs > rhs)
		return 1;
	return 0;
}

INTERN DWORD WINAPI
libk32_GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh) {
	struct stat64 st;
	TRACE("GetFileSize(%p, %p)", hFile, lpFileSizeHigh);
	if (!NTHANDLE_ISFD(hFile)) {
		errno = EBADF;
		return INVALID_FILE_SIZE;
	}
	if (fstat64(NTHANDLE_ASFD(hFile), &st) != 0)
		return FALSE;
	if (lpFileSizeHigh)
		*lpFileSizeHigh = (DWORD)(st.st_size64 >> 32);
	return (DWORD)st.st_size64;
}

INTERN WINBOOL WINAPI
libk32_GetFileSizeEx(HANDLE hFile, PLARGE_INTEGER lpFileSize) {
	struct stat64 st;
	TRACE("GetFileSizeEx(%p, %p)", hFile, lpFileSize);
	if (!NTHANDLE_ISFD(hFile)) {
		errno = EBADF;
		return FALSE;
	}
	if (fstat64(NTHANDLE_ASFD(hFile), &st) != 0)
		return FALSE;
	lpFileSize->QuadPart = st.st_size64;
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_GetFileTime(HANDLE hFile,
                   LPFILETIME lpCreationTime,
                   LPFILETIME lpLastAccessTime,
                   LPFILETIME lpLastWriteTime) {
	struct stat64 st;
	TRACE("GetFileTime(%p, %p, %p, %p)",
	      hFile, lpCreationTime,
	      lpLastAccessTime, lpLastWriteTime);
	if (!NTHANDLE_ISFD(hFile)) {
		errno = EBADF;
		return FALSE;
	}
	if (fstat64(NTHANDLE_ASFD(hFile), &st) != 0)
		return FALSE;
	if (lpCreationTime)
		*lpCreationTime = libk32_TimeSpecToFileTime(&st.st_btimespec64);
	if (lpLastAccessTime)
		*lpLastAccessTime = libk32_TimeSpecToFileTime(&st.st_atimespec64);
	if (lpLastWriteTime)
		*lpLastWriteTime = libk32_TimeSpecToFileTime(&st.st_mtimespec64);
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_SetFileTime(HANDLE hFile,
                   CONST FILETIME *lpCreationTime,
                   CONST FILETIME *lpLastAccessTime,
                   CONST FILETIME *lpLastWriteTime) {
	struct timespec64 ts[3];
	atflag_t flags = AT_EMPTY_PATH;
	TRACE("SetFileTime(%p, %p, %p, %p)",
	      hFile, lpCreationTime,
	      lpLastAccessTime, lpLastWriteTime);
	if (!NTHANDLE_ISFD(hFile)) {
		errno = EBADF;
		return FALSE;
	}
	ts[0].tv_nsec = UTIME_OMIT;
	ts[1].tv_nsec = UTIME_OMIT;
	if (lpLastAccessTime)
		ts[0] = libk32_FileTimeToTimeSpec(lpLastAccessTime);
	if (lpLastWriteTime)
		ts[1] = libk32_FileTimeToTimeSpec(lpLastWriteTime);
	if (lpCreationTime) {
		ts[2] = libk32_FileTimeToTimeSpec(lpCreationTime);
		flags |= AT_CHANGE_BTIME;
	}
	return utimensat64(NTHANDLE_ASFD(hFile), "", ts, flags) == 0;
}

INTERN DWORD WINAPI
libk32_GetFileType(HANDLE hFile) {
	struct stat64 st;
	TRACE("GetFileType(%p)", hFile);
	if (!NTHANDLE_ISFD(hFile)) {
		errno = EBADF;
		return FILE_TYPE_UNKNOWN;
	}
	if (fstat64(NTHANDLE_ASFD(hFile), &st) != 0)
		return FILE_TYPE_UNKNOWN;
	if (S_ISBLK(st.st_mode))
		return FILE_TYPE_DISK;
	if (S_ISCHR(st.st_mode))
		return FILE_TYPE_CHAR;
	if (S_ISFIFO(st.st_mode) || S_ISSOCK(st.st_mode))
		return FILE_TYPE_PIPE;
	return FILE_TYPE_DISK; /* Also returned for "regular" files. */
}

INTERN WINBOOL WINAPI
libk32_FileTimeToLocalFileTime(CONST FILETIME *lpFileTime,
                               LPFILETIME lpLocalFileTime) {
	TRACE("FileTimeToLocalFileTime(%p, %p)", lpFileTime, lpLocalFileTime);
	*lpLocalFileTime = *lpFileTime;
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_LocalFileTimeToFileTime(CONST FILETIME *lpLocalFileTime,
                               LPFILETIME lpFileTime) {
	TRACE("LocalFileTimeToFileTime(%p, %p)", lpLocalFileTime, lpFileTime);
	*lpFileTime = *lpLocalFileTime;
	return TRUE;
}

DEFINE_PUBLIC_ALIAS(GetFileAttributesA, libk32_GetFileAttributesA);
DEFINE_PUBLIC_ALIAS(GetFileAttributesW, libk32_GetFileAttributesW);
DEFINE_PUBLIC_ALIAS(GetFileAttributesExA, libk32_GetFileAttributesExA);
DEFINE_PUBLIC_ALIAS(GetFileAttributesExW, libk32_GetFileAttributesExW);
DEFINE_PUBLIC_ALIAS(SetFileAttributesA, libk32_SetFileAttributesA);
DEFINE_PUBLIC_ALIAS(SetFileAttributesW, libk32_SetFileAttributesW);
DEFINE_PUBLIC_ALIAS(GetFileInformationByHandle, libk32_GetFileInformationByHandle);
DEFINE_PUBLIC_ALIAS(CompareFileTime, libk32_CompareFileTime);
DEFINE_PUBLIC_ALIAS(GetFileSize, libk32_GetFileSize);
DEFINE_PUBLIC_ALIAS(GetFileSizeEx, libk32_GetFileSizeEx);
DEFINE_PUBLIC_ALIAS(GetFileTime, libk32_GetFileTime);
DEFINE_PUBLIC_ALIAS(SetFileTime, libk32_SetFileTime);
DEFINE_PUBLIC_ALIAS(GetFileType, libk32_GetFileType);
DEFINE_PUBLIC_ALIAS(FileTimeToLocalFileTime, libk32_FileTimeToLocalFileTime);
DEFINE_PUBLIC_ALIAS(LocalFileTimeToFileTime, libk32_LocalFileTimeToFileTime);
/************************************************************************/

DECL_END

#endif /* !GUARD_LIBKERNEL32_FILEAPI_C */
