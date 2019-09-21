#include<stdio.h>
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include <stdlib.h>
#include <fstream>
#include<process.h>
#include<dir.h>

using namespace std;


class user
{
	char userid[10];
	char pass[10];
	char name[10];
	char n;
	public :
		void read();
		void reset();
		void signup();
		user login(int *checker);
		void sopen(char *ptr);
		int srch_file(char *ptr);
		void getuser_name(char *nm)
		{
			strcpy(nm,name);
		}
		void pttrns(char *pttr);
				
};



class file
{
	char name[20];
	char path[150];
	char data[20];
	public:
		void operator <<(file &fp2);
	    file();     //cunstructor   get name and path of file
	    file(char *user,char *filename);  //overloaded cunstructor 
		void write(file &);   //it writes the result of search function in the another file whose pointer we give as parameter
		void show();         //print the data of file on screen......file must be read by read() function before show()
		void search(char *); //it searches for given word and store the positions of that word in a linked list
		char getword(FILE *);   //from current cursor position it retrive next word from the file
		void encode();    //encode data 
		void decode();	//decode data	
		void upper_lower(int );   //converts data into uppercase
		void update();
		void removeit()
		{
			remove(path);
		}
};

class dictionary;

class word
{
	char w[10];
	char perm_words[40320][11];
	int size,perm_pos;
	public:
		void permute(const int start);
		friend void find_word(dictionary &d,word &w);
	word()
	{
		 cout<<"\nEnter a word:\n"<<endl;	 
	 	 cin>>w;
	 	 size=strlen(w);
	 	 perm_pos=0;
	 	 for(int j=0; j<size; j++)
	   	w[j]=tolower(w[j]);
	   	permute(0);
	   	
	}
	
};



class dictionary
{
	string *list;
	public:
		dictionary();
		friend void find_word(dictionary &d,word &w);
};


char tmp[150];
FILE *tempfile;
struct posns
	{
		int pos;
		struct posns *nextpos;
	};
struct lines
{
	int lineno;
	struct lines *nextline;
	struct posns *headp;
}*headl;

 class stack
{
    int top;
    char data[100001];
    public:
    	stack()
    	{
    	top=-1;
    	}
    	void push(char op);
    	char pop();
    	int isEmpty();
    	char peek(int i);
    	void print_stack();
    	int gettop()
    	{return top;
		}
};


int stack::isEmpty()
{
    return top == -1 ;
}


char stack::peek(int i)
{
    return data[i];
}


char stack::pop()
{
    if (!isEmpty())
        return data[top--] ;
    return '$';
}


void stack::push(char op)
{
if(top==10000)
{
printf("stack is full");
system("pause");
exit(0);
}
    data[++top] = op;
}


void stack::print_stack()
{
	int i=0;
	char arr[10001];

	system("cls");
	for(;i<=top;i++)
	{
		printf("%c",data[i]);
	}	
}


int user::srch_file(char *ptr)   //finds users files by name
		{
			fstream f;
			char tmp[15];
			int flag=0;
			strcpy(tmp,name);
			strcat(tmp,"\\");
			strcat(tmp,userid);
			strcat(tmp,"#.txt");
			f.open(tmp,ios::in);
			f.seekg(0);
			while(f>>tmp)
			{
				if(strcmp(ptr,tmp)==0)
				{
					flag=1;
					break;
				}
			}
			if(flag==0)
			cout<<"this file is not exist\n";
			f.close();
			return flag;
		}


void user::sopen(char *ptr)   //creats a file for track files created by particular user
		{
			fstream f;
			char tmp[35];
			strcpy(tmp,name);
			strcat(tmp,"\\");
			strcat(tmp,userid);
			strcat(tmp,"#.txt");
			f.open(tmp,ios::out|ios::app);
			f<<ptr<<"\n";
			f.close();
			strcpy(tmp,name);
			strcat(tmp,"\\");
			strcat(tmp,ptr);
			strcat(tmp,".txt");
			f.open(tmp,ios::out|ios::app);
			f.close();
		}


	user user::login(int *checker)  //searches user exists or not and login
		{
			fstream file;
			char tmp_userid[10],tmp_pass[10];
			int flag=0;
			cout<<"user ID\n";
			cin>>tmp_userid;
			file.open("user_info.txt",ios::in);
			file.seekg(0);
			
			while(file.read((char *)this,sizeof(user)))
			{
			    if(strcmp(userid,tmp_userid)==0)
			    {
			        flag=1;
			        break;
				}
			}
			
			if(flag)
			{
				char c;
				int i=0;
			    cout<<"password\n";
			    while(i<9)
			    {
				c=getch();
				if(c==13)
				{
					pass[i]='\0';
					cout<<"\n";
					break;
				}
				cout<<"*";
				tmp_pass[i++]=c;
			    }
			    if(strcmp(pass,tmp_pass)==0)
			    {
			    	file.close();
			    	*checker=1;
			        return *this;
				}
				else
				cout<<"password incorrect\n";
			}
			else
			cout<<"incorrect user_id\n";
			*checker=0;
			file.close();
			return *this;
		}

void user::pttrns(char *pttr)
		{
			fstream f;
			char tmp[15];
			int flag1=1;
			strcpy(tmp,name);
			strcat(tmp,"\\");
			strcat(tmp,userid);
			strcat(tmp,"#.txt");
			f.open(tmp,ios::in);
			f.seekg(0);
			while(f>>tmp)
			{
				int i=0,n,flag=1;
				if(strlen(tmp)==strlen(pttr))
				{
					while(pttr[i]!='\0')
					{
						if(pttr[i]!=tmp[i] && pttr[i]!='?')
						{
							flag=0;
							break;
						}
						i++;
					}
					if(flag)
					{
						cout<<tmp<<endl;
						flag1=0;
					}
				}
				
			}
			if(flag1)
			cout<<"no file found\n";
		}

void user::reset()
		{
			int i;
			while(i<10)
			userid[i++]='\0';
			i=0;
			while(i<10)
			pass[i++]='\0';
			i=0;
			while(i<10)
			name[i++]='\0';
		}


void user::read()
		{
			int i=0;
			char c;
			cout<<"enter user ID\n";
			cin>>userid;
			cout<<"enter password\n";
			while(i<9)
			{
				c=getch();
				if(c==13)
				{
					pass[i]='\0';
					cout<<"\n";
					break;
				}
				cout<<"*";
				pass[i++]=c;
			}
			cout<<"enter user name\n";
			cin>>name;
			n='\n';
			int check=mkdir(name);
			char tmp[35];
			strcpy(tmp,name);
			strcat(tmp,"\\");
			strcat(tmp,userid);
			strcat(tmp,"#.txt");
			fstream f;
			f.open(tmp,ios::out|ios::app);
			f.close();
		}

void file::update()
{
	char ch,elem;
	stack s2,data;
	FILE *fptr;
	cout<<"\n\n\tctrl+z for undo operation\n\n\tctrl+y for redo operation\n\n\tctrl+s for save file and exit\n";
	system("pause");
	system("cls");

if((fptr=fopen(path,"r"))==NULL)
printf("\nerror in opening file\n");
while((ch=fgetc(fptr))!=EOF)
{
	cout<<ch;
	data.push(ch);
}
fclose(fptr);
	while((ch=getch())!=19)
	{
		if(ch!=26 && ch!=25 &&ch!='\b')
		{
			if(ch==13)
				ch='\n';
			data.push(ch);
			printf("%c",ch);
		}
		else if(ch==26)
		{
			while(!data.isEmpty()&&(elem=data.pop())){
				if(elem==13)
				elem='\n';
				s2.push(elem);
				if(elem==' ')
				break;
			}
			data.print_stack();
		}
		else if((ch=='\b')&&(!data.isEmpty()))
		{
			data.pop();
			data.print_stack();
		}
		else
		{
			while(!s2.isEmpty()&&(elem=s2.pop()) )
			{
				if(elem==13)
				elem='\n';
				data.push(elem);
				if(elem==' ')
				break;
			}
			data.print_stack();
		}
		if(data.isEmpty()&&s2.isEmpty())
		break;
	}
	int top=data.gettop();
	if((fptr=fopen(path,"w"))==NULL)
	printf("\nerror in opening file\n");
	for(int i=0;i<=top;i++)
	{
		ch=data.peek(i);
		fputc(ch,fptr);
	}
	fclose(fptr);
}


void user::signup()
		{
			fstream file;
			char c=0;
			reset();
			read();
			file.open("user_info.txt",ios::out|ios::app);
			file.write((char *)this,sizeof(user));
			file.close();
			cout<<"account is created plzz login\n";
		}



file::file()
{
	char p[150];
	printf("\nenter the file name\n");
	fflush(stdin);
	cin>>name;
	strcat(name,".txt");
	printf("\nenter path of file\n {press 0 if it is in same folder from where program run}\n");
	cin>>p;
	if(p[0]=='0')
	{
		strcpy(path,name);
		strcpy(tmp,"jdjdjd.txt");
		//if((tempfile=fopen("jdjdjd.txt","w"))==NULL)
	    //printf("\nerror in opening temporary  file\n");
	}
	else
	{
		int j=0;
		for(int i=0;p[i]!='\0';i++)
		{
			if(p[i]=='\\')
			{
				path[j]=p[i];
				j++;
			}
			path[j]=p[i];
			j++;
		}
		
		
		path[j]='\0';
		strcpy(tmp,path);
		strcat(path,name);
		strcat(tmp,"jdjdjd.txt");
		
	}
	
}


file::file(char *user,char *filename)
{
	strcpy(path,user);
	strcat(path,"\\");
	strcat(path,filename);
	strcat(path,".txt");
	strcpy(tmp,"jdjdjd.txt");
	
}



void file::operator <<(file &fp2)  //operator overloading for merge files
		{
		    char ch;
		    FILE *p1=fopen(path,"a+");
		    FILE *p2=fopen(fp2.path,"r");
            if (p2 == NULL)
            {
            puts("Could not open files");
            exit(0);
            }
            fputc('\n',p1);
            while((ch=fgetc(p2))!=EOF)
                fputc(ch,p1);

            fclose(p1);
            fclose(p2);
         }

void file::encode()
{
FILE *fptr;
int ch,w;
if((fptr=fopen(path,"r"))==NULL)
printf("\nerror in opening file\n");

if((tempfile=fopen(tmp,"w"))==NULL)
	    printf("\nerror in opening file\n");

ch=fgetc(fptr);
fseek(fptr,0L,0);
while((w=fgetc(fptr))!=EOF)
{
	w=w+ch;
	fputc(w,tempfile);
}
fclose(fptr);
fclose(tempfile);
remove(path);
cout<<"\ncompleted encoding\n";
rename(tmp,path);
}




void file::decode()
{
 FILE *fptr;
 int ch,w;
if((fptr=fopen(path,"r"))==NULL)
printf("\nerror in opening file\n");

if((tempfile=fopen(tmp,"w"))==NULL)
	    printf("\nerror in opening file\n");

ch=fgetc(fptr);
ch=ch/2;
fseek(fptr,0L,0);
while((w=fgetc(fptr))!=EOF)
{
	w=w-ch;
	fputc(w,tempfile);
}
fclose(fptr);
fclose(tempfile);
remove(path);
cout<<"\ncompleted decoding\n";
rename(tmp,path);
}


void file::upper_lower(int c)
		{
		char ch;
	       FILE *fp;
								fp = fopen(path,"r");
	       						if((tempfile=fopen(tmp,"w"))==NULL)
	 							   printf("\nerror in opening file\n");
	      						system("cls");
								  if(c==1)
								{
									ch=fgetc(fp);
					   				while(ch!=EOF)
									   {	
									        if(ch>=97 && ch<=122)
	              							ch=ch-32;
	              							fprintf(tempfile,"%c",ch);
	       									printf("%c",ch);  	
									   		ch = fgetc(fp);
	       								}
	       						}
	       						else
	       						{
	       							ch=fgetc(fp);
	       							while(ch!=EOF)
									   {	  	
	              							if(ch>=65 && ch<=90)
	              								ch=ch+32;
	              							fprintf(tempfile,"%c",ch);
	       									printf("%c",ch);
	       									ch = fgetc(fp);
	       								}
								}
					   					fclose(fp);
										fclose(tempfile);	
										remove(path);
					   					printf("\nSuccessfully Converted\n");
					   					rename(tmp,path);
}

char file::getword(FILE *fptr)  //from current cursor position it retrive next word from the file 
{
	char ch;
	int i=-1;
do
	{
		i++;
		ch=fgetc(fptr);
	data[i]=ch;
	}while((ch!=' ')&&(ch!='\n')&&(ch!=EOF));	
	data[i]='\0';
	return ch;
}


void file::show()
{
FILE *fptr;
int ch;
if((fptr=fopen(path,"r"))==NULL)
printf("\nerror in opening file\n");
while((ch=fgetc(fptr))!=EOF)
{
	printf("%c",ch);
}
fclose(fptr);
}


void file::search(char *word)
{
	int i=0,count=0,pos=0,line=1,flag=0;
FILE *fptr;
if((fptr=fopen(path,"r"))==NULL)
printf("\nerror in opening file\n");

while(1)
{
	char ch;
	ch=getword(fptr);
	pos++;
	if(!(strcmp(data,word)))
	{
		count++;
		if(headl==NULL)
		{
			struct lines *temp;
			temp=new lines;
			temp->lineno=line;
			temp->nextline=NULL;
			temp->headp=new posns;
			temp->headp->pos=pos;
			temp->headp->nextpos=NULL;
			headl=temp;
		}
		else if(flag==0)
		{
			struct lines *temp,*travrs;
			temp=new lines;
			temp->lineno=line;
			temp->nextline=NULL;
			temp->headp=new posns;
			temp->headp->pos=pos;
			temp->headp->nextpos=NULL;
			travrs=headl;
			while(travrs->nextline!=NULL)
			travrs=travrs->nextline;
			travrs->nextline=temp;
			flag=1;
		}
		else
		{
			struct lines *travrsl;
			travrsl=headl;
			while(travrsl->nextline!=NULL)
			travrsl=travrsl->nextline;
			struct posns *trvrsp,*temp;
			trvrsp=travrsl->headp;
			while(trvrsp->nextpos!=NULL)
			trvrsp=trvrsp->nextpos;
			temp=new posns;
			temp->pos=pos;
			temp->nextpos=NULL;
			trvrsp->nextpos=temp;
		}
		
	}
		if(ch=='\n')
		{
		flag=0;
		pos=0;
		line++;	
		}
		if(ch==EOF)
		{
			printf("\ndone\n");
			fclose(fptr);
			return;
		}
}
}


void file::write(file &input)
{
	FILE *fptr,*source;
	fptr=fopen(path,"w");
	fprintf(fptr,"line no.\t\t\tpositions\n...................................................................................\n");
	struct lines *trvrsl;
	struct posns *trvrsp;
	trvrsl=headl;
	while(trvrsl!=NULL)
	{
		trvrsp=trvrsl->headp;
		fprintf(fptr,"  %d\t\t  ",trvrsl->lineno);
		while(trvrsp!=NULL)
		{
			fprintf(fptr,"%d",trvrsp->pos);
			trvrsp=trvrsp->nextpos;
		}
		fprintf(fptr,"\n");
		trvrsl=trvrsl->nextline;
	}
	fprintf(fptr,"\n............................................................................................................................\n");
	source=fopen(input.path,"r");
	int line=1;
	char ch;
	trvrsl=headl;
	while(trvrsl!=NULL)
	{
	if(trvrsl->lineno==line)
	{
		fprintf(fptr," line no. %d\t",trvrsl->lineno);
		do
		{
			ch=fgetc(source);
			fprintf(fptr,"%c",ch);
		}while((ch!='\n')&&(ch!=EOF));
		fprintf(fptr,"\n");
		trvrsl=trvrsl->nextline;
	}
	else
	while((ch=fgetc(source))!='\n');
	line++;
	}
	fclose(fptr);
}


void word::permute(const int start)
{  
static char *v=w;
  if (start == size-1)
  {
	  sprintf(perm_words[perm_pos++],"%s",v);
  }
  else
   {
    for (int i = start; i < size; i++) 
	{
      int tmp = v[i];
      
      v[i] = v[start];
      v[start] = tmp;
      permute(start+1);
      v[start] = v[i];
      v[i] = tmp;

    }
  }
}


void find_word(dictionary &d,word &w)
{
	for (int i=0; i<109583; i++)
	{
		for (int j=0; j<w.perm_pos; j++)
		{
		if(w.perm_words[j]==d.list[i])
		{
	cout<<"spelling suggestions: "<<d.list[i]<<endl;
		}
		}
	}
}


dictionary::dictionary()
{
	ifstream infile("words.txt");
	list = new string[109583];
	if (infile.is_open())
	{
		for (int i=0; i <109583; i++)
		{
			getline(infile, list[i]);
		}
	}
	
	infile.close();
}


int menu(char *name,char *filename)
{
	file f(name,filename);
	int ch;
	while(1)
	{
		
	cout<<"\nenter your choice\n\n1. encode a file\n\n2. decode a file\n\n3. find word\n\n4. show file\n\n5. run spelling suggester\n\n6. convert to uppercase or lowercase\n\n7. merge another file\n\n8. Edit file\n\n9. delete this file\n\n0. for close file\n";
	cin>>ch;
	system("cls");
	switch(ch)
	{
		case 0:
			return 0;
			break;
		case 1:
			f.encode();
			break;
		case 2:
			f.decode();
			break;
		case 3:
			{
				char word_for_find[30];
			cout<<"\nenter the word you want to search\n";
			cin>>word_for_find;
			printf("\nenter details of file where search result will be store\n");
			{
			file output;
			f.search(word_for_find);
			output.write(f);
			output.show();
			}
		}
			break;
		case 4:
			f.show();
			cout<<endl<<endl;
			break;
		case 5:
			{
			word w;
			dictionary d;
			find_word(d,w);
			}
			break;
			case 6:
				int c;
			cout<<"\n\n1. convert to uppercase\n\n2. convert to lower case\n\n";
			cin>>c;
			f.upper_lower(c);
			cout<<endl<<endl;
			break;
			case 7:
				{
				file f2;
			    f<<f2;
				cout<<endl<<"file successfully merged";
				}
			break;
			case 8:
				f.update();
			break;
			case 9:
				f.removeit();
				return 0;
			break;
	}
	system("pause");
	system("cls");
}
}

int main()
{
	int n,un;
	do
	{
		system("cls");	
		user u2;
		cout<<"\n\n**********welcome*********\n\n1. signup\n2. login\n3. exit\n";
		cin>>n;
		switch(n)
		{
			case 1:
				{
					u2.signup();
					system("pause");
					system("cls");
					break;
				}
			case 2:
				{
					int flag;
					u2=u2.login(&flag);
					system("pause");
					system("cls");
					if(flag)
					{
					int choi;
					do
					{
					cout<<"\n\n you are logged in\n\n";
					int n;
					char filename[20];
					cout<<"1. create new file\n\n2. open existing file\n\n3. logout\n";
					cin>>n;
					un=n;
					system("cls");
					switch(n)
					{
						case 1:
							{
								char name[20];
								cout<<"enter new file name\n";
								cin>>filename;
								u2.sopen(filename);
								u2.getuser_name(name);
								menu(name,filename);
								break;
							}
						case 2:
							{
								int m;
								cout<<"\n\n1. open file by file_name\n\n2. search file_name by pattern\n\n";
								cin>>m;
								system("cls");
								switch(m)
								{
									case 1:
										{
										char name[20];
										cout<<"\n\nenter existing file name1\n";
								        cin>>filename;
								        if(u2.srch_file(filename))
								        {
								        	u2.getuser_name(name);
								        	menu(name,filename);
										}
										else
										{
											system("pause");
										}
								        break;
								    	}
								    case 2:
								    	{
								    		char pttrn[15];
								    		cout<<"enter pattern\n";
								    		cin>>pttrn;
								    		u2.pttrns(pttrn);
								    		break;
										}
								}
								
							break;
							}
					}
			        
			        }while(un!=3);
			        
			        }
				}
				
		}	
	}while(n!=3);
    return 0;
	
}
