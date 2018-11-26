#ifndef SRC_TYPES_H_
#define SRC_TYPES_H_

#include <math.h>
#include <stdint.h>
#include <cassert>

#if (defined WIN32 || defined _WIN32 || defined WINCE || defined __CYGWIN__) && defined CxAPI_EXPORTS
#  define Cx_EXPORTS __declspec(dllexport)
#elif defined __GNUC__ && __GNUC__ >= 4
#  define Cx_EXPORTS __attribute__ ((visibility ("default")))
#else
#  define Cx_EXPORTS
#endif

#ifndef Cx_EXTERN_C
#  ifdef __cplusplus
#    define Cx_EXTERN_C extern "C"
#  else
#    define Cx_EXTERN_C
#  endif
#endif

#endif  // SRC_TYPES_H_
