#TEST: require_utility - "$SYSROOT_BIN_TARGET_COMMON/bin/-"
# Copyright (c) 2019-2023 Griefer@Work
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
#    Portions Copyright (c) 2019-2023 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

require_utility libncurses "$SYSROOT_BIN_TARGET_COMMON/$TARGET_LIBPATH/libncursesw.so"
require_utility openssl    "$PKG_CONFIG_PATH/openssl.pc"

# bsd-games is-working status:
#    adventure(1):    Prints "Invalid data section number: -88", followed by jumbled garbage
#    arithmetic(1):   Works
#    backgammon(1):   Works               -- Though I don't know how to play that game
#    banner(1):       Works
#    battlestart(1):  Works
#    bcd(1):          Works
#    caesar(1):       Works
#    canfield(1):     Works
#    cfscores(1):     "You are not listed in the password file?!?"
#                     >> yeah... maybe implement /etc/passwd?
#                     Related: `whoami` --> "whoami: unknown uid 0"
#    countmail(1):    Shell-script (appears broken; probably due to busybox)
#    cribbage(1):     Works               -- Though I don't know how to play that game
#    dab(1):          Spams the system log with "Unimplemented function called: `lrand48()'"
#    dm(1):           TODO: Investigate
#    factor(1):       Works
#    fortune(1):      Works
#    go-fish(1):      Works
#    gomoku(1):       Works               -- Though I don't know how to play that game
#    hack(1):         Uses hard-links, which FAT doesn't support (TODO: re-try in a ramfs setting)
#    hangman(1):      "hangman: fopen /usr/share/dict/words: No such file or directory"
#    hunt(1):         "hunt: Can't find myself."
#    huntd(1):        ... (I think this is a server?)
#    mille(1):        Works               -- Though I don't know how to play that game
#    monop(1):        Works
#    morse(1):        Works
#    number(1):       Works
#    phantasia(1):    Coredumps immediately
#    pig(1):          Works
#    pom(1):          Works
#    ppt(1):          Works
#    primes(1):       Works
#    quiz(1):         Works
#    rain(1):         Works
#    random(1):       Works
#    robots(1):       Works               -- Though I don't know how to play that game
#    rot13(1):        Works
#    sail(1):         "sail: syncfile: No such file or directory"
#    snake(1):        Works
#    snscores(1):     "No scores recorded yet!" (even after running and playing snake(1))
#    teachgammon(1):  Works               -- But I'm not sitting through all that!
#    tetris-bsd(1):   Works               -- But I like vitetris more -- this one w/o colors :(
#    trek(1):         "What length game:" -- No matter what's typed, prints "invalid input"
#    wargames(1):     Works               -- (kind-of, but it's a shell-script, so not my fault if it doesn't)
#    worm(1):         Time doesn't move unless you do (sys_alarm() --> Translate exception 0x8:0x0,E_UNKNOWN_SYSTEMCALL[0x8101,0x20] into errno=-ENOSYS)
#    worms(1):        Works               -- perfectly (lol! This one looks so cool)
#    wtf(1):          Doesn't appear to be working, but is a shell script so probably busybox's fault
#    wump(1):         Works



SRCPATH="$KOS_ROOT/binutils/src/bsdgames-git"
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/bsdgames"
DESTDIR="$SYSROOT_BINUTILS_TARGET/opt/bsdgames-install"

# Not tested if working w/o, but here for safety
. "$KOS_MISC/utilities/misc/gcc_hack.sh"

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -d "$DESTDIR" ]; then
	if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/_didmake" ]; then
		if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/GNUmakefile" ]; then
			if ! [ -f "$SRCPATH/configure" ]; then
				# https://stackoverflow.com/questions/3489173/how-to-clone-git-repository-with-specific-revision-changeset
				rm -rf "$SRCPATH" > /dev/null 2>&1
				cmd mkdir -p "$SRCPATH"
				cmd cd "$SRCPATH"
				cmd git init
				cmd git remote add origin "https://github.com/vattam/BSDGames.git"
				cmd git fetch origin "56b8944332186891cd5c0094bd3991e3c5f5a799"
				cmd git reset --hard FETCH_HEAD
				rm -rf "$SRCPATH/.git" > /dev/null 2>&1
			fi

			# Trying to do an out-of-source configure leads to errors, so
			# we create a full copy of the source folder for configure!
			rm -rf "$OPTPATH" > /dev/null 2>&1
			cmd cp -R "$SRCPATH" "$OPTPATH"
			cmd cd "$OPTPATH"

			# Configure parameters
			cmd cat > "./config.params" <<EOF
bsd_games_cfg_non_interactive=y
# atc:    needs bison + flex
# boggle: wants some word list to compile (guessing it doesn't ship its own levels, so-to-say...)
bsd_games_cfg_no_build_dirs="atc boggle"
bsd_games_cfg_install_prefix="$DESTDIR-temp"
bsd_games_cfg_gamesdir="/usr/bin"
bsd_games_cfg_sbindir="/usr/bin"
bsd_games_cfg_usrbindir="/usr/bin"
bsd_games_cfg_use_dm=n
bsd_games_cfg_man5dir="/usr/share/man/man5"
bsd_games_cfg_man6dir="/usr/share/man/man6"
bsd_games_cfg_man8dir="/usr/share/man/man8"
bsd_games_cfg_docdir="/usr/share/doc/bsd-games"
bsd_games_cfg_sharedir="/usr/share/games"
bsd_games_cfg_varlibdir="/var/games"
bsd_games_cfg_do_chown=n
bsd_games_cfg_use_dot_so=.so
bsd_games_cfg_gzip_manpages=n
bsd_games_cfg_cc="${CROSS_PREFIX}gcc"
bsd_games_cfg_cxx="${CROSS_PREFIX}g++"
bsd_games_cfg_optimize_flags="-g -O2"
bsd_games_cfg_warning_flags="-Wall -Wstrict-prototypes -Wmissing-prototypes -Wpointer-arith -Wcast-align -Wcast-qual -Wwrite-strings"
bsd_games_cfg_ncurses_lib="-lncurses"
bsd_games_cfg_use_libcrypto=y
bsd_games_cfg_openssl_lib="-lcrypto"
bsd_games_cfg_other_cflags=
bsd_games_cfg_other_ldflags=
bsd_games_cfg_pager=/bin/less
bsd_games_cfg_offensive_fortunes=y
bsd_games_cfg_sail_dir="/var/games/sail"
bsd_games_cfg_atc_dir="/usr/share/games/atc"
bsd_games_cfg_atc_scorefile="/var/games/atc_score"
bsd_games_cfg_battlestar_scorefile="/var/games/battlestar.log"
bsd_games_cfg_dictionary_src="/usr/share/dict/words"
bsd_games_cfg_boggle_dir="/usr/share/games/boggle"
bsd_games_cfg_canfield_scorefile="/var/games/cfscores"
bsd_games_cfg_cribbage_instrfile="/usr/share/games/cribbage.instr"
bsd_games_cfg_cribbage_scorefile="/var/games/criblog"
bsd_games_cfg_dm_configfile=/etc/dm.conf
bsd_games_cfg_dm_nogamesfile=/etc/nogames
bsd_games_cfg_dm_logfile="/var/games/games.log"
bsd_games_cfg_fish_instrfile="/usr/share/games/fish.instr"
bsd_games_cfg_fortune_dir="/usr/share/games/fortune"
bsd_games_cfg_hack_dir="/var/games/hack"
bsd_games_cfg_hangman_wordsfile=/usr/share/dict/words
bsd_games_cfg_monop_cardsfile="/usr/share/games/monop-cards.pck"
bsd_games_cfg_phantasia_dir="/var/games/phantasia"
bsd_games_cfg_quiz_dir="/usr/share/games/quiz"
bsd_games_cfg_robots_scorefile="/var/games/robots_roll"
bsd_games_cfg_rogue_scorefile="/var/games/rogue.scores"
bsd_games_cfg_sail_scorefile="/var/games/saillog"
bsd_games_cfg_snake_scorefile="/var/games/snake.log"
bsd_games_cfg_snake_rawscorefile="/var/games/snakerawscores"
bsd_games_cfg_tetris_scorefile="/var/games/tetris-bsd.scores"
bsd_games_cfg_wtf_acronymfile="/usr/share/misc/acronyms"
bsd_games_cfg_wump_infofile="/usr/share/games/wump.info"
EOF
			"$SH" "$OPTPATH/configure"
		fi

		if ! [ -f "$OPTPATH/.kos_patched" ]; then
			cmd cd "$OPTPATH"
			insert_line_top() {
				local text="$(cat "$1")"
				if ! [[ "$text" == "$2"* ]]; then
					echo "Insert line '$2' at top of '$1'"
					text="$2
$text"
					echo "$text" > "$1"
				fi
			}

			# Fix some missing includes (which probably worked on BSD due to cross-includes in system headers)
			insert_line_top "banner/banner.c"   "#include <sys/types.h>"
			insert_line_top "dm/dm.c"           "#include <fcntl.h>"
			insert_line_top "wump/wump.c"       "#include <fcntl.h>"

			fix_getline() {
				cmd sed -i 's/\bgetline\b/bsdgames_getline/g' "$1"
			}

			# Fix "getline()" function definitions conflicting with libc's getline(3)
			fix_getline boggle/boggle/bog.c
			fix_getline boggle/boggle/extern.h
			fix_getline boggle/boggle/mach.c
			fix_getline cribbage/crib.c
			fix_getline cribbage/cribbage.h
			fix_getline cribbage/io.c
			fix_getline gomoku/bdisp.c
			fix_getline gomoku/gomoku.h
			fix_getline gomoku/main.c

			:> "$OPTPATH/.kos_patched"
		fi

		# A couple of programs need to be built for the build machine (since they're
		# used to generate additional input files). However, the shipped makefile
		# doesn't understand that and tries to execute KOS binaries directly.
		#
		# Work around this issue by building all of those files using the actual host
		# CC before-the-fact, so that the "make" below won't try to build them wrongly

		cmd cd "$OPTPATH"
		cmd rm -f "phantasia/host_phantglobs.c"
		cmd ln -s "phantglobs.c" "phantasia/host_phantglobs.c"
		HOST_CC_COMMANDS=(
			"adventure/setup"
			"hack/makedefs"
			"monop/initdeck"
			"phantasia/host_phantglobs"
			"phantasia/setup"
			"fortune/strfile/strfile"
		)
		for file in "${HOST_CC_COMMANDS[@]}"; do
			if ! [ -f "$file.o" ]; then
				echo "Run: gcc -c -o $file.o $file.c"
				cmd gcc -c -o "$file.o" "$file.c" &
			fi
		done
		cmd wait
		[ -f "adventure/setup"         ] || { cmd gcc -o adventure/setup adventure/setup.o & }
		[ -f "hack/makedefs"           ] || { cmd gcc -o hack/makedefs hack/makedefs.o & }
		[ -f "monop/initdeck"          ] || { cmd gcc -o monop/initdeck monop/initdeck.o & }
		[ -f "phantasia/setup"         ] || { cmd gcc -o phantasia/setup phantasia/host_phantglobs.o phantasia/setup.o & }
		[ -f "fortune/strfile/strfile" ] || { cmd gcc -o fortune/strfile/strfile fortune/strfile/strfile.o & }
		cmd wait

		cmd cd "$OPTPATH"
		# XXX: For some reason, make fails the first time around (running it again seems to fix it?)
		make -j "$MAKE_PARALLEL_COUNT" || cmd make -j "$MAKE_PARALLEL_COUNT"
		> "$OPTPATH/_didmake"
	fi # Make
	rm -rf "$DESTDIR" > /dev/null 2>&1
	rm -rf "$DESTDIR-temp" > /dev/null 2>&1
	cmd cd "$OPTPATH"
	cmd make install -j "$MAKE_PARALLEL_COUNT"
	cmd mv "$DESTDIR-temp" "$DESTDIR"
fi # Install

# Don't install these files
INSTALL_SKIP="
/usr/bin/strfile.exe
/usr/bin/strfile
/usr/share/doc
/usr/share/man
"

# Install to disk
. "$KOS_MISC/utilities/misc/install-DESTDIR.sh"
