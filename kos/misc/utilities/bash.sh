#TEST: require_utility bash "$TARGET_SYSROOT/bin/bash"
# Copyright (c) 2019-2022 Griefer@Work
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgement (see the following) in the product
#    documentation is required:
#    Portions Copyright (c) 2019-2022 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

require_utility libncurses "$TARGET_SYSROOT/$TARGET_LIBPATH/libncursesw.so"
require_utility libreadline "$PKG_CONFIG_PATH/readline.pc"

PACKAGE_URL="https://ftp.gnu.org/gnu/bash/bash-5.1.16.tar.gz"
PACKAGE_NAME="bash-5.1.16"

CONFIGURE=(
	--enable-alias
	--enable-arith-for-command
	--enable-array-variables
	--enable-bang-history
	--enable-brace-expansion
	--enable-casemod-attributes
	--enable-casemod-expansions
	--enable-command-timing
	--enable-cond-command
	--enable-cond-regexp
	--enable-coprocesses
	--disable-dev-fd-stat-broken  # Nope: this isn't broken
	--enable-directory-stack
	--enable-disabled-builtins
	--enable-dparen-arithmetic
	--enable-extended-glob
	--enable-function-import
	--enable-glob-asciiranges-default
	--enable-help-builtin
	--enable-history
	--enable-job-control
	--enable-multibyte
	--disable-net-redirections
	--enable-process-substitution
	--enable-progcomp
	--enable-prompt-string-decoding
	--enable-readline
	--disable-restricted
	--enable-select
	--disable-separate-helpfiles
	--enable-single-help-strings
	--disable-mem-scramble
	--disable-profiling
	--disable-static-link
	--with-curses
	--without-bash-malloc
	--with-installed-readline
)

# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"


#TODO: Improve integration:
# checking for sys/pte.h... no
# checking for sys/stream.h... no
# checking for sys/ptem.h... no
# checking for _doprnt... no
# checking for __setostype... no
# checking for setdtablesize... no
# checking for regcomp... no
# checking for regexec... no
# checking for tzset... no
# checking for arc4random... no
# checking for libaudit.h... no
# checking whether AUDIT_USER_TTY is declared... no
# checking for mbstr.h... no
# checking for mbscasecmp... no
# checking for mbscmp... no
# checking for mbschr... no
# checking for bits16_t... no
# checking for u_bits16_t... no
# checking for bits32_t... no
# checking for u_bits32_t... no
# checking for bits64_t... no
