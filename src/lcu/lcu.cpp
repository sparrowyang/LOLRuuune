#include "lcu.h"
#include <exception>
#include <fstream>
#define CPPHTTPLIB_OPENSSL_SUPPORT
Lcu::Lcu() {
    m_logger = Logger("Lcu", "test.log");
    m_logger.log(LogType::_INFO, "Init Lcu");
}
Lcu::~Lcu() {}
std::string Lcu::exec(const char* cmd) {
    // AllocConsole();
    // ShowWindow(GetConsoleWindow(), SW_HIDE);
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(_popen(cmd, "r"), _pclose);
    if (!pipe) { throw std::runtime_error("popen() failed!"); }
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr) { result += buffer.data(); }
    }
    return result;
}
/*
        "name":"oniasdta",
        "primaryStyleId":8300,
        "subStyleId":8400,
        "selectedPerkIds": [8351,8313,8345,8347,8451,8444,5007,5002,5001]
*/
bool Lcu::setRune(int id) {
    if (!CheckConnect()) {
        return false;
    }
    if (m_RunePages.size() == 0) {
        m_logger.log(LogType::_WARM, "Set Empty Data");
        return false;
    }
    nlohmann::json j;
    j["name"]            = m_RunePages[id].GetName();
    j["primaryStyleId"]  = m_RunePages[id].GetprimaryStyleId();
    j["subStyleId"]      = m_RunePages[id].GetsubStyleId();
    j["selectedPerkIds"] = m_RunePages[id].GetPageData();
    m_logger.log(LogType::_INFO, "setRune");
    try {
        delRunePage();
        auto res = m_lolClient->Post(s_page, j.dump(), "application/json");
        std::cout << "setRune res " << res->body << std::endl;
        m_logger.log(LogType::_INFO, std::to_string(res->status));
    }
    catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }
    return false;
}
bool Lcu::addRunePage() {
    m_logger.log(LogType::_INFO, "addRunePage");
    return false;
}
bool Lcu::delRunePage() {
    if (!CheckConnect()) {
        return false;
    }
    m_logger.log(LogType::_INFO, "delRunePage");
    auto res = m_lolClient->Delete(s_page);
    // std::cout << "setRune res " << res->status << std::endl;
    m_logger.log(LogType::_INFO, std::to_string(res->status));
    return false;
}
void Lcu::DelSavePage(int id) {
    if (m_RunePages.size()) {
        m_RunePages.erase(m_RunePages.begin() + id);
    }
}
bool Lcu::saveRunnePage() {
    if (!CheckConnect()) {
        return false;
    }
    try {
        auto res   = m_lolClient->Get(s_page);
        auto jdata = nlohmann::json::parse(res->body);
        RunePage p;
        m_logger.log(LogType::_INFO, " >>> Save Page");
        m_logger.log(LogType::_INFO, jdata[0].dump());
        p.SetName(jdata[0]["name"].get<std::string>());
        p.SetData(jdata[0]["selectedPerkIds"].get<std::list<int>>());
        p.SetprimaryStyleId(jdata[0]["primaryStyleId"].get<int>());
        p.SetsubStyleId(jdata[0]["subStyleId"].get<int>());
        m_RunePages.emplace(m_RunePages.begin(), p);
        // m_RunePages.emplace_back(p);
        SaveToFile();
    }
    catch (std::exception e) {
        m_logger.log(LogType::_ERROR, "saveRunnePage Exception");
        m_logger.log(LogType::_ERROR, e.what());
    }
    return false;
}
void Lcu::SaveToFile() {
    std::ofstream f("data.json", std::ios_base::out);
    nlohmann::json j;
    for (size_t i = 0; i < m_RunePages.size(); i++) {
        j[i]["name"]            = m_RunePages[i].GetName();
        j[i]["primaryStyleId"]  = m_RunePages[i].GetprimaryStyleId();
        j[i]["subStyleId"]      = m_RunePages[i].GetsubStyleId();
        j[i]["selectedPerkIds"] = m_RunePages[i].GetPageData();
    }
    std::string d = j.dump();
    f.write(d.c_str(), d.length());
    f.close();
}
void Lcu::LoadFile() {
    std::ifstream f("data.json");
    try {
        nlohmann::json j = nlohmann::json::parse(f);
        m_logger.log(LogType::_INFO, "load data file");
        RunePage p;
        for (auto& i: j) {
            p.SetName(i["name"].get<std::string>());
            p.SetData(i["selectedPerkIds"].get<std::list<int>>());
            p.SetprimaryStyleId(i["primaryStyleId"].get<int>());
            p.SetsubStyleId(i["subStyleId"].get<int>());
            m_RunePages.emplace_back(p);
        }
    }
    catch (std::exception e) {
        m_logger.log(LogType::_ERROR, e.what());
    }
    f.close();
}
bool Lcu::CheckConnect() {
    if (!isConnect) {
        m_logger.log(LogType::_WARM, "Not Connect.");
    }
    return isConnect;
}
std::vector<RunePage> Lcu::GetSavePages() {
    return m_RunePages;
}
void Lcu::SetToken(const std::string& raw) {
    std::regex re("--remoting-auth-token=(.+?)\" \"--app-port=(\\d+)");
    // m_logger.log(LogType::_INFO, res);
    std::smatch match;
    std::regex_search(raw, match, re);
    try {
        if (match[1] == "" || match[2] == "") {
            throw std::runtime_error("Get token failed, please ensure game is started and run as Administor");
        }
        m_token     = match[1];
        m_port      = match[2];
        m_lolClient = std::make_unique<httplib::Client>("https://"
                                                        "127.0.0.1:" +
            m_port);
        m_lolClient;
        m_lolClient->enable_server_certificate_verification(false);
        m_lolClient->set_basic_auth("riot", m_token);
        isConnect = true;
    }
    catch (std::exception e) {
        m_logger.log(LogType::_ERROR, e.what());
    }
}
