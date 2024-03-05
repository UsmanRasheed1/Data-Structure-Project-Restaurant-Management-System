#include <iostream>
#include <fstream>
#include <ctime>
#include <windows.h>

using namespace std;
void textcolor();
struct node{
	string foodname;
	int price;
	int quantity;
};
class Queue{
	node arr[100];
	int n,top;
	public:
	Queue(){
	n=100;
	top=-1;
	}
	void push(node input){
		top++;
		arr[top]=input;
	}
	node pop(){
		node output=arr[0];
		for(int i=0;i<top;i++){
			arr[i]=arr[i+1];
		}
		top--;
		return output;
	}
	int check(){
		if(top!=-1){
			return 1;
		}
		else return 0;
	}
};
class fooditems{
	public:
		string foodname;
		int price;
		int amountearned;
		fooditems*right;
		fooditems*left;
		fooditems(string foodname,int price){
			this->foodname=foodname;
			this->price=price;
			this->right=NULL;
			this->left=NULL;
			amountearned=0;
		}
};

class BST{
	public:
	fooditems*create(string foodname,int price){
    fooditems*newnode=new fooditems(foodname,price);
  return newnode;
}
fooditems* insert(fooditems*root,string foodname,int price){
	if(root==NULL){
		return create(foodname,price);
	}
//	strcmp(data,root->data);
	if(foodname<root->foodname){
		root->left=insert(root->left,foodname,price);
	}
	else if(foodname>root->foodname){
		root->right=insert(root->right,foodname,price);
	}
	return root;
	}
	fooditems* Deleteitem(fooditems* root, string foodname){
        if(root == NULL)
            return NULL;
            
        else if(foodname < root->foodname)
            root->left = Deleteitem(root->left, foodname);
            
        else if(foodname > root->foodname)
            root->right = Deleteitem(root->right, foodname);
            
        else{
            if(root->left == NULL){
                fooditems* temp = root->right;
                delete root;
                return temp;
            }
            
            else if(root->right == NULL){
                fooditems* temp = root->left;
                delete root;
                return temp;
            }
            
            else{
                fooditems* temp = minvaluenode(root->right);
                root->foodname = temp->foodname;
                root->right = Deleteitem(root->right, temp->foodname);
            }
        }
        return root;
    }
    fooditems* minvaluenode(fooditems* NODE){
        fooditems* current = NODE;
        
        while(current -> left != NULL)
            current = current->left;
            
        return current;
    }
	void Displaymenu(fooditems*root){
		if(root==NULL){
			return;
		}
		Displaymenu(root->left);
		cout<<"* "<<root->foodname<<" "<<root->price<<endl;
		
		Displaymenu(root->right);
		
	}
	void Inorderfiling(fooditems*root){
		if(root==NULL){
			return;
		}
		Inorderfiling(root->left);
		fstream f("Fooditem-details.txt",ios::app);
		f<<"* "<<root->foodname<<":\nPrice: "<<root->price<<"\nAmount Earned: "<<root->amountearned<<endl<<endl;

		Inorderfiling(root->right);
	}
	void Displayamountearned(fooditems*root){
		if(root==NULL){
			return;
		}
		Displayamountearned(root->left);
		cout<<"* "<<root->foodname<<" "<<root->amountearned<<endl;
		
		Displayamountearned(root->right);
		
	}
	fooditems* SearchBST(fooditems* root, string foodname){
        if(root == NULL)
            return NULL;
        
        else if(foodname == root->foodname)
            return root;
        
        else if(foodname < root->foodname)
            return SearchBST(root->left, foodname);
        
        else if(foodname > root->foodname)
            return SearchBST(root->right, foodname);
    }	
    
    
	int orderfood(fooditems* root){
		Queue q;
		node ob;
		int o;
		string name[5]={"John","Fatima","Usman","Asuka","Akai"};
    	srand(time(0));
    	int randint=rand()%5;
		int quantity;
		string n;
		int totalsum=0;
		do{
		cout<<"Displaying Menu: \n";
		Displaymenu(root);
		cout<<"Enter the desired food item you would like to order"<<endl;
		cin>>n;
		fooditems*temp=SearchBST(root,n);
		if(temp==NULL){
			cout<<"Sorry, This item doesn't exist.\n";
		}
		else{
		
		ob.foodname=n;
		ob.price=temp->price;
		cout<<"Enter the desired quantity"<<endl;
		cin>>quantity;
		ob.quantity=quantity;
		temp->amountearned+=temp->price*quantity;
		cout<<"That would be "<<temp->price*quantity<<endl;
			q.push(ob);
	}
			cout<<"Do you want to order another item(1 for yes/0 for no)?"<<endl;
			cin>>o;  
		}while(o!=0);
		ifstream num("ReceiptNumber.txt");
		int i;
		num>>i;
		fstream f("Receipt.txt",ios::app);
		cout<<"----------------------      Displaying your Receipt: ------------------\n";
		f<<"----------------------      Displaying Receipt#"<<i<<": ------------------\n";
		while(q.check()!=0){
		ob=q.pop();
		cout<<ob.foodname<<"x"<<ob.quantity<<"     "<<ob.price*ob.quantity<<endl;
		f<<ob.foodname<<"x"<<ob.quantity<<"     "<<ob.price*ob.quantity<<endl;
		totalsum+=ob.price*ob.quantity;
		
	}
	cout<<"Total Bill: "<<totalsum<<"\nYour food will be delivered to your address in 30 minutes by our driver "<<name[randint]<<" in 30 minutes!\n";
	f<<"Total Bill: "<<totalsum<<"\nThe food was delivered by "<<name[randint]<<"\n";
	ofstream inp("ReceiptNumber.txt");
		i++;
		inp<<i;
	return totalsum;
}

};

struct Customerstruct{
	string username, password, email;
    string address;
	int customersum;
};
class Customer{
	string username, password, email;
    string address;
	int customersum;
	public:
    Customer* next=NULL;
    Customer* prev=NULL;
	
		
	Customer(){
		next=NULL;
		prev=NULL;
		username="";
		password="";
		email="";
		address="";
		customersum=0;
	}
	Customer(string inpn,string inpp,string inpe,string inpa){
		username=inpn;
		password=inpp;
		email=inpe;
		address=inpa;
		customersum=0;
		next=NULL;
		prev=NULL;
		
		//cout<<"check";
	}
	Customer(string inpn,string inpp,string inpe,string inpa,int cs){
		username=inpn;
		password=inpp;
		email=inpe;
		address=inpa;
		customersum=cs;
		next=NULL;
		prev=NULL;
		
		//cout<<"check";
	}
	
	int checkusername(string inpname){
		if(username==inpname){
			return 1;
		}
		else return 0;
	}
	int checkpassword(string inppassword){
		if(password==inppassword){
			return 1;
		}
		else return 0;
	}
	void inputname(string input){
		username=input;
	}
	void inputpassword(string input){
		password=input;
	}
	void inputemail(string input){
		email=input;
	}
	void inputaddress(string input){
		address=input;
	}
	void incrementsum(int input){
		customersum+=input;
	}
	string getname(){
		return username;
	}
	string getpassword(){
		return password;
	}
	string getemail(){
		return email;
	}
	string getaddress(){
		return address;
	}
	int getcustomersum(){
		return customersum;
	}
	

};

class CustomerList:public Customer,public BST{
	Customer* head=NULL;
	Customer* tail=NULL;
	fooditems* root=NULL;
	int companysum;
	public:
	CustomerList(){
		companysum=0;
		insert("Usman","Usman932","k213225@nu.edu.pk","-",999);
	    insert("Fatima","Fati12389","k213455@nu.edu.pk","DE",700);
	    insert("Test-ID-A","Test12","TestA@.edu.pk","-",1200);
	    insert("Test-ID-B","Test34","TestB@.edu.pk","-",400);
	    insert("Test-ID-C","Test56","TestC@nu.edu.pk","-",9999);
	    insert("Test-ID-D","Test78","TestD@nu.edu.pk","-",100);
    root=BST::insert(root,"Biryani",150);
	root=BST::insert(root,"Burger",200);
	root=BST::insert(root,"Chow-mein",500);
	root=BST::insert(root,"Noodle-Soup",290);
	root=BST::insert(root,"Fried-Rice",650);
	root=BST::insert(root,"Wonton",675);
	root=BST::insert(root,"Manchurian",700);
	root=BST::insert(root,"Chilli-Chicken",999);
	root=BST::insert(root,"Spaghetti",895);
	root=BST::insert(root,"Dumplings",750);
	root=BST::insert(root,"Nihari",600);
	root=BST::insert(root,"Chicken-Karahi",890);
	root=BST::insert(root,"Haleem",250);
	root=BST::insert(root,"Cheese-Burger",250);
	root=BST::insert(root,"Drink-Small",60);
    root=BST::insert(root,"Drink-Large",200);
    root=BST::insert(root,"Icecream",150);
    root=BST::insert(root,"Chocolate-Cake",500);
	}	
	string setname(){
		bool check=1;
		string name;
		Customer* temp=head;
		while(check==1){
	    cout<<"Enter your username: "; cin>>name;
	    if(temp==NULL){
	    	break;
		}
	    while(temp!=NULL){
	    	if(temp->checkusername(name)==0){
	    		check=0;
			}
			else{
				cout<<"Username is repeating, please enter again\n";
				check=1;
				temp=head;
				break;
			}
			temp=temp->next;	
		}
		
        }
        return name;
	}
	string setpassword(){
		int i=0,j=0,k=0,l=0;
		string password;
		Customer* temp=head;
		do{
		cout<<"Enter the password, the password must have one Upper case letter and atleast one number: ";
		cin>>password;
		k=0,l=0;
		i = password.length();
		for(j=0;j<i;j++){

		if(password[j]>=65 && password[j]<=90){
		k++;}
		if(password[j]>=48 && password[j]<=57){
		l++;}
		}
	    }while(k==0 || l==0);
	    return password;
	
	}
	string setemail(){
		string email;
		cout<<"Enter the email: ";
		cin>>email;
		return email;
	}
	string setaddress(){
		string address;
		cout<<"Enter your home address: ";
		cin>>address;
		return address;
	}
	void signup(){
		string name,password,email,address;
		int option;
		Customer* temp=head;
		bool check=1;
		cout<<"Welcome to the Sign Up system\n";
		while(option!=2){
		 textcolor(); 
		name=setname();
		password=setpassword();
		email=setemail();
		address=setaddress();
		insert(name,password,email,address);
		cout<<"\nWould you like to sign up again for a new user? Press the number for the following:\n1.Yes\n2.No\n";
		cin>>option;
		if(option==2){
			cout<<"\nGoing back to previous Menu Screen \n";
			Sleep(700);
		}
		}
	}
	
	Customer* loginsearch(){
		string name,password;
		int i=0;
		int k=0;
		cout<<"Enter the Username of the account you want to login for: \n";
		cout<<"Username: "; cin>>name;
		Customer* temp=head;
		while(temp!=NULL){
			if(temp->checkusername(name)==1){
				break;
			}
			temp=temp->next;
		}
		
		if(temp==NULL){
		cout<<"Username doesn't exist\nLOGIN PHASE TERMINATED\n";
		return NULL;
		}
		while(i!=3){
		cout<<"Enter the password for this account\n";
		cin>>password;
		if(temp->checkpassword(password)==0){
			i++;
			if(i<3){
			cout<<"Incorrect password entered "<<i<<" times, login will be terminated at 3 incorrect attempts\n";
			}
			else{
				cout<<"Incorrect password entered "<<i<<" times\nLOGIN TERMINATED\n";
			}
		}
		else{
			break;
		}
		}
		if(i<3){
			return temp;
		}
		else return NULL;
	}
	void login(){	
	if(head==NULL){
		cout<<"No Customers exist yet\n";
		cout<<"\nGoing back to previous Menu Screen \n";
			Sleep(700);
			return;
	}
	int i;
	int option;
	cout<<"Welcome to the Login Menu\n";
	Customer* temp;
	int sum;
	temp=loginsearch();
	if(temp==NULL){
		return;
	}
	while(option!=7){
		 textcolor(); 
	cout<<"\nWelcome User what would you like to do?\n1.Order Food\n2.Change Username\n3.Change Password\n4.Change Email\n5.Change Address\n6.View User Details\n7.Exit\n";
	cin>>option;
	if(option==1){
		sum=orderfood(root);
		fstream f("Receipt.txt",ios::app);
		cout<<"Your Username: "<<temp->getname()<<endl;
		cout<<"Your Address: "<<temp->getaddress()<<endl;
		cout<<"------------------------------------ Have a Good Meal! ---------------------------------\n";
		f<<"Customer Username: "<<temp->getname()<<endl;
		f<<"Customer Address: "<<temp->getaddress()<<endl;
		f<<"--------------------------------------------------------------------------------------------\n";
		
		companysum+=sum;
		temp->incrementsum(sum);
	}
	else if(option==2){
		temp->inputname(setname());
	}
	else if(option==3){
		temp->inputpassword(setpassword());
	}
	else if(option==4){
		temp->inputemail(setemail());
	}
	else if(option==5){
		temp->inputaddress(setaddress());
	}
	else if(option==6){
		cout<<"\nDisplaying User Details\n";
		cout<<"Name: "<<temp->getname()<<endl;
			cout<<"Password: "<<temp->getpassword()<<endl;
			cout<<"Email: "<<temp->getemail()<<endl;
			cout<<"Address: "<<temp->getaddress()<<endl;
			cout<<"Customersum: "<<temp->getcustomersum()<<endl;
			cout<<endl;
			
		
	}
	else if(option==7){
	cout<<"\nExiting the Login Phase\n";
	Sleep(700);
	break;	
	}
	}
	}
	void managermenu(){
		string input;
		string username,customerpassword,email,address;
		int customersum;
		fooditems* temp;
		int sum;
		string password="Manager123";
		int i=0;
		int j=0;
			while(i!=3){
		cout<<"Enter the Manager Password to proceed\n";
		cin>>input;
		if(input!=password){
			i++;
			if(i<3){
			cout<<"Incorrect password entered "<<i<<" times, The Manager Menu will be terminated at 3 incorrect attempts\n";
			}
			else{
				cout<<"Incorrect password entered "<<i<<" times\nMENU PHASE TERMINATED\n";
			}
		}
		else{
			break;
		}
	}
		if(i==3){
			return;
		}
		while(j!=15){
			 textcolor(); 
			cout<<"Welcome Manager, What would you like to do!\n1.Push a new user at the top/head\n2.Insert a new user at the end/tail\n3.View the Company Sum.\n4.View Customers from the head\n5.View Customers from the tail\n6.View customers by their names in Ascending order\n7.View Customers by their earnings in Ascending order\n8.Pop Customer (Delete head)\n9.Delete Customer at end (Delete the tail)\n10.Delete a Customer using their name\n11.View the food menu\n12.Delete a food item.\n13.Insert a food item.\n14.View the food earnings\n15.Exit";
		cout<<endl;
		cin>>j;
		Sleep(700);
		switch (j){
		
		case 1:
			username=setname();
			customerpassword=setpassword();
			email=setemail();
			address=setaddress();
			cout<<"Enter the Customer sum: "; cin>>customersum;	
			
			push(username,customerpassword,email,address,customersum);
			cout<<"\nCustomer pushed succesfully!\n";
			break;
		case 2:
			username=setname();
			customerpassword=setpassword();
			email=setemail();
			address=setaddress();
			cout<<"Enter the Customer sum: "; cin>>customersum;	
			insert(username,customerpassword,email,address,customersum);
			cout<<"\nCustomer inserted succesfully!\n";
			break;
		case 3:
			cout<<"\nThe Customer sum is: "<<getcompanysum()<<endl;
			break;
		case 4:
			displayfromhead();
			break;
		case 5:
			displayfromtail();
			break;
		case 6:
			displayascendingname();
			break;
		case 7:
			displayascendingsum();
			break;
		case 8:
			pop();
			cout<<"\nCustomer popped succesfully!\n";
			break;
		case 9:
			deletetail();
			cout<<"\nCustomer deleted from tail succesfully!\n";
			break;
		case 10:
			cout<<"Enter the name: "; cin>>username;
			deletename(username);
			cout<<"\nCustomer deleted succesfully!\n";
		case 11:
			cout<<"Displaying Menu: \n";
			Displaymenu(root);
			cout<<endl;
			break;
		case 12:
			cout<<"Enter the food name you would like to Delete ";
			Displaymenu(root);
			cin>>input;
			temp=SearchBST(root,input);
			if(temp==NULL){
				cout<<"The searched Node does not exist.\n";
			}
			else{
			root=Deleteitem(root,input);	
				cout<<"\nFood item deleted succesfully!\n";
			}
			break;
		case 13:
			cout<<"Enter the food name: "; cin>>input;
			cout<<"Enter the food's price: "; cin>>sum;
			
			root=BST::insert(root,input,sum);
			cout<<"\nFood item inserted succesfully!\n";
			break;
		case 14:
			cout<<"Displaying Amount Earned: \n";
			Displayamountearned(root);
			cout<<endl;
			break;
		case 15:
		break;
		}
			
		}
		
	}
	void push(string name,string password,string email,string address,int customersum){
		Customer* newnode=new Customer(name,password,email,address,customersum);
		if(head==NULL){
			head=newnode;
			tail=newnode;
			head->next=NULL;
			tail->prev=NULL;
		
		}
	else{
		newnode->next=head;
		head->prev=newnode;
		head=newnode;
		
	}
	}
	void pop(){
		Customer* temp=head;
		head=head->next;
		head->prev=NULL;
		delete temp;
	}
	void insert(string name,string password,string email,string address,int customersum){
		Customer* newnode=new Customer(name,password,email,address,customersum);
		if(head==NULL){
			head=newnode;
			tail=newnode;
			head->next=NULL;
			tail->prev=NULL;
		}
		else{
			tail->next=newnode;
			newnode->prev=tail;
			tail=newnode;
		}
	}
	void insert(string name,string password,string email,string address){
		Customer* newnode=new Customer(name,password,email,address);
		if(head==NULL){
			head=newnode;
			tail=newnode;
			head->next=NULL;
			tail->prev=NULL;
		}
		else{
			tail->next=newnode;
			newnode->prev=tail;
			tail=newnode;
		}
	}
	void deletetail(){
		Customer* temp=tail;
		tail=tail->prev;
		tail->next=NULL;
		delete temp;
	}
	void deletename(string name){
		Customer* temp=head;
		if(head->checkusername(name)==1){
			pop();
			return;
		}
		if(tail->checkusername(name)==1){
			deletetail();
			return;
		}
		while(temp->checkusername(name)!=1){
			temp=temp->next;
		}
		temp->prev->next=temp->next;
		temp->next->prev=temp->prev;
		delete temp;
		
	}
	void displayfromhead(){

		Customer* temp=head;
		int i=1;
		if(head==NULL){
			cout<<"No Data exists\n";
			return;
		}
		cout<<"Displaying Customer Details from Head: \n";
		while(temp!=NULL){
			cout<<"Customer "<<i<<endl;
			cout<<"Name: "<<temp->getname()<<endl;
			cout<<"Password: "<<temp->getpassword()<<endl;
			cout<<"Email: "<<temp->getemail()<<endl;
			cout<<"Address: "<<temp->getaddress()<<endl;
			cout<<"Customersum: "<<temp->getcustomersum()<<endl;
			cout<<endl;
			i++;
			temp=temp->next;
		}
	}
	void displayfromtail(){
		Customer* temp=tail;
		int i=1;
		if(tail==NULL){
			cout<<"No Data exists\n";
			return;
		}
		cout<<"Displaying Customer Details from Tail: \n";
		while(temp!=NULL){
			cout<<"Customer "<<i<<endl;
			cout<<"Name: "<<temp->getname()<<endl;
			cout<<"Password: "<<temp->getpassword()<<endl;
			cout<<"Email: "<<temp->getemail()<<endl;
			cout<<"Address: "<<temp->getaddress()<<endl;
			cout<<"Customersum: "<<temp->getcustomersum()<<endl;
			cout<<endl;
			i++;
			temp=temp->prev;
		}
	}
	int listsize(){
		Customer* temp=head;
		int i=0;
		while(temp!=NULL){
			i++;
			temp=temp->next;
		}
		return i;
	}
	void insertinstruct(Customerstruct* arr){
		int i=0;
		Customer* temp=head;
		while(temp!=NULL){
			arr[i].username=temp->getname();
			arr[i].email=temp->getemail();
			arr[i].password=temp->getpassword();
			arr[i].address=temp->getpassword();
			arr[i].customersum=temp->getcustomersum();
			temp=temp->next;
			i++;
		}
	}
	void displayascendingsum(){
		int i=listsize();
		Customerstruct temp;
		Customerstruct* arr=new Customerstruct[i];
		insertinstruct(arr);
		for(int j=0;j<i;j++){
			for(int k=0;k<i-1;k++){
				if(arr[k+1].customersum<arr[k].customersum){
					temp=arr[k+1];
					arr[k+1]=arr[k];
					arr[k]=temp;
				}
			}
		}
	cout<<"Displaying Customers according to Customer sum in ascending order: "<<endl;
	for(int j=0;j<i;j++){
		cout<<"Customer "<<j+1<<endl;
			cout<<"Name: "<<arr[j].username<<endl;
			cout<<"Password: "<<arr[j].password<<endl;
			cout<<"Email: "<<arr[j].email<<endl;
			cout<<"Address: "<<arr[j].address<<endl;
			cout<<"Customersum: "<<arr[j].customersum<<endl;
			cout<<endl;
	}
	}
	void displayascendingname(){
		int i=listsize();
		Customerstruct temp;
		Customerstruct* arr=new Customerstruct[i];
		insertinstruct(arr);
		for(int j=0;j<i;j++){
			for(int k=0;k<i-1;k++){
				if(arr[k+1].username<arr[k].username){
					temp=arr[k+1];
					arr[k+1]=arr[k];
					arr[k]=temp;
				}
			}
		}
	cout<<"Displaying Customers according to their Username in ascending order: "<<endl;
	for(int j=0;j<i;j++){
		cout<<"Customer "<<j+1<<endl;
			cout<<"Name: "<<arr[j].username<<endl;
			cout<<"Password: "<<arr[j].password<<endl;
			cout<<"Email: "<<arr[j].email<<endl;
			cout<<"Address: "<<arr[j].address<<endl;
			cout<<"Customersum: "<<arr[j].customersum<<endl;
			cout<<endl;
	}
	
	}
	int getcompanysum(){
		return companysum;
	}
	void filing(){
		fstream clear("Customerdetails.txt", std::ofstream::out | std::ofstream::trunc);
		fstream f("Customerdetails.txt",ios::app);
		Customer* temp=head;
		int i=1;
		if(head==NULL){
			f<<"No Data exists\n";
			return;
		}
		f<<"Displaying Customer Details from Head: \n";
		while(temp!=NULL){
			f<<"Customer "<<i<<endl;
			f<<"Name: "<<temp->getname()<<endl;
			f<<"Password: "<<temp->getpassword()<<endl;
			f<<"Email: "<<temp->getemail()<<endl;
			f<<"Address: "<<temp->getaddress()<<endl;
			f<<"Customersum: "<<temp->getcustomersum()<<endl;
			f<<endl;
			i++;
			temp=temp->next;
		}
		
		i=listsize();
		Customerstruct temp2;
		Customerstruct* arr=new Customerstruct[i];
		insertinstruct(arr);
		for(int j=0;j<i;j++){
			for(int k=0;k<i-1;k++){
				if(arr[k+1].customersum<arr[k].customersum){
					temp2=arr[k+1];
					arr[k+1]=arr[k];
					arr[k]=temp2;
				}
			}
		}
	f<<"Displaying Customers according to Customer sum in ascending order: "<<endl;
	for(int j=0;j<i;j++){
		f<<"Customer "<<j+1<<endl;
			f<<"Name: "<<arr[j].username<<endl;
			f<<"Password: "<<arr[j].password<<endl;
			f<<"Email: "<<arr[j].email<<endl;
			f<<"Address: "<<arr[j].address<<endl;
			f<<"Customersum: "<<arr[j].customersum<<endl;
			f<<endl;
	}
fstream clear2("Fooditem-details.txt", std::ofstream::out | std::ofstream::trunc);
Inorderfiling(root);
	}
	
	
};
void textcolor(){
int P=0;
	HANDLE console_color;
    console_color = GetStdHandle(
        STD_OUTPUT_HANDLE);
	srand(time(0));
	P=(rand()%15)+1;
         SetConsoleTextAttribute(console_color, P);		
}
void fileset(){
		fstream num("ReceiptNumber.txt");
		num<<1;
		fstream clear("Receipt.txt", std::ofstream::out | std::ofstream::trunc);
}



int main(){
	CustomerList ob;
	int i=0;
	fileset();
	while(i!=4){
    textcolor();    
    cout<<"Welcome to the Restaurant System Menu, what would you like to do: \n1.Go to the Manager Menu.\n2.Sign up.\n3.Login.\n4.Exit\n";
    cin>>i;
    Sleep(700);
    if(i==1){
    	ob.managermenu();
	}
	else if(i==2){
		ob.signup();
	}
	else if(i==3){
		ob.login();
	}
	else{
		cout<<"Exiting the program.\nGoodBye! C:";
	}
     }
     
    ob.filing();
}

