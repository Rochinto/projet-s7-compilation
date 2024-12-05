#!/bin/bash
./myml $1

if [ $? -ne 0 ]
then
    exit 1
fi

file_name="$(basename -s .ml $1)"

echo "#include \"../src/PCode.h\""      >  ./build/$file_name.c
echo "#include \"../$file_name.fp\""    >> ./build/$file_name.c
echo "int main(){"                      >> ./build/$file_name.c
echo "  #include \"../$file_name.p\""   >> ./build/$file_name.c
echo "  print_stack();"                 >> ./build/$file_name.c
echo "  return 0;"                      >> ./build/$file_name.c
echo "}"                                >> ./build/$file_name.c

gcc ./build/$file_name.c ./build/PCode.o -o ./build/$file_name