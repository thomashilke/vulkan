.SUFFIX:

include config.mk

SOURCES += $(wildcard tests/*.cpp)
OBJECTS = $(patsubst %.cpp,build/%.o,$(SOURCES))
DEPS = $(patsubst %.cpp,build/%.deps,$(SOURCES))

.PHONY = all deps clean install install-bin install-header install-lib install-dev
.DEFAULT_GOAL = all

all: $(BIN) $(LIB) $(HEADERS) tests

tests: bin/tests

run-tests: tests
	@bin/tests

-include $(DEPS)

$(HEADERS): include/$(PKG_NAME)/%: src/%
	@echo "[INST]" $(<:src/%=%)
	@$(MKDIR) $(MKDIRFLAGS) $(dir $@)
	@cp $< $(dir $@)

$(OBJECTS): build/%.o: %.cpp
	@echo "[CXX] " $@
	@$(MKDIR) $(MKDIRFLAGS) $(dir $@)
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

$(DEPS): build/%.deps: %.cpp
	@echo "[DEPS]" $@
	@$(MKDIR) $(MKDIRFLAGS) $(dir $@)
	@$(DEPS_BIN) -std=c++11 -MM -MT build/$*.o $< > $@
	@$(DEPS_BIN) -std=c++11 -MM -MT build/$*.deps $< >> $@

$(BIN): bin/%:
	@echo "[LD]  " $@
	@$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIB)

bin/tests: $(foreach obj,$(basename $(wildcard tests/*.cpp)),build/$(obj).o)
	@echo "[LD]  " $@
	@$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIB) -lboost_test_exec_monitor

$(LIB): lib/%:
	@echo "[AR]  " $@
	@$(AR) $(ARFLAGS) $@ $^

deps: $(DEPS)

clean:
	@rm -f $(OBJECTS)
	@rm -f $(DEPS)
	@rm -f $(BIN)
	@rm -rf build/*
	@rm -rf include/*
	@rm -f $(LIB)

install: install-dev
install-dev: install-header install-lib
install-all: install-header install-lib install-bin

install-bin: $(BIN)
ifneq ($(BIN),)
	@echo "[CP]  " $(BIN)
	@$(MKDIR) $(MKDIRFLAGS) $(PREFIX)/$(BIN_DIR)/
	@cp $(BIN) $(PREFIX)/$(BIN_DIR)/
endif

install-header: $(HEADERS)
ifneq ($(HEADERS),)
	@echo "[CP]  " $(HEADERS)
	@$(MKDIR) $(MKDIRFLAGS) $(PREFIX)/$(INCLUDE_DIR)/
	@cp -r include/* $(PREFIX)/$(INCLUDE_DIR)/
endif
install-lib: $(LIB)
ifneq ($(LIB),)
	@echo "[CP]  " $(LIBS)
	@$(MKDIR) $(MKDIRFLAGS) $(PREFIX)/$(LIB_DIR)/
	@cp $(LIB) $(PREFIX)/$(LIB_DIR)/
endif

print-%:
	@echo $*=$($*)
