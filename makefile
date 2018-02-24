NAME = lesson8
ofiles := $(NAME) reset asm4c \
  pentlyc pentlysound pentlymusic Foothills-fixed

#CC65_BIN = ../bin/
CC65_BIN:=
EMU:=fceux
DEBUGEMU:=~/.wine/drive_c/Program\ Files\ \(x86\)/FCEUX/fceux.exe

# Comment these out to disable automatic translation of the .ftm
# to a Pently score
FAMITRACKER:=C:/Users/Adrian/Downloads/FamiTracker-v0.4.6/famitracker.exe
FT2P:=../audio/ft2p

ifdef COMSPEC
  # these lines run on Windows
  RM:=del
  PY:=py -3
  # Because ca65 for Windows can find the asminc directory relative
  # to the directory containing ca65.exe, do not warn about CC65_HOME
else
  # these lines run on Linux, FreeBSD, and macOS
  RM:=rm
  PY:=py -3
  ifndef CC65_HOME
    $(error CC65_HOME is not set; it should be the parent directory of asminc)
  endif
endif

.PHONY: clean dist

CC65:=$(CC65_BIN)cc65
CA65:=$(CC65_BIN)ca65
LD65:=$(CC65_BIN)ld65
CC65FLAGS:=-Oi --add-source
srcdir:=src
objdir:=obj/nes

# Linking
$(NAME).nes: nes.cfg $(foreach o,$(ofiles),$(objdir)/$(o).o)
	$(LD65) -o $@ -C $^ nes.lib
	@echo $(NAME).nes created

# Compiling C for 6502
$(objdir)/%.s: $(srcdir)/%.c $(srcdir)/DEFINE.c
	$(CC65) $(CC65FLAGS) $< -o $@

# Assembling
$(objdir)/%.o: $(objdir)/%.s
	$(CA65) $< -o $@

$(objdir)/%.o: $(srcdir)/%.s
	$(CA65) $< -o $@

# Files that other files include
$(objdir)/pentlyc.o $(objdir)/pentlysound.o $(objdir)/pentlymusic.o: \
  $(srcdir)/pently.inc $(srcdir)/pentlyconfig.inc

$(objdir)/pentlymusic.o: $(objdir)/pentlybss.inc

# Lookup table generation
$(objdir)/pentlybss.inc: tools/mkrammap.py $(srcdir)/pentlyconfig.inc
	$(PY) $^ pentlymusicbase -o $@

# Audio conversion
ifdef FT2P
$(objdir)/%.txt: audio/%.ftm
	$(FAMITRACKER) $< -export $@
$(srcdir)/%.pently: $(objdir)/%.txt audio/sfx.pently
	$(FT2P) -i $< -o $@
endif
$(objdir)/%.s: tools/pentlyas.py audio/%.pently
	$(PY) $^ -o $@ --periods 76

# Housekeeping
clean:
	-$(RM) $(NAME).nes
	-$(RM) $(objdir)/*.o
	-$(RM) $(objdir)/*.s

# Packaging
dist: $(NAME).zip
$(NAME).zip: zip.in $(NAME).nes
	zip -9 -u $@ -@ < $<