//#include <iostream>
#include <fstream>
using namespace std;
#define LEN 5
#define P(i) (l+i)

class CStrList
{
private:
    class CStr
    {
    private:
        char data[LEN]; int prev,next,len;
    public:
        CStr() {SetZero();}
		CStr(const CStr &s) {for(int i = 0; i < s.len; i++) {this->data[i] = s.data[i];} this->len = s.len; prev = next = 0;}
		CStr &operator=(const CStr &s) {for(int i = 0; i < s.len; i++) {data[i] = s.data[i];} prev = s.prev; next = s.next; return *this;}
        ~CStr() {SetZero();}
        void SetZero() {for (int i = 0; i < LEN; i++) {data[i] = '\0';} len = prev = next = 0;}
/*
        ifstream openfile(string fname)
        {
            ifstream fin;
            fin.open(fname);
            if (fin.is_open())
            {
                cout<<"\nSuccess: file opened."<<endl;
                return fin;
            }
            else {cout<<"\nError: cannot open file!"<<endl;}
        }
*/
        void readnextunit(ifstream& in_file)
        {
            if (in_file.is_open())
            {
                char chtmp;
                int i = 0;
                while(in_file.get(chtmp)&&chtmp!='\n'&&i<=LEN)
                {
                    data[i] = chtmp;
                    i++;
                    /*if (i==LEN)
                    {
                        cout<<"\nStr is full."<<endl;
                        break;
                    }*/
                }
                len = i;
                cout<<"\nFinished."<<endl;
            }
            else {cout<<"\nNo file"<<endl;}
        }

        int getlen()
        {
            return len;
        }

        void print()
        {  
            if (data[0]=='\0'||len==0) {cout<<"\nEmpty"<<endl;}
            else
            {
                for (int j = 0; j < len; j++) cout<<data[j];
                cout<<"\nThat's all, folks"<<endl;
            }
        }

        friend class CStrList;
    };

	CStr *l; int b,e,cur,nl;

public:

//	class iterator
//	{
//	private:
//		CList *l; int n;
//	public:
//		iterator(CList *l, int n) {this->l = l; this->n = n;}
//		Str operator*() {return l->l[n].s;}
//		void operator++() {n = l->l[n].next;}
//		int operator!=(const iterator &b) {return n != b.n;}
//		friend class CList;
//	};


	enum Err {Empty, AnyError};

	CStrList() //setting zero
	{
		b = e = cur = 0;
		l = new CStr[nl = 1]; //nl = 100
		int i;
		for (i = 0; i < nl-1; i++) l[i].next = i+1;
		l[i].next = 0; //last elem points to the 0
	}
	
//	~CStrList() {clean();}
	
//	void clean() {while(delcur());}
	int delcur();
	int IsEmpty() {return cur == 0;}
	void tobegin() {cur = b;}
//	void GoToEnd() {cur = e;}	//(l+cur)

	int tonext()
	{
		if(cur == 0 || P(cur)->next == 0) return 0;
		else
		{
			cur = P(cur)->next;
			return 1;
		}
	}

//	int GoToPrev()
//	{
//		if(cur == 0 || P(cur)->prev == 0) return 0;
//		else
//		{
//			cur = P(cur)->prev;
//			return 1;
//		}
//	}

//	CStr getunit() {if(cur == 0) throw Empty; return P(cur)->(*l);}
	void addafter(const CStr &x);
	int loc(const CStr &x);
    void readnextstring(ifstream&);
	void del(int i);
    void printall();
};


int CStrList::loc(const CStr &x)
{
	int i = l->next;
	if(l->next == 0)
	{
		CStr *q = new CStr[2*nl];
		for(i = 0; i < nl; i++) q[i] = l[i];
		q->next = nl;
		for(i = nl; i < 2*nl-1; i++) q[i].next = i+1;
		q[i].next = 0; //last elem
		delete[] l; l = q;
		nl*=2;
	}
	l->next = l[i].next;
	for (int j = 0; j < x.len; j++) {l[i].data[j] = x.data[j];} l[i].prev = l[i].next = 0;
	return i;
}
/*
void CList::del(int i)
{
	l[i].next = l->next; l->next = i;
}

int CList::delcur()
{
	if(cur == 0) return 0;
	else
	{
		int n = cur; cur = 0;

		if(P(n)->next)
		{
			P(P(n)->next)->prev = P(n)->prev;
			cur = P(n)->next;
		}
		else e = P(n)->prev;

		if(P(n)->prev)
		{
			P(P(n)->prev)->next = P(n)->next;
			cur = P(n)->prev;
		}
		else b = P(n)->next;
		del(n);
		return 1;
	}
}
*/

void CStrList::addafter(const CStr &x)
{
	int n = loc(x); //equal to 'new CStr(x);
	if (cur == 0) {cur = b = e = n;}
	else
	{
		P(n)->next = P(cur)->next;
		P(n)->prev = cur;
		P(cur)->next = n;
		if (P(n)->next != 0) {P(P(n)->next)->prev = n;}
		else {e = n;}
	}
}

void CStrList::readnextstring(ifstream& in_file)
{
    for(;;)
    {
        this->l->readnextunit(in_file);
        if (this->l->getlen() != LEN) {break;}
        else {new *CStr() = x; this->addafter(x); delete[] x;}
    }
	//cout<<"\nw = "<<w<<endl;
    //if(w==LEN)
}
/*
int CStrList::getlength()
{
	return biglen;
}

void CStrList::printall()
{
	if (data[0]=='\0'||biglen==-1) cout<<"\nEmpty"<<endl;
	else
    {
        for (int j = 0; j < biglen; j++) cout<<data[j];
		cout<<"\n\nThat's all."<<endl;
    }

}
*/

int main()
{
	string fname; CStrList s; //s.print();
	cout<<"\nFile: "; cin>>fname;
	ifstream fin; fin.open(fname);
	s.readnextstring(fin); fin.close();

	return 0;
}















