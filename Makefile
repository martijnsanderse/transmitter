
# os specific
CLEANUP=rm -f
MKDIR=mkdir -p
TARGET_EXTENSION=out

# paths
PATHU = ../Unity/src/
PATHS = src/
PATHT = test/
PATHB = build/
PATHD = build/depends/
PATHO = build/objs/
PATHR = build/results/

BUILD_PATHS = $(PATHB) $(PATHD) $(PATHO) $(PATHR)

# sources
SRCT = $(wildcard $(PATHT)*.c)
RELSRC = $(wildcard $(PATHS)*.c)

# toolchain
COMPILE=gcc -c
LINK=gcc
DEPEND=gcc -MM -MG -MF
# compile flags: paths
CFLAGS=-I. -I$(PATHU) -I$(PATHS) 
# compile flags: define test
CFLAGS += -DTEST

# create results by running the executables and pipe output to results
RESULTS = $(patsubst $(PATHT)test%.c,$(PATHR)test%.txt,$(SRCT))

# summarize results
test: $(BUILD_PATHS) $(RESULTS)
	@echo "-----------------------\nIGNORES:\n-----------------------"
	@echo `grep -s IGNORE $(PATHR)*.txt`
	@echo "-----------------------\nFAILURES:\n-----------------------"
	@echo `grep -s FAIL $(PATHR)*.txt`
	@echo "\nDONE"


$(PATHR)%.txt: $(PATHB)%.$(TARGET_EXTENSION)
	-./$< > $@ 2>&1

# create executables
$(PATHB)test%.$(TARGET_EXTENSION): $(PATHO)test%.o $(PATHO)%.o $(PATHU)unity.o $(PATHD)test%.d $(PATHO)mock_ssd1325.o
	$(LINK) -o $@ $^

# create object files
$(PATHO)%.o:: $(PATHT)%.c
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHS)%.c
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHU)%.c $(PATHU)%.h
	$(COMPILE) $(CFLAGS) $< -o $@

# create the dependencies
$(PATHD)%.d:: $(PATHT)%.c
	$(DEPEND) $@ $<

# have make create directories for us
$(PATHB):
	$(MKDIR) $(PATHB)

$(PATHD):
	$(MKDIR) $(PATHD)

$(PATHO):
	$(MKDIR) $(PATHO)

$(PATHR):
	$(MKDIR) $(PATHR)

# cleanup
clean:
	$(CLEANUP) $(PATHO)*.o
	$(CLEANUP) $(PATHB)*.$(TARGET_EXTENSION)
	$(CLEANUP) $(PATHR)*.txt
	$(CLEANUP) $(PATHD)*.d

# keep some results unless explicit call to clean
.PRECIOUS: $(PATHB)test%.$(TARGET_EXTENSION)
.PRECIOUS: $(PATHD)%.d
.PRECIOUS: $(PATHO)%.o
.PRECIOUS: $(PATHR)%.txt

# phonies
.PHONY: clean
.PHONY: test