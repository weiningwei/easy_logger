#ifndef _EASY_LOGGER_H
#define _EASY_LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>

#include <thread>
#include <queue>
#include <condition_variable>

namespace logger
{

    enum LOGGER_LEVEL
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    class LOGGER
    {
    public:
        static LOGGER &get_instance()
        {
            static LOGGER _instance;
            return _instance;
        }

        void set_log_level(const LOGGER_LEVEL &level)
        {
            _level = level;
        }

        void set_log_file(const std::string &file_name)
        {
            _file_stream.open(file_name, std::ios::app);
        }

        void log(const LOGGER_LEVEL &level, const std::string &message)
        {
            if (level < _level)
            {
                return;
            }
            std::lock_guard<std::mutex> lock(_mtx);
            std::ostream &output = (level >= WARNING) ? std::cerr : std::cout;

            log_message(output, level, message);

            if (_file_stream.is_open())
            {
                log_message(_file_stream, level, message);
            }

            return;
        }

    private:
        LOGGER() : _level{INFO} {}
        ~LOGGER()
        {
            if (_file_stream.is_open())
            {
                _file_stream.close();
            }
        }
        LOGGER_LEVEL _level;
        std::mutex _mtx;

        std::ofstream _file_stream;
        //
        LOGGER(const LOGGER &) = delete;
        LOGGER &operator=(const LOGGER &) = delete;

        void log_message(std::ostream &stream, const LOGGER_LEVEL &level,
                         const std::string &message)
        {
            switch (level)
            {
            case DEBUG:
                stream << "DEBUG: ";
                break;
            case INFO:
                stream << "INFO: ";
                break;
            case WARNING:
                stream << "WARNING: ";
                break;
            case ERROR:
                stream << "ERROR: ";
            default:
                break;
            }
            stream << message << "\n";
        }
    };

    class ASYNC_LOGGER
    {
    public:
        ASYNC_LOGGER() : _stop_log(false)
        {
            _log_thread = std::thread(&ASYNC_LOGGER::process_log, this);
        }
        ~ASYNC_LOGGER()
        {
            {
                std::lock_guard<std::mutex> lock(_mtx);
                _stop_log = true;
            }
            _cond_var.notify_all();
            _log_thread.join();
        }

    private:
        std::queue<std::string> _log_queue;
        std::mutex _mtx;
        std::condition_variable _cond_var;
        std::thread _log_thread;

        bool _stop_log;

        void process_log()
        {
            std::ofstream log_file("log_async.txt");
            while (true)
            {
                std::unique_lock<std::mutex> lock(_mtx);
                _cond_var.wait(lock, [this]
                        { return !_log_queue.empty() || _stop_log; });

                while (!_log_queue.empty())
                {
                    log_file << _log_queue.front() << std::endl;
                    _log_queue.pop();
                }

                if (_stop_log && _log_queue.empty())
                    break;
            }
        }
    };
}

#endif