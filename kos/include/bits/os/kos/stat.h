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
#ifndef _BITS_OS_KOS_STAT_H
#define _BITS_OS_KOS_STAT_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/os/timespec.h>
#include <bits/types.h>

#ifdef __KOS__
#define __kos_stat                stat
#define __OFFSET_STAT_DEV         __OFFSET_KOS_STAT_DEV
#define __OFFSET_STAT_INO         __OFFSET_KOS_STAT_INO
#define __OFFSET_STAT_MODE        __OFFSET_KOS_STAT_MODE
#define __OFFSET_STAT_NLINK       __OFFSET_KOS_STAT_NLINK
#define __OFFSET_STAT_UID         __OFFSET_KOS_STAT_UID
#define __OFFSET_STAT_GID         __OFFSET_KOS_STAT_GID
#define __OFFSET_STAT_RDEV        __OFFSET_KOS_STAT_RDEV
#define __OFFSET_STAT_SIZE        __OFFSET_KOS_STAT_SIZE
#define __OFFSET_STAT_BLKSIZE     __OFFSET_KOS_STAT_BLKSIZE
#define __OFFSET_STAT_BLOCKS      __OFFSET_KOS_STAT_BLOCKS
#define __OFFSET_STAT_ATIME       __OFFSET_KOS_STAT_ATIME
#define __OFFSET_STAT_ATIME32     __OFFSET_KOS_STAT_ATIME
#define __OFFSET_STAT_ATIME64     __OFFSET_KOS_STAT_ATIME
#define __OFFSET_STAT_ATIMENSEC   __OFFSET_KOS_STAT_ATIMENSEC
#define __OFFSET_STAT_MTIME       __OFFSET_KOS_STAT_MTIME
#define __OFFSET_STAT_MTIME32     __OFFSET_KOS_STAT_MTIME
#define __OFFSET_STAT_MTIME64     __OFFSET_KOS_STAT_MTIME
#define __OFFSET_STAT_MTIMENSEC   __OFFSET_KOS_STAT_MTIMENSEC
#define __OFFSET_STAT_CTIME       __OFFSET_KOS_STAT_CTIME
#define __OFFSET_STAT_CTIME32     __OFFSET_KOS_STAT_CTIME
#define __OFFSET_STAT_CTIME64     __OFFSET_KOS_STAT_CTIME
#define __OFFSET_STAT_CTIMENSEC   __OFFSET_KOS_STAT_CTIMENSEC
#define __OFFSET_STAT_BTIME       __OFFSET_KOS_STAT_BTIME
#define __OFFSET_STAT_BTIME32     __OFFSET_KOS_STAT_BTIME
#define __OFFSET_STAT_BTIME64     __OFFSET_KOS_STAT_BTIME
#define __OFFSET_STAT_BTIMENSEC   __OFFSET_KOS_STAT_BTIMENSEC
#define __SIZEOF_STAT             __SIZEOF_KOS_STAT
#define __OFFSET_STAT_ATIMESPEC64 __OFFSET_KOS_STAT_ATIMESPEC
#define __OFFSET_STAT_MTIMESPEC64 __OFFSET_KOS_STAT_MTIMESPEC
#define __OFFSET_STAT_CTIMESPEC64 __OFFSET_KOS_STAT_CTIMESPEC
#define __OFFSET_STAT_BTIMESPEC64 __OFFSET_KOS_STAT_BTIMESPEC
#if defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define __OFFSET_STAT_ATIMESPEC __OFFSET_KOS_STAT_ATIMESPEC
#define __OFFSET_STAT_MTIMESPEC __OFFSET_KOS_STAT_MTIMESPEC
#define __OFFSET_STAT_CTIMESPEC __OFFSET_KOS_STAT_CTIMESPEC
#define __OFFSET_STAT_BTIMESPEC __OFFSET_KOS_STAT_BTIMESPEC
#endif /* __USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define __OFFSET_STAT_ATIMESPEC32 __OFFSET_KOS_STAT_ATIMESPEC
#define __OFFSET_STAT_MTIMESPEC32 __OFFSET_KOS_STAT_MTIMESPEC
#define __OFFSET_STAT_CTIMESPEC32 __OFFSET_KOS_STAT_CTIMESPEC
#define __OFFSET_STAT_BTIMESPEC32 __OFFSET_KOS_STAT_BTIMESPEC
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */

/* Define macros for available stat features. */
#if defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#ifdef __USE_XOPEN2K8
#define _STATBUF_ST_TIM 1
#endif /* __USE_XOPEN2K8 */
#define _STATBUF_ST_TIMESPEC 1 /* Apple extension? */
#endif /* __USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#define _STATBUF_ST_TIME     1 /* Always defined. */
#define _STATBUF_ST_NSEC     1
#define _STATBUF_ST_BLKSIZE  1
#define _STATBUF_ST_RDEV     1
#define _STATBUF_ST_BLOCKS   1
#ifdef __USE_KOS
#define _STATBUF_ST_INO32    1
#define _STATBUF_ST_INO64    1
#define _STATBUF_ST_SIZE32   1
#define _STATBUF_ST_SIZE64   1
#define _STATBUF_ST_BLOCKS32 1
#define _STATBUF_ST_BLOCKS64 1
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#ifdef __USE_XOPEN2K8
#define _STATBUF_ST_TIM32 1
#endif /* __USE_XOPEN2K8 */
#define _STATBUF_ST_TIMESPEC32 1
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#define _STATBUF_ST_TIME32 1
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_XOPEN2K8
#define _STATBUF_ST_TIM64 1
#endif /* __USE_XOPEN2K8 */
#define _STATBUF_ST_TIMESPEC64 1
#define _STATBUF_ST_TIME64 1
#endif /* __USE_TIME64 */

#ifdef __USE_LARGEFILE64
/* Even though `struct stat64' is the same as `struct stat', we can't
 * simply `#define stat64 stat' because of function definitions using
 * the same name in <sys/stat.h>... */
//#define stat64 stat
#define __kos_stat_alias64          stat64
#define __stat64                    stat64
#define __OFFSET_STAT64_DEV         __OFFSET_KOS_STAT_DEV
#define __OFFSET_STAT64_INO         __OFFSET_KOS_STAT_INO
#define __OFFSET_STAT64_MODE        __OFFSET_KOS_STAT_MODE
#define __OFFSET_STAT64_NLINK       __OFFSET_KOS_STAT_NLINK
#define __OFFSET_STAT64_UID         __OFFSET_KOS_STAT_UID
#define __OFFSET_STAT64_GID         __OFFSET_KOS_STAT_GID
#define __OFFSET_STAT64_RDEV        __OFFSET_KOS_STAT_RDEV
#define __OFFSET_STAT64_SIZE        __OFFSET_KOS_STAT_SIZE
#define __OFFSET_STAT64_BLKSIZE     __OFFSET_KOS_STAT_BLKSIZE
#define __OFFSET_STAT64_BLOCKS      __OFFSET_KOS_STAT_BLOCKS
#define __OFFSET_STAT64_ATIME       __OFFSET_KOS_STAT_ATIME
#define __OFFSET_STAT64_ATIME32     __OFFSET_KOS_STAT_ATIME
#define __OFFSET_STAT64_ATIME64     __OFFSET_KOS_STAT_ATIME
#define __OFFSET_STAT64_ATIMENSEC   __OFFSET_KOS_STAT_ATIMENSEC
#define __OFFSET_STAT64_MTIME       __OFFSET_KOS_STAT_MTIME
#define __OFFSET_STAT64_MTIME32     __OFFSET_KOS_STAT_MTIME
#define __OFFSET_STAT64_MTIME64     __OFFSET_KOS_STAT_MTIME
#define __OFFSET_STAT64_MTIMENSEC   __OFFSET_KOS_STAT_MTIMENSEC
#define __OFFSET_STAT64_CTIME       __OFFSET_KOS_STAT_CTIME
#define __OFFSET_STAT64_CTIME32     __OFFSET_KOS_STAT_CTIME
#define __OFFSET_STAT64_CTIME64     __OFFSET_KOS_STAT_CTIME
#define __OFFSET_STAT64_CTIMENSEC   __OFFSET_KOS_STAT_CTIMENSEC
#define __OFFSET_STAT64_BTIME       __OFFSET_KOS_STAT_BTIME
#define __OFFSET_STAT64_BTIME32     __OFFSET_KOS_STAT_BTIME
#define __OFFSET_STAT64_BTIME64     __OFFSET_KOS_STAT_BTIME
#define __OFFSET_STAT64_BTIMENSEC   __OFFSET_KOS_STAT_BTIMENSEC
#define __SIZEOF_STAT64             __SIZEOF_KOS_STAT
#define __OFFSET_STAT64_ATIMESPEC64 __OFFSET_KOS_STAT_ATIMESPEC
#define __OFFSET_STAT64_MTIMESPEC64 __OFFSET_KOS_STAT_MTIMESPEC
#define __OFFSET_STAT64_CTIMESPEC64 __OFFSET_KOS_STAT_CTIMESPEC
#define __OFFSET_STAT64_BTIMESPEC64 __OFFSET_KOS_STAT_BTIMESPEC
#if defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define __OFFSET_STAT64_ATIMESPEC __OFFSET_KOS_STAT_ATIMESPEC
#define __OFFSET_STAT64_MTIMESPEC __OFFSET_KOS_STAT_MTIMESPEC
#define __OFFSET_STAT64_CTIMESPEC __OFFSET_KOS_STAT_CTIMESPEC
#define __OFFSET_STAT64_BTIMESPEC __OFFSET_KOS_STAT_BTIMESPEC
#endif /* __USE_TIME_BITS64 || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define __OFFSET_STAT64_ATIMESPEC32 __OFFSET_KOS_STAT_ATIMESPEC
#define __OFFSET_STAT64_MTIMESPEC32 __OFFSET_KOS_STAT_MTIMESPEC
#define __OFFSET_STAT64_CTIMESPEC32 __OFFSET_KOS_STAT_CTIMESPEC
#define __OFFSET_STAT64_BTIMESPEC32 __OFFSET_KOS_STAT_BTIMESPEC
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#else /* __USE_LARGEFILE64 */
#define __stat64 stat
#endif /* !__USE_LARGEFILE64 */
#define __STAT32_MATCHES_STAT64
#endif /* __KOS__ */


#define __OFFSET_KOS_STAT_DEV       0
#define __OFFSET_KOS_STAT_INO       8
#define __OFFSET_KOS_STAT_MODE      16
#define __OFFSET_KOS_STAT_NLINK     20
#define __OFFSET_KOS_STAT_UID       24
#define __OFFSET_KOS_STAT_GID       28
#define __OFFSET_KOS_STAT_RDEV      32
#define __OFFSET_KOS_STAT_SIZE      40
#define __OFFSET_KOS_STAT_BLKSIZE   48
#define __OFFSET_KOS_STAT_BLOCKS    56
#define __OFFSET_KOS_STAT_RESERVED1 64 /* [FIELD(__st_reserved1)] */
#define __OFFSET_KOS_STAT_ATIMESPEC 128
#define __OFFSET_KOS_STAT_ATIME     128
#define __OFFSET_KOS_STAT_ATIMENSEC 136
#define __OFFSET_KOS_STAT_MTIMESPEC 144
#define __OFFSET_KOS_STAT_MTIME     144
#define __OFFSET_KOS_STAT_MTIMENSEC 152
#define __OFFSET_KOS_STAT_CTIMESPEC 160
#define __OFFSET_KOS_STAT_CTIME     160
#define __OFFSET_KOS_STAT_CTIMENSEC 168
#define __OFFSET_KOS_STAT_BTIMESPEC 176
#define __OFFSET_KOS_STAT_BTIME     176
#define __OFFSET_KOS_STAT_BTIMENSEC 184
#define __OFFSET_KOS_STAT_RESERVED2 192 /* [FIELD(__st_reserved2)] */
#define __SIZEOF_KOS_STAT           256
#define __ALIGNOF_KOS_STAT          __ALIGNOF_INT64__


#ifdef __CC__
__DECL_BEGIN

#if __SIZEOF_TIME_T__ != __SIZEOF_TIME64_T__
struct __stat_timespec32 /*[PREFIX(tv_)][NAME(stat_timespec32)]*/ {
	__time_t          tv_sec;  /* seconds since 01.01.1970 */
	__byte_t        __tv_pad_sec[__SIZEOF_TIME64_T__ - __SIZEOF_TIME_T__];
	__syscall_ulong_t tv_nsec; /* nanoseconds */
#ifdef __cplusplus
	__CXX_CLASSMEMBER operator timespec(void) const __CXX_NOEXCEPT {
		struct timespec __res;
		__res.tv_sec  = (__time_t)this->tv_sec;
		__res.tv_nsec = this->tv_nsec;
		return __res;
	}
	__CXX_CLASSMEMBER __stat_timespec32 &operator = (struct timespec const &__val) __CXX_NOEXCEPT {
		this->tv_sec  = (__time_t)__val.tv_sec;
		this->tv_nsec = __val.tv_nsec;
		return *this;
	}
#endif /* __cplusplus */
};
#endif /* __SIZEOF_TIME_T__ != __SIZEOF_TIME64_T__ */


/*[[[deemon
import * from deemon;
global final TYPE_WIDTH = 25;
global final NAME_WIDTH = 16;
global final TABSIZE    = 4;
global doStat64 = false;
function _printNameWithComment(name: string, comment: string) {
	print(name, ";"),;
	if (NAME_WIDTH > #name)
		print(" " * (NAME_WIDTH - #name)),;
	print(" /" "* ", comment, " *" "/");
}
function _Tdopadto(name: string, sizeofT: string, wantedSize: string | int, indent: string = "\t") {
	print(indent, "__byte_t".ljust(TYPE_WIDTH - (2 + (TABSIZE * (#indent - 1)))),
		"__st_pad_", name.lsstrip("st_"), "[", wantedSize, " - ", sizeofT, "];");
}
function _Tpadto(name: string, sizeofT: string, wantedSize: string | int, indent: string = "\t") {
	print("#if ", sizeofT, " < ", wantedSize);
	_Tdopadto(name, sizeofT, wantedSize, indent: indent);
	print("#endif /" "* ", sizeofT, " < ", wantedSize, " *" "/");
}
function _printNameWithCommentAndPad(
		name: string, comment: string, sizeofT: string,
		wantedSize: string | int | none, indent: string = "\t") {
	_printNameWithComment(name, comment);
	if (wantedSize !is none)
		_Tpadto(name, sizeofT, wantedSize, indent: indent);
}
function _printNameWithCommentAndForcedPad(
		name: string, comment: string, sizeofT: string,
		wantedSize: string | int | none, indent: string = "\t") {
	_printNameWithComment(name, comment);
	if (wantedSize !is none)
		_Tdopadto(name, sizeofT, wantedSize, indent: indent);
}
function _printTypedNameWithCommentAndPad(
		T: string, name: string, comment: string, sizeofT: string,
		wantedSize: string | int | none, indent: string = "\t") {
	print(indent, T.ljust(TYPE_WIDTH + 4 - (4 * #indent))),;
	_printNameWithCommentAndPad(name, comment, sizeofT, wantedSize, indent: indent);
}
function _printTypedNameWithCommentAndForcedPad(
		T: string, name: string, comment: string, sizeofT: string,
		wantedSize: string | int | none, indent: string = "\t") {
	print(indent, T.ljust(TYPE_WIDTH + 4 - (4 * #indent))),;
	_printNameWithCommentAndForcedPad(name, comment, sizeofT, wantedSize, indent: indent);
}
function Tfield(T: string, name: string, sizeofT: string, wantedSize: string | int | none, comment: string) {
	if (doStat64) {
		if (T.startswith("__FS_TYPE(") && T.endswith(")"))
			T = f"__{T[10:-1]}64_t";
		if (sizeofT.startswith("__FS_SIZEOF(") && sizeofT.endswith(")"))
			sizeofT = f"__SIZEOF_{sizeofT[12:-1]}64_T__";
	}
	if ((T.startswith("__FS_TYPE(") || T.startswith("__TM_TYPE(")) && T.endswith(")"))
		T = f"__{T[10:-1]}_t";
	if ((sizeofT.startswith("__FS_SIZEOF(") || sizeofT.startswith("__TM_SIZEOF(")) && sizeofT.endswith(")"))
		sizeofT = f"__SIZEOF_{sizeofT[12:-1]}_T__";
	_printTypedNameWithCommentAndPad(T, name, comment, sizeofT, wantedSize);
}
function Tfsfield(Tname: string, name: string, comment: string) {
	local SIZEOF_NAME = { "pos" : "off" }.get(Tname, Tname).upper();
	local TX         = f"__FS_TYPE({Tname})";
	local TXS        = f"__{Tname}_t";
	local TX_SIZEOF  = f"__FS_SIZEOF({SIZEOF_NAME})";
	local TXS_SIZEOF = f"__SIZEOF_{SIZEOF_NAME}_T__";
	local T32        = f"__{Tname}32_t";
	local T64        = f"__{Tname}64_t";
	local T32_SIZEOF = f"__SIZEOF_{SIZEOF_NAME}32_TYPE__";
	local T64_SIZEOF = "8";
//	local T64_SIZEOF = f"__SIZEOF_{SIZEOF_NAME}64_TYPE__";
	if (doStat64) {
		print("#ifdef __USE_KOS");
		print("	union {");
		print("		", T64. ljust(TYPE_WIDTH - TABSIZE)),;
		_printNameWithComment(name, comment);
		print("		", T32.ljust(TYPE_WIDTH - TABSIZE)),;
		_printNameWithComment(name + "32", comment);
		print("		", T64.ljust(TYPE_WIDTH - TABSIZE)),;
		_printNameWithComment(name + "64", comment);
		print("	};");
		print("#else /" "* __USE_KOS *" "/");
		print("	", T64.ljust(TYPE_WIDTH)),;
		_printNameWithComment(name, comment);
		print("#endif /" "* !__USE_KOS *" "/");
		return;
	}
	print("#ifdef __USE_KOS");
	print("	union {");
	print("		", TXS.ljust(TYPE_WIDTH - TABSIZE)),;
	_printNameWithComment(name, comment);
	print("		", T32.ljust(TYPE_WIDTH - TABSIZE)),;
	_printNameWithComment(name + "32", comment);
	print("		", T64.ljust(TYPE_WIDTH - TABSIZE)),;
	_printNameWithComment(name + "64", comment);
	print("	};");
	print("#else /" "* __USE_KOS *" "/");
	_printTypedNameWithCommentAndPad(TXS, name, comment, TXS_SIZEOF, T64_SIZEOF);
	print("#endif /" "* !__USE_KOS *" "/");
}

// >> struct timespec     st_atim;        #if defined(__USE_XOPEN2K8) && __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__
// >> struct timespec     st_atimespec;   #if __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__
// >> struct __timespec32 st_atim32;      #if defined(__USE_KOS) && defined(__USE_XOPEN2K8) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
// >> struct __timespec32 st_atimespec32; #if defined(__USE_KOS) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
// >> struct __timespec64 st_atim64;      #if defined(__USE_TIME64) && defined(__USE_XOPEN2K8)
// >> struct __timespec64 st_atimespec64; #ifdef __USE_TIME64
// >> __time_t            st_atime;
// >> __syscall_ulong_t   st_atimensec;
// >> __time32_t          st_atime32;     #ifdef __USE_KOS
// >> __time64_t          st_atime64;     #ifdef __USE_TIME64
function TtimespecField(name: string, comment: string, doUnionHead: bool = true, doUnionTail: bool = true) {
	if (doUnionHead)
		print("union {");

	print("#if __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__");
	print("	", "struct timespec".ljust(TYPE_WIDTH)),;
	_printNameWithComment("st_" + name + "timespec",       comment);
	print("#ifdef __USE_XOPEN2K8");
	print("	", "struct timespec".ljust(TYPE_WIDTH)),;
	_printNameWithComment("st_" + name + "tim",            comment);
	print("#endif /" "* __USE_XOPEN2K8 *" "/");
	print("#else /" "* __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__ *" "/");
	print("	", "struct __stat_timespec32".ljust(TYPE_WIDTH)),;
	_printNameWithComment("st_" + name + "timespec",       comment + " (`struct __timespec64')");
	print("#ifdef __USE_XOPEN2K8");
	print("	", "struct __stat_timespec32".ljust(TYPE_WIDTH)),;
	_printNameWithComment("st_" + name + "tim",            comment + " (`struct __timespec64')");
	print("#endif /" "* __USE_XOPEN2K8 *" "/");
	print("#endif /" "* __SIZEOF_TIME_T__ != __SIZEOF_TIME64_T__ *" "/");

	print("#ifdef __USE_KOS");
	print("	", "__time32_t".ljust(TYPE_WIDTH)),;
	_printNameWithComment("st_" + name + "time32",         comment + " (seconds since 01.01.1970)");
	print("#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__");
	print("	", "struct __timespec32".ljust(TYPE_WIDTH)),;
	_printNameWithComment("st_" + name + "timespec32",     comment);
	print("#ifdef __USE_XOPEN2K8");
	print("	", "struct __timespec32".ljust(TYPE_WIDTH)),;
	_printNameWithComment("st_" + name + "tim32",          comment);
	print("#endif /" "* __USE_XOPEN2K8 *" "/");
	print("#endif /" "* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ *" "/");
	print("#endif /" "* __USE_KOS *" "/");

	print("#ifdef __USE_TIME64");
	print("#ifdef __USE_XOPEN2K8");
	print("	", "struct __timespec64".ljust(TYPE_WIDTH)),;
	_printNameWithComment("st_" + name + "tim64",          comment);
	print("#endif /" "* __USE_XOPEN2K8 *" "/");
	print("	", "struct __timespec64".ljust(TYPE_WIDTH)),;
	_printNameWithComment("st_" + name + "timespec64",     comment);
	print("	", "__time64_t".ljust(TYPE_WIDTH)),;
	_printNameWithComment("st_" + name + "time64",         comment + " (seconds since 01.01.1970)");
	print("#endif /" "* __USE_TIME64 *" "/");

	print("struct {");
	_printTypedNameWithCommentAndPad("__time_t", "st_" + name + "time",     comment + " (seconds since 01.01.1970)", "__SIZEOF_TIME_T__", "__SIZEOF_TIME64_T__");
	_printTypedNameWithCommentAndPad("__syscall_ulong_t", "st_" + name + "timensec", comment + " (nanoseconds)", "__SIZEOF_SYSCALL_LONG_T__", "8");
	if (doUnionTail) {
		print("};};");
	} else {
		print("};");
	}
}

global actions = [];

actions.append([] -> Tfield("__dev_t",        "st_dev",     "__SIZEOF_DEV_T__",      8, "Backing device number"));
actions.append([] -> Tfsfield("ino",          "st_ino",                                 "INode number"));
actions.append([] -> Tfield("__mode_t",       "st_mode",    "__SIZEOF_MODE_T__",     4, "File access permissions & type"));
actions.append([] -> Tfield("__nlink_t",      "st_nlink",   "__SIZEOF_NLINK_T__",    4, "Number of hard links"));
actions.append([] -> Tfield("__uid_t",        "st_uid",     "__SIZEOF_UID_T__",      4, "File owner (user) ID"));
actions.append([] -> Tfield("__gid_t",        "st_gid",     "__SIZEOF_GID_T__",      4, "File owner (group) ID"));
actions.append([] -> Tfield("__dev_t",        "st_rdev",    "__SIZEOF_DEV_T__",      8, "Referenced device (s.a. `S_ISDEV(st_mode)')"));
actions.append([] {  print("#ifdef __USE_KOS_ALTERATIONS"); });
actions.append([] -> Tfsfield("pos",          "st_size",                                "File size (in bytes)"));
actions.append([] {  print("#else /" "* __USE_KOS_ALTERATIONS *" "/"); });
actions.append([] -> Tfsfield("off",          "st_size",                                "File size (in bytes)"));
actions.append([] {  print("#endif /" "* !__USE_KOS_ALTERATIONS *" "/"); });
actions.append([] -> Tfield("__blksize_t",    "st_blksize", "__SIZEOF_BLKSIZE_T__",  8, "File block size (in bytes)"));
actions.append([] -> Tfsfield("blkcnt",       "st_blocks",                              "File block count"));
actions.append([] {  print("	", "__byte_t".ljust(TYPE_WIDTH - 2)),; _printNameWithComment("__st_reserved1[64]", "Reserved for future use"); });
actions.append([] -> TtimespecField("a", "Last-accessed time"));
actions.append([] -> TtimespecField("m", "Last-modified time"));
actions.append([] -> TtimespecField("c", "Last-changed time"));
actions.append([] -> TtimespecField("b", "Birth/creation time", doUnionTail: false));
actions.append([] {  print("#ifndef __USE_KOS_PURE"); });
actions.append([] -> TtimespecField("birth", "Birth/creation time", doUnionHead: false, doUnionTail: false));
actions.append([] {  print("#endif /" "* !__USE_KOS_PURE *" "/"); });
actions.append([] {  print("};"); });
actions.append([] {  print("	", "__byte_t".ljust(TYPE_WIDTH - 2)),; _printNameWithComment("__st_reserved2[64]", "Reserved for future use"); });


// Print stat
print("struct __kos_stat /" "*[PREFIX(st_)][NAME(kos_stat)]*" "/ {");
for (local x: actions)
	x();
print("};");
print;

// Print stat64
print("#ifdef __kos_stat_alias64");
print("struct __kos_stat_alias64 /" "*[PREFIX(st_)][NAME(kos_stat64)]*" "/ {");
doStat64 = true;
for (local x: actions)
	x();
print("};");
print("#undef __kos_stat_alias64");
print("#endif /" "* __kos_stat_alias64 *" "/");
]]]*/
struct __kos_stat /*[PREFIX(st_)][NAME(kos_stat)]*/ {
	__dev_t                  st_dev;           /* Backing device number */
#if __SIZEOF_DEV_T__ < 8
	__byte_t               __st_pad_dev[8 - __SIZEOF_DEV_T__];
#endif /* __SIZEOF_DEV_T__ < 8 */
#ifdef __USE_KOS
	union {
		__ino_t              st_ino;           /* INode number */
		__ino32_t            st_ino32;         /* INode number */
		__ino64_t            st_ino64;         /* INode number */
	};
#else /* __USE_KOS */
	__ino_t                  st_ino;           /* INode number */
#if __SIZEOF_INO_T__ < 8
	__byte_t               __st_pad_ino[8 - __SIZEOF_INO_T__];
#endif /* __SIZEOF_INO_T__ < 8 */
#endif /* !__USE_KOS */
	__mode_t                 st_mode;          /* File access permissions & type */
#if __SIZEOF_MODE_T__ < 4
	__byte_t               __st_pad_mode[4 - __SIZEOF_MODE_T__];
#endif /* __SIZEOF_MODE_T__ < 4 */
	__nlink_t                st_nlink;         /* Number of hard links */
#if __SIZEOF_NLINK_T__ < 4
	__byte_t               __st_pad_nlink[4 - __SIZEOF_NLINK_T__];
#endif /* __SIZEOF_NLINK_T__ < 4 */
	__uid_t                  st_uid;           /* File owner (user) ID */
#if __SIZEOF_UID_T__ < 4
	__byte_t               __st_pad_uid[4 - __SIZEOF_UID_T__];
#endif /* __SIZEOF_UID_T__ < 4 */
	__gid_t                  st_gid;           /* File owner (group) ID */
#if __SIZEOF_GID_T__ < 4
	__byte_t               __st_pad_gid[4 - __SIZEOF_GID_T__];
#endif /* __SIZEOF_GID_T__ < 4 */
	__dev_t                  st_rdev;          /* Referenced device (s.a. `S_ISDEV(st_mode)') */
#if __SIZEOF_DEV_T__ < 8
	__byte_t               __st_pad_rdev[8 - __SIZEOF_DEV_T__];
#endif /* __SIZEOF_DEV_T__ < 8 */
#ifdef __USE_KOS_ALTERATIONS
#ifdef __USE_KOS
	union {
		__pos_t              st_size;          /* File size (in bytes) */
		__pos32_t            st_size32;        /* File size (in bytes) */
		__pos64_t            st_size64;        /* File size (in bytes) */
	};
#else /* __USE_KOS */
	__pos_t                  st_size;          /* File size (in bytes) */
#if __SIZEOF_OFF_T__ < 8
	__byte_t               __st_pad_size[8 - __SIZEOF_OFF_T__];
#endif /* __SIZEOF_OFF_T__ < 8 */
#endif /* !__USE_KOS */
#else /* __USE_KOS_ALTERATIONS */
#ifdef __USE_KOS
	union {
		__off_t              st_size;          /* File size (in bytes) */
		__off32_t            st_size32;        /* File size (in bytes) */
		__off64_t            st_size64;        /* File size (in bytes) */
	};
#else /* __USE_KOS */
	__off_t                  st_size;          /* File size (in bytes) */
#if __SIZEOF_OFF_T__ < 8
	__byte_t               __st_pad_size[8 - __SIZEOF_OFF_T__];
#endif /* __SIZEOF_OFF_T__ < 8 */
#endif /* !__USE_KOS */
#endif /* !__USE_KOS_ALTERATIONS */
	__blksize_t              st_blksize;       /* File block size (in bytes) */
#if __SIZEOF_BLKSIZE_T__ < 8
	__byte_t               __st_pad_blksize[8 - __SIZEOF_BLKSIZE_T__];
#endif /* __SIZEOF_BLKSIZE_T__ < 8 */
#ifdef __USE_KOS
	union {
		__blkcnt_t           st_blocks;        /* File block count */
		__blkcnt32_t         st_blocks32;      /* File block count */
		__blkcnt64_t         st_blocks64;      /* File block count */
	};
#else /* __USE_KOS */
	__blkcnt_t               st_blocks;        /* File block count */
#if __SIZEOF_BLKCNT_T__ < 8
	__byte_t               __st_pad_blocks[8 - __SIZEOF_BLKCNT_T__];
#endif /* __SIZEOF_BLKCNT_T__ < 8 */
#endif /* !__USE_KOS */
	__byte_t               __st_reserved1[64]; /* Reserved for future use */
union {
#if __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__
	struct timespec          st_atimespec;     /* Last-accessed time */
#ifdef __USE_XOPEN2K8
	struct timespec          st_atim;          /* Last-accessed time */
#endif /* __USE_XOPEN2K8 */
#else /* __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__ */
	struct __stat_timespec32 st_atimespec;     /* Last-accessed time (`struct __timespec64') */
#ifdef __USE_XOPEN2K8
	struct __stat_timespec32 st_atim;          /* Last-accessed time (`struct __timespec64') */
#endif /* __USE_XOPEN2K8 */
#endif /* __SIZEOF_TIME_T__ != __SIZEOF_TIME64_T__ */
#ifdef __USE_KOS
	__time32_t               st_atime32;       /* Last-accessed time (seconds since 01.01.1970) */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
	struct __timespec32      st_atimespec32;   /* Last-accessed time */
#ifdef __USE_XOPEN2K8
	struct __timespec32      st_atim32;        /* Last-accessed time */
#endif /* __USE_XOPEN2K8 */
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_XOPEN2K8
	struct __timespec64      st_atim64;        /* Last-accessed time */
#endif /* __USE_XOPEN2K8 */
	struct __timespec64      st_atimespec64;   /* Last-accessed time */
	__time64_t               st_atime64;       /* Last-accessed time (seconds since 01.01.1970) */
#endif /* __USE_TIME64 */
struct {
	__time_t                 st_atime;         /* Last-accessed time (seconds since 01.01.1970) */
#if __SIZEOF_TIME_T__ < __SIZEOF_TIME64_T__
	__byte_t               __st_pad_atime[__SIZEOF_TIME64_T__ - __SIZEOF_TIME_T__];
#endif /* __SIZEOF_TIME_T__ < __SIZEOF_TIME64_T__ */
	__syscall_ulong_t        st_atimensec;     /* Last-accessed time (nanoseconds) */
#if __SIZEOF_SYSCALL_LONG_T__ < 8
	__byte_t               __st_pad_atimensec[8 - __SIZEOF_SYSCALL_LONG_T__];
#endif /* __SIZEOF_SYSCALL_LONG_T__ < 8 */
};};
union {
#if __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__
	struct timespec          st_mtimespec;     /* Last-modified time */
#ifdef __USE_XOPEN2K8
	struct timespec          st_mtim;          /* Last-modified time */
#endif /* __USE_XOPEN2K8 */
#else /* __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__ */
	struct __stat_timespec32 st_mtimespec;     /* Last-modified time (`struct __timespec64') */
#ifdef __USE_XOPEN2K8
	struct __stat_timespec32 st_mtim;          /* Last-modified time (`struct __timespec64') */
#endif /* __USE_XOPEN2K8 */
#endif /* __SIZEOF_TIME_T__ != __SIZEOF_TIME64_T__ */
#ifdef __USE_KOS
	__time32_t               st_mtime32;       /* Last-modified time (seconds since 01.01.1970) */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
	struct __timespec32      st_mtimespec32;   /* Last-modified time */
#ifdef __USE_XOPEN2K8
	struct __timespec32      st_mtim32;        /* Last-modified time */
#endif /* __USE_XOPEN2K8 */
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_XOPEN2K8
	struct __timespec64      st_mtim64;        /* Last-modified time */
#endif /* __USE_XOPEN2K8 */
	struct __timespec64      st_mtimespec64;   /* Last-modified time */
	__time64_t               st_mtime64;       /* Last-modified time (seconds since 01.01.1970) */
#endif /* __USE_TIME64 */
struct {
	__time_t                 st_mtime;         /* Last-modified time (seconds since 01.01.1970) */
#if __SIZEOF_TIME_T__ < __SIZEOF_TIME64_T__
	__byte_t               __st_pad_mtime[__SIZEOF_TIME64_T__ - __SIZEOF_TIME_T__];
#endif /* __SIZEOF_TIME_T__ < __SIZEOF_TIME64_T__ */
	__syscall_ulong_t        st_mtimensec;     /* Last-modified time (nanoseconds) */
#if __SIZEOF_SYSCALL_LONG_T__ < 8
	__byte_t               __st_pad_mtimensec[8 - __SIZEOF_SYSCALL_LONG_T__];
#endif /* __SIZEOF_SYSCALL_LONG_T__ < 8 */
};};
union {
#if __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__
	struct timespec          st_ctimespec;     /* Last-changed time */
#ifdef __USE_XOPEN2K8
	struct timespec          st_ctim;          /* Last-changed time */
#endif /* __USE_XOPEN2K8 */
#else /* __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__ */
	struct __stat_timespec32 st_ctimespec;     /* Last-changed time (`struct __timespec64') */
#ifdef __USE_XOPEN2K8
	struct __stat_timespec32 st_ctim;          /* Last-changed time (`struct __timespec64') */
#endif /* __USE_XOPEN2K8 */
#endif /* __SIZEOF_TIME_T__ != __SIZEOF_TIME64_T__ */
#ifdef __USE_KOS
	__time32_t               st_ctime32;       /* Last-changed time (seconds since 01.01.1970) */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
	struct __timespec32      st_ctimespec32;   /* Last-changed time */
#ifdef __USE_XOPEN2K8
	struct __timespec32      st_ctim32;        /* Last-changed time */
#endif /* __USE_XOPEN2K8 */
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_XOPEN2K8
	struct __timespec64      st_ctim64;        /* Last-changed time */
#endif /* __USE_XOPEN2K8 */
	struct __timespec64      st_ctimespec64;   /* Last-changed time */
	__time64_t               st_ctime64;       /* Last-changed time (seconds since 01.01.1970) */
#endif /* __USE_TIME64 */
struct {
	__time_t                 st_ctime;         /* Last-changed time (seconds since 01.01.1970) */
#if __SIZEOF_TIME_T__ < __SIZEOF_TIME64_T__
	__byte_t               __st_pad_ctime[__SIZEOF_TIME64_T__ - __SIZEOF_TIME_T__];
#endif /* __SIZEOF_TIME_T__ < __SIZEOF_TIME64_T__ */
	__syscall_ulong_t        st_ctimensec;     /* Last-changed time (nanoseconds) */
#if __SIZEOF_SYSCALL_LONG_T__ < 8
	__byte_t               __st_pad_ctimensec[8 - __SIZEOF_SYSCALL_LONG_T__];
#endif /* __SIZEOF_SYSCALL_LONG_T__ < 8 */
};};
union {
#if __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__
	struct timespec          st_btimespec;     /* Birth/creation time */
#ifdef __USE_XOPEN2K8
	struct timespec          st_btim;          /* Birth/creation time */
#endif /* __USE_XOPEN2K8 */
#else /* __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__ */
	struct __stat_timespec32 st_btimespec;     /* Birth/creation time (`struct __timespec64') */
#ifdef __USE_XOPEN2K8
	struct __stat_timespec32 st_btim;          /* Birth/creation time (`struct __timespec64') */
#endif /* __USE_XOPEN2K8 */
#endif /* __SIZEOF_TIME_T__ != __SIZEOF_TIME64_T__ */
#ifdef __USE_KOS
	__time32_t               st_btime32;       /* Birth/creation time (seconds since 01.01.1970) */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
	struct __timespec32      st_btimespec32;   /* Birth/creation time */
#ifdef __USE_XOPEN2K8
	struct __timespec32      st_btim32;        /* Birth/creation time */
#endif /* __USE_XOPEN2K8 */
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_XOPEN2K8
	struct __timespec64      st_btim64;        /* Birth/creation time */
#endif /* __USE_XOPEN2K8 */
	struct __timespec64      st_btimespec64;   /* Birth/creation time */
	__time64_t               st_btime64;       /* Birth/creation time (seconds since 01.01.1970) */
#endif /* __USE_TIME64 */
struct {
	__time_t                 st_btime;         /* Birth/creation time (seconds since 01.01.1970) */
#if __SIZEOF_TIME_T__ < __SIZEOF_TIME64_T__
	__byte_t               __st_pad_btime[__SIZEOF_TIME64_T__ - __SIZEOF_TIME_T__];
#endif /* __SIZEOF_TIME_T__ < __SIZEOF_TIME64_T__ */
	__syscall_ulong_t        st_btimensec;     /* Birth/creation time (nanoseconds) */
#if __SIZEOF_SYSCALL_LONG_T__ < 8
	__byte_t               __st_pad_btimensec[8 - __SIZEOF_SYSCALL_LONG_T__];
#endif /* __SIZEOF_SYSCALL_LONG_T__ < 8 */
};
#ifndef __USE_KOS_PURE
#if __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__
	struct timespec          st_birthtimespec; /* Birth/creation time */
#ifdef __USE_XOPEN2K8
	struct timespec          st_birthtim;      /* Birth/creation time */
#endif /* __USE_XOPEN2K8 */
#else /* __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__ */
	struct __stat_timespec32 st_birthtimespec; /* Birth/creation time (`struct __timespec64') */
#ifdef __USE_XOPEN2K8
	struct __stat_timespec32 st_birthtim;      /* Birth/creation time (`struct __timespec64') */
#endif /* __USE_XOPEN2K8 */
#endif /* __SIZEOF_TIME_T__ != __SIZEOF_TIME64_T__ */
#ifdef __USE_KOS
	__time32_t               st_birthtime32;   /* Birth/creation time (seconds since 01.01.1970) */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
	struct __timespec32      st_birthtimespec32; /* Birth/creation time */
#ifdef __USE_XOPEN2K8
	struct __timespec32      st_birthtim32;    /* Birth/creation time */
#endif /* __USE_XOPEN2K8 */
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_XOPEN2K8
	struct __timespec64      st_birthtim64;    /* Birth/creation time */
#endif /* __USE_XOPEN2K8 */
	struct __timespec64      st_birthtimespec64; /* Birth/creation time */
	__time64_t               st_birthtime64;   /* Birth/creation time (seconds since 01.01.1970) */
#endif /* __USE_TIME64 */
struct {
	__time_t                 st_birthtime;     /* Birth/creation time (seconds since 01.01.1970) */
#if __SIZEOF_TIME_T__ < __SIZEOF_TIME64_T__
	__byte_t               __st_pad_birthtime[__SIZEOF_TIME64_T__ - __SIZEOF_TIME_T__];
#endif /* __SIZEOF_TIME_T__ < __SIZEOF_TIME64_T__ */
	__syscall_ulong_t        st_birthtimensec; /* Birth/creation time (nanoseconds) */
#if __SIZEOF_SYSCALL_LONG_T__ < 8
	__byte_t               __st_pad_birthtimensec[8 - __SIZEOF_SYSCALL_LONG_T__];
#endif /* __SIZEOF_SYSCALL_LONG_T__ < 8 */
};
#endif /* !__USE_KOS_PURE */
};
	__byte_t               __st_reserved2[64]; /* Reserved for future use */
};

#ifdef __kos_stat_alias64
struct __kos_stat_alias64 /*[PREFIX(st_)][NAME(kos_stat64)]*/ {
	__dev_t                  st_dev;           /* Backing device number */
#if __SIZEOF_DEV_T__ < 8
	__byte_t               __st_pad_dev[8 - __SIZEOF_DEV_T__];
#endif /* __SIZEOF_DEV_T__ < 8 */
#ifdef __USE_KOS
	union {
		__ino64_t            st_ino;           /* INode number */
		__ino32_t            st_ino32;         /* INode number */
		__ino64_t            st_ino64;         /* INode number */
	};
#else /* __USE_KOS */
	__ino64_t                st_ino;           /* INode number */
#endif /* !__USE_KOS */
	__mode_t                 st_mode;          /* File access permissions & type */
#if __SIZEOF_MODE_T__ < 4
	__byte_t               __st_pad_mode[4 - __SIZEOF_MODE_T__];
#endif /* __SIZEOF_MODE_T__ < 4 */
	__nlink_t                st_nlink;         /* Number of hard links */
#if __SIZEOF_NLINK_T__ < 4
	__byte_t               __st_pad_nlink[4 - __SIZEOF_NLINK_T__];
#endif /* __SIZEOF_NLINK_T__ < 4 */
	__uid_t                  st_uid;           /* File owner (user) ID */
#if __SIZEOF_UID_T__ < 4
	__byte_t               __st_pad_uid[4 - __SIZEOF_UID_T__];
#endif /* __SIZEOF_UID_T__ < 4 */
	__gid_t                  st_gid;           /* File owner (group) ID */
#if __SIZEOF_GID_T__ < 4
	__byte_t               __st_pad_gid[4 - __SIZEOF_GID_T__];
#endif /* __SIZEOF_GID_T__ < 4 */
	__dev_t                  st_rdev;          /* Referenced device (s.a. `S_ISDEV(st_mode)') */
#if __SIZEOF_DEV_T__ < 8
	__byte_t               __st_pad_rdev[8 - __SIZEOF_DEV_T__];
#endif /* __SIZEOF_DEV_T__ < 8 */
#ifdef __USE_KOS_ALTERATIONS
#ifdef __USE_KOS
	union {
		__pos64_t            st_size;          /* File size (in bytes) */
		__pos32_t            st_size32;        /* File size (in bytes) */
		__pos64_t            st_size64;        /* File size (in bytes) */
	};
#else /* __USE_KOS */
	__pos64_t                st_size;          /* File size (in bytes) */
#endif /* !__USE_KOS */
#else /* __USE_KOS_ALTERATIONS */
#ifdef __USE_KOS
	union {
		__off64_t            st_size;          /* File size (in bytes) */
		__off32_t            st_size32;        /* File size (in bytes) */
		__off64_t            st_size64;        /* File size (in bytes) */
	};
#else /* __USE_KOS */
	__off64_t                st_size;          /* File size (in bytes) */
#endif /* !__USE_KOS */
#endif /* !__USE_KOS_ALTERATIONS */
	__blksize_t              st_blksize;       /* File block size (in bytes) */
#if __SIZEOF_BLKSIZE_T__ < 8
	__byte_t               __st_pad_blksize[8 - __SIZEOF_BLKSIZE_T__];
#endif /* __SIZEOF_BLKSIZE_T__ < 8 */
#ifdef __USE_KOS
	union {
		__blkcnt64_t         st_blocks;        /* File block count */
		__blkcnt32_t         st_blocks32;      /* File block count */
		__blkcnt64_t         st_blocks64;      /* File block count */
	};
#else /* __USE_KOS */
	__blkcnt64_t             st_blocks;        /* File block count */
#endif /* !__USE_KOS */
	__byte_t               __st_reserved1[64]; /* Reserved for future use */
union {
#if __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__
	struct timespec          st_atimespec;     /* Last-accessed time */
#ifdef __USE_XOPEN2K8
	struct timespec          st_atim;          /* Last-accessed time */
#endif /* __USE_XOPEN2K8 */
#else /* __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__ */
	struct __stat_timespec32 st_atimespec;     /* Last-accessed time (`struct __timespec64') */
#ifdef __USE_XOPEN2K8
	struct __stat_timespec32 st_atim;          /* Last-accessed time (`struct __timespec64') */
#endif /* __USE_XOPEN2K8 */
#endif /* __SIZEOF_TIME_T__ != __SIZEOF_TIME64_T__ */
#ifdef __USE_KOS
	__time32_t               st_atime32;       /* Last-accessed time (seconds since 01.01.1970) */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
	struct __timespec32      st_atimespec32;   /* Last-accessed time */
#ifdef __USE_XOPEN2K8
	struct __timespec32      st_atim32;        /* Last-accessed time */
#endif /* __USE_XOPEN2K8 */
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_XOPEN2K8
	struct __timespec64      st_atim64;        /* Last-accessed time */
#endif /* __USE_XOPEN2K8 */
	struct __timespec64      st_atimespec64;   /* Last-accessed time */
	__time64_t               st_atime64;       /* Last-accessed time (seconds since 01.01.1970) */
#endif /* __USE_TIME64 */
struct {
	__time_t                 st_atime;         /* Last-accessed time (seconds since 01.01.1970) */
#if __SIZEOF_TIME_T__ < __SIZEOF_TIME64_T__
	__byte_t               __st_pad_atime[__SIZEOF_TIME64_T__ - __SIZEOF_TIME_T__];
#endif /* __SIZEOF_TIME_T__ < __SIZEOF_TIME64_T__ */
	__syscall_ulong_t        st_atimensec;     /* Last-accessed time (nanoseconds) */
#if __SIZEOF_SYSCALL_LONG_T__ < 8
	__byte_t               __st_pad_atimensec[8 - __SIZEOF_SYSCALL_LONG_T__];
#endif /* __SIZEOF_SYSCALL_LONG_T__ < 8 */
};};
union {
#if __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__
	struct timespec          st_mtimespec;     /* Last-modified time */
#ifdef __USE_XOPEN2K8
	struct timespec          st_mtim;          /* Last-modified time */
#endif /* __USE_XOPEN2K8 */
#else /* __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__ */
	struct __stat_timespec32 st_mtimespec;     /* Last-modified time (`struct __timespec64') */
#ifdef __USE_XOPEN2K8
	struct __stat_timespec32 st_mtim;          /* Last-modified time (`struct __timespec64') */
#endif /* __USE_XOPEN2K8 */
#endif /* __SIZEOF_TIME_T__ != __SIZEOF_TIME64_T__ */
#ifdef __USE_KOS
	__time32_t               st_mtime32;       /* Last-modified time (seconds since 01.01.1970) */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
	struct __timespec32      st_mtimespec32;   /* Last-modified time */
#ifdef __USE_XOPEN2K8
	struct __timespec32      st_mtim32;        /* Last-modified time */
#endif /* __USE_XOPEN2K8 */
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_XOPEN2K8
	struct __timespec64      st_mtim64;        /* Last-modified time */
#endif /* __USE_XOPEN2K8 */
	struct __timespec64      st_mtimespec64;   /* Last-modified time */
	__time64_t               st_mtime64;       /* Last-modified time (seconds since 01.01.1970) */
#endif /* __USE_TIME64 */
struct {
	__time_t                 st_mtime;         /* Last-modified time (seconds since 01.01.1970) */
#if __SIZEOF_TIME_T__ < __SIZEOF_TIME64_T__
	__byte_t               __st_pad_mtime[__SIZEOF_TIME64_T__ - __SIZEOF_TIME_T__];
#endif /* __SIZEOF_TIME_T__ < __SIZEOF_TIME64_T__ */
	__syscall_ulong_t        st_mtimensec;     /* Last-modified time (nanoseconds) */
#if __SIZEOF_SYSCALL_LONG_T__ < 8
	__byte_t               __st_pad_mtimensec[8 - __SIZEOF_SYSCALL_LONG_T__];
#endif /* __SIZEOF_SYSCALL_LONG_T__ < 8 */
};};
union {
#if __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__
	struct timespec          st_ctimespec;     /* Last-changed time */
#ifdef __USE_XOPEN2K8
	struct timespec          st_ctim;          /* Last-changed time */
#endif /* __USE_XOPEN2K8 */
#else /* __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__ */
	struct __stat_timespec32 st_ctimespec;     /* Last-changed time (`struct __timespec64') */
#ifdef __USE_XOPEN2K8
	struct __stat_timespec32 st_ctim;          /* Last-changed time (`struct __timespec64') */
#endif /* __USE_XOPEN2K8 */
#endif /* __SIZEOF_TIME_T__ != __SIZEOF_TIME64_T__ */
#ifdef __USE_KOS
	__time32_t               st_ctime32;       /* Last-changed time (seconds since 01.01.1970) */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
	struct __timespec32      st_ctimespec32;   /* Last-changed time */
#ifdef __USE_XOPEN2K8
	struct __timespec32      st_ctim32;        /* Last-changed time */
#endif /* __USE_XOPEN2K8 */
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_XOPEN2K8
	struct __timespec64      st_ctim64;        /* Last-changed time */
#endif /* __USE_XOPEN2K8 */
	struct __timespec64      st_ctimespec64;   /* Last-changed time */
	__time64_t               st_ctime64;       /* Last-changed time (seconds since 01.01.1970) */
#endif /* __USE_TIME64 */
struct {
	__time_t                 st_ctime;         /* Last-changed time (seconds since 01.01.1970) */
#if __SIZEOF_TIME_T__ < __SIZEOF_TIME64_T__
	__byte_t               __st_pad_ctime[__SIZEOF_TIME64_T__ - __SIZEOF_TIME_T__];
#endif /* __SIZEOF_TIME_T__ < __SIZEOF_TIME64_T__ */
	__syscall_ulong_t        st_ctimensec;     /* Last-changed time (nanoseconds) */
#if __SIZEOF_SYSCALL_LONG_T__ < 8
	__byte_t               __st_pad_ctimensec[8 - __SIZEOF_SYSCALL_LONG_T__];
#endif /* __SIZEOF_SYSCALL_LONG_T__ < 8 */
};};
union {
#if __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__
	struct timespec          st_btimespec;     /* Birth/creation time */
#ifdef __USE_XOPEN2K8
	struct timespec          st_btim;          /* Birth/creation time */
#endif /* __USE_XOPEN2K8 */
#else /* __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__ */
	struct __stat_timespec32 st_btimespec;     /* Birth/creation time (`struct __timespec64') */
#ifdef __USE_XOPEN2K8
	struct __stat_timespec32 st_btim;          /* Birth/creation time (`struct __timespec64') */
#endif /* __USE_XOPEN2K8 */
#endif /* __SIZEOF_TIME_T__ != __SIZEOF_TIME64_T__ */
#ifdef __USE_KOS
	__time32_t               st_btime32;       /* Birth/creation time (seconds since 01.01.1970) */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
	struct __timespec32      st_btimespec32;   /* Birth/creation time */
#ifdef __USE_XOPEN2K8
	struct __timespec32      st_btim32;        /* Birth/creation time */
#endif /* __USE_XOPEN2K8 */
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_XOPEN2K8
	struct __timespec64      st_btim64;        /* Birth/creation time */
#endif /* __USE_XOPEN2K8 */
	struct __timespec64      st_btimespec64;   /* Birth/creation time */
	__time64_t               st_btime64;       /* Birth/creation time (seconds since 01.01.1970) */
#endif /* __USE_TIME64 */
struct {
	__time_t                 st_btime;         /* Birth/creation time (seconds since 01.01.1970) */
#if __SIZEOF_TIME_T__ < __SIZEOF_TIME64_T__
	__byte_t               __st_pad_btime[__SIZEOF_TIME64_T__ - __SIZEOF_TIME_T__];
#endif /* __SIZEOF_TIME_T__ < __SIZEOF_TIME64_T__ */
	__syscall_ulong_t        st_btimensec;     /* Birth/creation time (nanoseconds) */
#if __SIZEOF_SYSCALL_LONG_T__ < 8
	__byte_t               __st_pad_btimensec[8 - __SIZEOF_SYSCALL_LONG_T__];
#endif /* __SIZEOF_SYSCALL_LONG_T__ < 8 */
};
#ifndef __USE_KOS_PURE
#if __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__
	struct timespec          st_birthtimespec; /* Birth/creation time */
#ifdef __USE_XOPEN2K8
	struct timespec          st_birthtim;      /* Birth/creation time */
#endif /* __USE_XOPEN2K8 */
#else /* __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__ */
	struct __stat_timespec32 st_birthtimespec; /* Birth/creation time (`struct __timespec64') */
#ifdef __USE_XOPEN2K8
	struct __stat_timespec32 st_birthtim;      /* Birth/creation time (`struct __timespec64') */
#endif /* __USE_XOPEN2K8 */
#endif /* __SIZEOF_TIME_T__ != __SIZEOF_TIME64_T__ */
#ifdef __USE_KOS
	__time32_t               st_birthtime32;   /* Birth/creation time (seconds since 01.01.1970) */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
	struct __timespec32      st_birthtimespec32; /* Birth/creation time */
#ifdef __USE_XOPEN2K8
	struct __timespec32      st_birthtim32;    /* Birth/creation time */
#endif /* __USE_XOPEN2K8 */
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#endif /* __USE_KOS */
#ifdef __USE_TIME64
#ifdef __USE_XOPEN2K8
	struct __timespec64      st_birthtim64;    /* Birth/creation time */
#endif /* __USE_XOPEN2K8 */
	struct __timespec64      st_birthtimespec64; /* Birth/creation time */
	__time64_t               st_birthtime64;   /* Birth/creation time (seconds since 01.01.1970) */
#endif /* __USE_TIME64 */
struct {
	__time_t                 st_birthtime;     /* Birth/creation time (seconds since 01.01.1970) */
#if __SIZEOF_TIME_T__ < __SIZEOF_TIME64_T__
	__byte_t               __st_pad_birthtime[__SIZEOF_TIME64_T__ - __SIZEOF_TIME_T__];
#endif /* __SIZEOF_TIME_T__ < __SIZEOF_TIME64_T__ */
	__syscall_ulong_t        st_birthtimensec; /* Birth/creation time (nanoseconds) */
#if __SIZEOF_SYSCALL_LONG_T__ < 8
	__byte_t               __st_pad_birthtimensec[8 - __SIZEOF_SYSCALL_LONG_T__];
#endif /* __SIZEOF_SYSCALL_LONG_T__ < 8 */
};
#endif /* !__USE_KOS_PURE */
};
	__byte_t               __st_reserved2[64]; /* Reserved for future use */
};
#undef __kos_stat_alias64
#endif /* __kos_stat_alias64 */
/*[[[end]]]*/

__DECL_END
#endif /* __CC__ */

#undef __PRIVATE_STAT_HAVE_TIME_UNION

#endif /* !_BITS_OS_KOS_STAT_H */
