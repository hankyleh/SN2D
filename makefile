SOURCES := src/main.cpp src/version.cpp src/input.cpp src/parse.cpp src/echo.cpp src/transport.cpp
HEADERS := src/version.h src/input.h src/parse.h src/echo.h src/transport.h

sn2d: $(SOURCES) $(HEADERS)
	g++ src/main.cpp -o ./sn2d -I./src
