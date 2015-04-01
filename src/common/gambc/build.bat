gsc -cc-options "-D___LIBRARY" -c mylib.scm
gsc -cc-options "-D___LIBRARY" -link -o mylib_.c mylib.c

# remove old .cpp
rm mylib.cpp; rm mylib_.cpp

# rename .c files to .cpp
mv mylib.c mylib.cpp; mv mylib_.c mylib_.cpp

# add #define ___LIBRARY in mylib.c and mylib_.c
