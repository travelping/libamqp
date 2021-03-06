#
# For details on how this Makefile works see the paper "Recursive Make Considered Harmful"
# by Peter Miller (http://aegis.sourceforge.net/auug97.pdf)
#

MODULE = LibAmqp/Transport

# SRC += $(filter-out $(wildcard $(MODULE)/*Stubb.c),$(wildcard $(MODULE)/*.c)) \
#    $(wildcard $(MODULE)/LowLevel/*.c)

SRC += $(wildcard $(MODULE)/*.c) \
    $(wildcard $(MODULE)/LowLevel/*.c) \
    $(wildcard $(MODULE)/Connection/IO/*.c) \
    $(wildcard $(MODULE)/Connection/*.c) \
    $(wildcard $(MODULE)/Decode/*.c) \
    $(wildcard $(MODULE)/Sasl/*.c) \
    $(wildcard $(MODULE)/Frame/*.c) \
    $(wildcard $(MODULE)/Amqp/*.c)

TEST_SRC += $(wildcard  \
    $(MODULE)/*Test.cpp) \
    $(wildcard $(MODULE)/DummyBroker/TestSupport/*.cpp) \
    $(wildcard $(MODULE)/DummyBroker/*.c) \
    $(wildcard $(MODULE)/LowLevel/TestSupport/*.cpp) \
    $(wildcard $(MODULE)/Frame/TestSupport/*.cpp) \
    $(wildcard $(MODULE)/LowLevel/*.cpp) \
    $(wildcard $(MODULE)/Connection/TestSupport/*.cpp) \
    $(wildcard $(MODULE)/Connection/IO/*.cpp) \
    $(wildcard $(MODULE)/Connection/*.cpp) \
    $(wildcard $(MODULE)/Sasl/*.cpp) \
    $(wildcard $(MODULE)/Frame/*.cpp) \
    $(wildcard $(MODULE)/Amqp/*.cpp)
