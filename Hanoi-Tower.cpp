#include<iostream>
#include<math.h>
using namespace std;


void printMovements(int numberOfDisks, int counter, string start, string temp, string end)
{
	if (counter == 1)
	{
		cout << numberOfDisks - counter + 1 << " " << start << " " << end << endl;
		return;
	}
	printMovements(numberOfDisks,counter - 1, start, end, temp);
	cout << numberOfDisks - counter + 1 << " " << start << " " << end << endl;
	printMovements(numberOfDisks, counter - 1, temp, start, end);
}

int movmentsNumber(int numberOfDisks)
{
	return (pow(2, numberOfDisks) - 1);
}

int main()
{
	int numberOfDisks;
	string rod1, rod2, rod3;

	cin >> numberOfDisks;
	cin >> rod1 >> rod2 >> rod3;
	cout << movmentsNumber(numberOfDisks) << endl;
	printMovements(numberOfDisks,numberOfDisks, rod1, rod2, rod3);

	return 0;
}