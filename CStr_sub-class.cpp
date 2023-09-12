#include <iostream>
#include <fstream>
using namespace std;
#define LEN 8

//int strlen(char*);

class CStr
{
private:
 char data[LEN]; int len;

public:
 CStr() {set_zero();}
 ~CStr() {set_zero();}

 void set_zero();
 int length();

 int read(ifstream&);
 void copyto(char*);
 void copyto(char*, int, int);
 int find(char*);

 void print();

};

int main()
{
	char tst[16]; ifstream f_in;
	CStr s;

	f_in.open("test3.txt");

	s.read(f_in); s.print();

	cout<<"\nString: "; cin>>tst;

	s.copyto(tst, 2, 10); cout<<tst<<endl;

	f_in.close();

	return 0;
}


void CStr::set_zero()
{
  for (int i = 0; i < LEN; i++)
  {
    data[i] = '\0';
  }

  len = 0;
}

int CStr::length()
{
  return len;
}

int CStr::read(ifstream& in_file)
{
  char chtmp = 0; int i = 0;

  while(in_file.get(chtmp) && chtmp!='\n' && chtmp!='\0' && i<=LEN)
  {
    data[i++] = chtmp;
    if (i==LEN)
    {
      cout<<"\nStr is full."<<endl;
      break;
    }
  }
//  data[i]='\0';
  len = i-1; //last symbol is '\n' or '\0'
  cout<<len<<endl;
  return len;
}

void CStr::print()
{  
  if (data[0]=='\0' || len==0) {cout<<"\nEmpty"<<endl;}
  else {for (int j = 0; j < len; j++) {cout<<data[j];} cout<<endl;}
}

void CStr::copyto(char *into)
{
  if (data[0]=='\0' || len==0) {cout<<"\nCannot copy empty string!"<<endl;}
  else {for (int j=0;j<len;j++) {into[j] = data[j];}}
}

void CStr::copyto(char *into, int beg_pos, int end_pos)
{
  if (data[0]=='\0' || len==0) {cout<<"\nCannot copy empty string!"<<endl;}
  else
  {
    if (beg_pos<=end_pos && end_pos<=len && beg_pos>=0)
    {
      for(int i = beg_pos; i<=end_pos; i++) {into[i-beg_pos] = data[i];}
    }
    else {cout<<"\nIncorrect parameters."<<endl;}
  }
}

int CStr::find(char *request) //make ans like in 1-char version
{
  int reqlen, ans;

  for(reqlen=0;request[reqlen];reqlen++);

  ans = 0;
  for(int j,i = 0; i <= len-reqlen; i++)
  {
    for(j = 0; data[i+j] == request[j]; j++)
    {
     if (j==reqlen-1) {cout<<"\nFound in position: "<<i<<endl; ans++;}
    }
  }
  if (ans==0) cout<<"\nNot found"<<endl;
  return ans;
}
