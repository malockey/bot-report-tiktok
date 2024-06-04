# Bot Report Tiktok

This C++ program uses `libcurl` to report users to TikTok via a provided URL and a list of proxy, handling responses and errors.

## Features

- Reports users to TikTok using a specified URL
- Supports proxy usage from a predefined list
- Validates URLs and handles errors gracefully
- Logs timestamps for each report request

## Prerequisites

- `libcurl` library
- C++ compiler (`g++`)

## Installation

### Linux

1. Install `libcurl`:

```
sudo apt-get install libcurl4-openssl-dev
```

2. Clone the repository:

```
git clone https://github.com/malockey/bot-report-tiktok.git
cd bot-report-tiktok
```

3. Compile the code:

```
g++ mass_report_tiktok.cpp -o mass_report_tiktok -lcurl
```

## Usage

1. Ensure you have a file named `proxies.txt` with proxy URLs listed line by line.
2. Run the program:

```
./mass_report_tiktok
```

3. Enter the TikTok report URL when prompted.

## Example

```
Enter the URL: https://www.tiktok.com/aweme/v2/aweme/feedback?user_id=12345
```

## Output

```
14:54:24 202406041753509012235F8107EC32B509
```
## Educational Purposes

This project is intended for educational purposes only. It is designed to demonstrate the use of `libcurl` in C++ for making HTTP requests and handling proxies. The authors do not condone any misuse of this tool, including reporting users on TikTok without valid reasons.