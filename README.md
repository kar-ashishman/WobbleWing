# Steps to Load an ELF in STM32CubeIDE

## 1. Create a New Project
- Open **STM32CubeIDE**.
- Go to **File → New → Project**.
- Choose **Empty Project** (or *Makefile Project with Existing Code* if you want to attach sources).
- Select your target MCU (e.g., **STM32F466RE**).

## 2. Configure the Project
- Once the project is created, don’t add sources.
- Right‑click the project → **Properties**.
- Navigate to **C/C++ Build → Settings**.
- Disable the build if you don’t want CubeIDE to compile.

## 3. Set Up Debug Configuration
- Go to **Run → Debug Configurations…**.
- Create a new **STM32 Cortex‑M C/C++ Application** configuration.

## 4. Link the ELF File
- In the **Main** tab, under *C/C++ Application*, browse and select your **.elf file**.

## 5. Configure the Debugger
- In the **Debugger** tab, ensure the correct **ST‑Link interface** is selected.

## 6. Flash and Debug
- Click **Apply** and then **Debug**.
- CubeIDE will flash the ELF to your board and let you debug it.