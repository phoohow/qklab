import os
import sys
import shutil
import logging

rootDir = os.getcwd()
logging.basicConfig(
    level=logging.INFO,
    format="[%(levelname)s]   file: %(filename)s   line: %(lineno)d\t%(message)s",
)


# Print help args
def printHelp():
    print(
        "Usage:\n"
        + "\t--help(-h)                                      :    list args\n"
        + "\t<prject name>                                   :    create new project\n"
        + "\t--add(-a)    <prject name>                      :    create new project\n"
        + "\t--delete(-d) <prject name>                      :    remove existed project\n"
        + "\t--rename(-r) <old prject name> <new prject name>:    rename existed project\n"
    )
    exit()


# Create project
def createProject(proj, cmakeFile, fileHead, fileCpp, mainCpp):
    # Process exception

    # Create folder if not exist
    if not os.path.exists(proj):
        os.mkdir("src/" + proj)

    # Create .h file
    if not os.path.exists(fileHead):
        f = open(fileHead, "w")
        f.write("#pragma once\n")
        f.close()
    else:
        logging.warning(fileHead + " exist!")

    includeHead = '#include "' + proj + '.h"\n'

    # # Create .cpp file
    # if not os.path.exists(fileCpp):
    #     f = open(fileCpp, 'w')
    #     f.write(includeHead)
    #     f.close()
    # else:
    #     logging.warning(fileCpp + " exist!")

    # Create main.cpp file
    mainContext = (
        includeHead
        + "#include <iostream>\n"
        + "#include <string>\n\n"
        + "int main()\n"
        + "{\n"
        + "\treturn 0;\n"
        + "}\n"
    )
    if not os.path.exists(mainCpp):
        f = open(mainCpp, "w")
        f.write(mainContext)
        f.close()
    else:
        logging.warning("main.cpp exist!")

    # Create cmake config
    addProj = "addProject(" + proj + ")"
    isFound = False
    with open(cmakeFile) as ff:
        if addProj in ff.read():
            isFound = True

    if not isFound:
        f = open(cmakeFile, "a+")
        f.write(addProj + "\n")


# Remove project
def removeProject(proj, cmakeFile):
    # Process exception

    # Remove project directory
    if os.path.exists(rootDir + "\\src\\" + proj):
        shutil.rmtree(rootDir + "\\src\\" + proj)
    else:
        logging.warning("Project " + proj + " not exist\n")
        pass

    # Remove project cmake config
    addProj = "addProject(" + proj + ")"
    f = open(cmakeFile, "r")
    fileContext = ""
    for token in f:
        if addProj in token:
            continue
        else:
            fileContext += token
    f.close()
    ff = open(cmakeFile, "w")
    ff.write(fileContext)
    ff.close()


def renameProject(oldProj, newProj, cmakeFile):
    # TODO
    # Process exception(last arg)

    # Check old project exist or not
    if not os.path.exists(rootDir + "\\src\\" + oldProj):
        logging.error("Project " + oldProj + " not exist. Check your input\n")
        exit()

    # Rename project name
    os.rename(rootDir + "\\src\\" + oldProj, rootDir + "\\src\\" + newProj)

    # Rename default .h file
    if os.path.exists(rootDir + "\\src\\" + newProj + "\\" + oldProj + ".h"):
        os.rename(
            rootDir + "\\src\\" + newProj + "\\" + oldProj + ".h",
            rootDir + "\\src\\" + newProj + "\\" + newProj + ".h",
        )
    else:
        f = open(rootDir + "\\src\\" + newProj + "\\" + newProj + ".h", "w")
        f.write("#pragma once\n")
        f.close()

    oldIncludeHead = '#include "' + oldProj + '.h"\n'
    newIncludeHead = '#include "' + newProj + '.h"\n'
    # Replace default head file in .cpp file
    for filePath, dirName, fileNames in os.walk(rootDir + "\\src\\" + newProj):
        for fileName in fileNames:
            if ".cpp" in fileName:
                f = open(filePath + "\\" + fileName, "r")
                fileContext = ""
                for token in f:
                    if oldIncludeHead in token:
                        fileContext += newIncludeHead
                    else:
                        fileContext += token
                f.close()
                ff = open(filePath + "\\" + fileName, "w")
                ff.write(fileContext)
                ff.close()

    # Replace cmake config name
    oldAddProj = "addProject(" + oldProj + ")"
    newAddProj = "addProject(" + newProj + ")"
    f = open(cmakeFile, "r")
    fileContext = ""
    for token in f:
        if oldAddProj in token:
            fileContext += newAddProj
        else:
            fileContext += token
    f.close()
    ff = open(cmakeFile, "w")
    ff.write(fileContext)
    ff.close()


if len(sys.argv) == 2:
    # Process help
    if sys.argv[1] == "--help" or sys.argv[1] == "-h":
        printHelp()

    # Create project
    proj = sys.argv[1]
    cmakeFile = rootDir + "\\CMakeLists.txt"
    fileHead = rootDir + "\\src\\" + proj + "\\" + proj + ".h"
    fileCpp = rootDir + "\\src\\" + proj + "\\" + proj + ".cpp"
    mainCpp = rootDir + "\\src\\" + proj + "\\main.cpp"
    createProject(proj, cmakeFile, fileHead, fileCpp, mainCpp)
elif len(sys.argv) == 3:
    proj = sys.argv[2]
    cmakeFile = rootDir + "\\CMakeLists.txt"
    fileHead = rootDir + "\\src\\" + proj + "\\" + proj + ".h"
    fileCpp = rootDir + "\\src\\" + proj + "\\" + proj + ".cpp"
    mainCpp = rootDir + "\\src\\" + proj + "\\main.cpp"

    # Create project
    if sys.argv[1] == "--add" or sys.argv[1] == "-a":
        createProject(proj, cmakeFile, fileHead, fileCpp, mainCpp)

    # Remove project
    elif sys.argv[1] == "--delete" or sys.argv[1] == "-d":
        removeProject(proj, cmakeFile)

    else:
        logging.error("Illegal operate!\n")
        printHelp()

elif len(sys.argv) == 4:
    oldProj = sys.argv[2]
    newProj = sys.argv[3]
    cmakeFile = rootDir + "\\CMakeLists.txt"
    if sys.argv[1] == "--rename" or sys.argv[1] == "-r":
        renameProject(oldProj, newProj, cmakeFile)
    else:
        logging.error("Illegal operate!\n")
        printHelp()

else:
    logging.error("Illegal operate!\n")
    printHelp()
