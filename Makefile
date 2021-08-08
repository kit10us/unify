#CC=g++
#CFLAGS=-std=c++17 -c -I .
CC=clang
CFLAGS=-c -I .
OSTARGET=linux
INTDIR=./intermediate/$(OSTARGET)/
OUTDIR=./lib/$(OSTARGET)/

all: unify

unify: make_directories others Angle.o Cast.o Color.o ColorUnit.o DataLock.o Frame.o \
	FrameLite.o FrameSet.o FrameSetInstance.o Frustum.o FStream.o Matrix.o NinePoint.o \
	Owner.o Parameters.o Path.o Plane.o Quaternion.o Ray.o Stream.o String.o TexArea.o \
	TexCoords.o TimeDelta.o Variant.o createlib

Angle.o: ./unify/Angle.cpp ./unify/Angle.h
	$(CC) $(CFLAGS) unify/Angle.cpp -o $(INTDIR)Angle.o

Cast.o: ./unify/Cast.cpp ./unify/Cast.h ./unify/Cast.inl
	$(CC) $(CFLAGS) unify/Cast.cpp -o $(INTDIR)Cast.o

Color.o: ./unify/Color.cpp ./unify/Color.h
	$(CC) $(CFLAGS) unify/Color.cpp -o $(INTDIR)Color.o

ColorUnit.o: ./unify/ColorUnit.cpp ./unify/ColorUnit.h
	$(CC) $(CFLAGS) unify/ColorUnit.cpp -o $(INTDIR)ColorUnit.o

DataLock.o: ./unify/DataLock.cpp ./unify/DataLock.h
	$(CC) $(CFLAGS) unify/DataLock.cpp -o $(INTDIR)DataLock.o

Frame.o: ./unify/Frame.cpp ./unify/Frame.h
	$(CC) $(CFLAGS) unify/Frame.cpp -o $(INTDIR)Frame.o

FrameLite.o: ./unify/FrameLite.cpp ./unify/FrameLite.h
	$(CC) $(CFLAGS) unify/FrameLite.cpp -o $(INTDIR)FrameLite.o

FrameSet.o: ./unify/FrameSet.cpp ./unify/FrameSet.h
	$(CC) $(CFLAGS) unify/FrameSet.cpp -o $(INTDIR)FrameSet.o

FrameSetInstance.o: ./unify/FrameSetInstance.cpp ./unify/FrameSetInstance.h
	$(CC) $(CFLAGS) unify/FrameSetInstance.cpp -o $(INTDIR)FrameSetInstance.o

Frustum.o: ./unify/Frustum.cpp ./unify/Frustum.h
	$(CC) $(CFLAGS) unify/Frustum.cpp -o $(INTDIR)Frustum.o

FStream.o: ./unify/FStream.cpp ./unify/FStream.h
	$(CC) $(CFLAGS) unify/FStream.cpp -o $(INTDIR)FStream.o

Matrix.o: ./unify/Matrix.cpp ./unify/Matrix.h
	$(CC) $(CFLAGS) unify/Matrix.cpp -o $(INTDIR)Matrix.o

NinePoint.o: ./unify/NinePoint.cpp ./unify/NinePoint.h
	$(CC) $(CFLAGS) unify/NinePoint.cpp -o $(INTDIR)NinePoint.o

Owner.o: ./unify/Owner.cpp ./unify/Owner.h
	$(CC) $(CFLAGS) unify/Owner.cpp -o $(INTDIR)Owner.o

Parameters.o: ./unify/Parameters.cpp ./unify/Parameters.h
	$(CC) $(CFLAGS) unify/Parameters.cpp -o $(INTDIR)Parameters.o

Path.o: ./unify/Path.cpp ./unify/Path.h
	$(CC) $(CFLAGS) unify/Path.cpp -o $(INTDIR)Path.o

Plane.o: ./unify/Plane.cpp ./unify/Plane.h
	$(CC) $(CFLAGS) unify/Plane.cpp -o $(INTDIR)Plane.o

Quaternion.o: ./unify/Quaternion.cpp ./unify/Quaternion.h
	$(CC) $(CFLAGS) unify/Quaternion.cpp -o $(INTDIR)Quaternion.o

Ray.o: ./unify/Ray.cpp ./unify/Ray.h
	$(CC) $(CFLAGS) unify/Ray.cpp -o $(INTDIR)Ray.o

Stream.o: ./unify/Stream.cpp ./unify/Stream.h
	$(CC) $(CFLAGS) unify/Stream.cpp -o $(INTDIR)Stream.o

String.o: ./unify/String.cpp ./unify/String.h ./unify/String.inl
	$(CC) $(CFLAGS) unify/String.cpp -o $(INTDIR)String.o

TexArea.o: ./unify/TexArea.cpp ./unify/TexArea.h
	$(CC) $(CFLAGS) unify/TexArea.cpp -o $(INTDIR)TexArea.o

TexCoords.o: ./unify/TexCoords.cpp ./unify/TexCoords.h
	$(CC) $(CFLAGS) unify/TexCoords.cpp -o $(INTDIR)TexCoords.o

TimeDelta.o: ./unify/TimeDelta.cpp ./unify/TimeDelta.h
	$(CC) $(CFLAGS) unify/TimeDelta.cpp -o $(INTDIR)TimeDelta.o

Variant.o: ./unify/Variant.cpp ./unify/Variant.h
	$(CC) $(CFLAGS) unify/Variant.cpp -o $(INTDIR)Variant.o

createlib: 
	ar ruc $(OUTDIR)Unify.a $(INTDIR)Angle.o $(INTDIR)Cast.o $(INTDIR)Color.o $(INTDIR)ColorUnit.o \
	$(INTDIR)DataLock.o $(INTDIR)Frame.o $(INTDIR)FrameLite.o $(INTDIR)FrameSet.o \
	$(INTDIR)FrameSetInstance.o $(INTDIR)Frustum.o $(INTDIR)FStream.o $(INTDIR)Matrix.o \
	$(INTDIR)NinePoint.o $(INTDIR)Owner.o $(INTDIR)Parameters.o $(INTDIR)Path.o $(INTDIR)Plane.o \
	$(INTDIR)Quaternion.o $(INTDIR)Ray.o $(INTDIR)Stream.o $(INTDIR)String.o $(INTDIR)TexArea.o \
	$(INTDIR)TexCoords.o $(INTDIR)TimeDelta.o $(INTDIR)Variant.o 

make_directories:
	mkdir -p $(INTDIR)
	mkdir -p $(OUTDIR)

# All other headers and inline files that have no cpp files, but want to be tested for changes.
others: unify/Any.h unify/BadCast.h unify/BBox.h unify/BBox.inl unify/BSphere.h unify/BSphere.inl \
	unify/BSquare.h unify/BSquare.inl unify/Exception.h unify/Flags.h unify/KeyValuePair.h \
	unify/LinkList.h unify/LinkList.inl unify/List.h unify/List.inl unify/Lookup.h \
	unify/Lookup.inl unify/Math.h unify/Math.inl unify/Optional.h unify/Optional.inl \
	unify/Parameters.inl unify/Range.h unify/Range.inl unify/Rect.h unify/Rect.inl \
	unify/RowColumn.h unify/RowColumn.inl unify/Size.h unify/Size.inl unify/Size3.h \
	unify/Size3.inl unify/TLink.h unify/TLink.inl unify/Tree.h unify/Tree.inl unify/Triangle.h \
	unify/Triangle.inl unify/Unify.h unify/V2.h unify/V2.inl unify/V3.h unify/V3.inl unify/V4.h \
	unify/V4.inl unify/Viewport.h unify/Viewport.inl

clean:
	rm -f $(INTDIR)*.o
	rm -f $(OUTDIR)*.a
