CC = em++
CC_FLAGS = -w

EXEC = index2.html
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) -s EXPORTED_FUNCTIONS="['_main', '_malloc','_getScore']" --preload-file n3310s.jpg

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

clean:
	rm -f $(EXEC) $(OBJECTS)
