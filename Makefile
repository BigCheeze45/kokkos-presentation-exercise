KOKKOS_PATH = /usr/local/kokkos-2.02.07
COMMON_DIR=common/
KOKKOS_DEVICES = "OpenMP"
EXE_NAME = "VecAdd-NaiveParallel-Vanilla"

SRC = $(wildcard *.cpp)

default: build
	echo "Start Build"


ifneq (,$(findstring Cuda,$(KOKKOS_DEVICES)))
CXX = ${KOKKOS_PATH}/config/nvcc_wrapper
EXE = ${EXE_NAME}.cuda
KOKKOS_ARCH = "SNB,Kepler30"
KOKKOS_CUDA_OPTIONS = "enable_lambda"
else
CXX = g++
EXE = ${EXE_NAME}.host
KOKKOS_ARCH = "SNB"
endif

CXXFLAGS = -O3
LINK = ${CXX}
LINKFLAGS = -g

DEPFLAGS = -M

OBJ = $(SRC:.cpp=.o)
LIB =

include $(KOKKOS_PATH)/Makefile.kokkos

build: $(EXE)

$(EXE): $(OBJ) $(COMMON_DIR)/Measurements.cpp $(COMMON_DIR)/Configuration.cpp $(KOKKOS_LINK_DEPENDS)
	$(LINK) $^ $(KOKKOS_LDFLAGS) $(LINKFLAGS) $(EXTRA_PATH) $(KOKKOS_LIBS) $(LIB) -o $(EXE)

clean: kokkos-clean
	rm -f *.o *.cuda *.host

# Compilation rules

#%.o:%.cpp $(COMMON_DIR)/Measurements.cpp $(COMMON_DIR)/Configuration.cpp $(KOKKOS_CPP_DEPENDS)
%.o:%.cpp $(KOKKOS_CPP_DEPENDS)
	$(CXX) $(KOKKOS_CPPFLAGS) $(KOKKOS_CXXFLAGS) $(CXXFLAGS) $(EXTRA_INC) -c $<

test: $(EXE)
	./$(EXE)
