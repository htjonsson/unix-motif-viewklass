#
#
#	makefile for the ViewKlass test harness
#
#	$Id: Makefile,v 1.9 2006/12/23 05:07:55 jostle Exp $	
#

INCDIRS = -I.. -I/usr/X11R6/include

LIBDIRS = -L.. -L/usr/X11R6/lib

LIBS    = -lvk -lvkhelp -lvk -lXpm -lXp -lXmu -lXm -lXt -lX11 -lstdc++

CC		= gcc -O0 -g

EFENCE	= ##-lefence

OBJS	=	vktest.o Slider.o testVkWidgetList.o testVkNameList.o \
			testVkComponentList.o TestPrefDialog.o TestPeriodic.o \
			TestInput.o TestAlignment.o TestCompletion.o TestWindow.o

LIB_DEPS	= ../libvk.a ../libvkhelp.a

SRCS = $(OBJS:.o=.cc)

HDRS = 	Slider.h TestPrefDialog.h TestPeriodic.h \
		TestInput.h TestAlignment.h TestCompletion.h TestWindow.h

all : vktest staticMenuTest resourceTest

vktest : ${OBJS} ${LIB_DEPS}
	${CC} $(OBJS) -Wall -o vktest $(LIBDIRS) $(LIBS) $(EFENCE)

Slider.o : Slider.cc Slider.h
	${CC} Slider.cc -c -Wall -o Slider.o $(INCDIRS)

vktest.o : vktest.cc
	${CC} vktest.cc -c -Wall -o vktest.o $(INCDIRS)

testVkWidgetList.o : testVkWidgetList.cc
	${CC} testVkWidgetList.cc -c -Wall -o testVkWidgetList.o $(INCDIRS)

testVkNameList.o : testVkNameList.cc
	${CC} testVkNameList.cc -c -Wall -o testVkNameList.o $(INCDIRS)

testVkComponentList.o : testVkComponentList.cc
	${CC} testVkComponentList.cc -c -Wall -o testVkComponentList.o \
	$(INCDIRS)

TestPrefDialog.o : TestPrefDialog.cc TestPrefDialog.h
	${CC} TestPrefDialog.cc -c -Wall -o TestPrefDialog.o \
	$(INCDIRS)

TestPeriodic.o : TestPeriodic.cc TestPeriodic.h
	${CC} TestPeriodic.cc -c -Wall -o TestPeriodic.o \
	$(INCDIRS)

TestInput.o : TestInput.cc TestInput.h
	${CC} TestInput.cc -c -Wall -o TestInput.o \
	$(INCDIRS)

TestAlignment.o : TestAlignment.cc TestAlignment.h
	${CC} TestAlignment.cc -c -Wall -o TestAlignment.o \
	$(INCDIRS)

TestCompletion.o : TestCompletion.cc TestCompletion.h
	${CC} TestCompletion.cc -c -Wall -o TestCompletion.o \
	$(INCDIRS)

TestWindow.o : TestWindow.cc TestWindow.h
	${CC} TestWindow.cc -c -Wall -o TestWindow.o \
	$(INCDIRS)

staticMenuTest : staticMenuTest.o ${LIB_DEPS}
	${CC} staticMenuTest.o -Wall -o staticMenuTest $(LIBDIRS) $(LIBS)

staticMenuTest.o : staticMenuTest.cc
	${CC} staticMenuTest.cc -c -Wall -o staticMenuTest.o $(INCDIRS)

resourceTest : resourceTest.o ${LIB_DEPS}
	${CC} resourceTest.o -Wall -o resourceTest $(LIBDIRS) $(LIBS)

resourceTest.o : resourceTest.cc
	${CC} resourceTest.cc -c -Wall -o resourceTest.o $(INCDIRS)

clean :
	-rm -f vktest staticMenuTest resourceTest *.o core *~

