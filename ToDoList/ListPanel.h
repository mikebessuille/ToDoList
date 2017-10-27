#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <memory>
#include <vector>
#include "ToDoItem.h"

using namespace std;

// class ListPanel :  public wxPanel
class ListPanel : public wxScrolledWindow
{
public:
	ListPanel(wxFrame *frame, int x = -1, int y = -1, int w = -1, int h = -1);
	virtual ~ListPanel();

	void OnIdle(wxIdleEvent &event);


// Controls
private:
	vector<shared_ptr<ToDoItem>> m_Items;

	wxDECLARE_EVENT_TABLE();

};

