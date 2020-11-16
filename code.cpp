#include <iostream>
#include <vector>
#include <thread>
#include <string>

using namespace std;

void addProp(double prop, double& sum) {
	sum += prop;
}

void addChild(double prop1, double prop2, double& sum) {
	thread* t[2];
	t[0] = new thread{ addProp, prop1, ref(sum) };
	t[1] = new thread{ addProp, prop2, ref(sum) };

	for (int i = 0; i < 2; i++) {
		t[i]->join();
		delete t[i];
	}
} 

void addDad(double prop1, double prop2, double prop3, double prop4, double& sum) {
	thread* th[2];
	th[0] = new thread{ addChild, prop1, prop2, ref(sum) };
	th[1] = new thread{ addChild, prop3, prop4, ref(sum) };
	
	for (int i = 0; i < 2; i++) {
		th[i]->join();
		delete th[i];
	}
}

int main()
{
	vector<double> childrenProp;

	string str;
	double prop = 0;
	double realProportion = 0;
	int sum = 0;

	do {
		for (int i = 0; i < 1; i++) {
			cout << "Enter sum (positive,  integer number)" << endl;
			cin >> str;

			try {
				sum = stoi(str);
			}
			catch (const std::exception&) {
				i--;
			}
		}
	} while (sum <= 0);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				do {
					cout << "Enter the proportion of the " << k + 1 << "th son of the "
						<< j + 1 << "th dad od the " << i + 1 << "th grandad (not negative, from 0 to 1)" << endl;

					cin >> str;
					try {
						prop = stod(str);
					}
					catch (const std::exception&) {
						k--;
					}
				} while (prop < 0 || prop > 1);

				childrenProp.push_back(prop);
				prop = 0;
			}
		}
	}

	thread* thr[2];
	for (int i = 0; i < 2; i++) {
		thr[i] = new thread{ addDad, childrenProp[i * 4], childrenProp[i * 4 + 1], childrenProp[i * 4 + 2],
			childrenProp[i * 4 + 3], ref(realProportion) };
	}

	for (int i = 0; i < 2; i++) {
		thr[i]->join();
		delete thr[i];
	}

	if (realProportion * sum != sum) {
		cout << "Incorrect";
	}
	else {
		cout << "Correct";
	}

	return 0;
}
