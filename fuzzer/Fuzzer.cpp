#include "Fuzzer.h"

void Fuzzer::Start(const int code_operation) {
    int enter_code = code_operation;
    int tmp_test_file = 0;
    Generation generation;
    generation.SetPath(PathIN, PathOUT);

    while (true) {
        LPWSTR arguments_convector = 0;
        if (enter_code == 1) {
            generation.GenFile();
            generation.GenBinaryFile();
            std::wstring name_file = L"..\\GenerationTestFile\\test.prc";
            std::wstring arguments(L"Convector.exe ..\\GenerationTestFile\\test.prc ..\\GenerationTestFile\\test2.doc");
            LPWSTR arguments_convector = &arguments[0];
            ArgumentsCMD(arguments_convector, name_file);
        }
        else if (enter_code == 2) {
            if (generation.TestFile(++tmp_test_file) != L"1") {
                std::wstring name_file = generation.TestFile(tmp_test_file);
                std::wstring name_exe(L"Convector.exe ");
                std::wstring name_path_out(L" ..\\GenerationTestFile\\test2.doc");
                std::wstring arguments = name_exe + name_file + name_path_out;
                LPWSTR arguments_convector = &arguments[0];
                ArgumentsCMD(arguments_convector, name_file);
            }
            else
                tmp_test_file = 0;
        }
    }
}

void Fuzzer::ArgumentsCMD(LPWSTR arguments_convector, std::wstring name_file) {
    STARTUPINFO process = { 0 };
    PROCESS_INFORMATION pr = { 0 };
    DWORD process_code;
    std::wstring path(L"..\\Convector.exe");
    LPWSTR path_exe = &path[0];
    if (CreateProcess(path_exe, arguments_convector, NULL, NULL, FALSE, NULL, NULL, NULL, &process, &pr) == TRUE) {
        WaitForSingleObject(pr.hProcess, INFINITE);
        if (GetExitCodeProcess(pr.hProcess, &process_code) == true) {
            if (process_code > 0) {
                CloseHandle(pr.hProcess);
                CreateLogFile NewLogFile;
                NewLogFile.LogFile(name_file);
            }
            CloseHandle(pr.hProcess);
        }
    }
    else {
        std::cout << "Error: " + GetLastError() << std::endl;
        system("pause");
        return;
    }
    DelFileConverter();
}

void Fuzzer::InformatioMessage() {
    std::string tmp_info;
    std::vector<std::string> v_info;
    std::ifstream info_file("..\\Information\\ReadMe.txt", std::ios::in);
    if (info_file.is_open()) {
        std::copy(std::istream_iterator<std::string>(info_file), std::istream_iterator<std::string>(), std::back_inserter(v_info));
        for (auto& a : v_info) {
            tmp_info += a + ' ';
        }
        std::wstring wstr(tmp_info.begin(), tmp_info.end());
        LPCUWSTR str_info = &wstr[0];
        MessageBox(0, str_info, L"Information massage", MB_OK);
    }
}