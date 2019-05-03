COMPONENT=SenseAppC

TOSMAKE_PRE_EXE_DEPS += SenseMsg.class 
TOSMAKE_CLEAN_EXTRA = *.class SenseMsg.java

CFLAGS += -I$(TINYOS_OS_DIR)/lib/printf
PFLAGS += -DNEW_PRINTF_SEMANTICS
CFLAGS += -DPRINTF_BUFFER_SIZE=1024

SenseMsg.class: $(wildcard *.java) SenseMsg.java 
	javac -target 1.8 -source 1.8 *.java 
 
SenseMsg.java: 
	nescc-mig java $(CFLAGS) -java-classname=SenseMsg Sense.h SenseMsg -o $@ 

TINYOS_ROOT_DIR?=/home/jyxk/tinyos-main
include $(TINYOS_ROOT_DIR)/Makefile.include
