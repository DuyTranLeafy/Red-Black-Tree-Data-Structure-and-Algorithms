#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <iomanip>

bool checkFileName;

using namespace std;
int n;
int temp = 0;

struct HOCVIEN
{
    char MSHV[9];
    char HTHV[31];
    char MMH1[5];
    char MMH2[5];
    int DM1,DM2;
};

enum COLOR {cRED, cBLACK};

struct BST
{
    HOCVIEN data;
    BST *left, *right, *parent;
    COLOR color;
}NULL_T;

void RB_INIT_BST(BST* &T)
{
    T = &NULL_T;
    NULL_T.color = cBLACK;
}

void RIGHT_ROTATE(BST* &T, BST* x)
{
    BST *y;
    y = x->left;
    x->left = y->right;
    if (y->right != &NULL_T) 
        (y->right)->parent = x;
    y->parent = x->parent;
    if (x->parent == &NULL_T) 
        T = y;
    else
        if (x == (x->parent)->right) 
            (x->parent)->right = y;
        else (x->parent)->left = y;
    y->right = x ; x->parent = y;
}

void LEFT_ROTATE(BST* &T, BST* x)
{
    BST *y;
    y = x->right;
    x->right = y->left;
    if (y->left != &NULL_T) 
        (y->left)->parent = x;
    y->parent = x->parent;
    if (x->parent == &NULL_T) 
        T = y;
    else
        if (x == (x->parent)->left) 
            (x->parent)->left = y;
        else (x->parent)->right = y;
    y->left = x ; x->parent = y;
}

void RB_INSERT_FIXUP(BST* &T, BST* z)
{
    BST *y;
    while ((z->parent)->color == cRED)
    {
        if (z->parent == ((z->parent)->parent)->left)
        {
            y = ((z->parent)->parent)->right;
            if (y->color == cRED)
            {
                (z->parent)->color = cBLACK;
                y->color = cBLACK;
                ((z->parent)->parent)->color = cRED;
                z = (z->parent)->parent;
            }
            else
            {
                if (z == (z->parent)->right) {
                z = z->parent; LEFT_ROTATE(T, z); 
                }
                (z->parent)->color = cBLACK;
                ((z->parent)->parent)->color = cRED; 
                RIGHT_ROTATE(T, (z->parent)->parent); 
            }
        }
        else
        {
            y = ((z->parent)->parent)->left;
            if (y->color == cRED) 
            {
                (z->parent)->color = cBLACK; 
                y->color = cBLACK;
                ((z->parent)->parent)->color = cRED; 
                z = (z->parent)->parent; 
            }
            else 
            { 
                if (z == (z->parent)->left)
                {
                    z = z->parent; 
                    RIGHT_ROTATE(T, z); 
                }
            (z->parent)->color = cBLACK; 
            ((z->parent)->parent)->color = cRED; 
            LEFT_ROTATE(T, (z->parent)->parent); 
            }
        }
    }
    T->color = cBLACK;
}

void RB_TREE_INSERT(BST* &T, HOCVIEN v)
{
    BST *z, *y, *x;
    z = new BST();
    z->data = v;
    z->left = &NULL_T;
    z->right = &NULL_T;
    z->color = cRED;
    y = &NULL_T;
    x = T;
    while (x != &NULL_T)
    {
        y = x;
        if (strcmp(z->data.MSHV,x->data.MSHV) < 0)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == &NULL_T)
        T = z;
    else
        if (strcmp(z->data.MSHV,y->data.MSHV) < 0)
            y->left = z;
        else
            y->right = z;
    RB_INSERT_FIXUP(T,z);
}

void PRINT_INF(BST* x)
{
    cout << setw(7) << left << x->data.MSHV << setw(20) 
	<< left << x->data.HTHV << setw(7) << left << x->data.MMH1 << setw(12) 
	<< left << x->data.DM1 << setw(7) << left << x->data.MMH2 
	<< setw(7) << left << x->data.DM2 << endl;

}

void PREORDER_TREE_WALK(BST *x)
{
    if (x != &NULL_T)
    {
        
        PREORDER_TREE_WALK(x->left);
        PRINT_INF(x);
        PREORDER_TREE_WALK(x->right);
    }
}

void READ_ONE_STUDENT(ifstream &filein, HOCVIEN &x)
{
    rewind(stdin);
    filein.getline(x.MSHV, 9, ',');
    filein.ignore();
    filein.getline(x.HTHV, 31, ',');
    filein.ignore();
    filein.getline(x.MMH1, 5, ',');
    filein.ignore();
    filein >> x.DM1;
    filein.ignore(2);
    rewind(stdin);
    filein.getline(x.MMH2, 5, ',');
    filein.ignore();
    filein >> x.DM2;
    filein.ignore();
}

void READ_FILE(BST* &T, string filename)
{
	ifstream filein;
    filein.open(filename.c_str());
    if (filein.fail())
    {
        cout << "Error !!" << endl;
        checkFileName = false;
    }
    else
    {
    	filein >> n;
        filein.ignore();
        for (int i=0; i<n; i++)
        {
            HOCVIEN a;
            READ_ONE_STUDENT(filein, a);
            RB_TREE_INSERT(T, a);
            checkFileName = true;
        }
    }
    filein.close();
}

void INPUT_INFOR_STUDENT(HOCVIEN &x)
{
    rewind(stdin);
    cout << "Nhap ma so Hoc Vien (MSHV): ";
    cin.getline(x.MSHV, sizeof(x.MSHV));
    cout << "Nhap ten Hoc Vien (HTHV): ";
    cin.getline(x.HTHV, sizeof(x.HTHV));
    cout << "Nhap ma mon hoc 1 (MMH1): ";
    cin.getline(x.MMH1, sizeof(x.MMH1)); 
    cout << "Nhap diem mon hoc 1 (DM1): ";
    cin >> x.DM1;
    cin.ignore(32767, '\n');
    cout << "Nhap ma mon hoc 2 (MMH2): ";
    cin.getline(x.MMH2, sizeof(x.MMH2));
    cout << "Nhap diem mon hoc 2 (DM2): ";
    cin >> x.DM2;
    cin.ignore(32767, '\n');
}

void WRITE_FILE(BST* &T, string filename)
{
    ofstream filein;
    filein.open(filename.c_str(), ios::app);
    if (filein.fail())
    {
        cout << "Error !!" << endl;
        checkFileName = false;
    }
    else
    {
        int s;
        cout << "Nhap so hoc vien muon them thong tin: ";
        cin >> s;
        filein << "Du lieu moi duoc them: " << endl;
        for (int i = 1; i <= s; i++)
        {
        	cout << "Thong tin hoc vien thu "<< i << endl;
        	HOCVIEN x;
       		INPUT_INFOR_STUDENT(x);
       		filein << x.MSHV <<", "<< x.HTHV <<", "<< x.MMH1 <<", "<< x.DM1 <<", "<< x.MMH2 <<", " << x.DM2 << endl;
		}
		checkFileName = true;
    }
    filein.close();
}


void FIND_STUDENT_BY_ID(BST* T, string key, BST* &p)
{
    if (T != &NULL_T)
    {
        if (_stricmp(T->data.MSHV,(char *)key.c_str()) == 0)
        {
            p = T;
            return;
        }
        FIND_STUDENT_BY_ID(T->left, key, p);
        FIND_STUDENT_BY_ID(T->right, key, p);
    }
}

void PRINT_FIRST_FORM()
{
    cout << setw(7) << left << "MSHV" << setw(20) << left << "Ho Va Ten" << setw(7) << left << "MaMH1" << setw(12) << left << "DiemMH1" << setw(7) << left << "MaMH2" << setw(7) << left << "DiemMH2" << endl;
    cout << setfill('-');
    cout << setw(60) << "-" << endl;
    cout << setfill(' ');
}

void RB_DELETE_FIXUP(BST**T, BST* x)
{
    BST* w;
    while ((x  != *T) && (x->color == cBLACK))
    {
        if (x == (x->parent)->left)
        {
            w = (x->parent)->right;
            if (w->color == cRED)
            {
                w->color = cBLACK;
                (x->parent)->color = cRED; 
                LEFT_ROTATE(*T, x->parent); 
                w = (x->parent)->right;
            }
            if (((w->left)->color == cBLACK) && ((w->right)->color == cBLACK))
            {
                w->color = cRED;
                x = x->parent;
            }
            else
            {
                if ((w->right)->color == cBLACK)
                {
                    (w->left)->color = cBLACK;
                    w->color = cRED;
                    RIGHT_ROTATE(*T, w);
                    w = (x->parent)->right;
                }
                w->color = (x->parent)->color;
                (x->parent)->color = cBLACK;
                (w->right)->color = cBLACK; 
                LEFT_ROTATE(*T, x->parent);
                x = *T;
            }
        }
        else
        {
            w = (x->parent)->left;
            if (w->color == cRED)
            {
                w->color = cBLACK;
                (x->parent)->color = cRED;
                RIGHT_ROTATE(*T, x->parent); 
                w = (x->parent)->left;
            }
            if (((w->right)->color == cBLACK) && ((w->left)->color == cBLACK))
            {
                w->color = cRED;
                x = x->parent;
            }
            else
            {
                if ((w->left)->color == cBLACK)
                {
                    (w->right)->color = cBLACK;
                    w->color = cRED;
                    LEFT_ROTATE(*T, w);
                    w = (x->parent)->left;
                }
                w->color = (x->parent)->color;
                (x->parent)->color = cBLACK;
                (w->left)->color = cBLACK;
                RIGHT_ROTATE(*T, x->parent);
                x = *T;
            }
        }
    }
    x->color = cBLACK;
} 

BST *TREE_MINIMUM(BST *x)
{
	while (x->left != NULL) x = x->left;
	return x;
}

BST *TREE_MAXIMUM(BST *x)
{
	while (x->right != NULL) x = x->right;
	return x;
}
BST *TREE_SUCCESSOR(BST *x)
{ 
	BST *y;
	if (x->right != NULL) 
	return 
		TREE_MINIMUM(x->right);
	y = x->parent;
	while ((y != NULL) && (x == y->right))
	{
		x = y; 
		y = y->parent;
	}
	return y;
}

BST *RB_TREE_DELETE(BST **T, BST *z)
{ 
	BST *x, *y;	
	if ((z->left== &NULL_T) || (z->right == &NULL_T))
		y = z;
	else 
		y = TREE_SUCCESSOR(z);
	if (y->left != &NULL_T) 	
		x = y->left ;
	else 
		x = y->right ;
	x->parent = y->parent;
	if (y->parent == &NULL_T) 
		*T = x;
	else 
		if (y == (y->parent)->left) 
			(y->parent)->left = x;
		else 
			(y->parent)->right = x;
	if (y != z) 
		{z->data = y->data;}
	if (y->color== cBLACK) 
		RB_DELETE_FIXUP(T, x);
	return y;
}

void DELETE_STUDENT_BY_ID(BST* T, string key, BST* &p)
{
    if (T != &NULL_T)
    {
        if (_stricmp(T->data.MSHV,(char *)key.c_str()) == 0)
        {
            p = T;
            return;
        }
        DELETE_STUDENT_BY_ID(T->left, key, p);
        DELETE_STUDENT_BY_ID(T->right, key, p);
    }
}
void FIND_ROOT(BST* T, BST *&x)
{
	if (T != &NULL_T) 
	{
		if(T->parent == &NULL_T  )
		{
		x = T;
		return;
		}
	}	
}

void In_Theo_RB_TREE(BST *x)
{
	if (x != &NULL_T) 
	{
		if (x->left != &NULL_T) 
		{
			cout << x->left->data.MSHV << ": " << x->left->data.HTHV  << ", " << "Nut con Trai cua "
			<< x->data.MSHV << ": " << x->data.HTHV <<endl;	
			if(x->color == 0)
				cout << "Mau cua " <<x->data.HTHV<<" : DO " << endl;
			else
				cout << "Mau cua " <<x->data.HTHV<<" : DEN "<< endl;
		}

		if(x->right != &NULL_T)
		{
			cout << x->right->data.MSHV << ": " << x->right->data.HTHV  << ", " << "Nut con Phai cua "
			<< x->data.MSHV << ": " << x->data.HTHV <<endl;	
			if(x->color == 0)
				cout << "Mau cua " <<x->data.HTHV<<" : DO " << endl;
			else
				cout << "Mau cua " <<x->data.HTHV<<" : DEN "<< endl;
		}
		In_Theo_RB_TREE(x->left);
		In_Theo_RB_TREE(x->right);
	}
}

HOCVIEN INSERT_TO_ARRAY(BST *x)
{
	HOCVIEN a;
	a.DM1 = x->data.DM1;
	a.DM2 = x->data.DM2;
	strcpy(a.HTHV,x->data.HTHV);
	strcpy(a.MMH1,x->data.MMH1);
	strcpy(a.MMH2,x->data.MMH2);
	strcpy(a.MSHV,x->data.MSHV);
	return a;
}

void COPPY_DATA_TO_ARRAY(BST *x, HOCVIEN A[])
{
	
    if (x != &NULL_T)
    {
        COPPY_DATA_TO_ARRAY(x->left,A);
        A[temp++] = INSERT_TO_ARRAY(x); 
        COPPY_DATA_TO_ARRAY(x->right,A);
    }
}

void SORT_BY_ASC_DM1(BST*T, HOCVIEN A[])
{	
	HOCVIEN tmp;
	for(int i=0; i < n-1; i++){
        for(int j = n-1;j>i;j--){
            if( A[i].DM1 > A[j].DM1)
			{
                tmp = A[i];
                A[i] = A[j];
                A[j] = tmp;
            }
        }
    }
}

void PRINT_FIRST_FORM_DM1()
{
    cout << setw(7) << left << "MSHV" << setw(20) << left << "Ho Va Ten" << setw(12) << left << "DiemMH1" << endl;
    cout << setfill('-');
    cout << setw(40) << "-" << endl;
    cout << setfill(' ');
}

void SORT_BY_ASC_DM2(BST*T, HOCVIEN B[])
{	
	HOCVIEN tmp;
	for(int i=0; i < n-1; i++){
        for(int j = n-1;j>i;j--){
            if( B[i].DM2 > B[j].DM2)
			{
                tmp = B[i];
                B[i] = B[j];
                B[j] = tmp;
            }
        }
    }
}

void PRINT_INF_DM1(HOCVIEN a)
{
    cout << setw(7) << left << a.MSHV << setw(20) 
	<< left << a.HTHV << setw(12) 
	<< left << a.DM1 << endl;
}

void PRINT_FIRST_FORM_DM2()
{
    cout << setw(7) << left << "MSHV" << setw(20) << left << "Ho Va Ten" << setw(12) << left << "DiemMH2" << endl;
    cout << setfill('-');
    cout << setw(40) << "-" << endl;
    cout << setfill(' ');
}

void PRINT_INF_DM2(HOCVIEN a)
{
    cout << setw(7) << left << a.MSHV << setw(20) 
	<< left << a.HTHV << setw(12) 
	<< left << a.DM2 << endl;
}

void SORT_BY_ASC_DM(BST*T, HOCVIEN A[])
{	
	HOCVIEN tmp;
	for(int i=0; i < n-1; i++){
        for(int j = n-1;j>i;j--){
            if( A[i].DM1 > A[j].DM1)
			{
               tmp = A[i];
                A[i] = A[j];
                A[j] = tmp;
            }
            if ( A[i].DM1 == A[j].DM1 ) 
            {
            	if( A[i].DM2 > A[j].DM2)
				{
	               tmp = A[i];
	                A[i] = A[j];
	                A[j] = tmp;
	            }
			}
        }
    }
}

void menu(BST* T)
{
    int option;
    while (true)
    {
        system("cls");
        cout << "*-------------------- MENU ---------------------*" << endl;
        cout << "| 1. Doc File Hoc Vien                          |" << endl;
        cout << "| 2. Them Mot Hoc Vien                          |" << endl;
        cout << "| 3. Xuat Danh Sach Hoc Vien                    |" << endl;
        cout << "| 4. Tim Hoc Vien Theo Ma Hoc Vien              |" << endl;
        cout << "| 5. Xoa Hoc Vien Theo Ma Hoc Vien              |" << endl;
        cout << "| 6. In Thong Tin Dang Cay Luu Tru              |" << endl;
        cout << "| 7. Sap xep thu tu tang dan theo diem mon hoc  |" << endl;
        cout << "| 8. Sap xep thu tu tang dan theo diem mon hoc 1|" << endl;
        cout << "|      neu diem mon hoc 1 bang nhau             |" << endl;
		cout << "|      -> sap tang dan theo mon hoc 2           |" << endl;
		cout << "| 9. Ghi thong tin vao file                     |" << endl;																
        cout << "| 0. Thoat                                      |" << endl;
        cout << "*-----------------------------------------------*" << endl;
        cout << "Nhap lua chon cua ban: ";
        cin >> option;
        if (option < 0 || option > 9)
        {
            cout << "Vui long nhap lai!!";
            system("pause");
        }
        else if (option == 1)
        {
            string filename;
            do 
            {
                cout << "Vui long nhap ten file: ";
                cin >> filename;
                READ_FILE(T, filename);
                if (checkFileName == false)
                {
                    cout << "Vui long nhap lai ten file!" << endl;
                }
                else
                {
                    cout << "File " << filename << " da duoc doc" << endl;
                }
            } while (checkFileName == false);
            system("pause");
        }
        else if (option == 2)
        {
            HOCVIEN x;
            cout << "Vui long nhap thong tin hoc vien " << endl;
            INPUT_INFOR_STUDENT(x);
            RB_TREE_INSERT(T, x);
            system("pause");
        }
        else if (option == 3)
        {
            PRINT_FIRST_FORM();
            PREORDER_TREE_WALK(T);
            system("pause");

        }
        else if (option == 4)
        {
            rewind(stdin);
            string key;
            cout << "Nhap ma so Hoc Vien (MSHV): ";
            getline(cin, key);
            BST* p = &NULL_T;
            FIND_STUDENT_BY_ID(T, key, p);
            if (p != &NULL_T)
            {
                PRINT_FIRST_FORM();
                PRINT_INF(p);
            }
            else
                cout << "Khong co Hoc Vien co Ma so la: " << key << endl;
            system("pause");            
            
        }
        else if (option == 5)
        {
        	BST* root = &NULL_T;
            FIND_ROOT(T,root);
            rewind(stdin);
            string key;
            cout << "Nhap ma so Hoc Vien can Xoa (MSHV): ";
            getline(cin, key);
            BST* p = &NULL_T;
            BST* temp = &NULL_T;
            DELETE_STUDENT_BY_ID(T, key, p);
          	if(p == root)
            {
            	temp->data = p->data;
            	p->data = p->right->data;
            	p->right->data = temp->data;
            	RB_TREE_DELETE(&T,p->right);
            	cout << "Sinh vien ma so " << key << " da duoc xoa khoi danh sach!"<< endl;
			}
			else
	            if (p != &NULL_T)
	            {
	                RB_TREE_DELETE(&T,p);
	                cout << "Sinh vien ma so " << key << " da duoc xoa khoi danh sach!" <<endl;
	            }
	            else
	                cout << "Khong co Hoc Vien co Ma so la: " << key << endl;
	            system("pause");
        }
        else if (option == 6)
        {
        	BST* root = &NULL_T;
    		FIND_ROOT(T,root);
    		cout << root->data.MSHV << ": " << root->data.HTHV << ", Root" << endl;
    		if(root->color == 0)
				cout << "Mau cua " <<root->data.HTHV<<" : DO " << endl;
			else
				cout << "Mau cua " <<root->data.HTHV<<" : DEN "<< endl;
            In_Theo_RB_TREE(T);           
            system("pause");
        }
        else if (option == 7)
        {
        	rewind(stdin);
        	string td;
        	cout << "Nhap diem mon hoc muon sap xep: ";
            getline(cin, td);
            if (_stricmp("DM1",(char *)td.c_str()) == 0)
            {
	        	HOCVIEN A[100];
	        	COPPY_DATA_TO_ARRAY(T,A);
				SORT_BY_ASC_DM1(T,A);
				PRINT_FIRST_FORM_DM1();
				for(int i=0; i<n ;i++)
					PRINT_INF_DM1(A[i]);
	        	system("pause");
	        }
	        else if (_stricmp("DM2",(char *)td.c_str()) == 0)
            {
	        	HOCVIEN B[100];
	        	COPPY_DATA_TO_ARRAY(T,B);
				SORT_BY_ASC_DM2(T,B);
				PRINT_FIRST_FORM_DM2();
				for(int i=0; i<n ;i++)
					PRINT_INF_DM2(B[i]);
	        	system("pause");
	        }
			else
			{
				cout << "Khong co diem cua mon hoc tren!" << endl;
				system("pause");
			}
		}
		else if (option == 8)
        {
       		cout << "n = " << n << endl;
        	HOCVIEN A[100];
        	COPPY_DATA_TO_ARRAY(T,A);
			SORT_BY_ASC_DM(T,A);
			PRINT_FIRST_FORM_DM1();
			for(int i=0; i<n ;i++)
				PRINT_INF_DM1(A[i]);
        	system("pause");
	    }
	    else if (option == 9)
        {
            string filename;
            cout << "Vui long nhap ten file: ";
            cin >> filename;
            WRITE_FILE(T, filename);
            cout << "Thong tin da duoc ghi vao file " << filename << endl;
            system("pause");
        }
        else
            break;
    }
}


int main()
{
    BST* T;
    RB_INIT_BST(T);
    menu(T);
    system("pause");
    return 0;
}
