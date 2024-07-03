#include <iostream>
#include<mysql.h>
#include<mysqld_error.h>
#include<windows.h>
#include<sstream>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

const char* HOST="localhost";
const char* USER="root";
const char* PW="149209@aditi";
const char* DB="mydatabase";

class Hostel{
	private:
		string Name;
		int Bed, Fee;
		public:
		Hostel(string name, int bed, int fee){
		Name=name;
		Bed=bed;
		Fee=fee;
	}
	
	
string getName(){
	return Name;
}
int getBed(){
	return Bed;
}
int getFee(){
	return Fee;
}
};

int main() {
	MYSQL* conn;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0)){
	cout<<"Error: "<<mysql_error(conn)<<endl;
}
else{
	cout<<"Logged in Database"<<endl;
}
Sleep(3000);

Hostel h("3star", 5, 5000);
int intB =h.getBed();
stringstream ss;
ss<<intB;
string strB=ss.str();

int intF=h.getFee();
stringstream as;
as<<intF;
string strF=as.str();
string insert ="INSERT INTO hostel (Name, Bed, Fee) VALUES ('"+h.getName()+"','"+strB+"','"+strF+"')";
if(mysql_query(conn,insert.c_str())){
	cout<<"Errorr: "<<mysql_error(conn)<<endl;
}
else{
	cout<<"Data inserted"<<endl;
}
bool exit= false;
while(!exit){
	system("cls");
	cout<<"Welcome To Hostel Management System"<<endl;
	cout<<"***********************************"<<endl;
	cout<<"1.Reserve Bed: "<<endl;
	cout<<"2.Exit: "<<endl;
	cout<<"Enter Your Choice: ";
	int val;
	cin>>val;
	
	if(val==1){
		string n;
		cout<<"Enter Student Name: ";
		cin>>n;
		int total;
		string check=" SELECT Bed FROM hostel WHERE Name = '"+h.getName()+"'";
		if(mysql_query(conn,check.c_str())){
	cout<<"Errorr: "<<mysql_error(conn)<<endl;
}
else{
	MYSQL_RES* res;
	res= mysql_store_result(conn);
	if(res){
		MYSQL_ROW row=mysql_fetch_row(res);
		if(row){
		total=atoi(row[0]);	
		}
		mysql_free_result(res);
	}
}
if(total>0){
	total--;
	
stringstream zs;
zs<<total;
string strT= zs.str();
string update = "UPDATE hostel SET Bed = '"+strT+"' WHERE Name= '"+h.getName()+"'";
	if(mysql_query(conn,update.c_str())){
	cout<<"Errorr: "<<mysql_error(conn)<<endl;
}
else{
	cout<<"Bed is Reserved Successfully in"<<h.getName()<<"Hostel For Student "<<n<<endl;
	cout<<"Please Pay "<<h.getFee()<<" Rupees."<<endl;
}
}
else if(total==0){
	cout<<"Sorry! No Bed Available"<<endl;
}
Sleep(8000);
}//if1

else if(val==2){
	exit=true;
	cout<<"Good Luck"<<endl;
	Sleep(3000);
}
else{
	cout<<"Invalid Input"<<endl;
	Sleep(3000);
}
}//while
mysql_close(conn);
	return 0;
}
