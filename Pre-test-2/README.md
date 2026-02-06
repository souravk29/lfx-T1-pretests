# LFX Mentorship Pre-test 2: WasmEdge C API Implementation

This project is a solution for the **WasmEdge CLI Tool Extension** pre-test. It implements a C++ program that utilizes the WasmEdge C API to load, validate, and execute a WebAssembly module, effectively replicating the behavior of the `wasmedge run` CLI command.

## 🎥 Solution Videos & Results

I have implemented and verified the solution using two different build methods.

### 1. Manual Compilation
*Direct compilation using `MSVC` without a build system. Output of Pre-test-1 is also included in this video.*
- [▶️ Watch Manual Compilation Video](https://drive.google.com/file/d/1i3bbZa1H_WCdEywAL0OfiHGC_rsiZRtK/view?usp=sharing)

**Execution Output:**
![Manual Compilation Output](Output_Of_Pretest-2.png)

---

### 2. Compilation Using CMake
*Automated build configuration using `CMakeLists.txt`.*
- [▶️ Watch CMake Solution Video](https://drive.google.com/file/d/1kDI_A1G2MrZQ-tMk0pVSJXMEqA6D5QSA/view?usp=sharing)

**Execution Output:**
![CMake Output](Output_using_CMake_Pretest-2.png)

## 🚀 How to Build & Run

**ℹ️ Note:** The compiled `fibonacci.wasm` file is **already attached** in this repository. You do NOT need to compile the source `.wat` file manually.

### Option 1: Using CMake (Recommended)
This method automatically handles dependencies and places the WASM file correctly.

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release

```
**Run the Application**

Windows
```bash
.\Release\fibonacci_runner.exe 10

```

Linux / macOS
```bash
./fibonacci_runner 10

```

### Option 2: Manual Compilation
# Example for Windows manual build
```bash
.\fibonacci_runner.exe 10

```
