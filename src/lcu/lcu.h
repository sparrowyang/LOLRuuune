#pragma once
#include <array>
#include <cstdio>
#include <iostream>
#include <map>
#include <memory>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>
#include "../logger/log.h"
#include "httplib.h"
#include "json.h"
#include "rune_page.h"
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
    bool CheckConnect();
    std::vector<RunePage> GetSavePages();
    void SetToken(const std::string& raw);
    std::vector<std::string> GetPageMsg(int i);

private:
    bool isConnect = false;
    std::vector<RunePage> m_RunePages;
    Logger m_logger;
    std::string m_token;
    std::string m_port;
    std::unique_ptr<httplib::Client> m_lolClient;
    const std::string s_currentPage = "/lol-perks/v1/currentpage";
    const std::string s_page        = "/lol-perks/v1/pages";
};