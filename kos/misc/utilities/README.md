
<a name="X-server"></a>
## Experimental utilities for X-server support:

### Invocation

From inside of KOS, run the following:

```sh
xinit /bin/xclock -- -dumbSched
```


### TODO

The X-server currently fails to start because of:

```
[trace ][6] sys_epoll_create1(flags: 524288)
[trace ][6][except] Translate exception 0x8:0x0[0x8101,0x20,0x80000] into errno=-38
```

Which is because KOS has yet to implement that system call.


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

