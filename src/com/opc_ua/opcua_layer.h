/*******************************************************************************
 * Copyright (c) 2015-2023 Florian Froschermeier <florian.froschermeier@tum.de>,
 *               fortiss GmbH, Primetals Technologies Austria GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Florian Froschermeier
 *      - initial integration of the OPC-UA protocol
 *    Stefan Profanter
 *      - refactoring and adaption to new concept
 *    Jose Cabral:
 *      - refactoring to cleaner architecture
 *    Markus Meingast:
 *      - add support for Object Structs
 *******************************************************************************/

#ifndef SRC_MODULES_OPC_UA_OPCUA_LAYER_H_
#define SRC_MODULES_OPC_UA_OPCUA_LAYER_H_

#include "../../core/cominfra/comlayer.h"
#include "opcua_helper.h"
#include <memory>

class COPC_UA_HandlerAbstract;
class CActionInfo;
class COPC_UA_ObjectStruct_Helper;

/**
 * Layer for the OPC UA communication. It is responsible for getting the type converters from its SDs/RDs,
 * creating an action out of its parameter, and calling the local/remote handler when the action is to be executed
 and
 */
class COPC_UA_Layer : public forte::com_infra::CComLayer {
  public:

    /**
     * Class constructor
     * @param paUpperLayer
     * @param paComFB
     */
    COPC_UA_Layer(forte::com_infra::CComLayer *paUpperLayer, forte::com_infra::CBaseCommFB *paComFB);

    /**
     * Class destructor
     */
    ~COPC_UA_Layer() override;

    /**
     * The handler uses this functions to let the layer know that some data has arrived
     * @param paData Data of type COPC_UA_Helper::UA_RecvVariable_handle passed from the handler
     * @param paSize not used
     * @return
     */
    forte::com_infra::EComResponse recvData(const void *paData, unsigned int paSize) override;

    /**
     * Executes the action in the handler
     * @param paData not used
     * @param paSize not used
     * @return
     */
    forte::com_infra::EComResponse sendData(void *paData, unsigned int paSize) override;

    /**
     * Function called when the external event (triggered when data is received) is executed in the FB
     * @return
     */
    forte::com_infra::EComResponse processInterrupt() override;

    /**
     * Trigger a new incoming event. This is needed here because the CUA_ClientInformation needs to trigger, but it doesn't know the handler
     */
    void triggerNewEvent();

  private:

    /**
     * Response for the processInterrupt() method
     */
    forte::com_infra::EComResponse mInterruptResp;

    /**
     * Pointer to the base class of the OPC UA handlers. Depending on the action, the local or remote will be set, and later used to execute the action
     */
    COPC_UA_HandlerAbstract *mHandler;

    /**
     * Information about the action that's returned from the CActionInfo factory, and which is later passed to the handler when initializing, executing and uninitializing the action
     */
    std::unique_ptr<CActionInfo> mActionInfo;

    /**
     * Called when INIT is triggered in the FB and QI is set to true
     * @param paLayerParameter String conatained between the square brackets in the ID data input (opc_ua[...])
     * @return e_InitOk is initialization was ok, e_InitTerminated otherwise
     */
    forte::com_infra::EComResponse openConnection(char *paLayerParameter) override;

    /**
     * Called when INIT is triggered in the FB and QI is set to false
     */
    void closeConnection() override;

    /**
     * Check that all types of the SDs/RDs of the FBs are correct
     * @return True if no problem occurred, false otherwise
     */
    bool checkTypesFromInterface() const;

    /**
     * Check the type for a specific data input or output of the FB
     * @param paPortIndex Index of the port to be gotten
     * @param paIsSD True if the port to get is an SD, false othewise
     * @return True if no error ocurred while looking for the type, false otherwise
     */
    bool checkPortConnectionInfo(unsigned int paPortIndex, bool paIsSD) const;

    /**
     * The following functions and variables are used because if many subscription are present in one FB, and all of them are updated,
     * we'll get one external event for each, when only one is needed.
     * TODO: this is a quick fix. This is a problem for any FB which has many RDs, meaning that if any of the RDs changes, an IND is triggered. It's not wrong,
     * but the tests lead to an overflow of external events, and this reduces a little.
     */
    void setDataAlreadyPresentRead(bool paDataRead);
    bool getDataAlreadyPresentRead();
    CSyncObject mDataAlreadyPresentMutex;
    bool mDataAlreadyPresent;

    bool mIsObjectNodeStruct;

    std::unique_ptr<COPC_UA_ObjectStruct_Helper> mStructObjectHelper;

    /**
     * Get the port connection pointer for a connected data port
     * @param paPortIndex The Index of the data port
     * @param paIsSD True if the port to get is an SD, false othewise
     * @return The pointer to the local port connection
    */
    const CDataConnection* getLocalPortConnection(int paPortIndex, bool paIsSD) const;

    /**
     * Get the id of the specified local data port name
     * @param paPortIndex The Index of the data port
     * @param paIsSD True if the port to get is an SD, false othewise
     * @return The pointer to the local port connection
    */
    CStringDictionary::TStringId getLocalPortNameId(int paPortIndex, bool paIsSD) const;

    /**
     * List of ANY pointers used as buffer to store the received data
     */
    std::vector<std::unique_ptr<CIEC_ANY>> mRDBuffer;

    /**
     * Mutex to access the mRDBuffer
     */
    CSyncObject mRDBufferMutex;
};

#endif /* SRC_MODULES_OPC_UA_OPCUA_LAYER_H_ */

