#include <iostream>
#include <fstream>
using namespace std;
#define LEN 16

class CStr
{
private:
  char data[LEN]; int len; CStr *next;

public:
  CStr() {set_zero(); next = NULL;}
  CStr(const CStr& s)
  {
    len = s.len;
    for(int i = 0; i<=len; i++)
    {
      data[i] = s.data[i];
    }
  }
  
  ~CStr() {set_zero();} //may be of no need

  void set_zero();
  int length();

  int read(ifstream&);
  void copy(char*);
  void copy(char*, int, int);
  int find(char*);

  void print();

  friend class CStrList;
};


class CStrList
{
private:
    CStr *head; CStr *tail;

public:
    CStrList() {head = NULL; tail = NULL;}

    ~CStrList()
    {
      while(head!=NULL)
      {CStr *temp = head->next; delete head; head = temp;}
    }

    void Add(CStr);
    CStr Gethead() {return *head;}
    void Print();

    ifstream Fileopen(string);
    int Lenstr();
    void Read(ifstream&);
    void Find(char*);
//    void Copy();
};


int main()
{
	cout<<"\nfile - Open file for reading."<<endl;
	cout<<"read - Read one string from file."<<endl;
	cout<<"len - Obtain the length of the string read."<<endl;
	cout<<"print - Output your string to the console."<<endl;
	cout<<"find - Find sub-string in the whole string."<<endl;
	cout<<"\nhelp - Help (you'll see this list again)."<<endl;
	cout<<"exit - Exit."<<endl;

	CStrList l; CStr s; string cmd; ifstream f; int flag = 0;

	for(;;)
	{
		cout<<"\nType command: "; cin>>cmd;
		if (cmd.compare("help")==0)
		{
			cout<<"\nfile - Open file for reading."<<endl;
			cout<<"read - Read one string from file."<<endl;
			cout<<"len - Obtain the length of read string."<<endl;
			cout<<"print - Output your string to the console."<<endl;
			cout<<"find - Find sub-string in the whole string."<<endl;
			cout<<"\nhelp - Help (you'll see this list again)."<<endl;
			cout<<"exit - Exit."<<endl;
		}
		else if (cmd.compare("file")==0)
		{
			string fname;
			cout<<"\nFile: "; cin>>fname;
			f = l.Fileopen(fname);
			if (f.is_open()) {flag = 1;}
		}
		else if (cmd.compare("read")==0)
		{
			if (flag) {l.~CStrList(); l.Read(f); l.Print(); flag = 2;}
			else {cout<<"\nYou have no open file yet."<<endl;}
		}
		else if (cmd.compare("len")==0)
		{
			if (flag==2) {cout<<"\nlength = "<<l.Lenstr();}
			else {cout<<"\nYou have no read string yet."<<endl;}
		}
		else if (cmd.compare("print")==0)
		{
			if (flag==2) {l.Print();}
			else {cout<<"\nYou have no read string yet."<<endl;}
		}
		else if (cmd.compare("find")==0)
		{
			if (flag==2)
			{char *req; cout<<"\nString to find: "; cin>>req; l.Find(req);}
			else {cout<<"\nYou have no read string yet."<<endl;}
		}
		else if (cmd.compare("exit")==0) {f.close(); break;}
		else {cout<<"\nIncorrect command. Type again."<<endl;}
	}
	return 0;
}


void CStrList::Add(CStr s)
{
  CStr *temp = new CStr;
  for(int i = 0; i<=s.len; i++) {temp->data[i] = s.data[i];}
  temp->len = s.len;
  temp->next = NULL;

  if(head!=NULL)
  {
    tail->next = temp;
    tail = temp;
  }
  else {head = tail = temp;}
//    delete temp;
}

void CStrList::Print()
{
  CStr *temp = new CStr;
  temp = head;
  while(temp!=NULL) {temp->print(); temp=temp->next;}
}

ifstream CStrList::Fileopen(string fname)
{
  ifstream fin;
  fin.open(fname);
  if (fin.is_open())
  {
    cout<<"\nSuccess: file opened."<<endl;
  }
  else {cout<<"\nError: cannot open file!"<<endl;}
  return fin;
}

void::CStrList::Read(ifstream &f)
{
  CStr *tmp = new CStr;
  int flag = LEN;
  for(;;)
  {
      int report = tmp->read(f);
      this->Add(*tmp);
      if (report == -1) {cout<<"\nNo file"<<endl; break;}
      else if (report == 1) {break;}
      else {f.seekg(flag, ios::beg); flag+=LEN;}
  }
}

void::CStrList::Find(char *request)
{
  CStr *temp = new CStr;
  temp = head;
  while(temp!=NULL) {temp->find(request); temp=temp->next;}
}

int CStrList::Lenstr()
{
  int sz = 0;
  for(CStr *s = head; s!=NULL; s = s->next) {sz+=s->length();} //s.length()
  return sz;
}


//--------------------------------------------------------------------------



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
  int rep = -1;
  if (in_file.is_open())
  {
    char chtmp;
    int j = 0;

    in_file.get(chtmp);


    if((((int)chtmp)!=10)&&(((int)chtmp)!=13)) {data[j]=chtmp; j++;}

    while(in_file.get(chtmp))
    {
      if (j==LEN)
      {
        if ((int)chtmp==13) {rep = 1;}
        else {rep = 0;}
        break;
      }
      else if ((int)chtmp==13) {rep = 1; break;}
      else
      {
        data[j++] = chtmp;
        //i++;
      }
    }
    len = j;
//    in_file.seekg(j+LEN, ios::beg);
  }
  return rep;
}

void CStr::print()
{  
  if (data[0]=='\0' || len==0) {cout<<"\nEmpty"<<endl;}
  else
  {
    for (int j = 0; j < len; j++) {cout<<data[j];}
  }
}

void CStr::copy(char *into)
{
  if (data[0]=='\0' || len==0) {cout<<"\nCannot copy empty string!"<<endl;}
  else {for (int j=0;j<len;j++) {into[j] = data[j];}}
}

void CStr::copy(char *into, int beg_pos, int end_pos)
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

int CStr::find(char *request)
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
