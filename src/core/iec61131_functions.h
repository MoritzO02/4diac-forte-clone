/*******************************************************************************
 * Copyright (c) 2010,2023 TU Vienna/ACIN, Profactor GmbH, fortiss GmbH
 *                         Primetals Technologies Austria GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Alois Zoitl, Monika Wenger, Ingo Hegny, Patrick Smejkal, Gerhard Ebenhofer,
 *    Matthias Plasch, Martin Melik Merkumians
 *      - initial implementation and rework communication infrastructure
 *    Martin Melik Merkumians
 *      - added different type templates for IEC 61131-3 functions and adds several type guards
 *      - Reworked binary operator templates to create correctly calculated and typed results
 *      - reworked and fixes ADD and SUB for time types
 *      - Added variadic comparison, MIN, MAX, ADD, MUL functions
 *      - Added unary plus function
 *******************************************************************************/
#ifndef IEC61131_FUNCTIONS_H_
#define IEC61131_FUNCTIONS_H_

#include "../arch/devlog.h"
#include "convert_functions.h"
#include "iec61131_cast_helper.h"
#include "./datatypes/forte_struct.h"
#include "./datatypes/forte_array_common.h"
#include "./datatypes/forte_array_fixed.h"
#include "./datatypes/forte_array_variable.h"
#include "./datatypes/forte_array_dynamic.h"

#include <algorithm>
#include <cmath>
#include <cstring>

#ifdef VXWORKS
#define tanf(x) static_cast<TForteFloat>(tan(x))
#define log10f(x) static_cast<TForteFloat>(log10(x))
#define logf(x) static_cast<TForteFloat>(log(x))
#define cosf(x) static_cast<TForteFloat>(cos(x))
#define atanf(x) static_cast<TForteFloat>(atan(x))
#define asinf(x) static_cast<TForteFloat>(asin(x))
#define acosf(x) static_cast<TForteFloat>(acos(x))
#define expf(x) static_cast<TForteFloat>(exp(x))
#define sinf(x) static_cast<TForteFloat>(sin(x))
#define sqrtf(x) static_cast<TForteFloat>(sqrt(x))
#endif

#define GENERATE_APPLY_FUNCTION(func)  template<typename T> struct func ##_Function { \
  static T call(const T& paIN1, const T& paIN2){ \
      return func(paIN1, paIN2); \
    }; \
};

template<typename T>
T func_ABS(const T &paIN) {
  static_assert((std::is_base_of_v<CIEC_ANY_NUM, T>), "T not of ANY_NUM");
  return (0 > static_cast<typename T::TValueType>(paIN)) ? T(static_cast<typename T::TValueType>(paIN) * static_cast<typename T::TValueType>(-1)) : paIN;
}

inline CIEC_REAL func_SQRT(const CIEC_REAL &paIN){
  return CIEC_REAL(sqrtf(static_cast<CIEC_REAL::TValueType>(paIN)));
}

inline CIEC_LREAL func_SQRT(const CIEC_LREAL &paIN){
  return CIEC_LREAL(sqrt(static_cast<CIEC_LREAL::TValueType>(paIN)));
}

inline CIEC_REAL func_LN(const CIEC_REAL &paIN){
  return CIEC_REAL(logf(static_cast<CIEC_REAL::TValueType>(paIN)));
}

inline CIEC_LREAL func_LN(const CIEC_LREAL &paIN){
  return CIEC_LREAL(log(static_cast<CIEC_LREAL::TValueType>(paIN)));
}

inline CIEC_REAL func_LOG(const CIEC_REAL &paIN){
  return CIEC_REAL(log10f(static_cast<CIEC_REAL::TValueType>(paIN)));
}

inline CIEC_LREAL func_LOG(const CIEC_LREAL &paIN){
  return CIEC_LREAL(log10(static_cast<CIEC_LREAL::TValueType>(paIN)));
}

inline CIEC_REAL func_SIN(const CIEC_REAL &paIN){
  return CIEC_REAL(sinf(static_cast<CIEC_REAL::TValueType>(paIN)));
}

inline CIEC_LREAL func_SIN(const CIEC_LREAL &paIN){
  return CIEC_LREAL(sin(static_cast<CIEC_LREAL::TValueType>(paIN)));
}

inline CIEC_REAL func_COS(const CIEC_REAL &paIN){
  return CIEC_REAL(cosf(static_cast<CIEC_REAL::TValueType>(paIN)));
}

inline CIEC_LREAL func_COS(const CIEC_LREAL &paIN){
  return CIEC_LREAL(cos(static_cast<CIEC_LREAL::TValueType>(paIN)));
}

inline CIEC_REAL func_TAN(const CIEC_REAL &paIN){
    return CIEC_REAL(tanf(static_cast<CIEC_REAL::TValueType>(paIN)));
}

inline CIEC_LREAL func_TAN(const CIEC_LREAL &paIN){
  return CIEC_LREAL(tan(static_cast<CIEC_LREAL::TValueType>(paIN)));
}

inline CIEC_REAL func_ASIN(const CIEC_REAL &paIN){
  return CIEC_REAL(asinf(static_cast<CIEC_REAL::TValueType>(paIN)));
}

inline CIEC_LREAL func_ASIN(const CIEC_LREAL &paIN){
  return CIEC_LREAL(asin(static_cast<CIEC_LREAL::TValueType>(paIN)));
}

inline CIEC_REAL func_ACOS(const CIEC_REAL &paIN){
  return CIEC_REAL(acosf(static_cast<CIEC_REAL::TValueType>(paIN)));
}

inline CIEC_LREAL func_ACOS(const CIEC_LREAL &paIN){
  return CIEC_LREAL(acos(static_cast<CIEC_LREAL::TValueType>(paIN)));
}

inline CIEC_REAL func_ATAN(const CIEC_REAL &paIN){
    return CIEC_REAL(atanf(static_cast<CIEC_REAL::TValueType>(paIN)));
}

inline CIEC_LREAL func_ATAN(const CIEC_LREAL &paIN){
  return CIEC_LREAL(atan(static_cast<CIEC_LREAL::TValueType>(paIN)));
}

inline CIEC_REAL func_EXP(const CIEC_REAL &paIN){
  return CIEC_REAL(expf(static_cast<CIEC_REAL::TValueType>(paIN)));
}

inline CIEC_LREAL func_EXP(const CIEC_LREAL &paIN){
  return CIEC_LREAL(exp(static_cast<CIEC_LREAL::TValueType>(paIN)));
}

template <typename T, typename U>
inline auto func_ATAN2(const T& paY, const U& paX) -> typename forte::core::mpl::get_castable_type_t<T, U> {
  static_assert(std::is_base_of_v<CIEC_ANY_REAL, T>, "T not of ANY_REAL");
  static_assert(std::is_base_of_v<CIEC_ANY_REAL, U>, "U not of ANY_REAL");
  using ReturnType = typename forte::core::mpl::get_castable_type_t<T, U>;
  using XValueType = typename U::TValueType;
  using YValueType = typename T::TValueType;
  using ReturnValueType = typename ReturnType::TValueType;
  const ReturnValueType xValue = static_cast<ReturnValueType>(static_cast<XValueType>(paX));
  const ReturnValueType yValue = static_cast<ReturnValueType>(static_cast<YValueType>(paY));
  return ReturnType(static_cast<ReturnValueType>(std::atan2(yValue, xValue)));
}

template<typename T>
auto func_ROL(const T &paIn, const CIEC_ANY_INT &paN) -> typename forte::core::mpl::get_equivalent_CIEC_class_t<T>  {
  static_assert((std::is_base_of_v<CIEC_ANY_BIT, T>), "T not of ANY_BIT");
  using returnType = typename forte::core::mpl::get_equivalent_CIEC_class_t<T>;
  if((true == paN.isSigned() && 0 <= paN.getSignedValue()) || false == paN.isSigned()) {
    return returnType(static_cast<typename returnType::TValueType>((paIn << paN.getUnsignedValue()) | (paIn >> (sizeof(typename returnType::TValueType) * 8 - paN.getUnsignedValue()))));
  } else {
    DEVLOG_ERROR("value of input N is less than zero\n");
    return returnType(static_cast<typename returnType::TValueType>(0));
  }
}

template<typename T>
auto func_ROR(const T &paIn, const CIEC_ANY_INT &paN) -> typename forte::core::mpl::get_equivalent_CIEC_class_t<T> {
  static_assert((std::is_base_of_v<CIEC_ANY_BIT, T>), "T not of ANY_BIT");
  using returnType = typename forte::core::mpl::get_equivalent_CIEC_class_t<T>;
  if((true == paN.isSigned() && 0 <= paN.getSignedValue()) || false == paN.isSigned()) {
    return returnType(static_cast<typename returnType::TValueType>((paIn >> paN.getUnsignedValue()) | (paIn << (sizeof(typename returnType::TValueType) * 8 - paN.getUnsignedValue()))));
  } else {
    DEVLOG_ERROR("value of input N is less than zero\n");
    return returnType(static_cast<typename returnType::TValueType>(0));
  }
}

template <typename T>
auto func_SHL(const T &paIn, const CIEC_ANY_INT &paN) -> typename forte::core::mpl::get_equivalent_CIEC_class_t<T> {
  static_assert((std::is_base_of_v<CIEC_ANY_BIT, T>), "T not of ANY_BIT");
  using returnType = typename forte::core::mpl::get_equivalent_CIEC_class_t<T>;
  if ((true == paN.isSigned() && 0 <= paN.getSignedValue()) || false == paN.isSigned()) {
    return returnType(static_cast<typename returnType::TValueType>(paIn << paN.getUnsignedValue()));
  } else {
    DEVLOG_ERROR("value of input N is less than zero\n");
    return returnType(static_cast<typename T::TValueType>(0));
  }
}

template<typename T>
auto func_SHR(const T &paIn, const CIEC_ANY_INT &paN) -> typename forte::core::mpl::get_equivalent_CIEC_class_t<T> {
  static_assert((std::is_base_of_v<CIEC_ANY_BIT, T>), "T not of ANY_BIT");
  using returnType = typename forte::core::mpl::get_equivalent_CIEC_class_t<T>;
  if((true == paN.isSigned() && 0 <= paN.getSignedValue()) || false == paN.isSigned()) {
    return returnType(static_cast<typename returnType::TValueType>(paIn >> paN.getUnsignedValue()));
  } else {
    DEVLOG_ERROR("value of input N is less than zero\n");
    return returnType(static_cast<typename returnType::TValueType>(0));
  }
}

template<> auto func_ROL(const CIEC_BOOL &paIn, const CIEC_ANY_INT &paN) -> CIEC_BOOL;

template<> auto func_ROR(const CIEC_BOOL &paIn, const CIEC_ANY_INT &paN) -> CIEC_BOOL;

template<> auto func_SHL(const CIEC_BOOL &paIn, const CIEC_ANY_INT &paN) -> CIEC_BOOL;

template<> auto func_SHR(const CIEC_BOOL &paIn, const CIEC_ANY_INT &paN) -> CIEC_BOOL;

template<typename T, typename U, template<typename A> class F, typename C>
auto APPLY(const T &paIN1, const U &paIN2) -> typename forte::core::mpl::get_castable_type_t<T, U> {
  static_assert(forte::core::mpl::are_of_subtype_v<C, T, U>, "Template instantiation with incompatible types");
  using tImplicitCastType = typename forte::core::mpl::get_castable_type_t<T, U>;
  static_assert(!(std::is_same_v<tImplicitCastType, forte::core::mpl::NullType>), "No implicit cast possible");
  const tImplicitCastType Result(F<tImplicitCastType>::call(static_cast<tImplicitCastType>(paIN1), static_cast<tImplicitCastType>(paIN2)));
  return Result;
}

template<class T, class U>
class AndOperation {
    using resultType = typename forte::core::mpl::get_castable_type_t<T, U>;
  public:
    static resultType call(const T &paIN1, const U &paIN2) {
      return resultType(static_cast<resultType>(paIN1) & static_cast<resultType>(paIN2));
    }
  private:
    AndOperation() = default;
};

template<class T>
class AndOperation<T, CIEC_BOOL> {
    using resultType = typename forte::core::mpl::get_castable_type_t<T, CIEC_BOOL>;
  public:
    static resultType call(const T &paIN1, const CIEC_BOOL &paIN2) {
      return resultType(paIN1 & (paIN2 ? 1 : 0));
    }
  private:
    AndOperation() = default;
};

template<class T>
class AndOperation<CIEC_BOOL, T> {
    using resultType = typename forte::core::mpl::get_castable_type_t<T, CIEC_BOOL>;
  public:
    static resultType call(const CIEC_BOOL &paIN1, const T &paIN2) {
      return resultType((paIN1 ? 1 : 0) & paIN2);
    }
  private:
    AndOperation() = default;
};

template<>
class AndOperation<CIEC_BOOL, CIEC_BOOL> {
  public:
    static CIEC_BOOL call(const CIEC_BOOL &paIN1, const CIEC_BOOL &paIN2) {
      return CIEC_BOOL(paIN1 && paIN2);
    }
  private:
    AndOperation() = default;
};

template<typename T, typename U>
auto func_AND(const T &paIN1, const U &paIN2) -> typename forte::core::mpl::get_castable_type_t<typename forte::core::mpl::get_equivalent_CIEC_class_t<T>, typename forte::core::mpl::get_equivalent_CIEC_class_t<U>> {
    using tTClass = typename forte::core::mpl::get_equivalent_CIEC_class_t<T>;
    using tUClass = typename forte::core::mpl::get_equivalent_CIEC_class_t<U>;
    static_assert(forte::core::mpl::are_of_subtype_v<CIEC_ANY_BIT, tTClass, tUClass>, "Template instantiation with incompatible types");
    using tImplicitCastType = typename forte::core::mpl::get_castable_type_t<tTClass, tUClass>;
    static_assert(!(std::is_same_v<tImplicitCastType, forte::core::mpl::NullType>), "No implicit cast possible");
    return AndOperation<tTClass, tUClass>::call(paIN1, paIN2);
}

template<class T, class U>
class OrOperation {
    using resultType = typename forte::core::mpl::get_castable_type_t<T, U>;
  public:
    static resultType call(const T &paIN1, const U &paIN2) {
      return resultType(static_cast<resultType>(paIN1) | static_cast<resultType>(paIN2));
    }
  private:
    OrOperation() = default;
};

template<class T>
class OrOperation<T, CIEC_BOOL> {
    using resultType = typename forte::core::mpl::get_castable_type_t<T, CIEC_BOOL>;
  public:
    static resultType call(const T &paIN1, const CIEC_BOOL &paIN2) {
      return resultType(paIN1 | (paIN2 ? 1 : 0));
    }
  private:
    OrOperation() = default;
};

template<class T>
class OrOperation<CIEC_BOOL, T> {
    using resultType = typename forte::core::mpl::get_castable_type_t<T, CIEC_BOOL>;
  public:
    static resultType call(const CIEC_BOOL &paIN1, const T &paIN2) {
      return resultType((paIN1 ? 1 : 0) | paIN2);
    }
  private:
    OrOperation() = default;
};

template<>
class OrOperation<CIEC_BOOL, CIEC_BOOL> {
  public:
    static CIEC_BOOL call(const CIEC_BOOL &paIN1, const CIEC_BOOL &paIN2) {
      return CIEC_BOOL(paIN1 || paIN2);
    }
  private:
    OrOperation() = default;
};


template<typename T, typename U>
auto func_OR(const T &paIN1, const U &paIN2) -> typename forte::core::mpl::get_castable_type_t<typename forte::core::mpl::get_equivalent_CIEC_class_t<T>, typename forte::core::mpl::get_equivalent_CIEC_class_t<U>> {
  using tTClass = typename forte::core::mpl::get_equivalent_CIEC_class_t<T>;
  using tUClass = typename forte::core::mpl::get_equivalent_CIEC_class_t<U>;
  static_assert(forte::core::mpl::are_of_subtype_v<CIEC_ANY_BIT, tTClass, tUClass>, "Template instantiation with incompatible types");
  using tImplicitCastType = typename forte::core::mpl::get_castable_type_t<tTClass, tUClass>;
  static_assert(!(std::is_same_v<tImplicitCastType, forte::core::mpl::NullType>), "No implicit cast possible");
  return OrOperation<tTClass, tUClass>::call(paIN1, paIN2);
}
template<class T, class U>
class XorOperation {
  using resultType = typename forte::core::mpl::get_castable_type_t<T, U>;
public:
  static resultType call(const T &paIN1, const U &paIN2)
  {
      return resultType(static_cast<resultType>(paIN1) ^ static_cast<resultType>(paIN2));
    }
  private:
    XorOperation() = default;
};

template<class T>
class XorOperation<T, CIEC_BOOL> {
  using resultType = typename forte::core::mpl::get_castable_type_t<T, CIEC_BOOL>;
  public:
    static resultType call(const T &paIN1, const CIEC_BOOL &paIN2) {
      return resultType(paIN1 ^ (paIN2 ? 1 : 0));
    }
  private:
    XorOperation() = default;
};

template<class T>
class XorOperation<CIEC_BOOL, T> {
    using resultType = typename forte::core::mpl::get_castable_type_t<T, CIEC_BOOL>;
  public:
    static resultType call(const CIEC_BOOL &paIN1, const T &paIN2) {
      return resultType((paIN1 ? 1 : 0) ^ paIN2);
    }
  private:
    XorOperation() = default;
};

template<>
class XorOperation<CIEC_BOOL, CIEC_BOOL> {
  public:
    static CIEC_BOOL call(const CIEC_BOOL &paIN1, const CIEC_BOOL &paIN2) {
      return CIEC_BOOL(paIN1.operator bool() != paIN2.operator bool());
    }
  private:
    XorOperation() = default;
};

template<typename T, typename U>
auto func_XOR(const T &paIN1, const U &paIN2) -> typename forte::core::mpl::get_castable_type_t<typename forte::core::mpl::get_equivalent_CIEC_class_t<T>, typename forte::core::mpl::get_equivalent_CIEC_class_t<U>> {
  using tTClass = typename forte::core::mpl::get_equivalent_CIEC_class_t<T> ;
  using tUClass = typename forte::core::mpl::get_equivalent_CIEC_class_t<U>;
  static_assert(forte::core::mpl::are_of_subtype_v<CIEC_ANY_BIT, tTClass, tUClass>, "Template instantiation with incompatible types");
  using tImplicitCastType = typename forte::core::mpl::get_castable_type_t<tTClass, tUClass>;
  static_assert(!(std::is_same_v<tImplicitCastType, forte::core::mpl::NullType>), "No implicit cast possible");
  return XorOperation<tTClass, tUClass>::call(paIN1, paIN2);
}

template <typename T>
auto func_NOT(const T& paIN) -> typename forte::core::mpl::get_equivalent_CIEC_class_t<T> {
  static_assert((std::is_base_of_v<CIEC_ANY_BIT, T>), "NOT function only for ANY_BIT");
  using tResultType = typename forte::core::mpl::get_equivalent_CIEC_class_t<T>;
  if constexpr (std::is_same_v<tResultType, CIEC_BOOL>) {
    return tResultType(!paIN);
  } else {
    return tResultType(~paIN);
  }
}

template<typename T, typename U, typename ... Args>
CIEC_BOOL func_GT(const T &paIn1, const U &paIn2, const Args& ... args) {
  return CIEC_BOOL(func_GT(paIn1, paIn2) &&  func_GT(paIn2, args...));
}

template<typename T, typename U>
CIEC_BOOL func_GT(const T &paIN1, const U &paIN2) {
  static_assert(forte::core::mpl::are_of_subtype_v<CIEC_ANY_ELEMENTARY, T, U>, "Template instantiation with incompatible types");
  if constexpr (forte::core::mpl::are_of_subtype_v<CIEC_ANY_BIT, T, U>) { //ANY_BITs can be also partial accesses
    using tTClass = typename forte::core::mpl::get_equivalent_CIEC_class_t<T>;
    using tUClass = typename forte::core::mpl::get_equivalent_CIEC_class_t<U>;
    using tImplicitCastType = typename forte::core::mpl::get_castable_type_t<tTClass, tUClass>;
    static_assert(!(std::is_same_v<tImplicitCastType, forte::core::mpl::NullType>), "No implicit cast possible");
    return func_GT<tImplicitCastType>(static_cast<tImplicitCastType>(paIN1), static_cast<tImplicitCastType>(paIN2));
  } else {
    using tImplicitCastType = typename forte::core::mpl::get_castable_type_t<T, U>;
    static_assert(!(std::is_same_v<tImplicitCastType, forte::core::mpl::NullType>), "No implicit cast possible");
    return func_GT<tImplicitCastType>(static_cast<tImplicitCastType>(paIN1), static_cast<tImplicitCastType>(paIN2));
  }
}

template<typename T>
CIEC_BOOL func_GT(const T &paIN1, const T &paIN2) {
  if constexpr (forte::core::mpl::has_greater_v<T>) {
    return CIEC_BOOL(paIN1 > paIN2);
  } else {
    return CIEC_BOOL(static_cast<typename T::TValueType>(paIN1) > static_cast<typename T::TValueType>(paIN2));
  }
}

template<typename T, typename U, typename ... Args>
CIEC_BOOL func_EQ(const T &paIn1, const U &paIn2, const Args& ... args) {
  return CIEC_BOOL(func_EQ(paIn1, paIn2) &&  func_EQ(paIn2, args...));
}

template<typename T, typename U>
CIEC_BOOL func_EQ(const T &paIN1, const U &paIN2) {
  if constexpr (forte::core::mpl::has_equality_v<T, U>) {
    return CIEC_BOOL(paIN1 == paIN2);
  } else if constexpr (forte::core::mpl::are_of_subtype_v<CIEC_ANY_BIT, T, U>) { //ANY_BITs can be also partial accesses
    using tTClass = typename forte::core::mpl::get_equivalent_CIEC_class_t<T>;
    using tUClass = typename forte::core::mpl::get_equivalent_CIEC_class_t<U>;
    using tImplicitCastType = typename forte::core::mpl::get_castable_type_t<tTClass, tUClass>;
    static_assert(!(std::is_same_v<tImplicitCastType, forte::core::mpl::NullType>), "No implicit cast possible");
    return func_EQ<tImplicitCastType>(static_cast<tImplicitCastType>(paIN1), static_cast<tImplicitCastType>(paIN2));
  } else {
    using tImplicitCastType = typename forte::core::mpl::get_castable_type_t<T, U>;
    static_assert(!(std::is_same_v<tImplicitCastType, forte::core::mpl::NullType>), "No implicit cast possible");
    return func_EQ<tImplicitCastType>(static_cast<tImplicitCastType>(paIN1), static_cast<tImplicitCastType>(paIN2));
  }
}

template<typename T>
CIEC_BOOL func_EQ(const T &paIN1, const T &paIN2) {
  if constexpr (forte::core::mpl::has_equality_v<T>) {
    return CIEC_BOOL(paIN1 == paIN2);
  } else {
    return CIEC_BOOL(static_cast<typename T::TValueType>(paIN1) == static_cast<typename T::TValueType>(paIN2));
  }
}

template<typename T, typename U, typename ... Args>
CIEC_BOOL func_GE(const T &paIn1, const U &paIn2, const Args& ... args) {
  return CIEC_BOOL(func_GE(paIn1, paIn2) &&  func_GE(paIn2, args...));
}

template<typename T, typename U>
CIEC_BOOL func_GE(const T &paIN1, const U &paIN2) {
  static_assert(forte::core::mpl::are_of_subtype_v<CIEC_ANY_ELEMENTARY, T, U>, "Template instantiation with incompatible types");
  if constexpr (forte::core::mpl::are_of_subtype_v<CIEC_ANY_BIT, T, U>) { //ANY_BITs can be also partial accesses
    using tTClass = typename forte::core::mpl::get_equivalent_CIEC_class_t<T>;
    using tUClass = typename forte::core::mpl::get_equivalent_CIEC_class_t<U>;
    using tImplicitCastType = typename forte::core::mpl::get_castable_type_t<tTClass, tUClass>;
    static_assert(!(std::is_same_v<tImplicitCastType, forte::core::mpl::NullType>), "No implicit cast possible");
    return func_GE<tImplicitCastType>(static_cast<tImplicitCastType>(paIN1), static_cast<tImplicitCastType>(paIN2));
  } else {
    using tImplicitCastType = typename forte::core::mpl::get_castable_type_t<T, U>;
    static_assert(!(std::is_same_v<tImplicitCastType, forte::core::mpl::NullType>), "No implicit cast possible");
    return func_GE<tImplicitCastType>(static_cast<tImplicitCastType>(paIN1), static_cast<tImplicitCastType>(paIN2));
  }
}

template<typename T>
CIEC_BOOL func_GE(const T &paIN1, const T &paIN2) {
  if constexpr (forte::core::mpl::has_greater_equal_v<T>) {
    return CIEC_BOOL(paIN1 >= paIN2);
  } else {
    return CIEC_BOOL(static_cast<typename T::TValueType>(paIN1) >= static_cast<typename T::TValueType>(paIN2));
  }
}

template<typename T, typename U, typename ... Args>
CIEC_BOOL func_LE(const T &paIn1, const U &paIn2, const Args& ... args) {
  return CIEC_BOOL(func_LE(paIn1, paIn2) &&  func_LE(paIn2, args...));
}

template<typename T, typename U>
CIEC_BOOL func_LE(const T &paIN1, const U &paIN2) {
  static_assert(forte::core::mpl::are_of_subtype_v<CIEC_ANY_ELEMENTARY, T, U>, "Template instantiation with incompatible types");
  if constexpr (forte::core::mpl::are_of_subtype_v<CIEC_ANY_BIT, T, U>) { //ANY_BITs can be also partial accesses
    using tTClass = typename forte::core::mpl::get_equivalent_CIEC_class_t<T>;
    using tUClass = typename forte::core::mpl::get_equivalent_CIEC_class_t<U>;
    using tImplicitCastType = typename forte::core::mpl::get_castable_type_t<tTClass, tUClass>;
    static_assert(!(std::is_same_v<tImplicitCastType, forte::core::mpl::NullType>), "No implicit cast possible");
    return func_LE<tImplicitCastType>(static_cast<tImplicitCastType>(paIN1), static_cast<tImplicitCastType>(paIN2));
  } else {
    using tImplicitCastType = typename forte::core::mpl::get_castable_type_t<T, U>;
    static_assert(!(std::is_same_v<tImplicitCastType, forte::core::mpl::NullType>), "No implicit cast possible");
    return func_LE<tImplicitCastType>(static_cast<tImplicitCastType>(paIN1), static_cast<tImplicitCastType>(paIN2));
  }
}

template<typename T>
CIEC_BOOL func_LE(const T &paIN1, const T &paIN2) {
  if constexpr (forte::core::mpl::has_less_equal_v<T>) {
    return CIEC_BOOL(paIN1 <= paIN2);
  } else {
    return CIEC_BOOL(static_cast<typename T::TValueType>(paIN1) <= static_cast<typename T::TValueType>(paIN2));
  }
}

template<typename T, typename U, typename ... Args>
CIEC_BOOL func_LT(const T &paIn1, const U &paIn2, const Args& ... args) {
  return CIEC_BOOL(func_LT(paIn1, paIn2) &&  func_LT(paIn2, args...));
}

template<typename T, typename U>
CIEC_BOOL func_LT(const T &paIN1, const U &paIN2) {
  static_assert(forte::core::mpl::are_of_subtype_v<CIEC_ANY_ELEMENTARY, T, U>, "Template instantiation with incompatible types");
  if constexpr (forte::core::mpl::are_of_subtype_v<CIEC_ANY_BIT, T, U>) { //ANY_BITs can be also partial accesses
    using tTClass = typename forte::core::mpl::get_equivalent_CIEC_class_t<T>;
    using tUClass = typename forte::core::mpl::get_equivalent_CIEC_class_t<U>;
    using tImplicitCastType = typename forte::core::mpl::get_castable_type_t<tTClass, tUClass>;
    static_assert(!(std::is_same_v<tImplicitCastType, forte::core::mpl::NullType>), "No implicit cast possible");
    return func_LT<tImplicitCastType>(static_cast<tImplicitCastType>(paIN1), static_cast<tImplicitCastType>(paIN2));
  } else {
    using tImplicitCastType = typename forte::core::mpl::get_castable_type_t<T, U>;
    static_assert(!(std::is_same_v<tImplicitCastType, forte::core::mpl::NullType>), "No implicit cast possible");
    return func_LT<tImplicitCastType>(static_cast<tImplicitCastType>(paIN1), static_cast<tImplicitCastType>(paIN2));
  }
}

template<typename T>
CIEC_BOOL func_LT(const T &paIN1, const T &paIN2) {
  if constexpr (forte::core::mpl::has_less_v<T>) {
    return CIEC_BOOL(paIN1 < paIN2);
  } else {
    return CIEC_BOOL(static_cast<typename T::TValueType>(paIN1) < static_cast<typename T::TValueType>(paIN2));
  }
}

template<typename T, typename U>
CIEC_BOOL func_NE(const T &paIN1, const U &paIN2) {
  if constexpr (forte::core::mpl::has_equality_v<T, U>) {
    return CIEC_BOOL(paIN1 != paIN2);
  } else if constexpr (forte::core::mpl::are_of_subtype_v<CIEC_ANY_BIT, T, U>) { //ANY_BITs can be also partial accesses
    using tTClass = typename forte::core::mpl::get_equivalent_CIEC_class_t<T>;
    using tUClass = typename forte::core::mpl::get_equivalent_CIEC_class_t<U>;
    using tImplicitCastType = typename forte::core::mpl::get_castable_type_t<tTClass, tUClass>;
    static_assert(!(std::is_same_v<tImplicitCastType, forte::core::mpl::NullType>), "No implicit cast possible");
    return func_NE<tImplicitCastType>(static_cast<tImplicitCastType>(paIN1), static_cast<tImplicitCastType>(paIN2));
  } else {
    using tImplicitCastType = typename forte::core::mpl::get_castable_type_t<T, U>;
    static_assert(!(std::is_same_v<tImplicitCastType, forte::core::mpl::NullType>), "No implicit cast possible");
    return func_NE<tImplicitCastType>(static_cast<tImplicitCastType>(paIN1), static_cast<tImplicitCastType>(paIN2));
  }
}

template<typename T>
CIEC_BOOL func_NE(const T &paIN1, const T &paIN2) {
  if constexpr (forte::core::mpl::has_inequality_v<T>) {
    return CIEC_BOOL(paIN1 != paIN2);
  } else {
    return CIEC_BOOL(static_cast<typename T::TValueType>(paIN1) != static_cast<typename T::TValueType>(paIN2));
  }
}

template<typename T, typename U>
auto func_SEL(const CIEC_BOOL &G, const T &IN0, const U &IN1) -> typename forte::core::mpl::get_castable_type_t<T, U> {
  return (G.operator bool()) ? IN1 : IN0;
}

template<typename T, typename U,typename... Args>
auto func_MAX(const T &paIN1, const U &paIN2, const Args& ...args) {
  return func_MAX(func_MAX(paIN1, paIN2), args...);
}

GENERATE_APPLY_FUNCTION(func_MAX)
template<typename T, typename U>
auto func_MAX(const T &paIN1, const U &paIN2) -> typename forte::core::mpl::get_castable_type_t<T, U> {
  return APPLY<T, U, func_MAX_Function, CIEC_ANY_ELEMENTARY>(paIN1, paIN2);
}

template<typename T>
T func_MAX(const T &paIN1, const T &paIN2) {
  if(static_cast<typename T::TValueType>(paIN1) > static_cast<typename T::TValueType>(paIN2)) {
    return paIN1;
  } else {
    return paIN2;
  }
}

template<typename T, typename U, typename... Args>
auto func_MIN(const T &paIN1, const U &paIN2, const Args& ...args) {
  return func_MIN(func_MIN(paIN1, paIN2), args...);
}

GENERATE_APPLY_FUNCTION(func_MIN)
template<typename T, typename U>
auto func_MIN(const T &paIN1, const U &paIN2) -> typename forte::core::mpl::get_castable_type_t<T, U> {
  return APPLY<T, U, func_MIN_Function, CIEC_ANY_ELEMENTARY>(paIN1, paIN2);
}

template<typename T>
T func_MIN(const T &paIN1, const T &paIN2) {
  if(static_cast<typename T::TValueType>(paIN1) < static_cast<typename T::TValueType>(paIN2)) {
    return paIN1;
  } else {
    return paIN2;
  }
}

template<typename T, typename U, typename V>
auto func_LIMIT(const T &paMN, const U &paIN, const V &paMX) -> typename forte::core::mpl::get_castable_type_t<typename forte::core::mpl::get_castable_type_t<T, U>, V> {
  using tImplicitType = typename forte::core::mpl::get_castable_type_t<typename forte::core::mpl::get_castable_type_t<T, U>, V>;
  return func_MIN(func_MAX(static_cast<tImplicitType>(paIN), static_cast<tImplicitType>(paMN)), static_cast<tImplicitType>(paMX));
}

GENERATE_APPLY_FUNCTION(func_MOD)
template<typename T, typename U>
auto func_MOD(const T &paIN1, const U &paIN2) -> typename forte::core::mpl::get_castable_type_t<T, U> {
  return APPLY<T, U, func_MOD_Function, CIEC_ANY_INT>(paIN1, paIN2);
}

template<typename T>
T func_MOD(const T &paIN1, const T &paIN2) {
  using ValueType = typename T::TValueType;
  if(0 == static_cast<typename T::TValueType>(paIN2)) {
    return T(0);
  }
  return T(static_cast<ValueType>(paIN1.getSignedValue()) % static_cast<ValueType>(paIN2.getSignedValue()));
}

template<typename T>
T func_MOVE(const T &paIN) {
  return T(paIN);
}

template<typename T, typename U>
T func_EXPT(const T &paIN1, const U &paIN2) {
  static_assert((std::is_base_of_v<CIEC_ANY_REAL, T>), "IN1 not of type ANY_REAL");
  static_assert((std::is_base_of_v<CIEC_ANY_NUM, U>), "IN2 not of type ANY_NUM");
  return T(static_cast<typename T::TValueType>(pow(static_cast<typename T::TValueType>(paIN1), static_cast<typename U::TValueType>(paIN2))));
}

/*************** ADD ********************/

CIEC_TIME func_ADD_TIME(const CIEC_TIME &paIN1, const CIEC_TIME &paIN2);
CIEC_TIME_OF_DAY func_ADD_TOD_TIME(const CIEC_TIME_OF_DAY &paIN1, const CIEC_TIME &paIN2);
CIEC_DATE_AND_TIME func_ADD_DT_TIME(const CIEC_DATE_AND_TIME &paIN1, const CIEC_TIME &paIN2);

CIEC_LTIME func_ADD_LTIME(const CIEC_LTIME &paIN1, const CIEC_LTIME &paIN2);
CIEC_LTIME_OF_DAY func_ADD_LTOD_LTIME(const CIEC_LTIME_OF_DAY &paIN1, const CIEC_LTIME &paIN2);
CIEC_LDATE_AND_TIME func_ADD_LDT_LTIME(const CIEC_LDATE_AND_TIME &paIN1, const CIEC_LTIME &paIN2);

template <class T, class U>
class AddOperation {
  using resultType = typename forte::core::mpl::get_add_operator_result_type_t<T, U>;

public:
  static resultType call(const T &paIN1, const U &paIN2) {
    return resultType(static_cast<typename T::TValueType>(paIN1) + static_cast<typename U::TValueType>(paIN2));
  }
  AddOperation() = delete;
};

template <>
class AddOperation<CIEC_TIME_OF_DAY, CIEC_TIME> {
  using resultType = typename forte::core::mpl::get_add_operator_result_type_t<CIEC_TIME_OF_DAY, CIEC_TIME>;

public:
  static resultType call(const CIEC_TIME_OF_DAY &paIN1, const CIEC_TIME &paIN2) {
    return func_ADD_TOD_TIME(paIN1, paIN2);
  }
  AddOperation() = delete;
};

template <>
class AddOperation<CIEC_DATE_AND_TIME, CIEC_TIME> {
  using resultType = typename forte::core::mpl::get_add_operator_result_type_t<CIEC_DATE_AND_TIME, CIEC_TIME>;

public:
  static resultType call(const CIEC_DATE_AND_TIME &paIN1, const CIEC_TIME &paIN2) {
    return func_ADD_DT_TIME(paIN1, paIN2);
  }
  AddOperation() = delete;
};

template <>
class AddOperation<CIEC_LTIME_OF_DAY, CIEC_LTIME> {
  using resultType = typename forte::core::mpl::get_add_operator_result_type_t<CIEC_LTIME_OF_DAY, CIEC_LTIME>;

public:
  static resultType call(const CIEC_LTIME_OF_DAY &paIN1, const CIEC_LTIME &paIN2) {
    return func_ADD_LTOD_LTIME(paIN1, paIN2);
  }
  AddOperation() = delete;
};

template <>
class AddOperation<CIEC_LDATE_AND_TIME, CIEC_LTIME> {
  using resultType = typename forte::core::mpl::get_add_operator_result_type_t<CIEC_LDATE_AND_TIME, CIEC_LTIME>;

public:
  static resultType call(const CIEC_LDATE_AND_TIME &paIN1, const CIEC_LTIME &paIN2) {
    return func_ADD_LDT_LTIME(paIN1, paIN2);
  }
  AddOperation() = delete;
};

template <typename T, typename U, typename ...Args>
auto func_ADD(const T &paIN1, const U &paIN2, const Args& ...args) {
  static_assert(std::is_base_of_v<CIEC_ANY_NUM, T>, "Variadic ADD only allowed with ANY_NUMs");
  static_assert(std::is_base_of_v<CIEC_ANY_NUM, U>, "Variadic ADD only allowed with ANY_NUMs");
  return func_ADD(func_ADD(paIN1, paIN2), args...);
}

template <typename R = forte::core::mpl::NullType, typename T, typename U>
auto func_ADD(const T &paIN1, const U &paIN2) -> typename forte::core::mpl::get_add_operator_result_type_t<T, U> {
  using deductedType = typename forte::core::mpl::get_add_operator_result_type_t<T, U>;
  if constexpr (!std::is_same_v<R, forte::core::mpl::NullType>) {
    static_assert(std::is_same_v<deductedType, R>, "Deducted type and requested type do not match!\n");
  }
  return AddOperation<T, U>::call(paIN1, paIN2);
}

/*************** MUL ********************/
template <class T, class U>
class MulOperation {
  using resultType = typename forte::core::mpl::get_mul_operator_result_type_t<T, U>;

public:
  static resultType call(const T &paIN1, const U &paIN2) {
    return resultType(static_cast<typename T::TValueType>(paIN1) * static_cast<typename U::TValueType>(paIN2));
  }
  MulOperation() = delete;
};

template <class U>
class MulOperation<CIEC_TIME, U> {
  using resultType = typename forte::core::mpl::get_mul_operator_result_type_t<CIEC_TIME, U>;

public:
  static resultType call(const CIEC_TIME &paIN1, const U &paIN2) {
    return func_MUL_TIME(paIN1, paIN2);
  }
  MulOperation() = delete;
};

template <class U>
class MulOperation<CIEC_LTIME, U> {
  using resultType = typename forte::core::mpl::get_mul_operator_result_type_t<CIEC_LTIME, U>;

public:
  static resultType call(const CIEC_LTIME &paIN1, const U &paIN2) {
    return func_MUL_LTIME(paIN1, paIN2);
  }
  MulOperation() = delete;
};

template <typename T, typename U, typename ...Args>
auto func_MUL(const T &paIN1, const U &paIN2, const Args& ...args) {
  static_assert(std::is_base_of_v<CIEC_ANY_NUM, T>, "Variadic MUL only allowed with ANY_NUMs");
  static_assert(std::is_base_of_v<CIEC_ANY_NUM, U>, "Variadic MUL only allowed with ANY_NUMs");
  return func_MUL(func_MUL(paIN1, paIN2), args...);
}

template <typename R = forte::core::mpl::NullType, typename T, typename U>
auto func_MUL(const T &paIN1, const U &paIN2) -> typename forte::core::mpl::get_mul_operator_result_type_t<T, U> {
  using deductedType = typename forte::core::mpl::get_mul_operator_result_type_t<T, U>;
  if constexpr (!std::is_same_v<R, forte::core::mpl::NullType>) {
    static_assert(std::is_same_v<deductedType, R>, "Deducted type and requested type do not match!\n");
  }
  return MulOperation<T, U>::call(paIN1, paIN2);
}

/*********** SUB *************/
CIEC_TIME func_SUB_TIME(const CIEC_TIME &paIN1, const CIEC_TIME &paIN2);
CIEC_TIME_OF_DAY func_SUB_TOD_TIME(const CIEC_TIME_OF_DAY &paIN1, const CIEC_TIME &paIN2);
CIEC_DATE_AND_TIME func_SUB_DT_TIME(const CIEC_DATE_AND_TIME &paIN1, const CIEC_TIME &paIN2);
CIEC_TIME func_SUB_DT_DT(const CIEC_DATE_AND_TIME &paIN1, const CIEC_DATE_AND_TIME &paIN2);
CIEC_TIME func_SUB_TOD_TOD(const CIEC_TIME_OF_DAY &paIN1, const CIEC_TIME_OF_DAY &paIN2);
CIEC_TIME func_SUB_DATE_DATE(const CIEC_DATE &paIN1, const CIEC_DATE &paIN2);

CIEC_LTIME func_SUB_LTIME(const CIEC_LTIME &paIN1, const CIEC_LTIME &paIN2);
CIEC_LTIME_OF_DAY func_SUB_LTOD_LTIME(const CIEC_LTIME_OF_DAY &paIN1, const CIEC_LTIME &paIN2);
CIEC_LDATE_AND_TIME func_SUB_LDT_LTIME(const CIEC_LDATE_AND_TIME &paIN1, const CIEC_LTIME &paIN2);
CIEC_LTIME func_SUB_LDT_LDT(const CIEC_LDATE_AND_TIME &paIN1, const CIEC_LDATE_AND_TIME &paIN2);
CIEC_LTIME func_SUB_LTOD_LTOD(const CIEC_LTIME_OF_DAY &paIN1, const CIEC_LTIME_OF_DAY &paIN2);
CIEC_LTIME func_SUB_LDATE_LDATE(const CIEC_LDATE &paIN1, const CIEC_LDATE &paIN2);

template <class T, class U>
class SubOperation {
  using resultType = typename forte::core::mpl::get_sub_operator_result_type_t<T, U>;

public:
  static resultType call(const T &paIN1, const U &paIN2) {
    return resultType(static_cast<typename T::TValueType>(paIN1) - static_cast<typename U::TValueType>(paIN2));
  }
  SubOperation() = delete;
};

template <>
class SubOperation<CIEC_TIME_OF_DAY, CIEC_TIME> {
  using resultType = typename forte::core::mpl::get_sub_operator_result_type_t<CIEC_TIME_OF_DAY, CIEC_TIME>;

public:
  static resultType call(const CIEC_TIME_OF_DAY &paIN1, const CIEC_TIME &paIN2) {
    return func_SUB_TOD_TIME(paIN1, paIN2);
  }
  SubOperation() = delete;
};

template <>
class SubOperation<CIEC_DATE_AND_TIME, CIEC_TIME> {
  using resultType = typename forte::core::mpl::get_sub_operator_result_type_t<CIEC_DATE_AND_TIME, CIEC_TIME>;

public:
  static resultType call(const CIEC_DATE_AND_TIME &paIN1, const CIEC_TIME &paIN2) {
    return func_SUB_DT_TIME(paIN1, paIN2);
  }
  SubOperation() = delete;
};

template <>
class SubOperation<CIEC_DATE_AND_TIME, CIEC_DATE_AND_TIME> {
  using resultType = typename forte::core::mpl::get_sub_operator_result_type_t<CIEC_DATE_AND_TIME, CIEC_DATE_AND_TIME>;

public:
  static resultType call(const CIEC_DATE_AND_TIME &paIN1, const CIEC_DATE_AND_TIME &paIN2) {
    return func_SUB_DT_DT(paIN1, paIN2);
  }
  SubOperation() = delete;
};

template <>
class SubOperation<CIEC_TIME_OF_DAY, CIEC_TIME_OF_DAY> {
  using resultType = typename forte::core::mpl::get_sub_operator_result_type_t<CIEC_TIME_OF_DAY, CIEC_TIME_OF_DAY>;

public:
  static resultType call(const CIEC_TIME_OF_DAY &paIN1, const CIEC_TIME_OF_DAY &paIN2) {
    return func_SUB_TOD_TOD(paIN1, paIN2);
  }
  SubOperation() = delete;
};

template <>
class SubOperation<CIEC_DATE, CIEC_DATE> {
  using resultType = typename forte::core::mpl::get_sub_operator_result_type_t<CIEC_DATE, CIEC_DATE>;

public:
  static resultType call(const CIEC_DATE &paIN1, const CIEC_DATE &paIN2) {
    return func_SUB_DATE_DATE(paIN1, paIN2);
  }
  SubOperation() = delete;
};

template <>
class SubOperation<CIEC_LTIME_OF_DAY, CIEC_LTIME> {
  using resultType = typename forte::core::mpl::get_sub_operator_result_type_t<CIEC_LTIME_OF_DAY, CIEC_LTIME>;

public:
  static resultType call(const CIEC_LTIME_OF_DAY &paIN1, const CIEC_LTIME &paIN2) {
    return func_SUB_LTOD_LTIME(paIN1, paIN2);
  }
  SubOperation() = delete;
};

template <>
class SubOperation<CIEC_LDATE_AND_TIME, CIEC_LTIME> {
  using resultType = typename forte::core::mpl::get_sub_operator_result_type_t<CIEC_LDATE_AND_TIME, CIEC_LTIME>;

public:
  static resultType call(const CIEC_LDATE_AND_TIME &paIN1, const CIEC_LTIME &paIN2) {
    return func_SUB_LDT_LTIME(paIN1, paIN2);
  }
  SubOperation() = delete;
};

template <>
class SubOperation<CIEC_LDATE_AND_TIME, CIEC_LDATE_AND_TIME> {
  using resultType = typename forte::core::mpl::get_sub_operator_result_type_t<CIEC_LDATE_AND_TIME, CIEC_LDATE_AND_TIME>;

public:
  static resultType call(const CIEC_LDATE_AND_TIME &paIN1, const CIEC_LDATE_AND_TIME &paIN2) {
    return func_SUB_LDT_LDT(paIN1, paIN2);
  }
  SubOperation() = delete;
};

template <>
class SubOperation<CIEC_LTIME_OF_DAY, CIEC_LTIME_OF_DAY> {
  using resultType = typename forte::core::mpl::get_sub_operator_result_type_t<CIEC_LTIME_OF_DAY, CIEC_LTIME_OF_DAY>;

public:
  static resultType call(const CIEC_LTIME_OF_DAY &paIN1, const CIEC_LTIME_OF_DAY &paIN2) {
    return func_SUB_LTOD_LTOD(paIN1, paIN2);
  }
  SubOperation() = delete;
};

template <>
class SubOperation<CIEC_LDATE, CIEC_LDATE> {
  using resultType = typename forte::core::mpl::get_sub_operator_result_type_t<CIEC_LDATE, CIEC_LDATE>;

public:
  static resultType call(const CIEC_LDATE &paIN1, const CIEC_LDATE &paIN2) {
    return func_SUB_LDATE_LDATE(paIN1, paIN2);
  }
  SubOperation() = delete;
};

template <typename R = forte::core::mpl::NullType, typename T, typename U>
auto func_SUB(const T &paIN1, const U &paIN2) -> typename forte::core::mpl::get_sub_operator_result_type_t<T, U> {
  using deductedType = typename forte::core::mpl::get_sub_operator_result_type_t<T, U>;
  if constexpr (!std::is_same_v<R, forte::core::mpl::NullType>) {
    static_assert(std::is_same_v<deductedType, R>, "Deducted type and requested type do not match!\n");
  }
  return SubOperation<T, U>::call(paIN1, paIN2);
}

template <class T, class U>
class DivOperation {
  using resultType = typename forte::core::mpl::get_castable_type_t<T, U>;

public:
  static resultType call(const T &paIN1, const U &paIN2) {
    if(0 != static_cast<typename U::TValueType>(paIN2)) {
      return resultType(static_cast<typename T::TValueType>(paIN1) / static_cast<typename U::TValueType>(paIN2));
    }
    DEVLOG_ERROR("Division by zero!\n");
    return resultType(0); // Divisor is 0
  }
  DivOperation() = delete;
};

// Time division only works with TIME as dividend
template <class U>
class DivOperation<CIEC_TIME, U> {
  using resultType = typename forte::core::mpl::get_div_operator_result_type_t<CIEC_TIME, U>;

public:
  static resultType call(const CIEC_TIME &paIN1, const U &paIN2) {
    return func_DIV_TIME(paIN1, paIN2);
  }
  DivOperation() = delete;
};

template <class U>
class DivOperation<CIEC_LTIME, U> {
  using resultType =  typename forte::core::mpl::get_div_operator_result_type_t<CIEC_LTIME, U>;

public:
  static resultType call(const CIEC_LTIME &paIN1, const U &paIN2) {
    return func_DIV_LTIME(paIN1, paIN2);
  }
  DivOperation() = delete;
};


template <typename R = forte::core::mpl::NullType, typename T, typename U>
auto func_DIV(const T &paIN1, const U &paIN2) -> typename forte::core::mpl::get_div_operator_result_type_t<T, U> {
  using deductedType = typename forte::core::mpl::get_div_operator_result_type_t<T, U>;
  if constexpr (!std::is_same_v<R, forte::core::mpl::NullType>) {
    static_assert(std::is_same_v<deductedType, R>, "Deducted type and requested type do not match!\n");
  }
  return DivOperation<T, U>::call(paIN1, paIN2);
}

template <typename T>
T func_MINUS(const T& paIN) {
  return paIN.operator-();
}

/**
 * @brief Unary plus function, needed for exported code
 * 
 * @tparam T CIEC data type
 * @param paIN the value
 * @return constexpr T&& return the same object, as it hasn't been modified 
 */
template<typename T>
constexpr T&& func_PLUS(T&& paIN) {
  return static_cast<T&&>(paIN);
}

/**
 * @brief Unary plus function, needed for exported code
 *
 * @tparam T CIEC data type
 * @param paIN the value
 * @return constexpr T - a copy of paIN
 */
template<typename T>
constexpr T func_PLUS(const T& paIN) {
  return paIN;
}

CIEC_SINT func_TRUNC_SINT(const CIEC_REAL &paIN);
CIEC_INT func_TRUNC_INT(const CIEC_REAL &paIN);
CIEC_DINT func_TRUNC_DINT(const CIEC_REAL &paIN);
CIEC_LINT func_TRUNC_LINT(const CIEC_REAL &paIN);
CIEC_USINT func_TRUNC_USINT(const CIEC_REAL &paIN);
CIEC_UINT func_TRUNC_UINT(const CIEC_REAL &paIN);
CIEC_UDINT func_TRUNC_UDINT(const CIEC_REAL &paIN);
CIEC_ULINT func_TRUNC_ULINT(const CIEC_REAL &paIN);

CIEC_SINT func_REAL_TRUNC_SINT(const CIEC_REAL &paIN);
CIEC_INT func_REAL_TRUNC_INT(const CIEC_REAL &paIN);
CIEC_DINT func_REAL_TRUNC_DINT(const CIEC_REAL &paIN);
CIEC_LINT func_REAL_TRUNC_LINT(const CIEC_REAL &paIN);
CIEC_USINT func_REAL_TRUNC_USINT(const CIEC_REAL &paIN);
CIEC_UINT func_REAL_TRUNC_UINT(const CIEC_REAL &paIN);
CIEC_UDINT func_REAL_TRUNC_UDINT(const CIEC_REAL &paIN);
CIEC_ULINT func_REAL_TRUNC_ULINT(const CIEC_REAL &paIN);

//[[deprecated ("Not desired anymore and possible target of removal in the future")]] - attribute cannot be added, so its a comment for now
template <typename T, typename U>
auto func_TRUNC(const U &paIN) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_INT, T> && std::is_base_of_v<CIEC_ANY_REAL, U>, T> {
  return T(static_cast<typename T::TValueType>(static_cast<typename U::TValueType>(paIN)));
}

CIEC_SINT func_TRUNC_SINT(const CIEC_LREAL &paIN);
CIEC_INT func_TRUNC_INT(const CIEC_LREAL &paIN);
CIEC_DINT func_TRUNC_DINT(const CIEC_LREAL &paIN);
CIEC_LINT func_TRUNC_LINT(const CIEC_LREAL &paIN);
CIEC_USINT func_TRUNC_USINT(const CIEC_LREAL &paIN);
CIEC_UINT func_TRUNC_UINT(const CIEC_LREAL &paIN);
CIEC_UDINT func_TRUNC_UDINT(const CIEC_LREAL &paIN);
CIEC_ULINT func_TRUNC_ULINT(const CIEC_LREAL &paIN);

CIEC_SINT func_LREAL_TRUNC_SINT(const CIEC_LREAL &paIN);
CIEC_INT func_LREAL_TRUNC_INT(const CIEC_LREAL &paIN);
CIEC_DINT func_LREAL_TRUNC_DINT(const CIEC_LREAL &paIN);
CIEC_LINT func_LREAL_TRUNC_LINT(const CIEC_LREAL &paIN);
CIEC_USINT func_LREAL_TRUNC_USINT(const CIEC_LREAL &paIN);
CIEC_UINT func_LREAL_TRUNC_UINT(const CIEC_LREAL &paIN);
CIEC_UDINT func_LREAL_TRUNC_UDINT(const CIEC_LREAL &paIN);
CIEC_ULINT func_LREAL_TRUNC_ULINT(const CIEC_LREAL &paIN);

template<typename T>
CIEC_TIME func_MUL_TIME(const CIEC_TIME& paIN1, const T& paIN2){
  using TimeValueType = CIEC_TIME::TValueType;
  using In2ValueType = typename T::TValueType;
  using MulValueType = std::conditional_t<std::is_floating_point_v<In2ValueType>, TForteDFloat, TimeValueType>;

  return CIEC_TIME(static_cast<TimeValueType>(static_cast<MulValueType>(static_cast<TimeValueType>(paIN1)) * static_cast<In2ValueType>(paIN2)));
}

template<typename T>
CIEC_LTIME func_MUL_LTIME(const CIEC_LTIME &paIN1, const T &paIN2) {
  using LTimeValueType = CIEC_LTIME::TValueType;
  using In2ValueType = typename T::TValueType;
  using MulValueType = std::conditional_t<std::is_floating_point_v<In2ValueType>, TForteDFloat, LTimeValueType>;

  return CIEC_LTIME(static_cast<LTimeValueType>(static_cast<MulValueType>(static_cast<LTimeValueType>(paIN1)) * static_cast<In2ValueType>(paIN2)));
}

template<typename T>
CIEC_TIME func_DIV_TIME(const CIEC_TIME& paIN1, const T& paIN2) {
  using TimeValueType = CIEC_TIME::TValueType;
  using In2ValueType = typename T::TValueType;
  using MulValueType = std::conditional_t<std::is_floating_point_v<In2ValueType>, TForteDFloat, TimeValueType>;

  if(0 != static_cast<In2ValueType>(paIN2)) {
    return CIEC_TIME(static_cast<TimeValueType>(static_cast<MulValueType>(static_cast<TimeValueType>(paIN1)) / static_cast<In2ValueType>(paIN2)));
  } else {
    DEVLOG_ERROR("Division by zero!\n");
    return CIEC_TIME(0);
  }
}

template<typename T>
CIEC_LTIME func_DIV_LTIME(const CIEC_LTIME &paIN1, const T &paIN2) {
  using LTimeValueType = CIEC_LTIME::TValueType;
  using In2ValueType = typename T::TValueType;
  using MulValueType = std::conditional_t<std::is_floating_point_v<In2ValueType>, TForteDFloat, LTimeValueType>;

  if(0 != static_cast<In2ValueType>(paIN2)) {
    return CIEC_LTIME(static_cast<LTimeValueType>(static_cast<MulValueType>(static_cast<LTimeValueType>(paIN1)) / static_cast<In2ValueType>(paIN2)));
  } else {
    DEVLOG_ERROR("Division by zero!\n");
    return CIEC_LTIME(0);
  }
}

template<typename T, typename U>
T func_LEN(const U& paVal){
  static_assert(std::is_base_of_v<CIEC_ANY_INT, T>, "T not of ANY_INT");
  static_assert(std::is_base_of_v<CIEC_ANY_STRING, U>, "T not of ANY_STRING");
  return T(static_cast<typename T::TValueType>(paVal.length()));
}

template<typename T>
T func_LEFT(const T &paIn, const CIEC_ANY_INT &paL) {
  static_assert(std::is_base_of_v<CIEC_ANY_STRING, T>, "T not of ANY_STRING");
  if(true == paL.isSigned() && 0 > paL.getSignedValue()) {
    DEVLOG_ERROR("value of input L is less than zero\n");
    return paIn;
  } else {
    if(paIn.length() < paL.getUnsignedValue()) {
      DEVLOG_ERROR("string shorter than input L\n");
      return paIn;
    } else {
      if constexpr (std::is_same_v<CIEC_STRING,T>) {
        return CIEC_STRING(paIn.getStorage().substr(0, paL.getUnsignedValue()));
      } else {
        T temp;
        temp.reserve(static_cast<TForteUInt16>(paL.getUnsignedValue()));
        memcpy(temp.getValue(), paIn.getValue(), static_cast<TForteUInt16>(paL.getUnsignedValue()));
        temp.getValue()[paL.getUnsignedValue()] = '\0';
        temp.assign(temp.getValue(), static_cast<TForteUInt16>(paL.getUnsignedValue()));
        return temp;
      }
    }
  }
}

template<typename T>
T func_RIGHT(const T &paIn, const CIEC_ANY_INT &paL) {
  static_assert(std::is_base_of_v<CIEC_ANY_STRING, T>, "T not of ANY_STRING");
  if(true == paL.isSigned() && 0 > paL.getSignedValue()) {
    DEVLOG_ERROR("value of input L is less than zero\n");
    return paIn;
  } else {
    if(paIn.length() < paL.getUnsignedValue()) {
      DEVLOG_ERROR("string shorter than input L\n");
      return paIn;
    } else {
      if constexpr (std::is_same_v<CIEC_STRING,T>) {
        const CIEC_STRING::storage_type &storage = paIn.getStorage();
        return CIEC_STRING(storage.substr(storage.length() - paL.getUnsignedValue()));
      } else {
        T temp;
        temp.reserve(static_cast<TForteUInt16>(paL.getUnsignedValue()));
        memcpy(temp.getValue(), paIn.getValue() + (paIn.length() - static_cast<TForteUInt16>(paL.getUnsignedValue())),
          static_cast<TForteUInt16>(paL.getUnsignedValue()));
        temp.getValue()[paL.getUnsignedValue()] = '\0';
        temp.assign(temp.getValue(), static_cast<TForteUInt16>(paL.getUnsignedValue()));
        return temp;
      }
    }
  }
}

template<typename T>
T func_MID(const T &paIn, const CIEC_ANY_INT &paL, const CIEC_ANY_INT &paP) {
  static_assert(std::is_base_of_v<CIEC_ANY_STRING, T>, "T not of ANY_STRING");
  if(true == paP.isSigned() && 0 > paP.getSignedValue()) {
    DEVLOG_ERROR("value of input P is less than zero\n");
    return paIn;
  } else {
    CIEC_INT lenRight = CIEC_INT(static_cast<CIEC_INT::TValueType>(paIn.length() - paP.getUnsignedValue() + 1));
    CIEC_INT lenLeft = CIEC_INT(static_cast<CIEC_INT::TValueType>(paL.getUnsignedValue()));
    return func_LEFT(func_RIGHT(paIn, lenRight), lenLeft);
  }
}

template<typename T, typename U>
auto func_CONCAT(const T &paIn1, const U &paIn2) -> typename forte::core::mpl::get_concat_result_type_t<T, U> {
  using Returntype = typename forte::core::mpl::get_concat_result_type_t<T, U>;
  static_assert((std::is_base_of_v<CIEC_ANY_CHARS, T>), "T not of ANY_CHARS");
  static_assert((std::is_base_of_v<CIEC_ANY_CHARS, U>), "U not of ANY_CHARS");
  static_assert((std::is_base_of_v<CIEC_ANY_CHARS, Returntype>), "Returntype not of ANY_CHARS");
  Returntype temp(paIn1);
  if constexpr (std::is_base_of_v<CIEC_STRING, Returntype>) {
    temp.append(paIn2);
    return temp;
  } else {
    temp.reserve(static_cast<TForteUInt16>(paIn1.length() + paIn2.length()));
    temp.append(paIn2.getValue(), paIn2.length());
    return temp;
  }
}

template<typename T, typename ... Args>
auto func_CONCAT(const T &paIn1, const Args& ... args) {
  return func_CONCAT(paIn1, func_CONCAT(args...));
}

template<typename T>
T func_INSERT(const T &paIn1, const T &paIn2, const CIEC_ANY_INT &paP) {
  static_assert(std::is_base_of_v<CIEC_ANY_STRING, T>);
  if(std::numeric_limits<CIEC_UINT::TValueType>::max() < (paIn1.length() + paIn2.length())) {
    DEVLOG_ERROR("result would be longer than maximum allowed length\n");
    return paIn1;
  }
  const CIEC_ANY::TLargestUIntValueType P = paP.isSigned() ? static_cast<CIEC_ANY::TLargestUIntValueType>(std::max(CIEC_ANY::TLargestIntValueType(0), paP.getSignedValue())) : paP.getUnsignedValue();

  if(P == 0) {
    DEVLOG_ERROR("INSERT called with P equal or lower than 0!\n");
    return paIn1;
  }
  
  if(P > paIn1.length()) {
    DEVLOG_ERROR("INSERT called with P exceeding input string length!\n");
    return paIn1;
  }
  CIEC_INT positionRight = CIEC_INT(static_cast<CIEC_INT::TValueType>(paIn1.length() - paP.getSignedValue()));
  return func_CONCAT(func_CONCAT(func_LEFT(paIn1, paP), paIn2), func_RIGHT(paIn1, positionRight));
}

template<typename T>
T func_DELETE(const T &paIn, const CIEC_ANY_INT &paL, const CIEC_ANY_INT &paP) {
  static_assert(std::is_base_of_v<CIEC_ANY_STRING, T>);
  const CIEC_ANY::TLargestUIntValueType L = paL.isSigned() ? static_cast<CIEC_ANY::TLargestUIntValueType>(std::max(CIEC_ANY::TLargestIntValueType(0), paL.getSignedValue())) : paL.getUnsignedValue();

  const CIEC_ANY::TLargestUIntValueType P = paP.isSigned() ? static_cast<CIEC_ANY::TLargestUIntValueType>(std::max(CIEC_ANY::TLargestIntValueType(0), paP.getSignedValue())) : paP.getUnsignedValue();

  if(L == 0) {
    DEVLOG_ERROR("DELETE called with L equal or less than 0!\n");
    return paIn;
  }

  if(P == 0) {
    DEVLOG_ERROR("DELETE called with P equal or less than 0!\n");
    return paIn;
  }

  if((P + L) > paIn.length()) {
    DEVLOG_ERROR("DELETE called with delete length exceeding the length of string!\n");
    return paIn;
  }

  CIEC_UINT positionRight = CIEC_UINT(static_cast<CIEC_UINT::TValueType>(paIn.length() - (L + P - 1)));
  CIEC_UINT positionLeft = CIEC_UINT(static_cast<CIEC_UINT::TValueType>(P - 1));
  return func_CONCAT(func_LEFT(paIn, positionLeft), func_RIGHT(paIn, positionRight));
}

template<typename T>
T func_REPLACE(const T &paIn1, const T &paIn2, const CIEC_ANY_INT &paL, const CIEC_ANY_INT &paP) {
  static_assert(std::is_base_of_v<CIEC_ANY_STRING, T>);
  const CIEC_ANY::TLargestUIntValueType L = paL.isSigned() ? static_cast<CIEC_ANY::TLargestUIntValueType>(std::max(CIEC_ANY::TLargestIntValueType(0), paL.getSignedValue())) : paL.getUnsignedValue();
  const CIEC_ANY::TLargestUIntValueType P = paP.isSigned() ? static_cast<CIEC_ANY::TLargestUIntValueType>(std::max(CIEC_ANY::TLargestIntValueType(0), paP.getSignedValue())) : paP.getUnsignedValue();

  if(L == 0) {
    DEVLOG_ERROR("REPLACE called with L equal or less to 0!\n");
    return paIn1;
  }

  if(P == 0) {
    DEVLOG_ERROR("REPLACE called with P equal or less to 0!\n");
    return paIn1;
  }

  if((P + L - 1) > paIn1.length()) { //STRINGs start at index 1, so we need to subtract 1
    DEVLOG_ERROR("REPLACE outside string boundaries!\n");
    return paIn1;
  }

  if((P + L + paIn2.length()) > std::numeric_limits<CIEC_UINT::TValueType>::max()) {
    DEVLOG_ERROR("REPLACE exceeds length of string!\n");
  }

  CIEC_INT positionRight = CIEC_INT(static_cast<CIEC_INT::TValueType>(paIn1.length() - (L + P - 1)));
  CIEC_INT positionLeft = CIEC_INT(static_cast<CIEC_INT::TValueType>(P - 1));
  return func_CONCAT(func_CONCAT(func_LEFT(paIn1, positionLeft), paIn2), func_RIGHT(paIn1, positionRight));
}

template <typename T, typename U, typename V>
T func_FIND(const U &paIn1, const V &paIn2) {
  static_assert(std::is_base_of_v<CIEC_ANY_INT, T>, "result must be of type CIEC_ANY_INT");
  static_assert(std::is_base_of_v<CIEC_ANY_STRING, U>, "paIn1 must be of type CIEC_ANY_STRING");
  static_assert(std::is_base_of_v<CIEC_ANY_CHARS, V>, "paIn2 must be of type CIEC_ANY_CHARS");
  if constexpr(std::is_base_of_v<U, CIEC_STRING>) {
    static_assert(std::is_base_of_v<V, CIEC_STRING> || std::is_same_v<V, CIEC_CHAR>, "FIND in STRING only with STRING or CHAR");
    if constexpr(std::is_base_of_v<V, CIEC_STRING>) {
      const auto findIndex = paIn1.getStorage().find(paIn2.getStorage());
      if (findIndex != std::string::npos) {
        return T(static_cast<typename T::TValueType>(findIndex + 1));
      }
    }
    else if constexpr (std::is_same_v<V, CIEC_CHAR>) {
      const auto findIndex = paIn1.getStorage().find(static_cast<CIEC_CHAR::TValueType>(paIn2));
      if (findIndex != std::string::npos) {
        return T(static_cast<typename T::TValueType>(findIndex + 1));
      }   
    }
    return T(0);
  } else if constexpr(std::is_same_v<U, CIEC_WSTRING>) {
    static_assert(std::is_same_v<V, CIEC_WSTRING> || std::is_same_v<V, CIEC_WCHAR>, "FIND in WSTRING only with WSTRING or WCHAR");
    if constexpr(std::is_same_v<V, CIEC_WSTRING>) {
      const char* pc_Find = strstr(paIn1.getValue(), paIn2.getValue());
      if (nullptr != pc_Find){
        return T(static_cast<typename T::TValueType>(pc_Find - paIn1.getValue() + 1));
      }
    } else if constexpr(std::is_same_v<V, CIEC_WCHAR>) {
      const char* pc_Find = strstr(paIn1.getValue(), static_cast<CIEC_WCHAR::TValueType>(paIn2));
      if (nullptr != pc_Find){
        return T(static_cast<typename T::TValueType>(pc_Find - paIn1.getValue() + 1));
      }
    }
    return T(0);
  }
}

template <typename T>
T func_TOUPPER(const T &paIn) {
  static_assert(std::is_base_of_v<CIEC_ANY_STRING, T>, "Operand must be of type ANY_STRING!");
  if constexpr (std::is_base_of_v<CIEC_STRING, T>) {
    CIEC_STRING::storage_type buffer(paIn.getStorage());
    std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::toupper);
    return CIEC_STRING(buffer);
  } else {
    T temp(paIn);
    char *current = temp.getValue();
    for(size_t i = 0; i <= paIn.length(); ++i) {
      current[i] = static_cast<char>(toupper(current[i]));
    }
    return temp;
  }
}

template <typename T>
T func_TOLOWER(const T &paIn) {
  static_assert(std::is_base_of_v<CIEC_ANY_STRING, T>, "Operand must be of type ANY_STRING!");
  if constexpr (std::is_base_of_v<CIEC_STRING, T>) {
    CIEC_STRING::storage_type buffer(paIn.getStorage());
    std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
    return CIEC_STRING(buffer);
  } else {
    T temp(paIn);
    char *current = temp.getValue();
    for(size_t i = 0; i <= paIn.length(); ++i) {
      current[i] = static_cast<char>(tolower(current[i]));
    }
    return temp;
  }
}

CIEC_DATE_AND_TIME func_CONCAT_DATE_TOD(const CIEC_DATE &paIN1, const CIEC_TIME_OF_DAY &paIN2);

CIEC_DATE func_CONCAT_DATE(const CIEC_ANY_INT &YEAR, const CIEC_ANY_INT &MONTH, const CIEC_ANY_INT &DAY);

CIEC_DATE_AND_TIME func_CONCAT_DT(const CIEC_ANY_INT &YEAR, const CIEC_ANY_INT &MONTH, const CIEC_ANY_INT &DAY, const CIEC_ANY_INT &HOUR, const CIEC_ANY_INT &MINUTE, const CIEC_ANY_INT &SECOND, const CIEC_ANY_INT &MILLISECOND);

CIEC_TIME_OF_DAY func_CONCAT_TOD(const CIEC_ANY_INT &HOUR, const CIEC_ANY_INT &MINUTE, const CIEC_ANY_INT &SECOND, const CIEC_ANY_INT &MILLISECOND);

CIEC_LDATE_AND_TIME func_CONCAT_LDATE_LTOD(const CIEC_LDATE &paIN1, const CIEC_LTIME_OF_DAY &paIN2);

CIEC_LDATE func_CONCAT_LDATE(const CIEC_ANY_INT &YEAR, const CIEC_ANY_INT &MONTH, const CIEC_ANY_INT &DAY);

CIEC_LDATE_AND_TIME func_CONCAT_LDT(const CIEC_ANY_INT &YEAR, const CIEC_ANY_INT &MONTH, const CIEC_ANY_INT &DAY, const CIEC_ANY_INT &HOUR, const CIEC_ANY_INT &MINUTE, const CIEC_ANY_INT &SECOND, const CIEC_ANY_INT &MILLISECOND);

CIEC_LTIME_OF_DAY func_CONCAT_LTOD(const CIEC_ANY_INT &HOUR, const CIEC_ANY_INT &MINUTE, const CIEC_ANY_INT &SECOND, const CIEC_ANY_INT &MILLISECOND);

void func_SPLIT_DATE(const CIEC_DATE &paValue, CIEC_ANY_INT &YEAR, CIEC_ANY_INT &MONTH, CIEC_ANY_INT &DAY);

void func_SPLIT_LDATE(const CIEC_LDATE &paValue, CIEC_ANY_INT &YEAR, CIEC_ANY_INT &MONTH, CIEC_ANY_INT &DAY);

void func_SPLIT_TOD(const CIEC_TIME_OF_DAY &paValue, CIEC_ANY_INT &HOUR, CIEC_ANY_INT &MINUTE, CIEC_ANY_INT &SECOND, CIEC_ANY_INT &MILLISECOND);

void func_SPLIT_LTOD(const CIEC_LTIME_OF_DAY &paValue, CIEC_ANY_INT &HOUR, CIEC_ANY_INT &MINUTE, CIEC_ANY_INT &SECOND, CIEC_ANY_INT &MILLISECOND);

void func_SPLIT_DT(const CIEC_DATE_AND_TIME &paValue, CIEC_ANY_INT &YEAR, CIEC_ANY_INT &MONTH, CIEC_ANY_INT &DAY, CIEC_ANY_INT &HOUR, CIEC_ANY_INT &MINUTE, CIEC_ANY_INT &SECOND, CIEC_ANY_INT &MILLISECOND);

void func_SPLIT_LDT(const CIEC_LDATE_AND_TIME &paValue, CIEC_ANY_INT &YEAR, CIEC_ANY_INT &MONTH, CIEC_ANY_INT &DAY, CIEC_ANY_INT &HOUR, CIEC_ANY_INT &MINUTE, CIEC_ANY_INT &SECOND, CIEC_ANY_INT &MILLISECOND);

/** @brief Get day of the week Sunday = 0, 1 = Monday, etc
 * 
 * This function differs from the standard in taking an LDATE, which can be implicitly cast from a DATE
 */
template<typename T>
T func_DAY_OF_WEEK(const CIEC_LDATE &paValue) {
  static_assert(std::is_base_of_v<CIEC_ANY_INT, T>, "T not of ANY_INT");
  struct tm timeStruct;
  paValue.getTimeStruct(&timeStruct);
  return T(static_cast<typename T::TValueType>(timeStruct.tm_wday));
}

/**
 * @brief returns current monotonic clock value as time span in nanoseconds
 *
 * @return CIEC_TIME time span since monotonic clock start
 */
CIEC_TIME func_NOW_MONOTONIC();

/**
 * @brief returns current local date and time - may be subject to time jumps
 *
 * @return CIEC_DATE_AND_TIME of the current local time
 */
CIEC_DATE_AND_TIME func_NOW();

/**
 * @brief Return if an ANY_REAL is a valid number
 * 
 * @tparam T Needs to be a subtype of CIEC_ANY_REAL
 * @param paValue The value to be checked
 * @return CIEC_BOOL false if inf or NaN, true otherwise
 */
template <typename T>
CIEC_BOOL func_IS_VALID(const T& paValue) {
  static_assert((std::is_base_of_v<CIEC_ANY_REAL, T>), "T not of ANY_REAL");
  const typename T::TValueType value = static_cast<typename T::TValueType>(paValue);
  return CIEC_BOOL(!(std::isnan(value) || std::isinf(value)));
}

/**
 * @brief Checks if the ANY_BIT contains a valid BCD number
 *
 * @tparam T Needs to be a subtype of CIEC_ANY_BIT
 * @param paValue The value to be checked
 * @return CIEC_BOOL false if not a valid BCD, true otherwise
 */
template <typename T>
CIEC_BOOL func_IS_VALID_BCD(const T& paValue) {
  static_assert(std::is_base_of_v<CIEC_ANY_BIT, T>, "Operand must be of ANY_BIT (excluding BOOL)"); // any bit type is allowed
  static_assert(!std::is_same_v<CIEC_BOOL, T>, "Operand must be of ANY_BIT, but not BOOL"); // but not BOOL
  using ValueType = typename T::TValueType;
  constexpr size_t valueTypeSize = sizeof(ValueType);
  constexpr ValueType mask = 0x0F;
  constexpr size_t nibble = 4;
  const ValueType value = static_cast<ValueType>(paValue);
  for (size_t i = 0U; i < valueTypeSize; i++) {
    const size_t bitShift = i * 8;
    if (((value >> bitShift) & mask) > 9U || ((value >> (bitShift + nibble)) & mask) > 9U) {
      return CIEC_BOOL(false);
    }
  }
  return CIEC_BOOL(true);
}

template <typename T>
T swapSimpleDataHelper(const T data) {
  constexpr size_t dataSize = sizeof(T);
  const char *const dataBytes = reinterpret_cast<const char *>(&data);
  T swappedData;
  char *const swappedDataBytes = reinterpret_cast<char*>(&swappedData);

  if constexpr (1 == dataSize) {
    return T(data);
  } else if constexpr(2 == dataSize) {
    *(swappedDataBytes) = *(dataBytes + 1);
    *(swappedDataBytes + 1) = *(dataBytes);
  } else if constexpr(4 == dataSize) {
    *(swappedDataBytes + 0) = *(dataBytes + 3);
    *(swappedDataBytes + 1) = *(dataBytes + 2);
    *(swappedDataBytes + 2) = *(dataBytes + 1);
    *(swappedDataBytes + 3) = *(dataBytes + 0);
  } else if constexpr(8 == dataSize) {
    *(swappedDataBytes + 0) = *(dataBytes + 7);
    *(swappedDataBytes + 1) = *(dataBytes + 6);
    *(swappedDataBytes + 2) = *(dataBytes + 5);
    *(swappedDataBytes + 3) = *(dataBytes + 4);
    *(swappedDataBytes + 4) = *(dataBytes + 3);
    *(swappedDataBytes + 5) = *(dataBytes + 2);
    *(swappedDataBytes + 6) = *(dataBytes + 1);
    *(swappedDataBytes + 7) = *(dataBytes + 0);
  } else {
    static_assert(true, "Size of data is unhandled");
  }
  return swappedData;
}

template <typename T>
auto swapEndianess(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_MAGNITUDE, T>, T> {
  const typename T::TValueType data = static_cast<typename T::TValueType>(paValue);
  typename T::TValueType swappedData = swapSimpleDataHelper(data);
  return T(swappedData);
}

template <typename T>
auto swapEndianess(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_BIT, T>, T> {
  const typename T::TValueType data = static_cast<typename T::TValueType>(paValue);
  typename T::TValueType swappedData = swapSimpleDataHelper(data);
  return T(swappedData);
}

template <typename T>
auto swapEndianess(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_CHAR, T>, T> {
  const typename T::TValueType data = static_cast<typename T::TValueType>(paValue);
  typename T::TValueType swappedData = swapSimpleDataHelper(data);
  return T(swappedData);
}

template <typename T>
auto swapEndianess(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_DATE, T>, T> {
  const typename T::TValueType data = static_cast<typename T::TValueType>(paValue);
  typename T::TValueType swappedData = swapSimpleDataHelper(data);
  return T(swappedData);
}

template <typename T>
auto swapEndianess(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_STRING, T>, T> {
  if constexpr (std::is_same_v<CIEC_STRING, T>) {
    return T(paValue);
  } else if constexpr (std::is_same_v<CIEC_WSTRING, T>) {
    T reversed(paValue);
    const TForteUInt16 length = reversed.length();
    for(TForteUInt16 i = 0; i < length; i += sizeof(typename T::TSymbolType)) {
      *(reversed.getValue() + i) = *(paValue.getValue() + (i + 1));
      *(reversed.getValue() + (i + 1)) = *(paValue.getValue() + i);
    }
    return reversed;
  } else {
    static_assert(true, "Unhandled/unknown subtype of CIEC_ANY_STRING");
  }
}

void swapEndianessInplace(CIEC_ARRAY &paValue);

void swapEndianessInplace(CIEC_STRUCT &paValue);

template <typename T>
auto swapEndianess(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_STRUCT, T>, T> {
  T reversed(paValue);
  swapEndianessInplace(reversed);
  return reversed;
}

template <template <typename, intmax_t, intmax_t> typename T, typename U, intmax_t lowerBound, intmax_t upperBound>
auto swapEndianess(const T<U, lowerBound, upperBound> &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ARRAY_FIXED<U, lowerBound, upperBound>, T<U, lowerBound, upperBound>>, T<U, lowerBound, upperBound>> {
  T<U, lowerBound, upperBound> reversed(paValue);
  for (auto iter = reversed.begin(); iter != reversed.end(); iter++) {
    *iter = swapEndianess(*iter);
  }
  return reversed;
}

template <template <typename> typename T, typename U>
auto swapEndianess(const T<U> &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ARRAY_VARIABLE<U>, T<U>>, T<U>> {
  T<U> reversed(paValue);
  for (auto iter = reversed.begin(); iter != reversed.end(); iter++) {
    *iter = swapEndianess(*iter);
  }
  return reversed;
}

#ifdef FORTE_LITTLE_ENDIAN
template <typename T>
T func_TO_LITTLE_ENDIAN(const T &paValue) {
  return paValue;
}

template <typename T>
T func_FROM_LITTLE_ENDIAN(const T &paValue) {
  return paValue;
}

template <typename T>
auto func_TO_BIG_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_MAGNITUDE, T>, T> {
  return swapEndianess(paValue);
}

template <typename T>
auto func_TO_BIG_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_BIT, T>, T> {
  return swapEndianess(paValue);
}

template <typename T>
auto func_TO_BIG_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_CHAR, T>, T> {
  return swapEndianess(paValue);
}

template <typename T>
auto func_TO_BIG_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_DATE, T>, T> {
  return swapEndianess(paValue);
}

template <typename T>
auto func_TO_BIG_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_STRING, T>, T> {
  return swapEndianess(paValue);
}

CIEC_ARRAY_DYNAMIC func_TO_BIG_ENDIAN(const CIEC_ARRAY_DYNAMIC &paValue);

template <typename T>
auto func_TO_BIG_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_STRUCT, T>, T> {
  return swapEndianess(paValue);
}

template <template <typename, intmax_t, intmax_t> typename T, typename U, intmax_t lowerBound, intmax_t upperBound>
auto func_TO_BIG_ENDIAN(const T<U, lowerBound, upperBound> &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ARRAY_FIXED<U, lowerBound, upperBound>, T<U, lowerBound, upperBound>>, T<U, lowerBound, upperBound>> {
  return swapEndianess(paValue);
}

template <template <typename> typename T, typename U>
auto func_TO_BIG_ENDIAN(const T<U> &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ARRAY_VARIABLE<U>, T<U>>, T<U>> {
  return swapEndianess(paValue);
}

template <typename T>
auto func_FROM_BIG_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_MAGNITUDE, T>, T> {
  return swapEndianess(paValue);
}

template <typename T>
auto func_FROM_BIG_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_BIT, T>, T> {
  return swapEndianess(paValue);
}

template <typename T>
auto func_FROM_BIG_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_CHAR, T>, T> {
  return swapEndianess(paValue);
}

template <typename T>
auto func_FROM_BIG_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_DATE, T>, T> {
  return swapEndianess(paValue);
}

template <typename T>
auto func_FROM_BIG_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_STRING, T>, T> {
  return swapEndianess(paValue);
}

CIEC_ARRAY_DYNAMIC func_FROM_BIG_ENDIAN(const CIEC_ARRAY_DYNAMIC &paValue);

template <typename T>
auto func_FROM_BIG_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_STRUCT, T>, T> {
  return swapEndianess(paValue);
}

template <template <typename, intmax_t, intmax_t> typename T, typename U, intmax_t lowerBound, intmax_t upperBound>
auto func_FROM_BIG_ENDIAN(const T<U, lowerBound, upperBound> &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ARRAY_FIXED<U, lowerBound, upperBound>, T<U, lowerBound, upperBound>>, T<U, lowerBound, upperBound>> {
  return swapEndianess(paValue);
}

template <template <typename> typename T, typename U>
auto func_FROM_BIG_ENDIAN(const T<U> &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ARRAY_VARIABLE<U>, T<U>>, T<U>> {
  return swapEndianess(paValue);
}
#endif

#ifdef FORTE_BIG_ENDIAN
template <typename T>
auto func_TO_LITTLE_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_MAGNITUDE, T>, T> {
  return swapEndianess(paValue);
}

template <typename T>
auto func_TO_LITTLE_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_BIT, T>, T> {
  return swapEndianess(paValue);
}

template <typename T>
auto func_TO_LITTLE_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_CHAR, T>, T> {
  return swapEndianess(paValue);
}

template <typename T>
auto func_TO_LITTLE_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_DATE, T>, T> {
  return swapEndianess(paValue);
}

template <typename T>
auto func_TO_LITTLE_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_STRING, T>, T> {
  return swapEndianess(paValue);
}

CIEC_ARRAY_DYNAMIC func_TO_LITTLE_ENDIAN(const CIEC_ARRAY_DYNAMIC &paValue);

template <typename T>
auto func_TO_LITTLE_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_STRUCT, T>, T> {
  return swapEndianess(paValue);
}

template <template <typename, intmax_t, intmax_t> typename T, typename U, intmax_t lowerBound, intmax_t upperBound>
auto func_TO_LITTLE_ENDIAN(const T<U, lowerBound, upperBound> &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ARRAY_FIXED<U, lowerBound, upperBound>, T<U, lowerBound, upperBound>>, T<U, lowerBound, upperBound>> {
  return swapEndianess(paValue);
}

template <template <typename> typename T, typename U>
auto func_TO_LITTLE_ENDIAN(const T<U> &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ARRAY_VARIABLE<U>, T<U>>, T<U>> {
  return swapEndianess(paValue);
}

template <typename T>
auto func_FROM_LITTLE_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_MAGNITUDE, T>, T> {
  return swapEndianess(paValue);
}

template <typename T>
auto func_FROM_LITTLE_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_BIT, T>, T> {
  return swapEndianess(paValue);
}

template <typename T>
auto func_FROM_LITTLE_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_CHAR, T>, T> {
  return swapEndianess(paValue);
}

template <typename T>
auto func_FROM_LITTLE_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_DATE, T>, T> {
  return swapEndianess(paValue);
}

template <typename T>
auto func_FROM_LITTLE_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ANY_STRING, T>, T> {
  return swapEndianess(paValue);
}

CIEC_ARRAY_DYNAMIC func_FROM_LITTLE_ENDIAN(const CIEC_ARRAY_DYNAMIC &paValue);

template <typename T>
auto func_FROM_LITTLE_ENDIAN(const T &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_STRUCT, T>, T> {
  return swapEndianess(paValue);
}

template <template <typename, intmax_t, intmax_t> typename T, typename U, intmax_t lowerBound, intmax_t upperBound>
auto func_FROM_LITTLE_ENDIAN(const T<U, lowerBound, upperBound> &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ARRAY_FIXED<U, lowerBound, upperBound>, T<U, lowerBound, upperBound>>, T<U, lowerBound, upperBound>> {
  return swapEndianess(paValue);
}

template <template <typename> typename T, typename U>
auto func_FROM_LITTLE_ENDIAN(const T<U> &paValue) -> typename std::enable_if_t<std::is_base_of_v<CIEC_ARRAY_VARIABLE<U>, T<U>>, T<U>> {
  return swapEndianess(paValue);
}

template <typename T>
T func_TO_BIG_ENDIAN(const T &paValue) {
  return paValue;
}

template <typename T>
T func_FROM_BIG_ENDIAN(const T &paValue) {
  return paValue;
}
#endif

#endif /* IEC61131_FUNCTIONS_H_ */
