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
%(c_prefix){
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/newlib/libc/include/libgen.h) */
/* (#) Portability: DragonFly BSD (/include/libgen.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/libgen.h) */
/* (#) Portability: FreeBSD       (/include/libgen.h) */
/* (#) Portability: GNU C Library (/misc/libgen.h) */
/* (#) Portability: GNU Hurd      (/usr/include/libgen.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/libgen.h) */
/* (#) Portability: NetBSD        (/include/libgen.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/libgen.h) */
/* (#) Portability: OpenBSD       (/include/libgen.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/libgen.h) */
/* (#) Portability: diet libc     (/include/libgen.h) */
/* (#) Portability: libc6         (/include/libgen.h) */
/* (#) Portability: mintlib       (/include/libgen.h) */
/* (#) Portability: musl libc     (/include/libgen.h) */
/* (#) Portability: uClibc        (/include/libgen.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(EOF = __EOF)]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#ifdef __INTELLISENSE__
#ifdef __USE_SOLARIS
#include <bits/types/FILE.h>
#include <bits/types/size_t.h>
#include <bits/types/mode_t.h>
#endif /* __USE_SOLARIS */
#endif /* __INTELLISENSE__ */

#ifdef __CC__
__SYSDECL_BEGIN

}

@@Return the directory, that is everything leading up to, but not
@@including the last slash of `path'. If no such path exists, "."
@@is returned instead. Trailing slashes are ignored
@@>> dirname("/usr/include///"); // Returns "/usr"
@@>> dirname("/usr/include/");   // Returns "/usr"
@@>> dirname("/usr/include");    // Returns "/usr"
@@>> dirname("/usr/");           // Returns "/"
@@>> dirname("/usr");            // Returns "/"
@@>> dirname("/");               // Returns "/"
@@>> dirname("///");             // Returns "/"
@@>> dirname("foo/bar/");        // Returns "foo"
@@>> dirname("foo/bar");         // Returns "foo"
@@>> dirname("foo/");            // Returns "."
@@>> dirname("foo");             // Returns "."
@@>> dirname(".");               // Returns "."
@@>> dirname("..");              // Returns "."
@@>> dirname("");                // Returns "."
@@>> dirname(NULL);              // Returns "."
@@Note  that for this purpose, `path' may be modified in-place, meaning
@@that you should really always pass an strdup()'d, or writable string.
[[nonnull]] char *dirname([[in_opt]] char *path) {
	char *iter;
	/* Handle the empty-path case. */
	if (!path || !*path)
		goto fallback;
	iter = strend(path);
	for (;;) {
		--iter;
		if (*iter != '/')
			break;
		if (iter <= path) {
			/* String consists only of '/'-characters */
			return path;
		}
		/* Trim trailing slashes */
		*iter = '\0';
	}
	/* HINT: iter == strend(path) - 1; */
	for (;;) {
		if (iter < path)
			goto fallback;
		if (*iter == '/')
			break;
		--iter;
	}
	if (iter == path) {
		/* First character is the slash (e.g. "/foo/")
		 * Return "/" in this case! */
		++iter;
	}
	/* Delete the  slash character  (or  the one  after  the
	 * slash, if the only character left is a leading slash) */
	iter[0] = '\0';
	return path;
fallback:
	return (char *)".";
}



@@Return the filename-part, that is everything following
@@the last slash of `filename'. If no such part exists, "."
@@is returned instead. Trailing slashes are ignored
@@>> basename("/usr/include///"); // Returns "include"
@@>> basename("/usr/include/");   // Returns "include"
@@>> basename("/usr/include");    // Returns "include"
@@>> basename("/usr/");           // Returns "usr"
@@>> basename("/usr");            // Returns "usr"
@@>> basename("/");               // Returns "/"
@@>> basename("///");             // Returns "/"
@@>> basename("foo/bar/");        // Returns "bar"
@@>> basename("foo/bar");         // Returns "bar"
@@>> basename("foo/");            // Returns "foo"
@@>> basename("foo");             // Returns "foo"
@@>> basename(".");               // Returns "."
@@>> basename("..");              // Returns ".."
@@>> basename("");                // Returns "."
@@>> basename(NULL);              // Returns "."
@@Note that for this purpose, `filename' may be modified in-place, meaning
@@that  you should really  always pass an  strdup()'d, or writable string.
@@
@@Also note that a different version of this function exists in <string.h>,
@@where if you  include both  <libgen.h> and  <string.h>, you  can use  the
@@alternate function from <string.h>  by `#undef basename', or calling  the
@@function as `(basename)(...)' (as opposed to `basename(...)')
[[nonnull, export_alias("__gnu_basename")]]
char *__xpg_basename([[inout_opt]] char *filename) {
	char *iter;
	/* Handle the empty-path case. */
	if (!filename || !*filename)
		goto fallback;
	iter = strend(filename);
	for (;;) {
		--iter;
		if (*iter != '/')
			break;
		if (iter <= filename) {
			/* String consists only of '/'-characters */
			return filename;
		}
		/* Trim trailing slashes */
		*iter = '\0';
	}
	/* HINT: iter == strend(path) - 1; */
	for (;;) {
		if (iter < filename)
			break;
		if (*iter == '/')
			break;
		--iter;
	}
	return iter + 1;
fallback:
	return (char *)".";
}

%[insert:pp_if($has_function(__xpg_basename))]
%#define basename(path) __xpg_basename(path)
%[insert:pp_endif]


/************************************************************************/
/* More functions found on OpenSolaris                                  */
/************************************************************************/

%
%#ifdef __USE_SOLARIS
%{
#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __mode_t_defined
#define __mode_t_defined
typedef __mode_t mode_t;
#endif /* !__mode_t_defined */

#ifndef __FILE_defined
#define __FILE_defined
typedef __FILE FILE;
#endif /* !__FILE_defined */

}

%[insert:prefix(DEFINE_PIO_OFFSET)]

%[default:section(".text.crt{|.dos}.solaris")]

// TODO: #ifdef _REENTRANT
// TODO: char **____loc1(void);
// TODO: int *___i_size(void);
// TODO: #define __loc1 (*____loc1())
// TODO: #define __i_size (*___i_size())
// TODO: #else
// TODO: __CSDECLARE(,char *,__loc1)
// TODO: __CSDECLARE(,int,__i_size)
// TODO: #endif

// TODO: [[ATTR_SENTINEL]] char *regcmp(char const *s1, ...);

// TODO: char *regex(char const *re, char const *subject, ...);

// TODO: int gmatch(char const *string, char const *pattern);

// TODO: int isencrypt(char const *textbuf, size_t buflen);

// TODO: int p2open([[in_opt]] char const *cmdline, [[out]] FILE *files[2]);

// TODO: int p2close([[in]] FILE *files[2]);

// TODO: int mkdirp([[in]] char const *pathname, mode_t mode);

// TODO: int rmdirp([[in]] char *pathname, [[out]] char *remaining);

// TODO: char *pathfind([[nullable]] char const *path, [[in]] char const *name, [[in_opt]] char const *mode);

%[define_c_language_keyword("__KOS_FIXED_CONST")]

@@>> bgets(3)
@@Read at most `buflen_minus_one' characters from `fp' and into `buf'
@@Afterwards, a trailing  NUL-character is appended  to `buf'  (hence
@@the `minus_one' in  `buflen_minus_one'). Stop  reading (and  append
@@the trailing NUL) once `fgetc(fp) == EOF', or `fgetc(fp)' returns a
@@character from `stop_chars'. In this last case, the read  character
@@is NOT ungetc'd, meaning it will be lost.
@@@param: buf:   Output buffer. (Assuming success), this function always
@@               writes at least  `1' (trailing NUL)  character to  this
@@               buffer.
@@@return: NULL: `buflen_minus_one != 0', and the  first character  read
@@               from `fp' was `EOF'. The case where the first character
@@               read is in `stop_chars' doesn't cause a NULL-return.
@@@return: * :   Returns a pointer to the trailing NUL written to `buf'
@@               There is no true error  case; read errors are  treated
@@               the same way as end-of-file.
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[requires_function(fgetc), impl_include("<asm/crt/stdio.h>")]]
char *bgets([[out/*(? <= buflen_minus_one+1)*/]] char *buf, size_t buflen_minus_one,
            [[inout]] FILE *fp,
            [[in_opt]] char __KOS_FIXED_CONST *stop_chars) {
	char *iter = buf;
	if (stop_chars == NULL)
		stop_chars = (char __KOS_FIXED_CONST *)"";
	for (; buflen_minus_one; --buflen_minus_one) {
		int ch = fgetc(fp);
		if (ch == EOF) {
			if (iter == buf)
				return NULL;
			break;
		}
		if (strchr(stop_chars, ch))
			break;
		*iter++ = ch;
	}
	*iter = '\0';
	return iter;
}

@@>> bufsplit(3)
@@Split `string' on field-separator characters (by default "\t" or  "\n"),
@@replacing  those characters with  '\0'. The produced  list of strings is
@@then stored in up to `result_c' pointers of `result_v', with the  actual
@@number  of produced  strings returned  (any unused  trailing pointers of
@@`result_v' are  filled  with  the  empty  string  at  `strend(string)').
@@In  case `string' contains  more than `result_c'  fields, only the first
@@`result_c' fields are actually split and `result_v[result_c-1]' contains
@@the remaining of `string', including any unsplit trailing fields.
@@
@@The set of characters used as field-separators can also be changed  for
@@this function in a  call `bufsplit(NEW_FIELDS, 0, NULL)'. Note that  in
@@this case, `string' must remain  allocated and usable until fields  are
@@changed yet again. There is no way to reset the default ("\t\n") set of
@@field separator characters.
@@
@@@return: * : The number of  field strings extracted  from `string'  and
@@             stored in `result_v'. All remaining pointers in `result_v'
@@             beyond `return' (and  before `result_c')  are filled  with
@@             the empty string found at `strend(IN:string)'.
[[decl_include("<bits/types.h>")]]
[[impl_include("<hybrid/host.h>")]] /* __pic__ */
size_t bufsplit([[inout_opt]] char *string, size_t result_c,
                [[out_opt/*(result_c)*/]] char **result_v) {
	size_t count;
	char const *splitchar;
	static char const default_splitchar[] = "\t\n";
@@pp_ifdef __pic__@@
	@@static char const *bufsplit_saved_splitchar = NULL;@@
	if (bufsplit_saved_splitchar == NULL)
		bufsplit_saved_splitchar = default_splitchar;
@@pp_else@@
	static char const *bufsplit_saved_splitchar = default_splitchar;
@@pp_endif@@
	if unlikely(!string)
		return 0;
	if (result_c == 0 && result_v == NULL) {
		bufsplit_saved_splitchar = (char const *)string;
		return 1;
	} else {
		if unlikely((result_c != 0 && result_v == NULL) ||
		            (result_c == 0 && result_v != NULL))
			return 0;
	}
	splitchar = bufsplit_saved_splitchar;
	for (count = 0; count < result_c; ) {
		result_v[count++] = string;
		/* Find end of field. */
		string = strpbrk(string, splitchar);
		if (!string)
			break;
		/* Split field. */
		*string++ = '\0';
		if (*string == '\0') {
			/* Special case: end-of-string after field separator
			 * --> no more fields. */
			break;
		}
	}
	/* All remaining fields become the empty string that exists at
	 * the end of the last  (preceding) field. There is always  at
	 * least one field at the start of the string. */
	if (count < result_c) {
		size_t i;
		string = strend(result_v[count - 1]);
		for (i = count; i < result_c; i++)
			result_v[i] = string;
	}
	return count;
}

[[static, requires_function(read, malloc, realloc)]]
[[decl_include("<bits/types.h>")]]
[[impl_include("<asm/crt/malloc.h>")]] /* __REALLOC_ZERO_IS_NONNULL */
char *fcopylist_sz([[fdread]] fd_t fd, [[out]] size_t *p_filesize) {
	size_t reslen  = 0;
	size_t buflen  = 1024;
	byte_t *result = (byte_t *)malloc(buflen);
	if unlikely(!result) {
		buflen = 1;
		result = (byte_t *)malloc(1);
		if unlikely(!result)
			goto err;
	}
	for (;;) {
		/* Ensure that buffer space is available. */
		size_t i, insize;
		size_t freelen = buflen - reslen;
		byte_t *bufptr;
		if unlikely(!freelen) {
			byte_t *new_result;
			size_t newlen = buflen * 2;
			if unlikely(newlen < buflen)
				newlen = buflen + 1;
			new_result = (byte_t *)realloc(result, newlen);
			if unlikely(!new_result) {
				newlen = buflen + 1;
				new_result = (byte_t *)realloc(result, newlen);
				if unlikely(!new_result)
					goto err_r;
			}
			result  = new_result;
			buflen  = newlen;
			freelen = buflen - reslen;
		}
		bufptr = result + reslen;
		insize = (size_t)read(fd, bufptr, freelen);
		if ((ssize_t)insize <= 0) {
			if unlikely((ssize_t)insize < 0)
				goto err_r;
			break; /* End-of-file */
		}
		/* Replace all line-feeds within read text with '\0' */
@@pp_if 1@@
		for (i = 0; i < insize;) {
			char ch = bufptr[i];
			if (ch == '\r') {
				/* Universal linefeed support */
				bufptr[i] = '\0';
				++i;
				if (i >= insize)
					break;
				if (bufptr[i] == '\n') {
					/* Collapse 2-byte linefeed into a single '\0' */
					--insize;
					memmovedown(&bufptr[i],
					            &bufptr[i + 1],
					            insize - i);
				}
			} else {
				if (ch == '\n')
					bufptr[i] = '\0';
				++i;
			}
		}
@@pp_else@@
		for (i = 0; i < insize; ++i) {
			if (bufptr[i] == '\n')
				bufptr[i] = '\0';
		}
@@pp_endif@@
		reslen += insize;
	}

	/* Free unused memory */
	{
		byte_t *new_result;
@@pp_ifdef __REALLOC_ZERO_IS_NONNULL@@
		new_result = (byte_t *)realloc(result, reslen);
@@pp_else@@
		new_result = (byte_t *)realloc(result, reslen ? reslen : 1);
@@pp_endif@@
		if likely(new_result)
			result = new_result;
	}
	*p_filesize = reslen;
	return (char *)result;
err_r:
@@pp_if $has_function(free)@@
	free(result);
@@pp_endif@@
err:
	return NULL;
}

[[static, decl_include("<hybrid/typecore.h>")]]
[[crt_dos_variant]]
[[requires_function(open, fcopylist_sz)]]
[[impl_include("<asm/os/oflags.h>")]]
char *copylist_sz([[in]] char const *filename,
                  [[out]] size_t *p_filesize) {
	char *result;
@@pp_ifdef O_RDONLY@@
	fd_t fd = open(filename, O_RDONLY | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);
@@pp_else@@
	fd_t fd = open(filename, __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);
@@pp_endif@@
	if unlikely(fd < 0)
		return NULL;
	result = fcopylist_sz(fd, p_filesize);
@@pp_if $has_function(close)@@
	close(fd);
@@pp_endif@@
	return result;
}


@@>> copylist(3), copylist64(3)
@@Load a given file `filename' into memory (via `malloc(3)'), and return
@@a  pointer to this newly malloc'd data-blob (the caller is responsible
@@to eventually free(3) it). The size of this loaded data blob is stored
@@in the given `p_filesize'. The file  is processed such that all  line-
@@feeds are replaced with '\0' characters.
@@This function is stupid and should not be used for the following reasons:
@@ - Loading  an entire file  into an malloc buffer  is highly inefficient. If
@@   you want to load a file into memory, use mmap(2), which allows the kernel
@@   to only load file  parts as you  actually make use  of them, rather  than
@@   being forced to load all  of them at once. Even  if you want to load  all
@@   of them at  once, mmap(2) is  still more efficient  since the kernel  can
@@   simply map its actual  I/O buffer into you  process, rather than the  way
@@   that `read(2)' would be required to first load the I/O buffer, then  copy
@@   from that I/O buffer into your malloc'd buffer.
@@ - The `p_filesize' argument, and the fact  that this function has a  64-bit
@@   offset variant doesn't make any flipping sense. - Because the entire file
@@   gets  loaded into memory  at once, it's literally  impossible to use this
@@   function with files that are  larger than `SIZE_MAX' bytes, meaning  that
@@   any file size for which this function could possibly succeed _has_ to  be
@@   small enough to fit into a `size_t'. As such, using off_t/pos_t where the
@@   actual limiting factor  is unaffected  by `_FILE_OFFSET_BITS=64'  doesn't
@@   make any sense. For example:
@@    i386: sizeof(size_t)==4, sizeof(pos_t)==4, sizeof(pos64_t)==8:
@@     -> copylist()  is non-portable to other architectures because there
@@        is no guaranty on the  relation between size_t and pos_t.  There
@@        might be a system where `sizeof(pos_t) < sizeof(size_t)', so you
@@        have to be ready to use `copylist64()' instead.
@@     -> copylist64() doesn't make any sense because the function literally
@@        cannot succeed for  files larger than  32-bit, as it's  physically
@@        impossible to malloc() a buffer for such a file.
@@    x86_64: sizeof(size_t)==8, sizeof(pos_t)==8, sizeof(pos64_t)==8:
@@     -> copylist() is non-portable for the same reasons as on i386
@@     -> copylist64() is identical to copylist() because pos_t is  always
@@        64-bit, meaning that its existence isn't explicitly warranted on
@@        this architecture.
[[wunused, cp, decl_include("<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("copylist")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("copylist64")]]
[[crt_dos_variant, impl_prefix(DEFINE_PIO_OFFSET)]]
[[requires_include("<bits/types.h>"), impl_include("<bits/types.h>")]]
[[requires(($has_function(copylist64) && __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__) || $has_function(copylist_sz))]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_SIZE_T__), crt_intern_kos_alias("libc_copylist_sz")]]
char *copylist([[in]] char const *filename,
               [[out]] __PIO_OFFSET *p_filesize) {
@@pp_if $has_function(copylist64) && __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__@@
	__PIO_OFFSET64 filesize64;
	char *result = copylist64(filename, &filesize64);
	*p_filesize = (__PIO_OFFSET)filesize64;
	return result;
@@pp_elif __SIZEOF_OFF_T__ == __SIZEOF_SIZE_T__@@
	return copylist_sz(filename, (size_t *)p_filesize);
@@pp_else@@
	char *result;
	size_t size;
	result = copylist_sz(filename, &size);
	*p_filesize = (__PIO_OFFSET)size;
	return result;
@@pp_endif@@
}

%
%#ifdef __USE_LARGEFILE64
[[wunused, cp, decl_include("<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET)]]
[[preferred_off64_variant_of(copylist), doc_alias("copylist")]]
[[crt_dos_variant, impl_include("<bits/types.h>"), impl_prefix(DEFINE_PIO_OFFSET)]]
[[requires_function(copylist_sz)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__), crt_intern_alias("copylist")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF64_T__ == __SIZEOF_SIZE_T__), crt_intern_kos_alias("libc_copylist_sz")]]
char *copylist64([[in]] char const *filename,
                 [[out]] __PIO_OFFSET64 *p_filesize) {
@@pp_if __SIZEOF_OFF64_T__ == __SIZEOF_SIZE_T__@@
	return copylist_sz(filename, (size_t *)p_filesize);
@@pp_else@@
	char *result;
	size_t size;
	result = copylist_sz(filename, &size);
	*p_filesize = (__PIO_OFFSET64)size;
	return result;
@@pp_endif@@
}
%#endif /* __USE_LARGEFILE64 */


%[insert:extern(eaccess)]

@@>> strcadd(3)
@@Decode C-style escape sequences from `string' and write the result to `dstbuf'
@@To prevent a buffer overflow, `dstbuf' should be at least `strlen(string) + 1'
@@bytes long (the +1 because this function appends a trailing '\0')
@@@return: * : A pointer to the trailing '\0' appended to `dstbuf'
[[nonnull, impl_include("<hybrid/typecore.h>")]]
char *strcadd([[out]] char *dstbuf, [[in]] char const *string) {
	for (;;) {
		char ch = *string++;
		if (ch == '\0')
			break;
		if (ch == '\\') {
			ch = *string++;
			switch (ch) {

			case '\0': goto done;

			case 'a': ch = 7; break;  /* BEL */
			case 'b': ch = 8; break;  /* BS */
			case 't': ch = 9; break;  /* TAB */
			case 'n': ch = 10; break; /* LF */
			case 'v': ch = 11; break; /* VT */
			case 'f': ch = 12; break; /* FF */
			case 'r': ch = 13; break; /* CR */
//			case '\\': break; /* Unnecessary; already done by default case */

			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7': {
				/* Octal character */
				byte_t outb = (byte_t)(ch - '0');
				unsigned int count = 1;
				for (; count < 3; ++string, ++count) {
					ch = *string;
					if (!(ch >= '0' && ch <= '7'))
						break;
					outb <<= 3;
					outb |= (byte_t)(ch - '0');
				}
				ch = (char )outb;
			}	break;

			/* XXX: '\xAB' */
			/* XXX: '\u0014' */
			/* XXX: '\U00000014' */

			default:
				break;
			}
		}
		*dstbuf++ = ch;
	}
done:
	*dstbuf = '\0'; /* NUL-terminate */
	return dstbuf;
}

@@>> strccpy(3)
@@Same as `strcadd()', but re-returns `dstbuf' rather than `strend(dstbuf)'
@@@return: dstbuf: Always re-returns `dstbuf'
[[nonnull, requires_function(strcadd)]]
char *strccpy([[out]] char *dstbuf, [[in]] char const *string) {
	strcadd(dstbuf, string);
	return dstbuf;
}

@@>> strcadd(3)
@@Encode a given `string' using C-style escape sequences, and write the result to `dstbuf'
@@To prevent a buffer overflow, `dstbuf' should be at least `strlen(string) * 4 + 1' bytes
@@long (the +1 because this function appends a trailing '\0')
@@When non-NULL, characters from `dont_encode' are not encoded, but instead kept as-is.
@@@return: * : A pointer to the trailing '\0' appended to `dstbuf'
[[nonnull]]
char *streadd([[out]] char *dstbuf,
              [[in]] char const *string,
              [[in_opt]] char const *dont_encode) {
	if (dont_encode == NULL)
		dont_encode = "";
	for (;;) {
		char ch = *string++;
		if (ch == '\0')
			break;
		if ((!isprint(ch) || ch == '\\') && !strchr(dont_encode, ch)) {
			/* Escape this character. */
			*dstbuf++ = '\\';
			switch (ch) {

			case 7: ch = 'a'; break;  /* BEL */
			case 8: ch = 'b'; break;  /* BS */
			case 9: ch = 't'; break;  /* TAB */
			case 10: ch = 'n'; break; /* LF */
			case 11: ch = 'v'; break; /* VT */
			case 12: ch = 'f'; break; /* FF */
			case 13: ch = 'r'; break; /* CR */
			case '\\': break;
			/* NOTE: Yes, apparently " and ' don't get encoded... */

			default:
@@pp_if 1@@
				dstbuf += sprintf(dstbuf, "%.3o", (unsigned int)(unsigned char)ch);
@@pp_else@@
				*dstbuf++ = itoa_octal(((unsigned int)(unsigned char)ch & 0700) >> 6);
				*dstbuf++ = itoa_octal(((unsigned int)(unsigned char)ch & 070) >> 3);
				*dstbuf++ = itoa_octal(((unsigned int)(unsigned char)ch & 07));
@@pp_endif@@
				continue;
			}
		}
		*dstbuf++ = ch;
	}
/*done:*/
	*dstbuf = '\0'; /* NUL-terminate */
	return dstbuf;
}

@@>> strecpy(3)
@@Same as `streadd()', but re-returns `dstbuf' rather than `strend(dstbuf)'
@@@return: dstbuf: Always re-returns `dstbuf'
[[nonnull, requires_function(streadd)]]
char *strecpy([[out]] char *dstbuf,
              [[in]] char const *string,
              [[in_opt]] char const *dont_encode) {
	streadd(dstbuf, string, dont_encode);
	return dstbuf;
}

@@>> strfind(3)
@@Same as `p = strstr(haystack, needle); p ? p - haystack : -1'
@@@return: * : `needle' found at `haystack + return'
@@@return: -1: `needle' not found in `haystack'
[[wunused, pure, decl_include("<features.h>"), impl_include("<features.h>")]]
__STDC_INT_AS_SSIZE_T strfind([[in]] char const *haystack,
                              [[in]] char const *needle) {
	char const *ptr = strstr(haystack, needle);
	return ptr ? (__STDC_INT_AS_SSIZE_T)(ptr - haystack) : -1;
}

@@>> strrspn(3)
@@Scanning from the right, return a pointer to last character in  `haystack'
@@for which `strchr(accept, ch) != NULL'. If `haystack' consists entirely of
@@characters from `accept', re-returns `haystack'.
[[wunused, pure, nonnull]]
char *strrspn([[in]] char const *haystack,
              [[in]] char const *accept) {
	char const *iter = strend(haystack);
	while (iter > haystack && strchr(accept, iter[-1]))
		--iter;
	return (char *)iter;
}

@@>> strtrns(3)
@@Copy `string' to `result'  (including its trailing NUL),  but
@@replace any characters that appear at `find_map[i]' with  the
@@character from `repl_map[i]'. For this purpose, this function
@@assumes that at least the first `strlen(find_map)' characters
@@of `repl_map' can be accessed,  and that the `result'  buffer
@@has space for at least `strlen(string) + 1' characters.
@@@return: result: Always re-returns `result'
[[nonnull, impl_include("<bits/types.h>")]]
char *strtrns([[in]] char const *string,
              [[in]] char const *find_map,
              [[in]] char const *repl_map,
              [[out]] char *result) {
@@pp_ifdef __OPTIMIZE_SIZE__@@
	char *dst = result;
	for (;;) {
		char ch = *string++;
		char const *pos;
		if (!ch)
			break;
		pos = strchr(find_map, ch);
		if (pos != NULL)
			ch = repl_map[(size_t)(pos - find_map)];
		*dst++ = ch;
	}
	*dst++ = '\0';
	return result;
@@pp_else@@
	char map[256], ch, *dst = result;
	unsigned int i;
	for (i = 0; i < 256; ++i)
		map[i] = (char)(unsigned char)i;
	for (; *find_map; ++find_map, ++repl_map) {
		char find = *find_map;
		char repl = *repl_map;
		map[(unsigned char)find] = repl;
	}
	do {
		ch = *string++;
		ch = map[(unsigned char)ch];
		*dst++ = ch;
	} while (ch);
	return result;
@@pp_endif@@
}


%#endif /* __USE_SOLARIS */




%{

__SYSDECL_END
#endif /* __CC__ */

}
