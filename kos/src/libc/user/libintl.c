/*[[[magic
// Because g++ is dumb and refuses to parse array
// initializers, compile this file as C, rather than C++
options["COMPILE.language"] = "c";
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.remove("-fno-rtti");
gcc_opt.append("-fexceptions");
]]]*/
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
#ifndef GUARD_LIBC_USER_LIBINTL_C
#define GUARD_LIBC_USER_LIBINTL_C 1

#include "../api.h"
/**/

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <sys/mman.h>
#include <sys/stat.h>

#include <alloca.h>
#include <assert.h>
#include <fcntl.h>
#include <locale.h>
#include <paths.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <libintl.h>

#include "../libc/dl.h"
#include "../libc/globals.h"

/**/
#include "libintl.h"

DECL_BEGIN

#undef LC_COUNT

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
print("PRIVATE char const category_names[] =");
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
print("PRIVATE u8 const category_names_offsets[LC_COUNT] = {");
print("	[0 ... LC_COUNT - 1] = category_names__END,");
for (local name: CATEGORIES) {
	print("	[", name, "]", (" " * (longest_catname_len - #name)), " = category_names__OFFSET_", name, ",");
}
print("};");
print("#pragma GCC diagnostic pop");
]]]*/
PRIVATE char const category_names[] =
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
PRIVATE u8 const category_names_offsets[LC_COUNT] = {
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
                                  * Note that KOS only supports same-endian mo files! */
	u32 mo_magic;    /* .mo file magic (== MO_FILE_MAGIC) */
	u32 mo_revision; /* .mo file revision (ignored; we only use features from the initial revision!) */
	u32 mo_strcount; /* # of strings */
	u32 mo_stroffs;  /* Offset  to  string offset  table  (relative to  the  file base)
	                  * >> u32 (*str_offsets)[mo_strcount][2] = FILE_BASE + mo_stroffs;
	                  * NOTE: The strings pointed to by these offsets are sorted lexicographically, ascending. */
	u32 mo_trnoffs;  /* Offset to translations offset table (relative to the file base)
	                  * >> u32 (*trn_offsets)[mo_strcount][2] = FILE_BASE + mo_stroffs; */
};


struct mo_file {
	/* .mo filename makeup:
	 *
	 * ```
	 *   /usr/share/locale/de/LC_MESSAGES/xz.mo
	 *   [===============] [] [=========] [][=]
	 *   |                 |  |           | |
	 *   |                 |  |           | \--- File extension
	 *   |                 |  |           \----- current_domainname
	 *   |                 |  \----------------- Category (as given to `dcngettext(3)')
	 *   |                 \-------------------- Language (see below)
	 *   \-------------------------------------- Domain directory (usually `_PATH_TEXTDOMAIN')
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
	 *     NULL                                // In this case, no translating is performed,
	 *                                         // meaning that  gettext() simply  re-returns
	 *                                         // its argument.
	 * ```
	 */
	LLRBTREE_NODE(mo_file)           mf_node;     /* [lock(mofiletree_lock)] R/B Tree node */
	uintptr_half_t                   mf_category; /* [const] Category id (one of `LC_*') */
	uintptr_half_t                   mf_red;      /* [lock(mofiletree_lock)] Red/Black bit for the tree of mo files. */
	size_t                           mf_size;     /* [const] Total size of file (== mmap'd size) */
	union {
		byte_t                      *mf_base;     /* [1..mf_size][owned][const] File base address / data blob. (mmap'd) */
		struct mo_file_header const *mf_hdr;      /* [1..1][const] File header. */
	};
	COMPILER_FLEXIBLE_ARRAY(char,    mf_name);    /* [*][const] Absolute filename of this file. */
};

/* Define the R/B-tree API */
DECL_END
#define RBTREE_DECL                PRIVATE
#define RBTREE_IMPL                PRIVATE
#define RBTREE(name)               mofiletree_##name
#define RBTREE_T                   struct mo_file
#define RBTREE_Tkey                char const *
#define RBTREE_CC                  __FCALL
#define RBTREE_NOTHROW             NOTHROW
#define RBTREE_KEY_LO(a, b)        (strcmp(a, b) < 0)
#define RBTREE_KEY_EQ(a, b)        (strcmp(a, b) == 0)
#define RBTREE_ISRED(self)         ((self)->mf_red != 0)
#define RBTREE_SETRED(self)        (void)((self)->mf_red = 1)
#define RBTREE_SETBLACK(self)      (void)((self)->mf_red = 0)
#define RBTREE_FLIPCOLOR(self)     (void)((self)->mf_red ^= 1)
#define RBTREE_COPYCOLOR(dst, src) (void)((dst)->mf_red = (src)->mf_red)
#define RBTREE_GETNODE(self)       (self)->mf_node
#define RBTREE_GETKEY(node)        (node)->mf_name
#define RBTREE_WANT_TRYINSERT
#define RBTREE_OMIT_REMOVE
#define RBTREE_OMIT_REMOVENODE
#define RBTREE_OMIT_INSERT
#define RBTREE_LEFT_LEANING
#include <hybrid/sequence/rbtree-abi.h>
DECL_BEGIN

/* Lock for the LLRB tree used to implement the .mo file cache. */
PRIVATE struct atomic_rwlock mofiletree_lock = ATOMIC_RWLOCK_INIT;
/* [0..n][lock(mofiletree_lock)] Root for the .mo file cache tree. */
PRIVATE LLRBTREE_ROOT(mo_file) mofiletree_root = NULL;





/* [0..1][lock(WRITE_ONCE || UNSAFE_CALLER)][*]
 * Cache of language names used for individual categories. These strings
 * are lazily initialized as strdup()  copies of strings retrieved  from
 * environment variables. */
PRIVATE char *language_names[LC_COUNT] = { [0 ... LC_COUNT - 1] = NULL };
PRIVATE char const unknown_language_name[] = "";

/* Clear  cached language  names for  all categories.  This function is
 * called when one of the thread-unsafe libintl configuration functions
 * is called:
 *   - textdomain(3)
 *   - bindtextdomain(3)
 *   - bind_textdomain_codeset(3) */
PRIVATE void NOTHROW(__FCALL clear_language_cache)(void) {
	unsigned int i;
	for (i = 0; i < LC_COUNT; ++i) {
		char *lang = language_names[i];
		if (lang) {
			language_names[i] = NULL;
			if (lang != unknown_language_name)
				free(lang);
		}
	}
}

/* Return the language name used for the given `category' of
 * messages. Returns an empty string if no language is  set.
 * NOTE: The caller must ensure that `category' is valid.
 * NOTE: Leading or trailing slashes will have been removed */
PRIVATE WUNUSED ATTR_RETNONNULL char const *
NOTHROW(__FCALL get_language_name)(int category) {
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
		                             NULL, result);
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
PRIVATE size_t domain_directory_size = 0; /* # of domain directory bindings. */
/* [0..domain_directory_size][sort(dd_dom)][owned] List of domain directory bindings (sorted by `dd_dom'). */
PRIVATE struct domain_directory *domain_directory_list = NULL;

/* Default domain directory. NOTE: Code assumes that this does _NOT_ end with a trailing slash! */
PRIVATE char const default_domain_dir[] = _PATH_TEXTDOMAIN;

/* Return the directory against which `domainname' is bound. */
PRIVATE WUNUSED ATTR_PURE ATTR_RETNONNULL NONNULL((1)) char const *__FCALL
get_domain_directory(char const *__restrict domainname) {
	size_t lo = 0, hi = domain_directory_size;
	/* Binary search for the correct entry. */
	while (lo < hi) {
		size_t i;
		int cmp;
		i   = (lo + hi) / 2;
		cmp = strcmp(domain_directory_list[i].dd_dom, domainname);
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



/* Try to open a .mo file for the given specs. */
PRIVATE ATTR_NOINLINE WUNUSED NONNULL((1)) struct mo_file *__FCALL
open_mo_file(char const *__restrict domainname, int category) {
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
	atomic_rwlock_read(&mofiletree_lock);
	result = mofiletree_locate(mofiletree_root, filename);
	atomic_rwlock_endread(&mofiletree_lock);
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
		fd = open(filename, O_RDONLY);
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
			 * so. (Meaning that these offests will _remain_ valid) */
			if (OVERFLOW_UMUL(base->mo_strcount, 8, &size))
				goto err_r_map;
			if (OVERFLOW_UADD(maxoff, size, &maxoff))
				goto err_r_map;
			if (maxoff > (size_t)st.st_size)
				goto err_r_map;
		}

		result->mf_size = (size_t)st.st_size;
		result->mf_base = (byte_t *)base;
	}

	/* Fill in the other fields of the new file. */
	memcpy(result->mf_name, filename, filename_size);
	result->mf_category = (uintptr_half_t)(unsigned int)category;

	/* Now try to insert the new descriptor into the tree. */
	atomic_rwlock_write(&mofiletree_lock);
	if unlikely(!mofiletree_tryinsert(&mofiletree_root, result)) {
		/* Race condition: another thread was faster. */
		atomic_rwlock_endwrite(&mofiletree_lock);
		munmap(result->mf_base, result->mf_size);
		free(result);
		goto again_load_from_tree;
	}
	atomic_rwlock_endwrite(&mofiletree_lock);

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
PRIVATE struct atomic_rwlock last_lock       = ATOMIC_RWLOCK_INIT;
PRIVATE struct mo_file /**/ *last_file       = NULL;
PRIVATE int /*            */ last_category   = 0;
PRIVATE char const /*    */ *last_domainname = NULL;


/* Return the .mo file associated with the given arguments. */
PRIVATE WUNUSED NONNULL((1)) struct mo_file *__FCALL
get_mo_file(char const *__restrict domainname, int category) {
	struct mo_file *result;
	atomic_rwlock_read(&last_lock);
	if (last_category == category) {
		if (last_domainname == domainname) {
			result = last_file;
			atomic_rwlock_endread(&last_lock);
			return result;
		}
#ifndef __OPTIMIZE_SIZE__
		else if (strcmp(last_domainname, domainname) == 0) {
			/* Different memory location, but same string! */
			if (!atomic_rwlock_upgrade(&last_lock)) {
				if (last_category != category) {
					atomic_rwlock_endwrite(&last_lock);
					goto load_file_slowly;
				}
			}
			last_domainname = domainname;
			result          = last_file;
			atomic_rwlock_endwrite(&last_lock);
			return result;
		}
#endif /* !__OPTIMIZE_SIZE__ */
	}
	atomic_rwlock_endread(&last_lock);
#ifndef __OPTIMIZE_SIZE__
load_file_slowly:
#endif /* !__OPTIMIZE_SIZE__ */

	/* Open a new/cached .mo file */
	result = open_mo_file(domainname, category);

	/* On success, remember the last used file. */
	if (result) {
		atomic_rwlock_write(&last_lock);
		last_file       = result;
		last_category   = category;
		last_domainname = domainname;
		atomic_rwlock_endwrite(&last_lock);
	}
	return result;
}


/* [0..1][owned] Current domain name (as set by `textdomain()')
 * Defaults to the part after the last slash in `dlmodulename(dlopen(NULL, 0))' */
PRIVATE char *current_domainname = NULL;


/*[[[head:libc_dcngettext,hash:CRC-32=0x79ad7a07]]]*/
INTERN ATTR_SECTION(".text.crt.i18n") ATTR_PURE WUNUSED __ATTR_FORMAT_ARG(2) __ATTR_FORMAT_ARG(3) char *
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
	if unlikely(!file)
		goto fail;

	/* TODO: Actually retrieve strings. */

fail:
	/* Fallback... */
	CRT_UNIMPLEMENTEDF("libc_dcngettext(%q, %q, %q, %lu, %d)",
	                   domainname, msgid_singular, msgid_plural, n, category);
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
			cmp = strcmp(domain_directory_list[i].dd_dom, domainname);
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
				cmp = strcmp(domain_directory_list[i].dd_dom, domainname);
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

/*[[[start:exports,hash:CRC-32=0x2829af3a]]]*/
DEFINE_PUBLIC_ALIAS(dcngettext, libc_dcngettext);
DEFINE_PUBLIC_ALIAS(textdomain, libc_textdomain);
DEFINE_PUBLIC_ALIAS(bindtextdomain, libc_bindtextdomain);
DEFINE_PUBLIC_ALIAS(bind_textdomain_codeset, libc_bind_textdomain_codeset);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_LIBINTL_C */
