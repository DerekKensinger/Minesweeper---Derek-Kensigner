#pragma once

#include "wx/wx.h"
#include "wx/frame.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	int nFieldWidth = 10;
	int nFieldHieght = 10;
	wxButton** btn;
	int* nField = nullptr;	
	bool bFirstClick = true;

	void OnButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

