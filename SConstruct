import os

env = Environment()
env.Tool("docbook-kit", toolpath = ["docbook-kit/tools/SCons"], docbookkit_dir = "docbook-kit", docbook_dir = "docbook")
Export("env")

env.DocBook("BeautifulXMPPTesting.xml")

SConscript(dirs = "src")

################################################################################
# Code generation helper
################################################################################

import sys, re, os.path

def generateCode(target, source, env) :
	# Strips empty lines from the beginning & end of a program
	def stripEmptyLines(program) :
		programLines = program.split('\n')
		newProgramLines = []
		inProgram = False
		for line in programLines :
			if not re.match("^\s*$", line) or inProgram :
				inProgram = True
				newProgramLines.append(line)
		return '\n'.join(newProgramLines).rstrip()

	def createCallouts(program, calloutPrefix) :
		newProgramLines = []
		calloutLines = []
		nextID = 0
		for line in program.split("\n") :
			# FIXME: Takes the largest match
			m = re.match(".*\/* \(\*\) (.*) \*/.*", line)
			if m :
				cobID = "cob-" + calloutPrefix + "-" + str(nextID)
				coID = "co-" + calloutPrefix + "-" + str(nextID)
				nextID += 1
				line = re.sub("/\*.*\*/", "]]><co id=\"%(cobID)s\" linkends=\"%(coID)s\"/><![CDATA[" % {"cobID" : cobID, "coID" : coID}, line)
				calloutLines.append("<callout arearefs=\"%(cobID)s\" id=\"%(coID)s\"><para>%(text)s</para></callout>" % {"cobID": cobID, "coID": coID, "text": m.group(1)})
			newProgramLines.append(line)
		callouts = "<calloutlist>" + "\n".join(calloutLines) + "</calloutlist>" if len(calloutLines) > 0 else ""
		return ("\n".join(newProgramLines), callouts)
			
	# Parse program
	filename = source[0].abspath
	filenameBase = os.path.basename(filename).replace(".cpp", "")
	inputfile = open(filename)
	program = ""
	programs = {}
	programName = ""
	for line in inputfile.readlines() :
		emptyLine = (line.strip() == "")
		if re.match("^#include", line) :
			continue
		if re.match("^#pragma", line) :
			continue
		if re.match("^using ", line) :
			continue
		m = re.match("^/// (.*)", line)
		if m :
			if programName :
				programs[programName] = program
			program = ""
			programName = m.group(1).strip().replace(" ", "")
			continue
		line = re.sub("\t", "  ", line)
		line = re.sub("_V\d", "", line)
		line = re.sub("shared_ptr<(\w+)>", "\g<1>*", line)
		program += line
	programs[programName] = program
	inputfile.close()

	for programName, program in programs.items() :
		program = stripEmptyLines(program)
		(program, callouts) = createCallouts(program, filenameBase + "-" + programName)

		document = "<foo><programlisting><![CDATA[" + program + "]]></programlisting>" + callouts + "</foo>"

		# Generate code
		outputFile = os.path.join(target[0].dir.abspath, os.path.basename(filename)) + ".xml"
		if programName != "" :
			outputFile = outputFile.replace(".cpp", "." + programName + ".cpp")
		output = open(outputFile, 'w')
		output.write(document)
		output.close()

################################################################################
# Generate sources
################################################################################

generated_sources = [
		("DataChannel.h", "XMPP/DataChannel.h"),
		("ClientTest.TestClient.cpp", "Tests/ClientTest.cpp"),
		("SessionTest.TestFailingConnection.cpp", "Tests/SessionTest.cpp"),
		("SessionTest.TestEncrypt.cpp", "Tests/SessionTest.cpp"),
		("SessionTest.TestEncryptWithoutServerSupport.cpp", "Tests/SessionTest.cpp"),
		("RoomDiscovererTest.FixtureDefinition.cpp", "Tests/RoomDiscovererTest.cpp"),
		("RoomDiscovererTest.Tests.cpp", "Tests/RoomDiscovererTest.cpp"),
		("VersionPayloadSerializerTest.Tests.cpp", "Tests/VersionPayloadSerializerTest.cpp"),
		("VersionResponderTest_V1.Tests.cpp", "Tests/VersionResponderTest_V1.cpp"),
		("VersionResponderTest_V2.Tests.cpp", "Tests/VersionResponderTest_V2.cpp"),
		("VersionResponderTest_V3.Tests.cpp", "Tests/VersionResponderTest_V3.cpp"),
	]

for target, source in generated_sources :
	env.Command(os.path.join("generated", target + ".xml"), 
			os.path.join("src", source), Action(generateCode, cmdstr = "$GENCOMSTR"))
