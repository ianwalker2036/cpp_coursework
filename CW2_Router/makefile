#target: prerequisites
#<tab> recipe

OBJ = networkMain.o host.o router.o message.o
executable = network

GCC = g++
CFLAGS = -Wall -g -MMD

$(executable): $(OBJ)
	$(GCC) $(CFLAGS) $(OBJ) -o $(executable)

%.o: %.cpp
	$(GCC) $(CFLAGS) -c $<

-include $(OBJ:.o=.d)

.PHONY: clean
clean: 
	rm -f $(OBJ) $(executable) $(OBJ:.o=.d)
