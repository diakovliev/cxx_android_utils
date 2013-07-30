#ifndef _NotificationManager_genheader
#define _NotificationManager_genheader

static JavaMethod NotificationManager[] = {
  /* android.app.NotificationManager(); */
  { 0, Void, Private|Constructor, "<init>", "<init>", "()V" },
  /* public void notify(int, android.app.Notification); */
  { 0, Void, Public|Function, "notify", "notify", "(ILandroid/app/Notification;)V" },
  /* public void notify(java.lang.String, int, android.app.Notification); */
  { 0, Void, Public|Function, "notify_0", "notify", "(Ljava/lang/String;ILandroid/app/Notification;)V" },
  /* public void cancel(int); */
  { 0, Void, Public|Function, "cancel", "cancel", "(I)V" },
  /* public void cancel(java.lang.String, int); */
  { 0, Void, Public|Function, "cancel_1", "cancel", "(Ljava/lang/String;I)V" },
  /* public void cancelAll(); */
  { 0, Void, Public|Function, "cancelAll", "cancelAll", "()V" },
};

static JavaObjectDesc NotificationManager_Desc = {
  NotificationManager,
  sizeof(NotificationManager)/sizeof(NotificationManager[0])
};

#endif /*_NotificationManager_genheader*/
