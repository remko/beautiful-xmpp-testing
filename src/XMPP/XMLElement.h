#pragma once

class XMLElement {
	public:
		XMLElement() {
		}

		std::string getTagName() {
			return "";
		}

		bool isValid() {
			return true;
		}

		static XMLElement fromString(const std::string& string) {
			return XMLElement();
		}

		std::string getAttribute(const std::string& attribute) {
			return attributes[attribute];
		}

		XMLElement getElementByTagNameNS(const std::string&, const std::string&) {
			return XMLElement();
		}

		XMLElement getElementByTagName(const std::string&) {
			return XMLElement();
		}

		std::string getText() {
			return "";
		}

		std::map<std::string, std::string> attributes;
};
