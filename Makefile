CC=g++
RM=rm -rf
MKDIR=mkdir -p
CFLAGS_I=-I$(INCDIR) -I$(THIRD_PARTY_INC)
CFLAGS_L=-pthread -ldl -lsqlite3
CFLAGS=-g
THIRD_PARTY_INC=./third_party/includes
INCDIR=./inc
SRCDIR=./src
BLDDIR=./build
INC=$(shell find $(INCDIR) -name '*.Hxx')
SRC=$(shell find $(SRCDIR) -name '*.cxx')
OBJ=$(patsubst ./%,$(BLDDIR)/%,$(SRC:.cxx=.o))
BIN=$(BLDDIR)/server

build: $(BIN)

$(BIN): $(OBJ) $(INC)
	$(CC) -o $(BIN) $(CFLAGS) $(CFLAGS_I) $(OBJ) $(CFLAGS_L)

$(BLDDIR)/%.o: %.cxx
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS_I) -c $< -o $@

$(BLDDIR):
	$(MKDIR) $(BLDDIR)

.PHONY: clean
clean:
	$(RM) $(BIN)
	$(RM) $(BLDDIR)
