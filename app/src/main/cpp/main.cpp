#include <android_native_app_glue.h>
#include <android/log.h>

void android_main(struct android_app* state) {
    __android_log_print(ANDROID_LOG_DEBUG, __FUNCTION__ , "It lives!!!");
}