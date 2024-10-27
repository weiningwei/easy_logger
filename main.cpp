#include "easy_logger.h"

int main()
{
    logger::LOGGER::get_instance().set_log_level(logger::DEBUG);
    logger::LOGGER::get_instance().set_log_file("log.txt");
    logger::LOGGER::get_instance().log(logger::INFO, "This is an info message.");
    logger::LOGGER::get_instance().log(logger::DEBUG, "This is a debug message.");
    logger::LOGGER::get_instance().log(logger::ERROR, "This is an error message.");
    return 0;
}