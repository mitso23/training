DIR:=$(PRJ_ROOT)/$(DIR)

SRCS:= $(patsubst %,$(DIR)/%,$(SRCS))

OBJS:= $(patsubst %.cpp,%.o,$(SRCS))

ifneq (,$(findstring .so,$(NAME)))
	OUTDIR:=$(PRJ_ROOT)/lib/$(NAME)
else
	OUTDIR:=$(PRJ_ROOT)/bin/$(NAME)
endif

$(NAME) : $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $(OUTDIR) 

$(DIR)/%.o: $(DIR)/%.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) -c $< -o $@

$(DIR)/%.o: $(DIR)/%.c
	$(CC) -c $(CFLAGS) $(INCLUDES) -c $< -o $@

depend: $(SRCS)
	makedepend -f ${PRJ_ROOT}/rules.mk -- $(SRCS) -I ${PRJ_ROOT}/include -Y > /dev/null 2>&1  

clean:
ifeq (,$(findstring .so,$(NAME)))
	$(RM) $(DIR)/*.o $(PRJ_ROOT)/bin/$(NAME) 
else
	$(RM) $(DIR)/*.o $(DIR)/*.so $(PRJ_ROOT)/lib/$(NAME)
endif
# DO NOT DELETE

/home/mitso23/c++/training//testapps/C++17/C++17.o: /home/mitso23/c++/training/testapps/C++17/AutomaticTypeDeduction.h
/home/mitso23/c++/training//testapps/C++17/C++17.o: /home/mitso23/c++/training/testapps/C++17/FoldExpressions.h
/home/mitso23/c++/training//testapps/C++17/C++17.o: /home/mitso23/c++/training/testapps/C++17/StructureBinding.h
/home/mitso23/c++/training//testapps/C++17/C++17.o: /home/mitso23/c++/training/testapps/C++17/lambdas.h
/home/mitso23/c++/training//testapps/C++17/C++17.o: /home/mitso23/c++/training/include/utils/Noisy.h
/home/mitso23/c++/training//testapps/C++17/C++17.o: /home/mitso23/c++/training/include/utils/counted.h
/home/mitso23/c++/training//testapps/C++17/C++17.o: /home/mitso23/c++/training/testapps/C++17/templates.h
