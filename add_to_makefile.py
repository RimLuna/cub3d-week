#!/usr/bin/env python3
import subprocess
import os
import time
import shutil
import re

src = "./"
target = "../"
listfirst = os.listdir(src)
makefile = "Makefile"

while True:
	time.sleep(1)
	listnow = os.listdir(src)
	newf = [f for f in listnow if all([not f in listfirst, f.endswith(".c")])]
	for f in newf:
		lines = []
		with open(makefile, "r+") as mfile:
			for line in mfile:
				if line.startswith("SRCS =\t\t"):
					split_line = line.split()
					new = "\t\t" + f + " " + "\\\n" + "\t\t"
					split_line.insert(2, new)
					line = ''.join(split_line)
					print(line)
					lines.append(line)
				else:
					lines.append(line)
			mfile.close()
		with open(makefile, "w") as mfile:
			for l in lines:
				mfile.write(l)
			mfile.close()
	listfirst = listnow
