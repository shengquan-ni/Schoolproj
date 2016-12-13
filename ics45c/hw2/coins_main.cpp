#include "Coins.h"

int main()
{
	Coins pocket(5,3,6,8),piggyBank(50,50,50,50);
	cout<<"My pocket has "<<pocket<<endl;
	cout<<"My piggyBank has "<<piggyBank<<endl;
	Coins cost= pocket.extract_exact_change(68);
	cout<<"The bag of Chips cost me"<<cost<<endl;
	cout<<"My pocket has "<<pocket<<endl;
	pocket.deposit_coins(piggyBank);
	cout<<"After I transfer a bunch of coins from my piggyBank"<<endl;
	cout<<"My pocket has "<<pocket<<endl;
	cout<<"My piggyBank has "<<piggyBank<<endl;
	Coins change_on_sofa(10,20,30,40);
	cout<<"There is some coins on my sofa:"<<change_on_sofa<<endl;
	piggyBank.deposit_coins(change_on_sofa);
	cout<<"After I put the change in my piggyBank"<<endl;
	cout<<"My piggyBank has $"<<piggyBank.total_value_in_cents()/(float)100<<endl;
}
