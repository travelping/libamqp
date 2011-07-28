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

#include <stdlib.h>

#include "Transport/TransportTestSupport.h"

namespace SuiteTransport
{
    int TransportFixture::in_memory = true;
    
    amqp_endpoint_address_t TransportFixture::endpoint_address = {
        "localhost", AMQP_DEFAULT_PORT
    };

    TransportFixture::TransportFixture() : endpoint()
    {
        endpoint = TransportFixture::initialize_endpoint(context);
        // TODO - exposing event loop details
        amqp_save_event_loop_for_context(context, ev_default_loop(0));
    }

    TransportFixture::~TransportFixture()
    {
    }

    amqp_endpoint_t *TransportFixture::initialize_endpoint(amqp_context_t *context)
    {
        amqp_endpoint_t *result;
        if (in_memory)
        {
            result = amqp__initialize_endpoint_stubb(context, &TransportFixture::endpoint_address);
        }
        else
        {
            result = amqp__initialize_endpoint(context, &TransportFixture::endpoint_address);
        }
        return result;
    }
}
