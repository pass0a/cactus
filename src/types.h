#ifndef SRC_TYPES_H_
#define SRC_TYPES_H_

#include <math.h>
#include <stdint.h>
namespace cactus {

enum DataType {
    kFloat = 0,
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
struct IsValidDataType;

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

}

#endif  // SRC_TYPES_H_