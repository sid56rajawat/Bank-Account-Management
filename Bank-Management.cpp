#include<bits/stdc++.h>
#include<fstream>
using namespace std;

int usr=0;

class Account{
    vector <float> passbook;
    string name;
    int type;
    long int acno;
    float balance;
public:
    void printpassbook(){
        cout<<"\nStarting Balance : "<<passbook[0]<<endl;
        for(int i=1;i<passbook.size();i++){
            if(passbook[i]>0){
                cout<<name<<" Deposited "<<passbook[i]<<endl;
            }
            else{
                cout<<name<<" Withdrew "<<-passbook[i]<<endl;
            }
        }
    }
    void accept(){
        cout<<"Enter name : ";
        cin>>name;
        cout<<"Enter Account number : ";
        cin>>acno;
        cout<<"1.Current\n2.Savings\n3.Salary\nEnter Account type : ";
        cin>>type;
        cout<<"Enter Balance : ";
        cin>>balance;
        passbook.push_back(balance);
    }
    void deposit(){
        int temp;
        cout<<"Enter amount to deposit : ";
        cin>>temp;
        try{
            if(type==1){
                balance=balance+temp;
                cout<<"Account Balance : "<<balance;
                passbook.push_back(temp);
            }
            if(type==2 && temp<=10000){
                balance=balance+temp;
                cout<<"Account Balance : "<<balance;
                passbook.push_back(temp);
            }
            else if(type==2 && temp>10000){
                throw "You cannot deposit this amount in Savings account";
            }
            if(type==3 && temp<=50000){
                balance=balance+temp;
                cout<<"Account Balance : "<<balance;
                passbook.push_back(temp);
            }
            else if(type==3 && temp>50000){
                throw "You cannot deposit this amount in Salary account";
            }
        }catch(const char* msg){
            cerr<<msg<<endl;
        }
        
    }
    void withdraw(){
        int temp;
        cout<<"Enter amount to withdraw : ";
        cin>>temp;
        try{
            if(temp>balance){throw "\nInsufficient Balance!!";}
            else{
                if(type==1){
                    balance=balance-temp;
                    cout<<"Account Balance : "<<balance;
                    passbook.push_back(-temp);
                }
                if(type==2 && temp<=10000){
                    balance=balance-temp;
                    cout<<"Account Balance : "<<balance;
                    passbook.push_back(-temp);
                }
                else if(type==2 && temp>10000){
                    throw "You cannot withdraw this amount from Savings account";
                }
                if(type==3 && temp<=50000){
                    balance=balance-temp;
                    cout<<"Account Balance : "<<balance;
                    passbook.push_back(-temp);
                }
                else if(type==3 && temp>50000){
                    throw "You cannot withdraw this amount from Salary account";
                }
            }
        }catch(const char* msg){
            cerr<<msg<<endl;
        }
    }
    void display(){
        cout<<"\nAccount Number : "<<acno;
        cout<<"\tName : "<<name;
        cout<<"\nAccount Type : ";
        if(type==1){cout<<"Current";}
        else if(type==2){cout<<"Savings";}
        else if(type==3){cout<<"Salary";}
        cout<<"\tBalance : "<<balance<<"\n\n";
    }
    long int getac(){
        return acno;
    }
};

int main(){
    int ch=1,n,key,flag=0;
    Account temp;
    fstream file;
    vector <Account> bank;
    while(ch!=0){
        flag=0;
        cout<<"\n0.Exit\n1.Enter Records\n2.Display Records\n3.Deposit\n4.Withdraw\n5.PassBook\n6.Store in file\nEnter choice : ";
        cin>>ch;
        switch(ch){
            case 0:
                cout<<"Thank You!!";
                break;
            case 1:
                cout<<"\nEnter Number of Users : ";
                cin>>n;
                for(int i=0;i<n;i++){
                    Account temp;
                    temp.accept();
                    bank.push_back(temp); 
                    usr++;
                }
                break;
            case 2:
                cout<<"\nDisplaying Records of all accounts :-\n";
                file.open("bank.txt",ios::in);
                for(int i=0;i<usr;i++){
                    file.read((char *)&temp,sizeof(temp));
                    temp.display();
                }
                file.close();
                break;
            case 3:
                cout<<"Enter Account number : ";
                cin>>key;
                for(int i=0;i<usr;i++){
                    if(bank[i].getac()==key){
                        bank[i].deposit();
                        flag=1;
                    }
                }
                if(flag==0){cout<<"\nRecord not found!!";}
                break;
            case 4:
                cout<<"Enter Account number : ";
                cin>>key;
                for(int i=0;i<usr;i++){
                    if(bank[i].getac()==key){
                        bank[i].withdraw();
                        flag=1;
                    }
                }
                if(flag==0){cout<<"\nRecord not found!!";}
                break;
            case 5:
                cout<<"Enter Account number : ";
                cin>>key;
                for(int i=0;i<usr;i++){
                    if(bank[i].getac()==key){
                        bank[i].printpassbook();
                        flag=1;
                    }
                }
                if(flag==0){cout<<"\nRecord not found!!";}
                break;
            case 6:
                file.open("Bank.txt",ios::out);
                for(int i=0;i<usr;i++){
                    file.write((char *)&bank[i],sizeof(bank[i]));
                }
                file.close();
                cout<<"\nFile write Successfull!!";
                break;
            default:
                cout<<"\nEnter a valid choice";
        }
    }
}