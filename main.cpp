//username = admin
//password = admin456

#include <iostream>   // input and output operations
#include <iomanip>    //formatting
#include<fstream>     //file handling
#include <windows.h>  //color support
#include <thread>   //this_thread::sleep_for function
#include <chrono>  //For time-related functions
#include <ctime>  //get current date and time
#include <cctype>    // For case conversion


using namespace std;

//define book structure
 struct Book
{   int isbn;
    string name;
    string author;
    float price;
    int quantity;
};

//books array
const int maxSize = 12; // define the maximum number of books
    Book books[maxSize];
    int size= 0;   //size of the book array

//define order structure
struct Order
{
    string date;
    string customer;
    string orderBook;
    string authorBook;
    int orderQuantity;
    int orderTotal;
};

//order array
const int maxOrders = 5; // define the maximum number of orders
   Order orders[maxOrders];
   int orderSize=0;   //size of the order array


// Function declarations
void displayNethraBookShopASCIIArt();
void displayTopic();       //display topic
void login();        //handle user login details
void showMenu();           //display the main menu
void clearConsole();       //clear the console screen
void manageBooks();        //manage books
void manageOrders();       //manage orders
void backManageBooks();    //back to manage books menu
void backManageOrders();   //back to manage orders menu
void tryAgain();           //prompt the user to try again
void loadBooks(Book books[], int& size, const int maxSize);
void saveBooks(const Book books[], int size);
void loadOrders(Order orders[], int& orderSize, const int maxOrders);
void saveOrders(const Order orders[], int orderSize);
void showBooks(const Book books[], int size,int maxSize);   //show book list
void addBook(Book books[], int& size,int maxSize);         //add book
void searchBook(const Book books[],int size);       //search book
void updateBook(Book books[], int size);
void deleteBook(Book books[], int& size);      //delete book
void prepareQuotation();                       //prepare quotation
void setColor(int color);         //set text colors
void displayBookList(const Book books[], int size);  //show current book list before deleting
void showPendingOrders (const Order orders[], int orderSize, int maxOrders );   //show pending orders
void addOrder(Order orders[], int& orderSize, Book books[], int size);  //add order
void completePendingOrder(Order orders[], int& orderSize, Book books[], int& size);  //complete pending order
string getCurrentDate();   //get current data in YY-MM-DD format
bool compareIgnoreCase(const string& str1, const string& str2); // Function to compare two strings ignoring case
void about();  //show about
void addAnotherBook(); //add another book
void addAnotherOrder(); //add another order
void completeAnotherOrder(); //complete another order
void searchAnotherBook(); //search another book
void deleteAnotherBook(); //delete another book


//colors
const int GREEN = 10;
const int WHITE = 15;
const int YELLOW = 14;
const int PURPLE = 13;
const int RED = 12;
const int Cyan = 11;


//main function
int main()
{
    displayNethraBookShopASCIIArt();
    displayTopic();
    loadBooks(books, size, maxSize);  // Load books from file
    loadOrders(orders, orderSize, maxOrders);  // Load orders from file
    login();


    return 0;
}


//function definitions are start from here.

void displayNethraBookShopASCIIArt() {
    // Array of color codes for the animation
    const int colors[] = {14, 10, 12, 11, 13, 15};  // Yellow, Green, Red, Cyan, Purple, White

    // Loop through the colors to create an animation effect
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            setColor(colors[j]);
            cout << R"(







               _   _      _   _                ______             _      _____ _
              | \ | |    | | | |               | ___ \           | |    /  ___| |
              |  \| | ___| |_| |__  _ __ __ _  | |_/ / ___   ___ | | __ \ `--.| |__   ___  _ __
              | . ` |/ _ | __| '_ \| '__/ _` | | ___ \/ _ \ / _ \| |/ /  `--. | '_ \ / _ \| '_ \
              | |\  |  __| |_| | | | | | (_| | | |_/ | (_) | (_) |   <  /\__/ | | | | (_) | |_) |
              \_| \_/\___|\__|_| |_|_|  \__,_| \____/ \___/ \___/|_|\_\ \____/|_| |_|\___/| .__/
                                                                                          | |
                                                                                          |_|




                                                Version 1.0






    )" << endl;
     this_thread::sleep_for(chrono::milliseconds(150));  // Pause for a short duration
            system("cls");
        }
    }

    setColor(7);  // Reset color to default
}


void displayTopic()
{
    setColor(GREEN);
    cout<<"------------------------------------------------------------------------"<<endl;
    cout<<"|              Nethra Books - Management System                        |"<<endl;
    cout<<"------------------------------------------------------------------------"<<endl;
    setColor(WHITE);

    cout<<endl;
}

//this function clear the console screen and show the main topic.
void clearConsole()
{
    system("cls");
    displayTopic(); //function call
}

void login()
{
   //Hardcoded username and password, set as constants
   const string userName="admin";
   const string password="admin456";

   string user;
   string pass;

    bool isValidLogin = false;

    // Validate user login details
    // Execute the block of code repeatedly until the user enters the correct details.
    while (!isValidLogin) {
        cout<< "Enter correct usernme and password for login"<<endl;
        cout<<endl;
        cout << "User Name: ";
        cin >> user;
        cout << "Password: ";
        cin >> pass;

        if (user == userName && pass == password) {
            isValidLogin = true;
        } else {
            cout<<endl;
            cout << "Invalid login. Please try again." << endl;
            cout<<endl;
        }
    }

    showMenu(); //if user enter the correct details, this will show the Main menu.

}

void showMenu() //display Main menu
{
    clearConsole();
    //print Main menu
    setColor(YELLOW);
    cout<<"*** Main Menu ****"<<endl;
    setColor(WHITE);
    cout<<endl;
    cout<<"1.Manage Books"<<endl;
    cout<<"2.Manage Orders"<<endl;
    cout<<"3.Logout"<<endl;
    cout<<"4.About"<<endl;
    cout<<"5.Exit"<<endl;
    cout<<endl;
    //get user choice
     int a;
    cout<<"Enter your choice: ";
    cin>>a;
    //switch for handle user's choice
    switch(a)
    {

        case 1:
            manageBooks();
            break;

        case 2:
            manageOrders();
            break;

        case 3:
            clearConsole();
            login();
            break;

        case 4:
           clearConsole();
           about();
           break;
        case 5:
           cout<<endl;
           clearConsole();
           cout<<"Good Bye! Press Enter to Close"<<endl;
           exit(0);
           break;
        // Invalid choice, prompt user to try again
         default:
           cout<<endl;
           cout<<"Invalid choice"<<endl;
           tryAgain();
    }
}

void manageBooks()
{
    clearConsole();
    //print the Manage Book menu
    setColor(YELLOW);
    cout<<"**** Manage Books ****"<<endl;
    setColor(WHITE);
    cout<<endl;
    cout<<"1.View book list"<<endl;
    cout<<"2.Search book"<<endl;
    cout<<"3.Add book"<<endl;
    cout<<"4.Update book"<<endl;
    cout<<"5.Delete book"<<endl;
    cout<<"6.Go to main menu"<<endl;
    cout<<endl;
    //get user choice
    int b;
    cout<<"Enter your choice: ";
    cin>>b;
    cout<<endl;

    //switch for handle user's choice
    switch(b)
    {
        case 1:
             showBooks(books, size, maxSize);
            break;


        case 2:
            searchBook(books,size);
            break;

        case 3:

             addBook(books,size,maxSize);
             break;

         case 4:

             updateBook(books,size);
             break;

        case 5:
             deleteBook(books,size);
             break;

        case 6:
             showMenu();  //function call, go to main menu
             break;

        default:
            cout<<"Invalid choice";
            cout<<endl;
            // Prompt user to exit to book management menu
            backManageBooks();

    }
}

void manageOrders()
{
    clearConsole();
    //display Manage orders menu
    setColor(YELLOW);
    cout<<"**** Manage Orders ****"<<endl;
    setColor(WHITE);
    cout<<endl;
    cout<<"1.View pending orders"<<endl;
    cout<<"2.Add orders"<<endl;
    cout<<"3.Complete pending orders"<<endl;
    cout<<"4.Prepare quotation"<<endl;
    cout<<"5.Go to main menu"<<endl;
    cout<<endl;
    //get user choice as input
    int c;
    cout<<"Enter your choice: ";
    cin>>c;
    cout<<endl;

    //switch for handle user's choice
    switch(c)
    {

    case 1:
           showPendingOrders (orders, orderSize, maxOrders);
           break;
    case 2:
           addOrder(orders, orderSize,books,size);
           break;

    case 3:
        completePendingOrder(orders, orderSize, books, size);
        break;

    case 4:
        prepareQuotation();
        break;

    case 5:
        showMenu();
        break;

    default:
        cout<<"Invalid choice";
        cout<<endl;
        backManageOrders();

   }
}

void backManageBooks()
{
    //boolean for check if the input is valid
    bool isValidChoice = false;

    // Continue looping until a valid input(5) is received
    while (!isValidChoice) {
    int x;
    cout<<endl;
    cout<<"Enter 5 to Back: ";
    cin>>x;

    if (x == 5)
        {
            isValidChoice = true;
            manageBooks();
        }
    else
       {
      cout<<endl;
      //display error msg
      cout << "Please enter a valid input" << endl;
      cout<<endl;
       }
 }
}

void backManageOrders()
{
    //boolean for check if the input is valid
     bool isValidExit = false;

    // Continue looping until a valid input(5) is receive
    while (!isValidExit) {
    int y;
    cout<<endl;
    cout<<"Enter 5 to Back: ";
    cin>>y;

    if (y == 5)
        {
            isValidExit = true;
            manageOrders();
        }
    else
       {
      cout<<endl;
      cout << "Please enter a valid input" << endl;
      cout<<endl;
       }
 }
}

void tryAgain()
{
    //boolean for check if the input is valid
    bool isValidTry = false;

    // Continue looping until a valid input(5) is received
    while (!isValidTry) {
    int z;
    cout<<endl;
    cout<<"Enter 5 to Try Again: ";
    cin>>z;

    if (z == 5)
        {
            isValidTry = true;
            showMenu();
        }
    else
       {
      cout<<endl;
      //display error msg
      cout << "Please enter a valid input" << endl;
      cout<<endl;
       }
 }
}

void loadBooks(Book books[], int& size, const int maxSize) {
    ifstream inFile("books.txt");
    if (inFile.is_open()) {
        while (size < maxSize && inFile >> books[size].isbn) {
            inFile.ignore();
            getline(inFile, books[size].name);
            getline(inFile, books[size].author);
            inFile >> books[size].price >> books[size].quantity;
            size++;
        }
        inFile.close();
    } else {
        cout << "Error: Could not open books.txt" << endl;
    }
}

void saveBooks(const Book books[], int size) {
    ofstream outFile("books.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < size; ++i) {
            outFile << books[i].isbn << endl;
            outFile << books[i].name << endl;
            outFile << books[i].author << endl;
            outFile << books[i].price << endl;
            outFile << books[i].quantity << endl;
        }
        outFile.close();
    } else {
        cout << "Error: Could not open books.txt" << endl;
    }
}

void loadOrders(Order orders[], int& orderSize, const int maxOrders) {
    ifstream inFile("orders.txt");
    if (inFile.is_open()) {
        while (orderSize < maxOrders && getline(inFile, orders[orderSize].date)) {
            getline(inFile, orders[orderSize].customer);
            getline(inFile, orders[orderSize].orderBook);
            getline(inFile, orders[orderSize].authorBook);
            inFile >> orders[orderSize].orderQuantity >> orders[orderSize].orderTotal;
            inFile.ignore();
            orderSize++;
        }
        inFile.close();
    } else {
        cout << "Error: Could not open orders.txt" << endl;
    }
}

void saveOrders(const Order orders[], int orderSize) {
    ofstream outFile("orders.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < orderSize; ++i) {
            outFile << orders[i].date << endl;
            outFile << orders[i].customer << endl;
            outFile << orders[i].orderBook << endl;
            outFile << orders[i].authorBook << endl;
            outFile << orders[i].orderQuantity << endl;
            outFile << orders[i].orderTotal << endl;
        }
        outFile.close();
    } else {
        cout << "Error: Could not open orders.txt" << endl;
    }
}

void showBooks(const Book books[], int size, int maxSize)
{
    clearConsole();
            cout<<"**Book List**"<<endl;
            cout<<endl;

            //Want to make table like arrangement for user friendliness
            // Set column headers with specified width and alignment
            cout << left << setw(20) << "ISBN" << setw(20) << "Name" << setw(20) << "Author" << setw(15)<<internal<< "Price(Rs.)" << setw(15)<<internal << "Quantity" << endl;
             // Create a line separator for better readability
            cout << setfill('-') << setw(90) << "-" << setfill(' ') << endl; // Line separator


            for (int i = 0; i < size; i++)
                {
                   // Display each book's details with specified width and alignment
                   cout << left << setw(20) << books[i].isbn<< setw(20) << books[i].name << setw(20) << books[i].author << setw(15) << internal << books[i].price << setw(15) << internal << books[i].quantity << endl;
                }
                // Create a line separator after displaying the books
                cout << setfill('-') << setw(90) << "-" << setfill(' ') << endl;

                cout<<endl;

                cout<<"Max Limit = "<<maxSize<<"\t\t\t\tCurrent book count = "<<size<<endl;

                backManageBooks();
}

void searchBook(const Book books[], int size) {
    clearConsole();
    cout << "**Search Book**" << endl;
    cout << endl;
    string searchBook;
    cout << "Enter the book name or ISBN to search: ";
    cin.ignore(); // Ignore the newline character from the previous input
    getline(cin, searchBook); // Get the entire line as an input
    cout << endl;

    bool bookFound = false;

    for (int i = 0; i < size; i++) {
        // Compare ignoring case
        if (compareIgnoreCase(books[i].name, searchBook) || compareIgnoreCase(to_string(books[i].isbn), searchBook)) {
            bookFound = true;
            clearConsole();
            setColor(YELLOW);
            cout << "Book found" << endl;
            setColor(WHITE);
            cout << endl;
            cout << "ISBN: " << books[i].isbn << "\tName: " << books[i].name << "\tAuthor: " << books[i].author << "\tPrice(Rs.): " << books[i].price << "\t\tQuantity: " << books[i].quantity << endl;

            searchAnotherBook();
            break;
        }
    }

    if (!bookFound) {
        clearConsole();
        cout << "Book not found." << endl;
        searchAnotherBook();
    }


}


void addBook(Book books[], int& size, int maxSize) {
    if (size < maxSize) {
        clearConsole();
        cout << "**Add Book**" << endl;
        cout << endl;
        int newISBN;
        cout << "Enter ISBN: ";
        cin >> newISBN;
        // Check if a book with the same ISBN already exists
        int existingIndex = -1;
        for (int i = 0; i < size; i++) {
            if (books[i].isbn == newISBN) {
                existingIndex = i;
                break;
            }
        }
        if (existingIndex != -1) {
            // Book with the same ISBN already exists, update the quantity
            int additionalQuantity;
            cout << "Enter additional quantity: ";
            cin >> additionalQuantity;
            books[existingIndex].quantity += additionalQuantity;
            cout << "Quantity updated for existing book with ISBN " << newISBN << "." << endl;
        } else {
            // Book with the given ISBN doesn't exist, add a new book
            books[size].isbn = newISBN;
            cout << "Enter book name: ";
            cin.ignore();
            getline(cin, books[size].name);
            cout << "Enter author name: ";
            getline(cin, books[size].author);
            cout << "Enter price: ";
            cin >> books[size].price;
            cout << "Enter quantity: ";
            cin >> books[size].quantity;
            cout<<endl;
            cout << "Successfully added '" << books[size].name << "' to the book list." << endl;
            ++size;  //increment size of the book array because of the newly added book
        }
        saveBooks(books, size);  // Save changes to file
        addAnotherBook();
    } else {
        clearConsole();
        cout << "Cannot add more books. Maximum limit reached." << endl;
        backManageBooks();
    }
}

void updateBook(Book books[], int size) {
    clearConsole();
    cout << "**Update Book**" << endl;
    cout << endl;

    displayBookList(books, size);

    int updateISBN;
    cout << "Enter the ISBN of the book to update: ";
    cin >> updateISBN;

    // Find the index of the book with the given ISBN
    int updateIndex = -1;
    for (int i = 0; i < size; i++) {
        if (books[i].isbn == updateISBN) {
            updateIndex = i;
            break;
        }
    }

    if (updateIndex != -1) {
        clearConsole();
        cout << "Enter new details for the book:" << endl;
        cout << endl;

        cout << "Enter book name: ";
        cin.ignore();
        getline(cin, books[updateIndex].name);

        cout << "Enter author name: ";
        getline(cin, books[updateIndex].author);

        cout << "Enter price: ";
        cin >> books[updateIndex].price;

        cout << "Enter quantity: ";
        cin >> books[updateIndex].quantity;
        cout << endl;

        // Update data in the file
        const string filename = "books.txt";
        ofstream outFile(filename);
        if (!outFile) {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        for (int i = 0; i < size; i++) {
            outFile << books[i].isbn << endl;
            outFile << books[i].name << endl;
            outFile << books[i].author << endl;
            outFile << fixed << setprecision(2) << books[i].price << endl;
            outFile << books[i].quantity << endl;
        }

        outFile.close();

        setColor(YELLOW);
        cout << "Book details updated successfully." << endl;
        setColor(WHITE);
    } else {
        cout << "Book with ISBN " << updateISBN << " not found." << endl;
    }

    backManageBooks();
}


void deleteBook(Book books[], int& size) {
    clearConsole();

    displayBookList(books, size);

    // Prompt user for the ISBN of the book to be deleted
    int deleteISBN;
    cout << "Enter the ISBN of the book to delete: ";
    cin >> deleteISBN;

    // Find the index of the book with the given ISBN
    int deleteIndex = -1;
    for (int i = 0; i < size; i++) {
        if (books[i].isbn == deleteISBN) {
            deleteIndex = i;
            break;
        }
    }

    if (deleteIndex != -1) {
        // Shift elements to fill the gap caused by the deleted book
        for (int i = deleteIndex; i < size - 1; i++) {
            books[i] = books[i + 1];
        }

        --size;  // Decrement size of the book array after deleting a book

        // Update data in the file
        const string filename = "books.txt";
        ofstream outFile(filename);
        if (!outFile) {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        for (int i = 0; i < size; i++) {
            outFile << books[i].isbn << endl;
            outFile << books[i].name << endl;
            outFile << books[i].author << endl;
            outFile << fixed << setprecision(2) << books[i].price << endl;
            outFile << books[i].quantity << endl;
        }

        outFile.close();

        // Print message
        cout << endl;
        setColor(YELLOW);
        cout << "Book with ISBN " << deleteISBN << " has been deleted." << endl;
        setColor(WHITE);
    } else {
        cout << endl;
        cout << "Book with ISBN " << deleteISBN << " not found." << endl;
    }

    deleteAnotherBook();
}

void showPendingOrders (const Order orders[], int orderSize, int maxOrders )
{
     clearConsole();
        //display the pending orders header
        cout<<"**Pending Orders**"<<endl;
        cout<<endl;

        // Set column headers with specified width and alignment
        cout << left << setw(12) << "Date" << setw(20) << "Customer" << setw(25)<< "Book" << setw(25)<< "Author"<<setw(15) <<internal << "Quantity" <<setw(15) <<internal << "Total (Rs.)"<< endl;
        cout << setfill('-') << setw(115) << "-" << setfill(' ') << endl; // Line separator

        // Loop through the array of  orders and display their information
        for (int i = 0; i < orderSize; i++)
            {
              //Display each order's details with specified width and alignment
              cout << left << setw(12) << orders[i].date << setw(20) << orders[i].customer << setw(25) << orders[i].orderBook << setw(25) << orders[i].authorBook << setw(15) << internal << orders[i].orderQuantity << setw(15) << internal << orders[i].orderTotal<< endl;}

              cout << setfill('-') << setw(115) << "-" << setfill(' ') << endl; //line seperator

            cout<<endl;
            cout<<"Max Limit = "<<maxOrders<<"\t\t\t\tCurrent order count = "<<orderSize<<endl;

        backManageOrders(); //call function to exit to order management menu

}

void addOrder(Order orders[], int& orderSize, Book books[], int size) {
    if (orderSize < maxOrders) {
        clearConsole();

        cout<<"**Add Order**"<<endl;
        cout<<endl;

        orders[orderSize].date = getCurrentDate(); //set current date
        cout << "Customer: ";
        cin.ignore();
        getline(cin, orders[orderSize].customer);

       bool validBook = false;
       do {
           cout << "Book: ";
           getline(cin, orders[orderSize].orderBook);

           // Check if the book exists in the current book array
           for (int i = 0; i < size; i++) {
               if (compareIgnoreCase(books[i].name, orders[orderSize].orderBook)) {
                   validBook = true;

                   // Auto-generate author based on the existing book array
                   orders[orderSize].authorBook = books[i].author;

                   // Auto-generate price based on the existing book array
                   float price = books[i].price;

                   // Prompt user for quantity
                   cout << "Enter quantity: ";
                   cin >> orders[orderSize].orderQuantity;

                   //check the quantity is enough
                   if (orders[orderSize].orderQuantity > 0 && orders[orderSize].orderQuantity <= books[i].quantity) {
                       // Calculate subtotal
                       float subTotal = orders[orderSize].orderQuantity * price;

                       // Determine discount based on subtotal
                       float discount;
                       if (subTotal >= 5000) {
                           discount = 25; // 25% discount
                       } else if (subTotal >= 3000) {
                           discount = 20; // 20% discount
                       } else if (subTotal >= 1000) {
                           discount = 10; // 10% discount
                       } else {
                           discount = 0; // No discount for less than 1000 subtotal
                       }

                       // Calculate total with discount
                       orders[orderSize].orderTotal = subTotal - (subTotal * (discount / 100));

                       // Display details with discount
                       cout<<endl;
                       cout << discount << "% Discount added to the total bill" << endl;
                       cout << "Discount: Rs." << subTotal * (discount / 100) << endl;
                       cout << endl;
                       cout << "Total = Rs." << subTotal << " - Rs." << subTotal * (discount / 100) << " = Rs." << orders[orderSize].orderTotal << "/=" << endl;

                       cout << endl;
                       setColor(YELLOW);
                       cout << "Successfully added to the pending order list." << endl;
                       setColor(WHITE);

                       ++orderSize;

                       // Write the new order to the orders file
                       ofstream ordersFile("orders.txt", ios::app); // Open in append mode
                       if (ordersFile.is_open()) {
                           ordersFile << orders[orderSize - 1].date << endl;
                           ordersFile << orders[orderSize - 1].customer << endl;
                           ordersFile << orders[orderSize - 1].orderBook << endl;
                           ordersFile << orders[orderSize - 1].authorBook << endl;
                           ordersFile << orders[orderSize - 1].orderQuantity << endl;
                           ordersFile << orders[orderSize - 1].orderTotal << endl;
                           ordersFile.close();
                       } else {
                           cout << "Error: Unable to write to orders file." << endl;
                           // Handle error appropriately
                       }

                       addAnotherOrder();

                   } else {
                       cout<<endl;
                       cout << "Sorry, not enough stock. Available quantity: " << books[i].quantity << endl;
                       addAnotherOrder();
                   }

                   break;
               }
           }

           if (!validBook) {
               cout<<endl;
               cout << "Book not found. Press 1 to try again or press 5 to back:";

               int userChoice;
               cin >> userChoice;

               if (userChoice == 5) {
                   manageOrders();
               } else {
                   // Clear the input buffer to prevent infinite loop on invalid input
                   cin.clear();
                   cin.ignore(numeric_limits<streamsize>::max(), '\n');
               }
           }

       } while (!validBook);
   } else {
       clearConsole();
       cout<<"Sorry, order limit reached"<<endl;
       backManageOrders();
   }
}

void completePendingOrder(Order orders[], int& orderSize, Book books[], int& size) {
    clearConsole();

    // Check if there are no pending orders
    if (orderSize == 0) {
        cout << "No pending orders." << endl;
        backManageOrders();
        return;
    }

    // Display pending orders
    cout << "Pending Orders:" << endl;
    cout << endl;
    for (int i = 0; i < orderSize; i++) {
        cout << i + 1 << ". " << orders[i].customer <<" - " << orders[i].orderBook << " - " << orders[i].orderQuantity<<" books"<<" - Rs." << orders[i].orderTotal<<endl;
        cout << endl;
    }

    // Prompt user to enter the order number to complete the order
    int selectedIndex;
    cout<<endl;
    cout << "Enter the order number to complete: ";
    cin >> selectedIndex;
    selectedIndex -= 1;

    // Check if the entered index is valid
    if (selectedIndex >= 0 && selectedIndex < orderSize) {
        // Get the index of the selected pending order
        int arrayIndex = selectedIndex;

        int bookIndex = -1;
        // Find the book in the books array
        for (int j = 0; j < size; j++) {
            // Compare ignoring case
            if (compareIgnoreCase(books[j].name, orders[arrayIndex].orderBook)) {
                bookIndex = j;
                break;
            }
        }

        // Check if the book exists
        if (bookIndex != -1) {
            // Update the quantity of the completed order in the books array
            books[bookIndex].quantity -= orders[arrayIndex].orderQuantity;

            // Remove the order from the pending order list
            for (int j = arrayIndex; j < orderSize-1; j++) {
                orders[j] = orders[j + 1];
            }
            --orderSize;

            // Write updated books and orders to files

            // Update books file
            ofstream booksFile("books.txt");
            if (booksFile.is_open()) {
                for (int i = 0; i < size; ++i) {
                    booksFile << books[i].isbn << endl;
                    booksFile << books[i].name << endl;
                    booksFile << books[i].author << endl;
                    booksFile << books[i].price << endl;
                    booksFile << books[i].quantity << endl;
                }
                booksFile.close();
            } else {
                cout << "Error: Unable to update books file." << endl;
                // Handle error appropriately
            }

            // Update orders file
            ofstream ordersFile("orders.txt");
            if (ordersFile.is_open()) {
                for (int i = 0; i < orderSize; ++i) {
                    ordersFile << orders[i].date << endl;
                    ordersFile << orders[i].customer << endl;
                    ordersFile << orders[i].orderBook << endl;
                    ordersFile << orders[i].authorBook << endl;
                    ordersFile << orders[i].orderQuantity << endl;
                    ordersFile << orders[i].orderTotal << endl;
                }
                ordersFile.close();
            } else {
                cout << "Error: Unable to update orders file." << endl;
            }

            // Display success message
            cout << endl;
            setColor(YELLOW);
            cout << "Order #" << selectedIndex + 1 << " completed successfully!" << endl;
            cout << endl;
            cout << "Book quantity updated"<<endl;
            setColor(WHITE);
            completeAnotherOrder();
        } else {
            cout<<endl;
            // Display error message for book not found
            cout << "Error: Book not found in the book list." << endl;
            completeAnotherOrder();
        }
    } else {
        // Display error message for invalid index
        cout<<endl;
        cout << "Error: Invalid number" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        completeAnotherOrder();
    }

}


void prepareQuotation() {
    clearConsole();
    // Display the quotation header
    cout << "** Quotation **" << endl;
    cout << endl;

    // Declare variables for quotation details
    string date, customer, book, author;
    float price, discount, subTotal, total;
    int quantity;

    bool validBook = false;

    // Prompt user for quotation details
    cout << "Customer: ";
    cin.ignore();
    getline(cin, customer);

    while (!validBook) {
        // Prompt user for book details
        cout << "Book: ";
        getline(cin, book);

        // Find the book in the book array using case-insensitive comparison
        int bookIndex = -1;
        for (int i = 0; i < size; i++) {
            // Compare ignoring case
            if (compareIgnoreCase(book, books[i].name)) {
                bookIndex = i;
                break;
            }
        }

        if (bookIndex != -1) {
            // Book found, directly use information from the book list
            author = books[bookIndex].author;
            price = books[bookIndex].price;

            validBook = true;

            // Prompt user for quantity
            bool validQuantity = false;
            while (!validQuantity) {
                cout << "Enter quantity: ";
                cin >> quantity;

                if (quantity > 0 && quantity <= books[bookIndex].quantity) {
                    validQuantity = true;
                } else {
                    cout<<endl;
                    cout << "Sorry, not enough stock" << endl;
                    backManageOrders();
                }
            }

            // Calculate subtotal
            subTotal = quantity * price;

            cout << endl;
            // Display subtotal
            cout << "Subtotal: Rs." << subTotal << endl;
            cout << endl;

            // Determine discount based on subtotal
            if (subTotal >= 5000) {
                discount = 25; // 25% discount
            } else if (subTotal >= 3000) {
                discount = 20; // 20% discount
            } else if (subTotal >= 1000) {
                discount = 10; // 10% discount
            } else {
                discount = 0; // No discount for less than 1000 subtotal
            }

            // Calculate total with discount
            total = subTotal - (subTotal * (discount / 100));

            // Display details with discount
            cout << discount << "% Discount added to the total bill" << endl;
            cout << "Discount: Rs." << subTotal * (discount / 100) << endl;
            cout << endl;
            cout << "Total = Rs." << subTotal << " - Rs." << subTotal * (discount / 100) << " = Rs." << total << "/=" << endl;

            // Open a text file for writing a quotation
            ofstream outputFile("quotation.txt");

            // Check if the file is successfully opened
            if (outputFile.is_open()) {
                // Write information to the file
                outputFile << "********************************************" << endl;
                outputFile << "            Nethra Book Shop - Kandy        " << endl;
                outputFile << "********************************************" << endl;
                outputFile << endl;
                outputFile << getCurrentDate() << endl;
                outputFile << "Customer: " << customer << endl;
                outputFile << endl;
                outputFile << "Book: " << book << endl;
                outputFile << "Author: " << author << endl;
                outputFile << "Price: Rs." << price << endl;
                outputFile << "Quantity: " << quantity << endl;
                outputFile << endl;
                outputFile << "Subtotal: Rs." << subTotal << endl;
                outputFile << endl;
                outputFile << discount << "% Discount added to the bill" << endl;
                outputFile << "Discount: Rs." << subTotal * (discount / 100) << endl;
                outputFile << endl;
                outputFile << "Total : Rs." << subTotal << " - Rs." << subTotal * (discount / 100) << " = Rs." << total << "/=" << endl;
                outputFile << endl;
                outputFile << "----------------------------------------------" << endl;
                outputFile << "   Thank you for choosing Nethra Book Shop!   " << endl;
                outputFile << "**********************************************" << endl;
                // Close the file
                outputFile.close();

                cout << endl;
                // Inform the user that the quotation has been successfully written
                setColor(YELLOW);
                cout << "Quotation has been written to the file 'quotation.txt'" << endl;
                setColor(WHITE);
            } else {
                // Display a message if writing the quotation fails
                cout << "Quotation has not been written" << endl;
            }
        } else {
            cout << "Book not found. Press 1 to try again or press 5 to back: ";

            int userChoice;
            cin >> userChoice;

            if (userChoice == 1) {
                // Clear the input buffer to prevent infinite loop on invalid input
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else if (userChoice == 5) {
                manageOrders();
            }
        }
    }
    backManageOrders();
}


void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void displayBookList(const Book books[], int size) {
    // Display the current book list
    cout << "** Book List **" << endl;
    cout << endl;

    cout << left << setw(20) << "ISBN" << setw(20) << "Name" << setw(20) << "Author" << setw(15)<<internal<< "Price(Rs.)" << setw(15)<<internal << "Quantity" << endl;
             // Create a line separator for better readability
            cout << setfill('-') << setw(90) << "-" << setfill(' ') << endl; // Line separator

    for (int i = 0; i < size; i++)
        {
                // Display each book's details with specified width and alignment
          cout << left << setw(20) << books[i].isbn<< setw(20) << books[i].name << setw(20) << books[i].author << setw(15) << internal << books[i].price << setw(15) << internal << books[i].quantity << endl;
        }
                // Create a line separator after displaying the books
            cout << setfill('-') << setw(90) << "-" << setfill(' ') << endl;


    cout << endl;
}


string getCurrentDate() {
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);

    // Convert the current time to a string in the format YYYY-MM-DD
    struct tm* timeinfo;
    char buffer[80];
    timeinfo = localtime(&currentTime);
    strftime(buffer, sizeof(buffer), "%Y/%m/%d", timeinfo);

    return string(buffer);
}

bool compareIgnoreCase(const string& str1, const string& str2) {
    return equal(str1.begin(), str1.end(), str2.begin(), str2.end(), [](char c1, char c2) {
        return tolower(c1) == tolower(c2);
    });
}

void about()
{
    clearConsole();
    setColor(PURPLE);
    cout<<"Software Information: "<<endl;
    cout<<endl;
    setColor(WHITE);
    cout<<"Version : 1.0"<<endl;
    cout<<"Last Modified : 2023/12/12"<<endl;
    cout<<endl;
    cout<<"This Book Shop Management System assists administrators in efficiently managing books and orders.Features include viewing, adding, searching, and deleting books,as well as handling pending orders, adding new ones, marking as complete,and generating quotations." <<endl;
    setColor(PURPLE);
    cout<<endl;
    cout<<"Developer Details: "<<endl;
    cout<<endl;
    setColor(WHITE);
    cout<<"Name: Hasaranga Samarakoon"<<endl;
    cout<<"Expertise: System Development, Programming (C++), Problem-Solving"<<endl;
    cout<<"Passion: Technology Enthusiast, Continuous Learner"<<endl;
    cout<<endl;
    setColor(PURPLE);
    cout<<"Contact Developer: "<<endl;
    setColor(WHITE);
    cout<<endl;
    cout<<"Email: hasarangasamarakoon@gmail.com"<<endl;
    cout<<"Mobile: (+94)778929895"<<endl;
    cout<<endl;
    cout<<"Thank you for using Nethra Book Shop Management System !"<<endl;
    cout<<endl;
    int e;
    //boolean for check if the input is valid
     bool isValide = false;

    // Continue looping until a valid input(5) is receive
    while (!isValide) {
    cout<<endl;
    setColor(YELLOW);
    cout<<"Enter 5 to Back: ";
    setColor(WHITE);
    cin>>e;

    if (e == 5)
        {
            isValide = true;
            showMenu();
        }
    else
       {
      cout<<endl;
      cout << "Please enter a valid input" << endl;
      cout<<endl;
       }
 }
}

void addAnotherBook()
{
    cout<<endl;
    int g;
    cout<<"Enter 3 to add another book or Enter 5 to back:";
    cin>>g;
    cout<<endl;

    switch(g)
    {
    case 3 :
        addBook(books, size, maxSize);
        break;

    case 5:
        manageBooks();
        break;

    default:
        cout<<"Please Enter Valid Input"<<endl;
        addAnotherBook();
    }

}

void addAnotherOrder()
{
    cout<<endl;
    int f;
    cout<<"Enter 3 to add another order or Enter 5 to back:";
    cin>>f;
    cout<<endl;

    switch(f)
    {
    case 3 :
        addOrder(orders, orderSize,books,size);
        break;

    case 5:
        manageOrders();
        break;

    default:
        cout<<"Please Enter Valid Input"<<endl;
        addAnotherOrder();
    }
}

void completeAnotherOrder()
{
    cout<<endl;
    int h;
    cout<<"Enter 3 to complete another order or Enter 5 to back:";
    cin>>h;
    cout<<endl;

    switch(h)
    {
    case 3 :
        completePendingOrder(orders, orderSize, books, size);
        break;

    case 5:
        manageOrders();
        break;

    default:
        cout<<"Please Enter Valid Input"<<endl;
        completeAnotherOrder();
    }

}

void searchAnotherBook()
{
   cout<<endl;
    int k;
    cout<<"Enter 3 to search another book or Enter 5 to back:";
    cin>>k;
    cout<<endl;

    switch(k)
    {
    case 3 :
        searchBook(books,size);
        break;

    case 5:
        manageBooks();
        break;

    default:
        cout<<"Please Enter Valid Input"<<endl;
        searchAnotherBook();
    }
}

void deleteAnotherBook()
{
   cout<<endl;
    int l;
    cout<<"Enter 3 to delete another book or Enter 5 to back:";
    cin>>l;
    cout<<endl;

    switch(l)
    {
    case 3 :
        deleteBook(books, size);
        break;

    case 5:
        manageBooks();
        break;

    default:
        cout<<"Please Enter Valid Input"<<endl;
        deleteAnotherBook();
    }
}
