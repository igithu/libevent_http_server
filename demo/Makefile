#COMAKE2 edit-mode: -*- Makefile -*-
####################64Bit Mode####################
ifeq ($(shell uname -m),x86_64)
CC=gcc
CXX=g++
CXXFLAGS=-g \
  -pipe \
  -W \
  -Wall \
  -fPIC
CFLAGS=-g \
  -pipe \
  -W \
  -Wall \
  -fPIC
CPPFLAGS=-D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\"
INCPATH=-I./src
DEP_INCPATH=-I../third-64/libevent \
  -I../third-64/libevent/include \
  -I../third-64/libevent/output \
  -I../third-64/libevent/output/include

#============ CCP vars ============
CCHECK=@ccheck.py
CCHECK_FLAGS=
PCLINT=@pclint
PCLINT_FLAGS=
CCP=@ccp.py
CCP_FLAGS=


#COMAKE UUID
COMAKE_MD5=09c347de41a57c5fb6c50a0e7a07777a  COMAKE


.PHONY:all
all:comake2_makefile_check libhttp_server.a http_server 
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mall[0m']"
	@echo "make all done"

.PHONY:comake2_makefile_check
comake2_makefile_check:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mcomake2_makefile_check[0m']"
	#in case of error, update 'Makefile' by 'comake2'
	@echo "$(COMAKE_MD5)">comake2.md5
	@md5sum -c --status comake2.md5
	@rm -f comake2.md5

.PHONY:ccpclean
ccpclean:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mccpclean[0m']"
	@echo "make ccpclean done"

.PHONY:clean
clean:ccpclean
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mclean[0m']"
	rm -rf libhttp_server.a
	rm -rf ./output/lib/libhttp_server.a
	rm -rf ./output/include/http_handler.h
	rm -rf ./output/include/http_server.h
	rm -rf ./output/include/util.h
	rm -rf http_server
	rm -rf ./output/bin/http_server
	rm -rf src/http_server_http_handler.o
	rm -rf src/http_server_http_server.o
	rm -rf src/http_server_util.o
	rm -rf src/http_server_main.o

.PHONY:dist
dist:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mdist[0m']"
	tar czvf output.tar.gz output
	@echo "make dist done"

.PHONY:distclean
distclean:clean
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mdistclean[0m']"
	rm -f output.tar.gz
	@echo "make distclean done"

.PHONY:love
love:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlove[0m']"
	@echo "make love done"

libhttp_server.a:src/http_server_http_handler.o \
  src/http_server_http_server.o \
  src/http_server_util.o \
  src/http_handler.h \
  src/http_server.h \
  src/util.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlibhttp_server.a[0m']"
	ar crs libhttp_server.a src/http_server_http_handler.o \
  src/http_server_http_server.o \
  src/http_server_util.o
	mkdir -p ./output/lib
	cp -f --link libhttp_server.a ./output/lib
	mkdir -p ./output/include
	cp -f --link src/http_handler.h src/http_server.h src/util.h ./output/include

http_server:src/http_server_main.o \
  libhttp_server.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mhttp_server[0m']"
	$(CXX) src/http_server_main.o -Xlinker "-(" libhttp_server.a ../third-64/libevent/lib/libevent.a \
  ../third-64/libevent/lib/libevent_core.a \
  ../third-64/libevent/lib/libevent_extra.a \
  ../third-64/libevent/lib/libevent_openssl.a \
  ../third-64/libevent/lib/libevent_pthreads.a -lpthread \
  -lcrypto \
  -lrt -Xlinker "-)" -o http_server
	mkdir -p ./output/bin
	cp -f --link http_server ./output/bin

src/http_server_http_handler.o:src/http_handler.cpp \
  src/util.h \
  src/http_handler.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/http_server_http_handler.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/http_server_http_handler.o src/http_handler.cpp

src/http_server_http_server.o:src/http_server.cpp \
  src/http_handler.h \
  src/util.h \
  src/http_server.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/http_server_http_server.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/http_server_http_server.o src/http_server.cpp

src/http_server_util.o:src/util.cpp \
  src/util.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/http_server_util.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/http_server_util.o src/util.cpp

src/http_server_main.o:src/main.cc \
  src/http_server.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/http_server_main.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/http_server_main.o src/main.cc

endif #ifeq ($(shell uname -m),x86_64)


