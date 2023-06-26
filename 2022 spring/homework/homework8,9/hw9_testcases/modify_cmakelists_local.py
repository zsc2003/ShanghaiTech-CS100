import os
import sys

CMAKELIST = "./CMakeLists.txt"

part_ignored = False

with open(CMAKELIST, 'r') as infile:
    lines = infile.readlines()

with open(CMAKELIST, 'w', newline = '') as outfile:
    for line in lines:
        if(line.find('add_subdirectory') != -1 or line.find('ADD_SUBDIRECTORY') != -1):
            part_ignored = True

        if(part_ignored):
            if(line.find(')') != -1):
                part_ignored = False
            continue

        if(line.find('FREEGLUT') != -1):
            continue

        if(line.find('src/ProvidedFramework/SpriteManager') != -1):
            continue

        if(line.find('freeglut') != -1 or line.find('SOIL') != -1):
            continue

        outfile.write(line)


    