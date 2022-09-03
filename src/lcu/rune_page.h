#pragma once
#include <list>
#include <string>
class RunePage {
public:
    RunePage();
    ~RunePage();
    void SetName(std::string name);
    void SetprimaryStyleId(int id) void SetsubStyleId(int id);
    void SetData(std::list<int> data);
    std::string GetName();
    std::list<int> GetPageData();
    int GetprimaryStyleId();
    int GetsubStyleId();

private:
    std::string m_name;
    int m_primaryStyleId;
    int m_subStyleId;
    std::list<int> m_selectedPerkIds;
};