/*******************************************************************************
 * Copyright (c) 2006, 2023 ACIN, Profactor GmbH, AIT, fortiss GmbH,
 *                          Primetals Technologies Austria GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *  Alois Zoitl, Gerhard Ebenhofer, Thomas Strasser, Rene Smodic,
 *  Martin Melik Merkumians, Ingo Hegny, Filip Andren - initial API and implementation and/or initial documentation
 *  Tarik Terzimehic - make OPC UA server port setable from the command line
 *******************************************************************************/
#include <fortenew.h>
#include <stdio.h>
#include <signal.h>
#include "../startuphook.h"
#include "../../stdfblib/ita/RMT_DEV.h"

#include "../utils/mainparam_utils.h"

#ifdef FORTE_IO_PLCNEXT
#include "../../modules/PLCnext/plcNextDeviceStatus.h"
#endif

#ifdef __UCLIBC__
extern "C" {
  void * __stack_chk_guard = 0;

  void __stack_chk_guard_setup(void) {
    unsigned char *p;
    p = (unsigned char *) &__stack_chk_guard;

    p[0] = 0;
    p[1] = 0;
    p[2] = '\n';
    p[3] = 255;	// XXX: Random this
  }

  /*
   * This is called if the SSP checks fail, which means that the stack has been
   * corrupted.
   */
  void __stack_chk_fail(void)
  {
    abort();
  }

  #include <link.h>
  #include <sys/auxv.h>

  #define AUX_MAX_AT_ID 40
  ElfW(auxv_t) _dl_auxvt[AUX_MAX_AT_ID];
}
#endif

/*!\brief Check if the correct endianess has been configured.
 *
 * If the right endianess is not set this function will end FORTE.
 */
void checkEndianess();

//this keeps away a lot of rtti and exception handling stuff
#ifndef __cpp_exceptions
extern "C" void __cxa_pure_virtual(void){
  //TODO maybe add some reporting here
  //Although we should never get here
  //if we are here something very very bad has happened e.g., stack overflow or other memory corruption

}
#endif

RMT_DEV *poDev = nullptr;

void endForte(int paSig){
  (void) paSig;
  if(nullptr != poDev){
    poDev->changeFBExecutionState(EMGMCommandType::Kill);
  }
}

/*!\brief Creates the Device-Object
 * \param paMGRID A string containing IP and Port like [IP]:[Port]
 */
void createDev(const char *paMGRID){

  signal(SIGINT, endForte);
  signal(SIGTERM, endForte);
  signal(SIGHUP, endForte);

  poDev = new RMT_DEV;
  poDev->initialize();

  poDev->setMGR_ID(paMGRID);
  poDev->startDevice();
  DEVLOG_INFO("FORTE is up and running\n");
  poDev->MGR.joinResourceThread();
  DEVLOG_INFO("FORTE finished\n");
  delete poDev;
}

int main(int argc, char *arg[]){

  checkEndianess();

  startupHook(argc, arg);

#ifdef FORTE_IO_PLCNEXT
  sleep(3);
  DeviceStatus::startup();
#endif

  const char *pIpPort = parseCommandLineArguments(argc, arg);
  if((0 != strlen(pIpPort)) && (nullptr != strchr(pIpPort, ':'))){
    createDev(pIpPort);
  }
  else{ //! Lists the help for FORTE
    listHelp();
  }

  return 0;
}

void checkEndianess(){
  int i = 1;
  char *p = (char *) &i;
  if(p[0] == 1){
    //we are on a little endian platform
#ifdef FORTE_BIG_ENDIAN
    DEVLOG_ERROR("Wrong endianess configured! You are on a little endian platform and have configured big endian!\n");
    exit(-1);
#endif
  }
  else{
    //we are on a big endian platform
#ifdef FORTE_LITTLE_ENDIAN
    DEVLOG_ERROR("Wrong endianess configured! You are on a big endian platform and have configured little endian!\n");
    exit(-1);
#endif
  }
}
