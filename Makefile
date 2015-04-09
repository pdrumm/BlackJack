CMP = g++
MAIN = mainDeck
FUNC1 = CardDeck
FUNC2 = Player
FUNC3 = BlackJack
EXEC = $(MAIN)

$(EXEC): $(MAIN).o $(FUNC1).o $(FUNC2).o $(FUNC3).o
	$(CMP) -o $(EXEC)  $(MAIN).o $(FUNC1).o $(FUNC2).o $(FUNC3).o

$(MAIN).o: $(MAIN).cpp 
	$(CMP) -c $(MAIN).cpp

$(FUNC1).o: $(FUNC1).cpp $(FUNC1).h
	$(CMP) -c $(FUNC1).cpp

$(FUNC2).o: $(FUNC2).cpp $(FUNC2).h
	$(CMP) -c $(FUNC2).cpp

$(FUNC3).o: $(FUNC3).cpp $(FUNC3).h
	$(CMP) -c $(FUNC3).cpp

clean:
	rm $(EXEC) *.o
