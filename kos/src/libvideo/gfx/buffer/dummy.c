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
#ifndef GUARD_LIBVIDEO_GFX_BUFFER_DUMMY_C
#define GUARD_LIBVIDEO_GFX_BUFFER_DUMMY_C 1
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/align.h>

#include <kos/anno.h>
#include <kos/aref.h>
#include <kos/refcnt.h>
#include <kos/types.h>
#include <sys/mman.h>

#include <assert.h>
#include <atomic.h>
#include <fcntl.h>
#include <malloc.h>
#include <stddef.h>
#include <unistd.h>

#include <libvideo/gfx/buffer/dummy.h>

#include "dummy.h"

DECL_BEGIN

PRIVATE fd_t dev_void = -1;
PRIVATE WUNUSED fd_t CC get_dev_void(void) {
	fd_t result = atomic_read(&dev_void);
	if (result == -1) {
#ifdef __KOS__
		result = open("/dev/void", O_RDWR);
		if (result < 0)
#endif /* __KOS__ */
		{
			/* Shouldn't happen under KOS... */
			result = open("/dev/null", O_RDWR);
		}
		if (result >= 0) {
			fd_t old = atomic_cmpxch_val(&dev_void, -1, result);
			if unlikely(old != -1) {
				(void)close(result);
				result = old;
			}
		}
	}
	return result;
}

/* Hooked by build script via `-fini=libvideo_gfx_fini' */
INTERN void libvideo_gfx_fini(void) {
	if (dev_void != -1)
		(void)close(dev_void);
}

PRIVATE WUNUSED byte_t *CC mmap_void(size_t num_bytes) {
	byte_t *result;
	fd_t dev_void = get_dev_void();
	if unlikely(dev_void < 0)
		return NULL;
	result = (byte_t *)mmap(NULL, num_bytes, PROT_READ | PROT_WRITE,
	                        MAP_PRIVATE | MAP_FILE, dev_void, 0);
	if (result == MAP_FAILED) {
		result = NULL;
	} else {
		assert(result != NULL);
	}
	return result;
}

PRIVATE void CC munmap_void(byte_t *data, size_t num_bytes) {
	(void)munmap(data, num_bytes);
}



AWREF(video_buffer_dummy_awref, video_buffer_dummy);

/* [0..1] Cached, most-recent dummy buffer (so it can be re-used if still allocated) */
PRIVATE struct video_buffer_dummy_awref current_dummy = AWREF_INIT(NULL);


PRIVATE NONNULL((1)) void CC
dummy_destroy(struct video_buffer_dummy *__restrict self) {
	awref_cmpxch(&current_dummy, self, NULL);
	munmap_void(self->vbd_data, self->vbd_size);
	free(self);
}


/* Return a video buffer dummy representing at least `num_bytes' bytes of data
 * @return: * : A reference to a dummy buffer able to substitute at least `num_bytes' bytes
 * @return: NULL: Insufficient memory */
DEFINE_PUBLIC_ALIAS(video_buffer_getdummy, libvideo_buffer_getdummy);
INTERN WUNUSED REF struct video_buffer_dummy *CC
libvideo_buffer_getdummy(size_t num_bytes) {
	size_t aligned_num_bytes;
	REF struct video_buffer_dummy *current;
	REF struct video_buffer_dummy *result;
	current = awref_get(&current_dummy);
	if (current) {
		if (current->vbd_size >= num_bytes)
			return current;
		video_buffer_dummy_decref(current);
	}

	/* Allocate a new dummy buffer */
	result = (REF struct video_buffer_dummy *)malloc(sizeof(struct video_buffer_dummy));
	if unlikely(!result)
		goto err;
	aligned_num_bytes = CEIL_ALIGN(num_bytes, getpagesize());
	result->vbd_data = mmap_void(aligned_num_bytes);
	if unlikely(!result->vbd_data)
		goto err_r;
	result->vbd_size    = aligned_num_bytes;
	result->vbd_refcnt  = 1;
	result->vbd_destroy = &dummy_destroy;
	while (!awref_cmpxch(&current_dummy, current, result)) {
		/* Check again if the now-current dummy is large enough */
		current = awref_get(&current_dummy);
		if (current) {
			if (current->vbd_size >= aligned_num_bytes) {
				dummy_destroy(result);
				return current;
			}
			video_buffer_dummy_decref(current);
		}
	}
	return result;
err_r:
	free(result);
err:
	return NULL;
}

DECL_END

#endif /* !GUARD_LIBVIDEO_GFX_BUFFER_DUMMY_C */
