

PROGRAM=com-unit-tests



SRCCPP:=com-unit-tests.cpp \
TestTCP.cpp \
TestUDP.cpp

include ../../../../common.mk
include ../../../../unittest-common.mk



LIBS+=  -lcom  -ltestlib -llogmaster  -lexception  -lcmdline -lutilities -lreadline


INCLUDES+=$(GTEST_INCLUDES)

