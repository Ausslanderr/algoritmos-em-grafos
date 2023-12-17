# Variáveis para os compiladores e flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Diretório dos arquivos fonte
SRCDIR = src

# Nome do executável
TARGET = algoritmo

# Arquivos fonte
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Arquivos objeto
OBJECTS = $(SOURCES:.cpp=.o)

# Regra padrão
all: $(TARGET)

# Regra para construir o executável
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para construir os arquivos objeto
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os arquivos compilados
clean:
	rm -f $(SRCDIR)/*.o $(TARGET)

# Regra para executar o programa
run: $(TARGET)
	./$(TARGET)

# Remova a regra de dependência abaixo se não houver arquivo algoritmo.h
# $(SRCDIR)/algoritmo.o: $(SRCDIR)/algoritmo.h
