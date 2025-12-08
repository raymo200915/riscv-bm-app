# RISC-V Bare-Metal Application for QEMU

## Build & Run

### App as M-mode

    ```
    make CROSS_COMPILE=<TOOLCHAIN_DIR>/bin/riscv64-linux-
    qemu-system-riscv64 -M virt -cpu rv64,zkr=on -m 4096 -nographic -bios bm-app.elf
    ```

### App as S-mode

    ```
    make CROSS_COMPILE=<TOOLCHAIN_DIR>/bin/riscv64-linux- BM_S_MODE=1
    ```

    Run with QEMU internal openSBI as M-mode 

    ```
    qemu-system-riscv64 -M virt -cpu rv64,zkr=on -m 4096 -nographic -kernel bm-app.elf
    ```

    Run with pre-built openSBI fw_jump as M-mode

    ```
    qemu-system-riscv64 -M virt -cpu rv64,zkr=on -m 4096 -nographic -bios fw_jump.bin -kernel bm-app.elf 
    ```
