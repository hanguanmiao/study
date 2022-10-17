# contrib/ldpipe_fdw/Makefile
MODULE_big = ldpipe_fdw
EXTENSION = ldpipe_fdw
DATA = ldpipe_fdw--1.0.sql
#DOCS = README.ldpipe_fdw
PGFILEDESC = "ldpipe_fdw access method for foreign server"
PG_CXXFLAGS=-std=c++11 -fPIC
SHLIB_LINK=-l:libprotobuf.a -lstdc++

ifndef TOOLCHAIN_INS
  $(error TOOLCHAIN_INS is undefined)
endif

TARGET: all



ALLDIR=$(shell find . -type d | grep -E '/\.|proto|test' -v)
CSRCS=$(foreach DIR,$(ALLDIR), $(wildcard $(DIR)/*.c))
CXXSRCS=$(foreach DIR,$(ALLDIR), $(wildcard $(DIR)/*.cpp))
COBJS=$(patsubst %.c,%.o,$(CSRCS))
CXXOBJS=$(patsubst %.cpp,%.o,$(CXXSRCS))

PROTODIR=$(shell find . -type d | grep -E '/ldpipe_fdw_proto$$')
PROTOFILE=$(wildcard $(PROTODIR)/*.proto)
PROTOSRC=$(patsubst %.proto,%.pb.cc,$(PROTOFILE))
PROTOHEAD=$(patsubst %.cc,%.h,$(PROTOSRC))
PROTOOBJS=$(patsubst %.cc,%.o, $(PROTOSRC))

OBJS = $(COBJS) $(CXXOBJS) $(PROTOOBJS)

ldpipe_fdw.o: module_check $(PROTOSRC)


$(PROTOSRC): $(PROTOFILE)
	cd $(PROTODIR);protoc --cpp_out=. $(notdir $(PROTOFILE))

.PHONY: module_check
module_check:
	@set -e; \
	if [ "${LDPIPE_FDW_MODULE}" = "postgres" ]; then \
		echo "make for postgres"; \
		cp ldpipe_fdw_sql/ldpipe_fdw_postgres--1.0.sql ldpipe_fdw--1.0.sql;	\
	elif [ "${LDPIPE_FDW_MODULE}" = "greenplum" ]; then \
		echo "make for greenplum";	\
		cp ldpipe_fdw_sql/ldpipe_fdw_greenplum--1.0.sql ldpipe_fdw--1.0.sql;	\
	else	\
		echo "LDPIPE_FDW_MODULE should be one of postgres and greenplum";	\
		exit 1;	\
	fi


ifdef USE_PGXS
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
else
subdir = contrib/ldpipe_fdw
top_builddir = ../..
include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk
endif

