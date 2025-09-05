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
#ifndef GUARD_LIBC_USER_FMTMSG_C
#define GUARD_LIBC_USER_FMTMSG_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "../api.h"
/**/

#include <kos/sched/shared-rwlock.h>

#include <format-printer.h>
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

#include "../libc/globals.h"
#include "fmtmsg.h"


DECL_BEGIN

/* fmtmsg print bits (initialized from `$MSGVERB') */
#define FMTMSG_PRINT_LABEL    0x01 /* "label" */
#define FMTMSG_PRINT_SEVERITY 0x02 /* "severity" */
#define FMTMSG_PRINT_TEXT     0x04 /* "text" */
#define FMTMSG_PRINT_ACTION   0x08 /* "action" */
#define FMTMSG_PRINT_TAG      0x10 /* "tag" */

PRIVATE ATTR_SECTION(".rodata.crt.fmtmsg") char const fmtmsg_verbs[][9] = {
	/* [ilog2(FMTMSG_PRINT_LABEL)]    = */ "label",
	/* [ilog2(FMTMSG_PRINT_SEVERITY)] = */ "severity",
	/* [ilog2(FMTMSG_PRINT_TEXT)]     = */ "text",
	/* [ilog2(FMTMSG_PRINT_ACTION)]   = */ "action",
	/* [ilog2(FMTMSG_PRINT_TAG)]      = */ "tag",
};


/* Mask of stuff to print (set of `FMTMSG_PRINT_*') */
PRIVATE ATTR_SECTION(".data.crt.fmtmsg") uint8_t fmtmsg_print = 0xff;

/* Parse the contents of `$MSGVERB' */
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) ATTR_SECTION(".text.crt.fmtmsg") uint8_t
NOTHROW(LIBCCALL fmtmsg_parse_msgverb)(char const *msgverb) {
	uint8_t result = 0;
	for (;;) {
		unsigned int i;
		char const *col;
		size_t len;
		col = strchrnul(msgverb, ':');
		len = (size_t)(col - msgverb);
		if unlikely(len >= lengthof(fmtmsg_verbs[0]))
			goto err;
		for (i = 0;; ++i) {
			if (i >= lengthof(fmtmsg_verbs)) {
				if unlikely(len == 0) {
					/* Special case: to simplify usage, we accept (and ignore) empty verbs */
					goto nextverb;
				}
				goto err;
			}
			if (bcmp(fmtmsg_verbs[i], msgverb, len * sizeof(char)) == 0 &&
			    fmtmsg_verbs[i][len] == '\0')
				break;
		}
		result |= (uint8_t)1 << i;
		msgverb = col;
		if (*msgverb == '\0')
			break;
nextverb:
		++msgverb; /* Skip over ':' */
	}
	return result;
err:
	/* Posix says:
	 * """
	 * If MSGVERB [...] is  not of the  correct format, or  if it contains  keywords
	 * other than the valid ones listed above, fmtmsg() shall select all components.
	 * """
	 */
	return 0xff;
}




/* Lock for accessing the dynamic parts of `<fmtmsg.h>' */
PRIVATE ATTR_SECTION(".bss.crt.fmtmsg")
DEFINE_SHARED_RWLOCK(fmtmsg_lock);

/* Helpers for accessing `fmtmsg_lock' */
#define /*        */ _fmtmsg_lock_reap()        (void)0
#define /*        */ fmtmsg_lock_reap()         (void)0
#define /*        */ fmtmsg_lock_mustreap()     0
#define /*BLOCKING*/ fmtmsg_lock_write()        shared_rwlock_write(&fmtmsg_lock)
#define /*        */ fmtmsg_lock_trywrite()     shared_rwlock_trywrite(&fmtmsg_lock)
#define /*        */ fmtmsg_lock_endwrite()     (shared_rwlock_endwrite(&fmtmsg_lock), fmtmsg_lock_reap())
#define /*        */ _fmtmsg_lock_endwrite()    shared_rwlock_endwrite(&fmtmsg_lock)
#define /*BLOCKING*/ fmtmsg_lock_read()         shared_rwlock_read(&fmtmsg_lock)
#define /*        */ fmtmsg_lock_tryread()      shared_rwlock_tryread(&fmtmsg_lock)
#define /*        */ _fmtmsg_lock_endread()     shared_rwlock_endread(&fmtmsg_lock)
#define /*        */ fmtmsg_lock_endread()      (void)(shared_rwlock_endread(&fmtmsg_lock) && (fmtmsg_lock_reap(), 0))
#define /*        */ _fmtmsg_lock_end()         shared_rwlock_end(&fmtmsg_lock)
#define /*        */ fmtmsg_lock_end()          (void)(shared_rwlock_end(&fmtmsg_lock) && (fmtmsg_lock_reap(), 0))
#define /*BLOCKING*/ fmtmsg_lock_upgrade()      shared_rwlock_upgrade(&fmtmsg_lock)
#define /*        */ fmtmsg_lock_tryupgrade()   shared_rwlock_tryupgrade(&fmtmsg_lock)
#define /*        */ fmtmsg_lock_downgrade()    shared_rwlock_downgrade(&fmtmsg_lock)
#define /*        */ fmtmsg_lock_reading()      shared_rwlock_reading(&fmtmsg_lock)
#define /*        */ fmtmsg_lock_writing()      shared_rwlock_writing(&fmtmsg_lock)
#define /*        */ fmtmsg_lock_canread()      shared_rwlock_canread(&fmtmsg_lock)
#define /*        */ fmtmsg_lock_canwrite()     shared_rwlock_canwrite(&fmtmsg_lock)
#define /*BLOCKING*/ fmtmsg_lock_waitread()     shared_rwlock_waitread(&fmtmsg_lock)
#define /*BLOCKING*/ fmtmsg_lock_waitwrite()    shared_rwlock_waitwrite(&fmtmsg_lock)

struct extra_severity {
	unsigned int                  es_severity; /* [>= 5] Extra severity code */
	COMPILER_FLEXIBLE_ARRAY(char, es_name);    /* NUL-terminated severity name */
};

/* [0..n][owned][lock(fmtmsg_lock)] Sorted (by `es_severity') list of extra severity codes. */
PRIVATE ATTR_SECTION(".bss.crt.fmtmsg") struct extra_severity **fmtmsg_extra_severity_start = NULL;
PRIVATE ATTR_SECTION(".bss.crt.fmtmsg") struct extra_severity **fmtmsg_extra_severity_end   = NULL;

/* Default severity codes. */
PRIVATE ATTR_SECTION(".rodata.crt.fmtmsg")
char const fmtmsg_default_severity[][8] = {
	[MM_NOSEV]   = "",
	[MM_HALT]    = "HALT",
	[MM_ERROR]   = "ERROR",
	[MM_WARNING] = "WARNING",
	[MM_INFO]    = "INFO",
};

/* Find the label associated with `severity' */
PRIVATE ATTR_PURE WUNUSED ATTR_SECTION(".text.crt.fmtmsg") char const *
NOTHROW_NCX(LIBCCALL fmtmsg_severify_getname)(unsigned int severity) {
	struct extra_severity **lo, **hi;
	if (severity < lengthof(fmtmsg_default_severity))
		return fmtmsg_default_severity[severity];

	/* Must be a dynamically defined severity level! */
	lo = fmtmsg_extra_severity_start;
	hi = fmtmsg_extra_severity_end;
	while (lo < hi) {
		struct extra_severity **mid;
		unsigned int mid_severity;
		mid          = lo + ((hi - lo) >> 1);
		mid_severity = (*mid)->es_severity;
		if (severity < mid_severity) {
			hi = mid;
		} else if (severity > mid_severity) {
			lo = mid + 1;
		} else {
			/* Found it! */
			return (*mid)->es_name;
		}
	}

	/* Welp: it ain't here... */
	return NULL;
}

/* Define (or override) an additional severity level
 * @return: MM_OK:    Success
 * @return: MM_NOTOK: Out of memory (errno was set to `ENOMEM') */
PRIVATE ATTR_SECTION(".text.crt.fmtmsg") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL fmtmsg_define_severity)(unsigned int severity,
                                             char const *name, size_t namelen) {
	struct extra_severity *newent;
	struct extra_severity **lo, **hi;
	/* Allocate new entry. */
	newent = (struct extra_severity *)malloc(offsetof(struct extra_severity, es_name) +
	                                         (namelen + 1) * sizeof(char));
	if unlikely(!newent)
		return MM_NOTOK;
	newent->es_severity = severity;
	*(char *)mempcpy(newent->es_name, name, namelen, sizeof(char)) = '\0';

	lo = fmtmsg_extra_severity_start;
	hi = fmtmsg_extra_severity_end;
	while (lo < hi) {
		struct extra_severity **mid;
		unsigned int mid_severity;
		mid          = lo + ((hi - lo) >> 1);
		mid_severity = (*mid)->es_severity;
		if (severity < mid_severity) {
			hi = mid;
		} else if (severity > mid_severity) {
			lo = mid + 1;
		} else {
			/* Override entry. */
			struct extra_severity *oldent;
			oldent = *mid;
			*mid = newent;
			free(oldent);
			return MM_OK;
		}
	}

	/* Must insert a new entry at `*lo' */
	{
		size_t pos, oldsize, newsize;
		pos     = (size_t)(lo - fmtmsg_extra_severity_start);
		oldsize = (size_t)(fmtmsg_extra_severity_end - fmtmsg_extra_severity_start);
		newsize = oldsize + 1;

		/* Realloc array of dynamic severity levels. */
		lo = (struct extra_severity **)realloc(fmtmsg_extra_severity_start,
		                                       newsize, sizeof(struct extra_severity *));
		if unlikely(!lo) {
			free(newent);
			return MM_NOTOK;
		}
		fmtmsg_extra_severity_start = lo;
		fmtmsg_extra_severity_end   = lo + newsize;
		memmoveup(&lo[pos + 1], &lo[pos], oldsize - pos,
		          sizeof(struct extra_severity *));
		lo[pos] = newent;
	}
	return MM_OK;
}

/* Remove an additional severity level
 * @return: MM_OK:    Success
 * @return: MM_NOTOK: No such `severity' */
PRIVATE ATTR_SECTION(".text.crt.fmtmsg") int
NOTHROW_NCX(LIBCCALL fmtmsg_remove_severity)(unsigned int severity) {
	struct extra_severity **lo, **hi;
	lo = fmtmsg_extra_severity_start;
	hi = fmtmsg_extra_severity_end;
	while (lo < hi) {
		struct extra_severity **mid;
		unsigned int mid_severity;
		mid          = lo + ((hi - lo) >> 1);
		mid_severity = (*mid)->es_severity;
		if (severity < mid_severity) {
			hi = mid;
		} else if (severity > mid_severity) {
			lo = mid + 1;
		} else {
			/* Remove this entry. */
			struct extra_severity *oldent;
			size_t newsize;
			oldent = *mid;
			--fmtmsg_extra_severity_end;
			memmovedown(mid, mid + 1,
			            (size_t)(fmtmsg_extra_severity_end - mid),
			            sizeof(struct extra_severity *));
			free(oldent);

			/* Try to free unused memory from the severity-vector. */
			newsize = (size_t)(fmtmsg_extra_severity_end - fmtmsg_extra_severity_start);
			lo = (struct extra_severity **)realloc(fmtmsg_extra_severity_start,
			                                       newsize, sizeof(struct extra_severity *));
			if likely(lo) {
				fmtmsg_extra_severity_start = lo;
				fmtmsg_extra_severity_end   = lo + newsize;
			}
			return MM_OK;
		}
	}

	/* Not found */
	return MM_NOTOK;
}


PRIVATE ATTR_SECTION(".text.crt.fmtmsg") void
NOTHROW_NCX(LIBCCALL fmtmsg_parse_sev_level)(char const *sev_level) {
	/* The sev_level environ variable looks like this:
	 * >> SEV_LEVEL="<keyword>,<severity>,<label>:<keyword2>,<severity2>,<label2>:[...]"
	 *
	 * Where:
	 * - <keyword>  is completely unused (and I have no idea what it's about)
	 * - <severity> is `strtol(<severity>, NULL, 0)'d to an integer (iow: <severity> can be "0xAB" or "123")
	 * - <label>    is the label that must be passed to `fmtmsg_define_severity()'
	 *
	 * Badly formatted elements simply get skipped.
	 */
	for (;;) {
		uint32_t severity;
		errno_t atoi_error;
		char const *col;
		col = strchrnul(sev_level, ':');

		/* Skip over the "<keyword>," part. */
		sev_level = (char const *)memchr(sev_level, ',', (size_t)(col - sev_level));
		if unlikely(!sev_level)
			goto next_item;
		++sev_level; /* Skip "," after "<keyword>" */

		/* Parse the "<severity>" part */
		severity = strtou32_r(sev_level, (char **)&sev_level, 0, &atoi_error);
		if unlikely(atoi_error != EOK)
			goto next_item; /* Error while parsing integer (e.g. `ERANGE' (overflow), or `ECANCELED' (nothing parsed)) */
		if unlikely(severity < lengthof(fmtmsg_default_severity))
			goto next_item; /* Bad severity code */
		if unlikely(sev_level > col) {
			/* Severity code ends ?after? the trailing ':' (shouldn't happen since
			 * `strtou32_r()' shouldn't parse ':'-characters, but just to be safe) */
			goto next_item;
		}

		/* Skip over the ',' after the "<severity>" part */
		if unlikely(*sev_level != ',')
			goto next_item;
		++sev_level;

		/* The rest of the current item is the severity label (errors here are also ignored...) */
		(void)fmtmsg_define_severity((unsigned int)severity, sev_level,
		                             (size_t)(col - sev_level));

		/* Keep on scanning for more items... */
next_item:
		if (*col == '\0')
			break;
		sev_level = col + 1;
	}
}


PRIVATE ATTR_SECTION(".bss.crt.fmtmsg")
pthread_once_t fmtmsg_didinit = PTHREAD_ONCE_INIT;
PRIVATE ATTR_SECTION(".text.crt.fmtmsg") void
NOTHROW(LIBCCALL fmtmsg_doinit)(void) {
	char *env;
	/* Load what should be printed from `$MSGVERB' */
	if ((env = getenv("MSGVERB")) != NULL && *env != '\0')
		fmtmsg_print = fmtmsg_parse_msgverb(env);

	/* Load extra severity levels from `$SEV_LEVEL' */
	if ((env = getenv("SEV_LEVEL")) != NULL)
		fmtmsg_parse_sev_level(env);
}

PRIVATE ATTR_SECTION(".text.crt.fmtmsg") void
NOTHROW(LIBCCALL fmtmsg_init)(void) {
	pthread_once(&fmtmsg_didinit,
	             &fmtmsg_doinit);
}


PRIVATE ATTR_SECTION(".text.crt.fmtmsg") ssize_t FORMATPRINTER_CC
fmtmsg_printer(void *arg, /*utf-8*/ char const *__restrict data, size_t datalen) {
	uintptr_t classification;
	classification = (uintptr_t)arg;
	if (classification & MM_PRINT) {
		if (file_printer(stderr, data, datalen) < 0)
			return -1; /* Caller will turn this into `MM_NOMSG' */
	}
	if (classification & MM_CONSOLE)
		syslog_printer(SYSLOG_PRINTER_CLOSURE(LOG_ERR), data, datalen);
	return (ssize_t)datalen;
}


/*[[[head:libc_fmtmsg,hash:CRC-32=0x9b4d3d84]]]*/
/* >> fmtmsg(3)
 * Print a message to `stderr(3)' and/or `syslog(3)'. The exact  format
 * in which the mssage is printed, alongside additional severity levels
 * depends on `$MSGVERB', `$SEV_LEVEL' and `addseverity(3)'.
 * @param: classification: Set of:
 *          - `MM_PRINT', `MM_CONSOLE', or `MM_PRINT | MM_CONSOLE'
 *          - `MM_HARD', `MM_FIRM' or `MM_SOFT'
 *          - `MM_APPL', `MM_UTIL' or `MM_OPSYS'
 *          - `MM_RECOVER' or `MM_NRECOV'
 * @param: label:    Message source, as "<domain>:<util>", where  "<domain>"
 *                   must not be longer than 10 chars, and "<util>" must not
 *                   be longer than 14 chars.
 * @param: severity: Message severity code (extra severity codes can be
 *                   defined by `addseverity(3)'  or via  `$SEV_LEVEL')
 * @param: text:     Error condition (e.g. "bad arguments given")
 * @param: action:   Steps to fix the error (if printed, is prefixed by "TO FIX: ")
 * @param: tag:      Reference to online docs for more info on error (should include `label')
 * @return: MM_NOTOK: Arguments are bad
 * @return: MM_OK:    Success
 * @return: MM_NOMSG: Failed to print message to `stderr(3)' */
INTERN ATTR_SECTION(".text.crt.fmtmsg") int
NOTHROW_NCX(LIBCCALL libc_fmtmsg)(long classification,
                                  char const *label,
                                  __STDC_INT_AS_UINT_T severity,
                                  char const *text,
                                  char const *action,
                                  char const *tag)
/*[[[body:libc_fmtmsg]]]*/
{
	void *printer_arg;
	char const *severity_name;
	int result = MM_NOTOK;

	/* Verify that `label' is OK (completely arbitrary restriction, but posix wants this...) */
	if (label != NULL) {
		char const *col = strchr(label, ':');
		if unlikely(!col)
			goto done_nolock;
		if ((size_t)(col - label) > 10)
			goto done_nolock;
		++col;
		if (strlen(col) > 14)
			goto done_nolock;
	}
	fmtmsg_init();
	fmtmsg_lock_read();
	severity_name = fmtmsg_severify_getname(severity);
	if unlikely(!severity_name)
		goto done;
	result      = MM_NOMSG;
	printer_arg = (void *)(uintptr_t)(unsigned long)classification;

	/* Actually print the message */
	{
		static ATTR_SECTION(".rodata.crt.fmtmsg") char const col_and_space[] = { ':', ' ' };
		static ATTR_SECTION(".rodata.crt.fmtmsg") char const lf[] = { '\n' };
		static ATTR_SECTION(".rodata.crt.fmtmsg") char const TO_FIX[] = { 'T', 'O', ' ', 'F', 'I', 'X', ':', ' ' };
		static ATTR_SECTION(".rodata.crt.fmtmsg") char const space_space[] = { ' ', ' ' };
		bool print_label    = label != MM_NULLLBL && (fmtmsg_print & FMTMSG_PRINT_LABEL) != 0;
		bool print_severity = *severity_name != '\0' && (fmtmsg_print & FMTMSG_PRINT_SEVERITY) != 0;
		bool print_text     = text != MM_NULLTXT && (fmtmsg_print & FMTMSG_PRINT_TEXT) != 0;
		bool print_action   = action != MM_NULLACT && (fmtmsg_print & FMTMSG_PRINT_ACTION) != 0;
		bool print_tag      = tag != MM_NULLTAG && (fmtmsg_print & FMTMSG_PRINT_TAG) != 0;
		if (print_label) {
			if unlikely(fmtmsg_printer(printer_arg, label, strlen(label)) < 0)
				goto done;
			if (print_severity || print_text || print_action || print_tag) {
				if unlikely(fmtmsg_printer(printer_arg, col_and_space, lengthof(col_and_space)) < 0)
					goto done;
			}
		}
		if (print_severity) {
			if unlikely(fmtmsg_printer(printer_arg, severity_name, strlen(severity_name)) < 0)
				goto done;
			if (print_text || print_action || print_tag) {
				if unlikely(fmtmsg_printer(printer_arg, col_and_space, lengthof(col_and_space)) < 0)
					goto done;
			}
		}
		if (print_text) {
			if unlikely(fmtmsg_printer(printer_arg, text, strlen(text)) < 0)
				goto done;
			if (print_action || print_tag) {
				if unlikely(fmtmsg_printer(printer_arg, lf, lengthof(lf)) < 0)
					goto done;
			}
		}
		if (print_action) {
			if unlikely(fmtmsg_printer(printer_arg, TO_FIX, lengthof(TO_FIX)) < 0)
				goto done;
			if unlikely(fmtmsg_printer(printer_arg, action, strlen(action)) < 0)
				goto done;
			if (print_tag) {
				if unlikely(fmtmsg_printer(printer_arg, space_space, lengthof(space_space)) < 0)
					goto done;
			}
		}
		if (print_tag) {
			if unlikely(fmtmsg_printer(printer_arg, tag, strlen(tag)) < 0)
				goto done;
		}
		if unlikely(fmtmsg_printer(printer_arg, lf, lengthof(lf)) < 0)
			goto done;
	}

	/* Indicate success. */
	result = MM_OK;
done:
	fmtmsg_lock_endread();
done_nolock:
	return result;
}
/*[[[end:libc_fmtmsg]]]*/

/*[[[head:libc_addseverity,hash:CRC-32=0x4c786585]]]*/
/* >> addseverity(3)
 * Add  (`s != NULL') or remove  (`s == NULL') custom severity levels.
 * By default (and these cannot be overwritten or removed), levels 0-4
 * are defined as:
 *  - 0: MM_NOSEV:   [""]        No severity level
 *  - 1: MM_HALT:    ["HALT"]    Application will halt as a result
 *  - 2: MM_ERROR:   ["ERROR"]   Non-fatal error encountered
 *  - 3: MM_WARNING: ["WARNING"] Unusual non-error condition (== warning)
 *  - 4: MM_INFO:    ["INFO"]    General information
 * Additionally,  `$SEV_LEVEL' is used  to define additional severity
 * levels  dynamically (just like  this function can  be used to) the
 * first time this function (or `fmtmsg(3)') is called. The format of
 * the `$SEV_LEVEL' variable follows posix specifications, and unlike
 * with the 5 default severity levels, these can be removed again, or
 * further overwritten by use of this function
 * @param: severity: The ID to assign for the new severity level (must be >= 5)
 * @param: s: - When non-NULL, define (or override) the label for `severity'.
 *            - When NULL, remove the definition for `severity'
 * @return: MM_OK:    Success
 * @return: MM_NOTOK: The given `severity' is `< 5' (errno was not modified)
 * @return: MM_NOTOK: Out of memory (errno was set to `ENOMEM')
 * @return: MM_NOTOK: No such `severity' and `s == NULL' (errno was not modified) */
INTERN ATTR_SECTION(".text.crt.fmtmsg") int
NOTHROW_NCX(LIBCCALL libc_addseverity)(__STDC_INT_AS_UINT_T severity,
                                       char const *s)
/*[[[body:libc_addseverity]]]*/
{
	int result;
	if ((int)severity < (int)lengthof(fmtmsg_default_severity))
		return MM_NOTOK;
	fmtmsg_init();
	fmtmsg_lock_write();
	/* Add, replace, or remove severity levels. */
	if (s == NULL) {
		result = fmtmsg_remove_severity((unsigned int)severity);
	} else {
		result = fmtmsg_define_severity((unsigned int)severity, s, strlen(s));
	}
	fmtmsg_lock_endwrite();
	return result;
}
/*[[[end:libc_addseverity]]]*/

/*[[[start:exports,hash:CRC-32=0x83da8b39]]]*/
DEFINE_PUBLIC_ALIAS_P(fmtmsg,libc_fmtmsg,,int,NOTHROW_NCX,LIBCCALL,(long classification, char const *label, __STDC_INT_AS_UINT_T severity, char const *text, char const *action, char const *tag),(classification,label,severity,text,action,tag));
DEFINE_PUBLIC_ALIAS_P(addseverity,libc_addseverity,,int,NOTHROW_NCX,LIBCCALL,(__STDC_INT_AS_UINT_T severity, char const *s),(severity,s));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_FMTMSG_C */
