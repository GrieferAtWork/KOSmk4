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
#ifndef GUARD_LIBKERNEL32_MESSAGES_C
#define GUARD_LIBKERNEL32_MESSAGES_C 1
#define _KOS_SOURCE 1
#define _UTF_SOURCE 1
#define _GNU_SOURCE 1

#include "api.h"
/**/

#include <kos/types.h>
#include <nt/messages.h>

#include <format-printer.h>
#include <malloc.h>
#include <string.h>
#include <uchar.h>
#include <wchar.h>

DECL_BEGIN

/************************************************************************/
__LIBC NOBLOCK ATTR_CONST /*kos*/ errno_t NOTHROW(LIBDCALL errno_nt2dos)(/*nt*/ errno_t value);
__LIBC NOBLOCK ATTR_CONST /*nt*/ errno_t NOTHROW(LIBDCALL errno_kos2nt)(/*kos*/ errno_t value);
__LIBC NOBLOCK ATTR_CONST /*dos*/ errno_t NOTHROW(LIBDCALL errno_nt2dos)(/*nt*/ errno_t value);
__LIBC NOBLOCK ATTR_CONST /*nt*/ errno_t NOTHROW(LIBDCALL errno_dos2nt)(/*kos*/ errno_t value);

PRIVATE char *WINAPI
libk32_MakeMessageA(DWORD dwFlags, LPCVOID lpSource, DWORD dwMessageId,
                    DWORD dwLanguageId, __NT_VA_LIST *Arguments) {
	struct format_aprintf_data printer;
	format_aprintf_data_init(&printer);
	(void)lpSource;
	(void)dwLanguageId;
	(void)Arguments;
	if (dwFlags & FORMAT_MESSAGE_FROM_SYSTEM) {
		char const *message;
		message = strerrordesc_np(errno_nt2dos(dwMessageId));
		if (message != NULL) {
			if (format_aprintf_printer(&printer, message, strlen(message)) < 0)
				goto err;
			goto done;
		}
	}
	if (format_printf(&format_aprintf_printer, &printer,
	                  "<Unknown message[flags:%#x,source:%p,id:%#x,lang:%#x]>",
	                  dwFlags, lpSource, dwMessageId, dwLanguageId) < 0)
		goto err;
done:
	return format_aprintf_pack(&printer, NULL);
err:
	format_aprintf_data_fini(&printer);
	return NULL;
}

PRIVATE char16_t *WINAPI
libk32_MakeMessageW(DWORD dwFlags, LPCVOID lpSource, DWORD dwMessageId,
                    DWORD dwLanguageId, __NT_VA_LIST *Arguments) {
	char *utf8;
	char16_t *result;
	utf8 = libk32_MakeMessageA(dwFlags, lpSource, dwMessageId, dwLanguageId, Arguments);
	if (!utf8)
		return NULL;
	result = convert_mbstoc16(utf8);
	free(utf8);
	return result;
}


INTERN DWORD WINAPI
libk32_FormatMessageA(DWORD dwFlags, LPCVOID lpSource, DWORD dwMessageId,
                      DWORD dwLanguageId, LPSTR lpBuffer, DWORD nSize, __NT_VA_LIST *Arguments) {
	char *msg;
	DWORD len;
	TRACE("FormatMessageA(%#x, %p, %#x, %#x, %p, %#x, %p)",
	      dwFlags, lpSource, dwMessageId,
	      dwLanguageId, lpBuffer, nSize, Arguments);
	msg = libk32_MakeMessageA(dwFlags, lpSource, dwMessageId, dwLanguageId, Arguments);
	if (!msg)
		return 0;
	len = (DWORD)strlen(msg);
	if (dwFlags & FORMAT_MESSAGE_ALLOCATE_BUFFER) {
		size_t used_size = malloc_usable_size(msg);
		if (nSize > used_size) {
			char *newmsg = (char *)realloc(msg, nSize);
			if (!newmsg) {
				free(msg);
				return 0;
			}
			msg = newmsg;
		}
		*(char **)lpBuffer = msg;
		return len;
	}
	++len;
	if (len > nSize)
		len = nSize;
	memcpy(lpBuffer, msg, len, sizeof(CHAR));
	--len;
	free(msg);
	return len;
}

INTERN DWORD WINAPI
libk32_FormatMessageW(DWORD dwFlags, LPCVOID lpSource, DWORD dwMessageId,
                      DWORD dwLanguageId, LPWSTR lpBuffer, DWORD nSize,
                      __NT_VA_LIST *Arguments) {
	char16_t *msg;
	DWORD len;
	TRACE("FormatMessageW(%#x, %p, %#x, %#x, %p, %#x, %p)",
	      dwFlags, lpSource, dwMessageId,
	      dwLanguageId, lpBuffer, nSize, Arguments);
	msg = libk32_MakeMessageW(dwFlags, lpSource, dwMessageId, dwLanguageId, Arguments);
	if (!msg)
		return 0;
	len = (DWORD)c16len(msg);
	if (dwFlags & FORMAT_MESSAGE_ALLOCATE_BUFFER) {
		size_t used_size = malloc_usable_size(msg);
		if (nSize > used_size) {
			char16_t *newmsg = (char16_t *)realloc(msg, nSize);
			if (!newmsg) {
				free(msg);
				return 0;
			}
			msg = newmsg;
		}
		*(char16_t **)lpBuffer = msg;
		return len;
	}
	++len;
	if (len > nSize)
		len = nSize;
	memcpy(lpBuffer, msg, len, sizeof(WCHAR));
	--len;
	free(msg);
	return len;
}

DEFINE_PUBLIC_ALIAS(FormatMessageA, libk32_FormatMessageA);
DEFINE_PUBLIC_ALIAS(FormatMessageW, libk32_FormatMessageW);
/************************************************************************/

DECL_END

#endif /* !GUARD_LIBKERNEL32_MESSAGES_C */
