/**
 * @file main.cpp
 * @author weiningwei (weiningwei09@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-10-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "easy_logger.h"


void test_funtion(int a, int b)
{

}


int main()
{
    logger::LOGGER::get_instance().set_log_level(logger::DEBUG);
    logger::LOGGER::get_instance().set_log_file("log.txt");
    logger::LOGGER::get_instance().log(logger::INFO, "This is an info message.");
    logger::LOGGER::get_instance().log(logger::DEBUG, "This is a debug message.");
    logger::LOGGER::get_instance().log(logger::ERROR, "This is an error message.");
    return 0;
}