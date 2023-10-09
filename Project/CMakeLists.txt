cmake_minimum_required(VERSION 3.20)
project(FGO_Sim)

set(CMAKE_CXX_STANDARD 23)

add_executable(FGO_Sim main.cpp Servant/Servant.cpp Servant/Servant.h Servant/Append_Skill/Append_Skill.cpp Servant/Append_Skill/Append_Skill.h Servant/Card/Card.cpp Servant/Card/Card.h Servant/Class/Class.cpp Servant/Class/Class.h Servant/Noble_Phantasm/Noble_Phantasm.cpp Servant/Noble_Phantasm/Noble_Phantasm.h Servant/Passive_Skill/Passive_Skill.cpp Servant/Passive_Skill/Passive_Skill.h Servant/Skill/Skill.cpp Servant/Skill/Skill.h Servant/Class/Saber/Saber.cpp Servant/Class/Saber/Saber.h Servant/Attribute/Attribute.cpp Servant/Attribute/Attribute.h Utils/utils.cpp Utils/utils.h Simulator/Simulator.cpp Simulator/Simulator.h Battlefield/Battlefield.cpp Battlefield/Battlefield.h Enemy/Enemy.cpp Enemy/Enemy.h Enemy/Enemy_Noble_Phantasm/Enemy_Noble_Phantasm.cpp Enemy/Enemy_Noble_Phantasm/Enemy_Noble_Phantasm.h Enemy/Enemy_Skill/Enemy_Skill.cpp Enemy/Enemy_Skill/Enemy_Skill.h Enemy/Enemy_Hit/Enemy_Hit.cpp Enemy/Enemy_Hit/Enemy_Hit.h Battle/Battle.cpp Battle/Battle.h)
