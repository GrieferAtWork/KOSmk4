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

%[define_replacement(major_t = __major_t)]
%[define_replacement(minor_t = __minor_t)]
%[define_replacement(dev_t = __dev_t)]
%[default_impl_section(".text.crt.system.utility")]

%{
#include <features.h>
#include <bits/types.h>

__SYSDECL_BEGIN

#ifdef __CC__

}

[[ATTR_CONST, ATTR_WUNUSED, nothrow]]
$major_t gnu_dev_major($dev_t dev) {
	return (major_t)((uintptr_t)dev >> 20);
}

[[ATTR_CONST, ATTR_WUNUSED, nothrow]]
$minor_t gnu_dev_minor($dev_t dev) {
	return (minor_t)((uintptr_t)dev & ((1 << 20) - 1));
}

[[ATTR_CONST, ATTR_WUNUSED, nothrow]]
$dev_t gnu_dev_makedev($major_t major, $minor_t minor) {
	return (dev_t)major << 20 | (dev_t)minor;
}

%{

/* Access the functions with their traditional names.  */
#define major(dev)        gnu_dev_major(dev)
#define minor(dev)        gnu_dev_minor(dev)
#define makedev(maj, min) gnu_dev_makedev(maj, min)

#endif /* __CC__ */

__SYSDECL_END

}