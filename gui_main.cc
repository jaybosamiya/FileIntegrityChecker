#include "gui_main.h"
#include "gui_dialogs.h"

#include <iostream>

namespace gui_common {
  Glib::RefPtr<Gtk::Builder> builder;
}

namespace button_signal_handler {

  void makeIntegrityFile() {
    std::string location_of_file, location_of_integrity_file;
    gui_dialogs::FileOpenDialog file_open_dialog;
    gui_dialogs::IntegrityFileSaveDialog integrity_file_save_dialog;
    if ( !file_open_dialog.get_location(location_of_file) )
      return;
    if ( !integrity_file_save_dialog.get_location(location_of_integrity_file) )
      return;
    std::cout << location_of_file << '\n' << location_of_integrity_file << '\n' << std::endl; // TODO: Connect to the backend from here
  }

  void testIntegrity() {
    std::string location_of_integrity_file;
    gui_dialogs::IntegrityFileOpenDialog integrity_file_open_dialog;
    if ( !integrity_file_open_dialog.get_location(location_of_integrity_file) )
      return;
    std::cout << location_of_integrity_file << '\n' << std::endl; // TODO: Connect to the backend from here
  }

  void help() {
    std::cout << "H" << std::endl; // TODO: Rewrite
  }

  void about() {
    std::cout << "A" << std::endl; // TODO: Rewrite
  }

}

int run_gui (int argc, char *argv[]) {
  Gtk::Main kit(argc, argv);
  using gui_common::builder;

  // Read the UI file and get all the necessary elements
  try {
    builder = Gtk::Builder::create_from_file(MAIN_WINDOW_UI);
  } catch (const Glib::FileError & ex) {
    std::cerr << ex.what() << std::endl;
    return 1;
  }

  // Make all the controls
  #define SET_WIDGET(T,X) Gtk::T* X = 0; builder->get_widget(#X, X)
  SET_WIDGET(Window,mainWindow);
  SET_WIDGET(Button,makeIntegrityFileButton);
  SET_WIDGET(Button,testIntegrityButton);
  SET_WIDGET(Button,helpButton);
  SET_WIDGET(Button,aboutButton);
  #undef SET_WIDGET

  // Connect the buttons' signals to relevant functions
  #define SET_HANDLER(X) X##Button->signal_clicked().connect(sigc::ptr_fun(&button_signal_handler::X))
  SET_HANDLER(makeIntegrityFile);
  SET_HANDLER(testIntegrity);
  SET_HANDLER(help);
  SET_HANDLER(about);
  #undef SET_HANDLER

  // Start the GUI
  if (mainWindow) {
    kit.run(*mainWindow);
  }

  return 0;
}
