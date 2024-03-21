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
#include "../../../src/core/datatypes/forte_dword.h"

#include "../../../src/core/datatypes/forte_sint.h"

#include "CIEC_PARTIAL_test.h"

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE(ANY_BIT_PARTIAL)
BOOST_AUTO_TEST_SUITE(CIEC_ANY_BIT_PARTIAL_DWORD)

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_INITVALUES_CHECK_BIT)
{
  CIEC_DWORD nTestDWord;

  test4X_0(nTestDWord,28);
  test4X_0(nTestDWord,24);
  test4X_0(nTestDWord,20);
  test4X_0(nTestDWord,16);
  test4X_0(nTestDWord,12);
  test4X_0(nTestDWord,8);
  test4X_0(nTestDWord,4);
  test4X_0(nTestDWord,0);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_INITVALUES_CHECK_BIT_CONST)
{
  const CIEC_DWORD nTestDWord;

  test4X_0(nTestDWord,28);
  test4X_0(nTestDWord,24);
  test4X_0(nTestDWord,20);
  test4X_0(nTestDWord,16);
  test4X_0(nTestDWord,12);
  test4X_0(nTestDWord,8);
  test4X_0(nTestDWord,4);
  test4X_0(nTestDWord,0);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_INITVALUES_CHECK_BYTE)
{
  CIEC_DWORD nTestDWord;

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(0)),0);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(1)),0);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(2)),0);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(3)),0);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_INITVALUES_CHECK_BYTE_CONST)
{
  const CIEC_DWORD nTestDWord;

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(0)),0);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(1)),0);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(2)),0);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(3)),0);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_INITVALUES_CHECK_WORD)
{
  CIEC_DWORD nTestDWord;

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(0)),0);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(1)),0);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_INITVALUES_CHECK_WORD_CONST)
{
  const CIEC_DWORD nTestDWord;

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(0)),0);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(1)),0);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_INITVALUES_CHECK_DWORD)
{
  CIEC_DWORD nTestDWord;

  BOOST_CHECK_EQUAL(nTestDWord,0);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_CONST_INIT)
{
  const CIEC_WORD nTestWord(0x42);
  CIEC_DWORD mTestDWord;

  mTestDWord.partial<CIEC_WORD>(0) = nTestWord;

  BOOST_CHECK_EQUAL(mTestDWord, 0x42);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_VALUE_CHECK_BIT)
{
  CIEC_DWORD nTestDWord;

  nTestDWord = CIEC_DWORD(0xCAFEBABE);

  test4X_C(nTestDWord,28)
  test4X_A(nTestDWord,24)
  test4X_F(nTestDWord,20)
  test4X_E(nTestDWord,16)

  test4X_B(nTestDWord,12)
  test4X_A(nTestDWord,8)
  test4X_B(nTestDWord,4)
  test4X_E(nTestDWord,0)

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_VALUE_CHECK_BIT_CONST)
{
  const CIEC_DWORD nTestDWord = 0xCAFEBABE_DWORD;

  test4X_C(nTestDWord,28)
  test4X_A(nTestDWord,24)
  test4X_F(nTestDWord,20)
  test4X_E(nTestDWord,16)

  test4X_B(nTestDWord,12)
  test4X_A(nTestDWord,8)
  test4X_B(nTestDWord,4)
  test4X_E(nTestDWord,0)

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_VALUE_CHECK_BYTE)
{
  CIEC_DWORD nTestDWord;

  nTestDWord = CIEC_DWORD(0xCAFEBABE);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(0)), 0xBE);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(1)), 0xBA);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(2)), 0xFE);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(3)), 0xCA);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_VALUE_CHECK_BYTE_CONST)
{
  const CIEC_DWORD nTestDWord = 0xCAFEBABE_DWORD;

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(0)), 0xBE);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(1)), 0xBA);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(2)), 0xFE);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(3)), 0xCA);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_VALUE_CHECK_WORD)
{
  CIEC_DWORD nTestDWord;

  nTestDWord = CIEC_DWORD(0xCAFEBABE);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(0)), 0xBABE);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(1)), 0xCAFE);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_VALUE_CHECK_WORD_CONST)
{
  const CIEC_DWORD nTestDWord = 0xCAFEBABE_DWORD;

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(0)), 0xBABE);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(1)), 0xCAFE);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_VALUE_CHECK_DWORD)
{
  CIEC_DWORD nTestDWord;

  nTestDWord = CIEC_DWORD(0xCAFEBABE);

  BOOST_CHECK_EQUAL(nTestDWord, 0xCAFEBABE);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_ASSIGN)
{
  CIEC_DWORD nTestDWord;

  set4X_B(nTestDWord,28);
  set4X_A(nTestDWord,24);
  set4X_A(nTestDWord,20);
  set4X_D(nTestDWord,16);
  set4X_F(nTestDWord,12);
  set4X_0(nTestDWord,8);
  set4X_0(nTestDWord,4);
  set4X_D(nTestDWord,0);

  test4X_B(nTestDWord,28);
  test4X_A(nTestDWord,24);
  test4X_A(nTestDWord,20);
  test4X_D(nTestDWord,16);
  test4X_F(nTestDWord,12);
  test4X_0(nTestDWord,8);
  test4X_0(nTestDWord,4);
  test4X_D(nTestDWord,0);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(3)), 0xBAU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(2)), 0xADU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(1)), 0xF0U);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(0)), 0x0DU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(1)), 0xBAADU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(0)), 0xF00DU);
  BOOST_CHECK_EQUAL(nTestDWord, 0xBAADF00DU);

  nTestDWord.partial<CIEC_BYTE>(3) = CIEC_BYTE(0xBA);
  nTestDWord.partial<CIEC_BYTE>(2) = CIEC_BYTE(0xD0);
  nTestDWord.partial<CIEC_BYTE>(1) = CIEC_BYTE(0xCA);
  nTestDWord.partial<CIEC_BYTE>(0) = CIEC_BYTE(0xFE);

  test4X_B(nTestDWord,28);
  test4X_A(nTestDWord,24);
  test4X_D(nTestDWord,20);
  test4X_0(nTestDWord,16);
  test4X_C(nTestDWord,12);
  test4X_A(nTestDWord,8);
  test4X_F(nTestDWord,4);
  test4X_E(nTestDWord,0);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(3)), 0xBAU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(2)), 0xD0U);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(1)), 0xCAU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(0)), 0xFEU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(1)), 0xBAD0U);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(0)), 0xCAFEU);
  BOOST_CHECK_EQUAL(nTestDWord, 0xBAD0CAFEU);

  nTestDWord.partial<CIEC_WORD>(1) = CIEC_WORD(0xCEC0);
  nTestDWord.partial<CIEC_WORD>(0) = CIEC_WORD(0xFFEE);

  test4X_C(nTestDWord,28);
  test4X_E(nTestDWord,24);
  test4X_C(nTestDWord,20);
  test4X_0(nTestDWord,16);
  test4X_F(nTestDWord,12);
  test4X_F(nTestDWord,8);
  test4X_E(nTestDWord,4);
  test4X_E(nTestDWord,0);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(3)), 0xCEU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(2)), 0xC0U);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(1)), 0xFFU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(0)), 0xEEU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(1)), 0xCEC0U);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(0)), 0xFFEEU);
  BOOST_CHECK_EQUAL(nTestDWord, 0xCEC0FFEEU);

  nTestDWord = CIEC_DWORD(0xADD511FE);

  test4X_A(nTestDWord,28);
  test4X_D(nTestDWord,24);
  test4X_D(nTestDWord,20);
  test4X_5(nTestDWord,16);
  test4X_1(nTestDWord,12);
  test4X_1(nTestDWord,8);
  test4X_F(nTestDWord,4);
  test4X_E(nTestDWord,0);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(3)), 0xADU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(2)), 0xD5U);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(1)), 0x11U);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(0)), 0xFEU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(1)), 0xADD5U);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(0)), 0x11FEU);
  BOOST_CHECK_EQUAL(nTestDWord, 0xADD511FEU);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_ASSIGN_CHAIN_SET_BIT_CHECK_BIT)
{
  CIEC_DWORD nTestDWord;

  set4X_B(nTestDWord,28);
  set4X_A(nTestDWord,24);
  set4X_A(nTestDWord,20);
  set4X_D(nTestDWord,16);
  set4X_F(nTestDWord,12);
  set4X_0(nTestDWord,8);
  set4X_0(nTestDWord,4);
  set4X_D(nTestDWord,0);

  test4X_B(nTestDWord,28);
  test4X_A(nTestDWord,24);
  test4X_A(nTestDWord,20);
  test4X_D(nTestDWord,16);
  test4X_F(nTestDWord,12);
  test4X_0(nTestDWord,8);
  test4X_0(nTestDWord,4);
  test4X_D(nTestDWord,0);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_ASSIGN_CHAIN_SET_BIT_CHECK_BYTE)
{
  CIEC_DWORD nTestDWord;

  set4X_B(nTestDWord,28);
  set4X_A(nTestDWord,24);
  set4X_A(nTestDWord,20);
  set4X_D(nTestDWord,16);
  set4X_F(nTestDWord,12);
  set4X_0(nTestDWord,8);
  set4X_0(nTestDWord,4);
  set4X_D(nTestDWord,0);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(3)), 0xBAU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(2)), 0xADU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(1)), 0xF0U);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(0)), 0x0DU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_ASSIGN_CHAIN_SET_BIT_CHECK_WORD)
{
  CIEC_DWORD nTestDWord;

  set4X_B(nTestDWord,28);
  set4X_A(nTestDWord,24);
  set4X_A(nTestDWord,20);
  set4X_D(nTestDWord,16);
  set4X_F(nTestDWord,12);
  set4X_0(nTestDWord,8);
  set4X_0(nTestDWord,4);
  set4X_D(nTestDWord,0);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(1)), 0xBAADU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(0)), 0xF00DU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_ASSIGN_CHAIN_SET_BIT_CHECK_DWORD)
{
  CIEC_DWORD nTestDWord;

  set4X_B(nTestDWord,28);
  set4X_A(nTestDWord,24);
  set4X_A(nTestDWord,20);
  set4X_D(nTestDWord,16);
  set4X_F(nTestDWord,12);
  set4X_0(nTestDWord,8);
  set4X_0(nTestDWord,4);
  set4X_D(nTestDWord,0);

  BOOST_CHECK_EQUAL(nTestDWord, 0xBAADF00DU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_CHANGE_CHAIN_SET_BYTE_CHECK_BIT)
{
  CIEC_DWORD nTestDWord;

  set4X_B(nTestDWord,28);
  set4X_A(nTestDWord,24);
  set4X_A(nTestDWord,20);
  set4X_D(nTestDWord,16);
  set4X_F(nTestDWord,12);
  set4X_0(nTestDWord,8);
  set4X_0(nTestDWord,4);
  set4X_D(nTestDWord,0);

  nTestDWord.partial<CIEC_BYTE>(3) = CIEC_BYTE(0xBA);
  nTestDWord.partial<CIEC_BYTE>(2) = CIEC_BYTE(0xD0);
  nTestDWord.partial<CIEC_BYTE>(1) = CIEC_BYTE(0xCA);
  nTestDWord.partial<CIEC_BYTE>(0) = CIEC_BYTE(0xFE);

  test4X_B(nTestDWord,28);
  test4X_A(nTestDWord,24);
  test4X_D(nTestDWord,20);
  test4X_0(nTestDWord,16);
  test4X_C(nTestDWord,12);
  test4X_A(nTestDWord,8);
  test4X_F(nTestDWord,4);
  test4X_E(nTestDWord,0);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_CHANGE_CHAIN_SET_BYTE_CHECK_BYTE)
{
  CIEC_DWORD nTestDWord;

  set4X_B(nTestDWord,28);
  set4X_A(nTestDWord,24);
  set4X_A(nTestDWord,20);
  set4X_D(nTestDWord,16);
  set4X_F(nTestDWord,12);
  set4X_0(nTestDWord,8);
  set4X_0(nTestDWord,4);
  set4X_D(nTestDWord,0);

  nTestDWord.partial<CIEC_BYTE>(3) = CIEC_BYTE(0xBA);
  nTestDWord.partial<CIEC_BYTE>(2) = CIEC_BYTE(0xD0);
  nTestDWord.partial<CIEC_BYTE>(1) = CIEC_BYTE(0xCA);
  nTestDWord.partial<CIEC_BYTE>(0) = CIEC_BYTE(0xFE);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(3)), 0xBAU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(2)), 0xD0U);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(1)), 0xCAU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(0)), 0xFEU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_CHANGE_CHAIN_SET_BYTE_CHECK_WORD)
{
  CIEC_DWORD nTestDWord;

  set4X_B(nTestDWord,28);
  set4X_A(nTestDWord,24);
  set4X_A(nTestDWord,20);
  set4X_D(nTestDWord,16);
  set4X_F(nTestDWord,12);
  set4X_0(nTestDWord,8);
  set4X_0(nTestDWord,4);
  set4X_D(nTestDWord,0);

  nTestDWord.partial<CIEC_BYTE>(3) = CIEC_BYTE(0xBA);
  nTestDWord.partial<CIEC_BYTE>(2) = CIEC_BYTE(0xD0);
  nTestDWord.partial<CIEC_BYTE>(1) = CIEC_BYTE(0xCA);
  nTestDWord.partial<CIEC_BYTE>(0) = CIEC_BYTE(0xFE);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(1)), 0xBAD0U);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(0)), 0xCAFEU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_CHANGE_CHAIN_SET_BYTE_CHECK_DWORD)
{
  CIEC_DWORD nTestDWord;

  set4X_B(nTestDWord,28);
  set4X_A(nTestDWord,24);
  set4X_A(nTestDWord,20);
  set4X_D(nTestDWord,16);
  set4X_F(nTestDWord,12);
  set4X_0(nTestDWord,8);
  set4X_0(nTestDWord,4);
  set4X_D(nTestDWord,0);

  nTestDWord.partial<CIEC_BYTE>(3) = CIEC_BYTE(0xBA);
  nTestDWord.partial<CIEC_BYTE>(2) = CIEC_BYTE(0xD0);
  nTestDWord.partial<CIEC_BYTE>(1) = CIEC_BYTE(0xCA);
  nTestDWord.partial<CIEC_BYTE>(0) = CIEC_BYTE(0xFE);

  BOOST_CHECK_EQUAL(nTestDWord, 0xBAD0CAFEU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_CHANGE_CHAIN_SET_WORD_CHECK_BIT)
{
  CIEC_DWORD nTestDWord;

  set4X_B(nTestDWord,28);
  set4X_A(nTestDWord,24);
  set4X_A(nTestDWord,20);
  set4X_D(nTestDWord,16);
  set4X_F(nTestDWord,12);
  set4X_0(nTestDWord,8);
  set4X_0(nTestDWord,4);
  set4X_D(nTestDWord,0);

  nTestDWord.partial<CIEC_BYTE>(3) = CIEC_BYTE(0xBA);
  nTestDWord.partial<CIEC_BYTE>(2) = CIEC_BYTE(0xD0);
  nTestDWord.partial<CIEC_BYTE>(1) = CIEC_BYTE(0xCA);
  nTestDWord.partial<CIEC_BYTE>(0) = CIEC_BYTE(0xFE);

  nTestDWord.partial<CIEC_WORD>(1) = CIEC_WORD(0xCEC0);
  nTestDWord.partial<CIEC_WORD>(0) = CIEC_WORD(0xFFEE);

  test4X_C(nTestDWord,28);
  test4X_E(nTestDWord,24);
  test4X_C(nTestDWord,20);
  test4X_0(nTestDWord,16);
  test4X_F(nTestDWord,12);
  test4X_F(nTestDWord,8);
  test4X_E(nTestDWord,4);
  test4X_E(nTestDWord,0);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_CHANGE_CHAIN_SET_WORD_CHECK_BYTE)
{
  CIEC_DWORD nTestDWord;

  set4X_B(nTestDWord,28);
  set4X_A(nTestDWord,24);
  set4X_A(nTestDWord,20);
  set4X_D(nTestDWord,16);
  set4X_F(nTestDWord,12);
  set4X_0(nTestDWord,8);
  set4X_0(nTestDWord,4);
  set4X_D(nTestDWord,0);

  nTestDWord.partial<CIEC_BYTE>(3) = CIEC_BYTE(0xBA);
  nTestDWord.partial<CIEC_BYTE>(2) = CIEC_BYTE(0xD0);
  nTestDWord.partial<CIEC_BYTE>(1) = CIEC_BYTE(0xCA);
  nTestDWord.partial<CIEC_BYTE>(0) = CIEC_BYTE(0xFE);

  nTestDWord.partial<CIEC_WORD>(1) = CIEC_WORD(0xCEC0);
  nTestDWord.partial<CIEC_WORD>(0) = CIEC_WORD(0xFFEE);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(3)), 0xCEU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(2)), 0xC0U);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(1)), 0xFFU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(0)), 0xEEU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_CHANGE_CHAIN_SET_WORD_CHECK_WORD)
{
  CIEC_DWORD nTestDWord;

  set4X_B(nTestDWord,28);
  set4X_A(nTestDWord,24);
  set4X_A(nTestDWord,20);
  set4X_D(nTestDWord,16);
  set4X_F(nTestDWord,12);
  set4X_0(nTestDWord,8);
  set4X_0(nTestDWord,4);
  set4X_D(nTestDWord,0);

  nTestDWord.partial<CIEC_BYTE>(3) = CIEC_BYTE(0xBA);
  nTestDWord.partial<CIEC_BYTE>(2) = CIEC_BYTE(0xD0);
  nTestDWord.partial<CIEC_BYTE>(1) = CIEC_BYTE(0xCA);
  nTestDWord.partial<CIEC_BYTE>(0) = CIEC_BYTE(0xFE);

  nTestDWord.partial<CIEC_WORD>(1) = CIEC_WORD(0xCEC0);
  nTestDWord.partial<CIEC_WORD>(0) = CIEC_WORD(0xFFEE);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(1)), 0xCEC0U);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(0)), 0xFFEEU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_CHANGE_CHAIN_SET_WORD_CHECK_DWORD)
{
  CIEC_DWORD nTestDWord;

  set4X_B(nTestDWord,28);
  set4X_A(nTestDWord,24);
  set4X_A(nTestDWord,20);
  set4X_D(nTestDWord,16);
  set4X_F(nTestDWord,12);
  set4X_0(nTestDWord,8);
  set4X_0(nTestDWord,4);
  set4X_D(nTestDWord,0);

  nTestDWord.partial<CIEC_BYTE>(3) = CIEC_BYTE(0xBA);
  nTestDWord.partial<CIEC_BYTE>(2) = CIEC_BYTE(0xD0);
  nTestDWord.partial<CIEC_BYTE>(1) = CIEC_BYTE(0xCA);
  nTestDWord.partial<CIEC_BYTE>(0) = CIEC_BYTE(0xFE);

  nTestDWord.partial<CIEC_WORD>(1) = CIEC_WORD(0xCEC0);
  nTestDWord.partial<CIEC_WORD>(0) = CIEC_WORD(0xFFEE);

  BOOST_CHECK_EQUAL(nTestDWord, 0xCEC0FFEEU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_CHANGE_CHAIN_WORD_SET_BIT_CHECK_BIT)
{
  CIEC_DWORD nTestDWord;

  set4X_B(nTestDWord,28);
  set4X_A(nTestDWord,24);
  set4X_A(nTestDWord,20);
  set4X_D(nTestDWord,16);
  set4X_F(nTestDWord,12);
  set4X_0(nTestDWord,8);
  set4X_0(nTestDWord,4);
  set4X_D(nTestDWord,0);

  nTestDWord.partial<CIEC_BYTE>(3) = CIEC_BYTE(0xBA);
  nTestDWord.partial<CIEC_BYTE>(2) = CIEC_BYTE(0xD0);
  nTestDWord.partial<CIEC_BYTE>(1) = CIEC_BYTE(0xCA);
  nTestDWord.partial<CIEC_BYTE>(0) = CIEC_BYTE(0xFE);

  nTestDWord.partial<CIEC_WORD>(1) = CIEC_WORD(0xCEC0);
  nTestDWord.partial<CIEC_WORD>(0) = CIEC_WORD(0xFFEE);

  set4X_A((nTestDWord.partial<CIEC_WORD>(1)),12);
  set4X_D((nTestDWord.partial<CIEC_WORD>(1)),8);
  set4X_D((nTestDWord.partial<CIEC_WORD>(1)),4);
  set4X_5((nTestDWord.partial<CIEC_WORD>(1)),0);
  set4X_1((nTestDWord.partial<CIEC_WORD>(0)),12);
  set4X_1((nTestDWord.partial<CIEC_WORD>(0)),8);
  set4X_F((nTestDWord.partial<CIEC_WORD>(0)),4);
  set4X_E((nTestDWord.partial<CIEC_WORD>(0)),0);

  test4X_A(nTestDWord,28);
  test4X_D(nTestDWord,24);
  test4X_D(nTestDWord,20);
  test4X_5(nTestDWord,16);
  test4X_1(nTestDWord,12);
  test4X_1(nTestDWord,8);
  test4X_F(nTestDWord,4);
  test4X_E(nTestDWord,0);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_CHANGE_CHAIN_WORD_SET_BIT_CHECK_BYTE)
{
  CIEC_DWORD nTestDWord;

  set4X_B(nTestDWord,28);
  set4X_A(nTestDWord,24);
  set4X_A(nTestDWord,20);
  set4X_D(nTestDWord,16);
  set4X_F(nTestDWord,12);
  set4X_0(nTestDWord,8);
  set4X_0(nTestDWord,4);
  set4X_D(nTestDWord,0);

  nTestDWord.partial<CIEC_BYTE>(3) = CIEC_BYTE(0xBA);
  nTestDWord.partial<CIEC_BYTE>(2) = CIEC_BYTE(0xD0);
  nTestDWord.partial<CIEC_BYTE>(1) = CIEC_BYTE(0xCA);
  nTestDWord.partial<CIEC_BYTE>(0) = CIEC_BYTE(0xFE);

  nTestDWord.partial<CIEC_WORD>(1) = CIEC_WORD(0xCEC0);
  nTestDWord.partial<CIEC_WORD>(0) = CIEC_WORD(0xFFEE);

  set4X_A((nTestDWord.partial<CIEC_WORD>(1)),12);
  set4X_D((nTestDWord.partial<CIEC_WORD>(1)),8);
  set4X_D((nTestDWord.partial<CIEC_WORD>(1)),4);
  set4X_5((nTestDWord.partial<CIEC_WORD>(1)),0);
  set4X_1((nTestDWord.partial<CIEC_WORD>(0)),12);
  set4X_1((nTestDWord.partial<CIEC_WORD>(0)),8);
  set4X_F((nTestDWord.partial<CIEC_WORD>(0)),4);
  set4X_E((nTestDWord.partial<CIEC_WORD>(0)),0);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(3)), 0xADU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(2)), 0xD5U);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(1)), 0x11U);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(0)), 0xFEU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_CHANGE_CHAIN_WORD_SET_BIT_CHECK_WORD)
{
  CIEC_DWORD nTestDWord;

  set4X_B(nTestDWord,28);
  set4X_A(nTestDWord,24);
  set4X_A(nTestDWord,20);
  set4X_D(nTestDWord,16);
  set4X_F(nTestDWord,12);
  set4X_0(nTestDWord,8);
  set4X_0(nTestDWord,4);
  set4X_D(nTestDWord,0);

  nTestDWord.partial<CIEC_BYTE>(3) = CIEC_BYTE(0xBA);
  nTestDWord.partial<CIEC_BYTE>(2) = CIEC_BYTE(0xD0);
  nTestDWord.partial<CIEC_BYTE>(1) = CIEC_BYTE(0xCA);
  nTestDWord.partial<CIEC_BYTE>(0) = CIEC_BYTE(0xFE);

  nTestDWord.partial<CIEC_WORD>(1) = CIEC_WORD(0xCEC0);
  nTestDWord.partial<CIEC_WORD>(0) = CIEC_WORD(0xFFEE);

  set4X_A((nTestDWord.partial<CIEC_WORD>(1)),12);
  set4X_D((nTestDWord.partial<CIEC_WORD>(1)),8);
  set4X_D((nTestDWord.partial<CIEC_WORD>(1)),4);
  set4X_5((nTestDWord.partial<CIEC_WORD>(1)),0);
  set4X_1((nTestDWord.partial<CIEC_WORD>(0)),12);
  set4X_1((nTestDWord.partial<CIEC_WORD>(0)),8);
  set4X_F((nTestDWord.partial<CIEC_WORD>(0)),4);
  set4X_E((nTestDWord.partial<CIEC_WORD>(0)),0);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(1)), 0xADD5U);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(0)), 0x11FEU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_CHANGE_CHAIN_WORD_SET_BIT_CHECK_DWORD)
{
  CIEC_DWORD nTestDWord;

  nTestDWord.partial<CIEC_BYTE>(3) = CIEC_BYTE(0xBA);
  nTestDWord.partial<CIEC_BYTE>(2) = CIEC_BYTE(0xD0);
  nTestDWord.partial<CIEC_BYTE>(1) = CIEC_BYTE(0xCA);
  nTestDWord.partial<CIEC_BYTE>(0) = CIEC_BYTE(0xFE);

  nTestDWord.partial<CIEC_WORD>(1) = CIEC_WORD(0xCEC0);
  nTestDWord.partial<CIEC_WORD>(0) = CIEC_WORD(0xFFEE);

  set4X_A((nTestDWord.partial<CIEC_WORD>(1)),12);
  set4X_D((nTestDWord.partial<CIEC_WORD>(1)),8);
  set4X_D((nTestDWord.partial<CIEC_WORD>(1)),4);
  set4X_5((nTestDWord.partial<CIEC_WORD>(1)),0);
  set4X_1((nTestDWord.partial<CIEC_WORD>(0)),12);
  set4X_1((nTestDWord.partial<CIEC_WORD>(0)),8);
  set4X_F((nTestDWord.partial<CIEC_WORD>(0)),4);
  set4X_E((nTestDWord.partial<CIEC_WORD>(0)),0);

  BOOST_CHECK_EQUAL(nTestDWord, 0xADD511FEU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_CHANGE_CHAIN_WORD_BYTE_SET_BIT_CHECK_BIT)
{
  CIEC_DWORD nTestDWord;

  set4X_C((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(1)),4);
  set4X_E((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(1)),0);
  set4X_C((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(0)),4);
  set4X_0((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(0)),0);
  set4X_F((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(1)),4);
  set4X_F((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(1)),0);
  set4X_E((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0)),4);
  set4X_E((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0)),0);

  test4X_C(nTestDWord,28);
  test4X_E(nTestDWord,24);
  test4X_C(nTestDWord,20);
  test4X_0(nTestDWord,16);
  test4X_F(nTestDWord,12);
  test4X_F(nTestDWord,8);
  test4X_E(nTestDWord,4);
  test4X_E(nTestDWord,0);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_CHANGE_CHAIN_WORD_BYTE_SET_BIT_CHECK_WORD_BIT)
{
  CIEC_DWORD nTestDWord;

  set4X_C((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(1)),4);
  set4X_E((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(1)),0);
  set4X_C((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(0)),4);
  set4X_0((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(0)),0);
  set4X_F((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(1)),4);
  set4X_F((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(1)),0);
  set4X_E((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0)),4);
  set4X_E((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0)),0);

  test4X_C((nTestDWord.partial<CIEC_WORD>(1)),12);
  test4X_E((nTestDWord.partial<CIEC_WORD>(1)),8);
  test4X_C((nTestDWord.partial<CIEC_WORD>(1)),4);
  test4X_0((nTestDWord.partial<CIEC_WORD>(1)),0);
  test4X_F((nTestDWord.partial<CIEC_WORD>(0)),12);
  test4X_F((nTestDWord.partial<CIEC_WORD>(0)),8);
  test4X_E((nTestDWord.partial<CIEC_WORD>(0)),4);
  test4X_E((nTestDWord.partial<CIEC_WORD>(0)),0);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_CHANGE_CHAIN_WORD_BYTE_SET_BIT_CHECK_WORD_BYTE_BIT)
{
  CIEC_DWORD nTestDWord;

  set4X_C((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(1)),4);
  set4X_E((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(1)),0);
  set4X_C((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(0)),4);
  set4X_0((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(0)),0);
  set4X_F((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(1)),4);
  set4X_F((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(1)),0);
  set4X_E((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0)),4);
  set4X_E((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0)),0);

  test4X_C((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(1)),4);
  test4X_E((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(1)),0);
  test4X_C((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(0)),4);
  test4X_0((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(0)),0);
  test4X_F((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(1)),4);
  test4X_F((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(1)),0);
  test4X_E((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0)),4);
  test4X_E((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0)),0);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_CHANGE_CHAIN_WORD_BYTE_SET_BIT_CHECK_WORD_BYTE)
{
  CIEC_DWORD nTestDWord;

  set4X_C((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(1)),4);
  set4X_E((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(1)),0);
  set4X_C((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(0)),4);
  set4X_0((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(0)),0);
  set4X_F((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(1)),4);
  set4X_F((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(1)),0);
  set4X_E((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0)),4);
  set4X_E((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0)),0);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(1)), 0xCEU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(0)), 0xC0U);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(1)), 0xFFU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0)), 0xEEU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_CHANGE_CHAIN_WORD_BYTE_SET_BIT_CHECK_BYTE)
{
  CIEC_DWORD nTestDWord;

  set4X_C((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(1)),4);
  set4X_E((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(1)),0);
  set4X_C((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(0)),4);
  set4X_0((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(0)),0);
  set4X_F((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(1)),4);
  set4X_F((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(1)),0);
  set4X_E((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0)),4);
  set4X_E((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0)),0);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(3)), 0xCEU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(2)), 0xC0U);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(1)), 0xFFU);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(0)), 0xEEU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_CHANGE_CHAIN_WORD_BYTE_SET_BIT_CHECK_WORD)
{
  CIEC_DWORD nTestDWord;

  set4X_A((nTestDWord.partial<CIEC_WORD>(1)),12);
  set4X_D((nTestDWord.partial<CIEC_WORD>(1)),8);
  set4X_D((nTestDWord.partial<CIEC_WORD>(1)),4);
  set4X_5((nTestDWord.partial<CIEC_WORD>(1)),0);
  set4X_1((nTestDWord.partial<CIEC_WORD>(0)),12);
  set4X_1((nTestDWord.partial<CIEC_WORD>(0)),8);
  set4X_F((nTestDWord.partial<CIEC_WORD>(0)),4);
  set4X_E((nTestDWord.partial<CIEC_WORD>(0)),0);

  set4X_C((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(1)),4);
  set4X_E((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(1)),0);
  set4X_C((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(0)),4);
  set4X_0((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(0)),0);
  set4X_F((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(1)),4);
  set4X_F((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(1)),0);
  set4X_E((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0)),4);
  set4X_E((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0)),0);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(1)), 0xCEC0U);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(0)), 0xFFEEU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_CHANGE_CHAIN_WORD_BYTE_SET_BIT_CHECK_DWORD)
{
  CIEC_DWORD nTestDWord;

  set4X_A((nTestDWord.partial<CIEC_WORD>(1)),12);
  set4X_D((nTestDWord.partial<CIEC_WORD>(1)),8);
  set4X_D((nTestDWord.partial<CIEC_WORD>(1)),4);
  set4X_5((nTestDWord.partial<CIEC_WORD>(1)),0);
  set4X_1((nTestDWord.partial<CIEC_WORD>(0)),12);
  set4X_1((nTestDWord.partial<CIEC_WORD>(0)),8);
  set4X_F((nTestDWord.partial<CIEC_WORD>(0)),4);
  set4X_E((nTestDWord.partial<CIEC_WORD>(0)),0);

  set4X_C((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(1)),4);
  set4X_E((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(1)),0);
  set4X_C((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(0)),4);
  set4X_0((nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(0)),0);
  set4X_F((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(1)),4);
  set4X_F((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(1)),0);
  set4X_E((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0)),4);
  set4X_E((nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0)),0);

  BOOST_CHECK_EQUAL(nTestDWord, 0xCEC0FFEEU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_SET_VALUE_WORD_A_CHECK_WORD)
{
  CIEC_DWORD nTestDWord;
  CIEC_WORD nTestWord;

  nTestWord = CIEC_WORD(0xCAFE);

  nTestDWord.partial<CIEC_WORD>(0).setValue(nTestWord);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(1)), 0x0000);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(0)), 0xCAFE);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_SET_VALUE_WORD_A_CHECK_DWORD)
{
  CIEC_DWORD nTestDWord;
  CIEC_WORD nTestWord;

  nTestWord = CIEC_WORD(0xCAFE);
  nTestDWord.partial<CIEC_WORD>(0).setValue(nTestWord);

  BOOST_CHECK_EQUAL(nTestDWord, 0x0000CAFE);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_SET_VALUE_WORD_B_CHECK_WORD)
{
  CIEC_DWORD nTestDWord;
  CIEC_WORD nTestWord;

  nTestWord = CIEC_WORD(0xCAFE);
  nTestDWord.partial<CIEC_WORD>(0).setValue(nTestWord);

  nTestWord = CIEC_WORD(0xBAD0);
  nTestDWord.partial<CIEC_WORD>(1).setValue(nTestWord);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(1)), 0xBAD0);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(0)), 0xCAFE);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_SET_VALUE_WORD_B_CHECK_DWORD)
{
  CIEC_DWORD nTestDWord;
  CIEC_WORD nTestWord;

  nTestWord = CIEC_WORD(0xCAFE);
  nTestDWord.partial<CIEC_WORD>(0).setValue(nTestWord);

  nTestWord = CIEC_WORD(0xBAD0);
  nTestDWord.partial<CIEC_WORD>(1).setValue(nTestWord);

  BOOST_CHECK_EQUAL(nTestDWord, 0xBAD0CAFE);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_SET_VALUE_BYTE_CHECK_BYTE)
{
  CIEC_DWORD nTestDWord;
  CIEC_WORD nTestWord;
  CIEC_BYTE nTestByte;

  nTestWord = CIEC_WORD(0xCAFE);
  nTestDWord.partial<CIEC_WORD>(0).setValue(nTestWord);

  nTestWord = CIEC_WORD(0xBAD0);
  nTestDWord.partial<CIEC_WORD>(1).setValue(nTestWord);

  nTestByte = CIEC_BYTE(0x0B);
  nTestDWord.partial<CIEC_BYTE>(1).setValue(nTestByte);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(3)), 0xBA);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(2)), 0xD0);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(1)), 0x0B);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(0)), 0xFE);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_SET_VALUE_BYTE_CHECK_WORD)
{
  CIEC_DWORD nTestDWord;
  CIEC_WORD nTestWord;
  CIEC_BYTE nTestByte;

  nTestWord = CIEC_WORD(0xCAFE);
  nTestDWord.partial<CIEC_WORD>(0).setValue(nTestWord);

  nTestWord = CIEC_WORD(0xBAD0);
  nTestDWord.partial<CIEC_WORD>(1).setValue(nTestWord);

  nTestByte = CIEC_BYTE(0x0B);
  nTestDWord.partial<CIEC_BYTE>(1).setValue(nTestByte);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(1)), 0xBAD0);
  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(0)), 0x0BFE);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_SET_VALUE_BYTE_CHECK_DWORD)
{
  CIEC_DWORD nTestDWord;
  CIEC_WORD nTestWord;
  CIEC_BYTE nTestByte;

  nTestWord = CIEC_WORD(0xCAFE);
  nTestDWord.partial<CIEC_WORD>(0).setValue(nTestWord);

  nTestWord = CIEC_WORD(0xBAD0);
  nTestDWord.partial<CIEC_WORD>(1).setValue(nTestWord);

  nTestByte = CIEC_BYTE(0x0B);
  nTestDWord.partial<CIEC_BYTE>(1).setValue(nTestByte);

  BOOST_CHECK_EQUAL(nTestDWord, 0xBAD00BFE);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_SET_VALUE_WORD_BYTE_CHECK_BYTE)
{
  CIEC_DWORD nTestDWord;
  CIEC_WORD nTestWord;
  CIEC_BYTE nTestByte;

  nTestWord = CIEC_WORD(0xCAFE);
  nTestDWord.partial<CIEC_WORD>(0).setValue(nTestWord);

  nTestWord = CIEC_WORD(0xBAD0);
  nTestDWord.partial<CIEC_WORD>(1).setValue(nTestWord);

  nTestByte = CIEC_BYTE(0x0B);
  nTestDWord.partial<CIEC_BYTE>(1).setValue(nTestByte);

  nTestByte = CIEC_BYTE(0xAD);
  nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0).setValue(nTestByte);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(0)), 0xAD);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_SET_VALUE_WORD_BYTE_CHECK_WORD)
{
  CIEC_DWORD nTestDWord;
  CIEC_WORD nTestWord;
  CIEC_BYTE nTestByte;

  nTestWord = CIEC_WORD(0xCAFE);
  nTestDWord.partial<CIEC_WORD>(0).setValue(nTestWord);

  nTestWord = CIEC_WORD(0xBAD0);
  nTestDWord.partial<CIEC_WORD>(1).setValue(nTestWord);

  nTestByte = CIEC_BYTE(0x0B);
  nTestDWord.partial<CIEC_BYTE>(1).setValue(nTestByte);

  nTestByte = CIEC_BYTE(0xAD);
  nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0).setValue(nTestByte);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(0)), 0x0BAD);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_SET_VALUE_WORD_BYTE_CHECK_DWORD)
{
  CIEC_DWORD nTestDWord;
  CIEC_WORD nTestWord;
  CIEC_BYTE nTestByte;

  nTestWord = CIEC_WORD(0xCAFE);
  nTestDWord.partial<CIEC_WORD>(0).setValue(nTestWord);

  nTestWord = CIEC_WORD(0xBAD0);
  nTestDWord.partial<CIEC_WORD>(1).setValue(nTestWord);

  nTestByte = CIEC_BYTE(0x0B);
  nTestDWord.partial<CIEC_BYTE>(1).setValue(nTestByte);

  nTestByte = CIEC_BYTE(0xAD);
  nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0).setValue(nTestByte);

  BOOST_CHECK_EQUAL(nTestDWord, 0xBAD00BAD);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_SET_VALUE_WORD_BYTE_BIT_CHECK_BIT_A)
{
  CIEC_DWORD nTestDWord;
  CIEC_WORD nTestWord;
  CIEC_BYTE nTestByte;
  CIEC_BOOL nTestBool;

  nTestWord = CIEC_WORD(0xCAFE);
  nTestDWord.partial<CIEC_WORD>(0).setValue(nTestWord);

  nTestWord = CIEC_WORD(0xBAD0);
  nTestDWord.partial<CIEC_WORD>(1).setValue(nTestWord);

  nTestByte = CIEC_BYTE(0x0B);
  nTestDWord.partial<CIEC_BYTE>(1).setValue(nTestByte);

  nTestByte = CIEC_BYTE(0xAD);
  nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0).setValue(nTestByte);

  nTestBool = CIEC_BOOL(false);
  nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0).partial<CIEC_BOOL>(0).setValue(nTestBool);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BOOL>(0)), false);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_SET_VALUE_WORD_BYTE_BIT_CHECK_BYTE_A)
{
  CIEC_DWORD nTestDWord;
  CIEC_WORD nTestWord;
  CIEC_BYTE nTestByte;
  CIEC_BOOL nTestBool;

  nTestWord = CIEC_WORD(0xCAFE);
  nTestDWord.partial<CIEC_WORD>(0).setValue(nTestWord);

  nTestWord = CIEC_WORD(0xBAD0);
  nTestDWord.partial<CIEC_WORD>(1).setValue(nTestWord);

  nTestByte = CIEC_BYTE(0x0B);
  nTestDWord.partial<CIEC_BYTE>(1).setValue(nTestByte);

  nTestByte = CIEC_BYTE(0xAD);
  nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0).setValue(nTestByte);

  nTestBool = CIEC_BOOL(false);
  nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0).partial<CIEC_BOOL>(0).setValue(nTestBool);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(0)), 0xAC);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_SET_VALUE_WORD_BYTE_BIT_CHECK_WORD_A)
{
  CIEC_DWORD nTestDWord;
  CIEC_WORD nTestWord;
  CIEC_BYTE nTestByte;
  CIEC_BOOL nTestBool;

  nTestWord = CIEC_WORD(0xCAFE);
  nTestDWord.partial<CIEC_WORD>(0).setValue(nTestWord);

  nTestWord = CIEC_WORD(0xBAD0);
  nTestDWord.partial<CIEC_WORD>(1).setValue(nTestWord);

  nTestByte = CIEC_BYTE(0x0B);
  nTestDWord.partial<CIEC_BYTE>(1).setValue(nTestByte);

  nTestByte = CIEC_BYTE(0xAD);
  nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0).setValue(nTestByte);

  nTestBool = CIEC_BOOL(false);
  nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0).partial<CIEC_BOOL>(0).setValue(nTestBool);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(0)), 0x0BAC);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_SET_VALUE_WORD_BYTE_BIT_CHECK_DWORD_A)
{
  CIEC_DWORD nTestDWord;
  CIEC_WORD nTestWord;
  CIEC_BYTE nTestByte;
  CIEC_BOOL nTestBool;

  nTestWord = CIEC_WORD(0xCAFE);
  nTestDWord.partial<CIEC_WORD>(0).setValue(nTestWord);

  nTestWord = CIEC_WORD(0xBAD0);
  nTestDWord.partial<CIEC_WORD>(1).setValue(nTestWord);

  nTestByte = CIEC_BYTE(0x0B);
  nTestDWord.partial<CIEC_BYTE>(1).setValue(nTestByte);

  nTestByte = CIEC_BYTE(0xAD);
  nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0).setValue(nTestByte);

  nTestBool = CIEC_BOOL(false);
  nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0).partial<CIEC_BOOL>(0).setValue(nTestBool);

  BOOST_CHECK_EQUAL(nTestDWord, 0xBAD00BAC);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_SET_VALUE_WORD_BYTE_BIT_CHECK_BIT_B)
{
  CIEC_DWORD nTestDWord;
  CIEC_WORD nTestWord;
  CIEC_BYTE nTestByte;
  CIEC_BOOL nTestBool;

  nTestWord = CIEC_WORD(0xCAFE);
  nTestDWord.partial<CIEC_WORD>(0).setValue(nTestWord);

  nTestWord = CIEC_WORD(0xBAD0);
  nTestDWord.partial<CIEC_WORD>(1).setValue(nTestWord);

  nTestByte = CIEC_BYTE(0x0B);
  nTestDWord.partial<CIEC_BYTE>(1).setValue(nTestByte);

  nTestByte = CIEC_BYTE(0xAD);
  nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0).setValue(nTestByte);

  nTestBool = CIEC_BOOL(false);
  nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0).partial<CIEC_BOOL>(0).setValue(nTestBool);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BOOL>(0)), false);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_SET_VALUE_WORD_BYTE_BIT_CHECK_BYTE_B)
{
  CIEC_DWORD nTestDWord;
  CIEC_WORD nTestWord;
  CIEC_BYTE nTestByte;
  CIEC_BOOL nTestBool;

  nTestWord = CIEC_WORD(0xCAFE);
  nTestDWord.partial<CIEC_WORD>(0).setValue(nTestWord);

  nTestWord = CIEC_WORD(0xBAD0);
  nTestDWord.partial<CIEC_WORD>(1).setValue(nTestWord);

  nTestByte = CIEC_BYTE(0x0B);
  nTestDWord.partial<CIEC_BYTE>(1).setValue(nTestByte);

  nTestByte = CIEC_BYTE(0xAD);
  nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0).setValue(nTestByte);

  nTestBool = CIEC_BOOL(false);
  nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0).partial<CIEC_BOOL>(0).setValue(nTestBool);

  nTestBool = CIEC_BOOL(true);
  nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(0).partial<CIEC_BOOL>(5).setValue(nTestBool);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_BYTE>(2)), 0xF0);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_SET_VALUE_WORD_BYTE_BIT_CHECK_WORD_B)
{
  CIEC_DWORD nTestDWord;
  CIEC_WORD nTestWord;
  CIEC_BYTE nTestByte;
  CIEC_BOOL nTestBool;

  nTestWord = CIEC_WORD(0xCAFE);
  nTestDWord.partial<CIEC_WORD>(0).setValue(nTestWord);

  nTestWord = CIEC_WORD(0xBAD0);
  nTestDWord.partial<CIEC_WORD>(1).setValue(nTestWord);

  nTestByte = CIEC_BYTE(0x0B);
  nTestDWord.partial<CIEC_BYTE>(1).setValue(nTestByte);

  nTestByte = CIEC_BYTE(0xAD);
  nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0).setValue(nTestByte);

  nTestBool = CIEC_BOOL(false);
  nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0).partial<CIEC_BOOL>(0).setValue(nTestBool);

  nTestBool = CIEC_BOOL(true);
  nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(0).partial<CIEC_BOOL>(5).setValue(nTestBool);

  BOOST_CHECK_EQUAL((nTestDWord.partial<CIEC_WORD>(1)), 0xBAF0);

}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_DWORD_SET_VALUE_WORD_BYTE_BIT_CHECK_DWORD_B)
{
  CIEC_DWORD nTestDWord;
  CIEC_WORD nTestWord;
  CIEC_BYTE nTestByte;
  CIEC_BOOL nTestBool;

  nTestWord = CIEC_WORD(0xCAFE);
  nTestDWord.partial<CIEC_WORD>(0).setValue(nTestWord);

  nTestWord = CIEC_WORD(0xBAD0);
  nTestDWord.partial<CIEC_WORD>(1).setValue(nTestWord);

  nTestByte = CIEC_BYTE(0x0B);
  nTestDWord.partial<CIEC_BYTE>(1).setValue(nTestByte);

  nTestByte = CIEC_BYTE(0xAD);
  nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0).setValue(nTestByte);

  nTestBool = CIEC_BOOL(false);
  nTestDWord.partial<CIEC_WORD>(0).partial<CIEC_BYTE>(0).partial<CIEC_BOOL>(0).setValue(nTestBool);

  nTestBool = CIEC_BOOL(true);
  nTestDWord.partial<CIEC_WORD>(1).partial<CIEC_BYTE>(0).partial<CIEC_BOOL>(5).setValue(nTestBool);

  BOOST_CHECK_EQUAL(nTestDWord, 0xBAF00BAC);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_READ_WITH_IEC_TYPE_INDEX)
{
  CIEC_DWORD nDWord(0xBE);
  CIEC_BOOL bBool;
  bBool = nDWord.partial<CIEC_BOOL>(CIEC_SINT(0));
  BOOST_TEST(static_cast<CIEC_BOOL::TValueType>(bBool) == false);

  bBool = nDWord.partial<CIEC_BOOL>(CIEC_SINT(1));
  BOOST_TEST(static_cast<CIEC_BOOL::TValueType>(bBool) == true);
}

BOOST_AUTO_TEST_CASE(PARTIAL_ACCESS_WRITE_WITH_IEC_TYPE_INDEX)
{
  CIEC_DWORD nDWord;
  nDWord.partial<CIEC_BOOL>(CIEC_SINT(0)) = CIEC_BOOL(true);
  BOOST_TEST(static_cast<CIEC_DWORD::TValueType>(nDWord) == 1U);

  nDWord.partial<CIEC_BOOL>(CIEC_SINT(1)) = CIEC_BOOL(true);
  BOOST_TEST(static_cast<CIEC_DWORD::TValueType>(nDWord) == 3U);
}

BOOST_AUTO_TEST_CASE(PARTIAL_COPY_PARTIAL_BOOL_TO_SAME_PARTIAL_BOOL) {
  CIEC_DWORD nDWord(0x00000002U);
  nDWord.partial<CIEC_BOOL>(CIEC_SINT(0)) = CIEC_BOOL(nDWord.cpartial<CIEC_BOOL>(CIEC_SINT(0)) || true);
  BOOST_TEST(static_cast<CIEC_DWORD::TValueType>(nDWord) == 0x03U);
}

BOOST_AUTO_TEST_CASE(PARTIAL_COPY_PARTIAL_BYTE_TO_SAME_PARTIAL_BYTE) {
  CIEC_DWORD nDWord(0xABCDEFFEU);
  nDWord.partial<CIEC_BYTE>(CIEC_SINT(0)) = CIEC_BYTE(
          static_cast<CIEC_BYTE::TValueType>(nDWord.cpartial<CIEC_BYTE>(CIEC_SINT(0))) | 0x01);
  BOOST_TEST(static_cast<CIEC_DWORD::TValueType>(nDWord) == 0xABCDEFFFU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_COPY_PARTIAL_WORD_TO_SAME_PARTIAL_WORD) {
  CIEC_DWORD nDWord(0xABCDEFFEU);
  nDWord.partial<CIEC_WORD>(CIEC_SINT(0)) = CIEC_WORD(
          static_cast<CIEC_WORD::TValueType>(nDWord.cpartial<CIEC_WORD>(CIEC_SINT(0))) | 0x1001);
  BOOST_TEST(static_cast<CIEC_DWORD::TValueType>(nDWord) == 0xABCDFFFFU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_COPY_PARTIAL_BOOL_TO_OTHER_PARTIAL_BOOL) {
  CIEC_DWORD nDWord(0x00000001U);
  nDWord.partial<CIEC_BOOL>(CIEC_SINT(1)) = nDWord.partial<CIEC_BOOL>(CIEC_SINT(0));
  BOOST_TEST(static_cast<CIEC_DWORD::TValueType>(nDWord) == 0x03U);
}

BOOST_AUTO_TEST_CASE(PARTIAL_COPY_PARTIAL_BYTE_TO_OTHER_PARTIAL_BYTE) {
  CIEC_DWORD nDWord(0x000000FEU);
  nDWord.partial<CIEC_BYTE>(CIEC_SINT(1)) = nDWord.partial<CIEC_BYTE>(CIEC_SINT(0));
  BOOST_TEST(static_cast<CIEC_DWORD::TValueType>(nDWord) == 0x0000FEFEU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_COPY_PARTIAL_WORD_TO_OTHER_PARTIAL_WORD) {
  CIEC_DWORD nDWord(0x000000FEU);
  nDWord.partial<CIEC_WORD>(CIEC_SINT(1)) = nDWord.partial<CIEC_WORD>(CIEC_SINT(0));
  BOOST_TEST(static_cast<CIEC_DWORD::TValueType>(nDWord) == 0x00FE00FEU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_COPY_PARTIAL_BOOL_TO_OTHER_PARTIAL_BYTE) {
  CIEC_DWORD nDWord(0x000000FEU);
  nDWord.partial<CIEC_BYTE>(CIEC_SINT(1)) = nDWord.partial<CIEC_BOOL>(CIEC_SINT(1));
  BOOST_TEST(static_cast<CIEC_DWORD::TValueType>(nDWord) == 0x000001FEU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_COPY_PARTIAL_BOOL_TO_OTHER_PARTIAL_WORD) {
  CIEC_DWORD nDWord(0x000000FEU);
  nDWord.partial<CIEC_WORD>(CIEC_SINT(1)) = nDWord.partial<CIEC_BOOL>(CIEC_SINT(1));
  BOOST_TEST(static_cast<CIEC_DWORD::TValueType>(nDWord) == 0x000100FEU);
}

BOOST_AUTO_TEST_CASE(PARTIAL_COPY_PARTIAL_BYTE_TO_OTHER_PARTIAL_WORD) {
  CIEC_DWORD nDWord(0x000000FEU);
  nDWord.partial<CIEC_WORD>(CIEC_SINT(1)) = nDWord.partial<CIEC_BYTE>(CIEC_SINT(0));
  BOOST_TEST(static_cast<CIEC_DWORD::TValueType>(nDWord) == 0x00FE00FEU);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
