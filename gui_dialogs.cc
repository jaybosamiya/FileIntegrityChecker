#include "gui_dialogs.h"
#include "gui_main.h"

namespace gui_dialogs {

  using namespace gui_common;

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
    FileDialog(title, Gtk::FILE_CHOOSER_ACTION_OPEN) {
    this->set_filter(AllFileFilter);
    add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
  }

  FileOpenDialog::FileOpenDialog() :
    FileDialog("Select file to make checksums for", Gtk::FILE_CHOOSER_ACTION_OPEN) {
    this->set_filter(AllFileFilter);
    add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
  }

  IntegrityFileOpenDialog::IntegrityFileOpenDialog() :
    FileOpenDialog("Select .integrity file") {
    this->set_filter(IntegrityFileFilter);
  }

  IntegrityFileSaveDialog::IntegrityFileSaveDialog() :
    FileDialog("Save .integrity file", Gtk::FILE_CHOOSER_ACTION_SAVE) {
    this->set_filter(IntegrityFileFilter);
    add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);
  }

  static Gtk::MessageDialog* helpMessageDialog = 0;

  static void help_message_dialog_response(int response_id) {
    if((response_id == Gtk::RESPONSE_CLOSE) ||
        (response_id == Gtk::RESPONSE_OK) ||
        (response_id == Gtk::RESPONSE_CANCEL) )
      helpMessageDialog->hide();
  }

  void show_help() {
    builder->get_widget("helpMessageDialog",helpMessageDialog);
    helpMessageDialog->signal_response().connect(sigc::ptr_fun(&gui_dialogs::help_message_dialog_response));
    helpMessageDialog->run();
  }

  static Gtk::AboutDialog* aboutDialog = 0;

  static void about_dialog_response(int response_id) {
    if((response_id == Gtk::RESPONSE_CLOSE) ||
        (response_id == Gtk::RESPONSE_CANCEL) )
      aboutDialog->hide();
  }

  void show_about_dialog() {
    builder->get_widget("aboutDialog",aboutDialog);
    aboutDialog->signal_response().connect(sigc::ptr_fun(&gui_dialogs::about_dialog_response));
    aboutDialog->run();
  }

}
