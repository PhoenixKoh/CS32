//#include <iostream>
//#include <string>
//using namespace std;

// Your declarations and implementations would go here
// Investment
class Investment
{
public:
	Investment(std::string name, int purchasePrice)
		: m_name(name), m_purchasePrice(purchasePrice)
	{

	}

	virtual ~Investment() // destructor of base class MUST be virtual
	{
		
	}

	std::string name() const // non-virtual
	{
		return m_name;
	}

	int purchasePrice() const // non-virtual
	{
		return m_purchasePrice;
	}

	virtual std::string description() const = 0; // pure virtual

	virtual bool fungible() const // non-pure virtual
	{
		return false;
	}

private:
	std::string m_name;
	int m_purchasePrice; // required type
};
// Painting
class Painting : public Investment
{
public:
	Painting(std::string name, int purchasePrice)
		: Investment(name, purchasePrice)
	{

	}

	virtual ~Painting()
	{
		cout << "Destroying " << name() << ", a painting" << endl;
	}

	virtual std::string description() const 
	{
		return "painting";
	}
};
// Stock
class Stock : public Investment
{
public:
	Stock(std::string name, int value, std::string tickerSymbol)
		: Investment(name, value)
	{
		m_tickerSymbol = tickerSymbol;
	}

	virtual ~Stock()
	{
		cout << "Destroying " << name() << ", a stock holding" << endl;
	}

	virtual std::string description() const 
	{
		string dp = "stock trading as ";
		dp += m_tickerSymbol;
		return dp;
	}

	virtual bool fungible() const 
	{
		return true;
	}

private:
	std::string m_tickerSymbol;
};
// House
class House : public Investment
{
public:
	House(std::string name, int purchasePrice)
	: Investment(name, purchasePrice)
	{

	}

	virtual ~House()
	{
		cout << "Destroying the house " << name() << endl;
	}

	virtual std::string description() const 
	{
		return "house";
	}
};

//void display(const Investment* inv)
//{
//	cout << inv->name();
//	if (inv->fungible())
//		cout << " (fungible)";
//	cout << ": " << inv->description() << " bought for $" << inv->purchasePrice() << endl;
//}
//
//int main()
//{
//	Investment* portfolio[4];
//	portfolio[0] = new Painting("Salvator Mundi", 450300000);
//	// Stock holdings have a name, value, and ticker symbol
//	portfolio[1] = new Stock("Alphabet", 100000, "GOOGL");
//	portfolio[2] = new Stock("Symantec", 50000, "SYMC");
//	portfolio[3] = new House("4 Privet Drive", 660000);
//
//	for (int k = 0; k < 4; k++)
//		display(portfolio[k]);
//
//	// Clean up the investments before exiting
//	cout << "Cleaning up" << endl;
//	for (int k = 0; k < 4; k++)
//		delete portfolio[k];
//}