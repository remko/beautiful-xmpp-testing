#!/usr/bin/env python

# Checks all <programlisting/> elements for XML, and validates
# all detected XML snippets.

import sys, xml.dom.minidom, re

# Retrieve the text portion from an XML node
def getText(nodelist):
	rc = ""
	for node in nodelist:
		if node.nodeType in [node.TEXT_NODE, node.CDATA_SECTION_NODE]:
			rc += node.data
	return rc


if len(sys.argv) < 2 :
		print "Please specify the docbook files you want to test"

hasError = False
for fileName in filter(lambda x: x.endswith(".xml"), sys.argv[1:]) :
	file = open(fileName)
	document = xml.dom.minidom.parseString(file.read())
	file.close()

	listings = document.getElementsByTagName("programlisting")
	for listing in listings :
		text = getText(listing.childNodes).encode("utf-8")
		text = text.strip()
		if not text.startswith("<") :
			continue
		try :
			streamDocument = "<stream>" + text + "</stream>"
			xml.dom.minidom.parseString(streamDocument)
		except xml.parsers.expat.ExpatError, error:
			hasError = True
			print "ERROR: " + fileName + ": " + str(error)
			print text + "\n"

if hasError:
	sys.exit(-1)
