#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Menu {
private:
	int price;
public:
	Menu(int price) : price{ price } {};

	virtual string descriere() = 0;

	virtual int getPret() {
		return price;
	}

	~Menu() = default;
};

class Coffeed : public Menu {
private:
	Menu& m;
public:
	Coffeed(Menu& m) : Menu{ m.getPret() }, m{ m }{};

	string descriere() override {
		return m.descriere() + " caffeinated";
	}

	int getPret() override {
		return m.getPret() + 5;
	}

	~Coffeed() = default;
};

class Cooled : public Menu {
private:
	Menu& m;
public:
	Cooled(Menu& m) : Menu{ m.getPret() }, m{ m }{};

	string descriere() override {
		return m.descriere() + " cooled";
	}

	int getPret() override {
		return m.getPret() + 4;
	}

	~Cooled() = default;
};

class Breakfast : public Menu {
private:
	string name;
public:
	Breakfast(const string& name) : Menu{ 0 }, name{ name }{};

	string descriere() override {
		return name;
	}

	int getPret() override {
		if (name == "omlette") return Menu::getPret() + 15;
		if (name == "eggs") return Menu::getPret() + 10;
	}

	~Breakfast() = default;
};

vector<Menu*> fun() {
	vector<Menu*> menus;

	Breakfast* bf1 = new Breakfast{ "omlette" };
	Cooled* cool1 = new Cooled{ *bf1 };
	Coffeed* coof1 = new Coffeed{ *cool1 };
	menus.push_back(coof1);

	Breakfast* bf2 = new Breakfast{ "eggs" };
	Coffeed* coof2 = new Coffeed{ *bf2 };
	menus.push_back(bf2);

	Breakfast* bf3 = new Breakfast{ "omlette" };
	menus.push_back(bf3);

	return menus;
}

int main() {
	auto orders = fun();
	sort(orders.begin(), orders.end(), [](Menu* m1, Menu* m2) { return m1->getPret() > m2->getPret(); });
	for (auto order : orders) {
		cout << order->descriere() << " " << order->getPret() << "\n";
	}
	return 0;
}