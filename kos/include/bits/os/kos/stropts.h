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
#ifndef _BITS_OS_KOS_STROPTS_H
#define _BITS_OS_KOS_STROPTS_H 1

#include <__stdinc.h>

#include <asm/os/kos/stropts.h> /* __FMNAMESZ */
#include <bits/types.h>

#define __SIZEOF_T_SCALAR_T__ 4

#ifdef __CC__
__DECL_BEGIN

#define __t_scalar_t  __LONG32_TYPE__
#define __t_uscalar_t __ULONG32_TYPE__

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("bandinfo")
#pragma push_macro("bi_pri")
#pragma push_macro("bi_flag")
#pragma push_macro("strbuf")
#pragma push_macro("maxlen")
#pragma push_macro("len")
#pragma push_macro("buf")
#pragma push_macro("strpeek")
#pragma push_macro("ctlbuf")
#pragma push_macro("databuf")
#pragma push_macro("flags")
#pragma push_macro("strfdinsert")
#pragma push_macro("fildes")
#pragma push_macro("offset")
#pragma push_macro("strioctl")
#pragma push_macro("ic_cmd")
#pragma push_macro("ic_timout")
#pragma push_macro("ic_len")
#pragma push_macro("ic_dp")
#pragma push_macro("strrecvfd")
#pragma push_macro("fd")
#pragma push_macro("uid")
#pragma push_macro("gid")
#pragma push_macro("str_mlist")
#pragma push_macro("l_name")
#pragma push_macro("str_list")
#pragma push_macro("sl_modlist")
#pragma push_macro("sl_nmods")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#undef bandinfo
#undef bi_pri
#undef bi_flag
#undef strbuf
#undef maxlen
#undef len
#undef buf
#undef strpeek
#undef ctlbuf
#undef databuf
#undef flags
#undef strfdinsert
#undef fildes
#undef offset
#undef strioctl
#undef ic_cmd
#undef ic_timout
#undef ic_len
#undef ic_dp
#undef strrecvfd
#undef fd
#undef uid
#undef gid
#undef str_mlist
#undef l_name
#undef str_list
#undef sl_nmods
#undef sl_modlist

/* Structured pointed to by the arg of the `I_FLUSHBAND' ioctl. */
struct bandinfo {
	unsigned char bi_pri;  /* ??? */
#if __SIZEOF_INT__ > 1
	unsigned char __bi_pad[(sizeof(int) / sizeof(unsigned char)) - 1];
#endif /* __SIZEOF_INT__ > 1 */
	int           bi_flag; /* ??? */
};

struct strbuf {
	int   maxlen; /* ??? */
	int   len;    /* ??? */
	char *buf;    /* ??? */
};

struct strpeek {
	struct strbuf ctlbuf;  /* ??? */
	struct strbuf databuf; /* ??? */
	__t_uscalar_t flags;   /* ??? */
};

struct strfdinsert {
	struct strbuf ctlbuf;  /* ??? */
	struct strbuf databuf; /* ??? */
	__t_uscalar_t flags;   /* ??? */
	__fd_t        fildes;  /* ??? */
	int           offset;  /* ??? */
};

struct strioctl {
	int        ic_cmd;    /* ??? */
	int        ic_timout; /* ??? */
	int        ic_len;    /* ??? */
#if ((__SIZEOF_INT__ * 3) % __SIZEOF_POINTER__) != 0
	__byte_t __ic_pad[__SIZEOF_POINTER__ - ((__SIZEOF_INT__ * 3) % __SIZEOF_POINTER__)];
#endif /* ((__SIZEOF_INT__ * 3) % __SIZEOF_POINTER__) != 0 */
	char      *ic_dp;     /* ??? */
};

struct strrecvfd {
	__fd_t  fd;        /* ??? */
	__uid_t uid;       /* ??? */
	__gid_t gid;       /* ??? */
	char    __fill[8]; /* ??? */
};

struct str_mlist {
	char l_name[__FMNAMESZ + 1]; /* ??? */
};

struct str_list {
	int               sl_nmods;   /* ??? */
#if __SIZEOF_INT__ < __SIZEOF_POINTER__
	__byte_t        __sl_pad[__SIZEOF_POINTER__ - __SIZEOF_INT__];
#endif /* __SIZEOF_INT__ < __SIZEOF_POINTER__ */
	struct str_mlist *sl_modlist; /* ??? */
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("sl_nmods")
#pragma pop_macro("sl_modlist")
#pragma pop_macro("str_list")
#pragma pop_macro("l_name")
#pragma pop_macro("str_mlist")
#pragma pop_macro("gid")
#pragma pop_macro("uid")
#pragma pop_macro("fd")
#pragma pop_macro("strrecvfd")
#pragma pop_macro("ic_dp")
#pragma pop_macro("ic_len")
#pragma pop_macro("ic_timout")
#pragma pop_macro("ic_cmd")
#pragma pop_macro("strioctl")
#pragma pop_macro("offset")
#pragma pop_macro("fildes")
#pragma pop_macro("strfdinsert")
#pragma pop_macro("flags")
#pragma pop_macro("databuf")
#pragma pop_macro("ctlbuf")
#pragma pop_macro("strpeek")
#pragma pop_macro("buf")
#pragma pop_macro("len")
#pragma pop_macro("maxlen")
#pragma pop_macro("strbuf")
#pragma pop_macro("bi_flag")
#pragma pop_macro("bi_pri")
#pragma pop_macro("bandinfo")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_STROPTS_H */
