TARGET := main
INCDIR := ./
SRCDIR := ./
BUILDDIR := .build

SRCS = $(TARGET).c


CFLAGS = -O2 -Wall -Wextra -Wpedantic

LDFLAGS =

CC := gcc

.PHONY: all clean tidy

all: $(TARGET) 

$(TARGET): $(BUILDDIR)/$(TARGET)
	cp $< $@

$(BUILDDIR)/$(TARGET): $(addprefix $(BUILDDIR)/,$(SRCS:.c=.o))
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(addprefix $(SRCDIR)/,%.c) $(BUILDDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $(addprefix -I,$(INCDIR)) -c $< -o $@

$(BUILDDIR): 
	mkdir -p $@

clean:
	@echo Cleaning up
	-rm -rf $(BUILDDIR)/*.o

tidy: clean
	-rm -f $(BUILDDIR)/$(TARGET)
	-rm -f $(TARGET)


