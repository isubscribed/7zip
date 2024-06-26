#include "Windows.h"
#include "ScannerCommonFunctions.h"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

using UnpackFunc = bool (*)(const TCHAR* chAction, const TCHAR* chArchiveName, const TCHAR* chOutputFolderName,
    const TCHAR* chPassword, const TCHAR* chFileFilter, ScanFileState* pScanFileState);
using PackFunc = bool (*)(const TCHAR* chAction, const TCHAR* chArchiveName, const TCHAR* chInputFileFolderName,
    const TCHAR* chPassword, const TCHAR* chFileFilter);

const std::wstring_view k7zipLibName = L"Binaries\\Au7zUnpacker.dll";
const fs::path kTestDir = fs::temp_directory_path() / "Test7zipFiles";
const fs::path kUnpackedFile = kTestDir / "Test7zip_unpacked.txt";
const fs::path kPackedFile = kTestDir / "Test7zip_packed.zip";
const std::wstring_view kPassword = L"-pabc!@#123ABC";
const std::string_view kUnpackedContent = "*** TestContent_12345 ***";
const int kMaxTempFileCount = 10000;

HMODULE g_7zip = nullptr;
UnpackFunc g_UnpackFunc = nullptr;
PackFunc g_PackFunc = nullptr;


template <typename F>
void InitFunc(F& function, const char* funcName)
{
    if (g_7zip)
    {
        function = reinterpret_cast<F>(GetProcAddress(g_7zip, funcName));
    }
}

TEST_CASE("Setup")
{
    g_7zip = LoadLibrary(k7zipLibName.data());
    REQUIRE(g_7zip);
    
    if (g_7zip)
    {
        InitFunc(g_UnpackFunc, "UnMax7zArchive");
        REQUIRE(g_UnpackFunc);

        InitFunc(g_PackFunc, "Max7zArchive");
        REQUIRE(g_PackFunc);
    }

    fs::remove_all(kTestDir);
}

TEST_CASE("Zipping/Unzipping the file", "[7zip]")
{
    SECTION("Create source file and write some content there")
    {
        fs::create_directory(kTestDir);
        std::ofstream originalFile(kUnpackedFile.string());
        REQUIRE(originalFile);
        originalFile << kUnpackedContent;
        originalFile.close();
        REQUIRE(!originalFile.is_open());
    }

    SECTION("Zipping the file")
    {
        bool result = g_PackFunc(L"a", kPackedFile.wstring().data(),
            kUnpackedFile.wstring().data(), kPassword.data(), nullptr);
        REQUIRE(result);
        REQUIRE(fs::exists(kPackedFile));
        fs::remove(kUnpackedFile);
    }

    SECTION("Unzipping the file")
    {
        std::wstring unpackDirName = L"-o" + kTestDir.wstring();
        ScanFileState fileState = ScanFileState::E_ScanFileState_None;
        bool result = g_UnpackFunc(L"x", kPackedFile.wstring().data(),
            unpackDirName.data(), kPassword.data(), nullptr, &fileState);
        REQUIRE(result);
        REQUIRE(fs::exists(kUnpackedFile));
        std::ifstream unpackedFile(kUnpackedFile);
        std::stringstream buffer;
        buffer << unpackedFile.rdbuf();
        REQUIRE(buffer.str() == kUnpackedContent);
    }
}

TEST_CASE("Teardown")
{
    FreeLibrary(g_7zip);
    fs::remove_all(kTestDir);
}
