#include <iostream>
#include <cstring>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <ctime>

struct Event
{
    char name[100];
    tm startDate;
    tm endDate;
};

int readFile(Event events[100], int n)
{
    Event e;
    std::ifstream file;

    file.open("events.bin", std::ios::in | std::ios::binary);

    if (!file.is_open())
    {
        return 0;
    }

    while (file.read(reinterpret_cast<char*>(&e), sizeof(Event)))
    {
        events[n] = e;
        n++;
    }

    file.close();
    return n;
}

tm getDate(int d, int m, int y)
{
    std::tm timeIn = { 0, 0, 0, // second, minute, hour
      d, m - 1, y - 1900 }; // 1-based day, 0-based month, year since 1900
    std::time_t timeTemp = std::mktime(&timeIn);
    std::tm* timeOut = std::localtime(&timeTemp);
    return *timeOut;
}

void printCalendar(Event events[], int numEvents)
{
    //Enter month and year in format MM/YYYY from the input by the user
    char input[100];
    std::cout << "Enter month and year in format MM/YYYY: ";
    std::cin.getline(input, sizeof(input));

    int month = 4, year = 2023;
    sscanf(input, "%d/%d", &month, &year);

    // Get the name of the month
    char monthName[100];
    tm date = getDate(1, month, year);
    strftime(monthName, 100, "%B", &date);

    // Print the month and year
    std::cout << monthName << " " << year << std::endl;

    // Print a line of dashes
    std::cout << std::setw(10) << std::setfill('-') << "" << std::endl;
    std::cout << std::setfill(' ');
}

int main()
{
    int n = 0;
    Event events[100];
    n = readFile(events, n);

    //current date/time based on current system
    time_t now = time(0);
    tm* localTime = localtime(&now);
    char buffer[200];
    strftime(buffer, 100, " %A, %d %B %Y", localTime);
    std::cout << "Welcome! Today is: " << buffer << std::endl;
    std::cout << "You have " << n << " events." << std::endl;

    int c = 0;

    while (c != 7)
    {
        std::cout << "[01] Show calendar" << std::endl;
        std::cout << "[02] Show schedule" << std::endl;

        std::cout << "[03] List Events" << std::endl;
        std::cout << "[04] Add event" << std::endl;
        std::cout << "[05] Remove event" << std::endl;
        std::cout << "[06] Set first weekday" << std::endl;

        std::cout << "[07] Exit" << std::endl;
        std::cout << "Enter [1-7]: ";

        std::cin >> c; getchar();

        switch (c)
        {
        case 1:
            printCalendar(events, n);
            break;
        }
    }

}

