#include <wasmedge/wasmedge.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    // If no input is provided, i have set input to 10
    int input = 10;
    if (argc > 1){
        input = atoi(argv[1]);
    }
    else{
        printf(" [INFO] No input provided. Defaulting to 10.\n");
    }

    // Sanity Check
    if (input < 0){
        printf(" [ERROR] Input must be a non-negative integer (input was %d).\n", input);
        return 1;
    }

    printf("  Computing Fibonacci(%d) using WASM..... \n\n", input);

    // Creating Configuration
    printf("  Creating WasmEdge configuration..... \n");
    WasmEdge_ConfigureContext *ConfCxt = WasmEdge_ConfigureCreate();

    // Create VM Context
    printf("  Creating VM context..... \n");
    WasmEdge_VMContext *VMCxt = WasmEdge_VMCreate(ConfCxt, NULL);

    // Prepare Parameters
    printf("  Preparing function parameters..... \n");
    WasmEdge_Value Params[1] = {WasmEdge_ValueGenI32(input)};
    WasmEdge_Value Returns[1];

    // Prepare Function Name
    printf("  Setting function name as : 'fib'..... \n");
    WasmEdge_String FuncName = WasmEdge_StringCreateByCString("fib");

    // Execute WASM
    printf("  Loading and executing fibonacci.wasm..... \n\n");
    WasmEdge_Result Res = WasmEdge_VMRunWasmFromFile(
        VMCxt,
        "fibonacci.wasm",
        FuncName,
        Params,
        1,
        Returns,
        1);

    // Result
    printf("  RESULT..... \n");
    if (WasmEdge_ResultOK(Res))
    {
        int32_t result = WasmEdge_ValueGetI32(Returns[0]);
        printf("  SUCCESS!\n");
        printf("  Fibonacci(%d) = %d \n", input, result);
    }
    else
    {
        printf("  ERROR!\n");
        printf("  Error message: %s \n", WasmEdge_ResultGetMessage(Res));
    }

    // Cleaning Up resources
    printf("  Cleaning up resources..... \n");
    WasmEdge_VMDelete(VMCxt);
    WasmEdge_ConfigureDelete(ConfCxt);
    WasmEdge_StringDelete(FuncName);

    printf(" Done! \n\n");

    return WasmEdge_ResultOK(Res) ? 0 : 1;
}
