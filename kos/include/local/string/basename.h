/* HASH CRC-32:0x1d5f1711 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_basename_defined
#define __local_basename_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(basename) __ATTR_WUNUSED __ATTR_PURE char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(basename))(char const *__filename) {
#line 556 "kos/src/libc/magic/string.c"
	char __ch, *__iter = (char *)__filename, *__result = __NULLPTR;
	if (!__filename || !*__filename)
		return (char *)__filename;
	do {
		__ch = *__iter++;
#ifdef ___WIN32
		if (__ch == '/' || __ch == '\\')
			__result = __iter;
#else /* _WIN32 */
		if (__ch == '/')
			__result = __iter;
#endif /* !_WIN32 */
	} while (__ch);
	if __unlikely(!__result)
		return (char *)__filename; /* Path doesn't contain '/'. */
	if (*__result)
		return __result; /* Last character isn't a '/'. */
	__iter = __result;
#ifdef ___WIN32
	while (__iter != __filename && (__iter[-1] == '/' || __iter[-1] == '\\'))
		--__iter;
#else /* _WIN32 */
	while (__iter != __filename && __iter[-1] == '/')
		--__iter;
#endif /* !_WIN32 */
	if (__iter == __filename)
		return __result-1; /* Only `'/'"-characters. */
	//*iter = '\0'; /* Trim all ending `'/'"-characters. */
#ifdef ___WIN32
	while (__iter != __filename && (__iter[-1] != '/' || __iter[-1] != '\\'))
		--__iter; /* Scan until the previous '/'. */
#else /* _WIN32 */
	while (__iter != __filename && __iter[-1] != '/')
		--__iter; /* Scan until the previous '/'. */
#endif /* !_WIN32 */
	return __iter; /* Returns string after previous '/'. */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_basename_defined */
