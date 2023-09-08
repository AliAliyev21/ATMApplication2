#include <iostream>
#include<assert.h>
#include <string>
using namespace std;


class Card {
private:
	string pan;
	string pin;
	string cvc;
	string expireDate;
	double balance;
public:

#pragma region Constructors
	Card() :pan("No Data"), pin("No Data"), cvc("No Data"), expireDate("No Data"), balance(0) {};

	Card(const string& pan, const string& pin, const string& cvc, const string& expireDate, const double& balance) {
		SetPan(pan);
		SetPin(pin);
		SetCvc(cvc);
		SetExpireDate(expireDate);
		SetBalance(balance);
	}
#pragma endregion

#pragma region Getters
	string GetPan()const { return pan; }

	string GetPin()const { return pin; }

	string GetCvc()const { return cvc; }

	string GetExpireDate()const { return expireDate; }

	double GetBalance()const { return balance; }
#pragma endregion

#pragma region Setters

	void SetPan(const string& pan) {
		assert(pan.size() == 16 && "Pan should be 16 digits");
		this->pan = pan;
	}

	void SetPin(const string& pin) {
		assert(pin.size() == 4 && "Pin should be 4 digits");
		this->pin = pin;
	}

	void SetCvc(const string& cvc) {
		assert(cvc.size() == 3 && "Cvc should be 3 digits");
		this->cvc = cvc;
	}

	void SetExpireDate(const string& expireDate) {
		this->expireDate = expireDate;
	}

	void SetBalance(const double& balance) {
		assert(balance >= 0 && "Balance should be greater than 0");
		this->balance = balance;
	}



#pragma endregion

#pragma region Other Functions

	void ShowCardInfo()const {
		cout << "\t\t\t\t= = = Card Info = = = " << endl << endl << endl;
		cout << "PAN : " << pan.substr(0, 4) << " - " << pan.substr(4, 4)
			<< " - " << pan.substr(8, 4) << " - " << pan.substr(12, 4) << endl;
		cout << "PIN : " << pin << endl;
		cout << "CVC : " << cvc << endl;
		cout << "Expire Date : " << expireDate.substr(0, 2) << " / " << expireDate.substr(2, 2) << endl;
		cout << "Balance : " << balance << " $ " << endl;
	}

#pragma endregion

};

class Notification {
	string information;
	string n_date;
public:
	Notification() :information("No Data"), n_date("No Data") {};

	Notification(const string& information) {
		this->n_date = __TIMESTAMP__;
		SetInformation(information);
	}

	void SetInformation(const string& information) {
		this->information = information;
	}


	string GetInformation()const { return information; }

	string GetDate()const { return n_date; }

	void ShowNotification() {
		cout << "Information : \"" << information << "\"  ________   Date : " << n_date << endl;
	}
};

class User {
private:
	string name;
	string surname;
	short int age;
	string phone;
	Card* card;
	Notification** notifications;
	int n_count=0;

public:
#pragma region Constructors
	User() :name("No Data"), surname("No Data"), age(0), phone("No Data"), card(nullptr){};

	User(const string& name, const string& surname, const int& age, const string& phone, const Card* card) {
		SetName(name);
		SetSurname(surname);
		SetAge(age);
		SetPhone(phone);
		SetCard(card);
	}
#pragma endregion

#pragma region Getters

	string GetName()const { return name; }

	string GetSurname()const { return surname; }

	short int GetAge()const { return age; }

	string GetPhone()const { return phone; }

	Card* GetCard()const { return card; }

	Notification** GetNotifications()const { return notifications; }

	int GetNotificationCount()const { return n_count; }

#pragma endregion

#pragma region Setters

	void SetName(const string& name) {
		this->name = name;
	}

	void SetSurname(const string& surname) {
		this->surname = surname;
	}

	void SetAge(const short int& age) {
		assert(age >= 18 && "Age should be greater than 17");
		this->age = age;
	}

	void SetPhone(const string& phone) {
		assert(phone.size() == 10 && "Phone should be 9 digits");
		this->phone = phone;
	}

	void SetCard(const Card* card) {
		this->card = new Card(*card);
	}

	void AddNotification(const Notification* notific) {
		auto temp = new Notification * [n_count + 1] {};
		for (size_t i = 0; i < n_count; i++)
		{
			temp[i] = notifications[i];
		}
		temp[n_count] = new Notification(*notific);
		this->notifications = temp;
		temp = nullptr;
		++n_count;
	}
#pragma endregion

	void ShowUserInfo()const {
		cout << "Name : " << this->name << endl;
		cout << "Surname : " << this->surname << endl;
		cout << "Age : " << this->age << endl;
		cout << "Phone : " << phone.substr(0, 3) << " - " << phone.substr(3, 3) << " - "
			<< phone.substr(6, 2) << " - " << phone.substr(8, 2) << endl;
	}

	~User() {
		delete card;
		for (size_t i = 0; i < n_count; i++)
		{
			delete notifications[i];
		}
		delete[]notifications;
	}
};

class Bank {
	string name;
	User** users;
	int count;
public:
	Bank() :name("No Data"), users(nullptr), count(0) {};

	Bank(const string& name) {
		SetName(name);
	}

	void SetName(const string& name) {
		this->name = name;
	}

	string GetName()const { return name; }

	User** GetUsers()const { return users; }

	int GetUsersCount()const { return count; }

	void AddUser(const User* user) {
		auto temp = new User * [count + 1] {};
		for (size_t i = 0; i < count; i++)
		{
			temp[i] = users[i];
		}
		temp[count] = new User(*user);
		users = temp;
		temp = nullptr;
		++count;
	}
	
	void DeleteUser(const User* user) {
		auto temp = new User * [count - 1] {};
		int index = 0;
		for (size_t i = 0; i < count; i++)
		{
			if (users[i]->GetCard()->GetPan() != user->GetCard()->GetPan()) { temp[index] = users[i]; ++index; }
		}
		users = temp;
		temp = nullptr;
		--count;
	}

	void ShowAllUsersInfo()const {
		string line(40, '-');
		for (size_t i = 0; i < count; i++)
		{
			cout << i + 1 << " . " << line << endl; users[i]->ShowUserInfo(); cout << endl << endl;
		}
	}


};

class Admin {
	string adminName;
	string adminPass;
public:
	Admin() :adminName("No data"), adminPass("No data") {};

	Admin(const string& adminName, const string& adminPass) {
		SetName(adminName);
		SetPass(adminPass);
	}

	void SetName(const string& adminName) {
		this->adminName = adminName;
	}

	void SetPass(const string& adminPass) {
		this->adminPass = adminPass;
	}

	string GetName()const { return adminName; }

	string GetPass()const { return adminPass; }


};

void UserInterface(const User* user) {
	cout << "\t\t\t\tWelcome " << user->GetName() << " " << user->GetSurname() << "  " << char(2) << endl << endl << endl;
	cout << "Account Info        [1]" << endl;
	cout << "Card Info           [2]" << endl;
	cout << "Notifications ( " << user->GetNotificationCount() << " ) " << "[3]" << endl;
	cout << "Money transfer      [4]" << endl;
	cout << "Return App Menu     [5]" << endl;
}

void AdminInterface(const Admin* admin) {
	cout << "Show All Users   [1]" << endl;
	cout << "Add New User     [2]" << endl;
	cout << "Update User      [3]" << endl;
	cout << "Delete User      [4]" << endl;
	cout << "Return App Menu  [5]" << endl;
}

void App(const Bank& bank) {
	cout << "\t\t\t\t = = = = " << bank.GetName() << " = = = = " << endl << endl << endl;
	cout << "User  [1]" << endl;
	cout << "Admin [2]" << endl;
}

void MoneyTransferInterface(const User* user) {
	cout << "Balance : " << user->GetCard()->GetBalance() << " $ " << endl << endl << endl;
	cout << "Additional transfer and payment methods will be available soon ... Thank you for choosing us" << endl << endl;
	cout << "Increasing the balance of other cards   [1]" << endl;
	cout << "Increasing mobile number balance        [2]" << endl << endl;
	cout << "Return User Menu                        [3]" << endl;
}

void MoneyTransferToOtherCard(User* user, User* other, const double& money) {
	double userBalance = user->GetCard()->GetBalance();
	double otherBalance = other->GetCard()->GetBalance();
	user->GetCard()->SetBalance(userBalance - money);
	other->GetCard()->SetBalance(otherBalance + money);
	int moneyTam = (int)money;
	int moneyKesr = (money - (int)money)*100;
	string notUser = to_string(moneyTam) + "." + to_string(moneyKesr) + " $ was transferred to the card with PAN number : " + other->GetCard()->GetPan();
	string notOther = to_string(moneyTam) + "." + to_string(moneyKesr) + " $ have been transferred from the card with PAN number :  " + user->GetCard()->GetPan() + "   to your card";
	user->AddNotification(new Notification(notUser));
	other->AddNotification(new Notification(notOther));
}

void MoneyTransferToThePhone(Bank&bank,User* user,const string & phone,const double & money){
	double userMoney= user->GetCard()->GetBalance();
	user->GetCard()->SetBalance(userMoney-money);
	int moneyTam = (int)money;
	int moneyKesr = (money - (int)money) * 100;
	string notificUser = to_string(moneyTam) + "." + to_string(moneyKesr) +
		" $ was transferred to the phone contact corresponding to the number : " + phone;
	user->AddNotification(new Notification(notificUser));
	for (size_t i = 0; i < bank.GetUsersCount(); i++)
	{
		if (phone == bank.GetUsers()[i]->GetPhone()) {
			string starsPan(8, '*');
			string notificOther = to_string(moneyTam) + "." + to_string(moneyKesr) +
				" $ was transferred to the your phone number from the bank account corresponding to the PAN number : "
				+ user->GetCard()->GetPan().substr(0, 4) + starsPan + user->GetCard()->GetPan().substr(user->GetCard()->GetPan().size() - 4, 4);
			bank.GetUsers()[i]->AddNotification(new Notification(notificOther)); break;
		}
	}
}

void ShowAllUsersByAdmin(const Bank& bank) {
	for (size_t i = 0; i < bank.GetUsersCount(); i++)
	{
		cout << "\t\t\t\t= = = = User "<<i+1<<" = = = = " << endl;
		bank.GetUsers()[i]->ShowUserInfo(); cout << endl<<endl;
		bank.GetUsers()[i]->GetCard()->ShowCardInfo(); cout << endl << endl;
		for (size_t i = 0; i < bank.GetUsers()[i]->GetNotificationCount(); i++)
		{
			bank.GetUsers()[i]->GetNotifications()[i]; cout << endl << endl;
		}
		cout << "--------------------------------------------------------" << endl << endl;
	}
}

User* GetNewUser() {
	cout << "User Info " << endl << endl;
	cout << "Enter name : ";
	string name = "";
	getline(cin, name);
	cout << "Enter surname : ";
	string surname = "";
	getline(cin, surname);
	cout << "Enter age : ";
	short int age = 0;
	cin >> age;
	cin.ignore();
	cin.clear();
	cout << "Enter phone number : ";
	string phone = "";
	getline(cin, phone);
	cout << endl << endl;
	cout << "Card Info " << endl<<endl;
	cout << "Enter PAN number (16 digits) : ";
	string pan = "";
	getline(cin, pan);
	cout << "Enter PIN number (4 digits) : ";
	string pin = "";
	getline(cin, pin);
	cout << "Enter CVC number (3 digits) : ";
	string cvc = "";
	getline(cin, cvc);
	cout << "Enter Expire Date ( example ==> 0523) : ";
	string expireDate = "";
	getline(cin, expireDate);
	double balance = 0;
	Card* card = new Card(pan, pin, cvc, expireDate, balance);
	return new User(name, surname, age, phone, card);
}

void UpdateUser(User* user) {
	user->ShowUserInfo();
	cout << endl << endl;
	cout << "Update PAN number (16 digits) : ";
	string pan = "";
	getline(cin, pan);
	user->GetCard()->SetPan(pan);
	cout << "Update PIN number (4 digits) : ";
	string pin = "";
	getline(cin, pin);
	user->GetCard()->SetPin(pin);
	cout << "Update CVC number (3 digits) : ";
	string cvc = "";
	getline(cin, cvc);
	user->GetCard()->SetCvc(cvc);
	cout << "Update Expire Date (exam ==> 0524) : ";
	string expireDate = "";
	getline(cin, expireDate);
	user->GetCard()->SetExpireDate(expireDate);
	cout << "Update balance ( $ ): ";
	double balance = 0;
	cin >> balance;
	user->GetCard()->SetBalance(balance);
}

void main() {
	system("color 09");
	Card* card1 = new Card("4169123456789123", "1111", "123", "0223", 4000);
	User user1("Anvar", "Mammadov", 21, "0514268456", card1);
	Card* card2 = new Card("4169423485498504", "2222", "444", "0226", 1230);
	User user2("Murad", "Goyayev", 21, "0703004449", card2);
	Notification not1("test");
	user1.AddNotification(&not1);
	Bank bank("UniBank");
	bank.AddUser(&user1);
	bank.AddUser(&user2);
	Admin* admin = new Admin("admin", "admin");
	char operation = NULL, select = NULL;
	enum AppSelection { iAmUser = '1', iAmAdmin = '2' };
	enum OperationsUI { accInfo = '1', cardInfo = '2', notific = '3', moneyTransfer = '4', back = '5' };
	while (true)
	{
		bool inputAccess = false;
		User* user = nullptr;
		system("cls");
		App(bank);
		cin >> select;
		cin.ignore();
		cin.clear();
		system("cls");
		if (select == iAmUser) {
			int pan_count = 0;
			int count = 0;
			while (true)
			{
				system("cls");
				cout << "Enter PAN : ";
				string pan = "";
				getline(cin, pan);
				system("cls");
				for (size_t i = 0; i < bank.GetUsersCount(); i++)
				{
					inputAccess = false;
					if (bank.GetUsers()[i]->GetCard()->GetPan() == pan) {
						while (count <= 3) {
							system("cls");
							cout << "Enter PIN : ";
							string pin = "";
							getline(cin, pin);
							system("cls");
							++count;
							if (bank.GetUsers()[i]->GetCard()->GetPin() == pin) {
								inputAccess = true; user = bank.GetUsers()[i]; break;
							}
							else {
								if (count == 3) { cout << "You have no rights left" << endl; system("pause"); break; }
								else cout << "PIN is wrong ... Try again.." << endl; system("pause"); continue;
							}
						}
						if (inputAccess)break;
					}
				}
				if (!inputAccess) {
					++pan_count;
					if (pan_count == 3)break;
					cout << "PAN is not found or PIN wrong ... Try again ..." << endl; system("pause"); continue;
				}
				else break;
			}
			if (inputAccess) {
				while (true)
				{
					system("cls");
					UserInterface(user);
					cin >> operation;
					cin.ignore();
					cin.clear();
					system("cls");
					if (operation == accInfo) {
						cout << "\t\t\t\t= = = = User Info = = = = \n\n" << endl;
						user->ShowUserInfo(); system("pause"); continue;
					}
					else if (operation == cardInfo) {
						user->GetCard()->ShowCardInfo(); system("pause"); continue;
					}
					else if (operation == notific) {
						for (size_t i = 0; i < user->GetNotificationCount(); i++)
						{
							cout << i + 1 << " .   "; user->GetNotifications()[i]->ShowNotification(); cout << endl << endl;
						}
						system("pause"); continue;
					}
					else if (operation == moneyTransfer) {
						system("cls");
						MoneyTransferInterface(user);
						char select = NULL;
						cin >> select;
						cin.ignore();
						cin.clear();

						if (select == '1') {
							User* other = nullptr;
							cout << "Enter the PAN number of the card to which you will transfer the money : ";
							string otherPan = "";
							getline(cin, otherPan);
							bool otherPanFind = false;
							for (size_t i = 0; i < bank.GetUsersCount(); i++)
							{
								if (bank.GetUsers()[i]->GetCard()->GetPan() == otherPan) {
									otherPanFind = true; other = bank.GetUsers()[i]; break;
								}
							}
							if (otherPanFind) {
								while (true)
								{
									cout << "10 $             [1]" << endl;
									cout << "20 $             [2]" << endl;
									cout << "50 $             [3]" << endl;
									cout << "100 $            [4]" << endl;
									cout << "Other            [5]" << endl;
									cout << "Return User Menu [6]" << endl;
									char choice = NULL;
									cin >> choice;
									cin.ignore();
									cin.clear();
									system("cls");
									if (choice == '1') {
										if (user->GetCard()->GetBalance() < 10) { cout << "Your balance is insufficient.." << endl; system("pause"); continue; }//assert istifade etmedim , çökmesini istemedim
										else {
											MoneyTransferToOtherCard(user, other, 10); cout << "Operation successfully" << endl; system("pause"); break;
										}
									}
									else if (choice == '2') {
										if (user->GetCard()->GetBalance() < 20) { cout << "Your balance is insufficient.." << endl; system("pause"); continue; }//assert istifade etmedim , çökmesini istemedim
										else {
											MoneyTransferToOtherCard(user, other, 20); cout << "Operation successfully" << endl; system("pause"); break;
										}
									}
									else if (choice == '3') {
										if (user->GetCard()->GetBalance() < 50) { cout << "Your balance is insufficient.." << endl; system("pause"); continue; }//assert istifade etmedim , çökmesini istemedim
										else {
											MoneyTransferToOtherCard(user, other, 50); cout << "Operation successfully" << endl; system("pause"); break;
										}
									}
									else if (choice == '4') {
										if (user->GetCard()->GetBalance() < 100) { cout << "Your balance is insufficient.." << endl; system("pause"); continue; }//assert istifade etmedim , çökmesini istemedim
										else {
											MoneyTransferToOtherCard(user, other, 100); cout << "Operation successfully" << endl; system("pause"); break;
										}
									}
									else if (choice == '5') {
										cout << "Enter the amount you want to transfer to another card : ";
										double money = 0;
										cin >> money;
										cin.ignore();
										cin.clear();
										if (user->GetCard()->GetBalance() < money) { cout << "Your balance is insufficient.." << endl; system("pause"); continue; }//assert istifade etmedim , çökmesini istemedim
										else {
											MoneyTransferToOtherCard(user, other, money); cout << "Operation successfully" << endl; system("pause"); break;
										}
									}
									else if (choice == '6') break;
									else { cout << "Operation not found ... " << endl; system("pause"); continue; }
								}

							}
							else { cout << "PAN not found ... " << endl; system("pause"); continue; }
						}
						else if (select == '2') {
							while (true)
							{
								cout << "Enter phone number : ";
								string phone = "";
								getline(cin, phone);
								cout << "1 $              [1]" << endl;
								cout << "2 $              [2]" << endl;
								cout << "5 $              [3]" << endl;
								cout << "10 $             [4]" << endl;
								cout << "Other            [5]" << endl;
								cout << "Return User Menu [6]" << endl;
								char choice = NULL;
								cin >> choice;
								cin.ignore();
								cin.clear();
								system("cls");
								if (choice == '1') {
									if (user->GetCard()->GetBalance() < 1) { cout << "Your balance is insufficient.." << endl; system("pause"); continue; }//assert istifade etmedim , çökmesini istemedim
									else {
										MoneyTransferToThePhone(bank, user, phone, 1); cout << "Operation successfully" << endl; system("pause"); break;
									}
								}
								else if (choice == '2') {
									if (user->GetCard()->GetBalance() < 2) { cout << "Your balance is insufficient.." << endl; system("pause"); continue; }//assert istifade etmedim , çökmesini istemedim
									else {
										MoneyTransferToThePhone(bank, user, phone, 2); cout << "Operation successfully" << endl; system("pause"); break;
									}
								}
								else if (choice == '3') {
									if (user->GetCard()->GetBalance() < 5) { cout << "Your balance is insufficient.." << endl; system("pause"); continue; }//assert istifade etmedim , çökmesini istemedim
									else {
										MoneyTransferToThePhone(bank, user, phone, 5); cout << "Operation successfully" << endl; system("pause"); break;
									}
								}
								else if (choice == '4') {
									if (user->GetCard()->GetBalance() < 10) { cout << "Your balance is insufficient.." << endl; system("pause"); continue; }//assert istifade etmedim , çökmesini istemedim
									else {
										MoneyTransferToThePhone(bank, user, phone, 10); cout << "Operation successfully" << endl; system("pause"); break;
									}
								}
								else if (choice == '5') {
									cout << "Enter the amount to be transferred to the phone account : ";
									double m = 0;
									cin >> m;
									cin.ignore();
									cin.clear();
									if (user->GetCard()->GetBalance() < m) { cout << "Your balance is insufficient.." << endl; system("pause"); continue; }//assert istifade etmedim , çökmesini istemedim
									else {
										MoneyTransferToThePhone(bank, user, phone, m); cout << "Operation successfully" << endl; system("pause"); break;
									}
								}
								else if (choice == '6')break;
								else { cout << "Operation not found ... " << endl; system("pause"); continue; }
							}

						}
						else if (select == '3')continue;
						else break;
					}
					else if (operation == back)break;
					else {
						cout << "Operation not found ..." << endl; system("pause"); continue;
					}
				}
			}
			else {
				cout << "Something went wrong, it goes back to the beginning..." << endl; system("pause"); continue;
			}
		}
		else if (select == iAmAdmin) {
			int c = 0;
			bool adminAccess = false;
			while (c<=3)
			{
				system("cls");
				if (c==3) { cout << "You have no rights left" << endl; system("pause"); break; }
				c++;
				cout << "Username : ";
				string name = "";
				getline(cin, name);
				cout << "Password : ";
				string pass = "";
				getline(cin, pass);
				if (name == admin->GetName() && pass == admin->GetPass()) {
					adminAccess = true; break;
				}
				else { cout << "Username or pass wrong .. try again .. "; system("pause"); }
			}
			if (adminAccess) {
				char op = NULL;
				while (true)
				{
					system("cls");
					AdminInterface(admin);
					cin >> op;
					cin.ignore();
					cin.clear();
					system("cls");
					if (op == '1') {
						ShowAllUsersByAdmin(bank); system("pause"); continue;
					}
					else if (op == '2') {
						auto newuser = GetNewUser();
						bank.AddUser(newuser);
						cout << "User added successfully..." << endl; system("pause"); continue;
					}
					else if (op == '3') {
						ShowAllUsersByAdmin(bank);
						cout << "\n\nEnter PAN number for update user : " << endl;
						string panNumber = "";
						getline(cin, panNumber);
						User* usr = nullptr;
						for (size_t i = 0; i < bank.GetUsersCount(); i++)
						{
							if (panNumber == bank.GetUsers()[i]->GetCard()->GetPan()) { usr = bank.GetUsers()[i]; break; }
						}
						if (usr != nullptr) {
							UpdateUser(usr); cout << "User updated successfully.." << endl; system("pause"); continue;
						}
						else { cout << "User not found..." << endl; system("pause"); continue; }
					}
					else if (op == '4') {
						ShowAllUsersByAdmin(bank);
						cout << "\n\nEnter PAN number for delete user : " << endl;
						string panNumber = "";
						getline(cin, panNumber);
						User* oldUser = nullptr;
						for (size_t i = 0; i < bank.GetUsersCount(); i++)
						{
							if (panNumber == bank.GetUsers()[i]->GetCard()->GetPan()) { oldUser = bank.GetUsers()[i]; break; }
						}
						if (oldUser != nullptr) {
							bank.DeleteUser(oldUser); cout << "User deleted successfully.." << endl; system("pause"); continue;
						}
						else { cout << "User not found..." << endl; system("pause"); continue; }
					}
					else if (op == '5') break;
					else { cout << "Operation not found.." << endl; system("pause"); continue; }
				}
			}
			else {
				cout << "Something went wrong .. Returned App Menu.." << endl; system("pause"); break;
			}	
		}
		else if (select == '3') {
			cout << "Application closed.." << endl; system("pause"); break;
		}
		else { cout << "Operation not found..." << endl; system("pause"); }
	}
	cout << endl << endl << endl; cin.get();
}