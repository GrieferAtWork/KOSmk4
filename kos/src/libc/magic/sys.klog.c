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
%(c_prefix){
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/klog.h) */
/* (#) Portability: diet libc     (/include/sys/klog.h) */
/* (#) Portability: musl libc     (/include/sys/klog.h) */
/* (#) Portability: uClibc        (/include/sys/klog.h) */
}

%[default:section(".text.crt{|.dos}.utility.klog")]

%[insert:prefix(
#include <features.h>
)]%{


#ifdef __CC__
__SYSDECL_BEGIN

}

[[decl_include("<features.h>")]]
int klogctl(__STDC_INT_AS_UINT_T type, char *bufp, __STDC_INT_AS_SIZE_T len);

%{

__SYSDECL_END
#endif /* __CC__ */

}
