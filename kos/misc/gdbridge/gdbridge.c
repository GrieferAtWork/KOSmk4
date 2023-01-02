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
#ifndef GUARD_GDBBRIDGE_GDBBRIDGE_C
#define GUARD_GDBBRIDGE_GDBBRIDGE_C 1
#define _GNU_SOURCE 1 /* memmem() */

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if 1

int main(int argc, char *argv[]) {
	STARTUPINFOW sStartupInfo;
	PROCESS_INFORMATION pInfo;
	DWORD dwExitCode;
#define WIDEN2(x) L##x
#define WIDEN(x) WIDEN2(x)
	WCHAR wCmdline[] = WIDEN(CMDLINE);
	memset(&sStartupInfo, 0, sizeof(sStartupInfo));
	sStartupInfo.cb         = sizeof(sStartupInfo);
	sStartupInfo.dwFlags    = STARTF_USESTDHANDLES;
	sStartupInfo.hStdInput  = GetStdHandle(STD_INPUT_HANDLE);
	sStartupInfo.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	sStartupInfo.hStdError  = GetStdHandle(STD_ERROR_HANDLE);
	SetHandleInformation(sStartupInfo.hStdInput, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
	SetHandleInformation(sStartupInfo.hStdOutput, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
	SetHandleInformation(sStartupInfo.hStdError, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
	if (!CreateProcessW(NULL, wCmdline,
	                    NULL, NULL, TRUE, CREATE_UNICODE_ENVIRONMENT,
	                    NULL, NULL, &sStartupInfo, &pInfo)) {
		fprintf(stderr, "CreateProcessW() failed: %lu (cmdline: '%ls')\n",
		        (unsigned long)GetLastError(), wCmdline);
		return 1;
	}
	dwExitCode = 1;
	WaitForSingleObject(pInfo.hProcess, INFINITE);
	GetExitCodeProcess(pInfo.hProcess, &dwExitCode);
	TerminateProcess(pInfo.hProcess, 0);
	CloseHandle(pInfo.hProcess);
	ExitProcess(dwExitCode);
}


#elif 1

static LPWSTR formCommandFile(char const *arg0) {
	LPWSTR result, dst;
#define USE_DEEMON_FROM_BINUTILS 1
#ifdef USE_DEEMON_FROM_BINUTILS
	static WCHAR const prefix[] = L"..\\..\\..\\binutils\\deemon\\deemon.exe \"";
	static WCHAR const suffix[] = L"gdbbridge.dee\"";
	size_t i, pathlen, total;
	pathlen = strlen(arg0);
	while (pathlen && (arg0[pathlen - 1] != '\\' && arg0[pathlen - 1] != '/'))
		--pathlen;
	while (pathlen && (arg0[pathlen - 1] == '\\' || arg0[pathlen - 1] == '/'))
		--pathlen;
#define CSTRLEN(x) ((sizeof(x) / sizeof(*(x))) - 1)
	total = (pathlen + 1 + CSTRLEN(prefix) + pathlen + 1 + CSTRLEN(suffix) + 1) * sizeof(WCHAR);
	result = (LPWSTR)malloc(total);
	if (!result) {
		fprintf(stderr, "malloc(%lu) failed\n", (unsigned long)total);
		ExitProcess(1);
	}
	dst = result;
	for (i = 0; i < pathlen; ++i)
		*dst++ = (WCHAR)arg0[i];
	if (pathlen)
		*dst++ = '\\';
	memcpy(dst, prefix, CSTRLEN(prefix) * sizeof(WCHAR));
	dst += CSTRLEN(prefix);
	for (i = 0; i < pathlen; ++i)
		*dst++ = (WCHAR)arg0[i];
	if (pathlen)
		*dst++ = '\\';
	memcpy(dst, suffix, sizeof(suffix));
	return result;
#else /* USE_DEEMON_FROM_BINUTILS */
	static WCHAR const prefix[] = L"cmd /c \"deemon \"";
	static WCHAR const suffix[] = L"gdbbridge.dee\"";
	size_t i, pathlen, total;
	pathlen = strlen(arg0);
	while (pathlen && (arg0[pathlen - 1] != '\\' && arg0[pathlen - 1] != '/'))
		--pathlen;
	while (pathlen && (arg0[pathlen - 1] == '\\' || arg0[pathlen - 1] == '/'))
		--pathlen;
#define CSTRLEN(x) ((sizeof(x) / sizeof(*(x))) - 1)
	total = (CSTRLEN(prefix) + pathlen + 1 + CSTRLEN(suffix) + 1) * sizeof(WCHAR);
	result = (LPWSTR)malloc(total);
	if (!result) {
		fprintf(stderr, "malloc(%lu) failed\n", (unsigned long)total);
		ExitProcess(1);
	}
	dst = result;
	memcpy(dst, prefix, CSTRLEN(prefix) * sizeof(WCHAR));
	dst += CSTRLEN(prefix);
	for (i = 0; i < pathlen; ++i)
		*dst++ = (WCHAR)arg0[i];
	if (pathlen)
		*dst++ = '\\';
	memcpy(dst, suffix, sizeof(suffix));
	return result;
#endif /* USE_DEEMON_FROM_BINUTILS */
}

int main(int argc, char *argv[]) {
	STARTUPINFOW sStartupInfo;
	PROCESS_INFORMATION pInfo;
	DWORD dwExitCode;
	LPWSTR wCmdline;
	memset(&sStartupInfo, 0, sizeof(sStartupInfo));
	sStartupInfo.cb         = sizeof(sStartupInfo);
	sStartupInfo.dwFlags    = STARTF_USESTDHANDLES;
	sStartupInfo.hStdInput  = GetStdHandle(STD_INPUT_HANDLE);
	sStartupInfo.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	sStartupInfo.hStdError  = GetStdHandle(STD_ERROR_HANDLE);
	SetHandleInformation(sStartupInfo.hStdInput, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
	SetHandleInformation(sStartupInfo.hStdOutput, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
	SetHandleInformation(sStartupInfo.hStdError, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
	wCmdline = formCommandFile(argv[0]);
	if (!CreateProcessW(NULL, wCmdline,
	                    NULL, NULL, TRUE, CREATE_UNICODE_ENVIRONMENT,
	                    NULL, NULL, &sStartupInfo, &pInfo)) {
		fprintf(stderr, "CreateProcessW() failed: %lu (cmdline: %ls)\n",
		        (unsigned long)GetLastError(), wCmdline);
		return 1;
	}
	dwExitCode = 1;
	WaitForSingleObject(pInfo.hProcess, INFINITE);
	GetExitCodeProcess(pInfo.hProcess, &dwExitCode);
	TerminateProcess(pInfo.hProcess, 0);
	CloseHandle(pInfo.hProcess);
	ExitProcess(dwExitCode);
}

#else
#ifndef __USE_GNU
#undef memmem
#define memmem my_memmem
static void *my_memmem(void const *haystack, size_t haystacklen,
                       void const *needle, size_t needlelen) {
	BYTE *candidate, marker;
	if (!needlelen)
		return (void *)haystack;
	if (needlelen > haystacklen)
		return NULL;
	haystacklen -= (needlelen - 1);
	marker       = *(BYTE *)needle;
	while ((candidate = (BYTE *)memchr(haystack, marker, haystacklen)) != NULL) {
		if (memcmp(candidate, needle, needlelen) == 0)
			return (void *)candidate;
		++candidate;
		haystacklen = ((BYTE *)haystack + haystacklen) - candidate;
		haystack    = (void const *)candidate;
	}
	return NULL;
}
#endif /* !__USE_GNU */


#define ERR(func) \
	fprintf(stderr, "%d:" #func "() failed: %lu\n", __LINE__, (unsigned long)GetLastError())

static HANDLE hOuR, hInW;
static HANDLE hMyR, hMyW;

static BOOL WriteFileAll(HANDLE hFile, LPCVOID lpBuffer, DWORD dwCount) {
	while (dwCount) {
		DWORD dwTemp;
		if (!WriteFile(hFile, lpBuffer, dwCount, &dwTemp, NULL))
			return FALSE;
		if (!dwTemp)
			return FALSE;
		if (dwTemp >= dwCount)
			break;
		lpBuffer = (LPCBYTE)lpBuffer + dwTemp;
		dwCount -= dwTemp;
	}
	return TRUE;
}

static BOOL TransferMyRToInW(void) {
	DWORD dwCount;
	static BYTE bTempBuffer[4096];
	if (!ReadFile(hMyR, bTempBuffer, sizeof(bTempBuffer), &dwCount, NULL)) {
		ERR(ReadFile);
		return FALSE;
	}
	if (!WriteFileAll(hInW, bTempBuffer, dwCount)) {
		ERR(WriteFile);
		return FALSE;
	}
	return TRUE;
}

static BOOL DoReadFile(HANDLE hFile, LPVOID lpBuffer,
                       DWORD nNumberOfBytesToRead,
                       LPDWORD lpNumberOfBytesRead) {
	HANDLE hWaitFor[2];
	DWORD dwStatus;
again:
	hWaitFor[0] = hMyR;
	hWaitFor[1] = hFile;
	dwStatus = WaitForMultipleObjects(2, hWaitFor, FALSE, INFINITE);
	if (dwStatus == WAIT_OBJECT_0 + 0) {
		if (!TransferMyRToInW())
			return FALSE;
		goto again;
	}
	if (dwStatus == WAIT_OBJECT_0 + 1) {
		return ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, NULL);
	}
	return TRUE;
}

static DWORD ReadFileMin(HANDLE hFile, LPCVOID lpBuffer, DWORD dwMinCount, DWORD dwMaxCount) {
	DWORD dwResult = 0;
	while (dwResult < dwMinCount) {
		DWORD dwTemp;
		if (!DoReadFile(hFile,
		                (PBYTE)lpBuffer + dwResult,
		                dwMaxCount - dwResult, &dwTemp))
			return FALSE;
		if (!dwTemp)
			return FALSE;
		dwResult += dwResult;
	}
	return dwResult;
}

static char const pattern[]   = "*stopped,reason=\"exited";
static char const lfpattern[] = "\n*stopped,reason=\"exited";
static char const response[]  = "inferior 1\nc\n";

int main(int argc, char *argv[]) {
	HANDLE hInR, hOuW;
	STARTUPINFOW sStartupInfo;
	PROCESS_INFORMATION pGdbProcessInfo;
	if (!CreatePipe(&hInR, &hInW, NULL, 4096)) {
		ERR(CreatePipe);
		return 1;
	}
	if (!CreatePipe(&hOuR, &hOuW, NULL, 4096)) {
		ERR(CreatePipe);
		return 1;
	}
	hMyR = GetStdHandle(STD_INPUT_HANDLE);
	hMyW = GetStdHandle(STD_OUTPUT_HANDLE);
	memset(&sStartupInfo, 0, sizeof(sStartupInfo));
	sStartupInfo.cb         = sizeof(sStartupInfo);
	sStartupInfo.dwFlags    = STARTF_USESTDHANDLES;
	sStartupInfo.hStdInput  = hInR;
	sStartupInfo.hStdOutput = hOuW;
	sStartupInfo.hStdError  = hOuW;
	SetHandleInformation(sStartupInfo.hStdInput, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
	SetHandleInformation(sStartupInfo.hStdOutput, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
	SetHandleInformation(sStartupInfo.hStdError, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
	{
		WCHAR wCmdline[] = L"gdb.exe --interpreter=mi";
		if (!CreateProcessW(NULL, wCmdline,
		                    NULL, NULL, TRUE, CREATE_UNICODE_ENVIRONMENT,
		                    NULL, NULL, &sStartupInfo, &pGdbProcessInfo)) {
			ERR(CreateProcessW);
			return 1;
		}
	}
	CloseHandle(hOuW);
	CloseHandle(hInR);
#if 1
	{
		static char const init[] =
		"set detach-on-fork off\n"
		"set schedule-multiple on\n"
		"set follow-fork-mode child\n"
		"set sysroot bin/i386-kos-OD\n"
		"set solib-search-path bin/i386-kos-OD/lib:bin/i386-kos-OD/os/drivers\n"
		"set target-async on\n"
		"target remote localhost:1234\n";
		WriteFileAll(hInW, init, sizeof(init) - 1);
	}
#endif
	for (;;) {
		DWORD dwCount, i;
		PBYTE pMatch, pEnd;
		static BYTE bTransferBuffer[4096];
		if (!DoReadFile(hOuR, bTransferBuffer,
		                sizeof(bTransferBuffer),
		                &dwCount)) {
			ERR(ReadFile);
			goto done;
		}
		if (!dwCount)
			goto done; /* EOF (graceful) */
		/* Scan input for `*stopped,reason="exited' */
		pEnd   = bTransferBuffer + dwCount;
		pMatch = bTransferBuffer;
again_scan_buffer:
		if (dwCount >= sizeof(pattern) - 1 &&
		    memcmp(pMatch, pattern, sizeof(pattern) - 1) == 0) {
			pMatch += sizeof(pattern) - 1;
			goto skip_until_eol_after_pMatch;
		}
		pMatch = (PBYTE)memmem(pMatch, dwCount,
		                       lfpattern, sizeof(lfpattern) - 1);
		if (pMatch) {
			PBYTE eol;
			if (!WriteFileAll(hMyW,
			                  bTransferBuffer,
			                  (DWORD)(pMatch - bTransferBuffer))) {
				ERR(WriteFile);
				goto done;
			}
			pMatch += sizeof(lfpattern) - 1;
skip_until_eol_after_pMatch:
			/* Respond with `c\n' to GDB. */
			if (!WriteFileAll(hMyR, response, sizeof(response) - 1)) {
				ERR(WriteFile);
				goto done;
			}
			eol = (PBYTE)memchr(pMatch, '\n', pEnd - pMatch);
			if (eol) {
				pMatch = eol;
				goto again_scan_buffer;
			}
			/* Read data until EOL */
			do {
				if (!DoReadFile(hOuR, bTransferBuffer,
				                sizeof(bTransferBuffer),
				                &dwCount)) {
					ERR(ReadFile);
					goto done;
				}
				if (!dwCount)
					goto done; /* EOF (graceful) */
				eol = (PBYTE)memchr(bTransferBuffer, '\n', dwCount);
			} while (!eol);
			pMatch = eol;
			goto again_scan_buffer;
		}

		/* Check if the buffer ends with some part of pattern. */
#define ENDSWITH(p, len) (dwCount >= len && memcmp(pEnd - (len), p, len) == 0)
		i = sizeof(lfpattern) - 1;
		while (i >= 3) { /* Don't consider ends-with-lf as a match! */
			--i;
			if (ENDSWITH(lfpattern, i)) {
				DWORD dwMissingChars;
				if (!WriteFileAll(hMyW, bTransferBuffer,
				                  1 + (DWORD)((pEnd - i) - bTransferBuffer))) {
					ERR(WriteFile);
					goto done;
				}
				dwMissingChars = (sizeof(lfpattern) - 1) - i;
				dwCount = ReadFileMin(hOuR, bTransferBuffer,
				                      dwMissingChars, sizeof(bTransferBuffer));
				if (!dwCount)
					goto done;
				if (memcmp(bTransferBuffer, pattern + i, dwMissingChars) == 0)
					goto again_scan_buffer;
				if (!WriteFileAll(hMyW, pattern, i)) {
					ERR(WriteFile);
					goto done;
				}
				break;
			}
		}
		if (!WriteFileAll(hMyW,
		                  bTransferBuffer,
		                  dwCount)) {
			ERR(WriteFile);
			goto done;
		}
	}
done:
	/* Make sure that GDB terminates when we do */
	TerminateThread(pGdbProcessInfo.hThread, 0);
	TerminateProcess(pGdbProcessInfo.hProcess, 0);
	return 0;
}
#endif



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !GUARD_GDBBRIDGE_GDBBRIDGE_C */
