#!/usr/bin/python
# Copyright 2010 Google Inc.
# Licensed under the Apache License, Version 2.0
# http://www.apache.org/licenses/LICENSE-2.0

# Google's Python Class
# http://code.google.com/edu/languages/google-python-class/

import sys
import re
from pathlib import Path

"""Baby Names exercise

Define the extract_names() function below and change main()
to call it.

For writing regex, it's nice to include a copy of the target
text for inspiration.

Here's what the html looks like in the baby.html files:
...
<h3 align="center">Popularity in 1990</h3>
....
<tr align="right"><td>1</td><td>Michael</td><td>Jessica</td>
<tr align="right"><td>2</td><td>Christopher</td><td>Ashley</td>
<tr align="right"><td>3</td><td>Matthew</td><td>Brittany</td>
...

Suggested milestones for incremental development:
 -Extract the year and print it
 -Extract the names and rank numbers and just print them
 -Get the names data into a dict and print it
 -Build the [year, 'name rank', ... ] list and print it
 -Fix main() to use the extract_names list
"""

def extract_names(filename):
  """
  Given a file name for baby.html, returns a list starting with the year string
  followed by the name-rank strings in alphabetical order.
  ['2006', 'Aaliyah 91', Aaron 57', 'Abagail 895', ' ...]
  """
  f = open(filename)
  text = f.read()
  f.close()
  resultList = []
  year = re.search(r"Popularity\sin\s(\d+)", text)
  if not year :
    sys.stderr.write('Couldn\'t find the year!\n')
    sys.exit(1)
  resultList.append(year.group(1))

  tuples = re.findall(r"tr align\=\"right\"><td>(\d+)</td><td>(\w+)</td><td>(\w+)</td>", text)
  
  nameRankDict = {}
  for nameRank in tuples :
    (rank, maleName, femaleName) = nameRank
    if maleName not in nameRankDict or nameRankDict[maleName] > rank: nameRankDict[maleName] = rank
    if femaleName not in nameRankDict  or nameRankDict[femaleName] > rank: nameRankDict[femaleName] = rank

  sortedList = sorted(nameRankDict.keys())
  
  for element in sortedList: 
    resultList.append(element + " " + nameRankDict[element])

  return resultList


def main():
  # This command-line parsing code is provided.
  # Make a list of command line arguments, omitting the [0] element
  # which is the script itself.
  args = sys.argv[1:]

  if not args:
    print ('usage: [--summaryfile] file [file ...]')
    sys.exit(1)

  # Notice the summary flag and remove it from args if it is present.
  summary = 0
  if args[0] == '--summaryfile': summary = 1
  elif args[0] == '--summaryfiles': summary = 2
  if summary != 0 : del args[0]

  # For each filename, get the names, then either print the text output
  # or write it to a summary file
  for file in args :
    textList = extract_names(file)
    text = "\n".join(textList)

    if summary == 0:
      print (text)
    elif summary == 1:
      f = open(file + ".summary.txt", "w")
      f.write(text)
      f.close()
  
  if summary == 2:
    path = Path('c:/Users/Jinn/Desktop/Python/google-python-exercises/babynames/')
    for file in path.glob('*.html'):
      textList = extract_names(file)
      text = "\n".join(textList)
      f = open(str(file) + ".summary.txt", "w")
      f.write(text)
      f.close()

if __name__ == '__main__':
  main()
