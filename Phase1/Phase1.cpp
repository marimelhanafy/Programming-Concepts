//Marim Elhanafy 201803468
//Hissa Al-Mohannadi 201801523
//Hagar Elsayed 201805123
//project c++ Fall2019 : Phase1
//B55 : Instructor: Aws Fida El-Din
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;
void drawLine(char);
int choices();
int main()
{
	char repeat;
	do
	{
		string ItemName;
		int quantity, ItemNo, AisleNo, ExpMonth, ExpDay;
		double price;
		fstream file;
		file.open("inventory.txt", ios::in | ios::out);
		if (file.fail()) //Testing for File Open Errors
		{
			cout << "File open failure!\n";
			return 0;
		}
		switch (choices())
		{
		case 1: //add new item :  asks the user to input data of a new item and then add the data to the items file
		{
			char val;
			cout << "Stock Control - Add Item: \n";
			drawLine('=');
			cout << "Enter the item Expiry Day: ";
			cin >> ExpDay;
			cout << "Enter the item Expiry Month: ";
			cin >> ExpMonth;
			cout << "Enter the item Aisle No: ";
			cin >> AisleNo;
			cout << "Enter the item Number: ";
			cin >> ItemNo;
			cout << "Enter the item price: ";
			cin >> price;
			cout << "Enter the quantity to be added: ";
			cin >> quantity;
			cout << "Enter the item name: ";
			cin.ignore();
			getline(cin, ItemName);
			cout << "Do you want to save the item? (Y/N) ";
			cin >> val;
			while (val != 'Y' && val != 'y' && val != 'N' && val != 'n')
			{
				cout << "Enter (Y/N)!";
				cin >> val;
			}
			if (val == 'Y' || val == 'y')
			{
				file << ExpDay << "\t" << ExpMonth << "\t" << AisleNo << "\t" << ItemNo << "\t" << price << "\t" << quantity << "\t" << ItemName;
				cout << "The Item saved successfully.\n";
			}
			else cout << "The Item not saved. Thank you!";
			break;
		}
		case 2: //List the current inventory in a tabular format all the information about each item
		{
			cout << "ExpDateDay\tExpDateMonth\tAisleNo\tItemNo\tprice\tQuantity\tItemName\n";
			while (file >> ExpDay >> ExpMonth >> AisleNo >> ItemNo >> price >> quantity)
			{
				getline(file, ItemName);
				cout << setw(10) << ExpDay << setw(18) << ExpMonth << setw(11) << AisleNo << setw(7) << ItemNo << setw(7) << price << setw(11) << quantity << ItemName << endl;
			}
			break;
		}
		case 3: //All items whose quantity field < 5
		{
			cout << "ExpDateDay\tExpDateMonth\tAisleNo\tItemNo\tprice\tquantity\tItemName\n";
			while (!file.eof())
			{
				file >> ExpDay >> ExpMonth >> AisleNo >> ItemNo >> price >> quantity;
				getline(file, ItemName);
				if (quantity < 5)
				{
					cout << setw(10) << ExpDay << setw(18) << ExpMonth << setw(11) << AisleNo << setw(7) << ItemNo << setw(7) << price << setw(11) << quantity << ItemName << endl;
				}
			}
			break;
		}
		case 4: //All items whose price is less than a value provided by the user
		{
			double userPrice;
			cout << "Enter a price : ";
			cin >> userPrice;
			cout << "Items with less price than " << userPrice << " are : \n";
			cout << "ExpDateDay\tExpDateMonth\tAisleNo\tItemNo\tprice\tquantity\tItemName\n";
			while (!file.eof())
			{
				file >> ExpDay >> ExpMonth >> AisleNo >> ItemNo >> price >> quantity;
				getline(file, ItemName);
				if (price < userPrice)
				{
					cout << setw(10) << ExpDay << setw(18) << ExpMonth << setw(11) << AisleNo << setw(7) << ItemNo << setw(7) << price << setw(11) << quantity << ItemName << endl;
				}
			}
			break;
		}
		case 5: //Show All expired items information
		{
			cout << "Expired Items are : \n";
			cout << "ExpDateDay\tExpDateMonth\tAisleNo\tItemNo\tprice\tquantity\tItemName\n";
			while (!file.eof())
			{
				file >> ExpDay >> ExpMonth >> AisleNo >> ItemNo >> price >> quantity;
				getline(file, ItemName);
				if (ExpMonth == 12 && ExpDay == 31)
				{
					cout << setw(10) << ExpDay << setw(18) << ExpMonth << setw(11) << AisleNo << setw(7) << ItemNo << setw(7) << price << setw(11) << quantity << ItemName << endl;
				}
			}
			break;
		}
		case 6: //Stock statistics: the average price, the most expensive item, the least expensive item
		{
			string maxItemName, minItemName;
			int maxQuantity, maxItemNo, maxAisleNo, maxExpMonth, maxExpDay, minQuantity, minItemNo, minAisleNo, minExpMonth, minExpDay, counter = 0;
			double maxPrice, minPrice, sum = 0, value, max = 0, min = 0, average = 0;
			while (!file.eof())
			{
				file >> ExpDay >> ExpMonth >> AisleNo >> ItemNo >> price >> quantity;
				getline(file, ItemName);
				sum += price;
				counter++;
				if (max <= price)
				{
					max = price;
					maxExpDay = ExpDay;
					maxExpMonth = ExpMonth;
					maxAisleNo = AisleNo;
					maxItemNo = ItemNo;
					maxPrice = price;
					maxQuantity = quantity;
					maxItemName = ItemName;
				}
				else if (min == 0) min = price;
				else if (min >= price)
				{
					min = price;
					minExpDay = ExpDay;
					minExpMonth = ExpMonth;
					minAisleNo = AisleNo;
					minItemNo = ItemNo;
					minPrice = price;
					minQuantity = quantity;
					minItemName = ItemName;
				}
			}
			average = sum / counter;
			cout << "Average price is " << average << endl;
			cout << "The maximum price is " << max << " QR \n";
			cout << "The minimum price is " << min << " QR \n";
			cout << "The most expensive item is : \n";
			cout << "ExpDateDay\tExpDateMonth\tAisleNo\tItemNo\tprice\tquantity\tItemName" << endl;
			cout << setw(10) << maxExpDay << setw(18) << maxExpMonth << setw(11) << maxAisleNo << setw(7) << maxItemNo << setw(7) << maxPrice << setw(11) << maxQuantity << maxItemName << endl;
			cout << "The least expensive item is : \n";
			cout << "ExpDateDay\tExpDateMonth\tAisleNo\tItemNo\tprice\tquantity\tItemName" << endl;
			cout << setw(10) << minExpDay << setw(18) << minExpMonth << setw(11) << minAisleNo << setw(7) << minItemNo << setw(7) << minPrice << setw(11) << minQuantity << minItemName << endl;
			break;
		}
		case 9: //exit the menu
		{
			cout << "Bye, see you again later!";
			break;
		}
		default: cout << "Please enter valid number"; //check validation
		}
		file.close();
		cout << "Do you want to repeat the menu? (Y/N) : ";
		cin >> repeat;
	} while (repeat == 'Y' || repeat == 'y'); //ask user if he want yo repeat the menu
	return 0;
}
void drawLine(char ch) //function to draw a line 
{
	for (int m = 0; m < 25; m++) cout << ch;
	cout << endl;
}
int choices() //function display choices and return the user choice 
{
	int choice;
	cout << "Hypermarket Managment System \n" << endl;
	cout << "\t\t[1] Add Item\n";
	cout << "\t\t[2] List Items\n";
	cout << "\t\t[3] Item whose quantity < 5\n";
	cout << "\t\t[4] Item with less price than a given price\n";
	cout << "\t\t[5] Expired items\n";
	cout << "\t\t[6] Stock statistics\n\n";
	cout << "\t\t[9] Exit\n";
	cout << "\tEnter your choice: ";
	cin >> choice;
	cout << endl;
	return choice;
}