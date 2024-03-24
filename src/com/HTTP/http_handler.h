/*******************************************************************************
 * Copyright (c) 2018, 2023 fortiss GmbH
 *               HIT robot group
 *               Primetals Austria GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Jose Cabral - initial API and implementation and/or initial documentation
 *    Tibalt Zhao - remove the client http layer when socket error in recv
 *    Martin Melik Merkumians - Change CIEC_STRING to std::string
 *******************************************************************************/

#ifndef SRC_MODULES_HTTP_OPCUAHANDLER_H_
#define SRC_MODULES_HTTP_OPCUAHANDLER_H_

#include <forte_thread.h>
#include <extevhan.h>
#include <conn.h>
#include <stdio.h>
#include <sockhand.h>
#include "forte_string.h"
#include "httplayer.h"
#include "comCallback.h"
#include "forte_date_and_time.h"

// cppcheck-suppress noConstructor
class CHTTP_Handler : public CExternalEventHandler, public CThread, public forte::com_infra::CComCallback {
  DECLARE_HANDLER(CHTTP_Handler)

  public:
    /* functions needed for the external event handler interface */
    void enableHandler() override;

    void disableHandler() override;

    void setPriority(int paPriority) override;

    int getPriority() const override;

    forte::com_infra::EComResponse recvData(const void *paData, unsigned int paSize) override;

    bool sendClientData(forte::com_infra::CHttpComLayer *paLayer, const std::string &paToSend);

    bool addServerPath(forte::com_infra::CHttpComLayer *paLayer, const std::string &paPath);

    void removeServerPath(const std::string &paPath);

    void sendServerAnswer(forte::com_infra::CHttpComLayer *paLayer, const std::string &paAnswer);

    void sendServerAnswerFromRecv(forte::com_infra::CHttpComLayer *paLayer, const std::string &paAnswer);

    void forceClose(forte::com_infra::CHttpComLayer* paLayer);

    void forceCloseFromRecv(forte::com_infra::CHttpComLayer* paLayer);

  private:

    /**
     * Overridden run() from CThread which loops the UA Server.
     */
    void run() override;

    void checkClientLayers();

    void checkAcceptedSockets();

    void startTimeoutThread();

    void stopTimeoutThread();

    void openHTTPServer();

    void closeHTTPServer();

    void removeAndCloseSocket(const CIPComSocketHandler::TSocketDescriptor paSocket);

    bool removeHTTPLayerFromClientList(const CIPComSocketHandler::TSocketDescriptor paSocket);

    void resumeSelfsuspend();

    void selfSuspend();

    void sendServerAnswerHelper(forte::com_infra::CHttpComLayer *paLayer, const std::string &paAnswer, bool paFromRecv);

    void forceCloseHelper(forte::com_infra::CHttpComLayer* paLayer, bool paFromRecv);

    bool recvClients(const CIPComSocketHandler::TSocketDescriptor paSocket, const int paRecvLength);

    bool recvServers(const CIPComSocketHandler::TSocketDescriptor paSocket);

    void removeSocketFromAccepted(const CIPComSocketHandler::TSocketDescriptor paSocket);

    void handlerReceivedWrongPath(const CIPComSocketHandler::TSocketDescriptor paSocket, const std::string &paPath);

    void clearServerLayers();

    void clearClientLayers();

    void clearAcceptedSockets();

    struct HTTPServerWaiting {
        forte::com_infra::CHttpComLayer* mLayer;
        std::string mPath;
        CSinglyLinkedList<CIPComSocketHandler::TSocketDescriptor> mSockets; //to handle many connections to the same path
    };

    struct HTTPClientWaiting {
        forte::com_infra::CHttpComLayer* mLayer;
        CIPComSocketHandler::TSocketDescriptor mSocket;
        CIEC_TIME mStartTime;
    };

    struct HTTPAcceptedSockets {
        CIPComSocketHandler::TSocketDescriptor mSocket;
        CIEC_TIME mStartTime;
    };

    CSinglyLinkedList<HTTPServerWaiting*> mServerLayers;
    CSyncObject mServerMutex;

    CSinglyLinkedList<HTTPClientWaiting*> mClientLayers;
    CSyncObject mClientMutex;

    CSinglyLinkedList<HTTPAcceptedSockets*> mAcceptedSockets;
    CSyncObject mAcceptedMutex;

    CSemaphore mSuspendSemaphore;

    static CIPComSocketHandler::TSocketDescriptor smServerListeningSocket;

    static char sRecvBuffer[cgIPLayerRecvBufferSize];
    static unsigned int sBufFillSize;

    static const unsigned int scmSendTimeout;
    static const unsigned int scmAcceptedTimeout;

    CSemaphore mThreadStarted;
};

#endif /* SRC_MODULES_HTTP_OPCUAHANDLER_H_ */
