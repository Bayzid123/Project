#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<stdlib.h>
using namespace std;

class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();
	void show_account();
	void modify();
	void dep(int x);
	void draw(int x);
	void report();
	int retacno();
	int retdeposit();
	char rettype() ;
};

void account::create_account()
{
	cout<<"\nEnter The account No. :";
	cin>>acno;
	cout<<"\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>deposit;
	cout<<"\n\n\nAccount Created..";
}

void account::show_account()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}


void account::modify()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nModify Balance amount : ";
	cin>>deposit;
}


void account::dep(int x)
{
	deposit+=x;
}

void account::draw(int x)
{
	deposit-=x;
}

void account::report()
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}


int account::retacno()
{
	return acno;
}

int account::retdeposit()
{
	return deposit;
}

char account::rettype()
{
	return type;
}
void write_account();
void display_sp(int n);
void modify_account(int n);
void delete_account(int n);
void display_all();
void deposit_withdraw(int n, int option);
void intro();

int main()
{
    system("color 17");
	int ch;
	int num;
	  cout<<"\t\t\t\t\t******\n";
    cout<<"\t\t\t\t     ************\n";
    cout<<"\t\t\t      *  *****    **    ****   *  \n";
    cout<<"\t\t\t      *  *    *   **   *    *  *  \n";
    cout<<"\t\t\t      *  *    *   **   *    *  *  \n";
    cout<<"\t\t\t      *  *    *   **   *    *  *  \n";
    cout<<"\t\t\t      *  *****    **   *    *  *  \n";
    cout<<"\t\t\t      *  *    *   **   ******  *  \n";
    cout<<"\t\t\t      *  *    *   **   *    *  *  \n";
    cout<<"\t\t\t      *  *    *   **   *    *  *  \n";
    cout<<"\t\t\t      *  *    *   **   *    *  *  \n";
    cout<<"\t\t\t      *  *****    **   *    *  *  \n";
    cout<<"\t\t\t      *           **           *\n";
    cout<<"\t\t\t      **************************\n";
    cout<<"\t\t\t                  **\n";
    cout<<"\t\t\t\t\t******\n";
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\t=========";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case 1:
			write_account();
			break;
		case 2:
			cout<<"\n\n\tEnter The account No. : ";
			cin>>num;
			deposit_withdraw(num,1);
			break;
		case 3:
			cout<<"\n\n\tEnter The account No. : ";
			 cin>>num;
			deposit_withdraw(num, 2);
			break;
		case 4:
			cout<<"\n\n\tEnter The account No. : ";
			cin>>num;
			display_sp(num);
			break;
		case 5:
			display_all();
			break;
		case 6:
			cout<<"\n\n\tEnter The account No. : ";
			 cin>>num;
			delete_account(num);
			break;
		 case 7:
			cout<<"\n\n\tEnter The account No. : ";
			 cin>>num;
			modify_account(num);
			break;
		 case 8:
			cout<<"\n\n\tThanks for using bank management system";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!=8);
	return 0;
}
void write_account()
{
	account ac;
	ofstream fout;
	fout.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	fout.write((char *) (&ac), sizeof(ac));
	fout.close();
}
void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream fin;
	fin.open("account.dat",ios::binary);
	if(!fin)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(fin.read((char *) (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
	fin.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}

void modify_account(int n)
{
	bool found;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof())
	{
		File.read((char *) (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)* (sizeof(account));
			File.seekp(pos,ios::cur);
			File.write((char *) (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}
void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char *) (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write((char *) (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}
void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type               Balance\n";
	cout<<"====================================================\n";
	while(inFile.read((char *) (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

void deposit_withdraw(int n, int m)
{
	int amt;
	bool found;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read((char *) (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(m==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposit<<\t\t\t";
				cin>>amt;
				ac.dep(amt);
			}
			if(m==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw\t\t\t";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos=(-1)*(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write((char *) (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }

	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}
void intro()
{
	cout<<"\n\t\t\t\tBANK Management System";

	cout<<"\n\n\n\t\t\t\tMADE BY : Md. Bayzid";
	cout<<"\n\n\t\t\t\t\Institution : IUBAT University";
	cin.get();
}





