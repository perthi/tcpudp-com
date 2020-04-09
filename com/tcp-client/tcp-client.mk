

PROGRAM:=tcp-client 

SRCCPP+=tcp-client.cpp 


LIBS+=  -lcom -llogmaster  -lutilities  -lexception -lreadline    -lpthread  

#CPPFLAGS=$(CPPFLAGS_RELAXED)


include ../../../common.mk

