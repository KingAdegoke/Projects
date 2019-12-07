//Samuel Adegoke
//ID 1001541794
#include <gtkmm.h>
#include <iostream>

class MainWindow : public Gtk::Window
{
	public:
		MainWindow()
		{
			set_default_size(700, 600);
			set_title("This is my guessing game!!");
			Gtk::Box *MainVBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
			add(*MainVBox);

			Gtk::MenuBar *HintBar = Gtk::manage(new Gtk::MenuBar());
			MainVBox->pack_start(*HintBar, Gtk::PACK_SHRINK, 0);

			Gtk::MenuItem *Menu = Gtk::manage(new Gtk::MenuItem("Opponent Hints", true));
			HintBar->append(*Menu);
			Gtk::MenuItem *Menu2 = Gtk::manage(new Gtk::MenuItem("Player Hints", true));
			HintBar->append(*Menu2);
			Gtk::MenuItem *Menu3 = Gtk::manage(new Gtk::MenuItem("Miscellaneous Hints", true));
			HintBar->append(*Menu3);


			Gtk::Menu *HintMenu = Gtk::manage(new Gtk::Menu());
			Menu->set_submenu(*HintMenu);
			Gtk::Menu *HintMenu2 = Gtk::manage(new Gtk::Menu());
			Menu2->set_submenu(*HintMenu2);
			Gtk::Menu *HintMenu3 = Gtk::manage(new Gtk::Menu());
			Menu3->set_submenu(*HintMenu3);


			Gtk::MenuItem *Hint = Gtk::manage(new Gtk::MenuItem("Lebron James", true));
			HintMenu->append(*Hint);
			Gtk::MenuItem *Hint2 = Gtk::manage(new Gtk::MenuItem("Kyrie Irving", true));
			HintMenu->append(*Hint2);
			Gtk::MenuItem *Hint3 = Gtk::manage(new Gtk::MenuItem("Kevin Love", true));
			HintMenu->append(*Hint3);


			Gtk::MenuItem *Hint4 = Gtk::manage(new Gtk::MenuItem("Stephen Curry", true));
			HintMenu2->append(*Hint4);
			Gtk::MenuItem *Hint5 = Gtk::manage(new Gtk::MenuItem("Kevin Durant", true));
			HintMenu2->append(*Hint5);
			Gtk::MenuItem *Hint6 = Gtk::manage(new Gtk::MenuItem("Klay Thompson", true));
			HintMenu2->append(*Hint6);

			Gtk::MenuItem *Hint7 = Gtk::manage(new Gtk::MenuItem("Won series 4-1", true));
			HintMenu3->append(*Hint7);
			Gtk::MenuItem *Hint8 = Gtk::manage(new Gtk::MenuItem("Lost previous year in the finals", true));
			HintMenu3->append(*Hint8);
			Gtk::MenuItem *Hint9 = Gtk::manage(new Gtk::MenuItem("3rd consecutive final appearance", true));
			HintMenu3->append(*Hint9);

			Gtk::Label *Question= Gtk::manage(new Gtk::Label("Who won the NBA finals in 2017?"));
			MainVBox->pack_start(*Question);
			Question->set_justify(Gtk::JUSTIFY_CENTER);
			Question->show();

			Gtk::Image *MyImage=Gtk::manage(new Gtk::Image{"2017championss.jpg"});
			MainVBox->pack_start(*MyImage);
			MyImage->show();


			Gtk::Box *horizontal = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0));
			MainVBox->add(*horizontal);

			Gtk::Button *okayButton = Gtk::manage(new Gtk::Button("Okay", Gtk::RESPONSE_OK));
			horizontal->pack_start(*okayButton);

			Gtk::Entry *MyEntry= Gtk::manage(new Gtk::Entry());
			MyEntry->set_text("Enter your guess here");
			horizontal->pack_start(*MyEntry);
			MyEntry->set_max_length(50);
			MyEntry->select_region(0, MyEntry->get_text_length());


			Gtk::Box *horizontal2 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0));
			MainVBox->add(*horizontal2);
			Gtk::Button *cancelButton = Gtk::manage(new Gtk::Button("Cancel", Gtk::RESPONSE_CANCEL));
			cancelButton->set_size_request(293);
			horizontal2->add(*cancelButton);
			MyEntry->grab_focus_without_selecting();
			okayButton->signal_clicked().connect(sigc::bind<Gtk::Entry*>(sigc::mem_fun(*this, &MainWindow::okay_button_click), MyEntry));
			cancelButton->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::cancel_button_click));
			MyEntry->signal_activate().connect(sigc::bind<Gtk::Entry*>(sigc::mem_fun(*this, &MainWindow::okay_button_click), MyEntry));
			MainVBox->show_all();
			
		}

	void okay_button_click (Gtk::Entry *MyEntry)
	{
		std::string guess = MyEntry->get_text();
		std::string answer = "Golden State Warriors";
		if(guess == answer)
		{
			Gtk::MessageDialog Correct{"",false, Gtk::MESSAGE_WARNING,
			Gtk::BUTTONS_OK};
			Correct.set_secondary_text("You Guessed <span fgcolor='#0000ff'>Correctly</span> !!", true);
			Correct.run();
		}
		else
		{
			Gtk::MessageDialog Wrong{"",false, Gtk::MESSAGE_ERROR,
			Gtk::BUTTONS_OK};
			Wrong.set_secondary_text("You Guessed <span fgcolor='#ff0000'>Incorrectly</span> \nPlease Try Again.",true);
			Wrong.run();
		}
	}

	void cancel_button_click ()
	{
		hide();
	}
};


int main (int argc, char *argv[]) 
{
	auto app = Gtk::Application::create(argc, argv, "");
	MainWindow MyWindow;
	app->run(MyWindow);
}