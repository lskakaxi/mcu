# Makefile for sdcc
# modified by shuox.liu@gmail.com
# Date: 2013-07-27 22:25

CC=sdcc
OUTDIR=out/
CFLAGS := -mmcs51
ifdef DEBUG
  CFLAGS += --debug
endif

except_main_srcs := $(filter-out main.c,$(wildcard *.c))  
except_main_objs := $(addprefix $(OUTDIR),$(subst .c,.rel,$(except_main_srcs)))

$(OUTDIR)%.rel: %.c
	$(CC) -o $(OUTDIR) ${CFLAGS} -c $<

all: gen_out ${except_main_objs}
	@echo OBJS except main: ${except_main_objs}
	$(CC) -o $(OUTDIR) ${CFLAGS} main.c ${except_main_objs}

gen_out:
	mkdir -p $(OUTDIR)

hex:
	packihx '$(wildcard $(OUTDIR)*.ihx)' > '$(patsubst %.ihx,%.hex,$(wildcard $(OUTDIR)*.ihx))'  

program: hex
	sudo avrdude -p 8052 -c usbasp -e -U flash:w:'./$(wildcard $(OUTDIR)*.ihx)'  

.PHONY: clean  
clean:
	@rm -rf out
	@rm -f *.bak
	@rm -f *.rel
	@rm -f *.asm
	@rm -f *.lst
	@rm -f *.sym
	@rm -f *.map
	@rm -f *.lnk
	@rm -f *.mem
	@rm -f *.i
	@rm -f *.d
	@rm -f *.rst
	@rm -f *.ihx
	@rm -f *.lk
	@echo clean.
