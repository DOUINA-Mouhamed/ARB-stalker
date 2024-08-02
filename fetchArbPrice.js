import fetch from 'node-fetch';

async function fetchArbPrice() {
    try {
        const response = await fetch('https://api.coingecko.com/api/v3/simple/price?ids=arbitrum&vs_currencies=eur');
        const data = await response.json();

        const arbPrice = data.arbitrum.eur;

        console.log(arbPrice);
    } catch (error) {
        console.error('Error fetching ARB price:', error);
        process.exit(1);
    }
}

fetchArbPrice();
