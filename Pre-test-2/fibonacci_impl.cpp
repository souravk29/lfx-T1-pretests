/*     LFX Mentorship Pre-test-2: WasmEdge      */

#include <iostream>
#include <string>
#include <limits>
#include <cstdio>

extern "C"
{
#include <wasmedge/wasmedge.h>
}

int main(int argc, char *argv[])
{

    // 1. Initial Resource Management
    WasmEdge_ConfigureContext *conf_cxt = nullptr;
    WasmEdge_VMContext *vm_cxt = nullptr;
    WasmEdge_String func_name = WasmEdge_StringCreateByCString("fib");
    int exit_code = 0;

    // INPUT VALIDATION
    int input = 10; // i have set default

    if (argc > 1)
    {
        try
        {
            size_t pos;
            long val = std::stol(argv[1], &pos);

            if (pos != std::string(argv[1]).length())
            {
                throw std::invalid_argument("Trailing characters");
            }

            if (val < 0 || val > std::numeric_limits<int>::max())
            {
                throw std::out_of_range("Input out of bounds");
            }
            input = static_cast<int>(val);
        }
        catch (const std::exception &e)
        {
            std::cerr << " [ERROR] Invalid input: " << argv[1]
                      << " Provide a non-negative integer" << std::endl;
            return 1;
        }
    }
    else
    {
        std::cout << " [INFO] No input provided. Defaulting is set to 10" << std::endl;
    }

    // FILE PATH HANDLING
    std::string wasm_file = "fibonacci.wasm";
    if (argc > 2)
    {
        wasm_file = argv[2];
    }

    // Pre-check file existence
    if (FILE *f = std::fopen(wasm_file.c_str(), "r"))
    {
        std::fclose(f);
    }
    else
    {
        std::cerr << " [ERROR] File not found: " << wasm_file << std::endl;
        return 1;
    }

    std::cout << "  Computing Fibonacci(" << input << ") using: " << wasm_file << std::endl;

    // VM INITIALIZATION
    conf_cxt = WasmEdge_ConfigureCreate();

    // Enable WASI: for compiled WASM modules
    WasmEdge_ConfigureAddHostRegistration(conf_cxt, WasmEdge_HostRegistration_Wasi);

    vm_cxt = WasmEdge_VMCreate(conf_cxt, nullptr);
    if (!vm_cxt)
    {
        std::cerr << " [ERROR] Failed to create WasmEdge VM." << std::endl;
        exit_code = 1;
        goto cleanup;
    }

    // EXECUTION PREP

    // We use a raw array instead of std::vector to avoid DLL boundary memory conflicts (Heap Corruption) on Windows( encountered : ) ).
    WasmEdge_Value params[1] = {WasmEdge_ValueGenI32(input)};

    // Safety Buffer: Size 4 to avoid Stack corruption erros (when [1])
    WasmEdge_Value returns[4];

    // Allowing custom function name from 3rd argument
    if (argc > 3)
    {
        WasmEdge_StringDelete(func_name);
        func_name = WasmEdge_StringCreateByCString(argv[3]);
    }

    // RUN WASM
    WasmEdge_Result res = WasmEdge_VMRunWasmFromFile(
        vm_cxt,
        wasm_file.c_str(),
        func_name,
        params, 1,
        returns, 1);

    if (WasmEdge_ResultOK(res))
    {
        int32_t result = WasmEdge_ValueGetI32(returns[0]);
        std::cout << "  SUCCESS! Fibonacci result: " << result << std::endl;
    }
    else
    {
        std::cerr << "  [RUNTIME ERROR]: " << WasmEdge_ResultGetMessage(res) << std::endl;
        exit_code = 1;
    }

    // CLEANUP
cleanup:
    if (vm_cxt)
        WasmEdge_VMDelete(vm_cxt);
    if (conf_cxt)
        WasmEdge_ConfigureDelete(conf_cxt);
    WasmEdge_StringDelete(func_name);

    return exit_code;
}