#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

constexpr int MAX_HALL_NUMBERS = 3;
constexpr int MAX_SHOW_TIME = 24;
constexpr int MAX_SEAT_PER_HALL = 10;

struct Seat
{
    std::string personName;
    int seatNumber;
};

struct ShowSession
{
    std::vector<Seat> reservedSeats;
    int movieTime;
    std::string movieName;
};

struct Hall
{
    std::vector<ShowSession> shows;
};

struct Multiplex
{
    std::vector<Hall> halls;
};


void addShow(Multiplex &multiplex, const std::string &movieName, int movieTime, int hallNumber);
void reserve(Multiplex &multiplex, int hallNumber, int movieTime, int seatNumber, const std::string &personName);
void listMovies(Multiplex &multiplex, int hallNumber);
void reportSeats(Multiplex &multiplex, int hallNumber, int movieTime);
bool sortSeanceTime(const ShowSession &a, const ShowSession &b);
bool sortSeat(const Seat &a, const Seat &b);
void makeLower(std::string &order);
void getOrders(Multiplex &multiplex);

int main()
{

    Multiplex multiplex;
    multiplex.halls.resize(3);

    getOrders(multiplex);

    return 0;
}

void addShow(Multiplex &multiplex, const std::string &movieName, int movieTime, int hallNumber)
{

    if (hallNumber <= 0 || hallNumber > MAX_HALL_NUMBERS)
    {
        std::cerr << "Error !! " << hallNumber << " is not valid\n";
        return;
    }
    else if (movieTime <= 0 || movieTime > 24)
    {
        std::cerr << "Eror !! " << movieTime << " is not valid.\n";
        return;
    }

    for (const ShowSession &existShow : multiplex.halls[hallNumber - 1].shows)
    {
        if (existShow.movieTime == movieTime)
        {
            std::cout << "A movie is already scheduled in this hall at this time\n";
            return;
        }
    }

    ShowSession newShow;
    newShow.movieName = movieName;
    newShow.movieTime = movieTime;

    multiplex.halls[hallNumber - 1].shows.emplace_back(newShow);

    std::cout << "OK\n";
}

void reserve(Multiplex &multiplex, int hallNumber, int movieTime, int seatNumber, const std::string &personName)
{

    if (movieTime <= 0 || movieTime > MAX_SHOW_TIME)
    {
        std::cerr << "Time : " << movieTime << " is not valid\n";
        return;
    }
    else if (hallNumber <= 0 || hallNumber > MAX_HALL_NUMBERS)
    {
        std::cerr << "Error " << hallNumber << " is not valid\n";
        return;
    }
    else if (seatNumber > (hallNumber * MAX_SEAT_PER_HALL) || seatNumber <= 0)
    {
        std::cerr << "Seat number : " << seatNumber << " is not valid\n";
        return;
    }

    bool showFind = false;

    for (ShowSession &foundShow : multiplex.halls[hallNumber - 1].shows)
    {
        if (foundShow.movieTime == movieTime)
        {
            showFind = true;

            for (const Seat &seatExist : foundShow.reservedSeats)
            {
                if (seatExist.seatNumber == seatNumber)
                {
                    std::cout << "This seat is already reserved\n";

                    return;
                }
            }

            Seat newSeat;
            newSeat.personName = personName;
            newSeat.seatNumber = seatNumber;

            foundShow.reservedSeats.emplace_back(newSeat);

            std::cout << "OK\n";

            return;
        }
    }

    if (!showFind)
    {
        std::cout << "No show is scheduled in this hall at the specified time\n";
        return;
    }
}

bool sortSeanceTime(const ShowSession &a, const ShowSession &b)
{
    return a.movieTime < b.movieTime;
}

void listMovies(Multiplex &multiplex, int hallNumber)
{
    if (hallNumber <= 0 || hallNumber > MAX_HALL_NUMBERS)
    {
        std::cerr << "Hall number : " << hallNumber << " is not valid\n";
        return;
    }

    std::sort(multiplex.halls[hallNumber - 1].shows.begin(),
              multiplex.halls[hallNumber - 1].shows.end(), sortSeanceTime);

    if (multiplex.halls[hallNumber - 1].shows.empty())
    {
        std::cout << "No movie found\n";
        return;
    }

    for (const ShowSession &show : multiplex.halls[hallNumber - 1].shows)
    {
        int availableSeats = (hallNumber * MAX_SEAT_PER_HALL) - show.reservedSeats.size();

        std::cout << show.movieName << " at " << show.movieTime << ":00: "
                  << availableSeats << " seats available\n";
    }
}

bool sortSeat(const Seat &a, const Seat &b)
{
    return a.seatNumber < b.seatNumber;
}

void reportSeats(Multiplex &multiplex, int hallNumber, int movieTime)
{
    if (hallNumber <= 0 || hallNumber > MAX_HALL_NUMBERS)
    {
        std::cerr << "Hall number : " << hallNumber << " is not valid";
        return;
    }
    else if (movieTime <= 0 || movieTime > MAX_SHOW_TIME)
    {
        std::cerr << "Movie time : " << movieTime << " is not valid";
        return;
    }

    bool findShow = false;
    for (ShowSession &show : multiplex.halls[hallNumber - 1].shows)
    {
        if (show.movieTime == movieTime)
        {
            findShow = true;

            std::sort(show.reservedSeats.begin(), show.reservedSeats.end(),
                      sortSeat);

            if (show.reservedSeats.empty())
            {
                std::cout << "All seats are available\n";
                return;
            }

            for (const Seat &seat : show.reservedSeats)
            {
                std::cout << "Seat " << seat.seatNumber << " is reserved by " << seat.personName
                          << std::endl;
            }
            return;
        }
    }

    if (!findShow)
    {
        std::cout << "No show is scheduled in this hall at the specified time\n";
    }
}

void makeLower(std::string &order)
{
    std::transform(order.begin(), order.end(), order.begin(), [](unsigned char A)
                   { return std::tolower(A); });
}

void getOrders(Multiplex &multiplex)
{
    std::string command;

    while (std::cin >> command)
    {
        makeLower(command);

        if (command == "add_show")
        {
            std::string movieName;
            int movieTime, hallNumber;
            std::cin >> movieName >> movieTime >> hallNumber;

            addShow(multiplex, movieName, movieTime, hallNumber);
        }
        else if (command == "reserve")
        {

            int hallNumber, movieTime, seatNumber;
            std::string personName;

            std::cin >> hallNumber >> movieTime >> seatNumber >> personName;

            reserve(multiplex, hallNumber, movieTime, seatNumber, personName);
        }
        else if (command == "list_movies")
        {
            int hallNumber;

            std::cin >> hallNumber;

            listMovies(multiplex, hallNumber);
        }
        else if (command == "report_seats")
        {
            int hallNumber, movieTime;

            std::cin >> hallNumber >> movieTime;

            reportSeats(multiplex, hallNumber, movieTime);
        }
        else if (command == "quit")
        {
            break;
        }
    }
}

