# ESP32 LED Control with OneButton

##  Yêu cầu phần cứng
- ESP32 DevKit
- 1 LED ngoài nối vào GPIO26 (qua điện trở 1kΩ)
- 1 nút nhấn nối vào GPIO25 (kéo xuống GND)
- LED1: LED tích hợp sẵn trên devboard (GPIO2 tùy loại board)

##  Chức năng
- **Single click**: Bật/Tắt LED hiện tại
- **Double click**: Chuyển điều khiển giữa LED1 (built-in) và LED2 (ngoài)
- **Long press (>1s)**: LED hiện tại nhấp nháy mỗi 200ms
- **Release**: Dừng nhấp nháy và tắt LED

##  Cách chạy
1. Clone repo:
   ```bash
   git clone https://github.com/<username>/<repo-name>.git
   cd <repo-name>

