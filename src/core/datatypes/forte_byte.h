/*******************************************************************************
 * Copyright (c) 2005, 2023 Profactor GmbH, ACIN
 *                          Johannes Kepler University Linz
 *                          Primetals Technologies Austria GmbH
 *                          Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Thomas Strasser, Ingomar Müller, Alois Zoitl, Gerhard Ebenhofer,
 *    Ingo Hegny, Martin Melik-Merkumians, Monika Wenger
 *      - initial implementation and rework communication infrastructure
 *    Ernst Blecha - add multibit partial access
 *    Martin Melik Merkumians - changes multibit access index from template
 *      parameter to call argument, make TForteByte constructor explicit,
 *      removed built-in type operator=
 *    Martin Jobst - add user-defined literal
 *******************************************************************************/
#ifndef _FORTE_BYTE_H_
#define _FORTE_BYTE_H_

#include "forte_any_bit.h"
#include "forte_bool.h"

#include "forte_any_int.h"
#include "forte_any_bit_partial.h"

#include <limits>

/*!\ingroup COREDTS CIEC_BYTE represents the byte data type according to IEC 61131.
 */
class CIEC_BYTE : public CIEC_ANY_BIT{
  DECLARE_FIRMWARE_DATATYPE(BYTE)

  public:
    using TValueType = TForteByte;
    [[deprecated("Please use the corresponding numeric_limits template")]]
    constexpr static size_t scmBitLength = 8U;

    [[deprecated("Please use the corresponding numeric_limits template")]]
    static constexpr TValueType scmMinVal = std::numeric_limits<TValueType>::min();
    [[deprecated("Please use the corresponding numeric_limits template")]]
    static constexpr TValueType scmMaxVal = std::numeric_limits<TValueType>::max();

    CIEC_BYTE() = default;

    CIEC_BYTE(const CIEC_BYTE& paValue) :
        CIEC_ANY_BIT(){
      setValueSimple(paValue);
    }

    CIEC_BYTE(const CIEC_BOOL &paValue) : CIEC_ANY_BIT() {
      setValueSimple(paValue);
    }

    explicit CIEC_BYTE(const TValueType paValue) {
      setTUINT8(paValue);
    }

    ~CIEC_BYTE() override = default;

    CIEC_BYTE& operator =(const CIEC_BYTE &paValue){
      // Simple value assignment - no self assignment check needed
      setValueSimple(paValue);
      return *this;
    }

    CIEC_BYTE &operator=(const CIEC_BOOL &paValue) {
      // Simple value assignment - no self assignment check needed
      setValueSimple(paValue);
      return *this;
    }

    /*! \brief Converts CIEC_BYTE to elementary byte
     *
     *   Conversion operator for converting CIEC_BYTE to elementary byte
     */
    operator TForteByte() const {
      return getTUINT8();
    }

    /*! \brief calculates buffer size needed for toString conversion
     */
    size_t getToStringBufferSize() const override final {
      return sizeof("255");
    }

    EDataTypeID getDataTypeID() const override final {
      return CIEC_ANY::e_BYTE;
    }

    /*! \brief Partial access within a CIEC_BYTE (e.g. [BYTE].partial<CIEC_BOOL,1>())
     *
     */
    template<class T>
    CIEC_ANY_BIT_PARTIAL<T, CIEC_BYTE> partial(size_t paIndex) {
      return CIEC_ANY_BIT_PARTIAL<T, CIEC_BYTE>(*this, paIndex);
    }

    template<class T>
    T partial(size_t paIndex) const {
      return CIEC_ANY_BIT_PARTIAL<T, CIEC_BYTE>::partialValue(*this, paIndex);
    }

    template<class T>
    T cpartial(size_t paIndex) const {
      return partial<T>(paIndex);
    }

    template<class T>
    CIEC_ANY_BIT_PARTIAL<T, CIEC_BYTE> partial(const CIEC_ANY_INT &paIndex) {
      return partial<T>(paIndex.getUnsignedValue());
    }

    template<class T>
    T partial(const CIEC_ANY_INT &paIndex) const {
      return partial<T>(paIndex.getUnsignedValue());
    }

    template<class T>
    T cpartial(const CIEC_ANY_INT &paIndex) const {
      return partial<T>(paIndex);
    }
};

inline CIEC_BYTE operator ""_BYTE(unsigned long long int paValue) {
  return CIEC_BYTE(static_cast<CIEC_BYTE::TValueType>(paValue));
}

namespace std {
  template <>
  struct numeric_limits<CIEC_BYTE> : public forte::templates::numeric_limits<CIEC_BYTE> {
    static constexpr size_t bitLength = 8U;
  };
}

#endif /*_FORTE_BYTE_H_*/
