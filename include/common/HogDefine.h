#pragma once

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

#define ENSURE_PTR(ptr) if(!ptr) { return; }
#define ENSURE_PTR_RETURN_VAL(ptr, retVal) if(!ptr) { return retVal; }
#define RETURN_IF_EMPTY(str) if(str.empty()) { return; }
#define REPORT_ERR std::printf("DAN YOU'RE MISSING SOMETHING IN %s: Line %d ", __FILE__, __LINE__);
#define REPORT_ERR_MSG(s) std::printf("DAN YOU'RE MISSING SOMETHING IN %s: Line %d Info: %s", __FILE__, __LINE__, s);
// TODO: THIS #define REPORT_ERR_MSG_FATAL(...) std::printf("DAN YOU'RE MISSING SOMETHING IN %s: Line %d Info: %s", __FILE__, __LINE__, s);
