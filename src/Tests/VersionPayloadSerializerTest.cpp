/// Tests

void VersionPayloadSerializerTest::testSerialize() {
	// Set up the test fixture
	VersionPayloadSerializer serializer;
	VersionPayload payload;
	payload.setVersion("Swift", "1.0");

	// Serialize a payload
	XMLElement result = serializer.serialize(payload);

	// Verify the serialized element
	ASSERT_EQUAL("query", result.getTagName());
	ASSERT_EQUAL("jabber:iq:version", result.getNamespace());
	XMLElement* nameElement = queryElement->getElementsByTagName("name");
	ASSERT(nameElement);
	ASSERT_EQUAL("Swift", nameElement->getText());
	XMLElement* versionElement = queryElement->getElementsByTagName("version");
	ASSERT(versionElement);
	ASSERT_EQUAL("1.0", versionElement->getText());
}
