# Group Randomizer




### Description

This sketch allows us to randomly create groups + assign them to something. It expects 2 text files in the data folder: 
- students.txt: newline separated list of students preceded with a group size (the first line)
- assign.txt: newline separated list of what to assign
- spacebrew.txt: (optional) location of spacebrew server (e.g. localhost or sandbox.spacebrew.cc) 

It accepts a boolean switch to start and stop randomization and sends out groups when finished separated by a ";" (see receipt printer sketch)

### Spacebrew info

- **Name**: Randomizer
- **Server**: sandbox.spacebrew.cc
- **Subscriptions**: 
  - randomize
- **Publishers**
  - selectedGroup


### Required Libraries

Put into ~/Documents/Processing/libraries

- Spacebrew: [spacebrew-processing-library](https://github.com/labatrockwell/spacebrew-processing-library.git)