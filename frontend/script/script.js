const temp_val = document.getElementById('temp_val');
const jog_val = document.getElementById('jog_val');
const addr_srv = "ws://localhost:8080";
const socket = new WebSocket(addr_srv);


const actualise = (temp, jog) => {
    temp_val.innerText = temp;
    jog_val.innerText = jog;
}

socket.addEventListener('message', function (event) {
    const data = JSON.parse(event.data);
    console.log(data);
    actualise(data.temp, data.jog);
});