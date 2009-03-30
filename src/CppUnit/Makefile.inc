CXXFLAGS += -isystem CppUnit

CPPUNIT_TARGET = CppUnit/CppUnit.a

CPPUNIT_SOURCES = \
  CppUnit/src/TextTestRunner.cpp \
  CppUnit/src/TextTestProgressListener.cpp \
  CppUnit/src/TextOutputter.cpp \
  CppUnit/src/StringTools.cpp \
  CppUnit/src/DefaultProtector.cpp \
  CppUnit/src/Protector.cpp \
  CppUnit/src/ProtectorChain.cpp \
  CppUnit/src/SynchronizedObject.cpp \
  CppUnit/src/SourceLine.cpp \
  CppUnit/src/TestRunner.cpp \
  CppUnit/src/TestFactoryRegistry.cpp \
  CppUnit/src/TestSuite.cpp \
  CppUnit/src/TestSuiteBuilderContext.cpp \
  CppUnit/src/TestResult.cpp \
  CppUnit/src/TestResultCollector.cpp \
  CppUnit/src/TestSuccessListener.cpp \
  CppUnit/src/TestComposite.cpp \
  CppUnit/src/TestCase.cpp \
  CppUnit/src/TestFailure.cpp \
  CppUnit/src/TestLeaf.cpp \
  CppUnit/src/TestNamer.cpp \
  CppUnit/src/Asserter.cpp \
  CppUnit/src/TypeInfoHelper.cpp \
  CppUnit/src/Exception.cpp \
  CppUnit/src/Message.cpp \
  CppUnit/src/AdditionalMessage.cpp \
  CppUnit/src/Test.cpp \
  CppUnit/src/TestPath.cpp

CPPUNIT_OBJECTS = \
	$(CPPUNIT_SOURCES:.cpp=.o)

CLEANFILES += \
	$(CPPUNIT_OBJECTS) \
	$(CPPUNIT_TARGET)

$(CPPUNIT_TARGET): $(CPPUNIT_OBJECTS)
	$(AR) $(ARFLAGS) $@ $(CPPUNIT_OBJECTS)
