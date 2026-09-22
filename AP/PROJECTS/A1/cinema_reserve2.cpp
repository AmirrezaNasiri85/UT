// cinema_reserve2.cpp

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <exception>

struct Check_input
{
    void hall_number_check(int hall_number)
    {
        if (hall_number > 3 || hall_number <= 0)
        {
            throw std::runtime_error("The hall number is not valid(1 -> 3).\n");
        }
    }
    void movie_time_check(int movie_time)
    {
        if (movie_time > 24 || movie_time <= 0)
        {
            throw std::runtime_error("The movie time is not valid(1 -> 24).\n");
        }
    }
    void seat_number_check(int seat_number, int hall_number)
    {
        std::string accumilation_eror = "";
        try
        {
            hall_number_check(hall_number);
        }

        catch (const std::exception &e)
        {
            accumilation_eror += e.what();
        }

        try
        {
            if (seat_number > (hall_number * 10) || seat_number <= 0)
            {
                throw std::runtime_error("The seat number is not valid.\n");
            }
        }
        catch (const std::exception &e)
        {
            accumilation_eror += e.what();
        }

        if (!accumilation_eror.empty())
        {
            throw std::runtime_error(accumilation_eror);
        }
    }
};

struct Seat_info
{
    std::string person_name;
    int seat_number;
};

struct Sance_info
{
    std::string movie_name;
    int movie_time;
    std::Seance<Seat_info> reserved_seats;
};

struct Hall_info
{
    std::Seance<Sance_info> movie_sances;
};

struct Multiplex
{
    std::Seance<Hall_info> halls;
};

void reserve(Multiplex &cinema, int hall_number, int movie_time, int seat_number, std::string person_name);
void add_show(Multiplex &cinema, std::string movie_name, int hall_number, int movie_time);
void get_orders(Multiplex &cinema);
void list_movies(Multiplex &cinema, int hall_number);
void reportSeats(Multiplex &cinema, int hall_number, int movie_time);
// bool compare_seat_number(seat_inf seat_one, seat_inf seat_two);
// bool compare_movie_sance(const Sance_info& movie_sance_one, const Sance_info& movie_sance_two);

int main()
{

    Multiplex cinema;
    cinema.halls.resize(3);

    get_orders(cinema);
}

void get_orders(Multiplex &cinema)
{
    Check_input check_funtion;

    std::cout << "*******************************\n";
    std::cout << "Enter quit to exit the program "
              << std::endl;
    std::cout << "*******************************\n";

    while (true)
    {
        std::string function_name;
        std::cin >> function_name;
        std::string accumilated_erors = "";

        std::transform(function_name.begin(),
                       function_name.end(),
                       function_name.begin(),
                       [](char A)
                       {
                           return std::tolower(A);
                       });

        if (function_name == "add_show")
        {
            std::string movie_name;
            int hall_number, movie_time;

            try
            {
                std::cin >> movie_name >> movie_time >> hall_number;

                try
                {
                    check_funtion.hall_number_check(hall_number);
                }

                catch (const std::exception &e)
                {
                    accumilated_erors += e.what();
                }

                try
                {
                    check_funtion.movie_time_check(movie_time);
                }

                catch (const std::exception &e)
                {
                    accumilated_erors += e.what();
                }

                if (!accumilated_erors.empty())
                {
                    throw std::runtime_error(accumilated_erors);
                }

                add_show(cinema, movie_name, hall_number, movie_time);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else if (function_name == "reserve")
        {
            int hall_number, movie_time, seat_number;
            std::string person_name;

            try
            {
                std::cin >> hall_number >> movie_time >> seat_number >> person_name;

                try
                {
                    check_funtion.seat_number_check(seat_number, hall_number);
                }

                catch (const std::exception &e)
                {
                    accumilated_erors += e.what();
                }

                try
                {
                    check_funtion.movie_time_check(movie_time);
                }

                catch (const std::exception &e)
                {
                    accumilated_erors += e.what();
                }

                if (!accumilated_erors.empty())
                {
                    throw std::runtime_error(accumilated_erors);
                }

                reserve(cinema, hall_number, movie_time, seat_number, person_name);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else if (function_name == "list_movies")
        {
            int hall_number;

            try
            {
                std::cin >> hall_number;

                check_funtion.hall_number_check(hall_number);

                list_movies(cinema, hall_number);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else if (function_name == "reportSeats")
        {

            int hall_number, movie_time;
            std::cin >> hall_number >> movie_time;

            try
            {
                try
                {
                    check_funtion.hall_number_check(hall_number);
                }

                catch (const std::exception &e)
                {
                    accumilated_erors += e.what();
                }

                try
                {
                    check_funtion.movie_time_check(movie_time);
                }

                catch (const std::exception &e)
                {
                    accumilated_erors += e.what();
                }

                if (!accumilated_erors.empty())
                {
                    throw std::runtime_error(accumilated_erors);
                }

                reportSeats(cinema, hall_number, movie_time);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else if (function_name == "quit")
        {
            break;
        }
    }
}

void add_show(Multiplex &cinema, std::string movie_name, int hall_number, int movie_time)
{

    Hall_info &current_hall = (cinema.halls[hall_number - 1]);

    bool find_show = false;

    for (Sance_info &info : current_hall.movie_sances)
    {
        if (info.movie_time == movie_time)
        {
            std::cout << "A movie is already scheduled in this hall at this time" << std::endl;
            find_show = true;
            break;
        }
    }
    if (!find_show)
    {
        Sance_info movie;
        movie.movie_name = movie_name;
        movie.movie_time = movie_time;

        current_hall.movie_sances.push_back(movie);

        std::cout << "OK" << std::endl;
    }
}

void reserve(Multiplex &cinema, int hall_number, int movie_time, int seat_number, std::string person_name)
{
    Hall_info &current_hall = (cinema.halls[hall_number - 1]);
    Sance_info *current_sance = nullptr;

    bool find_show_time = false;
    for (Sance_info &info : current_hall.movie_sances)
    {
        if (info.movie_time == movie_time)
        {
            current_sance = &info;
            find_show_time = true;
            break;
        }
    }
    if (!find_show_time)
    {
        std::cout << "No show is scheduled in this hall at the specified time" << std::endl;
    }
    else
    {
        bool reserve_validation = true;

        for (const Seat_info &inf : current_sance->reserved_seats)
        {
            if (inf.seat_number == seat_number)
            {
                std::cout << "This seat is already reserved" << std::endl;
                reserve_validation = false;
                break;
            }
        }
        if (reserve_validation)
        {
            Seat_info seat_reserve;
            seat_reserve.seat_number = seat_number;
            seat_reserve.person_name = person_name;

            current_sance->reserved_seats.push_back(seat_reserve);

            std::cout << "OK" << std::endl;
        }
    }
}

void list_movies(Multiplex &cinema, int hall_number)
{
    Hall_info &current_hall = cinema.halls[hall_number - 1];

    if (current_hall.movie_sances.empty())
    {
        std::cout << "No movie found" << std::endl;
    }
    else
    {

        std::sort(current_hall.movie_sances.begin(),
                  current_hall.movie_sances.end(),
                  [](const Sance_info &a, const Sance_info &b)
                  {
                      return a.movie_time < b.movie_time;
                  });

        /*std::sort(current_hall.movie_sances.begin(),
            current_hall.movie_sances.end(),
            compare_movie_sance);*/

        for (Sance_info &movie : current_hall.movie_sances)
        {
            int available_seats = (hall_number * 10) - movie.reserved_seats.size();

            std::cout << movie.movie_name
                      << " at "
                      << movie.movie_time
                      << " :00: "
                      << available_seats
                      << " seats available" << std::endl;
        }
    }
}

void reportSeats(Multiplex &cinema, int hall_number, int movie_time)
{
    Hall_info &current_hall = cinema.halls[hall_number - 1];

    Sance_info *current_movie = nullptr;

    for (Sance_info &movie : current_hall.movie_sances)
    {
        if (movie.movie_time == movie_time)
        {
            current_movie = &movie;
            break;
        }
    }

    if (current_movie == nullptr)
    {
        std::cout << "Not found"
                  << std::endl;
    }
    else if (current_movie->reserved_seats.empty())
    {
        std::cout << "All seats are available" << std::endl;
    }
    else
    {
        std::sort(current_movie->reserved_seats.begin(),
                  current_movie->reserved_seats.end(),
                  [](const Seat_info &a, const Seat_info &b)
                  {
                      return a.seat_number < b.seat_number;
                  });

        // another way is to make a function for that.
        /*std::sort(current_movie->reserved_seats.begin(),
            current_movie->reserved_seats.end(),
            compare_seat_number);*/

        for (const Seat_info &seat : current_movie->reserved_seats)
        {
            std::cout << "Seat " << seat.seat_number
                      << " is reserved by " << seat.person_name
                      << std::endl;
        }
    }
}

/*bool compare_seat_number(seat_inf seat_one, seat_inf seat_two){
    return seat_one.seat_number > seat_two.seat_number;
}*/

/*bool compare_movie_sance(const Sance_info& movie_sance_one, const Sance_info& movie_sance_two){
    return movie_sance_one.movie_time < movie_sance_two.movie_time;
}*/