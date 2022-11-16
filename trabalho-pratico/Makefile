CC = gcc #C compiler to use

CFLAGS = `pkg-config --cflags --libs glib-2.0` -O2 -Wall -Wextra -pedantic-errors# compile-time flags

SRCS = src/queries.c src/drivers.c src/rides.c src/parse.c src/users.c src/main.c # C source files

OBJS = $(SRCS:.c=.o) # C objects files

MAIN = programa-principal # executable file
Resultados:
	@mkdir -p $@

all: $(MAIN)

debug: CFLAGS = `pkg-config --cflags --libs glib-2.0` -g
debug: $(MAIN)

$(MAIN): $(OBJS) Resultados
	$(CC)  -o $(MAIN) $(OBJS) $(CFLAGS) 

.c.o:
	$(CC)  -c $<  -o $@ $(CFLAGS)

clean:
	@rm -rf src/*.o $(MAIN) Resultados
