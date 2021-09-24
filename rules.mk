DIR:=$(PRJ_ROOT)/$(DIR)

SRCS:= $(patsubst %,$(DIR)/%,$(SRCS))

ifneq (,$(findstring gcc-10,$(CC)))
	OBJS:= $(patsubst %.cpp,%.o,$(SRCS))
else
	OBJS:= $(patsubst %.c,%.o,$(SRCS))
endif

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


