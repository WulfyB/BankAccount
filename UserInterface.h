#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "BankAccount.h"
#include "SavingAccount.h"
#include "CheckingAccount.h"
#include "MoneyMarketAccount.h"
#include "CDAccount.h"
#include <iomanip>
#include <stdexcept>

class UserInterface
{
public:
	// This function initializes the user interface for the BTS for Aubie Bank.
	// This test program is incomplete in that the pay outs for interest are not applied
	// THIS is a lab exercise, and does not have full functionality
	// Also worth noting that contradiction between specs/examples were addressed by an 
	// inquiry to the TA Kaiqi Fan. The resulting implementation is an attempt to follow
	// her clarified instructions due to inconsistencies in the lab program
	int bankStart()
	{
		vector <BankAccount *> activeAccounts; // "Basket of active accounts"
		bool active = true; //Is BTS active?
		string uInput; //holds string inputs
		char input; //switch statement control char
		string temp; //holds temporary value
		string banner = "Welcome to AubieBank!"; //Aubie bank banner.
		size_t spaces = 0; //records space necessary
		string name; //Stores name for accounts
		string aType; //Stores account type
		double money; //money for withdrawal/deposit/etc
		string targetName; //name of target account holder
		string targetAccount; //target of transfer
		size_t numWD = 0; //stores number of withdrawal/deposits.
		double tHold; //Stores a transfer value or other values
		bool accExists = false; //checks of the account exists before attempt to access
		while (active)
		{
			uInput.clear();
			cout << "\n";
			spaces = 56 - banner.length();
			cout << string(12, ' ') // To center output: 80-56 =24, 24/2 = 12, so 12 spaces per side.
				<< "===================================================\n"
				<< string(12, ' ')
				<< "\n"
				<< string(12, ' ')
				<< "|"
				<< string(spaces / 2, ' ')
				<< banner
				<< string(spaces - spaces / 2, ' ')
				<< "|"
				<< string(12, ' ')
				<< "\n"
				<< string(12, ' ')
				<< "===================================================\n"
				<< string(12, ' ')
				<< "\n"
				<< "\n";
			cout << "Select an option by inputing the associated number:\n"
				<< "(1) Create Account, (2) Deposit, (3) Withdraw, (4), Transfer \n"
				<< "(5) Balance Inquiry, (6) Print account transcations, \n(7) Print bank balance, (8) Terminate \n"
				<< "User Input: ";
			while (uInput.empty())
			{
				getline(cin, uInput);
			}
			input = uInput.at(0);
			cout << "\n\n";
			switch (input)
			{
			case '1':
				temp.clear();
				cout << "We will be creating a new account. To cancel, input \"$$\" at any input.\n"
					<< "Please input name. "
					<< "Name:  ";
				while (temp.empty())
				{
					getline(cin, temp);
				}
				if (temp == "$$")
				{
					cout << "Ending transaction. This transaction will not be recorded.";
					break;
				}
				name = temp;
				cout << "Excellent. What kind of account type?\n"
					<< "(1)Checking Account, (2)Saving Account, (3)CD Account, (4) Money Market Account\n\n";
				temp.clear();
				uInput.clear();
				while (temp != "1" && temp != "2" && temp != "3" && temp != "4")
				{
					if (uInput == "$$")
					{
						break;
					}
					if (!uInput.empty())
					{
						cout << "Please input a numerical value to choose account.";
					}
					uInput.clear();
					while (uInput.empty())
					{
						getline(cin, uInput);
					}
					temp = uInput;

				}
				if (uInput == "$$")
				{
					cout << "Ending transaction. This transaction will not be recorded.";
					break;
				}
				aType;
				if (temp == "1")
				{
					aType = "Checking Account";
					for (size_t i = 0; i < activeAccounts.size(); i++)
					{
						if (activeAccounts[i]->getName() == name)
						{
							if (activeAccounts[i]->getAcc() == aType)
							{
								cout << "\n Warning: \nThis name/account combination already exists. \nThis transaction will not be recorded.";
								aType = "quit";
								break;
							}
						}
					}
					if (aType == "quit")
					{
						break;
					}
					cout << "Account type:  " << aType << "\n";
					activeAccounts.push_back(new CheckingAccount(name));
					//record something?

				}
				else if (temp == "2")
				{
					aType = "Saving Account";
					cout << "Account type:  " << aType << "\n";
					for (size_t i = 0; i < activeAccounts.size(); i++)
					{
						if (activeAccounts[i]->getName() == name)
						{
							if (activeAccounts[i]->getAcc() == aType)
							{
								cout << "\n Warning: \nThis name/account combination already exists. \nThis transaction will not be recorded.";
								aType = "quit";
								break;
							}
						}
					}
					if (aType == "quit")
					{
						break;
					}
					activeAccounts.push_back(new SavingAccount(name));
				}
				else if (temp == "3")
				{
					aType = "CD Account";
					cout << "Account type:  " << aType << "\n";
					for (size_t i = 0; i < activeAccounts.size(); i++)
					{
						if (activeAccounts[i]->getName() == name)
						{
							if (activeAccounts[i]->getAcc() == aType)
							{
								cout << "\n Warning: \nThis name/account combination already exists. \nThis transaction will not be recorded.";
								aType = "quit";
								break;
							}
						}
					}
					if (aType == "quit")
					{
						break;
					}
					activeAccounts[activeAccounts.size() - 1]->accCreation();
					size_t rate;
					uInput.clear();
					if (aType == "CD Account")
					{
						cout << "Please input interest rate (in precentage):  ";
						while (true)
						{
							while (uInput.empty())
							{
								getline(cin, uInput);
							}
							if (uInput == "$$")
							{
								break;
							}
							rate = stoi(uInput);
							if (rate < 100)
							{
								break;
							}
							cout << rate << " is an invalid percentage.";
						}
						if (uInput == "$$")
						{
							cout << "Ending transaction. This transaction will not be recorded.";
							break;
						}
						activeAccounts.push_back(new CDAccount(name, rate));
					}
				}
				else
				{
					aType = "Money Market Account";
					for (size_t i = 0; i < activeAccounts.size(); i++)
					{
						if (activeAccounts[i]->getName() == name)
						{
							if (activeAccounts[i]->getAcc() == aType)
							{
								cout << "\n Warning: \nThis name/account combination already exists. \nThis transaction will not be recorded.";
								aType = "quit";
								break;
							}
						}
					}
					if (aType == "quit")
					{
						break;
					}
					cout << "Account type:  " << aType << "\n";
					activeAccounts.push_back(new MoneyMarketAccount(name));
				}

				//Make the account type.
				break;

			case '2':
				temp.clear();
				cout << "We will be depositing to an existing account.  To cancel, input \"$$\" at any input.\n"
					<< "Please input name. "
					<< "Name:  ";
				while (temp.empty())
				{
					getline(cin, temp);
				}
				if (temp == "$$")
				{
					cout << "Ending transaction. This transaction will not be recorded.";
					break;
				}
				cout << "\nExcellent. What kind of account type?\n"
					<< "(1)Checking Account, (2)Saving Account, (3)CD Account, (4) Money Market Account\n\n";
				name = temp;
				temp.clear();
				uInput.clear();
				while (temp != "1" && temp != "2" && temp != "3" && temp != "4")
				{
					if (uInput == "$$")
					{
						break;
					}
					if (!uInput.empty())
					{
						cout << "Please input a numerical value to choose account.";
					}
					uInput.clear();
					while (uInput.empty())
					{
						getline(cin, uInput);
					}
					temp = uInput;

				}
				if (uInput == "$$")
				{
					cout << "Ending transaction. This transaction will not be recorded.";
					break;
				}
				aType;
				if (temp == "1")
				{
					aType = "Checking Account";
				}
				else if (temp == "2")
				{
					aType = "Saving Account";
				}
				else if (temp == "3")
				{
					aType = "CD Account";
				}
				else
				{
					aType = "Money Market Account";
				}
				cout << "Account type:  " << aType << "\n";
				cout << "Input deposit amount:  ";
				uInput.clear();
				while (uInput.empty())
				{
					getline(cin, uInput);
				}
				try
				{
					money = stod(uInput);
				}
				catch (const out_of_range&)
				{
					cout << "Invalid input. Input is out of range. \n Ending transaction. This transaction will not be recorded.";
					break;
				}
				catch (const invalid_argument&)
				{
					cout << "Invalid input. Input is not a number. \n Ending transaction. This transaction will not be recorded.";
					break;
				}
				accExists = false;
				for (size_t i = 0; i < activeAccounts.size(); i++)
				{
					if (activeAccounts[i]->getName() == name)
					{
						if (activeAccounts[i]->getAcc() == aType)
						{
							activeAccounts[i]->deposit(money);
							accExists = true;
						}
					}
				}
				if (!accExists) //invalid acount/name combination
				{
					cout << " This account/name combination is invalid. Ending transaction.\n This transaction will not be recorded.";
				}
				accExists = false;
				break;
			case '3':
				//calls withdrawal function
				temp.clear();
				cout << "We will be withdrawing to an existing account.\n"
					<< "Please input name. "
					<< "Name:  ";
				while (temp.empty())
				{
					getline(cin, temp);
				}
				cout << "Excellent. What kind of account type?\n"
					<< "(1)Checking Account, (2)Saving Account, (3)CD Account, (4) Money Market Account\n\n";
				if (temp == "$$")
				{
					cout << "Ending transaction. This transaction will not be recorded.";
					break;
				}
				name = temp;
				temp.clear();
				uInput.clear();
				while (temp != "1" && temp != "2" && temp != "3" && temp != "4")
				{
					if (uInput == "$$")
					{
						break;
					}
					if (!uInput.empty())
					{
						cout << "Please input a numerical value to choose account.";
					}
					uInput.clear();
					while (uInput.empty())
					{
						getline(cin, uInput);
					}
					temp = uInput;

				}
				if (uInput == "$$")
				{
					cout << "Ending transaction. This transaction will not be recorded.";
					break;
				}
				aType;
				if (temp == "1")
				{
					aType = "Checking Account";
				}
				else if (temp == "2")
				{
					aType = "Saving Account";
				}
				else if (temp == "3")
				{
					aType = "CD Account";
				}
				else
				{
					aType = "Money Market Account";
				}
				cout << "Account type:  " << aType << "\n";
				cout << "Input withdraw amount:  ";
				uInput.clear();
				while (uInput.empty())
				{
					getline(cin, uInput);
				}
				try
				{
					money = stod(uInput);
				}
				catch (const out_of_range&)
				{
					cout << "Invalid input. Input is out of range. \n Ending transaction. This transaction will not be recorded.";
					break;
				}
				catch (const invalid_argument&)
				{
					cout << "Invalid input. Input is not a number. \n Ending transaction. This transaction will not be recorded.";
					break;
				}
				for (size_t i = 0; i < activeAccounts.size(); i++)
				{
					if (activeAccounts[i]->getName() == name)
					{
						if (activeAccounts[i]->getAcc() == aType)
						{
							activeAccounts[i]->withdraw(money);
							accExists = true;
						}
					}
				}
				if (!accExists) //invalid acount/name combination
				{
					cout << " This account/name combination is invalid. Ending transaction.\n This transaction will not be recorded.";
					break;
				}
				accExists = false;
				// withdraw funds once account is found
				break;
			case '4':
				//calls transfer/deposit. Must be a "transfer" transaction
				temp.clear();
				cout << "We will be withdrawing to an existing account.\n"
					<< "Please input name. "
					<< "Name:  ";
				while (temp.empty())
				{
					getline(cin, temp);
				}
				cout << "Excellent. What kind of account type?\n"
					<< "(1)Checking Account, (2)Saving Account, (3)CD Account, (4) Money Market Account\n\n";
				if (temp == "$$")
				{
					cout << "Ending transaction. This transaction will not be recorded.";
					break;
				}
				name = temp;
				temp.clear();
				uInput.clear();
				while (temp != "1" && temp != "2" && temp != "3" && temp != "4")
				{
					if (uInput == "$$")
					{
						break;
					}
					if (!uInput.empty())
					{
						cout << "Please input a numerical value to choose account.";
					}
					uInput.clear();
					while (uInput.empty())
					{
						getline(cin, uInput);
					}
					temp = uInput;

				}
				if (uInput == "$$")
				{
					cout << "Ending transaction. This transaction will not be recorded.";
					break;
				}
				aType;
				if (temp == "1")
				{
					aType = "Checking Account";
				}
				else if (temp == "2")
				{
					aType = "Saving Account";
				}
				else if (temp == "3")
				{
					aType = "CD Account";
				}
				else
				{
					aType = "Money Market Account";
				}
				cout << "Account type:  " << aType << "\n";
				accExists = false;
				for (size_t i = 0; i < activeAccounts.size(); i++)
				{
					if (activeAccounts[i]->getName() == name)
					{
						if (activeAccounts[i]->getAcc() == aType)
						{
							accExists = true;
						}
					}
				}
				if (!accExists) //invalid acount/name combination
				{
					cout << " This account/name combination is invalid. Ending transaction.\n This transaction will not be recorded.";
					break;
				}
				accExists = false;
				// check from account balance. if not enough money, exit
				tHold = 0.00;
				//tHold stores amount to withdraw.
				//repeat with target.
				temp.clear();
				cout << "Funds acquired. Please select target account of transfer\n"
					<< "Please input name of account holder. "
					<< "Name:  ";
				while (temp.empty())
				{
					getline(cin, temp);
				}
				cout << "Excellent. What kind of account type for this individual?\n"
					<< "(1)Checking Account, (2)Saving Account, (3)CD Account, (4) Money Market Account\n\n";
				if (temp == "$$")
				{
					cout << "Ending transaction. This transaction will not be recorded.";
					break;
				}
				targetName = temp;
				temp.clear();
				uInput.clear();
				while (temp != "1" && temp != "2" && temp != "3" && temp != "4")
				{
					if (uInput == "$$")
					{
						break;
					}
					if (!uInput.empty())
					{
						cout << "Please input a numerical value to choose account.";
					}
					uInput.clear();
					while (uInput.empty())
					{
						getline(cin, uInput);
					}
					temp = uInput;

				}
				if (uInput == "$$")
				{
					cout << "Ending transaction. This transaction will not be recorded.";
					break;
				}
				if (temp == "1")
				{
					targetAccount = "Checking Account";
				}
				else if (temp == "2")
				{
					targetAccount = "Saving Account";
				}
				else if (temp == "3")
				{
					targetAccount = "CD Account";
				}
				else
				{
					targetAccount = "Money Market Account";
				}
				cout << "Account type:  " << targetAccount <<"\n";
				accExists = false;
				for (size_t i = 0; i < activeAccounts.size(); i++)
				{
					if (activeAccounts[i]->getName() == targetName)
					{
						if (activeAccounts[i]->getAcc() == targetAccount)
						{
							accExists = true;
						}
					}
				}
				if (!accExists) //invalid acount/name combination
				{
					cout << " This account/name combination is invalid. Ending transaction.\n This transaction will not be recorded.";
					break;
				}
				accExists = false;
				uInput.clear();
				cout << "Input transfer amount:  ";
				while (uInput.empty())
				{
					getline(cin, uInput);
				}
				try
				{
					money = stod(uInput);
				}
				catch (const out_of_range&)
				{
					cout << "Invalid input. Input is out of range. \n Ending transaction. This transaction will not be recorded.";
					break;
				}
				catch (const invalid_argument&)
				{
					cout << "Invalid input. Input is not a number. \n Ending transaction. This transaction will not be recorded.";
					break;
				}
				//execute twithdrawal
				for (size_t i = 0; i < activeAccounts.size(); i++)
				{
					if (activeAccounts[i]->getName() == name)
					{
						if (activeAccounts[i]->getAcc() == aType)
						{
							activeAccounts[i]->tWithdraw(money);
						}
					}
				}
				//execute tdeposit
				for (size_t i = 0; i < activeAccounts.size(); i++)
				{
					if (activeAccounts[i]->getName() == targetName)
					{
						if (activeAccounts[i]->getAcc() == targetAccount)
						{
							activeAccounts[i]->tDeposit(money);
						}
					}
				}
				break;
			case '5':
				//returns account balance
				temp.clear();
				cout << "We will be looking at the balance of an existing account.  To cancel, input \"$$\" at any input.\n"
					<< "Please input name. "
					<< "Name:  ";
				while (temp.empty())
				{
					getline(cin, temp);
				}
				if (temp == "$$")
				{
					cout << "Ending transaction. This transaction will not be recorded.";
					break;
				}
				cout << "\nExcellent. What kind of account type?\n"
					<< "(1)Checking Account, (2)Saving Account, (3)CD Account, (4) Money Market Account\n\n";
				name = temp;
				temp.clear();
				uInput.clear();
				while (temp != "1" && temp != "2" && temp != "3" && temp != "4")
				{
					if (uInput == "$$")
					{
						break;
					}
					if (!uInput.empty())
					{
						cout << "Please input a numerical value to choose account.";
					}
					uInput.clear();
					while (uInput.empty())
					{
						getline(cin, uInput);
					}
					temp = uInput;

				}
				if (uInput == "$$")
				{
					cout << "Ending transaction. This transaction will not be recorded.";
					break;
				}
				aType;
				if (temp == "1")
				{
					aType = "Checking Account";
				}
				else if (temp == "2")
				{
					aType = "Saving Account";
				}
				else if (temp == "3")
				{
					aType = "CD Account";
				}
				else
				{
					aType = "Money Market Account";
				}
				cout << "Account type:  " << aType << "\n";
				accExists = false;
				for (size_t i = 0; i < activeAccounts.size(); i++)
				{
					if (activeAccounts[i]->getName() == name)
					{
						if (activeAccounts[i]->getAcc() == aType)
						{
							tHold = activeAccounts[i]->getBalance();
							cout << "Balance:  "<<setprecision(2) <<fixed <<tHold;
							accExists = true;
						}
					}
				}
				tHold = 0.0;
				if (!accExists) //invalid acount/name combination
				{
					cout << " This account/name combination is invalid. Ending transaction.\n This transaction will not be recorded.";
					break;
				}
				accExists = false;
				break;
			case '6':
				// prints transaction for specified account
				// print transaction is more in line with the email sent to the TA Miss Fan
				temp.clear();
				cout << "We will be printing transaction history for a specified account.  To cancel, input \"$$\" at any input.\n"
					<< "Please input name. "
					<< "Name:  ";
				while (temp.empty())
				{
					getline(cin, temp);
				}
				if (temp == "$$")
				{
					cout << "Ending transaction. This transaction will not be recorded.";
					break;
				}
				cout << "\nExcellent. What kind of account type?\n"
					<< "(1)Checking Account, (2)Saving Account, (3)CD Account, (4) Money Market Account\n\n";
				name = temp;
				temp.clear();
				uInput.clear();
				while (temp != "1" && temp != "2" && temp != "3" && temp != "4")
				{
					if (uInput == "$$")
					{
						break;
					}
					if (!uInput.empty())
					{
						cout << "Please input a numerical value to choose account.";
					}
					uInput.clear();
					while (uInput.empty())
					{
						getline(cin, uInput);
					}
					temp = uInput;

				}
				if (uInput == "$$")
				{
					cout << "Ending transaction. This transaction will not be recorded.";
					break;
				}
				if (temp == "1")
				{
					aType = "Checking Account";
				}
				else if (temp == "2")
				{
					aType = "Saving Account";
				}
				else if (temp == "3")
				{
					aType = "CD Account";
				}
				else
				{
					aType = "Money Market Account";
				}
				cout << "Account type:  " << aType << "\n";
				accExists = false;
				for (size_t i = 0; i < activeAccounts.size(); i++)
				{
					if (activeAccounts[i]->getName() == name)
					{
						if (activeAccounts[i]->getAcc() == aType)
						{
							activeAccounts[i]->printTransactions();
							accExists = true;
						}
					}
				}
				if (!accExists) //invalid acount/name combination
				{
					cout << " This account/name combination is invalid. Ending transaction.\n This transaction will not be recorded.";
					break;
				}
				accExists = false;
				//print transactions
				break;
			case '7':
				cout << "Calculating available bank funds: \n\n";
				tHold = 0.0;
				for (size_t i = 0; i < activeAccounts.size(); i++)
				{

					activeAccounts[i]->computeBankBalance();
					tHold += activeAccounts[i]->getBalance();

				}
				cout << "The current available funds for Aubie Bank:  " << setprecision(2) << fixed <<tHold;
				tHold = 0.0;
				break;
			case '8':
				active = false;
				cout << "Terminating program.";
				break;
			default:
				cout << "Please input a valid numerical value.";
				break;
			}
		}
		return 0;
	}
};