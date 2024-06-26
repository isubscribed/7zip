cmake_minimum_required(VERSION 3.14)

# include(cmake/PreventInSourceBuilds.cmake)

project(7Zip
	VERSION 24.06
	LANGUAGES C CXX ASM
)

enable_testing()

add_definitions(
	-D_CONSOLE
	-DWIN_LONG_PATH
	-DZ7_EXTERNAL_CODECS
	-D_7ZIP_LARGE_PAGES
	-DSUPPORT_DEVICE_FILE
)

if (CMAKE_BUILD_NUMBER)
    add_definitions(-DGithubBuildNumber=${CMAKE_BUILD_NUMBER})
endif ()

if (MSVC)
    add_definitions(-DUNICODE -D_UNICODE -D_CRT_SECURE_NO_WARNINGS)
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif ()

if (NOT CMAKE_C_STANDARD)
	set(CMAKE_C_STANDARD 11)
endif ()

if (NOT CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 17)
endif ()

set(BUILD_SHARED_LIBS ON)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif ()

set(MAIN_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/Output/x64)

add_library(Au7zUnpacker SHARED ${SOURCES})

set_target_properties(Au7zUnpacker PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${MAIN_OUTPUT_DIR}/Debug/Binaries
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${MAIN_OUTPUT_DIR}/Release/Binaries
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${MAIN_OUTPUT_DIR}/MinSizeRel/Binaries
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${MAIN_OUTPUT_DIR}/RelWithDebInfo/Binaries
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${MAIN_OUTPUT_DIR}/Debug
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${MAIN_OUTPUT_DIR}/Release
    ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${MAIN_OUTPUT_DIR}/MinSizeRel
    ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${MAIN_OUTPUT_DIR}/RelWithDebInfo
)

target_sources(
    Au7zUnpacker PRIVATE

    C/7zCrc.h
    C/7zTypes.h
    C/Alloc.h
    C/CpuArch.h
    C/DllSecur.h
    C/Sort.h
    C/Threads.h

    C/7zCrc.c
    C/7zCrcOpt.c
    C/Alloc.c
    C/CpuArch.c
    C/DllSecur.c
    C/Sort.c
    C/Threads.c

    CPP/Common/CommandLineParser.h
    CPP/Common/Common.h
    CPP/Common/ComTry.h
    CPP/Common/Defs.h
    CPP/Common/DynLimBuf.h
    CPP/Common/IntToString.h
    CPP/Common/ListFileUtils.h
    CPP/Common/MyBuffer.h
    CPP/Common/MyCom.h
    CPP/Common/MyString.h
    CPP/Common/MyTypes.h
    CPP/Common/MyVector.h
    CPP/Common/NewHandler.h
    CPP/Common/StdInStream.h
    CPP/Common/StdOutStream.h
    CPP/Common/StringConvert.h
    CPP/Common/StringToInt.h
    CPP/Common/UTFConvert.h
    CPP/Common/Wildcard.h

    CPP/Common/CommandLineParser.cpp
    CPP/Common/CRC.cpp
    CPP/Common/DynLimBuf.cpp
    CPP/Common/IntToString.cpp
    CPP/Common/ListFileUtils.cpp
    CPP/Common/MyString.cpp
    CPP/Common/MyVector.cpp
    CPP/Common/NewHandler.cpp
    CPP/Common/StdInStream.cpp
    CPP/Common/StdOutStream.cpp
    CPP/Common/StringConvert.cpp
    CPP/Common/StringToInt.cpp
    CPP/Common/UTFConvert.cpp
    CPP/Common/Wildcard.cpp

    CPP/Windows/DLL.h
    CPP/Windows/ErrorMsg.h
    CPP/Windows/FileDir.h
    CPP/Windows/FileFind.h
    CPP/Windows/FileIO.h
    CPP/Windows/FileMapping.h
    CPP/Windows/FileName.h
    CPP/Windows/FileSystem.h
    CPP/Windows/MemoryLock.h
    CPP/Windows/NtCheck.h
    CPP/Windows/PropVariant.h
    CPP/Windows/PropVariantConv.h
    CPP/Windows/Registry.h
    CPP/Windows/Synchronization.h
    CPP/Windows/System.h
    CPP/Windows/SystemInfo.h
    CPP/Windows/Thread.h
    CPP/Windows/TimeUtils.h

    CPP/Windows/DLL.cpp
    CPP/Windows/ErrorMsg.cpp
    CPP/Windows/FileDir.cpp
    CPP/Windows/FileFind.cpp
    CPP/Windows/FileIO.cpp
    CPP/Windows/FileLink.cpp
    CPP/Windows/FileName.cpp
    CPP/Windows/FileSystem.cpp
    CPP/Windows/MemoryLock.cpp
    CPP/Windows/PropVariant.cpp
    CPP/Windows/PropVariantConv.cpp
    CPP/Windows/Registry.cpp
    CPP/Windows/System.cpp
    CPP/Windows/SystemInfo.cpp
    CPP/Windows/TimeUtils.cpp

    CPP/7zip/Archive/Common/ItemNameUtils.h
    CPP/7zip/Archive/Common/OutStreamWithCRC.h
    CPP/7zip/Archive/IArchive.h

    CPP/7zip/Archive/Common/ItemNameUtils.cpp
    CPP/7zip/Archive/Common/OutStreamWithCRC.cpp

    CPP/7zip/Common/CreateCoder.h
    CPP/7zip/Common/FilePathAutoRename.h
    CPP/7zip/Common/FileStreams.h
    CPP/7zip/Common/FilterCoder.h
    CPP/7zip/Common/LimitedStreams.h
    CPP/7zip/Common/MethodProps.h
    CPP/7zip/Common/MultiOutStream.h
    CPP/7zip/Common/ProgressUtils.h
    CPP/7zip/Common/RegisterArc.h
    CPP/7zip/Common/StreamObjects.h
    CPP/7zip/Common/StreamUtils.h
    CPP/7zip/Common/UniqBlocks.h

    CPP/7zip/Common/CreateCoder.cpp
    CPP/7zip/Common/FilePathAutoRename.cpp
    CPP/7zip/Common/FileStreams.cpp
    CPP/7zip/Common/FilterCoder.cpp
    CPP/7zip/Common/LimitedStreams.cpp
    CPP/7zip/Common/MethodProps.cpp
    CPP/7zip/Common/MultiOutStream.cpp
    CPP/7zip/Common/ProgressUtils.cpp
    CPP/7zip/Common/PropId.cpp
    CPP/7zip/Common/StreamObjects.cpp
    CPP/7zip/Common/StreamUtils.cpp
    CPP/7zip/Common/UniqBlocks.cpp

    CPP/7zip/Compress/CopyCoder.h
    CPP/7zip/Compress/CopyCoder.cpp

    CPP/7zip/ICoder.h
    CPP/7zip/IDecl.h
    CPP/7zip/IPassword.h
    CPP/7zip/IProgress.h
    CPP/7zip/IStream.h
    CPP/7zip/PropID.h

    CPP/7zip/UI/Common/ArchiveCommandLine.h
    CPP/7zip/UI/Common/ArchiveExtractCallback.h
    CPP/7zip/UI/Common/ArchiveOpenCallback.h
    CPP/7zip/UI/Common/Bench.h
    CPP/7zip/UI/Common/DefaultName.h
    CPP/7zip/UI/Common/DirItem.h
    CPP/7zip/UI/Common/EnumDirItems.h
    CPP/7zip/UI/Common/ExitCode.h
    CPP/7zip/UI/Common/Extract.h
    CPP/7zip/UI/Common/ExtractingFilePath.h
    CPP/7zip/UI/Common/ExtractMode.h
    CPP/7zip/UI/Common/HashCalc.h
    CPP/7zip/UI/Common/IFileExtractCallback.h
    CPP/7zip/UI/Common/LoadCodecs.h
    CPP/7zip/UI/Common/OpenArchive.h
    CPP/7zip/UI/Common/Property.h
    CPP/7zip/UI/Common/PropIDUtils.h
    CPP/7zip/UI/Common/ScannerCommonFunctions.h
    CPP/7zip/UI/Common/SetProperties.h
    CPP/7zip/UI/Common/SortUtils.h
    CPP/7zip/UI/Common/TempFiles.h
    CPP/7zip/UI/Common/Update.h
    CPP/7zip/UI/Common/UpdateAction.h
    CPP/7zip/UI/Common/UpdateCallback.h
    CPP/7zip/UI/Common/UpdatePair.h
    CPP/7zip/UI/Common/UpdateProduce.h
    CPP/7zip/UI/Common/ZipRegistry.h

    CPP/7zip/UI/Common/ArchiveCommandLine.cpp
    CPP/7zip/UI/Common/ArchiveExtractCallback.cpp
    CPP/7zip/UI/Common/ArchiveOpenCallback.cpp
    CPP/7zip/UI/Common/Bench.cpp
    CPP/7zip/UI/Common/DefaultName.cpp
    CPP/7zip/UI/Common/EnumDirItems.cpp
    CPP/7zip/UI/Common/Extract.cpp
    CPP/7zip/UI/Common/ExtractingFilePath.cpp
    CPP/7zip/UI/Common/HashCalc.cpp
    CPP/7zip/UI/Common/LoadCodecs.cpp
    CPP/7zip/UI/Common/OpenArchive.cpp
    CPP/7zip/UI/Common/PropIDUtils.cpp
    CPP/7zip/UI/Common/ScannerCommonFunctions.cpp
    CPP/7zip/UI/Common/SetProperties.cpp
    CPP/7zip/UI/Common/SortUtils.cpp
    CPP/7zip/UI/Common/TempFiles.cpp
    CPP/7zip/UI/Common/Update.cpp
    CPP/7zip/UI/Common/UpdateAction.cpp
    CPP/7zip/UI/Common/UpdateCallback.cpp
    CPP/7zip/UI/Common/UpdatePair.cpp
    CPP/7zip/UI/Common/UpdateProduce.cpp

    CPP/7zip/UI/Console/BenchCon.h
    CPP/7zip/UI/Console/ConsoleClose.h
    CPP/7zip/UI/Console/ExtractCallbackConsole.h
    CPP/7zip/UI/Console/HashCon.h
    CPP/7zip/UI/Console/List.h
    CPP/7zip/UI/Console/OpenCallbackConsole.h
    CPP/7zip/UI/Console/PercentPrinter.h
    CPP/7zip/UI/Console/StdAfx.h
    CPP/7zip/UI/Console/UpdateCallbackConsole.h
    CPP/7zip/UI/Console/UserInputUtils.h

    CPP/7zip/UI/Console/BenchCon.cpp
    CPP/7zip/UI/Console/ConsoleClose.cpp
    CPP/7zip/UI/Console/ExtractCallbackConsole.cpp
    CPP/7zip/UI/Console/HashCon.cpp
    CPP/7zip/UI/Console/List.cpp
    CPP/7zip/UI/Console/Main.cpp
    CPP/7zip/UI/Console/MainAr.cpp
    CPP/7zip/UI/Console/OpenCallbackConsole.cpp
    CPP/7zip/UI/Console/PercentPrinter.cpp
    CPP/7zip/UI/Console/StdAfx.cpp
	CPP/7zip/UI/Console/UpdateCallbackConsole.cpp
	CPP/7zip/UI/Console/UserInputUtils.cpp
	CPP/7zip/UI/Console/console.def
)

add_executable(Test_7zip Test_7zip/test_7zip.cpp)

target_include_directories(Test_7zip PUBLIC
    CPP/7zip/UI/Common
    ThirdParty/catch2
)

set_target_properties(Test_7zip PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${MAIN_OUTPUT_DIR}/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${MAIN_OUTPUT_DIR}/Release
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${MAIN_OUTPUT_DIR}/MinSizeRel
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${MAIN_OUTPUT_DIR}/RelWithDebInfo
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${MAIN_OUTPUT_DIR}/Debug
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${MAIN_OUTPUT_DIR}/Release
    ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${MAIN_OUTPUT_DIR}/MinSizeRel
    ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${MAIN_OUTPUT_DIR}/RelWithDebInfo
)

add_test(NAME Test_7zip COMMAND Test_7zip)
