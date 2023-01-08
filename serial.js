const { SerialPort } =  require('serialport');


const serialport = new SerialPort({ path: '/dev/ttyACM0', baudRate: 15200 })
    setInterval(() => {
    serialport.write(Uint8Array.from([97, 24, 124, 10, 13]));
    }, 1000);
