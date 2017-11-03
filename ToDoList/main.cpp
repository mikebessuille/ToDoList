// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "ListPanel.h"
#include "ControlIDs.h"

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnAddButton(wxCommandEvent& event);


private:
	void CreateMenu();

// member variables
private:
	ListPanel *m_ListPanel;
	wxPanel *m_BottomPanel;
	wxButton *m_AddButton;

private:
	wxDECLARE_EVENT_TABLE();
};

enum
{
	ID_Hello = 1
};



wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_MENU(ID_Hello, MyFrame::OnHello)
	EVT_MENU(wxID_EXIT, MyFrame::OnExit)
	EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
	EVT_BUTTON(ID_ADDBUTTON, MyFrame::OnAddButton)
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	// TODO: Read the size from the settings file.
	MyFrame *frame = new MyFrame("Hello World", wxPoint(50, 50), wxSize(450, 340));
	frame->Show(true);
	return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	CreateMenu();
	SetMinSize(wxSize(350, 350)); // Of the whole MyFrame (which contains the whole app)

	// The ListPanel which contains all the ToDoItems
	m_ListPanel = new ListPanel(this);
	m_ListPanel->SetMinSize(wxSize(-1, 280)); // -1 means unspecified (use default).  Height should be based on size of each TodoItem

	
	// Create a bottom window / panel, with an "Add" button
	m_BottomPanel = new wxPanel(this);
	wxButton *m_AddButton = new wxButton(m_BottomPanel, ID_ADDBUTTON, wxT("Add"));
	

	// Add the ListPanel and bottom panel into a new vertical sizer 
	// Flags: Vertically not stretchable (0 to constructor)
	// Horizontally stretchable (Expand())
	// Left-aligned
	// with border width 5.
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(m_ListPanel, wxSizerFlags(1).Left().Expand()); // No Border
	sizer->Add(m_BottomPanel, wxSizerFlags(0).Left().Border(wxALL, 5)); // Cannot expand vertically or horizontally
	sizer->SetSizeHints(this); // Should never resize smaller than the initial window... ?
	SetSizer(sizer); // use the sizer for layout
}

void MyFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("This is a wxWidgets' Hello world sample",
		"About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent& event)
{
	wxLogMessage("Hello world from wxWidgets!");
}


void MyFrame::CreateMenu()
{
	wxMenu *menuFile = new wxMenu;
	menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
		"Help string shown in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);
	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");
	SetMenuBar(menuBar);
	/*
	CreateStatusBar();
	SetStatusText("Welcome to wxWidgets!");
	*/
}

void MyFrame::OnAddButton(wxCommandEvent& event)
{
	// TODO: Bring up a dialogue box to enter the text.
	// TODO: Modify AddItem() to take a string!!!
	// TODO: Modify ToDoItem() to take a string, and not generate fake text data!!!
	
	m_ListPanel->AddItem();
}
