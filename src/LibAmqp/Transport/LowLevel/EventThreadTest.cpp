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

#include <TestHarness.h>
#include "Transport/LowLevel/EventThreadTestSupport.h"
#include "debug_helper.h"

#include "Transport/LowLevel/EventThread.h"

static void event_thread_handler(amqp_event_thread_t *event_thread)
{
    amqp_event_thread_run_loop(event_thread);
}

SUITE(Transport)
{
    TEST(event_thread_no_fixture)
    {
        amqp_context_t *context = amqp_create_context();

        struct ev_loop *loop = ev_default_loop(0);
        amqp_event_thread_t *event_thread = amqp_event_thread_initialize(context, event_thread_handler, loop, 0);

        int thread_allocations_ok = amqp_event_thread_destroy(context, event_thread);
        CHECK(thread_allocations_ok);

        int outer_allocations_ok = amqp_context_destroy(context);
        CHECK(outer_allocations_ok);
    }

    TEST_FIXTURE(EventThreadFixture, event_thread_providing_loop)
    {
        struct ev_loop *loop = ev_default_loop(0);
        m_event_thread = amqp_event_thread_initialize(context, EventThreadFixture::basic_event_thread_handler, loop, 0);
    }

    TEST_FIXTURE(EventThreadFixture, event_thread_without_loop)
    {
        m_event_thread = amqp_event_thread_initialize(context, EventThreadFixture::basic_event_thread_handler, 0, 0);
    }
}