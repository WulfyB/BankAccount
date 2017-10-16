#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "BankAccount.h"
using namespace std;
class CheckingAccount :public BankAccount
{
private:
	double fee; //fee based on withdrawal
public:
	CheckingAccount() = delete;
	CheckingAccount(string tName) : BankAccount(tName)
	{
		fee = 2.50;
		accountType = "Checking Account";
	}
	virtual void withdraw(double temp) override
	{
		if (temp < 0.0)
		{
			cout << "Negative amount cannot be removed via withdrawal. Consider using deposit.";
			cout << "The attempted transaction will not be recorded.";
		}
		else
		{
			if (temp > balance)
			{
				cout << "Insufficient funds! Transaction canceled! \n\n";

			}
			else
			{
				balance -= temp;
				numTrans++;
				if (balance < 500)
				{
					balance -= fee;
					transactions.push_back("Transaction " + to_string(numTrans + 1) + ": \n Withdraw \n Name:  " + this->getName()
						+ " \n Account Type:  " + this->getAcc() + "\n Withdrawal amount:  "
						+ to_string(temp) + "\n Fee:  " + to_string(fee) + "\n\n\n");
				}
				transactions.push_back("Transaction " + to_string(numTrans + 1) + ": \n Withdraw \n Name:  " + this->getName()
					+ " \n Account Type:  " + this->getAcc() + "\n Withdrawal amount:  "
					+ to_string(temp) + "\n Fee: N/A \n\n\n");
			}
		}

	}
	virtual void tWithdraw(double temp) override
	{
		balance -= temp;
		numTrans += 1;
		transactions.push_back("Transaction " + to_string(numTrans + 1) + ": \n Outgoing Transfer \n Name:  " + this->getName()
			+ " \n Account Type:  " + this->getAcc() + "\n \n");
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