CC = gcc #C compiler to use

CFLAGS = -Iinclude `pkg-config --cflags --libs glib-2.0` -O3 -Wall -Werror # compile-time flags

SRCS = src/query1.c src/query2.c src/query3.c src/query4.c src/query5.c src/query6.c src/query7.c src/query8.c src/query9.c src/queries.c src/drivers.c src/rides.c src/parse.c src/users.c src/dataverification.c src/cidades.c src/main.c # C source files

OBJS = $(SRCS:.c=.o) # C objects files

MAIN = programa-principal # executable file

all: $(MAIN)

Resultados:
	@mkdir -p $@

debug: CFLAGS = `pkg-config --cflags --libs glib-2.0` -g
debug: $(MAIN)

$(MAIN): $(OBJS) Resultados
	$(CC)  -o $(MAIN) $(OBJS) $(CFLAGS) 

.c.o:
	$(CC)  -c $<  -o $@ $(CFLAGS)

clean:
	@rm -rf src/*.o $(MAIN) Resultados

out_clean: 
	@rm -f Resultados/*.txt