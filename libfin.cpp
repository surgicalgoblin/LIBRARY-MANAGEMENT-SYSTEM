#include<string.h>
#include<fstream.h>
#include<conio.h>
#include<stdio.h>

class Book
{
int  Stock;	
int  ID;
char ISBN[12];
char Title[30];
char Author_name[50];
char Publisher[50];
int Publishing_day,Publishing_month,Publishing_year;
int Price;
public:       
       void Add_book()
            {
              clrscr();
	      cout<<"\n ID: ";
	      cin>>ID;
	      cout<<"\n Title: ";
	      gets(Title);
	      cout<<"\n ISBN: ";
	      gets(ISBN); 
	      cout<<"\n Author's name: ";
	      gets(Author_name);
	      cout<<"\n Publisher's name: ";
	      gets(Publisher);
	      cout<<"\n Publishing Date: ";
	      cout<<"\n                  day: ";
	      cin>>Publishing_day;
	      cout<<"\n                  month: ";
	      cin>>Publishing_month;
	      cout<<"\n                  year: ";
	      cin>>Publishing_year;
	      cout<<"\n Stock: ";
	      cin>>Stock;
	      cout<<"\n Price: ";
	      cin>>Price;
            }
			
	void Display_book()
            {	 
             cout<<"\n\n ID: "<<ID;
             cout<<"\n Title: "<<Title; 
             cout<<"\n ISBN: "<<ISBN;
             cout<<"\n Author's name: "<< Author_name;
             cout<<"\n Publisher:"<<Publisher;
             cout<<"\n Publishing date"<<Publishing_day<<"/"<< Publishing_month<<"/"<<Publishing_year;
             cout<<"\n Stock: "<<Stock;
	      cout<<"\n Price: "<<Price;
            }

        char* givetitle()
	     {
	      return Title;
             }

        int getid()
      	     {
	      return ID; 	
	     }

        void Stock_down()
             {
	      Stock--;	
             }

        void Stock_up()
             {
              Stock++;	
             }			
};

class Details
{
 int Issue_id;	
 char Class[5];
 int rollno;
 char name[20];
 char book_name[50];
 int issue_day,issue_month,issue_year;
 int return_day,return_month,return_year;
 public:       
        void ISSUE()
            {
	     clrscr();	
      	     cout<<"\n Issue ID: ";
	     cin>>Issue_id;
	     cout<<"\n Class: ";
	     gets(Class);
	     cout<<"\n Roll number: ";
	     cin>>rollno;
	     cout<<"\n Name of the student: ";
	     gets(name);
	     cout<<"\n Book name: ";
	     gets(book_name);
	     cout<<"\n Issue Date: ";
	     cout<<"\n             day: ";
	     cin>>issue_day;
	     cout<<"\n             month: ";
	     cin>>issue_month;
	     cout<<"\n             year: ";
	     cin>>issue_year;
	     cout<<"\n\n BOOK ISSUED, RETURN AFTER 20 DAYS. FINE = 2 RUPEES PER DAY.";
	    }
			
	int giveid()
      	    {
	     return Issue_id;	
	    }	
		
	void RETURN()
            { 	
	     cout<<"\n Return Date: ";
	     cout<<"\n             day: ";
	     cin>>return_day;
	     cout<<"\n             month: ";
	     cin>>return_month;
	     cout<<"\n             year: ";
	     cin>>return_year;
            }
			
        void DisplayRecord()
	    { 	
	     cout<<"\n\n\n Issue ID: "<<Issue_id;
	     cout<<"\n Class: "<<Class;
             cout<<"\n Roll number: "<<rollno;
	     cout<<"\n Name: "<<name;
             cout<<"\n Book: "<<book_name;
             cout<<"\n Issue date: "<<issue_day<<" "<<issue_month<<" "<<issue_year;
             cout<<"\n Return date: "<<return_day<<" "<<return_month<<" "<<return_year;
            }
			
	char* givename()
            {
	     return book_name; 	 
	    }			
};

void Write_book(Book s)
{
ofstream fout("Books.dat",ios::binary|ios::app);
fout.write((char *)&s,sizeof(s));
fout.close();
}

void displayall_book()
{
Book s;
ifstream fin("Books.dat",ios::binary);
while(!fin.eof() && fin.read((char *)&s,sizeof(s)))
     {
      s.Display_book();
     }
fin.close();
}

void display_book(int i)
{
Book s;
ifstream fin("Books.dat",ios::binary);
while(!fin.eof() && fin.read((char *)&s,sizeof(s)))
     {
      if(s.getid() == i)
        {
         s.Display_book();
        }
     }
fin.close();
}

void Update(int i)
{
Book s;
ifstream fin("Books.dat",ios::binary);
ofstream fout("temp.dat",ios::binary|ios::app);
while(!fin.eof() && fin.read((char *)&s,sizeof(s)))
     {
      if(s.getid() == i)
        {
         s.Add_book();
        }
      fout.write((char *)&s,sizeof(s));
     }
fin.close();
fout.close();
remove("Books.dat");
rename("temp.dat","Books.dat");
}

void Delete(int i)
{
Book s;
ifstream fin("Books.dat",ios::binary);
ofstream fout("temp.dat",ios::binary|ios::app);
while(!fin.eof() && fin.read((char *)&s,sizeof(s)))
     {
      if(s.getid() != i)
        {
         fout.write((char *)&s,sizeof(s));
        }
     }
fin.close();
fout.close();
remove("Books.dat");
rename("temp.dat","Books.dat");
}

void Write_record(Details d1)
{
ofstream fout("Record.dat",ios::binary|ios::app);
fout.write((char *)&d1,sizeof(d1));
fout.close();
Details d0;
ifstream fin("Record.dat",ios::binary);
while(!fin.eof() && fin.read((char *)&d0,sizeof(d0)))
     {
      Book s;
      ifstream fin1("Books.dat",ios::binary);
      ofstream fout("temp.dat",ios::binary|ios::app);
      while(!fin1.eof() && fin1.read((char *)&s,sizeof(s)))
           {
            if(strcmpi(s.givetitle(),d0.givename()) == 0)
              {
               s.Stock_down();
              }
            fout.write((char *)&s,sizeof(s));
           }
      fin1.close();
      fout.close();
      remove("Books.dat");
      rename("temp.dat","Books.dat");
     }
fin.close();
}

void Update_record(int i)
{
Details d0;
char nme[30];
ifstream fin("Record.dat",ios::binary);
ofstream fout("temp.dat",ios::binary|ios::app);
while(!fin.eof() && fin.read((char *)&d0,sizeof(d0)))
     {
      if(d0.giveid() == i)
        {
         d0.RETURN();
	 strcpy(nme,d0.givename());	 
        }
      fout.write((char *)&d0,sizeof(d0));
     }
fin.close();
fout.close();
remove("Record.dat");
rename("temp.dat","Record.dat");

ifstream fin2("Record.dat",ios::binary);
Book s;
ifstream fin1("Books.dat",ios::binary);
ofstream fout1("temp.dat",ios::binary|ios::app);
while(!fin1.eof() && fin1.read((char *)&s,sizeof(s)))
     {
      if(strcmpi(s.givetitle(),nme) == 0)
        {
         s.Stock_up();
        }
      fout1.write((char *)&s,sizeof(s));
	 }
fin1.close();
fout1.close();
remove("Books.dat");
rename("temp.dat","Books.dat");
fin2.close();	 
}

int fine(int Fine)
{
 return ((Fine-20)*2);
}

void display_record(int i)
{
Details d0;
ifstream fin("Record.dat",ios::binary);
while(!fin.eof() && fin.read((char *)&d0,sizeof(d0)))
     {
      if(d0.giveid() == i)
        {
         d0.DisplayRecord();
        }
     }
fin.close();
}

void displayall_record()
{
Details d0;
ifstream fin("Record.dat",ios::binary);
while(!fin.eof() && fin.read((char *)&d0,sizeof(d0)))
     {
      d0.DisplayRecord();
     }
fin.close();
}

void main()
{
clrscr();
int fine_day, choice;
char ch='y';
int i,n;
int id;
Book ss;
Details dd;
cout<<"                               !!!!WELCOME!!!!"<<"\n";
cout<<"\n\n\n\n";
cout<<"                           LIBRARY MANAGEMENT SYSTEM"<<"\n\n\n\n";
cout<<"	                                               MADE BY- ASHISH,ABHAY,ESHMAEL"<<"\n\n\n\n\n\n"<<"Press ENTER to continue";
getch();
clrscr();
do
{
  clrscr();
  cout<<"\n 1.Book Shelf";
  cout<<"\n 2.Issue/Return";
  cout<<"\n 3.Exit";
  cout<<"\n Enter the choice (1-3): ";
  cin>>choice;
  switch(choice)
  {
	  case 1:{
		  clrscr();
	          cout<<"\n 1.Add/Insert";
		  cout<<"\n 2.Update details";
		  cout<<"\n 3.Delete";
		  cout<<"\n 4.Search a book";
		  cout<<"\n 5.Display All";
		  cout<<"\n 6.Exit";
		  cout<<"\n Enter the choice (1-6): ";
		  cin>>choice;
		  switch(choice)
	     	        {
		         case 1:
			        clrscr();		
			        ss.Add_book(); Write_book(ss); break;
                          
			 case 2:
			        clrscr();
  	 			cout<<"\n Enter the ID of the book to be updated: ";
				cin>>id;
				Update(id);break;
                              
			 case 3:
                                clrscr(); 
			        cout<<"\n Enter the ID of the book to be deleted: ";
				cin>>id;
	      		        Delete(id);break;

		         case 4:
                                clrscr();  						
				cout<<"\n Enter the ID of the book :";
				cin>>id;
		   	        display_book(id);break;

			 case 5:
			       clrscr();
	  		       displayall_book();break;
								
		         case 6:
                                break;
								 
			 default:
                                 break;						
                        };
	  };break;

	  case 2:{
		  clrscr();
		  cout<<"\n 1.Issue";
		  cout<<"\n 2.Return";
		  cout<<"\n 3.Search by ID";
		  cout<<"\n 4.Display All Records";
		  cout<<"\n 5.Exit";
		  cout<<"\n Enter your choice (1-5): ";
		  cin>>choice;
		  switch(choice)
			{
			 case 1:
			        clrscr();
			        dd.ISSUE(); Write_record(dd); break;

		         case 2:
				clrscr();
				cout<<"\n Enter the Issue ID: ";
				cin>>id;
				Update_record(id);
 				cout<<"\n Days after book is returned: ";
				cin>>fine_day;
				if(fine_day > 20)
			          cout<<"\n The fine is: Rs."<<fine(fine_day);
				else
			          cout<<"\n Thanks.";
			        break;
                                
			 case 3:
				clrscr();
				cout<<"\n Enter the Issue ID: ";
				cin>>id;
				display_record(id);break;
					  
			 case 4:
			        clrscr();
			        displayall_record();break;
							  
		         case 5:
                                break;
				
       		         default:
                                 break;					   
		        };
	  };break;
	  
	  case 3:
	         break;
			 
	  default: 
                break; 	  
  };

  cout<<"\n\n\n\ Do you want to continue? ";
  cin>>ch;
} while(ch=='y'||ch=='Y');

getch();
}
