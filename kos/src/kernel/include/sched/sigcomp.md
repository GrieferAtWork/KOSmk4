# Signal Completion Callbacks

## Synopsis

Signal completion callbacks are custom connections for `struct sig`.


## Brief

Through use of signal completion callbacks, it becomes possible to dynamically monitor/intercept signals being delivered, as well as inject other custom code to-be executed upon some signal being delivered.

## Usage

### Eample: Raising Edge Detector

The following is an example implementation of a general-purpose raising-edge detector, which can be used to asynchronously maintain a connection to some arbitrary signal, and proceed to monitor said signal for raising-edge events (that is: keep track of every time the signal is broadcast/sent)

```c
/* `struct rising_edge_detector'   can  be  used  for  implementing  an  asynchronous
 * connection to a signal (i.e. do the equivalent of `task_connect()' asynchronously,
 * including across return-to-userspace-and-back-via-syscall  or similar  situations) */
struct rising_edge_detector {
	WEAK refcnt_t     red_refcnt;   /* Reference counter */
	struct sigcompcon red_compl;    /* The used completion callback */
	bool              red_detected; /* Set to true when a rising edge was detected */
	struct sig        red_ondetect; /* Broadcast when `red_detected' becomes true */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL rising_edge_detector_destroy)(struct rising_edge_detector *__restrict self) {
	sigcompcon_disconnect(&self->red_compl);
	kfree(self);
}
DEFINE_REFCNT_FUNCTIONS(struct rising_edge_detector, red_refcnt, rising_edge_detector_destroy)

PRIVATE NOBLOCK void
NOTHROW(FCALL red_phase2)(struct sigcompctx *__restrict UNUSED(context), void *buf) {
	/* We use a phase #2 callback to broadcast our own signal,
	 * indicating that a raising edge event has been detected. */
	REF struct rising_edge_detector *me;
	me = *(REF struct rising_edge_detector **)buf;
	sig_broadcast(&me->red_ondetect);
	decref_unlikely(me);
}

PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL red_phase1)(struct sigcompcon *__restrict self,
                          struct sigcompctx *__restrict context,
                          void *buf, size_t bufsize) {
	struct rising_edge_detector *me;
	if (bufsize < sizeof(void *))
		return sizeof(void *); /* Need a larger buffer */
	me = container_of(self, struct rising_edge_detector, red_compl);

	/* Automatic re-prime. Could also be  done by not re-priming  automatically,
	 * and instead remembering the connected signal and re-connecting every time
	 * the edge is consumed in `rising_edge_detector_waitfor()'
	 *
	 * But for the  purpose of simplicity  and this only  being meant as  a
	 * demo, just we always re-prime (meaning we'll always stay connected).
	 *
	 * Note that the `SIGCOMP_MODE_F_REPRIME' flag is ignored if the caller
	 * uses `sig_broadcast_for_fini()'  (or  similar,  `SIG_XSEND_F_FINI'). */
	context->scc_mode = SIGCOMP_MODE_F_REPRIME;
	if (atomic_xch(&me->red_detected, true)) {
		/* Don't consume "sig_send" signals after we've already detected an  edge.
		 * This is done by marking our context-mode as "SIGCOMP_MODE_F_NONVIABLE",
		 * which will cause "sig_send" to go looking for another receiver. */
		context->scc_mode |= SIGCOMP_MODE_F_NONVIABLE;
		return 0; /* Only need phase2 if we manage to set `red_detected' to true. */
	}
	*(void **)buf = incref(me); /* Inherited by `red_phase2()' */
	context->scc_post = &red_phase2;
	return sizeof(void *);
}

PRIVATE NOBLOCK NONNULL((1)) REF struct rising_edge_detector *FCALL
rising_edge_detector_create(struct sig *__restrict signal) THROWS(E_BADALLOC) {
	REF struct rising_edge_detector *result;
	result = (REF struct rising_edge_detector *)kmalloc(sizeof(REF struct rising_edge_detector),
	                                                    GFP_NORMAL);
	result->red_refcnt   = 1;
	result->red_detected = false;
	sig_init(&result->red_ondetect);
	sigcompcon_init(&result->red_compl, &red_phase1);
	sigcompcon_connect_for_poll(&result->red_compl, signal);
	return result;
}

PRIVATE BLOCKING NONNULL((1)) void FCALL
rising_edge_detector_waitfor(struct rising_edge_detector *__restrict self) {
	while (!atomic_xch(&self->red_detected, false)) {
		task_connect(&self->red_ondetect);
		if unlikely(atomic_xch(&self->red_detected, false)) {
			task_disconnectall();
			break;
		}
		task_waitfor();
	}
}

PRIVATE DEFINE_SIG(mysig);
PRIVATE REF struct rising_edge_detector *red;

PRIVATE void demo(void) {
	/* This is essentially an async task_connect() */
	red = rising_edge_detector_create(&mysig);

	/* At this point, control flow could even return
	 * back  to user-space, and `red' would still be
	 * able to pick up on `mysig' being triggered. */
	sig_broadcast(&mysig);

	/* Async task_waitfor() */
	rising_edge_detector_waitfor(red);
	decref(red);
}
```
