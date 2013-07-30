#! /bin/sh

ANDROID_SDK=~/android/android-sdk-linux
ANDROID_PLATFORM=android-14
ANDROID_JAR=$ANDROID_SDK/platforms/$ANDROID_PLATFORM/android.jar

#PACKAGE=android.app
#CLASS=Notification.Builder
#MARRAY_NAME=NotificationBuilder

PACKAGE=$1
CLASS=$2
MARRAY_NAME=$3

JAVAP_CMD=`javap -s -p -classpath "$ANDROID_JAR" "$PACKAGE.$CLASS"`

echo "#ifndef _${MARRAY_NAME}_genheader"
echo "#define _${MARRAY_NAME}_genheader"
echo ""
echo "static JavaMethod ${MARRAY_NAME}[] = {"

javap -s -p -classpath "$ANDROID_JAR" "$PACKAGE.$CLASS" | ./parce_def.py

echo "};"
echo ""
echo "static JavaObjectDesc ${MARRAY_NAME}_Desc = {"
echo "  $MARRAY_NAME,"
echo "  sizeof($MARRAY_NAME)/sizeof(${MARRAY_NAME}[0])"
echo "};"
echo ""
echo "#endif /*_${MARRAY_NAME}_genheader*/"

