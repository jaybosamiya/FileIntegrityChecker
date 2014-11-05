#
# Makefile for FileIntegrityChecker
#

CC     := g++
CFLAGS := `pkg-config gtkmm-3.0 --cflags`
LIBS   := `pkg-config gtkmm-3.0 --libs`
OBJDIR := obj

vpath %.cc src

objs := $(OBJDIR)/main.o \
				$(OBJDIR)/gui_main.o \
				$(OBJDIR)/gui_dialogs.o \
				$(OBJDIR)/backend/FileReader.o \
				$(OBJDIR)/backend/HashChecker.o \
				$(OBJDIR)/backend/HashGenerator.o \
				$(OBJDIR)/backend/Hash.o \
				$(OBJDIR)/backend/md5.o \
				$(OBJDIR)/backend/sha1.o

IntegrityFileChecker : $(objs) gui/mainWindow.glade
	$(CC) -o IntegrityFileChecker $(objs) $(LIBS)

gui/mainWindow.glade : src/gui/mainWindow.glade
	mkdir -p gui
	cp -f src/gui/mainWindow.glade gui/

$(OBJDIR)/backend/%.o : backend/%.cc | $(OBJDIR)/backend
	$(CC) -c $< -o $@

$(OBJDIR)/%.o : %.cc | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean targz

all : IntegrityFileChecker

clean :
	rm -rf IntegrityFileChecker IntegrityFileChecker.tar.gz $(OBJDIR) gui *~

targz : IntegrityFileChecker
	tar czf IntegrityFileChecker.tar.gz IntegrityFileChecker gui/mainWindow.glade

$(OBJDIR)/backend : $(OBJDIR)
	mkdir -p $(OBJDIR)/backend

$(OBJDIR) :
	mkdir -p $(OBJDIR)
