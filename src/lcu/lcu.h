#pragma once
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <array>
#include <cstdio>
#include <iostream>
#include <memory>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>
#include "../logger/log.h"
#include "httplib.h"
#include "json.h"
#include "rune_page.h"

#define CPPHTTPLIB_OPENSSL_SUPPORT
class RunePage;
class Lcu {
public:
    Lcu();
    ~Lcu();
    std::string exec(const char* cmd);
    bool setRune(int id);
    bool addRunePage();
    bool delRunePage();
    void DelSavePage(int id);
    bool saveRunnePage();
    void SaveToFile();
    void LoadFile();
    std::vector<RunePage> GetSavePages();

private:
    std::vector<RunePage> m_RunePages;
    Logger m_logger;
    std::string m_token;
    std::string m_port;
    std::unique_ptr<httplib::Client> m_lolClient;
    const std::string s_currentPage = "/lol-perks/v1/currentpage";
    const std::string s_page = "/lol-perks/v1/pages";
};