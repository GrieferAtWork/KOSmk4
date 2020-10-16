
<a name="X-server"></a>
## Experimental utilities for X-server support:

### Invocation

From inside of KOS, run the following:

```sh
xinit /bin/twm -- -dumbSched
```


### Status

twm crashes because of a bug with how `_XkbReadKeySyms()` calls `_XkbReadBufferCopyKeySyms`.

The line

```c
[182] if (offset+newMap->nSyms>=map->size_syms) {
```

should instead be

```c
[182] while (offset+newMap->nSyms>=map->size_syms) {
```

Or possibly be re-written entirely, as I'm not quite sure if that change would actually preserve logic, but as it stands, the following causes a crash:

```c
[196] _XkbReadBufferCopyKeySyms(buf,(KeySym *)&map->syms[offset],
[197]                          newMap->nSyms);
```

Because at this point, `offset...+=newMap->nSyms` may lie outside of the allocated map range, which only gets incremented statically, but may leave the map to small for the actually used offset:

```c
[186] sz= map->size_syms+128;
[187] map->syms= _XkbTypedRealloc(map->syms,sz,KeySym);
```

Here's a snapshot of the values of local variables I've generated with KOS's builtin debugger

```c
buf   : (XkbReadBufferPtr)0x3BFADD80
xkb   : (XkbDescPtr)0x10022380
rep   : (xkbGetMapReply *)0x3BFADDC8
i     : (int)224
map   : (XkbClientMapPtr)0x100223B0
offset: (int)4379
oldMap: (XkbSymMapPtr)0x10037750
newMap: (xkbSymMapWireDesc *)0x10027008
```

And here's a full traceback

```
/kos/binutils/src/x/libX11-1.5.0/src/xkb/XKBRdBuf.c(84,9) : 0CE1C88F+3[/lib/libX11.so.6][_XkbReadCopyKeySyms+36]
/kos/binutils/src/x/libX11-1.5.0/src/xkb/XKBRdBuf.c(94,5) : 0CE1C8F4+5[/lib/libX11.so.6][_XkbReadBufferCopyKeySyms+78]
/kos/binutils/src/x/libX11-1.5.0/src/xkb/XKBGetMap.c(196,3) : 0CE17E90+5[/lib/libX11.so.6][_XkbReadKeySyms+600]
/kos/binutils/src/x/libX11-1.5.0/src/xkb/XKBGetMap.c(489,11) : 0CE1899F+5[/lib/libX11.so.6][_XkbReadGetMapReply+353]
/kos/binutils/src/x/libX11-1.5.0/src/xkb/XKBGetMap.c(521,12) : 0CE18ADC+5[/lib/libX11.so.6][_XkbHandleGetMapReply+60]
/kos/binutils/src/x/libX11-1.5.0/src/xkb/XKBGetMap.c(538,10) : 0CE18B89+5[/lib/libX11.so.6][XkbGetUpdatedMap+160]
/kos/binutils/src/x/libX11-1.5.0/src/xkb/XKBGetMap.c(557,17) : 0CE18C4F+5[/lib/libX11.so.6][XkbGetMap+109]
/kos/binutils/src/x/libX11-1.5.0/src/xkb/XKBBind.c(504,12) : 0CE15688+5[/lib/libX11.so.6][_XkbLoadDpy+83]
/kos/binutils/src/x/libX11-1.5.0/src/xkb/XKBBind.c(222,9) : 0CE14C6E+5[/lib/libX11.so.6][XLookupKeysym+79]
/kos/binutils/src/x/twm-1.0.7/src/events.c(593,10) : 0804F443+5[/bin/twm][HandleKeyPress+336]
/kos/binutils/src/x/twm-1.0.7/src/events.c(321,3) : 0804EE29+2[/bin/twm][DispatchEvent+203]
/kos/binutils/src/x/twm-1.0.7/src/events.c(350,13) : 0804EEE4+5[/bin/twm][HandleEvents+178]
/kos/binutils/src/x/twm-1.0.7/src/twm.c(678,5) : 08062B6F+5[/bin/twm][main+4989]
/kos/kos/src/crt0/i386/crt0_32.S(39) : 0804B149+5[/bin/twm][_start+9]
```


### Status

Scrap all of the Xorg stuff already ported, and start from srcatch, using the most recent versions of everything.

Just to explain myself, when I started porting Xorg, I read something about issues with how newer versions are supposedly licensed, but I miss-understood some stuff, and I was always free to just port the most recent version. The blocker above has (likely) been fixed a long time ago, and who's to say that there aren't a bunch of similar bugs.

So rather than trying to fix age-old, outdated software, I think it's best to just admit my losses and start over with the most recent stuff.

Sources for recent releases can all be found here: https://www.x.org/releases/individual/


### Ported

- [libdrm-2.4.82](https://github.com/freedreno/libdrm/archive)
- [libfreetype2-2.10.2](https://www.freetype.org/)
- [libpixman-0.40.0](http://pixman.org/)
- Xorg (old)
	- [xtrans-1.2.7](https://www.x.org/releases/X11R7.7/src/lib)
	- [libfontenc-1.1.1](https://www.x.org/releases/X11R7.7/src/everything)
	- [xproto-7.0.23](https://www.x.org/releases/X11R7.7/src/everything)
	- [fontsproto-2.1.2](https://www.x.org/releases/X11R7.7/src/everything)
	- [libXfont-1.4.5](https://www.x.org/releases/X11R7.7/src/everything)
	- [xextproto-7.2.1](https://www.x.org/releases/X11R7.7/src/everything)
	- [kbproto-1.0.6](https://www.x.org/releases/X11R7.7/src/everything)
	- [inputproto-2.2](https://www.x.org/releases/X11R7.7/src/everything)
	- [libXau-1.0.7](https://www.x.org/releases/X11R7.7/src/everything)
	- [libxcb-1.8.1](https://www.x.org/releases/X11R7.7/src/everything)
	- [xf86bigfontproto-1.2.0](https://www.x.org/releases/X11R7.7/src/everything)
	- [libX11-1.5.0](https://www.x.org/releases/X11R7.7/src/everything)
	- [glproto-1.4.15](https://www.x.org/releases/X11R7.7/src/everything)
	- [xf86driproto-2.1.1](https://www.x.org/releases/X11R7.7/src/everything)
	- [fixesproto-5.0](https://www.x.org/releases/X11R7.7/src/everything)
	- [damageproto-1.2.1](https://www.x.org/releases/X11R7.7/src/everything)
	- [xcmiscproto-1.2.2](https://www.x.org/releases/X11R7.7/src/everything)
	- [bigreqsproto-1.1.2](https://www.x.org/releases/X11R7.7/src/everything)
	- [randrproto-1.3.2](https://www.x.org/releases/X11R7.7/src/everything)
	- [renderproto-0.11.1](https://www.x.org/releases/X11R7.7/src/everything)
	- [videoproto-2.3.1](https://www.x.org/releases/X11R7.7/src/everything)
	- [compositeproto-0.4.2](https://www.x.org/releases/X11R7.7/src/everything)
	- [recordproto-1.14.2](https://www.x.org/releases/X11R7.7/src/everything)
	- [scrnsaverproto-1.2.2](https://www.x.org/releases/X11R7.7/src/everything)
	- [resourceproto-1.2.0](https://www.x.org/releases/X11R7.7/src/everything)
	- [libxkbfile-1.0.8](https://www.x.org/releases/X11R7.7/src/everything)
	- [xf86vidmodeproto-2.3.1](https://www.x.org/releases/X11R7.7/src/everything)
	- [xf86dgaproto-2.1](https://www.x.org/releases/X11R7.7/src/everything)
	- [libXext-1.3.1](https://www.x.org/releases/X11R7.7/src/everything)
	- [libXxf86dga-1.1.3](https://www.x.org/releases/X11R7.7/src/everything)
	- [xorg-server-1.12.2](https://www.x.org/releases/X11R7.7/src/everything)
	- [xf86-video-vesa-2.3.1](https://www.x.org/releases/X11R7.7/src/everything)
	- [xkbcomp-1.2.4](https://www.x.org/releases/X11R7.7/src/everything)
	- [xkeyboard-config-2.6](https://www.x.org/releases/X11R7.7/src/everything)
	- [xf86-input-keyboard-1.6.1](https://www.x.org/releases/X11R7.7/src/everything)
	- [libICE-1.0.8](https://www.x.org/releases/X11R7.7/src/everything)
	- [libSM-1.2.1](https://www.x.org/releases/X11R7.7/src/everything)
	- [libXt-1.1.3](https://www.x.org/releases/X11R7.7/src/everything)
	- [libXmu-1.1.1](https://www.x.org/releases/X11R7.7/src/everything)
	- [xinit-1.3.2](https://www.x.org/archive//individual/app)
	- [twm-1.0.7](https://www.x.org/archive//individual/app)
- Xorg (new)
	- [libfontenc-1.1.4](https://www.x.org/releases/individual/lib/libfontenc-1.1.4.tar.gz)
	- [libX11-1.6.12](https://www.x.org/releases/individual/lib/libX11-1.6.12.tar.gz)
	- [libXau-1.0.9](https://www.x.org/releases/individual/lib/libXau-1.0.9.tar.gz)
	- [libxcb-1.14](https://www.x.org/releases/individual/lib/libxcb-1.14.tar.gz)
	- [libXfont2-2.0.4](https://www.x.org/releases/individual/lib/libXfont2-2.0.4.tar.gz)
	- [libxkbfile-1.1.0](https://www.x.org/releases/individual/lib/libxkbfile-1.1.0.tar.gz)
	- [bigreqsproto-1.1.2](https://www.x.org/releases/individual/proto/bigreqsproto-1.1.2.tar.gz)
	- [compositeproto-0.4.2](https://www.x.org/releases/individual/proto/compositeproto-0.4.2.tar.gz)
	- [damageproto-1.2.1](https://www.x.org/releases/individual/proto/damageproto-1.2.1.tar.gz)
	- [fixesproto-5.0](https://www.x.org/releases/individual/proto/fixesproto-5.0.tar.gz)
	- [fontsproto-2.1.3](https://www.x.org/releases/individual/proto/fontsproto-2.1.3.tar.gz)
	- [inputproto-2.3.2](https://www.x.org/releases/individual/proto/inputproto-2.3.2.tar.gz)
	- [kbproto-1.0.7](https://www.x.org/releases/individual/proto/kbproto-1.0.7.tar.gz)
	- [presentproto-1.1](https://www.x.org/releases/individual/proto/presentproto-1.1.tar.gz)
	- [randrproto-1.5.0](https://www.x.org/releases/individual/proto/randrproto-1.5.0.tar.gz)
	- [recordproto-1.14.2](https://www.x.org/releases/individual/proto/recordproto-1.14.2.tar.gz)
	- [renderproto-0.11.1](https://www.x.org/releases/individual/proto/renderproto-0.11.1.tar.gz)
	- [resourceproto-1.2.0](https://www.x.org/releases/individual/proto/resourceproto-1.2.0.tar.gz)
	- [scrnsaverproto-1.2.2](https://www.x.org/releases/individual/proto/scrnsaverproto-1.2.2.tar.gz)
	- [videoproto-2.3.3](https://www.x.org/releases/individual/proto/videoproto-2.3.3.tar.gz)
	- [xcmiscproto-1.2.2](https://www.x.org/releases/individual/proto/xcmiscproto-1.2.2.tar.gz)
	- [xextproto-7.3.0](https://www.x.org/releases/individual/proto/xextproto-7.3.0.tar.gz)
	- [xf86bigfontproto-1.2.0](https://www.x.org/releases/individual/proto/xf86bigfontproto-1.2.0.tar.gz)
	- [xf86dgaproto-2.1](https://www.x.org/releases/individual/proto/xf86dgaproto-2.1.tar.gz)
	- [xf86vidmodeproto-2.3.1](https://www.x.org/releases/individual/proto/xf86vidmodeproto-2.3.1.tar.gz)
	- [xproto-7.0.31](https://www.x.org/releases/individual/proto/xproto-7.0.31.tar.gz)
	- [xtrans-1.4.0](https://www.x.org/releases/individual/proto/xtrans-1.4.0.tar.gz)
	- [xcb-proto-1.14.1](https://www.x.org/releases/individual/proto/xcb-proto-1.14.1.tar.gz)
	- [xf86-video-vesa-2.5.0](https://www.x.org/releases/individual/driver/xf86-video-vesa-2.5.0.tar.gz)
	- [xkbcomp-1.4.3](https://www.x.org/releases/individual/app/xkbcomp-1.4.3.tar.gz)
	- [xkeyboard-config-2.31](https://www.x.org/releases/individual/data/xkeyboard-config/xkeyboard-config-2.31.tar.gz)
