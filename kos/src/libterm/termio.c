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
#ifndef GUARD_LIBTERM_TERMIO_C
#define GUARD_LIBTERM_TERMIO_C 1
#define _USE_64BIT_TIME_T 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/atomic.h>
#include <hybrid/minmax.h>

#include <kos/except.h>

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h> /* _POSIX_MAX_INPUT, _POSIX_MAX_CANON */
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <unicode.h>

#include <libbuffer/linebuffer.h>
#include <libterm/termio.h>

#include "termio.h"

#ifdef __KERNEL__
#include <sched/sig.h>
#else /* __KERNEL__ */
#include <kos/futexexpr.h>
#endif /* !__KERNEL__ */

DECL_BEGIN

LOCAL KERNEL_SELECT(__size_t, __ssize_t) CC
linebuffer_writef(struct linebuffer *__restrict self,
                  __USER __CHECKED void const *src,
                  size_t num_bytes, iomode_t mode) {
	KERNEL_SELECT(__size_t, __ssize_t) result;
	result = mode & IO_NONBLOCK
	         ? linebuffer_write_nonblock(self, src, num_bytes)
	         : linebuffer_write(self, src, num_bytes);
#ifdef __KERNEL__
	assert((size_t)result <= num_bytes);
#else /* __KERNEL__ */
	assert(result < 0 || (size_t)result <= num_bytes);
#endif /* !__KERNEL__ */
	return result;
}



/* Initialize/Finalize the given terminal controller. */
INTERN NOBLOCK NONNULL((1, 2)) void
NOTHROW_NCX(CC libterminal_init)(struct terminal *__restrict self,
                                 pterminal_oprinter_t oprinter,
                                 pterminal_raise_t raisefunc,
                                 pterminal_check_sigttou_t chk_sigttou) {
	assert(self);
	assert(oprinter);
	self->t_oprint      = oprinter;
	self->t_raise       = raisefunc;
	self->t_chk_sigttou = chk_sigttou;
	ringbuffer_init_ex(&self->t_ibuf, _POSIX_MAX_INPUT * 4);
	linebuffer_init_ex(&self->t_canon, _POSIX_MAX_CANON * 4);
	linebuffer_init_ex(&self->t_opend, MAX_C(_POSIX_MAX_INPUT / 2, 64));
	linebuffer_init_ex(&self->t_ipend, MAX_C(_POSIX_MAX_INPUT / 2, 64));
	sched_signal_init(&self->t_ioschange);
	/* Initialize the IOS to default values. */
	cfmakesane(&self->t_ios);
}


PRIVATE ssize_t CC libterminal_flush_ibuf(struct terminal *__restrict self, iomode_t mode, tcflag_t iflag);
PRIVATE ssize_t CC libterminal_flush_obuf(struct terminal *__restrict self, iomode_t mode, tcflag_t lflag);



/* Special text sequences. */
PRIVATE byte_t const slash[]     = { '/' };
PRIVATE byte_t const backslash[] = { '\\' };
PRIVATE byte_t const crlf[]      = { '\r', '\n' };
PRIVATE byte_t const lf[]        = { '\n' };
PRIVATE byte_t const bell[]      = { '\7' };
PRIVATE byte_t const erase1[]    = { '\b', ' ', '\b' };

FORCELOCAL ATTR_ARTIFICIAL ssize_t CC
libterminal_do_owrite_direct(struct terminal *__restrict self,
                             __USER __CHECKED void const *src,
                             size_t num_bytes, iomode_t mode) {
	return (*self->t_oprint)(self, src, num_bytes, mode);
}

FORCELOCAL ATTR_ARTIFICIAL KERNEL_SELECT(size_t, ssize_t) CC
libterminal_do_iwrite_direct(struct terminal *__restrict self,
                             __USER __CHECKED void const *src,
                             size_t num_bytes, iomode_t mode) {
	KERNEL_SELECT(size_t, ssize_t) result;
	result = mode & IO_NONBLOCK
	         ? ringbuffer_write_nonblock(&self->t_ibuf, src, num_bytes)
	         : ringbuffer_write(&self->t_ibuf, src, num_bytes);
	return result;
}

FORCELOCAL void CC
libterminal_do_iwrite_set_eofing(struct terminal *__restrict self) {
	/* Set the EOFing bit */
	ATOMIC_OR(self->t_ios.c_lflag, __IEOFING);
	/* Broadcast the signal send when the input buffer becomes non-empty,
	 * thus  causing  any  thread  waiting  on  input  data  to  wake up. */
	sched_signal_broadcast(&self->t_ibuf.rb_nempty);
}


PRIVATE ssize_t CC
libterminal_do_owrite_nostop_nobuf(struct terminal *__restrict self,
                                   __USER __CHECKED void const *src,
                                   size_t num_bytes, iomode_t mode,
                                   tcflag_t lflag) {
	tcflag_t oflag;
	ssize_t result, temp;
	oflag = ATOMIC_READ(self->t_ios.c_oflag);
	if ((oflag & (OPOST | OLCUC | ONLCR | OCRNL | ONLRET)) == 0) {
		/* Check for simple case: No pre-processing required. */
		result = libterminal_do_owrite_direct(self, src, num_bytes, mode);
	} else {
		byte_t const *iter, *end, *flush_start;
		result      = 0;
		iter        = (byte_t const *)src;
		end         = iter + num_bytes;
		flush_start = iter;
		for (; iter < end; ++iter) {
			byte_t ch = *iter;
			assert((size_t)result == (size_t)(flush_start - (byte_t const *)src));
			switch (ch) {

			case 'a' ... 'z':
				if ((oflag & OLCUC) || ((oflag & OPOST) && (lflag & (ICANON | XCASE)) == (ICANON | XCASE))) {
					/* Lowercase characters are mapped to uppercase on output. */
					if (flush_start < iter) {
						size_t count;
						count = (size_t)(iter - flush_start);
						temp  = libterminal_do_owrite_direct(self, flush_start, count, mode);
						if unlikely(temp < 0)
							goto err;
						result += temp;
						if unlikely((size_t)temp < count)
							goto done;
					}
					ch += ('A' - 'a');
					temp = libterminal_do_owrite_direct(self, &ch, 1, mode);
					if unlikely(temp <= 0)
						goto err_or_done;
					++result; /* Account for the control character */
					flush_start = iter + 1;
				}
				break;

			case 'A' ... 'Z':
				if ((oflag & OPOST) && (lflag & (ICANON | XCASE)) == (ICANON | XCASE)) {
					/* Uppercase characters are preceded by `\' on output. */
					if (flush_start < iter) {
						size_t count;
						count = (size_t)(iter - flush_start);
						temp  = libterminal_do_owrite_direct(self, flush_start, count, mode);
						if unlikely(temp < 0)
							goto err;
						result += temp;
						if unlikely((size_t)temp < count)
							goto done;
						flush_start = iter;
					}
					temp = libterminal_do_owrite_direct(self, backslash, COMPILER_LENOF(backslash), mode);
					if unlikely(temp < (ssize_t)COMPILER_LENOF(backslash))
						goto err_or_done;
				}
				break;

			case '\n':
				if (oflag & ONLCR) {
					if (flush_start < iter) {
						size_t count;
						count = (size_t)(iter - flush_start);
						temp  = libterminal_do_owrite_direct(self, flush_start, count, mode);
						if unlikely(temp < 0)
							goto err;
						result += temp;
						if unlikely((size_t)temp < count)
							goto done;
					}
					/* Output NL characters as CRNL */
					temp = libterminal_do_owrite_direct(self, crlf, COMPILER_LENOF(crlf), mode);
					if unlikely(temp < (ssize_t)COMPILER_LENOF(crlf))
						goto err_or_done;
					++result; /* Account for the control character */
					flush_start = iter + 1;
				}
				break;

			case '\r':
				if (oflag & (ONLRET | OCRNL)) {
					if (flush_start < iter) {
						size_t count;
						count = (size_t)(iter - flush_start);
						temp  = libterminal_do_owrite_direct(self, flush_start, count, mode);
						if unlikely(temp < 0)
							goto err;
						result += temp;
						if unlikely((size_t)temp < count)
							goto done;
					}
					if (oflag & ONLRET) {
						/* Don't output CR characters */
					} else if (oflag & OCRNL) {
						if (oflag & ONLCR) {
							/* Output CR characters as CRNL */
							temp = libterminal_do_owrite_direct(self, crlf, COMPILER_LENOF(crlf), mode);
							if unlikely(temp < (ssize_t)COMPILER_LENOF(crlf))
								goto err_or_done;
						} else {
							/* Output CR characters as NL */
							temp = libterminal_do_owrite_direct(self, lf, COMPILER_LENOF(lf), mode);
							if unlikely(temp < (ssize_t)COMPILER_LENOF(lf))
								goto err_or_done;
						}
					}
					++result; /* Account for the control character */
					flush_start = iter + 1;
				}
				break;

			default: break;
			}
		}
		assert((size_t)result == (size_t)(flush_start - (byte_t const *)src));
		if (flush_start < end) {
			temp = libterminal_do_owrite_direct(self, flush_start, (size_t)(end - flush_start), mode);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
	}
done:
	assert(result < 0 || (size_t)result <= num_bytes);
	return result;
err_or_done:
	if (temp >= 0)
		goto done;
err:
	return temp;
}

PRIVATE ssize_t CC
libterminal_do_owrite_nostop(struct terminal *__restrict self,
                             __USER __CHECKED void const *src,
                             size_t num_bytes, iomode_t mode,
                             tcflag_t iflag, tcflag_t lflag) {
	ssize_t result;
	if unlikely(iflag & IXOFF) {
		result = (ssize_t)linebuffer_writef(&self->t_opend, src, num_bytes, mode);
#ifndef __KERNEL__
		if unlikely(result < 0)
			goto done;
#endif /* !__KERNEL__ */
		/* Check for race condition: IXOFF was disabled in the mean time... */
		iflag = ATOMIC_READ(self->t_ios.c_iflag);
		if unlikely(!(iflag & IXOFF)) {
			ssize_t temp;
			temp = libterminal_flush_obuf(self, mode, lflag);
			if unlikely(temp < 0)
				return temp;
		}
		goto done;
	}
	result = libterminal_do_owrite_nostop_nobuf(self, src, num_bytes, mode, lflag);
done:
	return result;
}

PRIVATE ssize_t CC
libterminal_do_owrite(struct terminal *__restrict self,
                      __USER __CHECKED void const *src,
                      size_t num_bytes, iomode_t mode,
                      tcflag_t iflag, tcflag_t lflag) {
	ssize_t result;
	if ((lflag & TOSTOP) && self->t_chk_sigttou != NULL) {
		/* Must send `SIGTTOU' to a background process group. */
		result = (*self->t_chk_sigttou)(self);
		if unlikely(result < 0)
			goto done;
	}
	result = libterminal_do_owrite_nostop(self,
	                                      src,
	                                      num_bytes,
	                                      mode,
	                                      iflag,
	                                      lflag);
done:
	return result;
}


PRIVATE NONNULL((1)) ssize_t CC
libterminal_do_owrite_force_echo(struct terminal *__restrict self,
                                 __USER __CHECKED void const *src,
                                 size_t num_bytes, iomode_t mode,
                                 tcflag_t lflag) {
	ssize_t result, temp;
	if (!(lflag & ECHOCTL)) {
		/* Don't escape control characters (directly forward input text) */
		result = libterminal_do_owrite_nostop_nobuf(self,
		                                            src,
		                                            num_bytes,
		                                            mode,
		                                            lflag);
	} else {
		/* Must escape ASCII control characters (0x00 ... 0x1f) using the ^X notation */
		byte_t const *iter, *end, *flush_start;
		result      = 0;
		iter        = (byte_t const *)src;
		end         = iter + num_bytes;
		flush_start = iter;
		for (; iter < end; ++iter) {
			byte_t buf[2];
			byte_t ch = *iter;
			assert((size_t)result == (size_t)(flush_start - (byte_t const *)src));
			if (ch >= 0x20)
				continue;
			if (ch == '\t' || ch == '\r' || ch == '\n')
				continue; /* Don't escape these... */
			if (flush_start < iter) {
				size_t count;
				count = (size_t)(iter - flush_start);
				temp = libterminal_do_owrite_nostop_nobuf(self,
				                                          flush_start,
				                                          count,
				                                          mode,
				                                          lflag);
				if unlikely(temp < 0)
					goto err;
				result += temp;
				if unlikely((size_t)temp < count)
					goto done;
			}
			buf[0] = '^';
			buf[1] = '@' + ch;
			temp   = libterminal_do_owrite_nostop_nobuf(self, buf, 2, mode, lflag);
			if unlikely(temp < 2) {
				if unlikely(temp < 0)
					goto err;
				goto done;
			}
			++result; /* Account for the control character */
			flush_start = iter + 1;
		}
		if (flush_start < end) {
			temp = libterminal_do_owrite_nostop_nobuf(self,
			                                          flush_start,
			                                          (size_t)(end - flush_start),
			                                          mode,
			                                          lflag);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
	}
done:
	return (ssize_t)result;
err:
	return temp;
}

PRIVATE NONNULL((1)) ssize_t CC
libterminal_do_owrite_echo(struct terminal *__restrict self,
                           __USER __CHECKED void const *src,
                           size_t num_bytes, iomode_t mode,
                           tcflag_t lflag) {
	ssize_t result, temp;
	if (!(lflag & ECHO)) {
		result = 0;
		if (lflag & ECHONL) {
			/* Echo NEWLINE-characters */
			cc_t nl1, nl2;
			size_t i;
			nl1 = ATOMIC_READ(self->t_ios.c_cc[VEOL]);
			nl2 = ATOMIC_READ(self->t_ios.c_cc[VEOL2]);
			for (i = 0; i < num_bytes; ++i) {
				byte_t ch;
				ch = ((byte_t const *)src)[i];
				if (ch == '\n' || ch == nl1 || ch == nl2) {
					temp = libterminal_do_owrite_force_echo(self, &ch, 1, mode, lflag);
					if unlikely(temp <= 0)
						goto err_or_done;
					result += temp;
				}
			}
		}
		goto done;
	}
	result = libterminal_do_owrite_force_echo(self, src, num_bytes, mode, lflag);
done:
	return result;
err_or_done:
	if (!temp)
		goto done;
	return temp;
}




/* Write the given input to the canon */
PRIVATE NONNULL((1)) ssize_t CC
libterminal_do_iwrite_canon(struct terminal *__restrict self,
                            __USER __CHECKED void const *src,
                            size_t num_bytes, iomode_t mode,
                            tcflag_t iflag, tcflag_t lflag) {
	ssize_t result;
	result = linebuffer_writef(&self->t_canon, src, num_bytes, mode);
	if unlikely(result < 0)
		goto done;
	if ((iflag & IMAXBEL) && ((size_t)result < num_bytes) &&
	    (!(mode & IO_NONBLOCK) || (ATOMIC_READ(self->t_canon.lb_line.lc_size) >=
	                               ATOMIC_READ(self->t_canon.lb_limt)))) {
		ssize_t temp;
		/* Print a bell-character-sequence to the output */
		temp = libterminal_do_owrite_nostop_nobuf(self, bell, COMPILER_LENOF(bell), mode,
		                                          /* Disable `ECHOCTL' to prevent `bell' from being escaped. */
		                                          lflag & ~ECHOCTL);
		if unlikely(temp < 0)
			return temp;
	}
	/* Echo canonical input on-screen */
	if ((lflag & (ECHO | EXTPROC)) == ECHO)
		libterminal_do_owrite_echo(self, src, result, mode, lflag);
done:
	return result;
}

/* Flush the input buffer canon by writing all of its contents to `t_ibuf',
 * thus allowing the data to be read by a future call to `terminal_iread()'
 * @return: * : The number of flushed characters.
 * @return: <0: [USERSPACE] An error occurred (s.a. `errno') */
INTERN NONNULL((1)) KERNEL_SELECT(size_t, ssize_t) CC
libterminal_flush_icanon(struct terminal *__restrict self, iomode_t mode)
		KERNEL_SELECT(__THROWS(E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC, ...),
		              __THROWS(E_WOULDBLOCK, E_INTERRUPT, ...)) {
	KERNEL_SELECT(size_t, ssize_t) result;
	struct linecapture cap;
	linebuffer_capture(&self->t_canon, &cap);
	RAII_FINALLY { linebuffer_release(&self->t_canon, &cap); };
	result = libterminal_do_iwrite_direct(self, cap.lc_base, cap.lc_size, mode);
	return result;
}


/* Return the number of unicode characters within a given utf-8 string */
PRIVATE ATTR_PURE WUNUSED size_t CC
utf8_character_count(__USER __CHECKED /*utf-8*/ char const *string,
                     size_t num_bytes) {
	size_t result = 0;
	__USER __CHECKED char const *ptr, *end;
	ptr = string;
	end = string + num_bytes;
	while (ptr < end) {
		unicode_readutf8_n(&ptr, end);
		++result;
	}
	return result;
}

PRIVATE NONNULL((1)) ssize_t CC
libterminal_do_iwrite_erase(struct terminal *__restrict self,
                            __USER __CHECKED void const *erased_data,
                            size_t num_bytes, iomode_t mode,
                            tcflag_t lflag, tcflag_t iflag) {
	ssize_t temp, result = 0;
	if (lflag & ECHOPRT) {
		/* Hardcopy terminal support. */
		temp = libterminal_do_owrite_echo(self, backslash, COMPILER_LENOF(backslash), mode, lflag);
		if unlikely(temp < (ssize_t)COMPILER_LENOF(backslash))
			goto err_or_done;
		result += temp;
		if (iflag & IUTF8) {
			__USER __CHECKED char const *ptr, *nextptr, *start;
			start = (__USER __CHECKED char const *)erased_data;
			ptr   = (__USER __CHECKED char const *)((byte_t const *)erased_data + num_bytes);
			/* Unwrite data-blocks one unicode character at a time. */
			while (ptr > start) {
				nextptr = ptr;
				unicode_readutf8_rev_n(&nextptr, start);
				temp = libterminal_do_owrite_echo(self,
				                                  nextptr,
				                                  (size_t)((byte_t const *)ptr -
				                                           (byte_t const *)nextptr),
				                                  mode,
				                                  lflag);
				if unlikely(temp <= 0)
					goto err_or_done;
				result += temp;
				ptr = nextptr;
			}
		} else {
			/* Unwrite data-blocks one byte at a time. */
			while (num_bytes) {
				--num_bytes;
				temp = libterminal_do_owrite_echo(self,
				                                  (byte_t const *)erased_data + num_bytes,
				                                  1,
				                                  mode,
				                                  lflag);
				if unlikely(temp <= 0)
					goto err_or_done;
				result += temp;
			}
		}
		temp = libterminal_do_owrite_echo(self, slash, COMPILER_LENOF(slash), mode, lflag);
		if unlikely(temp < (ssize_t)COMPILER_LENOF(slash))
			goto err_or_done;
		result += temp;
	} else {
		size_t character_count;
		character_count = num_bytes;
		/* If UTF-8 is supported, count the number of characters
		 * to  delete,  rather   than  the   number  of   bytes. */
		if (iflag & IUTF8)
			character_count = utf8_character_count((__USER __CHECKED /*utf-8*/ char const *)erased_data, num_bytes);
		while (character_count) {
			--character_count;
			temp = libterminal_do_owrite_echo(self, erase1, COMPILER_LENOF(erase1), mode,
			                                  /* Disable `ECHOCTL', since `erase1' would
			                                   * otherwise  get   escaped   as   `^H ^H' */
			                                  lflag & ~ECHOCTL);
			if unlikely(temp < (ssize_t)COMPILER_LENOF(erase1))
				goto err_or_done;
			result += temp;
		}
	}
done:
	return result;
err_or_done:
	if (temp >= 0)
		goto done;
/*err:*/
	return temp;
}



/* Write PTY input after control characters have been handled. */
PRIVATE NONNULL((1)) ssize_t CC
libterminal_do_iwrite_controlled(struct terminal *__restrict self,
                                 __USER __CHECKED void const *src,
                                 size_t num_bytes, iomode_t mode,
                                 tcflag_t iflag, tcflag_t lflag) {
	ssize_t result, temp;
	struct linecapture capture;
	if (lflag & ICANON) {
		/* Canonical input mode */
		byte_t const *iter, *end, *flush_start;
		result      = 0;
		iter        = (byte_t const *)src;
		end         = iter + num_bytes;
		flush_start = iter;
		for (; iter < end; ++iter) {
			byte_t ch = *iter;
			assert((size_t)result == (size_t)(flush_start - (byte_t const *)src));
			/* Canon control characters (COMMIT, ERASE, etc.) */
			if (ch == _POSIX_VDISABLE)
				continue; /* Don't enable this. */
			if (ch == '\n' ||
			    ch == self->t_ios.c_cc[VEOL] ||
			    ch == self->t_ios.c_cc[VEOL2]) {
				size_t count;
				/* NOTE: +1, because the COMMIT character should be included within the flush. */
				count = (size_t)((iter + 1) - flush_start);
				temp  = libterminal_do_iwrite_canon(self, flush_start, count, mode, iflag, lflag);
				if unlikely(temp < 0)
					goto err;
				result += temp;
				if unlikely((size_t)temp < count)
					goto done;
				flush_start = iter + 1;
				/* Flush the current canon */
				IF_NOT_KERNEL(temp =) libterminal_flush_icanon(self, mode);
#ifndef __KERNEL__
				if unlikely(temp < 0)
					goto err;
#endif /* !__KERNEL__ */
			} else if (ch == self->t_ios.c_cc[VEOF]) {
				size_t count;
				count = (size_t)(iter - flush_start);
				temp  = libterminal_do_iwrite_canon(self, flush_start, count, mode, iflag, lflag);
				if unlikely(temp < 0)
					goto err;
				result += temp;
				if unlikely((size_t)temp < count)
					goto done;
				/* Flush the canon, set the `__IEOFING' flag, and broadcast `self->t_ibuf.rb_nempty' */
				IF_NOT_KERNEL(temp =) libterminal_flush_icanon(self, mode);
#ifndef __KERNEL__
				if unlikely(temp < 0)
					goto err;
#endif /* !__KERNEL__ */
				libterminal_do_iwrite_set_eofing(self);
				++result; /* Account for the control character */
				flush_start = iter + 1;
			} else if (ch == self->t_ios.c_cc[VERASE] && (lflag & ECHOE)) {
				size_t count;
				count = (size_t)(iter - flush_start);
				temp  = libterminal_do_iwrite_canon(self, flush_start, count, mode, iflag, lflag);
				if unlikely(temp < 0)
					goto err;
				result += temp;
				if unlikely((size_t)temp < count)
					goto done;
				/* Erase last written character */
				linebuffer_capture(&self->t_canon, &capture);
				if unlikely(!capture.lc_size) {
					/* Use rewrite in case a buffer was allocated, so that the buffer can be re-used */
					IF_NOT_KERNEL(temp =) linebuffer_rewrite(&self->t_canon, &capture);
#ifndef __KERNEL__
					if unlikely(temp < 0)
						goto err;
#endif /* !__KERNEL__ */
					if (iflag & IMAXBEL) {
						/* Cannot erase character from empty canon */
						temp = libterminal_do_owrite_echo(self, bell, COMPILER_LENOF(bell), mode,
						                                  /* Disable `ECHOCTL' to prevent `bell' from being escaped. */
						                                  lflag & ~ECHOCTL);
						if unlikely(temp < 0)
							goto err;
					}
				} else {
					byte_t delch;
					delch = capture.lc_base[--capture.lc_size];
					IF_NOT_KERNEL(temp =) linebuffer_rewrite(&self->t_canon, &capture);
#ifndef __KERNEL__
					if unlikely(temp < 0)
						goto err;
#endif /* !__KERNEL__ */
					temp = libterminal_do_iwrite_erase(self, &delch, 1, mode, lflag, iflag);
					if unlikely(temp < 0)
						goto err;
				}
				++result; /* Account for the control character */
				flush_start = iter + 1;
			} else if (ch == self->t_ios.c_cc[VKILL] && (lflag & ECHOK)) {
				size_t count;
				count = (size_t)(iter - flush_start);
				temp  = libterminal_do_iwrite_canon(self, flush_start, count, mode, iflag, lflag);
				if unlikely(temp < 0)
					goto err;
				result += temp;
				if unlikely((size_t)temp < count)
					goto done;
				/* Clear the entire input */
				linebuffer_capture(&self->t_canon, &capture);
				RAII_FINALLY { linebuffer_release(&self->t_canon, &capture); };
				if (lflag & ECHOKE) { /* Only echo when `ECHOKE' is set. */
					/* Erase the entire input line. */
					temp = libterminal_do_iwrite_erase(self,
					                                   capture.lc_base,
					                                   capture.lc_size,
					                                   mode,
					                                   lflag,
					                                   iflag);
					if unlikely(temp < 0)
						goto err;
				}
				++result; /* Account for the control character */
				flush_start = iter + 1;
			} else if (ch == self->t_ios.c_cc[VWERASE] && (lflag & (ECHOE | IEXTEN))) {
				size_t count;
				count = (size_t)(iter - flush_start);
				temp  = libterminal_do_iwrite_canon(self, flush_start, count, mode, iflag, lflag);
				if unlikely(temp < 0)
					goto err;
				result += temp;
				if unlikely((size_t)temp < count)
					goto done;
				/* Erase last written character */
				linebuffer_capture(&self->t_canon, &capture);
				TRY {
					if unlikely(!capture.lc_size) {
						if (iflag & IMAXBEL) {
							/* Cannot erase character from empty canon */
							temp = libterminal_do_owrite_echo(self, bell, COMPILER_LENOF(bell), mode,
							                                  /* Disable `ECHOCTL' to prevent `bell' from being escaped. */
							                                  lflag & ~ECHOCTL);
							if unlikely(temp < 0)
								goto err_capture;
						}
					} else {
						size_t new_size = capture.lc_size;

						/* Erase word (while (isspace(last)) erase(); while (!isspace(last)) erase()) */
						if (iflag & IUTF8) {
							char32_t uch;
							char const *textptr, *newptr;
							textptr = (char *)capture.lc_base + new_size;
							while (textptr > (char const *)capture.lc_base) {
								newptr = textptr;
								uch = unicode_readutf8_rev_n(&newptr, (char const *)capture.lc_base);
								if (!unicode_isspace(uch))
									break;
								textptr = newptr;
							}
							while (textptr > (char const *)capture.lc_base) {
								newptr = textptr;
								uch = unicode_readutf8_rev_n(&newptr, (char const *)capture.lc_base);
								if (unicode_isspace(uch))
									break;
								textptr = newptr;
							}
							new_size = (size_t)(textptr - (char *)capture.lc_base);
						} else {
							while (new_size && isspace(capture.lc_base[new_size - 1]))
								--new_size;
							while (new_size && !isspace(capture.lc_base[new_size - 1]))
								--new_size;
						}

						/* Echo erased characters. */
						temp = libterminal_do_iwrite_erase(self,
						                                   capture.lc_base + new_size,
						                                   capture.lc_size - new_size,
						                                   mode,
						                                   lflag,
						                                   iflag);
						if unlikely(temp < 0)
							goto err_capture;

						/* Re-write the truncated canon */
						capture.lc_size = new_size;
					}
				} EXCEPT {
					linebuffer_release(&self->t_canon, &capture);
					RETHROW();
				}
				IF_NOT_KERNEL(temp =) linebuffer_rewrite(&self->t_canon, &capture);
#ifndef __KERNEL__
				if unlikely(temp < 0)
					goto err;
#endif /* !__KERNEL__ */
				++result; /* Account for the control character */
				flush_start = iter + 1;
			} else if (ch == self->t_ios.c_cc[VREPRINT] && (lflag & IEXTEN)) {
				size_t count;

				/* Re-echo the contents of the canon */
				count = (size_t)(iter - flush_start);
				temp  = libterminal_do_iwrite_canon(self, flush_start, count, mode, iflag, lflag);
				if unlikely(temp < 0)
					goto err;
				result += temp;
				if unlikely((size_t)temp < count)
					goto done;
				++result; /* Account for the control character */
				flush_start = iter + 1;

				/* Clear the entire input */
				linebuffer_capture(&self->t_canon, &capture);
				TRY {
					/* Re-echo the contents of the canon */
					temp = libterminal_do_iwrite_canon(self,
					                                   capture.lc_base,
					                                   capture.lc_size,
					                                   mode,
					                                   iflag,
					                                   lflag);
					if unlikely(temp < 0)
						goto err_capture;
				} EXCEPT {
					linebuffer_release(&self->t_canon, &capture);
					RETHROW();
				}
				IF_NOT_KERNEL(temp =) linebuffer_rewrite(&self->t_canon, &capture);
#ifndef __KERNEL__
				if unlikely(temp < 0)
					goto err;
#endif /* !__KERNEL__ */
			}
		}
		if (flush_start < end) {
			temp = libterminal_do_iwrite_canon(self,
			                                   flush_start,
			                                   (size_t)(end - flush_start),
			                                   mode,
			                                   iflag,
			                                   lflag);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
	} else {
		/* Write input data */
		result = (ssize_t)libterminal_do_iwrite_direct(self, src, num_bytes, mode);
#ifndef __KERNEL__
		if unlikely(result < 0)
			goto done;
#endif /* !__KERNEL__ */
		/* Try to echo input data */
		temp = libterminal_do_owrite_echo(self, src, (size_t)result, mode, lflag);
		if unlikely(temp < 0)
			goto err;
	}
done:
	assert(result < 0 || (size_t)result <= num_bytes);
	return result;
err_capture:
	linecapture_fini(&capture);
err:
	return temp;
}

/* Write PTY input after it has been formatted according to `c_iflag & ...' */
PRIVATE NONNULL((1)) ssize_t CC
libterminal_do_iwrite_formatted(struct terminal *__restrict self,
                                __USER __CHECKED void const *src,
                                size_t num_bytes, iomode_t mode,
                                tcflag_t iflag, tcflag_t lflag) {
	ssize_t result, temp;
	if unlikely(!num_bytes)
		return 0;
	if ((ATOMIC_READ(self->t_ios.c_lflag) & __IESCAPING) &&
	    (ATOMIC_FETCHAND(self->t_ios.c_lflag, ~__IESCAPING) & __IESCAPING)) {
		byte_t ch;
		/* Escape the first character. */
		ch = ((byte_t const *)src)[0];
		if (lflag & ICANON) {
			result = libterminal_do_iwrite_canon(self, &ch, 1, mode, iflag, lflag);
		} else {
			result = (ssize_t)libterminal_do_iwrite_direct(self, &ch, 1, mode);
#ifndef __KERNEL__
			if unlikely(result <= 0)
				goto done;
#endif /* !__KERNEL__ */
			/* Try to echo data into the S2M ring */
			temp = libterminal_do_owrite_echo(self, &ch, 1, mode, lflag);
			if unlikely(temp < 0)
				goto err;
		}
		if unlikely(!result)
			return 0;
		result = libterminal_do_iwrite_formatted(self,
		                                         (byte_t const *)src + 1,
		                                         num_bytes - 1,
		                                         mode,
		                                         iflag,
		                                         lflag);
		return result + 1;
	}
	if unlikely(lflag & EXTPROC) {
		result = libterminal_do_iwrite_controlled(self,
		                                          src,
		                                          num_bytes,
		                                          mode,
		                                          iflag,
		                                          lflag);
	} else {
		byte_t const *iter, *end, *flush_start;
		result      = 0;
		iter        = (byte_t const *)src;
		end         = iter + num_bytes;
		flush_start = iter;
		/* If any input is given (which was tested above), support the IXANY
		 * flag which will restore output  whenever any input is typed  out. */
		assert(num_bytes);
		if ((iflag & IXANY) &&
		    (ATOMIC_READ(self->t_ios.c_iflag) & IXOFF) != 0 &&
		    (ATOMIC_FETCHAND(self->t_ios.c_iflag, ~IXOFF) & IXOFF) != 0) {
			temp = libterminal_flush_obuf(self, mode, lflag);
			if unlikely(temp < 0)
				goto err;
		}
		for (; iter < end; ++iter) {
			byte_t ch = *iter;
			assert((size_t)result == (size_t)(flush_start - (byte_t const *)src));
			if (ch == self->t_ios.c_cc[VINTR] && (lflag & ISIG)) {
				size_t count;
				assert(flush_start <= iter);
				count = (size_t)(iter - flush_start);
				temp  = libterminal_do_iwrite_controlled(self, flush_start, count, mode, iflag, lflag);
				if unlikely(temp < 0)
					goto err;
				result += temp;
				if unlikely((size_t)temp < count)
					goto done;
				/* Send a signal to the foreground process. */
				if (self->t_raise) {
					temp = (*self->t_raise)(self, SIGINT);
					if unlikely(temp < 0)
						goto err;
				}
				++result; /* Account for the control character */
				flush_start = iter + 1;
			} else if (ch == self->t_ios.c_cc[VQUIT] && (lflag & ISIG)) {
				size_t count;
				assert(flush_start <= iter);
				count = (size_t)(iter - flush_start);
				temp  = libterminal_do_iwrite_controlled(self, flush_start, count, mode, iflag, lflag);
				if unlikely(temp < 0)
					goto err;
				result += temp;
				if unlikely((size_t)temp < count)
					goto done;
				/* Send a signal to the foreground process. */
				if (self->t_raise) {
					temp = (*self->t_raise)(self, SIGQUIT);
					if unlikely(temp < 0)
						goto err;
				}
				++result; /* Account for the control character */
				flush_start = iter + 1;
			} else if (ch == self->t_ios.c_cc[VSUSP] && (lflag & ISIG)) {
				size_t count;
				assert(flush_start <= iter);
				count = (size_t)(iter - flush_start);
				temp  = libterminal_do_iwrite_controlled(self, flush_start, count, mode, iflag, lflag);
				if unlikely(temp < 0)
					goto err;
				result += temp;
				if unlikely((size_t)temp < count)
					goto done;
				/* Send a signal to the foreground process. */
				if (self->t_raise) {
					temp = (*self->t_raise)(self, SIGTSTP);
					if unlikely(temp < 0)
						goto err;
				}
				++result; /* Account for the control character */
				flush_start = iter + 1;
			} else if (ch == self->t_ios.c_cc[VLNEXT]) {
				/* Escape the next character from being matched against any `c_cc[*]' items. */
				if (flush_start < iter) {
					size_t count;
					count = (size_t)(iter - flush_start);
					temp  = libterminal_do_iwrite_controlled(self, flush_start, count, mode, iflag, lflag);
					if unlikely(temp < 0)
						goto err;
					result += temp;
					if unlikely((size_t)temp < count) {
						ATOMIC_OR(self->t_ios.c_lflag, __IESCAPING);
						goto done;
					}
				}
				++result; /* Account for the control character */
				flush_start = iter + 1;
				if (iter == end - 1) {
					ATOMIC_OR(self->t_ios.c_lflag, __IESCAPING);
				} else {
					ch = *++iter;
					/* Directly escape the next character */
					if (lflag & ICANON) {
						temp = libterminal_do_iwrite_canon(self, &ch, 1, mode, iflag, lflag);
						if unlikely(temp < 1)
							goto err_or_done;
						assert(temp == 1);
						result += temp;
					} else {
#ifdef __KERNEL__
						if unlikely(!libterminal_do_iwrite_direct(self, &ch, 1, mode))
							goto done;
						++result;
#else /* __KERNEL__ */
						temp = libterminal_do_iwrite_direct(self, &ch, 1, mode);
						if unlikely(temp < 1)
							goto err_or_done;
						assert(temp == 1);
						result += temp;
#endif /* !__KERNEL__ */
						/* Try to echo data into the S2M ring */
						temp = libterminal_do_owrite_echo(self, &ch, 1, mode, lflag);
						if unlikely(temp < 0)
							goto err;
					}
					/* Continue flushing after the escaped character. */
					flush_start = iter + 1;
				}
			} else if (ch == self->t_ios.c_cc[VSTOP] && (iflag & IXON)) {
				size_t count;
				count = (size_t)(iter - flush_start);
				temp  = libterminal_do_iwrite_controlled(self, flush_start, count, mode, iflag, lflag);
				if unlikely(temp < 0)
					goto err;
				result += temp;
				/* Enable suspended output */
				if unlikely((size_t)temp < count) {
					ATOMIC_OR(self->t_ios.c_iflag, IXOFF);
					goto done;
				}
				/* If this is the last character, or not just any sort of input
				 * can   disable  XOFF-mode  then  disable  output  processing. */
				if (iter == end - 1 || !(iflag & IXANY))
					ATOMIC_OR(self->t_ios.c_iflag, IXOFF);
				++result; /* Account for the control character */
				flush_start = iter + 1;
			} else if (ch == self->t_ios.c_cc[VSTART] && (iflag & IXON)) {
				size_t count;
				count = (size_t)(iter - flush_start);
				temp  = libterminal_do_iwrite_controlled(self, flush_start, count, mode, iflag, lflag);
				if unlikely(temp < 0)
					goto err;
				result += temp;
				if unlikely((size_t)temp < count)
					goto done;
				/* Disable suspended output (and re-enable output processing) */
				if (ATOMIC_FETCHAND(self->t_ios.c_iflag, ~IXOFF) & IXOFF) {
					temp = libterminal_flush_obuf(self, mode, lflag);
					if unlikely(temp < 0)
						goto err;
				}
				++result; /* Account for the control character */
				flush_start = iter + 1;
			}
		}
		if (flush_start < end) {
			temp = libterminal_do_iwrite_controlled(self,
			                                        flush_start,
			                                        (size_t)(end - flush_start),
			                                        mode,
			                                        iflag,
			                                        lflag);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
	}
done:
	return result;
err_or_done:
	if (!temp)
		goto done;
err:
	return temp;
}


PRIVATE ssize_t CC
libterminal_do_iwrite(struct terminal *__restrict self,
                      __USER __CHECKED void const *src,
                      size_t num_bytes, iomode_t mode, tcflag_t iflag) {
	tcflag_t lflag;
	ssize_t result, temp;
	lflag = ATOMIC_READ(self->t_ios.c_lflag);
	/* Check for special case: No formatting required. */
	if ((iflag & (PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IUCLC)) == 0 ||
	    ((lflag & EXTPROC) && (iflag & (ISTRIP | INLCR | IGNCR | ICRNL | IUCLC)) == 0)) {
		result = libterminal_do_iwrite_formatted(self,
		                                         src,
		                                         num_bytes,
		                                         mode,
		                                         iflag,
		                                         lflag);
	} else if unlikely(!num_bytes) {
		result = 0;
	} else {
		byte_t const *iter, *end, *flush_start;
		result      = 0;
		iter        = (byte_t const *)src;
		end         = iter + num_bytes;
		flush_start = iter;
		TRY {
			byte_t ch;
			ch = *iter;
			if ((lflag & (ICANON | XCASE | __IXCASEING)) == (ICANON | XCASE | __IXCASEING)) {
				lflag &= ~__IXCASEING;
				if (ch >= 'A' && ch <= 'Z') {
					++iter; /* Keep this character as upper-case. */
				} else {
					/* Print the missing backslash. */
					temp = libterminal_do_iwrite_formatted(self, "\\", 1,
					                                       mode, iflag, lflag);
					if unlikely(temp <= 0)
						goto err_or_done;
					result += temp;
					goto switch_ch;
				}
			} else {
				goto switch_ch;
			}
			for (; iter < end; ++iter) {
				ch = *iter;
switch_ch:
				assert((size_t)result == (size_t)(flush_start - (byte_t const *)src));
				switch (ch) {

				case 255:
					if (iflag & PARMRK && !(lflag & EXTPROC)) {
						/*  Must escape `\377' (255) as `\377\377' */
						if (flush_start < iter) {
							size_t count;
							count = (size_t)(iter - flush_start);
							temp = libterminal_do_iwrite_formatted(self, flush_start, count,
							                                       mode, iflag, lflag);
							if unlikely(temp < 0)
								goto err;
							result += temp;
							if unlikely((size_t)temp < count)
								goto done;
							flush_start = iter; /* Re-print a second \377 during the next flush */
						}
						temp = libterminal_do_iwrite_formatted(self, &ch, 1, mode, iflag, lflag);
						if unlikely(temp < 1)
							goto err_or_done;
						break;
					}
					ATTR_FALLTHROUGH
				case 128 ... 254:
					if (iflag & ISTRIP) {
						/* Strip the eighth bit. */
						if (flush_start < iter) {
							size_t count;
							count = (size_t)(iter - flush_start);
							temp = libterminal_do_iwrite_formatted(self, flush_start, count,
							                                       mode, iflag, lflag);
							if unlikely(temp < 0)
								goto err;
							result += temp;
							if unlikely((size_t)temp < count)
								goto done;
						}
						ch &= 0x7f;
						temp = libterminal_do_iwrite_formatted(self, &ch, 1, mode, iflag, lflag);
						if unlikely(temp < 1)
							goto err_or_done;
						++result; /* Account for the control character */
						flush_start = iter + 1;
					}
					break;

				case 'A' ... 'Z':
					if ((lflag & (ICANON | XCASE)) == (ICANON | XCASE)) {
						if (lflag & __IXCASEING) {
							assert(flush_start == iter - 1 || iter == (byte_t const *)src);
							ch += ('a' - 'A');
							temp = libterminal_do_iwrite_formatted(self, &ch, 1,
							                                       mode, iflag, lflag);
							if unlikely(temp < 1)
								goto err_or_done;
							if (iter != (byte_t const *)src)
								++result; /* Account for the \-character */
							++result; /* Account for the uppercase character */
							flush_start = iter + 1;
						}
					} else if ((iflag & IUCLC) && (lflag & IEXTEN)) {
						if (flush_start < iter) {
							size_t count;
							count = (size_t)(iter - flush_start);
							temp = libterminal_do_iwrite_formatted(self, flush_start, count,
							                                       mode, iflag, lflag);
							if unlikely(temp < 0)
								goto err;
							result += temp;
							if unlikely((size_t)temp < count)
								goto done;
						}
						ch += ('a' - 'A');
						temp = libterminal_do_iwrite_formatted(self, &ch, 1,
						                                       mode, iflag, lflag);
						if unlikely(temp < 1)
							goto err_or_done;
						++result; /* Account for the control character */
						flush_start = iter + 1;
					}
					break;

				case '\\':
					if ((lflag & (ICANON | XCASE)) == (ICANON | XCASE)) {
						if (flush_start < iter) {
							size_t count;
							count = (size_t)(iter - flush_start);
							temp = libterminal_do_iwrite_formatted(self, flush_start, count,
							                                       mode, iflag, lflag);
							if unlikely(temp < 0)
								goto err;
							result += temp;
							if unlikely((size_t)temp < count)
								goto done;
						}
						flush_start = iter;
						if (iter == end - 1) {
							++result; /* Account for the control character */
							flush_start = end;
						}
						lflag |= __IXCASEING;
					}
					continue;

				case '\n':
					if (iflag & INLCR) {
						if (flush_start < iter) {
							size_t count;
							count = (size_t)(iter - flush_start);
							temp = libterminal_do_iwrite_formatted(self, flush_start, count,
							                                       mode, iflag, lflag);
							if unlikely(temp < 0)
								goto err;
							result += temp;
							if unlikely((size_t)temp < count)
								goto done;
						}
						if (!(iflag & IGNCR)) {
							temp = libterminal_do_iwrite_formatted(self, "\r", 1,
							                                       mode, iflag, lflag);
							if unlikely(temp < 1)
								goto err_or_done;
						}
						++result; /* Account for the control character */
						flush_start = iter + 1;
					}
					break;

				case '\r':
					if (iflag & (IGNCR | ICRNL)) {
						if (flush_start < iter) {
							size_t count;
							count = (size_t)(iter - flush_start);
							temp = libterminal_do_iwrite_formatted(self, flush_start, count,
							                                       mode, iflag, lflag);
							if unlikely(temp < 0)
								goto err;
							result += temp;
							if unlikely((size_t)temp < count)
								goto done;
						}
						if ((iflag & (IGNCR | ICRNL)) == ICRNL) {
							/* Translate to LN */
							temp = libterminal_do_iwrite_formatted(self, "\n", 1,
							                                       mode, iflag, lflag);
							if unlikely(temp < 1)
								goto err_or_done;
						}
						++result; /* Account for the control character */
						flush_start = iter + 1;
					}
					break;

				default:
					break;
				}
				lflag &= ~__IXCASEING;
			}
			if (flush_start < end) {
				temp = libterminal_do_iwrite_formatted(self, flush_start,
				                                       (size_t)(end - flush_start),
				                                       mode, iflag, lflag);
				result += temp;
			}
		} EXCEPT {
			if ((lflag & (ICANON | XCASE)) == (ICANON | XCASE)) {
				tcflag_t of;
				do {
					of = ATOMIC_READ(self->t_ios.c_lflag);
				} while (!ATOMIC_CMPXCH_WEAK(self->t_ios.c_lflag, of,
				                             (of & ~__IXCASEING) | (lflag & __IXCASEING)));
			}
			RETHROW();
		}
		if ((lflag & (ICANON | XCASE)) == (ICANON | XCASE)) {
			tcflag_t of;
			do {
				of = ATOMIC_READ(self->t_ios.c_lflag);
			} while (!ATOMIC_CMPXCH_WEAK(self->t_ios.c_lflag, of,
			                             (of & ~__IXCASEING) | (lflag & __IXCASEING)));
		}
	}
done:
	return result;
err_or_done:
	if (!temp)
		goto done;
err:
	return temp;
}







PRIVATE ssize_t CC
libterminal_flush_obuf(struct terminal *__restrict self,
                       iomode_t mode, tcflag_t lflag) {
	ssize_t result;
	struct linecapture cap;
	linebuffer_capture(&self->t_opend, &cap);
	RAII_FINALLY { linebuffer_release(&self->t_opend, &cap); };
	result = libterminal_do_owrite_nostop_nobuf(self, cap.lc_base, cap.lc_size, mode, lflag);
	return result;
}

PRIVATE ssize_t CC
libterminal_flush_ibuf(struct terminal *__restrict self,
                       iomode_t mode, tcflag_t iflag) {
	ssize_t result;
	struct linecapture cap;
	linebuffer_capture(&self->t_ipend, &cap);
	RAII_FINALLY { linebuffer_release(&self->t_ipend, &cap); };
	result = libterminal_do_iwrite(self, cap.lc_base, cap.lc_size, mode, iflag);
	return result;
}


/* Print output (display) or input (keyboard) to a given terminal
 * @param: mode:   I/O mode (set of `IO_*'; the terminal sub-system recognizes `IO_NONBLOCK')
 * @return: >= 0 : The sum of return values from calls to the associated printer
 *                 - The usual rules apply where negative return values are propagated immediately.
 *                 - Data printed when an I/O buffer is flushed is not added to this sum, however
 *                   negative values  resulting  from  this case  are  propagated  none-the-less.
 *                 - In cases where  data is written  to multiple printers  (e.g. terminal_iwrite() w/  ECHO),
 *                   only the return  value of  the intended  printer (in this  case `t_iprint')  is added  to
 *                   the  eventually  returned sum.  - Additionally,  in this  case, the  lower of  the return
 *                   value of the original call to `t_iprint' and num_bytes passed to it is used as the number
 *                   of bytes that  would be echoed  on-screen. (meaning  that no characters  will get  echoed
 *                   that can't be added to the input queue)
 * @return: < 0:   A format-printer returned a negative value
 * @return: -1:   [USERSPACE] Printing to one of the linebuffers failed (s.a. `linebuffer_write()'; `errno') */
INTERN NONNULL((1)) ssize_t CC
libterminal_owrite(struct terminal *__restrict self,
                   __USER __CHECKED void const *src,
                   size_t num_bytes, iomode_t mode)
		KERNEL_SELECT(__THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT, E_BADALLOC, ...),
		              __THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT, ...)) {
	ssize_t result;
	tcflag_t iflag = ATOMIC_READ(self->t_ios.c_iflag);
	tcflag_t lflag = ATOMIC_READ(self->t_ios.c_lflag);
	result = libterminal_do_owrite(self, src, num_bytes, mode, iflag, lflag);
	return result;
}

INTERN NONNULL((1)) ssize_t CC
libterminal_iwrite(struct terminal *__restrict self,
                   __USER __CHECKED void const *src,
                   size_t num_bytes, iomode_t mode)
		KERNEL_SELECT(__THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT, E_BADALLOC, ...),
		              __THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT, ...)) {
	ssize_t result;
	tcflag_t iflag = ATOMIC_READ(self->t_ios.c_iflag);
	if unlikely(iflag & __IIOFF) {
		result = (ssize_t)linebuffer_writef(&self->t_ipend, src, num_bytes, mode);
#ifndef __KERNEL__
		if unlikely(result < 0)
			goto done;
#endif /* !__KERNEL__ */
		/* Check for race condition: __IIOFF was disabled in the mean time... */
		iflag = ATOMIC_READ(self->t_ios.c_iflag);
		if unlikely(!(iflag & __IIOFF)) {
			ssize_t temp;
			temp = libterminal_flush_ibuf(self, mode, iflag);
			if unlikely(temp < 0)
				return temp;
		}
		goto done;
	}
	/* Normal case: Forward without buffering. */
	result = libterminal_do_iwrite(self, src, num_bytes, mode, iflag);
done:
	return result;
}

PRIVATE NONNULL((1)) KERNEL_SELECT(size_t, ssize_t) CC
libterminal_do_iread_chk_eofing(struct terminal *__restrict self,
                                __USER __CHECKED void *dst,
                                size_t num_bytes) {
	size_t result, temp;
	result = ringbuffer_read_nonblock(&self->t_ibuf, dst, num_bytes);
	if (result) {
done:
		return (KERNEL_SELECT(size_t, ssize_t))result;
	}
again_connect:
	/* Check (and clear) a pending EOF indicator. */
	if (ATOMIC_FETCHAND(self->t_ios.c_lflag, ~__IEOFING) & __IEOFING)
		goto done;
	/* Check if the ring was closed. */
	if unlikely(!ATOMIC_READ(self->t_ibuf.rb_limit))
		goto done;
#ifdef __KERNEL__
	task_connect(&self->t_ibuf.rb_nempty);
	TRY {
		/* Try to read more data. */
		temp = ringbuffer_read_nonblock(&self->t_ibuf,
		                                (byte_t *)dst + result,
		                                num_bytes - result);
	} EXCEPT {
		task_disconnectall();
		RETHROW();
	}
	if unlikely(temp) {
		result += temp;
		task_disconnectall();
		goto done;
	}
	/* Check if the ring was closed. */
	if unlikely(!ATOMIC_READ(self->t_ibuf.rb_limit)) {
		task_disconnectall();
		goto done;
	}
	/* Check (and clear) a pending EOF indicator. */
	if (ATOMIC_FETCHAND(self->t_ios.c_lflag, ~__IEOFING) & __IEOFING) {
		task_disconnectall();
		goto done;
	}
	/* Wait for data to become available. */
	task_waitfor();
#else /* __KERNEL__ */
	{
		/* Use futex expressions to describe what we want to wait for */
		PRIVATE struct lfutexexpr const expr[] = {
			/* (self->t_ios.c_lflag & __IEOFING) == 0 */
			LFUTEXEXPR_TEXACT_BITS(struct terminal, t_ios.c_lflag, __IEOFING, 0),
			/* self->t_ibuf.rb_limit != 0 */
			LFUTEXEXPR_TNOT_EQUAL(struct terminal, t_ibuf.rb_limit, 0),
			/* self->t_ibuf.rb_avail == 0 */
			LFUTEXEXPR_TEQUAL(struct terminal, t_ibuf.rb_avail, 0),
			LFUTEXEXPR_END
		};
		if (lfutexexpr(&self->t_ibuf.rb_nempty, self, expr, NULL, 0) < 0)
			return -1;
	}
#endif /* !__KERNEL__ */
	/* Try to read more data. */
	temp = ringbuffer_read_nonblock(&self->t_ibuf,
	                                (byte_t *)dst + result,
	                                num_bytes - result);
	if (temp) {
		result += temp;
		goto done;
	}
	goto again_connect;
}


/* Read from the terminal input buffer (usually the keyboard), and into the given `dst'
 * @param: mode: Set of `0|IO_NONBLOCK'
 * @return: * :  The number of bytes read
 * @return: <0:  [USERSPACE] An error occurred (s.a. `errno') */
INTERN NONNULL((1)) KERNEL_SELECT(size_t, ssize_t) CC
libterminal_iread(struct terminal *__restrict self,
                  __USER __CHECKED void *dst,
                  size_t num_bytes, iomode_t mode)
		__THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT) {
	KERNEL_SELECT(size_t, ssize_t) result;
	result = ringbuffer_read_nonblock(&self->t_ibuf, dst, num_bytes);
#ifndef __KERNEL__
	if unlikely(result < 0)
		goto done;
#endif /* !__KERNEL__ */
	if (!(mode & IO_NONBLOCK)) {
		if (!result) {
			if unlikely(!num_bytes)
				return 0; /* Don't block in this case! */
			/* Do a blocking read. */
			result = libterminal_do_iread_chk_eofing(self, dst, num_bytes);
#ifndef __KERNEL__
			if unlikely(result < 0)
				goto done;
#endif /* !__KERNEL__ */
		}
		if ((size_t)result < num_bytes && result != 0) {
			/* Make sure to read at least `self->t_ios.c_cc[VMIN]' characters! */
			cc_t minread = ATOMIC_READ(self->t_ios.c_cc[VMIN]);
			if ((size_t)minread > num_bytes) /* Limit by what we can even return */
				minread = (cc_t)num_bytes;
			while ((size_t)result < minread) {
				KERNEL_SELECT(size_t, ssize_t) temp;
				temp = libterminal_do_iread_chk_eofing(self,
				                                       (byte_t *)dst + result,
				                                       num_bytes - result);
#ifdef __KERNEL__
				if unlikely(!temp)
					break;
#else /* __KERNEL__ */
				if unlikely(temp <= 0) {
					if (!temp)
						break;
					return temp; /* error */
				}
#endif /* !__KERNEL__ */
				result += temp;
			}
		}
	} else if (result == 0 && num_bytes != 0 && !(mode & IO_NODATAZERO) &&
	           !ringbuffer_closed(&self->t_ibuf)) {
		/* Handle the case of a non-blocking read with no data available. */
#ifdef __KERNEL__
		/* No data available. */
		THROW(E_WOULDBLOCK_WAITFORSIGNAL);
#else /* __KERNEL__ */
		errno  = EWOULDBLOCK;
		result = -1;
#endif /* !__KERNEL__ */
	}
#ifndef __KERNEL__
done:
#endif /* !__KERNEL__ */
	return result;
}


/* Set terminal I/O settings
 * @return: < 0: [USERSPACE]   A printer callback returned negative, or an error occurred (s.a. `errno')
 * @return: < 0: [KERNELSPACE] A printer callback returned negative */
INTERN NONNULL((1, 2)) ssize_t CC
libterminal_setios(struct terminal *__restrict self,
                   struct termios const *__restrict tio,
                   struct termios *old_tio)
		KERNEL_SELECT(__THROWS(E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC, ...),
		              __THROWS(E_WOULDBLOCK, E_INTERRUPT, ...)) {
	ssize_t error;
	struct termios old;
	bool echo_disabled;
again:
	old.c_iflag = ATOMIC_READ(self->t_ios.c_iflag);
	if (!(tio->c_iflag & IXOFF) && (old.c_iflag & IXOFF) &&
	    (ATOMIC_READ(self->t_opend.lb_line.lc_size) != 0)) {
		/* Disable output text buffering (flush `t_opend') */
		error = libterminal_flush_obuf(self, 0, ATOMIC_READ(self->t_ios.c_lflag));
		if unlikely(error < 0)
			goto err;
		goto again;
	}
	if (!(tio->c_iflag & __IIOFF) && (old.c_iflag & __IIOFF) &&
	    (ATOMIC_READ(self->t_ipend.lb_line.lc_size) != 0)) {
		/* Disable input text buffering (flush `t_ipend') */
		error = libterminal_flush_ibuf(self, 0, old.c_iflag);
		if unlikely(error < 0)
			goto err;
		goto again;
	}
	old.c_iflag = ATOMIC_XCH(self->t_ios.c_iflag, tio->c_iflag);
	TRY {
		if (!(tio->c_iflag & IXOFF) && (old.c_iflag & IXOFF) &&
		    (ATOMIC_READ(self->t_opend.lb_line.lc_size) != 0)) {
			/* Disable output text buffering (flush `t_opend') */
			error = libterminal_flush_obuf(self, 0, ATOMIC_READ(self->t_ios.c_lflag));
			if unlikely(error < 0) {
				ATOMIC_CMPXCH(self->t_ios.c_iflag, tio->c_iflag, old.c_iflag);
				goto err;
			}
		}
		if (!(tio->c_iflag & __IIOFF) && (old.c_iflag & __IIOFF) &&
		    (ATOMIC_READ(self->t_ipend.lb_line.lc_size) != 0)) {
			/* Disable input text buffering (flush `t_ipend') */
			error = libterminal_flush_ibuf(self, 0, old.c_iflag);
			if unlikely(error < 0) {
				ATOMIC_CMPXCH(self->t_ios.c_iflag, tio->c_iflag, old.c_iflag);
				goto err;
			}
		}
	} EXCEPT {
		ATOMIC_CMPXCH(self->t_ios.c_iflag, tio->c_iflag, old.c_iflag);
		RETHROW();
	}
	old.c_oflag  = ATOMIC_XCH(self->t_ios.c_oflag, tio->c_oflag);
	old.c_cflag  = ATOMIC_XCH(self->t_ios.c_cflag, tio->c_cflag);
	old.c_lflag  = ATOMIC_XCH(self->t_ios.c_lflag, tio->c_lflag);
	old.c_line   = ATOMIC_XCH(self->t_ios.c_line, tio->c_line);
	old.c_ispeed = ATOMIC_XCH(self->t_ios.c_ispeed, tio->c_ispeed);
	old.c_ospeed = ATOMIC_XCH(self->t_ios.c_ospeed, tio->c_ospeed);
	memcpy(old.c_cc, self->t_ios.c_cc, sizeof(old.c_cc));
	memcpy(self->t_ios.c_cc, tio->c_cc, sizeof(old.c_cc));
	/* Broadcast signals when certain flags change. */
	echo_disabled = ((old.c_lflag & (ECHO | EXTPROC)) == ECHO && (tio->c_lflag & (ECHO | EXTPROC)) != ECHO);
	if ((old.c_lflag & __IEOFING) == 0 && (tio->c_lflag & __IEOFING) != 0)
		sched_signal_broadcast(&self->t_ibuf.rb_nempty);
	if ((old.c_lflag & ICANON) != 0 && (tio->c_lflag & ICANON) == 0)
		sched_signal_broadcast(&self->t_canon.lb_nful);
	if (((old.c_iflag & IXOFF) != 0 && (tio->c_iflag & IXOFF) == 0) || echo_disabled) {
		sched_signal_broadcast(&self->t_opend.lb_nful);
	} else if ((old.c_iflag & IXOFF) == 0 && (tio->c_iflag & IXOFF) != 0) {
		sched_signal_broadcast(&self->t_ioschange);
	}
	if (((old.c_iflag & __IIOFF) != 0 && (tio->c_iflag & __IIOFF) == 0) || echo_disabled)
		sched_signal_broadcast(&self->t_ipend.lb_nful);
	/* Given the caller the old TIO descriptor, if they requested it. */
	if (old_tio)
		memcpy(old_tio, &old, sizeof(old));
	return 0;
err:
	return error;
}

DEFINE_PUBLIC_ALIAS(terminal_init, libterminal_init);
DEFINE_PUBLIC_ALIAS(terminal_owrite, libterminal_owrite);
DEFINE_PUBLIC_ALIAS(terminal_iwrite, libterminal_iwrite);
DEFINE_PUBLIC_ALIAS(terminal_iread, libterminal_iread);
DEFINE_PUBLIC_ALIAS(terminal_setios, libterminal_setios);
DEFINE_PUBLIC_ALIAS(terminal_flush_icanon, libterminal_flush_icanon);

DECL_END

#endif /* !GUARD_LIBTERM_TERMIO_C */
