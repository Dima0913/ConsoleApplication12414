#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Fraction 
{
private:
    int numerator;
    int denominator;

    void reduce()
    {
        int gcd = findGCD(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
    }

    int findGCD(int a, int b) 
    {
        if (b == 0) return a;
        return findGCD(b, a % b);
    }

public:
    Fraction(int num = 0, int den = 1) : numerator(num), denominator(den)
    {
        if (den == 0)
        {
            cout << "Error: Denominator cannot be zero. Setting denominator to 1." << endl;
            denominator = 1;
        }
        reduce();
    }

    void input() 
    {
        cout << "Enter numerator: ";
        cin >> numerator;
        cout << "Enter denominator: ";
        cin >> denominator;
        if (denominator == 0) 
        {
            cout << "Error: Denominator cannot be zero. Setting denominator to 1." << endl;
            denominator = 1;
        }
        reduce();
    }

    void print() const
    {
        cout << numerator << "/" << denominator << endl;
    }

    Fraction add(const Fraction& other) const
    {
        int num = numerator * other.denominator + other.numerator * denominator;
        int den = denominator * other.denominator;
        return Fraction(num, den);
    }

    Fraction subtract(const Fraction& other) const 
    {
        int num = numerator * other.denominator - other.numerator * denominator;
        int den = denominator * other.denominator;
        return Fraction(num, den);
    }

    Fraction multiply(const Fraction& other) const
    {
        int num = numerator * other.numerator;
        int den = denominator * other.denominator;
        return Fraction(num, den);
    }

    Fraction divide(const Fraction& other) const 
    {
        if (other.numerator == 0)
        {
            cout << "Error: Cannot divide by zero. Returning original fraction." << endl;
            return *this;
        }
        int num = numerator * other.denominator;
        int den = denominator * other.numerator;
        return Fraction(num, den);
    }

    void saveToFile(const string& filename) const 
    {
        ofstream file(filename, ios::out);
        if (file.is_open()) {
            file << numerator << " " << denominator << endl;
            file.close();
        }
        else
        {
            cout << "Unable to open file for writing." << endl;
        }
    }

    void loadFromFile(const string& filename) 
    {
        ifstream file(filename, ios::in);
        if (file.is_open()) 
        {
            file >> numerator >> denominator;
            if (denominator == 0)
            {
                cout << "Error: Denominator cannot be zero in file. Setting denominator to 1." << endl;
                denominator = 1;
            }
            file.close();
            reduce();
        }
        else 
        {
            cout << "Unable to open file for reading." << endl;
        }
    }
};

int main() 
{
    Fraction f1, f2;

    cout << "Enter first fraction:" << endl;
    f1.input();

    cout << "Enter second fraction:" << endl;
    f2.input();

    Fraction sum = f1.add(f2);
    Fraction difference = f1.subtract(f2);
    Fraction product = f1.multiply(f2);
    Fraction quotient = f1.divide(f2);

    cout << "First fraction: ";
    f1.print();

    cout << "Second fraction: ";
    f2.print();

    cout << "Sum: ";
    sum.print();

    cout << "Difference: ";
    difference.print();

    cout << "Product: ";
    product.print();

    cout << "Quotient: ";
    quotient.print();

    string filename = "fraction.txt";
    f1.saveToFile(filename);
    cout << "First fraction saved to file." << endl;

    Fraction f3;
    f3.loadFromFile(filename);
    cout << "Loaded fraction from file: ";
    f3.print();

}