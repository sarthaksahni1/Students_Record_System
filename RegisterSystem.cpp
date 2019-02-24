#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream.h>
#define TRUE 1
#define FALSE 0

typedef struct Student {
	double IDsStudent;
	char *pw;
	char condition;
	char* fName;
	char* lName;
	char* aName;
	char Field;
	char* Note;
	struct Student *Next;
} Student;
typedef Student *pStudent;

void PrintDataStudent(pStudent T);
void LoadDataStudent(pStudent TT,double sID, char *pw,char con, char *First, char *Last, 
					 char *Advisor,char field,char *Note );
bool UserChecker(pStudent T,double username, char *password, pStudent *TP);




pStudent CreateListStudent()
{
	pStudent T;
	T = (Student*)malloc(sizeof(Student));
	if (T == NULL) {
		printf("Out of memory!!!");
		exit(0);
	}
	T->Next = NULL;
	return T;
}

pStudent AdvanceStudent(pStudent T)
{
	return T->Next;
}

void InputDataStudent(pStudent TT)
{
    Student T;
	char fname[30],lname[30],aname[30],note[256],pw[15];

			printf("Enter Student ID : ");
			scanf("%lf",&(T.IDsStudent));
			printf("Enter Student Password : ");
			scanf(" %s",pw);
					printf("Enter student condition : ");
					scanf(" %c",&(T.condition));    
			printf("Enter student First-name : ");
			scanf(" %s",fname);
					printf("Enter student Last-name : ");
					scanf(" %s",lname);
			printf("Enter student's Advisor name : ");
			scanf(" %s",aname);
					printf("Enter Field : ");
					scanf(" %c",&T.Field);
			printf("Enter Note : ");
			scanf(" %s",note);
		
	LoadDataStudent(TT,T.IDsStudent,pw,T.condition,fname,lname,aname,T.Field,note );
}	

void PrintDataStudent(pStudent T)
{
	int count=0;
	if (T == NULL) 
			printf("\nEmpty!!!\n");
	else 
		{
		int i=0;
		do
		{
			printf("\n\nStudents ID\t: %.0lf"
				   "\nStudent Password\t: %s"
			       "\nStudent condition\t: %c"
				   "\nStudent Fname\t: %s"
				   "\nStudent Lname\t: %s"
		           "\nStudent Aname\t: %s"
				   "\nStudent Field\t: %c"
				   "\nStudent Note\t: %s",T->IDsStudent,T->pw,T->condition,T->fName,T->lName,T->aName,T->Field,T->Note);
				   T = AdvanceStudent(T);
				   count++;
		} while (T != NULL);
	}
	printf("\n\n>>>%d data has been viewed.",count);
	getch();
}

void DeleteStudent(pStudent T)
{
	double tID;
	pStudent P=T, tmp;
	
	printf("Enter student ID to delete : ");
	scanf("%lf",&tID);

	while(P->Next != NULL && tID != P->Next->IDsStudent)
		P = P->Next;

	tmp = P;
 
    if(P->Next != NULL) {
        tmp = P->Next;
        P->Next = tmp->Next;  
        free( tmp );
		printf("\nDeleted!!!");
		getch();
    }
}
void FindStudent(pStudent T)
{
		double tID;
		pStudent P;

		printf("Enter teacher ID to look : ");
		scanf("%lf",&tID);
		P = T;
		while(P  != NULL && tID != P->IDsStudent)
		P = P->Next;
		T = P;

		if (T != NULL) {
					printf("\n\nStudents ID\t: %.0lf"
						     "\nStudent Password\t: %s"
							 "\nStudent condition\t: %c"
							 "\nStudent First-Name\t: %s"
							 "\nStudent Last-Name\t: %s"
							 "\nStudent Advisor-Name\t: %s"
							 "\nStudent Field\t: %c"
							 "\nStudent Note\t: %s",T->IDsStudent,T->pw,T->condition,T->fName,T->lName,T->aName,T->Field,T->Note);
		} else
        printf("\nData was not founded!!!\n");
		getch();
}

void PrintFileStudent(pStudent T)
{
	char tmpname[30];
	FILE *fpStudent;

	printf("Enter file's name to be printed : ");
	scanf("%s",tmpname);
	strcat(tmpname,".txt");


	fpStudent = fopen (tmpname,"w+");
	if(fpStudent == NULL)
		printf("\nFile Not Accessed!!!\n");
	else {
				int count=0;
				if (T == NULL) 
						printf("\nEmpty!!!\n");
				else 
					{
					int i=0;
					do
					{
						fprintf(fpStudent,"\nStudents ID\t: %.0lf"
										  "\nStudent Password\t: %s"
										  "\nStudent condition\t: %c"
										  "\nStudent First-Name\t: %s"
										  "\nStudent Last-Name\t: %s"
										  "\nStudent Advisor-Name\t: %s"
										  "\nStudent Field\t: %c"
										  "\nStudent Note\t: %s",T->IDsStudent,T->pw,T->condition,T->fName,T->lName,T->aName,T->Field,T->Note);
							T = AdvanceStudent(T);
							count++;
					} while (T != NULL);
				}
				fprintf(fpStudent,"\n\n>>>%d data has been viewed.",count);
	}
	fclose(fpStudent);
	printf("\nData has been written!!!\n");
	getch();
}

void SaveStudent(pStudent T)
{
	char tmpname[30];
	FILE *fpStudent;

	printf("Enter save name : ");
	scanf("%s",tmpname);
	strcat(tmpname,".kks");


	fpStudent = fopen (tmpname,"w+");
	if(fpStudent == NULL)
		printf("\nFile Not Accessed!!!\n");
	else {
				int count=0;
				if (T == NULL) 
						printf("\nEmpty!!!\n");
				else 
					{
					int i=0;
					do
					{
						fprintf(fpStudent," %.0lf  %s  %c  %s  %s  %s  %c  %s"
							 ,T->IDsStudent,T->pw,T->condition,T->fName,T->lName,T->aName,T->Field,T->Note);
							T = AdvanceStudent(T);
							count++;
					} while (T != NULL);
				}
	}
	fclose(fpStudent);
	printf("\nData has been saved!!!\n");
	getch();
}
void LoadDataStudent(pStudent TT,double sID,char *pw, char con, char *First, char *Last, 
					 char *Advisor,char field,char *Note )
{	
    char *pFirst,*pLast,*pAdvisor,*pNote,*pW;
    Student T;
    pStudent PT;

	if (TT->Next == NULL)
	{
			T.IDsStudent = sID;
			T.condition = con;
			T.Field = field;
					pW = (char*) malloc(strlen(pw));
					strcpy(pW,pw);
					T.pw = pW;
			pFirst =(char*) malloc(strlen(First));
			strcpy(pFirst,First);
			T.fName = pFirst;
					pLast =(char*) malloc(strlen(Last));
					strcpy(pLast,Last);
					T.lName = pLast;
			pAdvisor =(char*) malloc(strlen(Advisor));
			strcpy(pAdvisor,Advisor);
			T.aName = pAdvisor;
				pNote =(char*) malloc(strlen(Note));
				strcpy(pNote,Note);
				T.Note = pNote;
		
			PT = (pStudent)malloc(sizeof(Student));
			if (PT == NULL) {
				printf("Out of memory!!!");
				exit(0);
			}
			else {
				PT->IDsStudent =T.IDsStudent;
				PT->condition = T.condition;    
				PT->pw = (char*) malloc(sizeof(pw));
					PT->pw = T.pw;
				PT->fName = (char*) malloc(sizeof(First));
					PT->fName = T.fName;
				PT->lName = (char*) malloc(sizeof(Last));
					PT->lName = T.lName;
				PT->aName = (char*) malloc(sizeof(Advisor));
					PT->aName = T.aName;
				PT->Field = T.Field;
				PT->Note = (char*) malloc(sizeof(Note));
					PT->Note = T.Note;
				TT->Next = PT;
				PT->Next = NULL;	
			}
	}
	else {
		LoadDataStudent(TT->Next,sID,pw,con,First,Last,Advisor,field,Note);
	}
}


void LoadStudent(pStudent T)
{
	char tmpname[30];
	double tID;
    char First[30],Last[30],Advisor[30],Note[256],condition,field,pw[15];
	FILE *fpStudent;
	int count=0;

	printf("Enter file's name : ");
	scanf("%s",tmpname);
	strcat(tmpname,".kks");

	fpStudent = fopen (tmpname,"r");
	if(fpStudent == NULL) 
		printf("\nFile Not Found!!!\n");
		
	
	else {
			if (T->Next == NULL)
			{
				if (T == NULL) 
						printf("\nEmpty!!!\n");
				else 
					{
					while(!feof(fpStudent))	{
						
					fscanf(fpStudent,"%lf %s %c %s %s %s %c %s"
							 ,&tID,pw,&condition,First,Last,Advisor,&field,Note);
					LoadDataStudent(T,tID,pw,condition,First,Last,Advisor,field,Note);
					count++;
					}
					printf("%d file has been loaded.\n",count);
				}
			}
			fclose(fpStudent);}
	getch();
}

void AdminStudent(pStudent T)
{

	short int menu;


	do {
        system("cls");
		printf("Student(s) Data\n"
			   "1. Insert data.\n"
			   "2. Print Data.\n"
			   "3. Delete Data\n"
			   "4. Find Data\n"
			   "5. Print Data to Text File.\n"
			   "6. Save File.\n"
			   "7. Load File.\n"
			   "0. Exit\n\n"
			   "Input : ");
		scanf("%d",&menu);

		switch(menu) {
		case 1 :	    InputDataStudent(T);
			break;
		case 2 :		PrintDataStudent(T->Next);
			break;
		case 3 :		DeleteStudent(T);
			break;
		case 4 :		FindStudent(T);
			break;
		case 5 :        PrintFileStudent(T->Next);
			break;
		case 6 :		SaveStudent(T->Next);
			break;
		case 7 :		LoadStudent(T);
			break;
		}
	}
	while(menu != 0);
}


typedef struct Subject {
	double IDs;
	char Subj[7];
	short int sec;
	short int creadit;
	short int grade;
	short int sw;
	struct Subject *Next;
} Subject;
typedef Subject *pSubject;

void PrintDataSubject(pSubject S);
void LoadDataSubject(pSubject SS,double IDs,char *subject, short int sec,short int creadit,short int grade, short int sw);


pSubject CreateListSubject()
{
	pSubject S;
	S = (pSubject)malloc(sizeof(Subject));
	if (S == NULL) {
		printf("Out of memory!!!");
		exit(0);
	}
	S->Next = NULL;
	return S;
}

pSubject AdvanceSubject(pSubject S)
{
	return S->Next;
}

void InputDataSubject(pSubject SS)
{
    Subject S;

					printf("Enter Student ID : ");
					scanf("%lf",&S.IDs);
			printf("Enter Subject : ");
			scanf("%s",S.Subj);
					printf("Enter Section : ");
					scanf(" %d",&S.sec);    
			printf("Enter Creadit : ");
			scanf(" %d",&S.creadit);
					printf("Enter the result : ");
					scanf(" %d",&S.grade);
			printf("Enter Subject Period : ");
			scanf("%d",&S.sw);
		
		LoadDataSubject(SS,S.IDs,S.Subj,S.sec,S.creadit,S.grade,S.sw);		
}																			

pSubject HeaderSubject(pSubject S)
{
		return S;
}
void PrintDataSubject(pSubject S)
{
	int count=0;
	if (S == NULL) 
			printf("\nEmpty!!!\n");
	else 
		{
		int i=0;
		do
		{
			printf("\n\nStudents IDs\t: %.0lf"
			     "\nSubject\t: %s"
				 "\nSection\t: %d"
				 "\nCreadit\t: %d"
		         "\nResult\t: %d"
				 "\nPeriod\t: %d"
				 ,S->IDs,S->Subj,S->sec,S->creadit,S->grade,S->sw);
				S = AdvanceSubject(S);
				count++;
		} while (S != NULL);
	}
	printf("\n\n>>>%d data has been viewed.",count);
	getch();
}

void DeleteSubject(pSubject S)
{
	char subjTmp[7];
	double sid;
	pSubject P=S, tmp;
	
	printf("Enter students ID and subject to delete : ");
	scanf("%ld",&sid);
	scanf(" %s",subjTmp);

	while(P->Next != NULL && strcmp(P->Next->Subj,subjTmp)!=0 && P->Next->IDs != sid)
		P = P->Next;

	tmp = P;
 
    if(P->Next != NULL) {
        tmp = P->Next;
        P->Next = tmp->Next;  
        free( tmp );
		printf("\nDeleted!!!");
		getch();
    }
}
void FindSubject(pSubject S)
{
		char subjTmp[7];
		double sid;
		pSubject P=S;

		printf("Enter student id and subject to find : ");
		scanf("%lf",&sid);
		scanf("%s",subjTmp);

		while(P->Next != NULL && strcmp(P->Next->Subj,subjTmp)!=0 && P->Next->IDs != sid)
		P = P->Next;

		S = P->Next;
		if (S != NULL) {
			printf("\n\nStudents IDs\t: %.0lf"
			     "\nSubject\t: %s"
				 "\nSection\t: %d"
				 "\nCreadit\t: %d"
		         "\nResult\t: %d"
				 "\nPeriod\t: %d"
				 ,S->IDs,S->Subj,S->sec,S->creadit,S->grade,S->sw);
		} else
        printf("\nData was not founded!!!\n");
		getch();
}

void PrintFileSubject(pSubject S)
{
	char tmpname[30];
	FILE *fpTeacher;

	printf("Enter file's name to be printed : ");
	scanf("%s",tmpname);
	strcat(tmpname,".txt");


	fpTeacher = fopen (tmpname,"w+");
	if(fpTeacher == NULL)
		printf("\nFile Not Accessed!!!\n");
	else {
				int count=0;
				if (S == NULL) 
						printf("\nEmpty!!!\n");
				else 
					{
					int i=0;
					do
					{
							fprintf(fpTeacher,"\n\nStudents IDs\t: %.0lf"
											 "\nSubject\t: %s"
											 "\nSection\t: %d"
											 "\nCreadit\t: %d"
											 "\nResult\t: %d"
											 "\nPeriod\t: %d"
											 ,S->IDs,S->Subj,S->sec,S->creadit,S->grade,S->sw);
							S = AdvanceSubject(S);
							count++;
					} while (S != NULL);
				}
				fprintf(fpTeacher,"\n\n>>>%d data has been viewed.",count);
	}
	fclose(fpTeacher);
	printf("\nData has been written!!!\n");
	getch();
}

void SaveSubject(pSubject S)
{
	char tmpname[30];
	FILE *fpTeacher;

	printf("Enter save name : ");
	scanf("%s",tmpname);
	strcat(tmpname,".kkc");


	fpTeacher = fopen (tmpname,"w+");
	if(fpTeacher == NULL)
		printf("\nFile Not Accessed!!!\n");
	else {
				int count=0;
				if (S == NULL) 
						printf("\nEmpty!!!\n");
				else 
					{
					int i=0;
					do
					{
							fprintf(fpTeacher," %.0lf %s %d %d %d %d",S->IDs,S->Subj,S->sec,S->creadit,S->grade,S->sw);
							S = AdvanceSubject(S);
							count++;
					} while (S != NULL);
				}
	}
	fclose(fpTeacher);
	printf("\nData has been saved!!!\n");
	getch();
}
void LoadDataSubject(pSubject SS,double IDs,char *subject, short int sec,short int creadit,short int grade, short int sw)
{	
    Subject S;
    pSubject PS;


	if (SS->Next == NULL)
	{
			S.IDs = IDs;
			strcpy(S.Subj,subject);
			S.sec = sec;
			S.creadit = creadit;
			S.grade = grade;
			S.sw = sw;
		
		
			PS = (pSubject)malloc(sizeof(Subject));
			if (PS == NULL) {
				printf("Out of memory!!!");
				exit(0);
			}
			else {
				strcpy(PS->Subj,S.Subj);
				PS->IDs = S.IDs;
				PS->sec = S.sec;
				PS->creadit = S.creadit;
				PS->grade = S.grade;
				PS->sw = S.sw;
				SS->Next = PS;
				PS->Next = NULL;	
			}
	}
	else {
		LoadDataSubject(SS->Next,IDs,subject,sec,creadit,grade,sw);
	}
}


void LoadSubject(pSubject S)
{
	char tmpname[30];
    Subject IS;
	FILE *fpTeacher;
	int count=0;

	printf("Enter file's name : ");
	scanf("%s",tmpname);
	strcat(tmpname,".kkc");

	fpTeacher = fopen (tmpname,"r");
	if(fpTeacher == NULL) 
		printf("\nFile Not Found!!!\n");
		
	
	else {
			if (S->Next == NULL)
			{
				if (S == NULL) 
						printf("\nEmpty!!!\n");
				else 
					{
					while(!feof(fpTeacher))	{
					fscanf(fpTeacher,"%lf %s %d %d %d %d",&IS.IDs,IS.Subj,&IS.sec,&IS.creadit,&IS.grade,&IS.sw);
					LoadDataSubject(S,IS.IDs,IS.Subj,IS.sec,IS.creadit,IS.grade,IS.sw);
					count++;
					}
					printf("\n%d file has been loaded.\n",count);
				}
			}
			fclose(fpTeacher);
	}
	getch();
}
void FindIDSubject(pSubject S)
{
	 double sid;
	 short int co=0;
	 pSubject keep[300],P;									   
	 P = S;

	 system("cls");
	 printf("Enter student ID : ");
	 scanf("%lf",&sid);
	
		for(;P->Next != NULL;P = P->Next)
			if(P->Next->IDs == sid){
				keep[co] = P->Next;
				co++;
			}
		

		printf("amount of co %d",co);
		if(co > 0){
			for(int k=0;k<co;k++){
				S = keep[k];
				printf("\n\nStudents IDs\t: %.0lf"
					 "\nSubject\t: %s"
					 "\nSection\t: %d"
					 "\nCreadit\t: %d"
					 "\nResult\t: %d"
					 "\nPeriod\t: %d"									
					 ,S->IDs,S->Subj,S->sec,S->creadit,S->grade,S->sw);	}
		} else
        printf("\nData was not founded!!!\n");
		getch();

}
void FindIDSubjectStudent(double ids,pSubject S)
{
	 double sid;
	 short int co=0,gr=0,cr=0;
	 pSubject keep[300],P;									   
	 P = S;

	 sid = ids;
	
		for(;P->Next != NULL;P = P->Next)
			if(P->Next->IDs == sid){
				keep[co] = P->Next;
				co++;
			}
		

		printf("\nAmount of subject %d\n",co);
		if(co > 0){
			for(int k=0;k<co;k++){
				S = keep[k];
				printf(
					 "\n\nSubject\t: %s"
					 "\nSection\t: %d"
					 "\nCreadit\t: %d"
					 "\nResult\t: %d"
					 "\nPeriod\t: %d"									
					 ,S->Subj,S->sec,S->creadit,S->grade,S->sw);
				gr += S->grade*S->creadit;
				cr += S->creadit;
			}
			printf("\n\nGPAX : %.3f",(float)gr/(float)cr);
		} else
        printf("\nData was not found!!!\n");
		getch();

}


void AdminSubject(pSubject S)
{
	short int menu;

	do {
        system("cls");
		printf("Subject Data\n"
			   "1. Insert data.\n"
			   "2. Print Data.\n"
			   "3. Delete Data\n"
			   "4. Find Data\n"
			   "5. Find Student and Subject(s).\n"
			   "6. Print Data to Text File.\n"
			   "7. Save File.\n"
			   "8. Load File.\n"
			   "0. Exit\n\n"
			   "Input : ");
		scanf("%d",&menu);

		switch(menu) {
		case 1 :	    InputDataSubject(S);
			break;
		case 2 :		PrintDataSubject(S->Next);
			break;
		case 3 :		DeleteSubject(S);
			break;
		case 4 :		FindSubject(S);
			break;
		case 5 :		FindIDSubject(S);
			break;
		case 6 :        PrintFileSubject(S->Next);
			break;
		case 7 :		SaveSubject(S->Next);
			break;
		case 8 :		LoadSubject(S);
			break;
		}
	}
	while(menu != 0);

}

bool PWcheck(char *pw)
{
	if (strcmp(pw,"system")==0)
		return TRUE;
	else
		return FALSE;
}

int CheckStudent(pStudent T)
{
	if (T->Next == NULL)
		return 0;
	else
		return CheckStudent(T->Next)+1;
}
int CheckSubject(pSubject S)
{
	 if (S->Next == NULL)
		return 0;
	else
		return CheckSubject(S->Next)+1;
}

void AdminSystem(pStudent T,pSubject S){

	short int in;

	do {
		system("cls");
		printf("[ Welcome, Administrator\n"
			   "[\n"
			   "[ Data Status\n"
			   "[ Student(s) Record : %d\n"
			   "[ Subject(s) Record : %d\n"
			   "[\n"
			   "[    Main Menu\n"
			   "[    1. Students Data Management\n"
			   "[    2. Subjects Data Management\n"
			   "[    0. Exit to login page\n"
			   "[ Input : ",CheckStudent(T),CheckSubject(S));
		scanf("%d",&in);

		switch(in){
		case 1 : 	AdminStudent(T);
			break;
		case 2 :	AdminSubject(S);
			break;
		}
	}while(in != 0);
}

void UserSystem(pStudent T, pSubject S);


void main()
{
	register pStudent T,TP;
	T = CreateListStudent();
	register pSubject S;
	S = CreateListSubject();

	double UserName;
	char PassWord[15];
	short int Invalid=0;

	do {
	system("cls");
	printf("[---------------------------------------------\n"
		   "[         L O G I N   S Y S T E M\n"
		   "[---------------------------------------------\n"
		   "[   PLEASE INPUT YOUR LOGIN CODE AND PASSWORD\n"
		   "[\n"
		   "[	USER NAME : ");
	scanf("%lf",&UserName);
	printf("[	PASSWORD  : ");
	scanf(" %s",PassWord);
	
	if (UserName == 1234 && PWcheck(PassWord))
			AdminSystem(T,S);
	else if	(UserChecker(T->Next,UserName,PassWord,&TP)) 
			UserSystem(TP,S);						
	else	Invalid++;

	}while(UserName != 0 || Invalid <3);
}

bool UserChecker(pStudent T,double username, char *password, pStudent *TP)
{
	while(T != NULL){
		if (T->IDsStudent == username && strcmp(T->pw,password)==0){
			*TP = T;
			printf("\ncompeting");
			return TRUE;
		}
		T = T->Next;
	}
	return FALSE;
}

void UserSystem(pStudent T, pSubject S)
{
	
		system("cls");
		printf("Welcome, %s %s\n\n",T->fName,T->lName);
		printf("Your Detail.\n"
			   "ID\t: %.0lf\n"
			   "First-Name\t: %s\n"
			   "Last-Name\t: %s\n"
			   "Advisor-Name\t: %s\n"
			   "Status\t: %c\n"
			   "Field\t: %c\n",T->IDsStudent,T->fName,T->lName,T->aName,T->condition,T->Field);

		FindIDSubjectStudent(T->IDsStudent,S);

}