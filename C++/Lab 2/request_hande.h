#include "nlohmann/json.hpp"
#include <curl/curl.h>
#include <iostream>
#include <unistd.h>
#include <conio.h>

#pragma once

class Request_handle {
private:
    std::string buffer;
    nlohmann::json response;
    static size_t write_callback(void * data, size_t current_size, size_t memory_amount, void * buffer_str) {
        size_t number_of_copies = current_size * memory_amount;
        ((std::string *) buffer_str) -> append((char *) data, number_of_copies);
        size_t new_size = current_size * memory_amount;
        return new_size;
    }

    void get_json_response() {
        using namespace nlohmann;
        CURL * cbr_exchange_rate = curl_easy_init();
        if (cbr_exchange_rate) {
            curl_easy_setopt(cbr_exchange_rate, CURLOPT_URL, "http://www.cbr-xml-daily.ru/daily_json.js");
            curl_easy_setopt(cbr_exchange_rate, CURLOPT_SSL_VERIFYPEER, 0); // если используем протокол https;
            curl_easy_setopt(cbr_exchange_rate, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(cbr_exchange_rate, CURLOPT_WRITEDATA, &buffer);
            CURLcode result = curl_easy_perform(cbr_exchange_rate);
            if (result != CURLE_OK) {
                std::cout << "Error :: curl_easy_perform() failed." << std::endl;
                exit(0);
            }

            curl_easy_cleanup(cbr_exchange_rate);
        }

        response = json::parse(buffer);
    }

public:
    Request_handle() = default;

    Request_handle(const Request_handle &other) { buffer = other.buffer; response = other.response; }

    void get_statistics() {
        using namespace std;
        get_json_response();
        vector<string> currencies;
        map<string, vector<double>> currency_value;
        for (nlohmann::json::iterator currency = response["Valute"].begin(); currency != response["Valute"].end(); ++currency) {
            currencies.push_back(currency.value()["CharCode"]);
            currency_value[currency.value()["CharCode"]];
        }

        while(!kbhit()) {
            cout << "Код" << " | " << "Название" << ", " << "номинал" << ", " << "текущий курс:" << endl;
            for (auto &i: currencies) {
                double value = response["Valute"][i]["Value"];
                int nominal_value = response["Valute"][i]["Nominal"];
                string name = response["Valute"][i]["Name"];
                cout << i << " | " << name << ", " << nominal_value << ", " << value << " " << "руб." << endl;
                currency_value[i].push_back(value);
            }

            cout << endl;
            sleep(10);
        }

        cout << "Код" << " | " << "Название" << ", " << "медиана" << ", " << "среднее значение:" << endl;
        for (auto &i: currencies) {
            double summary = 0, average = 0, median = 0;
            sort(currency_value[i].begin(), currency_value[i].end());
            for (auto &j: currency_value[i]) {
                summary += j;
            }

            size_t cur_size = currency_value[i].size();
            average = (summary) / (double) cur_size;
            median = currency_value[i][(int) (cur_size / 2)];
            string name = response["Valute"][i]["Name"];
            cout << i << " | " << name << ", " << median << " " << "руб. " << ", " << average << " " << "руб." << endl;
        }
    }

    ~Request_handle() = default;
};
