#include <iostream>
#include <string>

#include <dlfcn.h>

#include "nethost.h"
#include "coreclr_delegates.h"
#include "hostfxr.h"


using string_t = std::string;

typedef void (*SayIt)();

int main()
{
    std::cout << "Program start called\n";

    char_t buffer[256];
    size_t buffer_elements = sizeof(buffer)/sizeof(char_t);

    int rc = get_hostfxr_path(buffer, &buffer_elements, nullptr);
    if (rc!=0)
    {
        std::cerr << "[C++] Failed to find .NET runtime. Error code: " << rc << "\n";
        return -1;
    }

    string_t hostfxr_path = buffer;

    void* hostfxr_library = dlopen(hostfxr_path.c_str(), RTLD_LAZY | RTLD_LOCAL);

    auto init_fptr = (hostfxr_initialize_for_runtime_config_fn)dlsym(hostfxr_library, "hostfxr_initialize_for_runtime_config");
    auto get_delegate_fptr = (hostfxr_get_runtime_delegate_fn)dlsym(hostfxr_library, "hostfxr_get_runtime_delegate");
    auto close_fptr = (hostfxr_close_fn)dlsym(hostfxr_library, "hostfxr_close");

    string_t config_path = "Sandbox/bin/Debug/net10.0/Sandbox.deps.json";

    hostfxr_handle context = nullptr;
    init_fptr(config_path.c_str(), nullptr, &context);

    void* load_assembly_ptr = nullptr;
    get_delegate_fptr(context, hdt_load_assembly_and_get_function_pointer, &load_assembly_ptr);

auto load_assembly = (load_assembly_and_get_function_pointer_fn)load_assembly_ptr;

    string_t assembly_path = "Sandbox/bin/Debug/net10.0/Sandbox.dll";
    string_t type_name = "Sandbox.ComponentA, Sandbox"; // "Namespace.Class, AssemblyName"
    string_t method_name = "SayIt";

    SayIt sayIt = nullptr;

    load_assembly(assembly_path.c_str(), type_name.c_str(),
        method_name.c_str(), UNMANAGEDCALLERSONLY_METHOD, nullptr,
        (void**)&sayIt);

    if (sayIt!=nullptr)
    {
        sayIt();
    }
    else std::cout << "Say it not found :(\n";
    close_fptr(context);

    // SayIt function = nullptr;

    // if (function) function;

    std::cout << "Program end called\n";
    return 0;
}
