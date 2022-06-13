#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Minesweeper - Derek Kensinger", wxPoint(30,30), wxSize(800,600))
{
	btn = new wxButton * [nFieldWidth * nFieldHieght];
	wxGridSizer* grid = new wxGridSizer(nFieldHieght, nFieldHieght, 0, 0);

	nField = new int[nFieldWidth * nFieldHieght];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int x = 0; x < nFieldWidth; x++)
	{
		for (int y = 0; y < nFieldHieght; y++)
		{
			btn[y * nFieldWidth + x] = new wxButton(this, 10000 + (y * nFieldWidth + x));
			btn[y * nFieldWidth + x] ->SetFont(font);
			grid->Add(btn[y * nFieldWidth + x], 1, wxEXPAND | wxALL);

			btn[y * nFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
			nField[y * nFieldWidth + x] = 0;

		}
	}

	this->SetSizer(grid);
	grid->Layout();
}


cMain::~cMain()
{
	delete[] btn;
}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	// Get coordinate of button in field array
	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldWidth;

	if (bFirstClick)
	{
		int mines = 30;

		while (mines)
		{
			int rx = rand() % nFieldWidth;
			int ry = rand() % nFieldHieght;

			if (nField[ry * nFieldWidth + rx] == 0 && rx != x && ry != y)
			{
				nField[ry * nFieldWidth + rx] = -1;
				mines--;
			}
		}

		bFirstClick = false;
	}

	// Disable Button, preventing it being pressed again and creating a new mine field with each click.
	btn[y * nFieldWidth + x]->Enable(false);

	// Check if player hit mine.
	if (nField[y * nFieldWidth + x] == -1)
	{
		wxMessageBox("KABOOOOOOM!!!! - Game Over :( Thanks for playing!");

		//Reset the game.
		bFirstClick = true;
		for  (int x = 0; x < nFieldWidth; x++)
			for (int y = 0; y < nFieldHieght; y++)
			{
				nField[y * nFieldWidth + x] = 0;
				btn[y * nFieldWidth + x]->SetLabel("");
				btn[y * nFieldWidth + x]->Enable(true);
			}
	}
	// The player didn't click on a mine
	else
	{
		// Count the neighboring mines
		int mine_count = 0;
		for (int i = -1; i < 2; i++)
			for (int j = -1; j < 2; j++)
			{
				if (x + i > 0 && x + i < nFieldWidth && y + j >= 0 && y + j < nFieldHieght)
				{
					if (nField[(y + j) * nFieldWidth + (x + i)] == -1)
						mine_count++;
				}
			}

		// Update buttons label to show mine count if > 0.
		if (mine_count > 0)
		{
			btn[y * nFieldWidth + x]->SetLabel(std::to_string(mine_count));
		}

	}

	evt.Skip();
}

