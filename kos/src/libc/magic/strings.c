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

%{
#include <features.h>
#ifdef __USE_XOPEN2K8
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 */
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */

__SYSDECL_BEGIN

#ifdef __CC__
#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

}
%#if defined(__USE_MISC) || !defined(__USE_XOPEN2K8)

%[insert:extern(bcopy)]
%[insert:guarded_function(bcmp = memcmp)]
%[insert:extern(index)]
%[insert:extern(rindex)]

%
%#ifndef __bzero_defined
%#define __bzero_defined 1
%[insert:function(bzero)]
%#if defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
%[insert:function(bzero = bzeroc, externLinkageOverride: "C++")]
%#endif /* __cplusplus && __USE_STRING_OVERLOADS */
%#endif /* !__bzero_defined */
%
%#ifdef __USE_STRING_BWLQ
%[insert:extern(bzerow)]
%[insert:extern(bzerol)]
%[insert:extern(bzeroq)]
%#endif /* __USE_STRING_BWLQ */
%
%#ifdef __USE_KOS
%[insert:extern(bzeroc)]
%#endif /* __USE_KOS */
%#endif /* __USE_MISC || !__USE_XOPEN2K8 */
%
%[insert:extern(strcasecmp)]
%[insert:extern(strncasecmp)]
%
%#ifdef __USE_XOPEN2K8
%[insert:extern(strcasecmp_l)]
%[insert:extern(strncasecmp_l)]
%#endif /* __USE_XOPEN2K8 */
%


%
%#if defined(__USE_KOS) || defined(__USE_GNU) || defined(__USE_BSD)
@@Same as `bzero(buf, num_bytes)', however compilers will not optimize
@@away uses of this function when they (think) that clearing the memory
@@wouldn't have any visible side-effects (though those side-effects
@@may be a security-concious application trying to wipe sensitive data)
[[nocrt, no_crt_self_import]]
[[alias("bzero", "explicit_bzero", "__bzero")]]
void explicit_bzero(void *buf, size_t num_bytes) {
	void *volatile vbuf = buf;
	bzero(vbuf, num_bytes);
}
%#endif /* __USE_KOS || __USE_GNU || __USE_BSD */


%{
#if !defined(__cplusplus) && defined(__USE_STRING_OVERLOADS)
/* In C, we can use argument-count overload macros to implement these overloads! */
#ifdef __USE_MISC
#undef __PRIVATE_bzero_3
#undef __PRIVATE_bzero_4
#ifdef __USE_KOS
#define __PRIVATE_bzero_4   bzeroc
#else /* __USE_KOS */
__SYSDECL_END
#include <libc/string.h>
__SYSDECL_BEGIN
#define __PRIVATE_bzero_4   __libc_bzeroc
#endif /* !__USE_KOS */
#define __PRIVATE_bzero_3   (bzero)
#undef bzero
#define bzero(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_bzero_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* __USE_MISC */
#endif /* !__cplusplus && __USE_STRING_OVERLOADS */
}

%{
#endif /* __CC__ */

__SYSDECL_END

}

