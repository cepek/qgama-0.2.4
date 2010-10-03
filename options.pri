# Decide whether to compile with Expath 1.1 XML parsing library
# (for MS Windows we expect there is not present any other Expat library on system)
win32:DEFINES += GNU_gama_expat_1_1
win32:CONFIG += GNU_gama_expat_1_1

# defince
win32:MAKE_COMMAND=mingw32-make.exe
unix:MAKE_COMMAND=make
