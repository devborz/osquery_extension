#include "period.h"

Period Periods::parse(const std::string& period) {
    std::map<std::string, Period> periodsMap {
        {"h", LAST_HOUR},
        {"d", LAST_DAY},
        {"w", LAST_WEEK},
        {"m", LAST_MONTH},
        {"a", ALL}
    };

    return periodsMap[period];
}

std::time_t Periods::parseTime(const Period& period) {
    switch(period) {
        case LAST_HOUR : {return 3600;}
        case LAST_DAY  : {return 3600*24;}
        case LAST_WEEK : {return 3600*24*7;}
        case LAST_MONTH : {return 3600*31;}
        case ALL : {
            return std::chrono::system_clock::to_time_t(
                std::chrono::system_clock::now()
            );
        }
    }
}

bool Periods::isValidPeriod(const Period& period) {
    bool isValid = (period == LAST_HOUR) || (period == LAST_DAY)
                || (period == LAST_WEEK) || (period == LAST_MONTH)
                ||(period == ALL);

    return isValid;
}


/*std::cout << "Periods:\n" << std::setw(12)
                                        << "--period=h" << "\tlast hour\n"
                            << std::setw(12)
                                        << "--period=d" << "\tlast day\n"
                            << std::setw(12)
                                        << "--period=w" << "\tlast week\n"
                            << std::setw(12)
                                        << "--period=m" << "\tlast month\n"
                            << std::setw(12)
                                            << "--period=a" << "\tall time\n";*/
