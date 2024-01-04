/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __LOCAL_MB_CUR_MAX
#include <__crt.h>
#ifndef __LOCAL_MB_CUR_MAX
#include <hybrid/typecore.h>
__DECL_BEGIN
#ifdef MB_CUR_MAX
#define __LOCAL_MB_CUR_MAX MB_CUR_MAX
#elif defined(__mb_cur_max)
#define __LOCAL_MB_CUR_MAX ((__SIZE_TYPE__)__mb_cur_max)
#elif defined(__ctype_get_mb_cur_max) || defined(____ctype_get_mb_cur_max_defined)
#define __LOCAL_MB_CUR_MAX __ctype_get_mb_cur_max()
#elif defined(___mb_cur_max_func) || defined(_____mb_cur_max_func_defined)
#define __LOCAL_MB_CUR_MAX ((__SIZE_TYPE__)___mb_cur_max_func())
#elif defined(__p___mb_cur_max) || defined(____p___mb_cur_max_defined)
#define __LOCAL_MB_CUR_MAX ((__SIZE_TYPE__)*__p___mb_cur_max())
#elif defined(__CRT_HAVE___ctype_get_mb_cur_max)
#define ____ctype_get_mb_cur_max_defined
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW,__ctype_get_mb_cur_max,(void),())
#define __LOCAL_MB_CUR_MAX __ctype_get_mb_cur_max()
#elif defined(__CRT_HAVE____mb_cur_max_func)
#define _____mb_cur_max_func_defined
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,___mb_cur_max_func,(void),())
#define __LOCAL_MB_CUR_MAX ((__SIZE_TYPE__)___mb_cur_max_func())
#elif defined(__CRT_HAVE___p___mb_cur_max)
#define ____p___mb_cur_max_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,int *,__NOTHROW,__p___mb_cur_max,(void),())
#define __LOCAL_MB_CUR_MAX ((__SIZE_TYPE__)*__p___mb_cur_max())
#elif defined(__CRT_HAVE___mb_cur_max)
__CSDECLARE(,int,__mb_cur_max)
#define __mb_cur_max       __mb_cur_max
#define __LOCAL_MB_CUR_MAX ((__SIZE_TYPE__)__mb_cur_max)
#else /* __CRT_HAVE___ctype_get_mb_cur_max */
#define __LOCAL_MB_CUR_MAX 7 /* == UNICODE_UTF8_CURLEN */
#endif /* !__CRT_HAVE___ctype_get_mb_cur_max */
__DECL_END
#endif /* !__LOCAL_MB_CUR_MAX */
#endif /* !__LOCAL_MB_CUR_MAX */
