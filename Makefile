CC=g++
CFLAGS=-c -I .
OSTARGET=linux
OUTDIR=./intermediate/$(OSTARGET)/

all: make_directories others Angle.o Cast.o


unify:

Angle.o: ./unify/Angle.cpp ./unify/Angle.h
	$(CC) $(CFLAGS) unify/Angle.cpp -o $(OUTDIR)Angle.o

Cast.o: ./unify/Cast.cpp ./unify/Cast.h ./unify/Cast.inl
	$(CC) $(CFLAGS) unify/Cast.cpp -o $(OUTDIR)Cast.o


make_directories:
	mkdir -p $(OUTDIR)

# All other headers and inline files that have no cpp files, but want to be tested for changes.
others: unify/Any.h unify/BadCast.h unify/BBox.h unify/BBox.inl unify/BSphere.h unify/BSphere.inl \
	unify/BSquare.h unify/BSquare.inl
