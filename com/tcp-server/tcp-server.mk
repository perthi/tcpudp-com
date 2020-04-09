

PROGRAM:=tcp-server 

SRCCPP+=tcp-server.cpp 


LIBS+=  -lcom -llogmaster   -lutilities  -lexception -lreadline  -lpthread  

#CPPFLAGS=$(CPPFLAGS_RELAXED)


include ../../../common.mk

