#pragma once

#include <cctype>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

namespace StringParser {
    template<class T>
    struct item_return {
        typedef T type;
    };

    template<template<typename...> class C, typename U>

    struct item_return<C<U>> {
        typedef C<U> type;
    };

    class Exception : public std::runtime_error {
    public:
        virtual ~Exception() = default;

    protected:
        Exception(const std::string& e) : std::runtime_error(e) { }
    };

    class EmptyValueException : public Exception {
    public:
        EmptyValueException(const std::string& error) : Exception(error) { }
    };

    class FailParseException : public Exception {
    public:
        FailParseException(const std::string& error) : Exception(error) { }
    };

    template<typename T>
    typename item_return<T>::type parse(const std::string& paramValue) {
        if(paramValue.empty()) {
            throw EmptyValueException("Error. zero sized parameter");
        }

        T value;
        std::stringstream convertStream{paramValue};
        try {
            convertStream >> std::setbase(0) >> value;
            if(convertStream.fail())
                throw FailParseException("This is not a number: " + paramValue);
            return value;
        } catch(std::ios_base::failure& e) {
            auto error{std::string("Error. cannot parse parameter of type ") + typeid(T).name() + " : " + e.what()};
            throw FailParseException(error);
        }
    }

    template<template<typename...> class C, typename U>
    typename item_return<C<U>>::type parse(std::string paramValue, std::string&& delim = ";", size_t maxCount = 0) {
        std::list<std::string> digit;
        size_t pos   = 0;
        size_t count = 0;
        maxCount     = (maxCount == 0) ? std::numeric_limits<size_t>::max() : maxCount;
        while(((pos = paramValue.find(delim)) != std::string::npos) && (count < (maxCount - 1))) {
            digit.emplace_back(paramValue.substr(0, pos));
            paramValue.erase(0, pos + delim.length());
            ++count;
        }
        if(!paramValue.empty()) {
            digit.emplace_back(paramValue);
        }

        C<U> res;
        for(auto val : digit) {
            res.emplace_back(parse<U>(val));
        }
        return res;
    }

    template<>
    struct item_return<uint8_t> {
        typedef uint8_t type;
    };

    template<>
    inline uint8_t parse<uint8_t>(const std::string& paramValue) {
        if(paramValue.empty()) {
            throw EmptyValueException("Error. zero sized parameter");
        }
        uint32_t value;
        std::stringstream convertStream{paramValue};
        try {
            convertStream >> value;
            if(convertStream.fail()) {
                throw FailParseException("This is not a number: " + paramValue);
            }
            return static_cast<uint8_t>(value);
        } catch(std::ios_base::failure& e) {
            auto error{std::string("Error. cannot parse parameter of type ") + typeid(uint8_t).name() + " : "
                       + e.what()};
            std::cout << e.what() << std::endl;
            throw FailParseException(error);
        }
    }

    template<typename T>
    typename item_return<T>::type parseWithValidation(const std::string& paramValue) {
        std::stringstream convertStream;

        bool isCorrectString = true;
        bool parseDegree     = false;
        bool digitExists     = false;
        int commacnt         = 0;

        for(const char& ch : paramValue) {
            if(!isCorrectString)
                break;

            if(parseDegree) {
                // after 'e' or 'E' can be only sign and digits!
                if(std::isdigit(ch)) {
                    digitExists = true;

                    convertStream << ch;
                } else if(ch == '+' || ch == '-') {
                    if(digitExists)
                        isCorrectString = false; // in degree sign after digits, like e5-3

                    convertStream << ch;
                } else
                    isCorrectString = false;
            } else if(ch == '+' || ch == '-') { // can be only first symbol
                if(!convertStream.str().empty())
                    isCorrectString = false;
                convertStream << ch;
            } else if(ch == '.' || ch == ',') { // can be only one comma '.' or ',' in paramValue
                if(0 != commacnt++)
                    isCorrectString = false;
                convertStream << '.';
            } else if(std::isdigit(ch)) { // any digits accept
                digitExists = true;
                convertStream << ch;
            } else if((ch == 'E' || ch == 'e') && digitExists) { // for 1.313123e-17 and 1,1231e+12
                parseDegree = true;
                digitExists = false; // to check sign in a degree
                convertStream << ch;
            } else { // other any symbols is errors!
                isCorrectString = false;
            }
        }

        if(!isCorrectString) {
            throw FailParseException(paramValue + " incorrect parse to numerical (int/float) type");
        }

        T value;
        try {
            convertStream >> std::setbase(0) >> value;
            if(convertStream.fail()) {
                throw FailParseException("This is not a number: " + paramValue);
            }
            return value;
        } catch(std::ios_base::failure& e) {
            auto error{std::string("Error. cannot parse parameter of type ") + typeid(T).name() + " : " + e.what()};
            throw FailParseException(error);
        }
    }
} // namespace StringParser
