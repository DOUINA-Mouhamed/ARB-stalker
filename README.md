# ARB stalker 👓


## Introduction 🚀

**ARB Count** is a command-line tool designed to help users manage and evaluate their investments in Arbitrum (ARB) cryptocurrency. The program allows users to track transactions, calculate total investments, and determine potential profits or losses based on the current ARB price. This tool is particularly useful for cryptocurrency enthusiasts and traders who want to keep a close eye on their ARB investments.

## Features 🪶

- **Transaction Tracking**: Add and record transactions including date, amount invested in EUR, and ARB purchased.
- **Investment Overview**: Calculate the total investment amount and ARB holdings from a transaction file.
- **Profit/Loss Calculation**: Determine potential profits or losses by evaluating the current ARB price against the investment amount, considering a 1 EUR cash-out tax.
- **Live Price Fetching**: Fetch the current ARB price in EUR using the CoinGecko API.
- **Help Menu**: Provides guidance on how to use the tool via a `-h` flag.

## Requirements 🖥️

- Windows Operating System
- [Chocolatey](https://chocolatey.org/) package manager
- Node.js
- GCC (GNU Compiler Collection)

## Installation Guide 📰

### Step 1: Install Chocolatey 🍫

Chocolatey is a package manager for Windows that simplifies the installation of software.

1. Open **Windows PowerShell** with **Administrator** privileges.
2. Run the following command to install Chocolatey:

   ```bash
   Set-ExecutionPolicy Bypass -Scope Process -Force; 
   [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; 
   iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
   ```

Or see  [Chocolatey official documentation]([https://link-url-here.org](https://chocolatey.org/install)).

3. Close and reopen PowerShell to refresh the environment variables.

### Step 2: Install Node.js 🌳

Node.js is required to run the JavaScript script that fetches the current ARB price.

1. In PowerShell, run the following command to install Node.js:

   ```bash
   choco install nodejs -y
   ```

2. After installation, verify Node.js is installed by checking the version:

   ```bash
   node -v
   npm -v
   ```

### Step 3: Install GCC 🧬

GCC is required to compile the C program.

1. Install GCC using Chocolatey:

   ```bash
   choco install mingw -y
   ```

2. Verify GCC installation:

   ```bash
   gcc --version
   ```

### Step 4: Clone or Download the ARB Count Project ⬇️

1. Download the project files from the GitHub repository or clone it using Git:

   ```bash
   git clone https://github.com/DOUINA-Mouhamed/arb_count.git
   ```

2. Navigate to the project directory:

   ```bash
   cd arb_count
   ```

### Step 5: Install Node.js Dependencies 🧵

1. Install `node-fetch`, a package required for fetching data from the CoinGecko API:

   ```bash
   npm install node-fetch
   ```

2. Ensure that the `fetchArbPrice.js` script is correctly set to use ES modules. Your `package.json` should include `"type": "module"`:

   ```json
   {
     "name": "arb_count",
     "version": "1.0.0",
     "type": "module",
     "dependencies": {
       "node-fetch": "^3.3.1"
     }
   }
   ```

### Step 6: Compile the C Program ☄️

1. Compile the C program using GCC:

   ```bash
   gcc -o arb_count.exe arb_count.c
   ```

2. The executable `arb_count.exe` should now be in your project directory.

## Usage

The ARB Count tool can be used via command-line arguments. Below are examples of how to use the different functionalities:

### Display Help 🩹

To see the help message with details about available commands:

```bash
.\arb_count.exe -h
```

### Add a New Transaction 💰

To add a new transaction to the specified file:

```bash
.\arb_count.exe -t transactions.txt
```

### Calculate Total Investment and ARB Holdings 📊

To calculate the total investment and ARB holdings from a transactions file:

```bash
.\arb_count.exe transactions.txt
```

### Calculate Profit/Loss 📈

To calculate potential profit or loss based on the current ARB price:

```bash
.\arb_count.exe -s transactions.txt
```

## Examples 🖋️

### Adding a Transaction 💰

After executing the `-t` flag, you will be prompted to enter the transaction details:

```plaintext
Day (DD): 01
Month (MM): 08
Year (YYYY): 2024
EUR (00.00): 12.50
ARB (00.00): 25.00

Transaction added successfully.
```

### Calculating Total Investment 🏛️

Running the tool without any flags will give you a summary of your investments:

```bash
.\arb_count.exe transactions.txt
```

**Output:**

```plaintext
Fetching current ARB price...
Current ARB value in EUR: 0.57956E
Total invested (tax included): 24.82E
Total Arbitrum in possession: 40.00ARB
```

### Calculating Profit/Loss 💹

Using the `-s` flag will show your potential earnings or losses:

```bash
.\arb_count.exe -s transactions.txt
```

**Output:**

```plaintext
Total invested (tax included): 24.82E
Total Arbitrum in possession: 40.00ARB
Current ARB value in EUR: 23.18E
Loss: -2.64E
```

## Explanation of Flags ☑️

- **`-h`**: Display help information about the program and its usage.
- **`-t <filename>`**: Add a new transaction to the specified file, prompting the user for details.
- **`-s <filename>`**: Calculate potential profit or loss based on the current ARB price, considering a 1 EUR cash-out tax.
- **`<filename>`**: Calculate total investment and ARB holdings from the provided transaction file.

## Notes 📔

- The program assumes the transactions file is formatted with lines containing dates, EUR amounts, and ARB amounts, separated by colons (e.g., `01/08/2024:12.50E:25.00ARB`).
- Ensure Node.js and GCC are properly installed and configured in your PATH to compile and execute the program.

## Troubleshooting ⚔️

- **Node.js Not Recognized**: If Node.js commands are not recognized, verify that Node.js is installed and added to your system's PATH.
- **API Rate Limiting**: The CoinGecko API has a rate limit; if you hit this limit, wait a few moments before trying again.
- **Permission Issues**: Run PowerShell or Command Prompt as Administrator if you encounter permission-related errors.

## Contributing 🤝

Contributions are welcome! If you have ideas for improvements or encounter bugs, feel free to fork the repository and submit a pull request.

## License 🗞️

This project is licensed under the MIT License - see the LICENSE file for details.
