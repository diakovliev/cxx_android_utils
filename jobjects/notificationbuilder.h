#ifndef _NotificationBuilder_genheader
#define _NotificationBuilder_genheader

static JavaMethod NotificationBuilder[] = {
  /* public android.app.Notification$Builder(android.content.Context); */
  { 0, Void, Public|Constructor, "<init>", "<init>", "(Landroid/content/Context;)V" },
  /* public android.app.Notification$Builder setWhen(long); */
  { 0, Object, Public|Function, "setWhen", "setWhen", "(J)Landroid/app/Notification$Builder;" },
  /* public android.app.Notification$Builder setSmallIcon(int); */
  { 0, Object, Public|Function, "setSmallIcon", "setSmallIcon", "(I)Landroid/app/Notification$Builder;" },
  /* public android.app.Notification$Builder setSmallIcon(int, int); */
  { 0, Object, Public|Function, "setSmallIcon_0", "setSmallIcon", "(II)Landroid/app/Notification$Builder;" },
  /* public android.app.Notification$Builder setContentTitle(java.lang.CharSequence); */
  { 0, Object, Public|Function, "setContentTitle", "setContentTitle", "(Ljava/lang/CharSequence;)Landroid/app/Notification$Builder;" },
  /* public android.app.Notification$Builder setContentText(java.lang.CharSequence); */
  { 0, Object, Public|Function, "setContentText", "setContentText", "(Ljava/lang/CharSequence;)Landroid/app/Notification$Builder;" },
  /* public android.app.Notification$Builder setNumber(int); */
  { 0, Object, Public|Function, "setNumber", "setNumber", "(I)Landroid/app/Notification$Builder;" },
  /* public android.app.Notification$Builder setContentInfo(java.lang.CharSequence); */
  { 0, Object, Public|Function, "setContentInfo", "setContentInfo", "(Ljava/lang/CharSequence;)Landroid/app/Notification$Builder;" },
  /* public android.app.Notification$Builder setProgress(int, int, boolean); */
  { 0, Object, Public|Function, "setProgress", "setProgress", "(IIZ)Landroid/app/Notification$Builder;" },
  /* public android.app.Notification$Builder setContent(android.widget.RemoteViews); */
  { 0, Object, Public|Function, "setContent", "setContent", "(Landroid/widget/RemoteViews;)Landroid/app/Notification$Builder;" },
  /* public android.app.Notification$Builder setContentIntent(android.app.PendingIntent); */
  { 0, Object, Public|Function, "setContentIntent", "setContentIntent", "(Landroid/app/PendingIntent;)Landroid/app/Notification$Builder;" },
  /* public android.app.Notification$Builder setDeleteIntent(android.app.PendingIntent); */
  { 0, Object, Public|Function, "setDeleteIntent", "setDeleteIntent", "(Landroid/app/PendingIntent;)Landroid/app/Notification$Builder;" },
  /* public android.app.Notification$Builder setFullScreenIntent(android.app.PendingIntent, boolean); */
  { 0, Object, Public|Function, "setFullScreenIntent", "setFullScreenIntent", "(Landroid/app/PendingIntent;Z)Landroid/app/Notification$Builder;" },
  /* public android.app.Notification$Builder setTicker(java.lang.CharSequence); */
  { 0, Object, Public|Function, "setTicker", "setTicker", "(Ljava/lang/CharSequence;)Landroid/app/Notification$Builder;" },
  /* public android.app.Notification$Builder setTicker(java.lang.CharSequence, android.widget.RemoteViews); */
  { 0, Object, Public|Function, "setTicker_1", "setTicker", "(Ljava/lang/CharSequence;Landroid/widget/RemoteViews;)Landroid/app/Notification$Builder;" },
  /* public android.app.Notification$Builder setLargeIcon(android.graphics.Bitmap); */
  { 0, Object, Public|Function, "setLargeIcon", "setLargeIcon", "(Landroid/graphics/Bitmap;)Landroid/app/Notification$Builder;" },
  /* public android.app.Notification$Builder setSound(android.net.Uri); */
  { 0, Object, Public|Function, "setSound", "setSound", "(Landroid/net/Uri;)Landroid/app/Notification$Builder;" },
  /* public android.app.Notification$Builder setSound(android.net.Uri, int); */
  { 0, Object, Public|Function, "setSound_2", "setSound", "(Landroid/net/Uri;I)Landroid/app/Notification$Builder;" },
  /* public android.app.Notification$Builder setVibrate(long[]); */
  { 0, Object, Public|Function, "setVibrate", "setVibrate", "([J)Landroid/app/Notification$Builder;" },
  /* public android.app.Notification$Builder setLights(int, int, int); */
  { 0, Object, Public|Function, "setLights", "setLights", "(III)Landroid/app/Notification$Builder;" },
  /* public android.app.Notification$Builder setOngoing(boolean); */
  { 0, Object, Public|Function, "setOngoing", "setOngoing", "(Z)Landroid/app/Notification$Builder;" },
  /* public android.app.Notification$Builder setOnlyAlertOnce(boolean); */
  { 0, Object, Public|Function, "setOnlyAlertOnce", "setOnlyAlertOnce", "(Z)Landroid/app/Notification$Builder;" },
  /* public android.app.Notification$Builder setAutoCancel(boolean); */
  { 0, Object, Public|Function, "setAutoCancel", "setAutoCancel", "(Z)Landroid/app/Notification$Builder;" },
  /* public android.app.Notification$Builder setDefaults(int); */
  { 0, Object, Public|Function, "setDefaults", "setDefaults", "(I)Landroid/app/Notification$Builder;" },
  /* public android.app.Notification getNotification(); */
  { 0, Object, Public|Function, "getNotification", "getNotification", "()Landroid/app/Notification;" },
};

static JavaObjectDesc NotificationBuilder_Desc = {
  NotificationBuilder,
  sizeof(NotificationBuilder)/sizeof(NotificationBuilder[0])
};

#endif /*_NotificationBuilder_genheader*/
