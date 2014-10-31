DIRS := ${shell find testapps ! -iname testapps -type d}
#DIRS:= testapps/patterns

all: $(DIRS) 
	$(foreach DIR, $(DIRS), make --no-print-directory -C $(DIR);)
