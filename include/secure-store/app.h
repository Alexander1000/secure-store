#ifndef __BASE_H
// Make sure to only declare these classes once
#define __BASE_H

#include <wx/wx.h>

class MainApp: public wxApp // MainApp is the class for our application
{
    // MainApp just acts as a container for the window, or frame in MainFrame
public:
    virtual bool OnInit();
};

class MainFrame: public wxFrame // MainFrame is the class for our window,
{
    // It contains the window and all objects in it
public:
    MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
};

DECLARE_APP(MainApp)

#endif
