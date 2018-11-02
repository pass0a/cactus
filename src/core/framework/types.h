#ifndef SRC_TYPES_H_
#define SRC_TYPES_H_

#include <math.h>
#include <stdint.h>
#include <cassert>

namespace cactus {

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

enum DataType {
    kInvalid = 0,
    kFloat,
    kDouble,
    kInt8,
    kInt16,
    kInt32,
    kInt64,
    kUint8,
    kUint16,
    kUint32,
    kUint64
};

// Validates type T for whether it is a supported DataType.
template <class T>
struct IsValidDataType {
    static constexpr bool value = false;
};

// DataTypeToEnum<T>::v() and DataTypeToEnum<T>::value are the DataType
// constants for T, e.g. DataTypeToEnum<float>::v() is DT_FLOAT.
template <class T>
struct DataTypeToEnum {
    static_assert(IsValidDataType<T>::value, "Specified Data Type not supported");
};  // Specializations below

    // EnumToDataType<VALUE>::Type is the type for DataType constant VALUE, e.g.
    // EnumToDataType<DT_FLOAT>::Type is float.
template <DataType VALUE>
struct EnumToDataType {};  // Specializations below

                               // Template specialization for both DataTypeToEnum and EnumToDataType.
#define MATCH_TYPE_AND_ENUM(TYPE, ENUM)                 \
  template <>                                           \
  struct DataTypeToEnum<TYPE> {                         \
    static constexpr DataType value = ENUM;             \
  };                                                    \
  template <>                                           \
  struct IsValidDataType<TYPE> {                        \
    static constexpr bool value = true;                 \
  };                                                    \
  template <>                                           \
  struct EnumToDataType<ENUM> {                         \
    typedef TYPE Type;                                  \
  }

MATCH_TYPE_AND_ENUM(float_t, kFloat);
MATCH_TYPE_AND_ENUM(double_t, kDouble);
MATCH_TYPE_AND_ENUM(int8_t, kInt8);
MATCH_TYPE_AND_ENUM(int16_t, kInt16);
MATCH_TYPE_AND_ENUM(int32_t, kInt32);
MATCH_TYPE_AND_ENUM(int64_t, kInt64);
MATCH_TYPE_AND_ENUM(uint8_t, kUint8);
MATCH_TYPE_AND_ENUM(uint16_t, kUint16);
MATCH_TYPE_AND_ENUM(uint32_t, kUint32);
MATCH_TYPE_AND_ENUM(uint64_t, kUint64);

#undef MATCH_TYPE_AND_ENUM

#define SINGLE_ARG(...) __VA_ARGS__
#define CASE(TYPE, STMTS)             \
  case DataTypeToEnum<TYPE>::value: { \
    typedef TYPE T;                   \
    STMTS;                            \
    break;                            \
  }
#define CASES(TYPE_ENUM, STMTS) \
  switch (TYPE_ENUM) {                                         \
    CASE(float_t, SINGLE_ARG(STMTS))                             \
    CASE(double_t, SINGLE_ARG(STMTS))                            \
    CASE(int8_t, SINGLE_ARG(STMTS))                             \
    CASE(int16_t, SINGLE_ARG(STMTS))                            \
    CASE(int32_t, SINGLE_ARG(STMTS))                             \
    CASE(int64_t, SINGLE_ARG(STMTS))                            \
    CASE(uint8_t, SINGLE_ARG(STMTS))                             \
    CASE(uint16_t, SINGLE_ARG(STMTS))                            \
    CASE(uint32_t, SINGLE_ARG(STMTS))                             \
    CASE(uint64_t, SINGLE_ARG(STMTS))                            \
    case kInvalid:                                           \
      assert(0 && "tensor was Invaild!!!");                   \
      break;                                                   \
    default:                                                   \
      assert(0 && "tensor not supported this Type!!!");      \
      break;                                                   \
  }

#define ArrayCase(L1,L2, STMTS) \
  assert(L1.dtype()==L2.dtype());\
  if(L1.shape()!=L2.shape()){\
    if(L1.shape().total()==1){\
        CASES(L1.dtype(),T a=L1.get<T>(0);auto b = Map<T>::mapping(L2).array();STMTS)\
    }else if(L2.shape().total()==1){\
        CASES(L1.dtype(),auto a=Map<T>::mapping(L1).array();T b = L2.get<T>(0);STMTS)\
    }else {assert(0);}\
  }else{\
    CASES(L1.dtype(),auto a=Map<T>::mapping(L1).array();auto b = Map<T>::mapping(L2).array();STMTS)\
  }
#define TensorCase(L1,L2, STMTS) \
  assert(L1.dtype()==L2.dtype());\
  if(L1.shape()!=L2.shape()){\
    if(L1.shape().total()==1){\
        CASES(L1.dtype(),T a=L1.get<T>(0);auto b = Map<T>::mapping(L2);STMTS)\
    }else if(L2.shape().total()==1){\
        CASES(L1.dtype(),auto a=Map<T>::mapping(L1);T b = L2.get<T>(0);STMTS)\
    }else {assert(0);}\
  }else{\
    CASES(L1.dtype(),auto a=Map<T>::mapping(L1);auto b = Map<T>::mapping(L2);STMTS)\
  }
}



#endif  // SRC_TYPES_H_
