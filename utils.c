#include "tcp_bok.h"

// manage exchange key functions
int manage_exchange_key(int isServer, int command, int key_flag)
{
  // Exchange Key Flags for Client(0) and Server(1)
  static int g_ExchangeKey[2] = {0, 0};

  // session flag for client(0) and server(1)
  if (isServer != 0) {
    isServer = 1;
  }

  // command flag for get(0) and set(1)
  if (command != 0) {
    command = 1;
  }

  // flag value for OFF(0) and ON(1)
  if (key_flag != 0) {
    key_flag = 1;
  }

  if (command == 0) {
    return g_ExchangeKey[isServer];
  }

  g_ExchangeKey[isServer] = key_flag;
  return key_flag;
}

// getter functions
int get_client_status() {
  return manage_exchange_key(0, 0, 0);
}
int get_server_status() {
  return manage_exchange_key(1, 0, 0);
}

// setter functions
int set_client_status(int val) {
  return manage_exchange_key(0, 0, val);
}
int set_server_status(int val) {
  return manage_exchange_key(1, 0, val);
}