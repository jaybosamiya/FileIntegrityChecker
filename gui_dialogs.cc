#include "gui_dialogs.h"
#include "gui_main.h"

namespace gui_dialogs {
  bool is_initialization_done = false;

  void Dialog::location_setter(int response_id) {
    location = get_filename();
    hide();
    is_location_initialized = (response_id != Gtk::RESPONSE_CANCEL);
  }

  Dialog::Dialog(const Glib::ustring& title, Gtk::FileChooserAction action) :
    Gtk::FileChooserDialog(title, action),
    is_location_initialized(false) {
    location = std::string("");
    add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
    signal_response().connect(sigc::mem_fun(*this, &Dialog::location_setter));
  }

  bool Dialog::get_location(std::string &loc) {
    if ( this->is_location_initialized ) {
      loc = this->location;
      return true;
    }
    this->run();
    loc = this->location;
    return this->is_location_initialized;
  }

  FileOpenDialog::FileOpenDialog(const Glib::ustring& title) :
    Dialog(title, Gtk::FILE_CHOOSER_ACTION_OPEN) {}

  FileOpenDialog::FileOpenDialog() :
    Dialog("Select file", Gtk::FILE_CHOOSER_ACTION_OPEN) {}

  IntegrityFileOpenDialog::IntegrityFileOpenDialog() :
    FileOpenDialog("Select .integrity file") {}

  IntegrityFileSaveDialog::IntegrityFileSaveDialog() :
    Dialog("Save .integrity file", Gtk::FILE_CHOOSER_ACTION_SAVE) {}

}
