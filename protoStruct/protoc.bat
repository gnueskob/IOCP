set DST_DIR=%cd%/Compile
set SRC_DIR=%cd%
protoc -I=%SRC_DIR% --cpp_out=%DST_DIR% %SRC_DIR%/Echo.proto