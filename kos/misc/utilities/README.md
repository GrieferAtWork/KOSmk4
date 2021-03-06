
## KOS source tree locations for utilities

- `/binutils`
	- `/binutils/misc`
		- Sysroot for 3rd programs needed for building KOS components
		- These programs are build to run on your own machine (i.e. not meant to be run by KOS)
		- `/binutils/misc/opt/$PACKAGE_NAME`
			- Intermediate out-of-source build files for packages installed in `$PROJPATH/binutils/misc`
			- These programs are build to run on your own machine (i.e. not meant to be run by KOS)
	- `/binutils/$TARGET_CPU-kos`
		- Sysroot for per-toolchain programs built for the host.
		- Most notably, the toolchain GCC can be found under `/binutils/$TARGET_CPU-kos/bin/gcc`
		- `/binutils/$TARGET_CPU-kos/opt/$PACKAGE_NAME`
			- Intermediate out-of-source build files for 3rd party utilities built for KOS
		- `/binutils/$TARGET_CPU-kos/opt/$PACKAGE_NAME-install`
			- Package distribution installation (if needed)
			- This contains a super-set of files from 3rd party programs that get installed on KOS disk images
	- `/binutils/src`
		- Source files and package archives for 3rd party programs
		- This folder is populated by `make_toolchain.sh` and `make_utility.sh`
- `/kos/misc`
	- `/kos/misc/utilities`
		- A collection of shell-scripts used to install 3rd party programs for execution under KOS
	- `/kos/misc/patches/$PACKAGE_NAME.patch`
		- Patches used by scripts in `/kos/misc/utilities`
		- Where used, these are applied to `/binutils/src/$PACKAGE_NAME`
- `/bin/$TARGET_CPU-kos-common`
	- Common folder for 3rd party utilities installed on-disk
	- Files installed here are (usually) copied from `/binutils/$TARGET_CPU-kos/opt/$PACKAGE_NAME-install`
- `/bin/$TARGET_CPU-kos-$CONFIG`
	- Mirror of files found on `/bin/$TARGET_CPU-kos-$CONFIG/disk.img`
	- Mostly consists of symbolic links to files in `/bin/$TARGET_CPU-kos-common`
	- Files who's representation depends on how KOS and its system libraries are configured are also found here
	- This is where files from 3rd party utilities & KOS system files are merged
- `/bin/$TARGET_CPU-kos-$CONFIG/disk.img`
	- The actual (FAT) disk image with which KOS is booted


As such, when you install a 3rd party package, it will go through the following steps:
- `/kos/misc/utilities/my_utility.sh`: Your package's install script (called by `make_utility.sh`)
- `/binutils/src/my_utility-1.0.tar.gz`: downloaded from `https://my_url.com/my_utility-1.0.tar.gr`
- `/binutils/src/my_utility-1.0`: unpacked from the downloaded file
- `/binutils/src/my_utility-1.0/configure`: configure (using tools from the KOS toolchain)
- `/binutils/$TARGET_CPU-kos/opt/my_utility-1.0`: Output path for build files (pwd when `configure` is called)
- `/binutils/$TARGET_CPU-kos/opt/my_utility-1.0/Makefile`: Build the package (via `make`)
- `/binutils/$TARGET_CPU-kos/opt/my_utility-1.0-install`: Install the package (via `make DESTDIR=... install`)
- `/bin/$TARGET_CPU-kos-common`: Copy relevant files from the previous step here
- `/bin/$TARGET_CPU-kos-$CONFIG`: Create symbolic links to `$TARGET_CPU-kos-common`
- `/bin/$TARGET_CPU-kos-$CONFIG/disk.img`: Copy files onto KOS disk images (via `mcopy`)
The last 2 steps are performed for every `$CONFIG`-folder that can be located



<a name="X-server"></a>
## Experimental utilities for X-server support:

### Ported

- [libdrm-2.4.100](https://dri.freedesktop.org/libdrm/)
- [libfreetype2-2.10.2](https://www.freetype.org/)
- [libpixman-0.40.0](http://pixman.org/)
- [fontconfig-2.13.92](https://www.freedesktop.org/software/fontconfig/release/fontconfig-2.13.92.tar.gz)
- Xorg
	- [libfontenc-1.1.4](https://www.x.org/releases/individual/lib/libfontenc-1.1.4.tar.gz)
	- [libX11-1.6.12](https://www.x.org/releases/individual/lib/libX11-1.6.12.tar.gz)
	- [libXau-1.0.9](https://www.x.org/releases/individual/lib/libXau-1.0.9.tar.gz)
	- [libxcb-1.14](https://www.x.org/releases/individual/lib/libxcb-1.14.tar.gz)
	- [libXfont2-2.0.4](https://www.x.org/releases/individual/lib/libXfont2-2.0.4.tar.gz)
	- [libxkbfile-1.1.0](https://www.x.org/releases/individual/lib/libxkbfile-1.1.0.tar.gz)
	- [xorgproto-2020.1](https://www.x.org/releases/individual/proto/xorgproto-2020.1.tar.gz)
	- [xtrans-1.4.0](https://www.x.org/releases/individual/proto/xtrans-1.4.0.tar.gz)
	- [xcb-proto-1.14.1](https://www.x.org/releases/individual/proto/xcb-proto-1.14.1.tar.gz)
	- [xkbcomp-1.4.3](https://www.x.org/releases/individual/app/xkbcomp-1.4.3.tar.gz)
	- [xkeyboard-config-2.31](https://www.x.org/releases/individual/data/xkeyboard-config/xkeyboard-config-2.31.tar.gz)
	- [xorg-server-1.20.9](https://www.x.org/releases/individual/xserver/xorg-server-1.20.9.tar.gz)
	- [xf86-video-vesa-2.5.0](https://www.x.org/releases/individual/driver/xf86-video-vesa-2.5.0.tar.gz)
	- [libICE-1.0.10](https://www.x.org/releases/individual/lib/libICE-1.0.10.tar.gz)
	- [libSM-1.2.3](https://www.x.org/releases/individual/lib/libSM-1.2.3.tar.gz)
	- [libXaw-1.0.13](https://www.x.org/releases/individual/lib/libXaw-1.0.13.tar.gz)
	- [libXext-1.3.4](https://www.x.org/releases/individual/lib/libXext-1.3.4.tar.gz)
	- [libXmu-1.1.3](https://www.x.org/releases/individual/lib/libXmu-1.1.3.tar.gz)
	- [libXpm-3.5.13](https://www.x.org/releases/individual/lib/libXpm-3.5.13.tar.gz)
	- [libXt-1.2.0](https://www.x.org/releases/individual/lib/libXt-1.2.0.tar.gz)
	- [libXrender-0.9.10](https://www.x.org/releases/individual/lib/libXrender-0.9.10.tar.gz)
	- [libXft-2.3.3](https://www.x.org/releases/individual/lib/libXft-2.3.3.tar.gz)
	- [xclock-1.0.9](https://www.x.org/releases/individual/app/xclock-1.0.9.tar.gz)
	- [xinit-1.4.1](https://www.x.org/releases/individual/app/xinit-1.4.1.tar.gz)


### Invocation

From inside of KOS, run the following:

```sh
xinit /bin/xclock -- -dumbSched
```

And after a while you should see this:

![Xorg-first-time.png](../gallery/Xorg-first-time.png)
