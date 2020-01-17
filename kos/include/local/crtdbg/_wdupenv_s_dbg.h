/* HASH CRC-32:0xdfc9b6f */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__wdupenv_s_dbg_defined
#define __local__wdupenv_s_dbg_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_wdupenv_s_dbg) _Check_return_wat_ __ATTR_NONNULL((3)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wdupenv_s_dbg))(__WCHAR16_TYPE__ **__pbuf,
                                                            __SIZE_TYPE__ *__pbuflen,
                                                            __WCHAR16_TYPE__ const *__varname,
                                                            int __block_type,
                                                            char const *__filename,
                                                            int __line) {
#line 537 "kos/src/libc/magic/crtdbg.c"
	(void)__block_type;
	(void)__filename;
	(void)__line;
	(void)__pbuf;
	(void)__pbuflen;
	(void)__varname;
	/* TODO: c16dupenv_s() */
	__COMPILER_IMPURE();
	return 1;
}
__NAMESPACE_LOCAL_END
#endif /* !__local__wdupenv_s_dbg_defined */
