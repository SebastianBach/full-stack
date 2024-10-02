
document.getElementById('submit-button').addEventListener('click', function (event) {

    const overlay = document.getElementById('loading-overlay');
    overlay.style.display = 'block';

    event.preventDefault();
    const text = document.getElementById('text-field').value;
    const data = { 'text': text };
    var xhr = new XMLHttpRequest();
    xhr.open('POST', '/api/headline');
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.onload = function () {

        var result = ""
        if (xhr.status === 200) {
            const response = JSON.parse(xhr.responseText);
            result = response.result;
        }
        else {
            result = 'Request failed: ' + xhr.status;
        }

        var div = document.getElementById("result");
        div.innerHTML = result;

        overlay.style.display = 'none';
    };
    xhr.send(JSON.stringify(data));
});
