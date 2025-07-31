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
#ifndef GUARD_LIBVIDEO_DRIVER_ADAPTER_SVGA_H
#define GUARD_LIBVIDEO_DRIVER_ADAPTER_SVGA_H 1

#include "../api.h"
/**/

#ifdef HAVE_SVGA_ADAPTER
#include <hybrid/compiler.h>

#include <kos/aref.h>
#include <kos/sched/shared-lock.h>
#include <kos/types.h>

#include <libphys/phys.h>
#include <libsvgadrv/chipset.h>
#include <libvideo/driver/adapter.h>
#include <libvideo/driver/monitor.h>
#include <libvideo/gfx/buffer/rambuffer.h>

DECL_BEGIN

struct svga_adapter;
struct svga_buffer;
AXREF(svga_buffer_axref, svga_buffer);

struct svga_buffer: video_rambuffer {
	/* NOTE: The buffer described here is owned and must be unmapped using `:sva_libphys_unmap' */
	size_t                  svb_rb_total; /* [const] Total buffer size */
	struct video_buffer_ops svb_ops;      /* [const] Operator table. */
};
#define svga_buffer_getadapter(self) \
	video_domain_assvga(video_buffer_getdomain(self))
#define video_buffer_assvga(self) ((struct svga_buffer *)(self))

struct svga_monitor: video_monitor {
};
#define video_monitor_assvga(self) ((struct svga_monitor *)(self))
#define video_display_assvga(self) ((struct svga_monitor *)(self))

#if 1
#define svga_monitor_getadapter(self) \
	COMPILER_CONTAINER_OF(self, struct svga_adapter, sva_monitor)
#else
#define svga_monitor_getadapter(self) \
	video_adapter_assvga(video_monitor_getadapter(self))
#endif

struct svga_adapter: video_adapter {
	struct video_adapter_ops          sva_adapter_ops;   /* [const] Adapter operator table */
	struct svga_monitor               sva_monitor;       /* [1..1][const] The one-and-only SVGA monitor */
	struct video_monitor_ops          sva_monitor_ops;   /* [const] Monitor operator table */
	fd_t                              sva_vdlck;         /* [const] Video lock file for /dev/svga */
	void                             *sva_libphys;       /* [1..1][const] Handle for libphys */
	PMMAPPHYS                         sva_libphys_map;   /* [1..1][const] Helper to map physical memory */
	PMUNMAPPHYS                       sva_libphys_unmap; /* [1..1][const] Helper to unmap physical memory */
	void                             *sva_libsvgadrv;    /* [1..1][const] Handle for libsvgadrv */
	struct svga_chipset_driver const *sva_drv;           /* [1..1][const] SVGA driver */
#define svga_adapter_modeset(self) ((self)->sva_modeinfo != NULL)
	struct svga_modeinfo             *sva_modeinfo;      /* [0..1][lock(sva_cslock)] Descriptor for currently active video mode ("NULL" means that no mode has been set, yet) */
	struct video_monitor_mode         sva_mode;          /* [valid_if(sva_modeinfo != NULL)][lock(sva_cslock)] Currently active video mode */
	struct svga_buffer_axref          sva_buffer;        /* [0..1][lock(READ(ATOMIC), WRITE(ATOMIC && sva_cslock))] Display buffer (or "NULL" if not allocated or display mode was just set) */
	struct shared_lock                sva_cslock;        /* Lock for interfacing with `sva_cs' */
	struct svga_chipset               sva_cs;            /* SVGA chipset (flexible-length, so must be last field) */
};
#define video_domain_assvga(self)  ((struct svga_adapter *)(self))
#define video_adapter_assvga(self) ((struct svga_adapter *)(self))

#define _svga_adapter_cs_reap(self)      (void)0
#define svga_adapter_cs_reap(self)       (void)0
#define svga_adapter_cs_mustreap(self)   0
#define svga_adapter_cs_tryacquire(self) shared_lock_tryacquire(&(self)->sva_cslock)
#define svga_adapter_cs_acquire(self)    shared_lock_acquire(&(self)->sva_cslock)
#define svga_adapter_cs_acquire_nx(self) shared_lock_acquire_nx(&(self)->sva_cslock)
#define _svga_adapter_cs_release(self)   shared_lock_release(&(self)->sva_cslock)
#define svga_adapter_cs_release(self)    (shared_lock_release(&(self)->sva_cslock), svga_adapter_cs_reap(self))
#define svga_adapter_cs_acquired(self)   shared_lock_acquired(&(self)->sva_cslock)
#define svga_adapter_cs_available(self)  shared_lock_available(&(self)->sva_cslock)


/* Try to open `fd' as an SVGA video adapter.
 * @return: * :   Success
 * @return: NULL: Error (s.a. `errno')
 * @return: SVGA_TRYOPEN_BADDEV: Given `fd' is not for `/dev/svga' */
INTDEF WUNUSED struct svga_adapter *CC svga_tryopen(/*inherited(on_success)*/ fd_t fd);
#define SVGA_TRYOPEN_BADDEV ((struct svga_adapter *)-1)

DECL_END
#endif /* HAVE_SVGA_ADAPTER */

#endif /* !GUARD_LIBVIDEO_DRIVER_ADAPTER_SVGA_H */
