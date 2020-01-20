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

%[default_impl_section(.text.crt.ssp.string.memory)]

%{
#include <features.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

}

[userimpl][ATTR_LEAF]
__memcpy_chk:([nonnull] void *__restrict dst,
              [nonnull] void const *__restrict src,
              size_t num_bytes, size_t dst_bufsize)
		-> [== dst] void * {
	(void)dst_bufsize;
	return memcpy(dst, src, num_bytes);
}

[userimpl][ATTR_LEAF]
__memmove_chk:([nonnull] void *dst,
               [nonnull] void const *src,
               size_t num_bytes, size_t dst_bufsize)
		-> [== dst] void * {
	(void)dst_bufsize;
	return memmove(dst, src, num_bytes);
}

[userimpl][ATTR_LEAF]
__mempcpy_chk:([nonnull] void *__restrict dst,
               [nonnull] void const *__restrict src,
               size_t num_bytes, size_t dst_bufsize)
		-> [== dst + num_bytes] void * {
	(void)dst_bufsize;
	return memmove(dst, src, num_bytes);
}

[userimpl][ATTR_LEAF]
__memset_chk:([nonnull] void *__restrict dst, int byte,
              size_t num_bytes, size_t dst_bufsize)
		-> [== dst] void * {
	(void)dst_bufsize;
	return memset(dst, byte, num_bytes);
}

[userimpl][ATTR_LEAF]
__stpcpy_chk:([nonnull] char *__restrict dst,
              [nonnull] char const *__restrict src,
              size_t dst_bufsize)
		-> [== buf + strlen(src)] char * {
	(void)dst_bufsize;
	return stpcpy(dst, src);
}

[userimpl][ATTR_LEAF]
__strcat_chk:([nonnull] char *__restrict dst,
              [nonnull] char const *__restrict src,
              size_t dst_bufsize)
		-> [== buf] char * {
	(void)dst_bufsize;
	return strcat(dst, src);
}

[userimpl][ATTR_LEAF]
__strcpy_chk:([nonnull] char *__restrict dst,
              [nonnull] char const *__restrict src,
              size_t dst_bufsize)
		-> [== buf] char * {
	(void)dst_bufsize;
	return strcpy(dst, src);
}

[userimpl][ATTR_LEAF]
__strncat_chk:([nonnull] char *__restrict dst,
               [nonnull] char const *__restrict src,
               size_t buflen, size_t dst_bufsize)
		-> [== buf] char * {
	(void)dst_bufsize;
	return strncat(dst, src, buflen);
}

[userimpl][ATTR_LEAF]
__strncpy_chk:([nonnull] char *__restrict dst,
               [nonnull] char const *__restrict src,
               size_t buflen, size_t dst_bufsize)
		-> [== buf] char * {
	(void)dst_bufsize;
	return strncpy(dst, src, buflen);
}

%{

#endif /* __CC__ */

__SYSDECL_END

}