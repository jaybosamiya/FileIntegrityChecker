#include "gui_dialogs.h"
#include "gui_main.h"

#include <iostream> // temp

namespace gui_dialogs {
  bool is_initialization_done = false;
  Gtk::FileChooserDialog *saveIntegrityFileFileChooserDialog, *openFileFileChooserDialog;

  static std::string location;
  static bool is_location_initialized;

  void openFileOpen() {
    location = openFileFileChooserDialog->get_filename();
    is_location_initialized = true;
    openFileFileChooserDialog->hide();
  }

  void openFileCancel() {
    is_location_initialized = false;
    openFileFileChooserDialog->hide();
  }

  void saveIntegrityFileSave() {
    location = saveIntegrityFileFileChooserDialog->get_filename();
    is_location_initialized = true;
    saveIntegrityFileFileChooserDialog->hide();
  }

  void saveIntegrityFileCancel() {
    is_location_initialized = false;
    saveIntegrityFileFileChooserDialog->hide();
  }

  void init() {
    if ( is_initialization_done )
      return;

    using gui_common::builder;

    // Make all the controls
    #define SET_WIDGET(X) builder->get_widget(#X, X)
    SET_WIDGET(saveIntegrityFileFileChooserDialog);
    SET_WIDGET(openFileFileChooserDialog);
    #undef SET_WIDGET
    #define LOCAL_SET_WIDGET(T,X) Gtk::T* X = 0; builder->get_widget(#X, X)
    LOCAL_SET_WIDGET(Button,openFileOpenButton);
    LOCAL_SET_WIDGET(Button,openFileCancelButton);
    LOCAL_SET_WIDGET(Button,saveIntegrityFileSaveButton);
    LOCAL_SET_WIDGET(Button,saveIntegrityFileCancelButton);
    #undef LOCAL_SET_WIDGET

    // Connect the buttons' signals to relevant functions
    #define SET_HANDLER(X) X##Button->signal_clicked().connect(sigc::ptr_fun(&X))
    SET_HANDLER(openFileOpen);
    SET_HANDLER(openFileCancel);
    SET_HANDLER(saveIntegrityFileSave);
    SET_HANDLER(saveIntegrityFileCancel);
    #undef SET_HANDLER

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
