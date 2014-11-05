CC     := g++
CFLAGS := `pkg-config gtkmm-3.0 --cflags`
LIBS   := `pkg-config gtkmm-3.0 --libs`
OBJDIR    := obj

objs   := $(OBJDIR)/main.o \
				$(OBJDIR)/gui_main.o \
				$(OBJDIR)/gui_dialogs.o \
				$(OBJDIR)/backend/FileReader.o \
				$(OBJDIR)/backend/HashChecker.o \
				$(OBJDIR)/backend/HashGenerator.o \
				$(OBJDIR)/backend/Hash.o \
				$(OBJDIR)/backend/md5.o \
				$(OBJDIR)/backend/sha1.o

IntegrityFileChecker : $(objs)
	$(CC) -o IntegrityFileChecker $(objs) $(LIBS)

$(OBJDIR)/backend/%.o : backend/%.cc | $(OBJDIR)/backend
	$(CC) -c $< -o $@

$(OBJDIR)/%.o : %.cc | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean

all : IntegrityFileChecker

clean :
	rm -f *~
	rm -rf $(OBJDIR)

$(OBJDIR)/backend : $(OBJDIR)
	mkdir -p $(OBJDIR)/backend

$(OBJDIR) :
	mkdir -p $(OBJDIR)
