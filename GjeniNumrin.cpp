#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
	int numri = rand() % 100 + 1;
	int gjetja;
	int tentime = 0;

	cout << "Mire se vini ne loje!" << endl;
	cout << "Gjeni numrin nga 1-100. " << endl;

	do {
		cout << "Shtypni numrin: ";
		cin >> gjetja;
		tentime++;

		if (gjetja < numri) {
			cout << "Numri eshte me i madh! Provoni perseri." << endl;
		}
		else if (gjetja > numri) {
			cout << "Numri eshte me i vogel. Provoni perseri." << endl;
		}
		else {
			cout << "Ju lumte! Ju keni gjetur numrin pas " << tentime << " tentimesh." << endl;
		}
	} while (gjetja != numri);

	return 0;
}