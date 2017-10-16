#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "BankAccount.h"
using namespace std;
class SavingAccount :public BankAccount
{
public:
	SavingAccount() = delete;
	SavingAccount(string tName) : BankAccount(tName)
	{
		accountType = "Saving Account";
	}
	virtual void withdraw(double temp) override
	{
		if (temp > balance)
		{
			cout << "Insufficient funds! Transaction canceled! \n\n";

		}
		else
		{
			if (temp < 0.0)
			{
				cout << "Negative amount cannot be removed via withdrawal. Consider using deposit.";
				cout << "The attempted transaction will not be recorded.";
			}
			else
			{
				balance -= temp;
				numTrans += 1;
				transactions.push_back("Transaction " + to_string(numTrans + 1) + ": \n Withdraw \n Name:  " + this->getName()
					+ " \n Account Type:  " + this->getAcc() + "\n Withdrawal amount:  " + to_string(temp) + "\n\n\n");
			}
		}

	}
	virtual void tWithdraw(double temp) override
	{
		balance -= temp;
		numTrans += 1; 
		transactions.push_back("Transaction " + to_string(numTrans + 1) + ": \n Outgoing Transfer \n Name:  " + this->getName()
			+ " \n Account Type:  " + this->getAcc() + "\n Transfer amount:  " + to_string(temp) + "\n\n\n");
	}
	virtual void printTransactions()
	{
		for (int i = 0; i < numTrans; i++)
		{
			cout << transactions[i];
		}
	}
	virtual void computeBankBalance()
	{
		for (int i = 0; i < numTrans; i++)
		{
			cout << transactions[i];
		}
		cout << this->getName() << "'s Account Total:  " << this->getBalance();
	}
};