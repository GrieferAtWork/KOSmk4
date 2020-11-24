/* HASH CRC-32:0xa1f94c67 */
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
#ifndef __local_mkdtemp_defined
#define __local_mkdtemp_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_mkdir) || (defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE__mkdir))
__NAMESPACE_LOCAL_BEGIN
/* Dependency: system_mktemp from stdlib */
#ifndef __local___localdep_system_mktemp_defined
#define __local___localdep_system_mktemp_defined 1
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/system_mktemp.h>
__NAMESPACE_LOCAL_BEGIN
/* Internal implementation for creating temporary files.
 * @param: what: Select what kind of temporary object to create.
 *                  `0': Create a temporary file. (The handle of that file will be returned)
 *                       Creating mode used is 0600
 *                       This mode is only recognized when `$has_function(open)'
 *                  `1': Create a temporary directory. (0 is returned on success)
 *                       Creating mode used is 0700
 *                       This mode is only recognized when `$has_function(mkdir)'
 *                       NOTE: `flags' is ignored in this mode
 *                  `2': Braindead `mktemp(3)'-mode: Like `0', but don't actually create the
 *                       file. Instead, return `0' on success
 *                       This mode is only recognized when `$has_function(open) || $has_function(stat)'
 *                       NOTE: `flags' is ignored in this mode */
#define __localdep_system_mktemp __LIBC_LOCAL_NAME(system_mktemp)
#endif /* !__local___localdep_system_mktemp_defined */
/* >> mkdtemp(3)
 * Replace the last 6 characters of `TEMPLATE', which must be filled with
 * all 'X'-characters before the call (else errno=EINVAL + return -1),
 * with random characters such that the pathname described by `TEMPLATE'
 * will not already exists. Then, create a new directory with `mode=0700',
 * and re-return `template_' to indicate success.
 * On error, `NULL' will be returned, and the contents of `TEMPLATE' are undefined. */
__LOCAL_LIBC(mkdtemp) __ATTR_WUNUSED __ATTR_NONNULL((1)) char *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(mkdtemp))(char *__template_) {
	if (__localdep_system_mktemp(1, __template_, 0, 0) )
		__template_ = __NULLPTR;
	return __template_;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mkdtemp_defined
#define __local___localdep_mkdtemp_defined 1
#define __localdep_mkdtemp __LIBC_LOCAL_NAME(mkdtemp)
#endif /* !__local___localdep_mkdtemp_defined */
#else /* __CRT_HAVE_mkdir || (__CRT_DOS_PRIMARY && __CRT_HAVE__mkdir) */
#undef __local_mkdtemp_defined
#endif /* !__CRT_HAVE_mkdir && (!__CRT_DOS_PRIMARY || !__CRT_HAVE__mkdir) */
#endif /* !__local_mkdtemp_defined */
