#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct table
{
	int process;
	int page;
	int frame;
	int max_page_size;
	int valid_bit;
	int reference_bit;
	int modify_bit;
	int clock_bit;
	
};

void table_init(int process,int page,int max_page_size,int page_size)
{
	struct table page_table;
	int total_page;
	total_page = max_page_size/page_size;
	for (int i = 0; i < total_page; i++)
	{
		page_table.process = process;
		page_table.page = i;
		page_table.frame = i;
		page_table.valid_bit = 0;
		page_table.reference_bit = 0;
		page_table.modify_bit = 0;
		page_table.clock_bit =0;
		cout<<page_table.process<<" "<< page_table.page <<" "<< page_table.frame<<" "<<page_table.valid_bit<<" "<<page_table.reference_bit<<" " <<page_table.modify_bit <<" "<<page_table.clock_bit<<" "<<endl;
	}
	
	
}
int main()
{
	string line;
	int page_size;
	int a,b,i,j;
	int arr[10][2];
	
	i=0;
	ifstream myReadFile;
	myReadFile.open("progAddrLimits.txt");
	if (myReadFile.is_open()) 
	{
		while (!myReadFile.eof() && i<10) 
		{	j=0;
			myReadFile >> a >> b;
			cout<<a<<" "<<b<<endl;
			
			//cout<<"i: "<<i<<" "<<"j: "<<j<<endl;
			arr[i][j]=a;
			//cout<<"arr["<<i<<"]"<<"["<<j<<"]"<<arr[i][j]<<endl;
			j++;
			arr[i][j]=b;
			//cout<<"arr["<<i<<"]"<<"["<<j<<"]"<<arr[i][j]<<endl;
			i++;
		}
		
	}
	cout<<"page_table.process"<<" "<< "page_table.page" <<" "<< "page_table.frame"<<" "<<"page_table.valid_bit"<<" "<<"page_table.reference_bit"<<" " <<"page_table.modify_bit" <<" "<<"page_table.clock_bit"<<" "<<endl;
	for (int i = 0; i < 10; i++)
	{
		cout<<"enter page size: ";
		cin>>page_size;

		table_init(i,arr[i][0],arr[i][1],page_size);
	}
	
	

	return 0;
}