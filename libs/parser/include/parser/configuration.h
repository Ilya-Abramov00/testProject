//
// Created by gts on 07.06.2024.
//
#pragma once

#include "stringparser.h"

#include <cstdint>
#include <iostream>
#include <map>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

class Configuration {
public:
    Configuration(const std::map<std::string, std::string>& conf) : conf(conf) { }

    ~Configuration() { }

    inline bool checkProperty(const std::string& key) const {
        auto it = conf.find(key);
        if(it != conf.cend()) {
            return true;
        } else {
            return false;
        }
    }

    template<typename T>
    T getProperty(const std::string& key) const {
        auto it = conf.find(key);
        if(it != conf.cend()) {
            try {
                return StringParser::parse<T>(it->second);
            } catch(const StringParser::EmptyValueException& e) {
                throw StringParser::EmptyValueException(key + ": " + e.what());
            } catch(const StringParser::FailParseException& e) {
                throw StringParser::FailParseException(key + ": " + e.what());
            }
        }
        throw NotFoundException(key);
    }

    template<typename T>
    std::optional<T> tryGetProperty(const std::string& key) const {
        auto it = conf.find(key);
        if(it != conf.end()) {
            try {
                return StringParser::parse<T>(it->second);
            } catch(StringParser::EmptyValueException&) {
                return std::nullopt;
            } catch(const StringParser::FailParseException& e) {
                throw StringParser::FailParseException(key + ": " + e.what());
            }
        }
        return std::nullopt;
    }

    template<typename T>
    bool tryGetProperty(const std::string& key, T& result) const {
        auto value = tryGetProperty<T>(key);
        if(value) {
            result = *value;
            return true;
        }
        return false;
    }

    template<typename T>
    inline std::vector<T> getPropertyList(const std::string& key) const {
        bool ret = checkProperty(key);
        if(ret) {
            try {
                return StringParser::parse<std::vector, T>(conf[key]);
            } catch(const StringParser::EmptyValueException&) {
                return {};
            } catch(const StringParser::FailParseException& e) {
                throw StringParser::FailParseException(key + ": " + e.what());
            }
        } else {
            throw NotFoundException(key);
            return {};
        }
    }

    template<typename T>
    inline std::vector<T> tryGetPropertyList(const std::string& key) const {
        if(!checkProperty(key)) {
            return {};
        }
        try {
            return StringParser::parse<std::vector, T>(conf[key]);
        } catch(const StringParser::EmptyValueException&) {
            return {};
        } catch(const StringParser::FailParseException& e) {
            throw StringParser::FailParseException(key + ": " + e.what());
        }
    }

private:
    mutable std::map<std::string, std::string> conf;
};
