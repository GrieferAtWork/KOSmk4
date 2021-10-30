NOTHROW(KCALL fnode_v_changed)(struct mfile *__restrict self,
NOTHROW(KCALL fnode_v_destroy)(struct mfile *__restrict self) {
 * @throw: E_FSERROR_READONLY:    The `MFILE_FN_ATTRREADONLY' flag is (or was) set.
	if unlikely(self->mf_flags & MFILE_FN_ATTRREADONLY)
 * @throw: E_FSERROR_READONLY:    The `MFILE_FN_ATTRREADONLY' flag is (or was) set.
	if unlikely(self->mf_flags & MFILE_FN_ATTRREADONLY)
 * @throw: E_FSERROR_READONLY: The `MFILE_FN_ATTRREADONLY' flag is (or was) set. */
	if unlikely(self->mf_flags & MFILE_FN_ATTRREADONLY)
		struct mfile_stream_ops const *stream_ops;
		/* If defined, invoke the streams-sync operator */
		stream_ops = self->mf_ops->mo_stream;
		if (stream_ops != NULL && stream_ops->mso_sync != NULL)
			(*stream_ops->mso_sync)(self);
	                           MFILE_F_DELETED | MFILE_F_NOATIME | MFILE_FN_NODIRATIME |
	                           MFILE_F_NOMTIME | MFILE_F_CHANGED | MFILE_F_ATTRCHANGED |
	                           MFILE_F_FIXEDFILESIZE | MFILE_FN_ATTRREADONLY |
	                           MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO | MFILE_F_READONLY);
	                           MFILE_F_DELETED | MFILE_F_NOATIME | MFILE_FN_NODIRATIME |
	                           MFILE_F_NOMTIME | MFILE_F_CHANGED | MFILE_F_ATTRCHANGED |
	                           MFILE_F_FIXEDFILESIZE | MFILE_FN_ATTRREADONLY |
	                           MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO | MFILE_F_READONLY);
 *  - Set flags: MFILE_F_DELETED | MFILE_F_NOATIME | MFILE_FN_NODIRATIME |
 *               MFILE_F_NOMTIME | MFILE_F_CHANGED | MFILE_F_ATTRCHANGED |
 *               MFILE_F_FIXEDFILESIZE    |    MFILE_FN_ATTRREADONLY     |
 *               MFILE_F_NOUSRMMAP |  MFILE_F_NOUSRIO  |  MFILE_F_READONLY