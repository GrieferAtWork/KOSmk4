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
%(c_prefix){
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/sysinfo.h) */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/sysinfo.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/sysinfo.h) */
/* (#) Portability: diet libc     (/include/sys/sysinfo.h) */
/* (#) Portability: musl libc     (/include/sys/sysinfo.h) */
/* (#) Portability: uClibc        (/include/sys/sysinfo.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.system.info")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <linux/kernel.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{


#ifdef __CC__
__SYSDECL_BEGIN

}

@@>> sysinfo(2)
@@Return current system information
[[guard, decl_include("<linux/sysinfo.h>")]]
[[no_crt_self_import, if(!defined(__solaris__)), alias("sysinfo")]]
[[export_alias("__sysinfo", "__libc_sysinfo")]]
int sysinfo([[out]] struct sysinfo *info);

@@>> get_nprocs_conf(3)
@@Return the # of configured online processors
[[wunused, nothrow]]
[[export_as("__get_nprocs_conf")]] /* From Glibc 2.0.4 */
int get_nprocs_conf();

@@>> get_nprocs(3)
@@Return the # of currently online processors
[[wunused, nothrow]]
[[export_as("__get_nprocs")]] /* From Glibc 2.0.4 */
int get_nprocs();

@@>> get_phys_pages(3)
@@Return the total # of pages of physical memory
[[wunused, nothrow, decl_include("<bits/types.h>")]]
[[impl_include("<linux/sysinfo.h>")]]
[[requires_function(sysinfo, getpagesize)]]
[[export_as("__get_phys_pages")]] /* From Glibc 2.0.4 */
$intptr_t get_phys_pages() {
	struct @sysinfo@ info;
	uintptr_t result;
	size_t ps;
	if (sysinfo(&info))
		return -1;
	ps = getpagesize();
	while (info.@mem_unit@ > 1 && ps > 1) {
		info.@mem_unit@ >>= 1;
		ps >>= 1;
	}
	result = (uintptr_t)info.@totalram@ *
	         (uintptr_t)info.@mem_unit@;
	while (ps > 1) {
		result >>= 1;
		ps >>= 1;
	}
	return (intptr_t)result;
}


@@>> get_avphys_pages(3)
@@Return the total # of free pages of physical memory
[[wunused, nothrow, decl_include("<bits/types.h>")]]
[[impl_include("<linux/sysinfo.h>")]]
[[requires_function(sysinfo, getpagesize)]]
[[export_as("__get_avphys_pages")]] /* From Glibc 2.0.4 */
$intptr_t get_avphys_pages() {
	struct @sysinfo@ info;
	uintptr_t result;
	size_t ps;
	if (sysinfo(&info))
		return -1;
	ps = getpagesize();
	while (info.@mem_unit@ > 1 && ps > 1) {
		info.@mem_unit@ >>= 1;
		ps >>= 1;
	}
	result = (uintptr_t)info.@freeram@ *
	         (uintptr_t)info.@mem_unit@;
	while (ps > 1) {
		result >>= 1;
		ps >>= 1;
	}
	return (intptr_t)result;
}


%{
__SYSDECL_END
#endif /* __CC__ */

}
