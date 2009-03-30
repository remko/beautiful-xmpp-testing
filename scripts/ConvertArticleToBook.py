#!/usr/bin/env python
# coding=utf-8

# Convert the XMPP book article to a chapter for the BT book. 

import re, sys

assert(len(sys.argv) == 3)

input = open(sys.argv[1])
output = open(sys.argv[2], "w")
inArticleInfo = False
for line in input.readlines() :
	if inArticleInfo :
		if re.match(".*</articleinfo>.*", line) :
			inArticleInfo = False
	elif re.match(".*<articleinfo>.*", line) :
		inArticleInfo = True
	else :
		line = re.sub("<!DOCTYPE article", "<!DOCTYPE book", line)
		line = re.sub("<article>", 
"""<book>
<title>Beautiful Testing</title>
<chapter>
  <title>XMPP Testing</title>
""", line)
		line = re.sub("</article>", "</chapter>\n</book>", line)
		output.write(line)
input.close()
output.close()
