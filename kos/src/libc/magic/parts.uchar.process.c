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
%[define_replacement(pid_t = __pid_t)]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#ifndef _PROCESS_H
#include <process.h>
#endif /* !_PROCESS_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

#ifdef __CC__
__SYSDECL_BEGIN

/************************************************************************/
/* WARNING: UTF-16 functions use DOS paths under `DOSFS_ENABLED'        */
/*          s.a. `dosfs_setenabled(3)'                                  */
/************************************************************************/

}

%[define_wchar_replacement(__TWARGV = __T16ARGV, __T32ARGV)]
%[define_wchar_replacement(__TWENVP = __T16ENVP, __T32ENVP)]

%[define_type_class(__T16ARGV = "TP")]
%[define_type_class(__T16ENVP = "TP")]
%[define_type_class(__T32ARGV = "TP")]
%[define_type_class(__T32ENVP = "TP")]

%{
#ifndef __T16ARGV
#ifdef __USE_DOS_ALTERATIONS
#define __T16ARGV char16_t const *const *__restrict ___argv
#define __T16ENVP char16_t const *const *__restrict ___envp
#else /* __USE_DOS_ALTERATIONS */
#define __T16ARGV char16_t *const ___argv[__restrict_arr]
#define __T16ENVP char16_t *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__T16ARGV */
#ifndef __T32ARGV
#ifdef __USE_DOS_ALTERATIONS
#define __T32ARGV char32_t const *const *__restrict ___argv
#define __T32ENVP char32_t const *const *__restrict ___envp
#else /* __USE_DOS_ALTERATIONS */
#define __T32ARGV char32_t *const ___argv[__restrict_arr]
#define __T32ENVP char32_t *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__T32ARGV */
}

c16execv(*) %{uchar16("wexecv")}
c32execv(*) %{uchar32("wexecv")}
c16execve(*) %{uchar16("wexecve")}
c32execve(*) %{uchar32("wexecve")}
c16execvp(*) %{uchar16("wexecvp")}
c32execvp(*) %{uchar32("wexecvp")}
c16execvpe(*) %{uchar16("wexecvpe")}
c32execvpe(*) %{uchar32("wexecvpe")}
c16execl(*) %{uchar16("wexecl")}
c32execl(*) %{uchar32("wexecl")}
c16execlp(*) %{uchar16("wexeclp")}
c32execlp(*) %{uchar32("wexeclp")}
c16execle(*) %{uchar16("wexecle")}
c32execle(*) %{uchar32("wexecle")}
c16execlpe(*) %{uchar16("wexeclpe")}
c32execlpe(*) %{uchar32("wexeclpe")}

c16spawnv(*) %{uchar16("wspawnv")}
c32spawnv(*) %{uchar32("wspawnv")}
c16spawnve(*) %{uchar16("wspawnve")}
c32spawnve(*) %{uchar32("wspawnve")}
c16spawnvp(*) %{uchar16("wspawnvp")}
c32spawnvp(*) %{uchar32("wspawnvp")}
c16spawnvpe(*) %{uchar16("wspawnvpe")}
c32spawnvpe(*) %{uchar32("wspawnvpe")}
c16spawnl(*) %{uchar16("wspawnl")}
c32spawnl(*) %{uchar32("wspawnl")}
c16spawnlp(*) %{uchar16("wspawnlp")}
c32spawnlp(*) %{uchar32("wspawnlp")}
c16spawnle(*) %{uchar16("wspawnle")}
c32spawnle(*) %{uchar32("wspawnle")}
c16spawnlpe(*) %{uchar16("wspawnlpe")}
c32spawnlpe(*) %{uchar32("wspawnlpe")}

%[insert:extern(c16system)]
%[insert:extern(c32system)]

%{

__SYSDECL_END
#endif /* __CC__ */

}
