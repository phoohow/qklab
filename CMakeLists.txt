cmake_minimum_required(VERSION 3.20)

project(QuickLab)

# Add exe project 
function(AddProject proj)
    file(GLOB projAll ./${proj}/*)
    add_executable(${proj} ${projAll})
endfunction(AddProject proj)

AddProject(Ltemplate)
AddProject(TwinTaskKill)