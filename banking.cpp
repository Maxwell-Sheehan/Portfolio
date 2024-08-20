#include <iostream>
#include <iomanip>
#include <vector>
#include <conio.h> // this is important for press any ket to continue.

struct MonthDetails
{
    int year;
    int month;
    double opening_balance;
    double deposited_amount;
    double total_before_interest;
    double interest;
    double closing_balance;
};

void displayMenu(double &initial_investment, double &monthly_deposit, double &annual_interest, int &years)
{
    std::cout << "Initial Investment Amount: ";
    std::cin >> initial_investment;
    std::cout << "Monthly Deposit: ";
    std::cin >> monthly_deposit;
    std::cout << "Annual Interest: ";
    std::cin >> annual_interest;
    std::cout << "Number of Years: ";
    std::cin >> years;
}

void calculateInvestment(double initial_investment, double monthly_deposit, double annual_interest, int years, std::vector<MonthDetails> &details)
{
    double opening_balance = initial_investment;
    double monthly_interest_rate = annual_interest / 100 / 12; // this is from the provided detials calculation
    int months = years * 12;

    for (int month = 1; month <= months; ++month)
    {
        double total_before_interest = opening_balance + monthly_deposit;
        double interest = total_before_interest * monthly_interest_rate;
        double closing_balance = total_before_interest + interest;

        MonthDetails detail = {years, month, opening_balance, monthly_deposit, total_before_interest, interest, closing_balance};
        details.push_back(detail);

        opening_balance = closing_balance;
    }
}

void displayResults(const std::vector<MonthDetails> &details, int years, const std::string &title)
{
    std::cout << title << std::endl;
    std::cout << "Year      Year End Balance        Year End Earned Interest" << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;

    for (int year = 1; year <= years; ++year)

    {
        double year_end_balance = details[year * 12 - 1].closing_balance;
        double year_end_interest = 0.0;

        for (int month = (year - 1) * 12; month < year * 12; ++month)
        {
            year_end_interest += details[month].interest;
        }

        std::cout << std::fixed << std::setprecision(2); // this is making sure our $ is only to two decimal places

        // this piece is primarily for aesthetics, by setting the width we make it much easier to read for the user
        std::cout << std::setw(4) << year
                  << std::setw(20) << "$" << year_end_balance
                  << std::setw(23) << "$" << year_end_interest
                  << std::endl;
    }
}

int main()
{
    double initial_investment, monthly_deposit, annual_interest;
    int years;

    displayMenu(initial_investment, monthly_deposit, annual_interest, years);

    // this is the code of the investment with monthly deposits
    std::vector<MonthDetails> investment_details_with_deposits;
    calculateInvestment(initial_investment, monthly_deposit, annual_interest, years, investment_details_with_deposits);

    // this is the code of the investment without monthly deposits
    std::vector<MonthDetails> investment_details_without_deposits;
    calculateInvestment(initial_investment, 0, annual_interest, years, investment_details_without_deposits);

    std::cout << "Press any key to continue." << std::endl;
    __getch(); // this is waiting for user to input anything, then we move on

    displayResults(investment_details_without_deposits, years, "Balance and interest without additional monthly deposits");
    std::cout << std::endl;
    displayResults(investment_details_with_deposits, years, "Balance and interest with additional monthly deposits");

    return (0);
}