#ifndef PLATFORM_H
#define PLATFORM_H
#ifdef _WIN32
   #define USE_WINDOWS_COMMON
   
   #ifdef _WIN64
      #define USE_WINDOWS_ONLY_64
   #else
      #define USE_WINDOWS_ONLY_32
   #endif

#elif __APPLE__
#error "Not Support Apple platform"
/*
    #include "TargetConditionals.h"
    #if TARGET_IPHONE_SIMULATOR
         // iOS Simulator
    #elif TARGET_OS_IPHONE
        // iOS device
    #elif TARGET_OS_MAC
        // Other kinds of Mac OS
    #else
    #   error "Unknown Apple platform"
    #endif
*/
#elif __ANDROID__
    #error "Not Support Android platform"
#elif __linux__
    // linux
    #define USE_LINUX
#elif __unix__ // all unices not caught above
    #warning "unix platform maybe unstabitily"
#else
#   error "Unknown compiler"
#endif
#endif //PLATFORM_H
