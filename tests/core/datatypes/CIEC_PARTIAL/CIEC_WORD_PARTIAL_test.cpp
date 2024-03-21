/*******************************************************************************
 * Copyright (c) 2011 - 2012 ACIN, nxtControl, 2018 TU Vienna/ACIN
 *               2020 Johannes Kepler University Linz
 *               2022 Primetals Technologies Austria GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Martin Melik Merkumians, Ingo Hegny, Alois Zoitl, Stanislav Meduna - initial API and implementation and/or initial documentation
 *   Ernst Blecha - Adds partial access tests
 *   Martin Melik Merkumians - Updates test for changes in partial
 *******************************************************************************/

#include <boost/test/unit_test.hpp>

//BOOLEAN
#include "../../../src/core/datatypes/forte_bool.h"
//BIT-Datatypes
#include "../../../src/core/datatypes/forte_byte.h"
#include "../../../src/core/datatypes/forte_word.h"

#include "../../../src/core/datatypes/forte_sint.h"

#include "CIEC_PARTIAL_test.h"

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE(ANY_BIT_PARTIAL)
BOOST_AUTO_TEST_SUITE(CIEC_ANY_BIT_PARTIAL_WORD)

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WORD_INITVALUES_CHECK_BIT)
{
  CIEC_WORD nTestWord;

  test4X_0(nTestWord, 12)
  test4X_0(nTestWord, 8)
  test4X_0(nTestWord, 4)
  test4X_0(nTestWord, 0)

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WORD_INITVALUES_CHECK_BIT_CONST)
{
  const CIEC_WORD nTestWord;

  test4X_0(nTestWord, 12)
  test4X_0(nTestWord, 8)
  test4X_0(nTestWord, 4)
  test4X_0(nTestWord, 0)

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WORD_INITVALUES_CHECK_BYTE)
{
  CIEC_WORD nTestWord;

  BOOST_CHECK_EQUAL((nTestWord.partial<CIEC_BYTE>(0)),0);
  BOOST_CHECK_EQUAL((nTestWord.partial<CIEC_BYTE>(1)),0);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WORD_INITVALUES_CHECK_BYTE_CONST)
{
  const CIEC_WORD nTestWord;

  BOOST_CHECK_EQUAL((nTestWord.partial<CIEC_BYTE>(0)),0);
  BOOST_CHECK_EQUAL((nTestWord.partial<CIEC_BYTE>(1)),0);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WORD_CONST_INIT)
{
  const CIEC_BYTE nTestByte(0x42);
  CIEC_WORD mTestWord;

  mTestWord.partial<CIEC_BYTE>(0) = nTestByte;

  BOOST_CHECK_EQUAL(mTestWord, 0x42);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WORD_VALUE_CHECK_WORD)
{
  CIEC_WORD nTestWord;

  nTestWord =  CIEC_WORD(0xBABE);

  BOOST_CHECK_EQUAL(nTestWord, 0xBABE);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WORD_VALUE_CHECK_BYTE)
{
  CIEC_WORD nTestWord;

  nTestWord =  CIEC_WORD(0xBABE);

  BOOST_CHECK_EQUAL((nTestWord.partial<CIEC_BYTE>(0)), 0xBE);
  BOOST_CHECK_EQUAL((nTestWord.partial<CIEC_BYTE>(1)), 0xBA);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WORD_VALUE_CHECK_BYTE_CONST)
{
  const CIEC_WORD nTestWord = 0xBABE_WORD;

  BOOST_CHECK_EQUAL((nTestWord.partial<CIEC_BYTE>(0)), 0xBE);
  BOOST_CHECK_EQUAL((nTestWord.partial<CIEC_BYTE>(1)), 0xBA);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WORD_VALUE_CHECK_BIT)
{
  CIEC_WORD nTestWord;

  nTestWord =  CIEC_WORD(0xBABE);

  test4X_B(nTestWord, 12)
  test4X_A(nTestWord, 8)
  test4X_B(nTestWord, 4)
  test4X_E(nTestWord, 0)

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WORD_VALUE_CHECK_BIT_CONST)
{
  const CIEC_WORD nTestWord = 0xBABE_WORD;

  test4X_B(nTestWord, 12)
  test4X_A(nTestWord, 8)
  test4X_B(nTestWord, 4)
  test4X_E(nTestWord, 0)

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WORD_ASSIGN_BIT_CHECK_BIT)
{
  CIEC_WORD nTestWord;

  set4X_F(nTestWord,12);
  set4X_0(nTestWord,8);
  set4X_0(nTestWord,4);
  set4X_D(nTestWord,0);

  test4X_F(nTestWord,12);
  test4X_0(nTestWord,8);
  test4X_0(nTestWord,4);
  test4X_D(nTestWord,0);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WORD_ASSIGN_BIT_CHECK_BYTE)
{
  CIEC_WORD nTestWord;

  set4X_F(nTestWord,12);
  set4X_0(nTestWord,8);
  set4X_0(nTestWord,4);
  set4X_D(nTestWord,0);

  BOOST_CHECK_EQUAL((nTestWord.partial<CIEC_BYTE>(1)), 0xF0U);
  BOOST_CHECK_EQUAL((nTestWord.partial<CIEC_BYTE>(0)), 0x0DU);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WORD_ASSIGN_BIT_CHECK_WORD)
{
  CIEC_WORD nTestWord;

  set4X_F(nTestWord,12);
  set4X_0(nTestWord,8);
  set4X_0(nTestWord,4);
  set4X_D(nTestWord,0);

  BOOST_CHECK_EQUAL(nTestWord, 0xF00DU);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WORD_ASSIGN_BYTE_CHECK_BIT)
{
  CIEC_WORD nTestWord;

  nTestWord.partial<CIEC_BYTE>(1) = CIEC_BYTE(0xCA);
  nTestWord.partial<CIEC_BYTE>(0) = CIEC_BYTE(0xFE);

  test4X_C(nTestWord,12);
  test4X_A(nTestWord,8);
  test4X_F(nTestWord,4);
  test4X_E(nTestWord,0);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WORD_ASSIGN_BYTE_CHECK_BYTE)
{
  CIEC_WORD nTestWord;

  nTestWord.partial<CIEC_BYTE>(1) = CIEC_BYTE(0xCA);
  nTestWord.partial<CIEC_BYTE>(0) = CIEC_BYTE(0xFE);

  BOOST_CHECK_EQUAL((nTestWord.partial<CIEC_BYTE>(1)), 0xCAU);
  BOOST_CHECK_EQUAL((nTestWord.partial<CIEC_BYTE>(0)), 0xFEU);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WORD_ASSIGN_BYTE_CHECK_WORD)
{
  CIEC_WORD nTestWord;

  nTestWord.partial<CIEC_BYTE>(1) = CIEC_BYTE(0xCA);
  nTestWord.partial<CIEC_BYTE>(0) = CIEC_BYTE(0xFE);

  BOOST_CHECK_EQUAL(nTestWord, 0xCAFEU);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WORD_ASSIGN_WORD_CHECK_BIT)
{
  CIEC_WORD nTestWord;

  nTestWord = CIEC_WORD(0xFFEE);

  test4X_F(nTestWord,12);
  test4X_F(nTestWord,8);
  test4X_E(nTestWord,4);
  test4X_E(nTestWord,0);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WORD_ASSIGN_WORD_CHECK_BYTE)
{
  CIEC_WORD nTestWord;

  nTestWord = CIEC_WORD(0xFFEE);

  BOOST_CHECK_EQUAL((nTestWord.partial<CIEC_BYTE>(1)), 0xFFU);
  BOOST_CHECK_EQUAL((nTestWord.partial<CIEC_BYTE>(0)), 0xEEU);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WORD_ASSIGN_WORD_CHECK_WORD)
{
  CIEC_WORD nTestWord;

  nTestWord = CIEC_WORD(0xFFEE);

  BOOST_CHECK_EQUAL(nTestWord, 0xFFEEU);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WORD_ASSIGN_CHAIN_BYTE_BIT_CHECK_BIT)
{
  CIEC_WORD nTestWord;

  set4X_1(nTestWord,12);
  set4X_1(nTestWord,8);
  set4X_F(nTestWord,4);
  set4X_E(nTestWord,0);

  test4X_1(nTestWord,12);
  test4X_1(nTestWord,8);
  test4X_F(nTestWord,4);
  test4X_E(nTestWord,0);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WORD_ASSIGN_CHAIN_BYTE_BIT_CHECK_BYTE)
{
  CIEC_WORD nTestWord;

  set4X_1(nTestWord,12);
  set4X_1(nTestWord,8);
  set4X_F(nTestWord,4);
  set4X_E(nTestWord,0);

  BOOST_CHECK_EQUAL((nTestWord.partial<CIEC_BYTE>(1)), 0x11U);
  BOOST_CHECK_EQUAL((nTestWord.partial<CIEC_BYTE>(0)), 0xFEU);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WORD_ASSIGN_CHAIN_BYTE_BIT_CHECK_WORD) {
  CIEC_WORD nTestWord;

  set4X_1(nTestWord,12);
  set4X_1(nTestWord,8);
  set4X_F(nTestWord,4);
  set4X_E(nTestWord,0);

  BOOST_CHECK_EQUAL(nTestWord, 0x11FEU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_READ_WITH_IEC_TYPE_INDEX)
{
  CIEC_WORD nWord(0xBE);
  CIEC_BOOL bBool;
  bBool = nWord.partial<CIEC_BOOL>(CIEC_SINT(0));
  BOOST_TEST(static_cast<CIEC_BOOL::TValueType>(bBool) == false);

  bBool = nWord.partial<CIEC_BOOL>(CIEC_SINT(1));
  BOOST_TEST(static_cast<CIEC_BOOL::TValueType>(bBool) == true);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WRITE_WITH_IEC_TYPE_INDEX)
{
  CIEC_WORD nWord;
  nWord.partial<CIEC_BOOL>(CIEC_SINT(0)) = CIEC_BOOL(true);
  BOOST_TEST(static_cast<CIEC_WORD::TValueType>(nWord) == 1U);

  nWord.partial<CIEC_BOOL>(CIEC_SINT(1)) = CIEC_BOOL(true);
  BOOST_TEST(static_cast<CIEC_WORD::TValueType>(nWord) == 3U);
}

BOOST_AUTO_TEST_CASE(PARTIAL_COPY_PARTIAL_BOOL_TO_SAME_PARTIAL_BOOL) {
  CIEC_WORD nWord(0x0002U);
  nWord.partial<CIEC_BOOL>(CIEC_SINT(0)) = CIEC_BOOL(nWord.cpartial<CIEC_BOOL>(CIEC_SINT(0)) || true);
  BOOST_TEST(static_cast<CIEC_WORD::TValueType>(nWord) == 0x03U);
}

BOOST_AUTO_TEST_CASE(PARTIAL_COPY_PARTIAL_BYTE_TO_SAME_PARTIAL_BYTE) {
  CIEC_WORD nWord(0xABFEU);
  nWord.partial<CIEC_BYTE>(CIEC_SINT(0)) = CIEC_BYTE(
          static_cast<CIEC_BYTE::TValueType>(nWord.cpartial<CIEC_BYTE>(CIEC_SINT(0))) | 0x01);
  BOOST_TEST(static_cast<CIEC_WORD::TValueType>(nWord) == 0xABFFU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_COPY_PARTIAL_BOOL_TO_OTHER_PARTIAL_BOOL) {
  CIEC_WORD nWord(0x0001U);
  nWord.partial<CIEC_BOOL>(CIEC_SINT(1)) = nWord.partial<CIEC_BOOL>(CIEC_SINT(0));
  BOOST_TEST(static_cast<CIEC_WORD::TValueType>(nWord) == 0x03U);
}

BOOST_AUTO_TEST_CASE(PARTIAL_COPY_PARTIAL_BYTE_TO_OTHER_PARTIAL_BYTE) {
  CIEC_WORD nWord(0x00FEU);
  nWord.partial<CIEC_BYTE>(CIEC_SINT(1)) = nWord.partial<CIEC_BYTE>(CIEC_SINT(0));
  BOOST_TEST(static_cast<CIEC_WORD::TValueType>(nWord) == 0xFEFEU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_COPY_PARTIAL_BOOL_TO_OTHER_PARTIAL_BYTE) {
  CIEC_WORD nWord(0x00FEU);
  nWord.partial<CIEC_BYTE>(CIEC_SINT(1)) = nWord.partial<CIEC_BOOL>(CIEC_SINT(1));
  BOOST_TEST(static_cast<CIEC_WORD::TValueType>(nWord) == 0x01FEU);
}


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
