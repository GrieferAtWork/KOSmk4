/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/sysinfo.h) */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/[...]/sys/sysinfo.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/sysinfo.h) */
/* (#) Portability: diet libc     (/include/sys/sysinfo.h) */
/* (#) Portability: musl libc     (/include/sys/sysinfo.h) */
/* (#) Portability: uClibc        (/include/sys/sysinfo.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.system.info")]

%{
#include <features.h>
#include <linux/kernel.h>
#include <bits/types.h>

__SYSDECL_BEGIN

#ifdef __CC__
}

[[cp, decl_include("<linux/sysinfo.h>")]]
int sysinfo([[nonnull]] struct sysinfo *info);

[[cp, wunused]]
int get_nprocs_conf();

[[cp, wunused]]
int get_nprocs();

[[cp, wunused]]
$intptr_t get_phys_pages();

[[cp, wunused]]
$intptr_t get_avphys_pages();


%{
#endif /* __CC__ */

__SYSDECL_END

}