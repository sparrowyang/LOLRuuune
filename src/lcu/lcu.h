#pragma once
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "../logger/log.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>
#include <regex>
#define CPPHTTPLIB_OPENSSL_SUPPORT
class RunePage;
class Lcu
{

public:
	Lcu();
	~Lcu();
	std::string exec(const char* cmd);
	bool setRune();
	bool addRunePage();
	bool delRunePage();
	void test();

private:
	//std::vector<RunePage> RunePages;
	Logger m_logger;
	std::string m_token;
	std::string m_port;
	std::unique_ptr<httplib::Client> m_lolClient;
};