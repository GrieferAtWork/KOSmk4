## Video System Components

The KOS video system is based on various layers of control structures and operator V-tables that are all built on-top of each other, such that any arbitrary low-level component is able to override operators for higher-level components (to provide special-purpose optimizations).


### Driver

Library: `libvideo-driver.so`

---

> struct video_adapter: video_domain { ... };

Enumerate `video_monitor`s and provide a driver-specific domain allocator for video buffers (if possible, these are then set-up to directly use V-RAM, as well as provide hardware GFX operators)

> struct video_monitor: video_display { ... };

Top-level video_monitor:
- Set resolution
- Get LFB (linear frame buffer) as `video_buffer` (via video_display)
- Indicate to driver that LFB region was changed (via video_display)

---



### Compositor

Library: `libvideo-compositor.so`

---

> struct video_window: video_display { ... };

Description for a window within a compositor
- Get LFB as `video_buffer` (via video_display)
- Indicate to compositor that LFB region was changed (via video_display)

---



### Gfx

Library: `libvideo-gfx.so`

---

> struct video_domain { ... };

Allocator for `struct video_buffer`
- Default domain is provided by `video_ramdomain()`

---

> struct video_display { ... };

Abstraction between `video_monitor` and `video_window`:
- Get LFB as `video_buffer`
- LFB might changes when:
	- Resolution of `video_monitor` is changed
	- A `video_window` is resized, moved, becomes overlapped, ...
- Indicate that LFB region was changed

> struct video_format { };

Combination of `struct video_codec` ([1..1]) and `struct video_palette` ([0..1])

---

> struct video_codec { ... };

Descriptor for a pixel- and color format:
- Convert between `video_pixel_t` and `video_color_t`
- Do low-level pixel I/O on memory obtained through `video_lock` / `video_lockregion`:
	- Functions to get/set singular pixels
	- Functions to do horizontal/vertical/area fills
	- Functions to do area copies
- NOT reference-counted by default (except when dynamically created)
- Lots of built-in codecs for common formats
- Custom codecs can be constructed from 

---

> struct video_palette { ... };

Descriptor for color conversion of palette-based video codecs:
- Can be optimized for fast (`O(log N)`) color → pixel conversion
- Reference-counted, read-only (after creation)

---

> struct video_buffer { ... };

Descriptor for a 2D pixel plane:
- Tracks pixel format (video_codec)
- Tracks palettes (video_palette)
- Allows locking (sub-regions of) pixel data into memory (`video_lock`, `video_lockregion`)
- Allows creation of GFX contexts for rendering/blitting (`video_gfx`)
- Comes with various different forms
- Can easily be saved/loaded from on-disk files (video_buffer_load(), video_buffer_save())

---

> struct video_lock { ... };
> struct video_lockregion { ... };

Descriptors for video locks created for `video_buffer`

---

> struct video_gfx { ... };

Descriptor for a video graphics context
- Offers a big API for doing render operations
- Can be implemented via different backends (selected by linked `video_buffer`)
- Configurable support for clip rects, virtual rotation, ...
- Configurable color blending (e.g. alpha-blending)
- NOT reference-counted, NO finalizer, created on-demand and usually stored on-stack
	- State-full wrapper around linked `video_buffer`

---
