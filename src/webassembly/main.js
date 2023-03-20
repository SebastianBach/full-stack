const importObject = {
    console: {
        log: function (value) {
            console.log(value);
        }
    }
};

const runButton = document.getElementById('runButton');
runButton.addEventListener('click', async () => {

    event.preventDefault();

    const text = document.getElementById('text-field').value;

    if (text.length == 0) {
        document.getElementById("result").innerHTML = ""
        return;
    }

    var enc = new TextEncoder();
    arr = enc.encode(text);

    var io_array = new Int32Array(Module.asm.memory.buffer, 0, arr.length);

    // copy data in input/output array
    for (let i = 0; i < arr.length; i++) {
        io_array[i] = arr[i];
    }

    // call function
    Module._title_case(io_array.byteOffset, io_array.length);

    // get results
    var dec = new TextDecoder("utf-8");
    const converted_text = dec.decode(io_array);

    console.log(converted_text);

    // write to UI
    var div = document.getElementById("result");
    div.innerHTML = converted_text;
});

