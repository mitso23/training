LIBS_DIR := ${shell find src -type d ! -iname src ! -iname libcontainers  ! -iname libdatastructures }
TESTAPPS_DIR := ${shell find testapps -type d ! -iname datastructures ! -iname testapps}

all: 
	$(foreach LIB_DIR, $(LIBS_DIR), make --no-print-directory -C $(LIB_DIR);)
	$(foreach DIR, $(TESTAPPS_DIR), make --no-print-directory -C $(DIR);)

clean:
	$(foreach LIB_DIR, $(LIBS_DIR), make clean -C $(LIB_DIR);)
	$(foreach DIR, $(TESTAPPS_DIR), make clean -C $(DIR);)

