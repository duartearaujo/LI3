CC = gcc #C compiler to use

CFLAGS = -Iinclude `pkg-config --cflags --libs glib-2.0` -O3 -Wall -Werror -lncurses # compile-time flags

SRCS = src/query1.c src/query2.c src/query3.c src/query4.c src/query5.c src/query6.c src/query7.c src/query8.c src/query9.c src/queries.c src/drivers.c src/rides.c src/parse.c src/users.c src/datas.c src/dataverification.c src/cidades.c src/interactive.c src/catalogos.c src/main.c # C source files

SRCS_TESTE := $(filter-out src/main.c,$(SRCS))
SRCS_TESTE += src/testeQueries.c

OBJS = $(SRCS:.c=.o) # C objects files

OBJS_TESTE = $(SRCS_TESTE:.c=.o) # C objects files

MAIN = programa-principal # executable file

MAIN_TESTE = programa-testes

all: $(MAIN) $(MAIN_TESTE)

Resultados_testes:
	@mkdir -p $@

Resultados:
	@mkdir -p $@

$(MAIN_TESTE): $(OBJS_TESTE) Resultados_testes
	$(CC)  -o $(MAIN_TESTE) $(OBJS_TESTE) $(CFLAGS) 

debug: CFLAGS = `pkg-config --cflags --libs glib-2.0` -g -lncurses
debug: $(MAIN) $(MAIN_TESTE)

$(MAIN): $(OBJS) Resultados
	$(CC)  -o $(MAIN) $(OBJS) $(CFLAGS) 

.c.o:
	$(CC)  -c $<  -o $@ $(CFLAGS)

clean:
	@rm -rf src/*.o $(MAIN) $(MAIN_TESTE) Resultados Resultados_testes

out_clean: 
	@rm -f Resultados/*.txt