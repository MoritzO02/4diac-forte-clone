/*******************************************************************************
 * Copyright (c) 2017-2018 Marc Jakobi, github.com/MrcJkb
 *                         fortiss GmbH
 *                         Primetals Austria GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Marc Jakobi - initial implementation
 *    Jose Cabral - Use CIEC_STRING instead of const char* and cleanning of functions
 *    Martin Melik Merkumians - Change CIEC_STRING to std::string
 ********************************************************************************/

#ifndef _HTTPIPPARSER_H_
#define _HTTPIPPARSER_H_

#include <forte_string.h>
#include "httplayer.h"
#include "fortelist.h"

namespace forte {

  namespace com_infra {

    class CHttpParser {
      public:
        /**
         * Generates a HTTP GET request. The request is written to paDest
         * @param paDest place to store the request
         * @param paHost host of the server to connect
         * @param paPort port of the server to connect
         * @param paPath path to look for
         * @param paParams parameters to consider for the request
         */
        static void createGetRequest(std::string& paDest, const std::string& paHost, const TForteUInt16 paPort, const std::string& paPath, const std::string &paAuth, const std::string& paParams);

        /**
         * Generates a HTTP PUT request. The request is written to paDest.
         * @param paDest place to store the request
         * @param paHost host of the server to connect
         * @param paPort port of the server to connect
         * @param paPath path to access in the server
         * @param paParams parameters to consider for the request
         * @param paData data in the body to send to the server
         * @param paContentType content type of the request
         * @param paType PUT or POST
         */
        static void createPutPostRequest(std::string& paDest, const std::string& paHost, const TForteUInt16 paPort, const std::string& paPath, const std::string &paAuth, const std::string& paParams, const std::string& paBody,
            const std::string& paContentType, CHttpComLayer::ERequestType paType);

        /**
         * Adds a body to the request.
         * @param paDest old request
         * @param paContentType type of the body
         * @param paBody body of the request
         */
        static void addBodyToRequest (const std::string &paBody, const std::string &paContentType, std::string &paDest);

        /**
         * Extracts data from a response to a HTTP request
         * @param paDest place to store the body of the response
         * @param paResponseCode place to store the response code of the response
         * @param paSrc response received
         * @return true if no error happened, false otherwise
         */
        static bool parseResponse(std::string& paBody, std::string& paResponseCode, char* paSrc);

        /**
         * Parse a GET request received as a server
         * @param paPath place to store the received path
         * @param paParameterNames place to store the names of the parameters
         * @param paParameterValues place to store the value of the parameters
         * @param paData the received  GET request
         * @return true if no error happened, false otherwise
         */
        static bool parseGetRequest(std::string& paPath, CSinglyLinkedList<std::string>& paParameterNames, CSinglyLinkedList<std::string>& paParameterValues,
            char* paData);

        /**
         * Parse a PUT/POST request received as a server
         * @param paPath place to store the received path
         * @param paContent place to store the content of the request
         * @param paData the received PUT/POST  request
         * @return true if no error happened, false otherwise
         */
        static bool parsePutPostRequest(std::string& paPath, std::string &paContent, char* paData);

        /**
         * Create a HTTP response
         * @param paDest
         * @param paResult the status line of the response
         * @param paContentType the content type of the response
         * @param paData the body of the response
         */
        static void createResponse(std::string& paDest, const std::string& paResult, const std::string& paContentType, const std::string& paData);

        /**
         * Look in the request for its type
         * @param paRequest request to look into
         * @return Type of request
         */
        static CHttpComLayer::ERequestType getTypeOfRequest(const char* paRequest);

        CHttpParser() = delete;
        virtual ~CHttpParser() = delete;

      private:
        /**
         *  Creates the common parts of the headers of the supported types
         * @param paDest place to store the header
         * @param paHost server host to be written in the header
         * @param paPort server port to be written in the header
         * @param paPath the path to be written in the header
         * @param paParams parameters to consider for the request
         * @param paType the type of request to be written in the header
         */
        static void addCommonHeader (std::string &paDest, const std::string &paHost, const TForteUInt16 paPort, const std::string &paPath, const std::string &paAuth, const std::string &paParams, CHttpComLayer::ERequestType paType);

        /**
         * Appends the ending "\r\n\r\n" to the HTTP request
         * @param paDest place to store the header
         */
        static void addHeaderEnding(std::string& paDest);

        /**
         * Extracts the HTTP response
         * @param paDest place to store the header
         * @param paSrc source of the reponse
         * @return true if no error happened, false otherwise
         */
        static bool getHttpResponseCode(std::string& paDest, char* paSrc);

        /**
         * Parse parameter of GET request as a server
         * @param paParameters The string containing the parameters of the request
         * @param paParameterNames The result where the names of the parameters are stored
         * @param paParameterValues The result where the values of the parameters are stored
         * @return The number of parameters found. If wrong parameters are found, the result is treated as no parameters, meaning it returns zero
         */
        static unsigned int parseGETParameters(char* paParameters, CSinglyLinkedList<std::string>& paParameterNames,
            CSinglyLinkedList<std::string>& paParameterValues);
    };
  }
}

#endif /* _HTTPIPPARSER_H_ */
