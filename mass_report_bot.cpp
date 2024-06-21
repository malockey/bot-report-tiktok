#include <iostream>
#include <curl/curl.h>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <fstream>

std::string proxiesURLf() {
    std::string proxyFile = "proxies.txt";
    std::ifstream file(proxyFile);
    int index;

    if (file.is_open()) {
        std::string proxy;
        int currentIndex = 0;
        std::srand(std::time(nullptr));
        index = std::rand() % 162;
        while (std::getline(file, proxy) && currentIndex < index+1) {
            currentIndex++;
        }
        file.close();
        if (currentIndex == index) {
            return proxy;
        } else {
            return "Line not found.";
        }
    } else {
        return "Error opening file.";
    }
}

size_t writeCallback(char* data, size_t size, size_t nmemb, std::string* response) { // function of the callback
    size_t totalSize = size * nmemb;
    response->append(data, totalSize);
    return totalSize;
}

bool validURL(std::string reportURL) {
    std::string validURL = "https://www.tiktok.com/aweme/v2/aweme/feedback";
    if (reportURL.compare(0, validURL.length(), validURL) == 0) 
        return true;
    else {
        std::cout << "Incorrect URL..";
        return false;
    }
}

std::string searchStrings(std::string response, std::string search) {
    std::string result;

    size_t found = response.find(search);
    if (found != std::string::npos) {
        size_t startPos = found + search.length() + 3; // jump '=:"'
        size_t endPos = response.find('"', startPos);
        if (endPos != std::string::npos) 
            result = response.substr(startPos, endPos - startPos);
        else 
            result = response.substr(startPos);
    }
    return result;
}

std::string timeSystem() {
    std::time_t currentTime = std::time(nullptr);
    std::tm* localtime_r = std::localtime(&currentTime);

    int hour = localtime_r->tm_hour;
    int minute = localtime_r->tm_min; 
    int second = localtime_r->tm_sec;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hour << ":" << std::setw(2) << minute << ":" << std::setw(2) << second;
    
    return oss.str();
}

void printCentered(const std::string& text, int width) {
    int textWidth = static_cast<int>(text.length());
    if (textWidth >= width) {
        std::cout << text;
    } else {
        int padding = (width - textWidth) / 2;
        std::cout << std::setw(padding + textWidth) << std::setfill(' ') << text;
    }
}

void clearConsole() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

int badRequest = 0;
std::string reportUser(std::string& reportURL, const std::string& proxyUrl = "") {
    std::string result;

    if (badRequest == 10) {
        std::cout << "\nToo many bad requests, do you want to continue? Y/N" << std::endl;
        char choice;
        std::cin >> choice;

        if (choice == 'N' || choice == 'n') {
            return result = "no more requests";
        } else if (choice == 'Y' || choice == 'y') {
            badRequest = 0;
        } else {
            std::cout << "\ninvalid choice" << std::endl;
        }
    }

    if (validURL(reportURL)) {
        std::string response;
        CURLcode res;
        CURL* curl = curl_easy_init();

        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, reportURL.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

            if (!proxyUrl.empty()) {
                curl_easy_setopt(curl, CURLOPT_PROXY, proxyUrl.c_str());
            }

            res = curl_easy_perform(curl);
            

            if (res == CURLE_OK) {
                result += timeSystem() + " " + searchStrings(response, "logid") + " " + searchStrings(response, "status_message");
            }

            if (res != CURLE_OK || response == "" || response == "null") {
                result = "bad request";
                badRequest++;
            }


            curl_easy_cleanup(curl);
        }
    }
    std::cout << std::endl;
    printCentered(result, 80);
    return result;
}

int main() {
    std::string reportURL, proxyURL = proxiesURLf();
    std::cout << "Proxy: " << proxyURL << std::endl;
    std::cout << "Enter the URL: ";
    std::cin >> reportURL;
    clearConsole();
    
    do {
        reportUser(reportURL);
    } while (reportUser(reportURL) != "no more requests");
    
    return 0;
}