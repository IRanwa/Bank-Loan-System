#include <iostream>
#include <iomanip>
#define nicMax 100000 // NIC maximum number
#define nicMin 10000 // NIC minimum number

using namespace std;

//Data Structures and Pointers
struct customer {
	int NIC;
	char customerName[20];
	char customerAddress[50];
	int customerAge;
	char customerGender;
	char customerType;
	char loanType;
	double loanAmount;
	int loanDuration;
	struct customer *nextCustPtr;
};

typedef struct customer CustomerNode;
typedef CustomerNode *customerPtr;

struct loanQueue {
	int NIC;
	char loanType;
	double loanAmount;
	int loanDuration;
	struct loanQueue *nextLoanPtr;
};

typedef struct loanQueue LoanQueueNode;
typedef LoanQueueNode *loanQueuePtr;

//Function Prototypes
void displayMenu();
void registerCustomer();
void unregisterCustomer();
void updateCustomer();
void viewCustomer();
void viewAllCustomer();
void applyLoan();
void appRejLoan();
void viewAppCustomer();
void viewPendingCustomer();
void viewGeneralCustomer();

//Linear Array Search 
int linearArrSearch(int[],int);
//Linear Customer Search
customerPtr linearCustSearch(customerPtr, int);
//Sorting
void Sort(int[]);
//Command prompt clear command
void clearCMD();
//Customer Details display
void displayCustomerDetails(char);
//Getting Loan Amount from Queue
double loanAmount(loanQueuePtr , int);

//Link List
bool insertCustDetails(customerPtr *, int, char[20], char[50], int, char, char);
int deleteCustomerDetails(customerPtr *, int);
int isEmpty(customerPtr);

//Queue
bool enterLoanDetails(loanQueuePtr *, loanQueuePtr *, int, char, double , int );
void deleteLoanDetails(loanQueuePtr *,loanQueuePtr *);
int isEmpty(loanQueuePtr);

//Global Variables
loanQueuePtr headLoanPtr = NULL;
loanQueuePtr tailLoanPtr = NULL;
customerPtr cust = NULL;
const int NOOFCUST = 100; // No of customers
int custNIC[NOOFCUST];

int main(){
    int option = 0;

	for (int x = 0; x < NOOFCUST;x++) {
		::custNIC[x] = nicMax;
	}

	do{
		//Display Menu
		displayMenu();
		cout << "Select an Option : ";

		cin >> option;
		cout << endl;
	
		switch (option){
			case 1:
				//Register Customer
				cout << "Selected Option 1) Register Customer" << endl << endl;
				registerCustomer();
				break;
			case 2:
				//Unregister Customer
				cout << "Selected Option 2) Un-Register Customer" << endl << endl;
				unregisterCustomer();
				break;
			case 3:
				//Update Customer
				cout << "Selected Option 3) Update Customer" << endl << endl;
				updateCustomer();
				break;
			case 4:
				//View Customer
				cout << "Selected Option 4) View Customer" << endl << endl;
				viewCustomer();
				break;
			case 5:
				//View All Customers
				cout << "Selected Option 5) View All Customers" << endl << endl;
				viewAllCustomer();
				break;
			case 6:
				//Apply for a loan
				cout << "Selected Option 6) Apply for a Loan" << endl << endl;
				applyLoan();
				break;
			case 7:
				//Approve/Reject Loan
				cout << "Selected Option 7) Approve/Reject Loan" << endl << endl;
				appRejLoan();
				break;
			case 8:
				//View approved Customers
				cout << "Selected Option 8) View Approved Customers" << endl << endl;
				viewAppCustomer();
				break;
			case 9:
				//View Pending Customers
				cout << "Selected Option 9) View Pending Customers" << endl << endl;
				viewPendingCustomer();
				break;
			case 10:
				//View General Customers1
				cout << "Selected Option 10) View General Customers" << endl << endl;
				viewGeneralCustomer();
				break;
			default:
				cout << "Selected Option is Invalid!" << endl << endl;
		}
		cout << endl << endl;
		
	} while (option!=0);

	//getchar();
	return 0;
}

void displayMenu(){
	//Display Menu Options
	cout << "===================================================" << endl << endl;
	cout << setw(27) << "Bank Of Ceylon" << endl << endl;
	cout << setw(23) << "Welcome" << endl << endl;
	cout << setw(23) << "1) Register Customer" << endl;
	cout << setw(26) << "2) Un-Register Customer" << endl;
	cout << setw(21) << "3) Update Customer" << endl;
	cout << setw(19) << "4) View Customer" << endl;
	cout << setw(24) << "5) View All Customers" << endl;
	cout << setw(22) << "6) Apply for a Loan" << endl;
	cout << setw(25) << "7) Approve/Reject Loan" << endl;
	cout << setw(29) << "8) View Approved Customers" << endl;
	cout << setw(28) << "9) View Pending Customers" << endl;
	cout << setw(29) << "10) View General Customers" << endl;
	cout << setw(10) << "0) Exit" << endl << endl;
}

void registerCustomer(){
	int nic = 0; //Customer NIC
	char cName[20] = ""; // Customer Name
	char address[50] = ""; // Customer Address
	int age = 0; // Customer age
	char gender = NULL; //Customer gender
	char save = NULL;
	bool flag = true;
	int element = 0;

	cout << "Enter the NIC Number : ";
	cin >> nic;
	cin.ignore(); //This use to ignore the input stream charactSers manually

	if (nic<nicMin || nic>= nicMax){ //Checking NIC is a 5 digit number
		clearCMD();
		cout << "Entered NIC is Invalid!" << endl;
	}
	else{
		//Checking Customer already registered
		element = linearArrSearch(::custNIC, nic);
		if (element!=-1){
			clearCMD();
			cout << "Customer already Registered." << endl;
		}
		else{
			//Program request user to enter Customer Details
			cout << "Enter Customer Name : ";
			cin.get(cName, 20);
			cin.ignore();

			cout << "Enter Customer Address : ";
			cin.get(address, 40);

			cout << "Enter Customer Age : ";
			cin >> age;

			cout << "Enter Customer Gender (M :- Male / F :- Female): ";
			cin >> gender;
			
			//Checking Enter Gender Type Correct
			if((gender != 'M') && (gender != 'm') && (gender != 'f') && (gender != 'F')){
				clearCMD();
				cout << "Selected Gender is Invalid!" << endl;
				cout << "Registration Unsuccessful." << endl;
			}else{
					//Displaying entered customer details
					cout << endl;
					cout << "Customer Name : " << cName << endl;
					cout << "Customer Address : " << address << endl;
					cout << "Customer Age : " << age << endl;

					if ((gender == 'M') || (gender == 'm')) {
						cout << "Customer Gender : Male" << endl;
					}
					else {
						cout << "Customer Gender : Female" << endl;
					}

					do{
						//Requesting user to confirm entered Customer details correct
						cout << "Do you want to save these details (Y/N) : ";
						cin >> save;
						if ((save == 'Y') || (save == 'y')) {
							clearCMD();
							//Storing Customer Details in the System
							flag = insertCustDetails(&cust, nic, cName, address, age, gender, 'G');
							//Sorting customer NIC array
							Sort(::custNIC);
							if (flag) {
								cout << "Registered Successfully!" << endl;
							}
							else {
								cout << "Registration Unsuccessful." << endl;
							}
						}
						else if ((save == 'N') || (save == 'n')) {
							//User Decline to save the Customer Details
							clearCMD();
							cout << "Registration Unsuccessful." << endl;
						}
						else {
							cout << "Invalid Entry!" << endl;
						}
						//Until User Enter Y/N character it will go through a loop
					} while ((save != 'N') && (save != 'n') && (save != 'Y') && (save != 'y')); 
			}
		}
	}
}

void unregisterCustomer(){
	int nic = 0; // customer nic
	int status = 0;

	cout << "Enter the NIC Number : ";
	cin >> nic;
	if (nic<nicMin || nic >= nicMax){ //Checking NIC is a 5 digit number
		clearCMD();
		cout << "Entered NIC is Invalid!" << endl;
	}
	else{
		//Checking customer already registered
		status = linearArrSearch(::custNIC, nic);
		if (status!=-1) {
			//Finding customer details and remove
			status = deleteCustomerDetails(&cust, nic);
			if (status == 0) {
				cout << "Customer Un-Registered successfully!" << endl;
				Sort(::custNIC);
			}
			else if(status == 1) {
				cout << "This Customer has obtained a Loan!\nCustomer Un-Registration Unsuccessful." << endl;
			}
			else {
				cout << "This Customer has requested a Loan!\nCustomer Un-Registration Unsuccessful." << endl;
			}
		}
		else {
			cout << "This Customer is Not Registered!" << endl;
		}
	}
}

void updateCustomer(){
	int nic = 0 ; // customer nic
	char address[40] = "";
	int element = 0;
	customerPtr currentPtr = NULL;

	cout << "Enter the NIC Number : ";
	cin >> nic;
	cin.ignore();

	if (nic<nicMin || nic >= nicMax){ //Checking NIC is a 5 digit number
		clearCMD();
		cout << "Entered NIC is Invalid!" << endl;
	}
	else{
		//Checking customer registered
		element = linearArrSearch(::custNIC, nic);
		clearCMD();
		if (element != -1){
			//Request to enter new customer address
			cout << "Enter New Address : ";
			cin.get(address, 40);

			currentPtr = linearCustSearch(cust, nic);

			//Updating Customer Address
			strcpy_s(currentPtr->customerAddress, address);
			cout << "Customer Details Updated Sucessfully!" << endl;
		}
		else{
			cout << "This Customer is Not Registered!" << endl;
		}
	}
}

void viewCustomer(){
	int nic = 0; // customer nic
	char gender = NULL;
	char type = NULL;
	char lType = NULL;
	int element = 0;
	customerPtr currentPtr = NULL;
	
	cout << "Enter the NIC Number : ";
	cin >> nic;
	
	if (nic<nicMin || nic >= nicMax){ //Checking NIC is a 5 digit number
		clearCMD();
		cout << "Entered NIC is Invalid!" << endl;
	}
	else{
		//Checking customer registered
		element = linearArrSearch(::custNIC, nic);
		clearCMD();
		if (element != -1){
			currentPtr = linearCustSearch(cust, nic);
			//Display customer Details
			cout << endl;
			cout << "Customer Name : " << currentPtr->customerName << endl;
			cout << "Customer Address : " << currentPtr->customerAddress << endl;
			cout << "Customer Age : " << currentPtr->customerAge << endl;
			
			gender = currentPtr->customerGender;
			if ((gender=='M') || (gender=='m')) {
				cout << "Customer Gender : Male" << endl;
			}
			else {
				cout << "Customer Gender : Female" << endl;
			}
			
			type = currentPtr->customerType;
			if (type=='G') {
				cout << "Customer Type : General Customer" << endl;
			}
			else if (type=='P') {
				cout << "Customer Type : Pending Customer" << endl;
			}
			else {
				cout << "Customer Type : Loan Customer" << endl;
				lType = currentPtr->loanType;
				if (lType == 'H' || lType == 'h') {
					cout << "Loan Type : Home Loan" << endl;
				}
				else if (lType == 'P' || lType == 'p') {
					cout << "Loan Type : Personal Loan" << endl;
				}
				else if (lType == 'G' || lType == 'g') {
					cout << "Loan Type : Gold Loan" << endl;
				}
				else {
					cout << "Loan Type : Leasing" << endl;
				}
				cout << "Loan Amount : " << currentPtr->loanAmount << endl;
				cout << "Loan Duration : " << currentPtr->loanDuration << endl;
			}
			cout << endl;
		}
		else{
			cout << "This Customer is Not Registered!" << endl;
		}
	}
}

void viewAllCustomer(){
	displayCustomerDetails('A');
}

void applyLoan(){
	int nic = 0; // customer nic
	char cType = NULL; //Customer type
	char lType = NULL; // Loan type
	double lAmount = 0; // Loan amount
	int lDuration = 0; //Loan Duration
	char save = NULL;
	int element = 0;
	customerPtr currentPtr = NULL;

	cout << "Enter the NIC Number : ";
	cin >> nic;
	if (nic<nicMin || nic >= nicMax) { //Checking NIC is a 5 digit number
		clearCMD();
		cout << "Entered NIC is Invalid!" << endl;
	}
	else {
		element = linearArrSearch(::custNIC, nic);
		if (element!=-1) {
			currentPtr = linearCustSearch(cust, nic);

			cType = currentPtr->customerType;
			//Checking Customer is a General Customer. Only General Customer can request for a loan
			if (cType=='G') {
				cout << "Enter Loan Type (H:- Home Loans / P:- Personal Loans / G:- Gold Loans / L:- Leasing) : ";
				cin >> lType;
				if ((lType!='H') && (lType != 'P') && (lType != 'G') && (lType != 'L') && 
					(lType != 'h') && (lType != 'p') && (lType != 'g') && (lType != 'l')) {
					clearCMD();
					cout << "Selected Loan Type is Invalid!\nLoan Request Unsuccessful!" << endl;
				}
				else {
					cout << "Enter Loan Amount : ";
					cin >> lAmount;
					cout << "Enter Loan Duration : ";
					cin >> lDuration;

					cout << endl;
					//Display entered loan details (Type, Amount and Duration)
					if (lType=='H' || lType=='h') {
						cout << "Loan Type : Home Loan" << endl;
					}
					else if(lType == 'P' || lType == 'p'){
						cout << "Loan Type : Personal Loan" << endl;
					}
					else if (lType == 'G' || lType == 'g') {
						cout << "Loan Type : Gold Loan" << endl;
					}
					else {
						cout << "Loan Type : Leasing" << endl;
					}
					cout << "Loan Amount : " << lAmount << endl;
					cout << "Loan Duration : " << lDuration << endl;

					do {
						//Entered Loan details save request
						cout << "Do you want to save these details (Y/N) : ";
						cin >> save;
						if (save == 'Y' || save == 'y') {
							//Storing Loan Request Details in a Queue
							enterLoanDetails(&headLoanPtr, &tailLoanPtr, nic, lType, lAmount, lDuration);
							currentPtr->customerType = 'P'; //Changing Customer Type
							clearCMD();
							cout << "Loan Request Successfully Placed!" << endl;
						}
						else if (save == 'N' || save == 'n') {
							clearCMD();
							cout << "Loan Request Unsuccessful!" << endl;
						}
						else {
							cout << "Invalid Entry!" << endl;
						}
					} while (save != 'Y' && save != 'y' && save != 'N' && save != 'n');
				}
			}
			else if(cType=='L'){
				clearCMD();
				cout << "Already there's a Obtained Loan under this Customer.\nLoan Request Unsuccessful!" << endl;
			}
			else {
				clearCMD();
				cout << "Already there's a Pending Loan under this Customer.\nLoan Request Unsuccessful!" << endl;
			}
		}
		else {
			clearCMD();
			cout << "This Customer is Not Registered!" << endl;
		}
	}
}

void appRejLoan(){
	int nic = 0;
	char save = NULL;
	char lType = NULL;
	customerPtr element = NULL;
	loanQueuePtr currentPtr = headLoanPtr;
	bool flag = false; // Use to end the queue
	
	if (isEmpty(currentPtr)) {
		cout << "There are no loan requests in the queue!" << endl;
	}
	else {
			do{
				nic = currentPtr->NIC;
				lType = currentPtr->loanType;
				
				cout << "Customer NIC : " << nic << endl;
				
				if (lType == 'H' || lType == 'h') {
					cout << "Loan Type : Home Loan" << endl;
				}
				else if (lType == 'P' || lType == 'p') {
					cout << "Loan Type : Personal Loan" << endl;
				}
				else if (lType == 'G' || lType == 'g') {
					cout << "Loan Type : Gold Loan" << endl;
				}
				else {
					cout << "Loan Type : Leasing" << endl;
				}
				cout << "Loan Amount : " << currentPtr->loanAmount << endl;
				cout << "Loan Duration : " << currentPtr->loanDuration << endl;
				cout << endl;

				do {
					//Entered Loan details save request
					cout << "Do you want to Approve the Loan (Y / N / Q :- Exit from queue) : ";
					cin >> save;
					if (save == 'Y' || save == 'y' || save == 'N' || save == 'n') {
						element = linearCustSearch(cust, nic);

						//Updating customer details
						if (save == 'Y' || save == 'y') {
							element->loanType = currentPtr->loanType;
							element->loanAmount = currentPtr->loanAmount;
							element->loanDuration = currentPtr->loanDuration;
							element->customerType = 'L';
							cout << "Loan Approved." << endl;
						}
						else {
							element->customerType = 'G';
							cout << "Loan Rejected." << endl;
						}
						deleteLoanDetails(&headLoanPtr, &tailLoanPtr);
					}
					else if (save == 'Q' || save == 'q') {
						clearCMD();
						flag = true;
						cout << "Exiting from loan queue...." << endl;
					}
					else {
						cout << "Invalid Entry!" << endl;
					}
				} while (save != 'Q' && save != 'q' && save == 'Y' && save == 'y' && save == 'N' && save == 'n');

				currentPtr = headLoanPtr;
			} while (currentPtr!=NULL && (save != 'Q' && save != 'q'));
	}
}

void viewAppCustomer(){
	displayCustomerDetails('L');
}

void viewPendingCustomer(){
	displayCustomerDetails('P');
}

void viewGeneralCustomer(){
	displayCustomerDetails('G');
}

void displayCustomerDetails(char type) {
	clearCMD();
	bool flag = true; //This used to check whether if there's any registered records
	customerPtr currentPtr = cust;
	if (type=='G' || type == 'A') {
		cout << "Customer NIC" << setw(20) << "Customer Name" << endl;
	}
	else {
		cout << "Customer NIC" << setw(20) << "Customer Name" << setw(20) << "Loan Amount" << endl;
	}
	
	while (!isEmpty(currentPtr)) {
		if (type == 'A' || (currentPtr->customerType == 'G' && type == 'G')) {
			flag = false;
			cout << setw(12) << currentPtr->NIC << "        " << currentPtr->customerName << endl;
		}
		else if (currentPtr->customerType == 'P' && type == 'P') {
			flag = false;
			cout << setw(12) << currentPtr->NIC << "        " << currentPtr->customerName << "        " << loanAmount(headLoanPtr, currentPtr->NIC) << endl;
		}else if(currentPtr->customerType == 'L' && type == 'L'){
			flag = false;
			cout << setw(12) << currentPtr->NIC << "        " << currentPtr->customerName << "        " << currentPtr->loanAmount << endl;
		}
		currentPtr = currentPtr->nextCustPtr;
	}

	if (flag) {
		cout << endl << "No Record Found!" << endl;
	}
	cout << endl;
}

int linearArrSearch(int NIC[] ,int searchKey){
	for (int x = 0; x < NOOFCUST;x++) {
		if (NIC[x] == searchKey) {
			return x;
		}
	}
	return -1;
}

customerPtr linearCustSearch(customerPtr sPtr, int nic) {
	customerPtr currentPtr = sPtr;
	while (!isEmpty(currentPtr)) {
		if (currentPtr->NIC == nic) {
			return currentPtr;
		}
		currentPtr = currentPtr->nextCustPtr;
	}
	return NULL;
}

double loanAmount(loanQueuePtr headLoanPtr,int nic) {
	loanQueuePtr current = headLoanPtr;
	while (current!=NULL) {
		if (current->NIC == nic) {
			return current->loanAmount;
		}
		current = current->nextLoanPtr;
	}
	return NULL;
}

void Sort(int NIC[]) {
	int temp = 0;
	for (int x = 1; x < NOOFCUST;x++) {
		for (int y = 0; y < NOOFCUST-1;y++) {
			if (NIC[y]>NIC[y+1]) {
				temp = NIC[y];
				NIC[y] = NIC[y + 1];
				NIC[y + 1] = temp;
			}
		}
	}
}

void clearCMD() {
	system("cls");
}

bool insertCustDetails(customerPtr *sPtr,int nic,char name[20],char address[50],int age,char gender,char type) {
	customerPtr newPtr = NULL;
	customerPtr currentPtr = NULL;
	customerPtr previousPtr = NULL;

	//Creating a new CustomerNode
	newPtr = new CustomerNode;

	if (!isEmpty(newPtr)) {
		//Stroing values to newly created node
		newPtr->NIC = nic;
		strcpy_s(newPtr->customerName, name);
		strcpy_s(newPtr->customerAddress, address);
		newPtr->customerAge = age;
		newPtr->customerGender = gender;
		newPtr->customerType = type;

		newPtr->nextCustPtr = NULL;
		currentPtr = *sPtr;

		//Finding where to place the new node
		while (!isEmpty(currentPtr) && currentPtr->NIC<nic) {
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextCustPtr;
		}
		
		//Linking newly created node
		if (isEmpty(previousPtr)) {
			newPtr->nextCustPtr = *sPtr;
			*sPtr = newPtr;
		}
		else {
			previousPtr->nextCustPtr = newPtr;
			newPtr->nextCustPtr = currentPtr;
		}

		//Enter customer to array custNIC
		for (int x = 0; x < NOOFCUST;x++) {
			if (::custNIC[x]==nicMax) {
				::custNIC[x] = nic;
				break;
			}
		}
		return true;
	}
	else {
		cout << "No memory!" << endl;
		return false;
	}
}

int deleteCustomerDetails(customerPtr *sPtr, int nic) {
	/*
	1) Return value 0 represents Customer registered in the system and that customer unregistered successfully
	2) Return value 1 represents Customer registered in the system but Customer has obtained a loan. Because of that customer
		cannot unregister from the system
	3) Return value 2 represents Customer registered in the system but Customer has requested a loan. Because of that customer
		cannot unregister from the system
	*/
	customerPtr tempPtr = NULL;
	customerPtr previousPtr = NULL;
	customerPtr currentPtr = NULL;

	if (nic == (*sPtr)->NIC) {
		if ((*sPtr)->customerType == 'G') {
			tempPtr = *sPtr;
			*sPtr = (*sPtr)->nextCustPtr;
			delete(tempPtr);
		}
		else if ((*sPtr)->customerType == 'L') {
			return 1;
		}
		else {
			return 2;
		}
	}
	else {
		previousPtr = *sPtr;
		currentPtr = (*sPtr)->nextCustPtr;

		while (!isEmpty(currentPtr) && currentPtr->NIC != nic) {
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextCustPtr;
		}

		if (!isEmpty(currentPtr)) {
			if (currentPtr->customerType == 'G') {
				tempPtr = currentPtr;
				previousPtr->nextCustPtr = currentPtr->nextCustPtr;
				delete(tempPtr);
			}
			else if(currentPtr->customerType == 'L'){
				return 1;
			}
			else {
				return 2;
			}
		}
	}
	for (int x = 0; x < NOOFCUST; x++) {
		if (::custNIC[x] == nic) {
			::custNIC[x] = nicMax;
		}
	}
	return 0;
}

int isEmpty(customerPtr sPtr) {
	return sPtr == NULL;
}

bool enterLoanDetails(loanQueuePtr *headPtr, loanQueuePtr *tailPtr, int nic, char type, double amount, int duration) {
	loanQueuePtr newPtr = new LoanQueueNode;

	if (!isEmpty(newPtr)) {
		newPtr->NIC = nic;
		newPtr->loanType = type;
		newPtr->loanAmount = amount;
		newPtr->loanDuration = duration;
		newPtr->nextLoanPtr = NULL;

		if (isEmpty(*headPtr)) {
			*headPtr = newPtr;
		}
		else {
			(*tailPtr)->nextLoanPtr = newPtr;
		}
		*tailPtr = newPtr;
		return true;
	}
	else {
		cout << "not inserted. No Memory Available." << endl;
		return false;
	}
}

void deleteLoanDetails(loanQueuePtr *headPtr,loanQueuePtr *tailPtr) {
	loanQueuePtr tempPtr = NULL;

	tempPtr = *headPtr;
	*headPtr = (*headPtr)->nextLoanPtr;

	if (isEmpty(*headPtr)) {
		*tailPtr = NULL;
	}

	delete(tempPtr);
}

int isEmpty(loanQueuePtr currentPtr) {
	return currentPtr == NULL;
}