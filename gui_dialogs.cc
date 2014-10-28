#include "gui_dialogs.h"
#include "gui_main.h"

namespace gui_dialogs {
  bool is_initialization_done = false;

  void FileDialog::location_setter(int response_id) {
    location = get_filename();
    hide();
    is_location_initialized = (response_id != Gtk::RESPONSE_CANCEL);
  }

  FileDialog::FileDialog(const Glib::ustring& title, Gtk::FileChooserAction action) :
    Gtk::FileChooserDialog(title, action),
    is_location_initialized(false) {
    location = std::string("");
    add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
    signal_response().connect(sigc::mem_fun(*this, &FileDialog::location_setter));
  }

  bool FileDialog::get_location(std::string &loc) {
    if ( this->is_location_initialized ) {
      loc = this->location;
      return true;
    }
    this->run();
    loc = this->location;
    return this->is_location_initialized;
  }

  FileOpenDialog::FileOpenDialog(const Glib::ustring& title) :
    FileDialog(title, Gtk::FILE_CHOOSER_ACTION_OPEN) {}

  FileOpenDialog::FileOpenDialog() :
    FileDialog("Select file", Gtk::FILE_CHOOSER_ACTION_OPEN) {}

  IntegrityFileOpenDialog::IntegrityFileOpenDialog() :
    FileOpenDialog("Select .integrity file") {}

  IntegrityFileSaveDialog::IntegrityFileSaveDialog() :
    FileDialog("Save .integrity file", Gtk::FILE_CHOOSER_ACTION_SAVE) {}

  static Gtk::AboutDialog* aboutDialog = 0;

  static void about_dialog_response(int response_id) {
    if((response_id == Gtk::RESPONSE_CLOSE) ||
        (response_id == Gtk::RESPONSE_CANCEL) )
      aboutDialog->hide();
  }

  void show_about_dialog() {
    gui_common::builder->get_widget("aboutDialog",aboutDialog);
    aboutDialog->signal_response().connect(sigc::ptr_fun(&gui_dialogs::about_dialog_response));
    aboutDialog->run();
  }

}
