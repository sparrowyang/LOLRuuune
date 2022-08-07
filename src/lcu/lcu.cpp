#include "lcu.h"
#include <exception>
Lcu::Lcu()
{
	m_logger = Logger("Lcu", "test.log");
	m_logger.log(LogType::_INFO, "Init Lcu");
	std::regex re("--remoting-auth-token=(.+?)\" \"--app-port=(\\d+)");
	std::string res = exec("wmic process where \"name='LeagueClientUx.exe'\" get commandline");
	// m_logger.log(LogType::_INFO, res);
	std::smatch match;
	// TODO : 错误检查
	std::regex_search(res, match, re);
	std::cout<<match[1]<<match[2]<<std::endl;
	m_logger.log(LogType::_INFO, match[1]);
	m_logger.log(LogType::_INFO, match[2]);
	m_token = match[1];
	m_port = match[2];
	// m_lolClient = std::make_unique<httplib::Client>("https://riot:" + std::string(match[1]) + "@127.0.0.1:" + std::string(match[2]));
}
Lcu::~Lcu() {}

std::string Lcu::exec(const char *cmd)
{
	// AllocConsole();
	// ShowWindow(GetConsoleWindow(), SW_HIDE);
	std::array<char, 128> buffer;
	std::string result;
	std::shared_ptr<FILE> pipe(_popen(cmd, "r"), _pclose);
	if (!pipe)
		throw std::runtime_error("popen() failed!");
	while (!feof(pipe.get()))
	{
		if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
			result += buffer.data();
	}
	return result;
}

/*

	"name":"oniasdta",
	"primaryStyleId":8300,
	"subStyleId":8400,
	"selectedPerkIds": [8351,8313,8345,8347,8451,8444,5007,5002,5001]
*/
bool Lcu::setRune()
{
	#define CPPHTTPLIB_OPENSSL_SUPPORT
	httplib::Params params;
	params.emplace("name", "asdda");
	params.emplace("primaryStyleId", "8300");
	params.emplace("subStyleId", "8400");
	params.emplace("selectedPerkIds", "[8351,8313,8345,8347,8451,8444,5007,5002,5001]");
	std::string data = R"(
		{
    "name":"oniasdta",
    "primaryStyleId":8300,
    "subStyleId":8400,     
    "selectedPerkIds": [8351,8313,8345,8347,8451,8444,5007,5002,5001]
	)";
	m_logger.log(LogType::_INFO, "setRune");
	std::cout << "setRune" << std::endl;
	// httplib::Client cli("https://riot:" + m_token + "@127.0.0.1:" + m_port);
	try
	{
		httplib::Client cli("https://127.0.0.1:54767");
		cli.enable_server_certificate_verification(false);
		// cli.set_basic_auth("riot", m_token);
		cli.set_basic_auth("riot", "Rij0aKIfoneVG1SDKF0uXw");
		// httplib::Client cli("http://192.168.1.23");
		//  auto res = cli.Post("/typecho/", data,"application/json");
		auto res = cli.Get("/lol-perks/v1/pages");
		std::cout << "setRune res " << res->status << std::endl;
		m_logger.log(LogType::_INFO, res->body);
	}catch (std::exception e){
		std::cerr<<e.what()<<std::endl;
	}

	return false;
}
bool Lcu::addRunePage()
{
	m_logger.log(LogType::_INFO, "addRunePage");
	return false;
}
bool Lcu::delRunePage()
{
	m_logger.log(LogType::_INFO, "delRunePage");
	return false;
}
void Lcu::test() {}
