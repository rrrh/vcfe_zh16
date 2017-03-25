# sh@sighup.ch

OUTFILE := rom.smc
LDCONFIG := snes.cfg

AS := ca65
CC := cc65
LD := cl65

SPC700AS := dosbox -conf tools/tasm/dosbox.conf 2>&1 > /dev/null

ASFLAGS := -sir -g
CFLAGS := -Osir -g -I include --cpu 65c02 
LDFLAGS := 


MAPFILE := out/linker.map

OBJECTS := 	out/startup.o 			\
			out/snes_funcs.o	\
			out/ExhibitView.o 	\
			out/StartScreen.o 	\
			out/DemoView.o 		\
			out/timeline.o		\
			out/core.o 		\
			out/vcfe_scroller.o 	\
            out/sndutils.o     			\
			out/utils.o		\
			out/data.o		\
			out/data_e.o		\
			out/exibits.o		\
			out/hdr.o			
						
			 			
	
.PHONY:	snd data
	
all: snd $(OBJECTS) 
	$(LD) $(LDFLAGS) -m $(MAPFILE) -C $(LDCONFIG) -o out/$(OUTFILE) $(OBJECTS)
	ucon64 -smc -o out/ --chk -nbak out/$(OUTFILE) 

snd:
	@echo $(PATH) moin moin...
	#$(SPC700AS)

data: out/data.o out/exibits.o
	
out/%.o: data/%.s
	$(AS) $(ASFLAGS) -g -o $@ $<
	 
out/%.o: data/exibits/%.s
	$(AS) $(ASFLAGS) -g -o $@ $<
	 
out/%.o: src/%.s
	$(AS) $(ASFLAGS) -g -o $@ $<

out/%.o: lib/%.s
	$(AS) $(ASFLAGS) -g -o $@ $< 
	
out/%.s: src/%.c 
	$(CC) $(CFLAGS) -g -o $@ $<

out/%.s: src/slices/%.c
	$(CC) $(CFLAGS) -g -o $@ $<
	
out/%.o: out/%.s
	exit
	$(AS) $(ASFLAGS) -g -o $@ $<	

clean: snd_clean
	rm -f out/*

snd_clean:
	rm -f snd/*.{LST,OBJ}
