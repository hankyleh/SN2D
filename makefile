SOURCES := src/main.cpp src/input.cpp src/parse.cpp src/transport.cpp src/msg.cpp src/echo.cpp
HEADERS := src/version.h src/input.h src/parse.h src/transport.h src/msg.h src/echo.h
CFLAGS = -O3

sn2d: $(SOURCES) $(HEADERS)
	g++ $(SOURCES) -o ./sn2d -I./src $(CFLAGS)
