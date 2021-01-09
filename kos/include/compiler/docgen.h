/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_COMPILER_DOCGEN_H
#define __GUARD_COMPILER_DOCGEN_H 1

/* Function prototypes from system headers prefix argument names with `__'.
 * While this is necessary for c-compliant behavior, it admittedly does not
 * look too good when appearing in documentation.
 * That is where this header comes in, which is designed to automatically
 * define macros for renaming _all_ function argument names to their
 * underscore-less counterparts.
 * HINT: This header is should automatically be included by `__stdinc.h'
 *       when system headers are processed by a documentation generator.
 * NOTE: Argument names are automatically collected using the deemon
 *       script below. Run `$ deemon -F docgen.h' to update them.
 */

/*[[[deemon

#include <file>
#include <process>
#include <pipe>
#include <fs>

fs::chdir(fs::path::head(__FILE__));

local names = dict {};

function do_file(filename) {
	print file.io.stderr: "Header:", filename;
	local p = process("cproto", [
		"-msivx", "-D__CPROTO__", "-DCORRECT_ARGNAMES",
		"-I..", "-I../i386-kos", filename]);
	local r,w = pipe.new()...;
	p.stdout = w;
#ifdef __WINDOWS__
	p.stderr = file.open("NUL", "w");
#else
	p.stderr = file.open("/dev/null", "w");
#endif
	p.start();
	w.close();
	for (local l: r) {
		if ("P_((" !in l)
			continue;
		local pars = l.partition("P_((")[2].strip();
		pars = pars[:#pars-#"));"];
		for (local x: pars.split(",")) {
			x = x.reverse().scanf("%[a-zA-Z0-9_]")[0].reverse();
			names[x] = true;
		}
	}
	p.join();
}

function do_folder(path) {
	for (local f: fs::dir(path)) {
		if (f.endswith(".h")) {
			if (!fs::isdir(f))
				do_file(path + "/" + f);
		} else if (fs::isdir(fs::path::join(path, f))) {
			if (f != "private")
				do_folder(fs::path::join(path, f));
		}
	}
}

do_folder("..");

local argnames = names.keys().sorted();
for (local name: argnames) {
	if (!name.startswith("__"))
		continue;
	print "#define", name, name.lstrip("_");
}

]]]*/
#define ___argc argc
#define ___argv argv
#define ___envp envp
#define __a a
#define __a_bytes a_bytes
#define __abspath abspath
#define __accept accept
#define __act act
#define __action action
#define __addr addr
#define __addr_len addr_len
#define __address address
#define __advise advise
#define __af af
#define __ahost ahost
#define __ai ai
#define __align align
#define __alignment alignment
#define __alport alport
#define __amaster amaster
#define __arg arg
#define __args args
#define __aslave aslave
#define __assertion assertion
#define __attr attr
#define __attrib attrib
#define __b b
#define __b_bytes b_bytes
#define __base base
#define __basep basep
#define __bp bp
#define __bp_len bp_len
#define __buf buf
#define __buffer buffer
#define __buflen buflen
#define __bufloc bufloc
#define __bufsize bufsize
#define __byte byte
#define __c c
#define __c16 c16
#define __c32 c32
#define __c32len c32len
#define __c32max c32max
#define __callback callback
#define __cat_name cat_name
#define __catalog catalog
#define __category category
#define __category_mask category_mask
#define __cflags cflags
#define __ch ch
#define __char char
#define __checkpoint checkpoint
#define __clock_id clock_id
#define __closure closure
#define __cmd cmd
#define __cmsg cmsg
#define __cmsgp cmsgp
#define __command command
#define __cosx cosx
#define __count count
#define __data data
#define __databuf databuf
#define __databufp databufp
#define __datalen datalen
#define __dataset dataset
#define __delim delim
#define __delimiter delimiter
#define __delta delta
#define __denom denom
#define __desc desc
#define __dev dev
#define __dfd dfd
#define __dir dir
#define __dirlen dirlen
#define __dirp dirp
#define __diskfree diskfree
#define __disp disp
#define __domain domain
#define __domainp domainp
#define __dos_category dos_category
#define __drive drive
#define __drivelen drivelen
#define __dst dst
#define __dstbuf dstbuf
#define __dstlen dstlen
#define __dstsize dstsize
#define __duration duration
#define __dword dword
#define __e1 e1
#define __e2 e2
#define __ecode ecode
#define __edflag edflag
#define __eflags eflags
#define __egid egid
#define __elemcount elemcount
#define __elemsize elemsize
#define __endptr endptr
#define __ends ends
#define __eno eno
#define __ent ent
#define __entry entry
#define __envstr envstr
#define __err err
#define __err_num err_num
#define __errbuf errbuf
#define __errbuf_size errbuf_size
#define __errcode errcode
#define __errmsg errmsg
#define __errnum errnum
#define __euid euid
#define __evp evp
#define __exc exc
#define __exceptfds exceptfds
#define __exitcode exitcode
#define __exponent exponent
#define __expr expr
#define __ext ext
#define __extbuf extbuf
#define __extlen extlen
#define __extra_info extra_info
#define __f f
#define __facility facility
#define __fd fd
#define __fd2 fd2
#define __fd2p fd2p
#define __fdin fdin
#define __fdout fdout
#define __fds fds
#define __fdtype fdtype
#define __file file
#define __file_times file_times
#define __filelen filelen
#define __filename filename
#define __filler filler
#define __finddata finddata
#define __findfd findfd
#define __flag flag
#define __flags flags
#define __fmode fmode
#define __fname fname
#define __format format
#define __fp fp
#define __from from
#define __fromfd fromfd
#define __func func
#define __function function
#define __gaicbp gaicbp
#define __gid gid
#define __glibc_block glibc_block
#define __group group
#define __grouplen grouplen
#define __groups groups
#define __h_errnop h_errnop
#define __handle handle
#define __handler handler
#define __haystack haystack
#define __haystacklen haystacklen
#define __hint hint
#define __hnd hnd
#define __host host
#define __hostlen hostlen
#define __hostlong hostlong
#define __hostp hostp
#define __hostshort hostshort
#define __how how
#define __i i
#define __id id
#define __ident ident
#define __idtype idtype
#define __in in
#define __inc inc
#define __index index
#define __info info
#define __infop infop
#define __interface_addr interface_addr
#define __interrupt interrupt
#define __interval interval
#define __iov iov
#define __iovec iovec
#define __iptr iptr
#define __item item
#define __key key
#define __l l
#define __left left
#define __len len
#define __length length
#define __length1 length1
#define __length2 length2
#define __lenp lenp
#define __level level
#define __line line
#define __lineno lineno
#define __lineptr lineptr
#define __linesize linesize
#define __liovcnt liovcnt
#define __loc loc
#define __locale locale
#define __lockmode lockmode
#define __locuser locuser
#define __longind longind
#define __longopts longopts
#define __lvec lvec
#define __major major
#define __mallptr mallptr
#define __mask mask
#define __max_a_chars max_a_chars
#define __max_b_chars max_b_chars
#define __max_chars max_chars
#define __maxlen maxlen
#define __maxsize maxsize
#define __mem mem
#define __message message
#define __mhdr mhdr
#define __minor minor
#define __mnt_id mnt_id
#define __mode mode
#define __modes modes
#define __mountdirfd mountdirfd
#define __msec msec
#define __multx multx
#define __n n
#define __n_bytes n_bytes
#define __n_dwords n_dwords
#define __n_qwords n_qwords
#define __n_words n_words
#define __name name
#define __name_len name_len
#define __namelist namelist
#define __nbytes nbytes
#define __needle needle
#define __needlelen needlelen
#define __net net
#define __netgroup netgroup
#define __netlong netlong
#define __netshort netshort
#define __new new
#define __newfd newfd
#define __newmask newmask
#define __newmode newmode
#define __newname newname
#define __newthread newthread
#define __newval newval
#define __nfd nfd
#define __nfds nfds
#define __ngroups ngroups
#define __nmatch nmatch
#define __nmc nmc
#define __nochdir nochdir
#define __noclose noclose
#define __nptr nptr
#define __nsid nsid
#define __num num
#define __num_regs num_regs
#define __number number
#define __numer numer
#define __numofbytes numofbytes
#define __numsrc numsrc
#define __nwc nwc
#define __oact oact
#define __obstack obstack
#define __ofd ofd
#define __off off
#define __offin offin
#define __offout offout
#define __offset offset
#define __oflag oflag
#define __old old
#define __oldfd oldfd
#define __oldfile oldfile
#define __oldmask oldmask
#define __oldmode oldmode
#define __oldname oldname
#define __option option
#define __optional_actions optional_actions
#define __options options
#define __optlen optlen
#define __optname optname
#define __optval optval
#define __ord ord
#define __oset oset
#define __osfd osfd
#define __oss oss
#define __out out
#define __ovalue ovalue
#define __owner owner
#define __p p
#define __pad pad
#define __pai pai
#define __parameter_number parameter_number
#define __parameter_value parameter_value
#define __pass pass
#define __path path
#define __pattern pattern
#define __pbuf pbuf
#define __pbuflen pbuflen
#define __pc16 pc16
#define __pc32 pc32
#define __pcurrent pcurrent
#define __pend pend
#define __perr perr
#define __pfile pfile
#define __pflags pflags
#define __pfx pfx
#define __pgetc pgetc
#define __pgid pgid
#define __pgrp pgrp
#define __pgrp_id pgrp_id
#define __pid pid
#define __pinfo pinfo
#define __pipesize pipesize
#define __plusy plusy
#define __pmode pmode
#define __port port
#define __pos pos
#define __pp pp
#define __preg preg
#define __printer printer
#define __prompt prompt
#define __prop prop
#define __proto proto
#define __protocol protocol
#define __ps ps
#define __psize psize
#define __psrc psrc
#define __pstr pstr
#define __ptm ptm
#define __ptr ptr
#define __pungetc pungetc
#define __pwc pwc
#define __queue_selector queue_selector
#define __quo quo
#define __qword qword
#define __raddr raddr
#define __radix radix
#define __range range
#define __readfds readfds
#define __regs regs
#define __reject reject
#define __rem rem
#define __remaining remaining
#define __remuser remuser
#define __req req
#define __request request
#define __requested_time requested_time
#define __res res
#define __resbufp resbufp
#define __result result
#define __result_buf result_buf
#define __resultbuf resultbuf
#define __retval retval
#define __rgid rgid
#define __rhost rhost
#define __right right
#define __riovcnt riovcnt
#define __rport rport
#define __ruid ruid
#define __rvec rvec
#define __s s
#define __s1 s1
#define __s2 s2
#define __sa sa
#define __salen salen
#define __salt salt
#define __sample_buffer sample_buffer
#define __save_ptr save_ptr
#define __savemask savemask
#define __scale scale
#define __scp scp
#define __sec sec
#define __seconds seconds
#define __segments segments
#define __self self
#define __selfpc selfpc
#define __serv serv
#define __service service
#define __servlen servlen
#define __set set
#define __sflag sflag
#define __sgid sgid
#define __shflag shflag
#define __shortopts shortopts
#define __sig sig
#define __sigmask sigmask
#define __sign sign
#define __signgamp signgamp
#define __signo signo
#define __sinx sinx
#define __size size
#define __sizeinwords sizeinwords
#define __sizeloc sizeloc
#define __sizeok sizeok
#define __slist slist
#define __sock_in sock_in
#define __sockfd sockfd
#define __speed speed
#define __src src
#define __srcsize srcsize
#define __ss ss
#define __sse2_control_word sse2_control_word
#define __sse2_stat sse2_stat
#define __stacksz stacksz
#define __start start
#define __starts starts
#define __stat_loc stat_loc
#define __status status
#define __stay_open stay_open
#define __stayopen stayopen
#define __stop stop
#define __str str
#define __str1 str1
#define __str2 str2
#define __stream stream
#define __string string
#define __string1 string1
#define __string2 string2
#define __stringp stringp
#define __suid suid
#define __suser suser
#define __symname symname
#define __syntax syntax
#define __sysno sysno
#define __tagb tagb
#define __template template
#define __templatename templatename
#define __termios_p termios_p
#define __termp termp
#define __text text
#define __textlen textlen
#define __textmode textmode
#define __th th
#define __thread1 thread1
#define __thread2 thread2
#define __thread_return thread_return
#define __threadaddr threadaddr
#define __threadid threadid
#define __time0 time0
#define __time1 time1
#define __timeout timeout
#define __timer timer
#define __timerid timerid
#define __tm tm
#define __tmo tmo
#define __to to
#define __tofd tofd
#define __tp tp
#define __tptrp tptrp
#define __ts ts
#define __tstat tstat
#define __type type
#define __typep typep
#define __uid uid
#define __usage usage
#define __useconds useconds
#define __user user
#define __userp userp
#define __utf16 utf16
#define __utf16chars utf16chars
#define __utf32 utf32
#define __utf32chars utf32chars
#define __utf8 utf8
#define __utf8chars utf8chars
#define __utx utx
#define __val val
#define __vallen vallen
#define __value value
#define __varname varname
#define __version version
#define __vlen vlen
#define __vmessages vmessages
#define __w w
#define __wc wc
#define __wcs wcs
#define __wcslen wcslen
#define __wcsmax wcsmax
#define __when when
#define __whence whence
#define __winp winp
#define __word word
#define __writefds writefds
#define __ws ws
#define __x x
#define __x86_control_word x86_control_word
#define __x86_stat x86_stat
#define __y y
#define __year year
#define __z z
//[[[end]]]

/* XXX: Keywords starting with `__' that should
 *      appear in docs should be #undef'ed here. */


#endif /* !__GUARD_COMPILER_DOCGEN_H */
