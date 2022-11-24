CC = gcc
CPP = g++
LD = g++
CFLAGS = $(FLAGS)
CPPFLAGS = $(FLAGS)
BIN_NAME = orcs
RM = del /f

FLAGS =   -ggdb3 -g -Wall -Wextra -Werror -std=c++0x -lefence -O1 -pedantic -fsanitize=leak -Wno-stringop-truncation -lefence
LDFLAGS = -ggdb3
########################################################################
##FOLDERS
FD_PACKAGE = package
FD_PROCESSOR = processor
FD_BRANCH_PREDICTOR = branch_predictor
FD_OTHER = utils
FD_CACHE = cache
FD_DIRECTORY = directory
FD_PREFETCHER = prefetcher
FD_MEMORY = main_memory
FD_HIVE = hive
FD_VIMA = vima
FD_EMC = emc
FD_CONFIG = config
FD_DISAMBIGUATION = memory_disambiguation



###
LIBRARY = -lz -lconfig++

SRC_PACKAGE = 		$(FD_PACKAGE)/opcode_package.cpp

SRC_TRACE_READER = 	trace_reader.cpp

SRC_PROCESSOR =		$(FD_PROCESSOR)/processor.cpp

SRC_CORE =  simulator.cpp orcs_engine.cpp\
			$(SRC_TRACE_READER)\
			$(SRC_PACKAGE)\
			$(SRC_PROCESSOR)
			
########################################################
OBJS_CORE = ${SRC_CORE:.cpp=.o}
OBJS = $(OBJS_CORE)
########################################################
# implicit rules
%.o : %.cpp %.hpp
	$(CPP) -c $(CPPFLAGS) $< -o $@

########################################################

all: orcs

orcs: $(OBJS_CORE)
	$(LD) $(LDFLAGS) -o $(BIN_NAME) $(OBJS) $(LIBRARY)

clean:
	del /s *.o
	-$(RM) $(BIN_NAME).exe
	@echo OrCS cleaned!
	@echo

debug:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose 2> log.valgrind  ./orcs -c configuration_files/skylakeProposta.cfg -t '../Traces/vecSumScalar' > ../Logs/vecSumScalar.vet.log

orcs_vet: clean all
	mv orcs orcs_vet
	./orcs_vet -c configuration_files/skylake.cfg -t ../simpleVecSum512 > log_debug_n2


10K_test:
	./orcs_vet -c configuration_files/skylake.cfg -t ../simpleVecSum10K > log_debug_10K
	./orcs_base -c configuration_files/skylake.cfg -t ../simpleVecSum10K > log_debug_base_10K