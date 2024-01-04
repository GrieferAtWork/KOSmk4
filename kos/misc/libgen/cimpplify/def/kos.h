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

/* KOS */

#define __unix 1
#define __unix__ 1

#define __KOS__ 1

#undef linux
#undef __linux
#undef __linux__

#undef __NO_KOS_SYSTEM_HEADERS__
#define __KOS_SYSTEM_HEADERS__

#define __LIBCCALL_IS_LIBKCALL
#define __VLIBCCALL_IS_VLIBKCALL
#define __LIBCCALL __LIBKCALL
#define __VLIBCCALL __VLIBKCALL

#define __KOS_VERSION__ 400
#undef __PE__
#define __ELF__ 1

#pragma defined __O_ACCMODE
#pragma defined __O_RDONLY
#pragma defined __O_WRONLY
#pragma defined __O_RDWR
#pragma defined __O_ACCMODE_INVALID
#pragma defined __O_CREAT
#pragma defined __O_EXCL
#pragma defined __O_NOCTTY
#pragma defined __O_TRUNC
#pragma defined __O_APPEND
#pragma defined __O_NONBLOCK
#pragma defined __O_SYNC
#pragma defined __O_DSYNC
#pragma defined __O_ASYNC
#pragma defined __O_DIRECT
#pragma defined __O_LARGEFILE
#pragma defined __O_DIRECTORY
#pragma defined __O_NOFOLLOW
#pragma defined __O_NOATIME
#pragma defined __O_CLOEXEC
#pragma defined __O_PATH
#pragma defined __O_TMPFILE
#pragma defined __O_CLOFORK
#pragma defined __O_DOSPATH


#pragma defined ___IOFBF
#pragma defined ___IOLBF
#pragma defined ___IONBF
#pragma defined __BUFSIZ
#pragma defined __EOF
#pragma defined __WEOF16
#pragma defined __WEOF32
#pragma defined __WEOF
#pragma defined __L_tmpnam
#pragma defined __FILENAME_MAX
#pragma defined __TMP_MAX
#pragma defined __FOPEN_MAX
#pragma defined __L_ctermid
#pragma defined __L_cuserid

#pragma defined __SEEK_SET
#pragma defined __SEEK_CUR
#pragma defined __SEEK_END
#pragma defined __SEEK_DATA
#pragma defined __SEEK_HOLE
#pragma defined __RENAME_NOREPLACE
#pragma defined __RENAME_EXCHANGE
#pragma defined __RENAME_WHITEOUT
#pragma defined __RENAME_MOVETODIR
