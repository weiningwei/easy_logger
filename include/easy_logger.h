#ifndef _EASY_LOGGER_H
#define _EASY_LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>

namespace LOGGER
{

    enum logger_level
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    class Logger
    {
    public:
        static Logger &get_instance()
        {
            static Logger _instance;
            return _instance;
        }

        void set_log_level(const logger_level &level)
        {
            _level = level;
        }
        void log()
        {
            
        }

    private:
        Logger() : _level{INFO} {}
        logger_level _level;
        std::mutex _mtx;

        //
    }

}

#endif