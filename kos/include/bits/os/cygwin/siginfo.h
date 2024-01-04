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
#ifndef _BITS_OS_CYGWIN_SIGINFO_H
#define _BITS_OS_CYGWIN_SIGINFO_H 1

/* File:
 *    <bits/os/cygwin/siginfo.h>
 *
 * Definitions:
 *    - struct __siginfo_cygwin_struct { ... };
 *    - #define __SI_CYGWIN_MAX_SIZE ...
 * #ifdef __CRT_CYG_PRIMARY
 *    - struct __siginfo_struct { ... };
 *    - #define __SI_MAX_SIZE ...
 * #endif
 */

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/os/sigval.h> /* union sigval */
#include <bits/types.h>

#ifdef __CRT_CYG_PRIMARY
#define __siginfo_cygwin_struct __siginfo_struct
#define __SI_MAX_SIZE           __SI_CYGWIN_MAX_SIZE
#define __SI_PAD_SIZE           __SI_CYGWIN_PAD_SIZE
#endif /* __CRT_CYG_PRIMARY */


#define __SI_CYGWIN_MAX_SIZE    128
#define __SI_CYGWIN_PAD_SIZE   (__SI_CYGWIN_MAX_SIZE / 4)

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PACK
#pragma pack(push, 4)
#endif /* __COMPILER_HAVE_PRAGMA_PACK */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("_sigcommune")
#pragma push_macro("_si_code")
#pragma push_macro("_si_read_handle")
#pragma push_macro("_si_write_handle")
#pragma push_macro("_si_process_handle")
#pragma push_macro("_si_fd")
#pragma push_macro("_si_pipe_unique_id")
#pragma push_macro("_si_str")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#undef _sigcommune
#undef _si_code
#undef _si_read_handle
#undef _si_write_handle
#undef _si_process_handle
#undef _si_fd
#undef _si_pipe_unique_id
#undef _si_str

struct __ATTR_PACKED _sigcommune {
	__uint32_t       _si_code;
	void            *_si_read_handle;
	void            *_si_write_handle;
	void            *_si_process_handle;
	union __ATTR_PACKED {
		__INT32_TYPE__ _si_fd;
		__int64_t      _si_pipe_unique_id;
		char          *_si_str;
	};
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("_si_str")
#pragma pop_macro("_si_pipe_unique_id")
#pragma pop_macro("_si_fd")
#pragma pop_macro("_si_process_handle")
#pragma pop_macro("_si_write_handle")
#pragma pop_macro("_si_read_handle")
#pragma pop_macro("_si_code")
#pragma pop_macro("_sigcommune")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */


#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("si_signo")
#pragma push_macro("si_code")
#pragma push_macro("si_pid")
#pragma push_macro("si_uid")
#pragma push_macro("si_errno")
#pragma push_macro("_si_data")
#pragma push_macro("_si_commune")
#pragma push_macro("si_sigval")
#pragma push_macro("si_value")
#pragma push_macro("si_tid")
#pragma push_macro("si_overrun")
#pragma push_macro("si_status")
#pragma push_macro("si_utime")
#pragma push_macro("si_stime")
#pragma push_macro("si_addr")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#undef si_signo
#undef si_code
#undef si_pid
#undef si_uid
#undef si_errno
#undef _si_data
#undef _si_commune
#undef si_sigval
#undef si_value
#undef si_tid
#undef si_overrun
#undef si_status
#undef si_utime
#undef si_stime
#undef si_addr
struct __ATTR_PACKED __siginfo_cygwin_struct /*[NAME(siginfo_cygwin)][PREFIX(si_)]*/ {
	__INT32_TYPE__ si_signo;
	__INT32_TYPE__ si_code;
	__pid_t        si_pid;
	__uid_t        si_uid;
	__INT32_TYPE__ si_errno;
	union __ATTR_PACKED {
		__uint32_t _si_data[__SI_CYGWIN_PAD_SIZE];
		struct _sigcommune _si_commune;
		struct __ATTR_PACKED {
			union __ATTR_PACKED {
				union sigval si_sigval;
				union sigval si_value;
			};
			__timer_t       si_tid;
			__UINT32_TYPE__ si_overrun;
		};
		struct __ATTR_PACKED {
			__INT32_TYPE__  si_status;
			__clock_t       si_utime;
			__clock_t       si_stime;
		};
		void               *si_addr;
	};
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("si_addr")
#pragma pop_macro("si_stime")
#pragma pop_macro("si_utime")
#pragma pop_macro("si_status")
#pragma pop_macro("si_overrun")
#pragma pop_macro("si_tid")
#pragma pop_macro("si_value")
#pragma pop_macro("si_sigval")
#pragma pop_macro("_si_commune")
#pragma pop_macro("_si_data")
#pragma pop_macro("si_errno")
#pragma pop_macro("si_uid")
#pragma pop_macro("si_pid")
#pragma pop_macro("si_code")
#pragma pop_macro("si_signo")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#ifdef __COMPILER_HAVE_PRAGMA_PACK
#pragma pack(pop)
#endif /* __COMPILER_HAVE_PRAGMA_PACK */

__DECL_END
#endif /* __CC__ */


#endif /* !_BITS_OS_CYGWIN_SIGINFO_H */
