#!/usr/bin/env python

import sys, re, os.path

assert(len(sys.argv) == 3)
outputDir = sys.argv[2]

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
filename = sys.argv[1]
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
  outputFile = os.path.join(outputDir, os.path.basename(filename)) + ".xml"
  if programName != "" :
    outputFile = outputFile.replace(".cpp", "." + programName + ".cpp")
  output = open(outputFile, 'w')
  output.write(document)
  output.close()
