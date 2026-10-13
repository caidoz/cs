/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"
#include "Func_Net.h"
#include <cstdlib>
#include <crtdbg.h>

USING_NS_CC;

int WINAPI _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Explicit headless verification: never reads or writes the player's save.
    if (getenv("CS_CASTLE_PROTOCOL_TEST"))
        return NetCastleProtocolSelfTest() ? 0 : 1;

    // Isolated preview storage and non-modal CRT diagnostics for automated checks.
    if (const char* reviewPath = getenv("CS_CASTLE_REVIEW_PATH")) {
        FileUtils::getInstance()->setWritablePath(reviewPath);
#ifdef _DEBUG
        std::string report = std::string(reviewPath) + "startup-crt.log";
        HANDLE reportFile = CreateFileA(report.c_str(), GENERIC_WRITE,
            FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (reportFile != INVALID_HANDLE_VALUE) {
            _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
            _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
            _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
            _CrtSetReportFile(_CRT_WARN, (_HFILE)reportFile);
            _CrtSetReportFile(_CRT_ERROR, (_HFILE)reportFile);
            _CrtSetReportFile(_CRT_ASSERT, (_HFILE)reportFile);
        }
#endif
    }

    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}
