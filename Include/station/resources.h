#ifndef RESOURCES_H
#define RESOURCES_H

#include <QString>
#include <cstdint>
#include <string>

namespace Station {

enum RemoteTypes {
                  A,
                  B
};

struct ReceiveData {
    int       id;
    size_t    size;
    char*     data;
};

struct RawData {
    virtual void Fill(char* msg, size_t size) = 0;
    virtual QString GetString() const = 0;
    RemoteTypes type;
};

struct DataA : public RawData {
    std::string temperature;
    std::string pressure;

    virtual void Fill(char* msg, size_t size) {
        int check = 0;
        for (auto i = 0; i < size; ++i) {
            if (msg[i] == '_') {
                check = i;
                break;
            }

            temperature += msg[i];
        }
        for (auto i = ++check; i < size; ++i) {
            pressure += msg[i];
        }
    }

    virtual QString GetString() const {
        QString msg = "";
        msg += "Temperature = ";
        msg += QString::fromStdString(temperature);
        msg += "\nPressure = ";
        msg += QString::fromStdString(pressure);
        return msg;
    }
};

struct DataB : public RawData {
    std::string co2;

    virtual void Fill(char* msg, size_t size) {}
    virtual QString GetString() const {return "";}
};

} /* namespace Station */

#endif
