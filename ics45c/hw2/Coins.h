#include<iostream>
using namespace std;
const int CENTS_PER_QUARTER=25,CENTS_PER_DIME=10,CENTS_PER_NICKEL=5;
class Coins
{
public:
	Coins(int q, int d, int n, int p)
	{
		if(q<0 || d<0 || n<0|| p<0)
			cout<<"the number of any type of coin cannot smaller than 0"<<endl;
		quarters=q<0?0:q;
		dimes=d<0?0:d;
		nickels=n<0?0:n;
		pennies=p<0?0:p;
	}
	
	void deposit_coins(Coins &c)
	{
		quarters+=c.quarters,c.quarters=0;
		dimes+=c.dimes,c.dimes=0;
		nickels+=c.nickels,c.nickels=0;
		pennies+=c.pennies,c.pennies=0;
	}

	
	bool has_exact_change_for_cents(int amount_in_cents)
	{
		int total=total_value_in_cents();
		if(total<amount_in_cents)return false;
		if(total==amount_in_cents)return true;
		if(pennies>=amount_in_cents)
			return true;
		return recursive_search(amount_in_cents,quarters,dimes,nickels,pennies);
	}
	
	Coins extract_exact_change(int amount_in_cents)
	{
		Coins c(0,0,0,0);
		recursive_search(amount_in_cents,quarters,dimes,nickels,pennies,&c);
		return c;
	}

	int total_value_in_cents()
	{
		return quarters*CENTS_PER_QUARTER+dimes*CENTS_PER_DIME+nickels*CENTS_PER_NICKEL+pennies;
	}

	void print(ostream &out)
	{
		out<<quarters<<" quarters, "<<dimes<<" dimes, "<<nickels<<" nickels, "<<pennies<<" pennies.";
	}
private:
	int quarters,dimes,nickels,pennies;
    	void Coins_extract(int a,int q, int d,int n, int p, Coins* c)
	{
		c->quarters=quarters-q;
		quarters=q;
		c->dimes=dimes-d;
		dimes=d;
		c->nickels=nickels-n;
		nickels=n;
		c->pennies=a;
		pennies=p-a;
		
	}

	bool recursive_search(int a, int q, int d, int n, int p, Coins* c=NULL)
	{
		if(p>=a)
		{
			if(c)
				Coins_extract(a,q,d,n,p,c);
			return true;
		}
		if(q && a>=CENTS_PER_QUARTER && recursive_search(a-CENTS_PER_QUARTER,q-1,d,n,p,c))return true;
		if(d && a>=CENTS_PER_DIME && recursive_search(a-CENTS_PER_DIME,q,d-1,n,p,c))return true;
		if(n && a>=CENTS_PER_NICKEL && recursive_search(a-CENTS_PER_NICKEL,q,d,n-1,p,c))return true;
		return false;
	}

};

ostream &operator <<(ostream &out, Coins &c)
{
	c.print(out);
	return out;
}
