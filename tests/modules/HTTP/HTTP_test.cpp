/*******************************************************************************
 * Copyright (c) 2018 fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Jose Cabral - initial API and implementation and/or initial documentation
 *******************************************************************************/
#include <boost/test/unit_test.hpp>

#include "../../../src/com/HTTP/httpparser.h"
using namespace std::string_literals;

BOOST_AUTO_TEST_SUITE (HTTPParser_function_test)

  BOOST_AUTO_TEST_CASE(createGetRequest_test) {
    std::string dest = "random text"s;
    std::string host = "0.0.0.0"s;
    short unsigned int port = 80;
    std::string path = "/"s;
    std::string auth = ""s;
    std::string params = ""s;

    const char* resultValid1 = "GET / HTTP/1.1\r\nHost: 0.0.0.0:80\r\n\r\n";
    forte::com_infra::CHttpParser::createGetRequest(dest, host, port, path, auth, params);
    BOOST_TEST(dest == resultValid1);

    const char* resultValid2 = "GET / HTTP/1.1\r\nHost: 192.168.0.1:80\r\n\r\n";
    host = "192.168.0.1";
    forte::com_infra::CHttpParser::createGetRequest(dest, host, port, path, auth, params);
    BOOST_TEST(dest == resultValid2);

    const char* resultValid3 = "GET /lookFor HTTP/1.1\r\nHost: 192.168.0.1:80\r\n\r\n";
    path = "/lookFor";
    forte::com_infra::CHttpParser::createGetRequest(dest, host, port, path, auth, params);
    BOOST_TEST(dest == resultValid3);

    const char* resultValid4 = "GET /lookFor/something/else HTTP/1.1\r\nHost: 192.168.0.1:80\r\n\r\n";
    path = "/lookFor/something/else";
    forte::com_infra::CHttpParser::createGetRequest(dest, host, port, path, auth, params);
    BOOST_TEST(dest == resultValid4);
  }

  BOOST_AUTO_TEST_CASE(PUTPOST_test) {
    std::string dest = "random text"s;
    std::string destEmpty;
    std::string host = "0.0.0.0"s;
    short unsigned int port = 80;
    std::string path = "/"s;
    std::string auth = ""s;
    std::string params = "key1=val1;key2=val2"s;
    std::string body = "content of the body"s;
    std::string contentType = "text/xml"s;

    const char* putResultValid1 = "PUT /?key1=val1;key2=val2 HTTP/1.1\r\nHost: 0.0.0.0:80\r\nContent-Type: text/xml\r\nContent-Length: 19\r\n\r\ncontent of the body";
    const char* postResultValid1 = "POST /?key1=val1;key2=val2 HTTP/1.1\r\nHost: 0.0.0.0:80\r\nContent-Type: text/xml\r\nContent-Length: 19\r\n\r\ncontent of the body";
    forte::com_infra::CHttpParser::createPutPostRequest(dest, host, port, path, auth, params, body, contentType, forte::com_infra::CHttpComLayer::e_PUT);
    BOOST_TEST(dest == putResultValid1);
    forte::com_infra::CHttpParser::createPutPostRequest(dest, host, port, path, auth, params, body, contentType, forte::com_infra::CHttpComLayer::e_POST);
    BOOST_TEST(dest == postResultValid1);

    const char* putResultValid2 = "PUT /?key1=val1;key2=val2 HTTP/1.1\r\nHost: 192.168.0.1:80\r\nContent-Type: text/xml\r\nContent-Length: 19\r\n\r\ncontent of the body";
    const char* postResultValid2 = "POST /?key1=val1;key2=val2 HTTP/1.1\r\nHost: 192.168.0.1:80\r\nContent-Type: text/xml\r\nContent-Length: 19\r\n\r\ncontent of the body";
    host = "192.168.0.1"s;
    forte::com_infra::CHttpParser::createPutPostRequest(dest, host, port, path, auth, params, body, contentType, forte::com_infra::CHttpComLayer::e_PUT);
    BOOST_TEST(dest == putResultValid2);
    forte::com_infra::CHttpParser::createPutPostRequest(dest, host, port, path, auth, params, body, contentType, forte::com_infra::CHttpComLayer::e_POST);
    BOOST_TEST(dest == postResultValid2);

    const char* putResultValid3 = "PUT /lookFor?key1=val1;key2=val2 HTTP/1.1\r\nHost: 192.168.0.1:80\r\nContent-Type: text/xml\r\nContent-Length: 19\r\n\r\ncontent of the body";
    const char* postResultValid3 = "POST /lookFor?key1=val1;key2=val2 HTTP/1.1\r\nHost: 192.168.0.1:80\r\nContent-Type: text/xml\r\nContent-Length: 19\r\n\r\ncontent of the body";
    path = "/lookFor"s;
    forte::com_infra::CHttpParser::createPutPostRequest(dest, host, port, path, auth, params, body, contentType, forte::com_infra::CHttpComLayer::e_PUT);
    BOOST_TEST(dest == putResultValid3);
    forte::com_infra::CHttpParser::createPutPostRequest(dest, host, port, path, auth, params, body, contentType, forte::com_infra::CHttpComLayer::e_POST);
    BOOST_TEST(dest == postResultValid3);

    const char* putResultValid4 = "PUT /lookFor/something/else?key1=val1;key2=val2 HTTP/1.1\r\nHost: 192.168.0.1:80\r\nContent-Type: text/xml\r\nContent-Length: 19\r\n\r\ncontent of the body";
    const char* postResultValid4 = "POST /lookFor/something/else?key1=val1;key2=val2 HTTP/1.1\r\nHost: 192.168.0.1:80\r\nContent-Type: text/xml\r\nContent-Length: 19\r\n\r\ncontent of the body";
    path = "/lookFor/something/else"s;
    forte::com_infra::CHttpParser::createPutPostRequest(dest, host, port, path, auth, params, body, contentType, forte::com_infra::CHttpComLayer::e_PUT);
    BOOST_TEST(dest == putResultValid4);
    forte::com_infra::CHttpParser::createPutPostRequest(dest, host, port, path, auth, params, body, contentType, forte::com_infra::CHttpComLayer::e_POST);
    BOOST_TEST(dest == postResultValid4);

    const char* putEmptyData = "PUT /lookFor/something/else?key1=val1;key2=val2 HTTP/1.1\r\nHost: 192.168.0.1:80\r\nContent-Type: text/xml\r\nContent-Length: 0\r\n\r\n";
    const char* postEmptyData = "POST /lookFor/something/else?key1=val1;key2=val2 HTTP/1.1\r\nHost: 192.168.0.1:80\r\nContent-Type: text/xml\r\nContent-Length: 0\r\n\r\n";
    body.clear();
    forte::com_infra::CHttpParser::createPutPostRequest(dest, host, port, path, auth, params, body, contentType, forte::com_infra::CHttpComLayer::e_PUT);
    BOOST_TEST(dest == putEmptyData);
    forte::com_infra::CHttpParser::createPutPostRequest(dest, host, port, path, auth, params, body, contentType, forte::com_infra::CHttpComLayer::e_POST);
    BOOST_TEST(dest == postEmptyData);

    const char* putJSONType = "PUT /lookFor/something/else?key1=val1;key2=val2 HTTP/1.1\r\nHost: 192.168.0.1:80\r\nContent-Type: application/json\r\nContent-Length: 29\r\n\r\n{\"key1\" : val1,\"key2\" : val2}";
    const char* postJSONType = "POST /lookFor/something/else?key1=val1;key2=val2 HTTP/1.1\r\nHost: 192.168.0.1:80\r\nContent-Type: application/json\r\nContent-Length: 29\r\n\r\n{\"key1\" : val1,\"key2\" : val2}";
    contentType = "application/json"s;
    body = "{\"key1\" : val1,\"key2\" : val2}"s;
    forte::com_infra::CHttpParser::createPutPostRequest(dest, host, port, path, auth, params, body, contentType, forte::com_infra::CHttpComLayer::e_PUT);
    BOOST_TEST(dest == putJSONType);
    forte::com_infra::CHttpParser::createPutPostRequest(dest, host, port, path, auth, params, body, contentType, forte::com_infra::CHttpComLayer::e_POST);
    BOOST_TEST(dest == postJSONType);

    const char* putWithoutParams = "PUT /lookFor/something/else HTTP/1.1\r\nHost: 192.168.0.1:80\r\nContent-Type: application/json\r\nContent-Length: 29\r\n\r\n{\"key1\" : val1,\"key2\" : val2}";
    const char* postWithoutParams = "POST /lookFor/something/else HTTP/1.1\r\nHost: 192.168.0.1:80\r\nContent-Type: application/json\r\nContent-Length: 29\r\n\r\n{\"key1\" : val1,\"key2\" : val2}";
    params = ""s;
    forte::com_infra::CHttpParser::createPutPostRequest(dest, host, port, path, auth, params, body, contentType, forte::com_infra::CHttpComLayer::e_PUT);
    BOOST_TEST(dest == putWithoutParams);
    forte::com_infra::CHttpParser::createPutPostRequest(dest, host, port, path, auth, params, body, contentType, forte::com_infra::CHttpComLayer::e_POST);
    BOOST_TEST(dest == postWithoutParams);

    const char* putWithAuth = "PUT /lookFor/something/else HTTP/1.1\r\nHost: 192.168.0.1:80\r\nAuthorization: Token hereComesTheToken\r\nContent-Type: application/json\r\nContent-Length: 29\r\n\r\n{\"key1\" : val1,\"key2\" : val2}";
    const char* postWitAuth = "POST /lookFor/something/else HTTP/1.1\r\nHost: 192.168.0.1:80\r\nAuthorization: Token hereComesTheToken\r\nContent-Type: application/json\r\nContent-Length: 29\r\n\r\n{\"key1\" : val1,\"key2\" : val2}";
    auth = "Token hereComesTheToken"s;
    forte::com_infra::CHttpParser::createPutPostRequest(dest, host, port, path, auth, params, body, contentType, forte::com_infra::CHttpComLayer::e_PUT);
    BOOST_TEST(dest == putWithAuth);
    forte::com_infra::CHttpParser::createPutPostRequest(dest, host, port, path, auth, params, body, contentType, forte::com_infra::CHttpComLayer::e_POST);
    BOOST_TEST(dest == postWitAuth);
  }

  BOOST_AUTO_TEST_CASE(parseResponse_test) {
    std::string validReponse = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nkey1=val1;key2=val2"s;
    std::string validReponseNoBody = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: 0\r\n\r\n"s;
    std::string worngFirstLine = "HTTP/1.1 200 OK\nContent-Type: text/html"s;
    std::string worngStatusLine = "HTTP/1.1 200OK\r\nContent-Type: text/html\r\n\r\nkey1=val1;key2=val2"s;
    std::string body;
    std::string responseCode;

    BOOST_TEST(true == forte::com_infra::CHttpParser::parseResponse(body, responseCode, validReponse.data()));
    BOOST_TEST(body == "key1=val1;key2=val2"s);
    BOOST_TEST(responseCode == "200"s);

    responseCode.clear();
    BOOST_TEST(true == forte::com_infra::CHttpParser::parseResponse(body, responseCode, validReponseNoBody.data()));
    BOOST_TEST(body == ""s);
    BOOST_TEST(responseCode == "200"s);

    BOOST_TEST(false == forte::com_infra::CHttpParser::parseResponse(body, responseCode, worngFirstLine.data()));
    BOOST_TEST(false == forte::com_infra::CHttpParser::parseResponse(body, responseCode, worngStatusLine.data()));
  }

  BOOST_AUTO_TEST_CASE(createResponse_test) {
    std::string dest;
    std::string result = "HTTP/1.1 200 OK"s;
    std::string contentType = "application/json"s;
    std::string data = "{\"key1\" : val1,\"key2\" : val2}"s;

    const char* validResult = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: 29\r\n\r\n{\"key1\" : val1,\"key2\" : val2}";
    forte::com_infra::CHttpParser::createResponse(dest, result, contentType, data);
    BOOST_TEST(dest == validResult);

    const char* validResultNoBody = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: 0\r\n\r\n";
    data.clear();
    forte::com_infra::CHttpParser::createResponse(dest, result, contentType, data);
    BOOST_TEST(dest == validResultNoBody);
  }

  BOOST_AUTO_TEST_CASE(parseGetRequest_test) {
    std::string resultValidNoParameters = "GET / HTTP/1.1\r\nHost: 0.0.0.0\r\n\r\n"s;
    std::string resultValidNoParameters2 = "GET /path/to/look HTTP/1.1\r\nHost: 0.0.0.0\r\n\r\n"s;
    std::string resultValidParam = "GET /?key1=val1 HTTP/1.1\r\nHost: 0.0.0.0\r\n\r\n"s;
    std::string resultValidParams = "GET /?key1=val1&key2=val2 HTTP/1.1\r\nHost: 0.0.0.0\r\n\r\n"s;
    std::string resultValidParam2 = "GET /path/to/look?key1=val1 HTTP/1.1\r\nHost: 0.0.0.0\r\n\r\n"s;
    std::string resultValidParams2 = "GET /path/to/look?key1=val1&key2=val2 HTTP/1.1\r\nHost: 0.0.0.0\r\n\r\n"s;
    std::string invalidGET = "Get / HTTP/1.1\r\nHost: 0.0.0.0\r\n\r\n"s;
    std::string invalidPath = "GET /pathHTTP/1.1\r\n"s;

    std::string path;
    CSinglyLinkedList<std::string> parameterNames;
    CSinglyLinkedList<std::string> parameterValues;

    BOOST_TEST(true == forte::com_infra::CHttpParser::parseGetRequest(path, parameterNames, parameterValues, resultValidNoParameters.data()));
    BOOST_TEST(path == "/"s);
    BOOST_TEST(true == parameterNames.isEmpty());
    BOOST_TEST(true == parameterValues.isEmpty());

    BOOST_TEST(true == forte::com_infra::CHttpParser::parseGetRequest(path, parameterNames, parameterValues, resultValidNoParameters2.data()));
    BOOST_TEST(path == "/path/to/look"s);
    BOOST_TEST(true == parameterNames.isEmpty());
    BOOST_TEST(true == parameterValues.isEmpty());

    BOOST_TEST(true == forte::com_infra::CHttpParser::parseGetRequest(path, parameterNames, parameterValues, resultValidParam.data()));
    BOOST_TEST(path == "/"s);

    CSinglyLinkedList<std::string>::Iterator namesIter = parameterNames.begin();
    CSinglyLinkedList<std::string>::Iterator valuesIter = parameterValues.begin();

    BOOST_TEST((*namesIter) == "key1"s);
    BOOST_TEST((*valuesIter) == "val1"s);

    parameterNames.clearAll();
    parameterValues.clearAll();

    BOOST_TEST(true, forte::com_infra::CHttpParser::parseGetRequest(path, parameterNames, parameterValues, resultValidParams.data()));
    BOOST_TEST(path == "/");

    namesIter = parameterNames.begin();
    valuesIter = parameterValues.begin();

    BOOST_TEST((*namesIter) == "key1"s);
    BOOST_TEST((*valuesIter) == "val1"s);
    ++namesIter;
    ++valuesIter;
    BOOST_TEST((*namesIter) == "key2"s);
    BOOST_TEST((*valuesIter) == "val2"s);

    parameterNames.clearAll();
    parameterValues.clearAll();

    BOOST_TEST(true == forte::com_infra::CHttpParser::parseGetRequest(path, parameterNames, parameterValues, resultValidParam2.data()));
    BOOST_TEST(path == "/path/to/look"s);

    namesIter = parameterNames.begin();
    valuesIter = parameterValues.begin();

    BOOST_TEST((*namesIter) == "key1"s);
    BOOST_TEST((*valuesIter) == "val1"s);

    parameterNames.clearAll();
    parameterValues.clearAll();

    BOOST_TEST(true == forte::com_infra::CHttpParser::parseGetRequest(path, parameterNames, parameterValues, resultValidParams2.data()));
    BOOST_TEST(path == "/path/to/look"s);

    namesIter = parameterNames.begin();
    valuesIter = parameterValues.begin();

    BOOST_TEST((*namesIter) == "key1"s);
    BOOST_TEST((*valuesIter) == "val1");
    ++namesIter;
    ++valuesIter;
    BOOST_TEST((*namesIter) == "key2"s);
    BOOST_TEST((*valuesIter) == "val2"s);

    BOOST_TEST(false == forte::com_infra::CHttpParser::parseGetRequest(path, parameterNames, parameterValues, invalidGET.data()));
    BOOST_TEST(false == forte::com_infra::CHttpParser::parseGetRequest(path, parameterNames, parameterValues, invalidPath.data()));
  }

  BOOST_AUTO_TEST_SUITE_END()
