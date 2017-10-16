//Bank Account parent class of Saving
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <cmath> 
using namespace std;
class BankAccount
{
private:
	string name; //owner of the account

	
protected:
	vector<string> transactions; //vector of all transactions by this account.
	double balance = 0; //balance of the account
	int numTrans = 0; //stores number of transactions for an account
	string accountType; 	 //type of account
public:
	BankAccount::BankAccount() = delete;
	BankAccount::BankAccount(string tName)
	{
		name = tName;
	}
	string getName()
	{
		return name;
	}
	string getAcc()
	{
		return accountType;
	}
	virtual void accCreation()
	{
		transactions.push_back("Transaction #1: \n Account Created \n Name:  " + this->getName()
			+ " \n Account Type:  " + this->getAcc() + "\n \n\n");
		numTrans += 1;
		
	}
	double getBalance()
	{
		numTrans += 1;
		transactions.push_back( "Transaction " + to_string(numTrans + 1) + ": \n Incoming Transfer \n Name:  " + this->getName()
			+ " \n Account Type:  " + this->getAcc() + "\n Account Balance:  " + to_string(balance) + "\n\n\n");
		return balance;
	}
	double tGetBalance()
	{
		return balance;
	}
	void tDeposit(double temp) 
	{
		balance += temp;
		numTrans += 1; //lowers number of transactions as a correction to withdrawal
		transactions.push_back("Transaction " + to_string(numTrans + 1) +": \n Incoming Transfer \n Name:  " + this->getName()
			+ " \n Account Type:  " + this->getAcc() + "\n Transfer amount:  " + to_string(temp) + "\n\n\n");
	}
	void deposit(double temp)
	{
		if (temp < 0.0)
		{
			cout << "Negative amount cannot be added via deposit. Consider using withdrawal.";
			cout << "The attempted transaction will not be recorded.";
		}
		else
		{
			balance += temp;
			numTrans += 1;
			transactions.push_back("Transaction " + to_string(numTrans + 1) + ": \n Deposit \n Name:  " + this->getName()
				+ " \n Account Type:  " + this->getAcc() + "\n Deposit amount:  " + to_string(temp) + "\n\n\n");
		}
	}
	virtual void withdraw(double temp) = 0; //pure virtual function for withdraw
	virtual void tWithdraw(double temp) = 0; //pure virutal function for transfer based withdrawals
	virtual void printTransactions() = 0;//pure virtual function for printTransaction
	virtual void computeBankBalance() = 0; //pure virtual function for computerBankBalance
};