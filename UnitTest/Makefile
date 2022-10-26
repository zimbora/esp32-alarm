

# additional flags
CXXFLAGS += -std=c++11

MACROS = -DDEBUG
MACROS += -DDEBUGALARM

all: alarm

alarm: init cp_alarm make_alarm run clean

init:
	mkdir ./tmp
	cp ./Arduino.hpp ./tmp/
	cp ./Arduino.cpp ./tmp/

cp_alarm:
	cp ../alarm.hpp ./tmp/
	cp ../alarm.cpp ./tmp/

make_alarm:
	@echo "Compiling.."
	clang++ $(CXXFLAGS) -DUNITTEST -DALARMTEST $(MACROS) alarm_runner.cpp ./tmp/Arduino.cpp ./tmp/alarm.cpp

run:
	@echo "Running test.."
	./a.out

clean:
	@echo "Cleaning up"
	rm -r ./tmp
	rm *.out
