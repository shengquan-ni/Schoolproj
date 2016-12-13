#include "Coins.h"
#include <limits>
void try_input(int &var)
{
	while(1)
	{
		cin>>var;
		if(cin.good())
		{
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			return;
		}
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout<<"invalid input"<<endl;
		}
	}
}

int main()
{
	Coins myCoins(0,0,0,0);
	while(1)
	{
		cout<<"What do you want to do with your coins?"<<endl;
		cout<<"(1)deposit"<<endl;
		cout<<"(2)extract"<<endl;
		cout<<"(3)print balance"<<endl;
		cout<<"(4)exit"<<endl;
		cout<<"please enter the command number"<<endl;
		int cmd;
		cin>>cmd;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		int q,d,n,p,totalcents;
		switch(cmd)
		{
			case 1:
			{
				cout<<"enter how many quarters do you want to deposit"<<endl;
				try_input(q);
				cout<<"enter how many dimes do you want to deposit"<<endl;
				try_input(d);
				cout<<"enter how many nickels do you want to deposit"<<endl;
				try_input(n);
				cout<<"enter how many pennies do you want to deposit"<<endl;
				try_input(p);
				Coins temp_coins(q,d,n,p);
				myCoins.deposit_coins(temp_coins);
				break;
			}
			case 2:
				cout<<"enter how many cents do you want to extract"<<endl;
				try_input(totalcents);
				if(myCoins.has_exact_change_for_cents(totalcents))
					myCoins.extract_exact_change(totalcents);
				else
					cout<<"insufficient funds"<<endl;
				break;
			case 3:
				cout<<"your balance:$"<<myCoins.total_value_in_cents()/100.0<<endl;
				cout<<myCoins<<endl;
				break;
			case 4:
				return 0;
			default:
				cout<<"invaild command"<<endl;
				break;
		}

	}
}
