#include <iostream>
using namespace std;

class Contact 
{
private:
    char* fullName;
    char homePhone[20];
    char workPhone[20];
    char mobilePhone[20];
    char additionalInfo[100];

public:
    Contact() : fullName(nullptr) {}

    Contact(const char* name, const char* home, const char* work, const char* mobile, const char* info) 
    {
        allocateMemoryForName(name);
        copyString(homePhone, home);
        copyString(workPhone, work);
        copyString(mobilePhone, mobile);
        copyString(additionalInfo, info);
    }

    ~Contact() 
    {
        delete[] fullName;
    }

    void allocateMemoryForName(const char* name)
    {
        int length = 0;
        while (name[length] != '\0')
        {
            length++;
        }
        fullName = new char[length + 1];
        for (int i = 0; i <= length; ++i)
        {
            fullName[i] = name[i];
        }
    }

    void input()
    {
        char tempName[100];
        cout << "enter your full name: ";
        cin.ignore();
        cin.getline(tempName, 100);
        allocateMemoryForName(tempName);

        cout << "enter home number:  ";
        cin.getline(homePhone, 20);
        cout << "enter work number:  ";
        cin.getline(workPhone, 20);
        cout << "enter mobile phone number:  ";
        cin.getline(mobilePhone, 20);
        cout << "enetr additional info:  ";
        cin.getline(additionalInfo, 100);
    }

    void display() const
    {
        cout << "full name:        " << fullName << endl;
        cout << "home phone:       " << homePhone << endl;
        cout << "work phone:       " << workPhone << endl;
        cout << "mobile phone:     " << mobilePhone << endl;
        cout << "additional info:  " << additionalInfo << endl;
    }

    const char* getFullName() const
    {
        return fullName;
    }

private:
    void copyString(char* destination, const char* source)
    {
        int i = 0;
        while (source[i] != '\0')
        {
            destination[i] = source[i];
            i++;
        }
        destination[i] = '\0';
    }
};

const int MAX_CONTACTS = 100;

class PhoneBook
{
private:
    Contact contacts[MAX_CONTACTS];
    int count;

public:
    PhoneBook() : count(0) {}

    void addContact()
    {
        if (count < MAX_CONTACTS)
        {
            contacts[count].input();
            count++;
        }
        else
        {
            cout << "phone book is full" << endl;
        }
    }

    //удаление
    void removeContact(const char* name)
    {
        for (int i = 0; i < count; i++)
        {
            if (compareStrings(contacts[i].getFullName(), name))
            {
                for (int j = i; j < count - 1; j++)
                {
                    contacts[j] = contacts[j + 1];
                }
                count--;
                cout << "subscriber deleted" << endl;
                return;
            }
        }
        cout << "not found" << endl;
    }

    void searchContact(const char* name) const
    {
        for (int i = 0; i < count; i++)
        {
            if (compareStrings(contacts[i].getFullName(), name))
            {
                contacts[i].display();
                return;
            }
        }
        cout << "not found" << endl;
    }

    void showAllContacts() const
    {
        if (count == 0)
        {
            cout << "phone book is empty" << endl;
        }
        else
        {
            for (int i = 0; i < count; i++)
            {
                contacts[i].display();
                cout << "-----------------------------" << endl;
            }
        }
    }

private:
    bool compareStrings(const char* str1, const char* str2) const
    {
        int i = 0;
        while (str1[i] != '\0' && str2[i] != '\0')
        {
            if (str1[i] != str2[i])
            {
                return false;
            }
            i++;
        }
        return str1[i] == str2[i];
    }
};
int main()
{
    PhoneBook phoneBook;
    int choice;
    char name[100];

    do
    {
        cout << "1. add a subscriber" << endl;
        cout << "2. delete a subscriber" << endl;
        cout << "3. search for a subscriber by full name" << endl;
        cout << "4. show all subscribers" << endl;
        cout << "0. exit" << endl;
        cout << "your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            phoneBook.addContact();
            break;
        case 2:
            cout << "enter your full name to delete: ";
            cin.ignore();
            cin.getline(name, 100);
            phoneBook.removeContact(name);
            break;
        case 3:
            cout << "enter your full name to search: ";
            cin.ignore();
            cin.getline(name, 100);
            phoneBook.searchContact(name);
            break;
        case 4:
            phoneBook.showAllContacts();
            break;
        case 0:
            cout << "exit" << endl;
            break;
        default:
            cout << "wrong choice" << endl;
        }
    } while (choice != 0);

    return 0;
}