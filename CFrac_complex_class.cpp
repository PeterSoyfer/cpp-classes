//Soyfer_complex_class

#include <iostream>

using namespace std;

bool signum(int);
int gcd(int, int);


class CFrac
{
private:
	bool sign; int a, b; //false (0) if negative, true (1) if zero or positive
public:

//constructors and destructors

	CFrac() //SetZero analogue
	{
		a = 0; b = 1; sign = true;
	}

	CFrac(const int& nom, const int& denum)
	{
		if(denum == 0)
		{
			cout<<"\nBan: division by zero"<<endl;
		}
		else {a = nom; b = denum; sign = signum(nom*denum);}
	}

	CFrac(const CFrac &r)
	{
		a = r.a; b = r.b; sign = r.sign;
	}

	~CFrac() //calling destructor by typing "t.~CFrac();"
	{
		a = 0; b = 1; sign = true;
	}

//operators overload

	CFrac& operator=(const CFrac& r)
	{
		a = r.a; b = r.b; sign = r.sign;
		this->norm();
		return *this;
	}

	CFrac& operator+(const CFrac& r)
	{
		this->a = this->a*r.b + this->b*r.a; this->b = this->b*r.b;
		this->sign = signum(this->a*this->b);
		this->norm();
		return *this;
	}

	CFrac operator-(const CFrac& r) const
	{
		CFrac t;
		t.a = a*r.b - b*r.a; t.b = b*r.b;
		t.sign = signum(t.a*t.b);
		t.norm();
		return t;
	}

	CFrac operator*(const CFrac& r) const
	{
		CFrac t;
		t.a = a*r.a; t.b = b*r.b;
		t.sign = signum(t.a*t.b);
		t.norm();
		return t;
	}

	CFrac operator/(const CFrac& r) const
	{
		CFrac t;
		if (r.a == 0)
		{
			t.a = 0; t.b = 1; t.sign = true;
			cout<<"\nBan: division by zero. Result is set by default 0/1."<<endl;
		}
		else
		{
			t.a = a*r.b; t.b = b*r.a;
			t.sign = signum(t.a*t.b);
			t.norm();
		}
		return t;
	}

//other functions-methods of class according to the task

	//working with parameters of class
//	void setnom(int);
//	void setdenum(int);
//	void setsign(bool);
	int getnom();
	int getdenum();
	void norm();

	//methods-functions according to task
	void print();
	int frcmpr(const CFrac&);
	bool isproper();
	int wholepart();
	void period();

	friend void infrac(CFrac *);
};

//void CFrac::setnom(int nom) {a = nom;}

//void CFrac::setdenum(int denum) {b = denum;}

//void CFrac::setdenum(bool sgn) {sign = sgn;}

int CFrac::getnom() {return a;}

int CFrac::getdenum() {return b;}

void CFrac::norm() {int dvsr = gcd(a,b); a /= dvsr; b /= dvsr;}

void CFrac::print()
{
	this->norm();
	char sgn;
	if(sign) sgn = ' ';
	else sgn = '-';
	cout<<' '<<sgn<<abs(a)<<'/'<<abs(b)<<' ';
}

void infrac(CFrac *r)
{

	int frac[2] = {0,0}, sgn[2] = {1,1}, input, index; bool slash;
	index = 0; slash = false;

	cout<<"\nInput CFrac a/b (use '/' slash to separate): ";
	for(;;)
	{
		input=getchar(); //cout<<'\n'<<input<<endl;

		if(input==45) //char '-'
		{
			if ((slash==false)&&(frac[0]==0)) {sgn[0] = -1;}
			if ((slash==true)&&(frac[1]==0)) {sgn[1] = -1;}
		}

		if((input>=48)&&(input<58))
		{
			input -= 48; //input == cypher 0...9
			frac[index] *= 10; frac[index] += input;
		}

		if ((input==47)&&(slash==false)) {slash=true; index = 1;}

		if (input==10) {break;}
	}

	if (frac[1]!=0)
	{
		r->a = frac[0]*sgn[0]; r->b = frac[1]*sgn[1]; r->norm();
		r->sign = signum(r->a*r->b);
	}
	else
	{
		r->a = 0; r->b = 1; r->sign = true;
		cout<<"\nBan: incorrect fraction input."<<endl;
	}

	if ((r->a==0)&&(r->b==1)) {cout<<"\nCFrac was set 0/1."<<endl;}
}

int CFrac::frcmpr(const CFrac& r) //ans: 1 if '>', 2 if '<', 0 if '=='
{
	int ans, res, div;

	if (r.a == 0)
	{
		if (this->a == 0) ans = 0;
		else if (this->sign) ans = 1;
		else ans = 2;
	}

	else
	{
		CFrac t = *this/r;

		div = t.a/t.b; res = t.a % t.b;
		if (this->sign == r.sign)
		{
			switch(div)
			{
				case 0: ans = 2; break;
				case 1: if (res) ans = 1; else ans = 0; break;
				default: ans = 1; break;
			}
			if ((this->sign==false)&&(ans!=0)) {ans = 1 + ans%2;} //this->sign == r.sign < 0
		}

		else
		{
			if (this->sign) ans = 1; //r1 >= 0 => r2 < 0 => r1 > r2
			else ans = 2;
		}
	}

	return ans;
}

bool CFrac::isproper()
{
	bool q;
	if (abs(this->a) >= abs(this->b)) q = false;
	else q = true;
	return q;
}

int CFrac::wholepart()
{
	int whole;
	whole = this->a/this->b;
	return whole;
}

void CFrac::period()
{
	int num,denom,preper; //num - numerator, denom - denominator;
	num = abs(this->a); denom = abs(this->b);
	num /= gcd(num,denom); denom /= gcd(num,denom);

	int dnm = denom;
	int s = dnm % 2; int i2 = 0;
	while (s == 0) {dnm /= 2; s = dnm % 2; i2++;}

	s = dnm % 5; int i5 = 0;
	while (s == 0) {dnm /= 5; s = dnm % 5; i5++;}

	if (i2 > i5) {preper = i2;}
	else {preper = i5;}

	int perlen = 1; int p = 10;
	while (p != 1)
	{
		p = (10*p) % dnm;
		if (p == 0) {break;}
		perlen++;
	}

	char sgn;
	if(this->sign) {sgn = ' ';}
	else {sgn = '-';}

	this->print();
	cout<<" = "<<sgn<<num/denom<<".";

	int a = num % denom;
	for (int i = 0; i < preper; i++)
	{
		cout<<10*a/denom;
		a = (10*a) % denom;
	}

	cout<<"(";

	for (int i = 0; i < perlen; i++)
	{
		cout<<10*a/denom;
		a = (10*a) % denom;
	}

	cout<<")"<<endl;
}

//----------------------------
int main()
{
	cout<<"\ncr - Create a/b CFrac."<<endl;
	cout<<"cln - Clean CFrac (make it by default 0/1)."<<endl;
//	cout<<"chparam - Change parameters of CFrac: sign, numerator, denominator."<<endl;
	cout<<"pr - Print current value of CFrac."<<endl;
	cout<<"\nsm - Sum 2 CFracs."<<endl;
	cout<<"sb - Subtract 2 CFracs."<<endl;
	cout<<"mltpl - Multiply 2 CFracs."<<endl;
	cout<<"dvd - Divide 2 CFracs."<<endl;
	cout<<"cmpr - Compare 2 CFracs (>, <, ==)."<<endl;
	cout<<"\nprd - Obtain the knowledge about the period of CFrac."<<endl;
	cout<<"prpr - Obtain the knowledge: whether CFrac is proper or not."<<endl;
	cout<<"whl - Obtain the knowledge about whole part of CFrac."<<endl;
	cout<<"\nhelp - Help (you'll see this list again)."<<endl;
	cout<<"joke - Another little joke for real connoisseurs."<<endl;
	cout<<"exit - Exit."<<endl;

	string cmd; CFrac g;

	for(;;)
	{
		cout<<"\nType command: ";
		cin>>cmd;
		
		if (!cmd.compare("help"))
		{
			cout<<"\ncr - Create a/b CFrac."<<endl;
			cout<<"cln - Clean CFrac (make it by default 0/1)."<<endl;
			cout<<"pr - Print current value of CFrac."<<endl;
			cout<<"\nsm - Sum 2 CFracs."<<endl;
			cout<<"sb - Subtract 2 CFracs."<<endl;
			cout<<"mltpl - Multiply 2 CFracs."<<endl;
			cout<<"dvd - Divide 2 CFracs."<<endl;
			cout<<"cmpr - Compare 2 CFracs (>, <, ==)."<<endl;
			cout<<"\nprd - Obtain the knowledge about the period of CFrac."<<endl;
			cout<<"prpr - Obtain the knowledge: whether CFrac is proper or not."<<endl;
			cout<<"whl - Obtain the knowledge about whole part of CFrac."<<endl;
			cout<<"\nhelp - Help (you'll see this list of commands again)."<<endl;
			cout<<"joke - Another little joke for real connoisseurs."<<endl;
			cout<<"exit - Exit."<<endl;
		}

		else if (!cmd.compare("cr"))
		{
			getchar(); infrac(&g);
			cout<<"\nCreated."<<endl;
		}

		else if (!cmd.compare("cln"))
		{
			g.~CFrac();
			cout<<"\nCleaned."<<endl;
		}

		else if (!cmd.compare("pr"))
		{
			cout<<"\nYour CFrac is: "; g.print(); cout<<endl;
		}

		else if (!cmd.compare("sm"))
		{
			CFrac t1, t2;
			getchar(); infrac(&t1); infrac(&t2);
			g = CFrac(t1+t2); cout<<"\nSummed."<<endl;
//			(t1+t2).print();
		}

		else if (!cmd.compare("sb"))
		{
			CFrac t1, t2;
			getchar(); infrac(&t1); infrac(&t2);
			g = CFrac(t1-t2); cout<<"\nSubtracted."<<endl;
//			(t1-t2).print();
		}

		else if (!cmd.compare("mltpl"))
		{
			CFrac t1, t2;
			getchar(); infrac(&t1); infrac(&t2);
			g = CFrac(t1*t2); cout<<"\nMultiplied."<<endl;
//			(t1*t2).print();
		}

		else if (!cmd.compare("dvd"))
		{
			CFrac t1, t2;
			getchar(); infrac(&t1); infrac(&t2);
			g = CFrac(t1/t2);
			if (t2.getnom()) {cout<<"\nDivided."<<endl;}
		}

		else if (!cmd.compare("cmpr"))
		{
			CFrac t1, t2;
			getchar(); infrac(&t1); infrac(&t2);
			switch(t1.frcmpr(t2))
			{
				case 0: t1.print(); cout<<" = "; t2.print(); cout<<endl; break;
				case 1: t1.print(); cout<<" > "; t2.print(); cout<<endl; break;
				case 2: t1.print(); cout<<" < "; t2.print(); cout<<endl; break;
				default: cout<<"Comparison error"<<endl; break;
			}
			cout<<"Compared.\t"<<endl;
		}

		else if (!cmd.compare("prd"))
		{
			getchar(); infrac(&g); g.period();
		}

		else if (!cmd.compare("prpr"))
		{
			getchar(); infrac(&g);
			if (g.isproper()) {g.print(); cout<<" is proper."<<endl;}
			else {g.print(); cout<<" is not proper."<<endl;}
		}

		else if (!cmd.compare("whl"))
		{
			getchar(); infrac(&g);
			cout<<"\nWhole part of your CFrac is: "<<g.wholepart()<<endl;
		}

		else if (!cmd.compare("joke"))
		{
			cout<<"\nWhy did the chicken cross the Mobius strip?"<<endl;
			cout<<"\nTo get to the same side.\t(Much more funnier, don't you think so?)"<<endl;}

		else if (!cmd.compare("exit")) {cout<<"\nBye."<<endl; break;}

		else {cout<<"\nIncorrect command. Try again."<<endl;}
	}
	return 0;
}
//----------------------------

bool signum(int x)
{
    bool b;
    if (x>=0) b=true;
    else b=false;
    return b;
}

int gcd(int a, int b)
{
   return b == 0 ? a : gcd(b, a%b);
}