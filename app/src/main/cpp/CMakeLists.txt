cmake_minimum_required(VERSION 3.18.1)

add_library(native-activity SHARED main.cpp)

# Export ANativeActivity_onCreate(),
# Refer to: https://github.com/android-ndk/ndk/issues/381.
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")
#its necessary to be compiled into our binary
#its only a wrapper class around ANativeActivity_onCreate
#we could do it by our self's
add_library(native_app_glue STATIC
        ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

#we need to include it because of #include <android_native_app_glue.h> line
target_include_directories(native-activity PRIVATE
        ${ANDROID_NDK}/sources/android/native_app_glue)

target_link_libraries(
#        native-activity is the name of our shared object
        native-activity
#        native_app_glue is the name of our C class wrapper library around ANativeActivity_onCreate
#        method and android lifecycles
#        it's being statically compiled into our binary. it means we're copying it into out final binary
#        we could write it. but we don't want to
        native_app_glue
#        below libraries are automatically resolved by NDK compiler
        android
        log
)