#include "JsonSaver.h"

void JsonSaver::saveBashHistory(std::vector<ExecutedCommand>& history) {

    std::string home = getenv("HOME");

    std::ofstream out(home + "/bash_history.json", std::ofstream::out |
                      std::ofstream::trunc);

    if (out.is_open()) {
        nlohmann::json commands = nlohmann::json::array();

        unsigned int start = 0;
        if (history.size() >= 20) {
            start = history.size() - 20;
        }
        for (unsigned int i = start; i < history.size(); i++) {
            std::time_t t = history[i].getTime();

            std::string time = std::asctime(std::localtime(&t));

            time = time.substr(0, time.length() - 1);
            nlohmann::json obj = nlohmann::json::object ({
                {"time", time},
                {"path", history[i].getPath().string()},
                {"command", history[i].getCommand()}
            });
            commands.push_back(obj);
        }

        out << std::setw(4) << commands;

        out.close();
    }
    else {
        throw std::logic_error("File ~/bash_history.json was not found");
    }
}

void JsonSaver::saveFilesystemsHistory(std::vector<ChangedFile>& history) {

    std::string home = getenv("HOME");

    std::ofstream out(home + "/fs_history.json", std::ofstream::out |
                      std::ofstream::trunc);

    if (out.is_open()) {
        nlohmann::json files = nlohmann::json::array();

        unsigned int start = 0;
        if (history.size() >= 20) {
            start =  history.size() - 20;
        }
        for (unsigned int i = start; i < history.size(); i++) {
            std::time_t t = history[i].getTime();

            std::string time = std::asctime(std::localtime(&t));

            time = time.substr(0, time.length() - 1);

            nlohmann::json obj = nlohmann::json::object({
              {"time", time},
              {"path", history[i].getPath().string()},
              {"filename", history[i].getFileName()}
            });

            files.push_back(obj);
        }

        out << std::setw(4) << files;

        out.close();
    }
    else {
        throw std::logic_error("File ~/fs_history.json was not found");
    }
}
