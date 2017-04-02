#!/bin/sh
##################################################
# author : sven
# date   : 2013-09-30
##################################################

#TARGET_VERSION = GDB

# Hisilicon Hi3516 sample Makefile

# include ../Makefile.param


export CC		:=	$(CROSS)gcc
export CPP		:=	$(CROSS)g++
export AR		:=	$(CROSS)ar
export ARFLAGS  := 	rcs


ifeq ($(TARGET_VERSION),GDB)
	export	CPPFLAGS_V	=	$(FIT_MCU) -Wall -g
	LINKFLAGS_V	=	-lstdc++ -lpthread -lm
else
	export	CPPFLAGS_V	=	$(FIT_MCU) -Wall -O2
	LINKFLAGS_V	=	-lstdc++ -lpthread -lm -s
endif

#extern libs
ELIBS_PATH			:=	$(PWD)/libs
#ELIBS				:=	$(wildcard $(ELIBS_PATH)/*.a)

#final target
export TARGET = rtspSrv
ALL: $(TARGET)

export PUBLIC_PATH      := $(PWD)

#common
export COMMON_PATH	:=	$(PWD)/common
COMMON_SRCS			:=	$(wildcard $(COMMON_PATH)/*.cpp)
COMMON_INCS			:=	$(wildcard $(COMMON_PATH)/*.h)
COMMON				:=	$(COMMON_PATH)/$(notdir $(COMMON_PATH))$(TARGET).a
$(COMMON): $(COMMON_SRCS) $(COMMON_INCS)
	$(MAKE) -C $(COMMON_PATH) SUB_PATH=$(COMMON_PATH)


#main
MAIN_SRCS			:=	$(wildcard *.cpp)
MAIN_OBJS			:=	$(MAIN_SRCS:%.cpp=%.o)
MAIN_SRCSC			:=	$(wildcard *.c)
MAIN_OBJSC			:=	$(MAIN_SRCSC:%.c=%.o)

#procon
export PROCON_PATH	:=	$(PWD)/procon
PROCON_SRCS			:=	$(wildcard $(PROCON_PATH)/*.cpp)
PROCON_INCS			:=	$(wildcard $(PROCON_PATH)/*.h)
PROCON				:=	$(PROCON_PATH)/$(notdir $(PROCON_PATH)).a
$(PROCON): $(PROCON_SRCS) $(PROCON_INCS)
	$(MAKE) -C $(PROCON_PATH) SUB_PATH=$(PROCON_PATH)


#rtsp
export RTSP_PATH	:=	$(PWD)/rtspLib
RTSP_SRCS			:=	$(wildcard $(RTSP_PATH)/*.cpp)
RTSP_SRCSC			:=	$(wildcard $(RTSP_PATH)/*.c)
RTSP_INCS			:=	$(wildcard $(RTSP_PATH)/*.h)
RTSP				:=	$(RTSP_PATH)/$(notdir $(RTSP_PATH)).a
$(RTSP): $(RTSP_SRCS) $(RTSP_SRCSC) $(RTSP_INCS)
	$(MAKE) -C $(RTSP_PATH) SUB_PATH=$(RTSP_PATH)

##filling
#for make cleanall and dep
PATH_MOUDELS	+=   $(PUBLIC_PATH) $(COMMON_PATH) $(PROCON_PATH) $(RTSP_PATH)

#for src dep this makefile
DEP_MOUDELS		+=	$(MAIN_SRCS) $(MAIN_OBJSC) $(COMMON_SRCS) $(PUBLIC_SRCS) $(TEST_SRCS) $(PROCON_SRCS) \
                                $(RTSP_SRCS) $(RTSP_SRCSC)

#for this makefile include
INC_PATH		:=     -I$(PUBLIC_PATH) -I$(COMMON_PATH) -I$(PROCON_PATH)  -I$(RTSP_PATH)

FIRS_LIBS =  $(RTSP) $(PROCON) $(COMMON) $(ELIBS)

## this dir
CPPFLAGS		:=	$(CPPFLAGS_V)
CPPFLAGS		+=	$(INC_PATH)
LINKFLAGS		:=	$(LINKFLAGS_V)

$(TARGET): $(MAIN_OBJSC) $(FIRS_LIBS) $(EX_LIBS)
	$(CC) -o $(TARGET) $^ $(LINKFLAGS)
#	cp $(TARGET) /yfnfs

%.o: %.cpp
	$(CPP) -c $(CPPFLAGS) -o $@ $<
%.o: %.c
	$(CPP) -c $(CPPFLAGS) -o $@ $<

.PHONY: clean cleanall dep

clean:
	rm -fr $(MAIN_OBJSC) $(TARGET) *.dep

cleanall: clean
	@for loop in $(PATH_MOUDELS);\
	do \
		$(MAKE) -C $$loop clean SUB_PATH=$$loop; \
	done

dep:
	@for loop in $(PATH_MOUDELS);\
	do \
		$(MAKE) -C $$loop dep; \
	done

	(for i in $(DEP_MOUDELS);do  dirname $$i|xargs echo -n;echo -n "/";$(CPP) -MM $(INC_PATH) $$i;done) > Makefile.dep

### Dependencies:
ifeq (Makefile.dep, $(wildcard Makefile.dep))
include Makefile.dep
endif
