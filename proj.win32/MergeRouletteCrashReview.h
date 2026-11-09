#pragma once
// Automated preview diagnostics only; never installed for ordinary play.
#include <windows.h>
#include <dbghelp.h>
#include <cstdio>
#pragma comment(lib,"dbghelp.lib")
inline LONG WINAPI MergeReviewCrash(EXCEPTION_POINTERS* ex) {
    const char* dir=getenv("CS_MERGE_REVIEW_PATH");
    std::string path=std::string(dir?dir:"")+"crash.log";
    FILE* out=fopen(path.c_str(),"w");if(!out)return EXCEPTION_EXECUTE_HANDLER;
    HANDLE process=GetCurrentProcess(),thread=GetCurrentThread();
    SymInitialize(process,nullptr,TRUE);
    CONTEXT context=*ex->ContextRecord;STACKFRAME64 stack={};
    stack.AddrPC.Offset=context.Eip;stack.AddrStack.Offset=context.Esp;stack.AddrFrame.Offset=context.Ebp;
    stack.AddrPC.Mode=stack.AddrStack.Mode=stack.AddrFrame.Mode=AddrModeFlat;
    fprintf(out,"exception %08lx at %p\n",ex->ExceptionRecord->ExceptionCode,ex->ExceptionRecord->ExceptionAddress);
    for(int i=0;i<32;++i) {
        char memory[sizeof(SYMBOL_INFO)+1024]={};auto symbol=(SYMBOL_INFO*)memory;
        symbol->SizeOfStruct=sizeof(SYMBOL_INFO);symbol->MaxNameLen=1023;DWORD64 displacement=0;
        if(SymFromAddr(process,stack.AddrPC.Offset,&displacement,symbol))fprintf(out,"%s + %llu\n",symbol->Name,displacement);
        else fprintf(out,"%llx\n",stack.AddrPC.Offset);
        if(!StackWalk64(IMAGE_FILE_MACHINE_I386,process,thread,&stack,&context,nullptr,SymFunctionTableAccess64,SymGetModuleBase64,nullptr))break;
    }
    fclose(out);return EXCEPTION_EXECUTE_HANDLER;
}
