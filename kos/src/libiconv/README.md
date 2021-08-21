
### Q: Why are you hardcoding all of the codecs into a single library?

A: Because it's way more efficient, and before you get any wrong idea about how big this library is as a result, you should know that at the time of this being written, it's `582596` bytes (`569KiB`; which includes `.debug_info`) large (and sports support for `374` different codecs with `1502` different aliases). So no: this doesn't result in some insanely large data blobs, but rather a single very managable blob.

For comparison, glibc uses individual `*.so` files for every codec is supports (on my test Linux machine the're in `/usr/lib/i386-linux-gnu/gconv`). `ls | wc -l` tells me that there are `254`, and a quick glance at `ls -l` shows the smallest to be `9644` bytes large (though some go as far as `464188` bytes).

Nevertheless, assuming that they're all really small, let's do some quick maths: `9644 * 254 = 2449576`, which equates to `2.44MiB` of shared libraries (it's much more than that, but for now let's give the benefit of the doubt and work with the smallest values, especially since KOS's `374` codecs are mostly *simple* codecs)

Let's see what KOS needs per codec: `582596 / 374 = 1558` (rounded up)

<center>...</center>

I think you can see where I'm going with this: as per usual, glibc is anything but efficient or concerned about performance.

Now you might say: "but what about configurability?"  
To which I will say: "when was the last time you reconfigured your iconv database? Have you ever even heard about `iconvconfig(8)`? Because I'm not lying if I say I hadn't until I set off to write my own libiconv."

Now, the only reasonable argument there is against putting it all in one big library might be that loading it is an all-or-nothing kind-of deal, meaning that if you only need one of the many codecs, you still have to load all the rest. Now: that is a valid concern, but as I've shown above, this is not a very big library, so it doesn't take up *that* much of your address space.  
And finally, loading the library is fast for two reasons:

- Like all other KOS system library, this one's been written from scratch to minimize relocations (as usual, there are `0` `R_ARCH_RELATIVE` relocations, and only a hand full of `R_ARCH_JUMP_SLOT` relating to symbols exported from libc)
- Mapping the library into the address space uses lazy paging (s.a. `mmap(2)`, `sys_maplibrary(2)` and `libdl`), meaning that data is only loaded from disk if it's actally accessed, meaning that loading the library can be pretty much be thought of as an O(1) operation because it doesn't *really* get slower for larger data areas. (Even more so because there are so few relocations, and those that do exist only relate to a small hand full of pages (in this case: only a single page; namely the one containing `.rel.dyn` and `.rel.plt`), as opposed to say: all over `.data` as can be seen all too often throughout Linux programs \*sigh\*)

So as the end result, KOS is designed to work perfectly well with few large libraries, especially when compared to many small libraries. And unless we're talking libraries hundreds upon hundreds of megabytes in size, there's no point in trying to worry about how much of the address space is taken up at runtime.

Finally, if you still think that `569KiB` is too large for a library like this, you should really get over it and instead complain about how large `libc`'s already gotten (because at the time of this writing its `.so` is `2.6MiB` large; oops...)


A2: Alright, so there are *some* codecs so large that they would take up a significant portion of libiconv. So I've grouped them into separate sub-libraries that are lazily loaded when the associated codecs are first accessed. However, this is far from having one library for every supported codec!

