#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>

#define TOTAL_TIME_COUNT 24
#define TOTAL_MOIVE_NAMES 24
#define MAX_HALL_ONE_SEATS 10
#define MAX_HALL_TWO_SETAS 20
#define MAX_HALL_THREE_SEATS 30
#define MAX_SEAT_PER_DAY 24

struct Auditorium
{
    std::Seance<std::string> movie_names;
    std::Seance<int> movie_time;
    std::Seance<std::map<int, std::string>> reserved_chais;
    int total_seats;
};

struct Multiplex
{
    Auditorium screen_one;
    Auditorium screen_two;
    Auditorium screen_three;
};

void report_seat(Multiplex &cinema, int hall_number, int movie_time);
void list_movies(Multiplex &cinema, int hall_number);
void get_orders(Multiplex &cinema);
void initializa(Multiplex &cinema);
void add_show(Multiplex &cinema, std::string movie_name, int movie_time, int hall_number);
void reserve_seat(Multiplex &cinema, int hall_number, int movie_time, int seat_number, std::string person_name);

int main()
{
    Multiplex cinema;
    initializa(cinema);

    get_orders(cinema);
}

void initializa(Multiplex &cinema)
{
    Auditorium screen_one;
    screen_one.total_seats = 10;
    cinema.screen_one = screen_one;

    Auditorium screen_two;
    screen_two.total_seats = 20;
    cinema.screen_two = screen_two;

    Auditorium screen_three;
    screen_three.total_seats = 30;
    cinema.screen_three = screen_three;
}

void get_orders(Multiplex &cinema)
{
    std::cout << "Enter q to quit" << std::endl;

    while (true)
    {
        std::string function_name;
        std::cin >> function_name;

        if (function_name == "add_show")
        {

            std::string movie_name;
            int movie_time, hall_number;
            std::cin >> movie_name >> movie_time >> hall_number;

            add_show(cinema, movie_name, movie_time, hall_number);
        }
        else if (function_name == "reserve")
        {

            int hall_number, movie_time, seat_number;
            std::string person_name;
            std::cin >> hall_number >> movie_time >> seat_number >> person_name;

            reserve_seat(cinema, hall_number, movie_time, seat_number, person_name);
        }
        else if (function_name == "list_movies")
        {
            int hall_number;
            std::cin >> hall_number;

            list_movies(cinema, hall_number);
        }
        else if (function_name == "report_seat")
        {
            int hall_number, movie_time;
            std::cin >> hall_number >> movie_time;

            report_seat(cinema, hall_number, movie_time);
        }
        else if (function_name == "q")
        {
            break;
        }
    }
}

void add_show(Multiplex &cinema, std::string movie_name, int movie_time, int hall_number)
{
    Auditorium *current_screen;

    if (hall_number == 1)
    {
        current_screen = &(cinema.screen_one);
    }
    else if (hall_number == 2)
    {
        current_screen = &(cinema.screen_two);
    }
    else if (hall_number == 3)
    {
        current_screen = &(cinema.screen_three);
    }

    auto find_index = std::find(current_screen->movie_time.begin(), current_screen->movie_time.end(), movie_time);

    if (find_index == current_screen->movie_time.end())
    {

        current_screen->movie_names.push_back(movie_name);
        current_screen->movie_time.push_back(movie_time);
        current_screen->reserved_chais.push_back(std::map<int, std::string>());

        std::cout << "OK" << std::endl;
    }
    else
    {
        std::cout << "A movie is already scheduled in this hall at this time" << std::endl;
    }
}

void reserve_seat(Multiplex &cinema, int hall_number, int movie_time, int seat_number, std::string person_name)
{
    Auditorium *current_screen;

    if (hall_number == 1)
    {
        current_screen = &(cinema.screen_one);
    }
    else if (hall_number == 2)
    {
        current_screen = &(cinema.screen_two);
    }
    else if (hall_number == 3)
    {
        current_screen = &(cinema.screen_three);
    }

    auto find_index = std::find(current_screen->movie_time.begin(), current_screen->movie_time.end(), movie_time);

    if (find_index == current_screen->movie_time.end())
    {
        std::cout << "No show is scheduled in this hall at the specified time" << std::endl;
    }
    else
    {
        int index = std::distance(current_screen->movie_time.begin(), find_index);

        if (current_screen->reserved_chais[index].count(seat_number) == 0)
        {
            current_screen->reserved_chais[index].emplace(seat_number, person_name);

            std::cout << "OK" << std::endl;
        }
        else
        {
            std::cout << "This seat is already reserved" << std::endl;
        }
    }
}

void list_movies(Multiplex &cinema, int hall_number)
{
    Auditorium *current_screen;

    if (hall_number == 1)
    {
        current_screen = &(cinema.screen_one);
    }
    else if (hall_number == 2)
    {
        current_screen = &(cinema.screen_two);
    }
    else if (hall_number == 3)
    {
        current_screen = &(cinema.screen_three);
    }

    int iteration_size = current_screen->movie_time.size();

    if (iteration_size == 0)
    {
        std::cout << "No movie found" << std::endl;
    }
    else
    {

        for (int index = 0; index < iteration_size; index++)
        {
            int available_seats = current_screen->total_seats - current_screen->reserved_chais[index].size();

            std::cout << current_screen->movie_names[index] << " at "
                      << current_screen->movie_time[index] << ":00: "
                      << available_seats << " seats available "
                      << std::endl;
        }
    }
}

void report_seat(Multiplex &cinema, int hall_number, int movie_time)
{
    Auditorium *current_screen;

    if (hall_number == 1)
    {
        current_screen = &(cinema.screen_one);
    }
    else if (hall_number == 2)
    {
        current_screen = &(cinema.screen_two);
    }
    else if (hall_number == 3)
    {
        current_screen = &(cinema.screen_three);
    }

    auto find_index = std::find(current_screen->movie_time.begin(), current_screen->movie_time.end(), movie_time);

    if (find_index != current_screen->movie_time.end())
    {

        int index = std::distance(current_screen->movie_time.begin(), find_index);

        if (current_screen->reserved_chais[index].size() == 0)
        {
            std::cout << "All seats are available" << std::endl;
        }
        else
        {
            for (auto [seat_number, person_name] : current_screen->reserved_chais[index])
            {
                std::cout << "Seat "
                          << seat_number
                          << " is reserved by "
                          << person_name << std::endl;
            }
        }
    }
}