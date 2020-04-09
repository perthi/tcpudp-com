

PROGRAM:=tcp-example1 

SRCCPP+=tcp-example1.cpp 


LIBS+=   -lcom  -llogmaster -lutilities  -lexception  -lpthread   -lreadline  

#CPPFLAGS=$(CPPFLAGS_RELAXED)


include ../../../../common.mk

