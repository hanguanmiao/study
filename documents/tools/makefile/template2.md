TOPDIR=../..

CXX=g++
CXXFLAGS=-DOS_LINUX -std=c++11 -Wall -Wextra -pthread  -lprotobuf -lalibabacloud-oss-cpp-sdk -lcurl -lssl -lcrypto
CXXFLAG=

BIN=alioss_bin

.PHONY: clean VERINFO

# 除去隐藏目录
ALLDIR=$(shell find ../.. -type d | grep -E '\.git|ldpipe_proto|test|cmake|doc|samples|tools|third_party|raw-examples|10m|examples|protobuf' -v)
SRCS=$(foreach DIR,$(ALLDIR), $(wildcard $(DIR)/*.cc))

OBJS=$(patsubst %.cc,%.o,$(SRCS))

DEPENDENCY=$(patsubst %.o,%.o.d,$(OBJS))

PROTODIR=$(TOPDIR)/common/ldpipe_proto
PROTOFILE=$(wildcard $(PROTODIR)/*.proto)
PROTOSRC=$(patsubst %.proto,%.pb.cc,$(PROTOFILE))
#PROTOHEAD=$(patsubst %.cc,%.h,$(PROTOSRC))
PROTOOBJS=$(patsubst %.cc,%.o,$(PROTOSRC))

ALL: VERINFO $(BIN)

$(BIN): $(OBJS) $(PROTOOBJS) 
	$(CXX) -o $(BIN) $^ $(CXXFLAGS) $(CXXFLAG)

%.o: %.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(CXXFLAG) -MMD -MF $@.d 

$(PROTOSRC): $(PROTOFILE)
	cd $(PROTODIR);protoc --cpp_out=. $(notdir $(PROTOFILE))

VERINFO:
	@set -e; \
    newt=`date +'%Y-%m-%d%H'`; \
    newg="(`git rev-parse --short HEAD`)\""; \
    if [ -f VERSION ]; then \
        oldt=`sed -n '3p' VERSION | awk '{print $$2$$3}' | cut -d ':' -f1`; \
        oldg=`sed -n '3p' VERSION | awk '{print $$4}'`; \
    else \
        oldt=""; \
        oldg=""; \
    fi; \
    if [ "$$oldt"x != "$$newt"x -o "$$oldg"x != "$$newg"x ]; then \
        if [ -f VERSION ]; then \
            sed -i "3s/.*/\"$(BIN) `date +'%Y-%m-%d %T'` (`git rev-parse --short HEAD`)\"/" VERSION; \
        else \
            echo "static const char *g_version = " > VERSION; \
			echo "R\"HLP(" >> VERSION; \
            echo "$(BIN) `date +'%Y-%m-%d %T'` (`git rev-parse --short HEAD`)" >> VERSION; \
            echo -n ")HLP\";" >> VERSION; \
        fi; \
    fi

clean:
	rm -f $(OBJS) $(BIN) $(DEPENDENCY) $(PROTOOBJS) VERSION

-include $(DEPENDENCY)
