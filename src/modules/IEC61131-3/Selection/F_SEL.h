/*******************************************************************************
 * Copyright (c) 2011 - 2019 ACIN, fortiss GmbH
 *               2023 Martin Erich Jobst
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Monika Wenger, Alois Zoitl
 *   - initial API and implementation and/or initial documentation
 *   Jose Cabral:
 *   - Fix calculateValueString to use template variable
 *   Martin Jobst
 *     - refactor for ANY variant
 *******************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_bool.h"
#include "forte_any_variant.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class FORTE_F_SEL: public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_F_SEL)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  
  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  
  static const TEventID scm_nEventREQID = 0;
  
  static const TDataIOID scm_anEIWith[];
  static const TForteInt16 scm_anEIWithIndexes[];
  static const CStringDictionary::TStringId scm_anEventInputNames[];
  
  static const TEventID scm_nEventCNFID = 0;
  
  static const TDataIOID scm_anEOWith[]; 
  static const TForteInt16 scm_anEOWithIndexes[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];
  

  static const SFBInterfaceSpec scm_stFBInterfaceSpec;

  void executeEvent(TEventID pa_nEIID);

  void readInputData(TEventID pa_nEIID) override;
  void writeOutputData(TEventID pa_nEIID) override;

public:
  FORTE_F_SEL(const CStringDictionary::TStringId pa_nInstanceNameId, CResource *pa_poSrcRes);

  CIEC_BOOL var_G;
  CIEC_ANY_VARIANT var_IN0;
  CIEC_ANY_VARIANT var_IN1;
  CIEC_ANY_VARIANT var_OUT;
  
  CIEC_ANY_VARIANT var_conn_OUT;
  CEventConnection conn_CNF;
  CDataConnection *conn_G;
  CDataConnection *conn_IN0;
  CDataConnection *conn_IN1;
  CDataConnection conn_OUT;
  
  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;
  
  void evt_REQ(const CIEC_BOOL &pa_G, const CIEC_ANY_VARIANT &pa_IN0, const CIEC_ANY_VARIANT &pa_IN1, CIEC_ANY_VARIANT &pa_OUT) {
    var_G = pa_G;
    var_IN0 = pa_IN0;
    var_IN1 = pa_IN1;
    receiveInputEvent(scm_nEventREQID, nullptr);
    pa_OUT = var_OUT;
  }
  
  void operator()(const CIEC_BOOL &pa_G, const CIEC_ANY_VARIANT &pa_IN0, const CIEC_ANY_VARIANT &pa_IN1, CIEC_ANY_VARIANT &pa_OUT) {
    evt_REQ(pa_G, pa_IN0, pa_IN1, pa_OUT);
  }
  
};



