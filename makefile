SOURCES := src/main.cpp src/input.cpp src/parse.cpp src/transport.cpp src/msg.cpp
HEADERS := src/version.h src/input.h src/parse.h src/transport.h src/msg.h

sn2d: $(SOURCES) $(HEADERS)
	g++ $(SOURCES) -o ./sn2d -I./src
