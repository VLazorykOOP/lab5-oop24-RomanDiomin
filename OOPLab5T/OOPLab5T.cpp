#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
#include <random>    
using namespace std;

class Transport {
protected:
    string name;
public:
    Transport(string _name) : name(_name) {
    }

    virtual ~Transport() {}

    virtual void printInfo() {}
};

class Car : public Transport {
public:
    Car(string _name) : Transport(_name) {}

    ~Car() {}

    void printInfo() override {
        cout << "Car: " << name << endl;
    }
};

class Truck : public Transport {
public:
    Truck(string _name) : Transport(_name) {}

    ~Truck() {}

    void printInfo() override {
        cout << "Lorry: " << name << endl;
    }
};

class Steamship : public Transport {
public:
    Steamship(string _name) : Transport(_name) {
    }

    ~Steamship() {
    }

    void printInfo() override {
        cout << "Steamship: " << name << endl;
    }
};

class Airplane : public Transport {
public:
    Airplane(string _name) : Transport(_name) {
    }

    ~Airplane() {
    }

    void printInfo() override {
        cout << "flight: " << name << endl;
    }
};

class Card {
private:
    string suit;
    string rank;

public:
    Card(string _suit, string _rank) : suit(_suit), rank(_rank) {}

    void print() const {
        cout << rank << " of " << suit << endl;
    }

    string getSuit() const {
        return suit;
    }

    string getRank() const {
        return rank;
    }
};

class Deck {
private:
    vector <Card> cards;

public:
    Deck(bool shuffle = true) {
        string suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
        string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };

        for (const auto& suit : suits) {
            for (const auto& rank : ranks) {
                cards.emplace_back(Card(suit, rank));
            }
        }

        if (shuffle) {
            random_shuffle(cards.begin(), cards.end());
        }
    }

    void print() const {
        for (const auto& card : cards) {
            card.print();
        }
    }

    vector<Card> getCards() const {
        return cards;
    }
};

class Solitaire : public Deck {
public:
    Solitaire() : Deck(false) {}

    void play() {
        vector<Card> cards = getCards();
        for (int i = 0; i < 3; ++i) {
            for (size_t j = 0; j < cards.size() - 2; ++j) {
                if (cards[j].getSuit() == cards[j + 2].getSuit()) {
                    cout << "Removed cards: ";
                    cards[j].print();
                    cards[j + 1].print();
                    cards[j + 2].print();
                    cout << endl;
                    cards.erase(cards.begin() + j, cards.begin() + j + 3);
                }
            }
        }
    }
};


class Vector {
protected:
    int* data;
    size_t length;

public:
    Vector() : data(nullptr), length(0) {}

    explicit Vector(size_t size) : length(size) {
        data = new int[length];
    }

    Vector(const Vector& other) : length(other.length) {
        data = new int[length];
        for (size_t i = 0; i < length; ++i) {
            data[i] = other.data[i];
        }
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new int[length];
            for (size_t i = 0; i < length; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    ~Vector() {
        delete[] data;
    }

    int& operator[](size_t index) {
        if (index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const int& operator[](size_t index) const {
        if (index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t size() const {
        return length;
    }

    void push_back(int value) {
        int* temp = new int[length + 1];
        for (size_t i = 0; i < length; ++i) {
            temp[i] = data[i];
        }
        temp[length++] = value;
        delete[] data;
        data = temp;
    }

    void pop_back() {
        if (length == 0) {
            throw std::out_of_range("Vector is empty");
        }
        --length;
        int* temp = new int[length];
        for (size_t i = 0; i < length; ++i) {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
    }

    void resize(size_t size) {
        int* temp = new int[size];
        size_t minSize = size < length ? size : length;
        for (size_t i = 0; i < minSize; ++i) {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
        length = size;
    }

    void clear() {
        delete[] data;
        data = nullptr;
        length = 0;
    }
};

class SafeVector : public Vector {
private:
    int lower_bound;
    int upper_bound;

public:
    SafeVector(int lower, int upper) : lower_bound(lower), upper_bound(upper) {}

    SafeVector(const SafeVector& other) : Vector(other), lower_bound(other.lower_bound), upper_bound(other.upper_bound) {}

    SafeVector& operator=(const SafeVector& other) {
        if (this != &other) {
            Vector::operator=(other);
            lower_bound = other.lower_bound;
            upper_bound = other.upper_bound;
        }
        return *this;
    }

    int& operator[](size_t index) {
        if (index < lower_bound || index >= upper_bound) {
            throw std::out_of_range("Index out of range");
        }
        return Vector::operator[](index - lower_bound);
    }

    const int& operator[](size_t index) const {
        if (index < lower_bound || index >= upper_bound) {
            throw std::out_of_range("Index out of range");
        }
        return Vector::operator[](index - lower_bound);
    }
};

int main() {
    int task;
    cout << "Enter task: ";
    cin >> task;
    switch (task)
    {
    case 1: {
        Transport* transports[] = {
        new Car("BMW"),
        new Truck("Volvo"),
        new Steamship("Titanic"),
        new Airplane("Boeing 747")
        };

        for (int i = 0; i < 4; ++i) {
            transports[i]->printInfo();
        }

        for (int i = 0; i < 4; ++i) {
            delete transports[i];
        }
        break;
    }
    case 2: {
        cout << "Ordered Deck:" << endl;
        Deck orderedDeck(false);
        orderedDeck.print();

        cout << "\nShuffled Deck:" << endl;
        Deck shuffledDeck;
        shuffledDeck.print();

        cout << "\nSolitaire Game:" << endl;
        Solitaire solitaire;
        solitaire.play();
        break;
    }
    case 3: {
        try {
            SafeVector sv(0, 9);
            sv.push_back(10);
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Caught exception: " << e.what() << std::endl;
        }
        break;
    }
    }
    return 0;
}
