/* Change-Log:
		- Added border UI when user data is full in register function
		- Added minimum username length is >= 3 in register function
		- Added minimum password length is >= 8 in register function
		- Added Symbol & Number Checker Algorithms for register username
		- Removed MENU2 in register function
		- Removed MENU2 in login function
		- Renamed dashboard to Home Page
		- Removed '+' symbol in Home Page UI
		- Renamed 'List Movie' to 'Movies List'
		- Renamed 'List Ticket' to 'Ticket List'
		- Renamed Film to Movie
		- Renamed all Back input
		- Edited capitalize text
		- Add direction route menu in Order Details Page
		- Add some Comment for Information about the Code
		- Rename All Function
		- Fix Dot in Price
		- Fix bugs notification in function regisPage()
		- Add notification when exit
		- Error Handle Input
		- Add Notificator
		- Remove some useless variable
		- Add # for cancel

*/
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <fstream>

using namespace std;

/************ Prototype Function ************/

// Prototype function for Page
void mainPage();
void homePage(int userIndex);
void listMoviesPage(int userIndex);
void moviesDetailsPage(int movieIndex, int userIndex);
void cityListPage(int movieIndex, int userIndex);
void cinemaListPage(int movieIndex, int userIndex, int cityIndex);
void dateListPage(int movieIndex, int userIndex, int cityIndex, int mallIndex);
void timeListPage(int movieIndex, int userIndex, int cityIndex, int mallIndex, int dateIndex);
void orderDetailsPage(int userIndex, int movieIndex, int cityIndex, int mallIndex, int dateIndex, int timeIndex);
void ticketAmmountPage(int userIndex, int movieIndex, int cityIndex, int mallIndex, int dateIndex, int timeIndex);
void purchasedSuccessPage(int userIndex, int movieIndex, int cityIndex, int mallIndex, int dateIndex, int timeIndex, int ammount, string seat[], int tokenIndex);

// Prototype Function for Algorithms
void fillData();
void notificator(string text, int color, int borderLen, int parentLen, bool isContinue = true);
string insertDotPrice(int price);
string tokenGenerator();
void printTicket(int userIndex, int movieIndex, int cityIndex, int mallIndex, int dateIndex, int timeIndex, int ammount, string seat[], int tokenIndex, string email);
void loadingToken(int userIndex, int movieIndex, int cityIndex, int mallIndex, int dateIndex, int timeIndex, int ammount, string seat[]);
bool symbolCheck(string text);
//////////////////////////////////////////////



/************ Object & Variables ************/

// Accounts Array Data
string userId[10] = {"admin", "Test"};
string password[10] = {"admin", "Test"};

// Struct for UI
struct UI{
	string borderUI;
	string screenUI;
};

// Struct for Cinema Data
struct Cinema{
	string city[5] = {"Bekasi", "Jakarta", "Bandung", "Surabaya", "Depok"};

	string mall[5][5] = {
		{
			"Summarecon Mall Bekasi", 
			"Mega Bekasi", 
			"Mall Metropolitan", 
			"Bekasi Cyber Park", 
			"Grand Galaxy Park"
		},
		{
			"Plaza Senayan", 
			"Grand Indonesia", 
			"Mangga Dua Square", 
			"Djakarta Theater", 
			"Plaza Indonesia"
		},
		{
			"Ciwalk Mall", 
			"Braga Mall", 
			"Paris Van Java Mall", 
			"BEC Mall", 
			"Istana Plaza"
		},
		{
			"Pakuwon City",
			"Ciputra World",
			"Grand City",
			"Maspion Square",
			"Marvell City"
		},
		{
			"Depok Town Square",
			"Trans Studio Mall",
			"Depok Mall",
			"The Park Sawangan Mall",
			"Pesona Depok Timur Mall"
		}
	};

	string mallRoute[5][5] = {
		{
			
				"https://tinyurl.com/UKTix-Map-1-0",
				"https://tinyurl.com/UKTix-Map-2-0",
				"https://tinyurl.com/UKTix-Map-3-0",
				"https://tinyurl.com/UKTix-Map-4-0",
				"https://tinyurl.com/UKTix-Map-5-1"
			
		},
		{
			
				"https://tinyurl.com/UKTix-Map-6-1",
				"https://tinyurl.com/UKTix-Map-7-1",
				"https://tinyurl.com/UKTix-Map-8-0",
				"https://tinyurl.com/UKTix-Map-9-1",
				"https://tinyurl.com/UKTix-Map-10-1"
			
		},
		{
			
				"https://tinyurl.com/UKTix-Map-11-1",
				"https://tinyurl.com/UKTix-Map-12-0",
				"https://tinyurl.com/UKTix-Map-13-0",
				"https://tinyurl.com/UKTix-Map-14-0",
				"https://tinyurl.com/UKTix-Map-15-0"
			
		},
		{
			
				"https://tinyurl.com/UKTix-Map-16-0",
				"https://tinyurl.com/UKTix-Map-17-0",
				"https://tinyurl.com/UKTix-Map-18-0",
				"https://tinyurl.com/UKTix-Map-19-0",
				"https://tinyurl.com/UKTix-Map-20-0"
			
		},
		{
			
				"https://tinyurl.com/UKTix-Map-21-0",
				"https://tinyurl.com/UKTix-Map-22-0",
				"https://tinyurl.com/UKTix-Map-23-0",
				"https://tinyurl.com/UKTix-Map-24-0",
				"https://tinyurl.com/UKTix-Map-25-1"
			
		}
	};

	string date[5] = {"21 December 2021", "22 December 2021", "23 December 2021", "24 December 2021", "25 December 2021"};

	string time[5] = {"11:00", "13:15", "15:30", "18:45", "21:00"};

	string theater[5][5][5][5][4][11][9][2];

	string tokenUser[10][5];
	string tokenDetails[10][5][8];
};

// Struct for movies details
struct Movie{
	string title[30] = {"NO TIME TO DIE", "SHANG-CHI", "DUNE", "ETERNALS"};
	string genre [30] = {"Action, Adventure, Thriller", "Action, Adventure, Fantasy", "Adventure, Drama, Sci-fi", "Action, Adventure, Drama"};
	string synopsis[30] = {
		// No Time To Die
		"James Bond has left  active  service.\n            His peace is  short-lived  when Felix\n            Leather, an old friend  from the CIA,\n            turns  up  asking  for  help, leading\n            Bond onto  the  trail of a mysterious\n            villain   armed  with  dangerous  new\n            technology",
		// Shang-Chi
		"Shang-Chi,  the  master  of  weaponry\n            based Kung Fu, is  forced to confront\n            his past after being  drawn  into Ten\n            Rings organization",
		// DUNE
		"Feature adaptation of Frank Herbert's\n            science fiction  novel, about the son\n            of a noble family  entrusted with the\n            protection of the most valuable asset\n            and most vital  element in the galaxy",
		// ETERNALS
		"The saga of  the  eternals, a race of\n            immortal being who lived on Earth and\n            shaped its  history and civilizations"
	};
	string duration[30] = {"163 Minutes", "132 Minutes", "155 Minutes", "156 Minutes"};
	string director[30] = {"Cary Joji Fukunaga", "Destin Daniel Cretton", "Denis Villeneuve", "Chloe Zhao"};
	string trailer[30] = {"https://www.youtube.com/watch?v=BIhNsAtPbPI", "https://www.youtube.com/watch?v=8YjFbMbfXaQ", "https://www.youtube.com/watch?v=n9xhJrPXop4", "https://www.youtube.com/watch?v=x_me3xsvDgk"};
	string rating[30] = {"13+", "All Ages", "All Ages", "13+"};
	int price[30] = {35000, 36000, 37000, 38000};
};

// Declared a Class
UI ui;
Movie movie;
Cinema cinema;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

//////////////////////////////////////////////



/**************** UKTix Page ****************/

void inputEmailPage(int userIndex, int movieIndex, int cityIndex, int mallIndex, int dateIndex, int timeIndex, int ammount, string seat[], int tokenIndex) {
	// Variables
	string email;
	
	system("CLS");
	cout << ui.borderUI << endl;
	cout << "                  UKTix - Login" << endl;
	cout << ui.borderUI << endl;
	cout << "Type \'#\' for cancel" << endl;
	cout << "Input your email: ";
	getline(cin, email);

	printTicket(userIndex, movieIndex, cityIndex, mallIndex, dateIndex, timeIndex, ammount, seat, tokenIndex, email);
	cout << "Loading..." << endl;
	system("bin\\UKTix-SMTP.exe");
	getch();
	purchasedSuccessPage(userIndex, movieIndex, cityIndex, mallIndex, dateIndex, timeIndex, ammount, seat, tokenIndex);
	return;
}

// The page when user successfully bought a ticket
void purchasedSuccessPage(int userIndex, int movieIndex, int cityIndex, int mallIndex, int dateIndex, int timeIndex, int ammount, string seat[], int tokenIndex) {
	// Variables
	string input;
	string strTotal = insertDotPrice(movie.price[movieIndex] * ammount);
    string strPrice = insertDotPrice(movie.price[movieIndex]);

	// Set Seats
    for(int i = 0; i < ammount; i++) {
		for(int j = 0; j < 11; j++) {
            for(int k = 0; k < 9; k++) {
				if(cinema.theater[cityIndex][mallIndex][dateIndex][timeIndex][movieIndex][j][k][0] == seat[i]) {
					cinema.theater[cityIndex][mallIndex][dateIndex][timeIndex][movieIndex][j][k][1] = "true";
				}
			}
		}
	}
	
	// Display
    system("CLS");
	cout << ui.borderUI << endl;
    cout << "                      UKTix" << endl;
    cout << "     You've susccessfull purchased a ticket!" << endl;
    cout << "                 Token: ";
	SetConsoleTextAttribute(h, 10);
	cout << cinema.tokenUser[userIndex][tokenIndex] << endl;
	SetConsoleTextAttribute(h, 7);
	cout << "       (Don't share this token to anyone)" << endl;
	cout << ui.borderUI << endl << endl;
    cout << " Movie       : " << movie.title[movieIndex] << endl << endl;
    cout << " Location    : " << cinema.mall[cityIndex][mallIndex] << " | " << cinema.city[cityIndex] << endl << endl;
    cout << " Date        : " << cinema.date[dateIndex] << endl << endl;
    cout << " Time        : " << cinema.time[timeIndex] << endl << endl;
    cout << " Price       : Rp " << strPrice << endl << endl;
    cout << " Ammount     : " << ammount << endl << endl;
    cout << " Seat        : ";
    for(int i = 0; i < ammount; i++) {
        cout << seat[i] << " ";
    }
    cout << endl << endl;
    cout << " Total Price : Rp " << strTotal << endl << endl;
    cout << ui.borderUI << endl << endl;
	cout << " [1] Direction route to the " << cinema.mall[cityIndex][mallIndex] << endl;
	cout << " [2] Send Ticket to My Email" << endl;
	cout << " [0] Back to Home Page" << endl << endl;
	cout << " Choose Menu : ";

	// Input Condition
	getline(cin, input);
	if(input == "1") {
		ShellExecute(NULL, "open", cinema.mallRoute[cityIndex][mallIndex].c_str(), NULL, NULL, SW_SHOWNORMAL);
		purchasedSuccessPage(userIndex, movieIndex, cityIndex, mallIndex, dateIndex, timeIndex, ammount, seat, tokenIndex);
		return;
	} else if(input == "2") {
		inputEmailPage(userIndex, movieIndex, cityIndex, mallIndex, dateIndex, timeIndex, ammount, seat, tokenIndex);
		return;
	} else if(input == "0") {
		homePage(userIndex);
		return;
	} else {
		notificator("Menu not found", 2, 38, 50);
		purchasedSuccessPage(userIndex, movieIndex, cityIndex, mallIndex, dateIndex, timeIndex, ammount, seat, tokenIndex);
		return;
	}
}

// List page of Payment Method
void paymentsMethodListPage(int userIndex, int movieIndex, int cityIndex, int mallIndex, int dateIndex, int timeIndex, int ammount, string seat[]) {
	// Variables
	string input;
    string strPrice = insertDotPrice(movie.price[movieIndex]);
	string strTotal = insertDotPrice(movie.price[movieIndex] * ammount);

	// Display
    system("CLS");
	cout << ui.borderUI << endl;
    cout << "                  UKTix - Payments" << endl;
    cout << ui.borderUI << endl << endl;
    cout << " Movie       : " << movie.title[movieIndex] << endl << endl;
    cout << " Location    : " << cinema.mall[cityIndex][mallIndex] << " | " << cinema.city[cityIndex] << endl << endl;
    cout << " Date        : " << cinema.date[dateIndex] << endl << endl;
    cout << " Time        : " << cinema.time[timeIndex] << endl << endl;
    cout << " Price       : Rp " << strPrice << endl << endl;
    cout << " Ammount     : " << ammount << endl << endl;
    cout << " Seat        : ";
    for(int i = 0; i < ammount; i++) {
        cout << seat[i] << " ";
    }
    cout << endl << endl;
    cout << " Total Price : Rp " << strTotal << endl << endl;
    cout << ui.borderUI << endl;
	cout << " [1] GoPay" << endl;
	cout << " [2] DANA" << endl;
	cout << " [3] OVO" << endl;
	cout << endl << " [0] BACK TO ORDER DETAILS" << endl << endl;
	cout << " Choose Payments Method : ";

	// Input Condition
	getline(cin, input);
	if(input == "1" || input == "2" || input == "3") {
		loadingToken(userIndex, movieIndex, cityIndex, mallIndex, dateIndex, timeIndex, ammount, seat);
		return;
	} else if(input == "0") {
		orderDetailsPage(userIndex, movieIndex, cityIndex, mallIndex, dateIndex, timeIndex);
		return;
	} else {
		notificator("Menu not found", 2, 38, 50);
		paymentsMethodListPage(userIndex, movieIndex, cityIndex, mallIndex, dateIndex, timeIndex, ammount, seat);
	}
}

// Choose a seat for the user
void chooseSeatPage(int userIndex, int movieIndex, int cityIndex, int mallIndex, int dateIndex, int timeIndex, int ammount) {
    // Variables
    string input;
	int inputCount = 0;
	string seat[ammount];

	// Seats Algorithms
	while(true) {
		if(inputCount < ammount) {
			// Display when Choosing Seats
			system("cls");
			cout << ui.borderUI << endl;
			cout << "                    Seat List" << endl;
			cout << ui.borderUI << endl << endl;
			for(int i = 0; i < 11; i++) {
				cout << "  ";
				for(int j = 0; j < 9; j++) {
					if(cinema.theater[cityIndex][mallIndex][dateIndex][timeIndex][movieIndex][i][j][1] == "true") {
						cout << " [";
						SetConsoleTextAttribute(h, 12);
						cout << cinema.theater[cityIndex][mallIndex][dateIndex][timeIndex][movieIndex][i][j][0];
						SetConsoleTextAttribute(h, 7);
						cout << "]";
					} else if(cinema.theater[cityIndex][mallIndex][dateIndex][timeIndex][movieIndex][i][j][1] == "false") {
						for(int k = 0; k < ammount; k++) {
							if(cinema.theater[cityIndex][mallIndex][dateIndex][timeIndex][movieIndex][i][j][0] == seat[k]) {
								cout << " [";
								SetConsoleTextAttribute(h, 10);
								cout << cinema.theater[cityIndex][mallIndex][dateIndex][timeIndex][movieIndex][i][j][0];
								SetConsoleTextAttribute(h, 7);
								cout << "]";
								break;
							}
							if(k == (ammount -1)) {
								cout << " [" << cinema.theater[cityIndex][mallIndex][dateIndex][timeIndex][movieIndex][i][j][0] << "]";							
							}
						}
					}
				}
				cout << endl;
			}
			cout << endl;
			cout << ui.screenUI << endl;
			cout << ui.borderUI << endl;
			cout << " [A1] = Seat Available" << endl;
			cout << " [";
			SetConsoleTextAttribute(h, 12);
			cout << "A1";
			SetConsoleTextAttribute(h, 7);
			cout << "] = Seat Not Available" << endl;
			cout << " [";
			SetConsoleTextAttribute(h, 10);
			cout << "A1";
			SetConsoleTextAttribute(h, 7);
			cout << "] = Choosed Seat" << endl << endl;
			cout << "Type \'#\' for cancel" << endl;
			cout << " Choose a Seat: ";
			// Input Condition
			getline(cin, input);
			if(input == "#") {
				ticketAmmountPage(userIndex, movieIndex, cityIndex, mallIndex, dateIndex, timeIndex);
				return;
			}
			for(int i = 0; i < 11; i++) {
				for(int j = 0; j < 9; j++) {
					if(cinema.theater[cityIndex][mallIndex][dateIndex][timeIndex][movieIndex][i][j][0] == input) {
						for(int k = 0; k < ammount; k++) {
							if(cinema.theater[cityIndex][mallIndex][dateIndex][timeIndex][movieIndex][i][j][0] == seat[k]) {
								notificator("Choosed seat not available", 2, 38, 50);
								i = 11;
								j = 9;
								break;
							} else {
								if(cinema.theater[cityIndex][mallIndex][dateIndex][timeIndex][movieIndex][i][j][1] == "true") {
									notificator("Choosed seat not available", 2, 38, 50);
									i = 11;
									j = 9;
									break;
								} else {
									if(seat[k] == "") {
										seat[k] = input;
										notificator("Successfully choosed a seat", 1, 38, 50);
										inputCount++;
										i = 11;
										j = 9;
										break;
									}
								}
							}
						}
					}
					if(i == 10 && j == 8) {
						notificator("Choosed seat not available", 2, 38, 50);
						i = 11;
						break;
					}
				}
			}
		} else {
			// Display after Choosed Seats
			system("cls");
			cout << ui.borderUI << endl;
			cout << "                    Seat List" << endl;
			cout << ui.borderUI << endl << endl;
			for(int i = 0; i < 11; i++) {
				cout << "  ";
				for(int j = 0; j < 9; j++) {
					if(cinema.theater[cityIndex][mallIndex][dateIndex][timeIndex][movieIndex][i][j][1] == "true") {
						cout << " [";
						SetConsoleTextAttribute(h, 12);
						cout << cinema.theater[cityIndex][mallIndex][dateIndex][timeIndex][movieIndex][i][j][0];
						SetConsoleTextAttribute(h, 7);
						cout << "]";
					} else if(cinema.theater[cityIndex][mallIndex][dateIndex][timeIndex][movieIndex][i][j][1] == "false") {
						for(int k = 0; k < ammount; k++) {
							if(cinema.theater[cityIndex][mallIndex][dateIndex][timeIndex][movieIndex][i][j][0] == seat[k]) {
								cout << " [";
								SetConsoleTextAttribute(h, 10);
								cout << cinema.theater[cityIndex][mallIndex][dateIndex][timeIndex][movieIndex][i][j][0];
								SetConsoleTextAttribute(h, 7);
								cout << "]";
								break;
							}
							if(k == (ammount - 1)) {
								cout << " [" << cinema.theater[cityIndex][mallIndex][dateIndex][timeIndex][movieIndex][i][j][0] << "]";
							}
						}
					}
				}
				cout << endl;
			}
			cout << endl;
			cout << ui.screenUI << endl;
			cout << ui.borderUI << endl;
			cout << " [A1] = Seat Available" << endl;
			cout << " [";
			SetConsoleTextAttribute(h, 12);
			cout << "A1";
			SetConsoleTextAttribute(h, 7);
			cout << "] = Seat Not Available" << endl;
			cout << " [";
			SetConsoleTextAttribute(h, 10);
			cout << "A1";
			SetConsoleTextAttribute(h, 7);
			cout << "] = Choosed Seat" << endl << endl;
			notificator("Successfully choosed a seats", 1, 38, 50);
			paymentsMethodListPage(userIndex, movieIndex, cityIndex, mallIndex, dateIndex, timeIndex, ammount, seat);
			break;
		}
	}
	return;
}

// Enter the number of tickets to be purchased by the user
void ticketAmmountPage(int userIndex, int movieIndex, int cityIndex, int mallIndex, int dateIndex, int timeIndex) {
	// Variables
	string input;
	int int1;
	string strPrice = insertDotPrice(movie.price[movieIndex]);

	// Display
    system("CLS");
	cout << ui.borderUI << endl;
    cout << "             UKTix - Ticket Ammount" << endl;
    cout << ui.borderUI << endl << endl;
    cout << " Movie    : " << movie.title[movieIndex] << endl << endl;
    cout << " Location : " << cinema.mall[cityIndex][mallIndex] << " | " << cinema.city[cityIndex] << endl << endl;
    cout << " Date     : " << cinema.date[dateIndex] << endl << endl;
    cout << " Time     : " << cinema.time[timeIndex] << endl << endl;
    cout << " Price    : Rp " << strPrice << endl << endl;
    cout << ui.borderUI << endl;
	cout << "Type \'#\' for cancel" << endl;
	cout << " Ammount of Tickets : ";

	// Input Condition
	getline(cin, input);
	if(input == "") {
		notificator("Number of tickets must be 1 - 99", 2, 38, 50);
		ticketAmmountPage(userIndex, movieIndex, cityIndex, mallIndex, dateIndex, timeIndex);
		return;
	} else if(input == "#") {
		orderDetailsPage(userIndex, movieIndex, cityIndex, mallIndex, dateIndex, timeIndex);
		return;
	}
	try{
		int1 = stoi(input);
	} catch(exception &err) {
		notificator("Number of tickets must be 1 - 99", 2, 38, 50);
		ticketAmmountPage(userIndex, movieIndex, cityIndex, mallIndex, dateIndex, timeIndex);
		return;
	}
	if(int1 >= 1 &&  int1 <= 99) {
		chooseSeatPage(userIndex, movieIndex, cityIndex, mallIndex, dateIndex, timeIndex, int1);
		return;
	} else {
		notificator("Number of tickets must be 1 - 99", 2, 38, 50);
		ticketAmmountPage(userIndex, movieIndex, cityIndex, mallIndex, dateIndex, timeIndex);
		return;
	}
}

// Detail page of order
void orderDetailsPage(int userIndex, int movieIndex, int cityIndex, int mallIndex, int dateIndex, int timeIndex) {
	// Variables
	string input;
	string strPrice = to_string(movie.price[movieIndex]);
    strPrice.insert(2,".");

	// Display
    system("CLS");
	cout << ui.borderUI << endl;
    cout << "             UKTix - Order Details" << endl;
    cout << ui.borderUI << endl << endl;
    cout << " Movie    : " << movie.title[movieIndex] << endl << endl;
    cout << " Location : " << cinema.mall[cityIndex][mallIndex] << " | " << cinema.city[cityIndex] << endl << endl;
    cout << " Date     : " << cinema.date[dateIndex] << endl << endl;
    cout << " Time     : " << cinema.time[timeIndex] << endl << endl;
    cout << " Price    : Rp " << strPrice << endl << endl;
    cout << ui.borderUI << endl;
	cout << " [1] Next Step" << endl;
	cout << " [2] Direction route to the " << cinema.mall[cityIndex][mallIndex] << endl;
	cout << " [0] Back to Time List" << endl << endl;
	cout << " Choose Menu : ";

	// Input Condition
	getline(cin, input);
	if(input == "1") {
		ticketAmmountPage(userIndex, movieIndex, cityIndex, mallIndex, dateIndex, timeIndex);
		return;
	} else if(input == "2") {
		ShellExecute(NULL, "open", cinema.mallRoute[cityIndex][mallIndex].c_str(), NULL, NULL, SW_SHOWNORMAL);
		orderDetailsPage(userIndex, movieIndex, cityIndex, mallIndex, dateIndex, timeIndex);
		return;
	} else if(input == "0") {
		timeListPage(movieIndex, userIndex, cityIndex, mallIndex, dateIndex);
		return;
	} else {
        notificator("Menu not found", 2, 38, 50);
        orderDetailsPage(userIndex, movieIndex, cityIndex, mallIndex, dateIndex, timeIndex);
		return;
    }
}

// List page of Time
void timeListPage(int movieIndex, int userIndex, int cityIndex, int mallIndex, int dateIndex) {
	// Variables
	string input;
	int int1;

	// Display
    system("CLS");
	cout << ui.borderUI << endl;
    cout << "      UKTix - " << movie.title[movieIndex] << endl << endl;
	cout << "      Available Time at " << cinema.date[dateIndex] << endl;
    cout << ui.borderUI << endl << endl;

    for(int i = 0; i < 5; i++) {
        if(cinema.time[i] != "") {
            cout << "  [" << i + 1 << "] " << cinema.time[i] << endl;
        }
    }
    cout << endl << "  [0] Back to Date List" << endl << endl;
    cout << ui.borderUI << endl << endl;
	cout << " Choose Menu: ";

	// Input Condition
	getline(cin, input);
	if(input == "") {
		notificator("Menu not found", 2, 38, 50);
		timeListPage(movieIndex, userIndex, cityIndex, mallIndex, dateIndex);
		return;
	}
	try{
		int1 = stoi(input);
	} catch(exception &err) {
		notificator("Menu not found", 2, 38, 50);
		timeListPage(movieIndex, userIndex, cityIndex, mallIndex, dateIndex);
		return;
	}
	if(input == "0") {
		dateListPage(movieIndex, userIndex, cityIndex, mallIndex);
		return;
	}
    int1--;
	if(cinema.time[int1] != "" && int1 <= 5){
       orderDetailsPage(userIndex, movieIndex, cityIndex, mallIndex, dateIndex, int1);
	   return;
	} else {
		notificator("Menu not found", 2, 38, 50);
		timeListPage(movieIndex, userIndex, cityIndex, mallIndex, dateIndex);
		return;
	}
}

// List Page of Date
void dateListPage(int movieIndex, int userIndex, int cityIndex, int mallIndex) {
	// Variables
	string input;
	int int1;

	// Display
    system("CLS");
	cout << ui.borderUI << endl;
    cout << "      UKTix - " << movie.title[movieIndex] << endl << endl;
	cout << "      Available Date in " << cinema.mall[cityIndex][mallIndex] << endl;
    cout << ui.borderUI << endl << endl;

    for(int i = 0; i < 5; i++) {
        if(cinema.date[i] != "") {
            cout << "  [" << i + 1 << "] " << cinema.date[i] << endl;
        }
    }
    cout << endl << "  [0] Back to Cinema List" << endl << endl;
    cout << ui.borderUI << endl << endl;
	cout << " Choose Menu: ";

	// Input Condition
	getline(cin, input);
	if(input == "") {
		notificator("Menu not found", 2, 38, 50);
		dateListPage(movieIndex, userIndex, cityIndex, mallIndex);
		return;
	}
	try{
		int1 = stoi(input);
	} catch(exception &err) {
		notificator("Menu not found", 2, 38, 50);
		dateListPage(movieIndex, userIndex, cityIndex, mallIndex);
		return;
	}
	if(int1 == 0) {
		cinemaListPage(movieIndex, userIndex, cityIndex);
		return;
	}
	int1--;
	if(cinema.date[int1] != "" && int1 <= 5){
        timeListPage(movieIndex, userIndex, cityIndex, mallIndex, int1);
		return;
	} else {
		notificator("Menu not found", 2, 38, 50);
		dateListPage(movieIndex, userIndex, cityIndex, mallIndex);
		return;
	}
}

// Cinema list page in the city selected by the user
void cinemaListPage(int movieIndex, int userIndex, int cityIndex) {
	// Variables
	string input;
	int int1;

	// Display
    system("CLS");
	cout << ui.borderUI << endl;
    cout << "      UKTix - " << movie.title[movieIndex] << endl << endl;
	cout << "      Cinema Location in " << cinema.city[cityIndex] << endl;
    cout << ui.borderUI << endl << endl;

    for(int i = 0; i < 5; i++) {
        if(cinema.mall[cityIndex][i] != "") {
            cout << "  [" << i + 1 << "] " << cinema.mall[cityIndex][i] << endl;
        }
    }
    cout << endl << "  [0] Back to City List" << endl << endl;
    cout << ui.borderUI << endl << endl;
	cout << " Choose Menu: ";

	// Input Condition
	getline(cin, input);
	if(input == "") {
		notificator("Menu not found", 2, 38, 50);
		cinemaListPage(movieIndex, userIndex, cityIndex);
		return;
	}
	try{
		int1 = stoi(input);
	} catch(exception &err) {
		notificator("Menu not found", 2, 38, 50);
		cinemaListPage(movieIndex, userIndex, cityIndex);
		return;
	}
	if(int1 == 0) {
		cityListPage(movieIndex, userIndex);
		return;
	}
	int1 = int1 - 1;
	if(cinema.mall[cityIndex][int1] != "" && int1 <= 5) {
        dateListPage(movieIndex, userIndex, cityIndex, int1);
		return;
	} else {
		notificator("Menu not found", 2, 38, 50);
        cinemaListPage(movieIndex, userIndex, cityIndex);
		return;
	}
}

// City list page
void cityListPage(int movieIndex, int userIndex) {
	// Vriables
	string input;
	int int1;

	// Display
	system("CLS");
	cout << ui.borderUI << endl;
    cout << "      UKTix - " << movie.title[movieIndex] << endl << endl;
	cout << "      Cinema City Location" << endl;
    cout << ui.borderUI << endl << endl;
	for(int i = 0; i < 5; i++) {
		if(cinema.city[i] != "") {
			cout << "  [" << i + 1 << "] " << cinema.city[i] << endl;
		}
	}
	cout << endl << "  [0] Back to Movie Details" << endl << endl;
    cout << ui.borderUI << endl << endl;
	cout << " Choose Menu: ";

	// Input Condition
	getline(cin, input);
	if(input == "") {
		notificator("Menu not found", 2, 38, 50);
		cityListPage(movieIndex, userIndex);
		return;
	}
	try{
		int1 = stoi(input);
	} catch(exception &err) {
		notificator("Menu not found", 2, 38, 50);
		cityListPage(movieIndex, userIndex);
		return;
	}
	if(int1 == 0) {
		moviesDetailsPage(movieIndex, userIndex);
		return;
	}
	int1 = int1 - 1;
	if(cinema.city[int1] != "" && int1 <= 5) {
        cinemaListPage(movieIndex, userIndex, int1);
		return;
	} else {
        notificator("Menu not found", 2, 38, 50);
        cityListPage(movieIndex, userIndex);
		return;
    }
}

// Detail page of movies that have been selected by the user
void moviesDetailsPage(int movieIndex, int userIndex) {
	// Variables
	string input;

	// Display
	system("CLS");
	cout << ui.borderUI << endl;
    cout << "      UKTix - " << movie.title[movieIndex] << endl;
    cout << ui.borderUI << endl << endl;
    cout << " Title    : " << movie.title[movieIndex] << endl << endl;
    cout << " Genre    : " << movie.genre[movieIndex] << endl << endl;
    cout << " Synopsis : " << movie.synopsis[movieIndex] << endl << endl;
    cout << " Duration : " << movie.duration[movieIndex] << endl << endl;
    cout << " Director : " << movie.director[movieIndex] << endl << endl;
    cout << " Rating   : " << movie.rating[movieIndex] << endl << endl;
    cout << ui.borderUI << endl;
	cout << " [1] Play Trailer" << endl;
	cout << " [2] Buy Tickets" << endl;
	cout << " [0] Back to Movie List" << endl << endl;
	cout << " Choose Menu : ";

	// Input Condition
	getline(cin, input);
	if(input == "1") {
		ShellExecute(NULL, "open", movie.trailer[movieIndex].c_str(), NULL, NULL, SW_SHOWNORMAL);
		moviesDetailsPage(movieIndex, userIndex);
		return;
    } else if(input == "2") {
        cityListPage(movieIndex, userIndex);
		return;
    } else if(input == "0") {
        listMoviesPage(userIndex);
		return;
    } else {
        notificator("Menu not found", 2, 38, 50);
		moviesDetailsPage(movieIndex, userIndex);
        return;
    }
}

// List page of showing movies
void listMoviesPage(int userIndex) {
	// Variables
	string input;
	int int1;

	// Display
	system("CLS");
    cout << ui.borderUI << endl;
    cout << "      UKTix - Movie List" << endl << endl;
    cout << "      User: ";
	SetConsoleTextAttribute(h, 3);
	cout << userId[userIndex] << endl;
	SetConsoleTextAttribute(h, 7);
    cout << ui.borderUI << endl << endl;
	for(int i = 0; i < 30; i++) {
		if(movie.title[i] != "") {
			cout << "  [" << i + 1 << "] " << movie.title[i] << endl;
		}
	}
	cout << endl << "  [0] " << "Back to Home Page" << endl << endl;
    cout << ui.borderUI << endl << endl;
	cout << endl << " Choose Menu: ";

	// Input Condition
	getline(cin, input);
	if(input == "") {
		notificator("Menu not found", 2, 38, 50);
		listMoviesPage(userIndex);
		return;
	}
	try{
		int1 = stoi(input);
	} catch(exception &err) {
		notificator("Menu not found", 2, 38, 50);
		listMoviesPage(userIndex);
		return;
	}
	if(int1 == 0) {
		homePage(userIndex);
		return;
	}
	int1--;
    if(movie.title[int1] != "" && int1 <= 30) {
    	moviesDetailsPage(int1, userIndex);
		return;
    } else {
		notificator("Menu not found", 2, 38, 50);
        listMoviesPage(userIndex);
		return;
    }
}

// Details page of tickets that have been purchased by the user
void purchasedTicketDetailsPage(int userIndex, int tokenIndex) {
	// Variables
	string input;

	// Display=
	system("cls");
	cout << ui.borderUI << endl;
    cout << "                      UKTix" << endl;
    cout << "                 Token: ";
	SetConsoleTextAttribute(h, 10);
	cout << cinema.tokenUser[userIndex][tokenIndex] << endl;
	SetConsoleTextAttribute(h, 7);
    cout << "       (Don't share this token to anyone)" << endl;
    cout << ui.borderUI << endl << endl;
    cout << " Movie       : " << movie.title[stoi(cinema.tokenDetails[userIndex][tokenIndex][1])] << endl << endl;
    cout << " Location    : " << cinema.mall[stoi(cinema.tokenDetails[userIndex][tokenIndex][2])][stoi(cinema.tokenDetails[userIndex][tokenIndex][3])] << endl << endl;
    cout << " Date        : " << cinema.date[stoi(cinema.tokenDetails[userIndex][tokenIndex][4])] << endl << endl;
    cout << " Time        : " << cinema.time[stoi(cinema.tokenDetails[userIndex][tokenIndex][5])] << endl << endl;
    cout << " Ammount     : " << cinema.tokenDetails[userIndex][tokenIndex][6] << endl << endl;
    cout << " Seat        : " << cinema.tokenDetails[userIndex][tokenIndex][7] << endl << endl;
    cout << ui.borderUI << endl;
	cout << " [1] Direction route to the " << cinema.mall[stoi(cinema.tokenDetails[userIndex][tokenIndex][2])][stoi(cinema.tokenDetails[userIndex][tokenIndex][3])] << endl;
	cout << " [0] Back to Home Page" << endl << endl;
	cout << " Choose Menu : ";

	// Input Condition
	getline(cin, input);
	if(input == "1") {
		ShellExecute(NULL, "open", cinema.mallRoute[stoi(cinema.tokenDetails[userIndex][tokenIndex][2])][stoi(cinema.tokenDetails[userIndex][tokenIndex][3])].c_str(), NULL, NULL, SW_SHOWNORMAL);
		purchasedTicketDetailsPage(userIndex, tokenIndex);
		return;
	} else if(input == "0") {
		homePage(userIndex);
		return;
	} else {
		notificator("Menu not found", 2, 38, 50);
		purchasedTicketDetailsPage(userIndex, tokenIndex);
	}
}

// List page of tickets that have been purchased by the user
void purchasedTicketsPage(int userIndex) {
	// Variables
	string input;
	int int1;

	// Display
	system("cls");
	cout << ui.borderUI << endl;
	cout << "                    Your Order" << endl;
	cout << ui.borderUI << endl;
	if(cinema.tokenUser[userIndex][0] == ""){
		notificator("You don't have an order yet", 2, 38, 50, false);
	}
	for(int i = 0; i < 5; i++) {
		if(cinema.tokenUser[userIndex][i] == "") {
			break;
		}
		cout << "  [" << i + 1 << "] " << cinema.tokenUser[userIndex][i] << endl;
	}
	cout << endl << "  [0] Back To Home Page" << endl;
	cout << ui.borderUI << endl;
	cout << endl << "  Choose menu: ";

	// Input Condition
	getline(cin, input);
	if(input == "") {
		notificator("Menu not found", 2, 38, 50);
		purchasedTicketsPage(userIndex);
		return;
	}
	try{
		int1 = stoi(input);
	} catch(exception &err) {
		notificator("Input must be a Integer", 2, 38, 50);
		purchasedTicketsPage(userIndex);
		return;
	}
	if(int1 == 0) {
		homePage(userIndex);
		return;
	}
	int1--;
	if(cinema.tokenUser[userIndex][int1] != "") {
		purchasedTicketDetailsPage(userIndex, int1);
	} else {
		notificator("Menu not found", 2, 38, 50);
		purchasedTicketsPage(userIndex);
	}
	return;
}

// User Main page after logged in
void homePage(int userIndex) {
	// Variables
    string input;
	int int1;

	// Display
	system("CLS");
    cout << ui.borderUI << endl;
    cout << "      UKTix - Home" << endl << endl;
	cout << "      User: ";
	SetConsoleTextAttribute(h, 3);
	cout << userId[userIndex] << endl;
	SetConsoleTextAttribute(h, 7);
    cout << ui.borderUI << endl << endl;
    cout << "  [1] Movie List" << endl;
    cout << "  [2] Purchased Tickets" << endl;
    cout << "  [3] Logout" << endl << endl;
    cout << ui.borderUI << endl << endl;
    cout << " Choose Menu : ";

	// Input Chonditon
	getline(cin, input);
    if(input == "1") {
        listMoviesPage(userIndex);
		return;
    } else if(input == "2") {
		purchasedTicketsPage(userIndex);
	} else if(input == "3") {
        mainPage();
		return;
    } else {
		notificator("Menu not found", 2, 38, 50);
        homePage(userIndex);
		return;
    }
	return;
}

// Page for user login
void loginPage() {
    // Variables
	string input;
    string userTemp;
    string passwordTemp;

	// Display
	MENU: {
		system("CLS");
		cout << ui.borderUI << endl;
		cout << "                  UKTix - Login" << endl;
		cout << ui.borderUI << endl;
		cout << "Type \'#\' for cancel" << endl;
		
		// Input Condition
		if(userTemp == "") {
			cout << " Username : ";
			getline(cin, input);
			if(input == "") {
				notificator("Username can't be empty", 2, 38, 50);
				goto MENU;
				return;
			} else if(input == "#") {
				mainPage();
				return;
			}
			for(int i = 0; i < input.length(); i++) {
				if(input[i] == ' ') {
					notificator("Don't use space in username!", 2, 38, 50);
					goto MENU;
					return;
				}
			}
			userTemp = input;
		} else {
			cout << " Username : " << userTemp << endl;
		}
		if(passwordTemp == "") {
			cout << " Password : ";
			getline(cin, input);
			if(input == "") {
				notificator("Password can't be empty", 2, 38, 50);
				goto MENU;
				return;
			} else if(input == "#") {
				mainPage();
				return;
			}
			for(int i = 0; i < input.length(); i++) {
				if(input[i] == ' ') {
					notificator("Don't use space in password!", 2, 38, 50);
					goto MENU;
					return;
				}
			}
			passwordTemp = input;
		} else {
			cout << " Password : " << passwordTemp;
		}
	}

	// Account Check
	for(int i = 0; i <= 10; i++) {
		if(userTemp == userId[i]) {
			if(passwordTemp == password[i]) {
				notificator("Login Success", 1, 38, 50);
				homePage(i);
				return;
			}
		}
	}

	// Notification When Wrong
	notificator("Username or Password is wrong", 2, 38, 50);
	loginPage();
	return;
}

// Page for user register
void regisPage() {
	// Variables
	string input, userTemp, passwordTemp;
	int index;
	bool isAvailable = false;

	// Data Size Check
	for(int i = 0; i < 10; i++) {
        if(userId[i] == "") {
            index = i;
            isAvailable = true;
            break;
        }
    }
	
    if(isAvailable == false) {
		system("CLS");
		cout << ui.borderUI << endl;
		cout << "                 UKTix - Register" << endl;
		cout << ui.borderUI << endl;
		notificator("User Is Full", 2, 38, 50);
		mainPage();
		return;
    }

	// Display
	MENU: {
		system("CLS");
		cout << ui.borderUI << endl;
		cout << "                 UKTix - Register" << endl;
		cout << ui.borderUI << endl;
		cout << "Type \'#\' for cancel" << endl;
		
		// Input Condition
		if(userTemp == "") {
			cout << " New Username : ";
			getline(cin, input);
			if(input == "") {
				notificator("Username can't be empty", 2, 38, 50);
				goto MENU;
				return;
			} else if(input == "#") {
				mainPage();
				return;
			}
			for(int i = 0; i < input.length(); i++) {
				if(input[i] == ' ') {
					notificator("Don't use space in username", 2, 38, 50);
					goto MENU;
					return;
				}
			}
			if(input.length() < 3) {
				notificator("Username length must be >= 3", 2, 38, 50);
				goto MENU;
				return;
			} else if(symbolCheck(input) == true) {
				notificator("Don't use any symbols or number in username", 2, 45, 50);
				goto MENU;
				return;
			}
			for(int i = 0; i < 10; i++) {
				if(userId[i] == input) {
					notificator("Username is already exist", 2, 38, 50);
					goto MENU;
					return;
				}
			}
			userTemp = input;
		} else {
			cout << " New Username : " << userTemp << endl;
		}
		cout << " New Password : ";
		getline(cin, input);
		if(input == "") {
			notificator("Password can't be empty", 2, 38, 50);
			goto MENU;
			return;
		} else if(input == "#") {
			mainPage();
			return;
		} else if(input.length() < 8) {
			notificator("Password length must be >= 8", 2, 38, 50);
			goto MENU;
			return;
		}
		for(int i = 0; i < input.length(); i++) {
			if(input[i] == ' ') {
				notificator("Don't use space in password", 2, 38, 50);
				goto MENU;
				return;
			}
		}
		passwordTemp = input;
	}
	userId[index] = userTemp;
	password[index] = passwordTemp;
	notificator("Register Success", 1,  38, 50);
	mainPage();
	return;
}

// Main Page
void mainPage(){
	// Variables
	string input;
	
	// Display
    system("CLS");
    cout << ui.borderUI << endl;
    cout << "                      UKTix                      " << endl;
    cout << ui.borderUI << endl << endl;
    cout << " [1] Login" << endl;
    cout << " [2] Register" << endl;
    cout << " [3] Exit" << endl << endl;
    cout << ui.borderUI << endl;
    cout << endl << " Choose Menu : ";
    getline(cin, input);

	// Input Check
    if(input == "1") {
        loginPage();
		return;
    }  else if(input == "2") {
        regisPage();
		return;
    } else if(input == "3") {
		system("cls");
		notificator("Thank you for using UKTix", 1, 38, 50);
		system("cls");
        return;
    } else {
		notificator("Menu not found", 2, 38, 50);
        mainPage();
		return;
    }
	return;
}

//////////////////////////////////////////////



/************** Main Function **************/

int main(){
	system("title UKTix");
	fillData();
	srand(int(time(NULL)));

	mainPage();
	return 0;
}

//////////////////////////////////////////////



/*************** Algorithms ***************/

// Fill Some Data Algorithms
void fillData() {
    // Array Cinema Theater
    for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			for(int k = 0; k < 5; k++) {
				for(int l = 0; l < 5; l++) {
					for(int m = 0; m < 4; m++) {
						for(int n = 0; n < 11; n++) {
							string alphabet;
							if(n == 0) {
								alphabet = "A";
							}
							if(n == 1) {
								alphabet = "B";
							}
							if(n == 2) {
								alphabet = "C";
							}
							if(n == 3) {
								alphabet = "D";
							}
							if(n == 4) {
								alphabet = "E";
							}
							if(n == 5) {
								alphabet = "F";
							}
							if(n == 6) {
								alphabet = "G";
							}
							if(n == 7) {
								alphabet = "H";
							}
							if(n == 8) {
								alphabet = "I";
							}
							if(n == 9) {
								alphabet = "J";
							}
							if(n == 10) {
								alphabet = "K";
							}
							for(int o = 0; o < 9; o++) {
								string a = alphabet + to_string(o + 1);
								cinema.theater[i][j][k][l][m][n][o][0] = a;
								cinema.theater[i][j][k][l][m][n][o][1] = "false";

							}
							int randomNumber1 = rand() % 10;
							for(int o = 1; o <= randomNumber1; o++) {
								int randomNumber2 = rand() % 10;
								if(randomNumber2 == 0) {
									randomNumber2++;
								}
								cinema.theater[i][j][k][l][m][n][randomNumber2 - 1][1] = "true";
							}
						}
					}
				}
			}
		}
	}

	// Border UI
	for(int i = 1; i <= 50; i++) {
		ui.borderUI += 205;
	}

	// Screen UI
	ui.screenUI +=  "  ";
	ui.screenUI += 218;
	for(int i = 1; i <= 44; i++){
		ui.screenUI += 196;
	}
	ui.screenUI += 191;
	ui.screenUI += "\n";
	ui.screenUI += "  ";
	ui.screenUI += 179;
	for(int i = 1; i <= 19; i++){
		ui.screenUI += " ";
	}
	ui.screenUI += "Screen";
	for(int i = 1; i <= 19; i++){
		ui.screenUI += " ";
	}
	ui.screenUI += 179;
	ui.screenUI += "\n";
	ui.screenUI += "  ";
	ui.screenUI += 192;
	for(int i = 1; i <= 44; i++){
		ui.screenUI += 196;
	}
	ui.screenUI += 217;
    return;
}

// Notification Generator Algorithms
void notificator(string text, int color, int borderLen, int parentLen, bool isContinue) {
	/* Colors:
		(1) = Green
		(2) = Red
	*/
	
	// variables
	char sym1 = 218; // ┌
	char sym2 = 196; // ─
	char sym3 = 191; // ┐
	char sym4 = 179; // │
	char sym5 = 192; // └
	char sym6 = 217; // ┘
	int textLen = text.length();
	int splitTextLen = textLen / 2;
	int splitBorderLen = borderLen / 2;
	int colorReset = 7;
	string confirm = "Press any key to continue...";
	int confirmLen = confirm.length();
	int splitConfirmLen = confirmLen / 2;
	int intPosition = (parentLen - (borderLen + 2)) / 2;
	string strPosition;


	// Check Param
	if(textLen <= 0) { 
		cout << "Error 1";
		return;
	} else if(!(color >= 1 && color <= 2)) {
		cout << "Error 2";
		return;
	} else if(borderLen <= 0) {
		cout << "Error 3";
		return;
	}
	
	if(textLen > borderLen) {
		cout << "Error 3";
		return;
	} else if(borderLen > parentLen) {
		cout << "Error 4";
		return;
	}

	if(color == 1) {
		color = 10;
	} else if(color == 2) {
		color = 12;
	}

	// Algo
	if(isContinue == true) {
		for(int i = 1; i <= intPosition; i++) {
			strPosition += " ";
		}
		cout << strPosition << sym1;
		for(int i = 1; i <= borderLen; i++) {
			cout << sym2;
		}
		cout << sym3 << endl;
		cout << strPosition << sym4;
		for(int i = 1; i <= (splitBorderLen - splitTextLen); i++) {
			cout << " ";
		}
		SetConsoleTextAttribute(h, color);
		cout << text;
		SetConsoleTextAttribute(h, colorReset);
		for(int i = 1; i <= (borderLen - ((splitBorderLen - splitTextLen) + textLen)); i++) {
			cout << " ";
		}
		cout << sym4 << endl;
		cout << strPosition << sym4;
		for(int i = 1; i <= (splitBorderLen - splitConfirmLen); i++) {
			cout << " ";
		}
		cout << confirm;
		for(int i = 1; i <= (borderLen - ((splitBorderLen - splitConfirmLen) + confirmLen)); i++) {
			cout << " ";
		}
		cout << sym4 << endl;
		cout << strPosition << sym5;
		for(int i = 1; i <= borderLen; i++) {
			cout << sym2;
		}
		cout << sym6 << endl;
		getch();
	} else {
		for(int i = 1; i <= intPosition; i++) {
			strPosition += " ";
		}
		cout << strPosition << sym1;
		for(int i = 1; i <= borderLen; i++) {
			cout << sym2;
		}
		cout << sym3 << endl;
		cout << strPosition << sym4;
		for(int i = 1; i <= (splitBorderLen - splitTextLen); i++) {
			cout << " ";
		}
		SetConsoleTextAttribute(h, color);
		cout << text;
		SetConsoleTextAttribute(h, colorReset);
		for(int i = 1; i <= (borderLen - ((splitBorderLen - splitTextLen) + textLen)); i++) {
			cout << " ";
		}
		cout << sym4 << endl;
		cout << strPosition << sym5;
		for(int i = 1; i <= borderLen; i++) {
			cout << sym2;
		}
		cout << sym6 << endl;
	}
	return;
}

// Algorithms for Insert a Dot in Price
string insertDotPrice(int price) {
	string strPrice = to_string(price);
    if(strPrice.length() == 5){
        strPrice.insert(2,".");
    } else if(strPrice.length() == 6){
        strPrice.insert(3,".");
    } else if(strPrice.length() == 7){
        strPrice.insert(1,".");
        strPrice.insert(5,".");
    }

	return strPrice;
}

// Token Generator for Ticket
string tokenGenerator() {
    string numeric[9] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
	string alphabeticLow[26] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
	string alphabeticUp[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    string token;

	for(int i = 1; i <= 7; i++) {
		int ganjilGenap = rand() % 10;
		if((ganjilGenap % 2) == 1) {
			int ganjilGenap2 = rand() % 10;
			if((ganjilGenap2 % 2) == 1) {
				int alphaIndex = rand() % 26;
				token += alphabeticLow[alphaIndex];
			} else if((ganjilGenap2 % 2) == 0) {
				int alphaIndex = rand() % 26;
				token += alphabeticUp[alphaIndex];
			}
		} else if((ganjilGenap % 2) == 0) {
			int numerIndex = rand() % 9;
			token += numeric[numerIndex];
		}
		
		if(i == 7 && token.length() != 7) {
            i = 0;
			token = "";
		}
	}

    return token;
}

// Ticket printing algorithm
void printTicket(int userIndex, int movieIndex, int cityIndex, int mallIndex, int dateIndex, int timeIndex, int ammount, string seat[], int tokenIndex, string email) {
	// Variables
	string strTotal = insertDotPrice(movie.price[movieIndex] * ammount);
    string strPrice = insertDotPrice(movie.price[movieIndex]);
	string ticketFileName = "./bin/data/Ticket.tix";

	// Write Ticket Algorithms
	ofstream wDatabase;
	wDatabase.open(ticketFileName);
	wDatabase << "{\n  \"email\": \"" << email << "\",\n";
	wDatabase << "  \"text\": \"══════════════════════════════════════════════════\\n";
    wDatabase << "                      UKTix" << "\\n";
    wDatabase << "                 Token: " << cinema.tokenUser[userIndex][tokenIndex] << "\\n";
    wDatabase << "       (Don't share this token to anyone)" << "\\n";
    wDatabase << "══════════════════════════════════════════════════" << "\\n\\n";
    wDatabase << " Movie       : " << movie.title[movieIndex] << "\\n";
    wDatabase << " Location    : " << cinema.mall[cityIndex][mallIndex] << " | " << cinema.city[cityIndex] << "\\n\\n";
    wDatabase << " Date        : " << cinema.date[dateIndex] << "\\n\\n";
    wDatabase << " Time        : " << cinema.time[timeIndex] << "\\n\\n";
    wDatabase << " Price       : Rp " << strPrice << "\\n\\n";
    wDatabase << " Ammount     : " << ammount << "\\n\\n";
    wDatabase << " Seat        : ";
    for(int i = 0; i < ammount; i++) {
        wDatabase << seat[i] << " ";
    }
    wDatabase << "\\n\\n";
    wDatabase << " Total Price : Rp " << strTotal << "\\n\\n";
    wDatabase << "══════════════════════════════════════════════════\"\n}";

	return;
}

// Check data of token and Generating a token & ticket
void loadingToken(int userIndex, int movieIndex, int cityIndex, int mallIndex, int dateIndex, int timeIndex, int ammount, string seat[]) {
	// Variables
	int tokenIndex;
	string details;

	// Insert the token to array data
	for(tokenIndex = 0; tokenIndex < 5; tokenIndex++) {
		if(cinema.tokenUser[userIndex][tokenIndex] == "") {
			cinema.tokenUser[userIndex][tokenIndex] = tokenGenerator();
			break;
		}
		if(tokenIndex == 4) {
			notificator("You have reached the purchase limit", 2, 38, 50);
			homePage(userIndex);
			return;
		}
	}
	
	// Insert a ticket Details to array data
	cinema.tokenDetails[userIndex][tokenIndex][0] = to_string(userIndex);
	cinema.tokenDetails[userIndex][tokenIndex][1] = to_string(movieIndex);
	cinema.tokenDetails[userIndex][tokenIndex][2] = to_string(cityIndex);
	cinema.tokenDetails[userIndex][tokenIndex][3] = to_string(mallIndex);
	cinema.tokenDetails[userIndex][tokenIndex][4] = to_string(dateIndex);
	cinema.tokenDetails[userIndex][tokenIndex][5] = to_string(timeIndex);
	cinema.tokenDetails[userIndex][tokenIndex][6] = to_string(ammount);
	for(int i = 0; i < ammount; i++) {
		cinema.tokenDetails[userIndex][tokenIndex][7] += seat[i] + " ";
	}

	// Set the seats to be true
	for(int i = 0; i < ammount; i++) {
		for(int j = 0; j < 11; j++) {
            for(int k = 0; k < 9; k++) {
				if(cinema.theater[cityIndex][mallIndex][dateIndex][timeIndex][movieIndex][j][k][0] == seat[i]) {
					cinema.theater[cityIndex][mallIndex][dateIndex][timeIndex][movieIndex][j][k][1] = "true";
				}
			}
		}
	}

	// Purchased Success Page
	purchasedSuccessPage(userIndex, movieIndex, cityIndex, mallIndex, dateIndex, timeIndex, ammount, seat, tokenIndex);
	return;
}

// Algorithm to check if a text contains a symbol
bool symbolCheck(string text) {
    int userLen = text.length();
    int id;
    for(int i = 0; i < userLen; i++) {
        id = int(text[i]);
        if(id < 65) {
            return true;
        }
        if(id > 90 && id < 97) {
            return true;
        }
        if(id > 122) {
            return true;
        }
    }
    return false;
}

//////////////////////////////////////////////