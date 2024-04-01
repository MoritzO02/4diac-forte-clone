/*******************************************************************************
 * Copyright (c) 2022 Primetals Technologies Austria GmbH
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Martin Melik-Merkumians
 *      - initial implementation and rework communication infrastructure
 *******************************************************************************/

#pragma once

#ifndef _FORTE_BOOST_OUTPUT_SUPPORT_H_
#define _FORTE_BOOST_OUTPUT_SUPPORT_H_

#include <iostream>
#include "forte_lreal.h"
#include "forte_char.h"
#include "forte_wchar.h"
#include "forte_string.h"
#include "forte_string_fixed.h"
#include "forte_wstring.h"
#include "forte_time.h"
#include "forte_time_of_day.h"
#include "forte_date.h"
#include "forte_date_and_time.h"
#include "forte_ltime.h"
#include "forte_ltime_of_day.h"
#include "forte_ldate.h"
#include "forte_ldate_and_time.h"
#include "funcbloc.h"
#include "mgmcmd.h"

inline
std::ostream& boost_test_print_type(std::ostream &out, const CIEC_LREAL &variable) {
  std::vector<char> outputString(variable.getToStringBufferSize());
  variable.toString(outputString.data(), outputString.size());
  out << outputString.data();
  return out;
}

inline
std::ostream& boost_test_print_type(std::ostream &out, const CIEC_TIME &variable) {
  std::vector<char> outputString(variable.getToStringBufferSize());
  variable.toString(outputString.data(), outputString.size());
  out << outputString.data();
  return out;
}

inline
std::ostream& boost_test_print_type(std::ostream &out, const CIEC_TIME_OF_DAY &variable) {
  std::vector<char> outputString(variable.getToStringBufferSize());
  variable.toString(outputString.data(), outputString.size());
  out << outputString.data();
  return out;
}

inline
std::ostream& boost_test_print_type(std::ostream &out, const CIEC_DATE &variable) {
  std::vector<char> outputString(variable.getToStringBufferSize());
  variable.toString(outputString.data(), outputString.size());
  out << outputString.data();
  return out;
}

inline
std::ostream& boost_test_print_type(std::ostream &out, const CIEC_DATE_AND_TIME &variable) {
  std::vector<char> outputString(variable.getToStringBufferSize());
  variable.toString(outputString.data(), outputString.size());
  out << outputString.data();
  return out;
}

inline
std::ostream& boost_test_print_type(std::ostream &out, const CIEC_LTIME &variable) {
  std::vector<char> outputString(variable.getToStringBufferSize());
  variable.toString(outputString.data(), outputString.size());
  out << outputString.data();
  return out;
}

inline
std::ostream& boost_test_print_type(std::ostream &out, const CIEC_LTIME_OF_DAY &variable) {
  std::vector<char> outputString(variable.getToStringBufferSize());
  variable.toString(outputString.data(), outputString.size());
  out << outputString.data();
  return out;
}

inline
std::ostream& boost_test_print_type(std::ostream &out, const CIEC_LDATE &variable) {
  std::vector<char> outputString(variable.getToStringBufferSize());
  variable.toString(outputString.data(), outputString.size());
  out << outputString.data();
  return out;
}

inline
std::ostream& boost_test_print_type(std::ostream &out, const CIEC_LDATE_AND_TIME &variable) {
  std::vector<char> outputString(variable.getToStringBufferSize());
  variable.toString(outputString.data(), outputString.size());
  out << outputString.data();
  return out;
}

inline
std::ostream& boost_test_print_type(std::ostream &out, const CIEC_CHAR &variable) {
  std::vector<char> outputString(variable.getToStringBufferSize());
  variable.toString(outputString.data(), outputString.size());
  out << outputString.data();
  return out;
}

inline
std::ostream& boost_test_print_type(std::ostream &out, const CIEC_WCHAR &variable) {
  std::vector<char> outputString(variable.getToStringBufferSize());
  variable.toString(outputString.data(), outputString.size());
  out << outputString.data();
  return out;
}

inline
std::ostream& boost_test_print_type(std::ostream &out, const CIEC_STRING &variable) {
  out << variable.getStorage();
  return out;
}

template<size_t maxLength>
inline
std::ostream& boost_test_print_type(std::ostream &out, const CIEC_STRING_FIXED<maxLength> &variable) {
  out << variable.getStorage();
  return out;
}

inline
std::ostream& boost_test_print_type(std::ostream &out, const CIEC_WSTRING &variable) {
  std::vector<char> outputString(variable.getToStringBufferSize());
  variable.toString(outputString.data(), outputString.size());
  out << outputString.data();
  return out;
}

inline
std::ostream& boost_test_print_type(std::ostream &out, const EMGMResponse &variable) {
  out << static_cast<std::underlying_type_t<EMGMResponse>>(variable);
  return out;
}

inline
std::ostream& boost_test_print_type(std::ostream &out, const CFunctionBlock::E_FBStates &variable) {
  out << static_cast<std::underlying_type_t<CFunctionBlock::E_FBStates>>(variable);
  return out;
}

#endif
