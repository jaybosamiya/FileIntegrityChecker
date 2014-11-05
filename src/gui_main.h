#ifndef GUI_MAIN_H
#define GUI_MAIN_H

#include <gtkmm.h>

#define MAIN_WINDOW_UI "gui/mainWindow.glade"

namespace gui_common {
  extern Glib::RefPtr<Gtk::Builder> builder;
  extern Glib::RefPtr<Gtk::FileFilter> IntegrityFileFilter, AllFileFilter;
}

int run_gui (int argc, char *argv[]);

#endif
