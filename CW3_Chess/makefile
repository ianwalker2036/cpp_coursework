#target: prerequisites
#<tab> recipe

OBJ = ChessMain.o ChessBoard.o ChessPiece.o Bishop.o King.o Queen.o Pawn.o Rook.o Knight.o
executable = chess

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
