import fetch from 'node-fetch';

async function fetchArbPrice() {
    try {
        const response = await fetch('https://api.binance.com/api/v3/ticker/price?symbol=ARBEUR');
        
        if (!response.ok) {
            throw new Error(`HTTP error! Status: ${response.status}`);
        }

        const data = await response.json();

        const arbPrice = parseFloat(data.price);

        console.log(arbPrice);
    } catch (error) {
        console.error('Error fetching ARB price:', error.message);
        process.exit(1);
    }
}

fetchArbPrice();
