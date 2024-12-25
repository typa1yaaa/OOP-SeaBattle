# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -std=c++17 -I./include -I./part_field -I./game -I./abilities -I./lb4

# Цель по умолчанию
all: test_class

# Сборка программы из объектных файлов
test_class: test_class.o part_field/FieldSegment.o part_field/Ship.o part_field/ShipManager.o part_field/Field.o game/Exceptions.o part_field/Cell.o abilities/Abilities.o abilities/AbilitiesManager.o game/User.o game/Bot.o game/Game.o game/GameState.o lb4/Observer.o  lb4/InputProcessor.o lb4/CommandMapper.o lb4/FieldRendering.o 
	$(CXX) $(CXXFLAGS) test_class.o part_field/FieldSegment.o part_field/Ship.o part_field/ShipManager.o part_field/Field.o game/Exceptions.o part_field/Cell.o abilities/Abilities.o abilities/AbilitiesManager.o game/User.o game/Bot.o game/Game.o game/GameState.o lb4/Observer.o lb4/InputProcessor.o lb4/CommandMapper.o lb4/FieldRendering.o -o test_class

# Компиляция test_class.cpp в test_class.o
src/test_class.o: src/test_class.cpp part_field/FieldSegment.h part_field/Ship.h part_field/ShipManager.h part_field/Field.h game/Exceptions.h part_field/Cell.h abilities/Abilities.h abilities/AbilitiesManager.h game/User.h game/Bot.h game/Game.h game/GameState.h lb4/Observer.h lb4/GameMenagement.h lb4/InputProcessor.h lb4/CommandMapper.h lb4/FieldRendering.h lb4/GameDisplay.h
	$(CXX) $(CXXFLAGS) -c src/test_class.cpp -o src/test_class.o

# Компиляция FieldSegment.cpp в FieldSegment.o
part_field/FieldSegment.o: part_field/FieldSegment.cpp part_field/FieldSegment.h
	$(CXX) $(CXXFLAGS) -c part_field/FieldSegment.cpp -o part_field/FieldSegment.o

# Компиляция Ship.cpp в Ship.o
part_field/Ship.o: part_field/Ship.cpp part_field/Ship.h
	$(CXX) $(CXXFLAGS) -c part_field/Ship.cpp -o part_field/Ship.o

# Компиляция ShipManager.cpp в ShipManager.o
part_field/ShipManager.o: part_field/ShipManager.cpp part_field/ShipManager.h
	$(CXX) $(CXXFLAGS) -c part_field/ShipManager.cpp -o part_field/ShipManager.o

# Компиляция Field.cpp в Field.o
part_field/Field.o: part_field/Field.cpp part_field/Field.h
	$(CXX) $(CXXFLAGS) -c part_field/Field.cpp -o part_field/Field.o

# Компиляция Exceptions.cpp в Exceptions.o
game/Exceptions.o: game/Exceptions.cpp game/Exceptions.h
	$(CXX) $(CXXFLAGS) -c game/Exceptions.cpp -o game/Exceptions.o

# Компиляция Cell.cpp в Cell.o
part_field/Cell.o: part_field/Cell.cpp part_field/Cell.h
	$(CXX) $(CXXFLAGS) -c part_field/Cell.cpp -o part_field/Cell.o

# Компиляция Abilities.cpp в Abilities.o
abilities/Abilities.o: abilities/Abilities.cpp abilities/Abilities.h
	$(CXX) $(CXXFLAGS) -c abilities/Abilities.cpp -o abilities/Abilities.o

# Компиляция AbilitiesManager.cpp в AbilitiesManager.o
abilities/AbilitiesManager.o: abilities/AbilitiesManager.cpp abilities/AbilitiesManager.h
	$(CXX) $(CXXFLAGS) -c abilities/AbilitiesManager.cpp -o abilities/AbilitiesManager.o

# Компиляция User.cpp в User.o
game/User.o: game/User.cpp game/User.h
	$(CXX) $(CXXFLAGS) -c game/User.cpp -o game/User.o

# Компиляция Bot.cpp в Bot.o
game/Bot.o: game/Bot.cpp game/Bot.h
	$(CXX) $(CXXFLAGS) -c game/Bot.cpp -o game/Bot.o

# Компиляция GameState.cpp в GameState.o
game/GameState.o: game/GameState.cpp game/GameState.h game/Game.h
	$(CXX) $(CXXFLAGS) -c game/GameState.cpp -o game/GameState.o

# Компиляция Game.cpp в Game.o
game/Game.o: game/Game.cpp game/Game.h game/GameState.h
	$(CXX) $(CXXFLAGS) -c game/Game.cpp -o game/Game.o

# Компиляция Observer.cpp в Observer.o
lb4/Observer.o: lb4/Observer.cpp lb4/Observer.h
	$(CXX) $(CXXFLAGS) -c lb4/Observer.cpp -o lb4/Observer.o

# # Компиляция GameMenagement.cpp в GameMenagement.o
# lb4/GameMenagement.o: lb4/GameMenagement.cpp lb4/GameMenagement.h lb4/GameMenagement.tpp
# 	$(CXX) $(CXXFLAGS) -c lb4/GameMenagement.cpp -o lb4/GameMenagement.o

# Компиляция InputProcessor.cpp в InputProcessor.o
lb4/InputProcessor.o: lb4/InputProcessor.cpp lb4/InputProcessor.h
	$(CXX) $(CXXFLAGS) -c lb4/InputProcessor.cpp -o lb4/InputProcessor.o

# Компиляция CommandMapper.cpp в CommandMapper.o
lb4/CommandMapper.o: lb4/CommandMapper.cpp lb4/CommandMapper.h
	$(CXX) $(CXXFLAGS) -c lb4/CommandMapper.cpp -o lb4/CommandMapper.o

# Компиляция CommandMapper.cpp в CommandMapper.o
lb4/FieldRendering.o: lb4/FieldRendering.cpp lb4/FieldRendering.h
	$(CXX) $(CXXFLAGS) -c lb4/FieldRendering.cpp -o lb4/FieldRendering.o

# # Компиляция GameMenagement.cpp в GameMenagement.o
# lb4/GameDisplay.o: lb4/GameDisplay.cpp lb4/GameDisplay.h lb4/GameDisplay.tpp
# 	$(CXX) $(CXXFLAGS) -c lb4/GameDisplay.cpp -o lb4/GameDisplay.o

# Очистка объектных файлов и исполняемого файла
clean:
	rm -f src/*.o part_field/*.o game/*.o abilities/*.o lb4/*.o test_class

# Указание, что цели 'all' и 'clean' являются псевдоцелями
.PHONY: all clean