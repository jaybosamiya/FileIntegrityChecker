#include "gui_dialogs.h"
#include "gui_main.h"

namespace gui_dialogs {

  using namespace gui_common;

  void FileDialog::location_setter(int response_id) {
    location = get_filename();
    hide();
    is_location_initialized = (response_id == Gtk::RESPONSE_OK);
  }

  FileDialog::FileDialog(const Glib::ustring& title, Gtk::FileChooserAction action, const Gtk::StockID& stock_id) :
    Gtk::FileChooserDialog(title, action),
    is_location_initialized(false) {
    location = std::string("");
    add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    add_button(stock_id, Gtk::RESPONSE_OK);
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
    FileDialog(title, Gtk::FILE_CHOOSER_ACTION_OPEN, Gtk::Stock::OPEN) {
    this->set_filter(AllFileFilter);
  }

  FileOpenDialog::FileOpenDialog() :
    FileDialog("Select file for checksums", Gtk::FILE_CHOOSER_ACTION_OPEN, Gtk::Stock::OPEN) {
    this->set_filter(AllFileFilter);
  }

  IntegrityFileOpenDialog::IntegrityFileOpenDialog() :
    FileOpenDialog("Select .integrity file") {
    this->set_filter(IntegrityFileFilter);
  }

  IntegrityFileSaveDialog::IntegrityFileSaveDialog() :
    FileDialog("Save .integrity file", Gtk::FILE_CHOOSER_ACTION_SAVE, Gtk::Stock::SAVE) {
    this->set_filter(IntegrityFileFilter);
  }

  void MessageDialog::dialog_response(int response_id) {
    if((response_id == Gtk::RESPONSE_CLOSE) ||
        (response_id == Gtk::RESPONSE_OK) ||
        (response_id == Gtk::RESPONSE_CANCEL) )
      this->hide();
  }

  MessageDialog::MessageDialog(Gtk::MessageType msg_type) : Gtk::MessageDialog("", false, msg_type, Gtk::BUTTONS_OK) {
    set_title("File Integrity Checker");
    signal_response().connect(sigc::mem_fun(*this, &MessageDialog::dialog_response));
  }

  void MessageDialog::show_message(std::string primary, std::string secondary) {
    set_message(primary);
    set_secondary_text(secondary);
    run();
  }

  void show_help() {
    MessageDialog helpMessageDialog(Gtk::MESSAGE_QUESTION);
    helpMessageDialog.show_message("Help","Click on \"Make a .integrity file\" in order to store checksums for the file to be transferred\n\n"
      "Click on \"Test Integrity of File\" in order to verify that no corruption of data has occurred (for example, after file transfer)");
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

  void show_that_file(bool is_valid) {
    if ( is_valid ) {
      MessageDialog validDialog;
      validDialog.show_message("Valid","The file's integrity is uncompromized. You can be assured that the file is exactly as it was when the "
        ".integrity file was made.");
    } else { // Use Gtk::MESSAGE_WARNING 	or Gtk::MESSAGE_ERROR
      MessageDialog invalidDialog(Gtk::MESSAGE_ERROR);
      invalidDialog.show_message("Invalid","The file's integrity is compromized. Either the .integrity file, or the actual file itself have "
        "differences from when thay were first made.\nWe suggest that you should retry transfering the file and it's .integrity file.");
    }
  }

}
