CC=g++
CPPFLAGS= -g -Wall

OBJS= ictclas.o Result/Result.o Segment/DynamicArray.o Segment/NShortPath.o \
	  Segment/Queue.o Segment/SegGraph.o Segment/Segment.o \
	  Tag/Span.o \
	  Unknown/UnknowWord.o \
	  Utility/ContextStat.o Utility/Dictionary.o \
	  Utility/Utility.o \
	  Utility/MyDebug.o

all: $(OBJS)
	$(CC) $(CPPFLAGS) -o ictclas $(OBJS)

module: $(OBJS)
	swig -perl5 -c++ ictclas.i
	$(CC) -c -fpic ictclas_wrap.cxx -D_GNU_SOURCE -DTHREADS_HAVE_PIDS -DDEBIAN -fno-strict-aliasing -pipe -isystem /usr/local/include -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -I/usr/lib/perl5/5.8.6/i386-linux-thread-multi/CORE
	g++ -shared $(OBJS) ictclas_wrap.o -o ictclas.so


ictclas.o: ictclas.cpp ictclas.h

Result/Result.o: Result/Result.cpp Result/Result.h

SegmentSegment/DynamicArray.o: SegmentSegment/DynamicArray.cpp SegmentSegment/DynamicArray.h

Segment/NShortPath.o: Segment/NShortPath.cpp Segment/NShortPath.h

Segment/Queue.o: Segment/Queue.cpp Segment/Queue.h

Segment/SegGraph.o: Segment/SegGraph.cpp Segment/SegGraph.h

Segment/Segment.o : Segment/Segment.cpp Segment/Segment.h 

Tag/Span.o : Tag/Span.cpp Tag/Span.h 

Unknown/UnknowWord.o : Unknown/UnknowWord.cpp Unknown/UnknowWord.h 

Utility/ContextStat.o: Utility/ContextStat.cpp Utility/ContextStat.h

Utility/Dictionary.o: Utility/Dictionary.cpp Utility/Dictionary.h

Utility/Utility.o: Utility/Utility.cpp Utility/Utility.h

Utility/MyDebug.o: Utility/MyDebug.cpp Utility/MyDebug.h

clean:
	rm -f $(OBJS) ictclas ictclas_wrap.cxx ictclas_wrap.o ictclas.pm ictclas.so
