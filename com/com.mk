

LIBNAME_SO=libcom.so
#LIBNAME_A=libcom.a


SRCCPP:=GCom.cpp \
	GServerTCP.cpp \
	GClientTCP.cpp \
	GServerUDP.cpp \
	GClientUDP.cpp \
	GComErrorHandler.cpp \
	GServerUDPRelay.cpp \
	GServerTCPPublisher.cpp



include ../../common.mk



#CPPFLAGS=$(CPPFLAGS_RELAXED)
#CPPFLAGS_TMP:=$(CPPFLAGS)
#CPPFLAGS= $(filter-out -Weffc++, $(CPPFLAGS_TMP) )
