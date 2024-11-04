#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string>
using namespace std;

class Game
{
	public:
    	string name;
    	double price;

    	Game(const string& _name, double _price) {
               name = _name;
               price = _price;
        }

};

class Node
{
	public:
	    Game data;
    	Node* next;

        Node(const Game& _data) : data(_data), next(NULL) {}
};

class LinkedList
{
	private:
	    Node* head;

	public:
    	LinkedList() {
        head = NULL;
		}


    	void addGame(const string& name, double price)
		{
        	Node* newNode = new Node(Game(name, price));
        	newNode->next = head;
        	head = newNode;
    	}

	    void removeGame(const string& name)
		{
	        Node *current = head, *prev = NULL;
    	    while (current != NULL && current->data.name != name)
			{
            	prev = current;
            	current = current->next;
        	}

        	if (current == NULL)
			{
            	cout << "Game not found.\n";
            	return;
        	}
        	if (prev == NULL)
			{
	            head = current->next;
        	}
			else
			{
	            prev->next = current->next;
    	    }

	        delete current;
    	    cout << "Game removed: " << name << endl;
    	}

    	void setPrice(const string& name, double newPrice)
		{
        	Node* current = head;
        	while (current != NULL)
			{
	            if (current->data.name == name)
				{
	                current->data.price = newPrice;
    	            cout << "Price updated for " << name << ": $" << newPrice << endl;
        	        return;
            	}
            	current = current->next;
        	}
        	cout << "Game not found.\n";
    	}

    	void viewGames() const
		{
        	Node* current = head;
        	if (current==NULL)
			{
				cout<<"No games in Stock...\n";
	        	return;
			}
	        while (current != NULL)
			{
        	    cout << "Game: " << current->data.name << " - Price: $" << current->data.price << endl;
	            current = current->next;
    	    }
    	}

	    bool gameExists(const string& name) const
		{
    	    Node* current = head;
	        while (current != NULL)
			{
        	    if(current->data.name == name)
				{
            	    return true;
            	}
            	current = current->next;
        	}
        	return false;
    	}

	    double getGamePrice(const string& name) const
		{
	        Node* current = head;
    	    while (current != NULL)
			{
	            if (current->data.name == name)
				{
        	        return current->data.price;
            	}
            	current = current->next;
        	}
        	return 0.0;
		}
	

};


class MyQueue //customer buying things going to queue , then it will go from queue to file then admin will access the file and it will have all the detail of the sold games
{
private:
    Node* front;
    Node* rear;

public:
    MyQueue() {
        front = rear = NULL;
    }

    void enqueue(const Game& data)
    {
        Node* newNode = new Node(data);
        if (rear == NULL) {
            front = rear = newNode;
            return;
        }

        rear->next = newNode;
        rear = newNode;
    }

    void dequeue()
    {
        if (front == NULL) {
            return;
        }

        Node* temp = front;
        front = front->next;

        if (front == NULL) {
            rear = NULL;
        }

        delete temp;
    }

    Game frontValue() const
    {
        if (front != NULL) {
            return front->data;
        }
        return Game("", 0.0);
    }

    bool isEmpty() const
    {
        return front == NULL;
    }

    ~MyQueue()
    {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

class MyStack
{
	private:
	    Node* top;

	public:
    	MyStack() {
        top = NULL;
     }


    	void push(const Game& data)
		{
	        Node* newNode = new Node(data);
    	    newNode->next = top;
        	top = newNode;
    	}

	    void pop()
		{
	        if (top)
			{
	            Node* temp = top;
    	        top = top->next;
        	    delete temp;
        	}
    	}

	    Game topValue() const
		{
    	    if (top)
			{
	            return top->data;
	        }
    	    return Game("", 0.0);
    	}

    	bool isEmpty() const
		{
	        return top == NULL;
    	}

    	~MyStack()
		{
	        while (!isEmpty())
			{
        	    pop();
        	}
    	}
};

class Customer
{
	public:
		int counter=0;
		double sum=0;
    	string username;
    	double walletBalance;
    	MyStack cart;
    	LinkedList gameList; // New linked list to store games
    	MyStack purchasedGames; // Add this line to declare purchasedGames stack

         Customer(const string& _username, double _walletBalance, LinkedList& _sharedGameList) {
         username = _username;
         walletBalance = _walletBalance;
         gameList = _sharedGameList;
}

	    void addToCart(const string& gameName)
		{
        	if (gameList.gameExists(gameName))
			{
            	double gamePrice = gameList.getGamePrice(gameName);
            	Game gameToAdd(gameName, gamePrice);

	            cart.push(gameToAdd);
	            counter++;
	            cout << "Game added to cart: " << gameToAdd.name << " - Price: $" << gameToAdd.price << endl;
	            sum=sum+gameToAdd.price;
    	    }
			else
			{
            cout << "Game not found in the game list." << endl;
        	}
    	}

    	void checkout()
		{
        	double totalCost = 0;
        	while (!cart.isEmpty())
			{
	            Game purchasedGame = cart.topValue();
            	totalCost += purchasedGame.price;
            	cart.pop();
            	counter--;
            	purchasedGames.push(purchasedGame); // Add purchased games to the purchasedGames stack
        	}

	        if (walletBalance >= totalCost)
			{
            	walletBalance -= totalCost;
            	cout << "Checkout successful. Total cost: $" << totalCost << ". Wallet balance: $" << walletBalance << endl;
            	sum=0;
        	}
			else
			{
            	cout << "Insufficient balance. Total cost is $" << totalCost << ", but wallet balance is only $" << walletBalance << endl;
        	}
        	
    	}
    	void addFunds(double amount)
		{
        	if (amount > 0)
			{
	            walletBalance += amount;
    	        cout << "Funds added successfully. New wallet balance: $" << walletBalance << endl;
        	}
			else
			{
            	cout << "Invalid amount. Please enter a positive value." << endl;
        	}
    	}

    	void viewGames() const
		{
	        gameList.viewGames();
	        system("pause");
    	}

    	double searchGame(const string& name) const
		{
	        return gameList.getGamePrice(name);
    	}
	    void viewPurchasedGames() const
		{
	        cout << "Purchased Games:" << endl;
  	    	MyStack tempStack = purchasedGames; // Create a temporary stack for display
      		while (!tempStack.isEmpty())
			{
            	Game purchasedGame = tempStack.topValue();
            	tempStack.pop();
            	cout << "Game: " << purchasedGame.name << " - Price: " << purchasedGame.price << endl;
        	}
    	}
};

class Admin
{
	private:
	    LinkedList& gameList;

	public:
		Admin(LinkedList& _gameList) : gameList(_gameList) {}
		
    	void addGame(const string& name, double price)
		{
	        gameList.addGame(name, price);
    	}

    	void removeGame(const string& name)
		{
	        gameList.removeGame(name);
    	}

    	void setPrice(const string& name, double newPrice)
		{
	        gameList.setPrice(name, newPrice);
    	}

    	void viewGames() const
		{
	        gameList.viewGames();
	        system("pause");
    	}
};
void main_menu();
void customerMenu(Customer& customer)
{
   	char choice;
    bool back = false;
                          
    while (!back)
    
	{	cout << "                                    ______________________________ " << endl;
    	cout << "                                   |                              |" << endl;
        cout << "                                   |        Customer Menu         |"<<endl;
		cout << "                                   ||" << endl << endl << endl;
        cout<<"      My Wallet: $"<<customer.walletBalance<<"                                                     CART["<< customer.counter <<"] $"<<customer.sum<<endl<<endl;
        
        
        
        cout << "\t\t\t\t\t1. View Available Games\n";
        cout << "\t\t\t\t\t2. Add Game to Cart\n";
        cout << "\t\t\t\t\t3. Checkout\n";
        cout << "\t\t\t\t\t4. View Purchased Games\n";
        cout << "\t\t\t\t\t5. Add Funds\n";
        cout << "\t\t\t\t\t6. Sign Out\n"<<endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
		{
            case '1':{ 
            	system("cls");
            	cout<<"Total Games with Their Prices : \n";
                customer.viewGames();
                system("cls");
                break;}
            case '2':
			{
				system("cls");
            	cout<<"Add a Game to Cart : \n\n";
                string gameName;
                cout << "Name: ";
                cin >> gameName;
                customer.addToCart(gameName);
                cout<<"\n\n";
                system("pause");
                system("cls");
                break;
            }
            case '3':{
            	system("cls");
            	cout<<"Checkout Counter : \n\n";
            	customer.checkout();
            	cout<<"\n\n";
            	system("pause");
                break;}
            case '4':{
            	system("cls");
            	cout<<"Hope To See You Again :) "<<endl;
                customer.viewPurchasedGames();
                cout<<endl;
                system("pause");
                system("cls");
                break;
				}
            case '5':
            
            	system("cls");
            	cout<<"Manage Funds : \n\n";
				float balance;
               	cout<<"Add Funds : ";
               	cin>>balance;
               	customer.addFunds(balance);
               	cout<<endl;
               	system("pause");
               	system("cls");
                break;
            
            case '6': 
                back = true;
                system("cls");
                break;
        
                
            default:
                cout << "Invalid choice. Please try again.\n";
        }
       
    }
    main_menu();
}
void adminMenu(Admin& admin)
{
	
    char choice;
    bool back = false;
  	system("cls");
    while (!back)
	{	cout << "                                       ______________________________ " << endl;
    	cout << "                                      |                              |" << endl;
        cout << "                                      |        Admin Menu            |"<<endl;
		cout << "                                      ||" << endl << endl << endl;
        cout << "\t\t\t\t\t\t1. View All Games\n";
        cout << "\t\t\t\t\t\t2. Add Game\n";
        cout << "\t\t\t\t\t\t3. Remove Game\n";
        cout << "\t\t\t\t\t\t4. Set Game Price\n";
        cout << "\t\t\t\t\t\t5. Log Out\n\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
		{
            case '1':
            	system("cls");
            	cout<<"Total Games with Their Prices : \n";
                admin.viewGames();
                system("cls");
                break;            
            case '2':
			{
				system("cls");
            	cout<<"Enter Game Into the Stock.\n\n";
                string gameName;
                double price;
                cout << "Enter the game name: ";
                cin >> gameName;
                cout << "Enter game price: ";
                cin >> price;
                admin.addGame(gameName, price); // Call addGame function to add the game
                cout << "Game added successfully!\n";
                system("pause");
                system("cls");
                break;
            }
            case '3':
			{
				system("cls");
            	cout<<"Remove Game From the Stock.\n\n";
                string gameName;
                cout << "Enter game name: ";
                cin >> gameName;
                admin.removeGame(gameName); // Call RemoveGame function to remove the game
                cout << "\n\n";
                system("pause");
                system("cls");
                break;
            }
            case '4':
			{
				system("cls");
            	cout<<"Update Game Price.\n\n";
                string gameName;
                double price;
                cout << "Enter the game name : ";
                cin >> gameName;
                cout << "Enter it's New price: ";
                cin >> price;
                admin.setPrice(gameName, price); // Call addGame function to add the game
                cout << "\n\n";
                system("pause");
                break;
            }
            case '5':
                back = true;
                system("cls");
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                system("pause");
                system("cls");
        }
    }
}
void main_menu()
{
	LinkedList sharedGameList;  // Create a single instance of LinkedList for both Admin and Customer
    char choice;
    bool exitProgram = false;
	main:
	system("cls");
    while (!exitProgram)
	{
		
        system("CLS");
		cout << "                              ________________________________________________ " << endl;
    	cout << "                             |                                                |" << endl;
    	cout << "                             |        Game Sales & Account Rental System      |" << endl;
    	cout << "                             ||" << endl << endl << endl;
    	cout << "                                                Main Menu" << endl << endl << endl;
    	cout<<"    \t\t1. Login as Admin";
    	cout<<"    \t\t\t\t\t2. Continue as Customer\n";
//    	cout<<"\t\t\t\t3. Rent Accounts"<<endl;
        cout<<"               \t\t\t\t\t 3.Exit\n\n";
        cout<<"Enter your choice: ";
        cin >> choice;

        if(choice=='1')
		{
			system("cls");
    		char ch;
			string pin,email;
			string manager_acc[3]={"zaidwasim@gmail.com","asher@gmail.com","2022"};
			logadmin:
			cout<<"\n\n\t\t\t                  Login as Admin";
			cout<<"\n\nEmail    : ";
			cin>>email;
			cout<<"\nPin Code : ";
			for(int i=1;i<=4;i++)
			{
				ch = getch();
				pin += ch;
				cout<<"*";
			}
			cout<<endl;
			if((email == manager_acc[0] || email == manager_acc[1]) && pin == manager_acc[2] )
			{
				system("cls");
            	Admin admin(sharedGameList);	
            	adminMenu(admin);
        	}
        	else
			{
				cout<<"\nYou Entered Incorrect Details...Try Again!\n\n";
				system("pause");
				system("cls");
			}
		}
        else if(choice=='2')
		{
            Customer customer("DefaultCustomer", 100.0, sharedGameList);  
            system("cls");
            customerMenu(customer);
            break;
        }
        else if(choice=='3')
        {
            exitProgram = true;
    	}
        else
        {
            cout << "Invalid choice. Please try again.\n";
            system("pause");
        }
    }
}

int main()
{
	main_menu();

	return 0;
	}