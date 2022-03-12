/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

/* This right here allows headers to assume that stuff like open64() doesn't do
 * anything  and   can   also   be  resolved   by   linking   against   open(). */
#define __O_LARGEFILE 0

/* KOS */
#include "kos.h"

#define __CRT_DOS
#undef __CRT_DOS_PRIMARY
#define __CRT_GLC
#undef __CRT_GLC_PRIMARY
#define __CRT_KOS
#define __CRT_KOS_PRIMARY
#undef __CRT_CYG
#undef __CRT_CYG_PRIMARY
#undef __CRT_GENERIC
#undef __CRT_KOS_KERNEL
#undef __CRT_FREESTANDING
#undef __LIBC_BIND_CRTBUILTINS
#undef _WIN32

#define ____PRIVATE_VREDIRECT_UNPACK(...) __VA_ARGS__
#define __CASMNAME __asm__
#define __CASMNAME_SAME(x)
#define __CASMNAME_DOS(x) __asm__("DOS$" x)
#define __CASMNAME_KOS __asm__
#define __CASMNAME_DOS_SAME(x) __asm__("DOS$" x)
#define __CASMNAME_KOS_SAME(x)
#define __CDECLARE(attr,Treturn,nothrow,name,param,args)                                                __LIBC attr Treturn nothrow(__LIBCCALL name) param;
#define __CDECLARE_VOID(attr,nothrow,name,param,args)                                                   __LIBC attr void nothrow(__LIBCCALL name) param;
#define __CREDIRECT(attr,Treturn,nothrow,name,param,asmname,args)                                       __LIBC attr Treturn nothrow(__LIBCCALL name) param __asm__(#asmname);
#define __CREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args)                                   __LIBC attr Treturn nothrow(__LIBDCALL name) param __asm__("DOS$" #asmname);
#define __CREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,args)                                   __LIBC attr Treturn nothrow(__LIBKCALL name) param __asm__(#asmname);
#define __CREDIRECT_VOID(attr,nothrow,name,param,asmname,args)                                          __LIBC attr void nothrow(__LIBCCALL name) param __asm__(#asmname);
#define __CREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args)                                      __LIBC attr void nothrow(__LIBDCALL name) param __asm__("DOS$" #asmname);
#define __CREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,args)                                      __LIBC attr void nothrow(__LIBKCALL name) param __asm__(#asmname);
#define __CVREDIRECT(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)    __LIBC attr Treturn nothrow(__LIBCCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __asm__(#asmname);
#define __CVREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) __LIBC attr Treturn nothrow(__LIBDCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __asm__("DOS$" #asmname);
#define __CVREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) __LIBC attr Treturn nothrow(__LIBKCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __asm__(#asmname);
#define __CVREDIRECT_VOID(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)       __LIBC attr void nothrow(__LIBCCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __asm__(#asmname);
#define __CVREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   __LIBC attr void nothrow(__LIBDCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __asm__("DOS$" #asmname);
#define __CVREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   __LIBC attr void nothrow(__LIBKCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __asm__(#asmname);
#define __CVFREDIRECT(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __LIBC attr Treturn nothrow(__VLIBCCALL name) paramf __asm__(#asmname);
#define __CVFREDIRECT_DOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __LIBC attr Treturn nothrow(__VLIBDCALL name) paramf __asm__("DOS$" #asmname);
#define __CVFREDIRECT_KOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __LIBC attr Treturn nothrow(__VLIBKCALL name) paramf __asm__(#asmname);
#define __CVFREDIRECT_VOID(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)    __LIBC attr void nothrow(__VLIBCCALL name) paramf __asm__(#asmname);
#define __CVFREDIRECT_VOID_DOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __LIBC attr void nothrow(__VLIBDCALL name) paramf __asm__("DOS$" #asmname);
#define __CVFREDIRECT_VOID_KOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __LIBC attr void nothrow(__VLIBKCALL name) paramf __asm__(#asmname);
#define __CXREDIRECT(attr,Treturn,nothrow,name,param,asmname,code)                                      __LIBC attr Treturn nothrow(__LIBCCALL name) param __asm__(#asmname);
#define __CXREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,code)                                  __LIBC attr Treturn nothrow(__LIBDCALL name) param __asm__("DOS$" #asmname);
#define __CXREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,code)                                  __LIBC attr Treturn nothrow(__LIBKCALL name) param __asm__(#asmname);
#define __CXREDIRECT_VOID(attr,nothrow,name,param,asmname,code)                                         __LIBC attr void nothrow(__LIBCCALL name) param __asm__(#asmname);
#define __CXREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,code)                                     __LIBC attr void nothrow(__LIBDCALL name) param __asm__("DOS$" #asmname);
#define __CXREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,code)                                     __LIBC attr void nothrow(__LIBKCALL name) param __asm__(#asmname);
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,...)                                               __LIBC attr Treturn nothrow(__LIBCCALL name) param;
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)                                           __LIBC attr Treturn nothrow(__LIBDCALL name) param;
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)                                           __LIBC attr Treturn nothrow(__LIBKCALL name) param;
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,...)                                      __LIBC attr Treturn nothrow(__LIBCCALL name) param;
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...)                                  __LIBC attr Treturn nothrow(__LIBDCALL name) param;
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...)                                  __LIBC attr Treturn nothrow(__LIBKCALL name) param;

#define __CDECLARE_OPT(attr,Treturn,nothrow,name,param,args) __CDECLARE(attr,Treturn,nothrow,name,param,args)
#define __CDECLARE_VOID_OPT(attr,nothrow,name,param,args) __CDECLARE_VOID(attr,nothrow,name,param,args)
#define __CDECLARE_GCCNCX_OPT(attr,Treturn,nothrow,name,param,args) __CDECLARE_GCCNCX(attr,Treturn,nothrow,name,param,args)
#define __CDECLARE_VOID_GCCNCX_OPT(attr,nothrow,name,param,args) __CDECLARE_VOID_GCCNCX(attr,nothrow,name,param,args)
