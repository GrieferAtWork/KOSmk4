/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _NT_WINNLS_H
#define _NT_WINNLS_H 1

#include "__stdinc.h"
/**/

#include "types.h"

#ifdef __CC__
__DECL_BEGIN

#define CP_ACP        0
#define CP_OEMCP      1
#define CP_MACCP      2
#define CP_THREAD_ACP 3
#define CP_SYMBOL     42
#define CP_UTF7       65000
#define CP_UTF8       65001

WINBASEAPI WINBOOL WINAPI IsValidCodePage(UINT uCodePage);
WINBASEAPI UINT WINAPI GetACP(void);
WINBASEAPI UINT WINAPI GetOEMCP(void);
WINBASEAPI WINBOOL WINAPI IsDBCSLeadByte(BYTE bTestChar);
WINBASEAPI WINBOOL WINAPI IsDBCSLeadByteEx(UINT uCodePage, BYTE bTestChar);

__DECL_END
#endif /* __CC__ */

#endif /* !_NT_WINNLS_H */
