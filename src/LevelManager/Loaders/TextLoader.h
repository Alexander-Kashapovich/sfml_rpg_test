#pragma once

#include <fstream>
#include <filesystem>

#include "I_LevelLoader.h"

namespace fs = std::filesystem;

namespace LevelLoader
{

// ИД левела хранится в названии файла
class TextLoader final : public Interface
{
public:
    Level load(int index) override final;
    void save(const Level &level) override final;
};
}