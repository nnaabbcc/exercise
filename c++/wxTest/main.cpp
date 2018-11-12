#include <wx/app.h>
#include <wx/dialog.h>

class GuiApp : public wxApp
{
  public:
    bool OnInit() final
    {
        // Top level window will be free by wxWidgets
        auto gui = new wxDialog(nullptr, wxID_ANY, "wxTest");
        gui->ShowModal();
        return false;
    }
};

IMPLEMENT_APP(GuiApp)