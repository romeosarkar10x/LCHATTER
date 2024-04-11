SRC_DIRECTORY:=Src
OBJ_DIRECTORY:=Lib
DEP_DIRECTORY:=Lib
DEP_INTERMEDIATE_PREFIX=!

OBJ_FILES_DELIMITER=@


SRC_EXTENSION:=cpp
OBJ_EXTENSION:=o
DEP_EXTENSION:=d

CC=g++
CXXFLAGS=-c -std=c++20 -Wall -Wshadow -Wunused-result -Wextra -Wpedantic \
-Wconversion -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused \
-Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2 \
-Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast \
-ftemplate-depth=1000000 -fconcepts-diagnostics-depth=1000000


SRC_FILES:=${shell find ${SRC_DIRECTORY} -name *.${SRC_EXTENSION} }

# getsrc=${subst }

OBJ_FILES:=${subst ${SRC_DIRECTORY}${OBJ_FILES_DELIMITER},${OBJ_DIRECTORY}/,${subst .${SRC_EXTENSION},.${OBJ_EXTENSION},${subst /,${OBJ_FILES_DELIMITER},${SRC_FILES}}}}
DEP_FILES:=${patsubst ${OBJ_DIRECTORY}/%.${OBJ_EXTENSION},${DEP_DIRECTORY}/%.${DEP_EXTENSION},${OBJ_FILES}}
DEP_INTERMEDIATE_FILES:=${patsubst ${DEP_DIRECTORY}/%,${DEP_DIRECTORY}/${DEP_INTERMEDIATE_PREFIX}%,${DEP_FILES}}

# CXXFLAGS

func=${patsubst ${OBJ_DIRECTORY}/%${OBJ_EXTENSION},${SRC_DIRECTORY}/%${SRC_EXTENSION},${subst ${OBJ_FILES_DELIMITER},/,$1}}


# $(OBJ_DIRECTORY)/%.o: $(SRC_DIRECTORY)/%.cpp $(DEPS)
	
# ${OBJ_DIRECTORY}/%.${OBJ_EXTENSION}: ${SRC_DIRECTORY}/${subst _,/,%}
# 	g++ -c $< -o $@

# ${OBJ_DIRECTORY}/%.${OBJ_EXTENSION}: ${}
# 	echo "gadha"

# ${DEP_DIRECTORY}%.${DEP_EXTENSION}: ${OBJ_DIRECTORY}%.${SRC_EXTENSION}
# 	@set -e; rm -f $@; \
# 	$(CC) -MM $< > $@.$$$$; \
# 	sed "s,\($*\)\.o[ :]*,\1.o $@ : ,g" < $@.$$$$ > $@; \
# 	rm -f $@.$$$$
# define func
#     $(eval $@_HOSTNAME = $(1))
#     $(eval $@_PORT = $(2))
#     echo "${$@_PROTOCOL}//${$@_HOSTNAME}:${$@_PORT}/"
# endef


# func=$${subst _,/,$${patsubst ${DEP_DIRECTORY}/%.${DEP_EXTENSION},${SRC_DIRECTORY}/%.${SRC_EXTENSION},$${1}}}
# .SECONDEXPANSION:
# ${DEP_DIRECTORY}/%.d: $${subst _,/,$${patsubst ${DEP_DIRECTORY}/%.${DEP_EXTENSION},${SRC_DIRECTORY}/%.${SRC_EXTENSION},$$@}}
# 	echo "Success!" ; \
# 	echo "$@ + $<"
# ${DEP_DIRECTORY}/%.d: ${subst _,/,${patsubst %,${SRC_DIRECTORY}/%.${SRC_EXTENSION},$*}}

# ${DEP_DIRECTORY}/%.${DEP_EXTENSION}: ${subst _,/,${patsubst %,${SRC_DIRECTORY}/%.${SRC_EXTENSION},%}}
# .SECONDEXPANSION:


${DEP_DIRECTORY}/${DEP_INTERMEDIATE_PREFIX}%.${DEP_EXTENSION}:
	echo -e "${DEP_DIRECTORY}/$*.${DEP_EXTENSION}: ${subst ${OBJ_FILES_DELIMITER},/,${patsubst %,${SRC_DIRECTORY}/%.${SRC_EXTENSION},$*}}\n\
	\tset -e; rm -f \$$@; \$$(CC) -MM \$$< > \$$@.\$$\$$\$$\$$; sed \"s,\(\$$*\)\.o[ :]*,\1.o \$$@ : ,g\" < \$$@.\$$\$$\$$\$$ > \$$@; rm -f \$$@.\$$\$$\$$\$$\n\
	include ${DEP_DIRECTORY}/$*.${DEP_EXTENSION}" > \
	${DEP_DIRECTORY}/${DEP_INTERMEDIATE_PREFIX}$*.${DEP_EXTENSION}


include ${DEP_INTERMEDIATE_FILES}
# include ${DEP_FILES}


${OBJ_DIRECTORY}/%.${OBJ_EXTENSION}: ${DEP_DIRECTORY}/%.${DEP_EXTENSION}
	g++ $(CXXFLAGS) -o $@ ${call func,$@}
# echo "Success!" ; \
	# echo "$@ + $* + $<"

# include ${

# ${OBJ_DIRECTORY}

# ${DEP_DIRECTORY}/%.${DEP_EXTENSION}: ${subst _,/,${patsubst ${DEP_DIRECTORY}/%.${DEP_EXTENSION},${SRC_DIRECTORY}/%.${SRC_EXTENSION},$@}}
# 	echo "Success!"

# ${DEP_DIRECTORY}/%.${DEP_EXTENSION}:
# 	echo "Success!"
# .SECONDEXPANSION:

# Run:
# 	@echo "${SRC_FILES}"
# 	@echo ""
# 	@echo "${OBJ_FILES}"
# 	@echo ""
# 	@echo "${DEP_FILES}"
# 	@echo ""
# 	@echo "${DEP_INTERMEDIATE_FILES}"
	
# @echo "${subst _,/,${patsubst ${DEP_DIRECTORY}/%.${DEP_EXTENSION},${SRC_DIRECTORY}/%.${SRC_EXTENSION},${DEP_FILES}}}"

# echo "${search}"

${OBJ_DIRECTORY}/AppBackend.a: ${OBJ_FILES}
	ar -cruU $@ $?



# echo "here"

# rm -f "" ${DEP_FILES} ${DEP_INTERMEDIATE_FILES}

.DEFAULT_GOAL:=${OBJ_DIRECTORY}/AppBackend.a
# include ${DEP_FILES}
# .DEFAULT_GOAL:=RUN
# RUN:
# 	@echo "ha ha ha!"

# 	${MAKE}
