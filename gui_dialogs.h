#ifndef GUI_DIALOGS_H
#define GUI_DIALOGS_H

#include "gui_main.h"

#include <gtkmm.h>
#include <string>

namespace gui_dialogs {

  class FileDialog : public Gtk::FileChooserDialog {
    private:
      void location_setter(int response_id);
    protected:
      bool is_location_initialized;
      std::string location;
      FileDialog(const Glib::ustring& title, Gtk::FileChooserAction action, const Gtk::StockID& stock_id);
    public:
      bool get_location(std::string &loc); // Returns true iff loc is set (i.e. user does not cancel the dialog)
      void reset_location() { is_location_initialized = false; }
  };

  class FileOpenDialog : public FileDialog {
    public:
      FileOpenDialog(const Glib::ustring& title);
      FileOpenDialog();
  };

  class IntegrityFileOpenDialog : public FileOpenDialog {
    public:
      IntegrityFileOpenDialog();
  };

  class IntegrityFileSaveDialog : public FileDialog {
    public:
      IntegrityFileSaveDialog();
  };

  class MessageDialog : public Gtk::MessageDialog {
    private:
      void dialog_response(int response_id);
    public:
      MessageDialog(Gtk::MessageType msg_type = Gtk::MESSAGE_INFO);
      void show_message(std::string primary, std::string secondary = "");
  };

  void show_help();
  void show_about_dialog();
  void show_that_file(bool is_valid);

}

#endif
