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

depend: $(SRCS)
	makedepend -f ${PRJ_ROOT}/rules.mk -- $(SRCS) -I ${PRJ_ROOT}/include  -Y > /dev/null 2>&1  

clean:
	$(RM) $(DIR)/*.o $(PRJ_ROOT)/bin/$(NAME) 



# DO NOT DELETE

/home_local/miranda/training//testapps/C/Arrays.o: /home_local/miranda/training/testapps/C/Arrays.h
/home_local/miranda/training//testapps/C/main.o: /home_local/miranda/training/testapps/C/Arrays.h
/home_local/miranda/training//testapps/C/main.o: /home_local/miranda/training/testapps/C/Io.h
