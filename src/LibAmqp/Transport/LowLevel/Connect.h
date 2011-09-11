/*
   Copyright 2011 StormMQ Limited

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 */

#ifndef LIBAMQP_TRANSPORT_LOW_LEVEL_CONNECT_H
#define LIBAMQP_TRANSPORT_LOW_LEVEL_CONNECT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "libamqp_common.h"
#include "Transport/LowLevel/Socket.h"

extern int amqp_lookup_host_address(const char *host_name, int port, struct addrinfo **result);
extern int amqp_blocking_tcp_connect_to(const char *host_name, int port);

#ifdef __cplusplus
}
#endif
#endif