TOPDIR=../..

CXX=g++
CXXFLAGS=-DOS_LINUX -std=c++11 -Wall -Wextra -pthread  -lprotobuf
CXXFLAG=

BIN=alioss_bin

.PHONY: clean VERINFO

# 除去隐藏目录
ALLDIR=$(shell find ../.. -type d | grep -E '\.git|ldpipe_proto|test|cmake|doc|samples|tools|third_party|raw-examples|10m|examples|protobuf' -v)
#$(warning $(ALLDIR))
SRCS1=$(foreach DIR,$(ALLDIR), $(wildcard $(DIR)/*.cpp)) 
SRCS2=$(foreach DIR,$(ALLDIR), $(wildcard $(DIR)/*.cc))
#$(warning $(SRCS1) $(SRCS2))

DEPENDENCY=$(foreach DIR,$(ALLDIR), $(wildcard $(DIR)/*.h))
#$(warning $(DEPENDENCY))

OBJS=$(patsubst %.cpp,%.o,$(SRCS1)) $(patsubst %.cc,%.o,$(SRCS2))
#$(warning $(OBJS))

PROTODIR=$(TOPDIR)/ldpipe_proto
PROTOFILE=$(wildcard $(PROTODIR)/*.proto)
PROTOSRC=$(patsubst %.proto,%.pb.cc,$(PROTOFILE))
PROTOHEAD=$(patsubst %.cc,%.h,$(PROTOSRC))
PROTOOBJS=$(patsubst %.cc,%.o,$(PROTOSRC))

ALL: $(BIN) VERINFO

$(BIN): $(OBJS) $(PROTOOBJS) 
	$(CXX) -o $(BIN) $^ $(CXXFLAGS) $(CXXFLAG)

%.o: %.cc %.cpp %.h
	$(CXX) -o $@ -c $< $(CXXFLAGS)

$(PROTOSRC): $(PROTOFILE)
	cd $(PROTODIR);protoc --cpp_out=. $(notdir $(PROTOFILE))

VERINFO:
	@set -e; \
    newt=`date +'%Y-%m-%d%H'`; \
    newg="(`git rev-parse --short HEAD`)\""; \
    if [ -f VERSION ]; then \
        oldt=`sed -n '2p' VERSION | awk '{print $$2$$3}' | cut -d ':' -f1`; \
        oldg=`sed -n '2p' VERSION | awk '{print $$4}'`; \
    else \
        oldt=""; \
        oldg=""; \
    fi; \
    if [ "$$oldt"x != "$$newt"x -o "$$oldg"x != "$$newg"x ]; then \
        if [ -f VERSION ]; then \
            sed -i "2s/.*/\"$(BIN) `date +'%Y-%m-%d %T'` (`git rev-parse --short HEAD`)\"/" VERSION; \
        else \
            echo "static const char *g_version = " > VERSION; \
            echo "\"$(BIN) `date +'%Y-%m-%d %T'` (`git rev-parse --short HEAD`)\"" >> VERSION; \
            echo -n ";" >> VERSION; \
        fi; \
    fi

clean:
	rm -f $(OBJS) $(BIN)
