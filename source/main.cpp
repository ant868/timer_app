#include <switch.h>
#include <string.h>

#define PASSWORD "1234"

static bool check_password() {
    // per semplicità password fissa, qui puoi implementare input touch
    // ritorna true se password corretta, false altrimenti
    // in questo esempio la password è "1234"
    char input[5] = "1234";
    return strcmp(input, PASSWORD) == 0;
}

int main() {
    consoleInit(NULL);

    u64 start = armGetSystemTick();
    u64 timer = 5 * 60 * 1000000000ULL; // 5 minuti in nanosecondi
    bool running = true;

    while (appletMainLoop() && running) {
        hidScanInput();
        u64 now = armGetSystemTick();
        u64 diff = now - start;

        consoleClear();
        printf("Timer App\n");
        printf("Tempo: %llu secondi rimasti\n", (timer - diff) / 1000000000ULL);

        if(diff >= timer) {
            printf("Tempo scaduto!\n");
            if(check_password()) {
                printf("Password corretta, reset timer.\n");
                start = armGetSystemTick(); // reset timer
            } else {
                running = false; // esce dall'app
            }
        }

        printf("\nPremi [PLUS] per uscire.\n");
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
        if(kDown & KEY_PLUS) running = false;

        consoleUpdate(NULL);
        svcSleepThread(100000000ULL / 10);
    }

    consoleExit(NULL);
    return 0;
}
