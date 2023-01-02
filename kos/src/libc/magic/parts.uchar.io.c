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

%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]

%[insert:prefix(
#include <features.h>
)]%{
#ifndef _IO_H
#include <io.h>
#endif /* !_IO_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

#ifdef __CC__
__SYSDECL_BEGIN

/************************************************************************/
/* WARNING: UTF-16 functions use DOS paths under `DOSFS_ENABLED'        */
/*          s.a. `dosfs_setenabled(3)'                                  */
/************************************************************************/

struct _c16finddata32_t;
struct _c16finddata64_t;
struct _c16finddata32i64_t;
struct _c16finddata64i32_t;
struct _c32finddata32_t;
struct _c32finddata64_t;
struct _c32finddata32i64_t;
struct _c32finddata64i32_t;

}

%[insert:function(_c16access = c16access)]
%[insert:function(_c32access = c32access)]
%[insert:function(_c16chmod = c16chmod)]
%[insert:function(_c32chmod = c32chmod)]
%[insert:function(_c16creat = c16creat)]
%[insert:function(_c32creat = c32creat)]
%[insert:function(_c16unlink = c16unlink)]
%[insert:function(_c32unlink = c32unlink)]
%[insert:function(_c16rename = c16rename)]
%[insert:function(_c32rename = c32rename)]
%[insert:function(_c16open = c16open)]
%[insert:function(_c32open = c32open)]


_c16access_s(*) %{uchar16("_waccess_s")}
_c32access_s(*) %{uchar32("_waccess_s")}
_c16mktemp_s(*) %{uchar16("_wmktemp_s")}
_c32mktemp_s(*) %{uchar32("_wmktemp_s")}
_c16mktemp(*) %{uchar16("_wmktemp")}
_c32mktemp(*) %{uchar32("_wmktemp")}
_c16sopen_s(*) %{uchar16("_wsopen_s")}
_c32sopen_s(*) %{uchar32("_wsopen_s")}
_c16sopen_dispatch(*) %{uchar16("_wsopen_dispatch")}
_c32sopen_dispatch(*) %{uchar32("_wsopen_dispatch")}
_c16sopen(*) %{uchar16("_wsopen")}
_c32sopen(*) %{uchar32("_wsopen")}
_c16findfirst32(*) %{uchar16("_wfindfirst32")}
_c32findfirst32(*) %{uchar32("_wfindfirst32")}
_c16findfirst32i64(*) %{uchar16("_wfindfirst32i64")}
_c32findfirst32i64(*) %{uchar32("_wfindfirst32i64")}
_c16findfirst64(*) %{uchar16("_wfindfirst64")}
_c32findfirst64(*) %{uchar32("_wfindfirst64")}
_c16findnext32(*) %{uchar16("_wfindnext32")}
_c32findnext32(*) %{uchar32("_wfindnext32")}
_c16findnext32i64(*) %{uchar16("_wfindnext32i64")}
_c32findnext32i64(*) %{uchar32("_wfindnext32i64")}
_c16findnext64(*) %{uchar16("_wfindnext64")}
_c32findnext64(*) %{uchar32("_wfindnext64")}

%[insert:function(_c16findfirst64i32 = _c16findfirst64)]
%[insert:function(_c32findfirst64i32 = _c32findfirst64)]
%[insert:function(_c16findnext64i32 = _c16findnext64)]
%[insert:function(_c32findnext64i32 = _c32findnext64)]


%{

#ifndef _C16FINDDATA_T_DEFINED
#define _C16FINDDATA_T_DEFINED 1
/* Safely first! */
}%[push_macro @undef { attrib time_create time_access time_write size name }]%{
struct _c16finddata32_t {
	__UINT32_TYPE__      attrib;
	__INT32_TYPE__       time_create;
	__INT32_TYPE__       time_access;
	__INT32_TYPE__       time_write;
	_fsize_t             size;
	char16_t             name[260];
};
struct _c16finddata32i64_t {
	__UINT32_TYPE__      attrib;
	__INT32_TYPE__       time_create;
	__INT32_TYPE__       time_access;
	__INT32_TYPE__       time_write;
	__INT64_TYPE__       size;
	char16_t             name[260];
};
struct _c16finddata64i32_t {
	__UINT32_TYPE__      attrib;
	__INT64_TYPE__       time_create;
	__INT64_TYPE__       time_access;
	__INT64_TYPE__       time_write;
	union {
		_fsize_t         size;
		__INT64_TYPE__ __pad; /* I think this is correct? */
	};
	char16_t             name[260];
};
struct _c16finddata64_t {
	__UINT32_TYPE__      attrib;
	__INT64_TYPE__       time_create;
	__INT64_TYPE__       time_access;
	__INT64_TYPE__       time_write;
	__INT64_TYPE__       size;
	char16_t             name[260];
};
struct _c32finddata32_t {
	__UINT32_TYPE__      attrib;
	__INT32_TYPE__       time_create;
	__INT32_TYPE__       time_access;
	__INT32_TYPE__       time_write;
	_fsize_t             size;
	char32_t             name[260];
};
struct _c32finddata32i64_t {
	__UINT32_TYPE__      attrib;
	__INT32_TYPE__       time_create;
	__INT32_TYPE__       time_access;
	__INT32_TYPE__       time_write;
	__INT64_TYPE__       size;
	char32_t             name[260];
};
struct _c32finddata64i32_t {
	__UINT32_TYPE__      attrib;
	__INT64_TYPE__       time_create;
	__INT64_TYPE__       time_access;
	__INT64_TYPE__       time_write;
	union {
		_fsize_t         size;
		__INT64_TYPE__ __pad; /* I think this is correct? */
	};
	char32_t             name[260];
};
struct _c32finddata64_t {
	__UINT32_TYPE__      attrib;
	__INT64_TYPE__       time_create;
	__INT64_TYPE__       time_access;
	__INT64_TYPE__       time_write;
	__INT64_TYPE__       size;
	char32_t             name[260];
};
}%[pop_macro]%{

#ifdef __USE_TIME_BITS64
#define _c16finddata_t                       _c16finddata64i32_t
#define _c16finddatai64_t                    _c16finddata64_t
#define _c16findfirst(filename, finddata)    _c16findfirst64i32(filename, finddata)
#define _c16findnext(findfd, finddata)       _c16findnext64i32(findfd, finddata)
#define _c16findfirsti64(filename, finddata) _c16findfirst64(filename, finddata)
#define _c16findnexti64(findfd, finddata)    _c16findnext64(findfd, finddata)
#define _c32finddata_t                       _c32finddata64i32_t
#define _c32finddatai64_t                    _c32finddata64_t
#define _c32findfirst(filename, finddata)    _c32findfirst64i32(filename, finddata)
#define _c32findnext(findfd, finddata)       _c32findnext64i32(findfd, finddata)
#define _c32findfirsti64(filename, finddata) _c32findfirst64(filename, finddata)
#define _c32findnexti64(findfd, finddata)    _c32findnext64(findfd, finddata)
#else /* __USE_TIME_BITS64 */
#define _c16finddata_t                       _c16finddata32_t
#define _c16finddatai64_t                    _c16finddata32i64_t
#define _c16findfirst(filename, finddata)    _c16findfirst32(filename, finddata)
#define _c16findnext(findfd, finddata)       _c16findnext32(findfd, finddata)
#define _c16findfirsti64(filename, finddata) _c16findfirst32i64(filename, finddata)
#define _c16findnexti64(findfd, finddata)    _c16findnext32i64(findfd, finddata)
#define _c32finddata_t                       _c32finddata32_t
#define _c32finddatai64_t                    _c32finddata32i64_t
#define _c32findfirst(filename, finddata)    _c32findfirst32(filename, finddata)
#define _c32findnext(findfd, finddata)       _c32findnext32(findfd, finddata)
#define _c32findfirsti64(filename, finddata) _c32findfirst32i64(filename, finddata)
#define _c32findnexti64(findfd, finddata)    _c32findnext32i64(findfd, finddata)
#endif /* !__USE_TIME_BITS64 */
#endif /* !_C16FINDDATA_T_DEFINED */

__SYSDECL_END
#endif /* __CC__ */

}
