/*[[[magic
// Because g++ is dumb and refuses to parse array
// initializers, compile this file as C, rather than C++
options["COMPILE.language"] = "c";
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.remove("-fno-rtti");
gcc_opt.append("-fexceptions");
]]]*/
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
#ifndef GUARD_LIBC_USER_LIBINTL_C
#define GUARD_LIBC_USER_LIBINTL_C 1

#include "../api.h"
/**/

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sched/atomic-rwlock.h>

#include <sys/mman.h>
#include <sys/stat.h>

#include <alloca.h>
#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <locale.h>
#include <paths.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <libc/template/hex.h>
#include <libintl.h>

#include "../libc/dl.h"
#include "../libc/globals.h"

/**/
#include "libintl.h"

DECL_BEGIN

#undef LC_COUNT

#ifndef FCALL
#define FCALL __FCALL
#endif /* !FCALL */



/* Broadcast a notification that return value of `gettext()' may have changed. */
#ifndef notify_gettext_maybe_changed
#define notify_gettext_maybe_changed() \
	(void)(++_nl_msg_cat_cntr)
#endif /* !notify_gettext_maybe_changed */


/*[[[deemon
local offset = 0;

// Supported categories
local CATEGORIES = {
	"LC_CTYPE",
	"LC_NUMERIC",
	"LC_TIME",
	"LC_COLLATE",
	"LC_MONETARY",
	"LC_MESSAGES",
	"LC_ALL",
};

local longest_catname_len = CATEGORIES.each.length > ...;
print("PRIVATE ATTR_SECTION(\".rodata.crt.i18n\") char const category_names[] =");
for (local name: CATEGORIES) {
	if (offset) {
		print(repr("\0" + name));
		++offset;
	} else {
		print(repr name);
	}
	print("#define category_names__OFFSET_", name, (" " * (longest_catname_len - #name)), " ", offset);
	offset += #name;
}
print("#define category_names__END     ", (" " * longest_catname_len), offset);
print("\"\";");
print("#define LC_COUNT 0");
for (local name: CATEGORIES) {
	print("#if ", name, " >= LC_COUNT");
	print("#undef LC_COUNT");
	print("#define LC_COUNT (", name, " + 1)");
	print("#endif /" "* ", name, " >= LC_COUNT *" "/");
}
print("#pragma GCC diagnostic push");
print("#pragma GCC diagnostic ignored \"-Woverride-init\"");
print("PRIVATE ATTR_SECTION(\".rodata.crt.i18n\") u8 const category_names_offsets[LC_COUNT] = {");
print("	[0 ... LC_COUNT - 1] = category_names__END,");
for (local name: CATEGORIES) {
	print("	[", name, "]", (" " * (longest_catname_len - #name)), " = category_names__OFFSET_", name, ",");
}
print("};");
print("#pragma GCC diagnostic pop");
]]]*/
PRIVATE ATTR_SECTION(".rodata.crt.i18n") char const category_names[] =
"LC_CTYPE"
#define category_names__OFFSET_LC_CTYPE    0
"\0LC_NUMERIC"
#define category_names__OFFSET_LC_NUMERIC  9
"\0LC_TIME"
#define category_names__OFFSET_LC_TIME     20
"\0LC_COLLATE"
#define category_names__OFFSET_LC_COLLATE  28
"\0LC_MONETARY"
#define category_names__OFFSET_LC_MONETARY 39
"\0LC_MESSAGES"
#define category_names__OFFSET_LC_MESSAGES 51
"\0LC_ALL"
#define category_names__OFFSET_LC_ALL      63
#define category_names__END                69
"";
#define LC_COUNT 0
#if LC_CTYPE >= LC_COUNT
#undef LC_COUNT
#define LC_COUNT (LC_CTYPE + 1)
#endif /* LC_CTYPE >= LC_COUNT */
#if LC_NUMERIC >= LC_COUNT
#undef LC_COUNT
#define LC_COUNT (LC_NUMERIC + 1)
#endif /* LC_NUMERIC >= LC_COUNT */
#if LC_TIME >= LC_COUNT
#undef LC_COUNT
#define LC_COUNT (LC_TIME + 1)
#endif /* LC_TIME >= LC_COUNT */
#if LC_COLLATE >= LC_COUNT
#undef LC_COUNT
#define LC_COUNT (LC_COLLATE + 1)
#endif /* LC_COLLATE >= LC_COUNT */
#if LC_MONETARY >= LC_COUNT
#undef LC_COUNT
#define LC_COUNT (LC_MONETARY + 1)
#endif /* LC_MONETARY >= LC_COUNT */
#if LC_MESSAGES >= LC_COUNT
#undef LC_COUNT
#define LC_COUNT (LC_MESSAGES + 1)
#endif /* LC_MESSAGES >= LC_COUNT */
#if LC_ALL >= LC_COUNT
#undef LC_COUNT
#define LC_COUNT (LC_ALL + 1)
#endif /* LC_ALL >= LC_COUNT */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverride-init"
PRIVATE ATTR_SECTION(".rodata.crt.i18n") u8 const category_names_offsets[LC_COUNT] = {
	[0 ... LC_COUNT - 1] = category_names__END,
	[LC_CTYPE]    = category_names__OFFSET_LC_CTYPE,
	[LC_NUMERIC]  = category_names__OFFSET_LC_NUMERIC,
	[LC_TIME]     = category_names__OFFSET_LC_TIME,
	[LC_COLLATE]  = category_names__OFFSET_LC_COLLATE,
	[LC_MONETARY] = category_names__OFFSET_LC_MONETARY,
	[LC_MESSAGES] = category_names__OFFSET_LC_MESSAGES,
	[LC_ALL]      = category_names__OFFSET_LC_ALL,
};
#pragma GCC diagnostic pop
/*[[[end]]]*/

#define CATEGORY_NAME_OFFSET(category)              \
	(unlikely((unsigned int)(category) >= LC_COUNT) \
	 ? category_names__END                          \
	 : category_names_offsets[(unsigned int)(category)])
#define _CATEGORY_NAME_OFFSET(category) \
	category_names_offsets[(unsigned int)(category)]
#define CATEGORY_NAME(category) \
	(category_names + CATEGORY_NAME_OFFSET(category))
#define _CATEGORY_NAME(category) \
	(category_names + _CATEGORY_NAME_OFFSET(category))


struct mo_file_header {
	/* NOTE: The .mo file format is described here:
	 * https://www.gnu.org/software/gettext/manual/html_node/MO-Files.html
	 */
#define MO_FILE_MAGIC 0x950412de /* Actually could also be the BSWAP32 of this, in which
                                  * case  other fields also  use the reversed byteorder.
                                  * Note  that KOS only supports native-endian mo files! */
	u32 mo_magic;    /* .mo file magic (== MO_FILE_MAGIC) */
	u32 mo_revision; /* .mo file revision (ignored; we only use features from the initial revision!) */
	u32 mo_strcount; /* # of strings */
	u32 mo_stroffs;  /* Offset  to  string offset  table  (relative to  the  file base)
	                  * >> u32 (*str_offsets)[mo_strcount][2] = FILE_BASE + mo_stroffs;
	                  * NOTE: The strings pointed to by these offsets are sorted lexicographically, ascending. */
	u32 mo_trnoffs;  /* Offset to translations offset table (relative to the file base)
	                  * >> u32 (*trn_offsets)[mo_strcount][2] = FILE_BASE + mo_stroffs; */
};


struct mo_file_string {
	u32 mfs_len; /* Length of string */
	u32 mfs_off; /* Offset of string (relative to `mf_base') */
};

#ifndef __OPTIMIZE_SIZE__
/* Because it's the most common case (s.a. `gettext(3)'),
 * we  have  a dedicated  optimization for  when `n == 1' */
#define MO_FILE_HAVE_PLURAL1
#endif /* !__OPTIMIZE_SIZE__ */

struct mo_file {
	/* .mo filename makeup:
	 *
	 * ```
	 *   /usr/share/locale/de/LC_MESSAGES/xz.mo
	 *   └┴┴┴┴┴┴┴┼┴┴┴┴┴┴┴┘ ├┘ └┴┴┴┴┼┴┴┴┴┘ ├┘└┼┘
	 *           │         │       │      │  │
	 *           │         │       │      │  └── File extension
	 *           │         │       │      └───── current_domainname
	 *           │         │       └──────────── Category (as given to `dcngettext(3)')
	 *           │         └──────────────────── Language (see below)
	 *           └────────────────────────────── Domain directory (usually `_PATH_TEXTDOMAIN')
	 * ```
	 *
	 * Language  is determined from `environ'. On KOS the results of this are cached and are only
	 * dismissed once one of `textdomain(3)', `bindtextdomain(3)' or `bind_textdomain_codeset(3)'
	 * is called:
	 *
	 * ```
	 *     getenv("LANGUAGE") ?:
	 *     getenv("LC_ALL")   ?:
	 *     getenv(CATEGORY_NAME(category)) ?: // For the `category' given to `dcngettext(3)'
	 *     getenv("LANG") ?:
	 *     NULL                               // In this case, no translating is performed,
	 *                                        // meaning that  gettext(3) simply re-returns
	 *                                        // its argument.
	 * ```
	 */
	LLRBTREE_NODE(mo_file)           mf_node;     /* [lock(mofiletree_lock)] R/B Tree node */
	uintptr_half_t                   mf_category; /* [const] Category id (one of `LC_*') */
	uintptr_half_t                   mf_red;      /* [lock(mofiletree_lock)] Red/Black bit for the tree of mo files. */
	size_t                           mf_size;     /* [const] Total size of file (== mmap'd size) */
	union {
		byte_t const                *mf_base;     /* [1..mf_size][owned][const] File base address / data blob. (mmap'd) */
		struct mo_file_header const *mf_hdr;      /* [1..1][const] File header. */
	};
	/* Cached fields. */
	size_t                           mf_strcnt;   /* [const][== mf_hdr->mo_strcount] */
	struct mo_file_string const     *mf_strtab;   /* [const][== mf_base + mf_hdr->mo_stroffs] */
	struct mo_file_string const     *mf_trntab;   /* [const][== mf_base + mf_hdr->mo_trnoffs] */
	char const                      *mf_plural;   /* [const][0..1] Plural decode expression. */
#ifdef MO_FILE_HAVE_PLURAL1
	ulongptr_t                       mf_plural1;  /* [const][valid_if(mf_plural)] The value of `eval_plural_expression(mf_plural, 1)'. */
#endif /* MO_FILE_HAVE_PLURAL1 */
	COMPILER_FLEXIBLE_ARRAY(char,    mf_name);    /* [*][const] Absolute filename of this file. */
};

/* Define the R/B-tree API */
DECL_END

#define RBTREE_WANT_TRYINSERT
#define RBTREE_OMIT_REMOVE
#define RBTREE_OMIT_REMOVENODE
#define RBTREE_OMIT_INSERT
#define RBTREE_LEFT_LEANING
#define RBTREE_DECL          PRIVATE
#define RBTREE_IMPL          PRIVATE
#define RBTREE(name)         mofiletree_##name
#define RBTREE_T             struct mo_file
#define RBTREE_Tkey          char const *
#define RBTREE_CC            FCALL
#define RBTREE_NOTHROW       NOTHROW
#define RBTREE_REDFIELD      mf_red
#define RBTREE_GETNODE(self) (self)->mf_node
#define RBTREE_GETKEY(node)  (node)->mf_name
#define RBTREE_KEY_LO(a, b)  (strcmp(a, b) < 0)
#define RBTREE_KEY_LE(a, b)  (strcmp(a, b) <= 0)
#define RBTREE_KEY_EQ(a, b)  (strcmp(a, b) == 0)
#define RBTREE_KEY_NE(a, b)  (strcmp(a, b) != 0)
#define RBTREE_KEY_GR(a, b)  (strcmp(a, b) > 0)
#define RBTREE_KEY_GE(a, b)  (strcmp(a, b) >= 0)
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN

/* [0..n][lock(mofiletree_lock)] Root for the .mo file cache tree. */
PRIVATE LLRBTREE_ROOT(mo_file) mofiletree_root = NULL;

/* Lock for the LLRB tree used to implement the .mo file cache. */
PRIVATE struct atomic_rwlock mofiletree_lock = ATOMIC_RWLOCK_INIT;

/* Helper macros for `mofiletree_lock' */
#define mofiletree_mustreap()   0
#define mofiletree_reap()       (void)0
#define _mofiletree_reap()      (void)0
#define mofiletree_write()      atomic_rwlock_write(&mofiletree_lock)
#define mofiletree_trywrite()   atomic_rwlock_trywrite(&mofiletree_lock)
#define mofiletree_endwrite()   (atomic_rwlock_endwrite(&mofiletree_lock), mofiletree_reap())
#define _mofiletree_endwrite()  atomic_rwlock_endwrite(&mofiletree_lock)
#define mofiletree_read()       atomic_rwlock_read(&mofiletree_lock)
#define mofiletree_tryread()    atomic_rwlock_tryread(&mofiletree_lock)
#define _mofiletree_endread()   atomic_rwlock_endread(&mofiletree_lock)
#define mofiletree_endread()    (void)(atomic_rwlock_endread(&mofiletree_lock) && (mofiletree_reap(), 0))
#define _mofiletree_end()       atomic_rwlock_end(&mofiletree_lock)
#define mofiletree_end()        (void)(atomic_rwlock_end(&mofiletree_lock) && (mofiletree_reap(), 0))
#define mofiletree_upgrade()    atomic_rwlock_upgrade(&mofiletree_lock)
#define mofiletree_tryupgrade() atomic_rwlock_tryupgrade(&mofiletree_lock)
#define mofiletree_downgrade()  atomic_rwlock_downgrade(&mofiletree_lock)
#define mofiletree_reading()    atomic_rwlock_reading(&mofiletree_lock)
#define mofiletree_writing()    atomic_rwlock_writing(&mofiletree_lock)
#define mofiletree_canread()    atomic_rwlock_canread(&mofiletree_lock)
#define mofiletree_canwrite()   atomic_rwlock_canwrite(&mofiletree_lock)
#define mofiletree_waitread()   atomic_rwlock_waitread(&mofiletree_lock)
#define mofiletree_waitwrite()  atomic_rwlock_waitwrite(&mofiletree_lock)





/* [0..1][lock(WRITE_ONCE || UNSAFE_CALLER)][*]
 * Cache of language names used for individual categories. These strings
 * are lazily initialized as strdup()  copies of strings retrieved  from
 * environment variables. */
PRIVATE ATTR_SECTION(".bss.crt.i18n")
char *language_names[LC_COUNT] = { [0 ... LC_COUNT - 1] = NULL };
PRIVATE ATTR_SECTION(".rodata.crt.i18n")
char const unknown_language_name[] = "";

/* Clear  cached language  names for  all categories.  This function is
 * called when one of the thread-unsafe libintl configuration functions
 * is called:
 *   - textdomain(3)
 *   - bindtextdomain(3)
 *   - bind_textdomain_codeset(3) */
PRIVATE ATTR_SECTION(".text.crt.i18n") void
NOTHROW(FCALL clear_language_cache)(void) {
	unsigned int i;
	for (i = 0; i < LC_COUNT; ++i) {
		char *lang = language_names[i];
		if (lang) {
			language_names[i] = NULL;
			if (lang != unknown_language_name)
				free(lang);
		}
	}

	/* Indicate that gettext() strings may have changed. */
	notify_gettext_maybe_changed();
}

/* Return the language name used for the given `category' of
 * messages. Returns an empty string if no language is  set.
 * NOTE: The caller must ensure that `category' is valid.
 * NOTE: Leading or trailing slashes will have been removed */
PRIVATE ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.i18n") char const *
NOTHROW(FCALL get_language_name)(int category) {
	char const *result;
	result = language_names[(unsigned int)category];
	if (!result) {
		/* Lazily initialize. */
		char const *env_lang;
		env_lang = getenv("LANGUAGE");
		if (!env_lang)
			env_lang = getenv("LC_ALL");
		if (!env_lang)
			env_lang = getenv(_CATEGORY_NAME(category));
		if (!env_lang)
			env_lang = getenv("LANG");
		if (env_lang) {
			errno_t saved_errno;
			while (*env_lang == '/')
				++env_lang;
			saved_errno = libc_geterrno();
			result = strdup(env_lang);
			if unlikely(!result) {
				libc_seterrno(saved_errno);
				/* This is the only error handling we got... :( */
				return unknown_language_name;
			}
			while (*result) {
				char *end = (char *)strend(result);
				if (end[-1] != '/')
					break;
				end[-1] = '\0';
			}
		} else {
			result = unknown_language_name;
		}
		env_lang = ATOMIC_CMPXCH_VAL(language_names[(unsigned int)category],
		                             NULL, (char *)result);
		if unlikely(env_lang != NULL) {
			if (result != unknown_language_name)
				free((char *)result);
			result = env_lang;
		}
	}
	return result;
}


struct domain_directory {
	char *dd_dom; /* [1..1][owned][const] The domain that is bound. */
	char *dd_dir; /* [1..1][owned][const] The directory that is bound. (never
	               * equal  to `default_domain_dir', and always absolute, all
	               * trailing slashes already removed) */
};

/* Domain directory binding table. */
PRIVATE ATTR_SECTION(".bss.crt.i18n")
size_t domain_directory_size = 0; /* # of domain directory bindings. */

/* [0..domain_directory_size][sort(dd_dom)][owned] List of domain directory bindings (sorted by `dd_dom'). */
PRIVATE ATTR_SECTION(".bss.crt.i18n")
struct domain_directory *domain_directory_list = NULL;

/* Default domain directory. NOTE: Code assumes that this does _NOT_ end with a trailing slash! */
INTERN ATTR_SECTION(".rodata.crt.i18n") /* `INTERN' because exported as `_nl_default_dirname' */
char const default_domain_dir[] = _PATH_TEXTDOMAIN;

/* Return the directory against which `domainname' is bound. */
ATTR_SECTION(".text.crt.i18n")
PRIVATE ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) char const *FCALL
get_domain_directory(char const *__restrict domainname) {
	size_t lo = 0, hi = domain_directory_size;
	/* Binary search for the correct entry. */
	while (lo < hi) {
		size_t i;
		int cmp;
		i   = (lo + hi) / 2;
		cmp = strcmp(domainname, domain_directory_list[i].dd_dom);
		if (cmp < 0) {
			hi = i;
		} else if (cmp > 0) {
			lo = i + 1;
		} else {
			/* Found it! */
			return domain_directory_list[i].dd_dir;
		}
	}
	return default_domain_dir;
}

typedef ulongptr_t plural_tok_t;
#define PLURAL_TOK_EOF  0     /* End-of-file */
#define PLURAL_TOK_LAND 0x100 /* && */
#define PLURAL_TOK_LOR  0x101 /* || */
#define PLURAL_TOK_EQ   0x102 /* == */
#define PLURAL_TOK_NE   0x103 /* != */
#define PLURAL_TOK_GE   0x104 /* >= */
#define PLURAL_TOK_LE   0x105 /* <= */

#define _PLURAL_TOK_CONST_BASE 0x106
#define PLURAL_TOK_ISCONST(x)      ((plural_tok_t)(x) >= _PLURAL_TOK_CONST_BASE)
#define PLURAL_TOK_GETCONST(x)     ((longptr_t)(x)-_PLURAL_TOK_CONST_BASE)
#define PLURAL_TOK_SETCONST(value) ((plural_tok_t)(value) + _PLURAL_TOK_CONST_BASE)

struct plural_parser {
	plural_tok_t pp_tok; /* Current token. */
	char const  *pp_ptr; /* [1..1] Next token text pointer. */
	longptr_t    pp_n;   /* The input constant `n' */
};


/* Plural expression tokenization. */
PRIVATE ATTR_SECTION(".text.crt.i18n") NONNULL((1)) void
NOTHROW_NCX(FCALL plural_yield)(struct plural_parser *__restrict self) {
	plural_tok_t result;
	char const *ptr = self->pp_ptr;
	char ch;
again:
	ch = *ptr++;
	switch (ch) {

	case 0x00 ... 0x08:
	case 0x0e ... 0x1f:
	case 0x0a: /* LF */
	case 0x0d: /* CR */
	case ';':
		/* End-of-file characters. */
		goto eof;

	case 0x09: /* TAB */
	case 0x0b: /* VT */
	case 0x0c: /* FF */
	case 0x20: /* SPC */
		/* Space characters. */
		goto again;

	case 'n':
		/* Special case: the input constant `n' */
		if unlikely(isalnum(*ptr))
			goto eof; /* Error */
		result = PLURAL_TOK_SETCONST(self->pp_n);
		break;

	case '0': {
		ulongptr_t value;
		ch = *ptr;
		if (ch == 'x' || ch == 'X') {
			/* Hex constant */
			ch = *++ptr;
			if (!__libc_hex2int(ch, &value))
				goto eof; /* Error */
			for (;;) {
				ulongptr_t addend;
				ch = *++ptr;
				if (!__libc_hex2int(ch, &addend))
					break; /* Error */
				value *= 16;
				value += addend;
			}
		} else if (ch == 'b' || ch == 'B') {
			/* Binary constant */
			ch = *++ptr;
			if (ch != '0' && ch != '1')
				goto eof; /* Error */
			value = ch - '0';
			for (;;) {
				ch = *++ptr;
				if (ch != '0' && ch != '1')
					break;
				value *= 2;
				value += ch - '0';
			}
		} else if (ch >= '0' && ch <= '7') {
			/* Octal constant */
			value = ch - '0';
			for (;;) {
				ch = *++ptr;
				if (!(ch >= '0' && ch <= '7'))
					break;
				value *= 8;
				value += ch - '0';
			}
		} else {
			/* Just the number '0' */
			value = 0;
		}
		result = PLURAL_TOK_SETCONST(value);
	}	break;

	case '1' ... '9': {
		/* Decimal constant */
		ulongptr_t value = ch - '0';
		for (;;) {
			ch = *ptr;
			if (!(ch >= '0' && ch <= '9'))
				break;
			value *= 10;
			value += ch - '0';
			++ptr;
		}
		result = PLURAL_TOK_SETCONST(value);
	}	break;

	/* Multi-character tokens. */
	case '&':
		if (*ptr == '&') {
			++ptr;
			result = PLURAL_TOK_LAND;
		} else {
			goto defl;
		}
		break;

	case '|':
		if (*ptr == '|') {
			++ptr;
			result = PLURAL_TOK_LOR;
		} else {
			goto defl;
		}
		break;

	case '=':
		if (*ptr == '=') {
			++ptr;
			result = PLURAL_TOK_EQ;
		} else {
			goto defl;
		}
		break;

	case '!':
		if (*ptr == '=') {
			++ptr;
			result = PLURAL_TOK_NE;
		} else {
			goto defl;
		}
		break;

	case '>':
		if (*ptr == '=') {
			++ptr;
			result = PLURAL_TOK_GE;
		} else {
			goto defl;
		}
		break;

	case '<':
		if (*ptr == '=') {
			++ptr;
			result = PLURAL_TOK_LE;
		} else {
			goto defl;
		}
		break;

	default:
defl:
		result = (plural_tok_t)(unsigned char)ch;
		break;
	}
	self->pp_ptr = ptr;
	self->pp_tok = result;
	return;
eof:
	self->pp_tok = PLURAL_TOK_EOF;
}

/* The following c-like operators are supported (in this priority order):
 *   UNARY  ::=  '!' UNARY | '-' UNARY | <CONST> | '(' COND ')'
 *   PROD   ::=  UNARY | UNARY '*' PROD | UNARY '/' PROD | UNARY '%' PROD
 *   SUM    ::=  PROD | PROD '+' SUM | PROD '-' SUM
 *   CMP    ::=  SUM | SUM '<' CMP | SUM '>' CMP | SUM '<=' CMP | SUM '>=' CMP
 *   CMPEQ  ::=  CMP | CMP '==' CMPEQ | CMP '!=' CMPEQ
 *   LAND   ::=  CMPEQ | CMPEQ '&&' LAND
 *   LOR    ::=  LAND | LAND '||' LOR
 *   COND   ::=  LOR | LOR '?' COND ':' COND
 */

PRIVATE WUNUSED NONNULL((1)) longptr_t
NOTHROW_NCX(FCALL plural_cond)(struct plural_parser *__restrict self);
PRIVATE ATTR_SECTION(".text.crt.i18n") WUNUSED NONNULL((1)) longptr_t
NOTHROW_NCX(FCALL plural_unary)(struct plural_parser *__restrict self) {
	longptr_t result;
	plural_tok_t tok;
	tok = self->pp_tok;
	plural_yield(self);
	switch (tok) {

	case '-':
		result = -plural_unary(self);
		break;

	case '!':
		result = !plural_unary(self);
		break;

	case '(':
		result = plural_cond(self);
		if likely(self->pp_tok == ')') {
			plural_yield(self);
		} else {
			/* Force EOF */
			self->pp_tok = PLURAL_TOK_EOF;
			self->pp_ptr = strend(self->pp_ptr);
		}
		break;

	default:
		if (PLURAL_TOK_ISCONST(tok)) {
			result = PLURAL_TOK_GETCONST(tok);
		} else {
			result = 0; /* Invalid token... */
		}
		break;
	}
	return result;
}

PRIVATE ATTR_SECTION(".text.crt.i18n") WUNUSED NONNULL((1)) longptr_t
NOTHROW_NCX(FCALL plural_prod)(struct plural_parser *__restrict self) {
	longptr_t other, result = plural_unary(self);
	while (self->pp_tok == '*' || self->pp_tok == '/' || self->pp_tok == '%') {
		plural_tok_t cmd = self->pp_tok;
		plural_yield(self);
		other = plural_unary(self);
		if (cmd == '*') {
			result = result * other;
		} else if (other != 0) {
			result = cmd == '/' ? (result / other)
			                    : (result % other);
		}
	}
	return result;
}

PRIVATE ATTR_SECTION(".text.crt.i18n") WUNUSED NONNULL((1)) longptr_t
NOTHROW_NCX(FCALL plural_sum)(struct plural_parser *__restrict self) {
	longptr_t other, result = plural_prod(self);
	while (self->pp_tok == '+' || self->pp_tok == '-') {
		plural_tok_t cmd = self->pp_tok;
		plural_yield(self);
		other = plural_prod(self);
		result = cmd == '+' ? (result + other)
		                    : (result - other);
	}
	return result;
}

PRIVATE ATTR_SECTION(".text.crt.i18n") WUNUSED NONNULL((1)) longptr_t
NOTHROW_NCX(FCALL plural_cmp)(struct plural_parser *__restrict self) {
	longptr_t other, result = plural_sum(self);
	while (self->pp_tok == '<' || self->pp_tok == PLURAL_TOK_LE ||
	       self->pp_tok == '>' || self->pp_tok == PLURAL_TOK_GE) {
		plural_tok_t cmd = self->pp_tok;
		plural_yield(self);
		other = plural_sum(self);
		if (cmd == '<') {
			result = result < other;
		} else if (cmd == PLURAL_TOK_LE) {
			result = result <= other;
		} else if (cmd == '>') {
			result = result > other;
		} else {
			result = result >= other;
		}
	}
	return result;
}

PRIVATE ATTR_SECTION(".text.crt.i18n") WUNUSED NONNULL((1)) longptr_t
NOTHROW_NCX(FCALL plural_cmpeq)(struct plural_parser *__restrict self) {
	longptr_t other, result = plural_cmp(self);
	while (self->pp_tok == PLURAL_TOK_EQ || self->pp_tok == PLURAL_TOK_NE) {
		plural_tok_t cmd = self->pp_tok;
		plural_yield(self);
		other = plural_cmp(self);
		result = cmd == PLURAL_TOK_EQ ? (result == other)
		                              : (result != other);
	}
	return result;
}

PRIVATE ATTR_SECTION(".text.crt.i18n") WUNUSED NONNULL((1)) longptr_t
NOTHROW_NCX(FCALL plural_land)(struct plural_parser *__restrict self) {
	longptr_t other, result = plural_cmpeq(self);
	while (self->pp_tok == PLURAL_TOK_LAND) {
		plural_yield(self);
		other  = plural_cmpeq(self);
		result = result && other;
	}
	return result;
}

PRIVATE ATTR_SECTION(".text.crt.i18n") WUNUSED NONNULL((1)) longptr_t
NOTHROW_NCX(FCALL plural_lor)(struct plural_parser *__restrict self) {
	longptr_t other, result = plural_land(self);
	while (self->pp_tok == PLURAL_TOK_LOR) {
		plural_yield(self);
		other  = plural_land(self);
		result = result || other;
	}
	return result;
}

PRIVATE ATTR_SECTION(".text.crt.i18n") WUNUSED NONNULL((1)) longptr_t
NOTHROW_NCX(FCALL plural_cond)(struct plural_parser *__restrict self) {
	longptr_t result;
	result = plural_lor(self);
	if (self->pp_tok == '?') {
		longptr_t tt, ff;
		plural_yield(self);
		tt = plural_cond(self);
		if (self->pp_tok == ':')
			plural_yield(self);
		ff = plural_cond(self);
		result = result ? tt : ff;
	}
	return result;
}

/* Evaluate a plural expression and return the strend^N index to-be used. */
PRIVATE ATTR_SECTION(".text.crt.i18n") ATTR_PURE WUNUSED NONNULL((1)) ulongptr_t
NOTHROW_NCX(FCALL eval_plural_expression)(char const *__restrict expr,
                                          longptr_t n) {
	longptr_t result;
	struct plural_parser parser;
	parser.pp_ptr = expr;
	parser.pp_n   = n;
	plural_yield(&parser); /* Yield the first token. */

	/* Evaluate the expression. */
	result = plural_cond(&parser);

	/*syslog(LOG_DEBUG, "eval_plural_expression(%$q, %ld) -> %lu\n",
	       (size_t)(parser.pp_ptr - expr), expr, n, (ulongptr_t)result);*/

	/* Return the result */
	return (ulongptr_t)result;
}


/* Parse meta-data information. */
PRIVATE ATTR_SECTION(".text.crt.i18n") ATTR_PURE WUNUSED NONNULL((1)) char const *
NOTHROW_NCX(FCALL mo_extract_plural_from_metadata)(char const *__restrict header,
                                                   size_t header_len) {
	char const *header_end;
	/* We only care about plural information. The header contains line-wise
	 * instructions of where to find that sort of information, and the line
	 * we're looking for looks something like this:
	 * >> "Plural-Forms: nplurals=2; plural=(n != 1);\n"
	 * The part we're actually interested in here is "(n != 1);", where we
	 * want to return the pointer to the "(".
	 *
	 * When translating strings, we then parse the associated expression via
	 * a dedicated evaluation engine, which then evaluates to an addend that
	 * is to-be applied to translations by use of strend^N.
	 * In the above example then, do `return = strend(return)+1' whenever
	 * the `n'  argument  given  to  `dcngettext(3)'  differs  from  `1'.
	 *
	 * The expression parser treats these characters as EOF:
	 *     - ';',        (just a semicolon)
	 *     - 0 ... 31    (all control characters, but excluding `isspace(3)' ones, but including \n and \r)
	 *     - ')'         (only if unmatched by a preceding ')')
	 */
	header_end = header + header_len;
#define islf(ch) ((ch) == '\n' || (ch) == '\r')
	while (header < header_end) {
		char const *iter, *line_end;
		line_end = iter = header;
		while (line_end < header_end && !islf(*line_end))
			++line_end;
		/* Skip leading spaces. */
		while (iter < line_end && isspace(*iter))
			++iter;
		if (memcmp(iter, "Plural-Forms", 12 * sizeof(char)) == 0) {
			/* NOTE: No need to check for bounds with `line_end', because we
			 *       know that `line_end' is succeeded by \n or \r,  neither
			 *       of which are apart of the string "Plural-Forms". */
			iter += 12;
			while (iter < line_end && isspace(*iter))
				++iter;
			if (*iter == ':') {
				++iter;
				/* Found it! The rest of the  line is a sequence of  ";"-seperated
				 * expressions of the form "NAME=VALUE". We're looking for the one
				 * where NAME is `plural' */
				for (;;) {
					while (iter < line_end && isspace(*iter))
						++iter;
					if (iter >= line_end)
						break;
					if (memcmp(iter, "plural", 6 * sizeof(char)) == 0) {
						iter += 6;
						while (iter < line_end && isspace(*iter))
							++iter;
						if (*iter == '=') {
							++iter;
							while (iter < line_end && isspace(*iter))
								++iter;
							/* This is where the expression starts! */
							if (*iter <= 31 || *iter == ';')
								return NULL; /* No/empty plural expression? */
							return iter;
						}
					}
					/* Go to the next element of the expression list. */
					iter = (char const *)memend(iter, ';', (size_t)(line_end - iter)) + 1;
				}
			}
		}

		/* Go to the next line. */
		while (line_end < header_end && islf(*line_end))
			++line_end;
		header = line_end;
	}
	return NULL;
}

/* Try to open a .mo file for the given specs. */
PRIVATE ATTR_SECTION(".text.crt.i18n") ATTR_NOINLINE WUNUSED NONNULL((1)) struct mo_file *
NOTHROW_NCX(FCALL open_mo_file)(char const *__restrict domainname, int category) {
	struct mo_file *result;
	char const *lng; /* Used language name */
	char const *dir; /* Used domain directory */
	char const *cat; /* Category name */
	size_t lng_len;
	size_t dir_len;
	size_t cat_len;
	size_t dom_len;
	char *filename;
	size_t filename_size;
	errno_t saved_errno;
	cat = CATEGORY_NAME(category);
	if unlikely(!*cat)
		goto fail; /* Invalid category... */
	lng = get_language_name(category);
	if (!*lng)
		goto fail; /* No language specified. */
	dir = get_domain_directory(domainname);

	/* Load string lengths. */
	dir_len = strlen(dir);
	lng_len = strlen(lng);
	cat_len = strlen(cat);
	dom_len = strlen(domainname);

	/* Construct the full filename. */
	filename_size = dir_len + 1 + lng_len + 1 + cat_len + 1 + dom_len + 3;
	filename_size = (filename_size + 1) * sizeof(char);
	filename      = (char *)alloca(filename_size);
	{
		char *iter = filename;
		iter = (char *)mempcpy(iter, dir, dir_len, sizeof(char));
		*iter++ = '/';
		iter = (char *)mempcpy(iter, lng, lng_len, sizeof(char));
		*iter++ = '/';
		iter = (char *)mempcpy(iter, cat, cat_len, sizeof(char));
		*iter++ = '/';
		iter = (char *)mempcpy(iter, domainname, dom_len, sizeof(char));
		*iter++ = '.';
		*iter++ = 'm';
		*iter++ = 'o';
		*iter++ = '\0';
	}

	/* Look through the cache for a file with this name. */
again_load_from_tree:
	mofiletree_read();
	result = mofiletree_locate(mofiletree_root, filename);
	mofiletree_endread();
	if (result)
		goto done;

	/* Save `errno' so we can restore it if something goes wrong.
	 * After all: we're  not allowed to change `errno', which is
	 *            understandable since we're  here to  translate
	 *            strings, which may in turn reference their own
	 *            errno values. */
	saved_errno = libc_geterrno();

	/* Must allocate+open a new file. */
	result = (struct mo_file *)malloc(sizeof(struct mo_file) +
	                                  filename_size);
	if unlikely(!result)
		goto err;

	/* Open the file and try to map it into memory. */
	{
		fd_t fd;
		struct stat st;
		struct mo_file_header *base;
		fd = open(filename, O_RDONLY | O_CLOEXEC);
		if unlikely(fd < 0)
			goto err_r;
		if unlikely(fstat(fd, &st) != 0) {
err_r_fd:
			close(fd);
			goto err_r;
		}

		/* Make sure the file is large enough. */
		if unlikely((size_t)st.st_size < sizeof(struct mo_file_header))
			goto err_r_fd;

		/* Map into memory. */
		base = (struct mo_file_header *)mmap(NULL, (size_t)st.st_size, PROT_READ,
		                                     MAP_PRIVATE | MAP_FILE, fd, 0);
		if unlikely(base == (struct mo_file_header *)MAP_FAILED)
			goto err_r_fd;
		close(fd);

		/* Make sure that the .mo file header is intact. */
		if unlikely(base->mo_magic != MO_FILE_MAGIC) {
err_r_map:
			munmap(base, (size_t)st.st_size);
			goto err_r;
		}
		{
			u32 maxoff, size;
			maxoff = base->mo_trnoffs;
			/* Specs hint translations come after strings, so optimize for that case. */
			if unlikely(maxoff < base->mo_stroffs)
				maxoff = base->mo_stroffs;

			/* Verify that offsets within the header  are all OK. Note that  because
			 * we're using `MAP_PRIVATE', we're guarantied that the data of our file
			 * mapping won't change, even when  another process would attempt to  do
			 * so. (Meaning that these offsets will _remain_ valid) */
			if (OVERFLOW_UMUL(base->mo_strcount, 8, &size))
				goto err_r_map;
			if (OVERFLOW_UADD(maxoff, size, &maxoff))
				goto err_r_map;
			if (maxoff > (size_t)st.st_size)
				goto err_r_map;
		}

		result->mf_size   = (size_t)st.st_size;
		result->mf_base   = (byte_t const *)base;
		result->mf_strcnt = base->mo_strcount;
		result->mf_strtab = (struct mo_file_string const *)((byte_t const *)base + base->mo_stroffs);
		result->mf_trntab = (struct mo_file_string const *)((byte_t const *)base + base->mo_trnoffs);

		/* Load plural information. */
		result->mf_plural = NULL;
		if (base->mo_strcount > 1 && result->mf_strtab[0].mfs_len == 0) {
			u32 offset;
			if (!OVERFLOW_UADD(result->mf_trntab[0].mfs_off,
			                   result->mf_trntab[0].mfs_len,
			                   &offset) &&
			    offset < result->mf_size) {
				char const *metadata;
				size_t metadata_len;
				metadata     = (char const *)(result->mf_base + result->mf_trntab[0].mfs_off);
				metadata_len = result->mf_trntab[0].mfs_len;
				/* Extract the plural expression. */
				result->mf_plural = mo_extract_plural_from_metadata(metadata, metadata_len);
#ifdef MO_FILE_HAVE_PLURAL1
				if (result->mf_plural)
					result->mf_plural1 = eval_plural_expression(result->mf_plural, 1);
#endif /* MO_FILE_HAVE_PLURAL1 */
			}
		}
	}

	/* Fill in the other fields of the new file. */
	memcpy(result->mf_name, filename, filename_size);
	result->mf_category = (uintptr_half_t)(unsigned int)category;

	/* Now try to insert the new descriptor into the tree. */
	mofiletree_write();
	if unlikely(!mofiletree_tryinsert(&mofiletree_root, result)) {
		/* Race condition: another thread was faster. */
		mofiletree_endwrite();
		munmap((void *)result->mf_base, result->mf_size);
		free(result);
		goto again_load_from_tree;
	}
	mofiletree_endwrite();

	/* And we're done! */

done:
	return result;
err_r:
	free(result);
err:
	libc_seterrno(saved_errno);
fail:
	result = NULL;
	goto done;
}

/* Cache for the last-accessed mo-file. */
PRIVATE ATTR_SECTION(".bss.crt.i18n") struct atomic_rwlock last_lock       = ATOMIC_RWLOCK_INIT;
PRIVATE ATTR_SECTION(".bss.crt.i18n") struct mo_file /**/ *last_file       = NULL;
PRIVATE ATTR_SECTION(".bss.crt.i18n") int /*            */ last_category   = 0;
PRIVATE ATTR_SECTION(".bss.crt.i18n") char const /*    */ *last_domainname = NULL;

/* Helper macros for `last_lock' */
#define last_mustreap()   0
#define last_reap()       (void)0
#define _last_reap()      (void)0
#define last_write()      atomic_rwlock_write(&last_lock)
#define last_trywrite()   atomic_rwlock_trywrite(&last_lock)
#define last_endwrite()   (atomic_rwlock_endwrite(&last_lock), last_reap())
#define _last_endwrite()  atomic_rwlock_endwrite(&last_lock)
#define last_read()       atomic_rwlock_read(&last_lock)
#define last_tryread()    atomic_rwlock_tryread(&last_lock)
#define _last_endread()   atomic_rwlock_endread(&last_lock)
#define last_endread()    (void)(atomic_rwlock_endread(&last_lock) && (last_reap(), 0))
#define _last_end()       atomic_rwlock_end(&last_lock)
#define last_end()        (void)(atomic_rwlock_end(&last_lock) && (last_reap(), 0))
#define last_upgrade()    atomic_rwlock_upgrade(&last_lock)
#define last_tryupgrade() atomic_rwlock_tryupgrade(&last_lock)
#define last_downgrade()  atomic_rwlock_downgrade(&last_lock)
#define last_reading()    atomic_rwlock_reading(&last_lock)
#define last_writing()    atomic_rwlock_writing(&last_lock)
#define last_canread()    atomic_rwlock_canread(&last_lock)
#define last_canwrite()   atomic_rwlock_canwrite(&last_lock)
#define last_waitread()   atomic_rwlock_waitread(&last_lock)
#define last_waitwrite()  atomic_rwlock_waitwrite(&last_lock)



/* Return the .mo file associated with the given arguments. */
PRIVATE ATTR_SECTION(".text.crt.i18n") WUNUSED NONNULL((1)) struct mo_file *FCALL
get_mo_file(char const *__restrict domainname, int category) {
	struct mo_file *result;
	last_read();
	if (last_category == category) {
		if (last_domainname == domainname) {
			result = last_file;
			last_endread();
			return result;
		}
#ifndef __OPTIMIZE_SIZE__
		else if (strcmp(last_domainname, domainname) == 0) {
			/* Different memory location, but same string! */
			if (!last_upgrade()) {
				if (last_category != category) {
					last_endwrite();
					goto load_file_slowly;
				}
			}
			last_domainname = domainname;
			result          = last_file;
			last_endwrite();
			return result;
		}
#endif /* !__OPTIMIZE_SIZE__ */
	}
	last_endread();
#ifndef __OPTIMIZE_SIZE__
load_file_slowly:
#endif /* !__OPTIMIZE_SIZE__ */

	/* Open a new/cached .mo file */
	result = open_mo_file(domainname, category);

	/* On success, remember the last used file. */
	if (result) {
		last_write();
		last_file       = result;
		last_category   = category;
		last_domainname = domainname;
		last_endwrite();
	}
	return result;
}


/* [0..1][owned] Current domain name (as set by `textdomain()')
 * Defaults to the part after the last slash in `dlmodulename(dlopen(NULL, 0))' */
PRIVATE ATTR_SECTION(".bss.crt.i18n") char *current_domainname = NULL;


/* Translate the given message. */
PRIVATE ATTR_SECTION(".text.crt.i18n") ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) char const *
NOTHROW_NCX(FCALL mo_file_translate)(struct mo_file *__restrict self,
                                     char const *__restrict msgid) {
	size_t lo, hi;
	/* The specs promise that strings are sorted lexicographically.
	 * As such, we're able to perform a binary search to find  what
	 * we're after! */
	lo = 0;
	hi = self->mf_strcnt;
	while (lo < hi) {
		size_t i;
		u32 offset, size, end_offset;
		char const *str;
		int cmp;
		i      = (lo + hi) / 2;
		offset = self->mf_strtab[i].mfs_off;
		size   = self->mf_strtab[i].mfs_len;
		if unlikely(OVERFLOW_UADD(offset, size, &end_offset) ||
		            end_offset >= self->mf_size)
			goto corrupt;
		str = (char const *)(self->mf_base + offset);
		if unlikely(str[size] != '\0')
			goto corrupt;
		cmp = strcmp(msgid, str);
		if (cmp < 0) {
			hi = i;
		} else if (cmp > 0) {
			lo = i + 1;
		} else {
			/* Found it! */
			offset = self->mf_trntab[i].mfs_off;
			size   = self->mf_trntab[i].mfs_len;
			if unlikely(OVERFLOW_UADD(offset, size, &end_offset) ||
			            end_offset >= self->mf_size)
				goto corrupt;
			str = (char const *)(self->mf_base + offset);
			if unlikely(str[size] != '\0')
				goto corrupt;
			return str;
		}
	}
fallback:
	return msgid;
corrupt:
	self->mf_strcnt = 0; /* There's something wrong (don't try again in the future...) */
	goto fallback;
}

/* Translate the given message. */
PRIVATE ATTR_SECTION(".text.crt.i18n") ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) char const *
NOTHROW_NCX(FCALL mo_file_translate_plural)(struct mo_file *__restrict self,
                                            char const *__restrict msgid,
                                            ulongptr_t index) {
	size_t lo, hi;
	/* The specs promise that strings are sorted lexicographically.
	 * As such, we're able to perform a binary search to find  what
	 * we're after! */
	lo = 0;
	hi = self->mf_strcnt;
	while (lo < hi) {
		size_t i;
		u32 offset, size, end_offset;
		char const *str;
		int cmp;
		i      = (lo + hi) / 2;
		offset = self->mf_strtab[i].mfs_off;
		size   = self->mf_strtab[i].mfs_len;
		if unlikely(OVERFLOW_UADD(offset, size, &end_offset) ||
		            end_offset >= self->mf_size)
			goto corrupt;
		str = (char const *)(self->mf_base + offset);
		if unlikely(str[size] != '\0')
			goto corrupt;
		cmp = strcmp(msgid, str);
		if (cmp < 0) {
			hi = i;
		} else if (cmp > 0) {
			lo = i + 1;
		} else {
			/* Found it! */
			offset = self->mf_trntab[i].mfs_off;
			size   = self->mf_trntab[i].mfs_len;
			if unlikely(OVERFLOW_UADD(offset, size, &end_offset) ||
			            end_offset >= self->mf_size)
				goto corrupt;
			str = (char const *)(self->mf_base + offset);
			if unlikely(str[size] != '\0')
				goto corrupt;
			if (index > 0) {
				/* Skip to the index'th strend^N string.
				 *
				 * If  no such string  exists, ignore the plural
				 * index and simply return the base translation. */
				char const *end = str + size;
				char const *result = str;
				do {
					result = strend(result) + 1;
					if unlikely(result >= end)
						goto ignore_plural;
				} while (--index);
				return result;
			}
ignore_plural:
			return str;
		}
	}
fallback:
	return msgid;
corrupt:
	self->mf_strcnt = 0; /* There's something wrong (don't try again in the future...) */
	goto fallback;
}





/*[[[head:libc_dcngettext,hash:CRC-32=0xe2aa49d1]]]*/
INTERN ATTR_SECTION(".text.crt.i18n") ATTR_PURE WUNUSED ATTR_IN_OPT(1) ATTR_IN_OPT(2) ATTR_IN_OPT(3) __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3) char *
NOTHROW_NCX(LIBCCALL libc_dcngettext)(char const *domainname,
                                      char const *msgid_singular,
                                      char const *msgid_plural,
                                      ulongptr_t n,
                                      int category)
/*[[[body:libc_dcngettext]]]*/
{
	struct mo_file *file;

	/* If NULL, use the default domain name. */
	if likely(!domainname) {
		domainname = current_domainname;

		/* If `textdomain(3)' hasn't  been called yet,  then we  must
		 * initialize the default textdomain of the program manually. */
		if unlikely(!domainname) {
			errno_t saved_errno;
			/* As per the specs, we're not allowed to modify errno.
			 * But because textdomain(3) may modify it on error, we
			 * have to save and restore if that happens. */
			saved_errno = libc_geterrno();
			domainname  = libc_textdomain(NULL);
			if unlikely(!domainname) {
				libc_seterrno(saved_errno);
				goto fail;
			}
		}
	}

	file = get_mo_file(domainname, category);
	if (file) {
		char const *msgid = msgid_singular;
		if (file->mf_plural != NULL) {
			/* Plural  parsing support! */
			ulongptr_t index;
			if unlikely(msgid == NULL)
				return NULL;
			/* Calculate the plural expression index. */
#ifdef MO_FILE_HAVE_PLURAL1
			if (n == 1) {
				index = file->mf_plural1;
			} else
#endif /* MO_FILE_HAVE_PLURAL1 */
			{
				index = eval_plural_expression(file->mf_plural, n);
			}
			return (char *)mo_file_translate_plural(file, msgid, index);
		}

		/* Actually retrieve strings. */
		if (n != 1)
			msgid = msgid_plural;
		if likely(msgid != NULL)
			msgid = mo_file_translate(file, msgid);
		return (char *)msgid;
	}
fail:
	return n == 1 ? (char *)msgid_singular
	              : (char *)msgid_plural;
}
/*[[[end:libc_dcngettext]]]*/

/*[[[head:libc_textdomain,hash:CRC-32=0x1c4888fb]]]*/
INTERN ATTR_SECTION(".text.crt.i18n") char *
NOTHROW_NCX(LIBCCALL libc_textdomain)(char const *domainname)
/*[[[body:libc_textdomain]]]*/
{
	char *result;
	if (domainname) {
		/* Set the new default domain name. */
		result = strdup(domainname);
		if likely(result) {
			free(current_domainname);
			current_domainname = result;
			clear_language_cache();
		}
	} else {
		result = current_domainname;
		if (!result) {
			char const *modnam;
			modnam = dlmodulename(dlopen(NULL, 0));
			if unlikely(!modnam)
				modnam = "messages";                      /* Fallback (should never be needed) */
			result = (char *)strrchrnul(modnam, '/') + 1; /* Yes! This also works when there isn't a slash... */
			result = strdup(result);
			if likely(result) {
				current_domainname = result;
			}
		}
	}
	return result;
}
/*[[[end:libc_textdomain]]]*/

/*[[[head:libc_bindtextdomain,hash:CRC-32=0x7725190e]]]*/
INTERN ATTR_SECTION(".text.crt.i18n") char *
NOTHROW_NCX(LIBCCALL libc_bindtextdomain)(char const *domainname,
                                          char const *dirname)
/*[[[body:libc_bindtextdomain]]]*/
{
	char *result;
	if unlikely(!domainname || !*domainname)
		return NULL; /* Invalid argument */
	if (!dirname) {
		result = (char *)get_domain_directory(domainname);
	} else if (strcmp(dirname, default_domain_dir) == 0) {
		size_t lo, hi;
delete_domain_name:
		lo = 0;
		hi = domain_directory_size;
		/* Binary search for the correct entry. */
		while (lo < hi) {
			size_t i;
			int cmp;
			i   = (lo + hi) / 2;
			cmp = strcmp(domainname, domain_directory_list[i].dd_dom);
			if (cmp < 0) {
				hi = i;
			} else if (cmp > 0) {
				lo = i + 1;
			} else {
				struct domain_directory ent;
				memcpy(&ent, &domain_directory_list[i],
				       sizeof(struct domain_directory));
				/* Remove this entry from the set. */
				--domain_directory_size;
				if (!domain_directory_size) {
					struct domain_directory *list;
					list = domain_directory_list;
					domain_directory_list = NULL;
					free(list);
				} else {
					struct domain_directory *list;
					memmovedown(&domain_directory_list[i],
					            &domain_directory_list[i + 1],
					            domain_directory_size - i,
					            sizeof(struct domain_directory));
					/* Try to release unused memory. */
					list = (struct domain_directory *)realloc(domain_directory_list,
					                                          domain_directory_size,
					                                          sizeof(struct domain_directory));
					if likely(list)
						domain_directory_list = list;
				}
				free(ent.dd_dom);
				free(ent.dd_dir);
				break;
			}
		}
		result = (char *)default_domain_dir;
	} else {
		/* Make sure that the given path is absolute. */
		result = canonicalize_file_name(dirname);
		if likely(result) {
			size_t lo, hi;
			/* Do another check if this is actually the default directory. */
			if (strcmp(result, default_domain_dir) == 0) {
				free(result);
				goto delete_domain_name;
			}
			/* Insert into the list or override. */
			lo = 0;
			hi = domain_directory_size;
			while (lo < hi) {
				size_t i;
				int cmp;
				i   = (lo + hi) / 2;
				cmp = strcmp(domainname, domain_directory_list[i].dd_dom);
				if (cmp < 0) {
					hi = i;
				} else if (cmp > 0) {
					lo = i + 1;
				} else {
					struct domain_directory ent;
					char *olddir;
					memcpy(&ent, &domain_directory_list[i],
					       sizeof(struct domain_directory));
					/* Override an existing entry. */
					olddir     = ent.dd_dir;
					ent.dd_dir = result;
					free(olddir);
					goto done;
				}
			}
			assert(lo == hi);
			/* Insert a new entry at `lo' */
			{
				struct domain_directory *list;
				char *domainname_copy;
				list = (struct domain_directory *)realloc(domain_directory_list,
				                                          domain_directory_size + 1,
				                                          sizeof(struct domain_directory));
				if unlikely(!list) {
err_r:
					free(result);
					result = NULL;
					goto done;
				}
				domain_directory_list = list;

				/* Create a duplicate of the domain name.
				 * This copy will be owned by the new entry we're creating. */
				domainname_copy = strdup(domainname);
				if unlikely(!domainname_copy)
					goto err_r;

				/* Shift the list to free up an entry. */
				memmoveup(&list[lo + 1],
				          &list[lo],
				          domain_directory_size - lo,
				          sizeof(struct domain_directory));

				/* Fill in the new entry. */
				list[lo].dd_dom = domainname_copy;
				list[lo].dd_dir = result;

				/* Finally, update the directory table size to reflect changes. */
				++domain_directory_size;
			}
		}
	}
done:
	return result;
}
/*[[[end:libc_bindtextdomain]]]*/

/*[[[head:libc_bind_textdomain_codeset,hash:CRC-32=0x96f3a897]]]*/
INTERN ATTR_SECTION(".text.crt.i18n") char *
NOTHROW_NCX(LIBCCALL libc_bind_textdomain_codeset)(char const *domainname,
                                                   char const *codeset)
/*[[[body:libc_bind_textdomain_codeset]]]*/
{
	/* XXX: Implement me? */
	(void)domainname;
	(void)codeset;
	clear_language_cache();
	return (char *)codeset;
}
/*[[[end:libc_bind_textdomain_codeset]]]*/


/* This  is a special variable also visible to loaded programs, that
 * gets incremented every time anything  happens that may result  in
 * `gettext()' returning a different value from a given string, than
 * what it may have returned during a preceding invocation.
 *
 * This may be used by programs to cache translated strings for  as
 * long as they remain valid. And most importantly: this fixes some
 * configure  scripts that test  for a variable  by this name being
 * exported from libc (*cough* midnight-commander *cough*)... */
INTERN ATTR_SECTION(".bss.crt.i18n") int libc__nl_msg_cat_cntr = 0;
#undef _nl_msg_cat_cntr
DEFINE_PUBLIC_ALIAS(_nl_msg_cat_cntr, libc__nl_msg_cat_cntr);

/* Export the default domain directory by-name. (XXX: In the  original
 * glibc, programs could override this symbol and have libintl pick up
 * on that during initialization; this  could easily be added to  KOS,
 * but I've yet to do so since  I don't think that programs should  do
 * something  like that, because  `bindtextdomain(3)' already does the
 * same) */
#undef _nl_default_dirname
DEFINE_PUBLIC_ALIAS(_nl_default_dirname, default_domain_dir);

/* I don't really know what this symbol is supposed to be all about.
 * It's exported by glibc as `struct binding *_nl_domain_bindings;',
 * and looks like some kind of interface to internals.
 *
 * It  has to be exported because configure scripts exist that check
 * for this symbol being present. However, OpenSolaris also includes
 * compat for this scenario, and it  simply defines it as an  unused
 * NULL-pointer  to an integer. - So we  simply do the same and hope
 * for the best ;) */
#undef _nl_domain_bindings
INTERN ATTR_SECTION(".bss.crt.i18n") int *libc__nl_domain_bindings = NULL;
DEFINE_PUBLIC_ALIAS(_nl_domain_bindings, libc__nl_domain_bindings);




/*[[[start:exports,hash:CRC-32=0x2829af3a]]]*/
DEFINE_PUBLIC_ALIAS(dcngettext, libc_dcngettext);
DEFINE_PUBLIC_ALIAS(textdomain, libc_textdomain);
DEFINE_PUBLIC_ALIAS(bindtextdomain, libc_bindtextdomain);
DEFINE_PUBLIC_ALIAS(bind_textdomain_codeset, libc_bind_textdomain_codeset);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_LIBINTL_C */
