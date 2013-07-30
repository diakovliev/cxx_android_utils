#ifndef _ContextWrapper_genheader
#define _ContextWrapper_genheader

static JavaMethod ContextWrapper[] = {
  /* public android.content.ContextWrapper(android.content.Context); */
  { 0, Void, Public|Constructor, "<init>", "<init>", "(Landroid/content/Context;)V" },
  /* protected void attachBaseContext(android.content.Context); */
  { 0, Void, Protected|Function, "attachBaseContext", "attachBaseContext", "(Landroid/content/Context;)V" },
  /* public android.content.Context getBaseContext(); */
  { 0, Object, Public|Function, "getBaseContext", "getBaseContext", "()Landroid/content/Context;" },
  /* public android.content.res.AssetManager getAssets(); */
  { 0, Object, Public|Function, "getAssets", "getAssets", "()Landroid/content/res/AssetManager;" },
  /* public android.content.res.Resources getResources(); */
  { 0, Object, Public|Function, "getResources", "getResources", "()Landroid/content/res/Resources;" },
  /* public android.content.pm.PackageManager getPackageManager(); */
  { 0, Object, Public|Function, "getPackageManager", "getPackageManager", "()Landroid/content/pm/PackageManager;" },
  /* public android.content.ContentResolver getContentResolver(); */
  { 0, Object, Public|Function, "getContentResolver", "getContentResolver", "()Landroid/content/ContentResolver;" },
  /* public android.os.Looper getMainLooper(); */
  { 0, Object, Public|Function, "getMainLooper", "getMainLooper", "()Landroid/os/Looper;" },
  /* public android.content.Context getApplicationContext(); */
  { 0, Object, Public|Function, "getApplicationContext", "getApplicationContext", "()Landroid/content/Context;" },
  /* public void setTheme(int); */
  { 0, Void, Public|Function, "setTheme", "setTheme", "(I)V" },
  /* public android.content.res.Resources$Theme getTheme(); */
  { 0, Object, Public|Function, "getTheme", "getTheme", "()Landroid/content/res/Resources$Theme;" },
  /* public java.lang.ClassLoader getClassLoader(); */
  { 0, Object, Public|Function, "getClassLoader", "getClassLoader", "()Ljava/lang/ClassLoader;" },
  /* public java.lang.String getPackageName(); */
  { 0, Object, Public|Function, "getPackageName", "getPackageName", "()Ljava/lang/String;" },
  /* public android.content.pm.ApplicationInfo getApplicationInfo(); */
  { 0, Object, Public|Function, "getApplicationInfo", "getApplicationInfo", "()Landroid/content/pm/ApplicationInfo;" },
  /* public java.lang.String getPackageResourcePath(); */
  { 0, Object, Public|Function, "getPackageResourcePath", "getPackageResourcePath", "()Ljava/lang/String;" },
  /* public java.lang.String getPackageCodePath(); */
  { 0, Object, Public|Function, "getPackageCodePath", "getPackageCodePath", "()Ljava/lang/String;" },
  /* public android.content.SharedPreferences getSharedPreferences(java.lang.String, int); */
  { 0, Object, Public|Function, "getSharedPreferences", "getSharedPreferences", "(Ljava/lang/String;I)Landroid/content/SharedPreferences;" },
  /* public java.io.FileInputStream openFileInput(java.lang.String) throws java.io.FileNotFoundException; */
  { 0, Object, Public|Function, "openFileInput", "openFileInput", "(Ljava/lang/String;)Ljava/io/FileInputStream;" },
  /* public java.io.FileOutputStream openFileOutput(java.lang.String, int) throws java.io.FileNotFoundException; */
  { 0, Object, Public|Function, "openFileOutput", "openFileOutput", "(Ljava/lang/String;I)Ljava/io/FileOutputStream;" },
  /* public boolean deleteFile(java.lang.String); */
  { 0, Boolean, Public|Function, "deleteFile", "deleteFile", "(Ljava/lang/String;)Z" },
  /* public java.io.File getFileStreamPath(java.lang.String); */
  { 0, Object, Public|Function, "getFileStreamPath", "getFileStreamPath", "(Ljava/lang/String;)Ljava/io/File;" },
  /* public java.lang.String[] fileList(); */
  { 0, Object, Public|Function, "fileList", "fileList", "()[Ljava/lang/String;" },
  /* public java.io.File getFilesDir(); */
  { 0, Object, Public|Function, "getFilesDir", "getFilesDir", "()Ljava/io/File;" },
  /* public java.io.File getExternalFilesDir(java.lang.String); */
  { 0, Object, Public|Function, "getExternalFilesDir", "getExternalFilesDir", "(Ljava/lang/String;)Ljava/io/File;" },
  /* public java.io.File getObbDir(); */
  { 0, Object, Public|Function, "getObbDir", "getObbDir", "()Ljava/io/File;" },
  /* public java.io.File getCacheDir(); */
  { 0, Object, Public|Function, "getCacheDir", "getCacheDir", "()Ljava/io/File;" },
  /* public java.io.File getExternalCacheDir(); */
  { 0, Object, Public|Function, "getExternalCacheDir", "getExternalCacheDir", "()Ljava/io/File;" },
  /* public java.io.File getDir(java.lang.String, int); */
  { 0, Object, Public|Function, "getDir", "getDir", "(Ljava/lang/String;I)Ljava/io/File;" },
  /* public android.database.sqlite.SQLiteDatabase openOrCreateDatabase(java.lang.String, int, android.database.sqlite.SQLiteDatabase$CursorFactory); */
  { 0, Object, Public|Function, "openOrCreateDatabase", "openOrCreateDatabase", "(Ljava/lang/String;ILandroid/database/sqlite/SQLiteDatabase$CursorFactory;)Landroid/database/sqlite/SQLiteDatabase;" },
  /* public android.database.sqlite.SQLiteDatabase openOrCreateDatabase(java.lang.String, int, android.database.sqlite.SQLiteDatabase$CursorFactory, android.database.DatabaseErrorHandler); */
  { 0, Object, Public|Function, "openOrCreateDatabase_0", "openOrCreateDatabase", "(Ljava/lang/String;ILandroid/database/sqlite/SQLiteDatabase$CursorFactory;Landroid/database/DatabaseErrorHandler;)Landroid/database/sqlite/SQLiteDatabase;" },
  /* public boolean deleteDatabase(java.lang.String); */
  { 0, Boolean, Public|Function, "deleteDatabase", "deleteDatabase", "(Ljava/lang/String;)Z" },
  /* public java.io.File getDatabasePath(java.lang.String); */
  { 0, Object, Public|Function, "getDatabasePath", "getDatabasePath", "(Ljava/lang/String;)Ljava/io/File;" },
  /* public java.lang.String[] databaseList(); */
  { 0, Object, Public|Function, "databaseList", "databaseList", "()[Ljava/lang/String;" },
  /* public android.graphics.drawable.Drawable getWallpaper(); */
  { 0, Object, Public|Function, "getWallpaper", "getWallpaper", "()Landroid/graphics/drawable/Drawable;" },
  /* public android.graphics.drawable.Drawable peekWallpaper(); */
  { 0, Object, Public|Function, "peekWallpaper", "peekWallpaper", "()Landroid/graphics/drawable/Drawable;" },
  /* public int getWallpaperDesiredMinimumWidth(); */
  { 0, Int, Public|Function, "getWallpaperDesiredMinimumWidth", "getWallpaperDesiredMinimumWidth", "()I" },
  /* public int getWallpaperDesiredMinimumHeight(); */
  { 0, Int, Public|Function, "getWallpaperDesiredMinimumHeight", "getWallpaperDesiredMinimumHeight", "()I" },
  /* public void setWallpaper(android.graphics.Bitmap) throws java.io.IOException; */
  { 0, Void, Public|Function, "setWallpaper", "setWallpaper", "(Landroid/graphics/Bitmap;)V" },
  /* public void setWallpaper(java.io.InputStream) throws java.io.IOException; */
  { 0, Void, Public|Function, "setWallpaper_1", "setWallpaper", "(Ljava/io/InputStream;)V" },
  /* public void clearWallpaper() throws java.io.IOException; */
  { 0, Void, Public|Function, "clearWallpaper", "clearWallpaper", "()V" },
  /* public void startActivity(android.content.Intent); */
  { 0, Void, Public|Function, "startActivity", "startActivity", "(Landroid/content/Intent;)V" },
  /* public void startActivities(android.content.Intent[]); */
  { 0, Void, Public|Function, "startActivities", "startActivities", "([Landroid/content/Intent;)V" },
  /* public void startIntentSender(android.content.IntentSender, android.content.Intent, int, int, int) throws android.content.IntentSender$SendIntentException; */
  { 0, Void, Public|Function, "startIntentSender", "startIntentSender", "(Landroid/content/IntentSender;Landroid/content/Intent;III)V" },
  /* public void sendBroadcast(android.content.Intent); */
  { 0, Void, Public|Function, "sendBroadcast", "sendBroadcast", "(Landroid/content/Intent;)V" },
  /* public void sendBroadcast(android.content.Intent, java.lang.String); */
  { 0, Void, Public|Function, "sendBroadcast_2", "sendBroadcast", "(Landroid/content/Intent;Ljava/lang/String;)V" },
  /* public void sendOrderedBroadcast(android.content.Intent, java.lang.String); */
  { 0, Void, Public|Function, "sendOrderedBroadcast", "sendOrderedBroadcast", "(Landroid/content/Intent;Ljava/lang/String;)V" },
  /* public void sendOrderedBroadcast(android.content.Intent, java.lang.String, android.content.BroadcastReceiver, android.os.Handler, int, java.lang.String, android.os.Bundle); */
  { 0, Void, Public|Function, "sendOrderedBroadcast_3", "sendOrderedBroadcast", "(Landroid/content/Intent;Ljava/lang/String;Landroid/content/BroadcastReceiver;Landroid/os/Handler;ILjava/lang/String;Landroid/os/Bundle;)V" },
  /* public void sendStickyBroadcast(android.content.Intent); */
  { 0, Void, Public|Function, "sendStickyBroadcast", "sendStickyBroadcast", "(Landroid/content/Intent;)V" },
  /* public void sendStickyOrderedBroadcast(android.content.Intent, android.content.BroadcastReceiver, android.os.Handler, int, java.lang.String, android.os.Bundle); */
  { 0, Void, Public|Function, "sendStickyOrderedBroadcast", "sendStickyOrderedBroadcast", "(Landroid/content/Intent;Landroid/content/BroadcastReceiver;Landroid/os/Handler;ILjava/lang/String;Landroid/os/Bundle;)V" },
  /* public void removeStickyBroadcast(android.content.Intent); */
  { 0, Void, Public|Function, "removeStickyBroadcast", "removeStickyBroadcast", "(Landroid/content/Intent;)V" },
  /* public android.content.Intent registerReceiver(android.content.BroadcastReceiver, android.content.IntentFilter); */
  { 0, Object, Public|Function, "registerReceiver", "registerReceiver", "(Landroid/content/BroadcastReceiver;Landroid/content/IntentFilter;)Landroid/content/Intent;" },
  /* public android.content.Intent registerReceiver(android.content.BroadcastReceiver, android.content.IntentFilter, java.lang.String, android.os.Handler); */
  { 0, Object, Public|Function, "registerReceiver_4", "registerReceiver", "(Landroid/content/BroadcastReceiver;Landroid/content/IntentFilter;Ljava/lang/String;Landroid/os/Handler;)Landroid/content/Intent;" },
  /* public void unregisterReceiver(android.content.BroadcastReceiver); */
  { 0, Void, Public|Function, "unregisterReceiver", "unregisterReceiver", "(Landroid/content/BroadcastReceiver;)V" },
  /* public android.content.ComponentName startService(android.content.Intent); */
  { 0, Object, Public|Function, "startService", "startService", "(Landroid/content/Intent;)Landroid/content/ComponentName;" },
  /* public boolean stopService(android.content.Intent); */
  { 0, Boolean, Public|Function, "stopService", "stopService", "(Landroid/content/Intent;)Z" },
  /* public boolean bindService(android.content.Intent, android.content.ServiceConnection, int); */
  { 0, Boolean, Public|Function, "bindService", "bindService", "(Landroid/content/Intent;Landroid/content/ServiceConnection;I)Z" },
  /* public void unbindService(android.content.ServiceConnection); */
  { 0, Void, Public|Function, "unbindService", "unbindService", "(Landroid/content/ServiceConnection;)V" },
  /* public boolean startInstrumentation(android.content.ComponentName, java.lang.String, android.os.Bundle); */
  { 0, Boolean, Public|Function, "startInstrumentation", "startInstrumentation", "(Landroid/content/ComponentName;Ljava/lang/String;Landroid/os/Bundle;)Z" },
  /* public java.lang.Object getSystemService(java.lang.String); */
  { 0, Object, Public|Function, "getSystemService", "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;" },
  /* public int checkPermission(java.lang.String, int, int); */
  { 0, Int, Public|Function, "checkPermission", "checkPermission", "(Ljava/lang/String;II)I" },
  /* public int checkCallingPermission(java.lang.String); */
  { 0, Int, Public|Function, "checkCallingPermission", "checkCallingPermission", "(Ljava/lang/String;)I" },
  /* public int checkCallingOrSelfPermission(java.lang.String); */
  { 0, Int, Public|Function, "checkCallingOrSelfPermission", "checkCallingOrSelfPermission", "(Ljava/lang/String;)I" },
  /* public void enforcePermission(java.lang.String, int, int, java.lang.String); */
  { 0, Void, Public|Function, "enforcePermission", "enforcePermission", "(Ljava/lang/String;IILjava/lang/String;)V" },
  /* public void enforceCallingPermission(java.lang.String, java.lang.String); */
  { 0, Void, Public|Function, "enforceCallingPermission", "enforceCallingPermission", "(Ljava/lang/String;Ljava/lang/String;)V" },
  /* public void enforceCallingOrSelfPermission(java.lang.String, java.lang.String); */
  { 0, Void, Public|Function, "enforceCallingOrSelfPermission", "enforceCallingOrSelfPermission", "(Ljava/lang/String;Ljava/lang/String;)V" },
  /* public void grantUriPermission(java.lang.String, android.net.Uri, int); */
  { 0, Void, Public|Function, "grantUriPermission", "grantUriPermission", "(Ljava/lang/String;Landroid/net/Uri;I)V" },
  /* public void revokeUriPermission(android.net.Uri, int); */
  { 0, Void, Public|Function, "revokeUriPermission", "revokeUriPermission", "(Landroid/net/Uri;I)V" },
  /* public int checkUriPermission(android.net.Uri, int, int, int); */
  { 0, Int, Public|Function, "checkUriPermission", "checkUriPermission", "(Landroid/net/Uri;III)I" },
  /* public int checkCallingUriPermission(android.net.Uri, int); */
  { 0, Int, Public|Function, "checkCallingUriPermission", "checkCallingUriPermission", "(Landroid/net/Uri;I)I" },
  /* public int checkCallingOrSelfUriPermission(android.net.Uri, int); */
  { 0, Int, Public|Function, "checkCallingOrSelfUriPermission", "checkCallingOrSelfUriPermission", "(Landroid/net/Uri;I)I" },
  /* public int checkUriPermission(android.net.Uri, java.lang.String, java.lang.String, int, int, int); */
  { 0, Int, Public|Function, "checkUriPermission_5", "checkUriPermission", "(Landroid/net/Uri;Ljava/lang/String;Ljava/lang/String;III)I" },
  /* public void enforceUriPermission(android.net.Uri, int, int, int, java.lang.String); */
  { 0, Void, Public|Function, "enforceUriPermission", "enforceUriPermission", "(Landroid/net/Uri;IIILjava/lang/String;)V" },
  /* public void enforceCallingUriPermission(android.net.Uri, int, java.lang.String); */
  { 0, Void, Public|Function, "enforceCallingUriPermission", "enforceCallingUriPermission", "(Landroid/net/Uri;ILjava/lang/String;)V" },
  /* public void enforceCallingOrSelfUriPermission(android.net.Uri, int, java.lang.String); */
  { 0, Void, Public|Function, "enforceCallingOrSelfUriPermission", "enforceCallingOrSelfUriPermission", "(Landroid/net/Uri;ILjava/lang/String;)V" },
  /* public void enforceUriPermission(android.net.Uri, java.lang.String, java.lang.String, int, int, int, java.lang.String); */
  { 0, Void, Public|Function, "enforceUriPermission_6", "enforceUriPermission", "(Landroid/net/Uri;Ljava/lang/String;Ljava/lang/String;IIILjava/lang/String;)V" },
  /* public android.content.Context createPackageContext(java.lang.String, int) throws android.content.pm.PackageManager$NameNotFoundException; */
  { 0, Object, Public|Function, "createPackageContext", "createPackageContext", "(Ljava/lang/String;I)Landroid/content/Context;" },
  /* public boolean isRestricted(); */
  { 0, Boolean, Public|Function, "isRestricted", "isRestricted", "()Z" },
};

static JavaObjectDesc ContextWrapper_Desc = {
  ContextWrapper,
  sizeof(ContextWrapper)/sizeof(ContextWrapper[0])
};

#endif /*_ContextWrapper_genheader*/
