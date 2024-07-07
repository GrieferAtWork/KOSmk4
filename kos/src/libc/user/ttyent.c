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
#ifndef GUARD_LIBC_USER_TTYENT_C
#define GUARD_LIBC_USER_TTYENT_C 1

#include "../api.h"
/**/

#include <sys/syslog.h>

#include <ctype.h>
#include <paths.h>
#include <stdio.h>
#include <string.h>

#include <libgen.h>

#include "ttyent.h"

DECL_BEGIN

PRIVATE ATTR_SECTION(".bss.crt.database.tty") FILE *ttys_file = NULL;
PRIVATE ATTR_SECTION(".bss.crt.database.tty") struct ttyent tty_ent = { NULL, };

/*[[[head:libc_setttyent,hash:CRC-32=0xc9f31f2e]]]*/
/* >> setttyent(3)
 * @return: 1 : Success
 * @return: 0 : Error */
INTERN ATTR_SECTION(".text.crt.database.tty") int
NOTHROW_RPC_KOS(LIBCCALL libc_setttyent)(void)
/*[[[body:libc_setttyent]]]*/
{
	if (ttys_file) {
		rewind(ttys_file);
	} else {
		ttys_file = fopen(_PATH_TTYS, "r");
		if (!ttys_file)
			return 0;
	}
	return 1;
}
/*[[[end:libc_setttyent]]]*/

/*[[[head:libc_endttyent,hash:CRC-32=0x1470f177]]]*/
/* >> endttyent(3)
 * @return: 1 : Success
 * @return: 0 : Error */
INTERN ATTR_SECTION(".text.crt.database.tty") int
NOTHROW_NCX(LIBCCALL libc_endttyent)(void)
/*[[[body:libc_endttyent]]]*/
{
	if (ttys_file) {
		fclose(ttys_file);
		ttys_file = NULL;
	}
	return 1;
}
/*[[[end:libc_endttyent]]]*/

PRIVATE ATTR_SECTION(".text.crt.database.tty") ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL tty_strip_and_unescape)(char *str) {
	str = strlstrip(str);
	if (*str == '"') {
		char *eos = ++str;
		while (*eos) {
			if (*eos == '"')
				break;
			if (*eos == '\\') {
				++eos;
				if (*eos)
					++eos;
			} else {
				++eos;
			}
		}
		*eos = '\0';
		str = strccpy(str, str);
	} else {
		/* Strip trailing whitespace */
		str = strrstrip(str);
	}
	return str;
}

PRIVATE ATTR_SECTION(".text.crt.database.tty") ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL tty_nextfield)(char *str) {
	while (*str) {
		if (isspace(*str)) { /* XXX: Unicode support here? */
			str = strlstrip(str + 1);
			str[-1] = '\0';
			break;
		}
		if (*str == '"') {
			++str;
			while (*str) {
				if (*str == '"') {
					++str;
					break;
				}
				if (*str == '\\') {
					++str;
					if (*str)
						++str;
				} else {
					++str;
				}
			}
			if (*str)
				str[-1] = '\0';
			/* Skip whitespace after end of quoted area */
			str = strlstrip(str);
			break;
		}
		++str;
	}
	return str;
}

/*[[[head:libc_getttyent,hash:CRC-32=0xdca6cc64]]]*/
/* >> getttyent(3) */
INTERN ATTR_SECTION(".text.crt.database.tty") struct ttyent *
NOTHROW_RPC_KOS(LIBCCALL libc_getttyent)(void)
/*[[[body:libc_getttyent]]]*/
{
	char *line;
	if (!ttys_file)
		libc_setttyent();
	while ((line = fgetln(ttys_file, NULL)) != NULL) {

		/* Strip leading space */
		line = strlstrip(line);

		/* Skip empty- or comment-only lines */
		if (*line == '\0' || *line == '#')
			continue;

		/* Strip trailing space */
		line = strrstrip(line);

		/* Skip empty lines. */
		if (*line == '\0')
			continue;

		/* Lines look something like this:
		 * >> console "/usr/libexec/getty std.1200" vt100 on secure */
		bzero(&tty_ent, sizeof(tty_ent));
		tty_ent.ty_name  = line;
		line             = tty_nextfield(line);
		tty_ent.ty_getty = line;
		line             = tty_nextfield(line);
		tty_ent.ty_type  = line;
		line             = tty_nextfield(line);

		/* Parse flags */
		while (*line && *line != '#') {
			char *item = line, *value;
			line = tty_nextfield(line);
			item = tty_strip_and_unescape(item);
			if (strcmp(item, "on") == 0) {
				tty_ent.ty_status |= TTY_ON;
				continue;
			}
			if (strcmp(item, "secure") == 0) {
				tty_ent.ty_status |= TTY_SECURE;
				continue;
			}
			value = strchr(item, '=');
			if (value) {
				*value++ = '\0';
				value = tty_strip_and_unescape(value);
				if (strcmp(item, "group") == 0) {
					tty_ent.ty_group = value;
					continue;
				}
				if (strcmp(item, "window") == 0) {
					tty_ent.ty_window = value;
					continue;
				}
				syslog(LOG_WARN, "Unrecognized flag in /dev/ttys line: '%#q=%q'\n", item, value);
			} else {
				syslog(LOG_WARN, "Unrecognized flag in /dev/ttys line: '%#q'\n", item);
			}
		}
		if (*line == '#') {
			/* Trailing comment */
			line = strlstrip(line + 1);
			tty_ent.ty_comment = line;
		}

		/* Unescape string fields. */
		tty_ent.ty_name  = tty_strip_and_unescape(tty_ent.ty_name);
		tty_ent.ty_getty = tty_strip_and_unescape(tty_ent.ty_getty);
		tty_ent.ty_type  = tty_strip_and_unescape(tty_ent.ty_type);
		return &tty_ent;
	}
	return NULL;
}
/*[[[end:libc_getttyent]]]*/



/*[[[start:exports,hash:CRC-32=0x210a9003]]]*/
DEFINE_PUBLIC_ALIAS_P(getttyent,libc_getttyent,,struct ttyent *,NOTHROW_RPC_KOS,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(setttyent,libc_setttyent,,int,NOTHROW_RPC_KOS,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(endttyent,libc_endttyent,,int,NOTHROW_NCX,LIBCCALL,(void),());
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_TTYENT_C */
