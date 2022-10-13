
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wasm_export.h>

int main(int argc, char **argv) {
    static char global_heap_buf[512 * 1024];
    char *buffer, error_buf[128];
    int opt;
    char *wasm_path = NULL;

    wasm_module_t module = NULL;
    wasm_module_inst_t module_inst = NULL;
    wasm_exec_env_t exec_env = NULL;
    uint32_t buf_size, stack_size = 8092, heap_size = 8092;
    wasm_function_inst_t func = NULL;
    wasm_function_inst_t func2 = NULL;
    char *native_buffer = NULL;
    uint32_t wasm_buffer = 0;

    RuntimeInitArgs init_args;
    memset(&init_args, 0, sizeof(RuntimeInitArgs));

    init_args.mem_alloc_type = Alloc_With_Pool;
    init_args.mem_alloc_option.pool.heap_buf = global_heap_buf;
    init_args.mem_alloc_option.pool.heap_size = sizeof(global_heap_buf);

    if (!wasm_runtime_full_init(&init_args)) {
        printf("Init runtime environment failed.\n");
        return -1;
    } else {
        printf("Init runtime environment success.\n");
        wasm_runtime_destroy();
        return 0;
    }
}