#include "tcp_iso.h"

int check_msg_tp_cd(char* msg_tp_cd)
{
  static char* msg_tp_cd_list[] = {
    "admi.002", "admi.004.ConnectionCheck", "admi.004.SystemNotification",
    "admi.006", "admi.007", "admi.011",
    "camt.005", "camt.006", "camt.007",
    "camt.025", "camt.029",
    "camt.052", "camt.053", "camt.054", "camt.056",
    "camt.060", "camt.110", "camt.111",
    "pacs.002.CLS", "pacs.002.CORE",
    "pacs.004.CLS", "pacs.004.CORE",
    "pacs.008.CORE",
    "pacs.009.CLS", "pacs.009.CORE",
    "pacs.028",
  };

  for(int i = 0; i < sizeof(msg_tp_cd_list)/sizeof(msg_tp_cd_list[0]); i++) {
    if( strcmp(msg_tp_cd, msg_tp_cd_list[i]) == 0 ) {
      return 1;
    }
  }

    return 0;
}

