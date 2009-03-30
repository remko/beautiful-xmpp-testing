CPPFLAGS += -I. -Wall -DBOOST_SIGNALS_NAMESPACE=bsignals
ARFLAGS = rcs

################################################################################
# Default target
################################################################################

TARGET = AllTests

all: $(TARGET) ClientTest

################################################################################

include CppUnit/Makefile.inc

################################################################################

ClientTest: Tests/ClientTest.o
	$(CXX) -o $@ $< Swift.a -lexpat -lssl -lcrypto -lpthread -lresolv

################################################################################

SOURCES = \
	Tests/VersionResponderTest_V1.cpp \
	Tests/VersionResponderTest_V2.cpp \
	Tests/VersionResponderTest_V3.cpp \
	Tests/RoomDiscovererTest.cpp \
	Tests/SessionTest.cpp \
	AllTests.cpp
OBJECTS = $(patsubst %.c, %.o, $(patsubst %.cpp, %.o, $(SOURCES)))

$(TARGET): $(CPPUNIT_TARGET) $(CLIENTTEST_TARGET) $(OBJECTS) 
	$(CXX) -o $(TARGET) $(OBJECTS) $(CPPUNIT_TARGET) Swift.a

clean:
	-rm -rf $(CLEANFILES) $(OBJECTS) $(DEPS) AllTests ClientTest

check: $(TARGET)
	./$(TARGET)

################################################################################

DEPS = \
	$(patsubst %.c, %.dep, $(patsubst %.cpp, %.dep, $(SOURCES)))

ifeq (,$(findstring clean, $(MAKECMDGOALS)))
-include $(DEPS)
endif

%.dep: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MM -MG -MT $(basename $@).o $< > $@

%.dep: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -MM -MG -MT $(basename $@).o  $< > $@
