//Soyfer_Task1.12

#include <iostream>
#include <fstream>

using namespace std;

class CFrac
{
public:
	bool sign; int a,b; //false (0) if negative, true (1) if zero or positive
};


CFrac dofrac(void);
CFrac dofrac(const CFrac& r); //operator=
CFrac dofrac(int x, int y);
CFrac fracplus(const CFrac& r1, const CFrac& r2);
CFrac fracminus(const CFrac& r1, const CFrac& r2);
CFrac multiply(const CFrac& r1, const CFrac& r2);
CFrac divide(const CFrac& r1, const CFrac& r2);

void clean(CFrac *r);
//void fill(CFrac *r, int x, int y); //changing parameters of class
void infrac(CFrac *r);
void compare(CFrac *r1, CFrac *r2);
bool isproper(const CFrac& r);
int wholepart(const CFrac& r);
void period(const CFrac& r);

void test(void);
void print(CFrac *r);
bool signum(int x);
int gcd(int x, int y);
void norm(CFrac *r);


//---------------------------------------------------------------------------------
int main()
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
	cout<<"\nhelp - Help (you'll see this list again)."<<endl;
	cout<<"test - Launch autotest for this class from default file."<<endl;
	cout<<"joke - A little joke."<<endl;
	cout<<"exit - Exit."<<endl;

	string cmd; //int afrac = 0; int bfrac = 0;
	CFrac g = dofrac(0,0);

	for(;;)
	{
		cout<<"\nType command: ";
		cin>>cmd;
		
		if (!cmd.compare("test"))
		{
			cout<<"\nOK, soon here wil be some test"<<endl;
			/*ifstream infile;
			infile.open("test.txt");
			if (infile.is_open())
			{
				string tmp;
				while(infile>>str) {cout<<"\n"<<str<<endl;}
			}
			else
			{
				cout<<"\nError: cannot open file\n"<<endl;
			};*/
		}

		else if (!cmd.compare("help"))
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
			cout<<"\nhelp - Help (you'll see this list again)."<<endl;
			cout<<"test - Launch autotest for this class from default file."<<endl;
			cout<<"joke - A little joke."<<endl;
			cout<<"exit - Exit."<<endl;
		}

		else if (!cmd.compare("cr"))
		{
			getchar(); infrac(&g);
			if(g.b==0) {cout<<"\nThere is no CFrac for now."<<endl;}
			else {print(&g);}
		}

		else if (!cmd.compare("cln"))
		{
			g = dofrac(0,1); print(&g);
			cout<<"\nCongrats! CFrac was cleaned."<<endl;
		}

		else if (!cmd.compare("pr"))
		{
			if(g.b==0) {cout<<"\nThere is no CFrac for now."<<endl;}
			else {cout<<"\nYour CFrac is: "; print(&g); cout<<endl;}
		}

		else if (!cmd.compare("sm"))
		{
			CFrac t1 = dofrac(); CFrac t2 = dofrac();
			getchar(); infrac(&t1); infrac(&t2);
			CFrac t12 = fracplus(t1, t2); //norm(&t12);
			g = dofrac(t12.a, t12.b); print(&g);
		}

		else if (!cmd.compare("sb"))
		{
			CFrac t1 = dofrac(); CFrac t2 = dofrac();
			getchar(); infrac(&t1); infrac(&t2);
			CFrac t12 = fracminus(t1, t2); norm(&t12);
			g = dofrac(t12.a, t12.b);
			cout<<"\nCongrats! You can see the result (CFrac1 - CFrac 2) by typing 'pr'."<<endl;
		}

		else if (!cmd.compare("mltpl"))
		{
			CFrac t1 = dofrac(); CFrac t2 = dofrac();
			getchar(); infrac(&t1); infrac(&t2);
			CFrac t12 = multiply(t1, t2); norm(&t12);
			g = dofrac(t12.a, t12.b);
			cout<<"\nCongrats! 2 CFracs were multiplied."<<endl;
		}

		else if (!cmd.compare("dvd"))
		{
			CFrac t1 = dofrac(); CFrac t2 = dofrac();
			getchar(); infrac(&t1); infrac(&t2);
			CFrac t12 = divide(t1, t2);
			if (t12.b != 0) {g = dofrac(t12); print(&g);}
			else {cout<<"\nDivision banned."<<endl;}
		}

		else if (!cmd.compare("cmpr"))
		{
			CFrac t1 = dofrac(); CFrac t2 = dofrac();
			getchar(); infrac(&t1); infrac(&t2);
			compare(&t1, &t2);
			cout<<"Congrats! 2 CFracs were compared."<<endl;
		}

		else if (!cmd.compare("prd"))
		{
			getchar(); infrac(&g); norm(&g);
			period(g);
		}

		else if (!cmd.compare("prpr"))
		{
			getchar(); infrac(&g); norm(&g);
			if (isproper(g)) {print(&g); cout<<" is proper."<<endl;}
			else {print(&g); cout<<" is not proper."<<endl;}
		}

		else if (!cmd.compare("whl"))
		{
			getchar(); infrac(&g); norm(&g);
			cout<<"\nWhole part of your CFrac is: "<<wholepart(g)<<endl;
		}

		else if (!cmd.compare("joke"))
		{
			cout<<"\nWhy did the chicken cross the road?"<<endl;
			cout<<"\nTo get to the other side.\t(Funny, isn't it?)"<<endl;}

		else if (!cmd.compare("exit")) {cout<<"\nBye."<<endl; break;}

		else {cout<<"\nIncorrect command. Try again."<<endl;}
	}
	return 0;
}
//----------------------------


CFrac dofrac(void)
{
    CFrac t;
    t.a = 0; t.b = 1; t.sign = true;
    return t;

}

CFrac dofrac(const CFrac& r)
{
    CFrac t;
    t.a = r.a; t.b = r.b; t.sign = r.sign;
    return t;
}

CFrac dofrac(int x, int y)
{
    CFrac t; bool sgn = signum(x*y);
    t.a = x; t.b = y; t.sign = sgn;
    return t;
}

CFrac fracplus(const CFrac& r1, const CFrac& r2)
{
    CFrac t;
    t.a = r1.a*r2.b + r2.a*r1.b;
    t.b = r1.b*r2.b;
    t.sign = signum(t.a*t.b);
    return t;
}

CFrac fracminus(const CFrac& r1, const CFrac& r2) //r1 - r2
{
    CFrac t;
    t.a = r1.a*r2.b - r2.a*r1.b;
    t.b = r1.b*r2.b;
    t.sign = signum(t.a*t.b);
    return t;
}

CFrac multiply(const CFrac& r1, const CFrac& r2)
{
    CFrac t;
    t.a = r1.a*r2.a;
    t.b = r1.b*r2.b;
    t.sign = signum(t.a*t.b);
    return t;
}

CFrac divide(const CFrac& r1, const CFrac& r2) // r1 : r2
{
	CFrac t = dofrac(0,0);
	if (r2.a == 0) {cout<<"Don't you know that division by zero is mathematical taboo? ";}
	else {t = dofrac(r1.a*r2.b, r1.b*r2.a); norm(&t);}
	return t;
}

void clean(CFrac *r)
{
	(*r).a = 0; (*r).b = 1; (*r).sign = true;
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

		if((input>=48)&&(input<58)) //chars '0'...'9'
		{
			input -= 48; //input == cypher 0...9
			frac[index] *= 10; frac[index] += input;
		}

		if ((input==47)&&(slash==false)) {slash=true; index = 1;}

		if (input==10) {break;}
	}

	if (frac[1]!=0)
	{
		r->a = frac[0]*sgn[0]; r->b = frac[1]*sgn[1];
		r->sign = signum(r->a*r->b);
	}
	else {cout<<"\nBan: incorrect fraction input."<<endl;}
}

void compare(CFrac *r1, CFrac *r2) //ans: 1 if r1>r2, 2 if vice versa, 0 if equal
{
	int ans, res, div;

	if (r2->a == 0)
	{
		if (r1->a == 0) ans = 0;
		else if (r1->sign) ans = 1;
		else ans = 2;
	}

	else
	{
		CFrac t = divide(*r1, *r2);

		div = t.a / t.b; res = t.a % t.b;
		if (r1->sign == r2->sign)
		{
			switch(div)
			{
				case 0: ans = 2; break;
				case 1: if (res) ans = 1; else ans = 0; break;
				default: ans = 1; break;
			}
			if ((r1->sign==false)&&(ans!=0)) {ans = 1 + ans%2;} //r1->sign == r2->sign < 0
		}

		else
		{
			if (r1->sign) ans = 1; //r1 >= 0 => r2 < 0 => r1 > r2
			else ans = 2;
		}

	}

	switch(ans)
	{
		case 0: print(r1); cout<<" = "; print(r2); cout<<endl; break;
		case 1: print(r1); cout<<" > "; print(r2); cout<<endl; break;
		case 2: print(r1); cout<<" < "; print(r2); cout<<endl; break;
		default: cout<<"\nsomething gone wrong"<<endl;
	}
}

void period(const CFrac& r)
{
	int at,bt,preper; //at - numerator, bt - denominator;
	at = r.a; bt = r.b;
	at /= gcd(at,bt); bt /= gcd(at,bt);

	int b = bt;
	int s = b % 2; int i2 = 0;
	while (s == 0) {b /= 2; s = b % 2; i2++;}

	s = b % 5; int i5 = 0;
	while (s == 0) {b /= 5; s = b % 5; i5++;}

	int perlen = 1; int p = 10;
	while (p != 1)
	{
		p = (10*p) % b;
		if (p == 0) {break;}
		perlen++;
	}

	if (i2 > i5) {preper = i2;}
	else {preper = i5;}

	cout<<"\n"<<at<<"/"<<bt<<" = "<<at/bt<<".";
	int a = at % bt;
	for (int i = 0; i < preper; i++)
	{
		cout<<10*a/bt; a = (10*a) % bt;
	}
	cout<<"(";
	for (int i = 0; i < perlen; i++)
	{
		cout<<10*a/bt; a = (10*a) % bt;
	}
	cout<<")";
}

bool isproper(const CFrac& r)
{
	bool b;
	if (r.a >= r.b) b = false;
	else b = true;
	return b;
}

int wholepart(const CFrac& r)
{
	int whole;
	whole = r.a/r.b;
	return whole;
}

void print(CFrac *r)
{
	char sgn;
	if (r->sign) sgn = ' ';
	else sgn = '-';
	if (r->b != 0) {norm(r); cout<<sgn<<abs(r->a)<<"/"<<abs(r->b);}
	else {cout<<"\nBan: Division by zero detected."<<endl;}
}

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

void norm(CFrac *r)
{
	if(r->b != 0) {int z = gcd(r->a,r->b); r->a /= z; r->b /= z;}
	else {cout<<"\nBan: Division by zero detected."<<endl;}
}