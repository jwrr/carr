LIB=libcarr
CC=gcc
CFLAGS=-Wall -std=c99 
DEPS = src/carr_esc.h src/carr_readline.h src/headers.h src/carr_cis.h src/carr.h src/carr_readline_lua.h src/lua.h src/luaconf.h

OBJ=carr.o carr_readline.o carr_readline_lua.o lua_hacked.o

install/lib/$(LIB).a: $(LIB).a
	mkdir -p install/lib
	mv $(LIB).a  $@
	mkdir -p install/include
	cp src/carr*.h install/include
	
$(LIB).a: $(OBJ)
	ar cr $@ $(OBJ)

%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf *.o *.a install
