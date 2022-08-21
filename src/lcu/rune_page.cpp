#include "rune_page.h"

RunePage::RunePage(){}
RunePage::~RunePage(){}

std::string RunePage::GetName(){
    return m_name;
}

void RunePage::SetName(std::string name){
    m_name = name;
}

void RunePage::SetprimaryStyleId(int id)
{
	m_primaryStyleId = id;
}

void RunePage::SetsubStyleId(int id)
{
	m_subStyleId = id;
}

void RunePage::SetData(std::list<int> data){
	m_selectedPerkIds = data;
}

std::list<int>  RunePage::GetPageData(){
    return m_selectedPerkIds;
}

int RunePage::GetprimaryStyleId()
{
	return m_primaryStyleId;
}

int RunePage::GetsubStyleId()
{
	return m_subStyleId;
}
