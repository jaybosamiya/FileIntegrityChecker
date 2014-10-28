#ifndef GUI_DIALOGS_H
#define GUI_DIALOGS_H

#include <string>

namespace gui_dialogs {
  int dialog_test();

  class Dialog {
    protected:
      bool is_location_initialized;
      std::string location;
    public:
      Dialog() : is_location_initialized(false) {}
      virtual bool get_location(std::string &loc) = 0; // Returns true iff loc is set (i.e. user does not cancel the dialog)
      void reset_location() { is_location_initialized = false; }
  };

  class FileOpenDialog : public Dialog {
    public:
      bool get_location(std::string &loc);
  };

  class IntegrityFileOpenDialog : public FileOpenDialog {
    public:
      bool get_location(std::string &loc);
  };

  class IntegrityFileSaveDialog : public Dialog {
    public:
      bool get_location(std::string &loc);
  };
}

#endif
