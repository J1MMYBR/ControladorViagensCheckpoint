# Nome do programa final
PROG = output

# Compilador
CC = g++

# Flags do compilador
CPPFLAGS = -Wall -O0 -g -pedantic

# Lista de objetos
OBJS = main.o cidade.o passageiro.o trajeto.o transporte.o utils.o viagem.o

# Regra padrão que será executada por padrão
all: $(PROG)

# Regra para criar o executável final
$(PROG): $(OBJS)
	$(CC) $(CPPFLAGS) -o $(PROG) $(OBJS)

# Regras de compilação de objetos
main.o: main.cpp cidade.h passageiro.h trajeto.h transporte.h utils.h viagem.h
	$(CC) $(CPPFLAGS) -c main.cpp -o main.o

cidade.o: cidade.cpp cidade.h
	$(CC) $(CPPFLAGS) -c cidade.cpp -o cidade.o

passageiro.o: passageiro.cpp passageiro.h cidade.h
	$(CC) $(CPPFLAGS) -c passageiro.cpp -o passageiro.o

trajeto.o: trajeto.cpp trajeto.h passageiro.h cidade.h
	$(CC) $(CPPFLAGS) -c trajeto.cpp -o trajeto.o

transporte.o: transporte.cpp transporte.h cidade.h 
	$(CC) $(CPPFLAGS) -c transporte.cpp -o transporte.o
	
utils.o: utils.cpp utils.h cidade.h passageiro.h trajeto.h transporte.h utils.h viagem.h
	$(CC) $(CPPFLAGS) -c utils.cpp -o utils.o

viagem.o: viagem.cpp viagem.h cidade.h transporte.h passageiro.h
	$(CC) $(CPPFLAGS) -c viagem.cpp -o viagem.o
	
# Regra de limpeza (make clean)
clean:
	del /Q core $(PROG) $(OBJS) *.o 2>nul