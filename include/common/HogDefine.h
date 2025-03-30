#ifndef HOG_DEFINE_H
#define HOG_DEFINE_H 

#if defined(__unix__) || defined(__APPLE__) || defined(__linux__) || \
    defined(_POSIX_VERSION)
    #define IS_POSIX 1
#else
    #define IS_POSIX 0
#endif

#if defined(_WIN32)
    #define IS_WINDOWS 1
#else
    #define IS_WINDOWS 0
#endif 

#endif // End HOG_DEFINE_H
