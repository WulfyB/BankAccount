#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "BankAccount.h"

using namespace std;
class CDAccount :public BankAccount
{
private:
	double fee;
	int interestRate;
public:
	CDAccount() = delete;
	CDAccount(string tName, int tRate) : BankAccount(tName)
	{
		interestRate = tRate;
		accountType = "CD Account";
	}
	int getInterestRate()
	{
		return interestRate;
	}
	virtual void accCreation() override
	{
		transactions.push_back("Transaction 1: \n Account Created \n Name:  " + this->getName()
			+ " \n Account Type:  " + this->getAcc() + "\n\n\n");
		if (this->getAcc() == "CD Account")
		{
			transactions[0] += to_string(this->getInterestRate());
		}
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
				fee = balance*interestRate / 100;
				fee /= 4;
				balance -= temp;
				balance -= fee;
				numTrans += 1;
				transactions.push_back("Transaction " + to_string(numTrans + 1) + ": \n Withdraw \n Name:  " + this->getName()
					+ " \n Account Type:  " + this->getAcc() + "\n Withdrawal amount:  "
					+ to_string(temp) + "\n Fee:  " + to_string(fee) + "\n\n\n");
			}
		}

	}
	virtual void tWithdraw(double temp) override
	{
		fee = balance*interestRate/100;
		fee /= 4;
		balance -= temp;
		balance -= fee;
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