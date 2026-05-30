const wifiList = document.getElementById('wifi-list');
const ssidInput = document.getElementById('ssid-input');
const passwordInput = document.getElementById('password-input');
const submitButton = document.getElementById('submit-button');

function fetchWiFiNetworks() {
    fetch('/wifi-networks')
        .then(response => response.json())
        .then(data => {
            wifiList.innerHTML = '';
            data.networks.forEach(network => {
                const option = document.createElement('option');
                option.value = network;
                option.textContent = network;
                wifiList.appendChild(option);
            });
        })
        .catch(error => console.error('Error fetching Wi-Fi networks:', error));
}

submitButton.addEventListener('click', () => {
    const ssid = ssidInput.value;
    const password = passwordInput.value;

    fetch('/save-credentials', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ ssid, password }),
    })
    .then(response => {
        if (response.ok) {
            alert('Credentials saved successfully!');
        } else {
            alert('Failed to save credentials.');
        }
    })
    .catch(error => console.error('Error saving credentials:', error));
});

window.onload = fetchWiFiNetworks;