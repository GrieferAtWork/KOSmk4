/* HASH CRC-32:0xc834b397 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_umount_defined
#ifdef __CRT_HAVE_umount2
#define __local_umount_defined 1
/* Dependency: "umount2" */
#ifndef ____localdep_umount2_defined
#define ____localdep_umount2_defined 1
#ifdef __CRT_HAVE_umount2
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_umount2,(char const *__special_file, int __flags),umount2,(__special_file,__flags))
#else /* LIBC: umount2 */
#undef ____localdep_umount2_defined
#endif /* umount2... */
#endif /* !____localdep_umount2_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(umount) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(umount))(char const *__special_file) {
#line 220 "kos/src/libc/magic/sys.mount.c"
	return __localdep_umount2(__special_file, 0);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_umount2 */
#endif /* !__local_umount_defined */
