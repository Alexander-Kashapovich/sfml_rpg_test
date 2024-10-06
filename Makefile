#mingw32-make all

CHECK = cppcheck

PLATFORM = --platform=win64
ENABLE = --enable=style --enable=performance --enable=warning --enable=unusedFunction 
OTH_FLAGS = --inconclusive --language=c++ --std=c++17 --force

FLAGS = $(PLATFORM) $(ENABLE) $(OTH_FLAGS)

SRCS := $(shell C:/msys64/usr/bin/find.exe ./src -type f)

all: analyze

analyze: $(SRCS)
	@echo "Starting static analysis..."
	$(CHECK) $(FLAGS) $(INCLUDE_FLAGS) $(SRCS)
	@echo "Static analysis completed."