/*
   Copyright 2011-2012 StormMQ Limited

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

#ifndef LIBAMQP_TEST_DATA_TEST_FRAMES_H
#define LIBAMQP_TEST_DATA_TEST_FRAMES_H

#include "TestData/TestData.h"

namespace test_data
{
    extern TestData sasl_protocol_1_0_0;
    extern TestData sasl_protocol_1_1_0;
    extern TestData tls_protocol_1_0_0;
    extern TestData tls_protocol_1_1_0;
    extern TestData amqp_protocol_1_0_0;
    extern TestData amqp_protocol_1_1_0;

    extern TestData minimal_frame_header;
    extern TestData sasl_mechanisms_frame_with_invalid_descriptor_id;
    extern TestData sasl_mechanisms_frame;
    extern TestData sasl_mechanisms_frame_long;
    extern TestData sasl_mechanisms_frame_symbol;

    extern TestData sasl_init_frame;
    extern TestData sasl_init_frame_captured;

    extern TestData sasl_outcome_frame;
    extern TestData sasl_outcome_frame_auth_error;

    extern TestData client_open_frame;
    extern TestData client_open_frame_with_trailing_garbage;
    extern TestData broker_open_frame;
    extern TestData client_begin_frame;
    extern TestData broker_begin_frame;

    extern TestData client_attach_frame;
    extern TestData broker_attach_frame;
    extern TestData flow_frame;
    extern TestData broker_flow_frame;
    extern TestData ya_flow_frame;
    extern TestData transfer_frame_id_0;
    extern TestData transfer_frame_id_256;
    extern TestData transfer_frame_id_677;
    extern TestData close_frame;
    extern TestData close_confirm_frame;

}
#endif

