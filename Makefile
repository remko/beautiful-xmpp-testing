DOCUMENT = BeautifulXMPPTesting.xml

include docbook-kit/tools/Makefile.inc

################################################################################
# Custom rules
################################################################################

.PHONY: check
check: check-document check-spelling
	scripts/CheckStanzas.py $(DOCUMENT) $(DOCUMENT_DEPENDENCIES)
	$(MAKE) -C src

generated:
	mkdir -p generated

generated/VersionResponderTest_V1.%.cpp.xml: generated src/Tests/VersionResponderTest_V1.cpp
	scripts/GenerateCode.py src/Tests/VersionResponderTest_V1.cpp generated

generated/VersionResponderTest_V2.%.cpp.xml: generated src/Tests/VersionResponderTest_V2.cpp
	scripts/GenerateCode.py src/Tests/VersionResponderTest_V2.cpp generated

generated/VersionResponderTest_V3.%.cpp.xml: generated src/Tests/VersionResponderTest_V3.cpp
	scripts/GenerateCode.py src/Tests/VersionResponderTest_V3.cpp generated

generated/VersionPayloadSerializerTest.%.cpp.xml: generated src/Tests/VersionPayloadSerializerTest.cpp
	scripts/GenerateCode.py src/Tests/VersionPayloadSerializerTest.cpp generated

generated/RoomDiscovererTest.%.cpp.xml: generated src/Tests/RoomDiscovererTest.cpp
	scripts/GenerateCode.py src/Tests/RoomDiscovererTest.cpp generated

generated/SessionTest.%.cpp.xml: generated src/Tests/SessionTest.cpp
	scripts/GenerateCode.py src/Tests/SessionTest.cpp generated

generated/ClientTest.%.cpp.xml: generated src/Tests/ClientTest.cpp
	scripts/GenerateCode.py src/Tests/ClientTest.cpp generated

generated/DataChannel.h.xml: generated src/XMPP/DataChannel.h
	scripts/GenerateCode.py src/XMPP/DataChannel.h generated

BeautifulXMPPTesting.book.xml: BeautifulXMPPTesting.flat.xml
	scripts/ConvertArticleToBook.py $< $@

CLEANFILES += generated/* fop.cfg BeautifulXMPPTesting.book.xml
