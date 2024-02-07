#!/bin/bash

thisDir=$(pwd)
mainDir=$(realpath $thisDir/..)

# Build library
# TODO You may either directly use the CI build of your library, or replace the `make -j all` by the command needed
# to compile you library. Ensure that there is a DWARF dump for each resulting binary. The analyze.sh script will pick
# those up automatically.
pushd $mainDir
#make -j all
#make
dwarfdump -l libbotan-3.so.2 > microwalk/libbotan-3.so.2.dwarf
popd

# Generate MAP file for library
# TODO Same as above, ensure that there is a MAP file for each binary.
pushd $MAP_GENERATOR_PATH
dotnet MapFileGenerator.dll $mainDir/libbotan-3.so $thisDir/libbotan-3.map
popd

# Build targets
for target in $(find . -maxdepth 1 -name "target-*.c" -print)
do
  targetName=$(basename -- ${target%.*})
  
  # TODO Adjust command line to link against your library
  gcc -O0 -g main.c $targetName.c -fno-inline -fno-split-stack -L "$mainDir" -lbotan-3 -I "$mainDir/build/include" -o $targetName
  
  pushd $MAP_GENERATOR_PATH
  dotnet MapFileGenerator.dll $thisDir/$targetName $thisDir/$targetName.map
  popd
  
  dwarfdump -l $targetName >$targetName.dwarf
done
