#include "gui_dialogs.h"
#include "gui_main.h"

#include <iostream> // temp

namespace gui_dialogs {
  bool is_initialization_done = false;
  Gtk::FileChooserDialog *saveIntegrityFileFileChooserDialog, *openFileFileChooserDialog;

  void init() {
    if ( is_initialization_done )
      return;

    using gui_common::builder;

    // Make all the controls
    #define SET_WIDGET(X) builder->get_widget(#X, X)
    SET_WIDGET(saveIntegrityFileFileChooserDialog);
    SET_WIDGET(openFileFileChooserDialog);
    #undef SET_WIDGET

    is_initialization_done = true;
  }

  int dialog_test() {
//    Gtk::FileChooserDialog x;
//    x.get_filename
    init();
    openFileFileChooserDialog->show();
//    string z = openFileFileChooserDialog->get_filename();
    return 0;
  }

  bool FileOpenDialog::get_location(std::string &loc) {
    if ( this->is_location_initialized )
      return this->location;
    gui_dialogs::is_location_initialized = false;
    openFileFileChooserDialog->show();
    Gtk::FileChooserDialog x;
    x.on_hide()
  }

  bool IntegrityFileOpenDialog::get_location(std::string &loc) {
    return false; // TODO: Write code for this
  }

  bool IntegrityFileSaveDialog::get_location(std::string &loc) {
    return false; // TODO: Write code for this
  }

}
